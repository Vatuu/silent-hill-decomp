#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "screens/saveload/saveload.h"

void func_801E2D8C() // 0x801E2D8C
{
    s32 i;
    s32 j;

    func_80037124();

    D_801E750C = 0;
    D_801E7510 = 0;
    D_801E76D4 = INVENTORY_ITEM_COUNT_MAX;
    D_801E76D6 = 0;

    for (i = 0; i < MEMORY_CARD_SLOT_COUNT; i++)
    {
        D_801E76D2[i] = 1;
        D_801E76CE[i] = NO_VALUE;
        D_801E7564[i] = 0;
        D_801E756C[i] = 0;
        D_801E7570[i] = NO_VALUE;
        D_801E7574[i] = NO_VALUE;
        D_801E7578[i] = 0;
        D_801E7514[i] = 1;
        D_801E7518[i] = 0;

        for (j = 0; j < SAVE_COUNT_MAX; j++)
        {
            D_801E7584[j + (SAVE_COUNT_MAX * i)] = 0;
        }

        D_801E76D0 = 1;
    }
}

void Gfx_SaveBackgroundDraw() // 0x801E2EBC
{
    s_func_801E5898 var;
    s32             i;
    
    DVECTOR posTable[] = 
    {
        {
            .vx = 59,
            .vy = 16
        },
        {
            .vx = 209,
            .vy = 16
        }
    };

    char* strs[] =
    {
        "SLOT1",
        "SLOT2"
    };

    Gfx_StringSetColor(ColorId_White);
    
    for (i = 0; i < MEMORY_CARD_SLOT_COUNT; i++)
    {
        Gfx_StringSetPosition(posTable[i].vx, posTable[i].vy);
        Gfx_StringDraw(strs[i], 50);
    }

    var.field_0.vx = -136;
    var.field_0.vy = 60;
    var.field_4.vx = 272;
    var.field_4.vy = 40;
    Gfx_RectSaveInfoDraw(&var);
}

void func_801E2F90(s32 saveSlotIdx) // 0x801E2F90
{
    D_801E7578[saveSlotIdx] = D_800A97D4[saveSlotIdx] - D_801E7570[saveSlotIdx];
}

void func_801E2FCC(s32 arg0, s32 saveSlotIdx, s32 fileId, s32 arg3) // 0x801E2FCC
{
    #define OFFSET_X             SCREEN_POSITION_X(47.0f)
    #define FILE_STR_MARGIN_X    SCREEN_POSITION_X(10.0f)
    #define FILE_ID_STR_MARGIN_X FILE_STR_MARGIN_X + SCREEN_POSITION_X(15.75f)
    #define POS_Y                SCREEN_POSITION_Y(14.75f)

    char* str = "FILE";

    if (arg0 == D_800A97D4[saveSlotIdx] && arg3 >= 4)
    {
        Gfx_StringSetColor(ColorId_White);

        // Draw "FILE" string.
        Gfx_StringSetPosition((saveSlotIdx * OFFSET_X) + FILE_STR_MARGIN_X, POS_Y);
        Gfx_StringDraw(str, 50);

        // Draw file ID string.
        Gfx_StringSetPosition((saveSlotIdx * OFFSET_X) + FILE_ID_STR_MARGIN_X, POS_Y);
        Gfx_StringDrawInt(1, fileId);
    }
}

s32 func_801E3078(s_UnkSaveload0* arg0) // 0x801E3078
{
    if (arg0 != NULL && (arg0->field_8 & (1 << 24)))
    {
        Gfx_StringSetColor(ColorId_Gold);
        return 1;
    }

    Gfx_StringSetColor(ColorId_White);
    return 0;
}

