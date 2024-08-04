
#include <rtthread.h>
#include <webclient.h>
#include "weather.h"

#include <string.h>
#define GET_HEADER_BUFSZ               1024
#define GET_RESP_BUFSZ                 1200
#include "jsmn.h"
#include "jsmn_util.h"

static char uri[]={"http://api.map.baidu.com/weather/v1/?district_id=城市ID&data_type=all&ak=密钥"};

unsigned char *buffer = RT_NULL;
int bytes_read;

static int weather_get_comm(const char *uri)
{
    struct webclient_session* session = RT_NULL;

    int index, ret = 0;
    int  resp_status;
    int content_length = -1;

    session = webclient_session_create(GET_HEADER_BUFSZ);
    if (session == RT_NULL)
    {
        ret = -RT_ENOMEM;
        goto __exit;
    }
    if ((resp_status = webclient_get(session, uri)) != 200)
    {
        rt_kprintf("webclient GET request failed, response(%d) error.\n", resp_status);
        ret = -RT_ERROR;
        goto __exit;
    }

    rt_kprintf("webclient get response data: \n");

    content_length = webclient_content_length_get(session);
    if (content_length < 0)
    {
        rt_kprintf("webclient GET request type is chunked.\n");
        do
        {
            bytes_read = webclient_read(session, (void *)buffer, GET_RESP_BUFSZ);
            if (bytes_read <= 0)
            {
                break;
            }

        } while (1);

    }
    else
    {
        int content_pos = 0;

        do
        {
            bytes_read = webclient_read(session, (void *)buffer,
                    content_length - content_pos > GET_RESP_BUFSZ ?
                            GET_RESP_BUFSZ : content_length - content_pos);
            if (bytes_read <= 0)
            {
                break;
            }
            content_pos += bytes_read;
        } while (content_pos < content_length);


    }
 

__exit:
    if (session)
    {
        webclient_close(session);
    }

    return ret;
}

