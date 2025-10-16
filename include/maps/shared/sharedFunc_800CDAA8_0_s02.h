#include "bodyprog/player_logic.h"

// TODO:
// - Make defines for each of the `keyFrameIdx = XXX` assignments that change between maps, so they can be overridden here.
//   (better than having a bunch of #ifdef MAPXXX around those assignments)
//
// - Move these per-map defines into each maps header file instead, to get rid of this big block.
//   (defines might also end up used in other parts of code too)
//
// - The order of the switch cases below isn't ideal, most of them can probably be sorted.
//   Maps do depend on the order of the cases though, they're usually in descending order but seems some cases were inserted randomly.
//   (unfortunately #define sections below don't always match map order, some were re-sorted during early work on this func, but later were left in original order)
//
// - Rename `sharedFunc_800CDAA8_0_s02` -> `sharedFunc_800D0E34_0_s00`, sharedData_800D32A0_0_s02` -> `sharedData_800E39DC_0_s00`

// All maps have 52
#define HAS_PlayerState_Unk52

// Offset applied to `PlayerState_Unk59` / `PlayerState_Unk60` in certain maps.
#define KEYFRAME_OFFSET 0

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

#if defined(MAP1_S01)
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk59  // 0x3B
#define HAS_PlayerState_Unk60  // 0x3C
#define HAS_PlayerState_Unk83  // 0x53
#define HAS_PlayerState_Unk85  // 0x55
#define HAS_PlayerState_Unk122 // 0x7A
#define KEYFRAME_OFFSET        -54
#endif

#if defined(MAP1_S02)
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk53  // 0x35
#define HAS_PlayerState_Unk54  // 0x36
#define HAS_PlayerState_Unk55  // 0x37
#define HAS_PlayerState_Unk56  // 0x38
#define HAS_PlayerState_Unk57  // 0x39
#define HAS_PlayerState_Unk59  // 0x3B
#define HAS_PlayerState_Unk60  // 0x3C
#define HAS_PlayerState_Unk74  // 0x4A
#define HAS_PlayerState_Unk94  // 0x5E
#define HAS_PlayerState_Unk95  // 0x5F
#define HAS_PlayerState_Unk97  // 0x61
#define HAS_PlayerState_Unk98  // 0x62
#define HAS_PlayerState_Unk106 // 0x6A
#define KEYFRAME_OFFSET        -24
#endif

#if defined(MAP1_S03)
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk59  // 0x3B
#define HAS_PlayerState_Unk60  // 0x3C
#define HAS_PlayerState_Unk85  // 0x55
#define HAS_PlayerState_Unk86  // 0x56
#define HAS_PlayerState_Unk99  // 0x63
#define HAS_PlayerState_Unk100 // 0x64
#define HAS_PlayerState_Unk107 // 0x6B
#define HAS_PlayerState_Unk108 // 0x6C
#define HAS_PlayerState_Unk122 // 0x7A
#define KEYFRAME_OFFSET        -24
#endif

#if defined(MAP1_S06) || defined(MAP2_S00)
#define HAS_PlayerState_Unk52 // 0x34
#define HAS_PlayerState_Unk59 // 0x3B
#define HAS_PlayerState_Unk60 // 0x3C
#if defined(MAP1_S06)
#define KEYFRAME_OFFSET -249
#elif defined(MAP2_S00)
#define KEYFRAME_OFFSET 19
#endif
#endif

#if defined(MAP2_S01)
#define HAS_PlayerState_Unk51       // 0x33
#define HAS_PlayerState_Unk131      // 0x83
#define HAS_PlayerState_Unk52       // 0x34
#define HAS_PlayerState_Unk111      // 0x6F
#define HAS_PlayerState_Unk113      // 0x71
#define KEYFRAME_OFFSET        -361 // Affects `PlayerState_Unk113` keyframe.
#endif

#if defined(MAP3_S00)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk131 // 0x83
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk72  // 0x48
#define HAS_PlayerState_Unk115 // 0x73
#endif

