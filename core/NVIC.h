#include "stm32.h"
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
    unsigned     //19 bit

    unsigned     //19 bit
    unsigned     //19 bit
    unsigned     //19 bit
    unsigned     //19 bit

    unsigned     //19 bit
    unsigned     //19 bit
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