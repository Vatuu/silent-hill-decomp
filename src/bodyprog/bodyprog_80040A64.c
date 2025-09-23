#include "game.h"
#include "inline_no_dmpsx.h"

#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"
#include "types.h"

/** Known contents:
 * - Map loading funcs
 * - Animation funcs
 */

extern s_800C4168 const D_800C4168;

s8 Sound_StereoBalanceGet(const VECTOR3* soundPos) // 0x80040A64
{
    #define STEREO_BALANCE_RANGE 127

    VECTOR3 camPos;
    VECTOR  vec0; // Q27.4?
    VECTOR  vec1; // Q19.12
    MATRIX  mat;
    s32     dot;
    s32     balance;

    // If monoural sound type, default to balance of 0.
    if (g_GameWork.config_0.optSoundType_1E)
    {
        return 0;
    }

    // Compute normal from camera and sound source positions.
    vwGetViewPosition(&camPos);
    vec0.vx = (soundPos->vx - camPos.vx) >> 6; // TODO: Use `QX_12_TO_QX_4` here?
    vec0.vy = (soundPos->vy - camPos.vy) >> 6;
    vec0.vz = (soundPos->vz - camPos.vz) >> 6;
    VectorNormal(&vec0, &vec1);

    // Compute stereo balance.
    Vw_CoordHierarchyMatrixCompute(vwGetViewCoord(), &mat);
    dot     = Math_MultiplyMatrix(mat, vec1);
    balance = CLAMP(dot, -STEREO_BALANCE_RANGE, STEREO_BALANCE_RANGE);
    return balance;
}

void func_80040B6C() {}

bool func_80040B74(s32 charaId) // 0x80040B74
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(g_WorldGfx.charaModels_CC); i++)
    {
        if (g_WorldGfx.charaModels_CC[i].charaId_0 == charaId)
        {
            return true;
        }
    }

    return false;
}

void func_80040BAC() // 0x80040BAC
{
    DVECTOR   posTable[17];
    POLY_G4*  poly_g4;
    POLY_F4*  poly_f4;
    PACKET*   packet;
    POLY_G3*  poly_g3;
    DR_TPAGE* page;
    s32       i;
    s32       k;
    s32       j;
    s32*      ptr;

    for (i = 0; i < 17; i++)
    {
        if (i < 2)
        {
            posTable[i].vx = g_GameWork.gsScreenWidth_588 >> 1;
            posTable[i].vy = (g_GameWork.gsScreenHeight_58A >> 2) * i;
        }
        else if (i < 6)
        {
            posTable[i].vx = (g_GameWork.gsScreenWidth_588 >> 1) - (((g_GameWork.gsScreenWidth_588 >> 1) >> 1) * (i - 2));
            posTable[i].vy = g_GameWork.gsScreenHeight_58A >> 1;
        }
        else if (i < 10)
        {
            posTable[i].vx = -g_GameWork.gsScreenWidth_588 / 2;
            posTable[i].vy = (g_GameWork.gsScreenHeight_58A >> 1) - (((g_GameWork.gsScreenHeight_58A >> 1) >> 1) * (i - 6));
        }
        else if (i < 14)
        {
            posTable[i].vx = (-g_GameWork.gsScreenWidth_588 / 2) + ((g_GameWork.gsScreenWidth_588 >> 2) * (i - 10));
            posTable[i].vy = -g_GameWork.gsScreenHeight_58A / 2;
        }
        else
        {
            posTable[i].vx = g_GameWork.gsScreenWidth_588 / 2;
            posTable[i].vy = -g_GameWork.gsScreenHeight_58A / 2 + ((g_GameWork.gsScreenHeight_58A >> 2) * (i - 14));
        }
    }

    for (j = 0, ptr = &posTable[0], packet = &D_800BFBF0; j < 2; j++,
        packet += sizeof(DR_TPAGE) * 2 + sizeof(POLY_G4) * 16 * 3 + sizeof(POLY_G3) * 16 + sizeof(POLY_F4) * 16)
    {
        page = (DR_TPAGE*)packet;

        SetDrawTPage(page, 1, 1, 0x40);
        page++;
        SetDrawTPage(page, 1, 1, 0x20);

        poly_g3 = packet + sizeof(DR_TPAGE) * 2;
        poly_f4 = packet + (sizeof(DR_TPAGE) * 2) + ((sizeof(POLY_G4) * 16) * 3) + (sizeof(POLY_G3) * 16);

        for (i = 0; i < 16; i++, poly_g3++, poly_f4++)
        {
            SetPolyG3(poly_g3);
            setSemiTrans(poly_g3, 1);
            SetPolyF4(poly_f4);
            setSemiTrans(poly_f4, 1);

            *(s32*)&poly_f4->x2 = ptr[i % 16];
            *(s32*)&poly_f4->x3 = ptr[i % 16 + 1];
        }

        poly_g4 = packet + (sizeof(DR_TPAGE) * 2) + (sizeof(POLY_G3) * 16);

        for (k = 0; k < 3; k++)
        {
            for (i = 0; i < 16; i++, poly_g4++)
            {
                SetPolyG4(poly_g4);
                setSemiTrans(poly_g4, 1);
            }
        }
    }
}

void func_80040E7C(u8 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) // 0x80040E7C
{
    #define SET_RGB(r, g, b) \
        (((r) & 0xFF) | ((g) & 0xFF) << 8 | ((b) & 0xFF) << 16)

    u32      colorTable[4];
    s32      j;
    s32      i;
    s32      k;
    u32      color;
    POLY_G3* poly_g3;
    POLY_F4* poly_f4;
    POLY_G4* poly_g4;
    PACKET*  packet;

    color = SET_RGB(arg0, arg1, arg2);

    packet = &D_800BFBF0;

    colorTable[0] = SET_RGB(0, 0, 0);
    colorTable[1] = SET_RGB(arg3 / 3, arg4 / 3, arg5 / 3);
    colorTable[2] = SET_RGB(arg3 * 2 / 3, arg4 * 2 / 3, arg5 * 2 / 3);
    colorTable[3] = SET_RGB(arg3, arg4, arg5);

    for (i = 0; i < 2; i++,
        packet += (sizeof(DR_TPAGE) * 2) + ((sizeof(POLY_G4) * 16) * 3) + (sizeof(POLY_G3) * 16) + (sizeof(POLY_F4) * 16))
    {
        poly_g3 = packet + (sizeof(DR_TPAGE) * 2);
        poly_f4 = packet + (sizeof(DR_TPAGE) * 2) + ((sizeof(POLY_G4) * 16) * 3) + (sizeof(POLY_G3) * 16);

        for (j = 0; j < 16; j++, poly_g3++, poly_f4++)
        {
            *(s32*)&poly_g3->r0 = color + (poly_g3->code << 24);
            *(s32*)&poly_g3->r1 = colorTable[0];
            *(s32*)&poly_g3->r2 = colorTable[0];
            *(s32*)&poly_f4->r0 = colorTable[3] + (poly_f4->code << 24);
        }

        poly_g4 = packet + (sizeof(DR_TPAGE) * 2) + (sizeof(POLY_G3) * 16);

        for (k = 0; k < 3; k++)
        {
            for (j = 0; j < 16; j++, poly_g4++)
            {
                *(s32*)&poly_g4->r0 = colorTable[k] + (poly_g4->code << 24);
                *(s32*)&poly_g4->r1 = colorTable[k];
                *(s32*)&poly_g4->r2 = colorTable[k + 1];
                *(s32*)&poly_g4->r3 = colorTable[k + 1];
            }
        }
    }
}

void func_80041074(GsOT* arg0, s32 arg1, SVECTOR* arg2, VECTOR3* arg3) // 0x80041074
{
    VECTOR3 sp18;
    s32     sp28;
    s32     sp2C;

    func_800410D8(&sp18, &sp28, &sp2C, arg2, arg3);
    func_800414E0(arg0, &sp18, arg1, sp28, sp2C);
}

void func_800410D8(VECTOR3* pos0, s32* arg1, s32* arg2, SVECTOR* rot, VECTOR3* pos1)
{
    MATRIX        mat;
    SVECTOR       vec0;
    GsCOORDINATE2 coord;
    VECTOR        vec1;
    VECTOR        vec2;
    s32           flag;

    memset(&vec0, 0, sizeof(SVECTOR));

    coord.super      = NULL;
    coord.workm      = GsIDMATRIX;
    coord.workm.t[0] = Q12_TO_Q8(pos1->vx);
    coord.workm.t[1] = Q12_TO_Q8(pos1->vy);
    coord.workm.t[2] = Q12_TO_Q8(pos1->vz);
    coord.flg        = true;

    func_80049AF8(&coord, &mat);
    SetRotMatrix(&mat);
    SetTransMatrix(&mat);
    RotTrans(&vec0, &vec1, &flag);
    ApplyRotMatrix(rot, &vec2);
    func_8004122C(arg1, arg2, &vec1, &vec2);
    func_8004137C(pos0, &vec1, &vec2, ReadGeomScreen());
}

void func_8004122C(s32* angle0, s32* angle1, VECTOR* arg2, VECTOR* arg3) // 0x8004122C
{
    VECTOR  vec0;
    VECTOR  vec1;
    VECTOR  vec2;
    SVECTOR svec0;
    SVECTOR svec1;
    VECTOR  vec3;

    VectorNormal(arg2, &vec0);
    VectorNormal(arg3, &vec1);
    OuterProduct12(&vec0, &vec1, &vec2);
    VectorNormal(&vec2, &vec2);

    *angle0 = FP_ANGLE_NORM_U(ratan2(vec2.vy, vec2.vx) - FP_ANGLE(90.0f));

    svec0.vx = FP_FROM((vec0.vx * vec1.vx) + (vec0.vy * vec1.vy) + (vec0.vz * vec1.vz), Q12_SHIFT);
    OuterProduct12(&vec2, &vec0, &vec3);
    svec1.vx = FP_FROM((vec1.vx * vec3.vx) + (vec1.vy * vec3.vy) + (vec1.vz * vec3.vz), Q12_SHIFT);

    *angle1 = FP_ANGLE_NORM_U(ratan2(svec1.vx, svec0.vx));
}

void func_8004137C(VECTOR3* result, VECTOR* vec0, VECTOR* vec1, s32 screenDist)
{
    VECTOR vec;
    s32    offsetX;
    s32    offsetY;
    s32    screenDistHalf;
    s32    z;

    screenDistHalf = screenDist / 2;

    if (screenDistHalf < vec0->vz)
    {
        vec = *vec0;
    }
    else
    {
        z = 1;
        if (vec1->vz != 0)
        {
            z = vec1->vz;
        }

        vec.vz = screenDistHalf;
        vec.vx = (((screenDistHalf - vec0->vz) * vec1->vx) / z) + vec0->vx;
        vec.vy = (((screenDistHalf - vec0->vz) * vec1->vy) / z) + vec0->vy;
    }

    ReadGeomOffset(&offsetX, &offsetY);

    result->vz = vec.vz;
    result->vx = ((vec.vx * screenDist) / vec.vz) + offsetX;
    result->vy = ((vec.vy * screenDist) / vec.vz) + offsetY;
}

