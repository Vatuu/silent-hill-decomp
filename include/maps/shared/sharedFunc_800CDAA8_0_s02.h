#include "bodyprog/player_logic.h"

// TODO:
// - Rename `sharedFunc_800CDAA8_0_s02` -> `sharedFunc_800D0E34_0_s00`, sharedData_800D32A0_0_s02` -> `sharedData_800E39DC_0_s00`

// Keyframe indexes used for each state
// Maps can override these by defining the keyframe beforehand, only indexes that change in certain maps are included here.
// (most likely whatever tool they used to create the `g_MapOverlayHeader.animInfos_34` data also output a header defining these for each map)
#ifndef KEYFRAME_PlayerState_Unk59
#define KEYFRAME_PlayerState_Unk59 927
#endif

#ifndef KEYFRAME_PlayerState_Unk60
#define KEYFRAME_PlayerState_Unk60 942
#endif

#ifndef KEYFRAME_PlayerState_Unk69
#define KEYFRAME_PlayerState_Unk69 984
#endif

#ifndef KEYFRAME_PlayerState_Unk87
#define KEYFRAME_PlayerState_Unk87 873
#endif

#ifndef KEYFRAME_PlayerState_Unk88
#define KEYFRAME_PlayerState_Unk88 910
#endif

#ifndef KEYFRAME_PlayerState_Unk111
#define KEYFRAME_PlayerState_Unk111 678
#endif

#ifndef KEYFRAME_PlayerState_Unk113
#define KEYFRAME_PlayerState_Unk113 1084
#endif

#ifndef KEYFRAME_PlayerState_Unk114
#define KEYFRAME_PlayerState_Unk114 932
#endif

#ifndef KEYFRAME_PlayerState_Unk117
#define KEYFRAME_PlayerState_Unk117 723
#endif

#ifndef KEYFRAME_PlayerState_Unk122
#define KEYFRAME_PlayerState_Unk122 961
#endif

#ifndef KEYFRAME_PlayerState_Unk123
#define KEYFRAME_PlayerState_Unk123 693
#endif

#ifndef KEYFRAME_PlayerState_Unk146
#define KEYFRAME_PlayerState_Unk146 1074
#endif

#ifndef KEYFRAME_PlayerState_Unk147
#define KEYFRAME_PlayerState_Unk147 1108
#endif

#ifndef KEYFRAME_PlayerState_Unk153
#define KEYFRAME_PlayerState_Unk153 1036
#endif

#ifndef KEYFRAME_PlayerState_Unk162
#define KEYFRAME_PlayerState_Unk162 1237
#endif

#ifndef KEYFRAME_PlayerState_Unk167
#define KEYFRAME_PlayerState_Unk167 1070
#endif

// All maps have 52
#ifndef HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk52
#endif

// Very similar to `func_80071968_Switch1`
static inline void sharedFunc_800CDAA8_0_s02_Switch(void)
{
    if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_Unk52)
    {
        func_8003D01C();
        switch (g_SysWork.playerCombat_38.weaponAttack_F)
        {
            case 0:
            case 1:
            case 2:
            case 4:
            case 5:
            case 6:
            case 7:
            case 10:
            case 11:
            case 12:
            case 14:
            case 15:
            case 16:
            case 17:
            case 20:
            case 21:
            case 22:
            case 24:
            case 25:
            case 26:
            case 27:
                WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(2, 1));
                break;

            case 32:
            case 34:
            case 35:
                WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(3, 1));
                break;

            case 33:
                WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(4, 1));
                break;
        }
    }
    else
    {
        func_8003D03C();
        WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(1, 1));
    }
}

// Slight change in PlayerState_Unk55 version
static inline void sharedFunc_800CDAA8_0_s02_Switch_Unk85(s_PlayerExtra* extra)
{
    if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_Unk52)
    {
        func_8003D01C();

        switch (g_SysWork.playerCombat_38.weaponAttack_F)
        {
            case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_SteelPipe,    AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_RockDrill,    AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Hammer,       AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Chainsaw,     AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Katana,       AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Axe,          AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_SteelPipe,    AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_RockDrill,    AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Hammer,       AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Chainsaw,     AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Katana,       AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_Axe,          AttackInputType_Hold):
            case WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_SteelPipe,    AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_RockDrill,    AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Hammer,       AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Chainsaw,     AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Katana,       AttackInputType_Multitap):
            case WEAPON_ATTACK(EquippedWeaponId_Axe,          AttackInputType_Multitap):
                WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(2, 1));
                break;

            case WEAPON_ATTACK(EquippedWeaponId_Handgun,      AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_Shotgun,      AttackInputType_Tap):
            case WEAPON_ATTACK(EquippedWeaponId_HyperBlaster, AttackInputType_Tap):
                WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(3, 1));
                break;

            case WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Tap):
                WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(4, 1));
                break;
        }
    }
    else
    {
        func_8003D03C();

        if (extra->model_0.anim_4.keyframeIdx_8 >= 958)
        {
            WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(5, 1));
        }
        else
        {
            WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(1, 1));
        }
    }
}

