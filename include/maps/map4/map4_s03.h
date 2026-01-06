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

typedef struct
{
    SVECTOR field_0; // } Note: Not sure if these are actually `SVECTOR`.
    SVECTOR field_8; // } That struct fits and works with some copy code, but could be a custom struct of 4 `u16`s.
} s_800DB7D4;
STATIC_ASSERT_SIZEOF(s_800DB7D4, 0x10);

typedef struct
{
    SVECTOR field_0;  // Values copied from `s_800DB7D4::field_0`.
    SVECTOR field_8;  // Values copied from `s_800DB7D4::field_8`, with `vy` from `s_800DB7D4::field_0`.
    SVECTOR field_10; // Values copied from `s_800DB7D4::field_0`, with `vy` from `s_800DB7D4::field_8`.
    SVECTOR field_18; // Values copied from `s_800DB7D4::field_8`.
    s8      field_20;
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
    s32             field_0;
    s32             field_4;
    s_800E06A0      field_8[10];
    s_WorldObjectModel objRef_238;
} s_800E0698;
STATIC_ASSERT_SIZEOF(s_800E0698, 0x254);

typedef struct
{
    s32     field_0;
    s32     chara_4;
    VECTOR3 position_8;
    s32     funcptr_14;
} s_SubD_800E0930;
typedef struct
{
    s32             field_0;
    s_SubD_800E0930 sub_4;
} s_D_800E0930;

extern s_D_800E0930 D_800E0930[3];

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

extern s32 D_800E05A8;   // Angle?
extern q3_12 D_800E05AC; // Angle?
extern u16 D_800E05AE;

extern s8 D_800E05E0;
extern s8 D_800E05E1;
extern s8 D_800E05E2;

extern s_800E0698 D_800E0698;

extern VECTOR3 D_800E08F0;

extern s_SfxVolume D_800DB1F8[6];

void func_800D0C50(SVECTOR* rot, MATRIX* mat);

void func_800D19AC(VECTOR3* vec);

void func_800D19CC(VECTOR3* vec);

void Ai_Twinfeeler_TextureLoad(void);

/** @brief Translates a vector in the direction of a given Y axis heading angle along the XZ plane.
 *
 * @param outVec Output vector (Q19.12).
 * @param inVec Input vector (Q19.12).
 * @param headingAngle Y axis heading angle.
 * @param dist Translation distance.
 */
void Math_Vector3Translate(VECTOR3* outVec, const VECTOR3* inVec, q19_12 headingAngle, q19_12 dist);

void func_800D326C(void);

s_D_800E0930* func_800D344C(s_SubCharacter* chara, void (*funcptr)());

void func_800D3504(s_SubCharacter* chara);

void func_800D354C(VECTOR3*);

void func_800D3694(s_SubCharacter*, s_AnmHeader*, GsCOORDINATE2*);

void func_800D3AE0(s_SubCharacter* chara, s32 soundIdx);

u8 func_800D3B1C(void);

void func_800D3B44(bool disableDamage);

void func_800D3B68(s_SubCharacter* chara);

void func_800D3B74(s_SubCharacter* chara);

void func_800D3CBC(s_SubCharacter* chara);

bool Ai_Twinfeeler_Init(s_SubCharacter* chara);

void func_800D3E58(s_SubCharacter*);

void func_800D3FB0(s_SubCharacter* chara);

void func_800D3FD8(s_SubCharacter* chara);

void func_800D4000(s_SubCharacter* chara);

void func_800D4028(s_SubCharacter* chara);

void func_800D46E0(VECTOR3* vec0, VECTOR3* vec1);

s32 func_800D4924(VECTOR3* vec, q19_12 angle); // Assumed return type.

void func_800D4A34(s_SubCharacter* chara);

u32 func_800D4DD8(void);

void func_800D50D8(s_SubCharacter* chara);

void func_800D53B0(s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800D54B4(s_SubCharacter*, GsCOORDINATE2*);

void func_800D55C8(s_SubCharacter*);

void func_800D5888(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800D5904(s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800D59EC(s_SubCharacter*, GsCOORDINATE2*);

void func_800D5B6C(s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800D5BC8(s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800D5DF4(s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800D5E30(s_SubCharacter*, GsCOORDINATE2*);

void Ai_Twinfeeler_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

/** @brief Handles a First Aid Kit or Rifle Shells item pickup event. */
void MapEvent_CommonItemTake(void);

void func_800D6704(void);

void func_800D6774(void);

void func_800D6F24(void);

s32 func_800D7394(void);

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

void func_800D9BB0(void);

#endif
