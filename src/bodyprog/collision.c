#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>
#include <psyq/libapi.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/collision.h"
#include "bodyprog/math/math.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"

s_800C4478 D_800C4478;

// ========================================
// COLLISION HANDLING
// ========================================

void Collision_Init(void) // 0x800697EC
{
    Collision_FlagsSet(CollisionFlag_0);
    D_800C4478.triggerZoneCount = 0;
}

u16 Collision_FlagsGet(void) // 0x80069810
{
    return D_800C4478.flags;
}

void Collision_FlagsSet(u16 collFlags) // 0x80069820
{
    D_800C4478.flags = collFlags;
}

void Collision_FlagBitsSet(u16 collFlags) // 0x8006982C
{
    D_800C4478.flags |= collFlags;
}

void func_80069844(s32 collFlags) // 0x80069844
{
    D_800C4478.flags = (D_800C4478.flags & ~collFlags) | CollisionFlag_0;
}

void Collision_TriggerZonesUpdate(q19_12 posX, q19_12 posZ, s_TriggerZone* zones) // 0x80069860
{
    s_TriggerZone* curZone;
    q19_12         minX;
    q19_12         maxX;
    q19_12         minZ;
    q19_12         maxZ;

    D_800C4478.triggerZoneCount = 0;
    for (curZone = zones; !curZone->isEndOfArray; curZone++)
    {
        minX = FP_TO(curZone->positionX, Q12_SHIFT);
        maxX = FP_TO(curZone->positionX + curZone->sizeX, Q12_SHIFT);
        minZ = FP_TO(curZone->positionZ, Q12_SHIFT);
        maxZ = FP_TO(curZone->positionZ + curZone->sizeZ, Q12_SHIFT);

        minX -= Q12(16.0f);
        maxX += Q12(16.0f);
        minZ -= Q12(16.0f);
        maxZ += Q12(16.0f);

        if (posX >= minX && maxX >= posX &&
            posZ >= minZ && maxZ >= posZ)
        {
            D_800C4478.triggerZones[D_800C4478.triggerZoneCount] = curZone;
            D_800C4478.triggerZoneCount++;
        }
    }
}

void IpdCollData_FixOffsets(s_IpdCollisionData* collData) // 0x8006993C
{
    collData->ptr_C  = (u8*)collData->ptr_C + (u32)collData;
    collData->ptr_10 = (u8*)collData->ptr_10 + (u32)collData;
    collData->ptr_14 = (u8*)collData->ptr_14 + (u32)collData;
    collData->ptr_18 = (u8*)collData->ptr_18 + (u32)collData;
    collData->ptr_20 = (u8*)collData->ptr_20 + (u32)collData;
    collData->ptr_28 = (u8*)collData->ptr_28 + (u32)collData;
    collData->ptr_2C = (u8*)collData->ptr_2C + (u32)collData;
}

void func_80069994(s_IpdCollisionData* collData) // 0x80069994
{
    s32* curPtr;

    collData->field_30++;
    if (collData->field_30 > 252)
    {
        collData->field_30 = 0;

        // TODO: Is this `memset`/`bzero`?
        for (curPtr = &collData->field_34[0]; curPtr < &collData->field_34[256]; curPtr++)
        {
            *curPtr = 0;
        }
    }
}

void func_800699E4(s_IpdCollisionData* collData) // 0x800699E4
{
    collData->field_30++;
}

void Collision_Get(s_Collision* coll, q19_12 posX, q19_12 posZ) // 0x800699F8
{
    s_CollisionQuery    collQuery;
    VECTOR3             pos;
    s_CollisionState    state;
    s_IpdCollisionData* ipdCollData;

    pos.vx = Q12(0.0f);
    pos.vy = Q12(0.0f);
    pos.vz = Q12(0.0f);

    ipdCollData = Ipd_CollisionDataGet(posX, posZ);
    if (ipdCollData == NULL)
    {
        coll->groundHeight = Q12(8.0f);
        coll->field_6      = 0;
        coll->field_4      = 0;
        coll->groundType   = GroundType_Default;
        return;
    }

    collQuery.position.vx = posX;
    collQuery.position.vy = Q12(0.0f);
    collQuery.position.vz = posZ;
    collQuery.bottom      = Q12(0.0f);
    collQuery.top         = Q12(0.0f);
    collQuery.radius      = Q12(0.0f);
    Collision_QueryInit(&state, &pos, &collQuery, false);

    state.field_0_8  = 0;
    state.field_0_9  = 0;
    state.field_0_10 = 1;
    Ipd_GridCollisionQuery(&state, ipdCollData);

    if (state.field_90 == 1)
    {
        coll->groundType   = GroundType_Default;
        coll->groundHeight = Q12(8.0f);
    }
    else
    {
        coll->groundType   = state.groundType;
        coll->groundHeight = Q8_TO_Q12(Ipd_GroundHeightGet(state.field_4.positionX_18, state.field_4.positionZ_1C, &state));
    }

    coll->field_4 = state.field_88;
    coll->field_6 = state.field_8C;
}

s32 Collision_WallDetect(s_CollisionResult* collResult, VECTOR3* offset, s_SubCharacter* chara) // 0x80069B24
{
    s32 stackPtr;
    s32 response;

    stackPtr = SetSp(0x1F8003D8);
    response = Collision_WallResponse(collResult, offset, chara, Collision_CharaCollisionSetup(collResult, offset, chara));
    SetSp(stackPtr);
    return response;
}

