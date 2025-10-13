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

#if defined(MAP1_S00) || defined(MAP6_S03)
#define HAS_PlayerState_Unk52 // 0x34
#define HAS_PlayerState_Unk87 // 0x57
#define HAS_PlayerState_Unk88 // 0x58
#endif

#if defined(MAP7_S01)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk53  // 0x35
#define HAS_PlayerState_Unk54  // 0x36
#define HAS_PlayerState_Unk55  // 0x37
#define HAS_PlayerState_Unk56  // 0x38
#define HAS_PlayerState_Unk57  // 0x39
#define HAS_PlayerState_Unk59  // 0x3B
#define HAS_PlayerState_Unk60  // 0x3C
#define HAS_PlayerState_Unk72  // 0x48
#define HAS_PlayerState_Unk131 // 0x83
#define HAS_PlayerState_Unk145 // 0x91
#define HAS_PlayerState_Unk148 // 0x94
#define HAS_PlayerState_Unk155 // 0x9B
#define HAS_PlayerState_Unk156 // 0x9C
#define HAS_PlayerState_Unk157 // 0x9D
#define HAS_PlayerState_Unk158 // 0x9E
#define HAS_PlayerState_Unk167 // 0xA7
#endif

#if defined(MAP7_S02)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk131 // 0x83
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk59  // 0x3B
#define HAS_PlayerState_Unk60  // 0x3C
#define HAS_PlayerState_Unk72  // 0x48
#define HAS_PlayerState_Unk143 // 0x8F // todo
#define HAS_PlayerState_Unk144 // 0x90 // todo
#define HAS_PlayerState_Unk146 // 0x92 // todo
#define HAS_PlayerState_Unk147 // 0x93 // todo
#define HAS_PlayerState_Unk148 // 0x94
#define HAS_PlayerState_Unk155 // 0x9B
#define HAS_PlayerState_Unk156 // 0x9C
#define HAS_PlayerState_Unk157 // 0x9D
#define HAS_PlayerState_Unk158 // 0x9E
#endif

#if defined(MAP3_S05)
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk53  // 0x35
#define HAS_PlayerState_Unk54  // 0x36
#define HAS_PlayerState_Unk55  // 0x37
#define HAS_PlayerState_Unk56  // 0x38
#define HAS_PlayerState_Unk57  // 0x39
#define HAS_PlayerState_Unk59  // 0x3B
#define HAS_PlayerState_Unk60  // 0x3C
#define HAS_PlayerState_Unk69  // 0x45
#define HAS_PlayerState_Unk105 // 0x69
#define HAS_PlayerState_Unk81  // 0x51
#define HAS_PlayerState_Unk116 // 0x74
#define HAS_PlayerState_Unk141 // 0x8D
#endif

#if defined(MAP6_S04)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk131 // 0x83
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk53  // 0x35
#define HAS_PlayerState_Unk70  // 0x46
#define HAS_PlayerState_Unk113 // 0x71
#define HAS_PlayerState_Unk123 // 0x7B
#define HAS_PlayerState_Unk149 // 0x95
#define HAS_PlayerState_Unk150 // 0x96
#define HAS_PlayerState_Unk151 // 0x97
#define HAS_PlayerState_Unk152 // 0x98
#define HAS_PlayerState_Unk160 // 0xA0
#define HAS_PlayerState_Unk161 // 0xA1
#define HAS_PlayerState_Unk189 // 0xBD
#define HAS_PlayerState_Unk162 // 0xA2
#define HAS_PlayerState_Unk163 // 0xA3
#define HAS_PlayerState_Unk167 // 0xA7
#define HAS_PlayerState_Unk168 // 0xA8
#define HAS_PlayerState_Unk185 // 0xB9
#define HAS_PlayerState_Unk170 // 0xAA
#define HAS_PlayerState_Unk188 // 0xBC
#endif

// Very similar to `func_80071968_Switch1`
static inline void sharedFunc_800CDAA8_0_s02_Switch()
{
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
}

