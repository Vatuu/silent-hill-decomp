#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/air_screamer.h"

// NOTES: 
// - M0S01 includes extra functions missing entirely from other maps in the `defined(MAP0_S01)` block below.
//
// - There might still be a _lot_ of extra Air Screamer code not added here yet.
//   In MAP2_S00, all the code from the `air_screamer.c` include up to `Ai_Groaner_Update` seems to be Air Screamer related?
//   (140+ funcs... this includes the 25+ different func variants that all made use of `field_14C.bits.field_14C_2` etc)
//   Since there's `INCLUDE_ASM` gaps those can't really be moved here yet.
//   (MAP0_S01 also seems to share the same funcs, but most look ifdef'd out there, would need to make sure those are shared properly there first)

#define airScreamerProps airScreamer->properties_E4.airScreamer

void Ai_AirScreamer_Update(s_SubCharacter* airScreamer, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    sharedFunc_800D21E4_0_s01(anmHdr, coords);
    sharedFunc_800D2200_0_s01(airScreamer);

    Ai_AirScreamer_Init(airScreamer);

    sharedFunc_800D2274_0_s01(airScreamer);
    sharedFunc_800D2390_0_s01(airScreamer);
    sharedFunc_800D3928_0_s01(airScreamer);
    sharedFunc_800D62D8_0_s01(airScreamer);
    sharedFunc_800D7AB0_0_s01(airScreamer);
    sharedFunc_800D7EBC_0_s01(airScreamer);
    sharedFunc_800D81B0_0_s01(airScreamer);
}

bool sharedFunc_800D21E4_0_s01(s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    sharedData_800E21D0_0_s01.anmHdr_4 = anmHdr;
    sharedData_800E21D0_0_s01.coords_8 = coords;
    sharedData_800E21D0_0_s01.flags_0  = false;
    return true;
}

void sharedFunc_800D2200_0_s01(s_SubCharacter* airScreamer)
{
    s32 count;

    count = func_800808AC(airScreamer->position_18.vx, airScreamer->position_18.vz);
    if (count == 7)
    {
        return;
    }

    if (count < 8)
    {
        if (count != 0)
        {
            airScreamerProps.groundHeight_124 = Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz);
        }
    }
    else if (count != 12)
    {
        airScreamerProps.groundHeight_124 = Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz);
    }
}

bool sharedFunc_800D2274_0_s01(s_SubCharacter* airScreamer)
{
    s32              i;
    u32              flags;
    s_func_800D2E04* data;

    flags = airScreamerProps.flags_11C;

    if (!(flags & AirScreamerFlag_16))
    {
        if (flags & (AirScreamerFlag_3 | AirScreamerFlag_6))
        {
            flags &= ~(AirScreamerFlag_3 | AirScreamerFlag_6);
            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                flags |= AirScreamerFlag_6;
            }
            else
            {
                flags |= AirScreamerFlag_3;
            }
        }

        if (flags & AirScreamerFlag_28)
        {
            flags &= ~(AirScreamerFlag_2 | AirScreamerFlag_3 | AirScreamerFlag_4 | AirScreamerFlag_5 | AirScreamerFlag_6);
        }
        else if (flags & AirScreamerFlag_6)
        {
            flags &= ~(AirScreamerFlag_2 | AirScreamerFlag_3 | AirScreamerFlag_4 | AirScreamerFlag_5);
            Sd_SfxStop(sharedData_800CAA98_0_s01.sfxVolumes_CE8[2].id_0);
        }

        // Run through flags defining which SFX to play.
        data = &sharedData_800CAA98_0_s01;
        for (i = 0; i < 11; i++)
        {
            if (flags & (1 << i))
            {
                func_8005DC1C(data->sfxVolumes_CE8[i].id_0, &airScreamer->position_18, data->sfxVolumes_CE8[i].volume_2, 0);
            }
        }
    }

    return true;
}

void sharedFunc_800D2364_0_s01(s_SubCharacter* airScreamer)
{
    func_8005DC1C(Sfx_Unk1590, &airScreamer->position_18, Q8(0.5f), 0);
}

#define BIT_MASK(bit) \
    (1 << (bit))

#define BIT_GET(var, val, bit) \
    ((var) = ((u32)(val) >> (bit)), (var) &= 1)

#define BIT_SET(val, bit) \
    (((val) |  BIT_MASK(bit)))

#define BIT_CLEAR(val, bit) \
    (((val) & ~BIT_MASK(bit)))

static inline u32 BitAssign(u32 val, u32 bit, bool cond)
{
    u32 newVal;

    if (cond)
    {
        newVal = BIT_SET(val, bit);
    }
    else
    {
        newVal = BIT_CLEAR(val, bit);
    }

    return newVal;
}

static inline u32 MaskAssign(u32 val, u32 mask, bool cond)
{
    u32 newVal;

    if (cond)
    {
        newVal = val | mask;
    }
    else
    {
        newVal = val & ~mask;
    }

    return newVal;
}

