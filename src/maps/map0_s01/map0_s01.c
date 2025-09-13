#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/map0_s01.h"

const u32 D_800CA5C8[4] = {};

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800CCB8C);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800CD1F8);

void func_800CE000(s32 arg1, s32 arg2, s32 arg3) // 0x800CE000
{
    s32 temp_a2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_v0;
    s32 i;
    s32 var_v0;
    s32 var_v0_3;
    u32 temp_t0;
    u32 temp_v1_2;
    u16 temp_v1_3;
    
    func_80055434(&g_ParticleVectors0.vector_0);

    g_ParticleVectors0.field_28 = func_8005545C(&g_ParticleVectors0.svec_18);
    vwGetViewPosition(&g_ParticleVectors0.viewPosition_C);
    vwGetViewAngle(&g_ParticleVectors0.viewRotation_20);

    switch (arg3)
    {
        case 0:
        case -1:
            sharedData_800DD591_0_s00 = 1;

            // TODO: Meters?
            D_800E2160.vector_0.vx = Q19_12(-0.30f);
            D_800E2160.vector_0.vz = Q19_12(275.0f);
            D_800E2160.vector_C.vx = Q19_12(-0.30f);
            D_800E2160.vector_C.vz = Q19_12(265.0f);

            sharedData_800DD796_0_s01 = 1;

            if (arg3 == NO_VALUE)
            {
                g_SysWork.field_2349 = g_MapOverlayHeader.field_17;
                g_SysWork.field_2348 = g_MapOverlayHeader.field_17;
            }

            D_800DD798 = 0;
            sharedData_800E324C_0_s00.vz = 0;
            g_SysWork.field_234A = 1;
            D_800DE160 = arg2;

            sharedData_800E324C_0_s00.vx = 0;
            sharedData_800E0CB8_0_s00 = FP_FROM(sharedData_800E0CB0_0_s00, Q12_SHIFT);
            sharedData_800E0CB6_0_s00 = sharedData_800E0CB0_0_s00;
            sharedData_800E0CB4_0_s00 = sharedData_800E0CB0_0_s00;

            temp_s0 = SetSp(0x1F8003D8);

            sharedFunc_800CE59C_0_s01(g_Particles);
            SetSp(temp_s0);
            break;

        default:
            sharedData_800DD78B_0_s01 = g_DeltaTime0 == FP_TIME(0.0f);

            func_8003EDB8(&D_800E214C, &D_800E2150);

            if (sharedData_800E0CB6_0_s00 != sharedData_800E0CB4_0_s00)
            {
                if (sharedData_800DD78B_0_s01 == 0)
                {
                    D_800DD798++;
                }

                temp_s0_2 = FP_MULTIPLY(Math_Sin(FP_ANGLE(270.0f) + (D_800DD798 * 2)), 150, Q12_SHIFT) + 150;
                temp_a2 = FP_MULTIPLY(Math_Sin(FP_ANGLE(180.0f) + (D_800DD798 * 2)), 150, Q12_SHIFT) + 150;
                temp_t0 = sharedData_800E0CB6_0_s00 >> 14;
               
                for (i = 0; i < 2; i++)
                {
                    temp_v1_2 = (sharedData_800E0CB4_0_s00 >> ((1 - i) * 6)) & 0x3F;
                    temp_v1_3 = (sharedData_800E0CB4_0_s00 >> 6) & 0x3F;
                    temp_v0 = temp_v1_3;

                    switch (temp_v1_2)
                    {
                        case 4:
                        case 6:
                            sharedData_800DD78C_0_s01[i] = temp_s0_2;
                            break;

                        case 5:
                        case 7:
                            var_v0 = temp_s0_2 * 2;
                            sharedData_800DD78C_0_s01[i] = var_v0;
                            break;

                        case 32:
                        case 48:
                            sharedData_800DD78C_0_s01[i] = temp_a2;
                            break;

                        case 37:
                        case 39:
                        case 53:
                        case 55:
                            var_v0 = temp_s0_2 + 150;
                            sharedData_800DD78C_0_s01[i] = var_v0;
                            break;

                        case 40:
                        case 56:
                            var_v0 = temp_a2 * 2;
                            sharedData_800DD78C_0_s01[i] = var_v0;
                            break;

                        case 44:
                        case 46:
                        case 60:
                        case 62:
                            var_v0 = temp_a2 + 150;
                            sharedData_800DD78C_0_s01[i] = var_v0;
                            break;

                        case 0:
                            sharedData_800DD78C_0_s01[i] = 0;
                            break;

                        case 36:
                        case 38:
                        case 52:
                        case 54:
                            var_v0 = 150;
                            sharedData_800DD78C_0_s01[i] = var_v0;
                            break;

                        case 45:
                        case 47:
                        case 61:
                        case 63:
                            var_v0 = 300;
                            sharedData_800DD78C_0_s01[i] = var_v0;
                            break;
                    }

                    if (i == 0)
                    {
                        if (temp_t0 < 2)
                        {
                            if (temp_t0 != 1 || (sharedData_800E0CB4_0_s00 >> 14) < 2)
                            {
                                sharedData_800DD796_0_s01 = 1;
                                continue;
                            }
                        }

                        switch (temp_v0)
                        {
                            case 4:
                            case 6:
                            case 32:
                            case 48:
                                var_v0_3 = sharedData_800DD78C_0_s01[i] < (75 + 1);
                                sharedData_800DD796_0_s01 = var_v0_3 ^ 1;
                                break;

                            case 5:
                            case 7:
                            case 40:
                            case 56:
                                var_v0_3 = sharedData_800DD78C_0_s01[i] < (150 + 1);
                                sharedData_800DD796_0_s01 = var_v0_3 ^ 1;
                                break;

                            case 8:
                            case 9:
                            case 10:
                            case 11:
                            case 12:
                            case 13:
                            case 14:
                            case 15:
                            case 16:
                            case 17:
                            case 18:
                            case 19:
                            case 20:
                            case 21:
                            case 22:
                            case 23:
                            case 24:
                            case 25:
                            case 26:
                            case 27:
                            case 28:
                            case 29:
                            case 30:
                            case 31:
                            case 33:
                            case 34:
                            case 35:
                            case 36:
                            case 37:
                            case 38:
                            case 39:
                            case 41:
                            case 42:
                            case 43:
                            case 44:
                            case 45:
                            case 46:
                            case 47:
                            case 49:
                            case 50:
                            case 51:
                            case 52:
                            case 53:
                            case 54:
                            case 55:
                            default:
                                sharedData_800DD796_0_s01 = 1;
                                break;
                        }
                    }
                }

                if (D_800DD798 >= 0x200)
                {
                    D_800DD798 = 0;
                    g_SysWork.field_234A = 1;
                    sharedData_800E0CB6_0_s00 = sharedData_800E0CB4_0_s00;

                    switch ((sharedData_800E0CB8_0_s00 & 0xF) >> 2)
                    {
                        case 0:
                            sharedData_800DFB6C_0_s00 = 0;
                            sharedData_800DFB70_0_s00 = 0;
                            break;

                        case 1:
                            sharedData_800DFB6C_0_s00 = 1;
                            sharedData_800DFB70_0_s00 = 0;
                            break;

                        case 2:
                            sharedData_800DFB6C_0_s00 = 0;
                            sharedData_800DFB70_0_s00 = 1;
                            break;
                    }
                }
            }

            D_800DE164 = arg2;
            temp_s0_3 = SetSp(0x1F8003D8);

            Particle_Update(g_Particles);
            SetSp(temp_s0_3);

            for (i = sharedData_800DD78C_0_s01[0] + sharedData_800DD78C_0_s01[1]; i < PARTICLE_COUNT_MAX; i++)
            {
                g_Particles[i].stateStep_1E = 0;
            }
    }

    g_ParticleVectors1 = g_ParticleVectors0;
}


