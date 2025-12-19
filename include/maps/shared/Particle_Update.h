#include "inline_no_dmpsx.h"

bool Particle_Update(s_Particle* partHead)
{
    #define SNOW_REST_TICKS_UPDATE_MAX 32

#if defined(MAP0_S00) || \
    defined(MAP1_S02) || defined(MAP1_S03) || \
    defined(MAP4_S02) || defined(MAP4_S03) || defined(MAP4_S04) || defined(MAP4_S05) || \
    defined(MAP5_S00) || \
    defined(MAP6_S00) || defined(MAP6_S03)    
    s32 sp64;
#endif
    MATRIX      mat0;
    MATRIX      mat1;
    VECTOR3     prevPos;
    s16         rand;
    s32         pass;
    s32         density;
    s32         updateCount;
    s32         updatePrev;
    s_Particle* curPart;

    density = 0;

#if defined(MAP0_S00) || \
    defined(MAP1_S02) || defined(MAP1_S03) || \
    defined(MAP4_S02) || defined(MAP4_S03) || defined(MAP4_S04) || defined(MAP4_S05) || \
    defined(MAP5_S00) || \
    defined(MAP6_S00) || defined(MAP6_S03)
    if (sharedData_800E32D0_0_s00 < 27000)
    {
        sp64 = 3;
    }
    else
    {
        if (sharedData_800E32D0_0_s00 < 135000)
        {
            sp64 = 4;
        }
        else
        {
            sp64 = 5;
        }
    }
#endif
    
    GsInitCoordinate2(0, &g_SysWork.coord_22A8);

    g_Particle_Position.vx = g_ParticleVectors0.viewPosition_C.vx + FP_MULTIPLY(Math_Sin(g_ParticleVectors0.viewRotation_20.vy), Q12(3.0), Q12_SHIFT);
    g_Particle_Position.vz = g_ParticleVectors0.viewPosition_C.vz + FP_MULTIPLY(Math_Cos(g_ParticleVectors0.viewRotation_20.vy), Q12(3.0), Q12_SHIFT);
#if defined(MAP1_S06)
    g_Particle_Position.vy = Q12(-10.0);
#else
    g_Particle_Position.vy = Q12(-6.0);
#endif

    curPart = partHead;

    prevPos = g_Particle_Position;
    if (g_Particle_PrevPosition.vx == Q12(0.0f) && g_Particle_PrevPosition.vz == Q12(0.0f))
    {
        g_Particle_PrevPosition.vx = prevPos.vx;
        g_Particle_PrevPosition.vz = prevPos.vz;
    }

    sharedData_800DF158_1_s02 = sharedFunc_800CBBBC_0_s00();

    g_SysWork.coord_22A8.coord.t[1] = Q8(0.0f);
    g_SysWork.coord_22A8.coord.t[0] = Q12_TO_Q8(g_Particle_Position.vx);
    g_SysWork.coord_22A8.coord.t[2] = Q12_TO_Q8(g_Particle_Position.vz);
    
    g_SysWork.coord_22A8.flg = false;
    func_80049B6C(&g_SysWork.coord_22A8, &mat1, &mat0);
    gte_SetRotMatrix(&mat0);
    gte_SetTransMatrix(&mat0);

    // Get starting random value to use later.
    rand = Rng_Rand16();
    updatePrev = 0;

    // Update wind speed.
    if (sharedData_800E0CAC_0_s00 >= 2)
    {
        // Wind is active.
        // Ramp up the speed to 200, then add some randomness once fast enough.

        // Modulate X-axis speed.
        if (g_Particle_SpeedX < 200)
        {
            g_Particle_SpeedX++;
        }
        else
        {
            g_Particle_SpeedX += Rng_GenerateInt(-8, 8);
            limitRange(g_Particle_SpeedX, 200, 800);
        }

        // Modulate Z-axis speed.
        if (g_Particle_SpeedZ < 200)
        {
            g_Particle_SpeedZ++;
        }
        else
        {
            g_Particle_SpeedZ += Rng_GenerateInt(-8, 8);
            limitRange(g_Particle_SpeedZ, 20, 800); // Might be a dev mistake? Makes more sense to be 200 like above.
        }
    }
    // Wind is disabled, ramp speed down to 0.
    else
    {
        // X.
        if (g_Particle_SpeedX != 0)
        {
            g_Particle_SpeedX--;
        }

        // Z.
        if (g_Particle_SpeedZ != 0)
        {
            g_Particle_SpeedZ--;
        }
    }

    ////////////////////////////////////////////////////////////////////////////

    // Reset how many particles to spawn this tick.
    sharedData_800E2156_0_s01 = 0;

#if defined(MAP0_S00)
    if (g_SavegamePtr->mapRoomIdx_A5 == 3 && g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(200.0f))
    {
        sharedData_800DD591_0_s00 = 1;
    }
    else
    {
        sharedData_800DD591_0_s00 = 0;
    }

#elif defined(MAP0_S02)
    sharedData_800DD591_0_s00 = 2;

    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 2:
            sharedData_800E326C_0_s00.corners_0[0].vx = Q12(-101.5f);
            sharedData_800E326C_0_s00.corners_0[0].vz = Q12(23.8f);
            sharedData_800E326C_0_s00.corners_0[1].vx = Q12(-101.5f);
            sharedData_800E326C_0_s00.corners_0[1].vz = Q12(17.0f);
            sharedData_800E326C_0_s00.corners_0[2].vx = Q12(-98.5f);
            sharedData_800E326C_0_s00.corners_0[2].vz = Q12(17.0f);
            sharedData_800E326C_0_s00.corners_0[3].vx = Q12(-98.5f);
            sharedData_800E326C_0_s00.corners_0[3].vz = Q12(23.8f);
            sharedData_800E326C_0_s00.corners_0[4].vx = Q12(-98.5f);
            sharedData_800E326C_0_s00.corners_0[4].vz = Q12(23.8f);
            sharedData_800E326C_0_s00.corners_0[5].vx = Q12(-101.5f);
            sharedData_800E326C_0_s00.corners_0[5].vz = Q12(23.8f);
            sharedData_800E326C_0_s00.corners_0[6].vx = Q12(-101.5f);
            sharedData_800E326C_0_s00.corners_0[6].vz = Q12(17.0f);
            sharedData_800E326C_0_s00.corners_0[7].vx = Q12(-98.5f);
            sharedData_800E326C_0_s00.corners_0[7].vz = Q12(17.0f);
            break;

        case 3:
            sharedData_800E326C_0_s00.corners_0[0].vx = Q12(-145.0f);
            sharedData_800E326C_0_s00.corners_0[0].vz = Q12(15.5f);
            sharedData_800E326C_0_s00.corners_0[1].vx = Q12(-135.0f);
            sharedData_800E326C_0_s00.corners_0[1].vz = Q12(15.5f);
            break;

        case 4:
            sharedData_800E326C_0_s00.corners_0[0].vx = Q12(-184.0f);
            sharedData_800E326C_0_s00.corners_0[0].vz = Q12(23.0f);
            sharedData_800E326C_0_s00.corners_0[1].vx = Q12(-184.0f);
            sharedData_800E326C_0_s00.corners_0[1].vz = Q12(16.0f);
            break;
    }

