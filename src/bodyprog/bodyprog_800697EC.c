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
#include "bodyprog/player_logic.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"

s_800C4478 D_800C4478;

// ========================================
// ENVIRONMENT AND SCREEN GFX 3
// ========================================

void func_800697EC(void) // 0x800697EC
{
    func_80069820(1);
    D_800C4478.field_2 = 0;
}

u16 func_80069810(void) // 0x80069810
{
    return D_800C4478.field_0;
}

void func_80069820(u16 flags) // 0x80069820
{
    D_800C4478.field_0 = flags;
}

void func_8006982C(u16 flags) // 0x8006982C
{
    D_800C4478.field_0 |= flags;
}

void func_80069844(s32 arg0) // 0x80069844
{
    D_800C4478.field_0 = (D_800C4478.field_0 & ~arg0) | (1 << 0);
}

void func_80069860(s32 arg0, s32 arg1, s_func_8006F8FC* arg2) // 0x80069860
{
    s_func_8006F8FC* ptr;
    q19_12           minX;
    q19_12           maxX;
    q19_12           minZ;
    q19_12           maxZ;

    D_800C4478.field_2 = 0;

    for (ptr = arg2; !ptr->endOfArray_0_0; ptr++)
    {
        minX = FP_TO(ptr->positionX_0_1, Q12_SHIFT);
        maxX = FP_TO(ptr->positionX_0_1 + ptr->sizeX_0_21, Q12_SHIFT);
        minZ = FP_TO(ptr->positionZ_0_11, Q12_SHIFT);
        maxZ = FP_TO(ptr->positionZ_0_11 + ptr->sizeZ_0_25, Q12_SHIFT);

        minX -= Q12(16.0f);
        maxX += Q12(16.0f);
        minZ -= Q12(16.0f);
        maxZ += Q12(16.0f);

        if (arg0 >= minX && maxX >= arg0 &&
            arg1 >= minZ && maxZ >= arg1)
        {
            D_800C4478.field_4[D_800C4478.field_2] = ptr;
            D_800C4478.field_2++;
        }
    }
}

// ========================================
// COLLISION HANDLING
// ========================================

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
    s32* ptr;

    collData->field_30++;
    if (collData->field_30 > 252)
    {
        collData->field_30 = 0;

        // TODO: Is this `memset`/`bzero`?
        for (ptr = &collData->field_34[0]; ptr < &collData->field_34[256]; ptr++)
        {
            *ptr = 0;
        }
    }
}

void func_800699E4(s_IpdCollisionData* collData) // 0x800699E4
{
    collData->field_30++;
}

void Collision_Get(s_Collision* coll, q19_12 posX, q19_12 posZ) // 0x800699F8
{
    s_func_8006AB50     sp10;
    VECTOR3             pos;
    s_func_8006CC44     sp38;
    s_IpdCollisionData* ipdCollData;

    pos.vx = Q12(0.0f);
    pos.vy = Q12(0.0f);
    pos.vz = Q12(0.0f);

    ipdCollData = func_800426E4(posX, posZ);
    if (ipdCollData == NULL)
    {
        coll->groundHeight_0 = Q12(8.0f);
        coll->field_6        = 0;
        coll->field_4        = 0;
        coll->field_8        = 0;
        return;
    }

    sp10.position_0.vx = posX;
    sp10.position_0.vy = Q12(0.0f);
    sp10.position_0.vz = posZ;
    sp10.rotation_C.vx = Q12_ANGLE(0.0f);
    sp10.rotation_C.vy = Q12_ANGLE(0.0f);
    sp10.rotation_C.vz = Q12_ANGLE(0.0f);
    func_8006AB50(&sp38, &pos, &sp10, 0);

    sp38.field_0_8  = 0;
    sp38.field_0_9  = 0;
    sp38.field_0_10 = 1;
    func_8006AD44(&sp38, ipdCollData);

    if (sp38.field_90 == 1)
    {
        coll->field_8        = 0;
        coll->groundHeight_0 = Q12(8.0f);
    }
    else
    {
        coll->field_8        = sp38.field_94;
        coll->groundHeight_0 = Q8_TO_Q12(func_8006CC44(sp38.field_4.positionX_18, sp38.field_4.positionZ_1C, &sp38));
    }

    coll->field_4 = sp38.field_88;
    coll->field_6 = sp38.field_8C;
}

s32 func_80069B24(s_800C4590* arg0, VECTOR3* offset, s_SubCharacter* chara) // 0x80069B24
{
    s32 var0;
    s32 var1;

    var0 = SetSp(0x1F8003D8);
    var1 = func_80069BA8(arg0, offset, chara, func_80069FFC(arg0, offset, chara));
    SetSp(var0);
    return var1;
}

s32 func_80069BA8(s_800C4590* arg0, VECTOR3* offset, s_SubCharacter* chara, s32 arg4) // 0x80069BA8
{
    #define POINT_COUNT          9
    #define ANGLE_STEP           Q12_ANGLE(370.0f / POINT_COUNT) // @bug? Maybe `360.0f` was intended.
    #define WALL_COUNT_THRESHOLD 3                              // Unknown purpose.
    #define WALL_HEIGHT          Q12(0.5f)

    s_Collision     coll;
    e_CollisionType collType;
    s32             groundHeight;
    q19_12          wallHeightBound;
    s32             i;
    s32             wallCount;
    s32             var_s6;

    if (arg4 == NO_VALUE)
    {
        arg4 = 1;
        if (chara == &g_SysWork.playerWork_4C && chara->health_B0 > Q12(0.0f))
        {
            func_80069DF0(arg0, &chara->position_18, chara->position_18.vy, chara->rotation_24.vy);
        }
    }

    switch (chara->model_0.charaId_0)
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
            wallHeightBound = chara->position_18.vy - WALL_HEIGHT;

            switch (arg0->field_14)
            {
                case 12:
                    collType = CollisionType_Unk2;
                    break;

                default:
                    collType = (arg0->field_C < wallHeightBound) ? CollisionType_Wall : CollisionType_None;
                    break;
            }

            wallCount = 0;
            if (collType == CollisionType_None)
            {
                break;
            }

            for (i = 0, var_s6 = 12; i < POINT_COUNT; i++)
            {
                Collision_Get(&coll,
                              chara->position_18.vx + Q12_MULT(Math_Sin(i * ANGLE_STEP), Q12(0.2f)),
                              chara->position_18.vz + Q12_MULT(Math_Cos(i * ANGLE_STEP), Q12(0.2f)));

                switch (collType)
                {
                    case CollisionType_Wall:
                        if (coll.groundHeight_0 < wallHeightBound)
                        {
                            wallCount++;
                        }
                        break;

                    case CollisionType_Unk2:
                        if (coll.field_8 != 12)
                        {
                            var_s6 = coll.field_8;
                            groundHeight = coll.groundHeight_0;
                        }
                        break;
                }
            }

            switch (collType)
            {
                case 1:
                    if (wallCount < WALL_COUNT_THRESHOLD)
                    {
                        arg0->field_C = chara->position_18.vy;
                    }
                    break;

                case 2:
                    if (var_s6 != 12)
                    {
                        arg0->field_C  = groundHeight;
                        arg0->field_14 = 12;
                    }
                    break;
            }
            break;
    }

    return arg4;
}

static const u8 unk_rdata[] = { 0, 66, 5, 128, 0, 0, 0, 0 };

void func_80069DF0(s_800C4590* arg0, VECTOR3* pos, s32 arg2, s32 arg3) // 0x80069DF0
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
    s32         var_s5;

    groundHeightMin = Q12(-30.0f);
    groundHeightMax = Q12(30.0f);
    var_s5 = 0;

    // Collect ground heights around position?
    for (i = 0; i < POINT_COUNT; i++)
    {
        Collision_Get(&coll,
                      pos->vx + Math_Sin((arg3 & 0xF) + (i * ANGLE_STEP)),
                      pos->vz + Math_Cos((arg3 & 0xF) + (i * ANGLE_STEP)));
        groundHeights[i] = coll.groundHeight_0;

        if (groundHeightMin < coll.groundHeight_0)
        {
            groundHeightMin = coll.groundHeight_0;
            var_s5 = i;
        }

        if (coll.groundHeight_0 < groundHeightMax)
        {
            groundHeightMax = coll.groundHeight_0;
        }
    }

    groundHeight = (groundHeightMin + groundHeightMax) >> 1; // `/ 2`.
    if (groundHeight < (arg2 - Q12(0.1f)))
    {
        groundHeight = arg2 - Q12(0.1f);
    }

    for (i = var_s5 + 1, var_a0 = var_s5;
         i < (var_s5 + POINT_COUNT) && groundHeight < groundHeights[i & 0xF];
         i++)
    {
        var_a0 = i;
    }

    for (i = var_s5 - 1, var_s0 = var_s5;
         i < (var_s5 - POINT_COUNT) && groundHeight < groundHeights[i & 0xF];
         i--)
    {
        var_s0 = i;
    }

    angle = ((var_s0 + var_a0) << 8) >> 1;
    arg0->offset_0.vx = Q12_MULT_PRECISE(Math_Sin(angle), Q12(1.0f / 16.0f));
    arg0->offset_0.vz = Q12_MULT_PRECISE(Math_Cos(angle), Q12(1.0f / 16.0f));
}

s32 func_80069FFC(s_800C4590* arg0, VECTOR3* offset, s_SubCharacter* chara) // 0x80069FFC
{
    s_func_8006AB50 sp28;
    VECTOR3         offsetSpy;
    s32             collDataIdx;
    s32             charaCount;
    s32             var_s1; // TODO: Maybe `bool`?

    sp28.position_0.vx = chara->position_18.vx + chara->field_D8.offsetX_4;
    sp28.position_0.vy = chara->position_18.vy - Q12(0.02f);
    sp28.position_0.vz = chara->position_18.vz + chara->field_D8.offsetZ_6;

    if (func_800426E4(chara->position_18.vx, chara->position_18.vz) == NULL)
    {
        func_8006A178(arg0, Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(8.0f));
        return 1;
    }

    sp28.rotation_C.vy = chara->field_C8.field_0;
    sp28.rotation_C.vx = chara->field_C8.field_2;
    sp28.rotation_C.vz = chara->field_D4.radius_0;

    sp28.field_12 = chara->field_E1_0;

    offsetSpy = *offset;

    switch (chara->model_0.charaId_0)
    {
        case Chara_Harry:
        case Chara_Groaner:
        case Chara_Wormhead:
        case Chara_Romper:
            var_s1 = 1;
            break;

        default:
            var_s1 = 0;
            break;
    }

    return func_8006A4A8(arg0, &offsetSpy, &sp28, var_s1, func_800425D8(&collDataIdx), collDataIdx, NULL, 0, func_8006A1A4(&charaCount, chara, true), charaCount);
}

void func_8006A178(s_800C4590* arg0, q19_12 posX, q19_12 posY, q19_12 posZ, q19_12 heightY) // 0x8006A178
{
    arg0->offset_0.vx = posX;
    arg0->offset_0.vy = posY;
    arg0->offset_0.vz = posZ;
    arg0->field_12    = 0;
    arg0->field_10    = 0;
    arg0->field_14    = 0;
    arg0->field_18    = 0xFFFF0000;
    arg0->field_C     = heightY;
}

s_SubCharacter** func_8006A1A4(s32* charaCount, s_SubCharacter* chara, bool arg2) // 0x8006A1A4
{
    s_SubCharacter* curChara;
    static s_SubCharacter* D_800C4458[7];
    static s_SubCharacter** D_800C4474; /** Array of active characters? */

    if (chara != NULL &&
        (chara->model_0.charaId_0 == Chara_None || chara->field_E1_0 == 0 ||
        (chara->field_E1_0 == 1 && arg2 == true)))
    {
        *charaCount = 0;
        return &D_800C4458;
    }

    *charaCount = 0;
    D_800C4474 = &D_800C4458;

    for (curChara = &g_SysWork.npcs_1A0[0]; curChara < &g_SysWork.npcs_1A0[ARRAY_SIZE(g_SysWork.npcs_1A0)]; curChara++)
    {
        if (curChara->model_0.charaId_0 != Chara_None)
        {
            if (curChara->field_E1_0 != 0 &&
                (curChara->field_E1_0 != 1 || arg2 != true) &&
                curChara != chara &&
                (arg2 != true || chara == NULL || chara->field_E1_0 != 4 || curChara->field_E1_0 >= chara->field_E1_0))
            {
                *charaCount += 1;
                *D_800C4474 = curChara;
                D_800C4474++;
                curChara->field_E0 = 0;
            }
        }
    }

    curChara = &g_SysWork.playerWork_4C.player_0;
    if (curChara->model_0.charaId_0 != Chara_None)
    {
        if (curChara->field_E1_0 != 0 &&
            (curChara->field_E1_0 != 1 || arg2 != true) &&
            curChara != chara &&
            (arg2 != true || chara == NULL || chara->field_E1_0 != 4 || curChara->field_E1_0 >= chara->field_E1_0))
        {
            *charaCount += 1;
            *D_800C4474 = curChara;
            D_800C4474++;
            curChara->field_E0 = 0;
        }
    }

    return &D_800C4458;
}

s32 func_8006A3B4(s32 arg0, VECTOR* offset, s_func_8006AB50* arg2) // 0x8006A3B4
{
    s32 stackPtr;
    s32 var1;

    stackPtr = SetSp(0x1F8003D8);
    var1 = func_8006A42C(arg0, offset, arg2);
    SetSp(stackPtr);

    if (var1 == NO_VALUE)
    {
        var1 = 1;
    }

    return var1;
}

s32 func_8006A42C(s32 arg0, VECTOR3* offset, s_func_8006AB50* arg2) // 0x8006A42C
{
    VECTOR3 offsetCpy;
    s32     collDataIdx;

    offsetCpy = *offset;

    return func_8006A4A8(arg0, &offsetCpy, arg2, 0, func_800425D8(&collDataIdx), collDataIdx, NULL, 0, NULL, 0);
}

