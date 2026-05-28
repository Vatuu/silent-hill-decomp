#include <memory.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/dms.h"
#include "bodyprog/gfx/map_effects.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/player.h"
#include "bodyprog/ranking.h"
#include "bodyprog/sound/sound_system.h"
#include "main/rng.h"
#include "maps/map7/map7_s03.h"
#include "maps/characters/alessa.h"
#include "maps/characters/bloody_incubator.h"
#include "maps/characters/bloody_lisa.h"
#include "maps/characters/cybil.h"
#include "maps/characters/dahlia.h"
#include "maps/characters/incubator.h"
#include "maps/characters/incubus.h"
#include "maps/characters/kaufmann.h"
#include "screens/credits/credits.h"

void func_800D5D24(void) // 0x800D5D24
{
    s32  i;
    s32* ptr;

    ptr = D_800F2418;

    for (i = 5; i >= 0; i--)
    {
        *ptr++ = 0;
    }
}

bool func_800D5D48(void) // 0x800D5D48
{
    s32  var_s0;
    s32  i;
    s32* ptr0;
    s32* ptr1;

    ptr1   = NULL;
    var_s0 = 0;
    ptr0   = D_800F2418;

    // TODO: 6 refers to NPCs array?
    for (i = 0; i < 6; i++, ptr0++)
    {
        if (*ptr0 <= 0)
        {
            ptr1 = ptr0;
        }
        else if (D_800EB008 < *ptr0)
        {
            var_s0    += 2;
            D_800EB008 = (Rng_Rand16() / 21) + Q12(0.8f);
        }
        else if (D_800EB00C < *ptr0)
        {
            var_s0++;
            D_800EB00C = (Rng_Rand16() / 41) + Q12(0.4f);
        }
    }

    if (var_s0 < 2 && ptr1 != NULL)
    {
        *ptr1 = Q12(2.0f);
        return true;
    }
    else
    {
        return false;
    }
}

void func_800D5E78(void) // 0x800D5E78
{
    s32  i;
    s32* ptr;

    ptr = D_800F2418;

    // TODO: 6 refers to NPCs array?
    for (i = 0; i < 6; i++, ptr++)
    {
        if (*ptr > 0)
        {
            *ptr -= g_DeltaTime;
        }
    }
}

void func_800D5EC0(void) // 0x800D5EC0
{
    q19_12               cosAngle;
    q19_12               sinAngle;
    q19_12               randAngle;
    q19_12               dist;
    s32                  i;
    s_func_800D5EC0_A60* ptr1;
    s_func_800D5EC0*     ptr;
    s64                  temp;

    ptr = FS_BUFFER_1;

    ptr1 = ptr->field_A60;

    for (i = 0; i < 20; i++, ptr1++)
    {
        ptr1->field_34 = 0;

        ptr1->field_0.vx = Q12(0.0f);
        ptr1->field_0.vy = Q12(0.0f);
        ptr1->field_0.vz = Q12(0.0f);

        ptr1->field_30 = 0xFF;

        randAngle = Rng_Rand16();
        sinAngle = Math_Sin(randAngle);
        cosAngle = Math_Cos(randAngle);

        dist = Q12_MULT_PRECISE((Rng_Rand16() % Q12(1.0f)) + Q12(0.5f), Q12(6.0f));

        ptr1->field_20.vx = Q12_MULT_PRECISE(cosAngle, dist);
        ptr1->field_20.vy = Q12_MULT_PRECISE(sinAngle, dist);

        temp                = Q12(-1.6f) + 1;
        ptr1->field_20.vz = temp;
    }
}

void func_800D600C(s32 x, s32 y, s32 val) // 0x800D600C
{
    s32              offsetX;
    s32              offsetY;
    s16              row;
    s16              col;
    s_func_800D5EC0* ptr;
    u8*              buf;

    ptr = FS_BUFFER_1;

    offsetX = ptr->field_A50 & 0xFFFF;
    offsetY = ptr->field_A50 >> 16;

    col = (x + 82) - offsetX;
    row = (y + 122) - offsetY;

    col += (col > 0) ? 2 : -2;
    col /= 4;

    row += (row > 0) ? 2 : -2;
    row /= 4;

    if (col > 0 && col < 41 && row > 0 && row < 61)
    {
        buf  = ptr->field_5D + (col + (41 * row));
        *buf = val;
    }
}

void func_800D60E4(void) // 0x800D60E4
{
    SVECTOR              sp10;
    DVECTOR              sp18[2];
    s32                  sp20;
    s32                  i;
    s_func_800D5EC0_A60* ptr;
    s_func_800D5EC0*     base;

    base = (s_func_800D5EC0*)FS_BUFFER_1;
    ptr  = base->field_A60;

    for (i = 0; i < 20; i++, ptr++)
    {
        if (ptr->field_34 < 0)
        {
            sp10.vx = Q12_TO_Q4(ptr->field_0.vx);
            sp10.vy = Q12_TO_Q4(ptr->field_0.vy);
            sp10.vz = Q12_TO_Q4(ptr->field_0.vz);

            RotTransPers(&sp10, &sp18[0], &sp18[1], &sp20);
            func_800D600C(sp18[0].vx, sp18[0].vy, ptr->field_30);

            ptr->field_0.vx  += ptr->field_20.vx;
            ptr->field_0.vy  += ptr->field_20.vy;
            ptr->field_0.vz  += ptr->field_20.vz;
            ptr->field_20.vz -= 0x199;

            ptr->field_20.vz = MAX(ptr->field_20.vz, -0x1000);
            ptr->field_30   -= 20;
            ptr->field_30    = MAX(ptr->field_30, 0);
        }
        else
        {
            ptr->field_34 -= g_DeltaTime;
        }
    }
}

s32 func_800D621C(s32 arg0, s32 arg1) // 0x800D621C
{
    s_func_800D5EC0* buf;

    buf = (s_func_800D5EC0*)FS_BUFFER_1;

    return D_800EB010[buf->field_5D[(arg1 * 41) + arg0]];
}

void func_800D625C(void) // 0x800D625C
{
    u32              sp18;
    s_func_800D5EC0* ptr;
    GsOT_TAG*        ot;
    s32              x;
    s32              y;
    s32              col0;
    s32              col2;
    s32              col3;
    s32              i;
    s32              j;
    s32              col1;
    POLY_G4*         poly;
    DR_MODE*         mode;
    PACKET*          packet;
    s32              col;
    s32              idx;
    int              code;

    ptr = (s_func_800D5EC0*)FS_BUFFER_1;

    packet = GsOUT_PACKET_P;
    poly   = packet;

    x = (ptr->field_A50 & 0xFFFF) - 82;
    y = ((u32)ptr->field_A50 >> 16) - 122;

    idx = g_ActiveBufferIdx;
    ot  = g_OrderingTable0[idx].org;
    ot  = &ot[ptr->field_A54 >> 1];

    col  = 0x3A000000;
    code = 0x3A;

    for (i = 1; i < 61; i++)
    {
        col1 = func_800D621C(0, i - 1);
        col3 = func_800D621C(0, i);

        for (j = 1; j < 41; j++)
        {
            sp18 = ptr->field_5D[(i * 41) + j];

            col0 = col1;
            col2 = col3;
            col1 = func_800D621C(j, i - 1);

            col3 = func_800D621C(j, i);

            if (col == col0 &&
                col0 == col1 &&
                col0 == col2 &&
                col2 == col3)
            {
                continue;
            }

            if ((j + i) & 0x1)
            {
                poly->x0 = x + (j * 4);
                poly->y0 = y + (i * 4);
                poly->x1 = (x + (j * 4)) + 4;
                poly->y1 = y + (i * 4);
                poly->x2 = x + (j * 4);
                poly->y2 = (y + (i * 4)) + 4;
                poly->x3 = (x + (j * 4)) + 4;
                poly->y3 = (y + (i * 4)) + 4;

                *(s32*)&poly->r0 = col0;
                *(s32*)&poly->r1 = col1;
                *(s32*)&poly->r2 = col2;
                *(s32*)&poly->r3 = col3;
            }
            else
            {
                poly->x1 = x + (j * 4);
                poly->y1 = y + (i * 4);
                poly->x0 = (x + (j * 4)) + 4;
                poly->y0 = y + (i * 4);
                poly->x3 = x + (j * 4);
                poly->y3 = (y + (i * 4)) + 4;
                poly->x2 = (x + (j * 4)) + 4;
                poly->y2 = (y + (i * 4)) + 4;

                *(s32*)&poly->r0 = col1;
                *(s32*)&poly->r1 = col0;
                *(s32*)&poly->r2 = col3;
                *(s32*)&poly->r3 = col2;
            }

            setPolyG4(poly);
            poly->code = (float)sp18; // @hack
            poly->code = code;

            addPrim(ot, poly);
            poly++;
        }
    }

    packet = poly;
    mode   = packet;

    SetDrawMode(mode, 0, 1, 42, NULL);
    addPrim(ot, mode);
    packet         = mode + 1;
    GsOUT_PACKET_P = packet;
}

void func_800D6548(void) // 0x800D6548
{
    s32              i;
    s32              j;
    s32              val;
    s_func_800D5EC0* buf;
    u8*              tab;

    buf = FS_BUFFER_1;

    for (i = 0; i < 61; i++)
    {
        tab = &buf->field_5D[i * 41];

        for (j = 0; j < 41; j++)
        {
            val = tab[j - 41];

            if (j == 0)
            {
                val = 0;
            }
            else
            {
                val += tab[j - 1];
            }

            if (j == 40)
            {
                val = 0;
            }
            else
            {
                val = val + tab[j + 1];
            }

            val  += tab[j + 41];
            val >>= 2;
            val  -= 1;

            if (val <= 0)
            {
                tab[j] = 0;
            }
            else
            {
                tab[j] = val;
            }

            if (!Rng_GenerateUInt(0, 4095)) // 1 in 4096 chance.
            {
                tab[j] = 0;
            }
        }
    }
}

void func_800D663C(void) // 0x800D663C
{
    s_func_800D5EC0* buf = FS_BUFFER_1;
    memset(buf->field_34, 0, sizeof(buf->field_34));
    memset(buf->field_5D, 0, sizeof(buf->field_5D));
    memset(buf->field_A22, 0, sizeof(buf->field_A22));
}

void func_800D6690(VECTOR* arg0, q19_12 rotY) // 0x800D6690
{
    MATRIX  mat;
    VECTOR  sp30;
    SVECTOR rot; // Q3.12

    SetRotMatrix(&GsWSMATRIX);
    SetTransMatrix(&GsWSMATRIX);
    ApplyRotMatrixLV(arg0, &sp30);

    sp30.vx += GsWSMATRIX.t[0];
    sp30.vy += GsWSMATRIX.t[1];
    sp30.vz += GsWSMATRIX.t[2];

    TransMatrix(&mat, &sp30);
    SetTransMatrix(&mat);

    rot.vx = Q12_ANGLE(0.0f);
    rot.vy = rotY;
    rot.vz = Q12_ANGLE(0.0f);

    Math_RotMatrixZxyNeg(&rot, &mat);
    SetMulRotMatrix(&mat);
}

s32 func_800D6750(s32* sxy) // 0x800D6750
{
    SVECTOR sp10;
    s32     sp18;

    sp10.vx = Q8(0.0f);
    sp10.vy = Q8(0.0f);
    sp10.vz = Q8(0.0f);
    return RotTransPers(&sp10, sxy, &sp18, &sp18);
}

void func_800D6788(void) // 0x800D6788
{
    s_func_800D5EC0* buf = FS_BUFFER_1;

    if (buf->field_A5C > 0)
    {
        buf->field_A5C -= g_DeltaTime;
        return;
    }

    func_800D6690(&buf->field_4, buf->field_A58);
    buf->field_A54 = func_800D6750(&buf->field_A50);

    func_800D60E4();
    func_800D6548();
    func_800D625C();
}

void func_800D6804(const VECTOR3* from, const VECTOR3* to) // 0x800D6804
{
    q19_12           x0;
    q19_12           z0;
    q19_12           x1;
    q19_12           z1;
    s_func_800D5EC0* buf;

    buf = FS_BUFFER_1;

    x0 = to->vx - from->vx;
    z0 = to->vz - from->vz;

    buf->field_A58 = ratan2(x0, z0);

    if (x0 < Q12(0.0f))
    {
        x1 = x0 + 3;
    }
    else
    {
        x1 = x0;
    }

    x0 = from->vx + (x1 >> 2);

    if (z0 < Q12(0.0f))
    {
        z1 = z0 + 3;
    }
    else
    {
        z1 = z0;
    }

    z0 = (from->vz + (z1 >> 2));

    buf->field_4.vx = Q12_TO_Q8(x0);
    buf->field_4.vy = Q8(-1.0f);
    buf->field_4.vz = Q12_TO_Q8(z0);

    buf->field_A5C = 0;

    func_800D663C();
    func_800D5EC0();
}

void func_800D68C4(void) // 0x800D68C4
{
    q19_12               posX;
    q19_12               posY;
    q19_12               posZ;
    q19_12               dist;
    q19_12               randAngle;
    s32                  i;
    s_func_800D68C4*     base;
    s_func_800D68C4_A08* curPtr;

    base = FS_BUFFER_1;

    curPtr = base->field_A08;
    for (i = 0; i < 100; i++, curPtr++)
    {
        curPtr->field_0.vx = Q12(0.0f);
        curPtr->field_0.vy = Q12(0.0f);
        curPtr->field_0.vz = Q12(0.0f);

        curPtr->field_30 = 0xFF;

        randAngle = Rng_Rand16();
        posY = Q12_MULT_PRECISE(Math_Sin(randAngle), Q12(0.6f));
        dist = Q12_MULT_PRECISE(Math_Cos(randAngle), Q12(0.6f));

        randAngle = Rng_Rand16();
        posX = Q12_MULT_PRECISE(Math_Sin(randAngle), dist);
        posZ = Q12_MULT_PRECISE(Math_Cos(randAngle), dist);

        curPtr->field_20.vx = posX;
        curPtr->field_20.vy = posY;
        curPtr->field_20.vz = posZ;
    }
}

void func_800D6A10(s32 x, s32 y, s32 val) // 0x800D6A10
{
    s32              offsetX;
    s32              offsetY;
    s16              row;
    s16              col;
    s_func_800D68C4* ptr;
    u8*              buf;

    ptr = FS_BUFFER_1;

    offsetX = ptr->field_9FC & 0xFFFF;
    offsetY = ptr->field_9FC >> 16;

    col = (x + 49) - offsetX;
    row = (y + 49) - offsetY;

    col += (col > 0) ? 1 : -1;
    col /= 2;

    row += (row > 0) ? 1 : -1;
    row /= 2;

    if (col > 0 && col < 49 && row > 0 && row < 49)
    {
        buf  = ptr->field_65 + (col + (49 * row));
        *buf = val;
    }
}

void func_800D6ADC(void) // 0x800D6ADC
{
    SVECTOR              sp10;
    DVECTOR              sp18[2];
    s32                  sp20;
    s32                  i;
    s_func_800D68C4_A08* curPtr;
    s_func_800D68C4*     base;

    base = (s_func_800D68C4*)FS_BUFFER_1;

    curPtr = base->field_A08;
    for (i = 0; i < 100; i++, curPtr++)
    {
        sp10.vx = Q12_TO_Q4(curPtr->field_0.vx);
        sp10.vy = Q12_TO_Q4(curPtr->field_0.vy);
        sp10.vz = Q12_TO_Q4(curPtr->field_0.vz);

        RotTransPers(&sp10, &sp18[0], &sp18[1], &sp20);
        func_800D6A10(sp18[0].vx, sp18[0].vy, curPtr->field_30);

        curPtr->field_0.vx += curPtr->field_20.vx;
        curPtr->field_0.vy += curPtr->field_20.vy;
        curPtr->field_0.vz += curPtr->field_20.vz;
        curPtr->field_30    = curPtr->field_30 - 8;
        curPtr->field_30    = MAX(curPtr->field_30, 0);
    }
}

s32 func_800D6BCC(s32 arg0, s32 arg1) // 0x800D6BCC
{
    s_func_800D68C4* buf;

    buf = (s_func_800D68C4*)FS_BUFFER_1;

    return D_800EB410[buf->field_65[(arg1 * 49) + arg0]];
}

