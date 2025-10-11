#include "bodyprog/player_logic.h"

// Do all maps have 52?
#define HAS_PlayerState_Unk52

#if defined(MAP0_S00)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk53  // 0x35
#define HAS_PlayerState_Unk54  // 0x36
#define HAS_PlayerState_Unk55  // 0x37
#define HAS_PlayerState_Unk56  // 0x38
#define HAS_PlayerState_Unk57  // 0x39
#define HAS_PlayerState_Unk74  // 0x4A
#define HAS_PlayerState_Unk84  // 0x54
#define HAS_PlayerState_Unk131 // 0x83
#endif

#if defined(MAP0_S01)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk53  // 0x35
#define HAS_PlayerState_Unk70  // 0x46
#define HAS_PlayerState_Unk71  // 0x47
#define HAS_PlayerState_Unk76  // 0x4C
#define HAS_PlayerState_Unk77  // 0x4D
#define HAS_PlayerState_Unk78  // 0x4E
#define HAS_PlayerState_Unk89  // 0x59
#define HAS_PlayerState_Unk90  // 0x5A
#define HAS_PlayerState_Unk91  // 0x5B
#define HAS_PlayerState_Unk92  // 0x5C
#define HAS_PlayerState_Unk93  // 0x5D
#define HAS_PlayerState_Unk110 // 0x6E
#define HAS_PlayerState_Unk131 // 0x83
#define HAS_PlayerState_Unk132 // 0x84
#endif

#if defined(MAP1_S00)
#define HAS_PlayerState_Unk52 // 0x34
#define HAS_PlayerState_Unk87 // 0x57
#define HAS_PlayerState_Unk88 // 0x58
#endif

#if defined(MAP1_S00) || defined(MAP6_S03)
#define HAS_PlayerState_Unk52 // 0x34
#define HAS_PlayerState_Unk87 // 0x57
#define HAS_PlayerState_Unk88 // 0x58
#endif

// TODO: Rename to sharedFunc_800D0E34_0_s00

void sharedFunc_800CDAA8_0_s02(s_SubCharacter* playerChara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord)
{
    s_Collision coll;
    s32         sfx;
    s8          pitch;
    s8          sp2D;
    s32         temp_v0_16;
    s32         newMoveSpeed;
    q19_12      headingAngle;
    u16         maxKeyFrame;
    s32         keyFrameIdx;

    headingAngle = FP_ANGLE(0.0f);
    keyFrameIdx  = 0;

    sharedData_800D32A0_0_s02 = 0;
    sharedData_800E39D8_0_s00 = 0;

    playerChara->properties_E4.player.field_10C >>= 1;
    g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 = 0;

    func_8004C564(0, -1);

    playerChara->properties_E4.player.afkTimer_E8        = Q12(0.0f);
    playerChara->properties_E4.player.exhaustionTimer_FC = Q12(0.0f);

    switch (g_SysWork.player_4C.extra_128.state_1C)
    {
#ifdef HAS_PlayerState_Unk51
        case PlayerState_Unk51:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != Q12(0.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS) * 2;
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(0.0f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = Q12(0.0f);
                }
            }

            sharedData_800E39D8_0_s00 = 0;
            sharedData_800D32A0_0_s02 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;

            func_8007FC48(playerChara, extra, 0x190);

            if (extra->model_0.state_2 == 0)
            {
                extra->model_0.state_2++;
            }

            switch (D_800C457C)
            {
                case 3:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk56);
                    break;
                case 4:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk57);
                    break;
                default:
                    break;
            }

            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);
            break;
#endif
#ifdef HAS_PlayerState_Unk131
        case PlayerState_Unk131:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS) * 2;
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < 0)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
                }
            }

            sharedData_800E39D8_0_s00 = 0;
            sharedData_800D32A0_0_s02 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;
            func_8007FB94(playerChara, extra, 0x190);

            if (extra->model_0.state_2 == 0)
            {
                extra->model_0.state_2++;
            }

            switch (D_800C457C)
            {
                case 3:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk56);
                    break;
                case 4:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk57);
                    break;
                default:
                    break;
            }

            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);
            break;
