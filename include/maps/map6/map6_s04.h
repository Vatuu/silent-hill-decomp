#ifndef _MAPS_MAP6_S04_H
#define _MAPS_MAP6_S04_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk70
#define HAS_PlayerState_Unk113
#define HAS_PlayerState_Unk123
#define HAS_PlayerState_Unk149
#define HAS_PlayerState_Unk150
#define HAS_PlayerState_Unk151
#define HAS_PlayerState_Unk152
#define HAS_PlayerState_Unk160
#define HAS_PlayerState_Unk161
#define HAS_PlayerState_Unk189
#define HAS_PlayerState_Unk162
#define HAS_PlayerState_Unk163
#define HAS_PlayerState_Unk167
#define HAS_PlayerState_Unk168
#define HAS_PlayerState_Unk185
#define HAS_PlayerState_Unk170
#define HAS_PlayerState_Unk188
#define KEYFRAME_PlayerState_Unk167 1347

#define HAS_Chara_MonsterCybil
#define HAS_Chara_Dahlia
#define HAS_Chara_Alessa
#define MAP_CHARA_COUNT 3

#define MAP_FIELD_4C_COUNT 300
#define MAP_BLOOD_SPLAT_COUNT_MAX 150

#include "maps/shared.h"

#define UNK_FS_BUFFER_6 ((s_func_800DE274*)FS_BUFFER_6)

// Used with `FS_BUFFER_6`
typedef struct
{
    u8  field_0[0x4101];
    u8  field_4101[0x214];
    u8  unk_4315[3];
    s32 field_4318;
} s_func_800DE274;

typedef struct
{
    s32     field_0;
    VECTOR  vec_4; // Origin of something.
    VECTOR  vec_14;
    bool    isSlotInUse_24;
    q19_12  field_28;
    s32     field_2C; // Q23.8?
    void    (*funcPtr_30)(struct s_func_800E030C*);
    s32     field_34;
} s_func_800E030C;
STATIC_ASSERT_SIZEOF(s_func_800E030C, 0x38);

typedef struct
{
    s8              unk_0[4];
    VECTOR          field_4;
    s8              unk_14[32];
    u8              field_34[41];
    u8              field_5D[25 * 41];
    u8              field_45E[41];
    s8              unk_487[5];
    s32             field_48C;
    s32             field_490;
    s_func_800E030C field_494[800];
} s_func_800E05C8;

typedef struct
{
    s32            field_0;
    s32            field_4;
    s32            field_8;
    s32            field_C;
    s32            field_10;
    VECTOR3*       field_14;
    SVECTOR*       field_18;
    SVECTOR        field_1C;
    s32            (*field_24)(struct s_800ED848*);
    MATRIX         field_28;
    s32            field_48;
    s32*           field_4C;
    s8             unk_50[8];
    GsCOORDINATE2* field_58;
    s32            field_5C;
    s32            field_60;
    s32            field_64;
    VECTOR3*       field_68;
} s_800ED848;

typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
} s_800CB6AC;

typedef struct
{
    SVECTOR field_0;
    s32     field_8;
    s32     field_C;
} s_800CB69C;

typedef struct
{
    q3_12 field_0; // } Angle.
    q3_12 field_2; // }
    q3_12 field_4; // }
    q3_12 field_6; // }
} s_800EBB58;

extern s_800EBB58 D_800EBB58;
extern s16        D_800EBB5A;

extern s_800CB69C D_800CB69C;

extern s_800CB6AC D_800CB6AC[6];

extern s_800ED848 D_800ED848[16];

extern s_AnimInfo FLAUROS_ANIM_INFOS[];
extern s_AnimInfo PARASITE_ANIM_INFOS[];

extern s16 D_800EA856; // Keyframe index.

extern s32 D_800EBA30;

extern u16 D_800EBA64;

extern s32 D_800EBAA8;

extern u8 D_800EBB60;
extern u8 D_800EBB61;

extern VECTOR3 D_800EBB70;

extern s8 D_800ED543;

extern VECTOR3 D_800ED590;

extern VECTOR3 D_800ED5A0;

extern u8 D_800ED5AC; // g_MapMsgSoundIdx

/** Time. */
extern q19_12 D_800ED5B0;

extern q3_12 D_800ED5B6; // Angle.

extern s_Model g_Ai_MonsterCybil_ExtraModel; // Some kind of attachment or another `s_SubCharacter` instance?

extern s32 D_800ED588;
extern s32 D_800ED58C;

