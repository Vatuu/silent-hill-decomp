#ifndef _MAPS_MAP7_S03_H
#define _MAPS_MAP7_S03_H

#include "game.h"

#include <psyq/libgs.h>

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk153
#define HAS_PlayerState_Unk186
#define HAS_PlayerState_Unk162
#define HAS_PlayerState_Unk171
#define HAS_PlayerState_Unk172
#define HAS_PlayerState_Unk173
#define HAS_PlayerState_Unk174
#define HAS_PlayerState_Unk176
#define HAS_PlayerState_Unk177
#define HAS_PlayerState_Unk184
#define HAS_PlayerState_Unk178
#define HAS_PlayerState_Unk179
#define HAS_PlayerState_Unk180
#define HAS_PlayerState_Unk181
#define HAS_PlayerState_Unk182
#define HAS_PlayerState_Unk183
#define KEYFRAME_PlayerState_Unk153 816
#define KEYFRAME_PlayerState_Unk162 837

#define HAS_Chara_EndingCybil
#define HAS_Chara_EndingDahlia
#define HAS_Chara_Alessa
#define HAS_Chara_EndingKaufmann
#define HAS_Chara_BloodyLisa
#define HAS_Chara_Incubator
#define HAS_Chara_BloodyIncubator
#define MAP_CHARA_COUNT 7

// Config used by `Map_RoomIdxGet`.
#define MAP_ROOM_MIN_X    Q12(-200.0f)
#define MAP_ROOM_MAX_X    Q12(200.0f)
#define MAP_ROOM_MIN_Z    Q12(-160.0f)
#define MAP_ROOM_MAX_Z    Q12(0.f)

typedef struct
{
    VECTOR3 field_0;
    u8      unk_C[4];
    u8      unk_10[40];
    s32     flags_38;
} s_800ED7E0_ptr;
STATIC_ASSERT_SIZEOF(s_800ED7E0_ptr, 60);

typedef struct
{
    s32 field_0;
    s16 field_4;
    s16 field_6;
    s32 field_8;
    s16 field_C;
    s16 field_E;
    u8  unk_10[16];
    s32 field_20;
    u8  unk_24[24];
    s32 field_3C;
    s32 field_40;
    u8  unk_44[8];
} s_800F3D48_4;
STATIC_ASSERT_SIZEOF(s_800F3D48_4, 0x4C);

typedef struct
{
    u8           unk_0[4];
    s_800F3D48_4 field_4;
} s_800F3D48;
STATIC_ASSERT_SIZEOF(s_800F3D48, 0x50);

typedef struct
{
    s32    field_0;
    u8     unk_4[4];
    s32    field_8;
    s32    field_C;
    s32    field_10;
    s32    field_14;
    s32    field_18;
    s32    field_1C;
    u8     unk_20[8];
    s32    field_28[29];
    u8     unk_9C[4];
    s32    field_A0[29];
    u8     unk_114[4];
    MATRIX mat_118[29];
    u8     unk_4B8[32];
    s32    field_4D8;
    u8     unk_4DC[8];
    s32    field_4E4;
    s32    field_4E8;
    u8     unk_4EC[4];
    s32    field_4F0;
    s32    field_4F4;
} s_800F3DAC;
STATIC_ASSERT_SIZEOF(s_800F3DAC, 0x4F8);

// Note: Beginning is similar to M4S03 `s_800E0988`, which could be a substruct used here.
typedef struct
{
    q19_12          positionX_0;
    q19_12          positionZ_4;
    MATRIX          mat_8;
    s_SubCharacter* field_28;
    GsCOORDINATE2*  coords_2C;
    VECTOR3         playerPosition_30;
    u8              unk_3C[8];
    s32             field_44;
    s32             field_48;
} s_D_800F48A8;
STATIC_ASSERT_SIZEOF(s_D_800F48A8, 0x4C); // Assumed size.

extern s32 D_800F2438; // Length of `D_800F3D48` array.

extern s_800F3D48* D_800F3D48;

extern s_800F3DAC* D_800F3DAC; // Pointer to `s_800F3DAC[30]`.

extern s_D_800F48A8 D_800F48A8;

extern s32 D_800ED73C; // } RNG related values?
extern s32 D_800ED740; // }

extern u16 D_800ED768;

extern u16 D_800ED77C;

extern u16 D_800ED7B4;

extern s_800ED7E0_ptr* D_800ED7E0[];

extern u16 D_800ED898;

extern s32 D_800ED8AC;

extern s_800ED7E0_ptr* D_800ED8B0[];

extern s32 D_800ED8E8;

extern s_800ED7E0_ptr* D_800ED8EC[];

extern u16 D_800ED88C;

extern s32 D_800ED980;

extern s_800ED7E0_ptr* D_800ED984[];

extern u16 D_800ED9B4;

extern s32 D_800ED9B8;

extern s_800ED7E0_ptr* D_800ED9BC[];

extern s32 D_800EDA00;

extern s32 D_800EDA04;

extern u8 D_800EDA08;

extern s32 D_800EDA0C;

extern s16 D_800F23D0;

extern s32 D_800F23D4;

