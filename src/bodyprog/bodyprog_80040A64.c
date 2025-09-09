#include "game.h"

#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"
#include "types.h"

/** Known contents:
 * - Map loading funcs
 * - Animation funcs
 */

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
    vec0.vx = (soundPos->vx - camPos.vx) >> 6; // TODO: Use `Q19_12_TO_Q27_4` here?
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

bool func_80040B74(s32 arg0) // 0x80040B74
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(D_800BCE18.field_0); i++)
    {
        if (D_800BCE18.field_0[i].field_CC.field_0 == arg0)
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
    coord.workm.t[0] = FP_METER_TO_GEO(pos1->vx);
    coord.workm.t[1] = FP_METER_TO_GEO(pos1->vy);
    coord.workm.t[2] = FP_METER_TO_GEO(pos1->vz);
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

u32 IpdHeader_LoadStateGet(s_800C117C* arg0) // 0x80041B1C
{
    s32 queueState;
    s32 queueStateCpy;

    queueState    = Fs_QueueEntryLoadStatusGet(arg0->queueIdx_4);
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
    else if (arg0->ipdHeader_0->isLoaded_1 && IpdHeader_IsTextureLoaded(arg0->ipdHeader_0))
    {
        return StaticModelLoadState_Loaded;
    }

    return StaticModelLoadState_Corrupted;
}

u32 LmHeader_LoadStateGet(s_func_80041CB4* arg0) // 0x80041BA0
{
    s32 queueState;
    s32 queueStateCpy;

    queueState    = Fs_QueueEntryLoadStatusGet(arg0->queueIdx_8);
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
    else if (arg0->lmHeader_0->isLoaded_2 && LmHeader_IsTextureLoaded(arg0->lmHeader_0))
    {
        return StaticModelLoadState_Loaded;
    }

    return StaticModelLoadState_Corrupted;
}

void func_80041C24(s_LmHeader* lmHeader, s32 arg1, s32 arg2) // 0x80041C24
{
    bzero(&D_800C1020, sizeof(s_800C1020));
    func_80041CB4(&D_800C1020.field_138, lmHeader);

    D_800C1020.field_150 = arg1;
    D_800C1020.field_154 = arg2;
    D_800C1020.ipdTableSize_158 = 0;
    D_800C1020.field_588 = 1;

    func_80041D10(D_800C1020.ipdTable_15C, 4);
    func_80041D48();
    func_80041E98();
}

// This function is related to map loading.
void func_80041CB4(s_func_80041CB4* arg0, s_LmHeader* lmHeader) // 0x80041CB4
{
    arg0->lmHeader_0 = lmHeader;
    func_80041CEC(lmHeader);

    arg0->queueIdx_8 = 0;
    arg0->fileIdx_4  = NO_VALUE;
}

void func_80041CEC(s_LmHeader* lmHeader) // 0x80041CEC
{
    lmHeader->magic_0         = LM_HEADER_MAGIC;
    lmHeader->version_1       = 6;
    lmHeader->isLoaded_2      = 1;
    lmHeader->materialCount_3 = 0;
    lmHeader->modelCount_8    = 0;
}

void func_80041D10(s_800C117C* arg0, s32 size) // 0x80041D10
{
    s_800C117C* ptr;

    for(ptr = &arg0[0]; ptr < &arg0[size]; ptr++)
    {
        ptr->queueIdx_4 = NO_VALUE;
    }
}

void func_80041D48() // 0x80041D48
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

        func_8005B1A0(&D_800C1020.field_430.field_58[i], 0, 0, y, 0, 0, x, j);
    }

    func_8005B46C(&D_800C1020.field_430.field_0);
    func_8005B474(&D_800C1020.field_430.field_0, D_800C1020.field_430.field_58, 8);

    for (i = 0, y = 26, j = 0; i < 2; i++, x += 16)
    {
        func_8005B1A0(&D_800C1020.field_430.field_118[i], 0, 0, y, (i & 0x1) * 32, 0, x, j);
        if (i & 0x1)
        {
            y++;
        }
    }

    func_8005B46C(&D_800C1020.field_430.field_2C);
    func_8005B474(&D_800C1020.field_430.field_2C, D_800C1020.field_430.field_118, 2);
}

void func_80041E98() // 0x80041E98
{
    bzero(&D_800C1020.field_0, sizeof(s_IpdCollisionData));
    D_800C1020.field_0.field_1C = 512;
}

void Map_PlaceIpdAtGridPos(s16 ipdFileIdx, s32 x, s32 z) // 0x80041ED0
{
    s_800C117C*  ptr;
    s_IpdHeader* ipd;

    ((s16*)&D_800C1020.ipdGridCenter_42C[z])[x] = ipdFileIdx;

    for (ptr = D_800C1020.ipdTable_15C; ptr < &D_800C1020.ipdTable_15C[D_800C1020.ipdTableSize_158]; ptr++)
    {
        if (ptr->field_8 != x || ptr->field_A != z)
        {
            continue;
        }

        if (Fs_QueueEntryLoadStatusGet(ptr->queueIdx_4) >= FsQueueEntryLoadStatus_Loaded)
        {
            ipd = ptr->ipdHeader_0;
            if (ipd->isLoaded_1)
            {
                func_80056BF8(ipd->lmHeader_4);
            }
        }

        ptr->queueIdx_4 = NO_VALUE;
    }
}

void func_80041FF0() // 0x80041FF0
{
    func_80042300(&D_800C1020, D_800C1020.ipdTableSize_158);
}

void func_8004201C() // 0x8004201C
{
    s_Material_8* material_8;

    material_8 = &D_800C1020.field_430.field_58[0];
    while (material_8 < (&D_800C1020.field_430.field_58[8]))
    {
        if (material_8->field_14 == 0)
        {
            func_8005B3A4(material_8);
        }

        material_8++;
    }

    material_8 = &D_800C1020.field_430.field_118[0];
    while (material_8 < (&D_800C1020.field_430.field_118[2]))
    {
        if (material_8->field_14 == 0)
        {
            func_8005B3A4(material_8);
        }

        material_8++;
    }
}

void func_800420C0() // 0x800420C0
{
    func_800420FC();
    func_80042300(&D_800C1020, D_800C1020.ipdTableSize_158);
    func_80041D48();
}

void func_800420FC() // 0x800420FC
{
    s_func_80041CB4* ptr;

    ptr = &D_800C1020.field_138;

    if (Fs_QueueEntryLoadStatusGet(ptr->queueIdx_8) >= FsQueueEntryLoadStatus_Loaded &&
        ptr->lmHeader_0->isLoaded_2)
    {
        func_80056BF8(D_800C1020.field_138.lmHeader_0);
    }

    func_80041CB4(&D_800C1020.field_138, D_800C1020.field_138.lmHeader_0);
}

