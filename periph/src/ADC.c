#include "ADC.h"

void ADC_init(void){
    //Даёшь тактирование!
    REGISTER(RCC_BASE|RCC_APB2ENR) |= RCC_APB2ENR_ADC1EN |  \
                                      RCC_APB2ENR_IOPAEN;

    //Настройка пинов
    GPIOval* GPIO_a=(GPIOval*)(GPIOA|GPIOx_CRL); //GPIOC low's pins select
        
        GPIO_a->pin0=ANALOG_INPUT;
        GPIO_a->pin1=ANALOG_INPUT;
    //конфигрирование АЦП
        //калибровка
        REGISTER(ADC1_BASE|ADC_CR2)|=ADC_CR2_CAL;
        while (!(REGISTER(ADC1_BASE|ADC_CR2)&(ADC_CR2_CAL)));
        //ADC Settings
 //       REGISTER(ADC1_BASE|ADC_CR2)|=(ADC_CR2_CONT); //вкл. непрерывное преобразование
        REGISTER(ADC1_BASE|ADC_CR2)|=(ADC_CR2_SWenable|ADC_CR2_EXTTRIG); //софтварно АЦП-ить, вкл внешний запуск
        REGISTER(ADC1_BASE|ADC_CR1)|=(ADC_CR1_SCAN);

	    //freq of sampling
        SMPx* SMPR2=(SMPx*)(ADC1_BASE|ADC_SMPR2);
        SMPR2->SMP0=cycles_1_5;
        SMPR2->SMP1=cycles_1_5;

        //последовательность АЦП
        SQRx* SQR=(SQRx*)(ADC1_BASE|ADC_SQR3);
        SQR->SQ1=ch0;
        SQR->SQ2=ch1;
        //количество преобразований2045-2028
        SQR=(SQRx*)(ADC1_BASE|ADC_SQR1);
        SQR->ADC_REGULAR_LENGHT=conversions2;

        //вкл. АЦП
        REGISTER(ADC1_BASE|ADC_CR2)|=(ADC_CR2_adcON); 
}

void ADC_start_conversion(void){
    REGISTER(ADC1_BASE|ADC_CR2)|=(ADC_CR2_SWSTART|ADC_CR2_adcON);
    return;
}
void ADC_read(void){
    char baf[11]={0};
    intToStr((REGISTER(ADC1_BASE|ADC_DR)),baf);
    USART_sendString(baf);
    return ;
}

/*#######################################################
*************  шпаргалка по настройке  ******************
#########################################################

    ANALOG_INPUT=0x0,
    HI_Z_INPUT=0x4,
    PULL_INPUT=0x8,

    PUSH_PULL_OUTPUT_2MHZ=0x2,
    PUSH_PULL_OUTPUT_10MHZ=0x1,
    PUSH_PULL_OUTPUT_50MHZ=0x3,

    OPEN_DRAIN_OUTPUT_2MHZ=0x6,
    OPEN_DRAIN_OUTPUT_10MHZ=0x5,
    OPEN_DRAIN_OUTPUT_50MHZ=0x7,

    AF_PUSH_PULL_OUTPUT_2MHZ=0xA,
    AF_PUSH_PULL_OUTPUT_10MHZ=0x9,
    AF_PUSH_PULL_OUTPUT_50MHZ=0xB,

    AF_OPEN_DRAIN_OUTPUT_2MHZ=0xE,
    AF_OPEN_DRAIN_OUTPUT_10MHZ=0xD,
    AF_OPEN_DRAIN_OUTPUT_50MHZ=0xF,

*/
