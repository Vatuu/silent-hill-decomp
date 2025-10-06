#include "game.h"
#include "inline_no_dmpsx.h"

#include <libapi.h>
#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"

extern s_800C4168 D_800C4168;

void func_80055028() // 0x80055028
{
    func_80040BAC();
    func_8008D41C();

    // This struct might or might not be a GPU packet or some other graphics/GTE-related PsyQ thing.
    D_800C4168.field_0  = 0;
    D_800C4168.field_20 = Q12(1.0f);

    D_800C4168.worldTintColor_28.r = 128;
    D_800C4168.worldTintColor_28.g = 128;
    D_800C4168.worldTintColor_28.b = 128;

    D_800C4168.fogEnabled_1 = false;
    D_800C4168.field_2 = 0;

    D_800C4168.fogColor_1C.r = 255;
    D_800C4168.fogColor_1C.g = 255;
    D_800C4168.fogColor_1C.b = 255;

    D_800C4168.field_4C = 0;
    D_800C4168.field_50 = 0;
    D_800C4168.waterZones_4  = 0;
    D_800C4168.fogRelated_18 = 0;

    gte_SetFarColor(0, 0, 0);

    func_80055840(0x20000, 0x22000);
}

void func_800550D0() // 0x800550D0
{
    s32      color0;
    s32      color2;
    PACKET*  packet;
    PACKET*  packet2;
    DR_MODE* mode;
    POLY_G4* poly;
    GsOT*    ot;

    ot = &g_OrderingTable0[g_ActiveBufferIdx];

    if (D_800C4168.field_2 != 0)
    {
        func_80041074(ot, D_800C4168.field_54, &D_800C4168.field_58, &D_800C4168.field_60);
    }

    if (D_800C4168.field_0 == 1 && D_800C4168.field_50 != 0)
    {
        func_8008D470(D_800C4168.field_50, &D_800C4168.field_58, &D_800C4168.field_60, D_800C4168.waterZones_4);
    }

    if (D_800C4168.screenBrightness_8 > 0)
    {
        poly            = (POLY_G4*)GsOUT_PACKET_P;
        mode            = (DR_MODE*)(GsOUT_PACKET_P + sizeof(POLY_G4));
        GsOUT_PACKET_P += sizeof(POLY_G4) + sizeof(DR_MODE);

        color0           = (D_800C4168.screenBrightness_8 + (D_800C4168.screenBrightness_8 << 8)) + (D_800C4168.screenBrightness_8 << 16);
        *(s32*)&poly->r3 = color0;
        *(s32*)&poly->r2 = color0;
        *(s32*)&poly->r1 = color0;
        *(s32*)&poly->r0 = color0;

        setPolyG4(poly);
        setSemiTrans(poly, 1);
        setXY4(poly,
               -180, -120,
                180, -120,
               -180,  120,
                180,  120);

        AddPrim(ot->org, poly);
        SetDrawMode(mode, 0, 1, 0x20, NULL);
        AddPrim(ot->org, mode);
    }

    packet2 = GsOUT_PACKET_P;
    packet  = packet2;

    SetPriority(packet2, 0, 0);
    AddPrim(&ot->org[2047], packet2);

    poly           = (POLY_G4*)(packet + 0xC);
    GsOUT_PACKET_P = packet + 0x30;

    color2           = *(s32*)&D_800C4168.fogColor_1C;
    *(s32*)&poly->r3 = color2;
    *(s32*)&poly->r2 = color2;
    *(s32*)&poly->r1 = color2;
    *(s32*)&poly->r0 = color2;

    SetPolyG4(poly);
    setXY4(poly,
           -180, -120,
            180, -120,
           -180,  120,
            180,  120);

    AddPrim(&ot->org[2047], poly);
    packet = GsOUT_PACKET_P;
    SetPriority(packet, 0, 1);
    AddPrim(&ot->org[2047], packet);

    GsOUT_PACKET_P = packet + sizeof(DR_MODE);
    mode           = (DR_MODE*)GsOUT_PACKET_P;

    SetDrawMode(mode, 0, 1, 32, NULL);
    AddPrim(&ot->org[2047], mode);

    GsOUT_PACKET_P = packet + 24;
}

void func_80055330(u8 arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) // 0x80055330
{
    D_800C4168.field_0             = arg0;
    D_800C4168.field_20            = arg1;
    D_800C4168.field_3             = arg2;
    D_800C4168.worldTintColor_28.r = arg3 >> 5;
    D_800C4168.field_2C.m[0][2]    = arg3;
    D_800C4168.field_2C.m[0][1]    = arg3;
    D_800C4168.field_2C.m[0][0]    = arg3;
    D_800C4168.worldTintColor_28.g = arg4 >> 5;
    D_800C4168.screenBrightness_8  = arg6;
    D_800C4168.worldTintColor_28.b = arg5 >> 5;
    D_800C4168.field_2C.m[1][2]    = (s16)arg4;
    D_800C4168.field_2C.m[1][1]    = (s16)arg4;
    D_800C4168.field_2C.m[1][0]    = (s16)arg4;
    D_800C4168.field_2C.m[2][2]    = (s16)arg5;
    D_800C4168.field_2C.m[2][1]    = (s16)arg5;
    D_800C4168.field_2C.m[2][0]    = (s16)arg5;
    D_800C4168.field_24            = (arg3 * arg1) >> 17;
    D_800C4168.field_25            = (arg4 * arg1) >> 17;
    D_800C4168.field_26            = (arg5 * arg1) >> 17;
}

void Gfx_FogParamsSet(u8 fogEnabled, u8 fogColorR, u8 fogColorG, u8 fogColorB) // 0x800553C4
{
    D_800C4168.fogEnabled_1  = fogEnabled;
    D_800C4168.fogColor_1C.r = fogColorR;
    D_800C4168.fogColor_1C.g = fogColorG;
    D_800C4168.fogColor_1C.b = fogColorB;
}

void func_800553E0(u32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6) // 0x800553E0
{
    D_800C4168.field_2 = arg0;

    if (arg0 != 0)
    {
        func_80040E7C(arg1, arg2, arg3, arg4, arg5, arg6);
    }
}

void func_80055434(VECTOR3* vec) // 0x80055434
{
    *vec = D_800C4168.field_60;
}

s32 func_8005545C(SVECTOR* vec) // 0x8005545C
{
    *vec = D_800C4168.field_6C;
    return D_800C4168.field_54;
}

s32 func_80055490(SVECTOR* arg0) // 0x80055490
{
    *arg0 = D_800C4168.field_58;
    return D_800C4168.field_54;
}

void func_800554C4(s32 arg0, s16 arg1, GsCOORDINATE2* coord0, GsCOORDINATE2* coord1, SVECTOR* rot, q19_12 x, q19_12 y, q19_12 z, s_WaterZone* waterZones) // 0x800554C4
{
    MATRIX   mat;
    SVECTOR  tempSvec;
    VECTOR   vec;
    VECTOR3* ptr;
    VECTOR3* ptr2; // Q19.12

    D_800C4168.field_54 = arg0;
    D_800C4168.field_50 = arg1;
    D_800C4168.waterZones_4  = waterZones;

    if (coord0 == NULL)
    {
        D_800C4168.field_58 = *rot;
    }
    else
    {
        Vw_CoordHierarchyMatrixCompute(coord0, &mat);
        ApplyMatrixSV(&mat, rot, &D_800C4168.field_58);
    }

    if (coord1 == NULL)
    {
        ptr     = &D_800C4168.field_60;
        ptr->vx = x;
        ptr->vy = y;
        ptr->vz = z;
    }
    else
    {
        Vw_CoordHierarchyMatrixCompute(coord1, &mat);

        tempSvec.vx = Q12_TO_Q8(x);
        tempSvec.vy = Q12_TO_Q8(y);
        tempSvec.vz = Q12_TO_Q8(z);

        ApplyMatrix(&mat, &tempSvec, &vec);

        ptr2     = &D_800C4168.field_60;
        ptr2->vx = Q8_TO_Q12(vec.vx + mat.t[0]);
        ptr2->vy = Q8_TO_Q12(vec.vy + mat.t[1]);
        ptr2->vz = Q8_TO_Q12(vec.vz + mat.t[2]);
    }

    vwVectorToAngle(&D_800C4168.field_6C, &D_800C4168.field_58);
    D_800C4168.field_4C = arg0 >> 8;
    func_80055648(arg0, &D_800C4168.field_58);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80055648); // 0x80055648

s32 func_800557DC() // 0x800557DC
{
    MATRIX mat;

    func_80049C2C(&mat, D_800C4168.field_60.vx, D_800C4168.field_60.vy, D_800C4168.field_60.vz);
    return Q8_TO_Q12(mat.t[2]);
}

void func_80055814(s32 arg0) // 0x80055814
{
    D_800C4168.fogRelated_18 = Q12(1.0f) - func_800559A8(arg0);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80055840); // 0x80055840

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_800559A8); // 0x800559A8

u8 func_80055A50(s32 arg0) // 0x80055A50
{
    s32 temp;

    temp = arg0 >> 4;

    if (temp >= (1 << D_800C4168.fogRelated_14))
    {
        return 255;
    }

    return D_800C4168.field_CC[(temp << 7) >> D_800C4168.fogRelated_14];
}

void func_80055A90(CVECTOR* arg0, CVECTOR* arg1, u8 arg2, s32 arg3) // 0x80055A90
{
    s32 var_v1;

    arg3 = arg3 >> 4;
    if (arg3 < 0)
    {
        arg3 = 0;
    }

    if (arg3 < (1 << D_800C4168.fogRelated_14))
    {
        arg3 = D_800C4168.field_CC[(arg3 << 7) >> D_800C4168.fogRelated_14] << 4;
    }
    else
    {
        arg3 = 0xFF << 4;
    }

    var_v1 = Q12(1.0f) - (D_800C4168.fogRelated_18 + arg3);
    if (var_v1 < 0)
    {
        var_v1 = 0;
    }

    gte_lddp(var_v1);
    gte_ldrgb(&D_800C4168.fogColor_1C);

    gte_SetFarColor(0, 0, 0);

    gte_dpcs();

    gte_strgb(arg0);

    gte_lddp(arg3);
    gte_ldrgb(&D_800C4168.worldTintColor_28);

    gte_ldsv_(arg2 << 5);

    gte_dpcl();

    gte_strgb(arg1);
}

void func_80055B74(CVECTOR* result, CVECTOR* color, s32 arg2) // 0x80055B74
{
    s32 var_v0;
    s32 var_t0;

    arg2 >>= 4;

    var_t0 = D_800C4168.field_20 >> 5;

    if (arg2 < (1 << D_800C4168.fogRelated_14))
    {
        var_v0 = D_800C4168.field_CC[(arg2 << 7) >> D_800C4168.fogRelated_14];
    }
    else
    {
        var_v0 = 255;
    }

    var_v0 <<= 4;

    gte_lddp(var_v0);
    gte_ldrgb(color);
    gte_SetFarColor(D_800C4168.fogColor_1C.r, D_800C4168.fogColor_1C.g, D_800C4168.fogColor_1C.b);
    gte_ldsv_(var_t0 << 5);
    gte_dpcl();
    gte_strgb(result);
    gte_SetFarColor(0, 0, 0);
}

void func_80055C3C(CVECTOR* result, CVECTOR* color, s32 arg2, s32 arg3, s32 arg4, s32 arg5) // 0x80055C3C
{
    s32 temp_a1;
    s32 var_v0;
    s32 var_s0;

    var_s0  = arg5 >> 4;
    temp_a1 = func_80055D78(arg2, arg3, arg4);

    if (D_800C4168.fogEnabled_1)
    {
        if (var_s0 < (1 << D_800C4168.fogRelated_14))
        {
            var_v0 = D_800C4168.field_CC[(var_s0 << 7) >> D_800C4168.fogRelated_14];
        }
        else
        {
            var_v0 = 255;
        }

        gte_lddp(var_v0 << 4);
        gte_ldrgb(color);
        gte_SetFarColor(D_800C4168.fogColor_1C.r, D_800C4168.fogColor_1C.g, D_800C4168.fogColor_1C.b);
        gte_ldsv_(temp_a1 << 5);

        gte_dpcl();
        gte_strgb(result);

        gte_SetFarColor(0, 0, 0);
    }
    else
    {
        gte_lddp(Q12(1.0f) - (temp_a1 << 5));
        gte_ldrgb(color);
        gte_dpcs();
        gte_strgb(result);
    }
}

u8 func_80055D78(q19_12 x, q19_12 y, q19_12 z) // 0x80055D78
{
    q23_8    vec[3];
    s32      temp_v1;
    q23_8    tempX;
    s32      var_a3;
    s32      i;
    VECTOR3* ptr0;
    VECTOR3* ptr1;

    vec[0] = Q12_TO_Q8(x) - Q12_TO_Q8(D_800C4168.field_60.vx);
    vec[1] = Q12_TO_Q8(y) - Q12_TO_Q8(D_800C4168.field_60.vy);
    vec[2] = Q12_TO_Q8(z) - Q12_TO_Q8(D_800C4168.field_60.vz);

    if (D_800C4168.field_0 != 0)
    {
        ptr1 = &D_800C4168.field_84;
        for (i = 0, ptr0 = ptr1, var_a3 = 0xFF;
             i < ARRAY_SIZE(vec);
             i++, ptr0 += 2)
        {
            tempX = vec[i];
            ptr1  = ptr0;
            if (tempX < 0)
            {
                tempX = -tempX;
                ptr1++;
            }

            temp_v1 = ptr1->vy + FP_MULTIPLY(ptr1->vz, tempX - ptr1->vx, Q12_SHIFT);
            if (temp_v1 < var_a3)
            {
                var_a3 = temp_v1;
            }
        }
    }
    else
    {
        var_a3 = 0;
    }

    var_a3 += D_800C4168.field_20 >> 5;

    limitRange(var_a3, 0, D_800C4168.field_3);
    return var_a3;
}

void func_80055E90(CVECTOR* color, u8 fadeAmount) // 0x80055E90
{
    s32 alpha;
    u8  prev_cd;

    alpha = Q12(1.0f) - (fadeAmount * 32);

    // Works similar to `gte_DpqColor` macro, but `gte_lddp`/`gte_ldrgb` are in wrong order?

    gte_lddp(alpha);
    gte_ldrgb(&D_800C4168.worldTintColor_28);
    gte_dpcs();

    prev_cd = color->cd;
    gte_strgb(color);
    color->cd = prev_cd;
}

void func_80055ECC(CVECTOR* color, SVECTOR3* arg1, SVECTOR3* arg2, MATRIX* mat) // 0x80055ECC
{
    func_80055E90(color, func_80055F08(arg1, arg2, mat));
}

u8 func_80055F08(SVECTOR3* arg0, SVECTOR3* arg1, MATRIX* mat) // 0x80055F08
{
    MATRIX  rotMat;
    DVECTOR screenPos;
    s32     geomOffsetX;
    s32     geomOffsetY;
    s32     depthP;
    s32     geomScreen;
    s32     ret;
    s32     var_v1;
    u8      field_3;
    s32     field_20;

    func_80057228(mat, D_800C4168.field_54, &D_800C4168.field_58, &D_800C4168.field_60);

    gte_lddqa(D_800C4168.field_4C);
    gte_lddqb_0();
    gte_ldtr_0();

    ReadGeomOffset(&geomOffsetX, &geomOffsetY);
    geomScreen = ReadGeomScreen();
    SetGeomOffset(-1024, -1024);
    SetGeomScreen(16);

    rotMat.m[0][0] = D_800C4168.field_74.vx;
    rotMat.m[0][1] = D_800C4168.field_74.vy;
    rotMat.m[0][2] = D_800C4168.field_74.vz;
    rotMat.m[1][0] = -arg1->vx;
    rotMat.m[1][1] = -arg1->vy;
    rotMat.m[1][2] = -arg1->vz;
    rotMat.m[2][0] = arg0->vx - D_800C4168.field_7C.vx;
    rotMat.m[2][1] = arg0->vy - D_800C4168.field_7C.vy;
    rotMat.m[2][2] = arg0->vz - D_800C4168.field_7C.vz;

    field_3  = D_800C4168.field_3;
    field_20 = D_800C4168.field_20 >> 5;

    SetRotMatrix(&rotMat);

    gte_ldv0(&rotMat.m[2][0]);
    gte_rtps();
    gte_stsxy(&screenPos);
    gte_stdp(&depthP);

    screenPos.vx += 1024;
    screenPos.vy += 1024;

    ret   = (screenPos.vx * screenPos.vy) + (screenPos.vy * (depthP >> 4));
    ret >>= 5;
    ret  -= 16;
    if (ret < 0)
    {
        ret = 0;
    }

    ret += field_20;

    var_v1 = (screenPos.vx >> 1) + (depthP >> 2);
    if (var_v1 > 48)
    {
        var_v1 = 48;
    }

    ret = ret + var_v1;
    if (field_3 < ret)
    {
        ret = field_3;
    }

    SetGeomOffset(geomOffsetX, geomOffsetY);
    SetGeomScreen(geomScreen);

    return ret;
}

void LmHeader_FixOffsets(s_LmHeader* lmHdr) // 0x800560FC
{
    s32 i;

    if (lmHdr->isLoaded_2 == true)
    {
        return;
    }
    lmHdr->isLoaded_2 = true;

    // Add memory address of header to pointer fields.
    lmHdr->materials_4    = (u8*)lmHdr->materials_4    + (u32)lmHdr;
    lmHdr->modelHdrs_C = (u8*)lmHdr->modelHdrs_C + (u32)lmHdr;
    lmHdr->modelOrder_10  = (u8*)lmHdr->modelOrder_10  + (u32)lmHdr;

    for (i = 0; i < lmHdr->modelCount_8; i++)
    {
        if (lmHdr->magic_0 == LM_HEADER_MAGIC)
        {
            ModelHeader_FixOffsets(&lmHdr->modelHdrs_C[i], lmHdr);
        }
    }
}

void ModelHeader_FixOffsets(s_ModelHeader* modelHdr, s_LmHeader* lmHdr) // 0x800561A4
{
    s_MeshHeader* curMeshHdr;

    modelHdr->meshHdrs_C = (u8*)modelHdr->meshHdrs_C + (u32)lmHdr;

    for (curMeshHdr = &modelHdr->meshHdrs_C[0]; curMeshHdr < &modelHdr->meshHdrs_C[modelHdr->meshCount_8]; curMeshHdr++)
    {
        curMeshHdr->primitives_4 = (u8*)curMeshHdr->primitives_4 + (u32)lmHdr;
        curMeshHdr->verticesXy_8 = (u8*)curMeshHdr->verticesXy_8 + (u32)lmHdr;
        curMeshHdr->verticesZ_C  = (u8*)curMeshHdr->verticesZ_C  + (u32)lmHdr;
        curMeshHdr->normals_10   = (u8*)curMeshHdr->normals_10   + (u32)lmHdr;
        curMeshHdr->unkPtr_14    = (u8*)curMeshHdr->unkPtr_14    + (u32)lmHdr;
    }
}

void func_80056244(s_LmHeader* lmHdr, bool unkFlag) // 0x80056244
{
    s_ModelHeader* modelHdrs;
    s_ModelHeader* curModelHdr;
    s_MeshHeader*  curMeshHdr;
    s_Primitive*   prim;

    modelHdrs = lmHdr->modelHdrs_C;

    for (curModelHdr = &modelHdrs[0]; curModelHdr < &modelHdrs[lmHdr->modelCount_8]; curModelHdr++)
    {
        for (curMeshHdr = &curModelHdr->meshHdrs_C[0]; curMeshHdr < &curModelHdr->meshHdrs_C[curModelHdr->meshCount_8]; curMeshHdr++)
        {
            for (prim = &curMeshHdr->primitives_4[0]; prim < &curMeshHdr->primitives_4[curMeshHdr->primitiveCount_0]; prim++)
            {
                prim->field_6_15 = unkFlag;
            }
        }
    }
}

s32 Lm_MaterialCount(bool (*filterFunc)(s_Material* mat), s_LmHeader* lmHdr) // 0x80056348
{
    s32         count;
    s_Material* curMat;

    count = 0;
    for (curMat = lmHdr->materials_4; curMat < (lmHdr->materials_4 + lmHdr->materialCount_3); curMat++)
    {
        if (filterFunc(curMat))
        {
            count++;
        }
    }

    return count;
}

void func_800563E8(s_LmHeader* lmHdr, s32 arg1, s32 arg2, s32 arg3) // 0x800563E8
{
    s32         i;
    s_Material* curMat;

    if (arg2 < 0)
    {
        arg2 += 15;
    }

    for (i = 0, curMat = &lmHdr->materials_4[0];
         i < lmHdr->materialCount_3;
         i++, curMat++)
    {
        // TODO: Bitfield stuff? Doesn't seem to match other uses of `field_E`/`field_10` we've seen though.
        u8  temp_a0 = curMat->field_E;
        u16 temp_v1 = curMat->field_10;

        curMat->field_E  = ((temp_a0 + arg1) & 0x1F) | (temp_a0 & 0xE0);
        curMat->field_10 = ((temp_v1 + (arg2 >> 4)) & 0x3F) | ((temp_v1 + (arg3 << 6)) & 0x7FC0);
    }
}

void Lm_MaterialFileIdxApply(s_LmHeader* lmHdr, s32 fileIdx, s_FsImageDesc* image, s32 blendMode) // 0x80056464
{
    char  sp10[8];
    char  sp18[16];
    char* sp10Ptr;
    char* sp18Ptr;

    // Probably a `memset`.
    *(int*)sp10 = *(int*)(sp10 + 4) = 0;

    Fs_GetFileName(sp18, fileIdx);

    sp10Ptr = sp10;
    sp18Ptr = sp18;

    while (sp10Ptr < sp18 && *sp18Ptr != '.')
    {
        *sp10Ptr++ = *sp18Ptr++;
    }

    Lm_MaterialFsImageApply(lmHdr, sp10, image, blendMode);
}

void func_80056504(s_LmHeader* lmHdr, char* newStr, s_FsImageDesc* image, s32 blendMode) // 0x80056504
{
    char sp10[8];

    StringCopy(sp10, newStr);
    Lm_MaterialFsImageApply(lmHdr, sp10, image, blendMode);
}

bool Lm_MaterialFsImageApply(s_LmHeader* lmHdr, char* fileName, s_FsImageDesc* image, s32 blendMode) // 0x80056558
{
    s_Material* curMat;

    for (curMat = &lmHdr->materials_4[0];
         curMat < &lmHdr->materials_4[lmHdr->materialCount_3];
         curMat++)
    {
        if (!COMPARE_FILENAMES(&curMat->name_0, fileName))
        {
            curMat->field_C = 1;
            Material_FsImageApply(curMat, image, blendMode);
            return true;
        }
    }

    return false;
}

void Material_FsImageApply(s_Material* mat, s_FsImageDesc* image, s32 blendMode) // 0x8005660C
{
    s32 coeff;

    coeff = 4;
    switch (image->tPage[0])
    {
        default:
        case 0:
            break;

        case 1:
            coeff = 2;
            break;

        case 2:
            coeff = 1;
            break;
    }

    mat->field_14.u8[0] = image->u * coeff;
    mat->field_14.u8[1] = image->v;

    // Set GPU flags.
    mat->field_E  = ((image->tPage[0] & 0x3) << 7) | // X bits of texture page.
                    ((blendMode & 0x3) << 5) |       // Semi-transparency blend mode.
                    (image->tPage[1] & (1 << 4)) |   // dither/texture-depth flag.
                    (image->tPage[1] & 0xF);         // Y bits + color depth.
    mat->field_10 = (image->clutY << 6) |
                    ((image->clutX >> 4) & 0x3F);
}

void func_800566B4(s_LmHeader* lmHdr, s_FsImageDesc* images, s8 unused, s32 startIdx, s32 blendMode) // 0x800566B4
{
    char           filename[16];
    s32            i;
    s_Material*    curMat;
    s_FsImageDesc* curImage;

    // Loop could be using `&image[i]`/`&arg0->field_4[i]` instead? Wasn't able to make that match though.
    for (i = 0, curImage = images, curMat = lmHdr->materials_4;
         i < lmHdr->materialCount_3;
         i++, curMat++, curImage++)
    {
        Material_TimFileNameGet(filename, curMat);
        Fs_QueueStartReadTim(Fs_FindNextFile(filename, 0, startIdx), FS_BUFFER_9, curImage);
        Material_FsImageApply(curMat, curImage, blendMode);
    }
}

void Lm_MaterialsLoadWithFilter(s_LmHeader* lmHdr, s_ActiveTextures* activeTexs, bool (*filterFunc)(s_Material* mat), s32 fileIdx, s32 blendMode) // 0x80056774
{
    s_Material* curMat;

    for (curMat = &lmHdr->materials_4[0]; curMat < &lmHdr->materials_4[lmHdr->materialCount_3]; curMat++)
    {
        if (curMat->field_C == 0 && curMat->texture_8 == NULL &&
            (filterFunc == NULL || filterFunc(curMat)))
        {
            curMat->texture_8 = Texture_Get(curMat, activeTexs, FS_BUFFER_9, fileIdx, blendMode);
            if (curMat->texture_8 != NULL)
            {
                Material_FsImageApply(curMat, &curMat->texture_8->imageDesc_0, blendMode);
            }
        }
    }
}

bool LmHeader_IsTextureLoaded(s_LmHeader* lmHdr) // 0x80056888
{
    s_Material* curMat;

    if (!lmHdr->isLoaded_2)
    {
        return false;
    }

    for (curMat = &lmHdr->materials_4[0]; curMat < &lmHdr->materials_4[lmHdr->materialCount_3]; curMat++)
    {
        if (curMat->field_C != 0)
        {
            continue;
        }

        if (curMat->texture_8 == NULL)
        {
            return false;
        }

        if (!Fs_QueueIsEntryLoaded(curMat->texture_8->queueIdx_10))
        {
            return false;
        }
    }

    return true;
}

void Lm_MaterialFlagsApply(s_LmHeader* lmHdr) // 0x80056954
{
    s32         i;
    s32         j;
    s32         flags;
    s_Material* curMat;

    for (i = 0, curMat = lmHdr->materials_4; i < lmHdr->materialCount_3; i++, curMat++)
    {
        flags = (curMat->field_E != curMat->field_F) ? (1 << 0) : 0;

        if (curMat->field_10 != curMat->field_12)
        {
            flags |= 1 << 1;
        }

        if (curMat->field_14.u16 != curMat->field_16.u16)
        {
            flags |= 1 << 2;
        }

        if (flags)
        {
            for (j = 0; j < lmHdr->modelCount_8; j++)
            {
                if (lmHdr->magic_0 == LM_HEADER_MAGIC)
                {
                    Model_MaterialFlagsApply(&lmHdr->modelHdrs_C[j], i, curMat, flags);
                }
            }

            curMat->field_F        = curMat->field_E;
            curMat->field_12       = curMat->field_10;
            curMat->field_16.u8[0] = curMat->field_14.u8[0];
            curMat->field_16.u8[1] = curMat->field_14.u8[1];
        }
    }
}

void Model_MaterialFlagsApply(s_ModelHeader* modelHdr, s32 arg1, s_Material* mat, s32 flags) // 0x80056A88
{
    u16           field_14;
    u16           field_16;
    s_MeshHeader* curMeshHdr;
    s_Primitive*  curPrim;

    for (curMeshHdr = modelHdr->meshHdrs_C; curMeshHdr < &modelHdr->meshHdrs_C[modelHdr->meshCount_8]; curMeshHdr++)
    {
        for (curPrim = curMeshHdr->primitives_4; curPrim < &curMeshHdr->primitives_4[curMeshHdr->primitiveCount_0]; curPrim++)
        {
            if (curPrim->field_6_8 == NO_VALUE)
            {
                curPrim->field_6_0 = 32;
            }

            if (curPrim->field_6_8 == arg1)
            {
                if (flags & (1 << 0))
                {
                    curPrim->field_6_0 = mat->field_E;
                }
                if (flags & (1 << 1))
                {
                    curPrim->field_2 = mat->field_10 + (curPrim->field_2 - mat->field_12);
                }
                if (flags & (1 << 2))
                {
                    field_16      = mat->field_16.u16;
                    field_14      = mat->field_14.u16;
                    curPrim->field_0 = field_14 + (curPrim->field_0 - field_16);
                    curPrim->field_4 = field_14 + (curPrim->field_4 - field_16);
                    curPrim->field_8 = field_14 + (curPrim->field_8 - field_16);
                    curPrim->field_A = field_14 + (curPrim->field_A - field_16);
                }
            }
        }
    }
}

void Lm_MaterialRefCountDec(s_LmHeader* lmHdr) // 0x80056BF8
{
    s_Material* curMat;
    s_Texture*  tex;

    for (curMat = &lmHdr->materials_4[0]; curMat < &lmHdr->materials_4[lmHdr->materialCount_3]; curMat++)
    {
        tex = curMat->texture_8;
        if (tex != NULL)
        {
            tex->refCount_14--;
            if (tex->refCount_14 < 0)
            {
                tex->refCount_14 = 0;
            }

            curMat->texture_8 = NULL;
        }
    }
}

s32 LmHeader_ModelCountGet(s_LmHeader* lmHdr) // 0x80056C80
{
    return lmHdr->modelCount_8;
}

void Bone_ModelAssign(s_Bone* bone, s_LmHeader* lmHdr, s32 modelHdrIdx)
{
    s_ModelHeader* modelHdr;

    modelHdr = lmHdr->modelHdrs_C;
    bone->modelInfo_0.modelIdx_C = modelHdrIdx;

    if (lmHdr->magic_0 == LM_HEADER_MAGIC)
    {
        bone->modelInfo_0.modelHdr_8 = &modelHdr[modelHdrIdx];
    }
}

bool Lm_ModelFind(s_WorldObject_0* arg0, s_LmHeader* lmHdr, s_WorldObject_0_10* arg2) // 0x80056CB4
{
    u_Filename     sp10;
    s32            modelHdrCount;
    bool           result;
    s32            i;
    s_ModelHeader* modelHdr;

    result = false;

    StringCopy(sp10.str, arg2->name_0.str);

    modelHdrCount = lmHdr->modelCount_8;

    if (lmHdr->magic_0 == LM_HEADER_MAGIC)
    {
        for (i = 0, modelHdr = &lmHdr->modelHdrs_C[i]; i < modelHdrCount; i++, modelHdr++)
        {
            if (!COMPARE_FILENAMES(&modelHdr->name_0, &sp10))
            {
                result                       = true;
                arg0->modelInfo_0.modelIdx_C = i;
                arg0->modelInfo_0.modelHdr_8 = modelHdr;
            }
        }
    }

    return result;
}

void StringCopy(char* prevStr, char* newStr) // 0x80056D64
{
    *(s32*)&prevStr[4] = 0;
    *(s32*)&prevStr[0] = 0;
    strncpy(prevStr, newStr, 8);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80056D8C); // 0x80056D8C

void func_80057090(s_ModelInfo* modelInfo, GsOT* arg1, void* arg2, MATRIX* mat0, MATRIX* mat1, u16 arg5) // 0x80057090
{
    s32            temp_a0;
    GsOT_TAG*      otTag;
    s_ModelHeader* modelHdr;

    modelHdr = modelInfo->modelHdr_8;

    if (modelInfo->field_0 < 0)
    {
        return;
    }

    otTag = &arg1->org[func_800571D0(modelHdr->field_B_1)];
    temp_a0 = modelHdr->field_B_4;
    if ((temp_a0 & 0xFF) && temp_a0 >= 0 && temp_a0 < 4) // TODO: `& 0xFF` needed for match.
    {
        func_80059D50(temp_a0, modelInfo, mat0, arg2, otTag);
    }
    else
    {
        if (mat1 != NULL && D_800C4168.field_0 != 0)
        {
            func_80057228(mat1, D_800C4168.field_54, &D_800C4168.field_58, &D_800C4168.field_60);
        }

        if (modelHdr->field_B_0)
        {
            D_800C42B4 = arg5;
            func_8005A21C(modelInfo, otTag, arg2, mat0);
        }
        else
        {
            func_80057344(modelInfo, otTag, arg2, mat0);
        }
    }
}

