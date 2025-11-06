#include "inline_no_dmpsx.h"

void sharedFunc_800CEB24_0_s00(s_Particle* part)
{
    VECTOR3     particlePos;
    SVECTOR3    particlePosQ8;
    s32         zScreenStart;
    s_Particle* localPart;

    u8        primColorG;
    u8        primColorB;
    u8        primColorR;
    POLY_FT3* polyFt3;

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
        if (sharedData_800DD591_0_s00 != 0)
        {
            particlePos = part->position0_0;
            sharedFunc_800D0700_0_s00(&particlePos, &sharedData_800E5768_1_s02, &sharedData_800E5768_1_s02.corners_0[1], 0);
            if (g_SavegamePtr->mapRoomIdx_A5 == 5)
            {
                sharedFunc_800D0700_0_s00(&particlePos, (s_func_800CB560*)&sharedData_800E5768_1_s02.corners_0[2], &sharedData_800E5768_1_s02.corners_0[3], 0);
            }
            particlePosQ8.vx = Q12_TO_Q8(particlePos.vx);
            particlePosQ8.vy = Q12_TO_Q8(localPart->position0_0.vy);
            particlePosQ8.vz = Q12_TO_Q8(particlePos.vz);
        }
        else
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

            GsOUT_PACKET_P = (PACKET*)&polyFt3[1];
        }
    }
}
