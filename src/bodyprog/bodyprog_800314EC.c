#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"

void Gfx_BackgroundSpriteDraw(s_FsImageDesc* image) // 0x800314EC
{
    s32       baseYOffset;
    s32       tileX;
    s32       tileIndexX;
    s32       x;
    s32       y;
    GsOT*     ot;
    u32       textureShift;
    s32       texturePageX;
    u32       textureYOffset;
    DR_TPAGE* tPage;
    SPRT*     sprt;
    PACKET*   packet;

    ot             = (GsOT*)&D_800B7CC4[g_ObjectTableIdx];
    packet         = GsOUT_PACKET_P;
    baseYOffset    = -120 << (g_GameWork.gsScreenHeight_58A >> 8);
    textureShift   = image->tPage[0];
    texturePageX   = image->tPage[1];
    textureYOffset = image->v;

    for (y = 0; (g_GameWork.gsScreenHeight_58A >> 8) >= y; y++)
    {
        for (x = 0; ((g_GameWork.gsScreenWidth_588 - 1) >> (8 - textureShift)) >= x; x++)
        {
            sprt = (SPRT*)packet;

            addPrimFast(ot, sprt, 4);
            setRGBC0(sprt, D_800A8E58, D_800A8E58, D_800A8E58, 0x64);

            if (y == 0)
            {
                setWH(sprt, 256, 256 - textureYOffset);
                *((u32*)&sprt->u0) = (textureYOffset << 8) + (getClut(image->clutX, image->clutY) << 16);
            }
            else
            {
                setWH(sprt, 256, 256);
                *((u32*)&sprt->u0) = getClut(image->clutX, image->clutY) << 16;
            }

            tileX = x << 8;

            setXY0Fast(sprt,
                       (tileX - (g_GameWork.gsScreenWidth_588 >> 1)) - (image->u << (2 - textureShift)),
                       baseYOffset + ((256 - textureYOffset) * y));

            packet += sizeof(SPRT);
            tPage   = (DR_TPAGE*)packet;

            tileIndexX = x << textureShift;
            setDrawTPage(tPage, 0, 1, getTPage(textureShift, 0, (texturePageX + tileIndexX) << 6, ((texturePageX << 4) & 0x100) + (y << 8)));

            AddPrim(ot, tPage);
            packet = (PACKET*)tPage + sizeof(DR_TPAGE);
        }
    }

    GsOUT_PACKET_P        = packet;
    g_SysWork.field_22A0 |= 1;
    D_800A8E58            = 0x80;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_800317CC);

void func_80031AAC(s_FsImageDesc* image) // 0x80031AAC
{
    volatile s32 pad; // Is there a better solution?
    s32          i;
    s32          xOffset;
    u8           tPageY;
    POLY_FT4*    poly;

    poly = (POLY_FT4*)GsOUT_PACKET_P;

    for (i = 0; i < 3; i++)
    {
        setPolyFT4(poly);
        setXY0Fast(poly, -160 + 128 * i, -120);
        setXY1Fast(poly, 128 * i + (i == 2 ? -96 : -32), -120);

        xOffset = 128 * i;

        setXY2Fast(poly, -160 + xOffset, 120);
        setXY3Fast(poly, xOffset + (i == 2 ? -96 : -32), 120);

        *((u32*)&poly->u0) = (image->v << 8) + (getClut(image->clutX, image->clutY) << 16);

        tPageY = image->tPage[1];

        *((u32*)&poly->u1) = (image->v << 8) + (i == 2 ? 64 : 128) +
                             (getTPage(image->tPage[0], 0, (image->tPage[1] + i) << 6, (tPageY << 4) & 0x100) << 16);

        *((u16*)&poly->u2) = (image->v + 239) << 8;
        *((u16*)&poly->u3) = ((image->v + 239) << 8) + (i == 2 ? 64 : 128);

        setSemiTrans(poly, 0);

        *((u16*)&poly->r0) = D_800A8E58 + (D_800A8E58 << 8);
        poly->b0           = D_800A8E58;

        addPrim(&g_ObjectTable0[g_ObjectTableIdx].org[2], poly);
        poly++;
    }

    GsOUT_PACKET_P = (PACKET*)poly;
    g_SysWork.field_22A0 |= 1;
    D_800A8E58 = 0x80;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80031CCC);

void Gfx_DebugStringPosition(s16 x, s16 y) // 0x80031EFC
{
    #define OFFSET_X SCREEN_POSITION_X(50.0f)
    #define OFFSET_Y SCREEN_POSITION_Y(47.0f)

    if (x != NO_VALUE)
    {
        g_Gfx_DebugStringPosition0.vx =
        g_Gfx_DebugStringPosition1.vx = x - OFFSET_X;
    }

    if (y != NO_VALUE)
    {
        g_Gfx_DebugStringPosition1.vy = y - OFFSET_Y;
    }
}

void Gfx_DebugStringDraw(char* str)
{
    s32       textX;
    s32       textY;
    s32       charIdx;
    GsOT*     ot;
    u8*       strPtr;
    s32       charCode;
    PACKET*   packet;
    SPRT_8*   sprt8;
    DR_TPAGE* tPage;

    ot     = (GsOT*)&D_800B5C58[g_ObjectTableIdx];
    strPtr = str;
    packet = GsOUT_PACKET_P;
    textX  = g_Gfx_DebugStringPosition1.vx;
    textY  = g_Gfx_DebugStringPosition1.vy;

    while (*strPtr != 0)
    {
        charCode = *strPtr;
        switch (charCode)
        {
            default:
                sprt8 = (SPRT_8*)packet;
                addPrimFast(ot, sprt8, 3);
                setRGBC0(sprt8, 0x80, 0x80, 0x80, 0x74);
                setXY0Fast(sprt8, textX, textY);

                charIdx             = (char)toupper(charCode) - 0x2A;
                *((u32*)&sprt8->u0) = ((charIdx & 0x1F) * 8) + ((((charIdx >> 5) * 8) + 0xF0) << 8) + (0x7FD2 << 16);

            case 0x5F:
            case 32:
            case 9:
            case 11:
                textX += 8;
                break;

            case 0x7E:
                textX -= 8;
                break;

            case 10:
                textX  = g_Gfx_DebugStringPosition0.vx;
                textY += 8;
                break;
        }

        strPtr++;
        packet += sizeof(SPRT_8);
    }

    *((u32*)&g_Gfx_DebugStringPosition1) = (textX & 0xFFFF) + (textY << 0x10);
    tPage                                = (DR_TPAGE*)packet;
    setDrawTPage(tPage, 0, 1, 0x14);
    addPrim(ot, tPage);
    packet += sizeof(DR_TPAGE);
    GsOUT_PACKET_P = packet;
}

char* Math_IntegerToString(s32 widthMin, s32 value) // 0x80032154
{
    s32   isNegative;
    char* string = PSX_SCRATCH_ADDR(0x1E);

    if (value < 0)
    {
        isNegative = 1;
        value      = -value;
    }
    else
    {
        isNegative = 0;
    }

    *string = 0;

    do
    {
        string--;
        widthMin--;
        *string = '0' + (value % 10);
        value /= 10;
    } while (value > 0);

    if (isNegative)
    {
        string--;
        *string = '-';
        widthMin--;
    }

    while (widthMin > 0)
    {
        string--;
        *string = '\v';
        widthMin--;
    }

    return string;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_800321EC);

void Gfx_ClearRectInterlaced(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b)
{
    setRECT((RECT*)PSX_SCRATCH, x, y, w, h);
    VSync(0);
    ClearImage2((RECT*)PSX_SCRATCH, r, g, b);
    DrawSync(0);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_800323C8);

void Gfx_Init(u16 screenWidth, s32 isInterlaced) // 0x80032428
{
    g_GameWork.gsScreenWidth_588  = screenWidth;
    g_GameWork.gsScreenHeight_58A = !isInterlaced ? FRAMEBUFFER_HEIGHT_PROGRESSIVE : FRAMEBUFFER_HEIGHT_INTERLACED;

    DrawSync(0);
    GsInitGraph2(g_GameWork.gsScreenWidth_588, g_GameWork.gsScreenHeight_58A, (isInterlaced | 0x4), 1, 0);
    GsDefDispBuff2(0, 32, 0, isInterlaced ? 32 : 256);

    D_800C6E8E =
    D_800C6E26 = FRAMEBUFFER_HEIGHT_PROGRESSIVE;

    GsInit3D();
    Settings_ScreenXYSet(g_GameWorkConst->config_0.optScreenPosX_1C, g_GameWorkConst->config_0.optScreenPosY_1D);
    GsSwapDispBuff();
    GsSwapDispBuff();
}

void Settings_ScreenXYSet(s32 x, s32 y) // 0x800324F4
{
    Settings_DispEnvXYSet(&GsDISPENV, x, y);
}

