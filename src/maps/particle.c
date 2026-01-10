#include "inline_no_dmpsx.h"
#include "maps/particle.h"

// Particle-related functions.
//
// TODO:
//  - This should be a separate .c file/split in each map overlay, but for now #including this .c works.
//  - sharedData and structs that are only used in this file need to be moved from `shared.h` into `particle.h`
//  - A lot more particle funcs that can be merged here, but the funcs included in each map varies a lot, will
//    likely need a lot of `#ifdef MAPX_SXX`.

#if defined(MAP1_S01) || defined(MAP1_S04) || defined(MAP1_S05) || defined(MAP2_S01) || \
    defined(MAP2_S03) || defined(MAP2_S04) || defined(MAP3_S02) || defined(MAP3_S03) || \
    defined(MAP3_S04) || defined(MAP3_S05) || defined(MAP4_S00) || defined(MAP4_S01) || \
    defined(MAP4_S06) || defined(MAP5_S02) || defined(MAP6_S01) || defined(MAP6_S02) || \
    defined(MAP6_S04) || defined(MAP6_S05) || defined(MAP7_S00) || defined(MAP7_S01) || \
    defined(MAP7_S02)
    #define MAP_USE_PARTICLES 0
#else
    #define MAP_USE_PARTICLES 1
#endif

#if defined(MAP1_S02) || defined(MAP1_S03) || defined(MAP4_S02) || defined(MAP4_S03) || \
    defined(MAP4_S04) || defined(MAP4_S05) || defined(MAP5_S00) || defined(MAP6_S03)
    #define MAP_PARTICLE_HAS_CASE_0 0
#else
    #define MAP_PARTICLE_HAS_CASE_0 1
#endif

// `sharedData_800E32D0_0_s00` writes and `sharedFunc_800D0CB8_0_s00` are gated behind `MAP_PARTICLE_HAS_CASE_1`.
#if defined(MAP0_S00) || defined(MAP1_S02) || defined(MAP1_S03) || \
    defined(MAP4_S02) || defined(MAP4_S03) || defined(MAP4_S04) || \
    defined(MAP4_S05) || defined(MAP5_S00) || defined(MAP6_S00) || defined(MAP6_S03)
    #define MAP_PARTICLE_HAS_CASE_1 1
#else
    #define MAP_PARTICLE_HAS_CASE_1 0
#endif

#if MAP_USE_PARTICLES

void sharedFunc_800CF2A4_0_s01(s32 arg0, s_Particle* part, u16* rand, s32* deltaTime)
{
    u16      localRand;
    s16      movement;
    VECTOR3* pos;
    
    pos = &part->position0_0;

    switch (arg0)
    {
        case 0:
#if MAP_PARTICLE_HAS_CASE_0
            // Random value has been generated in caller and `rand` argument.
            // Add random X offset.
            part->movement_18.vx += Rng_GenerateIntFromInput(*rand, -7, 7);

            // Random value for Z and Y to share and store in `rand` argument.
            *rand = (u16)Rng_Rand16();

            // Add random Z offset.
            localRand             = *rand;
            part->movement_18.vz += Rng_GenerateIntFromInput(localRand, -7, 7);

            // Add random Y offset.
            part->movement_18.vy += Rng_GenerateIntFromInput(*rand, -1, 3);

            // Apply movement to position over time.
            part->position0_0.vy += TIMESTEP_SCALE(*deltaTime, (part->movement_18.vy >> 1) << 2);
#endif
            break;

        case 1:
#if MAP_PARTICLE_HAS_CASE_1
            part->position1_C.vx = pos->vx;
            part->position1_C.vz = pos->vz;
            part->position1_C.vy = pos->vy - part->movement_18.vy;
            part->movement_18.vy += sharedData_800E32D4_0_s00;

            pos->vy += TIMESTEP_SCALE(*deltaTime, part->movement_18.vy << 2);
#endif
            break;
    }

    // Clamp Y position at 0 and rest.
    if (pos->vy >= Q12(0.0f))
    {
        pos->vy = Q12(0.0f);
    }
}

