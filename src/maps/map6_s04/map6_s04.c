#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map6/map6_s04.h"
#include "maps/particle.h"
#include "maps/characters/larval_stalker.h"
#include "maps/characters/player.h"
#include "maps/characters/stalker.h"

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

void func_800D8848(s_Model* model) // 0x800D8848
{
    if (model->stateStep_3 == 0)
    {
        model->anim_4.status_0 = ANIM_STATUS(9, false);
        model->stateStep_3++;
    }

    if (model->anim_4.keyframeIdx_8 == D_800EA856)
    {
        g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[1].val16[1] = 1;
        model->stateStep_3                                                  = 0;
    }
}

s32 func_800D8898(s_AnimInfo* animInfo) // 0x800D8898
{
    if (animInfo->status_4 == ANIM_STATUS(1, true))
    {
        if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 0)
        {
            return 0;
        }

        if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 == 1)
        {
            return D_800CB118[animInfo->startKeyframeIdx_C];
        }
        else
        {
            return D_800CB178[animInfo->startKeyframeIdx_C];
        }
    }

    return 0;
}

void Ai_MonsterCybil_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D8908
{
    s_Model* extraModel;

    extraModel = &g_Ai_MonsterCybil_ExtraModel;

    if (chara->model_0.controlState_2 == ModelState_Uninitialized)
    {
        Ai_MonsterCybil_Init(chara, extraModel);
    }

    if (g_DeltaTime != Q12(0.0f))
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
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[12].val16[1] = Q12_ANGLE(90.0f);
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

    WorldGfx_HeldItemAttach(Chara_MonsterCybil, MODEL_BONE(1, 1));
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

    chara->field_D8.offsetZ_6 = Q12(0.0f);
    chara->field_D8.offsetX_4 = Q12(0.0f);
    chara->field_D8.offsetZ_2 = Q12(0.0f);
    chara->field_D8.offsetX_0 = Q12(0.0f);

    chara->model_0.stateStep_3 = 0;

    // TODO: Wrong union member used here.

    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[11].val8[1] = 0;
    D_800ED543                                                                   = 0;
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[7].val16[0]  = 10;
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[5].val16[1]  = 0;
    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[7].val16[1]  = 0;
    g_SysWork.npcs_1A0[0].properties_E4.player.field_F0                          = 0;
    g_SysWork.npcs_1A0[0].properties_E4.player.runTimer_108                      = 0;
    g_SysWork.npcs_1A0[0].properties_E4.npc.field_10C                            = 0;
    g_SysWork.npcs_1A0[0].properties_E4.player.runTimer_F8                       = 0;
}

void func_800D8B14(s_SubCharacter* chara, s_Model* model) // 0x800D8B14
{
    u8  sp10;
    s16 sp12;

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8 != Q12(0.0f))
    {
        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8 -= g_DeltaTime * 15;
    }

    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8 = CLAMP(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8, Q12(0.0f), INT_MAX);

    Player_DisableDamage(&sp10, 0);

    if (sp10 != 0)
    {
        return;
    }

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8 < 13)
    {
        if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8 > 2)
        {
            return;
        }
    }

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE == 9 ||
        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE == 11)
    {
        chara->damage_B4.amount_C = Q12(0.0f);
    }
    else
    {
        if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE != 12)
        {
            chara->damage_B4.amount_C = chara->damage_B4.amount_C >> 1;
        }

        if (chara->damage_B4.amount_C != Q12(0.0f))
        {
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8 += chara->damage_B4.amount_C;

            chara->health_B0         -= chara->damage_B4.amount_C;
            chara->damage_B4.amount_C = Q12(0.0f);

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_122 = Q12_ANGLE_NORM_U(
                ratan2(Q12_TO_Q8(chara->position_18.vx - g_SysWork.playerWork_4C.player_0.position_18.vx),
                       Q12_TO_Q8(chara->position_18.vz - g_SysWork.playerWork_4C.player_0.position_18.vz)) +
                Q12(1.0f));

            Math_ShortestAngleGet(chara->rotation_24.vy, g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_122, &sp12);

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_122 = sp12;

            if (chara->health_B0 <= Q12(0.0f))
            {
                Player_DisableDamage(&sp10, 1);
                Savegame_EventFlagSet(EventFlag_446);
                func_8004C564(0, NO_VALUE);
            }
            else
            {
                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8 >= Q12(800.0f))
                {
                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC != 12)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 9;
                        chara->model_0.stateStep_3                                 = 0;
                    }
                }

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8 >= Q12(800.0f) ||
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE == 12)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 9;
                    model->stateStep_3                                         = 0;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8 = 0;
                }
            }

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 0;
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_10C = 0;
        }
    }
}

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

