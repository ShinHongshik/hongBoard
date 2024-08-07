#ifndef SRC_HW_H_
#define SRC_HW_H_

#ifdef __cplusplus
  extern "C" {
#endif

#include "hw_def.h"

#include "cli.h"
#include "reset.h"
#include "uart.h"
#include "led.h"
#include "i2c.h"
#include "cmd_can.h"
#include "flash.h"
#include "reset.h"
#include "util.h"


bool hwInit(void);

#ifdef __cplusplus
}
#endif

#endif