// @hack Needed for match. Same as version in `rng.h` but without parenthesess around it.
// TODO: Changing `rng.h version` still doesn't let it match though?
#define Rng_GenerateIntFromInput(rand, low, high) \
    (s32)((rand) % (((high) - (low)) + 1)) + (low)

void sharedFunc_800CEFD0_1_s02(s32 pass, s_Particle* part, u16* rand, s32* deltaTime)
{
    s_Collision coll;
    q19_12      xDeltaCase0;
    q19_12      zDeltaCase0;
    q19_12      xDeltaCase1;
    q19_12      zDeltaCase1;
    u16         localRand;
    s_Particle* localPart = part;
    
// Value used in case 0 comparison
#if defined(MAP1_S06)
    #define UNK_VAL 6
#elif defined(MAP7_S03)
    #define UNK_VAL 8
#else
    #define UNK_VAL 5
#endif

#if defined(MAP0_S00) || defined(MAP0_S01) || defined(MAP0_S02) || defined(MAP1_S00) || \
    defined(MAP1_S06) || defined(MAP2_S00) || defined(MAP2_S02) || defined(MAP3_S00) || \
    defined(MAP3_S01) || defined(MAP3_S06) || defined(MAP5_S01) || defined(MAP5_S03) || \
    defined(MAP6_S00) || defined(MAP7_S03)

    xDeltaCase0 = g_Particle_PrevPosition.vx - g_Particle_Position.vx;
    zDeltaCase0 = g_Particle_PrevPosition.vz - g_Particle_Position.vz;

#elif defined(MAP5_S00) || defined(MAP6_S03)
    xDeltaCase1 = g_Particle_PrevPosition.vx - g_Particle_Position.vx;
    zDeltaCase1 = g_Particle_PrevPosition.vz - g_Particle_Position.vz;
#endif

    switch (pass)
    {
        case 0:
#if MAP_PARTICLE_HAS_CASE_0
            if (localPart->type_1F == 0)
            {
                localPart->movement_18.vx += Rng_GenerateIntFromInput(*rand, -7, 7);
                *rand                      = Rng_Rand16();
                localRand                  = *rand;
                localPart->movement_18.vz += Rng_GenerateIntFromInput(localRand, -7, 7);
                localPart->movement_18.vy += Rng_GenerateIntFromInput(*rand, -1, 3);
            }
            else
            {
                s32 localRand2 = Rng_Rand16();
                s32 temp       = 12;

                localPart->movement_18.vy += ((temp - g_Particle_PrevPosition.vy) - (g_Particle_PrevPosition.vy << 1) - (sharedData_800DD588_0_s00[0] >> 4)) + Rng_GenerateIntFromInput(localRand2, -2, 2);

                limitRange(localPart->movement_18.vy, 5, 1000);
            }

            localPart->position0_0.vx += TIMESTEP_SCALE(*deltaTime, (localPart->movement_18.vx << 2) + g_Particle_SpeedX + xDeltaCase0);
            localPart->position0_0.vy += TIMESTEP_SCALE(*deltaTime, (localPart->movement_18.vy >> 1) << 2);
            localPart->position0_0.vz += TIMESTEP_SCALE(*deltaTime, (localPart->movement_18.vz << 2) + g_Particle_SpeedZ + zDeltaCase0);

#if defined(MAP7_S03)
            localPart->position0_0.vz += (zDeltaCase0 - D_800F23D0);
#endif

            if (ABS(localPart->position0_0.vx) + ABS(localPart->position0_0.vz) > Q12(UNK_VAL))
            {
                if (sharedData_800DF158_1_s02 != 0)
                {
                    sharedFunc_800D01BC_0_s00(rand, &part->position0_0, UNK_VAL);
                }
                else
                {
                    localPart->position0_0.vx = -localPart->position0_0.vx;
                    localPart->position0_0.vz = -localPart->position0_0.vz;
                    localPart->type_1F       += 240;
                }
            }

            if (localPart->position0_0.vy >= Q12(0.0f))
            {
#if defined(MAP7_S03)
                localPart->position0_0.vy = Q12(0.0f);
                localPart->movement_18.vy = Q12(0.0f);
                localPart->stateStep_1E++;
#else
                PushMatrix();
                Collision_Get(&coll, localPart->position0_0.vx + g_Particle_Position.vx, localPart->position0_0.vz + g_Particle_Position.vz);
                PopMatrix();

                if (localPart->position0_0.vy >= coll.groundHeight_0)
                {
#if defined(MAP1_S06)
                    localPart->stateStep_1E = 0;
#else
                    localPart->position0_0.vy = coll.groundHeight_0;
                    if (coll.groundHeight_0 < Q12(0.0f) && coll.groundHeight_0 > Q12(-0.2))
                    {
                        localPart->position0_0.vy = Q12(0.0f);
                    }

                    localPart->movement_18.vy = Q12(0.0f);
                    localPart->stateStep_1E++;
#endif
                }
#endif
            }
#endif
            break;

        case 1:
#if MAP_PARTICLE_HAS_CASE_1
#if !defined(MAP5_S00) && !defined(MAP6_S03)
            xDeltaCase1 = g_ParticleVectors1.viewPosition_C.vx - g_ParticleVectors0.viewPosition_C.vx;
            zDeltaCase1 = g_ParticleVectors1.viewPosition_C.vz - g_ParticleVectors0.viewPosition_C.vz;

            localPart->position1_C.vx = localPart->position0_0.vx;
            localPart->position1_C.vz = localPart->position0_0.vz;
            localPart->position1_C.vy = localPart->position0_0.vy - localPart->movement_18.vy;
#endif
            localPart->position0_0.vx += TIMESTEP_SCALE(*deltaTime, g_Particle_SpeedX + xDeltaCase1);
            localPart->movement_18.vy += sharedData_800E32D4_0_s00;
            localPart->position0_0.vy += TIMESTEP_SCALE(*deltaTime, localPart->movement_18.vy << 2);

#if defined(MAP5_S00) || defined(MAP6_S03)
            localPart->position1_C.vy = localPart->position0_0.vy - Q12(0.125f);
#endif

            localPart->position0_0.vz += TIMESTEP_SCALE(*deltaTime, g_Particle_SpeedZ + zDeltaCase1);

#if defined(MAP5_S00) || defined(MAP6_S03)
            localPart->position1_C.vx = localPart->position0_0.vx;
            localPart->position1_C.vz = localPart->position0_0.vz;
#endif

            if (sharedData_800DF158_1_s02 != 0)
            {
                localPart->position1_C.vx = localPart->position0_0.vx;
                localPart->position1_C.vz = localPart->position0_0.vz;
            }

            if (ABS(localPart->position0_0.vx) + ABS(localPart->position0_0.vz) > Q12(6.0))
            {
                if (sharedData_800DF158_1_s02 != 0)
                {
                    sharedFunc_800D01BC_0_s00(rand, &part->position0_0, 6);

                    localPart->position1_C.vx = localPart->position0_0.vx;
                    localPart->position1_C.vz = localPart->position0_0.vz;
                }
                else
                {
                    localPart->position1_C.vx -= localPart->position0_0.vx;
                    localPart->position1_C.vz -= localPart->position0_0.vz;

                    localPart->position0_0.vx = -localPart->position0_0.vx;
                    localPart->position0_0.vz = -localPart->position0_0.vz;

                    localPart->position1_C.vx += localPart->position0_0.vx;
                    localPart->position1_C.vz += localPart->position0_0.vz;
                }
            }

            if (localPart->position0_0.vy >= 0)
            {
                PushMatrix();
                Collision_Get(&coll, localPart->position0_0.vx + g_Particle_Position.vx, localPart->position0_0.vz + g_Particle_Position.vz);
                PopMatrix();

                localPart->position0_0.vy = coll.groundHeight_0;
                localPart->movement_18.vx = coll.field_8;

                if (coll.field_8 == 11)
                {
                    localPart->type_1F        = 3;
                    localPart->position1_C.vx = localPart->position0_0.vx;
                    localPart->position1_C.vz = localPart->position0_0.vz;
                    localPart->position1_C.vy = localPart->position0_0.vy - 96; // TODO: Float.
                }

                localPart->movement_18.vz = Q12(0.0f);
                localPart->movement_18.vy = Q12(0.0f);
                localPart->stateStep_1E++;
            }
#endif
            break;
    }
}

