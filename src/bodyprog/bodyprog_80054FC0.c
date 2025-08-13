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

void func_80054FC0(s32* arg0, s32* arg1, u8 idx) // 0x80054FC0
{
    s32 var;

    var = D_800AD4A0[idx] - *arg0;
    if (var == 0)
    {
        return;
    }

    if (*arg1 >= var)
    {
        *arg0 += var;
        *arg1 -= var;
        return;
    }

    *arg0 += *arg1;
    *arg1  = 0;
}

void func_80055028() // 0x80055028
{
    func_80040BAC();
    func_8008D41C();

    // This struct might or might not be a GPU packet or some other graphics/GTE-related PsyQ thing.
    D_800C4168.field_0  = 0;
    D_800C4168.field_20 = 0x1000;

    // Likely a color triplet.
    D_800C4168.field_28.r = 0x80;
    D_800C4168.field_28.g = 0x80;
    D_800C4168.field_28.b = 0x80;

    D_800C4168.field_1 = 0;
    D_800C4168.field_2 = 0;

    // Likely a color triplet.
    D_800C4168.field_1C = 0xFF;
    D_800C4168.field_1D = 0xFF;
    D_800C4168.field_1E = 0xFF;

    D_800C4168.field_4C = 0;
    D_800C4168.field_50 = 0;
    D_800C4168.field_4  = 0;
    D_800C4168.field_18 = 0;

    gte_SetFarColor(0, 0, 0);

    func_80055840(0x20000, 0x22000);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800550D0); // 0x800550D0

void func_80055330(u8 arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) // 0x80055330
{
    D_800C4168.field_0          = arg0;
    D_800C4168.field_20         = arg1;
    D_800C4168.field_3          = arg2;
    D_800C4168.field_28.r       = arg3 >> 5;
    D_800C4168.field_2C.m[0][2] = arg3;
    D_800C4168.field_2C.m[0][1] = arg3;
    D_800C4168.field_2C.m[0][0] = arg3;
    D_800C4168.field_28.g       = arg4 >> 5;
    D_800C4168.field_8          = arg6;
    D_800C4168.field_28.b       = arg5 >> 5;
    D_800C4168.field_2C.m[1][2] = (s16)arg4;
    D_800C4168.field_2C.m[1][1] = (s16)arg4;
    D_800C4168.field_2C.m[1][0] = (s16)arg4;
    D_800C4168.field_2C.m[2][2] = (s16)arg5;
    D_800C4168.field_2C.m[2][1] = (s16)arg5;
    D_800C4168.field_2C.m[2][0] = (s16)arg5;
    D_800C4168.field_24         = (arg3 * arg1) >> 17;
    D_800C4168.field_25         = (arg4 * arg1) >> 17;
    D_800C4168.field_26         = (arg5 * arg1) >> 17;
}

void func_800553C4(u8 arg0, u8 arg1, u8 arg2, u8 arg3) // 0x800553C4
{
    D_800C4168.field_1  = arg0;
    D_800C4168.field_1C = arg1;
    D_800C4168.field_1D = arg2;
    D_800C4168.field_1E = arg3;
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005545C); // 0x8005545C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80055490); // 0x80055490

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800554C4); // 0x800554C4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80055648); // 0x80055648

s32 func_800557DC() // 0x800557DC
{
    MATRIX mat;

    func_80049C2C(&mat, D_800C4168.field_60.vx, D_800C4168.field_60.vy, D_800C4168.field_60.vz);
    return mat.t[2] * 16;
}

void func_80055814(s32 arg0) // 0x80055814
{
    D_800C4168.field_18 = FP_FLOAT_TO(1.0f, Q12_SHIFT) - func_800559A8(arg0);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80055840); // 0x80055840

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800559A8); // 0x800559A8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80055A50); // 0x80055A50

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80055A90); // 0x80055A90

void func_80055B74(CVECTOR* result, CVECTOR* color, s32 arg2) // 0x80055B74
{
    s32 var_v0;
    s32 var_t0;

    arg2 >>= 4;

    var_t0 = D_800C4168.field_20 >> 5;

    if (arg2 < (1 << D_800C4168.field_14))
    {
        var_v0 = D_800C4168.field_CC[(arg2 << 7) >> D_800C4168.field_14];
    }
    else
    {
        var_v0 = 255;
    }

    var_v0 <<= 4;

    gte_lddp(var_v0);
    gte_ldrgb(color);
    gte_SetFarColor(D_800C4168.field_1C, D_800C4168.field_1D, D_800C4168.field_1E);
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

    if (D_800C4168.field_1 != 0)
    {
        if (var_s0 < (1 << D_800C4168.field_14))
        {
            var_v0 = D_800C4168.field_CC[(var_s0 << 7) >> D_800C4168.field_14];
        }
        else
        {
            var_v0 = 255;
        }

        gte_lddp(var_v0 << 4);
        gte_ldrgb(color);
        gte_SetFarColor(D_800C4168.field_1C, D_800C4168.field_1D, D_800C4168.field_1E);
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80055D78); // 0x80055D78

void func_80055E90(CVECTOR* color, u8 fadeAmount) // 0x80055E90
{
    s32 alpha;
    u8  prev_cd;

    alpha = FP_ALPHA(1.0f) - (fadeAmount * 32);

    // Works similar to `gte_DpqColor` macro, but `gte_lddp`/`gte_ldrgb` are in wrong order?

    gte_lddp(alpha);
    gte_ldrgb(&D_800C4168.field_28);
    gte_dpcs();

    prev_cd = color->cd;
    gte_strgb(color);
    color->cd = prev_cd;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80055ECC); // 0x80055ECC

u8 func_80055F08(SVECTOR3* arg0, SVECTOR3* arg1, void* arg2) // 0x80055F08
{
    MATRIX  mat;
    DVECTOR screenPos;
    s32     geomOffsetX;
    s32     geomOffsetY;
    s32     depthP;
    s32     geomScreen;
    s32     ret;
    s32     var_v1;
    u8      field_3;
    s32     field_20;

    func_80057228(arg2, D_800C4168.field_54, D_800C4168.unk_58, &D_800C4168.field_60);

    gte_lddqa(D_800C4168.field_4C);
    gte_lddqb_0();
    gte_ldtr_0();

    ReadGeomOffset(&geomOffsetX, &geomOffsetY);
    geomScreen = ReadGeomScreen();
    SetGeomOffset(-1024, -1024);
    SetGeomScreen(16);

    mat.m[0][0] = D_800C4168.field_74.vx;
    mat.m[0][1] = D_800C4168.field_74.vy;
    mat.m[0][2] = D_800C4168.field_74.vz;
    mat.m[1][0] = -arg1->vx;
    mat.m[1][1] = -arg1->vy;
    mat.m[1][2] = -arg1->vz;
    mat.m[2][0] = arg0->vx - D_800C4168.field_7C.vx;
    mat.m[2][1] = arg0->vy - D_800C4168.field_7C.vy;
    mat.m[2][2] = arg0->vz - D_800C4168.field_7C.vz;
    field_3     = D_800C4168.field_3;
    field_20    = D_800C4168.field_20 >> 5;
    SetRotMatrix(&mat);

    gte_ldv0(&mat.m[2][0]);
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

void func_800560FC(s_800BE9FC* arg0) // 0x800560FC
{
    s32 i;

    if (arg0->field_2 != 1)
    {
        arg0->field_2 = 1;

        arg0->field_4  += (u32)arg0;
        arg0->field_C  += (u32)arg0;
        arg0->field_10 += (u32)arg0;

        for (i = 0; i < arg0->field_8; i++)
        {
            if (arg0->field_0 == 48)
            {
                func_800561A4(&arg0->field_C[i * 16], arg0);
            }
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800561A4); // 0x800561A4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80056244); // 0x80056244

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80056348); // 0x80056348

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800563E8); // 0x800563E8

void func_80056464(s_800BE9FC* arg0, s32 fileIdx, s32* arg2, s32 arg3) // 0x80056464
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

    func_80056558(arg0, sp10, arg2, arg3);
}

void func_80056504(s_800BE9FC* arg0, s8* arg1, s32* arg2, s32 arg3) // 0x80056504
{
    s8 sp10[8];

    func_80056D64(&sp10, arg1);
    func_80056558(arg0, &sp10, arg2, arg3);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80056558); // 0x80056558

void func_8005660C(s_func_8005660C_0* arg0, s_func_8005660C_1* arg1, s32 arg2) // 0x8005660C
{
    s32 coeff;

    coeff = 4;
    switch (arg1->field_0)
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

    arg0->field_14 = arg1->field_2 * coeff;
    arg0->field_15 = arg1->field_3;

    arg0->field_E  = ((arg1->field_0 & 0x3) << 7) | ((arg2 & 0x3) << 5) | (arg1->field_1 & (1 << 4)) | (arg1->field_1 & 0xF);
    arg0->field_10 = (arg1->field_6 << 6) | ((arg1->field_4 >> 4) & 0x3F);
}

void func_800566B4(s_func_800566B4* arg0, s_FsImageDesc* image, s8 unused, s32 startIdx, s32 arg4) // 0x800566B4
{
    char                 filename[16];
    s_func_800566B4_sub* var_s0;
    s_FsImageDesc*       imagePtr;
    s32                  i;

    // Loop could be using `&image[i]`/`&arg0->field_4[i]` instead? Wasn't able to make that match though.
    imagePtr = image;
    var_s0   = arg0->field_4;

    for (i = 0; i < arg0->field_3; i++, var_s0++, imagePtr++)
    {
        func_8005B3BC(filename, var_s0);
        Fs_QueueStartReadTim(Fs_FindNextFile(filename, 0, startIdx), FS_BUFFER_9, imagePtr);
        func_8005660C(var_s0, imagePtr, arg4);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80056774); // 0x80056774

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80056888); // 0x80056888

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80056954); // 0x80056954

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80056A88); // 0x80056A88

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80056BF8); // 0x80056BF8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80056C80); // 0x80056C80

void func_80056C8C(s_Bone* bone, s_800BE9FC* arg1, s32 arg2)
{
    u8* field_C;
    
    field_C       = arg1->field_C;
    bone->field_C = arg2;

    if (arg1->field_0 == '0') // Maybe `s_800BE9FC`'s `field_0` is `char*`? But its used as `s32` somewhere.
    {
        bone->field_8 = field_C + (arg2 * 16);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80056CB4); // 0x80056CB4

void func_80056D64(s8* prevStr, s8* newStr) // 0x80056D64
{
    *(s32*)&prevStr[4] = 0;
    *(s32*)&prevStr[0] = 0;
    strncpy(prevStr, newStr, 8);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80056D8C); // 0x80056D8C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80057090); // 0x80057090

// TODO: .rodata migration and odd code.
#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800571D0); // 0x800571D0
#endif

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80057228); // 0x80057228

void func_80057344(s_func_80057344* arg0, void* arg1, void* arg2, s32 arg3) // 0x80057344
{
    u32                var_s1;
    u32                var_s4;
    s_func_8005759C*   var_s0;
    s_func_80057344_8* var_s2;
    s_GteScratchData*  scratchData;

    scratchData = PSX_SCRATCH_ADDR(0);

    var_s2 = arg0->field_8;
    var_s4 = var_s2->field_9;
    var_s1 = var_s2->field_A;

    gte_lddqa(D_800C4168.field_4C);
    gte_lddqb_0();

    for (var_s0 = var_s2->field_C; var_s0 < &var_s2->field_C[var_s2->field_8]; var_s0++)
    {
        if (var_s4 != 0 || var_s1 != 0)
        {
            func_8005759C(var_s0, scratchData, var_s4, var_s1);
        }
        else
        {
            func_800574D4(var_s0, scratchData);
        }

        switch (D_800C4168.field_0)
        {
            case 0:
                break;
            case 1:
                func_80057658(var_s0, var_s1, scratchData, &D_800C4168.field_74, &D_800C4168.field_7C);
                break;
            case 2:
                func_80057A3C(var_s0, var_s1, scratchData, &D_800C4168.field_74);
                break;
        }

        func_80057B7C(var_s0, var_s4, scratchData, arg3);
        func_8005801C(var_s0, scratchData, arg1, arg2);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800574D4); // 0x800574D4

void func_8005759C(s_func_8005759C* arg0, s_GteScratchData* scratchData, s32 arg2, s32 arg3) // 0x8005759C
{
    s16* field_CPtr;
    s16* field_18CPtr;
    s32* field_8Ptr;
    s32* field_0Ptr;
    u8*  field_2B8Ptr;
    u8*  field_14Ptr;

    // Should be loop? Tried but no luck.
    field_0Ptr   = &scratchData->field_0[arg2];
    field_18CPtr = &scratchData->field_18C[arg2];
    field_8Ptr   = arg0->field_8;
    field_CPtr   = arg0->field_C;
    while (field_8Ptr < &arg0->field_8[arg0->field_1])
    {
        *field_0Ptr++   = *field_8Ptr++;
        *field_18CPtr++ = *field_CPtr++;
    }

    field_14Ptr  = arg0->field_14;
    field_2B8Ptr = &scratchData->field_2B8[arg3];
    while (field_14Ptr < &arg0->field_14[arg0->field_3])
    {
        *field_2B8Ptr++ = *field_14Ptr++;
    }
}

void func_80057658(s_func_8005759C* arg0, s32 offset, s_GteScratchData* scratchData, SVECTOR3* arg3, SVECTOR* arg4) // 0x80057658
{
    s32      geomOffsetX;
    s32      geomOffsetY;
    MATRIX*  mat;
    s32      geomScreen;
    s32      temp_t9;
    s32      var_a1;
    s32      var_v1;
    s32      temp_t2;
    u8*      end;
    u8*      var_t0;
    s16*     temp_t8;
    DVECTOR* screenPos;
    s32*     depthP;
    u8       temp_v1;

    s_func_8005759C_10* var_t3;

    scratchData->field_3AC = *arg4; // 3AC changed to SVECTOR

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

    for (var_t3 = arg0->field_10; var_t3 < &arg0->field_10[arg0->field_2]; var_t3++)
    {
        temp_t8   = &scratchData->field_380.m[2][0];
        screenPos = &scratchData->screenPos_3A4;
        depthP    = &scratchData->depthP_3A8;
        temp_t2   = temp_v1;

        *(u32*)&scratchData->field_3A0 = *(u32*)var_t3;

        mat->m[1][0] = scratchData->field_3A0.vx << 5;
        mat->m[1][1] = scratchData->field_3A0.vy << 5;
        mat->m[1][2] = scratchData->field_3A0.vz << 5;
        gte_SetRotMatrix_Row0_1(mat->m);

        end = &var_t0[scratchData->field_3A0.count];

        mat->m[2][0] = scratchData->field_0[*var_t0].vx - scratchData->field_3AC.vx;
        mat->m[2][1] = scratchData->field_0[*var_t0].vy - scratchData->field_3AC.vy;
        mat->m[2][2] = scratchData->field_18C[*var_t0] - scratchData->field_3AC.vz;
        gte_SetRotMatrix_Row2(mat->m);

        gte_ldv0(temp_t8);
        gte_rtps();
        gte_stsxy(screenPos);
        gte_stdp(depthP);

        while (++var_t0 < end)
        {
            mat->m[2][0] = scratchData->field_0[*var_t0].vx - scratchData->field_3AC.vx;
            mat->m[2][1] = scratchData->field_0[*var_t0].vy - scratchData->field_3AC.vy;
            mat->m[2][2] = scratchData->field_18C[*var_t0] - scratchData->field_3AC.vz;

            gte_SetRotMatrix_Row2(mat->m);
            gte_ldv0(temp_t8);
            gte_rtps();

            scratchData->screenPos_3A4.vx += 1024;
            scratchData->screenPos_3A4.vy += 1024;

            var_a1 = (scratchData->screenPos_3A4.vx * scratchData->screenPos_3A4.vy) + (scratchData->screenPos_3A4.vy * (scratchData->depthP_3A8 >> 4));
            var_a1 >>= 5;
            var_a1 -= 16;
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

        var_a1 = (scratchData->screenPos_3A4.vx * scratchData->screenPos_3A4.vy) + (scratchData->screenPos_3A4.vy * (scratchData->depthP_3A8 >> 4));
        var_a1 >>= 5;
        var_a1 -= 16;
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
    }

    SetGeomOffset(geomOffsetX, geomOffsetY);
    SetGeomScreen(geomScreen);
}

void func_80057A3C(s_func_8005759C* arg0, s32 offset, s_GteScratchData* scratchData, SVECTOR3* lightVec) // 0x80057A3C
{
    s32   var_v1;
    u8*   var_a3;
    void* endPtr;
    s32   temp_t2;

    s_func_8005759C_10* var_t0;

    scratchData->field_380.m[0][0] = lightVec->vx;
    scratchData->field_380.m[0][1] = lightVec->vy;
    scratchData->field_380.m[0][2] = lightVec->vz;
    gte_SetLightMatrix(&scratchData->field_380);

    var_a3  = &scratchData->field_2B8[offset];
    temp_t2 = D_800C4168.field_20;

    for (var_t0 = arg0->field_10; var_t0 < &arg0->field_10[arg0->field_2]; var_t0++)
    {
        *(u32*)&scratchData->field_3A0 = *(u32*)var_t0;

        scratchData->field_3AC.vx = scratchData->field_3A0.vx << 5;
        scratchData->field_3AC.vy = scratchData->field_3A0.vy << 5;
        scratchData->field_3AC.vz = scratchData->field_3A0.vz << 5;

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80057B7C); // 0x80057B7C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005801C); // 0x8005801C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80059D50); // 0x80059D50

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80059E34); // 0x80059E34

void func_8005A21C(s_func_80057344* arg0, void* arg1, void* arg2, s_func_8005A21C* arg3) // 0x8005A21C
{
    s16                var_v1;
    u32                temp_s3;
    u32                temp_s4;
    s_func_80057344_8* temp_s1;
    s_func_8005759C*   var_s0;
    s_GteScratchData*  scratchData;

    scratchData = PSX_SCRATCH_ADDR(0);

    if (D_800C4168.field_1 != 0)
    {
        if (arg3->field_1C < (1 << D_800C4168.field_14))
        {
            var_v1 = 4096 - (D_800C4168.field_CC[(s32)(arg3->field_1C << 7) >> D_800C4168.field_14] << 4);
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

    temp_s1 = arg0->field_8;
    var_s0  = temp_s1->field_C;
    temp_s4 = temp_s1->field_9;
    temp_s3 = temp_s1->field_A;

    for (var_s0 = temp_s1->field_C; var_s0 < &temp_s1->field_C[temp_s1->field_8]; var_s0++)
    {
        func_8005A900(var_s0, temp_s4, scratchData, arg3);

        if (D_800C4168.field_0 != 0)
        {
            func_8005AA08(var_s0, temp_s3, scratchData);
        }

        func_8005AC50(var_s0, scratchData, arg1, arg2);
    }
}

void func_8005A42C(s_GteScratchData* scratchData, s32 arg1) // 0x8005A42C
{
    s32 alpha = FP_ALPHA(1.0f) - FP_MULTIPLY(arg1, D_800C4168.field_20, Q12_SHIFT);

    gte_lddp(alpha);
    gte_ldrgb(&D_800C4168.field_28);
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

    var_s0 = (scratchData->screenPos_3DC.vx * scratchData->screenPos_3DC.vy) + (scratchData->screenPos_3DC.vy * (scratchData->depthP_3E0 >> 4));
    var_s0 >>= 5;
    var_s0 -= 16;
    if (var_s0 < 0)
    {
        var_s0 = 0;
    }

    var_v1 = (scratchData->screenPos_3DC.vx >> 1) + (scratchData->depthP_3E0 >> 2);
    if (var_v1 > 48)
    {
        var_v1 = 48;
    }

    var_s0 += var_v1;
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

    SetBackColor(FP_FROM((D_800C4168.field_24 + ((D_800C4168.field_28.r * var_a1) >> 7)) * alpha, Q12_SHIFT),
                 FP_FROM((D_800C4168.field_25 + ((D_800C4168.field_28.g * var_a1) >> 7)) * alpha, Q12_SHIFT),
                 FP_FROM((D_800C4168.field_26 + ((D_800C4168.field_28.b * var_a1) >> 7)) * alpha, Q12_SHIFT));
}

void func_8005A838(s32 arg0, s32 scale) // 0x8005A838
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005A900); // 0x8005A900

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005AA08); // 0x8005AA08

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005AC50); // 0x8005AC50

// Related to enviroment textures.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005B1A0); // 0x8005B1A0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005B1FC); // 0x8005B1FC

void func_8005B370(s_func_8005B370* arg0) // 0x8005B370
{
    arg0->field_14 = 0;
}

void func_8005B378(s_func_8005B370* arg0, s8* arg1) // 0x8005B378
{
    arg0->field_14 = 1;
    arg0->field_10 = 0;
    func_80056D64(arg0->field_8, arg1);
}

void func_8005B3A4(s_func_8005B3A4* arg0) // 0x8005B3A4
{
    arg0->field_C  = 0;
    arg0->field_8  = 0;
    arg0->field_14 = 0;
    arg0->field_10 = NO_VALUE;
}

void func_8005B3BC(char* filename, s_func_800566B4_sub* arg1) // 0x8005B3BC
{
    char sp10[12];

    // Some inline `memcpy`/`bcopy`/`strncpy`? those use `lwl`/`lwr`/`swl`/`swr` instead though
    // Example: casting `filename`/`arg1` to `u32*` and using `memcpy` does generate `lw`/`sw`,
    // but not in same order as this, guess it's some custom inline/macro instead.
    *(u32*)&sp10[0] = *(u32*)&arg1->unk_0[0];
    *(u32*)&sp10[4] = *(u32*)&arg1->unk_0[4];
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

void func_8005B46C(s32* arg0) // 0x8005B46C
{
    *arg0 = 0;
}

void func_8005B474(s32* arg0, u32 arg1, s32 idx) // 0x8005B474
{
    u32  temp_a2;
    u32  var_a1;
    u32* ptr;

    var_a1  = arg1;
    temp_a2 = var_a1 + (idx * 24);
    ptr     = arg0 + 1;

    for (; var_a1 < temp_a2; ptr++)
    {
        *ptr    = var_a1;
        var_a1 += 24;
        *arg0  += 1;
    }
}

s_800C1450_0_4* func_8005B4BC(char* str, s_800C1450* arg1) // 0x8005B4BC
{
    s_800C1450_0_4* ptr;
    char            prevStr[8];
    s32             i;

    func_80056D64(prevStr, str);

    for (i = 0; i < arg1->field_0.count_0; ++i)
    {
        ptr = arg1->field_0.entries_4[i];

        // Fast string comparison. `s_800C1450_0_4::field_8` is also likely a `char[8]`.
        if (ptr->field_10 != NO_VALUE &&
            *(u32*)&prevStr[0] == ptr->field_8 && *(u32*)&prevStr[4] == ptr->field_C)
        {
            return ptr;
        }
    }

    return NULL;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005B55C); // 0x8005B55C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005B62C); // 0x8005B62C

void func_8005BF0C(s16 unused, s16 x, s16 y) // 0x8005BF0C
{
    Gfx_DebugStringPosition(x, y);
}

s16 func_8005BF38(s16 arg0) // 0x8005BF38
{
    s16 res;
    s16 temp;

    temp = arg0 & 0xFFF;
    res  = temp;

    if (temp > 0x800)
    {
        res = temp | 0xF000;
    }

    return res;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005BF58); // 0x8005BF58

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005C1CC); // 0x8005C1CC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005C478); // 0x8005C478

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005C7B0); // 0x8005C7B0

s32 func_8005C7D0(s_SubCharacter* chara, s32 moveSpeed) // 0x8005C7D0
{
    s32             i = 0;
    s_SubCharacter* npc;
    s_SubCharacter* player;

    if (chara == &g_SysWork.player_4C)
    {
        return NPC_COUNT_MAX;
    }

    npc    = &g_SysWork.npcs_1A0;
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

    temp_s1 = shRcos(chara->rotation_24.vy);
    temp_v0 = shRsin(chara->rotation_24.vy);

    chara->field_D8.field_0 = FP_FROM((temp_s0 * temp_s1) + (temp_s3 * temp_v0), Q12_SHIFT);
    chara->field_D8.field_2 = FP_FROM((-temp_s0 * temp_v0) + (temp_s3 * temp_s1), Q12_SHIFT);
    chara->field_D8.field_4 = FP_FROM((temp_s2 * temp_s1) + (temp_s4 * temp_v0), Q12_SHIFT);
    chara->field_D8.field_6 = FP_FROM((-temp_s2 * temp_v0) + (temp_s4 * temp_s1), Q12_SHIFT);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005C944); // 0x8005C944

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005CB20); // 0x8005CB20

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005CD38); // 0x8005CD38

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005D50C); // 0x8005D50C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005D86C); // 0x8005D86C

s32 func_8005D974() // 0x8005D974
{
    s32 val = func_8005D86C();

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005D9B8); // 0x8005D9B8

void func_8005DC1C(s32 arg0, VECTOR3* arg1, s32 arg2, s32 arg3)
{
	func_8005DC3C(arg0, arg1, arg2, arg3, 0);
}

void func_8005DC3C(s32 sfx, VECTOR3* pos, s32 arg2, s32 arg3, s32 arg4) // 0x8005DC3C
{
    s32 var_a2;
    s32 var_s1;

    if ((arg3 & (1 << 0)) || (g_GameWork.config_0.optSoundType_1E))
    {
        var_s1 = 0;
    }
    else
    {
        var_s1 = func_80040A64(pos);
    }

    if (arg2 >= 0x100)
    {
        arg2 = 0xFF;
    }
    else if (arg2 < 0)
    {
        arg2 = 0;
    }

    if (!(arg3 & 2))
    {
        var_a2 = func_8005D9B8(pos, arg2);
    }
    else
    {
        var_a2 = arg2;
    }

    if (var_a2 >= 0x100)
    {
        var_a2 = 0xFF;
    }

    if (arg3 & 4)
    {
        func_800463C0(sfx, var_s1, ~var_a2, arg4);
    }
    else
    {
        Sd_PlaySfx(sfx, var_s1, ~var_a2);
    }
}

void func_8005DD44(s32 arg0, VECTOR3* arg1, s32 arg2, s8 arg3) // 0x8005DD44
{
    s32 var_a2;
    s32 var_s1;

    if (g_GameWork.config_0.optSoundType_1E != 0)
    {
        var_s1 = 0;
    }
    else
    {
        var_s1 = func_80040A64(arg1);
    }

    if (arg2 >= 0x100)
    {
        arg2 = 0xFF;
    }
    else if (arg2 < 0)
    {
        arg2 = 0;
    }

    var_a2 = func_8005D9B8(arg1, arg2);
    if (var_a2 >= 0x100)
    {
        var_a2 = 0xFF;
    }

    func_80046620(arg0 & 0xFFFF, var_s1, ~var_a2 & 0xFF, arg3);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005DE0C); // 0x8005DE0C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005E0DC); // 0x8005E0DC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005E414); // 0x8005E414

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005E650); // 0x8005E650

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005E70C); // 0x8005E70C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005E7E0); // 0x8005E7E0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005E89C); // 0x8005E89C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005F55C); // 0x8005F55C

s32 func_8005F680(s_func_800699F8* arg0) // 0x8005F680
{
    s32 var_a0;
    s8 temp_v1;

    temp_v1 = arg0->field_8;
    var_a0 = 0;
    if ((temp_v1 == 0) || (temp_v1 == 0xC) || (temp_v1 == 7))
    {
        var_a0 = 1;
    }
    return var_a0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8005F6B0); // 0x8005F6B0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80060044); // 0x80060044

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800611C0); // 0x800611C0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800622B8); // 0x800622B8

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

    g_MapOverlayHeader.field_4C[idx].field_0  = arg0->vx;
    g_MapOverlayHeader.field_4C[idx].field_8  = arg0->vy;
    g_MapOverlayHeader.field_4C[idx].field_4  = arg0->vz;
    g_MapOverlayHeader.field_4C[idx].field_E  = arg1;
    g_MapOverlayHeader.field_4C[idx].field_D  = var;
    g_MapOverlayHeader.field_4C[idx].field_B  = TEST_RNG(2);
    g_MapOverlayHeader.field_4C[idx].field_C  = 6;
    g_MapOverlayHeader.field_4C[idx].field_10 = arg3 * FP_FLOAT_TO(5.0f, Q12_SHIFT);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80062708); // 0x80062708

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006342C); // 0x8006342C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80063A50); // 0x80063A50

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80064334); // 0x80064334

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80064F04); // 0x80064F04

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80064FC0); // 0x80064FC0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800652F4); // 0x800652F4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80065B94); // 0x80065B94

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80066184); // 0x80066184

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80066D90); // 0x80066D90

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", GameState_MapScreen_Update); // 0x80066EB0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80067914); // 0x80067914

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80068CC0); // 0x80068CC0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80068E0C); // 0x80068E0C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800692A4); // 0x800692A4

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80069860); // 0x80069860

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006993C); // 0x8006993C

void func_80069994(s_func_800699E4* arg0) // 0x80069994
{
    s32* ptr;

    arg0->field_30++;

    if (arg0->field_30 > 252)
    {
        arg0->field_30 = 0;

        // TODO: Is this memset/bzero?
        for (ptr = &arg0->field_34[0]; ptr < &arg0->field_34[256]; ptr++)
        {
            *ptr = 0;
        }
    }
}

void func_800699E4(s_func_800699E4* arg0) // 0x800699E4
{
    arg0->field_30++;
}

