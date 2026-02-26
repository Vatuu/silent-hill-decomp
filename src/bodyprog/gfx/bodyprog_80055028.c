#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>
#include <psyq/libapi.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"

// ========================================
// ENVIRONMENT AND SCREEN GFX 1
// ========================================

extern s_WorldEnvWork g_WorldEnvWork;

void WorldEnv_Init(void) // 0x80055028
{
    func_80040BAC();
    func_8008D41C();

    g_WorldEnvWork.field_0  = 0;
    g_WorldEnvWork.field_20 = Q12(1.0f);

    g_WorldEnvWork.worldTintColor_28.r = 128;
    g_WorldEnvWork.worldTintColor_28.g = 128;
    g_WorldEnvWork.worldTintColor_28.b = 128;

    g_WorldEnvWork.isFogEnabled_1 = false;
    g_WorldEnvWork.field_2        = 0;

    g_WorldEnvWork.fogColor_1C.r = 255;
    g_WorldEnvWork.fogColor_1C.g = 255;
    g_WorldEnvWork.fogColor_1C.b = 255;

    g_WorldEnvWork.field_4C      = 0;
    g_WorldEnvWork.field_50      = 0;
    g_WorldEnvWork.waterZones_4  = 0;
    g_WorldEnvWork.fogIntensity_18 = 0;

    gte_SetFarColor(0, 0, 0);

    WorldEnv_FogDistanceSet(Q12(32.0f), Q12(34.0f));
}

