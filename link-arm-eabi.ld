/* link-arm-eabi.ld - linker script for arm eabi */
ENTRY(_start)
 
SECTIONS
{
    /* Starts at LOADER_ADDR. */
    . = 0x10000;
    _start = .;
    _text_start = .;
    .text :
    {
        KEEP(*(.text.boot))
        *(.text)
    }
    . = ALIGN(4096); /* align to page size */
    _text_end = .;
 
    _rodata_start = .;
    .rodata :
    {
        *(.rodata)
    }
    . = ALIGN(4096); /* align to page size */
    _rodata_end = .;
 
    _data_start = .;
    .data :
    {
        *(.data)
    }
    . = ALIGN(4096); /* align to page size */
    _data_end = .;
 
    __bss_start__ = .;
    .bss :
    {
        bss = .;
        *(.bss)
    }
    . = ALIGN(4096); /* align to page size */
    __bss_end__ = .;
    _end = .;
. = ALIGN(8);
  . = . + 0x14000;         /* SVC stack */
  stack_top = .;
 . = . + 0x100; /* some blank space */
 __heap_start = .;
}

