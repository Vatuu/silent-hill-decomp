#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s04.h"

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", D_800C9578);

INCLUDE_RODATA("asm/maps/map6_s04/nonmatchings/map6_s04", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB7F4_1_s01.h" // 0x800CC7E0

#include "maps/shared/sharedFunc_800CB8A0_1_s01.h" // 0x800CC88C

#include "maps/shared/sharedFunc_800CBA38_1_s01.h" // 0x800CCA24

#include "maps/shared/sharedFunc_800CBB30_1_s01.h" // 0x800CCB1C

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CD3AC

#include "maps/shared/Player.h"

#include "maps/shared/Ai_LarvalStalker_Update.h" // 0x800D00B8

#include "maps/shared/sharedFunc_800CF168_1_s00.h" // 0x800D01D0

#include "maps/shared/sharedFunc_800D140C_1_s00.h" // 0x800D2474

#include "maps/shared/sharedFunc_800D1524_1_s00.h" // 0x800D258C

#include "maps/shared/Ai_LarvalStalker_Init.h" // 0x800D2764

#include "maps/shared/sharedFunc_800D17BC_1_s00.h" // 0x800D2824

#include "maps/shared/sharedFunc_800D1DBC_1_s00.h" // 0x800D2E24

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D3560

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D36F4

#include "maps/shared/sharedFunc_800D3308_0_s00.h" // 0x800D3960

#include "maps/shared/sharedFunc_800D3B44_0_s00.h" // 0x800D419C

void sharedFunc_800D3EF4_0_s00(s_SubCharacter* chara) {} // 0x800D454C

#include "maps/shared/sharedFunc_800D4924_0_s00.h" // 0x800D4554

#include "maps/shared/sharedFunc_800D492C_0_s00.h" // 0x800D5124

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D5890

#include "maps/shared/sharedFunc_800D54A8_0_s00.h" // 0x800D5CA0

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D6340

#include "maps/shared/sharedFunc_800D5C64_0_s00.h" // 0x800D645C

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D67C4

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D6BC8

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D6D44

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D6D4C

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D6F04

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D6FF4

#include "maps/shared/sharedFunc_800D6970_0_s00.h" // 0x800D7168

#include "maps/shared/sharedFunc_800D70C4_0_s00.h" // 0x800D78BC

#include "maps/shared/sharedFunc_800D7BE8_0_s00.h" // 0x800D83E0

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D85FC

void func_800D87B0(s_SubCharacter* chara) // 0x800D87B0
{
    if (chara->properties_E4.player.moveDistance_126 != Q12(0.0f))
    {
        chara->properties_E4.player.moveDistance_126 -= Q12(0.4f);
        if (chara->properties_E4.player.moveDistance_126 < Q12(0.0f))
        {
            chara->properties_E4.player.moveDistance_126 = Q12(0.0f);
        }
    }

    if (chara->model_0.stateStep_3 == 0)
    {
        g_SysWork.npcs_1A0[0].properties_E4.player.moveDistance_126 = Q12(1.5f);
        Model_AnimStatusSet(&chara->model_0, 9, false);
    }

    if (chara->model_0.anim_4.keyframeIdx_8 == D_800EA856)
    {
        g_SysWork.npcs_1A0[0].properties_E4.splithead.field_EC.val16[0] = 1;
        chara->model_0.stateStep_3 = 0;
        g_SysWork.npcs_1A0[0].properties_E4.player.field_122 = 0;
    }
}

void func_800D8848(s_SubCharacter* chara) // 0x800D8848
{
    if (chara->model_0.stateStep_3 == 0)
    {
        chara->model_0.anim_4.status_0 = ANIM_STATUS(9, false);
        chara->model_0.stateStep_3++;
    }

    if (chara->model_0.anim_4.keyframeIdx_8 == D_800EA856)
    {
        g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[1].val16[1] = 1;
        chara->model_0.stateStep_3                                                  = 0;
    }
}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800D8898);