void func_801E30C4(s_UnkSaveload0* ptr, s32 arg1, s32 idx) // 0x801E30C4
{
    #define OFFSET_X SCREEN_POSITION_X(47.0f)
    #define MARGIN_X SCREEN_POSITION_X(28.25f)
    #define OFFSET_Y SCREEN_POSITION_Y(8.5f)
    #define MARGIN_Y SCREEN_POSITION_Y(22.25f)

    s32 idxVar = (s8)ptr->field_8;

    u8 D_801E2728[] =
        {
            0x52, 0x25, 0x1E, 0x2C,
            0x51, 0x51, 0x3D, 0x3D,
            0x3B, 0x33, 0x54, 0x51,
            0x51, 0x6D, 0x4B, 0x6F,
            0x61, 0x26, 0x37, 0x2D,
            0x5F, 0x30, 0x47, 0x66,
            0x4D};

    s32 var0;
    s16 var1;
    s32 colorId;
    u8* var2;

    var1 = D_801E7570[idx];

    if (arg1 >= var1 && (var1 + 4) >= arg1)
    {
        var0 = arg1 - var1;

        func_801E3078(ptr->field_C);

        if (D_801E76D6 != 0 && D_800A97D6 == idx && D_800A97D4[idx] == arg1)
        {
            if (D_801E76D5 != 0)
            {
                colorId = ColorId_Gold;
            }
            else
            {
                colorId = ColorId_White;
            }
            Gfx_StringSetColor(colorId);
        }

        Gfx_StringSetPosition(((idx * OFFSET_X) + MARGIN_X) - (D_801E2728[idxVar] / 2),
                              (var0 * OFFSET_Y) + MARGIN_Y);
        Gfx_StringDraw(D_801E74A8[idxVar], 50);
    }
}

void func_801E326C(s8* arg0, s8* arg1, s32 arg2, s32 arg3) // 0x801E326C
{
    if (arg2 == 0)
    {
        D_801E756C[arg3] = 0;
    }

    if (arg2 < D_801E7570[arg3] || (D_801E7570[arg3] + 4) < arg2)
    {
        if (D_801E756C[arg3] != arg0[6])
        {
            D_801E756C[arg3] = arg0[6];
        }
    }
    else
    {
        Gfx_SavesOutlineDraw(arg0, arg1, arg2, arg3);
    }
}

void func_801E3304(s8* arg0, s32 arg1, s32 arg2) // 0x801E3304
{
    char* D_801E2830[] =
        {
            "\x07MEMORY_CARD\nis_not_inserted",
            "\x07MEMORY_CARD\nis_\x01not_\x01"
            "formatted",
            "\x07MEMORY_CARD\nmay_be_broken",
            "\x07Now_checking\nMEMORY_CARD",
            "\x07Out_of_blocks",
            "\x07No_data_file",
            "\x07No_data_file",
            "\x07____Fil"
            "\x01"
            "e_\x01\x01is_\x01\x01"
            "da\x01ma\x01g\x01"
            "ed",
            "\x07",
            "\x07________\x01New_save",
            "\x07____Crea\x01t\x01"
            "e_\x01n\x01"
            "e\x01w_\x01"
            "fi\x01le"};

    s32 i;
    s32 temp_s2;

    temp_s2 = arg0[4];

    if (D_800A97D6 == arg2 && arg1 == 0 && temp_s2 >= 7)
    {
        Gfx_SelectedMemBarDraw();
    }

    if (arg1 == 0)
    {
        func_801E3E78();

        D_801E76D4++;
        D_801E76D4 = CLAMP(D_801E76D4, 0, 40);

        if (temp_s2 != 3)
        {
            D_801E7518[arg2] = 0;
        }

        if (D_801E7570[arg2] == NO_VALUE)
        {
            D_801E7570[arg2] = 0;
        }

        if ((u8)D_801E76D2[arg2] != 0)
        {
            if (D_800A97D4[arg2] == D_800BCD3C[arg2] - 2)
            {
                D_801E7570[arg2] = D_800A97D4[arg2] - 3;
            }
            else
            {
                D_801E7570[arg2] = D_800A97D4[arg2] - 2;
            }
        }

        if ((D_800BCD3C[arg2] < 6) || D_800A97D4[arg2] == 0)
        {
            D_801E7570[arg2] = 0;
        }
        else
        {
            if ((D_800BCD3C[arg2] - 2) < D_800A97D4[arg2])
            {
                D_801E7570[arg2] = D_800BCD3C[arg2] - 5;
            }
            else
            {
                while (D_800A97D4[arg2] - D_801E7570[arg2] >= 4)
                {
                    D_801E7570[arg2]++;
                }
                while (D_800A97D4[arg2] - 1 < D_801E7570[arg2])
                {
                    D_801E7570[arg2]--;
                }
            }
        }
        if (D_801E7570[arg2] != D_801E7574[arg2])
        {
            D_801E7514[arg2] = 1;
        }
    }

    switch (temp_s2)
    {
        case 1:
            D_801E76D2[arg2] = 0;
            if (g_GameWork.gameState_594 == 16)
            {
                func_801E43C8(arg2);
            }
            break;

        case 3:
            D_801E76D2[arg2] = 1;
            for (i = 0; i < 165; i++)
            {
                D_801E7584[i + (arg2 * 165)] = 0;
            }
            D_801E7570[arg2] = NO_VALUE;
            break;

        case 7:
        case 8:
        case 9:
        case 10:
            D_801E76D2[arg2] = 0;
            if (arg1 == 0)
            {
                Gfx_SavesTransparentBgDraw(arg2, D_800BCD3C[arg2], D_800A97D4[arg2], D_801E7578[arg2]);
            }
            break;
    }

    if ((arg1 < D_801E7570[arg2]) || ((D_801E7570[arg2] + 4) < arg1))
    {
        return;
    }

    D_801E7514[arg2] = 1;
    Gfx_StringSetColor(ColorId_White);

    switch (temp_s2)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            Gfx_StringSetPosition((arg2 * 150) + 22, 82);
            break;

        case 5:
        case 6:
            Gfx_StringSetPosition((arg2 * 150) + 38, 90);
            break;

        case 4:
            Gfx_StringSetPosition((arg2 * 150) + 32, 90);
            break;

        default:
            Gfx_StringSetPosition((arg2 * 150) + 6, (D_801E7518[arg2] * 20) + 53);
            break;
    }

    Gfx_StringDraw(D_801E2830[temp_s2], 50);

    if (temp_s2 < 7)
    {
        func_801E52D8(arg2, temp_s2);
    }

    D_801E7518[arg2]++;

    if (D_801E7518[arg2] == 5 || arg1 == D_800BCD3C[arg2] - 1)
    {
        if (D_801E7564[arg2] == 0)
        {
            D_801E7564[arg2] = 1;
        }

        D_801E7514[arg2] = 0;

        if (temp_s2 != 3)
        {
            D_801E7518[arg2] = 0;
        }
    }
}

