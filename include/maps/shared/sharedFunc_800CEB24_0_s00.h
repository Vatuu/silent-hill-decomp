#include "inline_no_dmpsx.h"

#if !defined(PARTICLE_CASE_COUNT)
    #define PARTICLE_CASE_COUNT 1
    #define HAS_PARTICLE_FALLBACK_CASE
#endif

/** Particle case switch handling.
 *
 * Maps define one or more HAS_PARTICLE_CASE_X flags to include their
 * respective switch cases.
 * When only a single case is present (`PARTICLE_CASE_COUNT == 1`), the 
 * macro below replaces `case N:` with `default:` so that the compiler
 * collapses the switch into a direct block, matching single-case maps 
 * that skip checking the case entirely.
 */
#if PARTICLE_CASE_COUNT > 1
    #define PARTICLE_CASE(id) case id
#else
    #define PARTICLE_CASE(id) default
#endif

void sharedFunc_800CEB24_0_s00(s_Particle* part)
{
#if !defined(MAP1_S00) && !defined(MAP6_S00) && !defined(MAP7_S03)
    VECTOR3     particlePos;
#endif

#if defined(HAS_PARTICLE_CASE_1)
    VECTOR3     partCorners[2];
#endif

    SVECTOR3    particlePosQ8;
    s32         zScreenStart;

    u8          primColorG;
    u8          primColorB;
    u8          primColorR;
    
    s_Particle* localPart;
    POLY_FT3*   polyFt3;

    localPart = part;
    polyFt3   = (POLY_FT3*)GsOUT_PACKET_P;

    if (part->type_1F >= 240)
    {
        part->type_1F += 16;
        if (part->stateStep_1E < 0 || part->stateStep_1E >= 31)
        {
            part->stateStep_1E = 0;
            return;
        }
    }
    else if (part->stateStep_1E != 0)
    {
#if !defined(MAP1_S00) && !defined(MAP6_S00) && !defined(MAP7_S03)
        if (sharedData_800DD591_0_s00 != 0)
        {
            particlePos = part->position0_0;

            // TODO: Check value of `sharedData_800DD591_0_s00` on each map, some of the `#if defined(MAPX)` changes in the switch below could be separate cases.
            // (fallback case might also have its own value too)
            switch (sharedData_800DD591_0_s00)
            {
#ifdef HAS_PARTICLE_CASE_1
                PARTICLE_CASE(1):
                    if (part->position0_0.vy < sharedData_800E326C_0_s00.corners_0[0].vy)
                    {
                        sharedFunc_800D0700_0_s00(&particlePos, &sharedData_800E326C_0_s00.corners_0[0], &sharedData_800E326C_0_s00.corners_0[1], 0);
                    }
                    else
                    {
                        s32 temp_v1;
                        partCorners[0].vx = sharedData_800E326C_0_s00.corners_0[0].vx;
                        partCorners[1].vx = sharedData_800E326C_0_s00.corners_0[1].vx;
                        temp_v1           = sharedData_800E326C_0_s00.corners_0[0].vz + 0x1400;
                        temp_v1          += part->position0_0.vy >> 2;
                        partCorners[1].vz = temp_v1;
                        partCorners[0].vz = temp_v1;

                        sharedFunc_800D0700_0_s00(&particlePos, &partCorners[0], &partCorners[1], 0);
                    }
                    break;
#endif

#ifdef HAS_PARTICLE_CASE_9
                PARTICLE_CASE(9):
#if defined(MAP3_S00) || defined(MAP3_S01) || defined(MAP3_S06)
                    sharedFunc_800D0700_0_s00(&particlePos, &sharedData_800E326C_0_s00.corners_0[0], &sharedData_800E326C_0_s00.corners_0[1], 0);
                    if (g_SavegamePtr->mapRoomIdx_A5 == 5)
#else
                    sharedFunc_800D0700_0_s00(&particlePos, &sharedData_800E326C_0_s00.corners_0[0], &sharedData_800E326C_0_s00.corners_0[1], 1);
                    if (particlePos.vy == 0)
#endif
                    {
                        sharedFunc_800D0700_0_s00(&particlePos, &sharedData_800E326C_0_s00.corners_0[2], &sharedData_800E326C_0_s00.corners_0[3], 0);
                    }
                    break;
#endif

#ifdef HAS_PARTICLE_CASE_10
                PARTICLE_CASE(10):
                    sharedFunc_800D0700_0_s00(&particlePos, &sharedData_800E326C_0_s00.corners_0[0], &sharedData_800E326C_0_s00.corners_0[1], 1);
                    if (particlePos.vy == 0)
                    {
                        sharedFunc_800D0700_0_s00(&particlePos, &sharedData_800E326C_0_s00.corners_0[2], &sharedData_800E326C_0_s00.corners_0[3], 1);
                        if (particlePos.vy == 0)
                        {
                            sharedFunc_800D0700_0_s00(&particlePos, &sharedData_800E326C_0_s00.corners_0[4], &sharedData_800E326C_0_s00.corners_0[5], 0);
                        }
                    }
                    break;
#endif

#ifdef HAS_PARTICLE_CASE_11
                PARTICLE_CASE(11):
#if defined(MAP0_S02)
                    if (g_SysWork.player_4C.chara_0.position_18.vx < Q12(-120.0f))
                    {
                        sharedFunc_800D0700_0_s00(&particlePos, &sharedData_800E326C_0_s00.corners_0[0], &sharedData_800E326C_0_s00.corners_0[1], 0);
                        break;
                    }
#endif
                    sharedFunc_800D0700_0_s00(&particlePos, &sharedData_800E326C_0_s00.corners_0[0], &sharedData_800E326C_0_s00.corners_0[1], 1);
                    if (particlePos.vy == 0)
                    {
                        sharedFunc_800D0700_0_s00(&particlePos, &sharedData_800E326C_0_s00.corners_0[2], &sharedData_800E326C_0_s00.corners_0[3], 1);
                        if (particlePos.vy == 0)
                        {
                            sharedFunc_800D0700_0_s00(&particlePos, &sharedData_800E326C_0_s00.corners_0[4], &sharedData_800E326C_0_s00.corners_0[5], 1);
                            if (particlePos.vy == 0)
                            {
                                sharedFunc_800D0700_0_s00(&particlePos, &sharedData_800E326C_0_s00.corners_0[6], &sharedData_800E326C_0_s00.corners_0[7], 0);
                            }
                        }
                    }
                    break;
#endif

#ifdef HAS_PARTICLE_FALLBACK_CASE
                default:
                    sharedFunc_800D0700_0_s00(&particlePos, &sharedData_800E326C_0_s00.corners_0[0], &sharedData_800E326C_0_s00.corners_0[1], 0);
                    break;
#endif
            }

            particlePosQ8.vx = Q12_TO_Q8(particlePos.vx);
            particlePosQ8.vy = Q12_TO_Q8(localPart->position0_0.vy);
            particlePosQ8.vz = Q12_TO_Q8(particlePos.vz);
        }
        else
#endif
        {
            particlePosQ8.vx = Q12_TO_Q8(localPart->position0_0.vx);
            particlePosQ8.vy = Q12_TO_Q8(localPart->position0_0.vy);
            particlePosQ8.vz = Q12_TO_Q8(localPart->position0_0.vz);
        }

        gte_ldv0(&particlePosQ8);
        gte_rtps();

        polyFt3->tpage = 44;
        polyFt3->u0    = 0;
        polyFt3->v0    = 112;
        polyFt3->u1    = 0;
        polyFt3->v1    = 115;
        polyFt3->u2    = 3;
        polyFt3->v2    = 112;

        setPolyFT3(polyFt3);

        gte_stsxy(&polyFt3->x0);
        gte_stszotz(&zScreenStart);

        if (D_800C39A0 == 1 || D_800C39A0 == 4)
        {
            primColorG = primColorB = primColorR = sharedData_800E3258_0_s00.r - (func_80055A50(zScreenStart) >> 2);
        }
        else
        {
            primColorR = sharedData_800E3258_0_s00.r;
            primColorG = sharedData_800E3258_0_s00.g;
            primColorB = sharedData_800E3258_0_s00.b;
        }

        zScreenStart = zScreenStart >> 1;

        if (localPart->stateStep_1E >= 2)
        {
            if (localPart->stateStep_1E < 31)
            {
                primColorR -= (primColorR * localPart->stateStep_1E) >> 5;
                primColorG -= (primColorG * localPart->stateStep_1E) >> 5;
                primColorB -= (primColorB * localPart->stateStep_1E) >> 5;
            }
            else
            {
                localPart->stateStep_1E = 0;
                return;
            }
        }

        polyFt3->r0 = primColorR;
        polyFt3->g0 = primColorG;
        polyFt3->b0 = primColorB;

        if (zScreenStart >= 33 && zScreenStart < (2048 - 1))
        {
            setSemiTrans(polyFt3, 1);
            polyFt3->x1 = polyFt3->x0;
            polyFt3->y2 = polyFt3->y0;

            if (zScreenStart < 64)
            {
                if (Game_FlashlightIsOn())
                {
                    // @unused Optimized out code that makes use of `D_800C39A0`
                    // Unknown what it was actually used for.
                    if (D_800C39A0 == 1 || D_800C39A0 == 4)
                    {
                        primColorB = primColorR;
                    }
                }

                polyFt3->clut = 0x1830;
                polyFt3->u0   = 3;
                polyFt3->v0   = 112;
                polyFt3->u1   = 3;
                polyFt3->v1   = 116;
                polyFt3->u2   = 7;
                polyFt3->v2   = 112;
                polyFt3->x2   = polyFt3->x0 + 4;
                polyFt3->y1   = polyFt3->y0 + 4;
            }
            else if (zScreenStart >= 256)
            {
                if (Game_FlashlightIsOn())
                {
                    // @unused Optimized out code that makes use of `D_800C39A0`
                    // Unknown what it was actually used for.
                    if (D_800C39A0 == 1 || D_800C39A0 == 4)
                    {
                        primColorB = primColorR;
                    }
                }

                polyFt3->clut = 0x19F0;
                polyFt3->x2   = polyFt3->x0 + 1;
                polyFt3->y1   = polyFt3->y0 + 1;
            }
            else
            {
                s32 clutBase;
                if (Game_FlashlightIsOn())
                {
                    // @unused Optimized out code that makes use of `D_800C39A0`, unknown what code actually used it for.
                    if (D_800C39A0 == 1 || D_800C39A0 == 4)
                    {
                        primColorB = primColorR;
                    }
                }

                clutBase = ((zScreenStart >> 5) + 96) << 6;

                do {} while (false); // @hack

                polyFt3->clut = clutBase | 0x30;
                polyFt3->x2   = polyFt3->x0 + 3;
                polyFt3->y1   = polyFt3->y0 + 3;
            }

#if defined(MAP1_S00) || defined(MAP6_S00)
            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[zScreenStart], polyFt3);
#elif defined(MAP7_S03)
            if (zScreenStart > 64 && D_800F23D4 > Q12(7.0f))
            {
                zScreenStart = 64;
            }
            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[zScreenStart], polyFt3);
#else
            switch (sharedData_800DD591_0_s00)
            {
                case 2:
                    if ((zScreenStart + 256) < 0x7FF)
                    {
                        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[zScreenStart + 256], polyFt3);
                    }
                    break;

                default:
                    addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[zScreenStart], polyFt3);
                    break;
            }
#endif
            GsOUT_PACKET_P = (PACKET*)&polyFt3[1];
        }
    }
}
