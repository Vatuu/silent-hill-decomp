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

// Note - Will: I added a bunch of poorly written comments among the code
// to have a better follow up of a code comprehension, some may be
// misleading as I'm mostly based on code functionallity with barely any
// in-game test.
// Please delete them or rewrite them properly after properly recognizing
// the function purpose.

s_ActiveCollisionTriggers g_ActiveCollisionTriggers;

void Collision_Init(void) // 0x800697EC
{
    Collision_FlagsSet(CollisionTriggerFlag_0);
    g_ActiveCollisionTriggers.collisionTriggerCount = 0;
}

u16 Collision_FlagsGet(void) // 0x80069810
{
    return g_ActiveCollisionTriggers.flags;
}

void Collision_FlagsSet(u16 collFlags) // 0x80069820
{
    g_ActiveCollisionTriggers.flags = collFlags;
}

void Collision_FlagBitsSet(u16 collFlags) // 0x8006982C
{
    g_ActiveCollisionTriggers.flags |= collFlags;
}

void Collision_FlagBitsClear(s32 collFlags) // 0x80069844
{
    g_ActiveCollisionTriggers.flags = (g_ActiveCollisionTriggers.flags & ~collFlags) | CollisionTriggerFlag_0;
}

void Collision_NearbyTriggersGet(q19_12 posX, q19_12 posZ, s_CollisionTrigger* triggers) // 0x80069860
{
    #define AABB_BUFFER Q12(16.0f)

    s_CollisionTrigger* curTrigger;
    q19_12              minX;
    q19_12              maxX;
    q19_12              minZ;
    q19_12              maxZ;

    g_ActiveCollisionTriggers.collisionTriggerCount = 0;

    // Run through collision triggers.
    for (curTrigger = triggers; !curTrigger->isEndOfArray; curTrigger++)
    {
        // Define AABB bounds.
        minX = FP_TO(curTrigger->positionX, Q12_SHIFT);
        maxX = FP_TO(curTrigger->positionX + curTrigger->sizeX, Q12_SHIFT);
        minZ = FP_TO(curTrigger->positionZ, Q12_SHIFT);
        maxZ = FP_TO(curTrigger->positionZ + curTrigger->sizeZ, Q12_SHIFT);

        // Expand AABB.
        minX -= AABB_BUFFER;
        maxX += AABB_BUFFER;
        minZ -= AABB_BUFFER;
        maxZ += AABB_BUFFER;

        // Collect collided trigger.
        if (posX >= minX && maxX >= posX &&
            posZ >= minZ && maxZ >= posZ)
        {
            g_ActiveCollisionTriggers.collisionTriggers[g_ActiveCollisionTriggers.collisionTriggerCount] = curTrigger;
            g_ActiveCollisionTriggers.collisionTriggerCount++;
        }
    }

    #undef AABB_BUFFER
}

void IpdCollData_FixOffsets(s_IpdCollisionData* collData) // 0x8006993C
{
    collData->collisionVertices = (u8*)collData->collisionVertices + (u32)collData;
    collData->surfaces    = (u8*)collData->surfaces + (u32)collData;
    collData->subcells      = (u8*)collData->subcells + (u32)collData;
    collData->ptr_18            = (u8*)collData->ptr_18 + (u32)collData;
    collData->subcellRanges     = (u8*)collData->subcellRanges + (u32)collData;
    collData->ptr_28            = (u8*)collData->ptr_28 + (u32)collData;
    collData->ptr_2C            = (u8*)collData->ptr_2C + (u32)collData;
}

void Collision_SubcellChecksReset(s_IpdCollisionData* collData) // 0x80069994
{
    s32* curPtr;

    collData->subcellsChecksCount++;
    if (collData->subcellsChecksCount > (sizeof(collData->subcellCheckIdx) - 4))
    {
        collData->subcellsChecksCount = 0;

        // TODO: Is this `memset`/`bzero`?
        for (curPtr = &collData->subcellCheckIdx[0]; curPtr < &collData->subcellCheckIdx[sizeof(collData->subcellCheckIdx)]; curPtr++)
        {
            *curPtr = 0;
        }
    }
}

void Collision_SubcellChecksCountUpdate(s_IpdCollisionData* collData) // 0x800699E4
{
    collData->subcellsChecksCount++;
}

void Collision_SurfaceGet(s_CollisionSurface* surface, q19_12 posX, q19_12 posZ) // 0x800699F8
{
    s_CollisionCylinder cylinder;
    VECTOR3             pos;
    s_CollisionState    state;
    s_IpdCollisionData* collData;

    pos.vx = Q12(0.0f);
    pos.vy = Q12(0.0f);
    pos.vz = Q12(0.0f);

    collData = Ipd_CollisionDataGet(posX, posZ);
    if (collData == NULL)
    {
        surface->groundHeight = Q12(8.0f);
        surface->tiltAngleZ   = Q12_ANGLE(0.0f);
        surface->tiltAngleX   = Q12_ANGLE(0.0f);
        surface->groundType   = GroundType_Default;
        return;
    }

    cylinder.position.vx = posX;
    cylinder.position.vy = Q12(0.0f);
    cylinder.position.vz = posZ;
    cylinder.bottom      = Q12(0.0f);
    cylinder.top         = Q12(0.0f);
    cylinder.radius      = Q12(0.0f);
    Collision_CollStateInit(&state, &pos, &cylinder, false);

    state.isCharaMoving = false;
    state.field_0_9     = false;
    state.field_0_10    = true;
    Collision_CharaCollisionHandling(&state, collData);

    if (state.heightDisabled == true)
    {
        surface->groundType   = GroundType_Default;
        surface->groundHeight = Q12(8.0f);
    }
    else
    {
        surface->groundType   = state.groundType;
        surface->groundHeight = Q8_TO_Q12(Ipd_GroundHeightGet(state.charaState.positionFromX, state.charaState.positionFromZ, &state));
    }

    surface->tiltAngleX = state.tiltAngleX;
    surface->tiltAngleZ = state.tiltAngleZ;
}

s32 Collision_WallDetect(s_CollisionResult* collResult, const VECTOR3* moveOffset, s_SubCharacter* chara) // 0x80069B24
{
    s32 stackPtr;
    s32 response;

    stackPtr = SetSp(PSX_SCRATCH_ADDR(0x3D8));
    response = Collision_WallResponse(collResult, moveOffset, chara, Collision_CharaCollisionSetup(collResult, moveOffset, chara));
    SetSp(stackPtr);
    return response;
}

s32 Collision_WallResponse(s_CollisionResult* collResult, const VECTOR3* moveOffset, s_SubCharacter* chara, s32 response) // 0x80069BA8
{
    #define POINT_COUNT          9
    #define ANGLE_STEP           Q12_ANGLE(370.0f / POINT_COUNT) // @bug? Maybe `360.0f` was intended.
    #define WALL_COUNT_THRESHOLD 3                               // Unknown purpose.
    #define WALL_HEIGHT          Q12(0.5f)

    s_CollisionSurface surface;
    e_CollisionType    collType;
    q19_12             groundHeight;
    q19_12             wallHeightBound;
    s32                i;
    s32                wallCount;
    s32                groundType; // `e_GroundType`

    if (response == NO_VALUE)
    {
        response = true;

        if (chara == &g_SysWork.playerWork && chara->health > Q12(0.0f))
        {
            Collision_GroundProbeRadial(collResult, &chara->position, chara->position.vy, chara->rotation.vy);
        }
    }

    switch (chara->model.charaId)
    {
        case Chara_Harry:
        case Chara_Groaner:
        case Chara_Wormhead:
        case Chara_LarvalStalker:
        case Chara_Stalker:
        case Chara_GreyChild:
        case Chara_Mumbler:
        case Chara_Creeper:
        case Chara_Romper:
        case Chara_PuppetNurse:
        case Chara_PuppetDoctor:
            wallHeightBound = chara->position.vy - WALL_HEIGHT;

            switch (collResult->surface.groundType)
            {
                case GroundType_None:
                    collType = CollisionType_Unk2;
                    break;

                default:
                    collType = (collResult->surface.groundHeight < wallHeightBound) ? CollisionType_Wall : CollisionType_None;
                    break;
            }

            wallCount = 0;
            if (collType == CollisionType_None)
            {
                break;
            }

            for (i = 0, groundType = GroundType_None; i < POINT_COUNT; i++)
            {
                Collision_SurfaceGet(&surface,
                                     chara->position.vx + Q12_MULT(Math_Sin(i * ANGLE_STEP), Q12(0.2f)),
                                     chara->position.vz + Q12_MULT(Math_Cos(i * ANGLE_STEP), Q12(0.2f)));

                switch (collType)
                {
                    case CollisionType_Wall:
                        if (surface.groundHeight < wallHeightBound)
                        {
                            wallCount++;
                        }
                        break;

                    case CollisionType_Unk2:
                        if (surface.groundType != GroundType_None)
                        {
                            groundType   = surface.groundType;
                            groundHeight = surface.groundHeight;
                        }
                        break;
                }
            }

            switch (collType)
            {
                case CollisionType_Wall:
                    if (wallCount < WALL_COUNT_THRESHOLD)
                    {
                        collResult->surface.groundHeight = chara->position.vy;
                    }
                    break;

                case CollisionType_Unk2:
                    if (groundType != GroundType_None)
                    {
                        collResult->surface.groundHeight = groundHeight;
                        collResult->surface.groundType   = GroundType_None;
                    }
                    break;
            }
            break;
    }

    return response;

    #undef POINT_COUNT
    #undef ANGLE_STEP
    #undef WALL_COUNT_THRESHOLD
    #undef WALL_HEIGHT
}

void Collision_GroundProbeRadial(s_CollisionResult* collResult, const VECTOR3* pos,
                                 q19_12 startGroundHeight, q19_12 startHeadingAngle) // 0x80069DF0
{
    #define POINT_COUNT 16
    #define ANGLE_STEP  Q12_ANGLE(360.0f / POINT_COUNT)

    q19_12             groundHeights[POINT_COUNT];
    s_CollisionSurface surface;
    q19_12             angle;
    s32                var_a0;
    q19_12             groundHeight;
    s32                var_s0;
    s32                i;
    q19_12             groundHeightMax;
    q19_12             groundHeightMin;
    s32                lowestGroundHeightIdx;

    groundHeightMin       = Q12(-30.0f);
    groundHeightMax       = Q12(30.0f);
    lowestGroundHeightIdx = 0;

    // Collect ground heights around position?
    for (i = 0; i < POINT_COUNT; i++)
    {
        Collision_SurfaceGet(&surface,
                             pos->vx + Math_Sin((startHeadingAngle & 0xF) + (i * ANGLE_STEP)),
                             pos->vz + Math_Cos((startHeadingAngle & 0xF) + (i * ANGLE_STEP)));
        groundHeights[i] = surface.groundHeight;

        if (groundHeightMin < surface.groundHeight)
        {
            groundHeightMin       = surface.groundHeight;
            lowestGroundHeightIdx = i;
        }

        if (surface.groundHeight < groundHeightMax)
        {
            groundHeightMax = surface.groundHeight;
        }
    }

    groundHeight = (groundHeightMin + groundHeightMax) >> 1; // `/ 2`.
    if (groundHeight < (startGroundHeight - INTERSECTION_BUFFER))
    {
        groundHeight = startGroundHeight - INTERSECTION_BUFFER;
    }

    for (i = lowestGroundHeightIdx + 1, var_a0 = lowestGroundHeightIdx;
         i < (lowestGroundHeightIdx + POINT_COUNT) && groundHeight < groundHeights[i & 0xF];
         i++)
    {
        var_a0 = i;
    }

    for (i = lowestGroundHeightIdx - 1, var_s0 = lowestGroundHeightIdx;
         i < (lowestGroundHeightIdx - POINT_COUNT) && groundHeight < groundHeights[i & 0xF];
         i--)
    {
        var_s0 = i;
    }

    angle = ((var_s0 + var_a0) << 8) >> 1;
    collResult->offset.vx = Q12_MULT_PRECISE(Math_Sin(angle), Q12(1.0f / 16.0f));
    collResult->offset.vz = Q12_MULT_PRECISE(Math_Cos(angle), Q12(1.0f / 16.0f));

    #undef POINT_COUNT
    #undef ANGLE_STEP
}

