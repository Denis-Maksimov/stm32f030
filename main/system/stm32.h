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
        #define RCC_CFGR_PLLMULx_4b(a)  ((a)<<18)
		#define RCC_CFGR_PLLMUL4    0x080000
		#define RCC_CFGR_PLLMUL5    0x0c0000
		#define RCC_CFGR_PLLMUL6    0x100000
		#define RCC_CFGR_PLLMUL7    0x140000
		#define RCC_CFGR_PLLMUL8    0x180000
		#define RCC_CFGR_PLLMUL9    0x1c0000
		#define RCC_CFGR_PLLMUL6_5  0x240000

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
	#define SCB_CFSR        0x28 //CFSR Configurable fault status register
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
        #define SysTick_CLKSOURCE 0x04 // Clock source selection - AHB/8 or AHB
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
        #define TIMx_CR1_CEN    (0x01<<0)
        #define TIMx_CR1_UDIS   (0x01<<1) // Update disable -  enable/disable UEV event generation.
        #define TIMx_CR1_URS    (0x01<<2) // Update request source
        #define TIMx_CR1_OPM    (0x01<<3) // One-pulse mode
        #define TIMx_CR1_DIR    (0x01<<4) // 0-up,1-down
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
            #define OC2M_PWD1               0b110 //In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0) as long as
            #define OC2M_PWD2               0b111 //In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1 else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else inactive
        #define TIMx_CCMR1_OC2CE    (0x01<<15) // Output compare 2 clear enable

        
    #define TIMx_CCMR2     0x1C         // capture/compare mode register 2 
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
        #define TIMx_CCER_CC2E     (0x01<<4)
        #define TIMx_CCER_CC2P     (0x01<<5)
        #define TIMx_CCER_CC3E     (0x01<<8)
        #define TIMx_CCER_CC3P     (0x01<<9)
        #define TIMx_CCER_CC4E     (0x01<<12)
        #define TIMx_CCER_CC4P     (0x01<<13)

    #define TIMx_CNT        0x24        //текущее значение
    #define TIMx_PSC  	    0x28        //предделитель
    #define TIMx_ARR        0x2C        //число значений
   

    #define TIMx_CCR1       0x34 // TIMx capture/compare register 1 
    #define TIMx_CCR2       0x38
    #define TIMx_CCR3       0x3c
    #define TIMx_CCR4       0x40

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
    #define USART1         0x40013800	
        
    #define USART_BRR     0x08
    #define USART_CR1 	    0x0c
        #define USART_CR1_SBK 	    0x01 //send Brake
        #define USART_CR1_RWU 	    0x02
        #define USART_CR1_RE 	    0x04 //RX enable
        #define USART_CR1_TE 	    0x08 //TX enable
        #define USART_CR1_IDLEIE 	0x10
        #define USART_CR1_RXNEIE 	0x20
        #define USART_CR1_TCIE 	    0x40 //TX complete interrupt enable
        #define USART_CR1_TXEIE 	0x80
        #define USART_CR1_PEIE 	    0x100
        #define USART_CR1_PS 	    0x200
        #define USART_CR1_PCE 	    0x400
        #define USART_CR1_WAKE 	    0x800
        #define USART_CR1_M 	    0x1000 //9-bit
        #define USART_CR1_UE 	    0x2000 //USART enable

	#define USART_SR 		0x00
        #define USART_SR_PE         0x01
        #define USART_SR_FE         0x02
        #define USART_SR_NE         0x04
        #define USART_SR_ORE        0x08
        #define USART_SR_IDLE       0x10
        #define USART_SR_RXNE       0x20
        #define USART_SR_TC         0x40
        #define USART_SR_TXE        0x80
        #define USART_SR_LBD        0x100
        #define USART_SR_CTS        0x200
	#define USART_DR 		0x04
/******************************************************************
** Serial peripheral interface (SPI) Register
*******************************************************************
+ */

    #define SPI1_base  0x40013000
    #define SPI_CR1    0x00
    #define SPI_CR2    0x04
    #define SPI_SR     0x08
/******************************************************************
** Inter-integrated circuit interface (i2c) Register
*******************************************************************
+ */

    #define I2C1  0x40005400
    #define I2C2  0x40005800
    #define I2C_CR1    0x00
        #define I2C_CR1_PE          0x01
        #define I2C_CR1_SMBUS       0x02
        #define I2C_CR1_SMBTYPE     0x08
        #define I2C_CR1_ENARP       0x10
        #define I2C_CR1_ENPEC       0x20
        #define I2C_CR1_ENGC        0x40
        #define I2C_CR1_NOSTRETCH   0x80
        #define I2C_CR1_START       0x100
        #define I2C_CR1_STOP        0x200
        #define I2C_CR1_ACK         0x400
        #define I2C_CR1_POS         0x800
        #define I2C_CR1_PEC         0x1000
        #define I2C_CR1_ALERT       0x2000
        #define I2C_CR1_SWRST       0x8000

    #define I2C_CR2    0x04
        #define I2C_CR2_FREQ        0x3F

    #define I2C_OAR1   0x08
    #define I2C_OAR2   0x0c
    #define I2C_DR     0x10
    #define I2C_SR1    0x14
        #define I2C_SR1_SB          0x01
        #define I2C_SR1_ADDR        0x02
        #define I2C_SR1_BTF         0x04
        #define I2C_SR1_TXE         0x80

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
	#define NVIC_ISER_0 	0x00		
    #define NVIC_ISER_1 	0x04
    #define NVIC_ISER_2 	0x08
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
  
#define REGISTER(a)     (*((volatile unsigned int *)(a)))
#define true  ((unsigned)(1)) 
#define false ((unsigned)(0)) 
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef signed char int8_t;
typedef signed int int32_t;
typedef signed short int16_t;

unsigned int __system_clock; // <-- переменная для регистрации текущего значения частоты системы
#endif // !STM32_H