s32 func_8006A4A8(s_800C4590* arg0, VECTOR3* offset, s_func_8006AB50* arg2, s32 arg3,
                  s_IpdCollisionData** collDataPtrs, s32 collDataIdx, s_func_8006CF18* arg6, s32 arg7, s_SubCharacter** charas, s32 charaCount) // 0x8006A4A8
{
    s_func_8006CC44      sp18;
    VECTOR3              sp120; // Q19.12
    VECTOR3              sp130;
    VECTOR3              offsetCpy;
    s32                  var_a0;
    s32                  i;
    s32                  var_s4;
    s32                  var_v0;
    s32                  count;
    s_SubCharacter**     curChara;
    s_IpdCollisionData** curCollData;
    s_SubCharacter*      chara;

    var_s4 = 0;

    if (arg2->field_12 == 5)
    {
        func_8006A178(arg0, offset->vx, offset->vy, offset->vz, arg2->position_0.vy);
        return 0;
    }

    func_8006A940(offset, arg2, charas, charaCount);

    offsetCpy = *offset;

    arg0->field_18 = func_8006F620(&offsetCpy, arg2, arg2->rotation_C.vz, arg2->rotation_C.vy);

    func_8006AB50(&sp18, &offsetCpy, arg2, arg3);

    sp130 = offsetCpy;

    arg0->offset_0.vz = Q12(0.0f);
    arg0->offset_0.vx = Q12(0.0f);
    arg0->offset_0.vy = offsetCpy.vy;

    while (true)
    {
        if (sp18.field_0_0 != 0)
        {
            sp18.field_0_8  = sp18.field_4.field_8 != 0;
            sp18.field_0_9  = 0;
            sp18.field_0_10 = 0;
        }
        else
        {
            sp18.field_0_8  = sp18.field_4.field_8 != 0;
            sp18.field_0_9  = 1;
            sp18.field_0_10 = 1;
        }

        // Run through collision data.
        for (curCollData = collDataPtrs; curCollData < &collDataPtrs[collDataIdx]; curCollData++)
        {
            func_8006AD44(&sp18, *curCollData);
        }

        if (sp18.field_44.field_0.field_0 && sp18.field_44.field_0.field_2.vx == sp18.field_44.field_0.field_2.vy)
        {
            var_s4 |= 1;
        }

        func_8006CF18(&sp18, arg6, arg7);

        // Run through characters.
        for (curChara = charas; curChara < &charas[charaCount]; curChara++)
        {
            chara  = *curChara;
            var_a0 = (chara->field_D4.radius_0 >> 4) + sp18.field_4.field_28;

            if (chara->field_E1_0 < (u32)sp18.field_4.field_0)
            {
                var_a0 -= 15;
            }

            sp18.field_98.field_0 = Q12_TO_Q8(chara->position_18.vx + chara->field_D8.offsetX_4);
            sp18.field_9C.field_0 = Q12_TO_Q8(chara->position_18.vz + chara->field_D8.offsetZ_6);

            sp18.field_A0.s_1.field_0 = Q12_TO_Q8(chara->field_C8.field_0 + chara->position_18.vy);
            sp18.field_A0.s_1.field_2 = Q12_TO_Q8(chara->field_C8.field_2 + chara->position_18.vy);
            sp18.field_A0.s_1.field_4 = var_a0;
            sp18.field_A0.s_1.field_6 = chara->field_E1_0;
            sp18.field_A0.s_1.field_8 = &chara->field_E0;

            if (sp18.field_0_0 == 0)
            {
                chara->field_E0 = 0;
            }

            func_8006CC9C(&sp18);
            func_8006CF18(&sp18, chara->field_E4, chara->field_E1_4);
        }

        func_8006D01C(&sp120, &sp130, func_8006CB90(&sp18), &sp18);

        arg0->offset_0.vx += sp120.vx;
        arg0->offset_0.vz += sp120.vz;

        if (sp18.field_0_0)
        {
            break;
        }

        if (sp18.field_44.field_0.field_0 || sp18.field_44.field_30.field_0)
        {
            count = 8;
            if (sp18.field_44.field_8.field_0 < 9)
            {
                count = sp18.field_44.field_8.field_0;
            }

            for (i = 0; i < count; i++)
            {
                *sp18.field_44.field_10[i] += 1;
            }
        }
        else if (sp18.field_34)
        {
            *sp18.field_40 += 1;
        }
        else
        {
            break;
        }

        sp18.field_0_0 = 1;
        func_8006D774(&sp18, &sp120, &sp130);
    }

    if (sp18.field_90 == 1)
    {
        var_v0         = Q12(8.0f);
        arg0->field_14 = 0;
    }
    else
    {
        arg0->field_14 = sp18.field_94;
        var_v0         = func_8006CC44(sp18.field_4.positionX_18 + Q12_TO_Q8(sp120.vx), sp18.field_4.positionZ_1C + Q12_TO_Q8(sp120.vz), &sp18) * 16;
    }

    arg0->field_C  = var_v0;
    arg0->field_10 = sp18.field_88;
    arg0->field_12 = sp18.field_8C;

    if (var_s4 != 0)
    {
        return NO_VALUE;
    }

    return sp18.field_0_0 != 0;
}

void func_8006A940(VECTOR3* offset, s_func_8006AB50* arg1, s_SubCharacter** charas, s32 charaCount) // 0x8006A940
{
    s32             angle;
    s32             posZ;
    s32             posX;
    s32             var_a0;
    s32             i;
    s32             var_s4;
    s32             var_v0;
    s32             temp2;
    s32             temp3;
    s32             temp4;
    s32             temp5;
    s32             temp6;
    s_SubCharacter* curChara;

    var_s4 = Q12(1.0f);
    angle  = ratan2(offset->vx, offset->vz);

    for (i = 0; i < charaCount; i++)
    {
        curChara = charas[i];
        if (!curChara->field_E1_0 || curChara->field_E1_0 == (1 << 0) || curChara->field_E1_0 >= arg1->field_12)
        {
            continue;
        }

        temp3 = curChara->field_C8.field_0 + curChara->position_18.vy;
        temp4 = curChara->field_C8.field_2 + curChara->position_18.vy;

        // TODO: Rotation + position? Seems wrong.
        temp6 = arg1->rotation_C.vy + arg1->position_0.vy;
        temp5 = arg1->rotation_C.vx + arg1->position_0.vy;
        if (temp3 > temp5 || temp4 < temp6)
        {
            continue;
        }

        posX = (curChara->position_18.vx + curChara->field_D8.offsetX_4) - arg1->position_0.vx;
        posZ = (curChara->position_18.vz + curChara->field_D8.offsetZ_6) - arg1->position_0.vz;

        temp2 = Vc_VectorMagnitudeCalc(posX, Q12(0.0f), posZ);
        if (((curChara->field_D4.radius_0 + arg1->rotation_C.vz) + Q12_ANGLE(36.0f)) < temp2)
        {
            continue;
        }

        var_a0 = Q12_MULT(Math_Cos(ratan2(posX, posZ) - angle), Q12(1.5f));

        var_v0 = MAX(var_a0, 0);
        var_a0 = var_v0;

        // Radius calc?
        if (curChara->model_0.charaId_0 == Chara_HangedScratcher)
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

void func_8006AB50(s_func_8006CC44* arg0, VECTOR3* pos, s_func_8006AB50* arg2, s32 arg3) // 0x8006AB50
{
    arg0->field_0_0       = 0;
    arg0->field_2         = D_800C4478.field_0;
    arg0->field_4.field_4 = arg3;

    func_8006ABC0(&arg0->field_4, pos, arg2);

    arg0->field_7C = 0x1E00;
    arg0->field_34 = 0;
    arg0->field_44.field_0.field_0  = 0;
    arg0->field_44.field_6          = 0;
    arg0->field_44.field_8.field_0  = 0;
    arg0->field_44.field_36         = 0;
    arg0->field_44.field_30.field_0 = 0;
    arg0->field_8C = 0;
    arg0->field_88 = 0;
    arg0->field_90 = 1;
    arg0->field_94 = 0;
}

void func_8006ABC0(s_func_8006ABC0* result, VECTOR3* pos, s_func_8006AB50* arg2) // 0x8006ABC0
{
    q3_12 angleXz;

    result->field_C.vx = Q12_TO_Q8(pos->vx);
    result->field_C.vy = Q12_TO_Q8(pos->vy);
    result->field_C.vz = Q12_TO_Q8(pos->vz);

    result->field_8 = SquareRoot0(SQUARE(result->field_C.vx) + SQUARE(result->field_C.vz));

    if (result->field_8 != 0)
    {
        // @unused
        result->direction_14.vx = Q12(result->field_C.vx) / result->field_8;
        result->direction_14.vz = Q12(result->field_C.vz) / result->field_8;

        angleXz                 = ratan2(result->field_C.vz, result->field_C.vx);
        result->direction_14.vx = Math_Cos(angleXz);
        result->direction_14.vz = Math_Sin(angleXz);
    }
    else
    {
        result->direction_14.vx = Q12(1.0f);
        result->direction_14.vz = Q12(0.0f);
    }

    result->field_28     = FP_FROM(arg2->rotation_C.vz, Q4_SHIFT); // TODO: Packed angle?
    result->positionX_18 = Q12_TO_Q8(arg2->position_0.vx);
    result->positionZ_1C = Q12_TO_Q8(arg2->position_0.vz);
    result->field_20     = result->positionX_18 + result->field_C.vx;
    result->field_24     = result->positionZ_1C + result->field_C.vz;
    result->field_2A     = FP_FROM(arg2->rotation_C.vy + arg2->position_0.vy, Q4_SHIFT); // TODO: Position + rotation? Seems wrong.
    result->field_2C     = FP_FROM(arg2->rotation_C.vx + arg2->position_0.vy, Q4_SHIFT);
    result->field_0      = arg2->field_12;
}

void func_8006AD44(s_func_8006CC44* arg0, s_IpdCollisionData* collData) // 0x8006AD44
{
    s32                    endIdx;
    s32                    startIdx;
    s32                    i;
    s32                    j;
    s_IpdCollisionData_20* curUnk;

    if ((collData->field_8_8 == 0 && collData->field_8_16 == 0 && collData->field_8_24 == 0) ||
        !func_8006AEAC(arg0, collData))
    {
        return;
    }

    if (arg0->field_0_0 == 0)
    {
        func_80069994(collData);
    }

    startIdx = arg0->field_A0.s_0.field_0;
    endIdx   = (arg0->field_A0.s_0.field_0 + arg0->field_A0.s_0.field_2) - 1;

    for (i = arg0->field_A0.s_0.field_1; i < (arg0->field_A0.s_0.field_1 + arg0->field_A0.s_0.field_3); i++)
    {
        curUnk = &collData->ptr_20[(i * collData->field_1E) + startIdx];

        for (j = startIdx; j <= endIdx; j++, curUnk++)
        {
            func_8006B1C8(arg0, collData, curUnk);
        }
    }

    if (arg0->field_0_0 == 0)
    {
        func_800699E4(collData);
    }

    if (arg0->field_0_10)
    {
        func_8006C838(arg0, collData);
        if (arg0->field_A0.s_0.field_4 != NULL)
        {
            func_8006CA18(arg0, collData, arg0->field_A0.s_0.field_4);
        }
    }
}

bool func_8006AEAC(s_func_8006CC44* arg0, s_IpdCollisionData* collData) // 0x8006AEAC
{
    s_func_8006CC44_A8* curUnk;

    if (!func_8006B004(arg0, collData))
    {
        return false;
    }

    arg0->field_98.vec_0.vx = arg0->field_4.positionX_18 - collData->positionX_0;
    arg0->field_98.vec_0.vz = arg0->field_4.positionZ_1C - collData->positionZ_4;
    arg0->field_9C.vec_0.vx = arg0->field_4.field_20 - collData->positionX_0;
    arg0->field_9C.vec_0.vz = arg0->field_4.field_24 - collData->positionZ_4;

    if ((arg0->field_98.vec_0.vx / collData->field_1C) < 0 || (arg0->field_98.vec_0.vx / collData->field_1C) >= collData->field_1E ||
        ((arg0->field_98.vec_0.vz / collData->field_1C) < 0) || (arg0->field_98.vec_0.vz / collData->field_1C) >= collData->field_1F)
    {
        arg0->field_A0.s_0.field_4 = NULL;
        return true;
    }

    arg0->field_A0.s_0.field_4 = (s_func_8006CA18*)&collData->ptr_20[((arg0->field_98.vec_0.vz / collData->field_1C) * collData->field_1E) +
                                                                     (arg0->field_98.vec_0.vx / collData->field_1C)];
    arg0->field_C8             = UCHAR_MAX;

    for (curUnk = arg0->field_A0.s_0.field_8; curUnk < &arg0->field_C8; curUnk++)
    {
        curUnk->field_0 = 0;
        curUnk->field_1 = UCHAR_MAX;
        curUnk->field_4 = INT_MAX;
    }

    return true;
}

bool func_8006B004(s_func_8006CC44* arg0, s_IpdCollisionData* collData) // 0x8006B004
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

    var_a3 = arg0->field_4.positionX_18 - collData->positionX_0;
    var_t0 = arg0->field_4.field_20 - collData->positionX_0;
    if (var_t0 < var_a3)
    {
        var_t0 ^= var_a3;
        var_a3 ^= var_t0;
        var_t0 ^= var_a3;
    }

    var_a3 -= arg0->field_4.field_28;
    var_t0 += arg0->field_4.field_28;

    var_a0 = arg0->field_4.positionZ_1C - collData->positionZ_4;
    var_a2 = arg0->field_4.field_24 - collData->positionZ_4;
    if (var_a2 < var_a0)
    {
        var_a2 ^= var_a0;
        var_a0 ^= var_a2;
        var_a2 ^= var_a0;
    }

    var_a0 -= arg0->field_4.field_28;
    var_a2 += arg0->field_4.field_28;

    if (temp_lo < var_a3 || temp_lo_2 < var_a0 || var_t0 < 0 || var_a2 < 0)
    {
        return false;
    }

    var_a3 = limitRange(var_a3, 0, temp_t3);
    var_a0 = limitRange(var_a0, 0, temp_t4);
    var_t0 = limitRange(var_t0, 0, temp_t3);
    var_a2 = limitRange(var_a2, 0, temp_t4);

    arg0->field_A0.s_0.field_0 = var_a3 / collData->field_1C;
    arg0->field_A0.s_0.field_1 = var_a0 / collData->field_1C;
    arg0->field_A0.s_0.field_2 = ((var_t0 / collData->field_1C) - arg0->field_A0.s_0.field_0) + 1;
    arg0->field_A0.s_0.field_3 = ((var_a2 / collData->field_1C) - arg0->field_A0.s_0.field_1) + 1;

    return true;
}

void func_8006B1C8(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s_IpdCollisionData_20* arg2) // 0x8006B1C8
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
                if (func_8006B318(arg0, collData, idx))
                {
                    if (arg0->field_0_10)
                    {
                        func_8006B6E8(arg0, arg2);
                    }

                    if (arg0->field_0_8 || arg0->field_0_9)
                    {
                        if (arg0->field_CC.field_C.s_field_0.field_1 == 0xFF)
                        {
                            func_8006B9C8(arg0);
                        }

                        if (arg0->field_CC.field_C.s_field_0.field_0 == 0xFF)
                        {
                            func_8006B8F8(&arg0->field_CC);
                            func_8006B9C8(arg0);
                        }
                    }
                }
            }
            else if (func_8006C3D4(arg0, collData, idx))
            {
                func_8006C45C(arg0);
            }
        }
    }
}

bool func_8006B318(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s32 idx) // 0x8006B318
{
    s32                    temp_a0_5;
    s32                    temp_s0;
    s32                    temp_v0;
    s_IpdCollisionData_10* temp_a0;
    s_IpdCollisionData_14* temp_a3;

    temp_a3 = &collData->ptr_14[idx];

    if (!((arg0->field_2 >> (temp_a3->field_0_14 * 4 | temp_a3->field_2_14)) & (1 << 0)))
    {
        return false;
    }

    arg0->field_CC.ipdCollisionData_0 = collData;
    arg0->field_CC.field_4 = idx;

    arg0->field_CC.field_6.vx = temp_a3->field_0_0;
    arg0->field_CC.field_6.vy = temp_a3->field_2_0;
    arg0->field_CC.field_6.vz = temp_a3->field_4;

    arg0->field_CC.field_12 = collData->ptr_C[temp_a3->field_7];
    arg0->field_CC.field_18 = collData->ptr_C[temp_a3->field_6];

    arg0->field_CC.field_C.s_field_0.field_0 = temp_a3->field_8;

    if ((arg0->field_CC.field_C.s_field_0.field_0) != 0xFF)
    {
        temp_a0                 = &collData->ptr_10[arg0->field_CC.field_C.s_field_0.field_0];
        arg0->field_CC.field_E  = temp_a0->field_6_8;
        arg0->field_CC.field_10 = temp_a0->field_6_5;

        if (arg0->field_4.field_4 && (temp_a0->field_6_5 == 1 || temp_a0->field_6_0 == 12))
        {
            arg0->field_CC.field_12.vy -= Q12(1.0f);
            arg0->field_CC.field_18.vy -= Q12(1.0f);
        }
    }

    arg0->field_CC.field_C.s_field_0.field_1 = temp_a3->field_9;

    if ((arg0->field_CC.field_C.s_field_0.field_1) != 0xFF)
    {
        temp_a0                 = &collData->ptr_10[arg0->field_CC.field_C.s_field_0.field_1];
        arg0->field_CC.field_F  = temp_a0->field_6_8;
        arg0->field_CC.field_11 = temp_a0->field_6_5;

        if (arg0->field_4.field_4 && (temp_a0->field_6_5 == 1 || temp_a0->field_6_0 == 12))
        {
            arg0->field_CC.field_12.vy = Q12(-1.0f);
            arg0->field_CC.field_18.vy = Q12(-1.0f);
        }
    }

    temp_v0 = (temp_a3->field_0_0 & 0xFFFF) + (temp_a3->field_2_0 << 16);
    gte_ldR11R12(temp_v0);
    gte_ldR13R21(temp_v0);
    temp_v0 = (u16)arg0->field_4.field_C.vx + (arg0->field_4.field_C.vz << 16);
    gte_ldvxy0(temp_v0);
    gte_gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&arg0->field_CC.field_20.field_14);
    temp_v0 = ((arg0->field_98.vec_0.vx - arg0->field_CC.field_12.vx) & 0xFFFF) + ((arg0->field_98.vec_0.vz - arg0->field_CC.field_12.vz) << 16);
    gte_ldvxy0(temp_v0);
    gte_gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&arg0->field_CC.field_20.field_0);

    temp_s0                            = arg0->field_CC.field_20.field_0.vx;
    temp_a0_5                          = arg0->field_CC.field_20.field_0.vz;
    arg0->field_CC.field_20.field_4.vx = arg0->field_CC.field_20.field_14.vx + temp_s0;
    arg0->field_CC.field_20.field_4.vz = arg0->field_CC.field_20.field_14.vz + temp_a0_5;

    if (temp_s0 < 0)
    {
        arg0->field_CC.field_20.field_8  = 2;
        arg0->field_CC.field_20.field_C  = SquareRoot0(SQUARE(temp_s0) + SQUARE(temp_a0_5));
        arg0->field_CC.field_20.field_10 = -temp_s0;
    }
    else if (arg0->field_CC.field_6.vz < temp_s0)
    {
        arg0->field_CC.field_20.field_8  = 2;
        arg0->field_CC.field_20.field_C  = SquareRoot0(SQUARE(temp_s0 - arg0->field_CC.field_6.vz) + SQUARE(temp_a0_5));
        arg0->field_CC.field_20.field_10 = temp_s0 - arg0->field_CC.field_6.vz;
    }
    else
    {
        if (temp_a0_5 < 0)
        {
            arg0->field_CC.field_20.field_C = -temp_a0_5;
        }
        else
        {
            arg0->field_CC.field_20.field_C = temp_a0_5;
        }

        arg0->field_CC.field_20.field_8 = 1;
    }

    return true;
}

