#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "bodyprog/events/bodyprog_data_800A99B4.h"
#include "bodyprog/events/npc_main.h"
#include "bodyprog/events/radio.h"
#include "bodyprog/game_boot/fs_chara_anim.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/sound/sound_system.h"
#include "main/fsqueue.h"

void Savegame_EnemyStateUpdate(s_SubCharacter* chara) // 0x80037DC4
{
    if (g_SavegamePtr->gameDifficulty <= GameDifficulty_Normal || Rng_RandQ12() >= Q12_ANGLE(108.0f))
    {
        g_SavegamePtr->ovlEnemyStates[g_SavegamePtr->mapIdx] &= ~(1 << chara->field_40);
    }
}

void Chara_DamagedFlagUpdate(s_SubCharacter* chara) // 0x80037E40
{
    if (chara->damage.amount > Q12(0.0f))
    {
        chara->flags |= CharaFlag_Damaged;
    }
    else
    {
        chara->flags &= ~CharaFlag_Damaged;
    }
}

void func_80037E78(s_SubCharacter* chara) // 0x80037E78
{
    s8  idx;
    s32 cond;

    // TODO: Strange `chara->headingAngle` access.
    if (chara->health <= Q12(0.0f) && (*(s32*)&chara->headingAngle & 0x600000) == 0x200000)
    {
        idx = chara->attackReceived;
        if (idx < 39) // TODO: What weapon attack?
        {
            cond = D_800AD4C8[idx].field_10 == 3;
            func_800914C4(cond, func_8009146C(cond) + 1);
        }

        chara->flags |= CharaFlag_Dead;
    }
}

void Game_NpcRoomInitSpawn(bool cond) // 0x80037F24
{
    s_Collision     coll;
    s32             groupCharaId0;
    s32             groupCharaId1;
    s32             npcIdx;
    s32             i;
    s32*            ovlEnemiesStatePtr;
    s_SpawnInfo*    curCharaSpawn;
    s_SubCharacter* chara;
    VECTOR3*        pos;

    npcIdx             = 0;
    curCharaSpawn      = g_MapOverlayHeader.charaSpawnInfos[0];
    ovlEnemiesStatePtr = &g_SavegamePtr->ovlEnemyStates[g_SavegamePtr->mapIdx];

    if (cond == false)
    {
        func_80037154();

        if (g_MapOverlayHeader.npcSpawnEvent != NULL)
        {
            g_MapOverlayHeader.npcSpawnEvent();
        }
    }

    groupCharaId0 = g_MapOverlayHeader.charaGroupIds[0];
    groupCharaId1 = g_MapOverlayHeader.charaGroupIds[1];

    for (i = 0; i < 32 && g_VBlanks < 4; i++, curCharaSpawn++)
    {
        if (g_SysWork.npcFlags == ((1 << g_SysWork.npcFlagsId) - 1)) // TODO: Macro for this check?
        {
            break;
        }

        pos = (VECTOR3*)curCharaSpawn;

        if (!(g_SysWork.sysFlags & SysFlag_NoEnemySpawn) &&
            HAS_FLAG(ovlEnemiesStatePtr, i) && !HAS_FLAG(g_SysWork.field_228C, i) &&
            curCharaSpawn->flags != SpawnFlag_None &&
            g_SavegamePtr->gameDifficulty >= curCharaSpawn->gameDifficultyMin &&
            func_8008F914(curCharaSpawn->positionX, curCharaSpawn->positionZ) &&
            !Math_Distance2dCheck(&g_SysWork.playerWork.player.position, pos, Q12(22.0f)) &&
            (!cond || Math_Distance2dCheck(&g_SysWork.playerWork.player.position, pos, Q12(20.0f))))
        {
            while (HAS_FLAG(&g_SysWork.npcFlags, npcIdx))
            {
                npcIdx++;
            }

            bzero(&g_SysWork.npcs[npcIdx], sizeof(s_SubCharacter));

            if (curCharaSpawn->charaId > Chara_None)
            {
                g_SysWork.npcs[npcIdx].model.charaId = curCharaSpawn->charaId;
            }
            else
            {
                g_SysWork.npcs[npcIdx].model.charaId = (i < 16) ? groupCharaId0 : groupCharaId1;
            }

            g_SysWork.npcs[npcIdx].field_40           = i;
            g_SysWork.npcs[npcIdx].model.controlState = 0;
            g_SysWork.npcs[npcIdx].model.stateStep    = curCharaSpawn->flags;
            g_SysWork.npcs[npcIdx].position.vx        = curCharaSpawn->positionX;
            g_SysWork.npcs[npcIdx].position.vz        = curCharaSpawn->positionZ;

            Collision_Get(&coll, curCharaSpawn->positionX, curCharaSpawn->positionZ);

            g_SysWork.npcs[npcIdx].position.vy = coll.groundHeight;
            g_SysWork.npcs[npcIdx].rotation.vy = Q8_TO_Q12(curCharaSpawn->rotationY);

            SET_FLAG(&g_SysWork.npcFlags, npcIdx);
            SET_FLAG(g_SysWork.field_228C, i);

            chara                    = &g_SysWork.npcs[npcIdx];
            chara->model.anim.flags |= AnimFlag_Visible;
        }
    }
}

