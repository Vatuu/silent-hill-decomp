#ifndef _BODYPROG_MAP_MAP_H
#define _BODYPROG_MAP_MAP_H

#include "bodyprog/anim.h"
#include "bodyprog/chara.h"
#include "bodyprog/formats/anm.h"
#include "bodyprog/view/structs.h"

// Something related to enemies attacks.
typedef struct
{
    union
    {
        q19_12 vx_0; // Displacement offset.
        struct
        {
            s16 field_0;
            s16 field_2;
        } s_0;
        struct
        {
            u16 field_0;
            u16 field_2;
        } s_1;
    } field_0;
    union
    {
        q19_12 vz_4;
        struct
        {
            s16 field_0;
            s16 field_2;
        } s_0;
    } field_4;
    q3_12 vy_8;
    u8    field_A;
    u8    field_B; // Flags?
    union
    {
        s32 field_0;
        struct
        {
            q3_12 field_0; // Angle.
            q3_12 field_2; // Angle.
        } s_0;
        struct
        {
            u8 field_0;
            u8 field_1;
            u8 field_2;
            u8 field_3;
        } s_1;
        struct
        {
            q4_12 field_0;
            u16   field_2;
        } s_2;
    } field_C;
    union
    {
        q20_12 field_0; // Timer.
        struct
        {
            s16 field_0;
            s16 field_2;
        } s_0;
        struct
        {
            s16 field_0;
            u8  field_2;
            u8  field_3;
        } s_1;
        struct
        {
            u8 field_0;
            u8 field_1;
            u8 field_2;
            u8 field_3;
        } s_2;
        struct
        {
            u16 field_0;
            u16 field_2;
        } s_3;
    } field_10;
} s_MapHdr_field_4C;
STATIC_ASSERT_SIZEOF(s_MapHdr_field_4C, 20);

/** @brief Speed zone. Defines a volume used for player speed modulation. */
typedef struct _SpeedZone
{
    /* 0x0 */ s8   type; /** `e_SpeedZoneType` */
              // 1 byte of padding.
    /* 0x2 */ q11_4 minX;
    /* 0x4 */ q11_4 maxX;
    /* 0x6 */ q11_4 minZ;
    /* 0x/ */ q11_4 maxZ;
} s_SpeedZone;

/** @brief Water zone. Defines a volume used for visual water effects. */
typedef struct _WaterZone
{
    /* 0x0 */ u8    isEnabled; /** `bool` */
              // 1 byte of padding.
    /* 0x2 */ q11_4 illumination;
    /* 0x4 */ q11_4 minX;
    /* 0x6 */ q11_4 maxX;
    /* 0x8 */ q11_4 minZ;
    /* 0xA */ q11_4 maxZ;
} s_WaterZone;

/** @brief Map GFX info. */
typedef struct _MapGfxInfo
{
    /* 0x0 */ s16                plmFileIdx_0;
    /* 0x2 */ char               tag_2[4];
    /* 0x6 */ u8                 flags_6; /** `e_MapFlags` */
              // 1 byte of padding.
    /* 0x8 */ const s_WaterZone* waterZones_8;
    /* 0xC */ const s_SpeedZone* speedZones_C;
} s_MapInfo;

typedef struct
{
    u8    unk_0;
    u8    field_1;
    u8    field_2;
    u8    unk_3;
    u8    field_4;
    u8    field_5;
    u8    field_6;
    u8    unk_7;
    u8    unk_8[2];
    s16   field_A;
    u8    unk_C[2];
    s16   field_E;
    q3_12 field_10;
    u8    unk_12[4];
    s16   field_16;
    u8    unk_18[8];
    s32   field_20;
    s32   field_24;
} s_MapOverlayHeader_5C;

typedef struct
{
    u8    field_0;
    u8    field_1;
    u8    field_2;
    u8    field_3;
    s16   field_4;
    s16   field_6;
    s16   field_8;
    s16   field_A;
    s16   field_C;
    s16   field_E;
    q3_12 field_10;
    s16   field_12;
    s32   field_14;
    s32   field_18;
    s32   field_1C;
} s_MapOverlayHeader_7C;
STATIC_ASSERT_SIZEOF(s_MapOverlayHeader_7C, 32);

