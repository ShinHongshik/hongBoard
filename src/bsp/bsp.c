#include "bsp.h"

#if 0
void SysTick_Handler(void)
{

}
#endif

bool bspInit(void)
{
  set_sys_clock_khz(250000, true); // overclock the rp2040 to 250mhz
  // set_sys_clock_khz(133000, true); // overclock the rp2040 to 250mhz
  
  stdio_init_all();
#if ( FREERTOS_USE == 1 )     

#else
  SysTick_Config(SystemCoreClock / 1000U);
#endif
  __enable_irq();

  return true;
}

void bspDeInit(void)
{
   __disable_irq();

  // Disable Interrupts
  //
  for (int i=0; i<1; i++)
  {
    NVIC->ICER[i] = 0xFFFFFFFF;
    __DSB();
    __ISB();
  }
  SysTick->CTRL = 0;
}

void delay(uint32_t time_ms)
{
#if (FREERTOS_USE == 1) // CMakeLists.txt defined 
  if (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING)
  {
    vTaskDelay(time_ms);
  }
  else
  {
    sleep_ms(time_ms);
  }
#else
    sleep_ms(time_ms);
#endif
}

void delay_Us(uint32_t us)
{
  volatile uint32_t i;

  for (i=0; i<us*1000; i++)
  {

  }
}


uint32_t millis(void)
{  
  return to_ms_since_boot(get_absolute_time());
}

uint32_t micros(void)
{
  return to_us_since_boot(get_absolute_time());
}