bool Collision_CharaCollisionSetup(s_CollisionResult* collResult, const VECTOR3* moveOffset, s_SubCharacter* chara) // 0x80069FFC
{
    s_CollisionCylinder cylinder;
    VECTOR3             offsetCpy;
    s32                 collDataIdx;
    s32                 charaCount;
    bool                cond;

    // Set collision cylinder position.
    cylinder.position.vx = chara->position.vx + chara->collision.shapeOffsets.cylinder.vx;
    cylinder.position.vy = chara->position.vy - Q12(0.02f);
    cylinder.position.vz = chara->position.vz + chara->collision.shapeOffsets.cylinder.vz;

    if (Ipd_CollisionDataGet(chara->position.vx, chara->position.vz) == NULL)
    {
        Collision_DefaultResultSet(collResult, Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(8.0f));
        return true;
    }

    // Set collision cylinder state.
    cylinder.top            = chara->collision.box.top;
    cylinder.bottom         = chara->collision.box.bottom;
    cylinder.radius         = chara->collision.cylinder.radius;
    cylinder.collisionState = chara->collision.state;

    offsetCpy = *moveOffset;

    switch (chara->model.charaId)
    {
        case Chara_Harry:
        case Chara_Groaner:
        case Chara_Wormhead:
        case Chara_Romper:
            cond = true;
            break;

        default:
            cond = false;
            break;
    }

    return func_8006A4A8(collResult, &offsetCpy, &cylinder, cond,
                         Ipd_ActiveChunksCollisionDataGet(&collDataIdx), collDataIdx, NULL, 0,
                         Collision_CollidableCharasGet(&charaCount, chara, true), charaCount);
}

void Collision_DefaultResultSet(s_CollisionResult* collResult, q19_12 offsetX, q19_12 offsetY, q19_12 offsetZ, q19_12 groundHeight) // 0x8006A178
{
    collResult->offset.vx            = offsetX;
    collResult->offset.vy            = offsetY;
    collResult->offset.vz            = offsetZ;
    collResult->surface.tiltAngleZ   = Q12_ANGLE(0.0f);
    collResult->surface.tiltAngleX   = Q12_ANGLE(0.0f);
    collResult->surface.groundType   = GroundType_Default;
    collResult->ceilingHeight        = Q12(DEFAULT_CEILING_HEIGHT);
    collResult->surface.groundHeight = groundHeight;
}

s_SubCharacter** Collision_CollidableCharasGet(s32* collCharaCount, const s_SubCharacter* excludedChara, bool includePlayer) // 0x8006A1A4
{
    s_SubCharacter*         curChara;
    static s_SubCharacter*  collCharas[NPC_COUNT_MAX + 1]; /** Enough for all NPCs and player. */
    static s_SubCharacter** curCollChara;                  /** Array of active characters. */

    // Filter invalid case.
    if (excludedChara != NULL &&
        (excludedChara->model.charaId == Chara_None ||
         excludedChara->collision.state == CharaCollisionState_Ignore ||
        (excludedChara->collision.state == CharaCollisionState_Player && includePlayer == true)))
    {
        *collCharaCount = 0;
        return &collCharas;
    }

    *collCharaCount = 0;
    curCollChara    = &collCharas;

    // Collect collidable NPCs.
    for (curChara = &g_SysWork.npcs[0]; curChara < &g_SysWork.npcs[ARRAY_SIZE(g_SysWork.npcs)]; curChara++)
    {
        if (curChara->model.charaId != Chara_None)
        {
            if (curChara->collision.state != CharaCollisionState_Ignore &&
                (curChara->collision.state != CharaCollisionState_Player || includePlayer != true) &&
                curChara != excludedChara &&
                (includePlayer != true || excludedChara == NULL ||
                 excludedChara->collision.state != CharaCollisionState_4 ||
                 curChara->collision.state >= excludedChara->collision.state))
            {
                *collCharaCount += 1;
                *curCollChara    = curChara;
                curCollChara++;
                curChara->collision.field_E0 = 0;
            }
        }
    }

    // Collect collidable player.
    curChara = &g_SysWork.playerWork.player;
    if (curChara->model.charaId != Chara_None)
    {
        if (curChara->collision.state != CharaCollisionState_Ignore &&
            (curChara->collision.state != CharaCollisionState_Player || includePlayer != true) &&
            curChara != excludedChara &&
            (includePlayer != true || excludedChara == NULL ||
             excludedChara->collision.state != CharaCollisionState_4 ||
             curChara->collision.state >= excludedChara->collision.state))
        {
            *collCharaCount += 1;
            *curCollChara    = curChara;
            curCollChara++;
            curChara->collision.field_E0 = 0;
        }
    }

    return &collCharas;
}

s32 Collision_OffsetCheck(s_CollisionResult* collResult, VECTOR* offset, const s_CollisionCylinder* cylinder) // 0x8006A3B4
{
    s32 stackPtr;
    s32 var1;

    stackPtr = SetSp(PSX_SCRATCH_ADDR(0x3D8));
    var1 = func_8006A42C(collResult, offset, cylinder);
    SetSp(stackPtr);

    if (var1 == NO_VALUE)
    {
        var1 = 1;
    }

    return var1;
}

s32 func_8006A42C(s_CollisionResult* collResult, const VECTOR3* offset, const s_CollisionCylinder* cylinder) // 0x8006A42C
{
    VECTOR3 offsetCpy;
    s32     collDataIdx;

    offsetCpy = *offset;

    return func_8006A4A8(collResult, &offsetCpy, cylinder, false,
                         Ipd_ActiveChunksCollisionDataGet(&collDataIdx), collDataIdx, NULL, 0, NULL, 0);
}

bool func_8006A4A8(s_CollisionResult* collResult, VECTOR3* moveOffset, const s_CollisionCylinder* cylinder, bool arg3,
                   s_IpdCollisionData** collDataPtrs, s32 collDataIdx, s_func_8006CF18* arg6, s32 arg7,
                   s_SubCharacter** charas, s32 charaCount) // 0x8006A4A8
{
    s_CollisionState     collState;
    VECTOR3              sp120; // Q19.12
    VECTOR3              moveOffset1;
    VECTOR3              moveOffsetCpy;
    s32                  var_a0;
    s32                  i;
    bool                 cond;
    q19_12               groundHeight;
    s32                  count;
    s_SubCharacter**     curChara;
    s_IpdCollisionData** curCollData;
    s_SubCharacter*      chara;

    cond = false;

    if (cylinder->collisionState == CharaCollisionState_5)
    {
        Collision_DefaultResultSet(collResult, moveOffset->vx, moveOffset->vy, moveOffset->vz, cylinder->position.vy);
        return false;
    }

    Collision_TargetCharaCollidingSlowDown(moveOffset, cylinder, charas, charaCount);

    moveOffsetCpy = *moveOffset;
    collResult->ceilingHeight = Collision_CeilingHeightGet(&moveOffsetCpy, cylinder, cylinder->radius, cylinder->top);

    Collision_CollStateInit(&collState, &moveOffsetCpy, cylinder, arg3);

    moveOffset1 = moveOffsetCpy;

    collResult->offset.vz = Q12(0.0f);
    collResult->offset.vx = Q12(0.0f);
    collResult->offset.vy = moveOffsetCpy.vy;

    while (true)
    {
        if (collState.field_0_0)
        {
            collState.isCharaMoving = collState.charaState.distance != Q12(0.0f);
            collState.field_0_9     = false;
            collState.field_0_10    = false;
        }
        else
        {
            collState.isCharaMoving = collState.charaState.distance != Q12(0.0f);
            collState.field_0_9     = true;
            collState.field_0_10    = true;
        }

        // Run through collision data.
        for (curCollData = collDataPtrs; curCollData < &collDataPtrs[collDataIdx]; curCollData++)
        {
            Collision_CharaCollisionHandling(&collState, *curCollData);
        }

        if (collState.field_44.field_0.field_0 && collState.field_44.field_0.field_2.vx == collState.field_44.field_0.field_2.vy)
        {
            cond |= true;
        }

        func_8006CF18(&collState, arg6, arg7);

        // Run through characters.
        for (curChara = charas; curChara < &charas[charaCount]; curChara++)
        {
            chara  = *curChara;
            // TODO: Wrong. `chara->collision.cylinder.radius` is `q9_12` while `collState.charaState.radius`
            // is `q7_8`. Could be division?
            var_a0 = FP_FROM(chara->collision.cylinder.radius, Q4_SHIFT) + collState.charaState.radius;

            if (chara->collision.state < (u32)collState.charaState.collisionState)
            {
                var_a0 -= 15;
            }

            collState.charaPositionFrom.field_0 = Q12_TO_Q8(chara->position.vx + chara->collision.shapeOffsets.cylinder.vx);
            collState.charaPositionTo.field_0   = Q12_TO_Q8(chara->position.vz + chara->collision.shapeOffsets.cylinder.vz);

            collState.field_A0.s_1.field_0        = Q12_TO_Q8(chara->collision.box.top    + chara->position.vy);
            collState.field_A0.s_1.field_2        = Q12_TO_Q8(chara->collision.box.bottom + chara->position.vy);
            collState.field_A0.s_1.field_4        = var_a0;
            collState.field_A0.s_1.collisionState = chara->collision.state;
            collState.field_A0.s_1.field_8        = &chara->collision.field_E0;

            if (collState.field_0_0 == false)
            {
                chara->collision.field_E0 = 0;
            }

            func_8006CC9C(&collState);
            func_8006CF18(&collState, chara->collision.field_E4, chara->collision.field_E1_4);
        }

        func_8006D01C(&sp120, &moveOffset1, Collision_OffsetAlphaGet(&collState), &collState);

        collResult->offset.vx += sp120.vx;
        collResult->offset.vz += sp120.vz;

        if (collState.field_0_0)
        {
            break;
        }

        if (collState.field_44.field_0.field_0 || collState.field_44.field_30.field_0)
        {
            count = 8;
            if (collState.field_44.field_8.field_0 < 9)
            {
                count = collState.field_44.field_8.field_0;
            }

            for (i = 0; i < count; i++)
            {
                *collState.field_44.field_10[i] += 1;
            }
        }
        else if (collState.field_34)
        {
            *collState.field_40 += 1;
        }
        else
        {
            break;
        }

        collState.field_0_0 = true;
        func_8006D774(&collState, &sp120, &moveOffset1);
    }

    if (collState.heightDisabled == true)
    {
        groundHeight                   = Q12(8.0f);
        collResult->surface.groundType = GroundType_Default;
    }
    else
    {
        collResult->surface.groundType = collState.groundType;
        groundHeight                   = Q8_TO_Q12(Ipd_GroundHeightGet(collState.charaState.positionFromX + Q12_TO_Q8(sp120.vx),
                                                                       collState.charaState.positionFromZ + Q12_TO_Q8(sp120.vz), &collState));
    }

    collResult->surface.groundHeight = groundHeight;
    collResult->surface.tiltAngleX   = collState.tiltAngleX;
    collResult->surface.tiltAngleZ   = collState.tiltAngleZ;

    if (cond)
    {
        return NO_VALUE;
    }

    return collState.field_0_0 != false;
}

