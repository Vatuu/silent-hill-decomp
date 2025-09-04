#include "inline_no_dmpsx.h"

bool Particle_Update(s_Particle* partHead)
{
    #define SNOW_REST_TICKS_UPDATE_MAX 32

    MATRIX      mat0;
    MATRIX      mat1;
    VECTOR3     prevPos;
    s16         rand;
    s32         pass;
    s_Particle* partIter;

    
#if defined(MAP0_S00) || \
    defined(MAP1_S02) || defined(MAP1_S03) || \
    defined(MAP4_S02) || defined(MAP4_S03) || defined(MAP4_S04) || defined(MAP4_S05) || \
    defined(MAP5_S00) || \
    defined(MAP6_S00) || defined(MAP6_S03)    
    s32 sp64;
#endif

    s32 density;
    s32 updateCount;
    s32 updatePrev;

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

    sharedData_800E323C_0_s00.vx = g_ParticleVectors0.viewPosition_C.vx + FP_FROM(Math_Sin(g_ParticleVectors0.viewRotation_20.vy) * FP_METER(3.0), Q12_SHIFT);
    sharedData_800E323C_0_s00.vz = g_ParticleVectors0.viewPosition_C.vz + FP_FROM(Math_Cos(g_ParticleVectors0.viewRotation_20.vy) * FP_METER(3.0), Q12_SHIFT);
#if defined(MAP1_S06)
    sharedData_800E323C_0_s00.vy = FP_METER(-10.0);
#else
    sharedData_800E323C_0_s00.vy = FP_METER(-6.0);
#endif

    partIter = partHead;

    prevPos = sharedData_800E323C_0_s00;
    if (sharedData_800E324C_0_s00.vx == FP_METER(0.0f) && sharedData_800E324C_0_s00.vz == FP_METER(0.0f))
    {
        sharedData_800E324C_0_s00.vx = prevPos.vx;
        sharedData_800E324C_0_s00.vz = prevPos.vz;
    }

    sharedData_800DF158_1_s02 = sharedFunc_800CBBBC_0_s00();

    g_SysWork.coord_22A8.coord.t[1] = FP_METER_GEO(0.0f);
    g_SysWork.coord_22A8.coord.t[0] = FP_METER_TO_GEO(sharedData_800E323C_0_s00.vx);
    g_SysWork.coord_22A8.coord.t[2] = FP_METER_TO_GEO(sharedData_800E323C_0_s00.vz);
    
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

        // X.
        if (sharedData_800DFB64_0_s00 < 200)
        {
            sharedData_800DFB64_0_s00++;
        }
        else
        {
            sharedData_800DFB64_0_s00 += Rng_GenerateInt(Rng_Rand16(), -8, 8);
            limitRange(sharedData_800DFB64_0_s00, 200, 800);
        }

        // Z.
        if (sharedData_800DFB68_0_s00 < 200)
        {
            sharedData_800DFB68_0_s00++;
        }
        else
        {
            sharedData_800DFB68_0_s00 += Rng_GenerateInt(Rng_Rand16(), -8, 8);
            limitRange(sharedData_800DFB68_0_s00, 20, 800); // Might be a dev mistake? Makes more sense to be 200 like above.
        }
    }
    // Wind is disabled, ramp speed down to 0.
    else
    {
        // X.
        if (sharedData_800DFB64_0_s00 != 0)
        {
            sharedData_800DFB64_0_s00--;
        }

        // Z.
        if (sharedData_800DFB68_0_s00 != 0)
        {
            sharedData_800DFB68_0_s00--;
        }
    }

    ////////////////////////////////////////////////////////////////////////////

    // Reset how many particles to spawn this tick.
    sharedData_800E2156_0_s01 = 0;

