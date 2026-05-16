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

void func_8005C814(s_CharaShapeOffsets* offsets, s_SubCharacter* chara) // 0x8005C814
{
    q3_12 sinRotY;
    q3_12 cosRotY;
    q3_12 offsetX0;
    q3_12 offsetX1;
    q3_12 offsetZ0;
    q3_12 offsetZ1;

    offsetX0 = offsets->box.vx;
    offsetZ0 = offsets->box.vz;
    offsetX1 = offsets->cylinder.vx;
    offsetZ1 = offsets->cylinder.vz;

    cosRotY = Math_Cos(chara->rotation.vy);
    sinRotY = Math_Sin(chara->rotation.vy);

    chara->collision.shapeOffsets.box.vx = FP_FROM(( offsetX0 * cosRotY) + (offsetZ0 * sinRotY), Q12_SHIFT);
    chara->collision.shapeOffsets.box.vz = FP_FROM((-offsetX0 * sinRotY) + (offsetZ0 * cosRotY), Q12_SHIFT);
    chara->collision.shapeOffsets.cylinder.vx = FP_FROM(( offsetX1 * cosRotY) + (offsetZ1 * sinRotY), Q12_SHIFT);
    chara->collision.shapeOffsets.cylinder.vz = FP_FROM((-offsetX1 * sinRotY) + (offsetZ1 * cosRotY), Q12_SHIFT);
}

s32 func_8005C944(s_SubCharacter* chara, s_CollisionResult* collResult) // 0x8005C944
{
    s_CollisionResult collResult0;
    VECTOR3           offset;
    q3_12             headingAngle;
    s32               temp_s0;
    s32               temp_s0_2;
    s32               temp_s2;
    s32               temp_s3;
    s32               temp_v0;
    q19_12            sinHeadingAngle;
    s32               wallResponse;

    headingAngle = chara->headingAngle;
    temp_s0 = Q12_MULT_PRECISE(g_DeltaTime, chara->moveSpeed);
    temp_s2 = OVERFLOW_GUARD(temp_s0);
    temp_s3 = temp_s2 >> 1;

    sinHeadingAngle = Math_Sin(headingAngle);
    temp_s0_2       = temp_s0 >> temp_s3;
    temp_v0         = sinHeadingAngle >> temp_s3;

    offset.vx = Q12_MULT_PRECISE(temp_s0_2, temp_v0) << temp_s2;
    offset.vz = Q12_MULT_PRECISE(temp_s0_2, Math_Cos(headingAngle) >> temp_s3) << temp_s2;
    offset.vy = Q12_MULT_PRECISE(g_DeltaTime, chara->fallSpeed);

    wallResponse = Collision_WallDetect(&collResult0, &offset, chara);

    chara->position.vx += collResult0.offset.vx;
    chara->position.vy += collResult0.offset.vy;
    chara->position.vz += collResult0.offset.vz;

    if (chara->position.vy > collResult0.collision.groundHeight)
    {
        chara->position.vy = collResult0.collision.groundHeight;
        chara->fallSpeed   = Q12(0.0f);
    }

    if (collResult != NULL)
    {
        *collResult = collResult0;
    }

    return wallResponse;
}

