#pragma once
#include "stm32.h"
#include "GPIO.h"
#include "USART.h"
#include "string.h"

enum sample_time {
    cycles_1_5=0b000,
    cycles_7_5=0b001,
    cycles_13_5=0b010,
    cycles_28_5=0b011,
    cycles_41_5=0b100,
    cycles_55_5=0b101,
    cycles_71_5=0b110,
    cycles_239_5=0b111
};
typedef union tagSMPx{
	struct {//SMPR2
   		enum sample_time SMP0:3;
   		enum sample_time SMP1:3;
        enum sample_time SMP2:3;   
   		enum sample_time SMP3:3;
        enum sample_time SMP4:3;
   		enum sample_time SMP5:3;
   		enum sample_time SMP6:3;
        enum sample_time SMP7:3;
   		enum sample_time SMP8:3;
   		enum sample_time SMP9:3;
        unsigned     reserved:2;
	};

	struct {//SMPR1
       	enum sample_time SMP10:3;
   		enum sample_time SMP11:3;
        enum sample_time SMP12:3;   
   		enum sample_time SMP13:3;
        enum sample_time SMP14:3;
   		enum sample_time SMP15:3;
   		enum sample_time SMP16:3;
        enum sample_time SMP17:3;
        unsigned      reserve:8;
   	};

}SMPx;

enum adc_channel {
    ch0=0,
    ch1,
    ch2,
    ch3,
    ch4,
    ch5,
    ch6,
    ch7,
    ch8,
    ch9,
    ch10,
    ch11,
    ch12,
    ch13,
    ch14,
    ch15,
    ch16,
    ch17
};
enum num_of_conversions {
    conversions1=0,
    conversions2,
    conversions3,
    conversions4,
    conversions5,
    conversions6,
    conversions7,
    conversions8,
    conversions9,
    conversions10,
    conversions11,
    conversions12,
    conversions13,
    conversions14,
    conversions15,
    conversions16
};

typedef union tagSQRx{
	struct {//SQR3
   		enum adc_channel SQ1:5;
   		enum adc_channel SQ2:5;  
   		enum adc_channel SQ3:5;
        enum adc_channel SQ4:5;
   		enum adc_channel SQ5:5;
   		enum adc_channel SQ6:5;
	};

	struct {//SQR2
       	enum adc_channel SQ7:5;
   		enum adc_channel SQ8:5;  
   		enum adc_channel SQ9:5;
        enum adc_channel SQ10:5;
   		enum adc_channel SQ11:5;
   		enum adc_channel SQ12:5;
   	};
    struct {//SQR3
       	enum adc_channel SQ13:5;
   		enum adc_channel SQ14:5;  
   		enum adc_channel SQ15:5;
        enum adc_channel SQ16:5;
        enum num_of_conversions ADC_REGULAR_LENGHT:4;
   	};

}SQRx;



void ADC_init(void);
void ADC_start_conversion(void);
void ADC_read(void);