bool sharedFunc_800D2390_0_s01(s_SubCharacter* airScreamer)
{
    s32    bit0;
    s32    bit4;
    s32    bit5;
    s32    bit7;
    s32    sp20;
    s32    sp24;
    s32    sp28;
    bool   cond0;
    s32    bit14;
    s32    sp34;
    s32    bit15;
    s32    bit27;
    s32    cond1;
    s32    bit3;
    q19_12 posX;
    q19_12 posZ;
    s32    temp_s0_2;
    bool   cond2;
    s32    bit22;
    s32    flags;
    s32    bit6;
    s32    bit2;
    s32    bit1;
    s32    temp_s6;
    s32    temp_v0;
    s32    temp_v0_2;
    s32    var_s3;
    s32    var_s4;
    s32    var_s7;
    s32    var_v0;
    s32    var_v0_20;
    s32    var_v1_3;
    s32    bit21;
    s32    var_a0;
    s32    new_var2;
    s32    new_var4;

    sp28 = 0;

    posX  = airScreamer->position_18.vx;
    flags = airScreamerProps.flags_11C;
    posZ  = airScreamer->position_18.vz;

    temp_v0 = sharedData_800CAA98_0_s01.unk_380[39][airScreamer->model_0.anim_4.keyframeIdx_8];

    BIT_GET(bit1, temp_v0, 1);
    BIT_GET(bit2, temp_v0, 2);
    BIT_GET(bit3, temp_v0, 3);
    BIT_GET(bit4, temp_v0, 4);
    BIT_GET(bit5, temp_v0, 5);
    BIT_GET(bit6, temp_v0, 6);
    BIT_GET(bit7, temp_v0, 7);
    BIT_GET(bit0, temp_v0, 0);

    temp_s0_2 = func_800808AC(posX, posZ);

    cond2 = temp_s0_2 == 7;
    if (airScreamer->position_18.vy >= (Collision_GroundHeightGet(posX, posZ) - Q12(0.15f)))
    {
        sp28 = !cond2;
    }

    cond0 = false;
    if (temp_s0_2 == 12 || temp_s0_2 == 0)
    {
        cond0 = true;
    }

    BIT_GET(bit27, flags, 27);

    cond1 = false;
    if (flags & PlayerFlag_Unk13 || cond0)
    {
        cond1 = true;
    }

    BIT_GET(bit21, flags, 21);
    BIT_GET(bit22, flags, 22);
    BIT_GET(bit14, flags, 14);
    BIT_GET(bit15, flags, 15);

    temp_v0_2 = flags & (PlayerFlag_Unk6 | PlayerFlag_Unk28);
    sp34      = temp_v0_2;
    sp34      = temp_v0_2 != 0;
    sp20      = 0;

    temp_s6 = (bit0 == 0) & (bit1 == 0);

    if (bit6 == 0)
    {
        sp20 = bit1 & 0x1;
    }

    var_s7 = 0;

    sp24 = bit1 & bit6;

    if (bit2 == 0)
    {
        var_s7 = temp_s6 & 0x1;
    }

    var_s3 = 0;

    if (bit2 != 0)
    {
        var_s3 = temp_s6 & 0x1;
    }

    var_s4 = 0;

    if (airScreamer->position_18.vy < (Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz) - Q12(0.1f)))
    {
        switch (func_800808AC(airScreamer->position_18.vx, airScreamer->position_18.vz))
        {
            case 7:
            case 0:
            case 12:
                break;

            default:
                if (!bit21)
                {
                    var_v0 = var_s7 & 0x1;
                }
                else
                {
                    var_v0 = 0;
                }

                var_s4 = temp_s6 & var_v0;

                if (!bit22)
                {
                    var_s4 = temp_s6 & (var_v0 | var_s3);
                }
                break;
        }
    }

    // TODO: Weird `e_AirScreamerFlags` operations.

    flags = BitAssign(flags, 13, bit0 & sp28);
    flags = BitAssign(flags, 17, bit0);
    flags = BitAssign(flags, 18, !bit1);
    flags = BitAssign(flags, 19, sp20);
    flags = BitAssign(flags, 20, sp24);
    flags = BitAssign(flags, 21, var_s7);
    flags = BitAssign(flags, 22, var_s3);
    flags = BitAssign(flags, 23, !bit3 ? (temp_s6 & 1) : 0);
    flags = BitAssign(flags, 24, (bit3 == 1) ? (temp_s6 & 1) : 0);
    flags = BitAssign(flags, 25, bit4);
    flags = BitAssign(flags, 26, bit5);
    flags = BitAssign(flags, 27, bit7);
    flags = BIT_CLEAR(BitAssign(flags, 15, bit14), 14);
    var_a0 = BitAssign(flags, 28, sp34);

    new_var4 = AirScreamerFlag_7;

    if (bit27 == 0)
    {
        var_v1_3 = bit7;
        var_v1_3 = var_v1_3 & sp20;
    }
    else
    {
        var_v1_3 = 0;
    }

    var_v1_3 = MaskAssign(var_a0, new_var4, var_v1_3);

    new_var2 = AirScreamerFlag_8;
    flags  = MaskAssign(var_v1_3, new_var2, (bit27 == 0) ? ((bit7 & 0x1) & sp24) : 0);
    var_v1_3 = BitAssign(flags, 9, var_s4);

    var_a0 = AirScreamerFlag_10;
    if (!cond0 && !cond1)
    {
        var_v0_20 = bit0;
        var_v0_20 = var_v0_20 & sp28;
    }
    else
    {
        var_v0_20 = 0;
    }

    flags = BIT_CLEAR(MaskAssign(var_v1_3, var_a0, var_v0_20), 4);
    flags &= ~AirScreamerFlag_5;
    flags &= ~AirScreamerFlag_6;
    flags = BIT_CLEAR(BitAssign(flags, 3, !bit15 ? (bit14 & (1 << 0)) : 0), 2);
    flags &= ~AirScreamerFlag_0;
    flags &= ~AirScreamerFlag_1;

    airScreamerProps.flags_11C = flags;
    return true;
}

