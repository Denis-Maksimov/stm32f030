#include "crc16.h"
#include "modbus_general.h"
#include "u_stdlib.h"
// #include <stdio.h>
#include "u_string.h"
#include "slave.h"
#define MY_ADDRESS 4


//-- упаковать данные в сырой пакет 
struct raw_packet* pack_data(unsigned int destination_addres, unsigned char* data, unsigned int n)
{
    struct raw_packet* ret=(struct raw_packet*)u_malloc(sizeof(struct raw_packet));
     //-- prepares

    //
    ret->packet=(unsigned char*)u_malloc(n+3);
    //--pack address destination
    ret->packet[0]=destination_addres;

    //--pack data (PDU)
    u_memcpy(ret->packet+1,data,n);

    //--pack CRC16
    ret->packet[n+1]=(unsigned char)((CRC16(data,n)&0xff00)>>8);
    ret->packet[n+2]=(unsigned char)(CRC16(data,n)&0xff);
    ret->n=n+1+2;//+ 1 byte addres + 2 byte crc

    return ret;
    
}

//-- распаковать данные 
unsigned char* unpack_data(unsigned char* data, unsigned int n)
{
    
    //-- check address
    if (data[0]!=MY_ADDRESS){
        return 0;
    }
    // printf("address ok! address=0x%X\n", data[0]);
    data+=1;
    

    //-- check crc16 
    unsigned int crc=((data[n-3]<<8)|(data[n-2]))&0xFFFF;
    if(crc!=CRC16(data,n-3))
    {
        // printf("error crc, 0x%X != 0x%X\n",crc,CRC16(data,n-3));
        // fflush(stdout);
        return 0;
    }
    // printf("CRC ok! crc=0x%04X\n",crc);
    unsigned char* ret = (unsigned char*)u_malloc(n-3);
    u_memcpy(ret,data,n-3);
    // printf("data=%s\n",ret);
    return ret;
}

void free_raw(struct raw_packet* raw)
{
    u_free(raw->packet);
    u_free(raw);
}

// void print_raw(struct raw_packet* raw)
// {
//     for (int i = 0; i < (raw->n); i++)
//     {
//         (i)?(printf("-")):(i);
//         printf("0x%02X",raw->packet[i]&0xff);
//         fflush(stdout);

//     }
//     printf("\n");
    
// }

unsigned short endian_word(unsigned short word)
{
    return ((word&0xff)<<8)|((word&0xff00)>>8);
}


void slave_recv(void* buffer, size_t n)
{
    //снимаем адрес и CRC
    unsigned char* raw = unpack_data((unsigned char*)buffer, n);
    //выполняем modBus функцию
    struct raw_packet* response= funcs[raw[0]](raw+1);
    //отсылаем ответ    
    // MB_serial_send(response->packet response->n);
    free_raw(response);
}


