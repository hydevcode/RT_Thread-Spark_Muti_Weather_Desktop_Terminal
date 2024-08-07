/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 * 
 * Again edit by rt-thread group
 * Change Logs:
 * Date          Author          Notes
 * 2019-07-21    MurphyZhao      first edit
 */

#include "rtthread.h"
#include "dev_sign_api.h"
#include "mqtt_api.h"
#include "mqtt_main.h"
#include "jsmn.h"
#include "jsmn_util.h"
#include <drv_gpio.h>
#define GPIO_LED_B    GET_PIN(F, 11)
#define GPIO_LED_R    GET_PIN(F, 12)
char DEMO_PRODUCT_KEY[IOTX_PRODUCT_KEY_LEN + 1] = {0};
char DEMO_DEVICE_NAME[IOTX_DEVICE_NAME_LEN + 1] = {0};
char DEMO_DEVICE_SECRET[IOTX_DEVICE_SECRET_LEN + 1] = {0};

void *HAL_Malloc(uint32_t size);
void HAL_Free(void *ptr);
void HAL_Printf(const char *fmt, ...);
int HAL_GetProductKey(char product_key[IOTX_PRODUCT_KEY_LEN + 1]);
int HAL_GetDeviceName(char device_name[IOTX_DEVICE_NAME_LEN + 1]);
int HAL_GetDeviceSecret(char device_secret[IOTX_DEVICE_SECRET_LEN]);
uint64_t HAL_UptimeMs(void);
int HAL_Snprintf(char *str, const int len, const char *fmt, ...);

