#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

static s_MapTerrain g_MapTerrain;

static u32 Ipd_ChunkLoadStateGet(s32 queueIdx) // 0x80041ADC
{
    if (queueIdx == NO_VALUE)
    {
        return ChunkLoadState_Invalid;
    }
    else if (!Fs_QueueIsEntryLoaded(queueIdx))
    {
        return ChunkLoadState_Unloaded;
    }

    return ChunkLoadState_Loaded;
}

u32 Ipd_LoadStateGet(s_Chunk* chunk) // 0x80041B1C
{
    s32 loadState;
    s32 loadStateCpy;

    loadState    = Ipd_ChunkLoadStateGet(chunk->queueIdx);
    loadStateCpy = loadState;

    if (loadStateCpy == ChunkLoadState_Unloaded)
    {
        return StaticModelLoadState_Unloaded;
    }
    else if (loadStateCpy == ChunkLoadState_Invalid ||
             loadState    != ChunkLoadState_Loaded)
    {
        return StaticModelLoadState_Invalid;
    }
    else if (chunk->ipdHdr->isLoaded && Ipd_IsTextureLoaded(chunk->ipdHdr))
    {
        return StaticModelLoadState_Loaded;
    }

    return StaticModelLoadState_Corrupted;
}

u32 Ipd_LmLoadStateGet(s_IpdLm* globalLm) // 0x80041BA0
{
    s32 loadState;
    s32 loadStateCpy;

    loadState    = Ipd_ChunkLoadStateGet(globalLm->queueIdx);
    loadStateCpy = loadState;

    if (loadStateCpy == ChunkLoadState_Unloaded)
    {
        return StaticModelLoadState_Unloaded;
    }
    else if (loadStateCpy == ChunkLoadState_Invalid ||
             loadState    != ChunkLoadState_Loaded)
    {
        return StaticModelLoadState_Invalid;
    }
    else if (globalLm->lmHdr->isLoaded && Lm_IsTextureLoaded(globalLm->lmHdr))
    {
        return StaticModelLoadState_Loaded;
    }

    return StaticModelLoadState_Corrupted;
}

void Ipd_Init(s_LmHeader* lmHdr, s_IpdHeader* ipdBuf, s32 ipdBufSize) // 0x80041C24
{
    bzero(&g_MapTerrain, sizeof(s_MapTerrain));
    Ipd_LmInit(&g_MapTerrain.globalLm, lmHdr);

    g_MapTerrain.chunkBuffer      = ipdBuf;
    g_MapTerrain.chunkBufferSize  = ipdBufSize;
    g_MapTerrain.activeChunkCount = 0;
    g_MapTerrain.isExterior       = true;

    Ipd_ChunkQueueIdxsClear(g_MapTerrain.activeChunks, 4);
    Ipd_TexturesInit();
    Ipd_CollisionDataReset();
}

void Ipd_LmInit(s_IpdLm* globalLm, s_LmHeader* lmHdr) // 0x80041CB4
{
    globalLm->lmHdr = lmHdr;
    Ipd_LmHeaderInit(lmHdr);

    globalLm->queueIdx = 0;
    globalLm->fileIdx  = NO_VALUE;
}

void Ipd_LmHeaderInit(s_LmHeader* lmHdr) // 0x80041CEC
{
    lmHdr->magic         = LM_HEADER_MAGIC;
    lmHdr->version       = LM_VERSION;
    lmHdr->isLoaded      = true;
    lmHdr->materialCount = 0;
    lmHdr->modelCount    = 0;
}

void Ipd_ChunkQueueIdxsClear(s_Chunk* chunks, s32 chunkCount) // 0x80041D10
{
    s_Chunk* curChunk;

    for (curChunk = &chunks[0]; curChunk < &chunks[chunkCount]; curChunk++)
    {
        curChunk->queueIdx = NO_VALUE;
    }
}

void Ipd_TexturesInit(void) // 0x80041D48
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

        Texture_Init(&g_MapTerrain.chunkTextures.fullPageTextures[i], NULL, 0, y, 0, 0, x, j);
    }

    Textures_ActiveTex_CountReset(&g_MapTerrain.chunkTextures.fullPage);
    Textures_ActiveTex_PutTextures(&g_MapTerrain.chunkTextures.fullPage, g_MapTerrain.chunkTextures.fullPageTextures, 8);

    // Run through texture pages.
    for (i = 0, y = 26, j = 0; i < 2; i++, x += 16)
    {
        Texture_Init(&g_MapTerrain.chunkTextures.halfPageTextures[i], NULL, 0, y, (i & 0x1) * 32, 0, x, j);
        if (i & 0x1)
        {
            y++;
        }
    }

    Textures_ActiveTex_CountReset(&g_MapTerrain.chunkTextures.halfPage);
    Textures_ActiveTex_PutTextures(&g_MapTerrain.chunkTextures.halfPage, g_MapTerrain.chunkTextures.halfPageTextures, 2);
}

