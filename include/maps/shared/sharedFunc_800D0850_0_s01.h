#include "inline_no_dmpsx.h"

void sharedFunc_800D0850_0_s01(VECTOR3* vec0, VECTOR3* vec1)
{
#if !defined(MAP0_S00)
    SVECTOR   vec0Delta;
    SVECTOR   vec1Delta;
    MATRIX    matUnused0;
    MATRIX    worldMat;
    s32       depth;
    s32       clutBase;
    s32       primCodeHack;
    GsOT*     ot;
    POLY_FT4* prim;

    ot = &g_OrderingTable0[g_ActiveBufferIdx];

    GsInitCoordinate2(NULL, &g_SysWork.coord_22F8);
    g_SysWork.coord_22F8.flg        = false;
    g_SysWork.coord_22F8.coord.t[0] = Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vx);
    g_SysWork.coord_22F8.coord.t[1] = Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vy);
    g_SysWork.coord_22F8.coord.t[2] = Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vz);

    func_80049B6C(&g_SysWork.coord_22F8, &matUnused0, &worldMat);

    gte_SetRotMatrix(&worldMat);
    gte_SetTransMatrix(&worldMat);

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

    // Return if `depth / 2` isn't in range `[1, 158]`.
    if ((depth >> 1) < 1 || (depth >> 1) > 158)
    {
        return;
    }

    primCodeHack = 0x2C;
    setlen(prim, 9); setcode(prim, primCodeHack); // @hack Line should be `setPolyFT4(prim)`, `primCodeHack` is needed to remove tpage `li 0x2C` insn.
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
            if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 0x2))
            {
                prim->r0 = 0xFF;
                prim->g0 = 0xFF;
                prim->b0 = 0xFF;
            }
            else if (g_SysWork.field_2388.isFlashlightOn_15)
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
            else if (!(g_SysWork.field_2388.field_1C[1].field_0.field_0.s_field_0.field_0 & 0x1))
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
    prim->clut = clutBase | 0x30;

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
#endif
}