typedef struct
{
    s32    field_0[4];
    s16    field_10[4];
    q19_12 field_18[4];
    u16    field_28[4];
    u8     field_30[4];
    q3_12  field_34[4]; // Y angles.
    u16    field_3C[4];
    u16    field_44[4];
    s16    field_4C[4];
    u16    field_54[4];
    u16    field_5C[4];
    q4_12  field_64[4];
    s16    field_6c[4];
    s16    field_74;
    s8     __pad_76[2];
    u8     field_78;
} s_MapOverlayHeader_94;

/** @brief Contains X/Z coordinates and optional 4 bytes of data.
 * Map headers include an array of these, into which `s_EventData` includes an index. */
typedef struct _MapPoint2d
{
    /* 0x0    */ q19_12 positionX;
    /* 0x4+0  */ u32    mapIdx_4_0      : 5; /** `e_PaperMapIdx`? */
    /* 0x4+5  */ u32    field_4_5       : 4;
    /* 0x4+9  */ u32    loadingScreenId : 3; /** `e_LoadingScreenId` */
    /* 0x4+12 */ u32    field_4_12      : 4;
    /* 0x4+16 */ q24_8  triggerParam0   : 8; // Usually a `Q8_ANGLE`.
    /* 0x4+24 */ u32    triggerParam1   : 8;
    /* 0x8    */ q19_12 positionZ;
} s_MapPoint2d;
STATIC_ASSERT_SIZEOF(s_MapPoint2d, 12);

/** TODO: Known as `Trigger` in SilentHillMapExaminer: https://github.com/ItEndsWithTens/SilentHillMapExaminer/blob/master/src/SHME.ExternalTool.Guts/Trigger.cs */
typedef struct _EventData
{
    /* 0x0    */ s16 requiredEventFlag;
    /* 0x2    */ s16 disabledEventFlag;
    /* 0x4+0  */ s8  triggerType    : 4; /** `e_TriggerType` */
    /* 0x4+4  */ u8  activationType : 4; /** `e_TriggerActivationType` */
    /* 0x5    */ u8  pointOfInterestIdx; /** Index into `g_MapOverlayHeader.mapPoints`. */
    /* 0x6    */ u8  requiredItemId;     /** `e_InvItemId` that player must use from item screen. */
    /* 0x7    */ u8  __pad_7;
    /* 0x8+0  */ u32 sysState        : 5; /** `e_SysState` used by the event. */
    /* 0x8+5  */ u32 eventParam      : 8; /** Can be an ID of a `MapMsg`, sound effect, index into `mapEventFuncs`, or index into `mapPoints` for `areaLoad` events. */
    /* 0x8+8  */ u32 flags_8_13      : 6; /** `e_EventDataUnkState` */
    /* 0x8+13 */ u32 sfxPairIdx_8_19 : 5; /** `e_SfxPairIdx` | Index into `SFX_PAIRS`. */
    /* 0x8+19 */ u32 field_8_24      : 1;
    /* 0x8+24 */ u32 mapIdx          : 6;
    /* 0x8+25 */ u32 field_8_31      : 1;
} s_EventData;
STATIC_ASSERT_SIZEOF(s_EventData, 12);

/** @brief Special map-specific Harry anim data. */
typedef struct
{
    s16   status; /** Packed anim status. See `s_ModelAnim::status`. */
    s16   status_2; /** Packed anim status. See `s_ModelAnim::status`. */
    q3_12 time;   /** Fixed-point anim time. */
    s16   keyframeIdx_6;
} s_UnkStruct3_Mo;
STATIC_ASSERT_SIZEOF(s_UnkStruct3_Mo, 8);

/** Guessed based on in-debugger observation during gameplay.
 * Everything is inited to 0xFFFF and some data is written when the player is hit by monsters.
 * Might be more generic particles/decals struct.
 */
typedef struct _BloodSplat
{
    s16 field_0; // Maybe an array of `u16`s? Contains indices.
} s_BloodSplat;

