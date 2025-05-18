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
    s_801E2A98 var;
    s32        i;
    
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
        82, 37, 30, 44,
        81, 81, 61, 61,
        59, 51, 84, 81,
        81, 109, 75, 111,
        97, 38, 55, 45,
        95, 48, 71, 102,
        77
    };


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
        "\x07MEMORY_CARD\nis_\x01not_\x01""formatted",
        "\x07MEMORY_CARD\nmay_be_broken",
        "\x07Now_checking\nMEMORY_CARD",
        "\x07Out_of_blocks",
        "\x07No_data_file",
        "\x07No_data_file",
        "\x07____Fil""\x01""e_\x01\x01is_\x01\x01""da\x01ma\x01g\x01""ed",
        "\x07",
        "\x07________\x01New_save",
        "\x07____Crea\x01t\x01""e_\x01n\x01""e\x01w_\x01""fi\x01le"
    };

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
        "\x07You_\x01\x01removed_\x01\x01the_\x01\x01MEMORY_\x01\x01""CARD!",
        "\x07Now_formatting...",
        "\x07Now_saving...",
        "\x07Unable_to_create_a_new_file.",
        "\x07""Finished_saving.",
        "\x07""Failed_to_save!",
        "\x07The_data_is_not_found!",
        "\x07The_data_is_damaged!",
        "\x07""Failed_to_load!",
        "\x07""Finished_loading.",
        "\x07Now_loading..."
    };

    s16 xOffsets[] =
    {
        0, 268,
        141, 107,
        223, 136,
        119, 182,
        170, 117,
        143, 114
    };

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
    s8        color;
    u32       time;
    POLY_F4*  poly;

    char* D_801E2A3C[] =
    {
        "\x07Is_it_OK_to_overwrite?",
        "\x07Is_it_OK_to_format?",
        "\x07Yes__________No"
    };

    u8 xOffsets[] =
    {
        180, 154
    };

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
            Gfx_StringSetPosition(160 - (xOffsets[arg0] / 2), 178);
            Gfx_StringDraw(D_801E2A3C[arg0], 99);
            Gfx_StringSetPosition(0x68, 0xC4);
            Gfx_StringDraw("\x07Yes__________No", 99);

            poly = (POLY_F4*)GsOUT_PACKET_P;
            setlen(poly, 5);
            setcode(poly, 0x2A);

            if (time < 32)
            {
                color = (time * 2) + 32;
                setRGB0(poly, color, color, 32);
            }
            else
            {
                color = 96 - ((time - 32) * 2);
                setRGB0(poly, color, color, 32);
            }

            if (arg1 != 0)
            {
                setXY4(poly, -66, 82, -66, 98, -18, 82, -18, 98);
            }
            else
            {
                setXY4(poly, 18, 82, 18, 98, 66, 82, 66, 98);
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
    s32      sin;
    s8       color;
    u32      temp_s1;
    POLY_F4* poly;

    ot      = &g_ObjectTable1[g_ObjectTableIdx];
    temp_s0 = ~D_801E76CE[0] == 0;
    temp_s1 = D_801E76CE[temp_s0] - D_801E7570[temp_s0];

    if (temp_s1 < 5U)
    {
        sin = shRsin((D_801E76D4 << 0xA) / 40);
        poly    = (POLY_F4*)GsOUT_PACKET_P;
        setlen(poly, 5);
        setcode(poly, 0x2A);

        color = ~FP_FROM(sin * 0xFF, Q12_SHIFT);
        setRGB0(poly, color, color, color);

        setXY4(poly,
               temp_s0 * 150 - 130, temp_s1 * 20 - 62,
               temp_s0 * 150 - 130, temp_s1 * 20 - 43,
               temp_s0 * 150 - 11, temp_s1 * 20 - 62,
               temp_s0 * 150 - 11, temp_s1 * 20 - 43);

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
            {{-107, -88}, {-146, -88}},
            {{-107, -87}, {-146, -87}},
        },
        {
            {{-42, -88}, {-2, -88}},
            {{-42, -87}, {-2, -87}},
        },
        {
            {{-146, -88}, {-146, 42}},
            {{-145, -87}, {-145, 41}},
        },
        {
            {{-2, -88}, {-2, 42}},
            {{-3, -87}, {-3, 41}},
        },
        {
            {{-146, 42}, {-2, 42}},
            {{-145, 41}, {-3, 41}},
        }
    };

    s_801E2A48 D_801E2A98[5][2] =
    {
        {
            {{-106, -88}, {-106, -92}, {-146, -88}, {-150, -92}},
            {{-106, -87}, {-106, -83}, {-146, -87}, {-142, -83}},
        },
        {
            {{-42, -88}, {-42, -92}, {-2, -88}, {2, -92}},
            {{-42, -87}, {-42, -83}, {-2, -87}, {-6, -83}},
        },
        {
            {{-146, -88}, {-150, -92}, {-146, 42}, {-150, 46}},
            {{-145, -87}, {-141, -83}, {-145, 41}, {-141, 37}},
        },
        {
            {{-2, -88}, {2, -92}, {-2, 42}, {2, 46}},
            {{-3, -87}, {-7, -83}, {-3, 41}, {-7, 37}},
        },
        {
            {{-146, 42}, {-150, 46}, {-2, 42}, {2, 46}},
            {{-145, 41}, {-141, 37}, {-3, 41}, {-7, 37}},
        }
    };

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
                   D_801E2A48[j][i].field_0.vx + D_800A97D6 * 150, D_801E2A48[j][i].field_0.vy,
                   D_801E2A48[j][i].field_4.vx + D_800A97D6 * 150, D_801E2A48[j][i].field_4.vy);

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
                   D_801E2A98[j][i].field_0.vx + D_800A97D6 * 150, D_801E2A98[j][i].field_0.vy,
                   D_801E2A98[j][i].field_4.vx + D_800A97D6 * 150, D_801E2A98[j][i].field_4.vy,
                   D_801E2A98[j][i].field_8.vx + D_800A97D6 * 150, D_801E2A98[j][i].field_8.vy,
                   D_801E2A98[j][i].field_C.vx + D_800A97D6 * 150, D_801E2A98[j][i].field_C.vy);

            addPrim((u8*)ot->org + 0x1C, poly);
            GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G4);
        }
    }

    func_80052088(0, 0, 7, 1);
}

