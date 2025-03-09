#include "game.h"

#include <libcd.h>
#include <libetc.h>

#include "bodyprog/bodyprog.h"
#include "main/fsqueue.h"
#include "screens/b_konami/b_konami.h"
#include "screens/stream/stream.h"

void func_800C95AC(void)
{
    e_GameState prevState;
    s32 idx;

    if (g_GameWork.gameState_594 == GameState_KonamiLogo)
    {
        do
        {
            JOY_Update();

            switch (g_GameWork.gameStateStep_598[0])
            {
                case 0:
                    GFX_Init(0x280, 1);
                    
                    D_800BCD0C = 6;
                    D_800B5C30 = 0x333;

                   // Load \1ST\KONAMI2.TIM (Konami logo).
                    Fs_QueueStartReadTim(FILE_1ST_KONAMI2_TIM, FS_BUFFER_1, &D_800A9004);
                    
                    func_8003D160();
                    GameFS_BgItemLoad_8003BE9C();
                    func_8005E0DC(-1);

                    // Start loading \ANIM\HB_BASE.ANM.
                    Fs_QueueStartRead(FILE_ANIM_HB_BASE_ANM, FS_BUFFER_0);

                    g_GameWork.gameStateStep_598[0]++;
                    break;
                    
                case 1:
                    if (D_800BCD0C == g_GameWork.gameStateStep_598[0])
                    {
                        g_GameWork.gameStateStep_598[0] = 2;
                    }
                    break;
                    
                case 2:
                    if (g_pController1->btns_held_C != 0 || g_SysWork.field_1C >= 181)
                    {
                        D_800BCD0C = 3;
                        D_800B5C30 = 0x333;
                        g_GameWork.gameStateStep_598[0] = 3;
                    }
                    break;
                    
                case 3:
                    if ((D_800BCD0C & 7) == 5)
                    {
                        Fs_QueueWaitForEmpty();

                        prevState                = g_GameWork.gameState_594;
                        g_GameWork.gameState_594 = GameState_KCETLogo;

                        g_SysWork.field_1C = 0;
                        g_SysWork.field_20 = 0;

                        g_GameWork.gameStateStep_598[1] = 0;
                        g_GameWork.gameStateStep_598[2] = 0;

                        g_SysWork.sysState_8     = SysState_Gameplay;
                        g_SysWork.field_24 = 0;
                        g_SysWork.sysStateStep_C = 0;
                        g_SysWork.field_28 = 0;
                        g_SysWork.field_10 = 0;
                        g_SysWork.field_2C = 0;
                        g_SysWork.field_14 = 0;

                        g_GameWork.gameStateStep_598[0] = prevState;
                        g_GameWork.gameStatePrev_590    = prevState;
                        g_GameWork.gameStateStep_598[0] = 0;
                    }
                    break;
            }
            
            func_800C9FB8();
            func_8003260C();
            Fs_QueueUpdate();
            func_8002EB88();
            func_80033548();
            nullsub_800334C8();
            VSync(0);
            GsSwapDispBuff();
            GsDrawOt(&D_800A8FC4[g_CurOTNum]);

            // TODO: Deal with 0x801A2600.
            idx = GsGetActiveBuff();
            g_CurOTNum = idx;
            D_800C7018 = (idx << 0xF) + 0x801A2600;
            
            GsClearOt(0, 0, &D_800A8F74[idx]);
            GsClearOt(0, 0, &D_800A8FC4[g_CurOTNum]);
        } while (g_GameWork.gameState_594 == GameState_KonamiLogo);
    }
}

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800C9874);

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800C99A4);

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800C9E6C);

void func_800C9FB8(void)
{
    s32* temp_a1;

    func_800C9E6C(&D_800A8FFC, 0xF, 0, 0, 256, 256, -192, -192);
    func_800C9E6C(&D_800A8FFC, 0xF, 256, 0, 128, 256, 64, -192);
    func_800C9E6C(&D_800A8FFC, 0xF, 0, 256, 256, 128, -192, 64);
    func_800C9E6C(&D_800A8FFC, 0xF, 256, 256, 128, 128, 64, 64);

    temp_a1 = (g_CurOTNum << 4) + &D_800B5C7C;

    // TODO: Wait on fgsfds's investigations for cleaner match of graphics setup.
    // addPrim(temp_a1, D_800C7018);
    ((TILE*)D_800C7018)->tag = (u32)((*temp_a1 & 0xFFFFFF) | 0x03000000);
    setaddr(temp_a1, D_800C7018);
    
    setCodeWord((TILE*)D_800C7018, PRIM_RECT, 0xFFFFFF);
    setXY0Fast((TILE*)D_800C7018, -320, -240);
    setWH((TILE*)D_800C7018, 640, 480);

    D_800C7018 += sizeof(TILE);
}

void func_800CA120(void)
{
    u32* temp_a1;

    func_800C9E6C(&D_800A9004, 0xF, 0, 0, 256, 160, -208, -80);
    func_800C9E6C(&D_800A9004, 0xF, 256, 0, 160, 160, 48, -80);
    
    temp_a1 = (g_CurOTNum << 4) + &D_800B5C7C;

    // TODO: Wait on fgsfds's investigations for cleaner match of graphics setup.
    // addPrim(temp_a1, D_800C7018);
    ((TILE*)D_800C7018)->tag = (u32)((*temp_a1 & 0xFFFFFF) | 0x03000000);
    setaddr(temp_a1, D_800C7018);
    
    setCodeWord((TILE*)D_800C7018, PRIM_RECT, 0xFFFFFF);
    setXY0Fast((TILE*)D_800C7018, -320, -240);
    setWH((TILE*)D_800C7018, 640, 480);

    D_800C7018 += sizeof(TILE);
}

void func_800CA234(void)
{
    D_800CA4FC = 0;
}

s32 func_800CA240(s32* arg0)
{
    return *arg0;
}

void func_800CA24C(s32 arg0, s32 arg1, s32 arg2)
{
    s32 var_a3;
    s32* somePtr;

    var_a3 = 0;
    D_800CA4FC = 1;
    D_800CA500 = arg0;
    D_800CA504 = arg1;
    D_800CA50C = arg0 + arg2;
    D_800CA500 = arg0 + 4;
    do
    {
        somePtr = D_800CA4F4 + var_a3;
        var_a3 += 4;
        *somePtr = 0;
    }
    while (var_a3 < 4096);
    
    D_800CA508 = 4078;
    D_800CA510 = 0;
}

s32 func_800CA2B8(void)
{
    return D_800CA4FC;
}

INCLUDE_ASM("asm/screens/b_konami/nonmatchings/b_konami", func_800CA2C8);
