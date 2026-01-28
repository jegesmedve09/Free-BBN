#include <tamtypes.h>
#include <kernel.h>
#include <libcdvd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>                      // ← added for time_t
#include <osd_config.h>
#include "../../../gfx.h"
#include "../../../menu.h"
#include "../../../pad.h"
#include "../../../background.h"
#include "../../../utils.h"

#define DATEANDTIME_INFO_ITEM_COUNT 7
#define DATEANDTIME_INFO_START_Y    160
#define DATEANDTIME_INFO_START_X    40
#define DATEANDTIME_INFO_LINE_HEIGHT 38

static char month_str[72] = "Month: Error/No CMOS";
static char day_str[72]   = "Day: Error/No CMOS";
static char year_str[72]  = "Year: Error/No CMOS";
static char hour_str[72]  = "Hour: Error/No CMOS";
static char min_str[72]   = "Min: Error/No CMOS";
static char sec_str[72]   = "Sec: Error/No CMOS";
static char dst_str[72]   = "DST: --";

static const char *dateandtime_info_items[DATEANDTIME_INFO_ITEM_COUNT];

static char full_time_str[72] = "--:--:--";
static char full_date_str[72] = "-- -- ----";

static u8 month = 0, day = 0, year = 0;
static u8 hour = 0, min = 0, sec = 0;
static u8 is_dst = 0;

// NTP epoch offset: seconds from 1900-01-01 to 2000-01-01
#define NTP_TO_Y2K_EPOCH 3155673600UL

// Leap year check (simple for 2000-2099 range)
static int is_leap_year(int y) {
    y += 2000; // y is 0–99 → full year
    return (y % 4 == 0) && (y % 100 != 0 || y % 400 == 0);
}

// Days in month (already have this, but making it array-based for NTPS2 compat)
static const u8 days_per_month[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31}, // non-leap
    {0,31,29,31,30,31,30,31,31,30,31,30,31}  // leap
};

static u8 days_in_month(u8 m, u8 y) {
    return days_per_month[is_leap_year(y)][m];
}

// Convert sceCdCLOCK (local) → Unix time_t since 2000-01-01
time_t sceCdCLOCK_to_time_t(const sceCdCLOCK *clock) {
    int y  = bcd_to_dec(clock->year);
    int m  = bcd_to_dec(clock->month);
    int d  = bcd_to_dec(clock->day);
    int hh = bcd_to_dec(clock->hour);
    int mm = bcd_to_dec(clock->minute);
    int ss = bcd_to_dec(clock->second);

    time_t days = 0;
    for (int yy = 0; yy < y; yy++) {
        days += is_leap_year(yy) ? 366 : 365;
    }
    for (int mm2 = 1; mm2 < m; mm2++) {
        days += days_in_month(mm2, y);
    }
    days += d - 1; // day is 1-based

    return days * 86400 + hh * 3600 + mm * 60 + ss;
}

// Convert time_t (since 2000-01-01) → sceCdCLOCK
void time_t_to_sceCdCLOCK(time_t t, sceCdCLOCK *clock) {
    int y = 0;
    while (t >= (is_leap_year(y) ? 366UL : 365UL) * 86400UL) {
        t -= (is_leap_year(y) ? 366UL : 365UL) * 86400UL;
        y++;
    }
    clock->year = dec_to_bcd(y);

    int m = 1;
    while (t >= days_in_month(m, y) * 86400UL) {
        t -= days_in_month(m, y) * 86400UL;
        m++;
    }
    clock->month = dec_to_bcd(m);

    clock->day = dec_to_bcd((t / 86400) + 1);
    t %= 86400;

    clock->hour   = dec_to_bcd(t / 3600);
    t %= 3600;
    clock->minute = dec_to_bcd(t / 60);
    clock->second = dec_to_bcd(t % 60);
}

// NTP → time_t conversion (from NTPS2)
time_t time_NTP_to_time_t(u32 time_NTP, int offset_min, int dst) {
    time_t ps2_time = (time_t)time_NTP - NTP_TO_Y2K_EPOCH;
    if (dst) offset_min += 60;
    ps2_time += offset_min * 60;
    return ps2_time;
}

