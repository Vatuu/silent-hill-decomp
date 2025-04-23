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
    s32* (*routines[3])() = {func_801E3124, func_801E342C, func_801E3304};

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
            func_801E4394(D_801E5BD0);
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

bool func_801E3970(void) // 0x801E3970
{
    bool   showKCET    = false;
    bool   animateKCET = false;
    bool   finished    = false;
    char*  lineStrPtr;
    char** currentLinePtr;
    s32    temp_a1;
    s32    temp_a2;
    s32    currentLineYPos;
    s32    lineHeight;
    s32    temp_v0;
    s32    temp_v0_4;
    s32    vblank;
    s32    var_a0;
    s32    var_fp;
    s32    lineIndex;
    s32    i;
    s32    lineY;
    s32    var_s5;
    s32    sin;
    s32    cos;
    s32    linesToDraw;
    s32    var_t3;

    vblank = FP_MULTIPLY((s64)D_800C48F0, 0x1000, Q12_SHIFT);

    temp_a2    = D_801E5E84;
    lineHeight = D_801E5E7C;

    lineIndex = (vblank - 0x198) * D_801E5E80;
    lineIndex = lineIndex >> 16;
    if (lineIndex < 0)
    {
        lineIndex = 0;
    }

    var_a0 = vblank * D_801E5E80;
    var_a0 = var_a0 >> 16;
    if (var_a0 >= D_801E5C20)
    {
        var_a0 = D_801E5C20 - 1;
    }

    temp_a2 = (temp_a2 - vblank);
    var_fp  = temp_a2 + 0x78;

    temp_a2 = var_fp;
    var_s5  = 0;

    showKCET = var_fp < 0x78;

    var_t3          = lineIndex * lineHeight;
    temp_v0         = var_t3 - vblank;
    currentLineYPos = temp_v0 + 0x78;

    temp_v0     = (var_a0 - lineIndex);
    linesToDraw = temp_v0 + 1;

    if (showKCET)
    {
        animateKCET = var_fp < -0x2F;
        if (animateKCET)
        {
            var_fp = -0x30;
            var_s5 = -0x30 - temp_a2;
        }
    }
    else
    {
        animateKCET = false;
    }

    func_801E4310(160, 160, 160);
    func_801E434C(0, 0);

    lineY          = currentLineYPos;
    currentLinePtr = &D_801E5590[lineIndex];

    for (i = linesToDraw; i > 0; i--, lineY += lineHeight, currentLinePtr++)
    {
        lineStrPtr = *currentLinePtr;
        func_801E47E0(0, lineY);
        func_801E4C1C(lineStrPtr);
    }

    if (animateKCET)
    {
        temp_a1 = var_s5;
        if (var_s5 < 0x78) // rotate
        {
            temp_a1 = (var_s5 * 0x1000) / 0x78;
            temp_a1 = FP_MULTIPLY((s64)(0x1000 - temp_a1), 0x36F, Q12_SHIFT);
            sin     = -shRsin(temp_a1);
            cos     = shRcos(temp_a1);
            func_8009185C(0, 0, 0xF0, 0x1000, 0, 0x22000, 0xF0000, 0xB33, cos, sin);
        }
        else if (var_s5 < 0xB4) // zoom in
        {
            temp_a1   = var_s5 - 0x78;
            temp_a1   = (temp_a1 * 0x1000) / 0x3C;
            temp_v0_4 = FP_MULTIPLY((s64)(0x1000 - temp_a1), 0x1E000, Q12_SHIFT) + 0xD2000;
            func_8009185C(0, 0, 0xF0, 0x1000, 0, 0x22000, temp_v0_4, 0xB33, 0x1000, 0);
        }
        else if (var_s5 >= 0x168)
        {
            if (var_s5 < 0x1E0) // zoom out
            {
                temp_a1   = var_s5 - 0x168;
                temp_a1   = (temp_a1 * 0x1000) / 0x78;
                temp_v0_4 = FP_MULTIPLY((s64)(0x1000 - temp_a1), -0xE2E000, Q12_SHIFT) + 0xF00000;
                func_8009185C(0, 0, 0xF0, 0x1000, 0, 0x22000, temp_v0_4, 0xB33, 0x1000, 0);
            }
            else // hide and finish
            {
                finished = true;
                showKCET = false;
            }
        }
    }
    else if (((g_GameWork.optExtraOptionsEnabled_27 >> (D_801E5E8C - 1)) & 1) && (g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->controllerBinds_0.skip))
    {
        s32 skipTo    = D_801E5E84 + 0xA8;
        s32 skipToInt = FP_TO(skipTo, Q12_SHIFT);

        if (skipToInt < 0)
        {
            skipToInt += 0xFFF;
        }
        skipTo     = FP_FROM(skipToInt, Q12_SHIFT);
        D_800C48F0 = skipTo;
        Sd_EngineCmd(19);
    }

    if (showKCET)
    {
        func_801E47E0(0, var_fp);
        func_801E4C1C(D_801E5BD0);
    }

    return finished;
}

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

