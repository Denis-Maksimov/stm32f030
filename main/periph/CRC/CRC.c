#include "CRC.h"

#define __CRC_RESET_DR()        REGISTER(CRC_BASE|CRC_CR)|=CRC_CR_RESET
#define __CRC_CALC_CRC(a)       (REGISTER(CRC_BASE|CRC_DR)|=( a & 0xFF ) )

void CRC_init(){
    REGISTER(RCC_BASE|RCC_AHBENR) |= RCC_AHBENR_CRCEN;
    REGISTER(CRC_BASE|CRC_CR)     |= CRC_CR_RESET;
}

uint32_t crc32_native(char *bfr, int len, int clear){

    int l;
    uint32_t *p, x, crc;
    l = len >> 2; //equal:  l = len/4
    p = (uint32_t*)bfr;
    x = p[l];

    if(clear) 
        __CRC_RESET_DR();

    while (l--)
    {
        crc = __CRC_CALC_CRC(*p++);
    }

    switch (len & 3)
    {
    case 1:
        crc = __CRC_CALC_CRC(x & 0x000000FF);
        break;
    case 2:
        crc = __CRC_CALC_CRC(x & 0x0000FFFF);
        break;
    case 3:
        crc = __CRC_CALC_CRC(x & 0x00FFFFFF);
        break;
    
    default:
        return 0;
        break;
    }

    return (0xFFFFFFFF ^ crc);
    
}

uint32_t reverse_32(uint32_t data){
    asm("rbit r0, r0");
    return data;
}

uint32_t crc32_ether(char *buf, int len, int clear){
    
    uint32_t* p = (uint32_t*) buf;
    uint32_t  crc, crc_reg;

    if(clear) {
        __CRC_RESET_DR();
    }
    if(len >= 4){

        while(len >= 4)
        {
            crc_reg = __CRC_CALC_CRC(reverse_32(*p++));
            len -= 4;
        }
    }else{
        crc=0xFFFFFFFF;
        crc_reg=__CRC_CALC_CRC(0xEBABAB);
    }
    crc=reverse_32(crc_reg);
    if (len){
        __CRC_CALC_CRC(crc_reg);
        switch (len)
        {
        case 1:
            crc_reg = __CRC_CALC_CRC(reverse_32((*p & 0xFF)^crc) >> 24);
            crc= (crc >> 8) ^ reverse_32(crc_reg);
            break;
        case 2:
            crc_reg = __CRC_CALC_CRC(reverse_32((*p & 0xFFFF)^crc) >> 16);
            crc= (crc >> 8) ^ reverse_32(crc_reg);
            break;
        case 3:
            crc_reg = __CRC_CALC_CRC(reverse_32((*p & 0xFFFFFF)^crc) >> 8);
            crc= (crc >> 8) ^ reverse_32(crc_reg);
            break;
        
        default:
            break;
        }
    }
    return ~crc;

}

