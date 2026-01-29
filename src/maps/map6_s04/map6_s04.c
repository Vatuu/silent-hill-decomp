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

s32 func_800D8898(s_AnimInfo* arg0) // 0x800D8898
{
    if (arg0->status_4 == 3)
    {
        if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 0)
        {
            return 0;
        }

        if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 == 1)
        {
            return D_800CB118[arg0->startKeyframeIdx_C];
        }
        else
        {
            return D_800CB178[arg0->startKeyframeIdx_C];
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

void func_800D8B14(s_SubCharacter* arg0, s_Model* arg1) // 0x800D8B14
{
    u8  sp10;
    s16 sp12;

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8 != 0)
    {
        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8 -= g_DeltaTime0 * 0xF;
    }

    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8 = CLAMP(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8, 0, INT_MAX);

    Player_DisableDamage(&sp10, 0);

    if (sp10 != 0)
    {
        return;
    }

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8 < 0xD)
    {
        if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8 > 2)
        {
            return;
        }
    }

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE == 9 ||
        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE == 11)
    {
        arg0->damage_B4.amount_C = 0;
    }
    else
    {
        if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE != 12)
        {
            arg0->damage_B4.amount_C = arg0->damage_B4.amount_C >> 1;
        }

        if (arg0->damage_B4.amount_C != 0)
        {
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8 += arg0->damage_B4.amount_C;

            arg0->health_B0         -= arg0->damage_B4.amount_C;
            arg0->damage_B4.amount_C = 0;

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_122 = FP_ANGLE_NORM_U(
                ratan2((arg0->position_18.vx - g_SysWork.playerWork_4C.player_0.position_18.vx) >> 4,
                       (arg0->position_18.vz - g_SysWork.playerWork_4C.player_0.position_18.vz) >> 4) +
                0x1000);

            Math_ShortestAngleGet(arg0->rotation_24.vy, g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_122, &sp12);

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_122 = sp12;

            if (arg0->health_B0 <= 0)
            {
                Player_DisableDamage(&sp10, 1);
                Savegame_EventFlagSet(EventFlag_446);
                func_8004C564(0, -1);
            }
            else
            {
                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8 > 0x31FFFF)
                {
                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC != 0xC)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 9;
                        arg0->model_0.stateStep_3                                 = 0;
                    }
                }

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F8 > 0x31FFFF ||
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE == 0xC)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 9;
                    arg1->stateStep_3                                         = 0;
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

