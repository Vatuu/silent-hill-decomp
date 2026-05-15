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
#include "bodyprog/sound/sound_system.h"

// ========================================
// GLOBAL VARIABLES
// ========================================

s8 g_CharaAnimMetadataIdxs[Chara_Count] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    // 3 bytes of padding.
};

s_CharaAnimMetadata g_CharaTypeAnimMetadata[CHARA_GROUP_COUNT] = {
    {
        .charaId0_0         = Chara_Harry,
        .charaId1_1         = Chara_Harry,
        .animFile0_4        = FS_BUFFER_0,
        .animFile1_8        = (s_AnmHeader*)FS_BUFFER_0,
        .animBufferSize1_C  = 0x2E630,
        .animBufferSize2_10 = 0x2E630,
        .boneCoords         = NULL
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

bool Fs_CharaAnimDataSizeCheck(s32 animMetadataIdx0, s32 animMetadataIdx1) // 0x8003528C
{
    u32                  animBufferAddr1;
    u32                  animBufferAddr0;
    s_CharaAnimMetadata* animMetadata0;
    s_CharaAnimMetadata* animMetadata1;

    animMetadata0   = &g_CharaTypeAnimMetadata[animMetadataIdx0];
    animMetadata1   = &g_CharaTypeAnimMetadata[animMetadataIdx1];
    animBufferAddr0 = animMetadata0->animFile0_4;
    animBufferAddr1 = animMetadata1->animFile1_8;

    if (animBufferAddr0 >= (animBufferAddr1 + animMetadata1->animBufferSize2_10) ||
        animBufferAddr1 >= (animBufferAddr0 + animMetadata0->animBufferSize1_C))
    {
        return false;
    }

    return true;
}

s32 Fs_CharaAnimMetadataIdxGet(e_CharaId charaId) // 0x800352F8
{
    s32 i;

    for (i = 1; (i < CHARA_GROUP_COUNT); i++)
    {
        if (g_CharaTypeAnimMetadata[i].charaId1_1 == charaId)
        {
            return i;
        }
    }

    return 0;
}

void Fs_CharaAnimDataAlloc(s32 animMetadataIdx, e_CharaId charaId, s_AnmHeader* animFile, GsCOORDINATE2* boneCoords) // 0x80035338
{
    s32                  i;
    s_AnmHeader*         localAnimFile; // Local pointer required for match.
    s_CharaAnimMetadata* initAnimMetadata;
    s_CharaAnimMetadata* npcAnimMetadata;

    localAnimFile    = animFile;
    initAnimMetadata = &g_CharaTypeAnimMetadata[animMetadataIdx];

    if (charaId == Chara_None)
    {
        return;
    }

    // Estimates animation buffer data pointer by adding buffer size and current pointer position.
    for (npcAnimMetadata = &initAnimMetadata[-1]; localAnimFile == NULL; npcAnimMetadata--)
    {
        localAnimFile = npcAnimMetadata->animFile0_4 + npcAnimMetadata->animBufferSize1_C;
    }

    // If the target character ID matches with the selected element from `g_CharaTypeAnimMetadata`,
    // it ensures the animation buffer pointer matches with the previously estimated one.
    // If the estimated pointer is in a position behind of the currently saved one, it moves
    // data to the position of the estimated pointer.
    //
    // If any of the previous checks fail, values previously assigned at the index are cleared. If
    // the character hasn't been loaded in a different `g_InitializedCharaAnimInfo` slot, the
    // animation file is loaded.
    if (initAnimMetadata->charaId1_1 == charaId)
    {
        if (animMetadataIdx == 1 || localAnimFile == initAnimMetadata->animFile1_8)
        {
            Fs_CharaAnimDataUpdate(animMetadataIdx, charaId, initAnimMetadata->animFile1_8, boneCoords);
            return;
        }
        else if (localAnimFile < initAnimMetadata->animFile1_8)
        {
            initAnimMetadata->animFile0_4 = localAnimFile;

            Mem_Move32(localAnimFile,
                       g_CharaTypeAnimMetadata[animMetadataIdx].animFile1_8,
                       g_CharaTypeAnimMetadata[animMetadataIdx].animBufferSize2_10);
            Fs_CharaAnimDataUpdate(animMetadataIdx, charaId, localAnimFile, boneCoords);
            return;
        }
    }

    initAnimMetadata->boneCoords         = &g_SysWork.npcBoneCoords[0];
    initAnimMetadata->charaId1_1         = Chara_None;
    initAnimMetadata->animFile1_8        = NULL;
    initAnimMetadata->animBufferSize2_10 = 0;
    initAnimMetadata->charaId0_0         = charaId;
    initAnimMetadata->animFile0_4        = localAnimFile;
    initAnimMetadata->animBufferSize1_C  = Fs_GetFileSectorAlignedSize(CHARA_FILE_INFOS[charaId].animFileIdx);

    i = Fs_CharaAnimMetadataIdxGet(charaId);

    if (i > 0)
    {
        Mem_Move32(g_CharaTypeAnimMetadata[animMetadataIdx].animFile0_4,
                   g_CharaTypeAnimMetadata[i].animFile1_8,
                   g_CharaTypeAnimMetadata[i].animBufferSize2_10);
        Fs_CharaAnimDataUpdate(animMetadataIdx, charaId, initAnimMetadata->animFile0_4, boneCoords);
    }
    else
    {
        Fs_QueueStartReadAnm(animMetadataIdx, charaId, localAnimFile, boneCoords);
    }

    for (i = 1; i < CHARA_GROUP_COUNT; i++)
    {
        if (i != animMetadataIdx && g_CharaTypeAnimMetadata[i].charaId1_1 != Chara_None &&
            Fs_CharaAnimDataSizeCheck(animMetadataIdx, i) != false)
        {
            bzero(&g_CharaTypeAnimMetadata[i], sizeof(s_CharaAnimMetadata));
        }
    }
}

void Fs_CharaAnimDataUpdate(s32 animMetadataIdx, e_CharaId charaId, s_AnmHeader* animFile, GsCOORDINATE2* boneCoords) // 0x80035560
{
    s32                  boneCount;
    GsCOORDINATE2*       localBoneCoords;
    s_CharaAnimMetadata* animMetadata;

    localBoneCoords = boneCoords;
    animMetadata    = &g_CharaTypeAnimMetadata[animMetadataIdx];

    if (localBoneCoords == NULL)
    {
        if (animMetadataIdx == 1)
        {
            localBoneCoords = &g_SysWork.npcBoneCoords[0];
        }
        else if (animMetadataIdx >= 2)
        {
            boneCount        = g_CharaTypeAnimMetadata[animMetadataIdx - 1].animFile1_8->boneCount;
            localBoneCoords  = g_CharaTypeAnimMetadata[animMetadataIdx - 1].boneCoords;
            localBoneCoords += boneCount + 1;

            // Check for end of `g_SysWork.npcBoneCoords` array.
            if ((&localBoneCoords[animFile->boneCount] + 1) >= &g_SysWork.npcBoneCoords[NPC_BONE_COUNT_MAX])
            {
                localBoneCoords = g_MapOverlayHeader.unkBoneCoords_28;
            }
        }
    }

    animMetadata->charaId1_1         = charaId;
    animMetadata->animFile1_8        = animFile;
    animMetadata->animBufferSize2_10 = Fs_GetFileSectorAlignedSize(CHARA_FILE_INFOS[charaId].animFileIdx);
    animMetadata->boneCoords         = localBoneCoords;

    Anim_BoneInit(animFile, localBoneCoords);

    g_CharaAnimMetadataIdxs[charaId] = animMetadataIdx;
}

void Fs_CharaAnimBoneInfoUpdate(void) // 0x8003569C
{
    s32            i;
    GsCOORDINATE2* boneCoords;
    s_AnmHeader*   anmHdr;

    for (i = 1; i < (CHARA_GROUP_COUNT - 1); i++)
    {
        if (g_MapOverlayHeader.charaGroupIds[i] != Chara_None)
        {
            boneCoords  = g_CharaTypeAnimMetadata[i].boneCoords;
            anmHdr      = g_CharaTypeAnimMetadata[i + 1].animFile1_8;
            boneCoords += g_CharaTypeAnimMetadata[i].animFile1_8->boneCount + 1;

            // Check for end of `g_SysWork.npcBoneCoords` array.
            if ((&boneCoords[anmHdr->boneCount] + 1) >= &g_SysWork.npcBoneCoords[NPC_BONE_COUNT_MAX])
            {
                boneCoords = g_MapOverlayHeader.unkBoneCoords_28;
            }

            g_CharaTypeAnimMetadata[i + 1].boneCoords = boneCoords;
            Anim_BoneInit(anmHdr, boneCoords);
        }
    }
}
