#ifndef _SRC_HW_DEF_H_
#define _SRC_HW_DEF_H_

#ifdef __cplusplus
  extern "C"{
#endif

#include "bsp.h"

#define _DEF_FIRMWATRE_VERSION    "V240729R1"
#define _DEF_BOARD_NAME           "RP2040_APP"


#if (FREERTOS_USE == 1)
  #define _HW_DEF_RTOS_MEM_SIZE(x)              ((x)/1)


  #define _HW_DEF_RTOS_THREAD_PRI_MAIN          ( tskIDLE_PRIORITY + 1UL )
  #define _HW_DEF_RTOS_THREAD_PRI_CLI           ( tskIDLE_PRIORITY + 1UL )
  // #define _HW_DEF_RTOS_THREAD_PRI_TVWEB         ( tskIDLE_PRIORITY + 1UL )

  #define _HW_DEF_RTOS_THREAD_MEM_MAIN          _HW_DEF_RTOS_MEM_SIZE( 1*2048)
  #define _HW_DEF_RTOS_THREAD_MEM_CLI           _HW_DEF_RTOS_MEM_SIZE( 2*2048)
  // #define _HW_DEF_RTOS_THREAD_MEM_TVWEB         _HW_DEF_RTOS_MEM_SIZE( 1*1024)
#endif


#define _USE_HW_FLASH
#define _USE_HW_RESET
#define _USE_HW_RTOS


#define _USE_HW_LED
#define      HW_LED_MAX_CH          1

#define _USE_HW_UART
#define      HW_UART_MAX_CH         2

#define _USE_HW_GPIO
#define      HW_GPIO_MAX_CH         6

#define _USE_HW_CLI
#define      HW_CLI_CMD_LIST_MAX    16
#define      HW_CLI_CMD_NAME_MAX    16
#define      HW_CLI_LINE_HIS_MAX    4
#define      HW_CLI_LINE_BUF_MAX    64

#define _USE_HW_LOG
#define      HW_LOG_CH              _DEF_UART1
#define      HW_LOG_BOOT_BUF_MAX    1024
#define      HW_LOG_LIST_BUF_MAX    1024

#define _USE_HW_CMD
#define      HW_CMD_MAX_DATA_LENGTH (1024+8)

#define _USE_HW_SPI
#define      HW_SPI_MAX_CH          1

#define _USE_HW_W25QXX 
#define     HW_W25QXX_MAX_CH        1

#define _USE_HW_FS
#define      HW_FS_MAX_SIZE         (2*1024*1024)
// #define      HW_FS_FLASH_OFFSET     0x10100000w

#define _USE_HW_I2C 
#define HW_I2C_MAX_CH               1

#define _USE_HW_SC16IS740_



#define FLASH_BOOT_SIZE             (128*1024)           


#define FLASH_IMAGE_FW              0x10020000
#define FLASH_IMAGE_UPDATE          0x10200000
#define FLASH_IMAGE_SIZE            (2*1024*1024)

#define FLASH_ADDR_START            0x10020000
#define FLASH_ADDR_END              (FLASH_ADDR_START + (2048-128)*1024)


#define FLASH_OFFSET_FW_TAG         0x00000000
#define FLASH_OFFSET_FW_START       0x00000400
#define FLASH_OFFSET_FW_VECTOR      0x00000500
#define FLASH_OFFSET_FW_VER         0x00000800

#define FLASH_ADDR_FW_TAG           (FLASH_IMAGE_FW + FLASH_OFFSET_FW_TAG   )
#define FLASH_ADDR_FW_START         (FLASH_IMAGE_FW + FLASH_OFFSET_FW_START )
#define FLASH_ADDR_FW_VECTOR        (FLASH_IMAGE_FW + FLASH_OFFSET_FW_VECTOR)
#define FLASH_ADDR_FW_VER           (FLASH_IMAGE_FW + FLASH_OFFSET_FW_VER   )

#define FLASH_ADDR_UPDATE_TAG       (FLASH_IMAGE_UPDATE + FLASH_OFFSET_FW_TAG   )
#define FLASH_ADDR_UPDATE_START     (FLASH_IMAGE_UPDATE + FLASH_OFFSET_FW_START )
#define FLASH_ADDR_UPDATE_VECTOR    (FLASH_IMAGE_UPDATE + FLASH_OFFSET_FW_VECTOR)
#define FLASH_ADDR_UPDATE_VER       (FLASH_IMAGE_UPDATE + FLASH_OFFSET_FW_VER   )








#ifdef __cplusplus
}
#endif

#endif