void Game_NpcUpdate(void) // 0x80038354
{
    /** @brief Close NPC info for radio interference. */
    typedef struct _CloseNpcInfo
    {
        /* 0x0 */ s8      bitIdx;
                  // 3 bytes of padding.
        /* 0x4 */ q19_12  distanceToNpc;
        /* 0x8 */ VECTOR3 position; /** Q19.12 */
    } s_CloseNpcInfo;

    s_CloseNpcInfo  closestNpcInfos[3];
    u32             idxBits;
    s32             posZShift6;
    s32             posXShift6;
    s32             temp_t1;
    s32             m;
    u8              vol;
    s32             j;
    s32             var_s3;
    s32             k;
    bool            isLowVisInterior;
    s32             closeNpcInfoIdx0;
    s32             var_v1_3;
    s32             closeNpcInfoIdx1;
    s32             balance;
    s8              temp_s1;
    s32             closeNpcInfoIdx;
    s32             bitIdx;
    q20_12          curDistToNpc;
    u8              temp_a2;
    q20_12          distToNpcCpy;
    s32             l;
    s32             animDataIdx;
    s32             temp2;
    GsCOORDINATE2*  boneCoords;
    s_SubCharacter* curNpc;
    s_CloseNpcInfo* closeNpcInfo;

    s32 func_800382B0(s32 bitIdx)
    {
        s32 i;

        for (i = 0; i < (ARRAY_SIZE(closestNpcInfos) - 1); i++)
        {
            if (bitIdx == closestNpcInfos[i].bitIdx)
            {
                return i;
            }
        }

        return NO_VALUE;
    }

    // Gets close NPC info index.
    s32 func_800382EC()
    {
        s32 i;

        for (i = 0; i < (ARRAY_SIZE(closestNpcInfos) - 1); i++)
        {
            if (closestNpcInfos[i].bitIdx == NO_VALUE)
            {
                break;
            }

            if ((idxBits & (1 << closestNpcInfos[i].bitIdx)) == 0)
            {
                idxBits |= 1 << closestNpcInfos[i].bitIdx;
                return i;
            }
        }

        return NO_VALUE;
    }

    posXShift6 = Q12_TO_Q6(g_SysWork.playerWork.player.position.vx);
    posZShift6 = Q12_TO_Q6(g_SysWork.playerWork.player.position.vz);

    Demo_DemoRandSeedBackup();
    Demo_DemoRandSeedRestore();

    for (j = 0; j < ARRAY_SIZE(closestNpcInfos); j++)
    {
        closestNpcInfos[j].bitIdx        = NO_VALUE;
        closestNpcInfos[j].distanceToNpc = Q12(0.25f);
        closestNpcInfos[j].position.vy   = Q12(0.0f);
    }

    // Run through NPCs.
    for (k = 0, curNpc = g_SysWork.npcs;
         k < ARRAY_SIZE(g_SysWork.npcs);
         k++, curNpc++)
    {
        // Ignore invalid or special NPC.
        if (curNpc->model.charaId == Chara_None ||
            curNpc->model.charaId == Chara_Padlock)
        {
            continue;
        }

        // Only process enemy NPC for radio interference.
        if (curNpc->model.charaId <= Chara_MonsterCybil)
        {
            // Compute distance from player to NPC.
            curDistToNpc = Q12_SQUARE_PRECISE(Q12_TO_Q6(curNpc->position.vx) - posXShift6) +
                           Q12_SQUARE_PRECISE(Q12_TO_Q6(curNpc->position.vz) - posZShift6);

            // Check if map is low-visibility interior.
            isLowVisInterior = false;
            if (g_MapOverlayHeader.mapInfo->flags & MapFlag_Interior)
            {
                isLowVisInterior = (g_MapOverlayHeader.mapInfo->flags & (MapFlag_OneActiveChunk |
                                                                         MapFlag_TwoActiveChunks)) > 0;
            }

            // Run through ???
            for (j = 0; j < 3; j++)
            {
                // Check if NPC is detectable by radio.
                if (curNpc->health <= Q12(0.0f)             ||
                    curNpc->flags & CharaFlag_NoRadioStatic ||
                    curDistToNpc >= closestNpcInfos[j].distanceToNpc)
                {
                    continue;
                }

                // Check if player and NPC occupy the same 4x4 chunk region in low-visibility interior map.
                if (isLowVisInterior)
                {
                    // Check X axis.
                    s32 playerCell = (g_SysWork.playerWork.player.position.vx + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                    s32 npcCell    = (curNpc->position.vx                        + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                    if (npcCell != playerCell)
                    {
                        continue;
                    }

                    // Check Z axis.
                    playerCell = (g_SysWork.playerWork.player.position.vz + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                    npcCell    = (curNpc->position.vz                        + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                    if (npcCell != playerCell)
                    {
                        continue;
                    }
                }

                for (m = ARRAY_SIZE(closestNpcInfos) - 1; j < m; m--)
                {
                    closestNpcInfos[m].bitIdx        = closestNpcInfos[m - 1].bitIdx;
                    closestNpcInfos[m].distanceToNpc = closestNpcInfos[m - 1].distanceToNpc;
                    closestNpcInfos[m].position.vx   = closestNpcInfos[m - 1].position.vx;
                    closestNpcInfos[m].position.vz   = closestNpcInfos[m - 1].position.vz;
                }

                // TODO: Demangle this pointer math.
                temp_t1 = (u32)curNpc - (u32)g_SysWork.npcs;
                temp2   = ((((temp_t1 * 0x7E8) - (temp_t1 * 0xFD)) * 4) + temp_t1) * -0x3FFFF;

                closestNpcInfos[j].bitIdx        = temp2 >> 3;
                closestNpcInfos[j].distanceToNpc = curDistToNpc;
                closestNpcInfos[j].position.vx   = curNpc->position.vx;
                closestNpcInfos[j].position.vz   = curNpc->position.vz;
                break;
            }

            // TODO: Approximage Q12 values don't seem right.

            // Unload distant NPC to avoid drawing.
            distToNpcCpy = curDistToNpc;
            if (distToNpcCpy > ((!isLowVisInterior && curNpc->health < Q12(0.0f)) ? SQUARE(24) : // Approx. `Q12(0.15f)`.
                                                                                    SQUARE(40))) // Approx. `Q12(0.4f)`.
            {
                curNpc->model.charaId = Chara_None;

                SysWork_NpcFlagClear(k);
                CLEAR_FLAG(g_SysWork.field_228C, curNpc->field_40);
                continue;
            }

            // Set NPC visibility.
            if ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 0x2 && curDistToNpc > SQUARE(15)) || // Approx. `Q12(0.055f)`.
                (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & 0x2) &&
                    Camera_Distance2dGet(&curNpc->position) > SQUARE(15))) // Approx. `Q12(0.055f)`.
            {
                curNpc->model.anim.flags &= ~AnimFlag_Visible;
            }
            else
            {

                curNpc->model.anim.flags |= AnimFlag_Visible;
            }
        }

        curNpc->model.anim.flags |= AnimFlag_Unlocked;

        animDataIdx = g_CharaAnimDataIdxs[curNpc->model.charaId];
        boneCoords  = g_CharaModelAnimsData[animDataIdx].boneCoords;

        Chara_Flag8Clear(curNpc);
        Chara_DamagedFlagUpdate(curNpc);
        func_8003BD48(curNpc);

        g_MapOverlayHeader.charaUpdateFuncs[curNpc->model.charaId](curNpc, g_CharaModelAnimsData[animDataIdx].activeAnmHdr, boneCoords);

        func_8003BE28();
        func_80037E78(curNpc);
        func_8008A3AC(curNpc);

        if (curNpc->model.anim.flags & AnimFlag_Visible)
        {
            func_8003DA9C(curNpc->model.charaId, boneCoords, 1, curNpc->timer_C6, (s8)curNpc->model.paletteIdx);
        }
    }

    for (k = 2; k >= 0; k--)
    {
        if (closestNpcInfos[k].bitIdx != NO_VALUE)
        {
            break;
        }
    }

    g_RadioPitchState = k + 1;

    if (!(g_SavegamePtr->itemToggleFlags & ItemToggleFlag_RadioOn))
    {
        return;
    }

    idxBits = 0;

    for (l = 0; l < ARRAY_SIZE(g_RadioNpcInfos); l++)
    {
        closeNpcInfoIdx1 = g_RadioNpcInfos[l].idx;
        if (closeNpcInfoIdx1 == NO_VALUE)
        {
            closeNpcInfoIdx0 = NO_VALUE;
        }
        else
        {
            closeNpcInfoIdx0 = func_800382B0(closeNpcInfoIdx1);
        }

        if (closeNpcInfoIdx0 >= 0)
        {
            g_RadioNpcInfos[l].closeNpcInfoIdx = closeNpcInfoIdx0;
            idxBits                           |= 1 << closeNpcInfoIdx1;
        }
        else
        {
            g_RadioNpcInfos[l].idx = NO_VALUE;
        }
    }

    for (l = 0; l < ARRAY_SIZE(g_RadioNpcInfos); l++)
    {
        temp_s1 = g_RadioNpcInfos[l].idx;
        if (temp_s1 == NO_VALUE)
        {
            closeNpcInfoIdx = func_800382EC();
            if (closeNpcInfoIdx != temp_s1)
            {
                bitIdx = closestNpcInfos[closeNpcInfoIdx].bitIdx;
            }
            else
            {
                bitIdx = NO_VALUE;
            }

            g_RadioNpcInfos[l].closeNpcInfoIdx = closeNpcInfoIdx;
            g_RadioNpcInfos[l].idx = bitIdx;
        }
    }

    for (l = 0; l < ARRAY_SIZE(g_RadioNpcInfos); l++)
    {
        if (g_RadioNpcInfos[l].prevIdx == NO_VALUE)
        {
            if (g_RadioNpcInfos[l].idx >= 0)
            {
                SD_Call((u16)(Sfx_RadioInterferenceLoop + l));
            }
        }
        else
        {
            var_s3 = 0;
            if (!(g_MapOverlayHeader.mapInfo->flags & MapFlag_Interior) ||
                !(g_MapOverlayHeader.mapInfo->flags & (MapFlag_OneActiveChunk | MapFlag_TwoActiveChunks)))
            {
                var_s3 = 1;
            }

            if (g_RadioNpcInfos[l].idx >= 0)
            {
                closeNpcInfo = &closestNpcInfos[g_RadioNpcInfos[l].closeNpcInfoIdx];
                balance      = Vc_StereoBalanceGet(&closeNpcInfo->position);

                var_v1_3 = SquareRoot12(closeNpcInfo->distanceToNpc << Q12_SHIFT) >> 8;
                if (var_s3 != 0)
                {
                    var_v1_3 >>= 1;
                }

                vol = CLAMP(var_v1_3, 0, 0xFF);
                Sd_SfxAttributesUpdate(Sfx_RadioInterferenceLoop + l, balance, vol, 0);
            }
            else
            {
                Sd_SfxStop(Sfx_RadioInterferenceLoop + l);
            }
        }

        g_RadioNpcInfos[l].prevIdx = g_RadioNpcInfos[l].idx;
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

/** @brief Computes the squared 2D distance on the XZ plane from the reference position to the camera.
 *
 * @param pos Reference position (Q19.12).
 * @return 2D distance to the camera. TODO: Does it stay in Q25.6?
 */
static s32 Camera_Distance2dGet(const VECTOR3* pos) // 0x80038B44
{
    VECTOR3 camPos; // Q19.12
    q25_6   deltaX;
    q25_6   deltaZ;

    vwGetViewPosition(&camPos);
    deltaX = Q12_TO_Q6(camPos.vx - pos->vx);
    deltaZ = Q12_TO_Q6(camPos.vz - pos->vz);
    return Q12_MULT_PRECISE(deltaX, deltaX) + Q12_MULT_PRECISE(deltaZ, deltaZ);
}