#if defined(MAP3_S01)
#define HAS_PlayerState_Unk52 // 0x34
#define HAS_PlayerState_Unk59 // 0x3B
#define HAS_PlayerState_Unk60 // 0x3C
#define KEYFRAME_OFFSET       30
#endif

#if defined(MAP3_S03)
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk59  // 0x3B
#define HAS_PlayerState_Unk60  // 0x3C
#define HAS_PlayerState_Unk146 // 0x92
#define HAS_PlayerState_Unk147 // 0x93
#define HAS_PlayerState_Unk154 // 0x9A
#endif

#if defined(MAP3_S04)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk131 // 0x83
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk59  // 0x3B
#define HAS_PlayerState_Unk60  // 0x3C
#define HAS_PlayerState_Unk125 // 0x7D
#define KEYFRAME_OFFSET        30
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
#define KEYFRAME_OFFSET        30
#endif

#if defined(MAP3_S06)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk131 // 0x83
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk111 // 0x6F
#define HAS_PlayerState_Unk117 // 0x75
#endif

#if defined(MAP4_S01)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk131 // 0x83
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk53  // 0x35
#define HAS_PlayerState_Unk69  // 0x45
#define HAS_PlayerState_Unk105 // 0x69
#define HAS_PlayerState_Unk72  // 0x48
#define HAS_PlayerState_Unk116 // 0x74
#define HAS_PlayerState_Unk118 // 0x76
#define HAS_PlayerState_Unk119 // 0x77
#define HAS_PlayerState_Unk120 // 0x78
#define HAS_PlayerState_Unk121 // 0x79
#define HAS_PlayerState_Unk124 // 0x7c
#define HAS_PlayerState_Unk130 // 0x82
#define HAS_PlayerState_Unk140 // 0x8C
#define HAS_PlayerState_Unk142 // 0x8E
#define HAS_PlayerState_Unk153 // 0x99
#define HAS_PlayerState_Unk186 // 0xBA
#endif

#if defined(MAP4_S03)
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk123 // 0x7B
#define HAS_PlayerState_Unk128 // 0x80
#define HAS_PlayerState_Unk129 // 0x81
#endif

#if defined(MAP4_S04)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk131 // 0x83
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk53  // 0x35
#define HAS_PlayerState_Unk117 // 0x75
#define HAS_PlayerState_Unk134 // 0x86
#define HAS_PlayerState_Unk135 // 0x87
#endif

#if defined(MAP4_S05)
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk53  // 0x35
#define HAS_PlayerState_Unk54  // 0x36
#define HAS_PlayerState_Unk55  // 0x37
#define HAS_PlayerState_Unk56  // 0x38
#define HAS_PlayerState_Unk57  // 0x39
#define HAS_PlayerState_Unk109 // 0x6d
#endif

#if defined(MAP5_S00)
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk59  // 0x3B
#define HAS_PlayerState_Unk60  // 0x3C
#define HAS_PlayerState_Unk87  // 0x57
#define HAS_PlayerState_Unk88  // 0x58
#define HAS_PlayerState_Unk114 // 0x72
#define KEYFRAME_OFFSET        -96
#endif

#if defined(MAP5_S02)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk131 // 0x83
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk59  // 0x3B
#define HAS_PlayerState_Unk60  // 0x3C
#define HAS_PlayerState_Unk66  // 0x42
#define HAS_PlayerState_Unk70  // 0x46
#define HAS_PlayerState_Unk73  // 0x49
#define HAS_PlayerState_Unk153 // 0x99
#define HAS_PlayerState_Unk186 // 0xBA
#define HAS_PlayerState_Unk164 // 0xA4
#define HAS_PlayerState_Unk165 // 0xA5
#define HAS_PlayerState_Unk166 // 0xA6
#define KEYFRAME_OFFSET        -126
#endif

#if defined(MAP5_S03)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk131 // 0x83
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk59  // 0x3B
#define HAS_PlayerState_Unk60  // 0x3C
#define HAS_PlayerState_Unk69  // 0x45
#define HAS_PlayerState_Unk105 // 0x69
#define HAS_PlayerState_Unk159 // 0x9f
#define HAS_PlayerState_Unk169 // 0xa9
#define HAS_PlayerState_Unk187 // 0xbb
#define KEYFRAME_OFFSET        -126
#endif

