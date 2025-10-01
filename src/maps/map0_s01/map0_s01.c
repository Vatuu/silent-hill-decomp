#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/map0_s01.h"
const u32 D_800CA5C8[4] = {};

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800CCB8C);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800CD1F8);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CE000

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CE4C4

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CE59C

#include "maps/shared/Particle_Update.h" // 0x800CE8A8

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800CEB24_0_s00); // 0x800CEE2C

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CF2A4

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800CEFD0_1_s02); // 0x800CF3F4

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CF7BC

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CF8E8

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CF8F0

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CF9A8

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CFA30

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CFBE8

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CFD68

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CFE20

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CFFB8

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800CFFD8);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D0850);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D0C3C);

void func_800D16C4(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord) // 0x800D16C4
{
    s_Collision coll;
    VECTOR3     sp20;
    s32         headingAngle;
    s16         temp_v0;
    s32         temp_s0;
    s32         moveAmt;
    s32         temp_s2;
    s16         temp_s3;
    s32         scaleRestoreShift;
    u32         scaleReduceShift;
    s32         temp_v0_2;
    s32         temp_v0_3;
    s32         playerState;
    s32         moveSpeed;
    s32         var_a0;
    bool        cond;
    s16         var_s0;
    s16         var_v1;

    playerState = g_SysWork.player_4C.extra_128.state_1C;
    cond        = playerState < PlayerState_Unk58;

    if (playerState == PlayerState_Unk53)
    {
        cond = false;
    }

    if (cond)
    {
        Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);
        temp_s2 = FP_MULTIPLY(chara->moveSpeed_38, Math_Sin(chara->headingAngle_3C), Q12_SHIFT);
        temp_s0 = FP_MULTIPLY(chara->moveSpeed_38, Math_Cos(chara->headingAngle_3C), Q12_SHIFT);

        temp_s3 = Math_Cos(ABS(coll.field_4) >> 3); // `/ 8`.
        temp_v0 = Math_Cos(ABS(coll.field_6) >> 3); // `/ 8`.

        var_s0 = FP_MULTIPLY((FP_MULTIPLY(temp_s2, temp_s3, Q12_SHIFT)), temp_s3, Q12_SHIFT);
        var_v1 = FP_MULTIPLY((FP_MULTIPLY(temp_s0, temp_v0, Q12_SHIFT)), temp_v0, Q12_SHIFT);
    }
    else
    {
        var_s0 = FP_MULTIPLY(chara->moveSpeed_38, Math_Sin(chara->headingAngle_3C), Q12_SHIFT);
        var_v1 = FP_MULTIPLY(chara->moveSpeed_38, Math_Cos(chara->headingAngle_3C), Q12_SHIFT);
    }
    
    if (chara->moveSpeed_38 >= 0)
    {
        chara->moveSpeed_38 = SquareRoot0(SQUARE(var_s0) + SQUARE(var_v1));
    }
    else
    {
        chara->moveSpeed_38 = -SquareRoot0(SQUARE(var_s0) + SQUARE(var_v1));
    }

    moveSpeed    = chara->moveSpeed_38;
    headingAngle = chara->headingAngle_3C;
    moveAmt      = FP_MULTIPLY_PRECISE(moveSpeed, g_DeltaTime0, Q12_SHIFT);

    scaleRestoreShift = OVERFLOW_GUARD(moveAmt);
    scaleReduceShift = scaleRestoreShift >> 1;
       
    temp_v0_2 = Math_Sin(headingAngle) >> scaleReduceShift;
    temp_s0 = moveAmt >> scaleReduceShift;
    temp_s2 = FP_MULTIPLY_PRECISE(temp_s0, temp_v0_2, Q12_SHIFT);
    sp20.vx = temp_s2 << scaleRestoreShift;

    temp_v0_3 = Math_Cos(headingAngle) >> scaleReduceShift;
    temp_s2   = FP_MULTIPLY_PRECISE(temp_s0, temp_v0_3, Q12_SHIFT);
    sp20.vz   = temp_s2 << scaleRestoreShift;
    
    sp20.vy = FP_MULTIPLY_PRECISE(chara->field_34, g_DeltaTime0, Q12_SHIFT);

    if (cond)
    {
        func_80069B24(&D_800C4590.field_0, &sp20, chara);
        chara->position_18.vx += D_800C4590.field_0.vx;
        chara->position_18.vy += D_800C4590.field_0.vy;
        chara->position_18.vz += D_800C4590.field_0.vz;

        if (D_800C4590.field_14 == 0)
        {
            D_800C4590.field_C = chara->properties_E4.player.positionY_EC;
        }

        if ( chara->position_18.vy > D_800C4590.field_C)
        {
            chara->position_18.vy = D_800C4590.field_C;
            chara->field_34 = 0;
        }
    }
    else
    {
        chara->position_18.vx += sp20.vx;
        chara->position_18.vz += sp20.vz;
        playerState = g_SysWork.player_4C.extra_128.state_1C;

        if (playerState < PlayerState_Unk87 || (playerState >= PlayerState_Unk89 && playerState != PlayerState_Unk106))
        {
            chara->position_18.vy = Q12(0.0f);
        }

        chara->field_34 = 0;
    }

    if (g_DeltaTime0 == Q12(0.0f))
    {
        chara->rotationSpeed_2C.vy = FP_ANGLE(0.0f);
    } 
    else
    {
        chara->rotationSpeed_2C.vy = (sharedData_800E39D8_0_s00 << 8) / g_DeltaTime0;
    }

    coord->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coord->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coord->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);
}

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800D1B00

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800D1B3C

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800D1B48

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800D1CA8

