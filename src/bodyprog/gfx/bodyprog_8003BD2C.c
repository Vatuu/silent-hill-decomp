#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/memcard.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

static const s32 pad_rodata_80025524 = 0;

// ========================================
// UNKNOWN - IN-GAME RELATED
// ========================================

s32 Map_TypeGet(void) // 0x8003BD2C
{
    return g_WorldGfx.mapInfo_0 - MAP_INFOS;
}

void func_8003BD48(s_SubCharacter* chara) // 0x8003BD48
{
    u16 var_s0;

    D_800BCE14 = func_80069810();
    var_s0     = D_800BCE14;

    switch (Map_TypeGet())
    {
        case 0:
            if (chara->position_18.vx >= Q12(191.6f) && chara->position_18.vx <= Q12(198.8f) &&
                chara->position_18.vz >= Q12(-96.0f) && chara->position_18.vz <= Q12(-90.3f))
            {
                var_s0 = (var_s0 & ~0x2) | 0x4;
            }
            break;

        case 3:
        case 4:
            if (chara->position_18.vx >= Q12(-100.0f) && chara->position_18.vx <= Q12(-94.5f) &&
                chara->position_18.vz >= Q12(-70.3f) && chara->position_18.vz <= Q12(-62.0f))
            {
                var_s0 = (var_s0 & ~0x2) | 0x4;
            }
    }

    func_80069820(var_s0);
}

void func_8003BE28(void) // 0x8003BE28
{
    func_80069820(D_800BCE14);
}

s_LinkedBone* WorldGfx_CharaModelBonesGet(e_CharacterId charaId) // 0x8003BE50
{
    return g_WorldGfx.registeredCharaModels_18[charaId]->skeleton_14.bones_C;
}

// ========================================
// MAP GRAPHIC INITALIZATION
// ========================================

extern s_WorldEnvWork const g_WorldEnvWork;

void GameFs_BgEtcGfxLoad(void) // 0x8003BE6C
{
    static s_FsImageDesc IMAGE = { .tPage = { 0, 12 }, .clutX = 192 };

    Fs_QueueStartReadTim(FILE_TIM_BG_ETC_TIM, FS_BUFFER_1, &IMAGE);
}

void GameFs_BgItemLoad(void) // 0x8003BE9C
{
    g_WorldGfx.itemLmQueueIdx_2BE4 = Fs_QueueStartRead(FILE_BG_BG_ITEM_PLM, &g_WorldGfx.itemLmHdr_1BE4);
}

void func_8003BED0(void) // 0x8003BED0
{
    static s_FsImageDesc IMAGE_TIM = {
        .tPage = { 0, 15 },
        .u     = 0,
        .v     = 0,
        .clutX = 176,
        .clutY = 0
    };

    static s_FsImageDesc IMAGE_ETC = {
        .tPage = { 0, 12 },
        .u     = 0,
        .v     = 192,
        .clutX = 192,
        .clutY = 0
    };

    s_LmHeader* itemLmHdr;

    itemLmHdr = &g_WorldGfx.itemLmHdr_1BE4;

    if (!Fs_QueueIsEntryLoaded(g_WorldGfx.itemLmQueueIdx_2BE4) || itemLmHdr->isLoaded_2)
    {
        return;
    }

    LmHeader_FixOffsets(&g_WorldGfx.itemLmHdr_1BE4);
    Lm_MaterialFsImageApply1(&g_WorldGfx.itemLmHdr_1BE4, "TIM00", &IMAGE_TIM, 1);
    Lm_MaterialFsImageApply1(&g_WorldGfx.itemLmHdr_1BE4, "BG_ETC", &IMAGE_ETC, 1);
    Lm_MaterialFlagsApply(&g_WorldGfx.itemLmHdr_1BE4);
}

s32 Map_SpeedZoneTypeGet(q19_12 posX, q19_12 posZ) // 0x8003BF60
{
    s32                zoneType;
    const s_SpeedZone* curZone;

    zoneType = SpeedZoneType_Slow;

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP0_S00)
    {
        return SpeedZoneType_Normal;
    }

    if (g_WorldGfx.mapInfo_0->speedZones_C != NULL)
    {
        curZone = g_WorldGfx.mapInfo_0->speedZones_C;
        while (curZone->type_0 != NO_VALUE)
        {
            if (posX >= Q4_TO_Q12(curZone->minX_2) && Q4_TO_Q12(curZone->maxX_4) >= posX &&
                posZ >= Q4_TO_Q12(curZone->minZ_6) && Q4_TO_Q12(curZone->maxZ_8) >= posZ &&
                zoneType < curZone->type_0)
            {
                zoneType = curZone->type_0;
            }

            curZone++;
        }
    }

    return zoneType;
}

void WorldGfx_MapInit(void) // 0x8003C048
{
    WorldEnv_Init();

    g_WorldGfx.useStoredPoint_4 = false;

    Map_Init(GLOBAL_LM_BUFFER, IPD_BUFFER, 0x2C000);
    func_800697EC();

    g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

    Game_FlashlightAttributesFix();
    func_8005B55C(vwGetViewCoord());
    Gfx_WorldObjectsClear(&g_WorldGfx);
}

void Item_HeldItemModelFree(void) // 0x8003C0C0
{
    s_HeldItem* heldItem;

    heldItem = &g_WorldGfx.heldItem_1BAC;

    heldItem->itemId_0                       = NO_VALUE;
    heldItem->lmHdr_14                       = HELD_ITEM_LM_BUFFER;
    heldItem->bone_18.modelInfo_0.field_0    = 0;
    heldItem->bone_18.modelInfo_0.coord_4    = NULL;
    heldItem->bone_18.modelInfo_0.modelHdr_8 = NULL;
}

void CharaModel_AllModelsFree(void) // 0x8003C110
{
    s32           i;
    s_CharaModel* curModel;

    for (i = 0; i < Chara_Count; i++)
    {
        if (i != Chara_Harry)
        {
            g_WorldGfx.registeredCharaModels_18[i] = NULL;
        }
    }

    g_WorldGfx.charaLmBuffer_14 = MAP_CHARA_LM_BUFFER;
    for (curModel = &g_WorldGfx.charaModels_CC[0]; curModel < &g_WorldGfx.charaModels_CC[4]; curModel++)
    {
        CharaModel_Free(curModel);
    }
}

void CharaModel_Free(s_CharaModel* model) // 0x8003C1AC
{
    s_FsImageDesc image = { 0 };

    //memset(&image, 0, 8);
    model->charaId_0  = Chara_None;
    model->isLoaded_1 = false;
    model->queueIdx_4 = 0;
    model->lmHdr_8    = MAP_CHARA_LM_BUFFER;
    model->texture_C  = image;
}

