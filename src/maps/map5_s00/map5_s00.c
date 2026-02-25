
#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map5/map5_s00.h"
#include "maps/particle.h"
#include "maps/characters/creeper.h"
#include "maps/characters/player.h"
#include "maps/characters/hanged_scratcher.h"

void func_800CB0D8(void) // 0x800CB0D8
{
    s32 idx;
    s32 i;

    idx = func_8005E7E0(32);
    if (idx == NO_VALUE)
    {
        return;
    }

    sharedData_800DFB7C_0_s00[idx].field_B = 0;
    sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 = Rng_GenerateInt(0, 2);

    for (i = 0; i < 12; i++)
    {
        idx = func_8005E7E0(32);
        if (idx == NO_VALUE)
        {
            break;
        }

        sharedData_800DFB7C_0_s00[idx].field_B = 1;
        sharedData_800DFB7C_0_s00[idx].field_0.vx_0 = Rng_GenerateInt(Q12(-92.75f), Q12(-91.25f) - 1);
        sharedData_800DFB7C_0_s00[idx].vy_8 = Q12(0.5f);
        sharedData_800DFB7C_0_s00[idx].field_4.vz_4 = Rng_GenerateInt(Q12(7.35f), Q12(8.85f) - 1);
        sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0 = Rng_GenerateUInt(0, Q12_CLAMPED(1.0f));
        sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 = Rng_GenerateInt(0, 2);
    }
}

