#include <rthw.h>
#include <rtthread.h>

#include <wlan_connect.h>

#include <wlan_mgnt.h>
#include <wlan_prot.h>
#include <wlan_cfg.h>

#include <stdlib.h>


char wlan_ssid[] = "wifi scan WIFI名";
char wlan_password[] = "wifi join WIFI名 密码";
#define NET_READY_TIME_OUT       (rt_tick_from_millisecond(15 * 1000))

static void
wifi_ready_callback(int event, struct rt_wlan_buff *buff, void *parameter)
{
    rt_kprintf("%s\n", __FUNCTION__);
    char str[] = "ntp_sync";
    system(str);

}

static void
wifi_connect_callback(int event, struct rt_wlan_buff *buff, void *parameter)
{
    rt_kprintf("%s\n", __FUNCTION__);
    if ((buff != RT_NULL) && (buff->len == sizeof(struct rt_wlan_info)))
    {
        rt_kprintf("ssid : %s \n", ((struct rt_wlan_info *)buff->data)->ssid.val);
    }
}

static void
wifi_disconnect_callback(int event, struct rt_wlan_buff *buff, void *parameter)
{
    rt_kprintf("%s\n", __FUNCTION__);
    if ((buff != RT_NULL) && (buff->len == sizeof(struct rt_wlan_info)))
    {
        rt_kprintf("ssid : %s \n", ((struct rt_wlan_info *)buff->data)->ssid.val);
    }
}

static void
wifi_connect_fail_callback(int event, struct rt_wlan_buff *buff, void *parameter)
{
    rt_kprintf("%s\n", __FUNCTION__);
    if ((buff != RT_NULL) && (buff->len == sizeof(struct rt_wlan_info)))
    {
        rt_kprintf("ssid : %s \n", ((struct rt_wlan_info *)buff->data)->ssid.val);
    }
}
rt_err_t wlan_connect_init(void)
{
    rt_wlan_set_mode(RT_WLAN_DEVICE_STA_NAME, RT_WLAN_STATION);
    rt_wlan_config_autoreconnect(RT_TRUE);
    // net_ready = rt_sem_create("net_ready", 0, RT_IPC_FLAG_PRIO);
    rt_wlan_register_event_handler(RT_WLAN_EVT_READY,
    wifi_ready_callback, RT_NULL);
    rt_wlan_register_event_handler(RT_WLAN_EVT_STA_CONNECTED,
    wifi_connect_callback, RT_NULL);
    rt_wlan_register_event_handler(RT_WLAN_EVT_STA_DISCONNECTED,
    wifi_disconnect_callback, RT_NULL);
    rt_wlan_register_event_handler(RT_WLAN_EVT_STA_CONNECTED_FAIL,
    wifi_connect_fail_callback, RT_NULL);
}
rt_err_t wlan_connect(void)
{

    system(wlan_ssid);
    system(wlan_password);
    return 0;
}
rt_err_t wlan_connect_close(void)
{
    rt_err_t result = RT_EOK;
    rt_wlan_unregister_event_handler(RT_WLAN_EVT_READY);
    // rt_sem_delete(net_ready);
    rt_kprintf("wifi disconnect test!\n");
    result = rt_wlan_disconnect();
    if (result != RT_EOK)
    {
        rt_kprintf("disconnect failed\n");
        return result;
    }
    rt_kprintf("disconnect success\n");
}
int wlan_connect_thread_entry(void )
{
    wlan_connect_init();
    wlan_connect();
}
INIT_WIFI_EXPORT(wlan_connect_thread_entry);
