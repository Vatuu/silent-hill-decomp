#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s04.h"

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800C9578);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", g_MapOverlayHeader);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800CC7E0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800CC88C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800CCA24);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800CCB1C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800CD3AC);

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CD514

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CD694

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CD74C

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CD8B0

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CD8D0

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CE148

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CE534

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CF620

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CFA4C

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CFA88

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CFA94

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CFBF4

s32 func_800CFDCC()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CFDD4

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CFE84

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CFE9C

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CFEC4

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CFEDC

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CFF04

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CFFA8

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CFFB8

void func_800CFFC4(void) {}

void func_800CFFCC(void) {}

void func_800CFFD4(void) {}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800CFFDC);

void func_800D003C(void) {}

s32 func_800D0044()
{
    return 0;
}

void func_800D004C(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D0054

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D0064

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D00A4

#include "maps/shared/Ai_LarvalStalker_Update.h" // 0x800D00B8

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800CF168_1_s00); // 0x800D01D0

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800D140C_1_s00); // 0x800D2474

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800D1524_1_s00); // 0x800D258C

#include "maps/shared/Ai_LarvalStalker_Init.h" // 0x800D2764

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800D17BC_1_s00); // 0x800D2824

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800D1DBC_1_s00); // 0x800D2E24

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D3560

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D36F4

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800D3308_0_s00); // 0x800D3960

#include "maps/shared/sharedFunc_800D3B44_0_s00.h" // 0x800D419C

void sharedFunc_800D3EF4_0_s00(s_SubCharacter* chara) {} // 0x800D454C

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800D4924_0_s00); // 0x800D4554

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800D492C_0_s00); // 0x800D5124

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D5890

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800D54A8_0_s00); // 0x800D5CA0

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D6340

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800D5C64_0_s00); // 0x800D645C

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D67C4

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D6BC8

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D6D44

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D6D4C

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D6F04

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D6FF4

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", sharedData_800CAB70_0_s00);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800D6970_0_s00); // 0x800D7168

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800D70C4_0_s00); // 0x800D78BC

#include "maps/shared/sharedFunc_800D7BE8_0_s00.h" // 0x800D83E0

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D85FC

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800D87B0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800D8848);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800D8898);

void Ai_MonsterCybil_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D8908
{
    s_Model* extraModelPtr = &g_Ai_MonsterCybil_ExtraModel;

    if (chara->model_0.state_2 == 0)
    {
        Ai_MonsterCybil_Init(chara, extraModelPtr);
    }

    if (g_DeltaTime0 != Q12(0.0))
    {
        func_800D8B14(chara, extraModelPtr);
        func_800D8D7C(chara, extraModelPtr, coords);
        func_800D9790(chara, extraModelPtr);
        func_800D99E4(chara, extraModelPtr, anmHdr, coords);
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

    chara->field_E1_0 = 3;

    g_SysWork.npcs_1A0[0].properties_E4.larvalStalker.properties_E8[12].val16[1] = FP_ANGLE(90.0f);

    chara->model_0.anim_4.flags_2 |= AnimFlag_Visible | AnimFlag_Unlocked;

    chara->flags_3E |= CharaFlag_Unk9 | CharaFlag_Unk3;

    sharedData_800D16E4_2_s01 = 0;

    extraModel->anim_4.flags_2 |= AnimFlag_Visible | AnimFlag_Unlocked;

    chara->health_B0 = Q12(4000.0f);

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

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800D8A90);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800D8B14);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB118);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB178);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB1D8);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB208);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB238);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB250);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB278);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB2A0);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB2B4);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB2DC);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB304);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB364);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB3A4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800D8D7C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800D9790);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800D99E4);

void func_800D9AAC(s_SubCharacter* chara, s_Model* arg1) {}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800D9AB4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DA9C8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DB4CC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DB6FC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DB748);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DB81C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DB930);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DBA48);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DBD64);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DBE5C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DC018);

#include "maps/shared/Ai_Alessa_Update.h" // 0x800DC2B4

#include "maps/shared/sharedFunc_800CECFC_3_s02.h" // 0x800DC328

#include "maps/shared/sharedFunc_800CED44_3_s02.h" // 0x800DC370

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800CEEDC_3_s02); // 0x800DC508

#include "maps/shared/Ai_Alessa_Init.h" // 0x800DCA0C

#include "maps/shared/Ai_Dahlia_Update.h" // 0x800DCA30

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800CD280_2_s01); // 0x800DCAA4

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800CD2C8_2_s01); // 0x800DCAEC

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB554);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedSymbol_800CD4A0_2_s01); // 0x800DCCC4