void func_800699F8(s_func_800699F8* coll, s32 posX, s32 posZ) // 0x800699F8
{
    s_func_8006AB50 sp10;
    VECTOR3         sp28;
    s_func_8006CC44 sp38;

    s32 temp_v0;

    sp28.vx = 0;
    sp28.vy = 0;
    sp28.vz = 0;

    temp_v0 = func_800426E4(posX, posZ);
    if (!temp_v0)
    {
        coll->groundHeight_0 = FP_METER(8.0f);
        coll->field_6        = 0;
        coll->field_4        = 0;
        coll->field_8        = 0;
        return;
    }

    sp10.position_0.vx = posX;
    sp10.position_0.vy = 0;
    sp10.position_0.vz = posZ;
    sp10.rotation_C.vx = 0;
    sp10.rotation_C.vy = 0;
    sp10.rotation_C.vz = 0;
    func_8006AB50(&sp38, &sp28, &sp10, 0);

    sp38.field_0_8  = 0;
    sp38.field_0_9  = 0;
    sp38.field_0_10 = 1;
    func_8006AD44(&sp38, temp_v0);

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

s32 func_80069B24(VECTOR3* vec0, VECTOR3* vec1, s_SubCharacter* chara) // 0x80069B24
{
    s32 var0; 
    s32 var1;

    var0 = SetSp(0x1F8003D8);
    var1 = func_80069BA8(vec0, vec1, chara, func_80069FFC(vec0, vec1, chara));
    SetSp(var0);
    return var1; 
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80069BA8); // 0x80069BA8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80069DF0); // 0x80069DF0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80069FFC); // 0x80069FFC

void func_8006A178(s_func_8006A178* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x8006A178
{
    arg0->field_0  = arg1;
    arg0->field_4  = arg2;
    arg0->field_8  = arg3;
    arg0->field_12 = 0;
    arg0->field_10 = 0;
    arg0->field_14 = 0;
    arg0->field_18 = 0xFFFF0000;
    arg0->field_C  = arg4;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006A1A4); // 0x8006A1A4

s32 func_8006A3B4(s32 arg0, s32 arg1, s32 arg2) // 0x8006A3B4
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006A42C); // 0x8006A42C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006A4A8); // 0x8006A4A8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006A940); // 0x8006A940

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

    result->field_C.vx = FP_FROM(vec->vx, Q4_SHIFT);
    result->field_C.vy = FP_FROM(vec->vy, Q4_SHIFT);
    result->field_C.vz = FP_FROM(vec->vz, Q4_SHIFT);

    result->field_8 = SquareRoot0(SQUARE(result->field_C.vx) + SQUARE(result->field_C.vz));

    if (result->field_8 != 0)
    {
        result->directionX_14 = FP_METER(result->field_C.vx) / result->field_8;
        result->directionZ_16 = FP_METER(result->field_C.vz) / result->field_8;
        angleXz               = ratan2(result->field_C.vz, result->field_C.vx);
        result->directionX_14 = shRcos(angleXz);
        result->directionZ_16 = shRsin(angleXz);
    }
    else
    {
        result->directionX_14 = FP_METER(1.0f);
        result->directionZ_16 = 0;
    }

    result->field_28     = FP_FROM(arg2->rotation_C.vz, Q4_SHIFT);
    result->positionX_18 = FP_FROM(arg2->position_0.vx, Q4_SHIFT);
    result->positionZ_1C = FP_FROM(arg2->position_0.vz, Q4_SHIFT);
    result->field_20     = result->positionX_18 + result->field_C.vx;
    result->field_24     = result->positionZ_1C + result->field_C.vz;
    result->field_2A     = FP_FROM(arg2->rotation_C.vy + arg2->position_0.vy, Q4_SHIFT);
    result->field_2C     = FP_FROM(arg2->rotation_C.vx + arg2->position_0.vy, Q4_SHIFT);
    result->field_0      = arg2->field_12;
}

void func_8006AD44(s_func_8006CC44* arg0, s_func_800699E4* arg1) // 0x8006AD44
{
    s32  temp_s4;
    s32* var_s0;
    s32  temp_s5;
    s32  var_s1;
    s32  var_s2;

    if ((arg1->field_8_8 == 0 && arg1->field_8_16 == 0 && arg1->field_8_24 == 0) || !func_8006AEAC())
    {
        return;
    }

    if (arg0->field_0_0 == 0)
    {
        func_80069994(arg1);
    }

    temp_s5 = arg0->field_A0;
    temp_s4 = (arg0->field_A0 + arg0->field_A2) - 1;

    for (var_s2 = arg0->field_A1; var_s2 < (arg0->field_A1 + arg0->field_A3); var_s2++)
    {
        var_s0 = &arg1->field_20[(var_s2 * arg1->field_1E) + temp_s5];

        for (var_s1 = temp_s5; var_s1 <= temp_s4; var_s1++, var_s0++)
        {
            func_8006B1C8(arg0, arg1, var_s0);
        }
    }

    if (arg0->field_0_0 == 0)
    {
        func_800699E4(arg1);
    }

    if (arg0->field_0_10)
    {
        func_8006C838(arg0, arg1);
        if (arg0->field_A4 != 0)
        {
            func_8006CA18(arg0, arg1, arg0->field_A4);
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006AEAC); // 0x8006AEAC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006B004); // 0x8006B004

void func_8006B1C8(s_func_8006CC44* arg0, s_func_800699E4* arg1, s_func_8006B1C8* arg2) // 0x8006B1C8
{
    s32 var;
    s32 i;
    u8  idx;

    for (i = arg2->field_0; i < arg2->field_4; i++)
    {
        idx = arg1->field_28[i];

        if (arg1->field_30 >= arg1->field_34[idx])
        {
            arg1->field_34[idx] = arg1->field_30 + 1;
            var                 = arg1->field_8_16;

            if (idx < var)
            {
                if (func_8006B318(arg0, arg1, idx) != 0)
                {
                    if (arg0->field_0_10)
                    {
                        func_8006B6E8(arg0, arg2);
                    }

                    if (arg0->field_0_8 || arg0->field_0_9)
                    {
                        if (arg0->field_D9 == 0xFF)
                        {
                            func_8006B9C8(arg0);
                        }

                        if (arg0->field_D8 == 0xFF)
                        {
                            func_8006B8F8(arg0->unk_CC); // TODO: `unk_CC` is struct? 56 bytes?
                            func_8006B9C8(arg0);
                        }
                    }
                }
            }
            else if (func_8006C3D4(arg0, arg1, idx) != 0)
            {
                func_8006C45C(arg0);
            }
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006B318); // 0x8006B318

void func_8006B6E8(s_func_8006CC44* arg0, s_func_8006B1C8* arg1) // 0x8006B6E8
{
    // arg1 unused but `func_8006B1C8` passes second arg to this.
    s32                 index;
    s32                 temp_s1;
    s32                 temp_s2;
    s32                 temp_s3;
    s32                 temp_s4;
    s_func_8006CC44_A8* temp_s0;

    temp_s1 = arg0->field_D8;
    temp_s2 = arg0->field_D9;
    temp_s3 = arg0->field_DC;
    temp_s4 = arg0->field_DD;

    if (temp_s1 == 0xFF)
    {
        if (temp_s2 == 0xFF)
        {
            return;
        }
        index = arg0->field_DB;
    }
    else
    {
        index = arg0->field_DA;
    }

    temp_s0 = &arg0->field_A8[index];
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006B7E0); // 0x8006B7E0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006B8F8); // 0x8006B8F8

void func_8006B9C8(s_func_8006CC44* arg0) // 0x8006B9C8
{
    s32 field_28;

    if (arg0->field_D9 == 0xFF && arg0->field_EE < 0 &&
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006BB50); // 0x8006BB50

s32 func_8006BC34(s_func_8006BC34* arg0)
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
    
    return arg0->field_30 - (s16)var_v0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006BCC4); // 0x8006BCC4

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006BE40); // 0x8006BE40

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006BF88); // 0x8006BF88

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006C0C8); // 0x8006C0C8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006C1B8); // 0x8006C1B8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006C248); // 0x8006C248

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006C3D4); // 0x8006C3D4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006C45C); // 0x8006C45C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006C794); // 0x8006C794

void func_8006C838(s_func_8006CC44* arg0, s_func_800699E4* arg1) // 0x8006C838
{
    s32                 var_a0;
    s_func_800699E4_10* temp_a1;
    s_func_800699E4_18* temp_a0;
    s_func_8006CC44_A8* var_t1;

    if (!arg0->field_A4)
    {
        return;
    }

    if (arg0->field_C8 != 0xFF)
    {
        if (arg0->field_CA < arg0->field_7C)
        {
            temp_a0        = &arg1->ptr_18[arg0->field_C8 - arg1->field_8_16];
            arg0->field_7C = arg0->field_CA;
            arg0->field_80 = arg0->field_98 + arg1->field_0;
            arg0->field_84 = arg0->field_9A + arg1->field_4;
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
            temp_a1 = &arg1->ptr_10[var_t1->field_1];

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
                arg0->field_80 = arg0->field_98 + arg1->field_0;
                arg0->field_84 = arg0->field_9A + arg1->field_4;
                arg0->field_88 = temp_a1->field_8;
                arg0->field_8C = temp_a1->field_A;
                arg0->field_90 = temp_a1->field_6_5;
                arg0->field_94 = temp_a1->field_6_0;
            }
        }
    }
}

void func_8006CA18(s_func_8006CC44* arg0, s_func_800699E4* arg1, s_func_8006CA18* arg2) // 0x8006CA18
{
    s32                 startIdx;
    s32                 endIdx;
    s32                 var_a2;
    s_func_800699E4_10* ptr;
    u8*                 var_t1;

    startIdx = arg2->field_2;
    endIdx   = arg2->field_6;

    if (startIdx == endIdx)
    {
        return;
    }

    for (var_t1 = &arg1->field_2C[startIdx]; var_t1 < &arg1->field_2C[endIdx]; var_t1++)
    {
        ptr = &arg1->ptr_10[*var_t1];

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
                arg0->field_80 = arg0->field_98 + arg1->field_0;
                arg0->field_84 = arg0->field_9A + arg1->field_4;
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

s32 func_8006CC44(s32 arg0, s32 arg1, s_func_8006CC44* arg2) // 0x8006CC44
{
    if (arg2->field_94 != 12)
    {
        return FP_MULTIPLY(arg2->field_88, arg0 - arg2->field_80, Q12_SHIFT) +
               FP_MULTIPLY(arg2->field_8C, arg1 - arg2->field_84, Q12_SHIFT) +
               arg2->field_7C;
    }

    return FP_FLOAT_TO(0.5f, Q12_SHIFT);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006CC9C); // 0x8006CC9C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006CF18); // 0x8006CF18

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006D01C); // 0x8006D01C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006D2B4); // 0x8006D2B4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006D600); // 0x8006D600

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006D774); // 0x8006D774

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006D7EC); // 0x8006D7EC

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006DA08); // 0x8006DA08

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006DAE4); // 0x8006DAE4

static inline void func_8006DB3C_Inline(s8* arg0, VECTOR3* arg1, s32 arg2, u16* p)
{
    func_8006DAE4(arg0, arg1, arg2, (short)*p);
}

s32 func_8006DB3C(s_func_800700F8_2* arg0, VECTOR3* arg1, VECTOR3* arg2, s_func_800700F8* arg3) // 0x8006DB3C
{
    s32 sp28;
    s32 temp_s0;
    s32 temp_v0;
    s32 scratchAddr;

    temp_v0       = func_8006A1A4(&sp28, arg3, 1);
    arg0->field_0 = 0;

    if (func_8006DCE0((s32)PSX_SCRATCH, 1, 0, arg1, arg2, 0, 0, temp_v0, sp28) != 0)
    {
        temp_s0       = SetSp((s32)PSX_SCRATCH_ADDR(984));
        scratchAddr   = (s32)PSX_SCRATCH;
        arg0->field_0 = func_8006DEB0(arg0, scratchAddr);

        SetSp(temp_s0);
    }

    if (arg0->field_0 == 0)
    {
        func_8006DB3C_Inline(arg0, arg1, arg2, &((u8*)scratchAddr)[92]);
    }

    return arg0->field_0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006DC18); // 0x8006DC18

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

    arg0->field_2C.vx = FP_FROM(pos0->vx, Q4_SHIFT);
    arg0->field_2C.vy = FP_FROM(pos0->vy, Q4_SHIFT);
    arg0->field_2C.vz = FP_FROM(pos0->vz, Q4_SHIFT);

    arg0->field_50.vx = FP_FROM(pos1->vx, Q4_SHIFT);
    arg0->field_50.vy = FP_FROM(pos1->vy, Q4_SHIFT);
    arg0->field_50.vz = FP_FROM(pos1->vz, Q4_SHIFT);

    arg0->field_3C = arg0->field_2C.vx + arg0->field_50.vx;

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006DEB0); // 0x8006DEB0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006E0AC); // 0x8006E0AC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006E150); // 0x8006E150

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006E53C); // 0x8006E53C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006E78C); // 0x8006E78C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006EB8C); // 0x8006EB8C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006EE0C); // 0x8006EE0C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006EEB8); // 0x8006EEB8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006F250); // 0x8006F250

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006F3C4); // 0x8006F3C4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006F620); // 0x8006F620

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006F8FC); // 0x8006F8FC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006F99C); // 0x8006F99C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8006FAFC); // 0x8006FAFC

bool func_8006FD90(s_SubCharacter* chara, s32 arg1, s32 arg2, s32 arg3) // 0x8006FD90
{
    VECTOR3 sp10;
    VECTOR3 sp20;
    VECTOR3 sp30;
    VECTOR3 sp40;
    s32     var1;
    s32     deltaX;
    s32     deltaZ;
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

    deltaX = (g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx) >> 6;
    deltaZ = (g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) >> 6;
    dist   = SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)) << 6;

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
    if (func_8006DB3C(&var, &chara->position_18, &deltaPos, (s_func_800700F8*)chara) != 0)
    {
        result = var.field_10 == 0;
    }

    return result;
}

s32 func_800700F8(s_func_800700F8* arg0, s_func_800700F8* arg1) // 0x800700F8
{
    s_func_800700F8_2 sp10;
    VECTOR3           vec0;
    VECTOR3           vec1;

    vec0 = arg0->field_18;

    vec1.vx = arg1->field_18.vx - arg0->field_18.vx;
    vec1.vy = FP_METER(-0.1f);
    vec1.vz = arg1->field_18.vz - arg0->field_18.vz;

    return func_8006DB3C(&sp10, &vec0, &vec1, arg0) && sp10.field_10 == 0;
}

bool func_80070184(s_SubCharacter* chara, s32 arg1, s16 rotY) // 0x80070184
{
    s32 iVar0;
    s32 varX;
    s32 iVar1;
    s32 varY;
    s32 varZ;

    iVar0 = shRsin(rotY);
    varX  = chara->position_18.vx + FP_MULTIPLY(arg1, iVar0, Q12_SHIFT);
    iVar1 = shRcos(rotY);

    varY = chara->position_18.vy;
    varZ = chara->position_18.vz + FP_MULTIPLY(arg1, iVar1, Q12_SHIFT);

    // The calls to this often have a return, so assumed it just passes return of `func_80070084`.
    return func_80070084(chara, varX, varY, varZ);
}

bool func_80070208(s_func_800700F8* arg0, s32 arg1) // 0x80070208
{
    s_func_800700F8_2 var;
    VECTOR3           vec;
    s32               result;

    vec.vx = FP_MULTIPLY(arg1, shRsin(arg0->rotation_26.vy), Q12_SHIFT);
    vec.vy = 0;
    vec.vz = FP_MULTIPLY(arg1, shRcos(arg0->rotation_26.vy), Q12_SHIFT);

    result = false;
    if (func_8006DB3C(&var, &arg0->field_18, &vec, arg0) != 0)
    {
        result = var.field_10 > 0;
    }
    return result;
}

s32 func_8007029C(VECTOR3* arg0, s32 arg1, s16 angle) // 0x8007029C
{
    s8      vars[28];
    VECTOR3 vec;

    vec.vx = FP_MULTIPLY(arg1, shRsin(angle), Q12_SHIFT);
    vec.vy = 0;
    vec.vz = FP_MULTIPLY(arg1, shRcos(angle), Q12_SHIFT);

    return func_8006DB3C(&vars, &arg0[2], &vec, arg0);
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

void func_80070400(s_func_80070400_0* arg0, s_func_80070400_1* arg1, s_func_80070400_1* arg2) // 0x80070400
{
    s32 alpha;
    s32 invAlpha;

    // Compute alpha.
    if (arg0->field_4 & (1 << 0))
    {
        alpha = arg0->field_8 & 0xFFF;
    }
    else
    {
        alpha = arg0->field_E;
    }

    // Compute inverse alpha.
    invAlpha = FP_ALPHA(1.0f) - alpha;

    arg0->field_C8 = FP_FROM((arg1->field_0 * invAlpha) + (arg2->field_0 * alpha), Q12_SHIFT);
    arg0->field_CA = FP_FROM((arg1->field_2 * invAlpha) + (arg2->field_2 * alpha), Q12_SHIFT);
    arg0->field_CC = FP_FROM((arg1->field_4 * invAlpha) + (arg2->field_4 * alpha), Q12_SHIFT);
    arg0->field_CE = FP_FROM((arg1->field_6 * invAlpha) + (arg2->field_6 * alpha), Q12_SHIFT);
    arg0->field_DC = FP_FROM((arg1->field_10 * invAlpha) + (arg2->field_10 * alpha), Q12_SHIFT);
    arg0->field_DE = FP_FROM((arg1->field_12 * invAlpha) + (arg2->field_12 * alpha), Q12_SHIFT);
    arg0->field_D4 = FP_FROM((arg1->field_8 * invAlpha) + (arg2->field_8 * alpha), Q12_SHIFT);
    arg0->field_D8 = FP_FROM((arg1->field_C * invAlpha) + (arg2->field_C * alpha), Q12_SHIFT);
    arg0->field_DA = FP_FROM((arg1->field_E * invAlpha) + (arg2->field_E * alpha), Q12_SHIFT);
    arg0->field_D6 = FP_FROM((arg1->field_A * invAlpha) + (arg2->field_A * alpha), Q12_SHIFT);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800705E4); // 0x800705E4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800706E4); // 0x800706E4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80070B84); // 0x80070B84

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80070CF0); // 0x80070CF0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80070DF0); // 0x80070DF0

void func_800711C4(s32 arg0, s32 arg1) // 0x800711C4
{
    if (g_SysWork.player_4C.extra_128.field_20 == 25 || D_800C4580 == 0 || D_800C4582 == 0)
    {
        return;
    }

    if (D_800C4584 != 0)
    {
        g_SysWork.player_4C.extra_128.field_24 = arg1 + 10;
    }
    else
    {
        g_SysWork.player_4C.extra_128.field_24 = arg1 + 9;
    }
}

void func_80071224(s32 arg0, s32 arg1) // 0x80071224
{
    if (g_SysWork.player_4C.extra_128.field_20 == 25 || D_800C4580 == 0 || D_800C4582 == 0)
    {
        return;
    }

    if (D_800C4586 != 0)
    {
        g_SysWork.player_4C.extra_128.field_24 = arg1 + 9;
    }
    else
    {
        g_SysWork.player_4C.extra_128.field_24 = arg1 + 10;
    }
}

void func_80071284(s32 arg0) // 0x80071284
{
    if (g_GameWork.config_0.optExtraRetreatTurn_2A != 0)
    {
        if (D_800C4586 != 0)
        {
            D_800C454C = ((arg0 * g_DeltaTime0) * D_800C4586) >> 6; // Divide by `0x40 / 64`?
        }
        else if (D_800C4584 != 0)
        {
            D_800C454C = ((-arg0 * g_DeltaTime0) * D_800C4584) >> 6;
        }
    }
    else if (g_SysWork.player_4C.extra_128.field_24 == 4 || g_SysWork.player_4C.extra_128.field_24 == 24)
    {
        if (D_800C4586 != 0)
        {
            D_800C454C = ((-arg0 * g_DeltaTime0) * D_800C4586) >> 6;
        }
        else if (D_800C4584 != 0)
        {
            D_800C454C = ((arg0 * g_DeltaTime0) * D_800C4584) >> 6;
        }
    }
    else
    {
        if (D_800C4586 != 0)
        {
            D_800C454C = ((arg0 * g_DeltaTime0) * D_800C4586) >> 6;
        }
        else if (D_800C4584 != 0)
        {
            D_800C454C = ((-arg0 * g_DeltaTime0) * D_800C4584) >> 6;
        }
    }
}

void func_800713B4(s_SubCharacter* chara, s32 arg1) // 0x800713B4
{
    if (g_SysWork.player_4C.extra_128.field_24 != arg1)
    {
        chara->model_0.stateStep_3                   = 0;
        chara->model_0.state_2                       = 0;
        chara->properties_E4.player.properties_E4[5] = 0;
        chara->properties_E4.player.properties_E4[1] = 0;
        g_SysWork.field_235A                         = 0;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800713E8); // 0x800713E8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80071620); // 0x80071620

void Player_Logic_Update(s_SubCharacter* chara, void* arg1, GsCOORDINATE2* coord) // 0x800717D0
{
    // Called by `GameState_InGame_Update`, might be player update function.
    // - `chara` always `&g_SysWork.player_4C.chara_0`.
    // - `arg1`  always `0x8010A600`/`FS_BUFFER_0` (holds anim related data?).
    // - `coord` always `&g_SysWork.playerBoneCoords_890`.

    s_MainCharacterExtra* extra = &g_SysWork.player_4C.extra_128;

    if (g_DeltaTime0 != FP_TIME(0.0f))
    {
        Player_ReceiveDamage(chara, extra);

        if (g_Player_IsInWalkToRunTransition)
        {
            D_800C455C = 0;
            D_800C4558 = 0;
            D_800C45C0 = 0;
            D_800C45BE = 0;
            D_800C45BC = 0;
            D_800C457E = 0;
            D_800C4604 = 0;
            D_800C45F0 = 0;
            D_800C45E8 = 0;
            D_800C4582 = 0;
            D_800C45AE = 0;
            D_800C4586 = 0;
            D_800C4580 = 0;
            D_800C45AC = 0;
            D_800C4584 = 0;
        }

        if (!g_Player_DisableControl)
        {
            func_80071CE8(chara, extra, coord);
        }
        else
        {
            g_MapOverlayHeader.func_B8(chara, extra, coord);
        }

        if (!g_Player_DisableControl)
        {
            func_8007C0D8(chara, extra, coord);
        }
        else
        {
            g_MapOverlayHeader.func_BC(chara, extra, coord);
        }

        func_80071968(chara, extra, arg1, coord);
        func_8007D090(chara, extra, coord);
    }

    D_800C45B0.vx = 0;
    D_800C45B0.vz = 0;
}

static inline void func_80071968_Switch0()
{
    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != NO_VALUE)
    {
        switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
        {
            case EquippedWeaponId_KitchenKnife: 
            case EquippedWeaponId_SteelPipe: 
            case EquippedWeaponId_RockDrill: 
            case EquippedWeaponId_Hammer: 
            case EquippedWeaponId_Chainsaw: 
            case EquippedWeaponId_Katana: 
            case EquippedWeaponId_Axe: 
            case 10:
            case 11:
            case 12:
            case 14:
            case 15:
            case 16:
            case 17:
            case 20:
            case 21:
            case 22:
            case 24:
            case 25:
            case 26:
            case 27:
                func_8003DD80(1, 34); // `arg2` holds two values, split with `& 0xF0` / `& 0x0F` later on.
                break;

            case EquippedWeaponId_Handgun:
            case EquippedWeaponId_Shotgun:
            case EquippedWeaponId_HyperBlaster:
                func_8003DD80(1, 35);
                break;

            case EquippedWeaponId_HuntingRifle:
                func_8003DD80(1, 36);
                break;

            case 3:
            case 8:
            case 9:
            case 13:
            case 18:
            case 19:
            case 23:
            case 28:
            case 29:
            case 31:
                break;
        }
    }
    else
    {
        func_8003DD80(1, 34);
    }
}

static inline void func_80071968_Switch1()
{
    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != NO_VALUE)
    {
        switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
        {
            case EquippedWeaponId_KitchenKnife: 
            case EquippedWeaponId_SteelPipe: 
            case EquippedWeaponId_RockDrill: 
            case EquippedWeaponId_Hammer: 
            case EquippedWeaponId_Chainsaw: 
            case EquippedWeaponId_Katana: 
            case EquippedWeaponId_Axe: 
            case 10:
            case 11:
            case 12:
            case 14:
            case 15:
            case 16:
            case 17:
            case 20:
            case 21:
            case 22:
            case 24:
            case 25:
            case 26:
            case 27:
                func_8003DD80(1, 18);
                break;

            case EquippedWeaponId_Handgun:
            case EquippedWeaponId_Shotgun:
            case EquippedWeaponId_HyperBlaster:
                func_8003DD80(1, 19);
                break;

            case EquippedWeaponId_HuntingRifle:
                func_8003DD80(1, 20);
                break;

            case 3:
            case 8:
            case 9:
            case 13:
            case 18:
            case 19:
            case 23:
            case 28:
            case 29:
            case 31:
                break;
        }
    }
    else
    {
        func_8003DD80(1, (g_SysWork.field_2358 != 0) ? 18 : 17);
    }
}

// TODO: .rodata migration.
#ifdef NON_MATCHING
void func_80071968(s_SubCharacter* chara, s_MainCharacterExtra* extra, void* arg2, GsCOORDINATE2* coord)
{
    s_AnimInfo* animInfo;

    switch (g_SysWork.player_4C.extra_128.field_1C)
    {
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 76:
        case 77:
        case 78:
        case 79:
        case 80:
        case 83:
        case 84:
        case 85:
        case 86:
        case 87:
        case 88:
        case 93:
        case 94:
        case 95:
        case 97:
        case 98:
        case 99:
        case 100:
        case 102:
        case 103:
        case 104:
        case 105:
        case 107:
        case 108:
        case 111:
        case 112:
        case 118:
        case 119:
        case 122:
        case 134:
        case 136:
        case 137:
        case 138:
        case 139:
        case 141:
        case 142:
        case 143:
        case 144:
        case 145:
        case 146:
        case 147:
        case 148:
        case 152:
        case 162:
            break;

        case 54:
            func_80071968_Switch0();
            break;

        case 0: 
            switch (g_SysWork.player_4C.extra_128.field_20)
            {
                case 2:
                case 6:
                case 7:
                    func_80071968_Switch0();
                    break;
                
                default:
                    func_80071968_Switch1();
                    break;
            }
            break;

        default:  
        case 1: 
        case 2: 
        case 3: 
        case 4: 
        case 5: 
        case 6: 
        case 7: 
        case 8: 
        case 9: 
        case 10: 
        case 11: 
        case 12: 
        case 13: 
        case 14: 
        case 15: 
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 70:
        case 71:
        case 72:
        case 73:
        case 74:
        case 75:
        case 81:
        case 82:
        case 89:
        case 90:
        case 91:
        case 92:
        case 96:
        case 101:
        case 106:
        case 109:
        case 110:
        case 113:
        case 114:
        case 115:
        case 116:
        case 117:
        case 120:
        case 121:
        case 123:
        case 124:
        case 125:
        case 126:
        case 127:
        case 128:
        case 129:
        case 130:
        case 131:
        case 132:
        case 133:
        case 135:
        case 140:
        case 149:
        case 150:
        case 151:
        case 153:
        case 154:
        case 155:
        case 156:
        case 157:
        case 158:
        case 159:
        case 160:
        case 161:
            func_80071968_Switch1();
            break;
    }

    if (!g_Player_IsInWalkToRunTransition)
    {
        g_SysWork.player_4C.extra_128.field_18 = FP_FLOAT_TO(0.5f, Q12_SHIFT) - 1;
        animInfo                               = &g_MaybePlayerAnims[chara->model_0.anim_4.animIdx_0];
        animInfo->funcPtr_0(&chara->model_0, (s32)arg2, coord, animInfo);

        g_SysWork.player_4C.extra_128.field_18 = FP_FLOAT_TO(63.5f, Q12_SHIFT);
        animInfo                               = &g_MaybePlayerAnims[extra->model_0.anim_4.animIdx_0];
        animInfo->funcPtr_0(&extra->model_0, (s32)arg2, coord, animInfo);
        return;
    }

    g_SysWork.player_4C.extra_128.field_18 = FP_FLOAT_TO(0.5f, Q12_SHIFT) - 1;
    chara->model_0.anim_4.animIdx_0        = 0;
    animInfo                               = &g_MaybePlayerAnims[0];
    animInfo->funcPtr_0(chara, (s32)arg2, coord, animInfo);

    g_SysWork.player_4C.extra_128.field_18 = FP_FLOAT_TO(63.5f, Q12_SHIFT);
    animInfo                               = &g_MaybePlayerAnims[extra->model_0.anim_4.animIdx_0];
    animInfo->funcPtr_0(&extra->model_0, (s32)arg2, coord, animInfo);

    if (chara->model_0.anim_4.animIdx_0 == g_MaybePlayerAnims[0].animIdx_6)
    {
        g_Player_IsInWalkToRunTransition = false;
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80071968); // 0x80071968
#endif

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80071CE8); // 0x80071CE8

void func_80073FC0(s_MainCharacterExtra* extra, s32 arg1, s32 arg2, s32 arg3) // 0x80073FC0
{
    s32      temp;
    s_Model* model;

    temp  = g_SysWork.player_4C.extra_128.field_20;
    model = &g_SysWork.player_4C.chara_0.model_0;

    switch (g_SysWork.player_4C.extra_128.field_24)
    {
        case 1:
            g_SysWork.player_4C.extra_128.field_20 = 1;

        default:
            break;

        case 2:
            g_SysWork.player_4C.extra_128.field_20 = 2;
            break;

        case 4:
            g_SysWork.player_4C.extra_128.field_20 = 8;
            break;

        case 5:
            g_SysWork.player_4C.extra_128.field_20 = 4;
            break;

        case 6:
            g_SysWork.player_4C.extra_128.field_20 = 5;
            break;

        case 7:
            g_SysWork.player_4C.extra_128.field_20 = 6;
            break;

        case 8:
            g_SysWork.player_4C.extra_128.field_20 = 7;
            break;

        case 9:
            g_SysWork.player_4C.extra_128.field_20 = 9;
            break;

        case 10:
            g_SysWork.player_4C.extra_128.field_20 = 10;
            break;

        case 11:
            g_SysWork.player_4C.extra_128.field_20 = 13;
            break;

        case 3:
            g_SysWork.player_4C.extra_128.field_20 = 3;
            break;

        case 12:
            g_SysWork.player_4C.extra_128.field_20 = 14;
            break;

        case 13:
            g_SysWork.player_4C.extra_128.field_20 = 15;
            break;

        case 14:
            g_SysWork.player_4C.extra_128.field_20 = 16;
            break;

        case 15:
            g_SysWork.player_4C.extra_128.field_20 = 17;
            break;

        case 16:
            g_SysWork.player_4C.extra_128.field_20 = 18;
            break;

        case 0:
            switch (arg3)
            {
                case 0:
                case 2:
                    g_SysWork.player_4C.extra_128.field_20 = 0;
                    break;

                case 1:
                    if (D_800C4586 == 0)
                    {
                        if (D_800C4584 != 0)
                        {
                            g_SysWork.player_4C.extra_128.field_20 = 12;
                        }
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.field_20 = 11;
                    }
                    break;

                case 3:
                    if (D_800C4584 != 0)
                    {
                        g_SysWork.player_4C.extra_128.field_20 = 12;
                        break;
                    }

                    if (D_800C4586 == 0)
                    {
                        g_SysWork.player_4C.extra_128.field_20 = 0;
                    }
                    break;

                case 4:
                    if (D_800C4586 != 0)
                    {
                        g_SysWork.player_4C.extra_128.field_20 = 11;
                        break;
                    }

                    if (D_800C4584 == 0)
                    {
                        g_SysWork.player_4C.extra_128.field_20 = 0;
                    }
                    break;
            }
            break;
    }

    if (g_SysWork.player_4C.extra_128.field_20 != arg1)
    {
        extra->model_0.stateStep_3 = 0;
        extra->model_0.state_2     = 0;
    }

    switch (temp)
    {
        case 1:
            if (g_SysWork.player_4C.extra_128.field_20 != 2)
            {
                break;
            }

            extra->model_0.anim_4.animIdx_0      = model->anim_4.animIdx_0;
            extra->model_0.anim_4.keyframeIdx0_8 = model->anim_4.keyframeIdx0_8;
            extra->model_0.anim_4.time_4         = model->anim_4.time_4;
            extra->model_0.stateStep_3++;
            break;

        case 2:
            if (g_SysWork.player_4C.extra_128.field_20 != 1)
            {
                break;
            }

            extra->model_0.anim_4.animIdx_0      = model->anim_4.animIdx_0;
            extra->model_0.anim_4.keyframeIdx0_8 = model->anim_4.keyframeIdx0_8;
            extra->model_0.anim_4.time_4         = model->anim_4.time_4;
            extra->model_0.stateStep_3++;
            break;
    }
}

