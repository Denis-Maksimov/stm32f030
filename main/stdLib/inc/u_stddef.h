#ifndef U_STDDEF_H
#define U_STDDEF_H

#define REGISTER(a)     (*((volatile unsigned int *)(a)))
#define true  ((unsigned)(1)) 
#define false ((unsigned)(0)) 
#define __IO    volatile

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef signed char int8_t;
typedef signed int int32_t;
typedef signed short int16_t;

typedef unsigned int size_t;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;


#endif // !U_STDDEF_H
