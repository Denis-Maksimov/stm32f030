#ifndef SYS_OS_H
#define SYS_OS_H
#include "stm32.h"
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
   uint32_t xpsr;
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


//-- Дескриптор потока --
typedef uint32_t u_thread_t;

//-- Атрибуты потока --
typedef struct{
 	u_thread_t tid; //-> thread ID
    hw_stack_frame_t* hw_sp; // главный набор контекста
    sw_stack_frame_t* sw_sp; // доп. набор
    uint32_t* canary;           //адрес стековой канарейки 0xCAFEBABE для проверки целостности стека, он же начало стека проги
 }u_thread_attr_t;





#define THREAD_STACK_BEGIN      0x20004000
#define THREAD_STACK_SIZE       128
struct{
    uint32_t ticks;
    uint8_t n_tasks;         //0
    uint32_t active_tasks;  // .. 0 0 0 1 0 1 1 ..
    uint8_t current_task;
    u_thread_attr_t* task_attribs[32];
} sys_tasks;

u_thread_attr_t* get_attribs(uint32_t pid) __attribute__( ( naked ) );
uint32_t get_active_tasks();
uint32_t get_current_task();

void thread_create( void(*thread_handler)(void) );

void yield();
void task_mgr( );
void os_delay(uint32_t cycles);
void os_sleep_ms(uint32_t time);
// void increment_task() __attribute__( ( naked ) );
// u_thread_t task_create( void(*thread_handler)(void), u_thread_attr_t* attribs  );
// int stack_alloc(u_thread_attr_t* attribs);






/******************************************************
 * ARMv7M specific handler. In this programm using as
 * task mgr, context switcher etc.
 * Das ist heart of the my mini operation system
 * ---------------------------------------------------
 * __attribute__( ( naked ) ) is dirrective to compiler,
 * then disable pushing to stack.
 * !!!>> stacking here will hurt the program <<!!!
 * ---------------------------------------------------
 * ****************************************************/
void PendSV_Handler(void) __attribute__( ( naked ) );

void context_switch (uint32_t sp) __attribute__( ( naked ) );

uint32_t schedule(uint32_t in_ctx) __attribute__( ( naked ) );


#endif // !SYS_OS_H