#if defined(MAP6_S00)
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk53  // 0x35
#define HAS_PlayerState_Unk114 // 0x72
#define HAS_PlayerState_Unk126 // 0x7e
#define HAS_PlayerState_Unk127 // 0x7f
#define HAS_PlayerState_Unk133 // 0x85
#endif

#if defined(MAP6_S01)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk131 // 0x83
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk70  // 0x46
#define HAS_PlayerState_Unk71  // 0x47
#define HAS_PlayerState_Unk132 // 0x84
#define HAS_PlayerState_Unk113 // 0x71
#define KEYFRAME_OFFSET        -384
#endif

#if defined(MAP6_S02)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk131 // 0x83
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk53  // 0x35
#define HAS_PlayerState_Unk71  // 0x47
#define HAS_PlayerState_Unk132 // 0x84
#define HAS_PlayerState_Unk111 // 0x6F
#define HAS_PlayerState_Unk175 // 0xaf
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

#if defined(MAP7_S00)
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk53  // 0x35
#define HAS_PlayerState_Unk54  // 0x36
#define HAS_PlayerState_Unk55  // 0x37
#define HAS_PlayerState_Unk56  // 0x38
#define HAS_PlayerState_Unk57  // 0x39
#define HAS_PlayerState_Unk135 // 0x87
#define HAS_PlayerState_Unk136 // 0x88
#define HAS_PlayerState_Unk137 // 0x89
#define HAS_PlayerState_Unk138 // 0x8a
#define HAS_PlayerState_Unk139 // 0x8b
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
#define HAS_PlayerState_Unk143 // 0x8F
#define HAS_PlayerState_Unk144 // 0x90
#define HAS_PlayerState_Unk146 // 0x92
#define HAS_PlayerState_Unk147 // 0x93
#define HAS_PlayerState_Unk148 // 0x94
#define HAS_PlayerState_Unk155 // 0x9B
#define HAS_PlayerState_Unk156 // 0x9C
#define HAS_PlayerState_Unk157 // 0x9D
#define HAS_PlayerState_Unk158 // 0x9E
#define KEYFRAME_OFFSET        -65
#endif

#if defined(MAP7_S03)
#define HAS_PlayerState_Unk51  // 0x33
#define HAS_PlayerState_Unk131 // 0x83
#define HAS_PlayerState_Unk52  // 0x34
#define HAS_PlayerState_Unk153 // 0x99
#define HAS_PlayerState_Unk186 // 0xBA
#define HAS_PlayerState_Unk162 // 0xA2
#define HAS_PlayerState_Unk171 // 0xab
#define HAS_PlayerState_Unk172 // 0xac
#define HAS_PlayerState_Unk173 // 0xad
#define HAS_PlayerState_Unk174 // 0xae
#define HAS_PlayerState_Unk176 // 0xb0
#define HAS_PlayerState_Unk177 // 0xb1
#define HAS_PlayerState_Unk184 // 0xb8
#define HAS_PlayerState_Unk178 // 0xb2
#define HAS_PlayerState_Unk179 // 0xb3
#define HAS_PlayerState_Unk180 // 0xb4
#define HAS_PlayerState_Unk181 // 0xb5
#define HAS_PlayerState_Unk182 // 0xb6
#define HAS_PlayerState_Unk183 // 0xb7
#endif

// Very similar to `func_80071968_Switch1`
static inline void sharedFunc_800CDAA8_0_s02_Switch()
{
    if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_Unk52)
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

// Slight change in PlayerState_Unk55 version
static inline void sharedFunc_800CDAA8_0_s02_Switch_Unk85(s_MainCharacterExtra* extra)
{
    if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_Unk52)
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
        if (extra->model_0.anim_4.keyframeIdx_8 >= 958)
        {
            func_8003DD80(1, 21);
        }
        else
        {
            func_8003DD80(1, 17);
        }
    }
}