// `arg0` = what it's doing. Formatting, saving, or loading.
void func_801E3910(s32 arg0, s32 arg1) // 0x801E3910
{
    s32 strIdx;

    char* strs[] =
        {
            " ",
            "\x07You_\x01\x01removed_\x01\x01the_\x01\x01MEMORY_\x01\x01"
            "CARD!",
            "\x07Now_formatting...",
            "\x07Now_saving...",
            "\x07Unable_to_create_a_new_file.",
            "\x07"
            "Finished_saving.",
            "\x07"
            "Failed_to_save!",
            "\x07The_data_is_not_found!",
            "\x07The_data_is_damaged!",
            "\x07"
            "Failed_to_load!",
            "\x07"
            "Finished_loading.",
            "\x07Now_loading..."};

    s16 xOffsets[] =
        {
            0, 268,
            141, 107,
            223, 136,
            119, 182,
            170, 117,
            143, 114};

    switch (arg0)
    {
        // Format.
        case 1:
            strIdx = (arg1 == arg0) ? 1 : 2;
            break;

        // Save.
        case 2:
            switch (arg1)
            {
                // Memory card removed.
                case 0:
                    strIdx = 1; 
                    break;

                // Now saving.
                case 1:
                    strIdx = 3; 
                    break;

                // Unable to create new file.
                case 7:
                    strIdx = 4;
                    break;

                // Finished saving.
                case 11:
                    strIdx = 5; 
                    break;

                // Failed to save.
                case 10:
                    strIdx = 6; 
                    break;

                default:
                    strIdx = 0; 
                    break;
            }
            break;

        // Load.
        case 3:
            switch (arg1)
            {
                // Now loading.
                case 1:
                    strIdx = 11;
                    break;

                // Data is damaged.
                case 101:
                    strIdx = 8;
                    break;

                // Failed to load.
                case 10:
                    strIdx = 9;
                    break;

                // Finished loading.
                case 11:
                    strIdx = 10;
                    break;

                // Memory card removed.
                case 0:
                    strIdx = 1;
                    break;

                // Memory card removed.
                case 100:
                    strIdx = 1;
                    break;

                default:
                    strIdx = 0;
                    break;
            }
            break;

        default:
            strIdx = 0;
            break;
    }

    switch (D_801E7510)
    {
        case 0:
            D_801E750C = 0;
            D_801E7554 = 0;

            if (strIdx == 1)
            {
                g_GameWork.gameStateStep_598[2] = 0;
                D_801E7570[D_800A97D6] = NO_VALUE;
                D_801E7578[D_800A97D6] = NO_VALUE;
            }

            D_801E7554 = strIdx;
            D_801E7510++;
            
        case 1:
            // Loading and something.
            if (arg0 == 2 && arg1 == 1)
            {
                D_801E76D6 = arg1;
            }

            // Finished saving and `D_801E7554` isn't required string.
            if (strIdx == 5 && D_801E7554 != strIdx)
            {
                D_801E76CE[D_800A97D6] = D_800A97D4[D_800A97D6];
                D_801E76CE[1 - D_800A97D6] = NO_VALUE;
                D_801E76D4 = 0;
            }

            D_801E7554 = strIdx;
            Gfx_StringSetPosition(160 - (xOffsets[strIdx] >> 1), 186);
            Gfx_StringDraw(strs[strIdx], 99);

            // Finished saving.
            if (strIdx == 5)
            {
                D_801E76D6 = 0;
            }
            break;

        default:
            break;
    }
}