extern s32 D_800F2430;
extern s32 D_800F2434;

extern s32 D_800F3D8C;

extern s_WorldObjectDesc g_WorldObject_Bin;

extern s_WorldObjectDesc g_WorldObject_Nu;

extern s_WorldObjectDesc g_WorldObject_Baby;

extern u8 D_800F3E58; // Unknown type, pointer passed to func_800DB154

extern s32 D_800F47F0;

extern VECTOR3 g_WorldObject_UnkPos;

extern u8 D_800F4804;
extern u8 D_800F4805;
extern s8 D_800F4806;
extern s8 D_800F4807;
extern s8 D_800F4808;
extern s8 D_800F4809;
extern s8 D_800F480A;
extern s8 D_800F480B;
extern u8 D_800F480C;
extern s8 D_800F480D;
extern s8 D_800F480E;
extern s8 D_800F480F;
extern u8 D_800F4810;
extern u8 D_800F4811;
extern u8 D_800F4812;
extern u8 D_800F4813;
extern u8 D_800F4814;
extern u8 D_800F4815;
extern u8 D_800F4816;
extern u8 D_800F4817;
extern u8 D_800F4818;
extern u8 D_800F4819;
extern u8 D_800F481A;
extern u8 D_800F481B;
extern u8 D_800F481C;
extern u8 D_800EC8FC[340];
extern s_SfxVolume D_800EC8C8[13];
extern s32 D_800F3D98[4];

extern q19_12 D_800F4820; // Time.

extern s32 D_800F4824;

extern s32 D_800F4828;

extern s16 D_800F482C;

extern s32 D_800F4830;

extern s32 D_800F4834;

extern s32 D_800F4838;

extern s32 D_800F483C;

extern s_WorldObjectModel g_WorldObject_Real;
extern s_WorldObjectModel g_WorldObject_Ura;
extern s_WorldObjectModel g_WorldObject_Under;

extern s32 D_800F48A4;

extern s_AnimInfo LITTLE_INCUBUS_ANIM_INFOS[];
extern s_AnimInfo INCUBUS_ANIM_INFOS[];
extern s_AnimInfo UNKKOWN_23_ANIM_INFOS[];

