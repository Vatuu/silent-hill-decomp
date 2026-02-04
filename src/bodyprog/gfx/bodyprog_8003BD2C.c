#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/memcard.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/gfx/text_draw.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

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
    SVECTOR         ang;
    s32             temp_a1;
    s32             temp_a2;
    s32             moveAmt;
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
        vwGetViewAngle(&ang);

        flagsCpy = g_WorldGfx.mapInfo_0->flags_6;
        if (!(flagsCpy & MapFlag_Interior) || !(flagsCpy & (MapFlag_OneActiveChunk | MapFlag_TwoActiveChunks)))
        {
            var_s1 = Q12_MULT(Math_Cos(ang.vx), Q12(9.0f));
        }
        else
        {
            var_s1 = Q12(0.0f);
        }
        
        temp_s0_2 = Q12_MULT(var_s1, Math_Sin(ang.vy));
        temp_s0_2 = CLAMP(temp_s0_2, Q12(-6.0f), Q12(6.0f));

        temp_v1_4 = Q12_MULT(var_s1, Math_Cos(ang.vy));
        temp_v1_4 = CLAMP(temp_v1_4, Q12(-6.0f), Q12(6.0f));

        pos1.vx += temp_s0_2;
        pos1.vz += temp_v1_4;

        if (Vc_VectorMagnitudeCalc(pos1.vx - chara->position_18.vx, 0, pos1.vz - chara->position_18.vz) > 0x10000)
        {
            var_s1  = Q12(14.0f);
            pos1.vx = chara->position_18.vx + Q12_MULT(Math_Sin(ang.vy), var_s1);
            pos1.vz = chara->position_18.vz + Q12_MULT(Math_Cos(ang.vy), var_s1);
        }
    }
    else
    {
        pos1     = chara->position_18;
        pos1.vx += FP_FROM(FP_TO(Math_Sin(chara->rotation_24.vy), Q12_SHIFT), Q12_SHIFT);
        pos1.vz += FP_FROM(FP_TO(Math_Cos(chara->rotation_24.vy), Q12_SHIFT), Q12_SHIFT);
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

void func_8003DA9C(e_CharacterId charaId, GsCOORDINATE2* coord, s32 arg2, s16 arg3, s32 arg4) // 0x8003DA9C
{
    CVECTOR tintColor = { 0 };
    s16     ret;

    // Check if character is valid.
    if (charaId == Chara_None)
    {
        return;
    }

    arg3 = CLAMP(arg3, Q12(0.0f), Q12(1.0f));

    // Something to do with items held by player.
    if (charaId == Chara_Harry)
    {
        WorldGfx_HeldItemDraw();
    }

    ret = func_8003DD74(charaId, arg4);

    if (arg3 != 0)
    {
        tintColor = g_WorldEnvWork.worldTintColor_28;

        func_80055330(g_WorldEnvWork.field_0, g_WorldEnvWork.field_20, g_WorldEnvWork.field_3,
                      Q12_MULT_PRECISE(Q12(1.0f) - arg3, g_WorldEnvWork.worldTintColor_28.r) << 5,
                      Q12_MULT_PRECISE(Q12(1.0f) - arg3, g_WorldEnvWork.worldTintColor_28.g) << 5,
                      Q12_MULT_PRECISE(Q12(1.0f) - arg3, g_WorldEnvWork.worldTintColor_28.b) << 5,
                      g_WorldEnvWork.screenBrightness_8);
    }

    func_80045534(&g_WorldGfx.registeredCharaModels_18[charaId]->skeleton_14, &g_OrderingTable0[g_ActiveBufferIdx], arg2,
                  coord, Q8_TO_Q12(CHARA_FILE_INFOS[charaId].field_6), ret, CHARA_FILE_INFOS[charaId].field_8);

    if (arg3 != 0)
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
    s32 maskedVal;

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
    maskedVal = arg1 & 0xF;
    if (maskedVal != 0)
    {
        func_80045468(skel, &D_800A9ECC, false);

        switch (maskedVal)
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
    maskedVal = arg1 & 0xF0;
    if (maskedVal != 0)
    {
        func_80045468(skel, &D_800A9EE4, false);

        switch (maskedVal)
        {
            case 16:
                func_80045468(skel, &D_800A9EE8, true);
                break;

            case 32:
                func_80045468(skel, &D_800A9EEC, true);
                break;
        }
    }
}

void func_8003DF84(s_Skeleton* skel, s32 arg1) // 0x8003DF84
{
    s32 maskedVal;

    static s32 D_800A9EF0 = 0x0000FE14;
    static s32 D_800A9EF4 = 0x00FE1514;
    static s32 D_800A9EF8 = 0x0000FE12;
    static s32 D_800A9EFC = 0x00FE1312;

    maskedVal = arg1 & 0xF;
    if (maskedVal != 0)
    {
        switch (maskedVal)
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

    maskedVal = arg1 & 0xF0;
    if (maskedVal != 0)
    {
        switch (maskedVal)
        {
            case 16:
                func_80045468(skel, &D_800A9EFC, false);
                func_80045468(skel, &D_800A9EF8, true);
                break;

            case 32:
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

    maskedVal = arg1 & 0xF;
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

    maskedVal = arg1 & 0xF0;
    if (maskedVal != 0)
    {
        switch (maskedVal)
        {
            case 16:
                func_80045468(skel, &D_800A9F0C, false);
                func_80045468(skel, &D_800A9F08, true);
                break;

            case 32:
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

    maskedVal = arg1 & 0xF;
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

    maskedVal = arg1 & 0xF;
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


    maskedVal = arg1 & 0xF0;
    if (maskedVal != 0)
    {
        func_80045468(skel, &D_800A9F38, false);

        switch (maskedVal)
        {
            case 16:
                func_80045468(skel, &D_800A9F3C, true);
                break;

            case 32:
                func_80045468(skel, &D_800A9F40, true);
                break;

            case 48:
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

    maskedVal = arg1 & 0xF;
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

    maskedVal = arg1 & 0xF;
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

    maskedVal = arg1 & 0xF;
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


// ========================================
// OPTIONS
// ========================================
// Possibly the options overlay was at some point part of the engine like `SAVELOAD.BIN` was.

void Options_BrightnessMenu_LinesDraw(s32 arg0) // 0x8003E5E8
{
    s32       i;
    u8        color;
    GsOT_TAG* ot;
    PACKET*   packet;
    LINE_G2*  line;

    packet = GsOUT_PACKET_P;
    ot     = &g_OrderingTable0[g_ActiveBufferIdx].org[1];

    for (i = -10; i < 11; i++)
    {
        line = (LINE_G2*)packet;
        setLineG2(line);

        line->x1 = ((g_GameWork.gsScreenWidth_588 - 64) / 20) * i;
        line->x0 = line->x1;

        line->y0 = -16;
        line->y1 = (g_GameWork.gsScreenHeight_58A / 2) - 45;

        color = (arg0 * 8) + 4;

        line->b1 = color;
        line->g1 = color;
        line->r1 = color;

        line->b0 = color;
        line->g0 = color;
        line->r0 = color;

        AddPrim(ot, line);
        packet += sizeof(LINE_G2);
    }

    GsOUT_PACKET_P = packet;
}

// ========================================
// EFFECTS (FOG AND LIGHTING)
// ========================================

static s_MapEffectsPresetIdxs D_800A9F80 = { 1, 1  };
static s_MapEffectsPresetIdxs D_800A9F84 = { 2, 2  };
static s_MapEffectsPresetIdxs D_800A9F88 = { 6, 3  };
static s_MapEffectsPresetIdxs D_800A9F8C = { 7, 4  };
static s_MapEffectsPresetIdxs D_800A9F90 = { 6, 10 };
static s_MapEffectsPresetIdxs D_800A9F94 = { 6, 5  };
static s_MapEffectsPresetIdxs D_800A9F98 = { 9, 9  };
static s_MapEffectsPresetIdxs D_800A9F9C = { 6, 6  };
static s_MapEffectsPresetIdxs D_800A9FA0 = { 3, 3  };
static s_MapEffectsPresetIdxs D_800A9FA4 = { 5, 5  };

void GameFs_FlameGfxLoad(void) // 0x8003E710
{
    static s_FsImageDesc IMG_FLAME = {
        .tPage = { 0, 12 },
        .u     = 32,
        .v     = 0,
        .clutX = 800,
        .clutY = 64
    };

    Fs_QueueStartReadTim(FILE_TIM_FLAME_TIM, FS_BUFFER_1, &IMG_FLAME);
}

void func_8003E740(void) // 0x8003E740
{
    DVECTOR   sp10;
    MATRIX    sp18;
    SVECTOR   sp38;
    s32       sp40[4];
    SVECTOR   sp50;
    DVECTOR   sp58;
    s32       sp60;
    s32       temp_a0;
    s32       temp_s6;
    s32       i;
    s32       var_s5;
    s16*      var_a0;
    POLY_FT4* poly;
    s32       idx = 0;

    static u32 D_800A9FB0 = 0;

    if (g_DeltaTime0 != Q12(0.0f))
    {
        D_800A9FB0 += 8;
        for (i = 0; i < 8; i++)
        {
            D_800BCDE8[i] = Rng_Rand16();
        }
    }

    sp38.vx = 1;
    sp38.vy = -7;
    sp38.vz = 33;
    sp38.vx = Q12_MULT(Math_AngleNormalize(D_800BCDE8[idx++]), 5) + 1;
    sp38.vz = Q12_MULT(Math_AngleNormalize(D_800BCDE8[idx++]), 5) + 33;

    poly = (POLY_FT4*)GsOUT_PACKET_P;

    func_80049AF8(&g_SysWork.playerBoneCoords_890[HarryBone_RightHand], &sp18);
    SetRotMatrix(&sp18);
    SetTransMatrix(&sp18);

    var_s5 = RotTransPers(&sp38, &sp10, &sp60, &sp60);

    temp_s6  = var_s5 * 4;
    var_s5 >>= 1;
    var_s5  -= 2;

    if (var_s5 < 0)
    {
        var_s5 = 0;
    }

    if (temp_s6 > 128 && var_s5 < ORDERING_TABLE_SIZE - 1)
    {
        SetPolyFT4(poly);
        setSemiTrans(poly, true);

        temp_a0 = D_800BCDE8[idx++];

        if ((temp_a0 & 0xFFF) >= 3482) // TODO: `> Q12(0.85f)` also matches, but this gets used for `setRGB0` color?
        {
            D_800A9FB0 -= 16 + (temp_a0 & 0xF);
        }

        if (D_800A9FB0 >= 33)
        {
            D_800A9FB0 = 0;
        }

        setRGB0(poly, D_800A9FB0 + 48, D_800A9FB0 + 48, D_800A9FB0 + 48);
        poly->tpage = 44;
        poly->clut  = 4146;

        var_a0 = &D_800BCDE8[idx++];

        for (i = 0; i < 4; i++)
        {
            sp40[i] = (var_a0[i] & 0xF) - 8;
        }

        SetRotMatrix(&GsIDMATRIX);
        SetTransMatrix(&GsIDMATRIX);

        sp50.vz = temp_s6;
        sp50.vx = sp40[0] - 51;
        sp50.vy = sp40[2] - 51;

        RotTransPers(&sp50, &sp58, &sp60, &sp60);

        poly->x0 = sp10.vx + sp58.vx;
        poly->y0 = sp10.vy + sp58.vy;
        sp50.vx  = sp40[1] + 51;
        sp50.vy  = sp40[3] - 51;

        RotTransPers(&sp50, &sp58, &sp60, &sp60);

        poly->x1 = sp10.vx + sp58.vx;
        poly->y1 = sp10.vy + sp58.vy;
        sp50.vx  = -51 - sp40[1];
        sp50.vy  = 51 - sp40[3];

        RotTransPers(&sp50, &sp58, &sp60, &sp60);

        poly->x2 = sp10.vx + sp58.vx;
        poly->y2 = sp10.vy + sp58.vy;
        sp50.vx  = 51 - sp40[0];
        sp50.vy  = 51 - sp40[2];

        RotTransPers(&sp50, &sp58, &sp60, &sp60);

        poly->x3 = sp10.vx + sp58.vx;
        poly->y3 = sp10.vy + sp58.vy;

        poly->u0 = 128;
        poly->u1 = 191;
        poly->u2 = 128;
        poly->u3 = 191;

        poly->v0 = 0;
        poly->v1 = 0;
        poly->v2 = 63;
        poly->v3 = 63;

        AddPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[var_s5], poly);
        GsOUT_PACKET_P = (PACKET*)poly + sizeof(POLY_FT4);
    }
}

void Game_SpotlightLoadScreenAttribsFix(void) // 0x8003EB54
{
    g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

    g_SysWork.field_235C = &g_SysWork.playerBoneCoords_890[HarryBone_Root];
    g_SysWork.field_236C = &g_SysWork.playerBoneCoords_890[HarryBone_Root];

    Math_Vector3Set(&g_SysWork.pointLightPosition_2360, Q12(0.0f), Q12(-0.2f), Q12(-2.0f));
    Math_SVectorSet(&g_SysWork.pointLightRot_2370, FP_ANGLE(10.0f), FP_ANGLE(0.0f), FP_ANGLE(0.0f));
}

void Game_FlashlightAttributesFix(void) // 0x8003EBA0
{
    g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

    g_SysWork.field_235C = &g_SysWork.playerBoneCoords_890[HarryBone_Torso];
    g_SysWork.field_236C = &g_SysWork.playerBoneCoords_890[HarryBone_Root];

    Math_Vector3Set(&g_SysWork.pointLightPosition_2360, Q12(-0.08f), Q12(-0.28f), Q12(0.12f));
    Math_SVectorSet(&g_SysWork.pointLightRot_2370, FP_ANGLE(-15.0f), FP_ANGLE(0.0f), FP_ANGLE(0.0f));
}

void Gfx_MapEffectsAssign(s_MapOverlayHeader* mapHdr) // 0x8003EBF4
{
    bool                    hasActiveChunk;
    u8                      flags;
    s_MapEffectsPresetIdxs* presetIdxPtr;

    flags          = mapHdr->mapInfo_0->flags_6;
    hasActiveChunk = false;
    if (flags & MapFlag_Interior)
    {
        hasActiveChunk = (flags & (MapFlag_OneActiveChunk | MapFlag_TwoActiveChunks)) > 0;
    }

    switch (mapHdr->field_16)
    {
        case 1:
            if (hasActiveChunk)
            {
                presetIdxPtr = &D_800A9F84;
            }
            else
            {
                presetIdxPtr = &D_800A9F80;
            }
            break;

        case 2:
            if (hasActiveChunk)
            {
                presetIdxPtr = &D_800A9F8C;
            }
            else
            {
                presetIdxPtr = &D_800A9F88;
            }
            break;

        case 3:
            presetIdxPtr = &D_800A9F98;
            break;

        default:
            presetIdxPtr = &D_800A9F80;
            break;
    }

    Gfx_MapInitMapEffectsUpdate(presetIdxPtr->presetIdx1_0, presetIdxPtr->presetIdx2_1);
}

void Game_TurnFlashlightOn(void) // 0x8003ECBC
{
    g_SysWork.field_2388.isFlashlightOn_15 = true;
    g_SavegamePtr->itemToggleFlags_AC     &= ~ItemToggleFlag_FlashlightOff;
}

void Game_TurnFlashlightOff(void) // 0x8003ECE4
{
    g_SysWork.field_2388.isFlashlightOn_15 = false;
    g_SavegamePtr->itemToggleFlags_AC     |= ItemToggleFlag_FlashlightOff;
}

void Game_FlashlightToggle(void) // 0x8003ED08
{
    // Awkward `isFlashlightOn_15` toggle.
    g_SysWork.field_2388.isFlashlightOn_15 ^= true;
    if (g_SysWork.field_2388.isFlashlightOn_15 == true)
    {
        g_SavegamePtr->itemToggleFlags_AC &= ~ItemToggleFlag_FlashlightOff;
    }
    else
    {
        g_SavegamePtr->itemToggleFlags_AC |= ItemToggleFlag_FlashlightOff;
    }
}

bool Game_FlashlightIsOn(void) // 0x8003ED64
{
    return g_SysWork.field_2388.isFlashlightOn_15;
}

void Gfx_MapInitMapEffectsUpdate(s32 idx0, s32 idx1) // 0x8003ED74
{
    Gfx_MapEffectsUpdate(idx0, idx1, PrimitiveType_None, NULL, 0, 0);
    Gfx_FlashlightUpdate();
}

void func_8003EDA8(void) // 0x8003EDA8
{
    g_SysWork.field_2388.field_14 = 1;
}

void func_8003EDB8(CVECTOR* color0, CVECTOR* color1) // 0x8003EDB8
{
    *color0 = g_SysWork.field_2388.field_1C[g_SysWork.field_2388.isFlashlightOn_15].effectsInfo_0.field_21;
    *color1 = g_SysWork.field_2388.field_1C[g_SysWork.field_2388.isFlashlightOn_15].effectsInfo_0.field_25;
}

void func_8003EE30(s32 arg0, s32* arg1, s32 arg2, s32 arg3) // 0x8003EE30
{
    g_SysWork.field_2388.field_4    = (s8*)arg1;
    g_SysWork.field_2388.primType_0 = PrimitiveType_S32;
    g_SysWork.field_2388.field_8    = arg2;
    g_SysWork.field_2388.field_C    = arg3;

    g_SysWork.field_2388.field_EC[0] = g_SysWork.field_2388.field_1C[0];
    g_SysWork.field_2388.field_EC[1] = g_SysWork.field_2388.field_1C[1];
}

void Gfx_LoadScreenMapEffectsUpdate(s32 arg0, s32 arg1) // 0x8003EEDC
{
    Gfx_MapEffectsUpdate(arg0, arg1, PrimitiveType_None, NULL, 0, 0);
    Gfx_FlashlightUpdate();
}

void Gfx_MapEffectsUpdate(s32 idx0, s32 idx1, e_PrimitiveType primType, void* primData, s32 arg4, s32 arg5) // 0x8003EF10
{
    Gfx_MapEffectsStepUpdate(&g_MapEffectsPresets[idx0], &g_MapEffectsPresets[idx1], primType, primData, arg4, arg5);
}

void Gfx_MapEffectsStepUpdate(s_MapEffectsInfo* preset0, s_MapEffectsInfo* preset1, e_PrimitiveType primType, void* primData, s32 arg4, s32 arg5) // 0x8003EF74
{
    if (preset0 == preset1)
    {
        g_SysWork.field_2388.isFlashlightUnavailable_16 = true;
    }
    else
    {
        g_SysWork.field_2388.isFlashlightUnavailable_16 = false;
    }

    g_SysWork.field_2388.field_4 = primData;
    g_SysWork.field_2388.primType_0 = primType;
    g_SysWork.field_2388.field_8 = arg4;
    g_SysWork.field_2388.field_C = arg5;

    g_SysWork.field_2388.field_EC[0] = g_SysWork.field_2388.field_1C[0];
    g_SysWork.field_2388.field_EC[1] = g_SysWork.field_2388.field_1C[1];

    Gfx_FogParametersSet(&g_SysWork.field_2388.field_84[0], preset0);
    Gfx_FogParametersSet(&g_SysWork.field_2388.field_84[1], preset1);
}

void Gfx_FogParametersSet(s_StructUnk3* arg0, s_MapEffectsInfo* effectsInfo) // 0x8003F08C
{
    arg0->effectsInfo_0 = *effectsInfo;

    if (effectsInfo->field_0.s_field_0.field_0 & (1 << 2))
    {
        arg0->field_2E = Q12(1.0f);
    }
    else
    {
        arg0->field_2E = Q12(0.0f);
    }

    if (effectsInfo->field_0.s_field_0.field_0 & (1 << 4))
    {
        arg0->flashlightLensFlareIntensity_2C = Q12(1.0f);
    }
    else
    {
        arg0->flashlightLensFlareIntensity_2C = Q12(0.0f);
    }

    switch (effectsInfo->field_E)
    {
        case 0:
        case 1:
            arg0->field_30 = effectsInfo->fogDistance_10;
            break;

        case 2:
            arg0->field_30 = Q12(0.0f);
            break;

        case 3:
            arg0->field_30 = effectsInfo->fogDistance_10;
            break;
    }
}

void Gfx_FlashlightUpdate(void) // 0x8003F170
{
    MATRIX          mat;
    VECTOR          sp48;
    SVECTOR         rot;
    s32             temp_v0;
    u8              flags;
    s32             temp;
    GsCOORDINATE2*  coord;
    s_StructUnk3*   ptr2;
    s_SysWork_2388* ptr;

    ptr = &g_SysWork.field_2388;

    if (g_SysWork.field_2388.isFlashlightOn_15)
    {
        g_SysWork.field_2388.flashlightIntensity_18 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 4.0f);
    }
    else
    {
        g_SysWork.field_2388.flashlightIntensity_18 -= Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 4.0f);
    }

    g_SysWork.field_2388.flashlightIntensity_18 = CLAMP(g_SysWork.field_2388.flashlightIntensity_18, Q12(0.0f), Q12(1.0f));

    if (g_SysWork.field_2388.field_84[g_SysWork.field_2388.flashlightIntensity_18 != 0].effectsInfo_0.field_E == 3)
    {
        func_80049AF8(g_SysWork.field_235C, &mat);
        ApplyMatrixLV(&mat, (VECTOR*)&g_SysWork.pointLightPosition_2360, &sp48); // Bug? `g_SysWork.pointLightPosition_2360` is `VECTOR3`.
        ptr->field_84[g_SysWork.field_2388.flashlightIntensity_18 != 0].field_30 = sp48.vz + (mat.t[2] * 16);
    }

    if (ptr->primType_0 == PrimitiveType_None)
    {
        ptr->field_1C[0] = ptr->field_84[0];
        ptr->field_1C[1] = ptr->field_84[1];
    }
    else
    {
        temp_v0 = func_8003F6F0(func_8003F654(ptr), ptr->field_8, ptr->field_C);

        func_8003F838(&ptr->field_1C[0], &ptr->field_EC[0], &ptr->field_84[0], temp_v0);
        func_8003F838(&ptr->field_1C[1], &ptr->field_EC[1], &ptr->field_84[1], temp_v0);

        if (temp_v0 >= Q12(1.0f))
        {
            ptr->primType_0 = PrimitiveType_None;
        }
    }

    func_8003F838(&ptr->field_154, &ptr->field_1C[0], &ptr->field_1C[1], ptr->flashlightIntensity_18);

    ptr2 = &ptr->field_154;

    if (ptr->field_14 != 0)
    {
        flags         = ptr->field_154.effectsInfo_0.field_0.s_field_0.field_0;
        ptr->field_14 = 0;

        if (flags & (1 << 0))
        {
            Gfx_FogParametersSet(ptr2, &g_MapEffectsPresets[8]);
        }
        else if (flags & (1 << 1))
        {
            ptr2->effectsInfo_0.field_4 += Q12(0.3f);
        }
    }

    ptr->field_10 = func_8003FEC0(&ptr2->effectsInfo_0);
    func_8003FF2C(ptr2);

    temp = Q12_MULT(func_8003F4DC(&coord, &rot, ptr2->effectsInfo_0.field_4, ptr2->effectsInfo_0.field_0.s_field_0.field_2, func_80080A10(), &g_SysWork), g_SysWork.pointLightIntensity_2378);

    func_800554C4(temp, ptr2->flashlightLensFlareIntensity_2C, coord, g_SysWork.field_235C, &rot, 
                  g_SysWork.pointLightPosition_2360.vx, g_SysWork.pointLightPosition_2360.vy, g_SysWork.pointLightPosition_2360.vz,
                  g_WorldGfx.mapInfo_0->waterZones_8);
    func_80055814(ptr2->field_30);

    if (ptr->field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 3))
    {
        func_8003E740();
    }
}

q19_12 func_8003F4DC(GsCOORDINATE2** coords, SVECTOR* rot, q19_12 alpha, s32 arg3, u32 arg4, s_SysWork* sysWork) // 0x8003F4DC
{
    s32     temp;
    q19_12  alphaCpy;
    SVECTOR rot0;

    if (arg3 != 2)
    {
        arg4 = 1;
    }

    alphaCpy = alpha;
    if (arg4 == 0)
    {
        alphaCpy = Q12(0.0f);
    }

    switch (arg4)
    {
        default:
        case 1:
            *coords = sysWork->field_236C;
            break;

        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
            *coords = NULL;
            break;
    }

    switch (arg4)
    {
        default:
        case 1:
            rot0 = sysWork->pointLightRot_2370;
            break;

        case 0:
            rot0.vx = FP_ANGLE(0.0f);
            rot0.vy = FP_ANGLE(-90.0f);
            rot0.vz = FP_ANGLE(0.0f);
            break;

        case 2:
            rot0.vx = FP_ANGLE(-20.0f);
            rot0.vy = FP_ANGLE(195.0f);
            rot0.vz = FP_ANGLE(0.0f);
            break;

        case 3:
            rot0.vx = FP_ANGLE(-20.0f);
            rot0.vy = FP_ANGLE(-75.0f);
            rot0.vz = FP_ANGLE(0.0f);
            break;

        case 4:
            rot0.vx = FP_ANGLE(-20.0f);
            rot0.vy = FP_ANGLE(15.0f);
            rot0.vz = FP_ANGLE(0.0f);
            break;

        case 5:
            rot0.vx = FP_ANGLE(-20.0f);
            rot0.vy = FP_ANGLE(105.0f);
            rot0.vz = FP_ANGLE(0.0f);
            break;
    }

    rot->vy = -Math_Sin(rot0.vx);
    temp    = Math_Cos(rot0.vx);
    rot->vz = Q12_MULT(temp, Math_Cos(rot0.vy));
    rot->vx = Q12_MULT(temp, Math_Sin(rot0.vy));
    return alphaCpy;
}

u32 func_8003F654(s_SysWork_2388* arg0)
{
    switch (arg0->primType_0)
    {
        default:
        case PrimitiveType_None:
            break;

        case PrimitiveType_S8:
            return *arg0->field_4;

        case PrimitiveType_U8:
            return *(u8*)arg0->field_4;

        case PrimitiveType_S16:
            return *(s16*)arg0->field_4;

        case PrimitiveType_U16:
            return *(u16*)arg0->field_4;

        case PrimitiveType_S32:
            return *(s32*)arg0->field_4;
    }

    return 0;
}

s32 func_8003F6F0(s32 arg0, s32 arg1, s32 arg2) // 0x8003F6F0
{
    s32 leadingZeros;
    s32 shift;

    if (arg1 < arg2)
    {
        arg0 = CLAMP(arg0, arg1, arg2);
    }
    else if (arg2 < arg1)
    {
        arg0 = CLAMP(arg0, arg2, arg1);
    }
    else
    {
        return Q12(1.0f);
    }

    leadingZeros = 32 - Lzc(arg2 - arg1);
    shift        = 0;

    if ((leadingZeros + 12) >= 31)
    {
        shift = leadingZeros - 19;
    }

    shift = CLAMP(shift, 0, Q12_SHIFT);

    return ((arg0 - arg1) << (Q12_SHIFT - shift)) / ((arg2 - arg1) >> shift);
}

q19_12 Math_WeightedAverageGet(s32 a, s32 b, q19_12 weight) // 0x8003F7E4
{
    return Math_MulFixed(a, Q12(1.0f) - weight, Q12_SHIFT) + Math_MulFixed(b, weight, Q12_SHIFT);
}

void func_8003F838(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, q19_12 weight) // 0x8003F838
{
    q19_12 weight0;
    q19_12 weight1;
    q19_12 weight2;
    u32    temp;

    weight0 = weight * 2;
    weight0 = CLAMP(weight0, Q12(0.0f), Q12(1.0f));
    weight1 = (weight - Q12(0.5f)) * 2;
    weight1 = CLAMP(weight1, Q12(0.0f), Q12(1.0f));

    if (weight < Q12(0.5f))
    {
        arg0->effectsInfo_0.field_0.s_field_0.field_0 = arg1->effectsInfo_0.field_0.s_field_0.field_0;
    }
    else
    {
        arg0->effectsInfo_0.field_0.s_field_0.field_0 = arg2->effectsInfo_0.field_0.s_field_0.field_0;
    }

    func_8003FCB0(&arg0->effectsInfo_0, &arg1->effectsInfo_0, &arg2->effectsInfo_0, weight);

    if (arg1->flashlightLensFlareIntensity_2C == Q12(0.0f))
    {
        arg0->flashlightLensFlareIntensity_2C = Math_WeightedAverageGet(0, arg2->flashlightLensFlareIntensity_2C, weight1);
    }
    else
    {
        arg0->flashlightLensFlareIntensity_2C = Math_WeightedAverageGet(arg1->flashlightLensFlareIntensity_2C, arg2->flashlightLensFlareIntensity_2C, weight0);
    }

    if (arg1->effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0))
    {
        if (arg2->effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0))
        {
            arg0->effectsInfo_0.field_0.s_field_0.field_1 = Math_WeightedAverageGet(arg1->effectsInfo_0.field_0.s_field_0.field_1, arg2->effectsInfo_0.field_0.s_field_0.field_1, weight);
        }
        else
        {
            arg0->effectsInfo_0.field_0.s_field_0.field_1 = Math_WeightedAverageGet(arg1->effectsInfo_0.field_0.s_field_0.field_1, arg2->effectsInfo_0.field_0.s_field_0.field_1, weight1);
        }
    }
    else
    {
        if (arg2->effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0))
        {
            arg0->effectsInfo_0.field_0.s_field_0.field_1 = Math_WeightedAverageGet(arg1->effectsInfo_0.field_0.s_field_0.field_1, arg2->effectsInfo_0.field_0.s_field_0.field_1, weight0);
        }
        else
        {
            arg0->effectsInfo_0.field_0.s_field_0.field_1 = Math_WeightedAverageGet(arg1->effectsInfo_0.field_0.s_field_0.field_1, arg2->effectsInfo_0.field_0.s_field_0.field_1, weight);
        }
    }

    if (arg1->effectsInfo_0.field_E == 0)
    {
        if (arg2->effectsInfo_0.field_E != 0)
        {
            arg0->effectsInfo_0.field_E = arg2->effectsInfo_0.field_E;
            func_8003FD38(arg0, arg1, arg2, weight, weight0, weight1);
        }
        else
        {
            temp                  = arg2->effectsInfo_0.field_E;
            arg0->effectsInfo_0.field_E = temp;
            func_8003FD38(arg0, arg1, arg2, weight, weight, weight);
        }
    }
    else if (arg2->effectsInfo_0.field_E == 0)
    {
        if (weight1 >= Q12(1.0f))
        {
            arg0->effectsInfo_0.field_E = arg2->effectsInfo_0.field_E;
        }
        else
        {
            arg0->effectsInfo_0.field_E = arg1->effectsInfo_0.field_E;
        }

        func_8003FD38(arg0, arg1, arg2, weight, weight1, weight0);
    }
    else
    {
        temp                  = arg2->effectsInfo_0.field_E;
        arg0->effectsInfo_0.field_E = temp;
        func_8003FD38(arg0, arg1, arg2, weight, weight, weight);
    }

    arg0->effectsInfo_0.worldTintR_8 = Math_WeightedAverageGet(arg1->effectsInfo_0.worldTintR_8, arg2->effectsInfo_0.worldTintR_8, weight);
    arg0->effectsInfo_0.worldTintG_A = Math_WeightedAverageGet(arg1->effectsInfo_0.worldTintG_A, arg2->effectsInfo_0.worldTintG_A, weight);
    arg0->effectsInfo_0.worldTintB_C = Math_WeightedAverageGet(arg1->effectsInfo_0.worldTintB_C, arg2->effectsInfo_0.worldTintB_C, weight);

    if (arg1->effectsInfo_0.field_0.s_field_0.field_2 == 1 && arg2->effectsInfo_0.field_0.s_field_0.field_2 == 2)
    {
        if (weight < Q12(5.0f / 6.0f))
        {
            weight2                                 = Q12_MULT(weight, Q12(1.2f));
            weight2                                 = CLAMP(weight2, Q12(0.0f), Q12(1.0f));
            arg0->effectsInfo_0.field_0.s_field_0.field_2 = arg1->effectsInfo_0.field_0.s_field_0.field_2;
            arg0->effectsInfo_0.field_4                   = Math_WeightedAverageGet(arg1->effectsInfo_0.field_4, 0, weight2);
        }
        else
        {
            weight2                                 = (weight - Q12(5.0f / 6.0f)) * 6;
            weight2                                 = CLAMP(weight2, Q12(0.0f), Q12(1.0f));
            arg0->effectsInfo_0.field_0.s_field_0.field_2 = arg2->effectsInfo_0.field_0.s_field_0.field_2;
            weight0                                 = arg2->effectsInfo_0.field_4;
            arg0->effectsInfo_0.field_4                   = Math_WeightedAverageGet(Q12(0.0f), weight0, weight2);
        }
    }
    else if (arg1->effectsInfo_0.field_0.s_field_0.field_2 == 2 && arg2->effectsInfo_0.field_0.s_field_0.field_2 == 1)
    {
        if (weight < Q12(1.0f / 6.0f))
        {
            weight2                                 = weight * 6;
            weight2                                 = CLAMP(weight2, Q12(0.0f), Q12(1.0f));
            arg0->effectsInfo_0.field_0.s_field_0.field_2 = arg1->effectsInfo_0.field_0.s_field_0.field_2;
            arg0->effectsInfo_0.field_4                   = Math_WeightedAverageGet(arg1->effectsInfo_0.field_4, Q12(0.0f), weight2);
        }
        else
        {
            weight2                                 = Q12_MULT(weight - Q12(1.0f / 6.0f), Q12(1.2f));
            weight2                                 = CLAMP(weight2, Q12(0.0f), Q12(1.0f));
            arg0->effectsInfo_0.field_0.s_field_0.field_2 = arg2->effectsInfo_0.field_0.s_field_0.field_2;
            arg0->effectsInfo_0.field_4                   = Math_WeightedAverageGet(Q12(0.0f), arg2->effectsInfo_0.field_4, weight2);
        }
    }
    else
    {
        if (arg1->effectsInfo_0.field_0.s_field_0.field_2 != 0 && arg2->effectsInfo_0.field_0.s_field_0.field_2 == 0)
        {
            if (weight >= Q12(1.0f))
            {
                arg0->effectsInfo_0.field_0.s_field_0.field_2 = arg2->effectsInfo_0.field_0.s_field_0.field_2;
            }
            else
            {
                arg0->effectsInfo_0.field_0.s_field_0.field_2 = arg1->effectsInfo_0.field_0.s_field_0.field_2;
            }
        }
        else
        {
            arg0->effectsInfo_0.field_0.s_field_0.field_2 = arg2->effectsInfo_0.field_0.s_field_0.field_2;
        }

        arg0->effectsInfo_0.field_4 = Math_WeightedAverageGet(arg1->effectsInfo_0.field_4, arg2->effectsInfo_0.field_4, weight);
    }

    if (arg1->effectsInfo_0.field_18 == 0 && arg2->effectsInfo_0.field_18 != 0)
    {
        func_8003FE04(&arg0->effectsInfo_0, &arg1->effectsInfo_0, &arg2->effectsInfo_0, weight1);
    }
    else
    {
        func_8003FE04(&arg0->effectsInfo_0, &arg1->effectsInfo_0, &arg2->effectsInfo_0, weight);
    }
}

void func_8003FCB0(s_MapEffectsInfo* arg0, s_MapEffectsInfo* arg1, s_MapEffectsInfo* arg2, q19_12 alphaTo) // 0x8003FCB0
{
    q19_12 alphaFrom;
    
    alphaFrom = Q12(1.0f) - alphaTo;
    LoadAverageCol(&arg1->field_21.r, &arg2->field_21.r, alphaFrom, alphaTo, &arg0->field_21.r);
    LoadAverageCol(&arg1->field_25.r, &arg2->field_25.r, alphaFrom, alphaTo, &arg0->field_25.r);
}

void func_8003FD38(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, q19_12 weight0, q19_12 weight1, q19_12 alphaTo) // 0x8003FD38
{
    if (arg1->field_2E != arg2->field_2E)
    {
        arg0->field_2E = Math_WeightedAverageGet(arg1->field_2E, arg2->field_2E, weight0);
    }
    else
    {
        arg0->field_2E = arg2->field_2E;
    }

    arg0->field_30               = Math_WeightedAverageGet(arg1->field_30, arg2->field_30, weight0);
    arg0->effectsInfo_0.fogDistance_10 = Math_WeightedAverageGet(arg1->effectsInfo_0.fogDistance_10, arg2->effectsInfo_0.fogDistance_10, weight1);
    arg0->effectsInfo_0.field_6        = Math_WeightedAverageGet(arg1->effectsInfo_0.field_6, arg2->effectsInfo_0.field_6, weight0);

    LoadAverageCol(&arg1->effectsInfo_0.fogColor_14.r, &arg2->effectsInfo_0.fogColor_14.r, Q12(1.0f) - alphaTo, alphaTo, &arg0->effectsInfo_0.fogColor_14.r);
}

void func_8003FE04(s_MapEffectsInfo* arg0, s_MapEffectsInfo* arg1, s_MapEffectsInfo* arg2, q19_12 alphaTo) // 0x8003FE04
{
    q19_12 alphaFrom;

    alphaFrom = Q12(1.0f) - alphaTo;
    LoadAverageCol(&arg1->field_19.r, &arg2->field_19.r, alphaFrom, alphaTo, &arg0->field_19.r);
    LoadAverageCol(&arg1->screenTint_1D.r, &arg2->screenTint_1D.r, alphaFrom, alphaTo, &arg0->screenTint_1D.r);

    if ((arg0->field_19.r || arg0->field_19.g || arg0->field_19.b) ||
        (arg0->screenTint_1D.r || arg0->screenTint_1D.g || arg0->screenTint_1D.b))
    {
        arg0->field_18 = 1;
    }
    else
    {
        arg0->field_18 = 0;
    }
}

s32 func_8003FEC0(s_MapEffectsInfo* arg0) // 0x8003FEC0
{
    static q19_12 Y_ARRAY[5] = {
        Q12(1.75f),
        Q12(6.0f),
        Q12(9.5f),
        Q12(12.5f),
        Q12(15.0f)
    };

    if (g_WorldEnvWork.isFogEnabled_1)
    {
        return arg0->fogDistance_10;
    }

    if (g_WorldEnvWork.field_0 == 1)
    {
        return vwOresenHokan(Y_ARRAY, ARRAY_SIZE(Y_ARRAY), arg0->field_4, 0, Q12(2.0f));
    }

    return Q12(20.0f);
}

void func_8003FF2C(s_StructUnk3* arg0) // 0x8003FF2C
{
    s32   temp_a0;
    s32   temp_v1;
    q23_8 brightness;

    temp_v1    = Q12_MULT(arg0->field_2E, (g_GameWork.config_0.optBrightness_22 * 8) + 4);
    brightness = CLAMP(temp_v1, Q8_CLAMPED(0.0f), Q8_CLAMPED(1.0f));

    func_80055330(arg0->effectsInfo_0.field_0.s_field_0.field_2, arg0->effectsInfo_0.field_6, arg0->effectsInfo_0.field_0.s_field_0.field_1, arg0->effectsInfo_0.worldTintR_8, arg0->effectsInfo_0.worldTintG_A, arg0->effectsInfo_0.worldTintB_C, brightness);
    WorldEnv_FogParamsSet(arg0->effectsInfo_0.field_E != 0, arg0->effectsInfo_0.fogColor_14.r, arg0->effectsInfo_0.fogColor_14.g, arg0->effectsInfo_0.fogColor_14.b);

    temp_a0 = arg0->effectsInfo_0.fogDistance_10;

    WorldEnv_FogDistanceSet(temp_a0, temp_a0 + Q12(1.0f));
    func_800553E0(arg0->effectsInfo_0.field_18, arg0->effectsInfo_0.field_19.r, arg0->effectsInfo_0.field_19.g, arg0->effectsInfo_0.field_19.b, arg0->effectsInfo_0.screenTint_1D.r, arg0->effectsInfo_0.screenTint_1D.g, arg0->effectsInfo_0.screenTint_1D.b);
}
