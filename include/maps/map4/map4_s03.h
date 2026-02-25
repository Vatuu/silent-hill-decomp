#ifndef _MAPS_MAP4_S03_H
#define _MAPS_MAP4_S03_H

#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk123
#define HAS_PlayerState_Unk128
#define HAS_PlayerState_Unk129
#define KEYFRAME_PlayerState_Unk123 877

#define MAP_ROOM_MIN_X Q12(-240.0f)
#define MAP_ROOM_MAX_X Q12(240.0f)
#define MAP_ROOM_MIN_Z Q12(-120.0f)
#define MAP_ROOM_MAX_Z Q12(240.0f)

#define MAP_FIELD_4C_COUNT 250
#define MAP_BLOOD_SPLAT_COUNT_MAX 150

#include "maps/shared.h"

#define COPY_GT4_DATA(poly, idx, ptr0, ptr1, ptr2, n) \
{                                                     \
    u16* ptr4 = &(ptr0)[(idx)];                       \
    s32* ptr5 = &(ptr1)[(idx)];                       \
    s32* ptr6 = &(ptr2)[(idx)];                       \
                                                      \
    *(u16*)&(poly)->u##n = *ptr4;                     \
    *(s32*)&(poly)->x##n = *ptr5;                     \
    *(s32*)&(poly)->r##n = *ptr6;                     \
}

typedef struct
{
    SVECTOR field_0; // } Note: Not sure if these are actually `SVECTOR`.
    SVECTOR field_8; // } That struct fits and works with some copy code, but could be a custom struct of 4 `u16`s.
} s_800DB7D4;
STATIC_ASSERT_SIZEOF(s_800DB7D4, 0x10);

typedef struct
{
    SVECTOR field_0[4];
    u8      field_20;
    u8      field_21;
    u8      field_22;
    u8      field_23;
    s32     field_24;
    s32     field_28;
    s32     field_2C;
    s32     field_30;
    s16     field_34;
    s16     field_36;
} s_800E06A0;
STATIC_ASSERT_SIZEOF(s_800E06A0, 0x38);

typedef struct
{
    s32                field_0;
    s32                field_4;
    s_800E06A0         field_8[10];
    s_WorldObjectModel objRef_238;
    s8                 unk_254[4];
    VECTOR3            field_258;
} s_800E0698;
STATIC_ASSERT_SIZEOF(s_800E0698, 0x264);

typedef struct
{
    s32     field_0;
    s32     field_4;
    s_SubCharacter* chara_8;
    VECTOR3 position_C;
    void    (*funcptr_18)(struct s_800E0930*);
} s_800E0930;

typedef struct
{
    q19_12 x_0;
    q19_12 z_4;
    MATRIX world_8;
} s_800E0988;

typedef struct
{
    s32     field_0;
    s32     field_4;
    q19_12  field_8;
    s16     field_C;
    s16     field_E;
    s16     field_10;
    s8      unk_12[2];
    SVECTOR field_14;
    MATRIX  field_1C;
    s32     field_3C;
    u8      field_40[133]; // Type assumed.
    s32     (*field_C8)(struct s_800DF580*);
    q19_12  field_CC;
    s32     field_D0;
    s32     field_D4;
} s_800DF580;

typedef struct
{
    q19_12  timer_0;
    q19_12  field_4;
    SVECTOR field_8;
    s8      unk_10[4];
} s_800E0300;

typedef struct
{
    s32     field_0;
    SVECTOR field_4;
    s32     field_C;
    s32     field_10;
    s32     field_14;
    s8      unk_18[4];
} s_800E0440;

typedef struct
{
    q19_12  field_0;
    SVECTOR field_4;
    q19_12  field_C;
    q19_12  field_10;
    s8      unk_14[4];
} s_800E0900;

typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
} s_800DB210;

typedef struct
{
    u8  field_0;
    s8  unk_1;
    u16 field_2;
    u8  field_4;
    u8  field_5;
    u8  field_6;
    u8  field_7;
    u8  field_8;
    u8  field_9;
} s_800DB874;

extern s_800DB874 D_800DB874[];

