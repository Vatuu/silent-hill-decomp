#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/game_boot/fs_chara_anim.h"
#include "main/fsqueue.h"
#include "bodyprog/demo.h"
#include "bodyprog/game_boot/game_boot.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "bodyprog/ranking.h"
#include "bodyprog/sound_system.h"

// ========================================
// GLOBAL VARIABLES
// ========================================

s8 g_CharaAnimInfoIdxs[Chara_Count] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    // 3 bytes of padding.
};

s_CharaAnimDataInfo g_CharaTypeAnimInfo[CHARA_GROUP_COUNT] = {
    {
        .charaId0_0         = Chara_Harry,
        .charaId1_1         = Chara_Harry,
        .animFile0_4        = FS_BUFFER_0,
        .animFile1_8        = (s_AnmHeader*)FS_BUFFER_0,
        .animBufferSize1_C  = 0x2E630,
        .animBufferSize2_10 = 0x2E630,
        .npcBoneCoords      = NULL
    },
    {},
    {},
    {}
};

s_AnimInfo D_800A998C = {
    .playbackFunc        = Anim_PlaybackLoop,
    .status              = 0,
    .hasVariableDuration = false,
    .linkStatus          = ANIM_STATUS(0, false),
    .duration            = { Q12(8.0f) },
    .startKeyframeIdx    = 26,
    .endKeyframeIdx      = 44
};

bool Fs_CharaAnimDataSizeCheck(s32 charaDataAnimInfoIdx0, s32 charaDataAnimInfoIdx1) // 0x8003528C
{
    u32                  animBufferAddress1;
    u32                  animBufferAddress0;
    s_CharaAnimDataInfo* animDataInfo0;
    s_CharaAnimDataInfo* animDataInfo1;

    animDataInfo0      = &g_CharaTypeAnimInfo[charaDataAnimInfoIdx0];
    animDataInfo1      = &g_CharaTypeAnimInfo[charaDataAnimInfoIdx1];
    animBufferAddress0 = animDataInfo0->animFile0_4;
    animBufferAddress1 = animDataInfo1->animFile1_8;

    if (animBufferAddress0 >= (animBufferAddress1 + animDataInfo1->animBufferSize2_10) ||
        animBufferAddress1 >= (animBufferAddress0 + animDataInfo0->animBufferSize1_C))
    {
        return false;
    }

    return true;
}

s32 Fs_CharaAnimDataInfoIdxGet(e_CharaId charaId) // 0x800352F8
{
    s32 i;

    for (i = 1; (i < CHARA_GROUP_COUNT); i++)
    {
        if (g_CharaTypeAnimInfo[i].charaId1_1 == charaId)
        {
            return i;
        }
    }

    return 0;
}

void Fs_CharaAnimDataAlloc(s32 idx, e_CharaId charaId, s_AnmHeader* animFile, GsCOORDINATE2* boneCoords) // 0x80035338
{
    s32                  i;
    s_AnmHeader*         localAnimFile; // Local pointer required for match.
    s_CharaAnimDataInfo* initAnimDataInfo;
    s_CharaAnimDataInfo* npcAnimDataInfo;

    localAnimFile    = animFile;
    initAnimDataInfo = &g_CharaTypeAnimInfo[idx];

    if (charaId == Chara_None)
    {
        return;
    }

    // Estimates animation buffer data pointer by adding buffer size and current pointer position.
    for (npcAnimDataInfo = &initAnimDataInfo[-1]; localAnimFile == NULL; npcAnimDataInfo--)
    {
        localAnimFile = npcAnimDataInfo->animFile0_4 + npcAnimDataInfo->animBufferSize1_C;
    }

    // If the target character ID matches with the selected element from `g_CharaTypeAnimInfo`
    // then it ensures the animation buffer pointer matches with the previously estimated one, but
    // if the estimated pointer is in a position behind of the currently saved one then it moves
    // data to the position of the estimated pointer.
    //
    // If any of the previous checks fail, values previously assigned at index are cleared. Then, if
    // the character hasn't been loaded in a different `g_InitializedCharaAnimInfo` slot, the
    // animation file is loaded.
    if (initAnimDataInfo->charaId1_1 == charaId)
    {
        if (idx == 1 || localAnimFile == initAnimDataInfo->animFile1_8)
        {
            Fs_CharaAnimInfoUpdate(idx, charaId, initAnimDataInfo->animFile1_8, boneCoords);
            return;
        }
        else if (localAnimFile < initAnimDataInfo->animFile1_8)
        {
            initAnimDataInfo->animFile0_4 = localAnimFile;

            Mem_Move32(localAnimFile, g_CharaTypeAnimInfo[idx].animFile1_8, g_CharaTypeAnimInfo[idx].animBufferSize2_10);
            Fs_CharaAnimInfoUpdate(idx, charaId, localAnimFile, boneCoords);
            return;
        }
    }

    initAnimDataInfo->npcBoneCoords      = &g_SysWork.npcBoneCoords[0];
    initAnimDataInfo->charaId1_1         = Chara_None;
    initAnimDataInfo->animFile1_8        = NULL;
    initAnimDataInfo->animBufferSize2_10 = 0;
    initAnimDataInfo->charaId0_0         = charaId;
    initAnimDataInfo->animFile0_4        = localAnimFile;
    initAnimDataInfo->animBufferSize1_C  = Fs_GetFileSectorAlignedSize(CHARA_FILE_INFOS[charaId].animFileIdx);

    i = Fs_CharaAnimDataInfoIdxGet(charaId);

    if (i > 0)
    {
        Mem_Move32(g_CharaTypeAnimInfo[idx].animFile0_4, g_CharaTypeAnimInfo[i].animFile1_8, g_CharaTypeAnimInfo[i].animBufferSize2_10);
        Fs_CharaAnimInfoUpdate(idx, charaId, initAnimDataInfo->animFile0_4, boneCoords);
    }
    else
    {
        Fs_QueueStartReadAnm(idx, charaId, localAnimFile, boneCoords);
    }

    for (i = 1; i < CHARA_GROUP_COUNT; i++)
    {
        if (i != idx && g_CharaTypeAnimInfo[i].charaId1_1 != Chara_None && Fs_CharaAnimDataSizeCheck(idx, i) != false)
        {
            bzero(&g_CharaTypeAnimInfo[i], sizeof(s_CharaAnimDataInfo));
        }
    }
}