bool Ai_AirScreamer_Init(s_SubCharacter* airScreamer)
{
    #define BASE_HEALTH                 Q12(380.0f)
    #define AIR_SCREAMER_RAND_MAX       100
    #define NIGHT_FLUTTER_RAND_MAX      300
    #define RAND_MAX_HEALTH_BONUS_EASY -100
    #define RAND_MAX_HEALTH_BONUS_HARD  100

    // Return early if already initialized.
    if (airScreamer->model_0.controlState_2 != AirScreamerControl_None)
    {
        return false;
    }

    // Set base health with random variation, accounting for differences between Air Screamer and Night Flutter.
    if (airScreamer->model_0.charaId_0 == Chara_NightFlutter)
    {
        airScreamer->health_B0 = BASE_HEALTH + (Rng_RandQ12() * NIGHT_FLUTTER_RAND_MAX);
    }
    else
    {
        airScreamer->health_B0 = BASE_HEALTH + (Rng_RandQ12() * AIR_SCREAMER_RAND_MAX);
    }

    // Set health according to game difficulty.
    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case GameDifficulty_Easy:
            airScreamer->health_B0 += Rng_RandQ12() * RAND_MAX_HEALTH_BONUS_EASY;
            break;

        case GameDifficulty_Normal:
            break;

        case GameDifficulty_Hard:
            airScreamer->health_B0 += Rng_RandQ12() * RAND_MAX_HEALTH_BONUS_HARD;
            break;
    }

    sharedFunc_800D2BF4_0_s01(airScreamer);
    sharedSymbol_800D3B0C_0_s01(airScreamer);
    sharedFunc_800D2390_0_s01(airScreamer);
    sharedFunc_800D2390_0_s01(airScreamer);
    sharedFunc_800D2B00_0_s01(airScreamer);
    sharedFunc_800D2B10_0_s01(airScreamer);
    sharedFunc_800D2B28_0_s01(airScreamer);
    sharedFunc_800D2B4C_0_s01(airScreamer);
    Ai_AirScreamer_GroundWarp(airScreamer);
    sharedFunc_800D2BE4_0_s01(airScreamer);

    return true;

    #undef BASE_HEALTH
    #undef AIR_SCREAMER_RAND_MAX
    #undef NIGHT_FLUTTER_RAND_MAX
    #undef RAND_MAX_HEALTH_BONUS_EASY
    #undef RAND_MAX_HEALTH_BONUS_HARD
}

void sharedFunc_800D2B00_0_s01(s_SubCharacter* airScreamer)
{
    airScreamer->rotation_24.vx  = FP_ANGLE(0.0f);
    airScreamer->rotation_24.vz  = FP_ANGLE(0.0f);
    airScreamer->field_2A        = FP_ANGLE(0.0f);
}

void sharedFunc_800D2B10_0_s01(s_SubCharacter* airScreamer)
{
    airScreamer->damage_B4.position_0.vx = Q12(0.0f);
    airScreamer->damage_B4.position_0.vy = Q12(0.0f);
    airScreamer->damage_B4.position_0.vz = Q12(0.0f);
    airScreamer->damage_B4.amount_C      = Q12(0.0f);
    airScreamer->properties_E4.airScreamer.field_F4 = 0;
}

void sharedFunc_800D2B28_0_s01(s_SubCharacter* airScreamer)
{
    airScreamer->moveSpeed_38        = Q12(0.0f);
    airScreamer->field_34            = Q12(0.0f);
    airScreamer->rotationSpeed_2C.vx = FP_ANGLE(0.0f);
    airScreamer->rotationSpeed_2C.vy = FP_ANGLE(0.0f);
    airScreamer->rotationSpeed_2C.vz = FP_ANGLE(0.0f);
    airScreamer->field_32            = Q12(0.0f);
    airScreamer->headingAngle_3C     = airScreamer->rotation_24.vy;
}

void sharedFunc_800D2B4C_0_s01(s_SubCharacter* airScreamer)
{
    q19_12         deltaTime;
    s_AnmHeader*   anmHdr;
    GsCOORDINATE2* coords;

    deltaTime = g_DeltaTime0;

    anmHdr = sharedData_800E21D0_0_s01.anmHdr_4;
    coords = sharedData_800E21D0_0_s01.coords_8;

    g_DeltaTime0 = Q12(0.0f);
    func_80044950(airScreamer, anmHdr, coords);
    g_DeltaTime0 = deltaTime;

    sharedFunc_800D7560_0_s01(airScreamer);
    sharedFunc_800D82B8_0_s01(airScreamer);
}

void Ai_AirScreamer_GroundWarp(s_SubCharacter* airScreamer)
{
    airScreamer->position_18.vy = Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz);
}

void sharedFunc_800D2BE4_0_s01(s_SubCharacter* airScreamer)
{
    airScreamer->properties_E4.airScreamer.field_EC = 0;
    airScreamer->properties_E4.airScreamer.field_F0 = 0;
    airScreamer->properties_E4.airScreamer.field_F2 = 0;
}

void sharedFunc_800D2BF4_0_s01(s_SubCharacter* airScreamer)
{
    ModelAnim_AnimInfoSet(&airScreamer->model_0.anim_4, &sharedData_800CAA98_0_s01.animInfo_0);
}

