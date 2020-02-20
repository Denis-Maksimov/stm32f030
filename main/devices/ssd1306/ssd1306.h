
#include "i2c.h"
#include "stdlib.h"

#define SSD1306_ADDR_READ   0b01111001
#define SSD1306_ADDR_WRITE  0b01111000

#define SSD1306_Co_bit      (0x01<<7)   // Continuation bit 
#define SSD1306_DATA_CMD    (0x01<<6)   // 1-Data / 0-Command Selection bit

#define SSD1306_CMD         (SSD1306_Co_bit)


//--    1. Fundamental Command Table
#define  SSD1306_SET_CONTRAST               0x81
    #define  SSD1306_SET_CONTRAST_A(a)       ((0xff)&(a))
#define  SSD1306_CONTEXT_ENABLE             0xA4    // Resume to RAM content display
#define  SSD1306_CONTEXT_IGNORE             0xA5    // Entire display ON

#define  SSD1306_NORMAL                     0xA6    // 
#define  SSD1306_INVERSE                    0xA7    // 

#define  SSD1306_SLEEP                      0xAE    // Display OFF (sleep mode)
#define  SSD1306_WAKEUP                     0xAF    // display TURN ON


//--    2. Scrolling Command Table
//--    3. Addressing Setting Command Table
#define  SSD1306_SET_LOWER_COLUMN(a)          ((0x0f)&(a)) //Set the lower nibble of the column start address register for Page Addressing Mode using X[3:0] as data bits. The initial display line register is reset to 0000b after RESET.
#define  SSD1306_SET_HIGHER_COLUMN(a)         ((0x1f)&(a)) //Set the higher nibble of the column start address register for Page Addressing Mode using X[3:0] as data bits. The initial display line register is reset to 0000b after RESET.
#define  SSD1306_SET_MEM_ADDR_MODE            0x20  //set memory adressing mode
    #define  SSD1306_HORIZONTAL_AM          0b00    //запись колонками по байту слева направо с переносом по достижении края строки
    #define  SSD1306_VERTICAL_AM            0b01    //запись колонками по байту сверху-вниз с переносом вправо по достижении нижнего края
    #define  SSD1306_PAGE_AM                0b10    //запись колонками по байту слева направо без переноса

#define  SSD1306_SET_COLUMN_ADDR              0x21    //Setup column start and end address (0-127)
    #define  SSD1306_A_START_ADDR_CA(a)     ((0x7f)&(a))
    #define  SSD1306_B_END_ADDR_CA(b)       ((0x7f)&(b))

#define  SSD1306_SET_PAGE_ADDR                0x22    //Setup page start and end address (0-7)
    #define  SSD1306_A_START_ADDR_PA(a)     ((0x07)&(a))
    #define  SSD1306_B_END_ADDR_PA(b)       ((0x07)&(b))

#define  SSD1306_SET_PAGE_START(a)            ((0xB0)|((0x7)&(a))) //Set GDDRAM Page Start Address (PAGE0~PAGE7) for Page Addressing Mode

//--    4. Hardware Configuration (Panel resolution & layout related) Command Table

#define  SSD1306_SET_DISPLAY_START_LINE(a)  ((0x40)|((0x3F)&(a)))
#define  SSD1306_SET_SEGMENT_REMAP_0        0xA0    // column address 0 is mapped to SEG0 (RESET) 
#define  SSD1306_SET_SEGMENT_REMAP_127      0xA1    // column address 127 is mapped to SEG0
#define  SSD1306_SET_MULTIPLEX_RATIO        0xA8
    #define  SSD1306_SET_MULTIPLEX_RATIO_A(a)   ((0x3f)&(a))    //Set MUX ratio to N+1 MUX. !from 0 to 14 are invalid entry! 

#define  SSD1306_SCAN_DIRECTION_NORMAL      0xC0
#define  SSD1306_SCAN_DIRECTION_REMAPPED    0xC8
#define  SSD1306_SET_DISPLAY_OFFSET         0xD3
    #define  SSD1306_DISPLAY_OFFSET_A(a)    ((0x3f)&(a))

#define  SSD1306_SET_COM_PINS_CONF            0xDA
    #define  SSD1306_COM_PINS_CONF_SEQ        0x02 //Sequential COM pin configuration
    #define  SSD1306_COM_PINS_CONF_ALT        0x12 //1b(RESET), Alternative COM pin configuration
    #define  SSD1306_COM_PINS_CONF_REMAP_EN   (0x01<<5)


//--    5. Timing & Driving Scheme Setting Command Table
#define  SSD1306_SET_DISPLAY_CLK            0xD5
    #define  SSD1306_DISPLAY_CLK_A(a)       ((0xff)&(a)) //Set the Oscillator Frequency, FOSC.

#define  SSD1306_SET_PRECHARGE_PERIOD       0xD9
    #define  SSD1306_PRECHARGE_PERIOD_A(a)  ((0xff)&(a))

#define  SSD1306_SET_V_COMH_LVL       0xDB
    #define  SSD1306_V_COMH_065       0x00
    #define  SSD1306_V_COMH_077       0x20
    #define  SSD1306_V_COMH_083       0x30


void ssd1306init();
void ssd1306fill();