void Ipd_PlayerChunkInit(s_MapOverlayHeader* mapHdr, s32 playerPosX, s32 playerPosZ) // 0x8003C220
{
    s32        activeIpdCount;
    u8         flags;
    s_MapInfo* mapInfo;

    g_WorldGfx.mapInfo_0 = mapHdr->mapInfo_0;

    flags = mapHdr->mapInfo_0->flags_6;
    if (flags & MapFlag_OneActiveChunk)
    {
        activeIpdCount = 1;
    }
    else if (flags & MapFlag_TwoActiveChunks)
    {
        activeIpdCount = 2;
    }
    else
    {
        activeIpdCount = 4;
    }

    mapInfo = mapHdr->mapInfo_0;
    Ipd_MapFileInfoSet(mapInfo->tag_2, mapInfo->plmFileIdx_0, activeIpdCount, CHECK_FLAG(mapInfo->flags_6, MapFlag_Interior, false), 0, 0);

    if (mapHdr->mapInfo_0 == &MAP_INFOS[MapType_THR])
    {
        Map_PlaceIpdAtCell(FILE_BG_THR05FD_IPD, -1, 8);
    }

    Ipd_ChunkInit(playerPosX, playerPosZ, playerPosX, playerPosZ);
}

void Ipd_ActiveMapChunksClear0(void) // 0x8003C2EC
{
    Ipd_ActiveMapChunksClear();
}

void Map_WorldClear(void) // 0x8003C30C
{
    u8 flags;

    flags = g_WorldGfx.mapInfo_0->flags_6;
    if ((flags & MapFlag_Interior) && (flags & (MapFlag_OneActiveChunk | MapFlag_TwoActiveChunks)))
    {
        Map_WorldClearReset();
        return;
    }

    Ipd_ActiveMapChunksClear();
    Ipd_TexturesRefClear();
}

void WorldGfx_IpdSamplePointStore(void) // 0x8003C368
{
    g_WorldGfx.useStoredPoint_4 = true;
    g_WorldGfx.ipdSamplePoint_8 = g_SysWork.playerWork_4C.player_0.position_18;
}

void WorldGfx_IpdSamplePointReset(void) // 0x8003C3A0
{
    g_WorldGfx.useStoredPoint_4 = false;
}

void Ipd_CloseRangeChunksInit(void) // 0x8003C3AC
{
    VECTOR3         pos0; // Draw distance?
                          // Modifying `pos0.vz = Q12(200.0f);` makes the world to not draw. In the void, the player becomes immovable.
                          //
                          // Most of the time, X and Z share the same value as
                          // the player player position or a position slightly ahead computed from the heading angle.
                          //
                          // In Old Silent Hill (after Cafe 5to2) while standing still, this value is
                          // the same as `g_SysWork.playerWork_4C.player_0.position_18`.
    VECTOR3         pos1; // Draw distance?
                          // If the conditional `if (g_WorldEnvWork.isFogEnabled_1)` is reversed
                          // to run the `else` block, when fog is enabled, the draw distance
                          // is slightly reduced.
                          //
                          // Similarly to `pos0`, when fog is disabled, it uses the player position.
                          // Otherwise it's based the camera position, using its rotation to then make some extra calculations.
    SVECTOR         rot;
    s32             temp_a1;
    s32             temp_a2;
    q19_12          moveAmt;
    s32             temp_s0_2;
    s32             temp_v1_4;
    s32             var_a0;
    s32             var_a1;
    s32             var_s1;
    u8              flagsCpy;
    s_SubCharacter* chara;

    chara = &g_SysWork.playerWork_4C.player_0;

    if (g_WorldGfx.useStoredPoint_4)
    {
        pos0 = g_WorldGfx.ipdSamplePoint_8;
    }
    else
    {
        pos0 = chara->position_18;
    }

    moveAmt = (chara->moveSpeed_38 * Q12(5.5f)) / 16015; // TODO: `Q12(3.91f)`? What's this doing?
    moveAmt = CLAMP(moveAmt, Q12(0.0f), Q12(5.5f));

    pos0.vx += Q12_MULT_PRECISE(moveAmt, Math_Sin(chara->headingAngle_3C));
    pos0.vz += Q12_MULT_PRECISE(moveAmt, Math_Cos(chara->headingAngle_3C));

    if (g_WorldGfx.mapInfo_0 == &MAP_INFOS[MapType_THR] &&
        chara->position_18.vx >= Q12(-40.0f) && chara->position_18.vx <= Q12(40.0f) &&
        chara->position_18.vz >= Q12(200.0f) && chara->position_18.vz <= Q12(240.0f))
    {
        pos0.vz = Q12(200.0f);
    }

    if (g_WorldEnvWork.isFogEnabled_1)
    {
        vwGetViewPosition(&pos1);
        vwGetViewAngle(&rot);

        flagsCpy = g_WorldGfx.mapInfo_0->flags_6;
        if (!(flagsCpy & MapFlag_Interior) || !(flagsCpy & (MapFlag_OneActiveChunk | MapFlag_TwoActiveChunks)))
        {
            var_s1 = Q12_MULT(Math_Cos(rot.vx), Q12(9.0f));
        }
        else
        {
            var_s1 = Q12(0.0f);
        }

        temp_s0_2 = Q12_MULT(var_s1, Math_Sin(rot.vy));
        temp_s0_2 = CLAMP(temp_s0_2, Q12(-6.0f), Q12(6.0f));

        temp_v1_4 = Q12_MULT(var_s1, Math_Cos(rot.vy));
        temp_v1_4 = CLAMP(temp_v1_4, Q12(-6.0f), Q12(6.0f));

        pos1.vx += temp_s0_2;
        pos1.vz += temp_v1_4;

        if (Vc_VectorMagnitudeCalc(pos1.vx - chara->position_18.vx, Q12(0.0f), pos1.vz - chara->position_18.vz) > Q12(16.0f))
        {
            var_s1  = Q12(14.0f);
            pos1.vx = chara->position_18.vx + Q12_MULT(Math_Sin(rot.vy), var_s1);
            pos1.vz = chara->position_18.vz + Q12_MULT(Math_Cos(rot.vy), var_s1);
        }
    }
    else
    {
        pos1     = chara->position_18;
        pos1.vx += FP_FROM(Q12(Math_Sin(chara->rotation_24.vy)), Q12_SHIFT);
        pos1.vz += FP_FROM(Q12(Math_Cos(chara->rotation_24.vy)), Q12_SHIFT);
    }

    flagsCpy = g_WorldGfx.mapInfo_0->flags_6;
    if ((flagsCpy & MapFlag_Interior) && (flagsCpy & (MapFlag_OneActiveChunk | MapFlag_TwoActiveChunks)))
    {
        var_a1 = chara->position_18.vx / Q12(2.5f);
        if (chara->position_18.vx < Q12(0.0f))
        {
            var_a1--;
        }

        var_a0  = chara->position_18.vz / Q12(2.5f);
        temp_a1 = var_a1 * Q12(2.5f);

        if (chara->position_18.vz < Q12(0.0f))
        {
            var_a0--;
        }

        temp_a2 = var_a0 * Q12(2.5f);

        pos0.vx = CLAMP(pos0.vx, temp_a1 + 1, temp_a1 + (Q12(2.5f) - 1));
        pos0.vz = CLAMP(pos0.vz, temp_a2 + 1, temp_a2 + (Q12(2.5f) - 1));
        pos1.vx = CLAMP(pos1.vx, temp_a1 + 1, temp_a1 + (Q12(2.5f) - 1));
        pos1.vz = CLAMP(pos1.vz, temp_a2 + 1, temp_a2 + (Q12(2.5f) - 1));
    }

    Ipd_ChunkInit(pos0.vx, pos0.vz, pos1.vx, pos1.vz);
}

