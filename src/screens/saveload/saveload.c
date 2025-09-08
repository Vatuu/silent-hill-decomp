#include "game.h"

#include <libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/memcard.h"
#include "bodyprog/math.h"
#include "bodyprog/gfx/text_draw.h"

#define SAVE_FLASH_TIMER_MAX 40
#define SLOT_COLUMN_OFFSET   150
#define SLOT_ROW_OFFSET      20

const s32 pad = 0;

char* g_SaveLocationNames[] =
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

// Some kind of state. 0 or 1.
s32 D_801E7510 = 0;

/** `bool`s */
s16 D_801E7514[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s16 g_LoadingMemCardTimer[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s32 g_MemCardState = MemCardState_None;

s32 g_MemCardStateTextTimer = 0;

// Only used in `GameState_SaveScreen_Update`.
void (*g_GameState_SaveScreen_Funcs[])() =
{
    Savegame_ScreenInit,
    Savegame_ScreenLogic,
    Savegame_FormatLogic,
    Savegame_SaveLogic,
    Savegame_LoadLogic,
    Savegame_ContinueLogic
};

s32 g_SaveWriteOption = 0;

s32 g_IsSaveSelected = 0;

// Only used in `GameState_DeathLoadScreen_Update`.
void (*g_GameState_DeathLoadScreen_Funcs[])() =
{
    Savegame_ScreenInit,
    func_801E737C,
    Savegame_LoadLogic,
    Savegame_ContinueLogic
};

s32 D_801E7554 = 0;

s32 D_801E7558 = 0;

s32 g_SaveWriteOptionSelected = 0;

s32 D_801E7560 = 0; // Unused.

/** Some boolean statuses for each save slot. */
s32 D_801E7564[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s16 D_801E756C[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s16 g_HiddenElementsByDisplacement[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s16 D_801E7574[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s16 g_Gfx_SelectedSaveOffsetsY[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s8 D_801E757C[8] = {}; // Unused data - Splat gets confused and merges it with the previous data (`g_Gfx_SelectedSaveOffsetsY`).

/*
s8 D_801E7584[SAVEGAME_COUNT_MAX * MEMORY_CARD_SLOT_COUNT] = { };

s8 g_LastSaveIdx[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s8 g_DisplaySaveDataInfo = 0;

//s8 D_801E76D1 = 0; // Unused.

s8 g_IsMemCardNotInserted[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };

s8 g_Gfx_SaveFlashTimer = 0;

u8 g_IsNextFearMode = 0;

u8 g_IsGameSaving = 0;
*/

void Savegame_ScreenSubInit() // 0x801E2D8C
{
    s32 i;
    s32 j;

    func_80037124();

    D_801E750C           = 0;
    D_801E7510           = 0;
    g_Gfx_SaveFlashTimer = SAVE_FLASH_TIMER_MAX;
    g_IsGameSaving       = 0;

    for (i = 0; i < MEMORY_CARD_SLOT_COUNT; i++)
    {
        g_IsMemCardNotInserted[i]         = 1;
        g_LastSaveIdx[i]                  = NO_VALUE;
        D_801E7564[i]                     = 0;
        D_801E756C[i]                     = 0;
        g_HiddenElementsByDisplacement[i] = NO_VALUE;
        D_801E7574[i]                     = NO_VALUE;
        g_Gfx_SelectedSaveOffsetsY[i]     = 0;
        D_801E7514[i]                     = 1;
        g_LoadingMemCardTimer[i]          = 0;

        for (j = 0; j < SAVEGAME_COUNT_MAX; j++)
        {
            D_801E7584[j + (SAVEGAME_COUNT_MAX * i)] = 0;
        }

        g_DisplaySaveDataInfo = 1;
    }
}

void Gfx_SaveScreenBaseDraw() // 0x801E2EBC
{
    s_Line2d line;
    s32      i;
    
    DVECTOR slotStrPosTable[] = 
    {
        { 59, 16 },
        { 209, 16 }
    };

    char* slotStrs[] =
    {
        "SLOT1",
        "SLOT2"
    };

    Gfx_StringSetColor(ColorId_White);
    
    for (i = 0; i < MEMORY_CARD_SLOT_COUNT; i++)
    {
        Gfx_StringSetPosition(slotStrPosTable[i].vx, slotStrPosTable[i].vy);
        Gfx_StringDraw(slotStrs[i], 50);
    }

    line.vertex0_0.vx = -136;
    line.vertex0_0.vy = 60;
    line.vertex1_4.vx = 272;
    line.vertex1_4.vy = 40;
    Gfx_RectSaveInfoDraw(&line);
}

void Gfx_SaveSelectedDisplacement(s32 slotIdx, s32 unusedSaveCount) // 0x801E2F90
{
    g_Gfx_SelectedSaveOffsetsY[slotIdx] = g_SlotElementSelectedIdx[slotIdx] - g_HiddenElementsByDisplacement[slotIdx];
}

void Gfx_SaveSlotFileStringDraw(s32 saveIdx, s32 slotIdx, s32 fileId, s32 entryType) // 0x801E2FCC
{
    #define OFFSET_X             SCREEN_POSITION_X(47.0f)
    #define FILE_STR_MARGIN_X    SCREEN_POSITION_X(10.0f)
    #define FILE_ID_STR_MARGIN_X FILE_STR_MARGIN_X + SCREEN_POSITION_X(15.75f)
    #define POS_Y                SCREEN_POSITION_Y(14.75f)

    char* fileStr = "FILE";

    if (saveIdx == g_SlotElementSelectedIdx[slotIdx] && entryType >= SavegameEntryType_OutOfBlocks)
    {
        Gfx_StringSetColor(ColorId_White);

        // Draw "FILE" string.
        Gfx_StringSetPosition((slotIdx * OFFSET_X) + FILE_STR_MARGIN_X, POS_Y);
        Gfx_StringDraw(fileStr, 50);

        // Draw file ID string.
        Gfx_StringSetPosition((slotIdx * OFFSET_X) + FILE_ID_STR_MARGIN_X, POS_Y);
        Gfx_StringDrawInt(1, fileId);
    }
}

bool Gfx_SavegameEntryStringColorSet(s_SavegameMetadata* saveEntry) // 0x801E3078
{
    if (saveEntry != NULL && saveEntry->isNextFearMode_B)
    {
        Gfx_StringSetColor(ColorId_Gold);
        return true;
    }

    Gfx_StringSetColor(ColorId_White);
    return false;
}

void Gfx_SavegameEntryLocationNameDraw(s_SavegameEntry* saveEntry, s32 saveIdx, s32 slotIdx) // 0x801E30C4
{
    #define OFFSET_X SCREEN_POSITION_X(47.0f)
    #define MARGIN_X SCREEN_POSITION_X(28.25f)
    #define OFFSET_Y SCREEN_POSITION_Y(8.5f)
    #define MARGIN_Y SCREEN_POSITION_Y(22.25f)

    s32 nameIdx = saveEntry->locationId_8;

    u8 xOffsets[] =
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

    var1 = g_HiddenElementsByDisplacement[slotIdx];

    if (saveIdx >= var1 && (var1 + 4) >= saveIdx)
    {
        var0 = saveIdx - var1;

        Gfx_SavegameEntryStringColorSet(saveEntry->field_C);

        if (g_IsGameSaving != 0 && g_SelectedSaveSlotIdx == slotIdx && g_SlotElementSelectedIdx[slotIdx] == saveIdx)
        {
            if (g_IsNextFearMode != 0)
            {
                colorId = ColorId_Gold;
            }
            else
            {
                colorId = ColorId_White;
            }
            Gfx_StringSetColor(colorId);
        }

        Gfx_StringSetPosition(((slotIdx * OFFSET_X) + MARGIN_X) - (xOffsets[nameIdx] / 2),
                              (var0 * OFFSET_Y) + MARGIN_Y);
        Gfx_StringDraw(g_SaveLocationNames[nameIdx], 50);
    }
}

void Gfx_SaveEntryBorder(s_SavegameEntry* saveEntry, s_SavegameEntry* nextSaveEntry, s32 saveIdx, s32 slotIdx) // 0x801E326C
{
    if (saveIdx == 0)
    {
        D_801E756C[slotIdx] = 0;
    }

    if (saveIdx < g_HiddenElementsByDisplacement[slotIdx] || (g_HiddenElementsByDisplacement[slotIdx] + 4) < saveIdx)
    {
        if (D_801E756C[slotIdx] != saveEntry->fileIdx_6)
        {
            D_801E756C[slotIdx] = saveEntry->fileIdx_6;
        }
    }
    else
    {
        Gfx_SaveEntryBorderDraw(saveEntry, nextSaveEntry, saveIdx, slotIdx);
    }
}

void Gfx_SaveScreenDraw(s_SavegameEntry* saveEntry, s32 saveIdx, s32 slotIdx) // 0x801E3304
{
    char* statusStrs[11] =
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
    s32 entryType;

    entryType = saveEntry->type_4;

    if (g_SelectedSaveSlotIdx == slotIdx && saveIdx == 0 && entryType >= SavegameEntryType_CorruptedSave)
    {
        Gfx_SaveSlotBorderDraw();
    }

    if (saveIdx == 0)
    {
        Gfx_SavedFlashDraw();

        g_Gfx_SaveFlashTimer++;
        g_Gfx_SaveFlashTimer = CLAMP(g_Gfx_SaveFlashTimer, 0, SAVE_FLASH_TIMER_MAX);

        if (entryType != SavegameEntryType_LoadMemCard)
        {
            g_LoadingMemCardTimer[slotIdx] = 0;
        }

        if (g_HiddenElementsByDisplacement[slotIdx] == NO_VALUE)
        {
            g_HiddenElementsByDisplacement[slotIdx] = 0;
        }

        if ((u8)g_IsMemCardNotInserted[slotIdx] != 0)
        {
            if (g_SlotElementSelectedIdx[slotIdx] == (g_SlotElementCount[slotIdx] - 2))
            {
                g_HiddenElementsByDisplacement[slotIdx] = g_SlotElementSelectedIdx[slotIdx] - 3;
            }
            else
            {
                g_HiddenElementsByDisplacement[slotIdx] = g_SlotElementSelectedIdx[slotIdx] - 2;
            }
        }

        if (g_SlotElementCount[slotIdx] < 6 || g_SlotElementSelectedIdx[slotIdx] == 0)
        {
            g_HiddenElementsByDisplacement[slotIdx] = 0;
        }
        else
        {
            if ((g_SlotElementCount[slotIdx] - 2) < g_SlotElementSelectedIdx[slotIdx])
            {
                g_HiddenElementsByDisplacement[slotIdx] = g_SlotElementCount[slotIdx] - 5;
            }
            else
            {
                while ((g_SlotElementSelectedIdx[slotIdx] - g_HiddenElementsByDisplacement[slotIdx]) >= 4)
                {
                    g_HiddenElementsByDisplacement[slotIdx]++;
                }

                while ((g_SlotElementSelectedIdx[slotIdx] - 1) < g_HiddenElementsByDisplacement[slotIdx])
                {
                    g_HiddenElementsByDisplacement[slotIdx]--;
                }
            }
        }

        if (g_HiddenElementsByDisplacement[slotIdx] != D_801E7574[slotIdx])
        {
            D_801E7514[slotIdx] = 1;
        }
    }

    switch (entryType)
    {
        case SavegameEntryType_UnformattedMemCard:
            g_IsMemCardNotInserted[slotIdx] = 0;

            if (g_GameWork.gameState_594 == GameState_Unk10)
            {
                Gfx_SaveSlotMemCardMsgBoxShineDraw(slotIdx);
            }

            break;

        case SavegameEntryType_LoadMemCard:
            g_IsMemCardNotInserted[slotIdx] = 1;

            for (i = 0; i < SAVEGAME_COUNT_MAX; i++)
            {
                D_801E7584[i + (slotIdx * SAVEGAME_COUNT_MAX)] = 0;
            }

            g_HiddenElementsByDisplacement[slotIdx] = NO_VALUE;
            break;

        case SavegameEntryType_CorruptedSave:
        case SavegameEntryType_Save:
        case SavegameEntryType_NewSave:
        case SavegameEntryType_NewFile:
            g_IsMemCardNotInserted[slotIdx] = 0;

            if (saveIdx == 0)
            {
                Gfx_SaveSlotBoxDraw(slotIdx, g_SlotElementCount[slotIdx], g_SlotElementSelectedIdx[slotIdx], g_Gfx_SelectedSaveOffsetsY[slotIdx]);
            }
            break;
    }

    if (saveIdx < g_HiddenElementsByDisplacement[slotIdx] || ((g_HiddenElementsByDisplacement[slotIdx] + 4) < saveIdx))
    {
        return;
    }

    D_801E7514[slotIdx] = 1;
    Gfx_StringSetColor(ColorId_White);

    // Draw memory card message string.
    switch (entryType)
    {
        case SavegameEntryType_NoMemCard:
        case SavegameEntryType_UnformattedMemCard:
        case SavegameEntryType_CorruptedMemCard:
        case SavegameEntryType_LoadMemCard:
            Gfx_StringSetPosition((slotIdx * SLOT_COLUMN_OFFSET) + 22, 82);
            break;

        case SavegameEntryType_NoDataInMemCard:
        case SavegameEntryType_Unk6:
            Gfx_StringSetPosition((slotIdx * SLOT_COLUMN_OFFSET) + 38, 90);
            break;

        case SavegameEntryType_OutOfBlocks:
            Gfx_StringSetPosition((slotIdx * SLOT_COLUMN_OFFSET) + 32, 90);
            break;

        default:
            Gfx_StringSetPosition((slotIdx * SLOT_COLUMN_OFFSET) + 6, (g_LoadingMemCardTimer[slotIdx] * 20) + 53);
            break;
    }
    Gfx_StringDraw(statusStrs[entryType], 50);

    // Draw memory card message box.
    if (entryType < SavegameEntryType_CorruptedSave)
    {
        Gfx_SaveSlotMemCardMsgBoxDraw(slotIdx, entryType);
    }

    // Update memory card load timer.
    g_LoadingMemCardTimer[slotIdx]++;
    if (g_LoadingMemCardTimer[slotIdx] == 5 || saveIdx == (g_SlotElementCount[slotIdx] - 1))
    {
        if (D_801E7564[slotIdx] == 0)
        {
            D_801E7564[slotIdx] = 1;
        }
        D_801E7514[slotIdx] = 0;

        if (entryType != SavegameEntryType_LoadMemCard)
        {
            g_LoadingMemCardTimer[slotIdx] = 0;
        }
    }
}

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
        0,   268,
        141, 107,
        223, 136,
        119, 182,
        170, 117,
        143, 114
    };

    switch (memCardState)
    {
        case MemCardState_Format:
            strIdx = (arg1 == memCardState) ? 1 : 2;
            break;

        case MemCardState_Save:
            switch (arg1)
            {
                case CardResult_NotConnected:
                    strIdx = 1; 
                    break;

                case CardResult_Success:
                    strIdx = 3; 
                    break;

                case CardResult_FileCreateError:
                    strIdx = 4;
                    break;

                case CardResult_FileIoComplete:
                    strIdx = 5; 
                    break;

                case CardResult_FileIoError:
                    strIdx = 6; 
                    break;

                default:
                    strIdx = 0; 
                    break;
            }
            break;

        case MemCardState_Load:
            switch (arg1)
            {
                // Now loading.
                case CardResult_Success:
                    strIdx = 11;
                    break;

                case CardResult_DamagedData:
                    strIdx = 8;
                    break;

                case CardResult_FileIoError:
                    strIdx = 9;
                    break;

                case CardResult_FileIoComplete:
                    strIdx = 10;
                    break;

                case CardResult_NotConnected:
                    strIdx = 1;
                    break;

                case CardResult_Full:
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
                g_GameWork.gameStateStep_598[2]                       = 0;
                g_HiddenElementsByDisplacement[g_SelectedSaveSlotIdx] = NO_VALUE;
                g_Gfx_SelectedSaveOffsetsY[g_SelectedSaveSlotIdx]     = NO_VALUE;
            }

            D_801E7554 = strIdx;
            D_801E7510++;
            
        case 1:
            if (memCardState == MemCardState_Save && arg1 == 1)
            {
                g_IsGameSaving = arg1;
            }

            // Finished saving and `D_801E7554` isn't required string.
            if (strIdx == 5 && D_801E7554 != strIdx)
            {
                g_LastSaveIdx[g_SelectedSaveSlotIdx]     = g_SlotElementSelectedIdx[g_SelectedSaveSlotIdx];
                g_LastSaveIdx[1 - g_SelectedSaveSlotIdx] = NO_VALUE;
                g_Gfx_SaveFlashTimer = 0;
            }

            D_801E7554 = strIdx;
            Gfx_StringSetPosition(160 - (xOffsets[strIdx] >> 1), 186);
            Gfx_StringDraw(strs[strIdx], 99);

            // Finished saving.
            if (strIdx == 5)
            {
                g_IsGameSaving = 0;
            }
            break;
    }
}

void Gfx_WriteOptionSaveDraw(s32 arg0, s32 optionIdx) // 0x801E3C44
{
    GsOT*     ot;
    s8        color;
    u32       time;
    POLY_F4*  poly;

    char* strs[] =
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
            Gfx_StringDraw(strs[arg0], 99);
            Gfx_StringSetPosition(104, 196);
            Gfx_StringDraw("\x07Yes__________No", 99);

            poly = (POLY_F4*)GsOUT_PACKET_P;
            setPolyF4(poly);
            setSemiTrans(poly, 1);

            if (time < 32)
            {
                color = (time * 2) + FP_COLOR(0.125f);
                setRGB0(poly, color, color, 32);
            }
            else
            {
                color = FP_COLOR(0.375f) - ((time - 32) * 2);
                setRGB0(poly, color, color, FP_COLOR(0.125f));
            }

            if (optionIdx != 0)
            {
                setXY4(poly, -66, 82, -66, 98, -18, 82, -18, 98);
            }
            else
            {
                setXY4(poly, 18, 82, 18, 98, 66, 82, 66, 98);
            }

            GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_F4);
            addPrim((u8*)ot->org + 28, poly);

            Gfx_Primitive2dTextureSet(0, 0, 7, 1);
            break;
    }
}

void Gfx_SavedFlashDraw() // 0x801E3E78
{
    GsOT*    ot;
    s32      slotIdx;
    s32      sin;
    s8       color;
    u32      rowIdx;
    POLY_F4* poly;

    ot      = &g_ObjectTable1[g_ObjectTableIdx];
    slotIdx = ~g_LastSaveIdx[0] == 0;
    rowIdx = g_LastSaveIdx[slotIdx] - g_HiddenElementsByDisplacement[slotIdx];

    if (rowIdx < 5)
    {
        sin  = Math_Sin((g_Gfx_SaveFlashTimer << 10) / SAVE_FLASH_TIMER_MAX);
        poly = (POLY_F4*)GsOUT_PACKET_P;
        setPolyF4(poly);
        setSemiTrans(poly, 1);

        color = ~FP_FROM(sin * FP_COLOR(1.0f), Q12_SHIFT);
        setRGB0(poly, color, color, color);

        setXY4(poly,
               (slotIdx * SLOT_COLUMN_OFFSET) - 130, (rowIdx * SLOT_ROW_OFFSET) - 62,
               (slotIdx * SLOT_COLUMN_OFFSET) - 130, (rowIdx * SLOT_ROW_OFFSET) - 43,
               (slotIdx * SLOT_COLUMN_OFFSET) - 11,  (rowIdx * SLOT_ROW_OFFSET) - 62,
               (slotIdx * SLOT_COLUMN_OFFSET) - 11,  (rowIdx * SLOT_ROW_OFFSET) - 43);

        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_F4);
        addPrim((u8*)ot->org + 24, poly);

        Gfx_Primitive2dTextureSet(0, 0, 6, 1);
    }
}

void Gfx_SaveSlotBorderDraw() // 0x801E4010
{
    #define BORDER_LINE_COUNT  5
    #define BORDER_PIXEL_WIDTH 2
    #define LAYER              28

    GsOT*    ot;
    LINE_F2* borderLine;
    POLY_G4* glowPoly;
    s32      i;
    s32      j;

    // Lines for green border around slot. Each line is doubled for 2-pixel width.
    s_Line2d borderLines[BORDER_LINE_COUNT][BORDER_PIXEL_WIDTH] =
    {
        // Top-left.
        {
            { { -107, -88 }, { -146, -88 } },
            { { -107, -87 }, { -146, -87 } }
        },
        // Top-right.
        {
            { { -42, -88 }, { -2, -88 } },
            { { -42, -87 }, { -2, -87 } }
        },
        // Left.
        {
            { { -146, -88 }, { -146, 42 } },
            { { -145, -87 }, { -145, 41 } }
        },
        // Right.
        {
            { { -2, -88 }, { -2, 42 } },
            { { -3, -87 }, { -3, 41 } }
        },
        // Bottom.
        {
            { { -146, 42 }, { -2, 42 } },
            { { -145, 41 }, { -3, 41 } }
        }
    };

    // Polygons for green glow of border around slot. Each line has 2 quads for inner and outer glow.
    s_Quad2d borderGlowQuads[BORDER_LINE_COUNT][BORDER_PIXEL_WIDTH] =
    {
        // Top-left.
        {
            { { -106, -88 }, { -106, -92 }, { -146, -88 }, { -150, -92 } },
            { { -106, -87 }, { -106, -83 }, { -146, -87 }, { -142, -83 } }
        },
        // Top-right.
        {
            { { -42, -88 }, { -42, -92 }, { -2, -88 }, { 2, -92 } },
            { { -42, -87 }, { -42, -83 }, { -2, -87 }, { -6, -83 } }
        },
        // Left.
        {
            { { -146, -88 }, { -150, -92 }, { -146, 42 }, {-150, 46 } },
            { { -145, -87 }, { -141, -83 }, { -145, 41 }, {-141, 37 } }
        },
        // Right.
        {
            { { -2, -88 }, { 2, -92 }, { -2, 42 }, { 2, 46 } },
            { { -3, -87 }, { -7, -83 }, { -3, 41 }, { -7, 37 } }
        },
        // Bottom.
        {
            { { -146, 42 }, { -150, 46 }, { -2, 42 }, { 2, 46 } },
            { { -145, 41 }, { -141, 37 }, { -3, 41 }, { -7, 37 } }
        }
    };

    ot = &g_ObjectTable1[g_ObjectTableIdx];

    // Draw green border around slot.
    for (i = 0; i < BORDER_PIXEL_WIDTH; i++)
    {
        for (j = 0; j < BORDER_LINE_COUNT; j++)
        {
            borderLine = (LINE_F2*)GsOUT_PACKET_P;
            setLineF2(borderLine);

            setRGB0(borderLine, FP_COLOR(0.0f), FP_COLOR(1.0f), FP_COLOR(0.0f));

            setXY2(borderLine,
                   borderLines[j][i].vertex0_0.vx + (g_SelectedSaveSlotIdx * SLOT_COLUMN_OFFSET), borderLines[j][i].vertex0_0.vy,
                   borderLines[j][i].vertex1_4.vx + (g_SelectedSaveSlotIdx * SLOT_COLUMN_OFFSET), borderLines[j][i].vertex1_4.vy);

            addPrim((u8*)ot->org + LAYER, borderLine);
            GsOUT_PACKET_P = (u8*)borderLine + sizeof(LINE_F2);
        }
    }

    // Draw green border glow around slot.
    for (i = 0; i < BORDER_PIXEL_WIDTH; i++)
    {
        for (j = 0; j < BORDER_LINE_COUNT; j++)
        {
            glowPoly = (POLY_G4*)GsOUT_PACKET_P;
            setPolyG4(glowPoly);
            setSemiTrans(glowPoly, 1);

            setRGB0(glowPoly, FP_COLOR(0.0f), FP_COLOR(0.5f), FP_COLOR(0.0f));
            setRGB1(glowPoly, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));
            setRGB2(glowPoly, FP_COLOR(0.0f), FP_COLOR(0.5f), FP_COLOR(0.0f));
            setRGB3(glowPoly, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));

            setXY4(glowPoly,
                   borderGlowQuads[j][i].vertex0_0.vx + (g_SelectedSaveSlotIdx * SLOT_COLUMN_OFFSET), borderGlowQuads[j][i].vertex0_0.vy,
                   borderGlowQuads[j][i].vertex1_4.vx + (g_SelectedSaveSlotIdx * SLOT_COLUMN_OFFSET), borderGlowQuads[j][i].vertex1_4.vy,
                   borderGlowQuads[j][i].vertex2_8.vx + (g_SelectedSaveSlotIdx * SLOT_COLUMN_OFFSET), borderGlowQuads[j][i].vertex2_8.vy,
                   borderGlowQuads[j][i].vertex3_C.vx + (g_SelectedSaveSlotIdx * SLOT_COLUMN_OFFSET), borderGlowQuads[j][i].vertex3_C.vy);

            addPrim((u8*)ot->org + LAYER, glowPoly);
            GsOUT_PACKET_P = (u8*)glowPoly + sizeof(POLY_G4);
        }
    }

    Gfx_Primitive2dTextureSet(0, 0, 7, 1);
}

