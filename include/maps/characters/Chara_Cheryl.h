#ifndef _MAPS_CHARACTERS_CHERYL_H
#define _MAPS_CHARACTERS_CHERYL_H

extern s32 D_800DF1CC;

/** Timer. */
extern q19_12 D_800E3A30;

void Ai_Cheryl_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void func_800D802C(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coord);
void func_800D8124(s_SubCharacter* chara, GsCOORDINATE2* coord);
void func_800D8310(s_SubCharacter* chara, GsCOORDINATE2* coords);
bool func_800D8748(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx0, s32 keyframeIdx1, s32 arg4, s32 pitch);
void Ai_Cheryl_Init(s_SubCharacter* chara);

#endif