void func_800D8D7C(s_SubCharacter* chara, s_Model* model, GsCOORDINATE2* coords) // 0x800D8D7C
{
    enum _SfxId sfxId;
    s8          pitch0;
    s8          pitch1;
    q19_12      angle0;
    q19_12      moveSpeed;

    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 = Q8_TO_Q12(SquareRoot0(SQUARE(Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx)) +
                                                                                       SQUARE(Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz))));

    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_120 = func_800DB6FC(&chara->position_18);

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_120)
    {
        g_SysWork.npcs_1A0[0].properties_E4.player.runTimer_108 += g_DeltaTime;
    }
    else
    {
        g_SysWork.npcs_1A0[0].properties_E4.player.runTimer_108 = Q12(0.0f);
    }

    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106++;

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8)
    {
        case 0:
            func_800D9AB4(chara, model, coords);
            break;

        case 1:
            func_800DA9C8(chara, model, coords);
            break;

        case 4:
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A = Q12(0.25f);

            Model_AnimStatusKeyframeSet(chara->model_0, 4, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            Model_AnimStatusKeyframeSet(*model, 4, true, MONSTER_CYBIL_ANIM_INFOS, 0);

            if (chara->model_0.anim_4.keyframeIdx_8 >= 66)
            {
                WorldGfx_HeldItemAttach(Chara_MonsterCybil, 1);
            }
            else
            {
                WorldGfx_HeldItemAttach(Chara_MonsterCybil, 2);
            }

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;

            if (Savegame_EventFlagGet(EventFlag_445))
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F4 = 1;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8 = 1;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 1;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 1;
                chara->model_0.stateStep_3                                = 0;
                model->stateStep_3                                        = 0;
            }
            break;

        case 5:
            if (chara->model_0.stateStep_3 == 0)
            {
                model->stateStep_3 = 0;
                Model_AnimStatusKeyframeSet(chara->model_0, 14, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            }

            Model_AnimStatusKeyframeSet(*model, 14, true, MONSTER_CYBIL_ANIM_INFOS, 0);

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;

            if (chara->properties_E4.npc.field_F8)
            {
                chara->properties_E4.dahlia.stateIdx0 = 0;
                chara->model_0.stateStep_3            = 0;
                chara->properties_E4.npc.field_F8     = 0;
            }
            break;

        case 6:
            if (!chara->model_0.stateStep_3)
            {
                model->stateStep_3 = 0;
                Model_AnimStatusSet(&chara->model_0, 15, false);
            }

            Model_AnimStatusSet(model, 15, false);

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            if (chara->properties_E4.npc.field_F8)
            {
                chara->properties_E4.dahlia.stateIdx0 = 0;
                chara->model_0.stateStep_3            = 0;
                chara->properties_E4.npc.field_F8     = 0;
            }

            if (chara->model_0.anim_4.keyframeIdx_8 == 343)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8 = 12;
                chara->model_0.stateStep_3                                = 0;
                model->stateStep_3                                         = 0;
            }
            break;

        case 12:
            Model_AnimStatusKeyframeSet(chara->model_0, 21, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            Model_AnimStatusKeyframeSet(*model, 21, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;

            if (chara->properties_E4.npc.field_F8)
            {
                chara->properties_E4.dahlia.stateIdx0 = 0;
                chara->model_0.stateStep_3            = 0;
                chara->properties_E4.npc.field_F8     = 0;
            }
            break;

        case 9:
            if (!chara->model_0.stateStep_3)
            {
                model->stateStep_3 = 0;
                Model_AnimStatusKeyframeSet(chara->model_0, 20, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            }

            Model_AnimStatusKeyframeSet(*model, 20, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            WorldGfx_HeldItemAttach(Chara_MonsterCybil, 1);

            if (chara->properties_E4.npc.field_F8)
            {
                chara->properties_E4.dahlia.stateIdx0 = 0;
                chara->model_0.stateStep_3            = 0;
                chara->properties_E4.npc.field_F8     = 0;
            }
            break;

        case 10:
            if (!chara->model_0.stateStep_3)
            {
                model->stateStep_3 = 0;
                Model_AnimStatusKeyframeSet(chara->model_0, 18, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            }

            Model_AnimStatusKeyframeSet(*model, 18, true, MONSTER_CYBIL_ANIM_INFOS, 0);

            if (model->anim_4.keyframeIdx_8 >= 29)
            {
                WorldGfx_HeldItemAttach(Chara_MonsterCybil, 2);
            }
            else
            {
                WorldGfx_HeldItemAttach(Chara_MonsterCybil, 1);
            }

            if (chara->properties_E4.npc.field_F8)
            {
                chara->properties_E4.dahlia.stateIdx0 = 0;
                chara->model_0.stateStep_3            = 0;
                chara->properties_E4.npc.field_F8     = 0;
            }
            break;

        case 11:
            if (chara->model_0.stateStep_3 == 0)
            {
                model->stateStep_3 = 0;
                Model_AnimStatusKeyframeSet(chara->model_0, 19, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            }

            Model_AnimStatusKeyframeSet(*model, 19, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            WorldGfx_HeldItemAttach(Chara_MonsterCybil, 2);

            if (chara->properties_E4.npc.field_F8)
            {
                chara->properties_E4.dahlia.stateIdx0 = 0;
                chara->model_0.stateStep_3            = 0;
                chara->properties_E4.npc.field_F8     = 0;
            }

            if (!chara->model_0.stateStep_3)
            {
                model->stateStep_3 = 0;
            }
            break;

        case 7:
            if (!chara->model_0.stateStep_3)
            {
                model->stateStep_3 = 0;
                Model_AnimStatusKeyframeSet(chara->model_0, 16, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            }

            Model_AnimStatusKeyframeSet(*model, 16, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            break;

        case 8:
            if (!chara->model_0.stateStep_3)
            {
                model->stateStep_3 = 0;
                Model_AnimStatusKeyframeSet(chara->model_0, 17, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            }

            Model_AnimStatusKeyframeSet(*model, 17, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            break;
    }

    func_8007FDE0(0xB, &sfxId, &pitch0, &pitch1);

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8)
    {
        case 9:
            sharedFunc_800D908C_0_s00(41, chara, 5, 16, sfxId, pitch0);
            break;

        case 10:
            sharedFunc_800D9188_0_s00(37, chara, 29, Sfx_Unk1620);
            break;

        case 11:
            if (chara->model_0.anim_4.keyframeIdx_8 == 38)
            {
                func_8006342C(63, Q12_ANGLE(90.0f), chara->rotation_24.vy, g_SysWork.npcCoords_FC0);
            }

            sharedFunc_800D9188_0_s00(39, chara, 38, Sfx_Unk1622);
            break;

        case 4:
            sharedFunc_800D9188_0_s00(9, chara, 69, Sfx_Unk1621);
            break;

        case 5:
            if (chara->model_0.anim_4.keyframeIdx_8 < 312)
            {
                sharedFunc_800D9188_0_s00(29, chara, 289, Sfx_Unk1632);
            }
            else
            {
                sharedFunc_800D9188_0_s00(29, chara, 313, Sfx_Unk1631);
            }
            break;
    }

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 1)
    {
        sharedFunc_800D908C_0_s00(3, chara, 5, 16, sfxId, pitch0);
    }

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE)
    {
        case 2:
            if (ANIM_STATUS_IS_ACTIVE(model->anim_4.status_0) && model->anim_4.keyframeIdx_8 >= 29 && !sharedData_800D16E4_2_s01)
            {
                func_8005DC1C(Sfx_Unk1620, &chara->position_18, Q8(0.25f), 0);
                sharedData_800D16E4_2_s01 = 1;
            }
            else if (model->anim_4.keyframeIdx_8 < 29)
            {
                sharedData_800D16E4_2_s01 = 0;
            }
            break;

        case 3:
            if (ANIM_STATUS_IS_ACTIVE(model->anim_4.status_0) && model->anim_4.keyframeIdx_8 >= 38 && !sharedData_800D16E4_2_s01)
            {
                func_8005DC1C(Sfx_Unk1622, &chara->position_18, Q8(0.25f), 0);
                sharedData_800D16E4_2_s01 = 1;
            }

            else if (model->anim_4.keyframeIdx_8 < 38)
            {
                sharedData_800D16E4_2_s01 = 0;
            }
            break;

        case 4:
            break;
    }

    moveSpeed              = g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126;
    angle0                 = g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_122;
    chara->headingAngle_3C = Q12_ANGLE_ABS(angle0 + chara->rotation_24.vy);

    chara->moveSpeed_38 = moveSpeed;
    chara->fallSpeed_34 += g_GravitySpeed;

    coords->flg = false;
    Math_RotMatrixZxyNegGte(&chara->rotation_24, &coords->coord);
}

void func_800D9790(s_SubCharacter* chara, s_Model* model) // 0x800D9790
{
    s_800C4590 sp10;
    VECTOR3    sp30;
    VECTOR3    sp40;
    s32        temp_s4;
    s32        temp_s0;
    s32        temp_s2;
    s32        temp_s3;

    sp30 = chara->position_18;

    temp_s4 = chara->headingAngle_3C;
    temp_s0 = Q12_MULT_PRECISE(chara->moveSpeed_38, g_DeltaTime);

    temp_s2 = (temp_s0 < -0x7FFF || temp_s0 > 0x7FFF) * 4;
    temp_s3 = temp_s2 >> 1;

    sp40.vx = Q12_MULT_PRECISE(temp_s0 >> temp_s3, Math_Sin(temp_s4) >> temp_s3) << temp_s2;
    sp40.vz = Q12_MULT_PRECISE(temp_s0 >> temp_s3, Math_Cos(temp_s4) >> temp_s3) << temp_s2;
    sp40.vy = Q12_MULT_PRECISE(chara->fallSpeed_34, g_DeltaTime);

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC)
    {
        case 11:
            if (chara->model_0.anim_4.status_0 & 1)
            {
                chara->field_D4.radius_0 = Q12(0.3f) - (((chara->model_0.anim_4.keyframeIdx_8 - 216) * Q12(3.0f)) / 100);
            }

            func_80069B24(&sp10, &sp40, chara);

            chara->position_18.vx += sp10.offset_0.vx;
            chara->position_18.vz += sp10.offset_0.vz;
            chara->fallSpeed_34    = Q12(0.0f);
            break;

        case 12:
            chara->field_D4.radius_0 = Q12(0.0f);
            chara->position_18.vx   += sp40.vx;
            chara->position_18.vz   += sp40.vz;
            chara->fallSpeed_34      = Q12(0.0f);
            break;

        default:
            chara->field_D4.radius_0  = Q12(0.3f);
            chara->field_D8.offsetZ_6 = Q12(0.0f);
            chara->field_D8.offsetX_4 = Q12(0.0f);
            chara->field_D8.offsetZ_2 = Q12(0.0f);
            chara->field_D8.offsetX_0 = Q12(0.0f);

            func_80069B24(&sp10, &sp40, chara);

            chara->position_18.vx += sp10.offset_0.vx;
            chara->position_18.vy  = Q12(0.0f);
            chara->fallSpeed_34    = Q12(0.0f);
            chara->position_18.vz += sp10.offset_0.vz;
            break;
    }
}

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

void func_800D9AAC(s_SubCharacter* chara, s_Model* model) {} // 0x800D9AAC

void func_800D9AB4(s_SubCharacter* chara, s_Model* model, GsCOORDINATE2* coords) // 0x800D9AB4
{
    s16 temp_v0;

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC)
    {
        case 0:
            break;

        case 1:
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(1, false);
                chara->model_0.stateStep_3++;
            }

            func_800DC018(chara);

            if (g_SysWork.playerWork_4C.player_0.health_B0 > 0 && g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 == 0)
            {
                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 > Q12(0.6f))
                {
                    func_800DB748(chara);
                }

                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;

                if (chara->model_0.anim_4.status_0 == 3)
                {
                    if ((u16)chara->model_0.anim_4.keyframeIdx_8 < 24)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = D_800CB208[chara->model_0.anim_4.keyframeIdx_8];
                    }
                }

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_120 == 0)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 <<= 1;

                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 > 60)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 = 0;

                        if ((Rng_Rand16() % 10) > 4 && g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 > Q12(4.0f))
                        {
                            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE = func_800DB930();

                            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE != NO_VALUE)
                            {
                                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 12;
                                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 12;
                                chara->model_0.stateStep_3                                 = 0;
                                model->stateStep_3                                         = 0;
                            }
                        }
                        else
                        {
                            func_800DBA48(chara);
                        }
                    }
                }

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_104 <= 0 || chara->health_B0 < Q12(2000.0f))
                {
                    Savegame_EventFlagSet(EventFlag_444);

                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8 = 3;
                    chara->model_0.stateStep_3                                 = 0;
                    model->stateStep_3                                         = 0;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F4 = 0;
                    return;
                }
            }
            else if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 == 1)
            {
                func_800DBE5C(chara);

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_104 <= 0 || chara->health_B0 < Q12(2000.0f))
                {
                    Savegame_EventFlagSet(EventFlag_444);

                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8 = 3;
                    chara->model_0.stateStep_3                                 = 0;
                    model->stateStep_3                                         = 0;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F4 = 0;
                    return;
                }
            }
            else
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
                if (chara->model_0.anim_4.status_0 == 3)
                {
                    if ((u16)chara->model_0.anim_4.keyframeIdx_8 < 24)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = D_800CB208[chara->model_0.anim_4.keyframeIdx_8];
                    }
                }
            }

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_122 = 0;
            break;

        case 2:
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = 4;
                chara->model_0.stateStep_3++;
            }

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            break;

        case 3:
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = 6;
                chara->model_0.stateStep_3++;
            }

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            break;

        case 8:
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = 16;
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.keyframeIdx_8 == D_800EA836)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 1;
                chara->model_0.stateStep_3                                 = 0;
            }
            break;

        case 9:
            func_800D87B0(chara);
            break;

        case 10:
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = 20;
                chara->model_0.stateStep_3++;
            }

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            break;

        case 11:
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = 23;
                chara->model_0.stateStep_3++;
                chara->model_0.anim_4.time_4        = FP_TO(MONSTER_CYBIL_ANIM_INFOS[23].endKeyframeIdx_E, Q12_SHIFT);
                chara->model_0.anim_4.keyframeIdx_8 = MONSTER_CYBIL_ANIM_INFOS[23].endKeyframeIdx_E;
            }

            if (chara->properties_E4.monsterCybil.field_126 != 0)
            {
                chara->properties_E4.monsterCybil.field_126 = chara->properties_E4.monsterCybil.field_126 - 327;
                if (chara->properties_E4.monsterCybil.field_126 < 0)
                {
                    chara->properties_E4.monsterCybil.field_126 = 0;
                }
            }

            if (chara->model_0.anim_4.keyframeIdx_8 == (D_800EA896 - 4) || chara->model_0.anim_4.keyframeIdx_8 == (D_800EA896 - 5))
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = Q12(0.6f);
            }

            if (chara->model_0.anim_4.keyframeIdx_8 <= (D_800EA896 - 7))
            {
                chara->position_18.vy += g_GravitySpeed >> 2;
            }
            else if ((D_800EA896 - 4) >= chara->model_0.anim_4.keyframeIdx_8)
            {
                chara->position_18.vy += g_GravitySpeed >> 4;
            }
            else
            {
                chara->position_18.vy = g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_100 - 1843;
            }

            if (chara->position_18.vy > Q12(0.0f))
            {
                chara->position_18.vy = Q12(0.0f);
            }

            chara->rotation_24.vy = (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE < 6) ? (D_800CB2A0[g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE] - Q12_ANGLE(180.0f)) :
                                                                                                      D_800CB2A0[g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE];

            temp_v0 = 1;

            if (chara->model_0.anim_4.keyframeIdx_8 == D_800EA894)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = temp_v0;
                chara->model_0.stateStep_3                                 = 0;
            }
            break;

        case 12:
            chara->position_18.vx = D_800CB2B4[g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE] + Q12(20.0f);
            chara->position_18.vy = g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_100 - Q12(0.45f);
            chara->position_18.vz = D_800CB2DC[g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE] + Q12(100.0f);

            chara->rotation_24.vy = (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE < 6) ? (D_800CB2A0[g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE] - Q12_ANGLE(180.0f)) :
                                                                                                      D_800CB2A0[g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE];

            if (chara->model_0.anim_4.keyframeIdx_8 >= MONSTER_CYBIL_ANIM_INFOS[25].startKeyframeIdx_C &&
                MONSTER_CYBIL_ANIM_INFOS[25].endKeyframeIdx_E >= chara->model_0.anim_4.keyframeIdx_8)
            {
                chara->field_D8.offsetX_0 = Q12_MULT(Math_Sin(chara->rotation_24.vy), Q12(-0.46f));
                chara->field_D8.offsetZ_2 = Q12_MULT(Math_Cos(chara->rotation_24.vy), Q12(-0.46f));
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(12, false);
                chara->model_0.stateStep_3++;
            }

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            break;
    }

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE)
    {
        case 0:
            break;

        case 1:
            if (model->stateStep_3 == 0)
            {
                model->anim_4.status_0 = ANIM_STATUS(1, false);
                model->stateStep_3++;
            }

            if (model->anim_4.status_0 == ANIM_STATUS(1, true))
            {
                model->anim_4.time_4        = chara->model_0.anim_4.time_4;
                model->anim_4.keyframeIdx_8 = chara->model_0.anim_4.keyframeIdx_8;
            }

            if (g_SysWork.playerWork_4C.player_0.health_B0 > 0 && g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 == 0)
            {
                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 < Q12(0.8f) &&
                    (g_SysWork.playerWork_4C.extra_128.state_1C > 50 || g_SysWork.playerWork_4C.extra_128.state_1C < 47))
                {
                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE == 1)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 8;
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 8;
                        chara->model_0.stateStep_3                                 = 0;
                        model->stateStep_3                                         = 0;
                    }
                }
                else if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_108 >= Q12(3.0f) &&
                         (!func_800DB81C(chara) || g_SysWork.playerWork_4C.extra_128.state_1C == 47 ||
                          g_SysWork.playerWork_4C.extra_128.state_1C == 48))
                {
                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 <= Q12(4.0f))
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 2;
                        chara->model_0.stateStep_3                                 = 0;
                    }

                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 2;
                    model->stateStep_3                                         = 0;
                }
            }
            break;

        case 2:
            if (model->stateStep_3 == 0)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0 = 0;
                D_800EBB48                                                = Rng_Rand16() % Q12(1.0f);

                if (model->stateStep_3 == 0)
                {
                    model->anim_4.status_0 = ANIM_STATUS(2, false);
                    model->stateStep_3++;
                }
            }

            func_800DB748(chara);

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0 += g_DeltaTime;

            D_800ED570.vx = Q8_TO_Q12(coords[10].workm.t[0]);
            D_800ED570.vy = Q8_TO_Q12(coords[10].workm.t[1]);
            D_800ED570.vz = Q8_TO_Q12(coords[10].workm.t[2]);

            if (model->anim_4.keyframeIdx_8 >= 29)
            {
                WorldGfx_HeldItemAttach(Chara_MonsterCybil, 2);
            }

            if (model->anim_4.keyframeIdx_8 == D_800EA776 && D_800EBB48 < g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0)
            {
                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_120 != 0 &&
                    !(g_SysWork.playerWork_4C.player_0.flags_3E & (1 << 3)))
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_114 = 0;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE  = 3;
                    model->stateStep_3                                          = 0;

                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 2)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 3;
                        chara->model_0.stateStep_3                                 = 0;
                    }
                }
                else
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 10;
                    model->stateStep_3                                         = 0;

                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC != 1)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 10;
                        chara->model_0.stateStep_3                                 = 0;
                    }
                }
            }
            break;

        case 3:
            if (model->stateStep_3 == 0)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0  = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_108 = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_104--;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_114++;

                D_800EBB4A = Rng_Rand16() % Q12(1.0f);
            }

            D_800ED570.vx = Q8_TO_Q12(coords[10].workm.t[0]);
            D_800ED570.vy = Q8_TO_Q12(coords[10].workm.t[1]);
            D_800ED570.vz = Q8_TO_Q12(coords[10].workm.t[2]);

            if (model->anim_4.keyframeIdx_8 >= (MONSTER_CYBIL_ANIM_INFOS[7].startKeyframeIdx_C + 2) &&
                (MONSTER_CYBIL_ANIM_INFOS[7].startKeyframeIdx_C + 4) >= model->anim_4.keyframeIdx_8 &&
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_115 == 0)
            {
                chara->model_0.anim_4.animInfo_C = MONSTER_CYBIL_ANIM_INFOS;
                chara->field_44.field_0          = 1;

                // TODO: Whats' weapon attack 63?
                func_8006342C(63, g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A, chara->rotation_24.vy, g_SysWork.npcCoords_FC0);

                if (func_8008A0E4(chara->field_44.field_0,
                                  63,
                                  chara,
                                  &D_800ED570,
                                  &g_SysWork.playerWork_4C.player_0,
                                  chara->rotation_24.vy,
                                  g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A) != NO_VALUE)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_115 = 1;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 1;
                }
            }
            else
            {
                chara->field_44.field_0 = 0;
            }

            if (model->anim_4.keyframeIdx_8 >= (MONSTER_CYBIL_ANIM_INFOS[7].startKeyframeIdx_C + 4))
            {
                func_800DB748(chara);
            }

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0 += g_DeltaTime;

            if (model->stateStep_3 == 0)
            {
                model->anim_4.status_0 = ANIM_STATUS(3, false);
                model->stateStep_3++;
            }

            if (ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0) && model->anim_4.keyframeIdx_8 == MONSTER_CYBIL_ANIM_INFOS[7].endKeyframeIdx_E)
            {
                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_120 == 0 || g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_104 == 0 ||
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_114 == 3 || g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_115 != 0 ||
                    func_800DB81C(chara) == true)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_115 = 0;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE  = 10;
                    model->stateStep_3                                          = 0;

                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC != 1)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 10;
                        chara->model_0.stateStep_3                                 = 0;
                    }
                }
                else if ((D_800EBB4A + Q12(1.5f)) < g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0)
                {
                    model->stateStep_3                                         = 0;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0 = 0;

                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 3)
                    {
                        chara->model_0.stateStep_3 = 0;
                    }
                }
            }
            break;

        case 8:
            func_800DB748(chara);

            D_800ED570.vx = Q8_TO_Q12(coords[10].workm.t[0]);
            D_800ED570.vy = Q8_TO_Q12(coords[10].workm.t[1]);
            D_800ED570.vz = Q8_TO_Q12(coords[10].workm.t[2]);

            if (model->stateStep_3 == 0)
            {
                model->anim_4.status_0 = ANIM_STATUS(8, false);
                model->stateStep_3++;
            }

            if (model->anim_4.keyframeIdx_8 > 169 && model->anim_4.keyframeIdx_8 < 173)
            {
                chara->model_0.anim_4.animInfo_C = MONSTER_CYBIL_ANIM_INFOS;
                chara->field_44.field_0          = 1;
            }
            else
            {
                chara->field_44.field_0 = 0;
            }

            if (func_8008A0E4(chara->field_44.field_0, WEAPON_ATTACK(EquippedWeaponId_HandgunBullets, AttackInputType_Tap), chara, &D_800ED570, &g_SysWork.playerWork_4C.player_0, chara->rotation_24.vy, 0x400) != -1)
            {
                g_SysWork.playerWork_4C.player_0.damage_B4.position_0.vz = Q12(1.0f);

                if (sharedData_800D16E4_2_s01 == 0)
                {
                    func_8005DC1C(Sfx_Unk1630, &chara->position_18, Q8(0.25f), 0);
                }

                sharedData_800D16E4_2_s01                                  = 1;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 1;
            }

            if (model->anim_4.keyframeIdx_8 & 1 && model->anim_4.keyframeIdx_8 == D_800EA836)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 1;
                model->stateStep_3                                         = 0;
                sharedData_800D16E4_2_s01                                 = 0;
            }
            break;

        case 9:
            func_800D8848(model);

            if (model->anim_4.keyframeIdx_8 == D_800EA856 && g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 12)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 11;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 11;
                chara->model_0.stateStep_3                                 = 0;
                model->stateStep_3                                         = 0;
                chara->field_D8.offsetZ_2                                  = Q12(0.0f);
                chara->field_D8.offsetX_0                                  = Q12(0.0f);
            }
            break;

        case 10:
            if (model->stateStep_3 == 0)
            {
                model->anim_4.status_0 = 0x14;
                model->stateStep_3++;
            }

            if (ANIM_STATUS_IS_ACTIVE(model->anim_4.status_0) && model->anim_4.keyframeIdx_8 < 209)
            {
                WorldGfx_HeldItemAttach(Chara_MonsterCybil, 1);
            }

            if (model->anim_4.keyframeIdx_8 == MONSTER_CYBIL_ANIM_INFOS[model->anim_4.status_0].startKeyframeIdx_C)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 1;
                model->stateStep_3                                         = 0;

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 10)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 1;
                    chara->model_0.stateStep_3                                 = 0;
                }
            }
            break;

        case 11:
            if (model->stateStep_3 == 0)
            {
                model->anim_4.status_0 = ANIM_STATUS(11, true);
                model->stateStep_3++;
                model->anim_4.time_4        = FP_TO(MONSTER_CYBIL_ANIM_INFOS[23].endKeyframeIdx_E, Q12_SHIFT);
                model->anim_4.keyframeIdx_8 = MONSTER_CYBIL_ANIM_INFOS[23].endKeyframeIdx_E;
            }

            if (model->anim_4.keyframeIdx_8 == D_800EA894)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 1;
                model->stateStep_3                                         = 0;
            }
            break;

        case 12:
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0 += g_DeltaTime;

            if (chara->model_0.stateStep_3 == 0)
            {
                func_8005DC1C(Sfx_Unk1618, &chara->position_18, Q8(0.25f), 0);
            }

            if (model->stateStep_3 == 0)
            {
                model->anim_4.status_0 = 0x18;
                model->stateStep_3++;
            }

            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0 >= Q12(10.0f) ||
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_108 >= Q12(6.0f))
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 11;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 11;
                chara->model_0.stateStep_3                                 = 0;
                model->stateStep_3                                         = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0 = 0;
            }
            break;
    }
}

