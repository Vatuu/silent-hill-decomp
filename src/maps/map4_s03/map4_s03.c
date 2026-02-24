#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map4/map4_s03.h"
#include "maps/particle.h"
#include "maps/characters/player.h"
#include "maps/characters/twinfeeler.h"

#include "maps/shared/sharedFunc_800CB0A4_4_s03.h" // 0x800CB0A4

#include "maps/shared/sharedFunc_800CB1B0_4_s03.h" // 0x800CB1B0

#include "maps/shared/sharedFunc_800CBE54_4_s03.h" // 0x800CBE54

#include "maps/shared/sharedFunc_800CC004_4_s03.h" // 0x800CC004

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

#include "maps/shared/sharedFunc_800CD6B0_3_s03.h" // 0x800D04BC

#include "maps/shared/sharedFunc_800CD7F8_3_s03.h" // 0x800D0604

#include "maps/shared/sharedFunc_800CD920_3_s03.h" // 0x800D072C

#include "maps/shared/sharedFunc_800CD940_3_s03.h" // 0x800D074C

void func_800D078C(void) // 0x800D078C
{
    u32        tpage1;
    u16        x;
    u16        y;
    s_Texture* tex;

    tex    = Texture_InfoGet("SPUM602F");
    tpage1 = tex->imageDesc_0.tPage[1];
    x      = tex->imageDesc_0.clutX;
    y      = tex->imageDesc_0.clutY;

    D_800DF554 = tpage1;
    D_800DF558 = tpage1 | 0x20;
    D_800DF55C = tpage1 | 0x40;

    D_800DF560 = getClut(x, y + 1);
    D_800DF564 = getClut(x, y + 14);
    D_800DF568 = getClut(x, y + 15);
    D_800DF56C = getClut(x, y + 13);
    D_800DF570 = x >> 4;
}

void func_800D0840(void) // 0x800D0840
{
    RECT sp10;
    s32  temp_s0;
    s32  temp_s2;
    s32  temp_s3;
    s32  temp_t0;
    s32  var_a0;
    s32  var_a1_5;
    s32  var_a2;
    s32  i;
    s32  var_v1;
    s32  var_s6;
    u16* ptr0;
    u16* ptr1;
    u16* ptr2;

    var_s6 = 7;

    sp10.x = D_800DF570 * 16;
    sp10.y = 1;
    sp10.w = 16;
    sp10.h = 1;

    ptr0 = &D_800DB980;

    StoreImage(&sp10, ptr0);
    DrawSync(0);

    temp_t0 = D_800DB980[7];

    temp_s3 = (temp_t0 & 0x1F);
    temp_s2 = ((temp_t0 >> 5) & 0x1F);
    temp_s0 = ((temp_t0 >> 10) & 0x1F);

    temp_s3 += D_800DAA4C;
    temp_s2 += D_800DAA50;
    temp_s0 += D_800DAA54;

    ptr2 = &ptr0[16];
    ptr1 = &ptr0[32];

    Gfx_DebugStringPosition(160, 92);

    for (i = 0; i < var_s6; i++)
    {
        ptr2[i] = 0;

        temp_t0 = ptr0[i];

        var_a2 = temp_t0 & 0x1F;
        var_a0 = (temp_t0 >> 5) & 0x1F;
        var_v1 = (temp_t0 >> 10) & 0x1F;

        var_a2 = temp_s3 - var_a2;
        var_a2 = MAX((var_a2 * D_800DAA44) >> 7, 0);
        var_a2 = CLAMP_HIGH(var_a2, 0x1F);

        var_a0 = temp_s2 - var_a0;
        var_a0 = MAX((var_a0 * D_800DAA44) >> 7, 0);
        var_a0 = CLAMP_HIGH(var_a0, 0x1F);

        var_v1 = temp_s0 - var_v1;
        var_v1 = MAX((var_v1 * D_800DAA44) >> 7, 0);
        var_v1 = CLAMP_HIGH(var_v1, 0x1F);

        if (temp_t0 != 0)
        {
            ptr1[i] = var_a2 | (var_a0 << 5) | (var_v1 << 10) | 0x8000;
        }
        else
        {
            ptr1[i] = 0;
        }
    }

    for (; i < 16; i++)
    {
        temp_t0 = ptr0[i];

        var_a2 = temp_t0 & 0x1F;
        var_a0 = (temp_t0 >> 5) & 0x1F;
        var_v1 = (temp_t0 >> 10) & 0x1F;

        var_a2 = var_a2 - temp_s3;
        var_a2 = MAX((var_a2 * D_800DAA48) >> 7, 0);
        var_a2 = CLAMP_HIGH(var_a2, 0x1F);

        var_a0 = var_a0 - temp_s2;
        var_a0 = MAX((var_a0 * D_800DAA48) >> 7, 0);
        var_a0 = CLAMP_HIGH(var_a0, 0x1F);

        var_v1 = var_v1 - temp_s0;
        var_v1 = MAX((var_v1 * D_800DAA48) >> 7, 0);
        var_v1 = CLAMP_HIGH(var_v1, 0x1F);

        if (temp_t0 != 0)
        {
            ptr2[i] = var_a2 | (var_a0 << 5) | (var_v1 << 10) | 0x8000;
        }
        else
        {
            ptr2[i] = 0;
        }

        ptr1[i] = 0;
    }

    sp10.y = 14;
    sp10.h = 2;

    LoadImage(&sp10, &D_800DB980[16]);
    DrawSync(0);

    D_800DB980[0] = 0;

    ptr0 = &D_800DB980[1];

    for (i = 1; i < 16; i++, ptr0++)
    {
        var_a2 = i * 2;
        var_a2 = Q12_MULT_PRECISE(var_a2, Q12(0.4f));

        var_a2 = MAX(var_a2, 0);
        var_a2 = CLAMP_HIGH(var_a2, 0x1F);

        temp_t0 = Q12_MULT_PRECISE(i * 2, Q12(0.35f));

        var_a1_5 = MAX(temp_t0, 0);
        var_a1_5 = CLAMP_HIGH(var_a1_5, 0x1F);

        var_a0 = MAX(temp_t0, 0);
        var_a0 = CLAMP_HIGH(var_a0, 0x1F);

        *ptr0 = (var_a1_5 << 5) | (var_a0 << 10) | var_a2 | ~0x7FFF;
    }

    sp10.y = 13;
    sp10.h = 1;

    LoadImage(&sp10, &D_800DB980);
    DrawSync(0);
}

void func_800D0C50(SVECTOR* rot, MATRIX* mat) // 0x800D0C50
{
    MATRIX outMat;

    SetRotMatrix(mat);
    SetTransMatrix(mat);
    Math_RotMatrixXyz(rot, &outMat);
    SetMulRotMatrix(&outMat);
}

void func_800D0CA0(q19_12 rotY, SVECTOR* pos) // 0x800D0CA0
{
    MATRIX      mat;
    VECTOR      trans;
    SVECTOR     rot; // Q3.12
    s_800E0988* ptr;

    ptr = &D_800E0988;

    SetRotMatrix(&ptr->world_8);
    SetTransMatrix(&ptr->world_8);

    ApplyRotMatrix(pos, &trans);

    trans.vx += ptr->world_8.t[0];
    trans.vy += ptr->world_8.t[1];
    trans.vz += ptr->world_8.t[2];

    TransMatrix(&mat, &trans);
    SetTransMatrix(&mat);

    rot.vx = Q12_ANGLE(0.0f);
    rot.vy = rotY;
    rot.vz = Q12_ANGLE(0.0f);
    Math_RotMatrixZxyNeg(&rot, &mat);
    SetMulRotMatrix(&mat);
}

void func_800D0D6C(MATRIX* out, SVECTOR* pos, s32 rotY) // 0x800D0D6C
{
    SVECTOR     rot; // Q3.12
    s_800E0988* ptr;

    ptr = &D_800E0988;

    rot.vx = Q12_ANGLE(0.0f);
    rot.vy = rotY;
    rot.vz = Q12_ANGLE(0.0f);
    Math_RotMatrixXyz(&rot, out);

    out->t[0] = Q12_TO_Q8(ptr->x_0) + pos->vx;
    out->t[1] = Q12_TO_Q8(Q12(0.0f));
    out->t[2] = Q12_TO_Q8(ptr->z_4) + pos->vz;
}

void func_800D0DE4(SVECTOR* out, VECTOR* in, q19_12 headingAngle, q19_12 dist) // 0x800D0DE4
{
    q19_12 offsetX;
    q19_12 offsetZ;
    s32    x;
    s32    z;

    offsetX = Q12_MULT_PRECISE(Math_Sin(headingAngle), dist);
    offsetZ = Q12_MULT_PRECISE(Math_Cos(headingAngle), dist);

    x = in->vx - D_800E0988[0].x_0;
    z = in->vz - D_800E0988[0].z_4;

    out->vx = Q12_TO_Q8(x + offsetX);
    out->vy = Q12_TO_Q8(in->vy);
    out->vz = Q12_TO_Q8(z + offsetZ);
}

void func_800D0EC0(u8* buf, s32 w, s32 h) // 0x800D0EC0
{
    s32 i, j;
    s32 sum;

    for (i = 0; i < h - 1; i++)
    {
        for (j = 0; j < w; j++)
        {
            sum   = buf[w + j];
            sum  += buf[j - 1];
            sum  += buf[j];
            sum  += buf[j + 1];
            sum >>= 2;

            if (sum <= 0)
            {
                buf[j] = 0;
            }
            else
            {
                buf[j] = sum;
            }
        }

        buf += w;
    }
}

s32 func_800D0F40(s32 arg0, s32 arg1, s32 arg2) // 0x800D0F40
{
    s32 index;

    index = (arg0 * arg1) >> 8;
    if (index != 0 && g_DeltaTime != 0)
    {
        index += Rng_GenerateUInt(-2, 1);
        // TODO: `CLAMP` doesn't match?
        index = MIN(255, index);
        index = MAX(index, 0);
    }

    // @hack Needed to match weird a2 usage.
    if (arg2)
    {
        arg2++;
        arg2--;
    }

    return D_800DAA58[index];
}

void func_800D0FD4(s32* ord, void* arg1, u8* arg2, MATRIX* arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 abr) // 0x800D0FD4
{
    SVECTOR   vtx = { 0 };
    s32       sxy;
    s32       w;
    s32       h;
    s32       x;
    s32       y;
    s32       xbase;
    s32       ybase;
    s32       p;
    s32       flag;
    s32       col;
    s32*      ot;
    s32       depth;
    s16       sxy_l;
    s16       sxy_h;
    s32       sz;
    s32       i;
    s32       j;
    s32       col0;
    s32       col1;
    s32       col2;
    s32       col3;
    PACKET*   packet;
    DR_TPAGE* tpage;
    POLY_G4*  poly;
    u8*       ptr0;
    u8*       ptr1;

    col = D_800DAA58[0];
    sz  = RotTransPers(&vtx, &sxy, &p, &flag);

    // Divide overflow.
    if (flag & 0x20000)
    {
        return;
    }

    packet = GsOUT_PACKET_P;
    ot  = &ord[sz >> 1];

    sxy_l = sxy;
    sxy_h = sxy >> 16;
    depth = ReadGeomScreen();

    w = (depth * 8) / sz + 1;
    h = (depth * 12) / sz + 1;

    xbase = sxy_l - (arg5 / 2) * w;
    ybase = sxy_h - arg6 * h;

    for (i = 1; i < arg6 + 1; i++)
    {
        col3 = col;
        col1 = col3;

        ptr0 = arg2 + ((i - 1) * arg7);
        ptr0 = ptr0 + 1;
        ptr1 = arg2 + (i * arg7);
        ptr1 = ptr1 + 1;

        y = ((i - 1) * h) + ybase;

        for (j = 1; j < arg5 + 1; j++)
        {
            poly = packet;

            col0 = col1;
            col2 = col3;

            if (j == arg5)
            {
                col3 = col;
                col1 = col3;
            }
            else
            {
                col1 = func_800D0F40(*ptr0, arg4, abr);

                if (i == arg6)
                {
                    col3 = col;
                }
                else
                {
                    col3 = func_800D0F40(*ptr1, arg4, abr);
                }
            }

            if (col0 != col || col1 != col0 || col2 != col1 || col3 != col2)
            {
                x = (j - 1) * w + xbase;
                setXYWH(poly, x, y, w, h);

                *(s32*)&poly->r0 = col0;
                *(s32*)&poly->r1 = col1;
                *(s32*)&poly->r2 = col2;
                *(s32*)&poly->r3 = col3;

                setPolyG4(poly);
                setSemiTrans(poly, 1);
                addPrim(ot, packet);
            }

            packet += sizeof(POLY_G4);
            ptr0++;
            ptr1++;
        }
    }

    tpage = packet;

    setDrawTPage(tpage, 0, 1, getTPage(0, abr, 320, 0));
    addPrim(ot, tpage);
    packet           += sizeof(DR_TPAGE);
    GsOUT_PACKET_P = packet;
}

void func_800D13B4(u8* arg0, s32 arg1, s32 arg2, s32 arg3) // 0x800D13B4
{
    u8* buf;
    s32 i;
    s32 rnd;
    s32 index;

    buf = arg0 + (arg1 * (arg2 - 1));
    memset(buf, 0, arg1);

    if (arg3 > Q12(0.75f))
    {
        for (i = 0; i < 3; i++)
        {
            if (Rng_Rand16() & 0x70)
            {
                rnd            = Rng_Rand16() >> 2;
                index          = (rnd % (arg1 / 4)) + (arg1 / 4);
                buf[index + 1] = 0xff;
            }
        }
    }
}

void func_800D1478(SVECTOR* arg0, s32 arg1, q19_12 headingAgle, s32 mode, SVECTOR* arg4) // 0x800D1478
{
    s32    x;
    s32    y;
    s32    z;
    q19_12 dist;
    q19_12 angleStep;

    x = 0;
    y = 0;
    z = 0;

    switch (mode)
    {
        case 0:
        case 1:
            dist = (arg1 > Q12(0.75f)) ? 128 : 76;
            angleStep  = mode ? Q12_ANGLE(-90.0f) : Q12_ANGLE(90.0f);
            headingAgle += angleStep;

            x = Q12_MULT_PRECISE(dist, Math_Sin(headingAgle));
            z = Q12_MULT_PRECISE(dist, Math_Cos(headingAgle));
            y = (arg1 > Q12(0.75f)) ? 0x59 : 0x80;
            break;

        case 2:
            x = arg4->vx;
            y = arg4->vy;
            z = arg4->vz;
            break;

        case 3:
            break;
    }

    arg0->vx += Q12_MULT_PRECISE(x, g_DeltaTime);
    arg0->vy += Q12_MULT_PRECISE(y, g_DeltaTime);
    arg0->vz += Q12_MULT_PRECISE(z, g_DeltaTime);
}

void func_800D1604(GsOT_TAG* ot, int arg1) // 0x800D1604
{
    SVECTOR     sp28;
    SVECTOR     sp30;
    s_800DF580* iter;
    int         i;
    int         tick;
    int         temp_s4;

    sp28 = D_800CA788;

    memset(&sp30, 0, sizeof(sp30));

    iter = D_800DF580;

    for (i = 0; i < 16; iter++, i++)
    {
        if (iter->field_8 <= 0)
        {
            continue;
        }

        tick = iter->field_C8 ? iter->field_C8(iter) : 1;

        if (tick)
        {
            func_800D1478(&iter->field_14, iter->field_8, arg1, iter->field_4, &iter->field_C);
            func_800D0D6C(&iter->field_1C, &iter->field_14, 0);

            temp_s4 = func_80055F08(&sp30, &sp28, &iter->field_1C);

            func_800D0CA0(0, &iter->field_14);

            if (g_DeltaTime != 0)
            {
                func_800D13B4(&iter->field_40[1], 12, 11, iter->field_8);
                func_800D0EC0(&iter->field_40[1], 12, 11);
            }

            func_800D0FD4(ot, &iter->field_14, &iter->field_40[1], &iter->field_1C, FP_MULTIPLY_PRECISE(temp_s4, iter->field_CC, 12), 11, 9, 12, iter->field_3C);
            iter->field_8 -= g_DeltaTime;
        }
    }
}

void func_800D17FC(void) // 0x800D17FC
{
    s32         i;
    s_800DF580* ptr;

    ptr = D_800DF580;
    for (i = 0; i < 16; i++, ptr++)
    {
        ptr->field_8  = 0;
        ptr->field_D0 = 0;
        ptr->field_C8 = NULL;

        memset(&ptr->field_40, 0, sizeof(ptr->field_40));
    }
}

void func_800D185C(s32 arg0, s32 arg1) // 0x800D185C
{
    s_800DF580* ptr;

    ptr = &D_800DF580[arg1];
    if (ptr->field_8 <= 0)
    {
        ptr->field_4  = arg1 & 1;
        ptr->field_0  = arg1;
        ptr->field_8  = Q12(1.0f);
        ptr->field_3C = 1;
        ptr->field_C8 = NULL;
        ptr->field_D0 = 0;
        ptr->field_CC = Q12(1.0f);

        memset(&ptr->field_40, 0, sizeof(ptr->field_40));
        func_800D0DE4(&ptr->field_14, arg0, Q12_ANGLE(0.0f), Q12(0.0f));
    }
}

s_800DF580* func_800D1900(VECTOR* arg0, s32 arg1) // 0x800D1900
{
    s32         i;
    s_800DF580* ptr;

    ptr = D_800DF580;
    for (i = 0; i < 16; i++, ptr++)
    {
        if (ptr->field_8 <= Q12(0.0f))
        {
            ptr->field_C8 = NULL;
            ptr->field_D0 = 0;
            ptr->field_0  = i;
            ptr->field_8  = Q12(1.0f);
            ptr->field_4  = arg1;
            ptr->field_3C = 1;

            func_800D0DE4(&ptr->field_14, arg0, Q12_ANGLE(0.0f), Q12(0.0f));
            memset(&ptr->field_40, 0, sizeof(ptr->field_40));
            return ptr;
        }
    }

    return NULL;
}

void func_800D19AC(VECTOR3* vec) // 0x800D19AC
{
    func_800D1900(vec, 3);
}

void func_800D19CC(VECTOR3* vec) // 0x800D19CC
{
    D_800E08F0.vx = vec->vx;
    D_800E08F0.vy = vec->vy;
    D_800E08F0.vz = vec->vz;
}

bool func_800D19F0(s_800DF580* arg0) // 0x800D19F0
{
    switch (arg0->field_D0)
    {
        case 0:
            if (arg0->field_D4 < 0)
            {
                arg0->field_D0 = 1;
            }

            arg0->field_D4 -= g_DeltaTime;
            return false;

        case 1:
            if (arg0->field_8 > Q12(0.6f))
            {
                if (arg0->field_CC < Q12(0.65f))
                {
                    arg0->field_CC += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.34f));
                }
                else
                {
                    arg0->field_CC = Q12(0.65f);
                }
            }
            else
            {
                if (arg0->field_CC > Q12(0.0f))
                {
                    arg0->field_CC -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.25f));
                }
                else
                {
                    arg0->field_CC = Q12(0.0f);
                }
            }
            break;
    }

    return true;
}