extern s_WorldObjectDesc g_WorldObject_SFlauros;

extern s_WorldObjectModel g_WorldObject0[2];
extern s_WorldObjectModel g_WorldObject1[3];
extern s_WorldObjectModel g_WorldObject2;
extern s_WorldObjectModel g_WorldObject3;
extern s_WorldObjectModel g_WorldObject4[2];
extern s_WorldObjectModel g_WorldObject5;

extern VECTOR3 D_800ED740;

extern s_WorldObjectModel g_WorldObject6[3];
extern s_WorldObjectModel g_WorldObject7[2];
extern s_WorldObjectModel g_WorldObject8;
extern s_WorldObjectDesc g_WorldObject9;

extern u8 D_800ED5AD;
extern s16 D_800ED5B4;
extern u8  D_800ED5B8;
extern u8 D_800ED5F0;
extern u8 D_800ED840;
extern s8 D_800ED841;
extern u16 D_800EBA34[23]; // `g_MapMsgSounds`
extern s16 D_800ED5B4;
extern s16 D_800EA856;

extern s32 D_800CB118[];
extern s32 D_800CB178[];

extern s16       D_800CB208[];
extern s16       D_800CB2A0[];
extern const s32 D_800CB2B4[];
extern const s32 D_800CB2DC[];
extern s16       D_800EA776;
extern s16       D_800EA836;
extern s16       D_800EA894;
extern s16       D_800EA896; // Relative keyframe?
extern s16       D_800EBB48;
extern s16       D_800EBB4A;
extern VECTOR3   D_800ED570;

extern s16 D_800CB238[];
extern s16 D_800EA7D4;
extern s16 D_800EA7D6;
extern s16 D_800EA816;

extern VECTOR D_800ED560;

extern s32 D_800CB250[];
extern s32 D_800CB278[];
extern s16 D_800CB1D8[];

extern const s32 D_800CB304[12][2];
extern const s32 D_800CB364[12][2];
extern const s32 D_800CB3A4[12][2];

extern s32 D_800EAF20[];

extern s32 D_800EB320;
extern s32 D_800EB324;

extern SVECTOR D_800EB328;
extern SVECTOR D_800EB330;

extern s32 D_800EBB4C;
extern s32 D_800EBB50;

extern s32 D_800EB338[];

extern VECTOR3 D_800CB728;
extern s32     D_800EBB54;

extern s_AnimInfo      D_800CC424[];
extern s_UnkStruct3_Mo D_800CC4A4[];

extern s32 D_800EBAAC[10];
extern s32 D_800EBAD4[10];
extern q3_12 D_800EBAFC[10]; // Angles.

extern q19_12 D_800EBB10[4]; // Timers?
extern q19_12 D_800EBB20[4];
extern q20_12 D_800EBB30;    // Timer.
extern u8  D_800EBB34;       // Counter.

extern s16 D_800EBB36;
extern s16 D_800EBB38;

extern u8 D_800EBB7C;

void func_800E0164(void);

void func_800E05C8(s32 x, s32 y, s32 val);

void func_800E068C(void);

s32 func_800E0878(s32 arg0, s32 arg1);

void func_800E08B8(void);

void func_800E0BB0(void);

void func_800E0C58(void);

void func_800E0CCC(VECTOR* arg0, s32 arg1);

void func_800E0D8C(VECTOR3* arg0);

void func_800E0DC4(s32 arg0, s32 arg1);

void func_800E0FAC(s32 arg0);

void func_800D87B0(s_SubCharacter* chara);

void func_800D8848(s_Model* model);

s32 func_800D8898(s_AnimInfo* animInfo);

void Ai_MonsterCybil_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_MonsterCybil_Init(s_SubCharacter* chara, s_Model* extraModel);

void func_800D8A90(s_SubCharacter* chara);

void func_800D8B14(s_SubCharacter* chara, s_Model* model);

void func_800D8D7C(s_SubCharacter* chara, s_Model* model, GsCOORDINATE2* coords);

void func_800D9790(s_SubCharacter* chara, s_Model* model);