void Gfx_2dEffectsDraw(void) // 0x800550D0
{
    s32      color0;
    s32      color2;
    PACKET*  packet;
    PACKET*  packet2;
    DR_MODE* mode;
    POLY_G4* poly;
    GsOT*    ot;

    ot = &g_OrderingTable0[g_ActiveBufferIdx];

    if (g_WorldEnvWork.field_2 != 0)
    {
        func_80041074(ot, g_WorldEnvWork.field_54, &g_WorldEnvWork.field_58, &g_WorldEnvWork.field_60);
    }

    if (g_WorldEnvWork.field_0 == 1 && g_WorldEnvWork.field_50 != 0)
    {
        func_8008D470(g_WorldEnvWork.field_50, &g_WorldEnvWork.field_58, &g_WorldEnvWork.field_60, g_WorldEnvWork.waterZones_4);
    }

    if (g_WorldEnvWork.screenBrightness_8 > 0)
    {
        poly            = (POLY_G4*)GsOUT_PACKET_P;
        mode            = (DR_MODE*)(GsOUT_PACKET_P + sizeof(POLY_G4));
        GsOUT_PACKET_P += sizeof(POLY_G4) + sizeof(DR_MODE);

        color0           = (g_WorldEnvWork.screenBrightness_8 + (g_WorldEnvWork.screenBrightness_8 << 8)) + (g_WorldEnvWork.screenBrightness_8 << 16);
        *(s32*)&poly->r3 = color0;
        *(s32*)&poly->r2 = color0;
        *(s32*)&poly->r1 = color0;
        *(s32*)&poly->r0 = color0;

        setPolyG4(poly);
        setSemiTrans(poly, true);
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
    AddPrim(&ot->org[ORDERING_TABLE_SIZE - 1], packet2);

    poly           = (POLY_G4*)(packet + 0xC);
    GsOUT_PACKET_P = packet + 0x30;

    color2           = *(s32*)&g_WorldEnvWork.fogColor_1C;
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

    AddPrim(&ot->org[ORDERING_TABLE_SIZE - 1], poly);
    packet = GsOUT_PACKET_P;
    SetPriority(packet, 0, 1);
    AddPrim(&ot->org[ORDERING_TABLE_SIZE - 1], packet);

    GsOUT_PACKET_P = packet + sizeof(DR_MODE);
    mode           = (DR_MODE*)GsOUT_PACKET_P;

    SetDrawMode(mode, 0, 1, 32, NULL);
    AddPrim(&ot->org[ORDERING_TABLE_SIZE - 1], mode);

    GsOUT_PACKET_P = packet + 24;
}

void func_80055330(u8 arg0, s32 arg1, u8 arg2, s32 tintR, s32 tintG, s32 tintB, q23_8 brightness) // 0x80055330
{
    g_WorldEnvWork.field_0             = arg0;
    g_WorldEnvWork.field_20            = arg1;
    g_WorldEnvWork.field_3             = arg2;
    g_WorldEnvWork.worldTintColor_28.r = tintR >> 5;
    g_WorldEnvWork.field_2C.m[0][2]    = tintR;
    g_WorldEnvWork.field_2C.m[0][1]    = tintR;
    g_WorldEnvWork.field_2C.m[0][0]    = tintR;
    g_WorldEnvWork.worldTintColor_28.g = tintG >> 5;
    g_WorldEnvWork.screenBrightness_8  = brightness;
    g_WorldEnvWork.worldTintColor_28.b = tintB >> 5;
    g_WorldEnvWork.field_2C.m[1][2]    = (s16)tintG;
    g_WorldEnvWork.field_2C.m[1][1]    = (s16)tintG;
    g_WorldEnvWork.field_2C.m[1][0]    = (s16)tintG;
    g_WorldEnvWork.field_2C.m[2][2]    = (s16)tintB;
    g_WorldEnvWork.field_2C.m[2][1]    = (s16)tintB;
    g_WorldEnvWork.field_2C.m[2][0]    = (s16)tintB;
    g_WorldEnvWork.field_24            = (tintR * arg1) >> 17;
    g_WorldEnvWork.field_25            = (tintG * arg1) >> 17;
    g_WorldEnvWork.field_26            = (tintB * arg1) >> 17;
}

void WorldEnv_FogParamsSet(u8 isFogEnabled, u8 fogColorR, u8 fogColorG, u8 fogColorB) // 0x800553C4
{
    g_WorldEnvWork.isFogEnabled_1 = isFogEnabled;
    g_WorldEnvWork.fogColor_1C.r  = fogColorR;
    g_WorldEnvWork.fogColor_1C.g  = fogColorG;
    g_WorldEnvWork.fogColor_1C.b  = fogColorB;
}

void func_800553E0(u32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6) // 0x800553E0
{
    g_WorldEnvWork.field_2 = arg0;

    if (arg0 != 0)
    {
        func_80040E7C(arg1, arg2, arg3, arg4, arg5, arg6);
    }
}

void func_80055434(VECTOR3* vec) // 0x80055434
{
    *vec = g_WorldEnvWork.field_60;
}

s32 func_8005545C(SVECTOR* vec) // 0x8005545C
{
    *vec = g_WorldEnvWork.field_6C;
    return g_WorldEnvWork.field_54;
}

s32 func_80055490(SVECTOR* arg0) // 0x80055490
{
    *arg0 = g_WorldEnvWork.field_58;
    return g_WorldEnvWork.field_54;
}

void func_800554C4(s32 arg0, s16 arg1, GsCOORDINATE2* coord0, GsCOORDINATE2* coord1, SVECTOR* rot, q19_12 x, q19_12 y, q19_12 z, s_WaterZone* waterZones) // 0x800554C4
{
    MATRIX   mat;
    SVECTOR  tempSvec;
    VECTOR   vec;
    VECTOR3* pos0; // Q19.12
    VECTOR3* pos1; // Q19.12

    g_WorldEnvWork.field_54 = arg0;
    g_WorldEnvWork.field_50 = arg1;
    g_WorldEnvWork.waterZones_4  = waterZones;

    if (coord0 == NULL)
    {
        g_WorldEnvWork.field_58 = *rot;
    }
    else
    {
        Vw_CoordHierarchyMatrixCompute(coord0, &mat);
        ApplyMatrixSV(&mat, rot, &g_WorldEnvWork.field_58);
    }

    if (coord1 == NULL)
    {
        pos0     = &g_WorldEnvWork.field_60;
        pos0->vx = x;
        pos0->vy = y;
        pos0->vz = z;
    }
    else
    {
        Vw_CoordHierarchyMatrixCompute(coord1, &mat);

        tempSvec.vx = Q12_TO_Q8(x);
        tempSvec.vy = Q12_TO_Q8(y);
        tempSvec.vz = Q12_TO_Q8(z);

        ApplyMatrix(&mat, &tempSvec, &vec);

        pos1     = &g_WorldEnvWork.field_60;
        pos1->vx = Q8_TO_Q12(vec.vx + mat.t[0]);
        pos1->vy = Q8_TO_Q12(vec.vy + mat.t[1]);
        pos1->vz = Q8_TO_Q12(vec.vz + mat.t[2]);
    }

    vwVectorToAngle(&g_WorldEnvWork.field_6C, &g_WorldEnvWork.field_58);
    g_WorldEnvWork.field_4C = arg0 >> 8;
    func_80055648(arg0, &g_WorldEnvWork.field_58);
}

void func_80055648(s32 arg0, SVECTOR* arg1) // 0x80055648
{
    s32            var_a2;
    s32            temp_lo;
    s32            temp_t1;
    s32            temp_v0;
    s32            temp_v1;
    s32            j;
    s32            i;
    s_WorldEnvWork_84* ptr;

    for (i = 0, ptr = g_WorldEnvWork.field_84; i < 3; i++, ptr++)
    {
        switch (i)
        {
            case 0:
                var_a2 = arg1->vx;
                break;

            case 1:
                var_a2 = arg1->vy;
                break;

            case 2:
                var_a2 = arg1->vz;
                break;

            default:
                var_a2 = 0;
                break;
        }

        temp_t1 = Q12(var_a2 + Q12(1.3f)) / Q12(2.3f);
        temp_v1 = Q12(Q12(1.3f) - var_a2) / Q12(2.3f);
        temp_v0 = Q12(1024.0f) / temp_t1;
        temp_lo = Q12(1024.0f) / temp_v1;

        for (j = 0; j < ARRAY_SIZE(D_800AE1B4); j++)
        {
            ptr->field_0[0][j].vy = ptr->field_0[1][j].vy = Q12_MULT(D_800AE1B4[j].vy, arg0);
            ptr->field_0[0][j].vx                         = Q12_MULT(D_800AE1B4[j].vx, temp_t1);
            ptr->field_0[1][j].vx                         = Q12_MULT(D_800AE1B4[j].vx, temp_v1);
            ptr->field_0[0][j].vz                         = Q12_MULT(FP_MULTIPLY(D_800AE1B4[j].vz, temp_v0, Q12_SHIFT - 2), arg0);
            ptr->field_0[1][j].vz                         = Q12_MULT(FP_MULTIPLY(D_800AE1B4[j].vz, temp_lo, Q12_SHIFT - 2), arg0);
        }
    }
}

s32 func_800557DC(void) // 0x800557DC
{
    MATRIX mat;

    func_80049C2C(&mat, g_WorldEnvWork.field_60.vx, g_WorldEnvWork.field_60.vy, g_WorldEnvWork.field_60.vz);
    return Q8_TO_Q12(mat.t[2]);
}

void func_80055814(s32 arg0) // 0x80055814
{
    g_WorldEnvWork.fogIntensity_18 = Q12(1.0f) - func_800559A8(arg0);
}

void WorldEnv_FogDistanceSet(q19_12 nearDist, q19_12 farDist) // 0x80055840
{
    s32 temp_lo;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;
    s32 var_v1;
    s32 temp;

    nearDist = Q12_TO_Q8(nearDist);

    g_WorldEnvWork.fogNearDistance_C = nearDist;
    g_WorldEnvWork.fogFarDistance_10 = Q12_TO_Q8(farDist);
    g_WorldEnvWork.fogDepthShift_14  = 0x20 - Lzc(nearDist - 1);

    temp = (0x10 << (g_WorldEnvWork.fogDepthShift_14 + 1)) / nearDist;
    for (var_t0 = 0, var_a3 = 0; var_t0 < Q12(1.0f) && var_a3 < 0x80; var_t0 += temp, var_a3++)
    {
        temp_v1_2 = var_t0 >> 8;

        if (temp_v1_2 == 0)
        {
            var_a1 = 0x80;
            var_a2 = var_t0 & 0x7F;
            if (var_t0 & 0x80)
            {
                var_v1 = D_800AE1C0[0];
                var_a0 = 0;
            }
            else
            {
                var_a0 = D_800AE1C0[0];
                var_v1 = D_800AE1C0[1];
            }
        }
        else
        {
            var_a1 = 0x100;
            var_a2 = var_t0 & 0xFF;
            var_a0 = D_800AE1C0[temp_v1_2];
            var_v1 = D_800AE1C0[temp_v1_2 + 1];
        }

        temp_lo = (var_a0 * (var_a1 - var_a2) + var_v1 * var_a2) / var_a1;

        limitRange(temp_lo, 0, 0xFF);

        g_WorldEnvWork.fogRamp_CC[var_a3] = (u8)temp_lo;
    }

    for (; var_a3 < 0x80; var_a3++)
    {
        g_WorldEnvWork.fogRamp_CC[var_a3] = 0xFF;
    }
}

s32 func_800559A8(s32 arg0) // 0x800559A8
{
    s32 temp_a2;
    s32 temp_lo;
    s32 temp_v0;
    s32 var_a1;
    s32 var_v0;

    temp_v0 = 1 << g_WorldEnvWork.fogDepthShift_14;
    var_a1  = temp_v0 >> 7;

    if (temp_v0 < 0)
    {
        var_a1 = (temp_v0 + 0x7F) >> 7;
    }

    temp_v0 = arg0 >> 4;
    temp_lo = temp_v0 / var_a1;

    if (temp_lo < 0)
    {
        return 0;
    }

    if (temp_lo >= 0x80)
    {
        return Q12(1.0f);
    }

    temp_a2 = g_WorldEnvWork.fogRamp_CC[temp_lo] * 16;
    var_v0  = temp_v0 % var_a1;

    if (temp_lo == 0x7F)
    {
        temp_v0 = Q12(1.0f);
    }
    else
    {
        temp_v0 = g_WorldEnvWork.fogRamp_CC[temp_lo + 1] * 16;
    }

    return temp_a2 + ((temp_v0 - temp_a2) * var_v0) / var_a1;
}

u8 func_80055A50(s32 arg0) // 0x80055A50
{
    s32 temp;

    temp = arg0 >> 4;

    if (temp >= (1 << g_WorldEnvWork.fogDepthShift_14))
    {
        return 255;
    }

    return g_WorldEnvWork.fogRamp_CC[(temp << 7) >> g_WorldEnvWork.fogDepthShift_14];
}

void func_80055A90(CVECTOR* arg0, CVECTOR* arg1, u8 arg2, s32 arg3) // 0x80055A90
{
    s32 var_v1;

    // TODO: Maybe Q8 to Q12 and back again.
    arg3 = arg3 >> 4;
    if (arg3 < 0)
    {
        arg3 = 0;
    }

    if (arg3 < (1 << g_WorldEnvWork.fogDepthShift_14))
    {
        arg3 = g_WorldEnvWork.fogRamp_CC[(arg3 << 7) >> g_WorldEnvWork.fogDepthShift_14] << 4;
    }
    else
    {
        arg3 = 0xFF << 4;
    }

    var_v1 = Q12(1.0f) - (g_WorldEnvWork.fogIntensity_18 + arg3);
    if (var_v1 < 0)
    {
        var_v1 = 0;
    }

    gte_lddp(var_v1);
    gte_ldrgb(&g_WorldEnvWork.fogColor_1C);

    gte_SetFarColor(0, 0, 0);

    gte_dpcs();

    gte_strgb(arg0);

    gte_lddp(arg3);
    gte_ldrgb(&g_WorldEnvWork.worldTintColor_28);

    gte_ldsv_(arg2 << 5);

    gte_dpcl();

    gte_strgb(arg1);
}

void func_80055B74(CVECTOR* result, CVECTOR* color, s32 arg2) // 0x80055B74
{
    s32 var_v0;
    s32 var_t0;

    arg2 >>= 4;

    var_t0 = g_WorldEnvWork.field_20 >> 5;

    if (arg2 < (1 << g_WorldEnvWork.fogDepthShift_14))
    {
        var_v0 = g_WorldEnvWork.fogRamp_CC[(arg2 << 7) >> g_WorldEnvWork.fogDepthShift_14];
    }
    else
    {
        var_v0 = 255;
    }

    var_v0 <<= 4;

    gte_lddp(var_v0);
    gte_ldrgb(color);
    gte_SetFarColor(g_WorldEnvWork.fogColor_1C.r, g_WorldEnvWork.fogColor_1C.g, g_WorldEnvWork.fogColor_1C.b);
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

    if (g_WorldEnvWork.isFogEnabled_1)
    {
        if (var_s0 < (1 << g_WorldEnvWork.fogDepthShift_14))
        {
            var_v0 = g_WorldEnvWork.fogRamp_CC[(var_s0 << 7) >> g_WorldEnvWork.fogDepthShift_14];
        }
        else
        {
            var_v0 = 255;
        }

        gte_lddp(var_v0 << 4);
        gte_ldrgb(color);
        gte_SetFarColor(g_WorldEnvWork.fogColor_1C.r, g_WorldEnvWork.fogColor_1C.g, g_WorldEnvWork.fogColor_1C.b);
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

u8 func_80055D78(q19_12 posX, q19_12 posY, q19_12 posZ) // 0x80055D78
{
    q23_8    pos[3];
    s32      temp_v1;
    q23_8    tempX;
    s32      var_a3;
    s32      i;
    VECTOR3* ptr0;
    VECTOR3* ptr1;

    pos[0] = Q12_TO_Q8(posX) - Q12_TO_Q8(g_WorldEnvWork.field_60.vx);
    pos[1] = Q12_TO_Q8(posY) - Q12_TO_Q8(g_WorldEnvWork.field_60.vy);
    pos[2] = Q12_TO_Q8(posZ) - Q12_TO_Q8(g_WorldEnvWork.field_60.vz);

    if (g_WorldEnvWork.field_0 != 0)
    {
        ptr1 = &g_WorldEnvWork.field_84;
        for (i = 0, ptr0 = ptr1, var_a3 = 0xFF;
             i < ARRAY_SIZE(pos);
             i++, ptr0 += 2)
        {
            tempX = pos[i];
            ptr1  = ptr0;
            if (tempX < 0)
            {
                tempX = -tempX;
                ptr1++;
            }

            temp_v1 = ptr1->vy + Q12_MULT(ptr1->vz, tempX - ptr1->vx);
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

    var_a3 += g_WorldEnvWork.field_20 >> 5;

    limitRange(var_a3, 0, g_WorldEnvWork.field_3);
    return var_a3;
}

void func_80055E90(CVECTOR* color, u8 fadeAmount) // 0x80055E90
{
    q19_12 alpha;
    u8     prev_cd;

    alpha = Q12(1.0f) - (fadeAmount * 32);

    // Works similar to `gte_DpqColor` macro, but `gte_lddp`/`gte_ldrgb` are in wrong order?

    gte_lddp(alpha);
    gte_ldrgb(&g_WorldEnvWork.worldTintColor_28);
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

    func_80057228(mat, g_WorldEnvWork.field_54, &g_WorldEnvWork.field_58, &g_WorldEnvWork.field_60);

    gte_lddqa(g_WorldEnvWork.field_4C);
    gte_lddqb_0();
    gte_ldtr_0();

    ReadGeomOffset(&geomOffsetX, &geomOffsetY);
    geomScreen = ReadGeomScreen();
    SetGeomOffset(-1024, -1024);
    SetGeomScreen(16);

    rotMat.m[0][0] = g_WorldEnvWork.field_74.vx;
    rotMat.m[0][1] = g_WorldEnvWork.field_74.vy;
    rotMat.m[0][2] = g_WorldEnvWork.field_74.vz;
    rotMat.m[1][0] = -arg1->vx;
    rotMat.m[1][1] = -arg1->vy;
    rotMat.m[1][2] = -arg1->vz;
    rotMat.m[2][0] = arg0->vx - g_WorldEnvWork.field_7C.vx;
    rotMat.m[2][1] = arg0->vy - g_WorldEnvWork.field_7C.vy;
    rotMat.m[2][2] = arg0->vz - g_WorldEnvWork.field_7C.vz;

    field_3  = g_WorldEnvWork.field_3;
    field_20 = g_WorldEnvWork.field_20 >> 5;

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

// ========================================
// WORLD INITIALIZATION 2
// ========================================

void LmHeader_FixOffsets(s_LmHeader* lmHdr) // 0x800560FC
{
    s32 i;

    if (lmHdr->isLoaded_2 == true)
    {
        return;
    }
    lmHdr->isLoaded_2 = true;

    // Add memory address of header to pointer fields.
    lmHdr->materials_4   = (u8*)lmHdr->materials_4   + (u32)lmHdr;
    lmHdr->modelHdrs_C   = (u8*)lmHdr->modelHdrs_C   + (u32)lmHdr;
    lmHdr->modelOrder_10 = (u8*)lmHdr->modelOrder_10 + (u32)lmHdr;

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

void Lm_TransparentPrimSet(s_LmHeader* lmHdr, bool transparency) // 0x80056244
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
                prim->field_6.bits.field_6_15 = transparency;
            }
        }
    }
}

s32 Lm_MaterialCountGet(bool (*filterFunc)(s_Material* mat), s_LmHeader* lmHdr) // 0x80056348
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

void Lm_MaterialFileIdxApply(s_LmHeader* lmHdr, e_FsFile fileIdx, s_FsImageDesc* image, s32 blendMode) // 0x80056464
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

void Lm_MaterialFsImageApply1(s_LmHeader* lmHdr, char* newStr, s_FsImageDesc* image, s32 blendMode) // 0x80056504
{
    char strCpy[8];

    StringCopy(strCpy, newStr);
    Lm_MaterialFsImageApply(lmHdr, strCpy, image, blendMode);
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

void Lm_MaterialsLoadWithFilter(s_LmHeader* lmHdr, s_ActiveTextures* activeTexs, bool (*filterFunc)(s_Material* mat), e_FsFile fileIdx, s32 blendMode) // 0x80056774
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
    s32         matFlags;
    s_Material* curMat;

    for (i = 0, curMat = lmHdr->materials_4; i < lmHdr->materialCount_3; i++, curMat++)
    {
        matFlags = (curMat->field_E != curMat->field_F) ? MaterialFlag_0 : MaterialFlag_None;

        if (curMat->field_10 != curMat->field_12)
        {
            matFlags |= MaterialFlag_1;
        }
        if (curMat->field_14.u16 != curMat->field_16.u16)
        {
            matFlags |= MaterialFlag_2;
        }

        if (matFlags != 0)
        {
            for (j = 0; j < lmHdr->modelCount_8; j++)
            {
                if (lmHdr->magic_0 == LM_HEADER_MAGIC)
                {
                    Model_MaterialFlagsApply(&lmHdr->modelHdrs_C[j], i, curMat, matFlags);
                }
            }

            curMat->field_F        = curMat->field_E;
            curMat->field_12       = curMat->field_10;
            curMat->field_16.u8[0] = curMat->field_14.u8[0];
            curMat->field_16.u8[1] = curMat->field_14.u8[1];
        }
    }
}

void Model_MaterialFlagsApply(s_ModelHeader* modelHdr, s32 arg1, s_Material* mat, s32 matFlags) // 0x80056A88
{
    u16           field_14;
    u16           field_16;
    s_MeshHeader* curMeshHdr;
    s_Primitive*  curPrim;

    // Run through meshes.
    for (curMeshHdr = modelHdr->meshHdrs_C; curMeshHdr < &modelHdr->meshHdrs_C[modelHdr->meshCount_8]; curMeshHdr++)
    {
        // Run through primitives.
        for (curPrim = curMeshHdr->primitives_4; curPrim < &curMeshHdr->primitives_4[curMeshHdr->primitiveCount_0]; curPrim++)
        {
            // No material(?).
            if (curPrim->field_6.bits.field_6_8 == NO_VALUE)
            {
                curPrim->field_6.bits.field_6_0 = 32;
            }

            // Apply material flags.
            if (curPrim->field_6.bits.field_6_8 == arg1)
            {
                if (matFlags & MaterialFlag_0)
                {
                    curPrim->field_6.bits.field_6_0 = mat->field_E;
                }
                if (matFlags & MaterialFlag_1)
                {
                    curPrim->field_2 = mat->field_10 + (curPrim->field_2 - mat->field_12);
                }
                if (matFlags & MaterialFlag_2)
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

    // Run through materials.
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

bool Lm_ModelFind(s_WorldObjectModel* arg0, s_LmHeader* lmHdr, s_WorldObjectMetadata* metadata) // 0x80056CB4
{
    u_Filename     sp10;
    s32            modelHdrCount;
    bool           result;
    s32            i;
    s_ModelHeader* modelHdr;

    result = false;

    StringCopy(sp10.str, metadata->name_0.str);

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

// ========================================
// ENVIRONMENT AND SCREEN GFX 2 (Drawing?)
// ========================================

void func_80056D8C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, GsOT* arg6, s32 arg7) // 0x80056D8C
{
    s16       var_a3;
    s16       var_a3_2;
    s16       var_v1;
    s16       var_v1_2;
    s32       temp_a0_2;
    s32       var_s0;
    s32       var_t1;
    s32       var_v0;
    s32       var_v1_3;
    s32       var_v1_4;
    POLY_G4*  poly;
    DR_MODE*  mode;
    PACKET*   packet;
    PACKET*   packet2;
    GsOT_TAG* tag;
    s16       temp_s6;
    s16       temp_s5;

    var_t1  = arg4;
    temp_s5 = arg3;

    if (!g_WorldEnvWork.isFogEnabled_1)
    {
        return;
    }

    var_a3 = MAX(arg0, ~(g_GameWork.gsScreenWidth_588 >> 1));
    var_v1 = MAX(arg1, ~(g_GameWork.gsScreenHeight_58A >> 1));

    var_v1_2 = CLAMP_HIGH(arg2, (g_GameWork.gsScreenWidth_588 >> 1) + 1);
    temp_s6  = var_v1_2;

    var_a3_2 = CLAMP_HIGH(temp_s5, (g_GameWork.gsScreenHeight_58A >> 1) + 1);
    temp_s5  = var_a3_2;

    temp_a0_2 = 0x79C << (arg7 + 2);

    if (g_WorldEnvWork.isFogEnabled_1)
    {
        var_v1_3 = MIN(temp_a0_2, g_WorldEnvWork.fogFarDistance_10);
    }
    else
    {
        var_v1_3 = temp_a0_2;
    }

    var_v0 = var_t1 >> 4;

    if (var_v0 < (var_v1_3 + 0x300))
    {
        if (var_t1 < 0)
        {
            var_t1 = 0;
        }

        var_s0 = (func_80055A50(var_t1) * 16) + g_WorldEnvWork.fogIntensity_18;
        var_s0 = MIN(var_s0, 0x1000);

        var_v1_4 = MAX(arg5 >> 7, 1);

        packet = GsOUT_PACKET_P;
        tag    = &arg6->org[var_v1_4];

        SetPriority(packet, 0, 0);
        AddPrim(tag, packet);

        poly           = (POLY_G4*)(packet + 0xC);
        GsOUT_PACKET_P = (PACKET*)poly;

        *(u32*)&poly->r0 =
        *(u32*)&poly->r1 =
        *(u32*)&poly->r2 =
        *(u32*)&poly->r3 = Q12_MULT(g_WorldEnvWork.fogColor_1C.r, var_s0)       +
                           (Q12_MULT(g_WorldEnvWork.fogColor_1C.g, var_s0) << 8) +
                           (Q12_MULT(g_WorldEnvWork.fogColor_1C.b, var_s0) << 16);

        SetPolyG4(poly);

        *(s32*)&poly->x0 = var_a3 + (var_v1 << 16);
        *(s32*)&poly->x1 = temp_s6 + (var_v1 << 16);
        *(s32*)&poly->x2 = var_a3 + (temp_s5 << 16);
        *(s32*)&poly->x3 = temp_s6 + (temp_s5 << 16);

        setSemiTrans(poly, true);
        AddPrim(tag, poly);

        mode           = (DR_MODE*)(packet + 0x30);
        GsOUT_PACKET_P = (PACKET*)mode;
        SetDrawMode(mode, 0, 1, 32, NULL);
        AddPrim(tag, mode);

        packet2        = packet + 60;
        GsOUT_PACKET_P = packet2;
        SetPriority(packet2, 1, 1);
        AddPrim(tag, packet2);

        GsOUT_PACKET_P = packet + 72;
    }
}

void func_80057090(s_ModelInfo* modelInfo, GsOT* arg1, s32 arg2, MATRIX* mat0, MATRIX* mat1, u16 arg5) // 0x80057090
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
        if (mat1 != NULL && g_WorldEnvWork.field_0 != 0)
        {
            func_80057228(mat1, g_WorldEnvWork.field_54, &g_WorldEnvWork.field_58, &g_WorldEnvWork.field_60);
        }

        if (modelHdr->field_B_0)
        {
            g_WorldEnvWork.field_14C = arg5;
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
    q23_8 posX;
    q23_8 posY;
    q23_8 posZ;

    gte_SetRotMatrix_custom(mat);

    gte_ldv0(arg2);
    gte_rtv0();
    gte_lddp(alpha);
    gte_gpf12();
    gte_stsv(&g_WorldEnvWork.field_74);

    // Divide `arg3` by 16 and subtract matrix translation.
    posX = Q12_TO_Q8(arg3->vx) - mat->t[0];
    posY = Q12_TO_Q8(arg3->vy) - mat->t[1];
    posZ = Q12_TO_Q8(arg3->vz) - mat->t[2];

    gte_LoadVector0_XYZ(posX, posY, posZ);
    gte_rtv0();
    gte_stsv(&g_WorldEnvWork.field_7C);
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

    gte_lddqa(g_WorldEnvWork.field_4C);
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

        switch (g_WorldEnvWork.field_0)
        {
            case 0:
                break;

            case 1:
                func_80057658(curMeshHdr, normalOffset, scratchData, &g_WorldEnvWork.field_74, &g_WorldEnvWork.field_7C);
                break;

            case 2:
                func_80057A3C(curMeshHdr, normalOffset, scratchData, &g_WorldEnvWork.field_74);
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

    scratchData->field_380.field_0.m[0][0] = arg3->vx;
    scratchData->field_380.field_0.m[0][1] = arg3->vy;
    scratchData->field_380.field_0.m[0][2] = arg3->vz;

    gte_ldtr_0();

    ReadGeomOffset(&geomOffsetX, &geomOffsetY);
    geomScreen = ReadGeomScreen();
    SetGeomOffset(-1024, -1024);
    SetGeomScreen(16);

    temp_t9 = g_WorldEnvWork.field_20 >> 5;
    temp_v1 = g_WorldEnvWork.field_3;

    var_t0 = &scratchData->field_2B8[offset];
    mat    = &scratchData->field_380.field_0;

    for (curNormal = meshHdr->normals_10; curNormal < &meshHdr->normals_10[meshHdr->normalCount_2]; curNormal++)
    {
        temp_t8   = &scratchData->field_380.field_0.m[2][0];
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

    scratchData->field_380.field_0.m[0][0] = lightVec->vx;
    scratchData->field_380.field_0.m[0][1] = lightVec->vy;
    scratchData->field_380.field_0.m[0][2] = lightVec->vz;
    gte_SetLightMatrix(&scratchData->field_380.field_0);

    var_a3  = &scratchData->field_2B8[offset];
    temp_t2 = g_WorldEnvWork.field_20;

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

void func_80057B7C(s_MeshHeader* meshHdr, s32 offset, s_GteScratchData* scratchData, MATRIX* mat) // 0x80057B7C
{
    DVECTOR* screenXy;
    s16*     temp_a2;
    s32      temp_s2;
    u8*      var_t1;

    temp_s2 = g_WorldEnvWork.fogDepthShift_14;

    SetRotMatrix(mat);
    SetTransMatrix(mat);

    screenXy = &scratchData->screenXy_0[offset];

    *(s32*)&scratchData->field_380.field_0.m[0][0] = *(s32*)&screenXy[0];
    *(s32*)&scratchData->field_380.field_0.m[1][1] = *(s32*)&screenXy[1];
    *(s32*)&scratchData->field_380.field_0.m[2][2] = *(s32*)&screenXy[2];

    temp_a2 = &scratchData->field_18C[offset];

    scratchData->field_380.field_0.m[0][2]      = temp_a2[0];
    scratchData->field_380.field_0.m[2][0]      = temp_a2[1];
    *(s16*)&scratchData->field_380.field_0.t[0] = temp_a2[2];

    var_t1 = &scratchData->field_252[offset];

    gte_ldv3c(&scratchData->field_380.field_0);
    gte_rtpt();
    gte_stsxy3c(screenXy);
    gte_stsz3(&scratchData->field_380.field_0.m[0][2], &scratchData->field_380.field_0.m[2][0], &scratchData->field_380.field_0.t[0]);

    temp_a2[0] = scratchData->field_380.field_0.m[0][2];
    temp_a2[1] = scratchData->field_380.field_0.m[2][0];
    temp_a2[2] = scratchData->field_380.field_0.t[0];

    screenXy += 3;
    var_t1  += 3;
    temp_a2 += 3;

    if (g_WorldEnvWork.isFogEnabled_1)
    {
        for (;
             screenXy < &scratchData->screenXy_0[meshHdr->vertexCount_1 + offset];
             screenXy += 3, temp_a2 += 3, var_t1 += 3)
        {
            *(s32*)&scratchData->field_380.field_0.m[0][0] = *(s32*)&screenXy[0];
            *(s32*)&scratchData->field_380.field_0.m[1][1] = *(s32*)&screenXy[1];
            *(s32*)&scratchData->field_380.field_0.m[2][2] = *(s32*)&screenXy[2];

            scratchData->field_380.field_0.m[0][2]      = temp_a2[0];
            scratchData->field_380.field_0.m[2][0]      = temp_a2[1];
            *(s16*)&scratchData->field_380.field_0.t[0] = temp_a2[2];

            gte_ldv3c(&scratchData->field_380.field_0);
            gte_rtpt();

            var_t1[-3] = temp_a2[-3] < (1 << temp_s2) ? g_WorldEnvWork.fogRamp_CC[(temp_a2[-3] << 7) >> temp_s2] : 0xFF;
            var_t1[-2] = temp_a2[-2] < (1 << temp_s2) ? g_WorldEnvWork.fogRamp_CC[(temp_a2[-2] << 7) >> temp_s2] : 0xFF;
            var_t1[-1] = temp_a2[-1] < (1 << temp_s2) ? g_WorldEnvWork.fogRamp_CC[(temp_a2[-1] << 7) >> temp_s2] : 0xFF;

            gte_stsxy3c(screenXy);
            gte_stsz3(&scratchData->field_380.field_0.m[0][2], &scratchData->field_380.field_0.m[2][0], &scratchData->field_380.field_0.t[0]);

            temp_a2[0] = scratchData->field_380.field_0.m[0][2];
            temp_a2[1] = scratchData->field_380.field_0.m[2][0];
            temp_a2[2] = scratchData->field_380.field_0.t[0];
        }

        var_t1[-3] = temp_a2[-3] < (1 << temp_s2) ? g_WorldEnvWork.fogRamp_CC[(temp_a2[-3] << 7) >> temp_s2] : 0xFF;
        var_t1[-2] = temp_a2[-2] < (1 << temp_s2) ? g_WorldEnvWork.fogRamp_CC[(temp_a2[-2] << 7) >> temp_s2] : 0xFF;
        var_t1[-1] = temp_a2[-1] < (1 << temp_s2) ? g_WorldEnvWork.fogRamp_CC[(temp_a2[-1] << 7) >> temp_s2] : 0xFF;
    }
    else
    {
        for (; screenXy < &scratchData->screenXy_0[meshHdr->vertexCount_1 + offset]; screenXy += 3, temp_a2 += 3)
        {
            *(s32*)&scratchData->field_380.field_0.m[0][0] = *(s32*)&screenXy[0];
            *(s32*)&scratchData->field_380.field_0.m[1][1] = *(s32*)&screenXy[1];
            *(s32*)&scratchData->field_380.field_0.m[2][2] = *(s32*)&screenXy[2];

            scratchData->field_380.field_0.m[0][2]      = temp_a2[0];
            scratchData->field_380.field_0.m[2][0]      = temp_a2[1];
            *(s16*)&scratchData->field_380.field_0.t[0] = temp_a2[2];

            gte_ldv3c(&scratchData->field_380.field_0);
            gte_rtpt();
            gte_stsxy3c(screenXy);
            gte_stsz3(&scratchData->field_380.field_0.m[0][2], &scratchData->field_380.field_0.m[2][0], &scratchData->field_380.field_0.t[0]);

            temp_a2[0] = scratchData->field_380.field_0.m[0][2];
            temp_a2[1] = scratchData->field_380.field_0.m[2][0];
            temp_a2[2] = scratchData->field_380.field_0.t[0];
        }
    }
}

void func_8005801C(s_MeshHeader* meshHdr, s_GteScratchData* scratchData, GsOT_TAG* tag, s32 arg3) // 0x8005801C
{
    s32          sp10;
    s32          sp14;
    s32          sp18;
    s32          sp1C;
    s32          sp20;
    s32          var_t3;
    s32          var_t3_2;
    s32          temp_a2;
    s32          temp_a2_3;
    s32          temp_a2_4;
    s32          temp_a2_5;
    s32          temp_a2_7;
    s32          temp_a0;
    s32          temp_a0_13;
    s32          temp_a0_5;
    s32          temp_a0_7;
    s32          temp_a0_9;
    s32          temp_a1;
    s32          temp_a1_2;
    s32          temp_a1_3;
    s32          temp_a1_4;
    s32          temp_a1_5;
    s32          temp_a2_2;
    s32          temp_a2_6;
    s32          temp_a3;
    s32          temp_a3_2;
    s32          temp_a3_3;
    s32          temp_a3_4;
    s32          temp_a3_5;
    s32          temp_v1;
    s32          temp_v1_11;
    s32          temp_v1_16;
    s32          temp_v1_21;
    s32          temp_v1_27;
    s32          temp_v1_5;
    u32          temp_t0;
    u32          temp_t0_2;
    u32          temp_t0_3;
    u32          temp_t0_4;
    u32          temp_t0_5;
    s32          temp;
    s32          temp2;
    s32          temp3;
    s32          temp4;
    s_Primitive* prim;
    PACKET*      packet0;
    PACKET*      packet1;
    POLY_GT4*    poly0;
    POLY_G4*     poly1;
    POLY_G4*     poly2;
    POLY_GT4*    poly3;
    POLY_FT4*    poly4;

    temp_v1 = 0x79C << (arg3 + 2);

    if (!g_WorldEnvWork.isFogEnabled_1)
    {
        scratchData->field_380.s_0.field_1C = temp_v1;
    }
    else
    {
        scratchData->field_380.s_0.field_1C = g_WorldEnvWork.fogFarDistance_10;

        if (temp_v1 < scratchData->field_380.s_0.field_1C)
        {
            scratchData->field_380.s_0.field_1C = temp_v1;
        }
    }

    scratchData->field_380.s_0.field_0    = g_GameWork.gsScreenWidth_588 >> 1;
    scratchData->field_380.s_0.field_4    = g_WorldEnvWork.fogIntensity_18;
    scratchData->field_380.s_0.field_8    = g_WorldEnvWork.worldTintColor_28;
    scratchData->field_380.s_0.field_8.cd = 0x3C;

    if (g_WorldEnvWork.field_0 == 0)
    {
        gte_lddp(0x1000 - g_WorldEnvWork.field_20);
        gte_ldrgb(&scratchData->field_380.s_0.field_8);
        gte_dpcs();
        gte_strgb(&scratchData->field_380.s_0.field_8);
    }

    scratchData->field_380.s_0.field_C    = g_WorldEnvWork.fogColor_1C;
    scratchData->field_380.s_0.field_C.cd = 0x38;

    SetBackColor(0, 0, 0);

    prim = meshHdr->primitives_4;

    if (g_WorldEnvWork.field_0 != 0)
    {
        if (g_WorldEnvWork.isFogEnabled_1 != 0)
        {
            if (*(s32*)&scratchData->field_380.s_0.field_C & 0xFFFFFF)
            {
                poly3 = GsOUT_PACKET_P;
                poly1  = poly3 + 1;

                for (; prim < &meshHdr->primitives_4[meshHdr->primitiveCount_0]; prim++)
                {
                    *(s32*)&scratchData->field_380.s_0.field_10 = *(s32*)&prim->field_C;

                    scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_10];

                    if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_11])
                    {
                        scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_11];
                    }

                    if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_12])
                    {
                        scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_12];
                    }

                    if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_13])
                    {
                        scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_13];
                    }

                    if (scratchData->field_380.s_0.field_18 <= 0)
                    {
                        continue;
                    }

                    if (scratchData->field_380.s_0.field_18 <= 32)
                    {
                        scratchData->field_380.s_0.field_18 = 32;
                    }

                    if (scratchData->field_380.s_0.field_18 > scratchData->field_380.s_0.field_1C)
                    {
                        continue;
                    }

                    gte_NormalClip(*(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_10],
                                   *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_11],
                                   *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_12], &sp10);

                    if (sp10 <= 0)
                    {
                        gte_ldsxy0(*(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_13]);
                        gte_nclip();
                        gte_stopz(&sp10);

                        if (sp10 >= 0)
                        {
                            continue;
                        }
                    }

                    temp_a3 = scratchData->field_380.s_0.field_0;
                    temp_a2 = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_10];

                    temp_a1   = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_11];
                    temp_a0   = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_12];
                    temp_v1_5 = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_13];
                    temp_t0   = temp_a3 * 2;
                    temp_a2_2 = temp_a2;

                    if ((s16)temp_a2 + temp_a3 < temp_t0 || (s16)temp_a1 + temp_a3 < temp_t0 ||
                        (s16)temp_a0 + temp_a3 < temp_t0 || (s16)temp_v1_5 + temp_a3 < temp_t0)
                    {
                        *(s32*)&poly3->x0 = temp_a2_2;
                        *(s32*)&poly1->x0  = temp_a2_2;
                        *(s32*)&poly3->x1 = temp_a1;
                        *(s32*)&poly1->x1  = temp_a1;
                        *(s32*)&poly3->x2 = temp_a0;
                        *(s32*)&poly1->x2  = temp_a0;
                        *(s32*)&poly3->x3 = temp_v1_5;
                        *(s32*)&poly1->x3  = temp_v1_5;

                        *(s32*)&scratchData->field_380.s_0.field_14 = *(s32*)&prim->field_10;

                        var_t3  = 0x1000 - scratchData->field_252[scratchData->field_380.s_0.field_10] * 16;
                        var_t3 -= scratchData->field_380.s_0.field_4;
                        if (var_t3 < 0)
                        {
                            var_t3 = 0;
                        }

                        gte_lddp(var_t3);
                        gte_ldrgb(&scratchData->field_380.s_0.field_C);
                        gte_dpcs();
                        gte_strgb(&poly1->r0);
                        gte_lddp(scratchData->field_252[scratchData->field_380.s_0.field_10] << 4);
                        gte_ldsv_(scratchData->field_2B8[scratchData->field_380.s_0.field_14] << 5);
                        gte_ldrgb(&scratchData->field_380.s_0.field_8);
                        gte_dpcl();
                        gte_strgb(&poly3->r0);

                        var_t3  = 0x1000 - scratchData->field_252[scratchData->field_380.s_0.field_11] * 16;
                        var_t3 -= scratchData->field_380.s_0.field_4;
                        if (var_t3 < 0)
                        {
                            var_t3 = 0;
                        }

                        gte_lddp(var_t3);
                        gte_ldrgb(&scratchData->field_380.s_0.field_C);
                        gte_dpcs();
                        gte_strgb(&poly1->r1);
                        gte_lddp(scratchData->field_252[scratchData->field_380.s_0.field_11] << 4);
                        gte_ldsv_(scratchData->field_2B8[scratchData->field_380.s_0.field_15] << 5);
                        gte_ldrgb(&scratchData->field_380.s_0.field_8);
                        gte_dpcl();
                        gte_strgb(&poly3->r1);

                        var_t3  = 0x1000 - scratchData->field_252[scratchData->field_380.s_0.field_12] * 0x10;
                        var_t3 -= scratchData->field_380.s_0.field_4;
                        if (var_t3 < 0)
                        {
                            var_t3 = 0;
                        }

                        gte_lddp(var_t3);
                        gte_ldrgb(&scratchData->field_380.s_0.field_C);
                        gte_dpcs();
                        gte_strgb(&poly1->r2);
                        gte_lddp(scratchData->field_252[scratchData->field_380.s_0.field_12] << 4);
                        gte_ldsv_(scratchData->field_2B8[scratchData->field_380.s_0.field_16] << 5);
                        gte_ldrgb(&scratchData->field_380.s_0.field_8);
                        gte_dpcl();
                        gte_strgb(&poly3->r2);

                        var_t3  = 0x1000 - scratchData->field_252[scratchData->field_380.s_0.field_13] * 0x10;
                        var_t3 -= scratchData->field_380.s_0.field_4;
                        if (var_t3 < 0)
                        {
                            var_t3 = 0;
                        }

                        gte_lddp(var_t3);
                        gte_ldrgb(&scratchData->field_380.s_0.field_C);
                        gte_dpcs();
                        gte_strgb(&poly1->r3);
                        gte_lddp(scratchData->field_252[scratchData->field_380.s_0.field_13] << 4);
                        gte_ldsv_(scratchData->field_2B8[scratchData->field_380.s_0.field_17] << 5);
                        gte_ldrgb(&scratchData->field_380.s_0.field_8);
                        gte_dpcl();
                        gte_strgb(&poly3->r3);

                        *(s32*)&poly3->u0 = *(s32*)&prim->field_0;
                        *(s32*)&poly3->u1 = *(s32*)&prim->field_4 & 0xFFFFFF;
                        *(u16*)&poly3->u2 = prim->field_8;
                        *(u16*)&poly3->u3 = prim->field_A;

                        setlen(poly3, 12);
                        setlen(poly1, 8);

                        if (prim->field_6.flags & 0x8000)
                        {
                            packet1 = poly1 + 1;

                            SetPriority(packet1, 0, 0);
                            addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], packet1);

                            setSemiTrans(poly1, 1);
                            addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], poly1);

                            packet1 = (PACKET*)(poly1 + 1) + 0xC;
                            SetPriority(packet1, 1, 1);
                            addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], packet1);

                            addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], poly3);

                            poly3 = (PACKET*)(poly1 + 1) + 0xC + 0xC;
                            poly1  = poly3 + 1;
                        }
                        else
                        {
                            setSemiTrans(poly3, 1);

                            addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], poly3);
                            addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], poly1);

                            poly3 = poly1 + 1;
                            poly1  = poly3 + 1;
                        }
                    }
                }

                GsOUT_PACKET_P = poly1; // @bug? Should be `poly_gt4`
                return;
            }

            poly3 = GsOUT_PACKET_P;

            for (; prim < &meshHdr->primitives_4[meshHdr->primitiveCount_0]; prim++)
            {
                *(s32*)&scratchData->field_380.s_0.field_10 = *(s32*)&prim->field_C;

                scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_10];

                if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_11])
                {
                    scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_11];
                }

                if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_12])
                {
                    scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_12];
                }

                if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_13])
                {
                    scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_13];
                }

                if (scratchData->field_380.s_0.field_18 <= 0)
                {
                    continue;
                }

                if (scratchData->field_380.s_0.field_18 <= 32)
                {
                    scratchData->field_380.s_0.field_18 = 32;
                }

                if (scratchData->field_380.s_0.field_18 > scratchData->field_380.s_0.field_1C)
                {
                    continue;
                }

                gte_ldsxy3(*(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_10],
                           *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_11],
                           *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_12]);
                gte_nclip();
                gte_stopz(&sp14);

                if (sp14 <= 0)
                {
                    gte_ldsxy0(*(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_13]);
                    gte_nclip();
                    gte_stopz(&sp14);

                    if (sp14 >= 0)
                    {
                        continue;
                    }
                }

                temp_a3_2 = scratchData->field_380.s_0.field_0;
                temp_a2_3 = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_10];

                temp_a1_2  = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_11];
                temp_a0_5  = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_12];
                temp_v1_11 = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_13];
                temp_t0_2  = temp_a3_2 * 2;
                temp2      = temp_a2_3;

                if ((s16)temp_a2_3 + temp_a3_2 < temp_t0_2 || (s16)temp_a1_2 + temp_a3_2 < temp_t0_2 ||
                    (s16)temp_a0_5 + temp_a3_2 < temp_t0_2 || (s16)temp_v1_11 + temp_a3_2 < temp_t0_2)
                {
                    *(s32*)&poly3->x0 = temp2;
                    *(s32*)&poly3->x1 = temp_a1_2;
                    *(s32*)&poly3->x2 = temp_a0_5;
                    *(s32*)&poly3->x3 = temp_v1_11;

                    *(s32*)&scratchData->field_380.s_0.field_14 = *(s32*)&prim->field_10;

                    gte_lddp(scratchData->field_252[scratchData->field_380.s_0.field_10] << 4);
                    gte_ldsv_(scratchData->field_2B8[scratchData->field_380.s_0.field_14] << 5);
                    gte_ldrgb(&scratchData->field_380.s_0.field_8);
                    gte_dpcl();
                    gte_strgb(&poly3->r0);

                    gte_lddp(scratchData->field_252[scratchData->field_380.s_0.field_11] << 4);
                    gte_ldsv_(scratchData->field_2B8[scratchData->field_380.s_0.field_15] << 5);
                    gte_ldrgb(&scratchData->field_380.s_0.field_8);
                    gte_dpcl();
                    gte_strgb(&poly3->r1);

                    gte_lddp(scratchData->field_252[scratchData->field_380.s_0.field_12] << 4);
                    gte_ldsv_(scratchData->field_2B8[scratchData->field_380.s_0.field_16] << 5);
                    gte_ldrgb(&scratchData->field_380.s_0.field_8);
                    gte_dpcl();
                    gte_strgb(&poly3->r2);

                    gte_lddp(scratchData->field_252[scratchData->field_380.s_0.field_13] << 4);
                    gte_ldsv_(scratchData->field_2B8[scratchData->field_380.s_0.field_17] << 5);
                    gte_ldrgb(&scratchData->field_380.s_0.field_8);
                    gte_dpcl();
                    gte_strgb(&poly3->r3);

                    *(s32*)&poly3->u0 = *(s32*)&prim->field_0;
                    *(s32*)&poly3->u1 = *(s32*)&prim->field_4 & 0xFFFFFF;
                    *(u16*)&poly3->u2 = prim->field_8;
                    *(u16*)&poly3->u3 = prim->field_A;

                    setlen(poly3, 12);

                    addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], poly3);
                    poly3++;
                }
            }

            GsOUT_PACKET_P = poly3;
            return;
        }
        else
        {
            goto __block1530;
        }
    }

    if (g_WorldEnvWork.isFogEnabled_1 != 0)
    {
        poly3  = GsOUT_PACKET_P;
        poly2 = poly3 + 1;

        for (; prim < &meshHdr->primitives_4[meshHdr->primitiveCount_0]; prim++)
        {
            *(s32*)&scratchData->field_380.s_0.field_10 = *(s32*)&prim->field_C;

            scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_10];

            if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_11])
            {
                scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_11];
            }

            if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_12])
            {
                scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_12];
            }

            if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_13])
            {
                scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_13];
            }

            if (scratchData->field_380.s_0.field_18 <= 0)
            {
                continue;
            }

            if (scratchData->field_380.s_0.field_18 < 0x21)
            {
                scratchData->field_380.s_0.field_18 = 0x20;
            }

            if (scratchData->field_380.s_0.field_18 > scratchData->field_380.s_0.field_1C)
            {
                continue;
            }

            gte_ldsxy3(*(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_10],
                       *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_11],
                       *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_12]);
            gte_nclip();
            gte_stopz(&sp18);

            if (sp18 <= 0)
            {
                gte_ldsxy0(*(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_13]);
                gte_nclip();
                gte_stopz(&sp18);

                if (sp18 >= 0)
                {
                    continue;
                }
            }

            temp_a3_4 = scratchData->field_380.s_0.field_0;
            temp_a2_5 = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_10];

            temp_a1_4  = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_11];
            temp_a0_9  = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_12];
            temp_v1_21 = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_13];
            temp_t0_4  = temp_a3_4 * 2;
            temp_a2_6  = temp_a2_5;

            if ((s16)temp_a2_5 + temp_a3_4 < temp_t0_4 || (s16)temp_a1_4 + temp_a3_4 < temp_t0_4 ||
                (s16)temp_a0_9 + temp_a3_4 < temp_t0_4 || (s16)temp_v1_21 + temp_a3_4 < temp_t0_4)
            {
                *(s32*)&poly3->x0  = temp_a2_6;
                *(s32*)&poly2->x0 = temp_a2_6;
                *(s32*)&poly3->x1  = temp_a1_4;
                *(s32*)&poly2->x1 = temp_a1_4;
                *(s32*)&poly3->x2  = temp_a0_9;
                *(s32*)&poly2->x2 = temp_a0_9;
                *(s32*)&poly3->x3  = temp_v1_21;
                *(s32*)&poly2->x3 = temp_v1_21;

                temp4    = 0x1000 - scratchData->field_252[scratchData->field_380.s_0.field_10] * 0x10;
                var_t3_2 = temp4 - scratchData->field_380.s_0.field_4;
                if (var_t3_2 < 0)
                {
                    var_t3_2 = 0;
                }

                gte_lddp(var_t3_2);
                gte_ldrgb(&scratchData->field_380.s_0.field_C);
                gte_dpcs();
                gte_strgb(&poly2->r0);
                gte_lddp(0x1000 - var_t3_2);
                gte_ldrgb(&scratchData->field_380.s_0.field_8);
                gte_dpcs();
                gte_strgb(&poly3->r0);

                temp4    = 0x1000 - scratchData->field_252[scratchData->field_380.s_0.field_11] * 0x10;
                var_t3_2 = temp4 - scratchData->field_380.s_0.field_4;
                if (var_t3_2 < 0)
                {
                    var_t3_2 = 0;
                }

                gte_lddp(var_t3_2);
                gte_ldrgb(&scratchData->field_380.s_0.field_C);
                gte_dpcs();
                gte_strgb(&poly2->r1);
                gte_lddp(0x1000 - var_t3_2);
                gte_ldrgb(&scratchData->field_380.s_0.field_8);
                gte_dpcs();
                gte_strgb(&poly3->r1);

                temp4    = 0x1000 - scratchData->field_252[scratchData->field_380.s_0.field_12] * 0x10;
                var_t3_2 = temp4 - scratchData->field_380.s_0.field_4;
                if (var_t3_2 < 0)
                {
                    var_t3_2 = 0;
                }

                gte_lddp(var_t3_2);
                gte_ldrgb(&scratchData->field_380.s_0.field_C);
                gte_dpcs();
                gte_strgb(&poly2->r2);
                gte_lddp(0x1000 - var_t3_2);
                gte_ldrgb(&scratchData->field_380.s_0.field_8);
                gte_dpcs();
                gte_strgb(&poly3->r2);

                temp4    = 0x1000 - scratchData->field_252[scratchData->field_380.s_0.field_13] * 0x10;
                var_t3_2 = temp4 - scratchData->field_380.s_0.field_4;
                if (var_t3_2 < 0)
                {
                    var_t3_2 = 0;
                }

                gte_lddp(var_t3_2);
                gte_ldrgb(&scratchData->field_380.s_0.field_C);
                gte_dpcs();
                gte_strgb(&poly2->r3);
                gte_lddp(0x1000 - var_t3_2);
                gte_ldrgb(&scratchData->field_380.s_0.field_8);
                gte_dpcs();
                gte_strgb(&poly3->r3);

                *(s32*)&poly3->u0 = *(s32*)&prim->field_0;
                *(s32*)&poly3->u1 = *(s32*)&prim->field_4 & 0xFFFFFF;
                *(u16*)&poly3->u2 = prim->field_8;
                *(u16*)&poly3->u3 = prim->field_A;

                setlen(poly3, 12);
                setlen(poly2, 8);

                if (prim->field_6.flags & 0x8000)
                {
                    packet0 = poly2 + 1;

                    SetPriority(packet0, 0, 0);

                    addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], packet0);
                    setSemiTrans(poly2, 1);
                    addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], poly2);

                    packet0 = (PACKET*)(poly2 + 1) + 0xC;
                    SetPriority(packet0, 1, 1);
                    addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], packet0);
                    addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], poly3);

                    poly3  = (PACKET*)(poly2 + 1) + 0xC + 0xC;
                    poly2 = poly3 + 1;
                }
                else
                {
                    setSemiTrans(poly3, 1);
                    addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], poly3);
                    addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], poly2);

                    poly3  = poly2 + 1;
                    poly2 = poly3 + 1;
                }
            }
        }
        GsOUT_PACKET_P = poly2; // @bug? Should be `poly_gt4`
        return;
    }
    else
    {
        goto __block19CC;
    }