void sharedFunc_800CDAA8_0_s02(s_SubCharacter* playerChara, s_PlayerExtra* extra, GsCOORDINATE2* coord)
{
    s_Collision coll;
    e_SfxId     sfx;
    s8          pitch0;
    s8          pitch1;
    s32         newMoveSpeed;
    q19_12      headingAngle;
    u16         keyframeIdxMax;
    s32         keyframeIdx;

    headingAngle = Q12_ANGLE(0.0f);
    keyframeIdx  = 0;

    sharedData_800D32A0_0_s02 = 0;
    sharedData_800E39D8_0_s00 = 0;

    playerChara->properties_E4.player.field_10C                            >>= 1;
    g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 = 0;

    func_8004C564(0, -1);

    playerChara->properties_E4.player.afkTimer_E8        = Q12(0.0f);
    playerChara->properties_E4.player.exhaustionTimer_FC = Q12(0.0f);

    switch (g_SysWork.playerWork_4C.extra_128.state_1C)
    {
#ifdef HAS_PlayerState_Unk51
        case PlayerState_Unk51:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(0.0f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            sharedData_800E39D8_0_s00 = 0;
            sharedData_800D32A0_0_s02 = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;

            func_8007FC48(playerChara, extra, 400);

            if (extra->model_0.controlState_2 == ModelState_Uninitialized)
            {
                extra->model_0.controlState_2++;
            }

            switch (D_800C457C)
            {
                case 3:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk56);
                    break;

                case 4:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk57);
                    break;
            }

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(0.0f);
            break;
#endif

#ifdef HAS_PlayerState_Unk131
        case PlayerState_Unk131:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(0.0f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            sharedData_800E39D8_0_s00 = 0;
            sharedData_800D32A0_0_s02 = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;
            func_8007FB94(playerChara, extra, 400);

            if (extra->model_0.controlState_2 == ModelState_Uninitialized)
            {
                extra->model_0.controlState_2++;
            }

            switch (D_800C457C)
            {
                case 3:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk56);
                    break;

                case 4:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk57);
                    break;
            }

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(0.0f);
            break;
#endif

#ifdef HAS_PlayerState_Unk52
        case PlayerState_Unk52:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(0.0f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            sharedData_800E39D8_0_s00 = 0;
            sharedData_800D32A0_0_s02 = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;

            Model_AnimStatusSet(&extra->model_0, HarryAnim_Idle, false);
            Model_AnimStatusSet(&playerChara->model_0, HarryAnim_Idle, false);

            if (extra->model_0.controlState_2 == ModelState_Uninitialized)
            {
                extra->model_0.controlState_2++;
            }

            switch (D_800C457C)
            {
                case 3:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk56);
                    break;

                case 4:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk57);
                    break;
            }

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(0.0f);
            break;
#endif

#ifdef HAS_PlayerState_Unk53
        case PlayerState_Unk53:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 > Q12(1.4f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(1.4f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(1.4f);
                }
            }
            else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(1.4f))
            {
                if (playerChara->model_0.anim_4.keyframeIdx_8 >= 2)
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                }

                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = CLAMP(g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126,
                                                                                                Q12(0.0f),
                                                                                                Q12(1.4f));
            }

            sharedData_800D32A0_0_s02 = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;

            Model_AnimStatusSet(&extra->model_0, HarryAnim_WalkForward, false);
            Model_AnimStatusSet(&playerChara->model_0, HarryAnim_WalkForward, false);

            if (extra->model_0.controlState_2 == ModelState_Uninitialized)
            {
                extra->model_0.controlState_2++;
            }

            switch (D_800C457C)
            {
                case 0:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk54);
                    break;

                case 3:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk56);
                    break;

                case 4:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk57);
                    break;
            }

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(0.0f);
            break;
#endif

#ifdef HAS_PlayerState_Unk54
        case PlayerState_Unk54:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 > Q12(4.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(4.0f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(4.0f);
                }
            }
            else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(4.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.75f));
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 =
                    CLAMP(g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126, Q12(0.0f), Q12(4.0f));
            }

            sharedData_800D32A0_0_s02 = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;

            Model_AnimStatusSet(&extra->model_0, HarryAnim_RunForward, false);
            Model_AnimStatusSet(&playerChara->model_0, HarryAnim_RunForward, false);

            if (extra->model_0.controlState_2 == ModelState_Uninitialized)
            {
                extra->model_0.controlState_2++;
            }

            switch (D_800C457C)
            {
                case 1:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk53);
                    break;

                case 3:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk56);
                    break;

                case 4:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk57);
                    break;
            }

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = 0;
            break;
#endif

#ifdef HAS_PlayerState_Unk55
        case PlayerState_Unk55:
            sharedData_800D32A0_0_s02 = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;

            Model_AnimStatusSet(&extra->model_0, HarryAnim_WalkBackward, false);
            Model_AnimStatusSet(&playerChara->model_0, HarryAnim_WalkBackward, false);

            if (extra->model_0.controlState_2 == ModelState_Uninitialized)
            {
                extra->model_0.controlState_2++;
            }

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = Q12_ANGLE(180.0f);
            break;
#endif

#ifdef HAS_PlayerState_Unk56
        case PlayerState_Unk56:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(0.0f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            sharedData_800D32A0_0_s02 = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;
            sharedData_800E39D8_0_s00 = g_DeltaTime * 7;

            Model_AnimStatusSet(&extra->model_0, HarryAnim_TurnRight, false);
            Model_AnimStatusSet(&playerChara->model_0, HarryAnim_TurnRight, false);

            if (extra->model_0.controlState_2 == ModelState_Uninitialized)
            {
                extra->model_0.controlState_2++;
            }

            switch (D_800C457C)
            {
                case 0:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk54);
                    break;

                case 1:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk53);
                    break;

                case 4:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk57);
                    break;
            }

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = 0;

            g_Player_FlexRotationY = Q12_ANGLE(-28.2f);
            break;
#endif

