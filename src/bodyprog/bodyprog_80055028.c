#include "game.h"
#include "inline_no_dmpsx.h"

#include <libapi.h>
#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
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
    D_800C4168.field_20 = 0x1000;

    D_800C4168.worldTintColor_28.r = FP_COLOR(0.5f);
    D_800C4168.worldTintColor_28.g = FP_COLOR(0.5f);
    D_800C4168.worldTintColor_28.b = FP_COLOR(0.5f);

    D_800C4168.fogEnabled_1 = false;
    D_800C4168.field_2 = 0;

    D_800C4168.fogColor_1C.r = FP_COLOR(1.0f);
    D_800C4168.fogColor_1C.g = FP_COLOR(1.0f);
    D_800C4168.fogColor_1C.b = FP_COLOR(1.0f);

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

    ot = &g_ObjectTable0[g_ObjectTableIdx];

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
               -180, 120,
               180, 120);

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
           -180, 120,
           180, 120);

    AddPrim(&ot->org[2047], poly);
    packet = GsOUT_PACKET_P;
    SetPriority(packet, 0, 1);
    AddPrim(&ot->org[2047], packet);

    GsOUT_PACKET_P = packet + sizeof(DR_MODE);
    mode           = (DR_MODE*)GsOUT_PACKET_P;

    SetDrawMode(mode, 0, 1, 0x20, NULL);
    AddPrim(&ot->org[2047], mode);

    GsOUT_PACKET_P = packet + 0x18;
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

void func_800554C4(s32 arg0, s16 arg1, GsCOORDINATE2* coord0, GsCOORDINATE2* coord1, SVECTOR* svec, s32 x, s32 y, s32 z, s_WaterZone* waterZones) // 0x800554C4
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
        D_800C4168.field_58 = *svec;
    }
    else
    {
        Vw_CoordHierarchyMatrixCompute(coord0, &mat);
        ApplyMatrixSV(&mat, svec, &D_800C4168.field_58);
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

        tempSvec.vx = FP_METER_TO_GEO(x);
        tempSvec.vy = FP_METER_TO_GEO(y);
        tempSvec.vz = FP_METER_TO_GEO(z);

        ApplyMatrix(&mat, &tempSvec, &vec);

        ptr2     = &D_800C4168.field_60;
        ptr2->vx = FP_METER_FROM_GEO(vec.vx + mat.t[0]);
        ptr2->vy = FP_METER_FROM_GEO(vec.vy + mat.t[1]);
        ptr2->vz = FP_METER_FROM_GEO(vec.vz + mat.t[2]);
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
    return FP_METER_FROM_GEO(mat.t[2]);
}

void func_80055814(s32 arg0) // 0x80055814
{
    D_800C4168.fogRelated_18 = FP_FLOAT_TO(1.0f, Q12_SHIFT) - func_800559A8(arg0);
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

    var_v1 = 0x1000 - (D_800C4168.fogRelated_18 + arg3);
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

void func_80055C3C(CVECTOR* result, CVECTOR* color, void* arg2, void* arg3, s32 arg4, s32 arg5) // 0x80055C3C
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
        gte_lddp(4096 - (temp_a1 << 5));
        gte_ldrgb(color);
        gte_dpcs();
        gte_strgb(result);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80055D78); // 0x80055D78

void func_80055E90(CVECTOR* color, u8 fadeAmount) // 0x80055E90
{
    s32 alpha;
    u8  prev_cd;

    alpha = FP_ALPHA(1.0f) - (fadeAmount * 32);

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

void PlmHeader_FixOffsets(s_PlmHeader* plmHeader) // 0x800560FC
{
    s32 i;

    if (plmHeader->isLoaded_2 == true)
    {
        return;
    }
    plmHeader->isLoaded_2 = true;

    // Add memory address of header to pointer fields.
    plmHeader->textureList_4 = (u8*)plmHeader->textureList_4 + (u32)plmHeader;
    plmHeader->objectList_C  = (u8*)plmHeader->objectList_C  + (u32)plmHeader;
    plmHeader->objectOrds_10 = (u8*)plmHeader->objectOrds_10 + (u32)plmHeader;

    for (i = 0; i < plmHeader->objectCount_8; i++)
    {
        if (plmHeader->magic_0 == PLM_HEADER_MAGIC)
        {
            ObjList_FixOffsets(&plmHeader->objectList_C[i], plmHeader);
        }
    }
}

void ObjList_FixOffsets(s_ObjList* objList, s_PlmHeader* plmHeader) // 0x800561A4
{
    s_ObjHeader* obj;

    objList->meshes_C = (u8*)objList->meshes_C + (u32)plmHeader;

    for (obj = &objList->meshes_C[0]; obj < &objList->meshes_C[objList->meshCount_8]; obj++)
    {
        obj->primitives_4 = (u8*)obj->primitives_4 + (u32)plmHeader;
        obj->vertexXy_8   = (u8*)obj->vertexXy_8   + (u32)plmHeader;
        obj->vertexZ_C    = (u8*)obj->vertexZ_C    + (u32)plmHeader;
        obj->normals_10   = (u8*)obj->normals_10   + (u32)plmHeader;
        obj->unkPtr_14    = (u8*)obj->unkPtr_14    + (u32)plmHeader;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80056244); // 0x80056244

s32 func_80056348(bool (*arg0)(s_PlmTexList* texList), s_PlmHeader* plmHeader) // 0x80056348
{
    s32           count;
    s_PlmTexList* tex;

    count = 0;
    for (tex = plmHeader->textureList_4; tex < (plmHeader->textureList_4 + plmHeader->textureCount_3); tex++)
    {
        if (arg0(tex))
        {
            count++;
        }
    }

    return count;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_800563E8); // 0x800563E8

void func_80056464(s_PlmHeader* plmHeader, s32 fileIdx, s_FsImageDesc* image, s32 arg3) // 0x80056464
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

    func_80056558(plmHeader, sp10, image, arg3);
}

void func_80056504(s_PlmHeader* plmHeader, char* newStr, s_FsImageDesc* image, s32 arg3) // 0x80056504
{
    char sp10[8];

    StringCopy(sp10, newStr);
    func_80056558(plmHeader, sp10, image, arg3);
}

bool func_80056558(s_PlmHeader* plmHeader, char* fileName, s_FsImageDesc* image, s32 arg3) // 0x80056558
{
    s_PlmTexList* texList;
    u32*          texName;

    for (texList = &plmHeader->textureList_4[0];
         texList < &plmHeader->textureList_4[plmHeader->textureCount_3];
         texList++)
    {
        texName = texList->textureName_0.u32;
        if (texName[0] == *(u32*)&fileName[0] && texName[1] == *(u32*)&fileName[4])
        {
            texList->field_C = 1;
            func_8005660C(texList, image, arg3);
            return true;
        }
    }

    return false;
}

void func_8005660C(s_PlmTexList* plmHeader, s_FsImageDesc* image, s32 arg2) // 0x8005660C
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

    plmHeader->field_14.u8[0] = image->u * coeff;
    plmHeader->field_14.u8[1] = image->v;

    plmHeader->field_E  = ((image->tPage[0] & 0x3) << 7) | ((arg2 & 0x3) << 5) | (image->tPage[1] & (1 << 4)) | (image->tPage[1] & 0xF);
    plmHeader->field_10 = (image->clutY << 6) | ((image->clutX >> 4) & 0x3F);
}

void func_800566B4(s_PlmHeader* plmHeader, s_FsImageDesc* image, s8 unused, s32 startIdx, s32 arg4) // 0x800566B4
{
    char           filename[16];
    s32            i;
    s_PlmTexList*  texList;
    s_FsImageDesc* localImage;

    // Loop could be using `&image[i]`/`&arg0->field_4[i]` instead? Wasn't able to make that match though.
    localImage = image;
    texList    = plmHeader->textureList_4;

    for (i = 0; i < plmHeader->textureCount_3; i++, texList++, localImage++)
    {
        func_8005B3BC(filename, texList);
        Fs_QueueStartReadTim(Fs_FindNextFile(filename, 0, startIdx), FS_BUFFER_9, localImage);
        func_8005660C(texList, localImage, arg4);
    }
}

void func_80056774(s_PlmHeader* plmHeader, s_800C1450_0* arg1, bool (*func)(s_PlmTexList* plmTexList), void* arg3, s32 arg4) // 0x80056774
{
    s_PlmTexList* tex;

    for (tex = &plmHeader->textureList_4[0]; tex < &plmHeader->textureList_4[plmHeader->textureCount_3]; tex++)
    {
        if (tex->field_C == 0 && tex->field_8 == NULL && (func == NULL || func(tex)))
        {
            tex->field_8 = func_8005B1FC(tex, arg1, FS_BUFFER_9, arg3, arg4);
            if (tex->field_8 != NULL)
            {
                func_8005660C(tex, &tex->field_8->imageDesc_0, arg4);
            }
        }
    }
}

bool PlmHeader_IsTextureLoaded(s_PlmHeader* plmHeader) // 0x80056888
{
    s_PlmTexList* tex;

    if (!plmHeader->isLoaded_2)
    {
        return false;
    }

    for (tex = &plmHeader->textureList_4[0]; tex < &plmHeader->textureList_4[plmHeader->textureCount_3]; tex++)
    {
        if (tex->field_C != 0)
        {
            continue;
        }

        if (tex->field_8 == NULL)
        {
            return false;
        }

        if (!Fs_QueueIsEntryLoaded(tex->field_8->queueIdx_10))
        {
            return false;
        }
    }

    return true;
}

