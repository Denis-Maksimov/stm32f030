#include "TIM5.h"



void TIM5_init(uint32_t mode, void* settings){

    //Даёшь тактирование!
    REGISTER(RCC_BASE|RCC_APB1ENR) |= RCC_APB1_TIM5EN;
    //
    
    //
    switch (mode)
    {
    case TIME_BASE_UNIT:{
        struct Timer_mode_settings* Config;// = settings;
        Config=settings;
        TIM5_time_base_unit(Config->prescaller,Config->array);
        break;
    }
    case ENCODER_MODE:{
        struct Encoder_mode_settings* Config = settings;
        TIM5_encoder_interface_mode(Config);
        break;
    }
    default:
        break;
    }
    
    
}


void TIM5_time_base_unit(uint16_t prescaller,uint16_t array){

    REGISTER(TIM5_BASE|TIMx_PSC) = prescaller;
    REGISTER(TIM5_BASE|TIMx_ARR) = array;
    REGISTER(TIM5_BASE|TIMx_CNT) = 0;
    REGISTER(TIM5_BASE|TIMx_DIER) |= 1;
    REGISTER(TIM5_BASE|TIMx_CR1) |= TIMx_CR1_ARPE|TIMx_CR1_CEN;

}
//-------------------------------------------------------------------------------------

void TIM5_encoder_interface_mode(struct Encoder_mode_settings* cfg){
    //15.3.12 !!!

    //INPUT_FLOATING

    //-- setting pins --
    pin_init(cfg->TI1_pin,cfg->TI1_port,HI_Z_INPUT);
    pin_init(cfg->TI2_pin,cfg->TI2_port,HI_Z_INPUT);


    //-- select Encoder Interface mode  --
    if((cfg->TI1_en)&(cfg->TI2_en)){
        REGISTER(TIM5_BASE|TIMx_SMCR) |= TIMx_SMCR_SMS(SMS_MODE3); //TI1+TI2
        //-- Настраиваем второй мультиплексор (для первого и второго входа)  --
        REGISTER(TIM5_BASE|TIMx_CCMR1) |= TIMx_CCMR1_CC1S(CC1S_IN_TRC);
    }else if(cfg->TI1_en){
        REGISTER(TIM5_BASE|TIMx_SMCR)|=TIMx_SMCR_SMS(SMS_MODE1); //TI1
        //-- Настраиваем второй мультиплексор (для первого входа)  --
        REGISTER(TIM5_BASE|TIMx_CCMR1) |= TIMx_CCMR1_CC1S(CC1S_IN_TI1);
    }else{
        REGISTER(TIM5_BASE|TIMx_SMCR)|=TIMx_SMCR_SMS(SMS_MODE2); //TI2
        //-- Настраиваем второй мультиплексор (для второго входа)  --
        REGISTER(TIM5_BASE|TIMx_CCMR1) |= TIMx_CCMR1_CC1S(CC1S_IN_TI2);
    }

    //-- Select the TI1 and TI2 polarity  --
    REGISTER(TIM5_BASE|TIMx_CCER) |= TIMx_CCER_CC1P|TIMx_CCER_CC2P;

    //-- limit counts ---
    REGISTER(TIM5_BASE|TIMx_ARR) = cfg->array;

}
//-------------------------------------------------------------------------------------
void TIM5_counter_mode(){

}
void TIM5_clock_selection(){

}
void TIM5_input_capture_mode(){

}
void TIM5_PWM_input_mode(){

}
void TIM5_forced_output_mode(){

}
void TIM5_output_compare_mode(){

}
void TIM5_PWM_output_mode(){
    //Даёшь тактирование!
    REGISTER(RCC_BASE|RCC_APB1ENR) |= RCC_APB1_TIM2EN;
    pin_init(1,'A',AF_OPEN_DRAIN_OUTPUT_50MHZ);


    REGISTER(TIM2_BASE+TIMx_PSC)=20;
    REGISTER(TIM2_BASE+TIMx_ARR)=1000;
    
    REGISTER(TIM2_BASE+TIMx_CCR2)=500;

    REGISTER(TIM2_BASE+TIMx_CCMR1)|=TIMx_CCMR1_OC2M(OC2M_PWD1);
    REGISTER(TIM2_BASE+TIMx_CCER)|=TIMx_CCER_CC2E;
    REGISTER(TIM2_BASE+TIMx_CCER)&=~TIMx_CCER_CC2P;
    REGISTER(TIM2_BASE+TIMx_CR1)&=~TIMx_CR1_DIR;



    REGISTER(TIM2_BASE+TIMx_CR1)|=TIMx_CR1_CEN;


}

void TIM5_PWM_one_shot_mode(){

}