#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CE4C4

#include "maps/shared/sharedFunc_800CE59C_0_s01.h" // 0x800CE59C

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
    s_func_800699F8 sp10;
    VECTOR3         sp20;
    s32             headingAngle;
    s16             temp_v0;
    s32             temp_s0;
    s32             moveAmt;
    s32             temp_s2;
    s16             temp_s3;
    s32             scaleRestoreShift;
    u32             scaleReduceShift;
    s32             temp_v0_2;
    s32             temp_v0_3;
    s32             playerState;
    s32             moveSpeed;
    s32             var_a0;
    bool            cond;
    s16             var_s0;
    s16             var_v1;

    playerState = g_SysWork.player_4C.extra_128.state_1C;
    cond        = playerState < PlayerState_Unk58;

    if (playerState == PlayerState_Unk53)
    {
        cond = false;
    }

    if (cond)
    {
        func_800699F8(&sp10, chara->position_18.vx, chara->position_18.vz);
        temp_s2 = FP_MULTIPLY(chara->moveSpeed_38, Math_Sin(chara->headingAngle_3C), Q12_SHIFT);
        temp_s0 = FP_MULTIPLY(chara->moveSpeed_38, Math_Cos(chara->headingAngle_3C), Q12_SHIFT);

        temp_s3 = Math_Cos(ABS(sp10.field_4) >> 3);
        temp_v0 = Math_Cos(ABS(sp10.field_6) >> 3);

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
            chara->position_18.vy = FP_METER(0.0f);
        }

        chara->field_34 = 0;
    }

    if (g_DeltaTime0 == FP_TIME(0.0f))
    {
        chara->rotationSpeed_2C.vy = FP_ANGLE(0.0f);
    } 
    else
    {
        chara->rotationSpeed_2C.vy = (sharedData_800E39D8_0_s00 << 8) / g_DeltaTime0;
    }

    coord->coord.t[0] = FP_METER_TO_GEO(chara->position_18.vx);
    coord->coord.t[1] = FP_METER_TO_GEO(chara->position_18.vy);
    coord->coord.t[2] = FP_METER_TO_GEO(chara->position_18.vz);
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

    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_METER(2.3f);
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

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D2B4C_0_s01); // 0x800D2B4C

#include "maps/shared/sharedFunc_800D2BB0_0_s01.h" // 0x800D2BB0

#include "maps/shared/sharedFunc_800D2BE4_0_s01.h" // 0x800D2BE4

#include "maps/shared/sharedFunc_800D2BF4_0_s01.h" // 0x800D2BF4

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D2C0C);

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

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", g_SfxVolumes);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CB7E4);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CB7F0);

#ifdef NON_MATCHING // TODO .rodata
void func_800D3CC4(s_SubCharacter* chara)
{
    u32  keyframeIdx;
    bool cond;

    sharedData_800E21D0_0_s01.flags_0 |= 1 << 31;
    cond = false;

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            cond = true;
            chara->model_0.anim_4.status_0 = ANIM_STATUS(23, true);
            chara->model_0.stateStep_3 = 1;
            break;

        case 2:
            cond = true;
            chara->model_0.anim_4.status_0 = ANIM_STATUS(24, true);
            chara->model_0.stateStep_3 = 3;

        case 1:
        case 3:
            chara->properties_E4.player.flags_11C |= 1 << 16;

        default:
            break;

        case 4:
            cond = true;
            chara->model_0.anim_4.status_0 = ANIM_STATUS(15, true);
            chara->model_0.stateStep_3 = 5;

        case 5:
            chara->properties_E4.player.flags_11C &= ~(1 << 16);
            break;

        case 6:
            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(19, true))
            {
                chara->model_0.stateStep_3 = 7;
            }
            break;

        case 7:
            chara->model_0.state_2 = 0;
            chara->model_0.stateStep_3 = 13;
            sharedSymbol_800D3B0C_0_s01(chara);
            break;
    }

    func_800D2C0C(chara, 0);

    if (cond)
    {
        keyframeIdx = func_80044918(&chara->model_0.anim_4)->startKeyframeIdx_C;
        chara->model_0.anim_4.keyframeIdx_8 = keyframeIdx;
        chara->model_0.anim_4.time_4 = FP_TIME(keyframeIdx);
    }
}
#else
INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D3CC4);
#endif

#ifdef NON_MATCHING // TODO .rodata
void func_800D3DFC(s_SubCharacter* chara)
{
    s32 angle; // Maybe not angle.
    s32 flags;

    if (chara->field_40 < 0x20)
    {
        flags = g_MapOverlayHeader.charaSpawns_24C[0][chara->field_40].flags_6;
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

        if (func_80080514() >= angle)
        {
            func_80037DC4(chara);
        }
    }
}
#else
INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D3DFC);
#endif

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D3EB8);

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

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D426C);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D4420);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D45BC);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D46C4);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D4894);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D49B0);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D4A80_0_s01);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D4AEC);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D4E84);