void Fs_CharaAnimInfoUpdate(s32 idx, e_CharaId charaId, s_AnmHeader* animFile, GsCOORDINATE2* boneCoords) // 0x80035560
{
    s32                  idx0;
    GsCOORDINATE2*       localBoneCoords;
    s_CharaAnimDataInfo* animDataInfo;

    localBoneCoords   = boneCoords;
    animDataInfo = &g_CharaTypeAnimInfo[idx];

    if (localBoneCoords == NULL)
    {
        if (idx == 1)
        {
            localBoneCoords = &g_SysWork.npcBoneCoords[0];
        }
        else if (idx >= 2)
        {
            idx0        = g_CharaTypeAnimInfo[idx - 1].animFile1_8->boneCount;
            localBoneCoords  = g_CharaTypeAnimInfo[idx - 1].npcBoneCoords;
            localBoneCoords += idx0 + 1;

            // Check for end of `g_SysWork.npcBoneCoords` array.
            if ((&localBoneCoords[animFile->boneCount] + 1) >= &g_SysWork.npcBoneCoords[NPC_BONE_COUNT_MAX])
            {
                localBoneCoords = g_MapOverlayHeader.field_28;
            }
        }
    }

    animDataInfo->charaId1_1         = charaId;
    animDataInfo->animFile1_8        = animFile;
    animDataInfo->animBufferSize2_10 = Fs_GetFileSectorAlignedSize(CHARA_FILE_INFOS[charaId].animFileIdx);
    animDataInfo->npcBoneCoords      = localBoneCoords;

    Anim_BoneInit(animFile, localBoneCoords);

    g_CharaAnimInfoIdxs[charaId] = idx;
}

void Fs_CharaAnimBoneInfoUpdate(void) // 0x8003569C
{
    s32            i;
    GsCOORDINATE2* boneCoord;
    s_AnmHeader*   animFile;

    for (i = 1; i < (CHARA_GROUP_COUNT - 1); i++)
    {
        if (g_MapOverlayHeader.charaGroupIds[i] != Chara_None)
        {
            boneCoord  = g_CharaTypeAnimInfo[i].npcBoneCoords;
            animFile   = g_CharaTypeAnimInfo[i + 1].animFile1_8;
            boneCoord += g_CharaTypeAnimInfo[i].animFile1_8->boneCount + 1;

            // Check for end of `g_SysWork.npcBoneCoords` array.
            if ((&boneCoord[animFile->boneCount] + 1) >= &g_SysWork.npcBoneCoords[NPC_BONE_COUNT_MAX])
            {
                boneCoord = g_MapOverlayHeader.field_28;
            }

            g_CharaTypeAnimInfo[i + 1].npcBoneCoords = boneCoord;
            Anim_BoneInit(animFile, boneCoord);
        }
    }
}
