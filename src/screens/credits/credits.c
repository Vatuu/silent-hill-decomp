#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "screens/credits/credits.h"

void func_801E2E28(s32 idx) // 0x801E2E28
{
    s32 var0;
    s32 var1;

    D_801E5E8C = idx;

    func_8004729C(D_801E5558[idx].field_0);
    var1 = (D_801E5558[idx].field_4 * 2) - 0x1F8;
    var0 = var1 / D_801E5C20;

    D_801E5E7C = var1;
    D_801E5E88 = 1;
    D_801E5E7C = var0;
    D_801E5E84 = (var0 * D_801E5C20) + 0x1E0;
    D_801E5E80 = 0x10000 / var0;
}

s32 func_801E2ED8() // 0x801E2ED8
{
    switch (D_801E5E88)
    {
        case 0:
            break;

        case 1:
            Sd_EngineCmd((u16)D_801E5558[D_801E5E8C].field_0);
            D_801E5E88++;
            break;

        case 2:
            switch (func_80045B28())
            {
                case 0:
                    return 0;

                case 1:
                    D_800C48F0 = D_801E5558[D_801E5E8C].field_2;
                    return 1;

                default:
                    break;
            }

        default:
            break;
    }

    return 0;
}

s32 func_801E2FC0() // 0x801E2FC0
{
    switch (D_800BCD0C)
    {
        case 4:
        case 5:
        case 12:
        case 13:
            if (Fs_QueueGetLength() != 0)
            {
                break;
            }

            Game_StateSetNext(GameState_Unk15);
            return 1;

        case 2:
        case 3:
        case 10:
        case 11:
            break;

        default:
            D_800BCD0C = 10;
            D_800B5C30 = 1 << 12;
            break;
    }

    return 0;
}

void GameState_Unk15_Update() // 0x801E3094
{
    const s32* (*routines[3])() = { func_801E3124, func_801E342C, func_801E3304 };
    
    D_800C48F0 += g_VBlanks;
    if (routines[g_GameWork.gameStateStep_598[0]]() != 0) 
    {
        g_SysWork.timer_20 = 0;
        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
        g_GameWork.gameStateStep_598[0]++;
    }
}

s32 func_801E3124() // 0x801E3124
{
    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            switch (D_800BCD0C)
            {
                case 13:
                    g_GameWork.field_58C = 0xFF;
                    g_GameWork.field_58D = 0xFF;
                    g_GameWork.field_58E = 0xFF;
                    break;

                case 5:
                    g_GameWork.field_58C = 0;
                    g_GameWork.field_58D = 0;
                    g_GameWork.field_58E = 0;
                    break;
            }

            Sd_EngineCmd(18);
            Sd_EngineCmd(16);
            g_GameWork.gameStateStep_598[1]++;
            break;

        case 1:
            StoreImage(&D_801E557C[0], (u_long*)IMAGE_BUFFER_0);
            StoreImage(&D_801E557C[1], (u_long*)IMAGE_BUFFER_1);
            DrawSync(0);

            // Maybe an enum entry check.
            switch (D_800BCD0C)
            {
                case 13:
                    Gfx_ClearRectInterlaced(0, 32, 512, 448, FP_COLOR(1.0f), FP_COLOR(1.0f), FP_COLOR(1.0f));
                    break;

                case 5:
                    Gfx_ClearRectInterlaced(0, 32, 512, 448, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));
                    break;
            }

            g_GameWork.gameStateStep_598[1]++;
            break;

        case 2:
            Gfx_Init(0x200, 1);
            g_IntervalVBlanks = 1;
            D_801E5E74 = 0x3C;
            g_GameWork.gameStateStep_598[1]++;
            break;

        case 3:
            D_801E5E74--;
            
            if (D_801E5E74 <= 0 && func_80045B28() < 2)
            {
                g_GameWork.field_58C = 0;
                g_GameWork.field_58D = 0;
                g_GameWork.field_58E = 0;
                return 1;
            }

            break;
    }

    return 0;
}