void func_800D1AFC(void) // 0x800D1AFC
{
    VECTOR      sp10;
    q19_12      var_s1;
    s32         i;
    s_800DF580* ptr;
    VECTOR3*    vec;

    var_s1 = Rng_Rand16();

    for (i = 0; i < 5; i++)
    {
        vec = &D_800E0698.field_258;

        sp10.vx = vec->vx;
        sp10.vy = vec->vy;
        sp10.vz = vec->vz;

        ptr = func_800D1900(&sp10, 2);

        if (ptr != NULL)
        {
            var_s1       += Rng_GenerateUInt(-0x80, 0x80 - 1);
            ptr->field_C  = Q12_MULT_PRECISE(Math_Sin(var_s1), 0x99);
            ptr->field_E  = Rng_GenerateUInt(0x70, 0x90 - 1);
            ptr->field_10 = Q12_MULT_PRECISE(Math_Cos(var_s1), 0x99);
            ptr->field_8  = Q12(1.9f);
            ptr->field_D4 = Rng_GenerateUInt(0, 255);
            ptr->field_CC = Q12(0.3f);
            ptr->field_D0 = 0;
            ptr->field_C8 = func_800D19F0;
            ptr->field_3C = 1;
        }

        var_s1 += Q12(0.2f);
    }
}

void func_800D1C48(void) // 0x800D1C48
{
    VECTOR      sp10; // Q19.12
    s_800DF580* ptr;

    if (!(Rng_Rand16() & 0x30))
    {
        sp10.vx = D_800E08F0.vx;
        sp10.vy = D_800E08F0.vy + Q12(0.2f);
        sp10.vz = D_800E08F0.vz;

        ptr = func_800D1900(&sp10, 2);

        if (ptr != NULL)
        {
            ptr->field_C  = Rng_Rand16() % 0x99 - 0x4C;
            ptr->field_E  = -0x4C;
            ptr->field_10 = Rng_Rand16() % 0x99 - 0x4C;
            ptr->field_3C = 1;
        }
    }
}

void func_800D1D3C(GsOT_TAG* tag, SVECTOR3* arg1, MATRIX* arg2, s32 arg3) // 0x800D1D3C
{
    SVECTOR   sp28;
    SVECTOR   sp30;
    SVECTOR   sp38;
    SVECTOR   sp40;
    long      sp48;
    long      sp4C;
    long      sp50;
    long      sp54;
    long      sp58;
    long      sp5C;
    long      sp60;
    s32       temp_a3;
    s32       temp_t0;
    s32       temp_t1;
    s32       temp_v0_3;
    s32       temp_v1_2;
    u32       temp_a1;
    s32       temp_a2;
    s32       temp_v0;
    s32       var_a1;
    GsOT_TAG* temp_a1_2;
    POLY_FT4* poly;
    POLY_FT4* poly2;

    PushMatrix();
    temp_v0 = func_80055F08(arg1, &D_800DAE58, arg2) & 0xFF;
    temp_a2 = Q12_MULT_PRECISE(temp_v0, arg3);
    if (temp_a2 < 0x100)
    {
        var_a1 = temp_a2;
    }
    else
    {
        var_a1 = 0xFF;
    }

    func_80055E90((CVECTOR*)&sp48, var_a1 & 0xFF);
    PopMatrix();

    temp_t1 = arg1->vx - 0x80;
    temp_a3 = arg1->vy;
    temp_t0 = arg1->vz - 0x80;
    temp_v0_3 = arg1->vx + 0x80;
    temp_v1_2 = arg1->vz + 0x80;

    sp28.vx = temp_t1;
    sp28.vy = temp_a3;
    sp28.vz = temp_t0;

    sp30.vx = temp_v0_3;
    sp30.vy = temp_a3;
    sp30.vz = temp_t0;

    sp38.vx = temp_t1;
    sp38.vy = temp_a3;
    sp38.vz = temp_v1_2;

    sp40.vx = temp_v0_3;
    sp40.vy = temp_a3;
    sp40.vz = temp_v1_2;

    temp_a1 = RotTransPers4(&sp28, &sp30, &sp38, &sp40, &sp4C, &sp50, &sp54, &sp58, &sp5C, &sp60);
    poly = poly2 = (POLY_FT4*) GsOUT_PACKET_P;

    if (sp60 & 0x20000)
    {
        return;
    }

    poly2->tpage = D_800DF558;
    poly2->clut = D_800DF564;

    setUV4(poly2,
           0xE0, 0xC0,
           0xFF, 0xC0,
           0xE0, 0xE0,
           0xFF, 0xE0);

    *(s32*)&poly2->x0 = *(s32*)&sp4C;
    *(s32*)&poly2->x1 = *(s32*)&sp50;
    *(s32*)&poly2->x2 = *(s32*)&sp54;
    *(s32*)&poly2->x3 = *(s32*)&sp58;
    *(s32*)&poly2->r0 = *(s32*)&sp48;

    setPolyFT4(poly2);
    setSemiTrans(poly2, true);

    temp_a1_2 = &tag[temp_a1 >> 1];
    addPrim(&temp_a1_2[25], poly2);

    poly = poly2 + 1;
    poly->tpage = D_800DF55C;
    poly->clut = D_800DF568;

    setUV4(poly,
           0xE0, 0xC0,
           0xFF, 0xC0,
           0xE0, 0xE0,
           0xFF, 0xE0);

    *(s32*)&poly->x0 = *(s32*)&sp4C;
    *(s32*)&poly->x1 = *(s32*)&sp50;
    *(s32*)&poly->x2 = *(s32*)&sp54;
    *(s32*)&poly->x3 = *(s32*)&sp58;
    *(s32*)&poly->r0 = *(s32*)&sp48;

    setPolyFT4(poly);
    setSemiTrans(poly, true);

    temp_a1_2 = &tag[temp_a1 >> 1];
    addPrim(&temp_a1_2[25], poly);

    poly++;
    GsOUT_PACKET_P = (PACKET*)poly;
}

void func_800D1FF4(GsOT_TAG* arg0) // 0x800D1FF4
{
    SVECTOR     sp10 = { 0 };
    MATRIX      sp18;
    s32         i;
    s_800E0300* ptr1;
    s_800E0988* ptr0;

    ptr1 = D_800E0300;

    func_800D0D6C(&sp18, &sp10, 0);

    ptr0 = &D_800E0988;

    SetRotMatrix(&ptr0->world_8);
    SetTransMatrix(&ptr0->world_8);

    for (i = 0; i < ARRAY_SIZE(D_800E0300); i++, ptr1++)
    {
        if (ptr1->timer_0 > 0)
        {
            if (ptr1->timer_0 > Q12(1.2f))
            {
                ptr1->field_4 = Q12(1.0f);
            }
            else
            {
                ptr1->field_4 -= Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.3f);
                ptr1->field_4  = MAX(ptr1->field_4, Q12(0.0f));
            }

            func_800D1D3C(arg0, &ptr1->field_8, &sp18, ptr1->field_4);
            ptr1->timer_0 -= g_DeltaTime;
        }
    }
}

void func_800D2120(void) // 0x800D2120
{
    s32         i;
    s_800E0300* ptr;

    ptr = D_800E0300;

    for (i = 0; i < 16; i++, ptr++)
    {
        ptr->timer_0 = 0;
        ptr->field_4 = 0x800;
    }
}

void func_800D2150(VECTOR* arg0, s32 arg1) // 0x800D2150
{
    s_800E0300* ptr;

    ptr = &D_800E0300[arg1];
    if (ptr->timer_0 <= Q12(0.0f))
    {
        ptr->timer_0 = Q12(3.0f);
        func_800D0DE4(&ptr->field_8, arg0, Q12_ANGLE(0.0f), Q12(0.0f));
    }
}

void func_800D21AC(GsOT_TAG* ot, MATRIX* arg1, s32 arg2, s32 arg3) // 0x800D21AC
{
    SVECTOR   sp20[9];
    DVECTOR   sp68[9];
    CVECTOR   sp90[9];
    u16       spB8[9];
    s32       spD0;
    SVECTOR*  var_s0;
    s32       temp_v0;
    s32       temp_v0_2;
    s32       temp_v1;
    s32       k;
    s32       i;
    s32       j;
    s32       var_s4;
    s32       var_v0;
    s32       var_v0_2;
    DVECTOR*  var_s1;
    CVECTOR*  var_s1_2;
    u16*      var_a0_3;
    s32       idx;
    u8*       var_t4;
    GsOT_TAG* temp_v0_3;
    GsOT_TAG* ot1;
    POLY_GT4* poly;
    POLY_GT4* poly2;

    var_s4 = 0;
    var_s0 = sp20;

    temp_v0 = Q12_MULT_PRECISE(arg3, 0x100);
    temp_v1 = temp_v0;

    for (i = -1; i < 2; i++)
    {
        for (k = -1; k < 2; k++)
        {
            var_s0->vx = temp_v0 * k;
            var_s0->vy = 0;
            var_s0->vz = temp_v1 * i;
            var_s0++;
        }
    }

    PushMatrix();

    var_s0   = sp20;
    var_s1_2 = sp90;

    for (j = 0; j < 9; j++)
    {
        temp_v0_2 = func_80055F08(var_s0, &D_800DAE60, arg1);

        func_80055E90(var_s1_2, Q12_MULT_PRECISE(temp_v0_2, arg2));
        var_s1_2++;
        var_s0++;
    }

    PopMatrix();

    var_a0_3 = &spB8[0];

    for (i = 0; i < 3; i++)
    {
        var_v0 = (-0x80 + i * 0x20) & 0xFF;

        if (i == 2)
        {
            var_v0 -= 1;
        }

        for (k = 0; k < 3; k++)
        {
            var_v0_2 = (0x40 + k * 0x20) & 0xFF;
            if (k == 2)
            {
                var_v0_2 -= 1;
            }
            *var_a0_3 = (var_v0_2 & 0xFF) | ((var_v0 & 0xFF) << 8);
            var_a0_3++;
        }
    }

    var_s0 = sp20;
    var_s1 = sp68;

    for (j = 0; j < 3; j++)
    {
        temp_v1 = RotTransPers3(&var_s0[0], &var_s0[1], &var_s0[2],
                                &var_s1[0], &var_s1[1], &var_s1[2], &spD0, &spD0);
        if (j == 2)
        {
            var_s4 = temp_v1;
        }
        var_s0 += 3;
        var_s1 += 3;
    }

    temp_v0_3 = &ot[var_s4 >> 1];
    ot1        = &temp_v0_3[25];

    poly = (POLY_GT4*)GsOUT_PACKET_P;

    var_t4 = D_800DAE68;

    for (j = 0; j < 4; j++, var_t4 += 4)
    {
        idx = var_t4[0];
        COPY_GT4_DATA(poly, idx, (u16*)&spB8, (s32*)&sp68, (s32*)&sp90, 0);
        idx = var_t4[1];
        COPY_GT4_DATA(poly, idx, (u16*)&spB8, (s32*)&sp68, (s32*)&sp90, 1);
        idx = var_t4[2];
        COPY_GT4_DATA(poly, idx, (u16*)&spB8, (s32*)&sp68, (s32*)&sp90, 2);
        idx = var_t4[3];
        COPY_GT4_DATA(poly, idx, (u16*)&spB8, (s32*)&sp68, (s32*)&sp90, 3);

        poly->tpage = D_800DF558;
        poly->clut  = D_800DF564;

        setPolyGT4(poly);
        setSemiTrans(poly, 1);

        addPrim(ot1, poly);
        poly++;

        idx = var_t4[0];
        COPY_GT4_DATA(poly, idx, (u16*)&spB8, (s32*)&sp68, (s32*)&sp90, 0);
        idx = var_t4[1];
        COPY_GT4_DATA(poly, idx, (u16*)&spB8, (s32*)&sp68, (s32*)&sp90, 1);
        idx = var_t4[2];
        COPY_GT4_DATA(poly, idx, (u16*)&spB8, (s32*)&sp68, (s32*)&sp90, 2);
        idx = var_t4[3];
        COPY_GT4_DATA(poly, idx, (u16*)&spB8, (s32*)&sp68, (s32*)&sp90, 3);

        poly->tpage = D_800DF55C;
        poly->clut  = D_800DF568;

        setPolyGT4(poly);
        setSemiTrans(poly, 1);

        addPrim(ot1, poly);
        poly++;
    }

    GsOUT_PACKET_P = (PACKET*)poly;
}

void func_800D2684(VECTOR* arg0, s32 arg1) // 0x800D2684
{
    s32         i;
    s_800E0900* ptr;

    ptr = D_800E0900;

    for (i = 0; i < 2; i++, ptr++)
    {
        if (ptr->field_0 <= Q12(0.0f))
        {
            ptr->field_0  = Q12(4.5f);
            ptr->field_C  = Q12(0.5f);
            ptr->field_10 = Q12(0.4f);

            func_800D0DE4(&ptr->field_4, arg0, Q12_ANGLE(0.0f), Q12(0.0f));
            return;
        }
    }
}

void func_800D26FC(VECTOR* arg0, s32 arg1) // 0x800D26FC
{
    s32         i;
    s_800E0440* ptr;

    ptr = D_800E0440;

    for (i = 0; i < 3; i++, ptr++)
    {
        if (ptr->field_0 <= Q12(0.0f))
        {
            ptr->field_0  = Q12(8.0f);
            ptr->field_C  = Q12(0.0f);
            ptr->field_10 = Q12(0.0f);
            ptr->field_14 = arg1;

            func_800D0DE4(&ptr->field_4, arg0, Q12_ANGLE(0.0f), Q12(0.0f));
            break;
        }
    }

    func_800D2684(arg0, arg1);
}

void func_800D2790(GsOT_TAG* arg0, MATRIX* arg1, s32 arg2, s32 arg3) // 0x800D2790
{
    SVECTOR   sp20[9];
    DVECTOR   sp68[9];
    CVECTOR   sp90[9];
    u16       spB8[9];
    u16       spD0[9];
    s32       spE8;
    SVECTOR*  var_s0;
    s32       temp_v0;
    s32       temp_v0_2;
    s32       temp_v1;
    s32       k;
    s32       i;
    s32       j;
    s32       l;
    s32       var_s4;
    s32       var_v0;
    s32       var_v0_2;
    DVECTOR*  var_s1;
    CVECTOR*  var_s1_2;
    u16*      var_a0_3;
    s32       idx;
    u8*       var_t4;
    GsOT_TAG* temp_v0_3;
    GsOT_TAG* ot;
    POLY_GT4* poly;
    POLY_GT4* poly2;
    u16*      var_v1_2;
    s32       var_a1_2;

    var_s4 = 0;
    var_s0 = sp20;

    temp_v0 = Q12_MULT_PRECISE(arg3, 0xCC);
    temp_v1 = temp_v0;

    for (i = -1; i < 2; i++)
    {
        for (k = -1; k < 2; k++)
        {
            var_s0->vx = temp_v0 * k;
            var_s0->vy = 0;
            var_s0->vz = temp_v1 * i;
            var_s0++;
        }
    }

    PushMatrix();

    var_s0   = sp20;
    var_s1_2 = sp90;

    for (l = 0; l < 9; l++)
    {
        temp_v0_2 = func_80055F08(var_s0, &D_800DAE78, arg1);
        var_a1_2  = CLAMP_HIGH(Q12_MULT_PRECISE(temp_v0_2, arg2), 0xFF);

        func_80055E90(var_s1_2, var_a1_2);
        var_s1_2++;
        var_s0++;
    }

    PopMatrix();

    var_a0_3 = spB8;

    for (i = 0; i < 3; i++)
    {
        var_v0 = (-0x80 + i * 0x20) & 0xFF;

        if (i == 2)
        {
            var_v0 -= 1;
        }

        for (k = 0; k < 3; k++)
        {
            var_v0_2 = (k << 5) & 0xFF;
            if (k == 2)
            {
                var_v0_2 -= 1;
            }
            *var_a0_3 = (var_v0_2 & 0xFF) | ((var_v0 & 0xFF) << 8);
            var_a0_3++;
        }
    }

    var_v1_2 = spD0;

    for (i = 0; i < 3; i++)
    {
        var_v0 = (-0x40 + i * 0x20) & 0xFF;
        if (i == 2)
        {
            var_v0 -= 1;
        }

        for (k = 0; k < 3; k++)
        {
            var_v0_2 = (k << 5) & 0xFF;
            if (k == 2)
            {
                var_v0_2 -= 1;
            }
            *var_v1_2 = (var_v0_2 & 0xFF) | ((var_v0 & 0xFF) << 8);
            var_v1_2++;
        }
    }

    var_s0 = sp20;
    var_s1 = sp68;

    for (l = 0; l < 3; l++)
    {
        temp_v1 = RotTransPers3(&var_s0[0], &var_s0[1], &var_s0[2],
                                &var_s1[0], &var_s1[1], &var_s1[2], &spE8, &spE8);
        if (l == 2)
        {
            var_s4 = temp_v1;
        }
        var_s0 += 3;
        var_s1 += 3;
    }

    temp_v0_3 = &arg0[var_s4 >> 1];
    ot        = &temp_v0_3[25];

    poly = (POLY_GT4*)GsOUT_PACKET_P;

    var_t4 = D_800DAE80;

    for (l = 0; l < 4; l++, var_t4 += 4)
    {
        idx = var_t4[0];
        COPY_GT4_DATA(poly, idx, (u16*)&spB8, (s32*)&sp68, (s32*)&sp90, 0);
        idx = var_t4[1];
        COPY_GT4_DATA(poly, idx, (u16*)&spB8, (s32*)&sp68, (s32*)&sp90, 1);
        idx = var_t4[2];
        COPY_GT4_DATA(poly, idx, (u16*)&spB8, (s32*)&sp68, (s32*)&sp90, 2);
        idx = var_t4[3];
        COPY_GT4_DATA(poly, idx, (u16*)&spB8, (s32*)&sp68, (s32*)&sp90, 3);

        poly->tpage = 0x4D;
        poly->clut  = D_800DF56C;

        setPolyGT4(poly);
        setSemiTrans(poly, 1);

        addPrim(ot, poly);
        poly++;

        idx = var_t4[0];
        COPY_GT4_DATA(poly, idx, (u16*)&spD0, (s32*)&sp68, (s32*)&sp90, 0);
        idx = var_t4[1];
        COPY_GT4_DATA(poly, idx, (u16*)&spD0, (s32*)&sp68, (s32*)&sp90, 1);
        idx = var_t4[2];
        COPY_GT4_DATA(poly, idx, (u16*)&spD0, (s32*)&sp68, (s32*)&sp90, 2);
        idx = var_t4[3];
        COPY_GT4_DATA(poly, idx, (u16*)&spD0, (s32*)&sp68, (s32*)&sp90, 3);

        poly->tpage = 0x4D;
        poly->clut  = D_800DF56C;

        setPolyGT4(poly);
        setSemiTrans(poly, 1);

        addPrim(ot - 25, poly);
        poly++;
    }

    GsOUT_PACKET_P = (PACKET*)poly;
}