void Collision_TargetCharaCollidingSlowDown(VECTOR3* offset, const s_CollisionCylinder* cylinder, s_SubCharacter** charas, s32 charaCount) // 0x8006A940
{
    q19_12          headingAngle;
    q19_12          cylinderOffsetZ;
    q19_12          cylinderOffsetX;
    q19_12          var_a0;
    s32             i;
    q19_12          offsetAlpha;
    q19_12          var_v0;
    s32             dist;
    q19_12          curCharaTop;
    q19_12          curCharaBottom;
    q19_12          otherCharaBottom;
    q19_12          otherCharaTop;
    s_SubCharacter* curChara;

    offsetAlpha  = Q12(1.0f);
    headingAngle = ratan2(offset->vx, offset->vz);

    // Run through characters to collide.
    for (i = 0; i < charaCount; i++)
    {
        curChara = charas[i];

        // Check if current character is collidable.
        if (curChara->collision.state == CharaCollisionState_Ignore ||
            curChara->collision.state == CharaCollisionState_Player ||
            curChara->collision.state >= cylinder->collisionState)
        {
            continue;
        }

        // Check if cylinders collide on vertical axis using box top and bottom.
        curCharaTop      = curChara->collision.box.top    + curChara->position.vy;
        curCharaBottom   = curChara->collision.box.bottom + curChara->position.vy;
        otherCharaTop    = cylinder->top                  + cylinder->position.vy;
        otherCharaBottom = cylinder->bottom               + cylinder->position.vy;
        if (curCharaTop    > otherCharaBottom ||
            curCharaBottom < otherCharaTop)
        {
            continue;
        }

        cylinderOffsetX = (curChara->position.vx + curChara->collision.shapeOffsets.cylinder.vx) - cylinder->position.vx;
        cylinderOffsetZ = (curChara->position.vz + curChara->collision.shapeOffsets.cylinder.vz) - cylinder->position.vz;
        
        // Check if cylinders collide on XZ plane.
        dist = Vc_VectorMagnitudeCalc(cylinderOffsetX, Q12(0.0f), cylinderOffsetZ);
        if (((curChara->collision.cylinder.radius + cylinder->radius) + INTERSECTION_BUFFER) < dist)
        {
            continue;
        }

        // TODO: Check what this is doing. Computes a slowdown alpha based on the angle at which the cylinders collided?
        var_a0 = Q12_MULT(Math_Cos(ratan2(cylinderOffsetX, cylinderOffsetZ) - headingAngle), Q12(1.5f));
        var_v0 = MAX(var_a0, Q12(0.0f));
        var_a0 = var_v0;
        if (curChara->model.charaId == Chara_HangedScratcher)
        {
            var_a0 = MIN(var_a0, Q12(0.6f));
        }
        else
        {
            var_a0 = MIN(var_a0, Q12(0.4f));
        }

        offsetAlpha -= var_a0;
    }

    // Adjust displacement offset.
    offsetAlpha = MAX(offsetAlpha, Q12(0.4f));
    offset->vx  = Q12_MULT(offsetAlpha, offset->vx);
    offset->vz  = Q12_MULT(offsetAlpha, offset->vz);
}

void Collision_CollStateInit(s_CollisionState* collState, VECTOR3* moveOffset, const s_CollisionCylinder* cylinder, bool arg3) // 0x8006AB50
{
    collState->field_0_0          = false;
    collState->flags              = g_ActiveCollisionTriggers.flags;
    collState->charaState.field_4 = arg3;

    Collision_MoveDirectionCalc(&collState->charaState, moveOffset, cylinder);

    collState->field_7C = Q8(30.0f);
    collState->field_34 = 0;
    
    collState->field_44.field_0.field_0  = 0;
    collState->field_44.field_6          = 0;
    collState->field_44.field_8.field_0  = 0;
    collState->field_44.field_36         = 0;
    collState->field_44.field_30.field_0 = 0;
    
    collState->tiltAngleZ     = Q12_ANGLE(0.0f);
    collState->tiltAngleX     = Q12_ANGLE(0.0f);
    collState->heightDisabled = true;
    collState->groundType     = GroundType_Default;
}

void Collision_MoveDirectionCalc(s_CollisionCharaState* charaState, const VECTOR3* moveOffset, const s_CollisionCylinder* cylinder) // 0x8006ABC0
{
    q3_12 headingAngle;

    charaState->offset.vx = Q12_TO_Q8(moveOffset->vx);
    charaState->offset.vy = Q12_TO_Q8(moveOffset->vy);
    charaState->offset.vz = Q12_TO_Q8(moveOffset->vz);

    charaState->distance = Math_Vector2MagCalc(charaState->offset.vx, charaState->offset.vz);
    if (charaState->distance != Q12(0.0f))
    {
        // @unused
        charaState->direction.vx = Q12(charaState->offset.vx) / charaState->distance;
        charaState->direction.vz = Q12(charaState->offset.vz) / charaState->distance;

        headingAngle             = ratan2(charaState->offset.vz, charaState->offset.vx);
        charaState->direction.vx = Math_Cos(headingAngle);
        charaState->direction.vz = Math_Sin(headingAngle);
    }
    else
    {
        charaState->direction.vx = Q12(1.0f);
        charaState->direction.vz = Q12(0.0f);
    }

    charaState->radius         = Q12_TO_Q8(cylinder->radius);
    charaState->positionFromX  = Q12_TO_Q8(cylinder->position.vx);
    charaState->positionFromZ  = Q12_TO_Q8(cylinder->position.vz);
    charaState->positionToX    = charaState->positionFromX + charaState->offset.vx;
    charaState->positionToZ    = charaState->positionFromZ + charaState->offset.vz;
    charaState->topPos         = Q12_TO_Q8(cylinder->top    + cylinder->position.vy);
    charaState->bottomPos      = Q12_TO_Q8(cylinder->bottom + cylinder->position.vy);
    charaState->collisionState = cylinder->collisionState;
}

void Collision_CharaCollisionHandling(s_CollisionState* collState, s_IpdCollisionData* collData) // 0x8006AD44
{
    s32                    endIdx;
    s32                    startIdx;
    s32                    i;
    s32                    j;
    s_IpdCollSubcellRange* curCellRange;
    
    // Checks if IPD contains necessary collision information and if the game is able to get the
    // sub-cell where the character is currently placed on.
    if ((collData->surfaceCount == 0 && collData->subcellInfoCount == 0 && collData->field_8_24 == 0) ||
        !Collision_SubcellInit(collState, collData))
    {
        return;
    }
    
    if (collState->field_0_0 == false)
    {
        Collision_SubcellChecksReset(collData);
    }

    startIdx = collState->field_A0.s_0.closestXSubcellIdx;
    endIdx   = (collState->field_A0.s_0.closestXSubcellIdx + collState->field_A0.s_0.closeFarXSubcellIdxDiff) - 1;

    for (i = collState->field_A0.s_0.closestZSubcellIdx; i < (collState->field_A0.s_0.closestZSubcellIdx + collState->field_A0.s_0.closeFarZSubcellIdxDiff); i++)
    {
        curCellRange = &collData->subcellRanges[(i * collData->subcellXCount) + startIdx];

        for (j = startIdx; j <= endIdx; j++, curCellRange++)
        {
            func_8006B1C8(collState, collData, curCellRange);
        }
    }

    if (collState->field_0_0 == false)
    {
        Collision_SubcellChecksCountUpdate(collData);
    }

    // Important for handling height and movement in slopes.
    if (collState->field_0_10)
    {
        func_8006C838(collState, collData);
        if (collState->field_A0.s_0.subcellRange != NULL)
        {
            func_8006CA18(collState, collData, collState->field_A0.s_0.subcellRange);
        }
    }
}

bool Collision_SubcellInit(s_CollisionState* collState, const s_IpdCollisionData* collData) // 0x8006AEAC
{
    s_CollisionState_A8* curUnk;

    if (!Collision_SubcellIdxGet(collState, collData))
    {
        return false;
    }

    collState->charaPositionFrom.offset.vx = collState->charaState.positionFromX - collData->positionX;
    collState->charaPositionFrom.offset.vz = collState->charaState.positionFromZ - collData->positionZ;
    collState->charaPositionTo.offset.vx   = collState->charaState.positionToX   - collData->positionX;
    collState->charaPositionTo.offset.vz   = collState->charaState.positionToZ   - collData->positionZ;
    
    if ((collState->charaPositionFrom.offset.vx / collData->subcellSize) < 0 || (collState->charaPositionFrom.offset.vx / collData->subcellSize) >= collData->subcellXCount ||
        ((collState->charaPositionFrom.offset.vz / collData->subcellSize) < 0) || (collState->charaPositionFrom.offset.vz / collData->subcellSize) >= collData->subcellZCount)
    {
        collState->field_A0.s_0.subcellRange = NULL;
    }
    else
    {
        collState->field_A0.s_0.subcellRange = &collData->subcellRanges[((collState->charaPositionFrom.offset.vz / collData->subcellSize) * collData->subcellXCount) +
                                                                        (collState->charaPositionFrom.offset.vx / collData->subcellSize)];
        collState->subcellIdx                = NO_VALUE;

        for (curUnk = &collState->field_A0.s_0.field_8[0]; curUnk < &collState->field_A0.s_0.field_8[4]; curUnk++)
        {
            curUnk->subChunkTransDir   = SubChunkTransitionDirection_None;
            curUnk->surfaceIdx         = NO_VALUE;
            curUnk->radiusCollDiffDist = INT_MAX;
        }
    }
    return true;
}