void Gfx_SaveSlotMemCardMsgBoxShineDraw(s32 slotIdx) // 0x801E43C8
{
    GsOT*    ot;
    s16      colorTimer;
    s32      temp;
    s8       color;
    POLY_F4* poly;

    temp       = ((u8)g_SysWork.timer_1C) & 0x3F;
    colorTimer = temp;
    ot         = &g_ObjectTable1[g_ObjectTableIdx];

    if (g_SelectedSaveSlotIdx == slotIdx)
    {
        poly = (POLY_F4*)GsOUT_PACKET_P;
        setPolyF4(poly);
        setSemiTrans(poly, 1);

        if ((u16)colorTimer < FP_COLOR(0.125f))
        {
            color = (colorTimer * 2) + FP_COLOR(0.125f);
            setRGB0(poly, color, color, FP_COLOR(0.125f));
        }
        else
        {
            color = FP_COLOR(0.375f) - ((colorTimer - FP_COLOR(0.125f)) * 2);
            setRGB0(poly, color, color, FP_COLOR(0.125f));
        }

        setXY4(poly,
               (slotIdx * SLOT_COLUMN_OFFSET) - 142, -35, (slotIdx * SLOT_COLUMN_OFFSET) - 142, 2,
               (slotIdx * SLOT_COLUMN_OFFSET) - 6,   -35, (slotIdx * SLOT_COLUMN_OFFSET) - 6,   2);

        GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_F4);
        addPrim((u8*)ot->org + 28, poly);

        Gfx_Primitive2dTextureSet(0, 0, 7, 1);
    }
}