s32 func_801E3304() // 0x801E3304
{
    if (g_GameWork.gameStatePrev_590 == GameState_InGame)
    {
        if (g_GameWork.gameStateStep_598[1] == 0)
        {
            Gfx_Init(SCREEN_WIDTH, 0);
            D_800BCD0C = 0;
            g_GameWork.gameStateStep_598[1]++;
        }
        else if (g_GameWork.gameStateStep_598[1] != 10)
        {
            g_GameWork.gameStateStep_598[1]++;
        }
        else
        {
            Gfx_ClearRectInterlaced(0, 32, 320, 448, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));
            LoadImage(&D_801E557C[0], IMAGE_BUFFER_0);
            LoadImage(&D_801E557C[1], IMAGE_BUFFER_1);
            DrawSync(0);
            VSync(2);

            Game_StateSetPrevious();
        }

        return 0;
    }

    return 0;
}

s32 func_801E342C() // 0x801E342C
{
    s32 temp;
    u32* addr;
    TILE* tile;

    if (((g_GameWork.optExtraOptionsEnabled_27 >> (D_801E5E8C - 1)) & (1 << 0)) &&
        (g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->controllerBinds_0.skip))
    {
        D_800C48F0 = D_801E5558[D_801E5E8C].field_4 + (D_801E5E84 / 2);
        Sd_EngineCmd(19);
    }

    addr = (g_ObjectTableIdx << 11) + &D_800B7CC4;
    tile = (TILE*)GsOUT_PACKET_P;

    addPrimFast(addr, tile, 3);
    setCodeWord(tile, PRIM_RECT, 0);
    setXY0Fast(tile, -256, -224);
    setWHFast(tile, 512, 2);

    GsOUT_PACKET_P += sizeof(TILE);
    temp = func_801E3684();

    switch(g_GameWork.gameStateStep_598[1])
    {
        case 0:
            switch (D_800BCD0C)
            {
                case 13:
                    D_800BCD0C = 14;
                    break;

                case 5:
                    D_800BCD0C = 6;
                    break;
            }

            D_800B5C30 = 1 << 12;
            g_GameWork.gameStateStep_598[1]++;
            D_801E5E78 = 180;
            break;

        case 1:
            if (temp == 0)
            {
                break;
            }

            D_801E5E78--;
            if (!(func_80045B28() & 0xFF))
            {
                g_GameWork.gameStateStep_598[1]++;
            }
            break;

         case 2:
            D_801E5E78--;
            if (D_801E5E78 <= 0)
            {
                D_800BCD0C = g_GameWork.gameStateStep_598[1];
                g_GameWork.gameStateStep_598[1] = 3;
            }
            break;

        case 3:
            if (D_800BCD0C == 5)
            {
                g_GameWork.gameStateStep_598[1] = 4;
                return 1;
            }
            break;
    }

    return 0;
}

bool func_801E3684() // 0x801E3684
{
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s8* temp_s0;
    s32* var_s2;
    s32 temp_fp;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s1;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_v1;
    bool ret;

    temp_v1 = D_800C48F0 * 2;
    var_s0 = (s32)((temp_v1 - 0x1F8) * D_801E5E80);
    var_s0 = var_s0 >> 16;
    var_s6 = D_801E5E84;
    sp10 = D_801E5E7C;
    
    if (var_s0 < 0)
    {
        var_s0 = 0;
    }
    
    var_v1 = (s32)(temp_v1 * D_801E5E80);
    var_v1 = var_v1 >> 16;
    if (var_v1 >= D_801E5C20)
    {
        var_v1 = D_801E5C20 - 1;
    }
    
    sp14 = ((var_s0 * sp10) - temp_v1) + SCREEN_HEIGHT;
    sp18 = (var_v1 - var_s0) + 1;

    var_s6 = (var_s6 - temp_v1);
    var_s6 = var_s6 + SCREEN_HEIGHT;
    temp_fp = var_s6 < SCREEN_HEIGHT;
    
    if (temp_fp != 0)
    {
        ret = var_s6 < -23;
        var_s4 = -1;
        
        if (ret)
        {
            var_s6 = -24;
        }
    }
    else
    {
        ret = false;
        var_s4 = -1;
    }
    
    func_801E434C(1, 1);
    func_801E4310(48, 48, 48);
    
    for (var_s5 = 2; var_s5 >= 0; var_s5--, var_s4 += 2)
    {
        if (var_s5 == 0)
        {
            var_s4 = 0;
            func_801E434C(0, 0);
            func_801E4310(64, 64, 64);
        }
        
        var_s3 = sp14 + var_s4;
        var_s2 = &D_801E5590[var_s0];

        for (var_s1 = sp18; var_s1 > 0; var_s1--, var_s2++, var_s3 += sp10)
        {
            temp_s0 = *var_s2;
            func_801E42F8(0, var_s3);
            func_801E4394(temp_s0);
        }
        
        if (temp_fp != 0)
        {
            func_801E42F8(0, var_s6 + var_s4);
            func_801E4394(&D_801E5BD0);
        }
    } 
    
    return ret;
}

