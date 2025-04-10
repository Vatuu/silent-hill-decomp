#include "game.h"

#include <memory.h>
#include <libgte.h>
#include <libgpu.h>
#include <libetc.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"

void func_8002E630() 
{
    s_800B5508* ptr;
    s32 i;

    func_800303E4();

    D_800B5480 = 0; 

    // Clear arrays.
    bzero(D_800B5508, 1816);
    bzero(D_800B2780, 768);

    for (i = 0; i < 8; i++) 
    {
        D_800B5508[i].field_0 = 0;
        
        func_8002E730(i);

        switch (i) 
        {                          
            case 0:
                ptr = D_800B2780;
                break;

            case 4:
                ptr = D_800B3680;
                break;

            default:
                ptr = D_800B4580;
                break;
        }

        D_800B5508[i].field_14 = ptr;

        func_8002E6E4(i);
    } 
}

void func_8002E6E4(s32 idx)
{
    s_800B5508* temp_v0;
    s_800B5508* temp_s0;

    temp_v0 = &D_800B5508;
    temp_s0 = &temp_v0[idx];
    temp_s0->field_0 = 0;

    func_8002E730(idx);
    bzero(temp_s0->field_14, 3840);

    temp_s0->field_18 = 0;
}

void func_8002E730(s32 idx) 
{
    s32 i;

    for (i = 0; i < 15; i++) 
    {
        D_800B5508[idx].field_4[i] = 0;
    }
}

s32 func_8002E76C(s32 idx) 
{
    s32 ret;
    s32 i;

    ret = 1;

    for (i = 0; i < 15; i++)
    {    
        if (D_800B5508[idx].field_4[i] != 0) 
        {
            ret = 0; 
            break;
        }
    }

    return ret;
}

void func_8002E7BC()
{
    s_800B55E8* unk;

    if (D_800B5480 == 1)
        return;
    
    D_800B5480 = 1;
    func_8002E8E4();
    func_80030414();
    
    D_800B55E8[0].field_0 = 0;
    D_800B55E8[0].field_4 = 0;
    D_800B55E8[0].field_8 = 0;
    D_800B55E8[0].field_C = 0;
    D_800B55E8[0].field_10 = 0;
    D_800B55E8[0].field_14 = 0;
    D_800B55E8[1].field_0 = 0;

    unk = &D_800B55E8[1];
    unk->field_4 = 0;
    unk->field_8 = 0;
    unk->field_C = 0;
    unk->field_10 = 0;
    unk->field_14 = 0;
}

void func_8002E830()
{
    if (D_800B5480 != 0) 
    {
        D_800B5480 = 0;
        func_80030640();
    }
}

void func_8002E85C()
{
    D_800B5618 = 1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002E86C);

s32 func_8002E898() 
{
    s32 ret;
    s32 i;

    ret = 0;

    for (i = 0; i < 8; i++)
    {
        ret |= D_800B5508[i].field_0 << (i * 3);
    }

    return ret;
}

void func_8002E8D4()
{
    D_800B5618 = 1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002E8E4);

s32 func_8002E914() 
{
    s32 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < 8; i++)
    {
        ret |= D_800B5508[i].field_0 << (i * 2);
    }

    return ret;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002E94C);

s32 func_8002E990()
{
    return D_800B55FC;
}

s32 func_8002E9A0(s32 idx) 
{
    s32 ret;
    s32 i;

    ret = 0;

    for (i = 0; i < 15; i++)
    {
        ret |= D_800B5508[idx].field_4[i] << (i * 2);
    }

    return ret;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002E9EC);

s32 func_8002EA28(s32 idx) 
{
    s32 ret;
    s32 i;

    ret = 0;

    for (i = 0; i < 15; i++)
    {
        if (D_800B5508[idx].field_4[i] != 0)
        {
            ret++;
        }
    }

    return ret;
}

s32 func_8002EA78(s32 idx) 
{
    return D_800B5508[idx].field_18 - func_8002EA28(idx);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002EABC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002EB88);

