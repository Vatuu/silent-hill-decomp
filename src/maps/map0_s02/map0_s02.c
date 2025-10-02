#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/map0_s02.h"

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CACF0

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CB17C

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CB254

#include "maps/shared/Particle_Update.h" // 0x800CB560

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02", sharedFunc_800CEB24_0_s00); // 0x800CBBF4

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CC110

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02", sharedFunc_800CEFD0_1_s02); // 0x800CC260

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CC628

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CC754

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CC75C

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CC814

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CC89C

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CCA54

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CCBD4

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CCC8C

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CCE24

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02", func_800CCE44);

void func_800CD6BC(VECTOR3* vec0, VECTOR3* vec1) // 0x800CD6BC
{
    SVECTOR   vec0Delta;
    SVECTOR   vec1Delta;
    MATRIX    mtxUnused0;
    MATRIX    worldMtx;
    s32       depth;
    GsOT*     ot;
    s32       clutBase;
    POLY_FT4* prim;
    s32       primCodeHack;

    ot = &g_OrderingTable0[g_ActiveBufferIdx];

    GsInitCoordinate2(NULL, &g_SysWork.coord_22F8);
    g_SysWork.coord_22F8.flg        = 0;
    g_SysWork.coord_22F8.coord.t[0] = Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vx);
    g_SysWork.coord_22F8.coord.t[1] = Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vy);
    g_SysWork.coord_22F8.coord.t[2] = Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vz);

    func_80049B6C(&g_SysWork.coord_22F8, &mtxUnused0, &worldMtx);

    gte_SetRotMatrix(&worldMtx);
    gte_SetTransMatrix(&worldMtx);

    prim = (POLY_FT4*)GsOUT_PACKET_P;

    vec0Delta.vx = Q12_TO_Q8(vec0->vx - g_SysWork.player_4C.chara_0.position_18.vx);
    vec0Delta.vy = Q12_TO_Q8(vec0->vy - g_SysWork.player_4C.chara_0.position_18.vy);
    vec0Delta.vz = Q12_TO_Q8(vec0->vz - g_SysWork.player_4C.chara_0.position_18.vz);

    gte_ldv0(&vec0Delta);
    gte_rtps();

    vec1Delta.vx = Q12_TO_Q8(vec1->vx - g_SysWork.player_4C.chara_0.position_18.vx);
    vec1Delta.vy = Q12_TO_Q8(vec1->vy - g_SysWork.player_4C.chara_0.position_18.vy);
    vec1Delta.vz = Q12_TO_Q8(vec1->vz - g_SysWork.player_4C.chara_0.position_18.vz);

    gte_stsxy(&prim->x0);
    gte_stszotz(&depth);

    gte_ldv0(&vec1Delta);
    gte_rtps();
    gte_stsxy(&prim->x1);

    // Return if depth/2 isn't between 1 and 158 (inclusive)
    if ((depth >> 1) < 1 || (depth >> 1) > 158)
    {
        return;
    }

    primCodeHack = 0x2C;
    setlen(prim, 9); setcode(prim, primCodeHack); // @hack line should be setPolyFT4(prim), primCodeHack needed to remove tpage `li 0x2C` insn.
    prim->tpage = 0x2C;

    switch (g_MapOverlayHeader.field_16)
    {
        case 0:
            break;

        case 1:
            prim->r0 = 0xFF;
            prim->g0 = 0xFF;
            prim->b0 = 0xFF;
            break;

        case 2:
            if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 2))
            {
                prim->r0 = 0xFF;
                prim->g0 = 0xFF;
                prim->b0 = 0xFF;
            }
            else if (g_SysWork.field_2388.isFlashlightOn_15 != 0)
            {
                prim->r0 = 0xFF;
                prim->g0 = 0xFF;
                prim->b0 = 0xFF;
            }
            else if (g_SysWork.field_2388.field_1C[0].field_0.field_0.s_field_0.field_0 & 1)
            {
                prim->r0 = 0x30;
                prim->g0 = 0x30;
                prim->b0 = 0x30;
            }
            else if (!(g_SysWork.field_2388.field_1C[1].field_0.field_0.s_field_0.field_0 & 1))
            {
                prim->r0 = 0xFF;
                prim->g0 = 0xFF;
                prim->b0 = 0xFF;
            }
            else
            {
                prim->r0 = 0x30;
                prim->g0 = 0x30;
                prim->b0 = 0x30;
            }
            break;

        case 3:
            prim->r0 = 0x40;
            prim->g0 = 0x20;
            prim->b0 = 0x00;
            break;
    }

    prim->u0 = 10;
    prim->v0 = 116;
    prim->u1 = 10;
    prim->v1 = 116;
    prim->u2 = 13;
    prim->v2 = 116;
    prim->u3 = 13;
    prim->v3 = 116;

    clutBase   = ((depth >> 6) + 104) << 6;
    depth      = depth >> 1;
    prim->clut = (clutBase | 0x30);

    if ((prim->x0 < prim->x1 && prim->y0 < prim->y1) ||
        (prim->x0 > prim->x1 && prim->y0 > prim->y1))
    {
        prim->x2 = prim->x0 - 1;
        prim->x3 = prim->x1 - 1;
    }
    else
    {
        prim->x2 = prim->x0 + 1;
        prim->x3 = prim->x1 + 1;
    }

    prim->y2 = prim->y0 + 1;
    prim->y3 = prim->y1 + 1;

    addPrim(&ot->org[depth], prim);

    GsOUT_PACKET_P = (PACKET*)&prim[1];
}

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CDAA8

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02", func_800CDD9C);

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CE1C8

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CE204

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CE210

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CE370

s32 func_800CE548(void) // 0x800CE548
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CE550

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CE600

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CE618

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CE640

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CE658

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CE680

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CE724

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CE734

void func_800CE740(void) {}

void func_800CE748(void) {}

void func_800CE750(void) {}

void func_800CE758(void) {}

void func_800CE760(void) {}

s32 func_800CE768(void) // 0x800CE768
{
    return 0;
}

void func_800CE770(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CE778

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CE788

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CE7C8

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CE7DC

INCLUDE_ASM("asm/maps/map0_s02/nonmatchings/map0_s02", Map_RoomIdxGet); // 0x800CE7EC

void func_800CE884(s32 arg0) // 0x800CE884
{
    if (arg0 != 0)
    {
        func_800CE8B8();
        return;
    }

    sharedFunc_800CE934_0_s02();
}

void func_800CE8B8(void) // 0x800CE8B8
{
    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 5:
            func_8003640C(6);
            break;

        case 18:
            func_8003640C(!Savegame_EventFlagGet(EventFlag_379) ? 29 : 7);
            break;

        case 17:
            func_8003640C(7);
            break;
    }
}

#include "maps/shared/sharedFunc_800CE934_0_s02.h" // 0x800CE934

void Gfx_LoadingScreen_StageString(void) {}