s32 func_800571D0(u32 arg0) // 0x800571D0
{
    switch (arg0)
    {
        default:
        case 0:
            return 2;

        case 1:
            return 0;

        case 2:
            return 4;

        case 3:
            return 33;

        case 4:
            return 66;

        case 5:
            return 99;
    }
}

void func_80057228(MATRIX* mat, s32 alpha, SVECTOR* arg2, VECTOR3* arg3) // 0x80057228
{
    s32 x;
    s32 y;
    s32 z;

    gte_SetRotMatrix_custom(mat);

    gte_ldv0(arg2);
    gte_rtv0();
    gte_lddp(alpha);
    gte_gpf12();
    gte_stsv(&D_800C4168.field_74);

    // Divide arg3 by 16 and subtract matrix translation
    x = (arg3->vx >> 4) - mat->t[0];
    y = (arg3->vy >> 4) - mat->t[1];
    z = (arg3->vz >> 4) - mat->t[2];

    gte_LoadVector0_XYZ(x, y, z);

    gte_rtv0();

    gte_stsv(&D_800C4168.field_7C);
}

void func_80057344(s_ModelInfo* modelInfo, GsOT_TAG* otTag, void* arg2, MATRIX* mat) // 0x80057344
{
    u32               normalOffset;
    u32               vertOffset;
    s_MeshHeader*     curMeshHdr;
    s_ModelHeader*    modelHdr;
    s_GteScratchData* scratchData;

    scratchData = PSX_SCRATCH_ADDR(0);

    modelHdr     = modelInfo->modelHdr_8;
    vertOffset   = modelHdr->vertexOffset_9;
    normalOffset = modelHdr->normalOffset_A;

    gte_lddqa(D_800C4168.field_4C);
    gte_lddqb_0();

    for (curMeshHdr = modelHdr->meshHdrs_C; curMeshHdr < &modelHdr->meshHdrs_C[modelHdr->meshCount_8]; curMeshHdr++)
    {
        if (vertOffset != 0 || normalOffset != 0)
        {
            func_8005759C(curMeshHdr, scratchData, vertOffset, normalOffset);
        }
        else
        {
            func_800574D4(curMeshHdr, scratchData);
        }

        switch (D_800C4168.field_0)
        {
            case 0:
                break;

            case 1:
                func_80057658(curMeshHdr, normalOffset, scratchData, &D_800C4168.field_74, &D_800C4168.field_7C);
                break;

            case 2:
                func_80057A3C(curMeshHdr, normalOffset, scratchData, &D_800C4168.field_74);
                break;
        }

        func_80057B7C(curMeshHdr, vertOffset, scratchData, mat);
        func_8005801C(curMeshHdr, scratchData, otTag, arg2);
    }
}

void func_800574D4(s_MeshHeader* meshHdr, s_GteScratchData* scratchData) // 0x800574D4
{
    DVECTOR* vertexXy;
    s16*     vertexZ;
    DVECTOR* screenXy;
    s16*     var_a2;
    u8*      unkPtr;
    u8*      unkPtrDest;

    screenXy = &scratchData->screenXy_0[0];
    var_a2   = &scratchData->field_18C[0]; // `screenZ`? There's already an earlier struct field though.
    vertexXy = &meshHdr->verticesXy_8[0];
    vertexZ  = &meshHdr->verticesZ_C[0];

    while (var_a2 < &scratchData->field_18C[meshHdr->vertexCount_1])
    {
        *(u32*)screenXy++ = *(u32*)vertexXy++;

        *(u32*)var_a2 = *(u32*)vertexZ;
        vertexZ += 2;
        var_a2 += 2;
    }

    while (screenXy < &scratchData->screenXy_0[meshHdr->vertexCount_1])
    {
        *(u32*)screenXy++ = *(u32*)vertexXy++;
    }

    unkPtr     = &meshHdr->unkPtr_14[0];
    unkPtrDest = &scratchData->field_2B8[0];

    while (unkPtrDest < &scratchData->field_2B8[meshHdr->unkCount_3])
    {
        *(u32*)unkPtrDest = *(u32*)unkPtr;
        unkPtr += 4;
        unkPtrDest += 4;
    }
}

void func_8005759C(s_MeshHeader* meshHdr, s_GteScratchData* scratchData, s32 vertOffset, s32 normalOffset) // 0x8005759C
{
    s16* vertexZPtr;
    s16* field_18CPtr;
    s32* vertexXyPtr;
    s32* screenXyPtr;
    u8*  field_2B8Ptr;
    u8*  field_14Ptr;

    // Should be loop? Tried but no luck.
    screenXyPtr  = &scratchData->screenXy_0[vertOffset];
    field_18CPtr = &scratchData->field_18C[vertOffset];
    vertexXyPtr  = meshHdr->verticesXy_8;
    vertexZPtr   = meshHdr->verticesZ_C;
    while (vertexXyPtr < &meshHdr->verticesXy_8[meshHdr->vertexCount_1])
    {
        *screenXyPtr++  = *vertexXyPtr++;
        *field_18CPtr++ = *vertexZPtr++;
    }

    field_14Ptr  = meshHdr->unkPtr_14;
    field_2B8Ptr = &scratchData->field_2B8[normalOffset];
    while (field_14Ptr < &meshHdr->unkPtr_14[meshHdr->unkCount_3])
    {
        *field_2B8Ptr++ = *field_14Ptr++;
    }
}

void func_80057658(s_MeshHeader* meshHdr, s32 offset, s_GteScratchData* scratchData, SVECTOR3* arg3, SVECTOR* arg4) // 0x80057658
{
    s32       geomOffsetX;
    s32       geomOffsetY;
    s32       geomScreen;
    s32       temp_t9;
    s32       var_a1;
    s32       var_v1;
    s32       temp_t2;
    u8        temp_v1;
    u8*       end;
    u8*       var_t0;
    s16*      temp_t8;
    s32*      depthP;
    MATRIX*   mat;
    DVECTOR*  screenPos;
    s_Normal* curNormal;

    scratchData->field_3AC = *arg4; // 3AC changed to `SVECTOR`.

    scratchData->field_380.m[0][0] = arg3->vx;
    scratchData->field_380.m[0][1] = arg3->vy;
    scratchData->field_380.m[0][2] = arg3->vz;

    gte_ldtr_0();

    ReadGeomOffset(&geomOffsetX, &geomOffsetY);
    geomScreen = ReadGeomScreen();
    SetGeomOffset(-1024, -1024);
    SetGeomScreen(16);

    temp_t9 = D_800C4168.field_20 >> 5;
    temp_v1 = D_800C4168.field_3;

    var_t0 = &scratchData->field_2B8[offset];
    mat    = &scratchData->field_380;

    for (curNormal = meshHdr->normals_10; curNormal < &meshHdr->normals_10[meshHdr->normalCount_2]; curNormal++)
    {
        temp_t8   = &scratchData->field_380.m[2][0];
        screenPos = &scratchData->screenPos_3A4;
        depthP    = &scratchData->depthP_3A8;
        temp_t2   = temp_v1;

        *(u32*)&scratchData->field_3A0 = *(u32*)curNormal;

        mat->m[1][0] = scratchData->field_3A0.nx << 5;
        mat->m[1][1] = scratchData->field_3A0.ny << 5;
        mat->m[1][2] = scratchData->field_3A0.nz << 5;
        gte_SetRotMatrix_Row0_1(mat->m);

        end = &var_t0[scratchData->field_3A0.count];

        mat->m[2][0] = scratchData->screenXy_0[*var_t0].vx - scratchData->field_3AC.vx;
        mat->m[2][1] = scratchData->screenXy_0[*var_t0].vy - scratchData->field_3AC.vy;
        mat->m[2][2] = scratchData->field_18C[*var_t0] - scratchData->field_3AC.vz;
        gte_SetRotMatrix_Row2(mat->m);

        gte_ldv0(temp_t8);
        gte_rtps();
        gte_stsxy(screenPos);
        gte_stdp(depthP);

        while (++var_t0 < end)
        {
            mat->m[2][0] = scratchData->screenXy_0[*var_t0].vx - scratchData->field_3AC.vx;
            mat->m[2][1] = scratchData->screenXy_0[*var_t0].vy - scratchData->field_3AC.vy;
            mat->m[2][2] = scratchData->field_18C[*var_t0] - scratchData->field_3AC.vz;

            gte_SetRotMatrix_Row2(mat->m);
            gte_ldv0(temp_t8);
            gte_rtps();

            scratchData->screenPos_3A4.vx += 1024;
            scratchData->screenPos_3A4.vy += 1024;

            var_a1   = (scratchData->screenPos_3A4.vx * scratchData->screenPos_3A4.vy) + (scratchData->screenPos_3A4.vy * (scratchData->depthP_3A8 >> 4));
            var_a1 >>= 5;
            var_a1  -= 16;
            if (var_a1 < 0)
            {
                var_a1 = 0;
            }

            var_v1 = (scratchData->screenPos_3A4.vx >> 1) + (scratchData->depthP_3A8 >> 2);
            var_a1 += temp_t9;
            if (var_v1 > 48)
            {
                var_v1 = 48;
            }
            var_a1 += var_v1;

            if (temp_t2 < var_a1)
            {
                var_a1 = temp_t2;
            }

            *(var_t0 - 1) = var_a1;

            gte_stsxy(screenPos);
            gte_stdp(depthP);
        }

        scratchData->screenPos_3A4.vx += 1024;
        scratchData->screenPos_3A4.vy += 1024;

        var_a1   = (scratchData->screenPos_3A4.vx * scratchData->screenPos_3A4.vy) + (scratchData->screenPos_3A4.vy * (scratchData->depthP_3A8 >> 4));
        var_a1 >>= 5;
        var_a1  -= 16;
        if (var_a1 < 0)
        {
            var_a1 = 0;
        }

        var_v1  = (scratchData->screenPos_3A4.vx >> 1) + (scratchData->depthP_3A8 >> 2);
        var_a1 += temp_t9;
        if (var_v1 > 48)
        {
            var_v1 = 48;
        }
        var_a1 += var_v1;

        if (temp_t2 < var_a1)
        {
            var_a1 = temp_t2;
        }

        *(var_t0 - 1) = var_a1;
    }

    SetGeomOffset(geomOffsetX, geomOffsetY);
    SetGeomScreen(geomScreen);
}