void func_800DA9C8(s_SubCharacter* chara, s_Model* model, GsCOORDINATE2* coords) // 0x800DA9C8
{
    q19_12 angle;
    s32    temp_v0_2;
    s32    var_a1;
    s32    var_s3;

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC)
    {
        case 0:
            break;

        case 1:
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = 3;
                chara->model_0.stateStep_3++;
                chara->model_0.anim_4.time_4        = MONSTER_CYBIL_ANIM_INFOS[3].startKeyframeIdx_C + Q12(3.0f);
                chara->model_0.anim_4.keyframeIdx_8 = MONSTER_CYBIL_ANIM_INFOS[3].startKeyframeIdx_C + 3;
            }

            func_800DC018(chara);

            if (g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f) &&
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 == 0)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 > Q12(0.6f))
                {
                    func_800DB748(chara);
                }

                if (chara->model_0.anim_4.status_0 == 3)
                {
                    if ((u16)chara->model_0.anim_4.keyframeIdx_8 < 24)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = D_800CB208[chara->model_0.anim_4.keyframeIdx_8];
                    }
                }

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_120 == 0)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 <<= 1;

                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 > 60)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 = 0;
                        func_800DBA48(chara);
                    }
                }

                if (func_800DBD64(chara) != 0)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_10C += g_DeltaTime;
                }
                else
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_10C = 0;
                }

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_10C > Q12(3.0f))
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 1;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_10C = 0;
                }
            }
            else if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 == 1)
            {
                func_800DBE5C(chara);
            }
            else
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;

                if (chara->model_0.anim_4.status_0 == ANIM_STATUS(1, true))
                {
                    if ((u16)chara->model_0.anim_4.keyframeIdx_8 < 24)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = D_800CB208[chara->model_0.anim_4.keyframeIdx_8];
                    }
                }
            }

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_122 = 0;
            break;

        case 5:
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(5, false);
                chara->model_0.stateStep_3++;
            }

            func_800DB748(chara);

            if (chara->model_0.anim_4.keyframeIdx_8 >= (D_800EA7D4 + 10))
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = Q12(0.7f);
            }
            break;

        case 6:
            var_s3 = 0;
            var_a1 = 0;

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(6, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.status_0 & 1)
            {
                chara->model_0.anim_4.time_4        = g_SysWork.playerWork_4C.player_0.model_0.anim_4.time_4 - Q12(832.0f);
                chara->model_0.anim_4.keyframeIdx_8 = g_SysWork.playerWork_4C.player_0.model_0.anim_4.keyframeIdx_8 - 832;
            }

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            angle                                                    = Q12_FRACT((u16)chara->rotation_24.vy + Q12(1.5f));

            switch (g_SysWork.playerWork_4C.extra_128.state_1C)
            {
                case 32:
                    var_s3 = g_SysWork.playerWork_4C.player_0.position_18.vx + Q12_MULT(Math_Sin(angle), Q12(0.62f));
                    var_a1 = g_SysWork.playerWork_4C.player_0.position_18.vz + Q12_MULT(Math_Cos(angle), Q12(0.62f));
                    break;

                case 33:
                    var_s3 = g_SysWork.playerWork_4C.player_0.position_18.vx + Q12_MULT(Math_Sin(angle), Q12(0.8f));
                    var_a1 = g_SysWork.playerWork_4C.player_0.position_18.vz + Q12_MULT(Math_Cos(angle), Q12(0.8f));
                    break;
            }

            if (g_SysWork.playerWork_4C.extra_128.state_1C > 31 &&
                g_SysWork.playerWork_4C.extra_128.state_1C < 34)
            {
                if (var_s3 < chara->position_18.vx)
                {
                    chara->position_18.vx -= Q12(1.0f / 128.0f);
                }
                else if (chara->position_18.vx < var_s3)
                {
                    chara->position_18.vx += Q12(1.0f / 128.0f);
                }

                if (var_a1 < chara->position_18.vz)
                {
                    chara->position_18.vz = chara->position_18.vz - Q12(1.0f / 128.0f);
                }
                else if (chara->position_18.vz < var_a1)
                {
                    chara->position_18.vz = chara->position_18.vz + Q12(1.0f / 128.0f);
                }
            }
            break;

        case 7:
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(7, false);
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.keyframeIdx_8 == D_800EA816)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 1;
                chara->model_0.stateStep_3                                 = 0;
                chara->position_18.vx                                     += Q12_MULT(Math_Sin(chara->rotation_24.vy + Q12_ANGLE(33.75f)), Q12(0.1f));
                chara->position_18.vz                                     += Q12_MULT(Math_Cos(chara->rotation_24.vy + Q12_ANGLE(33.75f)), Q12(0.1f));
            }
            break;

        case 8:
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(8, false);
                chara->model_0.stateStep_3++;
            }
            break;

        case 9:
            func_800D87B0(chara);
            break;

        case 12:
            break;
    }

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE)
    {
        case 0:
            break;

        case 1:
            if (model->stateStep_3 == 0)
            {
                model->anim_4.status_0 = ANIM_STATUS(1, true);
                model->stateStep_3++;
                model->anim_4.time_4        = MONSTER_CYBIL_ANIM_INFOS[3].startKeyframeIdx_C + Q12(3.0f);
                model->anim_4.keyframeIdx_8 = MONSTER_CYBIL_ANIM_INFOS[3].startKeyframeIdx_C + 3;
            }

            if (model->anim_4.status_0 == ANIM_STATUS(1, true))
            {
                model->anim_4.time_4        = chara->model_0.anim_4.time_4;
                model->anim_4.keyframeIdx_8 = chara->model_0.anim_4.keyframeIdx_8;
            }

            if (g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f) &&
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 == 0 &&
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 < Q12(0.8f) &&
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 > 30)
            {
                if ((Rng_Rand16() % 8) >= 5)
                {
                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE == 1)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 8;
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 8;
                        chara->model_0.stateStep_3                                 = 0;
                        model->stateStep_3                                         = 0;
                    }
                }
                else
                {
                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE == 1)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 5;
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 5;
                        chara->model_0.stateStep_3                                 = 0;
                        model->stateStep_3                                         = 0;
                    }
                }
            }
            break;

        case 5:
            D_800ED570.vx = Q8_TO_Q12(coords[10].workm.t[0]);
            D_800ED570.vy = Q8_TO_Q12(coords[10].workm.t[1]);
            D_800ED570.vz = Q8_TO_Q12(coords[10].workm.t[2]);

            if (model->stateStep_3 == 0)
            {
                model->anim_4.status_0 = ANIM_STATUS(5, false);
                model->stateStep_3++;
            }

            if (model->anim_4.keyframeIdx_8 == MONSTER_CYBIL_ANIM_INFOS[11].endKeyframeIdx_E)
            {
                chara->model_0.anim_4.animInfo_C = MONSTER_CYBIL_ANIM_INFOS;
                chara->field_44.field_0          = 1;
            }
            else
            {
                chara->field_44.field_0 = 0;
            }

            temp_v0_2 = func_8008A0E4(chara->field_44.field_0,
                                      WEAPON_ATTACK(EquippedWeaponId_ShotgunShells, AttackInputType_Tap),
                                      chara,
                                      &D_800ED570,
                                      &g_SysWork.playerWork_4C.player_0,
                                      chara->rotation_24.vy,
                                      Q12_ANGLE(90.0f));

            if (temp_v0_2 != NO_VALUE)
            {
                g_SysWork.playerWork_4C.player_0.field_40 = chara->field_40;
            }

            if (model->anim_4.keyframeIdx_8 == D_800EA7D6)
            {
                if (temp_v0_2 !=NO_VALUE)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 6;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 6;
                }
                else
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 7;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 7;
                }

                model->stateStep_3                                          = 0;
                chara->model_0.stateStep_3                                  = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0  = 0;
            }
            break;

        case 6:
            if (model->stateStep_3 == 0)
            {
                model->anim_4.status_0 = ANIM_STATUS(6, false);
                model->stateStep_3++;
            }

            if (ANIM_STATUS_IS_ACTIVE(model->anim_4.status_0))
            {
                model->anim_4.time_4        = g_SysWork.playerWork_4C.player_0.model_0.anim_4.time_4 - Q12(832.0f);
                model->anim_4.keyframeIdx_8 = g_SysWork.playerWork_4C.player_0.model_0.anim_4.keyframeIdx_8 - 832;
            }

            g_SysWork.playerWork_4C.player_0.damage_B4.amount_C = g_DeltaTime * 4;

            if (g_SysWork.playerWork_4C.player_0.field_40 == NO_VALUE ||
                g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f) ||
                g_SysWork.playerWork_4C.player_0.attackReceived_41 == NO_VALUE)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 7;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 7;
                model->stateStep_3                                         = 0;
                chara->model_0.stateStep_3                                 = 0;
                g_SysWork.playerWork_4C.player_0.damage_B4.amount_C       = Q12(0.0f);
            }

            if (ANIM_STATUS_IS_ACTIVE(model->anim_4.status_0))
            {
                if (model->anim_4.keyframeIdx_8 == 101)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_118 = 0;
                }
                else
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_118 = D_800CB238[model->anim_4.keyframeIdx_8 - 91] +
                                                                                 (((D_800CB238[model->anim_4.keyframeIdx_8 - 90] - D_800CB238[model->anim_4.keyframeIdx_8 - 91]) * Q12_FRACT((u16)model->anim_4.time_4)) / Q12(1.0f));
                }
            }
            break;

        case 7:
            if (model->stateStep_3 == 0)
            {
                model->anim_4.status_0 = ANIM_STATUS(7, false);
                model->stateStep_3++;
            }

            if (model->anim_4.keyframeIdx_8 == D_800EA816)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE  = 1;
                model->stateStep_3                                          = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 1;
            }
            break;

        case 8:
            func_800DB748(chara);

            D_800ED570.vx = Q8_TO_Q12(coords[10].workm.t[0]);
            D_800ED570.vy = Q8_TO_Q12(coords[10].workm.t[1]);
            D_800ED570.vz = Q8_TO_Q12(coords[10].workm.t[2]);

            if (model->stateStep_3 == 0)
            {
                model->anim_4.status_0 = ANIM_STATUS(8, false);
                model->stateStep_3++;
            }

            if (model->anim_4.keyframeIdx_8 > 169 &&
                model->anim_4.keyframeIdx_8 < 173)
            {
                chara->model_0.anim_4.animInfo_C = MONSTER_CYBIL_ANIM_INFOS;
                chara->field_44.field_0          = 1;
            }
            else
            {
                chara->field_44.field_0 = 0;
            }

            if (func_8008A0E4(chara->field_44.field_0,
                              WEAPON_ATTACK(EquippedWeaponId_RifleShells, AttackInputType_Tap),
                              chara,
                              &D_800ED570,
                              &g_SysWork.playerWork_4C.player_0,
                              chara->rotation_24.vy,
                              Q12_ANGLE(90.0f)) != NO_VALUE)
            {
                g_SysWork.playerWork_4C.player_0.damage_B4.position_0.vz = Q12(1.0f);

                if (sharedData_800D16E4_2_s01 == 0)
                {
                    func_8005DC1C(Sfx_Unk1630, &chara->position_18, Q8(0.25f), 0);
                }

                sharedData_800D16E4_2_s01                                  = 1;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 1;
            }

            if (ANIM_STATUS_IS_ACTIVE(model->anim_4.keyframeIdx_8) && model->anim_4.keyframeIdx_8 == D_800EA836)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 1;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 1;
                model->stateStep_3                                         = 0;
                chara->model_0.stateStep_3                                 = 0;
                sharedData_800D16E4_2_s01                                 = 0;
            }
            break;

        case 9:
            func_800D8848(model);
            break;

        case 12:
            if (model->stateStep_3 == 0)
            {
                model->anim_4.status_0 = ANIM_STATUS(12, false);
                model->stateStep_3++;
            }
            break;
    }
}