s32 func_8005CB20(s_SubCharacter* chara, s_CollisionResult* collResult, q3_12 offsetX, q3_12 offsetZ) // 0x8005CB20
{
    s_CollisionResult collResult0;
    VECTOR3           offset; // Q19.12
    q19_12            headingAngle;
    s32               temp_s0;
    s32               temp_s0_2;
    s32               temp_s2;
    s32               temp_s3;
    s32               temp_v0_2;
    s32               temp_v0_4;
    q19_12            sinHeadingAngle;
    s32               ret;

    headingAngle = chara->headingAngle;
    temp_s0 = Q12_MULT_PRECISE(g_DeltaTime, chara->moveSpeed);
    temp_s2 = OVERFLOW_GUARD(temp_s0);
    temp_s3 = temp_s2 >> 1;

    sinHeadingAngle = Math_Sin(headingAngle);
    temp_s0_2 = temp_s0 >> temp_s3;
    temp_v0_2 = sinHeadingAngle >> temp_s3;
    offset.vx = (s32)Q12_MULT_PRECISE(temp_s0_2, temp_v0_2) << temp_s2;

    temp_v0_4 = Math_Cos(headingAngle) >> temp_s3;
    offset.vz = (s32)Q12_MULT_PRECISE(temp_s0_2, temp_v0_4) << temp_s2;

    sinHeadingAngle = chara->fallSpeed;
    offset.vx += offsetX;
    offset.vy  = Q12_MULT_PRECISE(g_DeltaTime, sinHeadingAngle);
    offset.vz += offsetZ;

    ret = Collision_WallDetect(&collResult0, &offset, chara);

    chara->position.vx += collResult0.offset.vx;
    chara->position.vy += collResult0.offset.vy;
    chara->position.vz += collResult0.offset.vz;

    if (chara->position.vy > collResult0.collision.groundHeight)
    {
        chara->position.vy = collResult0.collision.groundHeight;
        chara->fallSpeed   = Q12(0.0f);
    }

    if (collResult != NULL)
    {
        *collResult = collResult0;
    }

    return ret;
}