s32 func_800D1E5C() // 0x800D1E5C
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D1E64

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D1F14

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D1F2C

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D1F54

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D1F6C

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800D1F94

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D2038

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D2048

void func_800D2054(void) // 0x800D2054
{
    g_SysWork.playerCombatInfo_38.equippedWeapon_F = EquippedWeaponId_Handgun;
    func_8003CD6C(&g_SysWork.playerCombatInfo_38);
    g_SysWork.playerCombatInfo_38.equippedWeapon_F = NO_VALUE;
    func_8003D03C();
}

void Player_FallBackward(void) // 0x800D2094
{
    s_MainCharacter*      player;
    s_MainCharacterExtra* extra;

    player = &g_SysWork.player_4C;

    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = Q12(2.3f);
    g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124       = FP_ANGLE(180.0f);
    g_Player_HeadingAngle                                                   = FP_ANGLE(180.0f);

    g_SysWork.player_4C.extra_128.state_1C = PlayerState_FallBackward;
    player->chara_0.model_0.stateStep_3 = 0;
    player->chara_0.model_0.state_2 = 0;

    extra = &g_SysWork.player_4C.extra_128;
    extra->model_0.stateStep_3 = 0;
    extra->model_0.state_2 = 0;

    g_SysWork.player_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
    g_SysWork.player_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;
}

void func_800D20E4() {}

void func_800D20EC() {}

void func_800D20F4() {}

s32 func_800D20FC() // 0x800D20FC
{
    return 0;
}

void func_800D2104() {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D210C

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D211C

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D215C

#include "maps/shared/Ai_AirScreamer_Update.h" // 0x800D2170

#include "maps/shared/sharedFunc_800D21E4_0_s01.h" // 0x800D21E4

#include "maps/shared/sharedFunc_800D2200_0_s01.h" // 0x800D2200

#include "maps/shared/sharedFunc_800D2274_0_s01.h" // 0x800D2274

#include "maps/shared/sharedFunc_800D2364_0_s01.h" // 0x800D2364

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D2390_0_s01); // 0x800D2390

#include "maps/shared/Ai_AirScreamer_Init.h" // 0x800D2974