void func_800D6C0C(void) // 0x800D6C0C
{
    u32              sp18;
    s_func_800D68C4* ptr;
    GsOT_TAG*        ot;
    s32              x;
    s32              y;
    s32              col0;
    s32              col2;
    s32              col3;
    s32              i;
    s32              j;
    s32              col1;
    POLY_G4*         poly;
    DR_MODE*         mode;
    PACKET*          packet;
    s32              col;
    s32              idx;
    int              code;

    ptr = FS_BUFFER_1;

    packet = GsOUT_PACKET_P;
    poly   = packet;

    x = (ptr->field_9FC & 0xFFFF) - 49;
    y = ((u32)ptr->field_9FC >> 16) - 49;

    idx = g_ActiveBufferIdx;
    ot  = g_OrderingTable0[idx].org;
    ot  = &ot[ptr->field_A00 >> 1];

    col  = 0x3A000000;
    code = 0x3A;

    for (i = 1; i < 49; i++)
    {
        col1 = func_800D6BCC(0, i - 1);
        col3 = func_800D6BCC(0, i);

        for (j = 1; j < 49; j++)
        {
            sp18 = ptr->field_65[(i * 49) + j];

            col0 = col1;
            col2 = col3;
            col1 = func_800D6BCC(j, i - 1);

            col3 = func_800D6BCC(j, i);

            if (col == col0 &&
                col0 == col1 &&
                col0 == col2 &&
                col2 == col3)
            {
                continue;
            }

            if ((j + i) & 0x1)
            {
                poly->x0 = x + (j * 2);
                poly->y0 = y + (i * 2);
                poly->x1 = (x + (j * 2)) + 2;
                poly->y1 = y + (i * 2);
                poly->x2 = x + (j * 2);
                poly->y2 = (y + (i * 2)) + 2;
                poly->x3 = (x + (j * 2)) + 2;
                poly->y3 = (y + (i * 2)) + 2;

                *(s32*)&poly->r0 = col0;
                *(s32*)&poly->r1 = col1;
                *(s32*)&poly->r2 = col2;
                *(s32*)&poly->r3 = col3;
            }
            else
            {
                poly->x1 = x + (j * 2);
                poly->y1 = y + (i * 2);
                poly->x0 = (x + (j * 2)) + 2;
                poly->y0 = y + (i * 2);
                poly->x3 = x + (j * 2);
                poly->y3 = (y + (i * 2)) + 2;
                poly->x2 = (x + (j * 2)) + 2;
                poly->y2 = (y + (i * 2)) + 2;

                *(s32*)&poly->r0 = col1;
                *(s32*)&poly->r1 = col0;
                *(s32*)&poly->r2 = col3;
                *(s32*)&poly->r3 = col2;
            }

            setPolyG4(poly);
            poly->code = (float)sp18; // @hack
            poly->code = code;

            addPrim(ot, poly);
            poly++;
        }
    }

    packet = poly;
    mode   = packet;

    SetDrawMode(mode, 0, 1, 42, NULL);
    addPrim(ot, mode);
    packet         = mode + 1;
    GsOUT_PACKET_P = packet;
}

void func_800D6EF8(void) // 0x800D6EF8
{
    s32              i;
    s32              j;
    s32              val;
    s_func_800D68C4* buf;
    u8*              tab;

    buf = FS_BUFFER_1;

    for (i = 0; i < 49; i++)
    {
        tab = &buf->field_65[i * 49];

        for (j = 0; j < 49; j++)
        {
            val = tab[j - 49];

            if (j == 0)
            {
                val = 0;
            }
            else
            {
                val += tab[j - 1];
            }

            if (j == 48)
            {
                val = 0;
            }
            else
            {
                val = val + tab[j + 1];
            }

            val  += tab[j + 49];
            val >>= 2;
            val  -= 1;

            if (val <= 0)
            {
                tab[j] = 0;
            }
            else
            {
                tab[j] = val;
            }
        }
    }
}

void func_800D6FA0(void) // 0x800D6FA0
{
    s_func_800D68C4* buf = FS_BUFFER_1;

    memset(buf->field_34, 0, sizeof(buf->field_34));
    memset(buf->field_65, 0, sizeof(buf->field_65));
    memset(buf->field_9C6, 0, sizeof(buf->field_9C6));
}

void func_800D6FF4(VECTOR* arg0, q19_12 rotY) // 0x800D6FF4
{
    MATRIX  mat;
    VECTOR  sp30;
    SVECTOR rot; // Q3.12

    SetRotMatrix(&GsWSMATRIX);
    SetTransMatrix(&GsWSMATRIX);
    ApplyRotMatrixLV(arg0, &sp30);

    sp30.vx += GsWSMATRIX.t[0];
    sp30.vy += GsWSMATRIX.t[1];
    sp30.vz += GsWSMATRIX.t[2];

    TransMatrix(&mat, &sp30);
    SetTransMatrix(&mat);

    rot.vx = Q12_ANGLE(0.0f);
    rot.vy = rotY;
    rot.vz = Q12_ANGLE(0.0f);

    Math_RotMatrixZxyNeg(&rot, &mat);
    SetMulRotMatrix(&mat);
}

s32 func_800D70B4(s32* sxy) // 0x800D70B4
{
    SVECTOR sp10;
    s32     sp18;

    sp10.vx = Q8(0.0f);
    sp10.vy = Q8(0.0f);
    sp10.vz = Q8(0.0f);
    return RotTransPers(&sp10, sxy, &sp18, &sp18);
}

void func_800D70EC(void) // 0x800D70EC
{
    s_func_800D68C4* buf = FS_BUFFER_1;

    func_800D6FF4(&buf->field_4, buf->field_A04);
    buf->field_A00 = func_800D70B4(&buf->field_9FC);

    func_800D6ADC();
    func_800D6EF8();
    func_800D6C0C();
}

void func_800D7144(VECTOR3* arg0) // 0x800D7144
{
    s_func_800D68C4* buf = FS_BUFFER_1;

    buf->field_A04 = 0;

    buf->field_4.vx = Q12_TO_Q8(arg0->vx);
    buf->field_4.vy = Q12_TO_Q8(arg0->vy);
    buf->field_4.vz = Q12_TO_Q8(arg0->vz);

    func_800D6FA0();
    func_800D68C4();
}

void func_800D71A4(s32 arg0) // 0x800D71A4
{
    D_800F2430 = arg0;
}

void func_800D71B0(VECTOR3* pos, s32 arg1) // 0x800D71B0
{
    s32                  temp_hi_4;
    s32                  temp_hi_5;
    s32                  temp_hi_6;
    q19_12               sinAngle;
    q19_12               cosAngle;
    q19_12               randAngle0;
    s32                  randAngle1;
    s32                  temp_v0_4;
    s32                  temp_v0_6;
    s32                  i;
    s32                  j;
    s_func_800D71B0_498* ptr;
    s_func_800D71B0*     base;

    base = FS_BUFFER_25;
    ptr  = base->field_498;

    for (j = 0, i = 0; i < 200; i++, ptr++)
    {
        if (ptr->field_20 != 0)
        {
            continue;
        }

        if (j >= arg1)
        {
            break;
        }

        j++;

        randAngle0 = Rng_Rand16();
        sinAngle = Math_Sin(randAngle0);
        cosAngle = Math_Cos(randAngle0);

        randAngle1 = Rng_Rand16();
        temp_v0_4 = Q12_MULT_PRECISE(cosAngle, Math_Sin(randAngle1));
        temp_v0_6 = Q12_MULT_PRECISE(cosAngle, Math_Cos(randAngle1));

        ptr->field_0.vx = pos->vx + Q12_MULT_PRECISE(temp_v0_4, D_800EB810);
        ptr->field_0.vy = pos->vy + Q12_MULT_PRECISE(sinAngle, D_800EB810);
        ptr->field_0.vz = pos->vz + Q12_MULT_PRECISE(temp_v0_6, D_800EB810);
        ptr->field_28   = 0xFFF;

        randAngle0 = Rng_Rand16();
        sinAngle = Math_Sin(randAngle0);
        cosAngle = Math_Cos(randAngle0);

        randAngle0   = Rng_Rand16();
        temp_v0_4 = Q12_MULT_PRECISE(Math_Sin(randAngle0), cosAngle);
        temp_v0_6 = Q12_MULT_PRECISE(Math_Cos(randAngle0), cosAngle);

        temp_hi_4 = Q12_MULT_PRECISE(temp_v0_4, Q12(0.6f));
        temp_hi_5 = Q12_MULT_PRECISE(temp_v0_6, Q12(0.6f));
        temp_hi_6 = Q12_MULT_PRECISE(sinAngle, Q12(0.6f));

        ptr->field_10.vx = ((ptr->field_0.vx - pos->vx) * 4) + Q12_MULT_PRECISE(temp_v0_4, Q12(0.6f));
        ptr->field_10.vy = ((ptr->field_0.vy - pos->vy) * 4) + Q12_MULT_PRECISE(sinAngle, Q12(0.6f));
        ptr->field_10.vz = ((ptr->field_0.vz - pos->vz) * 4) + Q12_MULT_PRECISE(temp_v0_6, Q12(0.6f));

        randAngle0       = Rng_Rand16();
        ptr->field_34 = 0;
        randAngle0       = Rng_Rand16();
        ptr->field_30 = Q12(1.0f);
        ptr->field_20 = 1;
    }
}

void func_800D74F4(s32 x, s32 y, s32 val) // 0x800D74F4
{
    s16              row;
    s16              col;
    s_func_800D71B0* ptr;
    u8*              buf;

    ptr = FS_BUFFER_25;

    col = (x + 164);
    row = (y + 100);

    col += (col > 0) ? 4 : -4;
    col /= 8;

    row += (row > 0) ? 4 : -4;
    row /= 8;

    if (col > 0 && col < 41 && row > 0 && row < 25)
    {
        buf = ptr->field_5D + (col + (41 * row));
        if (val >> 4 < 0x100)
        {
            *buf = val >> 4;
        }
        else
        {
            *buf = 0xFF;
        }
    }
}

void func_800D75D0(void) // 0x800D75D0
{
    SVECTOR              sp10;
    DVECTOR              sp18[2];
    s32                  sp20;
    s32                  i;
    s_func_800D71B0_498* ptr;
    s_func_800D71B0*     base;

    base = FS_BUFFER_25;
    ptr  = base->field_498;

    for (i = 0; i < 200; i++, ptr++)
    {
        if (ptr->field_20 != 0)
        {
            if (ptr->field_34 < 0)
            {
                sp10.vx = Q12_TO_Q8(ptr->field_0.vx);
                sp10.vy = Q12_TO_Q8(ptr->field_0.vy);
                sp10.vz = Q12_TO_Q8(ptr->field_0.vz);

                RotTransPers(&sp10, &sp18[0], &sp18[1], &sp20);
                func_800D74F4(sp18[0].vx, sp18[0].vy, ptr->field_28);

                ptr->field_0.vx += Q12_MULT_PRECISE(ptr->field_10.vx, g_DeltaTime);
                ptr->field_0.vy += Q12_MULT_PRECISE(ptr->field_10.vy, g_DeltaTime);
                ptr->field_0.vz += Q12_MULT_PRECISE(ptr->field_10.vz, g_DeltaTime);

                ptr->field_28 -= Q12_MULT_PRECISE(g_DeltaTime, 0x1000);
                ptr->field_28  = MAX(ptr->field_28, 0);

                ptr->field_30 -= g_DeltaTime;

                if (ptr->field_30 < 0)
                {
                    ptr->field_20 = 0;
                }
            }
            else
            {
                ptr->field_34 -= g_DeltaTime;
            }
        }
    }
}

s32 func_800D77A4(s32 arg0, s32 arg1) // 0x800D77A4
{
    s_func_800D71B0* buf;

    buf = (s_func_800D71B0*)FS_BUFFER_25;

    return D_800EB814[buf->field_5D[(arg1 * 41) + arg0]];
}

void func_800D77E4(void) // 0x800D77E4
{
    u32              sp18;
    s_func_800D71B0* ptr;
    GsOT_TAG*        ot;
    s32              x;
    s32              y;
    s32              col0;
    s32              col2;
    s32              col3;
    s32              i;
    s32              j;
    s32              col1;
    POLY_G4*         poly;
    DR_MODE*         mode;
    PACKET*          packet;
    s32              col;
    s32              idx;
    int              code;

    ptr = FS_BUFFER_25;

    x = -0xA4;
    y = -0x64;

    idx = g_ActiveBufferIdx;
    ot  = g_OrderingTable0[idx].org;

    if ((ptr->field_490 >> 1) < 0x706)
    {
        ot = &ot[(ptr->field_490 >> 1) + 250];
    }
    else
    {
        ot = &ot[2036];
    }

    packet = GsOUT_PACKET_P;
    poly   = packet;

    i    = 1;
    col  = 0x3A000000;
    code = 0x3A;

    for (; i < 25; i++)
    {
        col1 = func_800D77A4(0, i - 1);
        col3 = func_800D77A4(0, i);

        for (j = 1; j < 41; j++)
        {
            sp18 = ptr->field_5D[(i * 41) + j];

            col0 = col1;
            col2 = col3;
            col1 = func_800D77A4(j, i - 1);

            col3 = func_800D77A4(j, i);

            if (col == col0 &&
                col0 == col1 &&
                col0 == col2 &&
                col2 == col3)
            {
                continue;
            }

            if ((j + i) & 0x1)
            {
                poly->x0 = x + (j * 8);
                poly->y0 = y + (i * 8);
                poly->x1 = (x + (j * 8)) + 8;
                poly->y1 = y + (i * 8);
                poly->x2 = x + (j * 8);
                poly->y2 = (y + (i * 8)) + 8;
                poly->x3 = (x + (j * 8)) + 8;
                poly->y3 = (y + (i * 8)) + 8;

                *(s32*)&poly->r0 = col0;
                *(s32*)&poly->r1 = col1;
                *(s32*)&poly->r2 = col2;
                *(s32*)&poly->r3 = col3;
            }
            else
            {
                poly->x1 = x + (j * 8);
                poly->y1 = y + (i * 8);
                poly->x0 = (x + (j * 8)) + 8;
                poly->y0 = y + (i * 8);
                poly->x3 = x + (j * 8);
                poly->y3 = (y + (i * 8)) + 8;
                poly->x2 = (x + (j * 8)) + 8;
                poly->y2 = (y + (i * 8)) + 8;

                *(s32*)&poly->r0 = col1;
                *(s32*)&poly->r1 = col0;
                *(s32*)&poly->r2 = col3;
                *(s32*)&poly->r3 = col2;
            }

            setPolyG4(poly);
            poly->code = (float)sp18; // @hack
            poly->code = code;

            addPrim(ot, poly);
            poly++;
        }
        ot -= 0x28 / 4;
    }

    packet = poly;
    mode   = packet;

    SetDrawMode(mode, 0, 1, 42, NULL);
    addPrim(ot, mode);
    packet         = mode + 1;
    GsOUT_PACKET_P = packet;
}

void func_800D7AD0(void) // 0x800D7AD0
{
    s32              i;
    s32              j;
    s32              val;
    s_func_800D71B0* buf;
    u8*              tab;

    buf = FS_BUFFER_25;

    for (i = 0; i < 25; i++)
    {
        tab = &buf->field_5D[i * 41];

        for (j = 0; j < 41; j++)
        {
            val = tab[j - 41];

            if (j == 0)
            {
                val = 0;
            }
            else
            {
                val += tab[j - 1];
            }

            if (j == 40)
            {
                val = 0;
            }
            else
            {
                val = val + tab[j + 1];
            }

            val  += tab[j + 41];
            val >>= 2;
            val  -= 1;

            if (val <= 0)
            {
                tab[j] = 0;
            }
            else
            {
                tab[j] = val;
            }
        }
    }
}