void Settings_DispEnvXYSet(DISPENV* display, s32 x, s32 y) // 0x80032524
{
    s_GameWork* gameWorkPtr;

    x = (x < -11) ? -11 : ((x > 11) ? 11 : x);
    y = (y < -8) ? -8 : ((y > 8) ? 8 : y);

    gameWorkPtr = g_GameWorkConst;
    gameWorkPtr->config_0.optScreenPosX_1C = x;
    gameWorkPtr->config_0.optScreenPosY_1D = y;

    display->screen.x = gameWorkPtr->config_0.optScreenPosX_1C;
    display->screen.y = gameWorkPtr->config_0.optScreenPosY_1D + 8;
}

void func_800325A4(DR_MODE* arg0) // 0x800325A4
{
    if (g_Gfx_ScreenFade & 8) 
    {
        SetDrawMode(arg0, 0, 1, 32, NULL);
    }
    else 
    {
        SetDrawMode(arg0, 0, 1, 64, NULL);
    }
}

int func_800325F8() // 0x800325F8
{
    return 4096 - D_800B5C28;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003260C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003289C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80032904);

void Gfx_VSyncCallback() // 0x80032b80
{
    D_800A9768++;
    D_800A976C++;

    g_SysWork.timer_1C++;
    g_SysWork.timer_20++;
    g_SysWork.timer_24++;
}

void GameFs_TitleGfxSeek() // 0x80032bd0
{
    Fs_QueueStartSeek(FILE_TIM_TITLE_E_TIM);
}

void GameFs_TitleGfxLoad() // 0x80032bf0
{
    Fs_QueueStartReadTim(FILE_TIM_TITLE_E_TIM, FS_BUFFER_3, &D_800A9014);
}

void GameFs_StreamBinSeek() // 0x80032C20
{
    Fs_QueueStartSeek(FILE_VIN_STREAM_BIN);
}

void GameFs_StreamBinLoad() // 0x80032C40
{
    Fs_QueueStartRead(FILE_VIN_STREAM_BIN, FS_BUFFER_1);
}

void GameFs_OptionBinLoad() // 0x80032C68
{
    Fs_QueueStartReadTim(FILE_TIM_OPTION_TIM, FS_BUFFER_1, &D_800A902C);
    Fs_QueueStartRead(FILE_VIN_OPTION_BIN, FS_BUFFER_1);
}

void GameFs_SaveLoadBinLoad() // 0x80032CA8
{
    Fs_QueueStartReadTim(FILE_TIM_SAVELOAD_TIM, FS_BUFFER_1, &D_800A902C);
    Fs_QueueStartRead(FILE_VIN_SAVELOAD_BIN, FS_BUFFER_1);
}

void func_80032CE8()
{
    Gfx_StringSetPosition(SCREEN_POSITION_X(33.75f), SCREEN_POSITION_Y(43.5f));
    Gfx_StringDraw(&D_8002510C, 100);
}

void GameState_Unk0_Update() // 0x80032D1C
{
    s32 gameStateStep0;
    s32 gameState;
    s32 unkGameStateVar;

    gameStateStep0 = g_GameWork.gameStateStep_598[0];
    switch (gameStateStep0)
    {
        case 0:
            g_GameWork.background2dColor_R_58C = 0;
            g_GameWork.background2dColor_G_58D = 0;
            g_GameWork.background2dColor_B_58E = 0;

            Gfx_Init(SCREEN_WIDTH, 0);
            g_SysWork.timer_20              = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            g_GameWork.gameStateStep_598[0]++;
            break;

        case 1:
            if (!func_80045B28())
            {
                unkGameStateVar = D_800A9774[g_GameWork.gameStateStep_598[1]];
                if (unkGameStateVar != 0)
                {
                    Sd_EngineCmd(unkGameStateVar);
                    g_GameWork.gameStateStep_598[1]++;
                }
                else
                {
                    g_SysWork.timer_20 = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    g_GameWork.gameStateStep_598[0]++;
                }
            }
            break;

        case 2:
            Fs_QueueStartReadTim(FILE_1ST_FONT16_TIM, FS_BUFFER_1, &D_800A8FF4);
            Fs_QueueStartReadTim(FILE_1ST_KONAMI_TIM, FS_BUFFER_1, &D_800A8FFC);

            g_Gfx_ScreenFade = gameStateStep0;
            g_GameWork.gameStateStep_598[0]++;
            break;

        case 3:
            if ((g_Gfx_ScreenFade & 0x7) == ((1 << 0) | (1 << 2)))
            {
                Fs_QueueWaitForEmpty();

                gameState = g_GameWork.gameState_594;
                
                g_SysWork.timer_1C = 0;
                g_SysWork.timer_20 = 0;

                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;

                g_SysWork.sysState_8     = 0;
                g_SysWork.timer_24       = 0;
                g_SysWork.sysStateStep_C = 0;
                g_SysWork.field_28       = 0;
                g_SysWork.field_10       = 0;
                g_SysWork.timer_2C       = 0;
                g_SysWork.field_14       = 0;

                g_GameWork.gameStateStep_598[0] = gameState;
                g_GameWork.gameState_594        = gameState + 1;
                g_GameWork.gameStatePrev_590    = gameState;
                g_GameWork.gameStateStep_598[0] = 0;
            }
            break;

        default:
            break;
    }

    func_80033548();
    Gfx_BackgroundSpriteDraw(&g_MainImg0);
    func_80089090(1);
}

void MainLoop() // 0x80032EE0
{
    #define TICKS_PER_SECOND_MIN (TICKS_PER_SECOND / 4)
    #define H_BLANKS_PER_TICK    263
    #define ONE_SEC_FIXED        FP_TO(1, Q12_SHIFT)

    #define H_BLANKS_PER_SECOND               (H_BLANKS_PER_TICK * TICKS_PER_SECOND)              // 15780
    #define H_BLANKS_TO_SEC_CONVERSION_FACTOR ((float)ONE_SEC_FIXED / (float)H_BLANKS_PER_SECOND) // 0.25956907477f

    #define H_BLANKS_PER_FRAME_MIN   (H_BLANKS_PER_SECOND / TICKS_PER_SECOND_MIN)                    // 1052
    #define H_BLANKS_FP_TO_SEC_SCALE (s32)(H_BLANKS_TO_SEC_CONVERSION_FACTOR * (float)ONE_SEC_FIXED) // 1063
    #define H_BLANKS_UNKNOWN_SCALE   10419                                                           // TODO: Somehow derive this value.
    #define V_BLANKS_MAX             4

    s32 vBlanks;
    s32 vCount;
    s32 vCountCopy;
    s32 interval;

    // Initialize engine.
    GsInitVcount();
    func_8002E630();
    func_8002E7BC();
    func_8002E85C();
    Joy_Init();
    VSyncCallback(&Gfx_VSyncCallback);
    InitGeom();
    func_8004BB10(); // Initializes something for graphics.
    func_800890B8();
    sd_init();

    // Run game.
    while (true)
    {
        g_MainLoop_FrameCount++;

        // Update input.
        Joy_ReadP1();
        Demo_ControllerDataUpdate();
        Joy_ControllerDataUpdate();

        if (MainLoop_ShouldWarmReset() == 2)
        {
            Game_WarmBoot();
            continue;
        }

        g_ObjectTableIdx = GsGetActiveBuff();

        if (g_GameWork.gameState_594 >= GameState_MainLoadScreen && g_GameWork.gameState_594 < GameState_MapEvent)
        {
            GsOUT_PACKET_P = (PACKET*)(TEMP_MEMORY_ADDR + (g_ObjectTableIdx << 17));
        }
        else if (g_GameWork.gameState_594 == GameState_InventoryScreen)
        {
            GsOUT_PACKET_P = (PACKET*)(TEMP_MEMORY_ADDR + (g_ObjectTableIdx * 40000));
        }
        else
        {
            GsOUT_PACKET_P = (PACKET*)(TEMP_MEMORY_ADDR + (g_ObjectTableIdx << 15));
        }

        GsClearOt(0, 0, &g_ObjectTable0[g_ObjectTableIdx]);
        GsClearOt(0, 0, &g_ObjectTable1[g_ObjectTableIdx]);

        g_SysWork.field_22A0 = 0;

        // Call update function for current GameState.
        D_800A977C[g_GameWork.gameState_594]();

        Demo_Update();
        Demo_GameRandSeedSet();

        if (MainLoop_ShouldWarmReset() == 2)
        {
            Game_WarmBoot();
            continue;
        }

        func_8003260C();
        func_8002EB88();
        func_800485D8();

        if (!func_80045B28())
        {
            Fs_QueueUpdate();
        }

        func_80089128();
        func_8008D78C(); // Camera update?
        DrawSync(0);

        // Handle V sync.
        if (g_SysWork.flags_22A4 & (1 << 1))
        {
            vBlanks = VSync(-1);
            g_VBlanks = vBlanks - g_PrevVBlanks;

            Demo_PresentIntervalUpdate();

            interval = g_Demo_VideoPresentInterval;
            g_PrevVBlanks = vBlanks;

            if (interval < g_IntervalVBlanks)
            {
                interval = g_IntervalVBlanks;
            }

            do
            {
                VSync(0);
                g_VBlanks++;
                g_PrevVBlanks++;
            }
            while (g_VBlanks < interval);

            g_UncappedVBlanks = g_VBlanks;
            g_VBlanks = MIN(g_VBlanks, 4);

            vCount = g_Demo_VideoPresentInterval * H_BLANKS_PER_TICK;
            vCountCopy = g_UncappedVBlanks * H_BLANKS_PER_TICK;
            g_VBlanks = g_Demo_VideoPresentInterval;
        }
        else
        {
            if (g_SysWork.sysState_8 != SysState_Gameplay)
            {
                g_VBlanks = VSync(-1) - g_PrevVBlanks;
                g_PrevVBlanks = VSync(-1);
                VSync(0);
            }
            else
            {
                if (g_Gfx_ScreenFade != 1)
                {
                    VSync(0);
                }

                g_VBlanks = VSync(-1) - g_PrevVBlanks;
                g_PrevVBlanks = VSync(-1);

                if (g_VBlanks < g_IntervalVBlanks)
                {
                    do
                    {
                        VSync(0);
                        g_VBlanks++;
                        g_PrevVBlanks++;
                    }
                    while (g_VBlanks < g_IntervalVBlanks);
                }
            }

            // Update V blanks.
            g_UncappedVBlanks = g_VBlanks;
            g_VBlanks = MIN(g_VBlanks, V_BLANKS_MAX);
            
            // Update V count.
            vCount = MIN(GsGetVcount(), H_BLANKS_PER_FRAME_MIN); // NOTE: Will call `GsGetVcount` twice.
            vCountCopy = vCount;
        }

        // Update delta time.
        g_DeltaTime0 = FP_MULTIPLY(vCount, H_BLANKS_FP_TO_SEC_SCALE, Q12_SHIFT);
        g_DeltaTime1 = FP_MULTIPLY(vCountCopy, H_BLANKS_FP_TO_SEC_SCALE, Q12_SHIFT);
        g_DeltaTime2 = FP_MULTIPLY(vCount, H_BLANKS_UNKNOWN_SCALE, Q12_SHIFT); // TODO: Unknown time scale.
        GsClearVcount();

        // Draw objects?
        GsSwapDispBuff();
        GsSortClear(g_GameWork.background2dColor_R_58C, g_GameWork.background2dColor_G_58D, g_GameWork.background2dColor_B_58E, &g_ObjectTable0[g_ObjectTableIdx]);
        GsDrawOt(&g_ObjectTable0[g_ObjectTableIdx]);
        GsDrawOt(&g_ObjectTable1[g_ObjectTableIdx]);
    }
}