void func_80074254(s_SubCharacter* chara, s_MainCharacterExtra* extra) // 0x80074254
{
    s32 var0;

    if (func_80075504(chara, extra))
    {
        return;
    }

    var0 = (D_800C45C8.field_1 == 10) ? 1333 : 1314;

    switch (g_SysWork.player_4C.extra_128.field_20)
    {
        case 0:
            func_80071620(55, chara, 551, 1320);
            break;

        case 14:
            if (func_80071620(23, chara, 173, var0) != 0)
            {
                func_8008944C();
            }
            break;

        case 17:
            if (func_80071620(39, chara, 340, var0) != 0)
            {
                func_8008944C();
            }
            break;

        case 18:
            if (func_80071620(43, chara, 369, var0) != 0)
            {
                func_8008944C();
            }
            break;
    }

    func_800771BC(chara, extra);
}

bool func_80075504(s_SubCharacter* chara, s_MainCharacterExtra* extra) // 0x80075504
{
    s32 sp1C;
    s16 sp20;
    s16 sp22;
    s32 sp24;
    s32 sp28;
    s32 temp_s1_2;
    s16 temp_v0_3;
    s16 temp_v1_3;
    s32 i;
    s16 var_s0;
    s32 var_t0;

    bool func_80074350() // 0x80074350
    {
        s16 ssp20;
        s16 temp_a1;
        s32 var_s2;
        s32 var_s3;
        u8  equippedWeaponId;

        equippedWeaponId = g_SysWork.playerCombatInfo_38.equippedWeapon_F;

        switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
        {
            case EquippedWeaponId_KitchenKnife:
                var_s2 = 0x26B;
                var_s3 = 0x265;
                break;

            case EquippedWeaponId_Chainsaw:
                var_s2 = 0x276;
                var_s3 = 0x270;
                break;

            case EquippedWeaponId_RockDrill:
                var_s2 = 0x238;
                var_s3 = 0x238;
                break;

            case EquippedWeaponId_Axe:
                var_s2 = 0x271;
                var_s3 = 0x26A;
                break;

            case EquippedWeaponId_SteelPipe:
            case EquippedWeaponId_Hammer:
                var_s2 = 0x288;
                var_s3 = 0x282;
                break;

            case EquippedWeaponId_Katana:
                var_s2 = 0x26B;
                var_s3 = 0x264;
                break;

            default:
                var_s3 = 0;
                var_s2 = 0;
                break;
        }

        if (g_SysWork.player_4C.extra_128.field_1C == 1)
        {
            g_SysWork.player_4C.chara_0.properties_E4.player.properties_E4[8] += g_DeltaTime0;

            if (g_GameWork.config_0.optExtraWeaponCtrl_23 == 0)
            {
                D_800C455C = 0;
                D_800C4558 = 0;
                D_800C45C0 = 0;
                D_800C45BE = 0;
                D_800C45BC = 0;
                D_800C457E = 0;
                D_800C4604 = 0;
                D_800C45F0 = 0;
                D_800C45E8 = 0;
                D_800C4582 = 0;
                D_800C45AE = 0;
                D_800C4586 = 0;
                D_800C4580 = 0;
                D_800C45AC = 0;
                D_800C4584 = 0;
            }
        }

        if (extra->model_0.state_2 == 0)
        {
            D_800AFBEC = 0;
            D_800AFBF0 = 0;

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk1;
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
            {
                D_800AFBEC = 0;
                D_800AFBE8 = D_800C4570.field_8;
                D_800AF220 = D_800C4570.field_A >> 4;
            }
            else if (D_800C45BE != 0 && g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill)
            {
                D_800AFBEC = 1;
                D_800AFBE8 = D_800C4570.field_8 - 4;
                D_800AF220 = (D_800C4570.field_A >> 4) - 2;
            }
            else
            {
                D_800AFBEC = 0;

                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill || D_800AF217 == 0)
                {
                    D_800AFBE8 = D_800C4570.field_8;
                    D_800AF220 = D_800C4570.field_A >> 4;
                }
                else if (D_800AF217 == -1)
                {
                    D_800AFBE8 = D_800C4570.field_8 + 4;
                    D_800AF220 = (D_800C4570.field_A >> 4) + 2;
                }
                else
                {
                    D_800AFBE8 = D_800C4570.field_8 + 2;
                    D_800AF220 = (D_800C4570.field_A >> 4) + 1;
                }
            }

            extra->model_0.state_2++;

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
            {
                g_SysWork.playerCombatInfo_38.equippedWeapon_F %= 10;
            }

            g_SysWork.playerCombatInfo_38.equippedWeapon_F += D_800AFBEC * 10;

            D_800C44D0 = g_MaybePlayerAnims[D_800AFBE8].keyframeIdx0_C + D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_E;
            D_800C44D4 = g_MaybePlayerAnims[D_800AFBE8].keyframeIdx0_C + D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_E +
                         D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_F;
        }

        if (g_SysWork.field_2353 != NO_VALUE && g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
        {
            if (!g_GameWork.config_0.optExtraAutoAiming_2C)
            {
                if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 1))
                {
                    func_8005CD38(&sp1C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x238, 0xA000, 0);
                    func_8005D50C(&D_800AF21C, &D_800C4554, &D_800C4556, &g_SysWork.playerCombatInfo_38, sp1C, 0xE3);
                }
                else
                {
                    func_8005CD38(&sp1C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x238, 0x3000, 0);
                    func_8005D50C(&D_800AF21C, &D_800C4554, &D_800C4556, &g_SysWork.playerCombatInfo_38, sp1C, 0xE3);
                }
            }
            else
            {
                sp1C = g_SysWork.field_2353;
            }

            if (sp1C == NO_VALUE && sp1C == D_800AF21C)
            {
                D_800C4556 = NO_VALUE;
                D_800C4554 = NO_VALUE;
            }

            if (sp1C == g_SysWork.field_2353)
            {
                chara->rotation_24.pad = (ratan2((g_SysWork.npcs_1A0[sp1C].position_18.vx + g_SysWork.npcs_1A0[sp1C].field_D8.field_0) - g_SysWork.player_4C.chara_0.position_18.vx,
                                                (g_SysWork.npcs_1A0[sp1C].position_18.vz + g_SysWork.npcs_1A0[sp1C].field_D8.field_2) - g_SysWork.player_4C.chara_0.position_18.vz) +
                                          0x1000) &
                                         0xFFF;
            }
            else
            {
                chara->rotation_24.pad = chara->rotation_24.vy;
            }

            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 60;
                extra->model_0.stateStep_3++;
            }
        }
        else
        {
            if (g_SysWork.field_2353 != NO_VALUE && !g_GameWork.config_0.optExtraAutoAiming_2C)
            {
                if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)))
                {
                    func_8005CD38(&sp1C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x3000, 0x3000, 5);
                }
                else
                {
                    func_8005CD38(&sp1C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x1000, 0x1000, 5);
                }

                if (sp1C == g_SysWork.field_2353)
                {
                    temp_a1 = (ratan2((g_SysWork.npcs_1A0[sp1C].position_18.vx + g_SysWork.npcs_1A0[sp1C].field_D8.field_0) - g_SysWork.player_4C.chara_0.position_18.vx,
                                      (g_SysWork.npcs_1A0[sp1C].position_18.vz + g_SysWork.npcs_1A0[sp1C].field_D8.field_2) - g_SysWork.player_4C.chara_0.position_18.vz) +
                               0x1000) &
                              0xFFF;

                    func_8007FB34(chara->rotation_24.vy, temp_a1, &ssp20);
                    D_800C454C = g_DeltaTime0 * 0xF;

                    if (ABS(ssp20) >= 0x80)
                    {
                        if (ssp20 < 0)
                        {
                            D_800C454C = -D_800C454C;
                        }
                    }
                    else
                    {
                        chara->rotation_24.pad = chara->rotation_24.vy = temp_a1;
                        D_800C454C                                   = 0;
                    }
                }
            }
            else
            {
                sp1C                                                       = NO_VALUE;
                g_SysWork.player_4C.chara_0.properties_E4.player.field_122 = 0x400;
                chara->rotation_24.pad                                      = chara->rotation_24.vy;
            }

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk11)
                {
                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.animIdx_0 = D_800C4577 - 12;
                        extra->model_0.stateStep_3++;
                    }
                }
                else
                {
                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.animIdx_0 = D_800C4577;
                        extra->model_0.stateStep_3++;
                    }
                }
            }
            else if (D_800C45BE != 0 && g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill)
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.animIdx_0 = D_800C4577 - 4;
                    extra->model_0.stateStep_3++;
                }
            }
            else if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill || D_800AF217 == 0)
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.animIdx_0 = D_800C4577;
                    extra->model_0.stateStep_3++;
                }
            }
            else if (D_800AF217 == NO_VALUE)
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.animIdx_0 = D_800C4577 + 4;
                    extra->model_0.stateStep_3++;
                }
            }
            else
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.animIdx_0 = D_800C4577 + 2;
                    extra->model_0.stateStep_3++;
                }
            }
        }

        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
        {
            if ((g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) != 5 &&
                (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) != 2)
            {
                if (extra->model_0.anim_4.keyframeIdx0_8 >= D_800C44D0 && D_800C44D4 >= extra->model_0.anim_4.keyframeIdx0_8)
                {
                    if (!(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk2))
                    {
                        chara->field_44 = 1;

                        func_8005DC1C(D_800C4570.field_0, &chara->position_18, 0x80, 0);

                        chara->properties_E4.player.field_10C                       = 0x40;
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk2;
                    }
                }
                else if (D_800C44D4 < extra->model_0.anim_4.keyframeIdx0_8)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
                }
            }
            else if (g_SysWork.player_4C.chara_0.properties_E4.player.field_114 == 0)
            {
                if (extra->model_0.anim_4.keyframeIdx0_8 >= D_800C44D0 && D_800C44D4 >= extra->model_0.anim_4.keyframeIdx0_8 &&
                    !(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk2))
                {
                    chara->field_44                                             = 1;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk2;
                }
            }
            else
            {
                if (chara->field_44 <= 0)
                {
                    chara->field_44 = 1;
                }

                chara->properties_E4.player.field_10C = 0x40;
            }
        }
        else
        {
            if (extra->model_0.anim_4.keyframeIdx0_8 >= D_800C44D0 && D_800C44D4 >= extra->model_0.anim_4.keyframeIdx0_8 &&
                !(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk1))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk1;

                if (g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10 != 0)
                {
                    chara->field_44 = 1;

                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_HyperBlaster)
                    {
                        g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10--;
                        g_SavegamePtr->items_0[g_SysWork.playerCombatInfo_38.field_12].count_1--;

                        func_8005DC1C(D_800C4570.field_0, &chara->position_18, 0x80, 0);
                    }
                    else
                    {
                        func_8005DC1C(D_800C4570.field_0, &chara->position_18, 0x30, 0);
                    }

                    chara->properties_E4.player.field_10C = 0xC8;
                }
                else
                {
                    func_8005DC1C(D_800C4574, &chara->position_18, 0x80, 0);

                    chara->properties_E4.player.field_10C = 32;

                    extra->model_0.anim_4.keyframeIdx0_8 = D_800C44F0[D_800AF220].field_6 - 3;
                    extra->model_0.anim_4.time_4         = FP_TO(D_800C44F0[D_800AF220].field_6 - 3, Q12_SHIFT);

                    if (g_SysWork.player_4C.extra_128.field_24 == 20)
                    {
                        chara->model_0.anim_4.keyframeIdx0_8 = D_800C44F0[D_800AF220].field_6 - 3;
                        chara->model_0.anim_4.time_4         = FP_TO(D_800C44F0[D_800AF220].field_6 - 3, Q12_SHIFT);
                    }
                }
            }
        }

        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
        {
            if (extra->model_0.anim_4.animIdx_0 == 59 || extra->model_0.anim_4.animIdx_0 == 61 || extra->model_0.anim_4.animIdx_0 == 63 ||
                extra->model_0.anim_4.animIdx_0 == 59 || extra->model_0.anim_4.animIdx_0 == 61 || extra->model_0.anim_4.animIdx_0 == 63 ||
                extra->model_0.anim_4.animIdx_0 == 59 || extra->model_0.anim_4.animIdx_0 == 61 || extra->model_0.anim_4.animIdx_0 == 63)
            {
                if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[D_800AF220].field_6)
                {
                    extra->model_0.anim_4.animIdx_0      = 57;
                    extra->model_0.anim_4.keyframeIdx0_8 = D_800C44F0[0].field_6;
                    extra->model_0.anim_4.time_4         = FP_TO(extra->model_0.anim_4.keyframeIdx0_8, Q12_SHIFT);

                    if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk0)
                    {
                        g_SysWork.player_4C.extra_128.field_1C = 1;
                        g_SysWork.player_4C.extra_128.field_20 = 20;

                        if (g_SysWork.player_4C.extra_128.field_24 == 34)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 20;
                        }
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.field_1C = 0;
                        g_SysWork.player_4C.extra_128.field_20 = 19;
                        extra->model_0.state_2                 =
                        extra->model_0.stateStep_3             = 0;

                        if (g_SysWork.player_4C.extra_128.field_24 == 34)
                        {
                            g_SysWork.player_4C.extra_128.field_24                      = 20;
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                        }
                    }

                    g_SysWork.player_4C.chara_0.properties_E4.player.properties_E4[8] = 0;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C       &= ~PlayerFlag_Unk2;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C       &= ~PlayerFlag_Unk1;
                    g_SysWork.playerCombatInfo_38.equippedWeapon_F                   %= 10;
                    return true;
                }
            }
        }
        else if ((extra->model_0.anim_4.animIdx_0 == 61 || extra->model_0.anim_4.animIdx_0 == 73) &&
                 extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[D_800AF220].field_6)
        {
            if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk0)
            {
                g_SysWork.player_4C.extra_128.field_1C = 1;
                g_SysWork.player_4C.extra_128.field_20 = 20;

                if (g_SysWork.player_4C.extra_128.field_24 == 34)
                {
                    g_SysWork.player_4C.extra_128.field_24 = 20;
                }
            }
            else
            {
                g_SysWork.player_4C.extra_128.field_1C = 0;
                g_SysWork.player_4C.extra_128.field_20 = 19;
                extra->model_0.state_2                 =
                extra->model_0.stateStep_3             = 0;

                if (g_SysWork.player_4C.extra_128.field_24 == 34)
                {
                    g_SysWork.player_4C.extra_128.field_24                      = 20;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                    chara->model_0.state_2                                      =
                    chara->model_0.stateStep_3                                  = 0;
                }
            }

            D_800C4556                                                        = NO_VALUE;
            D_800C4554                                                        = NO_VALUE;
            g_SysWork.player_4C.chara_0.properties_E4.player.properties_E4[8] = 0;
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C       &= ~PlayerFlag_Unk1;
            return true;
        }

        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk6;

        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
        {
            if (D_800AFBEC == 0 && g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill)
            {
                if (extra->model_0.anim_4.keyframeIdx0_8 >= var_s3 &&
                    extra->model_0.anim_4.keyframeIdx0_8 < var_s2 &&
                    extra->model_0.anim_4.animIdx_0 == 63 && (D_800C45BE != 0 || D_800C45C0 != 0))
                {
                    D_800AFBF0 = 1;
                }
            }
        }

        if (D_800AFBF0 != 0)
        {
            if (extra->model_0.anim_4.animIdx_0 == 63 && extra->model_0.anim_4.keyframeIdx0_8 >= var_s2)
            {
                extra->model_0.stateStep_3 = 0;

                if (g_SysWork.player_4C.extra_128.field_24 == 34)
                {
                    chara->model_0.stateStep_3 = 0;
                }

                D_800AFBE8                                     = D_800C4570.field_8 - 2;
                D_800AF220                                     = (D_800C4570.field_A >> 4) - 1;
                D_800AFBEC                                     = 2;
                g_SysWork.playerCombatInfo_38.equippedWeapon_F = (equippedWeaponId % 10) + 20;

                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.animIdx_0 = D_800C4570.field_7 - 2;
                    extra->model_0.stateStep_3++;
                }

                D_800C44D0 = g_MaybePlayerAnims[D_800AFBE8].keyframeIdx0_C + D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_E;
                D_800C44D4 = g_MaybePlayerAnims[D_800AFBE8].keyframeIdx0_C + D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_E +
                             D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_F;
                D_800AFBF0 = 0;

                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
            }
        }

        return false;
    }

    sp1C = NO_VALUE;

    if (g_SysWork.player_4C.extra_128.field_20 != 20 && g_SysWork.player_4C.extra_128.field_20 != 25)
    {
        g_SysWork.player_4C.chara_0.properties_E4.player.properties_E4[8] = 0;
    }

    switch (g_SysWork.player_4C.extra_128.field_20)
    {
        case 0:
            if ((extra->model_0.anim_4.animIdx_0 == 5 || extra->model_0.anim_4.animIdx_0 == 7) &&
                extra->model_0.stateStep_3 != 0)
            {
                extra->model_0.stateStep_3 = 0;
            }

            if (chara->properties_E4.player.properties_E4[6] < FP_FLOAT_TO(10.0f, Q12_SHIFT) && chara->health_B0 >= FP_FLOAT_TO(30.0f, Q12_SHIFT))
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.animIdx_0 = 52;
                    extra->model_0.stateStep_3++;
                }

                func_80073FC0(extra, 0, 53, 1);
            }
            else
            {
                chara->properties_E4.player.properties_E4[1] = 0;

                if (extra->model_0.anim_4.animIdx_0 != 53)
                {
                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.animIdx_0 = 52;
                        extra->model_0.stateStep_3++;
                    }

                    func_80073FC0(extra, 0, 0x37, 1);
                }
                else
                {
                    extra->model_0.stateStep_3 = 0;
                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.animIdx_0 = 54;
                        extra->model_0.stateStep_3++;
                    }
                }
            }

            if (g_SysWork.player_4C.extra_128.field_20 != 0)
            {
                chara->properties_E4.player.properties_E4[1] = 0;
            }

            chara->rotation_24.pad = chara->rotation_24.vy;

            if (g_SysWork.player_4C.extra_128.field_20 == 0)
            {
                chara->properties_E4.player.properties_E4[1]++;

                if (chara->properties_E4.player.properties_E4[1] >= 0x12C)
                {
                    if (chara->health_B0 >= FP_FLOAT_TO(60.0f, Q12_SHIFT))
                    {
                        chara->properties_E4.player.properties_E4[1]        = 0;
                        g_SysWork.player_4C.extra_128.field_1C              = 2;
                        chara->model_0.state_2 = chara->model_0.stateStep_3 = 0;
                        extra->model_0.state_2 = extra->model_0.stateStep_3 = 0;
                        g_SysWork.player_4C.extra_128.field_20              = 0;
                        g_SysWork.player_4C.extra_128.field_24              = 0;
                        return true;
                    }
                }
            }
            break;

        default:
            break;

        case 1:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 4;
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.animIdx_0 == 5)
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            func_80073FC0(extra, 1, 5, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 2:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 6;
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.animIdx_0 == 7)
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            func_80073FC0(extra, 2, 7, 2);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 3:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & 8)
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.animIdx_0 = 18;
                    extra->model_0.stateStep_3++;
                }
            }
            else if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 20;
                extra->model_0.stateStep_3++;
            }

            func_80073FC0(extra, 3, 19, 0);
            func_80073FC0(extra, 3, 21, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 4:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 12;
                extra->model_0.stateStep_3++;
            }

            func_80073FC0(extra, 4, 13, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 5:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 10;
                extra->model_0.stateStep_3++;
            }

            func_80073FC0(extra, 5, 11, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 6:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 16;
                extra->model_0.stateStep_3++;
            }

            func_80073FC0(extra, 6, 17, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;

            if (extra->model_0.anim_4.animIdx_0 == 17)
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }
            break;

        case 7:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 14;
                extra->model_0.stateStep_3++;
            }

            func_80073FC0(extra, 7, 15, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;

            if (extra->model_0.anim_4.animIdx_0 == 15)
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }
            break;

        case 8:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 8;
                extra->model_0.stateStep_3++;
            }

            func_80073FC0(extra, 8, 9, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 9:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 28;
                extra->model_0.stateStep_3++;
            }

            func_80073FC0(extra, 9, 29, 0);

            if (extra->model_0.anim_4.animIdx_0 == 29)
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 10:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 30;
                extra->model_0.stateStep_3++;
            }

            func_80073FC0(extra, 10, 31, 0);

            if (extra->model_0.anim_4.animIdx_0 == 31)
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 11:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 26;
                extra->model_0.stateStep_3++;
            }

            func_80073FC0(extra, 11, 27, 3);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 12:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 24;
                extra->model_0.stateStep_3++;
            }

            func_80073FC0(extra, 12, 25, 4);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 13:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 32;
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.animIdx_0 == 33)
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            func_80073FC0(extra, 13, 33, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 14:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 22;
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.animIdx_0 == 23)
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            func_80073FC0(extra, 14, 23, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 15:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 36;
                extra->model_0.stateStep_3++;
            }

            func_80073FC0(extra, 0xF, 0x25, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 16:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 40;
                extra->model_0.stateStep_3++;
            }

            func_80073FC0(extra, 16, 41, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 17:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 38;
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.animIdx_0 == 39)
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            func_80073FC0(extra, 17, 39, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 18:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 42;
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.animIdx_0 == 43)
            {
                extra->model_0.anim_4.time_4 = chara->model_0.anim_4.time_4;
            }

            func_80073FC0(extra, 18, 43, 0);
            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 19:
            g_SysWork.field_2353 = NO_VALUE;
            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw ||
                g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.field_114 != 0)
                {
                    if (chara->field_44 <= 0)
                    {
                        chara->field_44 = 1;
                    }

                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.animIdx_0 = 68;
                        extra->model_0.stateStep_3++;
                    }
                }
                else
                {
                    extra->model_0.anim_4.animIdx_0      = 57;
                    extra->model_0.anim_4.keyframeIdx0_8 = D_800AF5C6;
                    extra->model_0.anim_4.time_4         = D_800AF5C6 << 12;
                }
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;
            chara->rotation_24.pad = chara->rotation_24.vy;

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
            {
                if (extra->model_0.anim_4.animIdx_0 != 57 &&
                    extra->model_0.anim_4.animIdx_0 != 69)
                {
                    if (D_800C45BE != 0 || D_800C45C0 != 0)
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk11;
                    }
                    else
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk11;

                        if (extra->model_0.stateStep_3 == 0)
                        {
                            extra->model_0.anim_4.animIdx_0 = 68;
                            extra->model_0.stateStep_3++;
                        }
                    }
                }
                else
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk11;
                }
            }
            break;

        case 20:
            g_SysWork.player_4C.chara_0.properties_E4.player.properties_E4[8] += g_DeltaTime0;
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C        &= ~PlayerFlag_Unk6;

            if (D_800C4586 != 0)
            {
                var_t0 = 1;
            }
            else
            {
                var_t0 = (D_800C4584 != 0) * 2;
            }

            if ((extra->model_0.anim_4.animIdx_0 != 59 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[1].field_6) &&
                (extra->model_0.anim_4.animIdx_0 != 61 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[2].field_6) &&
                (extra->model_0.anim_4.animIdx_0 != 65 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[4].field_6))
            {
                var_t0 = 0;
                chara->properties_E4.player.properties_E4[7]++;
            }
            else
            {
                chara->properties_E4.player.properties_E4[7] = 0;
            }

            if (var_t0 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
                chara->properties_E4.player.properties_E4[4]                 = D_800AF212;

                if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)))
                {
                    func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0xAAA, 0xA000, var_t0);
                }
                else
                {
                    func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x555, 0x3000, var_t0);
                }

                if (D_800AF21C == NO_VALUE)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk12;
                    chara->model_0.stateStep_3                                  = 0;
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_122  = 0x400;
                    g_SysWork.player_4C.extra_128.field_20                      = 19;
                    D_800C45C0                                                  = 0;
                    g_SysWork.player_4C.extra_128.field_1C                      = 0;
                    D_800C45BE                                                  = 0;

                    extra->model_0.state_2 = extra->model_0.stateStep_3 = 0;

                    if (g_SysWork.player_4C.extra_128.field_24 == 34)
                    {
                        g_SysWork.player_4C.extra_128.field_24 = 20;
                        chara->model_0.state_2                 =
                        chara->model_0.stateStep_3             = 0;
                    }
                }
                else
                {
                    g_SysWork.player_4C.extra_128.field_20                      = 23;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk12;
                    extra->model_0.state_2                                      =
                    extra->model_0.stateStep_3                                  = 0;
                }

                g_SysWork.field_2353 = D_800AF21C;
            }
            else
            {
                if (extra->model_0.state_2 != 0)
                {
                    if (D_800C4540.vx != g_SysWork.npcs_1A0[g_SysWork.field_2353].position_18.vx || D_800C4540.vy != g_SysWork.npcs_1A0[g_SysWork.field_2353].position_18.vy ||
                        D_800C4540.vz != g_SysWork.npcs_1A0[g_SysWork.field_2353].position_18.vz || D_800C45F8.vx != g_SysWork.player_4C.chara_0.position_18.vx ||
                        D_800C45F8.vy != g_SysWork.player_4C.chara_0.position_18.vy || D_800C45F8.vz != g_SysWork.player_4C.chara_0.position_18.vz)
                    {
                        if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)))
                        {
                            func_8005CD38(&sp1C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x238, 0xA000, 0);
                        }
                        else
                        {
                            func_8005CD38(&sp1C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x11C, 0x3000, 0);
                        }

                        D_800C4540 = g_SysWork.npcs_1A0[g_SysWork.field_2353].position_18;
                    }
                    else
                    {
                        sp1C = g_SysWork.field_2353;
                    }
                }
                else
                {
                    sp1C       = g_SysWork.field_2353;
                    D_800C4540 = g_SysWork.npcs_1A0[g_SysWork.field_2353].position_18;
                }

                if (sp1C == g_SysWork.field_2353 && sp1C != NO_VALUE)
                {
                    chara->rotation_24.pad = (ratan2((g_SysWork.npcs_1A0[sp1C].position_18.vx + g_SysWork.npcs_1A0[sp1C].field_D8.field_0) - g_SysWork.player_4C.chara_0.position_18.vx,
                                                    (g_SysWork.npcs_1A0[sp1C].position_18.vz + g_SysWork.npcs_1A0[sp1C].field_D8.field_2) - g_SysWork.player_4C.chara_0.position_18.vz) +
                                              0x1000) &
                                             0xFFF;
                }
                else
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk12;
                    chara->model_0.stateStep_3                                  = 0;
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_122  = 0x400;
                    g_SysWork.field_2353                                        = NO_VALUE;
                    g_SysWork.player_4C.extra_128.field_1C                      = 0;
                    g_SysWork.player_4C.extra_128.field_20                      = 19;
                    extra->model_0.state_2                                      =
                    extra->model_0.stateStep_3                                  = 0;
                }
            }

            if (extra->model_0.state_2 == 0)
            {
                extra->model_0.state_2++;
            }
            break;

        case 21:
            chara->rotation_24.pad = chara->rotation_24.vy;

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw ||
                g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.field_114 != 0)
                {
                    if (extra->model_0.stateStep_3 == 0)
                    {
                        extra->model_0.anim_4.animIdx_0 = 66;
                        extra->model_0.stateStep_3++;
                    }
                }
                else if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.animIdx_0 = 56;
                    extra->model_0.stateStep_3++;
                }

                if (((g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw &&
                      extra->model_0.anim_4.animIdx_0 == 57 &&
                      extra->model_0.anim_4.keyframeIdx0_8 >= (D_800C44F0[0].field_4 + 5)) ||
                     (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill &&
                      extra->model_0.anim_4.animIdx_0 == 57 &&
                      extra->model_0.anim_4.keyframeIdx0_8 >= (D_800C44F0[0].field_4 + 9))) &&
                    !(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & 4))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_114 = 0x3C000;

                    func_8004C564(g_SysWork.playerCombatInfo_38.equippedWeapon_F, 0);

                    chara->properties_E4.player.field_10C                        = 0x40;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk2;
                }
            }
            else if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_HuntingRifle)
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.animIdx_0 = 58;
                    extra->model_0.stateStep_3++;
                }
            }
            else
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.animIdx_0 = 56;
                    extra->model_0.stateStep_3++;
                }
            }

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw ||
                g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
            {
                if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6 ||
                    extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[5].field_6)
                {
                    if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6)
                    {
                        func_8004C564(g_SysWork.playerCombatInfo_38.equippedWeapon_F, 1);
                    }

                    g_SysWork.player_4C.extra_128.field_20                       = 19;
                    extra->model_0.state_2                                       =
                    extra->model_0.stateStep_3                                   = 0;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;

                    if (g_SysWork.player_4C.chara_0.properties_E4.player.field_114 != 0)
                    {
                        chara->field_44 = 1;
                    }
                }
            }
            else
            {
                if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6 ||
                    extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[1].field_6)
                {
                    g_SysWork.player_4C.extra_128.field_20 = 19;
                }
            }
            break;

        case 22:
        case 23:
            sp22 = 0;

            if (g_SysWork.player_4C.extra_128.field_20 == 22)
            {
                if (g_GameWork.config_0.optExtraAutoAiming_2C != 0)
                {
                    if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)))
                    {
                        func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x238, 0xa000, 0);
                    }
                    else
                    {
                        func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x238, 0x3000, 0);
                    }
                }
                else if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 1))
                {
                    func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x3000, 0x7000, 4);
                }
                else
                {
                    func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0xE66, 0x2199, 4);
                }

                g_SysWork.field_2353 = D_800AF21C;
            }

            D_800AF220 = 1;
            chara->properties_E4.player.properties_E4[7]++;

            if (g_GameWork.config_0.optExtraWeaponCtrl_23 == 0)
            {
                D_800C455C = 0;
                D_800C4558 = 0;
                D_800C45C0 = 0;
                D_800C45BE = 0;
                D_800C45BC = 0;
                D_800C457E = 0;
                D_800C4604 = 0;
                D_800C45F0 = 0;
                D_800C45E8 = 0;
                D_800C4582 = 0;
                D_800C45AE = 0;
                D_800C4586 = 0;
                D_800C4580 = 0;
                D_800C45AC = 0;
                D_800C4584 = 0;
            }

            extra->model_0.state_2++;

            if (g_SysWork.player_4C.extra_128.field_20 == 22)
            {
                if (extra->model_0.stateStep_3 == 0)
                {
                    extra->model_0.anim_4.animIdx_0 = 64;
                    extra->model_0.stateStep_3++;
                }
            }
            else if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 58;
                extra->model_0.stateStep_3++;
            }

            if (g_SysWork.field_2353 == NO_VALUE)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_122  = 0x400;
                g_SysWork.player_4C.extra_128.field_20                      = 19;
                g_SysWork.player_4C.extra_128.field_1C                      = 0;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk12;
                extra->model_0.state_2                                      =
                extra->model_0.stateStep_3                                  = 0;
                break;
            }

            if (g_GameWork.config_0.optExtraAutoAiming_2C == 0)
            {
                temp_v0_3 = ratan2((g_SysWork.npcs_1A0[g_SysWork.field_2353].position_18.vx + g_SysWork.npcs_1A0[g_SysWork.field_2353].field_D8.field_0) - g_SysWork.player_4C.chara_0.position_18.vx,
                                   (g_SysWork.npcs_1A0[g_SysWork.field_2353].position_18.vz + g_SysWork.npcs_1A0[g_SysWork.field_2353].field_D8.field_2) - g_SysWork.player_4C.chara_0.position_18.vz);

                temp_s1_2 = (temp_v0_3 + 0x1000) & 0xFFF;

                switch (extra->model_0.anim_4.animIdx_0)
                {
                    case 59:
                    case 65:
                        if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[D_800AF220].field_6)
                        {
                            chara->rotation_24.vy = temp_s1_2;
                        }
                        break;
                }

                func_8007FB34(chara->rotation_24.vy, temp_s1_2, &sp20);

                D_800C454C = ((extra->model_0.state_2 * 3) + 12) * g_DeltaTime0;
                D_800C454C = CLAMP(D_800C454C, 0, 0xFFF);

                if (ABS(sp20) >= 0x80)
                {
                    if (sp20 < 0)
                    {
                        D_800C454C = -D_800C454C;
                    }
                }
                else
                {
                    chara->rotation_24.vy  = temp_s1_2;
                    D_800C454C             = 0;
                    chara->rotation_24.pad = temp_s1_2;

                    if (g_SysWork.player_4C.extra_128.field_20 == 22)
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk8;
                    }
                    else
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk8;
                    }

                    if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk9)
                    {
                        if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[4].field_6)
                        {
                            g_SysWork.player_4C.extra_128.field_20 = 25;

                            if (g_SysWork.player_4C.extra_128.field_24 == 20)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 34;
                                chara->model_0.state_2                 =
                                chara->model_0.stateStep_3             = 0;
                            }

                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
                            extra->model_0.state_2                                      =
                            extra->model_0.stateStep_3                                  = 0;
                        }
                    }
                    else if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[4].field_6)
                    {
                        g_SysWork.player_4C.extra_128.field_20 = 20;
                        extra->model_0.state_2                 =
                        extra->model_0.stateStep_3             = 0;
                    }
                }

                chara->rotation_24.pad = chara->rotation_24.vy;
                break;
            }

            temp_v0_3 = ratan2((g_SysWork.npcs_1A0[g_SysWork.field_2353].position_18.vx +
                                g_SysWork.npcs_1A0[g_SysWork.field_2353].field_D8.field_0) -
                               g_SysWork.player_4C.chara_0.position_18.vx,
                                (g_SysWork.npcs_1A0[g_SysWork.field_2353].position_18.vz +
                                 g_SysWork.npcs_1A0[g_SysWork.field_2353].field_D8.field_2) -
                                g_SysWork.player_4C.chara_0.position_18.vz);

            temp_s1_2 = (temp_v0_3 + 0x1000) & 0xFFF;

            func_8007FB34(chara->rotation_24.vy, temp_s1_2, &sp20);

            sp20 = CLAMP(sp20, -0x180, 0x180);

            temp_v1_3 = g_DeltaTime0 * 0xF;
            temp_v1_3 = CLAMP(temp_v1_3, 0, 0xFFF);
            var_s0    = temp_v1_3;

            func_8007FB34(chara->rotation_24.pad, temp_s1_2, &sp22);

            if (ABS(sp22) > 0x80)
            {
                if (sp22 < 0)
                {
                    var_s0 = -var_s0;
                }

                chara->rotation_24.pad = (chara->rotation_24.pad + (var_s0 >> 4) + 0x1000) & 0xFFF;
            }
            else
            {
                chara->rotation_24.pad = chara->rotation_24.vy + sp20;

                if (g_SysWork.player_4C.extra_128.field_20 == 22)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk8;
                }
                else
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk8;
                }

                if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk9)
                {
                    if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[4].field_6)
                    {
                        g_SysWork.player_4C.extra_128.field_20 = 25;

                        if (g_SysWork.player_4C.extra_128.field_24 == 20)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 34;
                            chara->model_0.state_2                 =
                            chara->model_0.stateStep_3             = 0;
                        }

                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
                        extra->model_0.state_2                                      =
                        extra->model_0.stateStep_3                                  = 0;
                    }
                }
                else if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[4].field_6)
                {
                    g_SysWork.player_4C.extra_128.field_20              = 20;
                    extra->model_0.state_2 = extra->model_0.stateStep_3 = 0;
                }
            }
            break;

        case 24:
            D_800AF220 = D_800C4570.field_A & 0xF;

            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = D_800C4570.field_6;
                extra->model_0.stateStep_3++;
            }

            if (extra->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[D_800AF220].field_4 ||
                ((g_SysWork.player_4C.extra_128.field_24 == 2 || g_SysWork.player_4C.extra_128.field_24 == 7 ||
                  g_SysWork.player_4C.extra_128.field_24 == 8) &&
                 (extra->model_0.anim_4.keyframeIdx0_8 <= D_800C44F0[D_800AF220].field_6)))
            {
                switch (g_SysWork.player_4C.extra_128.field_24)
                {
                    case 2:
                        g_SysWork.player_4C.extra_128.field_20 = 2;
                        break;

                    case 7:
                        g_SysWork.player_4C.extra_128.field_20 = 6;
                        break;

                    case 28:
                        g_SysWork.player_4C.extra_128.field_20 = 7;
                        break;

                    default:
                        g_SysWork.player_4C.extra_128.field_20 = 0;
                        break;
                }

                extra->model_0.state_2 = extra->model_0.stateStep_3 = 0;
                if (g_SysWork.player_4C.extra_128.field_24 == 0)
                {
                    chara->model_0.state_2 = chara->model_0.stateStep_3 = 0;
                }

                g_SysWork.field_2353 = NO_VALUE;
            }

            chara->rotation_24.pad = chara->rotation_24.vy;
            break;

        case 25:
            if (func_80074350() != 0)
            {
                return true;
            }
            break;

        case 26:
            if (extra->model_0.stateStep_3 == 0)
            {
                extra->model_0.anim_4.animIdx_0 = 62;
                extra->model_0.stateStep_3++;
            }

            if ((D_800AF624 + D_800C4570.field_9) <= extra->model_0.anim_4.keyframeIdx0_8 &&
                !(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk2))
            {
                func_8005DC1C(D_800C4570.field_2, &chara->position_18, 0x80, 0);

                chara->properties_E4.player.field_10C                       = 0x20;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk2;
            }

            if (extra->model_0.anim_4.keyframeIdx0_8 == D_800AF626)
            {
                D_800AF21C                                                  = NO_VALUE;
                g_SysWork.player_4C.extra_128.field_20                      = 19;
                g_SysWork.field_2353                                        = NO_VALUE;
                g_SysWork.player_4C.extra_128.field_1C                      = 0;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
                extra->model_0.anim_4.animIdx_0                             = 57;
                extra->model_0.anim_4.keyframeIdx0_8                        = 588;
                extra->model_0.anim_4.time_4                                = 0x24C000;

                if (g_SysWork.player_4C.extra_128.field_24 == 35)
                {
                    g_SysWork.player_4C.extra_128.field_24 = 20;
                }

                if (g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11 != 0)
                {
                    sp24 = g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10;
                    sp28 = g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11;

                    func_80054FC0(&sp24, &sp28, g_SysWork.playerCombatInfo_38.equippedWeapon_F);

                    g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10 = sp24;
                    g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11   = sp28;

                    for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
                    {
                        if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombatInfo_38.equippedWeapon_F + InventoryItemId_KitchenKnife))
                        {
                            g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10;
                        }
                        if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombatInfo_38.equippedWeapon_F + InventoryItemId_Handgun))
                        {
                            g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11;
                        }
                    }
                }
            }
            break;
    }

    return false;
}

