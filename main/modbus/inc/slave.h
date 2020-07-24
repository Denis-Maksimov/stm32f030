#ifndef MODBUS_SLAVE_H
#define MODBUS_SLAVE_H
#define U_MODBUS_API  extern

typedef struct raw_packet*(*modbus_func)(void*);
U_MODBUS_API struct raw_packet* slave_receive(struct raw_packet* raw);
U_MODBUS_API modbus_func funcs[];

#undef U_MODBUS_API
#endif //!MODBUS_SLAVE_H