void func_800D8D7C(s_SubCharacter* chara, s_Model* arg1, GsCOORDINATE2* coords) // 0x800D8D7C
{
    enum _SfxId sfx;
    s8          pitch0;
    s8          pitch1;
    s32         angle0;
    s32         moveSpeed;

    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 = SquareRoot0(
                                                                     SQUARE(Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx)) +
                                                                     SQUARE(Q12_TO_Q8(g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz)))
                                                                 << 4;

    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_120 = func_800DB6FC(&chara->position_18);

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_120)
    {
        g_SysWork.npcs_1A0[0].properties_E4.player.runTimer_108 += g_DeltaTime0;
    }
    else
    {
        g_SysWork.npcs_1A0[0].properties_E4.player.runTimer_108 = 0;
    }

    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106++;

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8)
    {
        case 0:
            func_800D9AB4(chara, arg1, coords);
            break;

        case 1:
            func_800DA9C8(chara, arg1, coords);
            break;

        case 4:
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A = 0x400;

            Model_AnimStatusKeyframeSet(chara->model_0, 4, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            Model_AnimStatusKeyframeSet(*arg1, 4, true, MONSTER_CYBIL_ANIM_INFOS, 0);

            if (chara->model_0.anim_4.keyframeIdx_8 >= 0x42)
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
                arg1->stateStep_3                                         = 0;
            }
            break;

        case 5:
            if (chara->model_0.stateStep_3 == 0)
            {
                arg1->stateStep_3 = 0;
                Model_AnimStatusKeyframeSet(chara->model_0, 14, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            }

            Model_AnimStatusKeyframeSet(*arg1, 14, true, MONSTER_CYBIL_ANIM_INFOS, 0);

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
                arg1->stateStep_3 = 0;
                Model_AnimStatusSet(&chara->model_0, 15, false);
            }
            Model_AnimStatusSet(arg1, 15, false);

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            if (chara->properties_E4.npc.field_F8)
            {
                chara->properties_E4.dahlia.stateIdx0 = 0;
                chara->model_0.stateStep_3            = 0;
                chara->properties_E4.npc.field_F8     = 0;
            }

            if (chara->model_0.anim_4.keyframeIdx_8 == 0x157)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8 = 0xC;
                chara->model_0.stateStep_3                                = 0;
                arg1->stateStep_3                                         = 0;
            }
            break;

        case 12:
            Model_AnimStatusKeyframeSet(chara->model_0, 21, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            Model_AnimStatusKeyframeSet(*arg1, 21, true, MONSTER_CYBIL_ANIM_INFOS, 0);
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
                arg1->stateStep_3 = 0;
                Model_AnimStatusKeyframeSet(chara->model_0, 20, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            }
            Model_AnimStatusKeyframeSet(*arg1, 20, true, MONSTER_CYBIL_ANIM_INFOS, 0);

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
                arg1->stateStep_3 = 0;
                Model_AnimStatusKeyframeSet(chara->model_0, 18, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            }
            Model_AnimStatusKeyframeSet(*arg1, 18, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            if (arg1->anim_4.keyframeIdx_8 >= 0x1D)
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
                arg1->stateStep_3 = 0;
                Model_AnimStatusKeyframeSet(chara->model_0, 19, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            }
            Model_AnimStatusKeyframeSet(*arg1, 19, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            WorldGfx_HeldItemAttach(Chara_MonsterCybil, 2);
            if (chara->properties_E4.npc.field_F8)
            {
                chara->properties_E4.dahlia.stateIdx0 = 0;
                chara->model_0.stateStep_3            = 0;
                chara->properties_E4.npc.field_F8     = 0;
            }
            if (!chara->model_0.stateStep_3)
            {
                arg1->stateStep_3 = 0;
            }
            break;

        case 7:
            if (!chara->model_0.stateStep_3)
            {
                arg1->stateStep_3 = 0;
                Model_AnimStatusKeyframeSet(chara->model_0, 16, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            }
            Model_AnimStatusKeyframeSet(*arg1, 16, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            break;

        case 8:
            if (!chara->model_0.stateStep_3)
            {
                arg1->stateStep_3 = 0;
                Model_AnimStatusKeyframeSet(chara->model_0, 17, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            }
            Model_AnimStatusKeyframeSet(*arg1, 17, true, MONSTER_CYBIL_ANIM_INFOS, 0);
            break;
    }

    func_8007FDE0(0xB, &sfx, &pitch0, &pitch1);

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8)
    {
        case 9:
            sharedFunc_800D908C_0_s00(0x29, chara, 5, 0x10, sfx, pitch0);
            break;

        case 10:
            sharedFunc_800D9188_0_s00(0x25, chara, 0x1D, 0x654);
            break;

        case 11:
            if (chara->model_0.anim_4.keyframeIdx_8 == 0x26)
            {
                func_8006342C(0x3F, 0x400, chara->rotation_24.vy, g_SysWork.npcCoords_FC0);
            }
            sharedFunc_800D9188_0_s00(0x27, chara, 0x26, 0x656);
            break;

        case 4:
            sharedFunc_800D9188_0_s00(9, chara, 0x45, 0x655);
            break;

        case 5:
            if (chara->model_0.anim_4.keyframeIdx_8 < 0x138)
            {
                sharedFunc_800D9188_0_s00(0x1D, chara, 0x121, 0x660);
            }
            else
            {
                sharedFunc_800D9188_0_s00(0x1D, chara, 0x139, 0x65F);
            }
            break;
    }

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 1)
    {
        sharedFunc_800D908C_0_s00(3, chara, 5, 0x10, sfx, pitch0);
    }

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE)
    {
        case 2:
            if (ANIM_STATUS_IS_ACTIVE(arg1->anim_4.status_0) && arg1->anim_4.keyframeIdx_8 >= 0x1D && !sharedData_800D16E4_2_s01)
            {
                func_8005DC1C(0x654, &chara->position_18, 0x40, 0);
                sharedData_800D16E4_2_s01 = 1;
            }
            else if (arg1->anim_4.keyframeIdx_8 < 0x1D)
            {
                sharedData_800D16E4_2_s01 = 0;
            }
            break;

        case 3:
            if (ANIM_STATUS_IS_ACTIVE(arg1->anim_4.status_0) && arg1->anim_4.keyframeIdx_8 >= 0x26 && !sharedData_800D16E4_2_s01)
            {
                func_8005DC1C(Sfx_Unk1622, &chara->position_18, 0x40, 0);
                sharedData_800D16E4_2_s01 = 1;
            }

            else if (arg1->anim_4.keyframeIdx_8 < 0x26)
            {
                sharedData_800D16E4_2_s01 = 0;
            }
            break;

        case 4:
            break;
    }

    moveSpeed              = g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126;
    angle0                 = g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_122;
    chara->headingAngle_3C = FP_ANGLE_ABS(angle0 + chara->rotation_24.vy);

    chara->moveSpeed_38 = moveSpeed;
    chara->field_34    += g_DeltaTime2;

    coords->flg = false;
    Math_RotMatrixZxyNegGte(&chara->rotation_24, &coords->coord);
}

void func_800D9790(s_SubCharacter* arg0, s_Model* arg1) // 0x800D9790
{
    s_800C4590 sp10;
    VECTOR3    sp30;
    VECTOR3    sp40;
    s32        temp_s4;
    s32        temp_s0;
    s32        temp_s2;
    s32        temp_s3;

    sp30 = arg0->position_18;

    temp_s4 = arg0->headingAngle_3C;
    temp_s0 = Q12_MULT_PRECISE(arg0->moveSpeed_38, g_DeltaTime0);

    temp_s2 = (temp_s0 < -0x7FFF || temp_s0 > 0x7FFF) * 4;
    temp_s3 = temp_s2 >> 1;

    sp40.vx = Q12_MULT_PRECISE(temp_s0 >> temp_s3, Math_Sin(temp_s4) >> temp_s3) << temp_s2;
    sp40.vz = Q12_MULT_PRECISE(temp_s0 >> temp_s3, Math_Cos(temp_s4) >> temp_s3) << temp_s2;
    sp40.vy = Q12_MULT_PRECISE(arg0->field_34, g_DeltaTime0);

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC)
    {
        case 11:
            if (arg0->model_0.anim_4.status_0 & 1)
            {
                arg0->field_D4.radius_0 = 0x4CC - (arg0->model_0.anim_4.keyframeIdx_8 - 0xD8) * 0x3000 / 100;
            }
            func_80069B24(&sp10, &sp40, arg0);
            arg0->position_18.vx += sp10.offset_0.vx;
            arg0->position_18.vz += sp10.offset_0.vz;
            arg0->field_34        = 0;
            break;

        case 12:
            arg0->field_D4.radius_0 = 0;
            arg0->position_18.vx   += sp40.vx;
            arg0->position_18.vz   += sp40.vz;
            arg0->field_34          = 0;
            break;

        default:
            arg0->field_D4.radius_0  = 0x4CC;
            arg0->field_D8.offsetZ_6 = 0;
            arg0->field_D8.offsetX_4 = 0;
            arg0->field_D8.offsetZ_2 = 0;
            arg0->field_D8.offsetX_0 = 0;

            func_80069B24(&sp10, &sp40, arg0);

            arg0->position_18.vx += sp10.offset_0.vx;
            arg0->position_18.vy  = 0;
            arg0->field_34        = 0;
            arg0->position_18.vz += sp10.offset_0.vz;
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

void func_800D9AAC(s_SubCharacter* chara, s_Model* arg1) {}                  // 0x800D9AAC

void func_800D9AB4(s_SubCharacter* arg0, s_Model* arg1, GsCOORDINATE2* arg2) // 0x800D9AB4
{
    s16 temp_v0;

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC)
    {
        case 0:
            break;

        case 1:
            if (arg0->model_0.stateStep_3 == 0)
            {
                arg0->model_0.anim_4.status_0 = 2;
                arg0->model_0.stateStep_3++;
            }

            func_800DC018(arg0);

            if (g_SysWork.playerWork_4C.player_0.health_B0 > 0 && g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 == 0)
            {
                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 > 0x999)
                {
                    func_800DB748(arg0);
                }

                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;

                if (arg0->model_0.anim_4.status_0 == 3)
                {
                    if ((u16)arg0->model_0.anim_4.keyframeIdx_8 < 0x18)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = D_800CB208[arg0->model_0.anim_4.keyframeIdx_8];
                    }
                }

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_120 == 0)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 <<= 1;

                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 > 0x3C)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 = 0;

                        if ((Rng_Rand16() % 10) > 4 && g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 > 0x4000)
                        {
                            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE = func_800DB930();

                            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE != -1)
                            {
                                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 0xC;
                                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 0xC;
                                arg0->model_0.stateStep_3                                 = 0;
                                arg1->stateStep_3                                         = 0;
                            }
                        }
                        else
                        {
                            func_800DBA48(arg0);
                        }
                    }
                }

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_104 <= 0 || arg0->health_B0 <= 0x7CFFFF)
                {
                    Savegame_EventFlagSet(EventFlag_444);
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8 = 3;
                    arg0->model_0.stateStep_3                                 = 0;
                    arg1->stateStep_3                                         = 0;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F4 = 0;
                    return;
                }
            }
            else if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 == 1)
            {
                func_800DBE5C(arg0);

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_104 <= 0 || arg0->health_B0 <= 0x7CFFFF)
                {
                    Savegame_EventFlagSet(EventFlag_444);
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8 = 3;
                    arg0->model_0.stateStep_3                                 = 0;
                    arg1->stateStep_3                                         = 0;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F4 = 0;
                    return;
                }
            }
            else
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
                if (arg0->model_0.anim_4.status_0 == 3)
                {
                    if ((u16)arg0->model_0.anim_4.keyframeIdx_8 < 0x18)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = D_800CB208[arg0->model_0.anim_4.keyframeIdx_8];
                    }
                }
            }
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_122 = 0;
            break;

        case 2:
            if (arg0->model_0.stateStep_3 == 0)
            {
                arg0->model_0.anim_4.status_0 = 4;
                arg0->model_0.stateStep_3++;
            }
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            break;

        case 3:
            if (arg0->model_0.stateStep_3 == 0)
            {
                arg0->model_0.anim_4.status_0 = 6;
                arg0->model_0.stateStep_3++;
            }
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            break;

        case 8:
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            if (arg0->model_0.stateStep_3 == 0)
            {
                arg0->model_0.anim_4.status_0 = 0x10;
                arg0->model_0.stateStep_3++;
            }
            if (arg0->model_0.anim_4.keyframeIdx_8 == D_800EA836)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 1;
                arg0->model_0.stateStep_3                                 = 0;
            }
            break;

        case 9:
            func_800D87B0(arg0);
            break;

        case 10:
            if (arg0->model_0.stateStep_3 == 0)
            {
                arg0->model_0.anim_4.status_0 = 0x14;
                arg0->model_0.stateStep_3++;
            }
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            break;

        case 11:
            if (arg0->model_0.stateStep_3 == 0)
            {
                arg0->model_0.anim_4.status_0 = 0x17;
                arg0->model_0.stateStep_3++;
                arg0->model_0.anim_4.time_4        = FP_TO(MONSTER_CYBIL_ANIM_INFOS[23].endKeyframeIdx_E, Q12_SHIFT);
                arg0->model_0.anim_4.keyframeIdx_8 = MONSTER_CYBIL_ANIM_INFOS[23].endKeyframeIdx_E;
            }

            if (arg0->properties_E4.monsterCybil.field_126 != 0)
            {
                arg0->properties_E4.monsterCybil.field_126 = arg0->properties_E4.monsterCybil.field_126 - 0x147;
                if (arg0->properties_E4.monsterCybil.field_126 < 0)
                {
                    arg0->properties_E4.monsterCybil.field_126 = 0;
                }
            }

            if (arg0->model_0.anim_4.keyframeIdx_8 == D_800EA896 - 4 || arg0->model_0.anim_4.keyframeIdx_8 == D_800EA896 - 5)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0x999;
            }

            if (arg0->model_0.anim_4.keyframeIdx_8 <= D_800EA896 - 7)
            {
                arg0->position_18.vy += g_DeltaTime2 >> 2;
            }
            else if (D_800EA896 - 4 >= arg0->model_0.anim_4.keyframeIdx_8)
            {
                arg0->position_18.vy += g_DeltaTime2 >> 4;
            }
            else
            {
                arg0->position_18.vy = g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_100 - 0x733;
            }

            if (arg0->position_18.vy > 0)
            {
                arg0->position_18.vy = 0;
            }

            arg0->rotation_24.vy = g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE < 6 ? D_800CB2A0[g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE] - 0x800 : D_800CB2A0[g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE];

            temp_v0 = 1;

            if (arg0->model_0.anim_4.keyframeIdx_8 == D_800EA894)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = temp_v0;
                arg0->model_0.stateStep_3                                 = 0;
            }
            break;

        case 12:
            arg0->position_18.vx = D_800CB2B4[g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE] + 0x14000;
            arg0->position_18.vy = g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_100 - 0x733;
            arg0->position_18.vz = D_800CB2DC[g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE] + 0x64000;

            arg0->rotation_24.vy = g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE < 6 ? D_800CB2A0[g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE] - 0x800 : D_800CB2A0[g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_FE];

            if (arg0->model_0.anim_4.keyframeIdx_8 >= MONSTER_CYBIL_ANIM_INFOS[25].startKeyframeIdx_C &&
                MONSTER_CYBIL_ANIM_INFOS[25].endKeyframeIdx_E >= arg0->model_0.anim_4.keyframeIdx_8)
            {
                arg0->field_D8.offsetX_0 = Q12_MULT(Math_Sin(arg0->rotation_24.vy), -0x75C);
                arg0->field_D8.offsetZ_2 = Q12_MULT(Math_Cos(arg0->rotation_24.vy), -0x75C);
            }

            if (arg0->model_0.stateStep_3 == 0)
            {
                arg0->model_0.anim_4.status_0 = 0x18;
                arg0->model_0.stateStep_3++;
            }
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            break;
    }

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE)
    {
        case 0:
            break;

        case 1:
            if (arg1->stateStep_3 == 0)
            {
                arg1->anim_4.status_0 = 2;
                arg1->stateStep_3++;
            }

            if (arg1->anim_4.status_0 == 3)
            {
                arg1->anim_4.time_4        = arg0->model_0.anim_4.time_4;
                arg1->anim_4.keyframeIdx_8 = arg0->model_0.anim_4.keyframeIdx_8;
            }

            if (g_SysWork.playerWork_4C.player_0.health_B0 > 0 && g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 == 0)
            {
                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 < 0xCCC &&
                    (g_SysWork.playerWork_4C.extra_128.state_1C > 0x32 || g_SysWork.playerWork_4C.extra_128.state_1C < 0x2F))
                {
                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE == 1)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 8;
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 8;
                        arg0->model_0.stateStep_3                                 = 0;
                        arg1->stateStep_3                                         = 0;
                    }
                }
                else if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_108 >= 0x3000 &&
                         (func_800DB81C(arg0) == 0 || g_SysWork.playerWork_4C.extra_128.state_1C == 0x2F ||
                          g_SysWork.playerWork_4C.extra_128.state_1C == 0x30))
                {
                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 <= 0x4000)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 2;
                        arg0->model_0.stateStep_3                                 = 0;
                    }

                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 2;
                    arg1->stateStep_3                                         = 0;
                }
            }
            break;

        case 2:
            if (arg1->stateStep_3 == 0)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0 = 0;
                D_800EBB48                                                = Rng_Rand16() % 0x1000;

                if (arg1->stateStep_3 == 0)
                {
                    arg1->anim_4.status_0 = 4;
                    arg1->stateStep_3++;
                }
            }

            func_800DB748(arg0);

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0 += g_DeltaTime0;

            D_800ED570.vx = arg2[10].workm.t[0] * 0x10;
            D_800ED570.vy = arg2[10].workm.t[1] * 0x10;
            D_800ED570.vz = arg2[10].workm.t[2] * 0x10;

            if (arg1->anim_4.keyframeIdx_8 >= 0x1D)
            {
                WorldGfx_HeldItemAttach(Chara_MonsterCybil, 2);
            }

            if (arg1->anim_4.keyframeIdx_8 == D_800EA776 && D_800EBB48 < g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0)
            {
                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_120 != 0 && !(g_SysWork.playerWork_4C.player_0.flags_3E & 8))
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_114 = 0;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE  = 3;
                    arg1->stateStep_3                                          = 0;

                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 2)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 3;
                        arg0->model_0.stateStep_3                                 = 0;
                    }
                }
                else
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 0xA;
                    arg1->stateStep_3                                         = 0;

                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC != 1)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 0xA;
                        arg0->model_0.stateStep_3                                 = 0;
                    }
                }
            }
            break;

        case 3:
            if (arg1->stateStep_3 == 0)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0  = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_108 = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_104--;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_114++;

                D_800EBB4A = Rng_Rand16() % 0x1000;
            }

            D_800ED570.vx = arg2[10].workm.t[0] * 0x10;
            D_800ED570.vy = arg2[10].workm.t[1] * 0x10;
            D_800ED570.vz = arg2[10].workm.t[2] * 0x10;

            if (arg1->anim_4.keyframeIdx_8 >= MONSTER_CYBIL_ANIM_INFOS[7].startKeyframeIdx_C + 2 &&
                MONSTER_CYBIL_ANIM_INFOS[7].startKeyframeIdx_C + 4 >= arg1->anim_4.keyframeIdx_8 &&
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_115 == 0)
            {
                arg0->model_0.anim_4.animInfo_C = MONSTER_CYBIL_ANIM_INFOS;
                arg0->field_44.field_0          = 1;

                func_8006342C(0x3F, g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A, arg0->rotation_24.vy, g_SysWork.npcCoords_FC0);

                if (func_8008A0E4(arg0->field_44.field_0, 0x3F, arg0, &D_800ED570, &g_SysWork.playerWork_4C.player_0, arg0->rotation_24.vy, g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A) != -1)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_115 = 1;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 1;
                }
            }
            else
            {
                arg0->field_44.field_0 = 0;
            }

            if (arg1->anim_4.keyframeIdx_8 >= MONSTER_CYBIL_ANIM_INFOS[7].startKeyframeIdx_C + 4)
            {
                func_800DB748(arg0);
            }

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0 += g_DeltaTime0;

            if (arg1->stateStep_3 == 0)
            {
                arg1->anim_4.status_0 = 6;
                arg1->stateStep_3++;
            }

            if (arg0->model_0.anim_4.status_0 & 1 && arg1->anim_4.keyframeIdx_8 == MONSTER_CYBIL_ANIM_INFOS[7].endKeyframeIdx_E)
            {
                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_120 == 0 || g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_104 == 0 ||
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_114 == 3 || g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_115 != 0 ||
                    func_800DB81C(arg0) == 1)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_115 = 0;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE  = 0xA;
                    arg1->stateStep_3                                          = 0;

                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC != 1)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 0xA;
                        arg0->model_0.stateStep_3                                 = 0;
                    }
                }
                else if (D_800EBB4A + 0x1800 < g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0)
                {
                    arg1->stateStep_3                                         = 0;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0 = 0;

                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 3)
                    {
                        arg0->model_0.stateStep_3 = 0;
                    }
                }
            }
            break;

        case 8:
            func_800DB748(arg0);

            D_800ED570.vx = arg2[10].workm.t[0] * 0x10;
            D_800ED570.vy = arg2[10].workm.t[1] * 0x10;
            D_800ED570.vz = arg2[10].workm.t[2] * 0x10;

            if (arg1->stateStep_3 == 0)
            {
                arg1->anim_4.status_0 = 0x10;
                arg1->stateStep_3++;
            }

            if (arg1->anim_4.keyframeIdx_8 > 0xA9 && arg1->anim_4.keyframeIdx_8 < 0xAD)
            {
                arg0->model_0.anim_4.animInfo_C = MONSTER_CYBIL_ANIM_INFOS;
                arg0->field_44.field_0          = 1;
            }
            else
            {
                arg0->field_44.field_0 = 0;
            }

            if (func_8008A0E4(arg0->field_44.field_0, 0x40, arg0, &D_800ED570, &g_SysWork.playerWork_4C.player_0, arg0->rotation_24.vy, 0x400) != -1)
            {
                g_SysWork.playerWork_4C.player_0.damage_B4.position_0.vz = 0x1000;

                if (sharedData_800D16E4_2_s01 == 0)
                {
                    func_8005DC1C(0x65E, &arg0->position_18, 0x40, 0);
                }
                sharedData_800D16E4_2_s01                                  = 1;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 1;
            }

            if (arg1->anim_4.keyframeIdx_8 & 1 && arg1->anim_4.keyframeIdx_8 == D_800EA836)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 1;
                arg1->stateStep_3                                         = 0;
                sharedData_800D16E4_2_s01                                 = 0;
            }
            break;

        case 9:
            func_800D8848(arg1);

            if (arg1->anim_4.keyframeIdx_8 == D_800EA856 && g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 0xC)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 0xB;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 0xB;
                arg0->model_0.stateStep_3                                 = 0;
                arg1->stateStep_3                                         = 0;
                arg0->field_D8.offsetZ_2                                  = 0;
                arg0->field_D8.offsetX_0                                  = 0;
            }
            break;

        case 10:
            if (arg1->stateStep_3 == 0)
            {
                arg1->anim_4.status_0 = 0x14;
                arg1->stateStep_3++;
            }

            if (arg1->anim_4.status_0 & 1 && arg1->anim_4.keyframeIdx_8 < 0xD1)
            {
                WorldGfx_HeldItemAttach(Chara_MonsterCybil, 1);
            }

            if (arg1->anim_4.keyframeIdx_8 == MONSTER_CYBIL_ANIM_INFOS[arg1->anim_4.status_0].startKeyframeIdx_C)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 1;
                arg1->stateStep_3                                         = 0;

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 0xA)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 1;
                    arg0->model_0.stateStep_3                                 = 0;
                }
            }
            break;

        case 11:
            if (arg1->stateStep_3 == 0)
            {
                arg1->anim_4.status_0 = 0x17;
                arg1->stateStep_3++;
                arg1->anim_4.time_4        = FP_TO(MONSTER_CYBIL_ANIM_INFOS[23].endKeyframeIdx_E, Q12_SHIFT);
                arg1->anim_4.keyframeIdx_8 = MONSTER_CYBIL_ANIM_INFOS[23].endKeyframeIdx_E;
            }

            if (arg1->anim_4.keyframeIdx_8 == D_800EA894)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 1;
                arg1->stateStep_3                                         = 0;
            }
            break;

        case 12:
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0 += g_DeltaTime0;
            if (arg0->model_0.stateStep_3 == 0)
            {
                func_8005DC1C(0x652, &arg0->position_18, 0x40, 0);
            }

            if (arg1->stateStep_3 == 0)
            {
                arg1->anim_4.status_0 = 0x18;
                arg1->stateStep_3++;
            }

            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0 > 0x9FFF || g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_108 >= 0x6000)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 0xB;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 0xB;
                arg0->model_0.stateStep_3                                 = 0;
                arg1->stateStep_3                                         = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0 = 0;
            }
            break;
    }
}

