//#include "stm32.h"
#include "ssd1306.h"

#define SSD1306(a,b)        (I2C_Write((SSD1306_ADDR_WRITE), (a), (b)))
void ssd1306init(){

    //temporary pointer
    uint8_t* data = (uint8_t*)u_malloc(4);

    //-- display off
    data[0]=SSD1306_SLEEP;
    SSD1306(data,1);

    //-- set memory adressing mode = Horizontal addressing mode
    data[0]=SSD1306_SET_MEM_ADDR_MODE;
    data[1]=SSD1306_HORIZONTAL_AM;
    SSD1306(data,2);


    //-- Setup column start and end address = 0px - 128px (ширина выводимого диапозона)
    data[0]=SSD1306_SET_COLUMN_ADDR;
    data[1]=SSD1306_A_START_ADDR_CA(0);
    data[2]=SSD1306_B_END_ADDR_CA(127);
    SSD1306(data,3);

    data[0]=SSD1306_SCAN_DIRECTION_NORMAL;
    SSD1306(data,1);

    
    // data[0]=SSD1306_SET_LOWER_COLUMN(0);
    // SSD1306(data,1);

    // data[0]=SSD1306_SET_HIGHER_COLUMN(0x10);
    // SSD1306(data,1);

    
    
    
    
    //-- display on
    data[0]=SSD1306_WAKEUP;
    SSD1306(data,1);

    u_free(data);



}

void ssd1306fill(){
    uint8_t* data = (uint8_t*)u_malloc(4);
    data[0]=SSD1306_DATA_CMD;
    data[1]= 0b10101010;
    data[2]=SSD1306_DATA_CMD;
    data[3]= 0b01010101;
    for (int i = 0; i < 128; i++)
    {
        SSD1306(data,4);
    }
    u_free(data);
}