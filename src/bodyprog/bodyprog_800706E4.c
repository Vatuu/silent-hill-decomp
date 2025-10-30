#include "game.h"
#include "inline_no_dmpsx.h"

#include <libapi.h>
#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/joy.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_800706E4", D_80028B94);

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_800706E4", D_800294F4);

// Some kind of `Anim_UpdateX` function, included in some `s_AnimInfo` array which also had pointers to `Anim_Update1`/`Anim_Update2`.

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800706E4", func_800706E4); // 0x800706E4