void func_800DB4CC(s_SubCharacter* chara, s_Model* model, GsCOORDINATE2* coord) // 0x800DB4CC
{
    q3_12  angle;
    q19_12 range;
    q19_12 delta;

    delta = (g_DeltaTime << 5) / 136;

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE)
    {
        case 9:
        case 11:
            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 12)
            {
                D_800ED560.vy = -224;
                D_800ED560.vz = -136;
                TransMatrix(&coord[1].coord, &D_800ED560);
            }

            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 11 &&
                model->anim_4.status_0 == ANIM_STATUS(9, true))
            {
                D_800ED560.vy = -224;
                D_800ED560.vz = -136;
                TransMatrix(&coord[1].coord, &D_800ED560);
            }
            break;

        case 10:
            range = delta >> 1;
            if (range >= (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A - Q12_ANGLE(90.0f)))
            {
                if ((g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A - Q12_ANGLE(90.0f)) >= -range)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A = Q12_ANGLE(90.0f);
                }
                else
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A += range;
                }
            }
            else
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A -= delta;
            }

            Math_RotMatrixZ(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A - Q12_ANGLE(90.0f), &coord[8].coord);
            break;

        case 2:
        case 3:
            // TODO: Use macro.
            angle = ratan2(SquareRoot0(SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vx - D_800ED570.vx) >> 4) +
                                     SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vz - D_800ED570.vz) >> 4)),
                         (g_SysWork.playerWork_4C.player_0.position_18.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_6 -
                          D_800ED570.vy) >>
                             4);

            if ((angle + delta) < g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A -= delta;
            }
            else
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A = angle;
            }

            Math_RotMatrixZ(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A - Q12_ANGLE(90.0f), &coord[8].coord);
            break;

        case 6:
            func_80044F14(&coord[1], 0, 0, -g_SysWork.npcs_1A0[0].properties_E4.player.field_118);
            break;
    }
}

