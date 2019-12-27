#include "System.h"
#define FLASH_ACR 0x40022000

void wait(volatile int i){
	while(i>0) {

    		--i;
	}
    	return;
}

void clock(void){

//    	REGISTER(RCC_BASE|RCC_CIR)=0xffffffff;
//	HSE on
  	REGISTER(RCC_BASE|RCC_CR)|=RCC_CR_HSEON;
  	while(!(REGISTER(RCC_BASE|RCC_CR)&(RCC_CR_HSERDY)));

  	REGISTER(FLASH_ACR)|=0x10;
  	REGISTER(FLASH_ACR)&=!0x03;
  	REGISTER(FLASH_ACR)|=0x02;

//  	REGISTER(RCC_BASE|RCC_CFGR)|=0x00000400;

  /*--------- Конфигурируем PLL -------: PLLCLK = HSE(8 МГц) * 9 = 72 MHz */
  //		ResetBit RCC_CFGR, 0x003F0000   @	(PLLSRC | PLLXTPRE | PLLMULL)
//  	REGISTER(RCC_BASE|RCC_CFGR)&=!0x003F0000;
  	REGISTER(RCC_BASE|RCC_CFGR)|=RCC_CFGR_PLLMUL9;

//  	REGISTER(RCC_BASE|RCC_CFGR2)&=0x00010FFF;
//  	REGISTER(RCC_BASE|RCC_CFGR2)|=0x00000670;

  	REGISTER(RCC_BASE|RCC_CR)|=RCC_CR_PLLON;
  	while(!(REGISTER(RCC_BASE|RCC_CR)&(RCC_CR_PLLRDY)));

  	REGISTER(RCC_BASE|RCC_CFGR)&=0x03;
  	REGISTER(RCC_BASE|RCC_CFGR)|=RCC_CFGR_SW_PLL;
  	while(!(REGISTER(RCC_BASE|RCC_CFGR)&(RCC_CFGR_SWS_PLL)));
 	return;
}//Тактирование


void RCC_DeInit(void)
{
  /* Set HSION bit */
  REGISTER(RCC_BASE|RCC_CR) |= (uint32_t)0x00000001;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */

  REGISTER(RCC_BASE|RCC_CFGR) &= (uint32_t)0xF8FF0000;


  /* Reset HSEON, CSSON and PLLON bits */
  REGISTER(RCC_BASE|RCC_CR) &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  REGISTER(RCC_BASE|RCC_CR) &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  REGISTER(RCC_BASE|RCC_CFGR) &= (uint32_t)0xFF80FFFF;

  /* Disable all interrupts and clear pending bits  */
  REGISTER(RCC_BASE|RCC_CIR) = (uint32_t)0x009F0000;

  /* Reset CFGR2 register */
  REGISTER(RCC_BASE|RCC_CFGR2) = (uint32_t)0x00000000;


}














void _RST(void){
  REGISTER(SCB_Base|SCB_AIRCR)= AIRCR_KEY | AIRCR_SYSRESETREQ;
}// Reset - как с кнопки