void sharedFunc_800CDAA8_0_s02(s_SubCharacter* playerChara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord)
{
    s_Collision coll;
    s32         sfx;
    s8          pitch;
    s8          sp2D;
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
            keyFrameIdx = 927 + KEYFRAME_OFFSET;
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
            keyFrameIdx = 942 + KEYFRAME_OFFSET;
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
#ifdef HAS_PlayerState_Unk87
        case PlayerState_Unk87:
            func_8007FC48(playerChara, extra, 0x166);
#ifdef MAP5_S00
            keyFrameIdx = 857;
#else
            keyFrameIdx = 873;
#endif
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
#ifdef MAP5_S00
            keyFrameIdx = 894;
#else
            keyFrameIdx = 910;
#endif
            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif
#ifdef HAS_PlayerState_Unk114
        case PlayerState_Unk114:
            func_8007FB94(playerChara, extra, 0x186);
#ifdef MAP6_S00
            keyFrameIdx = 956;
#else
            keyFrameIdx = 932;
#endif
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
            keyFrameIdx = 980;
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
            keyFrameIdx = 1002;
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
            keyFrameIdx = 1039;
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
#ifdef HAS_PlayerState_Unk85
        case PlayerState_Unk85:
            func_8007FB94(playerChara, extra, 0x169);
#ifdef MAP1_S03
            func_8003D03C();
            func_8003DD80(1, 0x11);
#else
            keyFrameIdx = 949;
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
#ifdef HAS_PlayerState_Unk122
        case PlayerState_Unk122:
#ifdef MAP1_S03
            func_8007FB94(playerChara, extra, 0x18E);
            keyFrameIdx = 1093;
#else
            func_8007FC48(playerChara, extra, 0x18E);
            keyFrameIdx = 961;
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
#ifdef MAP4_S01
            keyFrameIdx = 678;
#elif defined(MAP5_S03)
            keyFrameIdx = 828;
#else
            keyFrameIdx = 984;
#endif
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
            keyFrameIdx = 170;
            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk169
        case PlayerState_Unk169:
            keyFrameIdx = 864;
            if (playerChara->model_0.anim_4.keyframeIdx_8 <= keyFrameIdx + 19)
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
#ifdef HAS_PlayerState_Unk81
        case PlayerState_Unk81:
            keyFrameIdx = 998;
            if (playerChara->model_0.anim_4.keyframeIdx_8 >= keyFrameIdx + 3)
            {
                if (playerChara->model_0.anim_4.keyframeIdx_8 <= keyFrameIdx + 24)
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
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 =
                            CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126, 0, Q12(0.2875f));
                    }
                }
                else if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 != 0)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 -= ((g_DeltaTime0 * Q12(0.4f)) / TIME_STEP_30_FPS) * 2;
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 < 0)
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
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
            keyFrameIdx = 750;
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
            keyFrameIdx = 779;
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
            keyFrameIdx = 807;
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
            keyFrameIdx = 846;
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
            keyFrameIdx = 967;
            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk140
        case PlayerState_Unk140:
            func_8007FC48(playerChara, extra, 0x19F);
            keyFrameIdx = 982;
            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk142
        case PlayerState_Unk142:
            func_8007FB94(playerChara, extra, 0x1A1);
            keyFrameIdx = 1016;
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
#if !defined(MAP6_S04) && !defined(MAP5_S02) && !defined(MAP6_S01)
            func_8003D03C();
#endif
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
#ifdef HAS_PlayerState_Unk153
        case PlayerState_Unk153:
            func_8007FB94(playerChara, extra, 0x1AC);
#ifdef MAP5_S02
            keyFrameIdx = 889;
#elif defined(MAP7_S03)
            keyFrameIdx = 816;
#else
            keyFrameIdx = 1036;
