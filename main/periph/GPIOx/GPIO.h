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


/**
 * @brief  'auto' setup pin
 * @note   
 * @param  pin:     pin number
 * @param  port:    character of port 'A', 'B' or 'C'
 * @param  mode:    enum definition of mode pin
 * @retval None
 */
stm32_api void pin_init(uint8_t pin, uint8_t port, enum pin_mode mode);

//--------------------------------------------------------


/**
 * @brief  Чтение дискретного входа как на "Ардуино"
 * @note   ошибка на неверный порт и пин
 * @param  pin: 
 * @param  port: 
 * @retval 1 или 0 если ok; -2 неверный порт, -1 неверный пин
 */
stm32_api int digital_read(uint8_t pin, uint8_t port);
//--------------------------------------------------------

#endif // !GPIO_H