#include "maps/shared/sharedFunc_800D2B00_0_s01.h" // 0x800D2B00

#include "maps/shared/sharedFunc_800D2B10_0_s01.h" // 0x800D2B10

#include "maps/shared/sharedFunc_800D2B28_0_s01.h" // 0x800D2B28

#include "maps/shared/sharedFunc_800D2B4C_0_s01.h" // 0x800D2B4C

#include "maps/shared/sharedFunc_800D2BB0_0_s01.h" // 0x800D2BB0

#include "maps/shared/sharedFunc_800D2BE4_0_s01.h" // 0x800D2BE4

#include "maps/shared/sharedFunc_800D2BF4_0_s01.h" // 0x800D2BF4

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D2C0C_0_s01); // 0x800D2C0C

#include "maps/shared/sharedFunc_800D2E04_0_s01.h" // 0x800D2E04

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D2FB4);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D31D0_0_s01); // 0x800D31D0

#include "maps/shared/sharedFunc_800D3430_0_s01.h" // 0x800D3430

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D3508_0_s01); // 0x800D3508

#include "maps/shared/sharedFunc_800D3630_0_s01.h" // 0x800D3630

#include "maps/shared/sharedFunc_800D3758_0_s01.h" // 0x800D3758

#include "maps/shared/sharedFunc_800D3814_0_s01.h" // 0x800D3814

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D3928_0_s01); // 0x800D3928

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D39F4);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D3A3C);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D3AC0);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedSymbol_800D3B0C_0_s01); // 0x800D3B0C

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CA9F0);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CA9F4);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CAA00);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CAA18);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CAA30);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CAA48);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", sharedData_800CAA98_0_s01);

#include "maps/shared/sharedFunc_800D3CC4_0_s01.h" // 0x800D3CC4

#include "maps/shared/sharedFunc_800D3DFC_0_s01.h" // 0x800D3DFC

void func_800D3EB8(s_SubCharacter* arg0)
{
    s32 deltaTime10;
    bool temp_s2;
    bool var_s1;
    s32 temp_s3;
    u32 animStatus;
    s32 animStatus12;
    s32 animStatusActive;
    u32 stateStep;

    animStatus = arg0->model_0.anim_4.status_0;
    animStatus12 = ANIM_STATUS(12, true);
    func_800D5638(arg0);
    animStatusActive = animStatus | 1;
    stateStep =  arg0->model_0.stateStep_3;

    switch (stateStep)
    {
        case 0:
            temp_s3 = func_800D5F00(arg0);
            var_s1 = 0;
            temp_s2 = arg0->position_18.vy >= Q12(8.0f);
            if (func_800808AC(arg0->position_18.vx, arg0->position_18.vz) == 7)
            {
                var_s1 = (arg0->position_18.vy >= func_80080884(arg0->position_18.vx, arg0->position_18.vz));
            }
            if (temp_s2)
            {
                sharedFunc_800D2C0C_0_s01(arg0, 0);
                arg0->position_18.vx = g_SysWork.player_4C.chara_0.position_18.vx + 0x64000;
                arg0->position_18.vz = g_SysWork.player_4C.chara_0.position_18.vz + 0x64000;
                sharedFunc_800D3DFC_0_s01(arg0);
                return;
            }
            if (var_s1)
            {
                sharedFunc_800D2C0C_0_s01(arg0, 0);
                sharedFunc_800D2364_0_s01(arg0);
                arg0->position_18.vx = g_SysWork.player_4C.chara_0.position_18.vx + 0x64000;
                arg0->position_18.vz = g_SysWork.player_4C.chara_0.position_18.vz + 0x64000;
                sharedFunc_800D3DFC_0_s01(arg0);
                return;
            }
            if (arg0->health_B0 <= 0)
            {
                sharedFunc_800D2C0C_0_s01(arg0, 0);
                if ((animStatus == ANIM_STATUS(26, true)) && (temp_s3 == 1))
                {
                    arg0->health_B0 = -1;
                    func_800622B8(3, arg0, 9, 2);
                    arg0->model_0.stateStep_3 = temp_s3;
                    sharedFunc_800D3DFC_0_s01(arg0);
                    return;
                }
            }
            else
            {
                arg0->flags_3E |= 2;
                if (sharedFunc_800D2C0C_0_s01(arg0, 0x1000) == 4)
                {
                    if (arg0->health_B0 <= 0)
                    {
                        arg0->model_0.anim_4.status_0 = ANIM_STATUS(5, false);
                        arg0->properties_E4.player.flags_11C |= PlayerFlag_Unk6;
                        return;
                    }
                    arg0->model_0.anim_4.status_0 = ANIM_STATUS(12, false);
                    arg0->model_0.stateStep_3 = 2;
                    arg0->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
                    return;
                }

                deltaTime10 = g_DeltaTime0 * 10;
                if (deltaTime10 < arg0->health_B0)
                {
                    arg0->health_B0 -= deltaTime10;
                    return;
                }
                if (arg0->health_B0 > 0)
                {
                    arg0->health_B0 = 0;
                    return;
                }
                return;
            }
            break;
        case 1:
            sharedFunc_800D2C0C_0_s01(arg0, 0);
            break;
        case 2:
            sharedFunc_800D2C0C_0_s01(arg0, 0x800);
            if (animStatusActive != animStatus12)
            {
                arg0->model_0.stateStep_3 = 0;
            }
            break;
        default:
            break;
    }
}