void func_800D7B78(void) // 0x800D7B78
{
    s32                  i;
    s_func_800D71B0_498* ptr;
    s_func_800D71B0*     buf;

    buf = FS_BUFFER_25;

    ptr = buf->field_498;

    memset(buf->field_34, 0, sizeof(buf->field_34));
    memset(buf->field_5D, 0, sizeof(buf->field_5D));
    memset(buf->field_45E, 0, sizeof(buf->field_45E));

    for (i = 199; i >= 0; i--, ptr++)
    {
        ptr->field_20 = 0;
    }

    func_800D71A4(0xFF);
}

void func_800D7BF4(VECTOR* arg0, q19_12 rotY) // 0x800D7BF4
{
    MATRIX  mat;
    VECTOR  sp30;
    SVECTOR rot; // Q3.12

    SetRotMatrix(&GsWSMATRIX);
    SetTransMatrix(&GsWSMATRIX);
    ApplyRotMatrixLV(arg0, &sp30);

    sp30.vx += GsWSMATRIX.t[0];
    sp30.vy += GsWSMATRIX.t[1];
    sp30.vz += GsWSMATRIX.t[2];

    TransMatrix(&mat, &sp30);
    SetTransMatrix(&mat);

    rot.vx = Q12_ANGLE(0.0f);
    rot.vy = rotY;
    rot.vz = Q12_ANGLE(0.0f);

    Math_RotMatrixZxyNeg(&rot, &mat);
    SetMulRotMatrix(&mat);
}

s32 func_800D7CB4(s32* sxy) // 0x800D7CB4
{
    SVECTOR sp10;
    s32     sp18;

    sp10.vx = Q8(0.0f);
    sp10.vy = Q8(0.0f);
    sp10.vz = Q8(0.0f);
    return RotTransPers(&sp10, sxy, &sp18, &sp18);
}

void func_800D7CEC(void) // 0x800D7CEC
{
    D_800F2434 = 0;
}

void func_800D7CF8(void) // 0x800D7CF8
{
    D_800F2434 = 1;
}

void func_800D7D08(void) // 0x800D7D08
{
    s_func_800D71B0* buf = FS_BUFFER_25;

    func_800D7BF4(&buf->field_4, buf->field_494);
    buf->field_490 = func_800D7CB4(&buf->field_48C) + 0x140;

    if (D_800F2434 == 0)
    {
        func_800D75D0();
    }
    func_800D7AD0();
    func_800D77E4();
}

void func_800D7D74(s32 arg0) // 0x800D7D74
{
    VECTOR3          sp10;
    VECTOR3          sp20;
    s_func_800D71B0* ptr;

    if (D_800F2434 == 0)
    {
        sp10.vx = Rng_Rand16() - 0x3FFF;
        sp10.vy = (Rng_Rand16() >> 2) + 0x4801;
        sp10.vz = (Rng_Rand16() * 2) - 0x7FFF;

        if (func_800D5D48())
        {
            sp20 = sp10;

            ptr      = FS_BUFFER_25;
            sp20.vx += ptr->field_4.vx * 0x10;
            sp20.vy += ptr->field_4.vy * 0x10;
            sp20.vz += ptr->field_4.vz * 0x10;

            func_8005DC1C(Sfx_Unk1694, &sp20, D_800F2430, SfxFlag_None);
        }

        func_800D71B0(&sp10, 0x1E);
    }
}

void func_800D7E50(VECTOR3* arg0) // 0x800D7E50
{
    s_func_800D71B0* ptr;

    ptr = FS_BUFFER_25;

    memset(ptr, 0xA7, sizeof(s_func_800D71B0));

    func_800D7B78();

    ptr->field_494  = 0;
    ptr->field_4.vx = Q12_TO_Q8(arg0->vx);
    ptr->field_4.vy = Q12_TO_Q8(arg0->vy);
    ptr->field_4.vz = Q12_TO_Q8(arg0->vz);
}

void func_800D7ED0(void) // 0x800D7ED0
{
    func_800D7B78();
}

void func_800D7EF0(void) // 0x800D7D08
{
    func_800D7D08();
}

PACKET* func_800D7F10(void) // 0x800D7F10
{
    return GsOUT_PACKET_P;
}

void func_800D7F20(u8* arg0) // 0x800D7F20
{
    GsOUT_PACKET_P = arg0;
}

void func_800D7F2C(GsOT_TAG* ot, s32 arg1, q19_12 angle, q19_12 dist0, q19_12 dist1, s16 x1, s16 y1, s32 arg7) // 0x800D7F2C
{
    q19_12   sp14;
    s32      i;
    q19_12   angle0;
    q19_12   y2;
    q19_12   x2;
    q19_12   y0;
    q19_12   x0;
    q19_12   x3;
    q19_12   y3;
    POLY_G4* poly;

    sp14 = Q12(1.0f) / arg1;
    sp14 = sp14 / 2;

    poly   = func_800D7F10();
    angle0 = angle;

    for (i = 0; i < arg1; i++)
    {
        x0 = Q12_MULT_PRECISE(Math_Sin(angle0), dist1);
        y0 = Q12_MULT_PRECISE(Math_Cos(angle0), dist1);

        angle0 += sp14;

        x2 = Q12_MULT_PRECISE(Math_Sin(angle0), dist0);
        y2 = Q12_MULT_PRECISE(Math_Cos(angle0), dist0);

        angle0 += sp14;

        if (i == (arg1 - 1))
        {
            angle0 = angle;
        }

        x0 += x1;
        x2 += x1;
        y0 += y1;
        y2 += y1;

        x3 = Q12_MULT_PRECISE(Math_Sin(angle0), dist1);
        y3 = Q12_MULT_PRECISE(Math_Cos(angle0), dist1);

        x3 += x1;
        y3 += y1;

        *(s32*)&poly->r0 = 0;

        setPolyG4(poly);
        setSemiTrans(poly, 1);

        *(s32*)&poly->r1 = arg7;
        *(s32*)&poly->r2 = 0;
        *(s32*)&poly->r3 = 0;

        setXY4(poly, x0, y0, x1, y1, x2, y2, x3, y3);

        addPrim(ot, poly);
        poly++;
    }

    func_800D7F20(poly);
}

s32 func_800D822C(SVECTOR* worldPos, s16* outScreenX, s16* outScreenY) // 0x800D822C
{
    DVECTOR screenCoords[2];
    s32     depth;
    s32     scale;
    s16     screenX;
    s16     screenY;

    depth = RotTransPers(worldPos, &screenCoords[0], &screenCoords[1], &screenCoords[1]);
    scale = (ReadGeomScreen() * 200) / (depth + 1);

    screenX = screenCoords[0].vx;
    screenY = screenCoords[0].vy;

    *outScreenX = screenX;
    *outScreenY = screenY;
    return scale;
}

void func_800D82AC(GsOT_TAG* ot, s32 arg1, s32 arg2, s32 arg3) // 0x800D82AC
{
    s32 val1;
    s32 val2;

    val1 = Q12_MULT_PRECISE(arg3, 3000);
    val2 = Q12_MULT_PRECISE(arg3, 5000);

    func_800D7F2C(ot, 16, D_800EBC14, val2, val1, arg1, arg2, 0x141414);
    func_800D7F2C(ot, 12, 0, val2, val1, arg1, arg2, 0x141414);

    D_800EBC14 += 4;

    func_800D7F2C(ot, 4, -512,
                  Q12_MULT_PRECISE(arg3, 15000), Q12_MULT_PRECISE(arg3, 1500),
                  arg1, arg2, 0x102020);
}

s32 func_800D8438(s32 idx) // 0x800D8438
{
    return D_800EBC18[idx];
}

void func_800D8454(s32* arg0, s32 x, s32 y, s32 s) // 0x800D8454
{
    s32      i;
    s32      j;
    s32      col0;
    s32      col1;
    q19_12   angle;
    q19_12   x0;
    q19_12   y0;
    q19_12   w0;
    q19_12   h0;
    q19_12   x1;
    q19_12   y1;
    q19_12   w1;
    q19_12   h1;
    q19_12   sp34;
    q20_12   var_s1;
    s32      temp;
    POLY_G4* poly;

    sp34 = Q12(25.0f);
    angle = Q12_ANGLE(0.0f);

    x = Q12(x);
    y = Q12(y);
    s = Q12_MULT_PRECISE(s, Q12(1.5f));

    poly = (POLY_G4*)func_800D7F10();
    temp = 8;

    for (i = 0; i < 32; i++)
    {
        w0  = Math_Sin(angle);
        h0  = Math_Cos(angle);
        angle = angle + Q12_ANGLE(11.25f);
        w1  = Math_Sin(angle);
        h1  = Math_Cos(angle);

        w0 = (w0 * s) / temp;
        h0 = (h0 * s) / temp;
        w1 = (w1 * s) / temp;
        h1 = (h1 * s) / temp;

        var_s1 = Q12(200.0f);

        x0 = x;
        y0 = y;
        x1 = x;
        y1 = y;

        for (j = 0; j < temp; j++)
        {
            poly->x0 = FP_FROM(x0, Q12_SHIFT);
            poly->x1 = FP_FROM(x0 + w0, Q12_SHIFT);
            poly->x2 = FP_FROM(x1, Q12_SHIFT);
            poly->x3 = FP_FROM(x1 + w1, Q12_SHIFT);

            poly->y0 = FP_FROM(y0, Q12_SHIFT);
            poly->y1 = FP_FROM(y0 + h0, Q12_SHIFT);
            poly->y2 = FP_FROM(y1, Q12_SHIFT);
            poly->y3 = FP_FROM(y1 + h1, Q12_SHIFT);

            col0 = func_800D8438(FP_FROM(var_s1, Q12_SHIFT));
            col1 = func_800D8438(FP_FROM(var_s1 - sp34, Q12_SHIFT));

            *(s32*)&poly->r0 = col0;

            SetPolyG4(poly);
            *(s32*)&poly->r1 = col1;
            *(s32*)&poly->r2 = col0;
            *(s32*)&poly->r3 = col1;

            setSemiTrans(poly, 1);

            addPrim(arg0, poly);

            x0     += w0;
            x1     += w1;
            y0     += h0;
            y1     += h1;
            var_s1 -= sp34;
            poly++;
        }
    }

    func_800D7F20((u8*)poly);
}

void func_800D8738(void* ot, s32 abr) // 0x800D8738
{
    DR_MODE* drMode;

    drMode = func_800D7F10();
    SetDrawMode(drMode, 0, 1, getTPage(0, abr, 640, 0), NULL);
    addPrim(ot, drMode);

    func_800D7F20(&drMode[1]);
}

void func_800D87D4(void* ot) // 0x800D87D4
{
    SVECTOR worldPos;
    s16     screenX;
    s16     screenY;
    s32     screenDepth;

    Math_SVectorSet(&worldPos, 0, 0, 0);

    screenDepth = func_800D822C(&worldPos, &screenX, &screenY);
    if (screenDepth <= 100)
    {
        func_800D82AC(ot, screenX, screenY, screenDepth);
        func_800D8454(ot, screenX, screenY, screenDepth);
        func_800D8738(ot, 1);
    }
}

void func_800D8858(s32 arg0) // 0x800D8858
{
    GsOT_TAG* ot;
    s32       bufferIdx;

    if (arg0 < 3)
    {
        bufferIdx = g_ActiveBufferIdx;
        ot        = g_OrderingTable0[bufferIdx].org;
        ot        = &ot[300];

        func_800D7BF4(&D_800EC018[arg0], 0);
        func_800D87D4(ot);
    }
}

void func_800D88C4(void) // 0x800D88C4
{
}

void func_800D88CC(void) // 0x800D88CC
{
    D_800F3D8C = 0;
}

void func_800D88D8(void) // 0x800D88D8
{
    D_800F3D8C = 1;
}

s_800F3D48_0* func_800D88E8(s_800F3D48* arg0) // 0x800D88E8
{
    s_800F3D48_0* next;
    s_800F3D48_0* curPtr;
    s32           field8Value;

    curPtr      = arg0->ptr_0;
    field8Value = curPtr->field_8;

    if (field8Value == 1)
    {
        curPtr = curPtr->next_4;
        next   = curPtr->next_4;
    }
    else
    {
        next = curPtr->next_4;
    }

    if (arg0->field_4.field_0 <= 0)
    {
        if (field8Value != 2 && g_DeltaTime != Q12(0.0f))
        {
            arg0->ptr_0           = &curPtr[1];
            arg0->field_4.field_0 = curPtr[1].field_0;
        }
    }
    else
    {
        arg0->field_4.field_0--;
    }

    return next;
}

void func_800D8954(s_800F3D48* arg0, s_800F3D48_0_0* arg1) // 0x800D8954
{
    SVECTOR   sp10; // Q23.8
    DVECTOR   sp18[2];
    s32       sp20;
    s16       x0;
    s16       y0;
    s32       offsetX;
    s32       offsetY;
    s32       temp_lo_4;
    s32       temp_lo_5;
    s32       temp_s1;
    s32       temp_s3;
    s32       temp_t0;
    s32       temp_v0;
    s32       temp;
    s32       temp2;
    s32       bufferIdx;
    s32       otIdx;
    s32       temp5;
    s32       temp6;
    GsOT_TAG* ot;
    POLY_FT4* poly;

    temp5   = 0x10101;
    temp_s3 = arg0->field_4.field_3C * temp5;

    sp10.vx = Q12_TO_Q8(arg0->field_4.field_18.vx);
    sp10.vy = Q12_TO_Q8(arg0->field_4.field_18.vy);
    sp10.vz = Q12_TO_Q8(arg0->field_4.field_18.vz);

    temp_s1 = RotTransPers(&sp10, &sp18[0], &sp18[1], &sp20);

    if (sp20 & 0x20000)
    {
        return;
    }

    temp_v0 = ReadGeomScreen();
    temp_t0 = arg0->field_4.field_14;

    offsetX = arg1->field_4;
    offsetY = arg1->field_6;

    offsetX = ((offsetX * temp_v0) / 4) / temp_s1;
    offsetY = ((offsetY * temp_v0) / 4) / temp_s1;

    temp_lo_4 = ((arg1->field_C / 4) * temp_v0) / temp_s1;
    temp_lo_5 = ((arg1->field_E / 4) * temp_v0) / temp_s1;

    offsetX = Q12_MULT_PRECISE(offsetX, temp_t0);
    offsetY = Q12_MULT_PRECISE(offsetY, temp_t0);

    temp  = Q12_MULT_PRECISE(temp_lo_4, temp_t0);
    temp2 = Q12_MULT_PRECISE(temp_lo_5, temp_t0);

    temp6   = sp18[0].vy;
    x0 = sp18[0].vx - temp;
    y0 = temp6 - temp2;

    if (x0 < (-offsetX - 160) || x0 > 160 ||
        y0 < (-offsetY - 160) || y0 > 112)
    {
        return;
    }

    poly = GsOUT_PACKET_P;

    setXY4(poly,
           x0, y0,
           x0 + offsetX, y0,
           x0, y0 + offsetY,
           x0 + offsetX, y0 + offsetY);

    setUV4(poly, arg1->field_0, arg1->field_2, arg1->field_0 + arg1->field_4, arg1->field_2,
           arg1->field_0, arg1->field_2 + arg1->field_6, arg1->field_0 + arg1->field_4, arg1->field_2 + arg1->field_6);

    *(s32*)&poly->r0 = temp_s3;
    poly->tpage      = arg1->field_8;
    poly->clut       = arg1->field_A + arg0->field_4.field_E;

    setPolyFT4(poly);
    setSemiTrans(poly, 1);

    bufferIdx = g_ActiveBufferIdx;
    ot        = g_OrderingTable0[bufferIdx].org;
    otIdx     = temp_s1 >> 1;
    ot        = &ot[otIdx];

    addPrim(ot, poly);
    poly++;

    GsOUT_PACKET_P = poly;
}

void func_800D8CD4(q19_12 rotZ, SVECTOR* rot) // 0x800D8CD4
{
    MATRIX      transformMat;
    VECTOR      offset; // Rotation offset?
    SVECTOR     rot1;
    SVECTOR     rot0;
    q19_12      rotY;
    s_800F3D58* ptr;

    ptr = &D_800F3D58;

    ApplyRotMatrix(rot, &offset);

    offset.vx += ptr->mat_10.t[0];
    offset.vy += ptr->mat_10.t[1];
    offset.vz += ptr->mat_10.t[2];

    TransMatrix(&transformMat, &offset);
    SetTransMatrix(&transformMat);
    vwGetViewAngle(&rot0);

    rot1.vx = Q12_ANGLE(0.0f);
    rot1.vz = -rotZ;
    rotY    = rot0.vy;
    rot1.vy = rotY;

    Math_RotMatrixZxy(&rot1, &transformMat);
    SetMulRotMatrix(&transformMat);
}

