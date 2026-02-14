#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>
#include <psyq/libapi.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "main/fsqueue.h"

const s32 D_80028A18 = 0x80052F00;

const s32 pad_rodata_80028A1C = 0;

const RECT D_80028A20 = { SCREEN_WIDTH, 256, 192, SCREEN_HEIGHT };

const s32 pad_rodata_80028A28 = 0;

// ========================================
// MAP
// ========================================

void func_80066D90(void) // 0x80066D90
{
    s32       i;
    DR_TPAGE* var1; // Guessed type.
    TILE*     var2; // Guessed type.

    for (i = 0; i < 63; i++)
    {
        var1 = PSX_SCRATCH;
        setDrawTPage(var1, 0, 1, getTPageN(0, 2, 0, 0));
        DrawPrim(var1);

        var2 = PSX_SCRATCH;
        setlen(var2, 3);

        setRGBC0(var2, 8, 8, 8, PRIM_RECT | RECT_BLEND); // `setTile(); setSemiTrans();`
        setXY0Fast(var2, -160, -224);
        setWHFast(var2, 320, 448);
        DrawPrim(var2);

        Fs_QueueUpdate();
        VSync(SyncMode_Wait);
    }

    Fs_QueueWaitForEmpty();
}

void func_80066E40(void) // 0x80066E40
{
    DrawSync(SyncMode_Wait);
    StoreImage(&D_80028A20, FS_BUFFER_3);
    DrawSync(SyncMode_Wait);
}

void func_80066E7C(void) // 0x80066E7C
{
    LoadImage(&D_80028A20, FS_BUFFER_3);
    DrawSync(SyncMode_Wait);
}