bool Collision_SubcellIdxGet(s_CollisionState* collState, const s_IpdCollisionData* collData) // 0x8006B004
{
    q23_8 charaCollDiffZClosest;
    q23_8 charaCollDiffXClosest;
    q23_8 collCellXSize;
    q23_8 collCellZSize;
    q23_8 collCellXLimit;
    q23_8 collCellZLimit;
    q23_8 charaCollDiffZFarest;
    q23_8 charaCollDiffXFarest;
    
    collCellXSize  = collData->subcellSize * collData->subcellXCount;
    collCellXLimit = collCellXSize - 1;
    collCellZSize  = collData->subcellSize * collData->subcellZCount;
    collCellZLimit = collCellZSize - 1;

    // Getting X plane differences.
    charaCollDiffXClosest = collState->charaState.positionFromX - collData->positionX;
    charaCollDiffXFarest  = collState->charaState.positionToX   - collData->positionX;
    if (charaCollDiffXFarest < charaCollDiffXClosest)
    {
        charaCollDiffXFarest  ^= charaCollDiffXClosest;
        charaCollDiffXClosest ^= charaCollDiffXFarest;
        charaCollDiffXFarest  ^= charaCollDiffXClosest;
    }
    charaCollDiffXClosest -= collState->charaState.radius;
    charaCollDiffXFarest  += collState->charaState.radius;


    // Getting Z plane differences.
    charaCollDiffZClosest = collState->charaState.positionFromZ - collData->positionZ;
    charaCollDiffZFarest  = collState->charaState.positionToZ   - collData->positionZ;
    if (charaCollDiffZFarest < charaCollDiffZClosest)
    {
        charaCollDiffZFarest  ^= charaCollDiffZClosest;
        charaCollDiffZClosest ^= charaCollDiffZFarest;
        charaCollDiffZFarest  ^= charaCollDiffZClosest;
    }
    charaCollDiffZClosest -= collState->charaState.radius;
    charaCollDiffZFarest  += collState->charaState.radius;

    if (collCellXSize < charaCollDiffXClosest || collCellZSize < charaCollDiffZClosest || charaCollDiffXFarest < 0 || charaCollDiffZFarest < 0)
    {
        return false;
    }

    charaCollDiffXClosest = limitRange(charaCollDiffXClosest, 0, collCellXLimit);
    charaCollDiffZClosest = limitRange(charaCollDiffZClosest, 0, collCellZLimit);
    charaCollDiffXFarest  = limitRange(charaCollDiffXFarest, 0, collCellXLimit);
    charaCollDiffZFarest  = limitRange(charaCollDiffZFarest, 0, collCellZLimit);

    collState->field_A0.s_0.closestXSubcellIdx      = charaCollDiffXClosest / collData->subcellSize;
    collState->field_A0.s_0.closestZSubcellIdx      = charaCollDiffZClosest / collData->subcellSize;
    collState->field_A0.s_0.closeFarXSubcellIdxDiff = ((charaCollDiffXFarest / collData->subcellSize) - collState->field_A0.s_0.closestXSubcellIdx) + 1;
    collState->field_A0.s_0.closeFarZSubcellIdxDiff = ((charaCollDiffZFarest / collData->subcellSize) - collState->field_A0.s_0.closestZSubcellIdx) + 1;

    return true;
}

void func_8006B1C8(s_CollisionState* collState, s_IpdCollisionData* collData, s_IpdCollSubcellRange* subcellRanges) // 0x8006B1C8
{
    s32 subcellInfoCount;
    s32 i;
    u8  idx;

    for (i = subcellRanges[0].field_0; i < subcellRanges[1].field_0; i++)
    {
        idx = collData->ptr_28[i];
        
        // Checks if cell element haven't been analysed.
        if (collData->subcellsChecksCount >= collData->subcellCheckIdx[idx])
        {
            collData->subcellCheckIdx[idx] = collData->subcellsChecksCount + 1;
            subcellInfoCount               = collData->subcellInfoCount;
            
            // Checks if sub cell index is inside the defined sub cell information.
            if (idx < subcellInfoCount)
            {
                if (func_8006B318(collState, collData, idx))
                {
                    if (collState->field_0_10)
                    {
                        func_8006B6E8(collState, subcellRanges);
                    }

                    if (collState->isCharaMoving || collState->field_0_9)
                    {
                        if (collState->curCellCollision.field_C.cellSurfaces.surfaceIdx1 == UCHAR_MAX)
                        {
                            func_8006B9C8(collState);
                        }

                        if (collState->curCellCollision.field_C.cellSurfaces.surfaceIdx0 == UCHAR_MAX)
                        {
                            func_8006B8F8(&collState->curCellCollision);
                            func_8006B9C8(collState);
                        }
                    }
                }
            }
            else if (func_8006C3D4(collState, collData, idx))
            {
                func_8006C45C(collState);
            }
        }
    }
}

bool func_8006B318(s_CollisionState* collState, const s_IpdCollisionData* collData, s32 subcellIdx) // 0x8006B318
{
    q23_8             charaVertDiffZ;
    q23_8             charaVertDiffX;
    s32               temp_v0;
    s_IpdCollSurface* curCellSurface;
    s_IpdCollSubcell* subcell;

    subcell = &collData->subcells[subcellIdx];
    
    /** @note Alternative collision enabling?
     * As noted briefly in `e_CollisionTriggerFlags` the game contains two flags (three, but one is unused)
     * which specifically enable certain collisions under specific game events, see for example the school
     * boss valve puzzle which relays in this flag system in order to enable and disable the collision that
     * blocks the player from progressing until the puzzle is solved.
     *
     * Claude (on Kush/AI port repo) indicates this is used to enable certain collision cells so likely this is
     * where that system relays on.
     */
    if (!((collState->flags >> ((subcell->field_0_14 * 4) | subcell->field_2_14)) & (1 << 0)))
    {
        return false;
    }

    collState->curCellCollision.ipdCollisionData = collData;
    collState->curCellCollision.subcellIdx       = subcellIdx;

    collState->curCellCollision.field_6.vx = subcell->field_0_0;
    collState->curCellCollision.field_6.vy = subcell->field_2_0;
    collState->curCellCollision.field_6.vz = subcell->field_4;

    collState->curCellCollision.collisionVertex0 = collData->collisionVertices[subcell->collisionVertexIdx1];
    collState->curCellCollision.collisionVertex1 = collData->collisionVertices[subcell->collisionVertexIdx0];

    collState->curCellCollision.field_C.cellSurfaces.surfaceIdx0 = subcell->surfaceIdx0;

    if (collState->curCellCollision.field_C.cellSurfaces.surfaceIdx0 != UCHAR_MAX)
    {
        curCellSurface                              = &collData->surfaces[collState->curCellCollision.field_C.cellSurfaces.surfaceIdx0];
        collState->curCellCollision.field_E           = curCellSurface->field_6_8;
        collState->curCellCollision.disableSurface0Height = curCellSurface->disableHeight;

        if (collState->charaState.field_4 &&
            (curCellSurface->disableHeight == true || curCellSurface->groundType == GroundType_None))
        {
            collState->curCellCollision.collisionVertex0.vy -= Q8(-DEFAULT_CEILING_HEIGHT);
            collState->curCellCollision.collisionVertex1.vy -= Q8(-DEFAULT_CEILING_HEIGHT);
        }
    }

    collState->curCellCollision.field_C.cellSurfaces.surfaceIdx1 = subcell->surfaceIdx1;

    if (collState->curCellCollision.field_C.cellSurfaces.surfaceIdx1 != UCHAR_MAX)
    {
        curCellSurface                                    = &collData->surfaces[collState->curCellCollision.field_C.cellSurfaces.surfaceIdx1];
        collState->curCellCollision.field_F               = curCellSurface->field_6_8;
        collState->curCellCollision.disableSurface1Height = curCellSurface->disableHeight;

        if (collState->charaState.field_4 &&
            (curCellSurface->disableHeight == true || curCellSurface->groundType == GroundType_None))
        {
            collState->curCellCollision.collisionVertex0.vy = Q8(DEFAULT_CEILING_HEIGHT);
            collState->curCellCollision.collisionVertex1.vy = Q8(DEFAULT_CEILING_HEIGHT);
        }
    }

    /* Will - 1: Important for dealing with heights or cells transition, in any case of changing any value given to `field_8`
       then harry start freaking out when going through subcells that have different heights or subcells that have two
       with one having a different alture as he may suddenly appear way above of them, this is more something done to handle
       the transition between cells because onces the player is in the cell with different height to the previous one they
       can walk normally.
    */
    temp_v0 = PACKED_XZ16(subcell->field_0_0, subcell->field_2_0);
    gte_ldR11R12(temp_v0);
    gte_ldR13R21(temp_v0);
    
    temp_v0 = PACKED_XZ16(collState->charaState.offset.vx, collState->charaState.offset.vz);
    gte_ldvxy0(temp_v0);
    gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&collState->curCellCollision.field_20.charaMoveOffset);
    /* Will - 1: ^ These values are normally set to 0 when standing still and are only modified when moving.
    
       Will - 2: I think this a distance, the value when set isn't too big and also I think `charaState.offset` is the
       character movement offset, like the equivalent of doing `charaPositionFrom.offset.vx - charaPositionTo.offset.vx`
       that may explain why it's 0 when standing still.
    */
    
    temp_v0 = PACKED_XZ16(collState->charaPositionFrom.offset.vx - collState->curCellCollision.collisionVertex0.vx,
                          collState->charaPositionFrom.offset.vz - collState->curCellCollision.collisionVertex0.vz);
    gte_ldvxy0(temp_v0);
    gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&collState->curCellCollision.field_20.charaVertDiff);

    charaVertDiffX                                            = collState->curCellCollision.field_20.charaVertDiff.vx;
    charaVertDiffZ                                            = collState->curCellCollision.field_20.charaVertDiff.vz;
    collState->curCellCollision.field_20.charaMoveVertDiff.vx = collState->curCellCollision.field_20.charaMoveOffset.vx + charaVertDiffX;
    collState->curCellCollision.field_20.charaMoveVertDiff.vz = collState->curCellCollision.field_20.charaMoveOffset.vz + charaVertDiffZ;

    if (charaVertDiffX < Q8(0.0f))
    {
        collState->curCellCollision.field_20.subChunkTransDir   = SubChunkTransitionDirection_X;
        collState->curCellCollision.field_20.radiusCollDiffDist = Math_Vector2MagCalc(charaVertDiffX, charaVertDiffZ);
        collState->curCellCollision.field_20.collDiffDist       = -charaVertDiffX;
    }
    else if (collState->curCellCollision.field_6.vz < charaVertDiffX)
    {
        collState->curCellCollision.field_20.subChunkTransDir   = SubChunkTransitionDirection_X;
        collState->curCellCollision.field_20.radiusCollDiffDist = Math_Vector2MagCalc(charaVertDiffX - collState->curCellCollision.field_6.vz, charaVertDiffZ);
        collState->curCellCollision.field_20.collDiffDist       = charaVertDiffX - collState->curCellCollision.field_6.vz;
    }
    else
    {
        if (charaVertDiffZ < Q8(0.0f))
        {
            collState->curCellCollision.field_20.radiusCollDiffDist = -charaVertDiffZ;
        }
        else
        {
            collState->curCellCollision.field_20.radiusCollDiffDist = charaVertDiffZ;
        }

        collState->curCellCollision.field_20.subChunkTransDir = SubChunkTransitionDirection_Z;
    }

    return true;
}

void func_8006B6E8(s_CollisionState* collState, s_IpdCollSubcellRange* subcellRanges) // 0x8006B6E8
{
    s32                  idx;
    s32                  surfaceIdx0;
    s32                  surfaceIdx1;
    bool                 disableSurface0Height;
    bool                 disableSurface1Height;
    s_CollisionState_A8* temp_s0;

    surfaceIdx0           = collState->curCellCollision.field_C.cellSurfaces.surfaceIdx0;
    surfaceIdx1           = collState->curCellCollision.field_C.cellSurfaces.surfaceIdx1;
    disableSurface0Height = collState->curCellCollision.disableSurface0Height;
    disableSurface1Height = collState->curCellCollision.disableSurface1Height;

    if (surfaceIdx0 == UCHAR_MAX)
    {
        if (surfaceIdx1 == UCHAR_MAX)
        {
            return;
        }

        idx = collState->curCellCollision.field_F;
    }
    else
    {
        idx = collState->curCellCollision.field_E;
    }

    /* Will - 1: checks if the value at whatever the struct is `temp_s0`
       pointing have defined values. It first checks if `s_CollisionState_A8::field_0`
       is 0 or not, need to mention that this value is defined by default as `-1`
       in `Collision_SubcellInit` so any other value means that the values where defined
       already, but if `s_CollisionState_A8::field_0` is not zero then it checks
       if the value stored in `collState->curCellCollision.field_20.field_8` is
       defined with any value other than 0, if not then it comes back here and continues
       if it is then it proceed to do some other checks that will return true.
       
       Likely if any of those cases fails the check then it will redefine whatever
       is supposed to be stored there.
    */
    temp_s0 = &collState->field_A0.s_0.field_8[idx];
    if (!func_8006B7E0(temp_s0, &collState->curCellCollision.field_20))
    {
        return;
    }

    temp_s0->subChunkTransDir   = collState->curCellCollision.field_20.subChunkTransDir;
    temp_s0->radiusCollDiffDist = collState->curCellCollision.field_20.radiusCollDiffDist;
    temp_s0->collDiffDist       = collState->curCellCollision.field_20.collDiffDist;

    if (collState->curCellCollision.field_20.charaVertDiff.vz >= Q8(0.0f))
    {
        if (disableSurface0Height == true)
        {
            temp_s0->surfaceIdx = NO_VALUE;
        }
        else
        {
            temp_s0->surfaceIdx = surfaceIdx0;
        }
    }
    else
    {
        if (disableSurface1Height == true)
        {
            temp_s0->surfaceIdx = NO_VALUE;
        }
        else
        {
            temp_s0->surfaceIdx = surfaceIdx1;
        }
    }
}

