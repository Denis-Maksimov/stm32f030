#ifndef MODBUS_GENERAL_H
#define MODBUS_GENERAL_H
#define U_MODBUS_API  extern

struct raw_packet{
    unsigned int n;          // число байт в телеграмме
    unsigned char* packet;   // сырые данные пакета (с CRC16 и шлюхами)
};

//-- pack data
U_MODBUS_API struct raw_packet* pack_data(unsigned int destination_addres, unsigned char* data, unsigned int n);

//-- unpack data
U_MODBUS_API unsigned char* unpack_data(unsigned char* data, unsigned int n);

//-- kill struct raw_packet
U_MODBUS_API void free_raw(struct raw_packet* raw);

//-- print in stdout packet in hex mode
U_MODBUS_API void print_raw(struct raw_packet* raw);

//-- Изменить порядок байт в слове
U_MODBUS_API unsigned short endian_word(unsigned short word);

#undef U_MODBUS_API
#endif // !MODBUS_GENERAL_H