bool func_800CB25C(POLY_FT4** poly, s32 idx) // 0x800CB25C
{
    typedef struct
    {
        s_func_8005E89C field_0;
        SVECTOR         field_12C[3];
        DVECTOR         field_144;
        VECTOR3         field_148;
        s32             field_154;
        s32             field_158;
        s32             field_15C;
        s32             field_160;
    } s_func_800CB25C;

    DVECTOR          sp10[5][5];
    s32              sp78[5][5];
    s32              j;
    s32              i;
    s32              var_v0_4;
    s_func_800CB25C* ptr;

    ptr = PSX_SCRATCH;

    if (g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(-80.0f))
    {
        return false;
    }

    if (g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(0.0f))
    {
        return false;
    }

    if (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1))
    {
        if (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0))
        {
            return false;
        }
    }

    if (sharedData_800DFB7C_0_s00[idx].field_B != 0)
    {
        sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0 += Rng_GenerateUInt(-0x20, 0x20 - 1);
        sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0  = CLAMP_MIN_THEN_LOW(sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0, 0, 0xFFF);

        ptr->field_15C = Q12_MULT_PRECISE(sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0, Q12(1.5f));

        setPolyFT4(*poly);

        Math_SetSVectorFastSum(&ptr->field_12C[0], ((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 - ptr->field_15C) >> 4) - (u16)ptr->field_0.field_0.vx,
                               ((sharedData_800DFB7C_0_s00[idx].vy_8) >> 4) - ptr->field_0.field_0.vy,
                               ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 + ptr->field_15C) >> 4) - ptr->field_0.field_0.vz);

        Math_SetSVectorFastSum(&ptr->field_12C[1], ((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 + ptr->field_15C) >> 4) - (u16)ptr->field_0.field_0.vx,
                               ((sharedData_800DFB7C_0_s00[idx].vy_8) >> 4) - ptr->field_0.field_0.vy,
                               ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 + ptr->field_15C) >> 4) - ptr->field_0.field_0.vz);

        Math_SetSVectorFastSum(&ptr->field_12C[2], ((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 - ptr->field_15C) >> 4) - (u16)ptr->field_0.field_0.vx,
                               ((sharedData_800DFB7C_0_s00[idx].vy_8) >> 4) - ptr->field_0.field_0.vy,
                               ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 - ptr->field_15C) >> 4) - ptr->field_0.field_0.vz);

        gte_ldv3c(&ptr->field_12C);
        gte_rtpt();
        gte_stsxy3_g3(*poly);
        gte_stsz3c(&ptr->field_148);

        Math_SetSVectorFastSum(&ptr->field_12C[0], ((sharedData_800DFB7C_0_s00[idx].field_0.vx_0 + ptr->field_15C) >> 4) - (u16)ptr->field_0.field_0.vx,
                               ((sharedData_800DFB7C_0_s00[idx].vy_8) >> 4) - ptr->field_0.field_0.vy,
                               ((sharedData_800DFB7C_0_s00[idx].field_4.vz_4 - ptr->field_15C) >> 4) - ptr->field_0.field_0.vz);

        gte_ldv0(&ptr->field_12C);
        gte_rtps();
        gte_stsxy(&ptr->field_144);
        gte_stsz(&ptr->field_154);

        ptr->field_148.vx = (ptr->field_148.vx + ptr->field_148.vy + ptr->field_148.vz + ptr->field_154) >> 2;

        if (ptr->field_148.vx <= 0 || (ptr->field_148.vx >> 3) >= ORDERING_TABLE_SIZE)
        {
            return false;
        }

        if (ABS(ptr->field_144.vx) > 200 || ABS(ptr->field_144.vy) > 160)
        {
            return false;
        }

        *(s32*)&(*poly)->x3 = *(s32*)&ptr->field_144;
        setSemiTrans(*poly, 1);

        if (CLAMP_LOW(Q12_MULT_PRECISE(0x1000 - sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0, 0x20), 0) < 0x10)
        {
            var_v0_4 = MAX(Q12_MULT_PRECISE(0x1000 - sharedData_800DFB7C_0_s00[idx].field_C.s_2.field_0, 0x20), 0);
        }
        else
        {
            var_v0_4 = 0x10;
        }

        ptr->field_160 = var_v0_4;

        setUV0AndClutSum(*poly, 224, 160 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5), 0x13);
        setUV1AndTPageSum(*poly, 255, 160 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5), 0x4B);
        setUV2Sum(*poly, 224, 191 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5));
        setUV3Sum(*poly, 255, 191 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5));

        setRGB0Fast(*poly, ptr->field_160, ptr->field_160, ptr->field_160);

        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[(ptr->field_148.vx + 0x80) >> 3], *poly);
        *poly += 1;
    }
    else
    {
        for (i = 0; i < 25; i += 3)
        {
            for (j = 0; j < 3; j++)
            {
                Math_SetSVectorFastSum(&ptr->field_12C[j], ((((((i + j) % 5) * Q12(1.5f)) >> 1) - Q12(93.5f)) >> 4) - (u16)ptr->field_0.field_0.vx,
                                       0x80 - ptr->field_0.field_0.vy,
                                       ((0x9999 - ((i + j) / 5 * Q12(1.5f) >> 1)) >> 4) - ptr->field_0.field_0.vz);
            }

            gte_ldv3c(&ptr->field_12C[0]);
            gte_rtpt();
            gte_stsxy3c(&sp10[i / 5][i % 5]);
            gte_stsz3c(&sp78[i / 5][i % 5]);
        }

        Math_SetSVectorFastSum(&ptr->field_12C[0], -0x5A80 - (u16)ptr->field_0.field_0.vx,
                               0x80 - ptr->field_0.field_0.vy,
                               0x699 - ptr->field_0.field_0.vz);

        gte_ldv0(&ptr->field_12C);
        gte_rtps();
        gte_stsxy(&sp10[4][4]);
        gte_stsz(&sp78[4][4]);

        ptr->field_160 = !(func_80055D78(Q12(-92.0f), Q12(0.5f), Q12(8.1f)) < 129) * 8;

        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                if (sp78[i][j] <= 0 || (sp78[i][j] >> 3) >= ORDERING_TABLE_SIZE)
                {
                    continue;
                }

                if (ABS(sp10[i][j].vx) > 200 || ABS(sp10[i][j].vy) > 160)
                {
                    continue;
                }

                setPolyFT4(*poly);

                setXY4(*poly,
                       sp10[i][j].vx, sp10[i][j].vy,
                       sp10[i][j + 1].vx, sp10[i][j + 1].vy,
                       sp10[i + 1][j].vx, sp10[i + 1][j].vy,
                       sp10[i + 1][j + 1].vx, sp10[i + 1][j + 1].vy);

                setSemiTrans(*poly, 1);

                *(u16*)&(*poly)->r0 = ptr->field_160;
                (*poly)->b0         = 0;

                setUV0AndClutSum(*poly, 224 + (j * 8), (i * 8) + 160 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5), 0x0293);
                setUV1AndTPageSum(*poly, 231 + (j * 8), (i * 8) + 160 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5), 0x2B);
                setUV2Sum(*poly, 224 + (j * 8), (i * 8) + 160 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5) + 7);
                setUV3Sum(*poly, 231 + (j * 8), (i * 8) + 160 + (sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 5) + 7);

                ptr->field_158 = (sp78[i][j] + sp78[i + 1][j] + sp78[i][j + 1] + sp78[i + 1][j + 1]) >> 2;

                addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[(ptr->field_158 + 0x80) >> 3], *poly);
                *poly += 1;
            }
        }
    }

    return true;
}

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

