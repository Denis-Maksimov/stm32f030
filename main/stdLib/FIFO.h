#include "stm32.h" // ! stdint
#include "stdlib.h"

uint32_t new_FIFO(uint8_t size);
int FIFO_read(void* data_buffer, uint8_t __n, uint32_t ID);
void FIFO_write(void* __data,uint8_t _n,uint32_t ID);
void del_FIFO(uint32_t ID);

