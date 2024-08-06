#ifndef SRC_AP_DEF_H_
#define SRC_AP_DEF_H_

#include <array>
#include "hw.h"

// typedef struct {
//     uint8_t cmd_type;
//     uint8_t cmd_char[2];// last 2 byte
// }queue_type;


// typedef struct 
// {
//   bool redWhiteStartReq;
//   uint8_t redToggleLed;
//   uint8_t whiteToggleLed;
// }RED_WHITE_INDICATE_LED_t;

// extern RED_WHITE_INDICATE_LED_t redWhiteIndicate;

// TODO: Logger severity level
#define AP_LOGGER_ENABLE false
#if (AP_LOGGER_ENABLE)
  #define AP_LOGGER_PRINT(...)  cliPrintf(__VA_ARGS__)
#else
  #define AP_LOGGER_PRINT(...)
#endif


const bool DHCP_ENABLED = true; 
const std::array<uint8_t, 6> MAC_ADDRESS = { 0x00 , 0x08 , 0xDC, 0x12 , 0x34 , 0x56 };
const uint16_t SOCKET_PORT_DEFAULT = 4444;

#endif /* SRC_AP_AP_DEF_H_ */