#include "maps/shared/sharedFunc_800D5274_0_s01.h" // 0x800D5274

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D529C);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D53AC);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D5638);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D569C);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D57C8);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D598C);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D5B10);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D5C90);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D5D80);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D5E14);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D5E78);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D5F00);

#include "maps/shared/sharedFunc_800D62D8_0_s01.h" // 0x800D62D8

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D633C_0_s01); // 0x800D633C

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D63A4_0_s01); // 0x800D63A4

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D6600_0_s01); // 0x800D6600

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D6A60);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D6C7C);

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

void func_800D7E88(s_Model* model) // 0x800D7E88
{
    Anim_DurationGet(model, func_80044918(&model->anim_4));
}

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D7EBC_0_s01); // 0x800D7EBC

#include "maps/shared/sharedFunc_800D81B0_0_s01.h" // 0x800D81B0

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D81D0_0_s01);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D8244_0_s01);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D82B8_0_s01); // 0x800D82B8

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D8714_0_s01);

#include "maps/shared/sharedFunc_800D87FC_0_s01.h" // 0x800D87FC

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D8804);

#include "maps/shared/Ai_Cybil_Update.h" // 0x800D8814

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D8888_0_s01); // 0x800D8888

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
    g_Screen_FadeStatus = SCREEN_FADE_STATUS(ScreenFadeState_FadeInSteps, false);

    Gfx_DebugStringPosition(100, 100);
    Gfx_DebugStringDraw("STAGE 0-1");
    Gfx_LoadingScreen_BackgroundTexture();
}

const char* g_MapMessages[] =
{
    #include "maps/shared/mapMsg_common.h"
    "~J0(2.0)\tWas_I_dreaming?  ~E ",
    "~J0(2.5)\tHow_do_you_feel? ~E ",
    "~J0(6.0)\tLike_I've_been ~N\n\t\t\trun_over_by_a_truck, ~N\n\t\t\tbut_I'm_all_right,_I_guess. ~E ",
    "~J0(1.5)\tGlad_to_hear_it.",
    "~J0(5.0)\tYou_from_around_here? ~N\n\t\t\tWhy_don't_you ~N\n\t\t\ttell_me_what_happened? ",
    "~J0(3.0)\tWait_a_second. ~N\n\t\t\tI'm_just_a_tourist. ",
    "~J0(5.2)\tI_came_here_for_a_vacation. ~N\n\t\t\tI_just_got_here... ",
    "~J0(4.2)\tI_don't_know_what_happened. ",
    "~J0(4.0)\tI'd_like_to_find_out_myself. ",
    "~J0(2.0)\tUh-huh? ~E ",
    "~J0(3.0)\tHave_you_seen_a_little_girl? ",
    "~J0(4.0)\tJust_turned_seven_last_month... ~N\n\t\t\tShort,_black_hair... ",
    "~J0(1.5)\tMy_daughter. ",
    "~J0(1.0)\tSorry. ",
    "~J0(3.0)\tThe_only_person_I've_seen ~N\n\t\t\tin_this_town_is_you. ",
    "~J0(2.5)\tWhere_is_everybody? ",
    "~J0(3.5)\tI'd_tell_you_if_I_knew,~N\n\t\t\tbelieve_me. ",
    "~J0(5.5)\tBut,_from_what_I_can_tell, ~N\n\t\t\tsomething_bizarre_is_going_on. ",
    "~J0(2.5)\tThat's_all_I_know. ",
    "~J0(2.0)\tHmmm... ~E ",
    "~J0(2.0)\tWhat's_your_name? ",
    "~J0(1.0)\tHarry... ",
    "~J0(2.0)\tHarry_Mason. ",
    "~J0(2.0)\tCybil_Bennett. ",
    "~J0(4.0)\tI'm_a_police_officer ~N\n\t\t\tfrom_Brahms, ~N\n\t\t\tthe_next_town_over. ",
    "~J0(3.0)\tThe_phones_are_all_dead, ~N\n\t\t\tand_the_radio,_too. ",
    "~J0(4.0)\tI'm_going_back_to_call ~N\n\t\t\tin_some_reinforcements. ",
    "~J0(1.5)\tHmph. ~E ",
    "~D\t~J0(4.0)\tHold_it! ~N\n\t\t\tWhere_do_you_think ~N\n\t\t\tyou're_going? ~E ",
    "~J0(4.0)\tMy_daughter... ~N\n\t\t\tI've_gotta_find_her! ~E ",
    "~D\t~J0(1.5)\tNo_way! ~E ",
    "~J0(3.0)\tIt's_dangerous_out_there. ",
    "~J0(5.0)\tIn_that_case, ~N\n\t\t\tI_need_to_find_her_now! ~N\n\t\t\tCheryl's_my_little_girl. ",
    "~J0(3.0)\tI_can't_just_leave_her_out ~N\n\t\t\tthere_by_herself. ~E ",
    "~J0(2.5)\tHave_you_got_a_gun? ",
    "~J0(3.0)\tUmmm..._no. ~E ",
    "~J0(5.0)\tTake_this. ~N\n\t\t\tAnd_hope_you_don't ~N\n\t\t\thave_to_use_it. ",
    "~J0(1.5)\tNow_listen_to_me, ",
    "~J0(4.5)\tbefore_you_pull_the_trigger, ~N\n\t\t\tknow_who_you're_shooting. ",
    "~J0(3.0)\tAnd_don't_do_it ~N\n\t\t\tunless_you_have_to. ~E ",
    "~J0(3.0)\tAnd_don't_go_blasting_me ~N\n\t\t\tby_mistake. ",
    "~J0(2.5)\tGot_it? ~E ",
    "~J0(2.5)\tYeah._Thanks. ~E ",
    "~J0(5.0)\tYou'd_do_best_to_stay_nearby. ~N\n\t\t\tI'll_be_back_with ~N\n\t\t\thelp_as_quick_as_I_can. ~E ",
    "~H There_is_a_ ~C5 Residential_area_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Kitchen_knife ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Flashlight ~C7 . ~N\n\tTake_it? ~S4 ",
    "~J0(1.1)\tWhat's_that? ~E ",
    "~J0(4.5)\tHuh?_Radio? ~N\n\t\t\tWhat's_going_on_with_that_radio? ~E ",
    "\tThere_is_a_ ~C2 Pocket_radio ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tA_radio... is_it_broken? ~N\n\tCan't_hear_anything. ~E ",
    " ",
    "\tMaybe_I_should_check_for ~N\n\tsomething_useful_before_leaving. ~E ",
    "~J0(4.3)\tThis_is_not_a_dream! ~N\n\tWhat's_happening_to_this_place!? ~E ",
    "\tI'll_worry_about_the_radio_later, ~N\n\tI_have_more_important_stuff ~N\n\tto_do. ~E ",
    "\tI've_got_to_beat_that_monster! ~E ",
    "\tThe_radio_may_be ~N\n\tuseful_for_something. ",
    "\tI_better_take_it_with_me. ~E ",
    "\tPinball_machine. ~N\n\tNothing_unusual. ~E ",
    "\tCan't_turn_on_the_TV. ~N\n\tNo_power? ~E ",
    "\tI_have_more_important_stuff_to_do. ~E ",
};