void Settings_ScreenAndVolUpdate() // 0x0x800333CC
{
    s32 soundCmd;

    Settings_ScreenXYSet(g_GameWork.config_0.optScreenPosX_1C, g_GameWork.config_0.optScreenPosY_1D);

    soundCmd = (g_GameWork.config_0.optSoundType_1E != 0) ? 1 : 2;
    Sd_EngineCmd(soundCmd);

    Sd_SetVolume(OPT_SOUND_VOLUME_MAX, g_GameWork.config_0.optVolumeBgm_1F, g_GameWork.config_0.optVolumeSe_20);
}

void Settings_RestoreDefaults() // 0x8003342c
{
    g_GameWork.config_0.optExtraWeaponCtrl_23 = 1;
    g_GameWork.config_0.optBrightness_22 = 3;

    Settings_RestoreControlDefaults(0);

    g_GameWork.config_0.optVibrationEnabled_21 = OPT_VIBRATION_ENABLED;
    g_GameWork.config_0.optVolumeBgm_1F        = OPT_SOUND_VOLUME_MAX;
    g_GameWork.config_0.optVolumeSe_20         = OPT_SOUND_VOLUME_MAX;

    Settings_ScreenAndVolUpdate();

    g_GameWork.config_0.optExtraBloodColor_24 = 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", Settings_RestoreControlDefaults);

void nullsub_800334C8() {}

void func_800334D0() {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_800334D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80033548);

void SysWork_Clear() // 0x800340E0
{
    bzero(&g_SysWork, sizeof(s_SysWork));
}

s32 MainLoop_ShouldWarmReset() // 0x80034108
{
    #define RESET_BTN_FLAGS (ControllerFlag_Select | ControllerFlag_Start)
    #define UNK_BTN_FLAGS_0 (ControllerFlag_Select | ControllerFlag_Start | ControllerFlag_L2 | ControllerFlag_R2 | ControllerFlag_L1 | ControllerFlag_R1)
    #define UNK_BTN_FLAGS_1 (ControllerFlag_Start | ControllerFlag_Triangle | ControllerFlag_Square)

    if (g_GameWork.gameState_594 < GameState_MovieIntroAlternate)
    {
        return 0;
    }

    if (g_GameWork.gameState_594 == GameState_SaveScreen && g_GameWork.gameStateStep_598[0] == 4)
    {
        return 0;
    }

    if (g_GameWork.gameState_594 == GameState_Unk10 && (g_GameWork.gameStateStep_598[0] - 2) < 2u)
    {
        return 0;
    }

    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        if (D_800A9768 >= 1801)
        {
            return 2;
        }
    }
    else
    {
        D_800A9768 = 0;
    }

    if (g_GameWork.gameState_594 == GameState_MainMenu)
    {
        return 0;
    }

    // Reset something.
    if ((g_ControllerPtrConst->btns_held_C & RESET_BTN_FLAGS) != RESET_BTN_FLAGS)
    {
        D_800A976C = 0;
    }

    if (D_800A976C >= 121)
    {
        return 2; 
    }
    else if (g_ControllerPtrConst->btns_held_C == UNK_BTN_FLAGS_0 && (g_ControllerPtrConst->btns_new_10 & UNK_BTN_FLAGS_0))
    {
        return 2; 
    }
    else if (g_ControllerPtrConst->btns_held_C == UNK_BTN_FLAGS_1 && (g_ControllerPtrConst->btns_new_10 & ControllerFlag_Start))
    {
        return 2; 
    }

    return (g_SysWork.flags_22A4 & (1 << 8)) ? 2 : 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", Game_WarmBoot);

void Joy_Init() // 0x8003441C
{
    PadInitDirect(&g_GameWork.rawController_5B4, g_ControllerPtr);
    PadStartCom();
}

void Joy_ReadP1() // 0x80034450
{
    s_ControllerData* cont = &g_GameWork.controllers_38[0];

    // NOTE: `memcpy` is close, reads `rawController_5B4` as two `s32`s, but doesn't give match.
    // memcpy(&cont->analogController_0, &g_GameWork.rawController_5B4, sizeof(s_AnalogController));

    *(s32*)&cont->analogController_0 = *(s32*)&g_GameWork.rawController_5B4;
    *(s32*)&cont->analogController_0.right_x = *(s32*)&g_GameWork.rawController_5B4.right_x;

    // Alternate
    // ((s32*)&cont->analogController_0)[0] = ((s32*)&g_GameWork.rawController_5B4)[0];
    // ((s32*)&cont->analogController_0)[1] = ((s32*)&g_GameWork.rawController_5B4)[1];
}

void Joy_Update() // 0x8003446C
{
    Joy_ReadP1();
    Joy_ControllerDataUpdate();
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", Joy_ControllerDataUpdate);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", ControllerData_AnalogToDigital);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003483C);

void func_800348C0()
{
    bzero(&D_800A9944, 0x48);
}

void GameState_MainLoadScreen_Update() // 0x800348E8
{
    u8 temp;

    func_80034E58();
    func_80034964();

    if (g_SysWork.flags_22A4 & (1 << 10))
    {
        temp = D_800BCDD4 + 1;
        D_800BCDD4 = temp;

        if ((temp & 0xFF) >= 21)
        {
            g_SysWork.flags_22A4 &= ~(1 << 10);

            Sd_EngineCmd(1502);
            Sd_EngineCmd(1501);
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80034964);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80034E58);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80034EC8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80034F18);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80034FB8);

void Game_SavegameInitialize(s8 overlayId, s32 difficulty) // 0x800350BC
{
    s32  i;
    s32* var_a2;

    bzero(g_SavegamePtr, sizeof(s_ShSavegame));

    g_SavegamePtr->mapOverlayId_A4 = overlayId;

    difficulty = CLAMP(difficulty, GameDifficulty_Easy, GameDifficulty_Hard);

    var_a2 = g_SavegamePtr->field_B0;

    g_SavegamePtr->gameDifficulty_260 = difficulty;
    g_SavegamePtr->current2dMap_A9 = 1;

    for (i = 0; i < 45; i++)
    {
        var_a2[44] = NO_VALUE;
        var_a2--;
    }

    Game_SavegameResetPlayer();
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80035178);

void GameFs_MapLoad(s32 mapIdx) // 0x8003521C
{
    #define BASE_FILE_IDX FILE_VIN_MAP0_S00_BIN
    #define UNK_FLAGS     ((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5))

    Fs_QueueStartRead(BASE_FILE_IDX + mapIdx, g_OvlDynamic);
    func_8005E0DC(mapIdx);
    GameFs_PlayerMapAnimLoad(mapIdx);

    if (g_SysWork.flags_2298 & UNK_FLAGS)
    {
        func_8003CD6C(&g_SysWork.field_38);
    }

    func_800546A8((u8)g_SysWork.field_38.field_F);
}

