//#include "main.h"
#include "main.h"
#include "ssd1306.h"
/*

             | |s|s| |
             |g|w|w|3|
             |n|c|i|.|
             |d|l|o|3|
               |k| | |

              A A A A
              | | | |
          ____|_|_|_|___
        -|VB          3.3|-
    LED--|C13           G|-
        -|C14          5V|-
     _/_-|C15          B9|-
        -|A0           B8|-
        -|A1           B7|--SDA_I2C
        -|A2           B6|--SCL_I2C
        -|A3           B5|-
        -|A4           B4|-
        -|A5           B3|-
        -|A6          A15|-
        -|A7          A12|-
        -|B0          A11|-
        -|B1          A10|--USART
        -|B10          A9|--USART
        -|B11          A8|-
        -|R           B15|-
        -|3.3         B14|-
        -|G           B13|-
        -|G___________B12|-     
                USB



*/

char bufferr[5];

void main(){

        init();

//        ssd1306init();
        pin_init(15,'C',HI_Z_INPUT);
	while(1){
        

       

       
        debug(RCC_BASE+RCC_CFGR);
        debug(USART1);
        debug(SysTick_BASE+SysTick_VAL);
        asm("wfi");
        }


    asm("b hard_fault");
}




//---------------------------------------------END--------------------------------------------------------------------

