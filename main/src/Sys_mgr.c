#include "Sys_mgr.h"
//-----------------------------------------------------------------------

void SysTick_Handler(void){

    sys_ticks++;
 //   *sys_ticks=(*sys_ticks)+1;
    REGISTER(GPIOC|GPIOx_ODR) ^= (1<<13);
    while (!(REGISTER(SysTick_BASE|SysTick_CTRL)&SysTick_COUNTFLAG));
    return;
}
//-----------------------------------------------------------------------
void SysTick_init(int period){
    ///TODO: check sys clock

    REGISTER(SysTick_BASE|SysTick_LOAD)=period;
    REGISTER(SysTick_BASE|SysTick_CTRL)=SysTick_ENABLE|SysTick_TICKINT;
    asm("cpsie i");

}
//-----------------------------------------------------------------------
/************************************************
 * \brief Hard Fault handler
 * Сюда мы свалимся, если обратимся к несуществующему региону
 * памяти, или прыгнем не в ту степь (в неисполняемую память)
 * к примеру:
 * 
 * ldr r0, =RCC_BASE   //load in register r0 value 0x40021000
 * bx  r0              //branch to addres in register r0
 * <HARD FAULT!!>
 * 
 * или что-то ещё с камнем произойдёт
*************************************************/
void hard_fault(){
    while(1){
         //  wait(150000);
        for(volatile int i=0;i<15000;i++);

        REGISTER(GPIOC|GPIOx_ODR) ^= (1<<14);

        USART_sendString("Hard Fault!");
    }
}

//--------------------------------------------------- * 
 * same to segmentation fault --------------------

// big plans
void thread(void){
    ///TODO:
}
void mutex_lock(void){
    ///TODO:
}
void mutex_unlock(void){
    ///TODO:   
}