s_Material_8* func_80042178(char* arg0) // 0x80042178
{
    s_Material_8* material_8;

    material_8 = func_8005B4BC(arg0, &D_800C1020.field_430.field_0);
    if (material_8 != NULL)
    {
        return material_8;
    }

    material_8 = func_8005B4BC(arg0, &D_800C1020.field_430.field_2C);
    if (material_8 != NULL)
    {
        return material_8;
    }

    return NULL;
}

void func_800421D8(char* mapTag, s32 plmIdx, s32 arg2, s32 arg3, s32 arg4, s32 arg5) // 0x800421D8
{
    D_800C1020.field_588 = arg3;
    D_800C1020.field_134 = arg5;

    if (plmIdx != NO_VALUE)
    {
        if (plmIdx != D_800C1020.field_138.fileIdx_4)
        {
            if (Fs_QueueEntryLoadStatusGet(D_800C1020.field_138.queueIdx_8) >= FsQueueEntryLoadStatus_Loaded &&
                D_800C1020.field_138.lmHeader_0->isLoaded_2)
            {
                func_80056BF8(D_800C1020.field_138.lmHeader_0);
            }

            D_800C1020.field_138.fileIdx_4 = plmIdx;
            D_800C1020.field_138.queueIdx_8 = NO_VALUE;
        }
    }

    if (D_800C1020.ipdTableSize_158 != arg2 || strcmp(mapTag, D_800C1020.mapTag_144) != 0)
    {
        func_80042300(&D_800C1020, arg2);

        D_800C1020.ipdTableSize_158 = arg2;
        D_800C1020.field_14C = arg4;
        strcpy(D_800C1020.mapTag_144, mapTag);

        D_800C1020.mapTagSize_148 = strlen(mapTag);
        Map_MakeIpdGrid(&D_800C1020, mapTag, arg4);
    }
}

void func_80042300(s_800C1020* arg0, s32 arg1) // 0x80042300
{
    s32          step;
    s32          i;
    s_800C117C*  temp_s0;
    s_IpdHeader* ipd0;
    s_IpdHeader* ipd1;

    ipd0  = arg0->field_150;
    step = (arg0->field_154 / arg1) & ~0x3;

    for (i = 0; i < 4; i++, *(u8**)&ipd0 += step)
    {
        temp_s0 = &arg0->ipdTable_15C[i];

        if (Fs_QueueEntryLoadStatusGet(temp_s0->queueIdx_4) >= FsQueueEntryLoadStatus_Loaded)
        {
            ipd1 = temp_s0->ipdHeader_0;
            if (ipd1->isLoaded_1)
            {
                func_80056BF8(ipd1->lmHeader_4);
            }
        }

        temp_s0->queueIdx_4 = NO_VALUE;
        temp_s0->field_10   = 0x7FFFFFFF;
        temp_s0->field_18   = 0;

        if (i < arg1)
        {
            temp_s0->ipdHeader_0 = ipd0;
        }
        else
        {
            temp_s0->ipdHeader_0 = NULL;
        }
    }
}

