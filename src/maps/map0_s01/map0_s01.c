#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/map0_s01.h"

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800CCB8C);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800CD1F8);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800CE000);

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

void func_800D2094(void) // 0x800D2094
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

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D21E4_0_s01); // 0x800D21E4

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D2200_0_s01); // 0x800D2200

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D2274_0_s01); // 0x800D2274

void func_800D2364(s32 arg0) // 0x800D2364
{
    func_8005DC1C(Sfx_Unk1590, arg0 + 24, FP_VOLUME(0.5f), 0);
}

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D2390_0_s01); // 0x800D2390

#include "maps/shared/Ai_AirScreamer_Init.h" // 0x800D2974

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D2B00_0_s01); // 0x800D2B00

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D2B10_0_s01); // 0x800D2B10

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D2B28_0_s01); // 0x800D2B28

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D2B4C_0_s01); // 0x800D2B4C

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D2BB0_0_s01); // 0x800D2BB0

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D2BE4_0_s01); // 0x800D2BE4

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

    sharedData_800E21D0_0_s01 |= 1 << 31;
    cond = false;

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            cond = true;
            chara->model_0.anim_4.animIdx_0 = 47;
            chara->model_0.stateStep_3 = 1;
            break;

        case 2:
            cond = true;
            chara->model_0.anim_4.animIdx_0 = 49;
            chara->model_0.stateStep_3 = 3;

        case 1:
        case 3:
            chara->properties_E4.player.flags_11C |= 1 << 16;

        default:
            break;

        case 4:
            cond = true;
            chara->model_0.anim_4.animIdx_0 = 31;
            chara->model_0.stateStep_3 = 5;

        case 5:
            chara->properties_E4.player.flags_11C &= ~(1 << 16);
            break;

        case 6:
            if (chara->model_0.anim_4.animIdx_0 == 39)
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

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D7120);

s32 func_800D71F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x800D71F0
{
    s32 var_v1;
    s32 arg2Sqr;

    if (arg1 == 0)
    {
        return arg0;
    }

    if (arg2 != 0)
    {
        if (arg1 < 0)
        {
            arg1 = -arg1;
        }

        arg2Sqr  = FP_MULTIPLY_PRECISE(arg2, arg2, Q12_SHIFT) << Q12_SHIFT;
        arg2Sqr /= arg1 * 2;

        if (arg3 <= 0)
        {
            arg3 = -arg3;
        }

        if (arg3 < arg2Sqr)
        {
            var_v1 = SquareRoot12(FP_MULTIPLY_PRECISE(arg3, arg1 * 2, Q12_SHIFT));
            if (var_v1 == 0)
            {
                var_v1 = 1;
            }

            if (arg2 > 0)
            {
                if (var_v1 < arg2)
                {
                    arg2 = var_v1;
                }
            }
            else
            {
                if (arg2 < -var_v1)
                {
                    arg2 = -var_v1;
                }
            }
        }
    }

    return func_800D7120(arg0, arg1, arg2);
}

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D72E8);

s32 func_800D7440(VECTOR* vec0, VECTOR* vec1, s_SubCharacter* chara) // 0x800D7440
{
    s32     temp_s2;
    s32     posY;
    s32     result;
    s32     cond;
    VECTOR* vecCpy;

    vecCpy = vec0;

    func_800D81D0(chara);
    func_800D8714(chara, chara->moveSpeed_38, chara->headingAngle_3C);
    func_800D87FC(chara);

    result = func_80069B24(vecCpy, vec1, chara);

    posY    = chara->position_18.vy;
    temp_s2 = func_80080884(chara->position_18.vx + vecCpy->vx,
                            chara->position_18.vz + vecCpy->vz);

    if (sharedFunc_800D4A80_0_s01(chara) != 4)
    {
        if (vec1->vy > 0 && temp_s2 < (posY - FP_METER(0.5f)))
        {
            vecCpy->vx = 0;
            vecCpy->vz = 0;
        }
    }
    else if (temp_s2 < posY)
    {
        vecCpy->vx = 0;
        vecCpy->vz = 0;
    }

    if ((FP_FROM(vec1->vx, Q4_SHIFT) != FP_FROM(vecCpy->vx, Q4_SHIFT)) ||
        (FP_FROM(vec1->vz, Q4_SHIFT) != FP_FROM(vecCpy->vz, Q4_SHIFT)))
    {
        result = 1;
    }

    func_800D8244(chara);
    return result;
}

#include "maps/shared/sharedFunc_800D7560_0_s01.h" // 0x800D7560

void func_800D76A0(s_SubCharacter* chara) // 0x800D76A0
{
    if (chara->model_0.anim_4.animIdx_0 == 47 ||
        chara->model_0.anim_4.animIdx_0 == 27 ||
        chara->model_0.anim_4.animIdx_0 == 29)
    {
        if (func_800D77D0(chara) != 0)
        {
            chara->model_0.anim_4.animIdx_0 = 50;
        }
    }
    else if(chara->model_0.anim_4.animIdx_0 == 51)
    {
        if (func_800D77D0(chara) == 0)
        {
            chara->model_0.anim_4.animIdx_0 = 46;
        }
    }
}

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D7714);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D77D0);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D7AB0_0_s01); // 0x800D7AB0

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D7B14);

void func_800D7E88(s_Model* model) // 0x800D7E88
{
    func_800449AC(model, func_80044918(&model->anim_4));
}

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D7EBC_0_s01); // 0x800D7EBC

#include "maps/shared/sharedFunc_800D81B0_0_s01.h" // 0x800D81B0

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D81D0);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D8244);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D82B8_0_s01); // 0x800D82B8

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D8714);

void func_800D87FC() {}

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
    g_Gfx_ScreenFade = ScreenFadeState_FadeInSteps;

    Gfx_DebugStringPosition(100, 100);
    Gfx_DebugStringDraw(&D_800CBAD4);
    Gfx_LoadingScreen_BackgroundTexture();
}

#include "maps/shared/sharedFunc_800DA8E8_0_s01.h" // 0x800DA8E8