void func_800771BC(s_SubCharacter* chara, s_MainCharacterExtra* extra) // 0x800771BC
{
    s32 sp18;
    s32 sp1C;
    s32 i;

    switch (g_SysWork.player_4C.extra_128.field_20)
    {
        case 0:
        case 1:
        case 4:
        case 5:
        case 8:
        case 11:
        case 12:
            if (!g_Player_IsInWalkToRunTransition)
            {
                if ((D_800C457E != 0 && g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_KitchenKnife) ||
                    g_SysWork.playerCombatInfo_38.isAiming_13)
                {
                    g_SysWork.playerCombatInfo_38.isAiming_13 = 1;

                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
                    {
                        D_800AF21C = NO_VALUE;
                    }
                    else
                    {
                        if (g_GameWork.config_0.optExtraAutoAiming_2C != 0)
                        {
                            if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 1))
                            {
                                func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x238, 0xA000, 0);
                            }
                            else
                            {
                                func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x238, 0x3000, 0);
                            }
                        }
                        else if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 1))
                        {
                            func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x3000, 0x7000, 4);
                        }
                        else
                        {
                            func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0xE66, 0x2199, 4);
                        }
                    }

                    g_SysWork.field_2353 = D_800AF21C;
                    if (g_SysWork.field_2353 == NO_VALUE)
                    {
                        g_SysWork.player_4C.extra_128.field_20                     = 21;
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_122 = 0x400;
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.field_1C = 1;
                        g_SysWork.player_4C.extra_128.field_20 = 22;
                    }

                    if (g_SysWork.player_4C.extra_128.field_24 == 0)
                    {
                        g_SysWork.player_4C.extra_128.field_24 = 20;
                        chara->model_0.stateStep_3             = 0;
                        chara->model_0.state_2                 = 0;
                    }
                    else if (g_SysWork.player_4C.extra_128.field_24 < 20)
                    {
                        g_SysWork.player_4C.extra_128.field_24 += 20;
                    }

                    extra->model_0.stateStep_3                   = 0;
                    extra->model_0.state_2                       = 0;
                    chara->properties_E4.player.properties_E4[7] = 0;

                    if (g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11 != 0)
                    {
                        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
                        {
                            sp18 = g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10;
                            sp1C = g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11;

                            func_80054FC0(&sp18, &sp1C, g_SysWork.playerCombatInfo_38.equippedWeapon_F);

                            g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10 = sp18;
                            g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11   = sp1C;
                        }
                    }

                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
                    {
                        for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
                        {
                            if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombatInfo_38.equippedWeapon_F + InventoryItemId_KitchenKnife))
                            {
                                g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10;
                            }
                            if (g_SavegamePtr->items_0[i].id_0 == (g_SysWork.playerCombatInfo_38.equippedWeapon_F + InventoryItemId_Handgun))
                            {
                                g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11;
                            }
                        }
                    }
                }
            }
            break;
    }

    switch (g_SysWork.player_4C.extra_128.field_20)
    {
        case 0:
        case 1:
        case 4:
        case 5:
        case 8:
        case 11:
        case 12:
        case 19:
            if (func_8007F95C() != false)
            {
                if (D_800C45BE != 0)
                {
                    g_SysWork.player_4C.extra_128.field_1C = 6;
                    chara->model_0.stateStep_3             = 0;
                    chara->model_0.state_2                 = 0;
                    extra->model_0.stateStep_3             = 0;
                    extra->model_0.state_2                 = 0;
                    g_SysWork.player_4C.extra_128.field_20 = 0;
                    g_SysWork.player_4C.extra_128.field_24 = 0;
                    return;
                }

                if (D_800C45C0 != 0)
                {
                    g_SysWork.player_4C.extra_128.field_1C = 5;
                    chara->model_0.stateStep_3             = 0;
                    chara->model_0.state_2                 = 0;
                    extra->model_0.stateStep_3             = 0;
                    extra->model_0.state_2                 = 0;
                    g_SysWork.player_4C.extra_128.field_20 = 0;
                    g_SysWork.player_4C.extra_128.field_24 = 0;
                    return;
                }
            }
            break;
    }

    switch (g_SysWork.player_4C.extra_128.field_20)
    {
        case 19:
        case 20:
            if ((g_GameWork.config_0.optExtraWeaponCtrl_23 != 0 && D_800C457E == 0) ||
                (g_GameWork.config_0.optExtraWeaponCtrl_23 == 0 && D_800C457E != 0))
            {
                chara->properties_E4.player.properties_E4[4]                = 0;
                g_SysWork.player_4C.extra_128.field_20                      = 24;
                g_SysWork.field_2353                                        = NO_VALUE;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk0;
                g_SysWork.player_4C.extra_128.field_1C                      = 0;
                g_SysWork.playerCombatInfo_38.isAiming_13                   = 0;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;

                if (g_SysWork.player_4C.extra_128.field_24 == 20 ||
                    g_SysWork.player_4C.extra_128.field_24 == 34)
                {
                    g_SysWork.player_4C.extra_128.field_24 = 0;
                    chara->model_0.stateStep_3             = 0;
                    chara->model_0.state_2                 = 0;

                    extra->model_0.stateStep_3 = 0;
                    extra->model_0.state_2     = 0;
                    break;
                }

                if (g_SysWork.player_4C.extra_128.field_24 >= 21)
                {
                    g_SysWork.player_4C.extra_128.field_24 -= 20;
                }

                extra->model_0.stateStep_3 = 0;
                extra->model_0.state_2     = 0;
                break;
            }

            if ((D_800C45BE != 0 || D_800C45C0 != 0) &&
                g_SysWork.player_4C.extra_128.field_24 != 29 &&
                g_SysWork.player_4C.extra_128.field_24 != 30)
            {
                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
                {
                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw ||
                        g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
                    {
                        if ((extra->model_0.anim_4.animIdx_0 != 57 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[0].field_6) &&
                            (extra->model_0.anim_4.animIdx_0 != 59 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[1].field_6) &&
                            (extra->model_0.anim_4.animIdx_0 != 69 ||
                             extra->model_0.anim_4.keyframeIdx0_8 < D_800C44F0[6].field_4 ||
                             D_800C44F0[6].field_6 < extra->model_0.anim_4.keyframeIdx0_8) &&
                            (extra->model_0.anim_4.animIdx_0 != 61 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[2].field_6) &&
                            (extra->model_0.anim_4.animIdx_0 != 63 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[3].field_6) &&
                            (extra->model_0.anim_4.animIdx_0 != 67 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[5].field_6))
                        {
                            break;
                        }
                    }
                    else
                    {
                        if ((extra->model_0.anim_4.animIdx_0 != 57 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[0].field_6) &&
                            (extra->model_0.anim_4.animIdx_0 != 59 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[1].field_6) &&
                            (extra->model_0.anim_4.animIdx_0 != 61 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[2].field_6) &&
                            (extra->model_0.anim_4.animIdx_0 != 63 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[3].field_6))
                        {
                            break;
                        }
                    }
                }
                else
                {
                    if ((extra->model_0.anim_4.animIdx_0 != 57 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[0].field_6) &&
                        (extra->model_0.anim_4.animIdx_0 != 59 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[1].field_6) &&
                        (extra->model_0.anim_4.animIdx_0 != 61 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[2].field_6) &&
                        (extra->model_0.anim_4.animIdx_0 != 63 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[3].field_6) &&
                        (extra->model_0.anim_4.animIdx_0 != 65 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[4].field_6) &&
                        (extra->model_0.anim_4.animIdx_0 != 73 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[8].field_6) &&
                        (extra->model_0.anim_4.animIdx_0 != 69 || extra->model_0.anim_4.keyframeIdx0_8 != D_800C44F0[6].field_4))
                    {
                        break;
                    }
                }

                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk0;

                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
                {
                    if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)))
                    {
                        func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x3000, 0x3000, 5);
                    }
                    else
                    {
                        func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x1000, 0x1000, 5);
                    }

                    g_SysWork.field_2353 = D_800AF21C;
                }
                else
                {
                    if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & PlayerFlag_Unk0))
                    {
                        func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x7000, 0x7000, 5);
                    }
                    else
                    {
                        func_8005CD38(&D_800AF21C, &g_SysWork.player_4C.chara_0.properties_E4.player.field_122, &g_SysWork.playerCombatInfo_38, 0x2199, 0x2199, 5);
                    }
                }

                switch (D_800AF21C)
                {
                    default:
                        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
                        {
                            g_SysWork.player_4C.extra_128.field_1C                      = 1;
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk0 | PlayerFlag_Unk9;

                            if (g_SysWork.field_2353 != D_800AF21C)
                            {
                                g_SysWork.player_4C.extra_128.field_20 = 23;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.field_20 = 25;

                                if (g_SysWork.player_4C.extra_128.field_24 == 20)
                                {
                                    g_SysWork.player_4C.extra_128.field_24 = 34;
                                    chara->model_0.stateStep_3             = 0;
                                    chara->model_0.state_2                 = 0;
                                }
                            }

                            g_SysWork.field_2353 = D_800AF21C;
                            break;
                        }

                        g_SysWork.player_4C.extra_128.field_20 = 25;

                        if (g_SysWork.player_4C.extra_128.field_24 == 20)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 34;
                            chara->model_0.stateStep_3             = 0;
                            chara->model_0.state_2                 = 0;
                        }

                    case NO_VALUE:
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_122  = 0x400;
                        g_SysWork.player_4C.extra_128.field_20                      = 25;
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;

                        if (g_SysWork.player_4C.extra_128.field_24 == 20)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 34;
                            chara->model_0.stateStep_3             = 0;
                            chara->model_0.state_2                 = 0;
                        }
                        break;
                }

                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
                {
                    if (g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10 == 0 &&
                        (g_SavegamePtr->equippedWeapon_AA >> 5) == 5 &&
                        g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11 != 0)
                    {
                        g_SysWork.player_4C.extra_128.field_20                      = 26;
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;

                        if (g_SysWork.player_4C.extra_128.field_24 == 20 ||
                            g_SysWork.player_4C.extra_128.field_24 == 34)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 35;
                            chara->model_0.stateStep_3             = 0;
                            chara->model_0.state_2                 = 0;
                        }
                    }
                }
                else
                {
                    g_SysWork.player_4C.extra_128.field_20 = 25;

                    if (g_SysWork.player_4C.extra_128.field_24 == 20 ||
                        (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == 1 ||
                        (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == 4 ||
                        (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == 2 ||
                        (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == 6)
                    {
                        g_SysWork.player_4C.extra_128.field_24 = 34;
                        chara->model_0.stateStep_3             = 0;
                        chara->model_0.state_2                 = 0;
                    }
                }

                extra->model_0.stateStep_3 = 0;
                extra->model_0.state_2     = 0;
            }
            else
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
            }
            break;
    }
}

void func_80077BB8(s_SubCharacter* chara, s32 arg1, s32 animIdx, s32 keyframeIdx, s32 arg4, s32 arg5, s32 arg6) // 0x80077BB8
{
    s16 temp;

    if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
    {
        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= ((g_DeltaTime0 * 0x666) / 136) >> 1;
        if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
        {
            g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
        }
    }

    if (chara->model_0.stateStep_3 == 0)
    {
        chara->model_0.anim_4.animIdx_0 = arg1;
        chara->model_0.stateStep_3++;
    }

    if (g_SysWork.player_4C.extra_128.field_20 != 22)
    {
        if (chara->model_0.anim_4.animIdx_0 == animIdx && chara->model_0.anim_4.keyframeIdx0_8 >= keyframeIdx)
        {
            g_SysWork.player_4C.extra_128.field_24 = arg6;
            func_800713B4(chara, arg4);
        }

        func_80071284(2);
    }

    if (g_SysWork.player_4C.extra_128.field_24 == 0)
    {
        g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = 0;
        D_800C4608                                                 = 0;
    }
    else
    {
        temp                                                       = arg5;
        g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = temp;
        D_800C4608                                                 = temp;
    }
}