void func_801E4394(u8* string) // 0x801E4394
{
    u8*     strPtr     = string;
    s32     textX      = D_800AFE08.field_0;
    s32     textY      = D_800AFE08.field_2;
    s32     marginX    = D_800AFE08.field_4;
    s32     fontH      = D_800AFE08.field_6;
    s16*    widthTable = D_800AFE08.field_C;
    s32*    colorTable = D_800AFE08.field_10;
    PACKET* packet     = GsOUT_PACKET_P;
    u32     blendFlag  = (u8)D_800AFE08.field_7;
    u32     charCode   = *strPtr;
    u32     colorCode  = D_800AFE08.field_8 | (blendFlag << 25); // rgb + code + semi-transp flag
    u32     clut       = (u16)D_800AFE08.field_16;               // clut x, clut y
    s32*    addr       = (s32*)((g_ObjectTableIdx << 4) + &D_800B5C58);

    s32       charWidth;
    s32       widthSum;
    s32       idx;
    u32       temp;
    u32       nextChar;
    u8*       scanPtr;
    SPRT*     sprite;
    SPRT_16*  sprite16;
    DR_TPAGE* tpage;

    while (charCode != 0)
    {
        charWidth = widthTable[charCode];
        if ((charCode - 0x21) < 0x64) // normal font
        {
            sprite = (SPRT*)packet;
            addPrimFast(addr, sprite, 4);
            *(u32*)(&sprite->r0) = colorCode;
            setXY0Fast(sprite, textX, textY);
            idx                  = charCode - 0x21;
            temp                 = idx / 10;
            idx                  = idx % 10;
            idx                  = idx * 24;
            *(u32*)(&sprite->u0) = idx + (temp * 24 * 256);
            *(u32*)(&sprite->u0) += clut << 16;
            setWHFast(sprite, 24, 24);
            packet += sizeof(SPRT);
        }
        else
        {
            sprite16 = (SPRT_16*)packet;
            if ((charCode - 0xA0) < 0x10) // kcet font
            {
                addPrimFast(addr, sprite16, 3);
                *(u32*)(&sprite16->r0) = colorCode ^ (0x18 << 24); // GP0(7Ch) - Textured Rectangle, 16x16, opaque, texture-blending
                setXY0Fast(sprite16, textX, textY + 4);
                idx                    = charCode - 0xA0;
                *(u32*)(&sprite16->u0) = (idx * 256 * 16) + 16 * (16 - 1);
                *(u32*)(&sprite16->u0) += clut << 16;
                packet += sizeof(SPRT_16);
            }
            else if ((charCode - 0xB8) < 7) // kcet font, .YVUTSR
            {
                addPrimFast(addr, sprite16, 3);
                *(u32*)(&sprite16->r0) = colorCode ^ (0x18 << 24); // GP0(7Ch) - Textured Rectangle, 16x16, opaque, texture-blending
                setXY0Fast(sprite16, textX, textY + 4);
                idx                    = charCode - 0xB8;
                *(u32*)(&sprite16->u0) = (idx * 16) + (256 * 16 * (16 - 1) + 16 * 8);
                *(u32*)(&sprite16->u0) += clut << 16;
                packet += sizeof(SPRT_16);
            }
            else if ((charCode - 1) < 7) // changes font color
            {
                colorCode = colorTable[charCode - 1] | ((u8)D_800AFE08.field_7 << 25);
            }
            else if ((charCode - 0xD0) < 8) // changes font width table?
            {
                scanPtr  = strPtr + 1;
                widthSum = 0;
                while (1)
                {
                    s32 var  = 8;
                    nextChar = *scanPtr++;
                    if (nextChar == (charCode + 8) || ((nextChar == charCode) || (nextChar == 10)) || (nextChar == 0xd) || (nextChar == 0xc))
                    {
                        break;
                    }
                    if (((nextChar - 0xF0) >= var) && ((nextChar - 0xF8) > 7) && ((nextChar - 0xE0) > 7) && ((nextChar - 0xE8) > 7))
                    {
                        widthSum += widthTable[nextChar];
                    }
                }
                (&widthTable[charCode])[16] = widthSum / 2;
                (&widthTable[charCode])[32] = -(&widthTable[charCode])[16];
                (&widthTable[charCode])[24] = widthSum;
                (&widthTable[charCode])[40] = -(&widthTable[charCode])[24];
            }
        }
        switch ((s32)charCode) // offsets
        {
            case 10: // new line
                textX = marginX;
                textY += fontH;
                break;

            case 13: // carriage return
                textX = marginX;
                break;

            case 11: // vertical tab
                textY += fontH;
                break;

            case 12: // form feed
                textX = D_800AFE08.field_0;
                textY = D_800AFE08.field_2;
                break;

            default:
                textX += charWidth;
                break;
        }

        strPtr++;
        charCode = *strPtr;
    }

    tpage = (DR_TPAGE*)packet;
    setDrawTPage(tpage, 0, 1, D_800AFE08.field_14);
    addPrim(addr, tpage);
    D_800AFE08.field_0 = textX;
    D_800AFE08.field_2 = textY;
    GsOUT_PACKET_P     = packet + sizeof(DR_TPAGE);
}