void func_800DA9C8(s_SubCharacter* arg0, s_Model* arg1, GsCOORDINATE2* arg2) // 0x800DA9C8
{
    s32 temp_s0;
    s32 temp_v0_2;
    s32 var_a1;
    s32 var_s3;

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC)
    {
        case 0:
            break;

        case 1:
            if (arg0->model_0.stateStep_3 == 0)
            {
                arg0->model_0.anim_4.status_0 = 3;
                arg0->model_0.stateStep_3++;
                arg0->model_0.anim_4.time_4        = MONSTER_CYBIL_ANIM_INFOS[3].startKeyframeIdx_C + 0x3000;
                arg0->model_0.anim_4.keyframeIdx_8 = MONSTER_CYBIL_ANIM_INFOS[3].startKeyframeIdx_C + 3;
            }

            func_800DC018(arg0);

            if (g_SysWork.playerWork_4C.player_0.health_B0 > 0 && g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 == 0)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 > 0x999)
                {
                    func_800DB748(arg0);
                }

                if (arg0->model_0.anim_4.status_0 == 3)
                {
                    if ((u16)arg0->model_0.anim_4.keyframeIdx_8 < 0x18)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = D_800CB208[arg0->model_0.anim_4.keyframeIdx_8];
                    }
                }

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_120 == 0)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 <<= 1;

                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 > 0x3C)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 = 0;
                        func_800DBA48(arg0);
                    }
                }

                if (func_800DBD64(arg0) != 0)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_10C += g_DeltaTime0;
                }
                else
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_10C = 0;
                }

                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_10C > 0x3000)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 1;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_10C = 0;
                }
            }
            else if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 == 1)
            {
                func_800DBE5C(arg0);
            }
            else
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;

                if (arg0->model_0.anim_4.status_0 == 3)
                {
                    if ((u16)arg0->model_0.anim_4.keyframeIdx_8 < 0x18)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = D_800CB208[arg0->model_0.anim_4.keyframeIdx_8];
                    }
                }
            }
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_122 = 0;
            break;

        case 5:
            if (arg0->model_0.stateStep_3 == 0)
            {
                arg0->model_0.anim_4.status_0 = 0xA;
                arg0->model_0.stateStep_3++;
            }

            func_800DB748(arg0);

            if (arg0->model_0.anim_4.keyframeIdx_8 >= D_800EA7D4 + 0xA)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0xB33;
            }
            break;

        case 6:
            var_s3 = 0;
            var_a1 = 0;

            if (arg0->model_0.stateStep_3 == 0)
            {
                arg0->model_0.anim_4.status_0 = 0xC;
                arg0->model_0.stateStep_3++;
            }

            if (arg0->model_0.anim_4.status_0 & 1)
            {
                arg0->model_0.anim_4.time_4        = g_SysWork.playerWork_4C.player_0.model_0.anim_4.time_4 - 0x340000;
                arg0->model_0.anim_4.keyframeIdx_8 = g_SysWork.playerWork_4C.player_0.model_0.anim_4.keyframeIdx_8 - 0x340;
            }

            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            temp_s0                                                    = ((u16)arg0->rotation_24.vy + 0x1800) & 0xFFF;

            switch (g_SysWork.playerWork_4C.extra_128.state_1C)
            {
                case 32:
                    var_s3 = g_SysWork.playerWork_4C.player_0.position_18.vx + Q12_MULT(Math_Sin(temp_s0), 0x9EB);
                    var_a1 = g_SysWork.playerWork_4C.player_0.position_18.vz + Q12_MULT(Math_Cos(temp_s0), 0x9EB);
                    break;

                case 33:
                    var_s3 = g_SysWork.playerWork_4C.player_0.position_18.vx + Q12_MULT(Math_Sin(temp_s0), 0xCCC);
                    var_a1 = g_SysWork.playerWork_4C.player_0.position_18.vz + Q12_MULT(Math_Cos(temp_s0), 0xCCC);
                    break;
            }

            if (g_SysWork.playerWork_4C.extra_128.state_1C > 0x1F && g_SysWork.playerWork_4C.extra_128.state_1C < 0x22)
            {
                if (var_s3 < arg0->position_18.vx)
                {
                    arg0->position_18.vx -= 0x20;
                }
                else if (arg0->position_18.vx < var_s3)
                {
                    arg0->position_18.vx += 0x20;
                }

                if (var_a1 < arg0->position_18.vz)
                {
                    arg0->position_18.vz = arg0->position_18.vz - 0x20;
                }
                else if (arg0->position_18.vz < var_a1)
                {
                    arg0->position_18.vz = arg0->position_18.vz + 0x20;
                }
            }
            break;

        case 7:
            if (arg0->model_0.stateStep_3 == 0)
            {
                arg0->model_0.anim_4.status_0 = 0xE;
                arg0->model_0.stateStep_3++;
            }

            if (arg0->model_0.anim_4.keyframeIdx_8 == D_800EA816)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 1;
                arg0->model_0.stateStep_3                                 = 0;
                arg0->position_18.vx                                     += Q12_MULT(Math_Sin(arg0->rotation_24.vy + 0x180), 0x199);
                arg0->position_18.vz                                     += Q12_MULT(Math_Cos(arg0->rotation_24.vy + 0x180), 0x199);
            }
            break;

        case 8:
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
            if (arg0->model_0.stateStep_3 == 0)
            {
                arg0->model_0.anim_4.status_0 = 0x10;
                arg0->model_0.stateStep_3++;
            }
            break;

        case 9:
            func_800D87B0(arg0);
            break;

        case 12:
            break;
    }

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE)
    {
        case 0:
            break;

        case 1:
            if (arg1->stateStep_3 == 0)
            {
                arg1->anim_4.status_0 = 3;
                arg1->stateStep_3++;
                arg1->anim_4.time_4        = MONSTER_CYBIL_ANIM_INFOS[3].startKeyframeIdx_C + 0x3000;
                arg1->anim_4.keyframeIdx_8 = MONSTER_CYBIL_ANIM_INFOS[3].startKeyframeIdx_C + 3;
            }

            if (arg1->anim_4.status_0 == 3)
            {
                arg1->anim_4.time_4        = arg0->model_0.anim_4.time_4;
                arg1->anim_4.keyframeIdx_8 = arg0->model_0.anim_4.keyframeIdx_8;
            }

            if (g_SysWork.playerWork_4C.player_0.health_B0 > 0 && g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 == 0 &&
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 < 0xCCC && g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 > 0x1E)
            {
                if (Rng_Rand16() % 8 >= 5)
                {
                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE == 1)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 8;
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 8;
                        arg0->model_0.stateStep_3                                 = 0;
                        arg1->stateStep_3                                         = 0;
                    }
                }
                else
                {
                    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE == 1)
                    {
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 5;
                        g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 5;
                        arg0->model_0.stateStep_3                                 = 0;
                        arg1->stateStep_3                                         = 0;
                    }
                }
            }
            break;

        case 5:
            D_800ED570.vx = arg2[10].workm.t[0] * 0x10;
            D_800ED570.vy = arg2[10].workm.t[1] * 0x10;
            D_800ED570.vz = arg2[10].workm.t[2] * 0x10;

            if (arg1->stateStep_3 == 0)
            {
                arg1->anim_4.status_0 = 0xA;
                arg1->stateStep_3++;
            }

            if (arg1->anim_4.keyframeIdx_8 == MONSTER_CYBIL_ANIM_INFOS[11].endKeyframeIdx_E)
            {
                arg0->model_0.anim_4.animInfo_C = MONSTER_CYBIL_ANIM_INFOS;
                arg0->field_44.field_0          = 1;
            }
            else
            {
                arg0->field_44.field_0 = 0;
            }

            temp_v0_2 = func_8008A0E4(arg0->field_44.field_0, 0x42, arg0, &D_800ED570, &g_SysWork.playerWork_4C.player_0, arg0->rotation_24.vy, 0x400);

            if (temp_v0_2 != -1)
            {
                g_SysWork.playerWork_4C.player_0.field_40 = arg0->field_40;
            }

            if (arg1->anim_4.keyframeIdx_8 == D_800EA7D6)
            {
                if (temp_v0_2 != -1)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 6;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 6;
                }
                else
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 7;
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 7;
                }

                arg1->stateStep_3                                          = 0;
                arg0->model_0.stateStep_3                                  = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_F0  = 0;
            }
            break;

        case 6:
            if (arg1->stateStep_3 == 0)
            {
                arg1->anim_4.status_0 = 0xC;
                arg1->stateStep_3++;
            }

            if (arg1->anim_4.status_0 & 1)
            {
                arg1->anim_4.time_4        = g_SysWork.playerWork_4C.player_0.model_0.anim_4.time_4 - 0x340000;
                arg1->anim_4.keyframeIdx_8 = g_SysWork.playerWork_4C.player_0.model_0.anim_4.keyframeIdx_8 - 0x340;
            }

            g_SysWork.playerWork_4C.player_0.damage_B4.amount_C = g_DeltaTime0 * 4;

            if (g_SysWork.playerWork_4C.player_0.field_40 == -1 || g_SysWork.playerWork_4C.player_0.health_B0 <= 0 ||
                g_SysWork.playerWork_4C.player_0.attackReceived_41 == -1)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 7;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 7;
                arg1->stateStep_3                                         = 0;
                arg0->model_0.stateStep_3                                 = 0;
                g_SysWork.playerWork_4C.player_0.damage_B4.amount_C       = 0;
            }

            if (arg1->anim_4.status_0 & 1)
            {
                if (arg1->anim_4.keyframeIdx_8 == 0x65)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_118 = 0;
                }
                else
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_118 = D_800CB238[arg1->anim_4.keyframeIdx_8 - 0x5B] +
                                                                                 (((D_800CB238[arg1->anim_4.keyframeIdx_8 - 0x5A] - D_800CB238[arg1->anim_4.keyframeIdx_8 - 0x5B]) * ((u16)arg1->anim_4.time_4 & 0xFFF)) / 0x1000);
                }
            }
            break;

        case 7:
            if (arg1->stateStep_3 == 0)
            {
                arg1->anim_4.status_0 = 0xE;
                arg1->stateStep_3++;
            }

            if (arg1->anim_4.keyframeIdx_8 == D_800EA816)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE  = 1;
                arg1->stateStep_3                                          = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 1;
            }
            break;

        case 8:
            func_800DB748(arg0);

            D_800ED570.vx = arg2[10].workm.t[0] * 0x10;
            D_800ED570.vy = arg2[10].workm.t[1] * 0x10;
            D_800ED570.vz = arg2[10].workm.t[2] * 0x10;

            if (arg1->stateStep_3 == 0)
            {
                arg1->anim_4.status_0 = 0x10;
                arg1->stateStep_3++;
            }

            if (arg1->anim_4.keyframeIdx_8 > 0xA9 && arg1->anim_4.keyframeIdx_8 < 0xAD)
            {
                arg0->model_0.anim_4.animInfo_C = MONSTER_CYBIL_ANIM_INFOS;
                arg0->field_44.field_0          = 1;
            }
            else
            {
                arg0->field_44.field_0 = 0;
            }

            if (func_8008A0E4(arg0->field_44.field_0, 0x41, arg0, &D_800ED570, &g_SysWork.playerWork_4C.player_0, arg0->rotation_24.vy, 0x400) != -1)
            {
                g_SysWork.playerWork_4C.player_0.damage_B4.position_0.vz = 0x1000;

                if (sharedData_800D16E4_2_s01 == 0)
                {
                    func_8005DC1C(0x65E, &arg0->position_18, 0x40, 0);
                }
                sharedData_800D16E4_2_s01                                  = 1;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 1;
            }

            if (arg1->anim_4.keyframeIdx_8 & 1 && arg1->anim_4.keyframeIdx_8 == D_800EA836)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE = 1;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC = 1;
                arg1->stateStep_3                                         = 0;
                arg0->model_0.stateStep_3                                 = 0;
                sharedData_800D16E4_2_s01                                 = 0;
            }
            break;

        case 9:
            func_800D8848(arg1);
            break;

        case 12:
            if (arg1->stateStep_3 == 0)
            {
                arg1->anim_4.status_0 = 0x18;
                arg1->stateStep_3++;
            }
            break;
    }
}