void func_800D8D90(s_800F3D48* arg0, s_800F3D48_0_0* arg1) // 0x800D8D90
{
    SVECTOR   sp28;
    SVECTOR   sp30;
    SVECTOR   sp38;
    SVECTOR   sp40;
    SVECTOR   sp48;
    DVECTOR   sp50[4];
    s32       sp60;
    s32       sp64;
    s32       temp_a2;
    s32       temp_t1;
    s32       temp_s2;
    s32       temp_v0;
    s32       bufferIdx;
    s32       otIdx;
    s32       temp;
    GsOT_TAG* ot;
    POLY_FT4* poly;

    PushMatrix();

    sp28.vx = Q12_TO_Q8(arg0->field_4.field_18.vx);
    sp28.vy = Q12_TO_Q8(arg0->field_4.field_18.vy);
    sp28.vz = Q12_TO_Q8(arg0->field_4.field_18.vz);
    func_800D8CD4(arg0->field_4.field_38, &sp28);

    temp_t1 = arg1->field_4;
    temp_v0 = arg0->field_4.field_14;
    temp_a2 = arg1->field_6;

    temp_t1 = Q12_MULT_PRECISE(temp_t1, temp_v0);
    temp_a2 = Q12_MULT_PRECISE(temp_a2, temp_v0);

    temp = 0x10101;

    sp30.vx = -temp_t1;
    sp30.vy = -temp_a2;
    sp30.vz = 0;

    sp38.vx = temp_t1;
    sp38.vy = -temp_a2;
    sp38.vz = 0;

    sp40.vx = -temp_t1;
    sp40.vy = temp_a2;
    sp40.vz = 0;

    sp48.vx = temp_t1;
    sp48.vy = temp_a2;
    sp48.vz = 0;

    temp_s2 = RotTransPers4(&sp30, &sp38, &sp40, &sp48, &sp50[0], &sp50[1], &sp50[2], &sp50[3], &sp60, &sp64);

    PopMatrix();

    if (sp64 & 0x60000)
    {
        return;
    }

    poly = GsOUT_PACKET_P;

    *(s32*)&poly->x0 = *(s32*)&sp50[0];
    *(s32*)&poly->x1 = *(s32*)&sp50[1];
    *(s32*)&poly->x2 = *(s32*)&sp50[2];
    *(s32*)&poly->x3 = *(s32*)&sp50[3];

    setUV4(poly, arg1->field_0, arg1->field_2, arg1->field_0 + arg1->field_4, arg1->field_2,
           arg1->field_0, arg1->field_2 + arg1->field_6, arg1->field_0 + arg1->field_4, arg1->field_2 + arg1->field_6);

    *(s32*)&poly->r0 = arg0->field_4.field_3C * temp;
    poly->tpage      = arg1->field_8;
    poly->clut       = arg1->field_A;

    setPolyFT4(poly);
    setSemiTrans(poly, 1);

    bufferIdx = g_ActiveBufferIdx;
    ot        = g_OrderingTable0[bufferIdx].org;
    otIdx     = temp_s2 >> 1;
    ot        = &ot[otIdx];

    addPrim(ot, poly);
    poly++;

    GsOUT_PACKET_P = poly;
}

s_800F3D48* func_800D905C(void) // 0x800D905C
{
    s32         i;
    s_800F3D48* ptr;

    ptr = D_800F3D48;

    for (i = 0; i < D_800F2438; i++, ptr++)
    {
        s_800F3D48_4* ptr2 = &ptr->field_4;

        if (ptr2->field_4 != 0 || ptr2->field_6 != 0)
        {
            continue;
        }

        ptr2->field_6  = 1;
        ptr2->field_C  = 0;
        ptr2->field_8  = 0;
        ptr2->field_40 = 0;
        ptr2->field_E  = 0;
        ptr2->field_0  = 0;

        return ptr;
    }

    return NULL;
}

void func_800D90C8(void) // 0x800D90C8
{
    s_800F3D58* ptr;

    ptr = &D_800F3D58;

    Vw_WorldScreenMatrixAtPositionGet(&ptr->mat_10, ptr->field_0.vx, 0, ptr->field_0.vz);
    SetRotMatrix(&ptr->mat_10);
    SetTransMatrix(&ptr->mat_10);
}

void func_800D9114(s_800F3D48* arg0) // 0x800D9114
{
    arg0->field_4.field_18.vz += Q12_MULT_PRECISE(arg0->field_4.field_8, g_DeltaTime);

    if (g_DeltaTime != Q12(0.0f))
    {
        arg0->field_4.field_3C -= arg0->field_4.field_40;
        arg0->field_4.field_3C  = MAX(0, arg0->field_4.field_3C);
    }
}

void func_800D917C(void) // 0x800D917C
{
    s32             i;
    s_800F3D48*     curPtr;
    s_800F3D48_0*   ptr1;
    s_800F3D48_0_0* ptr2;

    curPtr = D_800F3D48;

    func_800D90C8();

    for (i = 0; i < D_800F2438; i++, curPtr++)
    {
        if (curPtr->field_4.field_4 != 0)
        {
            if (curPtr->field_4.field_44 != NULL)
            {
                if (D_800F3D8C == 0)
                {
                    ptr1 = curPtr->field_4.field_44(curPtr);
                    if (ptr1 != NULL && curPtr->field_4.field_48 != NULL && D_800F3D90 == 0)
                    {
                        curPtr->field_4.field_48(curPtr, ptr1);
                    }
                }
                else if (curPtr->field_4.field_48 != NULL && D_800F3D90 == 0)
                {
                    // TODO: `func_800D88E8` returns different struct.
                    ptr2 = (s_800F3D48_0_0*)func_800D88E8(curPtr);
                    curPtr->field_4.field_48(curPtr, ptr2);
                }

                func_800D9114(curPtr);
            }
        }
    }

    curPtr = D_800F3D48;
    for (i = 0; i < D_800F2438; i++, curPtr++)
    {
        if (curPtr->field_4.field_6 != 0)
        {
            curPtr->field_4.field_4 = 1;
            curPtr->field_4.field_6 = 0;

            if (curPtr->field_4.field_44 != NULL)
            {
                if (D_800F3D8C == 0)
                {
                    ptr1 = curPtr->field_4.field_44(curPtr);

                    if (ptr1 != NULL && curPtr->field_4.field_48 != NULL && D_800F3D90 == 0)
                    {
                        curPtr->field_4.field_48(curPtr, ptr1);
                    }
                }
                else if (curPtr->field_4.field_48 != NULL && D_800F3D90 == 0)
                {
                    // TODO: `func_800D88E8` returns different struct.
                    ptr2 = (s_800F3D48_0_0*)func_800D88E8(curPtr);
                    curPtr->field_4.field_48(curPtr, ptr2);
                }
            }
        }
    }
}

void func_800D9394(void) // 0x800D9394
{
    s_FsImageDesc image;

    image.tPage[0] = 0;
    image.tPage[1] = 55;
    image.u        = 0;
    image.v        = 0;
    image.clutX    = 80;
    image.clutY    = 0;
    Fs_QueueStartReadTim(FILE_TIM_ELAST_TIM, FS_BUFFER_1, &image);

    image.tPage[0] = 0;
    image.tPage[1] = 56;
    image.u        = 0;
    image.v        = 0;
    image.clutX    = 96;
    image.clutY    = 0;
    Fs_QueueStartReadTim(FILE_TIM_ELAST2_TIM, FS_BUFFER_1, &image);

    image.tPage[0] = 0;
    image.tPage[1] = 54;
    image.u        = 0;
    image.v        = 0;
    image.clutX    = 64;
    image.clutY    = 0;
    Fs_QueueStartReadTim(FILE_TIM_EF1_TIM, FS_BUFFER_1, &image);

    image.tPage[0] = 0;
    image.tPage[1] = 57;
    image.u        = 0;
    image.v        = 0;
    image.clutX    = 112;
    image.clutY    = 0;
    Fs_QueueStartReadTim(FILE_TIM_ELAST3_TIM, FS_BUFFER_1, &image);
}

void func_800D947C(void) // 0x800D947C
{
    s_800F3D48* ptr1;
    s32         i;
    s_800F3D58* ptr0;

    D_800F3D48 = (s_800F3D48*)FS_BUFFER_27;
    D_800F2438 = 80;

    ptr0 = &D_800F3D58;

    memset(D_800F3D48, 0xA7, 0x1900);

    ptr1 = D_800F3D48;

    for (i = 0; i < D_800F2438; i++, ptr1++)
    {
        ptr1->field_4.field_4 = 0;
        ptr1->field_4.field_6 = 0;
    }

    D_800F3D8C = 0;

    ptr0->field_0.vx = Q12(64.0f);
    ptr0->field_0.vy = Q12(0.0f);
    ptr0->field_0.vz = Q12(-64.0f);
}

void func_800D952C(void) // 0x800D952C
{
    s32         i;
    s_800F3D58* ptr0;
    s_800F3D48* ptr1;

    D_800F3D48 = &D_800F2448;
    D_800F2438 = 80;

    ptr0 = &D_800F3D58;

    memset(&D_800F2448, 0xA5, 0x1900);

    ptr1 = D_800F3D48;

    for (i = 0; i < D_800F2438; i++, ptr1++)
    {
        ptr1->field_4.field_4 = 0;
        ptr1->field_4.field_6 = 0;
    }

    D_800F3D8C = 0;

    ptr0->field_0.vx = Q12(64.0f);
    ptr0->field_0.vy = Q12(0.0f);
    ptr0->field_0.vz = Q12(-64.0f);
}

s_800F3D48_0* func_800D95D4(s_800F3D48* arg0) // 0x800D95D4
{
    s_800F3D48_0* result;

    arg0->field_4.field_18.vx += Q12_MULT_PRECISE(arg0->field_4.field_28.vx, g_DeltaTime);
    arg0->field_4.field_18.vy += Q12_MULT_PRECISE(arg0->field_4.field_28.vy, g_DeltaTime);
    arg0->field_4.field_18.vz += Q12_MULT_PRECISE(arg0->field_4.field_28.vz, g_DeltaTime);

    result = func_800D88E8(arg0);

    if (arg0->ptr_0->field_8 == 2)
    {
        arg0->field_4.field_4 = 0;
        arg0->field_4.field_6 = 0;
    }

    arg0->field_4.field_28.vx = Q12_MULT_FLOAT_PRECISE(arg0->field_4.field_28.vx, 0.8f);
    arg0->field_4.field_28.vy = Q12_MULT_FLOAT_PRECISE(arg0->field_4.field_28.vy, 0.8f);
    arg0->field_4.field_28.vz = Q12_MULT_FLOAT_PRECISE(arg0->field_4.field_28.vz, 0.8f);

    return result;
}

s_800F3D48_0* func_800D9740(s_800F3D48* arg0) // 0x800D9740
{
    s_800F3D48_0* ptr;

    arg0->field_4.field_18.vx += Q12_MULT_PRECISE(arg0->field_4.field_28.vx, g_DeltaTime);
    arg0->field_4.field_18.vy += Q12_MULT_PRECISE(arg0->field_4.field_28.vy, g_DeltaTime);
    arg0->field_4.field_18.vz += Q12_MULT_PRECISE(arg0->field_4.field_28.vz, g_DeltaTime);

    ptr = func_800D88E8(arg0);

    if (arg0->ptr_0->field_8 == 2)
    {
        arg0->field_4.field_4 = 0;
        arg0->field_4.field_6 = 0;
    }

    return ptr;
}

void func_800D982C(s_800F3D48* arg0) // 0x800D982C
{
    s32         rand;
    s32         temp;
    s_800F3D48* ptr;

    ptr = func_800D905C();

    if (ptr != NULL)
    {
        ptr->field_4.field_18 = arg0->field_4.field_18;
        rand                  = (Rng_Rand16() / 41) + 0x4CC;

        ptr->field_4.field_28.vx = Q12_MULT_PRECISE(arg0->field_4.field_28.vx, rand);
        ptr->field_4.field_28.vy = Q12_MULT_PRECISE(arg0->field_4.field_28.vy, rand);
        ptr->field_4.field_28.vz = Q12_MULT_PRECISE(arg0->field_4.field_28.vz, rand);

        temp = arg0->field_4.field_14;

        ptr->ptr_0 = &D_800EC5A8;

        ptr->field_4.field_44 = func_800D9740;
        ptr->field_4.field_48 = func_800D8D90;

        ptr->field_4.field_14 = temp;
        ptr->field_4.field_3C = arg0->field_4.field_3C;
        ptr->field_4.field_38 = arg0->field_4.field_38;
    }
}

void func_800D997C(s_800F3D48* arg0) // 0x800D997C
{
    q19_12      randAngle;
    s_800F3D48* ptr;

    ptr = func_800D905C();

    if (ptr != NULL)
    {
        ptr->field_4.field_3C    = arg0->field_4.field_3C;
        ptr->field_4.field_18    = arg0->field_4.field_18;
        ptr->field_4.field_18.vy = 0;

        randAngle = Rng_Rand16();

        ptr->field_4.field_28.vx = Q12_MULT_PRECISE(Math_Sin(randAngle), Q12(1.0f));
        ptr->field_4.field_28.vy = Q12(0.0f);
        ptr->field_4.field_28.vz = Q12_MULT_PRECISE(Math_Cos(randAngle), Q12(1.0f));

        ptr->field_4.field_14 = Q12_MULT_PRECISE(arg0->field_4.field_14, Q12(2.0f));

        ptr->ptr_0            = &D_800EC53C;
        ptr->field_4.field_44 = func_800D95D4;
        ptr->field_4.field_48 = func_800D8954;
    }
}

void func_800D9AA0(s_800F3D48* arg0) // 0x800D9AA0
{
    s32         temp;
    s_800F3D48* ptr;

    ptr = func_800D905C();

    if (ptr != NULL)
    {
        ptr->field_4.field_18 = arg0->field_4.field_18;
        ptr->field_4.field_3C = arg0->field_4.field_3C;

        temp = arg0->field_4.field_14;

        ptr->ptr_0 = &D_800EC614;

        ptr->field_4.field_28.vx = Q12(0.0f);
        ptr->field_4.field_28.vz = Q12(0.0f);

        ptr->field_4.field_44 = func_800D9740;
        ptr->field_4.field_48 = func_800D8954;
        ptr->field_4.field_14 = temp;

        ptr->field_4.field_18.vy += Q12_MULT_PRECISE(temp, Q12(-0.25f));
        ptr->field_4.field_28.vy  = Q12_MULT_PRECISE(temp, Q12(-1.0f));
    }
}

void func_800D9B90(s_800F3D48* arg0) // 0x800D9B90
{
    s32         temp;
    s32         temp2;
    s_800F3D48* ptr;

    ptr = func_800D905C();

    if (ptr != NULL)
    {
        ptr->field_4.field_18 = arg0->field_4.field_18;

        temp2 = arg0->field_4.field_14;
        temp  = arg0->field_4.field_3C;

        ptr->field_4.field_28.vx = Q12(0.0f);
        ptr->field_4.field_28.vz = Q12(0.0f);
        ptr->field_4.field_28.vy = Q12(1.0f);

        ptr->ptr_0            = &D_800EC53C;
        ptr->field_4.field_44 = func_800D9740;
        ptr->field_4.field_48 = func_800D8954;
        ptr->field_4.field_3C = temp;
        ptr->field_4.field_14 = temp2;
    }
}

