#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

void Ipd_ChunkDraw(s_IpdHeader* ipdHdr, q19_12 posX, q19_12 posZ, GsOT* ot, bool arg4) // 0x80044090
{
    #define CHUNK_SUBCELL_SIZE Q8(8.0f)

    s_ModelInfo         modelInfo;
    GsCOORDINATE2       modelCoord;
    MATRIX              viewMat;
    MATRIX              worldMat;
    s32                 geomX;
    s32                 geomZ;
    q23_8               cellBoundZ;
    q23_8               cellBoundX;
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

    // Compute cell boundary position.
    cellBoundX = ipdHdr->cellX * Q12_TO_Q8(CHUNK_CELL_SIZE);
    cellBoundZ = ipdHdr->cellZ * Q12_TO_Q8(CHUNK_CELL_SIZE);

    // Compute subcells.
    subcellX = FLOOR_TO_STEP(geomX - cellBoundX, CHUNK_SUBCELL_SIZE);
    subcellZ = FLOOR_TO_STEP(geomZ - cellBoundZ, CHUNK_SUBCELL_SIZE);
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

        if (!Gfx_ChunkSubcellVisibleCheck(modelBuffer, geomX - cellBoundX, geomZ - cellBoundZ, cellBoundX, cellBoundZ))
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
                modelCoord.workm.t[0] += cellBoundX;
                modelCoord.workm.t[2] += cellBoundZ;

                Vw_CoordToWorldAndViewMatrices(&modelCoord, &worldMat, &viewMat);
                func_80057090(&modelInfo, ot, arg4, &viewMat, &worldMat, 0);
            }
        }

        for (curUnk = modelBuffer->field_10; curUnk < &modelBuffer->field_10[modelBuffer->field_1]; curUnk++)
        {
            switch ((s8)curUnk->pad) // TODO: Must be another field.
            {
                case 0:
                    Gfx_BillboardDraw(1, Q8_TO_Q12(curUnk->vx + cellBoundX), Q8_TO_Q12(curUnk->vy), Q8_TO_Q12(curUnk->vz + cellBoundZ), ot, arg4);
                    break;

                case 1:
                    Gfx_BillboardDraw(2, Q8_TO_Q12(curUnk->vx + cellBoundX), Q8_TO_Q12(curUnk->vy), Q8_TO_Q12(curUnk->vz + cellBoundZ), ot, arg4);
                    break;
            }
        }
    }

    #undef CHUNK_SUBCELL_SIZE
}

bool Gfx_ChunkSubcellVisibleCheck(s_IpdModelBuffer* modelBuf, q7_8 subcellX, q7_8 subcellZ, q23_8 posX, q23_8 posZ) // 0x80044420
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
