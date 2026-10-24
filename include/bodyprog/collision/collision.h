#ifndef _BODYPROG_COLLISION_COLLISION_H
#define _BODYPROG_COLLISION_COLLISION_H

#include "bodyprog/chara/chara.h"
#include "bodyprog/collision/chara.h"
#include "bodyprog/collision/los.h"
#include "bodyprog/collision/ray.h"
#include "bodyprog/collision/trigger.h"
#include "bodyprog/formats/ipd.h"
#include "bodyprog/map/map.h"

#define INTERSECTION_BUFFER    Q12(0.1f)
#define DEFAULT_CEILING_HEIGHT -16.0f

/** @brief Global collision flags.
 * Applies for both NPCs and the player.
 */
typedef enum _CollisionTriggerFlags
{
    CollisionTriggerFlag_None    = 0,
    CollisionTriggerFlag_Map     = 1 << 0,
    CollisionTriggerFlag_Objects = 1 << 1,
    CollisionTriggerFlag_2       = 1 << 2, // Enables alternative objects collisions?
    CollisionTriggerFlag_3       = 1 << 3, /** @unused Only ever called in `MAP6_S05`. */
    CollisionTriggerFlag_All     = 0xFFFF
} e_CollisionTriggerFlags;

/** @brief Collision types. */
typedef enum _CollisionType
{
    CollisionType_None  = 0,
    CollisionType_Wall  = 1,
    CollisionType_Floor = 2 // TODO: Unsure.
} e_CollisionType;

// TODO: "Subchunk" term may be misused here, need to check.
typedef enum _SubChunkTransitionDirection
{
    SubChunkTransitionDirection_None = 0,
    SubChunkTransitionDirection_Z    = 1,
    SubChunkTransitionDirection_X    = 2
} e_SubChunkTransitionDirection;

/** @brief Collision point surface data. */
typedef struct _CollisionSurface
{
    /* 0x0 */ q19_12 floorHeight;
    /* 0x4 */ q3_12  tiltAngleX;
    /* 0x6 */ q3_12  tiltAngleZ;
    /* 0x8 */ s8     floorType; /** `e_FloorType` */
              // 3 bytes of padding.
} s_CollisionSurface;
STATIC_ASSERT_SIZEOF(s_CollisionSurface, 12);

/** @brief Collision point data. */
typedef struct _CollisionPoint
{
    /* 0x0  */ VECTOR3            position;   /** Q19.12 */
    /* 0xC  */ s_CollisionSurface surface;
    /* 0x18 */ s32                floorType; /** `e_FloorType` */
} s_CollisionPoint;

/** @brief Collision point probe result. */
typedef struct _CollisionResult
{
    /* 0x0  */ VECTOR3            offset; /** Q19.12 */
    /* 0xC  */ s_CollisionSurface surface;
    /* 0x18 */ q19_12             ceilingHeight;
} s_CollisionResult;

typedef struct
{
    /* 0x0 */ u8    subChunkTransDir; /**`e_SubChunkTransitionDirection` */
    /* 0x1 */ u8    surfaceIdx;       // Index for `s_IpdCollisionData::cellSurfaces`.
    /* 0x2 */ q7_8  collDiffDist;
    /* 0x4 */ q23_8 radiusCollDiffDist;
} s_CollisionState_A8;

typedef struct
{
    /* 0x0 */ s8      field_0;
    /* 0x2 */ DVECTOR field_2; // Q3.12 | Angle constraint. X is min, Y is max. TODO: Don't use `DVECTOR` for this anymore.
} s_CollisionState_44_0;

typedef struct
{
    /* 0x0  */ s_CollisionState_44_0 field_0;
    /* 0x6  */ q7_8                  radiusOffset;
    /* 0x8  */ s_CollisionState_44_0 field_8;
    /* 0xE  */ s16                   field_E;
    /* 0x10 */ s8*                   field_10[8];
    /* 0x30 */ s_CollisionState_44_0 field_30;
    /* 0x36 */ q7_8                  field_36; // Another radius offset for character collision?
} s_CollisionState_44;

