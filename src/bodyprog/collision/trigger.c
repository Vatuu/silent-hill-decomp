#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>
#include <psyq/libapi.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/collision/collision.h"
#include "bodyprog/math/math.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/sound/sound_system.h"
#include "main/rng.h"

/** @brief Computes a trigger height from half-meter height steps.
 *
 * @note The trigger height has a default offset of `Q12(-1.5f)`.
 *
 * @param steps Half-meter height steps.
 * @return Trigger height (Q19.12).
 */
#define TRIGGER_HEIGHT_GET(steps) \
    ((-Q12(steps) >> 1) - Q12(1.5f))

void func_8006F250(q19_12* arg0, q19_12 posX, q19_12 posZ, q19_12 posDeltaX, q19_12 posDeltaZ) // 0x8006F250
{
    s32              i;
    s_func_8006F338* ptr;

    ptr = PSX_SCRATCH;

    func_8006F338(ptr, posX, posZ, posDeltaX, posDeltaZ);

    // Run through collision triggers.
    for (i = 0; i < g_ActiveCollisionTriggers.collisionTriggerCount; i++)
    {
        if (func_8006F3C4(ptr, g_ActiveCollisionTriggers.collisionTriggers[i]))
        {
            break;
        }
    }

    if (ptr->field_28 == Q12(1.0f))
    {
        arg0[0] = Q12(32.0f);
        arg0[1] = Q12(-16.0f);
    }
    else
    {
        arg0[0] = Math_MulFixed(Vc_VectorMagnitudeCalc(ptr->field_10, Q12(0.0f), ptr->field_14), ptr->field_28, Q12_SHIFT);
        arg0[1] = ptr->triggerHeight;
    }
}

void func_8006F338(s_func_8006F338* arg0, q19_12 posX, q19_12 posZ, q19_12 posDeltaX, q19_12 posDeltaZ) // 0x8006F338
{
    q19_12 newPosX;
    q19_12 field_4;

    newPosX = posX + posDeltaX;

    arg0->field_0  = posX;
    arg0->field_4  = posZ;
    arg0->field_10 = posDeltaX;
    arg0->field_8  = posX + posDeltaX;
    arg0->field_28 = Q12(1.0f);
    arg0->triggerHeight = Q12(1048560.0f);
    arg0->field_14 = posDeltaZ;

    arg0->field_C = posZ + posDeltaZ;
    if (newPosX >= arg0->field_0)
    {
        arg0->field_18 = arg0->field_0;
        arg0->field_1C = arg0->field_8;
    }
    else
    {
        arg0->field_18 = posX + posDeltaX;
        arg0->field_1C = arg0->field_0;
    }

    field_4 = arg0->field_4;
    if (arg0->field_C >= arg0->field_4)
    {
        arg0->field_20 = field_4;
        arg0->field_24 = arg0->field_C;
        return;
    }
    else
    {
        arg0->field_20 = arg0->field_C;
        arg0->field_24 = arg0->field_4;
    }
}