void func_800D99E4(s_SubCharacter* chara, s_Model* modelUpper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800D9AAC(s_SubCharacter* chara, s_Model* model);

void func_800D9AB4(s_SubCharacter* chara, s_Model* model, GsCOORDINATE2* coords);

void func_800DA9C8(s_SubCharacter* chara, s_Model* model, GsCOORDINATE2* coords);

s32 func_800DBA48(s_SubCharacter* chara);

s32 func_800DBD64(s_SubCharacter* chara);

void func_800DB4CC(s_SubCharacter* chara, s_Model* model, GsCOORDINATE2* coord);

bool func_800DB81C(s_SubCharacter* chara);

s32 func_800DB930(void);

void func_800DB4CC(s_SubCharacter*, s_Model*, GsCOORDINATE2*);

s32 func_800DB6FC(VECTOR3* pos);

void func_800DB748(s_SubCharacter* chara);

void func_800DC018(s_SubCharacter* chara);

void Ai_Flauros_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Parasite_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800DE26C(void);

void func_800DE274(void);

void func_800DBE5C(s_SubCharacter* chara);

s32 func_800DE350(s32 arg0);

// TODO: Returns `PACKET*` but that causes mismatches?
void* func_800DE380(GsOT_TAG* arg0, PACKET* arg1);

void func_800DE5CC(void);

void func_800DE62C(void);

void func_800DE8F0(MATRIX* mat, SVECTOR* arg1, SVECTOR3* result);

void func_800DE95C(void);

s_800ED848* func_800DEA4C(void);

void func_800DEA94(s_800ED848* arg0);

void func_800DEAA8(s32 arg0);

s32 func_800DEB1C(s_800ED848* arg0);

void func_800DEC3C(VECTOR3*, SVECTOR3*); // Assumed return type.

void func_800DED30(void);

void func_800DED50(MATRIX* arg0, GsCOORDINATE2* arg1, s32 arg2);

bool func_800DEDEC(s_800ED848* arg0);

void func_800DEF50(VECTOR3*, GsCOORDINATE2*, s32*); // Assumed return type.

void func_800DF134(void);

void func_800DF160(MATRIX* arg0, VECTOR3* arg1, VECTOR3* arg2);

void func_800DF2F0(MATRIX* arg0, VECTOR3* arg1, VECTOR3* arg2);

bool func_800DF41C(s_800ED848* arg0);

void func_800DF5B0(VECTOR3*, VECTOR3*); // Assumed return type.

void func_800DF618(void);

void func_800DF64C(void);

s32 func_800DF670(s32 arg0);

PACKET* func_800DF6C4(GsOT_TAG* ot, PACKET* packet, MATRIX* mat);

void func_800DFA38(MATRIX* mat);

void func_800DFB44(void);

bool func_800DFBB0(s_800ED848* arg0);

void func_800DFC94(s32* arg0);

void func_800DFD08(void);

// TODO: Returns `PACKET*` but that causes mismatches?
void* func_800DFD3C(GsOT_TAG* ot, PACKET* packet, MATRIX* mat, s32 arg3, s32 arg4);

void func_800E00F4(void);

void func_800E01F4(void);

void func_800E0204(void);

void func_800E02E0(void);

s_func_800E030C* func_800E030C(void);

void func_800E0358(s_func_800E030C* arg0); // Unknown return type/args.

void func_800E03C4(const VECTOR3* from, const VECTOR3* to, q19_12 dist, s32 arg3);

void func_800E0FAC(s32); // Assumed return type.

/** @brief Multiplies two fixed-point Q19.12 values and returns the integer part with stochastic rounding.
 *
 * The fractional part determines the probability of rounding up:
 * Fractions closer to 0 rarely round up, fractions closer to 0x1000 almost always round up.
 * Prevents systematic bias and error accumulation over many operations.
 *
 * @param val0 First value.
 * @param val1 Second value.
 * @return Probabilistically rounded integer result of the multiplication.
 */
s32 func_800E0F28(q19_12 val0, q19_12 val1);

void func_800E10F8(void);

void func_800E15FC(s_SubCharacter* player, s_SubCharacter* npc, bool);

void func_800E1CA0(void);

void func_800E1D48(void);

/** Cutscene. */
void func_800E1D50(void);

void func_800E219C(void);

void func_800E2724(void);

void func_800E2950(void);

void MapEvent_CutsceneCybilDeath(void);

void func_800E3244(void);

void func_800E3EF4(void);

void func_800E558C(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

void func_800E636C(void); // Assumed types.

void func_800E6CB8(void);

void func_800E7204(void); // Assumed types.

void func_800E73B4(q19_12 arg0);

void func_800E74C4(void);

void func_800E75B8(s32 arg0, VECTOR3* arg1, s32 arg2, s32 arg3, s32 arg4); // Assumed types.

void func_800E7944(u32 arg0);

#endif