#elif defined(MAP1_S06)
    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 9:
        case 12:
        case 13:
        case 14:
            break;

        default:
            return false;
    }

#elif defined(MAP2_S00)
    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 3:
            if (g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(200.0f))
            {
                sharedData_800DD591_0_s00 = 1;
                sharedData_800E326C_0_s00.corners_0[0].vx = Q12(-5.0f);
                sharedData_800E326C_0_s00.corners_0[0].vy = Q12(-4.5f);
                sharedData_800E326C_0_s00.corners_0[0].vz = Q12(211.0f);
                sharedData_800E326C_0_s00.corners_0[1].vx = Q12(15.0f);
                sharedData_800E326C_0_s00.corners_0[1].vy = Q12(-4.5f);
                sharedData_800E326C_0_s00.corners_0[1].vz = Q12(211.0f);
            }
            else
            {
                sharedData_800DD591_0_s00 = 0;
            }
            break;

        case 7:
            if (g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(-55.0f) && g_SysWork.playerWork_4C.player_0.position_18.vx < Q12(-33.0f) && 
                g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(-14.0f) && g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(0.0f))
            {
                    sharedData_800DD591_0_s00 = 10;
                    sharedData_800E326C_0_s00.corners_0[0].vx = Q12(-44.5f);
                    sharedData_800E326C_0_s00.corners_0[0].vz = Q12(-11.2f);
                    sharedData_800E326C_0_s00.corners_0[1].vx = Q12(-44.5f);
                    sharedData_800E326C_0_s00.corners_0[1].vz = Q12(-13.0f);
                    sharedData_800E326C_0_s00.corners_0[2].vx = Q12(-43.0f);
                    sharedData_800E326C_0_s00.corners_0[2].vz = Q12(-13.0f);
                    sharedData_800E326C_0_s00.corners_0[3].vx = Q12(-43.0f);
                    sharedData_800E326C_0_s00.corners_0[3].vz = Q12(-11.2f);
                    sharedData_800E326C_0_s00.corners_0[4].vx = Q12(-43.0f);
                    sharedData_800E326C_0_s00.corners_0[4].vz = Q12(-11.2f);
                    sharedData_800E326C_0_s00.corners_0[5].vx = Q12(-44.5f);
                    sharedData_800E326C_0_s00.corners_0[5].vz = Q12(-11.2f);
            }
            else if (g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(-90.0f) && g_SysWork.playerWork_4C.player_0.position_18.vx < Q12(-56.0f) && 
                     g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(-14.0f) && g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(0.0f))
            {
                    sharedData_800DD591_0_s00 = 10;
                    sharedData_800E326C_0_s00.corners_0[0].vx = Q12(-79.0f);
                    sharedData_800E326C_0_s00.corners_0[0].vz = Q12(-10.5f);
                    sharedData_800E326C_0_s00.corners_0[1].vx = Q12(-79.0f);
                    sharedData_800E326C_0_s00.corners_0[1].vz = Q12(-13.0f);
                    sharedData_800E326C_0_s00.corners_0[2].vx = Q12(-66.5f);
                    sharedData_800E326C_0_s00.corners_0[2].vz = Q12(-13.0f);
                    sharedData_800E326C_0_s00.corners_0[3].vx = Q12(-66.5f);
                    sharedData_800E326C_0_s00.corners_0[3].vz = Q12(-10.5f);
                    sharedData_800E326C_0_s00.corners_0[4].vx = Q12(-66.5f);
                    sharedData_800E326C_0_s00.corners_0[4].vz = Q12(-10.5f);
                    sharedData_800E326C_0_s00.corners_0[5].vx = Q12(-79.0f);
                    sharedData_800E326C_0_s00.corners_0[5].vz = Q12(-10.5f);
            }
            else
            {
                sharedData_800DD591_0_s00 = 0;
            }
            break;

        case 1:
            if (g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(-240.0f) && g_SysWork.playerWork_4C.player_0.position_18.vx < Q12(-226.0f) && 
                g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(136.0f))
            {
                sharedData_800DD591_0_s00 = 10;
                sharedData_800E326C_0_s00.corners_0[0].vx = Q12(-232.0f);
                sharedData_800E326C_0_s00.corners_0[0].vz = Q12(151.0f);
                sharedData_800E326C_0_s00.corners_0[1].vx = Q12(-229.0f);
                sharedData_800E326C_0_s00.corners_0[1].vz = Q12(151.0f);
                sharedData_800E326C_0_s00.corners_0[2].vx = Q12(-232.0f);
                sharedData_800E326C_0_s00.corners_0[2].vz = Q12(158.0f);
                sharedData_800E326C_0_s00.corners_0[3].vx = Q12(-232.0f);
                sharedData_800E326C_0_s00.corners_0[3].vz = Q12(151.0f);
                sharedData_800E326C_0_s00.corners_0[4].vx = Q12(-228.0f);
                sharedData_800E326C_0_s00.corners_0[4].vz = Q12(151.0f);
                sharedData_800E326C_0_s00.corners_0[5].vx = Q12(-228.0f);
                sharedData_800E326C_0_s00.corners_0[5].vz = Q12(158.0f);
            }
            else if (g_SysWork.playerWork_4C.player_0.position_18.vx <= Q12(-240.0f) && g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(133.0f))
            {
                sharedData_800DD591_0_s00 = 9;
                sharedData_800E326C_0_s00.corners_0[0].vx = Q12(-251.0f);
                sharedData_800E326C_0_s00.corners_0[0].vz = Q12(142.0f);
                sharedData_800E326C_0_s00.corners_0[1].vx = Q12(-248.2f);
                sharedData_800E326C_0_s00.corners_0[1].vz = Q12(142.0f);
                sharedData_800E326C_0_s00.corners_0[2].vx = Q12(-248.2f);
                sharedData_800E326C_0_s00.corners_0[2].vz = Q12(142.0f);
                sharedData_800E326C_0_s00.corners_0[3].vx = Q12(-248.2f);
                sharedData_800E326C_0_s00.corners_0[3].vz = Q12(147.0f);
            }
            else
            {
                sharedData_800DD591_0_s00 = 0;
            }
            break;

        case 6:
            if (g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(-225.0f) && g_SysWork.playerWork_4C.player_0.position_18.vx < Q12(-195.0f) && 
                g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(-100.0f) && g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(-72.0f))
            {
                sharedData_800DD591_0_s00 = 10;
                sharedData_800E326C_0_s00.corners_0[0].vx = Q12(-208.0f);
                sharedData_800E326C_0_s00.corners_0[0].vz = Q12(-93.0f);
                sharedData_800E326C_0_s00.corners_0[1].vx = Q12(-208.0f);
                sharedData_800E326C_0_s00.corners_0[1].vz = Q12(-91.0f);
                sharedData_800E326C_0_s00.corners_0[2].vx = Q12(-212.0f);
                sharedData_800E326C_0_s00.corners_0[2].vz = Q12(-91.0f);
                sharedData_800E326C_0_s00.corners_0[3].vx = Q12(-212.0f);
                sharedData_800E326C_0_s00.corners_0[3].vz = Q12(-93.0f);
                sharedData_800E326C_0_s00.corners_0[4].vx = Q12(-208.0f);
                sharedData_800E326C_0_s00.corners_0[4].vz = Q12(-91.0f);
                sharedData_800E326C_0_s00.corners_0[5].vx = Q12(-212.0f);
                sharedData_800E326C_0_s00.corners_0[5].vz = Q12(-91.0f);
            }
            else
            {
                sharedData_800DD591_0_s00 = 0;
            }
            break;

        case 27:
            if (g_SysWork.playerWork_4C.player_0.position_18.vx < Q12(-275.0f) && g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(-175.0f))
            {
                sharedData_800DD591_0_s00 = 0xA;
                sharedData_800E326C_0_s00.corners_0[0].vx = Q12(-287.0f);
                sharedData_800E326C_0_s00.corners_0[0].vz = Q12(-182.5f);
                sharedData_800E326C_0_s00.corners_0[1].vx = Q12(-285.5f);
                sharedData_800E326C_0_s00.corners_0[1].vz = Q12(-182.5f);
                sharedData_800E326C_0_s00.corners_0[2].vx = Q12(-285.5f);
                sharedData_800E326C_0_s00.corners_0[2].vz = Q12(-177.5f);
                sharedData_800E326C_0_s00.corners_0[3].vx = Q12(-287.0f);
                sharedData_800E326C_0_s00.corners_0[3].vz = Q12(-177.5f);
                sharedData_800E326C_0_s00.corners_0[4].vx = Q12(-285.5f);
                sharedData_800E326C_0_s00.corners_0[4].vz = Q12(-181.5f);
                sharedData_800E326C_0_s00.corners_0[5].vx = Q12(-285.5f);
                sharedData_800E326C_0_s00.corners_0[5].vz = Q12(-178.4f);
            }
            else
            {
                sharedData_800DD591_0_s00 = 0;
            }
            break;
    }

