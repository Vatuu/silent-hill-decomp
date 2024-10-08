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
        header_s = .;
        build/asm/main/header.s.o(.data);
        header_DATA_END = .;
        header_DATA_SIZE = ABSOLUTE(header_DATA_END - header_DATA_START);
    }
    __romPos += SIZEOF(.header);
    header_ROM_END = __romPos;
    header_VRAM_END = .;

    main_ROM_START = __romPos;
    main_VRAM = ADDR(.main);
    .main 0x80010000 : AT(main_ROM_START) SUBALIGN(2)
    {
        FILL(0x00000000);
        main_RODATA_START = .;
        build/src/main.c.o(.rodata);
        build/asm/main/data/psyq.rodata.s.o(.rodata);
        . = ALIGN(., 2);
        main_RODATA_END = .;
        main_RODATA_SIZE = ABSOLUTE(main_RODATA_END - main_RODATA_START);
        main_TEXT_START = .;
        build/src/main.c.o(.text);
        build/asm/main/psyq.s.o(.text);
        . = ALIGN(., 2);
        main_TEXT_END = .;
        main_TEXT_SIZE = ABSOLUTE(main_TEXT_END - main_TEXT_START);
        main_DATA_START = .;
        main_data__s = .;
        build/asm/main/data/main.data.s.o(.data);
        psyq_data__s = .;
        build/asm/main/data/psyq.data.s.o(.data);
        . = ALIGN(., 2);
        main_DATA_END = .;
        main_DATA_SIZE = ABSOLUTE(main_DATA_END - main_DATA_START);
        main_SDATA_START = .;
        build/asm/main/data/main.sdata.s.o(.sdata);
        . = ALIGN(., 2);
        main_SDATA_END = .;
        main_SDATA_SIZE = ABSOLUTE(main_SDATA_END - main_SDATA_START);
    }
    main_bss_VRAM = ADDR(.main_bss);
    .main_bss (NOLOAD) : SUBALIGN(2)
    {
        FILL(0x00000000);
        main_SBSS_START = .;
        build/asm/main/data/psyq.sbss.s.o(.sbss);
        . = ALIGN(., 2);
        main_SBSS_END = .;
        main_SBSS_SIZE = ABSOLUTE(main_SBSS_END - main_SBSS_START);
        main_BSS_START = .;
        build/src/main.c.o(.bss);
        build/asm/main/psyq.s.o(.bss);
        build/asm/main/data/13494.bss.s.o(.bss);
        . = ALIGN(., 2);
        main_BSS_END = .;
        main_BSS_SIZE = ABSOLUTE(main_BSS_END - main_BSS_START);
    }
    __romPos += SIZEOF(.main);
    __romPos = ALIGN(__romPos, 2);
    . = ALIGN(., 2);
    main_ROM_END = __romPos;
    main_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