s32 Ai_AirScreamer_DamageTake(s_SubCharacter* airScreamer, q19_12 mult)
{
    q19_12 damage;
    s32    animStatus;
    s32    attack;
    u32    ret;
    s32    temp_v0;
    u8     temp_a1;
    q19_12 angle;

    damage     = airScreamer->damage_B4.amount_C;
    animStatus = airScreamer->model_0.anim_4.status_0;
    attack     = airScreamer->attackReceived_41;
    ret        = 0;

    if (airScreamer->properties_E4.unk0.field_E8_0 == 3)
    {
        switch (attack)
        {
            case 1:
            case 4:
                damage += damage / 2;
                break;

            case 33:
            case 34:
                damage = damage / 2;
                break;

            default:
                break;
        }
    }

    if (airScreamer->health_B0 > Q12(0.0f))
    {
        if (animStatus == ANIM_STATUS(21, true))
        {
            temp_v0 = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 10.0f, Q12_SHIFT);
            if (temp_v0 < airScreamer->health_B0)
            {
                airScreamer->health_B0 -= temp_v0;
            }
            else
            {
                airScreamer->health_B0 = Q12(0.0f);
            }
        }

        airScreamer->damage_B4.amount_C = Q12(0.0f);
        angle                     = mult; // @hack

        damage = FP_MULTIPLY_PRECISE(damage, angle, Q12_SHIFT);
        if (damage < airScreamer->health_B0)
        {
            airScreamer->health_B0 -= damage;
        }
        else
        {
            airScreamer->health_B0 = Q12(0.0f);
        }
    }

    if (damage > Q12(0.0f) || airScreamer->health_B0 <= Q12(0.0f))
    {
        temp_a1 = D_800AD4C8[attack].field_10;
        angle   = FP_ANGLE_NORM_S(g_SysWork.playerWork_4C.player_0.rotation_24.vy - airScreamer->rotation_24.vy);

#ifdef MAP0_S01
        if (airScreamer->health_B0 <= Q12(0.0f))
#else
        if (airScreamer->health_B0 <= Q12(120.0f))
#endif
        {
            if (damage > Q12(5.0f))
            {
                ret = 4;
            }
            else
            {
                ret = 3;
            }
        }
        else if (airScreamer->properties_E4.unk0.field_E8_0 != 3 && temp_a1 == 2 && Math_CheckSignedRange(angle, FP_ANGLE(120.0f)))
        {
            ret = 2;
        }
        else if (airScreamer->properties_E4.unk0.field_E8_0 == 3)
        {
            if (damage > Q12(45.0f) || temp_a1 == 1)
            {
                ret = 1;
            }
        }
        else
        {
            if (damage > Q12(20.0f) || temp_a1 == 1)
            {
                ret = 1;
            }
        }
    }

    return ret;
}

bool sharedFunc_800D2E04_0_s01(s_SubCharacter* airScreamer, VECTOR3* inVec, q19_12* outDist, q19_12* outAngle)
{
    u8     idxInfo;
    s32    idx;
    q19_12 angle1;
    q19_12 deltaX;
    q19_12 deltaZ;
    q19_12 dist0;
    q19_12 angle0;
    q19_12 angle;
    q19_12 dist;

    idxInfo = g_SysWork.field_2388.field_154.field_0.field_0.field_0;
    idx     = (idxInfo & (1 << 1)) ? ((idxInfo & (1 << 0)) ? 2 : 3) : (sharedFunc_800D4A80_0_s01(airScreamer) == 3);

    deltaX = inVec->vx - airScreamer->position_18.vx;
    deltaZ = inVec->vz - airScreamer->position_18.vz;

    dist0  = (u16)sharedData_800CAA98_0_s01.properties_D14[idx].val16[0];
    angle0 = (u16)sharedData_800CAA98_0_s01.properties_D14[idx].val16[1];

    angle = FP_ANGLE_NORM_S(ratan2(deltaX, deltaZ) - (airScreamer->rotation_24.vy + airScreamer->field_2A));
    dist  = SquareRoot12(FP_MULTIPLY_PRECISE(deltaX, deltaX, 12) + FP_MULTIPLY_PRECISE(deltaZ, deltaZ, 12));

    if (outDist != NULL)
    {
        *outDist = dist;
    }
    if (outAngle != NULL)
    {
        *outAngle = angle;
    }

    angle1 = angle + angle0;
    if (((u32)angle0 * 2) >= angle1 && dist0 >= dist)
    {
        sharedData_800DE170_0_s01.vx = airScreamer->position_18.vx;
        sharedData_800DE170_0_s01.vy = airScreamer->position_18.vy + airScreamer->field_C8.field_0; // Head offset.
        sharedData_800DE170_0_s01.vz = airScreamer->position_18.vz;
        return !func_8006D90C(&sharedData_800E2330_0_s01, &sharedData_800DE170_0_s01, inVec);
    }

    return false;
}