void Ipd_CollisionDataReset(void) // 0x80041E98
{
    bzero(&g_MapTerrain.collisionData, sizeof(s_IpdCollisionData));
    g_MapTerrain.collisionData.subcellSize = Q8(2.0f);
}

void Ipd_ChunkSet(s16 ipdFileIdx, s32 cellX, s32 cellZ) // 0x80041ED0
{
    s_Chunk*     curChunk;
    s_IpdHeader* ipdHdr;

    ((s16*)&g_MapTerrain.chunkGridCenter[cellZ])[cellX] = ipdFileIdx;

    // Run through active chunks.
    for (curChunk = &g_MapTerrain.activeChunks[0];
         curChunk < &g_MapTerrain.activeChunks[g_MapTerrain.activeChunkCount];
         curChunk++)
    {
        // Check if cell coordiantes match.
        if (curChunk->cellX != cellX ||
            curChunk->cellZ != cellZ)
        {
            continue;
        }

        // Check if chunk is loaded.
        if (Ipd_ChunkLoadStateGet(curChunk->queueIdx) >= ChunkLoadState_Loaded)
        {
            ipdHdr = curChunk->ipdHdr;
            if (ipdHdr->isLoaded)
            {
                Lm_MaterialRefCountDec(ipdHdr->lmHdr);
            }
        }

        curChunk->queueIdx = NO_VALUE;
    }
}

void Ipd_ActiveChunksClear(void) // 0x80041FF0
{
    Ipd_ChunksClear(&g_MapTerrain, g_MapTerrain.activeChunkCount);
}

void Ipd_TexturesRefClear(void) // 0x8004201C
{
    s_Texture* curTex;

    // Clear ful-page textures.
    curTex = &g_MapTerrain.chunkTextures.fullPageTextures[0];
    while (curTex < (&g_MapTerrain.chunkTextures.fullPageTextures[FULL_PAGE_CHUNK_TEXTURE_COUNT_MAX]))
    {
        if (curTex->refCount == 0)
        {
            Texture_RefClear(curTex);
        }

        curTex++;
    }

    // Clear half-page textures.
    curTex = &g_MapTerrain.chunkTextures.halfPageTextures[0];
    while (curTex < (&g_MapTerrain.chunkTextures.halfPageTextures[HALF_PAGE_CHUNK_TEXTURE_COUNT_MAX]))
    {
        if (curTex->refCount == 0)
        {
            Texture_RefClear(curTex);
        }

        curTex++;
    }
}

void Ipd_WorldReset(void) // 0x800420C0
{
    Ipd_LmReset();
    Ipd_ChunksClear(&g_MapTerrain, g_MapTerrain.activeChunkCount);
    Ipd_TexturesInit();
}

void Ipd_LmReset(void) // 0x800420FC
{
    s_IpdLm* globalLm;

    globalLm = &g_MapTerrain.globalLm;

    if (Ipd_ChunkLoadStateGet(globalLm->queueIdx) >= ChunkLoadState_Loaded &&
        globalLm->lmHdr->isLoaded)
    {
        Lm_MaterialRefCountDec(g_MapTerrain.globalLm.lmHdr);
    }

    Ipd_LmInit(&g_MapTerrain.globalLm, g_MapTerrain.globalLm.lmHdr);
}

s_Texture* Ipd_TextureInfoGet(char* texName) // 0x80042178
{
    s_Texture* tex;

    // Find full-page texture.
    tex = Textures_ActiveTex_FindTexture(texName, &g_MapTerrain.chunkTextures.fullPage);
    if (tex != NULL)
    {
        return tex;
    }

    // Find half-page texture.
    tex = Textures_ActiveTex_FindTexture(texName, &g_MapTerrain.chunkTextures.halfPage);
    if (tex != NULL)
    {
        return tex;
    }

    return NULL;
}