// TODO: Rename to sharedFunc_800D0E34_0_s00
void sharedFunc_800CDAA8_0_s02(s_SubCharacter* playerChara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord)
{
#ifdef HAS_PlayerState_Unk151
    const static VECTOR D_800CA618 = { Q12(14.94f), Q12(-0.05f), Q12(102.0f) };
#endif
    s_Collision coll;
    s32         sfx;
    s8          pitch;
    s8          sp2D;
    s32         newMoveSpeed;
    q19_12      headingAngle;
    u16         keyframeIdxMax;
    s32         keyframeIdx;

    headingAngle = FP_ANGLE(0.0f);
    keyframeIdx  = 0;

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
            }

            if (D_800C4606)
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
            }

            if (D_800C4606)
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
            }

            if (D_800C4606)
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
            keyframeIdx = 873;

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
            keyframeIdx = 910;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk53
        case PlayerState_Unk53:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 > Q12(1.4f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS) * 2; // TODO: There's a macro.
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(1.4f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = Q12(1.4f);
                }
            }
            else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(1.4f))
            {
                if (playerChara->model_0.anim_4.keyframeIdx_8 >= 2)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 += (g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS; // TODO: There's a macro.
                }

                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126,
                                                                                                Q12(0.0f),
                                                                                                Q12(1.4f));
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
            }

            if (D_800C4606)
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
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= (g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS; // TODO: There's a macro.
                if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(4.0f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = Q12(4.0f);
                }
            }
            else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(4.0f))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 += (g_DeltaTime0 * Q12(0.75f)) / TIME_STEP_30_FPS; // TODO: There's a macro.
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126,
                                                                                                Q12(0.0f),
                                                                                                Q12(4.0f));
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
            }

            if (D_800C4606)
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

            if (D_800C4606)
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
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS) * 2; // TODO: There's a macro.
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
            }

            if (D_800C4606)
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
                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS) * 2; // TODO: There's a macro.
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

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            headingAngle = g_SysWork.player_4C.chara_0.properties_E4.player.headingAngle_124 = 0;

            g_Player_FlexRotationY = FP_ANGLE(28.2f);
            break;
#endif

#ifdef HAS_PlayerState_Unk59
        case PlayerState_Unk59:
            func_8007FB94(playerChara, extra, 0x12C);
#if defined(MAP3_S05)
            keyframeIdx = 957;
#elif defined(MAP7_S02)
            keyframeIdx = 862;
#else
            keyframeIdx = 927;
#endif
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
#if defined(MAP3_S05)
            keyframeIdx = 972;
#elif defined(MAP7_S02)
            keyframeIdx = 877;
#else
            keyframeIdx = 942;
#endif
            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#if defined(HAS_PlayerState_Unk69) || defined(HAS_PlayerState_Unk105)
        case PlayerState_Unk69:
        case PlayerState_Unk105:
            func_8007FC48(playerChara, extra, 0x14B);
            keyframeIdx = 984;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif

#ifdef HAS_PlayerState_Unk81
        case PlayerState_Unk81:
            keyframeIdx = 998;
            if (playerChara->model_0.anim_4.keyframeIdx_8 >= keyframeIdx + 3)
            {
                if (playerChara->model_0.anim_4.keyframeIdx_8 <= keyframeIdx + 24)
                {
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 > Q12(0.2875f))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS) * 2;
                        if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(0.2875f))
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = Q12(0.2875f);
                        }
                    }
                    else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(0.2875f))
                    {
                        if (playerChara->model_0.anim_4.keyframeIdx_8 > 998)
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 += (g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS;
                        }

                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126,
                                                                                                        Q12(0.0f),
                                                                                                        Q12(0.2875f));
                    }
                }
                else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != Q12(0.0f))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS) * 2;
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < Q12(0.0f))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = Q12(0.0f);
                    }
                }
            }

            sharedData_800D32A0_0_s02 = (s32)g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126;

            func_8007FC48(playerChara, extra, 0x168);

            headingAngle = FP_ANGLE(180.0f);

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

#ifdef HAS_PlayerState_Unk146
        case PlayerState_Unk146:
            func_8007FB94(playerChara, extra, 0x1A5);
            keyframeIdx = 1074;

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
            keyframeIdx = 1108;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
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

#ifdef HAS_PlayerState_Unk70
        case PlayerState_Unk70:
            func_8007FB94(playerChara, extra, 0x156);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

#if !defined(MAP6_S04)
            func_8003D03C();
#endif
            break;
#endif

#ifdef HAS_PlayerState_Unk113
        case PlayerState_Unk113:
            func_8007FB94(playerChara, extra, 0x185);
            keyframeIdx = 1084;

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
            keyframeIdx = 693;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
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
                if (!(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & 0x40))
                {
                    func_8005F6B0(&g_SysWork.npcs_1A0[1], &D_800CA618, 3, 3);
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= 0x40;
                }
            }

            if (playerChara->model_0.anim_4.keyframeIdx_8 == (keyframeIdx + 8) ||
                playerChara->model_0.anim_4.keyframeIdx_8 == (keyframeIdx + 19))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~0x40;
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
            keyframeIdx = 1237;

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

#if defined(MAP6_S04)
            keyframeIdx = 1347;
#else
            keyframeIdx = 1070;