__block1530:
{
    poly0 = GsOUT_PACKET_P;

    for (; prim < &meshHdr->primitives_4[meshHdr->primitiveCount_0]; prim++)
    {
        *(s32*)&scratchData->field_380.s_0.field_10 = *(s32*)&prim->field_C;

        scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_10];

        if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_11])
        {
            scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_11];
        }

        if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_12])
        {
            scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_12];
        }

        if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_13])
        {
            scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_13];
        }

        if (scratchData->field_380.s_0.field_18 <= 0)
        {
            continue;
        }

        if (scratchData->field_380.s_0.field_18 <= 32)
        {
            scratchData->field_380.s_0.field_18 = 32;
        }

        if (scratchData->field_380.s_0.field_18 > scratchData->field_380.s_0.field_1C)
        {
            continue;
        }

        gte_ldsxy3(*(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_10],
                   *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_11],
                   *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_12]);
        gte_nclip();
        gte_stopz(&sp1C);

        if (sp1C <= 0)
        {
            gte_ldsxy0(*(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_13]);
            gte_nclip();
            gte_stopz(&sp1C);

            if (sp1C >= 0)
            {
                continue;
            }
        }

        temp_a3_3 = scratchData->field_380.s_0.field_0;
        temp_a2_4 = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_10];

        temp_a1_3  = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_11];
        temp_a0_7  = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_12];
        temp_v1_16 = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_13];
        temp_t0_3  = temp_a3_3 * 2;
        temp3      = temp_a2_4;

        if ((s16)temp_a2_4 + temp_a3_3 < temp_t0_3 || (s16)temp_a1_3 + temp_a3_3 < temp_t0_3 ||
            (s16)temp_a0_7 + temp_a3_3 < temp_t0_3 || (s16)temp_v1_16 + temp_a3_3 < temp_t0_3)
        {
            *(s32*)&poly0->x0 = temp3;
            *(s32*)&poly0->x1 = temp_a1_3;
            *(s32*)&poly0->x2 = temp_a0_7;
            *(s32*)&poly0->x3 = temp_v1_16;

            *(s32*)&scratchData->field_380.s_0.field_14 = *(s32*)&prim->field_10;

            if (scratchData->field_2B8[scratchData->field_380.s_0.field_14] >= 8)
            {
                gte_lddp(0x1000 - (scratchData->field_2B8[scratchData->field_380.s_0.field_14] << 5));
                gte_ldrgb(&scratchData->field_380.s_0.field_8);
                gte_dpcs();
                gte_strgb(&poly0->r0);
            }
            else
            {
                *(s32*)&poly0->r0 = 0x3C000000;
            }

            if (scratchData->field_2B8[scratchData->field_380.s_0.field_15] >= 8)
            {
                gte_lddp(0x1000 - (scratchData->field_2B8[scratchData->field_380.s_0.field_15] << 5));
                gte_ldrgb(&scratchData->field_380.s_0.field_8);
                gte_dpcs();
                gte_strgb(&poly0->r1);
            }
            else
            {
                *(s32*)&poly0->r1 = 0x3C000000;
            }

            if (scratchData->field_2B8[scratchData->field_380.s_0.field_16] >= 8)
            {
                gte_lddp(0x1000 - (scratchData->field_2B8[scratchData->field_380.s_0.field_16] << 5));
                gte_ldrgb(&scratchData->field_380.s_0.field_8);
                gte_dpcs();
                gte_strgb(&poly0->r2);
            }
            else
            {
                *(s32*)&poly0->r2 = 0x3C000000;
            }

            if (scratchData->field_2B8[scratchData->field_380.s_0.field_17] >= 8)
            {
                gte_lddp(0x1000 - (scratchData->field_2B8[scratchData->field_380.s_0.field_17] << 5));
                gte_ldrgb(&scratchData->field_380.s_0.field_8);
                gte_dpcs();
                gte_strgb(&poly0->r3);
            }
            else
            {
                *(s32*)&poly0->r3 = 0x3C000000;
            }

            *(s32*)&poly0->u0 = *(s32*)&prim->field_0;
            *(s32*)&poly0->u1 = *(s32*)&prim->field_4 & 0xFFFFFF;
            *(u16*)&poly0->u2 = prim->field_8;
            *(u16*)&poly0->u3 = prim->field_A;

            setlen(poly0, 12);

            addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], poly0);
            poly0++;
        }
    }
    GsOUT_PACKET_P = poly0;
    return;
}

