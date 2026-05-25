#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>
#include <psyq/libapi.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player.h"
#include "bodyprog/sound/sound_system.h"
#include "main/rng.h"

// ========================================
// COMBAT 1
// ========================================

s32 Chara_NpcIdxGet(s_SubCharacter* chara) // 0x8005C7D0
{
    s32             i;
    s_SubCharacter* curNpc;
    s_SubCharacter* player;

    i = 0;

    if (chara == &g_SysWork.playerWork.player)
    {
        return ARRAY_SIZE(g_SysWork.npcs);
    }

    curNpc = &g_SysWork.npcs[0];
    player = chara;
    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs); i++, curNpc++)
    {
        if (player == curNpc)
        {
            return i;
        }
    }

    return NO_VALUE;
}

void Chara_CollisionShapeOffsetsUpdate(s_CharaShapeOffsets* offsets, s_SubCharacter* chara) // 0x8005C814
{
    q3_12 boxOffsetX;
    q3_12 boxOffsetZ;
    q3_12 cylinderOffsetX;
    q3_12 cylinderOffsetZ;
    q3_12 sinRotY;
    q3_12 cosRotY;

    // Get relative shape offsets.
    boxOffsetX      = offsets->box.vx;
    boxOffsetZ      = offsets->box.vz;
    cylinderOffsetX = offsets->cylinder.vx;
    cylinderOffsetZ = offsets->cylinder.vz;

    // Compute XZ plane heading sine and cosine.
    cosRotY = Math_Cos(chara->rotation.vy);
    sinRotY = Math_Sin(chara->rotation.vy);

    // Update shape offsets.
    chara->collision.shapeOffsets.box.vx      = FP_FROM(( boxOffsetX      * cosRotY) + (boxOffsetZ      * sinRotY), Q12_SHIFT);
    chara->collision.shapeOffsets.box.vz      = FP_FROM((-boxOffsetX      * sinRotY) + (boxOffsetZ      * cosRotY), Q12_SHIFT);
    chara->collision.shapeOffsets.cylinder.vx = FP_FROM(( cylinderOffsetX * cosRotY) + (cylinderOffsetZ * sinRotY), Q12_SHIFT);
    chara->collision.shapeOffsets.cylinder.vz = FP_FROM((-cylinderOffsetX * sinRotY) + (cylinderOffsetZ * cosRotY), Q12_SHIFT);
}

