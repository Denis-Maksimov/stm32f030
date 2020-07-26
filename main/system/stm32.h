#ifndef STM32_H
#define STM32_H

/******************************************************************
**  Reset and clock control (RCC) Register
*******************************************************************
+ */
    #define RCC_BASE                0x40021000
    
    #define RCC_CR  		        0x00 //reset value 0x00000083
        #define RCC_CR_HSION  		    0x1<<0
        #define RCC_CR_HSIRDY  		    0x1<<1
        #define RCC_CR_HSITRIM_5b(a)    ((a)<<3)
        #define RCC_CR_HSICALL_8b(a)    ((a)<<8)
        #define RCC_CR_HSEON  		    0x1<<16
        #define RCC_CR_HSERDY  		    0x1<<17
        #define RCC_CR_HSEBYP 		    0x1<<18
        #define RCC_CR_CSSON 		    0x1<<19
        #define RCC_CR_PLLON 		    0x1<<24
        #define RCC_CR_PLLRDY 		    0x1<<25

	#define RCC_CFGR  		        0x04
  	      	#define RCC_CFGR_SW_HSE     0x01
      	  	#define RCC_CFGR_SW_PLL     0x02
        	#define RCC_CFGR_SWS_HSE    0x04
        	#define RCC_CFGR_SWS_PLL    0x08
        //AHB
            #define RCC_CFGR_AHBPREx(a) (((a)&0b1111)<<4)
                #define AHBPRE_1    0b0000
                #define AHBPRE_2    0b1000
                #define AHBPRE_4    0b1001
                #define AHBPRE_8    0b1010
                #define AHBPRE_16    0b1011
                #define AHBPRE_64    0b1100
                #define AHBPRE_128    0b1101
                #define AHBPRE_256    0b1110
                #define AHBPRE_512    0b1111

        	#define RCC_CFGR_AHBPRE_2   0x80
        	#define RCC_CFGR_AHBPRE_4   0x90
        	#define RCC_CFGR_AHBPRE_8   0xA0
        	#define RCC_CFGR_AHBPRE_16  0xB0
        	#define RCC_CFGR_AHBPRE_64  0xC0
        	#define RCC_CFGR_AHBPRE_128 0xD0
        	#define RCC_CFGR_AHBPRE_256 0xE0
        	#define RCC_CFGR_AHBPRE_512 0xF0
        //APB
        	#define RCC_CFGR_APB1PRE_2  0x0400
        	#define RCC_CFGR_APB1PRE_4  0x0500
        	#define RCC_CFGR_APB1PRE_8  0x0600
        	#define RCC_CFGR_APB1PRE_16 0x0700
        //APB2
        	#define RCC_CFGR_APB2PRE_2  0x2000
        	#define RCC_CFGR_APB2PRE_4  0x2800
        	#define RCC_CFGR_APB2PRE_8  0x3000
        	#define RCC_CFGR_APB2PRE_16 0x3800
        //ADC
        	#define RCC_CFGR_ADCPRE_4   0x4000
        	#define RCC_CFGR_ADCPRE_6   0x8000
        	#define RCC_CFGR_ADCPRE_8   0xC000
        //
        	#define RCC_CFGR_PLLSRC     0x1<<16 //< 0-HSI/2, 1-HSE
		#define RCC_CFGR_PLLXTPRE       0x1<<17 //< 0-HSE,   1-HSE/2
        #define RCC_CFGR_PLLMULx(a)  (((a)&0b1111)<<18)
		#define RCC_CFGR_PLLMUL4    0x080000
		#define RCC_CFGR_PLLMUL5    0x0c0000
		#define RCC_CFGR_PLLMUL6    0x100000
		#define RCC_CFGR_PLLMUL7    0x140000
		#define RCC_CFGR_PLLMUL8    0x180000
		#define RCC_CFGR_PLLMUL9    0x1c0000
		#define RCC_CFGR_PLLMUL6_5  0x240000
        #define PLLMULL_2           0b0000
        #define PLLMULL_3           0b0001
        #define PLLMULL_4           0b0010
        #define PLLMULL_5           0b0011
        #define PLLMULL_6           0b0100
        #define PLLMULL_7           0b0101
        #define PLLMULL_8           0b0110
        #define PLLMULL_9           0b0111
        #define PLLMULL_10          0b1000
        #define PLLMULL_11          0b1001
        #define PLLMULL_12          0b1010
        #define PLLMULL_13          0b1011
        #define PLLMULL_14          0b1100
        #define PLLMULL_15          0b1101
        #define PLLMULL_16          0b1110


	#define RCC_CFGR2  	    0x2C
	#define RCC_CIR 		0x08

    #define RCC_AHBENR      0x14
        #define RCC_AHBENR_DMA1EN       0x01<<0
        #define RCC_AHBENR_DMA2EN       0x01<<1
        #define RCC_AHBENR_SRAMEN       0x01<<2
        #define RCC_AHBENR_FLITFEN      0x01<<4
        #define RCC_AHBENR_CRCEN        0x01<<6 //< CRC подсчёт хэш-суммы
        #define RCC_AHBENR_FSMCEN       0x01<<8
        #define RCC_AHBENR_SDIOEN       0x01<<10

	#define RCC_APB2ENR 	0x18
        #define RCC_APB2ENR_AFIOEN      0x0001
        #define RCC_APB2ENR_IOPAEN      0x0004
        #define RCC_APB2ENR_IOPBEN      0x0008
        #define RCC_APB2ENR_IOPCEN      0x0010
        #define RCC_APB2ENR_IOPDEN      0x0020
        #define RCC_APB2ENR_IOPEEN      0x0040
        #define RCC_APB2ENR_IOPFEN      0x0080
        #define RCC_APB2ENR_IOPGEN      0x0100
        #define RCC_APB2ENR_ADC1EN      0x0200
        #define RCC_APB2ENR_ADC2EN      0x0400
        #define RCC_APB2ENR_TIM1EN      0x0800
        #define RCC_APB2ENR_SPI1EN      0x1000
        #define RCC_APB2ENR_TIM8EN      0x2000
        #define RCC_APB2ENR_USART1EN    0x4000
        #define RCC_APB2ENR_ADC3EN      0x8000

	
    #define SCB_Base 		0xE000ED00
    #define SCB_VTOR 		0x08
    #define FLASH_BASE     0x08000000
    //**************************
  

    #define RCC_APB1ENR 	0x1C
        #define RCC_APB1_TIM2EN      (0x01<<0)
        #define RCC_APB1_TIM3EN      (0x01<<1)
        #define RCC_APB1_TIM4EN      (0x01<<2)
        #define RCC_APB1_TIM5EN      (0x01<<3)
        #define RCC_APB1_TIM6EN      (0x01<<4)
        #define RCC_APB1_TIM7EN      (0x01<<5)
        #define RCC_APB1_WWDGEN      (0x01<<11)
        #define RCC_APB1_SPI2EN      (0x01<<14)
        #define RCC_APB1_SPI3EN      (0x01<<15)
        #define RCC_APB1_USART2EN    (0x01<<17)
        #define RCC_APB1_USART3EN    (0x01<<18)
        #define RCC_APB1_USART4EN    (0x01<<19)
        #define RCC_APB1_USART5EN    (0x01<<20)
        #define RCC_APB1_I2C1EN      (0x01<<21)
        #define RCC_APB1_I2C2EN      (0x01<<22)
        #define RCC_APB1_USBEN       (0x01<<23)
        #define RCC_APB1_CANEN       (0x01<<25)
        #define RCC_APB1_BKPEN       (0x01<<27)
        #define RCC_APB1_PWREN       (0x01<<28)
        #define RCC_APB1_DAC         (0x01<<29)