s32 Ipd_ChunkInitCheck(void) // 0x8003C850
{
    Ipd_CloseRangeChunksInit();
    return Ipd_AreChunksLoaded();
}

void Gfx_InGameDraw(s32 arg0) // 0x8003C878
{
    Gfx_WorldObjectsDraw(&g_WorldGfx);

    while (func_80043830())
    {
        Ipd_CloseRangeChunksInit();
        Fs_QueueWaitForEmpty();
    }

    Ipd_ChunkCheckDraw(&g_OrderingTable0[g_ActiveBufferIdx], arg0);
    Gfx_2dEffectsDraw();
}

// ========================================
// OBJECTS DRAW
// ========================================

void WorldObject_ModelNameSet(s_WorldObjectModel* arg0, char* newStr) // 0x8003C8F8
{
    arg0->metadata_10.lmIdx_9 = 0;
    arg0->modelInfo_0.field_0  = 0;

    StringCopy(arg0->metadata_10.name_0.str, newStr);

    arg0->metadata_10.field_8 = 0;
}

void WorldGfx_ObjectAdd(s_WorldObjectModel* arg0, const VECTOR3* pos, const SVECTOR3* rot) // 0x8003C92C
{
    q23_8          geomPosX;
    q23_8          geomPosY;
    q23_8          geomPosZ;
    q21_10         geomRotX;
    q19_12         geomRotY;
    q21_10         geomRotZ;
    s32            i;
    s32            lmIdx;
    s_WorldObject* obj;

    // Check if array of world objects to draw is full.
    if (g_WorldGfx.objectCount_2BE8 < ARRAY_SIZE(g_WorldGfx.objects_2BEC))
    {
        if (arg0->metadata_10.lmIdx_9 == 0)
        {
            func_8003BED0();

            lmIdx = func_8004287C(arg0, &arg0->metadata_10, g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz);
            if (lmIdx == 0)
            {
                if (!Lm_ModelFind(arg0, &g_WorldGfx.itemLmHdr_1BE4, &arg0->metadata_10))
                {
                    return;
                }
                else
                {
                    lmIdx = 1;
                }
            }

            arg0->metadata_10.lmIdx_9 = lmIdx;
        }

        // Compute geometry position and rotation.
        geomPosX = Q12_TO_Q8(pos->vx);
        geomPosY = Q12_TO_Q8(pos->vy);
        geomPosZ = Q12_TO_Q8(pos->vz);
        geomRotX = Q12_TO_Q10(rot->vx);
        geomRotY = Q12_TO_Q10(rot->vz);
        geomRotZ = rot->vy;

        // Check if world object to draw was already submitted?
        for (i = 0; i < g_WorldGfx.objectCount_2BE8; i++)
        {
            obj = &g_WorldGfx.objects_2BEC[i];

            if (arg0 == obj->model_0 &&
                geomPosX == obj->positionX_4 &&
                geomPosZ == obj->positionZ_8 &&
                geomPosY == obj->positionY_4 &&
                geomRotX == obj->rotationX_C &&
                geomRotZ == obj->rotationY_C &&
                geomRotY == obj->rotationZ_C)
            {
                return;
            }
        }

        // Submit world object to draw.
        obj = &g_WorldGfx.objects_2BEC[g_WorldGfx.objectCount_2BE8];
        obj->rotationX_C = geomRotX;
        obj->rotationY_C = geomRotZ;
        if (obj->positionZ_8) {} // @hack Required for match.
        obj->rotationZ_C = geomRotY;
        obj->model_0     = arg0;
        obj->positionX_4 = geomPosX;
        obj->positionY_4 = geomPosY;
        obj->positionZ_8 = geomPosZ;

        g_WorldGfx.objectCount_2BE8++;
    }
}

void Gfx_WorldObjectsClear(s_WorldGfxWork* worldGfxWork) // 0x8003CB3C
{
    worldGfxWork->objectCount_2BE8 = 0;
}

void Gfx_WorldObjectsDraw(s_WorldGfxWork* worldGfxWork) // 0x8003CB44
{
    s_WorldObject* curObj;

    // Run through world objects to draw.
    for (curObj = &worldGfxWork->objects_2BEC[0]; curObj < &worldGfxWork->objects_2BEC[worldGfxWork->objectCount_2BE8]; curObj++)
    {
        Gfx_WorldObjectDraw(curObj);
    }

    worldGfxWork->objectCount_2BE8 = 0;
}

void Gfx_WorldObjectDraw(s_WorldObject* obj) // 0x8003CBA4
{
    GsCOORDINATE2 coord;
    SVECTOR       rot; // Q3_12
    MATRIX        mats[2];

    coord.flg   = false;
    coord.super = NULL;

    // Set geometry position.
    coord.coord.t[0] = obj->positionX_4;
    coord.coord.t[1] = obj->positionY_4;
    coord.coord.t[2] = obj->positionZ_8;

    // Compute world rotation.
    rot.vx = Q10_TO_Q12(obj->rotationX_C);
    rot.vy = obj->rotationY_C;
    rot.vz = Q10_TO_Q12(obj->rotationZ_C);

    Math_RotMatrixZxyNeg(&rot, &coord.coord);
    func_80049B6C(&coord, &mats[1], &mats[0]);
    func_8003CC7C(obj->model_0, &mats[0], &mats[1]);
}

void func_8003CC7C(s_WorldObjectModel* arg0, MATRIX* arg1, MATRIX* arg2) // 0x8003CC7C
{
    s8                     lmIdx;
    s_WorldObjectMetadata* objMetaCpy;
    s_ModelHeader*         modelHdr;

    lmIdx = arg0->metadata_10.lmIdx_9;
    if (lmIdx == 0)
    {
        return;
    }

    modelHdr   = arg0->modelInfo_0.modelHdr_8;
    objMetaCpy = &arg0->metadata_10;

    if (lmIdx >= 3 && lmIdx < 7)
    {
        if (!IpdHeader_IsLoaded(lmIdx - 3))
        {
            arg0->metadata_10.lmIdx_9 = 0;
        }
    }

    if (COMPARE_FILENAMES(&objMetaCpy->name_0, &modelHdr->name_0))
    {
        arg0->metadata_10.lmIdx_9 = 0;
        return;
    }

    func_80057090(&arg0->modelInfo_0, &g_OrderingTable0[g_ActiveBufferIdx], 1, arg1, arg2, 0);
}

