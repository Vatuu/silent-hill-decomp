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
    Ai_AirScreamer_Control(airScreamer);
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
                func_8005DC1C(data->sfxVolumes_CE8[i].id_0, &airScreamer->position_18, data->sfxVolumes_CE8[i].volume_2.val8, 0);
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
    Ai_AirScreamerControl_0(airScreamer);
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
    q19_12 damage0;
    q19_12 damage1;
    s32    animStatus;
    s32    attack;
    u32    damageType;
    u8     temp_a1;
    q19_12 angle;

    damage0     = airScreamer->damage_B4.amount_C;
    animStatus = airScreamer->model_0.anim_4.status_0;
    attack     = airScreamer->attackReceived_41;
    damageType        = AirScreamerDamage_None;

    if (airScreamerProps.field_E8_0 == 3)
    {
        switch (attack)
        {
            case WEAPON_ATTACK(EquippedWeaponId_SteelPipe, AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Hammer,    AttackInputType_Tap):
                damage0 += damage0 / 2;
                break;

            case WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Shotgun,      AttackInputType_Tap):
                damage0 /= 2;
                break;

            default:
                break;
        }
    }

    if (airScreamer->health_B0 > Q12(0.0f))
    {
        if (animStatus == ANIM_STATUS(AirScreamerAnim_21, true))
        {
            damage1 = Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 10.0f);
            if (damage1 < airScreamer->health_B0)
            {
                airScreamer->health_B0 -= damage1;
            }
            else
            {
                airScreamer->health_B0 = Q12(0.0f);
            }
        }

        airScreamer->damage_B4.amount_C = Q12(0.0f);
        angle                     = mult; // @hack

        damage0 = Q12_MULT_PRECISE(damage0, angle);
        if (damage0 < airScreamer->health_B0)
        {
            airScreamer->health_B0 -= damage0;
        }
        else
        {
            airScreamer->health_B0 = Q12(0.0f);
        }
    }

    if (damage0 > Q12(0.0f) || airScreamer->health_B0 <= Q12(0.0f))
    {
        temp_a1 = D_800AD4C8[attack].field_10;
        angle   = FP_ANGLE_NORM_S(g_SysWork.playerWork_4C.player_0.rotation_24.vy - airScreamer->rotation_24.vy);

#ifdef MAP0_S01
        if (airScreamer->health_B0 <= Q12(0.0f))
#else
        if (airScreamer->health_B0 <= Q12(120.0f))
#endif
        {
            if (damage0 > Q12(5.0f))
            {
                damageType = AirScreamerDamage_4;
            }
            else
            {
                damageType = AirScreamerDamage_3;
            }
        }
        else if (airScreamerProps.field_E8_0 != 3 && temp_a1 == 2 && Math_CheckSignedRange(angle, FP_ANGLE(120.0f)))
        {
            damageType = AirScreamerDamage_2;
        }
        else if (airScreamerProps.field_E8_0 == 3)
        {
            if (damage0 > Q12(45.0f) || temp_a1 == 1)
            {
                damageType = AirScreamerDamage_1;
            }
        }
        else
        {
            if (damage0 > Q12(20.0f) || temp_a1 == 1)
            {
                damageType = AirScreamerDamage_1;
            }
        }
    }

    return damageType;
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

    if (airScreamerProps.flags_11C & (PlayerFlag_Unk19 | PlayerFlag_Unk20))
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
    offsetY = playerPos->vx - (airScreamer->position_18.vx + Q12_MULT_PRECISE(dist, Math_Sin(rotY)));
    offsetZ = playerPos->vz - (airScreamer->position_18.vz + Q12_MULT_PRECISE(dist, Math_Cos(rotY)));

    roughDist = FP_SQUARE_PRECISE(offsetY, Q12_SHIFT) + FP_SQUARE_PRECISE(offsetZ, Q12_SHIFT);
    if (roughDist > FP_SQUARE_PRECISE(Q12_MULT_PRECISE(var_s1, playerField10C), Q12_SHIFT))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool sharedFunc_800D31D0_0_s01(s_SubCharacter* airScreamer, const VECTOR3* pos, s32 arg2)
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
    offsetX            = pos->vx - (airScreamer->position_18.vx + Q12_MULT_PRECISE(offsetDist, Math_Sin(offsetHeadingAngle)));
    offsetZ            = pos->vz - (airScreamer->position_18.vz + Q12_MULT_PRECISE(offsetDist, Math_Cos(offsetHeadingAngle)));

    roughDist = FP_SQUARE_PRECISE(offsetX, Q12_SHIFT) + FP_SQUARE_PRECISE(offsetZ, Q12_SHIFT);
    distMax   = FP_SQUARE_PRECISE(var_s1, Q12_SHIFT);
    distMax   = Q12_MULT_PRECISE(distMax, arg2);
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

    #define playerProps g_SysWork.playerWork_4C.player_0.properties_E4.player

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

        angleToPlayer = Q12_MULT_PRECISE(offsetDist, Math_Sin(angleToPlayerCpy));
        offsetX = angleToPlayer;
        offsetZ = Q12_MULT_PRECISE(offsetDist, Math_Cos(angleToPlayerCpy));

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
        offsetX = Q12_MULT_PRECISE(offsetDist, Math_Sin(angleToPlayer));
        offsetZ = Q12_MULT_PRECISE(offsetDist, Math_Cos(angleToPlayer));

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

bool Ai_AirScreamer_Control(s_SubCharacter* airScreamer)
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
    airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_19, true);
    animTime = func_80044918(&airScreamer->model_0.anim_4)->startKeyframeIdx_C;
    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
    airScreamer->model_0.anim_4.keyframeIdx_8 = animTime;
    airScreamer->model_0.anim_4.time_4 = FP_TO(animTime, Q12_SHIFT);
}

void func_800D3A3C(s_SubCharacter* airScreamer) // 0x800D3A3C
{
    q19_12 animTime;
    s32    idx;

    idx = g_CharaAnimInfoIdxs[airScreamer->model_0.charaId_0];
    Ai_AirScreamer_Update(airScreamer, (&g_InitCharaDataAnimInfo[idx])->animFile1_8, (&g_InitCharaDataAnimInfo[idx])->npcCoords_14);

    airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_17, true);
    animTime = func_80044918(&airScreamer->model_0.anim_4)->startKeyframeIdx_C;
    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
    airScreamer->model_0.anim_4.keyframeIdx_8 = animTime;
    airScreamer->model_0.anim_4.time_4 = FP_TO(animTime, Q12_SHIFT);
}

void func_800D3AC0(s_SubCharacter* airScreamer) // 0x800D3AC0
{
    // Handle state step.
    switch(airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_1:
        case AirScreamerStateStep_3:
        case AirScreamerStateStep_5:
            airScreamer->model_0.stateStep_3++;
            break;

        default:
            break;
    }
}
#endif

void Ai_AirScreamerControl_0(s_SubCharacter* airScreamer)
{
    s32  keyframeIdx;
    s32  var0;
    bool var1;
    s32  var2;
    u32  controlState;
    u32  stateStep;
    s32  field40;
    u32  animStatus;

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
            var1 = true;
            break;

        case 1:
            var1 = false;
            break;
    }

    stateStep = AirScreamerStateStep_0;
    switch (airScreamer->model_0.stateStep_3)
    {
#if defined(MAP0_S01)
        case AirScreamerStateStep_12:
        default:
            var0 = 4;
            var1 = true;
            var2 = 3;
            animStatus = NO_VALUE;
            controlState = AirScreamerControl_1;
            break;

        case AirScreamerStateStep_13:
            animStatus = ANIM_STATUS(AirScreamerAnim_19, true);

            if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP0_S01)
            {
                var0 = 2;
                var1 = true;
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
            airScreamer->health_B0 -= airScreamer->health_B0 >> 2; // `/ 4`.
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
        airScreamerProps.flags_11C = AirScreamerFlag_16;
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

void Ai_AirScreamerControl_1(s_SubCharacter* airScreamer)
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
            Ai_AirScreamerControl_0(airScreamer);
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
    q19_12 chance;
    s32    flags;

    if (airScreamer->field_40 < 32)
    {
        flags = g_MapOverlayHeader.charaSpawns_24C[0][airScreamer->field_40].data.spawnInfo.flags_6;
        switch (flags)
        {
            case 1:
            case 8:
            case 9:
                chance = Q12(0.0f);
                break;

            case 10:
                chance = Q12(1.0f);
                break;

            case 2:
            case 3:
                chance = Q12(0.3f);
                break;

            default:
                chance = Q12(0.7f);
                break;
        }

        if (Rng_RandQ12() >= chance)
        {
            func_80037DC4(airScreamer);
        }
    }
}

void Ai_AirScreamerControl_2(s_SubCharacter* airScreamer)
{
    q19_12 damage;
    bool   cond1;
    bool   isBelowGround;
    bool   temp_s3;
    u32    animStatus;
    s32    animStatus12;
    bool   activeAnimStatus;

    animStatus   = airScreamer->model_0.anim_4.status_0;
    animStatus12 = ANIM_STATUS(AirScreamerAnim_12, true);

    sharedFunc_800D5638_0_s01(airScreamer);

    activeAnimStatus = ANIM_STATUS(ANIM_STATUS_IDX_GET(animStatus), true);

    // Handle state step.
    switch ((u32)airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            temp_s3       = sharedFunc_800D5F00_0_s01(airScreamer);
            isBelowGround = false;
            cond1         = airScreamer->position_18.vy >= Q12(8.0f);

            if (func_800808AC(airScreamer->position_18.vx, airScreamer->position_18.vz) == 7)
            {
                isBelowGround = airScreamer->position_18.vy >= Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz);
            }

            if (cond1)
            {
                Ai_AirScreamer_DamageTake(airScreamer, Q12(0.0f));

                airScreamer->position_18.vx = g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(100.0f);
                airScreamer->position_18.vz = g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(100.0f);

                sharedFunc_800D3DFC_0_s01(airScreamer);
                break;
            }

            if (isBelowGround)
            {
                Ai_AirScreamer_DamageTake(airScreamer, Q12(0.0f));
                sharedFunc_800D2364_0_s01(airScreamer);

                airScreamer->position_18.vx = g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(100.0f);
                airScreamer->position_18.vz = g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(100.0f);

                sharedFunc_800D3DFC_0_s01(airScreamer);
                break;
            }

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                Ai_AirScreamer_DamageTake(airScreamer, Q12(0.0f));

                if (animStatus == ANIM_STATUS(AirScreamerAnim_26, true) && temp_s3 == true)
                {
                    airScreamer->health_B0 = NO_VALUE;

                    func_800622B8(3, airScreamer, ANIM_STATUS(AirScreamerAnim_4, true), 2);

                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;

                    sharedFunc_800D3DFC_0_s01(airScreamer);
                    break;
                }
            }
            else
            {
                airScreamer->flags_3E |= CharaFlag_Unk2;

                if (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)) == AirScreamerDamage_4)
                {
                    if (airScreamer->health_B0 <= Q12(0.0f))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_5, false);
                        airScreamerProps.flags_11C          |= PlayerFlag_Unk6;
                        break;
                    }

                    airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_12, false);
                    airScreamer->model_0.stateStep_3     = AirScreamerStateStep_2;
                    airScreamerProps.flags_11C          |= PlayerFlag_WallStopRight;
                    break;
                }
#ifdef MAP0_S01
                damage = g_DeltaTime0 * 10;
                if (damage < airScreamer->health_B0)
                {
                    airScreamer->health_B0 -= damage;
                }
                else if (airScreamer->health_B0 > Q12(0.0f))
                {
                    airScreamer->health_B0 = Q12(0.0f);
                }
#endif
            }
            break;

        case AirScreamerStateStep_1:
            Ai_AirScreamer_DamageTake(airScreamer, Q12(0.0f));
            break;

        case AirScreamerStateStep_2:
            Ai_AirScreamer_DamageTake(airScreamer, Q12(0.5f));

            if (activeAnimStatus != animStatus12)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;
    }
}