void func_800414E0(GsOT* arg0, VECTOR3* arg1, s32 arg2, s32 arg3, s32 arg4) // 0x800414E0
{
    s32      sp10[4];
    DVECTOR  sp20[4];
    s32      temp_a1;
    s32      temp_a3;
    s32      temp_lo;
    s32      temp_s0_3;
    s32      temp_s1;
    s32      temp_s2;
    s32      var_a0;
    s32      var_s0;
    s32      var_s1;
    s32      i;
    s32      j;
    s32      var_v0;
    s32      var_v1;
    s32      var_v1_2;
    DVECTOR* var_s1_2;
    u32*     var_a1_3;
    u32*     var_t0;
    u32*     var_t1;
    u32*     var_t4;
    POLY_G3* poly_g3;
    POLY_G4* poly_g4;
    POLY_F4* poly_f4;

    if (arg1->vz < 0x400)
    {
        var_s1 = 0x1000;
    }
    else
    {
        var_s1 = 0x400000 / arg1->vz;
    }

    var_v0 = arg2 * 0x1F4;

    if (var_v0 < 0)
    {
        var_v0 += 0xFFF;
    }

    var_s0 = ((var_v0 >> 12) << 10) / arg1->vz;
    var_v1 = var_s0 * (0x3000 - FP_MULTIPLY(var_s1, Math_Cos(arg4), Q12_SHIFT));
    var_s0 = var_v1 / 16384;

    sp10[0] = (var_s0 / 5);
    sp10[1] = (var_s0 * 4) / 10;
    sp10[2] = (var_s0 * 7) / 10;
    sp10[3] = var_s0;

    temp_s1 = Math_Sin(arg4);
    temp_s2 = Math_Cos(arg3);
    temp_a3 = Math_Sin(arg3);

    for (i = 0; i < 4; i++)
    {
        temp_lo = FP_TO(var_s0 - (sp10[i] >> 1), Q12_SHIFT) / var_s0;
        var_v0  = sp10[i] * temp_lo;
        if (var_v0 < 0)
        {
            var_v0 += 0xFFF;
        }

        var_v0 = FP_FROM(var_v0, Q12_SHIFT) * temp_s2;
        if (var_v0 < 0)
        {
            var_v0 += 0xFFF;
        }

        var_v1_2 = FP_FROM(var_v0, Q12_SHIFT) * temp_s1;
        if (var_v1_2 < 0)
        {
            var_v1_2 += 0xFFF;
        }

        sp20[i].vx = arg1->vx + FP_FROM(var_v1_2, Q12_SHIFT);
        var_v0     = sp10[i] * temp_lo;
        if (var_v0 < 0)
        {
            var_v0 += 0xFFF;
        }

        var_v0 = FP_FROM(var_v0, Q12_SHIFT) * temp_a3;
        if (var_v0 < 0)
        {
            var_v0 += 0xFFF;
        }

        var_v1_2 = FP_FROM(var_v0, Q12_SHIFT) * temp_s1;
        if (var_v1_2 < 0)
        {
            var_v1_2 += 0xFFF;
        }

        sp20[i].vy = arg1->vy + FP_FROM(var_v1_2, Q12_SHIFT);
    }

    var_t4 = PSX_SCRATCH;

    for (i = 0; i < 4; i++)
    {
        var_s1_2 = var_t4 + i * 17;

        for (j = 0; j < 17; j++, var_s1_2++)
        {
            temp_s0_3 = Math_Cos(j << 8);
            temp_a1   = Math_Sin(j << 8);

            var_a0 = sp10[i] * temp_s0_3;

            if (var_a0 < 0)
            {
                var_a0 += 0xFFF;
            }

            var_s1_2->vx = sp20[i].vx + FP_FROM(var_a0, Q12_SHIFT);

            var_s1_2->vx = CLAMP(var_s1_2->vx, -0x400, 0x3FF);

            var_v0 = sp10[i] * temp_a1;

            if (var_v0 < 0)
            {
                var_v0 += 0xFFF;
            }

            var_s1_2->vy = sp20[i].vy + FP_FROM(var_v0, Q12_SHIFT);
            var_s1_2->vy = CLAMP(var_s1_2->vy, -0x400, 0x3FF);
        }
    }

    var_t0 = (u32*)PSX_SCRATCH;

    poly_g3 = &D_800BFBF0[g_ActiveBufferIdx][sizeof(DR_TPAGE) * 2];
    poly_f4 = &D_800BFBF0[g_ActiveBufferIdx][(sizeof(DR_TPAGE) * 2) + ((sizeof(POLY_G4) * 16) * 3) + (sizeof(POLY_G3) * 16)];

    for (j = 0; j < 16; j++, poly_g3++, poly_f4++)
    {
        poly_g3->x0         = arg1->vx;
        poly_g3->y0         = arg1->vy;
        *(s32*)&poly_g3->x1 = var_t0[j];
        *(s32*)&poly_g3->x2 = var_t0[j + 1];

        addPrim(arg0->org, poly_g3);

        *(s32*)&poly_f4->x0 = var_t0[j + 51];
        *(s32*)&poly_f4->x1 = var_t0[j + 52];

        addPrim(&arg0->org[1], poly_f4);
    }

    var_t1  = (u32*)PSX_SCRATCH;
    poly_g4 = &D_800BFBF0[g_ActiveBufferIdx][(sizeof(DR_TPAGE) * 2) + (sizeof(POLY_G3) * 16)];

    for (i = 0; i < 3; i++)
    {
        var_a1_3 = var_t1 + (i * 17);

        for (j = 0; j < 16; j++, poly_g4++)
        {
            *(s32*)&poly_g4->x0 = var_a1_3[j];
            *(s32*)&poly_g4->x1 = var_a1_3[j + 1];
            *(s32*)&poly_g4->x2 = var_a1_3[17 + j];
            *(s32*)&poly_g4->x3 = var_a1_3[(17 + j) + 1];

            addPrim(&arg0->org[1], poly_g4);
        }
    }

    AddPrim(arg0->org, &D_800BFBF0[g_ActiveBufferIdx][8]);
    AddPrim(&arg0->org[1], &D_800BFBF0[g_ActiveBufferIdx]);
}

u32 Fs_QueueEntryLoadStatusGet(s32 queueIdx) // 80041ADC
{
    if (queueIdx == NO_VALUE)
    {
        return FsQueueEntryLoadStatus_Invalid;
    }
    else if (!Fs_QueueIsEntryLoaded(queueIdx))
    {
        return FsQueueEntryLoadStatus_Unloaded;
    }

    return FsQueueEntryLoadStatus_Loaded;
}

u32 IpdHeader_LoadStateGet(s_IpdChunk* chunk) // 0x80041B1C
{
    s32 queueState;
    s32 queueStateCpy;

    queueState    = Fs_QueueEntryLoadStatusGet(chunk->queueIdx_4);
    queueStateCpy = queueState;

    if (queueStateCpy == FsQueueEntryLoadStatus_Unloaded)
    {
        return StaticModelLoadState_Unloaded;
    }
    else if (queueStateCpy == FsQueueEntryLoadStatus_Invalid ||
             queueState != FsQueueEntryLoadStatus_Loaded)
    {
        return StaticModelLoadState_Invalid;
    }
    else if (chunk->ipdHdr_0->isLoaded_1 && IpdHeader_IsTextureLoaded(chunk->ipdHdr_0))
    {
        return StaticModelLoadState_Loaded;
    }

    return StaticModelLoadState_Corrupted;
}

u32 LmHeader_LoadStateGet(s_GlobalLm* globalLm) // 0x80041BA0
{
    s32 queueState;
    s32 queueStateCpy;

    queueState    = Fs_QueueEntryLoadStatusGet(globalLm->queueIdx_8);
    queueStateCpy = queueState;

    if (queueStateCpy == FsQueueEntryLoadStatus_Unloaded)
    {
        return StaticModelLoadState_Unloaded;
    }
    else if (queueStateCpy == FsQueueEntryLoadStatus_Invalid ||
             queueState    != FsQueueEntryLoadStatus_Loaded)
    {
        return StaticModelLoadState_Invalid;
    }
    else if (globalLm->lmHdr_0->isLoaded_2 && LmHeader_IsTextureLoaded(globalLm->lmHdr_0))
    {
        return StaticModelLoadState_Loaded;
    }

    return StaticModelLoadState_Corrupted;
}

void Map_Init(s_LmHeader* lmHdr, s_IpdHeader* ipdBuf, s32 ipdBufSize) // 0x80041C24
{
    bzero(&g_Map, sizeof(s_Map));
    GlobalLm_Init(&g_Map.globalLm_138, lmHdr);

    g_Map.ipdBuffer_150 = ipdBuf;
    g_Map.ipdBufSize_154 = ipdBufSize;
    g_Map.ipdActiveSize_158 = 0;
    g_Map.isExterior = true;

    Ipd_ActiveChunksQueueIdxClear(g_Map.ipdActive_15C, 4);
    Ipd_TexturesInit1();
    Map_IpdCollisionDataInit();
}

void GlobalLm_Init(s_GlobalLm* globalLm, s_LmHeader* lmHdr) // 0x80041CB4
{
    globalLm->lmHdr_0 = lmHdr;
    LmHeader_Init(lmHdr);

    globalLm->queueIdx_8 = 0;
    globalLm->fileIdx_4  = NO_VALUE;
}

void LmHeader_Init(s_LmHeader* lmHdr) // 0x80041CEC
{
    lmHdr->magic_0         = LM_HEADER_MAGIC;
    lmHdr->version_1       = LM_VERSION;
    lmHdr->isLoaded_2      = true;
    lmHdr->materialCount_3 = 0;
    lmHdr->modelCount_8    = 0;
}

void Ipd_ActiveChunksQueueIdxClear(s_IpdChunk* chunks, s32 chunkCount) // 0x80041D10
{
    s_IpdChunk* curChunk;

    for (curChunk = &chunks[0]; curChunk < &chunks[chunkCount]; curChunk++)
    {
        curChunk->queueIdx_4 = NO_VALUE;
    }
}

void Ipd_TexturesInit1() // 0x80041D48
{
    s32 i;
    s16 j;
    s16 x;
    s32 y;

    for (i = 0, y = 8, x = 0, j = 0; i < 8; i++, y++, x += 16)
    {
        if (y == 11)
        {
            y = 21;
        }

        Texture_Init1(&g_Map.ipdTextures_430.fullPageTextures_58[i], 0, 0, y, 0, 0, x, j);
    }

    ActiveTextures_CountReset(&g_Map.ipdTextures_430.fullPage_0);
    ActiveTextures_PutTextures(&g_Map.ipdTextures_430.fullPage_0, g_Map.ipdTextures_430.fullPageTextures_58, 8);

    for (i = 0, y = 26, j = 0; i < 2; i++, x += 16)
    {
        Texture_Init1(&g_Map.ipdTextures_430.halfPageTextures_118[i], 0, 0, y, (i & 0x1) * 32, 0, x, j);
        if (i & 0x1)
        {
            y++;
        }
    }

    ActiveTextures_CountReset(&g_Map.ipdTextures_430.halfPage_2C);
    ActiveTextures_PutTextures(&g_Map.ipdTextures_430.halfPage_2C, g_Map.ipdTextures_430.halfPageTextures_118, 2);
}

void Map_IpdCollisionDataInit() // 0x80041E98
{
    bzero(&g_Map.field_0, sizeof(s_IpdCollisionData));
    g_Map.field_0.field_1C = 512;
}