void Ai_BloodyIncubator_Update(s_SubCharacter* bloodyIncubator, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_BloodyIncubator_AnimUpdate(s_SubCharacter* bloodyIncubator, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void func_800D3740(s_SubCharacter* bloodyIncubator, GsCOORDINATE2* coords);
void func_800D38D8(s_SubCharacter* bloodyIncubator, GsCOORDINATE2* coords);
void Ai_BloodyIncubator_Init(s_SubCharacter* bloodyIncubator);

void Ai_Incubator_Update(s_SubCharacter* incubator, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Incubator_AnimUpdate(s_SubCharacter* incubator, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void func_800D3C80(s_SubCharacter* incubator, GsCOORDINATE2* coords);
void func_800D3E18(s_SubCharacter* incubator, GsCOORDINATE2* coords);
void Ai_Incubator_Init(s_SubCharacter* incubator);

void Ai_LittleIncubus_Update(s_SubCharacter* incubus, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800D663C(void);

s32 func_800D6750(s32* sxy);

void func_800D6788(void); // Assumed return type.

void func_800D6804(VECTOR3*, VECTOR3*); // Assumed args/return type.

void func_800D6FA0(void);

s32 func_800D70B4(s32* sxy);

void func_800D70EC(void);

void func_800D7144(VECTOR3*);

void func_800D71A4(s32 arg0);

void func_800D74F4(s32 x, s32 z, s32 val);

s32 func_800D7CB4(s32* sxy);

void func_800D7CEC(void);

void func_800D7CF8(void);

void func_800D7D74(s32);

void func_800D7E50(VECTOR3*);

void func_800D7ED0(void);

void func_800D7EF0(void);

PACKET* func_800D7F10(void);

void func_800D7F20(u8* arg0);

void func_800D7F2C(void*, s32, s32, s32, s32, s16, s16, s32);

void func_800D82AC(void* arg0, s32 arg1, s32 arg2, s32 arg3);

void func_800D8858(s32);

void func_800D88C4(void);

void func_800D88CC(void);

void func_800D88D8(void);

s_800F3D48* func_800D905C(void);

void func_800D9114(s_800F3D48* arg0);

void func_800D9394(void);

void func_800D947C(void);

void func_800D952C(void);

void func_800DA4B4(s32* arg0, s32* arg1); // Assumed types.

s32 func_800DA4EC(s32 min, s32 max);

void func_800DA774(s_800ED7E0_ptr*);

void func_800DACFC(VECTOR3* vec, s32 arg1, s32 arg2);

void func_800DAD54(void);

void func_800DB154(GsCOORDINATE2*);

void func_800DB288(void);

void func_800DB608(void);

// Returns `bool`?
s32 func_800DC6DC(s32*, s32*, VECTOR3*, s_800F3DAC*);

void func_800DCD94(MATRIX* mat, VECTOR3* pos);

void func_800DCDDC(s_800F3DAC* arg0, VECTOR3* arg1, VECTOR3* arg2);

void func_800DCF94(void);

s_800F3DAC* func_800DD090(void);

void func_800DD240(VECTOR3* vec);

void func_800DD260(VECTOR3* arg0, VECTOR3* arg1);

void func_800DD2C8(VECTOR3* arg0, VECTOR3* arg1);

void func_800DD3D4(void* arg0, q19_12 scaleX, q19_12 scaleY, q19_12 scaleZ);

void func_800DD594(VECTOR3* pos, s_SubCharacter* chara, GsCOORDINATE2* coords, s32 arg3);

void func_800DD62C(VECTOR3* pos, s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800DD67C(VECTOR3* pos, s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800DD6CC(void);

void func_800DD7D0(VECTOR3*);
void func_800DD868(void);
s32  func_800DD964(void);
void func_800DD98C(bool disableDamage);
void func_800DD9B0(s_SubCharacter* chara);
void func_800DD9D4(s_SubCharacter* chara);
void func_800DD9F8(s_SubCharacter* chara);
bool Ai_Incubus_Init(s_SubCharacter* incubus, GsCOORDINATE2* coords);

void func_800DDB3C(s_SubCharacter* chara, GsCOORDINATE2* coords);

void func_800DDB68(s_SubCharacter* chara, s32 soundIdx);

s32 func_800DDBA4(s32 idx);

void func_800DBABC(void);

void func_800DDBBC(s_SubCharacter* incubus);

void func_800DDDB0(s_SubCharacter* incubus);
void func_800DDEEC(s_SubCharacter* incubus);
void func_800DDF14(s_SubCharacter* incubus);
void func_800DEA54(s_SubCharacter* incubus, GsCOORDINATE2* coords);
void func_800DEAF4(s_SubCharacter* incubus);
void func_800DEC38(s_SubCharacter* incubus);
void func_800DEC74(s_SubCharacter* incubus, GsCOORDINATE2* coord);
void func_800DED68(s_SubCharacter* incubus, GsCOORDINATE2* coord);
void func_800DEE44(s_SubCharacter* incubus);
void func_800DEE90(s_SubCharacter* incubus, s_AnmHeader* anmHdr,  GsCOORDINATE2* coord);
void func_800DEFE8(s_SubCharacter* incubus, GsCOORDINATE2* coord);
void func_800DF044(s_SubCharacter* incubus, GsCOORDINATE2* coords);
void func_800DF074(s_SubCharacter* incubus);
void Ai_Incubus_Update(s_SubCharacter* incubus, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800DF7F8(void);
s32  func_800DF90C(void);
void func_800DFA14(void);
s32 func_800DFB04(void);
void func_800DFB2C(bool disableDamage);
void func_800DFB50(s_SubCharacter* chara);
void func_800DFB74(s_SubCharacter* chara);
bool Ai_Unknown23_Init(s_SubCharacter* chara, GsCOORDINATE2* coords);
void func_800DFCE4(s_SubCharacter* chara);
void func_800DFEF0(s_SubCharacter* chara);
void func_800DFF28(s_SubCharacter* chara);
void func_800DFF44(s_SubCharacter* chara);
q19_12 func_800E04C4(void);
void func_800E0528(s_SubCharacter* chara);
void func_800E05DC(s_SubCharacter*, GsCOORDINATE2*);
void func_800E0670(s_SubCharacter* chara, GsCOORDINATE2* coord);
void func_800E0728(s_SubCharacter* chara);
void func_800E0774(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void func_800E0888(s_SubCharacter* chara, GsCOORDINATE2* coords);
void func_800E08E4(s_SubCharacter* chara, GsCOORDINATE2* coord);
void func_800E0914(s_SubCharacter* chara);
void Ai_Unknown23_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800E0A34(void);
void func_800E0B28(s32 arg0);
void func_800E0B5C(s32 arg0);

void func_800E0B90(void);
void func_800E0C10(void);

void func_800E14D4(void);

void func_800E14DC(s_PlayerWork*, s_SubCharacter*, bool);

void func_800E1788(s32);

q19_12 func_800E2444(q19_12 dampingRate, q19_12 current, q19_12 target);

// Some kind of RNG? Constants don't seem well known?
s32 func_800E28F4(void);

void func_800E2E90(void);

void func_800E3390(void);

void func_800E3B6C(void);

void func_800E3D18(void);

void func_800E3E84(void);

void func_800E3F30(void);

void func_800E4714(void);

void func_800E514C(void);

void func_800E62CC(void);

void func_800E70F0(void);

void func_800E7380(void);

void func_800E787C(void);

void func_800E86BC(void);

void func_800E8D20(void);

void func_800E9260(e_CharacterId, s32);

void func_800E941C(void);

void func_800E9444(e_CharacterId charaId, s_SubCharacter* chara);

void func_800E9490(s_SubCharacter* chara);

void func_800E9498(void);

void func_800E94AC(void);

void func_800E94C0(void);

void func_800E94F4(void);

void Map_WorldObjectsInit(void);

void func_800E972C(void);

void func_800E9874(void);

void func_800E98EC(void);

void func_800E9AC8(void);

void func_800E9C28(void);

#endif