s_800F3D48_0* func_800D9C20(s_800F3D48* arg0) // 0x800D9C20
{
    VECTOR3       sfxPos; // Q19.12
    s_800F3D48_0* ret;
    s_800F3D58*   ptr;

    ret = NULL;

    ptr = &D_800F3D58;

    switch (arg0->field_4.field_C)
    {
        case 0:
            arg0->ptr_0            = &D_800EC680[Rng_Rand16() / Q12(1.0f)];
            arg0->field_4.field_48 = func_800D8954;

            if (func_800D5D48() != false)
            {
                sfxPos.vx = arg0->field_4.field_18.vx + ptr->field_0.vx;
                sfxPos.vy = arg0->field_4.field_18.vy + ptr->field_0.vy;
                sfxPos.vz = arg0->field_4.field_18.vz + ptr->field_0.vz;
                func_8005DC1C(Sfx_Unk1692, &sfxPos, Q8_CLAMPED(1.0f), SfxFlag_None);
            }

            arg0->field_4.field_C++;

        case 1:
            ret = func_800D88E8(arg0);
            if (ret == &D_800EC34C)
            {
                func_800D9AA0(arg0);
            }

            if (Rng_Rand16() == 0)
            {
                func_800D9B90(arg0);
            }

            if (arg0->field_4.field_10 < Q12(0.0f))
            {
                arg0->field_4.field_10 = Q12(0.7f);
                arg0->field_4.field_C++;
            }
            break;

        case 2:
            ret                    = func_800D88E8(arg0);
            arg0->field_4.field_3C = Q12_MULT_PRECISE(arg0->field_4.field_3C, Q12(0.9f));
            if (arg0->field_4.field_10 < Q12(0.0f))
            {
                arg0->field_4.field_4 = 0;
                arg0->field_4.field_6 = 0;
            }
            break;
    }

    arg0->field_4.field_10 -= g_DeltaTime;
    return ret;
}

s_800F3D48_0* func_800D9DF8(s_800F3D48* arg0) // 0x800D9DF8
{
    s_CollisionSurface surface;
    SVECTOR            sp20;
    q19_12             groundHeight;
    s32                i;
    s_800F3D48_0*      ret;
    s_800F3D58*        ptr;

    ret = NULL;

    ptr = &D_800F3D58;

    switch (arg0->field_4.field_C)
    {
        case 0:
            sp20.vx = Q12_TO_Q8(arg0->field_4.field_18.vx);
            sp20.vy = Q12_TO_Q8(arg0->field_4.field_18.vy);
            sp20.vz = Q12_TO_Q8(arg0->field_4.field_18.vz);

            arg0->field_4.field_18.vx += Q12_MULT_PRECISE(arg0->field_4.field_28.vx, g_DeltaTime);
            arg0->field_4.field_18.vy += Q12_MULT_PRECISE(arg0->field_4.field_28.vy, g_DeltaTime);
            arg0->field_4.field_18.vz += Q12_MULT_PRECISE(arg0->field_4.field_28.vz, g_DeltaTime);

            if (arg0->field_4.field_18.vy > Q12(5.0f))
            {
                arg0->field_4.field_4 = 0;
                arg0->field_4.field_6 = 0;
            }
            else
            {
                PushMatrix();

                groundHeight = arg0->field_4.field_18.vy + ptr->field_0.vy;

                Collision_SurfaceGet(&surface, arg0->field_4.field_18.vx + ptr->field_0.vx,
                                     arg0->field_4.field_18.vz + ptr->field_0.vz);
                PopMatrix();

                if (surface.groundHeight < groundHeight)
                {
                    arg0->field_4.field_18.vy = surface.groundHeight;
                    arg0->field_4.field_48    = NULL;
                    arg0->field_4.field_10    = Q12(5.0f);
                    arg0->field_4.field_C++;

                    for (i = 0; i < 5; i++)
                    {
                        func_800D997C(arg0);
                    }
                }
            }

            ret = func_800D88E8(arg0);

            if (ret == &D_800EC3EC)
            {
                func_800D982C(arg0);
            }
            break;

        case 1:
            arg0->field_4.field_C  = 0;
            arg0->field_4.field_10 = Q12(5.0f);
            arg0->field_4.field_44 = func_800D9C20;
            arg0->field_4.field_14 = Q12_MULT_PRECISE(arg0->field_4.field_14, Q12(2.0f));
            break;
    }

    arg0->field_4.field_10 -= g_DeltaTime;
    return ret;
}

void func_800DA04C(void) // 0x800DA04C
{
    s_800F3D48* curPtr;
    s32         i;

    curPtr = D_800F3D48;
    for (i = 0; i < D_800F2438; i++, curPtr++)
    {
        curPtr->field_4.field_4 = 0;
        curPtr->field_4.field_6 = 0;
    }
}

q19_12 func_800DA08C(q19_12 arg0, q19_12 arg1, q19_12 arg2) // 0x800DA08C
{
    q19_12 scaledArg0;
    q19_12 scaledArg1;

    switch (arg2)
    {
        case 0:
            if (arg1 < arg0)
            {
                q19_12 temp = arg0;
                arg0        = arg1;
                arg1        = temp;
            }

            // TODO: Unsure what 0x6486 is meant to be.
            // 0x6486 = `Q12(6.2828f)`, while `sqrt(6.2828)` is 2.50655141579
            // `Q12(SQUARE(2.5f))` is very close, but gives 0x6400 instead of 0x6486...
            // Maybe 6.2828 is approximation of `PI * 2`? Doesn't work with our `PI` macro though.
            scaledArg0 = Q12_MULT_PRECISE(Q12_MULT_PRECISE(arg0, arg0), 0x6486);
            scaledArg1 = Q12_MULT_PRECISE(Q12_MULT_PRECISE(arg1, arg1), 0x6486);
            return scaledArg1 - scaledArg0;

        case 1:
            return Q12_MULT_PRECISE(arg0, arg1);

        default:
            return Q12(0.0f);
    }
}

q19_12 func_800DA178(q19_12 arg0, q19_12 arg1, q19_12 arg2, q19_12 arg3, q19_12 arg4) // 0x800DA178
{
    q19_12 temp_t0;

    if (arg2 < arg1)
    {
        temp_t0 = arg1;
        arg1    = arg2;
        arg2    = temp_t0;
    }

    temp_t0 = arg2 - arg1;

    arg0 = Q12_MULT_PRECISE(arg0, arg3);
    if (arg4 != Q12(0.0f) && temp_t0 != Q12(0.0f))
    {
        arg0 = Q12_MULT_PRECISE(arg0, temp_t0);
    }
    else
    {
        arg0 = Q12_MULT_PRECISE(arg0, g_DeltaTime);
    }
    return arg0;
}

s32 func_800DA1F4(VECTOR3* arg0, VECTOR3* arg1, q19_12 arg2, s32 arg3, s32 arg4) // 0x800DA1F4
{
    q19_12   temp_a0;
    s32      dist;
    s32      sinAngle;
    q19_12   randAngle;
    s32      var_fp;
    s32      temp_s0;
    VECTOR3* ptr;

    var_fp = 0x80;

    ptr = &D_800F3D58.field_0;

    switch (arg4)
    {
        case 0:
            temp_s0 = (arg3 - arg2) >> 3;
            temp_a0 = Rng_Rand16() / ((0x7FFF / temp_s0) + 1);
            temp_a0 = temp_a0 * 8;
            dist = arg2 + temp_a0;
            var_fp  = (Q12(10.0f) - temp_a0) / 320;

            randAngle = Rng_Rand16();

            sinAngle = Q12_MULT_PRECISE(Math_Sin(randAngle), dist);
            randAngle = Q12_MULT_PRECISE(Math_Cos(randAngle), dist);

            arg1->vx = (sinAngle + arg0->vx) - ptr->vx;
            arg1->vy = arg0->vy - ptr->vy;
            arg1->vz = (randAngle + arg0->vz) - ptr->vz;
            break;

        case 1:
            temp_a0 = Rng_Rand16() / (0x7FFF / arg2 + 1);
            sinAngle = temp_a0 - (arg2 / 2);
            temp_a0 = Rng_Rand16() / (0x7FFF / arg3 + 1);

            arg1->vx = (sinAngle + arg0->vx) - ptr->vx;
            arg1->vy = arg0->vy - ptr->vy;
            temp_a0  = temp_a0 - arg3 / 2;
            arg1->vz = (temp_a0 + arg0->vz) - ptr->vz;
            break;
    }

    return var_fp;
}

q19_12 func_800DA420(VECTOR3* result) // 0x800DA420
{
    q19_12 posX;
    q19_12 posY;

    posX = Q12_MULT_PRECISE(Math_Sin(Q12_ANGLE(15.0f)), Q12(5.0f));
    posY = Q12_MULT_PRECISE(Math_Cos(Q12_ANGLE(15.0f)), Q12(5.0f));

    result->vx = posX;
    result->vy = posY;
    result->vz = Q12(0.0f);
    return Q12_ANGLE(15.0f);
}

void func_800DA4B4(s32* arg0, s32* arg1) // 0x800DA4B4
{
    arg0[0] += (arg1[0] * arg0[1]) / arg1[1];
}

s32 func_800DA4EC(s32 min, s32 max) // 0x800DA4EC
{
    s32 range;

    if (max < min)
    {
        range = min;
        min   = max;
        max   = range;
    }

    range = max - min;
    min  += Rng_Rand16() / ((0x7FFF / range) + 1);
    return min;
}

void func_800DA550(s_800ED7E0_ptr* arg0) // 0x800DA550
{
    s32         temp_s4;
    s_800F3D48* ptr;

    ptr = func_800D905C();

    if (ptr == NULL)
    {
        return;
    }

    ptr->field_4.field_3C = func_800DA1F4(arg0, &ptr->field_4.field_18, arg0->field_C, arg0->field_10, arg0->field_24);
    ptr->field_4.field_14 = func_800DA4EC(arg0->field_1C, arg0->field_20);
    temp_s4               = func_800DA4EC(arg0->field_14, arg0->field_18);

    switch (arg0->field_28)
    {
        case 0:
            ptr->field_4.field_8  = arg0->field_2C;
            ptr->field_4.field_40 = arg0->field_30;
            ptr->field_4.field_38 = func_800DA420(&ptr->field_4.field_28);

            func_800DA4B4(&ptr->field_4.field_18, &ptr->field_4.field_28);

            ptr->ptr_0                = &D_800EC6EC;
            ptr->field_4.field_44     = func_800D9DF8;
            ptr->field_4.field_48     = func_800D8D90;
            ptr->field_4.field_18.vx += Q12_MULT_PRECISE(ptr->field_4.field_28.vx, temp_s4);
            ptr->field_4.field_18.vy += Q12_MULT_PRECISE(ptr->field_4.field_28.vy, temp_s4);
            break;

        case 1:
            ptr->field_4.field_14 *= 2;
            ptr->field_4.field_8   = arg0->field_2C;
            ptr->field_4.field_40  = arg0->field_30;
            ptr->ptr_0             = &D_800EC680[Rng_Rand16() / Q12(1.0f)];
            ptr->field_4.field_44  = func_800D9C20;
            ptr->field_4.field_10  = temp_s4;
            ptr->field_4.field_48  = func_800D8954;
            break;

        case 2:
            ptr->field_4.field_38 = func_800DA420(&ptr->field_4.field_28);
            func_800DA4B4(&ptr->field_4.field_18, &ptr->field_4.field_28);
            break;
    }
}

void func_800DA774(s_800ED7E0_ptr* arg0) // 0x800DA774
{
    s32 temp_v0;
    s32 i;
    s32 var_s0_2;
    s32 count;

    if (arg0->field_28 == 99)
    {
        Rng_SetSeed(0);
        func_800DA04C();
        return;
    }

    var_s0_2 = func_800DA178(func_800DA08C(arg0->field_C, arg0->field_10, arg0->field_24),
                             arg0->field_14, arg0->field_18, arg0->field_34, arg0->flags_38 & (1 << 1));

    count     = FP_FROM(var_s0_2, Q12_SHIFT);
    var_s0_2 %= Q12(1.0f);

    temp_v0  = Rng_Rand16();
    temp_v0 %= Q12(1.0f);

    if (var_s0_2 > temp_v0)
    {
        count++;
    }

    if (count > 50)
    {
        Rng_SetSeed(0);
    }

    for (i = 0; i < count; i++)
    {
        func_800DA550(arg0);
    }
}

s_800F3D48_0* func_800DA884(s_800F3D48* arg0) // 0x800DA884
{
    s_800F3D48_0* result;

    switch (arg0->field_4.field_C)
    {
        case 0:
            if (arg0->field_4.field_10 <= 0)
            {
                arg0->field_4.field_10 = 8;
                arg0->field_4.field_C++;
            }
            else
            {
                arg0->field_4.field_10 -= g_DeltaTime;
            }
            break;

        case 1:
            if (arg0->field_4.field_10 < 0)
            {
                arg0->field_4.field_40 = 10;
            }

            arg0->field_4.field_10--;

            arg0->field_4.field_18.vx += Q12_MULT_PRECISE(arg0->field_4.field_28.vx, g_DeltaTime);
            arg0->field_4.field_18.vy += Q12_MULT_PRECISE(arg0->field_4.field_28.vy, g_DeltaTime);
            arg0->field_4.field_18.vz += Q12_MULT_PRECISE(arg0->field_4.field_28.vz, g_DeltaTime);

            result = func_800D88E8(arg0);
            if (arg0->ptr_0->field_8 == 2)
            {
                arg0->field_4.field_4 = 0;
                arg0->field_4.field_6 = 0;
            }

            return result;
    }

    return NULL;
}