void func_8002ECE0(s_800B55E8* arg0)
{
    if (func_8003030C(arg0->field_4) != 0)
    {
        arg0->field_14 = 11;
        D_800B5508[arg0->field_4].field_0 = 3;
        
        func_8002E730(arg0->field_4);
        
        D_800B5508[arg0->field_4].field_18 = 15;
    }
    else
    {
        arg0->field_14 = 10;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002ED7C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002F278);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002F2C4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002F61C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002FB64);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002FBB4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002FC3C);

void SaveGame_CopyWithChecksum(s_ShSaveGameContainer* dest, s_ShSaveGame* src) // 0x8002FCCC
{
    bzero(dest, sizeof(s_ShSaveGameContainer));
    memcpy(&dest->saveGame_0, src, sizeof(s_ShSaveGame));
    SaveGame_ChecksumUpdate(&dest->footer_27C, &dest->saveGame_0, sizeof(s_ShSaveGameContainer));
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002FD5C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002FDB0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002FE70);

void SaveGame_ChecksumUpdate(s_ShSaveGameFooter* saveFooter, s8* saveData, s32 saveDataLength) // 0x8002FF30
{
    u8 checksum;

    saveFooter->checksum_0[0] = saveFooter->checksum_0[1] = 0;
    saveFooter->magic_2                                   = SAVEGAME_FOOTER_MAGIC;
    checksum                                              = SaveGame_ChecksumGenerate(saveData, saveDataLength);
    saveFooter->checksum_0[0] = saveFooter->checksum_0[1] = checksum;
}

s32 SaveGame_ChecksumValidate(s_ShSaveGameFooter* saveFooter, s8* saveData, s32 saveDataLength) // 0x8002FF74
{
    s32 isValid = 0;

    if (saveFooter->checksum_0[0] == SaveGame_ChecksumGenerate(saveData, saveDataLength))
    {
        isValid = saveFooter->magic_2 == SAVEGAME_FOOTER_MAGIC;
    }

    return isValid;
}

u8 SaveGame_ChecksumGenerate(s8* saveData, s32 saveDataLength) // 0x8002FFD0
{
    u8  checksum = 0;
    int i        = 0;

    for (i = 0; i < saveDataLength;)
    {
        i++;
        checksum ^= *saveData++;
    }

    return checksum;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030000);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800300B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030288);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003030C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030334);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030370);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800303E4);

void func_80030414() 
{
    func_80030444();
    func_8003045C();
    func_80030530();
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030444);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003045C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030530);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030640);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030668);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800306C8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030734);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800307BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030810);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030820);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030884);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030894);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800308A4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800308B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800308C4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800308D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800308E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800309FC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030A0C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030AD8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030C88);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030DC8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030F7C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800310B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80031184);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80031260);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800314A4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800314EC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800317CC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80031AAC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80031CCC);

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", Gfx_DebugStringDraw);

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800321EC);

void Gfx_ClearRectInterlaced(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b)
{
    setRECT((RECT*)PSX_SCRATCH, x, y, w, h);
    VSync(0);
    ClearImage2((RECT*)PSX_SCRATCH, r, g, b);
    DrawSync(0);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800323C8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", Gfx_Init);

void Settings_ScreenXYSet(s32 x, s32 y) // 0x800324F4
{
    Settings_DispEnvXYSet(&GsDISPENV, x, y);
}

void Settings_DispEnvXYSet(DISPENV* display, s32 x, s32 y) // 0x80032524
{
    s_GameWork* gameWorkPtr;

    x = (x < -11) ? -11 : ((x > 11) ? 11 : x);
    y = (y < -8) ? -8 : ((y > 8) ? 8 : y);

    gameWorkPtr = g_GameWorkPtr0;
    gameWorkPtr->screenPosX_1C = x;
    gameWorkPtr->screenPosY_1D = y;

    display->screen.x = gameWorkPtr->screenPosX_1C;
    display->screen.y = gameWorkPtr->screenPosY_1D + 8;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800325A4);
/*void func_800325A4(DR_MODE* arg0) 
{
    char* temp[2];

    if (D_800BCD0C & 8) 
    {
        temp[0] = 0; 

        SetDrawMode(arg0, 0, 1, 32, NULL);
    }
    else 
    {
        temp[0] = 0;

        SetDrawMode(arg0, 0, 1, 64, NULL);
    }
}*/

extern s32 D_800B5C28;

int func_800325F8() 
{
    return 4096 - D_800B5C28;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003260C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003289C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80032904);

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
    Gfx_StringPosition(SCREEN_POSITION_X(33.75f), SCREEN_POSITION_Y(43.5f));
    Gfx_StringDraw(&D_8002510C, 100);
}

