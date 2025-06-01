#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map1/map1_s01.h"

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D1AF0

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D1C84

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", sharedFunc_800D3308_0_s00); // 0x800D1EF0

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", sharedFunc_800D3B44_0_s00); // 0x800D272C

void func_800D2ADC() {}

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D2AE4);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D36B4);

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D3E20

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D4230);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D48D0);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D49EC);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D4D54);

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D5158

void func_800D52D4() {}

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D52DC);

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D5494

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D5584

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", sharedFunc_800D6970_0_s00); // 0x800D56F8

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", sharedFunc_800D70C4_0_s00); // 0x800D5E4C

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", sharedFunc_800D7BE8_0_s00); // 0x800D6970

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D6B8C

void Ai_Cat_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords) // 0x800D6D40
{
    s_AnimInfo* animInfo;
    s32         var_a0;

    if (chara->model_0.state_2 == 0)
    {
        chara->model_0.state_2                                      = 1;
        chara->model_0.anim_4.animIdx_0                             = 7;
        chara->model_0.anim_4.time_4                                = FP_TO(7, Q12_SHIFT);
        chara->model_0.anim_4.keyframeIdx1_A                        = 0;
        chara->model_0.stateStep_3                                  = 0;
        chara->model_0.anim_4.keyframeIdx0_8                        = 7;
        chara->position_18.vy                                       = 0;
        chara->properties_E4.larvalStalker.properties_E8[0].val8[0] = 0;
    }

    if (chara->model_0.stateStep_3 == 0)
    {
        if (chara->model_0.state_2 == 2)
        {
            chara->model_0.anim_4.animIdx_0      = 3;
            chara->model_0.anim_4.time_4         = FP_TO(7, Q12_SHIFT);
            chara->model_0.anim_4.keyframeIdx0_8 = 7;
        }
        else if (chara->model_0.state_2 == 3)
        {
            chara->model_0.anim_4.animIdx_0      = 5;
            chara->model_0.anim_4.time_4         = FP_TO(23, Q12_SHIFT);
            chara->model_0.anim_4.keyframeIdx0_8 = 23;
        }

        chara->model_0.stateStep_3++;
    }

    func_80035B04(&chara->position_18, &chara->rotation_24, coords);

    animInfo = &g_Ai_Cat_AnimInfo[chara->model_0.anim_4.animIdx_0];
    animInfo->funcPtr_0(chara, arg1, coords, animInfo);

    var_a0 = 0;
    if (chara->model_0.anim_4.animIdx_0 == 3)
    {
        if (((u8)chara->properties_E4.larvalStalker.properties_E8[0].val8[0] == 0 &&
             (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 20) < 3u) ||
            ((u8)chara->properties_E4.larvalStalker.properties_E8[0].val8[0] != 0 &&
             (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 25) < 3u))
        {
            var_a0 = 1;
        }
    }
    else
    {
        if (((u8)chara->properties_E4.larvalStalker.properties_E8[0].val8[0] == 0 &&
             (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 29) < 3u) ||
            ((u8)chara->properties_E4.larvalStalker.properties_E8[0].val8[0] != 0 &&
             (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 36) < 3u))
        {
            var_a0 = 1;
        }
    }

    if (var_a0 != 0)
    {
        func_8005DD44(0x5A7, &chara->position_18, 128, TEST_RNG(4) - 7);
        chara->properties_E4.larvalStalker.properties_E8[0].val8[0] ^= 1;
    }
}

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D6F34

#include "maps/shared/sharedFunc_800D7758_1_s00.h" // 0x800D6F44

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D6FE4);

void func_800D7050() {}

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D7058);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D70EC);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D7180);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D7214);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D72B0);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D72DC);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D7308);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D76F4);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D7830);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D7864);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D7EEC);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D7F18);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D857C);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D8794);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D87C0);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D91EC);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D9514);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D9DDC);

INCLUDE_ASM("asm/maps/map1_s01/nonmatchings/map1_s01_2", func_800D9EC4);
