#include "inline_no_dmpsx.h"
#include "maps/particle.h"

// Particle-related functions.
//
// TODO:
//  - This should be a separate .c file/split in each map overlay, but for now #including this .c works.
//  - sharedData and structs that are only used in this file need to be moved from `shared.h` into `particle.h`
//  - A lot more particle funcs that can be merged here, but the funcs included in each map varies a lot, will
//    likely need a lot of `#ifdef MAPX_SXX`.

// TODO: Figure out what these maps have in common.
// `sharedData_800E32D0_0_s00` writes and `sharedFunc_800D0CB8_0_s00` are gated behind `SET_800E32D0`.
#if defined(MAP0_S00) || defined(MAP1_S02) || defined(MAP1_S03) || \
    defined(MAP4_S02) || defined(MAP4_S03) || defined(MAP4_S04) || \
    defined(MAP4_S05) || defined(MAP5_S00) || defined(MAP6_S00) || defined(MAP6_S03)
#define SET_800E32D0 1
#endif

void sharedFunc_800D08B8_0_s00(s8 arg0, u32 arg1)
{
    s32 temp_a1;
    s32 shiftAmt;
    s32 var_s0;
    s32 var_s1;

    if (arg1 != 127)
    {
        if (arg1 == 2)
        {
            D_800C39A0 = 3;
        }
        else
        {
            D_800C39A0 = arg1;
        }
    }

    sharedData_800E0CBA_0_s00 = arg0;

#ifdef SET_800E32D0
    sharedData_800E32D0_0_s00 = 0;
#endif

    switch (arg0)
    {
        case 0:
            var_s1                    = 0;
            var_s0                    = 0;
            sharedData_800DFB6C_0_s00 = 0;
            sharedData_800DFB70_0_s00 = 0;
            break;

        case 1:
            var_s1                    = 1;
            var_s0                    = 0;
            sharedData_800DFB6C_0_s00 = 1;
            sharedData_800DFB70_0_s00 = 0;
            break;

        case 2:
            var_s1                    = 1;
            var_s0                    = 1;
            sharedData_800DFB6C_0_s00 = 1;
            sharedData_800DFB70_0_s00 = 0;
            break;

        case 5:
            var_s1                    = 2;
            var_s0                    = 0;
            sharedData_800DFB6C_0_s00 = 0;
            sharedData_800DFB70_0_s00 = 1;
#ifdef SET_800E32D0
            sharedData_800E32D0_0_s00 = 135000;
#endif
            break;

        case 6:
            var_s1                    = 2;
            var_s0                    = 1;
            sharedData_800DFB6C_0_s00 = 0;
            sharedData_800DFB70_0_s00 = 1;
#ifdef SET_800E32D0
            sharedData_800E32D0_0_s00 = 135000;
#endif
            break;

        default:
            var_s0                    = 0;
            var_s1                    = 0;
            sharedData_800DFB6C_0_s00 = 0;
            sharedData_800DFB70_0_s00 = 0;
            break;
    }

    if (var_s1 == 0)
    {
        sharedData_800E0CB0_0_s00 = var_s0 * 0x1000;
    }
    else
    {
        sharedData_800E0CB0_0_s00 = (var_s1 * 0x4000) | (var_s0 * 0x1000);

        temp_a1  = var_s0 + 4;
        shiftAmt = (2 - var_s1) * 6;

        sharedData_800E0CB0_0_s00 = sharedData_800E0CB0_0_s00 | (temp_a1 << shiftAmt) | (temp_a1 << (shiftAmt + 3));
    }

    sharedFunc_800D0A60_0_s00(D_800C39A0);

    sharedData_800E0CA8_0_s00 = var_s1;
    sharedData_800E0CAC_0_s00 = var_s0;
}

void sharedFunc_800D0A60_0_s00(s32 caseArg)
{
    s32 var0;
    s32 var1;
    s32 var2;

    D_800C39A0 = caseArg;

    switch (caseArg)
    {
        case 0:
        case 2:
        case 3:
        case 7:
        case 9:
        case 11:
            var0 = 1;
            var1 = 0;
            var2 = 0;
            break;

        case 4:
            var0 = 0;
            var1 = 1;
            var2 = 0;
            break;

        case 5:
        case 10:
            var0 = 1;
            var1 = 1;
            var2 = 0;
            break;

        case 6:
        case 8:
            var0 = 1;
            var1 = 0;
            var2 = 1;
            break;

        default:
            var2 = 0;
            var1 = 0;
            var0 = 0;
            break;
    }

    sharedData_800E0CB0_0_s00 = (u16)sharedData_800E0CB0_0_s00 | ((var0 | (var1 * 16) | (var2 << 8)) << 16);
    sharedData_800E0CB8_0_s00 = (sharedData_800E0CB8_0_s00 & 0xF) | ((sharedData_800E0CB0_0_s00 >> 12) & 0x1110);
}

