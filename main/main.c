#include "main.h"
#include "Sys_mgr.h"
#define sys_clock  8000000
#define msec    1000
#define _uSEC   10 //микросекунд на цикл



inline void off(void){
    REGISTER(GPIOC|GPIOx_BRR) = (1<<13);
}

inline void on(void){
    REGISTER(GPIOC|GPIOx_BSRR) = (1<<13);
}

//const unsigned short indicator[]={ind0,ind1,ind2,ind3,ind4,
//ind5,ind6,ind7,ind8,ind9,indA,indB,indC,indD,indE,indF};

void main(){        

        RCC_reset();
    	USART_init();		//Настройка USART
    	GPIO_init(); 		//Настройка пинов
        set_clock_HSE();
      //  ADC_init();
        // int* sys_ticks=(int*)0x20000000;
        SysTick_init(1000000);//100 000

        char buf[11];

    volatile register int last_time=0;
	while(1){


        intToStr(sys_ticks,buf);
    //     USART_sendChr('!');
        USART_sendString(buf);
        //asm("wfi");
     //   USART_sendStringi((char*)sys_ticks,4);
        USART_sendString("\r\n");
        asm("wfi");

        }
    asm("b hard_fault");

}




//---------------------------------------------END--------------------------------------------------------------------

