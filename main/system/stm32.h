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
	#define RCC_APB1ENR 	0x1C
    #define SCB_Base 		0xE000ED00
    #define SCB_VTOR 		0x08
    #define FLASH_BASE     0x08000000
    //**************************
    #define APB2_AFIO      0x01
    #define APB2_GPIOA     0x04
    #define APB2_GPIOB     0x08
    #define APB2_GPIOC     0x10
    #define APB2_GPIOD     0x20
    #define APB2_GPIOE     0x40
    #define APB2_ADC1      0x200    
    #define APB2_ADC2      0x400 
    #define APB2_TIM1      0x800    
    #define APB2_SPI1      0x1000
    #define APB2_USART1    0x4000    
    //***********LOW***************
    #define APB1_TIM2      0x01
    #define APB1_TIM3      0x02
    #define APB1_TIM4      0x04
    #define APB1_TIM5      0x08
    #define APB1_TIM6      0x10
    #define APB1_TIM7      0x20
    #define APB1_WWDG      0x800    
    #define APB1_SPI2      0x4000 
    #define APB1_SPI3      0x8000 

    #define APB1_I2C1      0x200000    

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
**  General-purpose Timers
*******************************************************************
+ */
    #define TIM2_BASE      0x40000000
    #define TIM3_BASE      0x40000400
    #define TIM4_BASE      0x40000800
    #define TIM5_BASE      0x40000C00

    #define TIMx_CR1        0x00
        #define TIMx_CEN    0x01
        #define TIMx_UDIS   0x02 // Update disable -  enable/disable UEV event generation.
        #define TIMx_URS    0x04 // Update request source
        #define TIMx_OPM    0x08 // One-pulse mode
        #define TIMx_DIR    0x10 // 0-up,1-down
        #define TIMx_ARPE   0x80 //auto reload

    #define TIMx_PSC  		0x28        //предделитель
    #define TIMx_ARR       0x2C        //число значений
    #define TIMx_SR        0x10        //статус   
    #define TIMx_DIER      0x0C        //события и прерывания
    #define TIMx_CNT       0x24        //текущее значение

    #define TIMx_CCMR1     0x18
        #define CCMR1_CC1_out      0x00    //00: CC1 channel is configured as output
        #define CCMR1_CC_inTI1     0x01    //01: CC1 channel is configured as input  IC1 is mapped on TI1
        #define CCMR1_CC_inTI2     0x02    //10: CC1 channel is configured as input  IC1 is mapped on TI2
        #define CCMR1_CCMR1_inTRC  0x03    //11: CC1 channel is configured as input  IC1 is mapped on TRC. 
                                //This mode is working only if
                                //an internal trigger input is selected through TS bit (TIMx_SMCR register)
        #define IC1PSC0    0x00
        #define IC1PSC2    0x04
        #define IC1PSC4    0x08
        #define IC1PSC8    0x0c

        #define CCMR1_OC1M_frozen     0x00
        #define CCMR1_OC1M_PWM1       0x60
        #define CCMR1_OC1M_PWM2       0x70
        #define CCMR1_OC2M_PWM1       0x6000
        #define CCMR1_OC2M_PWM2       0x7000
    
    #define TIMx_CCER              0x20
        #define TIMx_CCER_CC1E     0x0001
        #define TIMx_CCER_CC2E     0x0010
        #define TIMx_CCER_CC3E     0x0100
        #define TIMx_CCER_CC4E     0x1000

    #define TIMx_CCR1              0x34
    #define TIMx_CCR2              0x38
    #define TIMx_CCR3              0x3c
    #define TIMx_CCR4              0x40
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
**  Others
*******************************************************************
+ */
  
#define REGISTER(a)     (*((volatile unsigned int *)(a)))
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef signed char int8_t;
typedef signed int int32_t;
typedef signed short int16_t;

unsigned int __system_clock; // <-- переменная для регистрации текущего значения частоты системы
#endif // !STM32_H