bool func_8006F3C4(s_func_8006F338* arg0, const s_CollisionTrigger* trigger) // 0x8006F3C4
{
    q19_12 temp_s1;
    q19_12 var_v1;
    q19_12 minX;
    q19_12 maxX;
    q19_12 minZ;
    q19_12 maxZ;
    q19_12 var_s1;
    q19_12 var_v0;
    q19_12 var_v0_2;

    // Define AABB bounds.
    minX = Q12(trigger->positionX);
    maxX = Q12(trigger->positionX + trigger->sizeX);
    minZ = Q12(trigger->positionZ);
    maxZ = Q12(trigger->positionZ + trigger->sizeZ);

    // Check for AABB intersection.
    if ((minX >= arg0->field_1C || arg0->field_18 >= maxX) &&
        (minZ >= arg0->field_24 || arg0->field_20 >= maxZ))
    {
        return false;
    }

    if (arg0->field_0 >= minX && maxX >= arg0->field_0 &&
        arg0->field_4 >= minZ && maxZ >= arg0->field_4)
    {
        arg0->field_28 = Q12(0.0f);
        arg0->triggerHeight = TRIGGER_HEIGHT_GET(trigger->height);
    }
    else
    {
        if (arg0->field_10 >= Q12(0.0f))
        {
            if (arg0->field_14 >= Q12(0.0f))
            {
                var_s1   = minX;
                var_v0_2 = minZ;
            }
            else
            {
                var_s1   = minX;
                var_v0_2 = maxZ;
            }
        }
        else
        {
            if (arg0->field_14 >= Q12(0.0f))
            {
                var_s1   = maxX;
                var_v0_2 = minZ;
            }
            else
            {
                var_s1   = maxX;
                var_v0_2 = maxZ;
            }
        }

        // TODO: What are these shifts? Converts up to Q24, then down to Q8??
        temp_s1 = Vw_LineSegmentIntersectionCheck(FP_TO(arg0->field_10, Q12_SHIFT) >> 16, FP_TO(arg0->field_14, Q12_SHIFT) >> 16, FP_TO(var_v0_2 - arg0->field_4, Q12_SHIFT) >> 16,
                                FP_TO(minX - arg0->field_0, Q12_SHIFT) >> 16, FP_TO(maxX - arg0->field_0, Q12_SHIFT) >> 16);
        var_v0  = Vw_LineSegmentIntersectionCheck(FP_TO(arg0->field_14, Q12_SHIFT) >> 16, FP_TO(arg0->field_10, Q12_SHIFT) >> 16, FP_TO(var_s1 - arg0->field_0, Q12_SHIFT) >> 16,
                                FP_TO(minZ - arg0->field_4, Q12_SHIFT) >> 16, FP_TO(maxZ - arg0->field_4, Q12_SHIFT) >> 16);

        if (var_v0 >= temp_s1)
        {
            var_v1 = temp_s1;
        }
        else
        {
            var_v1 = var_v0;
        }

        if (var_v1 < arg0->field_28)
        {
            arg0->field_28 = var_v1;
            arg0->triggerHeight = TRIGGER_HEIGHT_GET(trigger->height);
        }
    }

    return arg0->field_28 == 0;
}