#endif

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

#ifdef HAS_PlayerState_Unk132
        case PlayerState_Unk132:
            func_8007FB94(playerChara, extra, 0x157);

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

#ifdef HAS_PlayerState_Unk76
        case PlayerState_Unk76:
            func_8007FC48(playerChara, extra, 0x15F);
            keyframeIdx = 827;

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }

            if (playerChara->model_0.anim_4.keyframeIdx_8 > keyframeIdx + 33 && playerChara->model_0.anim_4.keyframeIdx_8 < keyframeIdx + 46)
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
            keyframeIdxMax = 983; // Might be `keyframeIdx` instead?
            func_8007FB94(playerChara, extra, 0x164);
            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;

            if (sharedFunc_800D2DAC_0_s00() == 1 && g_SysWork.field_2358 == 0)
            {
                g_SysWork.field_2358 = 1;
                func_8005DC1C(Sfx_Unk1356, &playerChara->position_18, 128, 0);
            }

            if (playerChara->model_0.anim_4.keyframeIdx_8 >= keyframeIdxMax)
            {
                func_8003D03C();
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk77
        case PlayerState_Unk77:
            func_8007FC48(playerChara, extra, 0x160);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk78
        case PlayerState_Unk78:
            func_8007FC48(playerChara, extra, 0x161);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk89
        case PlayerState_Unk89:
            func_8007FC48(playerChara, extra, 0x16B);
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
            func_8007FC48(playerChara, extra, 0x158);

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
            func_8007FB94(playerChara, extra, 0x16D);
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
            func_8007FB94(playerChara, extra, 0x16E);

            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk93
        case PlayerState_Unk93:
            func_8007FB94(playerChara, extra, 0x16F);
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
            func_8007FB94(playerChara, extra, 0x182);

            if (D_800C4606)
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

#ifdef HAS_PlayerState_Unk59
        case PlayerState_Unk59:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 5, 0, sfx, pitch);
            break;
#endif

#ifdef HAS_PlayerState_Unk60
        case PlayerState_Unk60:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 7, 0, sfx, pitch);
            break;
#endif

#ifdef HAS_PlayerState_Unk146
        case PlayerState_Unk146:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 16, keyframeIdx + 10, sfx, pitch);
            break;
#endif

#ifdef HAS_PlayerState_Unk147
        case PlayerState_Unk147:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 11, keyframeIdx + 11, sfx, pitch);
            break;
#endif

#ifdef HAS_PlayerState_Unk81
        case PlayerState_Unk81:
            if ((keyframeIdx + 19) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 31, keyframeIdx + 19, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 31, keyframeIdx + 40, sfx, pitch);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk105
        case PlayerState_Unk105:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 5, keyframeIdx + 12, sfx, pitch);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk141
        case PlayerState_Unk141:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 46, keyframeIdx + 5, sfx, pitch);
            break;
#endif

#ifdef HAS_PlayerState_Unk155
        case PlayerState_Unk155:
            if (playerChara->model_0.anim_4.keyframeIdx_8 < 34)
            {
                if ((keyframeIdx + 10) >= playerChara->model_0.anim_4.keyframeIdx_8)
                {
                    func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 10, keyframeIdx + 16, sfx, pitch);
                }
                else
                {
                    if ((keyframeIdx + 21) >= playerChara->model_0.anim_4.keyframeIdx_8)
                    {
                        func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 21, keyframeIdx + 16, sfx, pitch);
                    }
                    else
                    {
                        func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 28, keyframeIdx + 25, sfx, pitch);
                    }
                }
            }
            else if ((keyframeIdx + 16) >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 34, keyframeIdx + 38, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 42, keyframeIdx + 46, sfx, pitch);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk156
        case PlayerState_Unk156:
            if (playerChara->model_0.anim_4.keyframeIdx_8 < 59)
            {
                if ((keyframeIdx + 9) >= playerChara->model_0.anim_4.keyframeIdx_8)
                {
                    func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 9, keyframeIdx + 22, sfx, pitch);
                }
                else
                {
                    if ((keyframeIdx + 30) >= playerChara->model_0.anim_4.keyframeIdx_8)
                    {
                        func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 30, keyframeIdx + 22, sfx, pitch);
                    }
                    else
                    {
                        func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 52, keyframeIdx + 42, sfx, pitch);
                    }
                }
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 59, keyframeIdx + 59, sfx, sp2D);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk157
        case PlayerState_Unk157:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 33, keyframeIdx + 25, sfx, sp2D);
            break;
#endif

#ifdef HAS_PlayerState_Unk158
        case PlayerState_Unk158:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 12, keyframeIdx + 5, sfx, sp2D);
            break;