void func_800D2CC8(void) // 0x800D2CC8
{
    s32         i;
    s_800E0900* ptr;

    ptr = D_800E0900;

    for (i = 1; i >= 0; i--)
    {
        ptr->field_0 = 0;
        ptr++;
    }
}

void func_800D2CEC(void) // 0x800D2CEC
{
    s32         i;
    s_800E0440* ptr;

    ptr = D_800E0440;

    for (i = 2; i >= 0; i--)
    {
        ptr->field_0 = 0;
        ptr++;
    }

    func_800D2CC8();
}

void func_800D2D28(GsOT_TAG* arg0)
{
    MATRIX      sp10;
    SVECTOR     sp30;
    s32         temp_s4;
    s32         var_a0;
    s32         i;
    s_800E0900* ptr;

    ptr = D_800E0900;
    vwGetViewAngle(&sp30);
    temp_s4 = sp30.vy + 0x800;

    for (i = 0; i < 2; i++, ptr++)
    {
        if (ptr->field_0 > 0)
        {
            ptr->field_10 += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.7f));
            ptr->field_10  = MIN(0x1000, ptr->field_10);

            if (ptr->field_0 > 0x2B33)
            {
                var_a0 = ptr->field_C + Q12_MULT_PRECISE(g_DeltaTime, 0x800);
                if (var_a0 > 0x1000)
                {
                    ptr->field_C = 0x1000;
                }
                else
                {
                    ptr->field_C = var_a0;
                }
            }
            else
            {
                ptr->field_C -= Q12_MULT_PRECISE(g_DeltaTime, 0x666);
                ptr->field_C  = MAX(ptr->field_C, 0);
            }

            func_800D0D6C(&sp10, &ptr->field_4, temp_s4);
            func_800D0CA0(temp_s4, &ptr->field_4);
            func_800D2790(arg0, &sp10, ptr->field_C, ptr->field_10);
            ptr->field_0 -= g_DeltaTime;
        }
    }
}

void func_800D2ED0(GsOT_TAG* arg0) // 0x800D2ED0
{
    MATRIX      sp10;
    s32         i;
    s_800E0440* ptr;

    ptr = D_800E0440;

    for (i = 0; i < 3; i++, ptr++)
    {
        if (ptr->field_0 > 0)
        {
            ptr->field_10 += Q12_MULT_PRECISE(g_DeltaTime, 0x800);
            ptr->field_10  = MIN(0x1000, ptr->field_10);

            if (ptr->field_0 > 0x2B33)
            {
                ptr->field_C = 0x1000;
            }
            else
            {
                ptr->field_C -= Q12_MULT_PRECISE(g_DeltaTime, 0x666);
                ptr->field_C  = MAX(ptr->field_C, 0);
            }
            func_800D0D6C(&sp10, &ptr->field_4, 0);
            func_800D0CA0(0, &ptr->field_4);
            func_800D21AC(arg0, &sp10, ptr->field_C, ptr->field_10);

            ptr->field_0 -= g_DeltaTime;
        }
    }

    func_800D2D28(arg0);
}

void Twinfeeler_TextureLoad(void) // 0x800D3038
{
    // TODO: Does game ever use this texture afterward?
    // After this `Twinfeeler_Init` checks `Fs_QueueDoThingWhenEmpty()` before proceeding.
    // Could it be some preload/warm-up before the actual enemy file loads? If so, this func should be renamed.
    Fs_QueueStartReadTim(FILE_TEST_WARMTEST_TIM, FS_BUFFER_1, &D_800A9094);
}

void Math_Vector3Translate(VECTOR3* outVec, const VECTOR3* inVec, q19_12 headingAngle, q19_12 dist) // 0x800D3068
{
    outVec->vx = inVec->vx + Q12_MULT_PRECISE(Math_Sin(headingAngle), dist);
    outVec->vy = inVec->vy;
    outVec->vz = inVec->vz + Q12_MULT_PRECISE(Math_Cos(headingAngle), dist);
}

void func_800D3114(void) // 0x800D3114
{
    VECTOR3     sp10;
    s_800E0930* ptr;

    ptr = D_800E0930;

    switch (ptr->field_0)
    {
        case 0:
            Math_Vector3Translate(&sp10, &ptr->position_C, ptr->chara_8->rotation_24.vy, 0x1400);
            func_800D19CC(&sp10);
            func_800D1AFC();
            func_800D26FC(&sp10, ptr->chara_8->rotation_24.vy);
            ptr->field_0++;
            break;

        case 1:
            if (ptr->field_4 >= 0xCCC)
            {
                func_800D1AFC();
                ptr->field_0++;
            }
            break;

        case 2:
            if (ptr->field_4 >= 0x1000)
            {
                func_800D1C48();
                ptr->field_0++;
            }
            break;

        case 3:
            if (ptr->field_4 >= 0x1800)
            {
                func_800D1AFC();
                ptr->funcptr_18 = NULL;
            }

            if (Rng_Rand16() & 0x80)
            {
                func_800D1C48();
            }
            break;
    }
    ptr->field_4 += g_DeltaTime;
}

INCLUDE_RODATA("maps/map4_s03/nonmatchings/map4_s03", D_800CA788);

void func_800D326C(void) // 0x800D326C
{
    VECTOR3     sp10;
    s_800E0930* ptr;

    ptr = D_800E0930;

    switch (ptr->field_0)
    {
        case 0:
            Math_Vector3Translate(&sp10, &ptr->position_C, ptr->chara_8->rotation_24.vy, 0x14CC);
            func_800D19CC(&sp10);
            ptr->field_0++;
            break;

        case 1:
            if (ptr->field_4 >= 0x4CC)
            {
                ptr->field_0++;
            }
            func_800D1C48();
            break;

        case 2:
            if (ptr->field_4 >= 0x599)
            {
                Math_Vector3Translate(&sp10, &ptr->position_C, ptr->chara_8->rotation_24.vy, 0x1266);
                func_800D26FC(&sp10, ptr->chara_8->rotation_24.vy);
                func_800D1AFC();
                ptr->field_0++;
            }
            break;

        case 3:
            if (ptr->field_4 >= 0xE66)
            {
                func_800D1C48();
                ptr->field_0++;
            }
            break;

        case 4:
            if (ptr->field_4 >= 0x14CC)
            {
                func_800D1AFC();
                ptr->funcptr_18 = NULL;
            }
            break;
    }
    ptr->field_4 += g_DeltaTime;
}

void func_800D33D0(void) // 0x800D33D0
{
    s32         i;
    s_800E0930* ptr;

    ptr = D_800E0930;

    for (i = 0; i < 3; i++, ptr++)
    {
        if (ptr->funcptr_18 != NULL)
        {
            ptr->funcptr_18(ptr);
        }
    }
}

void func_800D3428(void) // 0x800D3428
{
    s32         i;
    s_800E0930* ptr;

    ptr = D_800E0930;

    for (i = 2; i >= 0; i--)
    {
        ptr->funcptr_18 = NULL;
        ptr++;
    }
}

s_800E0930* func_800D344C(s_SubCharacter* chara, void (*funcptr)(s_800E0930*)) // 0x800D344C
{
    s_Collision coll;
    s32         i;
    s_800E0930* ptr;

    ptr = D_800E0930;

    for (i = 0; i < 3; i++, ptr++)
    {
        if (!ptr->funcptr_18)
        {
            Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);
            ptr->chara_8       = chara;
            ptr->position_C.vx = chara->position_18.vx;
            ptr->position_C.vy = coll.groundHeight_0;
            ptr->position_C.vz = chara->position_18.vz;
            ptr->funcptr_18    = funcptr;
            ptr->field_4       = 0;
            ptr->field_0       = 0;
            return ptr;
        }
    }
    return NULL;
}

void func_800D3504(s_SubCharacter* chara) // 0x800D3504
{
    func_800D344C(chara, &func_800D326C);
}

void func_800D3528(s_SubCharacter* chara) // 0x800D3528
{
    func_800D344C(chara, &func_800D3114);
}

void func_800D354C(VECTOR3* arg0) // 0x800D354C
{
    s32         var_a0;
    s32         var_v1;
    s_800E0988* ptr;

    ptr = D_800E0988;

    var_v1 = arg0->vx;

    if (var_v1 < 0)
    {
        var_v1 += 0x3FFFF;
    }
    var_v1 = (var_v1 >> 18) << 18;

    var_a0 = arg0->vz;

    if (var_a0 < 0)
    {
        var_a0 += 0x3FFFF;
    }

    ptr->x_0 = var_v1;
    ptr->z_4 = (var_a0 >> 18) << 18;

    func_800D078C();
    func_800D0840();
    func_800D17FC();
    func_800D2120();
    func_800D2CEC();
    func_800D3428();
}

void func_800D35DC(SVECTOR* rot) // 0x800D35DC
{
    GsOT_TAG*   ot;
    s_800E0988* ptr;
    s32         idx;

    ptr = D_800E0988;

    if (g_DeltaTime != Q12(0.0f))
    {
        func_800D33D0();
    }

    idx = g_ActiveBufferIdx;

    ot = g_OrderingTable0[idx].org;

    func_80049C2C(&ptr->world_8, ptr->x_0, 0, ptr->z_4);
    func_800D0C50(rot, &ptr->world_8);
    func_800D1604(ot, rot->vy);
    func_800D1FF4(ot);
    func_800D2ED0(ot);
}

void func_800D3694(s_SubCharacter* twinfeeler, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D3694
{
    typedef struct
    {
        MATRIX  field_0;
        SVECTOR field_20;
        VECTOR  field_28; // Q23.8
    } s_func_800D3694;

    enum _SfxId      var_a0;
    s32              temp_s0;
    s_AnimInfo*      anim;
    s_func_800D3694* ptr;

    twinfeeler->position_18.vy = D_800DB1E0[twinfeeler->model_0.stateStep_3];

    if (twinfeeler->model_0.controlState_2 == TwinfeelerControl_None)
    {
        twinfeeler->model_0.controlState_2       = TwinfeelerControl_1;
        twinfeeler->model_0.anim_4.status_0      = ANIM_STATUS(TwinfeelerAnim_6, true);
        twinfeeler->model_0.anim_4.keyframeIdx_8 = 163;
        twinfeeler->health_B0                    = 1;
        twinfeeler->model_0.anim_4.time_4        = Q12(163.0f);
        twinfeeler->model_0.anim_4.alpha_A       = Q12(0.0f);
        twinfeeler->field_E1_0                   = 3;
        twinfeeler->model_0.stateStep_3         -= 18;
        twinfeeler->rotation_24.vx               = D_800DB1E8[twinfeeler->model_0.stateStep_3];
        twinfeeler->rotation_24.vy               = D_800DB1F0[twinfeeler->model_0.stateStep_3];
    }

    if (twinfeeler->model_0.stateStep_3 == 1)
    {
        twinfeeler->timer_C6 = Q12(0.75f) - func_80055D78(twinfeeler->position_18.vx, twinfeeler->position_18.vy, twinfeeler->position_18.vz) * 16;
    }
    else
    {
        twinfeeler->timer_C6 = Q12(1.0f) - func_80055D78(twinfeeler->position_18.vx, twinfeeler->position_18.vy, twinfeeler->position_18.vz) * 16;
    }

    if (twinfeeler->timer_C6 < Q12(0.0f))
    {
        twinfeeler->timer_C6 = Q12(0.0f);
    }
    else if (twinfeeler->timer_C6 > Q12(1.0f))
    {
        twinfeeler->timer_C6 = Q12(1.0f);
    }

    if (twinfeeler->health_B0 > Q12(0.0f) && twinfeeler->damage_B4.amount_C > Q12(0.0f))
    {
        twinfeeler->health_B0               = Q12(0.0f);
        twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_7, false);
    }

    if (twinfeeler->health_B0 > Q12(0.0f) && twinfeeler->properties_E4.twinfeeler.field_E8.val32 == 0)
    {
        if (Rng_GenerateUInt(0, 3)) // 1 in 4 chance.
        {
            var_a0 = Sfx_Unk1553;
        }
        else
        {
            var_a0 = Sfx_Unk1552;
        }

        func_8005DC1C(var_a0, &twinfeeler->position_18, Q8(0.5f), 0);
        twinfeeler->properties_E4.twinfeeler.field_E8.val32 = Rng_GenerateInt(Q12(1.0f), Q12(1.8f) - 1);
    }
    else
    {
        twinfeeler->properties_E4.twinfeeler.field_E8.val32 -= g_DeltaTime;
        if (twinfeeler->properties_E4.twinfeeler.field_E8.val32 < 0)
        {
            twinfeeler->properties_E4.twinfeeler.field_E8.val32 = 0;
        }
    }

    if (twinfeeler->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_20, true))
    {
        if (twinfeeler->health_B0 == Q12(0.0f))
        {
            if (Chara_NpcIdxGet(twinfeeler) != g_SysWork.targetNpcIdx_2353)
            {
                twinfeeler->health_B0  = NO_VALUE;
                twinfeeler->field_E1_0 = 0;
                Savegame_EnemyStateUpdate(twinfeeler);
            }
        }
    }

    Math_MatrixTransform(&twinfeeler->position_18, (SVECTOR*)&twinfeeler->rotation_24, coords);

    anim = &TWINFEELER_ANIM_INFOS[twinfeeler->model_0.anim_4.status_0];
    anim->updateFunc_0(&twinfeeler->model_0, anmHdr, coords, anim);

    temp_s0 = D_800DB1D8[twinfeeler->model_0.stateStep_3];
    func_800705E4(coords, 0, temp_s0, temp_s0, temp_s0);

    twinfeeler->field_C8.field_4   = Q12(0.0f);
    twinfeeler->field_C8.field_2   = Q12(0.0f);
    twinfeeler->field_D8.offsetZ_6 = Q12(0.0f);
    twinfeeler->field_D8.offsetX_4 = Q12(0.0f);
    twinfeeler->field_D4.radius_0  = Q12(0.0f);

    ptr = PSX_SCRATCH;

    Vw_CoordHierarchyMatrixCompute(&coords[11], &ptr->field_0);

    gte_SetRotMatrix(&ptr->field_0);
    gte_SetTransMatrix(&ptr->field_0);
    Math_SetSVectorFast(&ptr->field_20, 64, 89, 0);

    gte_ldv0(&ptr->field_20);
    gte_rt();
    gte_stlvnl(&ptr->field_28);

    twinfeeler->field_C8.field_0   = Q12_MULT_PRECISE(Q8_TO_Q12(ptr->field_28.vy), temp_s0);
    twinfeeler->field_C8.field_6   = twinfeeler->field_C8.field_0 + 122;
    twinfeeler->field_D8.offsetX_0 = Q12_MULT_PRECISE(twinfeeler->position_18.vx - Q8_TO_Q12(ptr->field_28.vx), temp_s0);
    twinfeeler->field_D8.offsetZ_2 = Q12_MULT_PRECISE(twinfeeler->position_18.vz - Q8_TO_Q12(ptr->field_28.vz), temp_s0);
    twinfeeler->field_D4.field_2   = Q12(0.05f);
}

void func_800D3AE0(s_SubCharacter* chara, s32 soundIdx)
{
    func_8005DC1C(D_800DB1F8[soundIdx].id_0, &chara->position_18, D_800DB1F8[soundIdx].volume_2.val16, 0);
}

u32 func_800D3B1C(void) // 0x800D3B1C
{
    u8 sp10;

    Player_DisableDamage(&sp10, 0);
    return sp10;
}

void func_800D3B44(bool disableDamage)
{
    u8 sp10;

    Player_DisableDamage(&sp10, disableDamage);
}

void func_800D3B68(s_SubCharacter* twinfeeler) // 0x800D3B68
{
    twinfeeler->health_B0 = twinfeeler->properties_E4.npc.field_11C;
}

void func_800D3B74(s_SubCharacter* twinfeeler) // 0x800D3B74
{
    if (twinfeeler->health_B0 >= Q12(0.0f))
    {
        twinfeeler->properties_E4.npc.field_11C = twinfeeler->health_B0;
        twinfeeler->health_B0                   = NO_VALUE;
    }
}

void func_800D3B98(s_SubCharacter* twinfeeler) // 0x800D3B98
{
    s_Collision coll;
    q3_12       headingAngle;
    q19_12      dist;
    q19_12      posX;
    q19_12      posZ;

    headingAngle   = twinfeeler->rotation_24.vy;
    dist = Q12_MULT_PRECISE(Math_Sin(headingAngle), Q12(1.0f));

    Collision_Get(&coll, twinfeeler->position_18.vx + dist,
                  Q12_MULT_PRECISE(Math_Cos(headingAngle), Q12(1.0f)) + twinfeeler->position_18.vz);

    twinfeeler->position_18.vy = coll.groundHeight_0;

    if (twinfeeler->position_18.vy < Q12(-1.0f))
    {
        posX = twinfeeler->position_18.vx;
        posZ = twinfeeler->position_18.vz;
        Collision_Get(&coll, posX, posZ);

        twinfeeler->position_18.vy = coll.groundHeight_0;
        if (twinfeeler->position_18.vy < Q12(-1.0f))
        {
            twinfeeler->position_18.vx = Q12(118.5f);
            twinfeeler->position_18.vz = Q12(137.9f);

            Collision_Get(&coll, posX, posZ);
            twinfeeler->position_18.vy = coll.groundHeight_0;
        }
    }

    twinfeeler->properties_E4.twinfeeler.field_114 &= ~(1 << 2);
}

void func_800D3CBC(s_SubCharacter* twinfeeler) // 0x800D3CBC
{
    twinfeeler->position_18.vy               = Q12(10.0f);
    twinfeeler->properties_E4.npc.field_114 |= 1 << 2;
}