#if defined(MAP0_S00)
    if (g_SavegamePtr->mapRoomIdx_A5 == 3 && g_SysWork.player_4C.chara_0.position_18.vz > FP_METER(200.0f))
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
            sharedData_800E5768_1_s02.field_0 = 0xFFF9A800;
            sharedData_800E5768_1_s02.field_8 = 0x17CCC;
            sharedData_800E5768_1_s02.field_C = 0xFFF9A800;
            sharedData_800E5768_1_s02.field_14 = 0x11000;
            sharedData_800E5768_1_s02.field_18 = 0xFFF9D800;
            sharedData_800E5768_1_s02.field_20 = 0x11000;
            sharedData_800E5768_1_s02.field_24 = 0xFFF9D800;
            sharedData_800E5768_1_s02.field_2C = 0x17CCC;
            sharedData_800E5768_1_s02.field_30 = 0xFFF9D800;
            sharedData_800E5768_1_s02.field_38 = 0x17CCC;
            sharedData_800E5768_1_s02.field_3C = 0xFFF9A800;
            sharedData_800E5768_1_s02.field_44 = 0x17CCC;
            sharedData_800E5768_1_s02.field_48 = 0xFFF9A800;
            sharedData_800E5768_1_s02.field_50 = 0x11000;
            sharedData_800E5768_1_s02.field_54 = 0xFFF9D800;
            sharedData_800E5768_1_s02.field_5C = 0x11000;
        break;
        
        case 3:
            sharedData_800E5768_1_s02.field_0 = 0xFFF6F000;
            sharedData_800E5768_1_s02.field_8 = 0xF800;
            sharedData_800E5768_1_s02.field_C = 0xFFF79000;
            sharedData_800E5768_1_s02.field_14 = 0xF800;
        break;
        
        case 4:
            sharedData_800E5768_1_s02.field_0 = 0xFFF48000;
            sharedData_800E5768_1_s02.field_8 = 0x17000;
            sharedData_800E5768_1_s02.field_C = 0xFFF48000;
            sharedData_800E5768_1_s02.field_14 = 0x10000;
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
            if (g_SysWork.player_4C.chara_0.position_18.vz > FP_METER(200.0f))
            {
                sharedData_800DD591_0_s00 = 1;
                sharedData_800E5768_1_s02.field_0 = -0x5000;
                sharedData_800E5768_1_s02.field_4 = -0x4800;
                sharedData_800E5768_1_s02.field_8 = 0xD3000;
                sharedData_800E5768_1_s02.field_C = 0xF000;
                sharedData_800E5768_1_s02.field_10 = -0x4800;
                sharedData_800E5768_1_s02.field_14 = 0xD3000;
            }
            else
            {
                sharedData_800DD591_0_s00 = 0;
            }
            break;

        case 7:
            if (g_SysWork.player_4C.chara_0.position_18.vx > FP_METER(-55.0f) && g_SysWork.player_4C.chara_0.position_18.vx < FP_METER(-33.0f) && 
                g_SysWork.player_4C.chara_0.position_18.vz > FP_METER(-14.0f) && g_SysWork.player_4C.chara_0.position_18.vz < FP_METER(0.0f))
                {
                    sharedData_800DD591_0_s00 = 10;
                    sharedData_800E5768_1_s02.field_0 = 0xFFFD3800;
                    sharedData_800E5768_1_s02.field_8 = 0xFFFF4CCD;
                    sharedData_800E5768_1_s02.field_C = 0xFFFD3800;
                    sharedData_800E5768_1_s02.field_14 = 0xFFFF3000;
                    sharedData_800E5768_1_s02.field_18 = 0xFFFD5000;
                    sharedData_800E5768_1_s02.field_20 = 0xFFFF3000;
                    sharedData_800E5768_1_s02.field_24 = 0xFFFD5000;
                    sharedData_800E5768_1_s02.field_2C = 0xFFFF4CCD;
                    sharedData_800E5768_1_s02.field_30 = 0xFFFD5000;
                    sharedData_800E5768_1_s02.field_38 = 0xFFFF4CCD;
                    sharedData_800E5768_1_s02.field_3C = 0xFFFD3800;
                    sharedData_800E5768_1_s02.field_44 = 0xFFFF4CCD;
            }
            else if (g_SysWork.player_4C.chara_0.position_18.vx > FP_METER(-90.0f) && g_SysWork.player_4C.chara_0.position_18.vx < FP_METER(-56.0f) && 
                     g_SysWork.player_4C.chara_0.position_18.vz > FP_METER(-14.0f) && g_SysWork.player_4C.chara_0.position_18.vz < FP_METER(0.0f))
                {
                    sharedData_800DD591_0_s00 = 10;
                    sharedData_800E5768_1_s02.field_0 = 0xFFFB1000;
                    sharedData_800E5768_1_s02.field_8 = 0xFFFF5800;
                    sharedData_800E5768_1_s02.field_C = 0xFFFB1000;
                    sharedData_800E5768_1_s02.field_14 = 0xFFFF3000;
                    sharedData_800E5768_1_s02.field_18 = 0xFFFBD800;
                    sharedData_800E5768_1_s02.field_20 = 0xFFFF3000;
                    sharedData_800E5768_1_s02.field_24 = 0xFFFBD800;
                    sharedData_800E5768_1_s02.field_2C = 0xFFFF5800;
                    sharedData_800E5768_1_s02.field_30 = 0xFFFBD800;
                    sharedData_800E5768_1_s02.field_38 = 0xFFFF5800;
                    sharedData_800E5768_1_s02.field_3C = 0xFFFB1000;
                    sharedData_800E5768_1_s02.field_44 = 0xFFFF5800;
            }
            else
            {
                sharedData_800DD591_0_s00 = 0;
            }
            break;

        case 1:
            if (g_SysWork.player_4C.chara_0.position_18.vx > FP_METER(-240.0f) && g_SysWork.player_4C.chara_0.position_18.vx < FP_METER(-226.0f) && 
                g_SysWork.player_4C.chara_0.position_18.vz > FP_METER(136.0f))
            {
                sharedData_800DD591_0_s00 = 10;
                sharedData_800E5768_1_s02.field_0 = 0xFFF18000;
                sharedData_800E5768_1_s02.field_8 = 0x97000;
                sharedData_800E5768_1_s02.field_C = 0xFFF1B000;
                sharedData_800E5768_1_s02.field_14 = 0x97000;
                sharedData_800E5768_1_s02.field_18 = 0xFFF18000;
                sharedData_800E5768_1_s02.field_20 = 0x9E000;
                sharedData_800E5768_1_s02.field_24 = 0xFFF18000;
                sharedData_800E5768_1_s02.field_2C = 0x97000;
                sharedData_800E5768_1_s02.field_30 = 0xFFF1C000;
                sharedData_800E5768_1_s02.field_38 = 0x97000;
                sharedData_800E5768_1_s02.field_3C = 0xFFF1C000;
                sharedData_800E5768_1_s02.field_44 = 0x9E000;
            }
            else if (g_SysWork.player_4C.chara_0.position_18.vx <= FP_METER(-240.0f) && g_SysWork.player_4C.chara_0.position_18.vz > FP_METER(133.0f))
            {
                sharedData_800DD591_0_s00 = 9;
                sharedData_800E5768_1_s02.field_0 = 0xFFF05000;
                sharedData_800E5768_1_s02.field_8 = 0x8E000;
                sharedData_800E5768_1_s02.field_C = 0xFFF07CCD;
                sharedData_800E5768_1_s02.field_14 = 0x8E000;
                sharedData_800E5768_1_s02.field_18 = 0xFFF07CCD;
                sharedData_800E5768_1_s02.field_20 = 0x8E000;
                sharedData_800E5768_1_s02.field_24 = 0xFFF07CCD;
                sharedData_800E5768_1_s02.field_2C = 0x93000;
            }
            else
            {
                sharedData_800DD591_0_s00 = 0;
            }
            
        case 6:
            if (g_SysWork.player_4C.chara_0.position_18.vx > FP_METER(-225.0f) && g_SysWork.player_4C.chara_0.position_18.vx < FP_METER(-195.0f) && 
                g_SysWork.player_4C.chara_0.position_18.vz > FP_METER(-100.0f) && g_SysWork.player_4C.chara_0.position_18.vz < FP_METER(-72.0f))
            {
                sharedData_800DD591_0_s00 = 10;
                sharedData_800E5768_1_s02.field_0 = -851968;
                sharedData_800E5768_1_s02.field_8 = -380928;
                sharedData_800E5768_1_s02.field_C = -851968;
                sharedData_800E5768_1_s02.field_14 = -372736;
                sharedData_800E5768_1_s02.field_18 = -868352;
                sharedData_800E5768_1_s02.field_20 = -372736;
                sharedData_800E5768_1_s02.field_24 = -868352;
                sharedData_800E5768_1_s02.field_2C = -380928;
                sharedData_800E5768_1_s02.field_30 = -851968;
                sharedData_800E5768_1_s02.field_38 = -372736;
                sharedData_800E5768_1_s02.field_3C = -868352;
                sharedData_800E5768_1_s02.field_44 = -372736;
            }
            else
            {
                sharedData_800DD591_0_s00 = 0;
            }
            break;

        case 27:
            if (g_SysWork.player_4C.chara_0.position_18.vx < FP_METER(-275.0f) && g_SysWork.player_4C.chara_0.position_18.vz < FP_METER(-175.0f))
            {
                sharedData_800DD591_0_s00 = 10;
                sharedData_800E5768_1_s02.field_0 = -1175552;
                sharedData_800E5768_1_s02.field_8 = -747520;
                sharedData_800E5768_1_s02.field_C = -1169408;
                sharedData_800E5768_1_s02.field_14 = -747520;
                sharedData_800E5768_1_s02.field_18 = -1169408;
                sharedData_800E5768_1_s02.field_20 = -727040;
                sharedData_800E5768_1_s02.field_24 = -1175552;
                sharedData_800E5768_1_s02.field_2C = -727040;
                sharedData_800E5768_1_s02.field_30 = -1169408;
                sharedData_800E5768_1_s02.field_38 = -743424;
                sharedData_800E5768_1_s02.field_3C = -1169408;
                sharedData_800E5768_1_s02.field_44 = -730726;
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

    if (g_SysWork.player_4C.chara_0.position_18.vz > FP_METER(-33.0f) && g_SysWork.player_4C.chara_0.position_18.vz < FP_METER(-20.0f) &&
        g_SysWork.player_4C.chara_0.position_18.vx > FP_METER(13.0f) && g_SysWork.player_4C.chara_0.position_18.vx < FP_METER(44.0f))
    {
        sharedData_800E5768_1_s02.field_0 = 0x18000;
        sharedData_800E5768_1_s02.field_8 = 0xFFFED000;
        sharedData_800E5768_1_s02.field_C = 0x18000;
        sharedData_800E5768_1_s02.field_14 = 0xFFFEA800;
        sharedData_800E5768_1_s02.field_18 = 0x1F800;
        sharedData_800E5768_1_s02.field_20 = 0xFFFEA800;
        sharedData_800E5768_1_s02.field_24 = 0x1F800;
        sharedData_800E5768_1_s02.field_2C = 0xFFFED000;
        sharedData_800E5768_1_s02.field_30 = 0x18000;
        sharedData_800E5768_1_s02.field_38 = 0xFFFEA800;
        sharedData_800E5768_1_s02.field_3C = 0x1F800;
        sharedData_800E5768_1_s02.field_44 = 0xFFFEA800;
    }
    else if (g_SysWork.player_4C.chara_0.position_18.vz > FP_METER(-82.0f) && g_SysWork.player_4C.chara_0.position_18.vz < FP_METER(-56.0f) &&
             g_SysWork.player_4C.chara_0.position_18.vx > FP_METER(43.0f) && g_SysWork.player_4C.chara_0.position_18.vx < FP_METER(70.0f))
    {
        sharedData_800E5768_1_s02.field_0 = 0x3AB33;
        sharedData_800E5768_1_s02.field_8 = 0xFFFB9800;
        sharedData_800E5768_1_s02.field_C = 0x3AB33;
        sharedData_800E5768_1_s02.field_14 = 0xFFFBC000;
        sharedData_800E5768_1_s02.field_18 = 0x36800;
        sharedData_800E5768_1_s02.field_20 = 0xFFFBC000;
        sharedData_800E5768_1_s02.field_24 = 0x36800;
        sharedData_800E5768_1_s02.field_2C = 0xFFFB9800;
        sharedData_800E5768_1_s02.field_30 = 0x36800;
        sharedData_800E5768_1_s02.field_38 = 0xFFFB9800;
        sharedData_800E5768_1_s02.field_3C = 0x3AB33;
        sharedData_800E5768_1_s02.field_44 = 0xFFFB9800;
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
            sharedData_800E5768_1_s02.field_0 = 0x37800;
            sharedData_800E5768_1_s02.field_8 = 0x3F000;
            sharedData_800E5768_1_s02.field_C = 0x37800;
            sharedData_800E5768_1_s02.field_14 = 0x3A000;
            break;

        case 8:
            sharedData_800E5768_1_s02.field_0 = 0x64000;
            sharedData_800E5768_1_s02.field_8 = 0x38800;
            sharedData_800E5768_1_s02.field_C = 0x68000;
            sharedData_800E5768_1_s02.field_14 = 0x38800;
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
        for(updateCount = updatePrev;
            updateCount < (updatePrev + sharedData_800DD78C_0_s01[pass]);
            updateCount++, partIter++)
        {
            // Keep only the lower 4 bits.
            // NOTE: &= 0xF would be faster, but this is what they've done.
            partIter->type_1F %= 0xF0;

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
                    if (partIter->type_1F >= 2)
                    {
                        partIter->stateStep_1E = 0u;
                        partIter->type_1F = 0u;
                    }
                #endif
                    break;

                case 1:
                #if defined(MAP0_S00) || \
                    defined(MAP1_S02) || defined(MAP1_S03) || \
                    defined(MAP4_S02) || defined(MAP4_S03) || defined(MAP4_S04) || defined(MAP4_S05) || \
                    defined(MAP5_S00) || \
                    defined(MAP6_S00) || defined(MAP6_S03)
                    if (partIter->type_1F < 2 || partIter->type_1F > 3)
                    {
                        partIter->stateStep_1E = 0u;
                        partIter->type_1F = 2u;
                    }
                #endif
                    break;
            }

        #if defined(MAP7_S03)
            D_800F23D0 = (g_DeltaTime0 * 10936) / FP_TIME(1.0f);
        #endif

            if (sharedData_800DD78B_0_s01 != 0)
            {
                // NOTE: This function only has a body in `MAP07_S03` and everything else calls an empty function.
                sharedFunc_800CE954_7_s03(pass, partIter, &rand, &g_DeltaTime0);
            }
            else
            {
                switch (partIter->stateStep_1E)
                {
                    case ParticleState_Spawn:
                        if (sharedData_800E2156_0_s01 < density)
                        {
                            sharedData_800E2156_0_s01++;
                            sharedFunc_800CF9A8_0_s01(pass, partIter, &rand);
                        }
                        break;

                    case ParticleState_Active:
                        // TODO: This should pass `s_Particle*` but the matcher is struggling with that atm.
                        sharedFunc_800CEFD0_1_s02(pass, (s_sharedFunc_800CEFD0_1_s02*)partIter, &rand, &g_DeltaTime0);
                        break;

                    default: // `ParticleState_Rest`
                        partIter->stateStep_1E++;
                        if (partIter->stateStep_1E < SNOW_REST_TICKS_UPDATE_MAX)
                        {
                            // TODO: This should pass `s_Particle*` but the matcher is struggling with that atm.
                            sharedFunc_800CFFF8_0_s00(pass, (s_func_800CFFF8*)partIter, &rand);
                        }
                        #if defined(MAP1_S03) || \
                            defined(MAP4_S02) || defined(MAP4_S04) || defined(MAP4_S05) || \
                            defined(MAP5_S00) || \
                            defined(MAP6_S00) || defined(MAP6_S03)
                        else
                        {
                            sharedFunc_800D0690_1_s03(pass, partIter, &rand, &g_DeltaTime0);
                        }
                        #endif
                        break;
                }
            }
        }

        updatePrev += sharedData_800DD78C_0_s01[pass];
    }

    ////////////////////////////////////////////////////////////////////////////

    partIter = partHead;
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
            sharedData_800E32D0_0_s00 += sharedData_800DD78C_0_s01[pass];
            limitRange(sharedData_800E32D0_0_s00, 0, 135000);
        }
    #endif

        for(updateCount = updatePrev;
            updateCount < (updatePrev + sharedData_800DD78C_0_s01[pass]);
            updateCount++, partIter++)
        {
            switch (pass)
            {
                default:
                #if defined(MAP0_S00) || \
                    defined(MAP1_S02) || defined(MAP1_S03) || \
                    defined(MAP4_S02) || defined(MAP4_S03) || defined(MAP4_S04) || defined(MAP4_S05) || \
                    defined(MAP5_S00) || \
                    defined(MAP6_S00) || defined(MAP6_S03)
                    sharedFunc_800CEFF4_0_s00(partIter, sp64);
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
                    sharedFunc_800CEB24_0_s00(partIter);
                #endif
                    break;
            }
        }

        updatePrev += sharedData_800DD78C_0_s01[pass];
    }

    ////////////////////////////////////////////////////////////////////////////
    
    // Likely previous position for next particle system update.
    // Stores XZ position and rotation.
    sharedData_800E324C_0_s00.vx = prevPos.vx;
    sharedData_800E324C_0_s00.vz = prevPos.vz;
    sharedData_800E3260_0_s00 = sharedData_800E0C6E_0_s00;
    return false;
}