void sharedFunc_800CFFF8_0_s00(s32 pass, s_Particle* part, s16* rand)
{
    s32 absX;
    s32 threshold;

#if defined(MAP7_S03)
    #define PASS_ADD 8
#elif defined(MAP1_S06)
    #define PASS_ADD 6
#else
    #define PASS_ADD 5
#endif

    part->position0_0.vx += g_Particle_PrevPosition.vx - g_Particle_Position.vx;
    part->position0_0.vz += g_Particle_PrevPosition.vz - g_Particle_Position.vz;

#if defined(MAP7_S03)
    part->position0_0.vz += ((g_Particle_PrevPosition.vz - g_Particle_Position.vz) - D_800F23D0);
#endif

#if MAP_PARTICLE_HAS_CASE_0
    if (pass == 0 && sharedData_800E0CAC_0_s00 == 3)
    {
        part->position0_0.vx += FP_FROM(g_Particle_SpeedX, Q4_SHIFT);
        part->position0_0.vz += FP_FROM(g_Particle_SpeedZ, Q4_SHIFT);
    }
#endif

#if !defined(MAP1_S00) && !defined(MAP1_S02) && !defined(MAP1_S03) && !defined(MAP4_S04) && \
    !defined(MAP4_S05) && !defined(MAP5_S00) && !defined(MAP6_S00) && !defined(MAP6_S03) && \
    !defined(MAP7_S03)
    if (sharedData_800DD591_0_s00 != 0)
    {
        return;
    }
#endif

    absX = abs(part->position0_0.vx);

    // This helps match the original code: `threshold = threshold = ...` 
    // Also matches:
    // threshold = FP_TO(pass + 5, Q12_SHIFT); threshold = threshold += 0;
    threshold = threshold = FP_TO(pass + PASS_ADD, Q12_SHIFT);
    
    if (ABS_ADD(part->position0_0.vz, absX) > threshold)
    {
        part->stateStep_1E = 0;
    }
    
    if (part->type_1F == 3 || part->type_1F == 0xF3)
    {
        part->position1_C.vx = part->position0_0.vx;
        part->position1_C.vz = part->position0_0.vz;
    }
}