// Character deltas??
typedef struct
{
    /* 0x0  */ DVECTOR_XZ charaVertDiff;
    /* 0x4  */ DVECTOR_XZ charaMoveVertDiff;
    /* 0x8  */ u32        subChunkTransDir;   /** `e_SubChunkTransitionDirection` */
    /* 0xC  */ q23_8      radiusCollDiffDist; // Radius?
    /* 0x10 */ q7_8       collDiffDist;
    /* 0x12 */ s8         __pad_12[2];
    /* 0x14 */ DVECTOR_XZ charaMoveOffset;
} s_CollisionState_CC_20;

typedef union
{
    /* 0x0 */ q7_8 radiusOffset;
              struct
              {
                  /* 0x0 */ u8 surfaceIdx0;
                  /* 0x1 */ u8 surfaceIdx1;
    /* 0x0 */ } cellSurfaces;
} s_CollisionState_CC_C;

/** @brief Collision cell point data. */
typedef struct _CollisionCellPoint
{
    /* 0x0  */ s_IpdCollisionData*    ipdCollisionData;
    /* 0x4  */ u8                     cellIdx; // `s_IpdCollisionData::cells` index.
    /* 0x5  */ u8                     heightDisabled;
    /* 0x6  */ SVECTOR3               field_6; // Q7.8 | Probe position inside cell/cell? Wrong struct? Y is maybe Z.
    /* 0xC  */ s_CollisionState_CC_C  field_C; // Cell surface??
    /* 0xE  */ u8                     field_E;               // } Index from `s_IpdCollisionData::field_6_8`.
    /* 0xF  */ u8                     field_F;               // }
    /* 0x10 */ u8                     disableSurface0Height; /** `bool` */
    /* 0x11 */ u8                     disableSurface1Height; /** `bool` */
    /* 0x12 */ SVECTOR3               cellSplitVertex0;      /** Q23.8 | Vertex from `s_IpdCollisionData::cellSplitVertices`. */
    /* 0x18 */ SVECTOR3               cellSplitVertex1;      /** Q23.8 | Vertex from `s_IpdCollisionData::cellSplitVertices`. */
    /* 0x20 */ s_CollisionState_CC_20 field_20;
} s_CollisionCellPoint;
STATIC_ASSERT_SIZEOF(s_CollisionCellPoint, 56);

/** @brief Character collision state. */
typedef struct _CollisionCharaState
{
    /* 0x0  */ s32        collisionState; /** `e_CharaCollisionState` */
    /* 0x4  */ bool       field_4;        // `allowDefaultCeilHeight`? Set when the character collision being checked is any of the ones in
                                          // `Collision_CharaCollisionSetup`.
    /* 0x8  */ q19_12     distance;
    /* 0xC  */ SVECTOR    offset; /** Q23.8 | Character movement offset. */
    /* 0x14 */ DVECTOR_XZ direction;
    /* 0x18 */ q23_8      positionFromX;
    /* 0x1C */ q23_8      positionFromZ;
    /* 0x20 */ q23_8      positionToX;
    /* 0x24 */ q23_8      positionToZ;
    /* 0x28 */ q7_8       radius;
    /* 0x2A */ q7_8       top;
    /* 0x2C */ q7_8       bottom;
} s_CollisionCharaState;