bool sharedFunc_800D2FB4_0_s01(s_SubCharacter* airScreamer, VECTOR3* playerPos, s32 playerField10C)
{
    q3_12  rotY;
    q19_12 offsetY;
    q19_12 offsetZ;
    s32    idx;
    q19_12 dist;
    q19_12 var_s1;
    u64    roughDist;

    if (airScreamer->properties_E4.player.flags_11C & (PlayerFlag_Unk19 | PlayerFlag_Unk20))
    {
        idx = 2;
    }
    else
    {
        // TODO: Does `ANIM_STATUS_IS_ACTIVE` fit?
        if ((airScreamer->model_0.anim_4.status_0 | 0x1) == 27 ||
            (airScreamer->model_0.anim_4.status_0 | 0x1) == 29)
        {
            idx = 0;
        }
        else
        {
            idx = 1;
        }
    }

    var_s1  = sharedData_800CAA98_0_s01.field_D24[0][idx][0];
    dist = sharedData_800CAA98_0_s01.field_D24[0][idx][1];

    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case GameDifficulty_Easy:
            break;

        case GameDifficulty_Normal:
            var_s1 += Q12(0.5f);
            break;

        case GameDifficulty_Hard:
            var_s1 += Q12(1.0f);
            break;
    }

    rotY    = airScreamer->rotation_24.vy;
    offsetY = playerPos->vx - (airScreamer->position_18.vx + FP_MULTIPLY_PRECISE(dist, Math_Sin(rotY), Q12_SHIFT));
    offsetZ = playerPos->vz - (airScreamer->position_18.vz + FP_MULTIPLY_PRECISE(dist, Math_Cos(rotY), Q12_SHIFT));

    roughDist = FP_SQUARE_PRECISE(offsetY, Q12_SHIFT) + FP_SQUARE_PRECISE(offsetZ, Q12_SHIFT);
    if (roughDist > FP_SQUARE_PRECISE(FP_MULTIPLY_PRECISE(var_s1, playerField10C, Q12_SHIFT), Q12_SHIFT))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool sharedFunc_800D31D0_0_s01(s_SubCharacter* airScreamer, VECTOR3* pos, s32 arg2)
{
    q3_12  offsetHeadingAngle;
    q19_12 offsetDist;
    q19_12 offsetX;
    q19_12 offsetZ;
    q19_12 var_s1;
    q51_12 roughDist;
    q52_12 distMax;
    s32    idx;

    idx        = sharedData_800CAA98_0_s01.field_D3C[airScreamerProps.field_E8_4][airScreamerProps.field_E8_8];
    var_s1     = sharedData_800CAA98_0_s01.field_D24[1][idx][0];
    offsetDist = sharedData_800CAA98_0_s01.field_D24[1][idx][1];

    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case GameDifficulty_Easy:
            break;

        case GameDifficulty_Normal:
            var_s1 += Q12(0.5f);
            break;

        case GameDifficulty_Hard:
            var_s1 += Q12(1.0f);
            break;
    }

    if (airScreamer->model_0.controlState_2 == AirScreamerControl_3 ||
        airScreamer->model_0.controlState_2 == AirScreamerControl_9)
    {
        var_s1 += Q12(1.0f);
    }

    offsetHeadingAngle = airScreamer->rotation_24.vy;
    offsetX            = pos->vx - (airScreamer->position_18.vx + FP_MULTIPLY_PRECISE(offsetDist, Math_Sin(offsetHeadingAngle), Q12_SHIFT));
    offsetZ            = pos->vz - (airScreamer->position_18.vz + FP_MULTIPLY_PRECISE(offsetDist, Math_Cos(offsetHeadingAngle), Q12_SHIFT));

    roughDist = FP_SQUARE_PRECISE(offsetX, Q12_SHIFT) + FP_SQUARE_PRECISE(offsetZ, Q12_SHIFT);
    distMax   = FP_SQUARE_PRECISE(var_s1, Q12_SHIFT);
    distMax   = FP_MULTIPLY_PRECISE(distMax, arg2, Q12_SHIFT);
    if (roughDist > distMax)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool sharedFunc_800D3430_0_s01(s_SubCharacter* airScreamer, q19_12* dist, q19_12* angle)
{
    bool cond;

    sharedData_800DE180_0_s01.vx = g_SysWork.playerWork_4C.player_0.position_18.vx;
    sharedData_800DE180_0_s01.vy = g_SysWork.playerWork_4C.player_0.position_18.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_0; // Head offset.
    sharedData_800DE180_0_s01.vz = g_SysWork.playerWork_4C.player_0.position_18.vz;

    cond = sharedFunc_800D2E04_0_s01(airScreamer, &sharedData_800DE180_0_s01, dist, angle);
    if (cond)
    {
        airScreamerProps.position_104 = sharedData_800DE180_0_s01;
    }

    if (dist != NULL)
    {
        *dist = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.position_104);
    }

    if (angle != NULL)
    {
        *angle = func_80080478(&airScreamer->position_18, &airScreamerProps.position_104);
    }

    return cond;
}

