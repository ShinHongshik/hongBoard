#ifndef SRC_BSP_H_
#define SRC_BSP_H_

#include "def.h"

#ifdef __cplusplus
  extern "C" {
#endif

#include "RP2040.h"
#include "hardware/clocks.h"
#include "hardware/flash.h"
#include "pico/stdlib.h"
#include "pico/platform.h"
#include "hardware/adc.h"

#if (FREERTOS_USE == 1)
  #include "rtos.h"
#endif

bool bspInit(void);
void bspDeInit(void);

void delay(uint32_t time_ms);
void delay_Us(uint32_t us);

uint32_t millis(void);
uint32_t micros(void);


// void logPrintf(const char *fmt, ...);


#ifdef __cplusplus
}
#endif

#endif