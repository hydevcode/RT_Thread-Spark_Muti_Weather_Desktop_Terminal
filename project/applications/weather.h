#ifndef WEATHER_H
#define WEATHER_H

struct weather_info
{
    char now_temp[10];
    char now_text[20];
    char now_location[20];
    char now_humi[20];
    char now_time[25];

    char day1_time[10];
    char day1_text[10];
    char day1_temp[10];

    char day2_time[10];
    char day2_text[10];
    char day2_temp[10];

    char day3_time[10];
    char day3_text[10];
    char day3_temp[10];
};

int weather_get_test(struct weather_info *winfo);
#endif // WLAN_CONNECT_H