#include "maps/shared/sharedFunc_800DA8E8_0_s01.h" // 0x800DA8E8

const VECTOR3 D_800CC8FC = {0x00000CCC, 0xFFFFECCD, 0x0010D800};
const char D_800CC908[] = "HERO";
const char D_800CC910[] = "SIBYL";

extern VECTOR3 g_CutsceneCameraLookAtTarget;
extern s32 g_Timer0;
extern u8 g_SoundCmdIdx;
extern const VECTOR3 D_800CC8FC;
extern const char D_800CC908[];
extern const char D_800CC910[];

void Event_CafeCutscene()
{
    #define CUTSCENE_SKIP_STATE 52

    u8              temp_s0_5;
    s_SubCharacter* chara0;
    s_SubCharacter* chara1;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 &&
        g_SysWork.sysStateStep_C[0] > 5 && g_SysWork.sysStateStep_C[0] < 47)
    {
        SysWork_NextStateStepSet(CUTSCENE_SKIP_STATE);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            
            g_SysWork.field_30 = 20;
            g_Screen_FadeStatus = SCREEN_FADE_STATUS(ScreenFadeState_ResetTimeStep, false);
            g_SysWork.flags_22A4 |= 1 << 3;
            g_SavegamePtr->flags_AC &= ~(1 << 0);
            g_SysWork.flags_22A4 |= (1 << 5) | (1 << 9);
            g_SoundCmdIdx = 0;
            D_800DE250 = 0;
            D_800DE251 = 0;
            
            Fs_QueueStartRead(FILE_ANIM_CAFE_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_11);
            Chara_Load(0, Chara_Cybil, &g_SysWork.npcCoords_FC0[0], NO_VALUE, NULL, NULL);
            func_80088D0C();
            Chara_Spawn(Chara_Cybil, 0, FP_METER(4.4f), FP_METER(269.9f), FP_METER(0.0f), 2);
            
            g_Timer0 = 0;
            SysWork_StateStepIncrement();
        
        case 1:
            func_80087EDC(9);
            break;
        
        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 77, false);
            func_8008616C(0, false, 0, FP_TIME(0.0f), false);
            func_800D2054();
            SysWork_StateStepIncrement();
            break;
        
        case 3:
            func_80085EB8(2, &g_SysWork.player_4C.chara_0, NULL, false);
            SysWork_StateStepIncrement();
        
        case 4:
            func_8008616C(1, false, 0, FP_TIME(0.0f), false);
            break;
        
        case 5:
            func_80085EB8(3, &g_SysWork.player_4C.chara_0, NULL, false);
            SysWork_StateStepIncrement();
        
        case 6:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(7.8f), FP_TIME(0.0f), FP_TIME(5.0f), false, true);
            break;
        
        case 7:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(7.8f), FP_TIME(0.0f), FP_TIME(26.0f), true, false);
            func_800869E4(15, &g_SoundCmdIdx, g_SoundCmds); // "Was I dreaming?"
            break;
        
        case 8:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(7.8f), FP_TIME(0.0f), FP_TIME(26.0f), true, true);
            break;
        
        case 9:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 78, false);
            D_800DE250 = 1;
            SysWork_StateStepIncrement();
        
        case 10:
        case 11:
        case 12:
        case 13:
            switch (g_SysWork.sysStateStep_C[0])
            {
                case 10:
                    func_800869E4(16, &g_SoundCmdIdx, g_SoundCmds); // "How do you feel?"
                    break;

                case 11:
                    func_800869E4(17, &g_SoundCmdIdx, g_SoundCmds); // "Like I've been hit..."
                    break;

                case 12:
                    if (g_Timer0 == FP_TIME(48.0f) && D_800DE251 == 2)
                    {
                        SysWork_NextStateStepSet(13);
                    }
                    break;

                case 13:
                    func_800869E4(18, &g_SoundCmdIdx, g_SoundCmds); // "Glad to hear it."
                    break;
            }

            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(4.0f), FP_TIME(27.0f), FP_TIME(48.0f), true, false);

            if (D_800DE251 == 0 && g_Timer0 > FP_TIME(38.0f))
            {
                func_80085EB8(0, &g_SysWork.npcs_1A0[0], 10, false);
                func_80085EB8(0, &g_SysWork.player_4C.chara_0, 110, false);
                
                D_800DE251++;
            }

            temp_s0_5 = D_800DE251;
            if (D_800DE251 == 1 && sharedFunc_800D8964_0_s00(&g_SysWork.npcs_1A0[0]) == temp_s0_5)
            {
                func_80085EB8(0, &g_SysWork.npcs_1A0[0], 0xB, false);
                D_800DE251++;
            }
            break;

        case 14:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(3.0f), FP_TIME(49.0f), FP_TIME(139.0f), true, false);
            func_800869E4(25, &g_SoundCmdIdx, g_SoundCmds); // "Have you seen a little girl?"
            break;

        case 15:
            g_Timer0 = FP_TIME(140.0f);
            SysWork_StateStepIncrement();

        case 16:
            func_800869E4(35, &g_SoundCmdIdx, g_SoundCmds); // "What's your name?"
            break;

        case 17:
            func_80085E6C(FP_TIME(1.2f), false);
            break;

        case 18:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 93, false);
            SysWork_StateStepIncrement();

        case 19:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(141.0f), FP_TIME(152.0f), false, true);
            break;

        case 20:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 53, false);
            SysWork_StateStepIncrement();

        case 21:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(141.0f), FP_TIME(159.0f), true, true);
            func_8004729C(4108);
            break;

        case 22:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 7, false);
            Sd_EngineCmd(4108);
            SysWork_StateStepIncrement();

        case 23:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(160.0f), FP_TIME(173.0f), true, false);
            MapMsg_DisplayAndHandleSelection(false, 43, 0, 0, 0, false);
            Gfx_DebugStringPosition(30, 30);
            break;

        case 24:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x47, false);
            SysWork_StateStepIncrement();

        case 25:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(174.0f), FP_TIME(184.0f), true, false);
            func_800869E4(44, &g_SoundCmdIdx, g_SoundCmds);
            break;

        case 26:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 8, 0);
            SysWork_StateStepIncrement();

        case 27:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(185.0f), FP_TIME(194.0f), true, false);
            func_800869E4(45, &g_SoundCmdIdx, g_SoundCmds);
            break;

        case 28:
            g_Timer0 = FP_TIME(195.0f);

            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);
            SysWork_StateStepIncrement();

        case 29:
            func_800869E4(46, &g_SoundCmdIdx, g_SoundCmds); // "It's dangerous out there."
            break;

        case 30:
            func_80085E6C(FP_TIME(1.5f), false);
            break;

        case 31:
            func_800869E4(49, &g_SoundCmdIdx, g_SoundCmds);
            break;

        case 32:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 1, false);
            SysWork_StateStepIncrement();

        case 33:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(20.0f), FP_TIME(207.0f), FP_TIME(222.0f), true, true);
            break;

        case 34:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 6, false);
            SysWork_StateStepIncrement();

        case 35:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(5.0f), FP_TIME(223.0f), FP_TIME(251.0f), true, false);
            func_800869E4(51, &g_SoundCmdIdx, g_SoundCmds);
            break;

        case 36:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(5.0f), FP_TIME(223.0f), FP_TIME(251.0f), true, false);
            func_80085E6C(FP_TIME(0.6f), false);
            break;

        case 37:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(5.0f), FP_TIME(223.0f), FP_TIME(251.0f), true, false);
            func_800869E4(55, &g_SoundCmdIdx, g_SoundCmds);
            break;

        case 38:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 9, false);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x4C, false);
            SysWork_StateStepIncrement();

        case 39:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(252.0f), FP_TIME(280.0f), true, false);
            func_800869E4(57, &g_SoundCmdIdx, g_SoundCmds);
            break;

        case 40:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(252.0f), FP_TIME(280.0f), true, true);
            break;

        case 41:
            func_80085EB8(0, g_SysWork.npcs_1A0, 5, false);
            SysWork_StateStepIncrement();

        case 42:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(281.0f), FP_TIME(296.0f), true, true);
            break;

        case 43:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x33, false);
            g_Timer0 = FP_TIME(297.0f);
            SysWork_StateStepIncrement();

        case 44:
            func_800869E4(58, &g_SoundCmdIdx, g_SoundCmds);
            break;

        case 45:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 90, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 1, false);
            SysWork_StateStepIncrement();

        case 46:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(298.0f), FP_TIME(308.0f), true, true);
            break;

        case 47:
            D_800DE250 = 0;

            func_8005DC1C(Sfx_Unk1357, &D_800CC8FC, FP_VOLUME(0.5f), 0);
            SysWork_StateStepIncrement();

        case 48:
            func_80088F94(g_SysWork.npcs_1A0,0 ,0);
            Sd_EngineCmd(19);
            Chara_Load(0, Chara_AirScreamer, &g_SysWork.npcCoords_FC0[0], NO_VALUE, 0, 0);
            func_80086470(3, InventoryItemId_Handgun, HANDGUN_AMMO_PICKUP_ITEM_COUNT, false);
            SysWork_StateStepIncrement();

        case 49:
            func_8008616C(2, true, 0, FP_TIME(0.0f), false);
            break;

        case 50:
            g_Timer0 = FP_TIME(308.0);
            func_80085E6C(FP_TIME(0.5f), false);
            break;

        case 51:
            SysWork_StateStepReset();
            break;

        case CUTSCENE_SKIP_STATE:
            func_8008616C(2, true, 0, FP_TIME(0.0f), false);
            break;

        case 53:
            //SysWork_NextStateStepSet(48); // TODO: Doesn't match?
            g_SysWork.sysStateStep_C[0] = 48;
            g_SysWork.field_28          = 0;
            g_SysWork.sysStateStep_C[1] = 0;
            g_SysWork.timer_2C          = 0;
            g_SysWork.sysStateStep_C[2] = 0;
            break;

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(SysState_Gameplay);

            vcReturnPreAutoCamWork(1);
            func_8008616C(0, false, 2, FP_TIME(0.0f), false);
            func_8008616C(0, false, 0, FP_TIME(0.0f), false);
            Sd_EngineCmd(23);

            Savegame_EventFlagSet(EventFlag_49);
            g_Timer0 = NO_VALUE;
            break;
    }

    if (g_Timer0 >= FP_TIME(0.0f))
    {
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPositionTarget, &g_CutsceneCameraLookAtTarget, NULL, g_Timer0, FS_BUFFER_11));
        vcUserCamTarget(&g_CutsceneCameraPositionTarget, NULL, true);
        vcUserWatchTarget(&g_CutsceneCameraLookAtTarget, NULL, true);
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, &D_800CC908, g_Timer0, FS_BUFFER_11);

        if (D_800DE250 != 0)
        {
            chara0 = &g_SysWork.npcs_1A0[0];
            chara0->model_0.anim_4.flags_2 |= AnimFlag_Visible;
            Dms_CharacterGetPosRot(&chara0->position_18, &chara0->rotation_24, &D_800CC910, g_Timer0, FS_BUFFER_11);
            return;
        }

        chara1 = &g_SysWork.npcs_1A0[0];
        chara1->model_0.anim_4.flags_2 &= ~AnimFlag_Visible;
    }
}

