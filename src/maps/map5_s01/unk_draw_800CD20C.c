#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "maps/map5/map5_s01.h"

s16 func_800CD20C(void) // 0x800CD20C
{
    s32      i;
    GsDOBJ2* itemModel;

    if (D_800F159C == 1)
    {
        if (g_SysWork.sysStateStep_C[0] == 5)
        {
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
            {
                D_800ED5C8 += 3;
                Sd_PlaySfx(Sfx_MenuMove, 0, 0x40);
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickUp)
            {
                D_800ED5C8 += 1;
                Sd_PlaySfx(Sfx_MenuMove, 0, 0x40);
            }

            D_800ED5C8 &= 0x3;

            if (g_Controller0->btnsHeld_C & ControllerFlag_LStickLeft)
            {
                Sd_PlaySfx(Sfx_Unk1589, 0, 0x40);

                D_800F1598[D_800ED5C8]++;
                if (D_800F1598[D_800ED5C8] == 8)
                {
                    D_800F1598[D_800ED5C8] = 0;
                }
            }

            if (g_Controller0->btnsHeld_C & ControllerFlag_LStickRight)
            {
                Sd_PlaySfx(Sfx_Unk1589, 0, 0x40);

                D_800F1598[D_800ED5C8]--;
                if (D_800F1598[D_800ED5C8] == -1)
                {
                    D_800F1598[D_800ED5C8] = 7;
                }
            }
        }
    }

    D_800F15A0 = D_800F1598[0] + (D_800F1598[1] * 10) + (D_800F1598[2] * 100) + (D_800F1598[3] * 1000);

    func_800CE180();

    func_800CD51C(D_800F15A0, D_800ED5C8);
    PushMatrix();
    func_8004BBF4(&D_800F1570, &D_800F1510, &D_800F1560);

    for (itemModel = g_Items_ItemsModelData, i = 0; i < 6; i++, itemModel++)
    {
        g_Items_Transforms[i].rotate.vx = Q12_ANGLE(90.0f);
        g_Items_Transforms[i].rotate.vz = Q12_ANGLE(0.0f);

        ItemScreen_ItemRotate(&g_Items_Coords[i].param->rotate, &g_Items_Coords[i]);

        if (D_800F159C != 0)
        {
            func_800CDB14(i, D_800ED5C8);
        }

        GsSetFlatLight(0, &D_800F1450[i][0]);
        func_8004BD74(i, itemModel, 0);
    }

    PopMatrix();
    func_800CDB98();

    if (D_800F159C == 1)
    {
        return D_800F15A0;
    }
    else
    {
        return 0;
    }
}

void func_800CD51C(s32 arg0, s32 arg1) // 0x800CD51C
{
    s32 temp_v0;
    s32 i;
    s32 var_t1;
    s32 var_v0_2;
    s32 var_v0_3;
    s8  temp_v1_2;

    var_t1 = 0;

    switch (D_800F159C)
    {
        case 0:
            for (i = 0; i < 6; i++)
            {
                g_Items_Transforms[i].scale.vx =
                g_Items_Transforms[i].scale.vy =
                g_Items_Transforms[i].scale.vz = Q12(2.0f);

                temp_v0 = (D_800F159D * 0xFF) / 32;

                D_800F1450[i][1].b = temp_v0;
                D_800F1450[i][1].g = temp_v0;
                D_800F1450[i][1].r = temp_v0;
                D_800F1450[i][0].b = temp_v0;
                D_800F1450[i][0].g = temp_v0;
                D_800F1450[i][0].r = temp_v0;
            }

            D_800F159D++;

            if (D_800F159D >= 32)
            {
                D_800F159C = 1;
                D_800F159D = 0;
            }
            break;

        case 1:
            if (D_800F1590 != arg0)
            {
                D_800F159C = 2;
            }

            for (i = 0; i < 6; i++)
            {
                switch (i)
                {
                    case 0:
                        g_Items_Coords[i].coord.t[0] = Q8(0.0f);
                        g_Items_Coords[i].coord.t[1] = Q8(-0.204f);
                        g_Items_Coords[i].coord.t[2] = Q8(-32.5f);
                        break;

                    case 5:
                        g_Items_Coords[i].coord.t[0] = Q8(0.0f);
                        g_Items_Coords[i].coord.t[1] = Q8(-0.08f);
                        g_Items_Coords[i].coord.t[2] = Q8(-32.5f);
                        break;

                    default:
                        g_Items_Coords[i].coord.t[0] = Q8(0.0f);
                        g_Items_Coords[i].coord.t[1] = Q8(1.555f) - (i * Q8(0.415f));
                        g_Items_Coords[i].coord.t[2] = Q8(-32.5f);
                        break;
                }
            }
            break;

        case 2:
            D_800F159D++;

            if ((D_800F1594[arg1] < D_800F1598[arg1] && (D_800F1594[arg1] != 0 || D_800F1598[arg1] != 7)) ||
                (D_800F1594[arg1] == 7 && D_800F1598[arg1] == 0))
            {
                var_t1 = 1;
            }
            else
            {
                var_t1 = -1;
            }

            if (D_800F159D >= 16)
            {
                D_800F159C = 1;
                D_800F159D = 0;
                D_800F1590 = arg0;

                for (i = 0; i < 4; i++)
                {
                    D_800F1594[i] = D_800F1598[i];
                }

                var_t1 = 0;
            }
            break;
    }

    var_v0_2 = var_t1 * (D_800F159D << 9);

    g_Items_Transforms[0].rotate.vy = Q12_ANGLE(292.5f);
    g_Items_Transforms[5].rotate.vy = Q12_ANGLE(292.5f);

    for (i = 1; i < 5; i++)
    {
        temp_v1_2 = D_800F1594[i - 1];
        if (temp_v1_2 == D_800F1598[i - 1])
        {
            var_v0_3 = temp_v1_2 << 9;
        }
        else
        {
            var_v0_3 = (temp_v1_2 << 9) + (var_v0_2 / 16);
        }

        g_Items_Transforms[i].rotate.vy = var_v0_3 + Q12_ANGLE(247.5f);
    }
}