void Ipd_MapFileInfoSet(char* mapTag, e_FsFile plmIdx, s32 activeIpdCount, bool isExterior,
                        e_FsFile ipdFileIdx, e_FsFile texFileIdx) // 0x800421D8
{
    g_MapTerrain.isExterior     = isExterior;
    g_MapTerrain.textureFileIdx = texFileIdx;

    if (plmIdx != NO_VALUE && plmIdx != g_MapTerrain.globalLm.fileIdx)
    {
        if (Ipd_ChunkLoadStateGet(g_MapTerrain.globalLm.queueIdx) >= ChunkLoadState_Loaded &&
            g_MapTerrain.globalLm.lmHdr->isLoaded)
        {
            Lm_MaterialRefCountDec(g_MapTerrain.globalLm.lmHdr);
        }

        g_MapTerrain.globalLm.fileIdx  = plmIdx;
        g_MapTerrain.globalLm.queueIdx = NO_VALUE;
    }

    if (g_MapTerrain.activeChunkCount != activeIpdCount || strcmp(mapTag, g_MapTerrain.mapTag) != 0)
    {
        Ipd_ChunksClear(&g_MapTerrain, activeIpdCount);

        g_MapTerrain.activeChunkCount = activeIpdCount;
        g_MapTerrain.ipdFileIdx       = ipdFileIdx;
        strcpy(g_MapTerrain.mapTag, mapTag);

        g_MapTerrain.mapTagSize = strlen(mapTag);
        Ipd_MakeGrid(&g_MapTerrain, mapTag, ipdFileIdx);
    }
}

