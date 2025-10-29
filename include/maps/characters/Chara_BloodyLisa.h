#ifndef _MAPS_CHARACTERS_BLOODYLISA_H
#define _MAPS_CHARACTERS_BLOODYLISA_H

extern s32 sharedData_800E2C38_7_s01; // Used by `Ai_BloodyLisa_Init`.

void Ai_BloodyLisa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void sharedFunc_800D595C_7_s01(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coord);
void sharedFunc_800D59A4_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coord);
void sharedFunc_800D5B3C_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_BloodyLisa_Init(s_SubCharacter* chara);

#endif
