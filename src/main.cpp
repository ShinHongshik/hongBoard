
#include "main.h"

#if ( FREERTOS_USE == 1 )
	static void mainThread(void *param);
#endif 


int main() {
	hwInit();
#if ( FREERTOS_USE == 1 )
    xTaskCreate(mainThread, "mainThread", _HW_DEF_RTOS_THREAD_MEM_MAIN, NULL, _HW_DEF_RTOS_THREAD_PRI_MAIN, NULL);
    vTaskStartScheduler();
#else 
	apInit();
	apMain();
#endif
	return 0;
}

#if ( FREERTOS_USE == 1 )
	void mainThread(void *params)
	{
		(void)params;

		apInit();
		apMain();
	}
#endif 

