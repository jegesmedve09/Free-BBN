#include <tamtypes.h>
#include <kernel.h>
#include <libcdvd.h>
#include <stdio.h>

#include "../../../gfx.h"
#include "../../../menu.h"
#include "../../../pad.h"
#include "../../../background.h"
#include "../../../utils.h"

#define DATEANDTIME_INFO_ITEM_COUNT   7
#define DATEANDTIME_INFO_START_Y      160
#define DATEANDTIME_INFO_START_X      40
#define DATEANDTIME_INFO_LINE_HEIGHT  38

static char month_str[72] = "Month: Error/No CMOS";
u8 month = 0;
static char day_str[72] = "Day: Error/No CMOS";
u8 day = 0;
static char year_str[72] = "Year: Error/No CMOS";
u8 year = 0;
static char hour_str[72] = "Hour: Error/No CMOS";
u8 hour = 0;
static char min_str[72] = "Min: Error/No CMOS";
u8 min = 0;
static char sec_str[72] = "Sec: Error/No CMOS";
u8 sec = 0;
static char dst_str[72] = "Daylight Saving:Error/No CMOS";
u8 dst = 0;
static const char *dateandtime_info_items[DATEANDTIME_INFO_ITEM_COUNT];
char full_time_str[72] = "--:--:--";
char full_date_str[72] = "-- -- ----";

static void load_system_info(void)
{
    sceCdCLOCK clock;

    // Optional: make sure CDVD is initialized

    if (sceCdReadClock(&clock) == 1)  // Success returns 1
    {
        // Convert BCD to decimal for easier display/editing
        sec = bcd_to_dec(clock.second);
        min = bcd_to_dec(clock.minute);
        hour = bcd_to_dec(clock.hour);
        day = bcd_to_dec(clock.day);
        month = bcd_to_dec(clock.month);
        year = bcd_to_dec(clock.year);

        // Format strings (20xx year, padded numbers)
        snprintf(month_str, sizeof(month_str), "Month: %02d", month);
        snprintf(day_str,   sizeof(day_str),   "Day:   %02d", day);
        snprintf(year_str,  sizeof(year_str),  "Year:  20%02d", year);
        snprintf(hour_str,  sizeof(hour_str),  "Hour:  %02d", hour);
        snprintf(min_str,   sizeof(min_str),   "Min:   %02d", min);
        snprintf(sec_str,   sizeof(sec_str),   "Sec:   %02d", sec);
    }
	
	snprintf(full_time_str, sizeof(full_time_str),
                 "%02d:%02d:%02d", hour, min, sec);
	
	snprintf(full_date_str, sizeof(full_date_str),
                 "%02d %02d 20%02d", month, day, year);
	
    // Assign pointers to menu items (do this once after loading)
    dateandtime_info_items[0] = month_str;
    dateandtime_info_items[1] = day_str;
    dateandtime_info_items[2] = year_str;
    dateandtime_info_items[3] = hour_str;
    dateandtime_info_items[4] = min_str;
    dateandtime_info_items[5] = sec_str;
    dateandtime_info_items[6] = dst_str;
}

void update_time(void)
{
    sceCdCLOCK new_clock;

    new_clock.second = dec_to_bcd(sec);
    new_clock.minute = dec_to_bcd(min);
    new_clock.hour = dec_to_bcd(hour);
    new_clock.day = dec_to_bcd(day);
    new_clock.month = dec_to_bcd(month);
    new_clock.year = dec_to_bcd(year);     // year is 00-99 for 2000-2099

    sceCdWriteClock(&new_clock);
}