bool Twinfeeler_Init(s_SubCharacter* twinfeeler) // 0x800D3CD4
{
    q19_12          posX;
    q19_12          posZ;
    s_SubCharacter* localTwinfeeler; // TODO: Not sure why this is needed here, could be an inline in this func.

    localTwinfeeler = twinfeeler;

    if (!Fs_QueueDoThingWhenEmpty())
    {
        return false;
    }

    posX = twinfeeler->position_18.vx;
    posZ = twinfeeler->position_18.vz;

    twinfeeler->health_B0 = Q12(3000.0f);

    localTwinfeeler->properties_E4.twinfeeler.field_120 = NO_VALUE;

    twinfeeler->field_D4.radius_0 = Q12(0.3f);

    twinfeeler->model_0.anim_4.alpha_A = Q12(0.0f);

    twinfeeler->moveSpeed_38    = Q12(0.0f);
    twinfeeler->headingAngle_3C = twinfeeler->rotation_24.vy;
    twinfeeler->field_E1_0      = 4;

    localTwinfeeler->properties_E4.twinfeeler.field_EC.position_0.vx = Q12(0.0f);
    localTwinfeeler->properties_E4.twinfeeler.field_EC.position_0.vy = Q12(0.0f);
    localTwinfeeler->properties_E4.twinfeeler.field_EC.position_0.vz = Q12(0.0f);
    localTwinfeeler->properties_E4.twinfeeler.field_10C              = 0;
    localTwinfeeler->properties_E4.twinfeeler.field_110              = 0;
    localTwinfeeler->properties_E4.twinfeeler.field_114              = 0;
    localTwinfeeler->properties_E4.twinfeeler.field_100              = posX;
    localTwinfeeler->properties_E4.twinfeeler.field_104              = posZ;

    func_800D3CBC(twinfeeler);

    twinfeeler->field_D8.offsetX_4 = Q12(0.0f);
    twinfeeler->field_D8.offsetZ_6 = Q12(0.0f);
    twinfeeler->flags_3E          |= CharaFlag_Unk3;

    if (twinfeeler->model_0.stateStep_3 != 0)
    {
        twinfeeler->model_0.controlState_2     = twinfeeler->model_0.stateStep_3;
        twinfeeler->model_0.stateStep_3 = 0;
    }
    else
    {
        twinfeeler->model_0.controlState_2     = TwinfeelerControl_11;
        twinfeeler->model_0.stateStep_3 = 0;
    }

    *(u16*)&localTwinfeeler->properties_E4.twinfeeler.field_E8.val16[1] = NO_VALUE;

    func_800D3B74(twinfeeler);

    Character_AnimSet(twinfeeler, ANIM_STATUS(TwinfeelerAnim_8, false), 258);
    ModelAnim_AnimInfoSet(&twinfeeler->model_0.anim_4, TWINFEELER_ANIM_INFOS);

    Chara_DamageClear(twinfeeler);

    func_800D354C(&twinfeeler->position_18);
    twinfeeler->flags_3E |= CharaFlag_Unk9;
    return true;
}

void func_800D3E18(s_SubCharacter* chara) // 0x800D3E18
{
    *(u16*)&chara->properties_E4.twinfeeler.field_E8.val16[1] = NO_VALUE;

    Sd_SfxStop(Sfx_Unk1567);
    Sd_SfxStop(Sfx_Unk1559);
    func_800D354C(&chara->position_18);
}

void func_800D3E58(s_SubCharacter* twinfeeler) // 0x800D3E58
{
    s32 temp_v1;
    s32 var_a1;
    u8  temp_s1;

    if (twinfeeler->damage_B4.amount_C > Q12(0.0f) && twinfeeler->health_B0 >= Q12(0.0f))
    {
        twinfeeler->properties_E4.twinfeeler.field_EC   = twinfeeler->damage_B4;
        twinfeeler->properties_E4.twinfeeler.field_10C += twinfeeler->damage_B4.amount_C;
        twinfeeler->health_B0                           = MAX(twinfeeler->health_B0 - twinfeeler->damage_B4.amount_C, Q12(0.0f));

        temp_s1 = D_800DB190[twinfeeler->model_0.anim_4.status_0 >> 1];

        if (twinfeeler->health_B0 > Q12(20.0f))
        {
            if (twinfeeler->properties_E4.twinfeeler.field_10C > 0 &&
                twinfeeler->model_0.controlState_2 != TwinfeelerControl_2 && !(temp_s1 & 0x1))
            {
                twinfeeler->properties_E4.twinfeeler.field_10C = 0;
                twinfeeler->model_0.controlState_2             = TwinfeelerControl_2;
                twinfeeler->model_0.stateStep_3                = 0;
            }
        }
        else if (func_800D3B1C() == 0 && twinfeeler->model_0.controlState_2 != TwinfeelerControl_9)
        {
            if (!(temp_s1 & (1 << 1)))
            {
                twinfeeler->properties_E4.twinfeeler.field_118 = 1;
            }
            else
            {
                twinfeeler->properties_E4.twinfeeler.field_118 = 0;
            }

            twinfeeler->health_B0              = NO_VALUE;
            twinfeeler->model_0.controlState_2 = TwinfeelerControl_9;
            twinfeeler->model_0.stateStep_3    = 0;
            twinfeeler->flags_3E              |= CharaFlag_Unk2;
        }
    }

    Chara_DamageClear(twinfeeler);
}

void func_800D3FB0(s_SubCharacter* twinfeeler) // 0x800D3FB0
{
    if (twinfeeler->model_0.controlState_2 >= TwinfeelerControl_2)
    {
        twinfeeler->model_0.controlState_2     = TwinfeelerControl_12;
        twinfeeler->model_0.stateStep_3 = 0;
    }
    else
    {
        twinfeeler->model_0.stateStep_3 = 12;
    }
}

void func_800D3FD8(s_SubCharacter* twinfeeler) // 0x800D3FD8
{
    if (twinfeeler->model_0.controlState_2 >= TwinfeelerControl_2)
    {
        twinfeeler->model_0.controlState_2     = TwinfeelerControl_13;
        twinfeeler->model_0.stateStep_3 = 0;
    }
    else
    {
        twinfeeler->model_0.stateStep_3 = 13;
    }
}

void func_800D4000(s_SubCharacter* twinfeeler) // 0x800D4000
{
    if (twinfeeler->model_0.controlState_2 >= TwinfeelerControl_2)
    {
        twinfeeler->model_0.controlState_2     = TwinfeelerControl_3;
        twinfeeler->model_0.stateStep_3 = 0;
    }
    else
    {
        twinfeeler->model_0.stateStep_3 = 3;
    }
}

void Twinfeeler_Control_11(s_SubCharacter* twinfeeler) // 0x800D4028
{
    if (twinfeeler->model_0.stateStep_3 == 0)
    {
        func_800D3B74(twinfeeler);
        twinfeeler->moveSpeed_38 = Q12(0.0f);
        twinfeeler->model_0.stateStep_3++;
    }

    func_800D3CBC(twinfeeler);
}

void Twinfeeler_Control_12(s_SubCharacter* twinfeeler) // 0x800D4078
{
    s_SubCharacter* localTwinfeeler;

    localTwinfeeler = twinfeeler;

    if (twinfeeler->model_0.stateStep_3 == 0)
    {
        twinfeeler->rotation_24.vy  = Q12_ANGLE(0.0f);
        twinfeeler->headingAngle_3C = Q12_ANGLE(0.0f);
        twinfeeler->position_18.vx  = Q12(118.5f);
        twinfeeler->position_18.vz  = Q12(137.9f);

        func_800D3504(twinfeeler);

        twinfeeler->properties_E4.twinfeeler.field_FC = Q12(0.7f);
        twinfeeler->model_0.stateStep_3++;
    }

    switch (twinfeeler->model_0.stateStep_3)
    {
        case 1:
            if (twinfeeler->properties_E4.twinfeeler.field_FC < Q12(0.0f))
            {
                func_800D3B98(twinfeeler);

                twinfeeler->moveSpeed_38            = Q12(1.8f);
                twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_1, false);

                func_800D3AE0(twinfeeler, 5);
                twinfeeler->model_0.stateStep_3++;
            }

        case 2:
            if (localTwinfeeler->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_18, false))
            {
                twinfeeler->properties_E4.twinfeeler.field_FC = Q12(1.0f);
                localTwinfeeler->moveSpeed_38                     = Q12(1.2f);
                localTwinfeeler->model_0.anim_4.status_0          = ANIM_STATUS(TwinfeelerAnim_8, false);

                func_800D3AE0(localTwinfeeler, 4);
                localTwinfeeler->model_0.stateStep_3++;
            }
            break;

        case 3:
            if (twinfeeler->properties_E4.twinfeeler.field_FC < Q12(0.0f))
            {
                twinfeeler->moveSpeed_38 = Q12(0.8877f);

                Sd_SfxStop(Sfx_Unk1567);
                func_800D3AE0(twinfeeler, 1);

                twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_2, false);
                func_800D3528(twinfeeler);

                twinfeeler->model_0.stateStep_3++;
            }
            break;

        case 4:
            if (twinfeeler->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_18, false))
            {
                twinfeeler->model_0.controlState_2 = TwinfeelerControl_11;
                twinfeeler->model_0.stateStep_3    = 0;
                Sd_SfxStop(Sfx_Unk1559);
            }
            break;
    }

    twinfeeler->properties_E4.twinfeeler.field_FC -= g_DeltaTime;
}

void Twinfeeler_Control_13(s_SubCharacter* twinfeeler) // 0x800D4248
{
    if (twinfeeler->model_0.stateStep_3 == 0)
    {
        twinfeeler->position_18.vx  = Q12(131.0f);
        twinfeeler->position_18.vz  = Q12(140.0f);
        twinfeeler->rotation_24.vy  = Q12_ANGLE(90.0f);
        twinfeeler->headingAngle_3C = Q12_ANGLE(90.0f);

        func_800D3504(twinfeeler);
        twinfeeler->properties_E4.twinfeeler.field_FC = Q12(0.7f);

        Savegame_EnemyStateUpdate(twinfeeler);
        twinfeeler->model_0.stateStep_3++;
    }

    switch (twinfeeler->model_0.stateStep_3)
    {
        case 1:
            if (twinfeeler->properties_E4.twinfeeler.field_FC < Q12(0.0f))
            {
                func_800D3B98(twinfeeler);

                twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_23, false);
                twinfeeler->moveSpeed_38            = Q12(1.35f);

                func_800D3AE0(twinfeeler, 5);
                twinfeeler->model_0.stateStep_3++;
            }
            break;

        case 2:
            if (twinfeeler->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_18, false))
            {
                twinfeeler->moveSpeed_38 = Q12(0.8877f);
                func_800D3AE0(twinfeeler, 1);

                twinfeeler->model_0.anim_4.status_0 = 4;
                twinfeeler->model_0.stateStep_3++;
            }
            break;

        case 3:
            if (twinfeeler->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_18, false))
            {
                Sd_SfxStop(Sfx_Unk1559);
                twinfeeler->model_0.controlState_2 = TwinfeelerControl_11;
                twinfeeler->model_0.stateStep_3    = 1;
            }
            break;
    }

    twinfeeler->properties_E4.twinfeeler.field_FC -= g_DeltaTime;
}

void func_800D43AC(s_SubCharacter* twinfeeler, s32 arg1) // 0x800D43AC
{
    q19_12 angleDeltaToPlayer;
    s32    temp_v0_2;
    s32    var_s1;

    if (arg1 < 15)
    {
        var_s1 = 512;
    }
    else
    {
        var_s1 = 170;
    }

    angleDeltaToPlayer = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - twinfeeler->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - twinfeeler->position_18.vz) -
                                twinfeeler->rotation_24.vy);

    if ((u32)ABS(angleDeltaToPlayer) > 56) // TODO: Needs casting to `u32`.
    {
        temp_v0_2 = Q12_MULT_PRECISE(g_DeltaTime, var_s1);
        if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
        {
            twinfeeler->rotation_24.vy += temp_v0_2;
        }
        else
        {
            twinfeeler->rotation_24.vy -= temp_v0_2;
        }
    }
}

s32 func_800D4488(VECTOR3* arg0, s32 arg1) // 0x800D4488
{
    q19_12 sinAngle;
    q19_12 angle;
    q19_12 temp_v1;
    s32    temp_s3;
    s32    temp_s4;
    s32    temp;
    s32    temp2;
    s32    temp3;
    s32    newVar;

    temp_s4 = (arg1 >> 8) & 0xFF;
    temp_s3 = arg1 & 0xFF;

    temp    = ((Rng_Rand16() << 8) >> 0xF) + 0x7200;
    temp_v1 = temp_s4 << 9;

    newVar = 0x10;
    temp_s4 = temp_v1 + temp;
    temp_s4 = temp_s4 * newVar;

    temp3   = temp_s3 << 9;
    temp2   = ((Rng_Rand16() << 8) >> 0xF) + 0x8800;
    temp_s3 = temp3 + temp2;
    temp_s3 = temp_s3 * newVar;

    angle = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - temp_s4,
                     g_SysWork.playerWork_4C.player_0.position_18.vz - temp_s3);

    sinAngle = Math_Sin(angle);
    temp_v1 = temp_s3 - Math_Cos(angle);

    arg0->vx = temp_s4 - sinAngle;
    arg0->vz = temp_v1;

    return angle;
}

s32 func_800D4558(q19_12 angle, s32 arg1, s32 arg2) // 0x800D4558
{
    s_RayData ray;
    VECTOR3   sp30;
    VECTOR3   sp40;

    sp40.vx = arg1;
    sp40.vy = Q12(-0.3f);
    sp40.vz = arg2;

    sp30.vx = Math_Sin(angle);
    sp30.vy = Q12(0.0f);
    sp30.vz = Math_Cos(angle);

    if (func_8006DC18(&ray, &sp40, &sp30))
    {
        return ray.field_14;
    }
    else
    {
        return INT_MAX;
    }
}

void Twinfeeler_Control_5(s_SubCharacter* twinfeeler)
{
    s_SubCharacter* localTwinfeeler;

    localTwinfeeler = twinfeeler;

    if (twinfeeler->model_0.stateStep_3 == 0)
    {
        twinfeeler->properties_E4.twinfeeler.field_FC = Q12(0.7f);
        func_800D3504(twinfeeler);

        twinfeeler->model_0.stateStep_3++;
    }

    switch (twinfeeler->model_0.stateStep_3)
    {
        case 1:
            if (twinfeeler->properties_E4.twinfeeler.field_FC < Q12(0.0f))
            {
                func_800D3B68(twinfeeler);
                func_800D3B98(twinfeeler);

                twinfeeler->moveSpeed_38            = Q12(1.8f);
                twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_1, false);

                func_800D3AE0(twinfeeler, 5);
                twinfeeler->model_0.stateStep_3++;
            }
            break;

        case 2:
            func_800D43AC(twinfeeler, FP_FROM(twinfeeler->model_0.anim_4.time_4, Q12_SHIFT));
            break;
    }

    localTwinfeeler->properties_E4.twinfeeler.field_FC -= g_DeltaTime;

    if (twinfeeler->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_18, false))
    {
        func_800D4558(twinfeeler->rotation_24.vy, twinfeeler->position_18.vx, twinfeeler->position_18.vz);

        twinfeeler->model_0.controlState_2 = TwinfeelerControl_10;
        twinfeeler->model_0.stateStep_3    = 0;
    }
}

void func_800D46E0(VECTOR3* vec0, VECTOR3* vec1) // 0x800D46E0
{
    sharedFunc_800CB0A4_4_s03(vec0, vec1);
}

void Twinfeeler_Control_6(s_SubCharacter* twinfeeler, GsCOORDINATE2* arg1) // 0x800D4700
{
    MATRIX          sp10;
    VECTOR3         sp30;
    VECTOR3         sp40;
    s32             temp_s1;
    s_SubCharacter* localChara;

    localChara = twinfeeler;

    temp_s1 = twinfeeler->model_0.stateStep_3 == 0;
    if (temp_s1)
    {
        twinfeeler->properties_E4.twinfeeler.field_FC = Q12(0.7f);
        func_800D3504(twinfeeler);

        twinfeeler->model_0.stateStep_3++;
    }

    temp_s1 = FP_FROM(twinfeeler->model_0.anim_4.time_4, Q12_SHIFT);

    switch (twinfeeler->model_0.stateStep_3)
    {
        case 1:
            if (twinfeeler->properties_E4.twinfeeler.field_FC < Q12(0.0f))
            {
                func_800D3B68(twinfeeler);
                func_800D3B98(twinfeeler);

                twinfeeler->moveSpeed_38            = Q12(1.8f);
                twinfeeler->model_0.anim_4.status_0 = 2;

                func_800D3AE0(twinfeeler, 5);
                twinfeeler->model_0.stateStep_3++;
            }
            break;

        case 2:
            if (temp_s1 > 5)
            {
                func_800D3AE0(twinfeeler, 3);
                Vw_CoordHierarchyMatrixCompute(&arg1[14], &sp10);

                sp30.vx = Q8_TO_Q12(sp10.t[0]);
                sp30.vy = Q8_TO_Q12(sp10.t[1]);
                sp30.vz = Q8_TO_Q12(sp10.t[2]);
                sp40.vx = g_SysWork.playerWork_4C.player_0.position_18.vx;
                sp40.vy = g_SysWork.playerWork_4C.player_0.position_18.vy - Q12(1.0f);
                sp40.vz = g_SysWork.playerWork_4C.player_0.position_18.vz;

                func_800D46E0(&sp30, &sp40);
                twinfeeler->model_0.stateStep_3++;
            }

        case 3:
            func_800D43AC(localChara, temp_s1);
            break;
    }

    if (twinfeeler->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_18, false))
    {
        twinfeeler->model_0.controlState_2 = TwinfeelerControl_10;
        twinfeeler->model_0.stateStep_3    = 0;
    }

    localChara->properties_E4.twinfeeler.field_FC -= g_DeltaTime;
}

bool func_800D48CC(s32 arg0, s32 arg1) // 0x800D48CC
{
    s32 temp_a0;
    s32 temp_a1;

    temp_a0 = arg0 - D_800DB210.field_0;
    temp_a1 = arg1 - D_800DB210.field_4;

    if (temp_a0 > 0 && temp_a0 < D_800DB210.field_8 &&
        temp_a1 > 0 && temp_a1 < D_800DB210.field_C)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool func_800D4924(VECTOR3* vec, q19_12 angle) // 0x800D4924
{
    q19_12 posX;
    q19_12 posZ;

    posX = vec->vx + Q12_MULT_FLOAT_PRECISE(Math_Sin(angle), 1.0f);
    posZ = vec->vz + Q12_MULT_FLOAT_PRECISE(Math_Cos(angle), 1.0f);
    return func_800D48CC(Q12_TO_Q8(posX), Q12_TO_Q8(posZ));
}

void Twinfeeler_Control_10(s_SubCharacter* twinfeeler) // 0x800D49C0
{
    if (twinfeeler->model_0.stateStep_3 == 0)
    {
        twinfeeler->moveSpeed_38            = Q12(1.2f);
        twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_8, false);

        func_800D3AE0(twinfeeler, 4);
        twinfeeler->model_0.stateStep_3++;
    }
    else if (func_800D4924(&twinfeeler->position_18, twinfeeler->rotation_24.vy))
    {
        twinfeeler->model_0.controlState_2 = TwinfeelerControl_4;
        twinfeeler->model_0.stateStep_3    = 0;
    }
}

void Twinfeeler_Control_7(s_SubCharacter* twinfeeler) // 0x800D4A34
{
    if (twinfeeler->model_0.stateStep_3 == 0)
    {
        twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_17, false);
        twinfeeler->moveSpeed_38            = Q12(0.0f);
        twinfeeler->model_0.stateStep_3++;
    }

    if (twinfeeler->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_18, false))
    {
        twinfeeler->model_0.controlState_2 = TwinfeelerControl_8;
        twinfeeler->model_0.stateStep_3    = 0;
    }
}

void Twinfeeler_Control_8(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    MATRIX  sp10;
    VECTOR3 pos; // Q19.12

    if (chara->model_0.stateStep_3 == 0)
    {
        func_800D3AE0(chara, 3);
        chara->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_12, false);

        Vw_CoordHierarchyMatrixCompute(&coords[14], &sp10);

        pos.vx = Q8_TO_Q12(sp10.t[0]);
        pos.vy = Q8_TO_Q12(sp10.t[1]);
        pos.vz = Q8_TO_Q12(sp10.t[2]);

        func_800D46E0(&pos, &g_SysWork.playerWork_4C.player_0.position_18);

        chara->moveSpeed_38 = Q12(0.0f);
        chara->model_0.stateStep_3++;
    }

    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_18, false))
    {
        chara->model_0.controlState_2 = TwinfeelerControl_10;
        chara->model_0.stateStep_3    = 0;
    }
}