void func_80057A3C(s_MeshHeader* meshHdr, s32 offset, s_GteScratchData* scratchData, SVECTOR3* lightVec) // 0x80057A3C
{
    s32       var_v1;
    s32       temp_t2;
    u8*       var_a3;
    void*     endPtr;
    s_Normal* normal;

    scratchData->field_380.m[0][0] = lightVec->vx;
    scratchData->field_380.m[0][1] = lightVec->vy;
    scratchData->field_380.m[0][2] = lightVec->vz;
    gte_SetLightMatrix(&scratchData->field_380);

    var_a3  = &scratchData->field_2B8[offset];
    temp_t2 = D_800C4168.field_20;

    for (normal = meshHdr->normals_10; normal < &meshHdr->normals_10[meshHdr->normalCount_2]; normal++)
    {
        *(u32*)&scratchData->field_3A0 = *(u32*)normal;

        scratchData->field_3AC.vx = scratchData->field_3A0.nx << 5;
        scratchData->field_3AC.vy = scratchData->field_3A0.ny << 5;
        scratchData->field_3AC.vz = scratchData->field_3A0.nz << 5;

        gte_ldv0(&scratchData->field_3AC);
        gte_ll();

        var_v1   = gte_stIR1();
        var_v1  += temp_t2;
        var_v1 >>= 5;

        if (var_v1 > 0xFF)
        {
            var_v1 = 0xFF;
        }

        endPtr = &var_a3[scratchData->field_3A0.count];
        for (; var_a3 < endPtr; var_a3++)
        {
            *var_a3 = var_v1;
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80057B7C); // 0x80057B7C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005801C); // 0x8005801C

void func_80059D50(s32 arg0, s_ModelInfo* modelInfo, MATRIX* mat, void* arg3, GsOT_TAG* arg4) // 0x80059D50
{
    s_GteScratchData* scratchData;
    s_MeshHeader*     curMeshHdr;
    s_ModelHeader*    modelHdr;

    scratchData = PSX_SCRATCH_ADDR(0);

    modelHdr = modelInfo->modelHdr_8;

    for (curMeshHdr = &modelHdr->meshHdrs_C[0]; curMeshHdr < &modelHdr->meshHdrs_C[modelHdr->meshCount_8]; curMeshHdr++)
    {
        func_800574D4(curMeshHdr, scratchData);
        func_80057B7C(curMeshHdr, 0, scratchData, mat);
        func_80059E34(arg0, curMeshHdr, scratchData, arg3, arg4);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80059E34); // 0x80059E34

void func_8005A21C(s_ModelInfo* modelInfo, GsOT_TAG* otTag, void* arg2, MATRIX* mat) // 0x8005A21C
{
    s16               var_v1;
    u32               normalOffset;
    u32               vertOffset;
    s_ModelHeader*    modelHdr;
    s_MeshHeader*     curMeshHdr;
    s_GteScratchData* scratchData;

    scratchData = PSX_SCRATCH_ADDR(0);

    if (D_800C4168.fogEnabled_1)
    {
        if (mat->t[2] < (1 << D_800C4168.fogRelated_14))
        {
            var_v1 = Q12(1.0f) - (D_800C4168.field_CC[(s32)(mat->t[2] << 7) >> D_800C4168.fogRelated_14] << 4);
        }
        else
        {
            var_v1 = 1 << 4;
        }
    }
    else
    {
        var_v1 = 256 << 4;
    }

    switch (D_800C4168.field_0)
    {
        case 0:
            func_8005A42C(scratchData, var_v1);
            break;

        case 1:
            func_8005A478(scratchData, var_v1);
            SetColorMatrix(&D_800C4168.field_2C);
            gte_lddqa(D_800C4168.field_4C);
            gte_lddqb_0();
            break;

        case 2:
            func_8005A838(scratchData, var_v1);
            SetColorMatrix(&D_800C4168.field_2C);
            gte_lddqa(D_800C4168.field_4C);
            gte_lddqb_0();
            break;
    }

    modelHdr     = modelInfo->modelHdr_8;
    vertOffset   = modelHdr->vertexOffset_9;
    normalOffset = modelHdr->normalOffset_A;

    for (curMeshHdr = modelHdr->meshHdrs_C; curMeshHdr < &modelHdr->meshHdrs_C[modelHdr->meshCount_8]; curMeshHdr++)
    {
        func_8005A900(curMeshHdr, vertOffset, scratchData, mat);

        if (D_800C4168.field_0 != 0)
        {
            func_8005AA08(curMeshHdr, normalOffset, scratchData);
        }

        func_8005AC50(curMeshHdr, scratchData, otTag, arg2);
    }
}

void func_8005A42C(s_GteScratchData* scratchData, q19_12 alpha) // 0x8005A42C
{
    q19_12 invAlpha = Q12(1.0f) - FP_MULTIPLY(alpha, D_800C4168.field_20, Q12_SHIFT);

    gte_lddp(invAlpha);
    gte_ldrgb(&D_800C4168.worldTintColor_28);
    gte_dpcs();
    gte_strgb(&scratchData->field_3D8);
}

void func_8005A478(s_GteScratchData* scratchData, q19_12 alpha) // 0x8005A478
{
    s32 geomOffsetX;
    s32 geomOffsetY;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_a0;
    s16 geomScreen;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a2;
    s32 var_s0;
    s32 var_t1;
    s32 var_v1;

    s32 temp_s0_neg;
    s32 temp_s1_neg;
    s32 temp_s2_neg;

    ReadGeomOffset(&geomOffsetX, &geomOffsetY);
    geomScreen = ReadGeomScreen();
    SetGeomOffset(-1024, -1024);
    SetGeomScreen(16);

    temp_s0 = D_800C4168.field_7C.vx;
    temp_s1 = D_800C4168.field_7C.vy;
    temp_s2 = D_800C4168.field_7C.vz;

    var_t1 = SquareRoot0(SQUARE(temp_s0) + SQUARE(temp_s1) + SQUARE(temp_s2));
    if (var_t1 == 0)
    {
        var_t1 = 1;
    }

    temp_s0_neg = -temp_s0;
    temp_s1_neg = -temp_s1;
    temp_s2_neg = -temp_s2;

    *(u32*)&scratchData->field_3E4.m[0][0] = *(u32*)&D_800C4168.field_74;
    scratchData->field_3E4.m[0][2]         = D_800C4168.field_74.vz;

    scratchData->field_3E4.m[1][0] = Q12(temp_s0_neg) / var_t1;
    scratchData->field_3E4.m[1][1] = Q12(temp_s1_neg) / var_t1;
    scratchData->field_3E4.m[1][2] = Q12(temp_s2_neg) / var_t1;

    scratchData->field_3E4.m[2][0] = temp_s0_neg;
    scratchData->field_3E4.m[2][1] = temp_s1_neg;
    scratchData->field_3E4.m[2][2] = temp_s2_neg;

    gte_SetRotMatrix(&scratchData->field_3E4);
    gte_SetVector0(&scratchData->field_3E4.m[2][0]);
    gte_ldtr_0();
    gte_rtps();
    gte_stsxy(&scratchData->screenPos_3DC);
    gte_stdp(&scratchData->depthP_3E0);

    scratchData->screenPos_3DC.vx += 1024;
    scratchData->screenPos_3DC.vy += 1024;

    var_s0  = (scratchData->screenPos_3DC.vx * scratchData->screenPos_3DC.vy) + (scratchData->screenPos_3DC.vy * (scratchData->depthP_3E0 >> 4));
    var_s0 >>= 5;
    var_s0  -= 16;
    if (var_s0 < 0)
    {
        var_s0 = 0;
    }

    var_v1 = (scratchData->screenPos_3DC.vx >> 1) + (scratchData->depthP_3E0 >> 2);
    if (var_v1 > 48)
    {
        var_v1 = 48;
    }

    var_s0  += var_v1;
    var_s0 >>= 1;
    if (D_800C4168.field_3 < var_s0)
    {
        var_s0 = D_800C4168.field_3;
    }

    var_s0 = FP_MULTIPLY(var_s0, alpha, Q12_SHIFT);

    if (var_s0 < 0)
    {
        var_s0 = 0;
    }

    if ((var_s0 >> 2) > 40)
    {
        var_a2 = var_s0 - 40;
    }
    else
    {
        var_a2 = var_s0 - (var_s0 >> 2);
    }

    temp_a0 = (scratchData->field_3E4.m[1][0] * var_a2) >> 7;
    temp_a0 = CLAMP(temp_a0, Q12(-1.4f), Q12(1.4f));

    temp_v1 = (scratchData->field_3E4.m[1][1] * var_a2) >> 7;
    temp_v1 = CLAMP(temp_v1, Q12(-1.4f), Q12(1.4f));

    gte_SetLightSourceXY(temp_a0, temp_v1);

    temp_a0 = (scratchData->field_3E4.m[1][2] * var_a2) >> 7;
    temp_a0 = CLAMP(temp_a0, Q12(-1.4f), Q12(1.4f));

    gte_SetLightSourceZ(temp_a0);

    SetGeomOffset(geomOffsetX, geomOffsetY);
    SetGeomScreen(geomScreen);

    var_a1 = 40;

    if ((var_s0 >> 2) <= 40)
    {
        var_a1 = (var_s0 >> 2);
    }

    if (var_a1 > 64)
    {
        var_a1 = 64;
    }

    SetBackColor(FP_MULTIPLY(D_800C4168.field_24 + ((D_800C4168.worldTintColor_28.r * var_a1) >> 7), alpha, Q12_SHIFT),
                 FP_MULTIPLY(D_800C4168.field_25 + ((D_800C4168.worldTintColor_28.g * var_a1) >> 7), alpha, Q12_SHIFT),
                 FP_MULTIPLY(D_800C4168.field_26 + ((D_800C4168.worldTintColor_28.b * var_a1) >> 7), alpha, Q12_SHIFT));
}

void func_8005A838(s_GteScratchData* scratchData, s32 scale) // 0x8005A838
{
    SVECTOR3 vec;

    vec.vx = FP_MULTIPLY(D_800C4168.field_74.vx, scale, Q12_SHIFT) >> 1;
    vec.vy = FP_MULTIPLY(D_800C4168.field_74.vy, scale, Q12_SHIFT) >> 1;
    vec.vz = FP_MULTIPLY(D_800C4168.field_74.vz, scale, Q12_SHIFT) >> 1;

    gte_SetLightSVector(&vec);

    SetBackColor(FP_MULTIPLY(D_800C4168.field_24, scale, Q12_SHIFT),
                 FP_MULTIPLY(D_800C4168.field_25, scale, Q12_SHIFT),
                 FP_MULTIPLY(D_800C4168.field_26, scale, Q12_SHIFT));
}

void func_8005A900(s_MeshHeader* meshHdr, s32 offset, s_GteScratchData* scratchData, MATRIX* mat) // 0x8005A900
{
    DVECTOR* inXy;  // Model-space XY input
    u16*     inZ;   // Model-space Z input
    DVECTOR* outXy; // Projected XY output buffer
    u16*     outZ;  // Projected Z output buffer

    if (meshHdr->vertexCount_1 == 0)
    {
        return;
    }

    SetRotMatrix(mat);
    SetTransMatrix(mat);

    outXy = &scratchData->screenXy_0[offset];
    outZ  = &scratchData->screenZ_168[offset];

    inXy = meshHdr->verticesXy_8;
    inZ  = meshHdr->verticesZ_C;

    while (outXy < &scratchData->screenXy_0[meshHdr->vertexCount_1 + offset])
    {
        // Nearly same as `gte_RotTransPers3`, processes 3 vertices per iteration.
        gte_LoadVector0_1_2_XYZ(inXy, inZ);
        gte_rtpt();
        gte_FetchScreen0_1_2_XYZ(outXy, outZ);

        outXy += 3;
        outZ  += 3;
        inXy  += 3;
        inZ   += 3;
    }
}

u8 func_8005AA08(s_MeshHeader* meshHdr, s32 arg1, s_GteScratchData2* scratchData) // 0x8005AA08
{
	// Same as `gte_strgb3`, but takes `VECTOR3` pointer to store results.
	// Not sure why this was needed, the func that uses it also ends up calling the normal `gte_strgb3` too.
    #define gte_strgb3_vec( r0 ) __asm__ volatile ( \
        "swc2	$20, 0( %0 );"                      \
        "swc2	$21, 4( %0 );"                      \
        "swc2	$22, 8( %0 )"                       \
        :                                           \
        : "r"( r0 )                                 \
        : "memory" )

    CVECTOR   sp0;
    s_Normal* var_a3;
    VECTOR3*  var_t0;

    if (meshHdr->normalCount_2 == 0)
    {
        return;
    }

    sp0.cd = 0;
    gte_ldrgb(&sp0);

    var_a3 = meshHdr->normals_10;
    *(u32*)&scratchData->u.normal.field_3DC = *(u32*)&var_a3[0];
    scratchData->u.normal.field_3E0[0].vx = scratchData->u.normal.field_3DC.nx << 5;
    scratchData->u.normal.field_3E0[0].vy = scratchData->u.normal.field_3DC.ny << 5;
    scratchData->u.normal.field_3E0[0].vz = scratchData->u.normal.field_3DC.nz << 5;

    *(u32*)&scratchData->u.normal.field_3DC = *(u32*)&var_a3[1];
    scratchData->u.normal.field_3E0[1].vx = scratchData->u.normal.field_3DC.nx << 5;
    scratchData->u.normal.field_3E0[1].vy = scratchData->u.normal.field_3DC.ny << 5;
    scratchData->u.normal.field_3E0[1].vz = scratchData->u.normal.field_3DC.nz << 5;

    *(u32*)&scratchData->u.normal.field_3DC = *(u32*)&var_a3[2];
    var_a3 += 3;
    scratchData->u.normal.field_3E0[2].vx = scratchData->u.normal.field_3DC.nx << 5;
    scratchData->u.normal.field_3E0[2].vy = scratchData->u.normal.field_3DC.ny << 5;
    scratchData->u.normal.field_3E0[2].vz = scratchData->u.normal.field_3DC.nz << 5;

    var_t0 = &scratchData->field_21C[arg1];

    gte_ldv3c(scratchData->u.normal.field_3E0);
    gte_nct();

    while(var_a3 < &meshHdr->normals_10[meshHdr->normalCount_2])
    {
        *(u32*)&scratchData->u.normal.field_3DC = *(u32*)&var_a3[0];
        scratchData->u.normal.field_3E0[0].vx = scratchData->u.normal.field_3DC.nx << 5;
        scratchData->u.normal.field_3E0[0].vy = scratchData->u.normal.field_3DC.ny << 5;
        scratchData->u.normal.field_3E0[0].vz = scratchData->u.normal.field_3DC.nz << 5;

        *(u32*)&scratchData->u.normal.field_3DC = *(u32*)&var_a3[1];
        scratchData->u.normal.field_3E0[1].vx = scratchData->u.normal.field_3DC.nx << 5;
        scratchData->u.normal.field_3E0[1].vy = scratchData->u.normal.field_3DC.ny << 5;
        scratchData->u.normal.field_3E0[1].vz = scratchData->u.normal.field_3DC.nz << 5;

        *(u32*)&scratchData->u.normal.field_3DC = *(u32*)&var_a3[2];
        var_a3 += 3;
        scratchData->u.normal.field_3E0[2].vx = scratchData->u.normal.field_3DC.nx << 5;
        scratchData->u.normal.field_3E0[2].vy = scratchData->u.normal.field_3DC.ny << 5;
        scratchData->u.normal.field_3E0[2].vz = scratchData->u.normal.field_3DC.nz << 5;

        gte_strgb3_vec(var_t0); // Store result of previous `gte_nct` call.
        var_t0++;
        gte_ldv3c(scratchData->u.normal.field_3E0);
        gte_nct();
    }

    gte_strgb3(&var_t0->vx, &var_t0->vy, &var_t0->vz); // Store result from final `gte_nct`.
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005AC50); // 0x8005AC50

void Texture_Init1(s_Texture* tex, char* texName, u8 tPage0, u8 tPage1, s32 u, s32 v, s16 clutX, s16 clutY) // 0x8005B1A0
{
    tex->imageDesc_0.tPage[0] = tPage0;
    tex->imageDesc_0.tPage[1] = tPage1;
    tex->imageDesc_0.u        = u;
    tex->imageDesc_0.v        = v;
    tex->imageDesc_0.clutX    = clutX;
    tex->imageDesc_0.clutY    = clutY;

    StringCopy(tex->name_8.str, texName);

    tex->refCount_14 = 0;
    tex->queueIdx_10 = NO_VALUE;
}

s_Texture* Texture_Get(s_Material* mat, s_ActiveTextures* activeTexs, void* fsBuffer9, s32 fileIdx, s32 arg4)
{
    s8         filename[12];
    s8         debugStr[12];
    s32        fileId;
    s32        i;
    s32        smallestQueueIdx;
    u32        queueIdx;
    s_Texture* curTex;
    s_Texture* foundTex;
    
    smallestQueueIdx = INT_MAX;
    mat->texture_8 = NULL;
    foundTex = NULL;

    for (i = 0; i < activeTexs->count_0; i++)
    {
        curTex = activeTexs->textures_4[i];

        if (!COMPARE_FILENAMES(&mat->name_0, &curTex->name_8))
        {
            mat->texture_8 = curTex;
            curTex->refCount_14++;
            return curTex;
        }

        queueIdx = curTex->queueIdx_10;
        if ((s32)queueIdx < smallestQueueIdx && curTex->refCount_14 == 0)
        {
            smallestQueueIdx = queueIdx;
            foundTex       = curTex;
        }
    }

    if (foundTex == NULL)
    {
        return NULL;
    }

    Material_TimFileNameGet(&filename, mat);
    fileId = Fs_FindNextFile(&filename, 0, fileIdx);
    if (fileId == NO_VALUE)
    {
        // Failed to find file, log filename to screen.
        debugStr[12] = 0;
        Gfx_DebugStringPosition(100, 80);
        strncpy(&debugStr, &filename, 12);
#ifdef DEBUG
        // Code seen in 98-12-16 build.
        Gfx_DebugStringDraw(debugStr);
#endif
    }

    foundTex->queueIdx_10 = Fs_QueueStartReadTim(fileId, fsBuffer9, &foundTex->imageDesc_0);
    foundTex->refCount_14++;
    foundTex->name_8 = mat->name_0;

    return foundTex;
}

void Texture_RefCountReset(s_Texture* tex) // 0x8005B370
{
    tex->refCount_14 = 0;
}

void func_8005B378(s_Texture* tex, char* arg1) // 0x8005B378
{
    tex->refCount_14 = 1;
    tex->queueIdx_10 = 0;
    StringCopy(tex->name_8.str, arg1);
}

void Texture_Init0(s_Texture* tex) // 0x8005B3A4
{
    tex->name_8.u32[1] = 0;
    tex->name_8.u32[0] = 0;

    tex->refCount_14 = 0;
    tex->queueIdx_10 = NO_VALUE;
}

void Material_TimFileNameGet(char* filename, s_Material* mat) // 0x8005B3BC
{
    char sp10[12];

    // Some inline `memcpy`/`bcopy`/`strncpy`? those use `lwl`/`lwr`/`swl`/`swr` instead though
    // Example: casting `filename`/`arg1` to `u32*` and using `memcpy` does generate `lw`/`sw`,
    // but not in same order as this, guess it's some custom inline/macro instead.
    *(u32*)&sp10[0] = *(u32*)&mat->name_0.str[0];
    *(u32*)&sp10[4] = *(u32*)&mat->name_0.str[4];
    *(u32*)&sp10[8] = 0;

    strcat(sp10, D_80028544); // Copies `TIM` to end of `sp10` string.

    *(u32*)&filename[0] = *(u32*)&sp10[0];
    *(u32*)&filename[4] = *(u32*)&sp10[4];
    *(u32*)&filename[8] = *(u32*)&sp10[8];
}

void func_8005B424(VECTOR3* vec0, VECTOR3* vec1) // 0x8005B424
{
    vec0->vz = 0;
    vec0->vy = 0;
    vec0->vx = 0;

    if (vec1 == NULL)
    {
        return;
    }

    *((s_func_8005B424*)vec0) = *((s_func_8005B424*)vec1);
}

void ActiveTextures_CountReset(s_ActiveTextures* activeTexs) // 0x8005B46C
{
    activeTexs->count_0 = 0;
}

void ActiveTextures_PutTextures(s_ActiveTextures* activeTexs, s_Texture* texs, s32 texIdx) // 0x8005B474
{
    s_Texture*  curTex;
    s_Texture** texEntries;

    texEntries = activeTexs->textures_4;
    for (curTex = &texs[0]; curTex < &texs[texIdx];)
    {
        *texEntries++ = curTex++;
        activeTexs->count_0++;
    }
}

s_Texture* ActiveTextures_FindTexture(char* texName, s_ActiveTextures* activeTexs) // 0x8005B4BC
{
    char       prevTexName[8];
    s32        i;
    s_Texture* curTex;

    StringCopy(prevTexName, texName);

    for (i = 0; i < activeTexs->count_0; i++)
    {
        curTex = activeTexs->textures_4[i];
        if (curTex->queueIdx_10 != NO_VALUE && !COMPARE_FILENAMES(prevTexName, &curTex->name_8))
        {
            return curTex;
        }
    }

    return NULL;
}

void func_8005B55C(GsCOORDINATE2* coord) // 0x8005B55C
{
    s_800AE204* curPtr;

    D_800C42B8 = coord;

    for (curPtr = &D_800AE204[0]; curPtr < &D_800AE204[26]; curPtr++)
    {
        curPtr->field_10 = -Math_Cos(curPtr->field_4);
        curPtr->field_C  = -Math_Sin(curPtr->field_4);
        curPtr->field_E  = 0;
        curPtr->field_18 = FP_MULTIPLY(curPtr->field_2, Math_Cos(curPtr->field_4), Q12_SHIFT);
        curPtr->field_14 = FP_MULTIPLY(curPtr->field_2, Math_Sin(curPtr->field_4), Q12_SHIFT);
        curPtr->field_16 = curPtr->field_0;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005B62C); // 0x8005B62C

void func_8005BF0C(s16 unused, s16 x, s16 y) // 0x8005BF0C
{
    Gfx_DebugStringPosition(x, y);
}

q3_12 func_8005BF38(q3_12 angle) // 0x8005BF38
{
    q3_12 outAngle;
    q3_12 angleNorm;

    angleNorm = FP_ANGLE_NORM_U(angle);

    outAngle = angleNorm;
    if (angleNorm > FP_ANGLE(180.0f))
    {
        outAngle = angleNorm | 0xF000;
    }
    return outAngle;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005BF58); // 0x8005BF58

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005C1CC); // 0x8005C1CC

u32 func_8005C478(s16* arg0, s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2) // 0x8005C478
{
    s32   sp10;
    q3_12 angle0;
    q3_12 angle1;
    q3_12 angle2;
    s32   mag0;
    s32   mag1;
    s32   var0;
    s32   var_s1;
    s32   var_v0_4;
    s32   var1;
    s32   temp;

    angle0 = func_8005BF38(ratan2(x0 - x1, y0 - y1));
    angle1 = func_8005BF38(ratan2(x0 - x2, y0 - y2));
    angle2 = func_8005BF38(ratan2(x2 - x1, y2 - y1));
    mag0   = Math_Vector2MagCalc(x0 - x1, y0 - y1);
    mag1   = Math_Vector2MagCalc(x0 - x2, y0 - y2);

    if ((mag0 * Math_Sin(angle0 - angle2)) < 0)
    {
        sp10 = -FP_MULTIPLY(mag0, Math_Sin(angle0 - angle2), Q12_SHIFT);
    }
    else
    {
        sp10 = FP_MULTIPLY(mag0, Math_Sin(angle0 - angle2), Q12_SHIFT);
    }

    if (mag1 < mag0)
    {
        var0 = mag0;
    }
    else
    {
        var0 = mag1;
    }

    if (!(mag1 < mag0))
    {
        var1 = mag0;
    }
    else
    {
        var1 = mag1;
    }

    var0 = SQUARE(var0 >> 6);
    var1 = SQUARE(var1 >> 6);

    if (var0 < (var1 + (SQUARE((x2 - x1) >> 6) + SQUARE((y2 - y1) >> 6))))
    {
        if (arg0 != NULL)
        {
            if (mag0 * Math_Cos(angle0 - angle2) < 0)
            {
                var_s1 = -FP_MULTIPLY(mag0, Math_Cos(angle0 - angle2), Q12_SHIFT);
            }
            else
            {
                var_s1 = FP_MULTIPLY(mag0, Math_Cos(angle0 - angle2), Q12_SHIFT);
            }

            if ((mag1 * Math_Cos(angle1 - angle2)) < 0)
            {
                var_v0_4 = -FP_MULTIPLY(mag1, Math_Cos(angle1 - angle2), Q12_SHIFT);
            }
            else
            {
                var_v0_4 = FP_MULTIPLY(mag1, Math_Cos(angle1 - angle2), Q12_SHIFT);
            }

            temp  = var_s1 + var_v0_4;
            *arg0 = ((var_s1 << Q12_SHIFT) / temp);
        }

        return ABS(sp10);
    }

    if (mag0 < mag1)
    {
        if (arg0 != NULL)
        {
            *arg0 = 0;
        }

        return ABS(mag0);
    }

    if (arg0 != NULL)
    {
        *arg0 = Q12(1.0f);
    }

    return ABS(mag1);
}

s16 func_8005C7B0(s32 arg0) // 0x8005C7B0
{
    return D_800AE520[arg0 >> 5];
}

s32 func_8005C7D0(s_SubCharacter* chara) // 0x8005C7D0
{
    s32             i;
    s_SubCharacter* npc;
    s_SubCharacter* player;

    i = 0;

    if (chara == &g_SysWork.player_4C.chara_0)
    {
        return NPC_COUNT_MAX;
    }

    npc    = &g_SysWork.npcs_1A0[0];
    player = chara;
    for (i = 0; i < NPC_COUNT_MAX; i++, npc++)
    {
        if (player == npc)
        {
            return i;
        }
    }

    return NO_VALUE;
}

void func_8005C814(s_SubCharacter_D8* arg0, s_SubCharacter* chara) // 0x8005C814
{
    q3_12 sinRotY;
    q3_12 cosRotY;
    q3_12 offsetX0;
    q3_12 offsetX1;
    q3_12 offsetZ0;
    q3_12 offsetZ1;

    offsetX0 = arg0->offsetX_0;
    offsetZ0 = arg0->offsetZ_2;
    offsetX1 = arg0->offsetX_4;
    offsetZ1 = arg0->offsetZ_6;

    cosRotY = Math_Cos(chara->rotation_24.vy);
    sinRotY = Math_Sin(chara->rotation_24.vy);

    chara->field_D8.offsetX_0 = FP_FROM(( offsetX0 * cosRotY) + (offsetZ0 * sinRotY), Q12_SHIFT);
    chara->field_D8.offsetZ_2 = FP_FROM((-offsetX0 * sinRotY) + (offsetZ0 * cosRotY), Q12_SHIFT);
    chara->field_D8.offsetX_4 = FP_FROM(( offsetX1 * cosRotY) + (offsetZ1 * sinRotY), Q12_SHIFT);
    chara->field_D8.offsetZ_6 = FP_FROM((-offsetX1 * sinRotY) + (offsetZ1 * cosRotY), Q12_SHIFT);
}

s32 func_8005C944(s_SubCharacter* chara, s_800C4590* arg1) // 0x8005C944
{
    s_800C4590 sp10;
    VECTOR3    offset;
    q3_12      headingAngle;
    s32        temp_s0;
    s32        temp_s0_2;
    s32        temp_s2;
    s32        temp_s3;
    s32        temp_v0;
    q19_12     sinHeadingAngle;
    s32        ret;

    headingAngle = chara->headingAngle_3C;
    temp_s0 = FP_MULTIPLY_PRECISE(g_DeltaTime0, chara->moveSpeed_38, Q12_SHIFT);
    temp_s2 = OVERFLOW_GUARD(temp_s0);
    temp_s3 = temp_s2 >> 1;

    sinHeadingAngle = Math_Sin(headingAngle);
    temp_s0_2       = temp_s0 >> temp_s3;
    temp_v0         = sinHeadingAngle >> temp_s3;

    offset.vx = (s32)FP_MULTIPLY_PRECISE(temp_s0_2, temp_v0, Q12_SHIFT) << temp_s2;
    offset.vz = (s32)FP_MULTIPLY_PRECISE(temp_s0_2, Math_Cos(headingAngle) >> temp_s3, Q12_SHIFT) << temp_s2;
    offset.vy = (s32)FP_MULTIPLY_PRECISE(g_DeltaTime0, chara->field_34, Q12_SHIFT);

    ret = func_80069B24(&sp10, &offset, chara);

    chara->position_18.vx += sp10.offset_0.vx;
    chara->position_18.vy += sp10.offset_0.vy;
    chara->position_18.vz += sp10.offset_0.vz;

    if (chara->position_18.vy > sp10.field_C)
    {
        chara->position_18.vy = sp10.field_C;
        chara->field_34       = 0;
    }

    if (arg1 != NULL)
    {
        *arg1 = sp10;
    }

    return ret;
}

s32 func_8005CB20(s_SubCharacter* chara, s_800C4590* arg1, s16 x, s16 z) // 0x8005CB20
{
    s_800C4590 sp10;
    VECTOR3    offset;
    q19_12     headingAngle;
    s32        temp_s0;
    s32        temp_s0_2;
    s32        temp_s2;
    s32        temp_s3;
    s32        temp_v0_2;
    s32        temp_v0_4;
    q19_12     sinHeadingAngle;
    s32        ret;

    headingAngle = chara->headingAngle_3C;
    temp_s0 = FP_MULTIPLY_PRECISE(g_DeltaTime0, chara->moveSpeed_38, Q12_SHIFT);
    temp_s2 = OVERFLOW_GUARD(temp_s0);
    temp_s3 = temp_s2 >> 1;

    sinHeadingAngle = Math_Sin(headingAngle);
    temp_s0_2 = temp_s0 >> temp_s3;
    temp_v0_2 = sinHeadingAngle >> temp_s3;
    offset.vx = (s32)FP_MULTIPLY_PRECISE(temp_s0_2, temp_v0_2, Q12_SHIFT) << temp_s2;

    temp_v0_4 = Math_Cos(headingAngle) >> temp_s3;
    offset.vz = (s32)FP_MULTIPLY_PRECISE(temp_s0_2, temp_v0_4, Q12_SHIFT) << temp_s2;

    sinHeadingAngle = chara->field_34;
    offset.vx += x;
    offset.vy = FP_MULTIPLY_PRECISE(g_DeltaTime0, sinHeadingAngle, Q12_SHIFT);
    offset.vz += z;

    ret = func_80069B24(&sp10, &offset, chara);

    chara->position_18.vx += sp10.offset_0.vx;
    chara->position_18.vy += sp10.offset_0.vy;
    chara->position_18.vz += sp10.offset_0.vz;

    if (chara->position_18.vy > sp10.field_C)
    {
        chara->position_18.vy = sp10.field_C;
        chara->field_34       = 0;
    }

    if (arg1 != NULL)
    {
        *arg1 = sp10;
    }

    return ret;
}

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_80055028", D_80028544);

// Important for combat.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005CD38); // 0x8005CD38

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005D50C); // 0x8005D50C

s32 func_8005D86C(s32 arg0) // 0x8005D86C
{
    s32 var_a0;
    s32 var_v1;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp;

    temp    = Q12_FRACT(arg0);
    temp_a1 = FP_FROM(arg0, Q12_SHIFT);

    if (temp_a1 >= 12)
    {
        return 0;
    }
    if (temp_a1 < -20)
    {
        return INT_MAX;
    }

    temp_a2 = (arg0 & 0x7F) << 5;
    temp_a3 = temp >> 7;

    var_a0 = D_800AE564[temp_a3];
    if (temp_a1 > 0)
    {
        var_a0 >>= temp_a1;
    }
    else if (temp_a1 < 0)
    {
        var_a0 <<= -temp_a1;
    }

    if (temp_a2 != 0)
    {
        var_v1 = D_800AE564[temp_a3 + 1];
        if (temp_a1 > 0)
        {
            var_v1 >>= temp_a1;
        }
        else if (temp_a1 < 0)
        {
            var_v1 <<= -temp_a1;
        }

        var_a0 = FP_MULTIPLY_PRECISE(var_a0, Q12(1.0f) - temp_a2, Q12_SHIFT) + FP_MULTIPLY_PRECISE(var_v1, temp_a2, Q12_SHIFT);
    }

    return var_a0;
}

s32 func_8005D974(s32 arg0) // 0x8005D974
{
    s32 val;

    val = func_8005D86C(arg0);

    if (val > Q12(4.0f))
    {
        val = Q12(4.0f);
    }
    else if (val < Q12(0.0f))
    {
        val = Q12(0.0f);
    }

    return val;
}

s32 func_8005D9B8(VECTOR3* pos, q23_8 vol) // 0x8005D9B8
{
    s32 temp_v0;
    s32 deltaX;
    s32 deltaY;
    s32 deltaZ;
    s32 var_s0;
    s32 var_v0;

    vwGetViewPosition(&D_800C42C0);
    D_800C42CC = &g_SysWork.player_4C.chara_0.position_18;

    deltaX = D_800C42C0.vx - D_800C42CC->vx;
    deltaY = D_800C42C0.vy - D_800C42CC->vy;
    deltaZ = D_800C42C0.vz - D_800C42CC->vz;
    var_s0 = func_8005D974((SquareRoot12(FP_MULTIPLY_PRECISE(deltaX, deltaX, Q12_SHIFT) +
                                         FP_MULTIPLY_PRECISE(deltaY, deltaY, Q12_SHIFT) +
                                         FP_MULTIPLY_PRECISE(deltaZ, deltaZ, Q12_SHIFT)) - Q12(2.5f)) / 10);
    if (var_s0 > Q12(1.0f))
    {
        var_s0 = Q12(1.0f);
    }

    deltaX  = D_800C42CC->vx - pos->vx;
    deltaY  = D_800C42CC->vy - pos->vy;
    deltaZ  = D_800C42CC->vz - pos->vz;
    temp_v0 = func_8005D974((SquareRoot12(FP_MULTIPLY_PRECISE(deltaX, deltaX, Q12_SHIFT) +
                                          FP_MULTIPLY_PRECISE(deltaY, deltaY, Q12_SHIFT) +
                                          FP_MULTIPLY_PRECISE(deltaZ, deltaZ, Q12_SHIFT)) - Q12(6.0f)) / 4);

    var_v0 = FP_MULTIPLY_PRECISE(var_s0, temp_v0, Q12_SHIFT);
    if (var_v0 > Q12(2.0f))
    {
        var_v0 = Q12(2.0f);
    }
    else if (var_v0 < Q12(0.0f))
    {
        var_v0 = Q12(0.0f);
    }

    var_v0 = FP_MULTIPLY_PRECISE(vol, var_v0, Q12_SHIFT);
    if (var_v0 > Q8_CLAMPED(1.0f))
    {
        var_v0 = Q8_CLAMPED(1.0f);
    }
    else if (var_v0 < Q12(0.0f))
    {
        var_v0 = Q12(0.0f);
    }

    return var_v0;
}

void func_8005DC1C(s32 sfx, const VECTOR3* pos, q23_8 vol, s32 soundType)
{
    func_8005DC3C(sfx, pos, vol, soundType, 0);
}

void func_8005DC3C(s32 sfx, const VECTOR3* pos, q23_8 vol, s32 soundType, s32 pitch) // 0x8005DC3C
{
    q23_8 volCpy;
    s32   balance;

    // Get stereo balance.
    if (soundType & (1 << 0) || g_GameWork.config_0.optSoundType_1E)
    {
        balance = 0;
    }
    else
    {
        balance = Sound_StereoBalanceGet(pos);
    }

    // Clamp volume.
    if (vol > Q8_CLAMPED(1.0f))
    {
        vol = Q8_CLAMPED(1.0f);
    }
    else if (vol < Q8_CLAMPED(0.0f))
    {
        vol = Q8_CLAMPED(0.0f);
    }

    if (!(soundType & (1 << 1)))
    {
        volCpy = func_8005D9B8(pos, vol);
    }
    else
    {
        volCpy = vol;
    }

    if (volCpy > Q8_CLAMPED(1.0f))
    {
        volCpy = Q8_CLAMPED(1.0f);
    }

    if (soundType & (1 << 2))
    {
        func_800463C0(sfx, balance, ~volCpy, pitch);
    }
    else
    {
        Sd_PlaySfx(sfx, balance, ~volCpy);
    }
}

void func_8005DD44(s32 sfx, VECTOR3* pos, q23_8 vol, s8 pitch) // 0x8005DD44
{
    q23_8 volCpy;
    s32   balance;

    // Get stereo balance.
    if (g_GameWork.config_0.optSoundType_1E)
    {
        balance = 0;
    }
    else
    {
        balance = Sound_StereoBalanceGet(pos);
    }

    // Clamp volume.
    if (vol > Q8_CLAMPED(1.0f))
    {
        vol = Q8_CLAMPED(1.0f);
    }
    else if (vol < Q8_CLAMPED(0.0f))
    {
        vol = Q8_CLAMPED(0.0f);
    }

    volCpy = func_8005D9B8(pos, vol);
    if (volCpy > Q8_CLAMPED(1.0f))
    {
        volCpy = Q8_CLAMPED(1.0f);
    }

    func_80046620(sfx, balance, ~volCpy, pitch);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005DE0C); // 0x8005DE0C

void Map_EffectTexturesLoad(s32 mapIdx) // 0x8005E0DC
{
    s32 i;
    s32 effectTexFlags;

    D_800A908C.v     = 0;
    D_800A908C.clutY = 0;
    D_800A9094.v     = 128;

    // Get effect texture flags.
    effectTexFlags = EffectTextureFlag_None;
    switch (mapIdx)
    {
        case NO_VALUE:
            Fs_QueueStartReadTim(FILE_TIM_BLD_TIM, (s32)FONT24_BUFFER - ALIGN(Fs_GetFileSize(FILE_TIM_BLD_TIM), 0x800), &D_800A9084);
            g_LoadedEffectTextureFlags = EffectTextureFlag_None;
            break;

        case MapOverlayId_MAP0_S01:
            if (!Savegame_EventFlagGet(EventFlag_47))
            {
                effectTexFlags = EffectTextureFlag_Glass;
            }
            break;

        case MapOverlayId_MAP1_S02:
        case MapOverlayId_MAP1_S03:
            effectTexFlags = EffectTextureFlag_Water;
            break;

        case MapOverlayId_MAP1_S05:
            effectTexFlags = EffectTextureFlag_Fire | EffectTextureFlag_Ef;
            break;

        case MapOverlayId_MAP3_S05:
            if (!Savegame_EventFlagGet(EventFlag_284))
            {
                effectTexFlags = EffectTextureFlag_Fire;
            }
            break;

        case MapOverlayId_MAP4_S01:
            if (!Savegame_EventFlagGet(EventFlag_306))
            {
                effectTexFlags = EffectTextureFlag_Fire;
            }
            break;

        case MapOverlayId_MAP4_S05:
            effectTexFlags = EffectTextureFlag_Blood;
            break;

        case MapOverlayId_MAP5_S00:
        case MapOverlayId_MAP6_S03:
        case MapOverlayId_MAPX_S00: // @unused
            effectTexFlags = EffectTextureFlag_WaterRefract;
            break;
    }

    if (effectTexFlags == EffectTextureFlag_None)
    {
        return;
    }

    // Run through effect texture flags.
    g_LoadedEffectTextureFlags = EffectTextureFlag_None;
    for (i = 0; i < 16; i++)
    {
        if (!((effectTexFlags >> i) & (1 << 0)))
        {
            continue;
        }

        // Set global flag.
        g_LoadedEffectTextureFlags |= 1 << i;

        // TODO: Not sure if this is actually checking something gte related, but the macro/pointless branch is needed for match.
        if (gte_IsDisabled())
        {
            continue;
        }

        // Load effect textures.
        switch (1 << i)
        {
            case EffectTextureFlag_Glass:
                Fs_QueueStartReadTim(FILE_TIM_GLASS_TIM, (s32)FONT24_BUFFER - ALIGN(Fs_GetFileSize(FILE_TIM_GLASS_TIM), 0x800), &D_800A908C);
                break;

            case EffectTextureFlag_WaterRefract:
                Fs_QueueStartReadTim(FILE_TIM_DR_WAVE_TIM, (s32)FONT24_BUFFER - ALIGN(Fs_GetFileSize(FILE_TIM_DR_WAVE_TIM), 0x800), &D_800A908C);
                break;

            case EffectTextureFlag_Water:
                Fs_QueueStartReadTim(FILE_TIM_WATER_TIM, (s32)FONT24_BUFFER - ALIGN(Fs_GetFileSize(FILE_TIM_WATER_TIM), 0x800), &D_800A908C);
                break;

            case EffectTextureFlag_Fire:
                D_800A9094.v = 120;
                Fs_QueueStartReadTim(FILE_TIM_FIRE_TIM, (s32)FONT24_BUFFER - ALIGN(Fs_GetFileSize(FILE_TIM_FIRE_TIM), 0x800), &D_800A9094);
                break;

            case EffectTextureFlag_Ef:
                D_800A908C.v     = 64;
                D_800A908C.clutY = 4;
                Fs_QueueStartReadTim(FILE_TIM_EF_TIM, (s32)FONT24_BUFFER - ALIGN(Fs_GetFileSize(FILE_TIM_EF_TIM), 0x800), &D_800A908C);
                break;

            case EffectTextureFlag_Blood:
                Fs_QueueStartReadTim(FILE_TIM_BLOOD_TIM, (s32)FONT24_BUFFER - ALIGN(Fs_GetFileSize(FILE_TIM_BLOOD_TIM), 0x800), &D_800A908C);
                break;

            case EffectTextureFlag_WarmTest: // @unused See `e_EffectTextureFlags`.
                Fs_QueueStartReadTim(FILE_TEST_WARMTEST_TIM, (s32)FONT24_BUFFER - ALIGN(Fs_GetFileSize(FILE_TEST_WARMTEST_TIM), 0x800), &D_800A9094);
                break;
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005E414); // 0x8005E414

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005E650); // 0x8005E650

void func_8005E70C(void) // 0x8005E70C
{
    s32 i;
    s16 count;
    u8  temp_v0;

    count = g_MapOverlayHeader.unkTable1Count_50;
    for (i = 0; i < count; i++)
    {
        temp_v0 = g_MapOverlayHeader.unkTable1_4C[i].field_A;
        switch (temp_v0)
        {
            case 1:
            case 2:
            case 3:
            case 15:
            case 16:
            case 17:
            case 20:
            case 21:
            case 22:
                g_MapOverlayHeader.unkTable1_4C[i].field_A = 0;
                break;
        }
    }

    count = g_MapOverlayHeader.bloodSplatCount_58;
    for (i = 0; i < count; i++)
    {
        g_MapOverlayHeader.bloodSplats_54[i].unk_0 = NO_VALUE;
    }

    D_800C4414 = 0;
}

s32 func_8005E7E0(s32 arg0) // 0x8005E7E0
{
    s32 idx;
    s32 i;

    idx = D_800C4408;
    i = 0;
    while (i < g_MapOverlayHeader.unkTable1Count_50)
    {
        if (idx >= g_MapOverlayHeader.unkTable1Count_50)
        {
            idx = 0;
        }

        if (g_MapOverlayHeader.unkTable1_4C[idx].field_A != 0)
        {
            i++;
            idx++;
        }
        else
        {
            break;
        }
    }

    if (i == g_MapOverlayHeader.unkTable1Count_50)
    {
        return NO_VALUE;
    }

    g_MapOverlayHeader.unkTable1_4C[idx].field_A = arg0;

    D_800C4408 = idx + 1;
    return idx;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005E89C); // 0x8005E89C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005F55C); // 0x8005F55C

bool func_8005F680(s_Collision* coll) // 0x8005F680
{
    bool cond;
    s8   temp_v1;

    temp_v1 = coll->field_8;

    cond = false;
    if (temp_v1 == 0 || temp_v1 == 12 || temp_v1 == 7)
    {
        cond = true;
    }
    return cond;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005F6B0); // 0x8005F6B0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80060044); // 0x80060044

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_800611C0); // 0x800611C0

void func_800622B8(s32 arg0, s_SubCharacter* chara, s32 animStatus, s32 arg3) // 0x800622B8
{
    s_Collision coll;
    s32         temp_s0;
    s32         temp_s2;
    s32         temp_s3;
    s32         idx;
    s32         i;

    if (g_GameWork.config_0.optExtraBloodColor_24 == 14)
    {
        return;
    }

    arg3 = func_8005F55C(arg3);

    i = D_800AE5CC[animStatus + 1] - D_800AE5CC[animStatus];
    while (i > 0)
    {
        idx = func_8005E7E0(3);
        if (idx == NO_VALUE)
        {
            break;
        }

        temp_s0 = (D_800AE5CC[animStatus] + i) - 1;

        temp_s3 = Rng_Rand16() % D_800AE5F0[temp_s0 * 4]       + D_800AE5F0[(temp_s0 * 4) + 1];
        temp_s2 = Rng_Rand16() % D_800AE5F0[(temp_s0 * 4) + 2] + D_800AE5F0[(temp_s0 * 4) + 3];

        g_MapOverlayHeader.unkTable1_4C[idx].vx_0 = chara->position_18.vx +
                                                    FP_MULTIPLY(temp_s3, Math_Sin(chara->rotation_24.vy), Q12_SHIFT) -
                                                    FP_MULTIPLY(temp_s2, Math_Cos(chara->rotation_24.vy), Q12_SHIFT);
        g_MapOverlayHeader.unkTable1_4C[idx].vy_8 = chara->position_18.vy;
        g_MapOverlayHeader.unkTable1_4C[idx].vz_4 = chara->position_18.vz +
                                                    FP_MULTIPLY(temp_s3, Math_Cos(chara->rotation_24.vy), Q12_SHIFT) +
                                                    FP_MULTIPLY(temp_s2, Math_Sin(chara->rotation_24.vy), Q12_SHIFT);

        Collision_Get(&coll, g_MapOverlayHeader.unkTable1_4C[idx].vx_0, g_MapOverlayHeader.unkTable1_4C[idx].vz_4);

        if (ABS_DIFF(coll.groundHeight_0, chara->position_18.vy) > Q12(0.15f))
        {
            g_MapOverlayHeader.unkTable1_4C[(idx)].field_A = 0;
        }
        else
        {
            g_MapOverlayHeader.unkTable1_4C[idx].field_E  = D_800AE700[animStatus] + (Rng_Rand16() % (D_800AE700[animStatus] >> 2));
            g_MapOverlayHeader.unkTable1_4C[idx].field_D  = arg3;
            g_MapOverlayHeader.unkTable1_4C[idx].field_B  = (Rng_Rand16() & 3) + 4; // TODO: `Rng_GenerateInt` doesn't match?
            g_MapOverlayHeader.unkTable1_4C[idx].field_C  = func_8005C7D0(chara);
            g_MapOverlayHeader.unkTable1_4C[idx].field_10 = Rng_Rand16() & 0x1FFF;
        }

        i--;
    }
}

void func_800625F4(VECTOR3* arg0, s16 arg1, s32 arg2, s32 arg3) // 0x800625F4
{
    s32 idx;
    s8  var;

    var = func_8005F55C(arg2);

    idx = func_8005E7E0(4);
    if (idx == NO_VALUE)
    {
        return;
    }

    g_MapOverlayHeader.unkTable1_4C[idx].vx_0     = arg0->vx;
    g_MapOverlayHeader.unkTable1_4C[idx].vy_8     = arg0->vy;
    g_MapOverlayHeader.unkTable1_4C[idx].vz_4     = arg0->vz;
    g_MapOverlayHeader.unkTable1_4C[idx].field_E  = arg1;
    g_MapOverlayHeader.unkTable1_4C[idx].field_D  = var;
    g_MapOverlayHeader.unkTable1_4C[idx].field_B  = Rng_TestProbabilityBits(2);
    g_MapOverlayHeader.unkTable1_4C[idx].field_C  = 6;
    g_MapOverlayHeader.unkTable1_4C[idx].field_10 = arg3 * Q12(5.0f);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80062708); // 0x80062708

// Displays gun shooting effects.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006342C); // 0x8006342C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80063A50); // 0x80063A50

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80064334); // 0x80064334

void func_80064F04(VECTOR3* arg0, s8 arg1, s16 arg2) // 0x80064F04
{
    s32 idx;

    idx = func_8005E7E0(31);
    if (idx != NO_VALUE)
    {
        g_MapOverlayHeader.unkTable1_4C[idx].vx_0    = Q12_TO_Q8(arg0->vx);
        g_MapOverlayHeader.unkTable1_4C[idx].vy_8    = Q12_TO_Q8(arg0->vy);
        g_MapOverlayHeader.unkTable1_4C[idx].vz_4    = Q12_TO_Q8(arg0->vz);
        g_MapOverlayHeader.unkTable1_4C[idx].field_C = arg1;
        g_MapOverlayHeader.unkTable1_4C[idx].field_E = arg2;
    }
}

bool func_80064FC0(POLY_FT4** polys, s32 arg1) // 0x80064FC0
{
    s_func_80064FC0* ptr;
    s16              temp;

    ptr = PSX_SCRATCH;

    g_MapOverlayHeader.unkTable1_4C[arg1].field_A = 0;
    temp                                          = g_MapOverlayHeader.unkTable1_4C[arg1].vx_0 - ptr->field_0.vx;
    *(s32*)&ptr->field_12C.vx                     = (temp & 0xFFFF) + ((g_MapOverlayHeader.unkTable1_4C[arg1].vy_8 - ptr->field_0.vy) << 16);
    ptr->field_12C.vz                             = g_MapOverlayHeader.unkTable1_4C[arg1].vz_4 - ptr->field_0.vz;

    gte_ldv0(&ptr->field_12C);
    gte_rtps();
    gte_stsxy(&ptr->field_13C);
    gte_stsz(&ptr->field_140);

    if (ABS(ptr->field_13C.vx) >= 201 || ABS(ptr->field_13C.vy) >= 161)
    {
        return false;
    }

    ptr->field_144 = ((g_MapOverlayHeader.unkTable1_4C[arg1].field_E * ptr->field_2C) / ptr->field_140) >> 4;
    setPolyFT4(*polys);
    setXY0Fast(*polys, (u16)ptr->field_13C.vx - (u16)ptr->field_144, ptr->field_13C.vy + ptr->field_144);
    setXY1Fast(*polys, (u16)ptr->field_13C.vx + (u16)ptr->field_144, ptr->field_13C.vy + ptr->field_144);
    setXY2Fast(*polys, (u16)ptr->field_13C.vx - (u16)ptr->field_144, ptr->field_13C.vy - ptr->field_144);
    setXY3Fast(*polys, (u16)ptr->field_13C.vx + (u16)ptr->field_144, ptr->field_13C.vy - ptr->field_144);
    *(u16*)&(*polys)->r0 = 0x1020;
    (*polys)->b0         = 0x10;

    setSemiTrans((*polys), 1);

    *(u32*)&(*polys)->u0 = 0x018C0000;
    *(u32*)&(*polys)->u1 = 0x2C003F;
    *(u16*)&(*polys)->u2 = 0x3F00;
    *(u16*)&(*polys)->u3 = 0x3F3F;

    addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[(ptr->field_140 - 0x20) >> 3], (*polys));

    *polys += 1;
    return true;
}