#ifdef HAS_PlayerState_Unk57
        case PlayerState_Unk57:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(0.0f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                }
            }

            sharedData_800D32A0_0_s02 = g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;
            sharedData_800E39D8_0_s00 = g_DeltaTime * -7;

            Model_AnimStatusSet(&extra->model_0, HarryAnim_TurnLeft, false);
            Model_AnimStatusSet(&playerChara->model_0, HarryAnim_TurnLeft, false);

            if (extra->model_0.controlState_2 == ModelState_Uninitialized)
            {
                extra->model_0.controlState_2++;
            }

            switch (D_800C457C)
            {
                case 0:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk54);
                    break;

                case 1:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk53);
                    break;

                case 3:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk56);
                    break;
            }

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124 = 0;

            g_Player_FlexRotationY = Q12_ANGLE(28.2f);
            break;
#endif

#ifdef HAS_PlayerState_Unk59
        case PlayerState_Unk59:
            func_8007FB94(playerChara, extra, 0x12C);
            keyframeIdx = KEYFRAME_PlayerState_Unk59;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk60
        case PlayerState_Unk60:
            func_8007FB94(playerChara, extra, 0x12D);
            keyframeIdx = KEYFRAME_PlayerState_Unk60;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk66
        case PlayerState_Unk66:
            func_8007FB94(playerChara, extra, 0x138);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk70
        case PlayerState_Unk70:
            func_8007FB94(playerChara, extra, 342);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
#ifdef MAP0_S01
            func_8003D03C();
#endif
            break;
#endif

#ifdef HAS_PlayerState_Unk71
        case PlayerState_Unk71:
            func_8007FC48(playerChara, extra, 0x157);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk73
        case PlayerState_Unk73:
            func_8007FB94(playerChara, extra, 0x155);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk74
        case PlayerState_Unk74:
            func_8007FB94(playerChara, extra, 0x15E);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk83
        case PlayerState_Unk83:
            func_8007FB94(playerChara, extra, 0x163);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk84
        case PlayerState_Unk84:
            keyframeIdxMax = 983; // TODO: Should probably be `keyframeIdx` instead like other cases, but doesn't match with that?
            func_8007FB94(playerChara, extra, 0x164);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);

            if (sharedFunc_800D2DAC_0_s00() == 1 && g_SysWork.enablePlayerMatchAnim_2358 == false)
            {
                g_SysWork.enablePlayerMatchAnim_2358 = true;
                func_8005DC1C(Sfx_Unk1356, &playerChara->position_18, Q8_CLAMPED(0.5f), 0);
            }

            if (playerChara->model_0.anim_4.keyframeIdx_8 >= keyframeIdxMax)
            {
                func_8003D03C();
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk85
        case PlayerState_Unk85:
            func_8007FB94(playerChara, extra, 0x169);
#ifdef MAP1_S03
            func_8003D03C();
            WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(1, 1));
#else
            keyframeIdx = 949;
            sharedFunc_800CDAA8_0_s02_Switch_Unk85(extra);
#endif
            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk86
        case PlayerState_Unk86:
            func_8007FB94(playerChara, extra, 0x16A);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk87
        case PlayerState_Unk87:
            func_8007FC48(playerChara, extra, 0x166);
            keyframeIdx = KEYFRAME_PlayerState_Unk87;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk88
        case PlayerState_Unk88:
            func_8007FC48(playerChara, extra, 0x167);
            keyframeIdx = KEYFRAME_PlayerState_Unk88;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk94
        case PlayerState_Unk94:
            func_8007FB94(playerChara, extra, 0x164);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk95
        case PlayerState_Unk95:
            func_8007FB94(playerChara, extra, 0x170);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk97
        case PlayerState_Unk97:
            if (playerChara->model_0.anim_4.keyframeIdx_8 >= 1065)
            {
                Savegame_EventFlagSet(EventFlag_99);
            }

            if (playerChara->model_0.anim_4.keyframeIdx_8 < 1090)
            {
                func_8003D03C();
            }
            else
            {
                func_8003D01C();
            }

            func_8007FB94(playerChara, extra, 0x172);
            keyframeIdx = 1062;
            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk98
        case PlayerState_Unk98:
            func_8007FB94(playerChara, extra, 0x173);
            keyframeIdx = 1062;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            if (playerChara->model_0.anim_4.keyframeIdx_8 >= 1147)
            {
                Savegame_EventFlagClear(EventFlag_99);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk99
        case PlayerState_Unk99:
            func_8007FB94(playerChara, extra, 0x175);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk100
        case PlayerState_Unk100:
            func_8007FB94(playerChara, extra, 0x174);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif
#if defined(HAS_PlayerState_Unk69) || defined(HAS_PlayerState_Unk105)
        case PlayerState_Unk69:
        case PlayerState_Unk105:
            func_8007FC48(playerChara, extra, 0x14B);

            keyframeIdx = KEYFRAME_PlayerState_Unk69;
            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk72
        case PlayerState_Unk72:
            func_8007FB94(playerChara, extra, 0x154);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk81
        case PlayerState_Unk81:
            keyframeIdx = 998;
            if (playerChara->model_0.anim_4.keyframeIdx_8 >= (keyframeIdx + 3))
            {
                if (playerChara->model_0.anim_4.keyframeIdx_8 <= (keyframeIdx + 24))
                {
                    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 > Q12(0.2875f))
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                        if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(0.2875f))
                        {
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.2875f);
                        }
                    }
                    else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(0.2875f))
                    {
                        if (playerChara->model_0.anim_4.keyframeIdx_8 > 998)
                        {
                            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                        }
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = CLAMP(g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126,
                                                                                                        Q12(0.0f),
                                                                                                        Q12(0.2875f));
                    }
                }
                else if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 != Q12(0.0f))
                {
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                    if (g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 < Q12(0.0f))
                    {
                        g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                    }
                }
            }

            sharedData_800D32A0_0_s02 = (s32)g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126;
            func_8007FC48(playerChara, extra, 0x168);
            headingAngle = Q12_ANGLE(180.0f);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk106
        case PlayerState_Unk106:
            func_8007FB94(playerChara, extra, 0x17E);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk107
        case PlayerState_Unk107:
            func_8007FB94(playerChara, extra, 0x180);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk108
        case PlayerState_Unk108:
            func_8007FB94(playerChara, extra, 0x17F);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk109
        case PlayerState_Unk109:
            func_8007FB94(playerChara, extra, 0x181);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk114
        case PlayerState_Unk114:
            func_8007FB94(playerChara, extra, 0x186);
            keyframeIdx = KEYFRAME_PlayerState_Unk114;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk115
        case PlayerState_Unk115:
            func_8007FB94(playerChara, extra, 0x187);
            keyframeIdx = 699;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk116
        case PlayerState_Unk116:
            func_8007FC48(playerChara, extra, 0x188);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk118
        case PlayerState_Unk118:
            func_8007FB94(playerChara, extra, 0x18A);
            keyframeIdx = 750;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk119
        case PlayerState_Unk119:
            func_8007FB94(playerChara, extra, 0x18B);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk120
        case PlayerState_Unk120:
            func_8007FB94(playerChara, extra, 0x18C);
            keyframeIdx = 779;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk121
        case PlayerState_Unk121:
            func_8007FB94(playerChara, extra, 0x18D);
            keyframeIdx = 807;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk122
        case PlayerState_Unk122:
