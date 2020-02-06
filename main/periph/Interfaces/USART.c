#include "USART.h"

void USART_init(void){
    //clock
    REGISTER(RCC_BASE|RCC_APB2ENR) |= (RCC_APB2ENR_USART1EN)|(RCC_APB2ENR_IOPAEN)|(RCC_APB2ENR_AFIOEN);
    //pins
 //   GPIOval* GPIO_a=(GPIOval*)(GPIOA|GPIOx_CRH); //GPIOC high's pins select

      pin_init(9,'a',AF_PUSH_PULL_OUTPUT_50MHZ);
      pin_init(10,'a',HI_Z_INPUT);
//	    GPIO_a->pin9=AF_PUSH_PULL_OUTPUT_50MHZ;
//	    GPIO_a->pin10=HI_Z_INPUT;
  //  REGISTER(GPIOA|GPIOx_CRH) &= !0x0FF0;
  //  REGISTER(GPIOA|GPIOx_CRH) |= 0x04B0;
    //usart
  //  REGISTER(USART1|USART_BRR)=0x341;
    REGISTER(USART1|USART_BRR)=0x1d4c;

    REGISTER(USART1|USART_CR1)|=(USART_CR1_UE)| \
                                (USART_CR1_TE);

}

void USART_sendChr(char Ch){
  //  REGISTER(GPIOC|GPIOx_BRR) = (1<<13);
    while(!(REGISTER(USART1|USART_SR)&(USART_SR_TXE)));
    REGISTER(USART1|USART_DR)=Ch;
  //  REGISTER(GPIOC|GPIOx_BSRR) = (1<<13);
    return;
}

void USART_sendString(char* STR){
    int i=0;
    while(STR[i]!=0){
        USART_sendChr(STR[i]);
        i++;
    }
}

int USART_sendStringi(char* STR,int i){
    if(i==0){return i;}
    if(!(REGISTER(USART1|USART_SR)&(USART_SR_TXE))){return i;}
    if(STR[i+1]==0){i=0;return i;}
    REGISTER(USART1|USART_DR)=STR[i-1];
    return i+1;
}



/*
~~  Комментарии  ~~
 +                 -| Таблица |-
		|-----------------------------------------------
		| 	baud Rate ~= частота/скорость		            |
		|-----------------------------------------------
		|  частота	|  скорость 	|	BRR	  |
    |---------------------------------
		|	72 МГц	  |	9600	      |	1d4c	|
		|	24 МГц	  |	9600	      |	9c4	  |
		|	8  МГц	  |	9600	      |	341	  |
		|-----------------------------------------------|
 +  -----------------------------------------------------------------------------------------
  USART1_CR1,
  0x2000 - Включить USART									0x0040 - TCIE по завершению передачи
  0x1000 - 9 битовая передача								0x0020 - RXNEIE
  0x0800 - Просыпаться по адресу(иначе по линии idle)		0x0010 - IDLEIE
  0x0400 - Контроль паритета вкл							0x0008 - вкл TX передачу
  0x0200 - режим паритета 0-по событию 1 - odd?			    0x0004 - вкл RX приём
  0x0100 - вкл PE прерывание PE-бит в SR-регистре			0x0002 - RWU: Receiver wakeup
  0x0080 - вкл TXE прерывание TXE-бит в SR-регистре		    0x0001 - SBK: Send break
 ---------------------------------------------------------------------------------------------*/