void func_800D4114() {}

void func_800D411C() {}

void func_800D4124() {}

void func_800D412C() {}

void func_800D4134() {}

void func_800D413C() {}

void func_800D4144() {}

void func_800D414C() {}

void func_800D4154() {}

void func_800D415C() {}

void func_800D4164() {}

void func_800D416C() {}

void func_800D4174() {}

void func_800D417C() {}

void func_800D4184() {}

void func_800D418C() {}

void func_800D4194() {}

void func_800D419C() {}

void func_800D41A4() {}

void func_800D41AC() {}

void func_800D41B4() {}

void func_800D41BC() {}

void func_800D41C4() {}

void func_800D41CC() {}

void func_800D41D4() {}

void func_800D41DC() {}

void func_800D41E4() {}

void func_800D41EC() {}

void func_800D41F4() {}

void func_800D41FC() {}

void func_800D4204() {}

void func_800D420C() {}

void func_800D4214() {}

void func_800D421C() {}

void func_800D4224() {}

void func_800D422C() {}

void func_800D4234() {}

void func_800D423C() {}

void func_800D4244() {}

void func_800D424C() {}

void func_800D4254() {}

void func_800D425C() {}

void func_800D4264() {}

void func_800D426C(s_SubCharacter* chara)
{
    s32 var_v0;
    u32 temp_v0_2;
    u8 temp_v0;
    s32 animStatus;

    animStatus = chara->model_0.anim_4.status_0;
    if (chara->model_0.stateStep_3 != 1)
    {
        if (chara->model_0.stateStep_3 == 0 && animStatus == ANIM_STATUS(2, true) && chara->model_0.anim_4.keyframeIdx_8 < 0x200C)
        {
            chara->properties_E4.unk0.properties_120.val32 = Q12(4.0f);
            chara->model_0.stateStep_3 = 1;
            chara->properties_E4.unk0.flags_11C |= 0x20;
            chara->flags_3E |= 4;
        }
    }
    else if ((animStatus | 1) == ANIM_STATUS(19, true))
    {
        chara->model_0.stateStep_3 = 2;
        chara->properties_E4.unk0.properties_120.val32 = Q12(4.0f);
    }

    func_800D529C(chara, 0x1000, func_80080478(&chara->position_18, &g_SysWork.player_4C.chara_0.position_18));
    func_800D598C(chara);

    switch (sharedFunc_800D2C0C_0_s01(chara, Q12(1.0f))) // Chara_TakeDamage(chara, mulitplier) ?
    {
        case 0:
            if (!chara->properties_E4.unk0.properties_120.val32 ||
                chara == &g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353] ||
                Math_Distance2dGet(&chara->position_18, &g_SysWork.player_4C.chara_0.position_18) > Q12(6.5f))
            {
                chara->model_0.state_2 = 47;
                chara->model_0.stateStep_3 = 0;
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk4;
                return;
            }
        default:
            return;
        case 1:
        case 2:
            chara->model_0.state_2 = 50;
            chara->model_0.stateStep_3 = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            return;
        case 3:
        case 4:
            chara->model_0.state_2 = 51;
            chara->model_0.stateStep_3 = 0;
            if (chara->health_B0 <= 0)
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }
}

