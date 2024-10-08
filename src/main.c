#include "game.h"

// Push into .rodata by wrapping both pointers in a struct
const OverlayAddresses OVERLAY_POINTERS = {
    .dynamic_overlay  = 0x800C9578,
    .bodyprog_overlay = 0x80024B60,
};

INCLUDE_ASM("asm/main/nonmatchings/main", main);