s32 Chara_MovementUpdate(s_SubCharacter* chara, s_CollisionResult* collResult) // 0x8005C944
{
    s_CollisionResult newCollResult;
    VECTOR3           offset;
    q3_12             headingAngle;
    q19_12            moveSpeed;
    s32               moveDist;
    s32               scaleRestoreShift;
    s32               scaleReduceShift;
    s32               temp_v0;
    q19_12            sinHeadingAngle;
    s32               wallResponse;

    headingAngle      = chara->headingAngle;
    moveSpeed         = Q12_MULT_PRECISE(g_DeltaTime, chara->moveSpeed);
    scaleRestoreShift = OVERFLOW_GUARD(moveSpeed);
    scaleReduceShift  = scaleRestoreShift >> 1;

    sinHeadingAngle = Math_Sin(headingAngle);
    moveDist        = moveSpeed >> scaleReduceShift;
    temp_v0         = sinHeadingAngle >> scaleReduceShift;

    offset.vx = Q12_MULT_PRECISE(moveDist, temp_v0) << scaleRestoreShift;
    offset.vz = Q12_MULT_PRECISE(moveDist, Math_Cos(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vy = Q12_MULT_PRECISE(g_DeltaTime, chara->fallSpeed);

    wallResponse = Collision_WallDetect(&newCollResult, &offset, chara);

    chara->position.vx += newCollResult.offset.vx;
    chara->position.vy += newCollResult.offset.vy;
    chara->position.vz += newCollResult.offset.vz;

    // Warp to ground.
    if (chara->position.vy > newCollResult.surface.groundHeight)
    {
        chara->position.vy = newCollResult.surface.groundHeight;
        chara->fallSpeed   = Q12(0.0f);
    }

    if (collResult != NULL)
    {
        *collResult = newCollResult;
    }

    return wallResponse;
}

s32 func_8005CB20(s_SubCharacter* chara, s_CollisionResult* collResult, q3_12 offsetX, q3_12 offsetZ) // 0x8005CB20
{
    s_CollisionResult collResult0;
    VECTOR3           offset; // Q19.12
    q19_12            headingAngle;
    q19_12            moveSpeed;
    s32               temp_s0_2;
    s32               scaleRestoreShift;
    s32               scaleReduceShift;
    s32               temp_v0_2;
    s32               temp_v0_4;
    q19_12            sinHeadingAngle;
    s32               ret;

    headingAngle      = chara->headingAngle;
    moveSpeed         = Q12_MULT_PRECISE(g_DeltaTime, chara->moveSpeed);
    scaleRestoreShift = OVERFLOW_GUARD(moveSpeed);
    scaleReduceShift  = scaleRestoreShift >> 1;

    sinHeadingAngle = Math_Sin(headingAngle);
    temp_s0_2 = moveSpeed >> scaleReduceShift;
    temp_v0_2 = sinHeadingAngle >> scaleReduceShift;
    offset.vx = (s32)Q12_MULT_PRECISE(temp_s0_2, temp_v0_2) << scaleRestoreShift;

    temp_v0_4 = Math_Cos(headingAngle) >> scaleReduceShift;
    offset.vz = (s32)Q12_MULT_PRECISE(temp_s0_2, temp_v0_4) << scaleRestoreShift;

    sinHeadingAngle = chara->fallSpeed;
    offset.vx += offsetX;
    offset.vy  = Q12_MULT_PRECISE(g_DeltaTime, sinHeadingAngle);
    offset.vz += offsetZ;

    ret = Collision_WallDetect(&collResult0, &offset, chara);

    chara->position.vx += collResult0.offset.vx;
    chara->position.vy += collResult0.offset.vy;
    chara->position.vz += collResult0.offset.vz;

    if (chara->position.vy > collResult0.surface.groundHeight)
    {
        chara->position.vy = collResult0.surface.groundHeight;
        chara->fallSpeed   = Q12(0.0f);
    }

    if (collResult != NULL)
    {
        *collResult = collResult0;
    }

    return ret;
}

INCLUDE_ASM("bodyprog/nonmatchings/bodyprog_combat_8005BF38", func_8005CD38); // 0x8005CD38

bool func_8005D50C(s32* targetNpcIdx, q3_12* rotToTargetX, q3_12* rotToTargetY, const VECTOR3* attackPos,
                   u32 npcIdx, q19_12 angleConstraint) // 0x8005D50C
{
    s_RayTrace trace;
    VECTOR3    offsetToTarget; // Q19.12
    q3_12      rotToTargetX0;
    q3_12      rotToTargetY0;
    q3_12      curRotToTargetY;
    q3_12      curRotToTargetX;
    q19_12     targetDist;
    q19_12     curDistToTarget;
    s32        i;

    #define npc g_SysWork.npcs[npcIdx]

    // Check if NPC index is valid.
    if (npcIdx >= ARRAY_SIZE(g_SysWork.npcs))
    {
        return false;
    }

    offsetToTarget.vx = (npc.position.vx + npc.collision.shapeOffsets.box.vx) - attackPos->vx;
    offsetToTarget.vy = (npc.position.vy + npc.collision.box.offsetY)         - attackPos->vy;
    offsetToTarget.vz = (npc.position.vz + npc.collision.shapeOffsets.box.vz) - attackPos->vz;

    // Compute rotation to target.
    targetDist   = Math_Vector2MagCalcSafeQ6(offsetToTarget.vx, offsetToTarget.vz);
    rotToTargetY0 = ratan2(offsetToTarget.vx, offsetToTarget.vz);
    rotToTargetX0 = ratan2(targetDist, offsetToTarget.vy);

    *targetNpcIdx = npcIdx;
    *rotToTargetX = rotToTargetX0;
    *rotToTargetY = rotToTargetY0;

    // Run through NPCs to find closer targetable NPC.
    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs); i++)
    {
        #define curNpc g_SysWork.npcs[i]

        // Check if NPC is valid.
        if (curNpc.model.charaId == Chara_None ||
            curNpc.health < Q12(0.0f)          ||
            i == npcIdx)
        {
            continue;
        }

        // Compute offset.
        offsetToTarget.vx = (curNpc.position.vx + curNpc.collision.shapeOffsets.box.vx) - attackPos->vx;
        offsetToTarget.vy = (curNpc.position.vy + curNpc.collision.box.offsetY)         - attackPos->vy;
        offsetToTarget.vz = (curNpc.position.vz + curNpc.collision.shapeOffsets.box.vz) - attackPos->vz;

        // Check if Y-axis rotation to new target is within range.
        curRotToTargetY = ratan2(offsetToTarget.vx, offsetToTarget.vz);
        if (angleConstraint < ABS(Math_AngleNormalizeSigned(rotToTargetY0 - curRotToTargetY)))
        {
            continue;
        }

        // Check if distance is closer.
        curDistToTarget = Math_Vector2MagCalcSafeQ6(offsetToTarget.vx, offsetToTarget.vz);
        if (targetDist < curDistToTarget)
        {
            continue;
        }

        // Check if X-axis rotation to new target is within range.
        curRotToTargetX = ratan2(curDistToTarget, offsetToTarget.vy);
        if (angleConstraint < ABS(Math_AngleNormalizeSigned(rotToTargetX0 - curRotToTargetX)))
        {
            continue;
        }

        // Track closer targetable NPC.
        if (Ray_CharaTraceQuery(&trace, attackPos, &offsetToTarget, &g_SysWork.playerWork.player) &&
            trace.character == &g_SysWork.npcs[i])
        {
            *targetNpcIdx = i;
            *rotToTargetX = curRotToTargetX;
            targetDist    = curDistToTarget;
            *rotToTargetY = curRotToTargetY;
        }

        #undef curNpc
    }

    return true;

    #undef npc
}
