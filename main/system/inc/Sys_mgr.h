/***********************************************************
 * This file provide the header for next parts:
 * Sys_mgr.c
 * 
 * ********************************************************/
#ifndef SYS_MGR_H
#define SYS_MGR_H
#include "stm32.h"
#include "USART.h"
#include "stdlib.h"
#include "debug.h"
#include "Sys_mgr.h"
#include "Sys_os.h"


void SysTick_set_clock(void);
void SysTick_init(void);

uint32_t u_clock();



// //-- Атрибуты потока --
// typedef struct{
// 	u_thread_t tid;

// }u_thread_attr_t;

/*************************************************************** 
 * \brief create new thread
 * @tid: adress of thread descriptor
 * @attr: address allocated memory for struct of the attributes
 * @thread_handler: function-thread whith new handle
 * @argv: pointer to given arguments of thread_handler function
 * *************************************************************/
// int u_thread_create(u_thread_t* tid, u_thread_attr_t attr, void* (*thread_handler)(void*), void* argv );

// void u_thread_exit(void);
// void u_thread_join(void);


// void u_thread_exit(void);


// //----------------------------------------------------


// void u_thread_join(void);


// //----------------------------------------------------


void u_lock(void);
void u_unlock(void);

// //----------------------------------------------------


// void mutex_unlock(void){
//     ///TODO:   
// }


// //----------------------------------------------------

// void mutex_lock(void);
// void mutex_unlock(void);
//-------------------------
uint32_t get_MSP(void);
uint32_t get_PSP(void);
void set_MSP(uint32_t __reg);


// void shin();


// uint32_t save_ctx();
#endif // !SYS_MGR_H

