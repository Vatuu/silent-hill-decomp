#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s04.h"

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D3560

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D36F4

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", sharedFunc_800D3308_0_s00); // 0x800D3960

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", sharedFunc_800D3B44_0_s00); // 0x800D419C

void func_800D454C() {}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800D4554);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800D5124);

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D5890

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800D5CA0);

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D6340

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800D645C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800D67C4);

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D6BC8

void func_800D6D44() {}

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D6D4C

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D6F04

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D6FF4

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", sharedFunc_800D6970_0_s00); // 0x800D7168

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", sharedFunc_800D70C4_0_s00); // 0x800D78BC

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", sharedFunc_800D7BE8_0_s00); // 0x800D83E0

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D85FC

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800D87B0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800D8848);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800D8898);

void Ai_MonsterCybil_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords) // 0x800D8908
{
    s_Model* extraModelPtr = &g_Ai_MonsterCybil_ExtraModel;

    if (chara->model_0.state_2 == 0)
    {
        Ai_MonsterCybil_Init(chara, extraModelPtr);
    }

    if (g_DeltaTime0 != 0)
    {
        func_800D8B14(chara, extraModelPtr);
        func_800D8D7C(chara, extraModelPtr, coords);
        func_800D9790(chara, extraModelPtr);
        func_800D99E4(chara, extraModelPtr, arg1, coords);
        func_800DB4CC(chara, extraModelPtr, coords);
        func_800D9AAC(chara, extraModelPtr);
    }
}

void Ai_MonsterCybil_Init(s_SubCharacter* chara, s_Model* extraModel) // 0x800D89CC
{
    chara->model_0.state_2++;
    extraModel->state_2++;

    chara->model_0.stateStep_3 = 0;
    extraModel->stateStep_3    = 0;

    chara->field_E0_8 = 3;

    g_SysWork.npcs_1A0[0].properties_E4.larvalStalker.properties_E8[12].val16[1] = FP_ANGLE(90.0f);

    chara->model_0.anim_4.flags_2 |= AnimFlag_Visible | AnimFlag_Unk1;

    chara->flags_3E |= CharaFlag_Unk9 | CharaFlag_Unk3;

    sharedData_800D16E4_2_s01 = 0;

    extraModel->anim_4.flags_2 |= AnimFlag_Visible | AnimFlag_Unk1;

    chara->health_B0 = FP_HEALTH(4000.0f);

    g_SysWork.npcs_1A0[0].properties_E4.larvalStalker.properties_E8[7].val16[0] = 10;
    g_SysWork.npcs_1A0[0].properties_E4.larvalStalker.properties_E8[5].val16[1] = 0;
    g_SysWork.npcs_1A0[0].properties_E4.larvalStalker.properties_E8[7].val16[1] = 0;
    g_SysWork.npcs_1A0[0].properties_E4.larvalStalker.properties_E8[2].val32    = 0;
    g_SysWork.npcs_1A0[0].properties_E4.larvalStalker.properties_E8[8].val32    = 0;
    g_SysWork.npcs_1A0[0].properties_E4.larvalStalker.properties_E8[9].val32    = 0;
    g_SysWork.npcs_1A0[0].properties_E4.larvalStalker.properties_E8[4].val32    = 0;
    g_SysWork.npcs_1A0[0].properties_E4.larvalStalker.properties_E8[11].val8[2] = 0;
    g_SysWork.npcs_1A0[0].properties_E4.larvalStalker.properties_E8[3].val32    = 0;

    func_8003DD80(Chara_MonsterCybil, 17);
}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800D8A90);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800D8B14);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800D8D7C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800D9790);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800D99E4);

void func_800D9AAC(s_SubCharacter* chara, s_Model* arg1) {}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800D9AB4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DA9C8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DB4CC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DB6FC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DB748);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DB81C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DB930);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DBA48);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DBD64);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DBE5C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DC018);

#include "maps/shared/Ai_Alessa_Update.h" // 0x800DC2B4

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", sharedFunc_800CECFC_3_s02); // 0x800DC328

#include "maps/shared/sharedFunc_800CED44_3_s02.h" // 0x800DC370

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", sharedFunc_800CEEDC_3_s02); // 0x800DC508