#include "maps/shared/Ai_Dahlia_Init.h" // 0x800DD57C

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800DD5B8

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800DD5CC

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800DD610

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800DD628

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800DD634

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800DD648

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800DD65C

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800DD670

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800DD764);

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800DDDC8

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800DDDDC

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800DDDF0

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800DDEEC

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800DDFEC

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800DE064

void Ai_Flauros_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800DE0C4
{
    s32         i;
    s32         var_s1;
    s_AnimInfo* animInfo;

    if (chara->model_0.state_2 == 0)
    {
        chara->model_0.anim_4.alpha_A = Q12(0.0f);
        chara->model_0.state_2        = 1;
        chara->model_0.stateStep_3    = 0;
        Character_AnimSet(chara, ANIM_STATUS(1, true), 0);
    }

    if (chara->model_0.anim_4.time_4 <= Q12(21.0f))
    {
        if (chara->model_0.anim_4.time_4 > Q12(13.0f))
        {
            var_s1 = (chara->model_0.anim_4.time_4 - Q12(13.0f)) >> 3;
        }
        else
        {
            var_s1 = 0;
        }
    }
    else
    {
        var_s1 = Q12(1.0f);
    }

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coords);

    animInfo = &FLAUROS_ANIM_INFOS[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);

    for (i = 6; i < 11; i++)
    {
        func_800705E4(coords, i, var_s1, var_s1, var_s1);
    }
}

void Ai_Parasite_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800DE1CC
{
    s_AnimInfo* animInfo;

    if (chara->model_0.state_2 == 0)
    {
        chara->model_0.anim_4.alpha_A = Q12(0.0f);
        chara->model_0.state_2        = 1;
        chara->model_0.stateStep_3    = 0;
        Character_AnimSet(chara, ANIM_STATUS(1, true), 0);
    }

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coords);

    animInfo = &PARASITE_ANIM_INFOS[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
}

void func_800DE26C() {}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DE274);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DE350);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DE380);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DE5CC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DE62C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DE658);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DE8F0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DE95C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DEA4C);

void func_800DEA94(s32* arg0) // 0x800DEA94
{
    if (arg0 != NULL)
    {
        *arg0 = 0;
    }
}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DEAA8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DEB1C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DEC3C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DED30);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DED50);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DEDEC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DEF50);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DF134);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DF160);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DF2F0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DF41C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DF5B0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DF618);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DF64C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DF670);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DF6C4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DFA38);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DFB44);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DFBB0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DFC94);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DFD08);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DFD3C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E00F4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E0164);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E01F4);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB69C);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB6AC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E0204);

void func_800E02E0(void) // 0x800E02E0
{
    D_800ED588 = 0;
    func_800DE26C();
    func_800DF64C();
}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E030C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E0358);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E03C4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E05C8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E068C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E0878);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E08B8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E0BB0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E0C58);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E0CCC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E0D8C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E0DC4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E0F28);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E0FAC);

void func_800E10F8(void) // 0x800E10F8
{
    D_800ED58C = 0;
}

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800E1104

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E1114);

void func_800E1258(s32 arg0) // 0x800E1258
{
    (arg0 == 1) ? func_800E1290() : func_800E12D0();
}

void func_800E1290(void) // 0x800E1290
{
    func_8003640C(Savegame_EventFlagGet(EventFlag_440) ? 39 : 37);
}

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CB728);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E12D0);

void func_800E155C() {}

#include "maps/shared/sharedFunc_800DA8E8_0_s01.h" // 0x800E1564

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E15FC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E1CA0);

void func_800E1D48() {}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E1D50);

