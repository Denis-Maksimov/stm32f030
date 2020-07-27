#include "i2c.h"
#include "GPIO.h"
#define OWN_ADDRES 0x27<<1

void i2c_init(void)
{
	int periph_clock = 72;  // Тактирование перефирии i2c
	int freq_SCL = 100;    // частота частоты синхроимпульсов SCL i2c в кГц


    //-- clock
        REGISTER(RCC_BASE|RCC_APB1ENR) |= (RCC_APB1_I2C1EN);

    //-- pins
	pin_init(6,'B',AF_OPEN_DRAIN_OUTPUT_10MHZ);	//SCL
	pin_init(7,'B',AF_OPEN_DRAIN_OUTPUT_10MHZ);	//SDA

    //-- i2c
        //настраиваем модуль в режим I2C
        REGISTER(I2C1|I2C_CR1)&= ~I2C_CR1_SMBUS;
		REGISTER(I2C1|I2C_CR1)|=I2C_CR1_ACK|I2C_CR1_SMBTYPE;
		
	
    //-- указываем частоту тактирования модуля
        REGISTER(I2C1|I2C_CR2) &= ~I2C_CR2_FREQ(0b111111); //clear mask
	REGISTER(I2C1|I2C_CR2) |= I2C_CR2_FREQ(periph_clock); // Fclk1=168/4=42MHz 

    //-- конфигурируем I2C, standart mode, 100 KHz duty cycle 1/2	
        REGISTER(I2C1|I2C_CCR)&= ~(I2C_CCR_FS | I2C_CCR_DUTY);

    //-- Придумываем себе адрес 1-7 биты
        REGISTER(I2C1|I2C_OAR1)= OWN_ADDRES;

    //-- задаем частоту работы модуля SCL по формуле T_SCL /(2* T_PCLK1) 
	REGISTER(I2C1|I2C_CCR) |= (periph_clock*1000)/(2*freq_SCL); //10 000ns/48ns = 208

	/*
	Для правильной работы необходимо задать в “тактах” частоты тактирования модуля
	максимально возможное время установления, 
	по спецификации для стандартного режима максимальное время равно 1000 нс.
	Период тактовой частоты равен (1 / [APB clock] МГц) [нс], 
	следовательно время максимальное нарастания:
	1000kHz/[1000/APB clock(MHz)]+1    --> Standart_Mode
	300/[APB clock]+1 	  --> Fast_Mode
	*/
	REGISTER(I2C1|I2C_TRISE) = periph_clock+1;
	
    //-- включаем модуль
        REGISTER(I2C1|I2C_CR1) |= I2C_CR1_PE;

}

//------------------------------------------------
#include "USART.h"
void I2C_Write(uint8_t _addr, uint8_t* data, uint8_t __n)
{
	//--- формируем бит-сигнал "старт"
	REGISTER(I2C1|I2C_CR1) |= I2C_CR1_START;
		
		while(!(REGISTER(I2C1|I2C_SR1) & I2C_SR1_SB)); //тупим пока отправится
		REGISTER(I2C1|I2C_SR1)=0;					   //clear status
		// puts("start ok");

    //--- передаем адрес устройства
	REGISTER(I2C1|I2C_DR) = _addr;
		while(!(REGISTER(I2C1|I2C_SR1) & I2C_SR1_TxE));
		REGISTER(I2C1|I2C_SR1)&=0;	//(void) I2C2->SR1;
		REGISTER(I2C1|I2C_SR2)&=0;	//(void) I2C2->SR2;
		// puts("addr ok");
    // //--- передаем адрес регистра
	// REGISTER(I2C1|I2C_DR) = (uint32_t)reg_addr;	
	// 	while(!(REGISTER(I2C1|I2C_SR1)& I2C_SR1_TxE));	
			
    //--- записываем данные	
	for (int i = 0; i < __n; i++)
	{
		REGISTER(I2C1|I2C_DR) = data[i];					// отослали в регистр
		while((REGISTER(I2C1|I2C_SR1) & I2C_SR1_BTF));	// подождали отправки байта
		REGISTER(I2C1|I2C_SR1)&=0;
		// 
	}
	
		//стоп бит
	REGISTER(I2C1|I2C_CR1) |= I2C_CR1_STOP;		
	REGISTER(I2C1|I2C_SR1)=0;
	puts("byte ok");
}
/*
uint8_t I2C_Read(uint8_t reg_addr)
{
	uint8_t data;
	//стартуем
	I2C2->CR1 |= I2C_CR1_START;		
	while(!(I2C2->SR1 & I2C_SR1_SB)){};
	(void) I2C2->SR1;

	//передаем адрес устройства	
	I2C2->DR = I2C_ADDRESS(ADR,I2C_MODE_WRITE);
	while(!(I2C2->SR1 & I2C_SR1_ADDR)){};
	(void) I2C2->SR1;
	(void) I2C2->SR2;

	//передаем адрес регистра
	I2C2->DR = reg_addr;	
	while(!(I2C2->SR1 & I2C_SR1_TXE)){};	
	I2C2->CR1 |= I2C_CR1_STOP;	
			
	//рестарт!!!
	I2C2->CR1 |= I2C_CR1_START;		
	while(!(I2C2->SR1 & I2C_SR1_SB)){};
	(void) I2C2->SR1;
		
	//передаем адрес устройства, но теперь для чтения
	I2C2->DR = I2C_ADDRESS(ADR,I2C_MODE_READ);
	while(!(I2C2->SR1 & I2C_SR1_ADDR)){};
	(void) I2C2->SR1;
	(void) I2C2->SR2;
			
	//читаем	
	I2C2->CR1 &= ~I2C_CR1_ACK;
	while(!(I2C2->SR1 & I2C_SR1_RXNE)){};
	data = I2C2->DR;	
	I2C2->CR1 |= I2C_CR1_STOP;	
			
	return data;	
} 	
*/

void i2c_slave_Tx_mode(){}
void i2c_slave_Rx_mode(){}
void i2c_master_Tx_mode(){}
void i2c_master_Rx_mode(){}




/*#######################################################
*************  шпаргалка по настройке  ******************
#########################################################

FEDC BA98 // 7654 3210

    CNF для входа
00:0 Analog mode                 ----> &= ~GPIO_CRH_CNFx ### аналоговый вход
01:4 Floating input (reset state) ----> GPIO_CRH_CNFx_0 ### плавающий вход
10:8 Input with pull-up / pull-down ----> GPIO_CRH_CNFx_1 ### вход с резистором up/down устанавливается через GPIOx_ODR или GPIOx_BSR
11:F Reserved
    CNF для выхода
00:0x2/1/3 General purpose output push-pull ----> &= ~GPIO_CRH_CNFx ### 2MHz/10MHz/50MHz
01:0x6/5/7 General purpose output Open-drain ----> GPIO_CRH_CNFx_0 ###
10:0xA/9/B Alternate function output Push-pull ----> GPIO_CRH_CNFx_1 ###
11:0xE/D/F Alternate function output Open-drain ----> GPIO_CRH_CNFx ###
#########################################################
*************                          ******************
#######################################################*/
