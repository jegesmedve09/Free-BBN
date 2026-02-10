#include <tamtypes.h>
#include <kernel.h>
#include <libcdvd.h>
#include <stdio.h>
#include <string.h>
#include <time.h> // ← added for time_t
#include <osd_config.h>
#include "../../../gfx.h"
#include "../../../menu.h"
#include "../../../pad.h"
#include "../../../background.h"
#include "../../../utils.h"

#define DATEANDTIME_INFO_ITEM_COUNT 7
#define DATEANDTIME_INFO_START_Y 160
#define DATEANDTIME_INFO_START_X 40
#define DATEANDTIME_INFO_LINE_HEIGHT 38

static char month_str[72] = "Month: Error/No CMOS";
static char day_str[72] = "Day: Error/No CMOS";
static char year_str[72] = "Year: Error/No CMOS";
static char hour_str[72] = "Hour: Error/No CMOS";
static char min_str[72] = "Min: Error/No CMOS";
static char sec_str[72] = "Sec: Error/No CMOS";
static char dst_str[72] = "DST: --";

static const char *dateandtime_info_items[DATEANDTIME_INFO_ITEM_COUNT];
static char full_time_str[72] = "--:--:--";
static char full_date_str[72] = "-- -- ----";

static u8 month = 0, day = 0, year = 0;
static u8 hour = 0, min = 0, sec = 0;
static u8 is_dst = 0;

// Leap year check (simple for 2000-2099 range)
static int is_leap_year(int y) {
    return ((y + 2000) % 4 == 0);
}

// Days in month array
static const u8 days_per_month[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31}, // non-leap
    {0,31,29,31,30,31,30,31,31,30,31,30,31} // leap
};

static u8 days_in_month(u8 m, u8 y) {
    return days_per_month[is_leap_year(y)][m];
}

// Cumulative days before each month
static const u16 cum_days_before_month[2][13] = {
    {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334}, // non-leap
    {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335} // leap
};

// Convert sceCdCLOCK (JST) to time_t since 2000-01-01 00:00:00
time_t JST_clock_to_epoch(const sceCdCLOCK *clk) {
    int y = bcd_to_dec(clk->year);
    int m = bcd_to_dec(clk->month);
    int d = bcd_to_dec(clk->day);
    int h = bcd_to_dec(clk->hour);
    int mn = bcd_to_dec(clk->minute);
    int s = bcd_to_dec(clk->second);

    int leap = is_leap_year(y);
    long total_days = (long)y * 365;
    if (y > 0) {
        total_days += 1 + ((y - 1) / 4);
    }
    total_days += cum_days_before_month[leap][m];
    total_days += d - 1;

    return total_days * 86400LL + (long)h * 3600 + mn * 60 + s;
}

// Convert time_t since 2000-01-01 to sceCdCLOCK
void epoch_to_JST_clock(time_t epoch_time, sceCdCLOCK *clk) {
    long remaining_days = epoch_time / 86400;
    time_t remaining_secs = epoch_time % 86400;

    // Find year
    int y = 0;
    while (1) {
        int leap_flag = is_leap_year(y);
        long days_in_y = (leap_flag ? 366 : 365);
        if (remaining_days < days_in_y) {
            break;
        }
        remaining_days -= days_in_y;
        y++;
    }

    // Find month
    int leap_flag = is_leap_year(y);
    const u16 *cum_days = cum_days_before_month[leap_flag];
    int m = 1;
    while (m <= 12) {
        if (remaining_days < cum_days[m + 1]) {
            break;
        }
        m++;
    }

    remaining_days -= cum_days[m];
    int d = remaining_days + 1;

    int h = remaining_secs / 3600;
    remaining_secs %= 3600;
    int mn = remaining_secs / 60;
    int s = remaining_secs % 60;

    clk->year = dec_to_bcd(y);
    clk->month = dec_to_bcd(m);
    clk->day = dec_to_bcd(d);
    clk->hour = dec_to_bcd(h);
    clk->minute = dec_to_bcd(mn);
    clk->second = dec_to_bcd(s);
}

