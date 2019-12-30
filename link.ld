/***************************************************************

    .text — скомпилированный машинный код;              executable();

    .data — глобальные и статические переменные;        static type var = [any]; type var = [any];

    .rodata — аналог .data для неизменяемых данных;     const type var = [any];

    .bss — глобальные и статические переменные,         static type var; type var;
     которые при старте содержат нулевое значение.

***************************************************************/
MEMORY
{
   rom(RX)   : ORIGIN = 0x08000000, LENGTH = 128K
   ram(WAIL) : ORIGIN = 0x20000000, LENGTH = 20K 
}

ld_stack = 0x20005000;

SECTIONS
{
        /* Сначала идёт исполняемый код executable */
        .text : AT(0x08000000) ALIGN(4) { 
                ld_sisr = . ;
                KEEP(*(.vectors));    

                . = ALIGN(4);

                *(.text)
                *(.text.*)
                *(.rodata)
                *(.rodata.*)
 
                . = ALIGN(4);
                ld_etext = . ;

        } > rom

        /* Затем константы READ ONLY DATA */
        .rodata : AT(ld_etext) ALIGN(4)
        {
                ld_srodata = . ;

                *(.rodata)
                *(.rodata.*)

                . = ALIGN(4);
                ld_erodata = . ;

        } > rom

        /* Потом значения для инициализации переменных */
        .data : /*AT(0x20000200) ALIGN(4)*/
        {
                ld_sdata = . ;

                *(.data)
                *(.data.*)

                . = ALIGN(4);
                ld_edata = . ;

        } > ram AT> rom  /* <- Которые затем кидаем в начало оперативной памяти (в коде (у нас ассемблерный boot.s) ) */


        /* Далее, в ОПЕРАТИВНОЙ памяти, 
        ПОСЛЕ зарезервированного участка под инициализированные переменные
        записываем неинициализированные переменные
        в boot.s мы их всех memset(0)*/
        .bss :/* AT (ld_edata) ALIGN(4)*/
        {
                ld_sbss = . ;

                *(.bss)
                *(.bss.*)
                *(COMMON)

                . = ALIGN(4);
                ld_ebss = . ;

        } > ram

}/* SECTIONS */
