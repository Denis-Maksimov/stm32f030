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

const unsigned short indicator[]={ind0,ind1,ind2,ind3,ind4,
ind5,ind6,ind7,ind8,ind9,indA,indB,indC,indD,indE,indF};
int i=0;

void main(){        
    	//clock();		//настройка частоты на 72 МГц
    	USART_init();		//Настройка USART
    	GPIO_init(); 		//Настройка пинов
        ADC_init();
        int* sys_ticks=(int*)0x20000000;
        SysTick_init(1000);
    	// REGISTER(SysTick_BASE|SysTick_LOAD)=_uSEC;
    	// REGISTER(SysTick_BASE|SysTick_CTRL)=SysTick_ENABLE|SysTick_TICKINT;
    	// asm("cpsie i");
        char buf[11];

    volatile register int last_time=0;
	while(1){

    //------- Импульс 10 мкс ------------------
      REGISTER(GPIOB|GPIOx_BSRR) = (1<<10);
        //ждём 10 мкс
      last_time=(*sys_ticks);
        while (((*sys_ticks)-last_time)<2);
        REGISTER(GPIOB|GPIOx_BRR) = (1<<10);

    //------- Ждём эхо от датчика ------------------
        while (!(REGISTER(GPIOB|GPIOx_IDR)&(1<<11)));//ждём пока нет эхо
        last_time=*sys_ticks;
        while (REGISTER(GPIOB|GPIOx_IDR)&(1<<11));//ждём пока есть эхо
        last_time=*sys_ticks-last_time;
        //intToStr(last_time,buf);
        USART_sendString(buf);
        //asm("wfi");
        USART_sendStringi((char*)sys_ticks,4);
        //USART_sendString("\r\n");
        asm("wfi");

        }
    asm("b hard_fault");

}

// -----------------------------------------------------------------
// void SysTick_Handler(){

//     int* sys_ticks=(int*)0x20000000;
//     *sys_ticks=(*sys_ticks)+1;
//     REGISTER(GPIOC|GPIOx_ODR) ^= (1<<14);
//     while (!(REGISTER(SysTick_BASE|SysTick_CTRL)&SysTick_COUNTFLAG));
//     return;
// }

void hard_fault(){
    while(1){
        REGISTER(GPIOC|GPIOx_ODR) ^= (1<<14);
        USART_sendString("Hard Fault!");
        wait(150000);
    }
}




//---------------------------------------------END--------------------------------------------------------------------