void func_800CD818(void) // 0x800CD818
{
    Fs_QueueStartReadTim(FILE_ITEM_FOOK_TIM, FS_BUFFER_1, &D_800A907C);
    Fs_QueueStartRead(FILE_ITEM_FOOK_TMD, FS_BUFFER_21);
    Fs_QueueWaitForEmpty();
}

void func_800CD860(void) // 0x800CD860
{
    GsCOORD2PARAM* var_v1;
    GsCOORDINATE2* var_s1_2;
    s32            i;
    s16            temp_a0;
    s16            var_s1;

    var_s1                 = D_800F15A0;
    g_Items_DisplayedCount = 0;

    D_800F159C = 0;
    D_800F159D = 0;
    D_800ED5C8 = 3;

    ItemScreen_CamSet(&D_800F1570, &D_800F1510, (SVECTOR3*)&D_800F1560, 0);

    for (i = 0; i < 6; i++)
    {
        g_Items_Transforms[i].rotate.vz = 0;
        g_Items_Transforms[i].rotate.vx = 0;
        g_Items_Transforms[i].trans.vz  = 0;
        g_Items_Transforms[i].trans.vy  = 0;
        g_Items_Transforms[i].trans.vx  = 0;

        switch (i)
        {
            case 0:
            case 5:
                g_Items_Transforms[i].rotate.vy = 0x500;
                break;

            default:
                D_800F1594[i] = temp_a0         = var_s1 % 10;
                var_s1                          = var_s1 / 10;
                g_Items_Transforms[i].rotate.vy = (temp_a0 << 9) + 0xB00;
                break;
        }

        g_Items_Transforms[0].rotate.vy = 0xD00;
        g_Items_Transforms[5].rotate.vy = 0xD00;

        for (i = 1; i < 5; i++)
        {
            g_Items_Transforms[i].rotate.vy = (D_800F1598[i - 1] << 9) + 0xB00;
        }
    }

    GameFs_TmdDataAlloc((s32*)FS_BUFFER_21);

    for (i = 0; i < 6; i++)
    {
        Gfx_Items_Display((s_TmdFile*)FS_BUFFER_21, i, i);
        func_8005487C(i);

        switch (i)
        {
            case 0:
                g_Items_Coords[i].coord.t[0] = 0;
                g_Items_Coords[i].coord.t[1] = -0x34;
                g_Items_Coords[i].coord.t[2] = -0x2080;
                break;

            case 5:
                g_Items_Coords[i].coord.t[0] = 0;
                g_Items_Coords[i].coord.t[1] = -0x14;
                g_Items_Coords[i].coord.t[2] = -0x2080;
                break;

            default:
                g_Items_Coords[i].coord.t[0] = 0;
                g_Items_Coords[i].coord.t[1] = 0x18E - 0x6A * i;
                g_Items_Coords[i].coord.t[2] = -0x2080;
                break;
        }
    }

    func_800CDA8C();
}

void func_800CDA8C(void) // 0x800CDA8C
{
    s32 i;

    for (i = 0; i < 6; i++)
    {
        D_800F1450[i][0].vx = g_Items_Coords[i].coord.t[0];
        D_800F1450[i][0].vy = g_Items_Coords[i].coord.t[1];
        D_800F1450[i][0].vz = g_Items_Coords[i].coord.t[2] + 0x4E20;

        D_800F1450[i][1].vx = 0x1000;
        D_800F1450[i][1].vy = 0;
        D_800F1450[i][1].vz = 0;
    }

    GsSetAmbient(0x100, 0x100, 0x100);
    GsSetLightMode(1);
}

void func_800CDB14(s32 arg0, s32 arg1) // 0x800CDB14
{
    s32 i;

    D_800F1450[arg0][0].vx = g_Items_Coords[arg0].coord.t[0];
    D_800F1450[arg0][0].vy = g_Items_Coords[arg0].coord.t[1];
    D_800F1450[arg0][0].vz = g_Items_Coords[arg0].coord.t[2] + 0x4E20;

    D_800F1450[arg0][1].vx = 0;
    D_800F1450[arg0][1].vy = 0;
    D_800F1450[arg0][1].vz = 0;

    for (i = 0; i < 2; i++)
    {
        D_800F1450[arg0][i].r = 0xFF;
        D_800F1450[arg0][i].g = 0xFF;
        D_800F1450[arg0][i].b = 0xFF;
    }
}

