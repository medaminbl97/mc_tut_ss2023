/* Simple linker skript for ARM Cortex M4 Tiva
 * Norbert Balbierer
 */
HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x06000;
MEMORY
{
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x00040000
	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00008000
}

heap_size = 0x6000; /* 2K */

SECTIONS {


    .text : AT (0x00000000)
    {
        . = ALIGN(4);
        KEEP(*(.vectors)) /* Startup code */
        _start_text = .;
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        _end_text = .;
    } >FLASH

        .ARM.extab :
        {
                *(.ARM.extab* .gnu.linkonce.armextab.*)
        } > FLASH

        __exidx_start = .;
        .ARM.exidx :
        {
                *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        } > FLASH
        __exidx_end = .;

    _end_text = .;

    .data : AT (_end_text)
    {
        _start_data = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _end_data = .;
    } >SRAM

    .bss :
    {
         . = ALIGN(4);
        _start_bss = .;
	__bss_start__ = _start_bss;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _end_bss = .;
	__bss_end__ = _end_bss;
    } >SRAM

    . = ALIGN(4);
    .heap :
    {
    	__HeapBase = .;
        __end__ = .;
        /* _heap_start = .; */
        /* "end" is used by newlib's syscalls!!! */
        PROVIDE(end = .);
        PROVIDE(_heap_start = end );
        . = . + heap_size;
        PROVIDE(_heap_end = .);
	__HeapLimit = .;
    } >SRAM

    .ARM.attributes 0 : { *(.ARM.attributes) }

    .stack_dummy (COPY):
    {
        _end_stack = .;
        *(.stack*)
    } > SRAM

    /* Set stack top to end of RAM, and stack limit move down by
     * size of stack_dummy section */
    _start_stack = ORIGIN(SRAM) + LENGTH(SRAM);
    _size_stack = _start_stack - SIZEOF(.stack_dummy);
    PROVIDE(__stack = _start_stack);

    /* Check if data + heap + stack exceeds RAM limit */
    ASSERT(_size_stack >= _heap_end, "region RAM overflowed with stack")
}
_end = .;