#if defined(MAP1_S03) || defined(MAP4_S02) || defined(MAP4_S04) || defined(MAP4_S05) || \
    defined(MAP5_S00) || defined(MAP6_S00) || defined(MAP6_S03)

void sharedFunc_800D0690_1_s03(s32 pass, s_Particle* part, s16* rand, q19_12* deltaTime)
{
    q19_12 x = g_Particle_PrevPosition.vx - g_Particle_Position.vx;
    q19_12 z = g_Particle_PrevPosition.vz - g_Particle_Position.vz;

    part->position1_C.vy  = part->position0_0.vy - part->movement_18.vy;
    part->position0_0.vx += TIMESTEP_SCALE(*deltaTime, x);
    part->movement_18.vy += Q12(0.001f);
    part->position0_0.vy += TIMESTEP_SCALE(*deltaTime, part->movement_18.vy << 2);
    part->position1_C.vy  = part->position0_0.vy - Q12(1.0f / 32.0f);
    part->position0_0.vz += TIMESTEP_SCALE(*deltaTime, z);
    part->position1_C.vx  = part->position0_0.vx;
    part->position1_C.vz  = part->position0_0.vz;

    if ((ABS(part->position0_0.vx) + ABS(part->position0_0.vz)) > Q12(6.0f))
    {
        part->stateStep_1E = 0;
    }
}
#endif

