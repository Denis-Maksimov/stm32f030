#include "Sys_mgr.h"
//-----------------------------------------------------------------------


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
 * Тяжёлая ошибка, к примеру "Segmentation fault"
 * 
*************************************************/
void hard_fault(){
    while(1){
         //  wait(150000);
        for(volatile int i=0;i<15000;i++);

        REGISTER(GPIOC|GPIOx_ODR) ^= (1<<13);

        USART_sendString("Hard Fault!");
    }
}

//---------------------------------------------------




/*********************************************
 *  \brief Reset the same as with the button 
 * *******************************************/
void _RST(void){
  REGISTER(SCB_Base|SCB_AIRCR)= AIRCR_KEY | AIRCR_SYSRESETREQ;
}// Reset - как с кнопки


//----------------------------------------------------

#define U_THREAD_TIMEOUT 200
int desv[];
int desc;

// TODO: Это ещё пока не работает
void SysTick_Handler(void){
     volatile void* stack_ptr=0;
     __asm__ volatile( 
       "//-- Assembly inline --	\n\
	mrs psp,r0;		\n\
	movs r0,[%0];		\n\
	//-- End of inline -- "
	   :"=r"(stack_ptr)  // --> выход 
	   :"r"(stack_ptr)   // <-- вход
	   :"r0" );

    sys_ticks++;
    REGISTER(GPIOC|GPIOx_ODR) ^= (1<<13);
    while (!(REGISTER(SysTick_BASE|SysTick_CTRL)&SysTick_COUNTFLAG));
    
    /***********
     * Меняем контекст, тааак... надо подумать как
     * 1) нужно сохранить контекст прерванного потока
     * 2) загрузить контекст следующего потока
     *
     *
     * *******/

    return;
}

int u_thread_create(u_thread_t* tid, u_thread_attr_t attr, void* (*thread_handler)(void*), void* argv ){
	
	

	
	return 0; //-->success
}

//----------------------------------------------------


void u_thread_exit(void);


//----------------------------------------------------


void u_thread_join(void);


//----------------------------------------------------


void mutex_lock(void){
    ///TODO:
}


//----------------------------------------------------


void mutex_unlock(void){
    ///TODO:   
}


//----------------------------------------------------