#endif

#ifdef HAS_PlayerState_Unk113
        case PlayerState_Unk113:
            if (keyframeIdx + 5 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 14, keyframeIdx + 5, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 14, keyframeIdx + 21, sfx, pitch);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk123
        case PlayerState_Unk123:
            if (keyframeIdx + 9 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 14, keyframeIdx + 9, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 14, keyframeIdx + 19, sfx, pitch);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk149
        case PlayerState_Unk149:
            if (playerChara->model_0.anim_4.keyframeIdx_8 < keyframeIdx + 2)
            {
                func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx, Sfx_Unk1626);
            }
            else
            {
                if (playerChara->model_0.anim_4.keyframeIdx_8 < keyframeIdx + 8)
                {
                    if (func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 6, Q12(0.4f)) != false)
                    {
                        func_800892DC(8, 0x30); // Hex?
                    }
                }
                else
                {
                    if (playerChara->model_0.anim_4.keyframeIdx_8 < keyframeIdx + 41)
                    {
                        func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 3, Sfx_Unk1627);
                    }
                    else
                    {
                        func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 42, Sfx_Unk1628);
                    }
                }
            }

            if (keyframeIdx + 43 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 55, keyframeIdx + 43, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 55, keyframeIdx + 59, sfx, pitch);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk150
        case PlayerState_Unk150:
            if (func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 0x15, Q12(0.4f)) != false)
            {
                func_800892DC(8, 0x30); // Hex?
            }

            if (keyframeIdx + 8 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 8, keyframeIdx + 11, sfx, pitch);
            }
            else if (keyframeIdx + 0xE >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 14, keyframeIdx + 11, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 8, keyframeIdx + 16, sfx, pitch);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk151
        case PlayerState_Unk151:
            if (playerChara->model_0.anim_4.status_0 & 1)
            {
                if (keyframeIdx + 7 >= playerChara->model_0.anim_4.keyframeIdx_8)
                {
                    func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 7, Sfx_Unk1619);
                }
                else
                {
                    func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 11, Sfx_Unk1619);
                }

                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 16, keyframeIdx + 16, sfx, pitch);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk160
        case PlayerState_Unk160:
            if (keyframeIdx + 33 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 42, keyframeIdx + 33, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 42, keyframeIdx + 55, sfx, pitch);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk161
        case PlayerState_Unk161:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 24, keyframeIdx + 22, sfx, pitch);
            break;
#endif

#ifdef HAS_PlayerState_Unk162
        case PlayerState_Unk162:
            if (playerChara->model_0.anim_4.status_0 & 1)
            {
                func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 60, Sfx_Unk1623);
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk163
        case PlayerState_Unk163:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 6, 0, sfx, pitch);
            break;
#endif

#ifdef HAS_PlayerState_Unk167
        case PlayerState_Unk167:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 10, 0, sfx, pitch);
            break;
#endif

#ifdef HAS_PlayerState_Unk168
        case PlayerState_Unk168:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 38, keyframeIdx + 22, sfx, pitch);
            break;
#endif

#ifdef HAS_PlayerState_Unk185
        case PlayerState_Unk185:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 38, keyframeIdx + 22, sfx, pitch);
            break;
#endif

#ifdef HAS_PlayerState_Unk170
        case PlayerState_Unk170:
            func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 7, Sfx_Unk1629);
            break;
#endif

#ifdef HAS_PlayerState_Unk76
        case PlayerState_Unk76:
            if (playerChara->model_0.anim_4.status_0 & 1)
            {
                if (playerChara->model_0.anim_4.keyframeIdx_8 < keyframeIdx + 31)
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

#ifdef HAS_PlayerState_Unk91
        case PlayerState_Unk91:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 6, keyframeIdx + 6, sfx, pitch);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk92
        case PlayerState_Unk92:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 9, keyframeIdx + 9, sfx, pitch);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk93
        case PlayerState_Unk93:
            if (playerChara->model_0.anim_4.status_0 & 1)
            {
                func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 6, Sfx_Unk1385);
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 18, 0, sfx, pitch);
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            }
            break;
#endif

#ifdef HAS_PlayerState_Unk89
        case PlayerState_Unk89:
            if (keyframeIdx + 5 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 5, keyframeIdx + 16, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 74, keyframeIdx + 77, sfx, pitch);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk87
        case PlayerState_Unk87:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 35, keyframeIdx + 17, Sfx_Unk1423, pitch);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif

#ifdef HAS_PlayerState_Unk88
        case PlayerState_Unk88:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyframeIdx + 15, keyframeIdx + 31, Sfx_Unk1423, pitch);
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