void func_80032D1C()
{
    s32 gameStateStep0;
    s32 gameState;
    s32 unkGameStateVar;

    gameStateStep0 = g_GameWork.gameStateStep_598[0];
    switch (gameStateStep0)
    {
        case 0:
            g_GameWork.field_58C = 0;
            g_GameWork.field_58D = 0;
            g_GameWork.field_58E = 0;

            Gfx_Init(0x140, 0);
            g_SysWork.timer_20 = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            g_GameWork.gameStateStep_598[0]++;
            break;

        case 1:
            if (!(func_80045B28() & 0xFF))
            {
                unkGameStateVar = D_800A9774[g_GameWork.gameStateStep_598[1]];
                if (unkGameStateVar != 0)
                {
                    SD_EngineCmd(unkGameStateVar);
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

            D_800BCD0C = gameStateStep0;
            g_GameWork.gameStateStep_598[0]++;
            break;

        case 3:
            if ((D_800BCD0C & 7) == ((1 << 0) | (1 << 2)))
            {
                Fs_QueueWaitForEmpty();

                gameState = g_GameWork.gameState_594;
                
                g_SysWork.timer_1C = 0;
                g_SysWork.timer_20 = 0;

                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;

                g_SysWork.sysState_8 = 0;
                g_SysWork.timer_24 = 0;
                g_SysWork.sysStateStep_C = 0;
                g_SysWork.field_28 = 0;
                g_SysWork.field_10 = 0;
                g_SysWork.timer_2C = 0;
                g_SysWork.field_14 = 0;

                g_GameWork.gameStateStep_598[0] = gameState;
                g_GameWork.gameState_594 = gameState + 1;
                g_GameWork.gameStatePrev_590 = gameState;
                g_GameWork.gameStateStep_598[0] = 0;
            }
            break;

        default:
            break;
    }

    func_80033548();
    func_800314EC(&g_MainImg0);
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
    JOY_Init();
    VSyncCallback(&Gfx_VSyncCallback);
    InitGeom();
    func_8004BB10(); // Initializes something for graphics.
    func_800890B8();
    SD_DriverInit();

    // Run game.
    while (true)
    {
        g_MainLoop_FrameCount++;

        JOY_ReadP1();
        Demo_JoyUpdate();
        JOY_ControllerDataUpdate();

        if (MainLoop_ShouldWarmReset() == 2)
        {
            Game_WarmBoot();
            continue;
        }

        g_ObjectTableIdx = GsGetActiveBuff();

        if ((u32)(g_GameWork.gameState_594 - 10) < 2)
        {
            D_800C7018 = TEMP_MEMORY_ADDR + (g_ObjectTableIdx << 17);
        }
        else if (g_GameWork.gameState_594 == 14)
        {
            D_800C7018 = TEMP_MEMORY_ADDR + (g_ObjectTableIdx * 40000);
        }
        else
        {
            D_800C7018 = TEMP_MEMORY_ADDR + (g_ObjectTableIdx << 15);
        }

        GsClearOt(0, 0, &g_ObjectTable0[g_ObjectTableIdx]);
        GsClearOt(0, 0, &g_ObjectTable1[g_ObjectTableIdx]);

        g_SysWork.field_22A0 = 0;

        // State machine?
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

        if (!(func_80045B28() & 0xFF))
        {
            Fs_QueueUpdate();
        }

        func_80089128();
        func_8008D78C(); // Camera update?
        DrawSync(0);

        if (g_SysWork.flags_22A4 & 2)
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
            if (g_SysWork.sysState_8 != 0)
            {
                g_VBlanks = VSync(-1) - g_PrevVBlanks;
                g_PrevVBlanks = VSync(-1);
                VSync(0);
            }
            else
            {
                if (D_800BCD0C != 1)
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

            // Update VBlanks.
            g_UncappedVBlanks = g_VBlanks;
            g_VBlanks = MIN(g_VBlanks, V_BLANKS_MAX);
            
            // Update V count.
            vCount = MIN(GsGetVcount(), H_BLANKS_PER_FRAME_MIN); // NOTE: Will call GsGetVcount() twice.
            vCountCopy = vCount;
        }

        // Update delta time.
        g_DeltaTime0 = FP_MULTIPLY(vCount, H_BLANKS_FP_TO_SEC_SCALE, Q12_SHIFT);
        g_DeltaTime1 = FP_MULTIPLY(vCountCopy, H_BLANKS_FP_TO_SEC_SCALE, Q12_SHIFT);
        g_DeltaTime2 = FP_MULTIPLY(vCount, H_BLANKS_UNKNOWN_SCALE, Q12_SHIFT); // TODO: Unknown time scale.
        GsClearVcount();

        // Draw objects?
        GsSwapDispBuff();
        GsSortClear(g_GameWork.field_58C, g_GameWork.field_58D, g_GameWork.field_58E, &g_ObjectTable0[g_ObjectTableIdx]);
        GsDrawOt(&g_ObjectTable0[g_ObjectTableIdx]);
        GsDrawOt(&g_ObjectTable1[g_ObjectTableIdx]);
    }
}

void Settings_ScreenAndVolUpdate()
{
    s32 soundCmd;

    Settings_ScreenXYSet(g_GameWork.screenPosX_1C, g_GameWork.screenPosY_1D);
    
    soundCmd = (g_GameWork.optSoundType_1E != 0) ? 1 : 2;
    SD_EngineCmd(soundCmd);

    SD_SetVolume(OPT_SOUND_VOLUME_MAX, g_GameWork.optVolumeBgm_1F, g_GameWork.optVolumeSe_20);
}

void Settings_RestoreDefaults() // 0x8003342c
{
    g_GameWork.optWeaponCtrl_23 = 1;
    g_GameWork.optBrightness_22 = 3;

    Settings_RestoreControlDefaults(0);

    g_GameWork.optVibrationEnabled_21 = OPT_VIBRATION_ENABLED;
    g_GameWork.optVolumeBgm_1F = OPT_SOUND_VOLUME_MAX;
    g_GameWork.optVolumeSe_20 = OPT_SOUND_VOLUME_MAX;

    Settings_ScreenAndVolUpdate();

    g_GameWork.optBloodColor_24 = 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", Settings_RestoreControlDefaults);

void nullsub_800334C8() {}

void func_800334D0() {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800334D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80033548);

void SysWork_Clear() // 0x800340E0
{
    bzero(&g_SysWork, sizeof(s_SysWork));
}

s32 MainLoop_ShouldWarmReset() // 0x80034108
{
    #define RESET_BTN_FLAGS (Pad_Select | Pad_Start)
    #define UNK_BTN_FLAGS_0 (Pad_Select | Pad_Start | Pad_L2 | Pad_R2 | Pad_L1 | Pad_R1)
    #define UNK_BTN_FLAGS_1 (Pad_Start | Pad_Triangle | Pad_Square)

    if (g_GameWork.gameState_594 < GameState_MovieIntroAlternate)
    {
        return 0;
    }

    if (g_GameWork.gameState_594 == GameState_Unk8 && g_GameWork.gameStateStep_598[0] == 4)
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
    if ((g_ControllerPtr0->btns_held_C & RESET_BTN_FLAGS) != RESET_BTN_FLAGS)
    {
        D_800A976C = 0;
    }

    if (D_800A976C >= 121)
    {
        return 2; 
    }
    else if (g_ControllerPtr0->btns_held_C == UNK_BTN_FLAGS_0 && (g_ControllerPtr0->btns_new_10 & UNK_BTN_FLAGS_0))
    {
        return 2; 
    }
    else if (g_ControllerPtr0->btns_held_C == UNK_BTN_FLAGS_1 && (g_ControllerPtr0->btns_new_10 & Pad_Start))
    {
        return 2; 
    }

    return (g_SysWork.flags_22A4 & (1 << 8)) ? 2 : 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", Game_WarmBoot);

void JOY_Init() // 0x8003441C
{
    PadInitDirect(&g_GameWork.rawPadData_5B4, g_ControllerPtr1);
    PadStartCom();
}

void JOY_ReadP1() // 0x80034450
{
    s_ControllerData* cont = &g_GameWork.controllers_38[0];

    // NOTE: memcpy is close, reads rawPadData_5B4 as two s32s, but doesn't give match.
    // memcpy(&cont->analogPad_0, &g_GameWork.rawPadData_5B4, sizeof(s_AnalogPadData));

    *(s32*)&cont->analogPad_0 = *(s32*)&g_GameWork.rawPadData_5B4;
    *(s32*)&cont->analogPad_0.right_x = *(s32*)&g_GameWork.rawPadData_5B4.right_x;

    // Alternate
    // ((s32*)&cont->analogPad_0)[0] = ((s32*)&g_GameWork.rawPadData_5B4)[0];
    // ((s32*)&cont->analogPad_0)[1] = ((s32*)&g_GameWork.rawPadData_5B4)[1];
}

void JOY_Update() // 0x8003446C
{
    JOY_ReadP1();
    JOY_ControllerDataUpdate();
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", JOY_ControllerDataUpdate);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", ControllerData_AnalogToDigital);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003483C);

void func_800348C0()
{
    bzero(&D_800A9944, 0x48);
}

void func_800348E8()
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

            SD_EngineCmd(1502);
            SD_EngineCmd(1501);
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80034964);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80034E58);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80034EC8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80034F18);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80034FB8);

