#ifndef _BODYPROG_COLLISION_COLLISION_H
#define _BODYPROG_COLLISION_COLLISION_H

#include "bodyprog/chara/chara.h"
#include "bodyprog/formats/ipd.h"
#include "bodyprog/map/map.h"

/** @brief Computes a trigger height from half-meter height steps.
 *
 * @note The trigger height has a default offset of `Q12(-1.5f)`.
 *
 * @param steps Half-meter height steps.
 * @return Trigger height (Q19.12).
 */
#define TRIGGER_HEIGHT_GET(steps) \
    ((-Q12(steps) >> 1) - Q12(1.5f))


struct _IpdCollisionData;

/** @brief Global collision flags.
 * Applies for both NPCs and the player.
 */
typedef enum _CollisionTriggerFlags
{
    CollisionTriggerFlag_None = 0,
    CollisionTriggerFlag_0    = 1 << 0, // Enables map collisions.
    CollisionTriggerFlag_1    = 1 << 1, // Enables objects collisions.
    CollisionTriggerFlag_2    = 1 << 2, // Enables alternative objects collisions?
    CollisionTriggerFlag_3    = 1 << 3, // @unused Only ever call in `MAP6_S05`.
    CollisionTriggerFlag_All  = 0xFFFF
} e_CollisionTriggerFlags;

typedef enum _CollisionType
{
    CollisionType_None = 0,
    CollisionType_Wall = 1,
    CollisionType_Unk2 = 2
} e_CollisionType;

/** @brief Collision surface data. */
typedef struct _CollisionSurface
{
    /* 0x0 */ q19_12 groundHeight;
    /* 0x4 */ q3_12  tiltAngleX;
    /* 0x6 */ q3_12  tiltAngleZ;
    /* 0x8 */ s8     groundType; /** `e_GroundType` */
    // 3 bytes of padding.
} s_CollisionSurface;
STATIC_ASSERT_SIZEOF(s_CollisionSurface, 12);

/** @brief Collision point data. */
typedef struct _CollisionPoint
{
    /* 0x0  */ VECTOR3            position;   /** Q19.12 */
    /* 0xC  */ s_CollisionSurface surface;
    /* 0x18 */ s32                groundType; /** `e_GroundType` */
} s_CollisionPoint;

typedef struct _CollisionResult
{
    /* 0x0  */ VECTOR3            offset; /** Q19.12 */
    /* 0xC  */ s_CollisionSurface surface;
    /* 0x18 */ q19_12             ceilingHeight;
} s_CollisionResult;

/** @brief Collection of nearby collision triggers. */
typedef struct _ActiveCollisionTriggers
{
    /* 0x0 */ u16                 flags; /** `e_CollisionTriggerFlags` */
    /* 0x2 */ u8                  collisionTriggerCount;
    /* 0x3 */ u8                  __pad_3;
    /* 0x4 */ s_CollisionTrigger* collisionTriggers[20]; // Guessed size.
} s_ActiveCollisionTriggers;

/** @brief Collision cylinder with a character collision state. */
typedef struct _CollisionCylinder
{
    /* 0x0  */ VECTOR3 position; /** Q19.12 */
    /* 0xC  */ q3_12   bottom;
    /* 0xE  */ q3_12   top;
    /* 0x10 */ q3_12   radius;
    /* 0x14 */ s8      collisionState; /** `e_CharaCollisionState` */
} s_CollisionCylinder;
STATIC_ASSERT_SIZEOF(s_CollisionCylinder, 20);

typedef struct
{
    /* 0x0 */ u8  field_0;
    /* 0x1 */ u8  field_1;
    /* 0x2 */ s16 field_2;
    /* 0x4 */ s32 field_4;
} s_CollisionState_A8;

typedef struct
{
    /* 0x0 */ s8      field_0;
    /* 0x2 */ DVECTOR field_2; // Q3.12 | Angle constraint. X is min, Y is max. TODO: Don't use `DVECTOR` for this anymore.
} s_CollisionState_44_0;