void func_801E43C8(s32 arg0) // 0x801E43C8
{
    GsOT*    ot;
    s16      time;
    s32      temp;
    s8       color;
    POLY_F4* poly;

    temp = ((u8)g_SysWork.timer_1C) & 0x3F;
    time = temp;
    ot   = &g_ObjectTable1[g_ObjectTableIdx];

    if (D_800A97D6 == arg0)
    {
        poly = (POLY_F4*)GsOUT_PACKET_P;
        setlen(poly, 5);
        setcode(poly, 0x2A);

        if ((u16)time < 32)
        {
            color = (time * 2) + 32;
            setRGB0(poly, color, color, 32);
        }
        else
        {
            color = 96 - ((time - 32) * 2);
            setRGB0(poly, color, color, 32);
        }

        setXY4(poly,
               arg0 * 150 - 142, -35, arg0 * 150 - 142, 2,
               arg0 * 150 - 6, -35, arg0 * 150 - 6, 2);

        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_F4);
        addPrim((u8*)ot->org + 0x1C, poly);

        func_80052088(0, 0, 7, 1);
    }
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", Gfx_SavesTransparentBgDraw); // 0x801E451C

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", Gfx_SavesOutlineDraw); // 0x801E4D90

// TODO: Rodata migration
#ifdef NON_MATCHING
void func_801E52D8(s32 arg0, s32 arg1) // 0x801E52D8
{
    s_801E2C8C D_801E2C8C[2] =
    {
        {
            { 0xFF72, 0xFFDF }, { 0x0088, 0x0021 }, 0x00FF, 0x0000, 0x0000, 0x0000,
        },
        {
            { 0xFF72, 0xFFDF }, { 0x0088, 0x0021 }, 0x0000, 0x00FF, 0x0000, 0x0000
        }
    };

    s_801E2CAC D_801E2CAC =
    { 
        {
            {{ 0xFF70, 0xFFDC }, { 0xFFFC, 0xFFDC }},
            {{ 0xFF70, 0x0002 }, { 0xFFFC, 0x0002 }},
            {{ 0xFF70, 0xFFDC }, { 0xFF70, 0x0002 }},
            {{ 0xFFFC, 0xFFDC }, { 0xFFFC, 0x0002 }}
        }    
    };

    s_801E2CCC D_801E2CCC =
    {
        {
            {{ 0xFF70, 0xFFDC }, { 0xFF6C, 0xFFD8 }, { 0xFFFC, 0xFFDC }, { 0x0000, 0xFFD8 }},
            {{ 0xFF70, 0x0002 }, { 0xFF6C, 0x0006 }, { 0xFFFC, 0x0002 }, { 0x0000, 0x0006 }},
            {{ 0xFF70, 0xFFDC }, { 0xFF6C, 0xFFD8 }, { 0xFF70, 0x0002 }, { 0xFF6C, 0x0006 }},
            {{ 0xFFFC, 0xFFDC }, { 0x0000, 0xFFD8 }, { 0xFFFC, 0x0002 }, { 0x0000, 0x0006 }}
        }
    };
    
    if (arg1 == 1 && g_GameWork.gameState_594 == GameState_Unk10) 
    {
        Gfx_RectMemLoadDraw(&D_801E2CAC, &D_801E2CCC, &D_801E2C8C[1], arg0);
    } 
    else 
    {
        Gfx_RectMemLoadDraw(&D_801E2CAC, &D_801E2CCC, &D_801E2C8C[0], arg0);
    }
}
#else
INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E52D8); // 0x801E52D8
#endif

