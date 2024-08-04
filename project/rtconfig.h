#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

#define SOC_STM32F407ZG
#define BOARD_STM32F407_SPARK

/* RT-Thread Kernel */

#define RT_NAME_MAX 8
#define RT_CPUS_NR 1
#define RT_ALIGN_SIZE 8
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_USING_HOOK
#define RT_HOOK_USING_FUNC_PTR
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 1024

/* kservice optimization */

/* end of kservice optimization */

/* klibc optimization */

/* end of klibc optimization */
#define RT_USING_DEBUG
#define RT_DEBUGING_ASSERT
#define RT_DEBUGING_COLOR
#define RT_DEBUGING_CONTEXT
#define RT_USING_OVERFLOW_CHECK

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE
/* end of Inter-Thread communication */

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_SMALL_MEM
#define RT_USING_SMALL_MEM_AS_HEAP
#define RT_USING_HEAP
/* end of Memory Management */
#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart1"
#define RT_VER_NUM 0x50200
#define RT_BACKTRACE_LEVEL_MAX_NR 32
/* end of RT-Thread Kernel */
#define RT_USING_HW_ATOMIC
#define RT_USING_CPU_FFS
#define ARCH_ARM
#define ARCH_ARM_CORTEX_M
#define ARCH_ARM_CORTEX_M4

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 6144
#define RT_MAIN_THREAD_PRIORITY 10
#define RT_USING_MSH
#define RT_USING_FINSH
#define FINSH_USING_MSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 2048
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_CMD_SIZE 80
#define MSH_USING_BUILT_IN_COMMANDS
#define FINSH_USING_DESCRIPTION
#define FINSH_ARG_MAX 10
#define FINSH_USING_OPTION_COMPLETION

/* DFS: device virtual file system */

#define RT_USING_DFS
#define DFS_USING_POSIX
#define DFS_USING_WORKDIR
#define DFS_FD_MAX 16
#define RT_USING_DFS_V1
#define DFS_FILESYSTEMS_MAX 4
#define DFS_FILESYSTEM_TYPES_MAX 4
#define RT_USING_DFS_DEVFS
/* end of DFS: device virtual file system */

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_UNAMED_PIPE_NUMBER 64
#define RT_USING_SYSTEM_WORKQUEUE
#define RT_SYSTEM_WORKQUEUE_STACKSIZE 2048
#define RT_SYSTEM_WORKQUEUE_PRIORITY 23
#define RT_USING_SERIAL
#define RT_USING_SERIAL_V1
#define RT_SERIAL_USING_DMA
#define RT_SERIAL_RB_BUFSZ 64
#define RT_USING_I2C
#define RT_USING_I2C_BITOPS
#define RT_USING_PWM
#define RT_USING_RTC
#define RT_USING_SOFT_RTC
#define RT_USING_SPI
#define RT_USING_WIFI
#define RT_WLAN_DEVICE_STA_NAME "wlan0"
#define RT_WLAN_DEVICE_AP_NAME "wlan1"
#define RT_WLAN_SSID_MAX_LENGTH 32
#define RT_WLAN_PASSWORD_MAX_LENGTH 32
#define RT_WLAN_DEV_EVENT_NUM 2
#define RT_WLAN_MANAGE_ENABLE
#define RT_WLAN_SCAN_WAIT_MS 10000
#define RT_WLAN_CONNECT_WAIT_MS 10000
#define RT_WLAN_SCAN_SORT
#define RT_WLAN_MSH_CMD_ENABLE
#define RT_WLAN_JOIN_SCAN_BY_MGNT
#define RT_WLAN_AUTO_CONNECT_ENABLE
#define AUTO_CONNECTION_PERIOD_MS 2000
#define RT_WLAN_CFG_ENABLE
#define RT_WLAN_CFG_INFO_MAX 3
#define RT_WLAN_PROT_ENABLE
#define RT_WLAN_PROT_NAME_LEN 8
#define RT_WLAN_PROT_MAX 2
#define RT_WLAN_DEFAULT_PROT "lwip"
#define RT_WLAN_PROT_LWIP_ENABLE
#define RT_WLAN_PROT_LWIP_NAME "lwip"
#define RT_WLAN_WORK_THREAD_ENABLE
#define RT_WLAN_WORKQUEUE_THREAD_NAME "wlan"
#define RT_WLAN_WORKQUEUE_THREAD_SIZE 2048
#define RT_WLAN_WORKQUEUE_THREAD_PRIO 15
#define RT_USING_PIN
/* end of Device Drivers */

