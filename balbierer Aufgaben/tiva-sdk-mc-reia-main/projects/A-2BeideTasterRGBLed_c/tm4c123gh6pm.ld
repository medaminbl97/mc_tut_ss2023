/* Linkerscript for TM4C123GH6PM
 * Norbert Balbierer
 */

HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x04000;

MEMORY
{
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x00040000
	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00008000
}

SECTIONS {

    .text : AT (0x00000000)
    {
        KEEP(*(.vectors))
        . = ALIGN(4);
        . = ALIGN(4);
        _start_text = .;

        *(.text .text.* .gnu.linkonce.t.*)
        *(.rodata .rodata* .gnu.linkonce.r.*)
        
        KEEP (*(.init))
        KEEP (*(.fini))

        . = ALIGN(4); 
        _end_text = .;   
    } >FLASH

    .ARM.extab :
    {
        . = ALIGN(4);
        *(.ARM.extab* .gnu.linkonce.armextab.*)
        . = ALIGN(4);
    } >FLASH

    .ARM.exidx :
    {
        . = ALIGN(4);
        __exidx_start = .;
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
        __exidx_end = .;
        . = ALIGN(4);
    } >FLASH

    .preinit_array     :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        . = ALIGN(4);
    } >FLASH

    .init_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
        . = ALIGN(4);
    } >FLASH

    .fini_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
        . = ALIGN(4);
    } >FLASH
    
    _sidata = LOADADDR(.data);

    .data :
    {
        . = ALIGN(4);
        _start_data = .;
        *(.data .data*) 
        . = ALIGN(4);
        _end_data = .;  
    } >SRAM AT >FLASH


    . = ALIGN(4); 
    .bss :
    {
        _start_bss = .;
	    __bss_start__ = _start_bss;
        *(.bss .bss*)
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
        . = . + HEAP_SIZE;
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

    /* Remove information from the compiler libraries */
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }
}