#include "maps/shared/Ai_Alessa_Init.h" // 0x800DCA0C

#include "maps/shared/Ai_Dahlia_Update.h" // 0x800DCA30

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", sharedFunc_800CD280_2_s01); // 0x800DCAA4

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", sharedFunc_800CD2C8_2_s01); // 0x800DCAEC

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", sharedSymbol_800CD4A0_2_s01); // 0x800DCCC4

#include "maps/shared/Ai_Dahlia_Init.h" // 0x800DD57C

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800DD5B8

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800DD5CC

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800DD610

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800DD628

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800DD634

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800DD648

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800DD65C

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800DD670

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DD764);

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800DDDC8

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800DDDDC

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800DDDF0

// TODO: Requires rodata for jump table
// #include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800DDEEC
INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", sharedFunc_800D9188_0_s00); // 0x800DDEEC

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800DDFEC

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800DE064

void Ai_Flauros_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords) // 0x800DE0C4
{
    s32         i;
    s32         var_s1;
    s_AnimInfo* animInfo;

    if (chara->model_0.state_2 == 0)
    {
        chara->model_0.anim_4.keyframeIdx1_A = 0;
        chara->model_0.state_2               = 1;
        chara->model_0.stateStep_3           = 0;
        chara->model_0.anim_4.status_0      = ANIM_STATUS(1, true);
        chara->model_0.anim_4.time_4         = 0;
        chara->model_0.anim_4.keyframeIdx0_8 = 0;
    }

    if (chara->model_0.anim_4.time_4 <= FP_TO(21, Q12_SHIFT))
    {
        if (chara->model_0.anim_4.time_4 > FP_TO(13, Q12_SHIFT))
        {
            var_s1 = (chara->model_0.anim_4.time_4 - FP_TO(13, Q12_SHIFT)) >> 3;
        }
        else
        {
            var_s1 = 0;
        }
    }
    else
    {
        var_s1 = FP_TO(1, Q12_SHIFT);
    }

    func_80035B04(&chara->position_18, &chara->rotation_24, coords);

    animInfo = &g_Ai_Flauros_AnimInfo[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(chara, arg1, coords, animInfo);

    for (i = 6; i < 11; i++)
    {
        func_800705E4(coords, i, var_s1, var_s1, var_s1);
    }
}

void Ai_Parasite_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords) // 0x800DE1CC
{
    s_AnimInfo* animInfo;

    if (chara->model_0.state_2 == 0)
    {
        chara->model_0.anim_4.keyframeIdx1_A = 0;
        chara->model_0.state_2               = 1;
        chara->model_0.stateStep_3           = 0;
        chara->model_0.anim_4.status_0       = ANIM_STATUS(1, true);
        chara->model_0.anim_4.time_4         = 0;
        chara->model_0.anim_4.keyframeIdx0_8 = 0;
    }

    func_80035B04(&chara->position_18, &chara->rotation_24, coords);

    animInfo = &g_Ai_Parasite_AnimInfo[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(chara, arg1, coords, animInfo);
}

void func_800DE26C() {}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE274);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE350);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE380);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE5CC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE62C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE658);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE8F0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DE95C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DEA4C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DEA94);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DEAA8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DEB1C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DEC3C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DED30);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DED50);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DEDEC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DEF50);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF134);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF160);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF2F0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF41C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF5B0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF618);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF64C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF670);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DF6C4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DFA38);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DFB44);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DFBB0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DFC94);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DFD08);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800DFD3C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E00F4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0164);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E01F4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0204);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E02E0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E030C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0358);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E03C4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E05C8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E068C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0878);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E08B8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0BB0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0C58);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0CCC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0D8C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0DC4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0F28);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E0FAC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E10F8);

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800E1104

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E1114);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E1258);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E1290);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E12D0);

void func_800E155C() {}

#include "maps/shared/sharedFunc_800DA8E8_0_s01.h" // 0x800E1564

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E15FC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E1CA0);

void func_800E1D48() {}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E1D50);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E219C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E2724);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E2950);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E2CA0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E3244);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E3EF4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E558C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E5D44);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E5F54);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E636C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E6CB8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E7204);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E73B4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E74C4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E75B8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04_2", func_800E7944);