void func_801E47E0(s32 arg0, s32 arg1) // 0x801E47E0
{
    s32  temp_a2;
    s32  temp_lo;
    s32  temp_lo_11;
    s32  temp_lo_12;
    s32  temp_lo_15;
    s32  temp_lo_3;
    s32  temp_lo_4;
    s32  temp_lo_6;
    s32  temp_lo_7;
    s32  temp_t0;
    s32  temp_t1;
    s32  temp_t2;
    s32  temp_v0;
    s32  temp_v0_2;
    s32  temp_v0_3;
    s32  temp_v0_4;
    bool check = D_800AFE24.field_0 != arg0;

    if (D_800AFE24.field_2 != arg1)
    {
        temp_lo   = arg1 * D_800AFE24.field_3C;
        temp_t1   = D_800AFE24.field_24 << 0x16;
        temp_lo_3 = (D_800AFE24.field_30 + (s32)FP_MULTIPLY((s64)D_800AFE24.field_1C, temp_lo, Q12_SHIFT)) >> 2;
        temp_lo_3 = temp_t1 / temp_lo_3;

        temp_t2   = arg1 + 0x18;
        temp_lo_4 = temp_t2 * D_800AFE24.field_3C;
        temp_lo_6 = (D_800AFE24.field_30 + (s32)FP_MULTIPLY((s64)D_800AFE24.field_1C, temp_lo_4, Q12_SHIFT)) >> 2;
        temp_lo_6 = temp_t1 / temp_lo_6;

        temp_lo_7 = arg0 * D_800AFE24.field_34;
        temp_v0   = D_800AFE24.field_28 + FP_MULTIPLY((s64)D_800AFE24.field_1C, temp_lo_7, Q12_SHIFT);
        temp_t0   = FP_MULTIPLY((s64)temp_lo_3, temp_v0, Q12_SHIFT);
        temp_v0_2 = D_800AFE24.field_28 + FP_MULTIPLY((s64)D_800AFE24.field_1C, D_800AFE24.field_34, Q12_SHIFT);

        D_800AFE24.field_0  = arg0;
        D_800AFE24.field_2  = arg1;
        D_800AFE24.field_4  = arg0;
        D_800AFE24.field_40 = temp_t0;
        D_800AFE24.field_44 = FP_MULTIPLY((s64)temp_lo_6, temp_v0, Q12_SHIFT);
        D_800AFE24.field_48 = FP_MULTIPLY((s64)temp_lo_3, temp_v0_2, Q12_SHIFT) - FP_MULTIPLY((s64)temp_lo_3, D_800AFE24.field_28, Q12_SHIFT);
        D_800AFE24.field_4C = FP_MULTIPLY((s64)temp_lo_6, temp_v0_2, Q12_SHIFT) - FP_MULTIPLY((s64)temp_lo_6, D_800AFE24.field_28, Q12_SHIFT);
        temp_lo_11          = arg1 * D_800AFE24.field_38;
        temp_v0_3           = D_800AFE24.field_2C + FP_MULTIPLY((s64)D_800AFE24.field_1C, temp_lo_11, Q12_SHIFT);
        D_800AFE24.field_50 = FP_MULTIPLY((s64)temp_lo_3, temp_v0_3, Q12_SHIFT);

        temp_lo_12          = temp_t2 * D_800AFE24.field_38;
        temp_t0             = D_800AFE24.field_2C + FP_MULTIPLY((s64)D_800AFE24.field_1C, temp_lo_12, Q12_SHIFT);
        D_800AFE24.field_54 = FP_MULTIPLY((s64)temp_lo_6, temp_t0, Q12_SHIFT);
    }
    else if (check)
    {
        temp_v0_4          = arg0 - D_800AFE24.field_0;
        temp_a2            = temp_v0_4 * D_800AFE24.field_48;
        temp_lo_15         = temp_v0_4 * D_800AFE24.field_4C;
        D_800AFE24.field_0 = arg0;
        D_800AFE24.field_40 += temp_a2;
        D_800AFE24.field_44 += temp_lo_15;
    }
}

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

