#include "Sys_mgr.h"
#include "debug.h"
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



/*********************************************
 *  \brief Reset the same as with the button 
 * *******************************************/
void _RST(void){
  REGISTER(SCB_Base|SCB_AIRCR)= AIRCR_KEY | AIRCR_SYSRESETREQ;
}// Reset - как с кнопки


//----------------------------------------------------

struct Context_regs{
    uint32_t _r0;
    uint32_t _r1;
    uint32_t _r2;
    uint32_t _r3;
    uint32_t _r12;
    //sp = r15
    uint32_t _lr; //r14
    uint32_t _pc; //r15
    uint32_t _xPSR; //programm status register

};

//--------------------------------------------------------------
#define REG_xPSR

/*!
 * Hardware stack frame.
 * This is a clone of the stack frame used by NVIC
 */
typedef struct
{
   uint32_t r0;
   uint32_t r1;
   uint32_t r2;
   uint32_t r3;
   uint32_t r12;
   uint32_t lr;
   uint32_t pc;
   uint32_t psr;
}hw_stack_frame_t;

//--------------------------------------------------------------

/*!
 * Software stack frame.
 * This is a clone of the stack frame used by pkernel.
 */
typedef struct
{
   uint32_t r4;
   uint32_t r5;
   uint32_t r6;
   uint32_t r7;
   uint32_t r8;
   uint32_t r9;
   uint32_t r10;
   uint32_t r11;
}sw_stack_frame_t;

//--------------------------------------------------------------

// TODO: Это ещё пока не работает
void SysTick_Handler(void){

	

 
	

    sys_ticks++;
    REGISTER(GPIOC|GPIOx_ODR) ^= (1<<13);
    while (!(REGISTER(SysTick_BASE|SysTick_CTRL)&SysTick_COUNTFLAG));
    
   

	//-- вернёмся в прерывание PENDSVSET
	REGISTER(SCB_Base+SCB_ICSR)|=SCB_ICSR_PENDSVSET;
	__asm__ volatile( "dsb" ); // Data synchronization barrier
   __asm__ volatile( "isb" );  // Instruction synchronization barrier

    return;
}

//--------------------------------------------------------------
extern uint32_t stack;

void PendSV_Handler(void) __attribute__( ( naked ) );
void context_switch (uint32_t sp) __attribute__( ( naked ) );
uint32_t schedule(uint32_t in_ctx) __attribute__( ( naked ) );
void PendSV_Handler(void)
{
	

	// //--get context
	uint32_t sp = get_MSP();
    REGISTER(sp+20)=main_switcher;  //PC
    REGISTER(sp+24)=main_switcher; //LR

    // for (int i=0; i<32; i=i+4)
    //     {
    //         debug(sp+i);
    //     }
    
	asm volatile (
        //"ldr sp,=(0x20004FF8+32)   \n\t"
        "ldr lr, =0xFFFFFFF9 \n\t"
                   "BX lr               \n\t" );

}

//--------------------------------------------------------------


uint32_t save_ctx()
{
	uint32_t result;

	
   return result;




}
//----------------------------------

void context_switch (uint32_t sp)
{
   __asm__ volatile (
         "msr msp, %0  \n\t"
         "bx  lr       \n\t" 
		 : 
		 : "r" (sp) 
		 :
		 	);
}



//------------------------------------

uint32_t proc_mgr[2]={0x20003000U, 0xDeadCa11};

void shin(){
	hw_stack_frame_t* pfrm = (hw_stack_frame_t *)0x20003000+sizeof(sw_stack_frame_t);
	pfrm->r0 = pfrm->r1 = pfrm->r2 = pfrm->r3 = pfrm->r12 = 0;
	pfrm->pc = (uint32_t)main_switcher;
	pfrm->lr = (uint32_t)main_switcher; //if return, then HardFault
    pfrm->psr = 0x21000000; //default PSR value
}	

uint32_t schedule(uint32_t in_ctx)
{

	proc_mgr[1] = proc_mgr[0];
	proc_mgr[0]=in_ctx;
	
	uint32_t out_ctx = proc_mgr[1];

	return out_ctx;

}

//------------------------------------

//-- Get main stack pointer
uint32_t get_MSP(void)
{
	uint32_t result=0;
    asm volatile (
        "mrs %0, msp        \n\t"
//        "bx  lr             \n\t"  
        :"=r" (result) );
   return result;
}

//------------------------------------

//-- Get programm stack pointer
uint32_t get_PSP(void)
{
	register uint32_t result=0;
    asm volatile (
        "mrs %0, psp        \n\t"
//        "bx  lr             \n\t"  
        :"=r" (result) );
   return result;
}

//------------------------------------

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