#endif
#ifdef HAS_PlayerState_Unk52
        case PlayerState_Unk52:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != Q12(0.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS) * 2;
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(0.0f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = Q12(0.0f);
                }
            }

            sharedData_800E39D8_0_s00 = 0;
            sharedData_800D32A0_0_s02 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;

            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Idle, false);
                extra->model_0.stateStep_3++;
            }

            if (playerChara->model_0.stateStep_3 == 0)
            {
                playerChara->model_0.anim_4.status_0 = ANIM_STATUS(HarryAnim_Idle, false);
                playerChara->model_0.stateStep_3++;
            }

            if (extra->model_0.state_2 == 0)
            {
                extra->model_0.state_2++;
            }

            switch (D_800C457C)
            {
                case 3:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk56);
                    break;
                case 4:
                    Player_ExtraStateSet(playerChara, extra, PlayerState_Unk57);
                    break;
                default:
                    break;
            }

            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);
            break;
#endif
#ifdef HAS_PlayerState_Unk87
        case PlayerState_Unk87:
            func_8007FC48(playerChara, extra, 0x166);
            keyFrameIdx = 873;
            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            if (g_SysWork.player_4C.extra_128.state_1C == 52)
            {
                func_8003D01C();
                switch (g_SysWork.playerCombatInfo_38.weaponAttack_F)
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
                        func_8003DD80(1, 18);
                        break;
                    case 32:
                    case 34:
                    case 35:
                        func_8003DD80(1, 19);
                        break;
                    case 33:
                        func_8003DD80(1, 20);
                        break;
                }
            }
            else
            {
                func_8003D03C();
                func_8003DD80(1, 17);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk88
        case PlayerState_Unk88:
            func_8007FC48(playerChara, extra, 0x167);
            keyFrameIdx = 910;
            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            if (g_SysWork.player_4C.extra_128.state_1C == 0x34)
            {
                func_8003D01C();
                switch (g_SysWork.playerCombatInfo_38.weaponAttack_F)
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
                        func_8003DD80(1, 18);
                        break;
                    case 32:
                    case 34:
                    case 35:
                        func_8003DD80(1, 19);
                        break;
                    case 33:
                        func_8003DD80(1, 20);
                        break;
                }
            }
            else
            {
                func_8003D03C();
                func_8003DD80(1, 17);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk53
        case PlayerState_Unk53:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 > Q12(1.4f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS) * 2;
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(1.4f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = Q12(1.4f);
                }
            }
            else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(1.4f))
            {
                if (playerChara->model_0.anim_4.keyframeIdx_8 >= 2)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 += (g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS;
                }
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 =
                    CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126, 0, Q12(1.4f));
            }

            sharedData_800D32A0_0_s02 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;

            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = 4;
                extra->model_0.stateStep_3++;
            }

            if (playerChara->model_0.stateStep_3 == 0)
            {
                playerChara->model_0.anim_4.status_0 = 4;
                playerChara->model_0.stateStep_3++;
            }

            if (extra->model_0.state_2 == 0)
            {
                extra->model_0.state_2++;
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
                default:
                    break;
            }

            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);
            break;
#endif
#ifdef HAS_PlayerState_Unk54
        case PlayerState_Unk54:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 > Q12(4.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS;
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(4.0f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = Q12(4.0f);
                }
            }
            else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(4.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 += (g_DeltaTime0 * Q12(0.75f)) / TIME_STEP_30_FPS;
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 =
                    CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126, 0, Q12(4.0f));
            }

            sharedData_800D32A0_0_s02 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = 6;
                extra->model_0.stateStep_3++;
            }

            if (playerChara->model_0.stateStep_3 == 0)
            {
                playerChara->model_0.anim_4.status_0 = 6;
                playerChara->model_0.stateStep_3++;
            }

            if (extra->model_0.state_2 == 0)
            {
                extra->model_0.state_2++;
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
                default:
                    break;
            }

            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = 0;
            break;