s32 func_8003528C(s32 idx0, s32 idx1)
{
    u32         tempField_8;
    u32         tempField_4;
    s_800A992C* ptr0;
    s_800A992C* ptr1;

    ptr0        = &D_800A992C[idx0];
    ptr1        = &D_800A992C[idx1];
    tempField_4 = ptr0->field_4;
    tempField_8 = ptr1->field_8;

    if (tempField_4 >= (tempField_8 + ptr1->field_10) ||
        tempField_8 >= (tempField_4 + ptr0->field_C))
    {
        return 0;
    }

    return 1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_800352F8); // 0x800352F8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80035338); // 0x80035338

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80035560); // 0x80035560

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003569C); // 0x8003569C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80035780); // 0x80035780

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_800358A8); // 0x800358A8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_800358DC); // 0x800358DC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80035924); // 0x80035924

void func_8003596C() // 0x8003596C
{
    if (g_MapOverlayHeader.field_14 == 1)
    {
        func_80035DB4(1);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003599C); // 0x8003599C

s32 func_80035AB0(s32 arg0) // 0x80035AB0
{
    return g_GameWork.field_5B3 != arg0;
}

void func_80035AC8(s32 arg0) // 0x80035AC8
{
    g_GameWork.field_5B3 = arg0;
    Sd_EngineCmd(D_800A98AC[arg0]);
}

void func_80035B04(VECTOR3* pos, SVECTOR* rot, GsCOORDINATE2* coord) // 0x80035B04
{
    coord->flg = 0;

    coord->coord.t[0] = FP_FROM(pos->vx, Q4_SHIFT);
    coord->coord.t[1] = FP_FROM(pos->vy, Q4_SHIFT);
    coord->coord.t[2] = FP_FROM(pos->vz, Q4_SHIFT);

    func_80096E78(rot, (MATRIX*)&coord->coord);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80035B58); // 0x80035B58

void func_80035B98() // 0x80035B98
{
    Gfx_BackgroundSpriteDraw(&D_800A902C);
}

void func_80035BBC() // 0x80035BBC
{
    Gfx_BackgroundSpriteDraw(&D_800A9034);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80035BE0); // 0x80035BE0

void func_80035DB4(s32 arg0) // 0x80035DB4
{
    D_800BCD5C = 0;

    if (g_MapOverlayHeader.func_10)
    {
        g_MapOverlayHeader.func_10();
        if (arg0 == 0 && D_800BCD5C == 0)
        {
            func_80035F4C(1, 0xF0000, 0);
        }
    }
}

void func_80035E1C() // 0x80035E1C
{
    s32 i;

    for (i = 0; i < 9; i++)
    {
        g_SysWork.field_2748[i] = 0;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80035E44); // 0x80035E44

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80035ED0); // 0x80035ED0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80035F4C); // 0x80035F4C

void func_800363D0() // 0x800363D0
{
    D_800A9A1C = 0;
    g_SysWork.field_22A0 |= 1 << 3;
    func_80035DB4(0);
}

void func_8003640C(s32 arg0) // 0x8003640C
{
    if (arg0 != 0)
    {
        g_MapOverlayHeader.field_14 = arg0;
    }
}

void func_80036420() // 0x80036420
{
    s32 x;
    s32 z;
    s8  newMapRoomIdx;

    x = g_SysWork.player_4C.chara_0.position_18.vx;
    z = g_SysWork.player_4C.chara_0.position_18.vz;

    if (g_MapOverlayHeader.getMapRoomIdxFunc_4 == NULL)
    {
        newMapRoomIdx = 0;
    } 
    else 
    {
        newMapRoomIdx = g_MapOverlayHeader.getMapRoomIdxFunc_4(x, z);
    }

    g_SavegamePtr->mapRoomIdx_A5 = newMapRoomIdx;
}

s32 func_8003647C() // 0x8003647C
{
    return g_SavegamePtr->mapRoomIdx_A5 > g_MapOverlayHeader.field_8;
}

s32 func_80036498() // 80036498
{
    return !(g_SavegamePtr->mapRoomIdx_A5 > g_MapOverlayHeader.field_8);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_800364BC); // 0x800364BC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003652C); // 0x8003652C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_800365B8); // 0x800365B8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80036B5C); // 0x80036B5C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80036E48); // 0x80036E48

void func_8003708C(s16* ptr0, u16* ptr1) // 0x8003708C
{
    s32 var0;
    s16 var1;
    s32 var3;
    s32 shift;
    s32 i;

    var0 = 0;
    var1 = 0;

    for (i = 0; i < 12; i++)
    {
        shift = (i & 3) * 4;
        var3  = (*ptr1 >> shift) & 0xF;
        if (i != 0 && var3 == 11 && var0 != 0)
        {
            var1 |= 11 << shift;
        }

        var0 = 0;
        if (var3 != 0 && var3 != 11)
        {
            var1 |= 11 << shift;
            var0  = 1;
        }

        if ((i & 3) == 3 || i == 12)
        {
            ptr1++;
            *ptr0++ = var1;
            var1    = 0;
        }
    } 
}

void func_80037124() // 0x80037124
{
    D_800BCD78 = NO_VALUE;
    func_8003652C();
    DrawSync(0);
}

void func_80037154() // 0x80037154
{
    s32         i;
    s_800BCDA8* element;

    for (i = 0; i < 2; i++)
    {
        element = &D_800BCDA8[i];

        D_800BCDA8[i].field_2 = NO_VALUE;
        D_800BCDA8[i].field_1 = NO_VALUE;
        D_800BCDA8[i].field_3 = 0;
    }
}

void func_80037188() // 0x80037188
{
    s32 i;

    for (i = 0; i < 2; i++)
    {
        D_800BCDA8[i].field_0 = NO_VALUE;
    }

    for (i = 0; i < 2; i++)
    {
        func_8004690C((i + 0x529) & 0xFFFF);
    }
}

void Chara_PositionUpdateFromParams(s_AreaLoadParams* params) // 0x800371E8
{
    s32 rot = params->rotationY_4_16 * 16;

    Math_SVectorSet(&g_SysWork.player_4C.chara_0.rotation_24, 0, rot, 0);

    g_SysWork.player_4C.chara_0.position_18.vy = 0;
    g_SysWork.player_4C.chara_0.position_18.vx = params->char_x_0;
    g_SysWork.player_4C.chara_0.position_18.vz = params->char_z_8;

    if (params->field_4_24 >= 2)
    {
        g_SysWork.player_4C.chara_0.position_18.vx += FP_MULTIPLY_FLOAT((s64)shRsin(rot), 0.4f, Q12_SHIFT);
        g_SysWork.player_4C.chara_0.position_18.vz += FP_MULTIPLY_FLOAT((s64)shRcos(rot), 0.4f, Q12_SHIFT);
    }

    g_SysWork.field_2281 = params->field_4_9;

    if (params->mapIdx_4_0 == 24)
    {
        g_SavegamePtr->current2dMap_A9 = 0;
    }
    else if (params->mapIdx_4_0 != 0)
    {
        g_SavegamePtr->current2dMap_A9 = params->mapIdx_4_0;
    }

    g_SysWork.cameraAngleY_237A = rot;

    func_8007E9C4();
    func_80036420();
}

void func_80037334() // 0x80037334
{
    s_func_800699F8 sp10;

    if (g_MapOverlayHeader.func_40 != 0)
    {
        g_MapOverlayHeader.func_40();
    }

    func_800699F8(&sp10, g_SysWork.player_4C.chara_0.position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz);
    g_SysWork.player_4C.chara_0.position_18.vy = sp10.chara_grnd_0;
}

void func_80037388() // 0x80037388
{
    volatile s32 v1;
    s32 v2;
    s32 i;

    v1 = v2;
    for (i = 0; i < 5; i++)
    { 
        D_800BCDC0[i] = NO_VALUE;
        D_800BCD90[i] = 0;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_800373CC); // 0x800373CC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_800378D4); // 0x800378D4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80037A4C); // 0x80037A4C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80037C5C); // 0x80037C5C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80037DC4); // 0x80037DC4

void func_80037E40(s_SubCharacter* chara) // 0x80037E40
{
    if (chara->field_C0 > 0)
    {
        chara->flags_3E |= CharaFlag_Unk6;
    }
    else
    {
        chara->flags_3E &= ~CharaFlag_Unk6;
    }
}

void func_80037E78(s_SubCharacter* chara) // 0x80037E78
{
    s8  idx;
    s32 cond;

    // TODO: Strange `chara->headingAngle_3C` access.
    if (chara->health_B0 <= 0 && (*(s32*)&chara->headingAngle_3C & 0x600000) == 0x200000)
    {
        idx = chara->unk_40[1];
        if (idx < 39)
        {
            cond = D_800AD4C8[idx].field_10 == 3;
            func_800914C4(cond, func_8009146C(cond) + 1);
        }

        chara->flags_3E |= CharaFlag_Unk7;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80037F24);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_800382B0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_800382EC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80038354);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80038A6C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80038B44);

void GameState_InGame_Update() // 0x80038BD4
{
    s_SubCharacter* player;

    Demo_DemoRandSeedBackup();

    switch (g_GameWork.gameStateStep_598[0])
    {
        case 0:
            g_Gfx_ScreenFade = 6;
            D_800B5C30 = 0x3000;
            g_GameWork.gameStateStep_598[0] = 1;

        case 1:
            DrawSync(0);
            func_80037154();
            func_80036420();
            func_800892A4(1);

            g_IntervalVBlanks = 2;
            g_GameWork.gameStateStep_598[0]++;
            g_SysWork.field_22A0 |= 1 << 6;
            break;
    }

    if (g_SysWork.sysState_8 != 0 && g_SysWork.player_4C.chara_0.health_B0 <= 0)
    {
        SysWork_StateSetNext(SysState_Gameplay);
    }

    if (g_DeltaTime0 != 0)
    {
        D_800BCD84 = g_DeltaTime0;
    }
    else
    {
        D_800BCD84 = g_DeltaTime1;
    }

    if (g_SysWork.sysState_8 == SysState_Gameplay)
    {
        g_SysWork.field_18 = 0;
        D_800A9A2C[SysState_Gameplay]();
    }
    else
    {
        g_DeltaTime0 = 0;
        D_800A9A2C[g_SysWork.sysState_8]();

        if (g_SysWork.sysState_8 == 0)
        {
            func_800373CC(1);
            if (D_800A9A10 != 0xF)
            {
                SysWork_StateSetNext(D_800A9A10);
            }
        }
    }
    Demo_DemoRandSeedRestore();

    D_800A9A0C = ((g_Gfx_ScreenFade & 7) == 5) && Fs_QueueDoThingWhenEmpty() != 0;

    if ((g_SysWork.field_22A0 & 1) == 0 && g_MapOverlayHeader.func_40 != NULL)
    {
        g_MapOverlayHeader.func_40();
    }

    func_80032904();
    func_80035DB4(0);
    Demo_DemoRandSeedRestore();
    Demo_DemoRandSeedRestore();

    if ((g_SysWork.field_22A0 & 1) == 0)
    {
        func_80040014();
        vcMoveAndSetCamera(0, 0, 0, 0, 0, 0, 0, 0);
        if (g_MapOverlayHeader.func_44 != NULL)
        {
            g_MapOverlayHeader.func_44();
        }
        Demo_DemoRandSeedRestore();

        player = &g_SysWork.player_4C.chara_0;
        func_800717D0(player, FS_BUFFER_0, g_SysWork.playerBoneCoords_890);

        Demo_DemoRandSeedRestore();
        func_8003F170();

        if (g_SavegamePtr->mapOverlayId_A4 != 42)
        {
            g_MapOverlayHeader.func_168(0, g_SavegamePtr->mapOverlayId_A4, 1);
        }

        Demo_DemoRandSeedRestore();
        if (player->model_0.anim_4.flags_2 & (1 << 1))
        {
            func_8003DA9C(1, g_SysWork.playerBoneCoords_890, 1, g_SysWork.player_4C.chara_0.timer_C6, 0);
            func_8008A384(&g_SysWork.player_4C.chara_0);
            func_8007D970(&g_SysWork.player_4C, g_SysWork.playerBoneCoords_890);
            func_8008A3AC(&g_SysWork.player_4C.chara_0);
        }

        Demo_DemoRandSeedRestore();
        func_80037F24(1);
        func_80038354();
        func_8005E89C();
        func_8003C3AC();
        func_8003C878(1);
        Demo_DemoRandSeedAdvance();
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", SysState_Gameplay_Update);

void SysState_GamePaused_Update() // 0x800391E8
{
    D_800A9A68 += g_DeltaTime1;
    if (((D_800A9A68 >> 11) & 1) == 0)
    {
        Gfx_StringSetPosition(SCREEN_POSITION_X(39.25f), SCREEN_POSITION_Y(43.5f));
        Gfx_StringDraw(D_80025394, 99); // "\x07PAUSED"
    }

    func_80091380();
    func_8004C8DC();

    if (g_SysWork.sysStateStep_C == 0)
    {
        Sd_EngineCmd(3);
        g_SysWork.sysStateStep_C++;
    }

    // Debug button combo to bring up save screen from pause screen.
    // DPad-Left + L2 + L1 + LS-Left + RS-Left + L3
    if ((g_ControllerPtrConst->btns_held_C == (ControllerFlag_L3 | ControllerFlag_DpadLeft | ControllerFlag_L2 | ControllerFlag_L1 | ControllerFlag_LStickLeft2 | ControllerFlag_RStickLeft | ControllerFlag_LStickLeft)) &&
        (g_ControllerPtrConst->btns_new_10 & ControllerFlag_L3))
    {
        D_800A9A68 = 0;
        Sd_EngineCmd(4);
        g_MapEventIdx = 0;
        SysWork_StateSetNext(SysState_SaveMenu1);
        return;
    }

    if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.pause_14)
    {
        D_800A9A68 = 0;
        Sd_EngineCmd(4);
        SysWork_StateSetNext(SysState_Gameplay);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", SysState_OptionsMenu_Update); // 0x80039344

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003943C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", SysState_StatusMenu_Update); // 0x80039568

void GameState_LoadStatusScreen_Update() // 0x800395C0
{
    s_ShSavegame* savegame;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        DrawSync(0);
        g_IntervalVBlanks = 1;
        g_Gfx_ScreenFade  = 0;

        func_8003943C();

        if (func_80045B28())
        {
            Sd_EngineCmd(0x13);
        }

        savegame = g_SavegamePtr;
        func_800540A4(savegame->mapOverlayId_A4);
        GameFs_MapItemsTextureLoad(savegame->mapOverlayId_A4);

        g_GameWork.gameStateStep_598[0]++;
    }

    func_80031CCC(2);

    if (Fs_QueueDoThingWhenEmpty() != 0)
    {
        Game_StateSetNext(GameState_InventoryScreen);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", SysState_Unk3_Update); // 0x800396D4

void GameState_LoadMapScreen_Update() // 0x8003991C
{
    s_ShSavegame* savegame;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        DrawSync(0);
        g_IntervalVBlanks = 1;

        func_8003943C();
        func_80066E40();

        savegame = g_SavegamePtr;

        if (D_800A99CC[savegame->current2dMap_A9] != NO_VALUE)
        {
            Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + D_800A99CC[savegame->current2dMap_A9], FS_BUFFER_1, &D_800A9024);
        }

        Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + D_800A99B4[savegame->current2dMap_A9], FS_BUFFER_2, &D_800A901C);
        g_GameWork.gameStateStep_598[0]++;
    }

    func_80031CCC(2);

    if (Fs_QueueDoThingWhenEmpty() != 0)
    {
        Game_StateSetNext(GameState_MapScreen);
    }
}

void SysState_Fmv_Update() // 0x80039A58
{
    #define BASE_IDX 2072

    switch (g_SysWork.sysStateStep_C)
    {
        case 0:
            g_Gfx_ScreenFade         = 3;
            D_800A9A0C               = 0;
            g_SysWork.sysStateStep_C = 1;

        case 1:
            if (func_8003C850() != 0)
            {
                GameFs_StreamBinLoad();
                g_SysWork.sysStateStep_C++;
            }
            break;

        default:
            break;
    }

    if (D_800A9A0C == 0)
    {
        return;
    }

    // Copy framebuffer into `IMAGE_BUFFER_0` before movie playback.
    DrawSync(0);
    StoreImage(&D_800A9A6C, (u32*)IMAGE_BUFFER_0);
    DrawSync(0);

    func_800892A4(0);
    func_80089128();

    // Start playing movie. File to play is based on file ID `BASE_IDX - g_MapEventIdx`.
    // Blocks until movie has finished playback or user has skipped it.
    open_main(BASE_IDX - g_MapEventIdx, g_FileTable[BASE_IDX - g_MapEventIdx].blockCount);

    func_800892A4(1);

    // Restore copied framebuffer from `IMAGE_BUFFER_0`.
    GsSwapDispBuff();
    LoadImage(&D_800A9A6C, (u32*)IMAGE_BUFFER_0);
    DrawSync(0);

    // Set savegame flag based on `D_800BCDD8->eventFlagNum_2` flag ID.
    Savegame_EventFlagSet(g_MapEventParam->eventFlagId_2);

    // Return to game.
    Game_StateSetNext(GameState_InGame);

    // If flag is set, returns to `GameState_InGame` with `gameStateStep[0]` = 1.
    if ((g_MapEventParam->flags_8 >> 13) & (1 << 1)) // flags_8 & (1 << 14)? Does shift imply bitfield?
    {
        g_GameWork.gameStateStep_598[0] = 1;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", SysState_LoadArea_Update);

void AreaLoad_UpdatePlayerPosition() // 0x80039F30
{
    Chara_PositionUpdateFromParams(&D_800BCDB0);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_80039F54);

s8 func_80039F90() // 0x80039F90
{
    if (g_SysWork.flags_2298 & 0x3)
    {
        return g_SysWork.field_2282;
    }

    return 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", SysState_ReadMessage_Update);

void SysWork_SavegameUpdatePlayer() // 0x8003A120
{
    s_ShSavegame* save = g_SavegamePtr;

    save->locationId_A8       = g_MapEventIdx;
    save->playerPositionX_244 = g_SysWork.player_4C.chara_0.position_18.vx;
    save->playerPositionZ_24C = g_SysWork.player_4C.chara_0.position_18.vz;
    save->playerRotationY_248 = g_SysWork.player_4C.chara_0.rotation_24.vy;
    save->playerHealth_240    = g_SysWork.player_4C.chara_0.health_B0;
}

void func_8003A16C() // 0x8003A16C
{
    if (!(g_SysWork.flags_22A4 & 2))
    {
        // Update `savegame_30C` with player info.
        SysWork_SavegameUpdatePlayer();

        // TODO: What is `savegame_90` used for?
        g_GameWork.savegame_90 = g_GameWork.savegame_30C;
    }
}

void SysWork_SavegameReadPlayer() // 0x8003A1F4
{
    g_SysWork.player_4C.chara_0.position_18.vx = g_SavegamePtr->playerPositionX_244;
    g_SysWork.player_4C.chara_0.position_18.vz = g_SavegamePtr->playerPositionZ_24C;
    g_SysWork.player_4C.chara_0.rotation_24.vy = g_SavegamePtr->playerRotationY_248;
    g_SysWork.player_4C.chara_0.health_B0      = g_SavegamePtr->playerHealth_240;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", SysState_SaveMenu_Update); // 0x8003A230

void SysState_EventCallFunc_Update() // 0x8003A3C8
{
    if ((g_MapEventParam->flags_8 >> 13) & 0x3F)
    {
        Savegame_EventFlagSet(g_MapEventParam->eventFlagId_2);
    }

    g_DeltaTime0 = D_800BCD84;
    g_MapOverlayHeader.mapEventFuncs_20[g_MapEventIdx]();
}

void SysState_EventSetFlag_Update() // 0x8003A460
{
    g_DeltaTime0 = D_800BCD84;
    Savegame_EventFlagSet(g_MapEventParam->eventFlagId_2);
    g_SysWork.sysState_8 = 0;
}

void SysState_EventPlaySound_Update() // 0x8003A4B4
{
    g_DeltaTime0 = D_800BCD84;

    Sd_EngineCmd(((u16)g_MapEventIdx + 0x500) & 0xFFFF);

    Savegame_EventFlagSet(g_MapEventParam->eventFlagId_2);
    g_SysWork.sysState_8 = 0;
}

void SysState_GameOver_Update() // 0x8003A52C
{
    #define TIP_COUNT 15

    extern u8   g_SysState_GameOver_TipIdx; // Only used in this func, maybe static.
    extern char D_80025448[];               // "\aGAME_OVER" - needs rodata migration.

    u16  seenTipIdxs[1];
    s32  tipIdx;
    s32  randTipVal;
    u16* temp_a0;

    switch (g_SysWork.sysStateStep_C)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            g_SysWork.field_28 = 0;

            if (g_GameWork.savegame_90.continueCount_27B < 99)
            {
                g_GameWork.savegame_90.continueCount_27B++;
            }

            func_8003B550();

            // If every game over tip has been seen, reset flag bits.
            if (g_GameWork.config_0.seenGameOverTips_2E[0] == 0x7FFF)
            {
                g_GameWork.config_0.seenGameOverTips_2E[0] = 0;
            }

            randTipVal = 0;

            seenTipIdxs[0] = g_GameWork.config_0.seenGameOverTips_2E[0];
            for (tipIdx = 0; tipIdx < TIP_COUNT; tipIdx++)
            {
                if (!Flags16b_IsSet(seenTipIdxs, tipIdx))
                {
                    if ((!(g_SysWork.field_24DC & 0x3) && (tipIdx - 13) >= 2u) ||
                        ((g_SysWork.field_24DC & 0x3) && (tipIdx - 13) < 2u))
                    {
                        randTipVal += 3;
                    }
                    else
                    {
                        randTipVal++;
                    }
                }
            }

            randTipVal = (s32)Rng_Rand16() % randTipVal;

            // `randTipVal` seems to go unused after loop, gets checked during loop and can cause early exit,
            // thereby affecting what `tipIdx` will contain.
            for (tipIdx = 0; tipIdx < TIP_COUNT; tipIdx++)
            {
                if (!Flags16b_IsSet(seenTipIdxs, tipIdx))
                {
                    if ((!(g_SysWork.field_24DC & 0x3) && (tipIdx - 13) >= 2u) ||
                        ((g_SysWork.field_24DC & 0x3) && (tipIdx - 13) < 2u))
                    {
                        if (randTipVal < 3)
                        {
                            break;
                        }

                        randTipVal -= 3;
                    }
                    else
                    {
                        if (randTipVal <= 0)
                        {
                            break;
                        }

                        randTipVal--;
                    }
                }
            }

            // Store current shown `tipIdx`, later `sysStateStep_C == 7` will set it inside `seenGameOverTips_2E`.
            g_SysState_GameOver_TipIdx = tipIdx;

            Fs_QueueStartReadTim(FILE_TIM_TIPS_E01_TIM + tipIdx, FS_BUFFER_1, &D_800A9054);
            SysWork_StateStepIncrement();

        case 1:
            func_8008616C(2, 1, 0, 0x800, 0);
            break;

        case 2:
            func_8008616C(0, 0, 0, 0x800, 0);
            SysWork_StateStepIncrement();

        case 3:
            Gfx_StringSetPosition(SCREEN_POSITION_X(32.5f), SCREEN_POSITION_Y(43.5f));
            Gfx_StringDraw(D_80025448, 0x63); // "\aGAME_OVER" - needs rodata migration.
            g_SysWork.field_28++;

            if ((g_ControllerPtrConst->btns_new_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)) ||
                g_SysWork.field_28 > 240)
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 4:
            Gfx_StringSetPosition(SCREEN_POSITION_X(32.5f), SCREEN_POSITION_Y(43.5f));
            Gfx_StringDraw(D_80025448, 0x63); // "\aGAME_OVER" - needs rodata migration.
            func_8008616C(2, 1, 0, 0x2000, 0);
            break;

        case 5:
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
            {
                // TODO: Create `inline SysWork_StateStepReset` if other code matching is needed.
                g_SysWork.sysStateStep_C = NO_VALUE;
                g_SysWork.field_28       = 0;
                g_SysWork.field_10       = 0;
                g_SysWork.timer_2C       = 0;
                g_SysWork.field_14       = 0;
                break;
            }
            else
            {
                Fs_QueueWaitForEmpty();
                func_80037188();
                SysWork_StateStepIncrement();
            }

        case 6:
            func_8008616C(2, 0, 0, 0x2000, 0);
            g_SysWork.field_28 = 0;
            Gfx_BackgroundSpriteDraw(&D_800A9054);
            break;

        case 7:
            g_SysWork.field_28++;
            Gfx_BackgroundSpriteDraw(&D_800A9054);

            if (!(g_ControllerPtrConst->btns_new_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)))
            {
                if (g_SysWork.field_28 <= 480)
                {
                    break;
                }
            }

            // TODO: some inline FlagSet func? couldn't get matching ver, but pretty sure temp_a0 can be removed somehow
            temp_a0 = &g_GameWork.config_0.seenGameOverTips_2E[(g_SysState_GameOver_TipIdx >> 5)];
            *temp_a0 |= (1 << 0) << (g_SysState_GameOver_TipIdx & 0x1F);

            SysWork_StateStepIncrement();
            break;

        case 8:
            Gfx_BackgroundSpriteDraw(&D_800A9054);
            func_8008616C(2, 1, 0, 0x2000, 0);
            break;

        default:
            g_MapOverlayHeader.func_CC(0);
            SysWork_StateSetNext(0);
            Game_WarmBoot();
            break;
    }

    if (g_SysWork.sysStateStep_C >= 2 || g_GameWork.gameState_594 != GameState_InGame)
    {
        g_SysWork.field_22A0 |= 1 << 0;
    }
}

void GameState_MapEvent_Update() // 0x8003AA4C
{
    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        g_IntervalVBlanks               = 1;
        g_Gfx_ScreenFade                = 6;
        g_GameWork.gameStateStep_598[0] = 1;
    }

    D_800A9A0C = (g_Gfx_ScreenFade & 7) == 5 && Fs_QueueDoThingWhenEmpty() != 0;

    Savegame_EventFlagSet(g_MapEventParam->eventFlagId_2);

    g_MapOverlayHeader.mapEventFuncs_20[g_MapEventIdx]();

    Gfx_BackgroundSpriteDraw(&D_800A902C);
}

// TODO: RODATA migration
#ifdef NON_MATCHING
void GameState_MainMenu_Update()
{
    s32 nextGameStates[5] = // 0x80025480
    {
        GameState_SaveScreen, 
        GameState_DeathLoadScreen,
        GameState_MovieOpening,
        GameState_OptionScreen,
        GameState_MovieIntro
    };
    
    s32 temp_s2;
    s32 var_v0;
    s32 var_2;
    s_ShSavegame* save0;
    e_GameState prevState;

    func_80033548();
    temp_s2 = ((D_800A9A80 + 1) % 0x3) != 0;
    
    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        D_800A9A74 = 0;
        
        if (temp_s2 != 0)
        {
            g_SysWork.flags_2298 = 0x20;
        }
        else
        {
            g_GameWork.gameStateStep_598[0] = 1;
        }
    }
    
    switch (D_800A9A74)
    {
        case 0:
            g_GameWork.background2dColor_R_58C = 0;
            g_GameWork.background2dColor_G_58D = 0;
            g_GameWork.background2dColor_B_58E = 0;
            
            Gfx_ClearRectInterlaced(0, 32, SCREEN_WIDTH, FRAMEBUFFER_HEIGHT_INTERLACED, 0, 0, 0);
            Gfx_Init(SCREEN_WIDTH, 1);
            
            g_IntervalVBlanks = 1;
            g_Gfx_ScreenFade  = 6;
            D_800B5C30        = 0x2000;
            D_800A9A74++;
        
        case 1:
            if (temp_s2 != 0)
            {
                func_80034964();
                
                if (g_GameWork.gameStateStep_598[0] == 1 && g_SysWork.timer_20 == 0)
                {
                    D_800A9A80++;
                }
                
                if (g_GameWork.gameState_594 == GameState_MainLoadScreen)
                {
                    D_800A9A80++;
                }
            }
            
            D_800A9A7C = 12;
            
            if (g_GameWork.savegame_90.playerHealth_240 > 0)
            {
                D_800A9A7C = 14;
            }
            
            if (D_800BCD28 > 0)
            {
                D_800A9A7C |= (1 << 0) | (1 << 1);
                
                if (D_800A9A88 < D_800BCD28 && D_800A9A78 != 0)
                {
                    D_800A9A78 = 1;
                }
            }
            else if (D_800A9A88 > 0)
            {
                while(!(D_800A9A7C & (1 << D_800A9A78)))
                {
                    D_800A9A78++;
                }
            }
            
            D_800A9A7C |= D_800A9A7C << 5;
            
            if (g_ControllerPtrConst->field_18 & (ControllerFlag_LStickUp | ControllerFlag_LStickDown))
            {
                Sd_EngineCmd(0x519);
                g_GameWork.gameState_594 = GameState_MainMenu;
                
                if (g_GameWork.gameStateStep_598[0] != 1)
                {
                    g_GameWork.gameStateStep_598[0] = 1;
                    Fs_QueueReset();
                }
            }
            
            if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickUp)
            {
                D_800A9A78 += 5;
                while(!(D_800A9A7C & (1 << --D_800A9A78)))
                {
                }
            }
            
            if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickDown)
            {                
                while(!(D_800A9A7C & (1 << ++D_800A9A78)))
                {
                }
            }
            
            D_800A9A78 = D_800A9A78 % 5;
            
            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                g_GameWork.gameState_594 = GameState_MainMenu;
                
                if (g_GameWork.gameStateStep_598[0] != 1)
                {
                    g_GameWork.gameStateStep_598[0] = 1;
                    Fs_QueueReset();
                }
                
                g_Gfx_ScreenFade = 2;
                D_800A9A74      += 1;
                
                if (D_800A9A78 < 2U)
                {
                    Sd_EngineCmd(0x501);
                }
                else
                {
                    Sd_EngineCmd(0x51B);
                }
                
                switch (D_800A9A78)
                {
                    case 1:
                        if (g_GameWork.savegame_90.playerHealth_240 > 0)
                        {
                            g_GameWork.savegame_30C = g_GameWork.savegame_90;
                        }
                        else
                        {
                            GameFs_SaveLoadBinLoad();
                        }
                        
                        func_80035178();
                        g_SysWork.flags_2298 = 0x10;
                        GameFs_MapLoad(g_SavegamePtr->mapOverlayId_A4);
                        break;
                    
                    case 0:
                        GameFs_SaveLoadBinLoad();
                        break;
                    
                    case 2:
                        g_Gfx_ScreenFade = 0;
                        D_800A9A74       = 3;
                        break;
                    
                    case 3:
                        GameFs_OptionBinLoad();
                        break;
                    
                    case 4:
                        break;
                }
            }
            
            D_800A9A88 = D_800BCD28;
        
        default:
            break;
        
        case 3:
            if (temp_s2 != 0)
            {
                func_80034964();
                
                if ((g_GameWork.gameStateStep_598[0] == 1) && (g_SysWork.timer_20 == 0))
                {
                    D_800A9A80++;
                }
                
                if (g_GameWork.gameState_594 == GameState_MainLoadScreen)
                {
                    D_800A9A80++;
                }
            }
            
            if (g_ControllerPtrConst->field_18 & (ControllerFlag_LStickUp | ControllerFlag_LStickDown) || g_ControllerPtrConst->btns_new_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                g_GameWork.gameState_594 = GameState_MainMenu;
                
                if (g_GameWork.gameStateStep_598[0] != 1)
                {
                    g_GameWork.gameStateStep_598[0] = 1;
                    Fs_QueueReset();
                }
            }
            
            if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickUp)
            {
                var_v0 = 2;
                
                if (D_800A9A84 > 0)
                {
                    var_v0 = D_800A9A84 - 1;
                }
                
                D_800A9A84 = var_v0;
            }
            
            if (g_ControllerPtrConst->field_18 & ControllerFlag_LStickDown)
            {
                var_2 = 0;
                
                if (D_800A9A84 < 2)
                {
                    var_2 = D_800A9A84 + 1;
                }
                
                D_800A9A84 = var_2;
            }
            
            if (g_ControllerPtrConst->field_18 & (ControllerFlag_LStickUp | ControllerFlag_LStickDown))
            {
                Sd_EngineCmd(0x519u);
            }
            
            if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                Game_SavegameInitialize(0, D_800A9A84 - 1);
                func_80035178();
                g_SysWork.flags_2298 = 4;
                GameFs_MapLoad(0);
                GameFs_StreamBinLoad();
                Sd_EngineCmd(0x501);
                g_Gfx_ScreenFade = 2;
                D_800A9A74       = 4;
            }
            else if (g_ControllerPtrConst->btns_new_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                Sd_EngineCmd(0x51A);
                D_800A9A74 = 1;
            }
            break;
        
        case 2:
        case 4:
            if ((g_Gfx_ScreenFade & 7) == 5)
            {
                func_800323C8(320, 0); // old idb Sys_GFXReinit_800323C8(width, interlace_flag)
                Fs_QueueWaitForEmpty();
                
                if (g_GameWork.savegame_90.playerHealth_240 > 0)
                {
                    nextGameStates[1] = 10;
                }
                
                if (D_800A9A78 == 2)
                {
                    Chara_PositionUpdateFromParams(g_MapOverlayHeader.mapAreaLoadParams_1C);
                }
                
                func_8002E830();
                
                prevState                       = g_GameWork.gameState_594;
                g_GameWork.gameStateStep_598[0] = prevState;
                g_GameWork.gameState_594        = nextGameStates[D_800A9A78];
                g_SysWork.timer_1C              = 0;
                g_GameWork.gameStatePrev_590    = prevState;
                g_GameWork.gameStateStep_598[0] = 0;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
                SysWork_StateSetNext(SysState_Gameplay);
            }
            break;
    }
    
    if (g_ControllerPtrConst->btns_held_C != 0)
    {
        g_SysWork.timer_20 = 0;
    }
    
    if (temp_s2 == 0)
    {
        switch (g_GameWork.gameStateStep_598[0])
        {
            case 1:
                if (g_SysWork.timer_20 > 1740)
                {
                    GameFs_StreamBinLoad();
                    g_GameWork.gameStateStep_598[0]++;
                }
                break;
            
            case 2:
                if (Fs_QueueGetLength() == 0)
                {
                    D_800A9A80++;
					Game_StateSetNext_ClearStateSteps(GameState_MovieIntro);
                }
                break;
        }
    }
    
    if (g_GameWork.gameState_594 == GameState_MainMenu)
    {
        func_8003B758();
        func_8003B560();
        
        if (D_800A9A74 < 3)
        {
            func_8003B568();
            return;
        }
        
        func_8003B678(D_800A9A84);
        return;
    }
    
    *(s32*)0x1F800000 = 0x200000;
    *(s32*)0x1F800004 = 0x01C00140;
    ClearImage2((RECT* )0x1F800000, 0u, 0u, 0u);
    Gfx_Init(0x140u, 0);
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", GameState_MainMenu_Update); // 0x8003AB28
#endif

