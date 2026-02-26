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

// ========================================
// COMBAT 1
// ========================================

s32 Chara_NpcIdxGet(s_SubCharacter* chara) // 0x8005C7D0
{
    s32             i;
    s_SubCharacter* curNpc;
    s_SubCharacter* player;

    i = 0;

    if (chara == &g_SysWork.playerWork_4C.player_0)
    {
        return ARRAY_SIZE(g_SysWork.npcs_1A0);
    }

    curNpc = &g_SysWork.npcs_1A0[0];
    player = chara;
    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++, curNpc++)
    {
        if (player == curNpc)
        {
            return i;
        }
    }

    return NO_VALUE;
}

void func_8005C814(s_SubCharacter_D8* arg0, s_SubCharacter* chara) // 0x8005C814
{
    q3_12 sinRotY;
    q3_12 cosRotY;
    q3_12 offsetX0;
    q3_12 offsetX1;
    q3_12 offsetZ0;
    q3_12 offsetZ1;

    offsetX0 = arg0->offsetX_0;
    offsetZ0 = arg0->offsetZ_2;
    offsetX1 = arg0->offsetX_4;
    offsetZ1 = arg0->offsetZ_6;

    cosRotY = Math_Cos(chara->rotation_24.vy);
    sinRotY = Math_Sin(chara->rotation_24.vy);

    chara->field_D8.offsetX_0 = FP_FROM(( offsetX0 * cosRotY) + (offsetZ0 * sinRotY), Q12_SHIFT);
    chara->field_D8.offsetZ_2 = FP_FROM((-offsetX0 * sinRotY) + (offsetZ0 * cosRotY), Q12_SHIFT);
    chara->field_D8.offsetX_4 = FP_FROM(( offsetX1 * cosRotY) + (offsetZ1 * sinRotY), Q12_SHIFT);
    chara->field_D8.offsetZ_6 = FP_FROM((-offsetX1 * sinRotY) + (offsetZ1 * cosRotY), Q12_SHIFT);
}

s32 func_8005C944(s_SubCharacter* chara, s_800C4590* arg1) // 0x8005C944
{
    s_800C4590 sp10;
    VECTOR3    offset;
    q3_12      headingAngle;
    s32        temp_s0;
    s32        temp_s0_2;
    s32        temp_s2;
    s32        temp_s3;
    s32        temp_v0;
    q19_12     sinHeadingAngle;
    s32        ret;

    headingAngle = chara->headingAngle_3C;
    temp_s0 = Q12_MULT_PRECISE(g_DeltaTime, chara->moveSpeed_38);
    temp_s2 = OVERFLOW_GUARD(temp_s0);
    temp_s3 = temp_s2 >> 1;

    sinHeadingAngle = Math_Sin(headingAngle);
    temp_s0_2       = temp_s0 >> temp_s3;
    temp_v0         = sinHeadingAngle >> temp_s3;

    offset.vx = Q12_MULT_PRECISE(temp_s0_2, temp_v0) << temp_s2;
    offset.vz = Q12_MULT_PRECISE(temp_s0_2, Math_Cos(headingAngle) >> temp_s3) << temp_s2;
    offset.vy = Q12_MULT_PRECISE(g_DeltaTime, chara->fallSpeed_34);

    ret = func_80069B24(&sp10, &offset, chara);

    chara->position_18.vx += sp10.offset_0.vx;
    chara->position_18.vy += sp10.offset_0.vy;
    chara->position_18.vz += sp10.offset_0.vz;

    if (chara->position_18.vy > sp10.field_C)
    {
        chara->position_18.vy = sp10.field_C;
        chara->fallSpeed_34   = Q12(0.0f);
    }

    if (arg1 != NULL)
    {
        *arg1 = sp10;
    }

    return ret;
}

