#include "inline_no_dmpsx.h"

void sharedFunc_800CFFD8_0_s01(VECTOR3* vec0, q3_12* rotX, q3_12* rotY)
{
#if !defined(MAP0_S00)
    SVECTOR           startRelPos;
    SVECTOR           endRelPos;
    MATRIX            mtxUnused;
    MATRIX            worldMtx;
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

    g_SysWork.coord_22F8.flg        = 0;
    g_SysWork.coord_22F8.coord.t[0] = Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vx);
    g_SysWork.coord_22F8.coord.t[1] = Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vy);
    g_SysWork.coord_22F8.coord.t[2] = Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vz);

    func_80049B6C(&g_SysWork.coord_22F8, &mtxUnused, &worldMtx);

    gte_SetRotMatrix(&worldMtx);
    gte_SetTransMatrix(&worldMtx);

    beamDirY      = FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.weaponAttack_F].field_0, Math_Cos(*rotY), Q12_SHIFT);
    beamDirX      = FP_MULTIPLY(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.weaponAttack_F].field_0, Math_Sin(*rotY), Q12_SHIFT), Math_Sin(*rotX), Q12_SHIFT);
    beamDirZ      = FP_MULTIPLY(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.weaponAttack_F].field_0, Math_Sin(*rotY), Q12_SHIFT), Math_Cos(*rotX), Q12_SHIFT);
    beamStart.vx  = vec0->vx;
    beamStart.vy  = vec0->vy;
    beamStart.vz  = vec0->vz;
    beamOffset.vx = beamDirX;
    beamOffset.vy = beamDirY;
    beamOffset.vz = beamDirZ;

    PushMatrix();
    cond = func_8006DA08(&sp60, &beamStart, &beamOffset, &g_SysWork.player_4C.chara_0);
    PopMatrix();

    primCount = cond ? (FP_FROM(sp60.field_14, Q12_SHIFT) + 1) : 16;

    for (i = 0; i < primCount; i++)
    {
        beamStart.vx = vec0->vx + FP_MULTIPLY(beamDirX, i, 4);
        beamStart.vy = vec0->vy + FP_MULTIPLY(beamDirY, i, 4);
        beamStart.vz = vec0->vz + FP_MULTIPLY(beamDirZ, i, 4);

        startRelPos.vx = Q12_TO_Q8(beamStart.vx - g_SysWork.player_4C.chara_0.position_18.vx);
        startRelPos.vy = Q12_TO_Q8(beamStart.vy - g_SysWork.player_4C.chara_0.position_18.vy);
        startRelPos.vz = Q12_TO_Q8(beamStart.vz - g_SysWork.player_4C.chara_0.position_18.vz);
        gte_ldv0(&startRelPos);
        gte_rtps();

        polyGt4 = (POLY_GT4*)GsOUT_PACKET_P;

        beamOffset.vx = vec0->vx + FP_MULTIPLY(beamDirX, (i + 1), 4);
        beamOffset.vy = vec0->vy + FP_MULTIPLY(beamDirY, (i + 1), 4);
        beamOffset.vz = vec0->vz + FP_MULTIPLY(beamDirZ, (i + 1), 4);
        endRelPos.vx  = Q12_TO_Q8(beamOffset.vx - g_SysWork.player_4C.chara_0.position_18.vx);
        endRelPos.vy  = Q12_TO_Q8(beamOffset.vy - g_SysWork.player_4C.chara_0.position_18.vy);
        endRelPos.vz  = Q12_TO_Q8(beamOffset.vz - g_SysWork.player_4C.chara_0.position_18.vz);

        gte_stsxy(&polyGt4->x0);
        gte_stszotz(&zScreenStart);
        zScreenStart = zScreenStart >> 1;
        if (zScreenStart < 1 || zScreenStart >= 0xFF)
        {
            continue;
        }

        if (i == (primCount - 1))
        {
            endRelPos.vx = Q12_TO_Q8(sp60.field_4.vx - g_SysWork.player_4C.chara_0.position_18.vx);
            endRelPos.vy = Q12_TO_Q8(sp60.field_4.vy - g_SysWork.player_4C.chara_0.position_18.vy);
            endRelPos.vz = Q12_TO_Q8(sp60.field_4.vz - g_SysWork.player_4C.chara_0.position_18.vz);
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
            setSemiTrans(polyGt4, 1);
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