#ifndef NON_MATCHING
INCLUDE_ASM("bodyprog/nonmatchings/bodyprog_combat_8005BF38", func_8005CD38); // 0x8005CD38
#else
// Important for combat.
void func_8005CD38(s32* outNpcIdx, s16* outAngle, s_PlayerCombat* combat, s32 angleConstraint, s32 range, s32 mode) // 0x8005CD38
{
    s32 _pad[4];
    VECTOR3 rayFrom;
    s_RayData ray;
    VECTOR3 rayDir;
    s32 projX;
    s32 projZ;
    VECTOR3 npcPos;
    s32 npcIndices[6];
    s16 elevAngles[6];
    s16 horizAngles[6];
    s32 distances[6];
    s32 combatY;
    s32 rangeSqQ6;
    s32 combatX;
    s32 combatZ;
    s32 candidateCount;
    s32 npcOffset;
    u8* new_var;
    s_SysWork* sysWork;
    s32 i;
    s_SysWork* npcPtr;
    s16 angleCon;
    s_SubCharacter* new_var2;
    asm volatile("" : "+m" (mode), "+m" (_pad));
    combatX = combat->field_0.vx;
    combatY = combat->field_0.vy;
    combatZ = combat->field_0.vz;
    rangeSqQ6 = ((range) >> 6) * ((range) >> 6);
    candidateCount = 0;
    i = candidateCount;
    angleCon = (s16)angleConstraint;
    sysWork = &g_SysWork;
    npcPtr = sysWork;
    npcOffset = candidateCount;
    rayFrom.vx = combatX;
    rayFrom.vy = combatY;
    rayFrom.vz = combatZ;
    *outNpcIdx = -1;
    do
    {
        if (npcPtr->npcs_1A0[0].model_0.charaId_0 == Chara_None)
        {
            goto next_npc;
        }
        if (npcPtr->npcs_1A0[0].health_B0 < 0)
        {
            goto next_npc;
        }
        npcPos.vx = npcPtr->npcs_1A0[0].position_18.vx + npcPtr->npcs_1A0[0].field_D8.offsetX_0;
        npcPos.vy = npcPtr->npcs_1A0[0].position_18.vy + npcPtr->npcs_1A0[0].field_C8.field_6;
        npcPos.vz = npcPtr->npcs_1A0[0].position_18.vz + npcPtr->npcs_1A0[0].field_D8.offsetZ_2;
        if (mode < 3)
        {
            s32 dx = ((combatX - npcPos.vx) >> 6);
            s32 dy = ((combatY - npcPos.vy) >> 6);
            s32 dz = ((combatZ - npcPos.vz) >> 6);
            if (rangeSqQ6 < dx * dx + dy * dy + dz * dz)
            {
                goto next_npc;
            }
            {
                s16* hPtr = (s16*)((u8*)horizAngles + npcOffset);
                *(u16*)hPtr = ratan2(npcPos.vx - combatX, npcPos.vz - combatZ);
                {
                    s16 angleDiff;
                    s16 wrapped;
                    wrapped = func_8005BF38((s16)((u16)sysWork->playerWork_4C.player_0.rotation_24.vy - *(u16*)hPtr));
                    if ((s32)(wrapped << 16) < 0)
                    {
                        angleDiff = -func_8005BF38((s16)((u16)sysWork->playerWork_4C.player_0.rotation_24.vy - *(u16*)hPtr));
                    }
                    else
                    {
                        angleDiff = func_8005BF38((s16)((u16)sysWork->playerWork_4C.player_0.rotation_24.vy - *(u16*)hPtr));
                    }
                    if (angleCon < angleDiff)
                    {
                        goto next_npc;
                    }
                }
            }
            if (mode != 0)
            {
                if (sysWork->targetNpcIdx_2353 == i)
                {
                    goto next_npc;
                }
                {
                    s16* hPtr = (s16*)((u8*)horizAngles + npcOffset);
                    s16 relAngle;
                    relAngle = func_8005BF38((s16)(*(u16*)hPtr - (u16)sysWork->playerWork_4C.player_0.field_2A));
                    *(u16*)hPtr = relAngle;
                    if (mode == 1)
                    {
                        if ((s32)(relAngle << 16) < 0)
                        {
                            goto next_npc;
                        }
                    }
                    if (mode == 2)
                    {
                        if ((s32)(relAngle << 16) > 0)
                        {
                            i += 1;
                            goto loop_end;
                        }
                    }
                }
            }
        }
        else
        {
            projX = combatX + (((angleCon) * (Math_Sin((s32)sysWork->playerWork_4C.player_0.rotation_24.vy))) >> (12));
            new_var = (u8*)(&horizAngles[0]);
            {
                s32 dx = ((projX - npcPos.vx) >> 6);
                s32 cosVal = (((angleCon) * (Math_Cos((s32)sysWork->playerWork_4C.player_0.rotation_24.vy))) >> (12));
                s32 dz;
                projZ = combatZ + cosVal;
                dz = ((projZ - npcPos.vz) >> 6);
                if (rangeSqQ6 < dx * dx + dz * dz)
                {
                    goto next_npc;
                }
            }
            {
                s16* hPtr = (s16*)(new_var + npcOffset);
                *hPtr = func_8005BF38((s16)(ratan2(npcPos.vx - combatX, npcPos.vz - combatZ) - (u16)sysWork->playerWork_4C.player_0.rotation_24.vy));
            }
            if (mode != 3)
            {
                s32 hx = ((npcPos.vx - combatX) >> 6);
                s32 hz = ((npcPos.vz - combatZ) >> 6);
                distances[candidateCount] = ((SquareRoot0(hx * hx + hz * hz)) << 6);
            }
        }
        {
            s32 hx = ((npcPos.vx - combatX) >> 6);
            s32 hz = ((npcPos.vz - combatZ) >> 6);
            s16 elevAngle;
            s16* elevPtr;
            elevAngle = ratan2(((SquareRoot0(hx * hx + hz * hz)) << 6), npcPos.vy - combatY);
            elevPtr = (s16*)((u8*)elevAngles + npcOffset);
            *elevPtr = elevAngle;
            if (elevAngle < 0)
            {
                goto next_npc;
            }
            if (elevAngle >= 0x801)
            {
                goto next_npc;
            }
            if ((u32)(mode - 1) < 2u)
            {
            }
            else if (sysWork->targetNpcIdx_2353 == i)
            {
                *outNpcIdx = i;
                *outAngle = (u16)*elevPtr;
                goto end;
            }
            npcIndices[candidateCount] = i;
            npcOffset += 2;
            candidateCount += 1;
        }
    next_npc:
        i += 1;
    loop_end:
        npcPtr = (s_SysWork*)((u8*)npcPtr + 0x128);
    } while (i < 6);
    if (candidateCount == 0)
    {
        goto end;
    }
    if (candidateCount <= 0)
    {
        goto end;
    }
    {
        s32 outerIdx;
        s32* outerNpcPtr;
        s32 outerIdxX4;
        outerIdx = 0;
        sysWork = (s_SysWork*)((u8*)&g_SysWork + 0x1A0);
        outerNpcPtr = &npcIndices[0];
        outerIdxX4 = 0;
        do
        {
            s32 j = outerIdx + 1;
            new_var2 = g_SysWork.npcs_1A0;
            if (j < candidateCount)
            {
                s16* outerHorizAngle = &horizAngles[outerIdx];
                s32* outerDist = (s32*)((u8*)distances + outerIdxX4);
                s32 innerIdxX2 = outerIdx * 2;
                s32* innerNpcPtr = &npcIndices[j];
                s16* innerHorizAngle = &horizAngles[j];
                s32 innerIdxTimes2 = j * 2;
                s32* innerDist = &distances[j];
                do
                {
                    if (!((u16)g_SysWork.npcs_1A0[*outerNpcPtr].flags_3E & 2))
                    {
                        if ((u16)g_SysWork.npcs_1A0[*innerNpcPtr].flags_3E & 2)
                        {
                            goto no_swap;
                        }
                    }
                    else if (!((u16)g_SysWork.npcs_1A0[*innerNpcPtr].flags_3E & 2))
                    {
                        goto do_swap;
                    }
                    switch (mode)
                    {
                    case 0:
                    case 3:
                    {
                        s16 outerVal = *outerHorizAngle;
                        s16 innerVal = *innerHorizAngle;
                        s16 outerAbs = outerVal;
                        if (outerVal < 0)
                        {
                            outerAbs = -outerAbs;
                        }
                        if (innerVal >= 0)
                        {
                            if (innerVal < outerAbs)
                            {
                                goto do_swap;
                            }
                            goto no_swap;
                        }
                        else
                        {
                            if (-innerVal < outerAbs)
                            {
                                goto do_swap;
                            }
                            goto no_swap;
                        }
                    }
                    case 1:
                    {
                        s32 cmp = *innerHorizAngle < *outerHorizAngle;
                        if (cmp == 0)
                        {
                            goto no_swap;
                        }
                        goto do_swap;
                    }
                    case 2:
                    {
                        s32 cmp = *outerHorizAngle < *innerHorizAngle;
                        if (cmp == 0)
                        {
                            goto no_swap;
                        }
                        goto do_swap;
                    }
                    case 4:
                    {
                        s32 outerDistQ6 = ((*outerDist) >> 6);
                        s32 outerAngleAbs;
                        s32 innerDistQ6;
                        s32 innerAngleAbs;
                        outerAngleAbs = *outerHorizAngle;
                        if (outerAngleAbs < 0)
                        {
                            outerAngleAbs = -outerAngleAbs;
                        }
                        innerDistQ6 = ((*innerDist) >> 6);
                        innerAngleAbs = *innerHorizAngle;
                        if (innerAngleAbs < 0)
                        {
                            innerAngleAbs = -innerAngleAbs;
                        }
                        if (innerDistQ6 * innerDistQ6 * innerAngleAbs < outerDistQ6 * outerDistQ6 * outerAngleAbs)
                        {
                            goto do_swap;
                        }
                        goto no_swap;
                    }
                    case 5:
                        if (*innerDist < *outerDist)
                        {
                            goto do_swap;
                        }
                        goto no_swap;
                    }
                do_swap:
                    if ((u32)(mode - 4) < 2u)
                    {
                        s32 tmpDist = *outerDist;
                        *outerDist = *innerDist;
                        *innerDist = tmpDist;
                    }
                    {
                        s16 tmpAngle = *outerHorizAngle;
                        *outerHorizAngle = *innerHorizAngle;
                        {
                            s16* outerElevPtr = (s16*)((u8*)elevAngles + innerIdxX2);
                            s16* innerElevPtr = (s16*)((u8*)elevAngles + innerIdxTimes2);
                            *innerHorizAngle = tmpAngle;
                            {
                                s16 tmpElev = *outerElevPtr;
                                *outerElevPtr = *innerElevPtr;
                                *innerElevPtr = tmpElev;
                            }
                        }
                        {
                            s32 tmpIdx = *outerNpcPtr;
                            *outerNpcPtr = *innerNpcPtr;
                            *innerNpcPtr = tmpIdx;
                        }
                    }
                no_swap:
                    innerNpcPtr += 1;
                    innerHorizAngle += 1;
                    innerIdxTimes2 += 2;
                    j += 1;
                    innerDist += 1;
                } while (j < candidateCount);
            }
            {
                s32 npcIdx = *outerNpcPtr;
                rayDir.vx = (new_var2[npcIdx].position_18.vx + g_SysWork.npcs_1A0[npcIdx].field_D8.offsetX_0) - combatX;
                rayDir.vy = (g_SysWork.npcs_1A0[npcIdx].position_18.vy + g_SysWork.npcs_1A0[npcIdx].field_C8.field_6) - combatY;
                rayDir.vz = (g_SysWork.npcs_1A0[npcIdx].position_18.vz + g_SysWork.npcs_1A0[npcIdx].field_D8.offsetZ_2) - combatZ;
                if (func_8006DA08(&ray, &rayFrom, &rayDir, &g_SysWork.playerWork_4C.player_0) &&
                    ray.chara_10 == &g_SysWork.npcs_1A0[npcIdx])
                {
                    goto found;
                }
            }
            outerNpcPtr += 1;
            outerIdx += 1;
            outerIdxX4 += 4;
            if (outerIdx >= candidateCount)
            {
                goto check_result;
            }
        } while (1);
    found:
    check_result:
        if (outerIdx < candidateCount)
        {
            *outNpcIdx = npcIndices[outerIdx];
            *outAngle = (u16)elevAngles[outerIdx];
        }
    }
end:;
}
#endif