void Gfx_SaveSlotBoxDraw(s32 slotIdx, s32 saveCount, s32 selectedSaveIdx, s32 selectedSaveOffsetY) // 0x801E451C
{
    #define SCROLL_BAR_THUMB_RECT_COUNT 2
    #define SCROLL_BAR_ARROW_COUNT      2
    #define SCROLL_BAR_OFFSET_Y         60
    #define LAYER_BASE_0                28
    #define LAYER_BASE_1                32

    GsOT*    ot;
    POLY_F4* thumbPoly;
    POLY_F4* highlightPoly;
    POLY_G4* trackPoly;
    POLY_G3* arrowPoly;
    POLY_F4* unkPoly;
    s32      trackOffsetX;
    s32      thumbOffsetY;
    s32      thumbOffsetTopY;
    u32      thumbOffsetBottomY;
    s32      thumbOffsetX;
    s32      arrowOffsetX;
    u8       highlightColor;
    s32      i;
    s32      j;

    u32 selectedSaveHighlightTimer = (u8)g_SysWork.timer_1C & 0x3F;

    s_Quad2d scrollBarTrackQuads[] =
    {
        { { 0, 0 }, { 0, 96 }, { 4, 0 }, { 4, 96 } }, // Left half.
        { { 8, 0 }, { 8, 96 }, { 4, 0 }, { 4, 96 } }  // Right half.
    };

    s_Triangle2d scrollBarArrowTris[MEMORY_CARD_SLOT_COUNT][SCROLL_BAR_ARROW_COUNT] =
    {
        // Up arrows.
        {
            { { 4, -1 }, { -1, 7 }, { 8, 7 } }, // Slot 1 up arrow.
            { { 5, 1 }, { 0, 8 }, { 9, 8 } }    // Slot 2 up arrow.
        },
        // Down arrows.
        {
            { { 4, 96 }, { 0, 88 }, { 8, 88 } }, // Slot 1 down arrow.
            { { 5, 97 }, { 1, 89 }, { 9, 89 } }  // Slot 2 down arrow.
        }
    };

    u8 thumbOffsetsY[] =
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

    ot = &g_ObjectTable1[g_ObjectTableIdx];

    if (g_DisplaySaveDataInfo == 1 && slotIdx == g_SelectedSaveSlotIdx)
    {
        Gfx_SaveDataInfoDraw(slotIdx, selectedSaveIdx);
    }

    // Draw scroll bar thumb.
    if (saveCount != 0)
    {
        thumbOffsetY       = ((selectedSaveIdx * 79) / saveCount) + 8;
        thumbOffsetBottomY = thumbOffsetsY[saveCount - 1];

        // Inner and outer rectangles.
        for (i = 0; i < SCROLL_BAR_THUMB_RECT_COUNT; i++)
        {
            thumbPoly = (POLY_F4*)GsOUT_PACKET_P;
            setPolyF4(thumbPoly);

            // Inner rectangle color.
            if (i != 0)
            {
                setRGB0(thumbPoly, 0x70, 0x70, 0x70);
            }
            // Outer rectangle color.
            else
            {
                setRGB0(thumbPoly, 0x50, 0x50, 0x50);
            }

            // Reference track vertices for accurate thumb.
            thumbOffsetX    = (slotIdx * SLOT_COLUMN_OFFSET) - 139;
            thumbOffsetTopY = i - SCROLL_BAR_OFFSET_Y;
            setXY4(thumbPoly,
                   (scrollBarTrackQuads[0].vertex0_0.vx + thumbOffsetX) + i,  (scrollBarTrackQuads[0].vertex0_0.vy + thumbOffsetY) + thumbOffsetTopY,
                   (scrollBarTrackQuads[0].vertex0_0.vx + thumbOffsetX) + i, ((scrollBarTrackQuads[0].vertex0_0.vy + thumbOffsetY) + thumbOffsetBottomY) - (i + SCROLL_BAR_OFFSET_Y),
                   (scrollBarTrackQuads[1].vertex0_0.vx + thumbOffsetX) - i,  (scrollBarTrackQuads[1].vertex0_0.vy + thumbOffsetY) + thumbOffsetTopY,
                   (scrollBarTrackQuads[1].vertex0_0.vx + thumbOffsetX) - i, ((scrollBarTrackQuads[1].vertex0_0.vy + thumbOffsetY) + thumbOffsetBottomY) - (i + SCROLL_BAR_OFFSET_Y));

            // Ensure inner rectangle is on top.
            addPrim(((u8*)ot->org + LAYER_BASE_0) - (i * 4), thumbPoly);
            GsOUT_PACKET_P = (u8*)thumbPoly + sizeof(POLY_F4);
        }
    }

    // Draw selected save highlight.
    if (g_SelectedSaveSlotIdx == slotIdx)
    {
        highlightPoly = (POLY_F4*)GsOUT_PACKET_P;
        setPolyF4(highlightPoly);
        setSemiTrans(highlightPoly, 1);

        // Fade in and out.
        if (selectedSaveHighlightTimer < 0x20u)
        {
            highlightColor = (selectedSaveHighlightTimer * 2) + 0x20;
            setRGB0(highlightPoly, highlightColor, highlightColor, 0x20);
        }
        else
        {
            highlightColor = 0x60 - ((selectedSaveHighlightTimer - 0x20) * 2);
            setRGB0(highlightPoly, highlightColor, highlightColor, 0x20);
        }

        setXY4(highlightPoly,
               (slotIdx * SLOT_COLUMN_OFFSET) - 130, (selectedSaveOffsetY * SLOT_ROW_OFFSET) - 62,
               (slotIdx * SLOT_COLUMN_OFFSET) - 130, (selectedSaveOffsetY * SLOT_ROW_OFFSET) - 43,
               (slotIdx * SLOT_COLUMN_OFFSET) - 10,  (selectedSaveOffsetY * SLOT_ROW_OFFSET) - 62,
               (slotIdx * SLOT_COLUMN_OFFSET) - 10,  (selectedSaveOffsetY * SLOT_ROW_OFFSET) - 43);

        addPrim((u8*)ot->org + LAYER_BASE_0, highlightPoly);
        GsOUT_PACKET_P = (u8*)highlightPoly + sizeof(POLY_F4);

        Gfx_Primitive2dTextureSet(0, 0, 7, 1);
    }

    // Draw scroll bar arrows.
    for (i = 0; i < SCROLL_BAR_ARROW_COUNT; i++)
    {
        for (j = 0; j < 1; j++)
        {
            arrowPoly = (POLY_G3*)GsOUT_PACKET_P;
            setPolyG3(arrowPoly);

            setRGB0(arrowPoly, FP_COLOR(0.625f), FP_COLOR(0.625f), FP_COLOR(0.625f));
            setRGB1(arrowPoly, FP_COLOR(0.625f), FP_COLOR(0.625f), FP_COLOR(0.625f));
            setRGB2(arrowPoly, FP_COLOR(0.625f), FP_COLOR(0.625f), FP_COLOR(0.625f));

            arrowOffsetX = (slotIdx * SLOT_COLUMN_OFFSET) - 139;
            setXY3(arrowPoly,
                   scrollBarArrowTris[i][j].vertex0_0.vx + arrowOffsetX, scrollBarArrowTris[i][j].vertex0_0.vy - SCROLL_BAR_OFFSET_Y,
                   scrollBarArrowTris[i][j].vertex1_4.vx + arrowOffsetX, scrollBarArrowTris[i][j].vertex1_4.vy - SCROLL_BAR_OFFSET_Y,
                   scrollBarArrowTris[i][j].vertex2_8.vx + arrowOffsetX, scrollBarArrowTris[i][j].vertex2_8.vy - SCROLL_BAR_OFFSET_Y);

            addPrim((u8*)ot->org + LAYER_BASE_0, arrowPoly);
            GsOUT_PACKET_P = (u8*)arrowPoly + sizeof(POLY_G3);
        }
    }

    // Draw scroll bar track.
    for (i = 0; i < 2; i++)
    {
        trackPoly = (POLY_G4*)GsOUT_PACKET_P;
        setPolyG4(trackPoly);

        setRGB0(trackPoly, FP_COLOR(0.125f), FP_COLOR(0.125f), FP_COLOR(0.125f));
        setRGB1(trackPoly, FP_COLOR(0.125f), FP_COLOR(0.125f), FP_COLOR(0.125f));
        setRGB2(trackPoly, FP_COLOR(0.5f),   FP_COLOR(0.5f),   FP_COLOR(0.5f));
        setRGB3(trackPoly, FP_COLOR(0.5f),   FP_COLOR(0.5f),   FP_COLOR(0.5f));

        trackOffsetX = (slotIdx * SLOT_COLUMN_OFFSET) - 139;
        setXY4(trackPoly,
               scrollBarTrackQuads[i].vertex0_0.vx + trackOffsetX, scrollBarTrackQuads[i].vertex0_0.vy - SCROLL_BAR_OFFSET_Y,
               scrollBarTrackQuads[i].vertex1_4.vx + trackOffsetX, scrollBarTrackQuads[i].vertex1_4.vy - SCROLL_BAR_OFFSET_Y,
               scrollBarTrackQuads[i].vertex2_8.vx + trackOffsetX, scrollBarTrackQuads[i].vertex2_8.vy - SCROLL_BAR_OFFSET_Y,
               scrollBarTrackQuads[i].vertex3_C.vx + trackOffsetX, scrollBarTrackQuads[i].vertex3_C.vy - SCROLL_BAR_OFFSET_Y);

        addPrim((u8*)ot->org + LAYER_BASE_1, trackPoly);
        GsOUT_PACKET_P = (u8*)trackPoly + sizeof(POLY_G4);
    }

    // Draw transparent background.
    unkPoly = (POLY_F4*)GsOUT_PACKET_P;
    setPolyF4(unkPoly);
    setSemiTrans(unkPoly, 1);

    setRGB0(unkPoly, FP_COLOR(0.1875f), FP_COLOR(0.1875f), FP_COLOR(0.1875f));

    setXY4(unkPoly,
           (slotIdx * SLOT_COLUMN_OFFSET) - 139, -81,
           (slotIdx * SLOT_COLUMN_OFFSET) - 139,  37,
           (slotIdx * SLOT_COLUMN_OFFSET) - 9,   -81,
           (slotIdx * SLOT_COLUMN_OFFSET) - 9,    37);

    addPrim((u8*)ot->org + LAYER_BASE_1, unkPoly);
    GsOUT_PACKET_P = (u8*)unkPoly + sizeof(POLY_F4);

    Gfx_Primitive2dTextureSet(0, 0, 8, 1);
}

