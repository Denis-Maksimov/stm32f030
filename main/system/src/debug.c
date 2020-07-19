#include "debug.h"
#include "stdlib.h"
#include "string.h"
// void debug(void* adress){
//     typedef struct tagReg{
    
//     char four;
//     char tree;
//     char two;
//     char one;    
// } Reg;
//     Reg* rg=(Reg*)(adress);

//         USART_sendChr(rg->one);
//         USART_sendChr(rg->two);
//         USART_sendChr(rg->tree);
//         USART_sendChr(rg->four);
//     return;
// }

void debug(int adress){
        char* bufferr=(char*)u_malloc(9);
        u_intToHex(adress,bufferr);
        puts(bufferr);
        puts(" - adress\r\n");

        u_intToHex(REGISTER(adress),bufferr);
        puts(bufferr);
        puts(" - Value\r\n");

        u_free(bufferr);
}

void print(int digit)
{
        char* bufferr=(char*)u_malloc(9);
        u_intToHex(digit,bufferr);
        puts("0x");
        puts(bufferr);
        puts("\r\n");
        u_free(bufferr);
}