__block19CC:
    scratchData->field_380.s_0.field_8.cd = 0x2C;
    poly4                       = GsOUT_PACKET_P;

    for (prim = meshHdr->primitives_4; prim < &meshHdr->primitives_4[meshHdr->primitiveCount_0]; prim++)
    {
        *(s32*)&scratchData->field_380.s_0.field_10 = *(s32*)&prim->field_C;
        scratchData->field_380.s_0.field_18         = scratchData->field_18C[scratchData->field_380.s_0.field_10];

        if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_11])
        {
            scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_11];
        }

        if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_12])
        {
            scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_12];
        }

        if (scratchData->field_380.s_0.field_18 < scratchData->field_18C[scratchData->field_380.s_0.field_13])
        {
            scratchData->field_380.s_0.field_18 = scratchData->field_18C[scratchData->field_380.s_0.field_13];
        }

        if (scratchData->field_380.s_0.field_18 <= 0)
        {
            continue;
        }

        if (scratchData->field_380.s_0.field_18 < 0x21)
        {
            scratchData->field_380.s_0.field_18 = 0x20;
        }

        if (scratchData->field_380.s_0.field_18 > scratchData->field_380.s_0.field_1C)
        {
            continue;
        }

        gte_ldsxy3(*(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_10],
                   *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_11],
                   *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_12]);
        gte_nclip();
        gte_stopz(&sp20);

        if (sp20 <= 0)
        {
            gte_ldsxy0(*(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_13]);
            gte_nclip();
            gte_stopz(&sp20);

            if (sp20 >= 0)
            {
                continue;
            }
        }

        temp_a3_5 = scratchData->field_380.s_0.field_0;
        temp_a2_7 = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_10];

        temp_a1_5  = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_11];
        temp_a0_13 = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_12];
        temp_v1_27 = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_13];
        temp_t0_5  = temp_a3_5 * 2;
        temp       = temp_a2_7;

        if ((s16)temp_a2_7 + temp_a3_5 < temp_t0_5 || (s16)temp_a1_5 + temp_a3_5 < temp_t0_5 ||
            (s16)temp_a0_13 + temp_a3_5 < temp_t0_5 || (s16)temp_v1_27 + temp_a3_5 < temp_t0_5)
        {
            *(s32*)&poly4->x0 = temp;
            *(s32*)&poly4->x1 = temp_a1_5;
            *(s32*)&poly4->x2 = temp_a0_13;
            *(s32*)&poly4->x3 = temp_v1_27;

            *(s32*)&poly4->r0 = *(s32*)&scratchData->field_380.s_0.field_8;

            *(s32*)&poly4->u0 = *(s32*)&prim->field_0;
            *(s32*)&poly4->u1 = *(s32*)&prim->field_4 & 0xFFFFFF;
            *(u16*)&poly4->u2 = prim->field_8;
            *(u16*)&poly4->u3 = prim->field_A;

            setlen(poly4, 9);

            addPrim(&tag[(scratchData->field_380.s_0.field_18 >> arg3) >> 2], poly4);

            poly4++;
        }
    }

    GsOUT_PACKET_P = poly4;
}