void Map_PlaceIpdAtGridPos(s16 ipdFileIdx, s32 chunkCoordX, s32 chunkCoordZ) // 0x80041ED0
{
    s_IpdChunk*  curChunk;
    s_IpdHeader* ipdHdr;

    ((s16*)&g_Map.ipdGridCenter_42C[chunkCoordZ])[chunkCoordX] = ipdFileIdx;

    for (curChunk = g_Map.ipdActive_15C; curChunk < &g_Map.ipdActive_15C[g_Map.ipdActiveSize_158]; curChunk++)
    {
        if (curChunk->coordX_8 != chunkCoordX || curChunk->coordZ_A != chunkCoordZ)
        {
            continue;
        }

        if (Fs_QueueEntryLoadStatusGet(curChunk->queueIdx_4) >= FsQueueEntryLoadStatus_Loaded)
        {
            ipdHdr = curChunk->ipdHdr_0;
            if (ipdHdr->isLoaded_1)
            {
                Lm_MaterialRefCountDec(ipdHdr->lmHdr_4);
            }
        }

        curChunk->queueIdx_4 = NO_VALUE;
    }
}

void Ipd_ActiveChunksClear0() // 0x80041FF0
{
    Ipd_ActiveChunksClear(&g_Map, g_Map.ipdActiveSize_158);
}

void Ipd_TexturesInit0() // 0x8004201C
{
    s_Texture* curTex;

    // TODO: Will these match as for loops?
    curTex = &g_Map.ipdTextures_430.fullPageTextures_58[0];
    while (curTex < (&g_Map.ipdTextures_430.fullPageTextures_58[8]))
    {
        if (curTex->refCount_14 == 0)
        {
            Texture_Init0(curTex);
        }

        curTex++;
    }

    curTex = &g_Map.ipdTextures_430.halfPageTextures_118[0];
    while (curTex < (&g_Map.ipdTextures_430.halfPageTextures_118[2]))
    {
        if (curTex->refCount_14 == 0)
        {
            Texture_Init0(curTex);
        }

        curTex++;
    }
}

void func_800420C0() // 0x800420C0
{
    Map_GlobalLmFree();
    Ipd_ActiveChunksClear(&g_Map, g_Map.ipdActiveSize_158);
    Ipd_TexturesInit1();
}

void Map_GlobalLmFree() // 0x800420FC
{
    s_GlobalLm* globalLm;

    globalLm = &g_Map.globalLm_138;

    if (Fs_QueueEntryLoadStatusGet(globalLm->queueIdx_8) >= FsQueueEntryLoadStatus_Loaded &&
        globalLm->lmHdr_0->isLoaded_2)
    {
        Lm_MaterialRefCountDec(g_Map.globalLm_138.lmHdr_0);
    }

    GlobalLm_Init(&g_Map.globalLm_138, g_Map.globalLm_138.lmHdr_0);
}

s_Texture* func_80042178(char* texName) // 0x80042178
{
    s_Texture* tex;

    tex = ActiveTextures_FindTexture(texName, &g_Map.ipdTextures_430.fullPage_0);
    if (tex != NULL)
    {
        return tex;
    }

    tex = ActiveTextures_FindTexture(texName, &g_Map.ipdTextures_430.halfPage_2C);
    if (tex != NULL)
    {
        return tex;
    }

    return NULL;
}

void func_800421D8(char* mapTag, s32 plmIdx, s32 activeIpdCount, bool isExterior, s32 ipdFileIdx, s32 texFileIdx) // 0x800421D8
{
    g_Map.isExterior = isExterior;
    g_Map.texFileIdx_134 = texFileIdx;

    if (plmIdx != NO_VALUE)
    {
        if (plmIdx != g_Map.globalLm_138.fileIdx_4)
        {
            if (Fs_QueueEntryLoadStatusGet(g_Map.globalLm_138.queueIdx_8) >= FsQueueEntryLoadStatus_Loaded &&
                g_Map.globalLm_138.lmHdr_0->isLoaded_2)
            {
                Lm_MaterialRefCountDec(g_Map.globalLm_138.lmHdr_0);
            }

            g_Map.globalLm_138.fileIdx_4 = plmIdx;
            g_Map.globalLm_138.queueIdx_8 = NO_VALUE;
        }
    }

    if (g_Map.ipdActiveSize_158 != activeIpdCount || strcmp(mapTag, g_Map.mapTag_144) != 0)
    {
        Ipd_ActiveChunksClear(&g_Map, activeIpdCount);

        g_Map.ipdActiveSize_158 = activeIpdCount;
        g_Map.ipdFileIdx_14C = ipdFileIdx;
        strcpy(g_Map.mapTag_144, mapTag);

        g_Map.mapTagSize_148 = strlen(mapTag);
        Map_MakeIpdGrid(&g_Map, mapTag, ipdFileIdx);
    }
}

void Ipd_ActiveChunksClear(s_Map* map, s32 arg1) // 0x80042300
{
    s32          step;
    s32          i;
    s_IpdChunk*  curChunk;
    s_IpdHeader* ipd0;
    s_IpdHeader* ipd1;

    ipd0  = map->ipdBuffer_150;
    step = (map->ipdBufSize_154 / arg1) & ~0x3;

    for (i = 0; i < 4; i++, *(u8**)&ipd0 += step)
    {
        curChunk = &map->ipdActive_15C[i];

        if (Fs_QueueEntryLoadStatusGet(curChunk->queueIdx_4) >= FsQueueEntryLoadStatus_Loaded)
        {
            ipd1 = curChunk->ipdHdr_0;
            if (ipd1->isLoaded_1)
            {
                Lm_MaterialRefCountDec(ipd1->lmHdr_4);
            }
        }

        curChunk->queueIdx_4      = NO_VALUE;
        curChunk->distance1_10    = INT_MAX;
        curChunk->outsideCount_18 = 0;

        if (i < arg1)
        {
            curChunk->ipdHdr_0 = ipd0;
        }
        else
        {
            curChunk->ipdHdr_0 = NULL;
        }
    }
}

