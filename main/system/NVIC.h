#include "stm32.h"

//--- NVIC_ISER_[0] ---
#define WWDG_ie             (1<<0)
#define PVD_ie              (1<<1)
#define TAMPER_ie           (1<<2)
#define RTC_ie              (1<<3)
#define FLASH_ie            (1<<4)
#define RCC_ie              (1<<5)
#define EXTI0_ie            (1<<6)
#define EXTI1_ie            (1<<7)
#define EXTI2_ie            (1<<8)
#define EXTI3_ie            (1<<9)
#define EXTI4_ie            (1<<10)
#define DMA1_Channel1_ie    (1<<11)
#define DMA1_Channel2_ie    (1<<12)
#define DMA1_Channel3_ie    (1<<13)
#define DMA1_Channel4_ie    (1<<14)
#define DMA1_Channel5_ie    (1<<15)
#define DMA1_Channel6_ie    (1<<16)
#define DMA1_Channel7_ie    (1<<17)
#define ADC1_2_ie           (1<<18)
#define CAN1_TX_ie          (1<<19)
#define CAN1_RX0_ie         (1<<20)
#define CAN1_RX1_ie         (1<<21)
#define CAN1_SCE_ie         (1<<22)
#define EXTI9_5_ie          (1<<23)
#define TIM1_BRK_ie         (1<<24)
#define TIM1_UP_ie          (1<<25)
#define TIM1_TRG_COM_ie     (1<<26)
#define TIM1_CC_ie          (1<<27)
#define TIM2_ie             (1<<28)
#define TIM3_ie             (1<<29)
#define TIM4_ie             (1<<30)
#define I2C1_EV_ie          (1<<31)



void NVIC_init();


/* 
Interrupts
                            CMSIS array elements (1)
            Set-enable  Clear-enable    Set-pending     Clear-pending   Active Bit
0-31        ISER[0]     ICER[0]         ISPR[0]         ICPR[0]         IABR[0]
32-63       ISER[1]     ICER[1]         ISPR[1]         ICPR[1]         IABR[1]
64-67       ISER[2]     ICER[2]         ISPR[2]         ICPR[2]         IABR[2]

*/
/* 
struct _SCB_ICSR{
    unsigned VECTACTIVE:9;
    unsigned _rsv:2;
    unsigned RETOBASE:1;
    unsigned VECTPENDING:10;
    unsigned ISRPENDING:1;
    unsigned __rsv:2;
    unsigned PENDSTCLR:1;
    unsigned PENDSTSET:1;
    unsigned PENDSVCLR:1;
    unsigned PENDSVSET:1;
    unsigned ___rsv:2;
    unsigned NMIPENDSET:1;
};

struct _NVIC_ISER_0{
//0 bit
    unsigned 
    unsigned 
    unsigned 
    unsigned 

    unsigned 
    unsigned 
    unsigned 
    unsigned 

    unsigned 
    unsigned
    unsigned      //10 bit
    unsigned     ie_DMA1:1//11 bit

    unsigned     //12 bit
    unsigned     //13 bit
    unsigned     //14 bit
    unsigned     //15 bit

    unsigned     //16 bit
    unsigned     //17 bit
    unsigned ie_ADC:1;   //18 bit 
    unsigned    //19 bit

    unsigned    //20 bit
    unsigned    //21 bit
    unsigned    //22 bit
    unsigned    //23 bit

    unsigned    //24 bit
    unsigned    //25 bit
    unsigned  //26 bit
    unsigned ie_TIM1:1;//27 bit

    unsigned ie_TIM2:1;//28 bit
    unsigned ie_TIM3:1;//29 bit
    unsigned ie_TIM4:1;//30 bit
    unsigned //31 bit


};*/