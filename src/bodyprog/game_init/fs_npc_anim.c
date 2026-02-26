#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
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

s8 g_CharaAnimInfoIdxs[Chara_Count] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 3 0x00 padding.
};

s_CharaAnimDataInfo g_CharaTypeAnimInfo[GROUP_CHARA_COUNT] = {
    {
        .charaId0_0         = Chara_Harry,
        .charaId1_1         = Chara_Harry,
        .animFile0_4        = FS_BUFFER_0,
        .animFile1_8        = (s_AnmHeader*)FS_BUFFER_0,
        .animBufferSize1_C  = 0x2E630,
        .animBufferSize2_10 = 0x2E630,
        .npcCoords_14       = NULL
    }, {}, {}, {}
};

s_AnimInfo D_800A998C = {
    .updateFunc_0           = Anim_Update1,
    .status_4               = 0,
    .hasVariableDuration_5 = false,
    .status_6              = ANIM_STATUS(0, false),
    .duration_8            = { Q12(8.0f) },
    .startKeyframeIdx_C    = 26,
    .endKeyframeIdx_E      = 44
};

// ========================================
// CHARACTER ANIMATIONS MEMORY ALLOC
// ========================================

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

s32 Fs_CharaAnimDataInfoIdxGet(e_CharacterId charaId) // 0x800352F8
{
    s32 i;

    for (i = 1; (i < GROUP_CHARA_COUNT); i++)
    {
        if (g_CharaTypeAnimInfo[i].charaId1_1 == charaId)
        {
            return i;
        }
    }

    return 0;
}

void Fs_CharaAnimDataAlloc(s32 idx, e_CharacterId charaId, s_AnmHeader* animFile, GsCOORDINATE2* coord) // 0x80035338
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
            Fs_CharaAnimInfoUpdate(idx, charaId, initAnimDataInfo->animFile1_8, coord);
            return;
        }
        else if (localAnimFile < initAnimDataInfo->animFile1_8)
        {
            initAnimDataInfo->animFile0_4 = localAnimFile;

            Mem_Move32(localAnimFile, g_CharaTypeAnimInfo[idx].animFile1_8, g_CharaTypeAnimInfo[idx].animBufferSize2_10);
            Fs_CharaAnimInfoUpdate(idx, charaId, localAnimFile, coord);
            return;
        }
    }

    initAnimDataInfo->npcCoords_14       = &g_SysWork.npcCoords_FC0[0];
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
        Fs_CharaAnimInfoUpdate(idx, charaId, initAnimDataInfo->animFile0_4, coord);
    }
    else
    {
        Fs_QueueStartReadAnm(idx, charaId, localAnimFile, coord);
    }

    for (i = 1; i < GROUP_CHARA_COUNT; i++)
    {
        if (i != idx && g_CharaTypeAnimInfo[i].charaId1_1 != Chara_None && Fs_CharaAnimDataSizeCheck(idx, i) != false)
        {
            bzero(&g_CharaTypeAnimInfo[i], sizeof(s_CharaAnimDataInfo));
        }
    }
}

void Fs_CharaAnimInfoUpdate(s32 idx, e_CharacterId charaId, s_AnmHeader* animFile, GsCOORDINATE2* coord) // 0x80035560
{
    s32                  idx0;
    GsCOORDINATE2*       localCoord;
    s_CharaAnimDataInfo* animDataInfo;

    localCoord   = coord;
    animDataInfo = &g_CharaTypeAnimInfo[idx];

    if (localCoord == NULL)
    {
        if (idx == 1)
        {
            localCoord = &g_SysWork.npcCoords_FC0[0];
        }
        else if (idx >= 2)
        {
            idx0        = g_CharaTypeAnimInfo[idx - 1].animFile1_8->boneCount_6;
            localCoord  = g_CharaTypeAnimInfo[idx - 1].npcCoords_14;
            localCoord += idx0 + 1;

            // Check for end of `g_SysWork.npcCoords_FC0` array.
            if ((&localCoord[animFile->boneCount_6] + 1) >= &g_SysWork.npcCoords_FC0[NPC_BONE_COUNT_MAX])
            {
                localCoord = g_MapOverlayHeader.field_28;
            }
        }
    }

    animDataInfo->charaId1_1         = charaId;
    animDataInfo->animFile1_8        = animFile;
    animDataInfo->animBufferSize2_10 = Fs_GetFileSectorAlignedSize(CHARA_FILE_INFOS[charaId].animFileIdx);
    animDataInfo->npcCoords_14       = localCoord;

    Anim_BoneInit(animFile, localCoord);

    g_CharaAnimInfoIdxs[charaId] = idx;
}

void Fs_CharaAnimBoneInfoUpdate(void) // 0x8003569C
{
    s32            i;
    GsCOORDINATE2* coord;
    s_AnmHeader*   animFile;

    for (i = 1; i < GROUP_CHARA_COUNT - 1; i++)
    {
        if (g_MapOverlayHeader.charaGroupIds_248[i] != Chara_None)
        {
            coord    = g_CharaTypeAnimInfo[i].npcCoords_14;
            animFile = g_CharaTypeAnimInfo[i + 1].animFile1_8;
            coord   += g_CharaTypeAnimInfo[i].animFile1_8->boneCount_6 + 1;

            // Check for end of `g_SysWork.npcCoords_FC0` array.
            if ((&coord[animFile->boneCount_6] + 1) >= &g_SysWork.npcCoords_FC0[NPC_BONE_COUNT_MAX])
            {
                coord = g_MapOverlayHeader.field_28;
            }

            g_CharaTypeAnimInfo[i + 1].npcCoords_14 = coord;
            Anim_BoneInit(animFile, coord);
        }
    }
}
