/**************************************************************
 * Аппаратный блок для вычисления хэш-суммы
 * 
 * 
 *********************************************************** */

#ifndef CRC_H
#define CRC_H
#include "stm32.h"

void CRC_init();
uint32_t crc32_native(char *bfr, int len, int clear);
uint32_t reverse_32(uint32_t data);
uint32_t crc32_ether(char *buf, int len, int clear);


#endif // !CRC_H
