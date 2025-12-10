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
    s_SubCharacter* chara_0;
    s32             field_4;
    u8              unk_8[0x230];
    s_WorldObject_0 objRef_238;
} s_800E0698;

extern s_AnimInfo TWINFEELER_ANIM_INFOS[];

extern s32 D_800DB914; // } RNG related values?
extern s32 D_800DB918; // }

extern s_FsImageDesc D_800DB91C;

extern u16 D_800DB92C;

extern u16 D_800DB9E0;
extern u8  D_800DB9E2;

extern s_WorldObjectDesc g_WorldObject_Fence;
extern s_WorldObjectDesc g_WorldObject_Mal5_21;
extern s_WorldObject_0   g_WorldObject_Mal6[2];
extern VECTOR3           g_WorldObject_UnkPos;
extern SVECTOR3          g_WorldObject_UnkRot;
extern s_WorldObjectDesc g_WorldObject_SavePad;
extern s_WorldObject_0   g_CommonWorldObjects[6];

extern s32 D_800E05A8;
extern s16 D_800E05AC;
extern s16 D_800E05AE;

extern s8 D_800E05E0;
extern s8 D_800E05E1;
extern s8 D_800E05E2;

extern s_800E0698 D_800E0698;

void func_800D0C50(SVECTOR* rot, MATRIX* mat);

void func_800D19AC(VECTOR3* vec);

void Ai_Twinfeeler_TextureLoad(void);

void func_800D354C(VECTOR3*);

void func_800D3694(s_SubCharacter*, s_AnmHeader*, GsCOORDINATE2*);

u8 func_800D3B1C(void);

void func_800D3B44(s32);

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

void func_800D4A34(s_SubCharacter* chara);

u32 func_800D4DD8(void);

void func_800D50D8(s_SubCharacter* chara);

void func_800D53B0(s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800D54B4(s_SubCharacter*, GsCOORDINATE2*);

void func_800D55C8(s_SubCharacter*);

void func_800D5888(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

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

void func_800D76BC(s_SubCharacter* chara);

s32 func_800D76E8(void); // Assumed return type.

void func_800D78D4(void* arg0); // Unknown arg type.

void func_800D8FC0(void);

void func_800D960C(void);

void func_800D9824(void);

void Map_WorldObjectsInit(void);

#endif