void func_800D4420(s_SubCharacter* subChar)
{
    s32 dist0;
    s32 temp_v0;
    s32 temp_v0_2;

    s32 dist;

    switch (subChar->model_0.stateStep_3)
    {
        case 0:
            subChar->properties_E4.unk0.properties_120.val32 = Q12(1.5f);
            subChar->model_0.stateStep_3 = 1;
            break;
        case 1:
            if (Math_Distance2dGet(&subChar->position_18, &subChar->properties_E4.unk0.field_F8) < Q12(0.5f))
            {
                subChar->model_0.stateStep_3 = 0;
            }
            break;
    }

    func_800D53AC(subChar);
    sharedFunc_800D57C8_0_s01(subChar);

    switch (sharedFunc_800D2C0C_0_s01(subChar, 0x1000))
    {
        case 0:
            dist0 = -1;
            temp_v0 = subChar->properties_E4.unk0.field_F8.vy - subChar->position_18.vy;
            if (temp_v0 > Q12(-0.2f) && temp_v0 < Q12(0.8f))
            {
                dist0 = subChar->field_D4 + Q12(0.15f);
            }

            dist = Math_Distance2dGet(&subChar->position_18, &subChar->properties_E4.unk0.field_F8);
            if (dist < dist0)
            {
                temp_v0_2 = FP_ANGLE_NORM_S(func_80080478(&subChar->position_18, &subChar->properties_E4.unk0.field_F8) - subChar->rotation_24.vy);
                if (temp_v0_2 >= FP_ANGLE(-8.0f) && temp_v0_2 < FP_ANGLE(8.0f))
                {
                    subChar->model_0.state_2 = 49;
                    subChar->model_0.stateStep_3 = 0;
                }
            }
            break;

        case 1:
        case 2:
            subChar->model_0.state_2 = 50;
            subChar->model_0.stateStep_3 = 0;
            subChar->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            break;
        case 3:
        case 4:
            subChar->model_0.state_2 = 51;
            subChar->model_0.stateStep_3 = 0;
            if (subChar->health_B0 <= 0)
            {
                subChar->properties_E4.player.flags_11C |= PlayerFlag_Unk6;
            }
            else
            {
                subChar->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            }
            break;
        default:
            break;
    }
}

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D45BC);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D46C4);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D4894);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D49B0);

#include "maps/shared/sharedFunc_800D4A80_0_s01.h"

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D4AEC);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D4E84);

#include "maps/shared/sharedFunc_800D5274_0_s01.h" // 0x800D5274