void Ai_MonsterCybil_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D8908
{
    s_Model* extraModel;

    extraModel = &g_Ai_MonsterCybil_ExtraModel;

    if (chara->model_0.state_2 == 0)
    {
        Ai_MonsterCybil_Init(chara, extraModel);
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        func_800D8B14(chara, extraModel);
        func_800D8D7C(chara, extraModel, coords);
        func_800D9790(chara, extraModel);
        func_800D99E4(chara, extraModel, anmHdr, coords);
        func_800DB4CC(chara, extraModel, coords);
        func_800D9AAC(chara, extraModel);
    }
}

void Ai_MonsterCybil_Init(s_SubCharacter* chara, s_Model* extraModel) // 0x800D89CC
{
    chara->model_0.state_2++;
    extraModel->state_2++;

    chara->model_0.stateStep_3 = 0;
    extraModel->stateStep_3    = 0;

    chara->field_E1_0 = 3;

    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[12].val16[1] = FP_ANGLE(90.0f);

    chara->model_0.anim_4.flags_2 |= AnimFlag_Visible | AnimFlag_Unlocked;

    chara->flags_3E |= CharaFlag_Unk9 | CharaFlag_Unk3;

    sharedData_800D16E4_2_s01 = 0;

    extraModel->anim_4.flags_2 |= AnimFlag_Visible | AnimFlag_Unlocked;

    chara->health_B0 = Q12(4000.0f);

    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[7].val16[0] = 10;
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[5].val16[1] = 0;
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[7].val16[1] = 0;
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[2].val32    = 0;
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[8].val32    = 0;
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[9].val32    = 0;
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[4].val32    = 0;
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[11].val8[2] = 0;
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[3].val32    = 0;

    func_8003DD80(Chara_MonsterCybil, UNK_PACKED_DATA(1, 1));
}

void func_800D8A90(s_SubCharacter* chara) // 0x800D8A90
{
    chara->field_D4.field_0 = Q12(0.3f);
    chara->field_D4.field_2 = Q12(0.23f);
    chara->field_C8.field_0 = Q12(-1.6f);
    chara->field_C8.field_6 = Q12(-1.05f);
    chara->field_C8.field_8 = Q12(-1.45f);
    chara->health_B0 = Q12(4000.0f);
    chara->field_C8.field_2 = 0;
    chara->field_C8.field_4 = 0;

    chara->field_D8.offsetZ_6 = 0;
    chara->field_D8.offsetX_4 = 0;
    chara->field_D8.offsetZ_2 = 0;
    chara->field_D8.offsetX_0 = 0;

    chara->model_0.stateStep_3 = 0;

    // TODO: Wrong union member used here.

    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[0xB].val8[1] = 0;
    D_800ED543                                                                   = 0;
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[7].val16[0]  = 10;
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[5].val16[1]  = 0;
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[7].val16[1]  = 0;
    g_SysWork.npcs_1A0[0].properties_E4.player.field_F0                          = 0;
    g_SysWork.npcs_1A0[0].properties_E4.player.runTimer_108                      = 0;
    g_SysWork.npcs_1A0[0].properties_E4.npc.field_10C                            = 0;
    g_SysWork.npcs_1A0[0].properties_E4.player.runTimer_F8                       = 0;
}

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

void func_800DB6FC(VECTOR3* pos) // 0x800DB6FC
{
    Vw_AabbVisibleInScreenCheck(pos->vx - Q12(0.5f), pos->vx + Q12(0.5f),
                                pos->vy - Q12(1.7f), pos->vy + Q12(0.1f),
                                pos->vz - Q12(0.5f), pos->vz + Q12(0.5f));
}

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DB748);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DB81C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DB930);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DBA48);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DBD64);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DBE5C);

INCLUDE_ASM("asm/maps/map6_s04/nonmatchings/map6_s04", func_800DC018);
