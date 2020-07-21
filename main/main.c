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
int x=1;

//261 277 293 311 329 349 369 392 415 440 466 494
//523 554 587 622 659 698 740 784 830 880 932 987
//1 МГц -> 0,000 001 с == 1
#define C_  95
#define Cd  90
#define D_  85
#define Dd  80
#define E_  75
#define F_  71
#define Fd  67
#define G_  63
#define Gd  60
#define A_  56
#define B_  53
#define H_  50

int y[]={1,1,1,5};
void main_switcher(){
  
  while(1)
  {     
      //  write_DMA_USART(USART_buffer, 20);
        // puts("\r\noh, ja-ja!!! noch!");
        os_delay(10000);
         x++;
        
         if(x>sizeof(y)){x=0;}
  }

}

//------------------------------------

void task1()
{
  while(1)
  {
    REGISTER(GPIOC|GPIOx_ODR) ^= (1<<13);
    os_delay(y[x]);
    // puts("\r\nyeah, baby! its work!!");
    // os_delay(9);
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
        void TIM5_PWM_output_mode();
        thread_create(0);
        thread_create(task1);
        thread_create(main_switcher);
        asm volatile ("cpsie i");
        asm volatile ("cpsie f");

	while(1){

        puts("\r\nticks: ");
        print(sys_tasks.ticks);
          		
        os_delay(19);
        //asm("wfi");
        }


    asm("b hard_fault");
}







//---------------------------------------------END--------------------------------------------------------------------