void Ai_AirScreamerControl_3(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    bool cond;

    if (airScreamer->model_0.stateStep_3 == AirScreamerStateStep_0)
    {
        sharedFunc_800DDF74_2_s00(airScreamer, Q12(0.1f), airScreamer->rotation_24.vy);
        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
    }

    sharedFunc_800DF2D0_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            if (sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2)
            {
                if (!airScreamerProps.field_E8_8)
                {
                    cond = sharedFunc_800D3814_0_s01(airScreamer) >= Q12(2.0f);
                }
                else
                {
                    cond = true;
                }

                if (cond)
                {
                    airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    airScreamer->flags_3E              |= CharaFlag_Unk3;
                    airScreamerProps.flags_11C         |= AirScreamerFlag_4;
                }
            }
            else
            {
                if (airScreamerProps.flags_11C & AirScreamerFlag_31)
                {
                    airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                }
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}
// Similar to `Ai_AirScreamerControl_5`
void Ai_AirScreamerControl_4(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    temp_fp;
    q19_12 distToTarget;
    s32    temp_s1_2;
    bool   temp_s5;
    bool   temp_s6;
    bool   temp_s7;
    s32    temp_v0;
    s32    var_s3;
    bool   cond;
    bool   var_v0_2;
    s32    animStatus;
    bool   new_var;

    animStatus = airScreamer->model_0.anim_4.status_0;
    var_s3     = 0;
    cond       = false;
    temp_fp    = sharedFunc_800D4A80_0_s01(airScreamer);

    var_v0_2 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var  = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    temp_s6  = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;

    temp_s5 = var_v0_2;
    temp_s7 = new_var;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_64:
            sharedFunc_800DD4A4_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case AirScreamerStateStep_0:
            sharedFunc_800DDF74_2_s00(airScreamer, Q12(4.0f), airScreamer->rotation_24.vy);
            sharedFunc_800DE034_2_s00(airScreamer, &airScreamerProps.targetPosition_F8, Q12(3.0f));
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case AirScreamerStateStep_1:
            cond                             = true;
            airScreamerProps.timer_120       = Q12(8.0f);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;

        case AirScreamerStateStep_2:
            distToTarget = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            temp_s1_2    = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);
            temp_v0      = sharedFunc_800DC598_2_s00(airScreamer);

            if (temp_v0 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            else if (temp_v0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            else if ((distToTarget < Q12(1.0f) && (temp_s1_2 > -57 && temp_s1_2 < 57)) ||
                     airScreamerProps.flags_11C < 0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else if (cond)
            {
                if (sharedFunc_800DC200_2_s00(airScreamer) && distToTarget > Q12(6.0f))
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
                }
                else if (sharedFunc_800DC30C_2_s00(airScreamer))
                {
                    if (distToTarget >= Q12(1.5f) || Rng_RandQ12() >= Q12(0.5f))
                    {
                        // @hack This check should be `if (diff >= Q12(-1.0f) && diff < Q12(1.0f))`,
                        // but that results in `sltiu 0x2000` instead of the `li 0x2000/sltu` needed.
                        if (Math_CheckSignedRange(airScreamerProps.targetPosition_F8.vy - airScreamer->position_18.vy, Q12(1.0f)))
                        {
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                        }
                    }
                    else
                    {
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                    }
                }
            }
            break;

        case AirScreamerStateStep_3:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_25, true) || animStatus == ANIM_STATUS(AirScreamerAnim_23, true))
            {
                var_s3                               = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_22, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_4:
            var_s3 = 1;
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_25, true) || animStatus == ANIM_STATUS(AirScreamerAnim_23, true))
            {
                var_s3                               = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_24, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_6;
            }
            break;

        case AirScreamerStateStep_6:
            var_s3 = 2;
            break;
    }

    sharedFunc_800DF448_2_s00(airScreamer, false);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            switch (var_s3)
            {
                case 0:
                    if (temp_s5 | temp_s6 | temp_s7)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (temp_fp == 2)
                    {
                        if (temp_s5 | temp_s6 | temp_s7)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_18;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (temp_fp == 3)
                    {
                        if (temp_s5 | temp_s6 | temp_s7)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_35;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_33;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_5(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    animStatus;
    bool   field14C_0;
    bool   field14C_1;
    bool   field14C_2;
    bool   new_var1;
    bool   new_var2;
    bool   new_var3;
    s32    switchCond;
    bool   cond;
    s32    temp_fp;
    s32    new_var;
    q19_12 angleFieldF8;
    q19_12 distFieldF8;
    s32    temp_v0;

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;
    cond       = false;

    new_var    = sharedFunc_800D4A80_0_s01(airScreamer);
    new_var1   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    new_var2   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var3   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    temp_fp    = new_var;
    field14C_0 = new_var1;
    field14C_1 = new_var2;
    field14C_2 = new_var3;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            sharedFunc_800DDE14_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case AirScreamerStateStep_1:
            cond                             = true;
            airScreamerProps.timer_120       = Q12(6.0f);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;

        case AirScreamerStateStep_2:
            distFieldF8  = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            angleFieldF8 = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);

            temp_v0 = sharedFunc_800DC598_2_s00(airScreamer);
            if (temp_v0 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            else if (temp_v0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            else if ((distFieldF8 < Q12(0.5f) && (angleFieldF8 >= FP_ANGLE(-5.0f) && angleFieldF8 <= FP_ANGLE(5.0f))) ||
                     (airScreamerProps.flags_11C & AirScreamerFlag_31))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else if (cond)
            {
                if (sharedFunc_800DC200_2_s00(airScreamer) && distFieldF8 > Q12(6.0f))
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
                }
                else if (sharedFunc_800DC30C_2_s00(airScreamer))
                {
                    // @hack This check should be `if (diff >= Q12(-1.0f) && diff < Q12(1.0f))`,
                    // but that results in `sltiu 0x2000` instead of the `li 0x2000/sltu` needed.
                    if (Math_CheckSignedRange(airScreamerProps.targetPosition_F8.vy - airScreamer->position_18.vy, Q12(1.0f)))
                    {
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                    }
                }
            }
            break;

        case AirScreamerStateStep_3:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                switchCond                           = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(22, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_4:
            switchCond = 1;
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(24, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_6;
            }
            break;

        case AirScreamerStateStep_6:
            switchCond = 2;
            break;
    }

    sharedFunc_800DF448_2_s00(airScreamer, false);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (field14C_1 | field14C_0 | field14C_2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (temp_fp == 2)
                    {
                        if (field14C_1 | field14C_0 | field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_19;
                        }
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (temp_fp == 3)
                    {
                        if (field14C_1 | field14C_0 | field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_35;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_34;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

// Note: Very close match to `Ai_AirScreamerControl_7` other than some checks being removed.
// Changes here should be copied over there.

void Ai_AirScreamerControl_6(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32  animStatus;
    s32  switchCond;
    bool cond;
    s32  temp_fp;
    s32  temp_fp_tmp;
    s32  field15C;
    bool field14C_0;
    bool field14C_1;
    bool field14C_2;
    bool field14C_0_tmp;
    bool field14C_1_tmp;
    bool field14C_2_tmp;

    animStatus     = airScreamer->model_0.anim_4.status_0;
    switchCond     = 0;
    cond           = false;
    temp_fp_tmp    = sharedFunc_800D4A80_0_s01(airScreamer);
    field15C       = sharedData_800E21D0_0_s01.field_15C;
    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    temp_fp        = temp_fp_tmp;
    field14C_0     = field14C_0_tmp;
    field14C_1     = field14C_1_tmp;
    field14C_2     = field14C_2_tmp;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            airScreamerProps.timer_120 = Q12(6.0f);

        case AirScreamerStateStep_1:
            sharedFunc_800DE034_2_s00(airScreamer, &airScreamerProps.position_104, Q12(1.5f));

            if (!sharedFunc_800DC30C_2_s00(airScreamer))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (Rng_RandQ12() >= Q12(0.3f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_2:
            cond = true;

        case AirScreamerStateStep_3:
            if (sharedFunc_800DC598_2_s00(airScreamer))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
                break;
            }

            if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(1.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                if (cond)
                {
                    switchCond = 1;
                }

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (field14C_0 || field14C_1 || field14C_2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;

                switchCond = 0;

                if (field15C > 32)
                {
                    s32 var_v0 = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.position_104) - airScreamer->rotation_24.vy);
                    sharedFunc_800DDF74_2_s00(airScreamer, Q12(1.5f), (var_v0 / 4) + airScreamer->rotation_24.vy);
                    airScreamerProps.timer_120 = Q12(6.0f);
                }
            }
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_25, true) ||
                animStatus == ANIM_STATUS(AirScreamerAnim_23, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_22, false);

                if (field14C_2 || field14C_1)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_6;
                }
            }
            else if (field14C_2 || field14C_1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_25, true) ||
                animStatus == ANIM_STATUS(AirScreamerAnim_23, true))
            {
                switchCond                           = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_22, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_7;
            }
            break;

        case AirScreamerStateStep_6:
            if (field14C_2 || field14C_1)
            {
                switchCond                       = 3;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
            }
            else
            {
                switchCond = 2;
            }
            break;

        case AirScreamerStateStep_7:
            switchCond = 3;
            break;
    }

    sharedFunc_800DF448_2_s00(airScreamer, false);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                case 1:
                    if (field14C_2 || field14C_1)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    else if (switchCond == 1 && Rng_TestProbability(Q12(0.5f)))
                    {
                        s32 randVal = Rng_RandQ12();
                        s32 var_a0  = Q12(0.0f);

                        if (airScreamerProps.field_E8_8 == 1)
                        {
                            var_a0 = Q12(0.1f);
                        }

                        if (randVal < Q12(0.7f) - (var_a0 * 2))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_15;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    break;

                case 2:
                    if (temp_fp == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 3:
                    if (temp_fp == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            if (airScreamer->health_B0 <= 0)
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

// Note: Very close match to `Ai_AirScreamerControl_6` other than some checks being removed.
// Changes here should be copied over there.
void Ai_AirScreamerControl_7(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32  animStatus;
    s32  switchCond;
    bool var_s5;
    s32  temp_fp;
    s32  temp_fp_tmp;
    s32  field15C;
    bool field14C_0;
    bool field14C_1;
    bool field14C_2;
    bool field14C_0_tmp;
    bool field14C_1_tmp;
    bool field14C_2_tmp;

    animStatus     = airScreamer->model_0.anim_4.status_0;
    switchCond     = 0;
    var_s5         = false;
    temp_fp_tmp    = sharedFunc_800D4A80_0_s01(airScreamer);
    field15C       = sharedData_800E21D0_0_s01.field_15C;
    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_0     = field14C_0_tmp;
    field14C_1     = field14C_1_tmp;
    temp_fp        = temp_fp_tmp;
    field14C_2     = field14C_2_tmp;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            airScreamerProps.timer_120 = Q12(6.0f);

        case AirScreamerStateStep_1:
            sharedFunc_800DE034_2_s00(airScreamer, &airScreamerProps.position_104, Q12(2.0f));

            if (!sharedFunc_800DC30C_2_s00(airScreamer))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (Rng_RandQ12() >= Q12(0.5f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_2:
            var_s5 = true;

        case AirScreamerStateStep_3:
            if (sharedFunc_800DC598_2_s00(airScreamer))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
                break;
            }

            if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(1.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                if (var_s5)
                {
                    switchCond = 1;
                }

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (field14C_2 || field14C_0 || field14C_1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;

                if (field15C > 32)
                {
                    s32 var_v0 = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.position_104) - airScreamer->rotation_24.vy);
                    sharedFunc_800DDF74_2_s00(airScreamer, Q12(1.5f), (var_v0 / 4) + airScreamer->rotation_24.vy);
                    airScreamerProps.timer_120 = Q12(6.0f);
                }
            }
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_25, true) || animStatus == ANIM_STATUS(AirScreamerAnim_23, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_22, false);

                if (field14C_1 || field14C_0)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_6;
                }
            }
            else if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_25, true) || animStatus == ANIM_STATUS(AirScreamerAnim_23, true))
            {
                switchCond                           = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_22, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_7;
            }
            break;

        case AirScreamerStateStep_6:
            if (field14C_2 || field14C_1 || field14C_0)
            {
                switchCond                       = 3;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
            }
            else
            {
                switchCond = 2;
            }
            break;

        case AirScreamerStateStep_7:
            switchCond = 3;
            break;
    }

    sharedFunc_800DF448_2_s00(airScreamer, false);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            switch (switchCond)
            {
                case 0:
                case 1:
                    if (field14C_2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_8;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    else if (switchCond == 1)
                    {
                        s32 randVal = Rng_RandQ12();

                        s32 var_a0 = Q12(0.0f);
                        if (airScreamerProps.field_E8_8 == 1)
                        {
                            var_a0 = Q12(0.1f);
                        }

                        if (randVal < Q12(0.7f) - (var_a0 * 2))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    break;

                case 2:
                    if (temp_fp == 2)
                    {
                        if (!field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_22;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 3:
                    if (temp_fp == 2)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_22;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_8(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    animStatus;
    s32    switchCond1;
    q19_12 var_s7;
    s32    sp10;
    q19_12 unkDist;
    q19_12 unkAngle;
    bool   field14C_2;
    s32    temp_s3;
    s32    switchCond0;
    s32    chance0;
    s32    chance1;

    animStatus  = airScreamer->model_0.anim_4.status_0;
    switchCond1 = 0;
    var_s7      = Q12(0.0f);
    sp10        = sharedFunc_800D4A80_0_s01(airScreamer);
    unkDist     = sharedData_800E21D0_0_s01.distance_150;
    unkAngle    = sharedData_800E21D0_0_s01.angle_154;
    field14C_2  = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;

    if (airScreamerProps.field_E8_4)
    {
        var_s7 = Q12(0.1f);
    }

    temp_s3     = sharedFunc_800DC598_2_s00(airScreamer);
    switchCond0 = 0;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            switchCond1                = 1;
            airScreamerProps.timer_120 = Q12(2.0f);
            airScreamer->flags_3E     |= CharaFlag_Unk3;

        case AirScreamerStateStep_1:
            sharedFunc_800DDF74_2_s00(airScreamer, unkDist / 2, unkAngle);

            if (!sharedFunc_800DC30C_2_s00(airScreamer) || Rng_RandQ12() >= Q12(0.3f))
            {
                if (Rng_TestProbability(Q12(0.2f) + (var_s7 * 2)))
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                }
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_2:
            switchCond0 = 1;

            if (temp_s3 != 0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (airScreamerProps.timer_120 != Q12(0.0f))
            {
                if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(1.0f))
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
                }
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case AirScreamerStateStep_3:
            sharedFunc_800DDF74_2_s00(airScreamer, unkDist / 2, unkAngle);

#define angleDiff FP_ANGLE_NORM_S(unkAngle - airScreamer->rotation_24.vy)

            if (temp_s3 != 0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (angleDiff >= FP_ANGLE(-10.0f) && angleDiff < FP_ANGLE(10.0f))
            {
                switchCond0 = 2;
            }
            break;

#undef angleDiff

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_25, true) ||
                animStatus == ANIM_STATUS(AirScreamerAnim_23, true))
            {
                switchCond1                          = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_22, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            switchCond1 = 2;
            break;
    }

    switch (switchCond0)
    {
        case 1:
            sharedFunc_800DF448_2_s00(airScreamer, false);
            break;

        case 2:
            sharedFunc_800DF2D0_2_s00(airScreamer);
            break;

        default:
            sharedFunc_800DF60C_2_s00(airScreamer);
            break;
    }

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            switch (switchCond1)
            {
                case 0:
                    if (field14C_2 == 0)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    chance0 = sharedFunc_800DC894_2_s00(airScreamer, unkDist);
                    chance1 = sharedFunc_800DC6E4_2_s00(airScreamer, unkDist);

                    if (Rng_TestProbability(chance0))
                    {
                        if (airScreamerProps.field_E8_0 == 3)
                        {
                            sharedFunc_800DD13C_2_s00(airScreamer, airScreamer->field_40 + 1, Q12(0.6f));
                        }

                        airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        airScreamerProps.flags_11C         |= AirScreamerFlag_4;
                    }
                    else if (Rng_TestProbability(chance1))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_14;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        airScreamerProps.flags_11C         |= AirScreamerFlag_4;
                    }
                    break;

                case 2:
                    if (sp10 == switchCond1)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_22;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_9(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    bool cond0;
    bool cond1;
    u32  temp_v1;
    s32  animStatus;

    cond0      = false;
    animStatus = airScreamer->model_0.anim_4.status_0;

    // Handle state step.
    switch ((u32)airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            sharedFunc_800DDF74_2_s00(airScreamer, Q12(0.1f), airScreamer->rotation_24.vy);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
            airScreamerProps.timer_120       = Q12(56.0f);
            break;

        case AirScreamerStateStep_1:
        case AirScreamerStateStep_2:
        case AirScreamerStateStep_3:
        case AirScreamerStateStep_4:
        case AirScreamerStateStep_5:
        case AirScreamerStateStep_6:
        case AirScreamerStateStep_7:
            if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                cond0 = true;
            }
            else if ((((u32)airScreamer->model_0.stateStep_3 - 1) * Q12(8.0f)) >= airScreamerProps.timer_120 &&
                     animStatus == ANIM_STATUS(14, true))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(13, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_8;
                airScreamerProps.flags_11C          |= AirScreamerFlag_2;
            }
            break;

        case AirScreamerStateStep_8:
            airScreamerProps.timer_120 += g_DeltaTime0;

            if (animStatus == ANIM_STATUS(14, true))
            {
                temp_v1 = Rng_RandQ12() * 12;
                if (temp_v1 < airScreamerProps.timer_120)
                {
                    airScreamerProps.timer_120 -= temp_v1;
                }
                else
                {
                    airScreamerProps.timer_120 = 0;
                }

                airScreamer->model_0.stateStep_3 = ((u32)airScreamerProps.timer_120 / Q12(8.0f)) + 1;
            }
            break;
    }

    sharedFunc_800DF2D0_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (cond0)
            {
                case 0:
                    if (ANIM_STATUS_IS_ACTIVE(animStatus))
                    {
                        if (sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2)
                        {
                            if (!airScreamerProps.field_E8_8)
                            {
                                cond1 = sharedFunc_800D3814_0_s01(airScreamer) >= Q12(2.0f);
                            }
                            else
                            {
                                cond1 = true;
                            }

                            if (cond1)
                            {
                                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                                airScreamer->model_0.controlState_2  = AirScreamerControl_10;
                                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_0;
                                airScreamer->flags_3E               |= CharaFlag_Unk3;
                                airScreamerProps.flags_11C          |= AirScreamerFlag_4;
                                airScreamerProps.field_E8_8          = 3;
                            }
                        }
                        else if (airScreamerProps.flags_11C & AirScreamerFlag_31 ||
                                 sharedData_800E21D0_0_s01.field_14C.bits.field_14C_1 ||
                                 sharedData_800E21D0_0_s01.field_15C > Q12(10.0f))
                        {
                            airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                            airScreamer->model_0.controlState_2  = AirScreamerControl_7;
                            airScreamer->model_0.stateStep_3     = AirScreamerStateStep_0;
                            airScreamerProps.field_E8_8          = 3;
                        }
                    }
                    break;

                case 1:
                    airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    airScreamer->model_0.controlState_2  = AirScreamerControl_15;
                    airScreamer->model_0.stateStep_3     = AirScreamerStateStep_0;
                    sharedFunc_800D3DFC_0_s01(airScreamer);
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            return;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_10(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    animStatus;
    s32    sp14;
    s32    sp18;
    s32    temp_s3_2;
    s32    temp_s7;
    s32    temp_fp;
    q19_12 unkDist;
    s32    temp_s1_2;
    s32    temp_s1_3;
    s32    temp_s4_2;
    s32    temp_s5;
    s32    temp_s6;
    s32    switchCond;
    bool   new_var;

    animStatus = airScreamer->model_0.anim_4.status_0;
    sp14       = sharedFunc_800D4A80_0_s01(airScreamer);
    new_var    = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    sp18       = new_var;
    unkDist    = sharedData_800E21D0_0_s01.distance_150;

    sharedFunc_800DE11C_2_s00(airScreamer);
    switchCond = 0;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            temp_s5 = unkDist + (Rng_RandQ12() * 4);

            if (sharedFunc_800DC200_2_s00(airScreamer) && temp_s5 > Q12(8.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (!sharedFunc_800DC30C_2_s00(airScreamer) || temp_s5 <= Q12(4.0f) && Rng_RandQ12() >= Q12(0.5f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }

            airScreamerProps.timer_120 = Q12(4.0f);
            break;

        case AirScreamerStateStep_1:

            temp_s1_2 = sharedFunc_800DC598_2_s00(airScreamer);
            temp_s5   = Q12(0.6f);
            temp_fp   = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);

            if (temp_s1_2 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (temp_s1_2 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (temp_fp < Q12(1.1f))
            {
                temp_s6   = airScreamer->position_18.vy + airScreamer->field_C8.field_0 + Q12(0.1f);
                temp_s1_3 = g_SysWork.playerWork_4C.player_0.position_18.vy;
                temp_s3_2 = g_SysWork.playerWork_4C.player_0.field_C8.field_4;
                temp_s7   = g_SysWork.playerWork_4C.player_0.field_C8.field_0;

                temp_s4_2 = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);

                if (sharedFunc_800DC30C_2_s00(airScreamer))
                {
                    if ((temp_s1_3 + temp_s3_2) < temp_s6 || temp_s6 < (temp_s1_3 + temp_s7))
                    {
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                        break;
                    }
                }

                if (temp_fp < temp_s5)
                {
                    if (temp_s4_2 > -0x101 && temp_s4_2 < 0x100)
                    {
                        switchCond = 1;
                    }
                }
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_23, true) ||
                animStatus == ANIM_STATUS(AirScreamerAnim_25, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_22, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;
            }
            break;

        case AirScreamerStateStep_3:
            switchCond = 2;
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_23, true) ||
                animStatus == ANIM_STATUS(AirScreamerAnim_25, true))
            {
                switchCond                           = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_24, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            switchCond = 3;
            break;
    }

    sharedFunc_800DF448_2_s00(airScreamer, 1);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (!sharedFunc_800DC67C_2_s00(airScreamer))
                    {
                        if (sp18 == 0)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_13;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_14;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    // TODO: Likely some kind of `CharaHasFlag` inline?
                    if (!((&g_SysWork.playerWork_4C.player_0)->flags_3E & CharaFlag_Unk4) &&
                        g_SysWork.npcIdxs_2354[0] == NO_VALUE &&
                        g_SysWork.npcIdxs_2354[1] == NO_VALUE)
                    {
                        if (animStatus == ANIM_STATUS(AirScreamerAnim_25, true) ||
                            animStatus == ANIM_STATUS(AirScreamerAnim_23, true))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_12;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_11;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (sp14 == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 3:
                    if (sp14 == 3)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_38;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_11(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32 bit3;
    s32 f150;
    s32 idx;
    s32 switch2Idx;
    u32 stateStep;
    s32 animStatus;
    s16 stateStep1;

    animStatus = airScreamer->model_0.anim_4.status_0;
    idx        = sharedFunc_800D4A80_0_s01(airScreamer);
    switch2Idx = 0;

    bit3       = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    stateStep  = airScreamer->model_0.stateStep_3;
    f150       = sharedData_800E21D0_0_s01.distance_150;
    stateStep1 = AirScreamerStateStep_1;

    // Handle state step.
    switch (stateStep)
    {
        case AirScreamerStateStep_0:
            if (!sharedFunc_800DC30C_2_s00(airScreamer) || Rng_RandQ12() >= FP_ANGLE(252.0f))
            {
                airScreamer->properties_E4.dummy.properties_E8[0xE].val32 = Q12(2.0f);
                airScreamer->model_0.stateStep_3                          = stateStep1;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            break;

        case AirScreamerStateStep_1:
            if (sharedFunc_800DC598_2_s00(airScreamer))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                switch2Idx                           = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(22, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;
            }
            break;

        case 3:
            switch2Idx = 1;
            break;
    }

    sharedFunc_800DE1F8_2_s00(airScreamer);
    sharedFunc_800DF710_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switch2Idx)
            {
                case 0:
                    if (airScreamer->properties_E4.dummy.properties_E8[0xE].val32 == 0 || f150 > 0x2000)
                    {
                        if (bit3 == 0)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_13;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (idx == 2)
                    {
                        if (bit3 != 0)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_24;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_26;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                default:
                    return;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2          = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3             = AirScreamerStateStep_0;
            airScreamer->properties_E4.player.flags_11C |= AirScreamerFlag_3;
            return;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamer->properties_E4.player.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamer->properties_E4.player.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_12(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    bool cond0;
    bool cond1;
    s32  animStatus;

    cond0      = false;
    cond1      = false;
    animStatus = airScreamer->model_0.anim_4.status_0;

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;

        case 1:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(1, false);
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(1, true) && airScreamer->model_0.anim_4.keyframeIdx_8 < 8192)
            {
                airScreamer->model_0.stateStep_3             = AirScreamerStateStep_3;
                airScreamer->properties_E4.player.flags_11C |= PlayerFlag_Unk5;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                cond0 = true;
            }
            else if (airScreamer->field_44.field_8 == NO_VALUE)
            {
                cond0                            = true;
                cond1                            = true;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                cond0 = true;
                cond1 = true;
            }
            break;
    }

    sharedFunc_800DF358_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.2f)))
    {
        case 0:
            if (cond0)
            {
                if (airScreamerProps.field_E8_8 == 3)
                {
                    airScreamerProps.field_E8_8 = 2;

                    if (cond1 && Rng_TestProbability(Q12(0.5f)))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_11;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                    }
                }
                else
                {
                    if (cond1)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_11;
                    }
                    else if (Rng_TestProbability(Q12(0.5f)))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_11;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                    }
                }

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2          = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3             = AirScreamerStateStep_0;
            airScreamer->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamer->properties_E4.player.flags_11C |= PlayerFlag_Unk6;
            }
            else
            {
                airScreamer->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_13(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    bool field14C_2;
    bool field14C_1;
    bool new_var2;
    bool new_var3;
    s32  switchCond;
    s32  animStatus;
    s32  temp_s4;
    s32  new_var;

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;
    new_var    = sharedFunc_800D4A80_0_s01(airScreamer);
    new_var3   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var2   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_1 = new_var3;
    temp_s4    = new_var;
    field14C_2 = new_var2;

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            sharedFunc_800DE1F8_2_s00(airScreamer);

        case 1:
            airScreamerProps.timer_120 = Q12(4.0f);
            if (sharedFunc_800DC30C_2_s00(airScreamer) && Rng_TestProbability(Q12(0.4f)))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            break;

        case 2:
            if (sharedFunc_800DC598_2_s00(airScreamer))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                break;
            }

            if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(0.5f))
            {
                sharedFunc_800DE034_2_s00(airScreamer, &airScreamerProps.position_104, Q12(2.0f));
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                sharedFunc_800DE034_2_s00(airScreamer, &airScreamerProps.position_104, Q12(2.0f));
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                switchCond                           = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(22, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_4;
            }
            break;

        case 4:
            switchCond = 1;
            break;
    }

    sharedFunc_800DF448_2_s00(airScreamer, false);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (!sharedFunc_800DC67C_2_s00(airScreamer))
                    {
                        if (field14C_2 == 0)
                        {
                            if (airScreamerProps.timer_120 == Q12(0.0f) && !field14C_1 && Rng_TestProbability(Q12(0.5f)))
                            {
                                airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                                airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                            }
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_14;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (temp_s4 == 2)
                    {
                        if (field14C_2 != 0)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_26;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_14(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    animStatus;
    s32    switchCond;
    s32    temp_s7;
    s32    temp_s7_tmp;
    q19_12 dist;
    q19_12 angle;
    bool   field14C_2;
    bool   field14C_2_tmp;
    q19_12 val2_0 = Q12(2.0f); // @hack Used to fix register order, couldn't find how to remove this yet.
    q19_12 distFieldF8;
    s32    var_s6;             // Possibly `bool`.
    q19_12 angleDelta;
    s32    temp_v0;

    animStatus     = airScreamer->model_0.anim_4.status_0;
    switchCond     = 0;
    temp_s7_tmp    = sharedFunc_800D4A80_0_s01(airScreamer);
    dist           = sharedData_800E21D0_0_s01.distance_150;
    angle          = sharedData_800E21D0_0_s01.angle_154;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    temp_s7        = temp_s7_tmp;
    field14C_2     = field14C_2_tmp;
    distFieldF8    = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
    var_s6         = 0;

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            var_s6      = sharedFunc_800DE578_2_s00(airScreamer);
            distFieldF8 = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            angleDelta  = FP_ANGLE_NORM_S(angle - airScreamer->rotation_24.vy);

            if (sharedFunc_800DC200_2_s00(airScreamer) &&
                (Math_CheckSignedRange(angleDelta, FP_ANGLE(120.0f)) ||
                 (dist < Q12(5.0f) && Math_CheckSignedRange(angleDelta, FP_ANGLE(60.0f)))))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (!sharedFunc_800DC30C_2_s00(airScreamer) || (dist >= val2_0 && Rng_RandQ12() >= Q12(0.4f)))
            {
                airScreamerProps.timer_120       = Q12(2.0f);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else
            {
                temp_v0                          = 1;
                airScreamer->model_0.stateStep_3 = temp_v0 * 2; // @hack Copy of `temp_v0 == 1` hack below for them to be folded together.
            }
            break;

        case 1:
            temp_v0 = sharedFunc_800DC598_2_s00(airScreamer);
            if (temp_v0 == 1)
            {
                airScreamer->model_0.stateStep_3 = temp_v0 * 2; // @hack This should just be `= 2`, but that causes extra `li v0, 2` to be emitted here?
            }
            else if (temp_v0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (distFieldF8 < Q12(2.0f) || (airScreamerProps.flags_11C & AirScreamerFlag_31))
            {
                var_s6 = sharedFunc_800DE578_2_s00(airScreamer);
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
            {
                switchCond                           = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(22, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;
            }
            break;

        case 3:
            switchCond = 1;
            break;

        case 4:
            if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(24, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case 5:
            switchCond = 2;
            break;
    }

    sharedFunc_800DF448_2_s00(airScreamer, true);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    distFieldF8 = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);

                    if (var_s6 || (((field14C_2 != 0 && dist < Q12(15.0f)) || dist < Q12(4.0f)) && distFieldF8 < Q12(1.5f)))
                    {
                        airScreamer->model_0.controlState_2 = 10;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        airScreamerProps.field_E8_8         = 3;
                        airScreamerProps.flags_11C         |= AirScreamerFlag_4;
                    }
                    else if (dist > Q12(30.0f) && distFieldF8 < Q12(1.0f))
                    {
                        airScreamer->model_0.controlState_2 = 7;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (temp_s7 == 2)
                    {
                        airScreamer->model_0.controlState_2 = 27;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (temp_s7 == 3)
                    {
                        airScreamer->model_0.controlState_2 = 42;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = 16;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = 17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_15(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    sharedFunc_800DDF74_2_s00(airScreamer, Q12(0.5f), airScreamer->rotation_24.vy);
    sharedFunc_800DF2D0_2_s00(airScreamer);
    airScreamer->flags_3E &= ~CharaFlag_Unk3;

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch ((u32)airScreamerProps.field_E8_0)
            {
                case 0:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_4;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    break;

                case 1:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_5;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    break;

                case 3:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_5;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_16;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

// Very similar to `Ai_AirScreamerControl_44`, changes here should be copied there.
void Ai_AirScreamerControl_16(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    animStatus;
    bool   field14C_2;
    bool   field14C_2_tmp;
    bool   cond;
    s32    var_a0;
    q19_12 var_s1;

    animStatus             = airScreamer->model_0.anim_4.status_0;
    field14C_2_tmp         = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    airScreamer->flags_3E |= CharaFlag_Unk3;
    field14C_2             = field14C_2_tmp;
    cond                   = false;

    // Handle state step.
    switch ((u32)airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            if (field14C_2)
            {
                sharedFunc_800DE11C_2_s00(airScreamer);
            }
            else
            {
                sharedFunc_800DDF74_2_s00(airScreamer, Q12(4.0f), func_80080478(&airScreamer->position_18, &g_SysWork.playerWork_4C.player_0.position_18));
                airScreamerProps.position_104 = airScreamerProps.targetPosition_F8;
            }

            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;

        case AirScreamerStateStep_1:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(6, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_2;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus != ANIM_STATUS(6, false))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                airScreamerProps.flags_11C      |= AirScreamerFlag_3;
            }
            break;

        case AirScreamerStateStep_3:
            if (animStatus != ANIM_STATUS(6, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800DF80C_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f)))
    {
        case 0:
        case 1:
        case 2:
            if (!cond)
            {
                break;
            }

            var_s1 = airScreamerProps.field_E8_4 ? Q12(0.1f) : Q12(0.0f);

            if (airScreamerProps.field_E8_0 == 3)
            {
                sharedFunc_800DD13C_2_s00(airScreamer, airScreamer->field_40 + 1, Q12(0.7f));
            }

            if (field14C_2)
            {
                if (airScreamerProps.field_E8_8 == 5)
                {
                    airScreamer->model_0.controlState_2 = AirScreamerControl_14;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                    if (Rng_TestProbability(Q12_DIV(airScreamer->health_B0, Q12(380.0f)) + (var_s1 * 2)))
                    {
                        airScreamerProps.field_E8_8 = 3;
                    }
                }
                else
                {
                    airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                    // TODO: `Rng_TestProbability` doesn't fit?
                    if (Rng_RandQ12() <= (Q12_DIV(airScreamer->health_B0, Q12(380.0f)) + (var_s1 * 2)))
                    {
                        airScreamerProps.field_E8_8 = 3;
                    }
                    else
                    {
                        airScreamerProps.field_E8_8 = 5;
                    }
                }
                break;
            }

            switch (airScreamerProps.field_E8_8)
            {
                case 3:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_13;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                    if (Rng_TestProbability(Q12(0.5f) - (var_s1 * 3)))
                    {
                        airScreamerProps.field_E8_8 = 2;
                    }
                    break;

                case 2:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                    // TODO: Does `Rng_TestProbability` fit?
                    if (Rng_RandQ12() > (Q12_DIV(airScreamer->health_B0, Q12(380.0f)) + (var_s1 * 2)))
                    {
                        airScreamerProps.field_E8_8 = 5;
                    }
                    else if (Rng_TestProbability(Q12(0.3f) + (var_s1 * 3)))
                    {
                        airScreamerProps.field_E8_8 = 3;
                    }
                    break;

                case 5:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_14;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                    if (Rng_TestProbability(Q12_DIV(airScreamer->health_B0, Q12(380.0f))))
                    {
                        airScreamerProps.field_E8_8 = 3;
                    }
                    break;

                case 1:
                case 4:
                    if (Rng_TestProbability(Q12(0.2f) + (var_s1 * 5)))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_14;
                    }

                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                    if (Rng_TestProbability(Q12(0.5f) + (var_s1 * 3)))
                    {
                        var_a0 = 2;
                    }
                    else
                    {
                        var_a0 = 5;
                    }

                    airScreamerProps.field_E8_8 = var_a0;
                    break;

                case 0:
                default:
                    if (airScreamerProps.field_E8_0 == 3)
                    {
                        var_s1 = Q12(1.0f);
                    }

                    if (Rng_TestProbability(Q12(0.4f) + (var_s1 * 3)))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_14;
                    }

                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                    if (Rng_TestProbability(Q12(0.6f) + (var_s1 * 2)))
                    {
                        var_a0 = 2;
                    }
                    else
                    {
                        var_a0 = 5;
                    }

                    airScreamerProps.field_E8_8 = var_a0;
                    break;
            }
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_17;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_17(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    bool cond;
    s32  animStatus;
    u32  stateStep;

    cond = false;

    stateStep              = airScreamer->model_0.stateStep_3;
    animStatus             = airScreamer->model_0.anim_4.status_0;
    airScreamer->flags_3E |= CharaFlag_Unk3;

    // Handle state step.
    switch (stateStep)
    {
        case AirScreamerStateStep_0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_4, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_1:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_4, false))
            {
                airScreamer->model_0.stateStep_3             = AirScreamerStateStep_2;
                airScreamer->properties_E4.player.flags_11C |= AirScreamerFlag_3;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_4, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800DF8A0_2_s00(airScreamer);
    Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f));

    if (cond)
    {
        airScreamer->model_0.controlState_2 = AirScreamerControl_2;
        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
        airScreamerProps.field_E8_8         = 1;
    }
#endif
}

void Ai_AirScreamerControl_18(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    animStatus;
    s32    switchCond;
    s32    sp10;
    bool   field14C_0;
    bool   field14C_1;
    bool   field14C_2;
    bool   field14C_0_tmp;
    bool   field14C_1_tmp;
    bool   field14C_2_tmp;
    q19_12 distToTarget;
    q19_12 angleDeltaToTarget;
    s32    temp_s5;
    bool   cond; // TODO: Why does moving this decl cause mismatch?

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;
    sp10       = sharedFunc_800D4A80_0_s01(airScreamer);
    cond       = false;

    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_0     = field14C_0_tmp;
    field14C_1     = field14C_1_tmp;
    field14C_2     = field14C_2_tmp;

    temp_s5 = sharedFunc_800DC50C_2_s00(airScreamer);

    switch (airScreamer->model_0.stateStep_3)
    {
        case 64:
            sharedFunc_800DD4EC_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case 0:
            sharedFunc_800D529C_0_s01(airScreamer, Q12(5.0f), airScreamer->rotation_24.vy);
            sharedFunc_800DE6A8_2_s00(airScreamer, &airScreamerProps.targetPosition_F8, Q12(4.0f));
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case 1:
            cond                             = true;
            airScreamerProps.timer_120       = Q12(6.0f);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;

        case 2:
            distToTarget       = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            angleDeltaToTarget = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);

            if (!temp_s5)
            {
                if ((distToTarget < Q12(1.0f) && (angleDeltaToTarget >= FP_ANGLE(-5.0f) && angleDeltaToTarget <= FP_ANGLE(5.0f))) ||
                    airScreamer->properties_E4.player.flags_11C < 0)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                }
                else
                {
                    if (!airScreamerProps.timer_120)
                    {
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
                    }
                    else if (cond)
                    {
                        if (sharedFunc_800DC200_2_s00(airScreamer) && distToTarget > Q12(7.0f))
                        {
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
                        }
                        else if (sharedFunc_800DC3BC_2_s00(airScreamer) && distToTarget < Q12(3.0f) && Rng_TestProbability(Q12(0.7f)))
                        {
                            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                        }
                    }
                }
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                           = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_4;
            }
            break;

        case 4:
            switchCond = 1;
            break;

        case 5:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(18, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_6;
            }
            break;

        case 6:
            switchCond = 2;
            break;
    }

    sharedFunc_800D57C8_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if ((field14C_1 | field14C_0 | field14C_2) != 0)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if ((field14C_1 | field14C_0 | field14C_2) == 0)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_4;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                        break;
                    }

                    if (sharedFunc_800DC0A8_2_s00(airScreamer) != false)
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 2:
                    if (sp10 == 3)
                    {
                        if ((field14C_1 | field14C_0 | field14C_2) == 0)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_33;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_35;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_19(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    animStatus;
    bool   field14C_0;
    bool   field14C_1;
    bool   field14C_2;
    bool   new_var4;
    bool   new_var2;
    bool   new_var3;
    q19_12 distFieldF8;
    q19_12 angFieldF8;
    s32    switchCond;
    s32    sp10; // Possibly `bool`.
    s32    sp10_temp;
    bool   cond;
    bool   temp_s5;

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;

    // @hack These flags/bitfields always need weird variable juggling, is there a way to remove it?
    sp10_temp  = sharedFunc_800D4A80_0_s01(airScreamer);
    new_var4   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    new_var2   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var3   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    sp10       = sp10_temp;
    cond       = false;
    field14C_0 = new_var4;
    field14C_1 = new_var2;
    field14C_2 = new_var3;

    temp_s5 = sharedFunc_800DC50C_2_s00(airScreamer);

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            sharedFunc_800DE7E0_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case 1:
            cond                             = true;
            airScreamerProps.timer_120       = Q12(6.0f);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;

        case 2:
            distFieldF8 = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            angFieldF8  = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);

            if (!temp_s5)
            {
                if ((distFieldF8 < Q12(0.5f) && (angFieldF8 >= FP_ANGLE(-5.0f) && angFieldF8 <= FP_ANGLE(5.0f))) ||
                    (airScreamerProps.flags_11C & AirScreamerFlag_31))
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                }
                else if (airScreamerProps.timer_120 == Q12(0.0f))
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
                }
                else if (cond)
                {
                    if (sharedFunc_800DC200_2_s00(airScreamer) && distFieldF8 > Q12(6.0f))
                    {
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
                    }
                    else if (sharedFunc_800DC3BC_2_s00(airScreamer) && distFieldF8 < Q12(2.0f) && Rng_TestProbability(Q12(0.5f)))
                    {
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                    }
                }
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                           = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_4;
            }
            break;

        case 4:
            switchCond = 1;
            break;

        case 5:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(24, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_6;
            }
            break;

        case 6:
            switchCond = 2;
            break;
    }

    sharedFunc_800D57C8_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (field14C_1 | field14C_0 | field14C_2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (field14C_1 | field14C_0 | field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_5;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 2:
                    if (sp10 == 3)
                    {
                        if (field14C_1 | field14C_0 | field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_35;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_34;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_20(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    animStatus;
    q19_12 angle0;
    bool   field14C_0;
    bool   field14C_1;
    bool   field14C_2;
    bool   field14C_0_tmp;
    bool   field14C_1_tmp;
    bool   field14C_2_tmp;
    bool   temp_a0;
    bool   condModelStateIs2;
    s32    switchCond;
    q19_12 rngAngle0;
    q19_12 angleSubtract;
    q19_12 angle1;
    s32    damageType;

    animStatus = airScreamer->model_0.anim_4.status_0;
    angle0     = sharedData_800E21D0_0_s01.field_15C;

    field14C_0_tmp    = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp    = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp    = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_0        = field14C_0_tmp;
    field14C_1        = field14C_1_tmp;
    field14C_2        = field14C_2_tmp;
    temp_a0           = sharedFunc_800DC50C_2_s00(airScreamer);
    condModelStateIs2 = switchCond = 0;

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            airScreamerProps.timer_120 = Q12(6.0f);

        case 1:
            sharedFunc_800DE6A8_2_s00(airScreamer, &airScreamerProps.position_104, Q12(1.5f));

            if (!sharedFunc_800DC3BC_2_s00(airScreamer) || Rng_RandQ12() >= FP_ANGLE(72.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case 2:
            condModelStateIs2 = true;

        case 3:
            if (temp_a0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
                break;
            }

            if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(1.0f))
            {

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else if (!airScreamerProps.timer_120)
            {
                if (condModelStateIs2)
                {
                    switchCond = 1;
                }

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (field14C_0 || field14C_1 || field14C_2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;

                if (angle0 > (FP_ANGLE(2.9f)))
                {
                    angle1 = func_80080478(&airScreamer->position_18, &airScreamerProps.position_104) - airScreamer->rotation_24.vy;
                    angle1 = FP_ANGLE_NORM_S(angle1);
                    if (angle1 < FP_ANGLE(0.0f))
                    {
                        angle1 += FP_ANGLE(0.3f);
                    }

                    sharedFunc_800D529C_0_s01(airScreamer, Q12(1.5f), (angle1 >> 2) + airScreamer->rotation_24.vy);
                    airScreamerProps.timer_120 = Q12(6.0f);
                }
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);

                if (field14C_2 || field14C_1)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_6;
                }
            }
            else if (field14C_2 || field14C_1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case 5:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                           = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_7;
            }
            break;

        case 6:
            switchCond = 3;

            if (field14C_2 || field14C_1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
            }
            else
            {
                switchCond = 2;
            }
            break;

        case 7:
            switchCond = 3;
            break;
    }

    sharedFunc_800D57C8_0_s01(airScreamer);

    damageType = Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f));
    switch (damageType)
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                case 1:
                    if (!field14C_2 && !field14C_1)
                    {
                        if (switchCond == 1)
                        {
                            rngAngle0     = Rng_RandQ12();
                            angleSubtract = FP_ANGLE(0.0f);

                            if (airScreamerProps.field_E8_8 == switchCond)
                            {
                                angleSubtract = FP_ANGLE(36.0f);
                            }

                            if (rngAngle0 < (FP_ANGLE(252.0f) - (angleSubtract * 2)))
                            {
                                airScreamer->model_0.controlState_2 = AirScreamerControl_28;
                                airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                            }
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 3:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_21(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    switch3;
    s32    condModelStateIs2;
    s32    animStatus;
    q19_12 angle0;
    bool   field14C_0;
    bool   field14C_1;
    bool   field14C_2;
    bool   field14C_0_tmp;
    bool   field14C_1_tmp;
    bool   field14C_2_tmp;
    bool   temp_a0;
    q19_12 rngAngle0;
    q19_12 angleSubtract;
    q19_12 angle1;

    switch3           = 0;
    condModelStateIs2 = 0;
    animStatus        = airScreamer->model_0.anim_4.status_0;
    angle0            = sharedData_800E21D0_0_s01.field_15C;

    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_0     = field14C_0_tmp;
    field14C_1     = field14C_1_tmp;
    field14C_2     = field14C_2_tmp;
    temp_a0        = sharedFunc_800DC50C_2_s00(airScreamer);

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            airScreamerProps.timer_120 = Q12(6.0f);

        case AirScreamerStateStep_1:
            sharedFunc_800DE6A8_2_s00(airScreamer, &airScreamerProps.position_104, Q12(2.0f));

            if (!sharedFunc_800DC3BC_2_s00(airScreamer) || Rng_RandQ12() >= FP_ANGLE(36.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_2:
            condModelStateIs2 = 1;

        case AirScreamerStateStep_3:
            if (temp_a0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
                break;
            }

            if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(1.0f))
            {
                if (condModelStateIs2)
                {
                    switch3 = 1;
                }

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else if (!airScreamerProps.timer_120)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (field14C_2 || field14C_0 || field14C_1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;

                if (angle0 > (FP_ANGLE(2.9f)))
                {
                    angle1 = func_80080478(&airScreamer->position_18, &airScreamerProps.position_104) - airScreamer->rotation_24.vy;
                    angle1 = FP_ANGLE_NORM_S(angle1);
                    if (angle1 < FP_ANGLE(0.0f))
                    {
                        angle1 += FP_ANGLE(0.3f);
                    }

                    sharedFunc_800D529C_0_s01(airScreamer, Q12(2.0f), (angle1 >> 2) + airScreamer->rotation_24.vy);
                    airScreamerProps.timer_120 = Q12(6.0f);
                }
            }
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switch3                              = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);

                if (field14C_1 || field14C_0)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_6;
                }
            }
            else if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switch3                              = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_7;
            }
            break;

        case AirScreamerStateStep_6:
            switch3 = 3;
            if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
            }
            else
            {
                switch3 = 2;
            }
            break;

        case AirScreamerStateStep_7:
            switch3 = 3;
            break;
    }

    sharedFunc_800D57C8_0_s01(airScreamer);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switch3)
            {
                case 0:
                case 1:
                    if (field14C_2 == 0)
                    {
                        if (switch3 == 1)
                        {
                            rngAngle0     = Rng_RandQ12();
                            angleSubtract = FP_ANGLE(0.0f);

                            if (airScreamerProps.field_E8_8 == switch3)
                            {
                                angleSubtract = FP_ANGLE(36.0f);
                            }

                            if (rngAngle0 < (FP_ANGLE(252.0f) - (angleSubtract * 2)))
                            {
                                airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                                airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                            }
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_22;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (!field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_8;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 3:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_8;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_22(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    switchCond;
    s32    animStatus;
    q19_12 dist0;
    q19_12 angle0;
    bool   field14C_2;
    q19_12 chance0;
    q19_12 chance1;
    bool   temp_s3;
    s32    var_s5;
    q19_12 angleAdd;

    switchCond = 0;
    angleAdd   = FP_ANGLE(0.0f);
    animStatus = airScreamer->model_0.anim_4.status_0;
    dist0      = sharedData_800E21D0_0_s01.distance_150;
    angle0     = sharedData_800E21D0_0_s01.angle_154;
    field14C_2 = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;

    if (airScreamerProps.field_E8_4)
    {
        angleAdd = Q12(0.1f);
    }

    temp_s3 = sharedFunc_800DC50C_2_s00(airScreamer);
    var_s5  = 0;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            switchCond                 = 1;
            airScreamerProps.timer_120 = Q12(2.0f);
            airScreamer->flags_3E     |= CharaFlag_Unk3;

        case AirScreamerStateStep_1:
            sharedFunc_800D529C_0_s01(airScreamer, dist0 / 2, angle0);

            if (Rng_TestProbability((angleAdd * 2) + FP_ANGLE(72.0f)))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }

        default:
            break;

        case AirScreamerStateStep_2:
            var_s5 = 1;

            if (!temp_s3)
            {
                if (airScreamerProps.timer_120 != 0)
                {
                    if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(1.0f))
                    {
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
                    }
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                }
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_3:
            sharedFunc_800D529C_0_s01(airScreamer, dist0 / 2, angle0);

            if (temp_s3)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (FP_ANGLE_NORM_S(angle0 - airScreamer->rotation_24.vy) >= FP_ANGLE(-10.0f) &&
                     FP_ANGLE_NORM_S(angle0 - airScreamer->rotation_24.vy) < FP_ANGLE(10.0f))
            {
                var_s5 = 2;
            }
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_19, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_27, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            switchCond = 2;
            break;
    }

    if (var_s5 == 1)
    {
        sharedFunc_800D57C8_0_s01(airScreamer);
    }
    else
    {
        sharedFunc_800D598C_0_s01(airScreamer);
    }

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (field14C_2 == 0)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (animStatus == ANIM_STATUS(AirScreamerAnim_23, true) ||
                        animStatus == ANIM_STATUS(AirScreamerAnim_25, true))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_8;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_23, false);
                    }
                    break;

                case 1:
                    chance0 = sharedFunc_800DC894_2_s00(airScreamer, dist0);
                    chance1 = sharedFunc_800DC6E4_2_s00(airScreamer, dist0);
                    if (Rng_TestProbability(chance0))
                    {
                        if (airScreamerProps.field_E8_0 == 3)
                        {
                            sharedFunc_800DD13C_2_s00(airScreamer, airScreamer->field_40 + 1, Q12(0.6f));
                        }

                        airScreamer->model_0.controlState_2          = AirScreamerControl_23;
                        airScreamer->model_0.stateStep_3             = AirScreamerStateStep_0;
                        airScreamer->properties_E4.player.flags_11C |= CharaFlag_Unk5;
                    }
                    else if (Rng_TestProbability(chance1))
                    {
                        airScreamer->model_0.controlState_2          = AirScreamerControl_27;
                        airScreamer->model_0.stateStep_3             = AirScreamerStateStep_0;
                        airScreamer->properties_E4.player.flags_11C |= CharaFlag_Unk5;
                    }
                    break;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_23(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    temp_fp;
    s32    temp_fp_tmp;
    bool   field14C_2;
    bool   field14C_2_tmp;
    bool   temp_s6;
    q19_12 dist0;
    q19_12 dist1;
    q19_12 posDiffAngle;
    q19_12 distTest;
    s32    switchCond;
    s32    animStatus;

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;

    temp_fp_tmp    = sharedFunc_800D4A80_0_s01(airScreamer);
    dist0          = sharedData_800E21D0_0_s01.distance_150;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    temp_fp        = temp_fp_tmp;
    field14C_2     = field14C_2_tmp;
    temp_s6        = sharedFunc_800DC50C_2_s00(airScreamer);

    sharedFunc_800D53AC_0_s01(airScreamer);
    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
#define angleDiff FP_ANGLE_NORM_S(g_SysWork.playerWork_4C.player_0.rotation_24.vy - airScreamer->rotation_24.vy)

            distTest = dist0 + (Rng_RandQ12() * 4);
            if (sharedFunc_800DC200_2_s00(airScreamer) && distTest > Q12(8.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (!sharedFunc_800DC3BC_2_s00(airScreamer) || distTest >= Q12(4.0f) ||
                     (angleDiff < FP_ANGLE(-30.0f) || angleDiff >= FP_ANGLE(30.0f)) ||
                     Rng_RandQ12() >= Q12(0.2f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }

            airScreamerProps.timer_120 = Q12(4.0f);
            break;

#undef angleDiff

        case 1:
            distTest = NO_VALUE;
            if (airScreamerProps.targetPosition_F8.vy - airScreamer->position_18.vy > Q12(-0.2f) &&
                airScreamerProps.targetPosition_F8.vy - airScreamer->position_18.vy < Q12(0.8f))
            {
                distTest = airScreamer->field_D4.radius_0 + Q12(0.15f);
            }

            dist1        = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            posDiffAngle = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);

            if (temp_s6)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (dist1 < distTest && (posDiffAngle >= FP_ANGLE(-22.5f) && posDiffAngle < FP_ANGLE(22.5f)))
            {
                switchCond = 1;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;
            }
            break;

        case 3:
            switchCond = 2;
            break;

        case 4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                           = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(18, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case 5:
            switchCond = 3;
            break;
    }

    sharedFunc_800D57C8_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (!sharedFunc_800DC67C_2_s00(airScreamer))
                    {
                        if (field14C_2 == 0)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_26;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_27;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    // TODO: Likely some kind of `CharaHasFlag` inline?
                    if (!((&g_SysWork.playerWork_4C.player_0)->flags_3E & CharaFlag_Unk4) &&
                        g_SysWork.npcIdxs_2354[0] == NO_VALUE &&
                        g_SysWork.npcIdxs_2354[1] == NO_VALUE)
                    {
                        if (animStatus == ANIM_STATUS(19, true))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_25;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_24;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        sharedFunc_800DE11C_2_s00(airScreamer);
                        airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 3:
                    if (temp_fp == switchCond)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_38;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_24(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    bool temp_a0;
    bool unkField14C;
    s32  unkField150;
    s32  switchCond;
    s32  animStatus;

    switchCond  = 0;
    animStatus  = airScreamer->model_0.anim_4.status_0;
    unkField150 = sharedData_800E21D0_0_s01.distance_150;
    unkField14C = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    temp_a0     = sharedFunc_800DC50C_2_s00(airScreamer);

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            airScreamerProps.timer_120 = Q12(2.0f);
            if (Rng_TestProbability(Q12(0.7f)))
            {
                switchCond = 2;
                sharedFunc_800D529C_0_s01(airScreamer, Q12(8.0f), airScreamer->rotation_24.vy);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case 1:
            if (temp_a0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            break;

        case 4:
            switchCond = 2;

            if (temp_a0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (airScreamer->moveSpeed_38 > Q12(1.5f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            else if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(3.0f) ||
                     airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                           = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;
            }
            break;

        case 3:
            switchCond = 1;
            break;

        case 5:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                           = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(18, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_6;
            }
            break;

        case 6:
            switchCond = 3;
            break;
    }

    if (switchCond >= 2 && switchCond < 4)
    {
        sharedFunc_800D57C8_0_s01(airScreamer);
    }
    else
    {
        sharedFunc_800DEBCC_2_s00(airScreamer);
        sharedFunc_800D5B10_0_s01(airScreamer);
    }

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (airScreamerProps.timer_120 == Q12(0.0f) || unkField150 > Q12(2.0f))
                    {
                        if (!unkField14C)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_26;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (!unkField14C)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_13;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_11;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 2:
                    break;

                case 3:
                    if (sharedFunc_800D4A80_0_s01(airScreamer) == switchCond)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_39;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_25(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    bool var_s1;
    bool var_s2;
    s32  animStatus;

    var_s1     = false;
    var_s2     = false;
    animStatus = airScreamer->model_0.anim_4.status_0;

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;

        case 1:
            if (animStatus == ANIM_STATUS(19, true))
            {
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_2;
                airScreamer->model_0.anim_4.status_0 = 4;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(2, true) && airScreamer->model_0.anim_4.keyframeIdx_8 < 8192)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                airScreamerProps.flags_11C      |= 1 << 5;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(19, true))
            {
                var_s1 = true;
            }
            else if (airScreamer->field_44.field_8 == NO_VALUE)
            {
                var_s1                           = true;
                var_s2                           = true;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                var_s1 = true;
                var_s2 = true;
            }
            break;
    }

    sharedFunc_800D53AC_0_s01(airScreamer);
    sharedFunc_800D5C90_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.2f)))
    {
        case 0:
            if (var_s1)
            {
                if (airScreamerProps.field_E8_8 == 3)
                {
                    airScreamerProps.field_E8_8 = 2;

                    if (var_s2 && Rng_TestProbability(Q12(0.5f)))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_24;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                    }
                }
                else
                {
                    if (var_s2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_24;
                    }
                    else if (Rng_TestProbability(Q12(0.5f)))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_24;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                    }
                }
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= 1 << 3;
            break;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= 1 << 3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            if (airScreamer->health_B0 <= 0)
            {
                airScreamerProps.flags_11C |= 1 << 6;
            }
            else
            {
                airScreamerProps.flags_11C |= 1 << 3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_26(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32  animStatus;
    bool field14C_2;
    bool field14C_1;
    bool new_var;
    bool new_var2;
    bool temp_a0;
    bool switchCond;

    switchCond = false;
    animStatus = airScreamer->model_0.anim_4.status_0;

    new_var    = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var2   = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_1 = new_var;
    field14C_2 = new_var2;

    temp_a0 = sharedFunc_800DC50C_2_s00(airScreamer);

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            sharedFunc_800DEBCC_2_s00(airScreamer);

        case AirScreamerStateStep_1:
            airScreamerProps.timer_120       = Q12(4.0f);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            break;

        case AirScreamerStateStep_2:
            if (temp_a0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            else if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(0.5f))
            {
                sharedFunc_800DE6A8_2_s00(airScreamer, &airScreamerProps.position_104, Q12(2.5f));
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                sharedFunc_800DE6A8_2_s00(airScreamer, &airScreamerProps.position_104, Q12(2.5f));
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_3:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                           = true;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_4:
            switchCond = true;
            break;
    }

    sharedFunc_800D57C8_0_s01(airScreamer);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case false:
                    if (sharedFunc_800DC67C_2_s00(airScreamer))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_27;
                    }
                    else if (!field14C_2)
                    {
                        if (airScreamerProps.timer_120 == Q12(0.0f) && !field14C_1 &&
                            Rng_TestProbability(Q12(0.5f)))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                    }

                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    break;

                case true:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_13;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_27(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    animStatus;
    s32    switchCond;
    s32    temp_fp;
    bool   field14C_2;
    bool   field14C_2_tmp;
    q19_12 dist;
    q19_12 angle;
    q19_12 distFieldF8;
    s32    var_s6; // Possibly `bool`
    bool   cond;
    q19_12 angleDiff;

    animStatus     = airScreamer->model_0.anim_4.status_0;
    switchCond     = 0;
    temp_fp        = sharedFunc_800D4A80_0_s01(airScreamer);
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    dist           = sharedData_800E21D0_0_s01.distance_150;
    angle          = sharedData_800E21D0_0_s01.angle_154;
    field14C_2     = field14C_2_tmp;

    distFieldF8 = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
    var_s6      = 0;
    cond        = sharedFunc_800DC50C_2_s00(airScreamer);

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            var_s6      = sharedFunc_800DEC64_2_s00(airScreamer);
            distFieldF8 = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            angleDiff   = FP_ANGLE_NORM_S(angle - airScreamer->rotation_24.vy);

            if (sharedFunc_800DC200_2_s00(airScreamer) && airScreamer->moveSpeed_38 > Q12(1.5f) &&
                (Math_CheckSignedRange(angleDiff, FP_ANGLE(120.0f)) || ((dist < Q12(5.0f)) && Math_CheckSignedRange(angleDiff, FP_ANGLE(60.0f)))))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else
            {
                airScreamerProps.timer_120 = Q12(2.0f);

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_1:
            if (cond)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (distFieldF8 < Q12(2.0f) || (airScreamerProps.flags_11C & AirScreamerFlag_31))
            {
                var_s6 = sharedFunc_800DEC64_2_s00(airScreamer);
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_19, true))
            {
                switchCond                           = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_27, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;
            }
            break;

        case AirScreamerStateStep_3:
            switchCond = 1;
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_19, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_18, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            switchCond = 2;
            break;
    }

    sharedFunc_800D57C8_0_s01(airScreamer);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            switch (switchCond)
            {
                case 0:
                    if (var_s6 || ((field14C_2 && dist < Q12(15.0f)) || dist < Q12(4.0f)) && distFieldF8 < Q12(1.5f))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        airScreamerProps.field_E8_8         = 3;
                        airScreamerProps.flags_11C         |= AirScreamerFlag_4;
                    }
                    else if (dist > Q12(30.0f) && distFieldF8 < Q12(1.0f))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (animStatus == ANIM_STATUS(AirScreamerAnim_23, true) || animStatus == ANIM_STATUS(AirScreamerAnim_25, true))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_14;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(airScreamer))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_23, false);
                    }
                    break;

                case 2:
                    if (temp_fp == 3)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_42;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case AirScreamerDamage_1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_28(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    sharedFunc_800D529C_0_s01(airScreamer, Q12(0.5f), airScreamer->rotation_24.vy);
    sharedFunc_800D598C_0_s01(airScreamer);
    airScreamer->flags_3E &= ~CharaFlag_Unk3;

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            // @hack Explicit `u32` cast needed for match.
            switch ((u32)airScreamerProps.field_E8_0)
            {
                case 0:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_18;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    break;

                case 1:
                case 3:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_19;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    break;
            }
            break;

        case 1:
            airScreamer->model_0.controlState_2 = AirScreamerControl_29;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            return;

        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_29(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32  temp_s2;
    s32  var_a0;
    s32  var_s1;
    s32  var_s1_2;
    u32  animStatus;
    u32  stateStep;
    bool new_var;

    animStatus             = airScreamer->model_0.anim_4.status_0;
    new_var                = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    var_s1                 = 0;
    temp_s2                = new_var;
    stateStep              = airScreamer->model_0.stateStep_3;
    airScreamer->flags_3E |= CharaFlag_Unk3;

    // Handle state step.
    switch (stateStep)
    {
        case AirScreamerStateStep_0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_7, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_1:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_7, false))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                airScreamerProps.flags_11C      |= AirScreamerFlag_3;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_7, true))
            {
                var_s1 = 1;
            }
            break;
    }

    sharedFunc_800D5D80_0_s01(airScreamer);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f)))
    {
        case AirScreamerDamage_None:
        case AirScreamerDamage_1:
            if (var_s1 != 0)
            {
                var_s1_2 = Q12(0.0f);
                if (airScreamer->properties_E4.airScreamer.field_E8_4)
                {
                    var_s1_2 = Q12(0.1f);
                }

                if (airScreamer->properties_E4.airScreamer.field_E8_0 == 3)
                {
                    sharedFunc_800DD13C_2_s00(airScreamer, airScreamer->field_40 + 1, Q12(0.7f));
                }

                if (temp_s2 != 0)
                {
                    if (airScreamer->properties_E4.airScreamer.field_E8_8 == 5)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_27;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                        if (Rng_TestProbability(Q12_DIV(airScreamer->health_B0, Q12(380.0f)) + (var_s1_2 * 2)))
                        {
                            airScreamer->properties_E4.airScreamer.field_E8_8 = 3;
                        }
                        break;
                    }

                    airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                    if (Rng_RandQ12() > (Q12_DIV(airScreamer->health_B0, Q12(380.0f)) + (var_s1_2 * 2)))
                    {
                        airScreamer->properties_E4.airScreamer.field_E8_8 = 5;
                    }
                    else
                    {
                        airScreamer->properties_E4.airScreamer.field_E8_8 = 3;
                    }
                    break;
                }

                switch (airScreamer->properties_E4.airScreamer.field_E8_8)
                {
                    case 3:
                        airScreamer->model_0.controlState_2 = AirScreamerControl_26;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                        if (Rng_TestProbability(Q12(0.5f) - (var_s1_2 * 3)))
                        {
                            airScreamer->properties_E4.airScreamer.field_E8_8 = 2;
                        }
                        break;

                    case 2:
                        airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                        // TODO: Will `Rng_TestProbability` fit?
                        if (Rng_RandQ12() > (Q12_DIV(airScreamer->health_B0, Q12(380.0f)) + (var_s1_2 * 2)))
                        {
                            airScreamer->properties_E4.airScreamer.field_E8_8 = 5;
                        }
                        else if (Rng_TestProbability((var_s1_2 * 3) + Q12(0.3f)))
                        {
                            airScreamer->properties_E4.airScreamer.field_E8_8 = 3;
                        }
                        break;

                    case 5:
                        airScreamer->model_0.controlState_2 = AirScreamerControl_27;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                        if (Rng_TestProbability(Q12_DIV(airScreamer->health_B0, Q12(380.0f))))
                        {
                            airScreamer->properties_E4.airScreamer.field_E8_8 = 3;
                        }
                        break;

                    case 1:
                    case 4:
                        // TODO: Will `Rng_TestProbability` fit?
                        if (Rng_RandQ12() >= ((var_s1_2 * 5) + Q12(0.2f)))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_27;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                        if (Rng_TestProbability((var_s1_2 * 3) + Q12(0.5f)))
                        {
                            var_a0 = 2;
                        }
                        else
                        {
                            var_a0 = 5;
                        }

                        airScreamer->properties_E4.airScreamer.field_E8_8 = var_a0;
                        break;

                    default:
                    case 0:
                        if (airScreamer->properties_E4.airScreamer.field_E8_0 == 3)
                        {
                            var_s1_2 = Q12(1.0f);
                        }

                        if (Rng_RandQ12() >= ((var_s1_2 * 3) + Q12(0.4f)))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_27;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        }

                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                        if (Rng_TestProbability((var_s1_2 * 2) + Q12(0.6f)))
                        {
                            var_a0 = 2;
                        }
                        else
                        {
                            var_a0 = 5;
                        }

                        airScreamer->properties_E4.airScreamer.field_E8_8 = var_a0;
                        break;
                }
            }
            break;

        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_30;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_30(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    bool cond;
    s32  animStatus;

    cond                   = false;
    animStatus             = airScreamer->model_0.anim_4.status_0;
    airScreamer->flags_3E |= CharaFlag_Unk3;

    switch ((u32)airScreamer->model_0.stateStep_3)
    {
        case 0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(9, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_1;
            }
            break;

        case 1:
            if (animStatus != ANIM_STATUS(9, false))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                airScreamerProps.flags_11C      |= AirScreamerFlag_3;
            }
            break;

        case 2:
            if (animStatus != ANIM_STATUS(9, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800D5E14_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f)))
    {
        case 0:
        case 1:
        case 2:
            if (cond)
            {
                airScreamer->model_0.controlState_2 = AirScreamerControl_31;
                airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            }
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_31(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            airScreamerProps.timer_120 = (Rng_RandQ12() * 2) + Q12(0.5f);

            sharedFunc_800D529C_0_s01(airScreamer,
                                      Q12(4.0f),
                                      airScreamer->rotation_24.vy + Q12_MULT_PRECISE(Rng_RandQ12() - FP_ANGLE(180.0f), FP_ANGLE(45.0f)));

            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case 1:
            if (airScreamerProps.timer_120 == Q12(0.0f) ||
                Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(2.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;
    }

    sharedFunc_800E012C_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f)))
    {
        case 0:
            break;

        case 1:
        case 2:
            airScreamerProps.flags_11C |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            if (airScreamer->health_B0 <= 0)
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_32(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    bool cond;
    s32  animStatus;

    cond       = false;
    animStatus = airScreamer->model_0.anim_4.status_0;

    airScreamer->flags_3E |= CharaFlag_Unk3;

    switch ((u32)airScreamer->model_0.stateStep_3)
    {
        case 0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                if (animStatus == ANIM_STATUS(HarryAnim_RunRightStumble, true) ||
                    animStatus == ANIM_STATUS(HarryAnim_RunForwardWallStopRight, true))
                {
                    airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunRightWallStop, false);
                }
                else
                {
                    airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_RunForwardWallStopLeft, false);
                }

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case 1:
            if (animStatus != ANIM_STATUS(HarryAnim_RunForwardWallStopLeft, false) &&
                animStatus != ANIM_STATUS(HarryAnim_RunRightWallStop, false))
            {
                airScreamer->model_0.stateStep_3             = AirScreamerStateStep_2;
                airScreamer->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            }
            break;

        case 2:
            if (animStatus != ANIM_STATUS(HarryAnim_RunForwardWallStopLeft, true) &&
                animStatus != ANIM_STATUS(HarryAnim_RunRightWallStop, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800D5E14_0_s01(airScreamer);
    Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f));

    if (cond)
    {
        airScreamer->model_0.controlState_2 = AirScreamerControl_2;
        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

        airScreamerProps.field_E8_8 = 1;
    }
#endif
}

void Ai_AirScreamerControl_33(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32  animStatus;
    s32  switchCond;
    s32  sp10;
    bool cond;
    bool field14C_0;
    bool field14C_1;
    bool field14C_2;
    bool field14C_0_tmp;
    bool field14C_1_tmp;
    bool field14C_2_tmp;
    s32  temp_s4;
    s32  distFieldF8;
    s32  angleDiff;

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;
    sp10       = sharedFunc_800D4A80_0_s01(airScreamer);
    cond       = 0;

    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;

    field14C_0 = field14C_0_tmp;
    field14C_1 = field14C_1_tmp;
    field14C_2 = field14C_2_tmp;

    temp_s4 = sharedFunc_800DC438_2_s00(airScreamer);

    switch (airScreamer->model_0.stateStep_3)
    {
        case 64:
            sharedFunc_800DD534_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case 0:
            cond = true;

            airScreamerProps.timer_120 = Q12(5.0f);
            sharedFunc_800DEC84_2_s00(airScreamer, Q12(6.0f), airScreamer->rotation_24.vy);
            sharedFunc_800DECA4_2_s00(airScreamer, &airScreamerProps.targetPosition_F8, Q12(5.0f));

            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;

        case 1:
            distFieldF8 = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            angleDiff   = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);

            if (temp_s4 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (temp_s4 == 1 || (sharedFunc_800DC30C_2_s00(airScreamer) &&
                                      cond == true &&
                                      airScreamerProps.flags_11C & AirScreamerFlag_31 &&
                                      (distFieldF8 < Q12(2.0f) || Math_CheckSignedRange(angleDiff, FP_ANGLE(60.0f)))))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (sharedFunc_800DC3BC_2_s00(airScreamer) &&
                     cond == true &&
                     distFieldF8 < Q12(4.0f) &&
                     (angleDiff >= FP_ANGLE(-30.0f) && angleDiff <= FP_ANGLE(30.0f)) &&
                     Rng_TestProbability(Q12(0.7f)))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f) || distFieldF8 < Q12(3.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                           = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(16, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;
            }
            break;

        case 3:
            switchCond = 1;
            break;

        case 4:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(15, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case 5:
            switchCond = 2;
            break;

        case 65:
            sharedFunc_800DDA80_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case 66:
            sharedFunc_800DD588_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case 67:
            sharedFunc_800DD834_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            airScreamerProps.flags_11C      |= AirScreamerFlag_12;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 0, 1);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (field14C_1 | field14C_0 | field14C_2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_35;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (sp10 == 1)
                    {
                        if (!(field14C_1 | field14C_0 | field14C_2))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_4;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    break;

                case 2:
                    if (sp10 == 2)
                    {
                        if (!(field14C_1 | field14C_0 | field14C_2))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_18;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_45;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            if (airScreamer->health_B0 <= 0)
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_34(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    animStatus;
    s32    switchCond;
    s32    sp10;
    bool   cond;
    bool   field14C_0;
    bool   field14C_1;
    bool   field14C_2;
    bool   field14C_0_tmp;
    bool   field14C_1_tmp;
    bool   field14C_2_tmp;
    s32    temp_s4;
    q19_12 distFieldF8;
    q19_12 angFieldF8;

    animStatus     = airScreamer->model_0.anim_4.status_0;
    switchCond     = 0;
    sp10           = sharedFunc_800D4A80_0_s01(airScreamer);
    cond           = false;
    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    field14C_0     = field14C_0_tmp;
    field14C_1     = field14C_1_tmp;
    field14C_2     = field14C_2_tmp;
    temp_s4        = sharedFunc_800DC438_2_s00(airScreamer);

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            cond                       = 1;
            airScreamerProps.timer_120 = Q12(5.0f);
            sharedFunc_800DECC4_2_s00(airScreamer);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;

        case 1:
            distFieldF8 = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            angFieldF8  = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);
            if (temp_s4 == 2)
            {
                airScreamer->model_0.stateStep_3 = temp_s4;
            }
            else if (temp_s4 == 1 ||
                     (sharedFunc_800DC30C_2_s00(airScreamer) && cond == true &&
                      airScreamerProps.flags_11C & AirScreamerFlag_31 &&
                      (distFieldF8 < Q12(2.0f) || Math_CheckSignedRange(angFieldF8, FP_ANGLE(60.0f))))) // @hack Should be `angFieldF8 >= FP_ANGLE(-60.0f) && angFieldF8 < FP_ANGLE(60.0f)`
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (sharedFunc_800DC3BC_2_s00(airScreamer) && cond == true && distFieldF8 < Q12(4.0f) &&
                     (angFieldF8 >= FP_ANGLE(-30.0f) && angFieldF8 <= FP_ANGLE(30.0f)) && Rng_TestProbability(Q12(0.7f)))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f) || distFieldF8 < Q12(2.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                           = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;
            }
            break;

        case 3:
            switchCond = 1;
            break;

        case 4:
            if (animStatus == ANIM_STATUS(17, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case 5:
            switchCond = 2;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 0, 1);
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if ((field14C_1 | field14C_0 | field14C_2) != 0)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_35;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    if (sp10 == switchCond)
                    {
                        airScreamer->model_0.controlState_2 = (field14C_1 | field14C_0 | field14C_2) ? 6 : 5;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (sp10 == switchCond)
                    {
                        airScreamer->model_0.controlState_2 = (field14C_1 | field14C_0 | field14C_2) ? 20 : 19;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_45;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_35(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32  temp_a0;
    s32  temp_a1;
    s32  temp_s3;
    s32  temp_s4;
    s32  temp_s5;
    s32  temp_s6;
    s32  temp_s7;
    s32  var_a0;
    s32  var_a1;
    s32  unkAngleDelta;
    s32  var_s1;
    s32  animStatus;
    bool new_var;
    bool new_var2;
    bool new_var3;

    animStatus = airScreamer->model_0.anim_4.status_0;

    var_s1 = 0;

    temp_s7 = sharedFunc_800D4A80_0_s01(airScreamer);

    temp_s6 = sharedData_800E21D0_0_s01.field_15C;

    new_var  = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var2 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    new_var3 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;

    temp_s5 = new_var3;
    temp_s4 = new_var;
    temp_s3 = new_var2;

    temp_a0 = sharedFunc_800DC438_2_s00(airScreamer);
    var_a1  = 0;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            airScreamerProps.timer_120 = Q12(6.0f);

        case AirScreamerStateStep_1:
            sharedFunc_800DECA4_2_s00(airScreamer, &airScreamerProps.position_104, Q12(2.0f));

            if (sharedFunc_800DC30C_2_s00(airScreamer) && Rng_TestProbability(Q12(0.1f)))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_8;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            break;

        case AirScreamerStateStep_2:
            var_a1 = 1;

        case AirScreamerStateStep_3:
            if (temp_a0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else
            {
                if (temp_a0 == 1)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_8;
                }
                else if (airScreamerProps.timer_120 == Q12(0.0f))
                {
                    if (var_a1 != 0)
                    {
                        var_s1 = 1;
                    }
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                }
                else if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(1.0f))
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
                }
                else if (temp_s5 || temp_s4 || temp_s3)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                    if (temp_s6 >= 33)
                    {

                        unkAngleDelta = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.position_104) - airScreamer->rotation_24.vy);
                        if (unkAngleDelta < FP_ANGLE(0.0f))
                        {
                            unkAngleDelta += FP_ANGLE(0.3f);
                        }

                        sharedFunc_800DEC84_2_s00(airScreamer, Q12(2.0f), (unkAngleDelta >> 2) + airScreamer->rotation_24.vy);
                        airScreamerProps.timer_120 = Q12(6.0f);
                    }
                }
            }
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                var_s1                               = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);

                if (!temp_s3 && !temp_s4)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_6;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
                }
            }
            else if (temp_s3 || temp_s4)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                var_s1                               = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_7;
            }
            break;

        case AirScreamerStateStep_6:
            if (temp_s3 || temp_s4)
            {
                var_s1                           = 3;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
            }
            else
            {
                var_s1 = 2;
            }
            break;

        case AirScreamerStateStep_7:
            var_s1 = 3;
            break;

        case AirScreamerStateStep_8:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                var_s1                               = 4;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);

                if (!temp_s3 && !temp_s4)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_10;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_11;
                }
            }
            else if (temp_s3 || temp_s4)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_9;
            }
            break;

        case AirScreamerStateStep_9:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                var_s1                               = 5;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_11;
            }
            break;

        case AirScreamerStateStep_10:
            if (temp_s3 || temp_s4)
            {
                var_s1                           = 5;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_11;
            }
            else
            {
                var_s1 = 4;
            }
            break;

        case AirScreamerStateStep_11:
            var_s1 = 5;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 0, 2);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (var_s1)
            {
                case 0:
                case 1:
                    if (!temp_s3 && !temp_s4)
                    {
                        if (var_s1 == 1)
                        {
                            temp_a1 = Rng_RandQ12();

                            if (airScreamerProps.field_E8_8 == var_s1)
                            {
                                var_a0 = Q12(0.1f);
                            }
                            else
                            {
                                var_a0 = 0;
                            }

                            if (temp_a1 < (Q12(0.7f) - (var_a0 * 2)))
                            {
                                airScreamer->model_0.controlState_2 = AirScreamerControl_43;
                                airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                            }
                        }
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_36;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (temp_s7 == 1)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 3:
                    if (temp_s7 == 1)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 4:
                    if (temp_s7 == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 5:
                    if (temp_s7 == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_45;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_36(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32  animStatus;
    s32  switchCond;
    s32  temp_fp;
    s32  field15C;
    bool field14C_0;
    bool field14C_1;
    bool field14C_2;
    bool field14C_0_tmp;
    bool field14C_1_tmp;
    bool field14C_2_tmp;
    bool cond;
    s32  temp_a0;

    animStatus     = airScreamer->model_0.anim_4.status_0;
    switchCond     = 0;
    temp_fp        = sharedFunc_800D4A80_0_s01(airScreamer);
    field15C       = sharedData_800E21D0_0_s01.field_15C;
    field14C_0_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    field14C_1_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;

    field14C_0 = field14C_0_tmp;
    field14C_1 = field14C_1_tmp;
    field14C_2 = field14C_2_tmp;

    cond    = false;
    temp_a0 = sharedFunc_800DC438_2_s00(airScreamer);

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            if (sharedFunc_800DC30C_2_s00(airScreamer) && Rng_TestProbability(Q12(0.1f)))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_8;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }

        case AirScreamerStateStep_1:
            airScreamerProps.timer_120 = Q12(6.0f);
            sharedFunc_800DECA4_2_s00(airScreamer, &airScreamerProps.position_104, Q12(3.0f));
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            break;

        case AirScreamerStateStep_2:
            cond = true;

        case AirScreamerStateStep_3:
            if (temp_a0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (temp_a0 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_8;
            }
            else if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(1.0f))
            {
                if (cond)
                {
                    switchCond = 1;
                }

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else if (field14C_2 || field14C_0 || field14C_1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;

                if (field15C > 32)
                {
                    q19_12 angleDiff = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.position_104) - airScreamer->rotation_24.vy);
                    sharedFunc_800DEC84_2_s00(airScreamer, Q12(3.0f), (angleDiff / 4) + airScreamer->rotation_24.vy);
                    airScreamerProps.timer_120 = Q12(6.0f);
                }
            }
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);

                if (!field14C_1 && !field14C_0)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_6;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
                }
            }
            else if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                           = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_7;
            }
            break;

        case AirScreamerStateStep_6:
            switchCond = 3;

            if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
            }
            else
            {
                switchCond = 2;
            }
            break;

        case AirScreamerStateStep_7:
            switchCond = 3;
            break;

        case AirScreamerStateStep_8:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                           = 4;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);

                if (!field14C_1 && !field14C_0)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_10;
                }
                else
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_11;
                }
            }
            else if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_9;
            }
            break;

        case AirScreamerStateStep_9:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                           = 5;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_11;
            }
            break;

        case AirScreamerStateStep_10:
            switchCond = 5;

            if (field14C_2 || field14C_1 || field14C_0)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_11;
            }
            else
            {
                switchCond = 4;
            }
            break;

        case AirScreamerStateStep_11:
            switchCond = 5;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 1, 1);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            switch (switchCond)
            {
                case 0:
                case 1:
                    if (field14C_2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_37;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    else if (switchCond == 1)
                    {
                        s32 rand   = Rng_RandQ12();
                        s32 var_a0 = 0;

                        if (airScreamerProps.field_E8_8 == 1)
                        {
                            var_a0 = Q12(0.1f);
                        }

                        if (rand < (Q12(0.7f) - (var_a0 * 2)))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_35;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    break;

                case 2:
                    if (temp_fp == 1)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_8;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_6;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    break;

                case 3:
                    if (temp_fp == 1)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_8;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_7;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    break;

                case 4:
                    if (temp_fp == 2)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_22;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_20;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    break;

                case 5:
                    if (temp_fp == 2)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_22;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_21;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        }
                    }
                    break;
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_45;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_37(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    temp_a0;
    q19_12 chance1;
    q19_12 dist;
    s32    temp_s4;
    bool   field14C;
    q19_12 angle;
    s32    switchCond;
    q19_12 chance0;
    s32    animStatus;
    s32    new_var;

    switchCond = 0;
    animStatus = airScreamer->model_0.anim_4.status_0;
    new_var    = sharedFunc_800D4A80_0_s01(airScreamer);
    dist       = sharedData_800E21D0_0_s01.distance_150;
    angle      = sharedData_800E21D0_0_s01.angle_154;
    field14C   = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    temp_s4    = new_var;
    temp_a0    = sharedFunc_800DC438_2_s00(airScreamer);

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            switchCond                 = 1;
            airScreamerProps.timer_120 = Q12(2.0f);
            airScreamer->flags_3E     |= CharaFlag_Unk3;

        case AirScreamerStateStep_1:
            sharedFunc_800DECA4_2_s00(airScreamer, &airScreamerProps.position_104, Q12(4.0f));
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            break;

        case AirScreamerStateStep_2:
            if (temp_a0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            else if (temp_a0 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            else if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(1.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_3:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_4:
            switchCond = 2;
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                           = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_6;
            }
            break;

        case AirScreamerStateStep_6:
            switchCond = 3;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 2, 0);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            switch (switchCond)
            {
                case 0:
                    if (!field14C)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_36;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (temp_s4 == 1)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_8;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 3:
                    if (temp_s4 == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_22;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 1:
                    chance0 = sharedFunc_800DC894_2_s00(airScreamer, dist);

                    chance1 = sharedFunc_800DC6E4_2_s00(airScreamer, dist);
                    if (FP_ANGLE_NORM_S(angle - airScreamer->rotation_24.vy) >= FP_ANGLE(-22.5f) &&
                        FP_ANGLE_NORM_S(angle - airScreamer->rotation_24.vy) < FP_ANGLE(22.5f) &&
                        dist > Q12(4.0f) && dist < Q12(8.0f))
                    {
                        chance0 += Q12(0.2f);
                    }

                    if (Rng_TestProbability(chance0))
                    {
                        if (airScreamerProps.field_E8_0 == 3)
                        {
                            sharedFunc_800DD13C_2_s00(airScreamer, airScreamer->field_40 + 1, Q12(0.6f));
                        }

                        airScreamer->model_0.controlState_2 = AirScreamerControl_38;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        airScreamerProps.flags_11C         |= AirScreamerFlag_4;
                    }
                    else if (Rng_TestProbability(chance1))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_42;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        airScreamerProps.flags_11C         |= AirScreamerFlag_4;
                    }
                    break;
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_45;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_38(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32           sp10;
    s32           temp_s0;
    s32           temp_s0_2;
    s32           temp_s0_4;
    s32           stateStep;
    s32           temp_s5;
    s32           temp_v0;
    s32           temp_v1_2;
    s32           var_s4;
    s32           temp_s7;
    s32           var_v0_2;
    bool          new_var;
    s32           temp_s6;
    s_PlayerWork* playerWork;

    temp_s7 = airScreamer->model_0.anim_4.status_0;
    var_s4  = 0;

    temp_v0 = sharedFunc_800D4A80_0_s01(airScreamer);

    new_var = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    temp_s0 = sharedData_800E21D0_0_s01.distance_150;
    sp10    = new_var;

    stateStep = sharedFunc_800DC438_2_s00(airScreamer);
    temp_s6   = sharedFunc_800DEE24_2_s00(airScreamer);

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            temp_s0_2 = temp_s0 + (Rng_RandQ12() * 4);

            if (!sharedFunc_800DC30C_2_s00(airScreamer) || temp_s0_2 >= Q12(3.0f) || Rng_RandQ12() >= 0x333)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            airScreamer->properties_E4.dummy.properties_E8[14].val32 = Q12(4.0f);
            break;

        case 1:
            temp_s5   = airScreamer->properties_E4.dummy.properties_E8[5].val32 - airScreamer->position_18.vy;
            temp_s0_4 = Math_Distance2dGet(&airScreamer->position_18, (VECTOR3*)&airScreamer->properties_E4.dummy.properties_E8[4]);
            temp_v1_2 = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, (VECTOR3*)&airScreamer->properties_E4.dummy.properties_E8[4]) - airScreamer->rotation_24.vy);

            if (stateStep == AirScreamerStateStep_2)
            {
                airScreamer->model_0.stateStep_3 = stateStep;
            }
            else if (stateStep == AirScreamerStateStep_1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if ((temp_s5 >= -0x333 && temp_s5 <= 0x333) &&
                     (temp_s6 > 0x599 && temp_s6 < 0x8CD) &&
                     (temp_v1_2 >= -0x80 && temp_v1_2 <= 0x80))
            {
                var_s4 = 1;
            }
            else
            {
                // @hack This check should be `if ((temp_v1_2 >= -0x400 && temp_v1_2 < 0x400) && temp_s0_4 < Q12(4.0f))`,
                if (Math_CheckSignedRange(temp_v1_2, 0x400) && (temp_s0_4 < Q12(4.0f)))
                {
                    var_s4 = 2;
                }
                else if (airScreamer->properties_E4.dummy.properties_E8[14].val32 == 0)
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                }
            }
            break;

        case 2:
            if (temp_s7 == 35)
            {
                var_s4                               = 3;
                airScreamer->model_0.anim_4.status_0 = 32;
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;
            }
            break;

        case 3:
            var_s4 = 3;
            break;

        case 4:
            if (temp_s7 == 35)
            {
                var_s4                               = 4;
                airScreamer->model_0.anim_4.status_0 = 30;
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case 5:
            var_s4 = 4;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 2, 0);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (var_s4)
            {
                case 0:
                case 2:
                    if (!sharedFunc_800DC67C_2_s00(airScreamer))
                    {
                        var_v0_2 = 41;
                        if (sp10 != 0)
                        {
                            if (var_s4 == 2)
                            {
                                airScreamer->model_0.controlState_2 = AirScreamerControl_39;
                                airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                            }
                            break;
                        }
                    }
                    else
                    {
                        var_v0_2 = 42;
                    }

                    airScreamer->model_0.controlState_2 = var_v0_2;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    break;

                case 1:
                    playerWork = &g_SysWork.playerWork_4C;

                    if (!((u16)playerWork->player_0.flags_3E & 8) &&
                        (g_SysWork.npcIdxs_2354[0] == NO_VALUE && g_SysWork.npcIdxs_2354[1] == NO_VALUE) &&
                        temp_s7 == 0x23)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_40;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 3:
                    if (temp_v0 == 1)
                    {
                        sharedFunc_800DE11C_2_s00(airScreamer);
                        airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 4:
                    if (temp_v0 == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2                       = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3                          = AirScreamerStateStep_0;
            airScreamer->properties_E4.dummy.properties_E8[13].val32 |= 8;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_45;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            if (airScreamer->health_B0 <= 0)
            {
                airScreamer->properties_E4.dummy.properties_E8[13].val32 |= 1 << 6;
            }
            else
            {
                airScreamer->properties_E4.dummy.properties_E8[13].val32 |= 8;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_39(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32  sp10;
    s32  temp_a0;
    s32  temp_s0_2;
    s32  temp_s3;
    s32  temp_s5;
    s32  temp_s7;
    s32  temp_v0;
    s32  var_s4;
    s32  temp_s6;
    bool new_var;
    s32  temp_s8;

    temp_s6 = airScreamer->model_0.anim_4.status_0;
    var_s4  = 0;
    temp_v0 = sharedFunc_800D4A80_0_s01(airScreamer);
    new_var = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    sp10    = new_var;

    temp_s5   = sharedData_800E21D0_0_s01.distance_150;
    temp_s7   = sharedData_800E21D0_0_s01.angle_154;
    temp_s8   = temp_v0;
    temp_s3   = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
    temp_s0_2 = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);
    temp_a0   = sharedFunc_800DC438_2_s00(airScreamer);

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            sharedFunc_800DF24C_2_s00(airScreamer);
            Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);

            if (temp_s5 > Q12(6.0f))
            {
                temp_s3 = Q12(6.0f);
            }
            else if (temp_s5 > Q12(2.0f))
            {
                temp_s3 = Q12(12.0f) - temp_s5;
            }
            else
            {
                temp_s3 = Q12(10.0f);
            }

            temp_s3  += Rng_RandQ12() * 2;
            temp_s0_2 = FP_ANGLE_NORM_S((temp_s7 + 0x800) - airScreamer->rotation_24.vy) / 2 + airScreamer->rotation_24.vy;

            sharedFunc_800DEC84_2_s00(airScreamer, temp_s3, temp_s0_2 + (Rng_RandQ12() - 0x800) / 8);
            airScreamerProps.timer_120       = Q12(5.0f);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case 1:
            if (temp_a0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (temp_a0 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (temp_s3 < Q12(2.0f) || Math_CheckSignedRange(temp_s0_2, 0x400) ||
                     airScreamerProps.timer_120 == Q12(0.0f))
            {
                var_s4 = 1;
            }
            break;

        case 2:
            if (temp_s6 == 35)
            {
                var_s4                               = 2;
                airScreamer->model_0.anim_4.status_0 = 32;
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;
            }
            break;

        case 3:
            var_s4 = 2;
            break;

        case 4:
            if (temp_s6 == 35)
            {
                var_s4                               = 3;
                airScreamer->model_0.anim_4.status_0 = 30;
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case 5:
            var_s4 = 3;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 2, 0);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (var_s4)
            {
                case 0:
                case 1:
                    if (sp10 != 0)
                    {
                        if (temp_s5 > Q12(7.0f))
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_38;
                            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                            break;
                        }
                    }

                    if (var_s4 == 1)
                    {
                        if (airScreamerProps.field_E8_8 != 3)
                        {
                            airScreamerProps.field_E8_8 = 2;
                        }
                        airScreamer->model_0.controlState_2 = AirScreamerControl_41;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (temp_s8 == 1)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_13;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 3:
                    if (temp_s8 == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_26;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;
        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= 8;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_45;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_40(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    bool cond0;
    bool cond1;
    s32  animStatus;

    cond0 = false;
    cond1 = false;

    // Handle state step.
    animStatus = airScreamer->model_0.anim_4.status_0;
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;

        case AirScreamerStateStep_1:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_3, false);
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_3, true) &&
                airScreamer->model_0.anim_4.keyframeIdx_8 < 8192)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                airScreamerProps.flags_11C      |= AirScreamerFlag_5;
            }
            break;

        case AirScreamerStateStep_3:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                cond0 = true;
            }
            else if (airScreamer->field_44.field_8 == NO_VALUE)
            {
                cond0                            = true;
                cond1                            = true;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                cond0 = true;
                cond1 = true;
            }
            break;
    }

    sharedFunc_800DEE24_2_s00(airScreamer);
    sharedFunc_800E0514_2_s00(airScreamer);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.2f)))
    {
        case AirScreamerDamage_None:
            if (cond0)
            {
                if (airScreamerProps.field_E8_8 == 5 && cond1)
                {
                    airScreamerProps.field_E8_8         = 1;
                    airScreamer->model_0.controlState_2 = AirScreamerControl_42;
                }
                else
                {
                    airScreamer->model_0.controlState_2 = AirScreamerControl_39;
                }

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_45;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_41(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    animStatus;
    s32    switchCond;
    s32    temp_s6;
    s32    temp_s6_tmp;
    bool   field14C_2;
    bool   field14C_2_tmp;
    s32    temp_s4;
    q19_12 unkDist;
    q19_12 unkDeltaAngle;

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;

    // @hack Weird variable juggling needed for match, is there another way to do this?
    temp_s6_tmp    = sharedFunc_800D4A80_0_s01(airScreamer);
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    temp_s6        = temp_s6_tmp;
    field14C_2     = field14C_2_tmp;
    temp_s4        = sharedFunc_800DC438_2_s00(airScreamer);

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            sharedFunc_800DF22C_2_s00(airScreamer);

        case AirScreamerStateStep_1:
            airScreamerProps.timer_120       = Q12(4.0f);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            break;

        case AirScreamerStateStep_2:
            unkDist       = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            unkDeltaAngle = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);

            if (temp_s4 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
            }
            else if (temp_s4 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
            }
            else if (unkDist < Q12(0.5f))
            {
                if (sharedFunc_800DC30C_2_s00(airScreamer) && Rng_TestProbability(Q12(0.3f)))
                {
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_5;
                }
                else
                {
                    switchCond = 1;
                }
            }
            else if (unkDist < Q12(4.0f) && Math_CheckSignedRange(unkDeltaAngle, FP_ANGLE(90.0f))) // @hack Should be `angFieldF8 >= FP_ANGLE(-90.0f) && angFieldF8 < FP_ANGLE(90.0f)`
            {
                switchCond = 2;
            }

            if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                sharedFunc_800DECA4_2_s00(airScreamer, &airScreamerProps.position_104, Q12(2.5f));
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_3:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                           = 3;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_4:
            switchCond = 3;
            break;

        case AirScreamerStateStep_5:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                           = 4;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_6;
            }
            break;

        case AirScreamerStateStep_6:
            switchCond = 4;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 1, 0);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            switch (switchCond)
            {
                case AirScreamerDamage_None:
                case AirScreamerDamage_1:
                case AirScreamerDamage_2:
                    if (sharedFunc_800DC67C_2_s00(airScreamer))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_42;
                    }
                    else if (field14C_2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_38;
                    }
                    else if (switchCond == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_39;
                    }
                    else if (switchCond == 1)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_36;
                    }
                    else
                    {
                        break;
                    }

                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    break;

                case AirScreamerDamage_3:
                    if (temp_s6 == 1)
                    {
                        if (!field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_13;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_10;
                        }
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;

                case AirScreamerDamage_4:
                    if (temp_s6 == 2)
                    {
                        if (field14C_2)
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_23;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = AirScreamerControl_26;
                        }
                        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_45;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_42(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    temp_a0;
    bool   field14C;
    s32    angleDelta;
    q19_12 angle;
    q19_12 dist;
    s32    temp_s7;
    s32    switchCond;
    q19_12 var_s3;
    s32    var_s5; // Possibly `bool`
    s32    animStatus;
    s32    new_var;

    animStatus = airScreamer->model_0.anim_4.status_0;
    switchCond = 0;
    new_var    = sharedFunc_800D4A80_0_s01(airScreamer);
    dist       = sharedData_800E21D0_0_s01.distance_150;
    angle      = sharedData_800E21D0_0_s01.angle_154;
    field14C   = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    temp_s7    = new_var;
    var_s3     = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
    temp_a0    = sharedFunc_800DC438_2_s00(airScreamer);
    var_s5     = 0;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            var_s5     = sharedFunc_800DF24C_2_s00(airScreamer);
            var_s3     = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            angleDelta = FP_ANGLE_NORM_S(angle - airScreamer->rotation_24.vy);
            if (!sharedFunc_800DC30C_2_s00(airScreamer) || (angleDelta < FP_ANGLE(-30.0f) || angleDelta >= FP_ANGLE(30.0f)))
            {
                airScreamerProps.timer_120       = Q12(2.0f);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_1:
            if (temp_a0 == 2)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
            }
            else if (temp_a0 == 1)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            else if (var_s3 < Q12(2.0f) || (airScreamerProps.flags_11C & AirScreamerFlag_31))
            {
                var_s5 = sharedFunc_800DF24C_2_s00(airScreamer);
            }
            else if (airScreamerProps.timer_120 == Q12(0.0f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                           = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_16, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;
            }
            break;

        case AirScreamerStateStep_3:
            switchCond = 1;
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_17, true))
            {
                switchCond                           = 2;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;
            }
            break;

        case AirScreamerStateStep_5:
            switchCond = 2;
            break;
    }

    sharedFunc_800E021C_2_s00(airScreamer, 2, 0);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            switch (switchCond)
            {
                case 0:
                    if (var_s5 || (((field14C != 0 && dist < Q12(15.0f)) || dist < Q12(4.0f)) && var_s3 < Q12(1.5f)))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_38;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                        airScreamerProps.field_E8_8         = 3;
                        airScreamerProps.flags_11C         |= AirScreamerFlag_4;
                    }
                    else if (dist > Q12(30.0f) && var_s3 < Q12(1.0f))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_36;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    return;

                case 1:
                    if (temp_s7 == 1)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_14;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;

                case 2:
                    if (temp_s7 == 2)
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_27;
                        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    }
                    break;
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_45;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_43(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    sharedFunc_800DEC84_2_s00(airScreamer, Q12(0.5f), airScreamer->rotation_24.vy);
    sharedFunc_800E021C_2_s00(airScreamer, 1, 1);
    airScreamer->flags_3E &= ~CharaFlag_Unk3;

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            // @hack Explicit `u32` cast needed for match.
            switch ((u32)airScreamerProps.field_E8_0)
            {
                case 0:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_33;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    break;

                case 1:
                case 3:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_34;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                    break;
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_44;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_45;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

// Very similar to `Ai_AirScreamerControl_16`, changes here should be copied there.
void Ai_AirScreamerControl_44(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    s32    animStatus;
    bool   field14C_2;
    bool   field14C_2_tmp;
    bool   cond;
    s32    var_a0;
    q19_12 var_s1;

    animStatus             = airScreamer->model_0.anim_4.status_0;
    field14C_2_tmp         = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    airScreamer->flags_3E |= CharaFlag_Unk3;
    field14C_2             = field14C_2_tmp;
    cond                   = false;

    // Handle state step. @hack Explicit `u32` cast needed for match.
    switch ((u32)airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_8, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_1:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_8, false))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                airScreamerProps.flags_11C      |= AirScreamerFlag_3;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_8, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800E041C_2_s00(airScreamer);

    // Handle damage.
    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f)))
    {
        case AirScreamerDamage_None:
        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            if (!cond)
            {
                break;
            }

            var_s1 = airScreamerProps.field_E8_4 ? Q12(0.1f) : Q12(0.0f);

            if (airScreamerProps.field_E8_0 == 3)
            {
                sharedFunc_800DD13C_2_s00(airScreamer, airScreamer->field_40 + 1, Q12(0.7f));
            }

            if (field14C_2)
            {
                if (airScreamerProps.field_E8_8 == 5)
                {
                    airScreamer->model_0.controlState_2 = AirScreamerControl_42;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                    if (Rng_TestProbability(Q12_DIV(airScreamer->health_B0, Q12(380.0f)) + (var_s1 * 2)))
                    {
                        airScreamerProps.field_E8_8 = 3;
                    }
                    break;
                }
                else
                {
                    airScreamer->model_0.controlState_2 = AirScreamerControl_38;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                    // TODO: Can `Rng_TestProbability` fit?
                    if (Rng_RandQ12() <= (Q12_DIV(airScreamer->health_B0, Q12(380.0f)) + (var_s1 * 2)))
                    {
                        airScreamerProps.field_E8_8 = 3;
                    }
                    else
                    {
                        airScreamerProps.field_E8_8 = 5;
                    }
                }
                break;
            }

            switch (airScreamerProps.field_E8_8)
            {
                case 3:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_41;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                    if (Rng_TestProbability(((Q12(0.5f) - (var_s1 * 3)))))
                    {
                        airScreamerProps.field_E8_8 = 2;
                    }
                    break;

                case 2:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_36;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                    if (Rng_RandQ12() > (Q12_DIV(airScreamer->health_B0, Q12(380.0f)) + (var_s1 * 2)))
                    {
                        airScreamerProps.field_E8_8 = 5;
                    }
                    else if (Rng_TestProbability(Q12(0.3f) + (var_s1 * 3)))
                    {
                        airScreamerProps.field_E8_8 = 3;
                    }
                    break;

                case 5:
                    airScreamer->model_0.controlState_2 = AirScreamerControl_42;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

                    if (Rng_TestProbability(Q12_DIV(airScreamer->health_B0, Q12(380.0f))))
                    {
                        airScreamerProps.field_E8_8 = 3;
                    }
                    break;

                case 1:
                case 4:
                    if (Rng_TestProbability(Q12(0.2f) + (var_s1 * 5)))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_36;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_42;
                    }

                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                    if (Rng_TestProbability(Q12(0.5f) + (var_s1 * 3)))
                    {
                        var_a0 = 2;
                    }
                    else
                    {
                        var_a0 = 5;
                    }

                    airScreamerProps.field_E8_8 = var_a0;
                    break;

                case 0:
                default:
                    if (airScreamerProps.field_E8_0 == 3)
                    {
                        var_s1 = Q12(1.0f);
                    }

                    if (Rng_TestProbability(Q12(0.4f) + (var_s1 * 3)))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_36;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_42;
                    }

                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

                    if (Rng_TestProbability(Q12(0.6f) + (var_s1 * 2)))
                    {
                        var_a0 = 2;
                    }
                    else
                    {
                        var_a0 = 5;
                    }

                    airScreamerProps.field_E8_8 = var_a0;
                    break;
            }
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_45;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_45(s_SubCharacter* airScreamer)
{
#ifndef MAP0_S01
    bool cond;
    s32  animStatus;

#define airScreamerFlags airScreamer->properties_E4.airScreamer

    cond       = false;
    animStatus = airScreamer->model_0.anim_4.status_0;

    airScreamer->flags_3E |= CharaFlag_Unk3;

    // Handle state step. TODO: Cast necessary?
    switch ((u32)airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_11, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_1:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_11, false))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                airScreamerFlags.flags_11C      |= AirScreamerFlag_3;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_11, true))
            {
                cond = true;
            }
            break;
    }

    if (sharedFunc_800D4A80_0_s01(airScreamer) == 3)
    {
        sharedFunc_800E04B0_2_s00(airScreamer);
    }
    else
    {
        sharedFunc_800D5638_0_s01(airScreamer);
    }

    Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f));

    if (cond)
    {
        airScreamer->model_0.controlState_2 = AirScreamerControl_2;
        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
        airScreamerFlags.field_E8_8         = 1;
    }
