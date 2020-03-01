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

void main_switcher(){
  while(1)
  {      
        puts("oh, ja-ja!!! noch!\r\n");
        asm volatile("wfi");
  }

}



void task1()
{
  while(1)
  {
    puts("yeah, baby! its work!!\r\n");
    asm volatile("wfi");
  }
}


void main(){
        asm volatile ("cpsid i");
        asm volatile ("cpsid f");
        init();
 //       shin();
//        ssd1306init();
        pin_init(15,'C',HI_Z_INPUT);
 //       u_thread_attr_t* attribs = (u_thread_attr_t*)u_malloc(sizeof(u_thread_attr_t));
 //       task_create( main_switcher, attribs  );
 //       u_thread_attr_t* attribs1 = (u_thread_attr_t*)u_malloc(sizeof(u_thread_attr_t));
 //       task_create( task1, attribs1  );

  sys_tasks.current_task=0;
  sys_tasks.active_tasks=0b11;

  sys_tasks.task_attribs[0]=(u_thread_attr_t*)u_malloc(sizeof(u_thread_attr_t));
  sys_tasks.task_attribs[1]=(u_thread_attr_t*)u_malloc(sizeof(u_thread_attr_t));
  sys_tasks.task_attribs[2]=(u_thread_attr_t*)u_malloc(sizeof(u_thread_attr_t));

  sys_tasks.task_attribs[0]->hw_sp=0x20004000;
  sys_tasks.task_attribs[0]->hw_sp->xpsr=0x21000000;
  sys_tasks.task_attribs[0]->hw_sp->lr=main;
  sys_tasks.task_attribs[0]->hw_sp->pc=main;

  sys_tasks.task_attribs[1]->hw_sp=0x20004000-128;
  sys_tasks.task_attribs[1]->hw_sp->xpsr=0x21000000;
  sys_tasks.task_attribs[1]->hw_sp->lr=task1;
  sys_tasks.task_attribs[1]->hw_sp->pc=task1;
 // sys_tasks.task_attribs[1]->hw_sp-=32;


  sys_tasks.task_attribs[2]->hw_sp=0x20004000-236;
  sys_tasks.task_attribs[2]->hw_sp->xpsr=0x21000000;
  sys_tasks.task_attribs[2]->hw_sp->lr=main_switcher;
  sys_tasks.task_attribs[2]->hw_sp->pc=main_switcher;
 // sys_tasks.task_attribs[2]->hw_sp-=32;


        asm volatile ("cpsie i");
        asm volatile ("cpsie f");

	while(1){
//	__asm__ volatile(" mov %0, sp"
//			:"=r"(stack)::);	

      puts("hi of before stack:\r\n");		
//      debug(sys_tasks.task_attribs[0]->hw_sp);
      // debug(&(sys_tasks.current_task));
      // debug(&(sys_tasks.task_attribs[0]));
        asm("wfi");
        }


    asm("b hard_fault");
}







//---------------------------------------------END--------------------------------------------------------------------

