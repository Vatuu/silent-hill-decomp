#ifndef _BODYPROG_COLLISION_COLLISION_H
#define _BODYPROG_COLLISION_COLLISION_H

#include "bodyprog/chara/chara.h"
#include "bodyprog/map/map.h"

struct _IpdCollisionData;

/** @brief Global collision flags.
 * Applies for both NPCs and the player.
 */
typedef enum _CollisionFlags
{
    CollisionFlag_None = 0,
    CollisionFlag_0    = 1 << 0, // Enables map collisions.
    CollisionFlag_1    = 1 << 1, // Enables objects collisions.
    CollisionFlag_2    = 1 << 2, // Enables alternative objects collisions?
    CollisionFlag_3    = 1 << 3, // @unused Only ever call in `MAP6_S05`.
    CollisionFlag_All  = 0xFFFF
} e_CollisionFlags;

typedef enum _CollisionType
{
    CollisionType_None = 0,
    CollisionType_Wall = 1,
    CollisionType_Unk2 = 2
} e_CollisionType;

typedef struct _Collision
{
    /* 0x0 */ q19_12 groundHeight;
    /* 0x4 */ q3_12  field_4;    // X
    /* 0x6 */ q3_12  field_6;    // Z
    /* 0x8 */ s8     groundType; /** `e_GroundType` */
    // 3 bytes of padding.
} s_Collision;
STATIC_ASSERT_SIZEOF(s_Collision, 12);

/** @brief Collision point data. */
typedef struct _CollisionPoint
{
    /* 0x0  */ VECTOR3     position;   /** Q19.12 */
    /* 0xC  */ s_Collision collision;
    /* 0x18 */ s32         groundType; /** `e_GroundType` */
} s_CollisionPoint;

typedef struct _CollisionQuery
{
    /* 0x0  */ VECTOR3 position; /** Q19.12 */
    /* 0xC  */ q3_12   bottom;
    /* 0xE  */ q3_12   top;
    /* 0x10 */ q3_12   radius;         // Unsure. Set to cylinder radius.
    /* 0x14 */ s8      collisionState; /** `e_CharaCollisionState` */
} s_CollisionQuery;
STATIC_ASSERT_SIZEOF(s_CollisionQuery, 20);

typedef struct
{
    u8  field_0;
    u8  field_1;
    s16 field_2;
    s32 field_4;
} s_CollisionState_A8;

typedef struct
{
    s8      field_0;
    s8      unk_1;
    DVECTOR field_2; // Q3.12 | Angle constraint. X is min, Y is max. TODO: Don't use `DVECTOR` for this anymore.
} s_CollisionState_44_0;

typedef struct
{
    s_CollisionState_44_0 field_0;
    s16                  field_6;
    s_CollisionState_44_0 field_8;
    s16                  field_E;
    s8*                  field_10[8];
    s_CollisionState_44_0 field_30;
    s16                  field_36;
} s_CollisionState_44;

typedef union
{
    s16 field_0;
    struct
    {
        u8 field_0;
        u8 field_1;
    } s_field_0;
} s_CollisionState_CC_C;

typedef struct
{
    DVECTOR_XZ field_0;
    DVECTOR_XZ field_4;
    u32        field_8;
    s32        field_C;
    s16        field_10;
    s8         __pad_12[2];
    DVECTOR_XZ field_14;
} s_CollisionState_CC_20;

typedef struct
{
    struct _IpdCollisionData*   ipdCollisionData_0;
    u8                    field_4; // Index.
    u8                    field_5;
    SVECTOR3              field_6; // Q7.8 | Probe position?
    s_CollisionState_CC_C  field_C;
    u8                    field_E;
    u8                    field_F;
    u8                    field_10;
    u8                    field_11;
    SVECTOR3              field_12;
    SVECTOR3              field_18;
    s8                    unk_1E[2];
    s_CollisionState_CC_20 field_20;
} s_CollisionState_CC;
STATIC_ASSERT_SIZEOF(s_CollisionState_CC, 56);

// Collision-related.
typedef struct
{
    /* 0x0  */ s32        collisionState; /** `e_CharaCollisionState` */
    /* 0x4  */ bool       field_4;
    /* 0x8  */ q19_12     distance_8;
    /* 0xC  */ SVECTOR    offset_C; // Q23.8
    /* 0x14 */ DVECTOR_XZ direction_14;
    /* 0x18 */ q23_8      positionX_18;
    /* 0x1C */ q23_8      positionZ_1C;
    /* 0x20 */ q23_8      newPositionX_20;
    /* 0x24 */ q23_8      newPositionZ_24;
    /* 0x28 */ q7_8       field_28; // Radius.
    /* 0x2A */ q7_8       field_2A; // Top.
    /* 0x2C */ q7_8       field_2C; // Bottom.
} s_func_8006ABC0;

typedef struct
{
    u8  unk_0[2];
    s16 field_2;
    u8  unk_4[2];
    s16 field_6;
} s_func_8006CA18;

