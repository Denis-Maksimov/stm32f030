#include "Sys_mgr.h"

extern void SysTick_Handler(){

    int* sys_ticks=(int*)0x20000000;
    *sys_ticks=(*sys_ticks)+1;
    REGISTER(GPIOC|GPIOx_ODR) ^= (1<<14);
    while (!(REGISTER(SysTick_BASE|SysTick_CTRL)&SysTick_COUNTFLAG));
    return;
}

void SysTick_init(int period){
    ///TODO: check sys clock

    REGISTER(SysTick_BASE|SysTick_LOAD)=period;
    REGISTER(SysTick_BASE|SysTick_CTRL)=SysTick_ENABLE|SysTick_TICKINT;
    asm("cpsie i");

}
        
