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

extern s_WorldEnvWork const g_WorldEnvWork;

s16 D_800BCDE8[8];

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

    if (g_DeltaTime != Q12(0.0f))
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
    Math_SVectorSet(&g_SysWork.pointLightRot_2370, Q12_ANGLE(10.0f), Q12_ANGLE(0.0f), Q12_ANGLE(0.0f));
}

void Game_FlashlightAttributesFix(void) // 0x8003EBA0
{
    g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

    g_SysWork.field_235C = &g_SysWork.playerBoneCoords_890[HarryBone_Torso];
    g_SysWork.field_236C = &g_SysWork.playerBoneCoords_890[HarryBone_Root];

    Math_Vector3Set(&g_SysWork.pointLightPosition_2360, Q12(-0.08f), Q12(-0.28f), Q12(0.12f));
    Math_SVectorSet(&g_SysWork.pointLightRot_2370, Q12_ANGLE(-15.0f), Q12_ANGLE(0.0f), Q12_ANGLE(0.0f));
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
        g_SysWork.field_2388.flashlightIntensity_18 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 4.0f);
    }
    else
    {
        g_SysWork.field_2388.flashlightIntensity_18 -= Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 4.0f);
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
            rot0.vx = Q12_ANGLE(0.0f);
            rot0.vy = Q12_ANGLE(-90.0f);
            rot0.vz = Q12_ANGLE(0.0f);
            break;

        case 2:
            rot0.vx = Q12_ANGLE(-20.0f);
            rot0.vy = Q12_ANGLE(195.0f);
            rot0.vz = Q12_ANGLE(0.0f);
            break;

        case 3:
            rot0.vx = Q12_ANGLE(-20.0f);
            rot0.vy = Q12_ANGLE(-75.0f);
            rot0.vz = Q12_ANGLE(0.0f);
            break;

        case 4:
            rot0.vx = Q12_ANGLE(-20.0f);
            rot0.vy = Q12_ANGLE(15.0f);
            rot0.vz = Q12_ANGLE(0.0f);
            break;

        case 5:
            rot0.vx = Q12_ANGLE(-20.0f);
            rot0.vy = Q12_ANGLE(105.0f);
            rot0.vz = Q12_ANGLE(0.0f);
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