void func_8003B550() // 0x8003B550
{
    D_800A9A78 = 1;
}

void func_8003B560() {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003B568); // 0x8003B568

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003B678); // 0x8003B678

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003B758); // 0x8003B758

void func_8003B7BC()
{
    // Can't be `s32*` since 462 doesn't divide by 4, so I'm guessing it's `s8`.
    s8* s0 = 0x801E2432;

    memset(s0, 0, 462);
    D_800BCDE0 = s0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003B7FC); // 0x8003B7FC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003B838); // 0x8003B838

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003BA08); // 0x8003BA08

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003BAC4); // 0x8003BAC4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003BBF4); // 0x8003BBF4

void func_8003BC8C() // 0x8003BC8C
{
    if (D_800A9EB0 == ((D_800A9EB0 / 5) * 5))
    {
        func_8003BBF4(D_800A9EB0);
    }

    D_800A9EB0++;
    func_8003BA08();
}

void func_8003BCF4() // 0x8003BCF4
{
    s32 i;

    func_8003B7BC();

    for (i = 0; i < 30; i++)
    {
        func_8003BBF4();
    }
}

// TODO: Remake this whenever we have further context of `D_8002500C`.
s32 func_8003BD2C() // 0x8003BD2C
{
    return (D_800BCE18.field_0 - &D_8002500C) >> 2;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003BD48);

