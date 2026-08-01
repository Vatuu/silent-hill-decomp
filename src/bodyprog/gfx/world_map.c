#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

static s_WorldMapWork g_WorldMapWork;

/** @brief Gets the load status of an IPD/PLM file by utilizing `Fs_QueueIsEntryLoaded`.
 *
 * @param queueIdx Index of the queue entry to check.
 * @return Queue entry load status (`e_WorldMapLoadState`).
 */
static u32 WorldMap_LoadStateGet(s32 queueIdx) // 0x80041ADC
{
    if (queueIdx == NO_VALUE)
    {
        return WorldMapLoadState_Invalid;
    }
    else if (!Fs_QueueIsEntryLoaded(queueIdx))
    {
        return WorldMapLoadState_Unloaded;
    }

    return WorldMapLoadState_Loaded;
}

/** @brief Gets the load state of an IPD file (Chunk) and their dependencies.
 *
 * @param Chunk IPD file to check.
 * @return IPD file load state `(e_MapModelLoadState`).
 */
static u32 WorldMap_ChunkLoadStateGet(s_MapChunk* chunk) // 0x80041B1C
{
    s32 loadState;
    s32 loadStateCpy;

    loadStateCpy = loadState = WorldMap_LoadStateGet(chunk->queueIdx);

    if (loadStateCpy == WorldMapLoadState_Unloaded)
    {
        return MapModelLoadState_Unloaded;
    }
    else if (loadStateCpy == WorldMapLoadState_Invalid ||
             loadState    != WorldMapLoadState_Loaded)
    {
        return MapModelLoadState_Invalid;
    }
    else if (chunk->ipdHdr->isLoaded && WorldMap_TextureLoadedCheck(chunk->ipdHdr))
    {
        return MapModelLoadState_Loaded;
    }

    return MapModelLoadState_Corrupted;
}

/** @brief Gets the load state of a PLM file (Global LM) and their dependencies.
 *
 * @param globalLm PLM file to check.
 * @return PLM file load state `(e_MapModelLoadState`).
 */
static u32 WorldMap_GlobalLmLoadStateGet(s_PlmLm* globalLm) // 0x80041BA0
{
    s32 loadState;
    s32 loadStateCpy;

    loadStateCpy = loadState = WorldMap_LoadStateGet(globalLm->queueIdx);

    if (loadStateCpy == WorldMapLoadState_Unloaded)
    {
        return MapModelLoadState_Unloaded;
    }
    else if (loadStateCpy == WorldMapLoadState_Invalid ||
             loadState    != WorldMapLoadState_Loaded)
    {
        return MapModelLoadState_Invalid;
    }
    else if (globalLm->lmHdr->isLoaded && Lm_IsTextureLoaded(globalLm->lmHdr))
    {
        return MapModelLoadState_Loaded;
    }

    return MapModelLoadState_Corrupted;
}

void WorldMap_Init(s_LmHeader* lmHdr, s_IpdHeader* ipdBuf, s32 ipdBufSize) // 0x80041C24
{
    bzero(&g_WorldMapWork, sizeof(s_WorldMapWork));
    WorldMap_GlobalLmInit(&g_WorldMapWork.globalLm, lmHdr);

    g_WorldMapWork.chunkBuffer      = ipdBuf;
    g_WorldMapWork.chunkBufferSize  = ipdBufSize;
    g_WorldMapWork.activeChunkCount = 0;
    g_WorldMapWork.isExterior       = true;

    WorldMap_ChunkQueueClear(g_WorldMapWork.activeChunks, 4);
    WorldMap_TexturesInit();
    WorldMap_CollisionDataReset();
}

void WorldMap_GlobalLmInit(s_PlmLm* globalLm, s_LmHeader* lmHdr) // 0x80041CB4
{
    globalLm->lmHdr = lmHdr;
    WorldMap_GlobalLmHeaderInit(lmHdr);

    globalLm->queueIdx = 0;
    globalLm->fileIdx  = NO_VALUE;
}

void WorldMap_GlobalLmHeaderInit(s_LmHeader* lmHdr) // 0x80041CEC
{
    lmHdr->magic         = LM_HEADER_MAGIC;
    lmHdr->version       = LM_VERSION;
    lmHdr->isLoaded      = true;
    lmHdr->materialCount = 0;
    lmHdr->modelCount    = 0;
}

void WorldMap_ChunkQueueClear(s_MapChunk* chunkBufferPtr, s32 activeChunkCount) // 0x80041D10
{
    s_MapChunk* curChunk;

    for (curChunk = &chunkBufferPtr[0]; curChunk < &chunkBufferPtr[activeChunkCount]; curChunk++)
    {
        curChunk->queueIdx = NO_VALUE;
    }
}

void WorldMap_TexturesInit(void) // 0x80041D48
{
    s32 i;
    s16 j;
    s16 x;
    s32 y;

    // Run through texture pages.
    for (i = 0, y = 8, x = 0, j = 0;
         i < 8;
         i++, y++, x += 16)
    {
        if (y == 11)
        {
            y = 21;
        }

        Texture_Init(&g_WorldMapWork.chunkTextures.fullPageTextures[i], NULL, 0, y, 0, 0, x, j);
    }

    Textures_ActiveTex_CountReset(&g_WorldMapWork.chunkTextures.fullPage);
    Textures_ActiveTex_PutTextures(&g_WorldMapWork.chunkTextures.fullPage, g_WorldMapWork.chunkTextures.fullPageTextures, 8);

    // Run through texture pages.
    for (i = 0, y = 26, j = 0; i < 2; i++, x += 16)
    {
        Texture_Init(&g_WorldMapWork.chunkTextures.halfPageTextures[i], NULL, 0, y, (i & 0x1) * 32, 0, x, j);
        if (i & 0x1)
        {
            y++;
        }
    }

    Textures_ActiveTex_CountReset(&g_WorldMapWork.chunkTextures.halfPage);
    Textures_ActiveTex_PutTextures(&g_WorldMapWork.chunkTextures.halfPage, g_WorldMapWork.chunkTextures.halfPageTextures, 2);
}

void WorldMap_CollisionDataReset(void) // 0x80041E98
{
    bzero(&g_WorldMapWork.collisionData, sizeof(s_IpdCollisionData));
    g_WorldMapWork.collisionData.subcellSize = Q8(2.0f);
}

