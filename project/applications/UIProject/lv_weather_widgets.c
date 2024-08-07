/**
 * @file lv_weather_widgets.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <lvgl.h>
#include "lv_weather_widgets.h"
#include "weather.h"
#include "led_clock.h"
#include "aht10.h"
#include "mqtt_main.h"
#include "ap3216c.h"
#if LV_MEM_CUSTOM == 0 && LV_MEM_SIZE < (38ul * 1024ul)
    #error Insufficient memory for lv_demo_widgets. Please set LV_MEM_SIZE to at least 38KB (38ul * 1024ul).  48KB is recommended.
#endif

/*********************
 *      DEFINES
 *********************/
#define AHT21_I2C_BUS "i2c3"
#define LIGHT_I2C_BUS "i2c2"
struct rt_thread AHT21_t;
aht10_device_t Dev = RT_NULL;
float Humi,Temp;
rt_uint8_t aht21_thread_stack[800];


ap3216c_device_t dev_light;
rt_uint16_t ps_data;
float brightness;
/**********************
 *      TYPEDEFS
 **********************/
typedef enum {
    DISP_SMALL,
    DISP_MEDIUM,
    DISP_LARGE,
} disp_size_t;


lv_obj_t *wlabel1;
lv_obj_t *wlabel2;
lv_obj_t *wlabel3;
lv_obj_t *wlabel_temp;
lv_obj_t *wlabel_location;
lv_obj_t *layout6_label1;
lv_obj_t *layout6_label2;
lv_obj_t *layout6_label3;
lv_obj_t *layout7_label1;
lv_obj_t *layout7_label2;
lv_obj_t *layout7_label3;  
lv_obj_t *layout8_label1;
lv_obj_t *layout8_label2;
lv_obj_t *layout8_label3;
lv_obj_t *title;

static lv_timer_t *timer = NULL;
void timer_callback(lv_timer_t *timer)
{
   struct weather_info *winfo;
   winfo=rt_malloc(sizeof(struct weather_info));

    rt_memset(winfo, 0x00, sizeof(struct weather_info));
    weather_get_test(winfo);

    lv_label_set_text(wlabel1, winfo->now_text);
    lv_label_set_text(wlabel2, winfo->now_humi);
    lv_label_set_text(wlabel3,winfo->now_time);
    lv_label_set_text(wlabel_temp, winfo->now_temp);
    lv_label_set_text(wlabel_location, winfo->now_location);

    lv_label_set_text(layout6_label1, winfo->day1_time);
    lv_label_set_text(layout6_label2, winfo->day1_text);
    lv_label_set_text(layout6_label3, winfo->day1_temp);

    lv_label_set_text(layout7_label1, winfo->day2_time);
    lv_label_set_text(layout7_label2, winfo->day2_text);
    lv_label_set_text(layout7_label3, winfo->day2_temp);

    lv_label_set_text(layout8_label1, winfo->day3_time);
    lv_label_set_text(layout8_label2, winfo->day3_text);
    lv_label_set_text(layout8_label3, winfo->day3_temp);

    rt_free(winfo);
}
static lv_timer_t *timer2 = NULL;
int count=0;
void timer2_callback(lv_timer_t *timer)
{
        Humi=aht10_read_humidity(Dev);
        Temp=aht10_read_temperature(Dev);
        char buf[40]={'\0'};
        rt_sprintf(buf, "温度:%.2f°C  湿度:%.2f ", Temp,Humi);
        strcat(buf,"%");
        lv_label_set_text(title, buf);
        if(count>5){
        ps_data = ap3216c_read_ps_data(dev_light);
        brightness = ap3216c_read_ambient_light(dev_light);
        char           *payload = "{\"params\":{\"CurrentTemperature\": %.2f,\"CurrentHumidity\": %.2f,\"LightLux\": %.2f,\"ps_data\": %d}}";
        char payload_t[100]={'\0'};
        rt_sprintf(payload_t, payload, Temp,Humi,brightness,ps_data);
        mqtt_main_publish(pclient,payload_t);
        count=0;
        }
        count++;
        led_matrix_example_entry();
 
}

static disp_size_t disp_size;
static const lv_font_t * font_large;
static const lv_font_t * font_normal;