// TODO: Move this line into separate `Chara_HangedScratcher` split.
#include "../src/maps/characters/hanged_scratcher.c" // 0x800CFC24

// TODO: Move this line into separate `Chara_Creeper` split.
#include "../src/maps/characters/creeper.c" // 0x800D387C

void func_800D5B00(void) // 0x800D5B00
{
    q19_12               angle;
    q19_12               cosAngle;
    q19_12               randAngle;
    q19_12               sinAngle;
    q19_12               temp_lo;
    s32                  i;
    s_func_800D5B00_D94* ptr;
    s_func_800D5B00*     base;

    base = (s_func_800D5B00*)FS_BUFFER_1;
    ptr  = base->field_D94;

    for (i = 0; i < 200; i++, ptr++)
    {
        ptr->field_34   = Rng_GenerateInt(0, 4914);
        ptr->field_0.vx = 0;
        ptr->field_0.vy = 0;
        ptr->field_0.vz = 0;
        ptr->field_30   = 255;

        angle = Rng_Rand16();

        if (Math_Sin(angle) < Q12(0.0f))
        {
            sinAngle = Math_Sin(angle);
        }
        else
        {
            sinAngle = -Math_Sin(angle);
        }

        cosAngle   = Math_Cos(angle);
        randAngle = Rng_Rand16();

        angle = Q12_MULT(Math_Sin(randAngle), cosAngle);
        temp_lo = Q12_MULT(Math_Cos(randAngle), cosAngle);

        ptr->field_20.vx = Q12_MULT_PRECISE(angle, Q12(1.8f));
        ptr->field_20.vy = Q12_MULT_PRECISE(sinAngle, Q12(4.4f));
        ptr->field_20.vz = Q12_MULT_PRECISE(temp_lo, Q12(1.8f));
    }
}

void func_800D5CC4(s32 x, s32 y, s32 val) // 0x800D5CC4
{
    s32              offsetX;
    s32              offsetY;
    s16              row;
    s16              col;
    s_func_800D5B00* ptr;
    u8*              buf;

    ptr = FS_BUFFER_1;

    offsetX = ptr->field_D84 & 0xFFFF;
    offsetY = ptr->field_D84 >> 16;

    col = (x + 41) - offsetX;
    row = (y + 81) - offsetY;

    col += (col > 0) ? 1 : -1;
    col /= 2;

    row += (row > 0) ? 1 : -1;
    row /= 2;

    if (col > 0 && col < 41 && row > 0 && row < 81)
    {
        buf  = ptr->field_5D + (col + (41 * row));
        *buf = val;
    }
}

void func_800D5D90(void) // 0x800D5D90
{
    SVECTOR              sp10;
    DVECTOR              sp18[2];
    s32                  sp20;
    s32                  i;
    s_func_800D5B00_D94* ptr;
    s_func_800D5B00*     base;

    base = (s_func_800D5B00*)FS_BUFFER_1;
    ptr  = base->field_D94;

    for (i = 0; i < 200; i++, ptr++)
    {
        if (ptr->field_34 < 0)
        {
            sp10.vx = Q12_TO_Q4(ptr->field_0.vx);
            sp10.vy = Q12_TO_Q4(ptr->field_0.vy);
            sp10.vz = Q12_TO_Q4(ptr->field_0.vz);

            RotTransPers(&sp10, &sp18[0], &sp18[1], &sp20);
            func_800D5CC4(sp18[0].vx, sp18[0].vy, ptr->field_30);

            ptr->field_0.vx += ptr->field_20.vx;
            ptr->field_0.vy  = (ptr->field_0.vy + ptr->field_20.vy) + Q12(1.2f);
            ptr->field_0.vz += ptr->field_20.vz;
            ptr->field_30    = ptr->field_30 - 20;
            ptr->field_30    = MAX(ptr->field_30, 0);
        }
        else
        {
            ptr->field_34 -= g_DeltaTime;
        }
    }
}