void Twinfeeler_Control_4(s_SubCharacter* twinfeeler)
{
    s_SubCharacter* localTwinfeeler;

    localTwinfeeler = twinfeeler;

    if (twinfeeler->model_0.stateStep_3 == 0)
    {
        func_800D3528(twinfeeler);
        twinfeeler->properties_E4.twinfeeler.field_FC = Q12(0.0f);
        func_800D3AE0(twinfeeler, 1);

        twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_2, false);
        twinfeeler->moveSpeed_38            = Q12(0.8877f);
        twinfeeler->model_0.stateStep_3++;
    }

    if (twinfeeler->model_0.stateStep_3 == 1 && twinfeeler->properties_E4.twinfeeler.field_FC >= Q12(1.0f))
    {
        func_800D3B74(twinfeeler);
        twinfeeler->model_0.stateStep_3++;
    }

    if (twinfeeler->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_18, false))
    {
        Sd_SfxStop(Sfx_Unk1559);

        twinfeeler->model_0.controlState_2 = TwinfeelerControl_3;
        twinfeeler->model_0.stateStep_3    = 0;
    }

    localTwinfeeler->properties_E4.twinfeeler.field_FC += g_DeltaTime;
}

bool func_800D4C0C(u32 row, s32 col) // 0x800D4C0C
{
    if (row < 9 && col >= 0 && col < 5)
    {
        if ((D_800DB1A8[row * 5 + col] & 1) == 0)
        {
            return true;
        }
    }

    return false;
}

u16 func_800D4C5C(u8* arg0, s32 arg1, s32 arg2, s32 arg3) // 0x800D4C5C
{
    s32 temp_s1;
    s32 temp_s2;
    s32 i;
    u8  temp_a1;
    s32 temp;
    s32 temp2;
    s32 temp3;
    s32 ret;

    for (i = arg1 - 1; i > 0; i--)
    {
        temp       = (u32)((i + 1) * Rng_Rand16()) >> 16;
        temp_a1    = arg0[i];
        arg0[i]    = arg0[temp];
        arg0[temp] = temp_a1;
    }

    for (i = 0; i < arg1; i++)
    {
        temp = arg0[i];

        temp2 = (temp % 3) - 1;
        temp3 = (temp / 3) - 1;

        temp_s2 = arg2 + temp2;
        temp_s1 = arg3 + temp3;

        if (func_800D4C0C(temp_s2, temp_s1) != 0)
        {
            ret = ((temp_s1 & 0xFFFF) + (temp_s2 << 8));
            return ret;
        }
    }

    return 0xFFFF;
}

s32 func_800D4D80(s32 arg0, s32 arg1) // 0x800D4D80
{
    u8  sp10[16];
    s32 i;
    u8* ptr;

    ptr = &sp10;

    for (i = 0; i < 9; i++)
    {
        if (i != 4)
        {
            *ptr = i;
            ptr += 1;
        }
    }

    return func_800D4C5C(&sp10, 8, arg0, arg1);
}

u32 func_800D4DD8(void) // 0x800D4DD8
{
    s32 var_v0;

    var_v0 = (g_SysWork.playerWork_4C.player_0.rotation_24.vy - 256) & 0xFFF;
    if (var_v0 < 0)
    {
        var_v0 += 0x1FF;
    }

    return var_v0 >> 9;
}

u16 func_800D4E00(s32 arg0, s32 arg1, s32 arg2) // 0x800D4E00
{
    u16 var_a0;

    var_a0 = func_800D4C5C(&D_800DB220[arg2], 3, arg0, arg1);
    if (var_a0 == 0xFFFF)
    {
        var_a0 = func_800D4D80(arg0, arg1);
    }

    return var_a0;
}

s32 func_800D4E78(s32 arg0, s32 arg1) // 0x800D4E78
{
    s32 temp_a3;
    s32 temp_s0;
    s32 temp_s2;
    s32 var_a2;
    s32 var_s0;
    s32 var_s2;
    s32 var_v0_2;
    s32 var_v1;

    temp_s0  = Q12_MULT_PRECISE(arg0, 0x2333);
    temp_s2  = Q12_MULT_PRECISE(Math_Sin(arg1), temp_s0);
    var_v0_2 = Q12_MULT_PRECISE(Math_Cos(arg1), temp_s0);

    var_s2  = var_v0_2 + g_SysWork.playerWork_4C.player_0.position_18.vz;
    var_s0  = g_SysWork.playerWork_4C.player_0.position_18.vx + temp_s2;
    temp_a3 = var_s0 >> 4;

    var_a2 = temp_a3 - 0x7100;

    if (var_a2 < 0)
    {
        var_a2 = temp_a3 - 0x6F01;
    }

    var_s0 = var_a2 >> 9;

    if (var_s0 < 0)
    {
        var_s0 = 0;
    }

    if (var_s0 < 9)
    {
        var_v1 = var_s0;
    }
    else
    {
        var_v1 = 8;
    }

    var_s0 = var_v1;

    var_s2 = ((var_s2 >> 4) - 0x8700) / 0x200;

    if (var_s2 < 0)
    {
        var_s2 = 0;
    }

    if (var_s2 < 5)
    {
        var_v1 = var_s2;
    }
    else
    {
        var_v1 = 4;
    }

    var_s2 = var_v1;

    return func_800D4E00(var_s0, var_s2, 7 - func_800D4DD8());
}

void Twinfeeler_Control_3(s_SubCharacter* chara) // 0x800D4FC0
{
    s16   temp_v0;
    q3_12 angleDeltaToPlayer;
    s16   var_v0_2;

    if (chara->model_0.stateStep_3 == 0)
    {
        chara->properties_E4.twinfeeler.field_FC = Q12(2.0f);
        chara->model_0.anim_4.status_0           = ANIM_STATUS(TwinfeelerAnim_8, false);
        chara->model_0.stateStep_3++;
    }

    func_800D3CBC(chara);

    if (chara->properties_E4.twinfeeler.field_FC < Q12(0.0f))
    {
        temp_v0 = func_800D4488(&chara->position_18,
                                func_800D4E78(g_SysWork.playerWork_4C.player_0.moveSpeed_38, g_SysWork.playerWork_4C.player_0.headingAngle_3C) & 0xFFFF);

        chara->headingAngle_3C = temp_v0;
        chara->rotation_24.vy  = temp_v0;

        angleDeltaToPlayer = func_8005BF38((ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx -
                                                   chara->position_18.vx,
                                               g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) -
                                           temp_v0));

        angleDeltaToPlayer = ABS(angleDeltaToPlayer);

        if (angleDeltaToPlayer >= Q12_ANGLE(45.0f))
        {
            chara->model_0.controlState_2 = TwinfeelerControl_5;
        }
        else
        {
            chara->model_0.controlState_2 = TwinfeelerControl_6;
        }

        chara->model_0.stateStep_3 = 0;
    }

    chara->properties_E4.twinfeeler.field_FC -= g_DeltaTime;
}

void Twinfeeler_Control_2(s_SubCharacter* twinfeeler) // 0x800D50D8
{
    if (twinfeeler->model_0.stateStep_3 == 0)
    {
        twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_13, false);
        twinfeeler->model_0.stateStep_3++;
    }

    if (twinfeeler->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_18, false))
    {
        twinfeeler->model_0.controlState_2     = TwinfeelerControl_4;
        twinfeeler->model_0.stateStep_3 = 0;
        twinfeeler->moveSpeed_38        = Q12(0.0f);
    }
}

void Twinfeeler_Control_9(s_SubCharacter* twinfeeler) // 0x800D511C
{
    s32             temp_s1;
    s_SubCharacter* localTwinfeeler;

    localTwinfeeler = twinfeeler;

    if (twinfeeler->model_0.stateStep_3 == 0)
    {
        Sd_SfxStop(Sfx_Unk1559);

        if (twinfeeler->properties_E4.twinfeeler.field_118 == 0)
        {
            twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_17, false);
            twinfeeler->model_0.stateStep_3     = 1;
        }
        else
        {
            func_800D3AE0(twinfeeler, 0);
            twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_16, false);
            twinfeeler->model_0.stateStep_3     = 2;
        }
    }

    switch (twinfeeler->model_0.stateStep_3)
    {
        case 1:
            if (twinfeeler->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_18, false))
            {
                func_800D3AE0(twinfeeler, 0);
                twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_16, false);
                twinfeeler->model_0.stateStep_3++;
            }
            break;

        case 2:
            if (twinfeeler->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_22, false))
            {
                localTwinfeeler->properties_E4.twinfeeler.field_FC = Q12(5.0f);
                twinfeeler->model_0.stateStep_3++;
            }
            break;

        case 3:
            if (localTwinfeeler->properties_E4.twinfeeler.field_FC < Q12(0.0f))
            {
                twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_11, false);
                twinfeeler->model_0.stateStep_3++;
            }
            break;

        case 4:
            if (twinfeeler->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_18, false))
            {
                twinfeeler->moveSpeed_38            = Q12(1.2f);
                twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_8, false);
                twinfeeler->model_0.stateStep_3++;
            }
            break;

        case 5:
            temp_s1 = func_800D4558(twinfeeler->rotation_24.vy, twinfeeler->position_18.vx, twinfeeler->position_18.vz);
            if (func_800D4924(&twinfeeler->position_18, twinfeeler->rotation_24.vy) ||
                temp_s1 < Q12(2.0f))
            {
                func_800D3528(twinfeeler);
                func_800D3AE0(twinfeeler, 1);

                twinfeeler->model_0.anim_4.status_0 = ANIM_STATUS(TwinfeelerAnim_2, false);
                twinfeeler->moveSpeed_38            = Q12(0.8877f);
                twinfeeler->model_0.stateStep_3++;
            }
            break;

        case 6:
            if (twinfeeler->model_0.anim_4.status_0 == ANIM_STATUS(TwinfeelerAnim_18, false))
            {
                Sd_SfxStop(Sfx_Unk1559);
                Savegame_EventFlagSet(EventFlag_326);

                twinfeeler->model_0.controlState_2 = ANIM_STATUS(TwinfeelerAnim_5, true);
                twinfeeler->model_0.stateStep_3    = 0;
            }
            break;
    }

    if (twinfeeler->model_0.stateStep_3 < 5)
    {
        Chara_MoveSpeedUpdate(twinfeeler, Q12(1.0f));
    }

    localTwinfeeler->properties_E4.twinfeeler.field_FC -= g_DeltaTime;
}

void Twinfeeler_ControlUpdate(s_SubCharacter* twinfeeler, GsCOORDINATE2* coords) // 0x800D53B0
{
    // Handle control state.
    switch (twinfeeler->model_0.controlState_2)
    {
        case TwinfeelerControl_11:
            Twinfeeler_Control_11(twinfeeler);
            break;

        case TwinfeelerControl_12:
            Twinfeeler_Control_12(twinfeeler);
            break;

        case TwinfeelerControl_13:
            Twinfeeler_Control_13(twinfeeler);
            break;

        case TwinfeelerControl_5:
            Twinfeeler_Control_5(twinfeeler);
            break;

        case TwinfeelerControl_6:
            Twinfeeler_Control_6(twinfeeler, coords);
            break;

        case TwinfeelerControl_4:
            Twinfeeler_Control_4(twinfeeler);
            break;

        case TwinfeelerControl_3:
            Twinfeeler_Control_3(twinfeeler);
            break;

        case TwinfeelerControl_7:
            Twinfeeler_Control_7(twinfeeler);
            break;

        case TwinfeelerControl_8:
            Twinfeeler_Control_8(twinfeeler, coords);
            break;

        case TwinfeelerControl_2:
            Twinfeeler_Control_2(twinfeeler);
            break;

        case TwinfeelerControl_9:
            Twinfeeler_Control_9(twinfeeler);
            break;

        case TwinfeelerControl_10:
            Twinfeeler_Control_10(twinfeeler);
            break;
    }
}