void Gfx_RectMemLoadDraw(s_801E2CAC* arg0, s_801E2CCC* arg1, s_801E2C8C* arg2, s32 arg3) // 0x801E54DC
{
    GsOT* ot;
    s32 i;
    s_801E2A98* temp;
    LINE_F2* line;
    POLY_G4* poly_g4;
    POLY_F4* poly_f4;
    
    ot = &g_ObjectTable1[g_ObjectTableIdx];
    
    for (i = 0; i < 4; i++)
    {
        line = (LINE_F2*)GsOUT_PACKET_P;
        setLineF2(line);
        setRGB0(line, arg2->field_8, arg2->field_A, arg2->field_C);
        setXY2(line,
            arg0->field_0[i].field_0.vx + arg3 * 0x96, arg0->field_0[i].field_0.vy,
            arg0->field_0[i].field_4.vx + arg3 * 0x96, arg0->field_0[i].field_4.vy
        );
        addPrim((u8*)ot->org + 0x1C, line);
        GsOUT_PACKET_P = (u8*)line + sizeof(LINE_F2);
    }
    
    for (i = 0; i < 4; i++)
    {
        poly_g4 = (POLY_G4*)GsOUT_PACKET_P;
        setlen(poly_g4, 8);
        setcode(poly_g4, 0x3A);
        setRGB0(poly_g4, arg2->field_8 / 2, arg2->field_A / 2, arg2->field_C / 2);
        setRGB1(poly_g4, 0, 0, 0);
        setRGB2(poly_g4, arg2->field_8 / 2, arg2->field_A / 2, arg2->field_C / 2);
        setRGB3(poly_g4, 0, 0, 0);

        temp = (s_801E2A98*)&arg1->field_0[i].field_8;

        setXY4(poly_g4,
            arg1->field_0[i].field_0.vx + arg3 * 0x96, arg1->field_0[i].field_0.vy,
            arg1->field_0[i].field_4.vx + arg3 * 0x96, arg1->field_0[i].field_4.vy,
            arg1->field_0[i].field_8.vx + arg3 * 0x96, temp->field_0.vy,
            temp->field_4.vx + arg3 * 0x96, temp->field_4.vy
        );

        addPrim((u8*)ot->org + 0x20, poly_g4);
        GsOUT_PACKET_P = (u8*)poly_g4 + sizeof(POLY_G4);
    }
    
    func_80052088(0, 0, 5, 1);
    
    poly_f4 = (POLY_F4*)GsOUT_PACKET_P;
    setlen(poly_f4, 5);
    setcode(poly_f4, 0x2A);
    setRGB0(poly_f4, 0x30, 0x30, 0x30);

    setXY4(poly_f4,
        arg2->field_0.vx + arg3 * 0x96, arg2->field_0.vy,
        arg2->field_0.vx + arg3 * 0x96, arg2->field_0.vy + arg2->field_4.vy,
        arg2->field_0.vx + arg2->field_4.vx + arg3 * 0x96, arg2->field_0.vy,
        arg2->field_0.vx + arg2->field_4.vx + arg3 * 0x96, arg2->field_0.vy + arg2->field_4.vy
    );
    
    addPrim((u8*)ot->org + 0x20, poly_f4);
    GsOUT_PACKET_P = (u8*)poly_f4 + sizeof(POLY_F4);
    
    func_80052088(0, 0, 8, 1);
}

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

