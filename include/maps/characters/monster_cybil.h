#ifndef _MAPS_CHARACTERS_MONSTERCYBIL_H
#define _MAPS_CHARACTERS_MONSTERCYBIL_H

extern s16     D_800EA776;
extern s16     D_800EA7D4;
extern s16     D_800EA7D6;
extern s16     D_800EA816;
extern s16     D_800EA836;
extern s16     D_800EA856; // Keyframe index.
extern s16     D_800EA894;
extern s16     D_800EA896; // Relative keyframe?
extern s16     D_800EBB48;
extern s16     D_800EBB4A;
extern s_Model g_MonsterCybil_ExtraModel; // Some kind of attachment or another `s_SubCharacter` instance?
extern VECTOR  D_800ED560;
extern VECTOR3 D_800ED570;

void func_800D87B0(s_SubCharacter* monsterCybil);

void func_800D8848(s_Model* modelUpper);

s32 func_800D8898(s_AnimInfo* animInfo);

void MonsterCybil_Update(s_SubCharacter* monsterCybil, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords);

void MonsterCybil_Init(s_SubCharacter* monsterCybil, s_Model* modelUpper);

void func_800D8A90(s_SubCharacter* monsterCybil);

void func_800D8B14(s_SubCharacter* monsterCybil, s_Model* modelUpper);

void func_800D8D7C(s_SubCharacter* monsterCybil, s_Model* modelUpper, GsCOORDINATE2* boneCoords);

void func_800D9790(s_SubCharacter* monsterCybil, s_Model* modelUpper);

void func_800D99E4(s_SubCharacter* monsterCybil, s_Model* modelUpperUpper, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords);

void func_800D9AAC(s_SubCharacter* monsterCybil, s_Model* modelUpper);

void func_800D9AB4(s_SubCharacter* monsterCybil, s_Model* modelUpper, GsCOORDINATE2* boneCoords);

void func_800DA9C8(s_SubCharacter* monsterCybil, s_Model* modelUpper, GsCOORDINATE2* boneCoords);

void func_800DB4CC(s_SubCharacter* monsterCybil, s_Model* modelUpper, GsCOORDINATE2* boneCoords);

bool func_800DB6FC(VECTOR3* pos);

void func_800DB748(s_SubCharacter* monsterCybil);

bool func_800DB81C(s_SubCharacter* monsterCybil);

s32 func_800DB930(void);

s32 func_800DBA48(s_SubCharacter* monsterCybil);

bool func_800DBD64(s_SubCharacter* monsterCybil);

void func_800DBE5C(s_SubCharacter* monsterCybil);

void func_800DC018(s_SubCharacter* monsterCybil);

#endif
