/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2021-10-18     Meco Man      First version
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include <rtconfig.h>

#define LV_COLOR_DEPTH          16
#define LV_COLOR_16_SWAP 0
#define LV_COLOR_SCREEN_TRANSP 0
#define LV_COLOR_MIX_ROUND_OFS 0
#define LV_COLOR_CHROMA_KEY lv_color_hex(0x00ff00)         /*pure green*/
#define LV_MEM_BUF_MAX_NUM 8
#define LV_MEMCPY_MEMSET_STD 0
#define LV_USE_PERF_MONITOR     0
#define LV_MEM_SIZE (8U * 512U)
#define MY_DISP_HOR_RES          240
#define MY_DISP_VER_RES          240

#define LV_FONT_GEN_JYUU_GOTHIC_NEW_14 1
#define LV_FONT_MONTSERRAT_24 1


#ifdef PKG_USING_LV_MUSIC_DEMO
/* music player demo */
#define LV_HOR_RES_MAX              MY_DISP_HOR_RES
#define LV_VER_RES_MAX              MY_DISP_VER_RES
#define LV_USE_DEMO_RTT_MUSIC       1
#define LV_DEMO_RTT_MUSIC_AUTO_PLAY 1
#define LV_FONT_MONTSERRAT_12       1
#define LV_FONT_MONTSERRAT_16       1
#define LV_COLOR_SCREEN_TRANSP      1
#endif

#endif