bool func_8006B7E0(s_CollisionState_A8* cur, s_CollisionState_CC_20* prev) // 0x8006B7E0
{
    if (cur->subChunkTransDir == SubChunkTransitionDirection_None)
    {
        return true;
    }

    switch (prev->subChunkTransDir)
    {
        case SubChunkTransitionDirection_None:
            return false;

        case SubChunkTransitionDirection_Z:
            switch (cur->subChunkTransDir)
            {
                case 1:
                    if (prev->radiusCollDiffDist < cur->radiusCollDiffDist)
                    {
                        return true;
                    }
                    break;

                case 2:
                    if (prev->radiusCollDiffDist < (cur->radiusCollDiffDist + 6))
                    {
                        return true;
                    }
                    break;
            }
            break;

        case SubChunkTransitionDirection_X:
            switch (cur->subChunkTransDir)
            {
                case 1:
                    if (prev->radiusCollDiffDist < (cur->radiusCollDiffDist - 6))
                    {
                        return true;
                    }
                    break;

                case 2:
                    if (prev->radiusCollDiffDist < (cur->radiusCollDiffDist - 6))
                    {
                        return true;
                    }

                    if (prev->radiusCollDiffDist < (cur->radiusCollDiffDist + 6) && prev->collDiffDist < cur->collDiffDist)
                    {
                        return true;
                    }
                    break;
            }
    }

    return false;
}

void func_8006B8F8(s_CollisionCell* collCell) // 0x8006B8F8
{
    s_CollisionState_CC_20* ptr;
    s32                     temp_a1;
    s32                     temp_a2;
    s32                     temp_a3;

    temp_a3                               = (u16)collCell->collisionVertex0.vx;
    temp_a1                               = (u16)collCell->collisionVertex1.vx;
    temp_a2                               = (u16)collCell->collisionVertex1.vz;
    collCell->collisionVertex1.vx         = temp_a3;
    temp_a3                               = (u16)collCell->collisionVertex0.vy;
    collCell->collisionVertex0.vy         = collCell->collisionVertex1.vy;
    collCell->collisionVertex0.vx         = temp_a1;
    collCell->field_6.vx                  = -collCell->field_6.vx;
    collCell->collisionVertex1.vy         = temp_a3;
    collCell->field_6.vy                  = -collCell->field_6.vy;
    temp_a3                               = (u16)collCell->collisionVertex0.vz;
    collCell->collisionVertex1.vz         = temp_a3;
    temp_a3                               = collCell->field_C.cellSurfaces.surfaceIdx0;
    collCell->field_20.charaMoveOffset.vx = -collCell->field_20.charaMoveOffset.vx;

    collCell->collisionVertex0.vz              = temp_a2;
    collCell->field_C.cellSurfaces.surfaceIdx0 = collCell->field_C.cellSurfaces.surfaceIdx1;

    ptr = &collCell->field_20;

    collCell->field_C.cellSurfaces.surfaceIdx1 = temp_a3;
    temp_a3                                    = collCell->field_E;
    collCell->field_20.charaMoveOffset.vz      = -collCell->field_20.charaMoveOffset.vz;
    collCell->field_E                          = collCell->field_F;
    collCell->field_F                          = temp_a3;

    ptr->charaVertDiff.vz     = -ptr->charaVertDiff.vz;
    ptr->charaVertDiff.vx     = (collCell->field_6.vz - ptr->charaVertDiff.vx);
    ptr->charaMoveVertDiff.vz = -ptr->charaMoveVertDiff.vz;
    ptr->charaMoveVertDiff.vx = (collCell->field_6.vz - ptr->charaMoveVertDiff.vx);
}

void func_8006B9C8(s_CollisionState* collState) // 0x8006B9C8
{
    q23_8 charaRadius;

    if (collState->curCellCollision.field_C.cellSurfaces.surfaceIdx1 == UCHAR_MAX &&
        collState->curCellCollision.field_20.charaVertDiff.vz < Q8(0.0f) &&
        (collState->charaState.bottomPos >= collState->curCellCollision.collisionVertex0.vy ||
         collState->charaState.bottomPos >= collState->curCellCollision.collisionVertex1.vy))
    {
        if (collState->field_0_9 && collState->curCellCollision.field_20.radiusCollDiffDist < collState->charaState.radius)
        {
            func_8006BB50(collState, 0);
            return;
        }

        charaRadius = collState->charaState.radius;
        if (collState->field_0_9 && collState->curCellCollision.field_20.radiusCollDiffDist < (charaRadius + 8))
        {
            func_8006BB50(collState, 1);
        }

        if (collState->isCharaMoving)
        {
            if (!collState->field_44.field_0.field_0 &&
                (-charaRadius < collState->curCellCollision.field_20.charaVertDiff.vz || -charaRadius < collState->curCellCollision.field_20.charaMoveVertDiff.vz) &&
                (-charaRadius < collState->curCellCollision.field_20.charaVertDiff.vx || -charaRadius < collState->curCellCollision.field_20.charaMoveVertDiff.vx) &&
                (collState->curCellCollision.field_20.charaVertDiff.vx < (charaRadius + collState->curCellCollision.field_6.vz) || collState->curCellCollision.field_20.charaMoveVertDiff.vx < (charaRadius + collState->curCellCollision.field_6.vz)))
            {
                func_8006BE40(collState);
            }
        }
    }
}

void func_8006BB50(s_CollisionState* collState, s32 arg1) // 0x8006BB50
{
    q23_8 charaCollDistX;
    q23_8 charaCollDistZ;
    q7_8  temp2;

    if (func_8006BC34(collState) < Q8(0.0f))
    {
        return;
    }

    if (collState->curCellCollision.field_20.charaVertDiff.vx < Q8(0.0f))
    {
        charaCollDistX = collState->charaPositionFrom.offset.vx - collState->curCellCollision.collisionVertex0.vx;
        charaCollDistZ = collState->charaPositionFrom.offset.vz - collState->curCellCollision.collisionVertex0.vz;
    }
    else if (collState->curCellCollision.field_6.vz < collState->curCellCollision.field_20.charaVertDiff.vx)
    {
        charaCollDistX = collState->charaPositionFrom.offset.vx - collState->curCellCollision.collisionVertex1.vx;
        charaCollDistZ = collState->charaPositionFrom.offset.vz - collState->curCellCollision.collisionVertex1.vz;
    }
    else
    {
        charaCollDistX = collState->curCellCollision.field_6.vy;
        charaCollDistZ = -collState->curCellCollision.field_6.vx;
    }

    temp2 = collState->charaState.radius - collState->curCellCollision.field_20.radiusCollDiffDist;
    func_8006BCC4(&collState->field_44, &collState->curCellCollision.ipdCollisionData->subcellCheckIdx[collState->curCellCollision.subcellIdx], arg1, charaCollDistX, charaCollDistZ, temp2);
}

q23_8 func_8006BC34(s_CollisionState* collState)
{
    q7_8 temp_a2;
    q7_8 temp_a3;
    q7_8 temp_v0;
    q7_8 temp_v1;
    q7_8 temp_a1;
    q7_8 var_v0;

    temp_v1 = collState->curCellCollision.field_20.charaVertDiff.vx;
    if (temp_v1 < Q8(0.0f))
    {
        var_v0 = collState->curCellCollision.collisionVertex0.vy;
    }
    else
    {
        temp_a2 = collState->curCellCollision.field_6.vz;
        if (temp_a2 < temp_v1)
        {
            var_v0 = collState->curCellCollision.collisionVertex1.vy;
        }
        else
        {
            temp_a3 = collState->curCellCollision.collisionVertex0.vy;
            temp_v0 = collState->curCellCollision.collisionVertex1.vy;
            temp_a1 = collState->curCellCollision.collisionVertex0.vy;

            if (temp_a3 == temp_v0)
            {
                var_v0 = temp_a1;
            }
            else
            {
                var_v0 = temp_a1 + ((s32)((temp_v0 - temp_a3) * temp_v1) / temp_a2);
            }
        }
    }

    return collState->charaState.bottomPos - var_v0;
}

void func_8006BCC4(s_CollisionState_44* arg0, s8* arg1, u32 arg2, q7_8 distX, q7_8 distZ, q7_8 arg5) // 0x8006BCC4
{
    q7_8 rotX;
    q7_8 rotY;

    // TODO: This are not Q12 values nor angles. However the equivalent of both `Q12_ANGLE` in Q8 is weird.
    rotX = Q12_FRACT(ratan2(distZ, distX) - Q12_ANGLE(89.0f));
    rotY = Q12_FRACT(rotX + Q12_ANGLE(178.0f));

    switch (arg2)
    {
        case 0:
            *arg1 += 1;

            func_8006BDDC(&arg0->field_0, rotX, rotY);

            if (arg0->field_6 < arg5)
            {
                arg0->field_6 = arg5;
            }
            break;

        case 1:
            func_8006BDDC(&arg0->field_8, rotX, rotY);

            if (arg0->field_8.field_0 < 9)
            {
                arg0->field_10[arg0->field_8.field_0 - 1] = arg1;
            }
            break;
        
        case 2:
            *arg1 += 1;

            func_8006BDDC(&arg0->field_30, rotX, rotY);

            if (arg0->field_36 < arg5)
            {
                arg0->field_36 = arg5;
            }
            break;
    }
}

void func_8006BDDC(s_CollisionState_44_0* arg0, q7_8 rotX, q7_8 rotY) // 0x8006BDDC
{
    if (arg0->field_0 == 0)
    {
        arg0->field_0 = 1;
        arg0->field_2.vx = rotX;
        arg0->field_2.vy = rotY;
        return;
    }

    arg0->field_0++;
    Vw_ClampAngleRange(&arg0->field_2.vx, &arg0->field_2.vy, rotX, rotY);
}