void WorldMap_ChunkSet(s16 ipdFileIdx, s32 chunkX, s32 chunkZ) // 0x80041ED0
{
    s_MapChunk*  curChunk;
    s_IpdHeader* curIpdHdr;

    ((s16*)&g_WorldMapWork.chunksGridCenter[chunkZ])[chunkX] = ipdFileIdx;

    // Run through active chunks.
    for (curChunk = &g_WorldMapWork.activeChunks[0];
         curChunk < &g_WorldMapWork.activeChunks[g_WorldMapWork.activeChunkCount];
         curChunk++)
    {
        // Check if chunk coordiantes match.
        if (curChunk->chunkX != chunkX ||
            curChunk->chunkZ != chunkZ)
        {
            continue;
        }

        // Check if chunk is loaded.
        if (WorldMap_LoadStateGet(curChunk->queueIdx) >= WorldMapLoadState_Loaded)
        {
            curIpdHdr = curChunk->ipdHdr;
            if (curIpdHdr->isLoaded)
            {
                Lm_MaterialRefCountDec(curIpdHdr->lmHdr);
            }
        }

        curChunk->queueIdx = NO_VALUE;
    }
}

void WorldMap_ActiveChunksClear(void) // 0x80041FF0
{
    WorldMap_ChunksClear(&g_WorldMapWork, g_WorldMapWork.activeChunkCount);
}

void WorldMap_TexturesRefClear(void) // 0x8004201C
{
    s_Texture* curTex;

    // Clear ful-page textures.
    curTex = &g_WorldMapWork.chunkTextures.fullPageTextures[0];
    while (curTex < (&g_WorldMapWork.chunkTextures.fullPageTextures[FULL_PAGE_CHUNK_TEXTURE_COUNT_MAX]))
    {
        if (curTex->refCount == 0)
        {
            Texture_RefClear(curTex);
        }

        curTex++;
    }

    // Clear half-page textures.
    curTex = &g_WorldMapWork.chunkTextures.halfPageTextures[0];
    while (curTex < (&g_WorldMapWork.chunkTextures.halfPageTextures[HALF_PAGE_CHUNK_TEXTURE_COUNT_MAX]))
    {
        if (curTex->refCount == 0)
        {
            Texture_RefClear(curTex);
        }

        curTex++;
    }
}

void WorldMap_Reset(void) // 0x800420C0
{
    WorldMap_GlobalLmReset();
    WorldMap_ChunksClear(&g_WorldMapWork, g_WorldMapWork.activeChunkCount);
    WorldMap_TexturesInit();
}

void WorldMap_GlobalLmReset(void) // 0x800420FC
{
    s_PlmLm* globalLm;

    globalLm = &g_WorldMapWork.globalLm;

    if (WorldMap_LoadStateGet(globalLm->queueIdx) >= WorldMapLoadState_Loaded &&
        globalLm->lmHdr->isLoaded)
    {
        Lm_MaterialRefCountDec(g_WorldMapWork.globalLm.lmHdr);
    }

    WorldMap_GlobalLmInit(&g_WorldMapWork.globalLm, g_WorldMapWork.globalLm.lmHdr);
}

s_Texture* WorldMap_ActiveTextureInfoGet(char* texName) // 0x80042178
{
    s_Texture* tex;

    // Find full-page texture.
    tex = Textures_ActiveTex_FindTexture(texName, &g_WorldMapWork.chunkTextures.fullPage);
    if (tex != NULL)
    {
        return tex;
    }

    // Find half-page texture.
    tex = Textures_ActiveTex_FindTexture(texName, &g_WorldMapWork.chunkTextures.halfPage);
    if (tex != NULL)
    {
        return tex;
    }

    return NULL;
}

void WorldMap_InfoSet(char* mapTag, e_FsFile plmIdx, s32 activeChunkCount, bool isExterior,
                      e_FsFile ipdFileIdx, e_FsFile texFileIdx) // 0x800421D8
{
    g_WorldMapWork.isExterior     = isExterior;
    g_WorldMapWork.textureFileIdx = texFileIdx;

    if (plmIdx != NO_VALUE && plmIdx != g_WorldMapWork.globalLm.fileIdx)
    {
        if (WorldMap_LoadStateGet(g_WorldMapWork.globalLm.queueIdx) >= WorldMapLoadState_Loaded &&
            g_WorldMapWork.globalLm.lmHdr->isLoaded)
        {
            Lm_MaterialRefCountDec(g_WorldMapWork.globalLm.lmHdr);
        }

        g_WorldMapWork.globalLm.fileIdx  = plmIdx;
        g_WorldMapWork.globalLm.queueIdx = NO_VALUE;
    }

    if (g_WorldMapWork.activeChunkCount != activeChunkCount || strcmp(mapTag, g_WorldMapWork.mapTag) != 0)
    {
        WorldMap_ChunksClear(&g_WorldMapWork, activeChunkCount);

        g_WorldMapWork.activeChunkCount = activeChunkCount;
        g_WorldMapWork.ipdFileIdx      = ipdFileIdx;
        strcpy(g_WorldMapWork.mapTag, mapTag);

        g_WorldMapWork.mapTagSize = strlen(mapTag);
        WorldMap_MakeGrid(&g_WorldMapWork, mapTag, ipdFileIdx);
    }
}

void WorldMap_ChunksClear(s_WorldMapWork* terrain, s32 activeChunksCount) // 0x80042300
{
    s32          chunkSize;
    s32          i;
    s_MapChunk*  curChunk;
    s_IpdHeader* chunkBuffer;
    s_IpdHeader* curIpdHdr;

    chunkBuffer = terrain->chunkBuffer;
    chunkSize   = (terrain->chunkBufferSize / activeChunksCount) & ~0x3;

    for (i = 0; i < ACTIVE_CHUNK_COUNT_MAX; i++, *(u8**)&chunkBuffer += chunkSize)
    {
        curChunk = &terrain->activeChunks[i];

        if (WorldMap_LoadStateGet(curChunk->queueIdx) >= WorldMapLoadState_Loaded)
        {
            curIpdHdr = curChunk->ipdHdr;
            if (curIpdHdr->isLoaded)
            {
                Lm_MaterialRefCountDec(curIpdHdr->lmHdr);
            }
        }

        curChunk->queueIdx              = NO_VALUE;
        curChunk->paddedDistanceToEdge1 = INT_MAX;
        curChunk->outsideCount          = 0;

        if (i < activeChunksCount)
        {
            curChunk->ipdHdr = chunkBuffer;
        }
        else
        {
            curChunk->ipdHdr = NULL;
        }
    }
}