void Game_SaveGameInitialize(s8 overlayIdx, s32 difficulty) // 0x800350BC
{
    s32  i;
    s32* var_a2;

    bzero(g_SaveGamePtr, sizeof(s_ShSaveGame));

    g_SaveGamePtr->mapOverlayIdx_A4 = overlayIdx;

    // -1 = easy, 0 = normal, 1 = hard.
    difficulty = CLAMP(difficulty, -1, 1);

    var_a2 = g_SaveGamePtr->field_B0;

    g_SaveGamePtr->field_260      = (g_SaveGamePtr->field_260 & 0x0FFFFFFF) | (difficulty << 28);
    g_SaveGamePtr->mapIdx_A9 = 1;

    for (i = 0; i < 45; i++)
    {
        var_a2[44] = NO_VALUE;
        var_a2--;
    }

    Game_SaveGameResetPlayer();
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035178);

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

    func_800546A8((u8)g_SysWork.field_47);
}

s32 func_8003528C(s32 idx0, s32 idx1)
{
    u32 tempField_8;
    u32 tempField_4;
    s_800A992C* ptr0;
    s_800A992C* ptr1;

    ptr0 = &D_800A992C[idx0];
    ptr1 = &D_800A992C[idx1];
    tempField_4 = ptr0->field_4;
    tempField_8 = ptr1->field_8;

    if (tempField_4 >= (tempField_8 + ptr1->field_10) ||
        tempField_8 >= (tempField_4 + ptr0->field_C))
    {
        return 0;
    }

    return 1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800352F8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035338);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035560);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003569C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035780);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800358A8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800358DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035924);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003596C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003599C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035AB0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035AC8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035B04);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035B58);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035B98);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035BBC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035BE0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035DB4);