void func_80077D00(s_SubCharacter* chara, s_MainCharacterExtra* extra) // 0x80077D00
{
    #define TRAVEL_DIST_MAX FP_METER(1000000.0f)
    #define TRAVEL_DIST_MIN 1

    // Used for `player.field_126`.
    #define GET_MAX(x)         \
        (((x) == 2) ? 0x5000 : (((x) == 0) ? 0x3800 : 0x4000))

    // Used for `player.field_126`.
    #define GET_VAL(val, delta)     \
        (((val) < 0x3800) ?         \
        (((delta) * 0xC00) / 136) : \
        (((delta) + (((delta) < 0) ? 3 : 0)) >> 2))

    s32 var_a2;
    s32 travelDistStep;
    s32 temp_s1;
    s32 temp_s3;
    s32 var_a3;
    s32 var_s2;
    s32 temp;

    if (g_SysWork.player_4C.extra_128.field_24 < 20)
    {
        var_s2 = 0;
    }
    else
    {
        var_s2 = 20;
    }

    // Compute move distance step.
    temp_s3        = func_8007D6F0(chara, &D_800C45C8);
    temp_s1        = func_8003BF60(chara->position_18.vx, chara->position_18.vz);
    var_a2         = SQUARE(chara->position_18.vx - D_800C45F8.vx);
    temp           = SQUARE(chara->position_18.vz - D_800C45F8.vz);
    travelDistStep = SquareRoot0(var_a2 + temp);

    switch (g_SysWork.player_4C.extra_128.field_24)
    {
        case 0:
        case 20:
        case 34:
            break;

        case 1:
        case 4:
        case 5:
        case 6:
        case 21:
        case 24:
        case 25:
        case 26:
            g_SavegamePtr->walkDistance_258 += travelDistStep;
            g_SavegamePtr->walkDistance_258  = CLAMP(g_SavegamePtr->walkDistance_258, TRAVEL_DIST_MIN, TRAVEL_DIST_MAX);
            break;

        default:
            g_SavegamePtr->runDistance_254 += travelDistStep;
            g_SavegamePtr->runDistance_254  = CLAMP(g_SavegamePtr->runDistance_254, TRAVEL_DIST_MIN, TRAVEL_DIST_MAX);
            break;
    }

    switch (g_SysWork.player_4C.extra_128.field_24)
    {
        case 0:
        case 20:
            if (chara->model_0.anim_4.animIdx_0 == 5)
            {
                chara->model_0.stateStep_3 = 0;
            }

            if (var_s2 != 0)
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= (g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136;
                    if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
                    }
                }
            }
            else if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= ((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136) * 2;
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
                }
            }

            if (g_SysWork.player_4C.extra_128.field_24 == 0)
            {
                if (g_SysWork.player_4C.extra_128.field_20 == 24)
                {
                    if (!g_SysWork.playerCombatInfo_38.isAiming_13 && chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.animIdx_0 = D_800C4570.field_6;
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (chara->properties_E4.player.properties_E4[6] < FP_FLOAT_TO(10.0f, Q12_SHIFT) &&
                         chara->health_B0 >= FP_FLOAT_TO(30.0f, Q12_SHIFT))
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.animIdx_0 = 52;
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (chara->model_0.stateStep_3 == 0)
                {
                    chara->model_0.anim_4.animIdx_0 = 54;
                    chara->model_0.stateStep_3++;
                }
            }
            else
            {
                if (g_SysWork.player_4C.extra_128.field_20 == 24)
                {
                    if (!g_SysWork.playerCombatInfo_38.isAiming_13 && chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.animIdx_0 = D_800C4570.field_6;
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
                {
                    if ((g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw ||
                         g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill) &&
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_114 != 0)
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.animIdx_0 = 66;
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.animIdx_0 = 56;
                            chara->model_0.stateStep_3++;
                        }
                    }
                }
                else if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk6)
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.animIdx_0 = 68;
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (g_SysWork.player_4C.extra_128.field_20 == 22)
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.animIdx_0 = 64;
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_HuntingRifle)
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.animIdx_0 = 58;
                        chara->model_0.stateStep_3++;
                    }
                }
                else
                {
                    if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.animIdx_0 = 56;
                        chara->model_0.stateStep_3++;
                    }
                }

                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk6;
            }

            if (g_SysWork.player_4C.extra_128.field_1C == 1)
            {
                if (chara->model_0.anim_4.animIdx_0 & (1 << 0) && extra->model_0.anim_4.animIdx_0 & (1 << 0))
                {
                    if (chara->model_0.anim_4.animIdx_0 >= 58 || chara->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6 || 
                        chara->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[5].field_6)
                    {
                        if (D_800C45E8 != 0)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 21;
                        }
                        else if (D_800C45F0 != 0)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 24;
                        }
                    }
                }

                func_800713B4(chara, var_s2);
            }
            else
            {
                if (chara->model_0.anim_4.animIdx_0 & (1 << 0) && extra->model_0.anim_4.animIdx_0 & (1 << 0))
                {
                    if ((var_s2 == 0 && g_SysWork.player_4C.chara_0.properties_E4.player.field_126 == 0) ||
                        chara->model_0.anim_4.animIdx_0 >= 58 || chara->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6)
                    {
                        if (D_800C45E8 != 0)
                        {
                            if ((D_800C4604 != 0 && temp_s3 == 0) &&
                                (var_s2 == 0 ||
                                 ((g_GameWork.config_0.optExtraWeaponCtrl_23 != 0 && D_800C457E == 0) ||
                                  (g_GameWork.config_0.optExtraWeaponCtrl_23 == 0 && D_800C457E != 0)) && 
                                 (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == 1))
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 2;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.field_24 = var_s2 + 1;
                            }
                        }
                        else if (D_800C45F0 != 0)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = var_s2 + 4;
                        }
                        else if (D_800C45AE != 0)
                        {
                            chara->headingAngle_3C = chara->headingAngle_3C + FP_ANGLE(90.0f);
                            temp_s3                = func_8007D6F0(chara, &D_800C45C8);

                            if (D_800C4604 != 0 && var_s2 == 0 && temp_s3 == 0)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 7;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.field_24 = var_s2 + 5;
                            }
                        }
                        else if (D_800C45AC != 0)
                        {
                            chara->headingAngle_3C -= FP_ANGLE(90.0f);
                            temp_s3                 = func_8007D6F0(chara, &D_800C45C8);

                            if (D_800C4604 != 0 && var_s2 == 0 && temp_s3 == 0)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 8;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.field_24 = var_s2 + 6;
                            }
                        }

                        if (var_s2 == 0 && g_SysWork.playerCombatInfo_38.isAiming_13 == false)
                        {
                            if ((g_GameWork.config_0.optExtraWalkRunCtrl_2B != 0 && D_800C4604 == 0) ||
                                (g_GameWork.config_0.optExtraWalkRunCtrl_2B == 0 && D_800C4604 != 0))
                            {
                                if (D_800C45F0 != 0)
                                {
                                    g_SysWork.player_4C.extra_128.field_24 = 11;
                                    g_SysWork.player_4C.extra_128.field_20 = 13;
                                    extra->model_0.stateStep_3             = 0;
                                    extra->model_0.state_2                 = 0;
                                }
                            }
                        }

                        if (g_SysWork.player_4C.extra_128.field_24 == var_s2 && !g_Player_IsInWalkToRunTransition)
                        {
                            func_800711C4(chara, var_s2);
                        }
                    }
                }

                func_800713B4(chara, var_s2);

                if (D_800C4604 != 0)
                {
                    func_80071284(10);
                }
                else
                {
                    func_80071284(7);
                }

                if (var_s2 != 0 && g_SysWork.player_4C.extra_128.field_20 == 19)
                {
                    if (D_800C454C != FP_TIME(0.0f))
                    {
                        switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
                        {
                            case EquippedWeaponId_KitchenKnife:
                                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = (u32)(D_800C454C * 0x465) >> 9;
                                break;

                            case EquippedWeaponId_Chainsaw:
                            case EquippedWeaponId_Katana:
                            case EquippedWeaponId_Axe:
                                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = (u32)(D_800C454C * 0x15F9) >> 11;
                                break;

                            case EquippedWeaponId_SteelPipe:
                            case EquippedWeaponId_Hammer:
                                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = ((u32)(D_800C454C * 0xD2F) >> 10);
                                break;

                            case EquippedWeaponId_RockDrill:
                            case EquippedWeaponId_Handgun:
                            case EquippedWeaponId_HuntingRifle:
                            case EquippedWeaponId_Shotgun:
                            case EquippedWeaponId_HyperBlaster:
                                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = (-(D_800C454C * 0x87F0) >> 14);
                                break;
                        }

                        if (g_DeltaTime0 != FP_TIME(0.0f))
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 * 0x88) / g_DeltaTime0);
                        }

                        if (D_800C454C != FP_TIME(0.0f))
                        {
                            chara->properties_E4.player.properties_E4[1] = 0;
                        }
                    }
                }
                else if (D_800C454C != FP_TIME(0.0f))
                {
                    chara->properties_E4.player.properties_E4[1] = 0;
                }

                if (D_800C4584 != 0 && chara->model_0.stateStep_3 == 1 &&
                         (chara->model_0.anim_4.animIdx_0 == 53 || chara->model_0.anim_4.animIdx_0 == 55))
                {
                    chara->model_0.stateStep_3      = 2;
                    chara->model_0.anim_4.animIdx_0 = 24;
                }
                else if (D_800C4586 != 0 && chara->model_0.stateStep_3 == 1 && 
                         (chara->model_0.anim_4.animIdx_0 == 53 || chara->model_0.anim_4.animIdx_0 == 55))
                {
                    chara->model_0.stateStep_3      = 2;
                    chara->model_0.anim_4.animIdx_0 = 26;
                }

                if (D_800C4584 == 0 && D_800C4586 == 0 && chara->model_0.stateStep_3 == 2 &&
                    (chara->model_0.anim_4.animIdx_0 == 27 || chara->model_0.anim_4.animIdx_0 == 25))
                {
                    chara->model_0.anim_4.animIdx_0 = 52;
                    chara->model_0.stateStep_3      = 0;
                }
            }

            if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 == 0 ||
                D_800C4584 != 0 || D_800C4586 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = 0;
                D_800C4608                                                 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
            }
            break;

        case 1:
        case 21:
            if (D_800C45E8 == 0)
            {
                g_SysWork.field_235A |= 1 << 0;
            }

            if (g_SysWork.field_235A & (1 << 0) && g_SysWork.player_4C.extra_128.field_24 < 20 && 
                g_SysWork.player_4C.extra_128.field_20 != 24)
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= (((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136) * 2);

                    if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
                    }
                }
            }
            else
            {
                if (g_Controller0->sticks_20.sticks_0.leftY < -0x3F)
                {
                    D_800AF216 = ABS(g_Controller0->sticks_20.sticks_0.leftY);
                    func_80070B84(chara, FP_FLOAT_TO(0.75f, Q12_SHIFT), FP_FLOAT_TO(1.4f, Q12_SHIFT), 2);
                }
                else
                {
                    if (D_800AF216 != 0)
                    {
                        func_80070B84(chara, FP_FLOAT_TO(0.75f, Q12_SHIFT), FP_FLOAT_TO(1.4f, Q12_SHIFT), 2);
                    }
                    else if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 > FP_FLOAT_TO(1.4f, Q12_SHIFT))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= (((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136) * 2);
                        if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 < FP_FLOAT_TO(1.4f, Q12_SHIFT))
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = FP_FLOAT_TO(1.4f, Q12_SHIFT);
                        }
                    }
                    else if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 < FP_FLOAT_TO(1.4f, Q12_SHIFT))
                    {
                        if (chara->model_0.anim_4.keyframeIdx0_8 >= 2)
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.field_126 += ((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136);
                        }
                        
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.field_126, 0, FP_FLOAT_TO(1.4f, Q12_SHIFT));
                    }

                    if (g_Controller0->btnsHeld_C & ControllerFlag_LStickUp)
                    {
                        D_800AF216 = 0;
                    }
                }
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 4;
                chara->model_0.stateStep_3++;
            }

            if (g_SysWork.player_4C.extra_128.field_1C == 1)
            {
                if (g_SysWork.field_235A & (1 << 0))
                {
                    if ((g_SysWork.player_4C.extra_128.field_24 < 20 && g_SysWork.player_4C.extra_128.field_20 != 24) ||
                         (chara->model_0.anim_4.keyframeIdx0_8 >= 10 &&
                          chara->model_0.anim_4.keyframeIdx0_8 <= 11) || 
                         chara->model_0.anim_4.keyframeIdx0_8 == 22 || chara->model_0.anim_4.keyframeIdx0_8 == 21)
                    {
                        g_SysWork.player_4C.extra_128.field_24 = 20;
                    }
                }

                func_800713B4(chara, var_s2 | (1 << 0));

                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_HyperBlaster)
                {
                    func_80071284(5);
                }
            }
            else
            {
                if (!(g_SysWork.field_235A & (1 << 0)))
                {
                    if (D_800C4604 != 0)
                    {
                        if (var_s2 == 0 && temp_s3 == 0 &&
                            (g_SysWork.player_4C.extra_128.field_20 == 1 || g_SysWork.player_4C.extra_128.field_20 == 24))
                        {
                            if (chara->model_0.anim_4.keyframeIdx0_8 >= 10 &&
                                chara->model_0.anim_4.keyframeIdx0_8 <= 11)
                            {
                                g_SysWork.player_4C.extra_128.field_24                      = 2;
                                g_MaybePlayerAnims[0].keyframeIdx1_E                        = 36;
                                g_MaybePlayerAnims[0].animIdx_6                             = 7;
                                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk5;
                            }
                            else if (chara->model_0.anim_4.keyframeIdx0_8 >= 21 &&
                                     chara->model_0.anim_4.keyframeIdx0_8 <= 22)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 2;
                                g_MaybePlayerAnims[0].keyframeIdx1_E   = 26;
                                g_MaybePlayerAnims[0].animIdx_6        = 7;
                            }
                        }
                    }
                }
                else if ((g_SysWork.player_4C.extra_128.field_24 < 20 && g_SysWork.player_4C.extra_128.field_20 != 24) ||
                         (chara->model_0.anim_4.keyframeIdx0_8 >= 10 &&
                          chara->model_0.anim_4.keyframeIdx0_8 <= 11) || 
                         chara->model_0.anim_4.keyframeIdx0_8 == 22 || chara->model_0.anim_4.keyframeIdx0_8 == 21)
                {
                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < 0x20 && var_s2 != 0)
                    {
                        if (((extra->model_0.anim_4.animIdx_0 == 59 || extra->model_0.anim_4.animIdx_0 == 61) && 
                            (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_Chainsaw &&
                             g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill)) || 
                            extra->model_0.anim_4.animIdx_0 == 63)
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk10;
                            chara->model_0.stateStep_3                                  = 0;
                            chara->model_0.state_2                                      = 0;
                            g_SysWork.player_4C.extra_128.field_24                      = 34;
                        }
                        else
                        {
                            g_SysWork.player_4C.extra_128.field_24                      = var_s2;
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                        }
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.field_24                      = var_s2;
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                    }
                }

                if (g_SysWork.player_4C.extra_128.field_24 == (var_s2 + 1) && !g_Player_IsInWalkToRunTransition)
                {
                    func_800711C4(chara, var_s2);
                }

                func_800713B4(chara, var_s2 | (1 << 0));
                func_80071284(5);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = 0;
            D_800C4608                                                 = FP_FLOAT_TO(0.0f, Q12_SHIFT);

            if (g_SysWork.player_4C.extra_128.field_24 == 2)
            {
                chara->model_0.anim_4.animIdx_0 = 0;
                chara->model_0.stateStep_3++;
                g_Player_IsInWalkToRunTransition = true;
            }
            break;

        case 2:
            chara->properties_E4.player.properties_E4[6] += g_DeltaTime0;

            if (g_Controller0->sticks_20.sticks_0.leftY < -0x3F)
            {
                D_800AF216 = ABS(g_Controller0->sticks_20.sticks_0.leftY);

                var_a2 = GET_MAX(temp_s1);

                if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 < FP_FLOAT_TO(3.5f, Q12_SHIFT)) 
                {
                    var_a3 = (g_DeltaTime0 * FP_FLOAT_TO(0.75f, Q12_SHIFT)) / 136;
                } 
                else 
                {
                    temp   = g_DeltaTime0;
                    temp  += (temp < 0) ? 3 : 0;
                    var_a3 = temp >> 2;
                }

                func_80070CF0(chara, FP_FLOAT_TO(2.0f, Q12_SHIFT), var_a2, var_a3, (g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136);
            }
            else
            {
                if (D_800AF216 != 0)
                {
                    var_a2 = GET_MAX(temp_s1);

                    if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 < FP_FLOAT_TO(3.5f, Q12_SHIFT)) 
                    {
                        var_a3 = (g_DeltaTime0 * FP_FLOAT_TO(0.75f, Q12_SHIFT)) / 136;
                    } 
                    else 
                    {
                        temp   = g_DeltaTime0;
                        temp  += (temp < 0) ? 3 : 0;
                        var_a3 = temp >> 2;
                    }

                    func_80070CF0(chara, FP_FLOAT_TO(2.0f, Q12_SHIFT), var_a2, var_a3, (g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136);
                }
                else if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 > GET_MAX(temp_s1))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= (g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136;

                    if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 < GET_MAX(temp_s1))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = GET_MAX(temp_s1);
                    }
                }
                else
                {
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 < GET_MAX(temp_s1))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 += GET_VAL(g_SysWork.player_4C.chara_0.properties_E4.player.field_126, g_DeltaTime0);
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126  = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.field_126, 0, GET_MAX(temp_s1));
                    }
                }

                if (g_Controller0->btnsHeld_C & ControllerFlag_LStickUp)
                {
                    D_800AF216 = 0;
                }
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 6;
                chara->model_0.stateStep_3++;
            }

            if ((chara->model_0.anim_4.keyframeIdx0_8 == 43 || chara->model_0.anim_4.keyframeIdx0_8 == 33) && 
                chara->position_18.vy == chara->properties_E4.player.properties_E4[2])
            {
                chara->field_34 = FP_FLOAT_TO(-1.25f, Q12_SHIFT);
            }

            if (g_SysWork.player_4C.extra_128.field_20 != 22 && chara->model_0.anim_4.animIdx_0 == 7)
            {
                switch (temp_s3)
                {
                    case 1:
                        if (chara->properties_E4.player.properties_E4[9] >= 0xA000u)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 12;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx0_8 >= 30 &&
                                 chara->model_0.anim_4.keyframeIdx0_8 <= 31)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = temp_s3;
                            g_MaybePlayerAnims[0].keyframeIdx1_E   = 8;
                            g_MaybePlayerAnims[0].animIdx_6        = 5;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx0_8 >= 41 &&
                                 chara->model_0.anim_4.keyframeIdx0_8 <= 42)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = temp_s3;
                            g_MaybePlayerAnims[0].keyframeIdx1_E   = 20;
                            g_MaybePlayerAnims[0].animIdx_6        = 5;
                        }
                        break;

                    case 2:
                        if (chara->properties_E4.player.properties_E4[9] >= 0xA000u)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 3;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx0_8 >= 30 &&
                                 chara->model_0.anim_4.keyframeIdx0_8 <= 31)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 1;
                            g_MaybePlayerAnims[0].keyframeIdx1_E   = 8;
                            g_MaybePlayerAnims[0].animIdx_6        = 5;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx0_8 >= 41 &&
                                 chara->model_0.anim_4.keyframeIdx0_8 <= 42)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 1;
                            g_MaybePlayerAnims[0].keyframeIdx1_E   = 20;
                            g_MaybePlayerAnims[0].animIdx_6        = 5;
                        }
                        break;

                    default:
                        if (D_800C4604 == 0 || D_800C45E8 == 0)
                        {
                            if (D_800C45E8 != 0)
                            {
                                if (chara->model_0.anim_4.keyframeIdx0_8 >= 30 &&
                                    chara->model_0.anim_4.keyframeIdx0_8 <= 31)
                                {
                                    g_SysWork.player_4C.extra_128.field_24 = 1;
                                    g_MaybePlayerAnims[0].keyframeIdx1_E   = 8;
                                    g_MaybePlayerAnims[0].animIdx_6        = 5;
                                }
                                else if (chara->model_0.anim_4.keyframeIdx0_8 >= 41 &&
                                         chara->model_0.anim_4.keyframeIdx0_8 <= 42)
                                {
                                    g_SysWork.player_4C.extra_128.field_24 = 1;
                                    g_MaybePlayerAnims[0].keyframeIdx1_E   = 20;
                                    g_MaybePlayerAnims[0].animIdx_6        = 5;
                                }
                            }
                            else if (chara->properties_E4.player.properties_E4[5] >= 5 &&
                                     g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >= FP_FLOAT_TO(3.125f, Q12_SHIFT))
                            {
                                if (chara->model_0.anim_4.keyframeIdx0_8 >= 33 &&
                                    chara->model_0.anim_4.keyframeIdx0_8 <= 34)
                                {
                                    g_SysWork.player_4C.extra_128.field_24                      = 3;
                                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk3;
                                }
                                else if (chara->model_0.anim_4.keyframeIdx0_8 >= 43 &&
                                         chara->model_0.anim_4.keyframeIdx0_8 <= 44)
                                {
                                    g_SysWork.player_4C.extra_128.field_24                      = 3;
                                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk3;
                                }
                            }
                            else
                            {
                                if (chara->model_0.anim_4.keyframeIdx0_8 >= 30 &&
                                    chara->model_0.anim_4.keyframeIdx0_8 <= 31)
                                {
                                    g_SysWork.player_4C.extra_128.field_24 = 1;
                                    g_MaybePlayerAnims[0].keyframeIdx1_E   = 8;
                                    g_MaybePlayerAnims[0].animIdx_6        = 5;
                                }
                                else if (chara->model_0.anim_4.keyframeIdx0_8 >= 41 &&
                                         chara->model_0.anim_4.keyframeIdx0_8 <= 42)
                                {
                                    g_SysWork.player_4C.extra_128.field_24 = 1;
                                    g_MaybePlayerAnims[0].keyframeIdx1_E   = 20;
                                    g_MaybePlayerAnims[0].animIdx_6        = 5;
                                }
                            }
                        }
                        break;
                }
            }

            if (g_SysWork.player_4C.extra_128.field_24 != 2)
            {
                func_800713B4(chara, 2);
            }

            func_80071284(4);

            D_800C4608                                                 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
            g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = 0;

            if (g_SysWork.player_4C.extra_128.field_24 == 1)
            {
                chara->model_0.anim_4.animIdx_0 = 0;
                chara->model_0.stateStep_3++;
                g_Player_IsInWalkToRunTransition = true;
            }
            break;

        case 3:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= ((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136) >> 1;
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
                }
            }

            if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk3)
            {
                if (chara->model_0.stateStep_3 == 0)
                {
                    chara->model_0.anim_4.animIdx_0 = 18;
                    chara->model_0.stateStep_3++;
                }
            }
            else if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 20;
                chara->model_0.stateStep_3++;
            }

            if (g_SysWork.player_4C.extra_128.field_20 != 0x16)
            {
                if (chara->model_0.anim_4.animIdx_0 == 21 && chara->model_0.anim_4.keyframeIdx0_8 >= 168 ||
                    chara->model_0.anim_4.animIdx_0 == 19 && chara->model_0.anim_4.keyframeIdx0_8 >= 158)
                {
                    g_SysWork.player_4C.extra_128.field_24 = 0;
                    func_800713B4(chara, 3);
                }

                func_80071284(4);
            }
            break;

        case 4:
        case 24:
            if (D_800C45F0 == 0)
            {
                g_SysWork.field_235A |= 1 << 1;
            }

            if (g_SysWork.field_235A & (1 << 1) &&
                g_SysWork.player_4C.extra_128.field_24 < 20 && g_SysWork.player_4C.extra_128.field_20 != 24)
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= (((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136) * 2);
                    if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
                    }
                }
            }
            else if (g_Controller0->sticks_20.sticks_0.leftY >= (1 << 6))
            {
                D_800AF216 = ABS(g_Controller0->sticks_20.sticks_0.leftY);
                func_80070B84(chara, FP_FLOAT_TO(0.75f, Q12_SHIFT), FP_FLOAT_TO(1.15f, Q12_SHIFT), 2);
            }
            else
            {
                if (D_800AF216 != 0)
                {
                    func_80070B84(chara, FP_FLOAT_TO(0.75f, Q12_SHIFT), FP_FLOAT_TO(1.15f, Q12_SHIFT), 2);
                }
                else if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 > FP_FLOAT_TO(1.15f, Q12_SHIFT))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= (((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136) * 2);
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 < FP_FLOAT_TO(1.15f, Q12_SHIFT))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = FP_FLOAT_TO(1.15f, Q12_SHIFT);
                    }
                }
                else if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 < FP_FLOAT_TO(1.15f, Q12_SHIFT))
                {
                    if (chara->model_0.anim_4.keyframeIdx0_8 >= 2)
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 += ((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136);
                    }
                        
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.field_126,
                                                                                       FP_FLOAT_TO(0.0f, Q12_SHIFT),
                                                                                       FP_FLOAT_TO(1.15f, Q12_SHIFT));
                }

                if (g_Controller0->btnsHeld_C & ControllerFlag_LStickDown)
                {
                    D_800AF216 = 0;
                }
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 8;
                chara->model_0.stateStep_3++;
            }

            if (g_SysWork.player_4C.extra_128.field_1C == 1)
            {
                if (g_SysWork.field_235A & (1 << 1))
                {
                    if ((g_SysWork.player_4C.extra_128.field_24 < 20 && g_SysWork.player_4C.extra_128.field_20 != 24) ||
                         (chara->model_0.anim_4.keyframeIdx0_8 >= 56 &&
                          chara->model_0.anim_4.keyframeIdx0_8 <= 57) ||
                         chara->model_0.anim_4.keyframeIdx0_8 == 67 ||
                         chara->model_0.anim_4.keyframeIdx0_8 == 66)
                    {
                        g_SysWork.player_4C.extra_128.field_24 = 20;
                    }
                }

                func_800713B4(chara, var_s2 + 4);

                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_HyperBlaster)
                {
                    func_80071284(5);
                }
            }
            else
            {
                if (!(g_SysWork.field_235A & 2))
                {
                    if (((chara->model_0.anim_4.keyframeIdx0_8 >= 66 &&
                          chara->model_0.anim_4.keyframeIdx0_8 <= 67) ||
                         chara->model_0.anim_4.keyframeIdx0_8 == 46 ||
                         chara->model_0.anim_4.keyframeIdx0_8 == 47) && 
                        var_s2 == 0 && g_SysWork.player_4C.extra_128.field_20 != 24)
                    {
                        if ((g_GameWork.config_0.optExtraWalkRunCtrl_2B != 0 && D_800C4604 == 0) ||
                            (g_GameWork.config_0.optExtraWalkRunCtrl_2B == 0 && D_800C4604 != 0))
                        {
                            if (D_800C45F0 != 0)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 11;
                                g_SysWork.player_4C.extra_128.field_20 = 13;
                                extra->model_0.stateStep_3             = 0;
                                extra->model_0.state_2                 = 0;
                            }
                        }
                    }
                }
                else if ((g_SysWork.player_4C.extra_128.field_24 < 20 && g_SysWork.player_4C.extra_128.field_20 != 24) ||
                         (chara->model_0.anim_4.keyframeIdx0_8 >= 56 &&
                          chara->model_0.anim_4.keyframeIdx0_8 <= 57) ||
                         chara->model_0.anim_4.keyframeIdx0_8 == 67 ||
                         chara->model_0.anim_4.keyframeIdx0_8 == 66)
                {
                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun && var_s2 != 0)
                    {
                        if (((extra->model_0.anim_4.animIdx_0 == 59 ||
                              extra->model_0.anim_4.animIdx_0 == 61) &&
                             (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_Chainsaw &&
                              g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill)) || 
                            extra->model_0.anim_4.animIdx_0 == 63)
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk10;
                            chara->model_0.stateStep_3                                  = 0;
                            chara->model_0.state_2                                      = 0;
                            g_SysWork.player_4C.extra_128.field_24                      = 34;
                        }
                        else
                        {
                            g_SysWork.player_4C.extra_128.field_24                      = var_s2;
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                        }
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.field_24                      = var_s2;
                        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk10;
                    }
                }

                if (g_SysWork.player_4C.extra_128.field_24 == (var_s2 + 4) && !g_Player_IsInWalkToRunTransition)
                {
                    func_800711C4(chara, var_s2);
                }

                func_800713B4(chara, var_s2 + 4);
                func_80071284(4);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = FP_FLOAT_TO(0.5f, Q12_SHIFT);
            D_800C4608                                                 = FP_FLOAT_TO(0.5f, Q12_SHIFT);
            break;

        case 5:
        case 25:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 > FP_FLOAT_TO(1.25f, Q12_SHIFT))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= ((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136);
                if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 < FP_FLOAT_TO(1.25f, Q12_SHIFT))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = FP_FLOAT_TO(1.25f, Q12_SHIFT);
                }
            }
            else
            {
                if (chara->model_0.anim_4.keyframeIdx0_8 >= 100 &&
                    chara->model_0.anim_4.keyframeIdx0_8 <= 111)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 += ((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136);
                }
                else if (chara->model_0.anim_4.keyframeIdx0_8 >= 112)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= ((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136);
                }

                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.field_126,
                                                                                   FP_FLOAT_TO(0.0f, Q12_SHIFT),   
                                                                                   FP_FLOAT_TO(1.25f, Q12_SHIFT));
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 12;
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.animIdx_0 == 13 &&
                chara->model_0.anim_4.keyframeIdx0_8 >= 117)
            {
                if (D_800C45AE == 0)
                {
                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun && var_s2 != 0)
                    {
                        if (((extra->model_0.anim_4.animIdx_0 == 59 ||
                              extra->model_0.anim_4.animIdx_0 == 61) &&
                             (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_Chainsaw &&
                              g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill)) || 
                            extra->model_0.anim_4.animIdx_0 == 63)
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk10;
                            chara->model_0.stateStep_3                                  = 0;
                            chara->model_0.state_2                                      = 0;
                            g_SysWork.player_4C.extra_128.field_24                      = 34;
                        }
                        else
                        {
                            g_SysWork.player_4C.extra_128.field_24 = var_s2;
                        }
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.field_24 = var_s2;
                    }
                }
                else if (D_800C4604 != 0 && var_s2 == 0 && temp_s3 == 0)
                {
                    if (g_SysWork.player_4C.extra_128.field_20 != 24)
                    {
                        g_SysWork.player_4C.extra_128.field_24 = 7;
                    }
                }
            }

            func_800711C4(chara, var_s2);
            func_800713B4(chara, var_s2 + 5);
            func_80071284(3);

            g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = FP_FLOAT_TO(0.25f, Q12_SHIFT);
            D_800C4608                                                 = FP_FLOAT_TO(0.25f, Q12_SHIFT);
            break;

        case 6:
        case 26:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 > FP_FLOAT_TO(1.25f, Q12_SHIFT))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= ((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136);
                if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 < FP_FLOAT_TO(1.25f, Q12_SHIFT))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = FP_FLOAT_TO(1.25f, Q12_SHIFT);
                }
            }
            else
            {
                if (chara->model_0.anim_4.keyframeIdx0_8 >= 75 &&
                    chara->model_0.anim_4.keyframeIdx0_8 <= 86)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 += ((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136);
                }
                else if (chara->model_0.anim_4.keyframeIdx0_8 >= 87)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= ((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136);
                }

                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.field_126,
                                                                                   FP_FLOAT_TO(0.0f, Q12_SHIFT),
                                                                                   FP_FLOAT_TO(1.25f, Q12_SHIFT));
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 10;
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.animIdx_0 == 11 &&
                chara->model_0.anim_4.keyframeIdx0_8 >= 92)
            {
                if (D_800C45AC == 0)
                {
                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun && var_s2 != 0)
                    {
                        if (((extra->model_0.anim_4.animIdx_0 == 59 ||
                              extra->model_0.anim_4.animIdx_0 == 61) &&
                             (g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_Chainsaw &&
                              g_SysWork.playerCombatInfo_38.equippedWeapon_F != EquippedWeaponId_RockDrill)) || 
                             extra->model_0.anim_4.animIdx_0 == 63)
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk10;
                            chara->model_0.stateStep_3                                  = 0;
                            chara->model_0.state_2                                      = 0;
                            g_SysWork.player_4C.extra_128.field_24                      = 34;
                        }
                        else
                        {
                            g_SysWork.player_4C.extra_128.field_24 = var_s2;
                        }
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.field_24 = var_s2;
                    }
                }
                else if (D_800C4604 != 0 && var_s2 == 0 && temp_s3 == 0)
                {
                    if (g_SysWork.player_4C.extra_128.field_20 != 24)
                    {
                        g_SysWork.player_4C.extra_128.field_24 = 8;
                    }
                }
            }

            func_80071224(chara, var_s2);
            func_800713B4(chara, var_s2 + 6);
            func_80071284(3);

            g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = FP_FLOAT_TO(-0.25f, Q12_SHIFT);
            D_800C4608                                                 = FP_FLOAT_TO(-0.25f, Q12_SHIFT);
            break;

        case 7:
            chara->properties_E4.player.properties_E4[6] += g_DeltaTime0;
            if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 > 0x32C8)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= ((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136);
                if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 < 0x32C8)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0x32C8;
                }
            }
            else if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 < 0x32C8)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 += ((g_DeltaTime0 * FP_FLOAT_TO(0.75f, Q12_SHIFT)) / 136);
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126  = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.field_126, 0, 0x32C8);
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 16;
                chara->model_0.stateStep_3++;
            }

            if ((chara->model_0.anim_4.keyframeIdx0_8 == 139 ||
                 chara->model_0.anim_4.keyframeIdx0_8 == 145) &&
                chara->position_18.vy == chara->properties_E4.player.properties_E4[2])
            {
                chara->field_34 = FP_FLOAT_TO(-1.0f, Q12_SHIFT);
            }

            if (g_SysWork.player_4C.extra_128.field_20 != 22)
            {
                switch (temp_s3)
                {
                    case 1:
                        if (chara->properties_E4.player.properties_E4[9] >= 0xA000u)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 16;
                        }
                        else
                        {
                            if (chara->model_0.anim_4.animIdx_0 == 17 && chara->model_0.anim_4.keyframeIdx0_8 >= 147)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 0;
                            }
                        }
                        break;

                    case 2:
                        if (chara->properties_E4.player.properties_E4[9] >= 0xA000u)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 14;
                        }
                        else
                        {
                            if (chara->model_0.anim_4.animIdx_0 == 17 && chara->model_0.anim_4.keyframeIdx0_8 >= 147)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 0;
                            }
                        }
                        break;

                    default:
                        if (chara->properties_E4.player.properties_E4[5] >= 5 &&
                            g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >= FP_FLOAT_TO(3.125f, Q12_SHIFT))
                        {
                            if (chara->model_0.anim_4.keyframeIdx0_8 >= 144 && (D_800C4604 == 0 || D_800C45AE == 0))
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 14;
                            }
                        }
                        else if (chara->model_0.anim_4.animIdx_0 == 17 && chara->model_0.anim_4.keyframeIdx0_8 >= 147 &&
                                 (D_800C4604 == 0 || D_800C45AE == 0))
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 0;
                        }
                        break;
                }
            }

            func_800713B4(chara, 7);
            func_80071284(4);

            g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = FP_FLOAT_TO(0.25f, Q12_SHIFT);
            D_800C4608                                                 = FP_FLOAT_TO(0.25f, Q12_SHIFT);
            break;

        case 8:
            chara->properties_E4.player.properties_E4[6] += g_DeltaTime0;
            if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >= 0x32C9)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= ((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136);
                if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 < 0x32C8)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0x32C8;
                }
            }
            else if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 < 0x32C8)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 += ((g_DeltaTime0 * FP_FLOAT_TO(0.75f, Q12_SHIFT)) / 136);
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126  = CLAMP(g_SysWork.player_4C.chara_0.properties_E4.player.field_126, 0, 0x32C8);
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 14;
                chara->model_0.stateStep_3++;
            }

            if ((chara->model_0.anim_4.keyframeIdx0_8 == 125 ||
                 chara->model_0.anim_4.keyframeIdx0_8 == 132) &&
                chara->position_18.vy == chara->properties_E4.player.properties_E4[2])
            {
                chara->field_34 = FP_FLOAT_TO(-1.0f, Q12_SHIFT);
            }

            if (g_SysWork.player_4C.extra_128.field_20 != 22)
            {
                switch (temp_s3)
                {
                    case 1:
                        if (chara->properties_E4.player.properties_E4[9] >= 0xA000u)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 15;
                        }
                        else
                        {
                            if (chara->model_0.anim_4.animIdx_0 == 15 &&
                                chara->model_0.anim_4.keyframeIdx0_8 >= 0x84)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 0;
                            }
                        }
                        break;

                    case 2:
                        if (chara->properties_E4.player.properties_E4[9] >= 0xA000u)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 13;
                        }
                        else
                        {
                            if (chara->model_0.anim_4.animIdx_0 == 15 && chara->model_0.anim_4.keyframeIdx0_8 >= 132)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 0;
                            }
                        }
                        break;

                    default:
                        if (chara->properties_E4.player.properties_E4[5] >= 5 &&
                            g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >= FP_FLOAT_TO(3.125f, Q12_SHIFT))
                        {
                            if (chara->model_0.anim_4.keyframeIdx0_8 > 128 && (D_800C4604 == 0 || D_800C45AC == 0))
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 13;
                            }
                        }
                        else if (chara->model_0.anim_4.animIdx_0 == 15 && chara->model_0.anim_4.keyframeIdx0_8 >= 132 &&
                                 (D_800C4604 == 0 || D_800C45AC == 0))
                        {
                            g_SysWork.player_4C.extra_128.field_24 = 0;
                        }
                        break;
                }
            }

            func_800713B4(chara, 8);
            func_80071284(4);

            g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = FP_FLOAT_TO(-0.25f, Q12_SHIFT);
            D_800C4608                                                 = FP_FLOAT_TO(-0.25f, Q12_SHIFT);
            break;

        case 9:
        case 29:
            D_800C4608 = FP_FLOAT_TO(0.0f, Q12_SHIFT);

            if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= ((g_DeltaTime0 << 11) / 136);
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
                }
            }

            if (chara->model_0.state_2 == 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_120 = chara->rotation_24.vy;
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 28;
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.state_2 == 0)
            {
                chara->model_0.state_2++;
            }

            if (chara->model_0.anim_4.animIdx_0 == 29 && chara->model_0.anim_4.keyframeIdx0_8 >= 206)
            {
                D_800C454C = g_DeltaTime0 * 24;
            }
            else
            {
                D_800C454C = FP_TIME(0.0f);
            }

            if (ABS_DIFF(g_SysWork.player_4C.chara_0.properties_E4.player.field_120, chara->rotation_24.vy) > (FP_ANGLE(180.0f) - ((s32)(g_DeltaTime0 * 24) >> 4)))
            {
                if (ABS_DIFF(g_SysWork.player_4C.chara_0.properties_E4.player.field_120, chara->rotation_24.vy) < (((g_DeltaTime0 * 24) >> 4) + FP_ANGLE(180.0f)))
                {
                    chara->rotation_24.vy                                      = g_SysWork.player_4C.chara_0.properties_E4.npc.field_120 + FP_ANGLE(180.0f);
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = FP_FLOAT_TO(1.4f, Q12_SHIFT);
                    D_800C454C                                                 = FP_TIME(0.0f);

                    if (chara->model_0.anim_4.keyframeIdx0_8 >= 213)
                    {
                        if (D_800C45E8 != 0)
                        {
                            if (D_800C4604 != 0 && var_s2 == 0)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 2;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.field_24 = var_s2 + 1;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (D_800C45F0 != 0)
                        {
                            if (D_800C4604 != 0 && var_s2 == 0)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 11;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.field_24 = var_s2 + 4;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (D_800C45AE != 0)
                        {
                            chara->headingAngle_3C += FP_ANGLE(90.0f);

                            if (D_800C4604 != 0 && var_s2 == 0)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 7;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.field_24 = var_s2 + 5;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (D_800C45AC != 0)
                        {
                            chara->headingAngle_3C -= FP_ANGLE(90.0f);

                            if (D_800C4604 != 0 && var_s2 == 0)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 8;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.field_24 = var_s2 + 6;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx0_8 >= 216)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = var_s2;
                            chara->model_0.stateStep_3             = 0;
                            chara->model_0.state_2                 = 0;
                        }
                    }
                }
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = 0;
            D_800C4608                                                 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
            break;

        case 10:
        case 30:
            D_800C4608 = FP_FLOAT_TO(0.0f, Q12_SHIFT);

            if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= (g_DeltaTime0 << 11) / 136;
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
                }
            }

            if (chara->model_0.state_2 == 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_120 = chara->rotation_24.vy;
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 30;
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.state_2 == 0)
            {
                chara->model_0.state_2++;
            }

            if (chara->model_0.anim_4.animIdx_0 == 31 && chara->model_0.anim_4.keyframeIdx0_8 >= 219)
            {
                D_800C454C = -(g_DeltaTime0 * 24);
            }
            else
            {
                D_800C454C = FP_TIME(0.0f);
            }

            if (ABS_DIFF(g_SysWork.player_4C.chara_0.properties_E4.player.field_120, chara->rotation_24.vy) > (FP_ANGLE(180.0f) - ((g_DeltaTime0 * 24) >> 4)))
            {
                if (ABS_DIFF(g_SysWork.player_4C.chara_0.properties_E4.player.field_120, chara->rotation_24.vy) < (((g_DeltaTime0 * 24) >> 4) + FP_ANGLE(180.0f)))
                {
                    chara->rotation_24.vy                                      = g_SysWork.player_4C.chara_0.properties_E4.npc.field_120 + FP_ANGLE(180.0f);
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = FP_FLOAT_TO(1.4f, Q12_SHIFT);
                    D_800C454C                                                 = FP_TIME(0.0f);

                    if (chara->model_0.anim_4.keyframeIdx0_8 >= 226)
                    {
                        if (D_800C45E8 != 0)
                        {
                            if (D_800C4604 != 0 && var_s2 == 0)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 2;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.field_24 = var_s2 + 1;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (D_800C45F0 != 0)
                        {
                            if (D_800C4604 != 0 && var_s2 == 0)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 11;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.field_24 = var_s2 + 4;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (D_800C45AE != 0)
                        {
                            chara->headingAngle_3C += FP_ANGLE(90.0f);

                            if (D_800C4604 != 0 && var_s2 == 0)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 7;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.field_24 = var_s2 + 5;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (D_800C45AC != 0)
                        {
                            chara->headingAngle_3C -= FP_ANGLE(90.0f);

                            if (D_800C4604 != 0 && var_s2 == 0)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 8;
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.field_24 = var_s2 + 6;
                            }

                            chara->model_0.stateStep_3 = 0;
                            chara->model_0.state_2     = 0;
                        }
                        else if (chara->model_0.anim_4.keyframeIdx0_8 >= 229)
                        {
                            g_SysWork.player_4C.extra_128.field_24 = var_s2;
                            chara->model_0.stateStep_3             = 0;
                            chara->model_0.state_2                 = 0;
                        }
                    }
                }
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = 0;
            D_800C4608                                                 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
            break;
            
        case 11:
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 32;
                chara->model_0.stateStep_3++;
            }
            
            if ((chara->model_0.anim_4.animIdx_0 >= 32 &&
                 chara->model_0.anim_4.animIdx_0 <= 33) &&
                chara->model_0.anim_4.keyframeIdx0_8 < 245)
            {
                if (chara->model_0.state_2 == 0)
                {
                    chara->field_34 = FP_FLOAT_TO(-2.0f, Q12_SHIFT);
                }

                chara->model_0.state_2++;
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = FP_FLOAT_TO(2.25f, Q12_SHIFT);
                D_800C4550                                                 = FP_FLOAT_TO(2.25f, Q12_SHIFT);
            }
            else
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= (((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136) * 2);
                    if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
                    }
                }

                D_800C4550 = g_SysWork.player_4C.chara_0.properties_E4.player.field_126;
            }

            if (chara->model_0.anim_4.animIdx_0 == 33 &&
                chara->model_0.anim_4.keyframeIdx0_8 == 246)
            {
                if (chara->position_18.vy < chara->properties_E4.player.properties_E4[2])
                {
                    g_SysWork.player_4C.extra_128.field_1C = 4;

                    chara->model_0.stateStep_3 = 0;
                    chara->model_0.state_2     = 0;
                    extra->model_0.stateStep_3 = 0;
                    extra->model_0.state_2     = 0;

                    g_SysWork.player_4C.extra_128.field_20                     = 0;
                    g_SysWork.player_4C.extra_128.field_24                     = 0;
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = FP_FLOAT_TO(1.25f, Q12_SHIFT);
                }
                else 
                {
                    g_SysWork.player_4C.extra_128.field_24 = var_s2;
                    chara->model_0.stateStep_3 = 0;
                    chara->model_0.state_2 = 0;
                    chara->field_34 = 0;
                }
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = FP_FLOAT_TO(0.5f, Q12_SHIFT);
            D_800C4608                                                 = FP_FLOAT_TO(0.5f, Q12_SHIFT);
            break;

        case 12:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= ((((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136) * 2) / 3);
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
                }
            }

            if (D_800C45DC <= FP_FLOAT_TO(0.5f, Q12_SHIFT) && g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= (((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136) * 4);
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
                }
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 22;
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.animIdx_0 == 23 && chara->model_0.anim_4.keyframeIdx0_8 == 179)
            {
                g_SysWork.player_4C.extra_128.field_24 = 0;
                func_800713B4(chara, 12);
            }
            break;

        case 13:
            func_80077BB8(chara, 36, 37, 335, 13, FP_FLOAT_TO(-0.25f, Q12_SHIFT), var_s2);
            break;

        case 14:
            func_80077BB8(chara, 40, 41, 364, 14, FP_FLOAT_TO(0.25f, Q12_SHIFT), var_s2);
            break;

        case 15:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= ((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136) >> 2;
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
                }
            }

            // SFX?
            if (D_800C45DC < 1393)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 38;
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.animIdx_0 == 39 &&
                chara->model_0.anim_4.keyframeIdx0_8 == 349)
            {
                g_SysWork.player_4C.extra_128.field_24 = 0;
                func_800713B4(chara, 15);
            }

            if (g_SysWork.player_4C.extra_128.field_24 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = FP_FLOAT_TO(-0.25f, Q12_SHIFT);
                D_800C4608                                                 = FP_FLOAT_TO(-0.25f, Q12_SHIFT);
                break;
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = 0;
            D_800C4608                                                 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
            break;

        case 16:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= ((g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136) >> 2;
                if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
                }
            }

            // SFX?
            if (D_800C45DC <= 1392)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
            }

            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 42;
                chara->model_0.stateStep_3++;
            }

            if (chara->model_0.anim_4.animIdx_0 == 43 &&
                chara->model_0.anim_4.keyframeIdx0_8 == 378)
            {
                g_SysWork.player_4C.extra_128.field_24 = 0;
                func_800713B4(chara, 16);
            }

            if (g_SysWork.player_4C.extra_128.field_24 == 0)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = 0;
                D_800C4608                                                 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
                break;
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.field_124 = FP_FLOAT_TO(0.25f, Q12_SHIFT);
            D_800C4608                                                 = FP_FLOAT_TO(0.25f, Q12_SHIFT);
            break;

        case 34:
            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun &&
                (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == 6)
            {
                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == 16)
                {
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 == 0 && 
                        (extra->model_0.anim_4.keyframeIdx0_8 >= D_800C44F0[D_800AF220].field_4 + 7))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = FP_FLOAT_TO(5.0f, Q12_SHIFT);
                        D_800C4608                                                 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
                    }
                }
                else if (chara->model_0.stateStep_3 == 0 && D_800C45BE == 0)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = FP_FLOAT_TO(5.0f, Q12_SHIFT);
                    D_800C4608                                                 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
                }
            }

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F < 32 && (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) == 6)
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= (g_DeltaTime0 * 0x444) / 136;
                    if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
                    }
                }
            }
            else
            {
                if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 != 0)
                {
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 -= (g_DeltaTime0 * FP_FLOAT_TO(0.4f, Q12_SHIFT)) / 136;
                    if ((g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 16) & (1 << 0))
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0;
                    }
                }
            }

            if (g_SysWork.field_2353 == NO_VALUE || g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
            {
                if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
                {
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk11)
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.animIdx_0 = D_800C4570.field_7 - 12;
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.animIdx_0 = D_800C4570.field_7;
                            chara->model_0.stateStep_3++;
                        }
                    }
                }
                else if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk10)
                {
                    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw || g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.animIdx_0 = D_800C4570.field_7;
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else if (chara->model_0.stateStep_3 == 0)
                    {
                        chara->model_0.anim_4.animIdx_0 = 56;
                        chara->model_0.stateStep_3++;
                    }

                    if (chara->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6 || 
                        chara->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[5].field_6)
                    {
                        chara->model_0.anim_4.animIdx_0      = extra->model_0.anim_4.animIdx_0;
                        chara->model_0.anim_4.keyframeIdx0_8 = extra->model_0.anim_4.keyframeIdx0_8;
                        chara->model_0.anim_4.time_4         = extra->model_0.anim_4.time_4;
                        chara->model_0.stateStep_3++;
                    }
                }
                else if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
                {
                    if (D_800AF217 == 1)
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.animIdx_0 = D_800C4570.field_7 + 2;
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else if (D_800AF217 == NO_VALUE)
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.animIdx_0 = D_800C4570.field_7 + 4;
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.animIdx_0 = D_800C4570.field_7;
                            chara->model_0.stateStep_3++;
                        }
                    }
                }
                else
                {
                    if (extra->model_0.anim_4.animIdx_0 == 61)
                    {
                        chara->model_0.anim_4.animIdx_0      = extra->model_0.anim_4.animIdx_0;
                        chara->model_0.anim_4.keyframeIdx0_8 = extra->model_0.anim_4.keyframeIdx0_8;
                        chara->model_0.anim_4.time_4         = extra->model_0.anim_4.time_4;
                        chara->model_0.stateStep_3++;
                    }
                    else if (D_800C45BE != 0 || extra->model_0.anim_4.animIdx_0 == 59)
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.animIdx_0 = D_800C4570.field_7 - 4;
                            chara->model_0.stateStep_3++;
                        }
                    }
                    else if (D_800C45C0 != 0 || extra->model_0.anim_4.animIdx_0 == 63)
                    {
                        if (chara->model_0.stateStep_3 == 0)
                        {
                            chara->model_0.anim_4.animIdx_0 = D_800C4570.field_7;
                            chara->model_0.stateStep_3++;
                        }
                    }
                }
            }
            else if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = D_800C4570.field_8 - 1;
                chara->model_0.stateStep_3++;
            }

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun ||
                ((g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) != 1 &&
                 (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) != 4 &&
                 (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) != 2 &&
                 (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10) != 6))
            {
                if (chara->model_0.anim_4.animIdx_0 & (1 << 0) && extra->model_0.anim_4.animIdx_0 & (1 << 0) &&
                    (chara->model_0.anim_4.animIdx_0 >= 58 || chara->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6))
                {
                    if (D_800C45E8 == 0)
                    {
                        if (D_800C45F0 != 0)
                        {
                            if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 == 0)
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 24;
                            }
                        }
                        else if (g_SysWork.player_4C.extra_128.field_1C != 1)
                        {
                            if (D_800C45AE == 0)
                            {
                                if (D_800C45AC != 0)
                                {
                                    g_SysWork.player_4C.extra_128.field_24 = 26;
                                }
                            }
                            else
                            {
                                g_SysWork.player_4C.extra_128.field_24 = 25;
                            }
                        }
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.field_24 = 21;
                    }
                    
                    if (g_SysWork.player_4C.extra_128.field_24 != 34)
                    {
                        func_800713B4(chara, 0x14);
                        break;
                    }
                }
            }
            break;

        case 35:
            if (chara->model_0.stateStep_3 == 0)
            {
                chara->model_0.anim_4.animIdx_0 = 62;
                chara->model_0.stateStep_3++;
            }

            if ((chara->model_0.anim_4.animIdx_0 & (1 << 0)) && (extra->model_0.anim_4.animIdx_0 & (1 << 0)) &&
                (chara->model_0.anim_4.animIdx_0 >= 58 || chara->model_0.anim_4.keyframeIdx0_8 == D_800C44F0[0].field_6))
            {
                if (D_800C45E8 != 0)
                {
                    g_SysWork.player_4C.extra_128.field_24 = 21;
                }
                else if (D_800C45F0 != 0)
                {
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 == 0)
                    {
                        g_SysWork.player_4C.extra_128.field_24 = 24;
                    }
                }
                else if (g_SysWork.player_4C.extra_128.field_1C != 1)
                {
                    if (D_800C45AE != 0)
                    {
                        g_SysWork.player_4C.extra_128.field_24 = 25;
                    }
                    else if (D_800C45AC != 0)
                    {
                        g_SysWork.player_4C.extra_128.field_24 = 26;
                    }
                }

                if (g_SysWork.player_4C.extra_128.field_24 != 35)
                {
                    func_800713B4(chara, 20);
                }
            }
            break;
    }

    func_8007B924(chara, extra);
}