#define EXAMPLE_TRACE(fmt, ...)  \
    do { \
        HAL_Printf("%s|%03d :: ", __func__, __LINE__); \
        HAL_Printf(fmt, ##__VA_ARGS__); \
        HAL_Printf("%s", "\r\n"); \
    } while(0)

void mqtt_recv_handle(const uint32_t payload_len,const char *payload)
{
    char *buffer=rt_malloc(payload_len+1);
    rt_memset(buffer,0x00,payload_len+1);

    rt_strcpy(buffer,payload);
    jsmn_parser parser;
    jsmn_init(&parser);

    jsmntok_t *tokens = (jsmntok_t *)rt_malloc(sizeof(jsmntok_t) * 150);
    int tokens_len = jsmn_parse(&parser, buffer, payload_len+1, tokens, 150);
    if (tokens_len <= 0)
    {
        rt_kprintf("Error before: [%d]\r\n", sizeof(tokens));
        return;
    }
    jsmn_item_t root;
    JSMN_ItemInit(&root, tokens, 0, tokens_len);
    jsmn_item_t root_params_item;
    JSMN_GetObjectItem(buffer, &root, "params", &root_params_item);
    jsmn_item_t root_LEDSwitch_R_item;
    jsmn_item_t root_LEDSwitch_B_item;
    //接收命令
    JSMN_GetObjectItem(buffer, &root_params_item, "LEDSwitch_R", &root_LEDSwitch_R_item);
    char* led_r=JSMN_GetValueString(buffer, &root_LEDSwitch_R_item);


    JSMN_GetObjectItem(buffer, &root_params_item, "LEDSwitch_B", &root_LEDSwitch_B_item);
    char *led_b=JSMN_GetValueString(buffer, &root_LEDSwitch_B_item);
    if(led_r!=NULL)
    {
        if(rt_strcmp(led_r,"1")==0)
        {
        rt_pin_write(GPIO_LED_R, PIN_LOW);
        }else{
            rt_pin_write(GPIO_LED_R, PIN_HIGH);
        }
    }
    if(led_b!=NULL)
    {
        if(rt_strcmp(led_b,"1")==0)
        {
        rt_pin_write(GPIO_LED_B, PIN_LOW);
        }else{
            rt_pin_write(GPIO_LED_B, PIN_HIGH);
        }
    }
    rt_free(tokens);
    rt_free(buffer);
}
static void mqtt_main_message_arrive(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
    
}

static int mqtt_main_subscribe(void *handle)
{
    int res = 0;
    const char *fmt = "/%s/%s/user/get";
    char *topic = NULL;
    int topic_len = 0;

    topic_len = strlen(fmt) + strlen(DEMO_PRODUCT_KEY) + strlen(DEMO_DEVICE_NAME) + 1;
    topic = HAL_Malloc(topic_len);
    if (topic == NULL) {
        EXAMPLE_TRACE("memory not enough");
        return -1;
    }
    memset(topic, 0, topic_len);
    HAL_Snprintf(topic, topic_len, fmt, DEMO_PRODUCT_KEY, DEMO_DEVICE_NAME);

    res = IOT_MQTT_Subscribe(handle, topic, IOTX_MQTT_QOS0, mqtt_main_message_arrive, NULL);
    if (res < 0) {
        EXAMPLE_TRACE("subscribe failed");
        HAL_Free(topic);
        return -1;
    }

    HAL_Free(topic);
    return 0;
}

int mqtt_main_publish(void *handle, char *payload)
{
    int             res = 0;
    const char     *fmt = "/sys/%s/%s/thing/event/property/post";
    char           *topic = NULL;
    int             topic_len = 0;


    topic_len = strlen(fmt) + strlen(DEMO_PRODUCT_KEY) + strlen(DEMO_DEVICE_NAME) + 1;
    topic = HAL_Malloc(topic_len);
    if (topic == NULL) {
        EXAMPLE_TRACE("memory not enough");
        return -1;
    }
    memset(topic, 0, topic_len);
    HAL_Snprintf(topic, topic_len, fmt, DEMO_PRODUCT_KEY, DEMO_DEVICE_NAME);

    res = IOT_MQTT_Publish_Simple(0, topic, IOTX_MQTT_QOS0, payload, strlen(payload));
    if (res < 0) {
        EXAMPLE_TRACE("publish failed, res = %d", res);
        HAL_Free(topic);
        return -1;
    }

    HAL_Free(topic);
    return 0;
}

static void mqtt_main_event_handle(void *pcontext, void *pclient, iotx_mqtt_event_msg_pt msg)
{
    EXAMPLE_TRACE("msg->event_type : %d", msg->event_type);
    iotx_mqtt_topic_info_t     *topic_info = (iotx_mqtt_topic_info_pt) msg->msg;

    switch (msg->event_type) {
        case IOTX_MQTT_EVENT_PUBLISH_RECEIVED:
            /* print topic name and topic message */
            // EXAMPLE_TRACE("Message Arrived:");
            // EXAMPLE_TRACE("Topic  : %.*s", topic_info->topic_len, topic_info->ptopic);
            // EXAMPLE_TRACE("Payload: %.*s", topic_info->payload_len, topic_info->payload);
            // EXAMPLE_TRACE("\n");
            mqtt_recv_handle(topic_info->payload_len,topic_info->payload);
            break;
        default:
            break;
    }
}


void mqtt_main_init(void)
{

    int                     res = 0;
    iotx_mqtt_param_t       mqtt_params;

    HAL_GetProductKey(DEMO_PRODUCT_KEY);
    HAL_GetDeviceName(DEMO_DEVICE_NAME);
    HAL_GetDeviceSecret(DEMO_DEVICE_SECRET);

    EXAMPLE_TRACE("mqtt example");

    memset(&mqtt_params, 0x0, sizeof(mqtt_params));

    mqtt_params.handle_event.h_fp = mqtt_main_event_handle;

    pclient = IOT_MQTT_Construct(&mqtt_params);
    if (NULL == pclient) {
        EXAMPLE_TRACE("MQTT construct failed");
        return;
    }

    res = mqtt_main_subscribe(pclient);
    if (res < 0) {
        IOT_MQTT_Destroy(&pclient);
        return;
    }
    rt_pin_mode(GPIO_LED_B, PIN_MODE_OUTPUT);
    rt_pin_mode(GPIO_LED_R, PIN_MODE_OUTPUT);
    rt_pin_write(GPIO_LED_B, PIN_HIGH);
    rt_pin_write(GPIO_LED_R, PIN_HIGH);
    return;
}
void mqtt_main(void *par){

    mqtt_main_init();
    while(1)
    {
        IOT_MQTT_Yield(pclient, 200);
    }

return ;
}
struct rt_thread mqtt_main_thread;
rt_uint8_t mqtt_main_thread_stack[2048];
int mqtt_main_thread_init(void)
{
    rt_err_t err;
    err = rt_thread_init(&mqtt_main_thread, "mqtt_main_thread", mqtt_main, RT_NULL,
           &mqtt_main_thread_stack[0], sizeof(mqtt_main_thread_stack), 20, 10);
    if(err != RT_EOK)
    {
        return -1;
    }
    rt_thread_startup(&mqtt_main_thread);
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(mqtt_main_thread_init,mqtt_main_thread_init);
#endif