#endif
}

// Control 46+ are only included in MAP0_S01

void Ai_AirScreamerControl_46(s_SubCharacter* airScreamer)
{
#ifdef MAP0_S01
    s32 animStatus;

    animStatus = airScreamer->model_0.anim_4.status_0;

    if (airScreamer->model_0.stateStep_3 != AirScreamerStateStep_1)
    {
        if (airScreamer->model_0.stateStep_3 == AirScreamerStateStep_0 &&
            animStatus == ANIM_STATUS(AirScreamerAnim_2, true) &&
            airScreamer->model_0.anim_4.keyframeIdx_8 < 8204)
        {
            airScreamerProps.timer_120       = Q12(4.0f);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            airScreamerProps.flags_11C      |= AirScreamerFlag_5;
            airScreamer->flags_3E           |= CharaFlag_Unk3;
        }
    }
    else if (ANIM_STATUS(ANIM_STATUS_IDX_GET(animStatus), true) == ANIM_STATUS(AirScreamerAnim_19, true))
    {
        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
        airScreamerProps.timer_120       = Q12(4.0f);
    }

    sharedFunc_800D529C_0_s01(airScreamer, Q12(1.0f), func_80080478(&airScreamer->position_18, &g_SysWork.playerWork_4C.player_0.position_18));
    sharedFunc_800D598C_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            if (airScreamerProps.timer_120 == Q12(0.0f) ||
                airScreamer == &g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353] ||
                Math_Distance2dGet(&airScreamer->position_18, &g_SysWork.playerWork_4C.player_0.position_18) > Q12(6.5f))
            {
                airScreamer->model_0.controlState_2 = AirScreamerControl_47;
                airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                airScreamerProps.flags_11C         |= AirScreamerFlag_4;
            }
            break;

        default:
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_50;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_51;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_47(s_SubCharacter* airScreamer)
{
#ifdef MAP0_S01
    q19_12 dist0;
    q19_12 deltaY;
    q19_12 unkAngleDelta;
    q19_12 dist;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            airScreamerProps.timer_120       = Q12(1.5f);
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            break;

        case AirScreamerStateStep_1:
            if (Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) < Q12(0.5f))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;
    }

    sharedFunc_800D53AC_0_s01(airScreamer);
    sharedFunc_800D57C8_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            dist0  = NO_VALUE;
            deltaY = airScreamerProps.targetPosition_F8.vy - airScreamer->position_18.vy;
            if (deltaY > Q12(-0.2f) && deltaY < Q12(0.8f))
            {
                dist0 = airScreamer->field_D4.radius_0 + Q12(0.15f);
            }

            dist = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.targetPosition_F8);
            if (dist < dist0)
            {
                unkAngleDelta = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamerProps.targetPosition_F8) - airScreamer->rotation_24.vy);
                if (unkAngleDelta >= FP_ANGLE(-8.0f) && unkAngleDelta < FP_ANGLE(8.0f))
                {
                    airScreamer->model_0.controlState_2 = AirScreamerControl_49;
                    airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                }
            }
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_50;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= PlayerFlag_WallStopRight;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_51;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= PlayerFlag_Unk6;
            }
            else
            {
                airScreamerProps.flags_11C |= PlayerFlag_WallStopRight;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_48(s_SubCharacter* airScreamer)
{
#ifdef MAP0_S01
    if (!airScreamer->model_0.stateStep_3)
    {
        airScreamerProps.timer_120       = Q12(2.0f);
        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
    }

    sharedFunc_800D53AC_0_s01(airScreamer);
    sharedFunc_800D5B10_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case AirScreamerDamage_None:
            if (airScreamerProps.timer_120 == Q12(0.0f) ||
                Math_Distance2dGet(&airScreamer->position_18, &g_SysWork.playerWork_4C.player_0.position_18) > Q12(2.0f))
            {
                airScreamer->model_0.controlState_2 = AirScreamerControl_47;
                airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                break;
            }

        default:
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_50;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= PlayerFlag_WallStopRight;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_51;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= PlayerFlag_Unk6;
            }
            else
            {
                airScreamerProps.flags_11C |= PlayerFlag_WallStopRight;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_49(s_SubCharacter* airScreamer)
{
#ifdef MAP0_S01
    bool cond0;
    bool cond1;
    s32  animStatus;

    cond0      = false;
    animStatus = airScreamer->model_0.anim_4.status_0;
    cond1      = false;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;

        case AirScreamerStateStep_1:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_19, true))
            {
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_2;
                airScreamer->model_0.anim_4.status_0 = AirScreamerAnim_4;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_2, true) && airScreamer->model_0.anim_4.keyframeIdx_8 < 8192)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_3;
                airScreamerProps.flags_11C      |= PlayerFlag_Unk5;
            }
            break;

        case AirScreamerStateStep_3:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_19, true))
            {
                cond0 = true;
            }
            else if (airScreamer->field_44.field_8 == NO_VALUE)
            {
                cond0                            = true;
                cond1                            = true;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_4;
            }
            break;

        case AirScreamerStateStep_4:
            if (animStatus == ANIM_STATUS(AirScreamerAnim_19, true))
            {
                cond0 = true;
                cond1 = true;
            }
            break;
    }

    sharedFunc_800D53AC_0_s01(airScreamer);
    sharedFunc_800D5C90_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.2f)))
    {
        case AirScreamerDamage_None:
            if (cond0)
            {
                if (!cond1)
                {
                    if (Rng_RandQ12() >= FP_ANGLE(180.0f))
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_47;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = AirScreamerControl_48;
                    }
                }
                else
                {
                    airScreamer->model_0.controlState_2 = AirScreamerControl_48;
                }

                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
                break;
            }

        default:
            break;

        case AirScreamerDamage_1:
        case AirScreamerDamage_2:
            airScreamer->model_0.controlState_2 = AirScreamerControl_50;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
            airScreamerProps.flags_11C         |= AirScreamerFlag_3;
            break;

        case AirScreamerDamage_3:
        case AirScreamerDamage_4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_51;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
            break;
    }