// ========================================
// HELD ITEM DRAW
// ========================================

s32 WorldGfx_HeldItemIdGet(void) // 0x8003CD5C
{
    return g_WorldGfx.heldItem_1BAC.itemId_0;
}

s32 WorldGfx_PlayerPrevHeldItem(s_PlayerCombat* combat) // 0x8003CD6C
{
    s32 itemId;
    s8  weaponAttack;

    weaponAttack = combat->weaponAttack_F;
    itemId       = NO_VALUE;
    if (weaponAttack != NO_VALUE)
    {
        itemId = weaponAttack + InventoryItemId_KitchenKnife;
    }

    return WorldGfx_PlayerHeldItemSet(itemId);
}

s32 WorldGfx_PlayerHeldItemSet(e_InventoryItemId itemId) // 0x8003CDA0
{
    s32         fileIdx;
    s_HeldItem* heldItem;

    // Check if requested item is already being held.
    heldItem = &g_WorldGfx.heldItem_1BAC;
    if (heldItem->itemId_0 == itemId)
    {
        return 0;
    }

    // Define texture files to load.
    heldItem->itemId_0 = itemId;
    switch (itemId)
    {
        default:
            fileIdx = NO_VALUE;
            break;

        case NO_VALUE:
        case InventoryItemId_KitchenKnife:
        case InventoryItemId_Hammer:
        case InventoryItemId_Axe:
        case InventoryItemId_Handgun:
        case InventoryItemId_HuntingRifle:
        case InventoryItemId_Shotgun:
            fileIdx                 = NO_VALUE;
            heldItem->textureName_8 = "HERO";
            break;

        case InventoryItemId_SteelPipe:
            fileIdx                 = FILE_ITEM_PIPE_TIM;
            heldItem->textureName_8 = "PIPE";
            break;

        case InventoryItemId_CutscenePhone:
            fileIdx                 = FILE_ITEM_PHONE_TIM;
            heldItem->textureName_8 = "PHONE";
            break;

        case InventoryItemId_CutsceneFlauros:
            fileIdx                 = FILE_ITEM_FLAUROS_TIM;
            heldItem->textureName_8 = "FLAUROS";
            break;

        case InventoryItemId_CutsceneAglaophotis:
            fileIdx                 = FILE_ITEM_AGLA_TIM;
            heldItem->textureName_8 = "AGLA";
            break;

        case InventoryItemId_CutscenePlasticBottle:
            fileIdx                 = FILE_ITEM_BOTL_TIM;
            heldItem->textureName_8 = "BOTL";
            break;

        case InventoryItemId_CutsceneBaby:
            fileIdx                 = FILE_ITEM_BABY_TIM;
            heldItem->textureName_8 = "BABY";
            break;

        case InventoryItemId_CutsceneBloodPack:
            fileIdx                 = FILE_ITEM_BLOOD_TIM;
            heldItem->textureName_8 = "BLOOD";
            break;

        case InventoryItemId_Chainsaw:
            fileIdx                 = FILE_ITEM_CSAW_TIM;
            heldItem->textureName_8 = "CSAW";
            break;

        case InventoryItemId_HyperBlaster:
            fileIdx                 = FILE_ITEM_HPRGUN_TIM;
            heldItem->textureName_8 = "HPRGUN";
            break;

        case InventoryItemId_RockDrill:
            fileIdx                 = FILE_ITEM_DRILL_TIM;
            heldItem->textureName_8 = "DRILL";
            break;

        case InventoryItemId_Katana:
            fileIdx                 = FILE_ITEM_KATANA_TIM;
            heldItem->textureName_8 = "KATANA";
            break;
    }

    // Set texture UVs.
    if (fileIdx == NO_VALUE)
    {
        heldItem->imageDesc_C.tPage[1] = 27;
        heldItem->imageDesc_C.tPage[0] = 0;
        heldItem->imageDesc_C.u        = 0;
        heldItem->imageDesc_C.v        = 0;
        heldItem->imageDesc_C.clutX    = 736;
        heldItem->imageDesc_C.clutY    = 480;
    }
    else
    {
        heldItem->imageDesc_C.tPage[1] = 27;
        heldItem->imageDesc_C.tPage[0] = 0;
        heldItem->imageDesc_C.u        = 48;
        heldItem->imageDesc_C.v        = 224;
        heldItem->imageDesc_C.clutX    = 736;
        heldItem->imageDesc_C.clutY    = 498;
    }

    // Load texture.
    if (fileIdx != NO_VALUE)
    {
        heldItem->queueIdx_4 = Fs_QueueStartReadTim(fileIdx, FS_BUFFER_10, &heldItem->imageDesc_C);
    }

    // Define index of model file to lead.
    switch (itemId)
    {
        case NO_VALUE:
        default:
            fileIdx = NO_VALUE;
            break;

        case InventoryItemId_KitchenKnife:
            fileIdx = FILE_ITEM_KNIFE_PLM;
            break;

        case InventoryItemId_SteelPipe:
            fileIdx = FILE_ITEM_PIPE_PLM;
            break;

        case InventoryItemId_Hammer:
            fileIdx = FILE_ITEM_HAMMER_PLM;
            break;

        case InventoryItemId_Axe:
            fileIdx = FILE_ITEM_AXE_PLM;
            break;

        case InventoryItemId_Handgun:
            fileIdx = FILE_ITEM_HANDGUN_PLM;
            break;

        case InventoryItemId_HuntingRifle:
            fileIdx = FILE_ITEM_RIFLE_PLM;
            break;

        case InventoryItemId_Shotgun:
            fileIdx = FILE_ITEM_SHOTGUN_PLM;
            break;

        case InventoryItemId_CutscenePhone:
            fileIdx = FILE_ITEM_PHONE_PLM;
            break;

        case InventoryItemId_CutsceneFlauros:
            fileIdx = FILE_ITEM_FLAUROS_PLM;
            break;

        case InventoryItemId_CutsceneAglaophotis:
            fileIdx = FILE_ITEM_AGLA_PLM;
            break;

        case InventoryItemId_CutscenePlasticBottle:
            fileIdx = FILE_ITEM_BOTL_PLM;
            break;

        case InventoryItemId_CutsceneBaby:
            fileIdx = FILE_ITEM_BABY_PLM;
            break;

        case InventoryItemId_CutsceneBloodPack:
            fileIdx = FILE_ITEM_BLOOD_PLM;
            break;

        case InventoryItemId_Chainsaw:
            fileIdx = FILE_ITEM_CSAW_PLM;
            break;

        case InventoryItemId_HyperBlaster:
            fileIdx = FILE_ITEM_HPRGUN_PLM;
            break;

        case InventoryItemId_RockDrill:
            fileIdx = FILE_ITEM_DRILL_PLM;
            break;

        case InventoryItemId_Katana:
            fileIdx = FILE_ITEM_KATANA_PLM;
            break;
    }

    // Load model.
    if (fileIdx != NO_VALUE)
    {
        heldItem->queueIdx_4 = Fs_QueueStartRead(fileIdx, heldItem->lmHdr_14);
        return heldItem->queueIdx_4;
    }

    return 0;
}

