#ifndef FLASH_H
#define FLASH_H
#include "stm32.h"
/**
 * @brief  Записывает n байт во флеш память
 * @note   Записывает с точностью до слова 4 байт, неполный остаток игнорируется
 * @param  dest: куда записывать
 * @param  src:  откуда записывать
 * @param  n:    число байт
 * @retval None
 */
stm32_api void flashWrite(void* dest, void* src, u32 n);
stm32_api void flashMassErase(void);

#endif // !FLASH_H