typedef struct
{
    /* 0x0  */ s_CollisionState_44_0 field_0;
    /* 0x6  */ s16                   field_6;
    /* 0x8  */ s_CollisionState_44_0 field_8;
    /* 0xE  */ s16                   field_E;
    /* 0x10 */ s8*                   field_10[8];
    /* 0x30 */ s_CollisionState_44_0 field_30;
    /* 0x36 */ s16                   field_36;
} s_CollisionState_44;

typedef union
{
    /* 0x0 */ s16 field_0;
              struct
              {
                  /* 0x0 */ u8 field_0;
                  /* 0x1 */ u8 field_1;
    /* 0x0 */ } s_field_0;
} s_CollisionState_CC_C;

typedef struct
{
    /* 0x0  */ DVECTOR_XZ field_0;
    /* 0x4  */ DVECTOR_XZ field_4;
    /* 0x8  */ u32        field_8;
    /* 0xC  */ s32        field_C; // Radius?
    /* 0x10 */ s16        field_10;
    /* 0x12 */ s8         __pad_12[2];
    /* 0x14 */ DVECTOR_XZ field_14;
} s_CollisionState_CC_20;

typedef struct
{
    /* 0x0  */ s_IpdCollisionData*    ipdCollisionData_0;
    /* 0x4  */ u8                     field_4; // `s_IpdCollisionData::ptr_14` Index.
    /* 0x5  */ u8                     field_5;
    /* 0x6  */ SVECTOR3               field_6; // Q7.8 | Probe position?
    /* 0xC  */ s_CollisionState_CC_C  field_C;
    /* 0xE  */ u8                     field_E;  // } Index from `s_IpdCollisionData::field_6_8`.
    /* 0xF  */ u8                     field_F;  // }
    /* 0x10 */ u8                     field_10; // } Index from `s_IpdCollisionData::field_6_5`.
    /* 0x11 */ u8                     field_11; // }
    /* 0x12 */ SVECTOR3               collPoint_12; // Data from `s_IpdCollisionData::collPoints`
    /* 0x18 */ SVECTOR3               collPoint_18; // Data from `s_IpdCollisionData::collPoints`
    /* 0x1E */ s8                     unk_1E[2];
    /* 0x20 */ s_CollisionState_CC_20 field_20;
} s_CollisionState_CC;
STATIC_ASSERT_SIZEOF(s_CollisionState_CC, 56);

typedef struct _CollisionCharaMovement
{
    /* 0x0  */ s32        collisionState; /** `e_CharaCollisionState` */
    /* 0x4  */ bool       field_4; // Flag set when the character collisions being check is any of the ones being
                                   // in the of `Collision_CharaCollisionSetup`.
    /* 0x8  */ q19_12     moveDistance; // TODO: Just `distance`.
    /* 0xC  */ SVECTOR    moveOffset; // Q23.8 | TODO: Just `offset`.
    /* 0x14 */ DVECTOR_XZ direction;
    /* 0x18 */ q23_8      positionX;
    /* 0x1C */ q23_8      positionZ;
    /* 0x20 */ q23_8      newPositionX;
    /* 0x24 */ q23_8      newPositionZ;
    /* 0x28 */ q7_8       radius;
    /* 0x2A */ q7_8       topPos;
    /* 0x2C */ q7_8       bottomPos;
} s_CollisionCharaMovement;

