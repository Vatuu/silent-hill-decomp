#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
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

            D_800E2160.vector_0.vx = Q19_12(-0.30f);
            D_800E2160.vector_0.vz = Q19_12(275.0f);
            D_800E2160.vector_C.vx = Q19_12(-0.30f);
            D_800E2160.vector_C.vz = Q19_12(265.0f);

            sharedData_800DD796_0_s01 = 1;

            if (arg3 == -1)
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
            D_800DD78B = g_DeltaTime0 == 0;

            func_8003EDB8(&D_800E214C, &D_800E2150);

            if (sharedData_800E0CB6_0_s00 != sharedData_800E0CB4_0_s00)
            {
                if (D_800DD78B == 0)
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
                        case 0x4:
                        case 0x6:
                            sharedData_800DD78C_0_s01[i] = temp_s0_2;
                            break;

                        case 0x5:
                        case 0x7:
                            var_v0 = temp_s0_2 * 2;
                            sharedData_800DD78C_0_s01[i] = var_v0;
                            break;

                        case 0x20:
                        case 0x30:
                            sharedData_800DD78C_0_s01[i] = temp_a2;
                            break;

                        case 0x25:
                        case 0x27:
                        case 0x35:
                        case 0x37:
                            var_v0 = temp_s0_2 + 150;
                            sharedData_800DD78C_0_s01[i] = var_v0;
                            break;

                        case 0x28:
                        case 0x38:
                            var_v0 = temp_a2 * 2;
                            sharedData_800DD78C_0_s01[i] = var_v0;
                            break;

                        case 0x2C:
                        case 0x2E:
                        case 0x3C:
                        case 0x3E:
                            var_v0 = temp_a2 + 150;
                            sharedData_800DD78C_0_s01[i] = var_v0;
                            break;

                        case 0x0:
                            sharedData_800DD78C_0_s01[i] = 0;
                            break;

                        case 0x24:
                        case 0x26:
                        case 0x34:
                        case 0x36:
                            var_v0 = 150;
                            sharedData_800DD78C_0_s01[i] = var_v0;
                            break;

                        case 0x2D:
                        case 0x2F:
                        case 0x3D:
                        case 0x3F:
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
                            case 0x4:
                            case 0x6:
                            case 0x20:
                            case 0x30:
                                var_v0_3 = sharedData_800DD78C_0_s01[i] < (75 + 1);
                                sharedData_800DD796_0_s01 = var_v0_3 ^ 1;
                                break;

                            case 0x5:
                            case 0x7:
                            case 0x28:
                            case 0x38:
                                var_v0_3 = sharedData_800DD78C_0_s01[i] < (150 + 1);
                                sharedData_800DD796_0_s01 = var_v0_3 ^ 1;
                                break;

                            case 0x8:
                            case 0x9:
                            case 0xA:
                            case 0xB:
                            case 0xC:
                            case 0xD:
                            case 0xE:
                            case 0xF:
                            case 0x10:
                            case 0x11:
                            case 0x12:
                            case 0x13:
                            case 0x14:
                            case 0x15:
                            case 0x16:
                            case 0x17:
                            case 0x18:
                            case 0x19:
                            case 0x1A:
                            case 0x1B:
                            case 0x1C:
                            case 0x1D:
                            case 0x1E:
                            case 0x1F:
                            case 0x21:
                            case 0x22:
                            case 0x23:
                            case 0x24:
                            case 0x25:
                            case 0x26:
                            case 0x27:
                            case 0x29:
                            case 0x2A:
                            case 0x2B:
                            case 0x2C:
                            case 0x2D:
                            case 0x2E:
                            case 0x2F:
                            case 0x31:
                            case 0x32:
                            case 0x33:
                            case 0x34:
                            case 0x35:
                            case 0x36:
                            case 0x37:
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

            func_800CE8A8(g_Particles);
            SetSp(temp_s0_3);

            for(i = sharedData_800DD78C_0_s01[0] + sharedData_800DD78C_0_s01[1]; i < 300; i++)
            {
                g_Particles[i].stateStep_1E = 0;
            }
    }

    g_ParticleVectors1 = g_ParticleVectors0;
}


#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CE4C4

#include "maps/shared/sharedFunc_800CE59C_0_s01.h" // 0x800CE59C

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800CE8A8);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800CEE2C);

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CF2A4

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800CF3F4);

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CF7BC

void func_800CF8E8() {}

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

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D16C4);

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
        keyframeIdx = func_80044918(&chara->model_0.anim_4)->keyframeIdx0_C;
        chara->model_0.anim_4.keyframeIdx0_8 = keyframeIdx;
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
    func_800449AC(model, func_80044918(&model->anim_4));
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

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D9C60);

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800DA2C4

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800DA2D8

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800DA2EC

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800DA3E8

#include "maps/shared/sharedFunc_800D921C_0_s00.h" // 0x800DA49C

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

    if (!(g_SavegamePtr->eventFlags_168[1] & (1 << 16)))
    {
        if (!(g_SavegamePtr->eventFlags_168[1] & (1 << 17)))
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
    if (!(g_SavegamePtr->eventFlags_168[4] & (1 << 18)))
    {
        if (!(g_SavegamePtr->eventFlags_168[1] & ((1 << 16) | (1 << 17))))
        {
            var1 = 0xF0000;
            if ((g_SavegamePtr->eventFlags_168[1] & (1 << 7)) && g_GameWork.soundCmd_5B2 == 9)
            {
                var0 = 2;
            }
            else
            {
                var0 = 0x201;
            }
        }
        else if (g_SavegamePtr->eventFlags_168[1] & (1 << 15))
        {
            if (!(g_SavegamePtr->eventFlags_168[1] & (1 << 16)))
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
    g_Gfx_ScreenFade = SCREEN_FADE_STATUS(ScreenFadeState_FadeInSteps, false);

    Gfx_DebugStringPosition(100, 100);
    Gfx_DebugStringDraw(&D_800CBAD4);
    Gfx_LoadingScreen_BackgroundTexture();
}

#include "maps/shared/sharedFunc_800DA8E8_0_s01.h" // 0x800DA8E8