extern s_800DB210 D_800DB210;

extern SVECTOR3 D_800DAE60;

extern u8 D_800DAE68[];

extern s_800DF580 D_800DF580[];

extern s_800E0300 D_800E0300[16];

extern s_800E0440 D_800E0440[];

extern s_800E0900 D_800E0900[];

extern s_800E0930 D_800E0930[3];

extern s_800E0988 D_800E0988[];

extern s_800DB7D4 D_800DB7D4;
extern s_800DB7D4 D_800DB7E4[3][3];

extern s_AnimInfo TWINFEELER_ANIM_INFOS[];

extern s32 D_800DB914; // } RNG related values?
extern s32 D_800DB918; // }

extern s_FsImageDesc D_800DB91C;

extern u16 D_800DB92C;

extern u16 D_800DB9E0;
extern u8  D_800DB9E2;

extern s_WorldObjectDesc g_WorldObject_Fence;
extern s_WorldObjectDesc g_WorldObject_Mal5_21;
extern s_WorldObjectModel   g_WorldObject_Mal6[2];
extern VECTOR3           g_WorldObject_UnkPos;
extern SVECTOR3          g_WorldObject_UnkRot;
extern s_WorldObjectDesc g_WorldObject_SavePad;
extern s_WorldObjectModel   g_CommonWorldObjects[6];
extern s_WorldObjectModel   D_800E08D0;
extern s_WorldObjectPose g_CommonWorldObjectPoses[3]; // 0x800DB930
extern VECTOR3 D_800DB7C8;
extern SVECTOR D_800DB924;

extern u32 D_800DF554;
extern u32 D_800DF558;
extern u32 D_800DF55C;
extern u32 D_800DF560;
extern u32 D_800DF564;
extern u32 D_800DF568;
extern u32 D_800DF56C;
extern u32 D_800DF570;

extern s32 D_800DAA44;
extern s32 D_800DAA48;
extern s32 D_800DAA4C;
extern s32 D_800DAA50;
extern s32 D_800DAA54;
extern u16 D_800DB980[];

extern s32 D_800E05A8;   // Angle?
extern q3_12 D_800E05AC; // Angle?
extern u16 D_800E05AE;

extern u8 D_800E05E0;
extern u8 D_800E05E1;
extern u8 D_800E05E2;

extern s_800E0698 D_800E0698;

extern SVECTOR3 D_800DAE58;

// Q19.12
extern VECTOR3 D_800E08F0;

extern s32 D_800DAA58[];

extern s_SfxVolume D_800DB1F8[6];

extern SVECTOR3 D_800DAE78;

extern u8 D_800DAE80[];

extern s16 D_800DB1D8[];

extern q3_12 D_800DB1E0[]; // Y positions?

extern s16 D_800DB1E8[];

extern s16 D_800DB1F0[];

extern u8 D_800DB190[];

extern u8 D_800DB1A8[];

extern u8 D_800DB220[][3];

extern SVECTOR D_800CA788;

extern s8 D_800DB238[][6];

extern s32 D_800DB27C[];

extern s32 D_800DB2FC[];

extern u8 D_800DB3A0[];

extern s_func_8006CF18 D_800E04A0;

void func_800D078C(void);

void func_800D0840(void);

void func_800D0C50(SVECTOR* rot, MATRIX* mat);

// TODO: Could be `SVECTOR3`, need to check callers.
void func_800D0CA0(q19_12 rotY, SVECTOR* pos);

// TODO: Could be `SVECTOR3`, need to check callers.
void func_800D0D6C(MATRIX* out, SVECTOR* pos, q19_12 rotY);

// TODO: Could be `SVECTOR3`/VECTOR3`, need to check callers.
void func_800D0DE4(SVECTOR* out, VECTOR* in, q19_12 headingAngle, q19_12 dist);

void func_800D0EC0(u8* buf, s32 w, s32 h);

s32 func_800D0F40(s32 arg0, s32 arg1, s32 arg2);

void func_800D13B4(u8* arg0, s32 arg1, s32 arg2, s32 arg3);

