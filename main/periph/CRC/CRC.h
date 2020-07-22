/**************************************************************
 * Аппаратный блок для вычисления хэш-суммы
 * 
 * 
 *********************************************************** */

#ifndef CRC_H
#define CRC_H
#include "stm32.h"

stm32_api void CRC_init();
stm32_api uint32_t crc32_native(char *bfr, int len, int clear);
stm32_api uint32_t reverse_32(uint32_t data);
stm32_api uint32_t crc32_ether(char *buf, int len, int clear);


#endif // !CRC_H