void Event_ToBeContinued(void) // 0x800DB790
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement();

        case 1:
            func_8008616C(0, true, 0, FP_TIME(0.0f), false);
            func_800862F8(0, FILE_TIM_CONTINUE_TIM, false);
            SysWork_StateStepIncrement();

        case 2:
            func_8008616C(1, true, 0, FP_TIME(0.0f), false);
            return;

        case 3:
            func_800862F8(1, FILE_1ST_2ZANKO80_TIM, false);
            return;

        case 4:
            func_8008616C(0, false, 0, FP_TIME(2.0f), false);
            SysWork_StateStepIncrement();

        case 5:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                SysWork_StateStepIncrement();
            }

            func_80085E6C(FP_TIME(4.0f), false);

            if (g_SysWork.sysStateStep_C[0] == 7)
            {
                g_SysWork.sysStateStep_C[0] = 6;
            }
            break;

        case 7:
            func_800862F8(7, FILE_TIM_COMESOON_TIM, false);
            break;

        case 8:
            func_8008616C(0, false, 0, FP_TIME(1.5f), false);
            func_8004690C(Sfx_Unk1321);
            func_8004690C(Sfx_Unk1322);
            SysWork_StateStepIncrement();

        case 9:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                SysWork_StateStepIncrement();
            }

            func_80085E6C(FP_TIME(4.0f), false);

            if (g_SysWork.sysStateStep_C[0] == 11)
            {
                g_SysWork.sysStateStep_C[0] = 10;
                break;
            }
            break;

        case 6:
        case 10:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            func_8008616C(2, true, 0, FP_TIME(1.5f), false);
            break;

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(SysState_Gameplay);
            Game_WarmBoot();

            g_SysWork.field_22A0 |= 1 << 0;
            break;
    }
}