void func_801E4C1C(u8* strPtr) // 0x801E4C1C
{
    PACKET* packet;
    s32*    addr;

    s32 textX   = D_800AFE24.field_0;
    s32 textY   = D_800AFE24.field_2;
    s32 marginX = D_800AFE24.field_4;
    s32 fontH   = D_800AFE24.field_6;
    u32 colorCode;

    s32 var_a3 = D_800AFE24.field_40;
    s32 var_t3 = D_800AFE24.field_44;
    s32 var_t7 = D_800AFE24.field_48;
    s32 var_t6 = D_800AFE24.field_4C;
    s32 var_t4 = D_800AFE24.field_50;
    s32 var_t5 = D_800AFE24.field_54;

    u32       clut       = (u16)D_800AFE24.field_16;
    u32       tPage      = D_800AFE24.field_14;
    s16*      widthTable = D_800AFE24.field_C;
    s32*      colorTable = D_800AFE24.field_10;
    u32       blendFlag  = (u8)D_800AFE24.field_7 << 25;
    s32       charWidth;
    bool      textXChanged;
    bool      textYChanged;
    u32       nextChar;
    u8*       scanPtr;
    POLY_FT4* poly;
    s32       widthSum;
    u32       charCode;

    s32 temp_a0_4;
    s32 temp_a1_2;
    s32 temp_lo_3;
    s32 temp_lo_6;
    s32 temp_v0_5;
    s32 temp_v0_7;

    s32 var_a1;
    s32 var_a2;
    s32 var_t0;
    s32 var_t0_2;

    u32 temp_v1;
    u32 temp;
    s32 idx;

    packet = GsOUT_PACKET_P;
    addr   = (s32*)((g_ObjectTableIdx << 4) + &D_800B5C58);

    charCode  = *strPtr;
    colorCode = D_800AFE24.field_8 | blendFlag; // rgb + code + semi-transp flag

    while (charCode != 0)
    {
        poly = (POLY_FT4*)packet;

        var_t0 = (charCode - 0xA0) < 0x10U | (charCode - 0xB8 < 7U) << 1;
        if (var_t0 != 0) // map kcet font to normal
        {
            if (var_t0 == 1)
            {
                charCode = D_801E5E5C[charCode - 0xA0];
            }
            else
            {
                charCode = D_801E5E6C[charCode - 0xB8];
            }
        }

        charWidth = widthTable[charCode];
        if (charCode - 0x21 < 0x64U) // normal font
        {
            s32 offset         = 24 * 256;
            idx                = charCode - 0x21;
            temp               = idx / 10;
            idx                = idx % 10;
            idx                = idx * 24;
            temp               = temp * 24;
            *(u32*)(&poly->u0) = idx + (temp * 256);
            *(u32*)(&poly->u0) += clut << 16;
            *(u32*)(&poly->u1) = (idx + charWidth) + (temp * 256);
            *(u32*)(&poly->u1) += tPage << 16;
            temp_v1            = temp * (u64)256; // from permuter, not sure why this works
            *(u32*)(&poly->u2) = idx + (temp_v1 + offset);
            *(u32*)(&poly->u3) = (idx + charWidth) + (temp_v1 + offset);

            if (var_t0 != 0)
            {
                charWidth = (charWidth * 2) / 3;
                var_a1    = var_t7 * charWidth;
                var_a2    = var_t6 * charWidth;
                var_a2    = ((var_a2 - var_a1) * 2) / 3 + var_a1;
                var_t0_2  = ((var_t5 - var_t4) * 2) / 3 + var_t4;
            }
            else
            {
                var_a1   = var_t7 * charWidth;
                var_t0_2 = var_t5;
                var_a2   = var_t6 * charWidth;
            }
            addPrimFast(addr, (POLY_FT4*)packet, 9);
            *(u32*)(&poly->r0) = colorCode; // GP0(2Ch) - Textured four-point polygon, opaque, texture-blending
            setXY0Fast(poly, FP_FROM(var_a3, Q12_SHIFT), FP_FROM(var_t4, Q12_SHIFT));
            setXY1Fast(poly, FP_FROM(var_a3 + var_a1, Q12_SHIFT), FP_FROM(var_t4, Q12_SHIFT));
            setXY2Fast(poly, FP_FROM(var_t3, Q12_SHIFT), FP_FROM(var_t0_2, Q12_SHIFT));
            setXY3Fast(poly, FP_FROM(var_t3 + var_a2, Q12_SHIFT), FP_FROM(var_t0_2, Q12_SHIFT));
            packet += sizeof(POLY_FT4);
        }
        else if ((charCode - 1) < 7U) // changes font color
        {
            colorCode = colorTable[charCode - 1] | ((u8)D_800AFE24.field_7 << 25);
        }
        else if ((charCode - 0xD0) < 8U) // changes font width table?
        {
            widthSum = 0;
            scanPtr  = strPtr + 1;
            while (1)
            {
                s32 var  = 8;
                nextChar = *scanPtr++;
                if ((nextChar == (charCode + 8)) || (nextChar == charCode) || (nextChar == 0xA) || (nextChar == 0xD) || (nextChar == 0xC))
                {
                    break;
                }
                if ((nextChar - 0xF0) >= var && (nextChar - 0xF8) >= 8U && (nextChar - 0xE0) >= 8U && (nextChar - 0xE8) >= 8U)
                {
                    var_t0 = (nextChar - 0xA0) < 0x10U | (nextChar - 0xB8 < 7U) << 1;
                    if (var_t0 != 0) // map kcet font to normal
                    {
                        if (var_t0 == 1)
                        {
                            nextChar = D_801E5E5C[nextChar - 0xA0];
                        }
                        else
                        {
                            nextChar = D_801E5E6C[nextChar - 0xB8];
                        }
                        widthSum += (widthTable[nextChar] * 2) / 3;
                    }
                    else
                    {
                        widthSum += widthTable[nextChar];
                    }
                }
            }
            (&widthTable[charCode])[16] = widthSum / 2;
            (&widthTable[charCode])[32] = -(&widthTable[charCode])[16];
            (&widthTable[charCode])[24] = widthSum;
            (&widthTable[charCode])[40] = -(&widthTable[charCode])[24];
        }

        textXChanged = false;
        textYChanged = false;
        switch ((s32)charCode) // offsets
        {
            case 10: // new line
                textX = marginX;
                textY += fontH;
                textYChanged = true;
                break;

            case 11: // vertical tab
                textY += fontH;
                textYChanged = true;
                break;

            case 13: // carriage return
                charWidth    = textX - marginX;
                textX        = marginX;
                textXChanged = true;
                break;

            case 12: // form feed
                textX        = D_800AFE24.field_0;
                textY        = D_800AFE24.field_2;
                textYChanged = true;
                break;

            default:
                textX += charWidth;
                textXChanged = true;
                break;
        }

        if (textYChanged)
        {
            temp_a1_2 = D_800AFE24.field_24 << 0x16;

            temp_lo_3 = (D_800AFE24.field_30 + (s32)FP_MULTIPLY((s64)D_800AFE24.field_1C, textY * D_800AFE24.field_3C, Q12_SHIFT)) >> 2;
            temp_lo_3 = temp_a1_2 / temp_lo_3;

            temp_lo_6 = (D_800AFE24.field_30 + (s32)FP_MULTIPLY((s64)D_800AFE24.field_1C, (textY + 0x18) * D_800AFE24.field_3C, Q12_SHIFT)) >> 2;
            temp_lo_6 = temp_a1_2 / temp_lo_6;

            temp_v0_5 = D_800AFE24.field_28 + FP_MULTIPLY((s64)D_800AFE24.field_1C, textX * D_800AFE24.field_34, Q12_SHIFT);

            var_a3 = FP_MULTIPLY((s64)temp_lo_3, temp_v0_5, Q12_SHIFT);
            var_t3 = FP_MULTIPLY((s64)temp_lo_6, temp_v0_5, Q12_SHIFT);

            temp_v0_5 = D_800AFE24.field_28 + FP_MULTIPLY((s64)D_800AFE24.field_1C, D_800AFE24.field_34, Q12_SHIFT);

            var_t7 = FP_MULTIPLY((s64)temp_lo_3, temp_v0_5, Q12_SHIFT) - FP_MULTIPLY((s64)temp_lo_3, D_800AFE24.field_28, Q12_SHIFT);
            var_t6 = FP_MULTIPLY((s64)temp_lo_6, temp_v0_5, Q12_SHIFT) - FP_MULTIPLY((s64)temp_lo_6, D_800AFE24.field_28, Q12_SHIFT);

            temp_v0_7 = D_800AFE24.field_2C + FP_MULTIPLY((s64)D_800AFE24.field_1C, textY * D_800AFE24.field_38, Q12_SHIFT);
            var_t4    = FP_MULTIPLY((s64)temp_lo_3, temp_v0_7, Q12_SHIFT);

            temp_a0_4 = D_800AFE24.field_2C + FP_MULTIPLY((s64)D_800AFE24.field_1C, (textY + 0x18) * D_800AFE24.field_38, Q12_SHIFT);
            var_t5    = FP_MULTIPLY((s64)temp_lo_6, temp_a0_4, Q12_SHIFT);
        }
        else if (textXChanged)
        {
            var_a3 += charWidth * var_t7;
            var_t3 += charWidth * var_t6;
        }

        strPtr++;
        charCode = *strPtr;
    }

    GsOUT_PACKET_P      = packet;
    D_800AFE24.field_0  = textX;
    D_800AFE24.field_2  = textY;
    D_800AFE24.field_40 = var_a3;
    D_800AFE24.field_44 = var_t3;
    D_800AFE24.field_48 = var_t7;
    D_800AFE24.field_4C = var_t6;
    D_800AFE24.field_50 = var_t4;
    D_800AFE24.field_54 = var_t5;
}
