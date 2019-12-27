
/*_boot_checksum = 0 - (_stack_base + main + 1 + (hang + 1) * 5);*/

MEMORY
{
   rom(RX)   : ORIGIN = 0x08000000, LENGTH = 128K
   ram(WAIL) : ORIGIN = 0x20000000, LENGTH = 20K 
}

ld_stack = 0x20005000;

SECTIONS
{
        
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

        .data : AT(0x20000200) ALIGN(4)
        {
                ld_sdata = . ;

                *(.data)
                *(.data.*)

                . = ALIGN(4);
                ld_edata = . ;

        } > ram

        .bss : AT (ld_edata) ALIGN(4)
        {
                ld_sbss = . ;

                *(.bss)
                *(.bss.*)
                *(COMMON)

                . = ALIGN(4);
                ld_ebss = . ;

        } > ram
}