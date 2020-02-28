#ifndef SYS_MGR_H
#define SYS_MGR_H
#include "stm32.h"
#include "USART.h"
#include "stdlib.h"
uint32_t handle_reg1;
uint32_t handle_reg2;
int sys_ticks;
void SysTick_init(int period);
void main_switcher();


///TODO:

#define U_THREAD_MAX_COUNT_OF_THREADS 20


//-- Дескриптор потока --
typedef uint32_t u_thread_t;

//-- Атрибуты потока --
typedef struct{
	u_thread_t tid;

}u_thread_attr_t;

/*************************************************************** 
 * \brief create new thread
 * @tid: adress of thread descriptor
 * @attr: address allocated memory for struct of the attributes
 * @thread_handler: function-thread whith new handle
 * @argv: pointer to given arguments of thread_handler function
 * *************************************************************/
int u_thread_create(u_thread_t* tid, u_thread_attr_t attr, void* (*thread_handler)(void*), void* argv );

void u_thread_exit(void);
void u_thread_join(void);


void mutex_lock(void);
void mutex_unlock(void);
//-------------------------
uint32_t get_MSP(void);
uint32_t get_PSP(void);
void shin();


uint32_t save_ctx();
#endif // !SYS_MGR_H