s32 func_800DB6FC(VECTOR3* pos) // 0x800DB6FC
{
    return Vw_AabbVisibleInScreenCheck(pos->vx - Q12(0.5f), pos->vx + Q12(0.5f),
                                       pos->vy - Q12(1.7f), pos->vy + Q12(0.1f),
                                       pos->vz - Q12(0.5f), pos->vz + Q12(0.5f));
}

void func_800DB748(s_SubCharacter* chara) // 0x800DB748
{
    q3_12 angleToPlayer;
    q3_12 shortestAngle;

    // TODO: Not sure if `Q12_TO_Q8` makes sense here, maybe this was just a divide by 16 for some reason.
    angleToPlayer = Q12_ANGLE_ABS(ratan2(Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx),
                                        Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz)));

    Math_ShortestAngleGet(chara->rotation_24.vy, angleToPlayer, &shortestAngle);

    if (ABS(shortestAngle) < Q12_ANGLE(11.3f))
    {
        chara->rotation_24.vy = angleToPlayer;
    }
    else if (shortestAngle > Q12_ANGLE(0.0f))
    {
        chara->rotation_24.vy += Q12_ANGLE(11.3f);
    }
    else
    {
        chara->rotation_24.vy -= Q12_ANGLE(11.3f);
    }
}

bool func_800DB81C(s_SubCharacter* chara) // 0x800DB81C
{
    s_RayData ray;
    VECTOR3   dir;

    dir.vy = Q12_MULT(D_800AD4C8[63].field_0, Math_Cos(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A));
    dir.vx = Q12_MULT(Q12_MULT(D_800AD4C8[63].field_0, Math_Sin(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A)), Math_Sin(chara->rotation_24.vy));
    dir.vz = Q12_MULT(Q12_MULT(D_800AD4C8[63].field_0, Math_Sin(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A)), Math_Cos(chara->rotation_24.vy));

    if (func_8006DA08(&ray, &D_800ED570, &dir, chara) && ray.chara_10 == NULL)
    {
        return true;
    }

    return false;
}