void Gfx_SaveEntryBorderDraw(s_SavegameEntry* saveEntry, s_SavegameEntry* nextSaveEntry, s32 saveIdx, s32 slotIdx) // 0x801E4D90
{
    GsOT* ot;
    u32   entryIdx         = saveEntry->elementIdx_7;
    s32   fileColorIdx     = saveEntry->fileIdx_6 + 1;
    s32   nextFileColorIdx = nextSaveEntry->fileIdx_6 + 1;
    s16   tileOffsetX1;
    s16   tileOffsetX0;
    s32   borderLineOffsetX;
    s32   borderLineOffsetY;
    s32   rowIdx;
    s32   i;
    s32   firstLineIdx;

    s_Line2d entryBorderLines[] =
    {
        { { -131, -62 }, { -11, -62 } },
        { { -131, -43 }, { -11, -43 } },
        { { -131, -62 }, { -131, -44 } },
        { { -11,  -62 }, { -11, -44 } }
    };

    s_PrimColor fileColors[] =
    {
        { 0x20, 0xA0, 0x20, 0x00 },
        { 0x60, 0xA0, 0x20, 0x00 },
        { 0xA0, 0xA0, 0x20, 0x00 },
        { 0xA0, 0x80, 0x20, 0x00 },
        { 0xA0, 0x60, 0x20, 0x00 },
        { 0xA0, 0x20, 0x20, 0x00 },
        { 0xA0, 0x20, 0x60, 0x00 },
        { 0xA0, 0x20, 0x80, 0x00 },
        { 0xA0, 0x20, 0xA0, 0x00 },
        { 0x80, 0x20, 0xA0, 0x00 },
        { 0x60, 0x20, 0xA0, 0x00 },
        { 0x20, 0x20, 0xA0, 0x00 },
        { 0x20, 0x40, 0xA0, 0x00 },
        { 0x20, 0x60, 0xA0, 0x00 },
        { 0x20, 0xA0, 0xA0, 0x00 }
    };

    LINE_F2* borderLine;
    TILE*    cornerTile;

    ot     = &g_ObjectTable1[g_ObjectTableIdx];
    rowIdx = saveIdx - g_HiddenElementsByDisplacement[slotIdx];

    // Draw border around savegame entry.
    firstLineIdx = rowIdx ? (entryIdx > 0) : 0;
    for (i = firstLineIdx; i < 4; i++)
    {
        borderLine = (LINE_F2*)GsOUT_PACKET_P;
        setLineF2(borderLine);
        setRGB0(borderLine, fileColors[fileColorIdx - 1].r, fileColors[fileColorIdx - 1].g, fileColors[fileColorIdx - 1].b);

        borderLineOffsetX = slotIdx * SLOT_COLUMN_OFFSET;
        borderLineOffsetY = rowIdx  * SLOT_ROW_OFFSET;

        // Regular entry.
        if (firstLineIdx == 0)
        {
            setXY2(borderLine,
                   entryBorderLines[i].vertex0_0.vx + borderLineOffsetX, entryBorderLines[i].vertex0_0.vy + borderLineOffsetY,
                   entryBorderLines[i].vertex1_4.vx + borderLineOffsetX, entryBorderLines[i].vertex1_4.vy + borderLineOffsetY);
        }
        // Entry at boundary between files.
        else
        {
            setXY2(borderLine,
                   entryBorderLines[i].vertex0_0.vx + borderLineOffsetX, (entryBorderLines[i].vertex0_0.vy + borderLineOffsetY) - ((i + (s32)((u32)i >> 31)) >> 1),
                   entryBorderLines[i].vertex1_4.vx + borderLineOffsetX,  entryBorderLines[i].vertex1_4.vy + borderLineOffsetY);
        }

        addPrim((u8*)ot->org + 24, borderLine);
        GsOUT_PACKET_P = (u8*)borderLine + sizeof(LINE_F2);
    }

    // Draw file start corner markers.
    if (entryIdx == 0)
    {
        for (i = 0; i < 2; i++)
        {
            cornerTile = (TILE*)GsOUT_PACKET_P;
            setTile(cornerTile);

            setRGB0(cornerTile, fileColors[fileColorIdx - 1].r, fileColors[fileColorIdx - 1].g, fileColors[fileColorIdx - 1].b);

            tileOffsetX0 = (slotIdx * SLOT_COLUMN_OFFSET) - 131;
            setXY0(cornerTile, tileOffsetX0 + (i * 117), (rowIdx * 20) - 62);
            setWH(cornerTile, 4, 4);

            addPrim((u8*)ot->org + 24, cornerTile);
            GsOUT_PACKET_P = (u8*)cornerTile + sizeof(TILE);
        }
    }

    // Draw file end corner markers.
    if (fileColorIdx != nextFileColorIdx || (saveIdx + 1) == g_SlotElementCount[slotIdx])
    {
        for (i = 0; i < 2; i += 1)
        {
            cornerTile = (TILE*)GsOUT_PACKET_P;
            setTile(cornerTile);

            setRGB0(cornerTile, fileColors[fileColorIdx - 1].r, fileColors[fileColorIdx - 1].g, fileColors[fileColorIdx - 1].b);

            tileOffsetX1 = (slotIdx * SLOT_COLUMN_OFFSET) - 131;
            setXY0(cornerTile, tileOffsetX1 + (i * 117), (rowIdx * 20) - 46);
            setWH(cornerTile, 4, 4);

            addPrim((u8*)ot->org + 24, cornerTile);
            GsOUT_PACKET_P = (u8*)cornerTile + sizeof(TILE);
        }
    }

    if (D_801E756C[slotIdx] != fileColorIdx)
    {
        D_801E756C[slotIdx] = fileColorIdx;
    }
}