/* C/C++ and POSIX layer */

/* ISO-ANSI C layer */

/* Timezone and Daylight Saving Time */

#define RT_LIBC_USING_LIGHT_TZ_DST
#define RT_LIBC_TZ_DEFAULT_HOUR 8
#define RT_LIBC_TZ_DEFAULT_MIN 0
#define RT_LIBC_TZ_DEFAULT_SEC 0
/* end of Timezone and Daylight Saving Time */
/* end of ISO-ANSI C layer */

/* POSIX (Portable Operating System Interface) layer */

#define RT_USING_POSIX_FS
#define RT_USING_POSIX_POLL
#define RT_USING_POSIX_SELECT
#define RT_USING_POSIX_SOCKET

/* Interprocess Communication (IPC) */


/* Socket is in the 'Network' category */

/* end of Interprocess Communication (IPC) */
/* end of POSIX (Portable Operating System Interface) layer */
/* end of C/C++ and POSIX layer */

/* Network */

#define RT_USING_SAL
#define SAL_INTERNET_CHECK

/* Docking with protocol stacks */

#define SAL_USING_LWIP
/* end of Docking with protocol stacks */
#define SAL_USING_POSIX
#define RT_USING_NETDEV
#define NETDEV_USING_IFCONFIG
#define NETDEV_USING_PING
#define NETDEV_USING_NETSTAT
#define NETDEV_USING_AUTO_DEFAULT
#define NETDEV_IPV4 1
#define NETDEV_IPV6 0
#define RT_USING_LWIP
#define RT_USING_LWIP203
#define RT_USING_LWIP_VER_NUM 0x20003
#define RT_LWIP_MEM_ALIGNMENT 4
#define RT_LWIP_IGMP
#define RT_LWIP_ICMP
#define RT_LWIP_DNS
#define RT_LWIP_DHCP
#define IP_SOF_BROADCAST 1
#define IP_SOF_BROADCAST_RECV 1

/* Static IPv4 Address */

#define RT_LWIP_IPADDR "192.168.1.30"
#define RT_LWIP_GWADDR "192.168.1.1"
#define RT_LWIP_MSKADDR "255.255.255.0"
/* end of Static IPv4 Address */
#define RT_LWIP_UDP
#define RT_LWIP_TCP
#define RT_LWIP_RAW
#define RT_MEMP_NUM_NETCONN 8
#define RT_LWIP_PBUF_NUM 16
#define RT_LWIP_RAW_PCB_NUM 4
#define RT_LWIP_UDP_PCB_NUM 4
#define RT_LWIP_TCP_PCB_NUM 4
#define RT_LWIP_TCP_SEG_NUM 40
#define RT_LWIP_TCP_SND_BUF 8196
#define RT_LWIP_TCP_WND 8196
#define RT_LWIP_TCPTHREAD_PRIORITY 10
#define RT_LWIP_TCPTHREAD_MBOX_SIZE 8
#define RT_LWIP_TCPTHREAD_STACKSIZE 1024
#define RT_LWIP_ETHTHREAD_PRIORITY 12
#define RT_LWIP_ETHTHREAD_STACKSIZE 1024
#define RT_LWIP_ETHTHREAD_MBOX_SIZE 8
#define LWIP_NETIF_STATUS_CALLBACK 1
#define LWIP_NETIF_LINK_CALLBACK 1
#define RT_LWIP_NETIF_NAMESIZE 6
#define SO_REUSE 1
#define LWIP_SO_RCVTIMEO 1
#define LWIP_SO_SNDTIMEO 1
#define LWIP_SO_RCVBUF 1
#define LWIP_SO_LINGER 0
#define LWIP_NETIF_LOOPBACK 0
#define RT_LWIP_USING_PING
/* end of Network */