void func_8006B6E8(s_func_8006CC44* arg0, s_IpdCollisionData_20* arg1) // 0x8006B6E8
{
    s32                 idx;
    s32                 temp_s1;
    s32                 temp_s2;
    s32                 temp_s3;
    s32                 temp_s4;
    s_func_8006CC44_A8* temp_s0;

    temp_s1 = arg0->field_CC.field_C.s_field_0.field_0;
    temp_s2 = arg0->field_CC.field_C.s_field_0.field_1;
    temp_s3 = arg0->field_CC.field_10;
    temp_s4 = arg0->field_CC.field_11;

    if (temp_s1 == 0xFF)
    {
        if (temp_s2 == 0xFF)
        {
            return;
        }

        idx = arg0->field_CC.field_F;
    }
    else
    {
        idx = arg0->field_CC.field_E;
    }

    temp_s0 = &arg0->field_A0.s_0.field_8[idx];
    if (!func_8006B7E0(temp_s0, &arg0->field_CC.field_20))
    {
        return;
    }

    temp_s0->field_0 = arg0->field_CC.field_20.field_8;
    temp_s0->field_4 = arg0->field_CC.field_20.field_C;
    temp_s0->field_2 = arg0->field_CC.field_20.field_10;

    if (arg0->field_CC.field_20.field_0.vz >= 0)
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

bool func_8006B7E0(s_func_8006CC44_A8* arg0, s_func_8006CC44_CC_20* arg1) // 0x8006B7E0
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

void func_8006B8F8(s_func_8006CC44_CC* arg0) // 0x8006B8F8
{
    s_func_8006CC44_CC_20* ptr;
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

void func_8006B9C8(s_func_8006CC44* arg0) // 0x8006B9C8
{
    s32 field_28;

    if (arg0->field_CC.field_C.s_field_0.field_1 == 0xFF && arg0->field_CC.field_20.field_0.vz < 0 &&
        (arg0->field_4.field_2C >= arg0->field_CC.field_12.vy || arg0->field_4.field_2C >= arg0->field_CC.field_18.vy))
    {
        if (arg0->field_0_9 && arg0->field_CC.field_20.field_C < arg0->field_4.field_28)
        {
            func_8006BB50(arg0, 0);
            return;
        }

        field_28 = arg0->field_4.field_28;
        if (arg0->field_0_9 && arg0->field_CC.field_20.field_C < (field_28 + 8))
        {
            func_8006BB50(arg0, 1);
        }

        if (arg0->field_0_8)
        {
            if (!arg0->field_44.field_0.field_0 &&
                (-field_28 < arg0->field_CC.field_20.field_0.vz || -field_28 < arg0->field_CC.field_20.field_4.vz) &&
                (-field_28 < arg0->field_CC.field_20.field_0.vx || -field_28 < arg0->field_CC.field_20.field_4.vx) &&
                (arg0->field_CC.field_20.field_0.vx < (field_28 + arg0->field_CC.field_6.vz) || arg0->field_CC.field_20.field_4.vx < (field_28 + arg0->field_CC.field_6.vz)))
            {
                func_8006BE40(arg0);
            }
        }
    }
}

void func_8006BB50(s_func_8006CC44* arg0, s32 arg1) // 0x8006BB50
{
    q19_12 deltaX;
    q19_12 deltaZ;
    s16    temp2;

    if (func_8006BC34(arg0) < 0)
    {
        return;
    }

    if (arg0->field_CC.field_20.field_0.vx < 0)
    {
        deltaX = arg0->field_98.vec_0.vx - arg0->field_CC.field_12.vx;
        deltaZ = arg0->field_98.vec_0.vz - arg0->field_CC.field_12.vz;
    }
    else if (arg0->field_CC.field_6.vz < arg0->field_CC.field_20.field_0.vx)
    {
        deltaX = arg0->field_98.vec_0.vx - arg0->field_CC.field_18.vx;
        deltaZ = arg0->field_98.vec_0.vz - arg0->field_CC.field_18.vz;
    }
    else
    {
        deltaX = arg0->field_CC.field_6.vy;
        deltaZ = -arg0->field_CC.field_6.vx;
    }

    temp2 = arg0->field_4.field_28 - arg0->field_CC.field_20.field_C;
    func_8006BCC4(&arg0->field_44, (u8*)arg0->field_CC.ipdCollisionData_0 + (arg0->field_CC.field_4 + 52), arg1, deltaX, deltaZ, temp2);
}

s32 func_8006BC34(s_func_8006CC44* arg0)
{
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_v0;
    s16 temp_v1;
    u16 temp_a1;
    u16 var_v0;

    temp_v1 = arg0->field_CC.field_20.field_0.vx;
    if (temp_v1 < 0)
    {
        var_v0 = arg0->field_CC.field_12.vy;
    }
    else
    {
        temp_a2 = arg0->field_CC.field_6.vz;
        if (temp_a2 < temp_v1)
        {
            var_v0 = arg0->field_CC.field_18.vy;
        }
        else
        {
            temp_a3 = arg0->field_CC.field_12.vy;
            temp_v0 = arg0->field_CC.field_18.vy;
            temp_a1 = arg0->field_CC.field_12.vy;

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

    return arg0->field_4.field_2C - (s16)var_v0;
}

void func_8006BCC4(s_func_8006CC44_44* arg0, s8* arg1, u32 arg2, q3_12 deltaX, q3_12 deltaZ, s16 arg5) // 0x8006BCC4
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

void func_8006BDDC(s_func_8006CC44_44_0* arg0, q3_12 rotX, q3_12 rotY) // 0x8006BDDC
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

void func_8006BE40(s_func_8006CC44* arg0) // 0x8006BE40
{
    s32 temp_a3;
    s32 var_a2;
    s32 var_a1;
    u32 var_v1;
    s32 temp;

    var_a1  = 0;
    temp_a3 = -arg0->field_4.field_28;
    var_a2  = 0;

    if (arg0->field_CC.field_20.field_0.vz >= temp_a3)
    {
        if (arg0->field_CC.field_20.field_0.vx >= 0)
        {
            if (arg0->field_CC.field_6.vz >= arg0->field_CC.field_20.field_0.vx)
            {
                var_a2 = arg0->field_CC.field_20.field_0.vx;
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
        if (arg0->field_CC.field_20.field_14.vz == 0)
        {
            if ((arg0->field_CC.field_20.field_0.vx > 0) && (arg0->field_CC.field_20.field_0.vx < arg0->field_CC.field_6.vz))
            {
                var_a1 = 0;
                var_a2 = arg0->field_CC.field_20.field_0.vx;
            }
        }
        else
        {
            var_a1 = FP_TO(temp_a3 - arg0->field_CC.field_20.field_0.vz, Q12_SHIFT) / arg0->field_CC.field_20.field_14.vz;
            temp   = arg0->field_CC.field_20.field_14.vx * var_a1;
            temp   = FP_FROM(temp, Q12_SHIFT);
            var_a2 = temp + arg0->field_CC.field_20.field_0.vx;
        }

        if (var_a2 < 0)
        {
            var_v1 = 0;
        }
        else if (arg0->field_CC.field_6.vz < var_a2)
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
            func_8006BF88(arg0, &arg0->field_CC.field_12);
            break;

        case 1:
            func_8006BF88(arg0, &arg0->field_CC.field_18);
            break;

        case 2:
            func_8006C0C8(arg0, var_a1, var_a2);
            break;
    }
}

void func_8006BF88(s_func_8006CC44* arg0, SVECTOR3* arg1) // 0x8006BF88
{
    s16 temp_v0;
    s32 temp2;
    s32 temp3;

    temp_v0 = func_8006C248(*(s32*)&arg0->field_4.direction_14, arg0->field_4.field_8,
                            arg1->vx - arg0->field_98.vec_0.vx,
                            arg1->vz - arg0->field_98.vec_0.vz,
                            arg0->field_4.field_28);
    if (temp_v0 != -1 && func_8006C1B8(2, temp_v0, arg0) && arg0->field_4.field_2C > arg1->vy)
    {
        arg0->field_38 = temp_v0;
        arg0->field_34 = 2;
        temp2          = arg0->field_98.vec_0.vx + Q12_MULT(arg0->field_4.field_C.vx, temp_v0);
        arg0->field_3A = (arg0->field_4.field_8 * temp_v0) >> 8;
        arg0->field_40 = (u8*)arg0->field_CC.ipdCollisionData_0 + (arg0->field_CC.field_4 + 52);

        arg0->field_3C = temp2 - arg1->vx;
        temp3          = arg0->field_98.vec_0.vz + Q12_MULT(arg0->field_4.field_C.vz, temp_v0);
        arg0->field_3E = temp3 - arg1->vz;
    }
}

void func_8006C0C8(s_func_8006CC44* arg0, s16 arg1, s16 arg2) // 0x8006C0C8
{
    s32 temp;

    if (!func_8006C1B8(1, arg1, arg0) || arg0->field_CC.field_20.field_14.vz < 0)
    {
        return;
    }

    temp = ((arg0->field_CC.field_18.vy - arg0->field_CC.field_12.vy) * arg2) / arg0->field_CC.field_6.vz;

    if (temp + arg0->field_CC.field_12.vy < arg0->field_4.field_2C)
    {
        arg0->field_40 = (u8*)arg0->field_CC.ipdCollisionData_0 + (arg0->field_CC.field_4 + 52);
        arg0->field_34 = 1;
        arg0->field_38 = arg1;
        arg0->field_3A = (arg0->field_4.field_8 * arg1) >> 8;
        arg0->field_3C = arg0->field_CC.field_6.vy;
        arg0->field_3E = -arg0->field_CC.field_6.vx;
    }
}

bool func_8006C1B8(u32 arg0, s16 arg1, s_func_8006CC44* arg2) // 0x8006C1B8
{
    s32 var;

    var = (arg2->field_4.field_8 * arg1) >> 8;
    switch (arg0)
    {
        default:
        case 0:
            return false;

        case 2:
            if (arg2->field_34 != 1)
            {
                if (arg2->field_34 == 0)
                {
                   return true;
                }

                break;
            }

            var += 96;
            break;

        case 1:
            if (arg2->field_34 != arg0)
            {
                if (arg2->field_34 != 0)
                {
                    if (arg2->field_34 == 2)
                    {
                        var -= 96;
                    }

                    break;
                }

                return true;
            }
            break;
    }

    return var < arg2->field_3A;
}

s16 func_8006C248(s32 arg0, s16 arg1, q3_12 deltaX, q3_12 deltaZ, s16 arg4) // 0x8006C248
{
    DVECTOR sp10;
    s16     temp_v0;
    s16     var_v1;
    s16     temp_lo;

    gte_ldR11R12(arg0);
    gte_ldR13R21(arg0);
    gte_ldvxy0((deltaX & 0xFFFF) + (deltaZ << 16));
    gte_gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&sp10.vx);

    if (sp10.vx < 0)
    {
        var_v1 = SquareRoot0(SQUARE(sp10.vx) + SQUARE(sp10.vy));
    }
    else if (arg1 < sp10.vx)
    {
        temp_v0 = sp10.vx - arg1;
        var_v1  = SquareRoot0(SQUARE(temp_v0) + SQUARE(sp10.vy));
    }
    else
    {
        var_v1 = ABS(sp10.vy);
    }

    if (arg1 == 0)
    {
        temp_lo = -1;
        if (var_v1 >= arg4)
        {
            return temp_lo;
        }
        else
        {
            return 0;
        }
    }

    if (var_v1 >= arg4)
    {
        return -1;
    }

    temp_lo = FP_TO(sp10.vx - SquareRoot0(SQUARE(arg4) - SQUARE(sp10.vy)), Q12_SHIFT) / arg1;
    temp_lo = CLAMP(temp_lo, Q12(0.0f), Q12(1.0f));

    return temp_lo;
}

bool func_8006C3D4(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s32 idx) // 0x8006C3D4
{
    s_IpdCollisionData_18* temp_a1;

    arg0->field_CC.ipdCollisionData_0 = collData;
    arg0->field_CC.field_4 = idx;
    temp_a1 = &collData->ptr_18[idx - collData->field_8_16];

    if (!((arg0->field_2 >> temp_a1->field_0_8) & (1 << 0)))
    {
        return false;
    }

    arg0->field_CC.field_5         = temp_a1->field_0_5;
    arg0->field_CC.field_6.vx      = temp_a1->vec_2.vx;
    arg0->field_CC.field_6.vy      = temp_a1->vec_2.vy;
    arg0->field_CC.field_6.vz      = temp_a1->vec_2.vz;
    arg0->field_CC.field_C.field_0 = temp_a1->field_8;
    return true;
}

void func_8006C45C(s_func_8006CC44* arg0) // 0x8006C45C
{
    q3_12 distMax;
    q3_12 dist;
    s16   var_s2;
    s32   bound;
    s32   deltaX;
    s32   deltaZ;
    s32   temp_v1;
    s32   temp;
    s32   temp2;

    distMax = arg0->field_4.field_28 + arg0->field_CC.field_C.field_0;
    bound   = distMax + 8;
    temp_v1 = arg0->field_CC.field_6.vx - bound;

    if (arg0->field_98.vec_0.vx < temp_v1 &&
        arg0->field_9C.vec_0.vx < temp_v1)
    {
        return;
    }

    if ((arg0->field_CC.field_6.vx + bound) < arg0->field_98.vec_0.vx &&
        (arg0->field_CC.field_6.vx + bound) < arg0->field_9C.vec_0.vx)
    {
        return;
    }

    if (arg0->field_98.vec_0.vz < (arg0->field_CC.field_6.vz - bound) &&
        arg0->field_9C.vec_0.vz < (arg0->field_CC.field_6.vz - bound))
    {
        return;
    }

    if ((arg0->field_CC.field_6.vz + bound) < arg0->field_98.vec_0.vz &&
        (arg0->field_CC.field_6.vz + bound) < arg0->field_9C.vec_0.vz)
    {
        return;
    }

    deltaX = arg0->field_98.vec_0.vx - arg0->field_CC.field_6.vx;
    deltaZ = arg0->field_98.vec_0.vz - arg0->field_CC.field_6.vz;
    dist   = SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ));

    if (dist < arg0->field_CC.field_C.field_0 && arg0->field_CC.field_5 != 1 &&
        (arg0->field_C8 == 0xFF || arg0->field_CC.field_6.vy < arg0->field_CA))
    {
        arg0->field_C8 = arg0->field_CC.field_4;
        arg0->field_CA = arg0->field_CC.field_6.vy;
    }

    if (!arg0->field_0_8 && !arg0->field_0_9 || dist < arg0->field_CC.field_C.field_0)
    {
        return;
    }

    if (dist < distMax && arg0->field_0_9)
    {
        func_8006C794(arg0, 0, dist);
        return;
    }

    if (dist < (distMax + 8) && arg0->field_0_9)
    {
        func_8006C794(arg0, 1, dist);
    }

    if (!arg0->field_0_8 || arg0->field_44.field_0.field_0)
    {
        return;
    }

    var_s2 = func_8006C248(*(s32*)&arg0->field_4.direction_14, arg0->field_4.field_8,
                           arg0->field_CC.field_6.vx - arg0->field_98.vec_0.vx,
                           arg0->field_CC.field_6.vz - arg0->field_98.vec_0.vz,
                           distMax);

    if (var_s2 == -1)
    {
        return;
    }

    if (var_s2 < 0)
    {
        var_s2 = 0;
    }

    if (func_8006C1B8(1, var_s2, arg0) && arg0->field_4.field_2C >= arg0->field_CC.field_6.vy)
    {
        arg0->field_38 = var_s2;
        arg0->field_34 = 1;
        temp           = arg0->field_98.vec_0.vx + Q12_MULT(arg0->field_4.field_C.vx, var_s2);
        arg0->field_3A = (arg0->field_4.field_8 * var_s2) >> 8;
        arg0->field_40 = (u8*)arg0->field_CC.ipdCollisionData_0 + (arg0->field_CC.field_4 + 52);
        arg0->field_3C = temp - arg0->field_CC.field_6.vx;
        temp2          = arg0->field_98.vec_0.vz + Q12_MULT(arg0->field_4.field_C.vz, var_s2);
        arg0->field_3E = temp2 - arg0->field_CC.field_6.vz;
    }
}

void func_8006C794(s_func_8006CC44* arg0, s32 arg1, s32 dist) // 0x8006C794
{
    if (arg0->field_4.field_2C >= (arg0->field_CC.field_6.vy + (dist - arg0->field_CC.field_C.field_0)))
    {
        func_8006BCC4(&arg0->field_44,
                      (u8*)arg0->field_CC.ipdCollisionData_0 + (arg0->field_CC.field_4 + 52),
                      arg1,
                      arg0->field_98.vec_0.vx - arg0->field_CC.field_6.vx,
                      arg0->field_98.vec_0.vz - arg0->field_CC.field_6.vz,
                      (arg0->field_4.field_28 + arg0->field_CC.field_C.field_0) - dist);
    }
}

void func_8006C838(s_func_8006CC44* arg0, s_IpdCollisionData* collData) // 0x8006C838
{
    s32                    var_a0;
    s_func_8006CC44_A8*    curUnk;
    s_IpdCollisionData_10* temp_a1;
    s_IpdCollisionData_18* temp_a0;

    if (!arg0->field_A0.s_0.field_4)
    {
        return;
    }

    if (arg0->field_C8 != 0xFF)
    {
        if (arg0->field_CA < arg0->field_7C)
        {
            temp_a0        = &collData->ptr_18[arg0->field_C8 - collData->field_8_16];
            arg0->field_7C = arg0->field_CA;
            arg0->field_80 = arg0->field_98.vec_0.vx + collData->positionX_0;
            arg0->field_84 = arg0->field_98.vec_0.vz + collData->positionZ_4;
            arg0->field_88 = 0;
            arg0->field_8C = 0;
            arg0->field_90 = temp_a0->field_0_5;
            arg0->field_94 = temp_a0->field_0_0;
        }
    }

    for (curUnk = &arg0->field_A0.s_0.field_8[0]; curUnk < &arg0->field_A0.s_0.field_8[4]; curUnk++)
    {
        if (curUnk->field_1 != 0xFF)
        {
            temp_a1 = &collData->ptr_10[curUnk->field_1];

            var_a0 = temp_a1->field_2;

            if (temp_a1->field_8 != 0)
            {
                var_a0 += FP_FROM(temp_a1->field_8 * (arg0->field_98.vec_0.vx - temp_a1->field_0), Q12_SHIFT);
            }

            if (temp_a1->field_A != 0)
            {
                var_a0 += FP_FROM(temp_a1->field_A * (arg0->field_98.vec_0.vz - temp_a1->field_4), Q12_SHIFT);
            }

            if (var_a0 < arg0->field_7C)
            {
                arg0->field_7C = var_a0;
                arg0->field_80 = arg0->field_98.vec_0.vx + collData->positionX_0;
                arg0->field_84 = arg0->field_98.vec_0.vz + collData->positionZ_4;
                arg0->field_88 = temp_a1->field_8;
                arg0->field_8C = temp_a1->field_A;
                arg0->field_90 = temp_a1->field_6_5;
                arg0->field_94 = temp_a1->field_6_0;
            }
        }
    }
}

void func_8006CA18(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s_func_8006CA18* arg2) // 0x8006CA18
{
    s32                    startIdx;
    s32                    endIdx;
    s32                    var_a2;
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

        if (((arg0->field_2 >> ptr->field_6_11) & (1 << 0)) && ptr->field_6_5 != 1)
        {
            var_a2 = ptr->field_2;

            if (ptr->field_8 != 0)
            {
                var_a2 += FP_FROM(ptr->field_8 * (arg0->field_98.vec_0.vx - ptr->field_0), Q12_SHIFT);
            }

            if (ptr->field_A != 0)
            {
                var_a2 += FP_FROM(ptr->field_A * (arg0->field_98.vec_0.vz - ptr->field_4), Q12_SHIFT);
            }

            if (var_a2 < arg0->field_7C)
            {
                arg0->field_7C = var_a2;
                arg0->field_80 = arg0->field_98.vec_0.vx + collData->positionX_0;
                arg0->field_84 = arg0->field_98.vec_0.vz + collData->positionZ_4;
                arg0->field_88 = ptr->field_8;
                arg0->field_8C = ptr->field_A;
                arg0->field_90 = ptr->field_6_5;
                arg0->field_94 = ptr->field_6_0;
            }
        }
    }
}

s16 func_8006CB90(s_func_8006CC44* arg0) // 0x8006CB90
{
    s32 temp_v0;

    if (arg0->field_7C == 0x1E00)
    {
        return Q12(1.0f);
    }

    temp_v0 = func_8006CC44(arg0->field_4.field_20, arg0->field_4.field_24, arg0);
    if ((arg0->field_4.field_2C + arg0->field_4.field_C.vy) < temp_v0 ||
        temp_v0 == arg0->field_7C)
    {
        return Q12(1.0f);
    }

    return FP_TO(arg0->field_4.field_8, Q12_SHIFT) / SquareRoot0(SQUARE(arg0->field_4.field_8) +
                                                                 SQUARE(temp_v0 - arg0->field_4.field_2C));
}

s32 func_8006CC44(q23_8 x, q23_8 z, s_func_8006CC44* arg2) // 0x8006CC44
{
    if (arg2->field_94 != 12)
    {
        return Q12_MULT(arg2->field_88, x - arg2->field_80) +
               Q12_MULT(arg2->field_8C, z - arg2->field_84) +
               arg2->field_7C;
    }

    return Q12(0.5f);
}

void func_8006CC9C(s_func_8006CC44* arg0) // 0x8006CC9C
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

    if (arg0->field_A0.s_1.field_6 < 2 || *arg0->field_A0.s_1.field_8 != 0)
    {
        return;
    }

    if (arg0->field_98.field_0 + (arg0->field_A0.s_1.field_4 + arg0->field_4.field_8) < arg0->field_4.positionX_18 ||
        arg0->field_4.field_20 < arg0->field_98.field_0 - (arg0->field_A0.s_1.field_4 + arg0->field_4.field_8))
    {
        return;
    }

    if (arg0->field_9C.field_0 + (arg0->field_A0.s_1.field_4 + arg0->field_4.field_8) < arg0->field_4.positionZ_1C ||
        arg0->field_4.field_24 < arg0->field_9C.field_0 - (arg0->field_A0.s_1.field_4 + arg0->field_4.field_8) ||
        arg0->field_4.field_2A > arg0->field_A0.s_1.field_2)
    {
        return;
    }

    deltaX = (arg0->field_4.positionX_18 - arg0->field_98.field_0);

    if (arg0->field_4.field_2C < arg0->field_A0.s_1.field_0)
    {
        return;
    }

    deltaZ = arg0->field_4.positionZ_1C - arg0->field_9C.field_0;
    temp_s4 = SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ));

    temp_v0 = func_8006C248(*(s32*)&arg0->field_4.direction_14, arg0->field_4.field_8,
                            arg0->field_98.field_0 - arg0->field_4.positionX_18,
                            arg0->field_9C.field_0 - arg0->field_4.positionZ_1C,
                            arg0->field_A0.s_1.field_4);
    if (temp_v0 == NO_VALUE)
    {
        return;
    }

    if (temp_v0 == 0)
    {
        if (arg0->field_0_9)
        {
            temp3 = arg0->field_A0.s_1.field_4 - temp_s4;
            func_8006BCC4(&arg0->field_44, arg0->field_A0.s_1.field_8, 2, deltaX, deltaZ, temp3);
        }
    }
    else if (arg0->field_0_8 && arg0->field_44.field_0.field_0 == 0 && func_8006C1B8(1, temp_v0, arg0))
    {
        temp2 = (arg0->field_4.positionZ_1C - arg0->field_9C.field_0);
        temp5 = Q12_MULT(temp_v0, arg0->field_4.field_C.vz);

        arg0->field_40 = arg0->field_A0.s_1.field_8;
        arg0->field_38 = temp_v0;

        arg0->field_34 = 1;

        temp  = (arg0->field_4.positionX_18 - arg0->field_98.field_0);
        temp4 = Q12_MULT(temp_v0, arg0->field_4.field_C.vx);

        arg0->field_3A = (arg0->field_4.field_8 * temp_v0) >> 8; // TODO: Conversion to Q4?
        arg0->field_3C = temp + temp4;
        arg0->field_3E = temp2 + temp5;
    }
}