void func_80035E1C()
{
    s32 i;
    for (i = 0; i < 9; i++)
    {
        g_SysWork.field_2748[i] = 0;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035E44);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035ED0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035F4C);

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
        D_800C9590 = arg0;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80036420);

s32 func_8003647C() // 0x8003647C
{
    return g_SaveGamePtr->field_A5 > D_800C9584;
}

s32 func_80036498() // 80036498
{
    return !(g_SaveGamePtr->field_A5 > D_800C9584);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800364BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003652C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800365B8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80036B5C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80036E48);

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
        var3 = (*ptr1 >> shift) & 0xF;
        if (i != 0 && var3 == 11 && var0 != 0)
        {
            var1 |= 11 << shift;
        }

        var0 = 0;
        if (var3 != 0 && var3 != 11)
        {
            var1 |= 11 << shift;
            var0 = 1;
        }

        if ((i & 3) == 3 || i == 12)
        {
            ptr1++;
            *ptr0++ = var1;
            var1 = 0;
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
    s32 i;
    s_800BCDA8* element;

    for (i = 0; i < 2; i++)
    {
        element = &D_800BCDA8[i];

        D_800BCDA8[i].field_2 = NO_VALUE;
        D_800BCDA8[i].field_1 = NO_VALUE;
        D_800BCDA8[i].field_3 = 0;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037188);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", Chara_PositionUpdateFromParams);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037334);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037388);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800373CC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800378D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037A4C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037C5C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037DC4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037E40);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037E78);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037F24);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800382B0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800382EC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80038354);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80038A6C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80038B44);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80038BD4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80038F6C);

void func_800391E8() // 0x800391E8
{
    D_800A9A68 += g_DeltaTime1;
    if (((D_800A9A68 >> 11) & 1) == 0)
    {
        Gfx_StringPosition(SCREEN_POSITION_X(39.25f), SCREEN_POSITION_Y(43.5f));
        Gfx_StringDraw(D_80025394, 99); // "\x07PAUSED"
    }

    func_80091380();
    func_8004C8DC();

    if (g_SysWork.sysStateStep_C == 0)
    {
        SD_EngineCmd(3);
        g_SysWork.sysStateStep_C++;
    }

    // Debug button combo to bring up save screen from pause screen.
    // DPad-Left + L2 + L1 + LS-Left + RS-Left + L3
    if ((g_ControllerPtr0->btns_held_C == (Pad_L3 | Pad_DpadLeft | Pad_L2 | Pad_L1 | Pad_LStickLeft2 | Pad_RStickLeft | Pad_LStickLeft)) &&
        (g_ControllerPtr0->btns_new_10 & Pad_L3))
    {
        D_800A9A68 = 0;
        SD_EngineCmd(4);
        g_MapEventIdx = 0;
        SysWork_StateSetNext(SysState_SaveMenu1);
        return;
    }

    if (g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->controllerBinds_0.pause)
    {
        D_800A9A68 = 0;
        SD_EngineCmd(4);
        SysWork_StateSetNext(SysState_Gameplay);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80039344);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003943C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80039568);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800395C0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800396D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003991C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80039A58);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80039C40);