void func_800DB4CC(s_SubCharacter* chara, s_Model* model, GsCOORDINATE2* coord) // 0x800DB4CC
{
    s16 ang;
    s32 range;
    s32 delta;

    delta = (g_DeltaTime0 << 5) / 136;

    switch (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EE)
    {
        case 9:
        case 11:

            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 12)
            {
                D_800ED560.vy = -0xE0;
                D_800ED560.vz = -0x88;
                TransMatrix(&coord[1].coord, &D_800ED560);
            }

            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_EC == 11 && model->anim_4.status_0 == 19)
            {
                D_800ED560.vy = -0xE0;
                D_800ED560.vz = -0x88;
                TransMatrix(&coord[1].coord, &D_800ED560);
            }
            break;

        case 10:
            range = delta >> 1;

            if (range >= g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A - 0x400)
            {
                if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A - 0x400 >= -range)
                {
                    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A = 0x400;
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

            Math_RotMatrixZ(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A - 0x400, &coord[8].coord);
            break;

        case 2:
        case 3:
            ang = ratan2(SquareRoot0(SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vx - D_800ED570.vx) >> 4) +
                                     SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vz - D_800ED570.vz) >> 4)),
                         (g_SysWork.playerWork_4C.player_0.position_18.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_6 -
                          D_800ED570.vy) >>
                             4);

            if ((ang + delta) < g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A -= delta;
            }
            else
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A = ang;
            }

            Math_RotMatrixZ(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A - 0x400, &coord[8].coord);
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