const VECTOR3 D_800CCA1C =
{
    0x00000CCC,
    0xFFFFE99A,
    0x0010BB33,
};

const VECTOR3 D_800CCA28 =
{
    0x000004CC,
    0xFFFFE99A,
    0x0010BB33,
};

const VECTOR3 D_800CCA34 =
{
    0x00000CCC,
    0xFFFFE334,
    0x0010BB33,
};

const VECTOR3 D_800CCA40 =
{
    0x00000CCC,
    0xFFFFE99A,
    0x00111E66,
};

const VECTOR3 D_800CCA4C =
{
    0x000004CC,
    0xFFFFE99A,
    0x00111E66,
};

const VECTOR3 D_800CCA58 =
{
    0x00000CCC,
    0xFFFFE334,
    0x00108199,
};

const char D_800CCA64[] = "BIRD";

#define EventPositionInit(eventPos, x, y, z, arg4, arg5) \
    EventPositionSet(eventPos, FP_METER(x), FP_METER(y), FP_METER(z), arg4, arg5)

static inline void EventPositionSet(s_EventPosition* eventPos, s32 x, s32 y, s32 z, s32 arg4, s16 arg5)
{
    Math_Vector3Set(&eventPos->position_0, x, y, z);
    eventPos->field_C  = arg4;
    eventPos->field_10 = arg5;
}

void Event_AirScreamerIntroCutscene() // 0x800DBAA0
{
    s32 var_a1;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8003A16C();

            Savegame_EventFlagSet(EventFlag_50);

            Sd_EngineCmd(1321);
            Sd_EngineCmd(1322);

            Savegame_EventFlagSet(EventFlag_52);

            // Warp player.
            g_SysWork.player_4C.chara_0.position_18.vx = FP_METER(1.3f);
            g_SysWork.player_4C.chara_0.position_18.vz = FP_METER(269.7f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(5.0f);

            g_Timer0 = FP_TIME(26.0f);

            func_8008616C(0, true, 3, FP_TIME(0.0f), false);

            g_SoundCmdIdx = 0;
            SysWork_StateStepIncrement();

        case 1:
            func_80087EDC(30);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 91, 0);
            SysWork_StateStepIncrement();

        case 4:
            var_a1     = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_TIME(15.0f), Q12_SHIFT);
            g_Timer0 = MIN(var_a1, FP_TIME(37.0f));
            if (g_Timer0 >= FP_TIME(37.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 5:
            func_800869E4(62, &g_SoundCmdIdx, &D_800DE124); // "What's that?"
            break;

        case 6:
            func_80085E6C(FP_TIME(0.5f), false);
            break;

        case 7:
            func_800869E4(63, &g_SoundCmdIdx, &D_800DE124); // "Huh? Radio?"
            break;

        case 8:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 92, false);
            SysWork_StateStepIncrement();

        case 9:
            var_a1     = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_TIME(15.0f), Q12_SHIFT);
            g_Timer0 = MIN(var_a1, FP_TIME(52.0f));
            if (g_Timer0 >= FP_TIME(52.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 10:
            g_Timer0 = MAX(g_Timer0, FP_TIME(53.0f));
            D_800E23A1 = 0x80;
            Savegame_EventFlagSet(EventFlag_45);

            func_80085E6C(FP_TIME(1.5f), false);
            break;

        case 11:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 53, false);
            SysWork_StateStepIncrement();

        case 12:
            var_a1     = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_TIME(15.0f), Q12_SHIFT);
            g_Timer0 = MIN(var_a1, FP_TIME(75.0f));

            if (g_Timer0 >= FP_TIME(75.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 13:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 89, false);

            D_800E23A1 = 0xE0;
            Savegame_EventFlagSet(EventFlag_46);
            g_Timer0 = FP_TIME(76.0f);

            SysWork_StateStepIncrement();

        case 14:
            var_a1   = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_TIME(18.0f), Q12_SHIFT);
            g_Timer0 = MIN(var_a1, FP_TIME(115.0f));
            if (g_Timer0 >= FP_TIME(115.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 15:
            func_800CCB8C(&D_800CCA1C, &D_800CCA28, 0x2800, 0xCC, 0x999, 0x666, 0x199, 0);
            func_8005DC1C(Sfx_Unk1373, &D_800CCA34, FP_VOLUME(0.5f), 0);
            SysWork_StateStepIncrement();

        case 16:
            var_a1     = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_TIME(18.0f), Q12_SHIFT);
            g_Timer0 = MIN(var_a1, FP_TIME(146.0f));
            if (g_Timer0 >= FP_TIME(146.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 17:
            func_800CCB8C(&D_800CCA40, &D_800CCA4C, 0x3000, 0x147, 0x666, 0x666, 0xED, 0);
            func_8005DC1C(Sfx_Unk1374, &D_800CCA58, FP_VOLUME(0.5f), 0);
            func_8005DC1C(Sfx_Unk1375, &D_800CCA58, FP_VOLUME(0.5f), 0);
            SysWork_StateStepIncrement();

        case 18:
            var_a1     = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_TIME(18.0f), Q12_SHIFT);
            g_Timer0 = MIN(var_a1, FP_TIME(147.0f));
            if (g_Timer0 >= FP_TIME(147.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 19:
            func_800D3AC0(g_SysWork.npcs_1A0);
            SysWork_StateStepIncrement();

        case 20:
            var_a1     = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_TIME(18.0f), Q12_SHIFT);
            g_Timer0 = MIN(var_a1, FP_TIME(154.0f));
            if (g_Timer0 >= FP_TIME(154.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 21:
            Savegame_EventFlagSet(EventFlag_47);
            func_800D39F4(g_SysWork.npcs_1A0);
            func_8008616C(0, false, 2, FP_TIME(0.0f), false);

            g_Timer0 = NO_VALUE;

            vcReturnPreAutoCamWork(1);

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(SysState_Gameplay);
            Player_FallBackward();

            g_SysWork.flags_22A4 &= ~(1 << 5);
            g_SysWork.flags_22A4 &= ~(1 << 9);
            break;
    }

    if (g_Timer0 >= FP_TIME(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, &D_800CC908, g_Timer0, FS_BUFFER_11);

        if (g_SysWork.sysStateStep_C[0] >= 20)
        {
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, D_800CCA64, g_Timer0, FS_BUFFER_11);
            g_SysWork.npcs_1A0[0].position_18.vx += FP_MULTIPLY(Math_Sin(g_SysWork.npcs_1A0[0].rotation_24.vy), FP_METER(0.2f), Q12_SHIFT);
            g_SysWork.npcs_1A0[0].position_18.vz += FP_MULTIPLY(Math_Cos(g_SysWork.npcs_1A0[0].rotation_24.vy), FP_METER(0.2f), Q12_SHIFT);
        }

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPositionTarget, &g_CutsceneCameraLookAtTarget, NULL, g_Timer0, FS_BUFFER_11));
        vcUserCamTarget(&g_CutsceneCameraPositionTarget, NULL, true);
        vcUserWatchTarget(&g_CutsceneCameraLookAtTarget, NULL, true);
    }
}

