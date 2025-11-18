#ifndef _MAPS_MAP7_S03_H
#define _MAPS_MAP7_S03_H

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
    u8      unk_10[0x28];
    s32     flags_38;
} s_800ED7E0_ptr;
STATIC_ASSERT_SIZEOF(s_800ED7E0_ptr, 0x3C);

extern s32 D_800ED73C; // } RNG related values?
extern s32 D_800ED740; // }

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

extern u8 D_800EDA08;

extern s32 D_800EDA0C;

extern s16 D_800F23D0;

extern s32 D_800F23D4;

extern s32 D_800F2430;
extern s32 D_800F2434;

extern s32 D_800F3D8C;

extern u8 D_800F3DE4; // Unknown type, pointer passed to func_800D7144

extern u8 D_800F3E58; // Unknown type, pointer passed to func_800DB154

extern s32 D_800F47F0;

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
extern s8 D_800F4810;
extern s8 D_800F4811;
extern s8 D_800F4812;
extern u8 D_800F4813;
extern s8 D_800F4814;
extern u8 D_800F4815;
extern u8 D_800F4816;
extern u8 D_800F4817;
extern s8 D_800F4818;
extern s8 D_800F4819;
extern s8 D_800F481A;
extern u8 D_800F481B;
extern u8 D_800F481C;

extern q19_12 D_800F4820; // Time.

extern s32 D_800F4824;

extern s32 D_800F4828;

extern s16 D_800F482C;

extern s32 D_800F4830;

extern s32 D_800F4834;

extern s32 D_800F4838;

extern s32 D_800F483C;

extern s16 D_800F23D0;

extern s_AnimInfo LITTLE_INCUBUS_ANIM_INFOS[];
extern s_AnimInfo INCUBUS_ANIM_INFOS[];
extern s_AnimInfo UNKKOWN_23_ANIM_INFOS[];

void Ai_BloodyIncubator_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_BloodyIncubator_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void func_800D3740(s_SubCharacter*, GsCOORDINATE2*);
void func_800D38D8(s_SubCharacter*, GsCOORDINATE2*);
void Ai_BloodyIncubator_Init(s_SubCharacter* chara);

void Ai_Incubator_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Incubator_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void func_800D3C80(s_SubCharacter* chara, GsCOORDINATE2* coord);
void func_800D3E18(s_SubCharacter*, GsCOORDINATE2*);
void Ai_Incubator_Init(s_SubCharacter* chara);

void Ai_LittleIncubus_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800D70EC(void);

void func_800D7144(void*); // TODO: Unknown arg type.

void func_800D71A4(s32 arg0);

void func_800D7CEC(void);

void func_800D7CF8(void);

void func_800D7D74(s32);

void func_800D7E50(VECTOR3*);

void func_800D7ED0(void);

void func_800D7EF0(void);

PACKET* func_800D7F10(void);

void func_800D7F20(u8* arg0);

void func_800D8858(s32);

void func_800D88C4(void);

void func_800D88CC(void);

void func_800D88D8(void);

void func_800D9394(void);

void func_800D947C(void);

void func_800DA774(s_800ED7E0_ptr*);

void func_800DAD54(void);

void func_800DB154(GsCOORDINATE2*);

void func_800DB288(void);

void func_800DB608(void);
void func_800DD67C(VECTOR3*, s_SubCharacter*, GsCOORDINATE2*);
void func_800DD7D0(VECTOR3*);
void func_800DD868(void);
u8   func_800DD964(void);
void func_800DD98C(s32);
void func_800DD9B0(s_SubCharacter*);
void func_800DD9D4(s_SubCharacter*);
void func_800DD9F8(s_SubCharacter*);
bool Ai_Incubus_Init(s_SubCharacter* chara, GsCOORDINATE2* coords);
void func_800DDBBC(s_SubCharacter*);
void func_800DEC74(s_SubCharacter*, GsCOORDINATE2*);
void func_800DED68(s_SubCharacter*, GsCOORDINATE2*);
void func_800DEE44(s_SubCharacter* chara);
void func_800DEE90(s_SubCharacter*, s_AnmHeader*, GsCOORDINATE2*);
void func_800DEFE8(s_SubCharacter* chara, GsCOORDINATE2* coord);
void func_800DF044(s_SubCharacter* chara, GsCOORDINATE2* coords);
void func_800DF074(s_SubCharacter* chara);
void Ai_Incubus_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800DFA14(void);
void func_800DFB2C(s32);
void func_800DFB50(s_SubCharacter*);
void func_800DFB74(s_SubCharacter*);
bool Ai_Unknown23_Init(s_SubCharacter* chara, GsCOORDINATE2* coords);
void func_800DFCE4(s_SubCharacter*);
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

void func_800E14DC(s_MainCharacter*, s_SubCharacter*, bool);

void func_800E1788(s32);

// Some kind of RNG? Constants don't seem well known?
s32 func_800E28F4(void);

void func_800E2E90(void);

void func_800E3390(void);

void func_800E3B6C(void);

void func_800E3D18(void);

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

void func_800E9444(e_CharacterId, s_SubCharacter*);

void func_800E9490(s_SubCharacter* chara);

void func_800E9498(void);
void func_800E94AC(void);
void func_800E94F4(void);

void func_800E9874(void);

#endif