s32 func_800DB81C(s_SubCharacter* chara) // 0x800DB81C
{
    s_RayData ray;
    VECTOR3   dir;

    dir.vy = Q12_MULT(D_800AD4C8[63].field_0, Math_Cos(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A));
    dir.vx = Q12_MULT(Q12_MULT(D_800AD4C8[63].field_0, Math_Sin(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A)), Math_Sin(chara->rotation_24.vy));
    dir.vz = Q12_MULT(Q12_MULT(D_800AD4C8[63].field_0, Math_Sin(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_11A)), Math_Cos(chara->rotation_24.vy));

    if (func_8006DA08(&ray, &D_800ED570, &dir, chara) && ray.chara_10 == NULL)
    {
        return 1;
    }

    return 0;
}

s32 func_800DB930(void) // 0x800DB930
{
    VECTOR3 sp10;
    s32     min;
    s32     found;
    s32     i;
    s32     px;
    s32     pz;
    s32     len;

    min   = 0x14000;
    found = -1;

    for (i = 0; i < 10; i++)
    {
        sp10.vx = D_800CB2B4[i] + 0x14000;
        sp10.vy = -0x800;
        sp10.vz = D_800CB2DC[i] + 0x64000;

        if (func_800DB6FC(&sp10))
        {
            continue;
        }

        len = SquareRoot0(SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vx - sp10.vx) >> 4) +
                          SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vz - sp10.vz) >> 4))
              << 4;

        if (len < min)
        {
            min   = len;
            found = i;
        }
    }

    return found;
}