void func_800652F4(VECTOR3* arg0, s16 arg1, s16 arg2, s16 arg3) // 0x800652F4
{
    DVECTOR          sp10[32][3];
    s32              sp190[32][3];
    s32              i;
    s32              temp_a1;
    s32              temp_t0;
    s32              temp_t1;
    s32              temp_v1;
    s32              temp_v1_3;
    s32              j;
    s32              var_s1;
    s32              var_v0_3;
    s32              temp;
    s_func_800652F4* ptr;

    ptr = PSX_SCRATCH;

    temp_t1          = FP_FROM(g_SysWork.player_4C.chara_0.position_18.vx, Q12_SHIFT);
    temp_t0          = FP_FROM(g_SysWork.player_4C.chara_0.position_18.vy, Q12_SHIFT);
    temp_v1          = FP_FROM(g_SysWork.player_4C.chara_0.position_18.vz, Q12_SHIFT);
    ptr->field_40.vx = temp_t1 << 8;
    ptr->field_40.vy = temp_t0 << 8;
    ptr->field_40.vz = temp_v1 << 8;

    func_80049C2C(&ptr->field_20, FP_TO(temp_t1, Q12_SHIFT), FP_TO(temp_t0, Q12_SHIFT), FP_TO(temp_v1, Q12_SHIFT));

    gte_SetRotMatrix(&ptr->field_20);
    gte_SetTransMatrix(&ptr->field_20);
    gte_ReadGeomScreen(&ptr->field_4C);

    for (i = 0; i < 3; i++)
    {
        var_s1           = ((arg2 >> 4) + 0x80) * i;
        temp             = 0x1000;
        ptr->field_54[i] = -FP_MULTIPLY_PRECISE(CLAMP_LOW((temp - FP_MULTIPLY(var_s1, Math_Sin(arg2 >> 2), Q12_SHIFT)) - Math_Cos(arg2 >> 2), 0),
                                                0x2800,
                                                Q12_SHIFT);
        temp             = 0x80;
        ptr->field_60[i] = FP_MULTIPLY_PRECISE(CLAMP_LOW(arg2 - (FP_MULTIPLY(var_s1, Math_Cos(arg2 >> 2), Q12_SHIFT) - temp), 0),
                                               0x2800,
                                               Q12_SHIFT);
    }

    ptr->field_50 = -0x40;

    for (i = 0; i < 32; i++)
    {
        for (j = 0; j < 3; j++)
        {
            *(s32*)&ptr->field_8[j] = ((((arg0->vx + FP_FROM(FP_MULTIPLY(ptr->field_60[j], Math_Sin(ptr->field_50), Q12_SHIFT) * Math_Cos(arg1) -
                                        ptr->field_54[j] * Math_Sin(arg1), Q12_SHIFT)) >> 4) - (u16)ptr->field_40.vx) & 0xFFFF) +
                                      ((((arg0->vy + FP_MULTIPLY(ptr->field_60[j], Math_Cos(ptr->field_50), Q12_SHIFT)) >> 4) - ptr->field_40.vy) << 16);

            (&ptr->field_8[j])->vz = ((arg0->vz + (((FP_MULTIPLY(ptr->field_60[j], Math_Sin(ptr->field_50), Q12_SHIFT) * Math_Sin(arg1)) +
                                    (ptr->field_54[j] * Math_Cos(arg1))) >> Q12_SHIFT)) >> 4) - ptr->field_40.vz;
        }

        gte_ldv3c(&ptr->field_8);
        gte_rtpt();
        gte_stsxy3c(&sp10[i]);
        gte_stsz3c(&sp190[i]);

        ptr->field_50 += 0x80;
    }

    ptr->field_0 = (POLY_G4*)GsOUT_PACKET_P;

    for (i = 0; i < 32; i++)
    {
        temp_v1_3 = i + 1;
        var_v0_3  = temp_v1_3;
        if (temp_v1_3 < 0)
        {
            var_v0_3 = i + 32;
        }

        temp_a1 = var_v0_3 >> 5;
        temp_a1 = temp_v1_3 - (temp_a1 << 5);

        for (j = 0; j < 2; j++)
        {
            setPolyG4(ptr->field_0);

            setXY0Fast(ptr->field_0, sp10[i][j].vx, sp10[i][j].vy);
            setXY1Fast(ptr->field_0, sp10[temp_a1][j].vx, sp10[temp_a1][j].vy);
            setXY2Fast(ptr->field_0, sp10[i][j + 1].vx, sp10[i][j + 1].vy);
            setXY3Fast(ptr->field_0, sp10[temp_a1][j + 1].vx, sp10[temp_a1][j + 1].vy);

            ptr->field_68 = (sp190[i][j] + sp190[temp_a1][j] + sp190[i][j + 1] + sp190[temp_a1][j + 1]) >> 2;
            setSemiTrans(ptr->field_0, 1);

            ptr->field_0->r0 = ptr->field_0->r1 = CLAMP_LOW(D_800AE710[j].field_0 - (arg3 >> 4) - (arg2 >> 5), 0);
            ptr->field_0->g0 = ptr->field_0->g1 = CLAMP_LOW(D_800AE710[j].field_1 - (arg3 >> 4) - (arg2 >> 5), 0);
            ptr->field_0->b0 = ptr->field_0->b1 = CLAMP_LOW(D_800AE710[j].field_2 - (arg3 >> 4) - (arg2 >> 5), 0);

            ptr->field_0->r2 = ptr->field_0->r3 = CLAMP_LOW(D_800AE710[j + 1].field_0 - (arg3 >> 4) - (arg2 >> 5), 0);
            ptr->field_0->g2 = ptr->field_0->g3 = CLAMP_LOW(D_800AE710[j + 1].field_1 - (arg3 >> 4) - (arg2 >> 5), 0);
            ptr->field_0->b2 = ptr->field_0->b3 = CLAMP_LOW(D_800AE710[j + 1].field_2 - (arg3 >> 4) - (arg2 >> 5), 0);

            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ptr->field_68 >> 3], ptr->field_0);

            ptr->field_0++;
            ptr->field_4 = (DR_TPAGE*)ptr->field_0;
            setDrawTPage(ptr->field_4, 0, 1, 0x20);
            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ptr->field_68 >> 3], ptr->field_4);
            ptr->field_4++;
            ptr->field_0 = (POLY_G4*)ptr->field_4;
        }
    }

    GsOUT_PACKET_P = (PACKET*)ptr->field_0;
}

void func_80065B94(VECTOR3* arg0, s16 arg1) // 0x80065B94
{
    s16              temp_s0;
    s32              x;
    s32              y;
    s32              z;
    s16              temp_fp;
    s32              i;
    s16              temp;
    s32              temp2;
    POLY_FT4*        next;
    s_func_80065B94* ptr;

    ptr = PSX_SCRATCH;

    x                = FP_FROM(g_SysWork.player_4C.chara_0.position_18.vx, Q12_SHIFT);
    y                = FP_FROM(g_SysWork.player_4C.chara_0.position_18.vy, Q12_SHIFT);
    z                = FP_FROM(g_SysWork.player_4C.chara_0.position_18.vz, Q12_SHIFT);
    ptr->field_2C.vx = Q8(x);
    ptr->field_2C.vy = Q8(y);
    ptr->field_2C.vz = Q8(z);

    func_80049C2C(&ptr->field_C, Q12(x), Q12(y), Q12(z));

    gte_SetRotMatrix(&ptr->field_C);
    gte_SetTransMatrix(&ptr->field_C);
    gte_ReadGeomScreen(&ptr->field_38);

    temp                 = Q12_TO_Q8(arg0->vx) - ptr->field_2C.vx;
    *(s32*)&ptr->field_4 = (temp & 0xFFFF) + ((Q12_TO_Q8(arg0->vy) - ptr->field_2C.vy) << 16);
    ptr->field_4.vz      = Q12_TO_Q8(arg0->vz) - ptr->field_2C.vz;

    gte_ldv0(&ptr->field_4);
    gte_rtps();
    gte_stsxy(&ptr->field_3C);
    gte_stsz(&ptr->field_40);

    if (ptr->field_40 < ptr->field_38 && (ptr->field_40 >> 3) >= 0x800)
    {
        return;
    }

    ptr->field_0 = (POLY_FT4*)GsOUT_PACKET_P;
    setPolyFT4(ptr->field_0);
    *(s32*)&ptr->field_0->u0 = 0x014C4020;
    *(s32*)&ptr->field_0->u1 = 0x2C403F;
    *(u16*)&ptr->field_0->u2 = 0x5F20;
    *(u16*)&ptr->field_0->u3 = 0x5F3F;
    setSemiTrans(ptr->field_0, 1);

    temp_fp = ptr->field_38 * (s32)FP_MULTIPLY_PRECISE((arg1 >> 1) + 0x800, 0x100, Q12_SHIFT) / ptr->field_40;

    for (i = 0; i < 8; i++)
    {
        temp2 = arg1;
        if (arg1 == 0)
        {
            D_800C4428[i] = (i << 9) + Rng_GenerateInt(Rng_Rand16(), 0, 255) - 128;
            D_800C4438[i] = (Math_Cos(Rng_Rand16() & 0x7FF) >> 1) + 0x1000;
        }

        temp_s0 = FP_MULTIPLY_PRECISE(temp_fp, D_800C4438[i], Q12_SHIFT);

        ptr->field_44.vx = FP_MULTIPLY(temp_s0, Math_Sin(D_800C4428[i]), Q12_SHIFT);
        ptr->field_44.vy = FP_MULTIPLY(temp_s0, Math_Sin(D_800C4428[i] + FP_ANGLE(90.0f)), Q12_SHIFT);

        ptr->field_48.vx = FP_MULTIPLY(-temp_s0, Math_Cos(D_800C4428[i]), Q12_SHIFT);
        ptr->field_48.vy = FP_MULTIPLY(-temp_s0, Math_Cos(D_800C4428[i] + FP_ANGLE(90.0f)), Q12_SHIFT);

        setXY0Fast(ptr->field_0, (u16)ptr->field_3C.vx, ptr->field_3C.vy);
        setXY1Fast(ptr->field_0, (u16)ptr->field_3C.vx + (u16)ptr->field_44.vx, ptr->field_3C.vy + ptr->field_48.vx);
        setXY2Fast(ptr->field_0, (u16)ptr->field_3C.vx + (u16)ptr->field_44.vy, ptr->field_3C.vy + ptr->field_48.vy);
        setXY3Fast(ptr->field_0, (u16)ptr->field_44.vy + ((u16)ptr->field_3C.vx + (u16)ptr->field_44.vx), ptr->field_3C.vy + ptr->field_48.vx + ptr->field_48.vy);

        *(u16*)&ptr->field_0->r0 = ((128 - (temp2 >> 5)) << 8) - (((temp2 * 5) >> 7) - 160);
        ptr->field_0->b0         = 96 - ((temp2 * 3) >> 7);

        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ptr->field_40 >> 3], ptr->field_0);

        next  = ptr->field_0 + 1;
        *next = *ptr->field_0;

        ptr->field_0++;
    }

    GsOUT_PACKET_P = (PACKET*)ptr->field_0;
}

void func_80066184() // 0x80066184
{
    s32              i;
    s_func_80066184* ptr;
    POLY_GT4*        poly;

    if (g_Controller0->btnsClicked_10 & ControllerFlag_R3)
    {
        D_800AE73C = 0x2000;
    }

    if (g_Controller0->btnsHeld_C & ControllerFlag_Cross)
    {
        D_800AE73C = ((D_800AE73C - g_DeltaTime0) < 0) ? 0 : (D_800AE73C - g_DeltaTime0);
    }

    ptr = PSX_SCRATCH;

    ptr->field_3C.vx = Q12(FP_FROM(g_SysWork.player_4C.chara_0.position_18.vx, Q12_SHIFT));
    ptr->field_3C.vy = Q12(FP_FROM(g_SysWork.player_4C.chara_0.position_18.vy, Q12_SHIFT));
    ptr->field_3C.vz = Q12(FP_FROM(g_SysWork.player_4C.chara_0.position_18.vz, Q12_SHIFT));

    func_80049C2C(&ptr->field_4, ptr->field_3C.vx, ptr->field_3C.vy, ptr->field_3C.vz);

    gte_SetRotMatrix(&ptr->field_4);
    gte_SetTransMatrix(&ptr->field_4);
    gte_ReadGeomScreen(&ptr->field_48);

    for (i = 0; i < 4; i++)
    {
        *(s32*)&ptr->field_24[i].vx = (Q12_TO_Q8((D_800AE71C[i][0] - ptr->field_3C.vx)) & 0xFFFF) + (Q12_TO_Q8((-81 - ptr->field_3C.vy)) << 16);
        ptr->field_24[i].vz         = Q12_TO_Q8(D_800AE71C[i][1] - ptr->field_3C.vz);
    }

    gte_ldv3c(&ptr->field_24);
    gte_rtpt();
    gte_stsxy3c(&ptr->field_4C);
    gte_stsz3c(&ptr->field_5C);
    gte_ldv0(&ptr->field_3C);
    gte_rtps();
    gte_stsxy(&ptr->field_58);
    gte_stsz(&ptr->field_68);

    ptr->field_0 = (POLY_GT4*)GsOUT_PACKET_P;

    setPolyGT4(ptr->field_0);

    setXY0Fast(ptr->field_0, (u16)ptr->field_4C.vx, ptr->field_4C.vy);
    setXY1Fast(ptr->field_0, (u16)ptr->field_50.vx, ptr->field_50.vy);
    setXY2Fast(ptr->field_0, (u16)ptr->field_54.vx, ptr->field_54.vy);
    setXY3Fast(ptr->field_0, (u16)ptr->field_58.vx, ptr->field_58.vy);

    ptr->field_6C = MIN(FP_MULTIPLY(CLAMP_MIN_THEN_LOW(D_800AE73C, Q12(0.0f), Q12(1.0f)),
                                    func_80055D78(Q12(22.7f), Q12(0.0f), Q12(-22.1f)), Q12_SHIFT),
                        0xFF);

    ptr->field_70 = MIN(FP_MULTIPLY(CLAMP_MIN_THEN_LOW(D_800AE73C - Q12(0.75f), Q12(0.0f), Q12(1.0f)),
                                    func_80055D78(Q12(22.7f), Q12(0.0f), Q12(-22.1f)), Q12_SHIFT),
                        0xFF);

    ptr->field_74 = MIN(FP_MULTIPLY(CLAMP_MIN_THEN_LOW(D_800AE73C, Q12(0.0f), Q12(1.0f)),
                                    func_80055D78(Q12(22.7f), Q12(0.0f), Q12(-22.1f)), Q12_SHIFT),
                        0xFF);

    ptr->field_78 = MIN(FP_MULTIPLY(CLAMP_MIN_THEN_LOW(D_800AE73C - Q12(0.75f), Q12(0.0f), Q12(1.0f)),
                                    func_80055D78(Q12(22.7f), Q12(0.0f), Q12(-22.1f)), Q12_SHIFT),
                        0xFF);

    *(u16*)&ptr->field_0->r0 = ptr->field_6C + (ptr->field_6C << 8);
    ptr->field_0->b0         = ptr->field_6C;
    *(u16*)&ptr->field_0->r1 = ptr->field_70 + (ptr->field_70 << 8);
    ptr->field_0->b1         = ptr->field_70;
    *(u16*)&ptr->field_0->r2 = ptr->field_74 + (ptr->field_74 << 8);
    ptr->field_0->b2         = ptr->field_74;
    *(u16*)&ptr->field_0->r3 = ptr->field_78 + (ptr->field_78 << 8);
    ptr->field_0->b3         = ptr->field_78;

    setSemiTrans(ptr->field_0, 1);

    poly  = ptr->field_0 + 1;
    *poly = *ptr->field_0;

    *(u32*)&ptr->field_0->u0 = 0xE0000;
    *(u32*)&ptr->field_0->u1 = 0x2D003F;
    *(u16*)&ptr->field_0->u2 = 0x3F00;
    *(u16*)&ptr->field_0->u3 = 0x3F3F;

    addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[(ptr->field_5C + ptr->field_60 + ptr->field_64 + ptr->field_68) >> 5], ptr->field_0);

    ptr->field_0++;

    *(u32*)&ptr->field_0->u0 = 0xE0000;
    *(u32*)&ptr->field_0->u1 = 0x4D003F;
    *(u16*)&ptr->field_0->u2 = 0x3F00;
    *(u16*)&ptr->field_0->u3 = 0x3F3F;

    ptr->field_6C = MIN(FP_MULTIPLY(CLAMP_LOW_THEN_MIN(D_800AE73C - 0x1000, 0, 0x1000),
                                    func_80055D78(0x16B33, 0, -0x16199), Q12_SHIFT - 1),
                        0xFF);

    ptr->field_70 = MIN(FP_MULTIPLY(CLAMP_LOW_THEN_MIN(D_800AE73C - 0x1000, 0, 0x1000),
                                    func_80055D78(0x16B33, 0, -0x16199), Q12_SHIFT - 1),
                        0xFF);

    ptr->field_74 = MIN(FP_MULTIPLY(CLAMP_LOW_THEN_MIN(D_800AE73C - 0x1000, 0, 0x1000),
                                    func_80055D78(0x16B33, 0, -0x16199), Q12_SHIFT - 1),
                        0xFF);

    ptr->field_78 = MIN(FP_MULTIPLY(CLAMP_LOW_THEN_MIN(D_800AE73C - 0x1000, 0, 0x1000),
                                    func_80055D78(0x16B33, 0, -0x16199), Q12_SHIFT - 1),
                        0xFF);

    *(u16*)&ptr->field_0->r0 = ptr->field_6C + (ptr->field_6C << 8);
    ptr->field_0->b0         = ptr->field_6C;
    *(u16*)&ptr->field_0->r1 = ptr->field_70 + (ptr->field_70 << 8);
    ptr->field_0->b1         = ptr->field_70;
    *(u16*)&ptr->field_0->r2 = ptr->field_74 + (ptr->field_74 << 8);
    ptr->field_0->b2         = ptr->field_74;
    *(u16*)&ptr->field_0->r3 = ptr->field_78 + (ptr->field_78 << 8);
    ptr->field_0->b3         = ptr->field_78;

    addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[(ptr->field_5C + ptr->field_60 + ptr->field_64 + ptr->field_68) >> 5], ptr->field_0);

    GsOUT_PACKET_P = (PACKET*)++ptr->field_0;
}

void func_80066D90() // 0x80066D90
{
    s32       i;
    DR_TPAGE* var1; // Guessed type.
    TILE*     var2; // Guessed type.

    for (i = 0; i < 63; i++)
    {
        var1 = PSX_SCRATCH;
        setDrawTPage(var1, 0, 1, getTPageN(0, 2, 0, 0));
        DrawPrim(var1);

        var2 = PSX_SCRATCH;
        setlen(var2, 3);

        setRGBC0(var2, 8, 8, 8, PRIM_RECT | RECT_BLEND); // `setTile(); setSemiTrans();`
        setXY0Fast(var2, -160, -224);
        setWHFast(var2, 320, 448);
        DrawPrim(var2);

        Fs_QueueUpdate();
        VSync(SyncMode_Wait);
    }

    Fs_QueueWaitForEmpty();
}

void func_80066E40() // 0x80066E40
{
    DrawSync(SyncMode_Wait);
    StoreImage(&D_80028A20, FS_BUFFER_3);
    DrawSync(SyncMode_Wait);
}

void func_80066E7C() // 0x80066E7C
{
    LoadImage(&D_80028A20, FS_BUFFER_3);
    DrawSync(SyncMode_Wait);
}

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_80055028", hack_D_80028A18_fix);

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_80055028", D_80028A20);

void GameState_MapScreen_Update() // 0x80066EB0
{
    s32 temp_s0_2;
    s32 temp_s4;
    s8  temp_a0_4;
    u16 var_s5;
    u16 var_s6;
    u32 temp_a0;
    u32 temp;
    u32 temp2;
    u32 temp3;
    u32 temp4;

    func_800363D0();
    Game_TimerUpdate();

    switch (g_GameWork.gameStateStep_598[0])
    {
        case 0:
            Screen_Refresh(SCREEN_WIDTH, true);

            D_800C444A = g_MapMarkingTimFileIdxs[g_SavegamePtr->current2dMapIdx_A9];
            temp_a0    = g_SavegamePtr->current2dMapIdx_A9;
            D_800C444C = NO_VALUE;
            D_800C4454 = Q12(1.0f);
            D_800AE770 = 0;
            D_800C4448 = temp_a0;

            func_80037188(temp_a0);
            Sd_EngineCmd(Sfx_Unk1308);
            func_80066E40();
            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + g_FullscreenMapTimFileIdxs[D_800C4448], FS_BUFFER_2, &g_MapImg);
            Fs_QueueWaitForEmpty();

            g_IntervalVBlanks   = 1;
            ScreenFade_Start(true, true, false);

            g_GameWork.gameStateStep_598[0] = 2;
            g_SysWork.timer_20              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case 2:
            if (D_800C444C < 0)
            {
                var_s5 = 0;
                var_s6 = 0;
            }
            else
            {
                temp   = D_800C444C - FP_MULTIPLY_PRECISE(D_800C4454, D_800C444C, Q12_SHIFT);
                var_s6 = FP_FROM(temp, Q12_SHIFT);

                temp2  = D_800C4450 - FP_MULTIPLY_PRECISE(D_800C4454, D_800C4450, Q12_SHIFT);
                var_s5 = FP_FROM(temp2, Q12_SHIFT);
            }

            temp_s4 = (D_800C4454 >> 1) + 0x800;

            temp_s0_2 = func_80067914(D_800C4448, var_s6, var_s5, temp_s4);
            func_80068E0C(1, D_800C4448, 0, 0, var_s6, var_s5, temp_s4);

            if (ScreenFade_IsNone())
            {
                if (D_800AE770 == 0 && D_800C4454 == Q12(1.0f))
                {
                    func_80068CC0(D_800C4448);
                }
            }

            func_800692A4(var_s6, var_s5, temp_s4);

            if ((g_GameWork.gameStatePrev_590 == GameState_InventoryScreen && g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2) ||
                (g_GameWork.gameStatePrev_590 != GameState_InventoryScreen && g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.cancel_2 |
                                                                                                               g_GameWorkPtr->config_0.controllerConfig_0.map_18)))
            {
                Sd_EngineCmd(Sfx_Unk1308);

                if (g_GameWork.gameStatePrev_590 == GameState_InventoryScreen)
                {
                    GsDrawOt(&g_OrderingTable0[g_ActiveBufferIdx]);
                    VSync(SyncMode_Wait);
                    GsDrawOt(&g_OrderingTable0[g_ActiveBufferIdx]);
                    func_80066E7C();
                    GameFs_MapItemsTextureLoad(g_SavegamePtr->mapOverlayId_A4);
                    func_80066D90();
                    ScreenFade_ResetTimestep();
                }
                else
                {
                    ScreenFade_Start(true, false, false);
                }

                g_GameWork.gameStateStep_598[0] = 4;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                break;
            }

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                if (D_800AE770 != 0)
                {
                    D_800AE770 = 0;
                }
                else
                {
                    D_800AE770 = 1;

                    if (D_800C444C < 0)
                    {
                        D_800C444C = Q12(CLAMP_LOW_THEN_MIN((s16)temp_s0_2 + 80, 0, 160));
                        D_800C4450 = Q12(CLAMP_LOW_THEN_MIN((temp_s0_2 >> 16) + 60, 0, 120));
                    }
                }
            }

            if (D_800AE770 == 0)
            {
                if (D_800C4454 == Q12(1.0f))
                {
                    if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickUp)
                    {
                        if (HAS_MAP(D_800AE740[D_800C4448][0]))
                        {
                            D_800C4449 = D_800AE740[D_800C4448][0];

                            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + g_FullscreenMapTimFileIdxs[D_800C4449]);
                            ScreenFade_Start(true, false, false);

                            D_800C444C                      = NO_VALUE;
                            g_GameWork.gameStateStep_598[0] = 3;
                            g_SysWork.timer_20              = 0;
                            g_GameWork.gameStateStep_598[1] = 0;
                            g_GameWork.gameStateStep_598[2] = 0;
                            break;
                        }
                    }

                    if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickDown)
                    {
                        if (HAS_MAP(D_800AE740[D_800C4448][1]))
                        {
                            D_800C4449 = D_800AE740[D_800C4448][1];

                            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + g_FullscreenMapTimFileIdxs[D_800C4449]);
                            ScreenFade_Start(true, false, false);

                            D_800C444C = NO_VALUE;
                            g_GameWork.gameStateStep_598[0] = 3;
                            g_SysWork.timer_20              = 0;
                            g_GameWork.gameStateStep_598[1] = 0;
                            g_GameWork.gameStateStep_598[2] = 0;
                            break;
                        }
                    }
                    break;
                }

                D_800C4454 = MIN(D_800C4454 + 196, Q12(1.0f));
                break;
            }

            D_800C4454  = CLAMP_LOW(D_800C4454 - 196, 0);
            D_800C444C += ((g_Controller0->sticks_24.sticks_0.leftX << 14) / 75);
            D_800C444C  = CLAMP_RANGE(D_800C444C, 0, 0xA0000);
            D_800C4450 += ((g_Controller0->sticks_24.sticks_0.leftY << 14) / 75);
            D_800C4450  = CLAMP_RANGE(D_800C4450, 0, 0x78000);
            break;

        case 3:
            if (ScreenFade_IsFinished())
            {
                D_800C4448 = D_800C4449;

                Sd_EngineCmd(Sfx_Unk1308);

                g_GameWork.gameStateStep_598[0] = 1;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                break;
            }

            func_80067914(D_800C4448, 0, 0, Q12(1.0f));
            func_80068E0C(1, D_800C4448, 0, 0, 0, 0, Q12(1.0f));
            func_800692A4(0, 0, Q12(1.0f));
            break;

        case 1:
            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + g_FullscreenMapTimFileIdxs[D_800C4448], FS_BUFFER_2, &g_MapImg);

            temp_a0_4 = g_MapMarkingTimFileIdxs[D_800C4448];
            if (temp_a0_4 != D_800C444A && temp_a0_4 != NO_VALUE)
            {
                D_800C444A = g_MapMarkingTimFileIdxs[D_800C4448];
                Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + g_MapMarkingTimFileIdxs[D_800C4448], FS_BUFFER_1, &g_MapMarkerAtlasImg);
            }

            Fs_QueueWaitForEmpty();
            ScreenFade_Start(true, true, false);

            g_GameWork.gameStateStep_598[0] = 2;
            g_SysWork.timer_20              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case 4:
            temp3   = D_800C444C - FP_MULTIPLY_PRECISE(D_800C4454, D_800C444C, Q12_SHIFT);
            var_s6  = FP_FROM(temp3, Q12_SHIFT);
            temp4   = D_800C4450 - FP_MULTIPLY_PRECISE(D_800C4454, D_800C4450, Q12_SHIFT);
            temp_s4 = (D_800C4454 >> 1) + 0x800;
            var_s5  = FP_FROM(temp4, Q12_SHIFT);

            func_80067914(D_800C4448, var_s6, var_s5, temp_s4);
            func_80068E0C(1, D_800C4448, 0, 0, var_s6, var_s5, temp_s4);
            func_800692A4(var_s6, var_s5, temp_s4);

            if (ScreenFade_IsFinished())
            {
                if (g_GameWork.gameStatePrev_590 == GameState_InGame || g_GameWork.gameStatePrev_590 == GameState_LoadMapScreen)
                {
                    func_80066E7C();
                    Screen_Init(SCREEN_WIDTH, false);
                    g_GameWork.gameStatePrev_590 = GameState_InGame;
                }

                Game_StateSetPrevious();
            }
            break;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80067914); // 0x80067914

bool func_80068CC0(s32 arg0) // 0x80068CC0
{
    s32      i;
    POLY_G3* poly;

    for (i = 0; i < 2; i++)
    {
        if (HAS_MAP(D_800AE740[arg0][i]))
        {
            poly = GsOUT_PACKET_P;
            setPolyG3(poly);

            if (i != 0)
            {
                setXY0Fast(poly,  0, 216);
                setXY1Fast(poly, -8, 200);
                setXY2Fast(poly,  8, 200);
            }
            else
            {
                setXY0Fast(poly,  0, -216);
                setXY1Fast(poly, -8, -200);
                setXY2Fast(poly,  8, -200);
            }

            *(u16*)&poly->r0 = 0x1010;
            poly->b0         = 0xC4;
            *(u16*)&poly->r1 = 0x8080;
            poly->b1         = 0xC4;
            *(u16*)&poly->r2 = 0x8080;
            poly->b2         = 0xC4;

            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], poly);
            GsOUT_PACKET_P = ++poly;
        }
    }

    return true;
}

bool func_80068E0C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 arg4, u16 arg5, u16 arg6) // 0x80068E0C
{
    s32              sp0;
    u16              sp4;
    s16              temp_v1_3;
    s32              temp_a0;
    s32              temp_a0_2;
    s32              temp_v1_4;
    s32              var_t4;
    s32              var_t5;
    s32              temp;
    s32              temp2;
    s16              temp3;
    s32              temp4;
    s32              temp6;
    s_func_80068E0C* ptr;

    ptr = PSX_SCRATCH;

    if (g_MapMarkingTimFileIdxs[arg1] == NO_VALUE)
    {
        return false;
    }

    if (D_800AEDBC[arg1].ptr_0 == NULL)
    {
        return false;
    }

    if (D_800AEDBC[arg1].ptr_4 == NULL)
    {
        return false;
    }

    ptr->field_0 = (POLY_FT4*)GsOUT_PACKET_P;
    var_t5       = 0;

    if (arg0 == 2)
    {
        var_t5       = (arg2 - D_800AEDBC[arg1].field_8) >> 1;
        ptr->field_C = var_t5 + 1;
    }
    else
    {
        arg3         = 0x80;
        ptr->field_C = (D_800AEDBC[arg1].field_A - D_800AEDBC[arg1].field_8) >> 1;
    }

    for (; var_t5 < ptr->field_C; var_t5++)
    {
        for (var_t4 = 0; var_t4 < 2; var_t4++)
        {
            if (arg0 == 1 && !Savegame_EventFlagGet(D_800AEDBC[arg1].field_8 + (var_t5 * 2) + var_t4 + 1))
            {
                continue;
            }

            if (arg0 == 2 && (arg2 & 1) != var_t4)
            {
                continue;
            }

            ptr->field_8 = *(s_800AE8A0_4*)&D_800AEDBC[arg1].ptr_4[var_t5];
            if (var_t4 != 0)
            {
                if (ptr->field_8.field_3)
                {
                    ptr->field_4 = *(s_800AE8A0_0*)&D_800AEDBC[arg1].ptr_0[ptr->field_8.field_3];
                }
                else
                {
                    continue;
                }
            }
            else if (ptr->field_8.field_2)
            {
                ptr->field_4 = *(s_800AE8A0_0*)&D_800AEDBC[arg1].ptr_0[ptr->field_8.field_2];
            }
            else
            {
                continue;
            }

            sp4     = 0xA0;
            temp6   = (ptr->field_8.field_0 << 1) - (arg4 - sp4);
            temp_a0 = (FP_TO(temp6, Q12_SHIFT) / arg6) - 0xA0;

            sp4       = 0xF0;
            temp4     = FP_TO((ptr->field_8.field_1 << 1) - ((arg5 * 2) - sp4), Q12_SHIFT);
            temp_v1_3 = (temp4 / arg6) - 0xF0;

            temp_a0_2 = temp_a0 + FP_TO(ptr->field_4.field_2, Q12_SHIFT) / arg6;
            temp3     = FP_TO(ptr->field_4.field_3, Q12_SHIFT) / arg6;
            temp_v1_4 = temp_v1_3 + temp3;

            setPolyFT4(ptr->field_0);
            setXY0Fast(ptr->field_0, temp_a0, temp_v1_3);
            setXY1Fast(ptr->field_0, temp_a0_2, temp_v1_3);
            setXY2Fast(ptr->field_0, temp_a0, temp_v1_4);
            setXY3Fast(ptr->field_0, temp_a0_2, temp_v1_4);

            temp                       = (ptr->field_4.field_1 << 8) + 0x80;
            *((s32*)&ptr->field_0->u0) = ptr->field_4.field_0 + temp + (getClut(g_MapMarkerAtlasImg.clutX, g_MapMarkerAtlasImg.clutY) << 16);
            temp2                      = ptr->field_4.field_2 + 0x80;
            *((s32*)&ptr->field_0->u1) = ptr->field_4.field_0 + temp2 + (ptr->field_4.field_1 << 8) + 0x470000;
            sp0                        = ((ptr->field_4.field_1 + ptr->field_4.field_3) << 8) + 0x80;
            *((s16*)&ptr->field_0->u2) = ptr->field_4.field_0 + sp0;
            *((s16*)&ptr->field_0->u3) = ptr->field_4.field_2 + (ptr->field_4.field_0 + 0x80) + ((ptr->field_4.field_1 + ptr->field_4.field_3) << 8);

            setRGBC0(ptr->field_0, arg3, arg3, arg3, 0x2E);
            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[3], ptr->field_0);
            ptr->field_0++;
        }
    }

    GsOUT_PACKET_P = (PACKET*)ptr->field_0;
    return true;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_800692A4); // 0x800692A4

void func_800697EC()
{
    func_80069820(1);
    D_800C447A = 0;
}

u16 func_80069810() // 0x80069810
{
    return D_800C4478.field_0;
}

void func_80069820(u16 arg0) // 0x80069820
{
    D_800C4478.field_0 = arg0;
}

void func_8006982C(u16 arg0) // 0x8006982C
{
    D_800C4478.field_0 |= arg0;
}

void func_80069844(s32 arg0) // 0x80069844
{
    D_800C4478.field_0 = (D_800C4478.field_0 & ~arg0) | (1 << 0);
}

void func_80069860(s32 arg0, s32 arg1, s_func_8006F8FC* arg2) // 0x80069860
{
    s_func_8006F8FC* ptr;
    q19_12           minX;
    q19_12           maxX;
    q19_12           minZ;
    q19_12           maxZ;

    D_800C4478.field_2 = 0;

    for (ptr = arg2; !(ptr->field_0_0 & 1); ptr++)
    {
        minX = FP_TO(ptr->field_0_1, Q12_SHIFT);
        maxX = FP_TO(ptr->field_0_1 + ptr->field_0_21, Q12_SHIFT);
        minZ = FP_TO(ptr->field_0_11, Q12_SHIFT);
        maxZ = FP_TO(ptr->field_0_11 + ptr->field_0_25, Q12_SHIFT);

        minX -= 0x10000;
        maxX += 0x10000;
        minZ -= 0x10000;
        maxZ += 0x10000;

        if (arg0 >= minX && maxX >= arg0 &&
            arg1 >= minZ && maxZ >= arg1)
        {
            D_800C4478.field_4[D_800C4478.field_2] = ptr;
            D_800C4478.field_2++;
        }
    }
}