void func_801E3C44(s32 arg0, s32 arg1) // 0x801E3C44
{
    GsOT*     ot;
    GsOT_TAG* temp_t0;
    s8        color;
    u32       time;

    POLY_F4* poly;

    char* D_801E2A3C[] =
        {
            "\x07Is_it_OK_to_overwrite?",
            "\x07Is_it_OK_to_format?",
            "\x07Yes__________No"};

    u8 xOffsets[] =
        {
            0xb4, 0x9a};

    D_801E76D0 = 0;
    time       = (u8)g_SysWork.timer_1C & 0x3F;
    ot         = &g_ObjectTable1[g_ObjectTableIdx];

    switch (D_801E750C)
    {
        case 0:
            D_801E7510 = 0;
            D_801E7558 = arg0 != 0;
            D_801E750C = 1;

        case 1:
            Gfx_StringSetPosition(0xA0 - (xOffsets[arg0] / 2), 0xB2);
            Gfx_StringDraw(D_801E2A3C[arg0], 0x63);
            Gfx_StringSetPosition(0x68, 0xC4);
            Gfx_StringDraw("\x07Yes__________No", 0x63);

            poly = (POLY_F4*)GsOUT_PACKET_P;
            setlen(poly, 5);
            setcode(poly, 0x2A);

            if (time < 0x20u)
            {
                color = (time * 2) + 0x20;
                setRGB0(poly, color, color, 0x20);
            }
            else
            {
                color = 0x60 - ((time - 0x20) * 2);
                setRGB0(poly, color, color, 0x20);
            }

            if (arg1 != 0)
            {
                setXY4(poly, -0x42, 0x52, -0x42, 0x62, -0x12, 0x52, -0x12, 0x62);
            }
            else
            {
                setXY4(poly, 0x12, 0x52, 0x12, 0x62, 0x42, 0x52, 0x42, 0x62);
            }

            GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_F4);
            addPrim((u8*)ot->org + 0x1C, poly);

            func_80052088(0, 0, 7, 1);
            break;
    }
}

void func_801E3E78() // 0x801E3E78
{
    GsOT*    ot;
    s32      temp_s0;
    s32      temp_v0;
    s8       temp_v1;
    u32      temp_s1;
    POLY_F4* poly;

    ot      = &g_ObjectTable1[g_ObjectTableIdx];
    temp_s0 = ~D_801E76CE[0] == 0;
    temp_s1 = D_801E76CE[temp_s0] - D_801E7570[temp_s0];

    if (temp_s1 < 5U)
    {
        temp_v0 = shRsin((D_801E76D4 << 0xA) / 40);
        poly    = (POLY_F4*)GsOUT_PACKET_P;
        setlen(poly, 5);
        setcode(poly, 0x2A);

        temp_v1 = ~FP_FROM(temp_v0 * 0xFF, Q12_SHIFT);
        setRGB0(poly, temp_v1, temp_v1, temp_v1);

        setXY4(poly,
               temp_s0 * 0x96 - 0x82, temp_s1 * 0x14 - 0x3E,
               temp_s0 * 0x96 - 0x82, temp_s1 * 0x14 - 0x2B,
               temp_s0 * 0x96 - 0x0B, temp_s1 * 0x14 - 0x3E,
               temp_s0 * 0x96 - 0x0B, temp_s1 * 0x14 - 0x2B);

        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_F4);
        addPrim((u8*)ot->org + 0x18, poly);

        func_80052088(0, 0, 6, 1);
    }
}