#endif
#ifdef HAS_PlayerState_Unk55
        case PlayerState_Unk55:
            sharedData_800D32A0_0_s02 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;

            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = 8;
                extra->model_0.stateStep_3    += 1;
            }

            if (playerChara->model_0.stateStep_3 == 0)
            {
                playerChara->model_0.anim_4.status_0 = 8;
                playerChara->model_0.stateStep_3    += 1;
            }

            if (extra->model_0.state_2 == 0)
            {
                extra->model_0.state_2++;
            }

            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = FP_ANGLE(180.0f);
            break;
#endif
#ifdef HAS_PlayerState_Unk56
        case PlayerState_Unk56:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != Q12(0.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS) * 2;
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(0.0f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = Q12(0.0f);
                }
            }

            sharedData_800D32A0_0_s02 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;
            sharedData_800E39D8_0_s00 = g_DeltaTime0 * 7;

            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = 0x1A;
                extra->model_0.stateStep_3    += 1;
            }

            if (playerChara->model_0.stateStep_3 == 0)
            {
                playerChara->model_0.anim_4.status_0 = 0x1A;
                playerChara->model_0.stateStep_3    += 1;
            }

            if (extra->model_0.state_2 == 0)
            {
                extra->model_0.state_2++;
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
                default:
                    break;
            }

            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = 0;

            g_Player_FlexRotationY = FP_ANGLE(-28.2f);
            break;
#endif
#ifdef HAS_PlayerState_Unk57
        case PlayerState_Unk57:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != Q12(0.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS) * 2;
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(0.0f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = Q12(0.0f);
                }
            }

            sharedData_800D32A0_0_s02 = g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;
            sharedData_800E39D8_0_s00 = g_DeltaTime0 * -7;

            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.status_0 = 0x18;
                extra->model_0.stateStep_3    += 1;
            }

            if (playerChara->model_0.stateStep_3 == 0)
            {
                playerChara->model_0.anim_4.status_0 = 0x18;
                playerChara->model_0.stateStep_3    += 1;
            }

            if (extra->model_0.state_2 == 0)
            {
                extra->model_0.state_2++;
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

            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = 0;

            g_Player_FlexRotationY = FP_ANGLE(28.2f);
            break;
#endif
#ifdef HAS_PlayerState_Unk70
        case PlayerState_Unk70:
            func_8007FB94(playerChara, extra, 0x156);
            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            func_8003D03C();
            break;
#endif
#ifdef HAS_PlayerState_Unk71
        case PlayerState_Unk71:
            func_8007FC48(playerChara, extra, 0x157);

            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            break;
#endif
#ifdef HAS_PlayerState_Unk132
        case PlayerState_Unk132:
            func_8007FB94(playerChara, extra, 0x157);

            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            break;
#endif
#ifdef HAS_PlayerState_Unk74
        case PlayerState_Unk74:
            func_8007FB94(playerChara, extra, 0x15E);

            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            break;
#endif
#ifdef HAS_PlayerState_Unk76
        case PlayerState_Unk76:
            func_8007FC48(playerChara, extra, 0x15F);

            keyFrameIdx = 827;
            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            if (playerChara->model_0.anim_4.keyframeIdx_8 > keyFrameIdx + 33 && playerChara->model_0.anim_4.keyframeIdx_8 < keyFrameIdx + 46)
            {
                func_8003D03C();
            }
            else
            {
                func_8003D01C();
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk84
        case PlayerState_Unk84:
            maxKeyFrame = 983; // might be `keyFrameIdx` instead?
            func_8007FB94(playerChara, extra, 0x164);
            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;

            if (sharedFunc_800D2DAC_0_s00() == 1 && g_SysWork.field_2358 == 0)
            {
                g_SysWork.field_2358 = 1;
                func_8005DC1C(Sfx_Unk1356, &playerChara->position_18, 128, 0);
            }

            if (playerChara->model_0.anim_4.keyframeIdx_8 >= maxKeyFrame)
            {
                func_8003D03C();
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk77
        case PlayerState_Unk77:
            func_8007FC48(playerChara, extra, 0x160);

            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk78
        case PlayerState_Unk78:
            func_8007FC48(playerChara, extra, 0x161);

            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk89
        case PlayerState_Unk89:
            func_8007FC48(playerChara, extra, 0x16B);
            keyFrameIdx = 948;
            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk90
        case PlayerState_Unk90:
            func_8007FC48(playerChara, extra, 0x158);
            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            func_8003D03C();
            break;
#endif
#ifdef HAS_PlayerState_Unk91
        case PlayerState_Unk91:
            func_8007FB94(playerChara, extra, 0x16D);
            keyFrameIdx = 1027;
            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk92
        case PlayerState_Unk92:
            func_8007FB94(playerChara, extra, 0x16E);
            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk93
        case PlayerState_Unk93:
            func_8007FB94(playerChara, extra, 0x16F);
            keyFrameIdx = 1055;
            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk110
        case PlayerState_Unk110:
            func_8007FB94(playerChara, extra, 0x182);
            if (D_800C4606 != 0)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif
    }

    Collision_Get(&coll, playerChara->position_18.vx, playerChara->position_18.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch, &sp2D);

    switch (g_SysWork.player_4C.extra_128.state_1C)
    {
#ifdef HAS_PlayerState_Unk52
        case PlayerState_Unk52:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Moving)
            {
                if (playerChara->model_0.anim_4.status_0 == 0x34)
                {
                    func_8005DD44(sfx, &playerChara->position_18, 64, pitch);
                    playerChara->properties_E4.player.field_10C                 = pitch + 16;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
                }
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk53
        case PlayerState_Unk53:
            func_800713E8(5, playerChara, 18, 6, sfx, pitch);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;
#endif
#ifdef HAS_PlayerState_Unk54
        case PlayerState_Unk54:
            if (func_800713E8(7, playerChara, 31, 41, sfx, sp2D) != false)
            {
                playerChara->properties_E4.player.runTimer_F8++;
            }
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;
#endif
#ifdef HAS_PlayerState_Unk56
        case PlayerState_Unk56:
            func_800713E8(27, playerChara, 204, 200, sfx, pitch);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif
#ifdef HAS_PlayerState_Unk57
        case PlayerState_Unk57:
            func_800713E8(25, playerChara, 187, 191, sfx, pitch);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif
#ifdef HAS_PlayerState_Unk76
        case PlayerState_Unk76:
            if (playerChara->model_0.anim_4.status_0 & 1)
            {
                if (playerChara->model_0.anim_4.keyframeIdx_8 < (keyFrameIdx + 31))
                {
                    func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 1, Sfx_Unk1386);
                }
                else
                {
                    func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 33, Sfx_Unk1369);
                }
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk91
        case PlayerState_Unk91:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 6, keyFrameIdx + 6, sfx, pitch);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif
#ifdef HAS_PlayerState_Unk92
        case PlayerState_Unk92:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 9, keyFrameIdx + 9, sfx, pitch);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif
#ifdef HAS_PlayerState_Unk93
        case PlayerState_Unk93:
            if (playerChara->model_0.anim_4.status_0 & 1)
            {
                func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 6, Sfx_Unk1385);
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 18, 0, sfx, pitch);
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk89
        case PlayerState_Unk89:
            if (keyFrameIdx + 5 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 5, keyFrameIdx + 16, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 74, keyFrameIdx + 77, sfx, pitch);
            }
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif
#ifdef HAS_PlayerState_Unk87
        case PlayerState_Unk87:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 35, keyFrameIdx + 17, Sfx_Unk1423, pitch);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif
#ifdef HAS_PlayerState_Unk88
        case PlayerState_Unk88:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 15, keyFrameIdx + 31, Sfx_Unk1423, pitch);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif
        default:
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
    }

    newMoveSpeed = sharedData_800D32A0_0_s02;

    playerChara->rotation_24.vy  = FP_ANGLE_NORM_U((playerChara->rotation_24.vy + (sharedData_800E39D8_0_s00 >> 4)) + FP_ANGLE(360.0f));
    playerChara->headingAngle_3C = FP_ANGLE_NORM_U(playerChara->rotation_24.vy + headingAngle);
    playerChara->moveSpeed_38    = newMoveSpeed;
    playerChara->field_34       += g_DeltaTime2;

    coord->flg = false;
    Math_MatrixRotate1(&playerChara->rotation_24, &coord->coord);
}
