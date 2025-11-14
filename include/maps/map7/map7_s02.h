#ifndef _MAPS_MAP7_S02_H
#define _MAPS_MAP7_S02_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk59
#define HAS_PlayerState_Unk60
#define HAS_PlayerState_Unk72
#define HAS_PlayerState_Unk143
#define HAS_PlayerState_Unk144
#define HAS_PlayerState_Unk146
#define HAS_PlayerState_Unk147
#define HAS_PlayerState_Unk148
#define HAS_PlayerState_Unk155
#define HAS_PlayerState_Unk156
#define HAS_PlayerState_Unk157
#define HAS_PlayerState_Unk158
#define KEYFRAME_PlayerState_Unk59 862
#define KEYFRAME_PlayerState_Unk60 877

#define HAS_Chara_Dahlia
#define HAS_Chara_GhostChildAlessa
#define HAS_Chara_Kaufmann
#define HAS_Chara_GhostDoctor
#define MAP_CHARA_COUNT 4

// Config used by `Map_RoomIdxGet`.
#define MAP_ROOM_MIN_X    Q12(-200.0f)
#define MAP_ROOM_MAX_X    Q12(200.0f)
#define MAP_ROOM_MIN_Z    Q12(-160.0f)
#define MAP_ROOM_MAX_Z    Q12(0.f)

typedef struct
{
    u8  field_0;
    u8  unk_1[1];
    s16 field_2;
} s_800EA494;

extern s_MapPoint2d MAP_POINTS[];

extern u16 D_800E9CE4;

extern u16 D_800E9CFC;

/** Some SFX position. */
extern VECTOR3 D_800E9D00;

extern u16 D_800E9D50;

/** Map message indices. */
extern u16 D_800E9D6C[];

extern u16 D_800E9D7C;

extern s16 D_800E9D80[];

extern u8 D_800E9D8E;

extern s8 D_800E9ECC;
extern u8 D_800E9ECD;

/** Time. */
extern s16 D_800E9ED6;
extern s16 D_800E9ED8;
extern s16 D_800E9EDA;

/** Index into `D_800E9D6C`. */
extern u8 D_800EA490;
extern u16 D_800EA492;

extern s_800EA494 D_800EA494;

extern s32 D_800EB68C;
extern s32 D_800EB690;

extern VECTOR3 D_800EB694;
extern VECTOR3 D_800EB6A4;

extern u8  D_800EB6B0;
extern s32 D_800EB6B4;

extern s_WorldObjectPose D_800EB6E0; // Assumed type.

extern s8 D_800EBAF4;

extern s_WorldObjectDesc D_800EBB64;

/** Timer. */
extern q3_12 D_800EBB94;

void Ai_GhostDoctor_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_GhostDoctor_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

/** @brief Updates the transform of the `coord` matrix to the character's position, converting
 * from world space to geometry space.
 *
 * @param chara Reference character.
 * @param coord Output coord to update.
 */
void Character_CoordTransformUpdate(s_SubCharacter* chara, GsCOORDINATE2* coord);

void Ai_GhostDoctor_Init(s_SubCharacter* chara);

/** Likely takes Harry character based on property usage. */
void func_800D8C00(s_SubCharacter* chara, GsCOORDINATE2* coord);

void func_800D97FC(s32 arg0);

void func_800D9830(s32 arg0);

void func_800D9864(void);

void func_800D98E4(void);

void func_800DA248(void);

/** Cutscene. */
void func_800DAA4C(void);

/** @brief Handles a First Aid Kit, Health Drink, Handgun Bullets, or Shotgun Shells item pickup event. */
void MapEvent_CommonItemTake(void);

void func_800DB498(void);

void func_800DB52C(void);

/** @brief Key of Bethor use event. */
void MapEvent_KeyOfBethorUse(void);

/** @brief Key of Aratron use event. */
void MapEvent_KeyOfAratronUse(void);

void func_800DB738(void);

void func_800DBB34(void);

/** @brief Handles the Ankh item pickup event. */
void MapEvent_AnkhTake(void);

void func_800DC778(void);

void func_800DCD00(void);

void func_800DD9E8(void);

void func_800DDEC8(void);

/** @brief Handles the Disk of Ouroboros item pickup event. */
void MapEvent_DiskOfOuroborosTake(void);

void func_800DF21C(void);

void func_800DFA54(void);

/** @brief Handles the Screwdriver item pickup event. */
void MapEvent_ScrewdriverTake(void);

void func_800DFAAC(void);

void func_800DFAE4(void);

/** @brief Handles the Amulet of Solomon item pickup event. */
void MapEvent_AmuletOfSolomonTake(void);

void func_800DFB48(void);

/** @brief Earlier version of `map7_s01::func_800D9C9C` using unfinished sfx IDs, possibly unused here. */
void func_800DFDDC(void);

/** @brief Handles the Crest of Mercury item pickup event. */
void MapEvent_CrestOfMercuryTake(void);

/** @brief Handles the Ring of Contract item pickup event. */
void MapEvent_RingOfContractTake(void);

/** @brief Handles the Camera item pickup event. */
void MapEvent_CameraTake(void);

void func_800E0CB4(void);

void func_800E0FF0(void);

void func_800E12E4(void);

void func_800E1398(void);

void func_800E1DAC(void);

void func_800E1FF4(void);

void func_800E2DC0(void);

#endif