void func_80059D50(s32 arg0, s_ModelInfo* modelInfo, MATRIX* mat, s32 arg3, GsOT_TAG* tag) // 0x80059D50
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
        func_80059E34(arg0, curMeshHdr, scratchData, arg3, tag);
    }
}

void func_80059E34(u32 arg0, s_MeshHeader* meshHdr, s_GteScratchData* scratchData, s32 arg3, GsOT_TAG* tag) // 0x80059E34
{
    s32          sp0;
    s32          var_t2;
    s32          x2;
    s32          x1;
    s32          temp_v1;
    s32          x3;
    u16          var_a2;
    s32          packedColor;
    s32          var_t9;
    u32          temp_t0;
    u32          temp_t1;
    s32          temp;
    s32          x0;
    GsOT_TAG*    tag0;
    GsOT_TAG*    tag1;
    s_Primitive* prim;
    POLY_FT4*    poly;

    tag1 = &g_OrderingTable0[g_ActiveBufferIdx].org[640];

    switch (arg0)
    {
        case 0:
        default:
            return;

        case 1:
        case 3:
            packedColor = 0x2E383838;
            var_a2 = 0x140;
            break;

        case 2:
            packedColor = 0x2E808080;
            var_a2 = 0x20;
            break;
    }

    temp_v1 = 0x79C << (arg3 + 2);
    var_t9  = g_WorldEnvWork.isFogEnabled_1 ? MIN(temp_v1, g_WorldEnvWork.fogFarDistance_10) : temp_v1;

    poly                        = (POLY_FT4*)GsOUT_PACKET_P;
    scratchData->field_380.s_0.field_0 = g_GameWork.gsScreenWidth_588 >> 1;

    for (prim = meshHdr->primitives_4; prim < &meshHdr->primitives_4[meshHdr->primitiveCount_0]; prim++)
    {
        *(s32*)&scratchData->field_380.s_0.field_10 = *(s32*)&prim->field_C;

        var_t2 = scratchData->field_18C[scratchData->field_380.s_0.field_10];
        var_t2 = MAX(scratchData->field_18C[scratchData->field_380.s_0.field_11], var_t2);
        var_t2 = MAX(scratchData->field_18C[scratchData->field_380.s_0.field_12], var_t2);
        var_t2 = MAX(scratchData->field_18C[scratchData->field_380.s_0.field_13], var_t2);

        if (var_t2 <= 0)
        {
            continue;
        }

        if (var_t2 <= 32)
        {
            var_t2 = 32;
        }

        if (var_t9 < var_t2)
        {
            continue;
        }

        gte_NormalClip(*(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_10],
                       *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_11],
                       *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_12],
                       &sp0);

        if (sp0 <= 0)
        {
            gte_ldsxy0(*(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_13]);
            gte_nclip();
            gte_stopz(&sp0);

            if (sp0 >= 0)
            {
                continue;
            }
        }

        temp = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_10];
        x1 = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_11];
        x2 = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_12];
        x3 = *(s32*)&scratchData->screenXy_0[scratchData->field_380.s_0.field_13];

        temp_t0 = scratchData->field_380.s_0.field_0;
        temp_t1 = temp_t0 * 2;
        x0 = temp;

        if (scratchData->screenXy_0[scratchData->field_380.s_0.field_10].vx + temp_t0 >= temp_t1 &&
            (s16)x1 + temp_t0 >= temp_t1 &&
            (s16)x2 + temp_t0 >= temp_t1 &&
            (s16)x3 + temp_t0 >= temp_t1)
        {
            continue;
        }

        *(s32*)&poly->x0 = x0;
        *(s32*)&poly->x1 = x1;
        *(s32*)&poly->x2 = x2;
        *(s32*)&poly->x3 = x3;

        *(s32*)&poly->r0 = packedColor;
        *(s32*)&poly->u0 = *(s32*)&prim->field_0;
        *(s32*)&poly->u1 = ((*(u32*)&prim->field_4 & 0x1FFFFF) | (var_a2 << 16)); // Maybe `field_4` is bitfield
        *(u16*)&poly->u2 = prim->field_8;
        *(u16*)&poly->u3 = prim->field_A;

        setlen(poly, 9);

        if (arg0 == 1)
        {
            tag0 = tag1;
        }
        else
        {
            tag0 = &tag[var_t2 >> (arg3 + 2)];
        }

        addPrim(tag0, poly);
        poly++;
    }

    GsOUT_PACKET_P = (PACKET*)poly;
}

