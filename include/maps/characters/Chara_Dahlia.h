#ifndef _MAPS_CHARACTERS_DAHLIA_H
#define _MAPS_CHARACTERS_DAHLIA_H

/** @brief Dahlia character animation indices. */
typedef enum _DahliaAnim
{
    DahliaAnim_Still = 0,
    DahliaAnim_1     = 1,
    DahliaAnim_2     = 2,
    DahliaAnim_3     = 3,
    DahliaAnim_4     = 4,
    DahliaAnim_5     = 5,
    DahliaAnim_6     = 6,
    DahliaAnim_7     = 7,
    DahliaAnim_8     = 8,
    DahliaAnim_9     = 9,
    DahliaAnim_10    = 10,
    DahliaAnim_11    = 11,
    DahliaAnim_12    = 12,
    DahliaAnim_13    = 13,
    DahliaAnim_14    = 14,
    DahliaAnim_15    = 15,
    DahliaAnim_16    = 16,
    DahliaAnim_17    = 17,
    DahliaAnim_18    = 18,
    DahliaAnim_19    = 19,
    DahliaAnim_20    = 20,
    DahliaAnim_21    = 21,
    DahliaAnim_22    = 22,
    DahliaAnim_23    = 23,
    DahliaAnim_24    = 24,
    DahliaAnim_25    = 25
} e_DahliaAnim;

/** @brief Dahlia character anim infos. */
extern s_AnimInfo DAHLIA_ANIM_INFOS[];