#endif
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
            keyFrameIdx = 889;
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
            keyFrameIdx = 953;

            if (playerChara->model_0.anim_4.keyframeIdx_8 == keyFrameIdx + 5)
            {
                if (!(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk6))
                {
                    func_8006342C(0x20, 0x340, playerChara->rotation_24.vy, coord);
                    func_8005F6B0(&g_SysWork.npcs_1A0[1], &(VECTOR3){ Q12(140.39f), Q12(-0.55f), Q12(22.76f) }, 3, 3);
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk6;
                }
            }

            if (playerChara->model_0.anim_4.keyframeIdx_8 == keyFrameIdx + 22)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;
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
#ifdef HAS_PlayerState_Unk141
        case PlayerState_Unk141:
            func_8007FB94(playerChara, extra, 0x1A0);
            keyFrameIdx = 1066;
            if (D_800C4606)
            {
                Player_ExtraStateSet(playerChara, extra, PlayerState_Unk52);
                D_800C4606 = 0;
            }
            sharedFunc_800CDAA8_0_s02_Switch();
            break;
#endif
#ifdef HAS_PlayerState_Unk115
        case PlayerState_Unk115:
            func_8007FB94(playerChara, extra, 0x187);
            keyFrameIdx = 699;
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
#ifdef MAP3_S03
            keyFrameIdx = 954;
#else
            keyFrameIdx = 1074;
#endif
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
#ifdef MAP3_S03
            keyFrameIdx = 988;
#else
            keyFrameIdx = 1108;
#endif
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
#ifdef HAS_PlayerState_Unk154
        case PlayerState_Unk154:
            keyFrameIdx = 1006;

            if (playerChara->model_0.anim_4.keyframeIdx_8 > keyFrameIdx + 72)
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
            keyFrameIdx = 678;
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
            keyFrameIdx = 733;
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
            keyFrameIdx = 793;
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
            keyFrameIdx = 834;
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
#ifdef HAS_PlayerState_Unk111
        case PlayerState_Unk111:
            func_8007FB94(playerChara, extra, 0x183);
#ifdef MAP6_S02
            keyFrameIdx = 915;
#else
            keyFrameIdx = 678;
#endif
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
            keyFrameIdx = 1084 + KEYFRAME_OFFSET;
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
#ifdef MAP4_S04
            keyFrameIdx = 678;
#else
            keyFrameIdx = 723;
#endif
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
#ifdef MAP4_S03
            keyFrameIdx = 877;
#else
            keyFrameIdx = 693;
#endif
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
                extra->model_0.anim_4.time_4       = FP_TO(g_MapOverlayHeader.animInfos_34[playerChara->model_0.anim_4.status_0 - 76].startKeyframeIdx_C, Q12_SHIFT) + (new_var = g_SysWork.npcs_1A0)[0].model_0.anim_4.time_4 - Q12(261.0f);
                playerChara->model_0.anim_4.time_4 = FP_TO(g_MapOverlayHeader.animInfos_34[playerChara->model_0.anim_4.status_0 - 76].startKeyframeIdx_C, Q12_SHIFT) + new_var[0].model_0.anim_4.time_4 - Q12(261.0f);
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
            keyFrameIdx = 728;
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
#ifdef HAS_PlayerState_Unk149
        case PlayerState_Unk149:
            func_8007FB94(playerChara, extra, 0x1A8);
            keyFrameIdx = 728;
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
            keyFrameIdx = 793;
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
            keyFrameIdx = 1106;
            if (playerChara->model_0.anim_4.keyframeIdx_8 == keyFrameIdx + 11 || playerChara->model_0.anim_4.keyframeIdx_8 == keyFrameIdx + 7)
            {
                if (!(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk6))
                {
                    func_8005F6B0(&g_SysWork.npcs_1A0[1], &(VECTOR3){ Q12(14.94f), Q12(-0.05f), Q12(102.0f) }, 3, 3);
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk6;
                }
            }
            if (playerChara->model_0.anim_4.keyframeIdx_8 == keyFrameIdx + 8 || playerChara->model_0.anim_4.keyframeIdx_8 == keyFrameIdx + 19)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;
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
            keyFrameIdx = 1126;
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
            keyFrameIdx = 1207;
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
#ifdef MAP7_S03
            keyFrameIdx = 837;
#else
            keyFrameIdx = 1237;
#endif
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
            keyFrameIdx = 1347;
