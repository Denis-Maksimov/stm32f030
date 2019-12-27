#include "GPIO.h"

void GPIO_init(void){
    //Даёшь тактирование!
    REGISTER(RCC_BASE|RCC_APB2ENR) |= (RCC_APB2ENR_IOPCEN|RCC_APB2ENR_IOPBEN);

    //Настройка пинов
    GPIOval* GPIO_c=(GPIOval*)(GPIOC|GPIOx_CRH); //GPIOC high's pins select
    
	    GPIO_c->pin13=PUSH_PULL_OUTPUT_2MHZ;
	    GPIO_c->pin14=PUSH_PULL_OUTPUT_2MHZ;

        REGISTER(GPIOB|GPIOx_CRL)=0x22222222;//B 0-7 output
    GPIO_c=(GPIOval*)(GPIOB|GPIOx_CRH);
        GPIO_c->pin8=PUSH_PULL_OUTPUT_2MHZ;
	    GPIO_c->pin10=PUSH_PULL_OUTPUT_2MHZ;
}



/*#######################################################
*************  шпаргалка по настройке  ******************
#########################################################

FEDC BA98 // 7654 3210

    CNF для входа
00:0 Analog mode                 ----> &= ~GPIO_CRH_CNFx ### аналоговый вход
01:4 Floating input (reset state) ----> GPIO_CRH_CNFx_0 ### плавающий вход
10:8 Input with pull-up / pull-down ----> GPIO_CRH_CNFx_1 ### вход с резистором up/down устанавливается через GPIOx_ODR или GPIOx_BSR
11:F Reserved
    CNF для выхода
00:0x2/1/3 General purpose output push-pull ----> &= ~GPIO_CRH_CNFx ### 2MHz/10MHz/50MHz
01:0x6/5/7 General purpose output Open-drain ----> GPIO_CRH_CNFx_0 ###
10:0xA/9/B Alternate function output Push-pull ----> GPIO_CRH_CNFx_1 ###
11:0xE/D/F Alternate function output Open-drain ----> GPIO_CRH_CNFx ###
#########################################################
*************                          ******************
#######################################################
enum mode {
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
};







*/
