#pragma once
#include "stm32.h"

void wait(volatile int i);
void clock(void); //настройка тактирования
//void _RST(void); //SW reset