static void load_system_info(void) {
    sceCdCLOCK raw_clock;
    if (sceCdReadClock(&raw_clock) != 1) {
        strcpy(full_time_str, "--:--:-- (No CMOS)");
        strcpy(full_date_str, "-- -- ----");
        return;
    }

    // Raw is JST (UTC+9), convert to UTC by subtracting 9 hours
    int utc_h = bcd_to_dec(raw_clock.hour) - 9;
    int day_borrow = 0;
    if (utc_h < 0) {
        utc_h += 24;
        day_borrow = -1;
    }
    sceCdCLOCK utc_clock = raw_clock;
    utc_clock.hour = dec_to_bcd(utc_h);
    if (day_borrow) {
        int d_val = bcd_to_dec(utc_clock.day) + day_borrow;
        int m_val = bcd_to_dec(utc_clock.month);
        int y_val = bcd_to_dec(utc_clock.year);
        if (d_val <= 0) {
            m_val--;
            if (m_val == 0) {
                m_val = 12;
                y_val--;
            }
            d_val += days_in_month(m_val, y_val);
        }
        utc_clock.day = dec_to_bcd(d_val);
        utc_clock.month = dec_to_bcd(m_val);
        utc_clock.year = dec_to_bcd(y_val);
    }

    // UTC to local: add timezone + DST offset
    int timezone_min = configGetTimezone();
    int dst_min = configIsDaylightSavingEnabled() ? 60 : 0;
    int total_offset_min = timezone_min + dst_min;
    time_t utc_epoch = JST_clock_to_epoch(&utc_clock);
    time_t local_epoch = utc_epoch + (time_t)total_offset_min * 60;

    // Convert local epoch back to clock
    sceCdCLOCK local_clock;
    epoch_to_JST_clock(local_epoch, &local_clock);

    sec = bcd_to_dec(local_clock.second);
    min = bcd_to_dec(local_clock.minute);
    hour = bcd_to_dec(local_clock.hour);
    day = bcd_to_dec(local_clock.day);
    month = bcd_to_dec(local_clock.month);
    year = bcd_to_dec(local_clock.year);
    is_dst = configIsDaylightSavingEnabled();

    snprintf(month_str, sizeof(month_str), "Month: %02d", month);
    snprintf(day_str, sizeof(day_str), "Day: %02d", day);
    snprintf(year_str, sizeof(year_str), "Year: 20%02d", year);
    snprintf(hour_str, sizeof(hour_str), "Hour: %02d", hour);
    snprintf(min_str, sizeof(min_str), "Min: %02d", min);
    snprintf(sec_str, sizeof(sec_str), "Sec: %02d", sec);
    snprintf(dst_str, sizeof(dst_str), "DST: %s", is_dst ? "On" : "Off");

    u8 use12h = configGetTimeFormat();
    if (use12h) {
        int h12 = hour % 12;
        if (h12 == 0) h12 = 12;
        snprintf(full_time_str, sizeof(full_time_str), "%02d:%02d:%02d %s",
                 h12, min, sec, hour < 12 ? "AM" : "PM");
    } else {
        snprintf(full_time_str, sizeof(full_time_str), "%02d:%02d:%02d", hour, min, sec);
    }
    snprintf(full_date_str, sizeof(full_date_str), "%02d %02d 20%02d", month, day, year);

    dateandtime_info_items[0] = month_str;
    dateandtime_info_items[1] = day_str;
    dateandtime_info_items[2] = year_str;
    dateandtime_info_items[3] = hour_str;
    dateandtime_info_items[4] = min_str;
    dateandtime_info_items[5] = sec_str;
    dateandtime_info_items[6] = dst_str;
}