// "Now checking MEMORY CARD"?
void Gfx_SaveSlotMemCardMsgBoxDraw(s32 slotIdx, s32 entryType) // 0x801E52D8
{
    s_ColoredLine2d coloredLines[MEMORY_CARD_SLOT_COUNT] =
    {
        // Red line.
        {
            { { -142, -33 }, { 136, 33 } },
            255, 0, 0,
            0,
        },
        // Green line.
        {
            { { -142, -33 }, { 136, 33 } }, 
            0, 255, 0,
            0
        }
    };

    s_LineBorder borderLines =
    {
        {
            { { -144, -36 }, { -4, -36 } },
            { { -144, 2 }, { -4, 2 } },
            { { -144, -36 }, { -144, 2 } },
            { { -4, -36 }, { -4, 2 } }
        }
    };

    s_QuadBorder borderGlowQuads =
    {
        {
            { { -144, -36 }, { -148, -40 }, { -4, -36 }, { 0, -40 } },
            { { -144, 2 }, { -148, 6 }, { -4, 2 }, { 0, 6 } },
            { { -144, -36 }, { -148, -40 }, { -144, 2 }, { -148, 6 } },
            { { -4, -36 }, { 0, -40 }, { -4, 2 }, { 0, 6 } }
        }
    };

    if (entryType == SavegameEntryType_UnformattedMemCard && g_GameWork.gameState_594 == GameState_Unk10) 
    {
        Gfx_SaveSlotMemCardMsgBoxSubDraw(&borderLines, &borderGlowQuads, &coloredLines[1], slotIdx);
    } 
    else 
    {
        Gfx_SaveSlotMemCardMsgBoxSubDraw(&borderLines, &borderGlowQuads, &coloredLines[0], slotIdx);
    }
}