#else
            keyFrameIdx = 1070;
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
            keyFrameIdx = 1363;
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
            keyFrameIdx = 1363;
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
            keyFrameIdx = 1411;
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
            keyFrameIdx = 1062;
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
            keyFrameIdx = 1062;
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
#ifdef HAS_PlayerState_Unk76
        case PlayerState_Unk76:
            func_8007FC48(playerChara, extra, 0x15F);
            keyFrameIdx = 827;
            if (D_800C4606)
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
            keyFrameIdx = 948;
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
            keyFrameIdx = 1027;
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
            keyFrameIdx = 1055;
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
#ifdef HAS_PlayerState_Unk171
        case PlayerState_Unk171:
            func_8007FB94(playerChara, extra, 0x1BE);
            keyFrameIdx = 937;
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
            keyFrameIdx = 961;
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
            keyFrameIdx = 1087;
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
            keyFrameIdx = 1198;
            if (playerChara->model_0.anim_4.keyframeIdx_8 >= keyFrameIdx + 23)
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
            keyFrameIdx = 1358;
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
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 5, 0, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk60
        case PlayerState_Unk60:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 7, 0, sfx, pitch);
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
#ifdef HAS_PlayerState_Unk97
        case PlayerState_Unk97:
            if (keyFrameIdx + 4 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 10, keyFrameIdx + 4, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 10, keyFrameIdx + 13, sfx, pitch);
            }
            func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 26, Sfx_Unk1456);
            break;
#endif
#ifdef HAS_PlayerState_Unk115
        case PlayerState_Unk115:
            if (keyFrameIdx + 9 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 9, keyFrameIdx + 33, sfx, pitch);
            }
            else
            {
                if (keyFrameIdx + 39 >= playerChara->model_0.anim_4.keyframeIdx_8)
                {
                    func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 39, keyFrameIdx + 33, sfx, pitch);
                }
                else
                {
                    func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 46, keyFrameIdx + 42, sfx, pitch);
                }
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk122
        case PlayerState_Unk122:
            if (keyFrameIdx + 9 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 14, keyFrameIdx + 9, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 14, keyFrameIdx + 19, sfx, pitch);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk146
        case PlayerState_Unk146:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 16, keyFrameIdx + 10, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk147
        case PlayerState_Unk147:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 11, keyFrameIdx + 11, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk154
        case PlayerState_Unk154:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 7, keyFrameIdx + 21, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk81
        case PlayerState_Unk81:
            if (keyFrameIdx + 19 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 31, keyFrameIdx + 19, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 31, keyFrameIdx + 40, sfx, pitch);
            }
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif
#ifdef HAS_PlayerState_Unk105
        case PlayerState_Unk105:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 5, keyFrameIdx + 12, sfx, pitch);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif
#ifdef HAS_PlayerState_Unk118
        case PlayerState_Unk118:
            if (keyFrameIdx + 8 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 12, keyFrameIdx + 8, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 12, keyFrameIdx + 16, sfx, pitch);
            }
            if (playerChara->model_0.anim_4.status_0 & 1)
            {
#define Sfx_Unk1539 1539
                func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 9, Sfx_Unk1539);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk120
        case PlayerState_Unk120:
            if (keyFrameIdx + 5 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 17, keyFrameIdx + 5, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 17, keyFrameIdx + 25, sfx, pitch);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk121
        case PlayerState_Unk121:
            if (keyFrameIdx + 5 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 5, keyFrameIdx + 12, sfx, pitch);
            }
            else if (keyFrameIdx + 23 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 23, keyFrameIdx + 12, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 5, keyFrameIdx + 29, sfx, pitch);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk124
        case PlayerState_Unk124:
            if (func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, 80, 87, sfx, sp2D))
            {
                playerChara->properties_E4.player.runTimer_F8++;
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk140
        case PlayerState_Unk140:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 25, keyFrameIdx + 25, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk142
        case PlayerState_Unk142:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 10, keyFrameIdx + 10, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk130
        case PlayerState_Unk130:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 14, keyFrameIdx + 14, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk153
        case PlayerState_Unk153:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 5, keyFrameIdx + 12, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk186
        case PlayerState_Unk186:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, 0, keyFrameIdx + 12, sfx, pitch);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Moving;
            break;