typedef struct _CollisionState
{
    /* 0x0+0  */ u8                    field_0_0     : 8;  /** `bool` TODO: Check, code only assigns 0 or 1. */
    /* 0x0+8  */ s8                    isCharaMoving : 1;  /** `bool` */
    /* 0x0+9  */ s8                    field_0_9     : 1;  /** `bool` */
    /* 0x0+10 */ s8                    field_0_10    : 1;  /** `bool` */
    /* 0x2    */ u16                   flags         : 16; /** `e_CollisionTriggerFlags` */
    /* 0x4    */ s_CollisionCharaState charaState;
    /* 0x34   */ s32                   field_34;
    /* 0x38   */ s16                   field_38; // `distanceAlpha` for something.
    /* 0x3A   */ q11_4                 field_3A;
    /* 0x3C   */ q7_8                  field_3C; // X?
    /* 0x3E   */ q7_8                  field_3E; // Z?
    /* 0x40   */ s8*                   field_40;
    /* 0x44   */ s_CollisionState_44   field_44;
    /* 0x7C   */ q23_8                 slopedFloorHeight; // TODO: How is `floorHeight` different?
    /* 0x80   */ q23_8                 charaCellOffsetX; // } Character position in cell.
    /* 0x84   */ q23_8                 charaCellOffsetZ; // } 
    /* 0x88   */ q19_12                tiltAngleX;
    /* 0x8C   */ q19_12                tiltAngleZ;
    /* 0x90   */ bool                  heightDisabled; /** `bool` | TODO: Does disabled height indicate a wall or pit? */
    /* 0x94   */ s32                   floorType;     /** `e_FloorType` */

                 union
                 {
                     DVECTOR_XZ offset; /** Q23.8 */
                     q23_8      vx;
    /* 0x98   */ } charaPositionFrom;
                 union
                 {
                     DVECTOR_XZ offset; /** Q23.8 */
                     q23_8      vz;
    /* 0x9C   */ } charaPositionTo;
                 union
                 {
                     struct
                     {
                         /* 0x0 */ u8                  closestXCellIdx;
                         /* 0x1 */ u8                  closestZCellIdx;
                         /* 0x2 */ u8                  closeFarXCellIdxDiff;
                         /* 0x3 */ u8                  closeFarZCellIdxDiff;
                         /* 0x4 */ s_IpdCellRange*     cellRange;
                         /* 0x8 */ s_CollisionState_A8 field_8[4];
                     } s_0;
                     struct
                     {
                         /* 0x0 */ q7_8 bottom; // Set to absolute character bottom height.
                         /* 0x2 */ q7_8 top;    // Set to absolute character top height.
                         /* 0x4 */ q7_8 radius;
                         /* 0x6 */ u8   collisionState; /** `e_CharaCollisionState` */
                         /* 0x8 */ u8*  field_8; // Cell check idx?
                     } s_1;
    /* 0xA0   */ } field_A0; // Floor info? Cell info? Cell state?

    /* 0xC8   */ u8                   cellIdx; /** Secondary. Used only if detecting a cell after not finding one. */
    /* 0xCA   */ q7_8                 floorHeight; // TODO: Base floor height with slope unaccounted for?
    /* 0xCC   */ s_CollisionCellPoint point;
    // TODO: Maybe incomplete. Maybe not, added the final padding based on `Collision_SurfaceGet`.
} s_CollisionState;

// emoose: Also works: `extern u16 g_ActiveCollisionTriggers[];`, `arg0->field_4 = g_ActiveCollisionTriggers[0];`.
// Didn't see any array accesses in Ghidra though, struct might be more likely.
extern s_ActiveCollisionTriggers g_ActiveCollisionTriggers;

// ========================================
// @split? Collision init, flags, getters.
// ========================================

/** @brief Initializes the collision subsystem, resetting flags and clearing the trigger zone count. */
void Collision_Init(void);

/** @brief Gets the active collision flags.
 *
 * @return Active collision flags.
 */
u16 Collision_FlagsGet(void);

/** @brief Sets the active collision flags.
 *
 * @param collFlags New collision flags.
 */
void Collision_FlagsSet(u16 collFlags);

/** @brief Sets additional active collision flags.
 *
 * @param collFlags Additional collision flags to set.
 */
void Collision_FlagBitsSet(u16 collFlags);

/** @brief Clears active collision flags. `CollisionTriggerFlag_Map` is excepted.
 *
 * @param collFlags Collision flags to clear.
 */
void Collision_FlagBitsClear(s32 collFlags);

/** @brief Runs through collision triggers and collects those containing the given XZ position.
 *
 * @param posX Query X position.
 * @param posZ Query Z position.
 * @param triggers Array of collision triggers.
 */
void Collision_NearbyTriggersGet(q19_12 posX, q19_12 posZ, const s_CollisionTrigger* triggers);

// ========================================
// @split? IPD functions.
// ========================================

