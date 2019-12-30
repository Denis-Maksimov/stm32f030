#include "debug.h"

void debug(void* adress){
    typedef struct tagReg{
    
    char four;
    char tree;
    char two;
    char one;    
} Reg;
    Reg* rg=(Reg*)(adress);

        USART_sendChr(rg->one);
        USART_sendChr(rg->two);
        USART_sendChr(rg->tree);
        USART_sendChr(rg->four);
    return;
}