void func_8007B924(s_SubCharacter* chara, s_MainCharacterExtra* extra) // 0x8007B924
{
    s32 sp18;
    s8  sp1C;
    s8  sp1D;

    func_8007FDE0(D_800C4590.field_14, &sp18, &sp1C, &sp1D);

    if (g_SysWork.player_4C.extra_128.field_24 != 11 && g_SysWork.player_4C.extra_128.field_24 != 35)
    {
        D_800C4550 = g_SysWork.player_4C.chara_0.properties_E4.player.field_126;
    }

    switch (g_SysWork.player_4C.extra_128.field_24)
    {
        case 2:
        case 7:
        case 8:
            if ((chara->model_0.anim_4.animIdx_0 & (1 << 0)) && chara->model_0.anim_4.animIdx_0 >= 7)
            {
                chara->properties_E4.player.properties_E4[6] += g_DeltaTime0;
            }
            break;

        case 0:
        case 3:
        case 12:
        case 15:
        case 16:
        case 20:
            chara->properties_E4.player.properties_E4[6] -= g_DeltaTime0 * 2;
            break;

        default:
            chara->properties_E4.player.properties_E4[6] -= g_DeltaTime0;
            break;
    }

    chara->properties_E4.player.properties_E4[6] = CLAMP(chara->properties_E4.player.properties_E4[6], FP_FLOAT_TO(0.0f, Q12_SHIFT), FP_FLOAT_TO(35.0f, Q12_SHIFT));

    if (chara->model_0.anim_4.animIdx_0 == 55)
    {
        if (chara->properties_E4.player.properties_E4[6] < FP_FLOAT_TO(10.0f, Q12_SHIFT) &&
            chara->health_B0 >= FP_FLOAT_TO(30.0f, Q12_SHIFT))
        {
            chara->model_0.stateStep_3 = 0;
            chara->model_0.state_2     = 0;
            extra->model_0.stateStep_3 = 0;
            extra->model_0.state_2     = 0;
        }
    }

    switch (g_SysWork.player_4C.extra_128.field_24)
    {
        case 0:
        case 20:
            if (g_SysWork.player_4C.extra_128.field_20 == 11)
            {
                func_800713E8(27, chara, 204, 200, sp18, sp1C);
            }
            else if (g_SysWork.player_4C.extra_128.field_20 == 12)
            {
                func_800713E8(25, chara, 187, 191, sp18, sp1C);
            }

            if ((g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk15) &&
                ((chara->model_0.anim_4.animIdx_0 >= 53 &&
                  chara->model_0.anim_4.animIdx_0 <= 54) ||
                 chara->model_0.anim_4.animIdx_0 == 57))
            {
                func_8005DD44(sp18, &chara->position_18, 24, sp1C);

                chara->properties_E4.player.field_10C                        = sp1C + 16;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk15;
            }

            if (chara->model_0.anim_4.keyframeIdx0_8 == 246 &&
                !(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk5))
            {
                func_8005DD44(sp18, &chara->position_18, 128, sp1D);

                chara->properties_E4.player.field_10C                        = sp1D + 32;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk5;
            }
            break;

        default:
            break;

        case 4:
        case 24:
            func_800713E8(9, chara, 52, 63, sp18, sp1C);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk15;
            break;

        case 1:
        case 21:
            func_800713E8(5, chara, 18, 6, sp18, sp1C);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk15;
            break;

        case 2:
            if (func_800713E8(7, chara, 31, 41, sp18, sp1D) != 0)
            {
                chara->properties_E4.player.properties_E4[5]++;
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk15;
            break;

        case 5:
            func_800713E8(13, chara, 118, 108, sp18, sp1C);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk15;
            break;

        case 6:
            func_800713E8(11, chara, 93, 83, sp18, sp1C);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk15;
            break;

        case 7:
            if (func_800713E8(17, chara, 145, 139, sp18, sp1D) != 0)
            {
                chara->properties_E4.player.properties_E4[5]++;
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk15;
            break;

        case 8:
            if (func_800713E8(15, chara, 131, 125, sp18, sp1D) != 0)
            {
                chara->properties_E4.player.properties_E4[5]++;
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk15;
            break;

        case 3:
            if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk3)
            {
                if (chara->model_0.anim_4.keyframeIdx0_8 < 152)
                {
                    func_800713E8(19, chara, 151, 154, sp18, sp1D);
                }
                else
                {
                    func_800713E8(19, chara, 156, 154, sp18, sp1D);
                }
            }
            else
            {
                if (chara->model_0.anim_4.keyframeIdx0_8 < 162)
                {
                    func_800713E8(21, chara, 164, 161, sp18, sp1D);
                }
                else
                {
                    func_800713E8(21, chara, 164, 166, sp18, sp1D);
                }
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk15;
            break;

        case 13:
            if (chara->model_0.anim_4.keyframeIdx0_8 < 323)
            {
                func_800713E8(37, chara, 322, 324, sp18, sp1D);
            }
            else
            {
                func_800713E8(37, chara, 327, 324, sp18, sp1D);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk15;
            break;

        case 14:
            if (chara->model_0.anim_4.keyframeIdx0_8 < 352)
            {
                func_800713E8(41, chara, 353, 351, sp18, sp1D);
            }
            else
            {
                func_800713E8(41, chara, 353, 356, sp18, sp1D);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk15;
            break;

        case 12:
            if (chara->model_0.anim_4.keyframeIdx0_8 < 172)
            {
                func_800713E8(23, chara, 171, 174, sp18, sp1D);
            }
            else
            {
                func_800713E8(23, chara, 176, 174, sp18, sp1D);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk15;
            break;

        case 15:
            if (chara->model_0.anim_4.keyframeIdx0_8 < 338)
            {
                func_800713E8(39, chara, 337, 341, sp18, sp1C);
            }
            else if (chara->model_0.anim_4.keyframeIdx0_8 < 344)
            {
                func_800713E8(39, chara, 343, 341, sp18, sp1C);
            }
            else
            {
                func_800713E8(39, chara, 356, 346, sp18, sp1D);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk15;
            break;

        case 16:
            if (chara->model_0.anim_4.keyframeIdx0_8 < 367)
            {
                func_800713E8(43, chara, 366, 370, sp18, sp1C);
            }
            else if (chara->model_0.anim_4.keyframeIdx0_8 < 373)
            {
                func_800713E8(43, chara, 372, 370, sp18, sp1C);
            }
            else
            {
                func_800713E8(43, chara, 385, 375, sp18, sp1D);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk15;
            break;

        case 10:
        case 30:
            func_800713E8(31, chara, 222, 224, sp18, sp1C);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk15;
            break;

        case 9:
        case 29:
            func_800713E8(29, chara, 209, 211, sp18, sp1C);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk15;
            break;

        case 11:
        case 31:
            if (chara->model_0.anim_4.keyframeIdx0_8 < 243)
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk5;
            }

            if (chara->position_18.vy == D_800C4590.field_C)
            {
                func_800713E8(33, chara, 243, 245, sp18, sp1D);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk15;
            break;
    }
}

void func_8007C0D8(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord) // 0x8007C0D8
{
    s_func_800699F8 sp10;
    VECTOR3         sp20;
    VECTOR3         sp30;
    VECTOR3         sp40;
    s16             temp_v0;
    s16             temp_a1;
    s16             temp_s0;
    s32             temp_s0_2;
    s32             temp_s2;
    s32             temp_s2_2;
    s32             temp_s3;
    s32             temp_s3_2;
    s32             temp_v0_3;
    s16             temp_v1;
    s32             posY;
    u32             temp;

    D_800C45F8 = chara->position_18;

    func_800699F8(&sp10, chara->position_18.vx, chara->position_18.vz);

    temp_s3 = FP_MULTIPLY(chara->moveSpeed_38, shRsin(chara->headingAngle_3C), Q12_SHIFT);
    temp_s2 = FP_MULTIPLY(chara->moveSpeed_38, shRcos(chara->headingAngle_3C), Q12_SHIFT);

    temp_s0 = shRcos(ABS(sp10.field_4) >> 3);

    temp_v0 = shRcos(ABS(sp10.field_6) >> 3);

    temp_v1 = FP_MULTIPLY(FP_MULTIPLY(temp_s3, temp_s0, Q12_SHIFT), temp_s0, Q12_SHIFT);
    temp_a1 = FP_MULTIPLY(FP_MULTIPLY(temp_s2, temp_v0, Q12_SHIFT), temp_v0, Q12_SHIFT);

    if (chara->moveSpeed_38 >= 0)
    {
        chara->moveSpeed_38 = SquareRoot0(SQUARE(temp_v1) + SQUARE(temp_a1));
    }
    else
    {
        chara->moveSpeed_38 = -SquareRoot0(SQUARE(temp_v1) + SQUARE(temp_a1));
    }

    temp_s0_2 = FP_MULTIPLY_PRECISE(chara->moveSpeed_38, g_DeltaTime0, Q12_SHIFT);

    temp_v0_3 = chara->headingAngle_3C;
    temp      = temp_s0_2 + 0x7FFF;
    temp_s2_2 = (temp > 0xFFFE) * 4;
    temp_s3_2 = temp_s2_2 >> 1;

    sp20.vx = FP_MULTIPLY_PRECISE((temp_s0_2 >> temp_s3_2), shRsin(temp_v0_3) >> temp_s3_2, Q12_SHIFT);
    sp20.vx <<= temp_s2_2;

    sp20.vz = FP_MULTIPLY_PRECISE((temp_s0_2 >> temp_s3_2), shRcos(temp_v0_3) >> temp_s3_2, Q12_SHIFT);
    sp20.vz <<= temp_s2_2;

    sp20.vy = FP_MULTIPLY_PRECISE(chara->field_34, g_DeltaTime0, Q12_SHIFT);

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP1_S05)
    {
        sp20.vx = sp20.vx + D_800C45B0.vx;
        sp30.vx = sp20.vx;
        sp20.vz = sp20.vz + D_800C45B0.vz;
        sp30.vz = sp20.vz;
    }

    func_80069B24(&D_800C4590, &sp20, chara);

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP1_S05)
    {
        if (D_800C45B0.vx != 0 && (DIFF_SIGN(sp30.vx, D_800C4590.field_0.vx) || abs(sp30.vx) >= ABS(D_800C4590.field_0.vx)))
        {
            sp40.vx = sp30.vx - D_800C4590.field_0.vx;
        }
        else
        {
            sp40.vx = 0;
        }

        if (D_800C45B0.vz != 0 && (DIFF_SIGN(sp30.vz, D_800C4590.field_0.vz) || abs(sp30.vz) >= ABS(D_800C4590.field_0.vz)))
        {
            sp40.vz = sp30.vz - D_800C4590.field_0.vz;
        }
        else
        {
            sp40.vz = 0;
        }

        g_MapOverlayHeader.func_158(-sp40.vx, -sp40.vz);
    }

    chara->position_18.vx += D_800C4590.field_0.vx;
    chara->position_18.vy += D_800C4590.field_0.vy;
    chara->position_18.vz += D_800C4590.field_0.vz;

    if (g_SysWork.player_4C.extra_128.field_20 == 2 ||
        g_SysWork.player_4C.extra_128.field_20 == 6 ||
        g_SysWork.player_4C.extra_128.field_20 == 7)
    {
        chara->properties_E4.player.properties_E4[9] += SquareRoot0(SQUARE(D_800C4590.field_0.vx) +
                                                                    SQUARE(D_800C4590.field_0.vy) +
                                                                    SQUARE(D_800C4590.field_0.vz));
    }
    else
    {
        chara->properties_E4.player.properties_E4[9] = 0;
    }

    if (*(u16*)&g_SavegamePtr->mapOverlayId_A4 == 3331)
    {
        D_800C4590.field_C = 0;
    }

    if (D_800C4590.field_14 == 0)
    {
        D_800C4590.field_C = chara->properties_E4.player.properties_E4[2];
    }

    if (chara->position_18.vy > D_800C4590.field_C)
    {
        chara->position_18.vy = D_800C4590.field_C;
        chara->field_34       = 0;
    }

    temp_a1 = (ratan2(chara->position_18.vx - D_800C45F8.vx, chara->position_18.vz - D_800C45F8.vz) + 0x1000) & 0xFFF;

    if (((u32)g_SysWork.player_4C.extra_128.field_1C - 3) >= 2)
    {
        if (!g_Player_IsInWalkToRunTransition)
        {
            posY = chara->position_18.vy;
            if ((D_800C4590.field_C - posY) >= FP_METER(0.65f))
            {
                if (ABS_DIFF(chara->rotation_24.vy, temp_a1) >= FP_ANGLE(90.0f) &&
                    ABS_DIFF(chara->rotation_24.vy, temp_a1) < FP_ANGLE(270.0f))
                {
                    if (g_SysWork.player_4C.extra_128.field_24 != 11)
                    {
                        g_SysWork.player_4C.extra_128.field_1C = 4;
                        chara->model_0.stateStep_3             = 0;
                        chara->model_0.state_2                 = 0;
                        extra->model_0.stateStep_3             = 0;
                        extra->model_0.state_2                 = 0;
                        g_SysWork.player_4C.extra_128.field_20 = 0;
                        g_SysWork.player_4C.extra_128.field_24 = 0;
                    }
                }
                else
                {
                    g_SysWork.player_4C.extra_128.field_1C = 3;
                    chara->model_0.stateStep_3             = 0;
                    chara->model_0.state_2                 = 0;
                    extra->model_0.stateStep_3             = 0;
                    extra->model_0.state_2                 = 0;
                    g_SysWork.player_4C.extra_128.field_20 = 0;
                    g_SysWork.player_4C.extra_128.field_24 = 0;
                }

                g_SysWork.playerCombatInfo_38.isAiming_13 = false;
            }
        }
    }

    chara->properties_E4.player.properties_E4[2] = D_800C4590.field_C;
    coord->coord.t[0]                            = FP_FROM(chara->position_18.vx, Q4_SHIFT);
    coord->coord.t[1]                            = FP_FROM(chara->position_18.vy, Q4_SHIFT);
    coord->coord.t[2]                            = FP_FROM(chara->position_18.vz, Q4_SHIFT);
}

void Player_ReceiveDamage(s_SubCharacter* chara, s_MainCharacterExtra* extra) // 0x8007C800
{
    s16 sp10;
    u16 temp_s0;
    s32 i;
    s32 var_s4;
    s32 var_v1_2;
    s8  temp_v0_3;

    var_s4 = 0x52E;

    if (chara->field_41 != NO_VALUE)
    {
        switch (D_800AD4C8[chara->field_41].field_11)
        {
            case 2:
                var_s4 = 0x52F;
                break;

            case 4:
                var_s4 = 0x530;
                break;

            case 5:
                var_s4 = 0x531;
                break;

            case 0:
                break;
        }
    }

    if (g_Player_DisableControl || g_Player_DisableDamage)
    {
        chara->damageReceived_C0 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
        return;
    }

    switch (g_SysWork.player_4C.extra_128.field_1C)
    {
        case 3:
        case 4:
        case 41:
        case 42:
        case 45:
        case 46:
        case 49:
        case 50:
            break;

        case 8:
        case 9:
            return;

        case 10:
        case 13:
        case 14:
        case 15:
        case 32:
        case 33:
        case 39:
        case 40:
        case 47:
        case 48:
		// Code related when enemies grab Harry.
            if (chara->damageReceived_C0 != 0 && !(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk14))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk14;
                func_8005DC1C(var_s4, &chara->position_18, 0x20, 0);
                chara->properties_E4.player.field_10C = 0x40;
            }

            if (chara->damageReceived_C0 == FP_FLOAT_TO(0.0f, Q12_SHIFT))
            {
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk14;
            }

            func_80089494();
            break;

        case 7:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 35:
        case 37:
        case 38:
            chara->field_BC = 0;
            chara->field_B8 = 0;
            chara->field_B4 = 0;

            if (chara->field_41 == 0x2F)
            {
                g_SysWork.player_4C.chara_0.field_D6   = 0;
                g_SysWork.player_4C.extra_128.field_1C = 9;
                chara->model_0.stateStep_3             = 0;
                chara->model_0.state_2                 = 0;
                extra->model_0.stateStep_3             = 0;
                extra->model_0.state_2                 = 0;
                g_SysWork.player_4C.extra_128.field_20 = 0;
                g_SysWork.player_4C.extra_128.field_24 = 0;
                return;
            }

            if (chara->field_41 >= 0x44 &&
                chara->field_41 <  0x46)
            {
                chara->damageReceived_C0 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
            }
            break;

        default:
            if (g_Player_IsInWalkToRunTransition)
            {
                D_800C4560 = chara->field_41;
                return;
            }

            if (D_800C4560 != NO_VALUE)
            {
                chara->field_41 = D_800C4560;
                D_800C4560      = NO_VALUE;
            }

            if (chara->field_41 <= 0)
            {
                break;
            }

            g_SysWork.field_2353                           = NO_VALUE;
            g_SysWork.playerCombatInfo_38.equippedWeapon_F = (g_SavegamePtr->equippedWeapon_AA == InventoryItemId_Unequipped) ? NO_VALUE : (g_SavegamePtr->equippedWeapon_AA - 0x80);

            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill)
            {
                func_8004C564(2, 3);
            }

            if (g_SysWork.player_4C.extra_128.field_1C >= 3 &&
                g_SysWork.player_4C.extra_128.field_1C <  7)
            {
                g_SysWork.player_4C.chara_0.field_C8         = -0x1999;
                g_SysWork.player_4C.chara_0.field_CA         = 0;
                g_SysWork.player_4C.chara_0.field_CE         = -0x1199;
                g_SysWork.player_4C.chara_0.field_D8.field_6 = 0;
                g_SysWork.player_4C.chara_0.field_D8.field_4 = 0;
                g_SysWork.player_4C.chara_0.field_D8.field_2 = 0;
                g_SysWork.player_4C.chara_0.field_D8.field_0 = 0;
            }

            temp_s0 = g_SysWork.npcs_1A0[chara->field_40].rotation_24.vy;
            if (chara->field_41 >= 0x40 &&
                chara->field_41 <  0x42)
            {
                temp_s0 -= 0x400;
            }
            else if (chara->field_41 == 0x45)
            {
                temp_s0 = 0x400;
            }
            else if (chara->field_41 == 0x44)
            {
                temp_s0 = chara->field_B8;
            }

            temp_s0   = ((temp_s0 - chara->rotation_24.vy) + 0x1000) & 0xFFF;
            temp_v0_3 = chara->field_41 - 40;
            switch (temp_v0_3)
            {
                case 27:
                    g_SysWork.player_4C.extra_128.field_1C = 7;
                    chara->model_0.stateStep_3             = 0;
                    chara->model_0.state_2                 = 0;
                    extra->model_0.stateStep_3             = 0;
                    extra->model_0.state_2                 = 0;
                    g_SysWork.player_4C.extra_128.field_20 = 0;
                    g_SysWork.player_4C.extra_128.field_24 = 0;
                    break;

                case 23:
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0x1800;
                    func_8007FB34(chara->rotation_24.vy, g_SysWork.npcs_1A0[0].rotation_24.vy, &sp10);
                    D_800C4608 = sp10;

                    if (temp_s0 >= 0x400 &&
                        temp_s0 <  0xC00)
                    {
                        g_SysWork.player_4C.extra_128.field_1C = 45;
                        chara->model_0.stateStep_3             = 0;
                        chara->model_0.state_2                 = 0;
                        extra->model_0.stateStep_3             = 0;
                        extra->model_0.state_2                 = 0;
                        g_SysWork.player_4C.extra_128.field_20 = 0;
                        g_SysWork.player_4C.extra_128.field_24 = 0;
                    }
                    else
                    {
                        g_SysWork.player_4C.extra_128.field_1C = 46;
                        chara->model_0.stateStep_3             = 0;
                        chara->model_0.state_2                 = 0;
                        extra->model_0.stateStep_3             = 0;
                        extra->model_0.state_2                 = 0;
                        g_SysWork.player_4C.extra_128.field_20 = 0;
                        g_SysWork.player_4C.extra_128.field_24 = 0;
                    }
                    break;

                case 20:
                case 22:
                    chara->damageReceived_C0               = FP_FLOAT_TO(10.0f, Q12_SHIFT);
                    g_SysWork.player_4C.extra_128.field_1C = 19;
                    chara->model_0.stateStep_3             = 0;
                    chara->model_0.state_2                 = 0;
                    extra->model_0.stateStep_3             = 0;
                    extra->model_0.state_2                 = 0;
                    g_SysWork.player_4C.extra_128.field_20 = 0;
                    g_SysWork.player_4C.extra_128.field_24 = 0;
                    break;

                case 1:
                case 2:
                    g_SysWork.player_4C.extra_128.field_1C = 19;
                    chara->model_0.stateStep_3             = 0;
                    chara->model_0.state_2                 = 0;
                    extra->model_0.stateStep_3             = 0;
                    extra->model_0.state_2                 = 0;
                    g_SysWork.player_4C.extra_128.field_20 = 0;
                    g_SysWork.player_4C.extra_128.field_24 = 0;
                    break;

                case 9:
                case 14:
                case 16:
                case 26:
                    if (temp_s0 >= 0x400 &&
                        temp_s0 <  0xC00)
                    {
                        g_SysWork.field_2354[0] = chara->field_40;

                        temp_v0_3 = chara->field_41 - 0x2D;
                        switch (temp_v0_3)
                        {
                            case 9:
                                g_SysWork.player_4C.extra_128.field_1C = 0x25;
                                chara->model_0.stateStep_3             = 0;
                                chara->model_0.state_2                 = 0;
                                extra->model_0.stateStep_3             = 0;
                                extra->model_0.state_2                 = 0;
                                g_SysWork.player_4C.extra_128.field_20 = 0;
                                g_SysWork.player_4C.extra_128.field_24 = 0;
                                break;

                            case 0:
                            case 11:
                                g_SysWork.player_4C.extra_128.field_1C = 0xA;
                                chara->model_0.stateStep_3             = 0;
                                chara->model_0.state_2                 = 0;
                                extra->model_0.stateStep_3             = 0;
                                extra->model_0.state_2                 = 0;
                                g_SysWork.player_4C.extra_128.field_20 = 0;
                                g_SysWork.player_4C.extra_128.field_24 = 0;
                                break;

                            case 4:
                                g_SysWork.player_4C.extra_128.field_1C = 0xE;
                                chara->model_0.stateStep_3             = 0;
                                chara->model_0.state_2                 = 0;
                                extra->model_0.stateStep_3             = 0;
                                extra->model_0.state_2                 = 0;
                                g_SysWork.player_4C.extra_128.field_20 = 0;
                                g_SysWork.player_4C.extra_128.field_24 = 0;
                                break;

                            case 21:
                                g_SysWork.player_4C.extra_128.field_1C = 0x20;
                                chara->model_0.stateStep_3             = 0;
                                chara->model_0.state_2                 = 0;
                                extra->model_0.stateStep_3             = 0;
                                extra->model_0.state_2                 = 0;
                                g_SysWork.player_4C.extra_128.field_20 = 0;
                                g_SysWork.player_4C.extra_128.field_24 = 0;
                                break;
                        }
                    }
                    else
                    {
                        g_SysWork.field_2354[1] = chara->field_40;

                        temp_v0_3 = chara->field_41 - 0x2D;
                        switch (temp_v0_3)
                        {
                            case 9:
                                g_SysWork.player_4C.extra_128.field_1C = 0x26;
                                chara->model_0.stateStep_3             = 0;
                                chara->model_0.state_2                 = 0;
                                extra->model_0.stateStep_3             = 0;
                                extra->model_0.state_2                 = 0;
                                g_SysWork.player_4C.extra_128.field_20 = 0;
                                g_SysWork.player_4C.extra_128.field_24 = 0;
                                break;

                            case 0:
                            case 11:
                                g_SysWork.player_4C.extra_128.field_1C = 0xD;
                                chara->model_0.stateStep_3             = 0;
                                chara->model_0.state_2                 = 0;
                                extra->model_0.stateStep_3             = 0;
                                extra->model_0.state_2                 = 0;
                                g_SysWork.player_4C.extra_128.field_20 = 0;
                                g_SysWork.player_4C.extra_128.field_24 = 0;
                                break;

                            case 4:
                                g_SysWork.player_4C.extra_128.field_1C = 0xF;
                                chara->model_0.stateStep_3             = 0;
                                chara->model_0.state_2                 = 0;
                                extra->model_0.stateStep_3             = 0;
                                extra->model_0.state_2                 = 0;
                                g_SysWork.player_4C.extra_128.field_20 = 0;
                                g_SysWork.player_4C.extra_128.field_24 = 0;
                                break;

                            case 21:
                                g_SysWork.player_4C.extra_128.field_1C = 0x21;
                                chara->model_0.stateStep_3             = 0;
                                chara->model_0.state_2                 = 0;
                                extra->model_0.stateStep_3             = 0;
                                extra->model_0.state_2                 = 0;
                                g_SysWork.player_4C.extra_128.field_20 = 0;
                                g_SysWork.player_4C.extra_128.field_24 = 0;
                                break;
                        }
                    }
                    break;

                case 7:
                    chara->health_B0                       = NO_VALUE;
                    chara->field_D6                        = 0;
                    g_SysWork.player_4C.extra_128.field_1C = 9;
                    chara->model_0.stateStep_3             = 0;
                    chara->model_0.state_2                 = 0;
                    extra->model_0.stateStep_3             = 0;
                    extra->model_0.state_2                 = 0;
                    g_SysWork.player_4C.extra_128.field_20 = 0;
                    g_SysWork.player_4C.extra_128.field_24 = 0;
                    return;

                case 29:
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0x1999;
                    func_8007FB34(chara->rotation_24.vy, 0x400, &sp10);
                    D_800C4608 = sp10;

                case 28:
                    if (chara->field_41 != 0x45)
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.field_126 = 0x4000;
                        func_8007FB34(chara->rotation_24.vy, (s16)chara->field_B8, &sp10);
                        D_800C4608 = sp10;
                    }

                case 0:
                case 3:
                case 4:
                case 5:
                case 6:
                case 8:
                case 10:
                case 12:
                case 17:
                case 18:
                case 19:
                case 21:
                case 24:
                case 25:
                    if (temp_s0 >= 0x200 && temp_s0 < 0x600)
                    {
                        var_v1_2 = 0x1A;
                    }
                    else if (temp_s0 >= 0x600 && temp_s0 < 0xA00)
                    {
                        var_v1_2 = 0x18;
                    }
                    else if (temp_s0 >= 0xA00 && temp_s0 < 0xE00)
                    {
                        var_v1_2 = 0x19;
                    }
                    else
                    {
                        var_v1_2 = 0x17;
                    }

                    g_SysWork.player_4C.extra_128.field_1C = var_v1_2;
                    chara->model_0.stateStep_3             = 0;
                    chara->model_0.state_2                 = 0;
                    extra->model_0.stateStep_3             = 0;
                    extra->model_0.state_2                 = 0;
                    g_SysWork.player_4C.extra_128.field_20 = 0;
                    g_SysWork.player_4C.extra_128.field_24 = 0;
                    break;

                case 13:
                    if (temp_s0 < 0x7FF)
                    {
                        var_v1_2 = 0x1B;
                    }
                    else
                    {
                        var_v1_2 = 0x1C;
                    }

                    g_SysWork.player_4C.extra_128.field_1C = var_v1_2;
                    chara->model_0.stateStep_3             = 0;
                    chara->model_0.state_2                 = 0;
                    extra->model_0.stateStep_3             = 0;
                    extra->model_0.state_2                 = 0;
                    g_SysWork.player_4C.extra_128.field_20 = 0;
                    g_SysWork.player_4C.extra_128.field_24 = 0;
                    break;
            }

            if ((u32)g_SysWork.player_4C.extra_128.field_1C >= 3)
            {
                chara->properties_E4.player.properties_E4[1]                = 0;
                chara->properties_E4.player.properties_E4[4]                = 0;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk12;
                g_SysWork.playerCombatInfo_38.isAiming_13                   = false;
                g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;
                chara->field_44                                             = NO_VALUE;
            }
            break;
    }

    if (g_SysWork.player_4C.extra_128.field_1C == 8)
    {
        chara->damageReceived_C0 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
        chara->field_BC          = 0;
        chara->field_B8          = 0;
        chara->field_B4          = 0;
        return;
    }

    if (chara->damageReceived_C0 != 0)
    {
        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;
        if (!(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_Unk14))
        {
            func_8005DC1C(var_s4, &chara->position_18, 0x20, 0);
            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_Unk14;
            chara->properties_E4.player.field_10C = 0x40;
        }

        if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP0_S00)
        {
            chara->health_B0 -= chara->damageReceived_C0 * 2;
        }
        else
        {
            switch (g_SavegamePtr->gameDifficulty_260)
            {
                case GameDifficulty_Easy:
                    chara->damageReceived_C0 = (chara->damageReceived_C0 * 3) >> 2;
                    break;

                case GameDifficulty_Hard:
                    chara->damageReceived_C0 = (chara->damageReceived_C0 * 6) >> 2;
                    break;
            }

            chara->health_B0 -= chara->damageReceived_C0;
        }

        if (chara->health_B0 < 0)
        {
            chara->health_B0 = NO_VALUE;
            D_800C4561       = 1;
        }

        func_800893D0(chara->damageReceived_C0);
        chara->damageReceived_C0 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
    }

    if (chara->health_B0 <= FP_FLOAT_TO(0.0f, Q12_SHIFT) && g_SysWork.player_4C.extra_128.field_1C != 8 &&
        g_SysWork.player_4C.extra_128.field_1C != 36 && g_SysWork.player_4C.extra_128.field_1C != 39 &&
        g_SysWork.player_4C.extra_128.field_1C != 40 && g_SysWork.player_4C.extra_128.field_1C != 47 &&
        g_SysWork.player_4C.extra_128.field_1C != 48 && !g_Player_IsInWalkToRunTransition)
    {
        chara->field_40          = NO_VALUE;
        g_SavegamePtr->field_238 = 0;

        for (i = 0; i < 4; i++)
        {
            g_SysWork.field_2354[i] = NO_VALUE;
        }

        if (chara->field_41 == 66)
        {
            g_SysWork.player_4C.extra_128.field_1C = 36;
            chara->model_0.stateStep_3             = 0;
            chara->model_0.state_2                 = 0;
            extra->model_0.stateStep_3             = 0;
            extra->model_0.state_2                 = 0;
            g_SysWork.player_4C.extra_128.field_20 = 0;
            g_SysWork.player_4C.extra_128.field_24 = 0;
        }
        else
        {
            g_SysWork.player_4C.extra_128.field_1C = 8;
            chara->model_0.stateStep_3             = 0;
            chara->model_0.state_2                 = 0;
            extra->model_0.stateStep_3             = 0;
            extra->model_0.state_2                 = 0;
            g_SysWork.player_4C.extra_128.field_20 = 0;
            g_SysWork.player_4C.extra_128.field_24 = 0;
        }
    }
}

void func_8007D090(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord) // 0x8007D090
{
    s32 temp_a1_3;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_v1;

    switch (g_SysWork.player_4C.extra_128.field_1C)
    {
        case 1:
            switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
            {
                case EquippedWeaponId_Handgun:
                    var_a2 = 20;
                    var_a3 = 2;
                    break;

                case EquippedWeaponId_HuntingRifle:
                    var_a2 = 18;
                    var_a3 = 6;
                    break;

                case EquippedWeaponId_Shotgun:
                    var_a2 = 26;
                    var_a3 = 3;
                    break;

                case EquippedWeaponId_HyperBlaster:
                    var_a2 = 30;
                    var_a3 = 0;
                    break;

                default:
                    var_a2 = 12;
                    var_a3 = 6;
                    break;
            }

            if (g_SysWork.player_4C.extra_128.field_20 == 26 || g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
            {
                D_800AF212 = 0;
                D_800AF210 = 0;
            }
            else
            {
                D_800AF212 = g_SysWork.player_4C.chara_0.properties_E4.npc.field_122 - (1 << 10);

                if (ABS(chara->rotation_24.pad - chara->rotation_24.vy) > FP_ANGLE(180.0f))
                {
                    if (chara->rotation_24.pad > chara->rotation_24.vy)
                    {
                        D_800AF210 = -(((chara->rotation_24.vy + FP_ANGLE(360.0f)) - chara->rotation_24.pad) & 0xFFF);
                    }
                    else
                    {
                        D_800AF210 = ((chara->rotation_24.pad + FP_ANGLE(360.0f)) - chara->rotation_24.vy) & 0xFFF;
                    }
                }
                else
                {
                    D_800AF210 = chara->rotation_24.pad - chara->rotation_24.vy;
                }

                if (chara->properties_E4.player.properties_E4[7] != 0 || g_SysWork.player_4C.extra_128.field_20 == 22 ||
                    g_SysWork.player_4C.extra_128.field_20 == 23)
                {
                    if (g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & (1 << 8))
                    {
                        var_v1 = 0;
                    }
                    else
                    {
                        var_v1 = var_a3;
                    }

                    if (chara->properties_E4.player.properties_E4[4] != 0)
                    {
                        temp_a1_3 = chara->properties_E4.player.properties_E4[4] - D_800AF212;
                        if (D_800AF212 < chara->properties_E4.player.properties_E4[4])
                        {
                            var_a0 = chara->properties_E4.player.properties_E4[7] * (((var_a2 + chara->properties_E4.player.properties_E4[7]) * g_DeltaTime0) / 136);
                            if (var_a0 < temp_a1_3)
                            {
                                D_800AF212 = chara->properties_E4.larvalStalker.properties_E8[3].val16[0] - var_a0;
                            }
                        }
                        else
                        {
                            var_a0 = -(chara->properties_E4.player.properties_E4[7] * (((var_a2 + chara->properties_E4.player.properties_E4[7]) * g_DeltaTime0) / 136));
                            if (temp_a1_3 < var_a0)
                            {
                                D_800AF212 = chara->properties_E4.larvalStalker.properties_E8[3].val16[0] - var_a0;
                            }
                        }
                    }
                    else
                    {
                        if (chara->properties_E4.player.properties_E4[7] < var_v1)
                        {
                            D_800AF210 = 0;
                            D_800AF212 = 0;
                        }
                        else
                        {
                            temp_v0   = chara->properties_E4.player.properties_E4[7] + 1;
                            temp_a1_3 = temp_v0 - var_v1;
                            var_a0    = 4;
                            var_a0    = temp_a1_3 * (((var_a2 + ((temp_a1_3 * 2) + var_a0)) * g_DeltaTime0) / 136);

                            if (D_800AF212 > 0)
                            {
                                if (var_a0 < D_800AF212)
                                {
                                    D_800AF212 = var_a0;
                                }
                            }
                            else if (D_800AF212 < 0)
                            {
                                if (D_800AF212 < -var_a0)
                                {
                                    D_800AF212 = -var_a0;
                                }
                            }

                            if (D_800AF210 > 0)
                            {
                                if (var_a0 < D_800AF210)
                                {
                                    D_800AF210 = var_a0;
                                }
                            }
                            else if (D_800AF210 < 0)
                            {
                                if (D_800AF210 < -var_a0)
                                {
                                    D_800AF210 = -var_a0;
                                }
                            }
                        }
                    }
                }

                D_800AF212 = CLAMP(D_800AF212, -0x280, 0x280);
                D_800AF210 = CLAMP(D_800AF210, -0x180, 0x180);

                func_80044F14(&coord[1], 0, D_800AF212 >> 1, D_800AF210);
                shRotMatrixZ(D_800AF212 >> 1, &coord[4].coord);
                shRotMatrixZ(D_800AF212 >> 1, &coord[8].coord);
            }
            break;

        case 0:
            if (D_800AF212 > 0)
            {
                D_800AF212 -= 0x20;
            }
            else if (D_800AF212 < 0)
            {
                D_800AF212 += 0x20;
            }

            temp_a1_3 = (g_DeltaTime0 * 24) / 136;

            if (D_800AF212 > 0)
            {
                D_800AF212 -= temp_a1_3;
                if (D_800AF212 < 0)
                {
                    D_800AF212 = 0;
                }
            }
            else if (D_800AF212 < 0)
            {
                D_800AF212 += temp_a1_3;
                if (D_800AF212 > 0)
                {
                    D_800AF212 = 0;
                }
            }

            if (D_800AF210 > 0)
            {
                D_800AF210 -= temp_a1_3;
                if (D_800AF210 < 0)
                {
                    D_800AF210 = 0;
                }
            }
            else if (D_800AF210 < 0)
            {
                D_800AF210 += temp_a1_3;
                if (D_800AF210 > 0)
                {
                    D_800AF210 = 0;
                }
            }

            func_80044F14(&coord[1], 0, D_800AF212 >> 1, D_800AF210);
            shRotMatrixZ(D_800AF212 >> 1, &coord[4].coord);
            shRotMatrixZ(D_800AF212 >> 1, &coord[8].coord);
            break;

        case 180:
            if (D_800AF210 != 0)
            {
                func_80044F14(&coord[1], 0, 0,     0xC0);
                func_80044F14(&coord[2], 0, 0x140, 0xE0);
            }
            break;

        default:
            if (g_SysWork.player_4C.extra_128.field_1C >= 52 &&
                g_SysWork.player_4C.extra_128.field_1C <  59)
            {
                func_80044F14(&coord[2], 0, 0, D_800AF210);
            }
            else
            {
                D_800AF210 = 0;
                D_800AF212 = 0;
            }
            break;
    }

    if (g_SysWork.field_2358 != 0 && g_SysWork.player_4C.extra_128.field_1C < 58)
    {
        func_80044F14(&g_SysWork.playerBoneCoords_890[8],  0,    0x2D0, -0x64);
        func_80044F14(&g_SysWork.playerBoneCoords_890[9], -0xA0, 0x100, -0x15E);
        func_80044F14(&g_SysWork.playerBoneCoords_890[10], 0x96, 0,      0);
    }
}

void func_8007D6E0() // 0x8007D6E0
{
    D_800AF210 = 1;
}

s32 func_8007D6F0(s_SubCharacter* arg0, s_D_800C45C8* arg1) // 0x8007D6F0
{
    s_func_800700F8_2 sp10[2];
    VECTOR3           vecs[4];
    bool              ret[2];
    s32               temp_lo;
    s32               temp_s0;
    s32               temp_s1;
    s32               temp_s3;
    s32               temp_s4;
    s32               temp_s5;
    s16               angle;
    u16               angleDelta;

    temp_s0  = g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 3;
    temp_s0 += FP_METER(0.75f); // Maybe meters?
    temp_s1  = FP_METER(-0.6f);
    temp_s1 -= g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >> 4;

    temp_s4 = FP_MULTIPLY(shRcos(arg0->headingAngle_3C), FP_METER(0.2f), Q12_SHIFT); // Maybe meters?
    temp_s3 = FP_MULTIPLY(shRsin(arg0->headingAngle_3C), FP_METER(0.2f), Q12_SHIFT); // Maybe meters?
    temp_s5 = FP_MULTIPLY(temp_s0, shRsin(arg0->headingAngle_3C), Q12_SHIFT);
    temp_lo = FP_MULTIPLY(temp_s0, shRcos(arg0->headingAngle_3C), Q12_SHIFT);

    temp_s1 -= FP_METER(0.4f);

    vecs[0].vy = arg0->position_18.vy + temp_s1;
    vecs[0].vx = (arg0->position_18.vx + temp_s4) + temp_s5;

    vecs[0].vz = (arg0->position_18.vz - temp_s3) + temp_lo;
    vecs[2].vy = arg0->position_18.vy - FP_METER(0.4f);
    vecs[2].vx = arg0->position_18.vx + temp_s4;
    vecs[2].vz = arg0->position_18.vz - temp_s3;

    ret[0] = func_8006D90C(&sp10[0], &vecs[2], &vecs[0]);

    if (ret[0])
    {
        vecs[1].vy = vecs[0].vy;
        vecs[1].vx = (arg0->position_18.vx - temp_s4) + temp_s5;
        vecs[1].vz = (arg0->position_18.vz + temp_s3) + temp_lo;
        vecs[3].vy = vecs[2].vy;
        vecs[3].vx = arg0->position_18.vx - temp_s4;
        vecs[3].vz = arg0->position_18.vz + temp_s3;

        ret[1] = func_8006D90C(&sp10[1], &vecs[3], &vecs[1]);

        if (ret[1])
        {
            arg1->field_14 = (sp10[0].field_14 + sp10[1].field_14) >> 1;
            arg1->field_1  = sp10[0].field_1;

            angle      = (((sp10[0].field_1C + sp10[1].field_1C) >> 1) + FP_ANGLE(360.0f)) & 0xFFF;
            angleDelta = ABS_DIFF(angle, arg0->headingAngle_3C);

            if (angleDelta > FP_ANGLE(160.0f) &&
                angleDelta < FP_ANGLE(200.0f))
            {
                if ((arg0->position_18.vy - FP_METER(1.3f)) < sp10[0].field_18 || sp10[0].field_1 == 0 || sp10[0].field_1 == 12)
                {
                    if ((arg0->position_18.vy - FP_METER(0.3f)) >= sp10[0].field_18)
                    {
                        return 2;
                    }
                }
                else
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void func_8007D970(s_SubCharacter* chara, GsCOORDINATE2* coord) // 0x8007D970
{
    VECTOR  sp20;
    VECTOR  sp30;
    VECTOR  sp40;
    MATRIX  sp50;
    VECTOR  sp70;
    VECTOR  sp80;
    SVECTOR sp90;
    DVECTOR sp98;
    s32      temp_s0;
    s32      temp_v0_5;
    s32      temp_v0_6;
    s16      var_a1;
    VECTOR*  vec;
    VECTOR*  vec2;
    VECTOR*  vec3;
    s_Model* model;

    model = &g_SysWork.player_4C.extra_128.model_0;

    if (g_SysWork.player_4C.extra_128.field_24 < 20)
    {
        vec     = &g_SysWork.playerCombatInfo_38.field_0;
        vec->vx = g_SysWork.playerBoneCoords_890[17].workm.t[0] * 16;
        vec->vy = g_SysWork.playerBoneCoords_890[17].workm.t[1] * 16;
        vec->vz = g_SysWork.playerBoneCoords_890[17].workm.t[2] * 16;
    }
    else
    {
        switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
        {
            case NO_VALUE:
            case 8:
            case 9:
                vec2     = &g_SysWork.playerCombatInfo_38.field_0;
                vec2->vx = g_SysWork.playerBoneCoords_890[17].workm.t[0] * 16;
                vec2->vy = g_SysWork.playerBoneCoords_890[17].workm.t[1] * 16;
                vec2->vz = g_SysWork.playerBoneCoords_890[17].workm.t[2] * 16;
                break;

            default:
                vec3     = &g_SysWork.playerCombatInfo_38.field_0;
                vec3->vx = g_SysWork.playerBoneCoords_890[10].workm.t[0] * 16;
                vec3->vy = g_SysWork.playerBoneCoords_890[10].workm.t[1] * 16;
                vec3->vz = g_SysWork.playerBoneCoords_890[10].workm.t[2] * 16;
                break;
        }
    }

    if (g_SysWork.player_4C.chara_0.properties_E4.player.field_114 != 0)
    {
        g_SysWork.timer_2C++;

        if (g_SysWork.player_4C.chara_0.properties_E4.player.field_126 >= 0x32C8 || (g_SysWork.timer_2C & (1 << 0)))
        {
            func_8006342C(g_SavegamePtr->equippedWeapon_AA - InventoryItemId_KitchenKnife, 0, 0, coord);
        }
    }

    if (((u32)g_SysWork.player_4C.extra_128.field_1C - 7) >= 44 &&
        ((u32)g_SysWork.player_4C.extra_128.field_1C < 2 || g_SysWork.player_4C.extra_128.field_1C == 5 || g_SysWork.player_4C.extra_128.field_1C == 6))
    {
        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun && g_SysWork.player_4C.extra_128.field_24 >= 20)
        {
            if (g_SysWork.player_4C.extra_128.field_1C == 1 && D_800AF21C != NO_VALUE)
            {
                sp98.vx = ratan2((g_SysWork.npcs_1A0[D_800AF21C].position_18.vx + g_SysWork.npcs_1A0[D_800AF21C].field_D8.field_0) - g_SysWork.playerCombatInfo_38.field_0.vx,
                                 (g_SysWork.npcs_1A0[D_800AF21C].position_18.vz + g_SysWork.npcs_1A0[D_800AF21C].field_D8.field_2) - g_SysWork.playerCombatInfo_38.field_0.vz);
            }
            else
            {
                // HACK: Required for match.
                do { chara->rotation_24.pad = chara->rotation_24.vy; } while (0);

                sp98.vx = chara->rotation_24.pad;
            }

            sp98.vy = g_SysWork.player_4C.chara_0.properties_E4.player.field_122;
            var_a1  = sp98.vy;

            if (var_a1 >= 0x180)
            {
                if (var_a1 > 0x680)
                {
                    var_a1 = 0x680;
                }
            }
            else
            {
                var_a1 = 0x180;
            }

            if (chara->field_44 > 0)
            {
                func_8006342C(g_SysWork.playerCombatInfo_38.equippedWeapon_F, var_a1, sp98.vx, coord);
            }
        }
        else
        {
            switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
            {
                case NO_VALUE:
                case 8:
                case 9:
                    *(u32*)&sp90 = 0x3C0000;
                    sp90.vz      = 0x86;
                    Vw_CoordHierarchyMatrixCompute(&coord[17], &sp50);
                    break;

                default:
                    if (g_SysWork.player_4C.extra_128.field_24 < 20)
                    {
                        *(u32*)&sp90 = 0x3C0000;
                        sp90.vz      = 0x86;
                        Vw_CoordHierarchyMatrixCompute(&coord[17], &sp50);
                    }
                    else
                    {
                        switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F % 10)
                        {
                            case 0:
                                *(u32*)&sp90 = (FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xF, Q12_SHIFT) & 0xFFFF) +
                                               (-(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x4B, Q12_SHIFT - 1)) << 16);
                                sp90.vz      = FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x4B, Q12_SHIFT) >> 1;
                                break;

                            case 1:
                                *(u32*)&sp90 = (FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xF, Q12_SHIFT) & 0xFFFF) +
                                               (-(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xE1, Q12_SHIFT) >> 1) << 16);
                                sp90.vz      = FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x2D, Q12_SHIFT - 2);
                                break;

                            case 5:
                                *(u32*)&sp90 = ((FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xF, Q12_SHIFT) >> 1) & 0xFFFF) +
                                               (-(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x87, Q12_SHIFT) >> 1) << 16);
                                sp90.vz      = FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x1EF, Q12_SHIFT) >> 1;
                                break;

                            case 2:
                                *(u32*)&sp90 = (-(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x2D, Q12_SHIFT)) << 16);
                                sp90.vz          = FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x2D, Q12_SHIFT - 2);
                                break;

                            case 7:
                                *(u32*)&sp90 = (-(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x2C1, Q12_SHIFT) >> 1) << 16);
                                sp90.vz      = FP_MULTIPLY((u32)D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xC3, Q12_SHIFT);
                                break;

                            case 4:
                                *(u32*)&sp90 = ((FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xF, Q12_SHIFT) >> 1) & 0xFFFF) +
                                               (-(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x69, Q12_SHIFT)) << 16);
                                sp90.vz      = FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x13B, Q12_SHIFT) >> 1;
                                break;

                            case 6:
                                *(u32*)&sp90 = ((FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xF, Q12_SHIFT) >> 1) & 0xFFFF) +
                                               (-(FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0x13B, Q12_SHIFT) >> 1) << 16);
                                sp90.vz      = FP_MULTIPLY(D_800AD4C8[g_SysWork.playerCombatInfo_38.equippedWeapon_F].field_0, 0xF, Q12_SHIFT);
                                break;
                        }

                        Vw_CoordHierarchyMatrixCompute(&coord[10], &sp50);
                    }
                    break;
            }

            gte_SetRotMatrix(&sp50);
            gte_SetTransMatrix(&sp50);
            gte_ldv0(&sp90);
            gte_rt();
            gte_stlvnl(&sp70);

            temp_v0_5 = FP_FROM(g_SysWork.playerCombatInfo_38.field_0.vx, Q4_SHIFT) - sp70.vx;
            temp_v0_6 = FP_FROM(g_SysWork.playerCombatInfo_38.field_0.vz, Q4_SHIFT) - sp70.vz;
            temp_s0   = SquareRoot0(SQUARE(temp_v0_5) + SQUARE(temp_v0_6));

            sp98.vx = ratan2(sp70.vx - FP_FROM(g_SysWork.playerCombatInfo_38.field_0.vx, Q4_SHIFT),
                             sp70.vz - FP_FROM(g_SysWork.playerCombatInfo_38.field_0.vz, Q4_SHIFT));
            sp98.vy = ratan2(temp_s0, sp70.vy - FP_FROM(g_SysWork.playerCombatInfo_38.field_0.vy, Q4_SHIFT));
        }

        if (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_HyperBlaster &&
            g_SysWork.playerCombatInfo_38.isAiming_13 &&
            model->anim_4.animIdx_0 >= 57 &&
            model->anim_4.keyframeIdx0_8 >= 574)
        {
            if (g_SysWork.player_4C.extra_128.field_1C < 2)
            {
                if (g_SysWork.player_4C.extra_128.field_1C == 0 && g_SysWork.field_2353 != NO_VALUE)
                {
                    g_SysWork.field_2353 = NO_VALUE;
                }

                *(u32*)&sp90 = 0xFFD90000;
                sp90.vz      = 87;

                Vw_CoordHierarchyMatrixCompute(&coord[10], &sp50);
                gte_SetRotMatrix(&sp50);
                gte_SetTransMatrix(&sp50);
                gte_ldv0(&sp90);
                gte_rt();
                gte_stlvnl(&sp80);

                sp20.vx = sp80.vx * 16;
                sp20.vy = sp80.vy * 16;
                sp20.vz = sp80.vz * 16;

                if (g_GameWork.config_0.optExtraAutoAiming_2C != 0)
                {
                    sp98.vx = chara->rotation_24.pad;
                }

                g_MapOverlayHeader.func_178(&sp20.vx, &sp98.vx, &sp98.vy);
            }
        }

        if (g_SysWork.player_4C.extra_128.field_1C < 2)
        {
            if ((g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_Chainsaw &&
                 model->anim_4.keyframeIdx0_8 >= 572 &&
                 model->anim_4.keyframeIdx0_8 <  584) ||
                (g_SysWork.playerCombatInfo_38.equippedWeapon_F == EquippedWeaponId_RockDrill &&
                 chara->model_0.anim_4.keyframeIdx0_8 >= 577 &&
                 model->anim_4.keyframeIdx0_8         <  583))
            {
                *(u32*)&sp90 = 0;
                sp90.vz      = 0;

                Vw_CoordHierarchyMatrixCompute(&coord[10], &sp50);
                gte_SetRotMatrix(&sp50);
                gte_SetTransMatrix(&sp50);
                gte_ldv0(&sp90);
                gte_rt();
                gte_stlvnl(&sp80);

                *(u32*)&sp90 = 0;
                sp90.vz      = 0;
                sp30.vx      = sp80.vx * 16;
                sp30.vy      = sp80.vy * 16;
                sp30.vz      = sp80.vz * 16;

                Vw_CoordHierarchyMatrixCompute(&coord[6], &sp50);
                gte_SetRotMatrix(&sp50);
                gte_SetTransMatrix(&sp50);
                gte_ldv0(&sp90);
                gte_rt();
                gte_stlvnl(&sp80);

                sp40.vx = sp80.vx * 16;
                sp40.vy = sp80.vy * 16;
                sp40.vz = sp80.vz * 16;
                g_MapOverlayHeader.func_17C(&sp30.vx, &sp40.vx);
            }
        }

        if (g_SysWork.player_4C.extra_128.field_20 != 24)
        {
            if (g_SysWork.playerCombatInfo_38.equippedWeapon_F >= EquippedWeaponId_Handgun)
            {
                if (D_800C4554 != NO_VALUE || D_800C4556 != D_800C4554)
                {
                    func_8008A0E4(chara->field_44, g_SysWork.playerCombatInfo_38.equippedWeapon_F, chara, &D_800C44E0, g_SysWork.npcs_1A0, D_800C4556, D_800C4554);
                }
                else
                {
                    func_8008A0E4(chara->field_44, g_SysWork.playerCombatInfo_38.equippedWeapon_F, chara, &D_800C44E0, g_SysWork.npcs_1A0, sp98.vx, sp98.vy);
                }
            }
            else
            {
                func_8008A0E4(chara->field_44, g_SysWork.playerCombatInfo_38.equippedWeapon_F, chara, &g_SysWork.playerCombatInfo_38, g_SysWork.npcs_1A0, sp98.vx, sp98.vy);
            }

            D_800C42D2 = sp98.vx;
            D_800C42D0 = sp98.vy;
        }
    }

    D_800C44E0.field_0 = g_SysWork.playerCombatInfo_38.field_0;
}