#ifdef MAP1_S03
            func_8007FB94(playerChara, extra, 0x18E);
#else
            func_8007FC48(playerChara, extra, 0x18E);
#endif
            keyframeIdx = KEYFRAME_PlayerState_Unk122;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk124
        case PlayerState_Unk124:
            func_8007FC48(playerChara, extra, 0x191);
            keyframeIdx = 846;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk125
        case PlayerState_Unk125:
            func_8007FC48(playerChara, extra, 0x192);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk126
        case PlayerState_Unk126:
            func_8007FC48(playerChara, extra, 0x193);
            keyframeIdx = 980;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk127
        case PlayerState_Unk127:
            func_8007FC48(playerChara, extra, 0x194);
            keyframeIdx = 1002;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk130
        case PlayerState_Unk130:
            func_8007FC48(playerChara, extra, 0x197);
            keyframeIdx = 967;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk132
        case PlayerState_Unk132:
            func_8007FB94(playerChara, extra, 343);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk76
        case PlayerState_Unk76:
            func_8007FC48(playerChara, extra, 351);
            keyframeIdx = 827;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            if (playerChara->model_0.anim_4.keyframeIdx_8 > (keyframeIdx + 33) &&
                playerChara->model_0.anim_4.keyframeIdx_8 < (keyframeIdx + 46))
            {
                func_8003D03C();
            }
            else
            {
                func_8003D01C();
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk77
        case PlayerState_Unk77:
            func_8007FC48(playerChara, extra, 352);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk78
        case PlayerState_Unk78:
            func_8007FC48(playerChara, extra, 353);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk89
        case PlayerState_Unk89:
            func_8007FC48(playerChara, extra, 363);
            keyframeIdx = 948;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk90
        case PlayerState_Unk90:
            func_8007FC48(playerChara, extra, 344);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            func_8003D03C();
            break;
#endif

#ifdef HAS_PlayerState_Unk91
        case PlayerState_Unk91:
            func_8007FB94(playerChara, extra, 365);
            keyframeIdx = 1027;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk92
        case PlayerState_Unk92:
            func_8007FB94(playerChara, extra, 366);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk93
        case PlayerState_Unk93:
            func_8007FB94(playerChara, extra, 367);
            keyframeIdx = 1055;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk110
        case PlayerState_Unk110:
            func_8007FB94(playerChara, extra, 386);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk111
        case PlayerState_Unk111:
            func_8007FB94(playerChara, extra, 0x183);
            keyframeIdx = KEYFRAME_PlayerState_Unk111;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk113
        case PlayerState_Unk113:
            func_8007FB94(playerChara, extra, 0x185);
            keyframeIdx = KEYFRAME_PlayerState_Unk113;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk117
        case PlayerState_Unk117:
            func_8007FC48(playerChara, extra, 0x189);
            keyframeIdx = KEYFRAME_PlayerState_Unk117;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk123
        case PlayerState_Unk123:
            func_8007FB94(playerChara, extra, 0x18F);
            keyframeIdx = KEYFRAME_PlayerState_Unk123;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk128
        case PlayerState_Unk128:
            func_8007FC48(playerChara, extra, 0x195);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk129
        case PlayerState_Unk129:
            func_8007FC48(playerChara, extra, 0x196);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk133
        case PlayerState_Unk133:
            func_8007FB94(playerChara, extra, 0x198);
            keyframeIdx = 1039;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk134
        case PlayerState_Unk134:
            func_8007FB94(playerChara, extra, 0x199);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();

            if (playerChara->model_0.anim_4.status_0 & 1 << 0)
            {
                s_SubCharacter* new_var; // @hack Permuter find, maybe an inline here?
                extra->model_0.anim_4.time_4       = Q12(g_MapOverlayHeader.animInfos_34[playerChara->model_0.anim_4.status_0 - 76].startKeyframeIdx_C) + (new_var = g_SysWork.npcs_1A0)[0].model_0.anim_4.time_4 - Q12(261.0f);
                playerChara->model_0.anim_4.time_4 = Q12(g_MapOverlayHeader.animInfos_34[playerChara->model_0.anim_4.status_0 - 76].startKeyframeIdx_C) + new_var[0].model_0.anim_4.time_4 - Q12(261.0f);

                if (D_800C4606)
                {
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                    D_800C4606 = 0;
                }

                playerChara->model_0.anim_4.keyframeIdx_8 = FP_FROM(playerChara->model_0.anim_4.time_4, Q12_SHIFT);
                extra->model_0.anim_4.keyframeIdx_8       = FP_FROM(extra->model_0.anim_4.time_4, Q12_SHIFT);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk135
        case PlayerState_Unk135:
            func_8007FC48(playerChara, extra, 0x19A);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk136
        case PlayerState_Unk136:
            func_8007FB94(playerChara, extra, 0x19B);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk137
        case PlayerState_Unk137:
            func_8007FB94(playerChara, extra, 0x19C);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk138
        case PlayerState_Unk138:
            func_8007FB94(playerChara, extra, 0x19D);
            keyframeIdx = 728;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk139
        case PlayerState_Unk139:
            func_8007FC48(playerChara, extra, 0x19E);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk140
        case PlayerState_Unk140:
            func_8007FC48(playerChara, extra, 0x19F);
            keyframeIdx = 982;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk141
        case PlayerState_Unk141:
            func_8007FB94(playerChara, extra, 0x1A0);
            keyframeIdx = 1066;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk142
        case PlayerState_Unk142:
            func_8007FB94(playerChara, extra, 0x1A1);
            keyframeIdx = 1016;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk143
        case PlayerState_Unk143:
            func_8007FB94(playerChara, extra, 0x1A2);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }


            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk144
        case PlayerState_Unk144:
            func_8007FC48(playerChara, extra, 0x1A3);
            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk145
        case PlayerState_Unk145:
            func_8007FC48(playerChara, extra, 0x1A4);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk146
        case PlayerState_Unk146:
            func_8007FB94(playerChara, extra, 0x1A5);
            keyframeIdx = KEYFRAME_PlayerState_Unk146;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk147
        case PlayerState_Unk147:
            func_8007FC48(playerChara, extra, 0x1A6);
            keyframeIdx = KEYFRAME_PlayerState_Unk147;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk148
        case PlayerState_Unk148:
            func_8007FB94(playerChara, extra, 0x1A7);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk149
        case PlayerState_Unk149:
            func_8007FB94(playerChara, extra, 0x1A8);
            keyframeIdx = 728;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk150
        case PlayerState_Unk150:
            func_8007FC48(playerChara, extra, 0x1A9);
            keyframeIdx = 793;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk151
        case PlayerState_Unk151:
            keyframeIdx = 1106;

            if (playerChara->model_0.anim_4.keyframeIdx_8 == (keyframeIdx + 11) ||
                playerChara->model_0.anim_4.keyframeIdx_8 == (keyframeIdx + 7))
            {
                if (!(g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk6))
                {
                    func_8005F6B0(&g_SysWork.npcs_1A0[1], &(VECTOR3){ Q12(14.94f), Q12(-0.05f), Q12(102.0f) }, 3, 3);
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk6;
                }
            }

            if (playerChara->model_0.anim_4.keyframeIdx_8 == (keyframeIdx + 8) ||
                playerChara->model_0.anim_4.keyframeIdx_8 == (keyframeIdx + 19))
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;
            }

            func_8007FB94(playerChara, extra, 0x1AA);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk152
        case PlayerState_Unk152:
            func_8007FC48(playerChara, extra, 0x1AB);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk153
        case PlayerState_Unk153:
            func_8007FB94(playerChara, extra, 0x1AC);
            keyframeIdx = KEYFRAME_PlayerState_Unk153;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk154
        case PlayerState_Unk154:
            keyframeIdx = 1006;

            if (playerChara->model_0.anim_4.keyframeIdx_8 > keyframeIdx + 72)
            {
                func_8003D03C();
            }
            else
            {
                func_8003D01C();
            }

            func_8007FB94(playerChara, extra, 0x1AD);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk155
        case PlayerState_Unk155:
            func_8007FB94(playerChara, extra, 0x1AE);
            keyframeIdx = 678;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk156
        case PlayerState_Unk156:
            func_8007FB94(playerChara, extra, 0x1AF);
            keyframeIdx = 733;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk157
        case PlayerState_Unk157:
            func_8007FB94(playerChara, extra, 0x1B0);
            keyframeIdx = 793;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk158
        case PlayerState_Unk158:
            func_8007FB94(playerChara, extra, 0x1B1);
            keyframeIdx = 834;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk159
        case PlayerState_Unk159:
            func_8007FC48(playerChara, extra, 0x1B2);
            keyframeIdx = 170;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk160
        case PlayerState_Unk160:
            func_8007FC48(playerChara, extra, 0x1B3);
            keyframeIdx = 1126;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk161
        case PlayerState_Unk161:
            func_8007FC48(playerChara, extra, 0x1B4);
            keyframeIdx = 1207;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            if (playerChara->model_0.anim_4.keyframeIdx_8 == 1236)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk189);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk169
        case PlayerState_Unk169:
            keyframeIdx = 864;

            if (playerChara->model_0.anim_4.keyframeIdx_8 <= keyframeIdx + 19)
            {
                func_8003D01C();
            }
            else
            {
                func_8003D03C();
            }

            func_8007FB94(playerChara, extra, 0x1BC);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk175
        case PlayerState_Unk175:
            func_8007FB94(playerChara, extra, 0x1C2);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk186
        case PlayerState_Unk186:
            func_8007FB94(playerChara, extra, 0x1CD);