void WorldMap_MakeGrid(s_WorldMapWork* terrain, char* mapTag, e_FsFile fileIdxStart) // 0x800423F4
{
    char           filename[256];
    s32            x;
    s32            z;
    s32            i;
    char*          filenameSuffix;
    s_ChunkColumn* coll;

    terrain->chunksGridCenter = (s_ChunkColumn*)(&terrain->chunksGrid[8].idx[8]);

    for (z = -8; z < 11; z++)
    {
        for (x = -8; x < 8; x++)
        {
            ((s16*)&terrain->chunksGridCenter[z])[x] = NO_VALUE;
        }
    }

    // Attach all IPD files labeled with the assignated tag in game files.
    for (i = fileIdxStart; i < FS_FILE_COUNT; i++)
    {
        if (g_FileTable[i].type == FileType_Ipd)
        {
            Fs_GetFileName(filename, i);

            if (strncmp(filename, terrain->mapTag, terrain->mapTagSize) == 0)
            {
                filenameSuffix = &filename[terrain->mapTagSize];
                if (ConvertHexToS8(&x, filenameSuffix[0], filenameSuffix[1]) &&
                    ConvertHexToS8(&z, filenameSuffix[2], filenameSuffix[3]))
                {
                    coll         = &terrain->chunksGridCenter[z];
                    coll->idx[x] = i;
                }
            }
        }
    }
}

bool ConvertHexToS8(s32* out, char hex0, char hex1) // 0x8004255C
{
    char low;
    char high;
    char letterIdx;
    char hexVal;
    bool isNumber;

    high     = hex0 - '0';
    isNumber = high < 10;

    hexVal   = high;
    hexVal <<= 4;
    if (!isNumber)
    {
        letterIdx = hex0 - 'A';
        if (letterIdx > 5)
        {
            return false;
        }

        hexVal = (hex0 + 201) << 4;
    }

    low      = hex1 - '0';
    isNumber = low < 10;
    if (isNumber)
    {
        hexVal |= low;
    }
    else
    {
        letterIdx = hex1 - 'A';
        if (letterIdx > 5)
        {
            return false;
        }

        hexVal |= hex1 + 201;
    }

    *out = (hexVal << 24) >> 24; // Sign extend.
    return true;
}

s_IpdCollisionData** WorldMap_ActiveChunksCollisionDataGet(s32* collDataIdx) // 0x800425D8
{
    s_MapChunk*                curChunk;
    s_IpdCollisionData*        collData;
    s_IpdHeader*               curIpdHdr;
    static s_IpdCollisionData* activeChunksCollData[4];

    // Run through active chunks.
    for (curChunk = g_WorldMapWork.activeChunks, *collDataIdx = 0;
         curChunk < &g_WorldMapWork.activeChunks[g_WorldMapWork.activeChunkCount];
         curChunk++)
    {
        // Check if chunk is loaded.
        if (WorldMap_LoadStateGet(curChunk->queueIdx) >= WorldMapLoadState_Loaded)
        {
            curIpdHdr = curChunk->ipdHdr;
            if (curIpdHdr->isLoaded)
            {
                collData = WorldMap_HeaderCollisionDataGet(curIpdHdr);
                if (collData != NULL)
                {
                    activeChunksCollData[(*collDataIdx)++] = collData;
                }
            }
        }
    }

    return &activeChunksCollData[0];
}

s_IpdCollisionData* WorldMap_CollisionDataGet(q19_12 posX, q19_12 posZ) // 0x800426E4
{
    s32          geomX;
    s32          geomZ;
    s32          chunkX;
    s32          chunkZ;
    s_IpdHeader* curIpdHdr;
    s_MapChunk*  curChunk;

    // Convert position to geometry space.
    geomX = Q12_TO_Q8(posX);
    geomZ = Q12_TO_Q8(posZ);

    // Compute chunk coordinates.
    chunkX = FLOOR_TO_STEP(geomX, Q8(CHUNK_SIZE));
    chunkZ = FLOOR_TO_STEP(geomZ, Q8(CHUNK_SIZE));

    // Run through active chunk.
    for (curChunk = &g_WorldMapWork.activeChunks[0];
         curChunk < &g_WorldMapWork.activeChunks[g_WorldMapWork.activeChunkCount];
         curChunk++)
    {
        // Check if chunk is loaded.
        if (WorldMap_LoadStateGet(curChunk->queueIdx) < WorldMapLoadState_Loaded)
        {
            continue;
        }

        // Check if chunk coordinates matches target position.
        curIpdHdr = curChunk->ipdHdr;
        if (curIpdHdr->isLoaded &&
            curChunk->chunkX == chunkX && curChunk->chunkZ == chunkZ)
        {
            return &curIpdHdr->collisionData;
        }
    }

    // Fallback.
    if (((s16*)(&g_WorldMapWork.chunksGridCenter[chunkZ]))[chunkX] != NO_VALUE)
    {
        return NULL;
    }
    else
    {
        return &g_WorldMapWork.collisionData;
    }
}

s32 WorldMap_ObjectModelLocationGet(s_WorldObjectModel* model, s_WorldObjectMetadata* metadata, q19_12 posX, q19_12 posZ) // 0x8004287C
{
    s_MapChunk* closestChunks[4];
    q19_12      distsToEdges[4];
    q23_8       geomX;
    q23_8       geomZ;
    s32         chunkX;
    s32         chunkZ;
    q19_12      curDistToEdge;
    s32         i;
    s32         j;
    s32         k;
    s32         chunkCount;
    s_MapChunk* curChunk;
    s_PlmLm*    globalLm;

    globalLm = &g_WorldMapWork.globalLm;

    // Convert position to geometry space.
    geomX = Q12_TO_Q8(posX);
    geomZ = Q12_TO_Q8(posZ);

    if (WorldMap_LoadStateGet(globalLm->queueIdx) >= WorldMapLoadState_Loaded &&
        globalLm->lmHdr->isLoaded &&
        Lm_ModelFind(model, g_WorldMapWork.globalLm.lmHdr, metadata))
    {
        return WorldModelLocation_Chunk1;
    }

    chunkX = FLOOR_TO_STEP(geomX, Q8(CHUNK_SIZE));
    chunkZ = FLOOR_TO_STEP(geomZ, Q8(CHUNK_SIZE));

    // Run through active chunks.
    for (curChunk = &g_WorldMapWork.activeChunks[0], chunkCount = 0;
         curChunk < &g_WorldMapWork.activeChunks[g_WorldMapWork.activeChunkCount];
         curChunk++)
    {
        // Check if chunk file is loaded.
        if (WorldMap_LoadStateGet(curChunk->queueIdx) < WorldMapLoadState_Loaded)
        {
            continue;
        }

        // Check if chunk is loaded.
        if (!curChunk->ipdHdr->isLoaded)
        {
            continue;
        }

        // Interior: collect current chunk.
        if (!g_WorldMapWork.isExterior)
        {
            if (curChunk->chunkX == chunkX &&
                curChunk->chunkZ == chunkZ)
            {
                closestChunks[chunkCount] = curChunk;
                chunkCount++;
                break;
            }
        }
        // Exterior: collect 4 closest chunks.
        else
        {
            // Check if chunk is immediate neighbor.
            if (curChunk->chunkX >= (chunkX - 1) && (chunkX + 1) >= curChunk->chunkX &&
                curChunk->chunkZ >= (chunkZ - 1) && (chunkZ + 1) >= curChunk->chunkZ)
            {
                // Check if chunk is closer than any already collected.
                curDistToEdge = WorldMap_DistanceToChunkEdgeGet(geomX, geomZ, curChunk->chunkX, curChunk->chunkZ);
                for (i = 0; i < chunkCount; i++)
                {
                    if (curDistToEdge < distsToEdges[i])
                    {
                        break;
                    }
                }

                // Shift collected chunks to make room for new insertion.
                for (j = chunkCount; j >= (i + 1); j--)
                {
                    distsToEdges[j] = distsToEdges[j - 1];
                    closestChunks[j] = closestChunks[j - 1];
                }

                // Insert chunk.
                chunkCount++;
                distsToEdges[j]  = curDistToEdge;
                closestChunks[j] = curChunk;
            }
        }
    }

    // Find object.
    for (k = 0; k < chunkCount; k++)
    {
        curChunk = closestChunks[k];
        if (Lm_ModelFind(model, curChunk->ipdHdr->lmHdr, metadata))
        {
            return (curChunk - g_WorldMapWork.activeChunks) + WorldModelLocation_Chunk2;
        }
    }

    return WorldModelLocation_None;
}

