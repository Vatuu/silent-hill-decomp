#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/particle.h"
#include "maps/characters/larval_stalker.h"
#include "maps/characters/player.h"
#include "maps/characters/stalker.h"
#include "maps/map6/map6_s04.h"

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", D_800C9578);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB7F4_1_s01.h" // 0x800CC7E0

#include "maps/shared/sharedFunc_800CB8A0_1_s01.h" // 0x800CC88C

#include "maps/shared/sharedFunc_800CBA38_1_s01.h" // 0x800CCA24

#include "maps/shared/sharedFunc_800CBB30_1_s01.h" // 0x800CCB1C

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

// TODO: Move this line into separate `Chara_LarvalStalker` split.
#include "../src/maps/characters/larval_stalker.c" // 0x800D00B8

// TODO: Move this line into separate `Chara_Stalker` split.
#include "../src/maps/characters/stalker.c" // 0x800D3560

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
        g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[1].val16[0] = 1;
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

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04", func_800D8898);

void Ai_MonsterCybil_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D8908
{
    s_Model* extraModel;

    extraModel = &g_Ai_MonsterCybil_ExtraModel;

    if (chara->model_0.controlState_2 == ModelState_Uninitialized)
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
    chara->model_0.controlState_2++;
    extraModel->controlState_2++;

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

    WorldGfx_HeldItemAttach(Chara_MonsterCybil, UNK_PACKED_DATA(1, 1));
}

void func_800D8A90(s_SubCharacter* chara) // 0x800D8A90
{
    chara->field_D4.radius_0 = Q12(0.3f);
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

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04", func_800D8B14);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", D_800CB118);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", D_800CB178);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", D_800CB1D8);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", D_800CB208);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", D_800CB238);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", D_800CB250);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", D_800CB278);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", D_800CB2A0);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", D_800CB2B4);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", D_800CB2DC);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", D_800CB304);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", D_800CB364);

INCLUDE_RODATA("maps/map6_s04/nonmatchings/map6_s04", D_800CB3A4);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04", func_800D8D7C);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04", func_800D9790);

void func_800D99E4(s_SubCharacter* chara, s_Model* modelUpper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D99E4
{
    s_AnimInfo* animInfo;

    coords->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coords->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coords->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);

    anmHdr->activeBones_8 = HARRY_LOWER_BODY_BONE_MASK;

    animInfo = &MONSTER_CYBIL_ANIM_INFOS[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);

    anmHdr->activeBones_8 = HARRY_UPPER_BODY_BONE_MASK;

    animInfo = &MONSTER_CYBIL_ANIM_INFOS[modelUpper->anim_4.status_0];
    animInfo->updateFunc_0(modelUpper, anmHdr, coords, animInfo);
}

void func_800D9AAC(s_SubCharacter* chara, s_Model* arg1) {}

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04", func_800D9AB4);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04", func_800DA9C8);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04", func_800DB4CC);

void func_800DB6FC(VECTOR3* pos) // 0x800DB6FC
{
    Vw_AabbVisibleInScreenCheck(pos->vx - Q12(0.5f), pos->vx + Q12(0.5f),
                                pos->vy - Q12(1.7f), pos->vy + Q12(0.1f),
                                pos->vz - Q12(0.5f), pos->vz + Q12(0.5f));
}

void func_800DB748(s_SubCharacter* chara) // 0x800DB748
{
    q3_12 angleToPlayer;
    q3_12 shortestAngle;

    // TODO: Not sure if `Q12_TO_Q8` makes sense here, maybe this was just a divide by 16 for some reason.
    angleToPlayer = FP_ANGLE_ABS(ratan2(Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx),
                                        Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz)));

    Math_ShortestAngleGet(chara->rotation_24.vy, angleToPlayer, &shortestAngle);

    if (ABS(shortestAngle) < FP_ANGLE(11.3f))
    {
        chara->rotation_24.vy = angleToPlayer;
    }
    else if (shortestAngle > FP_ANGLE(0.0f))
    {
        chara->rotation_24.vy += FP_ANGLE(11.3f);
    }
    else
    {
        chara->rotation_24.vy -= FP_ANGLE(11.3f);
    }
}

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04", func_800DB81C);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04", func_800DB930);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04", func_800DBA48);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04", func_800DBD64);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04", func_800DBE5C);

INCLUDE_ASM("maps/map6_s04/nonmatchings/map6_s04", func_800DC018);
