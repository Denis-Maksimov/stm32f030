#include "TIMx.h"



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


#define TIMx_CCRx(a) 0x30+(a*4) 
void PWM_setup(struct TIMx_chx* tim, u16 T_us, u16 duty_cycle)
{
    REGISTER(tim->TIMx+TIMx_CR1)&=~(TIMx_CR1_CEN);
    if( (duty_cycle==0)||(T_us==0) ) {
        
        return;
    }
    REGISTER(tim->TIMx+TIMx_CNT)=0;
    REGISTER(tim->TIMx+TIMx_ARR)=0xFFFF&T_us;  //период счёта
    REGISTER(tim->TIMx+TIMx_CCRx(tim->ch))=0xFFFF&duty_cycle;  //коэффициент заполнения
    REGISTER(tim->TIMx+TIMx_CR1)|=TIMx_CR1_CEN;
}
/**
 * @brief  
 * @note   
 *      TIM5_CH4 > PA3
 * 
 *      TIM4_CH1 > PB6
 *      TIM4_CH2 > PB7
 *      TIM4_CH3 > PB8
 *      TIM4_CH4 > PB9
 * 
 *      TIM3_CH1 > PA6
 *      TIM3_CH2 > PA7
 *      TIM3_CH3 > PB0
 *      TIM3_CH4 > PB1
 * 
 *      TIM2_CH1_ETR > PA0
 *      TIM2_CH2 > PA1
 *      TIM2_CH3 > PA2
 *      TIM2_CH4 > PA3
 *      
 * @retval None
 */
void PWM_output_mode(struct TIMx_chx* ret_handle,uint8_t pin, uint8_t port)
{
    
    u32 TIMx;
    u8 ch;
    if ((pin<=3) && (port=='A')){
        TIMx =  TIM2_BASE;
        REGISTER(RCC_BASE|RCC_APB1ENR) |= RCC_APB1_TIM2EN;
        ch = pin+1;
    }else if ( (((pin==6)||(pin==7)) && port=='A') || ((pin<2) &&(port=='B') ) )
    {
        TIMx =  TIM3_BASE;
        REGISTER(RCC_BASE|RCC_APB1ENR) |= RCC_APB1_TIM3EN;
        (pin<2)?(ch=pin+1):(ch=pin-5);
    }else if (( pin-6 <=4) && (port=='B'))
    {
        TIMx =  TIM4_BASE;
        REGISTER(RCC_BASE|RCC_APB1ENR) |= RCC_APB1_TIM4EN;
        ch = pin-6;
    }else
    {
        //TODO: remap & log
        return;
    }
    
    
    
    pin_init(pin,port,AF_PUSH_PULL_OUTPUT_50MHZ);

    // //Даёшь тактирование!
    // REGISTER(RCC_BASE|RCC_APB1ENR) |= RCC_APB1_TIM2EN;

    REGISTER(TIMx+TIMx_PSC)=72;    //предделитель счёта

    // REGISTER(TIMx+TIMx_ARR)=T_us;  //период счёта
    // REGISTER(TIMx+TIMx_CCRx(ch))=duty_cycle;  //коэффициент заполнения

    if(ch==1){
        REGISTER(TIMx+TIMx_CCMR1)|=TIMx_CCMR1_OC1M(OC2M_PWD1);
        REGISTER(TIMx+TIMx_CCER)|=TIMx_CCER_CC1E;  //выход на ножку
        REGISTER(TIMx+TIMx_CCER)&=~(TIMx_CCER_CC1P); //полярность
    }
    else if(ch==2){
        REGISTER(TIMx+TIMx_CCMR1)|=TIMx_CCMR1_OC2M(OC2M_PWD1);
        REGISTER(TIMx+TIMx_CCER)|=TIMx_CCER_CC2E;  //выход на ножку
        REGISTER(TIMx+TIMx_CCER)&=~(TIMx_CCER_CC2P); //полярность
    }
    
    else if(ch==3){
        REGISTER(TIMx+TIMx_CCMR2)|=TIMx_CCMR2_OC3M(OC2M_PWD1);
        REGISTER(TIMx+TIMx_CCER)|=TIMx_CCER_CC3E;  //выход на ножку
        REGISTER(TIMx+TIMx_CCER)&=~(TIMx_CCER_CC3P); //полярность
    }
    
    else if(ch==4){
        REGISTER(TIMx+TIMx_CCMR2)|=TIMx_CCMR2_OC4M(OC2M_PWD1);
        REGISTER(TIMx+TIMx_CCER)|=TIMx_CCER_CC4E;  //выход на ножку
        REGISTER(TIMx+TIMx_CCER)&=~(TIMx_CCER_CC4P); //полярность
    }
        
    REGISTER(TIMx+TIMx_CR1)&=~(TIMx_CR1_DIR);
    // REGISTER(TIMx+TIMx_CR1)|=TIMx_CR1_CEN;
    ret_handle->TIMx=TIMx;
    ret_handle->ch=ch;

}//PWM_output_mode
#undef TIMx_CCRx 

void TIM5_PWM_one_shot_mode(){

}

