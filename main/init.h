#ifndef INIT_H
#define INIT_H
#include "stm32.h"

#include "string.h"
#include "USART.h"
#include "GPIO.h"
#include "debug.h"
#include "ADC.h"
#include "RCC.h"
#include "Sys_mgr.h"
#include "NVIC.h"
#include "TIMx.h"

extern void init(void);
extern char USART_buffer[];

#endif
