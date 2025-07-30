#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math.h"

const s32 rodataPad_800262F8 = 0;

#include "D_800262FC_Rodata.h"

void Inventory_DirectionalInputSet() // 0x8004F5DC
{
    if (g_Controller0->field_20.sticks_0.leftY < -64 || g_Controller0->field_20.sticks_0.leftY >= 64 ||
        g_Controller0->field_20.sticks_0.leftX < -64 || g_Controller0->field_20.sticks_0.leftX >= 64)
    {
        // Up.
        g_Inventory_IsUpClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickUp2;
        g_Inventory_IsUpPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickUp2;

        // Down.
        g_Inventory_IsDownClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickDown2;
        g_Inventory_IsDownPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickDown2;

        // Left.
        g_Inventory_IsLeftClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickLeft2;
        g_Inventory_IsLeftHeld    = g_Controller0->btnsHeld_C     & ControllerFlag_LStickLeft2;
        g_Inventory_IsLeftPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickLeft2;

        // Right.
        g_Inventory_IsRightClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickRight2;
        g_Inventory_IsRightHeld    = g_Controller0->btnsHeld_C     & ControllerFlag_LStickRight2;
        g_Inventory_IsRightPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickRight2;
    }
    else
    {
        // Up.
        g_Inventory_IsUpClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickUp;
        g_Inventory_IsUpPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickUp;

        // Down.
        g_Inventory_IsDownClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickDown;
        g_Inventory_IsDownPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickDown;

        // Left.
        g_Inventory_IsLeftClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickLeft;
        g_Inventory_IsLeftHeld    = g_Controller0->btnsHeld_C     & ControllerFlag_LStickLeft;
        g_Inventory_IsLeftPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickLeft;

        // Right.
        g_Inventory_IsRightClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickRight;
        g_Inventory_IsRightHeld    = g_Controller0->btnsHeld_C     & ControllerFlag_LStickRight;
        g_Inventory_IsRightPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickRight;
    }
}

void Gfx_ItemScreens_RenderInit(u32* selectedItemId) // 0x8004F764
{
    GsDOBJ2* ptr;
    s32      i;

    DVECTOR strPosTable[] = // 0x80027DD8
    {
        { 0x0076, 0xFFB0 },
        { 0x0090, 0x0130 },
        { 0x0024, 0x0130 },
        { 0x00F0, 0x0130 }, 
        { 0x00DA, 0xFFB0 },
        { 0x0028, 0xFFB0 },
        { 0x0010, 0x00B8 },
        { 0x0010, 0x00C8 }
    };

    char* strs[] = // 0x80027E34
    {
        "Equipment",
        "Exit",
        "Option",
        "Map",
        "Command",
        "Status",
        "No.",
        "Name:"
    };

    Gfx_StringSetColor(ColorId_White);

    if (g_GameWork.gameStateStep_598[1] < 21) // If screen is inventory
    {
        for (i = 0; i < 8; i++)
        {
            Gfx_StringSetPosition(strPosTable[i].vx, strPosTable[i].vy);
            Gfx_StringDraw(strs[i], 10);
        }

        Inventory_PlayerItemScroll(selectedItemId);

		// Player Items
        for (i = 0, ptr = &g_Items_ItemsModelData; i < 7; i++, ptr++)
        {
            if (D_800C3E18[i] != NO_VALUE)
            {
                if (g_SavegamePtr->items_0[D_800C3E18[i]].id_0 != 0xFF)
                {
                    g_Items_Items3dData0[i].rotation_10.vx = D_800262FC[g_SavegamePtr->items_0[D_800C3E18[i]].id_0 - 32].vx;
                    g_Items_Items3dData0[i].rotation_10.vz = D_800262FC[g_SavegamePtr->items_0[D_800C3E18[i]].id_0 - 32].vy;

                    Gfx_Items_ItemRotate(&g_Items_Items3dData1[i].param->rotate, &g_Items_Items3dData1[i]);
                    func_800548D8(i);
                    GsSetFlatLight(0, &g_Items_ItemsLightingData[i][0]);
                    GsSetFlatLight(1, &g_Items_ItemsLightingData[i][1]);
                    func_8004BD74(i, ptr, 0);
                }
            }
        }

		// Equipped Item
        if (g_SavegamePtr->items_0[g_Inventory_EquippedItemIdx].id_0 != 0xFF && g_Inventory_EquippedItemIdx != NO_VALUE)
        {
            g_Items_Items3dData0[7].rotation_10.vx = D_800262FC[g_SavegamePtr->items_0[g_Inventory_EquippedItemIdx].id_0 - 32].vx;
            g_Items_Items3dData0[7].rotation_10.vz = D_800262FC[g_SavegamePtr->items_0[g_Inventory_EquippedItemIdx].id_0 - 32].vy;

            Gfx_Items_ItemRotate(&g_Items_Items3dData1[7].param->rotate, &g_Items_Items3dData1[7]);
            func_800548D8(7);
            GsSetFlatLight(0, &D_800C3A88[0]);
            GsSetFlatLight(1, &D_800C3A88[1]);
            func_8004BD74(7, ptr, 0);
        }

        Gfx_Inventory_ItemDescriptionDraw(selectedItemId);
        Gfx_Inventory_2dBackgroundDraw(selectedItemId);
    }
    else
    {
        Gfx_Results_ItemsPosition(g_SavegamePtr->clearGameCount_24A);
        Gfx_Results_ItemsDisplay(g_SavegamePtr->clearGameCount_24A);
        Results_DisplayInfo(selectedItemId); // TODO: Takes no args in `credits.c`?
    }

    func_8004FB0C();
}

void func_8004FB0C() // 0x8004FB0C
{
    GsOT*    ot;
    POLY_F4* poly;

    ot   = &g_ObjectTable1[g_ObjectTableIdx];
    poly = (POLY_F4*)GsOUT_PACKET_P;

    setPolyF4(poly);
    setRGB0(poly, 0, 0, 0);
    setXY4(poly,
           -160, -224,
           -160, -222,
            160, -224,
            160, -222);
    addPrim(ot->org, poly);

    GsOUT_PACKET_P = (PACKET*)poly + sizeof(POLY_F4);
}

// TODO: RODATA migration.
//
// Function isn't fully matching.
// `SelectionOuline_InnerLine[g_Inventory_PrevSelectionId].field_0.vx - new_var` is mismatched
// Scratch: https://decomp.me/scratch/pGIn2
#ifdef NON_MATCHING
/** Draws many 2D menu elements.
 * The background behind the text in the upper
 * and lower part of the inventory screen, the
 * box used to indicate what the user has selected,
 * and triggers the drawing of the health status.
 */