/* Memory protection */

/* end of Memory protection */

/* Utilities */

/* end of Utilities */

/* Using USB legacy version */

/* end of Using USB legacy version */
/* end of RT-Thread Components */

/* RT-Thread online packages */

/* IoT - internet of things */

#define PKG_USING_WEBCLIENT
#define WEBCLIENT_NOT_USE_TLS
#define PKG_USING_WEBCLIENT_V220
#define PKG_WEBCLIENT_VER_NUM 0x20200

/* Wi-Fi */

/* Marvell WiFi */

/* end of Marvell WiFi */

/* Wiced WiFi */

/* end of Wiced WiFi */
#define PKG_USING_RW007
#define PKG_USING_RW007_V210
#define RW007_USING_STM32_DRIVERS
#define RW007_SPI_MAX_HZ 30000000
#define RW007_SPI_BUS_NAME "spi2"
#define RW007_CS_PIN 90
#define RW007_BOOT0_PIN 29
#define RW007_BOOT1_PIN 90
#define RW007_INT_BUSY_PIN 107
#define RW007_RST_PIN 111

/* CYW43012 WiFi */

/* end of CYW43012 WiFi */

/* BL808 WiFi */

/* end of BL808 WiFi */

/* CYW43439 WiFi */

/* end of CYW43439 WiFi */
/* end of Wi-Fi */
#define PKG_USING_NETUTILS
#define PKG_NETUTILS_NTP
#define NTP_USING_AUTO_SYNC
#define NTP_AUTO_SYNC_FIRST_DELAY 30
#define NTP_AUTO_SYNC_PERIOD 3600
#define NETUTILS_NTP_HOSTNAME "cn.ntp.org.cn"
#define NETUTILS_NTP_HOSTNAME2 "ntp.rt-thread.org"
#define NETUTILS_NTP_HOSTNAME3 "edu.ntp.org.cn"
#define PKG_USING_NETUTILS_LATEST_VERSION
#define PKG_NETUTILS_VER_NUM 0x99999

/* IoT Cloud */

/* end of IoT Cloud */
/* end of IoT - internet of things */

/* security packages */

/* end of security packages */

/* language packages */

/* JSON: JavaScript Object Notation, a lightweight data-interchange format */

#define PKG_USING_AGILE_JSMN
#define PKG_USING_AGILE_JSMN_V101
#define PKG_AGILE_JSMN_VER_NUM 0x10001
/* end of JSON: JavaScript Object Notation, a lightweight data-interchange format */

/* XML: Extensible Markup Language */

/* end of XML: Extensible Markup Language */
/* end of language packages */

/* multimedia packages */

/* LVGL: powerful and easy-to-use embedded GUI library */

#define PKG_USING_LVGL
#define PKG_LVGL_THREAD_PRIO 20
#define PKG_LVGL_THREAD_STACK_SIZE 4096
#define PKG_LVGL_DISP_REFR_PERIOD 5
#define PKG_LVGL_USING_DEMOS
#define PKG_LVGL_USING_V080311
#define PKG_LVGL_VER_NUM 0x080311
/* end of LVGL: powerful and easy-to-use embedded GUI library */

/* u8g2: a monochrome graphic library */

/* end of u8g2: a monochrome graphic library */
/* end of multimedia packages */

/* tools packages */

/* end of tools packages */

/* system packages */

/* enhanced kernel services */