void AreaLoad_UpdatePlayerPosition() // 0x80039F30
{
    Chara_PositionUpdateFromParams(&D_800BCDB0);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80039F54);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80039F90);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80039FB8);

void SysWork_SaveGameUpdatePlayer() // 0x8003A120
{
    s_ShSaveGame* save = g_SaveGamePtr;

    save->mapEventIdx_A8      = g_MapEventIdx;
    save->playerPositionX_244 = g_SysWork.player_4C.chara_0.position_18.vx;
    save->playerPositionZ_24C = g_SysWork.player_4C.chara_0.position_18.vz;
    save->playerRotationY_248 = g_SysWork.player_4C.chara_0.rotation_24.vy;
    save->playerHealth_240    = g_SysWork.player_4C.chara_0.health_B0;
}

void func_8003A16C() // 0x8003A16C
{
    if (!(g_SysWork.flags_22A4 & 2))
    {
        // Update saveGame_30C with player info.
        SysWork_SaveGameUpdatePlayer();

        // TODO: What is saveGame_90 used for?
        g_GameWork.saveGame_90 = g_GameWork.saveGame_30C;
    }
}

void SysWork_SaveGameReadPlayer() // 0x8003A1F4
{
    g_SysWork.player_4C.chara_0.position_18.vx = g_SaveGamePtr->playerPositionX_244;
    g_SysWork.player_4C.chara_0.position_18.vz = g_SaveGamePtr->playerPositionZ_24C;
    g_SysWork.player_4C.chara_0.rotation_24.vy = g_SaveGamePtr->playerRotationY_248;
    g_SysWork.player_4C.chara_0.health_B0      = g_SaveGamePtr->playerHealth_240;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003A230);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003A3C8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003A460);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003A4B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003A52C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003AA4C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003AB28);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003B550);