void Map_MakeIpdGrid(s_Map* map, char* mapTag, s32 fileIdxStart) // 0x800423F4
{
    char            sp10[256];
    s32             x;
    s32             z;
    s32             i;
    char*           filenameSuffix;
    s_IpdColumn*    col;

    map->ipdGridCenter_42C = (s_IpdColumn*)(&map->ipdGrid_1CC[8].idx[8]);

    for (z = -8; z < 11; z++)
    {
        for (x = -8; x < 8; x++)
        {
            ((s16*)&map->ipdGridCenter_42C[z])[x] = NO_VALUE;
        }
    }

    // Run through all game files.
    for (i = fileIdxStart; i < FS_FILE_COUNT; i++)
    {
        if (g_FileTable[i].type_8_24 == FileType_Ipd)
        {
            Fs_GetFileName(sp10, i);

            if (strncmp(sp10, map->mapTag_144, map->mapTagSize_148) == 0)
            {
                filenameSuffix = &sp10[map->mapTagSize_148];
                if (ConvertHexToS8(&x, filenameSuffix[0], filenameSuffix[1]) &&
                    ConvertHexToS8(&z, filenameSuffix[2], filenameSuffix[3]))
                {
                    col         = &map->ipdGridCenter_42C[z];
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

s_IpdCollisionData** func_800425D8(s32* collDataIdx) // 0x800425D8
{
    s_IpdChunk*         ptr;
    s_IpdCollisionData* collData;
    s_IpdHeader*        ipdHdr;

    ptr          = g_Map.ipdActive_15C;
    *collDataIdx = 0;

    while (ptr < &g_Map.ipdActive_15C[g_Map.ipdActiveSize_158])
    {
        if (Fs_QueueEntryLoadStatusGet(ptr->queueIdx_4) >= FsQueueEntryLoadStatus_Loaded)
        {
            ipdHdr = ptr->ipdHdr_0;
            if (ipdHdr->isLoaded_1)
            {
                collData = IpdHeader_CollisionDataGet(ipdHdr);
                if (collData != NULL)
                {
                    D_800C1010[(*collDataIdx)++] = collData;
                }
            }
        }

        ptr++;
    }

    return &D_800C1010[0];
}

s_IpdCollisionData* func_800426E4(s32 posX, s32 posZ) // 0x800426E4
{
    s32          collX;
    s32          collZ;
    s32          chunkCoordX;
    s32          chunkCoordZ;
    s_IpdHeader* ipdHdr;
    s_IpdChunk*  curChunk;

    // Convert position to geometry space.
    collX = Q12_TO_Q8(posX);
    collZ = Q12_TO_Q8(posZ);

    // Compute chunk coords.
    chunkCoordX = FLOOR_TO_STEP(collX, Q8(40.0f));
    chunkCoordZ = FLOOR_TO_STEP(collZ, Q8(40.0f));

    for (curChunk = g_Map.ipdActive_15C; curChunk < &g_Map.ipdActive_15C[g_Map.ipdActiveSize_158]; curChunk++)
    {
        if (Fs_QueueEntryLoadStatusGet(curChunk->queueIdx_4) < FsQueueEntryLoadStatus_Loaded)
        {
            continue;
        }

        ipdHdr = curChunk->ipdHdr_0;
        if (ipdHdr->isLoaded_1 &&
            curChunk->coordX_8 == chunkCoordX && curChunk->coordZ_A == chunkCoordZ)
        {
            return &ipdHdr->collisionData_54;
        }
    }

    if (((s16*)(&g_Map.ipdGridCenter_42C[chunkCoordZ]))[chunkCoordX] != NO_VALUE)
    {
        return NULL;
    }
    else
    {
        return &g_Map.field_0;
    }
}

s32 func_8004287C(s_WorldObject_0* arg0, s_WorldObject_0_10* arg1, s32 posX, s32 posZ) // 0x8004287C
{
    s_IpdChunk* chunks[4];
    s32         sp20[4];
    s32         collX;
    s32         chunkCoordZ;
    s32         chunkCoordX;
    s32         collZ;
    s32         temp_t0;
    s32         i;
    s32         j;
    s32         k;
    s32         idx;
    s_IpdChunk* curChunk;
    s_GlobalLm* globalLm;

    globalLm = &g_Map.globalLm_138;

    // Convert position to geometry space.
    collX = Q12_TO_Q8(posX);
    collZ = Q12_TO_Q8(posZ);

    if (Fs_QueueEntryLoadStatusGet(globalLm->queueIdx_8) >= FsQueueEntryLoadStatus_Loaded &&
        globalLm->lmHdr_0->isLoaded_2 &&
        Lm_ModelFind(arg0, g_Map.globalLm_138.lmHdr_0, arg1))
    {
        return 2;
    }

    chunkCoordX = FLOOR_TO_STEP(collX, Q8(40.0f));
    chunkCoordZ = FLOOR_TO_STEP(collZ, Q8(40.0f));

    for (curChunk = g_Map.ipdActive_15C, idx = 0;
         curChunk < &g_Map.ipdActive_15C[g_Map.ipdActiveSize_158];
         curChunk++)
    {
        if (Fs_QueueEntryLoadStatusGet(curChunk->queueIdx_4) < FsQueueEntryLoadStatus_Loaded)
        {
            continue;
        }

        if (!curChunk->ipdHdr_0->isLoaded_1)
        {
            continue;
        }

        if (!g_Map.isExterior)
        {
            if (curChunk->coordX_8 == chunkCoordX && curChunk->coordZ_A == chunkCoordZ)
            {
                chunks[idx] = curChunk;
                idx++;
                break;
            }
        }
        else
        {
            if (curChunk->coordX_8 >= (chunkCoordX - 1) && (chunkCoordX + 1) >= curChunk->coordX_8 &&
                curChunk->coordZ_A >= (chunkCoordZ - 1) && (chunkCoordZ + 1) >= curChunk->coordZ_A)
            {
                temp_t0 = Ipd_DistanceToEdgeGet(collX, collZ, curChunk->coordX_8, curChunk->coordZ_A);
                for (i = 0; i < idx; i++)
                {
                    if (temp_t0 < sp20[i])
                    {
                        break;
                    }
                }

                for (j = idx; j >= (i + 1); j--)
                {
                    sp20[j] = sp20[j - 1];
                    chunks[j] = chunks[j - 1];
                }

                idx++;
                sp20[j] = temp_t0;
                chunks[j] = curChunk;
            }
        }
    }

    for (k = 0; k < idx; k++)
    {
        curChunk = chunks[k];
        if (Lm_ModelFind(arg0, curChunk->ipdHdr_0->lmHdr_4, arg1))
        {
            return (curChunk - g_Map.ipdActive_15C) + 3;
        }
    }

    return 0;
}

bool IpdHeader_IsLoaded(s32 ipdIdx) // 0x80042C04
{
    return IpdHeader_LoadStateGet(&g_Map.ipdActive_15C[ipdIdx]) >= StaticModelLoadState_Loaded;
}

void func_80042C3C(q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1) // 0x80042C3C
{
    s32         fullPageTexCount;
    s_IpdChunk* curChunk;

    g_Map.field_578 = posX1;
    g_Map.field_57C = posZ1;

    if (g_Map.globalLm_138.queueIdx_8 == NO_VALUE) 
    {
        g_Map.globalLm_138.queueIdx_8 = Fs_QueueStartRead(g_Map.globalLm_138.fileIdx_4, g_Map.globalLm_138.lmHdr_0);
    }

    func_80042EBC(&g_Map, posX0, posZ0, posX1, posZ1);

    if (Fs_QueueEntryLoadStatusGet(g_Map.globalLm_138.queueIdx_8) >= FsQueueEntryLoadStatus_Loaded &&
        !g_Map.globalLm_138.lmHdr_0->isLoaded_2) 
    {
        fullPageTexCount = g_Map.ipdTextures_430.fullPage_0.count_0;
        g_Map.ipdTextures_430.fullPage_0.count_0 = 4;

        LmHeader_FixOffsets(g_Map.globalLm_138.lmHdr_0);
        Lm_MaterialsLoadWithFilter(g_Map.globalLm_138.lmHdr_0, &g_Map.ipdTextures_430.fullPage_0, NULL, g_Map.texFileIdx_134, 1);
        Lm_MaterialFlagsApply(g_Map.globalLm_138.lmHdr_0);

        g_Map.ipdTextures_430.fullPage_0.count_0 = fullPageTexCount;
    }

    for (curChunk = g_Map.ipdActive_15C; curChunk < &g_Map.ipdActive_15C[g_Map.ipdActiveSize_158]; curChunk++) 
    {
        if (Fs_QueueEntryLoadStatusGet(curChunk->queueIdx_4) >= FsQueueEntryLoadStatus_Loaded)
        {
            IpdHeader_FixOffsets(curChunk->ipdHdr_0, &g_Map.globalLm_138.lmHdr_0, 1, &g_Map.ipdTextures_430.fullPage_0, &g_Map.ipdTextures_430.halfPage_2C, g_Map.texFileIdx_134);
            func_80044044(curChunk->ipdHdr_0, curChunk->coordX_8, curChunk->coordZ_A);
        }
    }
}

q19_12 Ipd_DistanceToEdgeWithPaddingGet(q19_12 posX, q19_12 posZ, s32 fileChunkCoordX, s32 fileChunkCoordZ, bool isExterior) // 0x80042DE8
{
    q19_12 dist;

    dist = Ipd_DistanceToEdgeGet(Q12_TO_Q8(posX), Q12_TO_Q8(posZ), fileChunkCoordX, fileChunkCoordZ);
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

q19_12 Ipd_DistanceToEdgeGet(q19_12 posX, q19_12 posZ, s32 ipdChunkCoordX, s32 ipdChunkCoordZ) // 0x80042E2C
{
    #define IPD_CHUNK_SIZE Q8(40.0f)

    #define OUTSIDE_DIST(val, min, max) \
        (((val) < (min)) ? ((min) - (val)) : (((max) <= (val)) ? ((val) - (max)) : 0))

    s32 chunkBoundX;
    s32 chunkBoundZ;
    s32 x;
    s32 z;

    chunkBoundX = ipdChunkCoordX * IPD_CHUNK_SIZE;
    chunkBoundZ = ipdChunkCoordZ * IPD_CHUNK_SIZE;

    x = OUTSIDE_DIST(posX, chunkBoundX, chunkBoundX + IPD_CHUNK_SIZE);
    z = OUTSIDE_DIST(posZ, chunkBoundZ, chunkBoundZ + IPD_CHUNK_SIZE);
    return Vc_VectorMagnitudeCalc(x, 0, z);
}

s32 func_80042EBC(s_Map* map, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1) // 0x80042EBC
{
    s32          chunkCoordX0;
    s32          chunkCoordZ0;
    s32          chunkCoordZ1;
    s32          chunkCoordX1;
    s32          queueIdx;
    s32          gridX;
    s32          gridZ;
    s32          chunkIdx;
    s32          curQueueIdx;
    s32          x;
    s32          z;
    s_IpdChunk*  chunk;
    s_IpdHeader* ipdHdr;

    queueIdx = NO_VALUE;

    chunkCoordX0 = FLOOR_TO_STEP(Q12_TO_Q8(posX0), Q8(40.0f));
    chunkCoordZ0 = FLOOR_TO_STEP(Q12_TO_Q8(posZ0), Q8(40.0f));
    chunkCoordX1 = FLOOR_TO_STEP(Q12_TO_Q8(posX1), Q8(40.0f));
    chunkCoordZ1 = FLOOR_TO_STEP(Q12_TO_Q8(posZ1), Q8(40.0f));

    map->field_580 = chunkCoordX1;
    map->field_584 = chunkCoordZ1;

    Ipd_ActiveChunksSample(map, posX0, posZ0, posX1, posZ1, map->isExterior);
    func_800433B8(map);

    for (z = -1; z <= 1; z++)
    {
        for (x = -1; x <= 1; x++)
        {
            if (map->isExterior || (x == 0 && z == 0))
            {
                gridZ = chunkCoordZ0 + z;
                gridX = chunkCoordX0 + x;

                chunkIdx = Map_IpdIdxGet(gridX, gridZ);
                if (chunkIdx != NO_VALUE &&
                    Ipd_DistanceToEdgeWithPaddingGet(posX0, posZ0, gridX, gridZ, map->isExterior) <= Q12(0.0f) &&
                    !Map_IsIpdPresent(map->ipdActive_15C, gridX, gridZ))
                {
                    chunk = Ipd_FreeChunkFind(map->ipdActive_15C, map->isExterior);

                    if (Fs_QueueEntryLoadStatusGet(chunk->queueIdx_4) >= FsQueueEntryLoadStatus_Loaded)
                    {
                        ipdHdr = chunk->ipdHdr_0;
                        if (ipdHdr->isLoaded_1)
                        {
                            Lm_MaterialRefCountDec(ipdHdr->lmHdr_4);
                        }
                    }

                    curQueueIdx = Ipd_LoadStart(chunk, chunkIdx, gridX, gridZ, posX0, posZ0, posX1, posZ1, map->isExterior);
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

void Ipd_ActiveChunksSample(s_Map* map, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior) // 0x800431E4
{
    s_IpdChunk* curChunk;

    for (curChunk = map->ipdActive_15C; curChunk < &map->ipdActive_15C[4]; curChunk++)
    {
        if (curChunk->queueIdx_4 == NO_VALUE)
        {
            curChunk->distance0_C  = INT_MAX;
            curChunk->distance1_10 = INT_MAX;
        }
        else 
        {
            Ipd_DistanceToEdgeCalc(curChunk, posX0, posZ0, posX1, posZ1, isExterior);
        }

        if (Fs_QueueEntryLoadStatusGet(curChunk->queueIdx_4) < FsQueueEntryLoadStatus_Loaded || !curChunk->ipdHdr_0->isLoaded_1)
        {
            curChunk->materialCount_14 = 0;
        }
        else
        {
            curChunk->materialCount_14 = Ipd_HalfPageMaterialCountGet(curChunk->ipdHdr_0);
        }

        if (curChunk->distance0_C > Q12(0.0f) && curChunk->distance1_10 > Q12(0.0f))
        {
            curChunk->outsideCount_18++;
        }
        else
        {
            curChunk->outsideCount_18 = 0;
        }
    }
}

void Ipd_DistanceToEdgeCalc(s_IpdChunk* chunk, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior) // 0x80043338
{
    chunk->distance0_C  = Ipd_DistanceToEdgeWithPaddingGet(posX0, posZ0, chunk->coordX_8, chunk->coordZ_A, isExterior);
    chunk->distance1_10 = Ipd_DistanceToEdgeWithPaddingGet(posX1, posZ1, chunk->coordX_8, chunk->coordZ_A, isExterior);
}

void func_800433B8(s_Map* map) // 0x800433B8
{
    s_IpdChunk* curChunk;

    for (curChunk = &map->ipdActive_15C[0]; curChunk < &map->ipdActive_15C[map->ipdActiveSize_158]; curChunk++)
    {
        if (Fs_QueueEntryLoadStatusGet(curChunk->queueIdx_4) >= FsQueueEntryLoadStatus_Loaded)
        {
            if (curChunk->ipdHdr_0->isLoaded_1 &&
                curChunk->distance0_C > Q12(0.0f) && curChunk->distance1_10 > Q12(0.0f))
            {
                Lm_MaterialRefCountDec(curChunk->ipdHdr_0->lmHdr_4);
            }
        }
    }

    for (curChunk = &map->ipdActive_15C[0]; curChunk < &map->ipdActive_15C[map->ipdActiveSize_158]; curChunk++)
    {
        if (Fs_QueueEntryLoadStatusGet(curChunk->queueIdx_4) >= FsQueueEntryLoadStatus_Loaded)
        {
            if (curChunk->ipdHdr_0->isLoaded_1 &&
                (curChunk->distance0_C <= Q12(0.0f) || curChunk->distance1_10 <= Q12(0.0f)))
            {
                Ipd_MaterialsLoad(curChunk->ipdHdr_0, &map->ipdTextures_430.fullPage_0, &map->ipdTextures_430.halfPage_2C, map->texFileIdx_134);
                Lm_MaterialFlagsApply(curChunk->ipdHdr_0->lmHdr_4);
            }
        }
    }
}

s32 Map_IpdIdxGet(s32 gridX, s32 gridZ) // 0x80043554
{
    // @hack
    return ((s16*)&g_Map.ipdGridCenter_42C[gridZ])[gridX];
}

bool Map_IsIpdPresent(s_IpdChunk* chunks, s32 chunkCoordX, s32 chunkCoordZ) // 0x80043578
{
    s32 i;

    for (i = 0; i < g_Map.ipdActiveSize_158; i++)
    {
        if (chunks[i].queueIdx_4 != NO_VALUE &&
            chunkCoordX == chunks[i].coordX_8 && chunkCoordZ == chunks[i].coordZ_A)
        {
            return true;
        }
    }

    return false;
}

s_IpdChunk* Ipd_FreeChunkFind(s_IpdChunk* chunks, bool isExterior)
{
    s32         largestMatCount;
    q19_12      farthestDist;
    q19_12      dist;
    u32         largestOutsideCount;
    s32         matCount;
    s_IpdChunk* curChunk;
    s_IpdChunk* activeChunk;

    activeChunk         = NULL;
    largestOutsideCount = 0;
    largestMatCount     = 0;
    farthestDist        = Q12(0.0f);

    for (curChunk = chunks; curChunk < &chunks[g_Map.ipdActiveSize_158]; curChunk++)
    {
        if (!isExterior) 
        {
            if (curChunk->queueIdx_4 == NO_VALUE)
            {
                activeChunk = curChunk;
                break;
            }
            else
            {
                if (largestOutsideCount < curChunk->outsideCount_18)
                {
                    largestOutsideCount = curChunk->outsideCount_18;
                    activeChunk         = curChunk;
                }
            }
        }
        else
        {
            if (curChunk->queueIdx_4 == NO_VALUE) 
            {
                matCount = 0;
                
                if (largestMatCount == 0) 
                {
                    dist = INT_MAX;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                matCount = curChunk->materialCount_14;

                dist = curChunk->distance0_C;
                if (dist == Q12(0.0f))
                {
                    continue;
                }
            }

            if (largestMatCount < matCount || (matCount == largestMatCount && farthestDist < dist))
            {
                farthestDist    = dist;
                activeChunk     = curChunk;
                largestMatCount = matCount;
            }
        }
    }

    return activeChunk;
}

s32 Ipd_LoadStart(s_IpdChunk* chunk, s32 fileIdx, s32 chunkCoordX, s32 chunkCoordZ, q19_12 posX0, q19_12 posZ0, q19_12 posX1, q19_12 posZ1, bool isExterior) // 0x800436D8
{
    if (fileIdx == NO_VALUE)
    {
        return fileIdx;
    }

    chunk->coordX_8   = chunkCoordX;
    chunk->coordZ_A   = chunkCoordZ;
    chunk->queueIdx_4 = Fs_QueueStartRead(fileIdx, chunk->ipdHdr_0);

    Ipd_DistanceToEdgeCalc(chunk, posX0, posZ0, posX1, posZ1, isExterior);

    return chunk->queueIdx_4;
}

bool func_80043740() // 0x80043740
{
    s32         i;
    s_IpdChunk* curChunk;

    switch (LmHeader_LoadStateGet(&g_Map.globalLm_138))
    {
        case 0:
            break;

        case 1:
            return false;

        case 2:
            return false;
    }

    for (curChunk = g_Map.ipdActive_15C, i = 0;
         i < g_Map.ipdActiveSize_158;
         i++, curChunk++)
    {
        switch (IpdHeader_LoadStateGet(curChunk))
        {
            case 0:
            case 3:
                continue;
        }

        if (curChunk->distance0_C <= Q12(0.0f) || curChunk->distance1_10 <= Q12(0.0f))
        {
            return false;
        }
    }

    return true;
}

bool func_80043830(void) // 0x80043830
{
    s32         loadState;
    s_IpdChunk* curChunk;

    for (curChunk = &g_Map.ipdActive_15C[0]; curChunk < &g_Map.ipdActive_15C[g_Map.ipdActiveSize_158]; curChunk++)
    {
        loadState = IpdHeader_LoadStateGet(curChunk);
        if (loadState == StaticModelLoadState_Invalid || loadState == StaticModelLoadState_Loaded ||
            (curChunk->distance0_C > Q12(0.0f) && curChunk->distance1_10 > Q12(0.0f)))
        {
            continue;
        }

        if (!func_80043B34(curChunk, &g_Map))
        {
            continue;
        }

        if (Ipd_DistanceToEdgeGet(Q12_TO_Q8(g_Map.field_578), 
                          Q12_TO_Q8(g_Map.field_57C),
                          curChunk->coordX_8, curChunk->coordZ_A) <= Q8(4.5f))
        {
            return true;
        }
    }

    return false;
}

bool func_8004393C(q19_12 posX, q19_12 posZ) // 0x8004393C
{
    s32 fileChunkCoordX;
    s32 fileChunkCoordZ;

    fileChunkCoordX = FLOOR_TO_STEP(Q12_TO_Q8(posX), Q8(40.0f));
    fileChunkCoordZ = FLOOR_TO_STEP(Q12_TO_Q8(posZ), Q8(40.0f));
    
    if (g_Map.isExterior)
    {
        return Ipd_DistanceToEdgeGet(Q12_TO_Q8(g_Map.field_578), Q12_TO_Q8(g_Map.field_57C), fileChunkCoordX, fileChunkCoordZ) <= Q8(4.5f);
    }

    if (fileChunkCoordX == g_Map.field_580 &&
        fileChunkCoordZ == g_Map.field_584)
    {
        return true;
    }

    return false;
}

void func_80043A24(GsOT* ot, s32 arg1) // 0x80043A24
{
    s32         queueState;
    s_IpdChunk* curChunk;

    queueState = Fs_QueueEntryLoadStatusGet(g_Map.globalLm_138.queueIdx_8);

    if (queueState == FsQueueEntryLoadStatus_Unloaded)
    {
        return;
    }

    if (!(queueState == FsQueueEntryLoadStatus_Invalid ||
          (queueState == FsQueueEntryLoadStatus_Loaded && g_Map.globalLm_138.lmHdr_0->isLoaded_2)))
    {
        return;
    }

    curChunk = &g_Map.ipdActive_15C[0];
    for (; curChunk < &g_Map.ipdActive_15C[g_Map.ipdActiveSize_158]; curChunk++)
    {
        if (IpdHeader_LoadStateGet(curChunk) >= StaticModelLoadState_Loaded && func_80043B34(curChunk, &g_Map))
        {
            func_80044090(curChunk->ipdHdr_0, g_Map.field_578, g_Map.field_57C, ot, arg1);
        }
    }
}

bool func_80043B34(s_IpdChunk* chunk, s_Map* map)
{
    if (map->field_580 == chunk->coordX_8 &&
        map->field_584 == chunk->coordZ_A)
    {
        return true;
    }

    return map->isExterior != false;
}

bool IpdHeader_IsTextureLoaded(s_IpdHeader* ipdHdr) // 0x80043B70
{
    if (!ipdHdr->isLoaded_1)
    {
        return false;
    }

    return LmHeader_IsTextureLoaded(ipdHdr->lmHdr_4);
}

s_IpdCollisionData* IpdHeader_CollisionDataGet(s_IpdHeader* ipdHdr) // 0x80043BA4
{
    if (ipdHdr->isLoaded_1)
    {
        return &ipdHdr->collisionData_54;
    }

    return NULL;
}

void IpdHeader_FixOffsets(s_IpdHeader* ipdHdr, s_LmHeader** lmHdrs, s32 lmHdrCount, s_ActiveTextures* arg3, s_ActiveTextures* arg4, s32 arg5) // 0x80043BC4
{
    if (ipdHdr->isLoaded_1)
    {
        return;
    }
    ipdHdr->isLoaded_1 = true;

    IpdHeader_FixHeaderOffsets(ipdHdr);
    IpdCollData_FixOffsets(&ipdHdr->collisionData_54);
    LmHeader_FixOffsets(ipdHdr->lmHdr_4);
    func_8008E4EC(ipdHdr->lmHdr_4);
    Ipd_MaterialsLoad(ipdHdr, arg3, arg4, arg5);
    Lm_MaterialFlagsApply(ipdHdr->lmHdr_4);
    IpdHeader_ModelLinkObjectLists(ipdHdr, lmHdrs, lmHdrCount);
    IpdHeader_ModelBufferLinkObjectLists(ipdHdr, ipdHdr->modelInfo_14);
}

void Ipd_MaterialsLoad(s_IpdHeader* ipdHdr, s_ActiveTextures* arg1, s_ActiveTextures* arg2, s32 fileIdx) // 0x80043C7C
{
    if (!ipdHdr->isLoaded_1)
    {
        return;
    }

    if (arg1 != NULL)
    {
        Lm_MaterialsLoadWithFilter(ipdHdr->lmHdr_4, arg1, &LmFilter_IsFullPage, fileIdx, 1);
    }

    if (arg2 != NULL)
    {
        Lm_MaterialsLoadWithFilter(ipdHdr->lmHdr_4, arg2, &LmFilter_IsHalfPage, fileIdx, 1);
    }
}

s32 Ipd_HalfPageMaterialCountGet(s_IpdHeader* ipdHdr) // 0x80043D00
{
    if (!ipdHdr->isLoaded_1)
    {
        return 0;
    }

    return Lm_MaterialCount(LmFilter_IsHalfPage, ipdHdr->lmHdr_4);
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

    for (charCode = &mat->name_0.str[7]; charCode >= &mat->name_0.str[0]; charCode--)
    {
        if (*charCode == '\0')
        {
            continue;
        }

        return *charCode == 'H';
    }

    return false;
}

void IpdHeader_FixHeaderOffsets(s_IpdHeader* ipdHdr) // 0x80043DA4
{
    s_IpdModelBuffer* modelBuf;

    ipdHdr->lmHdr_4       = (u8*)ipdHdr->lmHdr_4 + (u32)ipdHdr;
    ipdHdr->modelInfo_14      = (u8*)ipdHdr->modelInfo_14 + (u32)ipdHdr;
    ipdHdr->modelBuffers_18   = (u8*)ipdHdr->modelBuffers_18 + (u32)ipdHdr;
    ipdHdr->modelOrderList_50 = (u8*)ipdHdr->modelOrderList_50 + (u32)ipdHdr;

    for (modelBuf = &ipdHdr->modelBuffers_18[0];
         modelBuf < &ipdHdr->modelBuffers_18[ipdHdr->modelBufferCount_9];
         modelBuf++)
    {
        modelBuf->field_C  = (u8*)modelBuf->field_C + (u32)ipdHdr;
        modelBuf->field_10 = (u8*)modelBuf->field_10 + (u32)ipdHdr;
        modelBuf->field_14 = (u8*)modelBuf->field_14 + (u32)ipdHdr;
    }
}

void IpdHeader_ModelLinkObjectLists(s_IpdHeader* ipdHdr, s_LmHeader** lmHdrs, s32 lmHdrCount) // 0x80043E50
{
    s32             i;
    s32             j;
    s_IpdModelInfo* modelInfo;

    for (i = 0; i < ipdHdr->modelCount_8; i++)
    {
        modelInfo = &ipdHdr->modelInfo_14[i];
        if (!modelInfo->isGlobalPlm_0)
        {
            modelInfo->modelHdr_C = LmHeader_ModelHeaderSearch(&modelInfo->modelName_4, ipdHdr->lmHdr_4);
        }
        else
        {
            for (j = 0; j < lmHdrCount; j++)
            {
                modelInfo->modelHdr_C = LmHeader_ModelHeaderSearch(&modelInfo->modelName_4, lmHdrs[j]);
                if (modelInfo->modelHdr_C != NULL)
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

    modelHeader = lmHdr->modelHdrs_C;

    for (i = 0; i < lmHdr->modelCount_8; i++, modelHeader++)
    {
        if (!COMPARE_FILENAMES(modelName, &modelHeader->modelName_0))
        {
            return modelHeader;
        }
    }

    return NULL;
}

void IpdHeader_ModelBufferLinkObjectLists(s_IpdHeader* ipdHdr, s_IpdModelInfo* ipdModels) // 0x80043F88
{
    s_IpdModelBuffer*   modelBuffer;
    s_IpdModelBuffer_C* unkData;

    for (modelBuffer = ipdHdr->modelBuffers_18;
         modelBuffer < &ipdHdr->modelBuffers_18[ipdHdr->modelBufferCount_9];
         modelBuffer++)
    {
        for (unkData = &modelBuffer->field_C[0];
             unkData < &modelBuffer->field_C[modelBuffer->field_0];
             unkData++)
        {
            // `unkData` originally stores model idx, replace that with pointer to the model's `modelHdr_C`.
            s32 modelIdx           = (s32)unkData->modelHdr_0;
            unkData->modelHdr_0 = ipdModels[modelIdx].modelHdr_C;
        }
    }
}

void func_80044044(s_IpdHeader* ipd, s32 gridX, s32 gridZ) // 0x80044044
{
    s32 prevGridX;
    s32 prevGridZ;

    prevGridX = ipd->levelGridX_2;
    prevGridZ = ipd->levelGridY_3;

    ipd->levelGridX_2                  = gridX;
    ipd->levelGridY_3                  = gridZ;
    ipd->collisionData_54.positionX_0 += (gridX - prevGridX) * Q8(40.0f);
    ipd->collisionData_54.positionZ_4 += (gridZ - prevGridZ) * Q8(40.0f);
}

void func_80044090(s_IpdHeader* ipdHdr, s32 arg1, s32 arg2, GsOT* ot, void* arg4) // 0x80044090
{
    s_ModelInfo         modelInfo;
    GsCOORDINATE2       sp28;
    MATRIX              sp78;
    MATRIX              sp98;
    s32                 spB8;
    s32                 spBC;
    s32                 temp_s3;
    s32                 temp_s5;
    s32                 var_a0;
    s32                 var_v1;
    s32                 i;
    s_IpdModelBuffer*   ipdModelBuf;
    s_IpdModelBuffer_C* var_s0;
    u8*                 temp_fp;
    SVECTOR*            var_s1;

    spB8 = Q12_TO_Q8(arg1);
    spBC = Q12_TO_Q8(arg2);

    temp_s5 = ipdHdr->levelGridX_2 * Q8(40.0f);
    temp_s3 = ipdHdr->levelGridY_3 * Q8(40.0f);

    var_v1 = FLOOR_TO_STEP(spB8 - temp_s5, Q8(8.0f));
    var_a0 = FLOOR_TO_STEP(spBC - temp_s3, Q8(8.0f));

    var_v1 = MAX(var_v1, 0);
    var_a0 = MAX(var_a0, 0);
    var_v1 = MIN(var_v1, 4);
    var_a0 = MIN(var_a0, 4);

    modelInfo.field_4 = &sp28;
    sp28.flg     = true;
    modelInfo.field_0 = 0;
    sp28.super   = NULL;

    temp_fp = &ipdHdr->textureCount_1C + (var_a0 * 10) + (var_v1 * 2);

    for (i = temp_fp[0]; i < temp_fp[1] + temp_fp[0]; i++)
    {
        ipdModelBuf = &ipdHdr->modelBuffers_18[ipdHdr->modelOrderList_50[i]];

        if (func_80044420(ipdModelBuf, spB8 - temp_s5, spBC - temp_s3, temp_s5, temp_s3))
        {
            for (var_s0 = ipdModelBuf->field_C; var_s0 < &ipdModelBuf->field_C[ipdModelBuf->field_0]; var_s0++)
            {
                modelInfo.modelHdr_8 = var_s0->modelHdr_0;
                if (modelInfo.modelHdr_8 != NULL)
                {
                    sp28.workm       = var_s0->field_4;
                    sp28.workm.t[0] += temp_s5;
                    sp28.workm.t[2] += temp_s3;

                    func_80049B6C(&sp28, &sp98, &sp78);
                    func_80057090(&modelInfo, ot, arg4, &sp78, &sp98, 0);
                }
            }

            for (var_s1 = ipdModelBuf->field_10; var_s1 < &ipdModelBuf->field_10[ipdModelBuf->field_1]; var_s1++)
            {
                switch ((s8)var_s1->pad)
                {
                    case 0:
                        func_8005B62C(1, (var_s1->vx + temp_s5) * 16, var_s1->vy * 16, (var_s1->vz + temp_s3) * 16, ot, arg4);
                        break;

                    case 1:
                        func_8005B62C(2, (var_s1->vx + temp_s5) * 16, var_s1->vy * 16, (var_s1->vz + temp_s3) * 16, ot, arg4);
                        break;
                }
            }
        }
    }
}

bool func_80044420(s_IpdModelBuffer* modelBuf, s16 arg1, s16 arg2, q23_8 x, q23_8 z) // 0x80044420
{
    GsCOORDINATE2 coord;
    MATRIX        mat;
    SVECTOR*      ptr;

    for (ptr = modelBuf->field_14; ptr < &modelBuf->field_14[modelBuf->field_2]; ptr++)
    {
        if (ptr->vx < arg1 && arg1 < ptr->vy &&
            ptr->vz < arg2)
        {
            if (arg2 < ptr->pad)
            {
                coord.flg   = true;
                coord.super = NULL;
                coord.workm = GsIDMATRIX;

                coord.workm.t[0] = x;
                coord.workm.t[1] = 0;
                coord.workm.t[2] = z;

                func_80049AF8(&coord, &mat);
                return Vw_AabbVisibleInFrustumCheck(&mat, modelBuf->field_4, -0x800, modelBuf->field_8, modelBuf->field_6, 0x400, modelBuf->field_A, 0x1900, g_GameWork.gsScreenHeight_58A);
            }
        }
    }

    return false;
}

// ========================================
// ANIMATION
// ========================================

void Anim_BoneInit(s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords) // 0x800445A4
{
    s32            boneIdx;
    s32            i;
    s32            j;
    s_AnmBindPose* bindPose;
    GsCOORDINATE2* coord;

    GsInitCoordinate2(NULL, boneCoords);

    for (boneIdx = 1, bindPose = &anmHdr->bindPoses_14[1], coord = &boneCoords[1];
         boneIdx < anmHdr->boneCount_6;
         boneIdx++, bindPose++, coord++)
    {
        coord->super = &boneCoords[anmHdr->bindPoses_14[boneIdx].parentBone];

        // If no translation for this bone, copy over `translationInitial_3`.
        if (bindPose->translationDataIdx_2 < 0)
        {
            for (i = 0; i < 3; i++)
            {
                coord->coord.t[i] = anmHdr->bindPoses_14[boneIdx].translationInitial_3[i] << anmHdr->scaleLog2_12;
            }
        }

        // If no rotation for this bone, create identity matrix.
        if (bindPose->rotationDataIdx_1 < 0)
        {
            for (i = 0; i < 3; i++)
            {
                for (j = 0; j < 3; j++)
                {
                    coord->coord.m[i][j] = ((j == i) ? FP_ANGLE(360.0f) : FP_ANGLE(0.0f));
                }
            }
        }
    }
}

void Anim_BoneUpdate(s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords, s32 keyframe0, s32 keyframe1, q19_12 alpha) // 0x800446D8
{
    s32            boneCount;
    bool           isPlayer;
    u32            activeBoneIdxs;
    s32            boneIdx;
    s32            scaleLog2;
    s32            boneTranslationDataIdx;
    s32            boneRotationDataIdx;
    s32            j;
    s32            i;
    s8*            frame0TranslationData;
    s8*            frame1TranslationData;
    s8*            frame0RotationData;
    s8*            frame1RotationData;
    void*          frame0Data;
    void*          frame0RotData;
    void*          frame1Data;
    void*          frame1RotData;
    GsCOORDINATE2* boneCoord;
    s_AnmBindPose* bindPose;

    boneCount     = anmHdr->boneCount_6;
    frame0Data    = ((u8*)anmHdr + anmHdr->dataOffset_0) + (anmHdr->keyframeDataSize_4 * keyframe0);
    frame0RotData = frame0Data + (anmHdr->translationBoneCount_3 * 3);
    frame1Data    = ((u8*)anmHdr + anmHdr->dataOffset_0) + (anmHdr->keyframeDataSize_4 * keyframe1);
    frame1RotData = frame1Data + (anmHdr->translationBoneCount_3 * 3);

    // For player, use inverted mask of `extra_128.disabledAnimBones_18` to facilitate masking of upper and lower body.
    isPlayer = boneCoords == &g_SysWork.playerBoneCoords_890[HarryBone_Root];
    if (isPlayer)
    {
        activeBoneIdxs = ~g_SysWork.player_4C.extra_128.disabledAnimBones_18;
    }
    else
    {
        activeBoneIdxs = anmHdr->activeBones_8;
    }

    // Skip root bone (index 0) and start processing from bone 1.
    boneCoords = &boneCoords[1];
    bindPose   = &anmHdr->bindPoses_14[1];

    for (boneIdx = 1, boneCoord = boneCoords;
         boneIdx < boneCount;
         boneIdx++, bindPose++, boneCoord++)
    {
        // Process bones marked as active.
        if (activeBoneIdxs & (1 << boneIdx))
        {
            boneCoord->flg = false;
            scaleLog2      = anmHdr->scaleLog2_12;

            boneTranslationDataIdx = bindPose->translationDataIdx_2;
            if (boneTranslationDataIdx >= 0)
            {
                // 3-byte vector translation.
                frame0TranslationData = frame0Data + (boneTranslationDataIdx * 3);
                frame1TranslationData = frame1Data + (boneTranslationDataIdx * 3);

                // Interpolate XYZ translation components.
                for (i = 0; i < 3; i++)
                {
                    // Linear interpolation with scaling: `frame0 + (frame1 - frame0) * alpha`.
                    boneCoord->coord.t[i] = (*frame0TranslationData << scaleLog2) +
                                            (((*frame1TranslationData - *frame0TranslationData) * alpha) >> (Q12_SHIFT - scaleLog2));

                    frame0TranslationData++;
                    frame1TranslationData++;
                }

                if (boneTranslationDataIdx == 0)
                {
                    boneCoord->coord.t[1] -= anmHdr->rootYOffset_13; // TODO: Not sure of purpose of this yet.
                }
            }

            boneRotationDataIdx = bindPose->rotationDataIdx_1;
            if (boneRotationDataIdx >= 0)
            {
                // 9-byte rotation matrix.
                frame0RotationData = frame0RotData + (boneRotationDataIdx * 9);
                frame1RotationData = frame1RotData + (boneRotationDataIdx * 9);

                // Interpolate rotation matrix.
                for (i = 0; i < 3; i++)
                {
                    for (j = 0; j < 3; j++)
                    {
                        boneCoord->coord.m[i][j] = (*frame0RotationData << 5) +
                                                   (((*frame1RotationData - *frame0RotationData) * alpha) >> 7);

                        frame0RotationData++;
                        frame1RotationData++;
                    }
                }
            }
        }
    }

    // Copy player hips translation to torso.
    if (isPlayer)
    {
        for (i = 0; i < 3; i++)
        {
            g_SysWork.playerBoneCoords_890[HarryBone_Torso].coord.t[i] = g_SysWork.playerBoneCoords_890[HarryBone_Hips].coord.t[i];
        }
    }
}

s_AnimInfo* func_80044918(s_ModelAnim* anim) // 0x80044918
{
    // `field_C`/`field_10` usually points to data at `0x800AF228` which contains funcptrs and other stuff.

    s_AnimInfo* animInfo_C;
    s_AnimInfo* animInfo_10;
    u8          animStatus0;
    s32         animStatus1;

    animInfo_C  = anim->animInfo_C;
    animInfo_10 = anim->animInfo_10;
    animStatus0 = anim->status_0;
    animStatus1 = anim->maybeSomeState_1;

    if (animInfo_10 != NULL && animStatus0 >= animStatus1)
    {
        animInfo_C  = animInfo_10;
        animInfo_C -= animStatus1;
    }

    return &animInfo_C[animStatus0];
}

void func_80044950(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x80044950
{
    s_AnimInfo* animInfo;

    animInfo = func_80044918(&chara->model_0.anim_4);
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
}

q19_12 Anim_DurationGet(s_Model* model, s_AnimInfo* anim) // 0x800449AC
{
    if (!anim->hasVariableDuration_5)
    {
        return anim->duration_8.constant;
    }

    return anim->duration_8.variableFunc();
}

/** @brief Computes the time step of the target animation. */
static inline q19_12 Anim_TimeStepGet(s_Model* model, s_AnimInfo* animInfo)
{
    q19_12 duration;

    if (model->anim_4.flags_2 & AnimFlag_Unlocked)
    {
        duration = Anim_DurationGet(model, animInfo);
        return FP_MULTIPLY_PRECISE(duration, g_DeltaTime0, Q12_SHIFT);
    }

    return Q12(0.0f);
}

void Anim_Update0(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* coords, s_AnimInfo* animInfo) // 0x800449F0
{
    bool setNewAnimStatus;
    s32  timeStep;
    s32  newTime;
    s32  newKeyframeIdx;
    s32  startTime;
    s32  endTime;
    s32  alpha;

    setNewAnimStatus = false;

    // Get time step.
    timeStep = Anim_TimeStepGet(model, animInfo);

    // Compute new time and keyframe index.
    newTime        = model->anim_4.time_4;
    newKeyframeIdx = FP_FROM(newTime, Q12_SHIFT);
    if (timeStep != Q12(0.0f))
    {
        newTime += timeStep;

        // Clamp new time to valid keyframe range.
        endTime = Q12(animInfo->endKeyframeIdx_E);
        if (newTime >= endTime)
        {
            newTime          = endTime;
            setNewAnimStatus = true;
        }
        else
        {
            startTime = Q12(animInfo->startKeyframeIdx_C);
            if (newTime <= startTime)
            {
                newTime          = startTime;
                setNewAnimStatus = true;
            }
        }

        newKeyframeIdx = FP_FROM(newTime, Q12_SHIFT);
    }

    // Update skeleton.
    alpha = Q12_FRACT(newTime);
    if ((model->anim_4.flags_2 & AnimFlag_Unlocked) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        Anim_BoneUpdate(anmHdr, coords, newKeyframeIdx, newKeyframeIdx + 1, alpha);
    }

    // Update frame data.
    model->anim_4.time_4        = newTime;
    model->anim_4.keyframeIdx_8 = newKeyframeIdx;
    model->anim_4.alpha_A       = Q12(0.0f);

    // Update anim status if anim started or ended.
    if (setNewAnimStatus)
    {
        model->anim_4.status_0 = animInfo->status_6;
    }
}

void Anim_Update1(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* coord, s_AnimInfo* animInfo) // 0x80044B38
{
    s32 startKeyframeIdx;
    s32 endKeyframeIdx;
    s32 nextStartKeyframeIdx;
    s32 keyframeCount;
    s32 startTime;
    s32 nextStartTime;
    s32 duration;
    s32 timeStep;
    s32 newTime;
    s32 newKeyframeIdx0;
    s32 newKeyframeIdx1;
    s32 alpha;

    startKeyframeIdx     = animInfo->startKeyframeIdx_C;
    endKeyframeIdx       = animInfo->endKeyframeIdx_E;
    nextStartKeyframeIdx = endKeyframeIdx + 1;
    keyframeCount        = nextStartKeyframeIdx - startKeyframeIdx;

    startTime     = Q12(startKeyframeIdx);
    nextStartTime = Q12(nextStartKeyframeIdx);
    duration      = Q12(keyframeCount);

    // Get time step.
    timeStep = Anim_TimeStepGet(model, animInfo);

    // Wrap new time to valid keyframe range.
    newTime = model->anim_4.time_4 + timeStep;
    while (newTime < startTime)
    {
        newTime += duration;
    }
    while (newTime >= nextStartTime)
    {
        newTime -= duration;
    }

    // Compute new keyframe 1. Wrap to start to facilitate loop.
    newKeyframeIdx0 = FP_FROM(newTime, Q12_SHIFT);
    newKeyframeIdx1 = newKeyframeIdx0 + 1;
    if (newKeyframeIdx1 == nextStartKeyframeIdx)
    {
        newKeyframeIdx1 = startKeyframeIdx;
    }

    // Update skeleton.
    alpha = Q12_FRACT(newTime);
    if ((model->anim_4.flags_2 & AnimFlag_Unlocked) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        Anim_BoneUpdate(anmHdr, coord, newKeyframeIdx0, newKeyframeIdx1, alpha);
    }

    // Update frame data.
    model->anim_4.time_4        = newTime;
    model->anim_4.keyframeIdx_8 = newKeyframeIdx0;
    model->anim_4.alpha_A       = Q12(0.0f);
}

void Anim_Update2(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* coord, s_AnimInfo* animInfo) // 0x80044CA4
{
    bool setNewAnimStatus;
    s32  startKeyframeIdx;
    s32  endKeyframeIdx;
    s32  timeStep;
    s32  alpha;
    
    setNewAnimStatus = false;
    startKeyframeIdx = animInfo->startKeyframeIdx_C;
    endKeyframeIdx   = animInfo->endKeyframeIdx_E;

    // If no start keyframe exists, default to active keyframe.
    if (startKeyframeIdx == NO_VALUE)
    {
        startKeyframeIdx = model->anim_4.keyframeIdx_8;
    }

    // Get time step.
    timeStep = Anim_TimeStepGet(model, animInfo);

    // Update time to start or end keyframe, whichever is closest.
    alpha  = model->anim_4.alpha_A;
    alpha += timeStep;
    if (alpha >= Q12(0.5f))
    {
        model->anim_4.time_4 = Q12(endKeyframeIdx);
    }
    else
    {
        model->anim_4.time_4 = Q12(startKeyframeIdx);
    }

    // Update frame data.
    if (alpha >= Q12(1.0f))
    {
        startKeyframeIdx            = endKeyframeIdx;
        model->anim_4.keyframeIdx_8 = endKeyframeIdx;
        
        alpha            = Q12(0.0f);
        setNewAnimStatus = true;
    }

    // Update skeleton.
    if ((model->anim_4.flags_2 & AnimFlag_Unlocked) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        Anim_BoneUpdate(anmHdr, coord, startKeyframeIdx, endKeyframeIdx, alpha);
    }

    // Update alpha.
    model->anim_4.alpha_A = alpha;

    // Update anim status if anim ended.
    if (setNewAnimStatus)
    {
        model->anim_4.status_0 = animInfo->status_6;
    }
}

void Anim_Update3(s_Model* model, s_AnmHeader* anmHdr, GsCOORDINATE2* coord, s_AnimInfo* animInfo) // 0x80044DF0
{
    s32    startKeyframeIdx;
    s32    endKeyframeIdx;
    s32    timeDelta;
    s32    timeStep;
    s32    alpha;
    q19_12 sinVal;
    s32    newTime;
    s32    newAlpha;

    startKeyframeIdx = animInfo->startKeyframeIdx_C;
    endKeyframeIdx   = animInfo->endKeyframeIdx_E;

    // Compute time step. TODO: Can't call `Anim_TimeStepGet` inline due to register constraints.
    if (model->anim_4.flags_2 & AnimFlag_Unlocked)
    {
        timeDelta = Anim_DurationGet(model, animInfo);
        timeStep  = FP_MULTIPLY_PRECISE(timeDelta, g_DeltaTime0, Q12_SHIFT);
    }
    else
    {
        timeStep = Q12(0.0f);
    }

    // Update alpha.
    newAlpha              = model->anim_4.alpha_A;
    alpha                 = newAlpha + timeStep;
    model->anim_4.alpha_A = alpha;

    // Compute ease-out alpha.
    sinVal   = Math_Sin((alpha / 2) - Q12(0.25f));
    newAlpha = (sinVal / 2) + Q12(0.5f);

    // Update time to start or end keyframe, whichever is closest.
    if (newAlpha >= Q12(0.5f))
    {
        newTime = Q12(startKeyframeIdx);
    }
    else
    {
        newTime = Q12(endKeyframeIdx);
    }

    alpha = newAlpha;

    // Update time.
    model->anim_4.time_4 = newTime;

    // Update skeleton.
    if ((model->anim_4.flags_2 & AnimFlag_Unlocked) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        Anim_BoneUpdate(anmHdr, coord, startKeyframeIdx, endKeyframeIdx, alpha);
    }

    // Update active keyframe.
    model->anim_4.keyframeIdx_8 = FP_FROM(newTime, Q12_SHIFT);
}

void func_80044F14(GsCOORDINATE2* coord, s16 z, s16 x, s16 y) // 0x80044F14
{
    *(s16*)0x1F800004 = z;
    *(s16*)0x1F800002 = y;
    *(s16*)0x1F800000 = x;
    
    func_80096E78((SVECTOR*)0x1F800000, (MATRIX*)0x1F800008);
    MulMatrix(&coord->coord, (MATRIX*)0x1F800008);
}

s8 Bone_ModelIdxGet(s8* ptr, bool reset) // 0x80044F6C
{
    // These two are probably part of a bigger struct.
    // `boneModelIdx` is not referenced directly anywhere else.
    // It must be reset somewhere at some point.
    #define boneIdxs     D_800C15B0
    #define boneModelIdx D_800C15B4

    if (reset)
    {
        boneIdxs = ptr;
    }

    // LM has <=1 model.
    if (boneIdxs[0] != -3)
    {
        // -2 for 0 models, 0 for 1 model.
        boneModelIdx = boneIdxs[0];
        boneIdxs++;
    }
    // Increment `boneModelIdx` and break loop when equal to number of models.
    else if (++boneModelIdx >= (boneIdxs[1] - 1))
    {
        boneIdxs++;
    }

    return boneModelIdx;
}

void Skeleton_Init(s_Skeleton* skel, s_Bone* bones, u8 boneCount) // 0x80044FE0
{
    skel->bones_8 = bones;
    skel->boneCount_0 = boneCount;
    skel->boneIdx_1 = 0;
    skel->field_2 = 1;
    skel->bones_4 = 0;

    func_80045014(skel);
}

void func_80045014(s_Skeleton* skel) // 0x80045014
{
    s_Bone* bone;

    // Traverse bone hierarchy and clear flags.
    for (bone = &skel->bones_8[0]; bone < &skel->bones_8[skel->boneCount_0]; bone++)
    {
        bone->modelInfo_0.field_0 = 0;
    }
}

void func_8004506C(s_Skeleton* skel, s_LmHeader* lmHdr) // 0x8004506C
{
    u8  sp10[4]; // Size unsure, this could be larger.
    s32 switchVar;

    switchVar = LmHeader_ModelCountGet(lmHdr);
    sp10[0]   = 0;

    switch (switchVar)
    {
        case 0:
            sp10[0] = BoneHierarchy_End;
            break;

        case 1:
            sp10[0] = 0;
            sp10[1] = BoneHierarchy_End;
            break;

        default:
            sp10[1] = BoneHierarchy_MultiModel;
            sp10[2] = LmHeader_ModelCountGet(lmHdr) - 1;
            sp10[3] = BoneHierarchy_End;
            break;
    }

    func_80045108(skel, lmHdr, (s8*)sp10, 0);
}

// Anim func.
void func_80045108(s_Skeleton* skel, s_LmHeader* lmHdr, s8* arg2, s32 arg3) // 0x80045108
{
    s_Bone*  curBone;
    s_Bone** boneOrd;
    s32      boneIdx;

    if (arg3 == 0)
    {
        skel->boneIdx_1 = 0;
        skel->bones_4   = NULL;
    }

    boneIdx = skel->boneIdx_1;
    Skeleton_BoneModelAssign(skel, lmHdr, arg2);

    boneOrd = &skel->bones_4;
    while (*boneOrd != NULL)
    {
        curBone = *boneOrd;
        boneOrd = &curBone->next_14;
    }

    // `Skeleton_BoneModelAssign` increments `boneIdx_1`.
    func_80045258(boneOrd, &skel->bones_8[boneIdx], skel->boneIdx_1 - boneIdx, lmHdr);
    func_800453E8(skel, false);
}

void Skeleton_BoneModelAssign(s_Skeleton* skel, s_LmHeader* lmHdr, s8* arg2) // 0x800451B0
{
    s32 modelIdx;
    
    modelIdx = Bone_ModelIdxGet(arg2, true);
    while (modelIdx != BoneHierarchy_End)
    {
        Bone_ModelAssign(&skel->bones_8[skel->boneIdx_1], lmHdr, modelIdx);

        skel->boneIdx_1++;
        modelIdx = Bone_ModelIdxGet(arg2, false);
    }
}

void func_80045258(s_Bone** boneOrd, s_Bone* bones, s32 boneIdx, s_LmHeader* lmHdr) // 0x80045258
{
    s_Bone* bone;
    u8*     curObjOrd;

    for (curObjOrd = lmHdr->modelOrder_10; curObjOrd < &lmHdr->modelOrder_10[lmHdr->modelCount_8]; curObjOrd++)
    {
        for (bone = bones; bone < &bones[boneIdx]; bone++)
        {
            if (bone->modelInfo_0.modelIdx_C == *curObjOrd)
            {
                *boneOrd = bone;
                boneOrd  = &bone->next_14;
            }
        }
    }

    *boneOrd = NULL;
}

// Anim func.
void func_800452EC(s_Skeleton* skel) // 0x800452EC
{
    s32            temp_a0;
    s32            var_v0;
    u32            temp_v1;
    s_Bone*        curBone;
    s_ModelHeader* modelHdr;

    curBone = skel->bones_4;
    while (curBone)
    {
        modelHdr = curBone->modelInfo_0.modelHdr_8;
        temp_v1 = modelHdr->modelName_0.str[1] - '0';
        temp_a0 = modelHdr->modelName_0.str[0] - '0';

        if (temp_v1 < 10 && temp_a0 >= 0 && temp_a0 < 10)
        {
            var_v0 = (temp_a0 * 10) + temp_v1;
        }
        else
        {
            var_v0 = 0;
        }

        curBone->field_10 = var_v0;
        curBone           = curBone->next_14;
    }
}

void func_80045360(s_Skeleton* skel, s8* arg1) // 0x80045360
{
    s32 i;
    s32 status;

    for (status = Bone_ModelIdxGet(arg1, true), i = 0; status != -2; i++)
    {
        skel->bones_8[i].field_10 = status;
        status = Bone_ModelIdxGet(arg1, false);
    }
}

void func_800453E8(s_Skeleton* skel, bool cond) // 0x800453E8
{
    s_Bone* bone;

    // Traverse bone hierarchy and set flags according to cond.
    for (bone = &skel->bones_8[0]; bone < &skel->bones_8[skel->boneCount_0]; bone++)
    {
        if (cond)
        {
            bone->modelInfo_0.field_0 &= ~(1 << 31);
        }
        else
        {
            bone->modelInfo_0.field_0 |= 1 << 31;
        }
    }
}

void func_80045468(s_Skeleton* skel, s32* arg1, bool cond) // 0x80045468
{
    s_Bone* bone;
    s32     status;

    bone = skel->bones_8;

    // Get skeleton status?
    status = Bone_ModelIdxGet(arg1, true);

    // Traverse bone hierarchy and set flags according to some condition.
    while (status != -2)
    {
        if (cond)
        {
            bone[status].modelInfo_0.field_0 &= ~(1 << 31);
        }
        else
        {
            bone[status].modelInfo_0.field_0 |= 1 << 31;
        }
        
        status = Bone_ModelIdxGet(arg1, false);
    }
}

void func_80045534(s_Skeleton* skel, GsOT* ot, void* arg2, GsCOORDINATE2* coord, s16 arg4, u16 arg5, s_FsImageDesc* images) // 0x80045534
{
    MATRIX         mat0;
    MATRIX         mat1;
    DVECTOR        sp60;
    s32            temp_a1;
    s16            var_fp;
    s16            var_s3;
    s16            var_s4;
    s16            var_s5;
    s16            var_s6;
    s16            var_s7;
    s32            temp_a0;
    s32            temp_s0;
    s32            temp_s1_2;
    s32            temp_s1_3;
    s32            temp_s1_4;
    s32            temp_v1;
    s32            var_s0;
    s32            var_s2;
    s32            var_s3_2;
    s32            var_v0_2;
    s32            var_v0_4;
    s32            var_v0_5;
    s_FsImageDesc* curImage;
    s_Bone*        curBone;

    var_s5 = 0x7FFF;
    var_s6 = 0x7FFF;
    var_s4 = 0x7FFF;
    var_s7 = -0x7FFF;
    var_fp = -0x7FFF;
    var_s3 = -0x7FFF;

    if (skel->field_2 == 0)
    {
        return;
    }

    var_s0 = NO_VALUE;

    if (images != NULL)
    {
        for (curImage = images; curImage->clutY != NO_VALUE; curImage++)
        {
            if (var_s0 != curImage->clutY)
            {
                var_s0 = curImage->clutY;
                func_80049AF8(&coord[var_s0], &mat0);
                SetRotMatrix(&mat0);
                SetTransMatrix(&mat0);
            }

            gte_ldv0(curImage);
            gte_rtps();
            gte_stsxy(&sp60);
            temp_a1 = gte_stSZ3();

            if (sp60.vx < var_s5)
            {
                var_s5 = sp60.vx;
            }

            if (var_s7 < sp60.vx)
            {
                var_s7 = sp60.vx;
            }

            if (sp60.vy < var_s6)
            {
                var_s6 = sp60.vy;
            }

            if (var_fp < sp60.vy)
            {
                var_fp = sp60.vy;
            }

            if (temp_a1 < var_s4)
            {
                var_s4 = temp_a1;
            }

            if (var_s3 < temp_a1)
            {
                var_s3 = temp_a1;
            }
        }
    }

    for (curBone = skel->bones_4; curBone != NULL; curBone = curBone->next_14)
    {
        if (curBone->modelInfo_0.field_0 >= 0)
        {
            func_80049B6C(&coord[(u8)curBone->field_10], &mat1, &mat0);

            if (curBone->modelInfo_0.field_0 & 1)
            {
                mat0.m[2][2]         = 0;
                *(s32*)&mat0.m[2][0] = 0;
                *(s32*)&mat0.m[1][1] = 0;
                *(s32*)&mat0.m[0][2] = 0;
                *(s32*)&mat0.m[0][0] = 0;
            }

            func_80057090(&curBone->modelInfo_0, ot, arg2, &mat0, &mat1, arg5);

            if (D_800C4168.fogEnabled_1)
            {
                gte_SetRotMatrix(&mat0);
                gte_SetTransMatrix(&mat0);
                gte_ldvxy0_Zero();
                gte_gte_ldvz0();
                gte_rtps();
                gte_stsxy(&sp60);
                temp_a1 = gte_stSZ3();

                if (sp60.vx < var_s5)
                {
                    var_s5 = sp60.vx;
                }

                if (var_s7 < sp60.vx)
                {
                    var_s7 = sp60.vx;
                }

                if (sp60.vy < var_s6)
                {
                    var_s6 = sp60.vy;
                }

                if (var_fp < sp60.vy)
                {
                    var_fp = sp60.vy;
                }

                if (temp_a1 < var_s4)
                {
                    var_s4 = temp_a1;
                }

                if (var_s3 < temp_a1)
                {
                    var_s3 = temp_a1;
                }
            }
        }
    }

    if (D_800C4168.fogEnabled_1)
    {
        temp_s1_2 = g_SysWork.playerBoneCoords_890[1].coord.t[1];
        temp_s1_2 = CLAMP(temp_s1_2, Q8(-2.0f), Q8(0.0f));

        temp_s1_2 += Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vy);
        temp_s1_3  = Math_MulFixed(Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vx), GsWSMATRIX.m[2][0], Q12_SHIFT);
        temp_s0    = Math_MulFixed(temp_s1_2, GsWSMATRIX.m[2][1], Q12_SHIFT);
        temp_s1_4  = ((temp_s1_3 + temp_s0) + Math_MulFixed(Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vz), GsWSMATRIX.m[2][2], Q12_SHIFT)) + GsWSMATRIX.t[2];

        var_s3_2 = (var_s4 + var_s3) >> 1;
        temp_v1  = var_s3_2 - ((var_s3 - var_s4) >> 1);

        temp_a0 = temp_v1 - 0x33;

        if (temp_s1_4 >= (temp_v1 - 0x41A))
        {
            if (temp_s1_4 < (temp_v1 - 0x1A))
            {
                var_v0_2  = temp_s1_4 + 0x3E7;
                var_v0_2 -= temp_a0;
                var_v0_2  = FP_TO(var_v0_2, Q12_SHIFT);

                if (var_v0_2 < 0)
                {
                    var_v0_2 += 0x3FF;
                }

                var_s3_2 += Math_MulFixed(temp_a0 - var_s3_2, var_v0_2 >> 10, Q12_SHIFT);
            }
            else if (temp_s1_4 < temp_a0)
            {
                var_s3_2 = temp_a0;
            }
            else if (temp_s1_4 < var_s3_2)
            {
                var_s3_2 = temp_s1_4;
            }
        }

        var_s3_2 = MAX(var_s3_2, 4);

        var_s2 = (var_s4 * 16) - arg4;
        var_s2 = MAX(var_s2, 0);

        var_s0   = ReadGeomScreen();
        var_v0_4 = (arg4 >> 4) * var_s0;

        if (var_s4 >= 5)
        {
            var_v0_5 = (var_v0_4 / var_s4) + 2;
        }
        else
        {
            var_v0_5 = (var_v0_4 / 4) + 2;
        }

        func_80056D8C(var_s5 - var_v0_5, var_s6 - var_v0_5, var_s7 + var_v0_5, var_fp + var_v0_5, var_s3_2 * 16, var_s2, ot, arg2);
    }
}