void Ipd_ChunksClear(s_MapTerrain* terrain, s32 activeChunksCount) // 0x80042300
{
    s32          chunkSize;
    s32          i;
    s_Chunk*     curChunk;
    s_IpdHeader* chunkBuffer;
    s_IpdHeader* ipdHdr1;

    chunkBuffer = terrain->chunkBuffer;
    chunkSize  = (terrain->chunkBufferSize / activeChunksCount) & ~0x3;

    for (i = 0; i < ACTIVE_CHUNK_COUNT_MAX; i++, *(u8**)&chunkBuffer += chunkSize)
    {
        curChunk = &terrain->activeChunks[i];

        if (Ipd_ChunkLoadStateGet(curChunk->queueIdx) >= ChunkLoadState_Loaded)
        {
            ipdHdr1 = curChunk->ipdHdr;
            if (ipdHdr1->isLoaded)
            {
                Lm_MaterialRefCountDec(ipdHdr1->lmHdr);
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

void Ipd_MakeGrid(s_MapTerrain* terrain, char* mapTag, e_FsFile fileIdxStart) // 0x800423F4
{
    char           filename[256];
    s32            x;
    s32            z;
    s32            i;
    char*          filenameSuffix;
    s_ChunkColumn* col;

    terrain->chunkGridCenter = (s_ChunkColumn*)(&terrain->chunkGrid[8].idx[8]);

    for (z = -8; z < 11; z++)
    {
        for (x = -8; x < 8; x++)
        {
            ((s16*)&terrain->chunkGridCenter[z])[x] = NO_VALUE;
        }
    }

    // Run through all game files.
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
                    col         = &terrain->chunkGridCenter[z];
                    col->idx[x] = i;
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

s_IpdCollisionData** Ipd_ActiveChunksCollisionDataGet(s32* collDataIdx) // 0x800425D8
{
    s_Chunk*                   curChunk;
    s_IpdCollisionData*        collData;
    s_IpdHeader*               ipdHdr;
    static s_IpdCollisionData* activeChunksCollData[4];

    curChunk     = g_MapTerrain.activeChunks;
    *collDataIdx = 0;

    // Run through active chunks.
    while (curChunk < &g_MapTerrain.activeChunks[g_MapTerrain.activeChunkCount])
    {
        // Check if chunk is loaded.
        if (Ipd_ChunkLoadStateGet(curChunk->queueIdx) >= ChunkLoadState_Loaded)
        {
            ipdHdr = curChunk->ipdHdr;
            if (ipdHdr->isLoaded)
            {
                collData = Ipd_HeaderCollisionDataGet(ipdHdr);
                if (collData != NULL)
                {
                    activeChunksCollData[(*collDataIdx)++] = collData;
                }
            }
        }

        curChunk++;
    }

    return &activeChunksCollData[0];
}

s_IpdCollisionData* Ipd_CollisionDataGet(q19_12 posX, q19_12 posZ) // 0x800426E4
{
    s32          geomX;
    s32          geomZ;
    s32          cellX;
    s32          cellZ;
    s_IpdHeader* ipdHdr;
    s_Chunk*     curChunk;

    // Convert position to geometry space.
    geomX = Q12_TO_Q8(posX);
    geomZ = Q12_TO_Q8(posZ);

    // Compute cell coordinates.
    cellX = FLOOR_TO_STEP(geomX, Q8(CHUNK_CELL_SIZE));
    cellZ = FLOOR_TO_STEP(geomZ, Q8(CHUNK_CELL_SIZE));

    // Run through active chunks.
    for (curChunk = &g_MapTerrain.activeChunks[0];
         curChunk < &g_MapTerrain.activeChunks[g_MapTerrain.activeChunkCount];
         curChunk++)
    {
        // Check if chunk is loaded.
        if (Ipd_ChunkLoadStateGet(curChunk->queueIdx) < ChunkLoadState_Loaded)
        {
            continue;
        }

        // Check if chunk matches cell coordinates.
        ipdHdr = curChunk->ipdHdr;
        if (ipdHdr->isLoaded &&
            curChunk->cellX == cellX && curChunk->cellZ == cellZ)
        {
            return &ipdHdr->collisionData;
        }
    }

    // Fallback.
    if (((s16*)(&g_MapTerrain.chunkGridCenter[cellZ]))[cellX] != NO_VALUE)
    {
        return NULL;
    }
    else
    {
        return &g_MapTerrain.collisionData;
    }
}

s32 Map_WorldObjectModelLocationGet(s_WorldObjectModel* model, s_WorldObjectMetadata* metadata, q19_12 posX, q19_12 posZ) // 0x8004287C
{
    s_Chunk*    closestChunks[4];
    q19_12      distsToEdges[4];
    q23_8       geomX;
    q23_8       geomZ;
    s32         cellX;
    s32         cellZ;
    q19_12      curDistToEdge;
    s32         i;
    s32         j;
    s32         k;
    s32         chunkCount;
    s_Chunk*    curChunk;
    s_IpdLm* globalLm;

    globalLm = &g_MapTerrain.globalLm;

    // Convert position to geometry space.
    geomX = Q12_TO_Q8(posX);
    geomZ = Q12_TO_Q8(posZ);

    if (Ipd_ChunkLoadStateGet(globalLm->queueIdx) >= ChunkLoadState_Loaded &&
        globalLm->lmHdr->isLoaded &&
        Lm_ModelFind(model, g_MapTerrain.globalLm.lmHdr, metadata))
    {
        return WorldModelLocation_Chunk1;
    }

    cellX = FLOOR_TO_STEP(geomX, Q8(CHUNK_CELL_SIZE));
    cellZ = FLOOR_TO_STEP(geomZ, Q8(CHUNK_CELL_SIZE));

    // Run through active chunks.
    for (curChunk = &g_MapTerrain.activeChunks[0], chunkCount = 0;
         curChunk < &g_MapTerrain.activeChunks[g_MapTerrain.activeChunkCount];
         curChunk++)
    {
        // Check if chunk file is loaded.
        if (Ipd_ChunkLoadStateGet(curChunk->queueIdx) < ChunkLoadState_Loaded)
        {
            continue;
        }

        // Check if chunk is loaded.
        if (!curChunk->ipdHdr->isLoaded)
        {
            continue;
        }

        // Interior: collect current chunk.
        if (!g_MapTerrain.isExterior)
        {
            if (curChunk->cellX == cellX &&
                curChunk->cellZ == cellZ)
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
            if (curChunk->cellX >= (cellX - 1) && (cellX + 1) >= curChunk->cellX &&
                curChunk->cellZ >= (cellZ - 1) && (cellZ + 1) >= curChunk->cellZ)
            {
                // Check if chunk is closer than any already collected.
                curDistToEdge = Map_DistanceToChunkEdgeGet(geomX, geomZ, curChunk->cellX, curChunk->cellZ);
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
                    distsToEdges[j]  = distsToEdges[j - 1];
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
            return (curChunk - g_MapTerrain.activeChunks) + WorldModelLocation_Chunk2;
        }
    }

    return WorldModelLocation_None;
}

bool Ipd_IsLoaded(s32 ipdIdx) // 0x80042C04
{
    return Ipd_LoadStateGet(&g_MapTerrain.activeChunks[ipdIdx]) >= StaticModelLoadState_Loaded;
}

void Ipd_ChunkInit(q19_12 curPosX, q19_12 curPosZ, q19_12 projPosX, q19_12 projPosZ) // 0x80042C3C
{
    s32      fullPageTexCount;
    s_Chunk* curChunk;

    g_MapTerrain.positionX = projPosX;
    g_MapTerrain.positionZ = projPosZ;

    if (g_MapTerrain.globalLm.queueIdx == NO_VALUE)
    {
        g_MapTerrain.globalLm.queueIdx = Fs_QueueStartRead(g_MapTerrain.globalLm.fileIdx, g_MapTerrain.globalLm.lmHdr);
    }

    Map_ChunkLoad(&g_MapTerrain, curPosX, curPosZ, projPosX, projPosZ);

    if (Ipd_ChunkLoadStateGet(g_MapTerrain.globalLm.queueIdx) >= ChunkLoadState_Loaded &&
        !g_MapTerrain.globalLm.lmHdr->isLoaded)
    {
        fullPageTexCount                          = g_MapTerrain.chunkTextures.fullPage.count;
        g_MapTerrain.chunkTextures.fullPage.count = 4;

        Lm_HeaderPtrsInit(g_MapTerrain.globalLm.lmHdr);
        Lm_MaterialsLoadWithFilter(g_MapTerrain.globalLm.lmHdr, &g_MapTerrain.chunkTextures.fullPage,
                                   NULL, g_MapTerrain.textureFileIdx, BlendMode_Additive);
        Lm_MaterialFlagsApply(g_MapTerrain.globalLm.lmHdr);

        g_MapTerrain.chunkTextures.fullPage.count = fullPageTexCount;
    }

    for (curChunk = &g_MapTerrain.activeChunks[0];
         curChunk < &g_MapTerrain.activeChunks[g_MapTerrain.activeChunkCount];
         curChunk++)
    {
        if (Ipd_ChunkLoadStateGet(curChunk->queueIdx) >= ChunkLoadState_Loaded)
        {
            Ipd_LoadedChunkInit(curChunk->ipdHdr, &g_MapTerrain.globalLm.lmHdr, 1,
                                &g_MapTerrain.chunkTextures.fullPage, &g_MapTerrain.chunkTextures.halfPage, g_MapTerrain.textureFileIdx);
            func_80044044(curChunk->ipdHdr, curChunk->cellX, curChunk->cellZ);
        }
    }
}

q19_12 Map_PaddedDistanceToChunkEdgeGet(q19_12 posX, q19_12 posZ, s32 cellX, s32 cellZ, bool isExterior) // 0x80042DE8
{
    q19_12 dist;

    dist = Map_DistanceToChunkEdgeGet(Q12_TO_Q8(posX), Q12_TO_Q8(posZ), cellX, cellZ);
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

q19_12 Map_DistanceToChunkEdgeGet(q19_12 posX, q19_12 posZ, s32 cellX, s32 cellZ) // 0x80042E2C
{
    #define OUTSIDE_DIST(val, min, max) \
        (((val) < (min)) ? ((min) - (val)) : (((max) <= (val)) ? ((val) - (max)) : 0))

    s32 cellBoundX;
    s32 cellBoundZ;
    s32 cellPosX;
    s32 cellPosZ;

    // Compute cell boundary position.
    cellBoundX = cellX * Q8(CHUNK_CELL_SIZE);
    cellBoundZ = cellZ * Q8(CHUNK_CELL_SIZE);

    cellPosX = OUTSIDE_DIST(posX, cellBoundX, cellBoundX + Q8(CHUNK_CELL_SIZE));
    cellPosZ = OUTSIDE_DIST(posZ, cellBoundZ, cellBoundZ + Q8(CHUNK_CELL_SIZE));
    return Vc_VectorMagnitudeCalc(cellPosX, Q12(0.0f), cellPosZ);
}

s32 Map_ChunkLoad(s_MapTerrain* terrain, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1) // 0x80042EBC
{
    s32          cellX0;
    s32          cellZ0;
    s32          cellZ1;
    s32          cellX1;
    s32          queueIdx;
    s32          projCellX;
    s32          projCellZ;
    s32          chunkIdx;
    s32          curQueueIdx;
    s32          curCellX;
    s32          curCellZ;
    s_Chunk*     freeChunk;
    s_IpdHeader* ipdHdr;

    queueIdx = NO_VALUE;

    cellX0 = FLOOR_TO_STEP(Q12_TO_Q8(posX0), Q8(CHUNK_CELL_SIZE));
    cellZ0 = FLOOR_TO_STEP(Q12_TO_Q8(posZ0), Q8(CHUNK_CELL_SIZE));
    cellX1 = FLOOR_TO_STEP(Q12_TO_Q8(posX1), Q8(CHUNK_CELL_SIZE));
    cellZ1 = FLOOR_TO_STEP(Q12_TO_Q8(posZ1), Q8(CHUNK_CELL_SIZE));

    terrain->cellX = cellX1;
    terrain->cellZ = cellZ1;

    Ipd_ActiveChunksSample(terrain, posX0, posZ0, posX1, posZ1, terrain->isExterior);
    Ipd_ChunkMaterialsApply(terrain);

    // Run through neighboring cells.
    for (curCellZ = -1; curCellZ <= 1; curCellZ++)
    {
        for (curCellX = -1; curCellX <= 1; curCellX++)
        {
            if (terrain->isExterior || (curCellX == 0 && curCellZ == 0))
            {
                projCellZ = cellZ0 + curCellZ;
                projCellX = cellX0 + curCellX;
                chunkIdx  = Map_IpdChunkFileIdxGet(projCellX, projCellZ);

                if (chunkIdx != NO_VALUE &&
                    Map_PaddedDistanceToChunkEdgeGet(posX0, posZ0, projCellX, projCellZ, terrain->isExterior) <= Q12(0.0f) &&
                    !Map_IsIpdPresentCheck(terrain->activeChunks, projCellX, projCellZ))
                {
                    freeChunk = Ipd_FreeChunkFind(terrain->activeChunks, terrain->isExterior);

                    if (Ipd_ChunkLoadStateGet(freeChunk->queueIdx) >= ChunkLoadState_Loaded)
                    {
                        ipdHdr = freeChunk->ipdHdr;
                        if (ipdHdr->isLoaded)
                        {
                            Lm_MaterialRefCountDec(ipdHdr->lmHdr);
                        }
                    }

                    curQueueIdx = Ipd_LoadStart(freeChunk, chunkIdx,
                                                projCellX, projCellZ,
                                                posX0, posZ0,
                                                posX1, posZ1,
                                                terrain->isExterior);
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

void Ipd_ActiveChunksSample(s_MapTerrain* terrain, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior) // 0x800431E4
{
    s_Chunk* curChunk;

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
            Ipd_DistanceToEdgeCalc(curChunk, posX0, posZ0, posX1, posZ1, isExterior);
        }

        if (Ipd_ChunkLoadStateGet(curChunk->queueIdx) < ChunkLoadState_Loaded || !curChunk->ipdHdr->isLoaded)
        {
            curChunk->materialCount = 0;
        }
        else
        {
            curChunk->materialCount = Ipd_HalfPageMaterialCountGet(curChunk->ipdHdr);
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

void Ipd_DistanceToEdgeCalc(s_Chunk* chunk, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior) // 0x80043338
{
    chunk->paddedDistanceToEdge0 = Map_PaddedDistanceToChunkEdgeGet(posX0, posZ0, chunk->cellX, chunk->cellZ, isExterior);
    chunk->paddedDistanceToEdge1 = Map_PaddedDistanceToChunkEdgeGet(posX1, posZ1, chunk->cellX, chunk->cellZ, isExterior);
}

void Ipd_ChunkMaterialsApply(s_MapTerrain* terrain) // 0x800433B8
{
    s_Chunk* curChunk;

    // Run through active chunks.
    for (curChunk = &terrain->activeChunks[0]; curChunk < &terrain->activeChunks[terrain->activeChunkCount]; curChunk++)
    {
        if (Ipd_ChunkLoadStateGet(curChunk->queueIdx) >= ChunkLoadState_Loaded)
        {
            if (curChunk->ipdHdr->isLoaded &&
                curChunk->paddedDistanceToEdge0 > Q12(0.0f) && curChunk->paddedDistanceToEdge1 > Q12(0.0f))
            {
                Lm_MaterialRefCountDec(curChunk->ipdHdr->lmHdr);
            }
        }
    }

    // Run through active chunks.
    for (curChunk = &terrain->activeChunks[0]; curChunk < &terrain->activeChunks[terrain->activeChunkCount]; curChunk++)
    {
        if (Ipd_ChunkLoadStateGet(curChunk->queueIdx) >= ChunkLoadState_Loaded)
        {
            if (curChunk->ipdHdr->isLoaded &&
                (curChunk->paddedDistanceToEdge0 <= Q12(0.0f) || curChunk->paddedDistanceToEdge1 <= Q12(0.0f)))
            {
                Ipd_MaterialsLoad(curChunk->ipdHdr, &terrain->chunkTextures.fullPage, &terrain->chunkTextures.halfPage, terrain->textureFileIdx);
                Lm_MaterialFlagsApply(curChunk->ipdHdr->lmHdr);
            }
        }
    }
}

s32 Map_IpdChunkFileIdxGet(s32 cellX, s32 cellZ) // 0x80043554
{
    // @hack
    return ((s16*)&g_MapTerrain.chunkGridCenter[cellZ])[cellX];
}

bool Map_IsIpdPresentCheck(const s_Chunk* activeChunks, s32 cellX, s32 cellZ) // 0x80043578
{
    s32 i;

    for (i = 0; i < g_MapTerrain.activeChunkCount; i++)
    {
        if (activeChunks[i].queueIdx != NO_VALUE &&
            cellX == activeChunks[i].cellX       &&
            cellZ == activeChunks[i].cellZ)
        {
            return true;
        }
    }

    return false;
}

s_Chunk* Ipd_FreeChunkFind(s_Chunk* activeChunks, bool isExterior)
{
    s32      largestMatCount;
    q19_12   farthestDist;
    q19_12   curDist;
    u32      largestOutsideCount;
    s32      matCount;
    s_Chunk* curChunk;
    s_Chunk* activeChunk;

    activeChunk         = NULL;
    largestOutsideCount = 0;
    largestMatCount     = 0;
    farthestDist        = Q12(0.0f);

    // Run through active chunks
    for (curChunk = activeChunks; curChunk < &activeChunks[g_MapTerrain.activeChunkCount]; curChunk++)
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

s32 Ipd_LoadStart(s_Chunk* chunk, e_FsFile fileIdx, s32 cellX, s32 cellZ, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior) // 0x800436D8
{
    if (fileIdx == NO_VALUE)
    {
        return fileIdx;
    }

    chunk->cellX    = cellX;
    chunk->cellZ    = cellZ;
    chunk->queueIdx = Fs_QueueStartRead(fileIdx, chunk->ipdHdr);

    Ipd_DistanceToEdgeCalc(chunk, posX0, posZ0, posX1, posZ1, isExterior);

    return chunk->queueIdx;
}

bool Ipd_ChunksLoadedCheck(void) // 0x80043740
{
    s32      i;
    s_Chunk* curChunk;

    switch (Ipd_LmLoadStateGet(&g_MapTerrain.globalLm))
    {
        case StaticModelLoadState_Invalid:
            break;

        case StaticModelLoadState_Unloaded:
            return false;

        case StaticModelLoadState_Corrupted:
            return false;
    }

    // Run through active chunks.
    for (curChunk = &g_MapTerrain.activeChunks[0], i = 0;
         i < g_MapTerrain.activeChunkCount;
         i++, curChunk++)
    {
        switch (Ipd_LoadStateGet(curChunk))
        {
            case StaticModelLoadState_Invalid:
            case StaticModelLoadState_Loaded:
                continue;
        }

        if (curChunk->paddedDistanceToEdge0 <= Q12(0.0f) || curChunk->paddedDistanceToEdge1 <= Q12(0.0f))
        {
            return false;
        }
    }

    return true;
}

bool Ipd_NextChunkLoadCheck(void) // 0x80043830
{
    s32      loadState;
    s_Chunk* curChunk;

    // Run through active chunks.
    for (curChunk = &g_MapTerrain.activeChunks[0];
         curChunk < &g_MapTerrain.activeChunks[g_MapTerrain.activeChunkCount];
         curChunk++)
    {
        // Check load state and distance.
        loadState = Ipd_LoadStateGet(curChunk);
        if (loadState == StaticModelLoadState_Invalid ||
            loadState == StaticModelLoadState_Loaded  ||
            (curChunk->paddedDistanceToEdge0 > Q12(0.0f) && curChunk->paddedDistanceToEdge1 > Q12(0.0f)))
        {
            continue;
        }

        // Check if chunk is in current cell.
        if (!Ipd_CellPositionMatchCheck(curChunk, &g_MapTerrain))
        {
            continue;
        }

        // Check if player is approaching chunk.
        if (Map_DistanceToChunkEdgeGet(Q12_TO_Q8(g_MapTerrain.positionX), Q12_TO_Q8(g_MapTerrain.positionZ),
                                       curChunk->cellX, curChunk->cellZ) <= Q8(4.5f))
        {
            return true;
        }
    }

    return false;
}

bool Ipd_CloseChunkEdgeCheck(q19_12 posX, q19_12 posZ) // 0x8004393C
{
    s32 cellX;
    s32 cellZ;

    cellX = FLOOR_TO_STEP(Q12_TO_Q8(posX), Q8(CHUNK_CELL_SIZE));
    cellZ = FLOOR_TO_STEP(Q12_TO_Q8(posZ), Q8(CHUNK_CELL_SIZE));

    if (g_MapTerrain.isExterior)
    {
        return Map_DistanceToChunkEdgeGet(Q12_TO_Q8(g_MapTerrain.positionX), Q12_TO_Q8(g_MapTerrain.positionZ),
                                          cellX, cellZ) <= Q8(4.5f);
    }

    if (cellX == g_MapTerrain.cellX &&
        cellZ == g_MapTerrain.cellZ)
    {
        return true;
    }

    return false;
}

void Ipd_ChunksDraw(GsOT* ot, bool arg1) // 0x80043A24
{
    s32      loadState;
    s_Chunk* curChunk;

    loadState = Ipd_ChunkLoadStateGet(g_MapTerrain.globalLm.queueIdx);

    if (loadState == ChunkLoadState_Unloaded)
    {
        return;
    }

    if (!(loadState == ChunkLoadState_Invalid ||
          (loadState == ChunkLoadState_Loaded && g_MapTerrain.globalLm.lmHdr->isLoaded)))
    {
        return;
    }

    // Draw active chunks.
    for (curChunk = &g_MapTerrain.activeChunks[0];
         curChunk < &g_MapTerrain.activeChunks[g_MapTerrain.activeChunkCount];
         curChunk++)
    {
        if (Ipd_LoadStateGet(curChunk) >= StaticModelLoadState_Loaded && Ipd_CellPositionMatchCheck(curChunk, &g_MapTerrain))
        {
            Ipd_ChunkDraw(curChunk->ipdHdr, g_MapTerrain.positionX, g_MapTerrain.positionZ, ot, arg1);
        }
    }
}

bool Ipd_CellPositionMatchCheck(s_Chunk* chunk, s_MapTerrain* terrain)
{
    if (terrain->cellX == chunk->cellX &&
        terrain->cellZ == chunk->cellZ)
    {
        return true;
    }

    return terrain->isExterior != false;
}

bool Ipd_IsTextureLoaded(s_IpdHeader* ipdHdr) // 0x80043B70
{
    if (!ipdHdr->isLoaded)
    {
        return false;
    }

    return Lm_IsTextureLoaded(ipdHdr->lmHdr);
}

s_IpdCollisionData* Ipd_HeaderCollisionDataGet(s_IpdHeader* ipdHdr) // 0x80043BA4
{
    if (ipdHdr->isLoaded)
    {
        return &ipdHdr->collisionData;
    }

    return NULL;
}

void Ipd_LoadedChunkInit(s_IpdHeader* ipdHdr, s_LmHeader** lmHdrs, s32 lmHdrCount,
              s_ActiveChunkTextures* fullPageActiveTexs, s_ActiveChunkTextures* halfPageActiveTexs,
              e_FsFile fileIdx) // 0x80043BC4
{
    if (ipdHdr->isLoaded)
    {
        return;
    }
    ipdHdr->isLoaded = true;

    Ipd_HeaderPtrsInit(ipdHdr);
    Ipd_CollisionPtrsInit(&ipdHdr->collisionData);
    Lm_HeaderPtrsInit(ipdHdr->lmHdr);
    func_8008E4EC(ipdHdr->lmHdr);
    Ipd_MaterialsLoad(ipdHdr, fullPageActiveTexs, halfPageActiveTexs, fileIdx);
    Lm_MaterialFlagsApply(ipdHdr->lmHdr);
    Ipd_HeaderModelLinkObjectLists(ipdHdr, lmHdrs, lmHdrCount);
    Ipd_HeaderModelBufferLinkObjectLists(ipdHdr, ipdHdr->modelInfo);
}

void Ipd_MaterialsLoad(s_IpdHeader* ipdHdr,
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

s32 Ipd_HalfPageMaterialCountGet(s_IpdHeader* ipdHdr) // 0x80043D00
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

void Ipd_HeaderPtrsInit(s_IpdHeader* ipdHdr) // 0x80043DA4
{
    s_IpdModelBuffer* curModelBuf;

    ipdHdr->lmHdr          = (u8*)ipdHdr->lmHdr          + (u32)ipdHdr;
    ipdHdr->modelInfo      = (u8*)ipdHdr->modelInfo      + (u32)ipdHdr;
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

void Ipd_HeaderModelLinkObjectLists(s_IpdHeader* ipdHdr, s_LmHeader** lmHdrs, s32 lmHdrCount) // 0x80043E50
{
    s32             i;
    s32             j;
    s_IpdModelInfo* curModelInfo;

    for (i = 0; i < ipdHdr->modelCount; i++)
    {
        curModelInfo = &ipdHdr->modelInfo[i];

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

void Ipd_HeaderModelBufferLinkObjectLists(s_IpdHeader* ipdHdr, s_IpdModelInfo* ipdModels) // 0x80043F88
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
            curModelInst->modelHdr = ipdModels[modelIdx].modelHdr;
        }
    }
}

void func_80044044(s_IpdHeader* ipd, s32 cellX, s32 cellZ) // 0x80044044
{
    s32 prevCellX;
    s32 prevCellZ;

    prevCellX = ipd->cellX;
    prevCellZ = ipd->cellZ;

    ipd->cellX                    = cellX;
    ipd->cellZ                    = cellZ;
    ipd->collisionData.positionX += (cellX - prevCellX) * Q8(CHUNK_CELL_SIZE);
    ipd->collisionData.positionZ += (cellZ - prevCellZ) * Q8(CHUNK_CELL_SIZE);
}