void Ipd_CollisionPtrsInit(s_IpdCollisionData* collData);

void Collision_CellChecksReset(s_IpdCollisionData* collData);

void Collision_CellChecksCountUpdate(s_IpdCollisionData* collData);

// ========================================
// @split? IPD/floor collision detection.
// ========================================

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

/** @brief Handles a wall collision response by sampling the floor at 9 points around a character.
 *
 * @param collResult Output collision result.
 * @param moveOffset Movement offset (unused).
 * @param chara Character to check.
 * @param response Initial collision pass response.
 * @return Wall response code.
 */
s32 Collision_WallResponse(s_CollisionResult* collResult, const VECTOR3* moveOffset, s_SubCharacter* chara, s32 response);

/** @brief Probes floor heights at 16 radial points to push away from a wall.
 * Called in `Collision_WallResponse` and used exclusively for the player.
 *
 * @note Since Y+ is down, the meanings of min/max and lowest/highest are inverted.
 *
 * @param collResult Output collision result with the XZ offset vector adjusted to push away from a wall.
 * @param pos Center position.
 * @param floorHeight Base floor height.
 * @param headingAngle Start heading angle on the XZ plane for the probe circle.
 */
void Collision_WallPush(s_CollisionResult* collResult, const VECTOR3* pos, q19_12 floorHeight, q19_12 headingAngle);

/** @brief Applies collision detection for a character's movement offset.
 *
 * @param collResult Output collision result.
 * @param moveOffset Movement offset.
 * @param chara Character performing the movement.
 * @return Collision result response.
 */
bool Collision_CharaCollisionSetup(s_CollisionResult* collResult, const VECTOR3* moveOffset, s_SubCharacter* chara);

/** @brief Initializes a default collision result with a position and floor height.
 *
 * @param result Collision result to initialize.
 * @param offsetX X offset.
 * @param offsetY Y offset.
 * @param offsetZ Z offset.
 * @param floorHeight Floor height.
 */
void Collision_DefaultResultSet(s_CollisionResult* collResult,
                                q19_12 offsetX, q19_12 offsetY, q19_12 offsetZ, q19_12 floorHeight);

/** @brief Gets an array of collidable characters for collision testing.
 *
 * @param collCharaCount Output number of collidable characters.
 * @param excludedChara Character to exclude, typically the one being tested.
 * @param includePlayer Filter out the player.
 * @return Collidable characters.
 */
s_SubCharacter** Collision_CollidableCharasGet(s32* collCharaCount, const s_SubCharacter* excludedChara,
                                               bool includePlayer);

/** @brief Checks a movement offset against a collision result.
 *
 * @param collResult Collision result.
 * @param offset Movement offset to test.
 * @param cylinder Collision cylinder.
 * @return `true` if movement is possible, `false` otherwise.
 */
s32 Collision_OffsetCheck(s_CollisionResult* collResult, VECTOR* offset, const s_CollisionCylinder* cylinder);

s32 func_8006A42C(s_CollisionResult* collResult, const VECTOR3* offset, const s_CollisionCylinder* cylinder);

// Something for character movement.
s32 func_8006A4A8(s_CollisionResult* collResult, VECTOR3* moveOffset, const s_CollisionCylinder* cylinder, bool arg3,
                  s_IpdCollisionData** collDataPtrs, s32 collDataIdx, s_func_8006CF18* arg6, s32 arg7,
                  s_SubCharacter** charas, s32 charaCount);

/** @brief Dampens a character's movement offset according to relational cylinder collisions with other characters.
 *
 * @param moveOffset Move offset to dampen.
 * @param cylinder Collision cylinder.
 * @param charas Characters to collide.
 * @param charaCount Number of characters.
 */
void Collision_MoveOffsetDampen(VECTOR3* moveOffset, const s_CollisionCylinder* cylinder,
                                s_SubCharacter** charas, s32 charaCount);

/** @brief Initializes a collision state for a new pass.
 *
 * @param state Collision state to initialize.
 * @param moveOffset Movement offset.
 * @param cylinder Collision cylinder.
 * @param arg3 Configuration flag. TODO: What is it?
 */
