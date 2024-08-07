#ifndef SRC_COMMON_ERR_CODE_H_
#define SRC_COMMON_ERR_CODE_H_
#ifdef __cplusplus
  extern "C" {
#endif


#define OK                            0
#define ERR_MEMORY                    1
#define ERR_FULL                      2
#define ERR_EMPTY                     3
#define ERR_NULL                      4
#define ERR_INVAILD_INDEX             5

// #define ERR_BOOT_WRONG_CMD            10
// #define ERR_BOOT_LED                  11
// #define ERR_BOOT_FLASH_ERASE          12
// #define ERR_BOOT_WRONG_RANGE          13
// #define ERR_BOOT_FLASH_WRITE          14
// #define ERR_BOOT_FLASH_READ           15
// #define ERR_BOOT_BUF_OVF              16
// #define ERR_BOOT_INVALID_FW           17
// #define ERR_BOOT_FW_CRC               18
// #define ERR_BOOT_JUMP_TO_FW           19
// #define ERR_BOOT_INVALID_TAG          20

#define ERR_BOOT_WRONG_CMD            0x000A
#define ERR_BOOT_LED                  0x000B
#define ERR_BOOT_FLASH_ERASE          0x000C
#define ERR_BOOT_WRONG_RANGE          0x000D
#define ERR_BOOT_FLASH_WRITE          0x000E
#define ERR_BOOT_BUF_OVF              0x000F
#define ERR_BOOT_INVALID_FW           0x0010
#define ERR_BOOT_FW_CRC               0x0011
#define ERR_BOOT_JUMP_TO_FW           0x0012
#define ERR_BOOT_TAG_MAGIC            0x0013
#define ERR_BOOT_TAG_SIZE             0x0014
#define ERR_BOOT_FLASH_READ           0x0015


#define ERR_CMD_MAX_LENGTH            0x0020
#define ERR_CMD_CHECKSUM              0x0021
#define ERR_CMD_RX_TIMEOUT            0x0022
#define ERR_CMD_NO_CMD                0x0023


#ifdef __cplusplus
  }
#endif



#endif