/******************************************************************
**  Flash memory interface registers
*******************************************************************
+ */
    #define FLASH_base          0x40022000
   
    #define FLASH_ACR           0x00                    // Flash access control register 
        #define FLASH_ACR_LATENCY(a)   ((0b111&a)<<0)   // These bits represent the ratio of the SYSCLK (system clock) period to the Flash access time
            #define LATENCY_0           0b000           // Zero wait state, if 0 < SYSCLK≤  24  MHz
            #define LATENCY_1           0b001           // One wait state, if 24 MHz < SYSCLK ≤  48  MHz
            #define LATENCY_2           0b010           // Two wait states, if 48 MHz < SYSCLK ≤ 72 MHz
        #define FLASH_ACR_HLFCYA        (0x01<<3)       // Flash half cycle access enable
        #define FLASH_ACR_PRFTBE        (0x01<<4)       // Prefetch buffer enable
        #define FLASH_ACR_PRFTBS        (0x01<<5)       // Prefetch buffer status
        
    #define FLASH_KEYR          0x04                    // These register represent the keys to unlock the FPEC
    
    #define FLASH_OPTKEYR       0x08                    // These register represent the keys to unlock the OPTWRE.
   
    #define FLASH_SR            0x0C                    // Flash status register
        #define FLASH_SR_BSY            (0x01<<0)       // This indicates that a Flash operation is in progress
        #define FLASH_SR_PGERR          (0x01<<2)       // Set by hardware when an address to be programmed contains a value different from '0xFFFF' before programming
        #define FLASH_SR_WRPRTERR       (0x01<<4)       // Set by hardware when programming a write-protected address of the Flash memory.
        #define FLASH_SR_EOP            (0x01<<5)       // Set by hardware when a Flash operation (programming / erase) is completed.
    
    #define FLASH_CR            0x10
        #define FLASH_CR_PG             (0x01<<0)       // Flash programming chosen.
        #define FLASH_CR_PER            (0x01<<1)       // Page erase.
        #define FLASH_CR_MER            (0x01<<2)       // Erase of all user pages chosen.
        #define FLASH_CR_OPTPG          (0x01<<4)       // Option byte programming chosen.
        #define FLASH_CR_OPTER          (0x01<<5)       // Option byte erase
        #define FLASH_CR_START          (0x01<<6)       // This bit triggers an ERASE operation when set. This bit is set only by software and reset when the BSY bit is reset.
        #define FLASH_CR_LOCK           (0x01<<7)       // Write to 1 only. When it is set, it indicates that the FPEC and FLASH_CR are locked. This bit is reset by hardware after detecting the unlock sequence.In the event of unsuccessful unlock operation, this bit remains set until the next reset.
        #define FLASH_CR_OPTWRE         (0x01<<9)       // When set, the option bytes can be programmed. This bit is set on writing the correct key sequence to the FLASH_OPTKEYR register.
        #define FLASH_CR_ERRIE          (0x01<<10)      // This bit enables the interrupt generation on an FPEC error (when PGERR / WRPRTERR are set in the FLASH_SR register)
        #define FLASH_CR_EOPIE          (0x01<<12)      // This bit enables the interrupt generation when the EOP bit in the FLASH_SR register goes to 1.

    #define FLASH_AR            0x14                    // Chooses the address to program when programming is selected, or a page to erase when Page Erase is selected.Note:   Write access to this register is blocked when the BSY bit in the FLASH_SR register is set
    
    #define FLASH_OBR           0x1C                    // Option byte register
        #define FLASH_OBR_OPTERR        (0x01<<0)       // Option byte error
        #define FLASH_OBR_RDPRT         (0x01<<1)       // Read protection
        #define FLASH_OBR_USER(a)   ((0b11111111&a)<<2) // This contains the user option byte loaded by the OBL.
            #define USER_WDG_SW         0b001
            #define USER_nRST_STOP      0b010
            #define USER_nRST_STDBY     0b100

        #define FLASH_OBR_DATA0(a)   ((0b11111111&a)<<10)
        #define FLASH_OBR_DATA1(a)   ((0b11111111&a)<<18)
    ///::TODO::

    
    #define FLASH_WRPR          0x20                    // Write protection register 

/******************************************************************
**  Information block
*******************************************************************
+ */
    #define SYS_MEM_BASE        0x1FFFF000
    
    #define OPTION_BYTES_1        0x1FFFF800
        #define OPTION_BYTES_1_RDP(a)          ((0b11111111&a)<<0)
        #define OPTION_BYTES_1_nRDP(a)         ((0b11111111&a)<<8)
        #define OPTION_BYTES_1_WDG_SW           (0x01<<16)
        #define OPTION_BYTES_1_nRST_STOP        (0x01<<17)
        #define OPTION_BYTES_1_nRST_STDBY       (0x01<<18)
        #define OPTION_BYTES_1_USER(a)         ((0b11111111&a)<<16)
        #define OPTION_BYTES_1_nUSER(a)        ((0b11111111&a)<<24)
    #define OPTION_BYTES_2        0x1FFFF804 // Datax
        #define OPTION_BYTES_2_DATA0(a)          ((0b11111111&a)<<0)
        #define OPTION_BYTES_2_nDATA0(a)         ((0b11111111&a)<<8)
        #define OPTION_BYTES_2_DATA1(a)         ((0b11111111&a)<<16)
        #define OPTION_BYTES_2_nDATA1(a)        ((0b11111111&a)<<24)
    #define OPTION_BYTES_3(n,w)        (0x1FFFF808+n*4+w) // Flash memory write protection option bytes n=0 for w=0,1 & n=1 for wrp=2,3 ;Write-protects pages 0 to 31

    
/******************************************************************
**  CRC calculation unit
*******************************************************************
+ */
    #define CRC_BASE        0x40023000

    #define CRC_DR          0x00 //Data register
    #define CRC_IDR         0x04 //Independent data register
    #define CRC_CR          0x08 //Control register
        #define CRC_CR_RESET    0x01<0 // сброс в 0xFFFF FFFF хэшсуммы (DR)


