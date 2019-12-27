#pragma once
#include "stm32.h"

enum pin_mode {
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

typedef union tagGPIOval{
	struct {
   		enum pin_mode pin0:4;
   		enum pin_mode pin1:4;
   		enum pin_mode pin2:4;
        enum pin_mode pin3:4;

   		enum pin_mode pin4:4;
        enum pin_mode pin5:4;
   		enum pin_mode pin6:4;
        enum pin_mode pin7:4;
	};

	struct {
       	enum pin_mode pin8:4;
        enum pin_mode pin9:4;
   	    enum pin_mode pin10:4;
       	enum pin_mode pin11:4;

        enum pin_mode pin12:4;
   	    enum pin_mode pin13:4;
       	enum pin_mode pin14:4;
       	enum pin_mode pin15:4;
   	};
}GPIOval;

void GPIO_init(void); //Настройка пинов
