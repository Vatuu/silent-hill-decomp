#ifndef _MAPS_CHARACTERS_DAHLIA_H
#define _MAPS_CHARACTERS_DAHLIA_H

/** @brief Dahlia character anim infos. */
extern s_AnimInfo DAHLIA_ANIM_INFOS[];

/*s_AnimInfo DAHLIA_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(0, true), false, NO_VALUE, { Q12(30) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(10) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(1, true), false, NO_VALUE, { Q12(5) }, 0, 15 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q12(10) }, NO_VALUE, 16 },
    { Anim_Update1, ANIM_STATUS(2, true), false, NO_VALUE, { Q12(15) }, 16, 44 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q12(10) }, NO_VALUE, 45 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(3, true), { Q12(15) }, 45, 85 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q12(3) }, NO_VALUE, 86 },
    { Anim_Update0, ANIM_STATUS(4, true), false, ANIM_STATUS(4, true), { Q12(2) }, 86, 109 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q12(2) }, NO_VALUE, 110 },
    { Anim_Update0, ANIM_STATUS(5, true), false, ANIM_STATUS(5, true), { Q12(3.5) }, 110, 166 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q12(5) }, NO_VALUE, 176 },
    { Anim_Update0, ANIM_STATUS(6, true), false, ANIM_STATUS(6, true), { Q12(5) }, 176, 226 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q12(15) }, NO_VALUE, 227 },
    { Anim_Update0, ANIM_STATUS(7, true), false, ANIM_STATUS(7, true), { Q12(8) }, 236, 247 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q12(10) }, NO_VALUE, 248 },
    { Anim_Update1, ANIM_STATUS(8, true), false, NO_VALUE, { Q12(5) }, 248, 263 },
    { Anim_Update2, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q12(10) }, NO_VALUE, 264 },
    { Anim_Update0, ANIM_STATUS(9, true), false, ANIM_STATUS(9, true), { Q12(6) }, 264, 304 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(10) }, NO_VALUE, 305 },
    { Anim_Update0, ANIM_STATUS(10, true), false, ANIM_STATUS(10, true), { Q12(10) }, 305, 335 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(10) }, NO_VALUE, 336 },
    { Anim_Update0, ANIM_STATUS(11, true), false, ANIM_STATUS(11, true), { Q12(10) }, 336, 349 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q12(10) }, NO_VALUE, 350 },
    { Anim_Update1, ANIM_STATUS(12, true), false, NO_VALUE, { Q12(10) }, 350, 369 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q12(10) }, NO_VALUE, 370 },
    { Anim_Update0, ANIM_STATUS(13, true), false, ANIM_STATUS(13, true), { Q12(10) }, 370, 395 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q12(10) }, NO_VALUE, 16 },
    { Anim_Update0, ANIM_STATUS(14, true), false, ANIM_STATUS(14, true), { Q12(15) }, 16, 80 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true), { Q12(10) }, NO_VALUE, 81 },
    { Anim_Update0, ANIM_STATUS(15, true), false, ANIM_STATUS(15, true), { Q12(10) }, 81, 96 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true), { Q12(10) }, NO_VALUE, 97 },
    { Anim_Update0, ANIM_STATUS(16, true), false, ANIM_STATUS(16, true), { Q12(10) }, 97, 103 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true), { Q12(10) }, NO_VALUE, 104 },
    { Anim_Update0, ANIM_STATUS(17, true), false, ANIM_STATUS(17, true), { Q12(10) }, 104, 139 },
    { Anim_Update2, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true), { Q12(10) }, NO_VALUE, 140 },
    { Anim_Update1, ANIM_STATUS(18, true), false, NO_VALUE, { Q12(10) }, 140, 155 },
    { Anim_Update2, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true), { Q12(10) }, NO_VALUE, 156 },
    { Anim_Update0, ANIM_STATUS(19, true), false, ANIM_STATUS(19, true), { Q12(10) }, 156, 193 },
    { Anim_Update2, ANIM_STATUS(20, false), false, ANIM_STATUS(20, true), { Q12(10) }, NO_VALUE, 194 },
    { Anim_Update1, ANIM_STATUS(20, true), false, NO_VALUE, { Q12(10) }, 194, 209 },
    { Anim_Update2, ANIM_STATUS(21, false), false, ANIM_STATUS(21, true), { Q12(10) }, NO_VALUE, 210 },
    { Anim_Update0, ANIM_STATUS(21, true), false, ANIM_STATUS(21, true), { Q12(10) }, 210, 228 },
    { Anim_Update2, ANIM_STATUS(22, false), false, ANIM_STATUS(22, true), { Q12(10) }, NO_VALUE, 229 },
    { Anim_Update1, ANIM_STATUS(22, true), false, NO_VALUE, { Q12(10) }, 229, 244 },
    { Anim_Update2, ANIM_STATUS(23, false), false, ANIM_STATUS(23, true), { Q12(10) }, NO_VALUE, 245 },
    { Anim_Update0, ANIM_STATUS(23, true), false, ANIM_STATUS(23, true), { Q12(10) }, 245, 259 },
    { Anim_Update2, ANIM_STATUS(24, false), false, ANIM_STATUS(24, true), { Q12(10) }, NO_VALUE, 260 },
    { Anim_Update0, ANIM_STATUS(24, true), false, ANIM_STATUS(24, true), { Q12(10) }, 260, 296 },
    { Anim_Update2, ANIM_STATUS(25, false), false, ANIM_STATUS(25, true), { Q12(10) }, NO_VALUE, 260 },
    { Anim_Update0, ANIM_STATUS(25, true), false, ANIM_STATUS(24, true), { Q12(0) }, 260, 296 }
};*/

extern s32 sharedData_800D16E0_2_s01; // Used by `Ai_Dahlia_Init`.

void Ai_Dahlia_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Dahlia_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Dahlia_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_Dahlia_AnimStateUpdate(s_SubCharacter* dahlia, GsCOORDINATE2* coords);
void Ai_Dahlia_Init(s_SubCharacter* chara);

#endif
