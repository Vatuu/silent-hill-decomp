#ifndef _BODYPROG_COLLISION_TRIGGER_H
#define _BODYPROG_COLLISION_TRIGGER_H

/** @brief Collision cylinder with a character collision state. TODO: Probably doesn't belong in this header. */
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
    /* 0x0  */ q19_12 positionX;
    /* 0x4  */ q19_12 positionZ;
    /* 0x8  */ q19_12 newPositionX;
    /* 0xC  */ q19_12 newPositionZ;
    /* 0x10 */ q19_12 offsetX;
    /* 0x14 */ q19_12 offsetZ;
    /* 0x18 */ q19_12 minX; // } TODO: Check. Maybe swapped.
    /* 0x1C */ q19_12 maxX; // }
    /* 0x20 */ q19_12 minZ; // } TODO: Check. Maybe swapped.
    /* 0x24 */ q19_12 maxZ; // }
    /* 0x28 */ q19_12 field_28; // Maybe XZ position.
    /* 0x2C */ q19_12 triggerHeight;
} s_func_8006F338;

/** @brief World-space collision trigger used to inform uneven terrain such as walls and stairs. */
typedef struct _CollisionTrigger
{
    /* 0x0+0  */ u8  isEndOfArray : 1;  /** `bool` | Marks last entry. */
    /* 0x0+1  */ s32 positionX    : 10; /** Meter steps. */
    /* 0x0+11 */ s32 positionZ    : 10; /** Meter steps. */
    /* 0x0+21 */ u32 sizeX        : 4;  /** Meter steps. */
    /* 0x0+25 */ u32 sizeZ        : 4;  /** Meter steps. */
    /* 0x0+29 */ u32 height       : 3;  /** Half-meter steps. Used to set `s_func_8006F338::field_2C` which is then copied by `func_8006F250`. */
} s_CollisionTrigger;
STATIC_ASSERT_SIZEOF(s_CollisionTrigger, 4);

/** @brief Collection of nearby collision triggers. */
typedef struct _ActiveCollisionTriggers
{
    /* 0x0 */ u16                 flags; /** `e_CollisionTriggerFlags` */
    /* 0x2 */ u8                  collisionTriggerCount;
    /* 0x4 */ s_CollisionTrigger* collisionTriggers[20]; // Guessed size.
} s_ActiveCollisionTriggers;

void func_8006F250(q19_12* arg0, q19_12 posX, q19_12 posZ, q19_12 offsetX, q19_12 offsetZ);

void func_8006F338(s_func_8006F338* arg0, q19_12 posX, q19_12 posZ, q19_12 offsetX, q19_12 offsetZ);

bool func_8006F3C4(s_func_8006F338* arg0, const s_CollisionTrigger* trigger);

/** @brief Gets the ceiling height, derived from active collision triggers.
 *
 * @param moveOffset Movement offset.
 * @param cylinder Collision cylinder.
 * @param cylinderRadius Cylinder radius.
 * @param cylinderHeight Cylinder height.
 * @return Ceiling height. `DEFAULT_CEILING_HEIGHT` if no ceiling exists.
 */
q19_12 Collision_CeilingHeightGet(VECTOR3* moveOffset,
                                  const s_CollisionCylinder* cylinder, q19_12 cylinderRadius, q19_12 cylinderHeight);

/** @brief Gets the offset from a world position to the edge of a collision trigger.
 * If the position is inside the trigger, the offset is (0, 0).
 *
 * @param offsetX Output offset X.
 * @param offsetZ Output offset Z.
 * @param posX World reference position X.
 * @param posZ World reference position Z.
 * @param trigger Reference collision trigger.
 */
void Collision_TriggerOffsetGet(q19_12* offsetX, q19_12* offsetZ, q19_12 posX, q19_12 posZ,
                                const s_CollisionTrigger* trigger);

#endif