void func_800D529C(s_SubCharacter* arg0, s32 thousand, s32 angle)
{
    s32 posX;
    s32 posZ;
    s32 x;
    s32 z;
    s32 y;
    s32 calcY;
    s32 someY;
    s32 someConst;

    posX = arg0->position_18.vx;
    posZ = arg0->position_18.vz;
    someConst = 0x1800; // } @hack permuter find.
    arg0++;             // }
    arg0--;             // }
    x = posX + FP_MULTIPLY_PRECISE(thousand, Math_Sin(angle), Q12_SHIFT);
    z = posZ + FP_MULTIPLY_PRECISE(thousand, Math_Cos(angle), Q12_SHIFT);


    calcY = func_80080884(x, z);
    someY = arg0->properties_E4.unk0.properties_124.val32;
    if (someY < calcY)
    {
        calcY = someY;
    }

    y = (calcY - someConst) - func_80080514() / 2;
    
    if (y < sharedFunc_800D5274_0_s01())
    {
        y = sharedFunc_800D5274_0_s01();
    }

    arg0->properties_E4.unk0.field_F8.vx = x;
    arg0->properties_E4.unk0.field_F8.vy = y;
    arg0->properties_E4.unk0.field_F8.vz = z;
    func_800D4E84(arg0);
}

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D53AC);

void func_800D5638(s_SubCharacter* arg0)
{
    s32 idx0;
    s32 idx1;
    s_sharedData_800E21D0_0_s01* dst;
    s_func_800D2E04* src;

    src = &sharedData_800CAA98_0_s01;
    dst = &sharedData_800E21D0_0_s01;

    idx0 = 3;
    dst->field_B4[idx0][2] = 0;
    idx0 = 0;
    dst->field_B4[idx0][2] = src->unk_380[2][0];
    dst->field_B4[idx0][1] = src->unk_380[2][1];

    idx0 = 1;
    dst->field_B4[idx0][2] = sharedData_800CAA98_0_s01.unk_380[0xB][0];
    dst->field_B4[idx0][1] = sharedData_800CAA98_0_s01.unk_380[0xB][1];
    idx0 = 3;
    dst->field_B4[idx0][1] = sharedData_800CAA98_0_s01.unk_380[0x1E][1];

    sharedFunc_800D5E78_0_s01(arg0, 0);
}

#include "maps/shared/sharedFunc_800D569C_0_s01.h" // 0x800D569C

#include "maps/shared/sharedFunc_800D57C8_0_s01.h" // 0x800D57C8

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D598C);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D5B10);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D5C90);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D5D80);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D5E14);

#include "maps/shared/sharedFunc_800D5E78_0_s01.h" // 0x800D5E78

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D5F00);

#include "maps/shared/sharedFunc_800D62D8_0_s01.h" // 0x800D62D8

#include "maps/shared/sharedFunc_800D633C_0_s01.h" // 0x800D633C

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D63A4_0_s01); // 0x800D63A4

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D6600_0_s01); // 0x800D6600