void func_80056954(s_PlmHeader* plmHeader) // 0x80056954
{
    s32           i;
    s32           j;
    s32           flags;
    s_PlmTexList* tex;

    for (i = 0, tex = plmHeader->textureList_4; i < plmHeader->textureCount_3; i++, tex++)
    {
        flags = (tex->field_E != tex->field_F) ? (1 << 0) : 0;

        if (tex->field_10 != tex->field_12)
        {
            flags |= 1 << 1;
        }

        if (tex->field_14.u16 != tex->field_16.u16)
        {
            flags |= 1 << 2;
        }

        if (flags)
        {
            for (j = 0; j < plmHeader->objectCount_8; j++)
            {
                if (plmHeader->magic_0 == PLM_HEADER_MAGIC)
                {
                    func_80056A88(&plmHeader->objectList_C[j], i, tex, flags);
                }
            }

            tex->field_F        = tex->field_E;
            tex->field_12       = tex->field_10;
            tex->field_16.u8[0] = tex->field_14.u8[0];
            tex->field_16.u8[1] = tex->field_14.u8[1];
        }
    }
}

void func_80056A88(s_ObjList* objList, s32 arg1, s_PlmTexList* plmTexList, s32 flags) // 0x80056A88
{
    u16             field_14;
    u16             field_16;
    s_ObjHeader*    objHeader;
    s_ObjPrimitive* objPrim;

    for (objHeader = objList->meshes_C; objHeader < &objList->meshes_C[objList->meshCount_8]; objHeader++)
    {
        for (objPrim = objHeader->primitives_4; objPrim < &objHeader->primitives_4[objHeader->primitiveCount_0]; objPrim++)
        {
            if (objPrim->field_6_8 == NO_VALUE)
            {
                objPrim->field_6_0 = 32;
            }

            if (objPrim->field_6_8 == arg1)
            {
                if (flags & (1 << 0))
                {
                    objPrim->field_6_0 = plmTexList->field_E;
                }
                if (flags & (1 << 1))
                {
                    objPrim->field_2 = plmTexList->field_10 + (objPrim->field_2 - plmTexList->field_12);
                }
                if (flags & (1 << 2))
                {
                    field_16         = plmTexList->field_16.u16;
                    field_14         = plmTexList->field_14.u16;
                    objPrim->field_0 = field_14 + (objPrim->field_0 - field_16);
                    objPrim->field_4 = field_14 + (objPrim->field_4 - field_16);
                    objPrim->field_8 = field_14 + (objPrim->field_8 - field_16);
                    objPrim->field_A = field_14 + (objPrim->field_A - field_16);
                }
            }
        }
    }
}

void func_80056BF8(s_PlmHeader* plmHeader) // 0x80056BF8
{
    s_PlmTexList*   tex;
    s_PlmTexList_8* temp_v1;

    for (tex = &plmHeader->textureList_4[0]; tex < &plmHeader->textureList_4[plmHeader->textureCount_3]; tex++)
    {
        temp_v1 = tex->field_8;
        if (temp_v1 != NULL)
        {
            temp_v1->field_14--;
            if (temp_v1->field_14 < 0)
            {
                temp_v1->field_14 = 0;
            }

            tex->field_8 = NULL;
        }
    }
}

s32 PlmHeader_ObjectCountGet(s_PlmHeader* plmHeader) // 0x80056C80
{
    return plmHeader->objectCount_8;
}

void func_80056C8C(s_Bone* bone, s_PlmHeader* plmHeader, s32 objListIdx)
{
    s_ObjList* objList = plmHeader->objectList_C;

    bone->objListIdx_C = objListIdx;

    if (plmHeader->magic_0 == PLM_HEADER_MAGIC)
    {
        bone->objList_8 = &objList[objListIdx];
    }
}