s32 Collision_WallResponse(s_CollisionResult* collResult, const VECTOR3* offset, s_SubCharacter* chara, s32 response) // 0x80069BA8
{
    #define POINT_COUNT          9
    #define ANGLE_STEP           Q12_ANGLE(370.0f / POINT_COUNT) // @bug? Maybe `360.0f` was intended.
    #define WALL_COUNT_THRESHOLD 3                               // Unknown purpose.
    #define WALL_HEIGHT          Q12(0.5f)

    s_Collision     coll;
    e_CollisionType collType;
    q19_12          groundHeight;
    q19_12          wallHeightBound;
    s32             i;
    s32             wallCount;
    s32             groundType; // `e_GroundType`

    if (response == NO_VALUE)
    {
        response = 1;

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

            switch (collResult->groundType)
            {
                case GroundType_12:
                    collType = CollisionType_Unk2;
                    break;

                default:
                    collType = (collResult->groundHeight < wallHeightBound) ? CollisionType_Wall : CollisionType_None;
                    break;
            }

            wallCount = 0;
            if (collType == CollisionType_None)
            {
                break;
            }

            for (i = 0, groundType = GroundType_12; i < POINT_COUNT; i++)
            {
                Collision_Get(&coll,
                              chara->position.vx + Q12_MULT(Math_Sin(i * ANGLE_STEP), Q12(0.2f)),
                              chara->position.vz + Q12_MULT(Math_Cos(i * ANGLE_STEP), Q12(0.2f)));

                switch (collType)
                {
                    case CollisionType_Wall:
                        if (coll.groundHeight < wallHeightBound)
                        {
                            wallCount++;
                        }
                        break;

                    case CollisionType_Unk2:
                        if (coll.groundType != GroundType_12)
                        {
                            groundType   = coll.groundType;
                            groundHeight = coll.groundHeight;
                        }
                        break;
                }
            }

            switch (collType)
            {
                case CollisionType_Wall:
                    if (wallCount < WALL_COUNT_THRESHOLD)
                    {
                        collResult->groundHeight = chara->position.vy;
                    }
                    break;

                case CollisionType_Unk2:
                    if (groundType != GroundType_12)
                    {
                        collResult->groundHeight = groundHeight;
                        collResult->groundType   = GroundType_12;
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

// Padding with garbage data.
#if VERSION_IS(USA)
    static const u8 unk_rdata[] = { 0x00, 0x42, 0x05, 0x80, 0x00, 0x00, 0x00, 0x00 };
#elif VERSION_IS(JAP0)
    static const u8 unk_rdata[] = { 0x00, 0x20, 0x3D, 0x20, 0x00, 0x00, 0x00, 0x00 };
#elif VERSION_IS(JAP1)
    static const u8 unk_rdata[] = { 0x00, 0x5E, 0x05, 0x80, 0x00, 0x00, 0x00, 0x00 };
#elif VERSION_IS(JAP2)
    static const u8 unk_rdata[] = { 0x00, 0x00, 0x42, 0x24, 0x00, 0x00, 0x00, 0x00 };
#endif

void Collision_GroundProbeRadial(s_CollisionResult* collResult, const VECTOR3* pos,
                                 q19_12 startGroundHeight, q19_12 startHeadingAngle) // 0x80069DF0
{
    #define POINT_COUNT 16
    #define ANGLE_STEP  Q12_ANGLE(360.0f / POINT_COUNT)

    s32         groundHeights[POINT_COUNT];
    s_Collision coll;
    q19_12      angle;
    s32         var_a0;
    q19_12      groundHeight;
    s32         var_s0;
    s32         i;
    q19_12      groundHeightMax;
    q19_12      groundHeightMin;
    s32         lowestGroundHeightIdx;

    groundHeightMin = Q12(-30.0f);
    groundHeightMax = Q12(30.0f);
    lowestGroundHeightIdx = 0;

    // Collect ground heights around position?
    for (i = 0; i < POINT_COUNT; i++)
    {
        Collision_Get(&coll,
                      pos->vx + Math_Sin((startHeadingAngle & 0xF) + (i * ANGLE_STEP)),
                      pos->vz + Math_Cos((startHeadingAngle & 0xF) + (i * ANGLE_STEP)));
        groundHeights[i] = coll.groundHeight;

        if (groundHeightMin < coll.groundHeight)
        {
            groundHeightMin       = coll.groundHeight;
            lowestGroundHeightIdx = i;
        }

        if (coll.groundHeight < groundHeightMax)
        {
            groundHeightMax = coll.groundHeight;
        }
    }

    groundHeight = (groundHeightMin + groundHeightMax) >> 1; // `/ 2`.
    if (groundHeight < (startGroundHeight - Q12(0.1f)))
    {
        groundHeight = startGroundHeight - Q12(0.1f);
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
    collResult->offset_0.vx = Q12_MULT_PRECISE(Math_Sin(angle), Q12(1.0f / 16.0f));
    collResult->offset_0.vz = Q12_MULT_PRECISE(Math_Cos(angle), Q12(1.0f / 16.0f));

    #undef POINT_COUNT
    #undef ANGLE_STEP
}

s32 Collision_CharaCollisionSetup(s_CollisionResult* collResult, VECTOR3* offset, s_SubCharacter* chara) // 0x80069FFC
{
    s_CollisionQuery collQuery;
    VECTOR3          offsetCpy;
    s32              collDataIdx;
    s32              charaCount;
    bool             cond;

    collQuery.position.vx = chara->position.vx + chara->collision.shapeOffsets.cylinder.vx;
    collQuery.position.vy = chara->position.vy - Q12(0.02f);
    collQuery.position.vz = chara->position.vz + chara->collision.shapeOffsets.cylinder.vz;

    if (Ipd_CollisionDataGet(chara->position.vx, chara->position.vz) == NULL)
    {
        Collision_DefaultResultSet(collResult, Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(8.0f));
        return 1;
    }

    collQuery.top            = chara->collision.box.top;
    collQuery.bottom         = chara->collision.box.bottom;
    collQuery.radius         = chara->collision.cylinder.radius;
    collQuery.collisionState = chara->collision.state;

    offsetCpy = *offset;

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

    return func_8006A4A8(collResult, &offsetCpy, &collQuery, cond,
                         Ipd_ActiveChunksCollisionDataGet(&collDataIdx), collDataIdx, NULL, 0,
                         Collision_CollidableCharasGet(&charaCount, chara, true), charaCount);
}

void Collision_DefaultResultSet(s_CollisionResult* collResult, q19_12 offsetX, q19_12 offsetY, q19_12 offsetZ, q19_12 groundHeight) // 0x8006A178
{
    collResult->offset_0.vx  = offsetX;
    collResult->offset_0.vy  = offsetY;
    collResult->offset_0.vz  = offsetZ;
    collResult->field_12     = 0;
    collResult->field_10     = 0;
    collResult->groundType   = GroundType_Default;
    collResult->field_18     = 0xFFFF0000;
    collResult->groundHeight = groundHeight;
}

s_SubCharacter** Collision_CollidableCharasGet(s32* collCharaCount, const s_SubCharacter* excludedChara, bool includePlayer) // 0x8006A1A4
{
    s_SubCharacter*         curChara;
    static s_SubCharacter*  collCharas[7];
    static s_SubCharacter** curCollChara; /** Array of active characters. */

    // Filder invalid case.
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

s32 Collision_OffsetCheck(s_CollisionResult* collResult, VECTOR* offset, s_CollisionQuery* collQuery) // 0x8006A3B4
{
    s32 stackPtr;
    s32 var1;

    stackPtr = SetSp(0x1F8003D8);
    var1 = func_8006A42C(collResult, offset, collQuery);
    SetSp(stackPtr);

    if (var1 == NO_VALUE)
    {
        var1 = 1;
    }

    return var1;
}

s32 func_8006A42C(s_CollisionResult* collResult, VECTOR3* offset, s_CollisionQuery* collQuery) // 0x8006A42C
{
    VECTOR3 offsetCpy;
    s32     collDataIdx;

    offsetCpy = *offset;

    return func_8006A4A8(collResult, &offsetCpy, collQuery, false,
                         Ipd_ActiveChunksCollisionDataGet(&collDataIdx), collDataIdx, NULL, 0, NULL, 0);
}

s32 func_8006A4A8(s_CollisionResult* collResult, VECTOR3* offset, s_CollisionQuery* collQuery, bool arg3,
                  s_IpdCollisionData** collDataPtrs, s32 collDataIdx, s_func_8006CF18* arg6, s32 arg7, s_SubCharacter** charas, s32 charaCount) // 0x8006A4A8
{
    s_CollisionState     collState;
    VECTOR3              sp120; // Q19.12
    VECTOR3              offset1;
    VECTOR3              offsetCpy;
    s32                  var_a0;
    s32                  i;
    bool                 cond;
    q23_8                groundHeight;
    s32                  count;
    s_SubCharacter**     curChara;
    s_IpdCollisionData** curCollData;
    s_SubCharacter*      chara;

    cond = false;

    if (collQuery->collisionState == CharaCollisionState_5)
    {
        Collision_DefaultResultSet(collResult, offset->vx, offset->vy, offset->vz, collQuery->position.vy);
        return 0;
    }

    func_8006A940(offset, collQuery, charas, charaCount);

    offsetCpy = *offset;

    collResult->field_18 = func_8006F620(&offsetCpy, collQuery, collQuery->radius, collQuery->top);

    Collision_QueryInit(&collState, &offsetCpy, collQuery, arg3);

    offset1 = offsetCpy;

    collResult->offset_0.vz = Q12(0.0f);
    collResult->offset_0.vx = Q12(0.0f);
    collResult->offset_0.vy = offsetCpy.vy;

    while (true)
    {
        if (collState.field_0_0 != 0)
        {
            collState.field_0_8  = collState.field_4.distance_8 != Q12(0.0f);
            collState.field_0_9  = 0;
            collState.field_0_10 = 0;
        }
        else
        {
            collState.field_0_8  = collState.field_4.distance_8 != Q12(0.0f);
            collState.field_0_9  = 1;
            collState.field_0_10 = 1;
        }

        // Run through collision data.
        for (curCollData = collDataPtrs; curCollData < &collDataPtrs[collDataIdx]; curCollData++)
        {
            Ipd_GridCollisionQuery(&collState, *curCollData);
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
            var_a0 = (chara->collision.cylinder.radius >> 4) + collState.field_4.field_28;

            if (chara->collision.state < (u32)collState.field_4.collisionState)
            {
                var_a0 -= 15;
            }

            collState.field_98.field_0 = Q12_TO_Q8(chara->position.vx + chara->collision.shapeOffsets.cylinder.vx);
            collState.field_9C.field_0 = Q12_TO_Q8(chara->position.vz + chara->collision.shapeOffsets.cylinder.vz);

            collState.field_A0.s_1.field_0 = Q12_TO_Q8(chara->collision.box.top + chara->position.vy);
            collState.field_A0.s_1.field_2 = Q12_TO_Q8(chara->collision.box.bottom + chara->position.vy);
            collState.field_A0.s_1.field_4 = var_a0;
            collState.field_A0.s_1.collisionState = chara->collision.state;
            collState.field_A0.s_1.field_8 = &chara->collision.field_E0;

            if (collState.field_0_0 == 0)
            {
                chara->collision.field_E0 = 0;
            }

            func_8006CC9C(&collState);
            func_8006CF18(&collState, chara->collision.field_E4, chara->collision.field_E1_4);
        }

        func_8006D01C(&sp120, &offset1, Collision_OffsetAlphaGet(&collState), &collState);

        collResult->offset_0.vx += sp120.vx;
        collResult->offset_0.vz += sp120.vz;

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

        collState.field_0_0 = 1;
        func_8006D774(&collState, &sp120, &offset1);
    }

    if (collState.field_90 == 1)
    {
        groundHeight           = Q12(8.0f);
        collResult->groundType = GroundType_Default;
    }
    else
    {
        collResult->groundType = collState.groundType;
        groundHeight           = Ipd_GroundHeightGet(collState.field_4.positionX_18 + Q12_TO_Q8(sp120.vx), collState.field_4.positionZ_1C + Q12_TO_Q8(sp120.vz), &collState) * 16;
    }

    collResult->groundHeight = groundHeight;
    collResult->field_10 = collState.field_88;
    collResult->field_12 = collState.field_8C;

    if (cond)
    {
        return NO_VALUE;
    }

    return collState.field_0_0 != 0;
}

void func_8006A940(VECTOR3* offset, s_CollisionQuery* collQuery, s_SubCharacter** charas, s32 charaCount) // 0x8006A940
{
    q19_12          angle;
    q19_12          posZ;
    q19_12          posX;
    q19_12          var_a0;
    s32             i;
    q19_12          var_s4;
    q19_12          var_v0;
    s32             mag;
    q19_12          top;
    q19_12          bottom;
    q19_12          temp5;
    q19_12          temp6;
    s_SubCharacter* curChara;

    var_s4 = Q12(1.0f);
    angle  = ratan2(offset->vx, offset->vz);

    for (i = 0; i < charaCount; i++)
    {
        curChara = charas[i];
        if (curChara->collision.state == CharaCollisionState_Ignore ||
            curChara->collision.state == CharaCollisionState_Player ||
            curChara->collision.state >= collQuery->collisionState)
        {
            continue;
        }

        top    = curChara->collision.box.top    + curChara->position.vy;
        bottom = curChara->collision.box.bottom + curChara->position.vy;

        // TODO: Rotation + position? Seems wrong.
        temp6 = collQuery->top + collQuery->position.vy;
        temp5 = collQuery->bottom + collQuery->position.vy;
        if (top > temp5 || bottom < temp6)
        {
            continue;
        }

        posX = (curChara->position.vx + curChara->collision.shapeOffsets.cylinder.vx) - collQuery->position.vx;
        posZ = (curChara->position.vz + curChara->collision.shapeOffsets.cylinder.vz) - collQuery->position.vz;

        mag = Vc_VectorMagnitudeCalc(posX, Q12(0.0f), posZ);
        if (((curChara->collision.cylinder.radius + collQuery->radius) + Q12_ANGLE(36.0f)) < mag)
        {
            continue;
        }

        var_a0 = Q12_MULT(Math_Cos(ratan2(posX, posZ) - angle), Q12(1.5f));

        var_v0 = MAX(var_a0, Q12(0.0f));
        var_a0 = var_v0;

        // Radius calc?
        if (curChara->model.charaId == Chara_HangedScratcher)
        {
            var_a0 = MIN(var_a0, Q12(0.6f));
        }
        else
        {
            var_a0 = MIN(var_a0, Q12(0.4f));
        }

        var_s4 -= var_a0;
    }

    var_s4 = MAX(var_s4, Q12(0.4f));

    offset->vx = Q12_MULT(var_s4, offset->vx);
    offset->vz = Q12_MULT(var_s4, offset->vz);
}

void Collision_QueryInit(s_CollisionState* collState, VECTOR3* pos, s_CollisionQuery* collQuery, bool arg3) // 0x8006AB50
{
    collState->field_0_0       = 0;
    collState->flags_2         = D_800C4478.flags;
    collState->field_4.field_4 = arg3;

    Collision_QueryDirectionCalc(&collState->field_4, pos, collQuery);

    collState->field_7C = Q8(30.0f);
    collState->field_34 = 0;
    
    collState->field_44.field_0.field_0  = 0;
    collState->field_44.field_6          = 0;
    collState->field_44.field_8.field_0  = 0;
    collState->field_44.field_36         = 0;
    collState->field_44.field_30.field_0 = 0;
    
    collState->field_8C = 0;
    collState->field_88 = 0;
    collState->field_90 = 1;
    collState->groundType = GroundType_Default;
}

void Collision_QueryDirectionCalc(s_func_8006ABC0* result, const VECTOR3* pos, const s_CollisionQuery* collQuery) // 0x8006ABC0
{
    q3_12 headingAngle;

    result->offset_C.vx = Q12_TO_Q8(pos->vx);
    result->offset_C.vy = Q12_TO_Q8(pos->vy);
    result->offset_C.vz = Q12_TO_Q8(pos->vz);

    result->distance_8 = SquareRoot0(SQUARE(result->offset_C.vx) + SQUARE(result->offset_C.vz));
    if (result->distance_8 != Q12(0.0f))
    {
        // @unused
        result->direction_14.vx = Q12(result->offset_C.vx) / result->distance_8;
        result->direction_14.vz = Q12(result->offset_C.vz) / result->distance_8;

        headingAngle            = ratan2(result->offset_C.vz, result->offset_C.vx);
        result->direction_14.vx = Math_Cos(headingAngle);
        result->direction_14.vz = Math_Sin(headingAngle);
    }
    else
    {
        result->direction_14.vx = Q12(1.0f);
        result->direction_14.vz = Q12(0.0f);
    }

    result->field_28        = Q12_TO_Q8(collQuery->radius);
    result->positionX_18    = Q12_TO_Q8(collQuery->position.vx);
    result->positionZ_1C    = Q12_TO_Q8(collQuery->position.vz);
    result->newPositionX_20 = result->positionX_18 + result->offset_C.vx;
    result->newPositionZ_24 = result->positionZ_1C + result->offset_C.vz;
    result->field_2A        = Q12_TO_Q8(collQuery->top + collQuery->position.vy);
    result->field_2C        = Q12_TO_Q8(collQuery->bottom + collQuery->position.vy);
    result->collisionState  = collQuery->collisionState;
}

void Ipd_GridCollisionQuery(s_CollisionState* collState, s_IpdCollisionData* collData) // 0x8006AD44
{
    s32                    endIdx;
    s32                    startIdx;
    s32                    i;
    s32                    j;
    s_IpdCollisionData_20* curUnk;

    if ((collData->field_8_8 == 0 && collData->field_8_16 == 0 && collData->field_8_24 == 0) ||
        !func_8006AEAC(collState, collData))
    {
        return;
    }

    if (collState->field_0_0 == 0)
    {
        func_80069994(collData);
    }

    startIdx = collState->field_A0.s_0.field_0;
    endIdx   = (collState->field_A0.s_0.field_0 + collState->field_A0.s_0.field_2) - 1;

    for (i = collState->field_A0.s_0.field_1; i < (collState->field_A0.s_0.field_1 + collState->field_A0.s_0.field_3); i++)
    {
        curUnk = &collData->ptr_20[(i * collData->field_1E) + startIdx];

        for (j = startIdx; j <= endIdx; j++, curUnk++)
        {
            func_8006B1C8(collState, collData, curUnk);
        }
    }

    if (collState->field_0_0 == 0)
    {
        func_800699E4(collData);
    }

    if (collState->field_0_10)
    {
        func_8006C838(collState, collData);
        if (collState->field_A0.s_0.field_4 != NULL)
        {
            func_8006CA18(collState, collData, collState->field_A0.s_0.field_4);
        }
    }
}

bool func_8006AEAC(s_CollisionState* collState, const s_IpdCollisionData* collData) // 0x8006AEAC
{
    s_CollisionState_A8* curUnk;

    if (!func_8006B004(collState, collData))
    {
        return false;
    }

    collState->field_98.vec_0.vx = collState->field_4.positionX_18 - collData->positionX;
    collState->field_98.vec_0.vz = collState->field_4.positionZ_1C - collData->positionZ;
    collState->field_9C.vec_0.vx = collState->field_4.newPositionX_20 - collData->positionX;
    collState->field_9C.vec_0.vz = collState->field_4.newPositionZ_24 - collData->positionZ;

    if ((collState->field_98.vec_0.vx / collData->field_1C) < 0 || (collState->field_98.vec_0.vx / collData->field_1C) >= collData->field_1E ||
        ((collState->field_98.vec_0.vz / collData->field_1C) < 0) || (collState->field_98.vec_0.vz / collData->field_1C) >= collData->field_1F)
    {
        collState->field_A0.s_0.field_4 = NULL;
        return true;
    }

    collState->field_A0.s_0.field_4 = (s_func_8006CA18*)&collData->ptr_20[((collState->field_98.vec_0.vz / collData->field_1C) * collData->field_1E) +
                                                                          (collState->field_98.vec_0.vx / collData->field_1C)];
    collState->field_C8             = UCHAR_MAX;

    for (curUnk = collState->field_A0.s_0.field_8; curUnk < &collState->field_C8; curUnk++)
    {
        curUnk->field_0 = 0;
        curUnk->field_1 = UCHAR_MAX;
        curUnk->field_4 = INT_MAX;
    }

    return true;
}

bool func_8006B004(s_CollisionState* collState, const s_IpdCollisionData* collData) // 0x8006B004
{
    s32 var_a0;
    s32 var_a3;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_t3;
    s32 temp_t4;
    s32 var_a2;
    s32 var_t0;

    temp_lo   = collData->field_1C * collData->field_1E;
    temp_t3   = temp_lo - 1;
    temp_lo_2 = collData->field_1C * collData->field_1F;
    temp_t4   = temp_lo_2 - 1;

    var_a3 = collState->field_4.positionX_18 - collData->positionX;
    var_t0 = collState->field_4.newPositionX_20 - collData->positionX;
    if (var_t0 < var_a3)
    {
        var_t0 ^= var_a3;
        var_a3 ^= var_t0;
        var_t0 ^= var_a3;
    }

    var_a3 -= collState->field_4.field_28;
    var_t0 += collState->field_4.field_28;

    var_a0 = collState->field_4.positionZ_1C - collData->positionZ;
    var_a2 = collState->field_4.newPositionZ_24 - collData->positionZ;
    if (var_a2 < var_a0)
    {
        var_a2 ^= var_a0;
        var_a0 ^= var_a2;
        var_a2 ^= var_a0;
    }

    var_a0 -= collState->field_4.field_28;
    var_a2 += collState->field_4.field_28;

    if (temp_lo < var_a3 || temp_lo_2 < var_a0 || var_t0 < 0 || var_a2 < 0)
    {
        return false;
    }

    var_a3 = limitRange(var_a3, 0, temp_t3);
    var_a0 = limitRange(var_a0, 0, temp_t4);
    var_t0 = limitRange(var_t0, 0, temp_t3);
    var_a2 = limitRange(var_a2, 0, temp_t4);

    collState->field_A0.s_0.field_0 = var_a3 / collData->field_1C;
    collState->field_A0.s_0.field_1 = var_a0 / collData->field_1C;
    collState->field_A0.s_0.field_2 = ((var_t0 / collData->field_1C) - collState->field_A0.s_0.field_0) + 1;
    collState->field_A0.s_0.field_3 = ((var_a2 / collData->field_1C) - collState->field_A0.s_0.field_1) + 1;

    return true;
}

void func_8006B1C8(s_CollisionState* collState, s_IpdCollisionData* collData, s_IpdCollisionData_20* arg2) // 0x8006B1C8
{
    s32 var;
    s32 i;
    u8  idx;

    for (i = arg2[0].field_0; i < arg2[1].field_0; i++)
    {
        idx = collData->ptr_28[i];

        if (collData->field_30 >= collData->field_34[idx])
        {
            collData->field_34[idx] = collData->field_30 + 1;
            var                     = collData->field_8_16;

            if (idx < var)
            {
                if (func_8006B318(collState, collData, idx))
                {
                    if (collState->field_0_10)
                    {
                        func_8006B6E8(collState, arg2);
                    }

                    if (collState->field_0_8 || collState->field_0_9)
                    {
                        if (collState->field_CC.field_C.s_field_0.field_1 == 0xFF)
                        {
                            func_8006B9C8(collState);
                        }

                        if (collState->field_CC.field_C.s_field_0.field_0 == 0xFF)
                        {
                            func_8006B8F8(&collState->field_CC);
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

bool func_8006B318(s_CollisionState* collState, const s_IpdCollisionData* collData, s32 idx) // 0x8006B318
{
    s32                    temp_a0_5;
    s32                    temp_s0;
    s32                    temp_v0;
    s_IpdCollisionData_10* temp_a0;
    s_IpdCollisionData_14* temp_a3;

    temp_a3 = &collData->ptr_14[idx];

    if (!((collState->flags_2 >> (temp_a3->field_0_14 * 4 | temp_a3->field_2_14)) & (1 << 0)))
    {
        return false;
    }

    collState->field_CC.ipdCollisionData_0 = collData;
    collState->field_CC.field_4 = idx;

    collState->field_CC.field_6.vx = temp_a3->field_0_0;
    collState->field_CC.field_6.vy = temp_a3->field_2_0;
    collState->field_CC.field_6.vz = temp_a3->field_4;

    collState->field_CC.field_12 = collData->ptr_C[temp_a3->field_7];
    collState->field_CC.field_18 = collData->ptr_C[temp_a3->field_6];

    collState->field_CC.field_C.s_field_0.field_0 = temp_a3->field_8;

    if ((collState->field_CC.field_C.s_field_0.field_0) != 0xFF)
    {
        temp_a0                 = &collData->ptr_10[collState->field_CC.field_C.s_field_0.field_0];
        collState->field_CC.field_E  = temp_a0->field_6_8;
        collState->field_CC.field_10 = temp_a0->field_6_5;

        if (collState->field_4.field_4 && (temp_a0->field_6_5 == 1 || temp_a0->groundType == GroundType_12))
        {
            collState->field_CC.field_12.vy -= Q12(1.0f);
            collState->field_CC.field_18.vy -= Q12(1.0f);
        }
    }

    collState->field_CC.field_C.s_field_0.field_1 = temp_a3->field_9;

    if ((collState->field_CC.field_C.s_field_0.field_1) != 0xFF)
    {
        temp_a0                 = &collData->ptr_10[collState->field_CC.field_C.s_field_0.field_1];
        collState->field_CC.field_F  = temp_a0->field_6_8;
        collState->field_CC.field_11 = temp_a0->field_6_5;

        if (collState->field_4.field_4 && (temp_a0->field_6_5 == 1 || temp_a0->groundType == GroundType_12))
        {
            collState->field_CC.field_12.vy = Q12(-1.0f);
            collState->field_CC.field_18.vy = Q12(-1.0f);
        }
    }

    // TODO: Use `Math_SetSVectorFastSum` here?
    temp_v0 = (temp_a3->field_0_0 & 0xFFFF) + (temp_a3->field_2_0 << 16);
    gte_ldR11R12(temp_v0);
    gte_ldR13R21(temp_v0);
    temp_v0 = (u16)collState->field_4.offset_C.vx + (collState->field_4.offset_C.vz << 16);
    gte_ldvxy0(temp_v0);
    gte_gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&collState->field_CC.field_20.field_14);
    temp_v0 = ((collState->field_98.vec_0.vx - collState->field_CC.field_12.vx) & 0xFFFF) + ((collState->field_98.vec_0.vz - collState->field_CC.field_12.vz) << 16);
    gte_ldvxy0(temp_v0);
    gte_gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&collState->field_CC.field_20.field_0);

    temp_s0                            = collState->field_CC.field_20.field_0.vx;
    temp_a0_5                          = collState->field_CC.field_20.field_0.vz;
    collState->field_CC.field_20.field_4.vx = collState->field_CC.field_20.field_14.vx + temp_s0;
    collState->field_CC.field_20.field_4.vz = collState->field_CC.field_20.field_14.vz + temp_a0_5;

    if (temp_s0 < 0)
    {
        collState->field_CC.field_20.field_8  = 2;
        collState->field_CC.field_20.field_C  = SquareRoot0(SQUARE(temp_s0) + SQUARE(temp_a0_5));
        collState->field_CC.field_20.field_10 = -temp_s0;
    }
    else if (collState->field_CC.field_6.vz < temp_s0)
    {
        collState->field_CC.field_20.field_8  = 2;
        collState->field_CC.field_20.field_C  = SquareRoot0(SQUARE(temp_s0 - collState->field_CC.field_6.vz) + SQUARE(temp_a0_5));
        collState->field_CC.field_20.field_10 = temp_s0 - collState->field_CC.field_6.vz;
    }
    else
    {
        if (temp_a0_5 < 0)
        {
            collState->field_CC.field_20.field_C = -temp_a0_5;
        }
        else
        {
            collState->field_CC.field_20.field_C = temp_a0_5;
        }

        collState->field_CC.field_20.field_8 = 1;
    }

    return true;
}

void func_8006B6E8(s_CollisionState* collState, s_IpdCollisionData_20* arg1) // 0x8006B6E8
{
    s32                 idx;
    s32                 temp_s1;
    s32                 temp_s2;
    s32                 temp_s3;
    s32                 temp_s4;
    s_CollisionState_A8* temp_s0;

    temp_s1 = collState->field_CC.field_C.s_field_0.field_0;
    temp_s2 = collState->field_CC.field_C.s_field_0.field_1;
    temp_s3 = collState->field_CC.field_10;
    temp_s4 = collState->field_CC.field_11;

    if (temp_s1 == 0xFF)
    {
        if (temp_s2 == 0xFF)
        {
            return;
        }

        idx = collState->field_CC.field_F;
    }
    else
    {
        idx = collState->field_CC.field_E;
    }

    temp_s0 = &collState->field_A0.s_0.field_8[idx];
    if (!func_8006B7E0(temp_s0, &collState->field_CC.field_20))
    {
        return;
    }

    temp_s0->field_0 = collState->field_CC.field_20.field_8;
    temp_s0->field_4 = collState->field_CC.field_20.field_C;
    temp_s0->field_2 = collState->field_CC.field_20.field_10;

    if (collState->field_CC.field_20.field_0.vz >= 0)
    {
        if (temp_s3 == 1)
        {
            temp_s0->field_1 = NO_VALUE;
        }
        else
        {
            temp_s0->field_1 = temp_s1;
        }
    }
    else
    {
        if (temp_s4 == 1)
        {
            temp_s0->field_1 = NO_VALUE;
        }
        else
        {
            temp_s0->field_1 = temp_s2;
        }
    }
}

bool func_8006B7E0(s_CollisionState_A8* arg0, s_CollisionState_CC_20* arg1) // 0x8006B7E0
{
if (arg0->field_0 == 0)
    {
        return true;
    }

    switch (arg1->field_8)
    {
        case 0:
            return false;

        case 1:
            switch (arg0->field_0)
            {
                case 1:
                    if (arg1->field_C < arg0->field_4)
                    {
                        return true;
                    }
                    break;

                case 2:
                    if (arg1->field_C < (arg0->field_4 + 6))
                    {
                        return true;
                    }
                    break;
            }
            break;

        case 2:
            switch (arg0->field_0)
            {
                case 1:
                    if (arg1->field_C < arg0->field_4 - 6)
                    {
                        return true;
                    }
                    break;

                case 2:
                    if (arg1->field_C < (arg0->field_4 - 6))
                    {
                        return true;
                    }

                    if (arg1->field_C < (arg0->field_4 + 6) && arg1->field_10 < arg0->field_2)
                    {
                        return true;
                    }
                    break;
            }
    }

    return false;
}

void func_8006B8F8(s_CollisionState_CC* arg0) // 0x8006B8F8
{
    s_CollisionState_CC_20* ptr;
    s32                    temp_a1;
    s32                    temp_a2;
    s32                    temp_a3;

    temp_a3                    = (u16)arg0->field_12.vx;
    temp_a1                    = (u16)arg0->field_18.vx;
    temp_a2                    = (u16)arg0->field_18.vz;
    arg0->field_18.vx          = temp_a3;
    temp_a3                    = (u16)arg0->field_12.vy;
    arg0->field_12.vy          = arg0->field_18.vy;
    arg0->field_12.vx          = temp_a1;
    arg0->field_6.vx           = -arg0->field_6.vx;
    arg0->field_18.vy          = temp_a3;
    arg0->field_6.vy           = -arg0->field_6.vy;
    temp_a3                    = (u16)arg0->field_12.vz;
    arg0->field_18.vz          = temp_a3;
    temp_a3                    = arg0->field_C.s_field_0.field_0;
    arg0->field_20.field_14.vx = -arg0->field_20.field_14.vx;

    arg0->field_12.vz               = temp_a2;
    arg0->field_C.s_field_0.field_0 = arg0->field_C.s_field_0.field_1;

    ptr = &arg0->field_20;

    arg0->field_C.s_field_0.field_1 = temp_a3;
    temp_a3                         = arg0->field_E;
    arg0->field_20.field_14.vz      = -arg0->field_20.field_14.vz;
    arg0->field_E                   = arg0->field_F;
    arg0->field_F                   = temp_a3;

    ptr->field_0.vz = -ptr->field_0.vz;
    ptr->field_0.vx = (arg0->field_6.vz - ptr->field_0.vx);
    ptr->field_4.vz = -ptr->field_4.vz;
    ptr->field_4.vx = (arg0->field_6.vz - ptr->field_4.vx);
}

void func_8006B9C8(s_CollisionState* collState) // 0x8006B9C8
{
    s32 field_28;

    if (collState->field_CC.field_C.s_field_0.field_1 == 0xFF && collState->field_CC.field_20.field_0.vz < 0 &&
        (collState->field_4.field_2C >= collState->field_CC.field_12.vy || collState->field_4.field_2C >= collState->field_CC.field_18.vy))
    {
        if (collState->field_0_9 && collState->field_CC.field_20.field_C < collState->field_4.field_28)
        {
            func_8006BB50(collState, 0);
            return;
        }

        field_28 = collState->field_4.field_28;
        if (collState->field_0_9 && collState->field_CC.field_20.field_C < (field_28 + 8))
        {
            func_8006BB50(collState, 1);
        }

        if (collState->field_0_8)
        {
            if (!collState->field_44.field_0.field_0 &&
                (-field_28 < collState->field_CC.field_20.field_0.vz || -field_28 < collState->field_CC.field_20.field_4.vz) &&
                (-field_28 < collState->field_CC.field_20.field_0.vx || -field_28 < collState->field_CC.field_20.field_4.vx) &&
                (collState->field_CC.field_20.field_0.vx < (field_28 + collState->field_CC.field_6.vz) || collState->field_CC.field_20.field_4.vx < (field_28 + collState->field_CC.field_6.vz)))
            {
                func_8006BE40(collState);
            }
        }
    }
}

void func_8006BB50(s_CollisionState* collState, s32 arg1) // 0x8006BB50
{
    q19_12 deltaX;
    q19_12 deltaZ;
    s16    temp2;

    if (func_8006BC34(collState) < 0)
    {
        return;
    }

    if (collState->field_CC.field_20.field_0.vx < 0)
    {
        deltaX = collState->field_98.vec_0.vx - collState->field_CC.field_12.vx;
        deltaZ = collState->field_98.vec_0.vz - collState->field_CC.field_12.vz;
    }
    else if (collState->field_CC.field_6.vz < collState->field_CC.field_20.field_0.vx)
    {
        deltaX = collState->field_98.vec_0.vx - collState->field_CC.field_18.vx;
        deltaZ = collState->field_98.vec_0.vz - collState->field_CC.field_18.vz;
    }
    else
    {
        deltaX = collState->field_CC.field_6.vy;
        deltaZ = -collState->field_CC.field_6.vx;
    }

    temp2 = collState->field_4.field_28 - collState->field_CC.field_20.field_C;
    func_8006BCC4(&collState->field_44, (u8*)collState->field_CC.ipdCollisionData_0 + (collState->field_CC.field_4 + 52), arg1, deltaX, deltaZ, temp2);
}

s32 func_8006BC34(s_CollisionState* collState)
{
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_v0;
    s16 temp_v1;
    u16 temp_a1;
    u16 var_v0;

    temp_v1 = collState->field_CC.field_20.field_0.vx;
    if (temp_v1 < 0)
    {
        var_v0 = collState->field_CC.field_12.vy;
    }
    else
    {
        temp_a2 = collState->field_CC.field_6.vz;
        if (temp_a2 < temp_v1)
        {
            var_v0 = collState->field_CC.field_18.vy;
        }
        else
        {
            temp_a3 = collState->field_CC.field_12.vy;
            temp_v0 = collState->field_CC.field_18.vy;
            temp_a1 = collState->field_CC.field_12.vy;

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

    return collState->field_4.field_2C - (s16)var_v0;
}

void func_8006BCC4(s_CollisionState_44* arg0, s8* arg1, u32 arg2, q3_12 deltaX, q3_12 deltaZ, s16 arg5) // 0x8006BCC4
{
    q7_8 rotX;
    q7_8 rotY;

    rotX = Q12_FRACT(ratan2(deltaZ, deltaX) - Q12_ANGLE(89.0f));
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

void func_8006BDDC(s_CollisionState_44_0* arg0, q3_12 rotX, q3_12 rotY) // 0x8006BDDC
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
    s32 temp_a3;
    s32 var_a2;
    s32 var_a1;
    u32 var_v1;
    s32 temp;

    var_a1  = 0;
    temp_a3 = -collState->field_4.field_28;
    var_a2  = 0;

    if (collState->field_CC.field_20.field_0.vz >= temp_a3)
    {
        if (collState->field_CC.field_20.field_0.vx >= 0)
        {
            if (collState->field_CC.field_6.vz >= collState->field_CC.field_20.field_0.vx)
            {
                var_a2 = collState->field_CC.field_20.field_0.vx;
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
        if (collState->field_CC.field_20.field_14.vz == 0)
        {
            if ((collState->field_CC.field_20.field_0.vx > 0) && (collState->field_CC.field_20.field_0.vx < collState->field_CC.field_6.vz))
            {
                var_a1 = 0;
                var_a2 = collState->field_CC.field_20.field_0.vx;
            }
        }
        else
        {
            var_a1 = FP_TO(temp_a3 - collState->field_CC.field_20.field_0.vz, Q12_SHIFT) / collState->field_CC.field_20.field_14.vz;
            temp   = collState->field_CC.field_20.field_14.vx * var_a1;
            temp   = FP_FROM(temp, Q12_SHIFT);
            var_a2 = temp + collState->field_CC.field_20.field_0.vx;
        }

        if (var_a2 < 0)
        {
            var_v1 = 0;
        }
        else if (collState->field_CC.field_6.vz < var_a2)
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
            func_8006BF88(collState, &collState->field_CC.field_12);
            break;

        case 1:
            func_8006BF88(collState, &collState->field_CC.field_18);
            break;

        case 2:
            func_8006C0C8(collState, var_a1, var_a2);
            break;
    }
}

void func_8006BF88(s_CollisionState* state, SVECTOR3* arg1) // 0x8006BF88
{
    s16 temp_v0;
    s32 temp2;
    s32 temp3;

    temp_v0 = func_8006C248(*(s32*)&state->field_4.direction_14, state->field_4.distance_8,
                            arg1->vx - state->field_98.vec_0.vx,
                            arg1->vz - state->field_98.vec_0.vz,
                            state->field_4.field_28);
    if (temp_v0 != -1 && func_8006C1B8(2, temp_v0, state) && state->field_4.field_2C > arg1->vy)
    {
        state->field_38 = temp_v0;
        state->field_34 = 2;
        temp2          = state->field_98.vec_0.vx + Q12_MULT(state->field_4.offset_C.vx, temp_v0);
        state->field_3A = (state->field_4.distance_8 * temp_v0) >> 8;
        state->field_40 = (u8*)state->field_CC.ipdCollisionData_0 + (state->field_CC.field_4 + 52);

        state->field_3C = temp2 - arg1->vx;
        temp3          = state->field_98.vec_0.vz + Q12_MULT(state->field_4.offset_C.vz, temp_v0);
        state->field_3E = temp3 - arg1->vz;
    }
}

void func_8006C0C8(s_CollisionState* collState, s16 arg1, s16 arg2) // 0x8006C0C8
{
    s32 temp;

    if (!func_8006C1B8(1, arg1, collState) || collState->field_CC.field_20.field_14.vz < 0)
    {
        return;
    }

    temp = ((collState->field_CC.field_18.vy - collState->field_CC.field_12.vy) * arg2) / collState->field_CC.field_6.vz;

    if (temp + collState->field_CC.field_12.vy < collState->field_4.field_2C)
    {
        collState->field_40 = (u8*)collState->field_CC.ipdCollisionData_0 + (collState->field_CC.field_4 + 52);
        collState->field_34 = 1;
        collState->field_38 = arg1;
        collState->field_3A = (collState->field_4.distance_8 * arg1) >> 8;
        collState->field_3C = collState->field_CC.field_6.vy;
        collState->field_3E = -collState->field_CC.field_6.vx;
    }
}

bool func_8006C1B8(u32 arg0, s16 arg1, s_CollisionState* collState) // 0x8006C1B8
{
    s32 var;

    var = (collState->field_4.distance_8 * arg1) >> 8;
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

            var += 96;
            break;

        case 1:
            if (collState->field_34 != arg0)
            {
                if (collState->field_34 != 0)
                {
                    if (collState->field_34 == 2)
                    {
                        var -= 96;
                    }

                    break;
                }

                return true;
            }
            break;
    }

    return var < collState->field_3A;
}

q3_12 func_8006C248(s32 packedDir, s16 arg1, q3_12 deltaX, q3_12 deltaZ, s16 arg4) // 0x8006C248
{
    DVECTOR sp10;
    s16     temp_v0;
    s16     dist;
    q3_12   alpha;

    gte_ldR11R12(packedDir);
    gte_ldR13R21(packedDir);
    gte_ldvxy0((deltaX & 0xFFFF) + (deltaZ << 16));
    gte_gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&sp10.vx);

    if (sp10.vx < 0)
    {
        dist = SquareRoot0(SQUARE(sp10.vx) + SQUARE(sp10.vy));
    }
    else if (arg1 < sp10.vx)
    {
        temp_v0 = sp10.vx - arg1;
        dist  = SquareRoot0(SQUARE(temp_v0) + SQUARE(sp10.vy));
    }
    else
    {
        dist = ABS(sp10.vy);
    }

    if (arg1 == 0)
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

    alpha = FP_TO(sp10.vx - SquareRoot0(SQUARE(arg4) - SQUARE(sp10.vy)), Q12_SHIFT) / arg1;
    alpha = CLAMP(alpha, Q12(0.0f), Q12(1.0f));

    return alpha;
}

bool func_8006C3D4(s_CollisionState* collState, s_IpdCollisionData* collData, s32 idx) // 0x8006C3D4
{
    s_IpdCollisionData_18* temp_a1;

    collState->field_CC.ipdCollisionData_0 = collData;
    collState->field_CC.field_4 = idx;
    temp_a1 = &collData->ptr_18[idx - collData->field_8_16];

    if (!((collState->flags_2 >> temp_a1->field_0_8) & (1 << 0)))
    {
        return false;
    }

    collState->field_CC.field_5         = temp_a1->field_0_5;
    collState->field_CC.field_6.vx      = temp_a1->vec_2.vx;
    collState->field_CC.field_6.vy      = temp_a1->vec_2.vy;
    collState->field_CC.field_6.vz      = temp_a1->vec_2.vz;
    collState->field_CC.field_C.field_0 = temp_a1->field_8;
    return true;
}

void func_8006C45C(s_CollisionState* collState) // 0x8006C45C
{
    q3_12  distMax;
    q3_12  dist;
    s16    var_s2;
    s32    bound;
    q19_12 deltaX;
    q19_12 deltaZ;
    s32    temp_v1;
    s32    temp;
    s32    temp2;

    distMax = collState->field_4.field_28 + collState->field_CC.field_C.field_0;
    bound   = distMax + 8;
    temp_v1 = collState->field_CC.field_6.vx - bound;

    if (collState->field_98.vec_0.vx < temp_v1 &&
        collState->field_9C.vec_0.vx < temp_v1)
    {
        return;
    }

    if ((collState->field_CC.field_6.vx + bound) < collState->field_98.vec_0.vx &&
        (collState->field_CC.field_6.vx + bound) < collState->field_9C.vec_0.vx)
    {
        return;
    }

    if (collState->field_98.vec_0.vz < (collState->field_CC.field_6.vz - bound) &&
        collState->field_9C.vec_0.vz < (collState->field_CC.field_6.vz - bound))
    {
        return;
    }

    if ((collState->field_CC.field_6.vz + bound) < collState->field_98.vec_0.vz &&
        (collState->field_CC.field_6.vz + bound) < collState->field_9C.vec_0.vz)
    {
        return;
    }

    deltaX = collState->field_98.vec_0.vx - collState->field_CC.field_6.vx;
    deltaZ = collState->field_98.vec_0.vz - collState->field_CC.field_6.vz;
    dist   = SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ));

    if (dist < collState->field_CC.field_C.field_0 && collState->field_CC.field_5 != 1 &&
        (collState->field_C8 == 0xFF || collState->field_CC.field_6.vy < collState->groundHeight))
    {
        collState->field_C8 = collState->field_CC.field_4;
        collState->groundHeight = collState->field_CC.field_6.vy;
    }

    if (!collState->field_0_8 && !collState->field_0_9 || dist < collState->field_CC.field_C.field_0)
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

    if (!collState->field_0_8 || collState->field_44.field_0.field_0)
    {
        return;
    }

    var_s2 = func_8006C248(*(s32*)&collState->field_4.direction_14, collState->field_4.distance_8,
                           collState->field_CC.field_6.vx - collState->field_98.vec_0.vx,
                           collState->field_CC.field_6.vz - collState->field_98.vec_0.vz,
                           distMax);

    if (var_s2 == -1)
    {
        return;
    }

    if (var_s2 < 0)
    {
        var_s2 = 0;
    }

    if (func_8006C1B8(1, var_s2, collState) && collState->field_4.field_2C >= collState->field_CC.field_6.vy)
    {
        collState->field_38 = var_s2;
        collState->field_34 = 1;
        temp           = collState->field_98.vec_0.vx + Q12_MULT(collState->field_4.offset_C.vx, var_s2);
        collState->field_3A = (collState->field_4.distance_8 * var_s2) >> 8;
        collState->field_40 = (u8*)collState->field_CC.ipdCollisionData_0 + (collState->field_CC.field_4 + 52);
        collState->field_3C = temp - collState->field_CC.field_6.vx;
        temp2          = collState->field_98.vec_0.vz + Q12_MULT(collState->field_4.offset_C.vz, var_s2);
        collState->field_3E = temp2 - collState->field_CC.field_6.vz;
    }
}

void func_8006C794(s_CollisionState* collState, s32 arg1, s32 dist) // 0x8006C794
{
    if (collState->field_4.field_2C >= (collState->field_CC.field_6.vy + (dist - collState->field_CC.field_C.field_0)))
    {
        func_8006BCC4(&collState->field_44,
                      (u8*)collState->field_CC.ipdCollisionData_0 + (collState->field_CC.field_4 + 52),
                      arg1,
                      collState->field_98.vec_0.vx - collState->field_CC.field_6.vx,
                      collState->field_98.vec_0.vz - collState->field_CC.field_6.vz,
                      (collState->field_4.field_28 + collState->field_CC.field_C.field_0) - dist);
    }
}

void func_8006C838(s_CollisionState* collState, s_IpdCollisionData* collData) // 0x8006C838
{
    s32                    var_a0;
    s_CollisionState_A8*   curUnk;
    s_IpdCollisionData_10* temp_a1;
    s_IpdCollisionData_18* temp_a0;

    if (!collState->field_A0.s_0.field_4)
    {
        return;
    }

    if (collState->field_C8 != 0xFF)
    {
        if (collState->groundHeight < collState->field_7C)
        {
            temp_a0        = &collData->ptr_18[collState->field_C8 - collData->field_8_16];
            collState->field_7C = collState->groundHeight;
            collState->field_80 = collState->field_98.vec_0.vx + collData->positionX;
            collState->field_84 = collState->field_98.vec_0.vz + collData->positionZ;
            collState->field_88 = 0;
            collState->field_8C = 0;
            collState->field_90 = temp_a0->field_0_5;
            collState->groundType = temp_a0->groundType;
        }
    }

    for (curUnk = &collState->field_A0.s_0.field_8[0]; curUnk < &collState->field_A0.s_0.field_8[4]; curUnk++)
    {
        if (curUnk->field_1 != 0xFF)
        {
            temp_a1 = &collData->ptr_10[curUnk->field_1];

            var_a0 = temp_a1->field_2;

            if (temp_a1->field_8 != 0)
            {
                var_a0 += Q12_MULT(temp_a1->field_8, collState->field_98.vec_0.vx - temp_a1->field_0);
            }

            if (temp_a1->field_A != 0)
            {
                var_a0 += Q12_MULT(temp_a1->field_A, collState->field_98.vec_0.vz - temp_a1->field_4);
            }

            if (var_a0 < collState->field_7C)
            {
                collState->field_7C = var_a0;
                collState->field_80 = collState->field_98.vec_0.vx + collData->positionX;
                collState->field_84 = collState->field_98.vec_0.vz + collData->positionZ;
                collState->field_88 = temp_a1->field_8;
                collState->field_8C = temp_a1->field_A;
                collState->field_90 = temp_a1->field_6_5;
                collState->groundType = temp_a1->groundType;
            }
        }
    }
}

void func_8006CA18(s_CollisionState* collState, s_IpdCollisionData* collData, s_func_8006CA18* arg2) // 0x8006CA18
{
    s32                    startIdx;
    s32                    endIdx;
    q23_8                  var_a2;
    u8*                    curUnk;
    s_IpdCollisionData_10* ptr;

    startIdx = arg2->field_2;
    endIdx   = arg2->field_6;

    if (startIdx == endIdx)
    {
        return;
    }

    for (curUnk = &collData->ptr_2C[startIdx]; curUnk < &collData->ptr_2C[endIdx]; curUnk++)
    {
        ptr = &collData->ptr_10[*curUnk];

        if (((collState->flags_2 >> ptr->field_6_11) & (1 << 0)) && ptr->field_6_5 != 1)
        {
            var_a2 = ptr->field_2;

            if (ptr->field_8 != 0)
            {
                var_a2 += Q12_MULT(ptr->field_8, collState->field_98.vec_0.vx - ptr->field_0);
            }

            if (ptr->field_A != 0)
            {
                var_a2 += Q12_MULT(ptr->field_A, collState->field_98.vec_0.vz - ptr->field_4);
            }

            if (var_a2 < collState->field_7C)
            {
                collState->field_7C = var_a2;
                collState->field_80 = collState->field_98.vec_0.vx + collData->positionX;
                collState->field_84 = collState->field_98.vec_0.vz + collData->positionZ;
                collState->field_88 = ptr->field_8;
                collState->field_8C = ptr->field_A;
                collState->field_90 = ptr->field_6_5;
                collState->groundType = ptr->groundType;
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

    groundHeight = Ipd_GroundHeightGet(collState->field_4.newPositionX_20, collState->field_4.newPositionZ_24, collState);
    if ((collState->field_4.field_2C + collState->field_4.offset_C.vy) < groundHeight ||
        groundHeight == collState->field_7C)
    {
        return Q12(1.0f);
    }

    return Q12_DIV(collState->field_4.distance_8, SquareRoot0(SQUARE(collState->field_4.distance_8) +
                                                              SQUARE(groundHeight - collState->field_4.field_2C)));
}

q23_8 Ipd_GroundHeightGet(q23_8 posX, q23_8 posZ, const s_CollisionState* collState) // 0x8006CC44
{
    if (collState->groundType != GroundType_12)
    {
        return Q12_MULT(collState->field_88, posX - collState->field_80) +
               Q12_MULT(collState->field_8C, posZ - collState->field_84) +
               collState->field_7C;
    }

    return Q8(8.0f);
}

void func_8006CC9C(s_CollisionState* state) // 0x8006CC9C
{
    q19_12 deltaX;
    q19_12 deltaZ;
    s32    temp_v0;
    s32    temp_s4;
    s32    temp;
    s32    temp2;
    s32    temp3;
    s32    temp4;
    s32    temp5;

    if (state->field_A0.s_1.collisionState < CharaCollisionState_2 ||
        *state->field_A0.s_1.field_8 != 0)
    {
        return;
    }

    if (state->field_98.field_0 + (state->field_A0.s_1.field_4 + state->field_4.distance_8) < state->field_4.positionX_18 ||
        state->field_4.newPositionX_20 < state->field_98.field_0 - (state->field_A0.s_1.field_4 + state->field_4.distance_8))
    {
        return;
    }

    if (state->field_9C.field_0 + (state->field_A0.s_1.field_4 + state->field_4.distance_8) < state->field_4.positionZ_1C ||
        state->field_4.newPositionZ_24 < state->field_9C.field_0 - (state->field_A0.s_1.field_4 + state->field_4.distance_8) ||
        state->field_4.field_2A > state->field_A0.s_1.field_2)
    {
        return;
    }

    deltaX = (state->field_4.positionX_18 - state->field_98.field_0);

    if (state->field_4.field_2C < state->field_A0.s_1.field_0)
    {
        return;
    }

    deltaZ = state->field_4.positionZ_1C - state->field_9C.field_0;
    temp_s4 = SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ));

    temp_v0 = func_8006C248(*(s32*)&state->field_4.direction_14, state->field_4.distance_8,
                            state->field_98.field_0 - state->field_4.positionX_18,
                            state->field_9C.field_0 - state->field_4.positionZ_1C,
                            state->field_A0.s_1.field_4);
    if (temp_v0 == NO_VALUE)
    {
        return;
    }

    if (temp_v0 == 0)
    {
        if (state->field_0_9)
        {
            temp3 = state->field_A0.s_1.field_4 - temp_s4;
            func_8006BCC4(&state->field_44, state->field_A0.s_1.field_8, 2, deltaX, deltaZ, temp3);
        }
    }
    else if (state->field_0_8 && state->field_44.field_0.field_0 == 0 && func_8006C1B8(1, temp_v0, state))
    {
        temp2 = (state->field_4.positionZ_1C - state->field_9C.field_0);
        temp5 = Q12_MULT(temp_v0, state->field_4.offset_C.vz);

        state->field_40 = state->field_A0.s_1.field_8;
        state->field_38 = temp_v0;

        state->field_34 = 1;

        temp  = (state->field_4.positionX_18 - state->field_98.field_0);
        temp4 = Q12_MULT(temp_v0, state->field_4.offset_C.vx);

        state->field_3A = (state->field_4.distance_8 * temp_v0) >> 8; // TODO: Conversion to Q4?
        state->field_3C = temp + temp4;
        state->field_3E = temp2 + temp5;
    }
}

void func_8006CF18(s_CollisionState* state, s_func_8006CF18* arg1, s32 idx) // 0x8006CF18
{
    s32              var_a1;
    s_func_8006CF18* curArg1;

    for (curArg1 = arg1; curArg1 < &arg1[idx]; curArg1++)
    {
        var_a1 = Q12_TO_Q8(curArg1->field_10) + state->field_4.field_28;
        if (curArg1->collisionState < (u32)state->field_4.collisionState)
        {
            var_a1 -= 15;
        }

        state->field_98.field_0 = Q12_TO_Q8(curArg1->position.vx);
        state->field_9C.field_0 = Q12_TO_Q8(curArg1->position.vz);

        state->field_A0.s_1.field_0 = Q12_TO_Q8(curArg1->field_E + curArg1->position.vy);
        state->field_A0.s_1.field_2 = Q12_TO_Q8(curArg1->field_C + curArg1->position.vy);
        state->field_A0.s_1.field_4 = var_a1;
        state->field_A0.s_1.collisionState = curArg1->collisionState;
        state->field_A0.s_1.field_8 = &curArg1->field_13;

        if (state->field_0_0 == 0)
        {
            curArg1->field_13 = 0;
        }

        func_8006CC9C(state);
    }
}

void func_8006D01C(VECTOR3* arg0, VECTOR3* offset, q3_12 offsetAlpha, s_CollisionState* collState) // 0x8006D01C
{
    VECTOR3 sp10;
    s32     temp_s0;
    s32     temp_s1;
    s32     temp_a0;
    s32     temp_v0;

    sp10.vx = Q12_MULT(offset->vx, offsetAlpha);
    sp10.vz = Q12_MULT(offset->vz, offsetAlpha);

    if (collState->field_44.field_0.field_0 || collState->field_44.field_30.field_0)
    {
        arg0->vx = Q12(0.0f);
        arg0->vz = Q12(0.0f);
        *offset    = sp10;
        func_8006D2B4(offset, &collState->field_44);
        return;
    }

    if (!collState->field_34)
    {
        *arg0    = sp10;
        offset->vz = Q12(0.0f);
        offset->vx = Q12(0.0f);
        return;
    }

    if (offsetAlpha < collState->field_38)
    {
        collState->field_34 = 0;
        *arg0          = sp10;
        offset->vz       = Q12(0.0f);
        offset->vx       = Q12(0.0f);
        return;
    }

    arg0->vx = Q12_MULT(offset->vx, collState->field_38);
    arg0->vz = Q12_MULT(offset->vz, collState->field_38);
    offset->vx = sp10.vx - arg0->vx;
    offset->vz = sp10.vz - arg0->vz;

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
                Vw_ClampAngleRange(&rotY1, &rotX1, arg1->field_8.field_2.vx, arg1->field_8.field_2.vy);
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

                Vw_ClampAngleRange(&arg1->field_0.field_2.vx, &arg1->field_0.field_2.vy, arg1->field_30.field_2.vx, arg1->field_30.field_2.vy);

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
                Vw_ClampAngleRange(&arg1->field_0.field_2.vx, &arg1->field_0.field_2.vy, arg1->field_8.field_2.vx, arg1->field_8.field_2.vy);
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

void func_8006D600(VECTOR3* pos, q19_12 angle, q19_12 angleMin, q19_12 angleMax, s32 arg4) // 0x8006D600
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
    q19_12 var_v0_2;
    q19_12 angle1;

    normAngle    = Q12_FRACT(angle);
    normAngleMin = Q12_FRACT(angleMin);
    normAngleMax = Q12_FRACT(angleMax);

    if (arg4 > 0x100)
    {
        arg4 = 0x100;
    }

    x      = Q12_MULT(arg4, Math_Cos(normAngle));
    angle2 = normAngleMax;
    z      = Q12_MULT(arg4, Math_Sin(normAngle));
    deltaX = pos->vx - x;
    deltaZ = pos->vz - z;
    angle1  = Q12_FRACT(ratan2(deltaZ, deltaX));

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

        var_v0_2 = Q12_MULT(deltaX, cosAngle2) + Q12_MULT(deltaZ, sinAngle2);
        if (var_v0_2 < Q12(0.0f))
        {
            var_v0_2 = Q12(0.0f);
        }

        pos->vx = x + Q12_MULT(var_v0_2, cosAngle2);
        pos->vz = z + Q12_MULT(var_v0_2, sinAngle2);
    }
}

void func_8006D774(s_CollisionState* state, VECTOR3* arg1, VECTOR3* arg2) // 0x8006D774
{
    SVECTOR sp10; // Types assumed. `SVECTOR3` might also work but there are 8 bytes between `sp10` and `sp18` and `SVECTOR3` is only 6 bytes.
    SVECTOR sp18;

    sp10.vx = Q12_TO_Q8(arg1->vx);
    sp10.vy = Q12_TO_Q8(arg1->vz);
    sp18.vx = Q12_TO_Q8(arg2->vx);
    sp18.vy = Q12_TO_Q8(arg2->vz);

    state->field_34                  = 0;
    state->field_44.field_0.field_0  = 0;
    state->field_44.field_6          = 0;
    state->field_44.field_8.field_0  = 0;
    state->field_44.field_36         = 0;
    state->field_44.field_30.field_0 = 0;

    func_8006D7EC(&state->field_4, &sp10, &sp18);
}

void func_8006D7EC(s_func_8006ABC0* arg0, SVECTOR* arg1, SVECTOR* arg2) // 0x8006D7EC
{
    q3_12  headingAngle;
    q19_12 dist;
    s16    z;

    arg0->offset_C.vx = arg2->vx;

    z                 = arg2->vy;
    arg0->offset_C.vz = arg2->vy;
    dist              = SquareRoot0(SQUARE(arg0->offset_C.vx) + SQUARE(z));

    arg0->distance_8 = dist;

    if (dist != Q12(0.0f))
    {
        arg0->direction_14.vx = FP_TO(arg0->offset_C.vx, Q12_SHIFT) / dist;
        arg0->direction_14.vz = FP_TO(arg0->offset_C.vz, Q12_SHIFT) / arg0->distance_8;

        headingAngle          = ratan2(arg0->offset_C.vz, arg0->offset_C.vx);
        arg0->direction_14.vx = Math_Cos(headingAngle);
        arg0->direction_14.vz = Math_Sin(headingAngle);
    }
    else
    {
        arg0->direction_14.vx = Q12(1.0f);
        arg0->direction_14.vz = Q12(0.0f);
    }

    arg0->positionX_18    = arg0->positionX_18 + arg1->vx;
    arg0->positionZ_1C    = arg0->positionZ_1C + arg1->vy;
    arg0->newPositionX_20 = arg0->positionX_18 + arg0->offset_C.vx;
    arg0->newPositionZ_24 = arg0->positionZ_1C + arg0->offset_C.vz;
}

// ========================================
// COMBAT 2
// ========================================

bool Ray_TraceQuery(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* to) // 0x8006D90C
{
    s32         prevScratchAddr;
    s_RayState* state;
    VECTOR3     offset; // Q19.12

    offset.vx = to->vx - from->vx;
    offset.vy = to->vy - from->vy;
    offset.vz = to->vz - from->vz;

    trace->hasHit = false;

    if (Ray_TraceSetup((s_RayState*)PSX_SCRATCH, 0, 0, from, &offset, 0, 0, NULL, 0))
    {
        prevScratchAddr = SetSp((s32)PSX_SCRATCH_ADDR(984));

        state         = (s_RayState*)PSX_SCRATCH;
        trace->hasHit = Ray_TraceRun(trace, state);

        SetSp(prevScratchAddr);
    }

    if (!trace->hasHit)
    {
        Ray_MissSet(trace, from, &offset, state->rayDistance);
    }

    return trace->hasHit;
}

bool Ray_CharaTraceQuery(s_RayTrace* trace, VECTOR3* from, VECTOR3* offset, s_SubCharacter* excludedChara) // 0x8006DA08
{
    s32              collCharaCount;
    s32              prevScratch;
    s_RayState*      state;
    s_SubCharacter** collCharas;

    collCharas = Collision_CollidableCharasGet(&collCharaCount, excludedChara, false);

    trace->hasHit = false;
    if (Ray_TraceSetup((s_RayState*)PSX_SCRATCH, 0, 0, from, offset, 0, 0, collCharas, collCharaCount))
    {
        prevScratch   = SetSp((s32)PSX_SCRATCH_ADDR(0x3D8));

        state         = (s_RayState*)PSX_SCRATCH;
        trace->hasHit = Ray_TraceRun(trace, state);

        SetSp(prevScratch);
    }

    if (!trace->hasHit)
    {
        Ray_MissSet(trace, from, offset, state->rayDistance);
    }

    return trace->hasHit;
}

void Ray_MissSet(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* offset, q23_8 dist) // 0x8006DAE4
{
    trace->hasHit       = false;
    trace->groundType   = GroundType_Default;
    trace->target.vx    = from->vx + offset->vx;
    trace->target.vy    = from->vy + offset->vy;
    trace->target.vz    = from->vz + offset->vz;
    trace->character    = NULL;
    trace->hitDistance  = Q8_TO_Q12(dist);
    trace->groundHeight = Q12(1.875f); // @bug? Awkward value suggests `Q8(30.0f)` may have been typed by mistake.
    trace->field_1C     = Q12_ANGLE(0.0f);
}

bool Ray_LosHitCheck(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* offset, s_SubCharacter* excludedChara) // 0x8006DB3C
{
    s32              collCharaCount;
    s32              prevScratchAddr;
    s_RayState*      state;
    s_SubCharacter** collCharas;

    collCharas = Collision_CollidableCharasGet(&collCharaCount, excludedChara, true);
    trace->hasHit    = false;

    if (Ray_TraceSetup((s_RayState*)PSX_SCRATCH, 1, 0, from, offset, 0, 0, collCharas, collCharaCount))
    {
        prevScratchAddr = SetSp((s32)PSX_SCRATCH_ADDR(984));

        state         = (s_RayState*)PSX_SCRATCH;
        trace->hasHit = Ray_TraceRun(trace, state);

        SetSp(prevScratchAddr);
    }

    if (!trace->hasHit)
    {
        Ray_MissSet(trace, from, offset, state->rayDistance);
    }

    return trace->hasHit;
}

bool func_8006DC18(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* offset) // 0x8006DC18
{
    s32         prevScratchAddr;
    s_RayState* state;

    trace->hasHit = false;
    if (Ray_TraceSetup((s32)PSX_SCRATCH, 1, 76, from, offset, 0, 0, NULL, 0))
    {
        prevScratchAddr = SetSp((s32)PSX_SCRATCH_ADDR(0x3D8));

        state         = (s_RayState*)PSX_SCRATCH;
        trace->hasHit = Ray_TraceRun(trace, state);

        SetSp(prevScratchAddr);
    }

    if (!trace->hasHit)
    {
        Ray_MissSet(trace, from, offset, state->rayDistance);
    }

    return trace->hasHit;
}

bool Ray_TraceSetup(s_RayState* state, bool useCylinder, q7_8 arg2, const VECTOR3* from, const VECTOR3* offset, q19_12 arg5, q19_12 arg6,
                    s_SubCharacter** collCharas, s32 collCharaCount)
{
    if (offset->vx == Q12(0.0f) && offset->vz == Q12(0.0f))
    {
        return false;
    }

    state->field_0  = useCylinder;
    state->field_4  = D_800C4478.flags; // Struct could begin some point earlier.
    state->field_6  = arg2;
    state->field_8  = SHRT_MAX;
    state->field_20 = 0;

    state->from.vx = Q12_TO_Q8(from->vx);
    state->from.vy = Q12_TO_Q8(from->vy);
    state->from.vz = Q12_TO_Q8(from->vz);

    state->offset.vx = Q12_TO_Q8(offset->vx);
    state->offset.vy = Q12_TO_Q8(offset->vy);
    state->offset.vz = Q12_TO_Q8(offset->vz);

    state->field_3C = state->from.vx + state->offset.vx;

    state->field_4C = Q12_TO_Q8(arg5);
    state->field_4E = Q12_TO_Q8(arg6);

    state->field_40 = state->from.vy + state->offset.vy;
    state->field_44 = state->from.vz + state->offset.vz;

    state->rayDistance = SquareRoot0(SQUARE(state->offset.vx) + SQUARE(state->offset.vz));
    if (state->rayDistance == Q8(0.0f))
    {
        return false;
    }

    state->field_58 = (state->offset.vx << Q12_SHIFT) / state->rayDistance;
    state->field_5A = (state->offset.vz << Q12_SHIFT) / state->rayDistance;

    if (state->offset.vy < 0)
    {
        state->field_5E = state->from.vy + state->field_4E;
        state->field_60 = state->field_40 + state->field_4E;
    }
    else
    {
        state->field_60 = state->from.vy + state->field_4E;
        state->field_5E = state->field_40 + state->field_4E;
    }

    state->collCharas     = collCharas;
    state->collCharaCount = collCharaCount;

    return true;
}

bool Ray_TraceRun(s_RayTrace* trace, s_RayState* state) // 0x8006DEB0
{
    s32                  collDataIdx;
    s32                  temp_lo;
    s_IpdCollisionData*  collData;
    s_SubCharacter**     curCollChara;
    s_IpdCollisionData** collDataPtrs;
    s_IpdCollisionData** curCollData;
    s_RayState_8C*       curUnk;

    // Run through IPD collision data.
    collDataPtrs = Ipd_ActiveChunksCollisionDataGet(&collDataIdx);
    for (curCollData = collDataPtrs; curCollData < &collDataPtrs[collDataIdx]; curCollData++)
    {
        collData = *curCollData;

        if (collData->field_8_8 || collData->field_8_16 || collData->field_8_24)
        {
            func_8006E0AC(state, collData);
            func_80069994(collData);

            for (curUnk = &state->field_8C; curUnk < &state->field_8C[state->field_88]; curUnk++)
            {
                temp_lo = curUnk->field_2 * state->field_7C;
                func_8006E53C(state, &collData->ptr_20[temp_lo + curUnk->field_0], collData);
            }
        }
    }

    // Run through collidable characters.
    for (curCollChara = state->collCharas;
         curCollChara < &state->collCharas[state->collCharaCount];
         curCollChara++)
    {
        func_8006EE0C(&state->field_6C, state->field_0, *curCollChara);
        func_8006EEB8(state, *curCollChara);
    }

    if (state->field_8 != SHRT_MAX)
    {
        trace->target.vx    = Q8_TO_Q12(state->field_C);
        trace->target.vy    = Q8_TO_Q12(state->field_10);
        trace->target.vz    = Q8_TO_Q12(state->field_14);
        trace->character    = state->field_20;
        trace->hitDistance  = Q8_TO_Q12(state->field_8);
        trace->groundHeight = Q8_TO_Q12(state->groundHeight);
        trace->field_1C     = ratan2(state->field_24, state->field_26);
        trace->groundType   = state->groundType;
        return true;
    }

    return false;
}

void func_8006E0AC(s_RayState* state, s_IpdCollisionData* arg1) // 0x8006E0AC
{
    // `state` type might be wrong.
    state->field_6C.field_0 = arg1->positionX;
    state->field_6C.field_4 = arg1->positionZ;
    state->field_6C.groundHeight = state->from.vx - state->field_6C.field_0;
    state->field_6C.field_A = state->from.vz - state->field_6C.field_4;
    state->field_6C.field_C = state->field_6C.groundHeight + state->offset.vx;
    state->field_6C.field_E = state->field_6C.field_A + state->offset.vz;
    state->field_7C = arg1->field_1E;
    state->field_80 = arg1->field_1F;
    state->field_84 = arg1->field_1C;

    func_8006E150(&state->field_6C, ((DVECTOR*)&state->offset)[0], ((DVECTOR*)&state->offset)[1]);
}

void func_8006E150(s_func_8006E490* arg0, DVECTOR arg1, DVECTOR arg2) // 0x8006E150
{
    DVECTOR subroutine_arg4;
    VECTOR  sp18;
    VECTOR  pos;
    s16     temp_lo;
    s16     temp_lo_2;
    s32     temp_a0_3;
    s32     temp_lo_4;
    s32     temp_t0;
    s32     temp_t1;
    s32     var_a2;
    s32     var_a3;
    u32     flags;

    flags = OrientationFlags_None;
    arg0->field_1C = Q8(0.0f);

    if (arg0->field_8.vx < 0 && arg0->field_C < 0 &&
        arg0->field_8.vy < 0 && arg0->field_E < 0)
    {
        return;
    }

    temp_lo   = arg0->field_10 * arg0->field_18;
    temp_lo_2 = arg0->field_14 * arg0->field_18;

    if (arg0->field_8.vx >= temp_lo && arg0->field_C >= temp_lo &&
        arg0->field_8.vy >= temp_lo_2 && arg0->field_E >= temp_lo_2)
    {
        return;
    }

    subroutine_arg4 = arg0->field_8;

    sp18.vz  = 0;
    sp18.pad = 0;

    sp18.vx = Q12(arg0->field_10);
    sp18.vy = Q12(arg0->field_14);

    if (arg1.vx < 0)
    {
        flags             |= OrientationFlags_InvertX;
        subroutine_arg4.vx = -subroutine_arg4.vx;

        arg1.vx = -arg1.vx;
        sp18.vz = -sp18.vx;
        sp18.vx = 0;
    }

    if (arg2.vx < 0)
    {
        flags             |= OrientationFlags_InvertZ;
        subroutine_arg4.vy = -subroutine_arg4.vy;
        arg2.vx            = -arg2.vx;
        sp18.pad           = -sp18.vy;
        sp18.vy            = 0;
    }

    if (arg1.vx < arg2.vx)
    {
        flags |= OrientationFlags_SwapXz;

        temp_a0_3          = subroutine_arg4.vx;
        subroutine_arg4.vx = subroutine_arg4.vy;
        subroutine_arg4.vy = temp_a0_3;

        temp_a0_3 = arg1.vx;
        arg1.vx   = arg2.vx;
        arg2.vx   = temp_a0_3;

        temp_a0_3 = sp18.vz;
        sp18.vz   = sp18.pad;
        sp18.pad  = temp_a0_3;
        temp_a0_3 = sp18.vx;
        sp18.vx   = sp18.vy;
        sp18.vy   = temp_a0_3;
    }

    if (subroutine_arg4.vx + arg1.vx < Q12_MULT(arg0->field_18, sp18.vx))
    {
        sp18.vx = Q12(subroutine_arg4.vx + arg1.vx) / arg0->field_18;
    }

    pos.vx = Q12(subroutine_arg4.vx) / arg0->field_18;
    pos.vy = Q12(subroutine_arg4.vy) / arg0->field_18;
    pos.vz = Q12(1.0f);

    pos.pad  = Q12(arg2.vx) / arg1.vx;
    temp_lo_4 = Q12_MULT(pos.pad, Q12_FRACT(pos.vx));

    if (FP_FROM(sp18.vx, Q12_SHIFT) < FP_FROM(pos.vx, Q12_SHIFT))
    {
        return;
    }

    do
    {
        func_8006E490(arg0, flags, pos.vx, pos.vy);

        temp_t0 = pos.vy;
        temp_t1 = pos.vx;
        var_a3  = temp_t0 + pos.pad;
        var_a2  = temp_t1 + Q12(1.0f);

        pos.vy = var_a3;
        pos.vx = var_a2;

        if (FP_FROM(temp_t0, Q12_SHIFT) < FP_FROM(var_a3, Q12_SHIFT))
        {
            if (Q12_FRACT(var_a3) < temp_lo_4)
            {
                func_8006E490(arg0, flags, var_a2, temp_t0);
            }
            else
            {
                func_8006E490(arg0, flags, temp_t1, var_a3);
            }
        }
    }
    while (arg0->field_1C < Q8(0.08f) && FP_FROM(pos.vx, Q12_SHIFT) <= FP_FROM(sp18.vx, Q12_SHIFT));
}

void func_8006E490(s_func_8006E490* arg0, u32 flags, q19_12 posX, q19_12 posZ) // 0x8006E490
{
    q19_12 tempPosX;

    if (flags & OrientationFlags_SwapXz)
    {
        tempPosX = posX;
        posX     = posZ;
        posZ     = tempPosX;
    }

    if (flags & OrientationFlags_InvertZ)
    {
        posZ = -posZ;
    }

    if (flags & OrientationFlags_InvertX)
    {
        posX = -posX;
    }

    posX = FP_FROM(posX, Q12_SHIFT);
    posZ = FP_FROM(posZ, Q12_SHIFT);
    if (posX >= Q12(0.0f) && posX < arg0->field_10 &&
        posZ >= Q12(0.0f) && posZ < arg0->field_14)
    {
        arg0->field_20[arg0->field_1C].field_0 = posX;
        arg0->field_20[arg0->field_1C].field_2 = posZ;
        arg0->field_1C++;
    }
}

void func_8006E53C(s_RayState* state, s_IpdCollisionData_20* arg1, s_IpdCollisionData* ipdColl) // 0x8006E53C
{
    s32                    i;
    s32                    temp_v0;
    s32                    temp_v0_2;
    bool                   cond0;
    bool                   cond1;
    bool                   cond2;
    u8                     temp_a0;
    s32                    temp_a0_3;
    s32                    temp_a2;
    s32                    idx;
    s_IpdCollisionData_18* temp_a1_2;
    s_IpdCollisionData_14* temp_a1;

    for (i = arg1[0].field_0; i < arg1[1].field_0; i++)
    {
        idx = ipdColl->ptr_28[i];
        temp_a0 = ipdColl->field_30;

        if (temp_a0 >= ipdColl->field_34[idx])
        {
            ipdColl->field_34[idx] = temp_a0 + 1;

            if (idx < ipdColl->field_8_16)
            {
                temp_a1 = &ipdColl->ptr_14[idx];

                temp_v0 = (u16)state->field_4 >> (temp_a1->field_0_14 * 4 | temp_a1->field_2_14);

                if (temp_v0 & (1 << 0))
                {
                    temp_a0_3 = temp_a1->field_8;
                    temp_a2   = temp_a1->field_9;

                    cond0 = temp_a0_3 != 0xFF && temp_a2 != 0xFF;

                    if (state->field_0 == true)
                    {
                        if (cond0)
                        {
                            continue;
                        }
                    }
                    else
                    {
                        cond1 = false;
                        cond2 = false;

                        if (temp_a0_3 == 0xFF || ipdColl->ptr_10[temp_a0_3].groundType == GroundType_Default ||
                            ipdColl->ptr_10[temp_a0_3].groundType == GroundType_12)
                        {
                            cond1 = true;
                        }

                        if (temp_a2 == 0xFF || ipdColl->ptr_10[temp_a2].groundType == GroundType_Default ||
                            ipdColl->ptr_10[temp_a2].groundType == GroundType_12)
                        {
                            cond2 = true;
                        }

                        if (cond1 && cond2)
                        {
                            continue;
                        }
                    }

                    func_8006E78C(state, temp_a1, ipdColl->ptr_C, ipdColl->ptr_10, cond0);
                }
            }
            else
            {
                temp_a1_2 = &ipdColl->ptr_18[idx - ipdColl->field_8_16];
                temp_v0_2 = (u16)state->field_4 >> temp_a1_2->field_0_8;

                if ((temp_v0_2 & (1 << 0)) &&
                    (state->field_0 == true ||
                     (temp_a1_2->groundType != GroundType_Default &&
                      temp_a1_2->groundType != GroundType_12)) &&
                    temp_a1_2->field_8 >= state->field_6)
                {
                    func_8006EB8C(state, temp_a1_2);
                }
            }
        }
    }
}

void func_8006E78C(s_RayState* state, s_IpdCollisionData_14* arg1, SVECTOR3* arg2, s_IpdCollisionData_10* arg3, s32 arg4) // 0x8006E78C
{
    SVECTOR sp0;
    SVECTOR sp8;

    SVECTOR3  sp10;
    s32       var_a3;
    q19_12    unkX;
    q19_12    unkZ;
    s32       var_a2;
    s32       groundType; // `e_GroundType`
    SVECTOR3* temp_t1;
    SVECTOR3* temp_t2;
    s32       temp_v1;
    s32       var_v1;

    groundType = GroundType_Default;
    temp_t1 = &arg2[arg1->field_7];
    temp_t2 = &arg2[arg1->field_6];

    if (state->field_5E >= temp_t1->vy || state->field_5E >= temp_t2->vy)
    {
        if (arg1->field_8 != 0xFF)
        {
            groundType = arg3[arg1->field_8].groundType;
        }
        if (arg1->field_9 != 0xFF)
        {
            groundType = arg3[arg1->field_9].groundType;
        }

        temp_v1 = state->field_58 + (state->field_5A << 16);
        gte_ldR11R12(temp_v1);
        gte_ldR13R21(temp_v1);
        gte_ldvxy0(((temp_t1->vx - state->field_6C.groundHeight) & 0xFFFF) + ((temp_t1->vz - state->field_6C.field_A) << 16));
        gte_gte_ldvz0();
        gte_rtv0();
        gte_stMAC12(&sp0);

        gte_ldvxy0(((temp_t2->vx - state->field_6C.groundHeight) & 0xFFFF) + ((temp_t2->vz - state->field_6C.field_A) << 16));
        gte_gte_ldvz0();
        gte_rtv0();
        gte_stMAC12(&sp8);

        if ((sp0.vy & 0x8000) != (sp8.vy & 0x8000))
        {
            if (state->field_0 == true)
            {
                gte_ldsxy3(0, *(s32*)&sp0.vx, *(s32*)&sp8.vx);
                gte_nclip();

                if (gte_stMAC0() >= 0)
                {
                    if (arg1->field_8 != 0xFF)
                    {
                        return;
                    }
                }
                else
                {
                    if (arg1->field_9 != 0xFF)
                    {
                        return;
                    }
                }
            }

            if (sp0.vy != sp8.vy)
            {
                var_v1 = ((sp0.vy << 12) / (sp0.vy - sp8.vy));
                var_a3 = (((sp8.vx - sp0.vx) * var_v1) >> 12) + sp0.vx;
                if (var_a3 >= 0 && state->rayDistance >= var_a3)
                {
                    gte_lddp(var_v1);
                    gte_ldsv3_(temp_t2->vx - temp_t1->vx, temp_t2->vy - temp_t1->vy, temp_t2->vz - temp_t1->vz);
                    gte_gpf12();
                    gte_stsv(&sp10);

                    sp10.vx += temp_t1->vx;
                    sp10.vy += temp_t1->vy;
                    sp10.vz += temp_t1->vz;

                    var_a2 = state->from.vy + state->field_4E;
                    if (state->offset.vy != 0)
                    {
                        var_a2 += (state->offset.vy * var_a3) / state->rayDistance;
                    }

                    if (var_a2 >= sp10.vy && var_a3 < state->field_8)
                    {
                        unkX = arg1->field_2_0;
                        unkZ = -arg1->field_0_0;
                        if (state->field_0 != true && arg4 != 0 && (sp8.vy - sp0.vy) > 0)
                        {
                            unkX = -unkX;
                            unkZ = arg1->field_0_0;
                        }

                        state->field_8  = var_a3;
                        state->field_C  = (sp10.vx + state->field_6C.field_0);
                        state->field_10 = (var_a2 - state->field_4E);
                        state->field_14 = (sp10.vz + state->field_6C.field_4);
                        state->groundHeight = sp10.vy;
                        state->field_24 = unkX;
                        state->field_26 = unkZ;
                        state->field_20 = 0;
                        state->groundType = groundType;
                    }
                }
            }
        }
    }
}

void func_8006EB8C(s_RayState* state, s_IpdCollisionData_18* arg1) // 0x8006EB8C
{
    SVECTOR sp10;
    SVECTOR sp18;
    s16     temp_a1_3;
    s32     temp_v0;
    s16     temp_a1;
    s32     temp_v1;

    temp_a1 = arg1->field_8;
    if (state->field_5E <= arg1->vec_2.vy)
    {
        return;
    }

    temp_v1 = state->field_58 + (state->field_5A << 16);
    gte_ldR11R12(temp_v1);
    gte_ldR13R21(temp_v1);
    gte_ldvxy0(((arg1->vec_2.vx - state->field_6C.groundHeight) & 0xFFFF) + ((arg1->vec_2.vz - state->field_6C.field_A) << 16));
    gte_gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&sp10);

    if (-temp_a1 < sp10.vx && sp10.vx < (state->rayDistance + temp_a1) && -temp_a1 < sp10.vy && sp10.vy < temp_a1)
    {
        temp_v0   = SquareRoot0((temp_a1 * temp_a1) - (sp10.vy * sp10.vy));
        temp_a1_3 = sp10.vx - temp_v0;

        if (temp_a1_3 >= -temp_v0 && state->rayDistance >= temp_a1_3 && temp_a1_3 < state->field_8)
        {
            gte_lddp(((temp_a1_3 << 12) / state->rayDistance));
            gte_ldsv3_(state->offset.vx, state->offset.vy, state->offset.vz);
            gte_gpf12();
            gte_stsv(&sp18);

            if ((sp18.vy + state->from.vy + state->field_4E) >= arg1->vec_2.vy)
            {
                state->field_8  = temp_a1_3;
                state->field_C  = sp18.vx + state->field_6C.groundHeight + state->field_6C.field_0;
                state->field_10 = sp18.vy + state->from.vy;
                state->field_14 = sp18.vz + state->field_6C.field_A + state->field_6C.field_4;
                state->groundHeight = arg1->vec_2.vy;
                state->field_24 = (sp18.vx + state->field_6C.groundHeight) - arg1->vec_2.vx;
                state->field_26 = (sp18.vz + state->field_6C.field_A) - arg1->vec_2.vz;
                state->field_20 = 0;
                state->groundType = arg1->groundType;
            }
        }
    }
}

void func_8006EE0C(s_RayState_6C* arg0, bool useCylinder, const s_SubCharacter* chara) // 0x8006EE0C
{
    q19_12 offsetZ;
    q19_12 offsetX;
    q19_12 unkY;

    if (useCylinder == true)
    {
        arg0->field_C = Q12_TO_Q8(chara->collision.cylinder.radius);
        offsetX       = chara->collision.shapeOffsets.cylinder.vx;
        offsetZ       = chara->collision.shapeOffsets.cylinder.vz;
        unkY          = chara->position.vy + chara->collision.box.bottom;
    }
    else
    {
        arg0->field_C = Q12_TO_Q8(chara->collision.cylinder.field_2);
        offsetX       = chara->collision.shapeOffsets.box.vx;
        offsetZ       = chara->collision.shapeOffsets.box.vz;
        unkY          = chara->position.vy + chara->collision.box.height;
    }

    arg0->field_A = Q12_TO_Q8(unkY);
    arg0->field_0 = Q12_TO_Q8(chara->position.vx + offsetX);
    arg0->field_4 = Q12_TO_Q8(chara->position.vz + offsetZ);
    arg0->groundHeight = Q12_TO_Q8(chara->position.vy + chara->collision.box.top);
}

void func_8006EEB8(s_RayState* state, s_SubCharacter* chara) // 0x8006EEB8
{
    VECTOR3 pos; // Q19.12
    s32     bound;
    q3_12   alpha;
    q3_12   clampedRayDist;
    q23_8   x1;
    q23_8   z1;
    q23_8   x0;
    q23_8   z0;
    q19_12  var_v1;

    if (state->from.vx <= state->field_3C)
    {
        x0 = state->from.vx;
        z0 = state->field_3C;
    }
    else
    {
        x0 = state->field_3C;
        z0 = state->from.vx;
    }

    if (state->from.vz <= state->field_44)
    {
        z1 = state->from.vz;
        x1 = state->field_44;
    }
    else
    {
        z1 = state->field_44;
        x1 = state->from.vz;
    }

    bound = state->field_6C.field_C;
    if ((state->field_6C.field_0 + bound) < x0 ||
         z0 < (state->field_6C.field_0 - bound))
    {
        return;
    }

    if ((state->field_6C.field_4 + bound) < z1 || x1 < (state->field_6C.field_4 - bound) ||
        ((state->from.vy + state->field_4E) < state->field_6C.groundHeight && (state->field_40 + state->field_4E) < state->field_6C.groundHeight) ||
        ((state->from.vy + state->field_4C) > state->field_6C.field_A && state->field_6C.field_A < (state->field_40 + state->field_4C)))
    {
        return;
    }

    alpha = func_8006C248(*(s32*)&state->field_58, state->rayDistance,
                          state->field_6C.field_0 - state->from.vx,
                          state->field_6C.field_4 - state->from.vz,
                          bound);
    if (alpha == NO_VALUE)
    {
        return;
    }

    clampedRayDist = Q12_MULT(state->rayDistance, alpha);
    if (clampedRayDist >= state->field_8)
    {
        return;
    }

    pos.vy = state->from.vy + (Q12_MULT(state->offset.vy, alpha));
    if ((pos.vy + state->field_4E) < state->field_6C.groundHeight ||
        state->field_6C.field_A < (pos.vy + state->field_4C))
    {
        if (state->offset.vy == 0)
        {
            return;
        }

        if ((pos.vy + state->field_4E) < state->field_6C.groundHeight)
        {
            var_v1 = Q12(state->field_6C.groundHeight - (state->from.vy + state->field_4E)) / state->offset.vy;
            if (var_v1 > Q12(1.0f))
            {
                return;
            }
            pos.vy = state->field_6C.groundHeight - state->field_4E;
        }
        else
        {
            var_v1 = Q12(state->field_6C.field_A - (state->from.vy + state->field_4C)) / state->offset.vy;
            if (var_v1 > Q12(1.0f))
            {
                return;
            }
            pos.vy = state->field_6C.field_A - state->field_4C;
        }

        pos.vx = state->from.vx + Q12_MULT(state->offset.vx, var_v1);
        pos.vz = state->from.vz + Q12_MULT(state->offset.vz, var_v1);
        if ((SQUARE(state->field_6C.field_0 - pos.vx) + SQUARE(state->field_6C.field_4 - pos.vz)) >= SQUARE(state->field_6C.field_C))
        {
            return;
        }
    }
    else
    {
        pos.vx = state->from.vx + Q12_MULT(state->offset.vx, alpha);
        pos.vz = state->from.vz + Q12_MULT(state->offset.vz, alpha);
    }

    state->field_8  = clampedRayDist;
    state->field_C  = pos.vx;
    state->field_10 = pos.vy;
    state->field_14 = pos.vz;
    state->groundHeight = state->field_6C.groundHeight;
    state->field_24 = pos.vx - state->field_6C.field_0;
    state->field_26 = pos.vz - state->field_6C.field_4;
    state->field_20 = chara;
    state->groundType = GroundType_Default;
}

void func_8006F250(q19_12* arg0, q19_12 posX, q19_12 posZ, q19_12 posDeltaX, q19_12 posDeltaZ) // 0x8006F250
{
    s32              i;
    s_func_8006F338* scratch;

    scratch = PSX_SCRATCH;

    func_8006F338(scratch, posX, posZ, posDeltaX, posDeltaZ);

    for (i = 0; i < D_800C4478.triggerZoneCount; i++)
    {
        if (func_8006F3C4(scratch, D_800C4478.triggerZones[i]))
        {
            break;
        }
    }

    if (scratch->field_28 == Q12(1.0f))
    {
        arg0[0] = Q12(32.0f);
        arg0[1] = Q12(-16.0f);
    }
    else
    {
        arg0[0] = Math_MulFixed(Vc_VectorMagnitudeCalc(scratch->field_10, Q12(0.0f), scratch->field_14), scratch->field_28, Q12_SHIFT);
        arg0[1] = scratch->field_2C;
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
    arg0->field_2C = Q12(1048560.0f);
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

bool func_8006F3C4(s_func_8006F338* arg0, const s_TriggerZone* zone) // 0x8006F3C4
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

    minX = Q12(zone->positionX);
    maxX = Q12(zone->positionX + zone->sizeX);
    minZ = Q12(zone->positionZ);
    maxZ = Q12(zone->positionZ + zone->sizeZ);

    if ((minX >= arg0->field_1C || arg0->field_18 >= maxX) &&
        (minZ >= arg0->field_24 || arg0->field_20 >= maxZ))
    {
        return false;
    }

    if (arg0->field_0 >= minX && maxX >= arg0->field_0 &&
        arg0->field_4 >= minZ && maxZ >= arg0->field_4)
    {
        arg0->field_28 = Q12(0.0f);
        arg0->field_2C = (-Q12(zone->height) >> 1) - Q12(1.5f);
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
            arg0->field_2C = (-Q12(zone->height) >> 1) - Q12(1.5f);
        }
    }

    return arg0->field_28 == 0;
}

q19_12 func_8006F620(VECTOR3* pos, s_CollisionQuery* collQuery, q19_12 dist, q19_12 offsetY) // 0x8006F620
{
    q19_12         x0;
    q19_12         z0;
    q19_12         x1;
    q19_12         z1;
    q19_12         collOffsetY;
    q19_12         posY;
    q19_12         distX;
    q19_12         distZ;
    q19_12         temp_a0;
    q19_12         zoneHeight;
    q19_12         max1;
    q19_12         temp_s0_3;
    q19_12         mag0;
    q19_12         angle;
    q19_12         var_s2;
    s32            i;
    q19_12         posX;
    q19_12         posZ;
    s32            height;
    s32            var_v1;
    s_TriggerZone* curZone;

    height = Q12(-16.0f);

    distX = Q12(0.0f);
    distZ = Q12(0.0f);

    posX        = pos->vx;
    posZ        = pos->vz;
    collOffsetY = collQuery->position.vy + offsetY;
    posY        = collOffsetY + pos->vy;

    for (i = 0; i < D_800C4478.triggerZoneCount; i++)
    {
        curZone = D_800C4478.triggerZones[i];

        // Check height.
        zoneHeight = (-Q12(curZone->height) >> 1) - Q12(1.5f);
        if ((posY - zoneHeight) >= Q12(0.0f))
        {
            continue;
        }

        func_8006F8FC(&x0, &z0, collQuery->position.vx + posX, collQuery->position.vz + posZ, curZone);
        if (MAX(ABS(x0), ABS(z0)) >= dist)
        {
            continue;
        }

        mag0 = Vc_VectorMagnitudeCalc(x0, Q12(0.0f), z0);
        if (mag0 >= dist)
        {
            continue;
        }

        if (mag0 > Q12(0.0f))
        {
            func_8006F8FC(&x1, &z1, collQuery->position.vx, collQuery->position.vz, curZone);

            var_s2 = Q12(0.1f);
            max1   = Vc_VectorMagnitudeCalc(x1, Q12(0.0f), z1);
            if ((dist - max1) <= Q12(0.1f))
            {
                var_s2 = dist - max1;
            }

            if ((mag0 - max1) < var_s2)
            {
                angle = ratan2(x0, z0);
                temp_s0_3 = var_s2 - (mag0 - max1);

                distX = Math_MulFixed(temp_s0_3, Math_Sin(angle), Q12_SHIFT);
                distZ = Math_MulFixed(temp_s0_3, Math_Cos(angle), Q12_SHIFT);
            }
        }
        else
        {
            if (zoneHeight < height)
            {
                height = zoneHeight;
            }

            posX = pos->vx;
            posZ = pos->vz;
            break;
        }

        posX += distX;
        posZ += distZ;
    }

    pos->vx = posX;
    pos->vz = posZ;

    if (height != Q12(-16.0f))
    {
        var_v1  = Q12(0.1f);
        temp_a0 = height - collOffsetY;

        if (temp_a0 < Q12(0.1f))
        {
            var_v1 = temp_a0;
        }

        if (pos->vy < var_v1)
        {
            pos->vy = var_v1;
        }
    }

    return height;
}

void func_8006F8FC(q19_12* outX, q19_12* outZ, q19_12 posX, q19_12 posZ, const s_TriggerZone* zone) // 0x8006F8FC
{
    q19_12 minX;
    q19_12 maxX;
    q19_12 minZ;
    q19_12 maxZ;

    // TODO: Using `Q12` doesn't match? There's an identical block in `func_8006F3C4`.
    minX = FP_TO(zone->positionX, Q12_SHIFT);
    maxX = FP_TO(zone->positionX + zone->sizeX, Q12_SHIFT);
    minZ = FP_TO(zone->positionZ, Q12_SHIFT);
    maxZ = FP_TO(zone->positionZ + zone->sizeZ, Q12_SHIFT);

    if (posX < minX)
    {
        *outX = posX - minX;
    }
    else
    {
        if (maxX >= posX)
        {
            *outX = Q12(0.0f);
        }
        else
        {
            *outX = posX - maxX;
        }
    }

    if (posZ < minZ)
    {
        *outZ = posZ - minZ;
        return;
    }
    else if (maxZ >= posZ)
    {
        *outZ = Q12(0.0f);
        return;
    }

    *outZ = posZ - maxZ;
}

// ========================================
// CHARACTER ANIMATION
// ========================================

q19_12 func_8006F99C(s_SubCharacter* chara, q19_12 dist, q3_12 headingAngle) // 0x8006F99C
{
    q3_12 curAngleOffset;
    q3_12 angleOffset;
    s32   i;

    angleOffset = NO_VALUE;
    for (i = 0; i < 15; i++)
    {
        if (i == 0)
        {
            curAngleOffset = Rng_GenerateUInt(-32, 31);
        }
        else if (i & 0x1)
        {
            curAngleOffset = (256 << ((i + 1) >> 1)) + Rng_GenerateUInt(0, 63);
        }
        else
        {
            curAngleOffset = -(256 << (i >> 1)) - Rng_GenerateUInt(0, 63);
        }

        if (angleOffset != NO_VALUE)
        {
            if (ABS(angleOffset) < ABS(curAngleOffset))
            {
                continue;
            }
        }

        if (!Ray_CharaLosHitCheck(chara, dist, curAngleOffset + headingAngle))
        {
            angleOffset = curAngleOffset;
        }
    }

    if (angleOffset != NO_VALUE)
    {
        return Math_AngleNormalizeSigned(angleOffset + headingAngle);
    }

    return Q12_ANGLE(360.0f);
}

q19_12 Chara_HeadingAngleGet(s_SubCharacter* chara, q19_12 dist, q19_12 toX, q19_12 toZ, q3_12 spanAngle, bool isClockwise) // 0x8006FAFC
{
    #define SPAN_STEP_COUNT 3

    s16    spanAngleStep;
    q3_12  curAngle;
    q19_12 curToZ;
    q19_12 curToX;
    q25_6  curOffsetX;
    q25_6  curOffsetZ;
    q25_6  curDist;
    s32    i;
    q19_12 shortestOrLongestDist;
    s32    stepCount;
    q3_12  unkAngle;

    // Define if distance should track minimum or maximum.
    shortestOrLongestDist = Q12(0.0f);
    if (isClockwise)
    {
        shortestOrLongestDist = INT_MAX;
    }

    spanAngleStep = spanAngle / SPAN_STEP_COUNT;
    unkAngle = Q12_ANGLE(-360.0f);

    // Define step count.
    stepCount = 7;
    if (spanAngle == Q12_ANGLE(360.0f))
    {
        stepCount = 12;
    }

    // Run through steps in span.
    for (i = 0; i < stepCount; i++)
    {
        if (spanAngle == Q12_ANGLE(360.0f))
        {
            curAngle = Q12((i * 30) + (Rng_Rand16() % 30)) / 360;
        }
        else
        {
            curAngle = (chara->rotation.vy +
                        ((i - SPAN_STEP_COUNT) * spanAngleStep) +
                        ((Rng_Rand16() % spanAngleStep) >> 1)) -
                       (spanAngleStep >> 2);
        }

        curToX = chara->position.vx + Q12_MULT(dist, Math_Sin(curAngle));
        curToZ = chara->position.vz + Q12_MULT(dist, Math_Cos(curAngle));

        if (!Ray_CharaToTargetLosHitCheck(chara, curToX, chara->position.vy, curToZ))
        {
            curOffsetX = Q12_TO_Q6(toX - curToX);
            curOffsetZ = Q12_TO_Q6(toZ - curToZ);
            curDist    = SQUARE(curOffsetX) + SQUARE(curOffsetZ);

            if ((!isClockwise && (shortestOrLongestDist < curDist)) ||
                ( isClockwise && (curDist               < shortestOrLongestDist)))
            {
                shortestOrLongestDist = curDist;
                unkAngle              = curAngle;
            }
        }
    }

    if (unkAngle != Q12_ANGLE(-360.0f))
    {
        return Math_AngleNormalizeSigned(unkAngle);
    }
    return Q12_ANGLE(360.0f);

    #undef SPAN_STEP_COUNT
}

bool func_8006FD90(s_SubCharacter* chara, s32 count, q19_12 baseDistMax, q19_12 distStep) // 0x8006FD90
{
    VECTOR3 sp10;
    VECTOR3 sp20;
    VECTOR3 pos;    // Q19.12
    VECTOR3 offset; // Q19.12
    s32     i;
    q19_12  dist;
    q19_12  distMult;
    q19_12  distMax;

    if (Math_AngleNormalizeSigned(ratan2(g_SysWork.playerWork.player.position.vx - chara->position.vx,
                                         g_SysWork.playerWork.player.position.vz - chara->position.vz) -
                                  chara->rotation.vy) < Q12_ANGLE(0.0f))
    {
        distMult = (Math_AngleNormalizeSigned(ratan2(g_SysWork.playerWork.player.position.vx - chara->position.vx,
                                                     g_SysWork.playerWork.player.position.vz - chara->position.vz) -
                                              chara->rotation.vy) * 2) + Q12_ANGLE(360.0f);
    }
    else
    {
        distMult = (Q12_ANGLE(180.0f) - Math_AngleNormalizeSigned((ratan2(g_SysWork.playerWork.player.position.vx - chara->position.vx,
                                                                          g_SysWork.playerWork.player.position.vz - chara->position.vz) -
                                                                   chara->rotation.vy))) * 2;
    }

    for (i = distMult; count > 0; count--)
    {
        distMult = Q12_MULT_PRECISE(distMult, i);
    }

    dist = Math_Vector2MagCalc(g_SysWork.playerWork.player.position.vx - chara->position.vx,
                               g_SysWork.playerWork.player.position.vz - chara->position.vz);
    distMax = baseDistMax + Q12_MULT_PRECISE(distStep, distMult);
    if (distMax < dist)
    {
        return false;
    }

    pos.vx = chara->position.vx;
    pos.vz = chara->position.vz;

    offset.vx = g_SysWork.playerWork.player.position.vx - chara->position.vx;
    offset.vz = g_SysWork.playerWork.player.position.vz - chara->position.vz;

    if ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1))
    {
        offset.vy = Q12(0.0f);
        pos.vy = g_SysWork.playerWork.player.position.vy + g_SysWork.playerWork.player.collision.box.top;
    }
    else
    {
        pos.vy = chara->position.vy + chara->collision.box.offsetY;
        offset.vy = (g_SysWork.playerWork.player.position.vy + g_SysWork.playerWork.player.collision.box.offsetY) -
                    (chara->position.vy - chara->collision.box.offsetY);
    }

    // Maybe `sp10` is not `VECTOR3`. Might need to rewrite this whole function if its `s_RayTrace`?
    return !Ray_CharaTraceQuery(&sp10, &pos, &offset, chara) || sp20.vx != Q12(0.0f);
}

bool Ray_CharaToTargetLosHitCheck(s_SubCharacter* fromChara, q19_12 toX, q19_12 toY, q19_12 toZ)
{
    s_RayTrace trace;
    VECTOR3    offset; // Q19.12

    offset.vx = toX - fromChara->position.vx;
    offset.vy = toY - fromChara->position.vy;
    offset.vz = toZ - fromChara->position.vz;

    return Ray_LosHitCheck(&trace, &fromChara->position, &offset, fromChara);
}

bool Ray_CharaToCharaTargetLosCheck(s_SubCharacter* fromChara, q19_12 toX, q19_12 toY, q19_12 toZ) // 0x80070084
{
    s_RayTrace trace;
    VECTOR3    offset; // Q19.12
    bool       isCharaMissed;

    offset.vx = toX - fromChara->position.vx;
    offset.vy = toY - fromChara->position.vy;
    offset.vz = toZ - fromChara->position.vz;

    isCharaMissed = false;
    if (Ray_LosHitCheck(&trace, &fromChara->position, &offset, fromChara))
    {
        isCharaMissed = trace.character == NULL;
    }
    return isCharaMissed;
}

bool Ray_NpcToPlayerLosHitCheck(s_SubCharacter* fromNpc, s_SubCharacter* toPlayer) // 0x800700F8
{
    s_RayTrace trace;
    VECTOR3    from;   // Q19.12
    VECTOR3    offset; // Q19.12

    from = fromNpc->position;

    offset.vx = toPlayer->position.vx - fromNpc->position.vx;
    offset.vy = Q12(-0.1f);
    offset.vz = toPlayer->position.vz - fromNpc->position.vz;

    return Ray_LosHitCheck(&trace, &from, &offset, fromNpc) && trace.character == NULL;
}

bool Ray_CharaToCharaDistLosCheck(s_SubCharacter* fromChara, q19_12 dist, q3_12 headingAngle) // 0x80070184
{
    q19_12 toX;
    q19_12 toY;
    q19_12 toZ;
    q19_12 sinHeadingAngle;
    q19_12 cosHeadingAngle;

    sinHeadingAngle = Math_Sin(headingAngle);
    toX             = fromChara->position.vx + Q12_MULT(dist, sinHeadingAngle);

    cosHeadingAngle = Math_Cos(headingAngle);
    toY             = fromChara->position.vy;
    toZ             = fromChara->position.vz + Q12_MULT(dist, cosHeadingAngle);

    return Ray_CharaToCharaTargetLosCheck(fromChara, toX, toY, toZ);
}

bool Ray_CharaToCharaFrontLosHitCheck(s_SubCharacter* fromChara, q19_12 dist) // 0x80070208
{
    s_RayTrace trace;
    VECTOR3    offset; // Q19.12
    bool       hasHit;

    offset.vx = Q12_MULT(dist, Math_Sin(fromChara->rotation.vy));
    offset.vy = Q12(0.0f);
    offset.vz = Q12_MULT(dist, Math_Cos(fromChara->rotation.vy));

    hasHit = false;
    if (Ray_LosHitCheck(&trace, &fromChara->position, &offset, fromChara))
    {
        hasHit = trace.character > NULL;
    }
    return hasHit;
}

bool Ray_CharaLosHitCheck(s_SubCharacter* fromChara, q19_12 dist, q3_12 headingAngle) // 0x8007029C
{
    s_RayTrace trace;
    VECTOR3    offset; // Q19.12

    offset.vx = Q12_MULT(dist, Math_Sin(headingAngle));
    offset.vy = Q12(0.0f);
    offset.vz = Q12_MULT(dist, Math_Cos(headingAngle));

    return Ray_LosHitCheck(&trace, &fromChara->position, &offset, fromChara);
}

bool func_80070320(void) // 0x80070320
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcIdxs); i++)
    {
        if (g_SysWork.npcIdxs[i] != NO_VALUE)
        {
            return true;
        }
    }

    return false;
}

q19_12 func_80070360(s_SubCharacter* chara, q19_12 someDist, q3_12 arg2) // 0x80070360
{
    q25_6  deltaX;
    q25_6  deltaZ;
    q19_12 dist;
    q19_12 result;

    dist = someDist;
    if (dist == Q12(0.0f))
    {
        deltaX = g_SysWork.playerWork.player.position.vx - chara->position.vx;
        deltaX = Q12_TO_Q6(deltaX);

        deltaZ = g_SysWork.playerWork.player.position.vz - chara->position.vz;
        deltaZ = Q12_TO_Q6(deltaZ);

        dist = SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ));
        dist = Q6_TO_Q12(dist);
    }

    // TODO: Why `>> 8`?
    result = Q12_MULT(arg2, g_SysWork.playerWork.player.properties.player.field_10C) - (dist >> 8);
    if (result < Q12(0.0f))
    {
        result = Q12(0.0f);
    }
    return result;
}

void Collision_CharaCollisionSet(s_SubCharacter* chara, s_Keyframe* keyframe0, s_Keyframe* keyframe1) // 0x80070400
{
    q19_12 alpha;
    q19_12 invAlpha;

    // Compute alpha.
    if (ANIM_STATUS_IS_ACTIVE(chara->model.anim.status))
    {
        alpha = Q12_FRACT(chara->model.anim.time);
    }
    else
    {
        alpha = chara->model.anim.alpha;
    }
    invAlpha = Q12(1.0f) - alpha;

    // Set interpolated collision shapes for active frame.
    chara->collision.box.top                  = FP_FROM((keyframe0->box.top     * invAlpha) + (keyframe1->box.top     * alpha), Q12_SHIFT);
    chara->collision.box.bottom               = FP_FROM((keyframe0->box.bottom  * invAlpha) + (keyframe1->box.bottom  * alpha), Q12_SHIFT);
    chara->collision.box.height               = FP_FROM((keyframe0->box.height  * invAlpha) + (keyframe1->box.height  * alpha), Q12_SHIFT);
    chara->collision.box.offsetY              = FP_FROM((keyframe0->box.offsetY * invAlpha) + (keyframe1->box.offsetY * alpha), Q12_SHIFT);
    chara->collision.shapeOffsets.cylinder.vx = FP_FROM((keyframe0->shapeOffsets.cylinder.vx * invAlpha) + (keyframe1->shapeOffsets.cylinder.vx * alpha), Q12_SHIFT);
    chara->collision.shapeOffsets.cylinder.vz = FP_FROM((keyframe0->shapeOffsets.cylinder.vz * invAlpha) + (keyframe1->shapeOffsets.cylinder.vz * alpha), Q12_SHIFT);
    chara->collision.cylinder.radius          = FP_FROM((keyframe0->box.field_8 * invAlpha) + (keyframe1->box.field_8 * alpha), Q12_SHIFT);
    chara->collision.shapeOffsets.box.vx      = FP_FROM((keyframe0->shapeOffsets.box.vx * invAlpha) + (keyframe1->shapeOffsets.box.vx * alpha), Q12_SHIFT);
    chara->collision.shapeOffsets.box.vz      = FP_FROM((keyframe0->shapeOffsets.box.vz * invAlpha) + (keyframe1->shapeOffsets.box.vz * alpha), Q12_SHIFT);
    chara->collision.cylinder.field_2         = FP_FROM((keyframe0->box.field_A * invAlpha) + (keyframe1->box.field_A * alpha), Q12_SHIFT);
}

void func_800705E4(GsCOORDINATE2* boneCoords, s32 idx, q19_12 scaleX, q19_12 scaleY, q19_12 scaleZ) // 0x800705E4
{
    q3_12 scale[3];
    s32   j;
    s32   i;

    scale[0] = scaleX;
    scale[1] = scaleY;
    scale[2] = scaleZ;

    for (i = 0; i < ARRAY_SIZE(scale); i++)
    {
        if (scale[i] == Q12(1.0f))
        {
            continue;
        }

        for (j = 0; j < 3; j++)
        {
            boneCoords[idx].coord.m[j][i] = Q12_MULT_PRECISE(scale[i], boneCoords[idx].coord.m[j][i]);
        }
    }

    boneCoords->flg = false;
}

// Used to overwrite `HARRY_BASE_ANIM_INFOS[56:76]` with weapon-specific animations.
// Always copies 20 `s_AnimInfo`s, but most weapons use less than that.
// @bug `EquippedWeaponId_HyperBlaster` will copy past the end of this array?
const s_AnimInfo D_80028B94[] = {
/* `EquippedWeaponId_Axe` */
/* 0   */ { Anim_BlendLinear,  ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 1   */ { Anim_PlaybackOnce, ANIM_STATUS(28, true),  false, ANIM_STATUS(28, true), { Q12(25.0f)  }, 568, 577 },
/* 2   */ { Anim_BlendLinear,  ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 579 },
/* 3   */ { Anim_PlaybackOnce, ANIM_STATUS(29, true),  false, ANIM_STATUS(29, true), { Q12(20.0f)  }, 579, 598 },
/* 4   */ { Anim_BlendLinear,  ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 599 },
/* 5   */ { Anim_PlaybackOnce, ANIM_STATUS(30, true),  false, ANIM_STATUS(30, true), { Q12(18.0f)  }, 599, 615 },
/* 6   */ { Anim_BlendLinear,  ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 616 },
/* 7   */ { Anim_PlaybackOnce, ANIM_STATUS(31, true),  false, ANIM_STATUS(31, true), { Q12(20.0f)  }, 616, 635 },
/* 8   */ { Anim_BlendLinear,  ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 577 },
/* 9   */ { Anim_PlaybackOnce, ANIM_STATUS(32, true),  false, ANIM_STATUS(32, true), { Q12(-35.0f) }, 568, 577 },

/* `EquippedWeaponId_Hammer` */
/* 10  */ { Anim_BlendLinear,  ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 11  */ { Anim_PlaybackOnce, ANIM_STATUS(28, true),  false, ANIM_STATUS(28, true), { Q12(40.0f)  }, 568, 579 },
/* 12  */ { Anim_BlendLinear,  ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 584 },
/* 13  */ { Anim_PlaybackOnce, ANIM_STATUS(29, true),  false, ANIM_STATUS(29, true), { Q12(22.0f)  }, 584, 613 },
/* 14  */ { Anim_BlendLinear,  ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 614 },
/* 15  */ { Anim_PlaybackOnce, ANIM_STATUS(30, true),  false, ANIM_STATUS(30, true), { Q12(16.0f)  }, 614, 634 },
/* 16  */ { Anim_BlendLinear,  ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 637 },
/* 17  */ { Anim_PlaybackOnce, ANIM_STATUS(31, true),  false, ANIM_STATUS(31, true), { Q12(18.0f)  }, 637, 659 },
/* 18  */ { Anim_BlendLinear,  ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 579 },
/* 19  */ { Anim_PlaybackOnce, ANIM_STATUS(32, true),  false, ANIM_STATUS(32, true), { Q12(-35.0f) }, 568, 579 },

/* `EquippedWeaponId_SteelPipe` */
/* 20  */ { Anim_BlendLinear,  ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 21  */ { Anim_PlaybackOnce, ANIM_STATUS(28, true),  false, ANIM_STATUS(28, true), { Q12(45.0f)  }, 568, 579 },
/* 22  */ { Anim_BlendLinear,  ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 584 },
/* 23  */ { Anim_PlaybackOnce, ANIM_STATUS(29, true),  false, ANIM_STATUS(29, true), { Q12(25.0f)  }, 584, 613 },
/* 24  */ { Anim_BlendLinear,  ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 614 },
/* 25  */ { Anim_PlaybackOnce, ANIM_STATUS(30, true),  false, ANIM_STATUS(30, true), { Q12(16.0f)  }, 614, 634 },
/* 26  */ { Anim_BlendLinear,  ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 637 },
/* 27  */ { Anim_PlaybackOnce, ANIM_STATUS(31, true),  false, ANIM_STATUS(31, true), { Q12(20.0f)  }, 637, 659 },
/* 28  */ { Anim_BlendLinear,  ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 579 },
/* 29  */ { Anim_PlaybackOnce, ANIM_STATUS(32, true),  false, ANIM_STATUS(32, true), { Q12(-40.0f) }, 568, 579 },

/* `EquippedWeaponId_KitchenKnife` */
/* 30  */ { Anim_BlendLinear,  ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 31  */ { Anim_PlaybackOnce, ANIM_STATUS(28, true),  false, ANIM_STATUS(28, true), { Q12(30.0f)  }, 568, 575 },
/* 32  */ { Anim_BlendLinear,  ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 581 },
/* 33  */ { Anim_PlaybackOnce, ANIM_STATUS(29, true),  false, ANIM_STATUS(29, true), { Q12(20.0f)  }, 581, 595 },
/* 34  */ { Anim_BlendLinear,  ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 596 },
/* 35  */ { Anim_PlaybackOnce, ANIM_STATUS(30, true),  false, ANIM_STATUS(30, true), { Q12(16.0f)  }, 596, 611 },
/* 36  */ { Anim_BlendLinear,  ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 613 },
/* 37  */ { Anim_PlaybackOnce, ANIM_STATUS(31, true),  false, ANIM_STATUS(31, true), { Q12(16.0f)  }, 613, 629 },
/* 38  */ { Anim_BlendLinear,  ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 577 },
/* 39  */ { Anim_PlaybackOnce, ANIM_STATUS(32, true),  false, ANIM_STATUS(32, true), { Q12(-40.0f) }, 568, 577 },

/* `EquippedWeaponId_Katana` */
/* 40  */ { Anim_BlendLinear,  ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 41  */ { Anim_PlaybackOnce, ANIM_STATUS(28, true),  false, ANIM_STATUS(28, true), { Q12(30.0f) }, 568, 579 },
/* 42  */ { Anim_BlendLinear,  ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 580 },
/* 43  */ { Anim_PlaybackOnce, ANIM_STATUS(29, true),  false, ANIM_STATUS(29, true), { Q12(25.0f) }, 580, 597 },
/* 44  */ { Anim_BlendLinear,  ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 598 },
/* 45  */ { Anim_PlaybackOnce, ANIM_STATUS(30, true),  false, ANIM_STATUS(30, true), { Q12(16.0f) }, 598, 611 },
/* 46  */ { Anim_BlendLinear,  ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 615 },
/* 47  */ { Anim_PlaybackOnce, ANIM_STATUS(31, true),  false, ANIM_STATUS(31, true), { Q12(16.0f) }, 615, 625 },
/* 48  */ { Anim_BlendLinear,  ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 579 },
/* 49  */ { Anim_PlaybackOnce, ANIM_STATUS(32, true),  false, ANIM_STATUS(32, true), { Q12(-35.0f) }, 568, 579 },

/* `EquippedWeaponId_Chainsaw` */
/* 50  */ { Anim_BlendLinear,  ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 51  */ { Anim_PlaybackOnce, ANIM_STATUS(28, true),  false, ANIM_STATUS(28, true), { Q12(15.0f)  }, 568, 583 },
/* 52  */ { Anim_BlendLinear,  ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 584 },
/* 53  */ { Anim_PlaybackOnce, ANIM_STATUS(29, true),  false, ANIM_STATUS(29, true), { Q12(16.0f)  }, 584, 602 },
/* 54  */ { Anim_BlendLinear,  ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 603 },
/* 55  */ { Anim_PlaybackOnce, ANIM_STATUS(30, true),  false, ANIM_STATUS(30, true), { Q12(14.0f)  }, 603, 618 },
/* 56  */ { Anim_BlendLinear,  ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 619 },
/* 57  */ { Anim_PlaybackOnce, ANIM_STATUS(31, true),  false, ANIM_STATUS(31, true), { Q12(14.0f)  }, 619, 637 },
/* 58  */ { Anim_BlendLinear,  ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 649 },
/* 59  */ { Anim_PlaybackOnce, ANIM_STATUS(32, true),  false, ANIM_STATUS(32, true), { Q12(-35.0f) }, 638, 649 },
/* 60  */ { Anim_BlendLinear,  ANIM_STATUS(33, false), false, ANIM_STATUS(33, true), { Q12(100.0f) }, NO_VALUE, 638 },
/* 61  */ { Anim_PlaybackOnce, ANIM_STATUS(33, true),  false, ANIM_STATUS(33, true), { Q12(24.0f)  }, 638, 649 },
/* 62  */ { Anim_BlendLinear,  ANIM_STATUS(34, false), false, ANIM_STATUS(34, true), { Q12(100.0f) }, NO_VALUE, 650 },
/* 63  */ { Anim_PlaybackLoop, ANIM_STATUS(34, true),  false, NO_VALUE,              { Q12(20.0f)  }, 650, 655 },

/* `EquippedWeaponId_RockDrill` */
/* 64  */ { Anim_BlendLinear,  ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 65  */ { Anim_PlaybackOnce, ANIM_STATUS(28, true),  false, ANIM_STATUS(28, true), { Q12(18.0f)  }, 568, 583 },
/* 66  */ { Anim_BlendLinear,  ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 584 },
/* 67  */ { Anim_PlaybackOnce, ANIM_STATUS(29, true),  false, ANIM_STATUS(29, true), { Q12(24.0f)  }, 584, 597 },
/* 68  */ { Anim_BlendLinear,  ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 598 },
/* 69  */ { Anim_PlaybackOnce, ANIM_STATUS(30, true),  false, ANIM_STATUS(30, true), { Q12(20.0f)  }, 598, 611 },
/* 70  */ { Anim_BlendLinear,  ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 612 },
/* 71  */ { Anim_PlaybackOnce, ANIM_STATUS(31, true),  false, ANIM_STATUS(31, true), { Q12(22.0f)  }, 612, 625 },
/* 72  */ { Anim_BlendLinear,  ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 636 },
/* 73  */ { Anim_PlaybackOnce, ANIM_STATUS(32, true),  false, ANIM_STATUS(32, true), { Q12(-25.0f) }, 626, 636 },
/* 74  */ { Anim_BlendLinear,  ANIM_STATUS(33, false), false, ANIM_STATUS(33, true), { Q12(100.0f) }, NO_VALUE, 626 },
/* 75  */ { Anim_PlaybackOnce, ANIM_STATUS(33, true),  false, ANIM_STATUS(33, true), { Q12(23.0f)  }, 626, 636 },
/* 76  */ { Anim_BlendLinear,  ANIM_STATUS(34, false), false, ANIM_STATUS(34, true), { Q12(100.0f) }, NO_VALUE, 637 },
/* 77  */ { Anim_PlaybackLoop, ANIM_STATUS(34, true),  false, NO_VALUE,              { Q12(24.0f)  }, 637, 640 },

/* `EquippedWeaponId_Handgun` */
/* 78  */ { Anim_BlendLinear,  ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 570 },
/* 79  */ { Anim_PlaybackOnce, ANIM_STATUS(28, true),  false, ANIM_STATUS(28, true), { Q12(35.0f)  }, 570, 579 },
/* 80  */ { Anim_BlendLinear,  ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 582 },
/* 81  */ { Anim_PlaybackOnce, ANIM_STATUS(29, true),  false, ANIM_STATUS(29, true), { Q12(40.0f)  }, 582, 592 },
/* 82  */ { Anim_BlendLinear,  ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 594 },
/* 83  */ { Anim_PlaybackOnce, ANIM_STATUS(30, true),  false, ANIM_STATUS(30, true), { Q12(25.0f)  }, 594, 604 },
/* 84  */ { Anim_BlendLinear,  ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 605 },
/* 85  */ { Anim_PlaybackOnce, ANIM_STATUS(31, true),  false, ANIM_STATUS(31, true), { Q12(30.0f)  }, 605, 658 },
/* 86  */ { Anim_BlendLinear,  ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 570 },
/* 87  */ { Anim_PlaybackOnce, ANIM_STATUS(32, true),  false, ANIM_STATUS(32, true), { Q12(60.0f)  }, 570, 592 },
/* 88  */ { Anim_BlendLinear,  ANIM_STATUS(33, false), false, ANIM_STATUS(33, true), { Q12(100.0f) }, NO_VALUE, 579 },
/* 89  */ { Anim_PlaybackOnce, ANIM_STATUS(33, true),  false, ANIM_STATUS(33, true), { Q12(-35.0f) }, 570, 579 },
/* 90  */ { Anim_BlendLinear,  ANIM_STATUS(34, false), false, ANIM_STATUS(34, true), { Q12(100.0f) }, NO_VALUE, 592 },
/* 91  */ { Anim_PlaybackOnce, ANIM_STATUS(34, true),  false, ANIM_STATUS(34, true), { Q12(-35.0f) }, 580, 592 },
/* 92  */ { Anim_BlendLinear,  ANIM_STATUS(35, false), false, ANIM_STATUS(35, true), { Q12(100.0f) }, NO_VALUE, 592 },
/* 93  */ { Anim_PlaybackOnce, ANIM_STATUS(35, true),  false, ANIM_STATUS(35, true), { Q12(-30.0f) }, 570, 592 },
/* 94  */ { Anim_BlendLinear,  ANIM_STATUS(36, false), false, ANIM_STATUS(36, true), { Q12(100.0f) }, NO_VALUE, 582 },
/* 95  */ { Anim_PlaybackOnce, ANIM_STATUS(36, true),  false, ANIM_STATUS(36, true), { Q12(25.0f)  }, 582, 604 },

/* `EquippedWeaponId_HuntingRifle` */
/* 96  */ { Anim_BlendLinear,  ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 97  */ { Anim_PlaybackOnce, ANIM_STATUS(28, true),  false, ANIM_STATUS(28, true), { Q12(35.0f)  }, 568, 587 },
/* 98  */ { Anim_BlendLinear,  ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 588 },
/* 99  */ { Anim_PlaybackOnce, ANIM_STATUS(29, true),  false, ANIM_STATUS(29, true), { Q12(25.0f)  }, 588, 597 },
/* 100 */ { Anim_BlendLinear,  ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 598 },
/* 101 */ { Anim_PlaybackOnce, ANIM_STATUS(30, true),  false, ANIM_STATUS(30, true), { Q12(16.0f)  }, 598, 607 },
/* 102 */ { Anim_BlendLinear,  ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 608 },
/* 103 */ { Anim_PlaybackOnce, ANIM_STATUS(31, true),  false, ANIM_STATUS(31, true), { Q12(20.0f)  }, 608, 642 },
/* 104 */ { Anim_BlendLinear,  ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 588 },
/* 105 */ { Anim_PlaybackOnce, ANIM_STATUS(32, true),  false, ANIM_STATUS(32, true), { Q12(25.0f)  }, 588, 597 },
/* 106 */ { Anim_BlendLinear,  ANIM_STATUS(33, false), false, ANIM_STATUS(33, true), { Q12(100.0f) }, NO_VALUE, 597 },
/* 107 */ { Anim_PlaybackOnce, ANIM_STATUS(33, true),  false, ANIM_STATUS(33, true), { Q12(-30.0f) }, 588, 597 },
/* 108 */ { Anim_BlendLinear,  ANIM_STATUS(34, false), false, ANIM_STATUS(34, true), { Q12(100.0f) }, NO_VALUE, 597 },
/* 109 */ { Anim_PlaybackOnce, ANIM_STATUS(34, true),  false, ANIM_STATUS(34, true), { Q12(-30.0f) }, 597, 597 },
/* 110 */ { Anim_BlendLinear,  ANIM_STATUS(35, false), false, ANIM_STATUS(35, true), { Q12(100.0f) }, NO_VALUE, 587 },
/* 111 */ { Anim_PlaybackOnce, ANIM_STATUS(35, true),  false, ANIM_STATUS(35, true), { Q12(-22.0f) }, 568, 587 },
/* 112 */ { Anim_BlendLinear,  ANIM_STATUS(36, false), false, ANIM_STATUS(36, true), { Q12(100.0f) }, NO_VALUE, 598 },
/* 113 */ { Anim_PlaybackOnce, ANIM_STATUS(36, true),  false, ANIM_STATUS(36, true), { Q12(16.0f)  }, 598, 607 },

/* `EquippedWeaponId_Shotgun` */
/* 114 */ { Anim_BlendLinear,  ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 570 },
/* 115 */ { Anim_PlaybackOnce, ANIM_STATUS(28, true),  false, ANIM_STATUS(28, true), { Q12(40.0f)  }, 570, 579 },
/* 116 */ { Anim_BlendLinear,  ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 582 },
/* 117 */ { Anim_PlaybackOnce, ANIM_STATUS(29, true),  false, ANIM_STATUS(29, true), { Q12(30.0f)  }, 582, 592 },
/* 118 */ { Anim_BlendLinear,  ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 594 },
/* 119 */ { Anim_PlaybackOnce, ANIM_STATUS(30, true),  false, ANIM_STATUS(30, true), { Q12(22.0f)  }, 594, 604 },
/* 120 */ { Anim_BlendLinear,  ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 605 },
/* 121 */ { Anim_PlaybackOnce, ANIM_STATUS(31, true),  false, ANIM_STATUS(31, true), { Q12(17.0f)  }, 605, 641 },
/* 122 */ { Anim_BlendLinear,  ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 570 },
/* 123 */ { Anim_PlaybackOnce, ANIM_STATUS(32, true),  false, ANIM_STATUS(32, true), { Q12(60.0f)  }, 570, 592 },
/* 124 */ { Anim_BlendLinear,  ANIM_STATUS(33, false), false, ANIM_STATUS(33, true), { Q12(100.0f) }, NO_VALUE, 579 },
/* 125 */ { Anim_PlaybackOnce, ANIM_STATUS(33, true),  false, ANIM_STATUS(33, true), { Q12(-40.0f) }, 570, 579 },
/* 126 */ { Anim_BlendLinear,  ANIM_STATUS(34, false), false, ANIM_STATUS(34, true), { Q12(100.0f) }, NO_VALUE, 592 },
/* 127 */ { Anim_PlaybackOnce, ANIM_STATUS(34, true),  false, ANIM_STATUS(34, true), { Q12(-40.0f) }, 580, 592 },
/* 128 */ { Anim_BlendLinear,  ANIM_STATUS(35, false), false, ANIM_STATUS(35, true), { Q12(100.0f) }, NO_VALUE, 592 },
/* 129 */ { Anim_PlaybackOnce, ANIM_STATUS(35, true),  false, ANIM_STATUS(35, true), { Q12(-20.0f) }, 570, 592 },
/* 130 */ { Anim_BlendLinear,  ANIM_STATUS(36, false), false, ANIM_STATUS(36, true), { Q12(100.0f) }, NO_VALUE, 582 },
/* 131 */ { Anim_PlaybackOnce, ANIM_STATUS(36, true),  false, ANIM_STATUS(36, true), { Q12(22.0f)  }, 582, 604 },

/* `EquippedWeaponId_HyperBlaster` */
/* 132 */ { Anim_BlendLinear,  ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 133 */ { Anim_PlaybackOnce, ANIM_STATUS(28, true),  false, ANIM_STATUS(28, true), { Q12(24.0f)  }, 568, 574 },
/* 134 */ { Anim_BlendLinear,  ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 574 },
/* 135 */ { Anim_PlaybackOnce, ANIM_STATUS(29, true),  false, ANIM_STATUS(29, true), { Q12(20.0f)  }, 574, 574 },
/* 136 */ { Anim_BlendLinear,  ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 575 },
/* 137 */ { Anim_PlaybackOnce, ANIM_STATUS(30, true),  false, ANIM_STATUS(30, true), { Q12(20.0f)  }, 575, 579 },
/* 138 */ { Anim_BlendLinear,  ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 139 */ { Anim_PlaybackOnce, ANIM_STATUS(31, true),  false, ANIM_STATUS(31, true), { Q12(17.0f)  }, 568, 568 },
/* 140 */ { Anim_BlendLinear,  ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 141 */ { Anim_PlaybackOnce, ANIM_STATUS(32, true),  false, ANIM_STATUS(32, true), { Q12(24.0f)  }, 568, 574 },
/* 142 */ { Anim_BlendLinear,  ANIM_STATUS(33, false), false, ANIM_STATUS(33, true), { Q12(100.0f) }, NO_VALUE, 574 },
/* 143 */ { Anim_PlaybackOnce, ANIM_STATUS(33, true),  false, ANIM_STATUS(33, true), { Q12(-20.0f) }, 568, 574 },
/* 144 */ { Anim_BlendLinear,  ANIM_STATUS(34, false), false, ANIM_STATUS(34, true), { Q12(100.0f) }, NO_VALUE, 574 },
/* 145 */ { Anim_PlaybackOnce, ANIM_STATUS(34, true),  false, ANIM_STATUS(34, true), { Q12(-20.0f) }, 574, 574 },
/* 146 */ { Anim_BlendLinear,  ANIM_STATUS(35, false), false, ANIM_STATUS(35, true), { Q12(100.0f) }, NO_VALUE, 574 },
/* 147 */ { Anim_PlaybackOnce, ANIM_STATUS(35, true),  false, ANIM_STATUS(35, true), { Q12(-20.0f) }, 568, 574 },
/* 148 */ { Anim_BlendLinear,  ANIM_STATUS(36, false), false, ANIM_STATUS(36, true), { Q12(100.0f) }, NO_VALUE, 574 },
/* 149 */ { Anim_PlaybackOnce, ANIM_STATUS(36, true),  false, ANIM_STATUS(36, true), { Q12(20.0f)  }, 574, 579 }
};

// Unused data?
INCLUDE_RODATA("bodyprog/nonmatchings/collision", D_800294F4);