void Gfx_SelectedMemBarDraw() // 0x801E4010
{
    s_801E2A98 D_801E2A48[5][2] =
        {

            {
                {{0xFF95, 0xFFA8}, {0xFF6E, 0xFFA8}},
                {{0xFF95, 0xFFA9}, {0xFF6E, 0xFFA9}},
            },
            {
                {{0xFFD6, 0xFFA8}, {0xFFFE, 0xFFA8}},
                {{0xFFD6, 0xFFA9}, {0xFFFE, 0xFFA9}},
            },
            {
                {{0xFF6E, 0xFFA8}, {0xFF6E, 0x002A}},
                {{0xFF6F, 0xFFA9}, {0xFF6F, 0x0029}},
            },
            {
                {{0xFFFE, 0xFFA8}, {0xFFFE, 0x002A}},
                {{0xFFFD, 0xFFA9}, {0xFFFD, 0x0029}},
            },
            {
                {{0xFF6E, 0x002A}, {0xFFFE, 0x002A}},
                {{0xFF6F, 0x0029}, {0xFFFD, 0x0029}},
            }

        };

    s_801E2A48 D_801E2A98[5][2] =
        {
            {
                {{0xFF96, 0xFFA8}, {0xFF96, 0xFFA4}, {0xFF6E, 0xFFA8}, {0xFF6A, 0xFFA4}},
                {{0xFF96, 0xFFA9}, {0xFF96, 0xFFAD}, {0xFF6E, 0xFFA9}, {0xFF72, 0xFFAD}},
            },
            {
                {{0xFFD6, 0xFFA8}, {0xFFD6, 0xFFA4}, {0xFFFE, 0xFFA8}, {0x0002, 0xFFA4}},
                {{0xFFD6, 0xFFA9}, {0xFFD6, 0xFFAD}, {0xFFFE, 0xFFA9}, {0xFFFA, 0xFFAD}},
            },
            {
                {{0xFF6E, 0xFFA8}, {0xFF6A, 0xFFA4}, {0xFF6E, 0x002A}, {0xFF6A, 0x002E}},
                {{0xFF6F, 0xFFA9}, {0xFF73, 0xFFAD}, {0xFF6F, 0x0029}, {0xFF73, 0x0025}},
            },
            {
                {{0xFFFE, 0xFFA8}, {0x0002, 0xFFA4}, {0xFFFE, 0x002A}, {0x0002, 0x002E}},
                {{0xFFFD, 0xFFA9}, {0xFFF9, 0xFFAD}, {0xFFFD, 0x0029}, {0xFFF9, 0x0025}},
            },
            {
                {{0xFF6E, 0x002A}, {0xFF6A, 0x002E}, {0xFFFE, 0x002A}, {0x0002, 0x002E}},
                {{0xFF6F, 0x0029}, {0xFF73, 0x0025}, {0xFFFD, 0x0029}, {0xFFF9, 0x0025}},
            }};

    GsOT*    ot;
    s32      i;
    s32      j;
    LINE_F2* line;
    POLY_G4* poly;

    ot = &g_ObjectTable1[g_ObjectTableIdx];

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 5; j++)
        {
            line = (LINE_F2*)GsOUT_PACKET_P;
            setLineF2(line);
            setRGB0(line, 0, 0xFF, 0);

            setXY2(line,
                   D_801E2A48[j][i].field_0.vx + D_800A97D6 * 0x96, D_801E2A48[j][i].field_0.vy,
                   D_801E2A48[j][i].field_4.vx + D_800A97D6 * 0x96, D_801E2A48[j][i].field_4.vy);

            addPrim((u8*)ot->org + 0x1C, line);
            GsOUT_PACKET_P = (u8*)line + sizeof(LINE_F2);
        }
    }

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 5; j++)
        {
            poly = (POLY_G4*)GsOUT_PACKET_P;
            setlen(poly, 8);
            setcode(poly, 0x3A);

            setRGB0(poly, 0, 0x80, 0);
            setRGB1(poly, 0, 0, 0);
            setRGB2(poly, 0, 0x80, 0);
            setRGB3(poly, 0, 0, 0);

            setXY4(poly,
                   D_801E2A98[j][i].field_0.vx + D_800A97D6 * 0x96, D_801E2A98[j][i].field_0.vy,
                   D_801E2A98[j][i].field_4.vx + D_800A97D6 * 0x96, D_801E2A98[j][i].field_4.vy,
                   D_801E2A98[j][i].field_8.vx + D_800A97D6 * 0x96, D_801E2A98[j][i].field_8.vy,
                   D_801E2A98[j][i].field_C.vx + D_800A97D6 * 0x96, D_801E2A98[j][i].field_C.vy);

            addPrim((u8*)ot->org + 0x1C, poly);
            GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G4);
        }
    }

    func_80052088(0, 0, 7, 1);
}

