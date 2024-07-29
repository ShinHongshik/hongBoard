#include "ap.h"

static void cliThread(void *args);




void apInit(void)
{
  cliOpen(_DEF_UART1, 115200);
  uartOpen(_DEF_UART2, 115200);

#if ( FREERTOS_USE == 1 )
  xTaskCreate(cliThread, "cliThread", _HW_DEF_RTOS_THREAD_MEM_CLI , NULL , _HW_DEF_RTOS_THREAD_PRI_CLI , NULL );
#endif

#ifdef _USE_HW_CLI
  // cliAdd("test", cliTest);
#endif
}

void apMain(void)
{
  while(true)
  {
    cliPrintf("ejkalwejrk;lwaejk;lr\r\n");
    delay(100);
  }
}

static void cliThread(void *args)
{

  while(true)
  {
    cliMain();    

    delay(1);
  }
}

volatile unsigned long tickHookCnt;

void vApplicationTickHook(void)
{
  tickHookCnt++;
}