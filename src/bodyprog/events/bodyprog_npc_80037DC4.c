#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/ranking.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/mem.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

// ========================================
// NPC RELATED - UPDATES
// ========================================

void Savegame_EnemyStateUpdate(s_SubCharacter* chara) // 0x80037DC4
{
    if (g_SavegamePtr->gameDifficulty_260 <= GameDifficulty_Normal || Rng_RandQ12() >= Q12_ANGLE(108.0f))
    {
        g_SavegamePtr->ovlEnemyStates[g_SavegamePtr->mapOverlayId_A4] &= ~(1 << chara->field_40);
    }
}

void Chara_DamagedFlagUpdate(s_SubCharacter* chara) // 0x80037E40
{
    if (chara->damage_B4.amount_C > Q12(0.0f))
    {
        chara->flags_3E |= CharaFlag_Damaged;
    }
    else
    {
        chara->flags_3E &= ~CharaFlag_Damaged;
    }
}

void func_80037E78(s_SubCharacter* chara) // 0x80037E78
{
    s8  idx;
    s32 cond;

    // TODO: Strange `chara->headingAngle_3C` access.
    if (chara->health_B0 <= Q12(0.0f) && (*(s32*)&chara->headingAngle_3C & 0x600000) == 0x200000)
    {
        idx = chara->attackReceived_41;
        if (idx < 39) // TODO: What weapon attack?
        {
            cond = D_800AD4C8[idx].field_10 == 3;
            func_800914C4(cond, func_8009146C(cond) + 1);
        }

        chara->flags_3E |= CharaFlag_Dead;
    }
}

void Game_NpcRoomInitSpawn(bool cond) // 0x80037F24
{
    s_Collision     coll;
    s32             charaId0;
    s32             charaId1;
    s32             npcIdx;
    s32             i;
    s32*            ovlEnemiesStatePtr;
    s_SpawnInfo*    curCharaSpawn;
    s_SubCharacter* chara;
    VECTOR3*        pos;

    npcIdx             = 0;
    curCharaSpawn      = g_MapOverlayHeader.charaSpawns_24C[0];
    ovlEnemiesStatePtr = &g_SavegamePtr->ovlEnemyStates[g_SavegamePtr->mapOverlayId_A4];

    if (cond == false)
    {
        func_80037154();

        if (g_MapOverlayHeader.npcSpawnEvent_48 != NULL)
        {
            g_MapOverlayHeader.npcSpawnEvent_48();
        }
    }

    charaId0 = g_MapOverlayHeader.charaGroupIds_248[0];
    charaId1 = g_MapOverlayHeader.charaGroupIds_248[1];

    for (i = 0; i < 32 && g_VBlanks < 4; i++, curCharaSpawn++)
    {
        if (g_SysWork.npcFlags_2290 == ((1 << g_SysWork.npcId_2280) - 1)) // TODO: Macro for this check?
        {
            break;
        }

        pos = (VECTOR3*)curCharaSpawn;

        if (!(g_SysWork.flags_22A4 & SysFlag2_4) && HAS_FLAG(ovlEnemiesStatePtr, i) && !HAS_FLAG(g_SysWork.field_228C, i) &&
            curCharaSpawn->flags_6 != 0 && g_SavegamePtr->gameDifficulty_260 >= curCharaSpawn->minGameDifficulty_7_0 &&
            func_8008F914(curCharaSpawn->positionX_0, curCharaSpawn->positionZ_8) &&
            !Math_Distance2dCheck(&g_SysWork.playerWork_4C.player_0.position_18, pos, Q12(22.0f)) &&
            (!cond || Math_Distance2dCheck(&g_SysWork.playerWork_4C.player_0.position_18, pos, Q12(20.0f))))
        {
            while (HAS_FLAG(&g_SysWork.npcFlags_2290, npcIdx))
            {
                npcIdx++;
            }

            bzero(&g_SysWork.npcs_1A0[npcIdx], sizeof(s_SubCharacter));

            if (curCharaSpawn->charaId_4 > Chara_None)
            {
                g_SysWork.npcs_1A0[npcIdx].model_0.charaId_0 = curCharaSpawn->charaId_4;
            }
            else
            {
                g_SysWork.npcs_1A0[npcIdx].model_0.charaId_0 = (i < 16) ? charaId0 : charaId1;
            }

            g_SysWork.npcs_1A0[npcIdx].field_40               = i;
            g_SysWork.npcs_1A0[npcIdx].model_0.controlState_2 = ModelState_Uninitialized;
            g_SysWork.npcs_1A0[npcIdx].model_0.stateStep_3    = curCharaSpawn->flags_6;
            g_SysWork.npcs_1A0[npcIdx].position_18.vx         = curCharaSpawn->positionX_0;
            g_SysWork.npcs_1A0[npcIdx].position_18.vz         = curCharaSpawn->positionZ_8;

            Collision_Get(&coll, curCharaSpawn->positionX_0, curCharaSpawn->positionZ_8);

            g_SysWork.npcs_1A0[npcIdx].position_18.vy = coll.groundHeight_0;
            g_SysWork.npcs_1A0[npcIdx].rotation_24.vy = curCharaSpawn->rotationY_5 * 16;

            SET_FLAG(&g_SysWork.npcFlags_2290, npcIdx);
            SET_FLAG(g_SysWork.field_228C, i);

            chara                          = &g_SysWork.npcs_1A0[npcIdx];
            chara->model_0.anim_4.flags_2 |= AnimFlag_Visible;
        }
    }
}