typedef struct _CollisionState
{
    /* 0x0+0  */ u8                       field_0_0     : 8; // Boolean? Code only assigns 1.
    /* 0x0+8  */ s8                       isCharaMoving : 1; /** `bool` */
    /* 0x0+9  */ s8                       field_0_9     : 1; /** `bool` */
    /* 0x0+10 */ s8                       field_0_10    : 1; /** `bool` */
    /* 0x0+11 */ s8                       field_0_11    : 5;
    /* 0x2    */ u16                      flags         : 16; /** `e_CollisionTriggerFlags` */
    /* 0x4    */ s_CollisionCharaMovement charaMoveInfo;
    /* 0x34   */ s32                      field_34;
    /* 0x38   */ s16                      field_38;
    /* 0x3A   */ s16                      field_3A;
    /* 0x3C   */ s16                      field_3C; // X?
    /* 0x3E   */ s16                      field_3E; // Z?
    /* 0x40   */ s8*                      field_40;
    /* 0x44   */ s_CollisionState_44      field_44;
    /* 0x7C   */ q23_8                    field_7C; // Related to ground height?
    /* 0x80   */ q23_8                    field_80; // X } Related to ground surface.
    /* 0x84   */ q23_8                    field_84; // Z }
    /* 0x88   */ q19_12                   tiltAngleX;
    /* 0x8C   */ q19_12                   tiltAngleZ;
    /* 0x90   */ s32                      field_90; // `bool`?
    /* 0x94   */ s32                      groundType; /** `e_GroundType` */

                 union
                 {
                     DVECTOR_XZ offset;
                     s32        field_0;
    /* 0x98   */ } charaPos;
                 union
                 {
                     DVECTOR_XZ offset;
                     s32        field_0;
    /* 0x9C   */ } charaNewPos;
                 union
                 {
                     struct
                     {
                         /* 0x0 */ u8                     closestXSubCellIdx;
                         /* 0x1 */ u8                     closestZSubCellIdx;
                         /* 0x2 */ u8                     closeFarXSubCellIdxDiff;
                         /* 0x3 */ u8                     closeFarZSubCellIdxDiff;
                         /* 0x4 */ s_IpdCollisionData_20* field_4;
                         /* 0x8 */ s_CollisionState_A8    field_8[4];
                     } s_0;
                     struct
                     {
                         /* 0x0 */ q7_8 field_0; // Set to absolute character bottom height.
                         /* 0x2 */ q7_8 field_2; // Set to absolute character top height.
                         /* 0x4 */ s16  field_4;
                         /* 0x6 */ u8   collisionState; /** `e_CharaCollisionState` */
                         /* 0x8 */ u8*  field_8;
                         /* 0xC */ s8   unk_C[28];
                     } s_1;
    /* 0xA0   */ } field_A0;

    /* 0xC8   */ u8                  field_C8;
    /* 0xC9   */ u8                  unk_C9[1];
    /* 0xCA   */ q7_8                groundHeight;
    /* 0xCC   */ s_CollisionState_CC field_CC;
    // TODO: Maybe incomplete. Maybe not, added the final padding based on `Collision_SurfaceGet`.
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
    /* 0x58 */ u16              field_58; // X
    /* 0x5A */ s16              field_5A; // Z
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

typedef struct
{
    s8         unk_0[8];
    DVECTOR    field_8;
    s16        field_C;
    s16        field_E;
    q19_12     field_10; // } X
    q19_12     field_14; // } Z
    s16        field_18;
    s8         unk_1A[2];
    s32        field_1C; // Index into `field_20`.
    DVECTOR_XZ field_20[2];
} s_func_8006E490;

typedef struct
{
    q19_12 field_0; // X position.
    q19_12 field_4; // Z position.
    q19_12 field_8;
    q19_12 field_C;
    q19_12 field_10; // X
    q19_12 field_14; // Z
    q19_12 field_18; // X } Bounds?
    q19_12 field_1C; // X }
    q19_12 field_20; // Z }
    q19_12 field_24; // Z }
    q19_12 field_28; // Maybe XZ position.
    q19_12 triggerHeight;
} s_func_8006F338;

// emoose: Also works: `extern u16 g_ActiveCollisionTriggers[];`, `arg0->field_4 = g_ActiveCollisionTriggers[0];`.
// Didn't see any array accesses in Ghidra though, struct might be more likely.
extern s_ActiveCollisionTriggers g_ActiveCollisionTriggers;

extern u16 g_CollisionTriggerFlags;

/** @brief Initializes the collision subsystem, resetting flags and clearing the trigger zone count. */
void Collision_Init(void);

/** @brief Gets the active collision flags. */
u16 Collision_FlagsGet(void);

/** @brief Sets the active collision flags.
 *
 * @param collFlags New collision flags.
 */
void Collision_FlagsSet(u16 collFlags);

/** @brief Sets additional active collision flags using OR.
 *
 * @param collFlags Collision flag bits to set.
 */
void Collision_FlagBitsSet(u16 collFlags);

void Collision_FlagBitsClear(s32 collFlags);

/** @brief Runs through collision triggers and collects those containing the given XZ position.
 *
 * @param posX Query X position.
 * @param posZ Query Z position.
 * @param triggers Array of collision triggers.
 */
void Collision_NearbyTriggersGet(q19_12 posX, q19_12 posZ, s_CollisionTrigger* triggers);

void IpdCollData_FixOffsets(s_IpdCollisionData* collData);

void func_80069994(s_IpdCollisionData* collData);

void func_800699E4(s_IpdCollisionData* collData);

/** @brief Gets the collision surface at a given 2D world position.
 *
 * @param surface Output collision surface.
 * @param posX X world position.
 * @param posZ Z world position.
 */
void Collision_SurfaceGet(s_CollisionSurface* surface, q19_12 posX, q19_12 posZ);

/** @brief Detects a wall collision using the scratchpad for performance.
 *
 * @param collResult Output collision result.
 * @param moveOffset Movement offset.
 * @param chara Character to check.
 * @return Wall response code.
 */
s32 Collision_WallDetect(s_CollisionResult* collResult, const VECTOR3* moveOffset, s_SubCharacter* chara);

/** @brief Handles a wall collision response by sampling the ground at 9 points around a character.
 *
 * @param collResult Output collision result.
 * @param moveOffset Movement offset (unused).
 * @param chara Character to check.
 * @param response Initial collision pass response.
 * @return Wall response code.
 */
s32 Collision_WallResponse(s_CollisionResult* collResult, const VECTOR3* moveOffset, s_SubCharacter* chara, s32 response);

/** @brief Probes ground heights at 16 radial points to determine the terrain slope direction.
 * Creates a terrain avoidance force to push away from illegal positions.
 *
 * @param collResult Output collision result with XZ offset vector pointing away from the highest terrain.
 * @param pos Center position.
 * @param startGroundHeight Starting character Y position.
 * @param startHeadingAngle Starting heading angle on the XZ plane for the probe circle.
 */
void Collision_GroundProbeRadial(s_CollisionResult* collResult, const VECTOR3* pos,
                                 q19_12 startGroundHeight, q19_12 startHeadingAngle);

/** @brief Applies collision detection for a character's movement offset.
 *
 * @param collResult Output collision result.
 * @param moveOffset Movement offset.
 * @param chara Character performing the movement.
 * @return Collision result response.
 */
bool Collision_CharaCollisionSetup(s_CollisionResult* collResult, const VECTOR3* moveOffset, s_SubCharacter* chara);

/** @brief Initializes a default collision result with a position and ground height.
 *
 * @param result Collision result to initialize.
 * @param offsetX X offset.
 * @param offsetY Y offset.
 * @param offsetZ Z offset.
 * @param groundHeight Ground height.
 */
void Collision_DefaultResultSet(s_CollisionResult* collResult, q19_12 offsetX, q19_12 offsetY, q19_12 offsetZ, q19_12 groundHeight);

/** @brief Gets an array of collidable characters for collision testing.
 *
 * @param collCharaCount Output number of collidable characters.
 * @param excludedChara Character to exclude, typically the one being tested.
 * @param includePlayer Filter out the player.
 * @return Collidable characters.
 */
s_SubCharacter** Collision_CollidableCharasGet(s32* collCharaCount, const s_SubCharacter* excludedChara, bool includePlayer);

/** @brief Checks a movement offset against a collision result.
 *
 * @param collResult Collision result.
 * @param offset Movement offset to test.
 * @param query Collision query parameters.
 * @return `true` if movement is possible, `false` otherwise.
 */
s32 Collision_OffsetCheck(s_CollisionResult* collResult, VECTOR* offset, const s_CollisionCylinder* collCylinder);

s32 func_8006A42C(s_CollisionResult* collResult, const VECTOR3* offset, const s_CollisionCylinder* collCylinder);

bool func_8006A4A8(s_CollisionResult* collResult, VECTOR3* moveOffset, const s_CollisionCylinder* collCylinder, bool arg3,
                   s_IpdCollisionData** collDataPtrs, s32 collDataIdx, s_func_8006CF18* arg6, s32 arg7,
                   s_SubCharacter** charas, s32 charaCount);

/** @brief Slows down colliding characters according to relational cylinder collision. */
void Collision_TargetCharaCollidingSlowDown(VECTOR3* offset, const s_CollisionCylinder* collCylinder, s_SubCharacter** charas, s32 charaCount);

/** @brief Initializes a collision state for a new pass.
 *
 * @param collState Collision state to initialize.
 * @param moveOffset Movement offset.
 * @param collCylinder Collision cylinder.
 * @param arg3 Configuration flag. TODO: What is it?
 */
void Collision_QueryInit(s_CollisionState* collState, VECTOR3* moveOffset, const s_CollisionCylinder* collCylinder, bool arg3);

/** @brief Calculates the movement direction vector and distance from a position offset.
 *
 * @param result Output movement direction and position data.
 * @param moveOffset Movement offset.
 * @param collCylinder Collision cylinder.
 */
void Collision_MoveDirectionCalc(s_CollisionCharaMovement* result, const VECTOR3* moveOffset, const s_CollisionCylinder* collCylinder);

void Collision_CharaCollisionHandling(s_CollisionState* collState, s_IpdCollisionData* collData);

bool func_8006AEAC(s_CollisionState* collState, const s_IpdCollisionData* collData);

bool Collision_CharaSubCellIdxGet(s_CollisionState* collState, const s_IpdCollisionData* collData);

void func_8006B1C8(s_CollisionState* collState, s_IpdCollisionData* collData, s_IpdCollisionData_20* arg2);

bool func_8006B318(s_CollisionState* collState, const s_IpdCollisionData* collData, s32 idx);

/** `arg1` is unused, but `func_8006B1C8` passes second arg to this. */
void func_8006B6E8(s_CollisionState* collState, s_IpdCollisionData_20* arg1);

bool func_8006B7E0(s_CollisionState_A8* arg0, s_CollisionState_CC_20* arg1);

void func_8006B8F8(s_CollisionState_CC* arg0);

void func_8006B9C8(s_CollisionState* collState);

void func_8006BB50(s_CollisionState* collState, s32 arg1);

q23_8 func_8006BC34(s_CollisionState* collState);

/** `arg3` and `arg4` might be XY or XZ position components. */
void func_8006BCC4(s_CollisionState_44* arg0, s8* arg1, u32 arg2, q7_8 distX, q7_8 distZ, q7_8 arg5);

void func_8006BDDC(s_CollisionState_44_0* arg0, q3_12 rotX, q3_12 rotY);

void func_8006BE40(s_CollisionState* collState);

void func_8006BF88(s_CollisionState* collState, SVECTOR3* arg1);

void func_8006C0C8(s_CollisionState* collState, s16 arg1, s16 arg2);

bool func_8006C1B8(u32 arg0, s16 arg1, s_CollisionState* collState);

q3_12 func_8006C248(s32 packedDir, s16 arg1, q3_12 deltaX, q3_12 deltaZ, s16 arg4);

bool func_8006C3D4(s_CollisionState* collState, s_IpdCollisionData* collData, s32 idx);

void func_8006C45C(s_CollisionState* collState);

void func_8006C794(s_CollisionState* collState, s32 arg1, s32 dist);

void func_8006C838(s_CollisionState* collState, s_IpdCollisionData* collData);

void func_8006CA18(s_CollisionState* collState, s_IpdCollisionData* collData, s_IpdCollisionData_20* arg2);

q3_12 Collision_OffsetAlphaGet(s_CollisionState* collState);

q23_8 Ipd_GroundHeightGet(q23_8 posX, q23_8 posZ, const s_CollisionState* collState);

void func_8006CC9C(s_CollisionState* collState);

void func_8006CF18(s_CollisionState* collState, s_func_8006CF18* arg1, s32 idx);

void func_8006D01C(VECTOR3* arg0, VECTOR3* offset, q3_12 offsetAlpha, s_CollisionState* collState);

void func_8006D2B4(VECTOR3* arg0, s_CollisionState_44* arg1);

void func_8006D600(VECTOR3* pos, q19_12 angle, q19_12 rotX, q19_12 rotY, s32 arg4);

void func_8006D774(s_CollisionState* collState, VECTOR3* arg1, VECTOR3* arg2);

/** `arg1` is likely Q23.8. */
void func_8006D7EC(s_CollisionCharaMovement* arg0, SVECTOR* arg1, SVECTOR* arg2);

bool Ray_TraceQuery(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* to);

/** Ray function. */
bool Ray_CharaTraceQuery(s_RayTrace* trace, const VECTOR3* from, VECTOR3* offset, s_SubCharacter* excludedChara);

void Ray_MissSet(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* offset, q23_8 dist);

/** @brief Checks if an obstruction in a ray's line of sight has been hit, ignoring a specified character.
 *
 * @param trace Ray trace.
 * @param from Ray origin.
 * @param offset Ray target offset from origin.
 * @param excludedChara Character to exclude.
 * @return `true` if there is an obstruction, `false` otherwise.
 */
bool Ray_LosHitCheck(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* offset, s_SubCharacter* excludedChara);

bool func_8006DC18(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* offset);

bool Ray_TraceSetup(s_RayState* state, bool useCylinder, q7_8 arg2, const VECTOR3* from, const VECTOR3* offset, q19_12 arg5, q19_12 arg6,
                    s_SubCharacter** collCharas, s32 collCharaCount);

bool Ray_TraceRun(s_RayTrace* trace, s_RayState* state);

// Fills `state` with info.
void func_8006E0AC(s_RayState* state, s_IpdCollisionData* ipdColl);

void func_8006E150(s_func_8006E490* arg0, DVECTOR arg1, DVECTOR arg2);

void func_8006E490(s_func_8006E490* arg0, u32 flags, q19_12 posX, q19_12 posZ);

void func_8006E53C(s_RayState* state, s_IpdCollisionData_20* arg1, s_IpdCollisionData* ipdColl);

void func_8006E78C(s_RayState* state, s_IpdCollisionData_14* arg1, SVECTOR3* arg2, s_IpdCollisionData_10* arg3, s32 arg4);

void func_8006EB8C(s_RayState* state, s_IpdCollisionData_18* arg1);

// Fills ray hit data?
void func_8006EE0C(s_RayState_6C* arg0, bool useCylinder, const s_SubCharacter* chara);

void func_8006EEB8(s_RayState* state, s_SubCharacter* chara);

void func_8006F250(q19_12* arg0, q19_12 posX, q19_12 posZ, q19_12 posDeltaX, q19_12 posDeltaZ);

void func_8006F338(s_func_8006F338* arg0, q19_12 posX, q19_12 posZ, q19_12 posDeltaX, q19_12 posDeltaZ);

bool func_8006F3C4(s_func_8006F338* arg0, const s_CollisionTrigger* trigger);

/** Translates something. Unsure on 3rd param's name. */
/** @brief Gets the ceiling height, derived from active collision triggers.
 *
 * @param moveOffset Movement offset.
 * @param collCylinder Collision cylinder.
 * @param cylinderRadius Cylinder radius.
 * @param cylinderHeight Cylinder height.
 * @return Ceiling height. `DEFAULT_CEILING_HEIGHT` if no ceiling exists.
 */
q19_12 Collision_CeilingHeightGet(VECTOR3* moveOffset,
                                  const s_CollisionCylinder* collCylinder, q19_12 cylinderRadius, q19_12 cylinderHeight);

/** @brief Gets the offset from a world position to the edge of a collision trigger.
 * If the position is inside the trigger, the offset is (0, 0).
 *
 * @param offsetX Output offset X.
 * @param offsetZ Output offset Z.
 * @param posX World reference position X.
 * @param posZ World reference position Z.
 * @param trigger Reference collision trigger.
 */
void Collision_TriggerOffsetGet(q19_12* offsetX, q19_12* offsetZ, q19_12 posX, q19_12 posZ, const s_CollisionTrigger* trigger);

q19_12 func_8006F99C(s_SubCharacter* chara, q19_12 dist, q3_12 headingAngle);

/** Angle getter. Something to do with the direction from a character to a target position, probably for NPC AI.
 * Unsure if `spanAngle` is an angle.
 */
q19_12 Chara_HeadingAngleGet(s_SubCharacter* chara, q19_12 dist, q19_12 toX, q19_12 toZ, q3_12 spanAngle, bool cond);

bool func_8006FD90(s_SubCharacter* chara, s32 count, q19_12 baseDistMax, q19_12 distStep);

/** @brief Checks if there's an obstructed target-based line of sight between a character and a target position.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param toX Target X position.
 * @param toY Target Y position.
 * @param toZ Target Z position.
 * @return `true` if there's an obstruction, `false` otherwise.
 */
bool Ray_CharaToTargetLosHitCheck(s_SubCharacter* fromChara, q19_12 toX, q19_12 toY, q19_12 toZ);

/** @brief Checks if there's an unobstructed target-based line of sight between a character and any other character.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param toX Target X position.
 * @param toY Target Y position.
 * @param toZ Target Z position.
 * @return `true` if there's no obstruction, `false` otherwise.
 */
bool Ray_CharaToCharaTargetLosCheck(s_SubCharacter* fromChara, q19_12 toX, q19_12 toY, q19_12 toZ);

/** @brief Checks if there's an unobstructed line of sight between an NPC and a player.
 *
 * @param fromNpc Origin NPC character.
 * @param toPlayer Target player character.
 * @return `true` if there's no obstruction, `false` otherwise.
 */
bool Ray_NpcToPlayerLosHitCheck(s_SubCharacter* fromNpc, s_SubCharacter* toPlayer);

/** @brief Checks if there's an unobstructed distance-based line of sight between a character and any other character.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param dist Ray distance.
 * @param headingAngle Ray heading angle on the XZ plane.
 * @return `true` if there's no obstruction, `false` otherwise.
 */
bool Ray_CharaToCharaDistLosCheck(s_SubCharacter* fromChara, q19_12 dist, q3_12 headingAngle);

/** @brief @unused Checks if there's another character obstructing the distance-based line of sight in front of a
 * character.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param dist Ray distance.
 * @return `true` if there's another character in front, `false` otherwise.
 */
bool Ray_CharaToCharaFrontLosHitCheck(s_SubCharacter* fromChara, q19_12 dist);

/** @brief Checks if there's an obstructed distance-based line of sight from a character.
 *
 * @note `fromChara` is excluded.
 *
 * @param fromChara Origin character.
 * @param dist Ray distance.
 * @param headingAngle Ray heading angle on the XZ plane.
 * @return `true` if there's an obstruction, `false` otherwise.
 */
bool Ray_CharaLosHitCheck(s_SubCharacter* fromChara, q19_12 dist, q3_12 headingAngle);

bool func_80070320(void);

/** TODO: Return type uncertain. */
q19_12 func_80070360(s_SubCharacter* chara, q19_12 someDist, q3_12 arg2);

/** @brief Sets a character's interpolated collision shapes for the active animation frame.
 *
 * @param chara Character to update.
 * @param keyframe0 First keyframe.
 * @param keyframe1 Second keyframe.
 */
void Collision_CharaCollisionSet(s_SubCharacter* chara, s_Keyframe* keyframe0, s_Keyframe* keyframe1);

void func_800705E4(GsCOORDINATE2* boneCoords, s32 idx, q19_12 scaleX, q19_12 scaleY, q19_12 scaleZ);

#endif