int dateandtime_show(void)
{
	
	while (1)
	{
		load_system_info();
		
		update_lava_background();
		gfx_draw_top_bar();
        gfx_draw_text("Date and Time", 40, 60,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),10, 4);
		menu_draw(dateandtime_info_items, DATEANDTIME_INFO_ITEM_COUNT, DATEANDTIME_INFO_START_X, DATEANDTIME_INFO_START_Y, DATEANDTIME_INFO_LINE_HEIGHT, GS_SETREG_RGBAQ(0xFF,0xFF,0x00,0x80,0), GS_SETREG_RGBAQ(0x90,0x90,0x90,0x80,0), 4, 10, 8);
        gfx_draw_text(full_time_str, 350, 100,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),10, 4);
        gfx_draw_text(full_date_str, 350, 160,GS_SETREG_RGBAQ(0xFF, 0xFF, 0xFF, 0x80, 0x00),10, 4);
		gfx_draw_text("\xFF\x00/\xFF\x01 Navigate \xFF\x02/\xFF\x03 Modify \xFF\x09 Back",5, 480,GS_SETREG_RGBAQ(0x70, 0x70, 0x70, 0x80, 0x00),5, 4);
		gfx_flip();
		gfx_exec();
		
		if(get_pad_buttons(0) & PAD_DOWN)
		{
			menu_increment();
			FuckAroundSilentlyMs(300);
		}
	
		if(get_pad_buttons(0) & PAD_UP)
		{
			menu_decrement();
			FuckAroundSilentlyMs(300);
		}
		
		if(get_pad_buttons(0) & PAD_TRIANGLE)
		{
			menu_reset_current_item();
			FuckAroundSilentlyMs(300);
			return 0;
		}
		
		if(get_pad_buttons(0) & PAD_LEFT)
		{
			int item = menu_get_current_item();
			
			//if (item == 0) { month = (month == 1) ? 12 : month - 1; }
            //else if (item == 1) { day = (day == 1) ? 31 : day - 1; }  // improve later
            //else if (item == 2) { year = (year == 0) ? 99 : year - 1; }
            //else if (item == 3) { hour = (hour == 0) ? 23 : hour - 1; }
            //else if (item == 4) { min  = (min  == 0) ? 59 : min - 1; }
            //else if (item == 5) { sec  = (sec  == 0) ? 59 : sec - 1; }
            
			if (item == 0)
			{
				month--;
				if (month == 0) month = 12;
				update_time();
				FuckAroundSilentlyMs(300);
			}
			//if (item == 1)
			//{
			//	day--;
			//	if (day == 0) day = 31;
			//	update_time();
			//	FuckAroundSilentlyMs(300);
			//}
			//if (item == 2)
			//{
			//	year--;
			//	if (year == 255) year = 99;
			//	update_time();
			//	FuckAroundSilentlyMs(300);
			//}
			//if (item == 3)
			//{
			//	hour--;
			//	if (hour == 255) hour = 23;
			//	update_time();
			//	FuckAroundSilentlyMs(300);
			//}
			//if (item == 4)
			//{
			//	min--;
			//	if (min == 255) min = 59;
			//	update_time();
			//	FuckAroundSilentlyMs(300);
			//}
			//if (item == 5)
			//{
			//	sec--;
			//	if (sec == 255) sec = 59;
			//	update_time();
			//	FuckAroundSilentlyMs(300);
			//}
		}
		
		if(get_pad_buttons(0) & PAD_RIGHT)
		{
			int item = menu_get_current_item();
			
			if (item == 0) { month = (month == 12) ? 1 : month + 1; }
            else if (item == 1) { day = (day == 31) ? 1 : day + 1; }
            else if (item == 2) { year = (year == 99) ? 0 : year + 1; }
            else if (item == 3) { hour = (hour == 23) ? 0 : hour + 1; }
            else if (item == 4) { min  = (min  == 59) ? 0 : min + 1; }
            else if (item == 5) { sec  = (sec  == 59) ? 0 : sec + 1; }
			
			//if (item == 0)
			//{
			//	month++;
			//	if (month == 13) month = 1;
			//	update_time();
			//	FuckAroundSilentlyMs(300);
			//}
			//if (item == 1)
			//{
			//	day++;
			//	if (day == 32) day = 1;
			//	update_time();
			//	FuckAroundSilentlyMs(300);
			//}
			//if (item == 2)
			//{
			//	year++;
			//	if (year == 100) year = 0;
			//	update_time();
			//	FuckAroundSilentlyMs(300);
			//}
			//if (item == 3)
			//{
			//	hour++;
			//	if (hour == 24) hour = 0;
			//	update_time();
			//	FuckAroundSilentlyMs(300);
			//}
			//if (item == 4)
			//{
			//	min++;
			//	if (min == 60) min = 0;
			//	update_time();
			//	FuckAroundSilentlyMs(300);
			//}
			//if (item == 5)
			//{
			//	sec++;
			//	if (sec == 60) sec = 0;
			//	update_time();
			//	FuckAroundSilentlyMs(300);
			//}
		}
		
	}
}
