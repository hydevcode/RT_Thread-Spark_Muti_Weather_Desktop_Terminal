#include <rtdevice.h>
#include <board.h>
#include <drv_matrix_led.h>
#include <drv_common.h>
#include <drv_gpio.h>
#include <string.h>
#include "led_clock.h"
const RGBColor_TypeDef LT_HOUR = {50, 50, 50};
const RGBColor_TypeDef LT_MINUTE_TEN = {50, 50, 50};
const RGBColor_TypeDef LT_MINUTE_UNIT = {20, 50, 10};
const RGBColor_TypeDef LT_MINUTE = {50, 25, 10};

rt_thread_t led_matrix_thread;
void led_matrix_set_time(int hour, int minute)
{
    led_matrix_fill(DARK);
    if(hour==12)
        Set_LEDColor(0,LT_HOUR);
    else
        Set_LEDColor(hour,LT_HOUR);
    
    int ten=minute/10;

    int unit=minute%10;
    if(ten!=0)
    {
        Set_LEDColor(ten+12,LT_MINUTE_TEN);
    }
    
        if(unit>5)
        {
            unit=unit-5;
            Set_LEDColor(18,LT_MINUTE_UNIT);
        }
        if(ten==unit&&ten!=0)
        {
            Set_LEDColor(ten+12,LT_MINUTE);
        }else{
            Set_LEDColor(unit+12,LT_MINUTE_UNIT);
        }
    RGB_Reflash();

}
void led_matrix_example_entry()
{
    time_t now = (time_t)0;
        struct timeval tv = { 0 };
        gettimeofday(&tv, RT_NULL);
        now = tv.tv_sec;
               
        char *time_str=ctime(&now);
        char *time_minute=strchr(time_str,':');
        time_minute[3]='\0';
        char *time_hour=&time_str[time_minute-time_str-2];

        time_minute++;
        time_hour[2]='\0';

        int hour_i=atoi(time_hour);
        int minute_i=atoi(time_minute);
        led_matrix_set_time(hour_i%12,minute_i);

}