static void load_system_info(void)
{
    sceCdCLOCK raw;
    if (sceCdReadClock(&raw) != 1) {
        strcpy(full_time_str, "--:--:-- (No CMOS)");
        strcpy(full_date_str, "-- -- ----");
        return;
    }

    // Raw RTC = JST
    // Convert to local time manually
    int tz_min = configGetTimezone();           // signed minutes from GMT
    int dst_min = configIsDaylightSavingEnabled() ? 60 : 0;
    int offset_min = tz_min + dst_min;

    // JST to UTC: subtract 9 hours (JST = UTC+9)
    int utc_hour = bcd_to_dec(raw.hour) - 9;
    int day_carry = 0;
    if (utc_hour < 0) {
        day_carry = -1;
        utc_hour += 24;
    }

    sceCdCLOCK utc = raw;
    utc.hour = dec_to_bcd(utc_hour);

    if (day_carry) {
        int d = bcd_to_dec(utc.day) + day_carry;
        int m = bcd_to_dec(utc.month);
        int y = bcd_to_dec(utc.year);
        if (d <= 0) {
            m--; if (m == 0) { m = 12; y--; }
            d += days_in_month(m, y);
        }
        utc.day   = dec_to_bcd(d);
        utc.month = dec_to_bcd(m);
        utc.year  = dec_to_bcd(y);
    }

    // UTC to local: add offset
    time_t t_utc = sceCdCLOCK_to_time_t(&utc);
    time_t t_local = t_utc + offset_min * 60;

    sceCdCLOCK local;
    time_t_to_sceCdCLOCK(t_local, &local);

    sec   = bcd_to_dec(local.second);
    min   = bcd_to_dec(local.minute);
    hour  = bcd_to_dec(local.hour);
    day   = bcd_to_dec(local.day);
    month = bcd_to_dec(local.month);
    year  = bcd_to_dec(local.year);
    is_dst = configIsDaylightSavingEnabled();

    snprintf(month_str, sizeof(month_str), "Month: %02d", month);
    snprintf(day_str,   sizeof(day_str),   "Day:   %02d", day);
    snprintf(year_str,  sizeof(year_str),  "Year:  20%02d", year);
    snprintf(hour_str,  sizeof(hour_str),  "Hour:  %02d", hour);
    snprintf(min_str,   sizeof(min_str),   "Min:   %02d", min);
    snprintf(sec_str,   sizeof(sec_str),   "Sec:   %02d", sec);
    snprintf(dst_str,   sizeof(dst_str),   "DST:   %s", is_dst ? "On" : "Off");

    u8 use12h = configGetTimeFormat();
    if (use12h) {
        int h12 = hour % 12; if (h12 == 0) h12 = 12;
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

static void update_time(void)
{
    sceCdCLOCK local;
    local.second = dec_to_bcd(sec);
    local.minute = dec_to_bcd(min);
    local.hour   = dec_to_bcd(hour);
    local.day    = dec_to_bcd(day);
    local.month  = dec_to_bcd(month);
    local.year   = dec_to_bcd(year);

    // Local → UTC (subtract offset)
    int tz_min = configGetTimezone();
    int dst_min = configIsDaylightSavingEnabled() ? 60 : 0;
    int offset_min = tz_min + dst_min;

    time_t t_local = sceCdCLOCK_to_time_t(&local);
    time_t t_utc = t_local - offset_min * 60;

    sceCdCLOCK utc;
    time_t_to_sceCdCLOCK(t_utc, &utc);

    // UTC → JST (+9h)
    int jst_h = bcd_to_dec(utc.hour) + 9;
    int carry_day = 0;
    if (jst_h >= 24) { carry_day = jst_h / 24; jst_h %= 24; }
    else if (jst_h < 0) { carry_day = -1; jst_h += 24; }

    sceCdCLOCK jst = utc;
    jst.hour = dec_to_bcd(jst_h);

    if (carry_day) {
        int new_d = bcd_to_dec(jst.day) + carry_day;
        int m = bcd_to_dec(jst.month);
        int y = bcd_to_dec(jst.year);
        while (new_d <= 0) {
            m--; if (m == 0) { m = 12; y--; }
            new_d += days_in_month(m, y);
        }
        while (new_d > days_in_month(m, y)) {
            new_d -= days_in_month(m, y);
            m++; if (m == 13) { m = 1; y++; }
        }
        jst.day   = dec_to_bcd(new_d);
        jst.month = dec_to_bcd(m);
        jst.year  = dec_to_bcd(y);
    }

    sceCdWriteClock(&jst);
}

// dateandtime_show() remains the same as your last version
// (with PAD_LEFT/RIGHT logic already using days_in_month_func for better day wrapping)
int dateandtime_show(void)
{
	gfx_fade_in(10);
    while (1)
    {
        load_system_info();
        background_update();
        gfx_draw_top_bar();

        gfx_draw_text("Date and Time", 40, 60,
                      GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00),10, 4);
        gfx_draw_text("Based On: ShyavanS + NTPS2.", 40, 420,
                      GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00),5, 4);
        gfx_draw_text("Thanx to u/R3Z3N for the idea", 40, 450,
                      GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00),5, 4);

        menu_draw(dateandtime_info_items, DATEANDTIME_INFO_ITEM_COUNT,
                  DATEANDTIME_INFO_START_X, DATEANDTIME_INFO_START_Y);

        gfx_draw_text(full_time_str, 350, 100,
                      GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00),10, 4);
        gfx_draw_text(full_date_str, 350, 160,
                      GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x80,0x00),10, 4);

        gfx_draw_text("\xFF\x00/\xFF\x01 Navigate  \xFF\x02/\xFF\x03 Change  \xFF\x09 Back",
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
            //else if (item == 6) { /* DST toggle not editable here */ }
        
			else if (item == 6) {
    u8 current = configIsDaylightSavingEnabled();
    configSetDaylightSavingEnabled(!current);  // toggle
    changed = 1;  // reload display
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
            //else if (item == 6) { /* DST toggle not editable here */ }
			
			else if (item == 6) {
    u8 current = configIsDaylightSavingEnabled();
    configSetDaylightSavingEnabled(!current);  // toggle
    changed = 1;  // reload display
}
        }

        if (changed) {
            update_time();
            FuckAroundSilentlyMs(300);
        }
    }
}
