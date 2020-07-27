#include "debug.h"
#include "u_stdlib.h"
#include "u_string.h"
#include "USART.h"
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
        char bufferr[9];
        u_intToHex(adress, &bufferr[0]);
        puts(bufferr);
        puts(" - adress\r\n");

        u_intToHex(REGISTER(adress),bufferr);
        puts(bufferr);
        puts(" - Value\r\n");

}

void print(int digit)
{
        char bufferr[9];
        u_intToHex(digit, &bufferr[0]);
        puts("0x");
        puts(bufferr);
        puts("\r\n");
}