bool sharedFunc_800D0B18_0_s00(s32 arg0)
{
    s32 temp_a0_2;
    u16 temp;

    if (g_SysWork.field_234A)
    {
        g_SysWork.field_2349 = arg0;
        g_SysWork.field_2348 = arg0;

        if (arg0 == 0)
        {
            sharedData_800E0CA8_0_s00 = 0;
        }
        else if (arg0 < 5)
        {
            sharedData_800E0CA8_0_s00 = 1;
        }
        else
        {
            sharedData_800E0CA8_0_s00 = 2;
        }

        if (sharedData_800E0CA8_0_s00 != 0)
        {
            sharedData_800E0CAC_0_s00 = (arg0 - 1) % 4u;
        }

        switch (sharedData_800E0CA8_0_s00)
        {
            case 1:
                sharedData_800DFB6C_0_s00 = 1;
                break;

            case 2:
                sharedData_800DFB70_0_s00 = 1;

#ifdef SET_800E32D0
                sharedData_800E32D0_0_s00 = 0;
#endif
                break;

            default:
                break;
        }

        sharedData_800E0CB4_0_s00 &= 0xFFF;
        temp                       = (((u16)sharedData_800E0CA8_0_s00 * 4) + sharedData_800E0CAC_0_s00) << Q12_SHIFT;
        temp_a0_2                  = sharedData_800E0CB4_0_s00 | temp;
        sharedData_800E0CB4_0_s00  = (sharedData_800E0CB4_0_s00 | temp) & 0xF000;
        temp_a0_2                  = (temp_a0_2 * 8) & 0xE38;

        if (sharedData_800E0CA8_0_s00 != 0)
        {
            sharedData_800E0CB4_0_s00 += temp_a0_2 + (((sharedData_800E0CAC_0_s00 + 4) << Q12_SHIFT) >> (sharedData_800E0CA8_0_s00 * 6));
        }
        else
        {
            sharedData_800E0CB4_0_s00 += temp_a0_2;
        }

        if (sharedData_800E0CB4_0_s00 != sharedData_800E0CB6_0_s00)
        {
            g_SysWork.field_234A = false;
        }

// TODO: Do these maps have anything in common?
#if defined(MAP0_S00) || defined(MAP0_S01) || defined(MAP0_S02) || \
    defined(MAP1_S00) || defined(MAP1_S02) || defined(MAP1_S03) || \
    defined(MAP1_S06) || defined(MAP2_S00) || defined(MAP2_S02) || \
    defined(MAP3_S00) || defined(MAP3_S01) || defined(MAP3_S06) || \
    defined(MAP4_S02) || defined(MAP4_S03) || defined(MAP4_S04) || \
    defined(MAP4_S05) || defined(MAP5_S00) || defined(MAP5_S01) || \
    defined(MAP5_S03) || defined(MAP6_S00) || defined(MAP6_S03) || \
    defined(MAP7_S03)
        if (sharedData_800E0CAC_0_s00 == 0 || sharedData_800E0CAC_0_s00 == 2)
        {
            g_Particle_PrevPosition.vy = Q12(0.0005f);
        }
        else
        {
            g_Particle_PrevPosition.vy = Q12(0.0f);
        }
#endif

        sharedData_800E0CB8_0_s00 = (sharedData_800E0CB8_0_s00 & ~0xF) + (sharedData_800E0CB4_0_s00 >> Q12_SHIFT);
        return true;
    }

    return false;
}