/******************************************************************
**  System control block
*******************************************************************
+ */

    #define SCB_ACTLR       0xE000E008    //only for STM32L and STM32F2 seriwes  
    #define SCB_Base 		0xE000ED00
    #define SCB_CPUID       0x00 //The CPUID register contains the processor part number, version, and implementation information.
    #define SCB_ICSR        0x04 //Interrupt control and state register
        #define SCB_ICSR_VECTACTIVE(a)          ((0x1FF&a)<<0)
        #define SCB_ICSR_RETOBASE               (0x1<<11)
        #define SCB_ICSR_ECTPENDING(a)          ((0x1FF&a)<<12)
        #define SCB_ICSR_ISRPENDING             (0x1<<22)
        #define SCB_ICSR_PENDSTCLR             (0x1<<25) //SysTick exception clear-pending bit.
        #define SCB_ICSR_PENDSTSET             (0x1<<26) //SysTick exception set-pending bit
        #define SCB_ICSR_PENDSVCLR             (0x1<<27) //PendSV clear-pending bit.
        #define SCB_ICSR_PENDSVSET             (0x1<<28) //PendSV set-pending bit.
        #define SCB_ICSR_NMIPENDSET             (0x1<<31) //NMI set-pending bit.



    #define SCB_VTOR 		0x08//Vector table offset register
    #define SCB_SCR         0x10//System control register
        #define SCB_SCR_SLEEPONEXIT 0x02
        #define SCB_SCR_SLEEPDEEP   0x03
        #define SCB_SCR_SEVEONPEND 0x10 //Send Event on Pending bit
    #define SCB_CCR         0x10//Configuration and control register

    #define SCB_SHPR1      0x18 //System handler priority register 1
    #define SCB_SHPR2      0x1C //System handler priority register 2
    #define SCB_SHPR3      0x20 //System handler priority register 3
    #define SCB_SHCSR      0x24 //System handler control and state register

    #define SCB_HFSR        0x2C //HFSR Configurable fault status register
        #define SCB_HFSR_VECTTBL    (0x01<<1)   //: Vector table hard fault
        #define SCB_HFSR_FORCED     (0x01<<30)  //Forced hard fault
        
	#define SCB_CFSR        0x28 //CFSR Configurable fault status register
        //-- MMFSR
        ///TODO:
        //-- BFSR
        #define SCB_CFSR_IBUSERR        (0x01<<8)       //Instruction bus error
        #define SCB_CFSR_PRECISERR      (0x01<<9)       //Precise data bus errorWhen
        #define SCB_CFSR_IMPRECISERR    (0x01<<10)      //Imprecise data bus error
        #define SCB_CFSR_UNSTKERR       (0x01<<11)      //Bus fault on unstacking for a return from exception
        #define SCB_CFSR_STKERR         (0x01<<12)      //Bus fault on stacking for exception entry

	#define SCB_BFAR        0x38 //BFAR - адрес точного отказа
	#define SCB_DFSR        0x30 //DFSR
    #define SCB_SCB_MMFAR   0x34 //Memory management fault address register

	#define SCB_AFSR  0x3C //AFSR  ???
    #define SCB_AIRCR 0x0C //Application interrupt and reset control register
        #define AIRCR_KEY         0x05FA0000 //ключ для доступа к регистру
        #define AIRCR_SYSRESETREQ 0x04      //софтварный reset
    #define FLASH_BASE     0x08000000
    #define RAM_BASE       0x20000000

/******************************************************************
**  System timer
*******************************************************************
+ */        
    #define SysTick_BASE 0xE000E010
    #define SysTick_CTRL 0x00
        #define SysTick_ENABLE 0x0001
        #define SysTick_TICKINT 0x02 // SysTick разрешение запроса на исключение
        #define SysTick_CLKSOURCE 0x04 // Clock source selection - 0: AHB/8  1:AHB
        #define SysTick_COUNTFLAG 0x00010000 // доходил до нуля?
    #define SysTick_LOAD 0x04 //со скольки считать
    #define SysTick_VAL 0x08 // текущее значение
    #define SysTick_CALIB 0x0C

