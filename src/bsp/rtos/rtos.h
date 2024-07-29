#ifndef RTOS_H_
#define RTOS_H_

#include "def.h"

// CMakeLists.txt
#if ( FREERTOS_USE == 1 )
    #include "FreeRTOS.h"
    #include "task.h"
    #include "semphr.h"
#endif

#endif