s32 func_800DBA48(s_SubCharacter* chara) // 0x800DBA48
{
    VECTOR sp10;
    s32    len;
    s32    var_s0;
    s32    count;
    s32    min;
    s32    found;
    s32    max;
    s32    i;
    s32    temp;

    temp = SquareRoot0(SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vx - 0x14000) >> 4) +
                       SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vz - 0x64000) >> 4))
           << 4;

    if (temp > 0x6800)
    {
        var_s0 = 0;
    }
    else if (temp > 0x3333)
    {
        var_s0 = 1;
    }
    else
    {
        var_s0 = 2;
    }

    min = 0x14000;
    len = 0x14000;

    found = -1;
    max   = g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110;
    count = (3 - var_s0) * 4;

    for (i = 0; i < count; i++)
    {
        switch (var_s0)
        {
            case 0:
                sp10.vx = D_800CB304[i][0] + 0x14000;
                sp10.vy = 0;
                sp10.vz = D_800CB304[i][1] + 0x64000;
                break;

            case 1:
                sp10.vx = D_800CB364[i][0] + 0x14000;
                sp10.vy = 0;
                sp10.vz = D_800CB364[i][1] + 0x64000;
                break;

            case 2:
                sp10.vx = D_800CB3A4[i][0] + 0x14000;
                sp10.vy = 0;
                sp10.vz = D_800CB3A4[i][1] + 0x64000;
                break;
        }

        if (!func_800DB6FC(&sp10))
        {
            len = SquareRoot0(SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vx - sp10.vx) >> 4) +
                              SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vz - sp10.vz) >> 4))
                  << 4;

            if (len < min)
            {
                found = i;
            }
        }
    }

    if (found == -1)
    {
        return 0;
    }

    if (len < max)
    {
        switch (var_s0)
        {
            case 0:
                sp10.vx = D_800CB304[found][0] + 0x14000;
                sp10.vz = D_800CB304[found][1] + 0x64000;
                break;

            case 1:
                sp10.vx = D_800CB364[found][0] + 0x14000;
                sp10.vz = D_800CB364[found][1] + 0x64000;
                break;

            case 2:
                sp10.vx = D_800CB3A4[found][0] + 0x14000;
                sp10.vz = D_800CB3A4[found][1] + 0x64000;
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
    s32 min;
    s32 i;
    s32 len;
    s32 px;
    s32 pz;

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110 > 0x2000)
    {
        return 0;
    }

    min = 0x6000;

    for (i = 0; i < 10; i++)
    {
        px = chara->position_18.vx - 0x14000;
        pz = chara->position_18.vz - 0x64000;

        len = SquareRoot0(SQUARE((D_800CB250[i] - px) >> 4) + SQUARE((D_800CB278[i] - pz) >> 4)) << 4;

        if (min > len)
        {
            min = len;
        }
    }

    return min < g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_110;
}