s32 func_800DB930(void) // 0x800DB930
{
    VECTOR3 sp10;
    q19_12  dist;
    q19_12  shortestDist;
    s32     foundIdx;
    s32     i;

    shortestDist   = Q12(20.0f);
    foundIdx = NO_VALUE;

    for (i = 0; i < 10; i++)
    {
        sp10.vx = D_800CB2B4[i] + Q12(20.0f);
        sp10.vy = Q12(-0.5f);
        sp10.vz = D_800CB2DC[i] + Q12(100.0f);

        if (func_800DB6FC(&sp10))
        {
            continue;
        }

        // TODO: Use macro.
        dist = SquareRoot0(SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vx - sp10.vx) >> 4) +
                          SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vz - sp10.vz) >> 4)) << 4;

        if (dist < shortestDist)
        {
            shortestDist = dist;
            foundIdx = i;
        }
    }

    return foundIdx;
}

s32 func_800DBA48(s_SubCharacter* chara) // 0x800DBA48
{
    // TODO: Decl order matters for some reason.
    VECTOR sp10;
    q19_12 dist;
    s32    var_s0;
    s32    count;
    q19_12 shortestDist;
    s32    foundIdx;
    q19_12 distMax;
    s32    i;
    q19_12 temp;

    // TODO: Use macro.
    temp = SquareRoot0(SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vx - Q12(20.0f)) >> 4) +
                       SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vz - Q12(100.0f)) >> 4)) << 4;
    if (temp > Q12(6.5f))
    {
        var_s0 = 0;
    }
    else if (temp > Q12(3.2f))
    {
        var_s0 = 1;
    }
    else
    {
        var_s0 = 2;
    }

    shortestDist = Q12(20.0f);
    dist = Q12(20.0f);

    foundIdx = -1;
    distMax   = g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110;
    count = (3 - var_s0) * 4;

    for (i = 0; i < count; i++)
    {
        switch (var_s0)
        {
            case 0:
                sp10.vx = D_800CB304[i][0] + Q12(20.0f);
                sp10.vy = 0;
                sp10.vz = D_800CB304[i][1] + Q12(100.0f);
                break;

            case 1:
                sp10.vx = D_800CB364[i][0] + Q12(20.0f);
                sp10.vy = 0;
                sp10.vz = D_800CB364[i][1] + Q12(100.0f);
                break;

            case 2:
                sp10.vx = D_800CB3A4[i][0] + Q12(20.0f);
                sp10.vy = 0;
                sp10.vz = D_800CB3A4[i][1] + Q12(100.0f);
                break;
        }

        if (!func_800DB6FC(&sp10))
        {
            dist = SquareRoot0(SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vx - sp10.vx) >> 4) +
                              SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vz - sp10.vz) >> 4))
                  << 4;

            if (dist < shortestDist)
            {
                foundIdx = i;
            }
        }
    }

    if (foundIdx == NO_VALUE)
    {
        return 0;
    }

    if (dist < distMax)
    {
        switch (var_s0)
        {
            case 0:
                sp10.vx = D_800CB304[foundIdx][0] + Q12(20.0f);
                sp10.vz = D_800CB304[foundIdx][1] + Q12(100.0f);
                break;

            case 1:
                sp10.vx = D_800CB364[foundIdx][0] + Q12(20.0f);
                sp10.vz = D_800CB364[foundIdx][1] + Q12(100.0f);
                break;

            case 2:
                sp10.vx = D_800CB3A4[foundIdx][0] + Q12(20.0f);
                sp10.vz = D_800CB3A4[foundIdx][1] + Q12(100.0f);
                break;
        }

        chara->position_18.vx = sp10.vx;
        chara->position_18.vz = sp10.vz;
        func_800DB748(chara);
        return 1;
    }

    return 2;
}