#endif
#ifdef HAS_PlayerState_Unk165
        case PlayerState_Unk165:
            func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 5, Sfx_Unk1283);
            break;
#endif
#ifdef HAS_PlayerState_Unk141
        case PlayerState_Unk141:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 46, keyFrameIdx + 5, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk155
        case PlayerState_Unk155:
            if (playerChara->model_0.anim_4.keyframeIdx_8 < 34)
            {
                if (keyFrameIdx + 10 >= playerChara->model_0.anim_4.keyframeIdx_8)
                {
                    func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 10, keyFrameIdx + 16, sfx, pitch);
                }
                else
                {
                    if (keyFrameIdx + 21 >= playerChara->model_0.anim_4.keyframeIdx_8)
                    {
                        func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 21, keyFrameIdx + 16, sfx, pitch);
                    }
                    else
                    {
                        func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 28, keyFrameIdx + 25, sfx, pitch);
                    }
                }
            }
            else if (keyFrameIdx + 16 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 34, keyFrameIdx + 38, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 42, keyFrameIdx + 46, sfx, pitch);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk156
        case PlayerState_Unk156:
            if (playerChara->model_0.anim_4.keyframeIdx_8 < 59)
            {
                if (keyFrameIdx + 9 >= playerChara->model_0.anim_4.keyframeIdx_8)
                {
                    func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 9, keyFrameIdx + 22, sfx, pitch);
                }
                else
                {
                    if (keyFrameIdx + 30 >= playerChara->model_0.anim_4.keyframeIdx_8)
                    {
                        func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 30, keyFrameIdx + 22, sfx, pitch);
                    }
                    else
                    {
                        func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 52, keyFrameIdx + 42, sfx, pitch);
                    }
                }
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 59, keyFrameIdx + 59, sfx, sp2D);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk157
        case PlayerState_Unk157:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 33, keyFrameIdx + 25, sfx, sp2D);
            break;
#endif
#ifdef HAS_PlayerState_Unk158
        case PlayerState_Unk158:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 12, keyFrameIdx + 5, sfx, sp2D);
            break;
#endif
#ifdef HAS_PlayerState_Unk159
        case PlayerState_Unk159:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 11, 0, sfx, sp2D);
            break;
#endif
#ifdef HAS_PlayerState_Unk113
        case PlayerState_Unk113:
            if (keyFrameIdx + 5 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 14, keyFrameIdx + 5, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 14, keyFrameIdx + 21, sfx, pitch);
            }
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif
#ifdef HAS_PlayerState_Unk111
        case PlayerState_Unk111:
            if (playerChara->model_0.anim_4.status_0 & 1)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 11, keyFrameIdx + 21, sfx, pitch);
            }
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif
#ifdef HAS_PlayerState_Unk114
        case PlayerState_Unk114:
            if (keyFrameIdx + 8 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 13, keyFrameIdx + 8, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 13, keyFrameIdx + 18, sfx, pitch);
            }
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Moving;
            break;
