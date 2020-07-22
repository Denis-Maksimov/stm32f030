#ifndef RCC_H

#include "stm32.h"
// #define FLASH_ACR 0x40022000

// устанавливает внешнее тактирование 72 МГц
stm32_api void set_clock_HSE();

// устанавливает внутреннее тактирование 8 МГц
stm32_api void set_clock_HSI();

// сброс RCC
stm32_api void RCC_reset(void);








#define RCC_H
#endif // !RCC_H
