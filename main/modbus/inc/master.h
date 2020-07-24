#ifndef MODBUS_MASTER_H
#define MODBUS_MASTER_H
#define U_MODBUS_API  extern

U_MODBUS_API void master_ModBus_Read_Coils(unsigned char destination_addres, unsigned short Starting_Address, unsigned short Quantity_of_coils);
U_MODBUS_API void master_ModBus_Read_Discrete_Inputs(unsigned char slave_addr,unsigned short Starting_Address,unsigned short Quantity_of_coils);
U_MODBUS_API void master_ModBus_Read_Holding_Registers(unsigned char slave_addr,unsigned short Starting_Address, unsigned short Quantity_of_coils);
U_MODBUS_API void master_ModBus_Read_Input_Registers(unsigned char slave_addr,unsigned short Starting_Address,unsigned short Quantity_of_regs);

U_MODBUS_API void master_ModBus_Write_Single_Coil(unsigned char slave_addr,unsigned short Address, unsigned short Value);
U_MODBUS_API void master_ModBus_Write_Single_Register(unsigned char slave_addr,unsigned short Address,unsigned short Value);
U_MODBUS_API void master_ModBus_Write_Multiple_Coils(unsigned char slave_addr,unsigned short Starting_Address,unsigned short Quantity_of_Outputs,unsigned char byte_count, unsigned char* Outputs_Value);

#undef U_MODBUS_API
#endif // !MODBUS_MASTER_H
