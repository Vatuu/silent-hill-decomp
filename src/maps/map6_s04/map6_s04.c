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

#include "maps/shared/Player_ControlFreeze.h" // 0x800CFA94

#include "maps/shared/Player_ControlUnfreeze.h" // 0x800CFBF4

#include "maps/shared/sharedFunc_800D23EC_0_s00.h" // 0x800CFDCC

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CFDD4

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CFE84

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CFE9C

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CFEC4

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CFEDC

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CFF04

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CFFA8

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CFFB8

#include "maps/shared/sharedFunc_800D2E6C_0_s00.h" // 0x800CFFC4

#include "maps/shared/sharedFunc_800D2E74_0_s00.h" // 0x800CFFCC

#include "maps/shared/sharedFunc_800D2E7C_0_s00.h" // 0x800CFFD4

#include "maps/shared/sharedFunc_800D2E84_0_s00.h" // 0x800CFFDC

#include "maps/shared/sharedFunc_800D2E8C_0_s00.h" // 0x800D003C

#include "maps/shared/sharedFunc_800D2E94_0_s00.h" // 0x800D0044

#include "maps/shared/sharedFunc_800D2E9C_0_s00.h" // 0x800D004C

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D0054

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D0064

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D00A4

#include "maps/shared/Ai_LarvalStalker_Update.h" // 0x800D00B8

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", sharedFunc_800CF168_1_s00); // 0x800D01D0

#include "maps/shared/sharedFunc_800D140C_1_s00.h" // 0x800D2474

#include "maps/shared/sharedFunc_800D1524_1_s00.h" // 0x800D258C

#include "maps/shared/Ai_LarvalStalker_Init.h" // 0x800D2764

#include "maps/shared/sharedFunc_800D17BC_1_s00.h" // 0x800D2824

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

#include "maps/shared/sharedFunc_800D5C64_0_s00.h" // 0x800D645C

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D67C4

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D6BC8

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D6D44

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D6D4C

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D6F04

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D6FF4

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

    func_8003DD80(Chara_MonsterCybil, UNK_PACKED_DATA(1, 1));
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