s32 func_800DBD64(s_SubCharacter* chara) // 0x800DBD64
{
    q19_12 shortestDist;
    q19_12 dist;
    q19_12 posX;
    q19_12 posZ;
    s32    i;

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 > Q12(2.0f))
    {
        return 0;
    }

    shortestDist = Q12(6.0f);

    for (i = 0; i < 10; i++)
    {
        posX = chara->position_18.vx - Q12(20.0f);
        posZ = chara->position_18.vz - Q12(100.0f);

        // TODO: Use macro.
        dist = SquareRoot0(SQUARE((D_800CB250[i] - posX) >> 4) + SQUARE((D_800CB278[i] - posZ) >> 4)) << 4;
        if (shortestDist > dist)
        {
            shortestDist = dist;
        }
    }

    return shortestDist < g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110;
}

void func_800DBE5C(s_SubCharacter* chara)
{
    q3_12  angle;
    q19_12 unkAngle1;
    q3_12  unkAngle0;

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8 == 1)
    {
        unkAngle1 = ((Rng_Rand16() & 0x1) * Q12_ANGLE(180.0f)) - Q12_ANGLE(90.0f);
    }
    else
    {
        unkAngle1 = ((Rng_Rand16() & 0x1) * Q12_ANGLE(180.0f)) - Q12_ANGLE(45.0f);
    }

    // TODO: Use macro.
    unkAngle0 = Q12_ANGLE_NORM_U(unkAngle1 + ratan2((chara->position_18.vx - Q12(20.0f)) >> 4, (chara->position_18.vz - Q12(100.0f)) >> 4) + Q12(1.0f));

    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(1, true))
    {
        if (chara->model_0.anim_4.keyframeIdx_8 >= 0 &&
            chara->model_0.anim_4.keyframeIdx_8 <= 23)
        {
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = D_800CB1D8[chara->model_0.anim_4.keyframeIdx_8];
        }
    }

    Math_ShortestAngleGet(chara->rotation_24.vy, unkAngle0, &angle);
    if (ABS(angle) < Q12_ANGLE(5.625f))
    {
        chara->rotation_24.vy = unkAngle0;
    }
    else if (angle > Q12_ANGLE(0.0f))
    {
        chara->rotation_24.vy += Q12_ANGLE(5.625f);
    }
    else
    {
        chara->rotation_24.vy -= Q12_ANGLE(5.625f);
    }

    chara->rotation_24.vy += (Rng_Rand16() % Q12_ANGLE(11.25f)) - Q12_ANGLE(5.625f);

    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_10C += g_DeltaTime;
    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_10C > Q12(5.0f))
    {
        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 0;
        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_10C = 0;
    }
}