#ifdef SET_800E32D0
void sharedFunc_800D0CB8_0_s00(void)
{
    u8 unkValDiv4;

    switch (g_SavegamePtr->mapOverlayId_A4)
    {
        case MapOverlayId_MAP0_S00:
        case MapOverlayId_MAP0_S01: // @unused Checks for `MAP0_S01`, but map itself doesn't contain this func?
        case MapOverlayId_MAP1_S02:
        case MapOverlayId_MAP1_S03:
        case MapOverlayId_MAP4_S02:
            unkValDiv4 = sharedData_800E32CC_0_s00 >> 2; // `sharedData_800E32CC_0_s00 / 4`

            if ((sharedData_800E32CC_0_s00 - sharedData_800DD58C_0_s00) > 15)
            {
                sharedData_800E32CC_0_s00 -= 15;
            }
            else if ((sharedData_800DD58C_0_s00 - sharedData_800E32CC_0_s00) > 15)
            {
                sharedData_800E32CC_0_s00 += 15;
            }

            if (sharedData_800E32CC_0_s00 == 0)
            {
                g_SysWork.field_234B_0 = 0;
                Sd_SfxStop(Sfx_Unk1360);
            }

            if (g_SysWork.field_234B_0 != 0)
            {
                func_8005DE0C(Sfx_Unk1360, &g_SysWork.playerWork_4C.player_0.position_18, unkValDiv4, Q12(0.0f), 0);
            }
            else if (sharedData_800E32CC_0_s00 != 0)
            {
                SD_Call(Sfx_Unk1360);
                g_SysWork.field_234B_0 = 1;
            }
    }
}
#endif

#ifdef SET_800E32D0
    #undef SET_800E32D0
#endif

void sharedFunc_800D0E04_0_s00(void)
{
    Sd_SfxStop(Sfx_Unk1360);
}