void Map_MakeIpdGrid(s_800C1020* arg0, char* mapTag, s32 fileIdxStart) // 0x800423F4
{
    s8              sp10[256];
    s32             x;
    s32             z;
    s32             i;
    s8*             filenameSuffix;
    s_IpdColumn*    col;

    arg0->ipdGridCenter_42C = (s_IpdColumn*)(&arg0->ipdGrid_1CC[8].idx[8]);

    for (z = -8; z < 11; z++)
    {
        for (x = -8; x < 8; x++)
        {
            ((s16*)&arg0->ipdGridCenter_42C[z])[x] = NO_VALUE;
        }
    }

    // Run through all game files.
    for (i = fileIdxStart; i < FS_FILE_COUNT; i++)
    {
        if (g_FileTable[i].type_8_18 == FileType_Ipd)
        {
            Fs_GetFileName(sp10, i);

            if (strncmp(sp10, arg0->mapTag_144, arg0->mapTagSize_148) == 0)
            {
                filenameSuffix = &sp10[arg0->mapTagSize_148];
                if (ConvertHexToS8(&x, filenameSuffix[0], filenameSuffix[1]) &&
                    ConvertHexToS8(&z, filenameSuffix[2], filenameSuffix[3]))
                {
                    col         = &arg0->ipdGridCenter_42C[z];
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

s32* func_800425D8(s32* arg0) // 0x800425D8
{
    s_800C117C*         ptr;
    s_IpdCollisionData* collData;
    s_IpdHeader*        ipd;

    ptr = D_800C1020.ipdTable_15C;
    *arg0  = 0;

    while (ptr < &D_800C1020.ipdTable_15C[D_800C1020.ipdTableSize_158])
    {
        if (Fs_QueueEntryLoadStatusGet(ptr->queueIdx_4) >= FsQueueEntryLoadStatus_Loaded)
        {
            ipd = ptr->ipdHeader_0;
            if (ipd->isLoaded_1)
            {
                collData = IpdHeader_CollisionDataGet(ipd);
                if (collData != NULL)
                {
                    D_800C1010[(*arg0)++] = collData;
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
    s32          xIdx;
    s32          zIdx;
    s_IpdHeader* ipd;
    s_800C117C*  ptr;

    // Convert position to collision space.
    collX = FP_METER_TO_GEO(posX);
    collZ = FP_METER_TO_GEO(posZ);

    // Indices to cells in IPD collision data?
    xIdx = FLOOR_TO_STEP(collX, FP_METER_GEO(40.0f));
    zIdx = FLOOR_TO_STEP(collZ, FP_METER_GEO(40.0f));

    for (ptr = D_800C1020.ipdTable_15C; ptr < &D_800C1020.ipdTable_15C[D_800C1020.ipdTableSize_158]; ptr++)
    {
        if (Fs_QueueEntryLoadStatusGet(ptr->queueIdx_4) < FsQueueEntryLoadStatus_Loaded)
        {
            continue;
        }

        ipd = ptr->ipdHeader_0;
        if (ipd->isLoaded_1 && ptr->field_8 == xIdx && ptr->field_A == zIdx)
        {
            return &ipd->collisionData_54;
        }
    }

    if (((s16*)(&D_800C1020.ipdGridCenter_42C[zIdx]))[xIdx] != NO_VALUE)
    {
        return NULL;
    }
    else
    {
        return &D_800C1020.field_0;
    }
}

s32 func_8004287C(s_800BCE18_2BEC_0* arg0, s_800BCE18_2BEC_0_10* arg1, s32 posX, s32 posZ) // 0x8004287C
{
    s_800C117C*      sp10[4];
    s32              sp20[4];
    s32              collX;
    s32              zIdx;
    s32              xIdx;
    s32              collZ;
    s32              temp_t0;
    s32              i;
    s32              j;
    s32              k;
    s32              idx;
    s_800C117C*      ptr1;
    s_func_80041CB4* ptr0;

    ptr0 = &D_800C1020.field_138;

    // Convert position to collision space.
    collX = FP_METER_TO_GEO(posX);
    collZ = FP_METER_TO_GEO(posZ);

    if (Fs_QueueEntryLoadStatusGet(ptr0->queueIdx_8) >= FsQueueEntryLoadStatus_Loaded &&
        ptr0->lmHeader_0->isLoaded_2 &&
        func_80056CB4(arg0, D_800C1020.field_138.lmHeader_0, arg1))
    {
        return 2;
    }

    // Indices to cells in IPD collision data?
    xIdx = FLOOR_TO_STEP(collX, FP_METER_GEO(40.0f));
    zIdx = FLOOR_TO_STEP(collZ, FP_METER_GEO(40.0f));

    for (ptr1 = D_800C1020.ipdTable_15C, idx = 0; ptr1 < &D_800C1020.ipdTable_15C[D_800C1020.ipdTableSize_158]; ptr1++)
    {
        if (Fs_QueueEntryLoadStatusGet(ptr1->queueIdx_4) < FsQueueEntryLoadStatus_Loaded)
        {
            continue;
        }

        if (!ptr1->ipdHeader_0->isLoaded_1)
        {
            continue;
        }

        if (D_800C1020.field_588 == 0)
        {
            if (ptr1->field_8 == xIdx && ptr1->field_A == zIdx)
            {
                sp10[idx] = ptr1;
                idx++;
                break;
            }
        }
        else
        {
            if (ptr1->field_8 >= (xIdx - 1) && (xIdx + 1) >= ptr1->field_8 &&
                ptr1->field_A >= (zIdx - 1) && (zIdx + 1) >= ptr1->field_A)
            {
                temp_t0 = func_80042E2C(collX, collZ, ptr1->field_8, ptr1->field_A);
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
                    sp10[j] = sp10[j - 1];
                }

                idx++;
                sp20[j] = temp_t0;
                sp10[j] = ptr1;
            }
        }
    }

    for (k = 0; k < idx; k++)
    {
        ptr1 = sp10[k];
        if (func_80056CB4(arg0, ptr1->ipdHeader_0->lmHeader_4, arg1))
        {
            return (ptr1 - D_800C1020.ipdTable_15C) + 3;
        }
    }

    return 0;
}

bool IpdHeader_IsLoaded(s32 ipdIdx) // 0x80042C04
{
    return IpdHeader_LoadStateGet(&D_800C1020.ipdTable_15C[ipdIdx]) >= StaticModelLoadState_Loaded;
}

void func_80042C3C(s32 x0, s32 z0, s32 x1, s32 z1) // 0x80042C3C
{
    s32         temp_s0;
    s_800C117C* var_s0;

    D_800C1020.field_578 = x1;
    D_800C1020.field_57C = z1;

    if (D_800C1020.field_138.queueIdx_8 == NO_VALUE) 
    {
        D_800C1020.field_138.queueIdx_8 = Fs_QueueStartRead(D_800C1020.field_138.fileIdx_4, D_800C1020.field_138.lmHeader_0);
    }

    func_80042EBC(&D_800C1020, x0, z0, x1, z1);

    if (Fs_QueueEntryLoadStatusGet(D_800C1020.field_138.queueIdx_8) >= FsQueueEntryLoadStatus_Loaded &&
        !D_800C1020.field_138.lmHeader_0->isLoaded_2) 
    {
        temp_s0                              = D_800C1020.field_430.field_0.count_0;
        D_800C1020.field_430.field_0.count_0 = 4;

        LmHeader_FixOffsets(D_800C1020.field_138.lmHeader_0);
        func_80056774(D_800C1020.field_138.lmHeader_0, &D_800C1020.field_430.field_0, NULL, D_800C1020.field_134, 1);
        func_80056954(D_800C1020.field_138.lmHeader_0);

        D_800C1020.field_430.field_0.count_0 = temp_s0;
    }

    for (var_s0 = D_800C1020.ipdTable_15C; var_s0 < &D_800C1020.ipdTable_15C[D_800C1020.ipdTableSize_158]; var_s0++) 
    {
        if (Fs_QueueEntryLoadStatusGet(var_s0->queueIdx_4) >= FsQueueEntryLoadStatus_Loaded)
        {
            IpdHeader_FixOffsets(var_s0->ipdHeader_0, &D_800C1020.field_138, 1, &D_800C1020.field_430.field_0, &D_800C1020.field_430.field_2C, D_800C1020.field_134);
            func_80044044(var_s0->ipdHeader_0, var_s0->field_8, var_s0->field_A);
        }
    }
}

s32 func_80042DE8(s32 posX, s32 posZ, s32 fileChunkCoordX, s32 fileChunkCoordZ, bool clip) // 0x80042DE8
{
    s32 dist;

    dist = func_80042E2C(FP_METER_TO_GEO(posX), FP_METER_TO_GEO(posZ), fileChunkCoordX, fileChunkCoordZ);
    if (clip)
    {
        dist -= FP_METER(1.0f);
        if (dist < FP_METER(0.0f))
        {
            dist = FP_METER(0.0f);
        }
    }

    return dist;
}

s32 func_80042E2C(s32 xPos, s32 zPos, s32 xFileChunkCoord, s32 zFileChunkCoord) // 0x80042E2C
{
    #define FILE_CHUNK_SIZE 0x2800

    #define OUTSIDE_DIST(val, lo, hi) \
        (((val) < (lo)) ? ((lo) - (val)) : (((hi) <= (val)) ? ((val) - (hi)) : 0))

    s32 xFileChunkBound;
    s32 zFileChunkBound;
    s32 x;
    s32 z;

    xFileChunkBound = xFileChunkCoord * FILE_CHUNK_SIZE;
    zFileChunkBound = zFileChunkCoord * FILE_CHUNK_SIZE;

    x = OUTSIDE_DIST(xPos, xFileChunkBound, xFileChunkBound + FILE_CHUNK_SIZE);
    z = OUTSIDE_DIST(zPos, zFileChunkBound, zFileChunkBound + FILE_CHUNK_SIZE);

    return Vc_VectorMagnitudeCalc(x, 0, z);
}

s32 func_80042EBC(s_800C1020* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x80042EBC
{
    s32           sp28;
    s32           sp2C;
    s32           sp30;
    s32           temp_s1;
    s32           temp_s3;
    s32           temp_v0;
    s32           temp_v0_2;
    s32           temp_v0_4;
    s32           j;
    s32           i;
    s32           var_v1;
    s_80043338*   temp_v0_3;
    s_80043338_0* temp_v1;

    sp30 = NO_VALUE;
    sp28 = FLOOR_TO_STEP(FP_METER_TO_GEO(arg1), FP_METER_GEO(40.0f));
    sp2C = FLOOR_TO_STEP(FP_METER_TO_GEO(arg2), FP_METER_GEO(40.0f));

    temp_v0 = FLOOR_TO_STEP(FP_METER_TO_GEO(arg3), FP_METER_GEO(40.0f));
    var_v1  = FLOOR_TO_STEP(FP_METER_TO_GEO(arg4), FP_METER_GEO(40.0f));

    arg0->field_580 = temp_v0;
    arg0->field_584 = var_v1;

    func_800431E4(arg0, arg1, arg2, arg3, arg4, arg0->field_588);
    func_800433B8(arg0);

    for (i = NO_VALUE; i < 2; i++)
    {
        for (j = NO_VALUE; j < 2; j++)
        {
            if (arg0->field_588 != 0 || (j == 0 && i == 0))
            {
                temp_s3 = sp2C + i;
                temp_s1 = sp28 + j;

                temp_v0_2 = func_80043554(temp_s1, temp_s3);
                if (temp_v0_2 != NO_VALUE &&
                    func_80042DE8(arg1, arg2, temp_s1, temp_s3, arg0->field_588) <= 0 &&
                    !func_80043578(&arg0->ipdTable_15C[0], temp_s1, temp_s3))
                {
                    temp_v0_3 = func_800435E4(&arg0->ipdTable_15C[0], arg0->field_588);

                    if (Fs_QueueEntryLoadStatusGet(temp_v0_3->queueEntryIdx_4) >= 2)
                    {
                        temp_v1 = temp_v0_3->destBuffer_0;
                        if (temp_v1->field_1 != 0)
                        {
                            func_80056BF8(temp_v1->field_4);
                        }
                    }

                    temp_v0_4 = func_800436D8(temp_v0_3, temp_v0_2, temp_s1, temp_s3, arg1, arg2, arg3, arg4, arg0->field_588);
                    if (temp_v0_4 != NO_VALUE)
                    {
                        sp30 = temp_v0_4;
                    }
                }
            }
        }
    }

    return sp30;
}

void func_800431E4(s_800C1020* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) // 0x800431E4
{
    s_800C117C* ptr;

    for (ptr = arg0->ipdTable_15C; ptr < arg0->ipdGrid_1CC; ptr++)
    {
        if (ptr->queueIdx_4 == NO_VALUE)
        {
            ptr->field_C  = 0x7FFFFFFF;
            ptr->field_10 = 0x7FFFFFFF;
        }
        else 
        {
            func_80043338(ptr, arg1, arg2, arg3, arg4, arg5);
        }

        if (Fs_QueueEntryLoadStatusGet(ptr->queueIdx_4) < FsQueueEntryLoadStatus_Loaded || !ptr->ipdHeader_0->isLoaded_1)
        {
            ptr->field_14 = 0;
        }
        else
        {
            ptr->field_14 = func_80043D00(ptr->ipdHeader_0);
        }

        if (ptr->field_C > 0 && ptr->field_10 > 0)
        {
            ptr->field_18++;
        }
        else
        {
            ptr->field_18 = 0;
        }
    }
}

void func_80043338(s_80043338* arg0, s32 posX0, s32 posZ0, s32 posX1, s32 posZ1, bool clip) // 0x80043338
{
    arg0->field_C  = func_80042DE8(posX0, posZ0, arg0->fileChunkCoordX_8, arg0->fileChunkCoordZ_A, clip);
    arg0->field_10 = func_80042DE8(posX1, posZ1, arg0->fileChunkCoordX_8, arg0->fileChunkCoordZ_A, clip);
}

void func_800433B8(s_800C1020* arg0) // 0x800433B8
{
    s_800C117C* ptr;

    for (ptr = &arg0->ipdTable_15C[0]; ptr < &arg0->ipdTable_15C[arg0->ipdTableSize_158]; ptr++)
    {
        if (Fs_QueueEntryLoadStatusGet(ptr->queueIdx_4) >= FsQueueEntryLoadStatus_Loaded)
        {
            if (ptr->ipdHeader_0->isLoaded_1 && ptr->field_C > 0 && ptr->field_10 > 0)
            {
                func_80056BF8(ptr->ipdHeader_0->lmHeader_4);
            }
        }
    }

    for (ptr = &arg0->ipdTable_15C[0]; ptr < &arg0->ipdTable_15C[arg0->ipdTableSize_158]; ptr++)
    {
        if (Fs_QueueEntryLoadStatusGet(ptr->queueIdx_4) >= FsQueueEntryLoadStatus_Loaded)
        {
            if (ptr->ipdHeader_0->isLoaded_1 && (ptr->field_C <= 0 || ptr->field_10 <= 0))
            {
                func_80043C7C(ptr->ipdHeader_0, &arg0->field_430.field_0, &arg0->field_430.field_2C, arg0->field_134);
                func_80056954(ptr->ipdHeader_0->lmHeader_4);
            }
        }
    }
}

s32 func_80043554(s32 gridX, s32 gridZ) // 0x80043554
{
    // @hack
    return ((s16*)&D_800C1020.ipdGridCenter_42C[gridZ])[gridX];
}

bool func_80043578(s_800C117C* arg0, s32 arg1, s32 arg2) // 0x80043578
{
    s32 i;

    for (i = 0; i < D_800C1020.ipdTableSize_158; i++)
    {
        if (arg0[i].queueIdx_4 != NO_VALUE &&
            arg1 == arg0[i].field_8 && arg2 == arg0[i].field_A)
        {
            return true;
        }
    }

    return false;
}

s_800C117C* func_800435E4(s_800C117C* arg0, s32 arg1)
{
    s32         var_t0;
    s32         var_t2;
    s32         var_v1;
    u32         var_t3;
    s32         var_a2;
    s_800C117C* ptr;
    s_800C117C* ret;

    ret    = NULL;
    var_t3 = 0;
    var_t0 = 0;
    var_t2 = 0;

    for (ptr = arg0; ptr < &arg0[D_800C1020.ipdTableSize_158]; ptr++)
    {
        if (arg1 == 0) 
        {
            if (ptr->queueIdx_4 == NO_VALUE)
            {
                ret = ptr;
                break;
            }
            else
            {
                if (var_t3 < ptr->field_18)
                {
                    var_t3 = ptr->field_18;
                    ret = ptr;
                }
            }
        }
        else
        {
            if (ptr->queueIdx_4 == -1) 
            {
                var_a2 = 0;
                
                if (var_t0 == 0) 
                {
                    var_v1 = 0x7FFFFFFF;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                var_a2 = ptr->field_14;
                var_v1 = ptr->field_C;
                
                if (var_v1 == 0)
                {
                    continue;
                }
            }

            if (var_t0 < var_a2 || (var_a2 == var_t0 && var_t2 < var_v1))
            {
                var_t2 = var_v1;
                ret    = ptr;
                var_t0 = var_a2;
            }
        }
    }

    return ret;
}

s32 func_800436D8(s_80043338* arg0, s32 fileIdx, s32 fileChunkCoordX, s32 fileChunkCoordZ, s32 posX0, s32 posZ0, s32 posX1, s32 posZ1, bool clip) // 0x800436D8
{
    // Return `NO_VALUE` if no file specified.
    if (fileIdx == NO_VALUE)
    {
        return fileIdx;
    }

    // Store file chunk coords and read file.
    arg0->fileChunkCoordX_8 = fileChunkCoordX;
    arg0->fileChunkCoordZ_A = fileChunkCoordZ;
    arg0->queueEntryIdx_4   = Fs_QueueStartRead(fileIdx, arg0->destBuffer_0);

    // Compute and store distance to file chunk edge in `arg0`.
    func_80043338(arg0, posX0, posZ0, posX1, posZ1, clip);

    // Return queue entry index.
    return arg0->queueEntryIdx_4;
}

bool func_80043740() // 0x80043740
{
    s32         i;
    s_800C117C* ptr;

    switch (LmHeader_LoadStateGet(&D_800C1020.field_138))
    {
        case 0:
            break;

        case 1:
            return false;

        case 2:
            return false;
    }

    for (ptr = D_800C1020.ipdTable_15C, i = 0;
         i < D_800C1020.ipdTableSize_158;
         i++, ptr++)
    {
        switch (IpdHeader_LoadStateGet(ptr))
        {
            case 0:
            case 3:
                continue;
        }

        if (ptr->field_C <= 0)
        {
            return false;
        }

        if (ptr->field_10 <= 0)
        {
            do {} while (0); // @hack

            return false;
        }
    }

    return true;
}

bool func_80043830(void) // 0x80043830
{
    s32         loadState;
    s_800C117C* ptr;

    for (ptr = &D_800C1020.ipdTable_15C[0]; ptr < &D_800C1020.ipdTable_15C[D_800C1020.ipdTableSize_158]; ptr++)
    {
        loadState = IpdHeader_LoadStateGet(ptr);
        if (loadState == StaticModelLoadState_Invalid || loadState == StaticModelLoadState_Loaded ||
            (ptr->field_C > 0 && ptr->field_10 > 0))
        {
            continue;
        }

        if (!func_80043B34(ptr, &D_800C1020))
        {
            continue;
        }

        if (func_80042E2C(FP_METER_TO_GEO(D_800C1020.field_578), FP_METER_TO_GEO(D_800C1020.field_57C), ptr->field_8, ptr->field_A) <= FP_METER_GEO(4.5f))
        {
            return true;
        }
    }

    return false;
}

bool func_8004393C(s32 posX, s32 posZ) // 0x8004393C
{
    s32 fileChunkCoordX;
    s32 fileChunkCoordZ;

    fileChunkCoordX = FLOOR_TO_STEP(FP_METER_TO_GEO(posX), FP_METER_GEO(40.0f));
    fileChunkCoordZ = FLOOR_TO_STEP(FP_METER_TO_GEO(posZ), FP_METER_GEO(40.0f));
    
    if (D_800C1020.field_588 != 0)
    {
        return func_80042E2C(FP_METER_TO_GEO(D_800C1020.field_578), FP_METER_TO_GEO(D_800C1020.field_57C), fileChunkCoordX, fileChunkCoordZ) <= FP_METER_GEO(4.5f);
    }

    if (fileChunkCoordX == D_800C1020.field_580 &&
        fileChunkCoordZ == D_800C1020.field_584)
    {
        return true;
    }

    return false;
}

void func_80043A24(GsOT* ot, s32 arg1) // 0x80043A24
{
    s32         queueState;
    s_800C117C* ptr;

    queueState = Fs_QueueEntryLoadStatusGet(D_800C1020.field_138.queueIdx_8);

    if (queueState == FsQueueEntryLoadStatus_Unloaded)
    {
        return;
    }

    if (!(queueState == FsQueueEntryLoadStatus_Invalid ||
          (queueState == FsQueueEntryLoadStatus_Loaded && D_800C1020.field_138.lmHeader_0->isLoaded_2)))
    {
        return;
    }

    ptr = &D_800C1020.ipdTable_15C[0];
    for (; ptr < &D_800C1020.ipdTable_15C[D_800C1020.ipdTableSize_158]; ptr++)
    {
        if (IpdHeader_LoadStateGet(ptr) >= 3 && func_80043B34(ptr, &D_800C1020))
        {
            func_80044090(ptr->ipdHeader_0, D_800C1020.field_578, D_800C1020.field_57C, ot, arg1);
        }
    }
}

bool func_80043B34(s_800C117C* arg0, s_800C1020* arg1)
{
    if (arg1->field_580 == arg0->field_8 && arg1->field_584 == arg0->field_A)
    {
        return true;
    }

    return arg1->field_588 != 0;
}

bool IpdHeader_IsTextureLoaded(s_IpdHeader* ipdHeader) // 0x80043B70
{
    if (!ipdHeader->isLoaded_1)
    {
        return false;
    }

    return LmHeader_IsTextureLoaded(ipdHeader->lmHeader_4);
}

s_IpdCollisionData* IpdHeader_CollisionDataGet(s_IpdHeader* ipdHeader) // 0x80043BA4
{
    if (ipdHeader->isLoaded_1)
    {
        return &ipdHeader->collisionData_54;
    }

    return NULL;
}

void IpdHeader_FixOffsets(s_IpdHeader* ipdHeader, s_LmHeader** lmHeaders, s32 lmHeaderCount, s_800C1450_0* arg3, s_800C1450_0* arg4, s32 arg5) // 0x80043BC4
{
    if (ipdHeader->isLoaded_1)
    {
        return;
    }
    ipdHeader->isLoaded_1 = true;

    IpdHeader_FixHeaderOffsets(ipdHeader);
    IpdCollData_FixOffsets(&ipdHeader->collisionData_54);
    LmHeader_FixOffsets(ipdHeader->lmHeader_4);
    func_8008E4EC(ipdHeader->lmHeader_4);
    func_80043C7C(ipdHeader, arg3, arg4, arg5);
    func_80056954(ipdHeader->lmHeader_4);
    IpdHeader_ModelLinkObjectLists(ipdHeader, lmHeaders, lmHeaderCount);
    IpdHeader_ModelBufferLinkObjectLists(ipdHeader, ipdHeader->modelInfo_14);
}

void func_80043C7C(s_IpdHeader* ipdHeader, s_800C1450_0* arg1, s_800C1450_0* arg2, s32 arg3) // 0x80043C7C
{
    if (!ipdHeader->isLoaded_1)
    {
        return;
    }

    if (arg1 != NULL)
    {
        func_80056774(ipdHeader->lmHeader_4, arg1, &LmFilter_NameDoesNotEndWithH, arg3, 1);
    }

    if (arg2 != NULL)
    {
        func_80056774(ipdHeader->lmHeader_4, arg2, &LmFilter_NameEndsWithH, arg3, 1);
    }
}

s32 func_80043D00(s_IpdHeader* ipdHeader) // 0x80043D00
{
    if (!ipdHeader->isLoaded_1)
    {
        return 0;
    }

    return func_80056348(LmFilter_NameEndsWithH, ipdHeader->lmHeader_4);
}

bool LmFilter_NameDoesNotEndWithH(s_Material* mat) // 0x80043D44
{
    return !LmFilter_NameEndsWithH(mat);
}

/* Not sure what is the significance of textures that end with H.
 * I've looked at all of them and can't find any pattern.
 */
bool LmFilter_NameEndsWithH(s_Material* mat) // 0x80043D64
{
    char* charCode;

    for (charCode = &mat->materialName_0.str[7]; charCode >= &mat->materialName_0.str[0]; charCode--)
    {
        if (*charCode == '\0')
        {
            continue;
        }

        return *charCode == 'H';
    }

    return false;
}

void IpdHeader_FixHeaderOffsets(s_IpdHeader* ipdHeader) // 0x80043DA4
{
    s_IpdModelBuffer* modelBuf;

    ipdHeader->lmHeader_4       = (u8*)ipdHeader->lmHeader_4 + (u32)ipdHeader;
    ipdHeader->modelInfo_14      = (u8*)ipdHeader->modelInfo_14 + (u32)ipdHeader;
    ipdHeader->modelBuffers_18   = (u8*)ipdHeader->modelBuffers_18 + (u32)ipdHeader;
    ipdHeader->modelOrderList_50 = (u8*)ipdHeader->modelOrderList_50 + (u32)ipdHeader;

    for (modelBuf = &ipdHeader->modelBuffers_18[0];
         modelBuf < &ipdHeader->modelBuffers_18[ipdHeader->modelBufferCount_9];
         modelBuf++)
    {
        modelBuf->field_C  = (u8*)modelBuf->field_C + (u32)ipdHeader;
        modelBuf->field_10 = (u8*)modelBuf->field_10 + (u32)ipdHeader;
        modelBuf->field_14 = (u8*)modelBuf->field_14 + (u32)ipdHeader;
    }
}

void IpdHeader_ModelLinkObjectLists(s_IpdHeader* ipdHeader, s_LmHeader** lmHeaders, s32 lmHeaderCount) // 0x80043E50
{
    s32             i;
    s32             j;
    s_IpdModelInfo* modelInfo;

    for (i = 0; i < ipdHeader->modelCount_8; i++)
    {
        modelInfo = &ipdHeader->modelInfo_14[i];
        if (!modelInfo->isGlobalPlm_0)
        {
            modelInfo->modelHeader_C = LmHeader_ModelHeaderSearch(&modelInfo->modelName_4, ipdHeader->lmHeader_4);
        }
        else
        {
            for (j = 0; j < lmHeaderCount; j++)
            {
                modelInfo->modelHeader_C = LmHeader_ModelHeaderSearch(&modelInfo->modelName_4, lmHeaders[j]);
                if (modelInfo->modelHeader_C != NULL)
                {
                    break;
                }
            }
        }
    }
}

s_ModelHeader* LmHeader_ModelHeaderSearch(u_Filename* modelName, s_LmHeader* lmHeader) // 0x80043F2C
{
    s32            i;
    s_ModelHeader* modelHeader;

    modelHeader = lmHeader->modelHeaders_C;

    for (i = 0; i < lmHeader->modelCount_8; i++, modelHeader++)
    {
        if (modelName->u32[0] == modelHeader->modelName_0.u32[0] &&
            modelName->u32[1] == modelHeader->modelName_0.u32[1])
        {
            return modelHeader;
        }
    }

    return NULL;
}

void IpdHeader_ModelBufferLinkObjectLists(s_IpdHeader* ipdHeader, s_IpdModelInfo* ipdModels) // 0x80043F88
{
    s_IpdModelBuffer*   modelBuffer;
    s_IpdModelBuffer_C* unkData;

    for (modelBuffer = ipdHeader->modelBuffers_18;
         modelBuffer < &ipdHeader->modelBuffers_18[ipdHeader->modelBufferCount_9];
         modelBuffer++)
    {
        for (unkData = &modelBuffer->field_C[0];
             unkData < &modelBuffer->field_C[modelBuffer->field_0];
             unkData++)
        {
            // unkData originally stores model idx, replace that with pointer to the models `modelHeader_C`
            s32 modelIdx           = (s32)unkData->modelHeader_0;
            unkData->modelHeader_0 = ipdModels[modelIdx].modelHeader_C;
        }
    }
}

void func_80044044(s_IpdHeader* ipd, s32 x, s32 z) // 0x80044044
{
    s32 gridX;
    s32 gridZ;

    gridX = ipd->levelGridX_2;
    gridZ = ipd->levelGridY_3;

    ipd->levelGridX_2             = x;
    ipd->levelGridY_3             = z;
    ipd->collisionData_54.posX_0 += (x - gridX) * 0x2800;
    ipd->collisionData_54.posZ_4 += (z - gridZ) * 0x2800;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80044090); // 0x80044090

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80044420); // 0x80044420

// ========================================
// ANIMATION
// ========================================

void Anim_BoneInit(s_AnmHeader* anmHeader, GsCOORDINATE2* boneCoords) // 0x800445A4
{
    s32            boneIdx;
    s32            i;
    s32            j;
    s_AnmBindPose* bindPose;
    GsCOORDINATE2* coord;

    GsInitCoordinate2(NULL, boneCoords);

    for (boneIdx = 1, bindPose = &anmHeader->bindPoses_14[1], coord = &boneCoords[1];
         boneIdx < anmHeader->boneCount_6;
         boneIdx++, bindPose++, coord++)
    {
        coord->super = &boneCoords[anmHeader->bindPoses_14[boneIdx].parentBone];

        // If no translation for this bone, copy over `translationInitial_3`.
        if (bindPose->translationDataIdx_2 < 0)
        {
            for (i = 0; i < 3; i++)
            {
                coord->coord.t[i] = anmHeader->bindPoses_14[boneIdx].translationInitial_3[i] << anmHeader->scaleLog2_12;
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

void Anim_BoneUpdate(s_AnmHeader* anmHeader, GsCOORDINATE2* boneCoords, s32 keyframe0, s32 keyframe1, s32 alpha) // 0x800446D8
{
    s32            boneCount;
    bool           isPlayer;
    u32            activeBoneIndices;
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

    boneCount     = anmHeader->boneCount_6;
    frame0Data    = (u8*)anmHeader + anmHeader->dataOffset_0 + (anmHeader->frameDataSize_4 * keyframe0);
    frame0RotData = frame0Data + (anmHeader->translationBoneCount_3 * 3);
    frame1Data    = (u8*)anmHeader + anmHeader->dataOffset_0 + (anmHeader->frameDataSize_4 * keyframe1);
    frame1RotData = frame1Data + (anmHeader->translationBoneCount_3 * 3);

    // For player, use inverted mask of `extra_128.disabledAnimBones_18` to facilitate masking of upper and lower body.
    isPlayer = boneCoords == &g_SysWork.playerBoneCoords_890[HarryBone_Root];
    if (isPlayer)
    {
        activeBoneIndices = ~g_SysWork.player_4C.extra_128.disabledAnimBones_18;
    }
    else
    {
        activeBoneIndices = anmHeader->activeBones_8;
    }

    // Skip root bone (index 0) and start processing from bone 1.
    boneCoords = &boneCoords[1];
    bindPose   = &anmHeader->bindPoses_14[1];

    for (boneIdx = 1, boneCoord = boneCoords;
         boneIdx < boneCount;
         boneIdx++, bindPose++, boneCoord++)
    {
        // Process bones marked as active.
        if (activeBoneIndices & (1 << boneIdx))
        {
            boneCoord->flg = false;
            scaleLog2      = anmHeader->scaleLog2_12;

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
                    boneCoord->coord.t[1] -= anmHeader->rootYOffset_13; // TODO: Not sure of purpose of this yet.
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

void func_80044950(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coords) // 0x80044950
{
    s_AnimInfo* animInfo;

    animInfo = func_80044918(&chara->model_0.anim_4);
    animInfo->updateFunc_0(&chara->model_0, anmHeader, coords, animInfo);
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

    return FP_TIME(0.0f);
}

void Anim_Update0(s_Model* model, s_AnmHeader* anmHeader, GsCOORDINATE2* coords, s_AnimInfo* animInfo) // 0x800449F0
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
    if (timeStep != FP_TIME(0.0f))
    {
        newTime += timeStep;

        // Clamp new time to valid keyframe range.
        endTime = FP_TIME(animInfo->endKeyframeIdx_E);
        if (newTime >= endTime)
        {
            newTime          = endTime;
            setNewAnimStatus = true;
        }
        else
        {
            startTime = FP_TIME(animInfo->startKeyframeIdx_C);
            if (newTime <= startTime)
            {
                newTime          = startTime;
                setNewAnimStatus = true;
            }
        }

        newKeyframeIdx = FP_FROM(newTime, Q12_SHIFT);
    }

    // Update skeleton.
    alpha = FP_ALPHA_NORM(newTime);
    if ((model->anim_4.flags_2 & AnimFlag_Unlocked) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        Anim_BoneUpdate(anmHeader, coords, newKeyframeIdx, newKeyframeIdx + 1, alpha);
    }

    // Update frame data.
    model->anim_4.time_4        = newTime;
    model->anim_4.keyframeIdx_8 = newKeyframeIdx;
    model->anim_4.alpha_A       = FP_ALPHA(0.0f);

    // Update anim status if anim started or ended.
    if (setNewAnimStatus)
    {
        model->anim_4.status_0 = animInfo->status_6;
    }
}

void Anim_Update1(s_Model* model, s_AnmHeader* anmHeader, GsCOORDINATE2* coord, s_AnimInfo* animInfo) // 0x80044B38
{
    s32 startKeyframeIdx;
    s32 endKeyframeIdx;
    s32 nextStartKeyframeIdx;
    s32 keyframeCount;
    s32 startKeyframeTime;
    s32 nextStartKeyframeTime;
    s32 keyframeCountTime;
    s32 timeStep;
    s32 newTime;
    s32 newKeyframeIdx0;
    s32 newKeyframeIdx1;
    s32 alpha;

    startKeyframeIdx     = animInfo->startKeyframeIdx_C;
    endKeyframeIdx       = animInfo->endKeyframeIdx_E;
    nextStartKeyframeIdx = endKeyframeIdx + 1;
    keyframeCount        = nextStartKeyframeIdx - startKeyframeIdx;

    startKeyframeTime     = FP_TIME(startKeyframeIdx);
    nextStartKeyframeTime = FP_TIME(nextStartKeyframeIdx);
    keyframeCountTime     = FP_TIME(keyframeCount);

    // Get time step.
    timeStep = Anim_TimeStepGet(model, animInfo);

    // Wrap new time to valid keyframe range?
    newTime = model->anim_4.time_4 + timeStep;
    while (newTime < startKeyframeTime)
    {
        newTime += keyframeCountTime;
    }
    while (newTime >= nextStartKeyframeTime)
    {
        newTime -= keyframeCountTime;
    }

    // Compute new keyframe 1. Wrap to start to facilitate loop.
    newKeyframeIdx0 = FP_FROM(newTime, Q12_SHIFT);
    newKeyframeIdx1 = newKeyframeIdx0 + 1;
    if (newKeyframeIdx1 == nextStartKeyframeIdx)
    {
        newKeyframeIdx1 = startKeyframeIdx;
    }

    // Update skeleton.
    alpha = FP_ALPHA_NORM(newTime);
    if ((model->anim_4.flags_2 & AnimFlag_Unlocked) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        Anim_BoneUpdate(anmHeader, coord, newKeyframeIdx0, newKeyframeIdx1, alpha);
    }

    // Update frame data.
    model->anim_4.time_4        = newTime;
    model->anim_4.keyframeIdx_8 = newKeyframeIdx0;
    model->anim_4.alpha_A       = FP_ALPHA(0.0f);
}

void Anim_Update2(s_Model* model, s_AnmHeader* anmHeader, GsCOORDINATE2* coord, s_AnimInfo* animInfo) // 0x80044CA4
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
    if (alpha >= FP_ALPHA(0.5f))
    {
        model->anim_4.time_4 = FP_TIME(endKeyframeIdx);
    }
    else
    {
        model->anim_4.time_4 = FP_TIME(startKeyframeIdx);
    }

    // Update frame data.
    if (alpha >= FP_ALPHA(1.0f))
    {
        startKeyframeIdx            = endKeyframeIdx;
        model->anim_4.keyframeIdx_8 = endKeyframeIdx;
        
        alpha            = FP_ALPHA(0.0f);
        setNewAnimStatus = true;
    }

    // Update skeleton.
    if ((model->anim_4.flags_2 & AnimFlag_Unlocked) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        Anim_BoneUpdate(anmHeader, coord, startKeyframeIdx, endKeyframeIdx, alpha);
    }

    // Update alpha.
    model->anim_4.alpha_A = alpha;

    // Update anim status if anim ended.
    if (setNewAnimStatus)
    {
        model->anim_4.status_0 = animInfo->status_6;
    }
}

void Anim_Update3(s_Model* model, s_AnmHeader* anmHeader, GsCOORDINATE2* coord, s_AnimInfo* animInfo) // 0x80044DF0
{
    s32 startKeyframeIdx;
    s32 endKeyframeIdx;
    s32 timeDelta;
    s32 timeStep;
    s32 alpha;
    s32 sinVal;
    s32 newTime;
    s32 sinAlpha;

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
        timeStep = FP_TIME(0.0f);
    }

    // Update alpha.
    sinAlpha              = model->anim_4.alpha_A;
    alpha                 = sinAlpha + timeStep;
    model->anim_4.alpha_A = alpha;

    // Sine-based easing?
    sinVal   = Math_Sin((alpha / 2) - FP_ALPHA(0.25f));
    sinAlpha = (sinVal / 2) + FP_ALPHA(0.5f);

    // Update time to start or end keyframe, whichever is closest.
    if (sinAlpha >= FP_ALPHA(0.5f))
    {
        newTime = FP_TIME(startKeyframeIdx);
    }
    else
    {
        newTime = FP_TIME(endKeyframeIdx);
    }

    alpha = sinAlpha;

    // Update time.
    model->anim_4.time_4 = newTime;

    // Update skeleton.
    if ((model->anim_4.flags_2 & AnimFlag_Unlocked) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        Anim_BoneUpdate(anmHeader, coord, startKeyframeIdx, endKeyframeIdx, alpha);
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

s8 func_80044F6C(s8* ptr, bool arg1) // 0x80044F6C
{
    if (arg1)
    {
        D_800C15B0 = ptr;
    }

    if (D_800C15B0[0] != -3)
    {
        D_800C15B4 = D_800C15B0[0];
        D_800C15B0++;
    }
    else if (++D_800C15B4 >= (D_800C15B0[1] - 1))
    {
        D_800C15B0++;
    }

    return D_800C15B4;
}

void func_80044FE0(s_Skeleton* skel, s_Bone* bones, u8 boneCount) // 0x80044FE0
{
    skel->bones_8 = bones;
    skel->boneCount_0 = boneCount;
    skel->boneIdx_1 = 0;
    skel->field_2 = 1;
    skel->field_4 = 0;

    func_80045014(skel);
}

void func_80045014(s_Skeleton* skel) // 0x80045014
{
    s_Bone* bone;

    // Traverse bone hierarchy and clear flags.
    for (bone = &skel->bones_8[0]; bone < &skel->bones_8[skel->boneCount_0]; bone++)
    {
        bone->flags_0 = 0;
    }
}

void func_8004506C(s_Skeleton* skel, s_LmHeader* lmHeader) // 0x8004506C
{
    u8  sp10[3]; // Size unsure, this could be larger.
    s32 switchVar;

    switchVar = LmHeader_ModelCountGet(lmHeader);
    sp10[0]   = 0;

    switch (switchVar)
    {
        case 0:
            sp10[0] = 0xFE;
            break;

        case 1:
            sp10[0] = 0;
            sp10[1] = 254;
            break;

        default:
            sp10[1] = 253;
            sp10[2] = LmHeader_ModelCountGet(lmHeader) - 1;
            sp10[3] = 254;
            break;
    }

    func_80045108(skel, lmHeader, sp10, 0);
}

// Anim func.
void func_80045108(s_Skeleton* skel, s_LmHeader* lmHeader, u8* arg2, s32 arg3) // 0x80045108
{
    s_Skeleton*  skel0; // Guessed the type. They both access `field_14` so maybe it's also `s_Skeleton`.
    s_Skeleton** skel1;
    s32          boneIdx;

    if (arg3 == 0)
    {
        skel->boneIdx_1 = 0;
        skel->field_4   = 0;
    }

    boneIdx = skel->boneIdx_1;
    func_800451B0(skel, lmHeader, arg2);

    skel1 = &skel->field_4;
    while (*skel1 != 0)
    {
        skel0 = *skel1;
        skel1 = &skel0->skeleton_14;
    }

    func_80045258(skel1, &skel->bones_8[boneIdx], skel->boneIdx_1 - boneIdx, lmHeader); // Very wierd third argument.
    func_800453E8(skel, false);
}

void func_800451B0(s_Skeleton* skel, s_LmHeader* lmHeader, s32* arg2) // 0x800451B0
{
    s32 var;
    
    var = func_80044F6C(arg2, true);

    while (var != -2)
    {
        func_80056C8C(&skel->bones_8[skel->boneIdx_1], lmHeader, var);

        skel->boneIdx_1++;
        var = func_80044F6C(arg2, false);
    }
}

void func_80045258(s_Skeleton** skels, s_Bone* bones, s32 boneIdx, s_LmHeader* lmHeader) // 0x80045258
{
    s_Bone* bone;
    u8*     objOrd;

    for (objOrd = lmHeader->modelOrder_10; objOrd < &lmHeader->modelOrder_10[lmHeader->modelCount_8]; objOrd++)
    {
        for (bone = bones; bone < &bones[boneIdx]; bone++)
        {
            if (bone->modelHeaderIdx_C == *objOrd)
            {
                *skels = (s_Skeleton*)bone;
                skels  = (s_Skeleton**)&bone->field_14;
            }
        }
    }

    *skels = NULL;
}

// Anim func.
void func_800452EC(s_Skeleton* skel) // 0x800452EC
{
    s32                temp_a0;
    s32                var_v0;
    u32                temp_v1;
    s_func_800452EC*   var_a1;
    s_func_800452EC_8* temp_v0;

    var_a1 = skel->field_4;

    while (var_a1)
    {
        temp_v0 = var_a1->field_8;
        temp_v1 = temp_v0->field_1 - 0x30;
        temp_a0 = temp_v0->field_0 - 0x30;

        if (temp_v1 < 10 && temp_a0 >= 0 && temp_a0 < 10)
        {
            var_v0 = (temp_a0 * 10) + temp_v1;
        }
        else
        {
            var_v0 = 0;
        }

        var_a1->field_10 = var_v0;
        var_a1           = var_a1->field_14;
    }
}

void func_80045360(s_Skeleton* skel, s8* arg1) // 0x80045360
{
    s32 boneIdx;
    s32 status;

    for (status = func_80044F6C(arg1, true), boneIdx = 0; status != -2; boneIdx++)
    {
        skel->bones_8[boneIdx].field_10 = status;
        status = func_80044F6C(arg1, false);
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
            bone->flags_0 &= ~(1 << 31);
        }
        else
        {
            bone->flags_0 |= 1 << 31;
        }
    }
}

void func_80045468(s_Skeleton* skel, s32* arg1, bool cond) // 0x80045468
{
    s_Bone* bone;
    s32     status;

    bone = skel->bones_8;

    // Get skeleton status?
    status = func_80044F6C(arg1, true);

    // Traverse bone hierarchy and set flags according to some condition.
    while (status != -2)
    {
        if (cond)
        {
            bone[status].flags_0 &= ~(1 << 31);
        }
        else
        {
            bone[status].flags_0 |= 1 << 31;
        }
        
        status = func_80044F6C(arg1, false);
    }
}

// Maybe larger anim func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045534); // 0x80045534