void Event_PocketRadioItemTake() // 0x800DC34C
{
    Event_ItemTake(InventoryItemId_PocketRadio, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M0S01_PickupPocketRadio, 64);
    g_SavegamePtr->flags_AC |= 1 << 0;
}

void Event_FlashlightItemTake() // 0x800DC394
{
    Event_ItemTake(InventoryItemId_Flashlight, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M0S01_PickupFlashlight, 61);
    Game_TurnFlashlightOff();
}

void Event_MapItemTake() // 0x800DC3C8
{
    static const RECT IMG_BUFFER_RECT = { 320, 256, 160, 240 };

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + D_800A99B5);
            SysWork_StateStepIncrement();

        case 1:
            func_8008616C(2, true, 0, FP_TIME(0.0f), false);
            break;

        case 2:
            DrawSync(0);
            StoreImage(&IMG_BUFFER_RECT, IMAGE_BUFFER);
            DrawSync(0);
            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + D_800A99B5, FS_BUFFER_2, &g_MapImg);
            Screen_Init(SCREEN_WIDTH, 1);

            g_IntervalVBlanks = 1;

            GsSwapDispBuff();
            func_8008616C(0, false, 0, FP_TIME(0.0f), false);
            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrement();

        case 3:
            g_BackgroundColor = 88;

            Gfx_BackgroundSpriteDraw(&g_MapImg);
            MapMsg_DisplayAndHandleSelection(true, 59, 6, 4, 0, false);
            break;

        case 5:
            LoadImage(&IMG_BUFFER_RECT, IMAGE_BUFFER);
            DrawSync(0);
            Screen_Init(SCREEN_WIDTH, 0);
            func_8008616C(0, false, 0, FP_TIME(0.0f), false);
            SysWork_StateStepReset();
            break;

        case 6:
            g_SavegamePtr->hasMapsFlags_164 |= 1 << 1;

            Fs_QueueStartRead(FILE_ANIM_CAFE2_DMS, FS_BUFFER_11);
            SysWork_StateStepIncrement();

        case 4:
        case 7:
            g_BackgroundColor = 88;

            Gfx_BackgroundSpriteDraw(&g_MapImg);
            func_8008616C(2, true, 0, FP_TIME(0.0f), false);
            break;

        case 8:
            LoadImage(&IMG_BUFFER_RECT, IMAGE_BUFFER);
            DrawSync(0);
            Screen_Init(SCREEN_WIDTH, 0);
            func_8008616C(0, false, 0, FP_TIME(0.0f), false);
            SysWork_StateStepIncrement();

        case 9:
            func_80088D0C();
            SysWork_StateStepIncrement();

        case 10:
            // Set cutscene character.
            Chara_Spawn(Chara_AirScreamer, 0, FP_METER(0.0f), FP_METER(0.0f), FP_METER(0.0f), 12);
            DmsHeader_FixOffsets(FS_BUFFER_11);
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, D_800CCA64, 0, FS_BUFFER_11);

            // Set camera.
            vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPositionTarget, &g_CutsceneCameraLookAtTarget, NULL, 0, FS_BUFFER_11));
            vcUserCamTarget(&g_CutsceneCameraPositionTarget, NULL, true);
            vcUserWatchTarget(&g_CutsceneCameraLookAtTarget, NULL, true);

            // Warp player.
            g_SysWork.player_4C.chara_0.position_18.vx = FP_METER(4.585938f);
            g_SysWork.player_4C.chara_0.position_18.vz = FP_METER(267.285156f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(90.0f);

            // Set flags.
            g_SysWork.field_2290             |= 1 << 0;
            g_SysWork.field_228C             |= 1 << 0;
            Savegame_EventFlagSet(EventFlag_38);

            SysWork_StateStepIncrement();

        case 11:
            func_8008616C(1, false, 0, FP_TIME(0.0f), false);
            break;

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void Event_KitchenKnifeItemTake() // 0x800DC830
{
    Event_ItemTake(InventoryItemId_KitchenKnife, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M0S01_PickupKitchenKnife, 60);
}

/** Presumably a pickup function. Maybe debug or something unused and commented out. */
void Event_EmptyFunction() {}

void Event_HealthItemTake() // 0x800DC864
{
    s32 eventFlagIdx;
    u32 pickupType;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 13:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M0S01_HealthDrink0;
            break;

        case 14:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M0S01_HealthDrink1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void Event_AirScreamerDeath() // 0x800DC8C8
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8004690C(Sfx_Unk1321);
            func_8004690C(Sfx_Unk1322);

            Savegame_EventFlagClear(EventFlag_52);
            g_SoundCmdIdx = 0;
            SysWork_StateStepIncrement();

        case 1:
            func_800869E4(68, &g_SoundCmdIdx, &D_800DE128); // This_is_not_a_dream!
            break;

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_51);
            break;
    }
}