/******************************************************************
**  Memory protection
*******************************************************************
+ */  
/******************************************************************
**  General-purpose Timers 2-5
*******************************************************************
+ */
    #define TIM2_BASE      0x40000000
    #define TIM3_BASE      0x40000400
    #define TIM4_BASE      0x40000800
    #define TIM5_BASE      0x40000C00

    #define TIMx_CR1        0x00
        #define TIMx_CR1_CEN    (0x01<<0)   //Counter enable
        #define TIMx_CR1_UDIS   (0x01<<1)   // Update disable -  enable/disable UEV event generation.
        #define TIMx_CR1_URS    (0x01<<2)   // Update request source
        #define TIMx_CR1_OPM    (0x01<<3)   // One-pulse mode
        #define TIMx_CR1_DIR    (0x01<<4)   // 0-up,1-down
        #define TIMx_CR1_CMS(a)     ((0b11&a)<<5)//Center-aligned mode selection
            #define CMS_EDGE_AM     0b00    
            #define CMS_CENTER_AM1  0b01
            #define CMS_CENTER_AM2  0b10
            #define CMS_CENTER_AM3  0b11
        #define TIMx_CR1_ARPE   (0x80<<7) //auto reload enable
        #define TIMx_CR1_CKD(a)     ((0b11&a)<<8)//Clock division
             #define CKD_tDTS_1     0b00 //tDTS=tCK_INT
             #define CKD_tDTS_2     0b01 //tDTS=tCK_INT*2
             #define CKD_tDTS_4     0b10 //tDTS=tCK_INT*4

    #define TIMx_CR2        0x04
        #define TIMx_CR2_CCDS    (0x01<<3) // Capture-Compare DMA selection 0-snt when CCx evnt occurs; 1 - when updt evnt occurs
        #define TIMx_CR2_MMS(a)     ((0b111&a)<<4)//master mode sellection
            #define MMS_RST     0b000 //Reset
            #define MMS_EN      0b001 //Enable
            #define MMS_UPD     0b010 //Update
            #define MMS_CMPP     0b000 //Compare-Pulse
            #define MMS_OC1REF   0b100 //OC1REF signal is used as trigger output (TRGO)
            #define MMS_OC2REF   0b101 //OC2REF signal is used as trigger output (TRGO)
            #define MMS_OC3REF   0b110 //OC3REF signal is used as trigger output (TRGO)
            #define MMS_OC4REF   0b111 //OC4REF signal is used as trigger output (TRGO)
        #define TIMx_CR2_TI1S   (0x01<<3) //0: TI1 Input = TIMx_CH1 pin; 1: TI1 Input = (TIMx_CH1 ^ TIMx_CH2 ^ TIMx_CH3) pins

    #define TIMx_SMCR       0x08    //slave mode control register 
        #define TIMx_SMCR_SMS(a)   ((0b111&a)<<0)
            #define SMS_DISABLE     0b000
            #define SMS_MODE1       0b001 //Encoder mode 1 - Counter counts up/down on TI2FP1 edge depending on TI1FP2 level.
            #define SMS_MODE2       0b010 //Encoder mode 2 - Counter counts up/down on TI1FP2 edge depending on TI2FP1 level
            #define SMS_MODE3       0b011 //Encoder mode 3 - Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input
            #define SMS_RESET_MODE  0b100 //Reset Mode - Rising edge of the selected trigger input (TRGI) reinitializes the counter and generates an update of the registers
            #define SMS_GATED_MODE  0b101 //Gated Mode - The counter clock is enabled when the trigger input (TRGI) is high. The counter stops (but is not reset) as soon as the trigger becomes low. Both start and stop of the counter are controlled
            #define SMS_TRIG_MODE   0b110 //Trigger Mode - The counter starts at a rising edge of the trigger TRGI (but it is not reset). Only the start of the counter is controlled
            #define SMS_EX_CLK_MODE 0b111 //External Clock Mode 1 - Rising edges of the selected trigger (TRGI) clock the counter.
        #define TIMx_SMCR_TS(a)    ((0b111&a)<<4)
        #define TIMx_SMCR_MSM       (0x01<<7)
        #define TIMx_SMCR_ETF(a)    ((0b1111&a)<<8)
        #define TIMx_SMCR_ETPS(a)    ((0b11&a)<<12)
        #define TIMx_SMCR_ECE       (0x01<<14)
        #define TIMx_SMCR_ETP       (0x01<<15)

    #define TIMx_DIER       0x0C    //TIMx DMA/Interrupt enable register
        //--interrups--
        #define TIMx_DIER_UIE     (0x01<<0)
        #define TIMx_DIER_CC1IE   (0x01<<1)
        #define TIMx_DIER_CC2IE   (0x01<<2)
        #define TIMx_DIER_CC3IE   (0x01<<3)
        #define TIMx_DIER_CC4IE   (0x01<<4)
        #define TIMx_DIER_TIE     (0x01<<6)
        //--DMA--
        #define TIMx_DIER_UDE     (0x01<<8)
        #define TIMx_DIER_CC1DE   (0x01<<9)
        #define TIMx_DIER_CC2DE   (0x01<<10)
        #define TIMx_DIER_CC3DE   (0x01<<11)
        #define TIMx_DIER_CC4DE   (0x01<<12)
        #define TIMx_DIER_TDE     (0x01<<14)

    #define TIMx_SR         0x10        //статус 
        #define TIMx_SR_UIF       (0x01<<0) //Update interrupt flag
        #define TIMx_SR_CC1IF     (0x01<<1) //Capture/compare 1 interrupt flag
        #define TIMx_SR_CC2IF     (0x01<<2) //Capture/compare 2 interrupt flag
        #define TIMx_SR_CC3IF     (0x01<<3) //Capture/compare 3 interrupt flag
        #define TIMx_SR_CC4IF     (0x01<<4) //Capture/compare 4 interrupt flag
        #define TIMx_SR_TIF       (0x01<<6) //Trigger interrupt flag
        #define TIMx_SR_CC1OF     (0x01<<9) //Capture/compare 1 overcapture flag
        #define TIMx_SR_CC2OF     (0x01<<10) //Capture/compare 2 overcapture flag
        #define TIMx_SR_CC3OF     (0x01<<11) //Capture/compare 3 overcapture flag
        #define TIMx_SR_CC4OF     (0x01<<12) //Capture/compare 4 overcapture flag

    #define TIMx_EGR        0x14        //event generation register

    //<< capture/compare mode register 1 (1,2 chanel's)>>
    #define TIMx_CCMR1     0x18         
        //--Input mode--
        #define TIMx_CCMR1_CC1S(a)     ((0b11&a)<<0)//Capture/Compare 1 selection
            #define CC1S_OUT      0x00    //00: CC1 channel is configured as output
            #define CC1S_IN_TI1     0x01    //01: CC1 channel is configured as input  IC1 is mapped on TI1
            #define CC1S_IN_TI2     0x02    //10: CC1 channel is configured as input  IC1 is mapped on TI2
            #define CC1S_IN_TRC  0x03       //11: CC1 channel is configured as input  IC1 is mapped on TRC. 
                                    //This mode is working only if
                                    //an internal trigger input is selected through TS bit (TIMx_SMCR register)
        
        #define TIMx_CCMR1_IC1PSC(a)     ((0b11&a)<<2) //Input capture 1 prescale
            #define IC1PSC_0    0b00 //no prescaller
            #define IC1PSC_2    0b01 //capture is done once every 2 events
            #define IC1PSC_4    0b10 //capture is done once every 4 events
            #define IC1PSC_8    0b11 //capture is done once every 8 events

        #define TIMx_CCMR1_IC1F(a)     ((0b1111&a)<<3) //Input capture 1 filter
            // #define IC1F_0    0b0000
            // #define IC1F_2    0b0001
            // #define IC1F_4    0b0010
            // #define IC1F_8    0b0011
            // #define IC1F_6    0b0100

        #define TIMx_CCMR1_CC2S(a)     ((0b11&a)<<8)//Capture/Compare 1 selection
            #define CC2S_OUT      0x00    //00: CC1 channel is configured as output
            #define CC2S_IN_TI1     0x01    //01: CC1 channel is configured as input  IC1 is mapped on TI1
            #define CC2S_IN_TI2     0x02    //10: CC1 channel is configured as input  IC1 is mapped on TI2
            #define CC2S_IN_TRC  0x03    //11: CC1 channel is configured as input  IC1 is mapped on TRC. 
                                    //This mode is working only if
                                    //an internal trigger input is selected through TS bit (TIMx_SMCR register)

        #define TIMx_CCMR1_IC2PSC(a)     ((0b11&a)<<10) //Input capture 1 prescale
            #define IC2PSC_0    0b00 //no prescaller
            #define IC2PSC_2    0b01 //capture is done once every 2 events
            #define IC2PSC_4    0b10 //capture is done once every 4 events
            #define IC2PSC_8    0b11 //capture is done once every 8 events

        #define TIMx_CCMR1_IC2F(a)     ((0b1111&a)<<12) //Input capture 2 filter
        //--output mode--
        #define TIMx_CCMR1_OC1FE     (0x01<<2) // Output compare 1 fast enable
        #define TIMx_CCMR1_OC1PE     (0x01<<3) // Output compare 1 preload enable
        #define TIMx_CCMR1_OC1M(a)   ((0b111&a)<<4) // Output compare 1 mode
            #define OC1M_FROZEN             0b000
            #define OC1M_HI_LVL_MATCH       0b001
            #define OC1M_LOW_LVL_MATCH      0b010
            #define OC1M_TOOGLE             0b011 //OC1REF toggles when TIMx_CNT=TIMx_CCR1
            #define OC1M_FORCED_LOW         0b100
            #define OC1M_FORCED_HI          0b101
            #define OC1M_PWD1               0b110 //In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0) as long as
            #define OC1M_PWD2               0b111 //In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1 else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else inactive
        #define TIMx_CCMR1_OC1CE    (0x01<<7)
        #define TIMx_CCMR1_OC2FE    (0x01<<10)// Output compare 2 fast enable
        #define TIMx_CCMR1_OC2PE    (0x01<<10)// Output compare 2 preload enable
        #define TIMx_CCMR1_OC2M(a)   ((0b111&a)<<12) // Output compare 1 mode
            #define OC2M_FROZEN             0b000
            #define OC2M_HI_LVL_MATCH       0b001
            #define OC2M_LOW_LVL_MATCH      0b010
            #define OC2M_TOOGLE             0b011 //OC1REF toggles when TIMx_CNT=TIMx_CCR1
            #define OC2M_FORCED_LOW         0b100
            #define OC2M_FORCED_HI          0b101
            #define OC2M_PWD1               0b110 //In upcounting, channel 2 is active as long as TIMx_CNT<TIMx_CCR1 else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0) as long as
            #define OC2M_PWD2               0b111 //In upcounting, channel 2 is inactive as long as TIMx_CNT<TIMx_CCR1 else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else inactive
        #define TIMx_CCMR1_OC2CE    (0x01<<15) // Output compare 2 clear enable

    //<< capture/compare mode register 2 (3,4 chanel's)>>    
    #define TIMx_CCMR2     0x1C         
    //--Input mode--
        #define TIMx_CCMR2_CC3S(a)     ((0b11&a)<<0)//Capture/Compare 1 selection
            #define CC3S_OUT      0x00    //00: CC1 channel is configured as output
            #define CC3S_IN_TI1     0x01    //01: CC1 channel is configured as input  IC1 is mapped on TI1
            #define CC3S_IN_TI2     0x02    //10: CC1 channel is configured as input  IC1 is mapped on TI2
            #define CC3S_IN_TRC  0x03    //11: CC1 channel is configured as input  IC1 is mapped on TRC. 
                                    //This mode is working only if
                                    //an internal trigger input is selected through TS bit (TIMx_SMCR register)
        
        #define TIMx_CCMR2_IC3PSC(a)     ((0b11&a)<<2) //Input capture 1 prescale
            #define IC1PSC_0    0b00 //no prescaller
            #define IC1PSC_2    0b01 //capture is done once every 2 events
            #define IC1PSC_4    0b10 //capture is done once every 4 events
            #define IC1PSC_8    0b11 //capture is done once every 8 events

        #define TIMx_CCMR2_IC3F(a)     ((0b1111&a)<<3) //Input capture 1 filter
            // #define IC1F_0    0b0000
            // #define IC1F_2    0b0001
            // #define IC1F_4    0b0010
            // #define IC1F_8    0b0011
            // #define IC1F_6    0b0100

        #define TIMx_CCMR2_CC4S(a)     ((0b11&a)<<8)//Capture/Compare 1 selection
            #define CC4S_OUT      0x00    //00: CC1 channel is configured as output
            #define CC4S_IN_TI1     0x01    //01: CC1 channel is configured as input  IC1 is mapped on TI1
            #define CC4S_IN_TI2     0x02    //10: CC1 channel is configured as input  IC1 is mapped on TI2
            #define CC4S_IN_TRC  0x03    //11: CC1 channel is configured as input  IC1 is mapped on TRC. 
                                    //This mode is working only if
                                    //an internal trigger input is selected through TS bit (TIMx_SMCR register)

        #define TIMx_CCMR2_IC4PSC(a)     ((0b11&a)<<10) //Input capture 1 prescale
            #define IC4PSC_0    0b00 //no prescaller
            #define IC4PSC_2    0b01 //capture is done once every 2 events
            #define IC4PSC_4    0b10 //capture is done once every 4 events
            #define IC4PSC_8    0b11 //capture is done once every 8 events

        #define TIMx_CCMR2_IC4F(a)     ((0b1111&a)<<12) //Input capture 2 filter
        //--output mode--
        #define TIMx_CCMR2_OC3FE     (0x01<<2) // Output compare 1 fast enable
        #define TIMx_CCMR2_OC3PE     (0x01<<3) // Output compare 1 preload enable
        #define TIMx_CCMR2_OC3M(a)   ((0b111&a)<<4) // Output compare 1 mode
            #define OC3M_FROZEN             0b000
            #define OC3M_HI_LVL_MATCH       0b001
            #define OC3M_LOW_LVL_MATCH      0b010
            #define OC3M_TOOGLE             0b011 //OC1REF toggles when TIMx_CNT=TIMx_CCR1
            #define OC3M_FORCED_LOW         0b100
            #define OC3M_FORCED_HI          0b101
            #define OC3M_PWD1               0b110 //In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0) as long as
            #define OC3M_PWD2               0b111 //In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1 else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else inactive
        #define TIMx_CCMR2_OC3CE    (0x01<<7)
        #define TIMx_CCMR2_OC4FE    (0x01<<10)// Output compare 2 fast enable
        #define TIMx_CCMR2_OC4PE    (0x01<<10)// Output compare 2 preload enable
        #define TIMx_CCMR2_OC4M(a)   ((0b111&a)<<12) // Output compare 1 mode
            #define OC4M_FROZEN             0b000
            #define OC4M_HI_LVL_MATCH       0b001
            #define OC4M_LOW_LVL_MATCH      0b010
            #define OC4M_TOOGLE             0b011 //OC1REF toggles when TIMx_CNT=TIMx_CCR1
            #define OC4M_FORCED_LOW         0b100
            #define OC4M_FORCED_HI          0b101
            #define OC4M_PWD1               0b110 //In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0) as long as
            #define OC4M_PWD2               0b111 //In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1 else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else inactive
        #define TIMx_CCMR2_OC4CE    (0x01<<15) // Output compare 2 clear enable


    // capture/compare enable register 
    #define TIMx_CCER              0x20     
        /**
         * CC1E: Capture/Compare 1 output enable
         * CC1 channel configured as output:
         * 0: Off - OC1 is not active. 
         * 1: On - OC1 signal is output on the corresponding output pin.
         * CC1 channel configured as input:
         * This bit determines if a capture of the counter value can actually be done into the input 
         * capture/compare register 1 (TIMx_CCR1) or not.
         * 0: Capture disabled.
         * 1: Capture enabled.
         * **/
        #define TIMx_CCER_CC1E     (0x01<<0)
        /**
         * CC1P: Capture/Compare 1 output polarity
         * CC1 channel configured as output:
         * 0: OC1 active high.1: OC1 active low.
         * CC1 channel configured as input:
         * This bit selects whether IC1 or IC1 is used for trigger or capture operations.
         * 0: non-inverted: capture is done on a rising edge of IC1. When used as external trigger, IC1 is non-inverted.
         * 1: inverted: capture is done on a falling edge of IC1. When used as external trigger, IC1 is inverted
         * **/
        #define TIMx_CCER_CC1P     (0x01<<1)
        #define TIMx_CCER_CC2E     (0x01<<4)    //выход на pin
        #define TIMx_CCER_CC2P     (0x01<<5)    //Capture/Compare 2 output polarity
        #define TIMx_CCER_CC3E     (0x01<<8)    //выход на pin
        #define TIMx_CCER_CC3P     (0x01<<9)    //Capture/Compare 3 output polarity
        #define TIMx_CCER_CC4E     (0x01<<12)   //выход на pin
        #define TIMx_CCER_CC4P     (0x01<<13)   //Capture/Compare 4 output polarity

    #define TIMx_CNT        0x24        //текущее значение
    #define TIMx_PSC  	    0x28        //предделитель
    #define TIMx_ARR        0x2C        //число значений
   

    #define TIMx_CCR1       0x34 // TIMx capture/compare register 1 
    #define TIMx_CCR2       0x38 // TIMx capture/compare register 2
    #define TIMx_CCR3       0x3c // TIMx capture/compare register 3
    #define TIMx_CCR4       0x40 // TIMx capture/compare register 4

    #define TIMx_DCR        0x48 //TIMx DMA control register
        #define TIMx_DCR_DBA(a)    ((0b11111&a)<<0) // DMA base address
        #define TIMx_DCR_DBL(a)    ((0b11111&a)<<0) // DMA burst length 0b0 - 0b10001
    #define TIMx_DMAR       0x4C    // TIMx DMA address for full transfer 