void func_800CDB98(void) // 0x800CDB98
{
    GsOT*    ot;
    s32      i;
    POLY_G3* poly_g3;
    POLY_G4* poly_g4;
    s32      temp_s5;
    s32      temp_s6;
    s32      temp_s7;

    ot = &g_OrderingTable2[g_ActiveBufferIdx];

    for (i = 0; i < 16; i++)
    {
        poly_g3 = GsOUT_PACKET_P;

        setPolyG3(poly_g3);
        setSemiTrans(poly_g3, 1);

        if (D_800F159C == 0)
        {
            setRGB0(poly_g3, D_800F159D * 4, D_800F159D * 4, D_800F159D * 0x70 / 32);
            setRGB1(poly_g3, D_800F159D * 0x62 / 32, D_800F159D * 0x62 / 32, D_800F159D * 0x54 / 32);
            setRGB2(poly_g3, D_800F159D * 0x62 / 32, D_800F159D * 0x62 / 32, D_800F159D * 0x54 / 32);
        }
        else
        {
            setRGB0(poly_g3, 0x80, 0x80, 0x70);
            setRGB1(poly_g3, 0x62, 0x62, 0x54);
            setRGB2(poly_g3, 0x62, 0x62, 0x54);
        }

        temp_s5 = 0x5A;

        setXY0Fast(poly_g3, 0, 0);
        setXY1Fast(poly_g3, Q12_MULT(Math_Sin(i << 8), temp_s5), Q12_MULT(Math_Cos(i << 8), temp_s5));
        setXY2Fast(poly_g3, Q12_MULT(Math_Sin((i + 1) << 8), temp_s5), Q12_MULT(Math_Cos((i + 1) << 8), temp_s5));

        addPrim(&ot->org[10], poly_g3);
        GsOUT_PACKET_P = poly_g3 + 1;
    }

    for (i = 0; i < 16; i++)
    {
        poly_g4 = GsOUT_PACKET_P;

        setPolyG4(poly_g4);
        setSemiTrans(poly_g4, 1);

        if (D_800F159C == 0)
        {
            setRGB0(poly_g4, D_800F159D * 3, D_800F159D * 3, D_800F159D * 0x54 / 32);
            setRGB1(poly_g4, D_800F159D * 3, D_800F159D * 3, D_800F159D * 0x54 / 32);
        }
        else
        {
            setRGB0(poly_g4, 0x60, 0x60, 0x54);
            setRGB1(poly_g4, 0x60, 0x60, 0x54);
        }

        setRGB2(poly_g4, 0, 0, 0);
        setRGB3(poly_g4, 0, 0, 0);

        temp_s7 = 0x5A;
        temp_s6 = 0xB4;

        setXY0Fast(poly_g4, Q12_MULT(Math_Sin(i << 8), temp_s7), Q12_MULT(Math_Cos(i << 8), temp_s7));
        setXY1Fast(poly_g4, Q12_MULT(Math_Sin((i + 1) << 8), temp_s7), Q12_MULT(Math_Cos((i + 1) << 8), temp_s7));
        setXY2Fast(poly_g4, Q12_MULT(Math_Sin(i << 8), temp_s6), Q12_MULT(Math_Cos(i << 8), temp_s6));
        setXY3Fast(poly_g4, Q12_MULT(Math_Sin((i + 1) << 8), temp_s6), Q12_MULT(Math_Cos((i + 1) << 8), temp_s6));

        addPrim(&ot->org[10], poly_g4);
        GsOUT_PACKET_P = poly_g4 + 1;
    }

    Gfx_Primitive2dTextureSet(0, 0, 0xA, 1);
}

void func_800CE180(void) // 0x800CE180
{
    GsOT*    ot;
    s32      i;
    POLY_G3* poly_g3;

    ot = &g_OrderingTable2[g_ActiveBufferIdx];

    for (i = 0; i < 2; i++)
    {
        poly_g3 = GsOUT_PACKET_P;

        setPolyG3(poly_g3);
        setSemiTrans(poly_g3, 1);

        setRGB0(poly_g3, 0xC0, 0x80, 0);
        setRGB1(poly_g3, 0xC0, 0x80, 0);
        setRGB2(poly_g3, 0xFF, 0x40, 0);

        setXY0Fast(poly_g3, -0x30 + 0x60 * i, (0x1D - D_800ED5C8 * 0x14));
        setXY1Fast(poly_g3, -0x30 + 0x60 * i, (0x2D - D_800ED5C8 * 0x14));
        setXY2Fast(poly_g3, -0x40 + 0x80 * i, (0x25 - D_800ED5C8 * 0x14));

        addPrim(&ot->org[9], poly_g3);

        GsOUT_PACKET_P = poly_g3 + 1;
    }
}