void func_8003D01C(void) // 0x8003D01C
{
    g_WorldGfx.heldItem_1BAC.bone_18.modelInfo_0.field_0 &= ~(1 << 31);
}

void func_8003D03C(void) // 0x8003D03C
{
    g_WorldGfx.heldItem_1BAC.bone_18.modelInfo_0.field_0 |= 1 << 31;
}

void WorldGfx_HeldItemDraw(void) // 0x8003D058
{
    MATRIX         mat0;
    MATRIX         mat1;
    GsCOORDINATE2* coord;
    s_HeldItem*    heldItem;
    s_LmHeader*    lmHdr;

    // Check if held item is valid.
    heldItem = &g_WorldGfx.heldItem_1BAC;
    if (heldItem->itemId_0 == NO_VALUE)
    {
        return;
    }

    // Distinguish between left-handed and right-handed items.
    if (heldItem->itemId_0 == InventoryItemId_CutscenePhone)
    {
        coord = &g_SysWork.playerBoneCoords_890[HarryBone_LeftHand];
    }
    else
    {
        coord = &g_SysWork.playerBoneCoords_890[HarryBone_RightHand];
    }

    if (Fs_QueueIsEntryLoaded(heldItem->queueIdx_4))
    {
        lmHdr = heldItem->lmHdr_14;
        if (!lmHdr->isLoaded_2)
        {
            LmHeader_FixOffsets(lmHdr);
            Lm_MaterialFsImageApply1(lmHdr, heldItem->textureName_8, &heldItem->imageDesc_C, BlendMode_Additive);
            Lm_MaterialFlagsApply(lmHdr);
            Bone_ModelAssign(&heldItem->bone_18, heldItem->lmHdr_14, 0);
        }

        func_80049B6C(coord, &mat1, &mat0);
        func_80057090(&heldItem->bone_18.modelInfo_0, &g_OrderingTable0[g_ActiveBufferIdx], 1, &mat0, &mat1, 0);
    }
}

// ========================================
// CHARACTER LOAD AND DRAW
// ========================================

void WorldGfx_HarryCharaLoad(void) // 0x8003D160
{
    s_FsImageDesc   image;
    s32             queueIdx;
    s_WorldGfxWork* worldGfxWork;
    s_CharaModel*   harryModel;
    s_LmHeader*     harryLmHdr;

    harryLmHdr = HARRY_LM_BUFFER;

    Chara_FsImageCalc(&image, Chara_Harry, 0);

    worldGfxWork                                     = &g_WorldGfx;
    harryModel                                       = &worldGfxWork->harryModel_164C;
    g_WorldGfx.registeredCharaModels_18[Chara_Harry] = harryModel;

    Fs_QueueStartRead(CHARA_FILE_INFOS[Chara_Harry].modelFileIdx, harryLmHdr);
    queueIdx = Fs_QueueStartReadTim(CHARA_FILE_INFOS[Chara_Harry].textureFileIdx, FS_BUFFER_1, &image);

    g_WorldGfx.harryModel_164C.charaId_0 = Chara_Harry;
    harryModel->isLoaded_1               = false;
    harryModel->queueIdx_4               = queueIdx;
    harryModel->lmHdr_8                  = harryLmHdr;
    g_WorldGfx.harryModel_164C.texture_C = image;
}

s32 WorldGfx_MapInitCharaLoad(s_MapOverlayHeader* mapHdr) // 0x8003D21C
{
    s_FsImageDesc image;
    bool          cond;
    s32           i;
    s32           j;
    s32           queueIdx;
    s32           curCharaId;
    s_CharaModel* curModel;

    for (queueIdx = 0, i = 0, g_WorldGfx.charaLmBuffer_14 = MAP_CHARA_LM_BUFFER, cond = false;
         i < GROUP_CHARA_COUNT;
         i++)
    {
        curCharaId = mapHdr->charaGroupIds_248[i];
        curModel   = &g_WorldGfx.charaModels_CC[i];

        if (curCharaId != Chara_None)
        {
            if (!cond)
            {
                if (curCharaId != curModel->charaId_0)
                {
                    cond = true;
                    for (j = i; j < ARRAY_SIZE(g_WorldGfx.charaModels_CC); j++)
                    {
                        g_WorldGfx.charaModels_CC[j].charaId_0 = Chara_None;
                    }
                }
            }

            if (cond)
            {
                Chara_FsImageCalc(&image, curCharaId, i);
                queueIdx = WorldGfx_CharaModelLoad(curCharaId, i, (s_LmHeader*)g_WorldGfx.charaLmBuffer_14, &image);
            }

            WorldGfx_CharaLmBufferAdvance(&g_WorldGfx.charaLmBuffer_14, curCharaId);
        }
    }

    return queueIdx;
}

void WorldGfx_CharaLmBufferAdvance(u8** buf, e_CharacterId charaId) // 0x8003D354
{
    s16 modelFileIdx;
    s32 fileSize;

    modelFileIdx = CHARA_FILE_INFOS[charaId].modelFileIdx;
    fileSize     = Fs_GetFileSize(modelFileIdx);

    Fs_GetFileSectorAlignedSize(modelFileIdx);
    *buf += (fileSize + 3) & ~0x3;
}

void Chara_FsImageCalc(s_FsImageDesc* image, s32 charaId, s32 modelIdx) // 0x8003D3BC
{
    s16 clutX;
    s16 clutY;
    s8  tPage;
    s8  v;
    s8  u;

    // TODO: Deoptimise.
    v = charaId < Chara_AirScreamer;
    if (charaId >= Chara_None && v)
    {
        tPage = 27;
        v     = 0;
        u     = 0;
        clutX = 736;
        clutY = 480;
    }
    else
    {
        clutY = 464;
        clutX = (modelIdx * 16) + 704;

        switch (modelIdx)
        {
            default:
                modelIdx = 0;

            case 0:
            case 1:
                tPage = 28;
                u     = 0;
                v     = modelIdx << 7;
                break;

            case 2:
            case 3:
                tPage = 29;
                u     = 0;
                v     = (modelIdx - 2) << 7;
                break;
        }
    }

    image->tPage[0] = 0;
    image->tPage[1] = tPage;
    image->u        = u;
    image->v        = v;
    image->clutX    = clutX;
    image->clutY    = clutY;
}

bool WorldGfx_IsCharaModelPresent(e_CharacterId charaId) // 0x8003D444
{
    return g_WorldGfx.registeredCharaModels_18[charaId] != NULL;
}