void func_8003BE28() // 0x8003BE28
{
    func_80069820(D_800BCE14);
}

s32 func_8003BE50(s32 idx) // 0x8003BE50
{
    return D_800BCE18.field_18[idx] + 32;
}

void GameFs_BgEtcGfxLoad() // 0x8003BE6C
{
    Fs_QueueStartReadTim(FILE_TIM_BG_ETC_TIM, FS_BUFFER_1, &D_800A9EB4);
}

void GameFs_BgItemLoad() // 0x8003BE9C
{
    D_800BCE18.field_1BE4.queueIdx_1000 = Fs_QueueStartRead(FILE_BG_BG_ITEM_PLM, &D_800BCE18.field_1BE4);
}

void func_8003BED0() // 0x8003BED0
{
    s_800BE9FC* D_800BE9FC = &D_800BCE18.field_1BE4;

    if (Fs_QueueIsEntryLoaded(D_800BE9FC->queueIdx_1000) == 0 || D_800BE9FC->field_2 != 0)
    {
        return;
    }

    func_800560FC(&D_800BCE18.field_1BE4);
    func_80056504(&D_800BCE18.field_1BE4, &D_80025528, &D_800A9EBC, 1);
    func_80056504(&D_800BCE18.field_1BE4, &D_80025530, &D_800A9EC4, 1);
    func_80056954(&D_800BCE18.field_1BE4);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003BF60); // 0x8003BF60

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003C048); // 0x8003C048

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003C0C0); // 0x8003C0C0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003C110); // 0x8003C110

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003C1AC); // 0x8003C1AC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003C220); // 0x8003C220