void IpdCollData_FixOffsets(s_IpdCollisionData* collData) // 0x8006993C
{
    collData->ptr_C  = (u8*)collData->ptr_C + (u32)collData;
    collData->ptr_10 = (u8*)collData->ptr_10 + (u32)collData;
    collData->ptr_14 = (u8*)collData->ptr_14 + (u32)collData;
    collData->ptr_18 = (u8*)collData->ptr_18 + (u32)collData;
    collData->ptr_20 = (u8*)collData->ptr_20 + (u32)collData;
    collData->ptr_28 = (u8*)collData->ptr_28 + (u32)collData;
    collData->ptr_2C = (u8*)collData->ptr_2C + (u32)collData;
}

void func_80069994(s_IpdCollisionData* collData) // 0x80069994
{
    s32* ptr;

    collData->field_30++;
    if (collData->field_30 > 252)
    {
        collData->field_30 = 0;

        // TODO: Is this `memset`/`bzero`?
        for (ptr = &collData->field_34[0]; ptr < &collData->field_34[256]; ptr++)
        {
            *ptr = 0;
        }
    }
}

void func_800699E4(s_IpdCollisionData* collData) // 0x800699E4
{
    collData->field_30++;
}

void Collision_Get(s_Collision* coll, q19_12 posX, q19_12 posZ) // 0x800699F8
{
    s_func_8006AB50     sp10;
    VECTOR3             pos;
    s_func_8006CC44     sp38;
    s_IpdCollisionData* ipdCollData;

    pos.vx = Q12(0.0f);
    pos.vy = Q12(0.0f);
    pos.vz = Q12(0.0f);

    ipdCollData = func_800426E4(posX, posZ);
    if (ipdCollData == NULL)
    {
        coll->groundHeight_0 = Q12(8.0f);
        coll->field_6        = 0;
        coll->field_4        = 0;
        coll->field_8        = 0;
        return;
    }

    sp10.position_0.vx = posX;
    sp10.position_0.vy = Q12(0.0f);
    sp10.position_0.vz = posZ;
    sp10.rotation_C.vx = FP_ANGLE(0.0f);
    sp10.rotation_C.vy = FP_ANGLE(0.0f);
    sp10.rotation_C.vz = FP_ANGLE(0.0f);
    func_8006AB50(&sp38, &pos, &sp10, 0);

    sp38.field_0_8  = 0;
    sp38.field_0_9  = 0;
    sp38.field_0_10 = 1;
    func_8006AD44(&sp38, ipdCollData);

    if (sp38.field_90 == 1)
    {
        coll->field_8        = 0;
        coll->groundHeight_0 = Q12(8.0f);
    }
    else
    {
        coll->field_8        = sp38.field_94;
        coll->groundHeight_0 = func_8006CC44(sp38.field_4.positionX_18, sp38.field_4.positionZ_1C, &sp38) * 16; // TODO: Converting from Q8 to Q12?
    }

    coll->field_4 = sp38.field_88;
    coll->field_6 = sp38.field_8C;
}

s32 func_80069B24(s_800C4590* arg0, VECTOR3* offset, s_SubCharacter* chara) // 0x80069B24
{
    s32 var0; 
    s32 var1;

    var0 = SetSp(0x1F8003D8);
    var1 = func_80069BA8(arg0, offset, chara, func_80069FFC(arg0, offset, chara));
    SetSp(var0);
    return var1; 
}

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_80055028", D_80028B2C);

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_80055028", D_80028B34);

s32 func_80069BA8(s_800C4590* arg0, VECTOR3* offset, s_SubCharacter* chara, s32 arg4) // 0x80069BA8
{
    #define POINT_COUNT          9
    #define ANGLE_STEP           FP_ANGLE(370.0f / POINT_COUNT) // @bug? Maybe `360.0f` was intended.
    #define WALL_COUNT_THRESHOLD 3                              // Unknown purpose.
    #define WALL_HEIGHT          Q12(0.5f)

    s_Collision     coll;
    e_CollisionType collType;
    s32             groundHeight;
    q19_12          wallHeightBound;
    s32             i;
    s32             wallCount;
    s32             var_s6;

    if (arg4 == -1)
    {
        arg4 = 1;
        if (chara == &g_SysWork.player_4C && chara->health_B0 > Q12(0.0f))
        {
            func_80069DF0(arg0, &chara->position_18, chara->position_18.vy, chara->rotation_24.vy);
        }
    }

    switch (chara->model_0.charaId_0)
    {
        case Chara_Harry:
        case Chara_Groaner:
        case Chara_Wormhead:
        case Chara_LarvalStalker:
        case Chara_Stalker:
        case Chara_GreyChild:
        case Chara_Mumbler:
        case Chara_Creaper:
        case Chara_Romper:
        case Chara_PuppetNurse:
        case Chara_PuppetDoctor:
            wallHeightBound = chara->position_18.vy - WALL_HEIGHT;

            switch (arg0->field_14)
            {
                case 12:
                    collType = CollisionType_Unk2;
                    break;

                default:
                    collType = (arg0->field_C < wallHeightBound) ? CollisionType_Wall : CollisionType_None;
                    break;
            }

            wallCount = 0;
            if (collType == CollisionType_None)
            {
                break;
            }

            for (i = 0, var_s6 = 12; i < POINT_COUNT; i++)
            {
                Collision_Get(&coll,
                              chara->position_18.vx + FP_MULTIPLY(Math_Sin(i * ANGLE_STEP), Q12(0.2f), Q12_SHIFT),
                              chara->position_18.vz + FP_MULTIPLY(Math_Cos(i * ANGLE_STEP), Q12(0.2f), Q12_SHIFT));

                switch (collType)
                {
                    case CollisionType_Wall:
                        if (coll.groundHeight_0 < wallHeightBound)
                        {
                            wallCount++;
                        }
                        break;

                    case CollisionType_Unk2:
                        if (coll.field_8 != 12)
                        {
                            var_s6 = coll.field_8;
                            groundHeight = coll.groundHeight_0;
                        }
                        break;
                }
            }

            switch (collType)
            {
                case 1:
                    if (wallCount < WALL_COUNT_THRESHOLD)
                    {
                        arg0->field_C = chara->position_18.vy;
                    }
                    break;

                case 2:
                    if (var_s6 != 12)
                    {
                        arg0->field_C  = groundHeight;
                        arg0->field_14 = 12;
                    }
                    break;
            }
            break;
    }

    return arg4;
}

static const u8 unk_rdata[] = { 0, 66, 5, 128, 0, 0, 0, 0 };

void func_80069DF0(s_800C4590* arg0, VECTOR3* pos, s32 arg2, s32 arg3) // 0x80069DF0
{
    #define POINT_COUNT 16
    #define ANGLE_STEP  FP_ANGLE(360.0f / POINT_COUNT)

    s32         groundHeights[POINT_COUNT];
    s_Collision coll;
    q19_12      angle;
    s32         var_a0;
    q19_12      groundHeight;
    s32         var_s0;
    s32         i;
    q19_12      groundHeightMax;
    q19_12      groundHeightMin;
    s32         var_s5;

    groundHeightMin = Q12(-30.0f);
    groundHeightMax = Q12(30.0f);
    var_s5 = 0;

    // Collect ground heights around position?
    for (i = 0; i < POINT_COUNT; i++)
    {
        Collision_Get(&coll,
                      pos->vx + Math_Sin((arg3 & 0xF) + (i * ANGLE_STEP)),
                      pos->vz + Math_Cos((arg3 & 0xF) + (i * ANGLE_STEP)));
        groundHeights[i] = coll.groundHeight_0;

        if (groundHeightMin < coll.groundHeight_0)
        {
            groundHeightMin = coll.groundHeight_0;
            var_s5 = i;
        }

        if (coll.groundHeight_0 < groundHeightMax)
        {
            groundHeightMax = coll.groundHeight_0;
        }
    }

    groundHeight = (groundHeightMin + groundHeightMax) >> 1; // `/ 2`.
    if (groundHeight < (arg2 - Q12(0.1f)))
    {
        groundHeight = arg2 - Q12(0.1f);
    }

    for (i = var_s5 + 1, var_a0 = var_s5;
         i < (var_s5 + POINT_COUNT) && groundHeight < groundHeights[i & 0xF];
         i++)
    {
        var_a0 = i;
    }

    for (i = var_s5 - 1, var_s0 = var_s5;
         i < (var_s5 - POINT_COUNT) && groundHeight < groundHeights[i & 0xF];
         i--)
    {
        var_s0 = i;
    }

    angle = ((var_s0 + var_a0) << 8) >> 1;
    arg0->offset_0.vx = FP_MULTIPLY_PRECISE(Math_Sin(angle), Q12(1.0f / 16.0f), Q12_SHIFT);
    arg0->offset_0.vz = FP_MULTIPLY_PRECISE(Math_Cos(angle), Q12(1.0f / 16.0f), Q12_SHIFT);
}

s32 func_80069FFC(s_800C4590* arg0, VECTOR3* offset, s_SubCharacter* chara) // 0x80069FFC
{
    s_func_8006AB50 sp28;
    VECTOR3         offsetSpy;
    s32             collDataIdx;
    s32             charaCount;
    s32             var_s1; // TODO: Maybe `bool`?

    sp28.position_0.vx = chara->position_18.vx + chara->field_D8.offsetX_4;
    sp28.position_0.vy = chara->position_18.vy - Q12(0.02f);
    sp28.position_0.vz = chara->position_18.vz + chara->field_D8.offsetZ_6;

    if (func_800426E4(chara->position_18.vx, chara->position_18.vz) == NULL)
    {
        func_8006A178(arg0, Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(8.0f));
        return 1;
    }

    sp28.rotation_C.vy = chara->field_C8;
    sp28.rotation_C.vx = chara->field_CA;
    sp28.rotation_C.vz = chara->field_D4;

    sp28.field_12 = chara->field_E1_0;

    offsetSpy = *offset;

    switch (chara->model_0.charaId_0)
    {
        case Chara_Harry:
        case Chara_Groaner:
        case Chara_Wormhead:
        case Chara_Romper:
            var_s1 = 1;
            break;

        default:
            var_s1 = 0;
            break;
    }

    return func_8006A4A8(arg0, &offsetSpy, &sp28, var_s1, func_800425D8(&collDataIdx), collDataIdx, NULL, 0, func_8006A1A4(&charaCount, chara, true), charaCount);
}

void func_8006A178(s_800C4590* arg0, q19_12 posX, q19_12 posY, q19_12 posZ, q19_12 heightY) // 0x8006A178
{
    arg0->offset_0.vx = posX;
    arg0->offset_0.vy = posY;
    arg0->offset_0.vz = posZ;
    arg0->field_12    = 0;
    arg0->field_10    = 0;
    arg0->field_14    = 0;
    arg0->field_18    = 0xFFFF0000;
    arg0->field_C     = heightY;
}

s_SubCharacter** func_8006A1A4(s32* charaCount, s_SubCharacter* chara, bool arg2) // 0x8006A1A4
{
    s_SubCharacter* curChara;

    if (chara != NULL &&
        (chara->model_0.charaId_0 == Chara_None || chara->field_E1_0 == 0 ||
        (chara->field_E1_0 == 1 && arg2 == true)))
    {
        *charaCount = 0;
        return &D_800C4458;
    }

    *charaCount = 0;
    D_800C4474 = &D_800C4458;

    for (curChara = &g_SysWork.npcs_1A0[0]; curChara < &g_SysWork.npcs_1A0[NPC_COUNT_MAX]; curChara++)
    {
        if (curChara->model_0.charaId_0 != Chara_None)
        {
            if (curChara->field_E1_0 != 0 &&
                (curChara->field_E1_0 != 1 || arg2 != true) &&
                curChara != chara &&
                (arg2 != true || chara == NULL || chara->field_E1_0 != 4 || curChara->field_E1_0 >= chara->field_E1_0))
            {
                *charaCount += 1;
                *D_800C4474 = curChara;
                D_800C4474++;
                curChara->field_E0 = 0;
            }
        }
    }

    curChara = &g_SysWork.player_4C.chara_0;
    if (curChara->model_0.charaId_0 != Chara_None)
    {
        if (curChara->field_E1_0 != 0 &&
            (curChara->field_E1_0 != 1 || arg2 != true) &&
            curChara != chara &&
            (arg2 != true || chara == NULL || chara->field_E1_0 != 4 || curChara->field_E1_0 >= chara->field_E1_0))
        {
            *charaCount += 1;
            *D_800C4474 = curChara;
            D_800C4474++;
            curChara->field_E0 = 0;
        }
    }

    return &D_800C4458;
}

s32 func_8006A3B4(s32 arg0, VECTOR* offset, s_func_8006AB50* arg2) // 0x8006A3B4
{
    s32 stackPtr;
    s32 var1;

    stackPtr = SetSp(0x1F8003D8);
    var1 = func_8006A42C(arg0, offset, arg2);
    SetSp(stackPtr);

    if (var1 == NO_VALUE)
    {
        var1 = 1;
    }

    return var1;
}

s32 func_8006A42C(s32 arg0, VECTOR3* offset, s_func_8006AB50* arg2) // 0x8006A42C
{
    VECTOR3 offsetCpy;
    s32     collDataIdx;

    offsetCpy = *offset;

    return func_8006A4A8(arg0, &offsetCpy, arg2, 0, func_800425D8(&collDataIdx), collDataIdx, NULL, 0, NULL, 0);
}

s32 func_8006A4A8(s_800C4590* arg0, VECTOR3* offset, s_func_8006AB50* arg2, s32 arg3,
                  s_IpdCollisionData** collDataPtrs, s32 collDataIdx, s_func_8006CF18* arg6, s32 arg7, s_SubCharacter** charas, s32 charaCount) // 0x8006A4A8
{
    s_func_8006CC44      sp18;
    VECTOR3              sp120; // Q19.12
    VECTOR3              sp130;
    VECTOR3              offsetCpy;
    s32                  var_a0;
    s32                  var_a1;
    s32                  var_s4;
    s32                  var_v0;
    s32                  var_a2;
    s_SubCharacter**     curChara;
    s_IpdCollisionData** curCollData;
    s_SubCharacter*      chara;

    var_s4 = 0;

    if (arg2->field_12 == 5)
    {
        func_8006A178(arg0, offset->vx, offset->vy, offset->vz, arg2->position_0.vy);
        return 0;
    }

    func_8006A940(offset, arg2, charas, charaCount);

    offsetCpy = *offset;

    arg0->field_18 = func_8006F620(&offsetCpy, arg2, arg2->rotation_C.vz, arg2->rotation_C.vy);

    func_8006AB50(&sp18, &offsetCpy, arg2, arg3);

    sp130 = offsetCpy;

    arg0->offset_0.vz = Q12(0.0f);
    arg0->offset_0.vx = Q12(0.0f);
    arg0->offset_0.vy = offsetCpy.vy;

    while (true)
    {
        if (sp18.field_0_0 != 0)
        {
            sp18.field_0_8  = sp18.field_4.field_8 != 0;
            sp18.field_0_9  = 0;
            sp18.field_0_10 = 0;
        }
        else
        {
            sp18.field_0_8  = sp18.field_4.field_8 != 0;
            sp18.field_0_9  = 1;
            sp18.field_0_10 = 1;
        }

        // Run through collision data.
        for (curCollData = collDataPtrs; curCollData < &collDataPtrs[collDataIdx]; curCollData++)
        {
            func_8006AD44(&sp18, *curCollData);
        }

        if (sp18.field_44.field_0.field_0 && sp18.field_44.field_0.field_2.vx == sp18.field_44.field_0.field_2.vy)
        {
            var_s4 |= 1;
        }

        func_8006CF18(&sp18, arg6, arg7);

        // Run through characters.
        for (curChara = charas; curChara < &charas[charaCount]; curChara++)
        {
            chara  = *curChara;
            var_a0 = (chara->field_D4 >> 4) + sp18.field_4.field_28;

            if (chara->field_E1_0 < (u32)sp18.field_4.field_0)
            {
                var_a0 -= 15;
            }

            sp18.field_98.field_0 = Q12_TO_Q8(chara->position_18.vx + chara->field_D8.offsetX_4);
            sp18.field_9C.field_0 = Q12_TO_Q8(chara->position_18.vz + chara->field_D8.offsetZ_6);

            sp18.field_A0.s_1.field_0 = Q12_TO_Q8(chara->field_C8 + chara->position_18.vy);
            sp18.field_A0.s_1.field_2 = Q12_TO_Q8(chara->field_CA + chara->position_18.vy);
            sp18.field_A0.s_1.field_4 = var_a0;
            sp18.field_A0.s_1.field_6 = chara->field_E1_0;
            sp18.field_A0.s_1.field_8 = &chara->field_E0;

            if (sp18.field_0_0 == 0)
            {
                chara->field_E0 = 0;
            }

            func_8006CC9C(&sp18);
            func_8006CF18(&sp18, chara->properties_E4.npc.unk_E4, chara->field_E1_4);
        }

        func_8006D01C(&sp120, &sp130, func_8006CB90(&sp18), &sp18);

        arg0->offset_0.vx += sp120.vx;
        arg0->offset_0.vz += sp120.vz;

        if (sp18.field_0_0)
        {
            break;
        }

        if (sp18.field_44.field_0.field_0 || sp18.field_44.field_30.field_0)
        {
            var_a2 = 8;
            if (sp18.field_44.field_8.field_0 < 9)
            {
                var_a2 = sp18.field_44.field_8.field_0;
            }

            for (var_a1 = 0; var_a1 < var_a2; var_a1++)
            {
                *sp18.field_44.field_10[var_a1] += 1;
            }
        }
        else if (sp18.field_34)
        {
            *sp18.field_40 += 1;
        }
        else
        {
            break;
        }

        sp18.field_0_0 = 1;
        func_8006D774(&sp18, &sp120, &sp130);
    }

    if (sp18.field_90 == 1)
    {
        var_v0         = Q12(8.0f);
        arg0->field_14 = 0;
    }
    else
    {
        arg0->field_14 = sp18.field_94;
        var_v0         = func_8006CC44(sp18.field_4.positionX_18 + Q12_TO_Q8(sp120.vx),
                                       sp18.field_4.positionZ_1C + Q12_TO_Q8(sp120.vz),
                                       &sp18) *
                         16;
    }

    arg0->field_C  = var_v0;
    arg0->field_10 = sp18.field_88;
    arg0->field_12 = sp18.field_8C;

    if (var_s4 != 0)
    {
        return -1;
    }

    return sp18.field_0_0 != 0;
}

void func_8006A940(VECTOR3* offset, s_func_8006AB50* arg1, s_SubCharacter** charas, s32 charaCount) // 0x8006A940
{
    s32             angle;
    s32             posZ;
    s32             posX;
    s32             var_a0;
    s32             i;
    s32             var_s4;
    s32             var_v0;
    s32             temp2;
    s32             temp3;
    s32             temp4;
    s32             temp5;
    s32             temp6;
    s_SubCharacter* curChara;

    var_s4 = Q12(1.0f);
    angle  = ratan2(offset->vx, offset->vz);

    for (i = 0; i < charaCount; i++)
    {
        curChara = charas[i];
        if (!curChara->field_E1_0 || curChara->field_E1_0 == (1 << 0) || curChara->field_E1_0 >= arg1->field_12)
        {
            continue;
        }

        temp3 = curChara->field_C8 + curChara->position_18.vy;
        temp4 = curChara->field_CA + curChara->position_18.vy;

        // TODO: Rotation + position? Seems wrong.
        temp6 = arg1->rotation_C.vy + arg1->position_0.vy;
        temp5 = arg1->rotation_C.vx + arg1->position_0.vy;
        if (temp3 > temp5 || temp4 < temp6)
        {
            continue;
        }

        posX = (curChara->position_18.vx + curChara->field_D8.offsetX_4) - arg1->position_0.vx;
        posZ = (curChara->position_18.vz + curChara->field_D8.offsetZ_6) - arg1->position_0.vz;

        temp2 = Vc_VectorMagnitudeCalc(posX, Q12(0.0f), posZ);
        if (((curChara->field_D4 + arg1->rotation_C.vz) + FP_ANGLE(36.0f)) < temp2)
        {
            continue;
        }

        var_a0 = FP_MULTIPLY(Math_Cos(ratan2(posX, posZ) - angle), Q12(1.5f), Q12_SHIFT);

        var_v0 = MAX(var_a0, 0);
        var_a0 = var_v0;

        // Radius calc?
        if (curChara->model_0.charaId_0 == Chara_HangedScratcher)
        {
            var_a0 = MIN(var_a0, Q12(0.6f));
        }
        else
        {
            var_a0 = MIN(var_a0, Q12(0.4f));
        }

        var_s4 -= var_a0;
    }

    var_s4 = MAX(var_s4, Q12(0.4f));

    offset->vx = FP_MULTIPLY(var_s4, offset->vx, Q12_SHIFT);
    offset->vz = FP_MULTIPLY(var_s4, offset->vz, Q12_SHIFT);
}

void func_8006AB50(s_func_8006CC44* arg0, VECTOR3* pos, s_func_8006AB50* arg2, s32 arg3) // 0x8006AB50
{
    arg0->field_0_0       = 0;
    arg0->field_2         = D_800C4478.field_0;
    arg0->field_4.field_4 = arg3;

    func_8006ABC0(&arg0->field_4, pos, arg2);

    arg0->field_7C = 0x1E00;
    arg0->field_34 = 0;
    arg0->field_44.field_0.field_0  = 0;
    arg0->field_44.field_6          = 0;
    arg0->field_44.field_8.field_0  = 0;
    arg0->field_44.field_36         = 0;
    arg0->field_44.field_30.field_0 = 0;
    arg0->field_8C = 0;
    arg0->field_88 = 0;
    arg0->field_90 = 1;
    arg0->field_94 = 0;
}

void func_8006ABC0(s_func_8006ABC0* result, VECTOR3* pos, s_func_8006AB50* arg2) // 0x8006ABC0
{
    q3_12 angleXz;

    result->field_C.vx = Q12_TO_Q8(pos->vx);
    result->field_C.vy = Q12_TO_Q8(pos->vy);
    result->field_C.vz = Q12_TO_Q8(pos->vz);

    result->field_8 = SquareRoot0(SQUARE(result->field_C.vx) + SQUARE(result->field_C.vz));

    if (result->field_8 != 0)
    {
        // @unused
        result->direction_14.vx = Q12(result->field_C.vx) / result->field_8;
        result->direction_14.vz = Q12(result->field_C.vz) / result->field_8;

        angleXz                 = ratan2(result->field_C.vz, result->field_C.vx);
        result->direction_14.vx = Math_Cos(angleXz);
        result->direction_14.vz = Math_Sin(angleXz);
    }
    else
    {
        result->direction_14.vx = Q12(1.0f);
        result->direction_14.vz = Q12(0.0f);
    }

    result->field_28     = FP_FROM(arg2->rotation_C.vz, Q4_SHIFT); // TODO: Packed angle?
    result->positionX_18 = Q12_TO_Q8(arg2->position_0.vx);
    result->positionZ_1C = Q12_TO_Q8(arg2->position_0.vz);
    result->field_20     = result->positionX_18 + result->field_C.vx;
    result->field_24     = result->positionZ_1C + result->field_C.vz;
    result->field_2A     = FP_FROM(arg2->rotation_C.vy + arg2->position_0.vy, Q4_SHIFT); // TODO: Position + rotation? Seems wrong.
    result->field_2C     = FP_FROM(arg2->rotation_C.vx + arg2->position_0.vy, Q4_SHIFT);
    result->field_0      = arg2->field_12;
}

void func_8006AD44(s_func_8006CC44* arg0, s_IpdCollisionData* collData) // 0x8006AD44
{
    s32                    endIdx;
    s32                    startIdx;
    s32                    i;
    s32                    j;
    s_IpdCollisionData_20* curUnk;

    if ((collData->field_8_8 == 0 && collData->field_8_16 == 0 && collData->field_8_24 == 0) ||
        !func_8006AEAC(arg0, collData))
    {
        return;
    }

    if (arg0->field_0_0 == 0)
    {
        func_80069994(collData);
    }

    startIdx = arg0->field_A0.s_0.field_0;
    endIdx   = (arg0->field_A0.s_0.field_0 + arg0->field_A0.s_0.field_2) - 1;

    for (i = arg0->field_A0.s_0.field_1; i < (arg0->field_A0.s_0.field_1 + arg0->field_A0.s_0.field_3); i++)
    {
        curUnk = &collData->ptr_20[(i * collData->field_1E) + startIdx];

        for (j = startIdx; j <= endIdx; j++, curUnk++)
        {
            func_8006B1C8(arg0, collData, curUnk);
        }
    }

    if (arg0->field_0_0 == 0)
    {
        func_800699E4(collData);
    }

    if (arg0->field_0_10)
    {
        func_8006C838(arg0, collData);
        if (arg0->field_A0.s_0.field_4 != NULL)
        {
            func_8006CA18(arg0, collData, arg0->field_A0.s_0.field_4);
        }
    }
}

bool func_8006AEAC(s_func_8006CC44* arg0, s_IpdCollisionData* collData) // 0x8006AEAC
{
    s_func_8006CC44_A8* curUnk;

    if (!func_8006B004(arg0, collData))
    {
        return false;
    }

    arg0->field_98.vec_0.vx = arg0->field_4.positionX_18 - collData->positionX_0;
    arg0->field_98.vec_0.vz = arg0->field_4.positionZ_1C - collData->positionZ_4;
    arg0->field_9C.vec_0.vx = arg0->field_4.field_20 - collData->positionX_0;
    arg0->field_9C.vec_0.vz = arg0->field_4.field_24 - collData->positionZ_4;

    if ((arg0->field_98.vec_0.vx / collData->field_1C) < 0 || (arg0->field_98.vec_0.vx / collData->field_1C) >= collData->field_1E ||
        ((arg0->field_98.vec_0.vz / collData->field_1C) < 0) || (arg0->field_98.vec_0.vz / collData->field_1C) >= collData->field_1F)
    {
        arg0->field_A0.s_0.field_4 = NULL;
        return true;
    }

    arg0->field_A0.s_0.field_4 = (s_func_8006CA18*)&collData->ptr_20[((arg0->field_98.vec_0.vz / collData->field_1C) * collData->field_1E) +
                                                                     (arg0->field_98.vec_0.vx / collData->field_1C)];
    arg0->field_C8             = UCHAR_MAX;

    for (curUnk = arg0->field_A0.s_0.field_8; curUnk < &arg0->field_C8; curUnk++)
    {
        curUnk->field_0 = 0;
        curUnk->field_1 = UCHAR_MAX;
        curUnk->field_4 = INT_MAX;
    }

    return true;
}

bool func_8006B004(s_func_8006CC44* arg0, s_IpdCollisionData* collData) // 0x8006B004
{
    s32 var_a0;
    s32 var_a3;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_t3;
    s32 temp_t4;
    s32 var_a2;
    s32 var_t0;

    temp_lo   = collData->field_1C * collData->field_1E;
    temp_t3   = temp_lo - 1;
    temp_lo_2 = collData->field_1C * collData->field_1F;
    temp_t4   = temp_lo_2 - 1;

    var_a3 = arg0->field_4.positionX_18 - collData->positionX_0;
    var_t0 = arg0->field_4.field_20 - collData->positionX_0;
    if (var_t0 < var_a3)
    {
        var_t0 ^= var_a3;
        var_a3 ^= var_t0;
        var_t0 ^= var_a3;
    }

    var_a3 -= arg0->field_4.field_28;
    var_t0 += arg0->field_4.field_28;

    var_a0 = arg0->field_4.positionZ_1C - collData->positionZ_4;
    var_a2 = arg0->field_4.field_24 - collData->positionZ_4;
    if (var_a2 < var_a0)
    {
        var_a2 ^= var_a0;
        var_a0 ^= var_a2;
        var_a2 ^= var_a0;
    }

    var_a0 -= arg0->field_4.field_28;
    var_a2 += arg0->field_4.field_28;

    if (temp_lo < var_a3 || temp_lo_2 < var_a0 || var_t0 < 0 || var_a2 < 0)
    {
        return false;
    }

    var_a3 = limitRange(var_a3, 0, temp_t3);
    var_a0 = limitRange(var_a0, 0, temp_t4);
    var_t0 = limitRange(var_t0, 0, temp_t3);
    var_a2 = limitRange(var_a2, 0, temp_t4);

    arg0->field_A0.s_0.field_0 = var_a3 / collData->field_1C;
    arg0->field_A0.s_0.field_1 = var_a0 / collData->field_1C;
    arg0->field_A0.s_0.field_2 = ((var_t0 / collData->field_1C) - arg0->field_A0.s_0.field_0) + 1;
    arg0->field_A0.s_0.field_3 = ((var_a2 / collData->field_1C) - arg0->field_A0.s_0.field_1) + 1;

    return true;
}

void func_8006B1C8(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s_IpdCollisionData_20* arg2) // 0x8006B1C8
{
    s32 var;
    s32 i;
    u8  idx;

    for (i = arg2[0].field_0; i < arg2[1].field_0; i++)
    {
        idx = collData->ptr_28[i];

        if (collData->field_30 >= collData->field_34[idx])
        {
            collData->field_34[idx] = collData->field_30 + 1;
            var                     = collData->field_8_16;

            if (idx < var)
            {
                if (func_8006B318(arg0, collData, idx))
                {
                    if (arg0->field_0_10)
                    {
                        func_8006B6E8(arg0, arg2);
                    }

                    if (arg0->field_0_8 || arg0->field_0_9)
                    {
                        if (arg0->field_CC.field_C.s_field_0.field_1 == 0xFF)
                        {
                            func_8006B9C8(arg0);
                        }

                        if (arg0->field_CC.field_C.s_field_0.field_0 == 0xFF)
                        {
                            func_8006B8F8(&arg0->field_CC);
                            func_8006B9C8(arg0);
                        }
                    }
                }
            }
            else if (func_8006C3D4(arg0, collData, idx))
            {
                func_8006C45C(arg0);
            }
        }
    }
}

bool func_8006B318(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s32 idx) // 0x8006B318
{
    s32                    temp_a0_5;
    s32                    temp_s0;
    s32                    temp_v0;
    s_IpdCollisionData_10* temp_a0;
    s_IpdCollisionData_14* temp_a3;

    temp_a3 = &collData->ptr_14[idx];

    if (!((arg0->field_2 >> (temp_a3->field_0_14 * 4 | temp_a3->field_2_14)) & (1 << 0)))
    {
        return false;
    }

    arg0->field_CC.field_0 = collData;
    arg0->field_CC.field_4 = idx;

    arg0->field_CC.field_6.vx = temp_a3->field_0_0;
    arg0->field_CC.field_6.vy = temp_a3->field_2_0;
    arg0->field_CC.field_6.vz = temp_a3->field_4;

    arg0->field_CC.field_12 = collData->ptr_C[temp_a3->field_7];
    arg0->field_CC.field_18 = collData->ptr_C[temp_a3->field_6];

    arg0->field_CC.field_C.s_field_0.field_0 = temp_a3->field_8;

    if ((arg0->field_CC.field_C.s_field_0.field_0) != 0xFF)
    {
        temp_a0                 = &collData->ptr_10[arg0->field_CC.field_C.s_field_0.field_0];
        arg0->field_CC.field_E  = temp_a0->field_6_8;
        arg0->field_CC.field_10 = temp_a0->field_6_5;

        if (arg0->field_4.field_4 && (temp_a0->field_6_5 == 1 || temp_a0->field_6_0 == 12))
        {
            arg0->field_CC.field_12.vy -= Q12(1.0f);
            arg0->field_CC.field_18.vy -= Q12(1.0f);
        }
    }

    arg0->field_CC.field_C.s_field_0.field_1 = temp_a3->field_9;

    if ((arg0->field_CC.field_C.s_field_0.field_1) != 0xFF)
    {
        temp_a0                 = &collData->ptr_10[arg0->field_CC.field_C.s_field_0.field_1];
        arg0->field_CC.field_F  = temp_a0->field_6_8;
        arg0->field_CC.field_11 = temp_a0->field_6_5;

        if (arg0->field_4.field_4 && (temp_a0->field_6_5 == 1 || temp_a0->field_6_0 == 12))
        {
            arg0->field_CC.field_12.vy = Q12(-1.0f);
            arg0->field_CC.field_18.vy = Q12(-1.0f);
        }
    }

    temp_v0 = (temp_a3->field_0_0 & 0xFFFF) + (temp_a3->field_2_0 << 16);
    gte_ldR11R12(temp_v0);
    gte_ldR13R21(temp_v0);
    temp_v0 = (u16)arg0->field_4.field_C.vx + (arg0->field_4.field_C.vz << 16);
    gte_ldvxy0(temp_v0);
    gte_gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&arg0->field_CC.field_20.field_14);
    temp_v0 = ((arg0->field_98.vec_0.vx - arg0->field_CC.field_12.vx) & 0xFFFF) + ((arg0->field_98.vec_0.vz - arg0->field_CC.field_12.vz) << 16);
    gte_ldvxy0(temp_v0);
    gte_gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&arg0->field_CC.field_20.field_0);

    temp_s0                            = arg0->field_CC.field_20.field_0.vx;
    temp_a0_5                          = arg0->field_CC.field_20.field_0.vz;
    arg0->field_CC.field_20.field_4.vx = arg0->field_CC.field_20.field_14.vx + temp_s0;
    arg0->field_CC.field_20.field_4.vz = arg0->field_CC.field_20.field_14.vz + temp_a0_5;

    if (temp_s0 < 0)
    {
        arg0->field_CC.field_20.field_8  = 2;
        arg0->field_CC.field_20.field_C  = SquareRoot0(SQUARE(temp_s0) + SQUARE(temp_a0_5));
        arg0->field_CC.field_20.field_10 = -temp_s0;
    }
    else if (arg0->field_CC.field_6.vz < temp_s0)
    {
        arg0->field_CC.field_20.field_8  = 2;
        arg0->field_CC.field_20.field_C  = SquareRoot0(SQUARE(temp_s0 - arg0->field_CC.field_6.vz) + SQUARE(temp_a0_5));
        arg0->field_CC.field_20.field_10 = temp_s0 - arg0->field_CC.field_6.vz;
    }
    else
    {
        if (temp_a0_5 < 0)
        {
            arg0->field_CC.field_20.field_C = -temp_a0_5;
        }
        else
        {
            arg0->field_CC.field_20.field_C = temp_a0_5;
        }

        arg0->field_CC.field_20.field_8 = 1;
    }

    return true;
}