s32 func_800D6A60(VECTOR3* vec0, VECTOR3* vec1, s_SubCharacter* chara, s32 arg3, VECTOR3* vec2)
{
    VECTOR3* vec0Cpy;
    s32 vec0X;
    s32 vec0Z;
    s32 vec0Y;
    s32 vec1X;
    s32 vec1Y;
    s32 vec1Z;
    s32 vec2X;
    s32 vec2Z;
    s32 posY;
    s32 calcY;
    s32 newVec1Y;
    s32 newVec2Y;
    s32 time;
    s32 ret;
    s32 retCode1;
    s32 flags;

    flags = chara->properties_E4.player.flags_11C;
    vec0Cpy = vec0;
    vec0X = vec0Cpy->vx;
    vec0Z = vec0Cpy->vz;
    ret = arg3;
    chara->position_18.vx += vec0X;
    chara->position_18.vz += vec0Z;
    if (ret == 0)
    {
        flags &= ~PlayerFlag_Unk31;
        vec1X = 0;
        vec2->vx = vec1->vx;
        vec1Z = 0;
        vec2->vz = vec1->vz;
    }
    else
    {
        flags |= PlayerFlag_Unk31;
        time = 0x01000000 / g_DeltaTime0;
        if (!(vec0X | vec0Z))
        {
            vec2X = 0;
            vec2Z = 0;
            vec2->vx = 0;
            vec2->vz = 0;
        }
        else
        {
            vec2X = FP_MULTIPLY_PRECISE(vec0X, time, Q12_SHIFT);
            vec2->vx = vec2X;
            vec2Z = FP_MULTIPLY_PRECISE(vec0Z, time, Q12_SHIFT);
            vec2->vz = vec2Z;
        }
        vec1X = vec2X - vec1->vx;
        vec1Z = vec2Z - vec1->vz;
    }
    vec1->vx = vec1X;
    vec1->vz = vec1Z;
    posY = chara->position_18.vy;
    vec1Y = vec1->vy;
    vec0Y = vec0Cpy->vy;

    calcY = func_80080884(chara->position_18.vx, chara->position_18.vz);
    D_800E22E4 = calcY;
    retCode1 = 1;

    if (!(chara->field_E1_0))
    {
        newVec2Y = 0;
        newVec1Y = 0;
    } 
    else if ((posY >= calcY) && (vec0Y >= 0))
    {
        flags &= ~PlayerFlag_Unk30;
        posY = calcY;
        newVec2Y = 0;
        newVec1Y = 0;
    } 
    else 
    {
        posY += vec0Y;
        if (posY >= calcY)
        {
            flags |= PlayerFlag_Unk30;
            ret = retCode1;
            newVec2Y = 0;
            newVec1Y = -vec1Y;
            posY = calcY;
        } 
        else 
        {
            flags &= ~PlayerFlag_Unk30;
            newVec2Y = vec1Y;
            newVec1Y = 0;
        }
    }

    chara->position_18.vy = posY;
    vec2->vy = newVec2Y;
    vec1->vy = newVec1Y;
    chara->properties_E4.player.flags_11C = flags;
    return ret;
}

void func_800D6C7C(VECTOR* arg0, s_SubCharacter* arg1, s32 arg2, VECTOR3* arg3)
{
    s32 temp_a0;
    s32 temp_hi;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_t0;
    s32 temp_t0_2;
    s32 sqr;
    s32 z;
    s32 y;
    s32 x;
    u32 temp_lo;
    u32 temp_v0;
    u32 temp_v0_2;
    u32 temp_v0_3;

    if (arg2 == 0)
    {
        x = 0;
        y = 0;
        z = 0;
    } 
    else 
    {
        x = arg0->vx;
        y = arg0->vy;
        z = arg0->vz;

        sqr = FP_MULTIPLY_PRECISE(x, x, Q12_SHIFT);
        sqr += FP_MULTIPLY_PRECISE(y, y, Q12_SHIFT);
        sqr += FP_MULTIPLY_PRECISE(z, z, Q12_SHIFT);
        
        sqr = SquareRoot12(sqr);
        
        arg1->damageReceived_C0 += Math_PreservedSignSubtract(sqr, 0x5000);
        if (sqr != 0) 
        {
            sqr = (s32) (Math_PreservedSignSubtract(sqr, Q12(6.0f)) << Q12_SHIFT) / sqr;
        }
        x = FP_MULTIPLY_PRECISE(x, sqr, Q12_SHIFT);
        y = FP_MULTIPLY_PRECISE(y, sqr, Q12_SHIFT);
        z = FP_MULTIPLY_PRECISE(z, sqr, Q12_SHIFT);
        
        if ((x | y | z) != 0)
        {
            arg1->field_B4 += FP_MULTIPLY_PRECISE(x, Q12(0.8f), Q12_SHIFT);
            arg1->field_B8 += FP_MULTIPLY_PRECISE(y, Q12(0.8f), Q12_SHIFT);
            arg1->field_BC += FP_MULTIPLY_PRECISE(z, Q12(0.8f), Q12_SHIFT);
        }
    }
    arg3->vx = x;
    arg3->vy = y;
    arg3->vz = z;
}

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D6EC4);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D7120_0_s01);

