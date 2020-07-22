#include "init.h"
#define sys_clock  8000000
#define msec    1000
#define _uSEC   10 //микросекунд на цикл

// inline void off(void){
//     REGISTER(GPIOC|GPIOx_BRR) = (1<<13);
// }

// inline void on(void){
//     REGISTER(GPIOC|GPIOx_BSRR) = (1<<13);
// }

char USART_buffer[256];
struct TIMx_chx handl;
void init(void){

    RCC_reset();
    USART_init(USART_buffer,256);		//Настройка USART
    
    PWM_output_mode(&handl,1,'A');
    PWM_setup(&handl, 1000, 500);
    GPIO_init(); 		//Настройка пинов
    set_clock_HSE(); // arbeitung--???
    NVIC_init();
    SysTick_init(72);//100 000


}
