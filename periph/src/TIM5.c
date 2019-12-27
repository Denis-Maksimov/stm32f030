#include "TIM5.h"

void TIM5_init(uint16_t prescaller,uint16_t array){
    //
    REGISTER(TIM5_BASE|TIMx_PSC) = prescaller;
    REGISTER(TIM5_BASE|TIMx_ARR) = array;
    REGISTER(TIM5_BASE|TIMx_CNT) = 0;
    REGISTER(TIM5_BASE|TIMx_DIER) |= 1;
    REGISTER(TIM5_BASE|TIMx_CR1) |= TIMx_ARPE|TIMx_CEN;
}