#include "maps/shared/sharedFunc_800D71F0_0_s01.h" // 0x800D71F0

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D72E8);

#include "maps/shared/sharedFunc_800D7440_0_s01.h" // 0x800D7440

#include "maps/shared/sharedFunc_800D7560_0_s01.h" // 0x800D7560

#include "maps/shared/sharedFunc_800D76A0_0_s01.h" // 0x800D76A0

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D7714);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D77D0_0_s01);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D7AB0_0_s01); // 0x800D7AB0

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D7B14);

q19_12 Model_AnimDurationGet(s_Model* model) // 0x800D7E88
{
    return Anim_DurationGet(model, func_80044918(&model->anim_4));
}

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D7EBC_0_s01); // 0x800D7EBC

#include "maps/shared/sharedFunc_800D81B0_0_s01.h" // 0x800D81B0

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D81D0_0_s01);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D8244_0_s01);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D82B8_0_s01); // 0x800D82B8

#include "maps/shared/sharedFunc_800D8714_0_s01.h" // 0x800D8714

#include "maps/shared/sharedFunc_800D87FC_0_s01.h" // 0x800D87FC

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D8804);

#include "maps/shared/Ai_Cybil_Update.h" // 0x800D8814

#include "maps/shared/sharedFunc_800D8888_0_s01.h"

#include "maps/shared/sharedFunc_800D88D0_0_s01.h" // 0x800D88D0

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedSymbol_800D8A68_0_s01); // 0x800D8A68

#include "maps/shared/Ai_Cybil_Init.h" // 0x800D9AD0

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D9B0C

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D9B20

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D9B64

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D9B7C

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D9B88

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D9B9C

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D9BB0

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D9BC4

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800D9C60

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800DA2C4

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800DA2D8

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800DA2EC

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800DA3E8

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800DA49C

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800DA4BC

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800DA51C

#include "maps/shared/sharedFunc_800D92AC_0_s00.h" // 0x800DA52C

void func_800DA778(s32 arg0) // 0x800DA778
{
    (arg0 != 0) ? func_800DA7AC() : func_800DA7FC();
}

void func_800DA7AC() // 0x800DA7AC
{
    s32 var;

    if (!Savegame_EventFlagGet(EventFlag_48))
    {
        if (!Savegame_EventFlagGet(EventFlag_49))
        {
            var = 9;
        }
        else
        {
            var = 30;
        }
    }
    else
    {
        var = 6;
    }

    func_8003640C(var);
}

void func_800DA7FC() // 0x800DA7FC
{
    s32 var0;
    s32 var1;

    var1 = 0x553;
    if (!Savegame_EventFlagGet(EventFlag_146))
    {
        if (!(Savegame_EventFlagGet(EventFlag_48) || Savegame_EventFlagGet(EventFlag_49)))
        {
            var1 = 0xF0000;
            if (Savegame_EventFlagGet(EventFlag_39) && g_GameWork.soundCmd_5B2 == 9)
            {
                var0 = 2;
            }
            else
            {
                var0 = 0x201;
            }
        }
        else if (Savegame_EventFlagGet(EventFlag_47))
        {
            if (!Savegame_EventFlagGet(EventFlag_48))
            {
                var1 = 0xF0000;
                var0 = 0x100;
            }
            else
            {
                var1 = 0x200;
                var0 = 0x201;
            }
        }
        else
        {
            var0 = 1;
        }
    }
    else
    {
        var0 = 1;
    }

    func_80035F4C(var0, var1, NULL);
}

void Gfx_LoadingScreen_StageString() // 0x800DA8A4
{
    ScreenFade_Start(false, true, false);

    Gfx_DebugStringPosition(100, 100);
    Gfx_DebugStringDraw("STAGE 0-1");
    Gfx_LoadingScreen_BackgroundTexture();
}

#include "maps/shared/sharedFunc_800DA8E8_0_s01.h" // 0x800DA8E8
