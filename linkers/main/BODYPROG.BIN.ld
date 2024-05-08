SECTIONS
{
    __romPos = 0;
    _gp = 0x80022BB0;
    bodyprog_ROM_START = __romPos;
    bodyprog_VRAM = ADDR(.bodyprog);
    .bodyprog 0x80024B60 : AT(bodyprog_ROM_START) SUBALIGN(8)
    {
        FILL(0x00000000);
        bodyprog_RODATA_START = .;
        build/main/asm/main/bodyprog/data/bodyprog.rodata.o(.rodata);
        . = ALIGN(., 16);
        bodyprog_RODATA_END = .;
        bodyprog_RODATA_SIZE = ABSOLUTE(bodyprog_RODATA_END - bodyprog_RODATA_START);
        bodyprog_TEXT_START = .;
        build/main/src/main/bodyprog.o(.text);
        . = ALIGN(., 16);
        bodyprog_TEXT_END = .;
        bodyprog_TEXT_SIZE = ABSOLUTE(bodyprog_TEXT_END - bodyprog_TEXT_START);
        bodyprog_DATA_START = .;
        bodyprog_data = .;
        build/main/asm/main/bodyprog/data/bodyprog.data.o(.data);
        . = ALIGN(., 16);
        bodyprog_DATA_END = .;
        bodyprog_DATA_SIZE = ABSOLUTE(bodyprog_DATA_END - bodyprog_DATA_START);
        bodyprog_BSS_START = .;
        build/main/src/main/bodyprog.o(.bss);
        . = ALIGN(., 16);
        bodyprog_BSS_END = .;
        bodyprog_BSS_SIZE = ABSOLUTE(bodyprog_BSS_END - bodyprog_BSS_START);
    }
    __romPos += SIZEOF(.bodyprog);
    __romPos = ALIGN(__romPos, 16);
    . = ALIGN(., 16);
    bodyprog_ROM_END = __romPos;
    bodyprog_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