/**
D_800BCD2C seems to be supposed to be a pointer struct, but it
was defined previously as a pointer byte (s8*) and defining it
as a pointer struct causes a big missmatch in `func_800C9874`.

Alternatively declaring it as a pointer int (s32*) doesn't
help too much.
*/
#ifdef NON_MATCHING
void func_801E649C()
{
    s32				step = g_GameWork.gameStateStep_598[1];
    s_UnkSaveload0* ptr;

    switch (step) 
    {
        case 0:
            if (func_80033548() == 0) 
            {
                break;
            }
            
            if (D_800BCD30[0] != 0 && D_800BCD30[1] != 0 && 
                (g_ControllerPtrConst->btns_new_10 & (Pad_LStickRight | Pad_LStickLeft))) 
            {
                D_800A97D6 ^= 1;
                Sd_EngineCmd(0x519);
            }
            
            if (D_800BCD3A > 0) 
            {
                D_801E753C = 0;
                D_801E7540 = 0;
                D_800BCD2C = (s_UnkSaveload0*)((D_800A97D6 * 0xA50) + BOOT_ADDR_0);
                
                if (g_ControllerPtrConst->field_18 & Pad_LStickUp) 
                {
                    if (D_800A97D4[D_800A97D6] != 0) 
                    {
                        D_800A97D4[D_800A97D6]--;
                        Sd_EngineCmd(0x519);
                    }
                }
                
                if (g_ControllerPtrConst->field_18 & Pad_LStickDown) 
                {
                    if (D_800A97D4[D_800A97D6] < D_800BCD30[D_800A97D6] - 1)
                    {
                        D_800A97D4[D_800A97D6]++;
                        Sd_EngineCmd(0x519);
                    }
                }
                
                ptr		   = &D_800BCD2C[D_800A97D4[D_800A97D6]];
                D_800BCD2C = ptr;
                D_800BCD40 = ptr->field_5;
                D_800BCD3F = ptr->field_6;
                D_800BCD3E = ptr->field_7;
                
                if (D_800BCD38 == 2) 
                {
                    if (ptr->field_0 == 0x7B70)
                    {
                        D_801E753C = 1;
                    }
                    
                    if ((u16)ptr->field_0 - 1 < 0x797B) 
                    {
                        D_801E7540 = 1;
                    }
                }
                
                if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerBinds_0.enter) 
                {
                    if ((D_801E753C | D_801E7540) != 0) 
                    {
                        D_801E755C 						 = 0;
                        g_GameWork.gameStateStep_598[2]  = 0;
                        g_GameWork.gameStateStep_598[1] += 1;
                    }
                    else
                    {
                        g_SysWork.timer_20 				 = 0;
                        g_GameWork.gameStateStep_598[1]  = 0;
                        g_GameWork.gameStateStep_598[2]  = 0;
                        g_GameWork.gameStateStep_598[0] += D_800BCD38;
                    }
                    Sd_EngineCmd(0x51B);
                }
            }
            
            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerBinds_0.cancel) 
            {
                D_800BCD0C						= 3;
                g_GameWork.gameStateStep_598[1] = 2;
                g_GameWork.gameStateStep_598[2] = 0;
                
                Sd_EngineCmd(0x51A);
                
                if (g_GameWork.gameStatePrev_590 == GameState_StatusScreen) 
                {
                    Sd_EngineCmd(0x17);
                    GameFs_TitleGfxLoad();
                    GameFs_StreamBinSeek();
                }
            }
            break;
        
        case 1:
            if (func_80033548() == 0) 
            {
                break;
            }

            D_801E7520 = 0;
            
            if (g_ControllerPtrConst->btns_new_10 & Pad_LStickLeft) 
            {
                D_801E755C = step;
                Sd_EngineCmd(0x519);
            }
            
            if (g_ControllerPtrConst->btns_new_10 & Pad_LStickRight) 
            {
                D_801E755C = 0;
                Sd_EngineCmd(0x519);
            }
            
            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerBinds_0.enter) 
            {
                if (D_801E755C == 0) 
                {
                    g_GameWork.gameStateStep_598[0] = step;
                    g_SysWork.timer_20 				= 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
                else
                {
                    g_SysWork.timer_20 				= 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    g_GameWork.gameStateStep_598[0] = D_801E7540 + 2;
                }
                Sd_EngineCmd(0x51B);
            }
            
            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerBinds_0.cancel) 
            {
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                Sd_EngineCmd(0x51A);
            }
            
            func_801E72DC(D_801E753C, D_801E755C);
            
            break;
        
        case 2:
            if ((D_800BCD0C & 7) == 5)
            {
                g_GameWork.field_58C = 0;
                g_GameWork.field_58D = 0;
                g_GameWork.field_58E = 0;
                
                Fs_QueueWaitForEmpty();
                
                if (g_GameWork.gameStatePrev_590 == GameState_StatusScreen)
                {
                    Game_StateSetNext(g_GameWork.gameStatePrev_590);
                }
                else
                {
                    if (D_800BCD38 == step)
                    {
                        func_8002E830();
                        Game_StateSetNext(GameState_InGame);
                    }
                    else
                    {
                        Game_StateSetNext(GameState_MainMenu);
                    }
                }
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E649C); // 0x801E649C
#endif

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
