/*
 * Copyright (c) 2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-06     Supperthomas first version
 * 2023-12-03     Meco Man     support nano version
 */

#include <board.h>
#include <rtthread.h>
#include <drv_gpio.h>
#ifndef RT_USING_NANO
#include <rtdevice.h>
#endif /* RT_USING_NANO */

#include "lv_port_disp.h"
#define WIFI_CS GET_PIN(F, 10)
void WIFI_CS_PULL_DOWN(void)
{
    rt_pin_mode(WIFI_CS,PIN_MODE_OUTPUT);
    rt_pin_write(WIFI_CS, PIN_LOW);
}
INIT_BOARD_EXPORT(WIFI_CS_PULL_DOWN);

int main(void)
{
    rt_thread_mdelay(1000);
    extern void lvgl_thread_entry(void *parameter);
    lvgl_thread_entry(NULL);

}