void Gfx_SaveSlotMemCardMsgBoxSubDraw(s_LineBorder* borderLines, s_QuadBorder* borderGlowQuads, s_ColoredLine2d* coloredLine, s32 slotIdx) // 0x801E54DC
{
    GsOT*     ot;
    LINE_F2*  borderLine;
    POLY_G4*  glowPoly;
    POLY_F4*  unkPoly;
    s_Line2d* glowLine;
    s32       i;

    ot = &g_ObjectTable1[g_ObjectTableIdx];

    // Draw border around message.
    for (i = 0; i < 4; i++)
    {
        borderLine = (LINE_F2*)GsOUT_PACKET_P;
        setLineF2(borderLine);
        setRGB0(borderLine, coloredLine->r_8, coloredLine->g_A, coloredLine->b_C);

        setXY2(borderLine,
               borderLines->lines_0[i].vertex0_0.vx + (slotIdx * SLOT_COLUMN_OFFSET), borderLines->lines_0[i].vertex0_0.vy,
               borderLines->lines_0[i].vertex1_4.vx + (slotIdx * SLOT_COLUMN_OFFSET), borderLines->lines_0[i].vertex1_4.vy);

        addPrim((u8*)ot->org + 28, borderLine);
        GsOUT_PACKET_P = (u8*)borderLine + sizeof(LINE_F2);
    }

    // Draw border glow around message.
    for (i = 0; i < 4; i++)
    {
        glowPoly = (POLY_G4*)GsOUT_PACKET_P;
        setPolyG4(glowPoly);
        setSemiTrans(glowPoly, 1);

        setRGB0(glowPoly, coloredLine->r_8 / 2, coloredLine->g_A / 2, coloredLine->b_C / 2);
        setRGB1(glowPoly, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));
        setRGB2(glowPoly, coloredLine->r_8 / 2, coloredLine->g_A / 2, coloredLine->b_C / 2);
        setRGB3(glowPoly, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));

        glowLine = (s_Line2d*)&borderGlowQuads->quads_0[i].vertex2_8;
        setXY4(glowPoly,
               borderGlowQuads->quads_0[i].vertex0_0.vx + (slotIdx * SLOT_COLUMN_OFFSET), borderGlowQuads->quads_0[i].vertex0_0.vy,
               borderGlowQuads->quads_0[i].vertex1_4.vx + (slotIdx * SLOT_COLUMN_OFFSET), borderGlowQuads->quads_0[i].vertex1_4.vy,
               borderGlowQuads->quads_0[i].vertex2_8.vx + (slotIdx * SLOT_COLUMN_OFFSET), glowLine->vertex0_0.vy,
               glowLine->vertex1_4.vx + (slotIdx * SLOT_COLUMN_OFFSET), glowLine->vertex1_4.vy);

        addPrim((u8*)ot->org + 32, glowPoly);
        GsOUT_PACKET_P = (u8*)glowPoly + sizeof(POLY_G4);
    }
    
    Gfx_Primitive2dTextureSet(0, 0, 5, 1);
    
    // Draw (???)'
    unkPoly = (POLY_F4*)GsOUT_PACKET_P;
    setPolyF4(unkPoly);
    setSemiTrans(unkPoly, 1);

    setRGB0(unkPoly, FP_COLOR(0.1875f), FP_COLOR(0.1875f), FP_COLOR(0.1875f));

    setXY4(unkPoly,
           coloredLine->line_0.vertex0_0.vx + (slotIdx * SLOT_COLUMN_OFFSET),                                    coloredLine->line_0.vertex0_0.vy,
           coloredLine->line_0.vertex0_0.vx + (slotIdx * SLOT_COLUMN_OFFSET),                                    coloredLine->line_0.vertex0_0.vy + coloredLine->line_0.vertex1_4.vy,
           coloredLine->line_0.vertex0_0.vx + coloredLine->line_0.vertex1_4.vx + (slotIdx * SLOT_COLUMN_OFFSET), coloredLine->line_0.vertex0_0.vy,
           coloredLine->line_0.vertex0_0.vx + coloredLine->line_0.vertex1_4.vx + (slotIdx * SLOT_COLUMN_OFFSET), coloredLine->line_0.vertex0_0.vy + coloredLine->line_0.vertex1_4.vy);

    addPrim((u8*)ot->org + 32, unkPoly);
    GsOUT_PACKET_P = (u8*)unkPoly + sizeof(POLY_F4);

    Gfx_Primitive2dTextureSet(0, 0, 8, 1);
}

void Gfx_RectSaveInfoDraw(s_Line2d* line) // 0x801E5898
{
    GsOT*    ot;
    s32      color;
    s32      i;
    POLY_F3* poly_f3;
    POLY_F4* poly_f4;
    LINE_G2* line_g2;

    // Adjusted lines?
    DVECTOR sp10[] =
    {
        { line->vertex0_0.vx,                            line->vertex0_0.vy },
        { (line->vertex0_0.vx + line->vertex1_4.vx) - 8, line->vertex0_0.vy },
        { line->vertex0_0.vx + line->vertex1_4.vx,       line->vertex0_0.vy + 8},
        { line->vertex0_0.vx + line->vertex1_4.vx,       line->vertex0_0.vy + line->vertex1_4.vy },
        { line->vertex0_0.vx + 8,                        line->vertex0_0.vy + line->vertex1_4.vy },
        { line->vertex0_0.vx,                            (line->vertex0_0.vy + line->vertex1_4.vy) - 8 }
    };

    s_Triangle2d tris[] =
    {
        {
            { line->vertex0_0.vx + line->vertex1_4.vx,       line->vertex0_0.vy },
            { (line->vertex0_0.vx + line->vertex1_4.vx) - 8, line->vertex0_0.vy },
            { line->vertex0_0.vx + line->vertex1_4.vx,       line->vertex0_0.vy + 8 },
        },
        {
            { line->vertex0_0.vx,     line->vertex0_0.vy + line->vertex1_4.vy },
            { line->vertex0_0.vx + 8, line->vertex0_0.vy + line->vertex1_4.vy },
            { line->vertex0_0.vx,     (line->vertex0_0.vy + line->vertex1_4.vy) - 8 }
        }
    };

    ot = &g_ObjectTable1[g_ObjectTableIdx];

    for (i = 0; i < 2; i++)
    {
        poly_f3 = (POLY_F3*)GsOUT_PACKET_P;
        setPolyF3(poly_f3);

        color = FP_COLOR(0.1875f); // HACK

        setSemiTrans(poly_f3, 1);
        setRGB0(poly_f3, color, FP_COLOR(0.1875f), FP_COLOR(0.1875f));

        setXY3(poly_f3,
               tris[i].vertex0_0.vx, tris[i].vertex0_0.vy,
               tris[i].vertex1_4.vx, tris[i].vertex1_4.vy,
               tris[i].vertex2_8.vx, tris[i].vertex2_8.vy);

        addPrim((u8*)ot->org + 32, poly_f3);
        GsOUT_PACKET_P  = (u8*)poly_f3;
        GsOUT_PACKET_P += sizeof(POLY_F3);
    }

    Gfx_Primitive2dTextureSet(0, 0, 8, 2);

    poly_f4 = (POLY_F4*)GsOUT_PACKET_P;
    setPolyF4(poly_f4);
    setSemiTrans(poly_f4, 1);

    setRGB0(poly_f4, FP_COLOR(0.1875f), FP_COLOR(0.1875f), FP_COLOR(0.1875f));

    setXY4(poly_f4,
           line->vertex0_0.vx,                      line->vertex0_0.vy,
           line->vertex0_0.vx,                      line->vertex0_0.vy + line->vertex1_4.vy,
           line->vertex0_0.vx + line->vertex1_4.vx, line->vertex0_0.vy,
           line->vertex0_0.vx + line->vertex1_4.vx, line->vertex0_0.vy + line->vertex1_4.vy);

    addPrim((u8*)ot->org + 36, poly_f4);
    GsOUT_PACKET_P = (u8*)poly_f4 + sizeof(POLY_F4);

    Gfx_Primitive2dTextureSet(0, 0, 9, 1);

    for (i = 0; i < 6; i++)
    {
        line_g2 = (LINE_G2*)GsOUT_PACKET_P;
        setLineG2(line_g2);

        if (i & 0x1)
        {
            setRGB0(line_g2, FP_COLOR(0.625f),  FP_COLOR(0.5f),    FP_COLOR(0.25f));
            setRGB1(line_g2, FP_COLOR(0.6875f), FP_COLOR(0.6875f), FP_COLOR(0.6875f));
        }
        else
        {
            setRGB0(line_g2, FP_COLOR(0.6875f), FP_COLOR(0.6875f), FP_COLOR(0.6875f));
            setRGB1(line_g2, FP_COLOR(0.625f),  FP_COLOR(0.5f),    FP_COLOR(0.25f));
        }

        setXY2(line_g2,
               sp10[i].vx, sp10[i].vy,
               sp10[(i + 1) % 6].vx,sp10[(i + 1) % 6].vy);

        addPrim((u8*)ot->org + 28, line_g2);
        GsOUT_PACKET_P = (u8*)line_g2 + sizeof(LINE_G2);
    }
}

