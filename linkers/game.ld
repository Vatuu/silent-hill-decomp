SECTIONS
{
    __romPos = 0;
    _gp = 0x80022BB0;
    game_ROM_START = __romPos;
    game_VRAM = ADDR(.game);
    .game 0x80024B60 : AT(game_ROM_START) SUBALIGN(8)
    {
        FILL(0x00000000);
        game_RODATA_START = .;
        build/game/src/game/overlay.o(.rodata);
        . = ALIGN(., 16);
        game_RODATA_END = .;
        game_RODATA_SIZE = ABSOLUTE(game_RODATA_END - game_RODATA_START);
        game_TEXT_START = .;
        build/game/src/game/overlay.o(.text);
        . = ALIGN(., 16);
        game_TEXT_END = .;
        game_TEXT_SIZE = ABSOLUTE(game_TEXT_END - game_TEXT_START);
        game_DATA_START = .;
        overlay_data = .;
        build/game/asm/game/data/overlay.data.o(.data);
        . = ALIGN(., 16);
        game_DATA_END = .;
        game_DATA_SIZE = ABSOLUTE(game_DATA_END - game_DATA_START);
        game_BSS_START = .;
        build/game/src/game/overlay.o(.bss);
        . = ALIGN(., 16);
        game_BSS_END = .;
        game_BSS_SIZE = ABSOLUTE(game_BSS_END - game_BSS_START);
    }
    __romPos += SIZEOF(.game);
    __romPos = ALIGN(__romPos, 16);
    . = ALIGN(., 16);
    game_ROM_END = __romPos;
    game_VRAM_END = .;

    /DISCARD/ :
    {
        *(*);
    }
}