void lv_weather_widgets(void)
{
    
    disp_size = DISP_SMALL; //屏幕大小

    font_large = LV_FONT_DEFAULT;
    font_normal = LV_FONT_DEFAULT;
    font_large     = &lv_font_montserrat_24;
    font_normal     = &lv_font_gen_jyuu_gothic_new_14;

    Dev=aht10_init(AHT21_I2C_BUS);
    if(Dev==RT_NULL)
    {
        rt_kprintf("aht10 init failed\n");
        return;
    }
    dev_light = ap3216c_init(LIGHT_I2C_BUS);
    if (dev_light == RT_NULL)
    {
        rt_kprintf("The sensor initializes failure.");
        return;
    }
    lv_obj_set_style_text_font(lv_scr_act(), font_normal, 0);
    static lv_style_t style_border;
    // lv_style_set_text_color(&style_title, lv_theme_get_color_primary(NULL));
    lv_style_set_border_width(&style_border, 0);
    lv_style_set_pad_all(&style_border, -5);

    lv_obj_t *page1 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(page1, LV_HOR_RES, LV_VER_RES);
    lv_obj_center(page1);
    lv_obj_set_layout(page1, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(page1, LV_FLEX_FLOW_COLUMN_WRAP);
    lv_obj_set_flex_align(page1, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(page1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(page1, &style_border,0);

    static lv_style_t style_text;
    // lv_style_set_text_color(&style_title, lv_theme_get_color_primary(NULL));
    lv_style_set_text_font(&style_text, font_normal);
    lv_style_set_align(&style_text, LV_ALIGN_CENTER);
    lv_style_set_pad_all(&style_text, 3);

    lv_obj_t *layout1= lv_obj_create(page1);
    lv_obj_set_size(layout1, LV_VER_RES-15, LV_HOR_RES-55);
    lv_obj_align_to(layout1, page1, LV_FLEX_ALIGN_CENTER, 0, 1);
    lv_obj_set_flex_flow(layout1, LV_FLEX_FLOW_COLUMN_WRAP);
    lv_obj_set_flex_align(layout1, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_style(layout1, &style_border,0);

    lv_obj_t *layout2= lv_obj_create(layout1);//管理今天天气图标天气文字
    lv_obj_set_size(layout2, LV_VER_RES-20, 80);
    lv_obj_align_to(layout2, layout1, LV_FLEX_ALIGN_CENTER, 0, 1);
    lv_obj_set_flex_flow(layout2, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(layout2, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(layout2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(layout2, &style_border,0);

    lv_obj_t *layout3= lv_obj_create(layout2);//今天天气图标
    lv_obj_set_size(layout3, 70, 70);
    lv_obj_align_to(layout3, layout2, LV_FLEX_ALIGN_CENTER, 0, 0);
    lv_obj_set_flex_flow(layout3, LV_FLEX_FLOW_COLUMN_WRAP);
    lv_obj_set_flex_align(layout3, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_style(layout3, &style_border,0);

    lv_obj_t *layout4= lv_obj_create(layout2);//天气文字
    lv_obj_set_size(layout4, 115, 70);
    lv_obj_align_to(layout4, layout2, LV_FLEX_ALIGN_CENTER, 0, 0);
    lv_obj_set_flex_flow(layout4, LV_FLEX_FLOW_COLUMN_WRAP);
    lv_obj_set_flex_align(layout4, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_scrollbar_mode(layout4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(layout4, &style_border,0);
    
    lv_obj_t *layout5= lv_obj_create(layout1);//未来天气
    lv_obj_set_size(layout5, LV_VER_RES-20, 90);
    lv_obj_align_to(layout5, layout1, LV_FLEX_ALIGN_CENTER, 0, 0);
    lv_obj_set_flex_flow(layout5, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(layout5, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_style(layout5, &style_border,0);
    lv_obj_set_scrollbar_mode(layout5, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *layout6= lv_obj_create(layout5);//未来天气1
    lv_obj_set_size(layout6, 65, 70);
    lv_obj_align_to(layout6, layout5, LV_FLEX_ALIGN_CENTER, 0, 1);
    lv_obj_set_flex_flow(layout6, LV_FLEX_FLOW_COLUMN_WRAP);
    lv_obj_set_flex_align(layout6, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
       lv_obj_add_style(layout6, &style_border,0);
       lv_obj_set_scrollbar_mode(layout6, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *layout7= lv_obj_create(layout5);//未来天气2
    lv_obj_set_size(layout7, 65, 70);
    lv_obj_align_to(layout7, layout5, LV_FLEX_ALIGN_CENTER, 0, 1);
    lv_obj_set_flex_flow(layout7, LV_FLEX_FLOW_COLUMN_WRAP);
    lv_obj_set_flex_align(layout7, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_style(layout7, &style_border,0);
    lv_obj_set_scrollbar_mode(layout7, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *layout8= lv_obj_create(layout5);//未来天气3
    lv_obj_set_size(layout8, 65, 70);
    lv_obj_align_to(layout8, layout5, LV_FLEX_ALIGN_CENTER, 0, 1);
    lv_obj_set_flex_flow(layout8, LV_FLEX_FLOW_COLUMN_WRAP);
    lv_obj_set_flex_align(layout8, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_style(layout8, &style_border,0);
    lv_obj_set_scrollbar_mode(layout8, LV_SCROLLBAR_MODE_OFF);

    wlabel1 = lv_label_create(layout4);
    lv_label_set_text(wlabel1, "雷阵雨 32/26°C");
    lv_obj_add_style(wlabel1, &style_text,0);
    wlabel2 = lv_label_create(layout4);
    lv_label_set_text(wlabel2, "空气湿度 90%");
    lv_obj_add_style(wlabel2, &style_text,0);
    wlabel3 = lv_label_create(layout4);
    lv_label_set_text(wlabel3, "7月32日 星期三");
    lv_obj_add_style(wlabel3, &style_text,0);

    wlabel_temp = lv_label_create(layout3);
    lv_label_set_text(wlabel_temp, "28°");
    static lv_style_t style_title;
    lv_obj_add_style(wlabel_temp, &style_title,0);
    lv_style_set_text_font(&style_title, font_large);
    wlabel_location = lv_label_create(layout3);
    lv_label_set_text(wlabel_location, "北京");
    lv_obj_add_style(wlabel_location, &style_text,0);

    layout6_label1 = lv_label_create(layout6);
    lv_label_set_text(layout6_label1, "周四");
    lv_obj_add_style(layout6_label1, &style_text,0);
    layout6_label2 = lv_label_create(layout6);
    lv_label_set_text(layout6_label2, "多云");
    lv_obj_add_style(layout6_label2, &style_text,0);
    layout6_label3 = lv_label_create(layout6);
    lv_label_set_text(layout6_label3, "34/27°C");
    lv_obj_add_style(layout6_label3, &style_text,0);

    layout7_label1 = lv_label_create(layout7);
    lv_label_set_text(layout7_label1, "周五");
    lv_obj_add_style(layout7_label1, &style_text,0);
    layout7_label2 = lv_label_create(layout7);
    lv_label_set_text(layout7_label2, "多云");
    lv_obj_add_style(layout7_label2, &style_text,0);
    layout7_label3 = lv_label_create(layout7);
    lv_label_set_text(layout7_label3, "34/27°C");
    lv_obj_add_style(layout7_label3, &style_text,0);

    layout8_label1 = lv_label_create(layout8);
    lv_label_set_text(layout8_label1, "周六");
    lv_obj_add_style(layout8_label1, &style_text,0);
    layout8_label2 = lv_label_create(layout8);
    lv_label_set_text(layout8_label2, "多云");
    lv_obj_add_style(layout8_label2, &style_text,0);
    layout8_label3 = lv_label_create(layout8);
    lv_label_set_text(layout8_label3, "34/27°C");
    lv_obj_add_style(layout8_label3, &style_text,0);


    lv_obj_t *layout_title = lv_obj_create(page1);
    lv_obj_set_flex_align(layout_title, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_size(layout_title, LV_HOR_RES-15, 35);
    lv_obj_set_scrollbar_mode(layout_title, LV_SCROLLBAR_MODE_OFF);

    title = lv_label_create(layout_title);
    lv_label_set_text(title, "温度:0.0°  湿度:0.0%");

    lv_obj_align_to(title, layout_title, LV_ALIGN_TOP_MID, 0, 0);
    lv_style_set_text_font(&style_text, font_normal);


    lv_style_set_pad_all(&style_text, -4);
    lv_obj_add_style(title, &style_text,0);


    timer = lv_timer_create(timer_callback, 600000, NULL);
    lv_timer_ready(timer);

    timer2 = lv_timer_create(timer2_callback, 1000, NULL);
 

 
   mqtt_main_thread_init();
}
void lv_weather_widgets_close(void)
{
    lv_anim_del(NULL, NULL);
    lv_obj_clean(lv_scr_act());

}