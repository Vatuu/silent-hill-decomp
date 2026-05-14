#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/game_boot/fs_chara_anim.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/sound/sound_system.h"
#include "main/fsqueue.h"

bool Chara_Load(s32 modelIdx, s8 charaId, GsCOORDINATE2* coords, s8 forceFree, s_LmHeader* lmHdr, s_FsImageDesc* tex) // 0x80088C7C
{
    Fs_CharaAnimDataAlloc(modelIdx + 1, charaId, NULL, coords);
    WorldGfx_CharaLmBufferAssign(forceFree);
    WorldGfx_CharaLoad(charaId, modelIdx, lmHdr, tex);
    return true;
}

bool Chara_ProcessLoads(void) // 0x80088D0C
{
    Fs_QueueWaitForEmpty();
    WorldGfx_CharaModelProcessAllLoads();
    return true;
}

void Chara_BonesInit(s32 idx) // 0x80088D34
{
    idx++;
    Anim_BoneInit(g_CharaTypeAnimInfo[idx].animFile1_8, g_CharaTypeAnimInfo[idx].npcBoneCoords);
}

s32 Chara_Spawn(e_CharaId charaId, s32 spawnFlags, q19_12 posX, q19_12 posZ, q3_12 rotY, u32 stateStep) // 0x80088D78
{
    s_Collision     coll;
    s32             i;
    s32             npcFlagsId;
    s32             arg1_1;
    s_SubCharacter* chara;

    if (charaId <= Chara_MonsterCybil && spawnFlags < 64)
    {
        arg1_1 = 0x1F;
        arg1_1 = spawnFlags & arg1_1;
    }
    else
    {
        arg1_1 = 0;
    }

    if (charaId <= Chara_MonsterCybil)
    {
        if (HAS_FLAG(g_SysWork.field_228C, arg1_1))
        {
            for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs); i++)
            {
                if (g_SysWork.npcs[i].field_40 == arg1_1)
                {
                    return i;
                }
            }

            return ARRAY_SIZE(g_SysWork.npcs);
        }

        npcFlagsId = 0;
        for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs); i++)
        {
            if (g_SysWork.npcs[i].model.charaId != Chara_None)
            {
                npcFlagsId++;
            }
        }

        if (npcFlagsId >= g_SysWork.npcFlagsId)
        {
            return 0;
        }
    }

    // Run through NPC slots.
    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs); i++)
    {
        // Skip occupied slot.
        if (g_SysWork.npcs[i].model.charaId != Chara_None)
        {
            continue;
        }

        bzero(&g_SysWork.npcs[i], sizeof(s_SubCharacter));

        g_SysWork.npcs[i].model.charaId = charaId;
        g_SysWork.npcs[i].field_40 = arg1_1;

        if (charaId <= Chara_MonsterCybil && spawnFlags < 64)
        {
            SET_FLAG(g_SysWork.field_228C, arg1_1);
        }

        SET_FLAG(&g_SysWork.npcFlags, i);

        g_SysWork.npcs[i].model.controlState = 0;
        g_SysWork.npcs[i].model.stateStep    = stateStep;
        g_SysWork.npcs[i].position.vx        = posX;

        Collision_Get(&coll, posX, posZ);
        g_SysWork.npcs[i].position.vy = coll.groundHeight;
        g_SysWork.npcs[i].position.vz = posZ;
        g_SysWork.npcs[i].rotation.vy = rotY;

        chara                    = &g_SysWork.npcs[i];
        chara->model.anim.flags |= AnimFlag_Visible;

        return i;
    }

    return ARRAY_SIZE(g_SysWork.npcs);
}

void Chara_ModelCharaIdClear(s_SubCharacter* chara, s32 unused0, s32 unuse1) // 0x80088F94
{
    if (chara == NULL)
    {
        return;
    }

    if (chara->model.charaId <= Chara_MonsterCybil)
    {
        CLEAR_FLAG(g_SysWork.field_228C, chara->field_40);
    }

    chara->model.charaId = Chara_None;
}

void Chara_SpawnFlagsSet(e_CharaId charaId, s32 spawnIdx, s32 spawnFlags) // 0x80088FF4
{
    s_SpawnInfo* spawnInfo;

    spawnInfo          = &g_MapOverlayHeader.charaSpawnInfos[g_CharaAnimInfoIdxs[charaId] - 1][spawnIdx];
    spawnInfo->flags_6 = spawnFlags;
}

void Chara_SpawnPositionSet(e_CharaId charaId, s32 spawnIdx, q19_12 posX, q19_12 posZ) // 0x80089034
{
    s_SpawnInfo* spawnInfo0;
    s_SpawnInfo* spawnInfo1;

    spawnInfo0              = &g_MapOverlayHeader.charaSpawnInfos[g_CharaAnimInfoIdxs[charaId] - 1][spawnIdx];
    spawnInfo0->positionX = posX;

    spawnInfo1              = &g_MapOverlayHeader.charaSpawnInfos[g_CharaAnimInfoIdxs[charaId] - 1][spawnIdx];
    spawnInfo1->positionZ = posZ;
}