#endif
#ifdef HAS_PlayerState_Unk117
        case PlayerState_Unk117:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 34, 0, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk123
        case PlayerState_Unk123:
            if (keyFrameIdx + 9 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 14, keyFrameIdx + 9, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 14, keyFrameIdx + 19, sfx, pitch);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk126
        case PlayerState_Unk126:
            if (keyFrameIdx + 9 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 16, keyFrameIdx + 9, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 16, keyFrameIdx + 22, sfx, pitch);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk127
        case PlayerState_Unk127:
            if (keyFrameIdx + 5 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 17, keyFrameIdx + 5, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 17, keyFrameIdx + 26, sfx, pitch);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk133
        case PlayerState_Unk133:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 5, keyFrameIdx + 5, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk138
        case PlayerState_Unk138:
            if (playerChara->model_0.anim_4.status_0 & 1)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 18, keyFrameIdx + 14, sfx, pitch);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk149
        case PlayerState_Unk149:
            if (playerChara->model_0.anim_4.keyframeIdx_8 < keyFrameIdx + 2)
            {
                func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx, Sfx_Unk1626);
            }
            else
            {
                if (playerChara->model_0.anim_4.keyframeIdx_8 < keyFrameIdx + 8)
                {
                    if (func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 6, Q12(0.4f)) != false)
                    {
                        func_800892DC(8, 0x30); // Hex?
                    }
                }
                else
                {
                    if (playerChara->model_0.anim_4.keyframeIdx_8 < keyFrameIdx + 41)
                    {
                        func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 3, Sfx_Unk1627);
                    }
                    else
                    {
                        func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 42, Sfx_Unk1628);
                    }
                }
            }
            if (keyFrameIdx + 43 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 55, keyFrameIdx + 43, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 55, keyFrameIdx + 59, sfx, pitch);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk150
        case PlayerState_Unk150:
            if (func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 21, Q12(0.4f)) != false)
            {
                func_800892DC(8, 0x30); // Hex?
            }
            if (keyFrameIdx + 8 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 8, keyFrameIdx + 11, sfx, pitch);
            }
            else if (keyFrameIdx + 0xE >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 14, keyFrameIdx + 11, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 8, keyFrameIdx + 16, sfx, pitch);
            }

            break;
#endif
#ifdef HAS_PlayerState_Unk151
        case PlayerState_Unk151:
            if (playerChara->model_0.anim_4.status_0 & 1)
            {
                if (keyFrameIdx + 7 >= playerChara->model_0.anim_4.keyframeIdx_8)
                {
                    func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 7, Sfx_Unk1619);
                }
                else
                {
                    func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 11, Sfx_Unk1619);
                }
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 16, keyFrameIdx + 16, sfx, pitch);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk160
        case PlayerState_Unk160:
            if (keyFrameIdx + 33 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 42, keyFrameIdx + 33, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 42, keyFrameIdx + 55, sfx, pitch);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk161
        case PlayerState_Unk161:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 24, keyFrameIdx + 22, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk162
        case PlayerState_Unk162:
            if (playerChara->model_0.anim_4.status_0 & 1)
            {
#ifdef MAP7_S03
#define Sfx_Unk1671 1671
                func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 60, Sfx_Unk1671);
#else
                func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 60, Sfx_Unk1623);
#endif
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk163
        case PlayerState_Unk163:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 6, 0, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk167
        case PlayerState_Unk167:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 10, 0, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk168
        case PlayerState_Unk168:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 38, keyFrameIdx + 22, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk185
        case PlayerState_Unk185:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 38, keyFrameIdx + 22, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk170
        case PlayerState_Unk170:
            func_80071620(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 7, Sfx_Unk1629);
            break;
#endif
#ifdef HAS_PlayerState_Unk172
        case PlayerState_Unk172:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 29, 0, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk176
        case PlayerState_Unk176:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 8, keyFrameIdx + 19, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk179
        case PlayerState_Unk179:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 8, keyFrameIdx + 44, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk183
        case PlayerState_Unk183:
            if (keyFrameIdx + 11 >= playerChara->model_0.anim_4.keyframeIdx_8)
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 28, keyFrameIdx + 11, sfx, pitch);
            }
            else
            {
                func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 28, keyFrameIdx + 55, sfx, pitch);
            }
            break;
#endif
#ifdef HAS_PlayerState_Unk171
        case PlayerState_Unk171:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, keyFrameIdx + 9, keyFrameIdx + 14, sfx, pitch);
            break;
#endif
#ifdef HAS_PlayerState_Unk76
        case PlayerState_Unk76:
            if (playerChara->model_0.anim_4.status_0 & 1)
            {
                if (playerChara->model_0.anim_4.keyframeIdx_8 < keyFrameIdx + 31)
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
#ifdef HAS_PlayerState_Unk175
        case PlayerState_Unk175:
            func_800713E8(playerChara->model_0.anim_4.status_0, playerChara, 18, 6, sfx, pitch);
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
