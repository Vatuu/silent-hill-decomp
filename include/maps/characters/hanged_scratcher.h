#ifndef _MAPS_CHARACTERS_HANGEDSCRATCHER_H
#define _MAPS_CHARACTERS_HANGEDSCRATCHER_H

/** @brief Hanged Scratcher character flags */
typedef enum _HangedScratcherFlags
{
    HangedScratchedFlag_0 = 1 << 0
} e_HangedScratcherFlags;

/** @brief Hanged Scratcher character animation indices. */
typedef enum _HangedScratcherAnim
{
    HangedScratcherAnim_Still = 0,
    HangedScratcherAnim_1     = 1,
    HangedScratcherAnim_2     = 2,
    HangedScratcherAnim_3     = 3,
    HangedScratcherAnim_4     = 4, // } Pair.
    HangedScratcherAnim_5     = 5, // }
    HangedScratcherAnim_6     = 6,
    HangedScratcherAnim_7     = 7,
    HangedScratcherAnim_8     = 8,
    HangedScratcherAnim_9     = 9,
    HangedScratcherAnim_10    = 10,
    HangedScratcherAnim_11    = 11,
    HangedScratcherAnim_12    = 12,
    HangedScratcherAnim_13    = 13,
    HangedScratcherAnim_14    = 14,
    HangedScratcherAnim_15    = 15,
    HangedScratcherAnim_16    = 16,
    HangedScratcherAnim_17    = 17,
    HangedScratcherAnim_18    = 18,
    HangedScratcherAnim_19    = 19,
    HangedScratcherAnim_20    = 20,
    HangedScratcherAnim_21    = 21,
    HangedScratcherAnim_22    = 22,
    HangedScratcherAnim_23    = 23,
    HangedScratcherAnim_24    = 24,
    HangedScratcherAnim_25    = 25,
    HangedScratcherAnim_26    = 26
} e_HangedScratcherAnim;

/** @brief Hanged Scratcher character control states. */
typedef enum _HangedScratcherControl
{
    HangedScratcherControl_None = 0,
    HangedScratcherControl_1    = 1,
    HangedScratcherControl_2    = 2,
    HangedScratcherControl_3    = 3,
    HangedScratcherControl_4    = 4,
    HangedScratcherControl_5    = 5,
    HangedScratcherControl_6    = 6,
    HangedScratcherControl_7    = 7,
    HangedScratcherControl_8    = 8,
    HangedScratcherControl_9    = 9,
    HangedScratcherControl_10   = 10,
    HangedScratcherControl_11   = 11,
    HangedScratcherControl_12   = 12,
    HangedScratcherControl_13   = 13,
    HangedScratcherControl_14   = 14,
    HangedScratcherControl_15   = 15,
    HangedScratcherControl_16   = 16
} e_HangedScratcherControl;

/** @brief Hanged Scratcher character state steps. */
typedef enum _HangedScratcherStateStep
{
    HangedScratcherStateStep_0  = 0,
    HangedScratcherStateStep_1  = 1,
    HangedScratcherStateStep_2  = 2,
    HangedScratcherStateStep_3  = 3,
    HangedScratcherStateStep_4  = 4,
    HangedScratcherStateStep_5  = 5,
    HangedScratcherStateStep_6  = 6,
    HangedScratcherStateStep_7  = 7,
    HangedScratcherStateStep_8  = 8,
    HangedScratcherStateStep_9  = 9,
    HangedScratcherStateStep_10 = 10,
    HangedScratcherStateStep_11 = 11,
    HangedScratcherStateStep_12 = 12,
    HangedScratcherStateStep_13 = 13,
    HangedScratcherStateStep_14 = 14,
    HangedScratcherStateStep_15 = 15,
    HangedScratcherStateStep_16 = 16,
    HangedScratcherStateStep_17 = 17,
    HangedScratcherStateStep_18 = 18,
    HangedScratcherStateStep_19 = 19,
    HangedScratcherStateStep_20 = 20
} e_HangedScratcherStateStep;