void Gfx_SaveDataInfoDraw(s32 slotIdx, s32 selectedSaveIdx) // 0x801E5E18
{
    char* labelStrs[] =
    {
        "Data",
        "Save",
        "Time",
        "hyper blaster",
        "power up",
        "You_need_1_free_block\n__to_create_a_new_file."
    };

    GsOT*               ot;
    s32                 saveId;
    s32                 mins;
    s32                 hasFlag;
    s32                 sec;
    s32                 hours;
    s32                 saveDataIdx;
    s32                 i;
    s32                 digitCount;
    s32                 offset;
    u32                 flags;
    u32                 timeInSec;
    s_SavegameMetadata* ptr;
    POLY_G4*            poly;

    ot = &g_ObjectTable1[g_ObjectTableIdx];

    g_ActiveSavegameEntry = GetActiveSavegameEntry(slotIdx);

    if (g_ActiveSavegameEntry[selectedSaveIdx].type_4 == SavegameEntryType_NewFile)
    {
        Gfx_StringSetColor(ColorId_White);
        Gfx_StringSetPosition(66, 178);
        Gfx_StringDraw("You_need_1_free_block\n__to_create_a_new_file.", 0x32);
    }
    else if (g_ActiveSavegameEntry[selectedSaveIdx].type_4 == SavegameEntryType_Save)
    {
        saveId      = g_ActiveSavegameEntry[selectedSaveIdx].savegameCount_2;
        saveDataIdx = g_ActiveSavegameEntry[selectedSaveIdx].elementIdx_7 + 1;

        saveId = CLAMP(saveId, 0, 999);

        ptr = g_ActiveSavegameEntry[selectedSaveIdx].field_C;

        timeInSec = FP_FROM(ptr->gameplayTimer_4, Q12_SHIFT);

        offset = ptr->add290Hours_B_1;
        hours  = (timeInSec / 3600) + offset * 290;

        flags = ptr->pickedUpSpecialItemCount_B_3;

        mins = (timeInSec / 60) % 60;
        sec  = timeInSec % 60;

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

        Gfx_StringSetPosition((digitCount * 10) + 220, 178);
        Gfx_StringDrawInt(2, mins);
        Gfx_StringDraw("_:_", 3);

        digitCount = sec < 10;

        Gfx_StringSetPosition((digitCount * 10) + 254, 178);
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
            setPolyG4(poly);
            setSemiTrans(poly, 1);

            hasFlag = flags & 0x10;

            if (i != 0)
            {
                setRGB0(poly, (hasFlag > 0) ? FP_COLOR(0.0f) : FP_COLOR(1.0f), FP_COLOR(1.0f), FP_COLOR(0.0f));
                setRGB2(poly, (hasFlag > 0) ? FP_COLOR(0.0f) : FP_COLOR(1.0f), FP_COLOR(1.0f), FP_COLOR(0.0f));
                setRGB1(poly, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));
                setRGB3(poly, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));
                setXY4(poly, -30, 89, -30, 93, 120, 89, 120, 93);
            }
            else
            {
                setRGB0(poly, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));
                setRGB2(poly, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));
                setRGB1(poly, (hasFlag > 0) ? FP_COLOR(0.0f) : FP_COLOR(1.0f), FP_COLOR(1.0f), FP_COLOR(0.0f));
                setRGB3(poly, (hasFlag > 0) ? FP_COLOR(0.0f) : FP_COLOR(1.0f), FP_COLOR(1.0f), FP_COLOR(0.0f));
                setXY4(poly, -30, 85, -30, 89, 120, 85, 120, 89);
            }

            GsOUT_PACKET_P = (u8*)poly + sizeof(POLY_G4);
            addPrim((u8*)ot->org + 28, poly);

            Gfx_Primitive2dTextureSet(0, 0, 7, 1);
        }
    }
}

void GameState_SaveScreen_Update() // 0x801E6320
{
    g_DisplaySaveDataInfo = 1;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        g_GameState_SaveScreen_Funcs[0]();
    }

    g_GameState_SaveScreen_Funcs[g_GameWork.gameStateStep_598[0]]();

    Gfx_SaveBackgroundDraw();
    Gfx_MemCardState();
    Gfx_SaveScreen();

    if (g_GameWork.gameState_594 == GameState_Unk10)
    {
        func_800363D0();
    }
}

void Savegame_ScreenInit() // 0x801E63C0
{
    if (g_GameWork.gameStatePrev_590 == GameState_MainMenu)
    {
        VSync(8);
    }

    g_IntervalVBlanks = 1;
    g_Gfx_ScreenFade  = SCREEN_FADE_STATUS(ScreenFadeState_FadeInStart, false);

    g_GameWork.background2dColor_R_58C = FP_COLOR(0.0f);
    g_GameWork.background2dColor_G_58D = FP_COLOR(0.0f);
    g_GameWork.background2dColor_B_58E = FP_COLOR(0.0f);

    D_800BCD39 = 0;
    if (g_GameWork.gameState_594 == GameState_DeathLoadScreen || g_GameWork.gameState_594 == GameState_SaveScreen)
    {
        if (D_800A97D8 != 0)
        {
            D_800BCD34 = 0;
        }
    }

    g_MemCardStateTextTimer = 0;
    D_800A97D8              = g_GameWork.gameState_594 == GameState_Unk10;

    Savegame_ScreenSubInit();

    g_SysWork.timer_20 = FP_TIME(0.0f);
    g_GameWork.gameStateStep_598[0]++;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;
}