#endif
}

void Ai_AirScreamerControl_50(s_SubCharacter* airScreamer)
{
#ifdef MAP0_S01
    s32  damageType;
    s32  animStatus;
    u32  stateStep;
    bool cond;

    stateStep  = airScreamer->model_0.stateStep_3;
    animStatus = airScreamer->model_0.anim_4.status_0;
    cond       = false;

    // Handle state step.
    switch (stateStep)
    {
        case AirScreamerStateStep_0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_7, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_1:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_7, false))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                airScreamerProps.flags_11C      |= AirScreamerFlag_3;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_7, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800D5D80_0_s01(airScreamer);

    // TODO: Switch?
    damageType = Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f));
    if (damageType >= 0)
    {
        if (damageType < 3)
        {
            if (cond)
            {
                airScreamer->model_0.controlState_2 = AirScreamerControl_47;
                airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
                airScreamerProps.field_E8_8         = 3;
            }
        }
        else if (damageType < 5)
        {
            airScreamer->model_0.controlState_2 = AirScreamerControl_51;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_6;
            }
            else
            {
                airScreamerProps.flags_11C |= AirScreamerFlag_3;
            }
        }
    }
#endif
}

void Ai_AirScreamerControl_51(s_SubCharacter* airScreamer)
{
#ifdef MAP0_S01
    s32  animStatus;
    u32  stateStep;
    bool cond;

    stateStep  = airScreamer->model_0.stateStep_3;
    animStatus = airScreamer->model_0.anim_4.status_0;
    cond       = false;

    // Handle state step.
    switch (stateStep)
    {
        case AirScreamerStateStep_0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_10, false);
                airScreamer->model_0.stateStep_3     = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_1:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_10, false))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                airScreamerProps.flags_11C      |= AirScreamerFlag_3;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_10, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800D5E14_0_s01(airScreamer);
    Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f));

    if (cond)
    {
        airScreamer->model_0.controlState_2 = AirScreamerControl_2;
        airScreamer->model_0.stateStep_3    = AirScreamerStateStep_0;
        airScreamerProps.field_E8_8         = 1;
    }
#endif
}

#undef airScreamerProps
