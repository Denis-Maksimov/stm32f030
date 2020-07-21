#include "USART.h"





//--------------------------------------------------------------
void USART_DMA_transmit_init(void);
void USART_DMA_recv_init(void* buffer, size_t buf_size);
void USART_init(void* buffer, size_t buf_size){

    //-- clock --
    REGISTER(RCC_BASE|RCC_APB2ENR) |= (RCC_APB2ENR_USART1EN);
    REGISTER(RCC_BASE|RCC_AHBENR) |= RCC_AHBENR_DMA1EN;
    
    //-- pins --
    pin_init(9,'A',AF_PUSH_PULL_OUTPUT_50MHZ);
    pin_init(10,'A',HI_Z_INPUT);

    //-- битрейт --
    REGISTER(USART1|USART_BRR)=0x1d4c;

  //-- usart & transmition & receive enable --
    REGISTER(USART1|USART_CR1) |= (USART_CR1_TE);
    REGISTER(USART1|USART_CR1) |= (USART_CR1_RE);
    REGISTER(USART1|USART_CR1) |= (USART_CR1_UE);

    //-- DMA
    USART_DMA_transmit_init();
    
    REGISTER(USART1|USART_CR3) |= (USART_CR2_DMAT); //transmit

    if(buffer){
      USART_DMA_recv_init(buffer, buf_size);
      REGISTER(USART1|USART_CR2) |= (USART_CR2_DMAR); //receive
    }

  

    return;
}

//--------------------------------------------------------------

void USART_DMA_transmit_init(void){

    REGISTER(DMA1_BASE|DMA_CCR4) &=~ DMA_CCRx_EN;
    //-- general settings --
      //periph adr
      REGISTER(DMA1_BASE|DMA_CPAR4) = (USART1 + USART_DR); 
      //interrupt
      // REGISTER(DMA1_BASE|DMA_CCR4) |= DMA_CCRx_TCIE; 
      //MEM->PERIPH
      REGISTER(DMA1_BASE|DMA_CCR4) |= DMA_CCRx_DIR; 
      //reset CYCLiC
      REGISTER(DMA1_BASE|DMA_CCR4) &= ~(DMA_CCRx_CIRC); 

    //-- perph settings --
      //increment
      REGISTER(DMA1_BASE|DMA_CCR4) &= ~(DMA_CCRx_PINC);
      //size
      REGISTER(DMA1_BASE|DMA_CCR4) &= ~(DMA_CCRx_PSIZE(0b11));
      REGISTER(DMA1_BASE|DMA_CCR4) |= DMA_CCRx_PSIZE(PSIZE_8b);

    //-- RAM memory settings --
    //increment
    REGISTER(DMA1_BASE|DMA_CCR4) |= DMA_CCRx_MINC;
    //size
    REGISTER(DMA1_BASE|DMA_CCR4) &= ~(DMA_CCRx_MSIZE(0b11));
    REGISTER(DMA1_BASE|DMA_CCR4) |= DMA_CCRx_MSIZE(MSIZE_8b);

    //-- Enable DMA --
   // REGISTER(DMA1_BASE|DMA_CCR4) |= DMA_CCRx_EN;
    return;
}
//--------------------------------------------------------------

void USART_DMA_recv_init(void* buffer, size_t buf_size)
{

    REGISTER(DMA1_BASE|DMA_CCR5) &=~ DMA_CCRx_EN;
    //-- general settings --
      //periph adr
      REGISTER(DMA1_BASE|DMA_CPAR5) = (USART1 + USART_DR); 
      //interrupt
      // REGISTER(DMA1_BASE|DMA_CCR4) |= DMA_CCRx_TCIE; 
      //MEM<-PERIPH
      REGISTER(DMA1_BASE|DMA_CCR5) &= ~(DMA_CCRx_DIR); 
      //CYCLiC
      REGISTER(DMA1_BASE|DMA_CCR5) |= (DMA_CCRx_CIRC); 

    //-- perph settings --
      //increment
      REGISTER(DMA1_BASE|DMA_CCR5) &= ~(DMA_CCRx_PINC);
      //size
      REGISTER(DMA1_BASE|DMA_CCR5) &= ~(DMA_CCRx_PSIZE(0b11));
      REGISTER(DMA1_BASE|DMA_CCR5) |= DMA_CCRx_PSIZE(PSIZE_8b);

    //-- RAM memory settings --
    //increment
    REGISTER(DMA1_BASE|DMA_CCR5) |= DMA_CCRx_MINC;
    //size
    REGISTER(DMA1_BASE|DMA_CCR5) &= ~(DMA_CCRx_MSIZE(0b11));
    REGISTER(DMA1_BASE|DMA_CCR5) |= DMA_CCRx_MSIZE(MSIZE_8b);

    //-- set adress & size bufer
      REGISTER(DMA1_BASE|DMA_CMAR5) = (uint32_t)buffer;
      REGISTER(DMA1_BASE|DMA_CNDTR5) = buf_size;
    //-- Enable DMA --
    REGISTER(DMA1_BASE|DMA_CCR5) |= DMA_CCRx_EN;
    return;
}
//--------------------------------------------------------------

int write_DMA_USART(const char* buffer, uint16_t buf_size){

    //-- DMA employment check 
    if(REGISTER(DMA1_BASE|DMA_CNDTR4)){
      return 1; 
    }

    //-- freeze DMA
    REGISTER(DMA1_BASE|DMA_CCR4) &=~ DMA_CCRx_EN;

      //-- set adress & size bufer
      REGISTER(DMA1_BASE|DMA_CMAR4) = (uint32_t)buffer;
      REGISTER(DMA1_BASE|DMA_CNDTR4) = buf_size;
    
      //-- clear flag Channel 4 - transfer complete clear
      REGISTER(DMA1_BASE|DMA_IFCR) |= DMA_IFCR_CTCIF(4);

    //-- resume DMA
    REGISTER(DMA1_BASE|DMA_CCR4) |= DMA_CCRx_EN;


    return 0;
}


//---------------------------------

/*blocking func*/
void puts(const char* buffer){

    while(write_DMA_USART(buffer, ((uint16_t)(u_strlen(buffer)))));

    return;
}

//------------------------------------

void DMA1_Channel4_IRQHandler(){
  REGISTER(DMA1_BASE|DMA_CCR4) &= ~DMA_CCRx_TCIE; //
   REGISTER(DMA1_BASE|DMA_IFCR) |= DMA_IFCR_CTCIF(4);
  USART_sendChr('*');

  return;
}
/***** usage *****

int main(){

    USART_init();
    
      puts("Hello, world, from DMA!");

    return 0;
}
******************/




//--------------------------------------------------------------

/***************************
 * obsolete code block (using CPU)   *
***************************/

void USART_sendChr(char Ch){
  //  REGISTER(GPIOC|GPIOx_BRR) = (1<<13);
    while(!(REGISTER(USART1|USART_SR)&(USART_SR_TXE)));
    REGISTER(USART1|USART_DR)=Ch;
  //  REGISTER(GPIOC|GPIOx_BSRR) = (1<<13);
    return;
}

//--------------------------------------------------------------

void USART_sendString(char* STR){
    int i=0;
    while(STR[i]!=0){
        USART_sendChr(STR[i]);
        i++;
    }
}

//--------------------------------------------------------------

int USART_sendStringi(char* STR,int i){
    if(i==0){return i;}
    if(!(REGISTER(USART1|USART_SR)&(USART_SR_TXE))){return i;}
    if(STR[i+1]==0){i=0;return i;}
    REGISTER(USART1|USART_DR)=STR[i-1];
    return i+1;
}

//--------------------------------------------------------------

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