void sharedFunc_800CE954_7_s03(s32 pass, s_Particle* part, s16* rand, q19_12* deltaTime)
{
#if defined(MAP7_S03)
    q19_12      deltaX;
    q19_12      deltaZ;
    s_Particle* ptr;

    ptr = part;
    
    deltaX = g_Particle_PrevPosition.vx - g_Particle_Position.vx;
    deltaZ = g_Particle_PrevPosition.vz - g_Particle_Position.vz;

    if (pass == 0)
    {
        part->position0_0.vx += deltaX;
        part->position0_0.vz += deltaZ - ((*deltaTime) * 2);

        if ((ABS(part->position0_0.vx) + ABS(part->position0_0.vz)) > Q12(8.0))
        {
            if (sharedData_800DF158_1_s02 != 0)
            {
                sharedFunc_800D01BC_0_s00(rand, &part->position0_0, 8);
            }
            else
            {
                ptr->position0_0.vx = -ptr->position0_0.vx;
                ptr->position0_0.vz = -ptr->position0_0.vz;
            }

            ptr->type_1F += 0xF0;
        }
    }
#endif
}

#if defined(MAP0_S00)
bool func_800D012C(VECTOR3* pos, s_func_800CC8FC* unused0, s32* unused1) // 0x800D012C
{
    q19_12 deltaX;
    q19_12 deltaZ;

    switch (g_SysWork.field_234B_4)
    {
        case 1:
            return true;

        case 2:
            deltaX = Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vx - pos->vx);
            deltaZ = Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vz - pos->vz);
            return SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)) < Q8(1.0f);
    }

    return false;
}
#endif

void sharedFunc_800D01BC_0_s00(u16* arg0, VECTOR3* arg1, s32 arg2)
{
    s32 temp_a0;
    s32 temp_s3;

    temp_a0  = (*arg0 % FP_TO(arg2, Q12_SHIFT)) + (Rng_Rand16() % FP_TO(arg2, Q12_SHIFT));
    temp_s3  = temp_a0 - FP_TO(arg2, Q12_SHIFT);
    arg1->vx = temp_s3;
    temp_s3  = FP_TO(arg2, Q12_SHIFT) - abs(temp_s3);
    arg1->vz = ((*arg0 % temp_s3) + (Rng_Rand16() % temp_s3)) - temp_s3;
}

void sharedFunc_800CF9A8_0_s01(s32 arg0, s_Particle* part, u16* rand)
{
    #define SNOW_Y_START_SPEED  Q12(0.0245f)
    #define RAIN_XZ_SPAWN_RANGE 6
#if defined(MAP1_S06)
    #define SNOW_XZ_SPAWN_RANGE 6
#elif defined(MAP7_S03)
    #define SNOW_XZ_SPAWN_RANGE 8
#else
    #define SNOW_XZ_SPAWN_RANGE 5
#endif

    s_Particle* localPart;

    localPart = part;

    switch (arg0)
    {
        case 0:
#if MAP_PARTICLE_HAS_CASE_0
            if (sharedData_800DD592_0_s00 != 0)
            {
                part->type_1F = ParticleType_Snow;
            }
            else
            {
                part->type_1F = ParticleType_Unk1;
            }

            // Set start position.
            localPart->position0_0.vy = g_Particle_Position.vy;

            // Set downward movement.
            localPart->movement_18.vz = Q12(0.0f);
            localPart->movement_18.vx = Q12(0.0f);
            localPart->movement_18.vy = SNOW_Y_START_SPEED;

            // Set random start XZ position.
            sharedFunc_800D01BC_0_s00(rand, part, SNOW_XZ_SPAWN_RANGE);

            // Second position unused for snow.
            localPart->position1_C.vz = Q12(0.0f);
            localPart->position1_C.vy = Q12(0.0f);
            localPart->position1_C.vx = Q12(0.0f);
#endif
            break;

        case 1:
#if MAP_PARTICLE_HAS_CASE_1
            localPart->type_1F = ParticleType_Rain;
            
            // Set start position.
            localPart->position0_0.vy = g_Particle_Position.vy + Q12(Rng_GenerateInt(0, 2));

#if defined(MAP5_S00) || defined(MAP6_S03)
            localPart->position1_C.vy = localPart->position0_0.vy - Q12(0.125f);
            localPart->movement_18.vy = Q12(0.0091f);
#else
            localPart->position1_C.vy = g_Particle_Position.vy;
            localPart->movement_18.vy = Q12(0.03675f);
#endif

            // Set random start XZ position.
            sharedFunc_800D01BC_0_s00(rand, part, RAIN_XZ_SPAWN_RANGE);

            // Copy random XZ to second position.
            localPart->position1_C.vx = localPart->position0_0.vx;
            localPart->position1_C.vz = localPart->position0_0.vz;
#endif
            break;
    }

    // Step to active state.
    localPart->stateStep_1E++;
}