q19_12 Collision_CeilingHeightGet(VECTOR3* moveOffset,
                                  const s_CollisionCylinder* cylinder, q19_12 cylinderRadius, q19_12 cylinderHeight) // 0x8006F620
{
    q19_12              projOffsetToTriggerX;
    q19_12              projOffsetToTriggerZ;
    q19_12              offsetToTriggerX;
    q19_12              offsetToTriggerZ;
    q19_12              cylinderTop;
    q19_12              projCylinderTop;
    q19_12              pushOffsetX;
    q19_12              pushOffsetZ;
    q19_12              cylinderTopToCeilDist;
    q19_12              triggerHeight;
    q19_12              distToTrigger;
    q19_12              pushDist;
    q19_12              projDistToTrigger;
    q19_12              angleToTrigger;
    q19_12              allowedIntersectDist;
    s32                 i;
    q19_12              moveOffsetX;
    q19_12              moveOffsetZ;
    q19_12              ceilHeight;
    q19_12              headroom;
    s_CollisionTrigger* curTrigger;

    ceilHeight  = Q12(DEFAULT_CEILING_HEIGHT);
    pushOffsetX = Q12(0.0f);
    pushOffsetZ = Q12(0.0f);

    // Compute start parameters.
    moveOffsetX     = moveOffset->vx;
    moveOffsetZ     = moveOffset->vz;
    cylinderTop     = cylinder->position.vy + cylinderHeight;
    projCylinderTop = cylinderTop + moveOffset->vy;

    // Run through collision triggers.
    for (i = 0; i < g_ActiveCollisionTriggers.collisionTriggerCount; i++)
    {
        curTrigger = g_ActiveCollisionTriggers.collisionTriggers[i];

        // Check if trigger overhead is avoided.
        triggerHeight = TRIGGER_HEIGHT_GET(curTrigger->height);
        if ((projCylinderTop - triggerHeight) >= Q12(0.0f))
        {
            continue;
        }

        // Check rough cylinder-trigger collision at projected position.
        Collision_TriggerOffsetGet(&projOffsetToTriggerX, &projOffsetToTriggerZ,
                                   cylinder->position.vx + moveOffsetX, cylinder->position.vz + moveOffsetZ,
                                   curTrigger);
        if (MAX(ABS(projOffsetToTriggerX), ABS(projOffsetToTriggerZ)) >= cylinderRadius)
        {
            continue;
        }

        // Check accurate cylinder-trigger collision at projected position.
        projDistToTrigger = Vc_VectorMagnitudeCalc(projOffsetToTriggerX, Q12(0.0f), projOffsetToTriggerZ);
        if (projDistToTrigger >= cylinderRadius)
        {
            continue;
        }

        // Handle horizontal edge rejection.
        if (projDistToTrigger > Q12(0.0f))
        {
            Collision_TriggerOffsetGet(&offsetToTriggerX, &offsetToTriggerZ,
                                       cylinder->position.vx, cylinder->position.vz,
                                       curTrigger);

            // Compute allowed intersection depth.
            allowedIntersectDist = INTERSECTION_BUFFER;
            distToTrigger        = Vc_VectorMagnitudeCalc(offsetToTriggerX, Q12(0.0f), offsetToTriggerZ);
            if ((cylinderRadius - distToTrigger) <= INTERSECTION_BUFFER)
            {
                allowedIntersectDist = cylinderRadius - distToTrigger;
            }

            // Check for projected intersection.
            if ((projDistToTrigger - distToTrigger) < allowedIntersectDist)
            {
                // Compute push distance away from trigger.
                angleToTrigger = ratan2(projOffsetToTriggerX, projOffsetToTriggerZ);
                pushDist       = allowedIntersectDist - (projDistToTrigger - distToTrigger);

                // Compute push offset.
                pushOffsetX = Math_MulFixed(pushDist, Math_Sin(angleToTrigger), Q12_SHIFT);
                pushOffsetZ = Math_MulFixed(pushDist, Math_Cos(angleToTrigger), Q12_SHIFT);
            }
        }
        // Handle predictive ceiling rejection.
        else
        {
            // Track lowest ceiling.
            if (triggerHeight < ceilHeight)
            {
                ceilHeight = triggerHeight;
            }

            // Reset move offset.
            moveOffsetX = moveOffset->vx;
            moveOffsetZ = moveOffset->vz;
            break;
        }

        // Apply push offset.
        moveOffsetX += pushOffsetX;
        moveOffsetZ += pushOffsetZ;
    }

    // Update movement offset.
    moveOffset->vx = moveOffsetX;
    moveOffset->vz = moveOffsetZ;

    // Restrict vertical movement.
    if (ceilHeight != Q12(DEFAULT_CEILING_HEIGHT))
    {
        // Compute headroom.
        headroom              = INTERSECTION_BUFFER;
        cylinderTopToCeilDist = ceilHeight - cylinderTop;
        if (cylinderTopToCeilDist < INTERSECTION_BUFFER)
        {
            headroom = cylinderTopToCeilDist;
        }

        // Clamp movement to ceiling.
        if (moveOffset->vy < headroom)
        {
            moveOffset->vy = headroom;
        }
    }

    return ceilHeight;
}

void Collision_TriggerOffsetGet(q19_12* offsetX, q19_12* offsetZ, q19_12 posX, q19_12 posZ,
                                const s_CollisionTrigger* trigger) // 0x8006F8FC
{
    q19_12 minX;
    q19_12 maxX;
    q19_12 minZ;
    q19_12 maxZ;

    // Define AABB bounds.
    minX = FP_TO(trigger->positionX, Q12_SHIFT);
    maxX = FP_TO(trigger->positionX + trigger->sizeX, Q12_SHIFT);
    minZ = FP_TO(trigger->positionZ, Q12_SHIFT);
    maxZ = FP_TO(trigger->positionZ + trigger->sizeZ, Q12_SHIFT);

    if (posX < minX)
    {
        *offsetX = posX - minX;
    }
    else if (maxX >= posX)
    {
        *offsetX = Q12(0.0f);
    }
    else
    {
        *offsetX = posX - maxX;
    }

    if (posZ < minZ)
    {
        *offsetZ = posZ - minZ;
        return;
    }
    else if (maxZ >= posZ)
    {
        *offsetZ = Q12(0.0f);
        return;
    }
    else
    {
        *offsetZ = posZ - maxZ;
        return;
    }
}