/*s_AnimInfo HANGED_SCRATCHER_ANIM_INFOS[] = {
    { Anim_Update2, NO_VALUE, false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { NULL, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, 0, 0 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(0) }, NO_VALUE, 0 },
    { Anim_Update0, ANIM_STATUS(1, true), false, ANIM_STATUS(24, false), { Q12(0) }, 0, 50 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q12(0) }, NO_VALUE, 51 },
    { Anim_Update0, ANIM_STATUS(2, true), false, ANIM_STATUS(25, false), { Q12(0) }, 51, 86 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q12(0) }, NO_VALUE, 87 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(26, false), { Q12(0) }, 87, 97 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q12(18) }, NO_VALUE, 98 },
    { Anim_Update0, ANIM_STATUS(4, true), false, ANIM_STATUS(14, false), { Q12(19.5f) }, 98, 115 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q12(12) }, NO_VALUE, 116 },
    { Anim_Update0, ANIM_STATUS(5, true), false, ANIM_STATUS(15, false), { Q12(23) }, 116, 135 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q12(4) }, NO_VALUE, 136 },
    { Anim_Update0, ANIM_STATUS(6, true), false, ANIM_STATUS(19, false), { Q12(2) }, 136, 147 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q12(4) }, NO_VALUE, 148 },
    { Anim_Update0, ANIM_STATUS(7, true), false, ANIM_STATUS(20, false), { Q12(1) }, 148, 153 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q12(4) }, NO_VALUE, 154 },
    { Anim_Update0, ANIM_STATUS(8, true), false, ANIM_STATUS(14, false), { Q12(14) }, 154, 165 },
    { Anim_Update2, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q12(4) }, NO_VALUE, 168 },
    { Anim_Update0, ANIM_STATUS(9, true), false, ANIM_STATUS(15, false), { Q12(0) }, 168, 175 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(16) }, NO_VALUE, 176 },
    { Anim_Update0, ANIM_STATUS(10, true), false, ANIM_STATUS(12, false), { Q12(0) }, 176, 191 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(2) }, NO_VALUE, 192 },
    { Anim_Update0, ANIM_STATUS(11, true), false, ANIM_STATUS(13, false), { Q12(0) }, 192, 201 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q12(16) }, NO_VALUE, 202 },
    { Anim_Update1, ANIM_STATUS(12, true), false, NO_VALUE, { Q12(3) }, 202, 215 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q12(2) }, NO_VALUE, 216 },
    { Anim_Update1, ANIM_STATUS(13, true), false, NO_VALUE, { Q12(3) }, 216, 221 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q12(2) }, NO_VALUE, 222 },
    { Anim_Update1, ANIM_STATUS(14, true), false, NO_VALUE, { Q12(0) }, 222, 231 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true), { Q12(2) }, NO_VALUE, 232 },
    { Anim_Update1, ANIM_STATUS(15, true), false, NO_VALUE, { Q12(0) }, 232, 243 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true), { Q12(16) }, NO_VALUE, 244 },
    { Anim_Update0, ANIM_STATUS(16, true), false, ANIM_STATUS(15, false), { Q12(0) }, 244, 266 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true), { Q12(8) }, NO_VALUE, 267 },
    { Anim_Update1, ANIM_STATUS(17, true), false, NO_VALUE, { Q12(0) }, 267, 276 },
    { Anim_Update2, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true), { Q12(4) }, NO_VALUE, 277 },
    { Anim_Update1, ANIM_STATUS(18, true), false, NO_VALUE, { Q12(0) }, 277, 292 },
    { Anim_Update2, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true), { Q12(16) }, NO_VALUE, 147 },
    { Anim_Update1, ANIM_STATUS(19, true), false, NO_VALUE, { Q12(0) }, 147, 148 },
    { Anim_Update2, ANIM_STATUS(20, false), false, ANIM_STATUS(20, true), { Q12(16) }, NO_VALUE, 153 },
    { Anim_Update1, ANIM_STATUS(20, true), false, NO_VALUE, { Q12(0) }, 153, 154 },
    { Anim_Update2, ANIM_STATUS(21, false), false, ANIM_STATUS(21, true), { Q12(16) }, NO_VALUE, 136 },
    { Anim_Update0, ANIM_STATUS(21, true), false, ANIM_STATUS(12, false), { Q12(16) }, 136, 147 },
    { Anim_Update2, ANIM_STATUS(22, false), false, ANIM_STATUS(22, true), { Q12(16) }, NO_VALUE, 148 },
    { Anim_Update0, ANIM_STATUS(22, true), false, ANIM_STATUS(13, false), { Q12(8) }, 148, 153 },
    { Anim_Update2, ANIM_STATUS(23, false), false, ANIM_STATUS(23, true), { Q12(4) }, NO_VALUE, 168 },
    { Anim_Update0, ANIM_STATUS(23, true), false, ANIM_STATUS(11, false), { Q12(0) }, 168, 174 },
    { Anim_Update2, ANIM_STATUS(24, false), false, ANIM_STATUS(24, true), { Q12(0) }, NO_VALUE, 50 },
    { Anim_Update1, ANIM_STATUS(24, true), false, NO_VALUE, { Q12(0) }, 50, 51 },
    { Anim_Update2, ANIM_STATUS(25, false), false, ANIM_STATUS(25, true), { Q12(0) }, NO_VALUE, 86 },
    { Anim_Update1, ANIM_STATUS(25, true), false, NO_VALUE, { Q12(0) }, 86, 87 },
    { Anim_Update2, ANIM_STATUS(26, false), false, ANIM_STATUS(26, true), { Q12(0) }, NO_VALUE, 97 },
    { Anim_Update1, ANIM_STATUS(26, true), false, NO_VALUE, { Q12(0) }, 97, 98 }
};*/

void Ai_HangedScratcher_Update(s_SubCharacter* scratcher, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_HangedScratcher_Init(s_SubCharacter* scratcher);

void sharedFunc_800CFF74_5_s00(s_SubCharacter* scratcher);

void Ai_HangedScratcher_ControlUpdate(s_SubCharacter* scratcher);

void Ai_HangedScratcher_Control_16(s_SubCharacter* scratcher);

void Ai_HangedScratcher_Control_1(s_SubCharacter* scratcher);

void Ai_HangedScratcher_Control_2(s_SubCharacter* scratcher);

void sharedFunc_800D26D8_5_s00(s_SubCharacter* scratcher);

void sharedFunc_800D2844_5_s00(s_SubCharacter* scratcher, s_AnmHeader*, GsCOORDINATE2*);

void sharedFunc_800D2C18_5_s00(s_SubCharacter* scratcher);

void sharedFunc_800D3300_5_s00(s_SubCharacter* scratcher);

#endif