/** @brief Character spawn info. */
typedef struct _SpawnInfo
{
    /* 0x0   */ q19_12 positionX;
    /* 0x4   */ s8     charaId; /** `e_CharaId` */
    /* 0x5   */ q0_8   rotationY;
    /* 0x6   */ s8     flags_6;               /** `e_SpawnFlags` | Copied to `stateStep` in `s_Model`, with `controlState = 0`. */
    /* 0x7+0 */ s32    gameDifficultyMin : 4; /** `e_GameDifficulty` | Minimum difficulty required for successful spawn. */
    /* 0x8   */ q19_12 positionZ;
} s_SpawnInfo;
STATIC_ASSERT_SIZEOF(s_SpawnInfo, 12);

/** @brief World-space trigger zone. */
typedef struct _TriggerZone
{
    /* 0x0+0  */ u8  isEndOfArray : 1;  /** `bool` | Marks last entry. */
    /* 0x0+1  */ s32 positionX    : 10; /** Meter steps. */
    /* 0x0+11 */ s32 positionZ    : 10; /** Meter steps. */
    /* 0x0+21 */ u32 sizeX        : 4;  /** Meter steps. */
    /* 0x0+25 */ u32 sizeZ        : 4;  /** Meter steps. */
    /* 0x0+29 */ u32 height       : 3;  /** Half-meter steps. Used to set `s_func_8006F338::field_2C` which is then copied by `func_8006F250`. */
} s_TriggerZone;
STATIC_ASSERT_SIZEOF(s_TriggerZone, 4);

/** TODO: `g_MapOverlayHeader` is part of the map overlay BIN files. Maybe should be moved to `maps/shared.h`.
 * If field has a comment that lists only certain map(s) it means all others set this field to 0.
 * func(?) means the signature is unknown and a default void() was selected for now.
 */