void func_800DA9F8(VECTOR3* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x800DA9F8
{
    s_800F3D48_0* sp10[3];
    s_800F3D48*   ptr;
    VECTOR3*      vec;

    memcpy(sp10, D_800CAE30, sizeof(D_800CAE30));

    vec = &D_800F3D58.field_0;

    ptr = func_800D905C();

    if (ptr != NULL)
    {
        ptr->field_4.field_18.vx = arg0->vx - vec->vx;
        ptr->field_4.field_18.vy = arg0->vy - vec->vy;
        ptr->field_4.field_18.vz = arg0->vz - vec->vz;

        ptr->field_4.field_28.vx = 0;
        ptr->field_4.field_28.vy = 0;
        ptr->field_4.field_28.vz = 0;

        ptr->field_4.field_3C = 0x80;
        ptr->field_4.field_14 = arg4;

        ptr->ptr_0 = sp10[arg1];

        ptr->field_4.field_E  = arg2 << 6;
        ptr->field_4.field_44 = func_800DA884;
        ptr->field_4.field_10 = arg3;
        ptr->field_4.field_48 = func_800D8954;
    }
}

void func_800DAB18(VECTOR3* arg0, s32 arg1, s32 arg2, s32 arg3) // 0x800DAB18
{
    s_800F3D48* ptr;
    VECTOR3*    vec;

    vec = &D_800F3D58.field_0;

    ptr = func_800D905C();

    if (ptr != NULL)
    {
        ptr->field_4.field_18.vx = arg0->vx - vec->vx;
        ptr->field_4.field_18.vy = arg0->vy - vec->vy;
        ptr->field_4.field_18.vz = arg0->vz - vec->vz;
        ptr->field_4.field_3C    = 30;
        ptr->field_4.field_28.vx = 0;
        ptr->field_4.field_28.vy = 0;
        ptr->field_4.field_28.vz = 0;
        ptr->ptr_0               = &D_800EC1B8;
        ptr->field_4.field_14    = arg3;
        ptr->field_4.field_E     = arg1 << 6;
        ptr->field_4.field_10    = arg2;
        ptr->field_4.field_44    = func_800DA884;
        ptr->field_4.field_48    = func_800D8954;
    }
}

void func_800DAC04(VECTOR3* arg0, void* arg1, s32 arg2) // 0x800DAC04
{
    s32 i;
    s32 var_s4;

    if (Rng_Rand16() & 0x50)
    {
        var_s4 = 2;
    }
    else
    {
        var_s4 = 3;
    }

    for (i = 0; i < var_s4; i++)
    {
        func_800DA9F8(arg0, Rng_Rand16() / (Q12(2.667f) - 1), arg2, D_800EC758[i], D_800EC764[Rng_Rand16() / (Q12(2.667f) - 1)]);
    }
}

void func_800DACFC(VECTOR3* vec, s32 arg1, s32 arg2) // 0x800DACFC
{
    func_800DAB18(vec, arg2, 0, Q12(2.5f));
    func_800DAC04(vec, arg1, arg2);
}

void func_800DAD54(void) // 0x800DAD54
{
    s32              i;
    s_func_800DAD54* curPtr;
    VECTOR3*         vec;

    vec = &D_800F3D58.field_0;

    curPtr = (s_func_800DAD54*)FS_BUFFER_28;
    for (i = 0; i < 400; i++, curPtr++)
    {
        curPtr->field_28 = 0;
    }

    vec->vx = Q12(64.0f);
    vec->vy = Q12(0.0f);
    vec->vz = Q12(-64.0f);
}

s_func_800DAD54* func_800DAD90(void) // 0x800DAD90
{
    s32              i;
    s_func_800DAD54* curPtr;

    curPtr = (s_func_800DAD54*)FS_BUFFER_28;
    for (i = 0; i < 400; i++, curPtr++)
    {
        if (curPtr->field_28 == 0)
        {
            curPtr->field_4  = 0;
            curPtr->field_28 = 1;
            return curPtr;
        }
    }

    return NULL;
}

void func_800DADE0(s_func_800DAD54* arg0, s_800F3D48_0_0* arg1) // 0x800DADE0
{
    SVECTOR   sp10; // Q23.8
    DVECTOR   sp18[2];
    s32       flags;
    s16       x0;
    s16       y0;
    s32       offsetX;
    s32       offsetY;
    s32       temp_lo_4;
    s32       temp_lo_5;
    s32       temp_s1;
    s32       temp_s3;
    s32       temp_t0;
    s32       temp_v0;
    s32       temp;
    s32       temp2;
    s32       bufferIdx;
    s32       otIdx;
    s32       temp5;
    s32       temp6;
    GsOT_TAG* ot;
    POLY_FT4* poly;

    temp5   = 0x10101;
    temp_s3 = arg0->field_1C * temp5;

    sp10.vx = Q12_TO_Q8(arg0->field_C.vx);
    sp10.vy = Q12_TO_Q8(arg0->field_C.vy);
    sp10.vz = Q12_TO_Q8(arg0->field_C.vz);

    temp_s1 = RotTransPers(&sp10, &sp18[0], &sp18[1], &flags);

    if (flags & (1 << 17))
    {
        return;
    }

    temp_v0 = ReadGeomScreen();
    temp_t0 = arg0->field_8;

    offsetX = arg1->field_4;
    offsetY = arg1->field_6;

    offsetX = ((offsetX * temp_v0) / 4) / temp_s1;
    offsetY = ((offsetY * temp_v0) / 4) / temp_s1;

    temp_lo_4 = ((arg1->field_C / 4) * temp_v0) / temp_s1;
    temp_lo_5 = ((arg1->field_E / 4) * temp_v0) / temp_s1;

    offsetX = Q12_MULT_PRECISE(offsetX, temp_t0);
    offsetY = Q12_MULT_PRECISE(offsetY, temp_t0);

    temp  = Q12_MULT_PRECISE(temp_lo_4, temp_t0);
    temp2 = Q12_MULT_PRECISE(temp_lo_5, temp_t0);

    temp6 = sp18[0].vy;
    x0    = sp18[0].vx - temp;
    y0    = temp6 - temp2;

    if (x0 < (-offsetX - 160) || x0 > 160 ||
        y0 < (-offsetY - 160) || y0 > 112)
    {
        return;
    }

    poly = GsOUT_PACKET_P;

    setXY4(poly,
           x0, y0,
           x0 + offsetX, y0,
           x0, y0 + offsetY,
           x0 + offsetX, y0 + offsetY);

    setUV4(poly, arg1->field_0, arg1->field_2, arg1->field_0 + arg1->field_4, arg1->field_2,
           arg1->field_0, arg1->field_2 + arg1->field_6, arg1->field_0 + arg1->field_4, arg1->field_2 + arg1->field_6);

    *(s32*)&poly->r0 = temp_s3;
    poly->tpage      = arg1->field_8;
    poly->clut       = arg1->field_A;

    setPolyFT4(poly);
    setSemiTrans(poly, 1);

    bufferIdx = g_ActiveBufferIdx;
    ot        = g_OrderingTable0[bufferIdx].org;
    otIdx     = temp_s1 >> 1;
    ot        = &ot[otIdx];

    addPrim(ot, poly);
    poly++;

    GsOUT_PACKET_P = poly;
}

void func_800DB154(GsCOORDINATE2* boneCoords) // 0x800DB154
{
    MATRIX           boneMat;
    VECTOR           boneOffsets[HarryBone_Count];
    s32              i;
    s32              coordCount;
    GsCOORDINATE2*   curBoneCoord;
    s_func_800DAD54* curPtr;
    VECTOR*          boneOffset;
    VECTOR3*         pos;

    curPtr = (s_func_800DAD54*)FS_BUFFER_28;
    coordCount = HarryBone_Count - 1;

    pos = &D_800F3D58.field_0;

    curBoneCoord = boneCoords;
    curBoneCoord++;

    // Get bone offsets.
    for (i = 1; i <= coordCount; i++, curBoneCoord++)
    {
        Vw_CoordHierarchyMatrixCompute(curBoneCoord, &boneMat);

        boneOffsets[i].vx = Q8_TO_Q12(boneMat.t[0]) - pos->vx;
        boneOffsets[i].vy = Q8_TO_Q12(boneMat.t[1]) - pos->vy;
        boneOffsets[i].vz = Q8_TO_Q12(boneMat.t[2]) - pos->vz;
    }

    func_800D90C8();

    for (i = 0; i < 400; i++, curPtr++)
    {
        if (curPtr->field_28 != 0)
        {
            boneOffset         = &boneOffsets[curPtr->field_24];
            curPtr->field_C.vx = boneOffset->vx;
            curPtr->field_C.vy = boneOffset->vy;
            curPtr->field_C.vz = boneOffset->vz;

            // TODO: `func_800D88E8` returns different struct.
            func_800DADE0(curPtr, (s_800F3D48_0_0*)func_800D88E8(curPtr));
        }
    }
}

void func_800DB288(void) // 0x800DB288
{
    s32              i;
    s32              rand;
    s_func_800DAD54* ptr;

    for (i = 1; i < 18; i++)
    {
        ptr = func_800DAD90();

        if (ptr != NULL)
        {
            rand = Rng_Rand16() / Q12(1.0f);

            ptr->field_0 = &D_800EC680[rand];

            rand = Rng_Rand16() / 16;

            ptr->field_8  = rand + Q12(0.5f);
            ptr->field_1C = 0x60;
            ptr->field_24 = i;
        }
    }
}

#include "maps/shared/sharedFunc_800CD6B0_3_s03.h" // 0x800DB338

#include "maps/shared/sharedFunc_800CD7F8_3_s03.h" // 0x800DB480

#include "maps/shared/sharedFunc_800CD920_3_s03.h" // 0x800DB5A8

#include "maps/shared/sharedFunc_800CD940_3_s03.h" // 0x800DB5C8

void func_800DB608(void) // 0x800DB608
{
    s_D_800F48A8* ptr;
    q19_12        speed;

    ptr = &D_800F48A8;

    if (g_DeltaTime != Q12(0.0f))
    {
        speed = (g_SavegamePtr->gameDifficulty == GameDifficulty_Easy) ? Q12(0.2f) : Q12(0.7f);

        // Velocity value based on previously saved player position?
        ptr->velocityX_3C      = ((g_SysWork.playerWork.player.position.vx - ptr->playerPosition_30.vx) * speed) / g_DeltaTime;
        ptr->velocityZ_40      = ((g_SysWork.playerWork.player.position.vz - ptr->playerPosition_30.vz) * speed) / g_DeltaTime;
        ptr->playerPosition_30 = g_SysWork.playerWork.player.position;
    }
    else
    {
        ptr->velocityX_3C = Q12(0.0f);
        ptr->velocityZ_40 = Q12(0.0f);
    }
}

void func_800DB6D0(MATRIX* arg0, const VECTOR* rot0, const VECTOR* rot1, const MATRIX* mat, s32 arg4) // 0x800DB6D0
{
    MATRIX  sp10;
    MATRIX  sp30;
    SVECTOR sp50;
    s32     temp_a3;
    s32     sp5C;
    s32     temp_a0;
    s32     sp64;
    s32     sp68;
    s32     sp6C;
    s32     var_s4;
    s32     var_s5;
    q19_12  angle0;
    q19_12  angle1;
    s32     temp_s6;
    s32     temp_s2;
    q19_12  dist;
    q19_12  angle2;
    s32     var_fp;
    s32     var_s1;
    q19_12  absAngle2;

    angle1 = arg4;

    if (mat != NULL)
    {
        var_s4 = -mat->m[2][0];
        var_s5 = mat->m[0][0];
        sp68   = -mat->m[1][2];
        sp6C   = mat->m[1][1];
    }
    else
    {
        var_s4 = 0;
        var_s5 = Q12(1.0f);
        sp68   = 0;
        sp6C   = Q12(1.0f);
    }

    angle2 = rot1->vx;
    var_s1  = angle2 - rot0->vx;
    temp_s6 = rot1->vy - rot0->vy;
    angle0  = rot1->vz - rot0->vz;

    temp_a3 = Q12_MULT(var_s1, var_s1);
    temp_a0 = Q12_MULT(angle0, angle0);
    sp5C    = Q12_MULT(temp_s6, temp_s6);

    temp_s2 = SquareRoot12(temp_a3 + temp_a0);

    if (temp_s2 != 0)
    {
        sp64   = Q12_DIV(var_s1, temp_s2);
        var_fp = Q12_DIV(angle0, temp_s2);
    }
    else
    {
        sp64   = var_s4;
        var_fp = var_s5;
    }

    if (mat != NULL)
    {
        angle0 = ratan2(var_s4, var_s5);
        angle2 = ratan2(sp64, var_fp) - angle0;
        angle2 = Q12_ANGLE_NORM_S(angle2);
        absAngle2  = ABS(angle2);

        if (angle1 < absAngle2)
        {
            if (angle2 <= Q12_ANGLE(0.0f))
            {
                angle0 = angle0 - angle1;
            }
            else
            {
                angle0 = angle0 + angle1;
            }

            sp64   = Math_Sin(angle0);
            var_fp = Math_Cos(angle0);
        }
    }

    dist = SquareRoot12(sp5C + temp_a3 + temp_a0);
    if (dist != Q12(0.0f))
    {
        var_s4 = -FP_TO(temp_s6, Q12_SHIFT) / dist; // TODO: `Q12_DIV` doesn't match.
        var_s1 = Q12_DIV(temp_s2, dist);
    }
    else
    {
        var_s4 = sp68;
        var_s1 = sp6C;
    }

    angle1 = angle1 / 2;

    if (mat != NULL)
    {
        angle0  = ratan2(sp68, sp6C);
        angle2 = ratan2(var_s4, var_s1) - angle0;
        angle2 = Q12_ANGLE_NORM_S(angle2);
        absAngle2   = ABS(angle2);

        if (angle1 < absAngle2)
        {
            if (angle2 <= Q12_ANGLE(0.0f))
            {
                angle0 = angle0 - angle1;
            }
            else
            {
                angle0 = angle0 + angle1;
            }

            var_s4 = Math_Sin(angle0);
            var_s1 = Math_Cos(angle0);
        }
    }

    vwGetViewAngle(&sp50);

    sp10.m[0][0] = Q12(1.0f);
    sp10.m[0][1] = 0;
    sp10.m[0][2] = 0;

    sp10.m[1][0] = 0;
    sp10.m[1][1] = Q12(1.0f);
    sp10.m[1][2] = 0;

    sp10.m[2][0] = 0;
    sp10.m[2][1] = 0;
    sp10.m[2][2] = Q12(1.0f);

    Math_RotMatrixZ(0, &sp10);
    MulMatrix(arg0, &sp10);

    sp30.m[0][0] = var_fp;
    sp30.m[0][1] = 0;
    sp30.m[0][2] = sp64;

    sp30.m[1][0] = 0;
    sp30.m[1][1] = Q12(1.0f);
    sp30.m[1][2] = 0;

    sp30.m[2][0] = -sp64;
    sp30.m[2][1] = 0;
    sp30.m[2][2] = var_fp;

    sp10.m[0][0] = Q12(1.0f);
    sp10.m[0][1] = 0;
    sp10.m[0][2] = 0;

    sp10.m[1][0] = 0;
    sp10.m[1][1] = var_s1;
    sp10.m[1][2] = -var_s4;

    sp10.m[2][0] = 0;
    sp10.m[2][1] = var_s4;
    sp10.m[2][2] = var_s1;

    MulMatrix0(&sp30, &sp10, arg0);
}

s32 func_800DBA08(SVECTOR* arg0, s32* arg1, s32* arg2) // 0x800DBA08
{
    s32 sp10;
    s32 sp14;
    s32 temp_s4;
    s32 temp_s0;

    temp_s4 = RotTransPers(arg0, arg1, &sp10, &sp14);

    if (sp14 & (1 << 17))
    {
        return 0;
    }

    arg0++;
    temp_s0 = RotTransPers(arg0, arg2, &sp10, &sp14);

    if (sp14 & (1 << 17))
    {
        return 0;
    }

    return (temp_s4 + temp_s0) / 2;
}

void func_800DBABC(void) // 0x800DBABC
{
    q19_12 val;
    s32    i;

    val = Q12(1.0f);
    for (i = 4; i >= 0; i--)
    {
        D_800F3D98[i] = val;
    }
}

void func_800DBAE8(const VECTOR3* pos, s32 idx) // 0x800DBAE8
{
    s32 temp_s0;

    temp_s0 = D_800EC770[idx].field_6;
    if (temp_s0 < D_800F3D98[idx])
    {
        temp_s0 = D_800EC770[idx].field_4;

        D_800EC770[idx].field_6 = temp_s0 + (Rng_Rand16() / ((SHRT_MAX / (temp_s0 >> 3)) + 1));
        D_800F3D98[idx]         = 0;

        func_8005DC1C(D_800EC770[idx].field_0, pos, D_800EC770[idx].field_2, SfxFlag_None);
    }
}

void func_800DBBA0(void) // 0x800DBBA0
{
    q19_12 deltaTime;
    s32    i;

    deltaTime = g_DeltaTime;
    for (i = 0; i < ARRAY_SIZE(D_800F3D98); i++)
    {
        D_800F3D98[i] += deltaTime;
    }
}

void func_800DBBD8(MATRIX* mat) // 0x800DBBD8
{
    MATRIX        transformMat;
    s_D_800F48A8* base;

    base = &D_800F48A8;

    CompMatrix(&base->mat_8, mat, &transformMat);
    SetRotMatrix(&transformMat);
    SetTransMatrix(&transformMat);
}

void func_800DBC18(q19_12 damageAmount) // 0x800DBC18
{
    s32 i;

    g_SysWork.playerWork.player.attackReceived = 67; // TODO: What weapon attack?

    if (D_800F3DB4 > Q12(0.8f))
    {
        D_800F3DB0 = 1;
        D_800F3DB4 = 0;
    }
    else
    {
        D_800F3DB4 = 0;
        D_800F3DB0++;
    }

    for (i = 1; i < D_800F3DB0; i++)
    {
        damageAmount >>= 1;
    }

    g_SysWork.playerWork.player.damage.amount += damageAmount;
}

bool func_800DBCA4(MATRIX* mat, VECTOR3* outVec) // 0x800DBCA4
{
    s_D_800F48A8* ptr;
    MATRIX        torsoMat;
    q23_8         deltaX;
    q23_8         deltaY;
    q23_8         deltaZ;
    q23_8         sqrX;
    q23_8         sqrY;
    q23_8         sqrZ;

    ptr = &D_800F48A8;

    Vw_CoordHierarchyMatrixCompute(&g_SysWork.playerBoneCoords[HarryBone_Torso], &torsoMat);
    deltaX = torsoMat.t[0] - Q12_TO_Q8(ptr->positionX);
    deltaY = torsoMat.t[1];
    deltaZ = torsoMat.t[2] - Q12_TO_Q8(ptr->positionZ);

    sqrX = Q12_TO_Q8(SQUARE(deltaX - mat->t[0]));
    sqrY = Q12_TO_Q8(SQUARE(deltaY - mat->t[1]));
    sqrZ = Q12_TO_Q8(SQUARE(deltaZ - mat->t[2]));

    if ((sqrX + sqrZ + sqrY) <= Q8(SQUARE(2.398f))) // TODO: Odd number, might be different Q format?
    {
        outVec->vx = Q8_TO_Q12(deltaX) + D_800F48A8.positionX;
        outVec->vy = Q8_TO_Q12(deltaY);
        outVec->vz = Q8_TO_Q12(deltaZ) + D_800F48A8.positionZ;
        return true;
    }

    return false;
}

void func_800DBD94(s_800F3DAC* arg0, GsOT_TAG* ot) // 0x800DBD94
{
    SVECTOR       sp10;
    SVECTOR       sp18;
    VECTOR3       sp20;
    s32           sp30;
    s32           sp34;
    s32           sp38;
    s32           sp3C;
    s32           sp40;
    s32*          sp44;
    q19_12        dist;
    u16           sp4C;
    GsOT_TAG*     temp_a0_3;
    MATRIX*       var_s7;
    q3_12         angle1;
    q19_12        angle0;
    s32           temp_v1;
    s32           var_a2;
    s32           i;
    q19_12        angle2;
    s32           var_s5;
    s32           var_s6;
    s32*          var_s3;
    s32           var_a0;
    POLY_FT4*     poly;
    PACKET*       packet;
    s_D_800F48A8* ptr;

    sp4C = 67;
    dist = Q12_MULT_PRECISE(arg0->rotationZ_4D8, Q12(0.9f));

    if (g_SysWork.npcs[2].model.charaId == Chara_Incubus)
    {
        sp4C = 3;
    }

    sp44   = arg0->field_A0;
    var_s7 = arg0->mat_118;
    var_s3 = arg0->field_28;

    sp38 = 0x80808;
    sp40 = arg0->field_20;

    for (i = 0; i < arg0->field_1C; i++, var_s7++, var_s3++, sp44++);

    angle2 = *sp44;

    sp10.vx = Q12_TO_Q8(Q12_MULT_PRECISE(Math_Sin(angle2), dist));
    sp10.vy = Q12_TO_Q8(Q12_MULT_PRECISE(Math_Cos(angle2), dist));
    angle0 = angle2 + Q12_ANGLE(90.0f);
    sp18.vx = Q12_TO_Q8(Q12_MULT_PRECISE(Math_Sin(angle0), dist));

    var_s3++;
    i++;
    sp44++;

    sp18.vy = Q12_TO_Q8(Q12_MULT_PRECISE(Math_Cos(angle0), dist));
    sp18.vz = Q8(0.0f);
    sp10.vz = Q8(0.0f);

    func_800DBBD8(var_s7++);

    var_a2 = func_800DBA08(&sp10, &sp30, &sp34);

    packet = GsOUT_PACKET_P;
    poly   = packet;
    ptr    = &D_800F48A8;

    for (; i < sp40;
         i++, var_s7++, var_s3++, sp44++)
    {
        var_a0 = angle2;
        angle2 = *sp44;
        sp3C   = var_a2;

        do
        {
            angle1 = Math_AngleNormalizeSigned(angle2 - var_a0);
        }
        while (false); // @hack

        angle0 = angle1;

        if (ABS(angle1) < Q12_ANGLE(90.0f))
        {
            var_s6 = sp30;
            var_s5 = sp34;
        }
        else
        {
            var_s6 = sp34;
            var_s5 = sp30;
        }

        sp10.vx = Q12_TO_Q8(Q12_MULT_PRECISE(Math_Sin(angle2), dist));
        sp10.vy = Q12_TO_Q8(Q12_MULT_PRECISE(Math_Cos(angle2), dist));
        angle0 = angle2 + Q12_ANGLE(90.0f);
        sp18.vx = Q12_TO_Q8(Q12_MULT_PRECISE(Math_Sin(angle0), dist));
        sp18.vy = Q12_TO_Q8(Q12_MULT_PRECISE(Math_Cos(angle0), dist));
        sp18.vz = Q8(0.0f);
        sp10.vz = Q8(0.0f);

        if (arg0->field_4E8 == 0 && func_800DBCA4(var_s7, &sp20) &&
            g_DeltaTime != Q12(0.0f) && ptr->field_44 == 0)
        {
            if (ptr->field_48 != 2)
            {
                if (ptr->field_48 == 0)
                {
                    func_800DBC18(Q12(30.0f));
                    func_800DACFC(&sp20, 0, 0);
                    func_800DBAE8(&g_SysWork.playerWork.player.position, 1);
                }
                else
                {
                    func_800DBC18(Q12(20.0f));
                    func_800DACFC(&sp20, 0, 1);
                }

                func_800DBAE8(&g_SysWork.playerWork.player.position, 3);
            }

            if (i < arg0->field_20)
            {
                sp40 = i;
                if (i < arg0->field_18)
                {
                    sp40 = i + 1;
                }

                arg0->field_18 = sp40;
                arg0->field_20 = sp40;
            }

            arg0->field_4E8 = 1;
        }

        func_800DBBD8(var_s7);

        var_a2 = func_800DBA08(&sp10, &sp30, &sp34);

        if (var_a2 == 0 || sp3C == 0)
        {
            continue;
        }

        if ((u16)var_s6 > 320 && (u32)(var_s6 >> 16) > 224 &&
            (u16)var_s5 > 320 && (u32)(var_s5 >> 16) > 224)
        {
            // @hack Some optimized out code?
            temp_v1 = sp30;
            temp_v1++;
            temp_v1--;
            sp30 = temp_v1;
        }

        if (*var_s3 == 0)
        {
            continue;
        }

        *(s32*)&poly->x0 = var_s6;
        *(s32*)&poly->x1 = var_s5;
        *(s32*)&poly->x2 = sp30;
        *(s32*)&poly->x3 = sp34;

        var_a0  = (i & 1) ? 0 : 0x7F;
        temp_v1 = 0x40;

        setUV4(poly, 0, var_a0, temp_v1, var_a0, 0, var_a0 + 127, temp_v1, var_a0 + 127);

        poly->tpage = 53;
        poly->clut  = sp4C;

        if (g_DeltaTime != Q12(0.0f))
        {
            *var_s3 -= sp38;
        }

        *(s32*)&poly->r0 = *var_s3;

        setPolyFT4(poly);
        setSemiTrans(poly, 1);

        temp_a0_3 = &ot[((sp3C + var_a2) / 2) >> 1];
        addPrim(temp_a0_3, poly);
        poly++;
    }

    packet         = poly;
    GsOUT_PACKET_P = packet;
}

void func_800DC3EC(s_800F3DAC* arg0) // 0x800DC3EC
{
    s32 valMax;
    s32 field20Val;
    s32 field1CVal;

    // TODO: Might be using some kind of `CLAMP` in this func, couldn't get match with our macros though.
    valMax = arg0->field_18;

    field20Val = ((arg0->timer_C - arg0->timer) * 30) / (arg0->timer_C / 2);
    // TODO: `field20Val = MIN(maxVal, field20Val)`?
    if (field20Val >= valMax)
    {
        field20Val = valMax;
    }
    arg0->field_20 = field20Val;

    if (arg0->timer < (arg0->timer_C / 2))
    {
        field1CVal = (((arg0->timer_C / 2) - arg0->timer) * 30) / (arg0->timer_C / 2);
        // TODO: `field1CVal = MIN(maxVal, field1CVal)`?
        if (field1CVal >= valMax)
        {
            field1CVal = valMax;
        }

        field1CVal     = MAX(0, field1CVal);
        arg0->field_1C = field1CVal;
    }
}

void func_800DC49C(s_800F3DAC* arg0) // 0x800DC49C
{
    VECTOR3 pos;
    bool    cond;
    MATRIX* mat;

    cond = D_800F48A8.field_48 != 0;

    if (arg0->field_4F4 == 0)
    {
        if (arg0->field_18 == arg0->field_20)
        {
            mat = &arg0->mat_118[arg0->field_18 - 1];
            Math_Vector3Set(&pos,
                            Q8_TO_Q12(mat->t[0]) + D_800F48A8.positionX,
                            Q8_TO_Q12(mat->t[1]),
                            Q8_TO_Q12(mat->t[2]) + D_800F48A8.positionZ);
            func_800DAC04(&pos, NULL, cond);
            arg0->field_4F4++;
        }
    }
}

void func_800DC544(GsOT_TAG* ot) // 0x800DC544
{
    s32         i;
    s_800F3DAC* ptr;

    ptr = D_800F3DAC;

    for (i = 0; i < 30; i++, ptr++)
    {
        if (ptr->field_0 == 0)
        {
            continue;
        }

        if (ptr->timer > Q12(0.0f) || ptr->field_1C != ptr->field_18)
        {
            func_800DC3EC(ptr);

            if (ptr->field_4F0)
            {
                ptr->field_4F0(ptr);
            }

            func_800DBD94(ptr, ot);
            ptr->timer -= g_DeltaTime;
        }
        else
        {
            ptr->field_0 = 0;
            func_800DD4CC(ptr);
        }
    }

    D_800F3DB4 += g_DeltaTime;

    func_800DBBA0();
}

bool Math_DistanceCheck(const VECTOR3* from, const VECTOR3* to, q19_12 distMax) // 0x800DC650
{
    q19_12 offsetX;
    q19_12 offsetY;
    q19_12 offsetZ;

    // Compute offset.
    offsetX = to->vx - from->vx;
    offsetY = to->vy - from->vy;
    offsetZ = to->vz - from->vz;

    // Compute square offset.
    offsetX = Q12_SQUARE(offsetX);
    offsetY = Q12_SQUARE(offsetY);
    offsetZ = Q12_SQUARE(offsetZ);

    // Check offset distance.
    return distMax < abs(SquareRoot12(offsetX + offsetZ + offsetY));
}

INCLUDE_RODATA("maps/map7_s03/nonmatchings/map7_s03_2", D_800CAE30);

static const SVECTOR D_800CAE3C = { 0, 0, 0x4000 };

bool func_800DC6DC(VECTOR* arg0, VECTOR* arg1, VECTOR3* arg2, s_800F3DAC* arg3) // 0x800DC6DC
{
    VECTOR  sp10;
    SVECTOR sp20;
    SVECTOR sp28;
    MATRIX  sp30;
    q19_12  dx;
    q19_12  dy;
    q19_12  dz;
    s32     dy_2;
    q19_12  randAngle;
    s32     temp_v1;
    q19_12  dist;

    if (arg3->field_10 == 0)
    {
        arg3->field_4E0 = 0;

        switch (arg3->field_4E4)
        {
            case 3:
                arg3->field_10 = 18;
                break;

            case 4:
                arg3->field_10 = 19;
                break;

            case 6:
                arg3->field_10 = 8;
                break;

            case 2:
                arg3->field_10 = 2;
                break;

            case 7:
                arg3->field_10 = 18;
                break;

            default:
                arg3->field_14 = 170;
                arg3->field_10++;
                break;
        }
    }

loop:
    switch (arg3->field_10)
    {
        case 1:
            if (!(Rng_Rand16() & 0xF0))
            {
                arg3->rotationZ_4D8  = Q12(0.2f);
                arg3->field_10  = 2;
                arg3->field_4E0 = 0;
            }
            else if (!(Rng_Rand16() & 0xF0))
            {
                arg3->field_10  = 14;
                arg3->field_4E0 = 0;
            }
            else if (arg0->vy <= Q12(0.5f))
            {
                arg3->field_10  = 8;
                arg3->field_4E0 = 0;
            }
            else if (!(Rng_Rand16() & 0x80))
            {
                arg3->field_10  = 6;
                arg3->field_4E0 = 0;
            }
            break;

        case 2:
            *arg1          = D_800EC798[(Rng_Rand16() >> 4) % 6];
            arg3->field_10 = 3;

        case 3:
            if (Math_DistanceCheck(arg0, arg1, Q12(0.3f)))
            {
                arg3->field_4E0++;
            }
            else
            {
                arg3->field_4E0 = 0;
                arg3->field_10  = 4;
            }
            break;

        case 4:
            arg1->vy = 0;
            arg3->field_10++;

        case 5:
            if (arg0->vy < 0)
            {
                arg3->field_4E0++;
                break;
            }

            arg3->field_4E0 = 0;
            arg3->field_4E4 = 5;
            return false;

        case 6:
            randAngle = Rng_Rand16();
            arg1->vx  = Math_Sin(randAngle);
            arg1->vy  = Q12(0.0f);
            arg1->vz  = Math_Cos(randAngle);
            arg3->field_10++;

        case 7:
            if (arg3->field_4E0 >= 4)
            {
                arg3->field_4E0 = 0;
                arg3->field_4E4 = 0;
                return false;
            }

            arg3->field_4E0++;
            break;

        case 8:
            dx = arg2->vx - arg0->vx;
            dx = FP_SQUARE(dx, Q12_SHIFT);

            dy = arg2->vy - arg0->vy;
            dy = FP_SQUARE(dy, Q12_SHIFT);

            dz = arg2->vz - arg0->vz;
            dz = FP_SQUARE(dz, Q12_SHIFT);

            dist = SquareRoot12(dx + dz + dy);

            dx = arg2->vx - arg0->vx;
            dy = Q12(-3.8f) - (dist / 4);
            dz = arg2->vz - arg0->vz;

            randAngle   = Rng_Rand16();
            arg1->vx  = arg0->vx + (dx / 2) - 0xFFF;
            arg1->vx += randAngle >> 2;

            randAngle   = Rng_Rand16();
            arg1->vy  = dy - 0xFFF;
            arg1->vy += randAngle >> 2;

            randAngle   = Rng_Rand16();
            arg1->vz  = arg0->vz + (dz / 2) - 0xFFF;
            arg1->vz += randAngle >> 2;

            arg3->field_10++;

        case 9:
            if (Math_DistanceCheck(arg0, arg1, arg3->rotationZ_4D8))
            {
                arg3->field_4E0++;
                break;
            }

            arg3->field_10  = 10;
            arg3->field_4E0 = 0;
            break;

        case 10:
            dx   = arg2->vx - arg0->vx;
            dy_2 = arg2->vz - arg0->vz;

            randAngle  = Rng_Rand16();
            temp_v1  = arg2->vx - 0x7FF;
            temp_v1 += randAngle >> 3;
            arg1->vx = temp_v1 - (dx / 8);

            randAngle        = Rng_Rand16();
            arg1->vy       = (randAngle >> 3) - (Q12(4.3f) - 1);
            randAngle        = Rng_Rand16();
            temp_v1        = arg2->vz - 0x7FF;
            temp_v1       += randAngle >> 3;
            arg1->vz       = temp_v1 - (dy_2 / 8);
            arg3->field_10 = 11;

        case 11:
            if (Math_DistanceCheck(arg0, arg1, Q12_MULT_PRECISE(arg3->rotationZ_4D8, Q12(1.5f))))
            {
                arg3->field_4E0++;
                break;
            }

            arg3->field_10  = 12;
            arg3->field_4E0 = 0;
            break;

        case 12:
            randAngle      = Rng_Rand16();
            temp_v1        = arg2->vx;
            temp_v1       += -0x7FF;
            temp_v1       += randAngle >> 3;
            arg1->vx       = temp_v1;
            arg1->vy       = 0;

            randAngle      = Rng_Rand16();
            temp_v1        = arg2->vz;
            temp_v1       += -0x7FF;
            temp_v1       += randAngle >> 3;
            arg1->vz       = temp_v1;
            arg3->field_10 = 11;

        case 13:
            if (!Math_DistanceCheck(arg0, arg1, arg3->rotationZ_4D8))
            {
                arg3->field_4E0 = 0;
                return false;
            }

            arg3->field_4E0++;
            break;

        case 14:
            sp28    = D_800CAE3C;
            sp20.vx = Rng_Rand16();
            sp20.vy = Rng_Rand16();
            sp20.vz = Q12(0.0f);

            Math_RotMatrixXyz(&sp20, &sp30);
            SetRotMatrix(&sp30);
            ApplyRotMatrix(&sp28, &sp10);

            arg1->vx = arg0->vx + sp10.vx;
            arg1->vy = arg0->vy + sp10.vy;
            arg1->vz = arg0->vz + sp10.vz;

        case 15:
            if (arg3->field_4E0 == 0)
            {
                arg3->field_4E0 = 1;
                break;
            }

            if (Rng_Rand16() & 0xF0)
            {
                break;
            }

            arg3->field_4E0 = 0;
            arg3->field_10  = 16;
            break;

        case 16:
            *arg1 = D_800EC798[6];
            arg3->field_10++;

        case 17:
            if (Math_DistanceCheck(arg0, arg1, arg3->rotationZ_4D8))
            {
                arg3->field_4E0++;
                break;
            }

            arg3->field_4E0 = 0;
            arg3->field_4E4 = 0;
            return 0;

        default:
            arg3->field_4E0++;
            break;

        case 18:
            if (!Math_DistanceCheck(arg0, arg1, arg3->rotationZ_4D8 / 2))
            {
                arg3->field_4E0 = 0;
                return false;
            }

            arg3->field_4E0++;
            break;

        case 19:
            if (arg3->field_4E0 >= 25)
            {
                arg3->field_4E0 = 0;
                return false;
            }

            arg3->field_4E0++;
            break;
    }

    if (arg3->field_4E0 == 0)
    {
        goto loop;
    }

    return true;
}

void func_800DCD94(MATRIX* mat, VECTOR3* pos) // 0x800DCD94
{
    mat->t[0] = Q12_TO_Q8(pos->vx - D_800F48A8.positionX);
    mat->t[1] = Q12_TO_Q8(pos->vy);
    mat->t[2] = Q12_TO_Q8(pos->vz - D_800F48A8.positionZ);
}

void func_800DCDDC(s_800F3DAC* arg0, const VECTOR3* arg1, const VECTOR3* arg2) // 0x800DCDDC
{
    VECTOR  sp18;
    VECTOR  sp28;
    SVECTOR sp38;
    VECTOR  sp40;
    s32     cond;
    s32     rand;
    s32     i;
    s32     randSum;
    MATRIX* mat;

    randSum = 0;
    mat     = &arg0->mat_118[0];

    sp18.vx = arg1->vx;
    sp18.vy = arg1->vy;
    sp18.vz = arg1->vz;

    if (arg2 != NULL)
    {
        sp28.vx = arg2->vx;
        sp28.vy = arg2->vy;
        sp28.vz = arg2->vz;
    }

    for (i = 0; i < ARRAY_SIZE(arg0->mat_118); i++, mat++)
    {
        cond = func_800DC6DC(&sp18, &sp28, arg2, arg0);
        if (i == 0)
        {
            func_800DB6D0(mat, &sp18, &sp28, NULL, 0);
        }
        else
        {
            arg0->field_14++; // @hack Needed for reg match.
            arg0->field_14--;
            func_800DB6D0(mat, &sp18, &sp28, mat - 1, arg0->field_14);
        }

        SetRotMatrix(mat);
        func_800DCD94(mat, &sp18);

        sp38.vx = 0;
        sp38.vy = 0;
        sp38.vz = arg0->rotationZ_4D8;
        ApplyRotMatrix(&sp38, &sp40);

        sp18.vx += sp40.vx;
        sp18.vy += sp40.vy;
        sp18.vz += sp40.vz;

        arg0->field_28[i] = 0xC0C0C0;

        rand              = Rng_GenerateInt(-0x400, 0x400 - 1);
        randSum          += rand;
        arg0->field_A0[i] = randSum;

        if (cond == 0)
        {
            break;
        }
    }

    arg0->field_18 = i;
}

void func_800DCF94(void) // 0x800DCF94
{
    s32         i;
    s_800F3DAC* curPtr;

    D_800F3DAC = (s_800F3DAC*)FS_BUFFER_35;
    curPtr     = D_800F3DAC;
    memset(curPtr, 0xA7, sizeof(s_800F3DAC) * 30);

    for (i = 0; i < 30; i++, curPtr++)
    {
        curPtr->field_0 = 0;
    }

    func_800DBABC();
}

void func_800DCFF8(void) // 0x800DCFF8
{
    s32         i;
    s_800F3DAC* curPtr;

    D_800F3DAC = (s_800F3DAC*)FS_BUFFER_30;

    curPtr = D_800F3DAC;
    for (i = 0; i < 30; i++, curPtr++)
    {
        curPtr->field_0 = 0;
    }

    func_800DBABC();
}

void func_800DD044(void) // 0x800DD044
{
    s32         i;
    s_800F3DAC* ptr;

    D_800F3DAC = (s_800F3DAC*)FS_BUFFER_1;
    ptr        = D_800F3DAC;

    for (i = 0; i < 30; i++, ptr++)
    {
        ptr->field_0 = 0;
    }

    func_800DBABC();
}

s_800F3DAC* func_800DD090(void) // 0x800DD090
{
    s32         i;
    s_800F3DAC* ptr;

    ptr = D_800F3DAC;

    for (i = 0; i < 30; i++, ptr++)
    {
        if (ptr->field_0 != 0)
        {
            continue;
        }

        ptr->field_0   = 1;
        ptr->field_4E8 = 0;
        ptr->field_1C  = 0;
        ptr->field_10  = 0;
        ptr->field_4F0 = 0;
        ptr->field_4F4 = 0;
        return ptr;
    }

    return NULL;
}
void func_800DD0EC(const VECTOR3* pos, s32 coordIdx) // 0x800DD0EC
{
    VECTOR        newPos;     // Q19.12
    VECTOR        offset;     // Q19.12
    SVECTOR       rot;        // Q3.12
    SVECTOR       offsetBase; // Q3.12
    MATRIX        rotMat;
    s_800F3DAC*   ptr0;
    s_D_800F48A8* ptr;

    offsetBase = (SVECTOR){ 0, 0, Q12(1.5f) }; // .rodata 0x800CAEAC

    ptr = &D_800F48A8;

    ptr0 = func_800DD090();
    if (ptr0 != NULL)
    {
        // Compute rotation matrix.
        rot.vx = Rng_Rand16();
        rot.vy = Rng_Rand16();
        rot.vz = Q12_ANGLE(0.0f);
        Math_RotMatrixXyz(&rot, &rotMat);

        // Rotate offset.
        SetRotMatrix(&rotMat);
        ApplyRotMatrix(&offsetBase, &offset);

        // Compute new position.
        newPos.vx = pos->vx + offset.vx;
        newPos.vy = pos->vy + offset.vy;
        newPos.vz = pos->vz + offset.vz;

        ptr0->field_4E4    = 3;
        ptr0->rotationZ_4D8     = Q12_ANGLE(108.0f);
        ptr0->timer_C      = Q12(1.0f);
        ptr0->timer      = Q12(1.0f);
        ptr0->coordIdx_4EC = coordIdx;
        ptr0->field_14     = Q12_ANGLE(15.0f);
        func_800DCDDC(ptr0, &newPos, pos);

        if (ptr->field_48 == 0)
        {
            func_800DBAE8(pos, 2);
        }
        else
        {
            func_800DBAE8(pos, 4);
        }
    }
}

void func_800DD240(const VECTOR3* pos) // 0x800DD240
{
    func_800DD0EC(pos, 2);
}

void func_800DD260(const VECTOR3* arg0, const VECTOR3* pos) // 0x800DD260
{
    s_800F3DAC* ptr;

    ptr = func_800DD090();
    if (ptr != NULL)
    {
        ptr->rotationZ_4D8  = Q12_ANGLE(43.2f);
        ptr->field_4E4 = 4;
        ptr->timer_C   = Q12(0.5f);
        ptr->timer   = Q12(0.5f);
        ptr->field_14  = Q12_ANGLE(45.0f);

        func_800DCDDC(ptr, arg0, pos);
    }
}

void func_800DD2C8(const VECTOR3* arg0, const VECTOR3* arg1) // 0x800DD2C8
{
    s_800F3DAC* ptr;

    ptr = func_800DD090();
    if (ptr != NULL)
    {
        ptr->rotationZ_4D8  = Q12_ANGLE(180.0f);
        ptr->field_4E4 = 4;
        ptr->timer_C   = Q12(0.5f);
        ptr->timer   = Q12(0.5f);
        ptr->field_14  = Q12_ANGLE(45.0f);

        func_800DCDDC(ptr, arg0, arg1);
    }
}

void func_800DD32C(const VECTOR3* arg0, const VECTOR3* arg1) // 0x800DD32C
{
    s_800F3DAC*   retPtr;
    s_D_800F48A8* ptr;

    ptr    = &D_800F48A8;
    retPtr = func_800DD090();
    if (retPtr != NULL)
    {
        retPtr->field_4F0 = func_800DC49C;
        retPtr->rotationZ_4D8  = Q12_ANGLE(216.0f);
        retPtr->field_4E4 = 6;
        retPtr->timer_C   = Q12(2.0f);
        retPtr->timer   = Q12(2.0f);
        retPtr->field_14  = Q12_ANGLE(45.0f);

        func_800DCDDC(retPtr, arg0, arg1);

        if (ptr->field_48 == 0)
        {
            func_800DBAE8(arg0, 0);
        }

        func_800DBAE8(arg0, 2);
    }
}

void func_800DD3D4(void* arg0, q19_12 scaleX, q19_12 scaleY, q19_12 scaleZ) // 0x800DD3D4
{
    VECTOR3 pos;
    MATRIX  mat;

    Vw_CoordHierarchyMatrixCompute(&g_SysWork.playerBoneCoords[HarryBone_Torso], &mat);

    pos.vx = Q8_TO_Q12(mat.t[0]) + scaleX;
    pos.vy = Q8_TO_Q12(mat.t[1]) + scaleY;
    pos.vz = Q8_TO_Q12(mat.t[2]) + scaleZ;

    func_800DD32C(arg0, &pos);
}

void func_800DD464(const VECTOR3* arg0) // 0x800DD464
{
    s_800F3DAC* ptr;

    ptr = func_800DD090();
    if (ptr != NULL)
    {
        ptr->field_4F0 = func_800DC49C;
        ptr->rotationZ_4D8  = Q12_ANGLE(90.0f);
        ptr->field_4E4 = 2;
        ptr->timer_C   = Q12(1.5f);
        ptr->timer   = Q12(1.5f);
        ptr->field_14  = Q12_ANGLE(20.0f);

        func_800DCDDC(ptr, arg0, arg0);
    }
}

void func_800DD4CC(s_800F3DAC* arg0) // 0x800DD4CC
{
    VECTOR3 newPos;  // Q19.12
    VECTOR3 prevPos; // Q19.12
    MATRIX  mat;
    s32     temp_v1;

    if (arg0->field_4E4 == 3)
    {
        temp_v1 = arg0->field_18 - 1;
        newPos.vx = Q8_TO_Q12(arg0->mat_118[temp_v1].t[0]) + D_800F48A8.positionX;
        newPos.vy = Q8_TO_Q12(arg0->mat_118[temp_v1].t[1]);
        newPos.vz = Q8_TO_Q12(arg0->mat_118[temp_v1].t[2]) + D_800F48A8.positionZ;

        Vw_CoordHierarchyMatrixCompute(&D_800F48A8.coords_2C[arg0->coordIdx_4EC], &mat);
        prevPos.vx = Q8_TO_Q12(mat.t[0]);
        prevPos.vy = Q8_TO_Q12(mat.t[1]);
        prevPos.vz = Q8_TO_Q12(mat.t[2]);

        func_800DD260(&newPos, &prevPos);
    }
}

void func_800DD594(const VECTOR3* pos, s_SubCharacter* chara, GsCOORDINATE2* boneCoords, s32 arg3) // 0x800DD594
{
    q19_12        newPosX;
    q19_12        newPosZ;
    s_D_800F48A8* ptr;

    ptr = &D_800F48A8;

    newPosX = pos->vx;
    if (newPosX < Q12(0.0f))
    {
        newPosX += Q12(64.0f) - 1;
    }
    newPosX = (newPosX >> 18) << 18;

    newPosZ = pos->vz;
    if (newPosZ < Q12(0.0f))
    {
        newPosZ += Q12(64.0f) - 1;
    }

    ptr->positionX = newPosX;
    ptr->positionZ = (newPosZ >> 18) << 18;
    ptr->field_28 = chara;
    ptr->coords_2C = boneCoords;
    ptr->playerPosition_30 = g_SysWork.playerWork.player.position;
    ptr->field_44 = 0;
    ptr->field_48 = arg3;

    func_800DCF94();
}

void func_800DD62C(const VECTOR3* pos, s_SubCharacter* chara, GsCOORDINATE2* boneCoords) // 0x800DD62C
{
    func_800D952C();
    func_800DD594(pos, chara, boneCoords, 0);
}

void func_800DD67C(const VECTOR3* pos, s_SubCharacter* chara, GsCOORDINATE2* boneCoords) // 0x800DD67C
{
    func_800D952C();
    func_800DD594(pos, chara, boneCoords, 1);
}

void func_800DD6CC(void) // 0x800DD6CC
{
    q19_12    posX;
    q19_12    posZ;
    s32       activeBufferIdx;
    GsOT_TAG* ot;

    posX            = D_800F48A8.positionX;
    posZ            = D_800F48A8.positionZ;
    activeBufferIdx = g_ActiveBufferIdx;
    ot              = g_OrderingTable0[activeBufferIdx].org;

    Vw_WorldScreenMatrixAtPositionGet(&D_800F48A8.mat_8, posX, Q12(0.0f), posZ);
    func_800DC544(ot);
    func_800D917C();
}

void func_800DD738(const VECTOR3* pos0, const VECTOR3* pos1, q19_12 rotZ, q19_12 timer) // 0x800DD738
{
    s_800F3DAC* ptr;

    ptr = func_800DD090();
    if (ptr != NULL)
    {
        ptr->field_4E4 = 7;
        ptr->rotationZ_4D8  = rotZ;
        ptr->timer_C   = timer;
        ptr->timer   = timer;
        ptr->field_14  = Q12_ANGLE(45.0f);

        func_800DCDDC(ptr, pos0, pos1);

        if (rotZ > Q12_ANGLE(108.0f))
        {
            func_800DBAE8(pos0, 0);
        }
        else
        {
            func_800DBAE8(pos0, 4);
        }
    }
}

void func_800DD7D0(VECTOR3* charaPos) // 0x800DD7D0
{
    s32           gridX;
    s32           gridZ;
    s_D_800F48A8* ptr;

    ptr = &D_800F48A8;

    // TODO: Possibly an inline/macro, based on needing separate `s_D_800F48A8*`
    gridX            = (charaPos->vx / Q12(64.0f)) * Q12(64.0f);
    gridZ            = (charaPos->vz / Q12(64.0f)) * Q12(64.0f);
    ptr->positionX = gridX;
    ptr->positionZ = gridZ;

    ptr->playerPosition_30 = g_SysWork.playerWork.player.position;
    ptr->field_44          = 1;
    ptr->field_48          = 2;

    func_800DCFF8();
}

void func_800DD868(void) // 0x800DD868
{
    q19_12    posX;
    q19_12    posZ;
    s32       activeBufferIdx;
    GsOT_TAG* ot;

    posX            = D_800F48A8.positionX;
    posZ            = D_800F48A8.positionZ;
    activeBufferIdx = g_ActiveBufferIdx;
    ot              = g_OrderingTable0[activeBufferIdx].org;

    Vw_WorldScreenMatrixAtPositionGet(&D_800F48A8.mat_8, posX, Q12(0.0f), posZ);
    func_800DC544(ot);
}

void func_800DD8CC(VECTOR3* charaPos) // 0x800DD8CC
{
    s32           gridX;
    s32           gridZ;
    s_D_800F48A8* ptr;

    ptr = &D_800F48A8;

    // TODO: Possibly an inline/macro, based on needing separate `s_D_800F48A8*`
    gridX            = (charaPos->vx / Q12(64.0f)) * Q12(64.0f);
    gridZ            = (charaPos->vz / Q12(64.0f)) * Q12(64.0f);
    ptr->positionX = gridX;
    ptr->positionZ = gridZ;

    ptr->playerPosition_30 = g_SysWork.playerWork.player.position;
    ptr->field_44          = 1;
    ptr->field_48          = 2;

    func_800DD044();
}