void func_800D54B4(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D54B4
{
    VECTOR3         pos; // Q19.12
    MATRIX          sp30;
    s32             var_s0;
    s32             var_v0;
    q19_12          posX;
    q19_12          posY;
    q19_12          posZ;
    s_SubCharacter* localChara;

    localChara = chara;

    // Handle control state.
    switch (chara->model_0.controlState_2)
    {
        case 5:
        case 6:
        case 8:
            var_s0 = 61;
            var_v0 = 14;
            break;

        default:
        case 2:
        case 3:
        case 4:
        case 7:
        case 9:
        case 10:
            var_s0 = 0;
            var_v0 = 0;
            break;
    }

    if (var_s0 != 0)
    {
        Vw_CoordHierarchyMatrixCompute(&coords[var_v0], &sp30);

        posX = Q8_TO_Q12(sp30.t[1]);
        posY = Q8_TO_Q12(sp30.t[0]);
        posZ = Q8_TO_Q12(sp30.t[2]);

        chara->field_C8.field_8 = chara->position_18.vy - posX;

        pos.vx = posY;
        pos.vy = posX;
        pos.vz = posZ;

        if (func_8008A0E4(1, var_s0, chara, &pos, &g_SysWork.playerWork_4C.player_0, chara->rotation_24.vy, Q12_ANGLE(90.0f)) != NO_VALUE)
        {
            localChara->properties_E4.twinfeeler.field_114 |= 1 << 0;
        }
    }
}

void func_800D55C8(s_SubCharacter* chara) // 0x800D55C8
{
    s_800C4590 sp10;
    VECTOR     unkPos; // Q19.12
    VECTOR     sp40;
    VECTOR     sp50;
    q19_12     moveSpeed;
    s32        temp_s0_2;
    q19_12     posComp;
    s32        temp_s2;
    s32        temp_v0;

    unkPos.vx = chara->properties_E4.twinfeeler.field_EC.position_0.vx;
    unkPos.vz = chara->properties_E4.twinfeeler.field_EC.position_0.vz;
    unkPos.vy = chara->properties_E4.twinfeeler.field_EC.position_0.vy;

    moveSpeed                                  = chara->moveSpeed_38;
    chara->properties_E4.twinfeeler.field_108 = moveSpeed;

    sp40.vx = Math_Sin(chara->rotation_24.vy);
    sp40.vz = Math_Cos(chara->rotation_24.vy);
    sp40.vy = Q12(0.0f);

    temp_s2   = Q12_MULT_PRECISE(unkPos.vx, Q12(3.5f)) + Q12_MULT_PRECISE(moveSpeed, sp40.vx);
    temp_v0   = Q12_MULT_PRECISE(unkPos.vy, Q12(3.5f));
    temp_s0_2 = Q12_MULT_PRECISE(unkPos.vz, Q12(3.5f)) + Q12_MULT_PRECISE(moveSpeed, sp40.vz);

    sp50.vx = temp_s2;
    sp50.vy = temp_v0;
    sp50.vz = temp_s0_2;

    chara->moveSpeed_38    = SquareRoot12(Q12_MULT_PRECISE(temp_s2, temp_s2) + Q12_MULT_PRECISE(temp_s0_2, temp_s0_2));
    chara->headingAngle_3C = ratan2(temp_s2, temp_s0_2);
    chara->fallSpeed_34   += g_GravitySpeed;

    if (!(chara->properties_E4.twinfeeler.field_114 & (1 << 2)))
    {
        func_8005C944(chara, &sp10);
    }

    posComp                                             = chara->properties_E4.twinfeeler.field_EC.position_0.vx;
    chara->moveSpeed_38                                    = chara->properties_E4.twinfeeler.field_108;
    chara->properties_E4.twinfeeler.field_EC.position_0.vx = SquareRoot12(Q12_MULT_PRECISE(posComp, posComp) >> g_VBlanks);

    if (posComp <= Q12(0.0f))
    {
        chara->properties_E4.twinfeeler.field_EC.position_0.vx = -chara->properties_E4.twinfeeler.field_EC.position_0.vx;
    }

    posComp                                             = chara->properties_E4.twinfeeler.field_EC.position_0.vy;
    chara->properties_E4.twinfeeler.field_EC.position_0.vy = SquareRoot12(Q12_MULT_PRECISE(posComp, posComp) >> g_VBlanks);

    if (posComp <= Q12(0.0f))
    {
        chara->properties_E4.twinfeeler.field_EC.position_0.vy = -chara->properties_E4.twinfeeler.field_EC.position_0.vy;
    }

    posComp                                             = chara->properties_E4.twinfeeler.field_EC.position_0.vz;
    chara->properties_E4.twinfeeler.field_EC.position_0.vz = SquareRoot12(Q12_MULT_PRECISE(posComp, posComp) >> g_VBlanks);

    if (posComp <= Q12(0.0f))
    {
        chara->properties_E4.twinfeeler.field_EC.position_0.vz = -chara->properties_E4.twinfeeler.field_EC.position_0.vz;
    }

    chara->rotation_24.vy = func_8005BF38(chara->rotation_24.vy);
}

void func_800D5888(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D5888
{
    s_AnimInfo* animInfo;

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coords);

    if (chara->model_0.anim_4.status_0 != ANIM_STATUS(0, false))
    {
        animInfo = &TWINFEELER_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
    }
}

void func_800D5904(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D5904
{
    MATRIX mat;
    q19_12 unkPosY;
    q19_12 unkBasePosY;
    q19_12 posX;
    q19_12 posY;
    q19_12 posZ;

    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(2, true))
    {
        Vw_CoordHierarchyMatrixCompute(&coords[6], &mat);
    }
    else
    {
        Vw_CoordHierarchyMatrixCompute(&coords[14], &mat);
    }

    posY = chara->position_18.vy;
    posX = Q8_TO_Q12(mat.t[0]) - chara->position_18.vx;
    posZ = Q8_TO_Q12(mat.t[2]) - chara->position_18.vz;

    unkBasePosY = Q8_TO_Q12(mat.t[1]) - posY;
    unkPosY = unkBasePosY - Q12(0.25f);
    chara->field_C8.field_0 = unkPosY;
    if (unkPosY >= posY)
    {
        chara->field_C8.field_2 = posY;
    }
    else
    {
        chara->field_C8.field_2 = unkPosY;
    }

    chara->field_C8.field_4 = unkBasePosY + Q12(0.25f);
    chara->field_D4.radius_0 = Q12(0.5f);
    chara->field_C8.field_6 = unkBasePosY;
    chara->field_D4.field_2 = Q12(0.4f);
    sharedFunc_800CD920_3_s03(chara, posX, posZ);

    chara->field_D8.offsetX_0 = chara->field_D8.offsetX_4;
    chara->field_D8.offsetZ_2 = chara->field_D8.offsetZ_6;
}

void func_800D59C0(s_LinkedBone* bone) // 0x800D59C0
{
    s32 i;

    for (i = 0; i < 56; i++)
    {
        bone[i].bone_0.modelInfo_0.field_0 &= ~1;
    }
}

void func_800D59EC(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D59EC
{
    u32           temp_v1;
    s32           temp_v1_3;
    s32           j;
    s32           i;
    s32           idx;
    u32           temp_a0_3;
    s8*           ptr;
    s_LinkedBone* bones;
    s_Bone*       bone;

    bones = WorldGfx_CharaModelBonesGet(Chara_Twinfeeler);

    func_800D59C0(bones);

    temp_v1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);

    if (temp_v1 < 0x20)
    {
        temp_v1_3 = D_800DB27C[temp_v1];

        for (i = temp_v1_3; i < 11; i++)
        {
            ptr = D_800DB238[i];

            for (j = 0; j < 6; j++, ptr++)
            {
                idx = *ptr;

                if (idx == NO_VALUE)
                {
                    break;
                }

                bone                       = &bones[idx - 1].bone_0;
                bone->modelInfo_0.field_0 |= 1 << 0;
            }
        }
    }
    else
    {
        temp_a0_3 = temp_v1 - 0x20;
        if (temp_a0_3 < 41)
        {
            temp_v1_3 = D_800DB2FC[temp_a0_3];

            for (i = 0; i < temp_v1_3; i++)
            {
                ptr = D_800DB238[i];

                for (j = 0; j < 6; j++, ptr++)
                {
                    idx = *ptr;

                    if (idx == NO_VALUE)
                    {
                        break;
                    }

                    bone                       = &bones[idx - 1].bone_0;
                    bone->modelInfo_0.field_0 |= 1 << 0;
                }
            }
        }
    }
}

void func_800D5B6C(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D5B6C
{
    q19_12 posY;

    if (chara->model_0.anim_4.flags_2 & AnimFlag_Visible)
    {
        func_800D5904(chara, coords);
        return;
    }

    posY            = chara->position_18.vy;
    chara->field_C8.field_2 = posY;
    chara->field_C8.field_4 = posY;
    chara->field_C8.field_0 = posY - Q12(1.0f);
    chara->field_C8.field_6 = posY - Q12(0.5f);
}

void func_800D5BC8(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D5BC8
{
    if (chara->model_0.stateStep_3 == 0)
    {
        Twinfeeler_ControlUpdate(chara, coords);
    }
}

bool func_800D5BF8(s32 arg0, s32 arg1, s32 arg2, u16* arg3) // 0x800D5BF8
{
    bool prevBit;
    bool newBit;
    bool bitChanged;

    prevBit    = (*arg3 >> arg0) & 0x1;
    newBit     = (arg2 < arg1);
    bitChanged = prevBit ^ newBit;

    if (newBit)
    {
        *arg3 |= 1 << arg0;
    }
    else
    {
        *arg3 &= ~(1 << arg0);
    }

    return bitChanged;
}

void func_800D5C3C(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D5C3C
{
    s32             temp_s1;
    s32             temp_s2;
    s32             var_a1;
    s32             i;
    s_SubCharacter* localChara;

    u8 D_800CA814[16] = {
        0x1E, 0x20, 0x1C, 0x1A,
        0x18, 0x16, 0x24, 0x22,
        0x28, 0x26, 0x2C, 0x2A,
        0x30, 0x2E, 0x34, 0x32
    };

    s32 D_800CA824[16] = {
        0xFFFFFFE7, 0xFFFFFFE7, 0xFFFFFFE2, 0xFFFFFFE2,
        0xFFFFFFD8, 0xFFFFFFD8, 0xFFFFFFBE, 0xFFFFFFBE,
        0xFFFFFFE2, 0xFFFFFFE2, 0xFFFFFFEC, 0xFFFFFFEC,
        0xFFFFFFE9, 0xFFFFFFE9, 0xFFFFFFE4, 0xFFFFFFE4
    };

    MATRIX sp60;
    VECTOR pos;

    localChara = chara;

    temp_s2  = localChara->properties_E4.twinfeeler.field_114 >> 2;
    temp_s2 ^= 1;
    temp_s2 &= 1;

    Gfx_DebugStringPosition(170, 20);

    for (i = 0; i < 16; i++)
    {
        Vw_CoordHierarchyMatrixCompute(&coords[D_800CA814[i]], &sp60);

        if (func_800D5BF8(i, sp60.t[1], D_800CA824[i], &localChara->properties_E4.twinfeeler.field_E8.val16[1]))
        {
            pos.vx = Q8_TO_Q12(sp60.t[0]);
            pos.vy = Q12(0.0f);
            pos.vz = Q8_TO_Q12(sp60.t[2]);

            if (i < 0)
            {
                var_a1 = i + 3;
            }
            else
            {
                var_a1 = i;
            }

            temp_s1 = (var_a1 >> 2) + (i & 0x1);

            func_800D185C(&pos, temp_s1);

            if (func_800D48CC(sp60.t[0], sp60.t[2]) && temp_s2 != 0)
            {
                func_800D2150(&pos, temp_s1);
            }
        }
    }
}

void func_800D5DF4(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D5DF4
{
    if (g_DeltaTime != Q12(0.0f))
    {
        func_800D5C3C(chara, coords);
    }

    func_800D35DC(&chara->rotation_24);
}

void func_800D5E30(s_SubCharacter* twinfeeler, GsCOORDINATE2* coords) // 0x800D5E30
{
    MATRIX           sp10;
    s32              i;
    q19_12           posY;
    q19_12           newPosX;
    q19_12           newPosY;
    q19_12           newPosZ;
    s_func_8006CF18* ptr;

    ptr = &D_800E04A0;

    twinfeeler->field_E4   = &D_800E04A0;
    twinfeeler->field_E1_4 = 4;

    for (i = 0; i < 4; i++, ptr++)
    {
        Vw_CoordHierarchyMatrixCompute(&coords[D_800DB3A0[i]], &sp10);

        posY    = twinfeeler->position_18.vy;
        newPosX = Q8_TO_Q12(sp10.t[0]);
        newPosY = Q8_TO_Q12(sp10.t[1]);
        newPosZ = Q8_TO_Q12(sp10.t[2]);

        ptr->field_10      = Q12(0.45f);
        ptr->field_E       = newPosY - Q12(0.3f);
        ptr->field_C       = posY;
        ptr->position_0.vx = newPosX;
        ptr->position_0.vy = newPosY;
        ptr->position_0.vz = newPosZ;
        ptr->field_12      = 3;
    }
}

void Twinfeeler_Update(s_SubCharacter* twinfeeler, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D5F28
{
    if (twinfeeler->model_0.controlState_2 == ModelState_Uninitialized)
    {
        Twinfeeler_TextureLoad(); // Just calls `Fs_QueueStartReadTim`.
        twinfeeler->model_0.controlState_2 = TwinfeelerControl_1;
        twinfeeler->model_0.stateStep_3 = 0;
    }

    if (twinfeeler->model_0.controlState_2 != TwinfeelerControl_1 || Twinfeeler_Init(twinfeeler))
    {
        if (g_DeltaTime != Q12(0.0f))
        {
            func_800D3E58(twinfeeler);
            Twinfeeler_ControlUpdate(twinfeeler, coords);
            func_800D55C8(twinfeeler);
            func_800D5BC8(twinfeeler, coords);
            func_800D5888(twinfeeler, anmHdr, coords);
            func_800D5B6C(twinfeeler, coords);
            func_800D54B4(twinfeeler, coords);
            func_800D5DF4(twinfeeler, coords);
            func_800D59EC(twinfeeler, coords);
            func_800D5E30(twinfeeler, coords);
            func_800D3B44(twinfeeler->flags_3E & CharaFlag_Unk2);

            if (twinfeeler->model_0.controlState_2 != TwinfeelerControl_10)
            {
                Sd_SfxStop(Sfx_Unk1567);
            }
        }
        else
        {
            func_800D5888(twinfeeler, anmHdr, coords);
            func_800D5DF4(twinfeeler, coords);
        }
    }
}

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D606C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D607C

#include "maps/shared/Map_RoomBgmInit_4_s02.h" // 0x800D6278

void func_800D654C(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D6554

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D65E8

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tDaddy...where_are_you...? ",
    "~J0(1.0)\tCheryl! ~E  ",
    "\tThere_is_a_ ~C2 Hunting_rifle ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tNothing_unusual. ~E ",
    "\tA_picture_is_projected ~N\n\ton_the_screen. ",
    "\tCheryl... ~N\n\twhere_could_she_be? ~E "
};

void MapEvent_CommonItemTake(void) // 0x800D667C
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 27:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M4S03_FirstAidKit;
            break;

        case 28:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M4S03_RifleShells0;
            break;

        case 29:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M4S03_RifleShells1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800D6704(void) // 0x800D6704
{
    s32 i;

    // Breaks from loop if there are any characters with ID in range [1, 24].
    for (i = 0; i < 6; i++)
    {
        if (g_SysWork.npcs_1A0[i].model_0.charaId_0 >= Chara_Harry &&
            g_SysWork.npcs_1A0[i].model_0.charaId_0 <= Chara_MonsterCybil)
        {
            break;
        }
    }

    if (i != 6)
    {
        g_DeltaTime = Q12(0.0f);
    }

    Event_ItemTake(InventoryItemId_HuntingRifle, RIFLE_AMMO_PICKUP_ITEM_COUNT, EventFlag_M4S03_PickupHuntingRifle, 17);
}

void func_800D6774(void) // 0x800D6774
{
    s_Collision coll;
    VECTOR3     vec;
    s32         i;

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 11)
    {
        SysWork_StateStepSet(0, 12);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(120.5f), Q12(-9.5f), Q12(137.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vy, g_SysWork.playerWork_4C.player_0.position_18.vz,
                             Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            D_800DB9E0 = Q12(0.0f);
            break;

        case 1:
        case 2:
            Camera_PositionSet(NULL, Q12(120.5f), Q12(-5.5f), Q12(138.0f), Q12(0.0f), Q12(0.0f), cam_mv_prm_user.max_spd_xz >> 3, cam_mv_prm_user.max_spd_y >> 1, false);
            D_800DB9E0 += g_DeltaTime;

            if (D_800DB9E0 >= Q12(1.8f))
            {
                break;
            }

            i = Rng_Rand16() % (((Q12(2.5f) - D_800DB9E0) / Q12(0.5f)) + 1);
            for (; i > 0; i--)
            {
                vec.vx = Rng_GenerateInt(Q12(118.0f), Q12(123.0f) - 1);
                vec.vy = 0;
                vec.vz = Rng_GenerateInt(Q12(140.0f), Q12(143.0f) - 1);
                func_800D19AC(&vec);
            }
            break;

        case 3:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(119.48f), Q12(-0.5f), Q12(143.35f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(118.16f), Q12(-0.86f), Q12(139.59f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            break;

        case 9:
        case 10:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(119.87f), Q12(-3.4f), Q12(138.71f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(119.13f), Q12(-1.49f), Q12(142.15f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            break;
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            Game_TurnFlashlightOn();

            Gfx_MapInitMapEffectsUpdate(6, 3);

            if (Savegame_EventFlagGet(EventFlag_322))
            {
                func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 129, false);
            }
            else
            {
                func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 128, false);
            }

            Collision_Get(&coll, g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz);
            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();

            g_SysWork.playerWork_4C.player_0.position_18.vy = coll.groundHeight_0;

            func_8005DC1C(Sfx_Unk1556, &QVECTOR3(119.5f, 0.0f, 141.5f), Q8_CLAMPED(0.5f), 0);
            func_80089470();
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            func_80085EB8(2, &g_SysWork.playerWork_4C.player_0, 0, false);
            break;

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(4.5f), false);
            break;

        case 3:
            func_800D3FB0(&g_SysWork.npcs_1A0[0]);
            Savegame_EventFlagSet(EventFlag_329);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementDelayed(Q12(0.7f), false);
            break;

        case 5:
            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);
            SysWork_StateStepIncrement(0);

        case 6:
            func_80085EB8(1, &g_SysWork.playerWork_4C.player_0, 0, false);
            break;

        case 7:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 123, false);
            SysWork_StateStepIncrement(0);

        case 8:
            SysWork_StateStepIncrementDelayed(Q12(2.4f), false);
            break;

        case 9:
            Player_ControlUnfreeze(true);
            Player_ControlFreeze();
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 52, false);

            g_SysWork.playerWork_4C.player_0.position_18.vx += Q12(0.5f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy += Q12_ANGLE(45.0f);

            SysWork_StateStepIncrement(0);

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(3.5f), false);
            break;

        case 11:
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepReset();
            break;

        case 12:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);

            if (g_SysWork.sysStateStep_C[0] != 12)
            {
                // Warp camera.
                Camera_PositionSet(NULL, Q12(119.87f), Q12(-3.4f), Q12(138.71f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
                Camera_LookAtSet(NULL, Q12(119.13f), Q12(-1.49f), Q12(142.15f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

                func_800D3E18(&g_SysWork.npcs_1A0[0]);
                func_800D4000(&g_SysWork.npcs_1A0[0]);
            }
            break;

        case 13:
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(120.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(141.5f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(-45.0f);

            Savegame_EventFlagSet(EventFlag_329);

            // Return to gameplay.
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            func_800D4000(&g_SysWork.npcs_1A0[0]);
            Savegame_EventFlagSet(EventFlag_324);
            func_8003A16C();
            break;
    }
}

void func_800D6F24(void) // 0x800D6F24
{
    s32   var_a0;
    s32   var_a0_2;
    s32   var_a2;
    s32   var_v0;
    void* var_s0;

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 9)
    {
        SysWork_StateStepSet(0, 9);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 2, Q12(0.0f), false);
            break;

        case 3:
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(124.4f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(140.9f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(90.0f);

            Camera_PositionSet(NULL, Q12(122.1f), Q12(-4.34f), Q12(141.87f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(125.65f), Q12(-2.74f), Q12(140.95f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 4:
            func_800D3FD8(&g_SysWork.npcs_1A0[0]);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 6:
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);

            Savegame_EventFlagSet(EventFlag_327);

            Camera_PositionSet(NULL, Q12(128.82f), Q12(-0.26f), Q12(139.1f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(125.24f), Q12(-0.8f), Q12(140.79f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_8005DC1C(Sfx_Unk1554, &QVECTOR3(132.0f, -0.75f, 140.0f), Q8_CLAMPED(0.5f), 0);

            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 8:
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(126.86f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(140.36f);

            Camera_PositionSet(NULL, Q12(122.55f), Q12(-2.1f), Q12(138.5f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(126.39f), Q12(-1.73f), Q12(139.56f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrementDelayed(Q12(3.5f), false);

            if (g_SysWork.sysStateStep_C[0] != 8)
            {
                SysWork_StateStepReset();
            }
            break;

        case 9:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 10:
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(126.86f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(140.36f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(90.0f);

            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);

            Savegame_EventFlagSet(EventFlag_327);

            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            func_8003A16C();
            break;
    }
}

s16 func_800D7394(void) // 0x800D7394
{
    if (g_DeltaTime != Q12(0.0f))
    {
        D_800DB914 = ((s32)(D_800DB918 * 0x7169AC35) >> 3) ^ 0xA547B39E;
        D_800DB918 = ((u32)(D_800DB914 * 0x892D719C) >> 3) ^ 0xC65A4B97;
    }

    return (u16)D_800DB914 & SHRT_MAX;
}

void func_800D7408(void) // 0x800D7408
{
    D_800E0698.field_0 = 0;
    D_800E0698.field_4 = 0;

    func_800D7450();
    func_800D7548();

    WorldObject_ModelNameSet(&D_800E0698.objRef_238, "REF_NEAR");
}

void func_800D7450(void) // 0x800D7450
{
    e_FsFile texFileIdx;
    s32      i;

    texFileIdx = NO_VALUE;

    for (i = 0; i < 3; i++)
    {
        switch (i)
        {
            case 0:
                texFileIdx          = FILE_TIM_TV1_TIM;
                D_800DB91C.tPage[1] = 29;
                D_800DB91C.u        = 0;
                D_800DB91C.v        = 0;
                D_800DB91C.clutY    = 0;
                break;

            case 1:
                texFileIdx          = FILE_TIM_TV2_TIM;
                D_800DB91C.tPage[1] = 12;
                D_800DB91C.u        = 32;
                D_800DB91C.v        = 0;
                D_800DB91C.clutY    = 5;
                break;

            case 2:
                texFileIdx          = FILE_TIM_TV3_TIM;
                D_800DB91C.tPage[1] = 28;
                D_800DB91C.v        = 128;
                D_800DB91C.u        = 0;
                D_800DB91C.clutY    = 10;
                break;
        }

        Fs_QueueStartReadTim(texFileIdx, FS_BUFFER_1, &D_800DB91C);
    }
}

void func_800D7548(void) // 0x800D7548
{
    s32 i;
    s32 j;

    func_800D761C(&D_800E0698.field_8[9], &D_800DB7D4, 1, 0);

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            func_800D761C(&D_800E0698.field_8[(i * 3) + j], &D_800DB7E4[i][j], 0, 0);
        }
    }
}

void func_800D761C(s_800E06A0* arg0, s_800DB7D4* arg1, s8 arg2, s32 arg3) // 0x800D761C
{
    arg0->field_20    = arg2;
    arg0->field_22    = 0;
    arg0->field_24    = 0;
    arg0->field_23    = 0;
    arg0->field_2C    = 0;
    arg0->field_21    = 0;

    arg0->field_0[0] = arg1->field_0;
    arg0->field_0[3] = arg1->field_8;

    // Switches `vy` to the other arg1 field?
    arg0->field_0[1].vx = arg1->field_8.vx;
    arg0->field_0[1].vy = arg1->field_0.vy;
    arg0->field_0[1].vz = arg1->field_8.vz;
    arg0->field_0[2].vx = arg1->field_0.vx;
    arg0->field_0[2].vy = arg1->field_8.vy;
    arg0->field_0[2].vz = arg1->field_0.vz;
}

void func_800D76BC(s32 arg0) // 0x800D76BC
{
    D_800E0698.field_0 = arg0;
    D_800E0698.field_4 = 0;

    func_800D7548();
}

bool func_800D76E8(void) // 0x800D76E8
{
    s32  i;
    bool result;

    result = true;

    for(i = 0; i < ARRAY_SIZE(D_800E0698.field_8); i++)
    {
        result &= D_800E0698.field_8[i].field_21;
    }

    return result;
}

void func_800D7718(void) // 0x800D7718
{
    MATRIX      mat;
    s16         temp_v0;
    s32         var_s2;
    s32         i;
    s_800E06A0* ptr;

    func_80049C2C(&mat, Q12(160.0f), Q12(0.0f), Q12(40.0f));
    SetRotMatrix(&mat);
    SetTransMatrix(&mat);

    var_s2 = 188;
    if (D_800E0698.field_0 != 0)
    {
        if (g_DeltaTime != Q12(0.0f))
        {
            D_800DB924.pad++;
            if (!(D_800DB924.pad & 0xB))
            {
                var_s2 = 164;
            }
        }

        WorldGfx_ObjectAdd(&D_800E0698.objRef_238, &D_800DB7C8, (SVECTOR3*)&D_800DB924);
    }

    for (i = 0; i < ARRAY_SIZE(D_800E0698.field_8); i++)
    {
        func_800D7808(&D_800E0698.field_8[i], i);
        func_800D88C8(&D_800E0698.field_8[i], var_s2);
    }
}

void func_800D7808(s_800E06A0* arg0, s32 arg1) // 0x800D7808
{
    s32 temp;

    if (g_DeltaTime == 0)
    {
        return;
    }

    temp = D_800E0698.field_0;
    switch (D_800E0698.field_0)
    {
        case 0:
            func_800D78D4(arg0);
            break;

        case 1:
            if (func_800D78F4(arg0, arg1) != 0)
            {
                arg0->field_21 = temp;
            }
            break;

        case 2:
            if (func_800D7AE0(arg0) != 0)
            {
                func_800D76BC(3);
            }
            break;

        case 3:
            func_800D7F1C(arg0);
            break;
    }
}

bool func_800D78D4(s_800E06A0* arg0) // 0x800D78D4
{
    return func_800D81FC(arg0, 0);
}

const u32 D_800CACA8[10] = {
    0x00000B33,
    0x00001E66,
    0x00001999,
    0x00001B33,
    0x00002333,
    0x00000E66,
    0x00001E66,
    0x00001800,
    0x00001CCC,
    0x000004CC,
};

s32 func_800D78F4(s_800E06A0* arg0, s32 arg1) // 0x800D78F4
{
    u32 sp10[10];
    s32 var_s0;
    s32 var_s2;

    var_s0 = 0;
    var_s2 = 0;

    switch (arg0->field_22)
    {
        case 0:
        default:
            memcpy(&sp10, &D_800CACA8, sizeof(D_800CACA8));
            var_s0 = func_800D81FC(arg0, sp10[arg1] + 2048);
            break;

        case 1:
            var_s0 = func_800D826C(arg0, 0, 409);
            break;

        case 2:
            var_s0 = func_800D826C(arg0, 1, 409);
            break;

        case 3:
            var_s0 = func_800D826C(arg0, 3, 955);
            break;

        case 4:
            var_s0 = func_800D826C(arg0, 4, 546);
            break;

        case 5:
            var_s0 = func_800D8620(arg0, 0, 6144);
            break;

        case 6:
            var_s0 = func_800D826C(arg0, 2, 682);
            break;

        case 7:
            var_s0 = func_800D8354(arg0, 1, 8192);
            break;

        case 8:
            var_s0 = func_800D826C(arg0, 3, 1365);
            break;

        case 9:
            var_s0 = func_800D84C0(arg0, 0, 9011);
            break;

        case 10:
            var_s0 = func_800D826C(arg0, 4, 1365);
            break;

        case 11:
            var_s0 = func_800D85E4(arg0, 409);
            break;

        case 12:
            var_s0 = func_800D826C(arg0, 3, 1365);
            break;

        case 13:
            var_s2 = func_800D84C0(arg0, 1, 2048);
            break;
    }

    arg0->field_24 += g_DeltaTime;

    if (var_s0 != 0)
    {
        arg0->field_22++;
        arg0->field_24 = 0;
    }

    return var_s2;
}

s32 func_800D7AE0(s_800E06A0* arg0) // 0x800D7AE0
{
    s32 var_s0;
    s32 var_s2;

    var_s0 = false;
    var_s2 = false;

    switch (arg0->field_22)
    {
        case 0:
            var_s0 = func_800D84C0(arg0, 0, (func_800D7394() >> 5) + 0x1199);
            break;

        case 1:
            var_s0 = func_800D826C(arg0, 4, (func_800D7394() >> 5) + 0x555);
            break;

        case 2:
            var_s0 = func_800D8620(arg0, 1, (func_800D7394() >> 5) + 0x1800);
            break;

        case 3:
            var_s0 = func_800D826C(arg0, 3, (func_800D7394() >> 5) + 0x555);
            break;

        case 4:
            var_s0 = func_800D8230(arg0, 0, (func_800D7394() >> 5) + 0x2AA);
            break;

        case 5:
            var_s0 = func_800D826C(arg0, 3, (func_800D7394() >> 5) + 0x555);
            break;

        case 6:
            var_s0 = func_800D8230(arg0, 1, (func_800D7394() >> 5) + 0xAAA);
            break;

        case 7:
            var_s0 = func_800D826C(arg0, 4, (func_800D7394() >> 5) + 0x555);
            break;

        case 8:
            var_s0 = func_800D8230(arg0, 2, (func_800D7394() >> 5) + 0x1000);
            break;

        case 9:
            var_s0 = func_800D826C(arg0, 3, (func_800D7394() >> 5) + 0x555);
            break;

        case 10:
            var_s0 = func_800D8230(arg0, 3, (func_800D7394() >> 5) + 0xAAA);
            break;

        case 11:
            var_s0 = func_800D826C(arg0, 4, (func_800D7394() >> 5) + 0x555);
            break;

        case 12:
            var_s0 = func_800D8230(arg0, 4, (func_800D7394() >> 5) + 0x2AA);
            break;

        case 13:
            var_s0 = func_800D8230(arg0, 5, (func_800D7394() >> 5) + 0xAAA);
            break;

        case 14:
            var_s0 = func_800D826C(arg0, 3, (func_800D7394() >> 5) + 0x555);
            break;

        case 15:
            var_s0 = func_800D8230(arg0, 6, (func_800D7394() >> 5) + 0x2AA);
            break;

        case 16:
            var_s0 = func_800D826C(arg0, 4, (func_800D7394() >> 5) + 0x555);
            break;

        case 17:
            var_s0 = func_800D8230(arg0, 7, (func_800D7394() >> 5) + 0xD55);
            break;

        case 18:
            var_s0 = func_800D826C(arg0, 3, (func_800D7394() >> 5) + 0x555);
            break;

        case 19:
            var_s0 = func_800D8230(arg0, 6, (func_800D7394() >> 5) + 0xAAA);
            break;

        case 20:
            var_s0 = func_800D826C(arg0, 4, (func_800D7394() >> 5) + 0x555);
            break;

        case 21:
            var_s0 = func_800D8230(arg0, 8, (func_800D7394() >> 5) + 0x1555);
            break;

        case 22:
            var_s0 = func_800D826C(arg0, 4, (func_800D7394() >> 5) + 0x444);
            break;

        case 24:
            var_s0 = func_800D8620(arg0, 2, (func_800D7394() >> 5) + 0x1800);
            break;

        case 25:
            var_s0 = func_800D85E4(arg0, (func_800D7394() >> 5) + 0x199);
            break;

        case 26:
            var_s0 = func_800D826C(arg0, 4, (func_800D7394() >> 5) + 0x444);
            break;

        case 23:
        case 27:
            var_s0 = func_800D826C(arg0, 3, (func_800D7394() >> 5) + 0x2AA);
            break;

        case 28:
            var_s2 = func_800D8620(arg0, 0, (func_800D7394() >> 5) + 0x1800);
            break;
    }

    arg0->field_24 += g_DeltaTime;

    if (var_s0)
    {
        arg0->field_24  = 0;
        arg0->field_22 += 1;
    }

    return var_s2;
}

void func_800D7F1C(s_800E06A0* arg0) // 0x800D7F1C
{
    s32 var_s0;
    s32 var_s2;

    var_s0 = 0;
    var_s2 = 0;

    switch (arg0->field_22)
    {
        case 0:
        default:
            var_s0 = func_800D8620(arg0, -1, 0xAAA);
            break;

        case 0xA:
            var_s0 = func_800D8620(arg0, -1, 0xAAA);
            break;

        case 0x14:
            var_s0 = func_800D8620(arg0, -1, 0xD55);
            break;

        case 0x1E:
            var_s0 = func_800D8620(arg0, -1, 0x1000);
            break;

        case 0x28:
            var_s0 = func_800D8620(arg0, -1, 0x12AA);
            break;

        case 0x32:
            var_s0 = func_800D8620(arg0, -1, 0x1555);
            break;

        case 0x3C:
            var_s0 = func_800D8354(arg0, 0, 0x1AAA);
            break;

        case 0x46:
            var_s0 = func_800D8354(arg0, 0, 0x1AAA);
            break;

        case 0x50:
            var_s2 = func_800D826C(arg0, 4, 0x3BB);
            break;

        case 0x51:
            var_s0 = func_800D8230(arg0, 0, 0x2AA);
            break;

        case 0x5A:
            var_s2 = func_800D826C(arg0, 3, 0x444);
            break;

        case 0x5B:
            var_s0 = func_800D8230(arg0, 1, 0xAAA);
            break;

        case 0x64:
            var_s2 = func_800D826C(arg0, 4, 0x444);
            break;

        case 0x65:
            var_s0 = func_800D8230(arg0, 2, 0x1000);
            break;

        case 0x6E:
            var_s2 = func_800D826C(arg0, 3, 0x444);
            break;

        case 0x6F:
            var_s0 = func_800D8230(arg0, 3, 0xAAA);
            break;

        case 0x78:
            var_s2 = func_800D826C(arg0, 4, 0x444);
            break;

        case 0x79:
            var_s2 = func_800D8230(arg0, 4, 0x2AA);
            break;

        case 0x7A:
            var_s0 = func_800D8230(arg0, 5, 0xAAA);
            break;

        case 0x82:
            var_s2 = func_800D826C(arg0, 3, 0x555);
            break;

        case 0x83:
            var_s0 = func_800D8230(arg0, 6, 0x2AA);
            break;

        case 0x8D:
            var_s0 = func_800D8230(arg0, 7, 0xD55);
            break;

        case 0x96:
            var_s2 = func_800D826C(arg0, 3, 0x555);
            break;

        case 0x97:
            var_s0 = func_800D8230(arg0, 6, 0xAAA);
            break;

        case 0x8C:
        case 0xA0:
            var_s2 = func_800D826C(arg0, 4, 0x555);
            break;

        case 0xA1:
            var_s0 = func_800D8230(arg0, 8, 0x1000);
            break;
    }

    arg0->field_24 += g_DeltaTime;

    if (var_s2 != 0)
    {
        arg0->field_22++;
        arg0->field_24 = 0;
    }

    if (var_s0 != 0)
    {
        arg0->field_22 = (func_800D7394() % 17) * 10;
        arg0->field_24 = 0;
    }
}

bool func_800D81FC(s_800E06A0* arg0, s32 arg1) // 0x800D81FC
{
    if (arg0->field_24 == 0)
    {
        arg0->field_28 = arg1;
    }

    arg0->field_30 = 0;
    arg0->field_34 = 0;
    arg0->field_36 = 0;

    return arg0->field_24 >= arg0->field_28;
}

bool func_800D8230(s_800E06A0* arg0, s32 arg1, s32 arg2) // 0x800D8230
{
    if (arg0->field_24 == 0)
    {
        arg0->field_28 = arg2;
    }

    arg0->field_30 = arg1 + 6;
    arg0->field_36 = 0;
    arg0->field_34 = 0;

    return arg0->field_24 >= arg0->field_28;
}

bool func_800D826C(s_800E06A0* arg0, s32 arg1, s32 arg2) // 0x800D826C
{
    if (arg0->field_24 == 0)
    {
        arg0->field_28 = arg2;
    }

    arg0->field_30 = 4;
    arg0->field_34 = 0;

    switch (arg1)
    {
        default:
        case 0:
            arg0->field_36 = 0;
            break;

        case 1:
            arg0->field_36 = 64;
            break;

        case 2:
            arg0->field_36 = 32;
            break;

        case 4:
            arg0->field_36 = (u32)((MIN(arg2, arg0->field_24) << 12) / arg2) >> 6; // TODO: Weird shifts, not sure if these are FP related?
            break;

        case 3:
            arg0->field_36 = 64 - ((((MIN(arg2, arg0->field_24) << 12) / arg2) << 6) >> 12);
            break;
    }

    return arg0->field_24 >= arg0->field_28;
}

bool func_800D8354(s_800E06A0* arg0, s32 arg1, s32 arg2) // 0x800D8354
{
    s32 sp10[4];
    s32 temp_a0;
    s32 var_t0;
    s32 var_v1;

    if (arg1 != 0)
    {
        var_t0 = 1;
    }
    else
    {
        var_t0 = (func_800D7394() & 0xFFF) < 0x199;
    }

    if (arg0->field_24 == 0)
    {
        arg0->field_28 = arg2;
    }

    arg0->field_36 = 0;
    arg0->field_34 = 0;
    sp10[0]        = arg2 - 0x555;

    sp10[0] = CLAMP(sp10[0], 0, 0x111);
    var_v1  = Q12_MULT(arg2, 0x4CC);

    if (var_v1 > 0x5DD)
    {
        var_v1 = 0x5DD;
    }

    sp10[1] = var_v1 + sp10[0];
    sp10[2] = sp10[1] + 0x3BB;
    sp10[3] = sp10[1] + 0x45E;

    var_v1 = arg0->field_24;

    if (sp10[0] >= arg0->field_24)
    {
        arg0->field_30 = 2;
        temp_a0        = sp10[0];

        if (var_v1 <= temp_a0)
        {
            var_v1 = var_v1 << 0xC;
        }
        else
        {
            var_v1 = temp_a0 << 0xC;
        }
        arg0->field_36 = Q12_MULT(var_v1 / temp_a0, 0x19) - 0x20;
    }
    else
    {
        if (var_v1 < sp10[1])
        {
            arg0->field_30 = 2;
        }
        else if (var_v1 < sp10[2] || var_t0 == 0 || var_v1 >= sp10[3])
        {
            arg0->field_30 = 3;
        }
        else
        {
            arg0->field_30 = 2;
        }
    }
    return arg0->field_24 >= arg2;
}

bool func_800D84C0(s_800E06A0* arg0, s32 arg1, s32 arg2) // 0x800D84C0
{
    if (arg0->field_24 == 0)
    {
        arg0->field_28 = arg2;
    }

    arg0->field_34 = 0;

    switch (arg1)
    {
        case 0:
        default:
            arg0->field_30 = 5;
            arg0->field_36 = (FP_TO(arg0->field_24 % Q12((1.0f / 3.0f) * 2.0f), Q12_SHIFT) / Q12((1.0f / 3.0f) * 2.0f)) >> 6;

            if (arg0->field_36 > 24 && arg0->field_36 < 29)
            {
                arg0->field_36 = 32;
            }
            break;

        case 1:
            arg0->field_30 = 5;
            arg0->field_34 = func_800D7394() % 6;
            arg0->field_36 = 32;
            break;
    }

    return !(arg0->field_24 < arg0->field_28);
}

bool func_800D85E4(s_800E06A0* arg0, s32 arg1) // 0x800D85E4
{
    if (arg0->field_24 == 0)
    {
        arg0->field_28 = arg1;
    }

    arg0->field_30 = 15;
    arg0->field_36 = 0;
    arg0->field_34 = 0;

    return arg0->field_24 >= arg0->field_28;
}

bool func_800D8620(s_800E06A0* arg0, s32 arg1, s32 arg2) // 0x800D8620
{
    if (arg0->field_24 == 0)
    {
        arg0->field_28 = arg2;
    }

    if (arg1 == NO_VALUE)
    {
        arg1 = func_800D87AC(arg0);
    }

    switch (arg1 + 1)
    {
        default:
        case 0:
            arg0->field_30 = 1;
            arg0->field_34 = 0;
            arg0->field_36 = 0;
            break;

        case 2:
            arg0->field_30 = 1;
            arg0->field_34 = 50;
            arg0->field_36 = 24;
            break;

        case 3:
            arg0->field_30 = 1;
            arg0->field_34 = 128;
            arg0->field_36 = 0;
            break;

        case 4:
            arg0->field_34 = 0;
            arg0->field_30 = 4;
            arg0->field_36 = FP_FROM(-(Q12_DIV(arg0->field_24 % Q12(1.5f), Q12(1.5f)) * 80), Q12_SHIFT) - 108;
            break;

        case 5:
            arg0->field_30 = 1;
            arg0->field_34 = 0;
            arg0->field_36 = 0;
            arg0->field_36 = func_800D7394() % 320;
            break;
    }

    return !(arg0->field_24 < arg0->field_28);
}

s32 func_800D87AC(s_800E06A0* arg0) // 0x800D87AC
{
    s32  temp_v1_2;
    bool cond;

    cond = false;
    if (arg0->field_24 == 0)
    {
        cond           = true;
        arg0->field_2C = func_800D8874();
    }
    else if (arg0->field_24 >= arg0->field_2C)
    {
        cond            = true;
        arg0->field_2C += func_800D8874();
    }

    if (cond)
    {
        temp_v1_2 = Q12_FRACT(func_800D7394());
        if (temp_v1_2 < Q12(0.3f))
        {
            arg0->field_23 = 0;
        }
        else if (temp_v1_2 < Q12(0.5f))
        {
            arg0->field_23 = 1;
        }
        else if (temp_v1_2 < Q12(0.77f))
        {
            arg0->field_23 = 2;
        }
        else if (temp_v1_2 < Q12(0.83f))
        {
            arg0->field_23 = 3;
        }
        else
        {
            arg0->field_23 = 4;
        }
    }

    return arg0->field_23;
}

q19_12 func_800D8874(void) // 0x800D8874
{
    q3_12 temp;
    q3_12 temp2;

    temp2 = Q12_FRACT(func_800D7394());
    temp  = Q12(0.5f);

    return Q12_MULT_PRECISE(temp, temp2) + Q12(1.0f);
}

void func_800D88C8(s_800E06A0* arg0, u8 arg1) // 0x800D88C8
{
    typedef struct
    {
        SVECTOR field_0;
        u16     field_8;
        u16     field_A;
    } s_func_800D88C8;

    SVECTOR         sp10[4];
    s_func_800D88C8 sp30[3][3];
    s32             spA0;
    u16             spA8;
    s32             spB0;
    s32             j;
    s32             temp_a2;
    s32             i;
    s32             var_t0;
    s32             k;
    s32             temp_s4;
    s32             temp_s6;
    s32             temp;
    s_800DB874*     temp_fp;
    POLY_FT4*       poly;
    POLY_FT4*       poly2;

    temp_fp = &D_800DB874[arg0->field_30];

    spA8  = temp_fp->field_0 & 0x10;
    temp  = (temp_fp->field_0 & 0xF) | 0x20;
    spA8 |= temp;

    temp_s6 = arg0->field_34 + temp_fp->field_4 + func_800D7394() % (temp_fp->field_8 + 1);
    spB0    = arg0->field_34 + temp_fp->field_4 + func_800D7394() % (temp_fp->field_8 + 1) + temp_fp->field_6 - 1;
    temp_s4 = arg0->field_36 + temp_fp->field_5 + func_800D7394() % (temp_fp->field_9 + 1);
    var_t0  = temp_s4 + temp_fp->field_7 - 1;

    for (i = 0; i < ARRAY_SIZE(arg0->field_0); i++)
    {
        sp10[i].vz = RotTransPers(&arg0->field_0[i], &sp10[i], &spA0, &spA0) * 4;
    }

    if (arg0->field_20 == 0)
    {
        temp_a2 = MAX(sp10[0].vz, sp10[1].vz);
        temp_a2 = MAX(temp_a2, sp10[2].vz);
        temp_a2 = MAX(temp_a2, sp10[3].vz) >> 3;

        if (temp_a2 > 0 && temp_a2 < ORDERING_TABLE_SIZE - 1)
        {
            poly = GsOUT_PACKET_P;

            setPolyFT4(poly);
            setRGB0(poly, arg1, arg1, arg1);

            *(s32*)&poly->x0 = *(s32*)&sp10[0];
            *(s32*)&poly->x1 = *(s32*)&sp10[1];

            do {} while (0); // @hack

            *(s32*)&poly->x2 = *(s32*)&sp10[2];
            *(s32*)&poly->x3 = *(s32*)&sp10[3];

            setUV4(poly,
                   temp_s6, temp_s4,
                   spB0, temp_s4,
                   temp_s6, var_t0,
                   spB0, var_t0);

            poly->tpage = spA8;
            poly->clut  = temp_fp->field_2;
            AddPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[temp_a2], poly);
            GsOUT_PACKET_P = poly + 1;
        }
    }
    else
    {
        sp30[0][0].field_0 = sp10[0];
        sp30[0][0].field_8 = temp_s6;
        sp30[0][0].field_A = temp_s4;

        sp30[0][2].field_0 = sp10[1];
        sp30[0][2].field_8 = spB0;
        sp30[0][2].field_A = temp_s4;

        sp30[2][0].field_0 = sp10[2];
        sp30[2][0].field_8 = temp_s6;
        sp30[2][0].field_A = var_t0;

        sp30[2][2].field_0 = sp10[3];
        sp30[2][2].field_8 = spB0;
        sp30[2][2].field_A = var_t0;

        sp30[0][1].field_0.vx = (sp30[0][0].field_0.vx + sp30[0][2].field_0.vx) >> 1;
        sp30[0][1].field_0.vy = (sp30[0][0].field_0.vy + sp30[0][2].field_0.vy) >> 1;
        sp30[0][1].field_0.vz = (sp30[0][0].field_0.vz + sp30[0][2].field_0.vz) >> 1;
        sp30[0][1].field_8    = (sp30[0][0].field_8 + sp30[0][2].field_8) >> 1;
        sp30[0][1].field_A    = (sp30[0][0].field_A + sp30[0][2].field_A) >> 1;

        sp30[1][0].field_0.vx = (sp30[0][0].field_0.vx + sp30[2][0].field_0.vx) >> 1;
        sp30[1][0].field_0.vy = (sp30[0][0].field_0.vy + sp30[2][0].field_0.vy) >> 1;
        sp30[1][0].field_0.vz = (sp30[0][0].field_0.vz + sp30[2][0].field_0.vz) >> 1;
        sp30[1][0].field_8    = (sp30[0][0].field_8 + sp30[2][0].field_8) >> 1;
        sp30[1][0].field_A    = (sp30[0][0].field_A + sp30[2][0].field_A) >> 1;

        sp30[1][2].field_0.vx = (sp30[0][2].field_0.vx + sp30[2][2].field_0.vx) >> 1;
        sp30[1][2].field_0.vy = (sp30[0][2].field_0.vy + sp30[2][2].field_0.vy) >> 1;
        sp30[1][2].field_0.vz = (sp30[0][2].field_0.vz + sp30[2][2].field_0.vz) >> 1;
        sp30[1][2].field_8    = (sp30[0][2].field_8 + sp30[2][2].field_8) >> 1;
        sp30[1][2].field_A    = (sp30[0][2].field_A + sp30[2][2].field_A) >> 1;

        sp30[2][1].field_0.vx = (sp30[2][0].field_0.vx + sp30[2][2].field_0.vx) >> 1;
        sp30[2][1].field_0.vy = (sp30[2][0].field_0.vy + sp30[2][2].field_0.vy) >> 1;
        sp30[2][1].field_0.vz = (sp30[2][0].field_0.vz + sp30[2][2].field_0.vz) >> 1;
        sp30[2][1].field_8    = (sp30[2][0].field_8 + sp30[2][2].field_8) >> 1;
        sp30[2][1].field_A    = (sp30[2][0].field_A + sp30[2][2].field_A) >> 1;

        sp30[1][1].field_0.vx = (sp30[1][0].field_0.vx + sp30[1][2].field_0.vx) >> 1;
        sp30[1][1].field_0.vy = (sp30[1][0].field_0.vy + sp30[1][2].field_0.vy) >> 1;
        sp30[1][1].field_0.vz = (sp30[1][0].field_0.vz + sp30[1][2].field_0.vz) >> 1;
        sp30[1][1].field_8    = (sp30[1][0].field_8 + sp30[1][2].field_8) >> 1;
        sp30[1][1].field_A    = (sp30[1][0].field_A + sp30[1][2].field_A) >> 1;

        for (j = 0; j < 2; j++)
        {
            for (k = 0; k < 2; k++)
            {
                temp_a2 = MAX(sp30[j][k].field_0.vz, sp30[j][k + 1].field_0.vz);
                temp_a2 = MAX(temp_a2, sp30[j + 1][k].field_0.vz);
                temp_a2 = MAX(temp_a2, sp30[j + 1][k + 1].field_0.vz) >> 3;

                if (temp_a2 > 0 && temp_a2 < ORDERING_TABLE_SIZE - 1)
                {
                    poly2 = GsOUT_PACKET_P;

                    setPolyFT4(poly2);
                    setRGB0(poly2, arg1, arg1, arg1);

                    *(s32*)&poly2->x0 = *(s32*)&sp30[j][k];
                    *(s32*)&poly2->x1 = *(s32*)&sp30[j][k + 1];
                    *(s32*)&poly2->x2 = *(s32*)&sp30[j + 1][k];
                    *(s32*)&poly2->x3 = *(s32*)&sp30[j + 1][k + 1];

                    setUV4(poly2,
                           sp30[j][k].field_8, sp30[j][k].field_A,
                           sp30[j][k + 1].field_8, sp30[j][k + 1].field_A,
                           sp30[j + 1][k].field_8, sp30[j + 1][k].field_A,
                           sp30[j + 1][k + 1].field_8, sp30[j + 1][k + 1].field_A);

                    poly2->tpage = spA8;
                    poly2->clut  = temp_fp->field_2;
                    AddPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[temp_a2], poly2);
                    GsOUT_PACKET_P = poly2 + 1;
                }
            }
        }
    }
}

void func_800D8FC0(void) // 0x800D8FC0
{
    typedef struct
    {
        SPRT*     sprt_0;
        DR_TPAGE* tpage_4;
        DR_STP*   stp_8;
        s32       activeBufferIdx_C;
    } g_GteScratchData_func_800D8FC0;

    g_GteScratchData_func_800D8FC0* scratchData;
    s32                             i;

    scratchData = PSX_SCRATCH_ADDR(0);

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 5)
    {
        SysWork_StateStepSet(0, 5);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800868DC(0);
            func_800868DC(1);
            func_800868DC(2);
            func_800868DC(3);
            func_800868DC(4);
            func_800868DC(5);
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);

            Savegame_EventFlagSet(EventFlag_333);

            func_800D76BC(1);
            Game_TurnFlashlightOn();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(2.2f), false);

            scratchData->activeBufferIdx_C = g_ActiveBufferIdx;
            scratchData->sprt_0            = (SPRT*)GsOUT_PACKET_P;
            for (i = 0; i < 2; i++)
            {
                setCodeWord(scratchData->sprt_0, PRIM_RECT | RECT_BLEND | RECT_TEXTURE, PACKED_COLOR(128, 128, 128, 0));
                setXY0Fast(scratchData->sprt_0, ((i << 8) - 160), -112);
                scratchData->sprt_0->u0 = 0;
                scratchData->sprt_0->v0 = (scratchData->activeBufferIdx_C == 0) ? 32 : 0;
                setWH(scratchData->sprt_0, (i == 0) ? 256 : 64, 224);
                addPrimFast(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratchData->sprt_0, 4);

                scratchData->sprt_0++;
                scratchData->tpage_4 = (DR_TPAGE*)scratchData->sprt_0;
                setDrawTPage(scratchData->tpage_4, 0, 0, getTPageFromBuffer(2, 0, scratchData->activeBufferIdx_C, i));

                AddPrim(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratchData->tpage_4);
                scratchData->tpage_4++;
                scratchData->sprt_0 = (SPRT*)scratchData->tpage_4;
            }

            scratchData->stp_8 = (DR_STP*)scratchData->sprt_0;
            SetDrawStp(scratchData->stp_8, 1);
            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ORDERING_TABLE_SIZE - 1], scratchData->stp_8);
            scratchData->stp_8++;
            SetDrawStp(scratchData->stp_8, 0);
            addPrim(&g_OrderingTable2[g_ActiveBufferIdx].org[0], scratchData->stp_8);
            scratchData->stp_8++;
            GsOUT_PACKET_P = (PACKET*)scratchData->stp_8;

            Camera_LookAtSet(NULL, Q12(162.5f), Q12(-1.15f), Q12(50.5f), Q12(0.375f), Q12(0.475f), Q12(0.0374f), Q12(0.0875f), false);
            break;

        case 3:
            Fs_QueueStartSeek(FILE_1ST_NO_BLOCK_TIM);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(162.77f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(55.43f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(180.0f);

            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, 2);
            func_8008D438();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(163.78f), Q12(-2.31f), Q12(58.91f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(162.5f), Q12(-1.15f), Q12(50.5f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);
            break;

        case 4:
            if (func_800D76E8())
            {
                SysWork_StateStepIncrement(0);
            }

            // Warp camera.
            Camera_PositionSet(NULL,
                               func_800868F4(Q12(-1.28f), Q12(6.5f), 0) + Q12(163.78f),
                               func_800868F4(Q12(1.16f), Q12(6.5f), 1) - Q12(2.31f),
                               func_800868F4(Q12(-4.41f), Q12(6.5f), 2) + Q12(58.91f),
                               Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), false);

            if (g_SysWork.sysStateStep_C[0] != 4)
            {
                SysWork_StateStepReset();
            }
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            // Return to gameplay.
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_330);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(162.77f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(55.43f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(180.0f);
            break;
    }
}

void func_800D960C(void) // 0x800D960C
{
    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] < 4)
    {
        SysWork_StateStepReset();
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(159.59f), Q12(-1.25f), Q12(59.49f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(161.69f), Q12(-1.53f), Q12(56.1f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_800D76BC(2);
            D_800DB9E2 = 0;

            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, 2);

            func_8008D448();
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 2:
            Map_MessageWithAudio(16, &D_800DB9E2, &D_800DB92C);
            break;

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        default:
            Savegame_EventFlagSet(EventFlag_332);

            // Return to gameplay.
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(false);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D9824(void) // 0x800D9824
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            ScreenFade_ResetTimestep();

            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_800D4000(&g_SysWork.npcs_1A0[0]);

            SysWork_StateStepIncrement(0);
            break;

        default:
            Savegame_EventFlagClear(EventFlag_335);

            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            break;
    }
}

void Map_WorldObjectsInit(void) // 0x800D991C
{
    D_800E05E2 = 0;
    D_800E05E0 = 0;
    D_800E05E1 = 0;
    D_800E05A8 = 0;
    D_800E05AC = 0;
    D_800E05AE = 0;

    if (!Savegame_EventFlagGet(EventFlag_324))
    {
        g_MapOverlayHeader.charaUpdateFuncs_194[Chara_Twinfeeler] = func_800D3694;
        func_800D7408();
        Fs_QueueWaitForEmpty();
    }

    WorldObjectInit(&g_WorldObject_Fence, "FENCE_HI", 130.5f, 0.0f, -93.0f, 0.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject_Mal5_21, "MAL5_21_", 117.2464f, -0.685f, 145.896f, -36.0f, 243.0f, 60.21f);

    WorldObject_ModelNameSet(&g_WorldObject_Mal6[0], "MAL6_27_");
    WorldObject_ModelNameSet(&g_WorldObject_Mal6[1], "MAL6_28_");

    Math_Vector3Set(&g_WorldObject_UnkPos, Q12(132.0f), Q12(-0.75f), Q12(140.0f));
    Math_SetSVectorFast(&g_WorldObject_UnkRot, Q12_ANGLE(90.0f), Q12_ANGLE(90.0f), Q12_ANGLE(0.0f));

    WorldObjectInit(&g_WorldObject_SavePad, D_800A99E4.savePadName_4, 217.15f, -1.25f, -22.9f, 0.0f, -173.0f, 0.0f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        D_800C4418.field_0 = Q12(5.0f);
    }
    else
    {
        D_800C4418.field_0 = Q12(3.5f);
    }

    D_800C4418.field_2 = Q12(0.2f);
    D_800C4418.field_4 = Q12(0.1f);
    D_800C4418.field_6 = Q12(0.45f);
    D_800C4418.field_8 = Q12(6.0f);
    D_800C4418.field_A = Q12(0.55f);
    D_800C4418.field_C = 18;

    if (Savegame_EventFlagGet(EventFlag_324) && !Savegame_EventFlagGet(EventFlag_327))
    {
        Savegame_EventFlagSet(EventFlag_335);
        Savegame_EventFlagClear(EventFlag_325);
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x800D9BB0
{
    q19_12 var_a0; // Angle?
    q19_12 var;    // Angle?
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 6, -1, 6) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        WorldGfx_ObjectAdd(&g_WorldObject_SavePad.object_0, &g_WorldObject_SavePad.position_1C, &g_WorldObject_SavePad.rotation_28);
    }

    if ((PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) || PLAYER_IN_MAP_CHUNK(vx, 1, 5, -1, 5)) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        if (Savegame_EventFlagGet(EventFlag_320))
        {
            if (!D_800E05A8)
            {
                func_8005DC1C(Sfx_Unk1555, &QVECTOR3(130.5f, 0.0f, -93.0f), Q8(0.5f), 0);

                g_SysWork.playerWork_4C.player_0.fallSpeed_34 += Q12(1.0f);
                D_800E05AE += Q12(1.0f);
            }

            func_80069844(2);
            D_800E05A8 += g_DeltaTime;

            if (D_800E05AC) {} // @hack

            var = ratan2(Q12_ANGLE(360.0f), FP_FROM(g_GravitySpeed * Math_Cos(g_WorldObject_Fence.rotation_28.vx), Q12_SHIFT));
            var_a0 = MAX(Q12(0.0f), Q12(1.0f) - (D_800E05A8 * 2));
            D_800E05AC = Q12_MULT_PRECISE(var_a0, D_800E05AC + var);
            g_WorldObject_Fence.rotation_28.vx += Q12_MULT_PRECISE(g_DeltaTime, D_800E05AC);

            D_800E05AE = MIN(Q12(15.0f), (D_800E05AE + g_GravitySpeed) + (g_GravitySpeed >> 4));

            g_WorldObject_Fence.position_1C.vy += Q12_MULT_PRECISE(g_DeltaTime, D_800E05AE);
            if (g_WorldObject_Fence.rotation_28.vx > Q12_ANGLE(90.0f))
            {
                g_WorldObject_Fence.rotation_28.vx = Q12_ANGLE(90.0f);
            }

            if (D_800E05A8 > Q12(1.0f))
            {
                // NOTE: Changed return type to `s32` in context.
                if (sharedFunc_800D2EA4_0_s00())
                {
                    Savegame_EventFlagSet(EventFlag_322);
                }

                Savegame_EventFlagSet(EventFlag_321);
            }
        }
        else
        {
            func_8006982C(2);
        }

        WorldGfx_ObjectAdd(&g_WorldObject_Fence.object_0, &g_WorldObject_Fence.position_1C, &g_WorldObject_Fence.rotation_28);
    }

    if ((PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) || PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4)) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M4S03_PickupHuntingRifle))
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Mal5_21.object_0, &g_WorldObject_Mal5_21.position_1C, &g_WorldObject_Mal5_21.rotation_28);
        }

        if (!Savegame_EventFlagGet(EventFlag_327))
        {
            func_8006982C(2);
            WorldGfx_ObjectAdd(&g_WorldObject_Mal6[0], &g_WorldObject_UnkPos, &g_WorldObject_UnkRot);
        }
        else
        {
            func_80069844(2);
            WorldGfx_ObjectAdd(&g_WorldObject_Mal6[1], &g_WorldObject_UnkPos, &g_WorldObject_UnkRot);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 6, -1, 6) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M4S03_FirstAidKit))
        {
            WorldGfx_ObjectAdd(g_CommonWorldObjects, &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 6, -1, 6) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M4S03_RifleShells0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 6, -1, 6) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M4S03_RifleShells1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }
}

void func_800DA3E0(void) // 0x800DA3E0
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if ((PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) || PLAYER_IN_MAP_CHUNK(vx, 1, 5, -1, 5)) &&
        PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        func_800D7718();
        if (D_800E05E0 == 0)
        {
            D_800E05E0++;

            if (Savegame_EventFlagGet(EventFlag_332))
            {
                func_800D76BC(3);
            }
        }

        if (Savegame_EventFlagGet(EventFlag_333))
        {
            if (D_800E05E1 == 0)
            {
                SD_Call(Sfx_Unk1563);
                SD_Call(Sfx_Unk1564);
                D_800E05E1++;
            }

            func_8005DE0C(Sfx_Unk1563, &QVECTOR3(162.5f, -1.125f, 51.45f), Q8(0.5f), Q12(48.0f), 0);
            func_8005DE0C(Sfx_Unk1564, &QVECTOR3(166.421f, -2.0f, 52.578f), Q8(0.5f), Q12(48.0f), 0);
        }
    }
    else
    {
        D_800E05E0 = 0;

        if (D_800E05E1 != 0)
        {
            Sd_SfxStop(Sfx_Unk1563);
            Sd_SfxStop(Sfx_Unk1564);
        }

        D_800E05E1 = 0;
    }

    if ((PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) || PLAYER_IN_MAP_CHUNK(vx, 1, 5, -1, 5)) &&
        PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        if (vcRetCamMvSmoothF() == 0 && (g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(125.8f) || D_800E05E2 == 1))
        {
            if (D_800E05E2 != 0)
            {
                Gfx_MapInitMapEffectsUpdate(6, 3);
            }
            else
            {
                Gfx_MapInitMapEffectsUpdate(6, 20);
            }

            D_800E05E2 ^= 1;
        }
    }
}

void func_800DA718(void) // 0x800DA718
{
    void** addr;

    if (Savegame_EventFlagGet(EventFlag_323) && !Savegame_EventFlagGet(EventFlag_325))
    {
        addr  = &g_MapOverlayHeader.charaUpdateFuncs_194[Chara_Twinfeeler];
        *addr = Twinfeeler_Update;

        Savegame_EventFlagSet(EventFlag_325);

        Fs_QueueStartReadTim(FILE_TIM_BLOOD_TIM, FS_BUFFER_1, &D_800A908C);
        Fs_QueueStartReadTim(FILE_TEST_WARMTEST_TIM, FS_BUFFER_1, &D_800A9094);
        Fs_QueueWaitForEmpty();
    }
}