extern s_800BCE18_2BEC_0 D_800E23B0[1];
extern s_800BCE18_2BEC_0 D_800E23D0[1];
extern s_800BCE18_2BEC_0 D_800E23F0[3];
extern s_800BCE18_2BEC_0 D_800E2450[2];

extern s_EventPosition g_DefaultEventPosition;
extern s_EventThing g_EventThing4A0;
extern s_EventThing g_EventThing4D0;
extern s_EventThing g_EventThing500;
extern s_EventThing g_EventThing530;

void func_800DC9C8() // 0x800DC9C8
{
    D_800E23A1 = 224;
    Math_Vector3f(&g_DefaultEventPosition.position_0, 0.0f, 0.0f, 280.0f, Q12_SHIFT);

    func_8003C8F8(&D_800E23B0[0], "IN_BLD1_");
    func_8003C8F8(&D_800E23D0[0], "IN1_HIDE");
    func_8003C8F8(&D_800E23F0[0], "BRK_BLD1");
    func_8003C8F8(&D_800E23F0[1], "BRK_GLS1");
    func_8003C8F8(&D_800E23F0[2], "BRK_GLS2");
    func_8003C8F8(&D_800E2450[0], "OUT1_HID");
    func_8003C8F8(&D_800E2450[1], "OUT_BLD_");

    EventPositionInit(&g_EventThing4A0.eventPosition_1C, 5.09f, -1.01f, 274.12f, 0x16C0000, 0);
    func_8003C8F8(&g_EventThing4A0.field_0, "KNIFE_HI");

    EventPositionInit(&g_EventThing4D0.eventPosition_1C, 5.18f, -1.0f, 267.28f, 0x4EEFFDE, 0);
    func_8003C8F8(&g_EventThing4D0.field_0, "FLASH_HI");

    EventPositionInit(&g_EventThing500.eventPosition_1C, 5.24f, -1.0f, 267.21f, 0x2880000, 0);
    func_8003C8F8(&g_EventThing500.field_0, "MAP_HIDE");

    EventPositionInit(&g_EventThing530.eventPosition_1C, 2.31f, -0.6f, 273.95f, 0x6880000, 0);
    func_8003C8F8(&g_EventThing530.field_0, "RADIO_HI");

    if (Savegame_EventFlagGet(EventFlag_40) && !Savegame_EventFlagGet(EventFlag_47))
    {
        g_SysWork.flags_22A4 |= (1 << 5) | (1 << 9);

        Chara_Load(0, Chara_AirScreamer, &g_SysWork.npcCoords_FC0[0], NO_VALUE, NULL, NULL);

        if (Savegame_EventFlagGet(EventFlag_38))
        {
            func_80088D0C();
            Chara_Spawn(Chara_AirScreamer, 0, FP_METER(1048566.0f), FP_METER(280.0f), FP_METER(0.0f), 12);
            func_800D3A3C(&g_SysWork.npcs_1A0[0]);

            Fs_QueueStartRead(FILE_ANIM_CAFE2_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);
        }
    }

    if (Savegame_EventFlagGet(EventFlag_159) && !Savegame_EventFlagGet(EventFlag_134))
    {
        func_8003ED74(6, 3);
    }

    g_Timer0 = 0;
    D_800E2560 = 0;

    // Maybe preloading assets that might be used in map?
    func_8003C8F8(&D_800E2570[0], D_800A99E4.firstAidKitName_8);
    func_8003C8F8(&D_800E2570[1], D_800A99E4.healthDrinkName_C);
    func_8003C8F8(&D_800E2570[2], D_800A99E4.ampouleName_10);
    func_8003C8F8(&D_800E2570[3], D_800A99E4.handgunBulletsName_14);
    func_8003C8F8(&D_800E2570[4], D_800A99E4.shotgunShellsName_18);
    func_8003C8F8(&D_800E2570[5], D_800A99E4.rifleShellsName_1C);
}

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800DCCF4); // Set in map `header.func_40`.

void func_800DD2EC(s32 arg0) // 0x800DD2EC // called by func_800DCCF4 only
{
    static const SVECTOR3 DEFAULT_ROT = {};

    s32 i;

    if (arg0 == 0)
    {
        for (i = 0; i <= 0; i++)
        {
            func_8003C92C(&D_800E23D0[i], &g_DefaultEventPosition, &DEFAULT_ROT);
        }

        for (i = 0; i <= 0; i++)
        {
            func_8003C92C(&D_800E23B0[i], &g_DefaultEventPosition, &DEFAULT_ROT);
        }

        return;
    }

    if (arg0 == 1)
    {
        for (i = 0; i < 2; i++)
        {
            func_8003C92C(&D_800E2450[i], &g_DefaultEventPosition, &DEFAULT_ROT);
        }

        return;
    }

    for (i = 0; i <= 0; i++)
    {
        func_8003C92C(&D_800E23D0[i], &g_DefaultEventPosition, &DEFAULT_ROT);
    }

    for (i = 0; i < 3; i++)
    {
        func_8003C92C(&D_800E23F0[i], &g_DefaultEventPosition, &DEFAULT_ROT);
    }
}
