//#include "main.h"
#include "main.h"



char bufferr[]="!!!Wr\r\n";

void main(){

        init();


	while(1){

        puts("Hello, world!\r\n");
        puts("Victory!\r\n");
        
        asm("wfi");
        }


    asm("b hard_fault");
}




//---------------------------------------------END--------------------------------------------------------------------