void func_8006CF18(s_func_8006CC44* arg0, s_func_8006CF18* arg1, s32 idx) // 0x8006CF18
{
    s32              var_a1;
    s_func_8006CF18* curArg1;

    for (curArg1 = arg1; curArg1 < &arg1[idx]; curArg1++)
    {
        var_a1 = (curArg1->field_10 >> 4) + arg0->field_4.field_28;
        if (curArg1->field_12 < (u32)arg0->field_4.field_0)
        {
            var_a1 -= 15;
        }

        arg0->field_98.field_0 = curArg1->position_0.vx >> 4;
        arg0->field_9C.field_0 = curArg1->position_0.vz >> 4;

        arg0->field_A0.s_1.field_0 = (curArg1->field_E + curArg1->position_0.vy) >> 4;
        arg0->field_A0.s_1.field_2 = (curArg1->field_C + curArg1->position_0.vy) >> 4;
        arg0->field_A0.s_1.field_4 = var_a1;
        arg0->field_A0.s_1.field_6 = curArg1->field_12;
        arg0->field_A0.s_1.field_8 = &curArg1->field_13;

        if (arg0->field_0_0 == 0)
        {
            curArg1->field_13 = 0;
        }

        func_8006CC9C(arg0);
    }
}

void func_8006D01C(VECTOR3* arg0, VECTOR3* arg1, s16 arg2, s_func_8006CC44* arg3) // 0x8006D01C
{
    VECTOR3 sp10;
    s32     temp_s0;
    s32     temp_s1;
    s32     temp_a0;
    s32     temp_v0;

    sp10.vx = Q12_MULT(arg1->vx, arg2);
    sp10.vz = Q12_MULT(arg1->vz, arg2);

    if (arg3->field_44.field_0.field_0 || arg3->field_44.field_30.field_0)
    {
        arg0->vx = 0;
        arg0->vz = 0;
        *arg1    = sp10;
        func_8006D2B4(arg1, &arg3->field_44);
        return;
    }

    if (!arg3->field_34)
    {
        *arg0    = sp10;
        arg1->vz = 0;
        arg1->vx = 0;
        return;
    }

    if (arg2 < arg3->field_38)
    {
        arg3->field_34 = 0;
        *arg0          = sp10;
        arg1->vz       = 0;
        arg1->vx       = 0;
        return;
    }

    arg0->vx = Q12_MULT(arg1->vx, arg3->field_38);
    arg0->vz = Q12_MULT(arg1->vz, arg3->field_38);
    arg1->vx = sp10.vx - arg0->vx;
    arg1->vz = sp10.vz - arg0->vz;

    temp_s0 = arg3->field_3C;
    temp_s1 = arg3->field_3E;
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

    temp_v0  = FP_FROM((arg1->vx * temp_s1) + (arg1->vz * -temp_s0), Q12_SHIFT);
    arg1->vx = Q12_MULT(temp_v0, temp_s1);
    arg1->vz = Q12_MULT(temp_v0, -temp_s0);

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

void func_8006D2B4(VECTOR3* arg0, s_func_8006CC44_44* arg1) // 0x8006D2B4
{
    s16  sp18;
    s16  sp1A;
    s16  sp1C;
    s16  sp1E;
    s16  temp_v0;
    s32  temp_v0_4;
    bool cond;
    bool var_s1;
    s16  var_s1_2;
    s32  var_v1;
    s16  var_v1_2;
    s16  var_a0;
    s16  diff_a0;
    s16  diff_v1;

    if (arg1->field_30.field_0 != 0)
    {
        var_s1 = false;
        if (arg1->field_0.field_0 != 0)
        {
            sp18 = arg1->field_0.field_2.vx;
            sp1A = arg1->field_0.field_2.vy;
            if (arg1->field_8.field_0 != 0)
            {
                Vw_ClampAngleRange(&sp18, &sp1A, arg1->field_8.field_2.vx, arg1->field_8.field_2.vy);
            }
        }
        else if (arg1->field_8.field_0 != 0)
        {
            sp18 = arg1->field_8.field_2.vx;
            sp1A = arg1->field_8.field_2.vy;
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
            temp_v0  = ratan2(arg0->vz, arg0->vx);
            var_s1_2 = 0x400;
            diff_a0  = ((sp1A - (temp_v0 - var_s1_2)) << 20) >> 20;
            diff_v1  = ((sp18 - (temp_v0 + var_s1_2)) << 20) >> 20;
            if (diff_a0 < 0 && diff_v1 >= 1)
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
            arg0->vx = 0;
            arg0->vz = 0;
            return;
        }

        var_s1_2 = (arg1->field_0.field_2.vx + arg1->field_0.field_2.vy) >> 1;

        if (arg1->field_0.field_2.vy < arg1->field_0.field_2.vx)
        {
            var_s1_2 = (var_s1_2 + 0x800) & 0xFFF;
        }

        if (arg1->field_8.field_0 == 0)
        {
            sp1C = arg1->field_0.field_2.vx;
            sp1E = arg1->field_0.field_2.vy;
        }
        else
        {
            sp1C = arg1->field_0.field_2.vx;
            sp1E = arg1->field_0.field_2.vy;

            Vw_ClampAngleRange(&sp1C, &sp1E, arg1->field_8.field_2.vx, arg1->field_8.field_2.vy);

            sp1C = sp1C & 0xFFF;
            sp1E = sp1E & 0xFFF;

            if (sp1C == sp1E)
            {
                sp1C = arg1->field_0.field_2.vx;
                sp1E = arg1->field_0.field_2.vy;
            }

            if (sp1C != sp1E)
            {
                var_v1    = ((sp1C - var_s1_2) << 20) >> 20;
                temp_v0_4 = ((sp1E - var_s1_2) << 20) >> 20;

                if (var_v1 >= 0 || temp_v0_4 <= 0)
                {
                    if (ABS(var_v1) < ABS(temp_v0_4))
                    {
                        var_s1_2 = sp1C;
                    }
                    else
                    {
                        var_s1_2 = sp1E;
                    }
                }
            }
        }

        var_v1_2 = MIN(arg1->field_6 + 2, 16) * 16;

        func_8006D600(arg0, var_s1_2, sp1C, sp1E, var_v1_2);
    }
}

void func_8006D600(VECTOR3* pos, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x8006D600
{
    s32    temp_a2;
    s16    temp_s0;
    s16    temp_s3;
    s16    temp;
    s32    temp_s0_2;
    s32    deltaX;
    s32    deltaZ;
    s32    z;
    s32    x;
    s32    temp_v0;
    s32    var_s0;
    s32    var_v0_2;
    q19_12 angle;

    // TODO: Angles here.

    temp_s0 = Q12_FRACT(arg1);
    temp_s3 = Q12_FRACT(arg2);
    temp    = Q12_FRACT(arg3);

    if (arg4 > 0x100)
    {
        arg4 = 0x100;
    }

    x      = Q12_MULT(arg4, Math_Cos(temp_s0));
    var_s0 = temp;
    z      = Q12_MULT(arg4, Math_Sin(temp_s0));
    deltaX = pos->vx - x;
    deltaZ = pos->vz - z;
    angle  = Q12_FRACT(ratan2(deltaZ, deltaX));

    if (angle < temp_s3)
    {
        angle += Q12_ANGLE(360.0f);
    }

    if (var_s0 < temp_s3)
    {
        var_s0 += Q12_ANGLE(360.0f);
    }

    temp_a2 = temp_s3 + Q12_ANGLE(360.0f);
    if (var_s0 < angle)
    {
        if (((var_s0 + temp_a2) >> 1) < angle)
        {
            var_s0 = temp_a2;
        }

        temp_s0_2 = Math_Sin(var_s0);
        temp_v0   = Math_Cos(var_s0);
        var_v0_2  = Q12_MULT(deltaX, temp_v0) + Q12_MULT(deltaZ, temp_s0_2);

        if (var_v0_2 < 0)
        {
            var_v0_2 = 0;
        }

        pos->vx = x + Q12_MULT(var_v0_2, temp_v0);
        pos->vz = z + Q12_MULT(var_v0_2, temp_s0_2);
    }
}

void func_8006D774(s_func_8006CC44* arg0, VECTOR3* arg1, VECTOR3* arg2) // 0x8006D774
{
    SVECTOR sp10; // Types assumed. `SVECTOR3` might also work but there are 8 bytes between `sp10` and `sp18` and `SVECTOR3` is only 6 bytes.
    SVECTOR sp18;

    sp10.vx = Q12_TO_Q8(arg1->vx);
    sp10.vy = Q12_TO_Q8(arg1->vz);
    sp18.vx = Q12_TO_Q8(arg2->vx);
    sp18.vy = Q12_TO_Q8(arg2->vz);

    arg0->field_34 = 0;
    arg0->field_44.field_0.field_0  = 0;
    arg0->field_44.field_6          = 0;
    arg0->field_44.field_8.field_0  = 0;
    arg0->field_44.field_36         = 0;
    arg0->field_44.field_30.field_0 = 0;

    func_8006D7EC(&arg0->field_4, &sp10, &sp18);
}

void func_8006D7EC(s_func_8006ABC0* arg0, SVECTOR* arg1, SVECTOR* arg2) // 0x8006D7EC
{
    s16 angle;
    s32 dist;
    s16 z;

    arg0->field_C.vx = arg2->vx;

    z                = arg2->vy;
    arg0->field_C.vz = arg2->vy;
    dist             = SquareRoot0(SQUARE(arg0->field_C.vx) + SQUARE(z));

    arg0->field_8 = dist;

    if (dist != 0)
    {
        arg0->direction_14.vx = FP_TO(arg0->field_C.vx, Q12_SHIFT) / dist;
        arg0->direction_14.vz = FP_TO(arg0->field_C.vz, Q12_SHIFT) / arg0->field_8;

        angle                 = ratan2(arg0->field_C.vz, arg0->field_C.vx);
        arg0->direction_14.vx = Math_Cos(angle);
        arg0->direction_14.vz = Math_Sin(angle);
    }
    else
    {
        arg0->direction_14.vx = Q12(1.0f);
        arg0->direction_14.vz = Q12(0.0f);
    }

    arg0->positionX_18 = arg0->positionX_18 + arg1->vx;
    arg0->positionZ_1C = arg0->positionZ_1C + arg1->vy;
    arg0->field_20     = arg0->positionX_18 + arg0->field_C.vx;
    arg0->field_24     = arg0->positionZ_1C + arg0->field_C.vz;
}

// ========================================
// COMBAT 2
// ========================================

bool Ray_LineCheck(s_RayData* ray, VECTOR3* from, VECTOR3* to) // 0x8006D90C
{
    s32     scratchPrev;
    s32     scratchAddr;
    VECTOR3 dir; // Q19.12

    dir.vx = to->vx - from->vx;
    dir.vy = to->vy - from->vy;
    dir.vz = to->vz - from->vz;

    ray->hasHit_0 = false;

    if (Ray_TraceSetup((s32)PSX_SCRATCH, 0, 0, from, &dir, 0, 0, NULL, 0))
    {
        scratchPrev   = SetSp((s32)PSX_SCRATCH_ADDR(984));
        scratchAddr   = (s32)PSX_SCRATCH;
        ray->hasHit_0 = Ray_TraceRun(ray, PSX_SCRATCH_ADDR(0));

        SetSp(scratchPrev);
    }

    if (!ray->hasHit_0)
    {
        Ray_MissSet(ray, from, &dir, (s16)*(u16*)(&((u8*)scratchAddr)[92]));
    }

    return ray->hasHit_0;
}

bool func_8006DA08(s_RayData* ray, VECTOR3* from, VECTOR3* dir, s_SubCharacter* chara) // 0x8006DA08
{
    s32              sp28;
    s32              scratchPrev;
    s32              scratchAddr;
    s_SubCharacter** charas;

    charas = func_8006A1A4(&sp28, chara, false);

    ray->hasHit_0 = false;
    if (Ray_TraceSetup((s32)PSX_SCRATCH, 0, 0, from, dir, 0, 0, charas, sp28))
    {
        scratchPrev   = SetSp((s32)PSX_SCRATCH_ADDR(0x3D8));
        scratchAddr   = (s32)PSX_SCRATCH;
        ray->hasHit_0 = Ray_TraceRun(ray, PSX_SCRATCH_ADDR(0));

        SetSp(scratchPrev);
    }

    if (!ray->hasHit_0)
    {
        Ray_MissSet(ray, from, dir, (s16)*(u16*)(&((u8*)scratchAddr)[92]));
    }

    return ray->hasHit_0;
}

void Ray_MissSet(s_RayData* ray, VECTOR3* from, VECTOR3* dir, q23_8 arg3) // 0x8006DAE4
{
    ray->hasHit_0   = false;
    ray->field_1    = 0;
    ray->field_4.vx = from->vx + dir->vx;
    ray->field_4.vy = from->vy + dir->vy;
    ray->field_4.vz = from->vz + dir->vz;
    ray->chara_10   = NULL;
    ray->field_14   = Q8_TO_Q12(arg3);
    ray->field_18   = Q12(1.875f);
    ray->field_1C   = Q12_ANGLE(0.0f);
}

static inline void func_8006DB3C_Inline(s_RayData* ray, VECTOR3* dir, VECTOR3* offset, u16* ptr)
{
    Ray_MissSet(ray, dir, offset, (short)*ptr);
}

bool func_8006DB3C(s_RayData* ray, VECTOR3* from, VECTOR3* dir, s_SubCharacter* chara) // 0x8006DB3C
{
    s32              charaCount;
    s32              stackPtr;
    s32              scratchAddr;
    s_SubCharacter** charas;

    charas       = func_8006A1A4(&charaCount, chara, true);
    ray->hasHit_0 = false;

    if (Ray_TraceSetup((s32)PSX_SCRATCH, 1, 0, from, dir, 0, 0, charas, charaCount))
    {
        stackPtr      = SetSp((s32)PSX_SCRATCH_ADDR(984));
        scratchAddr   = (s32)PSX_SCRATCH;
        ray->hasHit_0 = Ray_TraceRun(ray, scratchAddr);

        SetSp(stackPtr);
    }

    if (!ray->hasHit_0)
    {
        func_8006DB3C_Inline(ray, from, dir, &((u8*)scratchAddr)[92]);
    }

    return ray->hasHit_0;
}

bool func_8006DC18(s_RayData* ray, VECTOR3* vec1, VECTOR3* vec2) // 0x8006DC18
{
    s32 scratchPrev;
    s32 scratchAddr;

    ray->hasHit_0 = false;
    if (Ray_TraceSetup((s32)PSX_SCRATCH, 1, 76, vec1, vec2, 0, 0, NULL, 0))
    {
        scratchPrev   = SetSp((s32)PSX_SCRATCH_ADDR(0x3D8));
        scratchAddr   = (s32)PSX_SCRATCH;
        ray->hasHit_0 = Ray_TraceRun(ray, PSX_SCRATCH_ADDR(0));

        SetSp(scratchPrev);
    }

    if (!ray->hasHit_0)
    {
        Ray_MissSet(ray, vec1, vec2, (s16)*(u16*)(&((u8*)scratchAddr)[92]));
    }

    return ray->hasHit_0;
}

bool Ray_TraceSetup(s_RayState* state, s32 arg1, s16 arg2, VECTOR3* pos, VECTOR3* dir, s32 arg5, s32 arg6, s_SubCharacter** charas, s32 charaCount)
{
    if (dir->vx == Q12(0.0f) && dir->vz == Q12(0.0f))
    {
        return false;
    }

    state->field_0  = arg1;
    state->field_4  = D_800C4478.field_0; // Struct could begin some point earlier.
    state->field_6  = arg2;
    state->field_8  = SHRT_MAX;
    state->field_20 = 0;

    state->field_2C.vx = Q12_TO_Q8(pos->vx);
    state->field_2C.vy = Q12_TO_Q8(pos->vy);
    state->field_2C.vz = Q12_TO_Q8(pos->vz);

    state->field_50.vx = Q12_TO_Q8(dir->vx);
    state->field_50.vy = Q12_TO_Q8(dir->vy);
    state->field_50.vz = Q12_TO_Q8(dir->vz);

    state->field_3C = state->field_2C.vx + state->field_50.vx;

    state->field_4C = Q12_TO_Q8(arg5);
    state->field_4E = Q12_TO_Q8(arg6);

    state->field_40 = state->field_2C.vy + state->field_50.vy;
    state->field_44 = state->field_2C.vz + state->field_50.vz;

    state->field_5C = SquareRoot0(SQUARE(state->field_50.vx) + SQUARE(state->field_50.vz));
    if (state->field_5C == 0)
    {
        return false;
    }

    state->field_58 = (state->field_50.vx << Q12_SHIFT) / state->field_5C;
    state->field_5A = (state->field_50.vz << Q12_SHIFT) / state->field_5C;

    if (state->field_50.vy < 0)
    {
        state->field_5E = state->field_2C.vy + state->field_4E;
        state->field_60 = state->field_40 + state->field_4E;
    }
    else
    {
        state->field_60 = state->field_2C.vy + state->field_4E;
        state->field_5E = state->field_40 + state->field_4E;
    }

    state->characters_64     = charas;
    state->characterCount_68 = charaCount;

    return true;
}

bool Ray_TraceRun(s_RayData* ray, s_RayState* state) // 0x8006DEB0
{
    s32                  collDataIdx;
    s32                  temp_lo;
    s_IpdCollisionData*  collData;
    s_SubCharacter**     curChara;
    s_IpdCollisionData** collDataPtrs;
    s_IpdCollisionData** curCollData;
    s_RayState_8C*  curUnk;

    // Run through IPD collision data.
    collDataPtrs = func_800425D8(&collDataIdx);
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

    // Run through characters.
    for (curChara = state->characters_64; curChara < &state->characters_64[state->characterCount_68]; curChara++)
    {
        func_8006EE0C(&state->field_6C, state->field_0, *curChara);
        func_8006EEB8(state, *curChara);
    }

    if (state->field_8 != SHRT_MAX)
    {
        ray->field_4.vx = Q8_TO_Q12(state->field_C);
        ray->field_4.vy = Q8_TO_Q12(state->field_10);
        ray->field_4.vz = Q8_TO_Q12(state->field_14);
        ray->chara_10   = state->field_20;
        ray->field_14   = Q8_TO_Q12(state->field_8);
        ray->field_18   = Q8_TO_Q12(state->field_1C);
        ray->field_1C   = ratan2(state->field_24, state->field_26);
        ray->field_1    = state->field_28;
        return true;
    }

    return false;
}

void func_8006E0AC(s_RayState* state, s_IpdCollisionData* arg1) // 0x8006E0AC
{
    // `state` type might be wrong.
    state->field_6C.field_0 = arg1->positionX_0;
    state->field_6C.field_4 = arg1->positionZ_4;
    state->field_6C.field_8 = state->field_2C.vx - state->field_6C.field_0;
    state->field_6C.field_A = state->field_2C.vz - state->field_6C.field_4;
    state->field_6C.field_C = state->field_6C.field_8 + state->field_50.vx;
    state->field_6C.field_E = state->field_6C.field_A + state->field_50.vz;
    state->field_7C = arg1->field_1E;
    state->field_80 = arg1->field_1F;
    state->field_84 = arg1->field_1C;

    func_8006E150(&state->field_6C, ((DVECTOR*)&state->field_50)[0], ((DVECTOR*)&state->field_50)[1]);
}

void func_8006E150(s_func_8006E490* arg0, DVECTOR arg1, DVECTOR arg2) // 0x8006E150
{
    DVECTOR subroutine_arg4;
    VECTOR  sp18;
    VECTOR  sp28;
    s16     temp_lo;
    s16     temp_lo_2;
    s32     temp_a0_3;
    s32     temp_lo_4;
    s32     temp_t0;
    s32     temp_t1;
    s32     var_a2;
    s32     var_a3;
    u32     flags;

    flags = 0;
    arg0->field_1C = 0;

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
        flags             |= 1 << 0;
        subroutine_arg4.vx = -subroutine_arg4.vx;

        arg1.vx = -arg1.vx;
        sp18.vz = -sp18.vx;
        sp18.vx = 0;
    }

    if (arg2.vx < 0)
    {
        flags             |= 1 << 1;
        subroutine_arg4.vy = -subroutine_arg4.vy;
        arg2.vx            = -arg2.vx;
        sp18.pad           = -sp18.vy;
        sp18.vy            = 0;
    }

    if (arg1.vx < arg2.vx)
    {
        flags |= 1 << 2;

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

    sp28.vx = Q12(subroutine_arg4.vx) / arg0->field_18;
    sp28.vy = Q12(subroutine_arg4.vy) / arg0->field_18;
    sp28.vz = Q12(1.0f);

    sp28.pad  = Q12(arg2.vx) / arg1.vx;
    temp_lo_4 = Q12_MULT(sp28.pad, Q12_FRACT(sp28.vx));

    if (FP_FROM(sp18.vx, Q12_SHIFT) < FP_FROM(sp28.vx, Q12_SHIFT))
    {
        return;
    }

    do
    {
        func_8006E490(arg0, flags, sp28.vx, sp28.vy);

        temp_t0 = sp28.vy;
        temp_t1 = sp28.vx;
        var_a3  = temp_t0 + sp28.pad;
        var_a2  = temp_t1 + Q12(1.0f);

        sp28.vy = var_a3;
        sp28.vx = var_a2;

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
    while (arg0->field_1C < 20 && FP_FROM(sp28.vx, Q12_SHIFT) <= FP_FROM(sp18.vx, Q12_SHIFT));
}

void func_8006E490(s_func_8006E490* arg0, u32 flags, q19_12 posX, q19_12 posZ) // 0x8006E490
{
    q19_12 tempPosX;

    // TODO: `func_8006E150` also uses these flags. What subsystem are they for?
    // Flag 0: Invert X.
    // Flag 1: Invert Z.
    // Flag 2: Swap XZ.

    if (flags & (1 << 2))
    {
        tempPosX = posX;
        posX     = posZ;
        posZ     = tempPosX;
    }

    if (flags & (1 << 1))
    {
        posZ = -posZ;
    }

    if (flags & (1 << 0))
    {
        posX = -posX;
    }

    posX = FP_FROM(posX, Q12_SHIFT);
    posZ = FP_FROM(posZ, Q12_SHIFT);
    if (posX >= 0 && posX < arg0->field_10 &&
        posZ >= 0 && posZ < arg0->field_14)
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
    s_IpdCollisionData_18* temp_a1_2;
    u8                     temp_a0;
    s32                    temp_a0_3;
    s32                    temp_a2;
    s32                    idx;
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

                    if (state->field_0 == 1)
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

                        if (temp_a0_3 == 0xFF || ipdColl->ptr_10[temp_a0_3].field_6_0 == 0 ||
                            ipdColl->ptr_10[temp_a0_3].field_6_0 == 12)
                        {
                            cond1 = true;
                        }

                        if (temp_a2 == 0xFF || ipdColl->ptr_10[temp_a2].field_6_0 == 0 ||
                            ipdColl->ptr_10[temp_a2].field_6_0 == 12)
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
                    (state->field_0 == 1 || (temp_a1_2->field_0_0 && temp_a1_2->field_0_0 != 12)) &&
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
    s32       var_a1;
    s32       var_a2;
    s32       var_t1;
    s32       var_t7;
    SVECTOR3* temp_t1;
    SVECTOR3* temp_t2;
    s32       temp_v1;
    s32       var_v1;

    var_t7  = 0;
    temp_t1 = &arg2[arg1->field_7];
    temp_t2 = &arg2[arg1->field_6];
    if (state->field_5E >= temp_t1->vy || state->field_5E >= temp_t2->vy)
    {
        if (arg1->field_8 != 0xFF)
        {
            var_t7 = arg3[arg1->field_8].field_6_0;
        }
        if (arg1->field_9 != 0xFF)
        {
            var_t7 = arg3[arg1->field_9].field_6_0;
        }

        temp_v1 = state->field_58 + (state->field_5A << 16);
        gte_ldR11R12(temp_v1);
        gte_ldR13R21(temp_v1);
        gte_ldvxy0(((temp_t1->vx - state->field_6C.field_8) & 0xFFFF) + ((temp_t1->vz - state->field_6C.field_A) << 16));
        gte_gte_ldvz0();
        gte_rtv0();
        gte_stMAC12(&sp0);

        gte_ldvxy0(((temp_t2->vx - state->field_6C.field_8) & 0xFFFF) + ((temp_t2->vz - state->field_6C.field_A) << 16));
        gte_gte_ldvz0();
        gte_rtv0();
        gte_stMAC12(&sp8);

        if ((sp0.vy & 0x8000) != (sp8.vy & 0x8000))
        {
            if (state->field_0 == 1)
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
                var_v1 = ((sp0.vy << 0xC) / (sp0.vy - sp8.vy));
                var_a3 = (((sp8.vx - sp0.vx) * var_v1) >> 0xC) + sp0.vx;
                if (var_a3 >= 0 && state->field_5C >= var_a3)
                {
                    gte_lddp(var_v1);
                    gte_ldsv3_(temp_t2->vx - temp_t1->vx, temp_t2->vy - temp_t1->vy, temp_t2->vz - temp_t1->vz);
                    gte_gpf12();
                    gte_stsv(&sp10);

                    sp10.vx += temp_t1->vx;
                    sp10.vy += temp_t1->vy;
                    sp10.vz += temp_t1->vz;

                    var_a2 = state->field_2C.vy + state->field_4E;
                    if (state->field_50.vy != 0)
                    {
                        var_a2 += (state->field_50.vy * var_a3) / state->field_5C;
                    }

                    if (var_a2 >= sp10.vy && var_a3 < state->field_8)
                    {
                        var_a1 = arg1->field_2_0;
                        var_t1 = -arg1->field_0_0;
                        if (state->field_0 != 1 && arg4 != 0 && (sp8.vy - sp0.vy) > 0)
                        {
                            var_a1 = -var_a1;
                            var_t1 = arg1->field_0_0;
                        }
                        state->field_8  = var_a3;
                        state->field_C  = (sp10.vx + state->field_6C.field_0);
                        state->field_10 = (var_a2 - state->field_4E);
                        state->field_14 = (sp10.vz + state->field_6C.field_4);
                        state->field_1C = sp10.vy;
                        state->field_24 = var_a1;
                        state->field_26 = var_t1;
                        state->field_20 = 0;
                        state->field_28 = var_t7;
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
    gte_ldvxy0(((arg1->vec_2.vx - state->field_6C.field_8) & 0xFFFF) + ((arg1->vec_2.vz - state->field_6C.field_A) << 16));
    gte_gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&sp10);

    if (-temp_a1 < sp10.vx && sp10.vx < (state->field_5C + temp_a1) && -temp_a1 < sp10.vy && sp10.vy < temp_a1)
    {
        temp_v0   = SquareRoot0((temp_a1 * temp_a1) - (sp10.vy * sp10.vy));
        temp_a1_3 = sp10.vx - temp_v0;

        if (temp_a1_3 >= -temp_v0 && state->field_5C >= temp_a1_3 && temp_a1_3 < state->field_8)
        {
            gte_lddp(((temp_a1_3 << 12) / state->field_5C));
            gte_ldsv3_(state->field_50.vx, state->field_50.vy, state->field_50.vz);
            gte_gpf12();
            gte_stsv(&sp18);

            if ((sp18.vy + state->field_2C.vy + state->field_4E) >= arg1->vec_2.vy)
            {
                state->field_8  = temp_a1_3;
                state->field_C  = sp18.vx + state->field_6C.field_8 + state->field_6C.field_0;
                state->field_10 = sp18.vy + state->field_2C.vy;
                state->field_14 = sp18.vz + state->field_6C.field_A + state->field_6C.field_4;
                state->field_1C = arg1->vec_2.vy;
                state->field_24 = (sp18.vx + state->field_6C.field_8) - arg1->vec_2.vx;
                state->field_26 = (sp18.vz + state->field_6C.field_A) - arg1->vec_2.vz;
                state->field_20 = 0;
                state->field_28 = arg1->field_0_0;
            }
        }
    }
}

void func_8006EE0C(s_RayState_6C* arg0, s32 arg1, s_SubCharacter* chara) // 0x8006EE0C
{
    q19_12 offsetZ;
    q19_12 offsetX;
    q19_12 unkY;

    if (arg1 == 1)
    {
        arg0->field_C = Q12_TO_Q8(chara->field_D4.radius_0);
        offsetX       = chara->field_D8.offsetX_4;
        offsetZ       = chara->field_D8.offsetZ_6;
        unkY          = chara->position_18.vy + chara->field_C8.field_2;
    }
    else
    {
        arg0->field_C = Q12_TO_Q8(chara->field_D4.field_2);
        offsetX       = chara->field_D8.offsetX_0;
        offsetZ       = chara->field_D8.offsetZ_2;
        unkY          = chara->position_18.vy + chara->field_C8.field_4;
    }

    arg0->field_A = Q12_TO_Q8(unkY);
    arg0->field_0 = Q12_TO_Q8(chara->position_18.vx + offsetX);
    arg0->field_4 = Q12_TO_Q8(chara->position_18.vz + offsetZ);
    arg0->field_8 = Q12_TO_Q8(chara->position_18.vy + chara->field_C8.field_0);
}

void func_8006EEB8(s_RayState* state, s_SubCharacter* chara) // 0x8006EEB8
{
    VECTOR3 sp18; // Q23.8?
    s32     bound;
    s16     temp_v0;
    s16     temp_v0_2;
    q23_8   x1;
    q23_8   z1;
    q23_8   x0;
    q23_8   z0;
    q19_12  var_v1;

    if (state->field_2C.vx <= state->field_3C)
    {
        x0 = state->field_2C.vx;
        z0 = state->field_3C;
    }
    else
    {
        x0 = state->field_3C;
        z0 = state->field_2C.vx;
    }

    if (state->field_2C.vz <= state->field_44)
    {
        z1 = state->field_2C.vz;
        x1 = state->field_44;
    }
    else
    {
        z1 = state->field_44;
        x1 = state->field_2C.vz;
    }

    bound = state->field_6C.field_C;
    if ((state->field_6C.field_0 + bound) < x0 || z0 < (state->field_6C.field_0 - bound))
    {
        return;
    }

    if ((state->field_6C.field_4 + bound) < z1 || x1 < (state->field_6C.field_4 - bound) ||
        ((state->field_2C.vy + state->field_4E) < state->field_6C.field_8 && (state->field_40 + state->field_4E) < state->field_6C.field_8) ||
        ((state->field_2C.vy + state->field_4C) > state->field_6C.field_A && state->field_6C.field_A < (state->field_40 + state->field_4C)))
    {
        return;
    }

    temp_v0 = func_8006C248(*(s32*)&state->field_58, state->field_5C,
                            state->field_6C.field_0 - state->field_2C.vx,
                            state->field_6C.field_4 - state->field_2C.vz,
                            bound);
    if (temp_v0 == NO_VALUE)
    {
        return;
    }

    temp_v0_2 = Q12_MULT(state->field_5C, temp_v0);
    if (temp_v0_2 >= state->field_8)
    {
        return;
    }

    sp18.vy = state->field_2C.vy + (Q12_MULT(state->field_50.vy, temp_v0));
    if (((sp18.vy + state->field_4E) < state->field_6C.field_8) || (state->field_6C.field_A < (sp18.vy + state->field_4C)))
    {
        if (state->field_50.vy == 0)
        {
            return;
        }

        if ((sp18.vy + state->field_4E) < state->field_6C.field_8)
        {
            var_v1 = Q12(state->field_6C.field_8 - (state->field_2C.vy + state->field_4E)) / state->field_50.vy;
            if (var_v1 > Q12(1.0f))
            {
                return;
            }
            sp18.vy = state->field_6C.field_8 - state->field_4E;
        }
        else
        {
            var_v1 = Q12(state->field_6C.field_A - (state->field_2C.vy + state->field_4C)) / state->field_50.vy;
            if (var_v1 > Q12(1.0f))
            {
                return;
            }
            sp18.vy = state->field_6C.field_A - state->field_4C;
        }

        sp18.vx = state->field_2C.vx + Q12_MULT(state->field_50.vx, var_v1);
        sp18.vz = state->field_2C.vz + Q12_MULT(state->field_50.vz, var_v1);
        if ((SQUARE(state->field_6C.field_0 - sp18.vx) + SQUARE(state->field_6C.field_4 - sp18.vz)) >= SQUARE(state->field_6C.field_C))
        {
            return;
        }
    }
    else
    {
        sp18.vx = state->field_2C.vx + Q12_MULT(state->field_50.vx, temp_v0);
        sp18.vz = state->field_2C.vz + Q12_MULT(state->field_50.vz, temp_v0);
    }

    state->field_8  = temp_v0_2;
    state->field_C  = sp18.vx;
    state->field_10 = sp18.vy;
    state->field_14 = sp18.vz;
    state->field_1C = state->field_6C.field_8;
    state->field_24 = sp18.vx - state->field_6C.field_0;
    state->field_26 = sp18.vz - state->field_6C.field_4;
    state->field_20 = chara;
    state->field_28 = 0;
}

void func_8006F250(s32* arg0, q19_12 posX, q19_12 posZ, q19_12 posDeltaX, q19_12 posDeltaZ) // 0x8006F250
{
    s32              i;
    s_func_8006F338* scratch;

    scratch = PSX_SCRATCH;

    func_8006F338(scratch, posX, posZ, posDeltaX, posDeltaZ);

    for (i = 0; i < D_800C4478.field_2; i++)
    {
        if (func_8006F3C4(scratch, D_800C4478.field_4[i]))
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

bool func_8006F3C4(s_func_8006F338* arg0, s_func_8006F8FC* arg1) // 0x8006F3C4
{
    s32    temp_s1;
    s32    var_v1;
    q19_12 minX;
    q19_12 maxX;
    q19_12 minZ;
    q19_12 maxZ;
    s32    var_s1;
    s32    var_v0;
    s32    var_v0_2;

    minX = Q12(arg1->positionX_0_1);
    maxX = Q12(arg1->positionX_0_1 + arg1->sizeX_0_21);
    minZ = Q12(arg1->positionZ_0_11);
    maxZ = Q12(arg1->positionZ_0_11 + arg1->sizeZ_0_25);

    if ((minX >= arg0->field_1C || arg0->field_18 >= maxX) &&
        (minZ >= arg0->field_24 || arg0->field_20 >= maxZ))
    {
        return false;
    }

    if (arg0->field_0 >= minX && maxX >= arg0->field_0 &&
        arg0->field_4 >= minZ && maxZ >= arg0->field_4)
    {
        arg0->field_28 = Q12(0.0f);
        arg0->field_2C = (-Q12(arg1->field_0_29) >> 1) - Q12(1.5f); // NOTE: `-` sign on the outside required for match.
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

        temp_s1 = func_80048E3C(FP_TO(arg0->field_10, Q12_SHIFT) >> 16, FP_TO(arg0->field_14, Q12_SHIFT) >> 16, FP_TO(var_v0_2 - arg0->field_4, Q12_SHIFT) >> 16,
                                FP_TO(minX - arg0->field_0, Q12_SHIFT) >> 16, FP_TO(maxX - arg0->field_0, Q12_SHIFT) >> 16);
        var_v0  = func_80048E3C(FP_TO(arg0->field_14, Q12_SHIFT) >> 16, FP_TO(arg0->field_10, Q12_SHIFT) >> 16, FP_TO(var_s1 - arg0->field_0, Q12_SHIFT) >> 16,
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
            arg0->field_2C = (-Q12(arg1->field_0_29) >> 1) - Q12(1.5f); // NOTE: `-` sign on the outside required for match.
        }
    }

    return arg0->field_28 == 0;
}

s32 func_8006F620(VECTOR3* pos, s_func_8006AB50* arg1, s32 arg2, s32 arg3) // 0x8006F620
{
    s32              x0;
    s32              z0;
    s32              x1;
    s32              z1;
    s32              sp28;
    s32              sp2C;
    s32              distX;
    s32              distZ;
    s32              temp_a0;
    s32              temp_s0;
    s32              max1;
    s32              temp_s0_3;
    s32              mag0;
    q19_12           angle;
    s32              var_s2;
    s32              i;
    q19_12           posX;
    q19_12           posZ;
    s32              result;
    s32              var_v1;
    s_func_8006F8FC* temp_s2;

    result = Q12(-16.0f);

    distX = Q12(0.0f);
    distZ = Q12(0.0f);
    posX  = pos->vx;
    posZ  = pos->vz;
    sp28  = arg1->position_0.vy + arg3;
    sp2C  = sp28 + pos->vy;

    for (i = 0; i < D_800C4478.field_2; i++)
    {
        temp_s2 = D_800C4478.field_4[i];
        temp_s0 = (-Q12(temp_s2->field_0_29) >> 1) - Q12(1.5f); // NOTE: `-` sign on the outside required for match.

        if ((sp2C - temp_s0) >= 0)
        {
            continue;
        }

        func_8006F8FC(&x0, &z0, arg1->position_0.vx + posX, arg1->position_0.vz + posZ, temp_s2);
        if (MAX(ABS(x0), ABS(z0)) >= arg2)
        {
            continue;
        }

        mag0 = Vc_VectorMagnitudeCalc(x0, Q12(0.0f), z0);
        if (mag0 >= arg2)
        {
            continue;
        }

        if (mag0 > 0)
        {
            func_8006F8FC(&x1, &z1, arg1->position_0.vx, arg1->position_0.vz, temp_s2);

            var_s2 = Q12(0.1f);

            max1 = Vc_VectorMagnitudeCalc(x1, Q12(0.0f), z1);

            if ((arg2 - max1) <= Q12(0.1f))
            {
                var_s2 = arg2 - max1;
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
            if (temp_s0 < result)
            {
                result = temp_s0;
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

    if (result != Q12(-16.0f))
    {
        var_v1  = Q12(0.1f);
        temp_a0 = result - sp28;

        if (temp_a0 < Q12(0.1f))
        {
            var_v1 = temp_a0;
        }

        if (pos->vy < var_v1)
        {
            pos->vy = var_v1;
        }
    }

    return result;
}

void func_8006F8FC(q19_12* outX, q19_12* outZ, q19_12 posX, q19_12 posZ, const s_func_8006F8FC* arg4) // 0x8006F8FC
{
    q19_12 minX;
    q19_12 maxX;
    q19_12 minZ;
    q19_12 maxZ;

    // TODO: Using `Q12` doesn't match? There's an identical block in `func_8006F3C4`.
    minX = FP_TO(arg4->positionX_0_1, Q12_SHIFT);
    maxX = FP_TO(arg4->positionX_0_1 + arg4->sizeX_0_21, Q12_SHIFT);
    minZ = FP_TO(arg4->positionZ_0_11, Q12_SHIFT);
    maxZ = FP_TO(arg4->positionZ_0_11 + arg4->sizeZ_0_25, Q12_SHIFT);

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
// CHARACTERS ANIMATION RELATED
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
        else if (i & 1)
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

        if (!func_8007029C(chara, dist, curAngleOffset + headingAngle))
        {
            angleOffset = curAngleOffset;
        }
    }

    if (angleOffset != NO_VALUE)
    {
        return func_8005BF38(angleOffset + headingAngle);
    }

    return Q12_ANGLE(360.0f);
}

q19_12 Chara_HeadingAngleGet(s_SubCharacter* chara, q19_12 dist, q19_12 targetPosX, q19_12 targetPosZ, q3_12 spanAngle, bool isClockwise) // 0x8006FAFC
{
    s16    spanAngleDiv3;
    q3_12  curAngle;
    q19_12 curPosZ;
    q19_12 curPosX;
    q25_6  curOffsetX;
    q25_6  curOffsetZ;
    q25_6  curDist;
    s32    i;
    q19_12 distMinOrMax;
    s32    stepCount;
    q3_12  unkAngle;

    // Define if distance should track minimum or maximum.
    distMinOrMax = Q12(0.0f);
    if (isClockwise)
    {
        distMinOrMax = INT_MAX;
    }

    spanAngleDiv3 = spanAngle / 3;
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
            curAngle = Q12(((i * 30) + (Rng_Rand16() % 30))) / 360;
        }
        else
        {
            curAngle = (chara->rotation_24.vy + ((i - 3) * spanAngleDiv3) + ((Rng_Rand16() % spanAngleDiv3) >> 1)) - (spanAngleDiv3 >> 2);
        }

        curPosX = chara->position_18.vx + Q12_MULT(dist, Math_Sin(curAngle));
        curPosZ = chara->position_18.vz + Q12_MULT(dist, Math_Cos(curAngle));

        if (!func_80070030(chara, curPosX, chara->position_18.vy, curPosZ))
        {
            curOffsetX = Q12_TO_Q6(targetPosX - curPosX);
            curOffsetZ = Q12_TO_Q6(targetPosZ - curPosZ);
            curDist    = SQUARE(curOffsetX) + SQUARE(curOffsetZ);
            if ((!isClockwise && (distMinOrMax < curDist)) ||
                ( isClockwise && (curDist      < distMinOrMax)))
            {
                distMinOrMax = curDist;
                unkAngle     = curAngle;
            }
        }
    }

    if (unkAngle != Q12_ANGLE(-360.0f))
    {
        return func_8005BF38(unkAngle);
    }

    return Q12_ANGLE(360.0f);
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

    if (func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                             g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) -
                      chara->rotation_24.vy) < 0)
    {
        distMult = (func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                        g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) -
                                 chara->rotation_24.vy) * 2) + Q12_ANGLE(360.0f);
    }
    else
    {
        distMult = (Q12_ANGLE(180.0f) - func_8005BF38((ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                                             g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) -
                                                      chara->rotation_24.vy))) * 2;
    }

    for (i = distMult; count > 0; count--)
    {
        distMult = Q12_MULT_PRECISE(distMult, i);
    }

    dist = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                               g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);
    distMax = baseDistMax + Q12_MULT_PRECISE(distStep, distMult);
    if (distMax < dist)
    {
        return false;
    }

    pos.vx = chara->position_18.vx;
    pos.vz = chara->position_18.vz;

    offset.vx = g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx;
    offset.vz = g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz;

    if ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1))
    {
        offset.vy = Q12(0.0f);
        pos.vy = g_SysWork.playerWork_4C.player_0.position_18.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_0;
    }
    else
    {
        pos.vy = chara->position_18.vy + chara->field_C8.field_6;
        offset.vy = (g_SysWork.playerWork_4C.player_0.position_18.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_6) -
                    (chara->position_18.vy - chara->field_C8.field_6);
    }

    // Maybe `sp10` is not `VECTOR3`. Might need to rewrite this whole function if its `s_RayData`?
    return func_8006DA08(&sp10, &pos, &offset, chara) == 0 || sp20.vx != 0;
}

bool func_80070030(s_SubCharacter* chara, q19_12 posX, q19_12 posY, q19_12 posZ)
{
    s_RayData ray;
    VECTOR3   offset; // Q19.12

    offset.vx = posX - chara->position_18.vx;
    offset.vy = posY - chara->position_18.vy;
    offset.vz = posZ - chara->position_18.vz;

    func_8006DB3C(&ray, &chara->position_18, &offset, chara);
}

bool func_80070084(s_SubCharacter* chara, q19_12 fromX, q19_12 fromY, q19_12 fromZ) // 0x80070084
{
    s_RayData ray;
    VECTOR3   dir; // Q19.12
    bool      isCharaMissed;

    dir.vx = fromX - chara->position_18.vx;
    dir.vy = fromY - chara->position_18.vy;
    dir.vz = fromZ - chara->position_18.vz;

    isCharaMissed = false;
    if (func_8006DB3C(&ray, &chara->position_18, &dir, chara))
    {
        isCharaMissed = ray.chara_10 == NULL;
    }
    return isCharaMissed;
}

bool func_800700F8(s_SubCharacter* npc, s_SubCharacter* player) // 0x800700F8
{
    s_RayData ray;
    VECTOR3   pos;    // Q19.12
    VECTOR3   offset; // Q19.12

    pos = npc->position_18;

    offset.vx = player->position_18.vx - npc->position_18.vx;
    offset.vy = Q12(-0.1f);
    offset.vz = player->position_18.vz - npc->position_18.vz;

    return func_8006DB3C(&ray, &pos, &offset, npc) && ray.chara_10 == NULL;
}

bool func_80070184(s_SubCharacter* chara, s32 arg1, q3_12 rotY) // 0x80070184
{
    q19_12 posX;
    q19_12 posY;
    q19_12 posZ;
    q19_12 sinRotY;
    q19_12 cosRotY;

    sinRotY = Math_Sin(rotY);
    posX    = chara->position_18.vx + Q12_MULT(arg1, sinRotY);

    cosRotY = Math_Cos(rotY);
    posY    = chara->position_18.vy;
    posZ    = chara->position_18.vz + Q12_MULT(arg1, cosRotY);

    // The calls to this often have a return, so assumed it just passes return of `func_80070084`.
    return func_80070084(chara, posX, posY, posZ);
}

bool func_80070208(s_SubCharacter* chara, q19_12 dist) // 0x80070208
{
    s_RayData var;
    VECTOR3           offset; // Q19.12
    bool              cond;

    offset.vx = Q12_MULT(dist, Math_Sin(chara->rotation_24.vy));
    offset.vy = Q12(0.0f);
    offset.vz = Q12_MULT(dist, Math_Cos(chara->rotation_24.vy));

    cond = false;
    if (func_8006DB3C(&var, &chara->position_18, &offset, chara))
    {
        cond = var.chara_10 > 0;
    }
    return cond;
}

s32 func_8007029C(s_SubCharacter* chara, q19_12 dist, q3_12 rotY) // 0x8007029C
{
    s_RayData var;
    VECTOR3           offset; // Q19.12

    offset.vx = Q12_MULT(dist, Math_Sin(rotY));
    offset.vy = Q12(0.0f);
    offset.vz = Q12_MULT(dist, Math_Cos(rotY));

    return func_8006DB3C(&var, &chara->position_18, &offset, chara);
}

bool func_80070320(void) // 0x80070320
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcIdxs_2354); i++)
    {
        if (g_SysWork.npcIdxs_2354[i] != NO_VALUE)
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
        deltaX = g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx;
        deltaX = Q12_TO_Q6(deltaX);

        deltaZ = g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz;
        deltaZ = Q12_TO_Q6(deltaZ);

        dist = SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ));
        dist = Q6_TO_Q12(dist);
    }

    // TODO: Why `>> 8`?
    result = Q12_MULT(arg2, g_SysWork.playerWork_4C.player_0.properties_E4.player.field_10C) - (dist >> 8);
    if (result < 0)
    {
        result = 0;
    }
    return result;
}

