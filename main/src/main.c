#include "main.h"
#define sys_clock  8000000
#define msec    1000
#define _uSEC   200000 //микросекунд на цикл




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


    	REGISTER(SysTick_BASE|SysTick_LOAD)=_uSEC;
    	REGISTER(SysTick_BASE|SysTick_CTRL)=SysTick_ENABLE|SysTick_TICKINT;
    	asm("cpsie i");



	while(1){
        REGISTER(GPIOB|GPIOx_ODR)=(unsigned int)(indicator[i]);
        (i==15)?(i=0):(i++);
        asm("wfi");
        //REGISTER(GPIOC|GPIOx_ODR) ^= (1<<13);
        ADC_start_conversion();

        ADC_read();
        USART_sendChr('-');
        asm("wfi");
        ADC_read();
        USART_sendString("\r\n");
  

        }
    asm("b hard_fault");

}

// -----------------------------------------------------------------
void SysTick_Handler(){
    REGISTER(GPIOC|GPIOx_ODR) ^= (1<<14);
    while (!(REGISTER(SysTick_BASE|SysTick_CTRL)&SysTick_COUNTFLAG));
    return;
}

void hard_fault(){
    while(1){
        REGISTER(GPIOC|GPIOx_ODR) ^= (1<<14);
        USART_sendString("Hard Fault!");
        wait(150000);
    }
}




//---------------------------------------------END--------------------------------------------------------------------