s32 func_8005CB20(s_SubCharacter* chara, s_800C4590* arg1, q3_12 offsetX, q3_12 offsetZ) // 0x8005CB20
{
    s_800C4590 sp10;
    VECTOR3    offset; // Q19.12
    q19_12     headingAngle;
    s32        temp_s0;
    s32        temp_s0_2;
    s32        temp_s2;
    s32        temp_s3;
    s32        temp_v0_2;
    s32        temp_v0_4;
    q19_12     sinHeadingAngle;
    s32        ret;

    headingAngle = chara->headingAngle_3C;
    temp_s0 = Q12_MULT_PRECISE(g_DeltaTime, chara->moveSpeed_38);
    temp_s2 = OVERFLOW_GUARD(temp_s0);
    temp_s3 = temp_s2 >> 1;

    sinHeadingAngle = Math_Sin(headingAngle);
    temp_s0_2 = temp_s0 >> temp_s3;
    temp_v0_2 = sinHeadingAngle >> temp_s3;
    offset.vx = (s32)Q12_MULT_PRECISE(temp_s0_2, temp_v0_2) << temp_s2;

    temp_v0_4 = Math_Cos(headingAngle) >> temp_s3;
    offset.vz = (s32)Q12_MULT_PRECISE(temp_s0_2, temp_v0_4) << temp_s2;

    sinHeadingAngle = chara->fallSpeed_34;
    offset.vx += offsetX;
    offset.vy  = Q12_MULT_PRECISE(g_DeltaTime, sinHeadingAngle);
    offset.vz += offsetZ;

    ret = func_80069B24(&sp10, &offset, chara);

    chara->position_18.vx += sp10.offset_0.vx;
    chara->position_18.vy += sp10.offset_0.vy;
    chara->position_18.vz += sp10.offset_0.vz;

    if (chara->position_18.vy > sp10.field_C)
    {
        chara->position_18.vy = sp10.field_C;
        chara->fallSpeed_34   = Q12(0.0f);
    }

    if (arg1 != NULL)
    {
        *arg1 = sp10;
    }

    return ret;
}

// Important for combat.
INCLUDE_ASM("bodyprog/nonmatchings/bodyprog_combat_8005BF38", func_8005CD38); // 0x8005CD38

bool func_8005D50C(s32* targetNpcIdx, q3_12* outAngle0, q3_12* outAngle1, VECTOR3* unkOffset, u32 npcIdx, q19_12 angleConstraint) // 0x8005D50C
{
    s_RayData ray;
    VECTOR3   unkPos;
    q3_12     angle1;
    q3_12     angle0;
    q3_12     angle2;
    q3_12     angle3;
    q19_12    mag0;
    q19_12    mag1;
    s32       i;

    #define npc g_SysWork.npcs_1A0[npcIdx]

    // Check if NPC index is valid.
    if (npcIdx >= ARRAY_SIZE(g_SysWork.npcs_1A0))
    {
        return false;
    }

    unkPos.vx = (npc.position_18.vx + npc.field_D8.offsetX_0) - unkOffset->vx;
    unkPos.vy = (npc.position_18.vy + npc.field_C8.field_6) - unkOffset->vy;
    unkPos.vz = (npc.position_18.vz + npc.field_D8.offsetZ_2) - unkOffset->vz;

    mag0 = Math_Vector2MagCalc(unkPos.vx, unkPos.vz);
    angle0 = ratan2(unkPos.vx, unkPos.vz);
    angle1 = ratan2(mag0, unkPos.vy);

    *targetNpcIdx = npcIdx;
    *outAngle0 = angle1;
    *outAngle1 = angle0;

    // Run through NPCs.
    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
    {
        #define curNpc g_SysWork.npcs_1A0[i]

        // Check if NPC is valid.
        if (curNpc.model_0.charaId_0 == Chara_None ||
            curNpc.health_B0 < Q12(0.0f) || i == npcIdx)
        {
            continue;
        }

        unkPos.vx = (curNpc.position_18.vx + curNpc.field_D8.offsetX_0) - unkOffset->vx;
        unkPos.vy = (curNpc.position_18.vy + curNpc.field_C8.field_6) - unkOffset->vy;
        unkPos.vz = (curNpc.position_18.vz + curNpc.field_D8.offsetZ_2) - unkOffset->vz;

        angle2 = ratan2(unkPos.vx, unkPos.vz);
        if (angleConstraint < ABS(func_8005BF38(angle0 - angle2)))
        {
            continue;
        }

        mag1 = Math_Vector2MagCalc(unkPos.vx, unkPos.vz);
        if (mag0 < mag1)
        {
            continue;
        }

        angle3 = ratan2(mag1, unkPos.vy);
        if (angleConstraint < ABS(func_8005BF38(angle1 - angle3)))
        {
            continue;
        }

        if (func_8006DA08(&ray, unkOffset, &unkPos, &g_SysWork.playerWork_4C.player_0) && ray.chara_10 == &g_SysWork.npcs_1A0[i])
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