void func_8006BE40(s_CollisionState* collState) // 0x8006BE40
{
    q23_8 negRadius;
    q23_8 var_a2;
    s32   var_a1;
    u32   var_v1;
    s32   temp;

    var_a1    = 0;
    negRadius = -(collState->charaState.radius);
    var_a2    = Q8(0.0F);

    if (collState->curCellCollision.field_20.charaVertDiff.vz >= negRadius)
    {
        if (collState->curCellCollision.field_20.charaVertDiff.vx >= Q8(0.0f))
        {
            if (collState->curCellCollision.field_6.vz >= collState->curCellCollision.field_20.charaVertDiff.vx)
            {
                var_a2 = collState->curCellCollision.field_20.charaVertDiff.vx;
                var_v1 = 2;
            }
            else
            {
                var_v1 = 1;
            }
        }
        else
        {
            var_v1 = 0;
        }
    }
    else
    {
        if (collState->curCellCollision.field_20.charaMoveOffset.vz == 0)
        {
            if (collState->curCellCollision.field_20.charaVertDiff.vx > 0 &&
                collState->curCellCollision.field_20.charaVertDiff.vx < collState->curCellCollision.field_6.vz)
            {
                var_a1 = 0;
                var_a2 = collState->curCellCollision.field_20.charaVertDiff.vx;
            }
        }
        else
        {
            var_a1 = FP_TO(negRadius - collState->curCellCollision.field_20.charaVertDiff.vz, Q12_SHIFT) /
                     collState->curCellCollision.field_20.charaMoveOffset.vz;
            temp   = collState->curCellCollision.field_20.charaMoveOffset.vx * var_a1;
            temp   = FP_FROM(temp, Q12_SHIFT);
            var_a2 = temp + collState->curCellCollision.field_20.charaVertDiff.vx;
        }

        if (var_a2 < Q8(0.0F))
        {
            var_v1 = 0;
        }
        else if (collState->curCellCollision.field_6.vz < var_a2)
        {
            var_v1 = 1;
        }
        else
        {
            var_v1 = 2;
        }
    }

    switch (var_v1)
    {
        case 0:
            func_8006BF88(collState, &collState->curCellCollision.collisionVertex0);
            break;

        case 1:
            func_8006BF88(collState, &collState->curCellCollision.collisionVertex1);
            break;

        case 2:
            func_8006C0C8(collState, var_a1, var_a2);
            break;
    }
}

void func_8006BF88(s_CollisionState* collState, SVECTOR3* collVert) // 0x8006BF88
{
    q3_12 temp_v0;
    s32   temp2;
    s32   temp3;

    temp_v0 = func_8006C248(*(s32*)&collState->charaState.direction, collState->charaState.distance,
                            collVert->vx - collState->charaPositionFrom.offset.vx,
                            collVert->vz - collState->charaPositionFrom.offset.vz,
                            collState->charaState.radius);
    if (temp_v0 != NO_VALUE && func_8006C1B8(2, temp_v0, collState) && collState->charaState.bottomPos > collVert->vy)
    {
        collState->field_38 = temp_v0;
        collState->field_34 = 2;
        temp2               = collState->charaPositionFrom.offset.vx + Q12_MULT(collState->charaState.offset.vx, temp_v0);
        collState->field_3A = Q12_TO_Q4(collState->charaState.distance * temp_v0);
        collState->field_40 = &collState->curCellCollision.ipdCollisionData->subcellCheckIdx[collState->curCellCollision.subcellIdx];

        collState->field_3C = temp2 - collVert->vx;
        temp3               = collState->charaPositionFrom.offset.vz + Q12_MULT(collState->charaState.offset.vz, temp_v0);
        collState->field_3E = temp3 - collVert->vz;
    }
}

void func_8006C0C8(s_CollisionState* collState, s16 arg1, q7_8 arg2) // 0x8006C0C8
{
    q23_8 temp;

    if (!func_8006C1B8(1, arg1, collState) || collState->curCellCollision.field_20.charaMoveOffset.vz < 0)
    {
        return;
    }

    temp = ((collState->curCellCollision.collisionVertex1.vy - collState->curCellCollision.collisionVertex0.vy) * arg2) / collState->curCellCollision.field_6.vz;
    if (temp + collState->curCellCollision.collisionVertex0.vy < collState->charaState.bottomPos)
    {
        collState->field_40 = &collState->curCellCollision.ipdCollisionData->subcellCheckIdx[collState->curCellCollision.subcellIdx];
        collState->field_34 = 1;
        collState->field_38 = arg1;
        collState->field_3A = Q12_TO_Q4(collState->charaState.distance * arg1);
        collState->field_3C = collState->curCellCollision.field_6.vy;
        collState->field_3E = -collState->curCellCollision.field_6.vx;
    }
}

bool func_8006C1B8(u32 arg0, q3_12 arg1, s_CollisionState* collState) // 0x8006C1B8
{
    q27_4 var;

    var = Q12_TO_Q4(collState->charaState.distance * arg1);
    switch (arg0)
    {
        default:
        case 0:
            return false;

        case 2:
            if (collState->field_34 != 1)
            {
                if (collState->field_34 == 0)
                {
                   return true;
                }

                break;
            }

            var += Q4(6.0f);
            break;

        case 1:
            if (collState->field_34 != arg0)
            {
                if (collState->field_34 != 0)
                {
                    if (collState->field_34 == 2)
                    {
                        var -= Q4(6.0f);
                    }

                    break;
                }

                return true;
            }
            break;
    }

    return var < collState->field_3A;
}

q3_12 func_8006C248(s32 packedDir, q3_12 arg1, q3_12 deltaX, q7_8 deltaZ, q7_8 arg4) // 0x8006C248
{
    DVECTOR sp10; // Q19.12
    s16     temp_v0;
    s16     dist;
    q3_12   alpha;

    gte_ldR11R12(packedDir);
    gte_ldR13R21(packedDir);
    gte_ldvxy0(PACKED_XZ16(deltaX, deltaZ));
    gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&sp10.vx);

    if (sp10.vx < Q12(0.0f))
    {
        dist = Math_Vector2MagCalc(sp10.vx, sp10.vy);
    }
    else if (arg1 < sp10.vx)
    {
        temp_v0 = sp10.vx - arg1;
        dist  = Math_Vector2MagCalc(temp_v0, sp10.vy);
    }
    else
    {
        dist = ABS(sp10.vy);
    }

    if (arg1 == Q12(0.0f))
    {
        alpha = NO_VALUE;
        if (dist >= arg4)
        {
            return alpha;
        }
        else
        {
            return Q12(0.0f);
        }
    }

    if (dist >= arg4)
    {
        return NO_VALUE;
    }

    alpha = FP_TO(sp10.vx - SquareRoot0(SQUARE(arg4) - SQUARE(sp10.vy)), Q12_SHIFT) / arg1; // TODO: Use `Math_Vector2MagCalc`.
    alpha = CLAMP(alpha, Q12(0.0f), Q12(1.0f));

    return alpha;
}

bool func_8006C3D4(s_CollisionState* collState, s_IpdCollisionData* collData, s32 subcellIdx) // 0x8006C3D4
{
    s_IpdCollisionData_18* temp_a1;

    collState->curCellCollision.ipdCollisionData = collData;
    collState->curCellCollision.subcellIdx       = subcellIdx;
    temp_a1 = &collData->ptr_18[subcellIdx - collData->subcellInfoCount];

    if (!((collState->flags >> temp_a1->field_0_8) & (1 << 0)))
    {
        return false;
    }

    collState->curCellCollision.heightDisabled  = temp_a1->disableHeight;
    collState->curCellCollision.field_6.vx      = temp_a1->offset.vx;
    collState->curCellCollision.field_6.vy      = temp_a1->offset.vy;
    collState->curCellCollision.field_6.vz      = temp_a1->offset.vz;
    collState->curCellCollision.field_C.field_0 = temp_a1->field_8;
    return true;
}

void func_8006C45C(s_CollisionState* collState) // 0x8006C45C
{
    q7_8  distMax;
    q7_8  dist;
    q3_12 var_s2;
    q23_8 bound;
    q23_8 distX;
    q23_8 distZ;
    q23_8 temp_v1;
    s32   temp;
    s32   temp2;

    distMax = collState->charaState.radius + collState->curCellCollision.field_C.field_0;
    bound   = distMax + 8;
    temp_v1 = collState->curCellCollision.field_6.vx - bound;

    if (collState->charaPositionFrom.offset.vx < temp_v1 &&
        collState->charaPositionTo.offset.vx   < temp_v1)
    {
        return;
    }

    if ((collState->curCellCollision.field_6.vx + bound) < collState->charaPositionFrom.offset.vx &&
        (collState->curCellCollision.field_6.vx + bound) < collState->charaPositionTo.offset.vx)
    {
        return;
    }

    if (collState->charaPositionFrom.offset.vz < (collState->curCellCollision.field_6.vz - bound) &&
        collState->charaPositionTo.offset.vz < (collState->curCellCollision.field_6.vz - bound))
    {
        return;
    }

    if ((collState->curCellCollision.field_6.vz + bound) < collState->charaPositionFrom.offset.vz &&
        (collState->curCellCollision.field_6.vz + bound) < collState->charaPositionTo.offset.vz)
    {
        return;
    }

    distX = collState->charaPositionFrom.offset.vx - collState->curCellCollision.field_6.vx;
    distZ = collState->charaPositionFrom.offset.vz - collState->curCellCollision.field_6.vz;
    dist  = Math_Vector2MagCalc(distX, distZ);

    if (dist < collState->curCellCollision.field_C.field_0 && collState->curCellCollision.heightDisabled != true &&
        (collState->subcellIdx == UCHAR_MAX || collState->curCellCollision.field_6.vy < collState->groundHeight))
    {
        collState->subcellIdx   = collState->curCellCollision.subcellIdx;
        collState->groundHeight = collState->curCellCollision.field_6.vy;
    }

    if (!collState->isCharaMoving && !collState->field_0_9 || dist < collState->curCellCollision.field_C.field_0)
    {
        return;
    }

    if (dist < distMax && collState->field_0_9)
    {
        func_8006C794(collState, 0, dist);
        return;
    }

    if (dist < (distMax + 8) && collState->field_0_9)
    {
        func_8006C794(collState, 1, dist);
    }

    if (!collState->isCharaMoving || collState->field_44.field_0.field_0)
    {
        return;
    }

    var_s2 = func_8006C248(*(s32*)&collState->charaState.direction, collState->charaState.distance,
                           collState->curCellCollision.field_6.vx - collState->charaPositionFrom.offset.vx,
                           collState->curCellCollision.field_6.vz - collState->charaPositionFrom.offset.vz,
                           distMax);

    if (var_s2 == -1)
    {
        return;
    }

    if (var_s2 < Q12(0.0f))
    {
        var_s2 = 0;
    }

    if (func_8006C1B8(1, var_s2, collState) && collState->charaState.bottomPos >= collState->curCellCollision.field_6.vy)
    {
        collState->field_38 = var_s2;
        collState->field_34 = 1;
        temp                = collState->charaPositionFrom.offset.vx + Q12_MULT(collState->charaState.offset.vx, var_s2);
        collState->field_3A = Q12_TO_Q4(collState->charaState.distance * var_s2);
        collState->field_40 = &collState->curCellCollision.ipdCollisionData->subcellCheckIdx[collState->curCellCollision.subcellIdx];
        collState->field_3C = temp - collState->curCellCollision.field_6.vx;
        temp2               = collState->charaPositionFrom.offset.vz + Q12_MULT(collState->charaState.offset.vz, var_s2);
        collState->field_3E = temp2 - collState->curCellCollision.field_6.vz;
    }
}

void func_8006C794(s_CollisionState* collState, s32 arg1, s32 dist) // 0x8006C794
{
    if (collState->charaState.bottomPos >= (collState->curCellCollision.field_6.vy + (dist - collState->curCellCollision.field_C.field_0)))
    {
        func_8006BCC4(&collState->field_44,
                      &collState->curCellCollision.ipdCollisionData->subcellCheckIdx[collState->curCellCollision.subcellIdx],
                      arg1,
                      collState->charaPositionFrom.offset.vx - collState->curCellCollision.field_6.vx,
                      collState->charaPositionFrom.offset.vz - collState->curCellCollision.field_6.vz,
                      (collState->charaState.radius + collState->curCellCollision.field_C.field_0) - dist);
    }
}