void Game_SavegameResetPlayer() // 0x8007E530
{
    s32 i;

    g_SavegamePtr->inventoryItemSpaces_AB = 8;

    for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
    {
        g_SavegamePtr->items_0[i].id_0    = 0xFF;
        g_SavegamePtr->items_0[i].count_1 = 0;
    }

    g_SavegamePtr->playerHealth_240      = FP_FLOAT_TO(100.0f, Q12_SHIFT);
    g_SavegamePtr->field_A0              = 0;
    g_SavegamePtr->equippedWeapon_AA     = InventoryItemId_Unequipped;
    g_SavegamePtr->field_238             = 0;
    g_SavegamePtr->gameplayTimer_250     = 0;
    g_SavegamePtr->runDistance_254       = 0;
    g_SavegamePtr->walkDistance_258      = 0;
    g_SavegamePtr->pickedUpItemCount_23C = 0;
    g_SavegamePtr->clearGameCount_24A    = 0;
    g_SavegamePtr->add290Hours_25C_1     = 0;
}

void func_8007E5AC() // 0x8007E5AC
{
    s32      i;
    u32      temp_t0;
    s_Model* model;
    s_Model* extraModel;

    SysWork_SavegameReadPlayer();

    g_SysWork.player_4C.chara_0.model_0.charaId_0   = Chara_Hero;
    g_SysWork.player_4C.extra_128.model_0.charaId_0 = Chara_Hero;
    g_SysWork.player_4C.chara_0.field_D4            = 0x4CC;
    g_SysWork.player_4C.chara_0.field_D6            = 0x3AE;

    extraModel = &g_SysWork.player_4C.chara_0.model_0;
    model      = &g_SysWork.player_4C.extra_128.model_0;

    g_SysWork.field_2358 = 0;

    extraModel->anim_4.flags_2 |= AnimFlag_Unk1 | AnimFlag_Visible;
    model->anim_4.flags_2      |= AnimFlag_Unk1 | AnimFlag_Visible;

    g_SysWork.player_4C.chara_0.field_E0_8 = 3;
    g_Inventory_EquippedItem               = g_SavegamePtr->equippedWeapon_AA;

    temp_t0 = g_SavegamePtr->equippedWeapon_AA >> 5;

    if (temp_t0 >= 4 && temp_t0 < 6)
    {
        for (i = 0; g_SavegamePtr->items_0[i].id_0 != g_SavegamePtr->equippedWeapon_AA && i < INVENTORY_ITEM_COUNT_MAX; i++);

        g_SysWork.playerCombatInfo_38.equippedWeapon_F     = g_SavegamePtr->equippedWeapon_AA + InventoryItemId_KitchenKnife;
        g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10 = g_SavegamePtr->items_0[i].count_1;
        g_SysWork.playerCombatInfo_38.field_12             = i;

        if (temp_t0 == 4)
        {
            g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11 = 0;
        }
        else
        {
            for (i = 0; g_SavegamePtr->items_0[i].id_0 != (g_SavegamePtr->equippedWeapon_AA + InventoryItemId_HealthDrink) && i < INVENTORY_ITEM_COUNT_MAX; i++);

            if (i == INVENTORY_ITEM_COUNT_MAX)
            {
                g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11 = 0;
            }
            else
            {
                g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11 = (s8)g_SavegamePtr->items_0[i].count_1;
            }
        }
    }
    else
    {
        g_SysWork.playerCombatInfo_38.equippedWeapon_F     = NO_VALUE;
        g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10 = 0;
        g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11   = 0;
        g_SysWork.playerCombatInfo_38.field_12             = NO_VALUE;
    }

    g_SysWork.playerCombatInfo_38.isAiming_13 = false;
    D_800AF20C                                = 0;
    D_800C4588                                = 0;
    D_800C457C                                = 0;
    g_Player_DisableControl                   = false;

    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case GameDifficulty_Easy:
            D_800C45EC = FP_FLOAT_TO(5.0f, Q12_SHIFT);
            break;

        case GameDifficulty_Normal:
            D_800C45EC = FP_FLOAT_TO(2.5f, Q12_SHIFT);
            break;

        case GameDifficulty_Hard:
            D_800C45EC = FP_FLOAT_TO(1.8f, Q12_SHIFT);
            break;
    }

    D_800AF224                = NO_VALUE;
    g_GameWork.mapAnimIdx_5B1 = NO_VALUE;

    g_SavegamePtr->inventoryItemSpaces_AB = CLAMP(g_SavegamePtr->inventoryItemSpaces_AB, INVENTORY_ITEM_COUNT_MAX / 5, INVENTORY_ITEM_COUNT_MAX);
    g_SysWork.player_4C.chara_0.health_B0 = CLAMP(g_SysWork.player_4C.chara_0.health_B0, 1, FP_FLOAT_TO(100.0f, Q12_SHIFT));
}