// TODO: Could be `SVECTOR3`, need to check callers.
void func_800D1478(SVECTOR* arg0, s32 arg1, q19_12 headingAngle, s32 mode, SVECTOR* arg4);

void func_800D19AC(VECTOR3* vec);

void func_800D19CC(VECTOR3* vec);

void func_800D17FC(void);

void func_800D185C(s32 arg0, s32 arg1);

s_800DF580* func_800D1900(VECTOR* arg0, s32 arg1);

bool func_800D19F0(s_800DF580* arg0);

void func_800D1AFC(void);

void func_800D1C48(void);

void func_800D1D3C(GsOT_TAG* tag, SVECTOR3* arg1, MATRIX* arg2, s32 arg3);

void func_800D1FF4(GsOT_TAG* tag);

void func_800D2150(VECTOR* arg0, s32 arg1);

void func_800D21AC(GsOT_TAG* ot, MATRIX* arg1, s32 arg2, s32 arg3);

void func_800D35DC(SVECTOR* rot);

void func_800D33D0(void);

void func_800D2ED0(GsOT_TAG* arg0);

void func_800D2D28(GsOT_TAG* arg0);

void func_800D2120(void);

void func_800D2684(VECTOR* arg0, s32 arg1);

void func_800D26FC(VECTOR* arg0, s32 arg1);

void func_800D2790(GsOT_TAG* arg0, MATRIX* arg1, s32 arg2, s32 arg3);

void func_800D2CC8(void);

void func_800D2CEC(void);

void func_800D3114(void);

void func_800D326C(void);

void func_800D3428(void);

void func_800D354C(VECTOR3* arg0);

void func_800D3694(s_SubCharacter* twinfeeler, s_AnmHeader* arg1, GsCOORDINATE2* arg2);

void func_800D3B98(s_SubCharacter* chara);

void Twinfeeler_TextureLoad(void);

/** @brief Translates a vector in the direction of a given Y axis heading angle along the XZ plane.
 *
 * @param outVec Output vector (Q19.12).
 * @param inVec Input vector (Q19.12).
 * @param headingAngle Y axis heading angle.
 * @param dist Translation distance.
 */
void Math_Vector3Translate(VECTOR3* outVec, const VECTOR3* inVec, q19_12 headingAngle, q19_12 dist);

void func_800D3114(void); // Assumed args/return type.

void func_800D326C(void);

s_800E0930* func_800D344C(s_SubCharacter* chara, void (*funcptr)());

void func_800D3504(s_SubCharacter* chara);

void func_800D3528(s_SubCharacter* chara);

void func_800D354C(VECTOR3*);

