#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"

// ========================================
// CHARACTER SPAWN RELATED
// ========================================

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

void func_80088D34(s32 idx) // 0x80088D34
{
    idx++;
    Anim_BoneInit(g_CharaTypeAnimInfo[idx].animFile1_8, g_CharaTypeAnimInfo[idx].npcCoords_14);
}

s32 Chara_Spawn(e_CharacterId charaId, s32 arg1, q19_12 posX, q19_12 posZ, q3_12 rotY, u32 stateStep) // 0x80088D78
{
    s_Collision     coll;
    s32             i;
    s32             var_a0;
    s32             arg1_1;
    s_SubCharacter* var_s6;

    if (charaId <= Chara_MonsterCybil && arg1 < 0x40)
    {
        arg1_1 = 0x1F;
        arg1_1 = arg1 & arg1_1;
    }
    else
    {
        arg1_1 = 0;
    }

    if (charaId <= Chara_MonsterCybil)
    {
        if (HAS_FLAG(g_SysWork.field_228C, arg1_1))
        {
            for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
            {
                if (g_SysWork.npcs_1A0[i].field_40 == arg1_1)
                {
                    return i;
                }
            }

            return ARRAY_SIZE(g_SysWork.npcs_1A0);
        }

        var_a0 = 0;
        for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
        {
            if (g_SysWork.npcs_1A0[i].model_0.charaId_0 != Chara_None)
            {
                var_a0++;
            }
        }

        if (var_a0 >= g_SysWork.npcId_2280)
        {
            return 0;
        }
    }

    // Run through NPC slots.
    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
    {
        // Skip occupied slot.
        if (g_SysWork.npcs_1A0[i].model_0.charaId_0 != Chara_None)
        {
            continue;
        }

        bzero(&g_SysWork.npcs_1A0[i], sizeof(s_SubCharacter));

        g_SysWork.npcs_1A0[i].model_0.charaId_0 = charaId;
        g_SysWork.npcs_1A0[i].field_40 = arg1_1;

        if (charaId <= Chara_MonsterCybil && arg1 < 64)
        {
            SET_FLAG(g_SysWork.field_228C, arg1_1);
        }

        SET_FLAG(&g_SysWork.npcFlags_2290, i);

        g_SysWork.npcs_1A0[i].model_0.controlState_2     = ModelState_Uninitialized;
        g_SysWork.npcs_1A0[i].model_0.stateStep_3 = stateStep;

        g_SysWork.npcs_1A0[i].position_18.vx = posX;
        Collision_Get(&coll, posX, posZ);
        g_SysWork.npcs_1A0[i].position_18.vy = coll.groundHeight_0;
        g_SysWork.npcs_1A0[i].position_18.vz = posZ;
        g_SysWork.npcs_1A0[i].rotation_24.vy = rotY;

        var_s6                          = &g_SysWork.npcs_1A0[i];
        var_s6->model_0.anim_4.flags_2 |= AnimFlag_Visible;

        return i;
    }

    return ARRAY_SIZE(g_SysWork.npcs_1A0);
}

void func_80088F94(s_SubCharacter* chara, s32 unused1, s32 unused2) // 0x80088F94
{
    if (chara == NULL)
    {
        return;
    }

    if (chara->model_0.charaId_0 <= Chara_MonsterCybil)
    {
        CLEAR_FLAG(g_SysWork.field_228C, chara->field_40);
    }

    chara->model_0.charaId_0 = Chara_None;
}

void func_80088FF4(e_CharacterId charaId, s32 spawnIdx, s32 spawnFlags) // 0x80088FF4
{
    s_SpawnInfo* spawnInfo;

    spawnInfo          = &g_MapOverlayHeader.charaSpawns_24C[g_CharaAnimInfoIdxs[charaId] - 1][spawnIdx];
    spawnInfo->flags_6 = spawnFlags;
}

void func_80089034(e_CharacterId charaId, s32 spawnIdx, q19_12 posX, q19_12 posZ) // 0x80089034
{
    s_MapPoint2d* mapPoint0;
    s_MapPoint2d* mapPoint1;

    mapPoint0              = &g_MapOverlayHeader.charaSpawns_24C[g_CharaAnimInfoIdxs[charaId] - 1][spawnIdx];
    mapPoint0->positionX_0 = posX;

    mapPoint1              = &g_MapOverlayHeader.charaSpawns_24C[g_CharaAnimInfoIdxs[charaId] - 1][spawnIdx];
    mapPoint1->positionZ_8 = posZ;
}