/******************************************************************
**  General Purpose I/O Register
*******************************************************************
+ */
    #define GPIOA          0x40010800
    #define GPIOB 		    0x40010C00
 	#define GPIOC 		    0x40011000 

    #define GPIOx_CRL 		0x00    //<control low register
    #define GPIOx_CRH       0x04    //<control high register
    #define GPIOx_IDR       0x08    //<input data register
	#define GPIOx_ODR 		0x0C    //<output data register
    #define GPIOx_BSRR 	    0x10
    #define GPIOx_BRR 		0x14

/******************************************************************
** USART Universal sinchronus-asinchronus receiver-transmitter Register
*******************************************************************
+ */
    //## USART's base adress##
    #define USART1         0x40013800	

    //<< USART status register >>
    #define USART_SR 		0x00
        #define USART_SR_PE         0x01    //Parity error. This bit is set by hardware when a parity error occurs in receiver mode.
        #define USART_SR_FE         0x02    //Framing error. This bit is set by hardware when a de-synchronization, excessive noise or a break character is detected
        #define USART_SR_NE         0x04    //Noise is detected on a received frame
        #define USART_SR_ORE        0x08    //Owerrun error.This bit is set by hardware when the word currently being received in the shift register is ready to be transferred into the RDR register while RXNE=1
        #define USART_SR_IDLE       0x10    //Idle Line is detected
        #define USART_SR_RXNE       0x20    //content of the RDR shift register has been transferred to the USART_DR register
        #define USART_SR_TC         0x40    //transmission of a frame containing data is complete and if TXE is set
        #define USART_SR_TXE        0x80    //content of the TDR register has been transferred into the shift register
        #define USART_SR_LBD        0x100   //LIN break is detected
        #define USART_SR_CTS        0x200   //CTS input toggles

    //<< USART DATA register >>
    #define USART_DR 		0x04

    //<< USART Baudrate register >>
    #define USART_BRR     0x08

    //<< USART control register 1 >>
    #define USART_CR1 	    0x0c
        #define USART_CR1_SBK 	    0x01    //send Brake
        #define USART_CR1_RWU 	    0x02    //Receiver wakeup; Этот бит определяет, находится ли USART в "mute" режиме или нет. Он устанавливается и очищается soft-варно и может быть очищен аппаратным обеспечением при распознавании последовательности пробуждения.
        #define USART_CR1_RE 	    0x04    //RX enable
        #define USART_CR1_TE 	    0x08    //TX enable
        #define USART_CR1_IDLEIE 	0x10    //IDLE interrupt enable
        #define USART_CR1_RXNEIE 	0x20    //RXNE interrupt enable (Read data register not empty)
        #define USART_CR1_TCIE 	    0x40    //TX complete interrupt enable
        #define USART_CR1_TXEIE 	0x80    //TXE interrupt enable (Transmit data register empty)
        #define USART_CR1_PEIE 	    0x100   //PE interrupt enable (Parity error)
        #define USART_CR1_PS 	    0x200   //Паритет. 0-чёт 1-нечёт./ Parity selection 0: Even parity 1: Odd parity ; This bit selects the odd or even parity when the parity generation/detection is enabled (PCE bit set)
        #define USART_CR1_PCE 	    0x400   //Parity control enable
        #define USART_CR1_WAKE 	    0x800   //Wakeup method: 0: Idle Line. 1: Address Mark
        #define USART_CR1_M 	    0x1000  //9-bit
        #define USART_CR1_UE 	    0x2000  //USART enable

    //<< USART control register 2 >>
    #define USART_CR2 	    0x10
        #define USART_CR2_ADD(a) 	((0b1111&a)<<0) //Address of the USART node
        #define USART_CR2_LBDL 	    (0x01<<5) //lin break detection length 0=10bit 1=11bit
        #define USART_CR2_LBDIE	    (0x01<<6) // LIN break detection interrupt enable
        #define USART_CR2_LBCL 	    (0x01<<8) // Last bit clock pulse
        #define USART_CR2_CPHA 	    (0x01<<9) // Clock phase
        #define USART_CR2_CPOL 	    (0x01<<10) // Clock polarity
        #define USART_CR2_CLKEN	    (0x01<<11) // Clock enable
        #define USART_CR2_STOP(a) 	((0b11&a)<<12) // num of STOP bits
             #define STOP_1bit      (0b00)
             #define STOP_0_5bit    (0b01)
             #define STOP_2bit      (0b10)
             #define STOP_1_5bit    (0b11)

        #define USART_CR2_LINEN	    (0x01<<14) //LIN mode enable

    //<< USART control register 3 >>
    #define USART_CR3 	    0x14
        #define USART_CR3_EIE       (0x01<<0) //Error interrupt enable
        #define USART_CR3_IREN      (0x01<<1)   //IrDA mode enable
        #define USART_CR3_IRLP      (0x01<<2)   //IrDA low-power
        #define USART_CR3_HDSEL     (0x01<<3)   //Half-duplex selection
        #define USART_CR3_NACK      (0x01<<4)   //Smartcard NACK enable
        #define USART_CR3_SCEN      (0x01<<5)   //Smartcard mode enable
        #define USART_CR3_DMAR      (0x01<<6)   //DMA enable receiver
        #define USART_CR3_DMAT      (0x01<<7)   //DMA enable transmitter
        #define USART_CR3_RTSE      (0x01<<8)   //RTS enable
        #define USART_CR3_CTSE      (0x01<<9)   //CTS enable
        #define USART_CR3_CTSIE     (0x01<<10)  //CTS interrupt enable

    //<< Guard time and prescaler register >>
    #define USART_GTPR 	    0x18        
        #define USART_GTPR_PSC(a) 	((0xFF & (a))<<0) //Prescaler value
        #define USART_GTPR_GT(a) 	((0xFF & (a))<<8) //Guard time value