void func_8003C2EC()
{
    func_80041FF0();
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003C30C); // 0x8003C30C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003C368); // 0x8003C368

void func_8003C3A0() // 0x8003C3A0
{
    D_800BCE18.field_4 = 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003C3AC); // 0x8003C3AC

s32 func_8003C850() // 0x8003C850
{
    func_8003C3AC();
    func_80043740();
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003C878);

void func_8003C8F8(s_func_8003C8F8* arg0, s8* arg1) // 0x8003C8F8
{
    arg0->field_25 = 0;
    arg0->field_0 = 0;

    func_80056D64((s8*)&arg0->field_16, arg1);

    arg0->field_24 = 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003C92C);

void func_8003CB3C(s_800BCE18* arg0)
{
    arg0->field_2BE8 = 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003CB44);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003CBA4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003CC7C);

s32 func_8003CD5C() // 0x8003CD5C
{
    return D_800BCE18.field_1BAC;
}

void func_8003CD6C(s_MapWork* arg0) // 0x8003CD6C
{
    s32 var_a0;
    s8  temp_v0;

    temp_v0 = arg0->field_F;
    var_a0  = NO_VALUE;
    if (temp_v0 != NO_VALUE)
    {
        var_a0 = temp_v0 + 0x80;
    }

    func_8003CDA0(var_a0);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003CDA0);