#define PKG_USING_RT_VSNPRINTF_FULL
#define PKG_VSNPRINTF_SUPPORT_DECIMAL_SPECIFIERS
#define PKG_VSNPRINTF_SUPPORT_EXPONENTIAL_SPECIFIERS
#define PKG_VSNPRINTF_SUPPORT_WRITEBACK_SPECIFIER
#define PKG_VSNPRINTF_SUPPORT_LONG_LONG
#define PKG_VSNPRINTF_CHECK_FOR_NUL_IN_FORMAT_SPECIFIER
#define PKG_VSNPRINTF_INTEGER_BUFFER_SIZE 32
#define PKG_VSNPRINTF_DECIMAL_BUFFER_SIZE 32
#define PKG_VSNPRINTF_DEFAULT_FLOAT_PRECISION 6
#define PKG_VSNPRINTF_MAX_INTEGRAL_DIGITS_FOR_DECIMAL 9
#define PKG_VSNPRINTF_LOG10_TAYLOR_TERMS 4
#define PKG_USING_RT_VSNPRINTF_FULL_LATEST_VERSION
/* end of enhanced kernel services */

/* acceleration: Assembly language or algorithmic acceleration packages */

/* end of acceleration: Assembly language or algorithmic acceleration packages */

/* CMSIS: ARM Cortex-M Microcontroller Software Interface Standard */

/* end of CMSIS: ARM Cortex-M Microcontroller Software Interface Standard */

/* Micrium: Micrium software products porting for RT-Thread */

/* end of Micrium: Micrium software products porting for RT-Thread */
/* end of system packages */

/* peripheral libraries and drivers */

/* HAL & SDK Drivers */

/* STM32 HAL & SDK Drivers */

/* end of STM32 HAL & SDK Drivers */

/* Infineon HAL Packages */

/* end of Infineon HAL Packages */

/* Kendryte SDK */

/* end of Kendryte SDK */
/* end of HAL & SDK Drivers */

/* sensors drivers */

#define PKG_USING_AHT10
#define PKG_USING_AHT10_LATEST_VERSION
/* end of sensors drivers */

/* touch drivers */

/* end of touch drivers */
/* end of peripheral libraries and drivers */

/* AI packages */

/* end of AI packages */

/* Signal Processing and Control Algorithm Packages */

/* end of Signal Processing and Control Algorithm Packages */

/* miscellaneous packages */

/* project laboratory */

/* end of project laboratory */

/* samples: kernel and components samples */

/* end of samples: kernel and components samples */

/* entertainment: terminal games and other interesting software packages */

/* end of entertainment: terminal games and other interesting software packages */
/* end of miscellaneous packages */

/* Arduino libraries */


/* Projects and Demos */

/* end of Projects and Demos */

/* Sensors */

/* end of Sensors */

/* Display */

/* end of Display */

/* Timing */

/* end of Timing */

/* Data Processing */

/* end of Data Processing */

/* Data Storage */

/* Communication */

/* end of Communication */

/* Device Control */

/* end of Device Control */

/* Other */

/* end of Other */

/* Signal IO */

/* end of Signal IO */

/* Uncategorized */

/* end of Arduino libraries */
/* end of RT-Thread online packages */
#define SOC_FAMILY_STM32
#define SOC_SERIES_STM32F4

/* Hardware Drivers Config */

/* Onboard Peripheral Drivers */

#define BSP_USING_USB_TO_USART
#define BSP_USING_SRAM
#define BSP_USING_ONBOARD_LCD
#define BSP_USING_ONBOARD_LED_MATRIX
#define BSP_USING_LVGL
#define BSP_USING_LVGL_DEMO
#define BSP_USING_RW007_WLAN
#define BSP_USING_AHT21
/* end of Onboard Peripheral Drivers */

/* On-chip Peripheral Drivers */

#define BSP_USING_GPIO
#define BSP_USING_UART
#define BSP_USING_UART1
#define BSP_USING_PWM
#define BSP_USING_PWM3
#define BSP_USING_PWM3_CH2
#define BSP_USING_PWM14
#define BSP_USING_PWM14_CH1
#define BSP_USING_SPI
#define BSP_USING_SPI2
#define BSP_USING_I2C
#define BSP_USING_I2C3
#define BSP_I2C3_SCL_PIN 64
#define BSP_I2C3_SDA_PIN 65
#define BSP_USING_EXT_FMC_IO
#define BSP_USING_FMC
/* end of On-chip Peripheral Drivers */

/* Board extended module Drivers */

/* end of Board extended module Drivers */
/* end of Hardware Drivers Config */

#endif