void func_8003D460(void) {} // 0x8003D460

void WorldGfx_CharaModelTransparentSet(e_CharacterId charaId, bool enableTransparency) // 0x8003D468
{
    s16           data[256];
    RECT          rect;
    s32           x;
    s32           i;
    s32           y;
    s_CharaModel* model;

    model = g_WorldGfx.registeredCharaModels_18[charaId];
    Lm_TransparentPrimSet(model->lmHdr_8, enableTransparency);

    rect.x = model->texture_C.clutX;
    rect.y = model->texture_C.clutY;
    rect.w = 16;
    rect.h = 16;

    DrawSync(SyncMode_Wait);
    StoreImage(&rect, &data);

    for (y = 0, i = 0; y < 16; y++)
    {
        for (x = 0; x < 16; x++, i++)
        {
            if (!enableTransparency)
            {
                data[i] &= SHRT_MAX;
            }
            else
            {
                data[i] |= 1 << 15;
            }
        }
    }

    LoadImage(&rect, &data);
}

void WorldGfx_CharaModelMaterialSet(s32 charaId, s32 blendMode) // 0x8003D550
{
    s_CharaModel* model;

    model = g_WorldGfx.registeredCharaModels_18[charaId];
    Lm_MaterialFileIdxApply(model->lmHdr_8, CHARA_FILE_INFOS[charaId].textureFileIdx, &model->texture_C, blendMode);
    Lm_MaterialFlagsApply(model->lmHdr_8);
}

void WorldGfx_CharaLmBufferAssign(s8 forceFree) // 0x8003D5B4
{
    u8            charaId;
    s32           i;
    u32           lmData;
    s_CharaModel* curModel;

    for (i = 0; i < ARRAY_SIZE(g_WorldGfx.charaModels_CC); i++)
    {
        curModel = &g_WorldGfx.charaModels_CC[i];
        if ((forceFree >> i) & (1 << 0))
        {
            WorldGfx_CharaFree(curModel);
        }
    }

    i = 0;
    g_WorldGfx.charaLmBuffer_14 = MAP_CHARA_LM_BUFFER;
    for (; i < ARRAY_SIZE(g_WorldGfx.charaModels_CC); i++)
    {
        curModel = &g_WorldGfx.charaModels_CC[i];

        charaId = curModel->charaId_0;
        if (charaId != Chara_None)
        {
            lmData = (s32)curModel->lmHdr_8 + Fs_GetFileSize(CHARA_FILE_INFOS[charaId].modelFileIdx);
            if (g_WorldGfx.charaLmBuffer_14 < lmData)
            {
                g_WorldGfx.charaLmBuffer_14 = lmData;
            }
        }
    }
}

void WorldGfx_CharaFree(s_CharaModel* model) // 0x8003D6A4
{
    if (model->charaId_0 != Chara_None)
    {
        g_WorldGfx.registeredCharaModels_18[model->charaId_0] = NULL;
        CharaModel_Free(model);
    }
}

void WorldGfx_CharaLoad(e_CharacterId charaId, s32 modeIdx, s_LmHeader* lmHdr, s_FsImageDesc* tex) // 0x8003D6E0
{
    s_FsImageDesc image;
    s_LmHeader*   lmHdrBuf;

    // Set LM header.
    if (lmHdr != NULL)
    {
        lmHdrBuf = lmHdr;
    }
    else if (g_WorldGfx.charaModels_CC[modeIdx].charaId_0 != Chara_None)
    {
        lmHdrBuf = g_WorldGfx.charaModels_CC[modeIdx].lmHdr_8;
    }
    else
    {
        lmHdrBuf = (s_LmHeader*)g_WorldGfx.charaLmBuffer_14;
        WorldGfx_CharaLmBufferAdvance(&g_WorldGfx.charaLmBuffer_14, charaId);
    }

    // Set texture UVs.
    if (tex != NULL)
    {
        image = *tex;
    }
    else
    {
        Chara_FsImageCalc(&image, charaId, modeIdx);
    }

    WorldGfx_CharaModelLoad(charaId, modeIdx, lmHdrBuf, &image);
}

s32 WorldGfx_CharaModelLoad(e_CharacterId charaId, s32 modelIdx, s_LmHeader* lmHdr, s_FsImageDesc* tex) // 0x8003D7D4
{
    s32            queueIdx;
    s32            modelCharaId; // `e_CharacterId`
    s_CharaModel*  model;
    s_FsImageDesc* modelTex;

    model        = &g_WorldGfx.charaModels_CC[modelIdx];
    modelCharaId = model->charaId_0;
    modelTex     = &model->texture_C;

    // If character is invalid, set model as unused.
    if (charaId == Chara_None)
    {
        g_WorldGfx.registeredCharaModels_18[modelCharaId] = NULL;
        return 0;
    }

    // Register character model.
    if (modelCharaId != Chara_None)
    {
        if (charaId == modelCharaId)
        {
            if (lmHdr == model->lmHdr_8 && memcmp(tex, modelTex, sizeof(s_FsImageDesc)) == 0)
            {
                return 0;
            }
        }

        g_WorldGfx.registeredCharaModels_18[modelCharaId] = NULL;
    }
    g_WorldGfx.registeredCharaModels_18[charaId] = model;

    // Load model and texture files.
    queueIdx = Fs_QueueStartRead(CHARA_FILE_INFOS[charaId].modelFileIdx, lmHdr);
    if (CHARA_FILE_INFOS[charaId].textureFileIdx != NO_VALUE)
    {
        queueIdx = Fs_QueueStartReadTim(CHARA_FILE_INFOS[charaId].textureFileIdx, FS_BUFFER_1, tex);
    }

    // Set loaded model data.
    model->charaId_0  = charaId;
    model->isLoaded_1 = false;
    model->queueIdx_4 = queueIdx;
    model->lmHdr_8    = lmHdr;
    model->texture_C  = *tex;
    return queueIdx;
}

void WorldGfx_PlayerModelProcessLoad(void) // 0x8003D938
{
    WorldGfx_CharaModelProcessLoad(&g_WorldGfx.harryModel_164C);
}

void WorldGfx_CharaModelProcessAllLoads(void) // 0x8003D95C
{
    s32           i;
    s_CharaModel* model;

    for (i = 0; i < Chara_Count; i++)
    {
        if (i != Chara_Harry)
        {
            model = g_WorldGfx.registeredCharaModels_18[i];
            if (model != NULL)
            {
                WorldGfx_CharaModelProcessLoad(model);
            }
        }
    }
}