int weather_get_test(struct weather_info *winfo)
{

    int ret = 0;
 
    buffer = (unsigned char *) web_malloc(GET_RESP_BUFSZ);
    if (buffer == RT_NULL)
    {
        rt_kprintf("no memory for receive buffer.\n");
        ret = -RT_ENOMEM;
        goto __exit;

    }

    rt_memset(buffer,0x00,GET_RESP_BUFSZ);
    if(weather_get_comm(uri)==RT_EOK)
    {

        jsmn_parser parser;
        jsmn_init(&parser);

        jsmntok_t *tokens = (jsmntok_t *)rt_malloc(sizeof(jsmntok_t) * 150);
        int tokens_len = jsmn_parse(&parser, buffer, bytes_read, tokens, 150);
        if (tokens_len <= 0)
        {
            rt_kprintf("Error before: [%d]\r\n", sizeof(tokens));
            return -RT_ERROR;
        }

        jsmn_item_t root;
        JSMN_ItemInit(&root, tokens, 0, tokens_len);
        
        jsmn_item_t root_result_item;
        JSMN_GetObjectItem(buffer, &root, "result", &root_result_item);

        jsmn_item_t root_location_item;
        JSMN_GetObjectItem(buffer, &root_result_item, "location", &root_location_item);
        
        jsmn_item_t root_name_item;
        JSMN_GetObjectItem(buffer, &root_location_item, "name", &root_name_item);
        char *item_name=JSMN_GetValueString(buffer, &root_name_item);

        jsmn_item_t root_now_item;
        JSMN_GetObjectItem(buffer, &root_result_item, "now", &root_now_item);

        jsmn_item_t root_text_item;
        JSMN_GetObjectItem(buffer, &root_now_item, "text", &root_text_item);
        char *item_text=JSMN_GetValueString(buffer, &root_text_item);

        jsmn_item_t root_rh_item;
        JSMN_GetObjectItem(buffer, &root_now_item, "rh", &root_rh_item);
        char *item_rh=JSMN_GetValueString(buffer, &root_rh_item);

        jsmn_item_t root_feels_like_item;
        JSMN_GetObjectItem(buffer, &root_now_item, "feels_like", &root_feels_like_item);
        char *item_feels_like=JSMN_GetValueString(buffer, &root_feels_like_item);

        jsmn_item_t root_forecasts_item;
        JSMN_GetObjectItem(buffer, &root_result_item, "forecasts", &root_forecasts_item);

        jsmn_item_t root_day1_item;
        JSMN_GetArrayItem(&root_forecasts_item, 0, &root_day1_item);

        jsmn_item_t root_day1_high_item;
        JSMN_GetObjectItem(buffer, &root_day1_item, "high", &root_day1_high_item);
        char *root_day1_high=JSMN_GetValueString(buffer, &root_day1_high_item);

        jsmn_item_t root_day1_low_item;
        JSMN_GetObjectItem(buffer, &root_day1_item, "low", &root_day1_low_item);
        char *root_day1_low=JSMN_GetValueString(buffer, &root_day1_low_item);

        jsmn_item_t root_day1_date_item;
        JSMN_GetObjectItem(buffer, &root_day1_item, "date", &root_day1_date_item);
        char *root_day1_date=JSMN_GetValueString(buffer, &root_day1_date_item);

        jsmn_item_t root_day1_week_item;
        JSMN_GetObjectItem(buffer, &root_day1_item, "week", &root_day1_week_item);
        char *root_day1_week=JSMN_GetValueString(buffer, &root_day1_week_item);

        jsmn_item_t root_day2_item;
        JSMN_GetArrayItem(&root_forecasts_item, 1, &root_day2_item);

        jsmn_item_t root_day2_text_day_item;
        JSMN_GetObjectItem(buffer, &root_day2_item, "text_day", &root_day2_text_day_item);
        char *root_day2_text_day=JSMN_GetValueString(buffer, &root_day2_text_day_item);

        jsmn_item_t root_day2_high_item;
        JSMN_GetObjectItem(buffer, &root_day2_item, "high", &root_day2_high_item);
        char *root_day2_high=JSMN_GetValueString(buffer, &root_day2_high_item);

        jsmn_item_t root_day2_low_item;
        JSMN_GetObjectItem(buffer, &root_day2_item, "low", &root_day2_low_item);
        char *root_day2_low=JSMN_GetValueString(buffer, &root_day2_low_item);

        jsmn_item_t root_day2_week_item;
        JSMN_GetObjectItem(buffer, &root_day2_item, "week", &root_day2_week_item);
        char *root_day2_week=JSMN_GetValueString(buffer, &root_day2_week_item);

        jsmn_item_t root_day3_item;
        JSMN_GetArrayItem(&root_forecasts_item, 2, &root_day3_item);

        jsmn_item_t root_day3_text_day_item;
        JSMN_GetObjectItem(buffer, &root_day3_item, "text_day", &root_day3_text_day_item);
        char *root_day3_text_day=JSMN_GetValueString(buffer, &root_day3_text_day_item);

        jsmn_item_t root_day3_high_item;
        JSMN_GetObjectItem(buffer, &root_day3_item, "high", &root_day3_high_item);
        char *root_day3_high=JSMN_GetValueString(buffer, &root_day3_high_item);

        jsmn_item_t root_day3_low_item;
        JSMN_GetObjectItem(buffer, &root_day3_item, "low", &root_day3_low_item);
        char *root_day3_low=JSMN_GetValueString(buffer, &root_day3_low_item);

        jsmn_item_t root_day3_week_item;
        JSMN_GetObjectItem(buffer, &root_day3_item, "week", &root_day3_week_item);
        char *root_day3_week=JSMN_GetValueString(buffer, &root_day3_week_item);

        jsmn_item_t root_day4_item;
        JSMN_GetArrayItem(&root_forecasts_item, 3, &root_day4_item);

        jsmn_item_t root_day4_text_day_item;
        JSMN_GetObjectItem(buffer, &root_day4_item, "text_day", &root_day4_text_day_item);
        char *root_day4_text_day=JSMN_GetValueString(buffer, &root_day4_text_day_item);


        jsmn_item_t root_day4_high_item;
        JSMN_GetObjectItem(buffer, &root_day4_item, "high", &root_day4_high_item);
        char *root_day4_high=JSMN_GetValueString(buffer, &root_day4_high_item);

        jsmn_item_t root_day4_low_item;
        JSMN_GetObjectItem(buffer, &root_day4_item, "low", &root_day4_low_item);
        char *root_day4_low=JSMN_GetValueString(buffer, &root_day4_low_item);


        jsmn_item_t root_day4_week_item;
        JSMN_GetObjectItem(buffer, &root_day4_item, "week", &root_day4_week_item);
        char *root_day4_week=JSMN_GetValueString(buffer, &root_day4_week_item);

        strcpy(winfo->now_text, item_text);
        strcat(winfo->now_text, " ");
        strcat(winfo->now_text, root_day1_high);
        strcat(winfo->now_text, "/");
        strcat(winfo->now_text, root_day1_low);
        strcat(winfo->now_text, "°C\0");

        strcpy(winfo->now_location, item_name);
        strcpy(winfo->now_temp, item_feels_like);
        strcat(winfo->now_temp, "°");

        strncpy(winfo->now_humi, "空气湿度 ",sizeof("空气湿度 "));
        strcat(winfo->now_humi, item_rh);
        strcat(winfo->now_humi, "%\0\0\0\0");

        char *root_day1_date_2=strrchr(root_day1_date,'-');
        char *root_day1_date_1=root_day1_date;
        root_day1_date_1[root_day1_date_2-root_day1_date]='\0';
        root_day1_date_1=strchr(root_day1_date_1,'-');
        root_day1_date_1=root_day1_date_1+1;
        root_day1_date_2=root_day1_date_2+1;
        root_day1_date_2[2]='\0';

        strcpy(winfo->now_time, root_day1_date_1);
        strcat(winfo->now_time, "月");
        strcat(winfo->now_time, root_day1_date_2);
        strcat(winfo->now_time, "日 ");
        strcat(winfo->now_time, root_day1_week);
        strcat(winfo->now_time, "\0\0\0\0");  

        strcpy(winfo->day1_text, root_day2_text_day);
        strcpy(winfo->day1_temp, root_day2_high);
        strcat(winfo->day1_temp, "/");
        strcat(winfo->day1_temp, root_day2_low);
        strcat(winfo->day1_temp, "°C");

        char *root_day2_week_1=strrchr(root_day2_week,'期');
        root_day2_week_1++;
        strcpy(winfo->day1_time,"周");
        strcat(winfo->day1_time, root_day2_week_1);

       strcpy(winfo->day2_text, root_day3_text_day);
        strcpy(winfo->day2_temp, root_day3_high);
        strcat(winfo->day2_temp, "/");
        strcat(winfo->day2_temp, root_day3_low);
        strcat(winfo->day2_temp, "°C");

        char *root_day3_week_1=strrchr(root_day3_week,'期');
        root_day3_week_1++;
        strcpy(winfo->day2_time,"周");
        strcat(winfo->day2_time, root_day3_week_1);

       strcpy(winfo->day3_text, root_day4_text_day);
        strcpy(winfo->day3_temp, root_day4_high);
        strcat(winfo->day3_temp, "/");
        strcat(winfo->day3_temp, root_day4_low);
        strcat(winfo->day3_temp, "°C");

        char *root_day4_week_1=strrchr(root_day4_week,'期');
        root_day4_week_1++;
        strcpy(winfo->day3_time,"周");
        strcat(winfo->day3_time, root_day4_week_1);
        rt_free(tokens);
    }else
    {
        ret = -RT_ERROR;
        goto __exit;
    }

__exit:
    if (buffer)
    {
        web_free(buffer);
    }

    return RT_EOK;
}
