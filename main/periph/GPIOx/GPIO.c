#include "GPIO.h"

void GPIO_init(void){
    //Даёшь тактирование!
//    REGISTER(RCC_BASE|RCC_APB2ENR) |= (RCC_APB2ENR_IOPCEN|RCC_APB2ENR_IOPBEN);
//    REGISTER(GPIOC|GPIOx_CRH)=0x22222222;//B 0-7 output
    //Настройка пинов
    pin_init(13,'C',PUSH_PULL_OUTPUT_2MHZ);
    pin_init(14,'C',PUSH_PULL_OUTPUT_2MHZ);
//    GPIOval* GPIO_c=(GPIOval*)(GPIOC|GPIOx_CRH); //GPIOC high's pins select
    
//	    GPIO_c->pin13=PUSH_PULL_OUTPUT_2MHZ;
//	    GPIO_c->pin14=PUSH_PULL_OUTPUT_2MHZ;

    //    REGISTER(GPIOB|GPIOx_CRL)=0x22222222;//B 0-7 output
    pin_init(11,'B',HI_Z_INPUT);
    pin_init(10,'B',PUSH_PULL_OUTPUT_50MHZ);
 //   GPIO_c=(GPIOval*)(GPIOB|GPIOx_CRH);
   //     GPIO_c->pin11=HI_Z_INPUT;//echo
	 //   GPIO_c->pin10=PUSH_PULL_OUTPUT_50MHZ;//trig
}

void pin_init(uint8_t pin, uint8_t port, enum pin_mode mode){
    
    //-- sellect Hi-Low & register offset--
    if(pin>15)return;

    volatile uint32_t GPIO_base=0;
    volatile uint32_t _offset=0;
    uint8_t _pin=pin;
    if(pin > 7){
        _offset = GPIOx_CRH;
        pin=pin-8;
    }else{
        _offset = GPIOx_CRL;
    }

    //-- sellect port & base --
    switch (port)
    {
    case 'A':
        GPIO_base = (GPIOA);
        REGISTER(RCC_BASE|RCC_APB2ENR) |= (RCC_APB2ENR_IOPAEN);
        break;
    case 'B':
        GPIO_base = (GPIOB);
        REGISTER(RCC_BASE|RCC_APB2ENR) |= (RCC_APB2ENR_IOPBEN);
        break;
    case 'C':
        GPIO_base = (GPIOC);
        REGISTER(RCC_BASE|RCC_APB2ENR) |= (RCC_APB2ENR_IOPCEN);
        break;
    default:
        ///TODO:
        return;
    }
    
    //-- sellect mode --
    #define GPIOx_CRx *((volatile uint32_t*)(GPIO_base | _offset))
    uint32_t mask = 0x0f;
    //mask=(mask<<pin);                                           // set bits mask
    GPIOx_CRx &= ~(mask<<(pin*4));                            // clearing bits mask
    GPIOx_CRx |= (uint32_t)((mode & mask)<<(pin*4));   // set mode
    #undef GPIOx_CRx

    //-- binding if pull mode --
    if(mode == INPUT_PULLUP){
        *((volatile uint32_t*)(GPIO_base + GPIOx_ODR)) |= (0x01<<_pin);
    }
    if(mode == INPUT_PULLDOWN){
        *((volatile uint32_t*)(GPIO_base + GPIOx_ODR)) &= ~((uint32_t)(0x01<<_pin));
    }

    // -- Clock for Alternete Function
    if( ( mode>=10 )&&( mode<=15 ) ){
        REGISTER(RCC_BASE|RCC_APB2ENR) |= RCC_APB2ENR_AFIOEN;
    }
    return;
}

int digital_read(uint8_t pin, uint8_t port){
    //-- sellect port & base --
    volatile uint32_t GPIO_base=0;
    switch (port)
    {
    
    case 'A':
        GPIO_base = (GPIOA);
        REGISTER(RCC_BASE|RCC_APB2ENR) |= (RCC_APB2ENR_IOPAEN);
        break;
    case 'B':
        GPIO_base = (GPIOB);
        REGISTER(RCC_BASE|RCC_APB2ENR) |= (RCC_APB2ENR_IOPBEN);
        break;
    case 'C':
        GPIO_base = (GPIOC);
        REGISTER(RCC_BASE|RCC_APB2ENR) |= (RCC_APB2ENR_IOPCEN);
        break;
    default:
        ///TODO:
        return -1;


    }
    return (REGISTER(GPIO_base + GPIOx_IDR))>>pin;
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