bool func_8005D50C(s32* targetNpcIdx, q3_12* outAngle0, q3_12* outAngle1, VECTOR3* from, u32 npcIdx, q19_12 angleConstraint) // 0x8005D50C
{
    s_RayTrace trace;
    VECTOR3    unkPos;
    q3_12      angle1;
    q3_12      angle0;
    q3_12      angle2;
    q3_12      angle3;
    q19_12     mag0;
    q19_12     mag1;
    s32        i;

    #define npc g_SysWork.npcs[npcIdx]

    // Check if NPC index is valid.
    if (npcIdx >= ARRAY_SIZE(g_SysWork.npcs))
    {
        return false;
    }

    unkPos.vx = (npc.position.vx + npc.collision.shapeOffsets.box.vx) - from->vx;
    unkPos.vy = (npc.position.vy + npc.collision.box.offsetY) - from->vy;
    unkPos.vz = (npc.position.vz + npc.collision.shapeOffsets.box.vz) - from->vz;

    mag0 = Math_Vector2MagCalc(unkPos.vx, unkPos.vz);
    angle0 = ratan2(unkPos.vx, unkPos.vz);
    angle1 = ratan2(mag0, unkPos.vy);

    *targetNpcIdx = npcIdx;
    *outAngle0 = angle1;
    *outAngle1 = angle0;

    // Run through NPCs.
    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs); i++)
    {
        #define curNpc g_SysWork.npcs[i]

        // Check if NPC is valid.
        if (curNpc.model.charaId == Chara_None ||
            curNpc.health < Q12(0.0f) || i == npcIdx)
        {
            continue;
        }

        unkPos.vx = (curNpc.position.vx + curNpc.collision.shapeOffsets.box.vx) - from->vx;
        unkPos.vy = (curNpc.position.vy + curNpc.collision.box.offsetY) - from->vy;
        unkPos.vz = (curNpc.position.vz + curNpc.collision.shapeOffsets.box.vz) - from->vz;

        angle2 = ratan2(unkPos.vx, unkPos.vz);
        if (angleConstraint < ABS(Math_AngleNormalizeSigned(angle0 - angle2)))
        {
            continue;
        }

        mag1 = Math_Vector2MagCalc(unkPos.vx, unkPos.vz);
        if (mag0 < mag1)
        {
            continue;
        }

        angle3 = ratan2(mag1, unkPos.vy);
        if (angleConstraint < ABS(Math_AngleNormalizeSigned(angle1 - angle3)))
        {
            continue;
        }

        if (Ray_CharaTraceQuery(&trace, from, &unkPos, &g_SysWork.playerWork.player) && trace.character == &g_SysWork.npcs[i])
        {
            *targetNpcIdx  = i;
            *outAngle0  = angle3;
            mag0 = mag1;
            *outAngle1  = angle2;
        }

        #undef curNpc
    }

    return true;

    #undef npc
}