void Collision_CollStateInit(s_CollisionState* state, VECTOR3* moveOffset, const s_CollisionCylinder* cylinder, bool arg3);

// ========================================
// @split? Collision state fill.
// ========================================

/** @brief Calculates the movement direction vector and distance from a position offset.
 *
 * @param charaState Character collision state.
 * @param moveOffset Movement offset.
 * @param cylinder Collision cylinder.
 */
void Collision_MoveDirectionCalc(s_CollisionCharaState* charaState,
                                 const VECTOR3* moveOffset, const s_CollisionCylinder* cylinder);

void Collision_CharaCollisionHandle(s_CollisionState* state, s_IpdCollisionData* collData);

bool Collision_CellInit(s_CollisionState* state, const s_IpdCollisionData* collData);

bool Collision_CellIdxGet(s_CollisionState* state, const s_IpdCollisionData* collData);

void func_8006B1C8(s_CollisionState* state, s_IpdCollisionData* collData, s_IpdCellRange* cellRanges);

bool func_8006B318(s_CollisionState* state, const s_IpdCollisionData* collData, s32 cellIdx);

/** `arg1` is unused, but `func_8006B1C8` passes second arg to this. */
void func_8006B6E8(s_CollisionState* state, s_IpdCellRange* cellRanges);

bool func_8006B7E0(s_CollisionState_A8* cur, s_CollisionState_CC_20* prev);

void func_8006B8F8(s_CollisionCellPoint* cellPoint);

void func_8006B9C8(s_CollisionState* state);

void func_8006BB50(s_CollisionState* state, s32 arg1);

// Computes floor height, accounting for differences in cell split vertex heights?
q23_8 func_8006BC34(s_CollisionState* state);

/** `arg1` is cell check idx? */
void func_8006BCC4(s_CollisionState_44* arg0, s8* arg1, u32 unkState, q7_8 distX, q7_8 distZ, q7_8 radiusOffset);

void func_8006BDDC(s_CollisionState_44_0* arg0, q3_12 rotX, q3_12 rotY);

void func_8006BE40(s_CollisionState* state);

void func_8006BF88(s_CollisionState* state, const SVECTOR3* splitVert);

void func_8006C0C8(s_CollisionState* state, q3_12 arg1, q7_8 arg2);

bool func_8006C1B8(u32 arg0, q3_12 distAlpha, s_CollisionState* state);

q3_12 func_8006C248(s32 packedDir, q3_12 arg1, q3_12 deltaX, q7_8 deltaZ, q7_8 radius);

bool func_8006C3D4(s_CollisionState* state, s_IpdCollisionData* collData, s32 cellIdx);

void func_8006C45C(s_CollisionState* state);

void func_8006C794(s_CollisionState* state, s32 unkState, q23_8 dist);

void func_8006C838(s_CollisionState* state, s_IpdCollisionData* collData);

// Accounts for slopes in floor height?
void func_8006CA18(s_CollisionState* state, s_IpdCollisionData* collData, s_IpdCellRange* cellRanges);

// TODO: Computes alpha related to the floor slope?
q3_12 Collision_OffsetAlphaGet(s_CollisionState* state);

// Gets sloped floor height, not the base height.
q23_8 Ipd_FloorHeightGet(q23_8 posX, q23_8 posZ, const s_CollisionState* state);

void func_8006CC9C(s_CollisionState* state);

void func_8006CF18(s_CollisionState* state, s_func_8006CF18* arg1, s32 idx);

void func_8006D01C(VECTOR3* arg0, VECTOR3* offset, q3_12 offsetAlpha, s_CollisionState* state);

void func_8006D2B4(VECTOR3* offset, s_CollisionState_44* arg1);

void func_8006D600(VECTOR3* pos, q19_12 angle, q19_12 rotX, q19_12 rotY, q19_12 dist);

void func_8006D774(s_CollisionState* state, const VECTOR3* offset0, const VECTOR3* offset1);

/** Offsets are Q23.8. */
void func_8006D7EC(s_CollisionCharaState* charaState, const SVECTOR* offset0, const SVECTOR* offset1);

#endif