void Game_NpcUpdate(void) // 0x80038354
{
    typedef struct
    {
        s8      bitIdx_0;
        u8      unk_1[3];
        s32     field_4;
        VECTOR3 field_8;
    } s_func_800382EC_0;

    s_func_800382EC_0  field_0[3];
    u32                field_40;
    s32                posZShift6;
    s32                posXShift6;
    s32                temp_t1;
    s32                m;
    u8                 var_a2_2;
    s32                j;
    s32                var_s3;
    s32                k;
    s32                var_t5;
    s32                var_v0_4;
    s32                var_v1_3;
    s32                temp_s0_2;
    s32                temp_s0_4;
    s8                 temp_s1;
    s32                temp_v0_4;
    s32                var_v0_5;
    u32                temp_t3;
    u8                 temp_a2;
    u32                new_var;
    s32                l;
    s32                animDataInfoIdx;
    s32                temp2;
    GsCOORDINATE2*     coord;
    s_SubCharacter*    npc;
    s_func_800382EC_0* temp_s0_3;

    // GCC extension funcs.
    s32 func_800382B0(s32 arg0)
    {
        s32 i;

        for (i = 0; i < 2; i++)
        {
            if (arg0 == field_0[i].bitIdx_0)
            {
                return i;
            }
        }

        return NO_VALUE;
    }

    s32 func_800382EC()
    {
        s32 i;

        for (i = 0; i < 2; i++)
        {
            if (field_0[i].bitIdx_0 == NO_VALUE)
            {
                break;
            }

            if ((field_40 & (1 << field_0[i].bitIdx_0)) == 0)
            {
                field_40 |= (1 << field_0[i].bitIdx_0);
                return i;
            }
        }

        return NO_VALUE;
    }

    posXShift6 = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vx);
    posZShift6 = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vz);

    Demo_DemoRandSeedBackup();
    Demo_DemoRandSeedRestore();

    for (j = 0; j < ARRAY_SIZE(field_0); j++)
    {
        field_0[j].bitIdx_0   = NO_VALUE;
        field_0[j].field_4    = Q12(0.25f);
        field_0[j].field_8.vy = 0;
    }

    for (k = 0, npc = g_SysWork.npcs_1A0; k < ARRAY_SIZE(g_SysWork.npcs_1A0); k++, npc++)
    {
        if (npc->model_0.charaId_0 != Chara_None && npc->model_0.charaId_0 != Chara_Padlock)
        {
            if (npc->model_0.charaId_0 <= Chara_MonsterCybil)
            {
                temp_t3 = Q12_SQUARE_PRECISE(Q12_TO_Q6(npc->position_18.vx) - posXShift6) +
                          Q12_SQUARE_PRECISE(Q12_TO_Q6(npc->position_18.vz) - posZShift6);
                var_t5 = 0;

                if (g_MapOverlayHeader.mapInfo_0->flags_6 & MapFlag_Interior)
                {
                    var_t5 = (g_MapOverlayHeader.mapInfo_0->flags_6 & (MapFlag_OneActiveChunk | MapFlag_TwoActiveChunks)) > 0;
                }

                for (j = 0; j < 3; j++)
                {
                    if (npc->health_B0 <= Q12(0.0f) || npc->flags_3E & CharaFlag_Unk9 || temp_t3 >= field_0[j].field_4)
                    {
                        continue;
                    }

                    if (var_t5 != 0)
                    {
                        s32 playerCell = (g_SysWork.playerWork_4C.player_0.position_18.vx + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                        s32 npcCell    = (npc->position_18.vx                        + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                        if (npcCell != playerCell)
                        {
                            continue;
                        }

                        // TODO: Unique vars for these.
                        playerCell = (g_SysWork.playerWork_4C.player_0.position_18.vz + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                        npcCell    = (npc->position_18.vz                        + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                        if (npcCell != playerCell)
                        {
                            continue;
                        }
                    }

                    for (m = 2; j < m; m--)
                    {
                        field_0[m].bitIdx_0   = field_0[m - 1].bitIdx_0;
                        field_0[m].field_4    = field_0[m - 1].field_4;
                        field_0[m].field_8.vx = field_0[m - 1].field_8.vx;
                        field_0[m].field_8.vz = field_0[m - 1].field_8.vz;
                    }

                    temp_t1 = (u32)npc - (u32)g_SysWork.npcs_1A0;
                    temp2   = ((((temp_t1 * 0x7E8) - (temp_t1 * 0xFD)) * 4) + temp_t1) * -0x3FFFF;

                    field_0[j].bitIdx_0   = temp2 >> 3;
                    field_0[j].field_4    = temp_t3;
                    field_0[j].field_8.vx = npc->position_18.vx;
                    field_0[j].field_8.vz = npc->position_18.vz;
                    break;
                }

                new_var = temp_t3;

                if (new_var > ((var_t5 == 0 && npc->health_B0 < Q12(0.0f)) ? SQUARE(24) : SQUARE(40)))
                {
                    npc->model_0.charaId_0 = Chara_None;
                    SysWork_NpcFlagClear(k);
                    CLEAR_FLAG(g_SysWork.field_228C, npc->field_40);
                    continue;
                }

                if ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 0x2 && temp_t3 > SQUARE(15)) ||
                    (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 0x2) &&
                     Camera_Distance2dGet(&npc->position_18) > SQUARE(15)))
                {
                    npc->model_0.anim_4.flags_2 &= ~AnimFlag_Visible;
                }
                else
                {

                    npc->model_0.anim_4.flags_2 |= AnimFlag_Visible;
                }
            }

            npc->model_0.anim_4.flags_2 |= AnimFlag_Unlocked;

            animDataInfoIdx = g_CharaAnimInfoIdxs[npc->model_0.charaId_0];
            coord           = g_CharaTypeAnimInfo[animDataInfoIdx].npcCoords_14;

            Chara_Flag8Clear(npc);
            Chara_DamagedFlagUpdate(npc);
            func_8003BD48(npc);

            g_MapOverlayHeader.charaUpdateFuncs_194[npc->model_0.charaId_0](npc, g_CharaTypeAnimInfo[animDataInfoIdx].animFile1_8, coord);

            func_8003BE28();
            func_80037E78(npc);
            func_8008A3AC(npc);

            if (npc->model_0.anim_4.flags_2 & AnimFlag_Visible)
            {
                func_8003DA9C(npc->model_0.charaId_0, coord, 1, npc->timer_C6, (s8)npc->model_0.paletteIdx_1);
            }
        }
    }

    for (k = 2; k >= 0; k--)
    {
        if (field_0[k].bitIdx_0 != NO_VALUE)
        {
            break;
        }
    }

    g_RadioPitchState = k + 1;

    if (!(g_SavegamePtr->itemToggleFlags_AC & ItemToggleFlag_RadioOn))
    {
        return;
    }

    field_40 = 0;

    for (l = 0; l < ARRAY_SIZE(D_800BCDA8); l++)
    {
        temp_s0_2 = D_800BCDA8[l].field_1;
        if (temp_s0_2 == NO_VALUE)
        {
            var_v0_4 = NO_VALUE;
        }
        else
        {
            var_v0_4 = func_800382B0(temp_s0_2);
        }

        if (var_v0_4 >= 0)
        {
            D_800BCDA8[l].field_2 = var_v0_4;
            field_40             |= 1 << temp_s0_2;
        }
        else
        {
            D_800BCDA8[l].field_1 = NO_VALUE;
        }
    }

    for (l = 0; l < ARRAY_SIZE(D_800BCDA8); l++)
    {
        temp_s1 = D_800BCDA8[l].field_1;
        if (temp_s1 == NO_VALUE)
        {
            temp_v0_4 = func_800382EC();
            if (temp_v0_4 != temp_s1)
            {
                var_v0_5 = field_0[temp_v0_4].bitIdx_0;
            }
            else
            {
                var_v0_5 = NO_VALUE;
            }

            D_800BCDA8[l].field_2 = temp_v0_4;
            D_800BCDA8[l].field_1 = var_v0_5;
        }
    }

    for (l = 0; l < ARRAY_SIZE(D_800BCDA8); l++)
    {
        if (D_800BCDA8[l].field_0 == NO_VALUE)
        {
            if (D_800BCDA8[l].field_1 >= 0)
            {
                SD_Call((u16)(Sfx_RadioInterferenceLoop + l));
            }
        }
        else
        {
            var_s3 = 0;
            if (!(g_MapOverlayHeader.mapInfo_0->flags_6 & MapFlag_Interior) ||
                !(g_MapOverlayHeader.mapInfo_0->flags_6 & (MapFlag_OneActiveChunk | MapFlag_TwoActiveChunks)))
            {
                var_s3 = 1;
            }

            if (D_800BCDA8[l].field_1 >= 0)
            {
                temp_s0_3 = &field_0[D_800BCDA8[l].field_2];
                temp_s0_4 = Sound_StereoBalanceGet(&temp_s0_3->field_8);

                var_v1_3 = SquareRoot12(temp_s0_3->field_4 << Q12_SHIFT) >> 8;
                if (var_s3 != 0)
                {
                    var_v1_3 >>= 1;
                }

                var_a2_2 = CLAMP(var_v1_3, 0, 0xFF);

                Sd_SfxAttributesUpdate(Sfx_RadioInterferenceLoop + l, temp_s0_4, var_a2_2, 0);
            }
            else
            {
                Sd_SfxStop(Sfx_RadioInterferenceLoop + l);
            }
        }

        D_800BCDA8[l].field_0 = D_800BCDA8[l].field_1;
    }
}