void sharedFunc_800CFFD8_0_s01(VECTOR3* vec0, q3_12* rotX, q3_12* rotY)
{
#if !defined(MAP0_S00)
    SVECTOR           startRelPos;
    SVECTOR           endRelPos;
    MATRIX            matUnused;
    MATRIX            worldMat;
    s_func_800700F8_2 sp60;
    VECTOR3           beamStart;
    VECTOR3           beamOffset;
    SVECTOR           polyFt3Pos;
    s32               zScreenStart;
    s32               zScreenEnd;
    s32               beamDirX;
    s32               beamDirY;
    s32               beamDirZ;
    bool              cond;
    s32               i;
    s32               polyVCoord;
    s32               primCount;
    GsOT*             ot;
    POLY_GT4*         polyGt4;
    POLY_FT3*         polyFt3;

    ot = &g_OrderingTable0[g_ActiveBufferIdx];
    GsInitCoordinate2(NULL, &g_SysWork.coord_22F8);

    g_SysWork.coord_22F8.flg        = false;
    g_SysWork.coord_22F8.coord.t[0] = Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vx);
    g_SysWork.coord_22F8.coord.t[1] = Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vy);
    g_SysWork.coord_22F8.coord.t[2] = Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vz);

    func_80049B6C(&g_SysWork.coord_22F8, &matUnused, &worldMat);

    gte_SetRotMatrix(&worldMat);
    gte_SetTransMatrix(&worldMat);

    beamDirY      = Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, Math_Cos(*rotY));
    beamDirX      = Q12_MULT(Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, Math_Sin(*rotY)), Math_Sin(*rotX));
    beamDirZ      = Q12_MULT(Q12_MULT(D_800AD4C8[g_SysWork.playerCombat_38.weaponAttack_F].field_0, Math_Sin(*rotY)), Math_Cos(*rotX));
    beamStart.vx  = vec0->vx;
    beamStart.vy  = vec0->vy;
    beamStart.vz  = vec0->vz;
    beamOffset.vx = beamDirX;
    beamOffset.vy = beamDirY;
    beamOffset.vz = beamDirZ;

    PushMatrix();
    cond = func_8006DA08(&sp60, &beamStart, &beamOffset, &g_SysWork.playerWork_4C.player_0);
    PopMatrix();

    primCount = cond ? (FP_FROM(sp60.field_14, Q12_SHIFT) + 1) : 16;

    for (i = 0; i < primCount; i++)
    {
        beamStart.vx = vec0->vx + FP_MULTIPLY(beamDirX, i, 4);
        beamStart.vy = vec0->vy + FP_MULTIPLY(beamDirY, i, 4);
        beamStart.vz = vec0->vz + FP_MULTIPLY(beamDirZ, i, 4);

        startRelPos.vx = Q12_TO_Q8(beamStart.vx - g_SysWork.playerWork_4C.player_0.position_18.vx);
        startRelPos.vy = Q12_TO_Q8(beamStart.vy - g_SysWork.playerWork_4C.player_0.position_18.vy);
        startRelPos.vz = Q12_TO_Q8(beamStart.vz - g_SysWork.playerWork_4C.player_0.position_18.vz);
        gte_ldv0(&startRelPos);
        gte_rtps();

        polyGt4 = (POLY_GT4*)GsOUT_PACKET_P;

        beamOffset.vx = vec0->vx + FP_MULTIPLY(beamDirX, i + 1, 4);
        beamOffset.vy = vec0->vy + FP_MULTIPLY(beamDirY, i + 1, 4);
        beamOffset.vz = vec0->vz + FP_MULTIPLY(beamDirZ, i + 1, 4);
        endRelPos.vx  = Q12_TO_Q8(beamOffset.vx - g_SysWork.playerWork_4C.player_0.position_18.vx);
        endRelPos.vy  = Q12_TO_Q8(beamOffset.vy - g_SysWork.playerWork_4C.player_0.position_18.vy);
        endRelPos.vz  = Q12_TO_Q8(beamOffset.vz - g_SysWork.playerWork_4C.player_0.position_18.vz);

        gte_stsxy(&polyGt4->x0);
        gte_stszotz(&zScreenStart);
        zScreenStart = zScreenStart >> 1;
        if (zScreenStart < 1 || zScreenStart >= 0xFF)
        {
            continue;
        }

        if (i == (primCount - 1))
        {
            endRelPos.vx = Q12_TO_Q8(sp60.field_4.vx - g_SysWork.playerWork_4C.player_0.position_18.vx);
            endRelPos.vy = Q12_TO_Q8(sp60.field_4.vy - g_SysWork.playerWork_4C.player_0.position_18.vy);
            endRelPos.vz = Q12_TO_Q8(sp60.field_4.vz - g_SysWork.playerWork_4C.player_0.position_18.vz);
        }

        gte_ldv0(&endRelPos);
        gte_rtps();
        gte_stsxy(&polyGt4->x1);
        polyFt3Pos.vx = polyGt4->x1;
        polyFt3Pos.vy = polyGt4->y1;

        gte_stszotz(&zScreenEnd);
        zScreenEnd = zScreenEnd >> 1;
        if (zScreenEnd >= 1 && zScreenEnd <= 254u)
        {
            setPolyGT4(polyGt4);
            setSemiTrans(polyGt4, true);
            polyGt4->tpage = 44;

            switch (Game_HyperBlasterBeamColorGet())
            {
                case 0:
                    polyGt4->r0 = (i * -17) - 1;
                    polyGt4->g0 = 0;
                    polyGt4->b0 = 0;
                    polyGt4->r1 = (i * -17) - 18;
                    polyGt4->g1 = 0;
                    polyGt4->b1 = 0;
                    polyGt4->r2 = (i * -17) - 1;
                    polyGt4->g2 = 0;
                    polyGt4->b2 = 0;
                    polyGt4->r3 = (i * -17) - 18;
                    polyGt4->g3 = 0;
                    polyGt4->b3 = 0;
                    break;

                case 1:
                    polyGt4->r0 = (i * -17) - 1;
                    polyGt4->g0 = (i * -17) - 1;
                    polyGt4->b0 = 0;
                    polyGt4->r1 = (i * -17) - 18;
                    polyGt4->g1 = (i * -17) - 18;
                    polyGt4->b1 = 0;
                    polyGt4->r2 = (i * -17) - 1;
                    polyGt4->g2 = (i * -17) - 1;
                    polyGt4->b2 = 0;
                    polyGt4->r3 = (i * -17) - 18;
                    polyGt4->g3 = (i * -17) - 18;
                    polyGt4->b3 = 0;
                    break;

                case 2:
                    polyGt4->r0 = 0;
                    polyGt4->g0 = (i * -17) - 1;
                    polyGt4->b0 = 0;
                    polyGt4->r1 = 0;
                    polyGt4->g1 = (i * -17) - 18;
                    polyGt4->b1 = 0;
                    polyGt4->r2 = 0;
                    polyGt4->g2 = (i * -17) - 1;
                    polyGt4->b2 = 0;
                    polyGt4->r3 = 0;
                    polyGt4->g3 = (i * -17) - 18;
                    polyGt4->b3 = 0;
                    break;
            }

            polyVCoord    = 116;
            polyGt4->u0   = 10;
            polyGt4->u1   = 10;
            polyGt4->v0   = polyVCoord;
            polyGt4->v1   = polyVCoord;
            polyGt4->u2   = 13;
            polyGt4->v2   = polyVCoord;
            polyGt4->u3   = 13;
            polyGt4->v3   = polyVCoord;
            polyGt4->clut = ((((zScreenStart >> 5) + 104) << 6) | 0x30);

            if ((polyGt4->x0 < polyGt4->x1 && polyGt4->y0 < polyGt4->y1) ||
                (polyGt4->x0 > polyGt4->x1 && polyGt4->y0 > polyGt4->y1))
            {
                polyGt4->x2 = polyGt4->x0 - 1;
                polyGt4->x3 = polyGt4->x1 - 1;
            }
            else
            {
                polyGt4->x2 = polyGt4->x0 + 1;
                polyGt4->x3 = polyGt4->x1 + 1;
            }

            polyGt4->y2 = polyGt4->y0 + 1;
            polyGt4->y3 = polyGt4->y1 + 1;

            addPrim(&ot->org[zScreenStart], polyGt4);
            GsOUT_PACKET_P = (PACKET*)&polyGt4[1];
        }

        if (i == (primCount - 1))
        {
            polyFt3        = (POLY_FT3*)GsOUT_PACKET_P;
            polyFt3->tpage = 44;
            polyFt3->clut  = 0x1830;
            polyFt3->u0    = 3;
            polyFt3->v0    = 112;
            polyFt3->u1    = 3;
            polyFt3->v1    = 116;
            polyFt3->u2    = 7;
            polyFt3->v2    = 112;

            setPolyFT3(polyFt3);

            polyFt3->x0 = polyFt3Pos.vx;
            polyFt3->y0 = polyFt3Pos.vy;
            polyFt3->x1 = polyFt3->x0;
            polyFt3->y2 = polyFt3->y0;
            polyFt3->x2 = polyFt3->x0 + 4;
            polyFt3->y1 = polyFt3->y0 + 4;

            switch (Game_HyperBlasterBeamColorGet())
            {
                case 0:
                    polyFt3->r0 = 192;
                    polyFt3->g0 = 0;
                    polyFt3->b0 = 0;
                    break;

                case 1:
                    polyFt3->r0 = 192;
                    polyFt3->g0 = 192;
                    polyFt3->b0 = 0;
                    break;

                case 2:
                    polyFt3->r0 = 0;
                    polyFt3->g0 = 192;
                    polyFt3->b0 = 0;
                    break;
            }

            if (zScreenStart >= 1 && zScreenStart < 0xFF)
            {
                addPrim(&ot->org[zScreenStart], polyFt3);
                GsOUT_PACKET_P = (PACKET*)&polyFt3[1];
            }
        }
    }
