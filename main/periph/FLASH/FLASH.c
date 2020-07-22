#include "stm32.h"

#define RDPRT_KEY               ((u16)0x00A5)
#define FLASH_UNLOCK_KEY1       ((u32)0x45670123)
#define FLASH_UNLOCK_KEY2       ((u32)0xCDEF89AB)


static void flash_unlock(void)
{
    REGISTER(FLASH_base+FLASH_KEYR)=FLASH_UNLOCK_KEY1;
    REGISTER(FLASH_base+FLASH_KEYR)=FLASH_UNLOCK_KEY2;

}

static void flash_lock(void){
    REGISTER(FLASH_base+FLASH_CR) |= FLASH_CR_LOCK;
}

void flashMassErase(void)
{
    flash_unlock();
    REGISTER(FLASH_base+FLASH_CR) |= FLASH_CR_MER;
    REGISTER(FLASH_base+FLASH_CR) |= FLASH_CR_START;


}

void flashWrite(void* dest, void* src, u32 n)
{
    volatile u16* dest_ptr=dest;
    volatile u16* src_ptr=src;
    __asm__ volatile("cpsid i");
    __asm__ volatile ("cpsid f");
    flash_unlock();
    REGISTER(FLASH_base+FLASH_CR) |= FLASH_CR_PG;

    for(int i=0;i<(n>>2);i=i+2){
        while ( REGISTER(FLASH_base+FLASH_SR)&FLASH_SR_BSY);
        dest_ptr[i]=src_ptr[i+1];
        while ( REGISTER(FLASH_base+FLASH_SR)&FLASH_SR_BSY);
        dest_ptr[i+1]=src_ptr[i];
    }
    REGISTER(FLASH_base+FLASH_CR) &= ~FLASH_CR_PG;
    flash_lock();
    __asm__ volatile ("cpsie f");
    __asm__ volatile ("cpsie i");
    
}