#ifdef MAP5_S02
            keyframeIdx = 889;
#endif
            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk164
        case PlayerState_Unk164:
            func_8007FC48(playerChara, extra, 0x1B7);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk165
        case PlayerState_Unk165:
            keyframeIdx = 953;

            if (playerChara->model_0.anim_4.keyframeIdx_8 == keyframeIdx + 5)
            {
                if (!(g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Unk6))
                {
                    func_8006342C(0x20, 0x340, playerChara->rotation_24.vy, coord);
                    func_8005F6B0(&g_SysWork.npcs_1A0[1], &(VECTOR3){ Q12(140.39f), Q12(-0.55f), Q12(22.76f) }, 3, 3);
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk6;
                }
            }

            if (playerChara->model_0.anim_4.keyframeIdx_8 == keyframeIdx + 22)
            {
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;
            }

            func_8007FC48(playerChara, extra, 0x1B8);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk166
        case PlayerState_Unk166:
            func_8007FB94(playerChara, extra, 0x1B9);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk187
        case PlayerState_Unk187:
            func_8007FB94(playerChara, extra, 0x1CE);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk189
        case PlayerState_Unk189:
            func_8007FC48(playerChara, extra, 0x1D0);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk162
        case PlayerState_Unk162:
            func_8007FB94(playerChara, extra, 0x1B5);
            keyframeIdx = KEYFRAME_PlayerState_Unk162;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk163
        case PlayerState_Unk163:
            func_8007FC48(playerChara, extra, 0x1B6);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk167
        case PlayerState_Unk167:
            func_8007FB94(playerChara, extra, 0x1BA);
            keyframeIdx = KEYFRAME_PlayerState_Unk167;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk168
        case PlayerState_Unk168:
            func_8007FB94(playerChara, extra, 0x1BB);
            keyframeIdx = 1363;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk171
        case PlayerState_Unk171:
            func_8007FB94(playerChara, extra, 0x1BE);
            keyframeIdx = 937;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk172
        case PlayerState_Unk172:
            func_8007FC48(playerChara, extra, 0x1BF);
            keyframeIdx = 961;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk173
        case PlayerState_Unk173:
            func_8007FC48(playerChara, extra, 0x1C0);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk174
        case PlayerState_Unk174:
            func_8007FC48(playerChara, extra, 0x1C1);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk176
        case PlayerState_Unk176:
            keyframeIdx = 1087;
            func_8003D01C();
            func_8007FB94(playerChara, extra, 0x1C3);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk177
        case PlayerState_Unk177:
            func_8003D01C();
            func_8007FB94(playerChara, extra, 0x1C4);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk184
        case PlayerState_Unk184:
            func_8003D01C();
            func_8007FB94(playerChara, extra, 0x1CB);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk178
        case PlayerState_Unk178:
            func_8003D01C();
            func_8007FB94(playerChara, extra, 0x1C5);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk179
        case PlayerState_Unk179:
            keyframeIdx = 1198;

            if (playerChara->model_0.anim_4.keyframeIdx_8 >= keyframeIdx + 23)
            {
                func_8003D01C();
            }
            else
            {
                func_8003D03C();
            }

            func_8007FB94(playerChara, extra, 0x1C6);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk180
        case PlayerState_Unk180:
            func_8003D01C();
            func_8007FB94(playerChara, extra, 0x1C7);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk181
        case PlayerState_Unk181:
            func_8003D01C();
            func_8007FC48(playerChara, extra, 0x1C8);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk182
        case PlayerState_Unk182:
            func_8007FC48(playerChara, extra, 0x1C9);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk183
        case PlayerState_Unk183:
            func_8007FC48(playerChara, extra, 0x1CA);
            keyframeIdx = 1358;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk185
        case PlayerState_Unk185:
            func_8007FC48(playerChara, extra, 0x1CC);
            keyframeIdx = 1363;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk170
        case PlayerState_Unk170:
            func_8007FB94(playerChara, extra, 0x1BD);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            keyframeIdx = 1411;

            if (playerChara->model_0.anim_4.keyframeIdx_8 < 1417)
            {
                func_8003D01C();
            }
            else
            {
                func_8003D03C();
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk188
        case PlayerState_Unk188:
            func_8007FB94(playerChara, extra, 0x1CF);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif
    }

    Collision_Get(&coll, playerChara->position_18.vx, playerChara->position_18.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);

    switch (g_SysWork.playerWork_4C.extra_128.state_1C)
    {
#ifdef HAS_PlayerState_Unk52
        case PlayerState_Unk52:
            if (g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_Moving)
            {
                if (playerChara->model_0.anim_4.status_0 == ANIM_STATUS(HarryAnim_Idle, false))
                {
                    func_8005DD44(sfx, &playerChara->position_18, 64, pitch0);
                    playerChara->properties_E4.player.field_10C                 = pitch0 + 16;
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
                }
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk53
        case PlayerState_Unk53:
            Player_FootstepSfxPlay(5, playerChara, 18, 6, sfx, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk54
        case PlayerState_Unk54:
            if (Player_FootstepSfxPlay(7, playerChara, 31, 41, sfx, pitch1) != false)
            {
                playerChara->properties_E4.player.runTimer_F8++;
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk56
        case PlayerState_Unk56:
            Player_FootstepSfxPlay(27, playerChara, 204, 200, sfx, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk57
        case PlayerState_Unk57:
            Player_FootstepSfxPlay(25, playerChara, 187, 191, sfx, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk59
        case PlayerState_Unk59:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 5, 0, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk60
        case PlayerState_Unk60:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 7, 0, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk76
        case PlayerState_Unk76:
            if (ANIM_STATUS_IS_ACTIVE(playerChara->model_0.anim_4.status_0))
            {
                if (playerChara->model_0.anim_4.keyframeIdx_8 < (keyframeIdx + 31))
                {
                    func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 1, Sfx_Unk1386);
                }
                else
                {
                    func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 33, Sfx_Unk1369);
                }
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk81
        case PlayerState_Unk81:
            if ((keyframeIdx + 19) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 31, keyframeIdx + 19, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 31, keyframeIdx + 40, sfx, pitch0);
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk87
        case PlayerState_Unk87:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 35, keyframeIdx + 17, Sfx_Unk1423, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk88
        case PlayerState_Unk88:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 15, keyframeIdx + 31, Sfx_Unk1423, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk91
        case PlayerState_Unk91:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 6, keyframeIdx + 6, sfx, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk92
        case PlayerState_Unk92:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 9, keyframeIdx + 9, sfx, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk93
        case PlayerState_Unk93:
            if (ANIM_STATUS_IS_ACTIVE(playerChara->model_0.anim_4.status_0))
            {
                func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 6, Sfx_Unk1385);
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 18, 0, sfx, pitch0);
                g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk89
        case PlayerState_Unk89:
            if ((keyframeIdx + 5) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 5, keyframeIdx + 16, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 74, keyframeIdx + 77, sfx, pitch0);
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk97
        case PlayerState_Unk97:
            if ((keyframeIdx + 4) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 10, keyframeIdx + 4, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 10, keyframeIdx + 13, sfx, pitch0);
            }

            func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 26, Sfx_Unk1456);
            break;
#endif

#ifdef HAS_PlayerState_Unk105
        case PlayerState_Unk105:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 5, keyframeIdx + 12, sfx, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk113
        case PlayerState_Unk113:
            if ((keyframeIdx + 5) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 14, keyframeIdx + 5, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 14, keyframeIdx + 21, sfx, pitch0);
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk111
        case PlayerState_Unk111:
            if (ANIM_STATUS_IS_ACTIVE(playerChara->model_0.anim_4.status_0))
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 11, keyframeIdx + 21, sfx, pitch0);
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk114
        case PlayerState_Unk114:
            if ((keyframeIdx + 8) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 13, keyframeIdx + 8, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 13, keyframeIdx + 18, sfx, pitch0);
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk115
        case PlayerState_Unk115:
            if ((keyframeIdx + 9) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 9, keyframeIdx + 33, sfx, pitch0);
            }
            else
            {
                if (keyframeIdx + 39 >= playerChara->model_0.anim_4.keyframeIdx_8)
                {
                    Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 39, keyframeIdx + 33, sfx, pitch0);
                }
                else
                {
                    Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 46, keyframeIdx + 42, sfx, pitch0);
                }
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk117
        case PlayerState_Unk117:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 34, 0, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk118
        case PlayerState_Unk118:
            if ((keyframeIdx + 8) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 12, keyframeIdx + 8, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 12, keyframeIdx + 16, sfx, pitch0);
            }

            if (ANIM_STATUS_IS_ACTIVE(playerChara->model_0.anim_4.status_0))
            {
                func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 9, Sfx_Unk1539);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk120
        case PlayerState_Unk120:
            if ((keyframeIdx + 5) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 17, keyframeIdx + 5, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 17, keyframeIdx + 25, sfx, pitch0);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk121
        case PlayerState_Unk121:
            if ((keyframeIdx + 5) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 5, keyframeIdx + 12, sfx, pitch0);
            }
            else if ((keyframeIdx + 23) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 23, keyframeIdx + 12, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 5, keyframeIdx + 29, sfx, pitch0);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk122
        case PlayerState_Unk122:
            if ((keyframeIdx + 9) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 14, keyframeIdx + 9, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 14, keyframeIdx + 19, sfx, pitch0);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk123
        case PlayerState_Unk123:
            if ((keyframeIdx + 9) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 14, keyframeIdx + 9, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 14, keyframeIdx + 19, sfx, pitch0);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk124
        case PlayerState_Unk124:
            if (Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, 80, 87, sfx, pitch1))
            {
                playerChara->properties_E4.player.runTimer_F8++;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk126
        case PlayerState_Unk126:
            if ((keyframeIdx + 9) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 16, keyframeIdx + 9, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 16, keyframeIdx + 22, sfx, pitch0);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk127
        case PlayerState_Unk127:
            if ((keyframeIdx + 5) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 17, keyframeIdx + 5, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 17, keyframeIdx + 26, sfx, pitch0);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk133
        case PlayerState_Unk133:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 5, keyframeIdx + 5, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk138
        case PlayerState_Unk138:
            if (ANIM_STATUS_IS_ACTIVE(playerChara->model_0.anim_4.status_0))
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 18, keyframeIdx + 14, sfx, pitch0);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk140
        case PlayerState_Unk140:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 25, keyframeIdx + 25, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk141
        case PlayerState_Unk141:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 46, keyframeIdx + 5, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk142
        case PlayerState_Unk142:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 10, keyframeIdx + 10, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk130
        case PlayerState_Unk130:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 14, keyframeIdx + 14, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk146
        case PlayerState_Unk146:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 16, keyframeIdx + 10, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk147
        case PlayerState_Unk147:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 11, keyframeIdx + 11, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk149
        case PlayerState_Unk149:
            if (playerChara->model_0.anim_4.keyframeIdx_8 < (keyframeIdx + 2))
            {
                func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx, Sfx_Unk1626);
            }
            else
            {
                if (playerChara->model_0.anim_4.keyframeIdx_8 < (keyframeIdx + 8))
                {
                    if (func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 6, Q12(0.4f)) != false)
                    {
                        func_800892DC(8, 0x30); // Hex?
                    }
                }
                else
                {
                    if (playerChara->model_0.anim_4.keyframeIdx_8 < (keyframeIdx + 41))
                    {
                        func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 3, Sfx_Unk1627);
                    }
                    else
                    {
                        func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 42, Sfx_Unk1628);
                    }
                }
            }

            if ((keyframeIdx + 43) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 55, keyframeIdx + 43, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 55, keyframeIdx + 59, sfx, pitch0);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk150
        case PlayerState_Unk150:
            if (func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 21, Q12(0.4f)) != false)
            {
                func_800892DC(8, 0x30); // Hex?
            }

            if (keyframeIdx + 8 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 8, keyframeIdx + 11, sfx, pitch0);
            }
            else if ((keyframeIdx + 14) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 14, keyframeIdx + 11, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 8, keyframeIdx + 16, sfx, pitch0);
            }

            break;