#elif defined(MAP2_S02)
    if (g_SavegamePtr->mapRoomIdx_A5 == 17)
    {
        return false;
    }

    sharedData_800DD591_0_s00 = 0;

#elif defined(MAP3_S00)
    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 3:
        case 5:
        case 8:
        case 9:
        case 11:
            break;

        default:
            return false;
    }

#elif defined(MAP3_S01)
    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 3:
        case 5:
        case 8:
        case 9:
        case 11:
            break;

        default:
            return false;
    }

#elif defined(MAP3_S06)
    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 3:
        case 5:
        case 8:
        case 9:
        case 11:
            break;

        default:
            return false;
    }

#elif defined(MAP4_S02)
    if (g_SavegamePtr->mapRoomIdx_A5 == 17)
    {
        return false;
    }

#elif defined(MAP4_S03)
    if (g_SavegamePtr->mapRoomIdx_A5 != 20)
    {
        return false;
    }

#elif defined(MAP5_S01)
    sharedData_800DD591_0_s00 = 1;

    if (g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(-33.0f) && g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(-20.0f) &&
        g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(13.0f) && g_SysWork.playerWork_4C.player_0.position_18.vx < Q12(44.0f))
    {
        sharedData_800E326C_0_s00.corners_0[0].vx = Q12(24.0f);
        sharedData_800E326C_0_s00.corners_0[0].vz = Q12(-19.0f);
        sharedData_800E326C_0_s00.corners_0[1].vx = Q12(24.0f);
        sharedData_800E326C_0_s00.corners_0[1].vz = Q12(-21.5f);
        sharedData_800E326C_0_s00.corners_0[2].vx = Q12(31.5f);
        sharedData_800E326C_0_s00.corners_0[2].vz = Q12(-21.5f);
        sharedData_800E326C_0_s00.corners_0[3].vx = Q12(31.5f);
        sharedData_800E326C_0_s00.corners_0[3].vz = Q12(-19.0f);
        sharedData_800E326C_0_s00.corners_0[4].vx = Q12(24.0f);
        sharedData_800E326C_0_s00.corners_0[4].vz = Q12(-21.5f);
        sharedData_800E326C_0_s00.corners_0[5].vx = Q12(31.5f);
        sharedData_800E326C_0_s00.corners_0[5].vz = Q12(-21.5f);
    }
    else if (g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(-82.0f) && g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(-56.0f) &&
             g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(43.0f) && g_SysWork.playerWork_4C.player_0.position_18.vx < Q12(70.0f))
    {
        sharedData_800E326C_0_s00.corners_0[0].vx = Q12(58.7f);
        sharedData_800E326C_0_s00.corners_0[0].vz = Q12(-70.5f);
        sharedData_800E326C_0_s00.corners_0[1].vx = Q12(58.7f);
        sharedData_800E326C_0_s00.corners_0[1].vz = Q12(-68.0f);
        sharedData_800E326C_0_s00.corners_0[2].vx = Q12(54.5f);
        sharedData_800E326C_0_s00.corners_0[2].vz = Q12(-68.0f);
        sharedData_800E326C_0_s00.corners_0[3].vx = Q12(54.5f);
        sharedData_800E326C_0_s00.corners_0[3].vz = Q12(-70.5f);
        sharedData_800E326C_0_s00.corners_0[4].vx = Q12(54.5f);
        sharedData_800E326C_0_s00.corners_0[4].vz = Q12(-70.5f);
        sharedData_800E326C_0_s00.corners_0[5].vx = Q12(58.7f);
        sharedData_800E326C_0_s00.corners_0[5].vz = Q12(-70.5f);
    }
    else
    {
        sharedData_800DD591_0_s00 = 0;
    }