/******************************************************************
** Serial peripheral interface (SPI) Register
*******************************************************************
+ */

    #define SPI1_base  0x40013000
    #define SPI_CR1    0x00
    #define SPI_CR2    0x04
    #define SPI_SR     0x08
    #define SPI_DR     0x0C
    #define SPI_CRCPR     0x10
    #define SPI_RXCRCR     0x14
    #define SPI_TXCRCR     0x14
    #define SPI_I2SCFGR     0x1C
    #define SPI_I2SPR     0x14

/******************************************************************
** Inter-integrated circuit interface (i2c) Register
*******************************************************************
+ */

    #define I2C1  0x40005400
    #define I2C2  0x40005800
    #define I2C_CR1    0x00
        #define I2C_CR1_PE          (0x01<<0)
        #define I2C_CR1_SMBUS       (0x01<<1)   // 1-SMBus mode; 0-I2C mode
        #define I2C_CR1_SMBTYPE     (0x01<<3)
        #define I2C_CR1_ENARP       (0x01<<4)
        #define I2C_CR1_ENPEC       (0x01<<5)
        #define I2C_CR1_ENGC        (0x01<<6)
        #define I2C_CR1_NOSTRETCH   (0x01<<7)
        #define I2C_CR1_START       (0x01<<8)
        #define I2C_CR1_STOP        (0x01<<9)
        #define I2C_CR1_ACK         (0x01<<10)
        #define I2C_CR1_POS         (0x01<<11)
        #define I2C_CR1_PEC         (0x01<<12)
        #define I2C_CR1_ALERT       (0x01<<13)
        #define I2C_CR1_SWRST       (0x01<<15)

    #define I2C_CR2    0x04
        #define I2C_CR2_FREQ(a)      ((0b111111&a)<<0) //The FREQ bits must be configured with the APB clock frequency value (I2C peripheral connected to APB). The FREQ field is used by the peripheral to generate data setup and hold times compliant with the I2C specifications. The minimum allowed frequency is 2 MHz, the maximum frequency is limited by the maximum APB frequency and cannot exceed 50 MHz (peripheral intrinsic maximum limit)
        #define I2C_CR2_ITERREN       (0x01<<8)        //Error interrupt enable
        #define I2C_CR2_ITEVTEN       (0x01<<9)        //Event interrupt enable
        #define I2C_CR2_ITBUFEN       (0x01<<10)       //Buffer interrupt enable
        #define I2C_CR2_DMAEN         (0x01<<11)       // DMA requests enable
        #define I2C_CR2_LAST          (0X01<<12)       //DMA last transfer

    #define I2C_OAR1   0x08     // I2C Own address register 1
        #define I2C_OAR1_ADD7        ((0xFE&a)<<1)
        #define I2C_OAR1_ADD10        ((0x3FF&a)<<0)
        #define I2C_OAR1_ADDMODE      (0X01<<15)    // 0-7bit slave addres / 1-10bit slave adress

    #define I2C_OAR2   0x0c
        #define I2C_OAR2_ENDUAL     (0x01<<0) //Dual addressing mode enable
        #define I2C_OAR2_ADD2        ((0xFE&a)<<1) //Interface address in dual mode

    #define I2C_DR     0x10
    #define I2C_SR1    0x14
        #define I2C_SR1_SB          0x01        //Start bit (Master mode)
        #define I2C_SR1_ADDR        0x02        //Address sent (master mode)/matched (slave mode)
        #define I2C_SR1_BTF         0x04        //Byte transfer finished
        #define I2C_SR1_ADD10      (0x01<<3)   // 10-bit header sent (Master mode)
        #define I2C_SR1_STOPF      (0x01<<4)   //Stop detection (slave mode)
        #define I2C_SR1_RxNE       (0x01<<6)    //Data register not empty (receivers)
        #define I2C_SR1_TxE        (0x01<<7)    // Data register empty (transmitters)
        #define I2C_SR1_BERR       (0x01<<8)    // Bus error
        #define I2C_SR1_ARLO       (0x01<<9)    //Arbitration lost (master mode)
        #define I2C_SR1_AF         (0x01<<10)   //Acknowledge failure
        #define I2C_SR1_OVR         (0x01<<11)  //Overrun/Underrun
        #define I2C_SR1_PECERR      (0x01<<12)  //PEC error in reception
        #define I2C_SR1_TIMEOUT     (0x01<<14)  //Timeout or Tlow error
        #define I2C_SR1_SMBALERT    (0x01<<15)  //SMBus alert 

    #define I2C_SR2    0x18
    #define I2C_CCR    0x1c
        #define I2C_CCR_FS          0x8000
        #define I2C_CCR_DUTY        0x4000

    #define I2C_TRISE  0x20

