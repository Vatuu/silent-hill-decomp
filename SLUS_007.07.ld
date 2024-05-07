SECTIONS
{
    __romPos = 0;
    _gp = 0x80022BB0;
    header_ROM_START = __romPos;
    header_VRAM = ADDR(.header);
    .header : AT(header_ROM_START) SUBALIGN(2)
    {
        FILL(0x00000000);
        header_DATA_START = .;
        header = .;
        build/executable/asm/executable/header.o(.data);
        header_DATA_END = .;
        header_DATA_SIZE = ABSOLUTE(header_DATA_END - header_DATA_START);
    }
    __romPos += SIZEOF(.header);
    header_ROM_END = __romPos;
    header_VRAM_END = .;

    executable_ROM_START = __romPos;
    executable_VRAM = ADDR(.executable);
    .executable 0x80010000 : AT(executable_ROM_START) SUBALIGN(2)
    {
        FILL(0x00000000);
        executable_RODATA_START = .;
        build/executable/asm/executable/data/bootloader.rodata.o(.rodata);
        . = ALIGN(., 16);
        executable_RODATA_END = .;
        executable_RODATA_SIZE = ABSOLUTE(executable_RODATA_END - executable_RODATA_START);
        executable_TEXT_START = .;
        build/executable/src/executable/bootloader.o(.text);
        . = ALIGN(., 16);
        executable_TEXT_END = .;
        executable_TEXT_SIZE = ABSOLUTE(executable_TEXT_END - executable_TEXT_START);
        executable_DATA_START = .;
        bootloader = .;
        build/executable/src/executable/bootloader.o(.data);
        B940_data = .;
        build/executable/asm/executable/data/B940.data.o(.data);
        . = ALIGN(., 16);
        executable_DATA_END = .;
        executable_DATA_SIZE = ABSOLUTE(executable_DATA_END - executable_DATA_START);
        executable_BSS_START = .;
        build/executable/src/executable/bootloader.o(.bss);
        . = ALIGN(., 16);
        executable_BSS_END = .;
        executable_BSS_SIZE = ABSOLUTE(executable_BSS_END - executable_BSS_START);
    }
    __romPos += SIZEOF(.executable);
    __romPos = ALIGN(__romPos, 16);
    . = ALIGN(., 16);
    executable_ROM_END = __romPos;
    executable_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