void func_800DBE5C(s_SubCharacter* chara)
{
    s16 ang;
    s32 var_s1;
    s16 turn;

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_E8 == 1)
    {
        var_s1 = (Rng_Rand16() & 1) * 2048 - 1024;
    }
    else
    {
        var_s1 = (Rng_Rand16() & 1) * 2048 - 512;
    }

    turn = FP_ANGLE_NORM_U(var_s1 + ratan2((chara->position_18.vx - 0x14000) >> 4, (chara->position_18.vz - 0x64000) >> 4) + Q12(1.0f));

    if (chara->model_0.anim_4.status_0 == 3)
    {
        if (chara->model_0.anim_4.keyframeIdx_8 >= 0 && chara->model_0.anim_4.keyframeIdx_8 <= 23)
        {
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_126 = D_800CB1D8[chara->model_0.anim_4.keyframeIdx_8];
        }
    }

    Math_ShortestAngleGet(chara->rotation_24.vy, turn, &ang);

    if (ABS(ang) < 64)
    {
        chara->rotation_24.vy = turn;
    }
    else if (ang > 0)
    {
        chara->rotation_24.vy += 64;
    }
    else
    {
        chara->rotation_24.vy -= 64;
    }

    chara->rotation_24.vy += (Rng_Rand16() % 128) - 64;

    g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_10C += g_DeltaTime0;

    if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_10C > 0x5000)
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
    s32       turn;

    switch ((u8)g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116)
    {
        case 2:
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 += (g_DeltaTime0 << 5) / 136;
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 =
                CLAMP(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106, 0, 1536);

            turn = chara->rotation_24.vy;
            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 < 1024)
            {
                turn += (g_DeltaTime0 * 32) / 136;
            }
            chara->rotation_24.vy = turn;

            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 == 1536)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 = 0;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = 0;
            }
            break;

        case 3:
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 -= (g_DeltaTime0 * 32) / 136;
            g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 =
                CLAMP(g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106, -1536, 0);

            turn = chara->rotation_24.vy;
            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 > -1024)
            {
                turn -= (g_DeltaTime0 * 32) / 136;
            }
            chara->rotation_24.vy = turn;

            if (g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 == -1536)
            {
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 = 0;
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
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_116 = (Rng_Rand16() & 1) + 2;
                g_SysWork.npcs_1A0[0].properties_E4.monsterCybil.field_106 = 0;
            }
            break;
    }
}