void Gfx_Inventory_2dBackgroundDraw(s32* arg0) // 0x8004FBCC
{
    s16       ot0_7;
    s16       temp_a2_2;
    s16       temp_t2_3;
    s32       temp_t3;
    s32       temp_v1;
    s32       k;
    s32       i;
    s32       j;
    s32       var_t5;
    s32       var_t6;
    s32       new_var;
    s32       new_var3;
    s32       spA0;
    GsOT*     ot0;
    GsOT*     ot1;
    GsOT*     new_var2;
    POLY_G4*  poly_g4;
    POLY_FT4* poly_ft4;
    LINE_G2*  line_g2;

    s_Inventory_SelectionOutlineVector SelectionOuline_InnerLine[] = // 0x80027E54
    {
        { { 0xFFE0, 0xFFCC }, { 0x0040, 0x0080 } }, 
        { { 0xFFD0, 0xFF38 }, { 0x0060, 0x0090 } },
        { { 0xFFD0, 0x00B9 }, { 0x0060, 0x0018 } },
        { { 0xFF70, 0x00B9 }, { 0x0060, 0x0018 } },
        { { 0x0030, 0x00B9 }, { 0x0060, 0x0018 } },
        { { 0x0030, 0xFF38 }, { 0x0060, 0x0080 } },
        { { 0x0030, 0xFF38 }, { 0x0060, 0x0080 } },
        { { 0xFF70, 0xFF38 }, { 0x0060, 0x009C } },
        { { 0xFFD0, 0xFF38 }, { 0x00C0, 0x0100 } }
    };

    s_Inventory_SelectionOutlineVector SelectionOuline_ConerLines[] = // 0x80027E9C
    {
        { { 0xFFDE, 0xFFC8 }, { 0x0022, 0x0050 } },
        { { 0xFFCE, 0xFF34 }, { 0x0032, 0xFFCC } },
        { { 0xFFCE, 0x00B5 }, { 0x0032, 0x00D5 } },
        { { 0xFF6E, 0x00B5 }, { 0xFFD2, 0x00D5 } },
        { { 0x002E, 0x00B5 }, { 0x0092, 0x00D5 } },
        { { 0x002E, 0xFF34 }, { 0x0092, 0xFFBC } },
        { { 0x002D, 0xFF34 }, { 0x0092, 0xFFBC } },
        { { 0xFF6E, 0xFF34 }, { 0xFFD2, 0xFFD8 } },
        { { 0xFFCE, 0xFF34 }, { 0x0092, 0x003C } }
    };

    ot1 = &g_ObjectTable1[g_ObjectTableIdx];
    ot0 = &g_ObjectTable0[g_ObjectTableIdx];

    temp_v1 = g_SysWork.timer_1C & 0x7F;

    if (temp_v1 < 0x40)
    {
        spA0 = temp_v1;
    }
    else
    {
        spA0 = 0x7F - temp_v1;
    }

    Gfx_Inventory_HealthStatusDraw();
    if (g_Gfx_Inventory_SelectionBordersDraw == 8)
    {
        switch (*arg0)
        {
            case 1:
                var_t6 = 0;
                var_t5 = 1;
                break;

            case 2:
                var_t6 = 1;
                var_t5 = 1;
                break;

            case 3:
                var_t6 = 1;
                var_t5 = 0;
                break;

            case 4:
                var_t6 = 1;
                var_t5 = 2;
                break;

            case 5:
            case 6:
                var_t6 = 0;
                var_t5 = 2;
                break;

            case 7:
                var_t6 = 0;
                var_t5 = 0;
                break;

            default:
                var_t5 = -1;
                var_t6 = -1;
                break;
        }
    }
    else
    {   
        var_t5 = -1;
        var_t6 = -1;
    }

    if (g_GameWork.gameStateStep_598[1] != 20) 
    {
        for (i = 0; i < 2; i++)
        {
            for (j = 0; j < 3; j++)
            {
                for (k = 0; k < 2; k++)
                {
                    poly_g4 = (POLY_G4*)GsOUT_PACKET_P;
                    setPolyG4(poly_g4);

                    if (k != 0)
                    {
                        switch (g_SavegamePtr->gameDifficulty_260)
                        {
                            case GameDifficulty_Easy:
                                if (i == var_t6 && j == var_t5)
                                {
                                    setRGB0(poly_g4, spA0 - 0x80, 0xC0, spA0 * 3);
                                    setRGB2(poly_g4, spA0 - 0x80, 0xC0, spA0 * 3);
                                } 
                                else 
                                {
                                    setRGB0(poly_g4, 0x80, 0xC0, 0);
                                    setRGB2(poly_g4, 0x80, 0xC0, 0);
                                }
                                break;

                            case GameDifficulty_Normal:
                                if (i == var_t6 && j == var_t5)
                                {
                                    setRGB0(poly_g4, spA0 * 3, spA0 - 0x80, 0xC0);
                                    setRGB2(poly_g4, spA0 * 3, spA0 - 0x80, 0xC0);
                                }
                                else
                                {
                                    setRGB0(poly_g4, 0, 0x80, 0xC0);
                                    setRGB2(poly_g4, 0, 0x80, 0xC0);
                                }
                                break;

                            case GameDifficulty_Hard:
                                if (i == var_t6 && j == var_t5)
                                {
                                    setRGB0(poly_g4, spA0 - 0x80, spA0 * 3, 0xC0);
                                    setRGB2(poly_g4, spA0 - 0x80, spA0 * 3, 0xC0);
                                }
                                else
                                {
                                    setRGB0(poly_g4, 0x80, 0, 0xC0);
                                    setRGB2(poly_g4, 0x80, 0, 0xC0);
                                }
                                break;
                        }

                        setRGB1(poly_g4, 0, 0, 0);
                        setRGB3(poly_g4, 0, 0, 0);
                    }
                    else
                    {
                        switch (g_SavegamePtr->gameDifficulty_260)
                        {
							
                            case GameDifficulty_Easy:
                                if (i == var_t6 && j == var_t5)
                                {
                                    setRGB1(poly_g4, spA0 - 0x80, 0xC0, spA0 * 3);
                                    setRGB3(poly_g4, spA0 - 0x80, 0xC0, spA0 * 3);
                                }
                                else
                                {
                                    setRGB1(poly_g4, 0x80, 0xC0, 0);
                                    setRGB3(poly_g4, 0x80, 0xC0, 0);
                                }
                                break;

                            case GameDifficulty_Normal:
                                if (i == var_t6 && j == var_t5)
                                {
                                    setRGB1(poly_g4, spA0 * 3, spA0 - 0x80, 0xC0);
                                    setRGB3(poly_g4, spA0 * 3, spA0 - 0x80, 0xC0);
                                } 
                                else
                                {
                                    setRGB1(poly_g4, 0, 0x80, 0xC0);
                                    setRGB3(poly_g4, 0, 0x80, 0xC0);
                                }
                                break;

                            case GameDifficulty_Hard:
                                if (i == var_t6 && j == var_t5)
                                {
                                    setRGB1(poly_g4, spA0 - 0x80, spA0 * 3, 0xC0);
                                    setRGB3(poly_g4, spA0 - 0x80, spA0 * 3, 0xC0);
                                }
                                else
                                {
                                    setRGB1(poly_g4, 0x80, 0, 0xC0);
                                    setRGB3(poly_g4, 0x80, 0, 0xC0);
                                }
                                break;
                        }

                        setRGB0(poly_g4, 0, 0, 0);
                        setRGB2(poly_g4, 0, 0, 0);
                    }
            
                    if (i != 0)
                    {
                        setXY4(poly_g4,
                               -0x8C + (0x60 * j), 0xC0 + (6 * k),
                               -0x8C + (0x60 * j), 0xC6 + (6 * k),
                               -0x34 + (0x60 * j), 0xC0 + (6 * k),
                               -0x34 + (0x60 * j), 0xC6 + (6 * k));
                    }
                    else
                    {
                        setXY4(poly_g4,
                               -0x8C + (0x60 * j), -0xC0 + (6 * k),
                               -0x8C + (0x60 * j), -0xBA + (6 * k),
                               -0x34 + (0x60 * j), -0xC0 + (6 * k), 
                               -0x34 + (0x60 * j), -0xBA + (6 * k));
                    }

                    addPrim(&ot1->org[7], poly_g4);
                    GsOUT_PACKET_P = (PACKET*)poly_g4 + sizeof(POLY_G4);
                }
            }
        }
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            D_800C3B68[3 - i][j].vx = D_800C3B68[2 - i][j].vx;
            D_800C3B68[3 - i][j].vy = D_800C3B68[2 - i][j].vy;
        }
    }
    
    temp_t3   = (shRcos(g_Gfx_Inventory_SelectionBordersDraw << 7) * shRcos(g_Gfx_Inventory_SelectionBordersDraw << 7) * 0x10) >> 0x10;
    new_var   = SelectionOuline_InnerLine[*arg0].field_0.vx;
    new_var  -= SelectionOuline_InnerLine[g_Inventory_PrevSelectionId].field_0.vx;
    temp_a2_2 = SelectionOuline_InnerLine[*arg0].field_0.vx + FP_FROM((new_var) * temp_t3, Q12_SHIFT);

    D_800C3B68[0][0].vx = temp_a2_2;

    temp_t2_3 = SelectionOuline_InnerLine[*arg0].field_0.vy + 
                FP_FROM((SelectionOuline_InnerLine[g_Inventory_PrevSelectionId].field_0.vy - SelectionOuline_InnerLine[*arg0].field_0.vy) * temp_t3, Q12_SHIFT);

    D_800C3B68[0][1].vx = temp_a2_2;
    D_800C3B68[0][0].vy = temp_t2_3;
    
    temp_a2_2 = SelectionOuline_InnerLine[*arg0].field_0.vy + SelectionOuline_InnerLine[*arg0].field_4.vy + 
                FP_FROM(((SelectionOuline_InnerLine[g_Inventory_PrevSelectionId].field_0.vy + SelectionOuline_InnerLine[g_Inventory_PrevSelectionId].field_4.vy) - 
                (SelectionOuline_InnerLine[*arg0].field_0.vy + SelectionOuline_InnerLine[*arg0].field_4.vy)) * temp_t3, Q12_SHIFT);

    D_800C3B68[0][1].vy = temp_a2_2;

    ot0_7 = SelectionOuline_InnerLine[*arg0].field_0.vx + SelectionOuline_InnerLine[*arg0].field_4.vx + 
            FP_FROM(((SelectionOuline_InnerLine[g_Inventory_PrevSelectionId].field_0.vx + SelectionOuline_InnerLine[g_Inventory_PrevSelectionId].field_4.vx) - 
            (SelectionOuline_InnerLine[*arg0].field_0.vx + SelectionOuline_InnerLine[*arg0].field_4.vx)) * temp_t3, Q12_SHIFT);

    D_800C3B68[0][2].vy = temp_a2_2;
    D_800C3B68[0][3].vy = temp_t2_3;
    D_800C3B68[0][2].vx = ot0_7;
    D_800C3B68[0][3].vx = ot0_7;

    if (*arg0 == 8 || g_GameWork.gameStateStep_598[1] == 0xF)
    {
        poly_g4 = (POLY_G4*)GsOUT_PACKET_P;

        setPolyG4(poly_g4);
        setSemiTrans(poly_g4, 1);

        if (D_800AE190 < 0x21) 
        {
            setRGB0(poly_g4,
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10),
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10),
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10));
            setRGB1(poly_g4, 
                    (D_800AE190 >= 0x20) ? 0xFE : (D_800AE190 * 8),
                    (D_800AE190 >= 0x20) ? 0xFE : (D_800AE190 * 8),
                    (D_800AE190 >= 0x20) ? 0xFE : (D_800AE190 * 8));
            setRGB2(poly_g4, 
                    (D_800AE190 >= 8) ? 0xFE : (D_800AE190 * 32),
                    (D_800AE190 >= 8) ? 0xFE : (D_800AE190 * 32),
                    (D_800AE190 >= 8) ? 0xFE : (D_800AE190 * 32));
            setRGB3(poly_g4, 
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10),
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10),
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10));
        } 
        else 
        {
            setRGB0(poly_g4,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0);
            setRGB1(poly_g4, 
                    (D_800AE190 < 0x40) ? ((0x40 - D_800AE190) * 8) : 0,
                    (D_800AE190 < 0x40) ? ((0x40 - D_800AE190) * 8) : 0,
                    (D_800AE190 < 0x40) ? ((0x40 - D_800AE190) * 8) : 0);
            setRGB2(poly_g4, 
                    (D_800AE190 < 0x28) ? ((0x28 - D_800AE190) * 32) : 0,
                    (D_800AE190 < 0x28) ? ((0x28 - D_800AE190) * 32) : 0,
                    (D_800AE190 < 0x28) ? ((0x28 - D_800AE190) * 32) : 0);
            setRGB3(poly_g4, 
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0);
        }

        setXY4(poly_g4,
               D_800C3B68[3][0].vx + 1, D_800C3B68[3][0].vy + 2,
               D_800C3B68[3][1].vx + 1, D_800C3B68[3][1].vy,
               D_800C3B68[3][3].vx,     D_800C3B68[3][3].vy + 2,
               D_800C3B68[3][3].vx,     D_800C3B68[3][1].vy);

        addPrim(&ot1->org[5], poly_g4);
        GsOUT_PACKET_P = (PACKET*)poly_g4 + sizeof(POLY_G4);

        Gfx_Primitive2dTextureSet(0, 0, 5, 2);

        if ((D_800AE190 >= 0x21 && *arg0 == 8) || (D_800AE190 < 0x21 && g_GameWork.gameStateStep_598[1] == 0xF))
        {
            for (i = 0; i < 2; i++)
            {
                poly_ft4 = (POLY_FT4*)GsOUT_PACKET_P;
                setPolyFT4(poly_ft4);
                poly_ft4->clut = getClut(g_ItemInspectionImg.clutX, g_ItemInspectionImg.clutY);
                setRGB0(poly_ft4, 0x80, 0x80, 0x80);

                if (i != 0) 
                {
                    poly_ft4->tpage = 0x86;
                    setUV4(poly_ft4,
                           0x20, 0x10,
                           0x20, 0xFF,
                           0xC0, 0x10,
                           0xC0, 0xFF);
                    setXY4(poly_ft4,
                           (u16)(D_800C3B68[3][0].vx + (((-(D_800C3B68[3][0].vx + 4) + D_800C3B68[3][3].vx) >> 1) + 1)), D_800C3B68[3][0].vy + 2,
                           (u16)(D_800C3B68[3][1].vx + (((-(D_800C3B68[3][1].vx + 4) + D_800C3B68[3][3].vx) >> 1) + 1)), D_800C3B68[3][1].vy,
                           D_800C3B68[3][3].vx,                                                                          D_800C3B68[3][3].vy + 2,
                           D_800C3B68[3][3].vx,                                                                          D_800C3B68[3][1].vy);
                }
                else
                {
                    poly_ft4->tpage = 0x85;
                    setUV4(poly_ft4,
                           0,    0x10,
                           0,    0xFF,
                           0xA0, 0x10,
                           0xA0, 0xFF);
                    setXY4(poly_ft4,
                           D_800C3B68[3][0].vx + 1,                                                                      D_800C3B68[3][0].vy + 2,
                           D_800C3B68[3][1].vx + 1,                                                                      D_800C3B68[3][1].vy,
                           (u16)(D_800C3B68[3][0].vx + ((-(D_800C3B68[3][0].vx + 4) + (D_800C3B68[3][3].vx) >> 1) + 2)), D_800C3B68[3][3].vy + 2,
                           (u16)(D_800C3B68[3][1].vx + ((-(D_800C3B68[3][1].vx + 4) + (D_800C3B68[3][3].vx) >> 1) + 2)), D_800C3B68[3][1].vy);
                }

                addPrim(&ot1->org[5], poly_ft4);
                GsOUT_PACKET_P = (PACKET*)poly_ft4 + sizeof(POLY_FT4);
            }
        }
    }

    for (j = 0; j < 4; j++)
    {
        for (i = 0; i < 4; i++) 
        {
            line_g2 = (LINE_G2*)GsOUT_PACKET_P;
            setLineG2(line_g2);

            setRGB0(line_g2, 0x60 - (0x20 * j), 0x60 - (0x20 * j), 0xFF);
            setRGB1(line_g2, 0x60 - (0x20 * j), 0x60 - (0x20 * j), 0xFF);
            setXY2(line_g2,
                   D_800C3B68[j][i].vx, D_800C3B68[j][i].vy,
                   D_800C3B68[j][(i + 1) & 0x3].vx, D_800C3B68[j][(i + 1) & 0x3].vy);

            addPrim(&ot0->org[7], line_g2);
            GsOUT_PACKET_P = (PACKET*)line_g2 + sizeof(LINE_G2);
        }

        for (i = 1; i < 4; i += 2)
        {
            line_g2 = (LINE_G2*)GsOUT_PACKET_P;
            setLineG2(line_g2);

            setRGB0(line_g2, 0x60 - (0x20 * j), 0x60 - (0x20 * j), 0xFF);
            setRGB1(line_g2, 0x60 - (0x20 * j), 0x60 - (0x20 * j), 0xFF);
            setXY2(line_g2,
                   D_800C3B68[j][i].vx,             D_800C3B68[j][i].vy + 1,
                   D_800C3B68[j][(i + 1) & 0x3].vx, D_800C3B68[j][(i + 1) & 0x3].vy + 1);

            addPrim(&ot1->org[7], line_g2);
            GsOUT_PACKET_P = (PACKET*)line_g2 + sizeof(LINE_G2);
        }
    }

    if (g_Gfx_Inventory_SelectionBordersDraw != 8)
    {
        return;
    }

    for (i = 0; i < 6; i++)
    {
        line_g2 = (LINE_G2*)GsOUT_PACKET_P;
        setLineG2(line_g2);

        setRGB0(line_g2, -0x50 - spA0, -0x50 - spA0, 0xFF);
        setRGB1(line_g2, spA0 + 0x70, spA0 + 0x70, 0xFF);

        if (i / 3)
        {
            setXY2(line_g2, SelectionOuline_ConerLines[*arg0].field_4.vx,
                   (i == 4) ? (SelectionOuline_ConerLines[*arg0].field_4.vy - 1) : SelectionOuline_ConerLines[*arg0].field_4.vy,
                   (i != 5) ? (SelectionOuline_ConerLines[*arg0].field_4.vx - (SelectionOuline_InnerLine[*arg0].field_4.vx >> 1)) : SelectionOuline_ConerLines[*arg0].field_4.vx,
                   (i == 5) ? (SelectionOuline_ConerLines[*arg0].field_4.vy - (SelectionOuline_InnerLine[*arg0].field_4.vy >> 1)) : 
                   (i == 4) ? (SelectionOuline_ConerLines[*arg0].field_4.vy - 1) : SelectionOuline_ConerLines[*arg0].field_4.vy);
        }
        else
        {
            setXY2(line_g2, SelectionOuline_ConerLines[*arg0].field_0.vx,
                   (i == 1) ? (SelectionOuline_ConerLines[*arg0].field_0.vy - 1) : SelectionOuline_ConerLines[*arg0].field_0.vy,
                   (i != 2) ? (SelectionOuline_ConerLines[*arg0].field_0.vx + (SelectionOuline_InnerLine[*arg0].field_0.vx >> 1)) : SelectionOuline_ConerLines[*arg0].field_0.vx,
                   (i == 2) ? (SelectionOuline_ConerLines[*arg0].field_0.vy + (SelectionOuline_InnerLine[*arg0].field_0.vy >> 1)) : 
                   (i == 1) ? (SelectionOuline_ConerLines[*arg0].field_0.vy - 1) : SelectionOuline_ConerLines[*arg0].field_0.vy);
        }

        addPrim(&ot0->org[7], line_g2);
        GsOUT_PACKET_P = (PACKET*)line_g2 + sizeof(LINE_G2);
    }  
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/items/item_screens_3", Gfx_Inventory_2dBackgroundDraw); // 0x8004FBCC
#endif