void func_801E386C() // 0x801E386C
{
    s_UnkCredits1* ptr;
    s32 var0;
    s64 var1;
    s32 var2 = 5;
    
    func_8009185C(0, 0, SCREEN_HEIGHT, 0x1000, 0, 0x22000, 0xF0000, 0xB33, 899, -0xF9C);
    ptr = D_801E5558;
    ptr = &ptr[5];
    var0 = (u16)ptr->field_4;

    var1 = (s16)var0;
    var1 = FP_TO(var1, Q12_SHIFT);
    var1 = FP_FROM(var1, Q12_SHIFT);

    D_801E5E8C = var2;
    D_801E5E7C = var1 - 264;
    D_800C48F0 = (s32)ptr->field_2;
    D_801E5E7C = D_801E5E7C / D_801E5C20;
    D_801E5E84 = (D_801E5E7C * D_801E5C20) + SCREEN_HEIGHT;
    D_801E5E80 = 0x10000 / D_801E5E7C;
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3970);

void func_801E3DD0() // 0x801E3DD0 
{
    D_801E600C = Rng_Rand16();
}

s32 func_801E3DF8(s32 arg0) // 0x801E3DF8
{
    return ((u32)((arg0 & 0xFF) * 0x31) >> 6) | 0x38;
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3E18);

void func_801E42F8(s32 arg0, s32 arg1) // 0x801E42F8
{
    D_800AFE08.field_0 = arg0;
    D_800AFE08.field_2 = arg1;
    D_800AFE08.field_4 = arg0;
}

void func_801E4310(s32 r, s32 g, s32 b) // 0x801E4310
{
    D_800AFE08.field_8 = (r & 0xFF) | ((g & 0xFF) << 8) | ((b & 0xFF) << 16) | ((PRIM_RECT | RECT_TEXTURE) << 24);
}

void func_801E4340(s8 arg0) // 0x801E4340
{
    D_800AFE08.field_6 = arg0;
}

void func_801E434C(u32 arg0, u32 arg1) // 0x801E434C
{
    u32 shiftedArg1;
    u32 shiftedField_18;
    u32 maskedField_18;

    D_800AFE08.field_7 = (arg0 != 0);

    if (arg1 < 4)
    {
        maskedField_18 = D_800AFE08.field_18;
        shiftedField_18 = (maskedField_18 << 4) & 0x100;
        
        maskedField_18 &= 0xF;
        shiftedField_18 >>= 4;

        shiftedArg1 = arg1 & 3;
        shiftedArg1 <<= 5;
        shiftedArg1 |= shiftedField_18;
        shiftedArg1 |= (u8)maskedField_18;

        D_800AFE08.field_14 = shiftedArg1;
    }
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E4394);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E47E0);

void func_801E4B98(s32 r, s32 g, s32 b)
{
    D_800AFE24.field_8 = (r & 0xFF) | ((g & 0xFF) << 8) | ((b & 0xFF) << 16) | (GPU_COM_TF4 << 24);
}

void func_801E4BC8(s8 arg0) // 0x801E4BC8
{
    D_800AFE24.field_6 = arg0;
}

void func_801E4BD4(u32 arg0, u32 arg1) // 0x801E4BD4
{
    u32 shiftedArg1;
    u32 shiftedField_18;
    u32 maskedField_18;

    D_800AFE24.field_7 = (arg0 != 0);

    if (arg1 < 4)
    {
        maskedField_18 = D_800AFE24.field_18;
        shiftedField_18 = (maskedField_18 << 4) & 0x100;

        maskedField_18 &= 0xF;
        shiftedField_18 >>= 4;

        shiftedArg1 = arg1 & 3;
        shiftedArg1 <<= 5;
        shiftedArg1 |= shiftedField_18;
        shiftedArg1 |= (u8)maskedField_18;

        D_800AFE24.field_14 = shiftedArg1;
    }
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E4C1C);