#elif defined(MAP5_S03)
    sharedData_800DD591_0_s00 = 2;

    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 7:
            sharedData_800E326C_0_s00.corners_0[0].vx = Q12(55.5f);
            sharedData_800E326C_0_s00.corners_0[0].vz = Q12(63.0f);
            sharedData_800E326C_0_s00.corners_0[1].vx = Q12(55.5f);
            sharedData_800E326C_0_s00.corners_0[1].vz = Q12(58.0f);
            break;

        case 8:
            sharedData_800E326C_0_s00.corners_0[0].vx = Q12(100.0f);
            sharedData_800E326C_0_s00.corners_0[0].vz = Q12(56.5f);
            sharedData_800E326C_0_s00.corners_0[1].vx = Q12(104.0f);
            sharedData_800E326C_0_s00.corners_0[1].vz = Q12(56.5f);
            break;

        default:
            return false;
    }
#endif

    for (pass = 0; pass < 2; pass++)
    {
        // Set particle density.
        switch (pass)
        {
            case 0:
            #if defined(MAP0_S00) || defined(MAP0_S01) || defined(MAP0_S02) || \
                defined(MAP1_S00) || defined(MAP1_S06) || \
                defined(MAP2_S00) || defined(MAP2_S02) || \
                defined(MAP3_S00) || defined(MAP3_S01) || defined(MAP3_S06) || \
                defined(MAP5_S01) || defined(MAP5_S03) || \
                defined(MAP6_S00) || \
                defined(MAP7_S03)
                density = (g_SysWork.field_2349 == 1) ? 1 : 3;
            #endif
                break;

            default:
            #if defined(MAP0_S00) || \
                defined(MAP1_S02) || defined(MAP1_S03) || \
                defined(MAP4_S02) || defined(MAP4_S03) || defined(MAP4_S04) || defined(MAP4_S05) || \
                defined(MAP6_S00)
                density = 10;
            #elif defined(MAP5_S00) || \
                  defined(MAP6_S03)
                density = 1;
            #endif
                break;
        }
        
        // Handle particles in this state.
        for (updateCount = updatePrev;
             updateCount < (updatePrev + sharedData_800DD588_0_s00[pass]);
             updateCount++, curPart++)
        {
            // Keep only the lower 4 bits.
            // NOTE: &= 0xF would be faster, but this is what they've done.
            curPart->type_1F %= 0xF0;

            switch (pass)
            {
                case 0:
                #if defined(MAP0_S00) || defined(MAP0_S01) || defined(MAP0_S02) || \
                    defined(MAP1_S00) || defined(MAP1_S06) || \
                    defined(MAP2_S00) || defined(MAP2_S02) || \
                    defined(MAP3_S00) || defined(MAP3_S01) || defined(MAP3_S06) || \
                    defined(MAP5_S01) || defined(MAP5_S03) || \
                    defined(MAP6_S00) || \
                    defined(MAP7_S03)
                    if (curPart->type_1F >= 2)
                    {
                        curPart->stateStep_1E = 0u;
                        curPart->type_1F = 0u;
                    }
                #endif
                    break;

                case 1:
                #if defined(MAP0_S00) || \
                    defined(MAP1_S02) || defined(MAP1_S03) || \
                    defined(MAP4_S02) || defined(MAP4_S03) || defined(MAP4_S04) || defined(MAP4_S05) || \
                    defined(MAP5_S00) || \
                    defined(MAP6_S00) || defined(MAP6_S03)
                    if (curPart->type_1F < 2 || curPart->type_1F > 3)
                    {
                        curPart->stateStep_1E = 0u;
                        curPart->type_1F = 2u;
                    }
                #endif
                    break;
            }

        #if defined(MAP7_S03)
            D_800F23D0 = (g_DeltaTime0 * 10936) / Q12(1.0f);
        #endif

            if (sharedData_800DD584_0_s00 != 0)
            {
                // NOTE: This function only has a body in `MAP07_S03` and everything else calls an empty function.
                sharedFunc_800CE954_7_s03(pass, curPart, &rand, &g_DeltaTime0);
            }
            else
            {
                switch (curPart->stateStep_1E)
                {
                    case ParticleState_Spawn:
                        if (sharedData_800E2156_0_s01 < density)
                        {
                            sharedData_800E2156_0_s01++;
                            sharedFunc_800CF9A8_0_s01(pass, curPart, &rand);
                        }
                        break;

                    case ParticleState_Active:
                        sharedFunc_800CEFD0_1_s02(pass, curPart, &rand, &g_DeltaTime0);
                        break;

                    default: // `ParticleState_Rest`
                        curPart->stateStep_1E++;
                        if (curPart->stateStep_1E < SNOW_REST_TICKS_UPDATE_MAX)
                        {
                            // TODO: This should pass `s_Particle*` but the matcher is struggling with that atm.
                            sharedFunc_800CFFF8_0_s00(pass, (s_func_800CFFF8*)curPart, &rand);
                        }
                        #if defined(MAP1_S03) || \
                            defined(MAP4_S02) || defined(MAP4_S04) || defined(MAP4_S05) || \
                            defined(MAP5_S00) || \
                            defined(MAP6_S00) || defined(MAP6_S03)
                        else
                        {
                            sharedFunc_800D0690_1_s03(pass, curPart, &rand, &g_DeltaTime0);
                        }
                        #endif
                        break;
                }
            }
        }
        updatePrev += sharedData_800DD588_0_s00[pass];
    }

    ////////////////////////////////////////////////////////////////////////////

    curPart = partHead;
    updatePrev = 0;
    for (pass = 0; pass < 2; pass++)
    {
    #if defined(MAP0_S00) || \
        defined(MAP1_S02) || defined(MAP1_S03) || \
        defined(MAP4_S02) || defined(MAP4_S03) || defined(MAP4_S04) || defined(MAP4_S05) || \
        defined(MAP5_S00) || \
        defined(MAP6_S00) || defined(MAP6_S03)
        if (pass != 0)
        {
            sharedData_800E32D0_0_s00 += sharedData_800DD588_0_s00[pass];
            limitRange(sharedData_800E32D0_0_s00, 0, 135000);
        }
    #endif
        for (updateCount = updatePrev;
             updateCount < (updatePrev + sharedData_800DD588_0_s00[pass]);
             updateCount++, curPart++)
        {
            switch (pass)
            {
                default:
                #if defined(MAP0_S00) || \
                    defined(MAP1_S02) || defined(MAP1_S03) || \
                    defined(MAP4_S02) || defined(MAP4_S03) || defined(MAP4_S04) || defined(MAP4_S05) || \
                    defined(MAP5_S00) || \
                    defined(MAP6_S00) || defined(MAP6_S03)
                    sharedFunc_800CEFF4_0_s00(curPart, sp64);
                #endif
                    break;

                case 0:
                #if defined(MAP0_S00) || defined(MAP0_S01) || defined(MAP0_S02) || \
                    defined(MAP1_S00) || defined(MAP1_S06) || \
                    defined(MAP2_S00) || defined(MAP2_S02) || \
                    defined(MAP3_S00) || defined(MAP3_S01) || defined(MAP3_S06) || \
                    defined(MAP5_S01) || defined(MAP5_S03) || \
                    defined(MAP6_S00) || \
                    defined(MAP7_S03)
                    sharedFunc_800CEB24_0_s00(curPart);
                #endif
                    break;
            }
        }

        updatePrev += sharedData_800DD588_0_s00[pass];
    }

    ////////////////////////////////////////////////////////////////////////////

    // Likely previous position for next particle system update.
    // Stores XZ position and Y rotation.
    g_Particle_PrevPosition.vx = prevPos.vx;
    g_Particle_PrevPosition.vz = prevPos.vz;
    g_Particle_PrevRotationY   = g_Particle_RotationY;
    return false;
}
