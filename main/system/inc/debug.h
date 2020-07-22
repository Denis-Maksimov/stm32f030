#ifndef MY_DEBUG
#define MY_DEBUG

#include "stm32.h"


//выводит на экран 4 байта
stm32_api void debug(int adress);
stm32_api void print(int digit);
#endif // !MY_DEBUG
