#include "i2c.h"
#define OWN_ADDRES 0x46

void i2c_init(void){
    //clock
    REGISTER(RCC_BASE|RCC_APB2ENR) |= (APB2_GPIOB);
    REGISTER(RCC_BASE|RCC_APB1ENR) |= (APB1_I2C1);
    //pins
    REGISTER(GPIOB|GPIOx_CRL) |= 0xFF000000;

    //i2c
    //настраиваем модуль в режим I2C
    REGISTER(I2C1|I2C_CR1)&= ~I2C_CR1_SMBUS;
    //указываем частоту тактирования модуля
    REGISTER(I2C1|I2C_CR2)&= ~I2C_CR2_FREQ;
	REGISTER(I2C1|I2C_CR2)|= 42; // Fclk1=168/4=42MHz 
	//конфигурируем I2C, standart mode, 100 KHz duty cycle 1/2	
    REGISTER(I2C1|I2C_CCR)&= ~(I2C_CCR_FS | I2C_CCR_DUTY);
    //Придумываем себе адрес 1-7 биты
    REGISTER(I2C1|I2C_OAR1)= OWN_ADDRES;
    //задаем частоту работы модуля SCL по формуле 10 000nS/(2* TPCLK1) 
	REGISTER(I2C1|I2C_CCR) |= 208; //10 000ns/48ns = 208
    //Standart_Mode = 1000nS, Fast_Mode = 300nS, 1/42MHz = 24nS
	REGISTER(I2C1|I2C_TRISE) = 42; //(1000nS/24nS)+1
    //включаем модуль
    REGISTER(I2C1|I2C_CR1)&= ~I2C_CR1_SMBUS;

}


void I2C_Write(uint8_t reg_addr, uint8_t* data)
{
        //стартуем
        REGISTER(I2C1|I2C_CR1) |= I2C_CR1_START;		
	while(!(REGISTER(I2C1|I2C_SR1) & I2C_SR1_SB));
	//(void) I2C2->SR1;
	REGISTER(I2C1|I2C_SR1)=0;

        //передаем адрес устройства
	REGISTER(I2C1|I2C_DR) = OWN_ADDRES;
	while(!(REGISTER(I2C1|I2C_SR1) & I2C_SR1_ADDR));
    REGISTER(I2C1|I2C_SR1)=0;	//(void) I2C2->SR1;
    REGISTER(I2C1|I2C_SR2)=0;	//(void) I2C2->SR2;

        //передаем адрес регистра
	REGISTER(I2C1|I2C_DR) = (uint32_t)reg_addr;	
	while(!(REGISTER(I2C1|I2C_SR1)& I2C_SR1_TXE));	
			
        //пишем данные	
	int i=0;
	while(data[i]!=0){
		REGISTER(I2C1|I2C_DR) = data[i];					// отослали в регистр
		while(!(REGISTER(I2C1|I2C_SR1) & I2C_SR1_BTF));	// подождали отправки байта
	}
		//стоп бит
	REGISTER(I2C1|I2C_CR1) |= I2C_CR1_STOP;		
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