void WorldGfx_CharaModelProcessLoad(s_CharaModel* model) // 0x8003D9C8
{
    s_Skeleton* skel;

    if (!model->isLoaded_1 && model->charaId_0 != Chara_None && Fs_QueueIsEntryLoaded(model->queueIdx_4))
    {
        model->isLoaded_1 = true;

        LmHeader_FixOffsets(model->lmHdr_8);
        Lm_MaterialFileIdxApply(model->lmHdr_8, CHARA_FILE_INFOS[model->charaId_0].textureFileIdx, &model->texture_C, CHARA_FILE_INFOS[model->charaId_0].materialBlendMode_6_10 % 4);

        skel = &model->skeleton_14;

        Lm_MaterialFlagsApply(model->lmHdr_8);
        Skeleton_Init(skel, model->skeleton_14.bones_C, 56);
        func_8004506C(skel, model->lmHdr_8);
        func_800452EC(skel);
        func_800453E8(skel, true);
    }
}

void func_8003DA9C(e_CharacterId charaId, GsCOORDINATE2* coord, s32 arg2, q3_12 timer, s32 arg4) // 0x8003DA9C
{
    CVECTOR tintColor = { 0 };
    s16     ret;

    // Check if character is valid.
    if (charaId == Chara_None)
    {
        return;
    }

    timer = CLAMP(timer, Q12(0.0f), Q12(1.0f));

    // Something to do with items held by player.
    if (charaId == Chara_Harry)
    {
        WorldGfx_HeldItemDraw();
    }

    ret = func_8003DD74(charaId, arg4);

    if (timer != Q12(0.0f))
    {
        tintColor = g_WorldEnvWork.worldTintColor_28;

        func_80055330(g_WorldEnvWork.field_0, g_WorldEnvWork.field_20, g_WorldEnvWork.field_3,
                      Q12_MULT_PRECISE(Q12(1.0f) - timer, g_WorldEnvWork.worldTintColor_28.r) << 5,
                      Q12_MULT_PRECISE(Q12(1.0f) - timer, g_WorldEnvWork.worldTintColor_28.g) << 5,
                      Q12_MULT_PRECISE(Q12(1.0f) - timer, g_WorldEnvWork.worldTintColor_28.b) << 5,
                      g_WorldEnvWork.screenBrightness_8);
    }

    func_80045534(&g_WorldGfx.registeredCharaModels_18[charaId]->skeleton_14, &g_OrderingTable0[g_ActiveBufferIdx], arg2,
                  coord, Q8_TO_Q12(CHARA_FILE_INFOS[charaId].field_6), ret, CHARA_FILE_INFOS[charaId].field_8);

    if (timer != Q12(0.0f))
    {
        func_80055330(g_WorldEnvWork.field_0, g_WorldEnvWork.field_20, g_WorldEnvWork.field_3, tintColor.r << 5, tintColor.g << 5, tintColor.b << 5, g_WorldEnvWork.screenBrightness_8);
    }
}

s32 func_8003DD74(e_CharacterId charaId, s32 arg1) // 0x8003DD74
{
    return ((s32)arg1 << 10) & 0xFC00;
}

// ========================================
// ITEM ATTACHMENT
// ========================================

void WorldGfx_HeldItemAttach(e_CharacterId charaId, s32 arg1) // 0x8003DD80
{
    s_CharaModel* model;

    model = g_WorldGfx.registeredCharaModels_18[charaId];

    switch (charaId)
    {
        case Chara_Harry:
            func_8003DE60(&model->skeleton_14, arg1);
            break;

        case Chara_Stalker:
            func_8003E388(&model->skeleton_14, arg1);
            break;

        case Chara_Cybil:
        case Chara_EndingCybil:
            func_8003DF84(&model->skeleton_14, arg1);
            break;

        case Chara_MonsterCybil:
            func_8003E08C(&model->skeleton_14, arg1);
            break;

        case Chara_Dahlia:
        case Chara_EndingDahlia:
            func_8003E194(&model->skeleton_14, arg1);
            break;

        case Chara_Kaufmann:
        case Chara_EndingKaufmann:
            func_8003E238(&model->skeleton_14, arg1);
            break;

        case Chara_SplitHead:
            func_8003E414(&model->skeleton_14, arg1);
            break;

        case Chara_PuppetNurse:
            func_8003E4A0(&model->skeleton_14, arg1);
            break;

        case Chara_PuppetDoctor:
            func_8003E544(&model->skeleton_14, arg1);
            break;
    }
}

void func_8003DE60(s_Skeleton* skel, s32 arg1) // 0x8003DE60
{
    s32 idx;

    static s32 D_800A9ECC = 0xFE16FD13;
    static s32 D_800A9ED0 = 0x0000FE13;
    static s32 D_800A9ED4 = 0x0000FE14;
    static s32 D_800A9ED8 = 0x0000FE15;
    static s32 D_800A9EDC = 0x0000FE16;
    static s32 D_800A9EE0 = 0x000000FE;
    static s32 D_800A9EE4 = 0x00FE1211;
    static s32 D_800A9EE8 = 0x0000FE11;
    static s32 D_800A9EEC = 0x0000FE12;

    // Process first masked value.
    idx = MODEL_BONE_IDX_0_GET(arg1);
    if (idx != 0)
    {
        func_80045468(skel, &D_800A9ECC, false);

        switch (idx)
        {
            case 1:
                func_80045468(skel, &D_800A9ED0, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9ED4, true);
                break;

            case 3:
                func_80045468(skel, &D_800A9ED8, true);
                break;

            case 4:
                func_80045468(skel, &D_800A9EDC, true);
                break;

            case 5:
                func_80045468(skel, &D_800A9EE0, true);
                break;
        }
    }

    // Process second masked value.
    idx = MODEL_BONE_IDX_1_GET(arg1);
    if (idx != 0)
    {
        func_80045468(skel, &D_800A9EE4, false);

        switch (idx)
        {
            case 1 << 4:
                func_80045468(skel, &D_800A9EE8, true);
                break;

            case 2 << 4:
                func_80045468(skel, &D_800A9EEC, true);
                break;
        }
    }
}

static const s32 pad_rodata_80025BB0 = 0;

void func_8003DF84(s_Skeleton* skel, s32 arg1) // 0x8003DF84
{
    s32 idx;

    static s32 D_800A9EF0 = 0x0000FE14;
    static s32 D_800A9EF4 = 0x00FE1514;
    static s32 D_800A9EF8 = 0x0000FE12;
    static s32 D_800A9EFC = 0x00FE1312;

    idx = MODEL_BONE_IDX_0_GET(arg1);
    if (idx != 0)
    {
        switch (idx)
        {
            case 1:
                func_80045468(skel, &D_800A9EF4, false);
                func_80045468(skel, &D_800A9EF0, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9EF0, false);
                func_80045468(skel, &D_800A9EF4, true);
                break;
        }
    }

    idx = MODEL_BONE_IDX_1_GET(arg1);
    if (idx != 0)
    {
        switch (idx)
        {
            case 1 << 4:
                func_80045468(skel, &D_800A9EFC, false);
                func_80045468(skel, &D_800A9EF8, true);
                break;

            case 2 << 4:
                func_80045468(skel, &D_800A9EF8, false);
                func_80045468(skel, &D_800A9EFC, true);
                break;
        }
    }
}