void func_8006C838(s_CollisionState* collState, s_IpdCollisionData* collData) // 0x8006C838
{
    q19_12                 var_a0;
    s_CollisionState_A8*   curUnk;
    s_IpdCollSurface*      curSurface;
    s_IpdCollisionData_18* temp_a0;

    if (collState->field_A0.s_0.subcellRange == NULL)
    {
        return;
    }

    if (collState->subcellIdx != UCHAR_MAX && collState->groundHeight < collState->field_7C)
    {
        temp_a0                     = &collData->ptr_18[collState->subcellIdx - collData->subcellInfoCount];
        collState->field_7C         = collState->groundHeight;
        collState->charaCellOffsetX = collState->charaPositionFrom.offset.vx + collData->positionX;
        collState->charaCellOffsetZ = collState->charaPositionFrom.offset.vz + collData->positionZ;
        collState->tiltAngleX       = Q12_ANGLE(0.0f);
        collState->tiltAngleZ       = Q12_ANGLE(0.0f);
        collState->heightDisabled   = temp_a0->disableHeight;
        collState->groundType       = temp_a0->groundType;
    }

    for (curUnk = &collState->field_A0.s_0.field_8[0]; curUnk < &collState->field_A0.s_0.field_8[4]; curUnk++)
    {
        if (curUnk->surfaceIdx != UCHAR_MAX)
        {
            curSurface = &collData->surfaces[curUnk->surfaceIdx];

            var_a0 = curSurface->field_2;

            if (curSurface->tiltAngleX != Q12_ANGLE(0.0f))
            {
                var_a0 += Q12_MULT(curSurface->tiltAngleX, collState->charaPositionFrom.offset.vx - curSurface->field_0);
            }

            if (curSurface->tiltAngleZ != Q12_ANGLE(0.0f))
            {
                var_a0 += Q12_MULT(curSurface->tiltAngleZ, collState->charaPositionFrom.offset.vz - curSurface->field_4);
            }

            if (var_a0 < collState->field_7C)
            {
                collState->field_7C         = var_a0;
                collState->charaCellOffsetX = collState->charaPositionFrom.offset.vx + collData->positionX;
                collState->charaCellOffsetZ = collState->charaPositionFrom.offset.vz + collData->positionZ;
                collState->tiltAngleX       = curSurface->tiltAngleX;
                collState->tiltAngleZ       = curSurface->tiltAngleZ;
                collState->heightDisabled   = curSurface->disableHeight;
                collState->groundType       = curSurface->groundType;
            }
        }
    }
}

void func_8006CA18(s_CollisionState* collState, s_IpdCollisionData* collData, s_IpdCollSubcellRange* subcellRanges) // 0x8006CA18
{
    s32                      startIdx;
    s32                      endIdx;
    q23_8                    var_a2;
    u8*                      curUnk;
    s_IpdCollSurface* surfaceAttribs;

    startIdx = subcellRanges[0].field_2;
    endIdx   = subcellRanges[1].field_2;

    if (startIdx == endIdx)
    {
        return;
    }

    for (curUnk = &collData->ptr_2C[startIdx]; curUnk < &collData->ptr_2C[endIdx]; curUnk++)
    {
        surfaceAttribs = &collData->surfaces[*curUnk];

        if (((collState->flags >> surfaceAttribs->field_6_11) & (1 << 0)) &&
            surfaceAttribs->disableHeight != true)
        {
            var_a2 = surfaceAttribs->field_2;

            if (surfaceAttribs->tiltAngleX != Q12_ANGLE(0.0f))
            {
                var_a2 += Q12_MULT(surfaceAttribs->tiltAngleX, collState->charaPositionFrom.offset.vx - surfaceAttribs->field_0);
            }

            if (surfaceAttribs->tiltAngleZ != Q12_ANGLE(0.0f))
            {
                var_a2 += Q12_MULT(surfaceAttribs->tiltAngleZ, collState->charaPositionFrom.offset.vz - surfaceAttribs->field_4);
            }

            if (var_a2 < collState->field_7C)
            {
                collState->field_7C         = var_a2;
                collState->charaCellOffsetX = collState->charaPositionFrom.offset.vx + collData->positionX;
                collState->charaCellOffsetZ = collState->charaPositionFrom.offset.vz + collData->positionZ;
                collState->tiltAngleX       = surfaceAttribs->tiltAngleX;
                collState->tiltAngleZ       = surfaceAttribs->tiltAngleZ;
                collState->heightDisabled   = surfaceAttribs->disableHeight;
                collState->groundType       = surfaceAttribs->groundType;
            }
        }
    }
}

q3_12 Collision_OffsetAlphaGet(s_CollisionState* collState) // 0x8006CB90
{
    q23_8 groundHeight;

    if (collState->field_7C == Q8(30.0f))
    {
        return Q12(1.0f);
    }

    groundHeight = Ipd_GroundHeightGet(collState->charaState.positionToX, collState->charaState.positionToZ, collState);
    if ((collState->charaState.bottomPos + collState->charaState.offset.vy) < groundHeight ||
        groundHeight == collState->field_7C)
    {
        return Q12(1.0f);
    }

    return Q12_DIV(collState->charaState.distance, Math_Vector2MagCalc(collState->charaState.distance,
                                                                       groundHeight - collState->charaState.bottomPos));
}

q23_8 Ipd_GroundHeightGet(q23_8 posX, q23_8 posZ, const s_CollisionState* collState) // 0x8006CC44
{
    if (collState->groundType != GroundType_None)
    {
        return Q12_MULT(collState->tiltAngleX, posX - collState->charaCellOffsetX) +
               Q12_MULT(collState->tiltAngleZ, posZ - collState->charaCellOffsetZ) +
               collState->field_7C;
    }

    return Q8(8.0f);
}

void func_8006CC9C(s_CollisionState* collState) // 0x8006CC9C
{
    q23_8  deltaX;
    q23_8  deltaZ;
    q19_12 temp_v0;
    q23_8  temp_s4;
    q23_8  temp;
    q23_8  temp2;
    s32    temp3;
    s32    temp4;
    s32    tarCharaBottom;

    if (collState->field_A0.s_1.collisionState < CharaCollisionState_2 ||
        *collState->field_A0.s_1.field_8 != 0)
    {
        return;
    }

    if (collState->charaPositionFrom.field_0 + (collState->field_A0.s_1.field_4 + collState->charaState.distance) < collState->charaState.positionFromX ||
        collState->charaState.positionToX < collState->charaPositionFrom.field_0 - (collState->field_A0.s_1.field_4 + collState->charaState.distance))
    {
        return;
    }

    if (collState->charaPositionTo.field_0 + (collState->field_A0.s_1.field_4 + collState->charaState.distance) < collState->charaState.positionFromZ ||
        collState->charaState.positionToZ < collState->charaPositionTo.field_0 - (collState->field_A0.s_1.field_4 + collState->charaState.distance) ||
        collState->charaState.topPos > collState->field_A0.s_1.field_2)
    {
        return;
    }

    deltaX = (collState->charaState.positionFromX - collState->charaPositionFrom.field_0);

    if (collState->charaState.bottomPos < collState->field_A0.s_1.field_0)
    {
        return;
    }

    deltaZ = collState->charaState.positionFromZ - collState->charaPositionTo.field_0;
    temp_s4 = Math_Vector2MagCalc(deltaX, deltaZ);

    temp_v0 = func_8006C248(*(s32*)&collState->charaState.direction, collState->charaState.distance,
                            collState->charaPositionFrom.field_0 - collState->charaState.positionFromX,
                            collState->charaPositionTo.field_0   - collState->charaState.positionFromZ,
                            collState->field_A0.s_1.field_4);
    if (temp_v0 == NO_VALUE)
    {
        return;
    }

    if (temp_v0 == 0)
    {
        if (collState->field_0_9)
        {
            temp3 = collState->field_A0.s_1.field_4 - temp_s4;
            func_8006BCC4(&collState->field_44, collState->field_A0.s_1.field_8, 2, deltaX, deltaZ, temp3);
        }
    }
    else if (collState->isCharaMoving && collState->field_44.field_0.field_0 == 0 && func_8006C1B8(1, temp_v0, collState))
    {
        temp2 = (collState->charaState.positionFromZ - collState->charaPositionTo.field_0);
        tarCharaBottom = Q12_MULT(temp_v0, collState->charaState.offset.vz);

        collState->field_40 = collState->field_A0.s_1.field_8;
        collState->field_38 = temp_v0;

        collState->field_34 = 1;

        temp  = (collState->charaState.positionFromX - collState->charaPositionFrom.field_0);
        temp4 = Q12_MULT(temp_v0, collState->charaState.offset.vx);

        collState->field_3A = Q12_TO_Q4(collState->charaState.distance * temp_v0);
        collState->field_3C = temp + temp4;
        collState->field_3E = temp2 + tarCharaBottom;
    }
}

void func_8006CF18(s_CollisionState* state, s_func_8006CF18* arg1, s32 idx) // 0x8006CF18
{
    q23_8            var_a1;
    s_func_8006CF18* curArg1;

    for (curArg1 = arg1; curArg1 < &arg1[idx]; curArg1++)
    {
        var_a1 = Q12_TO_Q8(curArg1->field_10) + state->charaState.radius;
        if (curArg1->collisionState < (u32)state->charaState.collisionState)
        {
            var_a1 -= 15;
        }

        state->charaPositionFrom.field_0 = Q12_TO_Q8(curArg1->position.vx);
        state->charaPositionTo.field_0   = Q12_TO_Q8(curArg1->position.vz);

        state->field_A0.s_1.field_0        = Q12_TO_Q8(curArg1->field_E + curArg1->position.vy);
        state->field_A0.s_1.field_2        = Q12_TO_Q8(curArg1->field_C + curArg1->position.vy);
        state->field_A0.s_1.field_4        = var_a1;
        state->field_A0.s_1.collisionState = curArg1->collisionState;
        state->field_A0.s_1.field_8        = &curArg1->field_13;

        if (state->field_0_0 == false)
        {
            curArg1->field_13 = 0;
        }

        func_8006CC9C(state);
    }
}