typedef struct _CollisionState
{
    u8                 field_0_0  : 8; // Boolean? Code only assigns 1.
    s8                 field_0_8  : 1; // Something to do with collision. `bool` flag that states if there's a displacement?
    s8                 field_0_9  : 1;
    s8                 field_0_10 : 1;
    s8                 field_0_11 : 5;
    u16                flags_2    : 16; /** `e_CollisionFlags` */
    s_func_8006ABC0    field_4;
    s32                field_34;
    s16                field_38;
    s16                field_3A;
    s16                field_3C; // X?
    s16                field_3E; // Z?
    s8*                field_40;
    s_CollisionState_44 field_44;
    q23_8              field_7C; // Related to ground height?
    s32                field_80; // X
    s32                field_84; // Z
    s32                field_88; // X
    s32                field_8C; // Z
    s32                field_90; // `bool`?
    s32                groundType; /** `e_GroundType` */
    union
    {
        DVECTOR_XZ vec_0;
        s32        field_0;
    } field_98;
    union
    {
        DVECTOR_XZ vec_0;
        s32        field_0;
    } field_9C;
    union
    {
        struct
        {
            u8                 field_0; // Start index for something.
            u8                 field_1;
            u8                 field_2;
            u8                 field_3;
            s_func_8006CA18*   field_4;
            s_CollisionState_A8 field_8[4];
        } s_0;
        struct
        {
            q7_8 field_0; // Set to absolute character bottom height.
            q7_8 field_2; // Set to absolute character top height.
            s16  field_4;
            u8   collisionState; /** `e_CharaCollisionState` */
            u8*  field_8;
            s8   unk_C[28];
        } s_1;
    } field_A0;
    u8                 field_C8;
    u8                 unk_C9[1];
    /* 0xCA */ q7_8               groundHeight;
    s_CollisionState_CC field_CC;
    // TODO: Maybe incomplete. Maybe not, added the final padding based on `Collision_Get`.
} s_CollisionState;

typedef struct
{
    /* 0x0 */ q23_8 field_0; // X position.
    /* 0x4 */ q23_8 field_4; // Z position.
    /* 0x8 */ q7_8  groundHeight;
    /* 0xA */ q7_8  field_A; // Y??
    /* 0xC */ q7_8  field_C; // Collision cylinder radius?
    /* 0xE */ s16   field_E;
} s_RayState_6C;

typedef struct
{
    s16 field_0;
    s16 field_2;
} s_RayState_8C;

/** @brief State for an in-progress ray trace. Contains pointers to active characters among other things. */
typedef struct
{
    /* 0x0  */ bool             field_0; // "Use cylinder"?
    /* 0x4  */ s16              field_4; // Collision flags.
    /* 0x6  */ q7_8             field_6;
    /* 0x8  */ q7_8             field_8; // Hit distance? `SHRT_MAX` if no valid hit.
    /* 0xA  */ s8               __pad_A[2];
    /* 0xC  */ q19_12           field_C;  // } Q19.12 `VECTOR3`
    /* 0x10 */ q19_12           field_10; // }
    /* 0x14 */ q19_12           field_14; // }
    /* 0x18 */ s8               unk_18[4];
    /* 0x1C */ q7_8             groundHeight;
    /* 0x1E */ s8               __pad_1E[2];
    /* 0x20 */ s_SubCharacter*  field_20;
    /* 0x24 */ q3_12            field_24; // X
    /* 0x26 */ q3_12            field_26; // Z
    /* 0x28 */ s32              groundType; /** `e_GroundType` */
    /* 0x2C */ VECTOR3          from; // Q23.8
    /* 0x38 */ s8               unk_38[4];
    /* 0x3C */ s32              field_3C; // X  } Q23.8 `VECTOR3`?
    /* 0x40 */ s32              field_40; // Y? }
    /* 0x44 */ s32              field_44; // Z  }
    /* 0x48 */ s8               unk_48[4];
    /* 0x4C */ q7_8             field_4C; // X?
    /* 0x4E */ q7_8             field_4E; // Height offset.
    /* 0x50 */ SVECTOR          offset; // Q23.8
    /* 0x58 */ u16              field_58;
    /* 0x5A */ s16              field_5A;
    /* 0x5C */ q7_8             rayDistance;
    /* 0x5E */ s16              field_5E;
    /* 0x60 */ s16              field_60;
    /* 0x62 */ s8               __pad_62[2];
    /* 0x64 */ s_SubCharacter** collCharas;
    /* 0x68 */ s32              collCharaCount;
    /* 0x6C */ s_RayState_6C    field_6C;
    /* 0x7C */ s32              field_7C;
    /* 0x80 */ s32              field_80;
    /* 0x84 */ u16              field_84;
    /* 0x86 */ u8               __pad_86[2];
    /* 0x88 */ s32              field_88;
    /* 0x8C */ s_RayState_8C    field_8C[1]; // Unknown size.
} s_RayState;

/** @brief Ray trace line of sight info. */
typedef struct _RayTrace
{
    /* 0x0  */ s8              hasHit;     /** `bool` */
    /* 0x1  */ u8              groundType; /** `e_GroundType` */
    /* 0x2  */ s8              __pad_2[2];
    /* 0x4  */ VECTOR3         target; /** Q19.12 */
    /* 0x10 */ s_SubCharacter* character;
    /* 0x14 */ q19_12          hitDistance;
    /* 0x18 */ q19_12          groundHeight;
    /* 0x1C */ q3_12           field_1C; // Angle.
} s_RayTrace;

typedef struct _CollisionResult
{
    /* 0x0  */ VECTOR3 offset_0; /** Q19.12 */
    /* 0xC  */ q19_12  groundHeight;
    /* 0x10 */ s16     field_10;
    /* 0x12 */ s16     field_12;
    /* 0x14 */ s8      groundType; /** `e_GroundType` */
    /* 0x18 */ q19_12  field_18;
} s_CollisionResult;

// Related to collision?
typedef struct
{
    /* 0x0 */ u16            flags; /** `e_CollisionFlags` */
    /* 0x2 */ u8             triggerZoneCount;
    /* 0x3 */ u8             __pad_3;
    /* 0x4 */ s_TriggerZone* triggerZones[20]; // Guessed size.
} s_800C4478;

// emoose: Also works: `extern u16 D_800C4478[];`, `arg0->field_4 = D_800C4478[0];`.
// Didn't see any array accesses in Ghidra though, struct might be more likely.
extern s_800C4478 D_800C4478;

#endif
