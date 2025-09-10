#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "maps/map1/map1_s03.h"
#include "main/rng.h"
#include "maps/shared.h"

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D2DC0

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D2F54

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D3308_0_s00); // 0x800D31C0

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D3B44_0_s00); // 0x800D39FC

void func_800D3DAC(void) {}

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D3DB4);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D4984);

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D50F0

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D5500);

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D5BA0

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

#include "maps/shared/Ai_Creaper_Init.h" // 0x800D80A0

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D7EE8_1_s02); // 0x800D8360

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D8244_1_s02); // 0x800D86BC

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D8768);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D8AFC);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D93A8);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D99A0);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800D9BEC);

#include "maps/shared/sharedFunc_800D983C_1_s02.h" // 0x800D9CB4

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D9960_1_s02); // 0x800D9DD8

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", sharedFunc_800D99D0_1_s02); // 0x800D9E48

void Ai_LockerDeadBody_Update(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coords) // 0x800DA284
{
    s_AnimInfo* animInfo;

    if (chara->model_0.state_2 == 0)
    {
        chara->model_0.anim_4.alpha_A = FP_ALPHA(0.0f);
        Character_AnimSet(chara, ANIM_STATUS(2, true), 0);
        chara->model_0.state_2++;
        chara->position_18.vy = FP_METER(0.0f);
    }

    if (!Savegame_EventFlagGet(EventFlag_105))
    {
        chara->model_0.anim_4.flags_2 &= ~AnimFlag_Visible;
        chara->field_E0_8              = 0;
        return;
    }

    chara->model_0.anim_4.flags_2 |= AnimFlag_Visible;

    if (!Savegame_EventFlagGet(EventFlag_106))
    {
        if (chara->model_0.anim_4.status_0 == ANIM_STATUS(2, true))
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(1, true);
        }

        chara->field_E0_8 = 0;
    }
    else
    {
        Character_AnimSet(chara, ANIM_STATUS(3, true), 16);
        chara->field_E0_8 = 3;
    }

    func_80035B04(&chara->position_18, &chara->rotation_24, coords);

    animInfo = &LOCKER_DEAD_BODY_ANIM_INFOS[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&chara->model_0, anmHeader, coords, animInfo);

    chara->field_C8         = -0x4CC;
    chara->field_D8.field_4 = 0xF5;
    chara->field_D8.field_6 = 0xEE1;
    chara->field_CA         = 0;
    chara->field_CC         = 0;
    chara->field_CE         = 0;
    chara->field_D8.field_0 = 0;
    chara->field_D8.field_2 = 0;
    chara->field_D6         = 0;
    chara->field_D4         = 0x547;

    func_8005C814(&chara->field_D8, chara);
}

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800DA424

#include "maps/shared/sharedFunc_800D7758_1_s00.h" // 0x800DA434

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

#include "maps/shared/sharedFunc_800DA8E8_0_s01.h" // 0x800DCD44

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DCDDC);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DD3AC);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DD688);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DE624);

INCLUDE_ASM("asm/maps/map1_s03/nonmatchings/map1_s03_2", func_800DE828);