void func_8003B560() {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003B568);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003B678);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003B758);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003B7BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003B7FC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003B838);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BA08);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BAC4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BBF4);

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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BD2C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BD48);

void func_8003BE28() // 0x8003BE28
{
    func_80069820(D_800BCE14);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BE50);

void GameFs_BgEtcGfxLoad() // 0x8003BE6C
{
    Fs_QueueStartReadTim(FILE_TIM_BG_ETC_TIM, FS_BUFFER_1, &D_800A9EB4);
}

void GameFs_BgItemLoad() // 0x8003BE9C
{
    D_800BE9FC.queueIdx_1000 = Fs_QueueStartRead(FILE_BG_BG_ITEM_PLM, &D_800BE9FC);
}

void func_8003BED0() // 0x8003BED0
{
    if (Fs_QueueIsEntryLoaded(D_800BE9FC.queueIdx_1000) == 0 || D_800BE9FC.field_2 != 0)
    {
        return;
    }

    func_800560FC(&D_800BE9FC);
    func_80056504(&D_800BE9FC, &D_80025528, &D_800A9EBC, 1);
    func_80056504(&D_800BE9FC, &D_80025530, &D_800A9EC4, 1);
    func_80056954(&D_800BE9FC);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BF60);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C048);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C0C0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C110);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C1AC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C220);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C2EC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C30C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C368);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C3A0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C3AC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003c850);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C878);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C8F8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C92C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003CB3C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003CB44);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003CBA4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003CC7C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003CD5C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003CD6C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003CDA0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D01C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D03C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D058);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D160);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D21C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D354);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D3BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D444);

void func_8003D460() {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D468);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D550);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D5B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D6A4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D6E0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D7D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D938);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D95C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D9C8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003DA9C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003DD74);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003DD80);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003DE60);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003DF84);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E08C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E194);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E238);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E388);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E414);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E4A0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E544);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E5E8);

void GameFs_FlameGfxLoad() // 0x8003E710
{
    Fs_QueueStartReadTim(FILE_TIM_FLAME_TIM, FS_BUFFER_1, &D_800A9FA8);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E740);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EB54);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EBA0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EBF4);

void func_8003ECBC() // 0x8003ECBC
{
    g_SysWork.unk_2388[21] = 1;
    g_SaveGamePtr->flags_AC &= ~2;
}

void func_8003ECE4() // 0x8003ECE4
{
    g_SysWork.unk_2388[21] = 0;
    g_SaveGamePtr->flags_AC |= 2;
}

void func_8003ED08() // 0x8003ED08
{
    u8 var;

    var = g_SysWork.unk_2388[21] ^ 1;
    g_SysWork.unk_2388[21] = var;

    if (var == 1)
    {
        g_SaveGamePtr->flags_AC &= ~2;
        return;
    }

    g_SaveGamePtr->flags_AC |= 2;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003ED64);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003ED74);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EDA8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EDB8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EE30);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EEDC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EF10);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EF74);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003F08C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003F170);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003F4DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003F654);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003F6F0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003F7E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003F838);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003FCB0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003FD38);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003FE04);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003FEC0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003FF2C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80040004);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80040014);
