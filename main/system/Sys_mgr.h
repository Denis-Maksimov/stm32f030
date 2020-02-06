#ifndef SYS_MGR_H
#define SYS_MGR_H
#include "stm32.h"
#include "USART.h"
int sys_ticks;
void SysTick_init(int period);


///TODO:
void thread(void);
void mutex_lock(void);
void mutex_unlock(void);



#endif // !SYS_MGR_H