const char* MAP_MESSAGES[] =
{
    #include "maps/shared/mapMsg_common.h"
    "\tGotta'_go_find_Cybil! ~N\n\tNo_time_to_go_back. ~E ",
    "~J0(10)\t~E ",
    "~J0(10)\tCybil! ~E ",
    "~J0(2.3)\tWake_up!_Snap_out_of_it! ~E ",
    "~J0(1.0)\tCybil! ~E ",
    "~J0(4.7)\t...Harry? ~N\n\t\t\t...What...happened? ",
    "~J0(3.3)\tDon't_talk. ~N\n\t\t\tI'll_take_care_of_you. ~E ",
    "~J1(4.8)\tHarry... ~N\n\t\t\tWhy_did_they_take_your_daughter? ",
    "~J1(2.3)\tWhy_her? ",
    "~J1(3.0)\tI'm_not_sure,_myself. ",
    "~J1(4.3)\tBut_you_know,_Cheryl_isn't ~N\n\t\t\tmy_biological_daughter. ",
    "~J1(3.0)\tI_actually_haven't_told_her_yet. ",
    "~J1(3.3)\tShe_probably_already_knows ~N\n\t\t\tanyway,_though. ~E ",
    "~J1(3.9)\tWe_found_her_abandoned ~N\n\t\t\ton_the_side_of_the_highway. ",
    "~J1(3.3)\tNobody_knew ~N\n\t\t\twhere_she_came_from. ",
    "~J1(3.3)\tWe_didn't_have_any_kids ~N\n\t\t\tof_our_own. ",
    "~J1(2.4)\tMy_wife_was_sick, ",
    "~J1(3.4)\tand_it_didn't_look_like ~N\n\t\t\tshe_was_getting_any_better. ",
    "~J1(2.7)\tSo_we_took_Cheryl_in. ~E ",
    "~J1(3.1)\tSo_in_that_case... ",
    "~J1(5.2)\tThere_might_be_some_connection ~N\n\t\t\tbetween_Cheryl_and_this_town. ~E ",
    "~J1(3.4)\tSo_what_do_you_do_now? ",
    "~J1(3.5)\tCheryl_is_my_daughter. ~N\n\t\t\tI_will_save_her. ",
    "~J1(4.5)\tNo_matter_what. ~E ",
    "~J0(7.3)\t~E ",
    "~J0(7.0)\t~E ",
    "~J0(6.0)\tWhat_in_the_hell... ~N\n\t\t\tHow_could_this_have_happened? ~E ",
    "~J1(1.7)\tI_figured_you'd_show. ",
    "~J1(1.6)\tHold_it_right_there. ",
    "~J1(4.0)\tI_don't_know_who_you_are, ~N\n\t\t\twhat_you_are_trying_to_do, ~N\n\t\t\tand_I_don't_care. ",
    "~J1(1.6)\tJust_one_thing. ",
    "~J1(3.1)\tLet_Cheryl_go. ~N\n\t\t\tThat's_all_I_ask. ~E ",
    "~J0(1.0)\tWhat? ~E ",
    "~J0(1.0)\tDamn! ~E ",
    "~J0(1.2)\tHuh? ~E ",
    "~J0(1.5)\tWhat_is_this? ~E ",
    "~J0(1.4)\t~E ",
    "~J1(1.6)\tWhere's_Cheryl? ",
    "~J1(2.0)\tGive_me_back_my_daughter. ~E ",
    "~J0(3.2)\tWe_meet_at_last,_Alessa. ",
    "~J0(1.2)\t.......! ~E ",
    "~J1(1.8)\tDahlia_Gillespie...... ",
    "~J1(2.0)\tWhere's_Cheryl? ~N\n\t\t\tWhere_is_she!? ~E ",
    "~J1(1.2)\tAlessa. ",
    "~J1(4.0)\tThis_is_the_end_of ~N\n\t\t\tyour_little_game. ",
    "~J1(1.2)\tMama... ",
    "~J1(2.7)\tHuh? ~N\n\t\t\tCould_she_be...? ~E ",
    "~J1(4.6)\tYou've_been_a_ghastly_little_pest, ~N\n\t\t\thaven't_you?__Alessa? ",
    "~J1(2.0)\tI_was_careless. ",
    "~J1(3.5)\tThinking_you_couldn't_escape ~N\n\t\t\tfrom_our_spell. ",
    "~J1(4.5)\tBut_Mommy_didn't_know ~N\n\t\t\thow_much_you'd_grown. ",
    "~J1(4.3)\tThat's_why_I_couldn't_catch_you ~N\n\t\t\tall_by_myself. ",
    "~J1(2.8)\tBut_what_a_pity,_yes? ",
    "~J1(5.0)\tNow_you're_half_indebted ~N\n\t\t\tto_this_man_for_his_help. ",
    "~J1(2.7)\tHey! ~N\n\t\t\tWhat_are_you_talking_about? ",
    "~J1(6.9)\tAlessa._My_dear_little_girl... ~N\n\t\t\tThere_is_one_thing_left ~N\n\t\t\tI_need_you_to_do_for_me. ~E ",
    "~J0(2.3)\tNo. ~N\n\t\t\tGet_away_from_me. ",
    "~J0(1.8)\tBad_girl. ",
    "~J0(5.1)\tEverything_is_ready. ~N\n\t\t\tLet's_go_home_now. ~E ",
    "~J0(1.7)\tWhat's_going_on_here!? ~E ",
    "~J0(1.2)\t~E "
};

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CC424);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CC4A4);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CC4C4);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CC4CC);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CC4D4);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CC4DC);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E219C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E2724);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E2950);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E2CA0);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E3244);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E3EF4);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CC5B0);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CC5B8);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CC5C0);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CC5C8);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", jtbl_800CC5D0); // TODO: Why is this here?

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E558C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E5D44);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E5F54);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E636C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E6CB8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E7204);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E73B4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E74C4);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E75B8);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800E7944);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CC7C0);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CC7CC);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800CC7D8);