void func_80070400(s_SubCharacter* chara, s_Keyframe* keyframe0, s_Keyframe* keyframe1) // 0x80070400
{
    q19_12 alpha;
    q19_12 invAlpha;

    // Compute alpha.
    if (ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0))
    {
        alpha = Q12_FRACT(chara->model_0.anim_4.time_4);
    }
    else
    {
        alpha = chara->model_0.anim_4.alpha_A;
    }

    // Compute inverse alpha.
    invAlpha = Q12(1.0f) - alpha;

    chara->field_C8.field_0   = FP_FROM((keyframe0->field_0 * invAlpha) + (keyframe1->field_0 * alpha), Q12_SHIFT);
    chara->field_C8.field_2   = FP_FROM((keyframe0->field_2 * invAlpha) + (keyframe1->field_2 * alpha), Q12_SHIFT);
    chara->field_C8.field_4   = FP_FROM((keyframe0->field_4 * invAlpha) + (keyframe1->field_4 * alpha), Q12_SHIFT);
    chara->field_C8.field_6   = FP_FROM((keyframe0->field_6 * invAlpha) + (keyframe1->field_6 * alpha), Q12_SHIFT);
    chara->field_D8.offsetX_4 = FP_FROM((keyframe0->field_10 * invAlpha) + (keyframe1->field_10 * alpha), Q12_SHIFT);
    chara->field_D8.offsetZ_6 = FP_FROM((keyframe0->field_12 * invAlpha) + (keyframe1->field_12 * alpha), Q12_SHIFT);
    chara->field_D4.radius_0  = FP_FROM((keyframe0->field_8 * invAlpha) + (keyframe1->field_8 * alpha), Q12_SHIFT);
    chara->field_D8.offsetX_0 = FP_FROM((keyframe0->field_C * invAlpha) + (keyframe1->field_C * alpha), Q12_SHIFT);
    chara->field_D8.offsetZ_2 = FP_FROM((keyframe0->field_E * invAlpha) + (keyframe1->field_E * alpha), Q12_SHIFT);
    chara->field_D4.field_2   = FP_FROM((keyframe0->field_A * invAlpha) + (keyframe1->field_A * alpha), Q12_SHIFT);
}