void func_800D3694(s_SubCharacter* twinfeeler, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800D3AE0(s_SubCharacter* chara, s32 soundIdx);

u32 func_800D3B1C(void);

void func_800D3B44(bool disableDamage);

void func_800D3B68(s_SubCharacter* twinfeeler);

void func_800D3B74(s_SubCharacter* twinfeeler);

void func_800D3CBC(s_SubCharacter* twinfeeler);

bool Twinfeeler_Init(s_SubCharacter* twinfeeler);

void func_800D3E58(s_SubCharacter* twinfeeler);

void func_800D3FB0(s_SubCharacter* twinfeeler);

void func_800D3FD8(s_SubCharacter* twinfeeler);

void func_800D4000(s_SubCharacter* twinfeeler);

void Twinfeeler_Control_11(s_SubCharacter* twinfeeler);

void func_800D46E0(VECTOR3* vec0, VECTOR3* vec1);

bool func_800D4924(VECTOR3* vec, q19_12 angle); // Assumed return type.

void Twinfeeler_Control_10(s_SubCharacter* twinfeeler);

void Twinfeeler_Control_7(s_SubCharacter* twinfeeler);

void Twinfeeler_Control_4(s_SubCharacter* twinfeeler);

bool func_800D4C0C(u32 row, s32 col);

u16 func_800D4C5C(u8* arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_800D4D80(s32 arg0, s32 arg1);

u32 func_800D4DD8(void);

u16 func_800D4E00(s32 arg0, s32 arg1, s32 arg2);

s32 func_800D4488(VECTOR3*, s32);

void Twinfeeler_Control_12(s_SubCharacter* twinfeeler);

void Twinfeeler_Control_13(s_SubCharacter* twinfeeler);

void func_800D43AC(s_SubCharacter* twinfeeler, s32 arg1);

void Twinfeeler_Control_2(s_SubCharacter* twinfeeler);

void Twinfeeler_ControlUpdate(s_SubCharacter* twinfeeler, GsCOORDINATE2* coords);

void func_800D54B4(s_SubCharacter* chara, GsCOORDINATE2*);

s32 func_800D4558(q19_12 angle, s32 arg1, s32 arg2);

void Twinfeeler_Control_5(s_SubCharacter* twinfeeler);

void Twinfeeler_Control_6(s_SubCharacter* twinfeeler, GsCOORDINATE2* arg1);

bool func_800D48CC(s32 arg0, s32 arg1);

void func_800D55C8(s_SubCharacter*);

void func_800D5888(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800D5904(s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800D59EC(s_SubCharacter*, GsCOORDINATE2*);

void func_800D5B6C(s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800D5BC8(s_SubCharacter* chara, GsCOORDINATE2* coords);

bool func_800D5BF8(s32 arg0, s32 arg1, s32 arg2, u16* arg3);

void func_800D5DF4(s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800D5E30(s_SubCharacter* twinfeeler, GsCOORDINATE2* coords);

void Twinfeeler_Update(s_SubCharacter* twinfeeler, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

/** @brief Handles a First Aid Kit or Rifle Shells item pickup event. */
void MapEvent_CommonItemTake(void);

void func_800D6704(void);

void func_800D6774(void);

void func_800D6F24(void);

s16 func_800D7394(void);

void func_800D7408(void);

void func_800D7450(void);

void func_800D7548(void);

void func_800D761C(s_800E06A0* arg0, s_800DB7D4* arg1, s8 arg2, s32 arg3);

void func_800D76BC(s32 arg0);

bool func_800D76E8(void); // Assumed return type.

void func_800D7718(void);

void func_800D7808(s_800E06A0* arg0, s32 arg1); // Assumed types.

bool func_800D78D4(s_800E06A0* arg0);

bool func_800D81FC(s_800E06A0* arg0, s32 arg1);

bool func_800D8230(s_800E06A0* arg0, s32 arg1, s32 arg2);

bool func_800D826C(s_800E06A0* arg0, s32 arg1, s32 arg2);

void func_800D88C8(s_800E06A0*, u8); // Assumed types.

void func_800D8FC0(void);

void func_800D960C(void);

void func_800D9824(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

void func_800DA3E0(void);

void func_800D0FD4(s32* ord, void* arg1, u8* arg2, MATRIX* arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 abr);

void func_800D1604(GsOT_TAG* ot, int arg1);

void func_800D3E18(s_SubCharacter* chara);

void Twinfeeler_Control_8(s_SubCharacter* twinfeeler, GsCOORDINATE2* coords);

s32 func_800D4E78(s32 arg0, s32 arg1);

void Twinfeeler_Control_9(s_SubCharacter* twinfeeler);

void func_800D54B4(s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800D55C8(s_SubCharacter* chara);

void func_800D59C0(s_LinkedBone* bone);

void func_800D59EC(s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800D5C3C(s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800D5E30(s_SubCharacter* chara, GsCOORDINATE2* coords);

s32 func_800D78F4(s_800E06A0* arg0, s32 arg1);

s32 func_800D7AE0(s_800E06A0* arg0);

void func_800D7F1C(s_800E06A0* arg0);

bool func_800D8354(s_800E06A0* arg0, s32 arg1, s32 arg2);

bool func_800D84C0(s_800E06A0* arg0, s32 arg1, s32 arg2);

bool func_800D85E4(s_800E06A0* arg0, s32 arg1);

bool func_800D8620(s_800E06A0* arg0, s32 arg1, s32 arg2);

s32 func_800D87AC(s_800E06A0* arg0);

q19_12 func_800D8874(void);

void func_800DA718(void);

#endif
