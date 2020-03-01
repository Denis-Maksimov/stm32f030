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




/*********************************************
 *  \brief Reset the same as with the button 
 * *******************************************/
void _RST(void){
  REGISTER(SCB_Base|SCB_AIRCR)= AIRCR_KEY | AIRCR_SYSRESETREQ;
}// Reset - как с кнопки


//--------------------------------------------------------------

/********************************
 * Cyclic system interrupt
 * ******************************/
void SysTick_Handler(void){


    sys_ticks++;
    REGISTER(GPIOC|GPIOx_ODR) ^= (1<<13);
    while (!(REGISTER(SysTick_BASE|SysTick_CTRL)&SysTick_COUNTFLAG));
    
   

	//-- return to PendSV --
	REGISTER(SCB_Base+SCB_ICSR)|=SCB_ICSR_PENDSVSET;

    __asm__ volatile( "dsb" ); // Data synchronization barrier
    __asm__ volatile( "isb" );  // Instruction synchronization barrier

    return;
}

//--------------------------------------------------------------
extern uint32_t stack;



/********************************
 * Cyclic system interrupt
 * ******************************/
void PendSV_Handler(void)
{
  //  puts("1 ");
//  REGISTER(SCB_Base+SCB_ICSR)|=SCB_ICSR_PENDSVCLR|SCB_ICSR_PENDSTCLR;
  //  uint32_t PID = get_current_task();
//    puts("xpsr \r\n");
//    print(sys_tasks.task_attribs[sys_tasks.current_task]->hw_sp->xpsr);
    uint32_t _msp, _soft_sp; 
    
 //   sys_tasks.task_attribs[sys_tasks.current_task]->sw_sp=_msp-32;
    //save ctx
    __asm__ volatile(
        "mrs %0, msp        \n\t"
        "movs %1, %0        \n\t"
        " stmdb %1!, {r4-r7}       \n\t"
        " movs r4, r8              \n\t"
        " movs r5, r9              \n\t"
        " movs r6, r10              \n\t"
        " movs r7, r11              \n\t"
        " stmdb %1!, {r4-r7}       \n\t"
			:"=r"(_msp),"=r"(_soft_sp)
            :"r"(_msp)
            : "r4","r5","r6","r7"           );
    sys_tasks.task_attribs[sys_tasks.current_task]->hw_sp=(hw_stack_frame_t*)_msp; 
    sys_tasks.task_attribs[sys_tasks.current_task]->sw_sp=(sw_stack_frame_t*)_soft_sp; 

    (sys_tasks.current_task<2)?(sys_tasks.current_task=sys_tasks.current_task+1):(sys_tasks.current_task=0);
//	increment_task();
//    puts("3 ");



 //   while(REGISTER(DMA1_BASE|DMA_CNDTR4));
 //   set_MSP(sys_tasks.task_attribs[sys_tasks.current_task]->hw_sp);
    _msp     = sys_tasks.task_attribs[sys_tasks.current_task]->hw_sp;
    _soft_sp = sys_tasks.task_attribs[sys_tasks.current_task]->sw_sp;
    __asm__ volatile(
  //      "mrs r0, msp               \n\t"
 //       "adds r0, r0, #4               \n\t"
        " ldmia %1!, {r4-r7}       \n\t"
        " movs r11, r4              \n\t"
        " movs r10, r5              \n\t"
        " movs r9, r6              \n\t"
        " movs r8, r7              \n\t"
        " ldmia %1!, {r4-r7}       \n\t"
        "msr msp, %0        \n\t"
        "ldr lr, =0xFFFFFFF9 \n\t"
        "BX lr               \n\t"
			:
            :"r"(_msp),"r"(_soft_sp)
            : "r4","r5","r6","r7"             );

  //  puts("debugging:\r\n");
//	__asm__ volatile(" mov %0, sp"
//			:"=r"(stack)::);
 //   debug(stack+20);
 //   debug(stack+24);

    
	// // //--get context
	// uint32_t sp = get_MSP();
    // REGISTER(sp+20)=main_switcher;  //PC
    // REGISTER(sp+24)=main_switcher; //LR




}