void func_801E43C8(s32 arg0) // 0x801E43C8
{
    GsOT*    ot;
    s16      temp_v1_3;
    s32      temp_a2;
    s8       temp_v0;
    POLY_F4* poly;

    temp_a2   = ((u8)g_SysWork.timer_1C) & 0x3F;
    temp_v1_3 = temp_a2;
    ot        = &g_ObjectTable1[g_ObjectTableIdx];

    if (D_800A97D6 == arg0)
    {
        poly = (POLY_F4*)GsOUT_PACKET_P;
        setlen(poly, 5);
        setcode(poly, 0x2A);

        if (temp_v1_3 < 0x20U)
        {
            temp_v0 = (temp_v1_3 * 2) + 0x20;
            setRGB0(poly, temp_v0, temp_v0, 0x20);
        }
        else
        {
            temp_v0 = 0x60 - ((temp_v1_3 - 0x20) * 2);
            setRGB0(poly, temp_v0, temp_v0, 0x20);
        }

        setXY4(poly,
               arg0 * 0x96 - 0x8E, -0x23, arg0 * 0x96 - 0x8E, 2,
               arg0 * 0x96 - 6, -0x23, arg0 * 0x96 - 6, 2);

        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_F4);
        addPrim((u8*)ot->org + 0x1C, poly);

        func_80052088(0, 0, 7, 1);
    }
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", Gfx_SavesTransparentBgDraw); // 0x801E451C

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", Gfx_SavesOutlineDraw); // 0x801E4D90

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E52D8); // 0x801E52D8

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", Gfx_RectMemLoadDraw); // 0x801E54DC

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", Gfx_RectSaveInfoDraw); // 0x801E5898

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", Save_SaveDataInfoDraw); // 0x801E5E18

void GameState_SaveScreen_Update() // 0x801E6320
{
    D_801E76D0 = 1;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        D_801E7524[0]();
    }

    D_801E7524[g_GameWork.gameStateStep_598[0]]();

    Gfx_SaveBackground();
    func_801E7244();
    func_801E70C8();

    if (g_GameWork.gameState_594 == GameState_Unk10)
    {
        func_800363D0();
    }
}

void func_801E63C0() // 0x801E63C0
{
    if (g_GameWork.gameStatePrev_590 == GameState_MainMenu)
    {
        VSync(8);
    }

    g_IntervalVBlanks = 1;
    D_800BCD0C = 6;

    g_GameWork.field_58C = 0;
    g_GameWork.field_58D = 0;
    g_GameWork.field_58E = 0;

    D_800BCD39 = 0;
    if (g_GameWork.gameState_594 == GameState_DeathLoadScreen || g_GameWork.gameState_594 == GameState_SaveScreen)
    {
        if (D_800A97D8 != 0)
        {
            D_800BCD34 = 0;
        }
    }

    D_801E7520 = 0;
    D_800A97D8 = (g_GameWork.gameState_594 == GameState_Unk10);

    func_801E2D8C();

    g_SysWork.timer_20 = 0;
    g_GameWork.gameStateStep_598[0]++;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E649C); // 0x801E649C