/******************************************************************
** NVIC module
*------------------------------------------------------------------
*--(R/W)  Interrupt Set Enable Register
*---Offset: 0x080 (R/W)  Interrupt Clear Enable Register         
*******************************************************************
+ */
	#define NVIC_base 	0xE000E100
	#define NVIC_ISER_0 	0x00		//0-31
    #define NVIC_ISER_1 	0x04        //32-63
    #define NVIC_ISER_2 	0x08        //64-95
	#define NVIC_ICER_0 	0x80		
    #define NVIC_ICER_1 	0x84
    #define NVIC_ICER_2 	0x88
 //   #define NVIC_base_two 	0xE000E200
    #define NVIC_ISPR_0 	0x100
    #define NVIC_ISPR_1 	0x104
    #define NVIC_ISPR_2 	0x108
    #define NVIC_ICPR_0 	0x180
    #define NVIC_ICPR_1 	0x184
    #define NVIC_ICPR_2 	0x188
 //   #define NVIC_base_tree 	0xE000E300 
    #define NVIC_IABR0      0x200
    #define NVIC_IABR1      0x204    
    #define NVIC_IABR2      0x208
    #define NVIC_IPR0       0x300
    /*... */
    //#define NVIC_IPR20      0x320
    #define NVIC_STIR       0xE00

