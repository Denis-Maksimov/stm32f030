#include "NVIC.h"


void NVIC_init(){

    asm("cpsie i");
    asm("cpsie f");
    REGISTER(NVIC_base|NVIC_ISER_0) |= DMA1_Channel4_ie;

    return;
}