bool Math_Distance2dCheck(const VECTOR3* from, const VECTOR3* to, q19_12 radius) // 0x80038A6C
{
    q19_12 deltaX;
    q19_12 deltaZ;
    q19_12 radiusSqr;
    q19_12 sum;

    // Check rough radius intersection on X axis.
    deltaX = from->vx - to->vx;
    if (radius < deltaX)
    {
        return true;
    }
    if (radius < -deltaX)
    {
        return true;
    }

    // Check rough radius intersection on Z axis.
    deltaZ = from->vz - to->vz;
    if (radius < deltaZ)
    {
        return true;
    }
    if (radius < -deltaZ)
    {
        return true;
    }

    // Check distance.
    sum       = Q12_MULT_PRECISE(deltaX, deltaX) + Q12_MULT_PRECISE(deltaZ, deltaZ);
    radiusSqr = Q12_MULT_PRECISE(radius, radius);
    return sum > radiusSqr;
}

s32 Camera_Distance2dGet(const VECTOR3* pos) // 0x80038B44
{
    VECTOR3 camPos; // Q19.12
    q25_6   deltaX;
    q25_6   deltaZ;

    vwGetViewPosition(&camPos);
    deltaX = Q12_TO_Q6(camPos.vx - pos->vx);
    deltaZ = Q12_TO_Q6(camPos.vz - pos->vz);
    return Q12_MULT_PRECISE(deltaX, deltaX) + Q12_MULT_PRECISE(deltaZ, deltaZ);
}