/*s_AnimInfo DAHLIA_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(DahliaAnim_Still, false), false, ANIM_STATUS(DahliaAnim_Still, false), { Q12(0.0f) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(DahliaAnim_Still, true), false, NO_VALUE, { Q12(30.0f) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_1, false), false, ANIM_STATUS(DahliaAnim_1, true), { Q12(10.0f) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(DahliaAnim_1, true), false, NO_VALUE, { Q12(5.0f) }, 0, 15 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_2, false), false, ANIM_STATUS(DahliaAnim_2, true), { Q12(10.0f) }, NO_VALUE, 16 },
    { Anim_Update1, ANIM_STATUS(DahliaAnim_2, true), false, NO_VALUE, { Q12(15.0f) }, 16, 44 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_3, false), false, ANIM_STATUS(DahliaAnim_3, true), { Q12(10.0f) }, NO_VALUE, 45 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_3, true), false, ANIM_STATUS(DahliaAnim_3, true), { Q12(15.0f) }, 45, 85 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_4, false), false, ANIM_STATUS(DahliaAnim_4, true), { Q12(3.0f) }, NO_VALUE, 86 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_4, true), false, ANIM_STATUS(DahliaAnim_4, true), { Q12(2.0f) }, 86, 109 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_5, false), false, ANIM_STATUS(DahliaAnim_5, true), { Q12(2.0f) }, NO_VALUE, 110 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_5, true), false, ANIM_STATUS(DahliaAnim_5, true), { Q12(3.5f) }, 110, 166 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_6, false), false, ANIM_STATUS(DahliaAnim_6, true), { Q12(5.0f) }, NO_VALUE, 176 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_6, true), false, ANIM_STATUS(DahliaAnim_6, true), { Q12(5.0f) }, 176, 226 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_7, false), false, ANIM_STATUS(DahliaAnim_7, true), { Q12(15.0f) }, NO_VALUE, 227 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_7, true), false, ANIM_STATUS(DahliaAnim_7, true), { Q12(8.0f) }, 236, 247 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_8, false), false, ANIM_STATUS(DahliaAnim_8, true), { Q12(10.0f) }, NO_VALUE, 248 },
    { Anim_Update1, ANIM_STATUS(DahliaAnim_8, true), false, NO_VALUE, { Q12(5.0f) }, 248, 263 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_9, false), false, ANIM_STATUS(DahliaAnim_9, true), { Q12(10.0f) }, NO_VALUE, 264 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_9, true), false, ANIM_STATUS(DahliaAnim_9, true), { Q12(6.0f) }, 264, 304 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_10, false), false, ANIM_STATUS(DahliaAnim_10, true), { Q12(10.0f) }, NO_VALUE, 305 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_10, true), false, ANIM_STATUS(DahliaAnim_10, true), { Q12(10.0f) }, 305, 335 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_11, false), false, ANIM_STATUS(DahliaAnim_11, true), { Q12(10.0f) }, NO_VALUE, 336 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_11, true), false, ANIM_STATUS(DahliaAnim_11, true), { Q12(10.0f) }, 336, 349 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_12, false), false, ANIM_STATUS(DahliaAnim_12, true), { Q12(10.0f) }, NO_VALUE, 350 },
    { Anim_Update1, ANIM_STATUS(DahliaAnim_12, true), false, NO_VALUE, { Q12(10.0f) }, 350, 369 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_13, false), false, ANIM_STATUS(DahliaAnim_13, true), { Q12(10.0f) }, NO_VALUE, 370 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_13, true), false, ANIM_STATUS(DahliaAnim_13, true), { Q12(10.0f) }, 370, 395 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_14, false), false, ANIM_STATUS(DahliaAnim_14, true), { Q12(10.0f) }, NO_VALUE, 16 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_14, true), false, ANIM_STATUS(DahliaAnim_14, true), { Q12(15.0f) }, 16, 80 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_15, false), false, ANIM_STATUS(DahliaAnim_15, true), { Q12(10.0f) }, NO_VALUE, 81 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_15, true), false, ANIM_STATUS(DahliaAnim_15, true), { Q12(10.0f) }, 81, 96 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_16, false), false, ANIM_STATUS(DahliaAnim_16, true), { Q12(10.0f) }, NO_VALUE, 97 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_16, true), false, ANIM_STATUS(DahliaAnim_16, true), { Q12(10.0f) }, 97, 103 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_17, false), false, ANIM_STATUS(DahliaAnim_17, true), { Q12(10.0f) }, NO_VALUE, 104 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_17, true), false, ANIM_STATUS(DahliaAnim_17, true), { Q12(10.0f) }, 104, 139 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_18, false), false, ANIM_STATUS(DahliaAnim_18, true), { Q12(10.0f) }, NO_VALUE, 140 },
    { Anim_Update1, ANIM_STATUS(DahliaAnim_18, true), false, NO_VALUE, { Q12(10.0f) }, 140, 155 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_19, false), false, ANIM_STATUS(DahliaAnim_19, true), { Q12(10.0f) }, NO_VALUE, 156 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_19, true), false, ANIM_STATUS(DahliaAnim_19, true), { Q12(10.0f) }, 156, 193 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_20, false), false, ANIM_STATUS(DahliaAnim_20, true), { Q12(10.0f) }, NO_VALUE, 194 },
    { Anim_Update1, ANIM_STATUS(DahliaAnim_20, true), false, NO_VALUE, { Q12(10.0f) }, 194, 209 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_21, false), false, ANIM_STATUS(DahliaAnim_21, true), { Q12(10.0f) }, NO_VALUE, 210 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_21, true), false, ANIM_STATUS(DahliaAnim_21, true), { Q12(10.0f) }, 210, 228 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_22, false), false, ANIM_STATUS(DahliaAnim_22, true), { Q12(10.0f) }, NO_VALUE, 229 },
    { Anim_Update1, ANIM_STATUS(DahliaAnim_22, true), false, NO_VALUE, { Q12(10.0f) }, 229, 244 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_23, false), false, ANIM_STATUS(DahliaAnim_23, true), { Q12(10.0f) }, NO_VALUE, 245 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_23, true), false, ANIM_STATUS(DahliaAnim_23, true), { Q12(10.0f) }, 245, 259 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_24, false), false, ANIM_STATUS(DahliaAnim_24, true), { Q12(10.0f) }, NO_VALUE, 260 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_24, true), false, ANIM_STATUS(DahliaAnim_24, true), { Q12(10.0f) }, 260, 296 },
    { Anim_Update2, ANIM_STATUS(DahliaAnim_25, false), false, ANIM_STATUS(DahliaAnim_25, true), { Q12(10.0f) }, NO_VALUE, 260 },
    { Anim_Update0, ANIM_STATUS(DahliaAnim_25, true), false, ANIM_STATUS(DahliaAnim_24, true), { Q12(0.0f) }, 260, 296 }
};*/

extern s32 sharedData_800D16E0_2_s01; // Used by `Ai_Dahlia_Init`.

void Ai_Dahlia_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Dahlia_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Dahlia_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Dahlia_AnimStateUpdate(s_SubCharacter* dahlia, GsCOORDINATE2* coords);
void Ai_Dahlia_Init(s_SubCharacter* chara);

#endif