void func_8005A21C(s_ModelInfo* modelInfo, GsOT_TAG* otTag, void* arg2, MATRIX* mat) // 0x8005A21C
{
    s16               var_v1;
    u32               normalOffset;
    u32               vertOffset;
    s_ModelHeader*    modelHdr;
    s_MeshHeader*     curMeshHdr;
    s_GteScratchData* scratchData;

    scratchData = PSX_SCRATCH_ADDR(0);

    if (g_WorldEnvWork.isFogEnabled_1)
    {
        if (mat->t[2] < (1 << g_WorldEnvWork.fogDepthShift_14))
        {
            var_v1 = Q12(1.0f) - (g_WorldEnvWork.fogRamp_CC[(s32)(mat->t[2] << 7) >> g_WorldEnvWork.fogDepthShift_14] << 4);
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

    switch (g_WorldEnvWork.field_0)
    {
        case 0:
            func_8005A42C(scratchData, var_v1);
            break;

        case 1:
            func_8005A478(scratchData, var_v1);
            SetColorMatrix(&g_WorldEnvWork.field_2C);
            gte_lddqa(g_WorldEnvWork.field_4C);
            gte_lddqb_0();
            break;

        case 2:
            func_8005A838(scratchData, var_v1);
            SetColorMatrix(&g_WorldEnvWork.field_2C);
            gte_lddqa(g_WorldEnvWork.field_4C);
            gte_lddqb_0();
            break;
    }

    modelHdr     = modelInfo->modelHdr_8;
    vertOffset   = modelHdr->vertexOffset_9;
    normalOffset = modelHdr->normalOffset_A;

    for (curMeshHdr = modelHdr->meshHdrs_C; curMeshHdr < &modelHdr->meshHdrs_C[modelHdr->meshCount_8]; curMeshHdr++)
    {
        func_8005A900(curMeshHdr, vertOffset, scratchData, mat);

        if (g_WorldEnvWork.field_0 != 0)
        {
            func_8005AA08(curMeshHdr, normalOffset, scratchData);
        }

        func_8005AC50(curMeshHdr, scratchData, otTag, arg2);
    }
}

void func_8005A42C(s_GteScratchData* scratchData, q19_12 alpha) // 0x8005A42C
{
    q19_12 invAlpha = Q12(1.0f) - Q12_MULT(alpha, g_WorldEnvWork.field_20);

    gte_lddp(invAlpha);
    gte_ldrgb(&g_WorldEnvWork.worldTintColor_28);
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

    temp_s0 = g_WorldEnvWork.field_7C.vx;
    temp_s1 = g_WorldEnvWork.field_7C.vy;
    temp_s2 = g_WorldEnvWork.field_7C.vz;

    var_t1 = SquareRoot0(SQUARE(temp_s0) + SQUARE(temp_s1) + SQUARE(temp_s2));
    if (var_t1 == 0)
    {
        var_t1 = 1;
    }

    temp_s0_neg = -temp_s0;
    temp_s1_neg = -temp_s1;
    temp_s2_neg = -temp_s2;

    *(u32*)&scratchData->field_3E4.m[0][0] = *(u32*)&g_WorldEnvWork.field_74;
    scratchData->field_3E4.m[0][2]         = g_WorldEnvWork.field_74.vz;

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
    if (g_WorldEnvWork.field_3 < var_s0)
    {
        var_s0 = g_WorldEnvWork.field_3;
    }

    var_s0 = Q12_MULT(var_s0, alpha);

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

    SetBackColor(Q12_MULT(g_WorldEnvWork.field_24 + ((g_WorldEnvWork.worldTintColor_28.r * var_a1) >> 7), alpha),
                 Q12_MULT(g_WorldEnvWork.field_25 + ((g_WorldEnvWork.worldTintColor_28.g * var_a1) >> 7), alpha),
                 Q12_MULT(g_WorldEnvWork.field_26 + ((g_WorldEnvWork.worldTintColor_28.b * var_a1) >> 7), alpha));
}

void func_8005A838(s_GteScratchData* scratchData, s32 scale) // 0x8005A838
{
    SVECTOR3 vec;

    vec.vx = Q12_MULT(g_WorldEnvWork.field_74.vx, scale) >> 1;
    vec.vy = Q12_MULT(g_WorldEnvWork.field_74.vy, scale) >> 1;
    vec.vz = Q12_MULT(g_WorldEnvWork.field_74.vz, scale) >> 1;

    gte_SetLightSVector(&vec);

    SetBackColor(Q12_MULT(g_WorldEnvWork.field_24, scale),
                 Q12_MULT(g_WorldEnvWork.field_25, scale),
                 Q12_MULT(g_WorldEnvWork.field_26, scale));
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
        "swc2    $20, 0( %0 );"                      \
        "swc2    $21, 4( %0 );"                      \
        "swc2    $22, 8( %0 )"                       \
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

void func_8005AC50(s_MeshHeader* meshHdr, s_GteScratchData2* scratchData, GsOT_TAG* ot, s32 arg3) // 0x8005AC50
{
    typedef union
    {
        POLY_GT3* gt3;
        POLY_GT4* gt4;
        PACKET*   packet;
    } u_poly;

    s32          r4;
    s32          sp4;
    s16          temp_v1;
    s32          temp_a0;
    s32          temp_t4;
    s32          temp_t4_2;
    s32          temp_v0;
    s32          temp_v0_2;
    s32          var_t9;
    s32          var_v0;
    s32          var_v1;
    s32          var_a3;
    GsOT_TAG*    localOt;
    s_Primitive* prim;
    u16*         var_t5;
    u_poly       poly;

    var_a3              = g_WorldEnvWork.field_0;
    scratchData->u.s_1.field_8 = g_WorldEnvWork.field_14C << 16;

    temp_a0 = 0x79C << (arg3 + 2);
    var_t9  = g_WorldEnvWork.isFogEnabled_1 ? MIN(temp_a0, g_WorldEnvWork.fogFarDistance_10) : temp_a0;

    for (prim = meshHdr->primitives_4, poly.packet = GsOUT_PACKET_P; prim < &meshHdr->primitives_4[meshHdr->primitiveCount_0]; prim++)
    {
        *(s32*)&scratchData->u.s_1.field_0 = *(s32*)&prim->field_C;
        *(s32*)&scratchData->u.s_1.field_4 = *(s32*)&prim->field_10;

        if (scratchData->u.s_1.field_3 == 0xFF)
        {
            temp_t4 = (scratchData->screenZ_168[scratchData->u.s_1.field_0] + scratchData->screenZ_168[scratchData->u.s_1.field_1] +
                       scratchData->screenZ_168[scratchData->u.s_1.field_2] + scratchData->screenZ_168[scratchData->u.s_1.field_2]) >> 2;

            if (temp_t4 <= 0 || var_t9 < temp_t4)
            {
                continue;
            }

            gte_NormalClip(*(s32*)&scratchData->screenXy_0[scratchData->u.s_1.field_0],
                           *(s32*)&scratchData->screenXy_0[scratchData->u.s_1.field_1],
                           *(s32*)&scratchData->screenXy_0[scratchData->u.s_1.field_2],
                           &r4);

            if (r4 <= 0)
            {
                continue;
            }

            *(s32*)&poly.gt3->x0 = *(s32*)&scratchData->screenXy_0[scratchData->u.s_1.field_0];
            *(s32*)&poly.gt3->x1 = *(s32*)&scratchData->screenXy_0[scratchData->u.s_1.field_1];
            *(s32*)&poly.gt3->x2 = *(s32*)&scratchData->screenXy_0[scratchData->u.s_1.field_2];

            if (var_a3 != 0)
            {
                *(s32*)&poly.gt3->r0 = *(s32*)&scratchData->field_21C[scratchData->u.s_1.field_4];
                *(s32*)&poly.gt3->r1 = *(s32*)&scratchData->field_21C[scratchData->u.s_1.field_5];
                *(s32*)&poly.gt3->r2 = *(s32*)&scratchData->field_21C[scratchData->u.s_1.field_6];
            }
            else
            {
                *(s32*)&poly.gt3->r0 = *(s32*)&poly.gt3->r1 = *(s32*)&poly.gt3->r2 = *(s32*)&scratchData->field_3D8;
            }

            poly.gt3->code = ((prim->field_6.flags >> 15) * 2) | 0x34;

            *(s32*)&poly.gt3->u0 = *(s32*)&prim->field_0 + scratchData->u.s_1.field_8;
            *(s32*)&poly.gt3->u1 = *(s32*)&prim->field_4 & 0xFFFFFF;
            *(u16*)&poly.gt3->u2 = prim->field_8;

            setlen(poly.gt3, 9);

            addPrim(&ot[(temp_t4 >> arg3) >> 2], poly.gt3);
            poly.gt3++;
        }
        else
        {
            temp_t4 = (scratchData->screenZ_168[scratchData->u.s_1.field_0] + scratchData->screenZ_168[scratchData->u.s_1.field_1] +
                       scratchData->screenZ_168[scratchData->u.s_1.field_2] + scratchData->screenZ_168[scratchData->u.s_1.field_3]) >> 2;

            if (temp_t4 <= 0 || var_t9 < temp_t4)
            {
                continue;
            }

            gte_ldsxy3(*(s32*)&scratchData->screenXy_0[scratchData->u.s_1.field_0],
                       *(s32*)&scratchData->screenXy_0[scratchData->u.s_1.field_1],
                       *(s32*)&scratchData->screenXy_0[scratchData->u.s_1.field_2]);
            gte_nclip();
            gte_stopz(&sp4);

            if (sp4 <= 0)
            {
                gte_ldsxy0(*(s32*)&scratchData->screenXy_0[scratchData->u.s_1.field_3]);
                gte_nclip();
                gte_stopz(&sp4);

                if (sp4 >= 0)
                {
                    continue;
                }
            }

            *(s32*)&poly.gt4->x0 = *(s32*)&scratchData->screenXy_0[scratchData->u.s_1.field_0];
            *(s32*)&poly.gt4->x1 = *(s32*)&scratchData->screenXy_0[scratchData->u.s_1.field_1];
            *(s32*)&poly.gt4->x2 = *(s32*)&scratchData->screenXy_0[scratchData->u.s_1.field_2];
            *(s32*)&poly.gt4->x3 = *(s32*)&scratchData->screenXy_0[scratchData->u.s_1.field_3];

            if (var_a3 != 0)
            {
                *(s32*)&poly.gt4->r0 = *(s32*)&scratchData->field_21C[scratchData->u.s_1.field_4];
                *(s32*)&poly.gt4->r1 = *(s32*)&scratchData->field_21C[scratchData->u.s_1.field_5];
                *(s32*)&poly.gt4->r2 = *(s32*)&scratchData->field_21C[scratchData->u.s_1.field_6];
                *(s32*)&poly.gt4->r3 = *(s32*)&scratchData->field_21C[scratchData->u.s_1.field_7];
            }
            else
            {
                *(s32*)&poly.gt4->r0 = *(s32*)&poly.gt4->r1 = *(s32*)&poly.gt4->r2 = *(s32*)&poly.gt4->r3 = *(s32*)&scratchData->field_3D8;
            }

            poly.gt4->code = ((prim->field_6.flags >> 15) * 2) | 0x3C;

            *(s32*)&poly.gt4->u0 = *(s32*)&prim->field_0 + scratchData->u.s_1.field_8;
            *(s32*)&poly.gt4->u1 = *(s32*)&prim->field_4 & 0xFFFFFF;
            *(u16*)&poly.gt4->u2 = prim->field_8;
            *(u16*)&poly.gt4->u3 = prim->field_A;

            setlen(poly.gt4, 12);

            addPrim(&ot[(temp_t4 >> arg3) >> 2], poly.gt4);
            poly.gt4++;
        }
    }

    GsOUT_PACKET_P = poly.packet;
}

// ========================================
// TEXTURE HANDLING
// ========================================

void Texture_Init(s_Texture* tex, char* texName, u8 tPage0, u8 tPage1, s32 u, s32 v, s16 clutX, s16 clutY) // 0x8005B1A0
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

s_Texture* Texture_Get(s_Material* mat, s_ActiveTextures* activeTexs, void* fsBuffer9, e_FsFile fileIdx, s32 arg4)
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
        Text_Debug_PositionSet(100, 80);
        strncpy(&debugStr, &filename, 12);

#if VERSION_DATE <= VERSION_DATE_PROTO_981216
        // Code seen in 98-12-16 build.
        Text_Debug_Draw(debugStr);
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

void Texture_RefClear(s_Texture* tex) // 0x8005B3A4
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

INCLUDE_RODATA("bodyprog/nonmatchings/gfx/bodyprog_80055028", D_80028544);

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

void Textures_ActiveTex_CountReset(s_ActiveTextures* activeTexs) // 0x8005B46C
{
    activeTexs->count_0 = 0;
}

void Textures_ActiveTex_PutTextures(s_ActiveTextures* activeTexs, s_Texture* texs, s32 texIdx) // 0x8005B474
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

s_Texture* Textures_ActiveTex_FindTexture(char* texName, s_ActiveTextures* activeTexs) // 0x8005B4BC
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
        curPtr->field_18 = Q12_MULT(curPtr->field_2, Math_Cos(curPtr->field_4));
        curPtr->field_14 = Q12_MULT(curPtr->field_2, Math_Sin(curPtr->field_4));
        curPtr->field_16 = curPtr->field_0;
    }
}

INCLUDE_ASM("bodyprog/nonmatchings/gfx/bodyprog_80055028", func_8005B62C); // 0x8005B62C

// ========================================
// UNUSED
// ========================================
// Split from something related to debug feature that got cut?

void Gfx_DebugStringPositionSet(s16 unused, s16 posX, s16 posY) // 0x8005BF0C
{
    Text_Debug_PositionSet(posX, posY);
}