void Savegame_ScreenLogic() // 0x801E649C
{
    s32              gameStateStep = g_GameWork.gameStateStep_598[1];
    s_SavegameEntry* saveEntry;

    switch (gameStateStep)
    {
        case 0:
            if (func_80033548() == 0) 
            {
                break;
            }

            // Memory cards are inserted and user is moving between slots.
            if (g_MemCardElementCount[0] != 0 && g_MemCardElementCount[1] != 0 && 
                (g_Controller0->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft)))
            {
                g_SelectedSaveSlotIdx ^= 1;
                Sd_EngineCmd(Sfx_Back);
            }

            // A memory card is inserted.
            if (g_MemCardsTotalElementCount > 0)
            {
                g_SaveWriteOption     = 0;
                g_IsSaveSelected      = 0;
                g_ActiveSavegameEntry = GetActiveSavegameEntry(g_SelectedSaveSlotIdx);

                // Move down savegame entry.
                if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickUp) 
                {
                    if (g_SlotElementSelectedIdx[g_SelectedSaveSlotIdx] != 0) 
                    {
                        g_SlotElementSelectedIdx[g_SelectedSaveSlotIdx]--;
                        Sd_EngineCmd(Sfx_Back);
                    }
                }

                // Move up savegame entry.
                if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown) 
                {
                    if (g_SlotElementSelectedIdx[g_SelectedSaveSlotIdx] < g_MemCardElementCount[g_SelectedSaveSlotIdx] - 1)
                    {
                        g_SlotElementSelectedIdx[g_SelectedSaveSlotIdx]++;
                        Sd_EngineCmd(Sfx_Back);
                    }
                }

                saveEntry             = &g_ActiveSavegameEntry[g_SlotElementSelectedIdx[g_SelectedSaveSlotIdx]];
                g_ActiveSavegameEntry = saveEntry;
                D_800BCD40            = saveEntry->field_5;
                g_SelectedFileIdx     = saveEntry->fileIdx_6;
                g_SelectedSaveIdx     = saveEntry->elementIdx_7;

                if (D_800BCD38 == 2) 
                {
                    if (saveEntry->currentScreenSessionSaves_0 == 31600)
                    {
                        g_SaveWriteOption = 1;
                    }

                    // This is the code that defines if the selected element is the `New Save` option or a save game.
                    if ((u16)(saveEntry->currentScreenSessionSaves_0 - 1) < 31099)
                    {
                        g_IsSaveSelected = 1;
                    }
                }

                // Overwrite or format savegame entry.
                if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0) 
                {
                    if ((g_SaveWriteOption | g_IsSaveSelected) != 0) 
                    {
                        g_SaveWriteOptionSelected       = 0;
                        g_GameWork.gameStateStep_598[2] = 0;
                        g_GameWork.gameStateStep_598[1]++;
                    }
                    else
                    {
                        g_SysWork.timer_20               = FP_TIME(0.0f);
                        g_GameWork.gameStateStep_598[1]  = 0;
                        g_GameWork.gameStateStep_598[2]  = 0;
                        g_GameWork.gameStateStep_598[0] += D_800BCD38;
                    }

                    Sd_EngineCmd(Sfx_Confirm);
                }
            }

            // Exit save screen.
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2) 
            {
                g_Gfx_ScreenFade                = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutSteps, false);
                g_GameWork.gameStateStep_598[1] = 2;
                g_GameWork.gameStateStep_598[2] = 0;

                Sd_EngineCmd(Sfx_Cancel);

                if (g_GameWork.gameStatePrev_590 == GameState_InventoryScreen) 
                {
                    Sd_EngineCmd(23);
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

            if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickLeft) 
            {
                g_SaveWriteOptionSelected = gameStateStep;
                Sd_EngineCmd(Sfx_Back);
            }

            if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickRight) 
            {
                g_SaveWriteOptionSelected = 0;
                Sd_EngineCmd(Sfx_Back);
            }

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0) 
            {
                if (g_SaveWriteOptionSelected == 0)
                {
                    g_GameWork.gameStateStep_598[0] = gameStateStep;
                    g_SysWork.timer_20              = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
                else
                {
                    g_SysWork.timer_20              = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    g_GameWork.gameStateStep_598[0] = g_IsSaveSelected + 2;
                }
                Sd_EngineCmd(Sfx_Confirm);
            }

            // Cancel overwrite.
            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2) 
            {
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                Sd_EngineCmd(Sfx_Cancel);
            }

            Gfx_WriteOptionSave(g_SaveWriteOption, g_SaveWriteOptionSelected);
            break;

        case 2:
            if (Gfx_IsScreenFadeComplete())
            {
                g_GameWork.background2dColor_R_58C = 0;
                g_GameWork.background2dColor_G_58D = 0;
                g_GameWork.background2dColor_B_58E = 0;

                Fs_QueueWaitForEmpty();

                // Unused or cut debug feature?
                // This redirects to the status screen/inventory
                // if the user was in the status screen/inventory before saving.
                // However, it is impossible to access the save screen from there.
                if (g_GameWork.gameStatePrev_590 == GameState_InventoryScreen)
                {
                    Game_StateSetNext(g_GameWork.gameStatePrev_590);
                }
                else
                {
                    if (D_800BCD38 == gameStateStep)
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

void Savegame_FormatLogic() // 0x801E69E8
{
    #define STR_TIMER_MAX (TICKS_PER_SECOND / 2)

    // Handle memory card format state.
    switch (g_GameWork.gameStateStep_598[1])
    {
        case MemCardFormatState_0:
            g_MemCardState                  = MemCardState_Format;
            g_MemCardStateTextTimer         = STR_TIMER_MAX;
            g_GameWork.gameStateStep_598[1] = MemCardFormatState_1;
            g_GameWork.gameStateStep_598[2] = 0;

        case MemCardFormatState_1:
            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case MemCardFormatState_2:
            func_8002E94C(6, D_800BCD40, 0, 0);

            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case MemCardFormatState_3:
            switch (func_8002E990())
            {
                case 10:
                    g_MemCardStateTextTimer         = STR_TIMER_MAX;
                    g_GameWork.gameStateStep_598[0] = 1;
                    g_SysWork.timer_20              = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;

                case 11:
                    g_SysWork.timer_20 = 0;
                    g_GameWork.gameStateStep_598[0]++;
                    g_GameWork.gameStateStep_598[1] = MemCardFormatState_0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;
            }
            break;
    }
}

void Savegame_SaveLogic() // 0x801E6B18
{
    s_SavegameMetadata* saveEntry;

    // Handle save state.
    switch (g_GameWork.gameStateStep_598[1])
    {
        case SaveState_0:
            g_MemCardState = MemCardState_Save;
            saveEntry      = Savegame_MetadataGet(D_800BCD40, g_SelectedFileIdx, g_SelectedSaveIdx);

            if (g_SavegamePtr->locationId_A8 == SaveLocationId_NextFear)
            {
                saveEntry->savegameCount_8 = 0;
            }
            else
            {
                g_SavegamePtr->savegameCount_A6++;
                saveEntry->savegameCount_8 = g_SavegamePtr->savegameCount_A6;
            }

            saveEntry->locationId_A    = g_SavegamePtr->locationId_A8;
            saveEntry->gameplayTimer_4 = g_SavegamePtr->gameplayTimer_250;

            g_IsNextFearMode = saveEntry->isNextFearMode_B;

            saveEntry->isNextFearMode_B             = g_SavegamePtr->isNextFearMode_25C;
            saveEntry->add290Hours_B_1              = g_SavegamePtr->add290Hours_25C_1;
            saveEntry->pickedUpSpecialItemCount_B_3 = g_SavegamePtr->pickedUpSpecialItemCount_25C_3;

            func_8002E94C(5, D_800BCD40, g_SelectedFileIdx, g_SelectedSaveIdx);
            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;

        case SaveState_1:
            switch (func_8002E990())
            {
                default:
                    g_GameWork.gameStateStep_598[0] = 1;
                    g_SysWork.timer_20              = 0;
                    g_GameWork.gameStateStep_598[1] = SaveState_0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;

                case 1:
                    g_MemCardStateTextTimer = 30;
                    break;

                case 11:
                    func_8002E94C(3, D_800BCD40, g_SelectedFileIdx, 0);
                    g_GameWork.gameStateStep_598[1]++;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;
            }
            break;

        case SaveState_2:
            switch (func_8002E990())
            {
                case 1:
                    g_MemCardStateTextTimer = 30;
                    break;

                case 11:
                    g_GameWork.autosave_90 = g_GameWork.savegame_30C;

                default:
                    g_GameWork.gameStateStep_598[0] = 1;
                    g_SysWork.timer_20              = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;
            }
            break;
    }
}

void Savegame_LoadLogic() // 0x801E6DB0
{
    s32 var0;
    s32 var1;

    // Handle load state.
    switch (g_GameWork.gameStateStep_598[1])
    {
        case LoadState_0:
            g_MemCardState = MemCardState_Load;

            func_8002E94C(4, D_800BCD40, g_SelectedFileIdx, g_SelectedSaveIdx);

            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;

        case LoadState_1:
            var0 = func_8002E990();
            if (var0 != 1)
            {
                if (var0 != 11)
                {
                    D_800BCD39 = 1;
                    g_GameWork.gameStateStep_598[0] = 1;
                    g_SysWork.timer_20              = 0;
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

        case LoadState_2:
            var1 = func_8002E990();
            if (var1 == 1)
            {
                g_MemCardStateTextTimer = 30;
                break;
            }

            if (var1 != 11)
            {
                D_800BCD39                      = 1;
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
    }
}

void Savegame_ContinueLogic() // 0x801E6F38
{
    // Handle continue state.
    switch (g_GameWork.gameStateStep_598[1])
    {
        case ContinueState_0:
            func_8002E830();

            D_800A97D7             = 1;
            g_GameWork.autosave_90 = g_GameWork.savegame_30C;

            Game_PlayerInit();
            
            g_SysWork.processFlags_2298 = SysWorkProcessFlag_LoadSave;

            GameFs_MapLoad(g_SavegamePtr->mapOverlayId_A4);

            g_Gfx_ScreenFade = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutStart, false);
            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case ContinueState_1:
        {
            if (Gfx_IsScreenFadeComplete())
            {
                Fs_QueueWaitForEmpty();
                Settings_ScreenAndVolUpdate();

                Game_StateSetNext(GameState_MainLoadScreen);
            }
            break;
        }
    }
}

void Gfx_SaveBackgroundDraw() // 0x801E709C
{
    // Draw "SLOT 1"/"SLOT 2" strings and bottom transparent frame.
    Gfx_SaveScreenBaseDraw();

    // Draws background image.
    Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);
}

void Gfx_SaveScreen() // 0x801E70C8
{
    s32              i;
    s32              j;
    s_SavegameEntry* nextSaveEntry;

    // Run through save slots.
    for (i = 0; i < MEMORY_CARD_SLOT_COUNT; i++)
    {
        g_ActiveSavegameEntry = GetActiveSavegameEntry(i);

        // Run through savegame entries.
        for (j = 0; j < (s32)g_SlotElementCount[i]; j++)
        {
            if (g_ActiveSavegameEntry->currentScreenSessionSaves_0 >= 0)
            {
                Gfx_SaveSlotFileStringDraw(j, i, g_ActiveSavegameEntry->fileIdx_6 + 1, g_ActiveSavegameEntry->type_4);
            }

            Gfx_SaveScreenDraw(g_ActiveSavegameEntry, j, i);

            if (g_ActiveSavegameEntry->type_4 >= SavegameEntryType_CorruptedSave)
            {
                nextSaveEntry = g_ActiveSavegameEntry;
                if (j != g_SlotElementCount[i])
                {
                    nextSaveEntry++;
                }

                Gfx_SaveEntryBorder(g_ActiveSavegameEntry, nextSaveEntry, j, i);
            }

            if (g_ActiveSavegameEntry->type_4 == SavegameEntryType_Save)
            {
                Gfx_SavegameEntryLocationNameDraw(g_ActiveSavegameEntry, j, i);
            }

            g_ActiveSavegameEntry++;
        }

        if (g_GameWork.gameState_594 == GameState_DeathLoadScreen)
        {
            Gfx_SaveSelectedDisplacement(i, g_SavegameCount);
        }
        else
        {
            Gfx_SaveSelectedDisplacement(i, g_MemCardsTotalElementCount);
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
        case MemCardState_Format:
            Gfx_MemCardStateDraw(g_MemCardState, (D_800BCD34 >> (D_800BCD40 * 3)) & 0x7);
            break;

        case MemCardState_Save:
        case MemCardState_Load:
            Gfx_MemCardStateDraw(g_MemCardState, func_8002E990());
            break;
    }
}

void Gfx_WriteOptionSave(s32 arg0, s32 optionIdx) // 0x801E72DC
{
    Gfx_WriteOptionSaveDraw(arg0, optionIdx);
}

void GameState_DeathLoadScreen_Update() // 0x801E72FC
{
    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        g_GameState_DeathLoadScreen_Funcs[0]();
    }

    g_GameState_DeathLoadScreen_Funcs[g_GameWork.gameStateStep_598[0]]();

    Gfx_SaveBackgroundDraw();
    Gfx_MemCardState();
    Gfx_SaveScreen();
}

void func_801E737C() // 0x801E737C
{
    if (!func_80033548())
    {
        return;
    }

    if (g_SavegameCount == 0 || D_800BCD39 != 0 || !func_80033548())
    {
        g_GameWork.gameState_594 = GameState_SaveScreen;

        if (g_GameWork.gameStatePrev_590 == GameState_KcetLogo)
        {
            g_GameWork.gameStateStep_598[0] = 1;
            g_GameWork.gameStateStep_598[1] = g_GameWork.gameStatePrev_590;

            g_Gfx_ScreenFade = SCREEN_FADE_STATUS(ScreenFadeState_FadeOutSteps, false);

            GameFs_TitleGfxLoad();
        }

        return;
    }

    g_ActiveSavegameEntry = GetActiveSavegameEntry(g_SelectedSaveSlotIdx);
    g_ActiveSavegameEntry = &g_ActiveSavegameEntry[g_SlotElementSelectedIdx[g_SelectedSaveSlotIdx]];
    D_800BCD40            = g_ActiveSavegameEntry->field_5;
    g_SelectedFileIdx     = g_ActiveSavegameEntry->fileIdx_6;
    g_SelectedSaveIdx     = g_ActiveSavegameEntry->elementIdx_7;

    g_GameWork.gameStateStep_598[0]++;
    g_SysWork.timer_20              = 0;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;
}
