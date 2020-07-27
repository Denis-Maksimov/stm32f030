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
u16 x=1;

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
#include "lcd.h"
#include "u_string.h"
u16 y[] ={C_*4 ,D_*4 ,E_*4 ,F_*4 ,G_*4 ,A_*4 ,H_*4 };
u16 y1[]={10000,10000,10000,10000,10000,10000,10000};
extern struct TIMx_chx handl;
void main_switcher(){
  
  while(1)
  {     

         
        //  PWM_setup(&handl, y[x], (y[x])>>2);
        //  os_sleep_ms(y1[x]);

        //  x++;
        //  if(x>6){x=0;}
  }

}

//------------------------------------

void task1()
{
  while(1)
  {
    // REGISTER(GPIOC|GPIOx_ODR) ^= (1<<13);
    digital_write(13,'C',1);
    // print(REGISTER(I2C1|I2C_SR1));
    // os_delay(y[x]);
    // puts("\r\nyeah, baby! its work!!");
    // write_DMA_USART(USART_buffer, 20);
    os_sleep_ms(900);
    digital_write(13,'C',0);
    os_sleep_ms(100);
    // os_sleep_ms(1000);
//    asm volatile("wfi");
  }
}

//------------------------------------

void main(){
        asm volatile ("cpsid i");
        asm volatile ("cpsid f");
        init();
//        ssd1306init();
        USART_buffer[0]='X';
        USART_buffer[19]='Z';
        // pin_init(15,'C',HI_Z_INPUT);
        // void TIM5_PWM_output_mode();
        thread_create(0);
        thread_create(task1);
        // thread_create(main_switcher);
        asm volatile ("cpsie i");
        asm volatile ("cpsie f");

        
        LCDI2C_init(0x27<<1,16,2);
        LCDI2C_backlight();
        // LCDI2C_write(53);
        
        // LCDI2C_noBacklight(); // finish with backlight on
        LCDI2C_setCursor(0,0);
        LCDI2C_write_String("by Maksimov");
        char int_buffer[15]={0};
        os_sleep_ms(1500);
	while(1){

        puts("\r\nticks: ");
        print(sys_tasks.ticks);
        LCDI2C_setCursor(0,1);
        u_intToStr(sys_tasks.ticks, int_buffer);
        LCDI2C_clear();
        LCDI2C_write_String(int_buffer);
        os_sleep_ms(500);
        //asm("wfi");
        }


    asm("b hard_fault");
}







//---------------------------------------------END--------------------------------------------------------------------