#endif
}

void sharedFunc_800D0850_0_s01(VECTOR3* vec0, VECTOR3* vec1)
{
#if !defined(MAP0_S00)
    SVECTOR   vec0Delta;
    SVECTOR   vec1Delta;
    MATRIX    matUnused0;
    MATRIX    worldMat;
    s32       depth;
    s32       clutBase;
    GsOT*     ot;
    POLY_FT4* prim;

    ot = &g_OrderingTable0[g_ActiveBufferIdx];

    GsInitCoordinate2(NULL, &g_SysWork.coord_22F8);
    g_SysWork.coord_22F8.flg        = false;
    g_SysWork.coord_22F8.coord.t[0] = Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vx);
    g_SysWork.coord_22F8.coord.t[1] = Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vy);
    g_SysWork.coord_22F8.coord.t[2] = Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vz);

    func_80049B6C(&g_SysWork.coord_22F8, &matUnused0, &worldMat);

    gte_SetRotMatrix(&worldMat);
    gte_SetTransMatrix(&worldMat);

    prim = (POLY_FT4*)GsOUT_PACKET_P;

    vec0Delta.vx = Q12_TO_Q8(vec0->vx - g_SysWork.playerWork_4C.player_0.position_18.vx);
    vec0Delta.vy = Q12_TO_Q8(vec0->vy - g_SysWork.playerWork_4C.player_0.position_18.vy);
    vec0Delta.vz = Q12_TO_Q8(vec0->vz - g_SysWork.playerWork_4C.player_0.position_18.vz);

    gte_ldv0(&vec0Delta);
    gte_rtps();

    vec1Delta.vx = Q12_TO_Q8(vec1->vx - g_SysWork.playerWork_4C.player_0.position_18.vx);
    vec1Delta.vy = Q12_TO_Q8(vec1->vy - g_SysWork.playerWork_4C.player_0.position_18.vy);
    vec1Delta.vz = Q12_TO_Q8(vec1->vz - g_SysWork.playerWork_4C.player_0.position_18.vz);

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

    setPolyFT4TPage(prim, 0x2C);

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
            if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)))
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
            else if (!(g_SysWork.field_2388.field_1C[1].field_0.field_0.s_field_0.field_0 & (1 << 0)))
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