#endif

#if defined(MAP0_S00)
void func_800D0394(s32 arg0, VECTOR3* vecs) // 0x800D0394
{
    s32 i;

    g_SysWork.field_234B_4 = arg0;

    if (arg0)
    {
        sharedFunc_800D0A60_0_s00(D_800C39A0);

        if (arg0 == 2)
        {
            for (i = 0; i < ARRAY_SIZE(D_800E32DC); i++, vecs++)
            {
                D_800E32DC[i].vx = vecs->vx;
                D_800E32DC[i].vy = vecs->vy;
                D_800E32DC[i].vz = vecs->vz;
            }

            if (D_800DD593)
            {
                for (i = 0; i < ARRAY_SIZE(sharedData_800E34FC_0_s00); i++)
                {
                    // TODO: Is this angle math?
                    sharedData_800E34FC_0_s00[i].field_0.vx = Rng_AddGeneratedUInt(D_800E32DC[(i / 20) + 1].vx, Q12(-0.5f), Q12(0.5f) - 1);
                    sharedData_800E34FC_0_s00[i].field_0.vz = Rng_AddGeneratedUInt(D_800E32DC[(i / 20) + 1].vz, Q12(-0.5f), Q12(0.5f) - 1);
                    sharedData_800E34FC_0_s00[i].field_0.vy = D_800E32DC[(i / 20) + 1].vy;
                    sharedData_800E34FC_0_s00[i].field_11   = 1;
                    sharedData_800E34FC_0_s00[i].field_10   = 1;
                    sharedData_800E34FC_0_s00[i].field_12   = 0;
                    sharedData_800E34FC_0_s00[i].field_C    = 0;
                    sharedData_800E34FC_0_s00[i].field_E    = 0;
                }
            }

            if (D_800DD594)
            {
                for (i = 0; i < ARRAY_SIZE(sharedData_800E330C_0_s00); i++)
                {
                    sharedData_800E330C_0_s00[i].field_0.vx = D_800E32DC[0].vx + Rng_GenerateInt(Q12(-2.5f), Q12(2.5f) - 1);
                    sharedData_800E330C_0_s00[i].field_0.vy = D_800E32DC[0].vy + Rng_GenerateIntFromInput(-Rng_Rand16(), 0, Q12(4.0f) - 1); // TODO: Weird `-Rng_Rand16()`
                    sharedData_800E330C_0_s00[i].field_0.vz = D_800E32DC[0].vz + Rng_GenerateInt(Q12(-2.5f), Q12(2.5f) - 1);

                    sharedData_800E330C_0_s00[i].field_15   = 1;
                    sharedData_800E330C_0_s00[i].field_14   = 1;
                    sharedData_800E330C_0_s00[i].field_C.vx = 0;
                    sharedData_800E330C_0_s00[i].field_C.vz = 0;
                }
            }
        }
    }
}

