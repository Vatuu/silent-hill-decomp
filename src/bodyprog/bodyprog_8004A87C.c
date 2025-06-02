#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"

void Gfx_StringSetPosition(s32 x, s32 y) // 0x8004A87C
{
    #define OFFSET_X SCREEN_POSITION_X(50.0f)
    #define OFFSET_Y SCREEN_POSITION_Y(47.0f)

    if (x != NO_VALUE)
    {
        g_StringPositionX0 = x - OFFSET_X;
        g_StringPositionX1 = (s16)(x - OFFSET_X);
    }

    if (y != NO_VALUE)
    {
        g_StringPositionY = y - OFFSET_Y;
    }

    D_800AD49C = 6; // Maybe `ColorId_LightGrey`.
}

void func_8004A8C0(s32 arg0) // 0x8004A8C0
{
    D_800AD49C = arg0;
}

void func_8004A8CC() // 0x8004A8CC
{
    D_800AD49C = 6; // Maybe `ColorId_LightGrey`.
}

void Gfx_StringSetColor(s16 colorId) // 0x8004A8DC
{
    g_StringColorId = colorId;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", Gfx_StringDraw); // 0x8004A8E8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004ACF4); // 0x8004ACF4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004AF18); // 0x8004AF18

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004B658); // 0x8004B658

void func_8004B684() // 0x8004B684
{
    D_800C38B4 = 1;
    D_800C38B0.field_0 = 0;
    D_800C38B0.field_1 = 1;
    g_StringPositionX1 = SCREEN_POSITION_X(-37.5f);
    g_StringColorId = ColorId_White;
    g_SysWork.field_2350_0 = 0;
}

void func_8004B6D4(s16 arg0, s16 arg1) // 0x8004B6D4
{
    if (arg0 != NO_VALUE)
    {
        D_800C38FC = arg0 + (-g_GameWork.gsScreenWidth_588 / 2);
        D_800C391C = D_800C38FC;
    }

    if (arg1 != NO_VALUE)
    {
        D_800C38FE = arg1 + (-g_GameWork.gsScreenHeight_58A / 2);
    }
}

void func_8004B74C(s16 arg0) // 0x8004B74C
{
    if ((u32)arg0 >= 5)
    {
        D_800C391E = 0;
        return;
    }

    D_800C391E = arg0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004B76C); // 0x8004B76C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", Gfx_StringDrawInt); // 0x0x8004B9F8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004BB10); // 0x8004BB10

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004BB4C); // 0x8004BB4C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004BBF4); // 0x8004BBF4

void func_8004BCBC(s32 arg0) // 0x8004BCBC
{
    GsMapModelingData(arg0 + 4);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004BCDC); // 0x8004BCDC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004BD74); // 0x8004BD74

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004BFE8); // 0x8004BFE8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004C040); // 0x8004C040

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", Player_AnimUpdate); // 0x8004C088

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004C328); // 0x8004C328