void func_8006B6E8(s_func_8006CC44* arg0, s_IpdCollisionData_20* arg1) // 0x8006B6E8
{
    s32                 idx;
    s32                 temp_s1;
    s32                 temp_s2;
    s32                 temp_s3;
    s32                 temp_s4;
    s_func_8006CC44_A8* temp_s0;

    temp_s1 = arg0->field_CC.field_C.s_field_0.field_0;
    temp_s2 = arg0->field_CC.field_C.s_field_0.field_1;
    temp_s3 = arg0->field_CC.field_10;
    temp_s4 = arg0->field_CC.field_11;

    if (temp_s1 == 0xFF)
    {
        if (temp_s2 == 0xFF)
        {
            return;
        }

        idx = arg0->field_CC.field_F;
    }
    else
    {
        idx = arg0->field_CC.field_E;
    }

    temp_s0 = &arg0->field_A0.s_0.field_8[idx];
    if (!func_8006B7E0(temp_s0, &arg0->field_CC.field_20))
    {
        return;
    }

    temp_s0->field_0 = arg0->field_CC.field_20.field_8;
    temp_s0->field_4 = arg0->field_CC.field_20.field_C;
    temp_s0->field_2 = arg0->field_CC.field_20.field_10;

    if (arg0->field_CC.field_20.field_0.vz >= 0)
    {
        if (temp_s3 == 1)
        {
            temp_s0->field_1 = NO_VALUE;
        }
        else
        {
            temp_s0->field_1 = temp_s1;
        }
    }
    else
    {
        if (temp_s4 == 1)
        {
            temp_s0->field_1 = NO_VALUE;
        }
        else
        {
            temp_s0->field_1 = temp_s2;
        }
    }
}

bool func_8006B7E0(s_func_8006CC44_A8* arg0, s_func_8006CC44_CC_20* arg1) // 0x8006B7E0
{
if (arg0->field_0 == 0)
    {
        return true;
    }

    switch (arg1->field_8)
    {
        case 0:
            return false;

        case 1:
            switch (arg0->field_0)
            {
                case 1:
                    if (arg1->field_C < arg0->field_4)
                    {
                        return true;
                    }
                    break;

                case 2:
                    if (arg1->field_C < (arg0->field_4 + 6))
                    {
                        return true;
                    }
                    break;
            }
            break;

        case 2:
            switch (arg0->field_0)
            {
                case 1:
                    if (arg1->field_C < arg0->field_4 - 6)
                    {
                        return true;
                    }
                    break;

                case 2:
                    if (arg1->field_C < (arg0->field_4 - 6))
                    {
                        return true;
                    }

                    if (arg1->field_C < (arg0->field_4 + 6) && arg1->field_10 < arg0->field_2)
                    {
                        return true;
                    }
                    break;
            }
    }

    return false;
}

void func_8006B8F8(s_func_8006CC44_CC* arg0) // 0x8006B8F8
{
    s_func_8006CC44_CC_20* ptr;
    s32                    temp_a1;
    s32                    temp_a2;
    s32                    temp_a3;

    temp_a3                    = (u16)arg0->field_12.vx;
    temp_a1                    = (u16)arg0->field_18.vx;
    temp_a2                    = (u16)arg0->field_18.vz;
    arg0->field_18.vx          = temp_a3;
    temp_a3                    = (u16)arg0->field_12.vy;
    arg0->field_12.vy          = arg0->field_18.vy;
    arg0->field_12.vx          = temp_a1;
    arg0->field_6.vx           = -arg0->field_6.vx;
    arg0->field_18.vy          = temp_a3;
    arg0->field_6.vy           = -arg0->field_6.vy;
    temp_a3                    = (u16)arg0->field_12.vz;
    arg0->field_18.vz          = temp_a3;
    temp_a3                    = arg0->field_C.s_field_0.field_0;
    arg0->field_20.field_14.vx = -arg0->field_20.field_14.vx;

    arg0->field_12.vz               = temp_a2;
    arg0->field_C.s_field_0.field_0 = arg0->field_C.s_field_0.field_1;

    ptr = &arg0->field_20;

    arg0->field_C.s_field_0.field_1 = temp_a3;
    temp_a3                         = arg0->field_E;
    arg0->field_20.field_14.vz      = -arg0->field_20.field_14.vz;
    arg0->field_E                   = arg0->field_F;
    arg0->field_F                   = temp_a3;

    ptr->field_0.vz = -ptr->field_0.vz;
    ptr->field_0.vx = (arg0->field_6.vz - ptr->field_0.vx);
    ptr->field_4.vz = -ptr->field_4.vz;
    ptr->field_4.vx = (arg0->field_6.vz - ptr->field_4.vx);
}

void func_8006B9C8(s_func_8006CC44* arg0) // 0x8006B9C8
{
    s32 field_28;

    if (arg0->field_CC.field_C.s_field_0.field_1 == 0xFF && arg0->field_CC.field_20.field_0.vz < 0 &&
        (arg0->field_4.field_2C >= arg0->field_CC.field_12.vy || arg0->field_4.field_2C >= arg0->field_CC.field_18.vy))
    {
        if (arg0->field_0_9 && arg0->field_CC.field_20.field_C < arg0->field_4.field_28)
        {
            func_8006BB50(arg0, 0);
            return;
        }

        field_28 = arg0->field_4.field_28;
        if (arg0->field_0_9 && arg0->field_CC.field_20.field_C < (field_28 + 8))
        {
            func_8006BB50(arg0, 1);
        }

        if (arg0->field_0_8)
        {
            if (!arg0->field_44.field_0.field_0 &&
                (-field_28 < arg0->field_CC.field_20.field_0.vz || -field_28 < arg0->field_CC.field_20.field_4.vz) &&
                (-field_28 < arg0->field_CC.field_20.field_0.vx || -field_28 < arg0->field_CC.field_20.field_4.vx) &&
                (arg0->field_CC.field_20.field_0.vx < (field_28 + arg0->field_CC.field_6.vz) || arg0->field_CC.field_20.field_4.vx < (field_28 + arg0->field_CC.field_6.vz)))
            {
                func_8006BE40(arg0);
            }
        }
    }
}

void func_8006BB50(s_func_8006CC44* arg0, s32 arg1) // 0x8006BB50
{
    q19_12 deltaX;
    q19_12 deltaZ;
    s16    temp2;

    if (func_8006BC34(arg0) < 0)
    {
        return;
    }

    if (arg0->field_CC.field_20.field_0.vx < 0)
    {
        deltaX = arg0->field_98.vec_0.vx - arg0->field_CC.field_12.vx;
        deltaZ = arg0->field_98.vec_0.vz - arg0->field_CC.field_12.vz;
    }
    else if (arg0->field_CC.field_6.vz < arg0->field_CC.field_20.field_0.vx)
    {
        deltaX = arg0->field_98.vec_0.vx - arg0->field_CC.field_18.vx;
        deltaZ = arg0->field_98.vec_0.vz - arg0->field_CC.field_18.vz;
    }
    else
    {
        deltaX = arg0->field_CC.field_6.vy;
        deltaZ = -arg0->field_CC.field_6.vx;
    }

    temp2 = arg0->field_4.field_28 - arg0->field_CC.field_20.field_C;
    func_8006BCC4(&arg0->field_44, (u8*)arg0->field_CC.field_0 + (arg0->field_CC.field_4 + 52), arg1, deltaX, deltaZ, temp2);
}

s32 func_8006BC34(s_func_8006CC44* arg0)
{
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_v0;
    s16 temp_v1;
    u16 temp_a1;
    u16 var_v0;

    temp_v1 = arg0->field_CC.field_20.field_0.vx;
    if (temp_v1 < 0)
    {
        var_v0 = arg0->field_CC.field_12.vy;
    }
    else
    {
        temp_a2 = arg0->field_CC.field_6.vz;
        if (temp_a2 < temp_v1)
        {
            var_v0 = arg0->field_CC.field_18.vy;
        }
        else
        {
            temp_a3 = arg0->field_CC.field_12.vy;
            temp_v0 = arg0->field_CC.field_18.vy;
            temp_a1 = arg0->field_CC.field_12.vy;

            if (temp_a3 == temp_v0)
            {
                var_v0 = temp_a1;
            }
            else
            {
                var_v0 = temp_a1 + ((s32)((temp_v0 - temp_a3) * temp_v1) / temp_a2);
            }
        }
    }

    return arg0->field_4.field_2C - (s16)var_v0;
}

void func_8006BCC4(s_func_8006CC44_44* arg0, s8* arg1, u32 arg2, q3_12 deltaX, q3_12 deltaZ, s16 arg5) // 0x8006BCC4
{
    q7_8 rotX;
    q7_8 rotY;

    rotX = Q12_FRACT(ratan2(deltaZ, deltaX) - FP_ANGLE(89.0f));
    rotY = Q12_FRACT(rotX + FP_ANGLE(178.0f));

    switch (arg2)
    {
        case 0:
            *arg1 += 1;

            func_8006BDDC(&arg0->field_0, rotX, rotY);

            if (arg0->field_6 < arg5)
            {
                arg0->field_6 = arg5;
            }
            break;

        case 1:
            func_8006BDDC(&arg0->field_8, rotX, rotY);

            if (arg0->field_8.field_0 < 9)
            {
                arg0->field_10[arg0->field_8.field_0 - 1] = arg1;
            }
            break;

        case 2:
            *arg1 += 1;

            func_8006BDDC(&arg0->field_30, rotX, rotY);

            if (arg0->field_36 < arg5)
            {
                arg0->field_36 = arg5;
            }
            break;
    }
}

void func_8006BDDC(s_func_8006CC44_44_0* arg0, q3_12 rotX, q3_12 rotY) // 0x8006BDDC
{
    if (arg0->field_0 == 0)
    {
        arg0->field_0 = 1;
        arg0->field_2.vx = rotX;
        arg0->field_2.vy = rotY;
        return;
    }

    arg0->field_0++;
    Vw_ClampAngleRange(&arg0->field_2.vx, &arg0->field_2.vy, rotX, rotY);
}

void func_8006BE40(s_func_8006CC44* arg0) // 0x8006BE40
{
    s32 temp_a3;
    s32 var_a2;
    s32 var_a1;
    u32 var_v1;
    s32 temp;

    var_a1  = 0;
    temp_a3 = -arg0->field_4.field_28;
    var_a2  = 0;

    if (arg0->field_CC.field_20.field_0.vz >= temp_a3)
    {
        if (arg0->field_CC.field_20.field_0.vx >= 0)
        {
            if (arg0->field_CC.field_6.vz >= arg0->field_CC.field_20.field_0.vx)
            {
                var_a2 = arg0->field_CC.field_20.field_0.vx;
                var_v1 = 2;
            }
            else
            {
                var_v1 = 1;
            }
        }
        else
        {
            var_v1 = 0;
        }
    }
    else
    {
        if (arg0->field_CC.field_20.field_14.vz == 0)
        {
            if ((arg0->field_CC.field_20.field_0.vx > 0) && (arg0->field_CC.field_20.field_0.vx < arg0->field_CC.field_6.vz))
            {
                var_a1 = 0;
                var_a2 = arg0->field_CC.field_20.field_0.vx;
            }
        }
        else
        {
            var_a1 = FP_TO(temp_a3 - arg0->field_CC.field_20.field_0.vz, Q12_SHIFT) / arg0->field_CC.field_20.field_14.vz;
            temp   = arg0->field_CC.field_20.field_14.vx * var_a1;
            temp   = FP_FROM(temp, Q12_SHIFT);
            var_a2 = temp + arg0->field_CC.field_20.field_0.vx;
        }

        if (var_a2 < 0)
        {
            var_v1 = 0;
        }
        else if (arg0->field_CC.field_6.vz < var_a2)
        {
            var_v1 = 1;
        }
        else
        {
            var_v1 = 2;
        }
    }

    switch (var_v1)
    {
        case 0:
            func_8006BF88(arg0, &arg0->field_CC.field_12);
            break;

        case 1:
            func_8006BF88(arg0, &arg0->field_CC.field_18);
            break;

        case 2:
            func_8006C0C8(arg0, var_a1, var_a2);
            break;
    }
}

void func_8006BF88(s_func_8006CC44* arg0, SVECTOR3* arg1) // 0x8006BF88
{
    s16 temp_v0;
    s32 temp2;
    s32 temp3;

    temp_v0 = func_8006C248(*(s32*)&arg0->field_4.direction_14, arg0->field_4.field_8,
                            arg1->vx - arg0->field_98.vec_0.vx,
                            arg1->vz - arg0->field_98.vec_0.vz,
                            arg0->field_4.field_28);
    if (temp_v0 != -1 && func_8006C1B8(2, temp_v0, arg0) && arg0->field_4.field_2C > arg1->vy)
    {
        arg0->field_38 = temp_v0;
        arg0->field_34 = 2;
        temp2          = arg0->field_98.vec_0.vx + FP_MULTIPLY(arg0->field_4.field_C.vx, temp_v0, Q12_SHIFT);
        arg0->field_3A = (arg0->field_4.field_8 * temp_v0) >> 8;
        arg0->field_40 = (u8*)arg0->field_CC.field_0 + (arg0->field_CC.field_4 + 52);

        arg0->field_3C = temp2 - arg1->vx;
        temp3          = arg0->field_98.vec_0.vz + FP_MULTIPLY(arg0->field_4.field_C.vz, temp_v0, Q12_SHIFT);
        arg0->field_3E = temp3 - arg1->vz;
    }
}

void func_8006C0C8(s_func_8006CC44* arg0, s16 arg1, s16 arg2) // 0x8006C0C8
{
    s32 temp;

    if (!func_8006C1B8(1, arg1, arg0) || arg0->field_CC.field_20.field_14.vz < 0)
    {
        return;
    }

    temp = ((arg0->field_CC.field_18.vy - arg0->field_CC.field_12.vy) * arg2) / arg0->field_CC.field_6.vz;

    if (temp + arg0->field_CC.field_12.vy < arg0->field_4.field_2C)
    {
        arg0->field_40 = (u8*)arg0->field_CC.field_0 + (arg0->field_CC.field_4 + 52);
        arg0->field_34 = 1;
        arg0->field_38 = arg1;
        arg0->field_3A = (arg0->field_4.field_8 * arg1) >> 8;
        arg0->field_3C = arg0->field_CC.field_6.vy;
        arg0->field_3E = -arg0->field_CC.field_6.vx;
    }
}

bool func_8006C1B8(u32 arg0, s16 arg1, s_func_8006CC44* arg2) // 0x8006C1B8
{
    s32 var;

    var = (arg2->field_4.field_8 * arg1) >> 8;
    switch (arg0)
    {
        default:
        case 0:
            return false;

        case 2:
            if (arg2->field_34 != 1)
            {
                if (arg2->field_34 == 0)
                {
                   return true;
                }
                
                break;
            }

            var += 96;
            break;

        case 1:
            if (arg2->field_34 != arg0)
            {
                if (arg2->field_34 != 0)
                {
                    if (arg2->field_34 == 2)
                    {
                        var -= 96;
                    }
                    
                    break;
                }

                return true;
            }
            break;
    }

    return var < arg2->field_3A;
}

s16 func_8006C248(s32 arg0, s16 arg1, q3_12 deltaX, q3_12 deltaZ, s16 arg4) // 0x8006C248
{
    DVECTOR sp10;
    s16     temp_v0;
    s16     var_v1;
    s16     temp_lo;

    gte_ldR11R12(arg0);
    gte_ldR13R21(arg0);
    gte_ldvxy0((deltaX & 0xFFFF) + (deltaZ << 16));
    gte_gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&sp10.vx);

    if (sp10.vx < 0)
    {
        var_v1 = SquareRoot0(SQUARE(sp10.vx) + SQUARE(sp10.vy));
    }
    else if (arg1 < sp10.vx)
    {
        temp_v0 = sp10.vx - arg1;
        var_v1  = SquareRoot0(SQUARE(temp_v0) + SQUARE(sp10.vy));
    }
    else
    {
        var_v1 = ABS(sp10.vy);
    }

    if (arg1 == 0)
    {
        temp_lo = -1;
        if (var_v1 >= arg4)
        {
            return temp_lo;
        }
        else
        {
            return 0;
        }
    }

    if (var_v1 >= arg4)
    {
        return -1;
    }

    temp_lo = FP_TO(sp10.vx - SquareRoot0(SQUARE(arg4) - SQUARE(sp10.vy)), Q12_SHIFT) / arg1;
    temp_lo = CLAMP(temp_lo, Q12(0.0f), Q12(1.0f));

    return temp_lo;
}

bool func_8006C3D4(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s32 idx) // 0x8006C3D4
{
    s_IpdCollisionData_18* temp_a1;

    arg0->field_CC.field_0 = collData;
    arg0->field_CC.field_4 = idx;
    temp_a1        = &collData->ptr_18[idx - collData->field_8_16];

    if (!((arg0->field_2 >> temp_a1->field_0_8) & (1 << 0)))
    {
        return false;
    }

    arg0->field_CC.field_5         = temp_a1->field_0_5;
    arg0->field_CC.field_6.vx      = temp_a1->vec_2.vx;
    arg0->field_CC.field_6.vy      = temp_a1->vec_2.vy;
    arg0->field_CC.field_6.vz      = temp_a1->vec_2.vz;
    arg0->field_CC.field_C.field_0 = temp_a1->field_8;
    return true;
}

void func_8006C45C(s_func_8006CC44* arg0) // 0x8006C45C
{
    q3_12 distMax;
    q3_12 dist;
    s16   var_s2;
    s32   bound;
    s32   deltaX;
    s32   deltaZ;
    s32   temp_v1;
    s32   temp;
    s32   temp2;

    distMax = arg0->field_4.field_28 + arg0->field_CC.field_C.field_0;
    bound   = distMax + 8;
    temp_v1 = arg0->field_CC.field_6.vx - bound;

    if (arg0->field_98.vec_0.vx < temp_v1 &&
        arg0->field_9C.vec_0.vx < temp_v1)
    {
        return;
    }

    if ((arg0->field_CC.field_6.vx + bound) < arg0->field_98.vec_0.vx &&
        (arg0->field_CC.field_6.vx + bound) < arg0->field_9C.vec_0.vx)
    {
        return;
    }

    if (arg0->field_98.vec_0.vz < (arg0->field_CC.field_6.vz - bound) &&
        arg0->field_9C.vec_0.vz < (arg0->field_CC.field_6.vz - bound))
    {
        return;
    }

    if ((arg0->field_CC.field_6.vz + bound) < arg0->field_98.vec_0.vz &&
        (arg0->field_CC.field_6.vz + bound) < arg0->field_9C.vec_0.vz)
    {
        return;
    }

    deltaX = arg0->field_98.vec_0.vx - arg0->field_CC.field_6.vx;
    deltaZ = arg0->field_98.vec_0.vz - arg0->field_CC.field_6.vz;
    dist   = SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ));

    if (dist < arg0->field_CC.field_C.field_0 && arg0->field_CC.field_5 != 1 &&
        (arg0->field_C8 == 0xFF || arg0->field_CC.field_6.vy < arg0->field_CA))
    {
        arg0->field_C8 = arg0->field_CC.field_4;
        arg0->field_CA = arg0->field_CC.field_6.vy;
    }

    if (!arg0->field_0_8 && !arg0->field_0_9 || dist < arg0->field_CC.field_C.field_0)
    {
        return;
    }

    if (dist < distMax && arg0->field_0_9)
    {
        func_8006C794(arg0, 0, dist);
        return;
    }

    if (dist < (distMax + 8) && arg0->field_0_9)
    {
        func_8006C794(arg0, 1, dist);
    }

    if (!arg0->field_0_8 || arg0->field_44.field_0.field_0)
    {
        return;
    }

    var_s2 = func_8006C248(*(s32*)&arg0->field_4.direction_14, arg0->field_4.field_8,
                           arg0->field_CC.field_6.vx - arg0->field_98.vec_0.vx,
                           arg0->field_CC.field_6.vz - arg0->field_98.vec_0.vz,
                           distMax);

    if (var_s2 == -1)
    {
        return;
    }

    if (var_s2 < 0)
    {
        var_s2 = 0;
    }

    if (func_8006C1B8(1, var_s2, arg0) && arg0->field_4.field_2C >= arg0->field_CC.field_6.vy)
    {
        arg0->field_38 = var_s2;
        arg0->field_34 = 1;
        temp           = arg0->field_98.vec_0.vx + FP_MULTIPLY(arg0->field_4.field_C.vx, var_s2, Q12_SHIFT);
        arg0->field_3A = (arg0->field_4.field_8 * var_s2) >> 8;
        arg0->field_40 = (u8*)arg0->field_CC.field_0 + (arg0->field_CC.field_4 + 52);
        arg0->field_3C = temp - arg0->field_CC.field_6.vx;
        temp2          = arg0->field_98.vec_0.vz + FP_MULTIPLY(arg0->field_4.field_C.vz, var_s2, Q12_SHIFT);
        arg0->field_3E = temp2 - arg0->field_CC.field_6.vz;
    }
}

void func_8006C794(s_func_8006CC44* arg0, s32 arg1, s32 dist) // 0x8006C794
{
    if (arg0->field_4.field_2C >= (arg0->field_CC.field_6.vy + (dist - arg0->field_CC.field_C.field_0)))
    {
        func_8006BCC4(&arg0->field_44,
                      (u8*)arg0->field_CC.field_0 + (arg0->field_CC.field_4 + 52),
                      arg1,
                      arg0->field_98.vec_0.vx - arg0->field_CC.field_6.vx,
                      arg0->field_98.vec_0.vz - arg0->field_CC.field_6.vz,
                      (arg0->field_4.field_28 + arg0->field_CC.field_C.field_0) - dist);
    }
}

void func_8006C838(s_func_8006CC44* arg0, s_IpdCollisionData* collData) // 0x8006C838
{
    s32                    var_a0;
    s_func_8006CC44_A8*    curUnk;
    s_IpdCollisionData_10* temp_a1;
    s_IpdCollisionData_18* temp_a0;

    if (!arg0->field_A0.s_0.field_4)
    {
        return;
    }

    if (arg0->field_C8 != 0xFF)
    {
        if (arg0->field_CA < arg0->field_7C)
        {
            temp_a0        = &collData->ptr_18[arg0->field_C8 - collData->field_8_16];
            arg0->field_7C = arg0->field_CA;
            arg0->field_80 = arg0->field_98.vec_0.vx + collData->positionX_0;
            arg0->field_84 = arg0->field_98.vec_0.vz + collData->positionZ_4;
            arg0->field_88 = 0;
            arg0->field_8C = 0;
            arg0->field_90 = temp_a0->field_0_5;
            arg0->field_94 = temp_a0->field_0_0;
        }
    }

    for (curUnk = &arg0->field_A0.s_0.field_8[0]; curUnk < &arg0->field_A0.s_0.field_8[4]; curUnk++)
    {
        if (curUnk->field_1 != 0xFF)
        {
            temp_a1 = &collData->ptr_10[curUnk->field_1];

            var_a0 = temp_a1->field_2;

            if (temp_a1->field_8 != 0)
            {
                var_a0 += FP_FROM(temp_a1->field_8 * (arg0->field_98.vec_0.vx - temp_a1->field_0), Q12_SHIFT);
            }

            if (temp_a1->field_A != 0)
            {
                var_a0 += FP_FROM(temp_a1->field_A * (arg0->field_98.vec_0.vz - temp_a1->field_4), Q12_SHIFT);
            }

            if (var_a0 < arg0->field_7C)
            {
                arg0->field_7C = var_a0;
                arg0->field_80 = arg0->field_98.vec_0.vx + collData->positionX_0;
                arg0->field_84 = arg0->field_98.vec_0.vz + collData->positionZ_4;
                arg0->field_88 = temp_a1->field_8;
                arg0->field_8C = temp_a1->field_A;
                arg0->field_90 = temp_a1->field_6_5;
                arg0->field_94 = temp_a1->field_6_0;
            }
        }
    }
}

void func_8006CA18(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s_func_8006CA18* arg2) // 0x8006CA18
{
    s32                    startIdx;
    s32                    endIdx;
    s32                    var_a2;
    u8*                    curUnk;
    s_IpdCollisionData_10* ptr;

    startIdx = arg2->field_2;
    endIdx   = arg2->field_6;

    if (startIdx == endIdx)
    {
        return;
    }

    for (curUnk = &collData->ptr_2C[startIdx]; curUnk < &collData->ptr_2C[endIdx]; curUnk++)
    {
        ptr = &collData->ptr_10[*curUnk];

        if (((arg0->field_2 >> ptr->field_6_11) & (1 << 0)) && ptr->field_6_5 != 1)
        {
            var_a2 = ptr->field_2;

            if (ptr->field_8 != 0)
            {
                var_a2 += FP_FROM(ptr->field_8 * (arg0->field_98.vec_0.vx - ptr->field_0), Q12_SHIFT);
            }

            if (ptr->field_A != 0)
            {
                var_a2 += FP_FROM(ptr->field_A * (arg0->field_98.vec_0.vz - ptr->field_4), Q12_SHIFT);
            }

            if (var_a2 < arg0->field_7C)
            {
                arg0->field_7C = var_a2;
                arg0->field_80 = arg0->field_98.vec_0.vx + collData->positionX_0;
                arg0->field_84 = arg0->field_98.vec_0.vz + collData->positionZ_4;
                arg0->field_88 = ptr->field_8;
                arg0->field_8C = ptr->field_A;
                arg0->field_90 = ptr->field_6_5;
                arg0->field_94 = ptr->field_6_0;
            }
        }
    }
}

s16 func_8006CB90(s_func_8006CC44* arg0) // 0x8006CB90
{
    s32 temp_v0;

    if (arg0->field_7C == 0x1E00)
    {
        return Q12(1.0f);
    }

    temp_v0 = func_8006CC44(arg0->field_4.field_20, arg0->field_4.field_24, arg0);
    if ((arg0->field_4.field_2C + arg0->field_4.field_C.vy) < temp_v0 ||
        temp_v0 == arg0->field_7C)
    {
        return Q12(1.0f);
    }

    return FP_TO(arg0->field_4.field_8, Q12_SHIFT) / SquareRoot0(SQUARE(arg0->field_4.field_8) +
                                                                 SQUARE(temp_v0 - arg0->field_4.field_2C));
}

s32 func_8006CC44(q23_8 x, q23_8 z, s_func_8006CC44* arg2) // 0x8006CC44
{
    if (arg2->field_94 != 12)
    {
        return FP_MULTIPLY(arg2->field_88, x - arg2->field_80, Q12_SHIFT) +
               FP_MULTIPLY(arg2->field_8C, z - arg2->field_84, Q12_SHIFT) +
               arg2->field_7C;
    }

    return Q12(0.5f);
}

void func_8006CC9C(s_func_8006CC44* arg0) // 0x8006CC9C
{
    q19_12 deltaX;
    q19_12 deltaZ;
    s32    temp_v0;
    s32    temp_s4;
    s32    temp;
    s32    temp2;
    s32    temp3;
    s32    temp4;
    s32    temp5;

    if (arg0->field_A0.s_1.field_6 < 2 || *arg0->field_A0.s_1.field_8 != 0)
    {
        return;
    }

    if (arg0->field_98.field_0 + (arg0->field_A0.s_1.field_4 + arg0->field_4.field_8) < arg0->field_4.positionX_18 ||
        arg0->field_4.field_20 < arg0->field_98.field_0 - (arg0->field_A0.s_1.field_4 + arg0->field_4.field_8))
    {
        return;
    }

    if (arg0->field_9C.field_0 + (arg0->field_A0.s_1.field_4 + arg0->field_4.field_8) < arg0->field_4.positionZ_1C ||
        arg0->field_4.field_24 < arg0->field_9C.field_0 - (arg0->field_A0.s_1.field_4 + arg0->field_4.field_8) ||
        arg0->field_4.field_2A > arg0->field_A0.s_1.field_2)
    {
        return;
    }

    deltaX = (arg0->field_4.positionX_18 - arg0->field_98.field_0);

    if (arg0->field_4.field_2C < arg0->field_A0.s_1.field_0)
    {
        return;
    }

    deltaZ = arg0->field_4.positionZ_1C - arg0->field_9C.field_0;
    temp_s4 = SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ));

    temp_v0 = func_8006C248(*(s32*)&arg0->field_4.direction_14, arg0->field_4.field_8,
                            arg0->field_98.field_0 - arg0->field_4.positionX_18,
                            arg0->field_9C.field_0 - arg0->field_4.positionZ_1C,
                            arg0->field_A0.s_1.field_4);
    if (temp_v0 == NO_VALUE)
    {
        return;
    }

    if (temp_v0 == 0)
    {
        if (arg0->field_0_9)
        {
            temp3 = arg0->field_A0.s_1.field_4 - temp_s4;
            func_8006BCC4(&arg0->field_44, arg0->field_A0.s_1.field_8, 2, deltaX, deltaZ, temp3);
        }
    }
    else if (arg0->field_0_8 && arg0->field_44.field_0.field_0 == 0 && func_8006C1B8(1, temp_v0, arg0))
    {
        temp2 = (arg0->field_4.positionZ_1C - arg0->field_9C.field_0);
        temp5 = FP_MULTIPLY(temp_v0, arg0->field_4.field_C.vz, Q12_SHIFT);

        arg0->field_40 = arg0->field_A0.s_1.field_8;
        arg0->field_38 = temp_v0;

        arg0->field_34 = 1;

        temp  = (arg0->field_4.positionX_18 - arg0->field_98.field_0);
        temp4 = FP_MULTIPLY(temp_v0, arg0->field_4.field_C.vx, Q12_SHIFT);

        arg0->field_3A = (arg0->field_4.field_8 * temp_v0) >> 8; // TODO: Conversion to Q4?
        arg0->field_3C = temp + temp4;
        arg0->field_3E = temp2 + temp5;
    }
}