bool WorldMap_ActiveChunkLoadedCheck(s32 ipdIdx) // 0x80042C04
{
    return WorldMap_ChunkLoadStateGet(&g_WorldMapWork.activeChunks[ipdIdx]) >= MapModelLoadState_Loaded;
}

void WorldMap_ChunkInit(q19_12 curPosX, q19_12 curPosZ, q19_12 projPosX, q19_12 projPosZ) // 0x80042C3C
{
    s32         fullPageTexCount;
    s_MapChunk* curChunk;

    g_WorldMapWork.positionX = projPosX;
    g_WorldMapWork.positionZ = projPosZ;

    if (g_WorldMapWork.globalLm.queueIdx == NO_VALUE)
    {
        g_WorldMapWork.globalLm.queueIdx = Fs_QueueStartRead(g_WorldMapWork.globalLm.fileIdx, g_WorldMapWork.globalLm.lmHdr);
    }

    WorldMap_ChunkLoad(&g_WorldMapWork, curPosX, curPosZ, projPosX, projPosZ);

    if (WorldMap_LoadStateGet(g_WorldMapWork.globalLm.queueIdx) >= WorldMapLoadState_Loaded &&
        !g_WorldMapWork.globalLm.lmHdr->isLoaded)
    {
        fullPageTexCount                            = g_WorldMapWork.chunkTextures.fullPage.count;
        g_WorldMapWork.chunkTextures.fullPage.count = 4;

        Lm_HeaderPtrsInit(g_WorldMapWork.globalLm.lmHdr);
        Lm_MaterialsLoadWithFilter(g_WorldMapWork.globalLm.lmHdr, &g_WorldMapWork.chunkTextures.fullPage,
                                   NULL, g_WorldMapWork.textureFileIdx, BlendMode_Additive);
        Lm_MaterialFlagsApply(g_WorldMapWork.globalLm.lmHdr);

        g_WorldMapWork.chunkTextures.fullPage.count = fullPageTexCount;
    }

    for (curChunk = &g_WorldMapWork.activeChunks[0];
         curChunk < &g_WorldMapWork.activeChunks[g_WorldMapWork.activeChunkCount];
         curChunk++)
    {
        if (WorldMap_LoadStateGet(curChunk->queueIdx) >= WorldMapLoadState_Loaded)
        {
            WorldMap_ChunkPropertiesSet(curChunk->ipdHdr, &g_WorldMapWork.globalLm.lmHdr, 1,
                                        &g_WorldMapWork.chunkTextures.fullPage, &g_WorldMapWork.chunkTextures.halfPage, g_WorldMapWork.textureFileIdx);
            func_80044044(curChunk->ipdHdr, curChunk->chunkX, curChunk->chunkZ);
        }
    }
}

q19_12 WorldMap_PaddedDistanceToChunkEdgeGet(q19_12 posX, q19_12 posZ, s32 chunkX, s32 chunkZ, bool isExterior) // 0x80042DE8
{
    q19_12 dist;

    dist = WorldMap_DistanceToChunkEdgeGet(Q12_TO_Q8(posX), Q12_TO_Q8(posZ), chunkX, chunkZ);
    if (isExterior)
    {
        dist -= Q12(1.0f);
        if (dist < Q12(0.0f))
        {
            dist = Q12(0.0f);
        }
    }

    return dist;
}

q19_12 WorldMap_DistanceToChunkEdgeGet(q19_12 posX, q19_12 posZ, s32 chunkX, s32 chunkZ) // 0x80042E2C
{
    #define OUTSIDE_DIST(val, min, max) \
        (((val) < (min)) ? ((min) - (val)) : (((max) <= (val)) ? ((val) - (max)) : 0))

    s32 chunkBoundX;
    s32 chunkBoundZ;
    s32 chunkPosX;
    s32 chunkPosZ;

    // Compute chunk boundary position.
    chunkBoundX = chunkX * Q8(CHUNK_SIZE);
    chunkBoundZ = chunkZ * Q8(CHUNK_SIZE);

    chunkPosX = OUTSIDE_DIST(posX, chunkBoundX, chunkBoundX + Q8(CHUNK_SIZE));
    chunkPosZ = OUTSIDE_DIST(posZ, chunkBoundZ, chunkBoundZ + Q8(CHUNK_SIZE));
    return Vc_VectorMagnitudeCalc(chunkPosX, Q12(0.0f), chunkPosZ);
}

