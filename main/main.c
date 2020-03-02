//#include "main.h"
#include "main.h"
#include "ssd1306.h"
#include "stdlib.h"
#include "Sys_os.h"
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
uint32_t stack;
//------------------------------------
void main_switcher(){
  while(1)
  {     
       
        puts("oh, ja-ja!!! noch!\r\n");
         os_delay(25);
   //     asm volatile("wfi");
  }

}

//------------------------------------

void task1()
{
  while(1)
  {
    puts("yeah, baby! its work!!\r\n");
    os_delay(20);
//    asm volatile("wfi");
  }
}

//------------------------------------

void main(){
        asm volatile ("cpsid i");
        asm volatile ("cpsid f");
        init();
//        ssd1306init();
        pin_init(15,'C',HI_Z_INPUT);

        thread_create(0);
        thread_create(task1);
        thread_create(main_switcher);
        asm volatile ("cpsie i");
        asm volatile ("cpsie f");

	while(1){

          puts("hi of before stack:\r\n");		
        os_delay(19);
        //asm("wfi");
        }


    asm("b hard_fault");
}







//---------------------------------------------END--------------------------------------------------------------------

