#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "maps/shared.h"

extern s_AnimInfo D_800E1410[8];

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D2DC0

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D2F54

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D3308_0_s00); // 0x800D31C0

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D3B44_0_s00); // 0x800D39FC

void func_800D3DAC(void) {}

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D3DB4);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D4984);

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D50F0

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D5500);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D5BA0);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D5CBC);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D6024);

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D6428

void func_800D65A4(void) {}

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D65AC

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D6764

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D6854

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D6970_0_s00); // 0x800D69C8

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D70C4_0_s00); // 0x800D711C

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D7BE8_0_s00); // 0x800D7C40

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D7E5C

#include "maps/shared/Ai_Creaper_Update.h" // 0x800D8010

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D7C28_1_s02); // 0x800D80A0

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D7EE8_1_s02); // 0x800D8360

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D8244_1_s02); // 0x800D86BC

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D8768);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D8AFC);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D93A8);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D99A0);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D9BEC);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D983C_1_s02); // 0x800D9CB4

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D9960_1_s02); // 0x800D9DD8

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D99D0_1_s02); // 0x800D9E48

void Ai_LockerDeadBody_Update(s_SubCharacter* chara, s32 arg1, s32 arg2) // 0x800DA284
{
    s_AnimInfo* structPtr;

    if (chara->model_0.state_2 == 0)
    {
        chara->model_0.anim_4.keyframeIdx1_A = 0;
        chara->model_0.anim_4.animIdx_0      = 5;
        chara->model_0.anim_4.time_4         = 0;
        chara->model_0.anim_4.keyframeIdx0_8 = 0;
        chara->model_0.state_2++;
        chara->position_18.vy = 0;
    }

    if (!(g_SaveGamePtr->eventFlags_168[3] & (1 << 9)))
    {
        chara->model_0.anim_4.flags_2 &= ~2;
        chara->field_E0_8 = 0;
        return;
    }

    chara->model_0.anim_4.flags_2 |= 1 << 1;

    if (!(g_SaveGamePtr->eventFlags_168[3] & (1 << 10)))
    {
        if (chara->model_0.anim_4.animIdx_0 == 5)
        {
            chara->model_0.anim_4.animIdx_0 = 3;
        }

        chara->field_E0_8 = 0;
    }
    else
    {
        chara->model_0.anim_4.animIdx_0      = 7;
        chara->model_0.anim_4.time_4         = FP_TO(16, Q12_SHIFT);
        chara->model_0.anim_4.keyframeIdx0_8 = 16;
        chara->field_E0_8                    = 3;
    }

    func_80035B04(&chara->position_18, &chara->rotation_24, arg2);

    structPtr = &D_800E1410[chara->model_0.anim_4.animIdx_0];
    structPtr->funcPtr_0(chara, arg1, arg2, structPtr);

    chara->field_C8 = -0x4CC;
    chara->field_DC = 0xF5;
    chara->field_DE = 0xEE1;
    chara->field_CA = 0;
    chara->field_CC = 0;
    chara->field_CE = 0;
    chara->field_D8 = 0;
    chara->field_DA = 0;
    chara->field_D6 = 0;
    chara->field_D4 = 0x547;

    func_8005C814(&chara->field_D8, chara);
}

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800DA424

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DA434);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DA4D4);

void func_800DA630(void) {}

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DA638);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DA6CC);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DA760);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DA7F4);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DA8B0);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DA950);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DAA28);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DABC4);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DAF18);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DBEC8);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DC0F8);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DC2E4);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DC310);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DC780);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DC9A0);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DCB54);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DCD44);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DCDDC);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DD3AC);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DD688);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DE624);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DE828);
