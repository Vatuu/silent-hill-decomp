#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "screens/saveload/saveload.h"

/*
char* D_801E74A8[] =
{
    "Anywhere",
    "Cafe",
    "Bus",
    "Store",
    "Infirmary",
    "Doghouse",
    "Gordon",
    "Church",
    "Garage",
    "Police",
    "Reception",
    "Room_302",
    "Director's",
    "Jewelry_shop",
    "Pool_hall",
    "Antique_shop",
    "Theme_park",
    "Boat",
    "Bridge",
    "Motel",
    "Lighthouse",
    "Sewer",
    "Nowhere",
    "Child's_room",
    "Next_fear"
};

s32 D_801E750C = 0;

s32 D_801E7510 = 0;

s16 D_801E7514[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s16 D_801E7518[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s32 g_MemCardState = 0;

s32 g_MemCardStateTextTimer = 0;

void (*D_801E7524[])() =
{
    func_801E63C0,
    func_801E649C,
    func_801E69E8,
    func_801E6B18,
    func_801E6DB0,
    func_801E6F38
};

s32 D_801E753C = 0;

s32 D_801E7540 = 0;

void (*D_801E7544[])() =
{
    func_801E63C0,
    func_801E737C,
    func_801E6DB0,
    func_801E6F38
};

s32 D_801E7554 = 0;

s32 D_801E7558 = 0;

s32 D_801E755C = 0;

s32 D_801E7560 = 0; // Unused.

s32 D_801E7564[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s16 D_801E756C[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s16 D_801E7570[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s16 D_801E7574[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s16 D_801E7578[6] = { 0, 0, 0, 0, 0, 0 };

s8 D_801E7584[330] = { 0 };

s8 D_801E76CE[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s8 g_DisplaySaveDataInfo = 0;

s8 D_801E76D1 = 0; // Unused.

s8 D_801E76D2[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s8 D_801E76D4 = 0;

u8 D_801E76D5 = 0;

u8 D_801E76D6 = 0;
*/

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

        g_DisplaySaveDataInfo = 1;
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

void Gfx_SaveSelectedDisplacement(s32 saveSlotIdx, s32 arg1) // 0x801E2F90
{
    D_801E7578[saveSlotIdx] = D_800A97D4[saveSlotIdx] - D_801E7570[saveSlotIdx];
}

void Gfx_SaveFileSelectedDraw(s32 arg0, s32 saveSlotIdx, s32 fileId, s32 arg3) // 0x801E2FCC
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