bool func_800D0600(void) // 0x800D0600
{
    #define DIST_MAX Q12(40.0f)

    if (ABS(g_SysWork.playerWork_4C.player_0.position_18.vx - D_800E32DC[0].vx) +
        ABS(g_SysWork.playerWork_4C.player_0.position_18.vz - D_800E32DC[0].vz) < DIST_MAX ||
        ABS(g_SysWork.playerWork_4C.player_0.position_18.vx - D_800E32DC[1].vx) +
        ABS(g_SysWork.playerWork_4C.player_0.position_18.vz - D_800E32DC[1].vz) < DIST_MAX)
    {
        return true;
    }

    return false;
}
#endif

#if defined(MAP0_S00) || defined(MAP0_S01) || defined(MAP0_S02) || defined(MAP1_S06) || \
    defined(MAP2_S00) || defined(MAP2_S02) || defined(MAP3_S00) || defined(MAP3_S01) || \
    defined(MAP3_S06) || defined(MAP4_S02) || defined(MAP4_S03) || defined(MAP5_S01) || \
    defined(MAP5_S03)
void sharedFunc_800D0700_0_s00(VECTOR3* point, VECTOR3* lineStart, VECTOR3* lineEnd, s32 flag)
{
    VECTOR3 offset0;
    VECTOR3 offset1;
    VECTOR3 lineStartCpy;
    VECTOR3 lineEndCpy;
    s32     vecPToA_X;
    s32     vecPToA_Z;
    s32     vecPToB_X;
    s32     vecPToB_Z;
    s32     crossTerm1;
    s32     crossTerm2;

    // Early exit check.
    if (lineStart->vx == NO_VALUE)
    {
        point->vy = 1;
        return;
    }

    point->vx += g_Particle_Position.vx;
    offset0.vx = point->vx;

    point->vz += g_Particle_Position.vz;
    offset0.vz = point->vz;

    offset1.vx = offset0.vx;

    lineStartCpy.vx = lineStart->vx;
    lineEndCpy.vx   = lineEnd->vx;

    offset1.vy = offset0.vz;

    lineStartCpy.vy = lineStart->vz;
    lineEndCpy.vy   = lineEnd->vz;

    vecPToA_X = FP_FROM(lineStartCpy.vx - offset0.vx, Q4_SHIFT);
    vecPToB_X = FP_FROM(lineEndCpy.vx   - offset0.vx, Q4_SHIFT);
    vecPToA_Z = FP_FROM(lineStartCpy.vy - offset0.vz, Q4_SHIFT);
    vecPToB_Z = FP_FROM(lineEndCpy.vy   - offset0.vz, Q4_SHIFT);

    crossTerm1 = vecPToA_X * vecPToB_Z;
    crossTerm2 = vecPToA_Z * vecPToB_X;

    if (crossTerm2 < crossTerm1)
    {
        if (!flag)
        {
            if (lineStart->vx == lineEnd->vx)
            {
                if (lineStart->vx < offset0.vx)
                {
                    point->vx -= ABS(offset0.vx - lineStart->vx) * 2;
                }
                else
                {
                    point->vx += ABS(offset0.vx - lineStart->vx) * 2;
                }
            }
            else
            {
                if (lineStart->vz < offset0.vz)
                {
                    point->vz -= ABS(offset0.vz - lineStart->vz) * 2;
                }
                else
                {
                    point->vz += ABS(offset0.vz - lineStart->vz) * 2;
                }
            }
        }

        point->vy = 0;
    }
    else
    {
        point->vy = 1;
    }

    point->vx -= g_Particle_Position.vx;
    point->vz -= g_Particle_Position.vz;
}
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

#if MAP_PARTICLE_HAS_CASE_1
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
#if MAP_PARTICLE_HAS_CASE_1
            sharedData_800E32D0_0_s00 = 135000;
#endif
            break;

        case 6:
            var_s1                    = 2;
            var_s0                    = 1;
            sharedData_800DFB6C_0_s00 = 0;
            sharedData_800DFB70_0_s00 = 1;
#if MAP_PARTICLE_HAS_CASE_1
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

#if MAP_PARTICLE_HAS_CASE_1
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

#if MAP_PARTICLE_HAS_CASE_1
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