// TODO: RODATA migration.
#ifdef NON_MATCHING
static inline s16 GetUvOrRandom()
{
    if (D_800AE198 == 1) 
    {
        D_800AE1A8 = Rng_Rand16() % 134;
        return D_800AE1A8;
    }
    else
    {
        return D_800AE1A8 & 0xFF;
    }
}

void Gfx_Inventory_HealthStatusDraw() 
{
    s32       tempOverlayY;
    s16       overlayYPos;
    s32       health;
    s32       healthSegment;
    s16       healthStage;
    s32       i;
    u8        greenVal;
    u8        redVal;
    GsOT*     ot;
    POLY_FT4* poly_ft4;
    POLY_G4*  poly_g4;
    DR_TPAGE* tPage;

    u8 D_80027F04[] =
    { 
        0xFF, 0x00, 0x00, 0x00, 
        0xFF, 0xA0, 0x00, 0x00, 
        0xa0, 0xFF, 0x00, 0x00, 
        0x00, 0xFF, 0x00, 0x00 
    };

    ot     = &g_ObjectTable0[g_ObjectTableIdx];
    health = g_SysWork.player_4C.chara_0.health_B0;

    if (health < FP_FLOAT_TO(10.0f, Q12_SHIFT))
    {
        healthStage = 3;
    } 
    else if (health < FP_FLOAT_TO(50.0f, Q12_SHIFT))
    {
        healthStage = 2;
    }
    else
    {
        healthStage = 1;
    }

    healthStage                          += g_Inventory_HealthStatusScanlineTimer;
    g_Inventory_HealthStatusScanlineTimer = healthStage % 164;

    for (i = 0; i < 3; i++)
    {
        if (i != 1 || g_Inventory_HealthStatusScanlineTimer >= 30)
        {
            if (i == 2)
            {
                if (g_SysWork.player_4C.chara_0.health_B0 != FP_FLOAT_TO(100.0f, Q12_SHIFT) &&
                    ((Rng_Rand16() % ((g_SysWork.player_4C.chara_0.health_B0 >> 13) + 2) == 0) || D_800AE198 != 0))
                {
                    D_800AE198++;

                    if (D_800AE198 == 4) 
                    {
                        D_800AE198 = 0;
                    }
                }
                else
                {
                    continue;
                }
            } 

            poly_ft4 = (POLY_FT4*)GsOUT_PACKET_P;
            setPolyFT4(poly_ft4);
            poly_ft4->tpage = 159;
            poly_ft4->clut  = getClut(g_HealthPortraitImg.clutX, g_HealthPortraitImg.clutY);
            setRGB0(poly_ft4, 0x80, 0x80, 0x80);

            switch (i) 
            {
                case 0:
                    setUV4(poly_ft4,
                           40, 103,
                           40, 237,
                           124, 103,
                           124, 237);
                    setXY4(poly_ft4,
                           -138, -184,
                           -138, -50,
                           -54, -184,
                           -54, -50);
                    break;

                case 1:
                    setUV4(poly_ft4,
                           40,  g_Inventory_HealthStatusScanlineTimer + 73,
                           40,  g_Inventory_HealthStatusScanlineTimer + 75,
                           124, g_Inventory_HealthStatusScanlineTimer + 73,
                           124, g_Inventory_HealthStatusScanlineTimer + 75);
                    setXY4(poly_ft4,
                           -136, g_Inventory_HealthStatusScanlineTimer - 214,
                           -136, g_Inventory_HealthStatusScanlineTimer - 212,
                           -52,  g_Inventory_HealthStatusScanlineTimer - 214,
                           -52,  g_Inventory_HealthStatusScanlineTimer - 212);

                    if (g_Inventory_HealthStatusColorGradientTimer == 0)
                    {
                        g_Inventory_HealthStatusScanlinePosition = poly_ft4->y0;
                    }
                    break;

                case 2:
                    setUV4(poly_ft4,
                           40,  GetUvOrRandom() + 103,
                           40,  D_800AE1A8 + 105,
                           124, D_800AE1A8 + 103,
                           124, D_800AE1A8 + 105);
                    setXY4(poly_ft4,
                           -136, D_800AE1A8 - 184,
                           -136, D_800AE1A8 - 182,
                           -52,  D_800AE1A8 - 184,
                           -52,  D_800AE1A8 - 182);
                    break;
            }

            addPrim((u8*)ot->org - (-8156 + (i * 4)), poly_ft4);
            GsOUT_PACKET_P = (PACKET*)poly_ft4 + sizeof(POLY_FT4);
        }
    }

    poly_g4 = (POLY_G4*)GsOUT_PACKET_P;

    setPolyG4(poly_g4);
    setSemiTrans(poly_g4, 1);
    setRGB0(poly_g4, 0xFF, 0xFF, 0xFF);
    setRGB1(poly_g4, 0, 0, 0);
    setRGB2(poly_g4, 0xFF, 0xFF, 0xFF);
    setRGB3(poly_g4, 0, 0, 0);
    setXY4(poly_g4,
           -136, g_Inventory_HealthStatusScanlineTimer - 212,
           -136, g_Inventory_HealthStatusScanlineTimer - 182,
           -54,  g_Inventory_HealthStatusScanlineTimer - 212,
           -54,  g_Inventory_HealthStatusScanlineTimer - 182);

    tempOverlayY = poly_g4->y0 - 2;

    if (tempOverlayY >= -214)
    {
        if (tempOverlayY >= (g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)))
        {
            overlayYPos = tempOverlayY;
        }
        else
        {
            overlayYPos = -52;
        }
    } 
    else 
    {
        overlayYPos = -52;
    }

    addPrim(&ot->org[2036], poly_g4);
    GsOUT_PACKET_P = (PACKET*)poly_g4 + sizeof(POLY_G4);

    tPage = (DR_TPAGE*)GsOUT_PACKET_P;
    setDrawTPage(tPage, 0, 1, 64);
    addPrim(&ot->org[2036], tPage);
    GsOUT_PACKET_P = (PACKET*)tPage + sizeof(DR_TPAGE);

    if (g_Inventory_HealthStatusScanlinePosition != -300)
    {
        healthSegment = FP_FROM(g_SysWork.player_4C.chara_0.health_B0, Q12_SHIFT);

        if (healthSegment < 39)
        {
            redVal   = D_80027F04[0];
            greenVal = D_80027F04[1];
        }
        else if (healthSegment < 0x41)
        {
            redVal   = D_80027F04[4];
            greenVal = D_80027F04[5];
        }
        else if (healthSegment < 0x55)
        {
            redVal   = D_80027F04[8];
            greenVal = D_80027F04[9];
        }
        else
        {
            redVal   = D_80027F04[12];
            greenVal = D_80027F04[13];
        }

        for (i = 0; i < 2; i++)
        {
            poly_g4 = (POLY_G4*)GsOUT_PACKET_P;
            
            setPolyG4(poly_g4);
            setRGB0(poly_g4,
                    redVal   - ((redVal   * g_Inventory_HealthStatusColorGradientTimer) >> 6),
                    greenVal - ((greenVal * g_Inventory_HealthStatusColorGradientTimer) >> 6),
                    0);
            setRGB1(poly_g4, 0, 0, 0);
            setRGB2(poly_g4,
                    redVal   - ((redVal   * g_Inventory_HealthStatusColorGradientTimer) >> 6),
                    greenVal - ((greenVal * g_Inventory_HealthStatusColorGradientTimer) >> 6),
                    0);
            setRGB3(poly_g4, 0, 0, 0);

            if (i != 0)
            {
                setXY4(poly_g4,
                    -136, ((g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)) < -182) ?
                          -182 :
                          (g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)),
                    -136, poly_g4->y0 - 16,
                    -56,  ((g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)) < -182) ?
                          -182 :
                          (g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)),
                    -56,  poly_g4->y0 - 16);
            } 
            else
            {
                setXY4(poly_g4,
                    -136, ((g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)) < -182) ?
                          -182 :
                          (g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)),
                    -136, overlayYPos,
                    -56,  ((g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)) < -182) ?
                          -182 :
                          (g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)),
                    -56,  overlayYPos);
            }

            addPrim(&ot->org[2040], poly_g4);
            GsOUT_PACKET_P = (PACKET*)poly_g4 + sizeof(POLY_G4);
        }
    }

    if (g_SysWork.player_4C.chara_0.health_B0 < FP_FLOAT_TO(10.0f, Q12_SHIFT))
    {
        healthStage = 3;
    }
    else if (g_SysWork.player_4C.chara_0.health_B0 < FP_FLOAT_TO(50.0f, Q12_SHIFT))
    {
        healthStage = 2;
    }
    else
    {
        healthStage = 1;
    }

    g_Inventory_HealthStatusColorGradientTimer = healthStage + g_Inventory_HealthStatusColorGradientTimer;
    
    if (g_Inventory_HealthStatusColorGradientTimer >= 64)
    {
        g_Inventory_HealthStatusColorGradientTimer = 0;
        g_Inventory_HealthStatusScanlinePosition   = -300;
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/items/item_screens_3", Gfx_Inventory_HealthStatusDraw); // 0x80051020
#endif

// TODO: RODATA migration.
#ifdef NON_MATCHING
void Gfx_Inventory_ItemDescriptionDraw(s32* selectedItemId) // 0x8005192C
{
    s32 temp;
    s32 i;
    s32 idx;

    DVECTOR stringPos = { 208, 200 };

    char* D_80027F14[] = 
    {
        "Can't_use_it_here.",
        "Too_dark_to_look_at\n\t\tthe_item_here."
    };

    char* D_80027F94[] =
    {
        "Stock:",
        "==On==",
        "==Off==",
        "==Use_OK==",
        "==Use_OK?==",
        "==Use_NG==",
        "Fuel:"
    };

    switch (*selectedItemId)
    {
        case 0:
        case 5:
        case 7:
        case 8:
            idx = g_SysWork.inventoryItemSelectedIdx_2351;
            break;

        default:
            idx = g_SysWork.playerCombatInfo_38.field_12;
            break;
    }
    
    if (D_800AE185 != ((g_SavegamePtr->items_0[idx].id_0 >> 5) - 1) || 
        D_800AE186 != (g_SavegamePtr->items_0[idx].id_0 & 0x1F))
    {
        g_SysWork.field_10               = 0;
        g_SysWork.timer_2C               = 0;
        g_SysWork.field_14               = 0;
        g_Inventory_ItemNameTimer        = 0;
        g_Inventory_DescriptionRollTimer = 0;
        D_800AE18C                       = 0;
        D_800AE18E                       = 0;
        D_800AE178                       = 0;
    }
    
    if (idx != -1 && *selectedItemId != 2 && *selectedItemId != 3 && *selectedItemId != 4)
    {
        for (i = 0; i < g_SavegamePtr->inventoryItemSpaces_AB; i++) 
        {
            if (i == idx)
            {    
                if (idx + 1 >= 10)
                {
                    Gfx_StringSetPosition(45, 184);
                }
                else
                {
                    Gfx_StringSetPosition(55, 184);
                }
                
                Gfx_StringDrawInt(2, i + 1);
                i = g_SavegamePtr->inventoryItemSpaces_AB;
            }
        }
    }
    
    if ((g_Inventory_EquippedItem >> 5) == 5 && g_Inventory_EquippedItem != InventoryItemId_HyperBlaster)
    {
        Gfx_StringSetPosition(122, 30);
        Gfx_StringDraw(D_80027F94[0], 10);
        
        for (i = 0; i < g_SavegamePtr->inventoryItemSpaces_AB; i++) 
        {
            if (g_Inventory_EquippedItem == g_SavegamePtr->items_0[i].id_0) 
            {
                if (g_SavegamePtr->items_0[i].count_1 >= 10) 
                {
                    Gfx_StringSetPosition(178, 30);
                }
                else
                {
                    Gfx_StringSetPosition(188, 30);
                }
                Gfx_StringDrawInt(2, g_SavegamePtr->items_0[i].count_1);
            }
        }
    }
    
    temp = *selectedItemId;
    
    if (temp < 0 || (temp >= 2 && (*selectedItemId >= 9 || temp < 5)) ||
        g_SavegamePtr->items_0[idx].id_0 == 0xFF)
    {
        return;
    }
    
    switch (g_SavegamePtr->items_0[idx].id_0) 
    {
        case InventoryItemId_Flashlight:
            Gfx_StringSetPosition(stringPos.vx, stringPos.vy);
            if (func_8003ED64() == 0)
            {
                Gfx_StringDraw(D_80027F94[2], 10);
            } 
            else 
            {
                Gfx_StringDraw(D_80027F94[1], 10);
            }
            break;
            
        case InventoryItemId_PocketRadio:
            Gfx_StringSetPosition(stringPos.vx, stringPos.vy);
            if (g_SavegamePtr->flags_AC & 1) 
            {
                Gfx_StringDraw(D_80027F94[1], 10);
            } 
            else 
            {
                Gfx_StringDraw(D_80027F94[2], 10);
            }
            break;
            
        case InventoryItemId_HyperBlaster:
            Gfx_StringSetPosition(stringPos.vx - 16, stringPos.vy);

            switch (Inventory_HyperBlasterFunctionalTest()) 
            {
                case 2: // If HyperBlaster connected (Port 1).
                    Gfx_StringDraw(D_80027F94[3], 10);
                    break;
                
                case 1: // If HyperBlaster connected (Port 2).
                    Gfx_StringDraw(D_80027F94[4], 10);
                    break;
                
                case 0: // If HyperBlaster unlocked by finishing the game.
                    Gfx_StringDraw(D_80027F94[5], 10);
                    break;
            }
            break;
        
        case InventoryItemId_HealthDrink:
        case InventoryItemId_FirstAidKit:
        case InventoryItemId_Ampoule:
        case InventoryItemId_Handgun:
        case InventoryItemId_HuntingRifle:
        case InventoryItemId_Shotgun:
        case InventoryItemId_HandgunBullets:
        case InventoryItemId_RifleShells:
        case InventoryItemId_ShotgunShells:
            Gfx_StringSetPosition(stringPos.vx, stringPos.vy);
            Gfx_StringDraw(D_80027F94[0], 10);
            
            if (g_SavegamePtr->items_0[idx].id_0 != 0xFF) 
            {
                if (g_SavegamePtr->items_0[idx].count_1 >= 100) 
                {
                    Gfx_StringSetPosition(260, 200);
                } 
                else if (g_SavegamePtr->items_0[idx].count_1 >= 10) 
                {
                    Gfx_StringSetPosition(270, 200);
                }
                else
                {
                    Gfx_StringSetPosition(280, 200);
                }
                Gfx_StringDrawInt(3, g_SavegamePtr->items_0[idx].count_1);
            }
            break;
    }
        
    Gfx_StringSetColor(ColorId_White);

    D_800AE185 = (g_SavegamePtr->items_0[idx].id_0 >> 5) - 1;
    D_800AE186 = g_SavegamePtr->items_0[idx].id_0 & 0x1F;
        
    switch (g_SysWork.field_10) 
    {
        case 0:
            g_Inventory_ItemNameTimer += 1;
            Gfx_StringSetPosition(68, 200);
            if (Gfx_StringDraw(D_800ADB60[g_SavegamePtr->items_0[idx].id_0 - 32], g_Inventory_ItemNameTimer) == true) 
            {
                g_Inventory_ItemNameTimer = 100;
                g_SysWork.timer_2C = 0;
                g_SysWork.field_14 = 0;
                g_SysWork.field_10 += 1;
            }
            break;
            
        case 1:
            g_Inventory_DescriptionRollTimer += 2;
            Gfx_StringSetPosition(68, 200);
            Gfx_StringDraw(D_800ADB60[g_SavegamePtr->items_0[idx].id_0 - 32], 100);
            
            if (idx == g_Inventory_SelectedItemIdx) 
            {
                g_Inventory_ItemNameTimer = 0;
            }
            
            Gfx_StringSetPosition(30, 232);
            
            if (Gfx_StringDraw(D_800ADE6C[g_SavegamePtr->items_0[idx].id_0 - 32], g_Inventory_DescriptionRollTimer) == true)
            {
                g_Inventory_DescriptionRollTimer = 100;
                g_SysWork.timer_2C = 0;
                g_SysWork.field_14 = 0;
                g_SysWork.field_10 += 1;
            }
            break;

        case 2:
        case 3:
        case 4:
            Gfx_StringSetPosition(68, 200);
            Gfx_StringDraw(D_800ADB60[g_SavegamePtr->items_0[idx].id_0 - 32], 100);
            Gfx_StringSetPosition(30, 232);

            switch (g_SysWork.field_10) 
            {
                case 2:
                    Gfx_StringDraw(D_800ADE6C[g_SavegamePtr->items_0[idx].id_0 - 32], 100);
                    break;
                
                case 3:
                    Gfx_StringDraw(D_80027F14[0], 100);
                    break;
                
                case 4:
                    Gfx_StringDraw(D_80027F14[1], 100);
                    break;
            }
            
            if (idx == g_Inventory_SelectedItemIdx) 
            {
                g_Inventory_ItemNameTimer = 0;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/items/item_screens_3", Gfx_Inventory_ItemDescriptionDraw); // 0x8005192C
#endif

void Gfx_Primitive2dTextureSet(s32 x, s32 y, s32 otIdx, s32 abr) // 0x80052088
{
    GsOT*     ot0;
    GsOT*     ot1;
    s32       idx   = g_ObjectTableIdx;
    DR_TPAGE* tPage = (DR_TPAGE*)GsOUT_PACKET_P;

    setDrawTPage(tPage, 0, 1, getTPage(0, abr, x, y));

    ot1 = &g_ObjectTable1[idx];
    ot0 = &g_ObjectTable0[idx];

    if (abr < 4)
    {
        addPrim(&ot1->org[otIdx], tPage);
    }
    else
    {
        addPrim(&ot0->org[otIdx], tPage);
    }

    GsOUT_PACKET_P = (PACKET*)tPage + sizeof(DR_TPAGE);
}

void Gfx_Results_ItemsDisplay() // 0x800521A8
{
    GsDOBJ2* ptr;
    s32      i;

    for (i = 0, ptr = g_Items_ItemsModelData; i < 6; i++, ptr++)
    {
        if ((D_800C3E40 >> i) & (1 << 0))
        {
            Gfx_Items_ItemRotate(&g_Items_Items3dData1[i].param->rotate, &g_Items_Items3dData1[i]);
            func_800548D8(i);
            GsSetFlatLight(0, &g_Items_ItemsLightingData[i][0]);
            GsSetFlatLight(1, &g_Items_ItemsLightingData[i][1]);
            func_8004BD74(i, ptr, 3);
        }
    }
}

// TODO: RODATA migration.
#ifdef NON_MATCHING
void Gfx_Results_ItemsPosition() // 0x8005227C
{
    s32 i;

    SVECTOR vecs[] = // 0x80027FB0
    {
        { 0x0000, 0xFCC0, 0x1400, 0x0000 },
        { 0xFCF8, 0xFE80, 0x1400, 0x0000 },
        { 0x0308, 0xFE80, 0x1400, 0x0000 },
        { 0xFCF8, 0x0200, 0x1400, 0x0000 },
        { 0x0308, 0x0200, 0x1400, 0x0000 },
        { 0x0000, 0x03C0, 0x1400, 0x0000 },
    };

    if (g_SavegamePtr->clearGameCount_24A == 0)
    {
        g_SavegamePtr->clearGameCount_24A = 1;
    }

    for (i = 0; i < 6; i++)
    {
        if ((D_800C3E40 >> i) & (1 << 0))
        {
            g_Items_Items3dData1[i].coord.t[0]      = vecs[i].vx;
            g_Items_Items3dData1[i].coord.t[1]      = vecs[i].vy;
            g_Items_Items3dData1[i].coord.t[2]      = vecs[i].vz;
            g_Items_Items3dData0[i].rotation_10.vx  = 0x200;
            g_Items_Items3dData0[i].rotation_10.vz  = 0x200;
            g_Items_Items3dData0[i].scale_0.vz      = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[i].scale_0.vy      = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[i].scale_0.vx      = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[i].rotation_10.vy += 8;
        }
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/items/item_screens_3", Gfx_Results_ItemsPosition); // 0x8005227C
#endif

/** Name could be inaccurate.
 * Breaking this function call makes items no longer rotate,
 * and trying to scroll through the items will softlock the game.
 * If the user breaks the function before entering the
 * inventory, all items will be at the center of the screen
 * and the equiped item will appear frozen in its base pose.
 * If the user doesn't try scrolling through items, they
 * will be able to navigate through other functions. However,
 * messing with commands also will softlock the game.
 */
INCLUDE_ASM("asm/bodyprog/nonmatchings/items/item_screens_3", Inventory_PlayerItemScroll); // 0x800523D8

void func_800539A4(s32 scrollDirection, s32 arg1) // 0x800539A4
{
	#define RIGHT_SCROLL 7
	#define LEFT_SCROLL -7
	
    s32 sp10[10];
    s32 i;
    s32 var_a3_2;
    s32 var_s0;

    var_s0 = 0;

    for (i = 0; i < 10; i++)
    {
        sp10[i] = D_800C3E18[i];
    }

    var_a3_2 = (scrollDirection != 0) ? LEFT_SCROLL : RIGHT_SCROLL;
    var_a3_2 = (arg1 + var_a3_2 + g_SavegamePtr->inventoryItemSpaces_AB) % g_SavegamePtr->inventoryItemSpaces_AB;

    for (i = 0; i < 7; i++)
    {
        if (sp10[i] == var_a3_2)
        {
            var_s0 = i;
            i      = 7;
        }
    }

    sp10[var_s0] = arg1;

    if (g_SavegamePtr->items_0[arg1].id_0 != 0xFF)
    {
        for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
        {
            if (g_SavegamePtr->items_0[arg1].id_0 == g_Item_MapLoadableItems[i])
            {
                Gfx_Items_Display(FS_BUFFER_8, var_s0, i);
                func_8005487C(var_s0);
                i = INVENTORY_ITEM_COUNT_MAX;
            }
        }
    }

    for (i = 0; i < 10; i++)
    {
        D_800C3E18[i] = sp10[i];
    }
}

/** @note For better comprehension related to file handling
 * of inventory items.
 *
 * - `GameFs_UniqueItemModelLoad` loads model of items individually.
 * - `GameFs_MapItemsModelLoad` and `GameFs_MapItemsTextureLoad` load packs of textures and
 *   models of items, though while `GameFs_UniqueItemModelLoad` seems to load
 *   them individually based on what is being passed as argument,
 * - `GameFs_MapItemsModelLoad` and `GameFs_MapItemsTextureLoad` load the packs based on the 
 *   map being loaded.
 */

// TODO: RODATA migration.
#ifdef NON_MATCHING
void GameFs_UniqueItemModelLoad(u8 itemId) // 0x80053B08
{
    switch (itemId)
    {
        case InventoryItemId_HealthDrink:
            Fs_QueueStartRead(FILE_ITEM_UNQ21_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Ampoule:
            Fs_QueueStartRead(FILE_ITEM_UNQ22_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_HouseKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ41_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfLion:
            Fs_QueueStartRead(FILE_ITEM_UNQ42_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfWoodman:
            Fs_QueueStartRead(FILE_ITEM_UNQ43_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfScarecrow:
            Fs_QueueStartRead(FILE_ITEM_UNQ44_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_LibraryReserveKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ45_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_ClassroomKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ46_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KGordonKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ47_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_DrawbridgeKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ48_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_BasementKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ49_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_BasementStoreroomKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ4A_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_ExaminationRoomKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ4B_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_AntiqueShopKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ4C_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_SewerKey:
        case InventoryItemId_SewerExitKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ4D_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfOphiel:
            Fs_QueueStartRead(FILE_ITEM_UNQ4E_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfHagith:
            Fs_QueueStartRead(FILE_ITEM_UNQ4F_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfPhaleg:
            Fs_QueueStartRead(FILE_ITEM_UNQ50_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfBethor:
            Fs_QueueStartRead(FILE_ITEM_UNQ51_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfAratron:
            Fs_QueueStartRead(FILE_ITEM_UNQ52_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_NoteToSchool:
            Fs_QueueStartRead(FILE_ITEM_UNQ53_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_NoteDoghouse:
            Fs_QueueStartRead(FILE_ITEM_UNQ54_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PictureCard:
            Fs_QueueStartRead(FILE_ITEM_UNQ55_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_ChannelingStone:
            Fs_QueueStartRead(FILE_ITEM_UNQ56_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Chemical:
            Fs_QueueStartRead(FILE_ITEM_UNQ60_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_GoldMedallion:
            Fs_QueueStartRead(FILE_ITEM_UNQ61_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_SilverMedallion:
            Fs_QueueStartRead(FILE_ITEM_UNQ62_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_RubberBall:
            Fs_QueueStartRead(FILE_ITEM_UNQ63_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Flauros:
            Fs_QueueStartRead(FILE_ITEM_UNQ64_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlasticBottle:
            Fs_QueueStartRead(FILE_ITEM_UNQ65_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_UnknownLiquid:
            Fs_QueueStartRead(FILE_ITEM_UNQ66_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlateOfHatter:
            Fs_QueueStartRead(FILE_ITEM_UNQ67_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlateOfCat:
            Fs_QueueStartRead(FILE_ITEM_UNQ68_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlateOfQueen:
            Fs_QueueStartRead(FILE_ITEM_UNQ69_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlateOfTurtle:
            Fs_QueueStartRead(FILE_ITEM_UNQ6A_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_BloodPack:
            Fs_QueueStartRead(FILE_ITEM_UNQ6B_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_DisinfectingAlcohol:
            Fs_QueueStartRead(FILE_ITEM_UNQ6C_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Lighter:
            Fs_QueueStartRead(FILE_ITEM_UNQ6D_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_VideoTape:
            Fs_QueueStartRead(FILE_ITEM_UNQ6E_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KaufmannKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ70_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Receipt:
            Fs_QueueStartRead(FILE_ITEM_UNQ71_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_SafeKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ72_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Magnet:
            Fs_QueueStartRead(FILE_ITEM_UNQ73_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_MotorcycleKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ74_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_BirdCageKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ75_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Pliers:
            Fs_QueueStartRead(FILE_ITEM_UNQ76_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Screwdriver:
            Fs_QueueStartRead(FILE_ITEM_UNQ77_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Camera:
            Fs_QueueStartRead(FILE_ITEM_UNQ78_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_RingOfContract:
            Fs_QueueStartRead(FILE_ITEM_UNQ79_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_StoneOfTime:
            Fs_QueueStartRead(FILE_ITEM_UNQ7A_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_AmuletOfSolomon:
            Fs_QueueStartRead(FILE_ITEM_UNQ7B_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_CrestOfMercury:
            Fs_QueueStartRead(FILE_ITEM_UNQ7C_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Ankh:
            Fs_QueueStartRead(FILE_ITEM_UNQ7D_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_DaggerOfMelchior:
            Fs_QueueStartRead(FILE_ITEM_UNQ7E_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_DiskOfOuroboros:
            Fs_QueueStartRead(FILE_ITEM_UNQ7F_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KitchenKnife:
            Fs_QueueStartRead(FILE_ITEM_UNQ80_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_SteelPipe:
            Fs_QueueStartRead(FILE_ITEM_UNQ81_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Hammer:
            Fs_QueueStartRead(FILE_ITEM_UNQ82_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Chainsaw:
            Fs_QueueStartRead(FILE_ITEM_UNQ83_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Axe:
            Fs_QueueStartRead(FILE_ITEM_UNQ84_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_RockDrill:
            Fs_QueueStartRead(FILE_ITEM_UNQ85_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Katana:
            Fs_QueueStartRead(FILE_ITEM_UNQ86_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Handgun:
            Fs_QueueStartRead(FILE_ITEM_UNQA0_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_HuntingRifle:
            Fs_QueueStartRead(FILE_ITEM_UNQA1_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Shotgun:
            Fs_QueueStartRead(FILE_ITEM_UNQA2_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_HyperBlaster:
            Fs_QueueStartRead(FILE_ITEM_UNQA3_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_HandgunBullets:
            Fs_QueueStartRead(FILE_ITEM_UNQC0_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_RifleShells:
            Fs_QueueStartRead(FILE_ITEM_UNQC1_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_ShotgunShells:
            Fs_QueueStartRead(FILE_ITEM_UNQC2_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Flashlight:
            Fs_QueueStartRead(FILE_ITEM_UNQE0_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PocketRadio:
            Fs_QueueStartRead(FILE_ITEM_UNQE1_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_GasolineTank:
            Fs_QueueStartRead(FILE_ITEM_UNQE2_TMD, FS_BUFFER_5);
            break;

        default:
            Fs_QueueStartRead(FILE_ITEM_UNQ20_TMD, FS_BUFFER_5);
            break;
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/items/item_screens_3", GameFs_UniqueItemModelLoad); // 0x80053B08
#endif

void GameFs_Tim00TIMLoad() // 0x80053dA0
{
    if (g_SysWork.flags_2352 & (1 << 0))
    {
        return;
    }

    Fs_QueueStartReadTim(FILE_ITEM_TIM00_TIM, FS_BUFFER_1, &g_FirstAidKitItemTextureImg);
    g_SysWork.flags_2352 |= 1 << 0;
}

// TODO: RODATA migration.
#ifdef NON_MATCHING
void GameFs_MapItemsModelLoad(u32 mapId) // 0x80053DFC
{
    if (!(g_SysWork.flags_2352 & (1 << 7)))
    {
        Fs_QueueStartReadTim(FILE_ITEM_TIM07_TIM, FS_BUFFER_1, &D_800A9074);
        g_SysWork.flags_2352 |= 1 << 7;
    }

    switch (mapId)
    {
        case MapOverlayId_MAP1_S00:
        case MapOverlayId_MAP1_S01:
        case MapOverlayId_MAP1_S02:
        case MapOverlayId_MAP1_S03:
        case MapOverlayId_MAP1_S05:
            if (!(g_SysWork.flags_2352 & (1 << 1)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM01_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 1);
            }
            break;

        case MapOverlayId_MAP0_S01:
        case MapOverlayId_MAP0_S02:
        case MapOverlayId_MAP1_S06:
        case MapOverlayId_MAP2_S00:
        case MapOverlayId_MAP2_S01:
        case MapOverlayId_MAP2_S02:
        case MapOverlayId_MAP2_S04:
        case MapOverlayId_MAP4_S00:
        case MapOverlayId_MAP4_S01:
        case MapOverlayId_MAP4_S02:
        case MapOverlayId_MAP4_S03:
        case MapOverlayId_MAP4_S05:
            if (!(g_SysWork.flags_2352 & (1 << 2)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM02_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 2);
            }
            break;

        case MapOverlayId_MAP3_S00:
        case MapOverlayId_MAP3_S01:
        case MapOverlayId_MAP3_S02:
        case MapOverlayId_MAP3_S03:
        case MapOverlayId_MAP3_S04:
        case MapOverlayId_MAP3_S05:
        case MapOverlayId_MAP3_S06:
        case MapOverlayId_MAP4_S04:
            if (!(g_SysWork.flags_2352 & (1 << 3)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM03_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 3);
            }
            break;

        case MapOverlayId_MAP5_S00:
        case MapOverlayId_MAP5_S01:
        case MapOverlayId_MAP5_S02:
        case MapOverlayId_MAP5_S03:
        case MapOverlayId_MAP6_S00:
        case MapOverlayId_MAP6_S01:
        case MapOverlayId_MAP6_S02:
        case MapOverlayId_MAP6_S03:
        case MapOverlayId_MAP6_S04:
            if (!(g_SysWork.flags_2352 & (1 << 4)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM04_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 4);
            }
            break;

        case MapOverlayId_MAP7_S00:
        case MapOverlayId_MAP7_S01:
            if (!(g_SysWork.flags_2352 & (1 << 5)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM05_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 5);
            }
            break;

        case MapOverlayId_MAP7_S02:
        case MapOverlayId_MAP7_S03:
            if (!(g_SysWork.flags_2352 & (1 << 6)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM06_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 6);
            }
            break;

        case 0:
            break;
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/items/item_screens_3", GameFs_MapItemsModelLoad); // 0x80053DFC
#endif

// TODO: RODATA migration.
#ifdef NON_MATCHING
void GameFs_MapItemsTextureLoad(s32 mapId) // 0x80054024
{
    switch (mapId)
    {
        case MapOverlayId_MAP0_S00:
            Fs_QueueStartRead(FILE_ITEM_IT_000_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP0_S01:
        case MapOverlayId_MAP0_S02:
        case MapOverlayId_MAP1_S06:
        case MapOverlayId_MAP2_S00:
        case MapOverlayId_MAP2_S01:
        case MapOverlayId_MAP2_S02:
        case MapOverlayId_MAP2_S04:
        case MapOverlayId_MAP4_S00:
        case MapOverlayId_MAP4_S01:
        case MapOverlayId_MAP4_S02:
        case MapOverlayId_MAP4_S03:
        case MapOverlayId_MAP4_S05:
            Fs_QueueStartRead(FILE_ITEM_IT_001_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP1_S00:
        case MapOverlayId_MAP1_S01:
        case MapOverlayId_MAP1_S02:
        case MapOverlayId_MAP1_S03:
        case MapOverlayId_MAP1_S05:
            Fs_QueueStartRead(FILE_ITEM_IT_002_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP3_S00:
        case MapOverlayId_MAP3_S01:
        case MapOverlayId_MAP3_S02:
        case MapOverlayId_MAP3_S03:
        case MapOverlayId_MAP3_S04:
        case MapOverlayId_MAP3_S05:
        case MapOverlayId_MAP3_S06:
        case MapOverlayId_MAP4_S04:
            Fs_QueueStartRead(FILE_ITEM_IT_003_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP5_S00:
        case MapOverlayId_MAP5_S01:
        case MapOverlayId_MAP5_S02:
        case MapOverlayId_MAP5_S03:
        case MapOverlayId_MAP6_S00:
        case MapOverlayId_MAP6_S01:
        case MapOverlayId_MAP6_S02:
        case MapOverlayId_MAP6_S03:
        case MapOverlayId_MAP6_S04:
            Fs_QueueStartRead(FILE_ITEM_IT_004_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP7_S00:
        case MapOverlayId_MAP7_S01:
            Fs_QueueStartRead(FILE_ITEM_IT_005_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP7_S02:
        case MapOverlayId_MAP7_S03:
            Fs_QueueStartRead(FILE_ITEM_IT_006_TMD, FS_BUFFER_8);
            break;
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/items/item_screens_3", GameFs_MapItemsTextureLoad); // 0x80054024
#endif

void func_800540A4(s8 arg0) // 0x800540A4
{
    s32 i;
    s32 j;

    if (g_SysWork.playerCombatInfo_38.field_12 != NO_VALUE)
    {
        g_SavegamePtr->items_0[g_SysWork.playerCombatInfo_38.field_12].count_1 = g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10;
    }

    for (i = 0; i < g_SavegamePtr->inventoryItemSpaces_AB; i++)
    {
        if (g_SavegamePtr->items_0[i].id_0 >> 5 == 6 && 
            g_SavegamePtr->items_0[i].id_0 == (g_SavegamePtr->items_0[g_SysWork.playerCombatInfo_38.field_12].id_0 + 32))
        {
            g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11;

            if (!g_SavegamePtr->items_0[i].count_1)
            {
                g_SavegamePtr->items_0[i].id_0 = NO_VALUE;
            }

            g_SavegamePtr->inventoryItemSpaces_AB = func_8004F190(g_SavegamePtr);
            break;
        }
    }

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            D_800C3B68[i][j].vy = 0;
            D_800C3B68[i][j].vx = 0;
        }
    }

    D_800AE18C = 0;
    D_800AE18E = 0;

    Fs_QueueStartReadTim(FILE_ITEM_HEROPIC2_TIM, FS_BUFFER_1, &g_HealthPortraitImg);
}

// TODO: RODATA migration.
#ifdef NON_MATCHING
// Item rendering related.
void Gfx_Items_Render() // 0x80054200
{
    s32  temp_s5;
    s32  i;
    s32  saveItemsIdx;
    s32  inventoryItemsIdx;
    s32* var_s1;
    s32* var_s2;

    func_8004BFE8();

    D_800AE190 = 0;

    Gfx_ItemScreens_CameraSet(&D_800C3B48, &D_800C3AE8, &D_800C3B38, 0);

	/** This loops define the position, rotation and scale of the item that
	* the player has initially equipped in the inventory.
	*/
    for (i = 0; i < 10; i++)
    {
        D_800C3E18[i] = NO_VALUE;

        g_Items_Items3dData0[i].scale_0.vz     = FP_METER(1.0f);
        g_Items_Items3dData0[i].scale_0.vy     = FP_METER(1.0f);
        g_Items_Items3dData0[i].scale_0.vx     = FP_METER(1.0f);
        g_Items_Items3dData0[i].rotation_10.vz = 0;
        g_Items_Items3dData0[i].rotation_10.vy = 0;
        g_Items_Items3dData0[i].rotation_10.vx = 0;
        g_Items_Items3dData0[i].field_18.vz    = 0;
        g_Items_Items3dData0[i].field_18.vy    = 0;
        g_Items_Items3dData0[i].field_18.vx    = 0;
    }

    GameFs_TmdDataAlloc(FS_BUFFER_8);

    temp_s5 = (g_SysWork.inventoryItemSelectedIdx_2351 - 3 + g_SavegamePtr->inventoryItemSpaces_AB) % g_SavegamePtr->inventoryItemSpaces_AB;

    if (g_GameWork.gameStateStep_598[1] < 21) // If screen is inventory
    {
        for (inventoryItemsIdx = 0; inventoryItemsIdx < 7; inventoryItemsIdx++)
        {
            D_800C3E18[inventoryItemsIdx] = (temp_s5 + inventoryItemsIdx) % g_SavegamePtr->inventoryItemSpaces_AB;

            if (g_SavegamePtr->items_0[D_800C3E18[inventoryItemsIdx]].id_0 == 0xFF)
            {
                continue;
            }

            for (saveItemsIdx = 0; saveItemsIdx < INVENTORY_ITEM_COUNT_MAX; saveItemsIdx++)
            {
                if (g_SavegamePtr->items_0[D_800C3E18[inventoryItemsIdx]].id_0 == g_Item_MapLoadableItems[saveItemsIdx])
                {
                    Gfx_Items_Display(FS_BUFFER_8, inventoryItemsIdx, saveItemsIdx);
                    func_8005487C(inventoryItemsIdx);

                    saveItemsIdx = INVENTORY_ITEM_COUNT_MAX;
                }
            }
        }

        g_Inventory_EquippedItem = g_SavegamePtr->equippedWeapon_AA;

        for (i = 0; i < g_SavegamePtr->inventoryItemSpaces_AB; i++)
        {
            if (g_SavegamePtr->items_0[i].id_0 == g_Inventory_EquippedItem)
            {
                D_800C3E18[7] = i;

                i = g_SavegamePtr->inventoryItemSpaces_AB;
            }
        }

        if (g_Inventory_EquippedItemIdx != NO_VALUE) // If player has something equipped
        {
            for (saveItemsIdx = 0; saveItemsIdx < INVENTORY_ITEM_COUNT_MAX; saveItemsIdx++)
            {
                if (g_Inventory_EquippedItem == g_Item_MapLoadableItems[saveItemsIdx])
                {
                    Gfx_Items_Display(FS_BUFFER_8, 7, saveItemsIdx);
                    func_8005487C(7);

                    saveItemsIdx = INVENTORY_ITEM_COUNT_MAX;
                }
            }
        }

        g_Items_Items3dData1[7].coord.t[0] = 0;
        g_Items_Items3dData1[7].coord.t[1] = FP_METER(-0.15625f);
        g_Items_Items3dData1[7].coord.t[2] = 0;
    }
    else
    {
        u8 itemIds[] = // 0x8002848C .rodata
        {
            InventoryItemId_GasolineTank,
            InventoryItemId_Chainsaw,
            InventoryItemId_RockDrill,
            InventoryItemId_Katana,
            InventoryItemId_ChannelingStone,
            InventoryItemId_HyperBlaster
        };

        if (g_SavegamePtr->clearGameCount_24A == 0)
        {
            g_SavegamePtr->clearGameCount_24A = 1;
        }

        for (inventoryItemsIdx = 0; inventoryItemsIdx < 6; inventoryItemsIdx++)
        {
            D_800C3E18[inventoryItemsIdx] = inventoryItemsIdx;

            for (saveItemsIdx = 0; saveItemsIdx < INVENTORY_ITEM_COUNT_MAX; saveItemsIdx++)
            {
                if (itemIds[inventoryItemsIdx] == g_Item_MapLoadableItems[saveItemsIdx])
                {
                    Gfx_Items_Display(FS_BUFFER_8, inventoryItemsIdx, saveItemsIdx);
                    func_8005487C(inventoryItemsIdx);

                    saveItemsIdx = INVENTORY_ITEM_COUNT_MAX;
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/items/item_screens_3", Gfx_Items_Render); // 0x80054200
#endif

void Gfx_Items_RenderInit() // 0x80054558
{
    s32 i;

    D_800AE180                                 = 0;
    D_800AE187                                 = 0;
    g_Inventory_HealthStatusScanlineTimer      = 32;
    g_Inventory_HealthStatusColorGradientTimer = 0;
    D_800AE198                                 = 0;
    g_Inventory_HealthStatusScanlinePosition   = -300;
    g_Inventory_ItemNameTimer                  = 0;
    g_Inventory_DescriptionRollTimer           = 0;
    g_Inventory_ScrollTransitionTimer          = 0;

    for (i = 0; g_MapOverlayHeader.field_2C->field_0[i] != 0; i++)
    {
        g_Item_MapLoadableItems[i] = g_MapOverlayHeader.field_2C->field_0[i];
    }

    g_Item_MapLoadableItems[i] = 0;

    Gfx_Items_Render();
    Gfx_Items_SetAmbientLighting();
}

void Inventory_ExitAnimFixes() // 0x80054634
{
    u8 field_F;

    field_F                          = (u8)g_SysWork.playerCombatInfo_38.field_F;
    g_SavegamePtr->equippedWeapon_AA = g_Inventory_EquippedItem;

    if (g_SavegamePtr->equippedWeapon_AA)
    {
        g_SysWork.playerCombatInfo_38.field_F = g_SavegamePtr->equippedWeapon_AA + 0x80;
    }
    else
    {
        g_SysWork.playerCombatInfo_38.field_F     = NO_VALUE;
        g_SysWork.playerCombatInfo_38.isAiming_13 = 0;
    }

    func_800546A8((u8)g_SysWork.playerCombatInfo_38.field_F);
    Inventory_ExitAnimEquippedItemUpdate(&field_F);
}

// TODO: RODATA migration.
#ifdef NON_MATCHING
void func_800546A8(s32 arg0) // 0x800546A8
{
    switch ((u8)arg0)
    {
        case InventoryItemId_Unequipped:
            func_8003DD80(1, 34);
            break;

        case 1:
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
            func_8003DD80(1, 34);
            break;

        case InventoryItemId_HealthDrink:
        case InventoryItemId_FirstAidKit:
        case InventoryItemId_Ampoule:
            func_8003DD80(1, 19);
            break;

        default:
            func_8003DD80(1, 1);
            break;
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/items/item_screens_3", func_800546A8); // 0x800546A8
#endif

void Gfx_Items_Display(s_TmdFile* tmd, s32 arg1, s32 arg2) 
{
    u8                 var_v0;
    GsDOBJ2*           ptr;
    struct TMD_STRUCT* objs;
	
	objs = tmd->objects_C;

    GsLinkObject4((u32)&objs[arg2], &g_Items_ItemsModelData[arg1], 0);

    ptr         = &g_Items_ItemsModelData[arg1];
    ptr->coord2 = &g_Items_Items3dData1[arg1];

    if (D_800AE187 != 0)
    {
        var_v0 = D_800AE187;
    }
    else
    {
        var_v0 = g_MapOverlayHeader.field_2C->field_0[arg2];
    }

    switch (var_v0) 
    {
        case InventoryItemId_HealthDrink: 
        case InventoryItemId_FirstAidKit: 
        case InventoryItemId_Ampoule:
        case InventoryItemId_KitchenKnife: 
        case InventoryItemId_SteelPipe:
        case InventoryItemId_Hammer: 
        case InventoryItemId_Chainsaw:
        case InventoryItemId_Handgun: 
        case InventoryItemId_HuntingRifle: 
        case InventoryItemId_Shotgun:
        case InventoryItemId_HandgunBullets: 
        case InventoryItemId_RifleShells: 
        case InventoryItemId_ShotgunShells:
        case InventoryItemId_Flashlight: 
        case InventoryItemId_PocketRadio:
        case InventoryItemId_Axe:
            ptr->attribute = 0;
            break;

        default:
            ptr->attribute = 0x40000000;
            break;
    }

    if (D_800AE180 < 10)
    {
        D_800AE180++;
    }
}

void func_8005487C(s32 arg0) // 0x8005487C
{
    GsInitCoordinate2(NULL, &g_Items_Items3dData1[arg0]); // Initializes the coordinate system base.  base->coord is set to an identity matrix (GsIDMATRIX). super->sub is set to base.
    g_Items_Items3dData1[arg0].param = (GsCOORD2PARAM*) &g_Items_Items3dData0[arg0];
}

/** Something related to items lighting. */
void func_800548D8(s32 Idx) // 0x800548D8
{
    g_Items_ItemsLightingData[Idx][0].vx = g_Items_Items3dData1[Idx].coord.t[0];
    g_Items_ItemsLightingData[Idx][0].vy = g_Items_Items3dData1[Idx].coord.t[1];
    g_Items_ItemsLightingData[Idx][0].vz = g_Items_Items3dData1[Idx].coord.t[2] + 20000;
}

void Gfx_Items_SetAmbientLighting() // 0x80054928
{
    s32 i;

    for (i = 0; i < 10; i++)
    {
        g_Items_ItemsLightingData[i][0].r  = NO_VALUE;
        g_Items_ItemsLightingData[i][0].g  = NO_VALUE;
        g_Items_ItemsLightingData[i][0].b  = NO_VALUE;
        g_Items_ItemsLightingData[i][1].vx = FP_TO(1, Q12_SHIFT);
        g_Items_ItemsLightingData[i][1].vy = 0;
        g_Items_ItemsLightingData[i][1].vz = 0;
        g_Items_ItemsLightingData[i][1].r  = NO_VALUE;
        g_Items_ItemsLightingData[i][1].g  = NO_VALUE;
        g_Items_ItemsLightingData[i][1].b  = NO_VALUE;
    }

    GsSetAmbient(1024, 1024, 1024);
    GsSetLightMode(1);
}

// Similar to `Gfx_Items_SetAmbientLighting`.
void func_800549A0() // 0x800549A0
{
    #define IDX 9

    g_Items_ItemsLightingData[IDX][0].r  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].vx = FP_FLOAT_TO(1.0f, Q12_SHIFT);
    g_Items_ItemsLightingData[IDX][0].g  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][0].b  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].r  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].g  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].b  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].vy = 0;
    g_Items_ItemsLightingData[IDX][1].vz = 0;

    GsSetAmbient(2048, 2048, 2048);
    GsSetLightMode(1);
}

void func_80054A04(u8 itemId) // 0x80054A04
{
    D_800AE187 = itemId;
    D_800AE180 = 0;
    D_800AE1AC = 0;
    D_800AE1B0 = 0;

    D_800C3E18[9]                          = NO_VALUE;
    g_Items_Items3dData0[9].rotation_10.vz = 0;
    g_Items_Items3dData0[9].rotation_10.vy = 0;
    g_Items_Items3dData0[9].rotation_10.vx = 0;
    g_Items_Items3dData0[9].field_18.vz    = 0;
    g_Items_Items3dData0[9].field_18.vy    = 0;
    g_Items_Items3dData0[9].field_18.vx    = 0;

    GameFs_TmdDataAlloc(FS_BUFFER_5);

    D_800C3E18[9] = 0;

    Gfx_Items_Display(FS_BUFFER_5, 9, 0);
    func_8005487C(9);

    g_Items_Items3dData0[9].scale_0.vz = FP_FLOAT_TO(1.0f, Q12_SHIFT);
    g_Items_Items3dData0[9].scale_0.vy = FP_FLOAT_TO(1.0f, Q12_SHIFT);
    g_Items_Items3dData0[9].scale_0.vx = FP_FLOAT_TO(1.0f, Q12_SHIFT);

    func_800549A0();
    Gfx_ItemScreens_CameraSet(&D_800C3B48, &D_800C3AE8, &D_800C3B38, 0);
}

s32 func_80054AD8(u8 arg0) // 0x80054AD8
{
    s32 temp_a1;
    GsDOBJ2* obj;
    s_Items3dData* ptr;
    s16 x, y;

    g_Items_Items3dData1[9].coord.t[1] = 0x40;
    g_Items_Items3dData1[9].coord.t[0] = 0;
    g_Items_Items3dData1[9].coord.t[2] = -0x20B0;

    switch (D_800AE1AC) 
    {
        case 0:
            if (D_800AE1B0 >= 0x800) 
            {
                D_800AE1AC = 1;
            }

            ptr     = &g_Items_Items3dData0;
            temp_a1 = D_800AE1B0 << 12;

            x = D_800262FC[arg0 - 32].vx;
            y = D_800262FC[arg0 - 32].vy;

            ptr[9].scale_0.vz     = temp_a1 >> 11;
            ptr[9].scale_0.vy     = temp_a1 >> 11;
            ptr[9].scale_0.vx     = temp_a1 >> 11;

            ptr[9].rotation_10.vx = x;
            ptr[9].rotation_10.vy = 0;
            ptr[9].rotation_10.vz = y;
            break;

        case 1:
            g_Items_Items3dData0[9].scale_0.vz = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[9].scale_0.vy = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[9].scale_0.vx = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            D_800AE1AC = 2;
            break;
    }

    D_800AE1B0 += (g_DeltaTime1 * 2);
    D_800AE1B0  = CLAMP(D_800AE1B0, 0, 0x800);

    PushMatrix();
    func_8004BBF4(&D_800C3B48, &D_800C3AE8, &D_800C3B38);

    obj = &D_800C3E08;

    Gfx_Items_ItemRotate(&g_Items_Items3dData1[9].param->rotate, &g_Items_Items3dData1[9]);

    g_Items_Items3dData0[9].rotation_10.vy += g_DeltaTime1 >> 1;

    func_800548D8(9);
    GsSetFlatLight(0, &D_800C3AC8[0]);
    GsSetFlatLight(1, &D_800C3AC8[1]);
    func_8004BD74(9, obj, 2);
    PopMatrix();

    return D_800AE1AC > 0;
}

// TODO: RODATA migration.
#ifdef NON_MATCHING
void Inventory_AddSpecialItem(u8 itemId, s32 itemCount) // 0x80054CAC
{
    switch (itemId)
    {
        case InventoryItemId_RockDrill:
        case InventoryItemId_Chainsaw:
        case InventoryItemId_Katana:
        case InventoryItemId_HyperBlaster:
        case InventoryItemId_GasolineTank:
            g_SavegamePtr->pickedUpSpecialItemCount_25C_3++;
            break;

        case InventoryItemId_ChannelingStone:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_ChannelingStone))
            {
                g_SavegamePtr->pickedUpSpecialItemCount_25C_3++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_ChannelingStone; // `specialItemFlags`?
            }
            break;

        case InventoryItemId_PlateOfTurtle:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_PlateOfTurtle))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_PlateOfTurtle;
            }
            break;

        case InventoryItemId_PlateOfHatter:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_PlateOfHatter))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_PlateOfHatter;
            }
            break;

        case InventoryItemId_PlateOfCat:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_PlateOfCat))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_PlateOfCat;
            }
            break;

        case InventoryItemId_PlateOfQueen:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_PlateOfQueen))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_PlateOfQueen;
            }
            break;

        case InventoryItemId_Lighter:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_Lighter))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_Lighter;
            }
            break;

        case InventoryItemId_VideoTape:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_VideoTape))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_VideoTape;
            }
            break;

        case InventoryItemId_Camera:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_Camera))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_Camera;
            }
            break;

        default:
            g_SavegamePtr->pickedUpItemCount_23C++;
            break;
    }

    g_SavegamePtr->items_0[g_SavegamePtr->inventoryItemSpaces_AB].id_0    = itemId;
    g_SavegamePtr->items_0[g_SavegamePtr->inventoryItemSpaces_AB].count_1 = itemCount;
    g_SavegamePtr->inventoryItemSpaces_AB                                 = func_8004F190(g_SavegamePtr);
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/items/item_screens_3", Inventory_AddSpecialItem); // 0x80054CAC
#endif