bool sharedFunc_800D3508_0_s01(s_SubCharacter* airScreamer, q19_12* dist)
{
    q19_12 angleToPlayer;
    q19_12 angleToPlayerCpy;
    q19_12 offsetDist;
    q19_12 offsetX;
    u32    offsetZ;
    bool   cond;
    // TODO: Fix messy local var reuse.

    #define playerProps      g_SysWork.playerWork_4C.player_0.properties_E4.player

    offsetDist = playerProps.field_10C << 8;
    if (dist != NULL)
    {
        *dist = offsetDist;
    }

    cond = sharedFunc_800D2FB4_0_s01(airScreamer, &g_SysWork.playerWork_4C.player_0.position_18, offsetDist);
    if (cond)
    {
        angleToPlayer    = Math_AngleBetweenPositionsGet(airScreamer->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        angleToPlayerCpy = angleToPlayer;

        offsetZ = g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0;
        if (!(offsetZ & 0x2))
        {
            // @hack Permuter find.
            offsetZ = 0;
            while (offsetZ) {};

            do
            {
                sharedFunc_800D4A80_0_s01(airScreamer);
            }
            while (false);
        }

        angleToPlayer = FP_MULTIPLY_PRECISE(offsetDist, Math_Sin(angleToPlayerCpy), Q12_SHIFT);
        offsetX = angleToPlayer;
        offsetZ = FP_MULTIPLY_PRECISE(offsetDist, Math_Cos(angleToPlayerCpy), Q12_SHIFT);

        airScreamerProps.position_104.vx = airScreamer->position_18.vx + offsetX;
        airScreamerProps.position_104.vy = g_SysWork.playerWork_4C.player_0.position_18.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_6;
        airScreamerProps.position_104.vz = airScreamer->position_18.vz + offsetZ;
    }

    return cond;

    #undef playerProps
}

bool sharedFunc_800D3630_0_s01(s_SubCharacter* airScreamer, q19_12* dist)
{
    bool   cond;
    q19_12 angleToPlayer;
    q19_12 offsetDist;
    q19_12 offsetX;
    q19_12 offsetZ;

    offsetDist = sharedFunc_800D3814_0_s01(airScreamer);
    if (dist != NULL)
    {
        *dist = offsetDist;
    }

    // Set target position for pecking?
    cond = sharedFunc_800D31D0_0_s01(airScreamer, &g_SysWork.playerWork_4C.player_0.position_18, offsetDist);
    if (cond)
    {
        // Compute extra offset distance.
        offsetDist = MAX(offsetDist, Q12(1.5f));

        // Compute extra offset.
        angleToPlayer = Math_AngleBetweenPositionsGet(airScreamer->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        offsetX = FP_MULTIPLY_PRECISE(offsetDist, Math_Sin(angleToPlayer), Q12_SHIFT);
        offsetZ = FP_MULTIPLY_PRECISE(offsetDist, Math_Cos(angleToPlayer), Q12_SHIFT);

        // Set target position slightly ahead of Air Screamer.
        airScreamerProps.position_104.vx = airScreamer->position_18.vx + offsetX;
        airScreamerProps.position_104.vy = g_SysWork.playerWork_4C.player_0.position_18.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_6;
        airScreamerProps.position_104.vz = airScreamer->position_18.vz + offsetZ;
    }

    return cond;
}

s32 sharedFunc_800D3758_0_s01(s_SubCharacter* airScreamer, q19_12* outDist, q19_12* outAngle, q19_12 dist, s32* arg4)
{
    s32  cond1;
    s32  cond0;
    bool cond;
    s32  flags;

    cond = sharedFunc_800D3430_0_s01(airScreamer, outDist, outAngle);
    if (cond)
    {
        sharedData_800DE190_0_s01 = airScreamerProps.position_104;
    }

    cond0 = sharedFunc_800D3630_0_s01(airScreamer, dist);
    cond1 = sharedFunc_800D3508_0_s01(airScreamer, arg4);

    if (cond)
    {
        airScreamerProps.position_104 = sharedData_800DE190_0_s01;
    }

    flags = (cond != false) * 4;
    if (cond0)
    {
        flags |= 1 << 1;
    }

    return flags | (cond1 != false);
}

s32 sharedFunc_800D3814_0_s01(s_SubCharacter* airScreamer)
{
    s32 headingAngleDelta;
    s32 invDist;
    s32 dist;
    s32 distProp8;
    s32 headingAngleTo;
    s32 headingAngleFrom;

    headingAngleTo = func_80080478(&g_SysWork.playerWork_4C.player_0.position_18, &airScreamer->position_18);
    headingAngleFrom = g_SysWork.playerWork_4C.player_0.rotation_24.vy;

    invDist = Q12(8.0f) - Math_Distance2dGet(&g_SysWork.playerWork_4C.player_0.position_18, &airScreamer->position_18);
    if (invDist < Q12(0.0f))
    {
        invDist = Q12(0.0f);
    }
    else
    {
        invDist = invDist >> 3;
    }

    headingAngleDelta = ABS_32(FP_ANGLE_NORM_S(headingAngleTo - headingAngleFrom));
    if (invDist >= headingAngleDelta)
    {
        dist = (invDist - headingAngleDelta) * 4;
    }
    else
    {
        dist = Q12(0.0f);
    }
    
    if (g_Player_IsAiming)
    {
        distProp8 = func_8007FD2C();
        if (distProp8 > Q12(2.0f))
        {
            dist += Q12(2.0f);
        }
        else
        {
            dist += distProp8;
        }

        if (airScreamer == &g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353])
        {
            dist += Q12(1.0f);
        }
    }
    else
    {
        dist += Q12(0.5f);
    }

    return dist;
}

bool sharedFunc_800D3928_0_s01(s_SubCharacter* airScreamer)
{
    q20_12 someTime;
    q19_12 deltaTime;
    void (*controlFunc)(s_SubCharacter*);

    deltaTime = g_DeltaTime0;
    if (deltaTime < Q12(0.0f))
    {
        deltaTime = Q12(0.0f);
    }

    someTime = airScreamerProps.timer_120;
    if (someTime < deltaTime)
    {
        airScreamerProps.timer_120 = Q12(0.0f);
    }
    else
    {
        airScreamerProps.timer_120 = someTime - deltaTime;
    }

    sharedData_800E21D0_0_s01.field_14C.flags = sharedFunc_800D3758_0_s01(airScreamer,
                                                                          &sharedData_800E21D0_0_s01.distance_150,
                                                                          &sharedData_800E21D0_0_s01.angle_154,
                                                                          &sharedData_800E21D0_0_s01.field_158,
                                                                          &sharedData_800E21D0_0_s01.field_15C);

    if (airScreamerProps.field_E8_0 == 3)
    {
        airScreamerProps.field_E8_8 = 0;
    }

    // Handle control state.
    controlFunc = g_Ai_AirScreamer_ControlFuncs[airScreamer->model_0.controlState_2];
    if (controlFunc)
    {
        controlFunc(airScreamer);
    }

    return true;
}

#if defined(MAP0_S01)
void func_800D39F4(s_SubCharacter* airScreamer) // 0x800D39F4
{
    q19_12 animTime;

    // TODO: `Character_AnimSet` doesn't match?
    airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(19, true);
    animTime = func_80044918(&airScreamer->model_0.anim_4)->startKeyframeIdx_C;
    airScreamer->model_0.stateStep_3 = 7;
    airScreamer->model_0.anim_4.keyframeIdx_8 = animTime;
    airScreamer->model_0.anim_4.time_4 = FP_TO(animTime, Q12_SHIFT);
}

void func_800D3A3C(s_SubCharacter* airScreamer) // 0x800D3A3C
{
    q19_12 animTime;
    s32    idx;

    idx = g_CharaAnimInfoIdxs[airScreamer->model_0.charaId_0];
    Ai_AirScreamer_Update(airScreamer, (&g_InitCharaDataAnimInfo[idx])->animFile1_8, (&g_InitCharaDataAnimInfo[idx])->npcCoords_14);

    airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(17, true);
    animTime = func_80044918(&airScreamer->model_0.anim_4)->startKeyframeIdx_C;
    airScreamer->model_0.stateStep_3 = 3;
    airScreamer->model_0.anim_4.keyframeIdx_8 = animTime;
    airScreamer->model_0.anim_4.time_4 = FP_TO(animTime, Q12_SHIFT);
}

void func_800D3AC0(s_SubCharacter* airScreamer)
{
    switch(airScreamer->model_0.stateStep_3)
    {
        case 1:
        case 3:
        case 5:
            airScreamer->model_0.stateStep_3++;
            break;

        default:
            break;
    }
}
#endif

void sharedSymbol_800D3B0C_0_s01(s_SubCharacter* airScreamer)
{
    s32 keyframeIdx;
    s32 var0;
    s32 var1;
    s32 var2;
    u32 controlState;
    u32 stateStep;
    s32 field40;
    u32 animStatus;

    field40 = airScreamer->field_40;
    switch (field40 % 0x3)
    {
        case 0:
        default:
            var2 = 0;
            break;

        case 1:
            var2 = 1;
            break;

        case 2:
            var2 = 2;
            break;
    }

    switch(field40 - (field40 / 2) * 2)
    {
        case 0:
        default:
            var1 = 1;
            break;

        case 1:
            var1 = 0;
            break;
    }

    stateStep = AirScreamerStateStep_0;
    switch (airScreamer->model_0.stateStep_3)
    {
#if defined(MAP0_S01)
        case AirScreamerStateStep_12:
        default:
            var0 = 4;
            var1 = 1;
            var2 = 3;
            animStatus = NO_VALUE;
            controlState = AirScreamerControl_1;
            break;

        case AirScreamerStateStep_13:
            animStatus = ANIM_STATUS(AirScreamerAnim_19, true);

            if (g_SavegamePtr->mapOverlayId_A4 == 1)
            {
                var0 = 2;
                var1 = 1;
                var2 = 2;
                animStatus = ANIM_STATUS(AirScreamerAnim_2, true);
                controlState = AirScreamerControl_46;
            }
            else
            {
                var0 = 2;

                if (airScreamer->model_0.anim_4.status_0 == ANIM_STATUS(AirScreamerAnim_19, true))
                {
                    animStatus = NO_VALUE;
                }

                controlState = AirScreamerControl_18;
            }
            break;
#else
        default:
            var0 = 1;
            animStatus = ANIM_STATUS(AirScreamerAnim_23, true);
            controlState = AirScreamerControl_3;
            break;

        case AirScreamerStateStep_0:
        case AirScreamerStateStep_2:
            var0 = 1;
            animStatus = ANIM_STATUS(AirScreamerAnim_25, true);
            controlState = AirScreamerControl_5;
            break;

        case AirScreamerStateStep_3:
            var0 = 1;
            animStatus = ANIM_STATUS(AirScreamerAnim_19, true);
            controlState = AirScreamerControl_19;
            break;

        case AirScreamerStateStep_4:
            var0 = 0;
            animStatus = ANIM_STATUS(AirScreamerAnim_25, true);
            controlState = AirScreamerControl_4;
            stateStep = AirScreamerStateStep_64;
            break;

        case AirScreamerStateStep_5:
            var0 = 0;
            animStatus = ANIM_STATUS(AirScreamerAnim_19, true);
            controlState = AirScreamerControl_18;
            stateStep = AirScreamerStateStep_64;
            break;

        case AirScreamerStateStep_6:
            var0 = 0;
            animStatus = ANIM_STATUS(AirScreamerAnim_17, true);
            var2 = 2;
            controlState = AirScreamerControl_33;
            stateStep = AirScreamerStateStep_64;
            break;

        case AirScreamerStateStep_8:
            var0 = 1;
            animStatus = ANIM_STATUS(AirScreamerAnim_14, true);
            var2 = 4;
            controlState = AirScreamerControl_9;
            break;

        case AirScreamerStateStep_9:
            var0 = 3;
            animStatus = ANIM_STATUS(AirScreamerAnim_19, true);;
            controlState = AirScreamerControl_19;
            var2 = 2;
            airScreamer->health_B0 *= 4;;
            break;

        case AirScreamerStateStep_11:
            var0 = 0;
            animStatus = ANIM_STATUS(AirScreamerAnim_17, true);
            controlState = AirScreamerControl_33;
            stateStep = AirScreamerStateStep_65;
            var2 = 2;
            break;

        case AirScreamerStateStep_7:
            var0 = 0;
            animStatus = ANIM_STATUS(AirScreamerAnim_17, true);
            controlState = AirScreamerControl_33;
            stateStep = AirScreamerStateStep_66;
            var2 = 2;
            break;

        case AirScreamerStateStep_10:
            var0 = 0;
            animStatus = ANIM_STATUS(AirScreamerAnim_17, true);
            controlState = AirScreamerControl_33;
            stateStep = AirScreamerStateStep_67;
            var2 = 2;
            airScreamer->health_B0 -= airScreamer->health_B0 >> 2;
            break;
#endif
    }

    airScreamer->model_0.controlState_2 = controlState;
    airScreamer->model_0.stateStep_3 = stateStep;
    airScreamerProps.flags_11C = AirScreamerFlag_None;
    airScreamerProps.field_E8_0 = var0;
    airScreamerProps.field_E8_4 = var1;
    airScreamerProps.field_E8_8 = var2;

    if (controlState == AirScreamerControl_1)
    {
        airScreamerProps.flags_11C = CharaUnk0Flag_Unk16;
    }

    if (animStatus != NO_VALUE && animStatus != airScreamer->model_0.anim_4.status_0)
    {
        airScreamer->model_0.anim_4.status_0      = animStatus;
        keyframeIdx                               = func_80044918(&airScreamer->model_0.anim_4)->startKeyframeIdx_C;
        airScreamer->model_0.anim_4.alpha_A       = Q12(0.0f);
        airScreamer->model_0.anim_4.keyframeIdx_8 = keyframeIdx;
        airScreamer->model_0.anim_4.time_4        = FP_TO(keyframeIdx, Q12_SHIFT);
    }
}

void sharedFunc_800D3CC4_0_s01(s_SubCharacter* airScreamer)
{
    u32  keyframeIdx;
    bool setAnim;

    sharedData_800E21D0_0_s01.flags_0 |= 1 << 31;
    setAnim                            = false;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            setAnim                              = true;
            airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_23, true);
            airScreamer->model_0.stateStep_3     = AirScreamerStateStep_1;

        case AirScreamerStateStep_1:
            airScreamerProps.flags_11C |= AirScreamerFlag_16;
            break;

        case AirScreamerStateStep_2:
            setAnim                              = true;
            airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_24, true);
            airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;

        case AirScreamerStateStep_3:
            airScreamerProps.flags_11C |= AirScreamerFlag_16;
            break;

        case AirScreamerStateStep_4:
            setAnim                              = true;
            airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, true);
            airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;

        case AirScreamerStateStep_5:
            airScreamerProps.flags_11C &= ~AirScreamerFlag_16;
            break;

        case AirScreamerStateStep_6:
            if (airScreamer->model_0.anim_4.status_0 == ANIM_STATUS(AirScreamerAnim_19, true))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
            }
            break;

        case AirScreamerStateStep_7:
            airScreamer->model_0.controlState_2 = AirScreamerControl_None;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_13;
            sharedSymbol_800D3B0C_0_s01(airScreamer);
            break;
    }

    Ai_AirScreamer_DamageTake(airScreamer, Q12(0.0f));

    if (setAnim)
    {
        keyframeIdx                               = func_80044918(&airScreamer->model_0.anim_4)->startKeyframeIdx_C;
        airScreamer->model_0.anim_4.keyframeIdx_8 = keyframeIdx;
        airScreamer->model_0.anim_4.time_4        = Q12(keyframeIdx);
    }
}

void sharedFunc_800D3DFC_0_s01(s_SubCharacter* airScreamer)
{
    s32 angle; // Maybe not angle.
    s32 flags;

    if (airScreamer->field_40 < 32)
    {
        flags = g_MapOverlayHeader.charaSpawns_24C[0][airScreamer->field_40].data.spawnInfo.flags_6;
        switch (flags)
        {
            case 1:
            case 8:
            case 9:
                angle = FP_ANGLE(0.0f);
                break;

            case 10:
                angle = FP_ANGLE(360.0f);
                break;

            case 2:
            case 3:
                angle = FP_ANGLE(108.0f);
                break;

            default:
                angle = FP_ANGLE(252.0f);
                break;
        }

        if (Rng_RandQ12() >= angle)
        {
            func_80037DC4(airScreamer);
        }
    }
}

#undef airScreamerProps