void func_8003D01C() // 0x8003D01C
{
    D_800BCE18.field_1BC4 &= ~(1 << 31);
}

void func_8003D03C() // 0x8003D03C
{
    D_800BCE18.field_1BC4 |= 1 << 31;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003D058);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003D160);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003D21C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003D354);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003D3BC);

s32 func_8003D444(s32 idx) // 0x8003D444
{
    return D_800BCE18.field_18[idx] != 0;
}

void func_8003D460() {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003D468);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003D550);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003D5B4);

void func_8003D6A4(u8* arg0) // 0x8003D6A4
{
    u8 temp_v0;

    temp_v0 = *arg0;
    if (temp_v0 != 0)
    {
        D_800BCE18.field_18[temp_v0] = 0;
        func_8003C1AC();
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003D6E0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003D7D4);

void func_8003D938() // 0x8003D938
{
    func_8003D9C8(&D_800BCE18.field_164C);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003D95C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003D9C8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003DA9C);

s32 func_8003DD74(s32 arg0, s32 arg1) // 0x8003DD74
{
    return (arg1 << 10) & 0xFC00;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003DD80);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003DE60);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003DF84);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003E08C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003E194);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003E238);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003E388);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003E414);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003E4A0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003E544);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003E5E8);

void GameFs_FlameGfxLoad() // 0x8003E710
{
    Fs_QueueStartReadTim(FILE_TIM_FLAME_TIM, FS_BUFFER_1, &D_800A9FA8);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003E740);

/**
 * TODO: Please investigate me!
 */
void func_8003EB54() // 0x8003EB54
{
    s_StructUnk0*  temp_a0;
    s_StructUnk1*  temp_v0;
    GsCOORDINATE2* temp_v1;

    g_SysWork.field_2378 = 0x1000;

    temp_v1 = &g_SysWork.playerBoneCoords_890[0];
    temp_a0 = &g_SysWork.field_2360;

    g_SysWork.field_235C = temp_v1;
    g_SysWork.field_236C = temp_v1;
    g_SysWork.field_2360.field_0 = 0;

    temp_a0->field_4 = -0x333;
    temp_a0->field_8 = -0x2000;

    g_SysWork.field_2370.field_0 = 0x71;

    temp_v0 = &g_SysWork.field_2370;
    temp_v0->field_2 = 0;
    temp_v0->field_4 = 0;
}

void func_8003EBA0() // 0x8003EBA0
{
    s_SysWork*    temp0 = &g_SysWork;
    s_StructUnk0* temp1 = &temp0->field_2360;
    s_StructUnk1* temp2 = &temp0->field_2370;

    temp0->field_2378 = 0x1000;
    temp0->field_235C = &g_SysWork.playerBoneCoords_890[1];
    temp0->field_236C = g_SysWork.playerBoneCoords_890;
    temp1->field_0    = -0x147;
    temp1->field_4    = -0x47A;
    temp1->field_8    = 0x1EB;
    temp2->field_0    = -0xAA;
    temp2->field_2    = 0;
    temp2->field_4    = 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003EBF4);

void func_8003ECBC() // 0x8003ECBC
{
    g_SysWork.unk_2388[21] = 1;
    g_SavegamePtr->flags_AC &= ~2;
}

void func_8003ECE4() // 0x8003ECE4
{
    g_SysWork.unk_2388[21] = 0;
    g_SavegamePtr->flags_AC |= 1 << 1;
}

void func_8003ED08() // 0x8003ED08
{
    u8 var;

    var = g_SysWork.unk_2388[21] ^ 1;
    g_SysWork.unk_2388[21] = var;

    if (var == 1)
    {
        g_SavegamePtr->flags_AC &= ~(1 << 1);
        return;
    }

    g_SavegamePtr->flags_AC |= 1 << 1;
}

u8 func_8003ED64() // 0x8003ED64
{
    return g_SysWork.field_239D;
}

void func_8003ED74(s32 arg0, s32 arg1) // 0x8003ED74
{
    func_8003EF10(arg0, arg1, 0, 0, 0, 0);
    func_8003F170();
}

void func_8003EDA8() // 0x8003EDA8
{
    g_SysWork.field_239C = 1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003EDB8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003EE30);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003EEDC);

void func_8003EF10(s32 idx0, s32 idx1, s32 arg4, s32 arg5, s32 arg6, s32 arg7) // 0x8003EF10
{
    func_8003EF74(D_800A93CC[idx0].field_0, D_800A93CC[idx1].field_0, arg4, arg5, arg6, arg7);  
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003EF74);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003F08C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003F170);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003F4DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003F654);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003F6F0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003F7E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003F838);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003FCB0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003FD38);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003FE04);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003FEC0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_800314EC", func_8003FF2C);

void func_80040004(s_800BCE18* arg0) // 0x80040004
{
    D_800BCE18.field_1BD8 = &arg0->field_D2C;
}

void func_80040014() // 0x80040014
{
    func_80069860(g_SysWork.player_4C.chara_0.position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz, D_800BCE18.field_1BD8);
};
