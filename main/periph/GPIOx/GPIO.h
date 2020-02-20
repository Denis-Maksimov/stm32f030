#ifndef GPIO_H
#define GPIO_H
#include "stm32.h"

enum pin_mode {
    //- input
    ANALOG_INPUT    = 0b0000,
    HI_Z_INPUT      = 0b0100,
    PULL_INPUT      = 0b1000,
    INPUT_PULLDOWN  = 0x28, ///<--!!!only for pin_init();!!!
    INPUT_PULLUP    = 0x18,   ///<--!!!only for pin_init();!!!
    
    //-- Output --
    PUSH_PULL_OUTPUT_2MHZ   = 0b0010,
    PUSH_PULL_OUTPUT_10MHZ  = 0b0001,
    PUSH_PULL_OUTPUT_50MHZ  = 0b0011,

    OPEN_DRAIN_OUTPUT_2MHZ  = 0b0110,
    OPEN_DRAIN_OUTPUT_10MHZ = 0b0101,
    OPEN_DRAIN_OUTPUT_50MHZ = 0b0111,

    //-- AFIO --
    AF_PUSH_PULL_OUTPUT_2MHZ    = 0b1010,
    AF_PUSH_PULL_OUTPUT_10MHZ   = 0b1001,
    AF_PUSH_PULL_OUTPUT_50MHZ   = 0b1011,

    AF_OPEN_DRAIN_OUTPUT_2MHZ   = 0b1110,
    AF_OPEN_DRAIN_OUTPUT_10MHZ  = 0b1101,
    AF_OPEN_DRAIN_OUTPUT_50MHZ  = 0b1111,
};


//#define x (0b1101);


// typedef union tagGPIOval{
// 	struct {
//    		enum pin_mode pin0:4;
//    		enum pin_mode pin1:4;
//    		enum pin_mode pin2:4;
//         enum pin_mode pin3:4;

//    		enum pin_mode pin4:4;
//         enum pin_mode pin5:4;
//    		enum pin_mode pin6:4;
//         enum pin_mode pin7:4;
// 	};

// 	struct {
//        	enum pin_mode pin8:4;
//         enum pin_mode pin9:4;
//    	    enum pin_mode pin10:4;
//        	enum pin_mode pin11:4;

//         enum pin_mode pin12:4;
//    	    enum pin_mode pin13:4;
//        	enum pin_mode pin14:4;
//        	enum pin_mode pin15:4;
//    	};
// }GPIOval;

//--------------------------------------------------------

//Настройка пинов old manual verse
void GPIO_init(void); 

//--------------------------------------------------------

//'auto' setup pin
/// \arg 
///    @pin:  - pin number
///    @port: - character of port 'A', 'B' or 'C'
///    @mode: - enum definition of mode pin
void pin_init(uint8_t pin, uint8_t port, enum pin_mode mode);

//--------------------------------------------------------
int digital_read(uint8_t pin, uint8_t port);
//--------------------------------------------------------

#endif // !GPIO_H
