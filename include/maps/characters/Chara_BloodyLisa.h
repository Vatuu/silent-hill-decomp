#ifndef _MAPS_CHARACTERS_BLOODYLISA_H
#define _MAPS_CHARACTERS_BLOODYLISA_H

extern s32 sharedData_800E2C38_7_s01; // Used by `Ai_BloodyLisa_Init`.

void Ai_BloodyLisa_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_BloodyLisa_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coord);
void Ai_BloodyLisa_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coord);
void Ai_BloodyLisa_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords);
void Ai_BloodyLisa_Init(s_SubCharacter* chara);

#endif