typedef struct _MapOverlayHeader
{
    /* 0x0   */ s_MapInfo*             mapInfo;
    /* 0x4   */ u8                     (*mapRoomIdxGet)(q19_12 posX, q19_12 posY); // Called by `Savegame_MapRoomIdxUpdate`.
    /* 0x8   */ s8                     field_8;
    /* 0xC   */ s32                    (*func_C)();
                // 3 bytes of padding.
    /* 0x10  */ void                   (*bgmEvent)(bool);
    /* 0x14  */ s8                     bgmIdx;
    /* 0x15  */ u8                     ambientAudioIdx; // Ambient file index from `g_AmbientVabTaskLoadCmds`.
    /* 0x16  */ s8                     field_16;        // Set ambient tint and draw distance.
                                                        // A value of 3 sets the map to night.
                                                        // A value of 2 will sets the map to use a tint used during the hallaway
                                                        // intro.
                                                        // Giving this and next variable a name will require further investigation
                                                        // of `particle.c` code.
    /* 0x17  */ s8                     field_17;        // Set weather to play. Rain, heavy rain, or snow.
    /* 0x18  */ void                   (**loadingScreenFuncs)();
    /* 0x1C  */ s_MapPoint2d*          mapPoints;
    /* 0x20  */ void                   (**mapEventFuncs)(); /** Points to array of event functions. */
    /* 0x24  */ s_EventData*           mapEvents;
    /* 0x28  */ GsCOORDINATE2*         field_28; // Bone coords of some kind.
    /* 0x2C  */ u8*                    loadableItems;
    /* 0x30  */ const char**           mapMessages;
    /* 0x34  */ s_AnimInfo*            harryMapAnimInfos; /** Map-specific anim infos for Harry (for anims 38+). */
    /* 0x38  */ s_UnkStruct3_Mo*       field_38; // Array of 40?
    /* 0x3C  */ void                   (*initWorldObjects)(void);
    /* 0x40  */ void                   (*updateWorldObjects)(void);
    /* 0x44  */ void                   (*func_44)();
    /* 0x48  */ void                   (*npcSpawnEvent)();
    /* 0x4C  */ s_MapHdr_field_4C*     unkTable1_4C; // Related to collision?
    /* 0x50  */ s16                    unkTable1Count_50;
                // 2 bytes of padding.
    /* 0x54  */ s_BloodSplat*          bloodSplats;
    /* 0x58  */ s16                    bloodSplatCount;
                // 2 bytes of padding.
    /* 0x5C  */ s_MapOverlayHeader_5C* field_5C;
    /* 0x60  */ void                   (*func_60)(s32 idx, bool arg1);
    /* 0x64  */ s32                    (*func_64)(POLY_FT4** poly, s32);
    /* 0x68  */ s32                    (*func_68)(POLY_FT4** poly, s32);
    /* 0x6C  */ void                   (*func_6C)();
    /* 0x70  */ s32                    (*func_70)(POLY_FT4** poly, s32);
    /* 0x74  */ void                   (*func_74)();
    /* 0x78  */ s32                    (*func_78)(POLY_FT4** poly, s32);
    /* 0x7C  */ s_MapOverlayHeader_7C* field_7C; // Only map1_s01, map6_s04.
    /* 0x80  */ void                   (*func_80)();
    /* 0x84  */ s32                    (*func_84)(POLY_FT4** poly, s32);
    /* 0x88  */ s32*                   func_88;                          // Only map0_s01, map7_s01.
    /* 0x8C  */ s32                    (*func_8C)(POLY_FT4** poly, s32); // Only map0_s01, map7_s01.
    /* 0x90  */ s32                    (*func_90)(POLY_FT4** poly, s32); // Only map5_s00.
    /* 0x94  */ s_MapOverlayHeader_94* field_94;                         // Only map1_s02, map1_s03.
    /* 0x98  */ s32                    (*func_98)(POLY_FT4** poly, s32); // Only map1_s02, map1_s03.
    /* 0x9C  */ void                   (*func_9C)();                     // Only map1_s02, map1_s03.
    /* 0xA0  */ void*                  ptr_A0;                           // M1S03 only, pointer to `s_800E3A40` array.
    /* 0xA4  */ s32                    (*func_A4)(POLY_FT4** poly, s32); // Only map1_s03.
    /* 0xA8  */ void                   (*func_A8)();                     // Only map6_s02.
    /* 0xAC  */ s32                    (*func_AC)(POLY_FT4** poly, s32); // Only map4_s03, map4_s05.
    /* 0xB0  */ s32                    (*func_B0)(POLY_FT4** poly, s32); // Only map4_s03, map4_s05.
    /* 0xB4  */ s32                    (*func_B4)(POLY_FT4** poly, s32); // Only map1_s03, map4_s05, map6_s01, map6_s02, map5_s01.
    /* 0xB8  */ void                   (*func_B8)(s_SubCharacter* chara, s_PlayerExtra* extra, GsCOORDINATE2* coords);
    /* 0xBC  */ void                   (*func_BC)(s_SubCharacter* chara, s_PlayerExtra* extra, GsCOORDINATE2* coords);
    /* 0xC0  */ void                   (*func_C0)();
    /* 0xC4  */ void                   (*playerMatchArmAnimDisable)();
    /* 0xC8  */ void                   (*playerControlFreeze)();
    /* 0xCC  */ void                   (*playerControlUnfreeze)(bool setIdle);
    /* 0xD0  */ bool                   (*func_D0)(s32 playerExtraState, VECTOR3* vec, q3_12 angle, s32 vecCount); // 0x800C964C
    /* 0xD4  */ s32                    (*func_D4)(s32 playerExtraState); // Points to `sharedFunc_800D2C7C_0_s00` which has `void` return type, but changing this funcptr causes mismatch in `func_80085EB8`
    /* 0xD8  */ void                   (*func_D8)();                     // Assumed return type.
    /* 0xDC  */ void                   (*playerAnimLock)(void);
    /* 0xE0  */ void                   (*isPlayerAnimLocked)(void);
    /* 0xE4  */ void                   (*playerAnimUnlock)(void);
    /* 0xE8  */ s32                    (*func_E8)(void);
    /* 0xEC  */ bool                   (*playerMoveDistIsZero)(void);
    /* 0xF0  */ void                   (*playerMoveDistClear)(void);
    /* 0xF4  */ void                   (*playerFallBackward)(void);
    /* 0xF8  */ void                   (*func_F8)();
    /* 0xFC  */ void                   (*playerDamageFeetFront)(void);
    /* 0x100 */ void                   (*func_100)();
    /* 0x104 */ void                   (*func_104)();
    /* 0x108 */ s32                    (*func_108)();
    /* 0x10C */ void                   (*func_10C)();
    /* 0x110 */ void                   (*func_110)();
    /* 0x114 */ void                   (*func_114)();
    /* 0x118 */ void                   (*func_118)();
    /* 0x11C */ void                   (*func_11C)();
    /* 0x120 */ void                   (*func_120)();
    /* 0x124 */ void                   (*func_124)(s_SubCharacter* player, q19_12 afkTime);
    /* 0x128 */ s32                    (*playerRunTimerReset)(s_SubCharacter* player);
    /* 0x12C */ s32                    (*charaLock)(s_SubCharacter* chara);
    /* 0x130 */ void                   (*charaIsLockedCheck)(s_SubCharacter* chara);
    /* 0x134 */ s32                    (*charaUnlock)(s_SubCharacter* chara);
    /* 0x138 */ s32                    (*charaAnimPlaybackStateGet)(s_SubCharacter* chara);
    /* 0x13C */ bool                   (*func_13C)(s_SubCharacter* chara, s32 arg1, VECTOR3* arg2In, s32 angleIn, s32 arg4);
    /* 0x140 */ void                   (*charaVisibleSet)(s_SubCharacter* chara);
    /* 0x144 */ void                   (*charaInvisibleSet)(s_SubCharacter* chara);
    /* 0x148 */ bool                   (*func_148)(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx0, s32 keyframeIdx1, s32 sfxId, s32 pitch);
    /* 0x14C */ bool                   (*func_14C)(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx, s32 sfxId); // Play SFX?
    /* 0x150 */ s32                    (*charaAnimStartKeyframeIdxGet)(s_SubCharacter* chara);
    /* 0x154 */ void                   (*charaCollisionReset)(s_SubCharacter* chara);
    /* 0x158 */ void                   (*func_158)(q19_12 x, q19_12 z); // Only map1_s05, map1_s06.
    /* 0x15C */ void                   (*func_15C)();                   // Only map5_s01.
    /* 0x160 */ void                   (*func_160)();                   // Only map5_s01.
    /* 0x164 */ void                   (*func_164)();                   // Only map5_s01.
    /* 0x168 */ void                   (*particlesUpdate)(s32 unused, s32 mapId, s32);
    /* 0x16C */ void                   (*enviromentSet)(s8, u32);
    /* 0x170 */ void                   (*func_170)();
    /* 0x174 */ void                   (*func_174)();
    /* 0x178 */ void                   (*particleHyperBlasterBeamDraw)(VECTOR3* vec0, q19_12* rotX, q19_12* rotY);
    /* 0x17C */ void                   (*particleBeamDraw)(const VECTOR3* from, const VECTOR3* to);
    /* 0x180 */ void                   (*particleSoundStop)();
    /* 0x184 */ q19_12*                windSpeedX;
    /* 0x188 */ q19_12*                windSpeedZ;
    /* 0x18C */ s32*                   data_18C;
    /* 0x190 */ s32*                   data_190;
    /* 0x194 */ void                   (*charaUpdateFuncs[Chara_Count])(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords); /** Guessed params. Funcptrs for each `e_CharaId`, set to 0 for IDs not included in the map overlay. Called by `Game_NpcUpdate`. */
    /* 0x248 */ s8                     charaGroupIds[CHARA_GROUP_COUNT]; /** `e_CharaId` values where if `s_SpawnInfo::charaId == Chara_None`, `charaGroupIds[0]` is used for `charaSpawnInfos[0]` and `charaGroupIds[1]` for `charaSpawnInfos[1]`. */
    /* 0x24C */ s_SpawnInfo            charaSpawnInfos[2][16];           /** Array of character type/position/flags. `flags_6 == 0` are unused slots? Read by `Game_NpcRoomInitSpawn`. */
    /* 0x3CC */ VC_ROAD_DATA           cameraPaths[100];
    /* 0xD2C */ s_TriggerZone          triggerZones[200];
} s_MapOverlayHeader;
STATIC_ASSERT_SIZEOF(s_MapOverlayHeader, 4172);

#endif