void func_801E69E8() // 0x801E69E8
{
    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            D_801E751C = 1;
            D_801E7520 = 30;
            g_GameWork.gameStateStep_598[1] = 1;
            g_GameWork.gameStateStep_598[2] = 0;

        case 1:
            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case 2:
            func_8002E94C(6, D_800BCD40, 0, 0);

            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case 3:
            switch (func_8002E990())
            {
                case 10:
                    D_801E7520 = 30;
                    g_GameWork.gameStateStep_598[0] = 1;
                    g_SysWork.timer_20 = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;

                case 11:
                    g_SysWork.timer_20 = 0;
                    g_GameWork.gameStateStep_598[0]++;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E6B18); // 0x801E6B18

void func_801E6DB0() // 0x801E6DB0
{
    s32 var0;
    s32 var1;

    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            D_801E751C = 3;

            func_8002E94C(4, D_800BCD40, D_800BCD3F, D_800BCD3E);

            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;

        case 1:
            var0 = func_8002E990();
            if (var0 != 1)
            {
                if (var0 != 11)
                {
                    D_800BCD39 = 1;
                    g_GameWork.gameStateStep_598[0] = 1;
                    g_SysWork.timer_20 = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;
                }

                func_8002E94C(2, D_800BCD40, 0, 0);

                g_GameWork.gameStateStep_598[1]++;
                g_GameWork.gameStateStep_598[2] = 0;
                break;
            }

            D_801E7520 = 30;
            break;

        case 2:
            var1 = func_8002E990();
            if (var1 == 1)
            {
                D_801E7520 = 30;
                break;
            }

            if (var1 != 11)
            {
                D_800BCD39 = 1;
                g_GameWork.gameStateStep_598[0] = 1;
                g_SysWork.timer_20 = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                break;
            }

            D_801E7520 = 300;
            g_SysWork.timer_20 = 0;
            g_GameWork.gameStateStep_598[0]++;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        default:
            break;
    }
}

void func_801E6F38() // 0x801E6F38
{
    switch (g_GameWork.gameStateStep_598[1])
    {
        // TODO: Are these meant to use GameState? `gameStateStep` is normally something different?
        // First case here increments it too.
        case GameState_Unk0:
            func_8002E830();

            D_800A97D7 = 1;

            // Backup current savegame? Does anything ever restore from this?
            g_GameWork.saveGame_90 = g_GameWork.saveGame_30C;

            func_80035178();
            
            g_SysWork.flags_2298 = 8;

            GameFs_MapLoad(g_SaveGamePtr->mapOverlayIdx_A4);

            D_800BCD0C = 2;
            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case GameState_KonamiLogo:
        {
            if ((D_800BCD0C & 0x7) == 0x5)
            {
                Fs_QueueWaitForEmpty();
                Settings_ScreenAndVolUpdate();

                Game_StateSetNext(GameState_MainLoadScreen);
            }
            break;
        }

        default:
            break;
    }
}

void Gfx_SaveBackground() // 0x801E709C
{
    // Draw "SLOT 1"/"SLOT 2" strings and bottom transparent frame.
    Gfx_SaveBackgroundDraw();

    // Draws background image.
    Gfx_BackgroundSpriteDraw(&D_800A902C);
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E70C8); // 0x801E70C8

void func_801E7244() // 0x801E7244
{
    if (D_801E7520 <= 0)
    {
        return;
    }

    D_801E76D0 = 0;
    D_801E7520--;

    switch (D_801E751C) 
    {
        case 1:
            func_801E3910(D_801E751C, (D_800BCD34 >> (D_800BCD40 * 3)) & 0x7);
            break;

        case 2:
        case 3:
            func_801E3910(D_801E751C, func_8002E990());
            break;
    }
}

void func_801E72DC(s32 arg0, s32 arg1) // 0x801E72DC
{
    func_801E3C44(arg0, arg1);
}

void GameState_DeathLoadScreen_Update() // 0x801E72FC
{
    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        D_801E7544[0]();
    }

    D_801E7544[g_GameWork.gameStateStep_598[0]]();

    Gfx_SaveBackground();
    func_801E7244();
    func_801E70C8();
}

void func_801E737C() // 0x801E737C
{
    if (!func_80033548())
    {
        return;
    }

    if (D_800BCD28 == 0 || D_800BCD39 != 0 || !func_80033548())
    {
        g_GameWork.gameState_594 = GameState_SaveScreen;

        if (g_GameWork.gameStatePrev_590 == GameState_KcetLogo)
        {
            g_GameWork.gameStateStep_598[0] = 1;
            g_GameWork.gameStateStep_598[1] = g_GameWork.gameStatePrev_590;

            D_800BCD0C = 3;

            GameFs_TitleGfxLoad();
        }

        return;
    }

    D_800BCD2C = BOOT_ADDR_0 + (D_800A97D6 * 2640);
    D_800BCD2C = D_800BCD2C + (D_800A97D4[D_800A97D6] * 16);
    D_800BCD40 = D_800BCD2C[5];
    D_800BCD3F = D_800BCD2C[6];
    D_800BCD3E = D_800BCD2C[7];

    g_GameWork.gameStateStep_598[0]++;
    g_SysWork.timer_20 = 0;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;
}