void func_8006D01C(VECTOR3* arg0, VECTOR3* offset, q3_12 offsetAlpha, s_CollisionState* collState) // 0x8006D01C
{
    VECTOR3 adjOffset;
    s32     temp_s0;
    s32     temp_s1;
    s32     temp_a0;
    s32     temp_v0;

    adjOffset.vx = Q12_MULT(offset->vx, offsetAlpha);
    adjOffset.vz = Q12_MULT(offset->vz, offsetAlpha);

    if (collState->field_44.field_0.field_0 || collState->field_44.field_30.field_0)
    {
        arg0->vx = Q12(0.0f);
        arg0->vz = Q12(0.0f);
        *offset    = adjOffset;
        func_8006D2B4(offset, &collState->field_44);
        return;
    }

    if (!collState->field_34)
    {
        *arg0    = adjOffset;
        offset->vz = Q12(0.0f);
        offset->vx = Q12(0.0f);
        return;
    }

    if (offsetAlpha < collState->field_38)
    {
        collState->field_34 = 0;
        *arg0          = adjOffset;
        offset->vz       = Q12(0.0f);
        offset->vx       = Q12(0.0f);
        return;
    }

    arg0->vx = Q12_MULT(offset->vx, collState->field_38);
    arg0->vz = Q12_MULT(offset->vz, collState->field_38);
    offset->vx = adjOffset.vx - arg0->vx;
    offset->vz = adjOffset.vz - arg0->vz;

    temp_s0 = collState->field_3C;
    temp_s1 = collState->field_3E;
    temp_a0 = SQUARE(temp_s0) + SQUARE(temp_s1);

    if (temp_a0 < 256)
    {
        temp_a0 = SquareRoot0(temp_a0 * 256);
        temp_s0 = (temp_s0 << 16) / temp_a0;
        temp_s1 = (temp_s1 << 16) / temp_a0;
    }
    else
    {
        temp_a0 = SquareRoot0(temp_a0);
        temp_s0 = (temp_s0 << 12) / temp_a0; // `Q12_SHIFT`?
        temp_s1 = (temp_s1 << 12) / temp_a0;
    }

    temp_v0  = FP_FROM((offset->vx * temp_s1) + (offset->vz * -temp_s0), Q12_SHIFT);
    offset->vx = Q12_MULT(temp_v0, temp_s1);
    offset->vz = Q12_MULT(temp_v0, -temp_s0);

    if (temp_s0 > Q12(1.0f / 3.0f))
    {
        arg0->vx += Q12(0.004f);
    }
    else if (temp_s0 < Q12(-1.0f / 3.0f))
    {
        arg0->vx -= Q12(0.004f);
    }

    if (temp_s1 > Q12(1.0f / 3.0f))
    {
        arg0->vz += Q12(0.004f);
    }
    else if (temp_s1 < Q12(-1.0f / 3.0f))
    {
        arg0->vz -= Q12(0.004f);
    }
}

void func_8006D2B4(VECTOR3* arg0, s_CollisionState_44* arg1) // 0x8006D2B4
{
    q3_12  rotY1;
    q3_12  rotX1;
    q3_12  angleMin;
    q3_12  angleMax;
    q3_12  angle1;
    q19_12 unkAngleMax;
    bool   cond;
    bool   var_s1;
    q3_12  angle;
    q19_12 unkAngleMin;
    s16    var_v1_2;
    s16    var_a0;
    q3_12  angle2;
    q3_12  angle3;

    if (arg1->field_30.field_0 != 0)
    {
        var_s1 = false;
        if (arg1->field_0.field_0 != 0)
        {
            rotY1 = arg1->field_0.field_2.vx;
            rotX1 = arg1->field_0.field_2.vy;
            if (arg1->field_8.field_0 != 0)
            {
                Vw_ClampAngleRange(&rotY1, &rotX1,
                                   arg1->field_8.field_2.vx, arg1->field_8.field_2.vy);
            }
        }
        else if (arg1->field_8.field_0 != 0)
        {
            rotY1 = arg1->field_8.field_2.vx;
            rotX1 = arg1->field_8.field_2.vy;
        }
        else
        {
            var_s1 = true;
        }

        if (var_s1)
        {
            cond = true;
        }
        else
        {
            angle1  = ratan2(arg0->vz, arg0->vx);
            angle = Q12_ANGLE(90.0f);
            angle2  = Q12_ANGLE_NORM_S(rotX1 - (angle1 - angle));
            angle3  = Q12_ANGLE_NORM_S(rotY1 - (angle1 + angle));
            if (angle2 < Q12_ANGLE(0.0f) && angle3 > Q12_ANGLE(0.0f))
            {
                cond = false;
            }
            else
            {
                cond = true;
            }
        }

        if (cond)
        {
            if (arg1->field_0.field_0 == 0)
            {
                arg1->field_0 = arg1->field_30;
                arg1->field_6 = arg1->field_36;
            }
            else
            {
                arg1->field_0.field_0 += arg1->field_30.field_0;

                Vw_ClampAngleRange(&arg1->field_0.field_2.vx, &arg1->field_0.field_2.vy,
                                   arg1->field_30.field_2.vx, arg1->field_30.field_2.vy);

                var_a0 = arg1->field_6;
                if (arg1->field_6 < arg1->field_36)
                {
                    var_a0 = arg1->field_36;
                }
                arg1->field_6 = var_a0;
            }
        }

        if (arg1->field_8.field_0 != 0)
        {
            if (arg1->field_0.field_0 == 0)
            {
                arg1->field_0 = arg1->field_8;
                arg1->field_6 = 0;
            }
            else
            {
                arg1->field_0.field_0 += arg1->field_8.field_0;
                Vw_ClampAngleRange(&arg1->field_0.field_2.vx, &arg1->field_0.field_2.vy,
                                   arg1->field_8.field_2.vx, arg1->field_8.field_2.vy);
            }
        }
    }

    if (arg1->field_0.field_0 != 0)
    {
        if (arg1->field_0.field_2.vx == arg1->field_0.field_2.vy)
        {
            arg0->vx = Q12(0.0f);
            arg0->vz = Q12(0.0f);
            return;
        }

        angle = (arg1->field_0.field_2.vx + arg1->field_0.field_2.vy) >> 1;
        if (arg1->field_0.field_2.vy < arg1->field_0.field_2.vx)
        {
            angle = Q12_FRACT(angle + Q12_ANGLE(180.0f));
        }

        if (arg1->field_8.field_0 == 0)
        {
            angleMin = arg1->field_0.field_2.vx;
            angleMax = arg1->field_0.field_2.vy;
        }
        else
        {
            angleMin = arg1->field_0.field_2.vx;
            angleMax = arg1->field_0.field_2.vy;

            Vw_ClampAngleRange(&angleMin, &angleMax, arg1->field_8.field_2.vx, arg1->field_8.field_2.vy);

            angleMin = Q12_FRACT(angleMin);
            angleMax = Q12_FRACT(angleMax);
            if (angleMin == angleMax)
            {
                angleMin = arg1->field_0.field_2.vx;
                angleMax = arg1->field_0.field_2.vy;
            }

            if (angleMin != angleMax)
            {
                unkAngleMin = Q12_ANGLE_NORM_S(angleMin - angle);
                unkAngleMax = Q12_ANGLE_NORM_S(angleMax - angle);
                if (unkAngleMin >= Q12_ANGLE(0.0f) || unkAngleMax <= Q12_ANGLE(0.0f))
                {
                    if (ABS(unkAngleMin) < ABS(unkAngleMax))
                    {
                        angle = angleMin;
                    }
                    else
                    {
                        angle = angleMax;
                    }
                }
            }
        }

        var_v1_2 = MIN(arg1->field_6 + 2, 16) * 16;
        func_8006D600(arg0, angle, angleMin, angleMax, var_v1_2);
    }
}

void func_8006D600(VECTOR3* pos, q19_12 angle, q19_12 angleMin, q19_12 angleMax, q19_12 dist) // 0x8006D600
{
    q19_12 angle3;
    q3_12  normAngle;
    q3_12  normAngleMin;
    q3_12  normAngleMax;
    q19_12 sinAngle2;
    q19_12 deltaX;
    q19_12 deltaZ;
    q19_12 z;
    q19_12 x;
    q19_12 cosAngle2;
    q19_12 angle2;
    q19_12 dist0;
    q19_12 angle1;

    normAngle    = Q12_FRACT(angle);
    normAngleMin = Q12_FRACT(angleMin);
    normAngleMax = Q12_FRACT(angleMax);

    if (dist > Q12(1.0f / 16.0f))
    {
        dist = Q12(1.0f / 16.0f);
    }

    x      = Q12_MULT(dist, Math_Cos(normAngle));
    angle2 = normAngleMax;
    z      = Q12_MULT(dist, Math_Sin(normAngle));
    deltaX = pos->vx - x;
    deltaZ = pos->vz - z;
    angle1 = Q12_FRACT(ratan2(deltaZ, deltaX));

    if (angle1 < normAngleMin)
    {
        angle1 += Q12_ANGLE(360.0f);
    }

    if (angle2 < normAngleMin)
    {
        angle2 += Q12_ANGLE(360.0f);
    }

    angle3 = normAngleMin + Q12_ANGLE(360.0f);
    if (angle2 < angle1)
    {
        if (((angle2 + angle3) >> 1) < angle1)
        {
            angle2 = angle3;
        }

        sinAngle2 = Math_Sin(angle2);
        cosAngle2 = Math_Cos(angle2);

        dist0 = Q12_MULT(deltaX, cosAngle2) + Q12_MULT(deltaZ, sinAngle2);
        if (dist0 < Q12(0.0f))
        {
            dist0 = Q12(0.0f);
        }

        pos->vx = x + Q12_MULT(dist0, cosAngle2);
        pos->vz = z + Q12_MULT(dist0, sinAngle2);
    }
}

void func_8006D774(s_CollisionState* state, VECTOR3* arg1, VECTOR3* arg2) // 0x8006D774
{
    SVECTOR offset0; // Q7.8
    SVECTOR offset1; // Q7.8

    offset0.vx = Q12_TO_Q8(arg1->vx);
    offset0.vy = Q12_TO_Q8(arg1->vz);
    offset1.vx = Q12_TO_Q8(arg2->vx);
    offset1.vy = Q12_TO_Q8(arg2->vz);

    state->field_34                  = 0;
    state->field_44.field_0.field_0  = 0;
    state->field_44.field_6          = 0;
    state->field_44.field_8.field_0  = 0;
    state->field_44.field_36         = 0;
    state->field_44.field_30.field_0 = 0;

    func_8006D7EC(&state->charaState, &offset0, &offset1);
}

void func_8006D7EC(s_CollisionCharaState* charaState, SVECTOR* offset0, SVECTOR* offset1) // 0x8006D7EC
{
    q3_12  headingAngle;
    q19_12 dist;
    q7_8   z;

    charaState->offset.vx = offset1->vx;
    z                     = offset1->vy;
    charaState->offset.vz = offset1->vy;

    dist                 = Math_Vector2MagCalc(charaState->offset.vx, z);
    charaState->distance = dist;

    if (dist != Q12(0.0f))
    {
        charaState->direction.vx = FP_TO(charaState->offset.vx, Q12_SHIFT) / dist;
        charaState->direction.vz = FP_TO(charaState->offset.vz, Q12_SHIFT) / charaState->distance;

        headingAngle             = ratan2(charaState->offset.vz, charaState->offset.vx);
        charaState->direction.vx = Math_Cos(headingAngle);
        charaState->direction.vz = Math_Sin(headingAngle);
    }
    else
    {
        charaState->direction.vx = Q12(1.0f);
        charaState->direction.vz = Q12(0.0f);
    }

    charaState->positionFromX = charaState->positionFromX + offset0->vx;
    charaState->positionFromZ = charaState->positionFromZ + offset0->vy;
    charaState->positionToX   = charaState->positionFromX + charaState->offset.vx;
    charaState->positionToZ   = charaState->positionFromZ + charaState->offset.vz;
}

// Padding with garbage data.
#if VERSION_IS(USA)
    static const u8 __unk_rdata[] = { 0x00, 0x42, 0x05, 0x80, 0x00, 0x00, 0x00, 0x00 };
#elif VERSION_IS(JAP0)
    static const u8 __unk_rdata[] = { 0x00, 0x20, 0x3D, 0x20, 0x00, 0x00, 0x00, 0x00 };
#elif VERSION_IS(JAP1)
    static const u8 __unk_rdata[] = { 0x00, 0x5E, 0x05, 0x80, 0x00, 0x00, 0x00, 0x00 };
#elif VERSION_IS(JAP2)
    static const u8 __unk_rdata[] = { 0x00, 0x00, 0x42, 0x24, 0x00, 0x00, 0x00, 0x00 };
#endif