s32 func_800D5EA8(s32 arg0, s32 arg1) // 0x800D5EA8
{
    s_func_800D5B00* buf;

    buf = (s_func_800D5B00*)FS_BUFFER_1;

    return D_800DA154[buf->field_5D[(arg1 * 41) + arg0]];
}

void func_800D5EE8(void) // 0x800D5EE8
{
    // TODO: Messy decl order matters.
    u32              sp18;
    s_func_800D5B00* ptr;
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

    ptr = 0x801E2600;

    packet = GsOUT_PACKET_P;
    poly   = packet;

    x = (ptr->field_D84 & 0xFFFF) - 41;
    y = ((u32)ptr->field_D84 >> 16) - 81;

    idx = g_ActiveBufferIdx;
    ot    = g_OrderingTable0[idx].org;
    ot    = &ot[ptr->field_D88 >> 1];

    col  = 0x3A000000;
    code = 0x3A;

    for (i = 1; i < 81; i++)
    {
        col1 = func_800D5EA8(0, i - 1);
        col3 = func_800D5EA8(0, i);

        for (j = 1; j < 41; j++)
        {
            sp18 = ptr->field_5D[(i * 41) + j];

            col0 = col1;
            col2 = col3;
            col1 = func_800D5EA8(j, i - 1);

            col3 = func_800D5EA8(j, i);

            if (col  == col0 &&
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

    SetDrawMode(mode, 0, 1, 0x2A, NULL);
    addPrim(ot, mode);
    packet         = mode + 1;
    GsOUT_PACKET_P = packet;
}

void func_800D61D4(void) // 0x800D61D4
{
    s32              i;
    s32              j;
    s32              val;
    s_func_800D5B00* buf;
    u8*              tab;

    buf = FS_BUFFER_1;

    for (i = 0; i < 81; i++)
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
            val  -= 3;

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

void func_800D62C8(void)
{
    s_func_800D5B00* buf = FS_BUFFER_1;

    memset(buf->field_34, 0, sizeof(buf->field_34));
    memset(buf->field_5D, 0, sizeof(buf->field_5D));
    memset(buf->field_D56, 0, sizeof(buf->field_D56));
}

void func_800D631C(VECTOR* arg0, q19_12 rotY) // 0x800D631C
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

s32 func_800D63DC(s32* screenXy) // 0x800D63DC
{
    SVECTOR vec;
    s32     p;

    vec.vx = 0;
    vec.vy = 0;
    vec.vz = 0;
    return RotTransPers(&vec, screenXy, &p, &p);
}

void func_800D6414(void) // 0x800D6414
{
    s_func_800D5B00* buf = FS_BUFFER_1;

    if (buf->field_D90 > 0)
    {
        buf->field_D90 -= g_DeltaTime;
        return;
    }

    func_800D631C(&buf->field_4, buf->field_D8C);
    buf->field_D88 = func_800D63DC(&buf->field_D84);

    func_800D5D90();
    func_800D61D4();
    func_800D5EE8();
}

void func_800D6490(VECTOR3* arg0) // 0x800D6490
{
    s_func_800D5B00* buf = FS_BUFFER_1;

    buf->field_D8C  = 0;
    buf->field_D90  = 9830;
    buf->field_4.vx = Q12_TO_Q8(arg0->vx);
    buf->field_4.vy = Q12_TO_Q8(arg0->vy);
    buf->field_4.vz = Q12_TO_Q8(arg0->vz);

    func_800D62C8();
    func_800D5B00();
}

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D64F8

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D6508);

void func_800D6790(void) // 0x800D6790
{
    u32 flags = D_800DA578[g_SavegamePtr->mapRoomIdx_A5];

    if (Savegame_EventFlagGet(EventFlag_354))
    {
        flags |= (1 << 5) | (1 << 3) | (1 << 1);
    }

    Bgm_Update(flags, Q12(0.25f), &D_800DA570);
}

void func_800D67EC(void) {}

void func_800D67F4(void) // 0x800D67F4
{
    VECTOR3 pos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Map_MessageWithSfx(MapMsgIdx_DoorJammed, Sfx_Unk1576, &pos);
}

void func_800D6888(void) // 0x800D6888
{
    VECTOR3 pos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Map_MessageWithSfx(MapMsgIdx_DoorLocked, Sfx_Unk1576, &pos);
}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tUsed_the_ ~C2 Sewer_key ~C7 . ~E ",
    "\tUsed_the_ ~C2 Sewer_exit_key ~C7 . ~E ",
    "\tThere_is_a_ ~C2 Sewer_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Sewer_exit_key ~C7 ~N\n\tin_the_water._Take_it? ~S4 ",
    "\tGot_to_find_Cheryl. ~N\n\tNo_time_to_go_back. ~E ",
    "~H\tThere_is_a_ ~C5 Sewer_map ~N\n\t(connecting_to_resort_area) ~C7 . ~N\n\tTake_it? ~S4 "
};

void MapEvent_CommonItemTake(void) // 0x800D691C
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 38:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M5S00_ShotgunShells;
            break;

        case 39:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M5S00_HealthDrink0;
            break;

        case 40:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M5S00_HandgunBullets0;
            break;

        case 41:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M5S00_RifleShells;
            break;

        case 42:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M5S00_FirstAidKit0;
            break;

        case 43:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M5S00_FirstAidKit1;
            break;

        case 44:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M5S00_HealthDrink1;
            break;

        case 45:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M5S00_HandgunBullets1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800D69DC(void) // 0x800D69DC
{
    VECTOR3 pos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 10:
            Player_ItemRemove(InventoryItemId_SewerKey, 1);
            Map_MessageWithSfx(15, Sfx_UseKey, &pos);
            break;

        case 14:
            Player_ItemRemove(InventoryItemId_SewerExitKey, 1);
            Map_MessageWithSfx(16, Sfx_UseKey, &pos);
            break;

        default:
            Map_MessageWithSfx(MapMsgIdx_DoorUnlocked, Sfx_DoorUnlocked, &pos);
            break;
    }
}

void MapEvent_SewerKeyTake(void) // 0x800D6AD4
{
    Event_ItemTake(InventoryItemId_SewerKey, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M5S00_PickupSewerKey, 17);
}

void func_800D6B00(void) // 0x800D6B00
{
    VECTOR3 vec;
    s32     i;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            D_800DAB78 = Q12(-0.5f);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        case 5:
            g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;
            func_800862F8(7, FILE_TIM_DRAINKEY_TIM, false);
            break;

        case 6:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrement(0);

        case 8:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(1, false, 0, Q12(0.0f), false);
            break;

        case 9:
            func_800862F8(2, 0, false);
            g_SysWork.silentYesSelection_2350_4 = true;
            MapMsg_DisplayAndHandleSelection(true, 18, 10, 11, 0, false);
            break;

        case 10:
            Savegame_EventFlagSet(EventFlag_354);

            func_80086470(3u, InventoryItemId_SewerExitKey, 1, false);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(-92.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(7.7f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(0.0f);

            for (i = 0; i < ARRAY_SIZE(D_800DAB7C); i++)
            {
                D_800DAB7C[i] = Chara_Spawn(Chara_HangedScratcher, i, Q12(-93.3f), Q12(7.1f), Q12_ANGLE(180.0f), 18 + i);
            }

            if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
            {
                Chara_Spawn(Chara_HangedScratcher, 14, Q12(-94.3f), Q12(-5.5f), Q12_ANGLE(0.0f), 7U);
            }

            g_SysWork.field_30 = 20;

            Sd_PlaySfx(Sfx_Unk1575, 0, Q8_CLAMPED(0.5f));
            SysWork_StateStepIncrement(0);

        case 11:
            func_80086F44(0, 0);
            break;

        case 12:
            func_8008605C(EventFlag_354, 13, 16, false);
            break;

        case 13:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(-88.04f), Q12(-1.29f), Q12(6.26f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-91.77f), Q12(-0.89f), Q12(7.63f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            g_SysWork.pointLightIntensity_2378 = Q12(2.0f);

            SysWork_StateStepIncrement(0);

            vec = QVECTOR3(-91.3f, 0.3f, 8.5f);
            func_800D6490(&vec);

        case 14:
            if (D_800DAB78 < Q12(1.5f) && (D_800DAB78 + g_DeltaTime) > Q12(1.5f))
            {
                func_80085EB8(0u, &g_SysWork.playerWork_4C.player_0, 114, false);
            }

            D_800DAB78 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, 0.6f, 12);

            if (D_800DAB78 > Q12(3.55f))
            {
                SysWork_StateStepIncrement(0);
            }
            else if (D_800DAB78 > Q12(2.5f))
            {
                g_SysWork.npcs_1A0[D_800DAB7C[2]].properties_E4.dummy.properties_E8[0].val8[0] |= (1 << 7);
            }
            else if (D_800DAB78 > Q12(1.25f))
            {
                g_SysWork.npcs_1A0[D_800DAB7C[1]].properties_E4.dummy.properties_E8[0].val8[0] |= (1 << 7);
            }
            else if (D_800DAB78 > Q12(-0.1f))
            {
                g_SysWork.npcs_1A0[D_800DAB7C[0]].properties_E4.dummy.properties_E8[0].val8[0] |= (1 << 7);
            }

            func_800D6414();
            break;

        case 15:
            vcReturnPreAutoCamWork(true);
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            g_SysWork.npcs_1A0[D_800DAB7C[0]].model_0.controlState_2     = ModelState_Uninitialized;
            g_SysWork.npcs_1A0[D_800DAB7C[0]].model_0.stateStep_3 = 17;
            g_SysWork.npcs_1A0[D_800DAB7C[0]].position_18.vx     += Q12(-0.1878f);
            g_SysWork.npcs_1A0[D_800DAB7C[0]].position_18.vz     += Q12(0.245f);
            g_SysWork.npcs_1A0[D_800DAB7C[0]].rotation_24.vy      = Q12_ANGLE(112.5f);

            g_SysWork.npcs_1A0[D_800DAB7C[1]].model_0.controlState_2     = ModelState_Uninitialized;
            g_SysWork.npcs_1A0[D_800DAB7C[1]].model_0.stateStep_3 = 17;
            g_SysWork.npcs_1A0[D_800DAB7C[1]].position_18.vx     += Q12(1.8128f);
            g_SysWork.npcs_1A0[D_800DAB7C[1]].position_18.vz     += Q12(0.799f);
            g_SysWork.npcs_1A0[D_800DAB7C[1]].rotation_24.vy      = Q12_ANGLE(180.0f);

            g_SysWork.npcs_1A0[D_800DAB7C[2]].model_0.controlState_2     = ModelState_Uninitialized;
            g_SysWork.npcs_1A0[D_800DAB7C[2]].model_0.stateStep_3 = 17;
            g_SysWork.npcs_1A0[D_800DAB7C[2]].position_18.vx     += Q12(0.6531f);
            g_SysWork.npcs_1A0[D_800DAB7C[2]].position_18.vz     += Q12(-1.2493f);
            g_SysWork.npcs_1A0[D_800DAB7C[2]].rotation_24.vy      = Q12_ANGLE(0.0f);

            g_SysWork.playerWork_4C.player_0.position_18.vz += Q12(-1.2f);

            // Return to gameplay.
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            break;

        case 16:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D732C(void) // 0x800D732C
{
    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 3)
    {
        ScreenFade_ResetTimestep();
        SysWork_StateStepReset();
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            // Warp player.
            Player_ControlFreeze();
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(56.789f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(-2.02f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(60.02f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(-90.0f);
            Game_TurnFlashlightOn();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(58.49f), Q12(1.18f), Q12(59.07f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(56.67f), Q12(-2.3f), Q12(59.86f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0u, &g_SysWork.playerWork_4C.player_0, 88, false);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            // Move player.
            g_SysWork.playerWork_4C.player_0.position_18.vy += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.4f);

            SysWork_StateStepIncrementDelayed(Q12(3.8f), false);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);

            // Move player.
            g_SysWork.playerWork_4C.player_0.position_18.vy += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.4f);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(16.7f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(0.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(52.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(90.0f);

            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_355);
            func_8003A16C();
            break;
    }
}

void func_800D75FC(void) // 0x800D75FC
{
    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 6)
    {
        ScreenFade_ResetTimestep();
        SysWork_StateStepReset();
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            if (g_SysWork.sysStateStep_C[0] == 2)
            {
                g_SysWork.field_28 += g_DeltaTimeRaw;
                if (g_SysWork.field_28 > Q12(1.0f))
                {
                    SysWork_StateStepSet(0, 3);
                }
            }
            break;

        case 3:
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(56.773f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(-1.444f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(60.036f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(-90.0f);
            Game_TurnFlashlightOn();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(57.29f), Q12(-0.86f), Q12(59.36f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(55.07f), Q12(-4.0f), Q12(60.29f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 87, false);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, -0.4f, 12);
            SysWork_StateStepIncrementDelayed(Q12(3.8f), false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, -0.4f, 12);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_356);
            Savegame_EventFlagClear(EventFlag_357);
            break;
    }
}

void func_800D7940(void) // 0x800D7940
{
    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 6)
    {
        ScreenFade_ResetTimestep();
        SysWork_StateStepReset();
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);

            if (g_SysWork.sysStateStep_C[0] == 2)
            {
                g_SysWork.field_28 += g_DeltaTimeRaw;
                if (g_SysWork.field_28 > Q12(1.0f))
                {
                    SysWork_StateStepSet(0, 3);
                }
            }
            break;

        case 3:
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(56.769f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(-2.07f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(60.012f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(-90.0f);
            Game_TurnFlashlightOn();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(57.09f), Q12(-5.76f), Q12(60.59f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(55.96f), Q12(-2.01f), Q12(59.78f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 88, false);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, 0.4f, 12);
            SysWork_StateStepIncrementDelayed(Q12(3.8f), false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, 0.4f, 12);
            break;

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_357);
            Savegame_EventFlagClear(EventFlag_356);
            break;
    }
}

void func_800D7C84(void) // 0x800D7C84
{
    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 6)
    {
        ScreenFade_ResetTimestep();
        SysWork_StateStepReset();
    }

    g_SysWork.sysFlags_22A0 |= SysFlag_1;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        case 3:
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(-22.234f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(-1.734f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(60.508f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(-90.0f);
            Game_TurnFlashlightOn();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-20.39f), Q12(-3.84f), Q12(63.99f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-22.56f), Q12(-2.83f), Q12(60.78f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 87, false);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, -0.4f, 12);
            SysWork_StateStepIncrementDelayed(Q12(3.8f), false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, -0.4f, 12);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_358);
            Savegame_EventFlagClear(EventFlag_359);
            break;
    }
}

void func_800D7F88(void) // 0x800D7F88
{
    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 6)
    {
        ScreenFade_ResetTimestep();
        SysWork_StateStepReset();
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            ScreenFade_ResetTimestep();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        case 3:
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(-22.245f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(-2.439f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(60.488f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(-90.0f);
            Game_TurnFlashlightOn();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-21.29f), Q12(-0.04f), Q12(62.13f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-22.91f), Q12(-3.23f), Q12(60.34f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 88, false);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, 0.37f, 12);
            SysWork_StateStepIncrementDelayed(Q12(3.8f), false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, 0.4f, 12);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagClear(EventFlag_360);
            Savegame_EventFlagClear(EventFlag_358);
            Savegame_EventFlagSet(EventFlag_359);
            break;
    }
}

void MapEvent_MapTake(void) // 0x800D8280
{
    Event_MapTake(13, EventFlag_M5S00_PickupMap, 20);
}

void Map_WorldObjectsInit(void) // 0x800D82A8
{
    WorldObjectInit(&g_WorldObject_Map, "MAP_NEAR", 41.2f, -0.7f, -48.7f, 0.0f, -100.1f, 0.0f);
    func_800CB0D8();

    WorldObjectInit(&g_WorldObject_SavePad0, D_800A99E4.savePadName_4, 40.503f, -0.709f, -48.7925f, 0.0f, 5.7f, 0.0f);
    WorldObjectInit(&g_WorldObject_SavePad1, D_800A99E4.savePadName_4, -86.469f, -1.041f, -103.4905f, 0.0f, 206.3f, 0.0f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        func_80088FF4(Chara_Creeper, 0, 0);
        func_80088FF4(Chara_Creeper, 1, 0);
        func_80088FF4(Chara_Creeper, 4, 0);
        func_80088FF4(Chara_Creeper, 7, 0);
        func_80088FF4(Chara_Creeper, 12, 0);

        g_SysWork.npcId_2280 = 3;
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        func_80088FF4(Chara_Creeper, 5, (1 << 2) | (1 << 3));
        func_80088FF4(Chara_Creeper, 6, (1 << 2) | (1 << 3));
        func_80088FF4(Chara_Creeper, 7, 0);
        func_80088FF4(Chara_Creeper, 8, (1 << 0) | (1 << 2) | (1 << 3));
        func_80088FF4(Chara_Creeper, 9, (1 << 0) | (1 << 2) | (1 << 3));

        g_SysWork.npcId_2280 = 4;
    }
    else
    {
        g_SysWork.npcId_2280 = 4;
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x800D84D8
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S00_PickupMap))
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Map.object_0,
                               &g_WorldObject_Map.position_1C,
                               &g_WorldObject_Map.rotation_28);
        }

        WorldGfx_ObjectAdd(&g_WorldObject_SavePad0.object_0,
                           &g_WorldObject_SavePad0.position_1C,
                           &g_WorldObject_SavePad0.rotation_28);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        WorldGfx_ObjectAdd(&g_WorldObject_SavePad1.object_0,
                           &g_WorldObject_SavePad1.position_1C,
                           &g_WorldObject_SavePad1.rotation_28);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(368))
        {
            if (Savegame_EventFlagGet(EventFlag_354) && (g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(-66.0f)))
            {
                func_8005DC1C(1585, &D_800CB0CC, 0xFF, 2);
                Savegame_EventFlagSet(368);
            }
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S00_ShotgunShells))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &D_800DAAD0.position_0, &D_800DAAD0.rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S00_HealthDrink0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &D_800DAAE4.position_0, &D_800DAAE4.rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S00_HandgunBullets0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &D_800DAAF8.position_0, &D_800DAAF8.rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S00_RifleShells))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &D_800DAB0C.position_0, &D_800DAB0C.rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S00_FirstAidKit0))
        {
            WorldGfx_ObjectAdd(g_CommonWorldObjects, &D_800DAB20.position_0, &D_800DAB20.rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S00_FirstAidKit1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[0], &D_800DAB34.position_0, &D_800DAB34.rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S00_HealthDrink1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &D_800DAB48.position_0, &D_800DAB48.rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S00_HandgunBullets1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &D_800DAB5C.position_0, &D_800DAB5C.rotation_C);
        }
    }
}

void func_800D8DFC(void) // 0x800D8DFC
{
    if (Savegame_EventFlagGet(EventFlag_354))
    {
        func_80088FF4(Chara_HangedScratcher, 0, 6);
        func_80088FF4(Chara_HangedScratcher, 1, 6);
        func_80088FF4(Chara_HangedScratcher, 2, 6);

        if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
        {
            func_80088FF4(Chara_HangedScratcher, 11, 6);
        }

        if (Savegame_MapMarkingGet(MapMarkFlag_527))
        {
            func_80089034(Chara_HangedScratcher, 12, Q12(-90.3f), Q12(-92.9f));
        }

        func_80088FF4(Chara_HangedScratcher, 12, 6);
        func_80088FF4(Chara_HangedScratcher, 13, 6);
    }

    if (Savegame_EventFlagGet(EventFlag_M5S00_PickupSewerKey))
    {
        func_80088FF4(Chara_HangedScratcher, 6, 9);
    }
}

INCLUDE_RODATA("maps/map5_s00/nonmatchings/map5_s00", D_800CB0CC);