s32 WorldMap_ChunkLoad(s_WorldMapWork* terrain, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1) // 0x80042EBC
{
    s32          chunkX0;
    s32          chunkZ0;
    s32          chunkZ1;
    s32          chunkX1;
    s32          queueIdx;
    s32          projChunkX;
    s32          projChunkZ;
    s32          chunkIdx;
    s32          curQueueIdx;
    s32          curChunkX;
    s32          curChunkZ;
    s_MapChunk*   freeChunk;
    s_IpdHeader* ipdHdr;

    queueIdx = NO_VALUE;

    chunkX0 = FLOOR_TO_STEP(Q12_TO_Q8(posX0), Q8(CHUNK_SIZE));
    chunkZ0 = FLOOR_TO_STEP(Q12_TO_Q8(posZ0), Q8(CHUNK_SIZE));
    chunkX1 = FLOOR_TO_STEP(Q12_TO_Q8(posX1), Q8(CHUNK_SIZE));
    chunkZ1 = FLOOR_TO_STEP(Q12_TO_Q8(posZ1), Q8(CHUNK_SIZE));

    terrain->chunkX = chunkX1;
    terrain->chunkZ = chunkZ1;

    WorldMap_ActiveChunksSample(terrain, posX0, posZ0, posX1, posZ1, terrain->isExterior);
    WorldMap_ChunkMaterialsApply(terrain);

    // Run through close chunk.
    for (curChunkZ = -1; curChunkZ <= 1; curChunkZ++)
    {
        for (curChunkX = -1; curChunkX <= 1; curChunkX++)
        {
            if (terrain->isExterior || (curChunkX == 0 && curChunkZ == 0))
            {
                projChunkZ = chunkZ0 + curChunkZ;
                projChunkX = chunkX0 + curChunkX;
                chunkIdx  = WorldMap_IpdChunkFileIdxGet(projChunkX, projChunkZ);

                if (chunkIdx != NO_VALUE &&
                    WorldMap_PaddedDistanceToChunkEdgeGet(posX0, posZ0, projChunkX, projChunkZ, terrain->isExterior) <= Q12(0.0f) &&
                    !WorldMap_IsChunkPresentCheck(terrain->activeChunks, projChunkX, projChunkZ))
                {
                    freeChunk = WorldMap_FreeChunkSpaceFind(terrain->activeChunks, terrain->isExterior);

                    if (WorldMap_LoadStateGet(freeChunk->queueIdx) >= WorldMapLoadState_Loaded)
                    {
                        ipdHdr = freeChunk->ipdHdr;
                        if (ipdHdr->isLoaded)
                        {
                            Lm_MaterialRefCountDec(ipdHdr->lmHdr);
                        }
                    }

                    curQueueIdx = WorldMap_ChunkLoadStart(freeChunk, chunkIdx, projChunkX, projChunkZ,
                                                posX0, posZ0, posX1, posZ1, terrain->isExterior);
                    if (curQueueIdx != NO_VALUE)
                    {
                        queueIdx = curQueueIdx;
                    }
                }
            }
        }
    }

    return queueIdx;
}

void WorldMap_ActiveChunksSample(s_WorldMapWork* terrain, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior) // 0x800431E4
{
    s_MapChunk* curChunk;

    // Run through active chunks.
    for (curChunk = &terrain->activeChunks[0]; curChunk < &terrain->activeChunks[ACTIVE_CHUNK_COUNT_MAX]; curChunk++)
    {
        if (curChunk->queueIdx == NO_VALUE)
        {
            curChunk->paddedDistanceToEdge0 = INT_MAX;
            curChunk->paddedDistanceToEdge1 = INT_MAX;
        }
        else
        {
            WorldMap_DistanceToEdgeCalc(curChunk, posX0, posZ0, posX1, posZ1, isExterior);
        }

        if (WorldMap_LoadStateGet(curChunk->queueIdx) < WorldMapLoadState_Loaded || !curChunk->ipdHdr->isLoaded)
        {
            curChunk->materialCount = 0;
        }
        else
        {
            curChunk->materialCount = WorldMap_ChunkHalfPageMaterialCountGet(curChunk->ipdHdr);
        }

        if (curChunk->paddedDistanceToEdge0 > Q12(0.0f) && curChunk->paddedDistanceToEdge1 > Q12(0.0f))
        {
            curChunk->outsideCount++;
        }
        else
        {
            curChunk->outsideCount = 0;
        }
    }
}

void WorldMap_DistanceToEdgeCalc(s_MapChunk* chunk, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior) // 0x80043338
{
    chunk->paddedDistanceToEdge0 = WorldMap_PaddedDistanceToChunkEdgeGet(posX0, posZ0, chunk->chunkX, chunk->chunkZ, isExterior);
    chunk->paddedDistanceToEdge1 = WorldMap_PaddedDistanceToChunkEdgeGet(posX1, posZ1, chunk->chunkX, chunk->chunkZ, isExterior);
}

void WorldMap_ChunkMaterialsApply(s_WorldMapWork* terrain) // 0x800433B8
{
    s_MapChunk* curChunk;

    // Run through active chunk.
    for (curChunk = &terrain->activeChunks[0]; curChunk < &terrain->activeChunks[terrain->activeChunkCount]; curChunk++)
    {
        if (WorldMap_LoadStateGet(curChunk->queueIdx) >= WorldMapLoadState_Loaded)
        {
            if (curChunk->ipdHdr->isLoaded &&
                curChunk->paddedDistanceToEdge0 > Q12(0.0f) && curChunk->paddedDistanceToEdge1 > Q12(0.0f))
            {
                Lm_MaterialRefCountDec(curChunk->ipdHdr->lmHdr);
            }
        }
    }

    // Run through active chunk.
    for (curChunk = &terrain->activeChunks[0]; curChunk < &terrain->activeChunks[terrain->activeChunkCount]; curChunk++)
    {
        if (WorldMap_LoadStateGet(curChunk->queueIdx) >= WorldMapLoadState_Loaded)
        {
            if (curChunk->ipdHdr->isLoaded &&
                (curChunk->paddedDistanceToEdge0 <= Q12(0.0f) || curChunk->paddedDistanceToEdge1 <= Q12(0.0f)))
            {
                WorldMap_ChunkMaterialsLoad(curChunk->ipdHdr, &terrain->chunkTextures.fullPage, &terrain->chunkTextures.halfPage, terrain->textureFileIdx);
                Lm_MaterialFlagsApply(curChunk->ipdHdr->lmHdr);
            }
        }
    }
}

s32 WorldMap_IpdChunkFileIdxGet(s32 chunkX, s32 chunkZ) // 0x80043554
{
    // @hack
    return ((s16*)&g_WorldMapWork.chunksGridCenter[chunkZ])[chunkX];
}

bool WorldMap_IsChunkPresentCheck(const s_MapChunk* activeChunks, s32 chunkX, s32 chunkZ) // 0x80043578
{
    s32 i;

    for (i = 0; i < g_WorldMapWork.activeChunkCount; i++)
    {
        if (activeChunks[i].queueIdx != NO_VALUE &&
            chunkX == activeChunks[i].chunkX     &&
            chunkZ == activeChunks[i].chunkZ)
        {
            return true;
        }
    }

    return false;
}