void func_8007E860() // 0x8007E860
{
    s32 i;
    s32 startIdx;

    for (i = 0; i < 8; i++)
    {
        startIdx                         = 92;
        g_MaybePlayerAnims[startIdx + i] = g_MapOverlayHeader.animInfo_34[i + 16];
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8007E8C0); // 0x8007E8C0

void func_8007E9C4() // 0x8007E9C4
{
    s_SubCharacter* chara;

    chara = &g_SysWork.player_4C.chara_0;

    g_Player_IsInWalkToRunTransition                  = false;
    g_SysWork.player_4C.extra_128.field_1C            = 0;
    g_SysWork.player_4C.extra_128.field_20            = 0;
    g_SysWork.player_4C.extra_128.field_24            = 0;
    g_SysWork.player_4C.extra_128.model_0.stateStep_3 = 0;
    g_SysWork.player_4C.extra_128.model_0.state_2     = 0;

    chara->model_0.stateStep_3                = 0;
    chara->model_0.state_2                    = 0;
    g_SysWork.field_235A                      = 0;
    D_800AF210                                = 0;
    D_800AF212                                = 0;
    D_800C4560                                = NO_VALUE;
    g_SysWork.playerCombatInfo_38.isAiming_13 = false;

    func_8004C564(0, NO_VALUE);

    chara->rotation_24.pad = FP_ANGLE(90.0f);
    D_800C4561             = 0;
    g_Player_DisableDamage = false;
    D_800C455C             = 0;
    D_800C4558             = 0;
    D_800C45C0             = 0;
    D_800C45BE             = 0;

    chara->properties_E4.player.properties_E4[1]               = 0;
    chara->properties_E4.player.properties_E4[4]               = 0;
    chara->properties_E4.player.properties_E4[5]               = 0;
    chara->properties_E4.player.properties_E4[7]               = 0;
    chara->properties_E4.player.properties_E4[8]               = 0;
    chara->properties_E4.player.properties_E4[9]               = 0;
    chara->properties_E4.larvalStalker.properties_E8[10].val32 = 0;
    chara->properties_E4.player.flags_11C                      = 0;
    chara->properties_E4.player.field_126                      = 0;

    chara->damageReceived_C0 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
    chara->field_BC          = 0;
    chara->field_B8          = 0;
    chara->field_B4          = 0;

    D_800C45BC           = 0;
    chara->flags_3E     &= ~(1 << 3);
    D_800C45F8           = chara->position_18;
    g_SysWork.field_2353 = NO_VALUE;
    chara->field_40      = NO_VALUE;
    chara->field_41      = NO_VALUE;

    g_SysWork.field_2354[3] = NO_VALUE;
    g_SysWork.field_2354[2] = NO_VALUE;
    g_SysWork.field_2354[1] = NO_VALUE;
    g_SysWork.field_2354[0] = NO_VALUE;
    chara->field_D6         = 0x3AE;

    D_800C457E = 0;
    D_800C4604 = 0;
    D_800C45F0 = 0;
    D_800C45E8 = 0;
    D_800C4582 = 0;
    D_800C45AE = 0;
    D_800C4586 = 0;
    D_800C4580 = 0;
    D_800C45AC = 0;
    D_800C4584 = 0;
}

void GameFs_PlayerMapAnimLoad(s32 mapIdx) // 0x8007EB64
{
    #define BASE_FILE_IDX FILE_ANIM_HB_M0S00_ANM

    if (g_GameWork.mapAnimIdx_5B1 != mapIdx ||
        mapIdx == (FILE_ANIM_HB_M6S04_ANM - BASE_FILE_IDX) ||
        mapIdx == (FILE_ANIM_HB_M7S01_ANM - BASE_FILE_IDX) ||
        mapIdx == (FILE_ANIM_HB_M7S02_ANM - BASE_FILE_IDX))
    {
        g_GameWork.mapAnimIdx_5B1 = mapIdx;
        Fs_QueueStartRead(BASE_FILE_IDX + mapIdx, FS_BUFFER_4);
    }
}

void func_8007EBBC() // 0x8007EBBC
{
    s32 var_a1;
    s32 var_a2;
    s32 i;
    s8  temp_v1;

    var_a1 = 0;
    var_a2 = 0;

    g_SysWork.field_2353 = NO_VALUE;
    temp_v1              = g_SysWork.playerCombatInfo_38.equippedWeapon_F + 1;

    switch (temp_v1)
    {
        case 0:
            D_800C4570 = D_800AFBF4[0];
            return;

        case 1:
            var_a1                               = 30;
            var_a2                               = 15;
            D_800C4570                           = D_800AFBF4[1];
            g_SysWork.player_4C.chara_0.field_D0 = -0x1030;
            break;

        default:
            return;

        case 8:
            var_a1                               = 0;
            var_a2                               = 0;
            D_800C4570                           = D_800AFBF4[3];
            g_SysWork.player_4C.chara_0.field_D0 = -0xFD0;
            break;

        case 2:
        case 5:
            D_800C4570 = D_800AFBF4[2];
            switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
            {
                case EquippedWeaponId_Hammer:
                    var_a1 = 10;
                    var_a2 = 5;
                    break;

                case EquippedWeaponId_SteelPipe:
                    var_a1 = 20;
                    var_a2 = 10;
                    break;
            }

            g_SysWork.player_4C.chara_0.field_D0 = -0xEC0;
            break;

        case 6:
            var_a1                               = 50;
            var_a2                               = 25;
            D_800C4570                           = D_800AFBF4[4];
            g_SysWork.player_4C.chara_0.field_D0 = -0xE90;
            break;

        case 3:
            var_a1                               = 64;
            var_a2                               = 32;
            D_800C4570                           = D_800AFBF4[5];
            g_SysWork.player_4C.chara_0.field_D0 = -0x12E0;
            break;

        case 7:
            var_a1                               = 40;
            var_a2                               = 20;
            D_800C4570                           = D_800AFBF4[10];
            g_SysWork.player_4C.chara_0.field_D0 = -0xF20;
            break;

        case 33:
            var_a1                               = 78;
            var_a2                               = 39;
            D_800C4570                           = D_800AFBF4[6];
            g_SysWork.player_4C.chara_0.field_D0 = -0x1600;
            break;

        case 34:
            var_a1                               = 96;
            var_a2                               = 48;
            D_800C4570                           = D_800AFBF4[7];
            g_SysWork.player_4C.chara_0.field_D0 = -0x1180;
            break;

        case 35:
            var_a1                               = 114;
            var_a2                               = 57;
            D_800C4570                           = D_800AFBF4[8];
            g_SysWork.player_4C.chara_0.field_D0 = -0x1600;
            break;

        case 36:
            var_a1                               = 132;
            var_a2                               = 66;
            D_800C4570                           = D_800AFBF4[9];
            g_SysWork.player_4C.chara_0.field_D0 = -0x1610;
            break;
    }

    for (i = 56; i < 76; i++)
    {
        g_MaybePlayerAnims[i] = D_80028B94[(i - 56) + var_a1];
    }

    for (i = 0; i < 10; i++)
    {
        D_800C44F0[i] = D_800294F4[i + var_a2];
    }

    if (g_SysWork.playerCombatInfo_38.equippedWeapon_F != NO_VALUE && D_800AF224 != g_SysWork.playerCombatInfo_38.equippedWeapon_F)
    {
        D_800AF224 = g_SysWork.playerCombatInfo_38.equippedWeapon_F;
        func_8007F14C(g_SysWork.playerCombatInfo_38.equippedWeapon_F);

        switch (g_SysWork.playerCombatInfo_38.equippedWeapon_F)
        {
            case 0:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP3_ANM, FS_BUFFER_12);
                break;

            case 7:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP1_ANM, FS_BUFFER_12);
                break;

            case 1:
            case 4:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP2_ANM, FS_BUFFER_12);
                break;

            case 5:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP6_ANM, FS_BUFFER_12);
                break;

            case 2:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP8_ANM, FS_BUFFER_12);
                break;

            case 6:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP9_ANM, FS_BUFFER_12);
                break;

            case 32:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP4_ANM, FS_BUFFER_12);
                break;

            case 33:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP51_ANM, FS_BUFFER_12);
                break;

            case 34:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP52_ANM, FS_BUFFER_12);
                break;

            case 35:
                Fs_QueueStartRead(FILE_ANIM_HB_WEP53_ANM, FS_BUFFER_12);
                break;
        }
    }
}

// TODO: .rodata migration.
#ifdef NON_MATCHING
void func_8007F14C(u8 arg0) // 0x8007F14C
{
    switch (arg0)
    {
        case 0:
        case 1:
        case 4:
        case 6:
        case 7:
            Sd_EngineCmd(164);
            break;

        case 5:
            Sd_EngineCmd(169);
            break;

        case 2:
            Sd_EngineCmd(163);
            break;

        case 32:
            Sd_EngineCmd(166);
            break;

        case 33:
            Sd_EngineCmd(167);
            break;

        case 34:
            Sd_EngineCmd(168);
            break;

        case 35:
            Sd_EngineCmd(165);
            break;
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8007F14C); // 0x8007F14C
#endif

void func_8007F1CC() // 0x8007F1CC
{
    D_800C455C                       = 0;
    D_800C4558                       = 0;
    D_800C45C0                       = 0;
    D_800C45BE                       = 0;
    D_800C45BC                       = 0;
    D_800C457E                       = 0;
    D_800C4604                       = 0;
    D_800C45F0                       = 0;
    D_800C45E8                       = 0;
    D_800C4582                       = 0;
    D_800C45AE                       = 0;
    D_800C4586                       = 0;
    D_800C4580                       = 0;
    D_800C45AC                       = 0;
    D_800C4584                       = 0;
    g_Player_IsInWalkToRunTransition = false;
}

void func_8007F250(u8* ptr, s8 disableDamage) // 0x8007F250
{
    *ptr                   = D_800C4561;
    g_Player_DisableDamage = disableDamage;
}

bool func_8007F26C() // 0x8007F26C
{
    if (g_SysWork.player_4C.extra_128.field_20 == 25 ||
        g_SysWork.player_4C.extra_128.field_1C == 5 ||
        g_SysWork.player_4C.extra_128.field_1C == 6)
    {
        return true;
    }

    return false;
}

bool func_8007F2AC() // 0x8007F2AC
{
    if (g_SysWork.player_4C.chara_0.health_B0 <= 0 ||
        g_SysWork.playerCombatInfo_38.isAiming_13 ||
        g_SysWork.player_4C.extra_128.field_1C == 5 ||
        g_SysWork.player_4C.extra_128.field_1C == 6 ||
        (g_SysWork.player_4C.extra_128.field_1C >= 7 &&
         g_SysWork.player_4C.extra_128.field_1C <= 50))
    {
        return true;
    }

    return false;
}

s16 Player_AnimGetSomething() // 0x8007F308
{
    return g_MaybePlayerAnims[g_SysWork.player_4C.chara_0.model_0.anim_4.animIdx_0].keyframeIdx0_C;
}

// Large function. Something to do with player control.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8007F32C); // 0x8007F32C

bool func_8007F95C() // 0x8007F95C
{
    VECTOR3         pos0;
    VECTOR3         pos1;
    u16             sp30;
    s32             i;
    s_SubCharacter* ptr0;
    s_SubCharacter* ptr1;
    u16             temp;
    s32             radius;

    if (g_Player_IsInWalkToRunTransition)
    {
        return false;
    }

    pos0.vx = g_SysWork.player_4C.chara_0.position_18.vx;
    pos0.vy = g_SysWork.player_4C.chara_0.position_18.vy;
    pos0.vz = g_SysWork.player_4C.chara_0.position_18.vz;

    if (!g_SysWork.playerCombatInfo_38.isAiming_13 || g_SysWork.playerCombatInfo_38.equippedWeapon_F < EquippedWeaponId_Handgun)
    {
        for (i = 0, ptr1 = g_SysWork.npcs_1A0, ptr0 = g_SysWork.npcs_1A0; i < 6; i++, ptr1++, ptr0++)
        {
            if (ptr0->model_0.charaId_0 != Chara_None)
            {
                if (ptr0->model_0.charaId_0 != Chara_AirScreamer &&
                    ptr0->model_0.charaId_0 != Chara_NightFlutter)
                {
                    if (ptr0->model_0.charaId_0 == Chara_Creaper)
                    {
                        radius = FP_METER(0.65f);
                    }
                    else
                    {
                        radius = FP_METER(0.85f);
                    }
                }
                else
                {
                    radius = FP_METER(1.2f);
                }

                pos1.vx = ptr1->position_18.vx + ptr1->field_D8.field_0;
                pos1.vy = ptr1->position_18.vy;
                pos1.vz = ptr1->position_18.vz + ptr1->field_D8.field_2;

                if (!Math_Distance2dCheck(&pos0, &pos1, radius) && ABS(pos1.vy - pos0.vy) < FP_METER(0.3f) &&
                    ptr1->health_B0 > FP_FLOAT_TO(0.0f, Q12_SHIFT) && (ptr1->flags_3E & (1 << 1)))
                {
                    func_8007FB34(g_SysWork.player_4C.chara_0.rotation_24.vy, (ratan2(pos1.vx - pos0.vx, pos1.vz - pos0.vz) + FP_ANGLE(360.0f)) & 0xFFF, &sp30);

                    temp = sp30 + 0x3FF;
                    if (temp < 0x8FF)
                    {
                        g_SysWork.field_2353 = i;
                        return true;
                    }
                }
            }
        }
    }

    g_SysWork.field_2353 = NO_VALUE;
    return false;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8007FB34); // 0x8007FB34

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8007FB94); // 0x8007FB94

// Similar to above.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8007FC48); // 0x8007FC48

s32 func_8007FD2C() // 0x8007FD2C
{
    return g_SysWork.player_4C.chara_0.properties_E4.player.properties_E4[PlayerProperty_Unk8];
}

s32 func_8007FD3C() // 0x8007FD3C
{
    return g_SysWork.player_4C.chara_0.properties_E4.player.field_114;
}

void func_8007FD4C(s32 arg0) // 0x8007FD4C
{
    s32             i;
    s_SubCharacter* chara;

    chara = &g_SysWork.player_4C.chara_0;

    D_800AF20C      = 0;
    chara->field_40 = NO_VALUE;

    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk14;

    for (i = 0; i < 4; i++)
    {
        g_SysWork.field_2354[i] = NO_VALUE;
    }

    if (arg0 != 0) 
    {
        g_SysWork.player_4C.chara_0.field_D4         = 0x4CC;
        g_SysWork.player_4C.chara_0.field_D6         = 0x3AE;
        g_SysWork.player_4C.chara_0.field_C8         = FP_FLOAT_TO(-1.6f, Q12_SHIFT);
        g_SysWork.player_4C.chara_0.field_D8.field_6 = 0;
        g_SysWork.player_4C.chara_0.field_D8.field_4 = 0;
        g_SysWork.player_4C.chara_0.field_D8.field_2 = 0;
        g_SysWork.player_4C.chara_0.field_D8.field_0 = 0;
        g_SysWork.player_4C.chara_0.field_CA         = 0;
        g_SysWork.player_4C.chara_0.field_CE         = FP_FLOAT_TO(-1.1f, Q12_SHIFT);
    }
}

// Large function.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_8007FDE0); // 0x8007FDE0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800802CC); // 0x800802CC

s32 Math_Distance2d(VECTOR3* pos0, VECTOR3* pos1) // 0x8008037C
{
    s32 xDelta = pos1->vx - pos0->vx;
    s32 zDelta = pos1->vz - pos0->vz;
    return SquareRoot12(FP_MULTIPLY_PRECISE(xDelta, xDelta, Q12_SHIFT) + FP_MULTIPLY_PRECISE(zDelta, zDelta, Q12_SHIFT));
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_800803FC); // 0x800803FC

void func_80080458() // 0x80080458
{
    g_Controller1->btnsClicked_10 |= ControllerFlag_Select;
}

s32 func_80080478(VECTOR3* pos0, VECTOR3* pos1) // 0x80080478
{
    s32 x0;
    s32 x1;
    s32 y1;
    s32 y0;
    s32 z0;
    s32 z1;
    s32 xDelta;
    s32 zDelta;
    u16 atan2Delta;
    s32 unk;

    x0 = pos0->vx;
    x1 = pos1->vx;
    y0 = pos0->vy;
    y1 = pos1->vy;
    z0 = pos0->vz;
    z1 = pos1->vz;

    xDelta     = x1 - x0;
    zDelta     = z1 - z0;
    atan2Delta = ratan2(xDelta, zDelta);

    unk = func_8008A058(func_80080540(xDelta, 0, zDelta));
    return (ratan2(unk, y1 - y0) << 16) | atan2Delta;
}

s32 func_80080514() // 0x80080514
{
    s32 rand16;

    rand16 = Rng_Rand16();
    return (((rand16 * 2) ^ rand16) >> 3) & 0xFFF;
}

// TODO: Try decomping by hand. -- Sezz
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80054FC0", func_80080540); // 0x80080540

s32 Math_PreservedSignSubtract(s32 val, s32 subtractor) // 0x80080594
{
    s32 signBit;
    s32 absDiff;

    signBit = val >> 31;  
    absDiff = ((val ^ signBit) - signBit) - subtractor;  
    return ((absDiff & ~(absDiff >> 31)) ^ signBit) - signBit; 
}

void func_800805BC(VECTOR3* pos, SVECTOR* rot, GsCOORDINATE2* rootCoord, s32 arg3) // 0x800805BC
{
    MATRIX mat;
    VECTOR vec;

    Vw_CoordHierarchyMatrixCompute(rootCoord, &mat);
    gte_SetRotMatrix(&mat);
    gte_SetTransMatrix(&mat);

    while (arg3 > 0)
    {
        gte_ldv0(rot);
        gte_rt();
        gte_stlvnl(&vec);

        pos->vx = vec.vx * 16;
        pos->vy = vec.vy * 16;
        pos->vz = vec.vz * 16;

        arg3--;
        rot++;
        pos++;
    }
}

u32 func_800806AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x800806AC
{
    u32 res;

    res = arg0 != 0;
    if (res == 0)
    {
        return res;
    }

    res = ~arg0 == 0;
    if (res != 0)
    {
        return res;
    }

    func_800699F8(&D_800C4620, arg1, arg3);

    res = arg2 < D_800C4620.field_0;
    if (res != 0)
    {
        res = ~D_800C4620.field_8 != 0;
        if (res != 0)
        {
            res = (arg0 & (1 << D_800C4620.field_8));
            return res > 0u; 
        }
    }

    return res;
}

void func_8008074C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x8008074C
{
    func_800806AC(arg0, arg1, 1 << 31, arg3);
}

void func_8008076C(s32 posX, s32 posZ) // 0x8008076C
{
    s32              groundHeight;
    s32              caseVar;
    s32              x;
    s32              z;
    s_func_800699F8* coll;

    coll = &D_800AFC78.field_C;

    x = D_800AFC78.position_0.vx;
    z = D_800AFC78.position_0.vz;
    if (D_800AFC78.field_18 != NO_VALUE && x == posX && z == posZ)
    {
        return;
    }

    func_800699F8(coll, posX, posZ);
    D_800AFC78.position_0.vx = posX;
    D_800AFC78.position_0.vz = posZ;

    caseVar = coll->field_8;
    switch (coll->field_8)
    {
        case 0:
            groundHeight = FP_METER(8.0f);
            switch (g_SavegamePtr->mapOverlayId_A4)
            {
                case MapOverlayId_MAP5_S01:
                    if (posZ <= 0)
                    {
                        groundHeight = FP_METER(4.0f);
                        caseVar      = 7;
                    }
                    break;

                case MapOverlayId_MAP6_S00:
                    groundHeight = FP_METER(4.0f);
                    caseVar      = 7;
                    break;
            }
            break;

        case 12:
            groundHeight = FP_METER(8.0f);
            switch (g_SavegamePtr->mapOverlayId_A4)
            {
                case MapOverlayId_MAP6_S00:
                    groundHeight = FP_METER(4.0f);
                    caseVar      = 7;
                    break;
            }
            break;

        default:
            groundHeight = coll->groundHeight_0;
            break;
    }
    
    D_800AFC78.position_0.vy = groundHeight;
    D_800AFC78.field_18      = caseVar;
}

s32 func_80080884(s32 posX, s32 posZ) // 0x80080884
{
    func_8008076C(posX, posZ);
    return D_800AFC78.position_0.vy;
}

s32 func_800808AC(s32 posX, s32 posZ) // 0x800808AC
{
    func_8008076C(posX, posZ);
    return D_800AFC78.field_18;
}

s32 Math_MulFixed(s32 val0, s32 val1, s32 shift) // 0x800808D4
{
    u32 lo;

    // Use inline asm to fetch high/low parts of mult.
    // Only method found to allow C to keep same insn/reg order so far.
    __asm__ volatile(
        "mult %0, %1\n" // Multiply `val0` and `val1`.
        "mfhi %0\n"     // Move high result back into `val0`?
        "mflo %2\n"     // Move low result to lo.
        : "=r"(val0), "=r"(val1), "=r"(lo)
        : "0"(val0), "1"(val1));

#if 0
    // Equivalent C version of above (non-matching).
    s64 res = (s64)val0 * (s64)val1;
    val0    = (u32)(res >> 32);
    lo      = (u32)res;
#endif

    return (val0 << (32 - shift)) | (lo >> shift);
}

s32 Math_GetMagnitudeShift(s32 mag) // 0x800808F8
{
    #define THRESHOLD_0 (1 << 14)
    #define THRESHOLD_1 ((1 << 18) - 1)
    #define THRESHOLD_2 ((1 << 22) - 1)

    s32 shift;

    if (mag < THRESHOLD_0)
    {
        return 0;
    }

    if (mag > THRESHOLD_1)
    {
        if (mag > THRESHOLD_2)
        {
            return Q12_SHIFT;
        }

        shift = Q8_SHIFT;
        return shift;
    }

    shift = Q4_SHIFT;
    return shift;
}