/**
 * 2000 5000
 * 
 * 
*/


u_thread_attr_t* get_attribs(uint32_t pid)
{
    return sys_tasks.task_attribs[pid];
}
uint32_t get_active_tasks()
{
    return sys_tasks.active_tasks;
}
void set_active_tasks(uint32_t value){
    sys_tasks.active_tasks=value;
    return;
}
uint32_t get_current_task()
{
    return sys_tasks.current_task;
}
void increment_task()
{
    for (int i=sys_tasks.current_task+1;i<32;i++)
    {
        if((sys_tasks.active_tasks)&(1<<i))
        {
            sys_tasks.current_task = i;
            return ;
        }
            
    }
    sys_tasks.current_task=0;
    return; //<--nokilled process
}
//-----------------------------------------------------------------
u_thread_t task_create( void(*thread_handler)(void), u_thread_attr_t* attribs  )
{
        if (stack_alloc(attribs))
        {
            return 0;
        }

        attribs->hw_sp->pc = (uint32_t)thread_handler;
        attribs->hw_sp->lr = (uint32_t)thread_handler;
        attribs->hw_sp->xpsr = 0x01000000;
        attribs->sw_sp=(sw_stack_frame_t*)((uint32_t)(attribs->hw_sp)-32);

        sys_tasks.active_tasks |= 1 << attribs->tid;
        sys_tasks.task_attribs[attribs->tid] = attribs;
        return attribs->tid;

}


int stack_alloc(u_thread_attr_t* attribs)
{
    hw_stack_frame_t* ptr = (hw_stack_frame_t*)THREAD_STACK_BEGIN;
    int zond=1;
    for (int i=0;i<32;i++)
    {
        if ((get_active_tasks()&zond)==0)
        {
            set_active_tasks(
                     get_active_tasks()  | zond
                );
            attribs->hw_sp=ptr;
            attribs->tid=i;
            attribs->canary=(uint32_t*)(ptr+32);
            REGISTER(attribs->canary)=0xCafeBabe;
            return 0;
        }
        ptr=ptr-THREAD_STACK_SIZE;
        zond=zond<<1;
    }

   return 1; 
}





//--------------------------------------------------------------


// uint32_t save_ctx()
// {
// 	uint32_t result;

	
//    return result;




// }
// //----------------------------------

// void context_switch (uint32_t sp)
// {
//    __asm__ volatile (
//          "msr msp, %0  \n\t"
//          "bx  lr       \n\t" 
// 		 : 
// 		 : "r" (sp) 
// 		 :
// 		 	);
// }



//------------------------------------

// uint32_t proc_mgr[2]={0x20003000U, 0xDeadCa11};

// void shin(){
// 	hw_stack_frame_t* pfrm = (hw_stack_frame_t *)0x20003000+sizeof(sw_stack_frame_t);
// 	pfrm->r0 = pfrm->r1 = pfrm->r2 = pfrm->r3 = pfrm->r12 = 0;
// 	pfrm->pc = (uint32_t)main_switcher;
// 	pfrm->lr = (uint32_t)main_switcher; //if return, then HardFault
//     pfrm->psr = 0x21000000; //default PSR value
// }	

// uint32_t schedule(uint32_t in_ctx)
// {

// 	proc_mgr[1] = proc_mgr[0];
// 	proc_mgr[0]=in_ctx;
	
// 	uint32_t out_ctx = proc_mgr[1];

// 	return out_ctx;

// }

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
//-- Set main stack pointer
void set_MSP(uint32_t __reg)
{
    asm volatile (
        "msr msp, %0        \n\t"
        :
        :"r"(__reg) 
        : );

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

// int u_thread_create(u_thread_t* tid, u_thread_attr_t attr, void* (*thread_handler)(void*), void* argv ){
	
	

	
// 	return 0; //-->success
// }

//----------------------------------------------------


// void u_thread_exit(void);


// //----------------------------------------------------


// void u_thread_join(void);


// //----------------------------------------------------


// void mutex_lock(void){
//     ///TODO:
// }


// //----------------------------------------------------


// void mutex_unlock(void){
//     ///TODO:   
// }


// //----------------------------------------------------