bool func_80056CB4(s_800BCE18_2BEC_0* arg0, s_PlmHeader* plmHeader, s_800BCE18_2BEC_0_10* arg2) // 0x80056CB4
{
    u_Filename sp10;
    s32        objListCount;
    bool       result;
    s32        i;
    s_ObjList* objList;

    result = false;

    StringCopy(sp10.str, arg2->string_0);

    objListCount = plmHeader->objectCount_8;

    if (plmHeader->magic_0 == PLM_HEADER_MAGIC)
    {
        for (i = 0, objList = &plmHeader->objectList_C[i]; i < objListCount; i++, objList++)
        {
            if (objList->objName_0.u32[0] == sp10.u32[0] && objList->objName_0.u32[1] == sp10.u32[1])
            {
                result        = true;
                arg0->field_C = i;
                arg0->field_8 = objList;
                // TODO: `field_8` above used to be `s_800BCE18_2BEC_0_10*`, but this func showed it was `s_ObjList*`
                // Unsure if all `s_800BCE18_2BEC_0_10` refs should be changed though since struct is different size.
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

void func_80057090(s_func_80057344* arg0, s_func_80057090* arg1, void* arg2, MATRIX* mat0, MATRIX* mat1, u16 arg5) // 0x80057090
{
    s_ObjList* objList;
    void*      temp_s1;
    s32        temp_a0;

    objList = arg0->field_8;

    if (arg0->field_0 < 0)
    {
        return;
    }

    temp_s1 = arg1->field_4 + (func_800571D0(objList->field_B_1) * 4);
    temp_a0 = objList->field_B_4;
    if ((temp_a0 & 0xFF) != 0 && temp_a0 >= 0 && temp_a0 < 4) // HACK: `& 0xFF` needed for match.
    {
        func_80059D50(temp_a0, arg0, mat0, arg2, temp_s1);
    }
    else
    {
        if (mat1 != NULL && D_800C4168.field_0 != 0)
        {
            func_80057228(mat1, D_800C4168.field_54, &D_800C4168.field_58, &D_800C4168.field_60);
        }

        if (objList->field_B_0)
        {
            D_800C42B4 = arg5;
            func_8005A21C(arg0, temp_s1, arg2, mat0);
        }
        else
        {
            func_80057344(arg0, temp_s1, arg2, mat0);
        }
    }
}

s32 func_800571D0(u32 arg0) // 0x800571D0
{
    switch (arg0)
    {
        case 0:
        default:
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

void func_80057344(s_func_80057344* arg0, void* arg1, void* arg2, MATRIX* mat) // 0x80057344
{
    u32               normalOffset;
    u32               vertexOffset;
    s_ObjHeader*      objHeader;
    s_ObjList*        objList;
    s_GteScratchData* scratchData;

    scratchData = PSX_SCRATCH_ADDR(0);

    objList      = arg0->field_8;
    vertexOffset = objList->vertexOffset_9;
    normalOffset = objList->normalOffset_A;

    gte_lddqa(D_800C4168.field_4C);
    gte_lddqb_0();

    for (objHeader = objList->meshes_C; objHeader < &objList->meshes_C[objList->meshCount_8]; objHeader++)
    {
        if (vertexOffset != 0 || normalOffset != 0)
        {
            func_8005759C(objHeader, scratchData, vertexOffset, normalOffset);
        }
        else
        {
            func_800574D4(objHeader, scratchData);
        }

        switch (D_800C4168.field_0)
        {
            case 0:
                break;

            case 1:
                func_80057658(objHeader, normalOffset, scratchData, &D_800C4168.field_74, &D_800C4168.field_7C);
                break;

            case 2:
                func_80057A3C(objHeader, normalOffset, scratchData, &D_800C4168.field_74);
                break;
        }

        func_80057B7C(objHeader, vertexOffset, scratchData, mat);
        func_8005801C(objHeader, scratchData, arg1, arg2);
    }
}

void func_800574D4(s_ObjHeader* header, s_GteScratchData* scratchData) // 0x800574D4
{
    DVECTOR* vertexXy;
    s16*     vertexZ;
    DVECTOR* screenXy;
    s16*     var_a2;
    u8*      unkPtr;
    u8*      unkPtrDest;

    screenXy = &scratchData->screenXy_0[0];
    var_a2   = &scratchData->field_18C[0]; // `screenZ`? There's already an earlier struct field though.
    vertexXy = &header->vertexXy_8[0];
    vertexZ  = &header->vertexZ_C[0];

    while (var_a2 < &scratchData->field_18C[header->vertexCount_1])
    {
        *(u32*)screenXy++ = *(u32*)vertexXy++;

        *(u32*)var_a2 = *(u32*)vertexZ;
        vertexZ += 2;
        var_a2 += 2;
    }

    while (screenXy < &scratchData->screenXy_0[header->vertexCount_1])
    {
        *(u32*)screenXy++ = *(u32*)vertexXy++;
    }

    unkPtr     = &header->unkPtr_14[0];
    unkPtrDest = &scratchData->field_2B8[0];

    while (unkPtrDest < &scratchData->field_2B8[header->unkCount_3])
    {
        *(u32*)unkPtrDest = *(u32*)unkPtr;
        unkPtr += 4;
        unkPtrDest += 4;
    }
}

void func_8005759C(s_ObjHeader* header, s_GteScratchData* scratchData, s32 vertexOffset, s32 normalOffset) // 0x8005759C
{
    s16* vertexZPtr;
    s16* field_18CPtr;
    s32* vertexXyPtr;
    s32* screenXyPtr;
    u8*  field_2B8Ptr;
    u8*  field_14Ptr;

    // Should be loop? Tried but no luck.
    screenXyPtr  = &scratchData->screenXy_0[vertexOffset];
    field_18CPtr = &scratchData->field_18C[vertexOffset];
    vertexXyPtr  = header->vertexXy_8;
    vertexZPtr   = header->vertexZ_C;
    while (vertexXyPtr < &header->vertexXy_8[header->vertexCount_1])
    {
        *screenXyPtr++  = *vertexXyPtr++;
        *field_18CPtr++ = *vertexZPtr++;
    }

    field_14Ptr  = header->unkPtr_14;
    field_2B8Ptr = &scratchData->field_2B8[normalOffset];
    while (field_14Ptr < &header->unkPtr_14[header->unkCount_3])
    {
        *field_2B8Ptr++ = *field_14Ptr++;
    }
}

void func_80057658(s_ObjHeader* header, s32 offset, s_GteScratchData* scratchData, SVECTOR3* arg3, SVECTOR* arg4) // 0x80057658
{
    s32          geomOffsetX;
    s32          geomOffsetY;
    s32          geomScreen;
    s32          temp_t9;
    s32          var_a1;
    s32          var_v1;
    s32          temp_t2;
    u8           temp_v1;
    u8*          end;
    u8*          var_t0;
    s16*         temp_t8;
    s32*         depthP;
    MATRIX*      mat;
    DVECTOR*     screenPos;
    s_ObjNormal* normal;

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

    for (normal = header->normals_10; normal < &header->normals_10[header->normalCount_2]; normal++)
    {
        temp_t8   = &scratchData->field_380.m[2][0];
        screenPos = &scratchData->screenPos_3A4;
        depthP    = &scratchData->depthP_3A8;
        temp_t2   = temp_v1;

        *(u32*)&scratchData->field_3A0 = *(u32*)normal;

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

void func_80057A3C(s_ObjHeader* header, s32 offset, s_GteScratchData* scratchData, SVECTOR3* lightVec) // 0x80057A3C
{
    s32          var_v1;
    s32          temp_t2;
    u8*          var_a3;
    void*        endPtr;
    s_ObjNormal* normal;

    scratchData->field_380.m[0][0] = lightVec->vx;
    scratchData->field_380.m[0][1] = lightVec->vy;
    scratchData->field_380.m[0][2] = lightVec->vz;
    gte_SetLightMatrix(&scratchData->field_380);

    var_a3  = &scratchData->field_2B8[offset];
    temp_t2 = D_800C4168.field_20;

    for (normal = header->normals_10; normal < &header->normals_10[header->normalCount_2]; normal++)
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

void func_80059D50(s32 arg0, s_func_80057344* arg1, MATRIX* mat, void* arg3, void* arg4) // 0x80059D50
{
    s_GteScratchData* scratchData;
    s_ObjHeader*      mesh;
    s_ObjList*        objList;

    scratchData = PSX_SCRATCH_ADDR(0);

    objList = arg1->field_8;

    for (mesh = &objList->meshes_C[0]; mesh < &objList->meshes_C[objList->meshCount_8]; mesh++)
    {
        func_800574D4(mesh, scratchData);
        func_80057B7C(mesh, 0, scratchData, mat);
        func_80059E34(arg0, mesh, scratchData, arg3, arg4);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80059E34); // 0x80059E34

void func_8005A21C(s_func_80057344* arg0, void* arg1, void* arg2, MATRIX* mat) // 0x8005A21C
{
    s16               var_v1;
    u32               normalOffset;
    u32               vertexOffset;
    s_ObjList*        temp_s1;
    s_ObjHeader*      mesh;
    s_GteScratchData* scratchData;

    scratchData = PSX_SCRATCH_ADDR(0);

    if (D_800C4168.fogEnabled_1)
    {
        if (mat->t[2] < (1 << D_800C4168.fogRelated_14))
        {
            var_v1 = 4096 - (D_800C4168.field_CC[(s32)(mat->t[2] << 7) >> D_800C4168.fogRelated_14] << 4);
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

    temp_s1      = arg0->field_8;
    vertexOffset = temp_s1->vertexOffset_9;
    normalOffset = temp_s1->normalOffset_A;

    for (mesh = temp_s1->meshes_C; mesh < &temp_s1->meshes_C[temp_s1->meshCount_8]; mesh++)
    {
        func_8005A900(mesh, vertexOffset, scratchData, mat);

        if (D_800C4168.field_0 != 0)
        {
            func_8005AA08(mesh, normalOffset, scratchData);
        }

        func_8005AC50(mesh, scratchData, arg1, arg2);
    }
}

void func_8005A42C(s_GteScratchData* scratchData, s32 arg1) // 0x8005A42C
{
    s32 alpha = FP_ALPHA(1.0f) - FP_MULTIPLY(arg1, D_800C4168.field_20, Q12_SHIFT);

    gte_lddp(alpha);
    gte_ldrgb(&D_800C4168.worldTintColor_28);
    gte_dpcs();
    gte_strgb(&scratchData->field_3D8);
}

void func_8005A478(s_GteScratchData* scratchData, s32 alpha) // 0x8005A478
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

    scratchData->field_3E4.m[1][0] = FP_METER(temp_s0_neg) / var_t1;
    scratchData->field_3E4.m[1][1] = FP_METER(temp_s1_neg) / var_t1;
    scratchData->field_3E4.m[1][2] = FP_METER(temp_s2_neg) / var_t1;

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

    var_s0 = FP_FROM(var_s0 * alpha, Q12_SHIFT);

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
    temp_a0 = CLAMP(temp_a0, FP_METER(-1.4f), FP_METER(1.4f));

    temp_v1 = (scratchData->field_3E4.m[1][1] * var_a2) >> 7;
    temp_v1 = CLAMP(temp_v1, FP_METER(-1.4f), FP_METER(1.4f));

    gte_SetLightSourceXY(temp_a0, temp_v1);

    temp_a0 = (scratchData->field_3E4.m[1][2] * var_a2) >> 7;
    temp_a0 = CLAMP(temp_a0, FP_METER(-1.4f), FP_METER(1.4f));

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

void func_8005A900(s_ObjHeader* objHeader, s32 offset, s_GteScratchData* scratchData, MATRIX* mat) // 0x8005A900
{
    DVECTOR* inXy;  // Model-space XY input
    u16*     inZ;   // Model-space Z input
    DVECTOR* outXy; // Projected XY output buffer
    u16*     outZ;  // Projected Z output buffer

    if (objHeader->vertexCount_1 == 0)
    {
        return;
    }

    SetRotMatrix(mat);
    SetTransMatrix(mat);

    outXy = &scratchData->screenXy_0[offset];
    outZ  = &scratchData->screenZ_168[offset];

    inXy = objHeader->vertexXy_8;
    inZ  = objHeader->vertexZ_C;

    while (outXy < &scratchData->screenXy_0[objHeader->vertexCount_1 + offset])
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

u8 func_8005AA08(s_ObjHeader* objHeader, s32 arg1, s_GteScratchData2* scratchData) // 0x8005AA08
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

    CVECTOR      sp0;
    s_ObjNormal* var_a3;
    VECTOR3*     var_t0;

    if (objHeader->normalCount_2 == 0)
    {
        return;
    }

    sp0.cd = 0;
    gte_ldrgb(&sp0);

    var_a3 = objHeader->normals_10;
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

    while(var_a3 < &objHeader->normals_10[objHeader->normalCount_2])
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

void func_8005B1A0(s_800C1450_58* arg0, char* arg1, s32 arg2, u8 arg3, s32 arg4, s32 arg5, s16 arg6, s16 arg7) // 0x8005B1A0
{
    arg0->field_0 = arg2;
    arg0->field_1 = arg3;
    arg0->field_2 = arg4;
    arg0->field_3 = arg5;
    arg0->field_4 = arg6;
    arg0->field_6 = arg7;

    StringCopy(arg0->string_8.str, arg1);

    arg0->field_14 = 0;
    arg0->field_10 = NO_VALUE;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005B1FC); // 0x8005B1FC

void func_8005B370(s_800C1450_58* arg0) // 0x8005B370
{
    arg0->field_14 = 0;
}

void func_8005B378(s_800C1450_58* arg0, char* arg1) // 0x8005B378
{
    arg0->field_14 = 1;
    arg0->field_10 = 0;
    StringCopy(arg0->string_8.str, arg1);
}

void func_8005B3A4(s_800C1450_58* arg0) // 0x8005B3A4
{
    arg0->string_8.u32[1] = 0;
    arg0->string_8.u32[0] = 0;

    arg0->field_14 = 0;
    arg0->field_10 = NO_VALUE;
}

void func_8005B3BC(char* filename, s_PlmTexList* plmTexList) // 0x8005B3BC
{
    char sp10[12];

    // Some inline `memcpy`/`bcopy`/`strncpy`? those use `lwl`/`lwr`/`swl`/`swr` instead though
    // Example: casting `filename`/`arg1` to `u32*` and using `memcpy` does generate `lw`/`sw`,
    // but not in same order as this, guess it's some custom inline/macro instead.
    *(u32*)&sp10[0] = *(u32*)&plmTexList->textureName_0.str[0];
    *(u32*)&sp10[4] = *(u32*)&plmTexList->textureName_0.str[4];
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

void func_8005B46C(s_800C1450_0* arg0) // 0x8005B46C
{
    arg0->count_0 = 0;
}

void func_8005B474(s_800C1450_0* arg0, s_800C1450_58* arg1, s32 idx) // 0x8005B474
{
    s_800C1450_58*  ptr;
    s_800C1450_58** entryPtr;

    entryPtr = arg0->entries_4;
    for (ptr = &arg1[0]; ptr < &arg1[idx];)
    {
        *entryPtr++ = ptr++;
        arg0->count_0++;
    }
}

s_800C1450_58* func_8005B4BC(char* str, s_800C1450_0* arg1) // 0x8005B4BC
{
    char           prevStr[8];
    s32            i;
    s_800C1450_58* ptr;

    StringCopy(prevStr, str);

    for (i = 0; i < arg1->count_0; ++i)
    {
        ptr = arg1->entries_4[i];

        // Fast string comparison.
        if (ptr->field_10 != NO_VALUE &&
            *(u32*)&prevStr[0] == ptr->string_8.u32[0] && *(u32*)&prevStr[4] == ptr->string_8.u32[1])
        {
            return ptr;
        }
    }

    return NULL;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005B55C); // 0x8005B55C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005B62C); // 0x8005B62C

void func_8005BF0C(s16 unused, s16 x, s16 y) // 0x8005BF0C
{
    Gfx_DebugStringPosition(x, y);
}

s16 func_8005BF38(s16 angle) // 0x8005BF38
{
    s16 outAngle;
    s16 angleNorm;

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005C478); // 0x8005C478

s16 func_8005C7B0(s32 arg0) // 0x8005C7B0
{
    return D_800AE520[arg0 >> 5];
}

s32 func_8005C7D0(s_SubCharacter* chara, s32 moveSpeed) // 0x8005C7D0
{
    s32             i = 0;
    s_SubCharacter* npc;
    s_SubCharacter* player;

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
    s16 temp_v0;
    s16 temp_s0;
    s16 temp_s1;
    s16 temp_s2;
    s16 temp_s3;
    s16 temp_s4;

    temp_s0 = arg0->field_0;
    temp_s3 = arg0->field_2;
    temp_s2 = arg0->field_4;
    temp_s4 = arg0->field_6;

    temp_s1 = Math_Cos(chara->rotation_24.vy);
    temp_v0 = Math_Sin(chara->rotation_24.vy);

    chara->field_D8.field_0 = FP_FROM((temp_s0 * temp_s1) + (temp_s3 * temp_v0), Q12_SHIFT);
    chara->field_D8.field_2 = FP_FROM((-temp_s0 * temp_v0) + (temp_s3 * temp_s1), Q12_SHIFT);
    chara->field_D8.field_4 = FP_FROM((temp_s2 * temp_s1) + (temp_s4 * temp_v0), Q12_SHIFT);
    chara->field_D8.field_6 = FP_FROM((-temp_s2 * temp_v0) + (temp_s4 * temp_s1), Q12_SHIFT);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005C944); // 0x8005C944

s32 func_8005CB20(s_SubCharacter* chara, s_800C4590* arg1, s16 x, s16 z) // 0x8005CB20
{
    s_800C4590 sp10;
    VECTOR3    sp30;
    s32        headingAngle;
    s32        temp_s0;
    s32        temp_s0_2;
    s32        temp_s2;
    s32        temp_s3;
    s32        temp_v0_2;
    s32        temp_v0_4;
    s32        temp_v0_5;
    s32        ret;

    headingAngle = chara->headingAngle_3C;
    temp_s0 = FP_MULTIPLY_PRECISE(g_DeltaTime0, chara->moveSpeed_38, Q12_SHIFT);
    temp_s2 = OVERFLOW_GUARD(temp_s0);
    temp_s3 = temp_s2 >> 1;

    temp_v0_5 = Math_Sin(headingAngle);
    temp_s0_2 = temp_s0 >> temp_s3;
    temp_v0_2 = temp_v0_5 >> temp_s3;
    sp30.vx   = (s32)FP_MULTIPLY_PRECISE(temp_s0_2, temp_v0_2, Q12_SHIFT) << temp_s2;

    temp_v0_4 = Math_Cos(headingAngle) >> temp_s3;
    sp30.vz   = (s32)FP_MULTIPLY_PRECISE(temp_s0_2, temp_v0_4, Q12_SHIFT) << temp_s2;

    temp_v0_5 = chara->field_34;
    sp30.vx += x;
    sp30.vy = FP_MULTIPLY_PRECISE(g_DeltaTime0, temp_v0_5, Q12_SHIFT);
    sp30.vz += z;

    ret = func_80069B24(&sp10, &sp30, chara);

    chara->position_18.vx += sp10.field_0.vx;
    chara->position_18.vy += sp10.field_0.vy;
    chara->position_18.vz += sp10.field_0.vz;

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

    temp    = FP_ALPHA_NORM(arg0);
    temp_a1 = FP_FROM(arg0, Q12_SHIFT);

    if (temp_a1 >= 12)
    {
        return 0;
    }
    if (temp_a1 < -20)
    {
        return 0x7FFFFFFF;
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

        var_a0 = FP_MULTIPLY_PRECISE(var_a0, 0x1000 - temp_a2, Q12_SHIFT) + FP_MULTIPLY_PRECISE(var_v1, temp_a2, Q12_SHIFT);
    }

    return var_a0;
}

s32 func_8005D974(s32 arg0) // 0x8005D974
{
    s32 val = func_8005D86C(arg0);

    if (val > 0x4000)
    {
        val = 0x4000;
    }
    else if (val < 0)
    {
        val = 0;
    }

    return val;
}

s32 func_8005D9B8(VECTOR3* arg0, s32 arg1) // 0x8005D9B8
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
                                         FP_MULTIPLY_PRECISE(deltaZ, deltaZ, Q12_SHIFT)) - 0x2800) / 10);
    if (var_s0 > 0x1000)
    {
        var_s0 = 0x1000;
    }

    deltaX  = D_800C42CC->vx - arg0->vx;
    deltaY  = D_800C42CC->vy - arg0->vy;
    deltaZ  = D_800C42CC->vz - arg0->vz;
    temp_v0 = func_8005D974((SquareRoot12(FP_MULTIPLY_PRECISE(deltaX, deltaX, Q12_SHIFT) +
                                          FP_MULTIPLY_PRECISE(deltaY, deltaY, Q12_SHIFT) +
                                          FP_MULTIPLY_PRECISE(deltaZ, deltaZ, Q12_SHIFT)) - 0x6000) / 4);

    var_v0 = FP_MULTIPLY_PRECISE(var_s0, temp_v0, Q12_SHIFT);
    if (var_v0 > 0x2000)
    {
        var_v0 = 0x2000;
    }
    else if (var_v0 < 0)
    {
        var_v0 = 0;
    }

    var_v0 = FP_MULTIPLY_PRECISE(arg1, var_v0, Q12_SHIFT);
    if (var_v0 > 0xFF)
    {
        var_v0 = 0xFF;
    }
    else if (var_v0 < 0)
    {
        var_v0 = 0;
    }

    return var_v0;
}

void func_8005DC1C(s32 sfx, const VECTOR3* pos, s32 vol, s32 soundType)
{
    func_8005DC3C(sfx, pos, vol, soundType, 0);
}

void func_8005DC3C(s32 sfx, const VECTOR3* pos, s32 vol, s32 soundType, s32 pitch) // 0x8005DC3C
{
    s32 volCpy;
    s32 balance;

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
    if (vol > FP_VOLUME(1.0f))
    {
        vol = FP_VOLUME(1.0f);
    }
    else if (vol < FP_VOLUME(0.0f))
    {
        vol = FP_VOLUME(0.0f);
    }

    if (!(soundType & (1 << 1)))
    {
        volCpy = func_8005D9B8(pos, vol);
    }
    else
    {
        volCpy = vol;
    }

    if (volCpy > FP_VOLUME(1.0f))
    {
        volCpy = FP_VOLUME(1.0f);
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

void func_8005DD44(s32 sfx, VECTOR3* pos, s32 vol, s8 pitch) // 0x8005DD44
{
    s32 volCpy;
    s32 balance;

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
    if (vol > FP_VOLUME(1.0f))
    {
        vol = FP_VOLUME(1.0f);
    }
    else if (vol < FP_VOLUME(0.0f))
    {
        vol = FP_VOLUME(0.0f);
    }

    volCpy = func_8005D9B8(pos, vol);
    if (volCpy > FP_VOLUME(1.0f))
    {
        volCpy = FP_VOLUME(1.0f);
    }

    func_80046620(sfx & 0xFFFF, balance, ~volCpy & 0xFF, pitch);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005DE0C); // 0x8005DE0C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005E0DC); // 0x8005E0DC

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005E7E0); // 0x8005E7E0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005E89C); // 0x8005E89C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005F55C); // 0x8005F55C

s32 func_8005F680(s_func_800699F8* arg0) // 0x8005F680
{
    s32 var_a0;
    s8 temp_v1;

    temp_v1 = arg0->field_8;

    var_a0 = 0;
    if (temp_v1 == 0 || temp_v1 == 12 || temp_v1 == 7)
    {
        var_a0 = 1;
    }
    return var_a0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8005F6B0); // 0x8005F6B0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80060044); // 0x80060044

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_800611C0); // 0x800611C0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_800622B8); // 0x800622B8

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
    g_MapOverlayHeader.unkTable1_4C[idx].field_10 = arg3 * FP_FLOAT_TO(5.0f, Q12_SHIFT);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80062708); // 0x80062708

// Displays gun shooting effects.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006342C); // 0x8006342C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80063A50); // 0x80063A50

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80064334); // 0x80064334

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80064F04); // 0x80064F04

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80064FC0); // 0x80064FC0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_800652F4); // 0x800652F4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80065B94); // 0x80065B94

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80066184); // 0x80066184

void func_80066D90() // 0x80066D90
{
    s32       var_s1;
    DR_TPAGE* var1; // Guessed type.
    TILE*     var2; // Guessed type.

    for (var_s1 = 0; var_s1 < 0x3F; var_s1++)
    {
        var1 = PSX_SCRATCH;
        setlen(var1, 1);
        var1->code[0] = 0xE1000240;
        DrawPrim(var1);

        var2 = PSX_SCRATCH;
        setlen(var2, 3);

        // @hack Maybe not `TILE`?
        *(s32*)&var2->r0 = 0x62080808;
        *(s32*)&var2->x0 = 0xFF20FF60;
        *(s32*)&var2->w  = 0x01C00140;
        DrawPrim(var2);

        Fs_QueueUpdate();
        VSync(0);
    }

    Fs_QueueWaitForEmpty();
}

void func_80066E40() // 0x80066E40
{
    DrawSync(0);
    StoreImage(&D_80028A20, FS_BUFFER_3);
    DrawSync(0);
}

void func_80066E7C() // 0x80066E7C
{
    LoadImage(&D_80028A20, FS_BUFFER_3);
    DrawSync(0);
}

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_80055028", hack_D_80028A18_fix);

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_80055028", D_80028A20);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", GameState_MapScreen_Update); // 0x80066EB0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80067914); // 0x80067914

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80068CC0); // 0x80068CC0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80068E0C); // 0x80068E0C

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80069860); // 0x80069860

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

void func_800699F8(s_func_800699F8* coll, s32 posX, s32 posZ) // 0x800699F8
{
    s_func_8006AB50     sp10;
    VECTOR3             sp28;
    s_func_8006CC44     sp38;
    s_IpdCollisionData* ipdCollData;

    sp28.vx = FP_METER(0.0f);
    sp28.vy = FP_METER(0.0f);
    sp28.vz = FP_METER(0.0f);

    ipdCollData = func_800426E4(posX, posZ);
    if (ipdCollData == NULL)
    {
        coll->groundHeight_0 = FP_METER(8.0f);
        coll->field_6        = 0;
        coll->field_4        = 0;
        coll->field_8        = 0;
        return;
    }

    sp10.position_0.vx = posX;
    sp10.position_0.vy = FP_METER(0.0f);
    sp10.position_0.vz = posZ;
    sp10.rotation_C.vx = FP_ANGLE(0.0f);
    sp10.rotation_C.vy = FP_ANGLE(0.0f);
    sp10.rotation_C.vz = FP_ANGLE(0.0f);
    func_8006AB50(&sp38, &sp28, &sp10, 0);

    sp38.field_0_8  = 0;
    sp38.field_0_9  = 0;
    sp38.field_0_10 = 1;
    func_8006AD44(&sp38, ipdCollData);

    if (sp38.field_90 == 1)
    {
        coll->field_8        = 0;
        coll->groundHeight_0 = FP_METER(8.0f);
    }
    else
    {
        coll->field_8        = sp38.field_94;
        coll->groundHeight_0 = func_8006CC44(sp38.field_4.positionX_18, sp38.field_4.positionZ_1C, &sp38) * 16;
    }

    coll->field_4 = sp38.field_88;
    coll->field_6 = sp38.field_8C;
}

s32 func_80069B24(s_800C4590* arg0, VECTOR3* arg1, s_SubCharacter* chara) // 0x80069B24
{
    s32 var0; 
    s32 var1;

    var0 = SetSp(0x1F8003D8);
    var1 = func_80069BA8(arg0, arg1, chara, func_80069FFC(arg0, arg1, chara));
    SetSp(var0);
    return var1; 
}

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_80055028", D_80028B2C);

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_80055028", D_80028B34);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80069BA8); // 0x80069BA8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_80069DF0); // 0x80069DF0

s32 func_80069FFC(s_800C4590* arg0, VECTOR3* arg1, s_SubCharacter* chara) // 0x80069FFC
{
    s_func_8006AB50 sp28;
    VECTOR3         sp40;
    s32             sp50;
    s32             sp54;
    s32             var_s1;

    sp28.position_0.vx = chara->position_18.vx + chara->field_D8.field_4;
    sp28.position_0.vy = chara->position_18.vy - FP_METER(0.02f);
    sp28.position_0.vz = chara->position_18.vz + chara->field_D8.field_6;

    if (func_800426E4(chara->position_18.vx, chara->position_18.vz) == NULL)
    {
        func_8006A178(arg0, 0, 0, 0, 0x8000);
        return 1;
    }

    sp28.rotation_C.vy = chara->field_C8;
    sp28.rotation_C.vx = chara->field_CA;
    sp28.rotation_C.vz = chara->field_D4;

    sp28.field_12 = chara->field_E0_8;

    sp40 = *arg1;

    switch (chara->model_0.charaId_0)
    {
        case 1:
        case 4:
        case 5:
        case 12:
            var_s1 = 1;
            break;

        default:
            var_s1 = 0;
            break;
    }

    return func_8006A4A8(arg0, &sp40, &sp28, var_s1, func_800425D8(&sp50), sp50, 0, 0, func_8006A1A4(&sp54, chara, 1), sp54);
}

void func_8006A178(s_800C4590* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x8006A178
{
    arg0->field_0.vx = arg1;
    arg0->field_0.vy = arg2;
    arg0->field_0.vz = arg3;
    arg0->field_12 = 0;
    arg0->field_10 = 0;
    arg0->field_14 = 0;
    arg0->field_18 = 0xFFFF0000;
    arg0->field_C  = arg4;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006A1A4); // 0x8006A1A4

s32 func_8006A3B4(s32 arg0, VECTOR* arg1, s32 arg2) // 0x8006A3B4
{
    s32 var0;
    s32 var1;

    var0 = SetSp(0x1F8003D8);
    var1 = func_8006A42C(arg0, arg1, arg2);
    SetSp(var0);

    if (var1 == NO_VALUE)
    {
        var1 = 1;
    }

    return var1;
}

s32 func_8006A42C(s32 arg0, VECTOR3* arg1, s32 arg2) // 0x8006A42C
{
    VECTOR3 sp28;
    s32     sp38;

    sp28 = *arg1;

    return func_8006A4A8(arg0, &sp28, arg2, 0, func_800425D8(&sp38), sp38, 0, 0, 0, 0);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006A4A8); // 0x8006A4A8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006A940); // 0x8006A940

void func_8006AB50(s_func_8006CC44* arg0, VECTOR3* vec, s_func_8006AB50* arg2, s32 arg3) // 0x8006AB50
{
    arg0->field_0_0       = 0;
    arg0->field_2         = D_800C4478.field_0;
    arg0->field_4.field_4 = arg3;

    func_8006ABC0(&arg0->field_4, vec, arg2);

    arg0->field_7C = 0x1E00;
    arg0->field_34 = 0;
    arg0->field_44 = 0;
    arg0->field_4A = 0;
    arg0->field_4C = 0;
    arg0->field_7A = 0;
    arg0->field_74 = 0;
    arg0->field_8C = 0;
    arg0->field_88 = 0;
    arg0->field_90 = 1;
    arg0->field_94 = 0;
}

void func_8006ABC0(s_func_8006ABC0* result, VECTOR3* vec, s_func_8006AB50* arg2) // 0x8006ABC0
{
    s16 angleXz;

    result->field_C.vx = FP_METER_TO_GEO(vec->vx);
    result->field_C.vy = FP_METER_TO_GEO(vec->vy);
    result->field_C.vz = FP_METER_TO_GEO(vec->vz);

    result->field_8 = SquareRoot0(SQUARE(result->field_C.vx) + SQUARE(result->field_C.vz));

    if (result->field_8 != 0)
    {
        // @unused
        result->directionX_14 = FP_METER(result->field_C.vx) / result->field_8;
        result->directionZ_16 = FP_METER(result->field_C.vz) / result->field_8;

        angleXz               = ratan2(result->field_C.vz, result->field_C.vx);
        result->directionX_14 = Math_Cos(angleXz);
        result->directionZ_16 = Math_Sin(angleXz);
    }
    else
    {
        result->directionX_14 = FP_METER(1.0f);
        result->directionZ_16 = FP_METER(0.0f);
    }

    result->field_28     = FP_FROM(arg2->rotation_C.vz, Q4_SHIFT); // TODO: Packed angle?
    result->positionX_18 = FP_METER_TO_GEO(arg2->position_0.vx);
    result->positionZ_1C = FP_METER_TO_GEO(arg2->position_0.vz);
    result->field_20     = result->positionX_18 + result->field_C.vx;
    result->field_24     = result->positionZ_1C + result->field_C.vz;
    result->field_2A     = FP_FROM(arg2->rotation_C.vy + arg2->position_0.vy, Q4_SHIFT); // TODO: Position + rotation? Seems wrong.
    result->field_2C     = FP_FROM(arg2->rotation_C.vx + arg2->position_0.vy, Q4_SHIFT);
    result->field_0      = arg2->field_12;
}

void func_8006AD44(s_func_8006CC44* arg0, s_IpdCollisionData* collData) // 0x8006AD44
{
    s32  temp_s4;
    s32* var_s0;
    s32  temp_s5;
    s32  var_s1;
    s32  var_s2;

    if ((collData->field_8_8 == 0 && collData->field_8_16 == 0 && collData->field_8_24 == 0) ||
        !func_8006AEAC(arg0, collData))
    {
        return;
    }

    if (arg0->field_0_0 == 0)
    {
        func_80069994(collData);
    }

    temp_s5 = arg0->field_A0;
    temp_s4 = (arg0->field_A0 + arg0->field_A2) - 1;

    for (var_s2 = arg0->field_A1; var_s2 < (arg0->field_A1 + arg0->field_A3); var_s2++)
    {
        var_s0 = &collData->ptr_20[(var_s2 * collData->field_1E) + temp_s5];

        for (var_s1 = temp_s5; var_s1 <= temp_s4; var_s1++, var_s0++)
        {
            func_8006B1C8(arg0, collData, var_s0);
        }
    }

    if (arg0->field_0_0 == 0)
    {
        func_800699E4(collData);
    }

    if (arg0->field_0_10)
    {
        func_8006C838(arg0, collData);
        if (arg0->field_A4 != NULL)
        {
            func_8006CA18(arg0, collData, arg0->field_A4);
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006AEAC); // 0x8006AEAC

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

    var_a3 = arg0->field_4.positionX_18 - collData->posX_0;
    var_t0 = arg0->field_4.field_20 - collData->posX_0;
    if (var_t0 < var_a3)
    {
        var_t0 ^= var_a3;
        var_a3 ^= var_t0;
        var_t0 ^= var_a3;
    }

    var_a3 -= arg0->field_4.field_28;
    var_t0 += arg0->field_4.field_28;

    var_a0 = arg0->field_4.positionZ_1C - collData->posZ_4;
    var_a2 = arg0->field_4.field_24 - collData->posZ_4;
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

    arg0->field_A0 = (var_a3 / collData->field_1C);
    arg0->field_A1 = (var_a0 / collData->field_1C);
    arg0->field_A2 = ((var_t0 / collData->field_1C) - arg0->field_A0) + 1;
    arg0->field_A3 = ((var_a2 / collData->field_1C) - arg0->field_A1) + 1;

    return true;
}

void func_8006B1C8(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s_func_8006B1C8* arg2) // 0x8006B1C8
{
    s32 var;
    s32 i;
    u8  idx;

    for (i = arg2->field_0; i < arg2->field_4; i++)
    {
        idx = collData->ptr_28[i];

        if (collData->field_30 >= collData->field_34[idx])
        {
            collData->field_34[idx] = collData->field_30 + 1;
            var                     = collData->field_8_16;

            if (idx < var)
            {
                if (func_8006B318(arg0, collData, idx) != 0)
                {
                    if (arg0->field_0_10)
                    {
                        func_8006B6E8(arg0, arg2);
                    }

                    if (arg0->field_0_8 || arg0->field_0_9)
                    {
                        if (arg0->field_D8.s_field_0.field_1 == 0xFF)
                        {
                            func_8006B9C8(arg0);
                        }

                        if (arg0->field_D8.s_field_0.field_0 == 0xFF)
                        {
                            func_8006B8F8(&arg0->field_CC); // TODO: `unk_CC` is struct? 56 bytes?
                            func_8006B9C8(arg0);
                        }
                    }
                }
            }
            else if (func_8006C3D4(arg0, collData, idx) != 0)
            {
                func_8006C45C(arg0);
            }
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006B318); // 0x8006B318

void func_8006B6E8(s_func_8006CC44* arg0, s_func_8006B1C8* arg1) // 0x8006B6E8
{
    s32                 idx;
    s32                 temp_s1;
    s32                 temp_s2;
    s32                 temp_s3;
    s32                 temp_s4;
    s_func_8006CC44_A8* temp_s0;

    temp_s1 = arg0->field_D8.s_field_0.field_0;
    temp_s2 = arg0->field_D8.s_field_0.field_1;
    temp_s3 = arg0->field_DC;
    temp_s4 = arg0->field_DD;

    if (temp_s1 == 0xFF)
    {
        if (temp_s2 == 0xFF)
        {
            return;
        }

        idx = arg0->field_DB;
    }
    else
    {
        idx = arg0->field_DA;
    }

    temp_s0 = &arg0->field_A8[idx];
    if (!func_8006B7E0(temp_s0, &arg0->field_EC))
    {
        return;
    }

    temp_s0->field_0 = arg0->field_F4;
    temp_s0->field_4 = arg0->field_F8;
    temp_s0->field_2 = arg0->field_FC;

    if (arg0->field_EE >= 0)
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006B7E0); // 0x8006B7E0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006B8F8); // 0x8006B8F8

void func_8006B9C8(s_func_8006CC44* arg0) // 0x8006B9C8
{
    s32 field_28;

    if (arg0->field_D8.s_field_0.field_1 == 0xFF && arg0->field_EE < 0 &&
        (arg0->field_4.field_2C >= arg0->field_E0 || arg0->field_4.field_2C >= arg0->field_E6))
    {
        if (arg0->field_0_9 && arg0->field_F8 < arg0->field_4.field_28)
        {
            func_8006BB50(arg0, 0);
            return;
        }

        field_28 = arg0->field_4.field_28;
        if (arg0->field_0_9 && arg0->field_F8 < (field_28 + 8))
        {
            func_8006BB50(arg0, 1);
        }

        if (arg0->field_0_8)
        {
            if (!arg0->field_44 &&
                (-field_28 < arg0->field_EE || -field_28 < arg0->field_F2) &&
                (-field_28 < arg0->field_EC || -field_28 < arg0->field_F0) &&
                (arg0->field_EC < (field_28 + arg0->field_D6) || arg0->field_F0 < (field_28 + arg0->field_D6)))
            {
                func_8006BE40(arg0);
            }
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006BB50); // 0x8006BB50

s32 func_8006BC34(s_func_8006CC44* arg0)
{
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_v0;
    s16 temp_v1;
    u16 temp_a1;
    u16 var_v0;

    temp_v1 = arg0->field_EC;
    if (temp_v1 < 0)
    {
        var_v0 = arg0->field_E0;
    }
    else
    {
        temp_a2 = arg0->field_D6;
        if (temp_a2 < temp_v1)
        {
            var_v0 = arg0->field_E6;
        }
        else
        {
            temp_a3 = arg0->field_E0;
            temp_v0 = arg0->field_E6;
            temp_a1 = arg0->field_E0;

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006BCC4); // 0x8006BCC4

void func_8006BDDC(s_func_8006BDDC* arg0, s16 arg1, s16 arg2) // 0x8006BDDC
{
    if (arg0->field_0 == 0)
    {
        arg0->field_0 = 1;
        arg0->field_2 = arg1;
        arg0->field_4 = arg2;
        return;
    }

    arg0->field_0++;
    Vw_ClampAngleRange(&arg0->field_2, &arg0->field_4, arg1, arg2);
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

    if (arg0->field_EE >= temp_a3)
    {
        if (arg0->field_EC >= 0)
        {
            if (arg0->field_D6 >= arg0->field_EC)
            {
                var_a2 = arg0->field_EC;
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
        if (arg0->field_102 == 0)
        {
            if ((arg0->field_EC > 0) && (arg0->field_EC < arg0->field_D6))
            {
                var_a1 = 0;
                var_a2 = arg0->field_EC;
            }
        }
        else
        {
            var_a1 = FP_TO(temp_a3 - arg0->field_EE, Q12_SHIFT) / arg0->field_102;
            temp   = arg0->field_100 * var_a1;
            temp   = FP_FROM(temp, Q12_SHIFT);
            var_a2 = temp + arg0->field_EC;
        }

        if (var_a2 < 0)
        {
            var_v1 = 0;
        }
        else if (arg0->field_D6 < var_a2)
        {
            var_v1 = 1;
        }
        else
        {
            var_v1 = 2;
        }
    }

    // TODO: It's possible `temp_a3` is not passed in these calls.
    switch (var_v1)
    {
        case 0:
            func_8006BF88(arg0, &arg0->field_DE, var_a2, temp_a3);
            break;

        case 1:
            func_8006BF88(arg0, &arg0->field_E4, var_a2, temp_a3);
            break;

        case 2:
            func_8006C0C8(arg0, var_a1, var_a2, temp_a3);
            break;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006BF88); // 0x8006BF88

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006C0C8); // 0x8006C0C8

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006C248); // 0x8006C248

s32 func_8006C3D4(s_func_8006CC44* arg0, s_IpdCollisionData* collData, s32 idx) // 0x8006C3D4
{
    s_IpdCollisionData_18* temp_a1;

    arg0->field_CC = collData;
    arg0->field_D0 = idx;
    temp_a1        = &collData->ptr_18[idx - collData->field_8_16];

    if (!((arg0->field_2 >> temp_a1->field_0_8) & 0x1))
    {
        return 0;
    }

    arg0->field_D1         = temp_a1->field_0_5;
    arg0->field_D2         = temp_a1->field_2;
    arg0->field_D4         = temp_a1->field_4;
    arg0->field_D6         = temp_a1->field_6;
    arg0->field_D8.field_0 = temp_a1->field_8;
    return 1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006C45C); // 0x8006C45C

void func_8006C794(s_func_8006CC44* arg0, s32 arg1, s32 arg2) // 0x8006C794
{
    s32 var;

    if (arg0->field_4.field_2C >= (arg0->field_D4 + (arg2 - arg0->field_D8.field_0)))
    {
        var = arg0->field_D0 + 52;
        func_8006BCC4(&arg0->field_44,
                      arg0->field_CC + var,
                      arg1,
                      arg0->field_98 - arg0->field_D2,
                      arg0->field_9A - arg0->field_D6,
                      arg0->field_4.field_28 + arg0->field_D8.field_0 - arg2);
    }
}

void func_8006C838(s_func_8006CC44* arg0, s_IpdCollisionData* collData) // 0x8006C838
{
    s32                    var_a0;
    s_func_8006CC44_A8*    var_t1;
    s_IpdCollisionData_10* temp_a1;
    s_IpdCollisionData_18* temp_a0;

    if (!arg0->field_A4)
    {
        return;
    }

    if (arg0->field_C8 != 0xFF)
    {
        if (arg0->field_CA < arg0->field_7C)
        {
            temp_a0        = &collData->ptr_18[arg0->field_C8 - collData->field_8_16];
            arg0->field_7C = arg0->field_CA;
            arg0->field_80 = arg0->field_98 + collData->posX_0;
            arg0->field_84 = arg0->field_9A + collData->posZ_4;
            arg0->field_88 = 0;
            arg0->field_8C = 0;
            arg0->field_90 = temp_a0->field_0_5;
            arg0->field_94 = temp_a0->field_0_0;
        }
    }

    for (var_t1 = &arg0->field_A8[0]; var_t1 < &arg0->field_A8[4]; var_t1++)
    {
        if (var_t1->field_1 != 0xFF)
        {
            temp_a1 = &collData->ptr_10[var_t1->field_1];

            var_a0 = temp_a1->field_2;

            if (temp_a1->field_8 != 0)
            {
                var_a0 += FP_FROM(temp_a1->field_8 * (arg0->field_98 - temp_a1->field_0), Q12_SHIFT);
            }

            if (temp_a1->field_A != 0)
            {
                var_a0 += FP_FROM(temp_a1->field_A * (arg0->field_9A - temp_a1->field_4), Q12_SHIFT);
            }

            if (var_a0 < arg0->field_7C)
            {
                arg0->field_7C = var_a0;
                arg0->field_80 = arg0->field_98 + collData->posX_0;
                arg0->field_84 = arg0->field_9A + collData->posZ_4;
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
    u8*                    var_t1;
    s_IpdCollisionData_10* ptr;

    startIdx = arg2->field_2;
    endIdx   = arg2->field_6;

    if (startIdx == endIdx)
    {
        return;
    }

    for (var_t1 = &collData->ptr_2C[startIdx]; var_t1 < &collData->ptr_2C[endIdx]; var_t1++)
    {
        ptr = &collData->ptr_10[*var_t1];

        if (((arg0->field_2 >> ptr->field_6_11) & (1 << 0)) && ptr->field_6_5 != 1)
        {
            var_a2 = ptr->field_2;

            if (ptr->field_8 != 0)
            {
                var_a2 += FP_FROM(ptr->field_8 * (arg0->field_98 - ptr->field_0), Q12_SHIFT);
            }

            if (ptr->field_A != 0)
            {
                var_a2 += FP_FROM(ptr->field_A * (arg0->field_9A - ptr->field_4), Q12_SHIFT);
            }

            if (var_a2 < arg0->field_7C)
            {
                arg0->field_7C = var_a2;
                arg0->field_80 = arg0->field_98 + collData->posX_0;
                arg0->field_84 = arg0->field_9A + collData->posZ_4;
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
        return FP_FLOAT_TO(1.0f, Q12_SHIFT);
    }

    temp_v0 = func_8006CC44(arg0->field_4.field_20, arg0->field_4.field_24, arg0);
    if ((arg0->field_4.field_2C + arg0->field_4.field_C.vy) < temp_v0 ||
        temp_v0 == arg0->field_7C)
    {
        return FP_FLOAT_TO(1.0f, Q12_SHIFT);
    }

    return FP_TO(arg0->field_4.field_8, Q12_SHIFT) / SquareRoot0(SQUARE(arg0->field_4.field_8) +
                                                                 SQUARE(temp_v0 - arg0->field_4.field_2C));
}

s32 func_8006CC44(s32 x, s32 z, s_func_8006CC44* arg2) // 0x8006CC44
{
    if (arg2->field_94 != 12)
    {
        return FP_MULTIPLY(arg2->field_88, x - arg2->field_80, Q12_SHIFT) +
               FP_MULTIPLY(arg2->field_8C, z - arg2->field_84, Q12_SHIFT) +
               arg2->field_7C;
    }

    return FP_FLOAT_TO(0.5f, Q12_SHIFT);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006CC9C); // 0x8006CC9C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006CF18); // 0x8006CF18

void func_8006D01C(VECTOR3* arg0, VECTOR3* arg1, s16 arg2, s_func_8006CC44* arg3) // 0x8006D01C
{
    VECTOR3 sp10;
    s32     temp_s0;
    s32     temp_s1;
    s32     temp_a0;
    s32     temp_v0;

    sp10.vx = FP_MULTIPLY(arg1->vx, arg2, Q12_SHIFT);
    sp10.vz = FP_MULTIPLY(arg1->vz, arg2, Q12_SHIFT);

    if (arg3->field_44  || arg3->field_74)
    {
        arg0->vx = 0;
        arg0->vz = 0;
        *arg1    = sp10;
        func_8006D2B4(arg1, &arg3->field_44, arg2);
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

    if (temp_a0 < 0x100)
    {
        temp_a0 = SquareRoot0(temp_a0 * 0x100);
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

    if (temp_s0 > 0x555)
    {
        arg0->vx += 0x10;
    }
    else if (temp_s0 < -0x555)
    {
        arg0->vx -= 0x10;
    }

    if (temp_s1 > 0x555)
    {
        arg0->vz += 0x10;
    }
    else if (temp_s1 < -0x555)
    {
        arg0->vz -= 0x10;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006D2B4); // 0x8006D2B4

void func_8006D600(VECTOR3* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x8006D600
{
    s32 temp_a2;
    s16 temp_s0;
    s16 temp_s3;
    s16 temp;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0_2;
    s32 var_v1;

    // TODO: Angles here.

    temp_s0 = FP_ALPHA_NORM(arg1);
    temp_s3 = FP_ALPHA_NORM(arg2);
    temp    = FP_ALPHA_NORM(arg3);

    if (arg4 > 0x100)
    {
        arg4 = 0x100;
    }

    temp_s6 = FP_MULTIPLY(arg4, Math_Cos(temp_s0), Q12_SHIFT);
    var_s0  = temp;
    temp_s5 = FP_MULTIPLY(arg4, Math_Sin(temp_s0), Q12_SHIFT);
    temp_s1 = arg0->vx - temp_s6;
    temp_s2 = arg0->vz - temp_s5;
    var_v1  = FP_ALPHA_NORM(ratan2(temp_s2, temp_s1));

    if (var_v1 < temp_s3)
    {
        var_v1 += 0x1000;
    }

    if (var_s0 < temp_s3)
    {
        var_s0 += 0x1000;
    }

    temp_a2 = temp_s3 + 0x1000;
    if (var_s0 < var_v1)
    {
        if (((var_s0 + temp_a2) >> 1) < var_v1)
        {
            var_s0 = temp_a2;
        }

        temp_s0_2 = Math_Sin(var_s0);
        temp_v0   = Math_Cos(var_s0);
        var_v0_2  = FP_MULTIPLY(temp_s1, temp_v0, Q12_SHIFT) + FP_MULTIPLY(temp_s2, temp_s0_2, Q12_SHIFT);

        if (var_v0_2 < 0)
        {
            var_v0_2 = 0;
        }

        arg0->vx = temp_s6 + FP_MULTIPLY(var_v0_2, temp_v0, Q12_SHIFT);
        arg0->vz = temp_s5 + FP_MULTIPLY(var_v0_2, temp_s0_2, Q12_SHIFT);
    }
}

void func_8006D774(s_func_8006CC44* arg0, VECTOR3* arg1, VECTOR3* arg2) // 0x8006D774
{
    SVECTOR sp10; // Types assumed. SVECTOR3 might also work but there are 8 bytes between sp10 and sp18 and SVECTOR3 is only 6 bytes.
    SVECTOR sp18;

    sp10.vx = FP_FROM(arg1->vx, Q4_SHIFT);
    sp10.vy = FP_FROM(arg1->vz, Q4_SHIFT);
    sp18.vx = FP_FROM(arg2->vx, Q4_SHIFT);
    sp18.vy = FP_FROM(arg2->vz, Q4_SHIFT);

    arg0->field_34 = 0;
    arg0->field_44 = 0;
    arg0->field_4A = 0;
    arg0->field_4C = 0;
    arg0->field_7A = 0;
    arg0->field_74 = 0;

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
        arg0->directionX_14 = FP_TO(arg0->field_C.vx, Q12_SHIFT) / dist;
        arg0->directionZ_16 = FP_TO(arg0->field_C.vz, Q12_SHIFT) / arg0->field_8;

        angle               = ratan2(arg0->field_C.vz, arg0->field_C.vx);
        arg0->directionX_14 = Math_Cos(angle);
        arg0->directionZ_16 = Math_Sin(angle);
    }
    else
    {
        arg0->directionX_14 = 0x1000;
        arg0->directionZ_16 = 0;
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

    if (func_8006DCE0((s32)PSX_SCRATCH, 0, 0, vec1, &vecDelta, 0, 0, 0, 0) != 0)
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
    s32 sp28;
    s32 temp_v0;
    s32 scratchPrev;
    s32 scratchAddr;

    temp_v0 = func_8006A1A4(&sp28, chara, 0);

    arg0->field_0 = false;
    if (func_8006DCE0((s32)PSX_SCRATCH, 0, 0, vec1, vec2, 0, 0, temp_v0, sp28))
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

void func_8006DAE4(s_func_800700F8_2* arg0, VECTOR3* vec1, VECTOR3* vec2, s32 arg3) // 0x8006DAE4
{
    arg0->field_0  = 0;
    arg0->field_1  = 0;
    arg0->field_4  = vec1->vx + vec2->vx;
    arg0->field_8  = vec1->vy + vec2->vy;
    arg0->field_C  = vec1->vz + vec2->vz;
    arg0->field_10 = 0;
    arg0->field_14 = arg3 * 0x10;
    arg0->field_18 = 0x1E00;
    arg0->field_1C = 0;
}

static inline void func_8006DB3C_Inline(s_func_800700F8_2* arg0, VECTOR3* arg1, VECTOR3* arg2, u16* p)
{
    func_8006DAE4(arg0, arg1, arg2, (short)*p);
}

bool func_8006DB3C(s_func_800700F8_2* arg0, VECTOR3* arg1, VECTOR3* arg2, s_SubCharacter* chara) // 0x8006DB3C
{
    s32 sp28;
    s32 temp_s0;
    s32 temp_v0;
    s32 scratchAddr;

    temp_v0       = func_8006A1A4(&sp28, chara, 1);
    arg0->field_0 = false;

    if (func_8006DCE0((s32)PSX_SCRATCH, 1, 0, arg1, arg2, 0, 0, temp_v0, sp28))
    {
        temp_s0       = SetSp((s32)PSX_SCRATCH_ADDR(984));
        scratchAddr   = (s32)PSX_SCRATCH;
        arg0->field_0 = func_8006DEB0(arg0, scratchAddr);

        SetSp(temp_s0);
    }

    if (!arg0->field_0)
    {
        func_8006DB3C_Inline(arg0, arg1, arg2, &((u8*)scratchAddr)[92]);
    }

    return arg0->field_0;
}

bool func_8006DC18(s_func_800700F8_2* arg0, VECTOR3* vec1, VECTOR3* vec2) // 0x8006DC18
{
    s32 scratchPrev;
    s32 scratchAddr;

    arg0->field_0 = false;
    if (func_8006DCE0((s32)PSX_SCRATCH, 1, 0x4C, vec1, vec2, 0, 0, 0, 0) != 0)
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

bool func_8006DCE0(s_func_8006DCE0* arg0, s32 arg1, s16 arg2, VECTOR3* pos0, VECTOR3* pos1, s32 arg5, s32 arg6, s32 arg7, s32 arg8)
{
    if (pos1->vx == 0 && pos1->vz == 0)
    {
        return false;
    }

    arg0->field_0  = arg1;
    arg0->field_4  = D_800C4478.field_0; // Struct could begin some point earlier.
    arg0->field_6  = arg2;
    arg0->field_8  = 0x7FFF;
    arg0->field_20 = 0;

    arg0->field_2C.vx = FP_METER_TO_GEO(pos0->vx);
    arg0->field_2C.vy = FP_METER_TO_GEO(pos0->vy);
    arg0->field_2C.vz = FP_METER_TO_GEO(pos0->vz);

    arg0->field_50.vx = FP_METER_TO_GEO(pos1->vx);
    arg0->field_50.vy = FP_METER_TO_GEO(pos1->vy);
    arg0->field_50.vz = FP_METER_TO_GEO(pos1->vz);

    arg0->field_3C = arg0->field_2C.vx + arg0->field_50.vx;

    // `FP_METER_TO_GEO`?
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

    arg0->field_64 = arg7;
    arg0->field_68 = arg8;

    return true;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006DEB0); // 0x8006DEB0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006E0AC); // 0x8006E0AC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006E150); // 0x8006E150

void func_8006E490(s_func_8006E490* arg0, u32 arg1, s32 arg2, s32 arg3) // 0x8006E490
{
    s32 var_a2;

    if (arg1 & (1 << 2))
    {
        var_a2 = arg2;
        arg2   = arg3;
        arg3   = var_a2;
    }

    if (arg1 & (1 << 1))
    {
        arg3 = -arg3;
    }

    if (arg1 & (1 << 0))
    {
        arg2 = -arg2;
    }

    arg2 = FP_FROM(arg2, Q12_SHIFT);
    arg3 = FP_FROM(arg3, Q12_SHIFT);
    if (arg2 >= 0 && arg2 < arg0->field_10 && arg3 >= 0 && arg3 < arg0->field_14)
    {
        arg0->field_20[arg0->field_1C].field_0 = arg2;
        arg0->field_20[arg0->field_1C].field_2 = arg3;
        arg0->field_1C++;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006E53C); // 0x8006E53C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006E78C); // 0x8006E78C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006EB8C); // 0x8006EB8C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006EE0C); // 0x8006EE0C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006EEB8); // 0x8006EEB8

void func_8006F250(s_func_8006F250* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x8006F250
{
    s32              idx;
    s_func_8006F338* scratch;

    scratch = PSX_SCRATCH;

    func_8006F338(scratch, arg1, arg2, arg3, arg4);

    for (idx = 0; idx < D_800C4478.field_2; idx++)
    {
        if (func_8006F3C4(scratch, D_800C4478.field_4[idx]) != 0)
        {
            break;
        }
    }

    if (scratch->field_28 == 0x1000)
    {
        arg0->field_0 = 0x20000;
        arg0->field_4 = -0x10000;
    }
    else
    {
        arg0->field_0 = Math_MulFixed(Vc_VectorMagnitudeCalc(scratch->field_10, 0, scratch->field_14), scratch->field_28, Q12_SHIFT);
        arg0->field_4 = scratch->field_2C;
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
    arg0->field_28 = 0x1000;
    arg0->field_2C = 0xFFFF0000;
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006F3C4); // 0x8006F3C4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006F620); // 0x8006F620

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006F8FC); // 0x8006F8FC

s16 func_8006F99C(s_SubCharacter* chara, s32 arg1, s16 arg2) // 0x8006F99C
{
    s16 var_s0;
    s16 var_s2;
    s32 i;

    var_s2 = NO_VALUE;
    for (i = 0; i < 15; i++)
    {
        if (i == 0)
        {
            var_s0 = Rng_TestProbabilityBits(6) - 32;
        }
        else if (i & 1)
        {
            var_s0 = (256 << ((i + 1) >> 1)) + Rng_TestProbabilityBits(6);
        }
        else
        {
            var_s0 = -(256 << (i >> 1)) - Rng_TestProbabilityBits(6);
        }

        if (var_s2 != NO_VALUE)
        {
            if (ABS(var_s2) < ABS(var_s0))
            {
                continue;
            }
        }

        if (!func_8007029C(chara, arg1, var_s0 + arg2))
        {
            var_s2 = var_s0;
        }
    }

    if (var_s2 != NO_VALUE)
    {
        return func_8005BF38(var_s2 + arg2);
    }

    return FP_ALPHA(1.0f);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_8006FAFC); // 0x8006FAFC

bool func_8006FD90(s_SubCharacter* chara, s32 arg1, s32 arg2, s32 arg3) // 0x8006FD90
{
    VECTOR3 sp10;
    VECTOR3 sp20;
    VECTOR3 sp30;
    VECTOR3 sp40;
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
        var0 = FP_MULTIPLY((s64)var0, var1, Q12_SHIFT);
    }

    dist = Math_Vector2MagCalc(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                               g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);
    temp = arg2 + FP_MULTIPLY((s64)arg3, var0, Q12_SHIFT);
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
        sp40.vy = (g_SysWork.player_4C.chara_0.position_18.vy + g_SysWork.player_4C.chara_0.field_CE) -
                  (chara->position_18.vy - chara->field_CE);
    }

    // Maybe sp10 is not VECTOR3. Might need to rewrite this whole function if its `s_func_800700F8_2`?
    return func_8006DA08(&sp10, &sp30, &sp40, chara) == 0 || sp20.vx != 0;
}

bool func_80070030(s_SubCharacter* chara, s32 x, s32 y, s32 z)
{
    s_func_800700F8_2 temp;
    VECTOR3           deltaPos;

    deltaPos.vx = x - chara->position_18.vx;
    deltaPos.vy = y - chara->position_18.vy;
    deltaPos.vz = z - chara->position_18.vz;

    func_8006DB3C(&temp, &chara->position_18, &deltaPos, chara);
}

bool func_80070084(s_SubCharacter* chara, s32 x, s32 y, s32 z) // 0x80070084
{
    s_func_800700F8_2 var;
    VECTOR3           deltaPos;
    bool              result;

    deltaPos.vx = x - chara->position_18.vx;
    deltaPos.vy = y - chara->position_18.vy;
    deltaPos.vz = z - chara->position_18.vz;

    result = false;
    if (func_8006DB3C(&var, &chara->position_18, &deltaPos, chara))
    {
        result = var.field_10 == 0;
    }

    return result;
}

bool func_800700F8(s_SubCharacter* chara0, s_SubCharacter* chara1) // 0x800700F8
{
    s_func_800700F8_2 sp10;
    VECTOR3           vec0;
    VECTOR3           vec1;

    vec0 = chara0->position_18;

    vec1.vx = chara1->position_18.vx - chara0->position_18.vx;
    vec1.vy = FP_METER(-0.1f);
    vec1.vz = chara1->position_18.vz - chara0->position_18.vz;

    return func_8006DB3C(&sp10, &vec0, &vec1, chara0) && sp10.field_10 == 0;
}

bool func_80070184(s_SubCharacter* chara, s32 arg1, s16 rotY) // 0x80070184
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

bool func_80070208(s_SubCharacter* chara, s32 arg1) // 0x80070208
{
    s_func_800700F8_2 var;
    VECTOR3           vec;
    bool              result;

    vec.vx = FP_MULTIPLY(arg1, Math_Sin(chara->rotation_24.vy), Q12_SHIFT);
    vec.vy = 0;
    vec.vz = FP_MULTIPLY(arg1, Math_Cos(chara->rotation_24.vy), Q12_SHIFT);

    result = false;
    if (func_8006DB3C(&var, &chara->position_18, &vec, chara) != 0)
    {
        result = var.field_10 > 0;
    }
    return result;
}

s32 func_8007029C(s_SubCharacter* chara, s32 arg1, s16 angle) // 0x8007029C
{
    s8      vars[28];
    VECTOR3 vec;

    vec.vx = FP_MULTIPLY(arg1, Math_Sin(angle), Q12_SHIFT);
    vec.vy = 0;
    vec.vz = FP_MULTIPLY(arg1, Math_Cos(angle), Q12_SHIFT);

    return func_8006DB3C(&vars, &chara->position_18, &vec, chara);
}

bool func_80070320() // 0x80070320
{
    s32 i;

    for (i = 0; i < 4; i++)
    {
        if (g_SysWork.field_2354[i] != NO_VALUE)
        {
            return true;
        }
    }

    return false;
}

s32 func_80070360(s_SubCharacter* chara, s32 someDist, s16 arg2) // 0x80070360
{
    s32 vx;
    s32 vz;
    s32 var_a1;
    s32 result;

    var_a1 = someDist;
    if (var_a1 == 0)
    {
        vx = g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx;
        vx = FP_FROM(vx, 6);

        vz = g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz;
        vz = FP_FROM(vz, 6);

        var_a1 = SquareRoot0(SQUARE(vx) + SQUARE(vz));
        var_a1 = FP_TO(var_a1, 6);
    }

    result = FP_MULTIPLY(arg2, g_SysWork.player_4C.chara_0.properties_E4.player.field_10C, Q12_SHIFT) - FP_FROM(var_a1, Q8_SHIFT);
    if (result < 0)
    {
        result = 0;
    }
    return result;
}

void func_80070400(s_SubCharacter* chara, s_func_80070400_1* arg1, s_func_80070400_1* arg2) // 0x80070400
{
    s32 alpha;
    s32 invAlpha;

    // Compute alpha.
    if (chara->model_0.anim_4.status_0 & (1 << 0))
    {
        alpha = chara->model_0.anim_4.time_4 & 0xFFF;
    }
    else
    {
        alpha = chara->model_0.anim_4.keyframeIdx1_A;
    }

    // Compute inverse alpha.
    invAlpha = FP_ALPHA(1.0f) - alpha;

    chara->field_C8         = FP_FROM((arg1->field_0 * invAlpha) + (arg2->field_0 * alpha), Q12_SHIFT);
    chara->field_CA         = FP_FROM((arg1->field_2 * invAlpha) + (arg2->field_2 * alpha), Q12_SHIFT);
    chara->field_CC         = FP_FROM((arg1->field_4 * invAlpha) + (arg2->field_4 * alpha), Q12_SHIFT);
    chara->field_CE         = FP_FROM((arg1->field_6 * invAlpha) + (arg2->field_6 * alpha), Q12_SHIFT);
    chara->field_D8.field_4 = FP_FROM((arg1->field_10 * invAlpha) + (arg2->field_10 * alpha), Q12_SHIFT);
    chara->field_D8.field_6 = FP_FROM((arg1->field_12 * invAlpha) + (arg2->field_12 * alpha), Q12_SHIFT);
    chara->field_D4         = FP_FROM((arg1->field_8 * invAlpha) + (arg2->field_8 * alpha), Q12_SHIFT);
    chara->field_D8.field_0 = FP_FROM((arg1->field_C * invAlpha) + (arg2->field_C * alpha), Q12_SHIFT);
    chara->field_D8.field_2 = FP_FROM((arg1->field_E * invAlpha) + (arg2->field_E * alpha), Q12_SHIFT);
    chara->field_D6         = FP_FROM((arg1->field_A * invAlpha) + (arg2->field_A * alpha), Q12_SHIFT);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80055028", func_800705E4); // 0x800705E4