void func_8003E08C(s_Skeleton* skel, s32 arg1) // 0x8003E08C
{
    s32 maskedVal;

    static s32 D_800A9F00 = 0x0000FE02;
    static s32 D_800A9F04 = 0x0000FE03;
    static s32 D_800A9F08 = 0x0000FE00;
    static s32 D_800A9F0C = 0x00FE0100;

    maskedVal = MODEL_BONE_IDX_0_GET(arg1);
    if (maskedVal != 0)
    {
        switch (maskedVal)
        {
            case 1:
                func_80045468(skel, &D_800A9F04, false);
                func_80045468(skel, &D_800A9F00, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9F00, false);
                func_80045468(skel, &D_800A9F04, true);
                break;
        }
    }

    maskedVal = MODEL_BONE_IDX_1_GET(arg1);
    if (maskedVal != 0)
    {
        switch (maskedVal)
        {
            case 1 << 4:
                func_80045468(skel, &D_800A9F0C, false);
                func_80045468(skel, &D_800A9F08, true);
                break;

            case 2 << 4:
                func_80045468(skel, &D_800A9F08, false);
                func_80045468(skel, &D_800A9F0C, true);
                break;
        }
    }
}

void func_8003E194(s_Skeleton* skel, s32 arg1) // 0x8003E194
{
    s32 maskedVal;

    static s32 D_800A9F10 = 0xFE03FD00;
    static s32 D_800A9F14 = 0x0000FE00;
    static s32 D_800A9F18 = 0x00FE0201;
    static s32 D_800A9F1C = 0x0000FE03;

    maskedVal = MODEL_BONE_IDX_0_GET(arg1);
    if (maskedVal != 0)
    {
        func_80045468(skel, &D_800A9F10, false);

        switch (maskedVal)
        {
            case 1:
                func_80045468(skel, &D_800A9F14, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9F18, true);
                break;

            case 3:
                func_80045468(skel, &D_800A9F1C, true);
                break;
        }
    }
}

void func_8003E238(s_Skeleton* skel, s32 arg1) // 0x8003E238
{
    s32 maskedVal;

    static s32 D_800A9F20 = 0x06050403;
    static s32 D_800A9F24 = 0x000000FE; // @unused
    static s32 D_800A9F28 = 0x0000FE03;
    static s32 D_800A9F2C = 0x0000FE04;
    static s32 D_800A9F30 = 0x00FE0504;
    static s32 D_800A9F34 = 0x00FE0603;
    static s32 D_800A9F38 = 0xFE020100;
    static s32 D_800A9F3C = 0x0000FE00;
    static s32 D_800A9F40 = 0x0000FE01;
    static s32 D_800A9F44 = 0x00FE0201;

    maskedVal = MODEL_BONE_IDX_0_GET(arg1);
    if (maskedVal != 0)
    {
        func_80045468(skel, &D_800A9F20, false);

        switch (maskedVal)
        {
            case 1:
                func_80045468(skel, &D_800A9F28, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9F2C, true);
                break;

            case 3:
                func_80045468(skel, &D_800A9F30, true);
                break;

            case 4:
                func_80045468(skel, &D_800A9F34, true);
                break;
        }
    }


    maskedVal = MODEL_BONE_IDX_1_GET(arg1);
    if (maskedVal != 0)
    {
        func_80045468(skel, &D_800A9F38, false);

        switch (maskedVal)
        {
            case 1 << 4:
                func_80045468(skel, &D_800A9F3C, true);
                break;

            case 2 << 4:
                func_80045468(skel, &D_800A9F40, true);
                break;

            case 3 << 4:
                func_80045468(skel, &D_800A9F44, true);
                break;
        }
    }
}

void func_8003E388(s_Skeleton* skel, s32 arg1) // 0x8003E388
{
    s32 maskedVal;

    static s32 D_800A9F48 = 0x0000FE05;
    static s32 D_800A9F4C = 0x0000FE06;

    maskedVal = MODEL_BONE_IDX_0_GET(arg1);
    if (maskedVal != 0)
    {
        switch (maskedVal)
        {
            case 1:
                func_80045468(skel, &D_800A9F4C, false);
                func_80045468(skel, &D_800A9F48, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9F48, false);
                func_80045468(skel, &D_800A9F4C, true);
                break;
        }
    }
}

void func_8003E414(s_Skeleton* skel, s32 arg1) // 0x8003E414
{
    s32 maskedVal;

    static s32 D_800A9F50 = 0xFE19FD11;
    static s32 D_800A9F54 = 0xFE22FD1A;

    maskedVal = arg1 & 0x3;
    if (maskedVal == 0)
    {
        return;
    }

    switch (maskedVal)
    {
        case 1:
            func_80045468(skel, &D_800A9F50, false);
            func_80045468(skel, &D_800A9F54, true);
            break;

        case 2:
            func_80045468(skel, &D_800A9F54, false);
            func_80045468(skel, &D_800A9F50, true);
            break;
    }
}

void func_8003E4A0(s_Skeleton* skel, s32 arg1) // 0x8003E4A0
{
    s32 maskedVal;

    static s32 D_800A9F58 = 0x05040302;
    static s32 D_800A9F5C = 0x00FE0706; // @unused
    static s32 D_800A9F60 = 0x00FE0502;
    static s32 D_800A9F64 = 0x00FE0603;
    static s32 D_800A9F68 = 0x00FE0704;

    maskedVal = MODEL_BONE_IDX_0_GET(arg1);
    if (maskedVal != 0)
    {
        func_80045468(skel, &D_800A9F58, false);

        switch (maskedVal)
        {
            case 1:
                func_80045468(skel, &D_800A9F60, true);
                break;

            case 2:
                func_80045468(skel, &D_800A9F64, true);
                break;

            case 3:
                func_80045468(skel, &D_800A9F68, true);
                break;
        }
    }
}

void func_8003E544(s_Skeleton* skel, s32 arg1) // 0x8003E544
{
    s32 maskedVal;

    static s32 D_800A9F6C = 0x05040302;
    static s32 D_800A9F70 = 0x00FE0706; // @unused
    static s32 D_800A9F74 = 0x00FE0502;
    static s32 D_800A9F78 = 0x00FE0603;
    static s32 D_800A9F7C = 0x00FE0704;

    maskedVal = MODEL_BONE_IDX_0_GET(arg1);
    if (maskedVal == 0)
    {
        return;
    }

    func_80045468(skel, &D_800A9F6C, false);

    switch (maskedVal)
    {
        case 1:
            func_80045468(skel, &D_800A9F74, true);
            break;

        case 2:
            func_80045468(skel, &D_800A9F78, true);
            break;

        case 3:
            func_80045468(skel, &D_800A9F7C, true);
            break;
    }
}
