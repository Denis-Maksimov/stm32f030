
#include "RCC.h"
#include "Sys_mgr.h" //для синхронизации systick системных часов
/*************************************************************************************************
 * 
 * 
 *                                                                             |\
 *                   |----------------------------------------------------HSE->| \               
                     |       ______                                            |  \
                     |      /     /                                            |   \
 *                   |     / HSI /----\-----------------------------------HSI->|    \
 *                   |    /_____/      \       -----                           |     \
 *                   |     internal     \----*|    |                           |      \----SYSCLCK-->
 *                   |     8MHz               | /2 |\                          |  SW  /
 *                   |                        -----  \                         |     /
 *                   |              _                 \_____| \                |    /
 *                   |             | \                      |  \    ---------  |   /
 *                   |             |  \                     |   |--| PLL1MULL->|  /
 *                   |-------------|   \ -------------------|  /    x4-x9 --   | /
 *           ______  |             |   /                    |_/                |/
 * crystal  /     /  |-------/2----|  /                   PLLSRC       
 * ------->/ HSE /==/              |_/
 *  8MHz  /_____/                PLLXTPRE  
 *                          
 *                          
 *               
 * 
 * 
 * 
 * 
 ***************************************************************************************************
 * 
 *                                            ----
 *                                 |---------| /8 |------> SYSTICK
 *                                 |          ----
 *                                 |------------AHB------> 
 *              ----------------   |      -----------------
 * ---SYSCLCK-->| AHB prescaler |--|----->| APB1 prescaler |
 *              ----------------   |      -----------------
 *                /1.../512        |----->| APB2 prescaler |
 *                                         ----------------
 * 
 * 
 * **************************************************************************************************
 * 
 * 72MHz= HSE/prediv2*PLL2MULL =[prediv1src]= /prediv1 =[PLLsrc]=*PLL1MULL=[SW]
 * 
 *        8     /1     *1                        /1                 *9
 * 
 ***************************************************************************************************/

//-----------------------------------------------------------------

 void set_clock_HSE()
{
    
    //Если внешний кварц отключен
    if(!(REGISTER(RCC_BASE|RCC_CR)&RCC_CR_HSERDY))
    {
        //включаем
        REGISTER(RCC_BASE|RCC_CR) |= RCC_CR_HSEON;
        while (!(REGISTER(RCC_BASE|RCC_CR)&RCC_CR_HSERDY))
        {
            asm("nop");
        }
        
    }
    /* Reset HSEBYP bit */
    REGISTER(RCC_BASE|RCC_CR) &= (uint32_t)0xFFFBFFFF;

    /**************************************
     * магическое тактирование флеша
    ноль циклов ожидания, если 0 < SYSCLK ≤ 24 MHz
    один цикл ожидания, если 24 MHz < SYSCLK ≤ 48 MHz
    два цикла ожидания, если 48 MHz < SYSCLK ≤ 72 MHz
    ***********************************************/
    
  	REGISTER(FLASH_base|FLASH_ACR) &= ~(FLASH_ACR_LATENCY(0x03));
  	REGISTER(FLASH_base|FLASH_ACR) |=  FLASH_ACR_LATENCY(LATENCY_2);
    REGISTER(FLASH_base|FLASH_ACR) |=  FLASH_ACR_PRFTBE;

    //PLLMULL x9 
    REGISTER(RCC_BASE|RCC_CFGR) &= ~RCC_CFGR_PLLMULx(0xf);//0111
    REGISTER(RCC_BASE|RCC_CFGR) |=  RCC_CFGR_PLLMULx(PLLMULL_9);


    //PLLSRC <- PLLXTPRE
   // REGISTER(RCC_BASE|RCC_CFGR) |=  RCC_CFGR_PLLSRC;
    REGISTER(RCC_BASE|RCC_CFGR) |=  RCC_CFGR_PLLSRC;
    //PLLXTPRE <- HSE
    REGISTER(RCC_BASE|RCC_CFGR) &= ~(RCC_CFGR_PLLXTPRE);


    //включаем PLL, если не включен
    if(!(REGISTER(RCC_BASE|RCC_CR)&RCC_CR_PLLRDY)){

        REGISTER(RCC_BASE|RCC_CR) |= RCC_CR_PLLON;
        while (!(REGISTER(RCC_BASE|RCC_CR)&RCC_CR_PLLRDY));
    }

    // AHB/1    
    REGISTER(RCC_BASE|RCC_CFGR) &= ~(RCC_CFGR_AHBPREx(0b1111));
    
    //SW <- PLLx9|PLLSRC << PLLXTPRE << HSE
    REGISTER(RCC_BASE|RCC_CFGR) |= RCC_CFGR_SW_PLL;
    while (!(REGISTER(RCC_BASE|RCC_CFGR) & RCC_CFGR_SWS_PLL));
    __system_clock = 72000000;
    SysTick_set_clock();

 }

//-----------------------------------------------------------------
//TODO: троттлинг должен отключать перифирию
void set_clock_HSI()
{ 
    //Если внутренний кварц отключен
  if(!(REGISTER(RCC_BASE|RCC_CR) & RCC_CR_HSIRDY))
  {
      //включаем
      REGISTER(RCC_BASE|RCC_CR) |= RCC_CR_HSION;
      while (!(REGISTER(RCC_BASE|RCC_CR) & RCC_CR_HSIRDY))
      {
          asm("nop");
      }
      
  }
  //---Flash---
  REGISTER(FLASH_base|FLASH_ACR) &= ~(FLASH_ACR_LATENCY(0x03));
  REGISTER(FLASH_base|FLASH_ACR) |=  FLASH_ACR_LATENCY(LATENCY_0);
  REGISTER(FLASH_base|FLASH_ACR) &= ~(FLASH_ACR_PRFTBE);

  //Перечекаемся на внутренний кварц
  REGISTER(RCC_BASE|RCC_CFGR) &= ~(RCC_CFGR_SW_PLL|RCC_CFGR_SW_HSE);
  while ((REGISTER(RCC_BASE|RCC_CFGR) & (RCC_CFGR_SWS_PLL|RCC_CFGR_SWS_HSE)));
  __system_clock = 8000000;
  SysTick_set_clock();
}
//-----------------------------------------------------------------

/******************************************************************
 * \brief go RCC registers to starting values
******************************************************************/
void RCC_reset(void)
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

  __system_clock = 8000000;
    SysTick_set_clock();
}