#endif

#ifdef HAS_PlayerState_Unk151
        case PlayerState_Unk151:
            if (ANIM_STATUS_IS_ACTIVE(playerChara->model_0.anim_4.status_0))
            {
                if ((keyframeIdx + 7) >= playerChara->model_0.anim_4.keyframeIdx_8)
                {
                    func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 7, Sfx_Unk1619);
                }
                else
                {
                    func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 11, Sfx_Unk1619);
                }

                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 16, keyframeIdx + 16, sfx, pitch0);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk153
        case PlayerState_Unk153:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 5, keyframeIdx + 12, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk154
        case PlayerState_Unk154:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 7, keyframeIdx + 21, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk155
        case PlayerState_Unk155:
            if (playerChara->model_0.anim_4.keyframeIdx_8 < 34)
            {
                if (keyframeIdx + 10 >= playerChara->model_0.anim_4.keyframeIdx_8)
                {
                    Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 10, keyframeIdx + 16, sfx, pitch0);
                }
                else
                {
                    if (keyframeIdx + 21 >= playerChara->model_0.anim_4.keyframeIdx_8)
                    {
                        Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 21, keyframeIdx + 16, sfx, pitch0);
                    }
                    else
                    {
                        Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 28, keyframeIdx + 25, sfx, pitch0);
                    }
                }
            }
            else if ((keyframeIdx + 16) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 34, keyframeIdx + 38, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 42, keyframeIdx + 46, sfx, pitch0);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk156
        case PlayerState_Unk156:
            if (playerChara->model_0.anim_4.keyframeIdx_8 < 59)
            {
                if ((keyframeIdx + 9) >= playerChara->model_0.anim_4.keyframeIdx_8)
                {
                    Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 9, keyframeIdx + 22, sfx, pitch0);
                }
                else
                {
                    if ((keyframeIdx + 30) >= playerChara->model_0.anim_4.keyframeIdx_8)
                    {
                        Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 30, keyframeIdx + 22, sfx, pitch0);
                    }
                    else
                    {
                        Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 52, keyframeIdx + 42, sfx, pitch0);
                    }
                }
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 59, keyframeIdx + 59, sfx, pitch1);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk157
        case PlayerState_Unk157:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 33, keyframeIdx + 25, sfx, pitch1);
            break;
