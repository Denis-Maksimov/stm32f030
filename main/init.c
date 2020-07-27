#include "init.h"

// #define sys_clock  8000000
// #define msec    1000
// #define _uSEC   10 //микросекунд на цикл

// inline void off(void){
//     REGISTER(GPIOC|GPIOx_BRR) = (1<<13);
// }

// inline void on(void){
//     REGISTER(GPIOC|GPIOx_BSRR) = (1<<13);
// }

char USART_buffer[10];
struct TIMx_chx handl;

static void GPIO_init(void){

    //Настройка пинов
    pin_init(13,'C',PUSH_PULL_OUTPUT_2MHZ);

}


void init(void){

    RCC_reset();
    USART_init(USART_buffer,10);		//Настройка USART
    
    PWM_output_mode(&handl,1,'A');  // Настройка ШИМ
    PWM_setup(&handl, 1000, 500);   // Настройка ШИМ
    
    GPIO_init(); 		// Настройка пинов
    set_clock_HSE();    // установка 72 МГц
    NVIC_init();        // включение пользовательских прерываний
    SysTick_init();     // запуск часов


}







