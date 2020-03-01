#include "Sys_mgr.h"



/************************************************
 * \brief Hard Fault handler
 * Тяжёлая ошибка, к примеру "Segmentation fault"
 * 
*************************************************/
void hard_fault(){
    while(1){
         //  wait(150000);
        for(volatile int i=0;i<500000;i++);

        REGISTER(GPIOC|GPIOx_ODR) ^= (1<<13);

        USART_sendString("\r\nHard Fault!\n");

		if(REGISTER(SCB_Base+SCB_HFSR)&SCB_HFSR_VECTTBL)
			USART_sendString("-Vec_tabl\n\r");

		if(REGISTER(SCB_Base+SCB_HFSR)&SCB_HFSR_FORCED)
			USART_sendString("-forced\n\r");
        puts("\r\n Flt Flags: ");
		debug(SCB_Base+SCB_CFSR);
        puts("\r\n BF adr: ");
		debug(SCB_Base+SCB_BFAR);
    }
}

//---------------------------------------------------
void bus_fault(){
	while(1){
         //  wait(150000);
        for(volatile int i=0;i<500000;i++);

        REGISTER(GPIOC|GPIOx_ODR) ^= (1<<13);

        puts("Bus Fault!\n");

		if(REGISTER(SCB_Base+SCB_CFSR)&SCB_CFSR_IBUSERR)
			puts("-instruction BF\r\n");

		if(REGISTER(SCB_Base+SCB_CFSR)&SCB_CFSR_IMPRECISERR)
			puts("-imprecise data BF\r\n");

		if(REGISTER(SCB_Base+SCB_CFSR)&SCB_CFSR_PRECISERR)
			puts("-precise data BF\r\n");

		debug(SCB_Base+SCB_BFAR);
    }



}