#endif

#ifdef HAS_PlayerState_Unk158
        case PlayerState_Unk158:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 12, keyframeIdx + 5, sfx, pitch1);
            break;
#endif

#ifdef HAS_PlayerState_Unk159
        case PlayerState_Unk159:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 11, 0, sfx, pitch1);
            break;
#endif

#ifdef HAS_PlayerState_Unk160
        case PlayerState_Unk160:
            if ((keyframeIdx + 33) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 42, keyframeIdx + 33, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 42, keyframeIdx + 55, sfx, pitch0);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk161
        case PlayerState_Unk161:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 24, keyframeIdx + 22, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk175
        case PlayerState_Unk175:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, 18, 6, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk186
        case PlayerState_Unk186:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, 0, keyframeIdx + 12, sfx, pitch0);
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk162
        case PlayerState_Unk162:
            if (ANIM_STATUS_IS_ACTIVE(playerChara->model_0.anim_4.status_0))
            {
#ifdef MAP7_S03
                func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 60, Sfx_Unk1671);
#else
                func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 60, Sfx_Unk1623);
#endif
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk163
        case PlayerState_Unk163:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 6, 0, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk165
        case PlayerState_Unk165:
            func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 5, Sfx_Unk1283);
            break;
#endif

#ifdef HAS_PlayerState_Unk167
        case PlayerState_Unk167:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 10, 0, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk168
        case PlayerState_Unk168:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 38, keyframeIdx + 22, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk172
        case PlayerState_Unk172:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 29, 0, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk176
        case PlayerState_Unk176:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 8, keyframeIdx + 19, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk179
        case PlayerState_Unk179:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 8, keyframeIdx + 44, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk183
        case PlayerState_Unk183:
            if ((keyframeIdx + 11) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 28, keyframeIdx + 11, sfx, pitch0);
            }
            else
            {
                Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 28, keyframeIdx + 55, sfx, pitch0);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk171
        case PlayerState_Unk171:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 9, keyframeIdx + 14, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk185
        case PlayerState_Unk185:
            Player_FootstepSfxPlay(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 38, keyframeIdx + 22, sfx, pitch0);
            break;
#endif

#ifdef HAS_PlayerState_Unk170
        case PlayerState_Unk170:
            func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 7, Sfx_Unk1629);
            break;
#endif
        default:
            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
    }

    newMoveSpeed = sharedData_800D32A0_0_s02;

    playerChara->rotation_24.vy  = Q12_ANGLE_NORM_U((playerChara->rotation_24.vy + (sharedData_800E39D8_0_s00 >> 4)) + Q12_ANGLE(360.0f));
    playerChara->headingAngle_3C = Q12_ANGLE_NORM_U(playerChara->rotation_24.vy + headingAngle);
    playerChara->moveSpeed_38    = newMoveSpeed;
    playerChara->fallSpeed_34   += g_GravitySpeed;

    coord->flg = false;
    Math_RotMatrixZxyNegGte(&playerChara->rotation_24, &coord->coord);
}
