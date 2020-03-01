#ifndef MY_DEBUG
#define MY_DEBUG

#include "stm32.h"
#include "USART.h"

//выводит на экран 4 байта
void debug(int adress);
void print(int digit);
#endif // !MY_DEBUG