static void update_time(void) {
    sceCdCLOCK local_clock;
    local_clock.second = dec_to_bcd(sec);
    local_clock.minute = dec_to_bcd(min);
    local_clock.hour = dec_to_bcd(hour);
    local_clock.day = dec_to_bcd(day);
    local_clock.month = dec_to_bcd(month);
    local_clock.year = dec_to_bcd(year);

    // Local to UTC: subtract offset
    int timezone_min = configGetTimezone();
    int dst_min = configIsDaylightSavingEnabled() ? 60 : 0;
    int total_offset_min = timezone_min + dst_min;
    time_t local_epoch = JST_clock_to_epoch(&local_clock);
    time_t utc_epoch = local_epoch - (time_t)total_offset_min * 60;

    // UTC to JST: add 9 hours
    sceCdCLOCK utc_clock;
    epoch_to_JST_clock(utc_epoch, &utc_clock);
    int jst_h = bcd_to_dec(utc_clock.hour) + 9;
    int day_carry = 0;
    if (jst_h >= 24) {
        day_carry = jst_h / 24;
        jst_h %= 24;
    }
    sceCdCLOCK jst_clock = utc_clock;
    jst_clock.hour = dec_to_bcd(jst_h);
    if (day_carry) {
        int d_val = bcd_to_dec(jst_clock.day) + day_carry;
        int m_val = bcd_to_dec(jst_clock.month);
        int y_val = bcd_to_dec(jst_clock.year);
        while (d_val > days_in_month(m_val, y_val)) {
            d_val -= days_in_month(m_val, y_val);
            m_val++;
            if (m_val == 13) {
                m_val = 1;
                y_val++;
            }
        }
        jst_clock.day = dec_to_bcd(d_val);
        jst_clock.month = dec_to_bcd(m_val);
        jst_clock.year = dec_to_bcd(y_val);
    }

    sceCdWriteClock(&jst_clock);
}

// dateandtime_show() remains similar, with adjustments if needed
int dateandtime_show(void) {
    gfx_fade_in(10);
    while (1) {
        load_system_info();
        background_update();
        gfx_draw_top_bar();
        gfx_draw_text("Date and Time", 40, 60,
                      GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00),10, 4);
        menu_draw(dateandtime_info_items, DATEANDTIME_INFO_ITEM_COUNT,
                  DATEANDTIME_INFO_START_X, DATEANDTIME_INFO_START_Y);
        gfx_draw_text(full_time_str, 350, 100,
                      GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00),10, 4);
        gfx_draw_text(full_date_str, 350, 160,
                      GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00),10, 4);
        gfx_draw_text("\xFF\x00/\xFF\x01 Navigate \xFF\x02/\xFF\x03 Change \xFF\x09 Back",
                      5, 480, GS_SETREG_RGBAQ(0x70,0x70,0x70,0x80,0x00),5, 4);
        gfx_flip();
        gfx_exec();
        u32 pad = pad_get_buttons(0);
        if (pad & PAD_DOWN) {
            menu_increment(); FuckAroundSilentlyMs(300);
        }
        if (pad & PAD_UP) {
            menu_decrement(); FuckAroundSilentlyMs(300);
        }
        if (pad & PAD_TRIANGLE) {
            menu_reset_current_item();
            gfx_fade_out(10);
            return 0;
        }
        int changed = 0;
        int item = menu_get_current_item();
        if (pad & PAD_LEFT) {
            if (item == 0) { month = (month == 1) ? 12 : month - 1; changed = 1; }
            else if (item == 1) {
                day = (day == 1) ? days_in_month(month, year) : day - 1; changed = 1;
            }
            else if (item == 2) { year = (year == 0) ? 99 : year - 1; changed = 1; }
            else if (item == 3) { hour = (hour == 0) ? 23 : hour - 1; changed = 1; }
            else if (item == 4) { min = (min == 0) ? 59 : min - 1; changed = 1; }
            else if (item == 5) { sec = (sec == 0) ? 59 : sec - 1; changed = 1; }
            else if (item == 6) {
                u8 current = configIsDaylightSavingEnabled();
                configSetDaylightSavingEnabled(!current); // toggle
                changed = 1; //// reload display
            }
        }
        if (pad & PAD_RIGHT) {
            if (item == 0) { month = (month == 12) ? 1 : month + 1; changed = 1; }
            else if (item == 1) {
                day = (day == days_in_month(month, year)) ? 1 : day + 1; changed = 1;
            }
            else if (item == 2) { year = (year == 99) ? 0 : year + 1; changed = 1; }
            else if (item == 3) { hour = (hour == 23) ? 0 : hour + 1; changed = 1; }
            else if (item == 4) { min = (min == 59) ? 0 : min + 1; changed = 1; }
            else if (item == 5) { sec = (sec == 59) ? 0 : sec + 1; changed = 1; }
            else if (item == 6) {
                u8 current = configIsDaylightSavingEnabled();
                configSetDaylightSavingEnabled(!current); // toggle
                changed = 1; // reload display
            }
        }
        if (changed) {
            update_time();
            FuckAroundSilentlyMs(300);
        }
    }
}