void func_8006CF18(s_func_8006CC44* arg0, s_func_8006CF18* arg1, s32 idx) // 0x8006CF18
{
    s32              var_a1;
    s_func_8006CF18* curArg1;

    for (curArg1 = arg1; curArg1 < &arg1[idx]; curArg1++)
    {
        var_a1 = (curArg1->field_10 >> 4) + arg0->field_4.field_28;
        if (curArg1->field_12 < (u32)arg0->field_4.field_0)
        {
            var_a1 -= 15;
        }

        arg0->field_98.field_0 = curArg1->position_0.vx >> 4;
        arg0->field_9C.field_0 = curArg1->position_0.vz >> 4;

        arg0->field_A0.s_1.field_0 = (curArg1->field_E + curArg1->position_0.vy) >> 4;
        arg0->field_A0.s_1.field_2 = (curArg1->field_C + curArg1->position_0.vy) >> 4;
        arg0->field_A0.s_1.field_4 = var_a1;
        arg0->field_A0.s_1.field_6 = curArg1->field_12;
        arg0->field_A0.s_1.field_8 = &curArg1->field_13;

        if (arg0->field_0_0 == 0)
        {
            curArg1->field_13 = 0;
        }

        func_8006CC9C(arg0);
    }
}

void func_8006D01C(VECTOR3* arg0, VECTOR3* arg1, s16 arg2, s_func_8006CC44* arg3) // 0x8006D01C
{
    VECTOR3 sp10;
    s32     temp_s0;
    s32     temp_s1;
    s32     temp_a0;
    s32     temp_v0;

    sp10.vx = FP_MULTIPLY(arg1->vx, arg2, Q12_SHIFT);
    sp10.vz = FP_MULTIPLY(arg1->vz, arg2, Q12_SHIFT);

    if (arg3->field_44.field_0.field_0 || arg3->field_44.field_30.field_0)
    {
        arg0->vx = 0;
        arg0->vz = 0;
        *arg1    = sp10;
        func_8006D2B4(arg1, &arg3->field_44);
        return;
    }

    if (!arg3->field_34)
    {
        *arg0    = sp10;
        arg1->vz = 0;
        arg1->vx = 0;
        return;
    }

    if (arg2 < arg3->field_38)
    {
        arg3->field_34 = 0;
        *arg0          = sp10;
        arg1->vz       = 0;
        arg1->vx       = 0;
        return;
    }

    arg0->vx = FP_MULTIPLY(arg1->vx, arg3->field_38, Q12_SHIFT);
    arg0->vz = FP_MULTIPLY(arg1->vz, arg3->field_38, Q12_SHIFT);
    arg1->vx = sp10.vx - arg0->vx;
    arg1->vz = sp10.vz - arg0->vz;

    temp_s0 = arg3->field_3C;
    temp_s1 = arg3->field_3E;
    temp_a0 = SQUARE(temp_s0) + SQUARE(temp_s1);

    if (temp_a0 < 256)
    {
        temp_a0 = SquareRoot0(temp_a0 * 256);
        temp_s0 = (temp_s0 << 16) / temp_a0;
        temp_s1 = (temp_s1 << 16) / temp_a0;
    }
    else
    {
        temp_a0 = SquareRoot0(temp_a0);
        temp_s0 = (temp_s0 << 12) / temp_a0; // `Q12_SHIFT`?
        temp_s1 = (temp_s1 << 12) / temp_a0;
    }

    temp_v0  = FP_FROM((arg1->vx * temp_s1) + (arg1->vz * -temp_s0), Q12_SHIFT);
    arg1->vx = FP_MULTIPLY(temp_v0, temp_s1, Q12_SHIFT);
    arg1->vz = FP_MULTIPLY(temp_v0, -temp_s0, Q12_SHIFT);

    if (temp_s0 > Q12(1.0f / 3.0f))
    {
        arg0->vx += Q12(0.004f);
    }
    else if (temp_s0 < Q12(-1.0f / 3.0f))
    {
        arg0->vx -= Q12(0.004f);
    }

    if (temp_s1 > Q12(1.0f / 3.0f))
    {
        arg0->vz += Q12(0.004f);
    }
    else if (temp_s1 < Q12(-1.0f / 3.0f))
    {
        arg0->vz -= Q12(0.004f);
    }
}

void func_8006D2B4(VECTOR3* arg0, s_func_8006CC44_44* arg1) // 0x8006D2B4
{
    s16  sp18;
    s16  sp1A;
    s16  sp1C;
    s16  sp1E;
    s16  temp_v0;
    s32  temp_v0_4;
    bool cond;
    bool var_s1;
    s16  var_s1_2;
    s32  var_v1;
    s16  var_v1_2;
    s16  var_a0;
    s16  diff_a0;
    s16  diff_v1;

    if (arg1->field_30.field_0 != 0)
    {
        var_s1 = false;
        if (arg1->field_0.field_0 != 0)
        {
            sp18 = arg1->field_0.field_2.vx;
            sp1A = arg1->field_0.field_2.vy;
            if (arg1->field_8.field_0 != 0)
            {
                Vw_ClampAngleRange(&sp18, &sp1A, arg1->field_8.field_2.vx, arg1->field_8.field_2.vy);
            }
        }
        else if (arg1->field_8.field_0 != 0)
        {
            sp18 = arg1->field_8.field_2.vx;
            sp1A = arg1->field_8.field_2.vy;
        }
        else
        {
            var_s1 = true;
        }

        if (var_s1)
        {
            cond = true;
        }
        else
        {
            temp_v0  = ratan2(arg0->vz, arg0->vx);
            var_s1_2 = 0x400;
            diff_a0  = ((sp1A - (temp_v0 - var_s1_2)) << 20) >> 20;
            diff_v1  = ((sp18 - (temp_v0 + var_s1_2)) << 20) >> 20;
            if (diff_a0 < 0 && diff_v1 >= 1)
            {
                cond = false;
            }
            else
            {
                cond = true;
            }
        }

        if (cond)
        {
            if (arg1->field_0.field_0 == 0)
            {
                arg1->field_0 = arg1->field_30;
                arg1->field_6 = arg1->field_36;
            }
            else
            {
                arg1->field_0.field_0 += arg1->field_30.field_0;

                Vw_ClampAngleRange(&arg1->field_0.field_2.vx, &arg1->field_0.field_2.vy, arg1->field_30.field_2.vx, arg1->field_30.field_2.vy);

                var_a0 = arg1->field_6;

                if (arg1->field_6 < arg1->field_36)
                {
                    var_a0 = arg1->field_36;
                }

                arg1->field_6 = var_a0;
            }
        }

        if (arg1->field_8.field_0 != 0)
        {
            if (arg1->field_0.field_0 == 0)
            {
                arg1->field_0 = arg1->field_8;
                arg1->field_6 = 0;
            }
            else
            {
                arg1->field_0.field_0 += arg1->field_8.field_0;
                Vw_ClampAngleRange(&arg1->field_0.field_2.vx, &arg1->field_0.field_2.vy, arg1->field_8.field_2.vx, arg1->field_8.field_2.vy);
            }
        }
    }

    if (arg1->field_0.field_0 != 0)
    {
        if (arg1->field_0.field_2.vx == arg1->field_0.field_2.vy)
        {
            arg0->vx = 0;
            arg0->vz = 0;
            return;
        }

        var_s1_2 = (arg1->field_0.field_2.vx + arg1->field_0.field_2.vy) >> 1;

        if (arg1->field_0.field_2.vy < arg1->field_0.field_2.vx)
        {
            var_s1_2 = (var_s1_2 + 0x800) & 0xFFF;
        }

        if (arg1->field_8.field_0 == 0)
        {
            sp1C = arg1->field_0.field_2.vx;
            sp1E = arg1->field_0.field_2.vy;
        }
        else
        {
            sp1C = arg1->field_0.field_2.vx;
            sp1E = arg1->field_0.field_2.vy;

            Vw_ClampAngleRange(&sp1C, &sp1E, arg1->field_8.field_2.vx, arg1->field_8.field_2.vy);

            sp1C = sp1C & 0xFFF;
            sp1E = sp1E & 0xFFF;

            if (sp1C == sp1E)
            {
                sp1C = arg1->field_0.field_2.vx;
                sp1E = arg1->field_0.field_2.vy;
            }

            if (sp1C != sp1E)
            {
                var_v1    = ((sp1C - var_s1_2) << 20) >> 20;
                temp_v0_4 = ((sp1E - var_s1_2) << 20) >> 20;

                if (var_v1 >= 0 || temp_v0_4 <= 0)
                {
                    if (ABS(var_v1) < ABS(temp_v0_4))
                    {
                        var_s1_2 = sp1C;
                    }
                    else
                    {
                        var_s1_2 = sp1E;
                    }
                }
            }
        }

        var_v1_2 = MIN(arg1->field_6 + 2, 16) * 16;

        func_8006D600(arg0, var_s1_2, sp1C, sp1E, var_v1_2);
    }
}

void func_8006D600(VECTOR3* pos, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x8006D600
{
    s32 temp_a2;
    s16 temp_s0;
    s16 temp_s3;
    s16 temp;
    s32 temp_s0_2;
    s32 deltaX;
    s32 deltaZ;
    s32 z;
    s32 x;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0_2;
    s32 angle;

    // TODO: Angles here.

    temp_s0 = Q12_FRACT(arg1);
    temp_s3 = Q12_FRACT(arg2);
    temp    = Q12_FRACT(arg3);

    if (arg4 > 0x100)
    {
        arg4 = 0x100;
    }

    x      = FP_MULTIPLY(arg4, Math_Cos(temp_s0), Q12_SHIFT);
    var_s0 = temp;
    z      = FP_MULTIPLY(arg4, Math_Sin(temp_s0), Q12_SHIFT);
    deltaX = pos->vx - x;
    deltaZ = pos->vz - z;
    angle  = Q12_FRACT(ratan2(deltaZ, deltaX));

    if (angle < temp_s3)
    {
        angle += FP_ANGLE(360.0f);
    }

    if (var_s0 < temp_s3)
    {
        var_s0 += FP_ANGLE(360.0f);
    }

    temp_a2 = temp_s3 + FP_ANGLE(360.0f);
    if (var_s0 < angle)
    {
        if (((var_s0 + temp_a2) >> 1) < angle)
        {
            var_s0 = temp_a2;
        }

        temp_s0_2 = Math_Sin(var_s0);
        temp_v0   = Math_Cos(var_s0);
        var_v0_2  = FP_MULTIPLY(deltaX, temp_v0, Q12_SHIFT) + FP_MULTIPLY(deltaZ, temp_s0_2, Q12_SHIFT);

        if (var_v0_2 < 0)
        {
            var_v0_2 = 0;
        }

        pos->vx = x + FP_MULTIPLY(var_v0_2, temp_v0, Q12_SHIFT);
        pos->vz = z + FP_MULTIPLY(var_v0_2, temp_s0_2, Q12_SHIFT);
    }
}

void func_8006D774(s_func_8006CC44* arg0, VECTOR3* arg1, VECTOR3* arg2) // 0x8006D774
{
    SVECTOR sp10; // Types assumed. `SVECTOR3` might also work but there are 8 bytes between `sp10` and `sp18` and `SVECTOR3` is only 6 bytes.
    SVECTOR sp18;

    sp10.vx = Q12_TO_Q8(arg1->vx);
    sp10.vy = Q12_TO_Q8(arg1->vz);
    sp18.vx = Q12_TO_Q8(arg2->vx);
    sp18.vy = Q12_TO_Q8(arg2->vz);

    arg0->field_34 = 0;
    arg0->field_44.field_0.field_0  = 0;
    arg0->field_44.field_6          = 0;
    arg0->field_44.field_8.field_0  = 0;
    arg0->field_44.field_36         = 0;
    arg0->field_44.field_30.field_0 = 0;

    func_8006D7EC(&arg0->field_4, &sp10, &sp18);
}

void func_8006D7EC(s_func_8006ABC0* arg0, SVECTOR* arg1, SVECTOR* arg2) // 0x8006D7EC
{
    s16 angle;
    s32 dist;
    s16 z;

    arg0->field_C.vx = arg2->vx;

    z                = arg2->vy;
    arg0->field_C.vz = arg2->vy;
    dist             = SquareRoot0(SQUARE(arg0->field_C.vx) + SQUARE(z));

    arg0->field_8 = dist;

    if (dist != 0)
    {
        arg0->direction_14.vx = FP_TO(arg0->field_C.vx, Q12_SHIFT) / dist;
        arg0->direction_14.vz = FP_TO(arg0->field_C.vz, Q12_SHIFT) / arg0->field_8;

        angle                 = ratan2(arg0->field_C.vz, arg0->field_C.vx);
        arg0->direction_14.vx = Math_Cos(angle);
        arg0->direction_14.vz = Math_Sin(angle);
    }
    else
    {
        arg0->direction_14.vx = Q12(1.0f);
        arg0->direction_14.vz = Q12(0.0f);
    }

    arg0->positionX_18 = arg0->positionX_18 + arg1->vx;
    arg0->positionZ_1C = arg0->positionZ_1C + arg1->vy;
    arg0->field_20     = arg0->positionX_18 + arg0->field_C.vx;
    arg0->field_24     = arg0->positionZ_1C + arg0->field_C.vz;
}

bool func_8006D90C(s_func_800700F8_2* arg0, VECTOR3* vec1, VECTOR3* vec2) // 0x8006D90C
{
    s32     scratchPrev;
    s32     scratchAddr;
    VECTOR3 vecDelta;

    vecDelta.vx = vec2->vx - vec1->vx;
    vecDelta.vy = vec2->vy - vec1->vy;
    vecDelta.vz = vec2->vz - vec1->vz;

    arg0->field_0 = false;

    if (func_8006DCE0((s32)PSX_SCRATCH, 0, 0, vec1, &vecDelta, 0, 0, NULL, 0))
    {
        scratchPrev   = SetSp((s32)PSX_SCRATCH_ADDR(984));
        scratchAddr   = (s32)PSX_SCRATCH;
        arg0->field_0 = func_8006DEB0(arg0, PSX_SCRATCH_ADDR(0));

        SetSp(scratchPrev);
    }

    if (!arg0->field_0)
    {
        func_8006DAE4(arg0, vec1, &vecDelta, (s16)*(u16*)(&((u8*)scratchAddr)[92]));
    }

    return arg0->field_0;
}

bool func_8006DA08(s_func_800700F8_2* arg0, VECTOR3* vec1, VECTOR3* vec2, s_SubCharacter* chara) // 0x8006DA08
{
    s32              sp28;
    s32              scratchPrev;
    s32              scratchAddr;
    s_SubCharacter** charas;

    charas = func_8006A1A4(&sp28, chara, false);

    arg0->field_0 = false;
    if (func_8006DCE0((s32)PSX_SCRATCH, 0, 0, vec1, vec2, 0, 0, charas, sp28))
    {
        scratchPrev   = SetSp((s32)PSX_SCRATCH_ADDR(0x3D8));
        scratchAddr   = (s32)PSX_SCRATCH;
        arg0->field_0 = func_8006DEB0(arg0, PSX_SCRATCH_ADDR(0));

        SetSp(scratchPrev);
    }

    if (arg0->field_0 == 0)
    {
        func_8006DAE4(arg0, vec1, vec2, (s16)*(u16*)(&((u8*)scratchAddr)[92]));
    }

    return arg0->field_0;
}

void func_8006DAE4(s_func_800700F8_2* arg0, VECTOR3* pos, VECTOR3* offset, s32 arg3) // 0x8006DAE4
{
    arg0->field_0    = 0;
    arg0->field_1    = 0;
    arg0->field_4.vx = pos->vx + offset->vx;
    arg0->field_4.vy = pos->vy + offset->vy;
    arg0->field_4.vz = pos->vz + offset->vz;
    arg0->field_10   = 0;
    arg0->field_14   = arg3 * 16; // Q8 to Q12?
    arg0->field_18   = 0x1E00;
    arg0->field_1C   = 0;
}

static inline void func_8006DB3C_Inline(s_func_800700F8_2* arg0, VECTOR3* pos, VECTOR3* offset, u16* p)
{
    func_8006DAE4(arg0, pos, offset, (short)*p);
}

bool func_8006DB3C(s_func_800700F8_2* arg0, VECTOR3* pos, VECTOR3* offset, s_SubCharacter* chara) // 0x8006DB3C
{
    s32              charaCount;
    s32              stackPtr;
    s32              scratchAddr;
    s_SubCharacter** charas;

    charas       = func_8006A1A4(&charaCount, chara, true);
    arg0->field_0 = false;

    if (func_8006DCE0((s32)PSX_SCRATCH, 1, 0, pos, offset, 0, 0, charas, charaCount))
    {
        stackPtr      = SetSp((s32)PSX_SCRATCH_ADDR(984));
        scratchAddr   = (s32)PSX_SCRATCH;
        arg0->field_0 = func_8006DEB0(arg0, scratchAddr);

        SetSp(stackPtr);
    }

    if (!arg0->field_0)
    {
        func_8006DB3C_Inline(arg0, pos, offset, &((u8*)scratchAddr)[92]);
    }

    return arg0->field_0;
}

bool func_8006DC18(s_func_800700F8_2* arg0, VECTOR3* vec1, VECTOR3* vec2) // 0x8006DC18
{
    s32 scratchPrev;
    s32 scratchAddr;

    arg0->field_0 = false;
    if (func_8006DCE0((s32)PSX_SCRATCH, 1, 76, vec1, vec2, 0, 0, NULL, 0))
    {
        scratchPrev   = SetSp((s32)PSX_SCRATCH_ADDR(0x3D8));
        scratchAddr   = (s32)PSX_SCRATCH;
        arg0->field_0 = func_8006DEB0(arg0, PSX_SCRATCH_ADDR(0));

        SetSp(scratchPrev);
    }

    if (arg0->field_0 == 0)
    {
        func_8006DAE4(arg0, vec1, vec2, (s16) * (u16*)(&((u8*)scratchAddr)[92]));
    }

    return arg0->field_0;
}

bool func_8006DCE0(s_func_8006DCE0* arg0, s32 arg1, s16 arg2, VECTOR3* pos, VECTOR3* offset, s32 arg5, s32 arg6, s_SubCharacter** charas, s32 charaCount)
{
    if (offset->vx == Q12(0.0f) && offset->vz == Q12(0.0f))
    {
        return false;
    }

    arg0->field_0  = arg1;
    arg0->field_4  = D_800C4478.field_0; // Struct could begin some point earlier.
    arg0->field_6  = arg2;
    arg0->field_8  = 0x7FFF;
    arg0->field_20 = 0;

    arg0->field_2C.vx = Q12_TO_Q8(pos->vx);
    arg0->field_2C.vy = Q12_TO_Q8(pos->vy);
    arg0->field_2C.vz = Q12_TO_Q8(pos->vz);

    arg0->field_50.vx = Q12_TO_Q8(offset->vx);
    arg0->field_50.vy = Q12_TO_Q8(offset->vy);
    arg0->field_50.vz = Q12_TO_Q8(offset->vz);

    arg0->field_3C = arg0->field_2C.vx + arg0->field_50.vx;

    // `Q12_TO_Q8`?
    arg0->field_4C = FP_FROM(arg5, Q4_SHIFT);
    arg0->field_4E = FP_FROM(arg6, Q4_SHIFT);

    arg0->field_40 = arg0->field_2C.vy + arg0->field_50.vy;
    arg0->field_44 = arg0->field_2C.vz + arg0->field_50.vz;

    arg0->field_5C = SquareRoot0(SQUARE(arg0->field_50.vx) + SQUARE(arg0->field_50.vz));
    if (arg0->field_5C == 0)
    {
        return false;
    }

    arg0->field_58 = (arg0->field_50.vx << Q12_SHIFT) / arg0->field_5C;
    arg0->field_5A = (arg0->field_50.vz << Q12_SHIFT) / arg0->field_5C;

    if (arg0->field_50.vy < 0)
    {
        arg0->field_5E = arg0->field_2C.vy + arg0->field_4E;
        arg0->field_60 = arg0->field_40 + arg0->field_4E;
    }
    else
    {
        arg0->field_60 = arg0->field_2C.vy + arg0->field_4E;
        arg0->field_5E = arg0->field_40 + arg0->field_4E;
    }

    arg0->characters_64     = charas;
    arg0->characterCount_68 = charaCount;

    return true;
}

bool func_8006DEB0(s_func_800700F8_2* arg0, s_func_8006DCE0* arg1) // 0x8006DEB0
{
    s32                  collDataIdx;
    s32                  temp_lo;
    s_IpdCollisionData*  collData;
    s_SubCharacter**     curChara;
    s_IpdCollisionData** collDataPtrs;
    s_IpdCollisionData** curCollData;
    s_func_8006DCE0_8C*  curUnk;

    // Run through IPD collision data.
    collDataPtrs = func_800425D8(&collDataIdx);
    for (curCollData = collDataPtrs; curCollData < &collDataPtrs[collDataIdx]; curCollData++)
    {
        collData = *curCollData;

        if (collData->field_8_8 || collData->field_8_16 || collData->field_8_24)
        {
            func_8006E0AC(arg1, collData);
            func_80069994(collData);

            for (curUnk = &arg1->field_8C; curUnk < &arg1->field_8C[arg1->field_88]; curUnk++)
            {
                temp_lo = curUnk->field_2 * arg1->field_7C;
                func_8006E53C(arg1, &collData->ptr_20[temp_lo + curUnk->field_0], collData);
            }
        }
    }

    // Run through characters.
    for (curChara = arg1->characters_64; curChara < &arg1->characters_64[arg1->characterCount_68]; curChara++)
    {
        func_8006EE0C(&arg1->field_6C, arg1->field_0, *curChara);
        func_8006EEB8(arg1, *curChara);
    }

    // TODO: `* 16`s are Q8 to Q12?
    if (arg1->field_8 != 0x7FFF)
    {
        arg0->field_4.vx = arg1->field_C * 16;
        arg0->field_4.vy = arg1->field_10 * 16;
        arg0->field_4.vz = arg1->field_14 * 16;
        arg0->field_10   = arg1->field_20;
        arg0->field_14   = arg1->field_8 * 16;
        arg0->field_18   = arg1->field_1C * 16;
        arg0->field_1C   = ratan2(arg1->field_24, arg1->field_26);
        arg0->field_1    = arg1->field_28;
        return true;
    }

    return false;
}

void func_8006E0AC(s_func_8006DCE0* arg0, s_IpdCollisionData* arg1) // 0x8006E0AC
{
    // `arg0` type might be wrong.
    arg0->field_6C.field_0 = arg1->positionX_0;
    arg0->field_6C.field_4 = arg1->positionZ_4;
    arg0->field_6C.field_8 = arg0->field_2C.vx - arg0->field_6C.field_0;
    arg0->field_6C.field_A = arg0->field_2C.vz - arg0->field_6C.field_4;
    arg0->field_6C.field_C = arg0->field_6C.field_8 + arg0->field_50.vx;
    arg0->field_6C.field_E = arg0->field_6C.field_A + arg0->field_50.vz;
    arg0->field_7C = arg1->field_1E;
    arg0->field_80 = arg1->field_1F;
    arg0->field_84 = arg1->field_1C;

    func_8006E150(&arg0->field_6C, ((DVECTOR*)&arg0->field_50)[0], ((DVECTOR*)&arg0->field_50)[1]);
}

void func_8006E150(s_func_8006E490* arg0, DVECTOR arg1, DVECTOR arg2) // 0x8006E150
{
    DVECTOR subroutine_arg4;
    VECTOR  sp18;
    VECTOR  sp28;
    s16     temp_lo;
    s16     temp_lo_2;
    s32     temp_a0_3;
    s32     temp_lo_4;
    s32     temp_t0;
    s32     temp_t1;
    s32     var_a2;
    s32     var_a3;
    u32     flags;

    flags = 0;
    arg0->field_1C = 0;

    if (arg0->field_8.vx < 0 && arg0->field_C < 0 &&
        arg0->field_8.vy < 0 && arg0->field_E < 0)
    {
        return;
    }

    temp_lo   = arg0->field_10 * arg0->field_18;
    temp_lo_2 = arg0->field_14 * arg0->field_18;

    if (arg0->field_8.vx >= temp_lo && arg0->field_C >= temp_lo &&
        arg0->field_8.vy >= temp_lo_2 && arg0->field_E >= temp_lo_2)
    {
        return;
    }

    subroutine_arg4 = arg0->field_8;

    sp18.vz  = 0;
    sp18.pad = 0;

    sp18.vx = Q12(arg0->field_10);
    sp18.vy = Q12(arg0->field_14);

    if (arg1.vx < 0)
    {
        flags             |= 1 << 0;
        subroutine_arg4.vx = -subroutine_arg4.vx;

        arg1.vx = -arg1.vx;
        sp18.vz = -sp18.vx;
        sp18.vx = 0;
    }

    if (arg2.vx < 0)
    {
        flags             |= 1 << 1;
        subroutine_arg4.vy = -subroutine_arg4.vy;
        arg2.vx            = -arg2.vx;
        sp18.pad           = -sp18.vy;
        sp18.vy            = 0;
    }

    if (arg1.vx < arg2.vx)
    {
        flags |= 1 << 2;

        temp_a0_3          = subroutine_arg4.vx;
        subroutine_arg4.vx = subroutine_arg4.vy;
        subroutine_arg4.vy = temp_a0_3;

        temp_a0_3 = arg1.vx;
        arg1.vx   = arg2.vx;
        arg2.vx   = temp_a0_3;

        temp_a0_3 = sp18.vz;
        sp18.vz   = sp18.pad;
        sp18.pad  = temp_a0_3;
        temp_a0_3 = sp18.vx;
        sp18.vx   = sp18.vy;
        sp18.vy   = temp_a0_3;
    }

    if (subroutine_arg4.vx + arg1.vx < FP_MULTIPLY(arg0->field_18, sp18.vx, Q12_SHIFT))
    {
        sp18.vx = Q12(subroutine_arg4.vx + arg1.vx) / arg0->field_18;
    }

    sp28.vx = Q12(subroutine_arg4.vx) / arg0->field_18;
    sp28.vy = Q12(subroutine_arg4.vy) / arg0->field_18;
    sp28.vz = Q12(1.0f);

    sp28.pad  = Q12(arg2.vx) / arg1.vx;
    temp_lo_4 = FP_MULTIPLY(sp28.pad, Q12_FRACT(sp28.vx), Q12_SHIFT);

    if (FP_FROM(sp18.vx, Q12_SHIFT) < FP_FROM(sp28.vx, Q12_SHIFT))
    {
        return;
    }

    do
    {
        func_8006E490(arg0, flags, sp28.vx, sp28.vy);

        temp_t0 = sp28.vy;
        temp_t1 = sp28.vx;
        var_a3  = temp_t0 + sp28.pad;
        var_a2  = temp_t1 + Q12(1.0f);

        sp28.vy = var_a3;
        sp28.vx = var_a2;

        if (FP_FROM(temp_t0, Q12_SHIFT) < FP_FROM(var_a3, Q12_SHIFT))
        {
            if (Q12_FRACT(var_a3) < temp_lo_4)
            {
                func_8006E490(arg0, flags, var_a2, temp_t0);
            }
            else
            {
                func_8006E490(arg0, flags, temp_t1, var_a3);
            }
        }
    }
    while (arg0->field_1C < 20 && FP_FROM(sp28.vx, Q12_SHIFT) <= FP_FROM(sp18.vx, Q12_SHIFT));
}

void func_8006E490(s_func_8006E490* arg0, u32 flags, q19_12 posX, q19_12 posZ) // 0x8006E490
{
    q19_12 tempPosX;

    // TODO: `func_8006E150` also uses these flags. What subsystem are they for?
    // Flag 0: Invert X.
    // Flag 1: Invert Z.
    // Flag 2: Swap XZ.

    if (flags & (1 << 2))
    {
        tempPosX = posX;
        posX     = posZ;
        posZ     = tempPosX;
    }

    if (flags & (1 << 1))
    {
        posZ = -posZ;
    }

    if (flags & (1 << 0))
    {
        posX = -posX;
    }

    posX = FP_FROM(posX, Q12_SHIFT);
    posZ = FP_FROM(posZ, Q12_SHIFT);
    if (posX >= 0 && posX < arg0->field_10 &&
        posZ >= 0 && posZ < arg0->field_14)
    {
        arg0->field_20[arg0->field_1C].field_0 = posX;
        arg0->field_20[arg0->field_1C].field_2 = posZ;
        arg0->field_1C++;
    }
}

void func_8006E53C(s_func_8006DCE0* arg0, s_IpdCollisionData_20* arg1, s_IpdCollisionData* ipdColl) // 0x8006E53C
{
    s32                    i;
    s32                    temp_v0;
    s32                    temp_v0_2;
    bool                   cond0;
    bool                   cond1;
    bool                   cond2;
    s_IpdCollisionData_18* temp_a1_2;
    u8                     temp_a0;
    s32                    temp_a0_3;
    s32                    temp_a2;
    s32                    idx;
    s_IpdCollisionData_14* temp_a1;

    for (i = arg1[0].field_0; i < arg1[1].field_0; i++)
    {
        idx = ipdColl->ptr_28[i];
        temp_a0 = ipdColl->field_30;

        if (temp_a0 >= ipdColl->field_34[idx])
        {
            ipdColl->field_34[idx] = temp_a0 + 1;

            if (idx < ipdColl->field_8_16)
            {
                temp_a1 = &ipdColl->ptr_14[idx];

                temp_v0 = (u16)arg0->field_4 >> (temp_a1->field_0_14 * 4 | temp_a1->field_2_14);

                if (temp_v0 & (1 << 0))
                {
                    temp_a0_3 = temp_a1->field_8;
                    temp_a2   = temp_a1->field_9;

                    cond0 = temp_a0_3 != 0xFF && temp_a2 != 0xFF;

                    if (arg0->field_0 == 1)
                    {
                        if (cond0)
                        {
                            continue;
                        }
                    }
                    else
                    {
                        cond1 = false;
                        cond2 = false;

                        if (temp_a0_3 == 0xFF || ipdColl->ptr_10[temp_a0_3].field_6_0 == 0 ||
                            ipdColl->ptr_10[temp_a0_3].field_6_0 == 12)
                        {
                            cond1 = true;
                        }

                        if (temp_a2 == 0xFF || ipdColl->ptr_10[temp_a2].field_6_0 == 0 ||
                            ipdColl->ptr_10[temp_a2].field_6_0 == 12)
                        {
                            cond2 = true;
                        }

                        if (cond1 && cond2)
                        {
                            continue;
                        }
                    }

                    func_8006E78C(arg0, temp_a1, ipdColl->ptr_C, ipdColl->ptr_10, cond0);
                }
            }
            else
            {
                temp_a1_2 = &ipdColl->ptr_18[idx - ipdColl->field_8_16];
                temp_v0_2 = (u16)arg0->field_4 >> temp_a1_2->field_0_8;

                if ((temp_v0_2 & (1 << 0)) &&
                    (arg0->field_0 == 1 || (temp_a1_2->field_0_0 && temp_a1_2->field_0_0 != 12)) &&
                    temp_a1_2->field_8 >= arg0->field_6)
                {
                    func_8006EB8C(arg0, temp_a1_2);
                }
            }
        }
    }
}

void func_8006E78C(s_func_8006DCE0* arg0, s_IpdCollisionData_14* arg1, SVECTOR3* arg2, s_IpdCollisionData_10* arg3, s32 arg4) // 0x8006E78C
{
    SVECTOR sp0;
    SVECTOR sp8;

    SVECTOR3  sp10;
    s32       var_a3;
    s32       var_a1;
    s32       var_a2;
    s32       var_t1;
    s32       var_t7;
    SVECTOR3* temp_t1;
    SVECTOR3* temp_t2;
    s32       temp_v1;
    s32       var_v1;

    var_t7  = 0;
    temp_t1 = &arg2[arg1->field_7];
    temp_t2 = &arg2[arg1->field_6];
    if (arg0->field_5E >= temp_t1->vy || arg0->field_5E >= temp_t2->vy)
    {
        if (arg1->field_8 != 0xFF)
        {
            var_t7 = arg3[arg1->field_8].field_6_0;
        }
        if (arg1->field_9 != 0xFF)
        {
            var_t7 = arg3[arg1->field_9].field_6_0;
        }

        temp_v1 = arg0->field_58 + (arg0->field_5A << 16);
        gte_ldR11R12(temp_v1);
        gte_ldR13R21(temp_v1);
        gte_ldvxy0(((temp_t1->vx - arg0->field_6C.field_8) & 0xFFFF) + ((temp_t1->vz - arg0->field_6C.field_A) << 16));
        gte_gte_ldvz0();
        gte_rtv0();
        gte_stMAC12(&sp0);

        gte_ldvxy0(((temp_t2->vx - arg0->field_6C.field_8) & 0xFFFF) + ((temp_t2->vz - arg0->field_6C.field_A) << 16));
        gte_gte_ldvz0();
        gte_rtv0();
        gte_stMAC12(&sp8);

        if ((sp0.vy & 0x8000) != (sp8.vy & 0x8000))
        {
            if (arg0->field_0 == 1)
            {
                gte_ldsxy3(0, *(s32*)&sp0.vx, *(s32*)&sp8.vx);
                gte_nclip();

                if (gte_stMAC0() >= 0)
                {
                    if (arg1->field_8 != 0xFF)
                    {
                        return;
                    }
                }
                else
                {
                    if (arg1->field_9 != 0xFF)
                    {
                        return;
                    }
                }
            }

            if (sp0.vy != sp8.vy)
            {
                var_v1 = ((sp0.vy << 0xC) / (sp0.vy - sp8.vy));
                var_a3 = (((sp8.vx - sp0.vx) * var_v1) >> 0xC) + sp0.vx;
                if (var_a3 >= 0 && arg0->field_5C >= var_a3)
                {
                    gte_lddp(var_v1);
                    gte_ldsv3_(temp_t2->vx - temp_t1->vx, temp_t2->vy - temp_t1->vy, temp_t2->vz - temp_t1->vz);
                    gte_gpf12();
                    gte_stsv(&sp10);

                    sp10.vx += temp_t1->vx;
                    sp10.vy += temp_t1->vy;
                    sp10.vz += temp_t1->vz;

                    var_a2 = arg0->field_2C.vy + arg0->field_4E;
                    if (arg0->field_50.vy != 0)
                    {
                        var_a2 += (arg0->field_50.vy * var_a3) / arg0->field_5C;
                    }

                    if (var_a2 >= sp10.vy && var_a3 < arg0->field_8)
                    {
                        var_a1 = arg1->field_2_0;
                        var_t1 = -arg1->field_0_0;
                        if (arg0->field_0 != 1 && arg4 != 0 && (sp8.vy - sp0.vy) > 0)
                        {
                            var_a1 = -var_a1;
                            var_t1 = arg1->field_0_0;
                        }
                        arg0->field_8  = var_a3;
                        arg0->field_C  = (sp10.vx + arg0->field_6C.field_0);
                        arg0->field_10 = (var_a2 - arg0->field_4E);
                        arg0->field_14 = (sp10.vz + arg0->field_6C.field_4);
                        arg0->field_1C = sp10.vy;
                        arg0->field_24 = var_a1;
                        arg0->field_26 = var_t1;
                        arg0->field_20 = 0;
                        arg0->field_28 = var_t7;
                    }
                }
            }
        }
    }
}

void func_8006EB8C(s_func_8006DCE0* arg0, s_IpdCollisionData_18* arg1) // 0x8006EB8C
{
    SVECTOR sp10;
    SVECTOR sp18;
    s16     temp_a1_3;
    s32     temp_v0;
    s16     temp_a1;
    s32     temp_v1;

    temp_a1 = arg1->field_8;
    if (arg0->field_5E <= arg1->vec_2.vy)
    {
        return;
    }

    temp_v1 = arg0->field_58 + (arg0->field_5A << 16);
    gte_ldR11R12(temp_v1);
    gte_ldR13R21(temp_v1);
    gte_ldvxy0(((arg1->vec_2.vx - arg0->field_6C.field_8) & 0xFFFF) + ((arg1->vec_2.vz - arg0->field_6C.field_A) << 16));
    gte_gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&sp10);

    if (-temp_a1 < sp10.vx && sp10.vx < (arg0->field_5C + temp_a1) && -temp_a1 < sp10.vy && sp10.vy < temp_a1)
    {
        temp_v0   = SquareRoot0((temp_a1 * temp_a1) - (sp10.vy * sp10.vy));
        temp_a1_3 = sp10.vx - temp_v0;

        if (temp_a1_3 >= -temp_v0 && arg0->field_5C >= temp_a1_3 && temp_a1_3 < arg0->field_8)
        {
            gte_lddp(((temp_a1_3 << 12) / arg0->field_5C));
            gte_ldsv3_(arg0->field_50.vx, arg0->field_50.vy, arg0->field_50.vz);
            gte_gpf12();
            gte_stsv(&sp18);

            if ((sp18.vy + arg0->field_2C.vy + arg0->field_4E) >= arg1->vec_2.vy)
            {
                arg0->field_8  = temp_a1_3;
                arg0->field_C  = sp18.vx + arg0->field_6C.field_8 + arg0->field_6C.field_0;
                arg0->field_10 = sp18.vy + arg0->field_2C.vy;
                arg0->field_14 = sp18.vz + arg0->field_6C.field_A + arg0->field_6C.field_4;
                arg0->field_1C = arg1->vec_2.vy;
                arg0->field_24 = (sp18.vx + arg0->field_6C.field_8) - arg1->vec_2.vx;
                arg0->field_26 = (sp18.vz + arg0->field_6C.field_A) - arg1->vec_2.vz;
                arg0->field_20 = 0;
                arg0->field_28 = arg1->field_0_0;
            }
        }
    }
}