/******************************************************************
**  Direct memory access DMA
*******************************************************************
+ */
    #define DMA1_BASE          0x40020000
    #define DMA2_BASE          0x40020400

    #define DMA_ISR             0x00
        #define DMA_ISR_GIF(a)  (0b0001<<a) // Channel x global interrupt flag
        #define DMA_ISR_TCIF(a) (0b0010<a)  // Channel x transfer complete flag 
        #define DMA_ISR_HTIF(a) (0b0100<<a) // Channel x half transfer flag
        #define DMA_ISR_TEIF(a) (0b1000<<a) // Channel x transfer error flag

    #define DMA_IFCR            0x04
        #define DMA_IFCR_CGIF(a)  (0b0001<<a)
        #define DMA_IFCR_CTCIF(ch_num) (0b0010<ch_num)
        #define DMA_IFCR_CHTIF(a) (0b0100<<a)
        #define DMA_IFCR_CTEIF(a) (0b1000<<a)


    #define DMA_CCR1            0x08
    #define DMA_CNDTR1          0x0C
    #define DMA_CPAR1           0x10
    #define DMA_CMAR1           0x14

    #define DMA_CCR2            0x1c
    #define DMA_CNDTR2          0x20
    #define DMA_CPAR2           0x24
    #define DMA_CMAR2           0x28

    #define DMA_CCR3            0x30
    #define DMA_CNDTR3          0x34
    #define DMA_CPAR3           0x38
    #define DMA_CMAR3           0x3c

    #define DMA_CCR4            0x44
    #define DMA_CNDTR4          0x48
    #define DMA_CPAR4           0x4c
    #define DMA_CMAR4           0x50
    
    #define DMA_CCR5            0x58
    #define DMA_CNDTR5          0x5c
    #define DMA_CPAR5           0x60
    #define DMA_CMAR5           0x64

    #define DMA_CCR6            0x6c
    #define DMA_CNDTR6          0x70
    #define DMA_CPAR6           0x74
    #define DMA_CMAR6           0x78

    #define DMA_CCR7            0x80
    #define DMA_CNDTR7          0x84
    #define DMA_CPAR7           0x88
    #define DMA_CMAR7           0x8c

    // -- DMA_CCR(0-7) -- channel x configuration register
    #define DMA_CCRx_EN     (0X01<<0) //Channel enable
    #define DMA_CCRx_TCIE   (0X01<<1) //Transfer complete interrupt enable
    #define DMA_CCRx_HTIE   (0X01<<2) //Half transfer interrupt enable
    #define DMA_CCRx_TEIE   (0X01<<3) //Transfer error interrupt enable
    #define DMA_CCRx_DIR    (0X01<<4) //Data transfer direction 0: Read from peripheral 1: Read from memory
    #define DMA_CCRx_CIRC   (0X01<<5) //Circular mode
    #define DMA_CCRx_PINC   (0X01<<6)
    #define DMA_CCRx_MINC   (0X01<<7)
    #define DMA_CCRx_PSIZE(a)   ((0b11&(a))<<8)
        #define PSIZE_8b     (0b00)
        #define PSIZE_16b    (0b01)
        #define PSIZE_32b    (0b10)
        
    #define DMA_CCRx_MSIZE(a)   ((0b11&(a))<<10)
        #define MSIZE_8b     (0b00)
        #define MSIZE_16b    (0b01)
        #define MSIZE_32b    (0b10)
        
    #define DMA_CCRx_PL(a)      ((0b11&(a))<<12) //PRIORITY LVL
    #define DMA_CCRx_MEM2MEM   (0X01<<14)

/******************************************************************
**  Analog-Digital converse I/O Register
*******************************************************************
+ */
    #define ADC1_BASE          0x40012400

    #define ADC_SR             0x00
        #define ADC_SR_AWD     0x01    // Analog watchdog flag
        #define ADC_SR_EOC     0x02    // End of conversion
        #define ADC_SR_JEOC    0x04    // Injected channel end of conversion
        #define ADC_SR_JSTRT   0x08    // Injected channel Start flag
        #define ADC_SR_STRT    0x10    // Regular channel Start flag

    #define ADC_CR1            0x04
        #define ADC_CR1_SCAN   0x10

    #define ADC_CR2            0x08
        //**low**
        #define ADC_CR2_adcON 		0x01    // вкл. АЦП
        #define ADC_CR2_CONT 		0x02    // непрерывное преобразование
        #define ADC_CR2_CAL 		0x04    // вкл. калибровку
        #define ADC_CR2_RSTCAL 	0x08
        //**hight**
        #define ADC_CR2_SWenable     0x0E0000 //EXTSEL[2:0]: External event select for regular group ->SWSTART 
        #define ADC_CR2_EXTTRIG      0x100000 //Conversion on external event enable
        #define ADC_CR2_SWSTART      0x400000 //Start conversion of regular channels

    #define ADC_SMPR1           0x0C //10-17 chanels
    
    #define ADC_SMPR2           0x10 //0-9 chanels
    
    #define ADC_DR              0x4c
    #define ADC_SQR3            0x34
    #define ADC_SQR2            0x30
    #define ADC_SQR1            0x2C

/******************************************************************
**  USB (OTG_FS)
*******************************************************************
+ */
    #define USB_OTG_FS_BASE         0x50000000
    #define OTG_FS_GOTGCTL
    #define OTG_FS_GOTGINT
    #define OTG_FS_GAHBCFG
    #define OTG_FS_GUSBCFG
    #define OTG_FS_GRSTCTL
    #define OTG_FS_GINTSTS
    #define OTG_FS_GINTMSK
    #define OTG_FS_GRXSTSR
        //--host mode--
        //--device mode--
    #define OTG_FS_GRXSTSR
        //--host mode--
        //--device mode--
    #define OTG_FS_GRXFSIZ
    #define OTG_FS_HNPTXFSIZ    0
    #define OTG_FS_DIEPTXF0     (OTG_FS_HNPTXFSIZ)
    #define OTG_FS_HNPTXSTS
    #define OTG_FS_GCCFG
    #define OTG_FS_CID
    #define OTG_FS_HPTXFSIZ
    #define OTG_FS_DIEPTXF1
    #define OTG_FS_DIEPTXF2
    #define OTG_FS_DIEPTXF3
    #define OTG_FS_HCFG
    #define OTG_FS_HFIR
    #define OTG_FS_HFNUM
    #define OTG_FS_HPTXSTS
    #define OTG_FS_HAINT
    #define OTG_FS_HAINTMSK
    #define OTG_FS_HPRT
    #define OTG_FS_HCCHAR0
    #define OTG_FS_HCCHAR1
    #define OTG_FS_HCCHAR2
    #define OTG_FS_HCCHAR3
    #define OTG_FS_HCCHAR4
    #define OTG_FS_HCCHAR5
    #define OTG_FS_HCCHAR6
    #define OTG_FS_HCCHAR7
    #define OTG_FS_HCINT0
    #define OTG_FS_HCINT1
    #define OTG_FS_HCINT2
    #define OTG_FS_HCINT3
    #define OTG_FS_HCINT4
    #define OTG_FS_HCINT5
    #define OTG_FS_HCINT6
    #define OTG_FS_HCINT7
    #define OTG_FS_HCINTMSK0
    #define OTG_FS_HCINTMSK1
    #define OTG_FS_HCINTMSK2
    #define OTG_FS_HCINTMSK3
    #define OTG_FS_HCINTMSK4
    #define OTG_FS_HCINTMSK5
    #define OTG_FS_HCINTMSK6
    #define OTG_FS_HCINTMSK7
    //и ещё 5 страниц


/******************************************************************
**  Others
*******************************************************************
+ */
#include "u_stddef.h"
#define  stm32_api  extern

unsigned int __system_clock; // <-- переменная для регистрации текущего значения частоты системы
#endif // !STM32_H