void func_800705E4(GsCOORDINATE2* coord, s32 idx, q19_12 scaleX, q19_12 scaleY, q19_12 scaleZ) // 0x800705E4
{
    q3_12 scales[3];
    s32   row;
    s32   col;

    scales[0] = scaleX;
    scales[1] = scaleY;
    scales[2] = scaleZ;

    for (col = 0; col < ARRAY_SIZE(scales); col++)
    {
        if (scales[col] != Q12(1.0f))
        {
            for (row = 0; row < 3; row++)
            {
                coord[idx].coord.m[row][col] = Q12_MULT_PRECISE(scales[col], coord[idx].coord.m[row][col]);
            }
        }
    }

    coord->flg = false;
}

// Used to overwrite `HARRY_BASE_ANIM_INFOS[56:76]` with weapon-specific animations.
// Always copies 20 `s_AnimInfo`s, but most weapons use less than that.
// @bug `EquippedWeaponId_HyperBlaster` will copy past the end of this array?
const s_AnimInfo D_80028B94[] = {
/* `EquippedWeaponId_Axe` */
/* 0   */ { Anim_Update2, ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 1   */ { Anim_Update0, ANIM_STATUS(28, true), false, ANIM_STATUS(28, true), { Q12(25.0f) }, 568, 577 },
/* 2   */ { Anim_Update2, ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 579 },
/* 3   */ { Anim_Update0, ANIM_STATUS(29, true), false, ANIM_STATUS(29, true), { Q12(20.0f) }, 579, 598 },
/* 4   */ { Anim_Update2, ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 599 },
/* 5   */ { Anim_Update0, ANIM_STATUS(30, true), false, ANIM_STATUS(30, true), { Q12(18.0f) }, 599, 615 },
/* 6   */ { Anim_Update2, ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 616 },
/* 7   */ { Anim_Update0, ANIM_STATUS(31, true), false, ANIM_STATUS(31, true), { Q12(20.0f) }, 616, 635 },
/* 8   */ { Anim_Update2, ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 577 },
/* 9   */ { Anim_Update0, ANIM_STATUS(32, true), false, ANIM_STATUS(32, true), { Q12(-35.0f) }, 568, 577 },

/* `EquippedWeaponId_Hammer` */
/* 10  */ { Anim_Update2, ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 11  */ { Anim_Update0, ANIM_STATUS(28, true), false, ANIM_STATUS(28, true), { Q12(40.0f) }, 568, 579 },
/* 12  */ { Anim_Update2, ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 584 },
/* 13  */ { Anim_Update0, ANIM_STATUS(29, true), false, ANIM_STATUS(29, true), { Q12(22.0f) }, 584, 613 },
/* 14  */ { Anim_Update2, ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 614 },
/* 15  */ { Anim_Update0, ANIM_STATUS(30, true), false, ANIM_STATUS(30, true), { Q12(16.0f) }, 614, 634 },
/* 16  */ { Anim_Update2, ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 637 },
/* 17  */ { Anim_Update0, ANIM_STATUS(31, true), false, ANIM_STATUS(31, true), { Q12(18.0f) }, 637, 659 },
/* 18  */ { Anim_Update2, ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 579 },
/* 19  */ { Anim_Update0, ANIM_STATUS(32, true), false, ANIM_STATUS(32, true), { Q12(-35.0f) }, 568, 579 },

/* `EquippedWeaponId_SteelPipe` */
/* 20  */ { Anim_Update2, ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 21  */ { Anim_Update0, ANIM_STATUS(28, true), false, ANIM_STATUS(28, true), { Q12(45.0f) }, 568, 579 },
/* 22  */ { Anim_Update2, ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 584 },
/* 23  */ { Anim_Update0, ANIM_STATUS(29, true), false, ANIM_STATUS(29, true), { Q12(25.0f) }, 584, 613 },
/* 24  */ { Anim_Update2, ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 614 },
/* 25  */ { Anim_Update0, ANIM_STATUS(30, true), false, ANIM_STATUS(30, true), { Q12(16.0f) }, 614, 634 },
/* 26  */ { Anim_Update2, ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 637 },
/* 27  */ { Anim_Update0, ANIM_STATUS(31, true), false, ANIM_STATUS(31, true), { Q12(20.0f) }, 637, 659 },
/* 28  */ { Anim_Update2, ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 579 },
/* 29  */ { Anim_Update0, ANIM_STATUS(32, true), false, ANIM_STATUS(32, true), { Q12(-40.0f) }, 568, 579 },

/* `EquippedWeaponId_KitchenKnife` */
/* 30  */ { Anim_Update2, ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 31  */ { Anim_Update0, ANIM_STATUS(28, true), false, ANIM_STATUS(28, true), { Q12(30.0f) }, 568, 575 },
/* 32  */ { Anim_Update2, ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 581 },
/* 33  */ { Anim_Update0, ANIM_STATUS(29, true), false, ANIM_STATUS(29, true), { Q12(20.0f) }, 581, 595 },
/* 34  */ { Anim_Update2, ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 596 },
/* 35  */ { Anim_Update0, ANIM_STATUS(30, true), false, ANIM_STATUS(30, true), { Q12(16.0f) }, 596, 611 },
/* 36  */ { Anim_Update2, ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 613 },
/* 37  */ { Anim_Update0, ANIM_STATUS(31, true), false, ANIM_STATUS(31, true), { Q12(16.0f) }, 613, 629 },
/* 38  */ { Anim_Update2, ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 577 },
/* 39  */ { Anim_Update0, ANIM_STATUS(32, true), false, ANIM_STATUS(32, true), { Q12(-40.0f) }, 568, 577 },

/* `EquippedWeaponId_Katana` */
/* 40  */ { Anim_Update2, ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 41  */ { Anim_Update0, ANIM_STATUS(28, true), false, ANIM_STATUS(28, true), { Q12(30.0f) }, 568, 579 },
/* 42  */ { Anim_Update2, ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 580 },
/* 43  */ { Anim_Update0, ANIM_STATUS(29, true), false, ANIM_STATUS(29, true), { Q12(25.0f) }, 580, 597 },
/* 44  */ { Anim_Update2, ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 598 },
/* 45  */ { Anim_Update0, ANIM_STATUS(30, true), false, ANIM_STATUS(30, true), { Q12(16.0f) }, 598, 611 },
/* 46  */ { Anim_Update2, ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 615 },
/* 47  */ { Anim_Update0, ANIM_STATUS(31, true), false, ANIM_STATUS(31, true), { Q12(16.0f) }, 615, 625 },
/* 48  */ { Anim_Update2, ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 579 },
/* 49  */ { Anim_Update0, ANIM_STATUS(32, true), false, ANIM_STATUS(32, true), { Q12(-35.0f) }, 568, 579 },

/* `EquippedWeaponId_Chainsaw` */
/* 50  */ { Anim_Update2, ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 51  */ { Anim_Update0, ANIM_STATUS(28, true), false, ANIM_STATUS(28, true), { Q12(15.0f) }, 568, 583 },
/* 52  */ { Anim_Update2, ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 584 },
/* 53  */ { Anim_Update0, ANIM_STATUS(29, true), false, ANIM_STATUS(29, true), { Q12(16.0f) }, 584, 602 },
/* 54  */ { Anim_Update2, ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 603 },
/* 55  */ { Anim_Update0, ANIM_STATUS(30, true), false, ANIM_STATUS(30, true), { Q12(14.0f) }, 603, 618 },
/* 56  */ { Anim_Update2, ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 619 },
/* 57  */ { Anim_Update0, ANIM_STATUS(31, true), false, ANIM_STATUS(31, true), { Q12(14.0f) }, 619, 637 },
/* 58  */ { Anim_Update2, ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 649 },
/* 59  */ { Anim_Update0, ANIM_STATUS(32, true), false, ANIM_STATUS(32, true), { Q12(-35.0f) }, 638, 649 },
/* 60  */ { Anim_Update2, ANIM_STATUS(33, false), false, ANIM_STATUS(33, true), { Q12(100.0f) }, NO_VALUE, 638 },
/* 61  */ { Anim_Update0, ANIM_STATUS(33, true), false, ANIM_STATUS(33, true), { Q12(24.0f) }, 638, 649 },
/* 62  */ { Anim_Update2, ANIM_STATUS(34, false), false, ANIM_STATUS(34, true), { Q12(100.0f) }, NO_VALUE, 650 },
/* 63  */ { Anim_Update1, ANIM_STATUS(34, true), false, NO_VALUE, { Q12(20.0f) }, 650, 655 },

/* `EquippedWeaponId_RockDrill` */
/* 64  */ { Anim_Update2, ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 65  */ { Anim_Update0, ANIM_STATUS(28, true), false, ANIM_STATUS(28, true), { Q12(18.0f) }, 568, 583 },
/* 66  */ { Anim_Update2, ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 584 },
/* 67  */ { Anim_Update0, ANIM_STATUS(29, true), false, ANIM_STATUS(29, true), { Q12(24.0f) }, 584, 597 },
/* 68  */ { Anim_Update2, ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 598 },
/* 69  */ { Anim_Update0, ANIM_STATUS(30, true), false, ANIM_STATUS(30, true), { Q12(20.0f) }, 598, 611 },
/* 70  */ { Anim_Update2, ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 612 },
/* 71  */ { Anim_Update0, ANIM_STATUS(31, true), false, ANIM_STATUS(31, true), { Q12(22.0f) }, 612, 625 },
/* 72  */ { Anim_Update2, ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 636 },
/* 73  */ { Anim_Update0, ANIM_STATUS(32, true), false, ANIM_STATUS(32, true), { Q12(-25.0f) }, 626, 636 },
/* 74  */ { Anim_Update2, ANIM_STATUS(33, false), false, ANIM_STATUS(33, true), { Q12(100.0f) }, NO_VALUE, 626 },
/* 75  */ { Anim_Update0, ANIM_STATUS(33, true), false, ANIM_STATUS(33, true), { Q12(23.0f) }, 626, 636 },
/* 76  */ { Anim_Update2, ANIM_STATUS(34, false), false, ANIM_STATUS(34, true), { Q12(100.0f) }, NO_VALUE, 637 },
/* 77  */ { Anim_Update1, ANIM_STATUS(34, true), false, NO_VALUE, { Q12(24.0f) }, 637, 640 },

/* `EquippedWeaponId_Handgun` */
/* 78  */ { Anim_Update2, ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 570 },
/* 79  */ { Anim_Update0, ANIM_STATUS(28, true), false, ANIM_STATUS(28, true), { Q12(35.0f) }, 570, 579 },
/* 80  */ { Anim_Update2, ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 582 },
/* 81  */ { Anim_Update0, ANIM_STATUS(29, true), false, ANIM_STATUS(29, true), { Q12(40.0f) }, 582, 592 },
/* 82  */ { Anim_Update2, ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 594 },
/* 83  */ { Anim_Update0, ANIM_STATUS(30, true), false, ANIM_STATUS(30, true), { Q12(25.0f) }, 594, 604 },
/* 84  */ { Anim_Update2, ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 605 },
/* 85  */ { Anim_Update0, ANIM_STATUS(31, true), false, ANIM_STATUS(31, true), { Q12(30.0f) }, 605, 658 },
/* 86  */ { Anim_Update2, ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 570 },
/* 87  */ { Anim_Update0, ANIM_STATUS(32, true), false, ANIM_STATUS(32, true), { Q12(60.0f) }, 570, 592 },
/* 88  */ { Anim_Update2, ANIM_STATUS(33, false), false, ANIM_STATUS(33, true), { Q12(100.0f) }, NO_VALUE, 579 },
/* 89  */ { Anim_Update0, ANIM_STATUS(33, true), false, ANIM_STATUS(33, true), { Q12(-35.0f) }, 570, 579 },
/* 90  */ { Anim_Update2, ANIM_STATUS(34, false), false, ANIM_STATUS(34, true), { Q12(100.0f) }, NO_VALUE, 592 },
/* 91  */ { Anim_Update0, ANIM_STATUS(34, true), false, ANIM_STATUS(34, true), { Q12(-35.0f) }, 580, 592 },
/* 92  */ { Anim_Update2, ANIM_STATUS(35, false), false, ANIM_STATUS(35, true), { Q12(100.0f) }, NO_VALUE, 592 },
/* 93  */ { Anim_Update0, ANIM_STATUS(35, true), false, ANIM_STATUS(35, true), { Q12(-30.0f) }, 570, 592 },
/* 94  */ { Anim_Update2, ANIM_STATUS(36, false), false, ANIM_STATUS(36, true), { Q12(100.0f) }, NO_VALUE, 582 },
/* 95  */ { Anim_Update0, ANIM_STATUS(36, true), false, ANIM_STATUS(36, true), { Q12(25.0f) }, 582, 604 },

/* `EquippedWeaponId_HuntingRifle` */
/* 96  */ { Anim_Update2, ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 97  */ { Anim_Update0, ANIM_STATUS(28, true), false, ANIM_STATUS(28, true), { Q12(35.0f) }, 568, 587 },
/* 98  */ { Anim_Update2, ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 588 },
/* 99  */ { Anim_Update0, ANIM_STATUS(29, true), false, ANIM_STATUS(29, true), { Q12(25.0f) }, 588, 597 },
/* 100 */ { Anim_Update2, ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 598 },
/* 101 */ { Anim_Update0, ANIM_STATUS(30, true), false, ANIM_STATUS(30, true), { Q12(16.0f) }, 598, 607 },
/* 102 */ { Anim_Update2, ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 608 },
/* 103 */ { Anim_Update0, ANIM_STATUS(31, true), false, ANIM_STATUS(31, true), { Q12(20.0f) }, 608, 642 },
/* 104 */ { Anim_Update2, ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 588 },
/* 105 */ { Anim_Update0, ANIM_STATUS(32, true), false, ANIM_STATUS(32, true), { Q12(25.0f) }, 588, 597 },
/* 106 */ { Anim_Update2, ANIM_STATUS(33, false), false, ANIM_STATUS(33, true), { Q12(100.0f) }, NO_VALUE, 597 },
/* 107 */ { Anim_Update0, ANIM_STATUS(33, true), false, ANIM_STATUS(33, true), { Q12(-30.0f) }, 588, 597 },
/* 108 */ { Anim_Update2, ANIM_STATUS(34, false), false, ANIM_STATUS(34, true), { Q12(100.0f) }, NO_VALUE, 597 },
/* 109 */ { Anim_Update0, ANIM_STATUS(34, true), false, ANIM_STATUS(34, true), { Q12(-30.0f) }, 597, 597 },
/* 110 */ { Anim_Update2, ANIM_STATUS(35, false), false, ANIM_STATUS(35, true), { Q12(100.0f) }, NO_VALUE, 587 },
/* 111 */ { Anim_Update0, ANIM_STATUS(35, true), false, ANIM_STATUS(35, true), { Q12(-22.0f) }, 568, 587 },
/* 112 */ { Anim_Update2, ANIM_STATUS(36, false), false, ANIM_STATUS(36, true), { Q12(100.0f) }, NO_VALUE, 598 },
/* 113 */ { Anim_Update0, ANIM_STATUS(36, true), false, ANIM_STATUS(36, true), { Q12(16.0f) }, 598, 607 },

/* `EquippedWeaponId_Shotgun` */
/* 114 */ { Anim_Update2, ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 570 },
/* 115 */ { Anim_Update0, ANIM_STATUS(28, true), false, ANIM_STATUS(28, true), { Q12(40.0f) }, 570, 579 },
/* 116 */ { Anim_Update2, ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 582 },
/* 117 */ { Anim_Update0, ANIM_STATUS(29, true), false, ANIM_STATUS(29, true), { Q12(30.0f) }, 582, 592 },
/* 118 */ { Anim_Update2, ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 594 },
/* 119 */ { Anim_Update0, ANIM_STATUS(30, true), false, ANIM_STATUS(30, true), { Q12(22.0f) }, 594, 604 },
/* 120 */ { Anim_Update2, ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 605 },
/* 121 */ { Anim_Update0, ANIM_STATUS(31, true), false, ANIM_STATUS(31, true), { Q12(17.0f) }, 605, 641 },
/* 122 */ { Anim_Update2, ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 570 },
/* 123 */ { Anim_Update0, ANIM_STATUS(32, true), false, ANIM_STATUS(32, true), { Q12(60.0f) }, 570, 592 },
/* 124 */ { Anim_Update2, ANIM_STATUS(33, false), false, ANIM_STATUS(33, true), { Q12(100.0f) }, NO_VALUE, 579 },
/* 125 */ { Anim_Update0, ANIM_STATUS(33, true), false, ANIM_STATUS(33, true), { Q12(-40.0f) }, 570, 579 },
/* 126 */ { Anim_Update2, ANIM_STATUS(34, false), false, ANIM_STATUS(34, true), { Q12(100.0f) }, NO_VALUE, 592 },
/* 127 */ { Anim_Update0, ANIM_STATUS(34, true), false, ANIM_STATUS(34, true), { Q12(-40.0f) }, 580, 592 },
/* 128 */ { Anim_Update2, ANIM_STATUS(35, false), false, ANIM_STATUS(35, true), { Q12(100.0f) }, NO_VALUE, 592 },
/* 129 */ { Anim_Update0, ANIM_STATUS(35, true), false, ANIM_STATUS(35, true), { Q12(-20.0f) }, 570, 592 },
/* 130 */ { Anim_Update2, ANIM_STATUS(36, false), false, ANIM_STATUS(36, true), { Q12(100.0f) }, NO_VALUE, 582 },
/* 131 */ { Anim_Update0, ANIM_STATUS(36, true), false, ANIM_STATUS(36, true), { Q12(22.0f) }, 582, 604 },

/* `EquippedWeaponId_HyperBlaster` */
/* 132 */ { Anim_Update2, ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 133 */ { Anim_Update0, ANIM_STATUS(28, true), false, ANIM_STATUS(28, true), { Q12(24.0f) }, 568, 574 },
/* 134 */ { Anim_Update2, ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(100.0f) }, NO_VALUE, 574 },
/* 135 */ { Anim_Update0, ANIM_STATUS(29, true), false, ANIM_STATUS(29, true), { Q12(20.0f) }, 574, 574 },
/* 136 */ { Anim_Update2, ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(100.0f) }, NO_VALUE, 575 },
/* 137 */ { Anim_Update0, ANIM_STATUS(30, true), false, ANIM_STATUS(30, true), { Q12(20.0f) }, 575, 579 },
/* 138 */ { Anim_Update2, ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 139 */ { Anim_Update0, ANIM_STATUS(31, true), false, ANIM_STATUS(31, true), { Q12(17.0f) }, 568, 568 },
/* 140 */ { Anim_Update2, ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(100.0f) }, NO_VALUE, 568 },
/* 141 */ { Anim_Update0, ANIM_STATUS(32, true), false, ANIM_STATUS(32, true), { Q12(24.0f) }, 568, 574 },
/* 142 */ { Anim_Update2, ANIM_STATUS(33, false), false, ANIM_STATUS(33, true), { Q12(100.0f) }, NO_VALUE, 574 },
/* 143 */ { Anim_Update0, ANIM_STATUS(33, true), false, ANIM_STATUS(33, true), { Q12(-20.0f) }, 568, 574 },
/* 144 */ { Anim_Update2, ANIM_STATUS(34, false), false, ANIM_STATUS(34, true), { Q12(100.0f) }, NO_VALUE, 574 },
/* 145 */ { Anim_Update0, ANIM_STATUS(34, true), false, ANIM_STATUS(34, true), { Q12(-20.0f) }, 574, 574 },
/* 146 */ { Anim_Update2, ANIM_STATUS(35, false), false, ANIM_STATUS(35, true), { Q12(100.0f) }, NO_VALUE, 574 },
/* 147 */ { Anim_Update0, ANIM_STATUS(35, true), false, ANIM_STATUS(35, true), { Q12(-20.0f) }, 568, 574 },
/* 148 */ { Anim_Update2, ANIM_STATUS(36, false), false, ANIM_STATUS(36, true), { Q12(100.0f) }, NO_VALUE, 574 },
/* 149 */ { Anim_Update0, ANIM_STATUS(36, true), false, ANIM_STATUS(36, true), { Q12(20.0f) }, 574, 579 }
};

// Unused data?
INCLUDE_RODATA("bodyprog/nonmatchings/bodyprog_800697EC", D_800294F4);