s32 func_801E3078(s_UnkSaveload1* arg0) // 0x801E3078
{
    if (arg0 != NULL && arg0->isTitleYellowFlag_B_0)
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

void func_801E326C(s_UnkSaveload0* arg0, s_UnkSaveload0* arg1, s32 arg2, s32 arg3) // 0x801E326C
{
    if (arg2 == 0)
    {
        D_801E756C[arg3] = 0;
    }

    if (arg2 < D_801E7570[arg3] || (D_801E7570[arg3] + 4) < arg2)
    {
        if (D_801E756C[arg3] != arg0->field_6)
        {
            D_801E756C[arg3] = arg0->field_6;
        }
    }
    else
    {
        Gfx_SavesOutlineDraw(arg0, arg1, arg2, arg3);
    }
}

// Draw and update all the elements of the slots, save information and memory card states
// Gfx_MainSaveDrawUpdate
void func_801E3304(s_UnkSaveload0* arg0, s32 arg1, s32 arg2) // 0x801E3304
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

    temp_s2 = arg0->field_4;

    if (D_800A97D6 == arg2 && arg1 == 0 && temp_s2 >= 7)
    {
        Gfx_MemSelectedBarDraw();
    }

    if (arg1 == 0)
    {
        Gfx_SavedFlickerDraw();

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
            if (D_800A97D4[arg2] == g_SaveCount[arg2] - 2)
            {
                D_801E7570[arg2] = D_800A97D4[arg2] - 3;
            }
            else
            {
                D_801E7570[arg2] = D_800A97D4[arg2] - 2;
            }
        }

        if ((g_SaveCount[arg2] < 6) || D_800A97D4[arg2] == 0)
        {
            D_801E7570[arg2] = 0;
        }
        else
        {
            if ((g_SaveCount[arg2] - 2) < D_800A97D4[arg2])
            {
                D_801E7570[arg2] = g_SaveCount[arg2] - 5;
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

            if (g_GameWork.gameState_594 == GameState_Unk10)
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
                Gfx_SavesTransparentBgDraw(arg2, g_SaveCount[arg2], D_800A97D4[arg2], D_801E7578[arg2]);
            }

            break;

        default:
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

    if (D_801E7518[arg2] == 5 || arg1 == g_SaveCount[arg2] - 1)
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
void Gfx_MemCardStateDraw(s32 memCardState, s32 arg1) // 0x801E3910
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

    switch (memCardState)
    {
        // Format.
        case 1:
            strIdx = (arg1 == memCardState) ? 1 : 2;
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
            if (memCardState == 2 && arg1 == 1)
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

void Gfx_OverwriteSaveDraw(s32 arg0, s32 arg1) // 0x801E3C44
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

    g_DisplaySaveDataInfo = 0;
    time                  = (u8)g_SysWork.timer_1C & 0x3F;
    ot                    = &g_ObjectTable1[g_ObjectTableIdx];

    switch (D_801E750C)
    {
        case 0:
            D_801E7510 = 0;
            D_801E7558 = arg0 != 0;
            D_801E750C = 1;

        case 1:
            Gfx_StringSetPosition(160 - (xOffsets[arg0] / 2), 178);
            Gfx_StringDraw(D_801E2A3C[arg0], 99);
            Gfx_StringSetPosition(104, 196);
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

void Gfx_SavedFlickerDraw() // 0x801E3E78
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

    if (temp_s1 < 5)
    {
        sin  = shRsin((D_801E76D4 << 10) / 40);
        poly = (POLY_F4*)GsOUT_PACKET_P;
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

void Gfx_MemSelectedBarDraw() // 0x801E4010
{
    s_801E2A98 D_801E2A48[5][2] =
    {
        {
            { {-107, -88 }, { -146, -88 } },
            { {-107, -87 }, { -146, -87 } }
        },
        {
            { { -42, -88 }, { -2, -88 } },
            { { -42, -87 }, { -2, -87 } }
        },
        {
            { { -146, -88 }, { -146, 42 } },
            { { -145, -87 }, { -145, 41 } }
        },
        {
            { { -2, -88 }, { -2, 42 } },
            { { -3, -87 }, { -3, 41 } }
        },
        {
            { { -146, 42 }, { -2, 42 } },
            { { -145, 41 }, { -3, 41 } }
        }
    };

    s_801E2A48 D_801E2A98[5][2] =
    {
        {
            { { -106, -88 }, { -106, -92 }, { -146, -88 }, { -150, -92 } },
            { { -106, -87 }, { -106, -83 }, { -146, -87 }, { -142, -83 } },
        },
        {
            { { -42, -88 }, { -42, -92 }, { -2, -88 }, { 2, -92 } },
            { { -42, -87 }, { -42, -83 }, { -2, -87 }, { -6, -83 } },
        },
        {
            { { -146, -88 }, { -150, -92}, {-146, 42}, {-150, 46 } },
            { { -145, -87 }, { -141, -83}, {-145, 41}, {-141, 37 } },
        },
        {
            { { -2, -88 }, { 2, -92 }, { -2, 42 }, { 2, 46 } },
            { { -3, -87 }, { -7, -83 }, { -3, 41 }, { -7, 37 } },
        },
        {
            { { -146, 42 }, { -150, 46 }, { -2, 42 }, { 2, 46 } },
            { { -145, 41 }, { -141, 37 }, { -3, 41 }, { -7, 37 } },
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

void Gfx_SavesTransparentBgDraw(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x801E451C
{
    u32 temp_s4 = (u8)g_SysWork.timer_1C & 0x3F;

    s_801E2A48 D_801E2B38[] =
    {
        {{0, 0}, {0, 96}, {4, 0}, {4, 96}},
        {{8, 0}, {8, 96}, {4, 0}, {4, 96}}
    };

    s_801E2B58 D_801E2B58[2][2] =
    {
        {
            {{4, -1}, {-1, 7}, {8, 7}},
            {{5, 1}, {0, 8}, {9, 8}},
        },
        {
            {{4, 96}, {0, 88}, {8, 88}},
            {{5, 97}, {1, 89}, {9, 89}}
        }
    };

    u8 D_801E2B88[] =
    {
        79, 40, 27, 20, 16, 14, 12, 10,
        9, 8, 8, 7, 7, 6, 6, 5,
        5, 5, 5, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
    };

    GsOT*    ot;
    s32      temp_a0;
    s32      temp_a2;
    s32      temp_a2_2;
    s32      temp_t1;
    s32      temp_t2_2;
    s32      temp_v1;
    s32      i;
    s32      j;
    u8       color;
    u32      temp_t3;
    POLY_F4* poly_f4;
    POLY_F4* poly_f4_2;
    POLY_F4* poly_f4_3;
    POLY_G3* poly_g3;
    POLY_G4* poly_g4;

    ot = &g_ObjectTable1[g_ObjectTableIdx];

    if ((g_DisplaySaveDataInfo == 1) && (arg0 == D_800A97D6))
    {
        Save_SaveDataInfoDraw(arg0, arg2);
    }

    if (arg1 != 0)
    {
        temp_a2 = ((arg2 * 79) / arg1) + 8;
        temp_t3 = D_801E2B88[arg1 - 1];

        for (i = 0; i < 2; i++)
        {
            poly_f4 = (POLY_F4*)GsOUT_PACKET_P;

            setPolyF4(poly_f4);

            if (i != 0)
            {
                setRGB0(poly_f4, 0x70, 0x70, 0x70);
            }
            else
            {
                setRGB0(poly_f4, 0x50, 0x50, 0x50);
            }

            temp_t1 = (arg0 * 150) - 139;
            temp_a0 = (i - 60);

            setXY4(poly_f4,
                   (D_801E2B38[0].field_0.vx + temp_t1) + i, (D_801E2B38[0].field_0.vy + temp_a2) + temp_a0,
                   (D_801E2B38[0].field_0.vx + temp_t1) + i, ((D_801E2B38[0].field_0.vy + temp_a2) + temp_t3) - (i + 60),
                   (D_801E2B38[1].field_0.vx + temp_t1) - i, (D_801E2B38[1].field_0.vy + temp_a2) + temp_a0,
                   (D_801E2B38[1].field_0.vx + temp_t1) - i, ((D_801E2B38[1].field_0.vy + temp_a2) + temp_t3) - (i + 60));

            addPrim((u8*)ot->org + 0x1C - 4 * i, poly_f4);
            GsOUT_PACKET_P = (u8*)poly_f4 + sizeof(POLY_F4);
        }
    }

    if (D_800A97D6 == arg0)
    {
        poly_f4_2 = (POLY_F4*)GsOUT_PACKET_P;
        setlen(poly_f4_2, 5);
        setcode(poly_f4_2, 0x2A);

        if (temp_s4 < 0x20U)
        {
            color = (temp_s4 * 2) + 0x20;
            setRGB0(poly_f4_2, color, color, 0x20);
        }
        else
        {
            color = 0x60 - ((temp_s4 - 0x20) * 2);
            setRGB0(poly_f4_2, color, color, 0x20);
        }

        setXY4(poly_f4_2,
               arg0 * 150 - 130, arg3 * 20 - 62,
               arg0 * 150 - 130, arg3 * 20 - 43,
               arg0 * 150 - 10, arg3 * 20 - 62,
               arg0 * 150 - 10, arg3 * 20 - 43);

        addPrim((u8*)ot->org + 0x1C, poly_f4_2);
        GsOUT_PACKET_P = (u8*)poly_f4_2 + sizeof(POLY_F4);

        func_80052088(0, 0, 7, 1);
    }

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 1; j++)
        {
            poly_g3 = (POLY_G3*)GsOUT_PACKET_P;
            setPolyG3(poly_g3);

            setRGB0(poly_g3, 0xA0, 0xA0, 0xA0);
            setRGB1(poly_g3, 0xA0, 0xA0, 0xA0);
            setRGB2(poly_g3, 0xA0, 0xA0, 0xA0);

            temp_t2_2 = (arg0 * 150) - 139;

            setXY3(poly_g3,
                   D_801E2B58[i][j].field_0.vx + temp_t2_2, D_801E2B58[i][j].field_0.vy - 60,
                   D_801E2B58[i][j].field_4.vx + temp_t2_2, D_801E2B58[i][j].field_4.vy - 60,
                   D_801E2B58[i][j].field_8.vx + temp_t2_2, D_801E2B58[i][j].field_8.vy - 60);

            addPrim((u8*)ot->org + 0x1C, poly_g3);
            GsOUT_PACKET_P = (u8*)poly_g3 + sizeof(POLY_G3);
        }
    }

    for (i = 0; i < 2; i++)
    {
        poly_g4 = (POLY_G4*)GsOUT_PACKET_P;
        setPolyG4(poly_g4);

        setRGB0(poly_g4, 0x20, 0x20, 0x20);
        setRGB1(poly_g4, 0x20, 0x20, 0x20);
        setRGB2(poly_g4, 0x80, 0x80, 0x80);
        setRGB3(poly_g4, 0x80, 0x80, 0x80);

        temp_a2_2 = (arg0 * 150) - 139;

        setXY4(poly_g4,
               D_801E2B38[i].field_0.vx + temp_a2_2, D_801E2B38[i].field_0.vy - 60,
               D_801E2B38[i].field_4.vx + temp_a2_2, D_801E2B38[i].field_4.vy - 60,
               D_801E2B38[i].field_8.vx + temp_a2_2, D_801E2B38[i].field_8.vy - 60,
               D_801E2B38[i].field_C.vx + temp_a2_2, D_801E2B38[i].field_C.vy - 60);

        addPrim((u8*)ot->org + 0x20, poly_g4);
        GsOUT_PACKET_P = (u8*)poly_g4 + sizeof(POLY_G4);
    }

    poly_f4_3 = (POLY_F4*)GsOUT_PACKET_P;

    setlen(poly_f4_3, 5);
    setcode(poly_f4_3, 0x2A);
    setRGB0(poly_f4_3, 0x30, 0x30, 0x30);

    setXY4(poly_f4_3,
           arg0 * 150 - 139, -81,
           arg0 * 150 - 139, 37,
           arg0 * 150 - 9, -81,
           arg0 * 150 - 9, 37);

    addPrim((u8*)ot->org + 0x20, poly_f4_3);
    GsOUT_PACKET_P = (u8*)poly_f4_3 + sizeof(POLY_F4);

    func_80052088(0, 0, 8, 1);
}

void Gfx_SavesOutlineDraw(s_UnkSaveload0* arg0, s_UnkSaveload0* arg1, s32 arg2, s32 arg3) // 0x801E4D90
{
    GsOT* ot;
    u32   temp_s1  = arg0->field_7;
    s32   temp_s0  = arg0->field_6 + 1;
    s32   temp_s00 = arg1->field_6 + 1;
    s16   var_a2;
    s16   var_t0_3;
    s32   temp_t2;
    s32   temp_t3;
    s32   temp_t7;
    s32   i;
    s32   var_t8;

    s_801E2A98 D_801E2C30[] =
    {
        {{-131, -62}, {-11, -62}},
        {{-131, -43}, {-11, -43}},
        {{-131, -62}, {-131, -44}},
        {{-11, -62}, {-11, -44}}
    };

    s_primColor D_801E2C50[] =
    {
        {0x20, 0xA0, 0x20, 0x00},
        {0x60, 0xA0, 0x20, 0x00},
        {0xA0, 0xA0, 0x20, 0x00},
        {0xA0, 0x80, 0x20, 0x00},
        {0xA0, 0x60, 0x20, 0x00},
        {0xA0, 0x20, 0x20, 0x00},
        {0xA0, 0x20, 0x60, 0x00},
        {0xA0, 0x20, 0x80, 0x00},
        {0xA0, 0x20, 0xA0, 0x00},
        {0x80, 0x20, 0xA0, 0x00},
        {0x60, 0x20, 0xA0, 0x00},
        {0x20, 0x20, 0xA0, 0x00},
        {0x20, 0x40, 0xA0, 0x00},
        {0x20, 0x60, 0xA0, 0x00},
        {0x20, 0xA0, 0xA0, 0x00}
    };

    LINE_F2* line;
    TILE*    tile;

    ot      = &g_ObjectTable1[g_ObjectTableIdx];
    temp_t7 = arg2 - D_801E7570[arg3];

    var_t8 = temp_t7 ? (temp_s1 > 0) : 0;

    for (i = var_t8; i < 4; i++)
    {
        line = (LINE_F2*)GsOUT_PACKET_P;
        setLineF2(line);
        setRGB0(line, D_801E2C50[temp_s0 - 1].r, D_801E2C50[temp_s0 - 1].g, D_801E2C50[temp_s0 - 1].b);

        temp_t3 = arg3 * 150;
        temp_t2 = temp_t7 * 20;

        if (var_t8 == 0)
        {
            setXY2(line,
                   D_801E2C30[i].field_0.vx + temp_t3, D_801E2C30[i].field_0.vy + temp_t2,
                   D_801E2C30[i].field_4.vx + temp_t3, D_801E2C30[i].field_4.vy + temp_t2);
        }
        else
        {
            setXY2(line,
                   D_801E2C30[i].field_0.vx + temp_t3, (D_801E2C30[i].field_0.vy + temp_t2) - ((i + (s32)((u32)i >> 0x1F)) >> 1),
                   D_801E2C30[i].field_4.vx + temp_t3, D_801E2C30[i].field_4.vy + temp_t2);
        }

        addPrim((u8*)ot->org + 0x18, line);
        GsOUT_PACKET_P = (u8*)line + sizeof(LINE_F2);
    }

    if (temp_s1 == 0)
    {
        for (i = 0; i < 2; i++)
        {
            tile = (TILE*)GsOUT_PACKET_P;
            setTile(tile);

            setRGB0(tile, D_801E2C50[temp_s0 - 1].r, D_801E2C50[temp_s0 - 1].g, D_801E2C50[temp_s0 - 1].b);

            var_t0_3 = (arg3 * 150) - 131;
            setXY0(tile, var_t0_3 + 117 * i, ((temp_t7 * 20) - 62));
            setWH(tile, 4, 4);

            addPrim((u8*)ot->org + 0x18, tile);
            GsOUT_PACKET_P = (u8*)tile + sizeof(TILE);
        }
    }

    if (temp_s0 != temp_s00 || arg2 + 1 == g_SaveCount[arg3])
    {
        for (i = 0; i < 2; i += 1)
        {
            tile = (TILE*)GsOUT_PACKET_P;
            setTile(tile);

            setRGB0(tile, D_801E2C50[temp_s0 - 1].r, D_801E2C50[temp_s0 - 1].g, D_801E2C50[temp_s0 - 1].b);

            var_a2 = (arg3 * 150) - 131;
            setXY0(tile, var_a2 + 117 * i, ((temp_t7 * 20) - 46));
            setWH(tile, 4, 4);

            addPrim((u8*)ot->org + 0x18, tile);
            GsOUT_PACKET_P = (u8*)tile + sizeof(TILE);
        }
    }

    if (D_801E756C[arg3] != temp_s0)
    {
        D_801E756C[arg3] = temp_s0;
    }
}

void func_801E52D8(s32 arg0, s32 arg1) // 0x801E52D8
{
    s_801E2C8C D_801E2C8C[2] =
    {
        {
            {-142, -33},
            {136, 33},
            255,
            0,
            0,
            0,
        },
        {
            {-142, -33}, 
            {136, 33}, 
            0,
            255,
            0,
            0
        }
    };

    s_801E2CAC D_801E2CAC =
    {
        {
            {{-144, -36}, {-4, -36}},
            {{-144, 2}, {-4, 2}},
            {{-144, -36}, {-144, 2}},
            {{-4, -36}, {-4, 2}}
        }
    };

    s_801E2CCC D_801E2CCC =
    {
        {
            {{-144, -36}, {-148, -40}, {-4, -36}, {0, -40}},
            {{-144, 2}, {-148, 6}, {-4, 2}, {0, 6}},
            {{-144, -36}, {-148, -40}, {-144, 2}, {-148, 6}},
            {{-4, -36}, {0, -40}, {-4, 2}, {0, 6}}
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

void Gfx_RectMemLoadDraw(s_801E2CAC* arg0, s_801E2CCC* arg1, s_801E2C8C* arg2, s32 arg3) // 0x801E54DC
{
    GsOT*       ot;
    s32         i;
    s_801E2A98* temp;
    LINE_F2*    line;
    POLY_G4*    poly_g4;
    POLY_F4*    poly_f4;

    ot = &g_ObjectTable1[g_ObjectTableIdx];

    for (i = 0; i < 4; i++)
    {
        line = (LINE_F2*)GsOUT_PACKET_P;
        setLineF2(line);
        setRGB0(line, arg2->field_8, arg2->field_A, arg2->field_C);
        setXY2(line,
               arg0->field_0[i].field_0.vx + arg3 * 150, arg0->field_0[i].field_0.vy,
               arg0->field_0[i].field_4.vx + arg3 * 150, arg0->field_0[i].field_4.vy);
        addPrim((u8*)ot->org + 28, line);
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
               arg1->field_0[i].field_0.vx + (arg3 * 150), arg1->field_0[i].field_0.vy,
               arg1->field_0[i].field_4.vx + (arg3 * 150), arg1->field_0[i].field_4.vy,
               arg1->field_0[i].field_8.vx + (arg3 * 150), temp->field_0.vy,
               temp->field_4.vx + (arg3 * 150), temp->field_4.vy);

        addPrim((u8*)ot->org + 32, poly_g4);
        GsOUT_PACKET_P = (u8*)poly_g4 + sizeof(POLY_G4);
    }
    
    func_80052088(0, 0, 5, 1);
    
    poly_f4 = (POLY_F4*)GsOUT_PACKET_P;
    setlen(poly_f4, 5);
    setcode(poly_f4, 0x2A);
    setRGB0(poly_f4, 48, 48, 48);

    setXY4(poly_f4,
           arg2->field_0.vx + (arg3 * 150), arg2->field_0.vy,
           arg2->field_0.vx + (arg3 * 150), arg2->field_0.vy + arg2->field_4.vy,
           arg2->field_0.vx + arg2->field_4.vx + (arg3 * 150), arg2->field_0.vy,
           arg2->field_0.vx + arg2->field_4.vx + (arg3 * 150), arg2->field_0.vy + arg2->field_4.vy);

    addPrim((u8*)ot->org + 32, poly_f4);
    GsOUT_PACKET_P = (u8*)poly_f4 + sizeof(POLY_F4);

    func_80052088(0, 0, 8, 1);
}

void Gfx_RectSaveInfoDraw(s_801E2A98* arg0) // 0x801E5898
{
    GsOT*    ot;
    s32      color;
    s32      i;
    POLY_F3* poly_f3;
    POLY_F4* poly_f4;
    LINE_G2* line_g2;

    DVECTOR sp10[] =
    {
        {
            .vx = arg0->field_0.vx,
            .vy = arg0->field_0.vy
        },
        {
            .vx = (arg0->field_0.vx + arg0->field_4.vx) - 8,
            .vy = arg0->field_0.vy
        },
        {
            .vx = arg0->field_0.vx + arg0->field_4.vx,
            .vy = arg0->field_0.vy + 8},
        {
            .vx = arg0->field_0.vx + arg0->field_4.vx,
            .vy = arg0->field_0.vy + arg0->field_4.vy
        },
        {
            .vx = arg0->field_0.vx + 8,
            .vy = arg0->field_0.vy + arg0->field_4.vy
        },
        {
            .vx = arg0->field_0.vx,
            .vy = (arg0->field_0.vy + arg0->field_4.vy) - 8
        }
    };

    s_801E2B58 sp28[] =
    {
        {
            {
                .vx = arg0->field_0.vx + arg0->field_4.vx,
                .vy = arg0->field_0.vy
            },
            {
                .vx = (arg0->field_0.vx + arg0->field_4.vx) - 8,
                .vy = arg0->field_0.vy
            },
            {
                .vx = arg0->field_0.vx + arg0->field_4.vx,
                .vy = arg0->field_0.vy + 8
            },
        },
        {
            {
                .vx = arg0->field_0.vx,
                .vy = arg0->field_0.vy + arg0->field_4.vy
            },
            {
                .vx = arg0->field_0.vx + 8,
                .vy = arg0->field_0.vy + arg0->field_4.vy
            },
            {
                .vx = arg0->field_0.vx,
                .vy = (arg0->field_0.vy + arg0->field_4.vy) - 8
            }
        }
    };

    ot = &g_ObjectTable1[g_ObjectTableIdx];

    for (i = 0; i < 2; i++)
    {
        poly_f3 = (POLY_F3*)GsOUT_PACKET_P;
        setlen(poly_f3, 4);

        color = 0x30; // HACK

        setcode(poly_f3, 0x22);
        setRGB0(poly_f3, color, 0x30, 0x30);
        setXY3(poly_f3,
               sp28[i].field_0.vx, sp28[i].field_0.vy,
               sp28[i].field_4.vx, sp28[i].field_4.vy,
               sp28[i].field_8.vx, sp28[i].field_8.vy);
        addPrim((u8*)ot->org + 0x20, poly_f3);

        GsOUT_PACKET_P = (u8*)poly_f3;
        GsOUT_PACKET_P += sizeof(POLY_F3);
    }

    func_80052088(0, 0, 8, 2);

    poly_f4 = (POLY_F4*)GsOUT_PACKET_P;
    setlen(poly_f4, 5);
    setcode(poly_f4, 0x2A);
    setRGB0(poly_f4, 0x30, 0x30, 0x30);
    setXY4(poly_f4,
           arg0->field_0.vx, arg0->field_0.vy,
           arg0->field_0.vx, arg0->field_0.vy + arg0->field_4.vy,
           arg0->field_0.vx + arg0->field_4.vx, arg0->field_0.vy,
           arg0->field_0.vx + arg0->field_4.vx, arg0->field_0.vy + arg0->field_4.vy);
    addPrim((u8*)ot->org + 0x24, poly_f4);
    GsOUT_PACKET_P = (u8*)poly_f4 + sizeof(POLY_F4);

    func_80052088(0, 0, 9, 1);

    for (i = 0; i < 6; i++)
    {
        line_g2 = (LINE_G2*)GsOUT_PACKET_P;
        setLineG2(line_g2);

        if (i & 1)
        {
            setRGB0(line_g2, 0xA0, 0x80, 0x40);
            setRGB1(line_g2, 0xB0, 0xB0, 0xB0);
        }
        else
        {
            setRGB0(line_g2, 0xB0, 0xB0, 0xB0);
            setRGB1(line_g2, 0xA0, 0x80, 0x40);
        }

        setXY2(line_g2,
               sp10[i].vx, sp10[i].vy,
               sp10[(i + 1) % 6].vx,sp10[(i + 1) % 6].vy);

        addPrim((u8*)ot->org + 0x1C, line_g2);
        GsOUT_PACKET_P = (u8*)line_g2 + sizeof(LINE_G2);
    }
}

void Save_SaveDataInfoDraw(s32 arg0, s32 arg1) // 0x801E5E18
{
    char* D_801E2D70[] =
    {
        "Data",
        "Save",
        "Time",
        "hyper blaster",
        "power up",
        "You_need_1_free_block\n__to_create_a_new_file."
    };

    GsOT*           ot;
    s32             saveId;
    s32             mins;
    s32             hasFlag;
    s32             sec;
    s32             hours;
    s32             saveDataIdx;
    s32             i;
    s32             digitCount;
    s32             offset;
    u32             saveFlags;
    u32             flags;
    u32             timeInSec;
    s_UnkSaveload1* ptr;
    POLY_G4*        poly;

    ot = &g_ObjectTable1[g_ObjectTableIdx];

    D_800BCD2C = (s_UnkSaveload0*)&BOOT_ADDR_0[arg0 * 0xA50];

    if (D_800BCD2C[arg1].field_4 == 10)
    {
        Gfx_StringSetColor(ColorId_White);
        Gfx_StringSetPosition(66, 178);
        Gfx_StringDraw("You_need_1_free_block\n__to_create_a_new_file.", 0x32);
    }
    else if (D_800BCD2C[arg1].field_4 == 8)
    {
        saveId      = D_800BCD2C[arg1].field_2;     // Game's savegame counter.
        saveDataIdx = D_800BCD2C[arg1].field_7 + 1; // Savegame data index.

        saveId = CLAMP(saveId, 0, 999);

        ptr = D_800BCD2C[arg1].field_C;

        timeInSec = FP_FROM(ptr->gameplayTimer_4, Q12_SHIFT);

        offset = ptr->add290Hours_B_1;
        hours  = (timeInSec / 3600) + offset * 290;

        flags = ptr->hyperBlasterFlags_B_3;

        mins = (timeInSec / 60) % 60;
        sec = timeInSec % 60;

        Gfx_StringSetColor(ColorId_White);
        Gfx_StringSetPosition(40, 178);
        Gfx_StringDraw("Data", 5);

        digitCount = saveDataIdx < 10;

        Gfx_StringSetPosition(digitCount * 5 + 92, 178);
        Gfx_StringDrawInt(2, saveDataIdx);

        Gfx_StringSetPosition(40, 196);
        Gfx_StringDraw("Save", 5);

        digitCount = saveId < 10;

        Gfx_StringSetPosition(digitCount * 5 + 92, 196);
        Gfx_StringDrawInt(2, saveId);

        Gfx_StringSetPosition(128, 178);
        Gfx_StringDraw("Time", 5);

        digitCount = 0;
        if (hours < 100)
        {
            if (hours >= 10)
            {
                digitCount = 1;
            }
            else
            {
                digitCount = 2;
            }
        }

        Gfx_StringSetPosition((digitCount * 10) + 176, 178);
        Gfx_StringDrawInt(3, hours);
        Gfx_StringDraw("_:_", 3);

        digitCount = mins < 10;

        Gfx_StringSetPosition(digitCount * 10 + 220, 178);
        Gfx_StringDrawInt(2, mins);
        Gfx_StringDraw("_:_", 3);

        digitCount = sec < 10;

        Gfx_StringSetPosition(digitCount * 10 + 254, 178);
        Gfx_StringDrawInt(2, sec);

        if (!(flags & 0x18))
        {
            return;
        }

        Gfx_DebugStringPosition(152, 194);
        Gfx_DebugStringDraw("hyper blaster");
        Gfx_DebugStringPosition(172, 202);
        Gfx_DebugStringDraw("power up");

        for (i = 0; i < 2; i++)
        {
            poly = (POLY_G4*)GsOUT_PACKET_P;
            setlen(poly, 8);
            setcode(poly, 0x3A);

            hasFlag = (flags & 0x10);

            if (i != 0)
            {
                setRGB0(poly, (hasFlag > 0) ? 0 : 0xFF, 0xFF, 0);
                setRGB2(poly, (hasFlag > 0) ? 0 : 0xFF, 0xFF, 0);
                setRGB1(poly, 0, 0, 0);
                setRGB3(poly, 0, 0, 0);
                setXY4(poly, -30, 89, -30, 93, 120, 89, 120, 93);
            }
            else
            {
                setRGB0(poly, 0, 0, 0);
                setRGB2(poly, 0, 0, 0);
                setRGB1(poly, (hasFlag > 0) ? 0 : 0xFF, 0xFF, 0);
                setRGB3(poly, (hasFlag > 0) ? 0 : 0xFF, 0xFF, 0);
                setXY4(poly, -30, 85, -30, 89, 120, 85, 120, 89);
            }

            GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G4);
            addPrim((u8*)ot->org + 28, poly);

            func_80052088(0, 0, 7, 1);
        }
    }
}

void GameState_SaveScreen_Update() // 0x801E6320
{
    g_DisplaySaveDataInfo = 1;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        D_801E7524[0]();
    }

    D_801E7524[g_GameWork.gameStateStep_598[0]]();

    Gfx_SaveBackground();
    Gfx_MemCardState();
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

    g_MemCardStateTextTimer = 0;
    D_800A97D8 = g_GameWork.gameState_594 == GameState_Unk10;

    func_801E2D8C();

    g_SysWork.timer_20 = 0;
    g_GameWork.gameStateStep_598[0]++;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;
}

/**
* Crucial for working with the overlay.
* If `g_GameWork.gameStateStep_598[1]` comply any of the conditionals this happen:
* 0 - The user can fully move through the save menu.
* 1 - This triggers the overwrite save, even when the player is selecting a new save.
* 2 - Unknown, presumably it is used when the player leaves the save screen.
*/
void func_801E649C() // 0x801E649C
{
    s32             step = g_GameWork.gameStateStep_598[1];
    s_UnkSaveload0* ptr;

    switch (step) 
    {
        case 0:
            if (func_80033548() == 0) 
            {
                break;
            }

            if (D_800BCD30[0] != 0 && D_800BCD30[1] != 0 && 
                (g_ControllerPtrConst->btns_new_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))) 
            {
                D_800A97D6 ^= 1;
                Sd_EngineCmd(0x519);
            }

            if (D_800BCD3A > 0) 
            {
                D_801E753C = 0;
                D_801E7540 = 0;
                D_800BCD2C = (s_UnkSaveload0*)((D_800A97D6 * 0xA50) + BOOT_ADDR_0);

                if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickUp) 
                {
                    if (D_800A97D4[D_800A97D6] != 0) 
                    {
                        D_800A97D4[D_800A97D6]--;
                        Sd_EngineCmd(0x519);
                    }
                }

                if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickDown) 
                {
                    if (D_800A97D4[D_800A97D6] < D_800BCD30[D_800A97D6] - 1)
                    {
                        D_800A97D4[D_800A97D6]++;
                        Sd_EngineCmd(0x519);
                    }
                }

                ptr        = &D_800BCD2C[D_800A97D4[D_800A97D6]];
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

                    if ((u16)(ptr->field_0 - 1) < 0x797B)
                    {
                        D_801E7540 = 1;
                    }
                }

                if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter) 
                {
                    if ((D_801E753C | D_801E7540) != 0) 
                    {
                        D_801E755C                       = 0;
                        g_GameWork.gameStateStep_598[2]  = 0;
                        g_GameWork.gameStateStep_598[1] += 1;
                    }
                    else
                    {
                        g_SysWork.timer_20               = 0;
                        g_GameWork.gameStateStep_598[1]  = 0;
                        g_GameWork.gameStateStep_598[2]  = 0;
                        g_GameWork.gameStateStep_598[0] += D_800BCD38;
                    }
                    Sd_EngineCmd(0x51B);
                }
            }

            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel) 
            {
                D_800BCD0C                      = 3;
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

            g_MemCardStateTextTimer = 0;

            if (g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickLeft) 
            {
                D_801E755C = step;
                Sd_EngineCmd(0x519);
            }

            if (g_ControllerPtrConst->btns_new_10 & ControllerFlag_LStickRight) 
            {
                D_801E755C = 0;
                Sd_EngineCmd(0x519);
            }

            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter) 
            {
                if (D_801E755C == 0) 
                {
                    g_GameWork.gameStateStep_598[0] = step;
                    g_SysWork.timer_20              = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
                else
                {
                    g_SysWork.timer_20              = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    g_GameWork.gameStateStep_598[0] = D_801E7540 + 2;
                }
                Sd_EngineCmd(0x51B);
            }

            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel) 
            {
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                Sd_EngineCmd(0x51A);
            }

            Gfx_OverwriteSave(D_801E753C, D_801E755C);
            break;
        
        case 2:
            if ((D_800BCD0C & 0x7) == 5)
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

void func_801E69E8() // 0x801E69E8
{
    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            g_MemCardState                  = 1;
            g_MemCardStateTextTimer         = 30;
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
                    g_MemCardStateTextTimer         = 30;
                    g_GameWork.gameStateStep_598[0] = 1;
                    g_SysWork.timer_20              = 0;
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

void func_801E6B18() // 0x801E6B18
{
    s_UnkSaveload1* ptr;

    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            g_MemCardState = 2;
            ptr            = func_8002E9EC(D_800BCD40, D_800BCD3F, D_800BCD3E);

            if (g_SavegamePtr->mapEventIdx_A8 == 24)
            {
                ptr->savegameCount_8 = 0;
            }
            else
            {
                g_SavegamePtr->savegameCount_A6++;
                ptr->savegameCount_8 = g_SavegamePtr->savegameCount_A6;
            }

            ptr->mapEventIdx_A   = g_SavegamePtr->mapEventIdx_A8;
            ptr->gameplayTimer_4 = g_SavegamePtr->gameplayTimer_250;

            D_801E76D5 = ptr->isTitleYellowFlag_B_0;

            ptr->isTitleYellowFlag_B_0 = g_SavegamePtr->isTitleYellowFlag_25C_0;
            ptr->add290Hours_B_1       = g_SavegamePtr->add290Hours_25C_1;
            ptr->hyperBlasterFlags_B_3 = g_SavegamePtr->hyperBlasterFlags_25C_3;

            func_8002E94C(5, D_800BCD40, D_800BCD3F, D_800BCD3E);
            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;

        case 1:
            switch (func_8002E990())
            {
                default:
                    g_GameWork.gameStateStep_598[0] = 1;
                    g_SysWork.timer_20              = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;

                case 1:
                    g_MemCardStateTextTimer = 30;
                    break;

                case 11:
                    func_8002E94C(3, D_800BCD40, D_800BCD3F, 0);
                    g_GameWork.gameStateStep_598[1]++;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;
            }
            break;

        case 2:
            switch (func_8002E990())
            {
                case 1:
                    g_MemCardStateTextTimer = 30;
                    break;

                case 11:
                    g_GameWork.savegame_90 = g_GameWork.savegame_30C;

                default:
                    g_GameWork.gameStateStep_598[0] = 1;
                    g_SysWork.timer_20              = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;
            }
            break;

        default:
            break;
    }
}

void func_801E6DB0() // 0x801E6DB0
{
    s32 var0;
    s32 var1;

    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            g_MemCardState = 3;

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

            g_MemCardStateTextTimer = 30;
            break;

        case 2:
            var1 = func_8002E990();
            if (var1 == 1)
            {
                g_MemCardStateTextTimer = 30;
                break;
            }

            if (var1 != 11)
            {
                D_800BCD39 = 1;
                g_GameWork.gameStateStep_598[0] = 1;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                break;
            }

            g_MemCardStateTextTimer = 300;
            g_SysWork.timer_20      = 0;
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
            g_GameWork.savegame_90 = g_GameWork.savegame_30C;

            func_80035178();
            
            g_SysWork.flags_2298 = 8;

            GameFs_MapLoad(g_SavegamePtr->mapOverlayIdx_A4);

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

// Handles the logic for the drawing of all the information related to saves and the slots
// Gfx_SaveScreenDrawUpdate
void func_801E70C8() // 0x801E70C8
{
    s_UnkSaveload0* ptr;
    s32             i;
    s32             j;

    for (i = 0; i < MEMORY_CARD_SLOT_COUNT; i++)
    {
        D_800BCD2C = (s_UnkSaveload0*)&BOOT_ADDR_0[2640 * i];

        for (j = 0; j < (s32)g_SaveCount[i]; j++)
        {
            if (D_800BCD2C->field_0 >= 0)
            {
                Gfx_SaveFileSelectedDraw(j, i, D_800BCD2C->field_6 + 1, D_800BCD2C->field_4);
            }

            func_801E3304(D_800BCD2C, j, i);

            if (D_800BCD2C->field_4 >= 7)
            {
                ptr = D_800BCD2C;
                if (j != g_SaveCount[i])
                {
                    ptr++;
                }

                func_801E326C(D_800BCD2C, ptr, j, i);
            }

            if (D_800BCD2C->field_4 == 8)
            {
                func_801E30C4(D_800BCD2C, j, i);
            }

            D_800BCD2C++;
        }

        if (g_GameWork.gameState_594 == GameState_DeathLoadScreen)
        {
            Gfx_SaveSelectedDisplacement(i, D_800BCD28);
        }
        else
        {
            Gfx_SaveSelectedDisplacement(i, D_800BCD3A);
        }
    }
}

void Gfx_MemCardState() // 0x801E7244
{
    if (g_MemCardStateTextTimer <= 0)
    {
        return;
    }

    g_DisplaySaveDataInfo = 0;
    g_MemCardStateTextTimer--;

    switch (g_MemCardState)
    {
        case 1: // Format.
            Gfx_MemCardStateDraw(g_MemCardState, (D_800BCD34 >> (D_800BCD40 * 3)) & 0x7);
            break;

        case 2: // Save.
        case 3: // Load.
            Gfx_MemCardStateDraw(g_MemCardState, func_8002E990());
            break;
    }
}

void Gfx_OverwriteSave(s32 arg0, s32 arg1) // 0x801E72DC
{
    Gfx_OverwriteSaveDraw(arg0, arg1);
}

void GameState_DeathLoadScreen_Update() // 0x801E72FC
{
    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        D_801E7544[0]();
    }

    D_801E7544[g_GameWork.gameStateStep_598[0]]();

    Gfx_SaveBackground();
    Gfx_MemCardState();
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

    D_800BCD2C = (s_UnkSaveload0*)&BOOT_ADDR_0[D_800A97D6 * 2640];
    D_800BCD2C = &D_800BCD2C[D_800A97D4[D_800A97D6]];
    D_800BCD40 = D_800BCD2C->field_5;
    D_800BCD3F = D_800BCD2C->field_6;
    D_800BCD3E = D_800BCD2C->field_7;

    g_GameWork.gameStateStep_598[0]++;
    g_SysWork.timer_20              = 0;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;
}