s_MapChunk* WorldMap_FreeChunkSpaceFind(s_MapChunk* activeChunks, bool isExterior)
{
    s32         largestMatCount;
    q19_12      farthestDist;
    q19_12      curDist;
    u32         largestOutsideCount;
    s32         matCount;
    s_MapChunk* curChunk;
    s_MapChunk* activeChunk;

    activeChunk          = NULL;
    largestOutsideCount = 0;
    largestMatCount     = 0;
    farthestDist        = Q12(0.0f);

    // Run through active chunks.
    for (curChunk = activeChunks; curChunk < &activeChunks[g_WorldMapWork.activeChunkCount]; curChunk++)
    {
        if (!isExterior)
        {
            if (curChunk->queueIdx == NO_VALUE)
            {
                activeChunk = curChunk;
                break;
            }
            else
            {
                if (largestOutsideCount < curChunk->outsideCount)
                {
                    largestOutsideCount = curChunk->outsideCount;
                    activeChunk         = curChunk;
                }
            }
        }
        else
        {
            if (curChunk->queueIdx == NO_VALUE)
            {
                matCount = 0;

                if (largestMatCount == 0)
                {
                    curDist = INT_MAX;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                matCount = curChunk->materialCount;

                curDist = curChunk->paddedDistanceToEdge0;
                if (curDist == Q12(0.0f))
                {
                    continue;
                }
            }

            if (largestMatCount < matCount || (matCount == largestMatCount && farthestDist < curDist))
            {
                farthestDist    = curDist;
                activeChunk     = curChunk;
                largestMatCount = matCount;
            }
        }
    }

    return activeChunk;
}

s32 WorldMap_ChunkLoadStart(s_MapChunk* chunk, e_FsFile fileIdx, s32 chunkX, s32 chunkZ, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior) // 0x800436D8
{
    if (fileIdx == NO_VALUE)
    {
        return fileIdx;
    }

    chunk->chunkX   = chunkX;
    chunk->chunkZ   = chunkZ;
    chunk->queueIdx = Fs_QueueStartRead(fileIdx, chunk->ipdHdr);

    WorldMap_DistanceToEdgeCalc(chunk, posX0, posZ0, posX1, posZ1, isExterior);

    return chunk->queueIdx;
}

bool WorldMap_ActiveModelsLoadStateCheck(void) // 0x80043740
{
    s32         i;
    s_MapChunk* curChunk;

    switch (WorldMap_GlobalLmLoadStateGet(&g_WorldMapWork.globalLm))
    {
        case MapModelLoadState_Invalid:
            break;

        case MapModelLoadState_Unloaded:
            return false;

        case MapModelLoadState_Corrupted:
            return false;
    }

    // Run through active chunks.
    for (curChunk = &g_WorldMapWork.activeChunks[0], i = 0;
         i < g_WorldMapWork.activeChunkCount;
         i++, curChunk++)
    {
        switch (WorldMap_ChunkLoadStateGet(curChunk))
        {
            case MapModelLoadState_Invalid:
            case MapModelLoadState_Loaded:
                continue;
        }

        if (curChunk->paddedDistanceToEdge0 <= Q12(0.0f) || curChunk->paddedDistanceToEdge1 <= Q12(0.0f))
        {
            return false;
        }
    }

    return true;
}

bool WorldMap_NextChunkLoadCheck(void) // 0x80043830
{
    s32         loadState;
    s_MapChunk* curChunk;

    // Run through active chunks.
    for (curChunk = &g_WorldMapWork.activeChunks[0];
         curChunk < &g_WorldMapWork.activeChunks[g_WorldMapWork.activeChunkCount];
         curChunk++)
    {
        // Check load state and distance.
        loadState = WorldMap_ChunkLoadStateGet(curChunk);
        if (loadState == MapModelLoadState_Invalid ||
            loadState == MapModelLoadState_Loaded  ||
            (curChunk->paddedDistanceToEdge0 > Q12(0.0f) && curChunk->paddedDistanceToEdge1 > Q12(0.0f)))
        {
            continue;
        }

        // Check if chunk to be loaded is on a actually loaded chunk.
        if (!WorldMap_ChunkPositionMatchCheck(curChunk, &g_WorldMapWork))
        {
            continue;
        }

        // Check if player is approaching the chunk to be loaded.
        if (WorldMap_DistanceToChunkEdgeGet(Q12_TO_Q8(g_WorldMapWork.positionX), Q12_TO_Q8(g_WorldMapWork.positionZ),
                                            curChunk->chunkX, curChunk->chunkZ) <= Q8(4.5f))
        {
            return true;
        }
    }

    return false;
}

bool WorldMap_CloseChunkEdgeCheck(q19_12 posX, q19_12 posZ) // 0x8004393C
{
    s32 chunkX;
    s32 chunkZ;

    chunkX = FLOOR_TO_STEP(Q12_TO_Q8(posX), Q8(CHUNK_SIZE));
    chunkZ = FLOOR_TO_STEP(Q12_TO_Q8(posZ), Q8(CHUNK_SIZE));

    if (g_WorldMapWork.isExterior)
    {
        return WorldMap_DistanceToChunkEdgeGet(Q12_TO_Q8(g_WorldMapWork.positionX), Q12_TO_Q8(g_WorldMapWork.positionZ),
                                          chunkX, chunkZ) <= Q8(4.5f);
    }

    if (chunkX == g_WorldMapWork.chunkX &&
        chunkZ == g_WorldMapWork.chunkZ)
    {
        return true;
    }

    return false;
}

void WorldMap_ChunksDraw(GsOT* ot, bool arg1) // 0x80043A24
{
    s32         loadState;
    s_MapChunk* curChunk;

    loadState = WorldMap_LoadStateGet(g_WorldMapWork.globalLm.queueIdx);

    if (loadState == WorldMapLoadState_Unloaded)
    {
        return;
    }

    if (!(loadState == WorldMapLoadState_Invalid ||
          (loadState == WorldMapLoadState_Loaded && g_WorldMapWork.globalLm.lmHdr->isLoaded)))
    {
        return;
    }

    // Draw active chunks.
    for (curChunk = &g_WorldMapWork.activeChunks[0];
         curChunk < &g_WorldMapWork.activeChunks[g_WorldMapWork.activeChunkCount];
         curChunk++)
    {
        if (WorldMap_ChunkLoadStateGet(curChunk) >= MapModelLoadState_Loaded && WorldMap_ChunkPositionMatchCheck(curChunk, &g_WorldMapWork))
        {
            WorldMap_Draw(curChunk->ipdHdr, g_WorldMapWork.positionX, g_WorldMapWork.positionZ, ot, arg1);
        }
    }
}

bool WorldMap_ChunkPositionMatchCheck(s_MapChunk* chunk, s_WorldMapWork* terrain)
{
    if (terrain->chunkX == chunk->chunkX &&
        terrain->chunkZ == chunk->chunkZ)
    {
        return true;
    }

    return terrain->isExterior != false;
}

bool WorldMap_TextureLoadedCheck(s_IpdHeader* ipdHdr) // 0x80043B70
{
    if (!ipdHdr->isLoaded)
    {
        return false;
    }

    return Lm_IsTextureLoaded(ipdHdr->lmHdr);
}

s_IpdCollisionData* WorldMap_HeaderCollisionDataGet(s_IpdHeader* ipdHdr) // 0x80043BA4
{
    if (ipdHdr->isLoaded)
    {
        return &ipdHdr->collisionData;
    }

    return NULL;
}

void WorldMap_ChunkPropertiesSet(s_IpdHeader* ipdHdr, s_LmHeader** lmHdrs, s32 lmHdrCount,
                                 s_ActiveChunkTextures* fullPageActiveTexs, s_ActiveChunkTextures* halfPageActiveTexs,
                                 e_FsFile fileIdx) // 0x80043BC4
{
    if (ipdHdr->isLoaded)
    {
        return;
    }
    ipdHdr->isLoaded = true;

    WorldMap_ChunkHeaderPtrsInit(ipdHdr);
    Collision_ChunkHeaderPtrsInit(&ipdHdr->collisionData);
    Lm_HeaderPtrsInit(ipdHdr->lmHdr);
    func_8008E4EC(ipdHdr->lmHdr);
    WorldMap_ChunkMaterialsLoad(ipdHdr, fullPageActiveTexs, halfPageActiveTexs, fileIdx);
    Lm_MaterialFlagsApply(ipdHdr->lmHdr);
    WorldMap_ModelLinkObjectLists(ipdHdr, lmHdrs, lmHdrCount);
    WorldMap_ModelBufferLinkObjectLists(ipdHdr, ipdHdr->modelInfos);
}

void WorldMap_ChunkMaterialsLoad(s_IpdHeader* ipdHdr,
                                s_ActiveChunkTextures* fullPageActiveTexs, s_ActiveChunkTextures* halfPageActiveTexs,
                                e_FsFile fileIdx) // 0x80043C7C
{
    if (!ipdHdr->isLoaded)
    {
        return;
    }

    if (fullPageActiveTexs != NULL)
    {
        Lm_MaterialsLoadWithFilter(ipdHdr->lmHdr, fullPageActiveTexs, &LmFilter_IsFullPage, fileIdx, BlendMode_Additive);
    }

    if (halfPageActiveTexs != NULL)
    {
        Lm_MaterialsLoadWithFilter(ipdHdr->lmHdr, halfPageActiveTexs, &LmFilter_IsHalfPage, fileIdx, BlendMode_Additive);
    }
}

s32 WorldMap_ChunkHalfPageMaterialCountGet(s_IpdHeader* ipdHdr) // 0x80043D00
{
    if (!ipdHdr->isLoaded)
    {
        return 0;
    }

    return Lm_MaterialCountGet(LmFilter_IsHalfPage, ipdHdr->lmHdr);
}

bool LmFilter_IsFullPage(s_Material* mat) // 0x80043D44
{
    return !LmFilter_IsHalfPage(mat);
}

/* Not sure what is the significance of textures that end with H.
 * I've looked at all of them and can't find any pattern.
 */
bool LmFilter_IsHalfPage(s_Material* mat) // 0x80043D64
{
    char* charCode;

    for (charCode = &mat->name.str[7]; charCode >= &mat->name.str[0]; charCode--)
    {
        if (*charCode == '\0')
        {
            continue;
        }

        return *charCode == 'H';
    }

    return false;
}

void WorldMap_ChunkHeaderPtrsInit(s_IpdHeader* ipdHdr) // 0x80043DA4
{
    s_IpdModelBuffer* curModelBuf;

    ipdHdr->lmHdr          = (u8*)ipdHdr->lmHdr          + (u32)ipdHdr;
    ipdHdr->modelInfos     = (u8*)ipdHdr->modelInfos     + (u32)ipdHdr;
    ipdHdr->modelBuffers   = (u8*)ipdHdr->modelBuffers   + (u32)ipdHdr;
    ipdHdr->modelOrderList = (u8*)ipdHdr->modelOrderList + (u32)ipdHdr;

    for (curModelBuf = &ipdHdr->modelBuffers[0];
         curModelBuf < &ipdHdr->modelBuffers[ipdHdr->modelBufferCount];
         curModelBuf++)
    {
        curModelBuf->modelInstances   = (u8*)curModelBuf->modelInstances   + (u32)ipdHdr;
        curModelBuf->field_10         = (u8*)curModelBuf->field_10         + (u32)ipdHdr;
        curModelBuf->subcellPositions = (u8*)curModelBuf->subcellPositions + (u32)ipdHdr;
    }
}

void WorldMap_ModelLinkObjectLists(s_IpdHeader* ipdHdr, s_LmHeader** lmHdrs, s32 lmHdrCount) // 0x80043E50
{
    s32             i;
    s32             j;
    s_IpdModelInfo* curModelInfo;

    for (i = 0; i < ipdHdr->modelCount; i++)
    {
        curModelInfo = &ipdHdr->modelInfos[i];

        if (!curModelInfo->isGlobalPlm)
        {
            curModelInfo->modelHdr = LmHeader_ModelHeaderSearch(&curModelInfo->name, ipdHdr->lmHdr);
        }
        else
        {
            for (j = 0; j < lmHdrCount; j++)
            {
                curModelInfo->modelHdr = LmHeader_ModelHeaderSearch(&curModelInfo->name, lmHdrs[j]);
                if (curModelInfo->modelHdr != NULL)
                {
                    break;
                }
            }
        }
    }
}

s_ModelHeader* LmHeader_ModelHeaderSearch(u_Filename* modelName, s_LmHeader* lmHdr) // 0x80043F2C
{
    s32            i;
    s_ModelHeader* modelHeader;

    modelHeader = lmHdr->modelHdrs;

    for (i = 0; i < lmHdr->modelCount; i++, modelHeader++)
    {
        if (!COMPARE_FILENAMES(modelName, &modelHeader->name))
        {
            return modelHeader;
        }
    }

    return NULL;
}

void WorldMap_ModelBufferLinkObjectLists(s_IpdHeader* ipdHdr, s_IpdModelInfo* ipdModelInfos) // 0x80043F88
{
    s_IpdModelBuffer*   curModelBuffer;
    s_IpdModelInstance* curModelInst;

    for (curModelBuffer = ipdHdr->modelBuffers;
         curModelBuffer < &ipdHdr->modelBuffers[ipdHdr->modelBufferCount];
         curModelBuffer++)
    {
        for (curModelInst = &curModelBuffer->modelInstances[0];
             curModelInst < &curModelBuffer->modelInstances[curModelBuffer->modelInstanceCount];
             curModelInst++)
        {
            // TODO: `curModelInst` originally stores model idx. Replace that with pointer to the model's `modelHdr`.
            s32 modelIdx           = (s32)curModelInst->modelHdr;
            curModelInst->modelHdr = ipdModelInfos[modelIdx].modelHdr;
        }
    }
}

void func_80044044(s_IpdHeader* ipd, s32 chunkX, s32 chunkZ) // 0x80044044
{
    s32 prevChunkX;
    s32 prevChunkZ;

    prevChunkX = ipd->chunkX;
    prevChunkZ = ipd->chunkZ;

    ipd->chunkX                   = chunkX;
    ipd->chunkZ                   = chunkZ;
    ipd->collisionData.positionX += (chunkX - prevChunkX) * Q8(CHUNK_SIZE);
    ipd->collisionData.positionZ += (chunkZ - prevChunkZ) * Q8(CHUNK_SIZE);
}

void WorldMap_Draw(s_IpdHeader* ipdHdr, q19_12 posX, q19_12 posZ, GsOT* ot, bool arg4) // 0x80044090
{
    // TODO: Rename `CHUNK_SUBCELL_SIZE`
    #define CHUNK_SUBCELL_SIZE Q8(8.0f)
    
    s_ModelInfo         modelInfo;
    GsCOORDINATE2       modelCoord;
    MATRIX              viewMat;
    MATRIX              worldMat;
    s32                 geomX;
    s32                 geomZ;
    q23_8               chunkBoundZ;
    q23_8               chunkBoundX;
    s32                 subcellZ;
    s32                 subcellX;
    s32                 i;
    s_IpdModelBuffer*   modelBuffer;
    s_IpdModelInstance* curModelInst;
    u8*                 temp_fp;
    SVECTOR*            curUnk;

    // Convert position to geometry space.
    geomX = Q12_TO_Q8(posX);
    geomZ = Q12_TO_Q8(posZ);

    // Compute chunk boundary position.
    chunkBoundX = ipdHdr->chunkX * Q8(CHUNK_SIZE);
    chunkBoundZ = ipdHdr->chunkZ * Q8(CHUNK_SIZE);

    // Compute subcells.
    subcellX = FLOOR_TO_STEP(geomX - chunkBoundX, CHUNK_SUBCELL_SIZE);
    subcellZ = FLOOR_TO_STEP(geomZ - chunkBoundZ, CHUNK_SUBCELL_SIZE);
    subcellX = MAX(subcellX, 0);
    subcellZ = MAX(subcellZ, 0);
    subcellX = MIN(subcellX, 4);
    subcellZ = MIN(subcellZ, 4);

    modelInfo.coord   = &modelCoord;
    modelCoord.flg    = true;
    modelInfo.field_0 = 0;
    modelCoord.super  = NULL;

    temp_fp = &ipdHdr->textureCount + (subcellZ * 10) + (subcellX * 2);
    for (i = temp_fp[0]; i < (temp_fp[1] + temp_fp[0]); i++)
    {
        modelBuffer = &ipdHdr->modelBuffers[ipdHdr->modelOrderList[i]];

        if (!WorldMap_SubcellVisibleCheck(modelBuffer, geomX - chunkBoundX, geomZ - chunkBoundZ, chunkBoundX, chunkBoundZ))
        {
            continue;
        }

        for (curModelInst = modelBuffer->modelInstances;
             curModelInst < &modelBuffer->modelInstances[modelBuffer->modelInstanceCount];
             curModelInst++)
        {
            modelInfo.modelHdr = curModelInst->modelHdr;
            if (modelInfo.modelHdr != NULL)
            {
                // Set model matrix.
                modelCoord.workm = curModelInst->mat;

                // Offset model on XZ plane.
                modelCoord.workm.t[0] += chunkBoundX;
                modelCoord.workm.t[2] += chunkBoundZ;

                Vw_CoordToWorldAndViewMatrices(&modelCoord, &worldMat, &viewMat);
                func_80057090(&modelInfo, ot, arg4, &viewMat, &worldMat, 0);
            }
        }

        for (curUnk = modelBuffer->field_10; curUnk < &modelBuffer->field_10[modelBuffer->field_1]; curUnk++)
        {
            switch ((s8)curUnk->pad) // TODO: Must be another field.
            {
                case 0:
                    Gfx_BillboardDraw(1, Q8_TO_Q12(curUnk->vx + chunkBoundX), Q8_TO_Q12(curUnk->vy), Q8_TO_Q12(curUnk->vz + chunkBoundZ), ot, arg4);
                    break;

                case 1:
                    Gfx_BillboardDraw(2, Q8_TO_Q12(curUnk->vx + chunkBoundX), Q8_TO_Q12(curUnk->vy), Q8_TO_Q12(curUnk->vz + chunkBoundZ), ot, arg4);
                    break;
            }
        }
    }

    #undef CHUNK_SUBCELL_SIZE
}

bool WorldMap_SubcellVisibleCheck(s_IpdModelBuffer* modelBuf, q7_8 subcellX, q7_8 subcellZ, q23_8 posX, q23_8 posZ) // 0x80044420
{
    GsCOORDINATE2 viewCoord;
    MATRIX        viewMat;
    SVECTOR*      curSubcellPos; // TODO: Wrong struct.

    // Run through subcell positions.
    for (curSubcellPos = modelBuf->subcellPositions;
         curSubcellPos < &modelBuf->subcellPositions[modelBuf->subcellCount];
         curSubcellPos++)
    {
        if (curSubcellPos->vx < subcellX          &&
            subcellX          < curSubcellPos->vy &&
            curSubcellPos->vz < subcellZ)
        {
            if (subcellZ < curSubcellPos->pad) // TODO: `pad` access indicates different struct.
            {
                viewCoord.flg   = true;
                viewCoord.super = NULL;
                viewCoord.workm = GsIDMATRIX;

                viewCoord.workm.t[0] = posX;
                viewCoord.workm.t[1] = Q8(0.0f);
                viewCoord.workm.t[2] = posZ;

                Vw_CoordToViewSpaceMatrix(&viewCoord, &viewMat);
                return Vw_AabbVisibleInFrustumCheck(&viewMat,
                                                    modelBuf->minX, Q8(-8.0f), modelBuf->minZ,
                                                    modelBuf->maxX, Q8(4.0f), modelBuf->maxZ,
                                                    Q8(25.0f), g_GameWork.gsScreenHeight);
            }
        }
    }

    return false;
}