void func_8006EE0C(s_func_8006DCE0_6C* arg0, s32 arg1, s_SubCharacter* chara) // 0x8006EE0C
{
    q19_12 offsetZ;
    q19_12 offsetX;
    q19_12 unkY;

    if (arg1 == 1)
    {
        arg0->field_C = Q12_TO_Q8(chara->field_D4);
        offsetX       = chara->field_D8.offsetX_4;
        offsetZ       = chara->field_D8.offsetZ_6;
        unkY          = chara->position_18.vy + chara->field_CA;
    }
    else
    {
        arg0->field_C = Q12_TO_Q8(chara->field_D6);
        offsetX       = chara->field_D8.offsetX_0;
        offsetZ       = chara->field_D8.offsetZ_2;
        unkY          = chara->position_18.vy + chara->field_CC;
    }

    arg0->field_A = Q12_TO_Q8(unkY);
    arg0->field_0 = Q12_TO_Q8(chara->position_18.vx + offsetX);
    arg0->field_4 = Q12_TO_Q8(chara->position_18.vz + offsetZ);
    arg0->field_8 = Q12_TO_Q8(chara->position_18.vy + chara->field_C8);
}

void func_8006EEB8(s_func_8006DCE0* arg0, s_SubCharacter* chara) // 0x8006EEB8
{
    VECTOR3 sp18; // Q23.8?
    s32     bound;
    s16     temp_v0;
    s16     temp_v0_2;
    q23_8   x1;
    q23_8   z1;
    q23_8   x0;
    q23_8   z0;
    q19_12  var_v1;

    if (arg0->field_2C.vx <= arg0->field_3C)
    {
        x0 = arg0->field_2C.vx;
        z0 = arg0->field_3C;
    }
    else
    {
        x0 = arg0->field_3C;
        z0 = arg0->field_2C.vx;
    }

    if (arg0->field_2C.vz <= arg0->field_44)
    {
        z1 = arg0->field_2C.vz;
        x1 = arg0->field_44;
    }
    else
    {
        z1 = arg0->field_44;
        x1 = arg0->field_2C.vz;
    }

    bound = arg0->field_6C.field_C;
    if ((arg0->field_6C.field_0 + bound) < x0 || z0 < (arg0->field_6C.field_0 - bound))
    {
        return;
    }

    if ((arg0->field_6C.field_4 + bound) < z1 || x1 < (arg0->field_6C.field_4 - bound) ||
        ((arg0->field_2C.vy + arg0->field_4E) < arg0->field_6C.field_8 && (arg0->field_40 + arg0->field_4E) < arg0->field_6C.field_8) ||
        ((arg0->field_2C.vy + arg0->field_4C) > arg0->field_6C.field_A && arg0->field_6C.field_A < (arg0->field_40 + arg0->field_4C)))
    {
        return;
    }

    temp_v0 = func_8006C248(*(s32*)&arg0->field_58, arg0->field_5C,
                            arg0->field_6C.field_0 - arg0->field_2C.vx,
                            arg0->field_6C.field_4 - arg0->field_2C.vz,
                            bound);
    if (temp_v0 == NO_VALUE)
    {
        return;
    }

    temp_v0_2 = FP_MULTIPLY(arg0->field_5C, temp_v0, Q12_SHIFT);
    if (temp_v0_2 >= arg0->field_8)
    {
        return;
    }

    sp18.vy = arg0->field_2C.vy + (FP_MULTIPLY(arg0->field_50.vy, temp_v0, Q12_SHIFT));
    if (((sp18.vy + arg0->field_4E) < arg0->field_6C.field_8) || (arg0->field_6C.field_A < (sp18.vy + arg0->field_4C)))
    {
        if (arg0->field_50.vy == 0)
        {
            return;
        }

        if ((sp18.vy + arg0->field_4E) < arg0->field_6C.field_8)
        {
            var_v1 = Q12(arg0->field_6C.field_8 - (arg0->field_2C.vy + arg0->field_4E)) / arg0->field_50.vy;
            if (var_v1 > Q12(1.0f))
            {
                return;
            }
            sp18.vy = arg0->field_6C.field_8 - arg0->field_4E;
        }
        else
        {
            var_v1 = Q12(arg0->field_6C.field_A - (arg0->field_2C.vy + arg0->field_4C)) / arg0->field_50.vy;
            if (var_v1 > Q12(1.0f))
            {
                return;
            }
            sp18.vy = arg0->field_6C.field_A - arg0->field_4C;
        }

        sp18.vx = arg0->field_2C.vx + FP_MULTIPLY(arg0->field_50.vx, var_v1, Q12_SHIFT);
        sp18.vz = arg0->field_2C.vz + FP_MULTIPLY(arg0->field_50.vz, var_v1, Q12_SHIFT);
        if ((SQUARE(arg0->field_6C.field_0 - sp18.vx) + SQUARE(arg0->field_6C.field_4 - sp18.vz)) >= SQUARE(arg0->field_6C.field_C))
        {
            return;
        }
    }
    else
    {
        sp18.vx = arg0->field_2C.vx + FP_MULTIPLY(arg0->field_50.vx, temp_v0, Q12_SHIFT);
        sp18.vz = arg0->field_2C.vz + FP_MULTIPLY(arg0->field_50.vz, temp_v0, Q12_SHIFT);
    }

    arg0->field_8  = temp_v0_2;
    arg0->field_C  = sp18.vx;
    arg0->field_10 = sp18.vy;
    arg0->field_14 = sp18.vz;
    arg0->field_1C = arg0->field_6C.field_8;
    arg0->field_24 = sp18.vx - arg0->field_6C.field_0;
    arg0->field_26 = sp18.vz - arg0->field_6C.field_4;
    arg0->field_20 = chara;
    arg0->field_28 = 0;
}

void func_8006F250(s32* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x8006F250
{
    s32              i;
    s_func_8006F338* scratch;

    scratch = PSX_SCRATCH;

    func_8006F338(scratch, arg1, arg2, arg3, arg4);

    for (i = 0; i < D_800C4478.field_2; i++)
    {
        if (func_8006F3C4(scratch, D_800C4478.field_4[i]))
        {
            break;
        }
    }

    if (scratch->field_28 == Q12(1.0f))
    {
        arg0[0] = Q12(32.0f);
        arg0[1] = Q12(-16.0f);
    }
    else
    {
        arg0[0] = Math_MulFixed(Vc_VectorMagnitudeCalc(scratch->field_10, Q12(0.0f), scratch->field_14), scratch->field_28, Q12_SHIFT);
        arg0[1] = scratch->field_2C;
    }
}

void func_8006F338(s_func_8006F338* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x8006F338
{
    s32 temp_a1;
    s32 field_4;

    temp_a1 = arg1 + arg3;

    arg0->field_0  = arg1;
    arg0->field_4  = arg2;
    arg0->field_10 = arg3;
    arg0->field_8  = arg1 + arg3;
    arg0->field_28 = Q12(1.0f);
    arg0->field_2C = Q12(1048560.0f);
    arg0->field_14 = arg4;

    arg0->field_C = arg2 + arg4;
    if (temp_a1 >= arg0->field_0)
    {
        arg0->field_18 = arg0->field_0;
        arg0->field_1C = arg0->field_8;
    }
    else
    {
        arg0->field_18 = arg1 + arg3;
        arg0->field_1C = arg0->field_0;
    }

    field_4 = arg0->field_4;
    if (arg0->field_C >= arg0->field_4)
    {
        arg0->field_20 = field_4;
        arg0->field_24 = arg0->field_C;
        return;
    }
    else
    {
        arg0->field_20 = arg0->field_C;
        arg0->field_24 = arg0->field_4;
    }
}

bool func_8006F3C4(s_func_8006F338* arg0, s_func_8006F8FC* arg1) // 0x8006F3C4
{
    s32    temp_s1;
    s32    var_v1;
    q19_12 minX;
    q19_12 maxX;
    q19_12 minZ;
    q19_12 maxZ;
    s32    var_s1;
    s32    var_v0;
    s32    var_v0_2;

    minX = Q12(arg1->field_0_1);
    maxX = Q12(arg1->field_0_1 + arg1->field_0_21);
    minZ = Q12(arg1->field_0_11);
    maxZ = Q12(arg1->field_0_11 + arg1->field_0_25);

    if ((minX >= arg0->field_1C || arg0->field_18 >= maxX) &&
        (minZ >= arg0->field_24 || arg0->field_20 >= maxZ))
    {
        return false;
    }

    if (arg0->field_0 >= minX && maxX >= arg0->field_0 &&
        arg0->field_4 >= minZ && maxZ >= arg0->field_4)
    {
        arg0->field_28 = Q12(0.0f);
        arg0->field_2C = (-Q12(arg1->field_0_29) >> 1) - Q12(1.5f); // NOTE: `-` sign on the outside required for match.
    }
    else
    {
        if (arg0->field_10 >= Q12(0.0f))
        {
            if (arg0->field_14 >= Q12(0.0f))
            {
                var_s1   = minX;
                var_v0_2 = minZ;
            }
            else
            {
                var_s1   = minX;
                var_v0_2 = maxZ;
            }
        }
        else
        {
            if (arg0->field_14 >= Q12(0.0f))
            {
                var_s1   = maxX;
                var_v0_2 = minZ;
            }
            else
            {
                var_s1   = maxX;
                var_v0_2 = maxZ;
            }
        }

        temp_s1 = func_80048E3C(FP_TO(arg0->field_10, Q12_SHIFT) >> 16, FP_TO(arg0->field_14, Q12_SHIFT) >> 16, FP_TO(var_v0_2 - arg0->field_4, Q12_SHIFT) >> 16,
                                FP_TO(minX - arg0->field_0, Q12_SHIFT) >> 16, FP_TO(maxX - arg0->field_0, Q12_SHIFT) >> 16);
        var_v0  = func_80048E3C(FP_TO(arg0->field_14, Q12_SHIFT) >> 16, FP_TO(arg0->field_10, Q12_SHIFT) >> 16, FP_TO(var_s1 - arg0->field_0, Q12_SHIFT) >> 16,
                                FP_TO(minZ - arg0->field_4, Q12_SHIFT) >> 16, FP_TO(maxZ - arg0->field_4, Q12_SHIFT) >> 16);

        if (var_v0 >= temp_s1)
        {
            var_v1 = temp_s1;
        }
        else
        {
            var_v1 = var_v0;
        }

        if (var_v1 < arg0->field_28)
        {
            arg0->field_28 = var_v1;
            arg0->field_2C = (-Q12(arg1->field_0_29) >> 1) - Q12(1.5f); // NOTE: `-` sign on the outside required for match.
        }
    }

    return arg0->field_28 == 0;
}

s32 func_8006F620(VECTOR3* pos, s_func_8006AB50* arg1, s32 arg2, s32 arg3) // 0x8006F620
{
    s32              x0;
    s32              z0;
    s32              x1;
    s32              z1;
    s32              sp28;
    s32              sp2C;
    s32              distX;
    s32              distZ;
    s32              temp_a0;
    s32              temp_s0;
    s32              max1;
    s32              temp_s0_3;
    s32              mag0;
    s32              angle;
    s32              var_s2;
    s32              i;
    q19_12           posX;
    q19_12           posZ;
    s32              result;
    s32              var_v1;
    s_func_8006F8FC* temp_s2;

    result = Q12(-16.0f);

    distX = Q12(0.0f);
    distZ = Q12(0.0f);
    posX  = pos->vx;
    posZ  = pos->vz;
    sp28  = arg1->position_0.vy + arg3;
    sp2C  = sp28 + pos->vy;

    for (i = 0; i < D_800C4478.field_2; i++)
    {
        temp_s2 = D_800C4478.field_4[i];
        temp_s0 = (-Q12(temp_s2->field_0_29) >> 1) - Q12(1.5f); // NOTE: `-` sign on the outside required for match.

        if ((sp2C - temp_s0) >= 0)
        {
            continue;
        }

        func_8006F8FC(&x0, &z0, arg1->position_0.vx + posX, arg1->position_0.vz + posZ, temp_s2);
        if (MAX(ABS(x0), ABS(z0)) >= arg2)

        {
            continue;
        }

        mag0 = Vc_VectorMagnitudeCalc(x0, Q12(0.0f), z0);
        if (mag0 >= arg2)

        {
            continue;
        }

        if (mag0 > 0)
        {
            func_8006F8FC(&x1, &z1, arg1->position_0.vx, arg1->position_0.vz, temp_s2);

            var_s2 = Q12(0.1f);

            max1 = Vc_VectorMagnitudeCalc(x1, Q12(0.0f), z1);

            if ((arg2 - max1) <= Q12(0.1f))
            {
                var_s2 = arg2 - max1;
            }

            if ((mag0 - max1) < var_s2)
            {
                angle = ratan2(x0, z0);
                temp_s0_3 = var_s2 - (mag0 - max1);

                distX = Math_MulFixed(temp_s0_3, Math_Sin(angle), Q12_SHIFT);
                distZ = Math_MulFixed(temp_s0_3, Math_Cos(angle), Q12_SHIFT);
            }
        }
        else
        {
            if (temp_s0 < result)
            {
                result = temp_s0;
            }

            posX = pos->vx;
            posZ = pos->vz;
            break;
        }

        posX += distX;
        posZ += distZ;
    }

    pos->vx = posX;
    pos->vz = posZ;

    if (result != Q12(-16.0f))
    {
        var_v1  = Q12(0.1f);
        temp_a0 = result - sp28;

        if (temp_a0 < Q12(0.1f))
        {
            var_v1 = temp_a0;
        }

        if (pos->vy < var_v1)
        {
            pos->vy = var_v1;
        }
    }

    return result;
}

void func_8006F8FC(s32* outX, s32* outZ, s32 posX, s32 posZ, const s_func_8006F8FC* arg4) // 0x8006F8FC
{
    q19_12 minX;
    q19_12 maxX;
    q19_12 minZ;
    q19_12 maxZ;

    // TODO: Using `Q12` doesn't match? There's an identical block in `func_8006F3C4`.
    minX = FP_TO(arg4->field_0_1, Q12_SHIFT);
    maxX = FP_TO(arg4->field_0_1 + arg4->field_0_21, Q12_SHIFT);
    minZ = FP_TO(arg4->field_0_11, Q12_SHIFT);
    maxZ = FP_TO(arg4->field_0_11 + arg4->field_0_25, Q12_SHIFT);

    if (posX < minX)
    {
        *outX = posX - minX;
    }
    else
    {
        if (maxX >= posX)
        {
            *outX = Q12(0.0f);
        }
        else
        {
            *outX = posX - maxX;
        }
    }

    if (posZ < minZ)
    {
        *outZ = posZ - minZ;
        return;
    }
    else if (maxZ >= posZ)
    {
        *outZ = Q12(0.0f);
        return;
    }

    *outZ = posZ - maxZ;
}

q3_12 func_8006F99C(s_SubCharacter* chara, q19_12 dist, q3_12 headingAngle) // 0x8006F99C
{
    q3_12 curAngleOffset;
    q3_12 angleOffset;
    s32   i;

    angleOffset = NO_VALUE;
    for (i = 0; i < 15; i++)
    {
        if (i == 0)
        {
            curAngleOffset = Rng_TestProbabilityBits(6) - 32;
        }
        else if (i & 1)
        {
            curAngleOffset = (256 << ((i + 1) >> 1)) + Rng_TestProbabilityBits(6);
        }
        else
        {
            curAngleOffset = -(256 << (i >> 1)) - Rng_TestProbabilityBits(6);
        }

        if (angleOffset != NO_VALUE)
        {
            if (ABS(angleOffset) < ABS(curAngleOffset))
            {
                continue;
            }
        }

        if (!func_8007029C(chara, dist, curAngleOffset + headingAngle))
        {
            angleOffset = curAngleOffset;
        }
    }

    if (angleOffset != NO_VALUE)
    {
        return func_8005BF38(angleOffset + headingAngle);
    }

    return FP_ANGLE(360.0f);
}

q7_8 func_8006FAFC(s_SubCharacter* chara, s32 dist, s32 arg2, s32 arg3, s16 arg4, s32 arg5) // 0x8006FAFC
{
    s16    temp_v1;
    q7_8   angle;
    q19_12 newPosZ;
    q19_12 newPosX;
    s32    temp_v0;
    s32    temp_v0_2;
    s32    temp_v1_2;
    s32    i;
    s32    var_s4;
    s32    var_s7;
    s16    subroutine_arg4;

    var_s4 = 0;

    if (arg5 != 0)
    {
        var_s4 = INT_MAX;
    }

    temp_v1         = arg4 / 3;
    subroutine_arg4 = Q12(-1.0f);

    var_s7 = 7;
    if (arg4 == Q12(1.0f))
    {
        var_s7 = 12;
    }

    for (i = 0; i < var_s7; i++)
    {
        if (arg4 == Q12(1.0f))
        {
            angle = (((i * 30) + (Rng_Rand16() % 30)) << 12) / 360;
        }
        else
        {
            angle = (chara->rotation_24.vy + ((i - 3) * temp_v1) + ((Rng_Rand16() % temp_v1) >> 1)) - (temp_v1 >> 2);
        }

        newPosX = chara->position_18.vx + FP_MULTIPLY(dist, Math_Sin(angle), Q12_SHIFT);
        newPosZ = chara->position_18.vz + FP_MULTIPLY(dist, Math_Cos(angle), Q12_SHIFT);

        if (!func_80070030(chara, newPosX, chara->position_18.vy, newPosZ))
        {
            temp_v0   = (arg2 - newPosX) >> 6;
            temp_v0_2 = (arg3 - newPosZ) >> 6;
            temp_v1_2 = (temp_v0 * temp_v0) + (temp_v0_2 * temp_v0_2);

            if ((arg5 == 0 && (var_s4 < temp_v1_2)) ||
                (arg5 != 0 && (temp_v1_2 < var_s4)))
            {
                var_s4          = temp_v1_2;
                subroutine_arg4 = angle;
            }
        }
    }

    if (subroutine_arg4 != FP_ANGLE(-360.0f))
    {
        return func_8005BF38(subroutine_arg4);
    }

    return FP_ANGLE(360.0f);
}

bool func_8006FD90(s_SubCharacter* chara, s32 arg1, s32 arg2, s32 arg3) // 0x8006FD90
{
    VECTOR3 sp10;
    VECTOR3 sp20;
    VECTOR3 sp30; // Q19.12
    VECTOR3 sp40; // Q19.12
    s32     var1;
    s32     dist;
    s32     var0;
    s32     temp;

    if (func_8005BF38(ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                             g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) -
                      chara->rotation_24.vy) < 0)
    {
        var0 = (func_8005BF38(ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                                     g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) -
                              chara->rotation_24.vy) * 2) + FP_ANGLE(360.0f);
    }
    else
    {
        var0 = (FP_ANGLE(180.0f) - func_8005BF38((ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                                                         g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) -
                                                  chara->rotation_24.vy))) * 2;
    }

    for (var1 = var0; arg1 > 0; arg1--)
    {
        var0 = FP_MULTIPLY_PRECISE(var0, var1, Q12_SHIFT);
    }

    dist = Math_Vector2MagCalc(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                               g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);
    temp = arg2 + FP_MULTIPLY_PRECISE(arg3, var0, Q12_SHIFT);
    if (temp < dist)
    {
        return false;
    }

    sp30.vx = chara->position_18.vx;
    sp30.vz = chara->position_18.vz;

    sp40.vx = g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx;
    sp40.vz = g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz;

    if ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) == 2)
    {
        sp40.vy = 0;
        sp30.vy = g_SysWork.player_4C.chara_0.position_18.vy + g_SysWork.player_4C.chara_0.field_C8;
    }
    else
    {
        sp30.vy = chara->position_18.vy + chara->field_CE;
        sp40.vy = (g_SysWork.player_4C.chara_0.position_18.vy + g_SysWork.player_4C.chara_0.field_CE) - (chara->position_18.vy - chara->field_CE);
    }

    // Maybe `sp10` is not `VECTOR3`. Might need to rewrite this whole function if its `s_func_800700F8_2`?
    return func_8006DA08(&sp10, &sp30, &sp40, chara) == 0 || sp20.vx != 0;
}

bool func_80070030(s_SubCharacter* chara, q19_12 x, q19_12 y, q19_12 z)
{
    s_func_800700F8_2 temp;
    VECTOR3           offset; // Q19.12

    offset.vx = x - chara->position_18.vx;
    offset.vy = y - chara->position_18.vy;
    offset.vz = z - chara->position_18.vz;

    func_8006DB3C(&temp, &chara->position_18, &offset, chara);
}

bool func_80070084(s_SubCharacter* chara, q19_12 x, q19_12 y, q19_12 z) // 0x80070084
{
    s_func_800700F8_2 var;
    VECTOR3           offset; // Q19.12
    bool              cond;

    offset.vx = x - chara->position_18.vx;
    offset.vy = y - chara->position_18.vy;
    offset.vz = z - chara->position_18.vz;

    cond = false;
    if (func_8006DB3C(&var, &chara->position_18, &offset, chara))
    {
        cond = var.field_10 == 0;
    }
    return cond;
}

bool func_800700F8(s_SubCharacter* chara0, s_SubCharacter* chara1) // 0x800700F8
{
    s_func_800700F8_2 sp10;
    VECTOR3           pos;
    VECTOR3           offset; // Q19.12

    pos = chara0->position_18;

    offset.vx = chara1->position_18.vx - chara0->position_18.vx;
    offset.vy = Q12(-0.1f);
    offset.vz = chara1->position_18.vz - chara0->position_18.vz;

    return func_8006DB3C(&sp10, &pos, &offset, chara0) && sp10.field_10 == 0;
}

bool func_80070184(s_SubCharacter* chara, s32 arg1, q3_12 rotY) // 0x80070184
{
    s32 iVar0;
    s32 varX;
    s32 iVar1;
    s32 varY;
    s32 varZ;

    iVar0 = Math_Sin(rotY);
    varX  = chara->position_18.vx + FP_MULTIPLY(arg1, iVar0, Q12_SHIFT);
    iVar1 = Math_Cos(rotY);

    varY = chara->position_18.vy;
    varZ = chara->position_18.vz + FP_MULTIPLY(arg1, iVar1, Q12_SHIFT);

    // The calls to this often have a return, so assumed it just passes return of `func_80070084`.
    return func_80070084(chara, varX, varY, varZ);
}

bool func_80070208(s_SubCharacter* chara, q19_12 dist) // 0x80070208
{
    s_func_800700F8_2 var;
    VECTOR3           offset; // Q19.12
    bool              cond;

    offset.vx = FP_MULTIPLY(dist, Math_Sin(chara->rotation_24.vy), Q12_SHIFT);
    offset.vy = Q12(0.0f);
    offset.vz = FP_MULTIPLY(dist, Math_Cos(chara->rotation_24.vy), Q12_SHIFT);

    cond = false;
    if (func_8006DB3C(&var, &chara->position_18, &offset, chara))
    {
        cond = var.field_10 > 0;
    }
    return cond;
}

s32 func_8007029C(s_SubCharacter* chara, q19_12 dist, q3_12 angle) // 0x8007029C
{
    s8      vars[28];
    VECTOR3 offset; // Q19.12

    offset.vx = FP_MULTIPLY(dist, Math_Sin(angle), Q12_SHIFT);
    offset.vy = Q12(0.0f);
    offset.vz = FP_MULTIPLY(dist, Math_Cos(angle), Q12_SHIFT);

    return func_8006DB3C(&vars, &chara->position_18, &offset, chara);
}

bool func_80070320() // 0x80070320
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcIdxs_2354); i++)
    {
        if (g_SysWork.npcIdxs_2354[i] != NO_VALUE)
        {
            return true;
        }
    }

    return false;
}

q19_12 func_80070360(s_SubCharacter* chara, q19_12 someDist, q3_12 arg2) // 0x80070360
{
    q25_6  deltaX;
    q25_6  deltaZ;
    q19_12 dist;
    q19_12 result;

    dist = someDist;
    if (dist == Q12(0.0f))
    {
        deltaX = g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx;
        deltaX = Q12_TO_Q6(deltaX);

        deltaZ = g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz;
        deltaZ = Q12_TO_Q6(deltaZ);

        dist = SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ));
        dist = Q6_TO_Q12(dist);
    }

    // TODO: Why `>> 8`?
    result = FP_MULTIPLY(arg2, g_SysWork.player_4C.chara_0.properties_E4.player.field_10C, Q12_SHIFT) - (dist >> 8);
    if (result < 0)
    {
        result = 0;
    }
    return result;
}

void func_80070400(s_SubCharacter* chara, s_func_80070400_1* arg1, s_func_80070400_1* arg2) // 0x80070400
{
    q19_12 alpha;
    q19_12 invAlpha;

    // Compute alpha.
    if (IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0))
    {
        alpha = Q12_FRACT(chara->model_0.anim_4.time_4);
    }
    else
    {
        alpha = chara->model_0.anim_4.alpha_A;
    }

    // Compute inverse alpha.
    invAlpha = Q12(1.0f) - alpha;

    chara->field_C8           = FP_FROM((arg1->field_0 * invAlpha) + (arg2->field_0 * alpha), Q12_SHIFT);
    chara->field_CA           = FP_FROM((arg1->field_2 * invAlpha) + (arg2->field_2 * alpha), Q12_SHIFT);
    chara->field_CC           = FP_FROM((arg1->field_4 * invAlpha) + (arg2->field_4 * alpha), Q12_SHIFT);
    chara->field_CE           = FP_FROM((arg1->field_6 * invAlpha) + (arg2->field_6 * alpha), Q12_SHIFT);
    chara->field_D8.offsetX_4 = FP_FROM((arg1->field_10 * invAlpha) + (arg2->field_10 * alpha), Q12_SHIFT);
    chara->field_D8.offsetZ_6 = FP_FROM((arg1->field_12 * invAlpha) + (arg2->field_12 * alpha), Q12_SHIFT);
    chara->field_D4           = FP_FROM((arg1->field_8 * invAlpha) + (arg2->field_8 * alpha), Q12_SHIFT);
    chara->field_D8.offsetX_0 = FP_FROM((arg1->field_C * invAlpha) + (arg2->field_C * alpha), Q12_SHIFT);
    chara->field_D8.offsetZ_2 = FP_FROM((arg1->field_E * invAlpha) + (arg2->field_E * alpha), Q12_SHIFT);
    chara->field_D6           = FP_FROM((arg1->field_A * invAlpha) + (arg2->field_A * alpha), Q12_SHIFT);
}

void func_800705E4(GsCOORDINATE2* coord, s32 idx, s32 scaleX, s32 scaleY, s32 scaleZ) // 0x800705E4
{
    s16 scales[3];
    s32 row;
    s32 col;

    scales[0] = scaleX;
    scales[1] = scaleY;
    scales[2] = scaleZ;

    for (col = 0; col < ARRAY_SIZE(scales); col++)
    {
        if (scales[col] != Q12(1.0f))
        {
            for (row = 0; row < 3; row++)
            {
                coord[idx].coord.m[row][col] = FP_MULTIPLY_PRECISE(scales[col], coord[idx].coord.m[row][col], Q12_SHIFT);
            }
        }
    }

    coord->flg = false;
}