void func_800DC018(s_SubCharacter* chara) // 0x800DC018
{
    s_RayData ray;
    VECTOR3   from;
    VECTOR3   to;
    q19_12    newRotY;

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116)
    {
        case 2:
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12_ANGLE(11.25f / 4.0f));
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 = CLAMP(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106,
                                                                               Q12_ANGLE(0.0f),
                                                                               Q12_ANGLE(135.0f));

            newRotY = chara->rotation_24.vy;
            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 < Q12_ANGLE(90.0f))
            {
                newRotY += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12_ANGLE(11.25f / 4.0f));
            }
            chara->rotation_24.vy = newRotY;

            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 == Q12_ANGLE(135.0f))
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 = Q12_ANGLE(0.0f);
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 0;
            }
            break;

        case 3:
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12_ANGLE(11.25f / 4.0f));
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 = CLAMP(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106,
                                                                               Q12_ANGLE(-135.0f),
                                                                               Q12_ANGLE(0.0f));

            newRotY = chara->rotation_24.vy;
            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 > Q12_ANGLE(-90.0f))
            {
                newRotY -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12_ANGLE(11.25f / 4.0f));
            }
            chara->rotation_24.vy = newRotY;

            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 == Q12_ANGLE(-135.0f))
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 = Q12_ANGLE(0.0f);
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 0;
            }
            break;

        default:
            from.vx = chara->position_18.vx;
            from.vy = chara->position_18.vy;
            from.vz = chara->position_18.vz;

            to.vx = chara->position_18.vx + Q12_MULT(Math_Sin(chara->rotation_24.vy), Q12(0.3f));
            to.vy = from.vy;
            to.vz = chara->position_18.vz + Q12_MULT(Math_Cos(chara->rotation_24.vy), Q12(0.3f));

            if (Ray_LineCheck(&ray, &from, &to))
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = (Rng_Rand16() & 0x1) + 2;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 = Q12_ANGLE(0.0f);
            }
            break;
    }
}
