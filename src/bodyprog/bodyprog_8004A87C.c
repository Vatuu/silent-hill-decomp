#include "game.h"

#include <libgs.h>

#include "bodyprog/bodyprog.h"

void GFX_StringPosition(s32 x, s32 y)
{
    if (x != -1)
    {
        D_800C38A8 = x - 160;
        D_800C38AC = (s16)(x - 160);
    }

    if (y != -1)
    {
        D_800C38AA = y - 112;
    }

    D_800AD49C = 6;
}

void func_8004A8C0(s32 arg0)
{
    D_800AD49C = arg0;
}

void func_8004A8CC(void)
{
    D_800AD49C = 6;
}

void func_8004A8DC(s16 arg0)
{
    D_800AD498 = arg0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", GFX_StringDraw);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004ACF4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004AF18);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004B658);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004B684);

void func_8004B6D4(s16 arg0, s16 arg1)
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

void func_8004B74C(s16 arg0)
{
    if ((u32)arg0 >= 5)
    {
        D_800C391E = 0;
        return;
    }
    
    D_800C391E = arg0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004B76C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004B9F8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004BB10);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004BB4C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004BBF4);

void func_8004BCBC(s32 arg0)
{
    GsMapModelingData(arg0 + 4);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004BCDC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004BD74);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004BFE8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004C040);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004C088);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004C328);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004C45C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004C4F8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004C54C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004C564);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004C8DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004C9B0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004D1A0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004D518);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004E6D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004E864);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004EC7C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004EE94);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004EF48);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004F10C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004F190);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004F57C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004F5DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004F764);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004FB0C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8004FBCC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80051020);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005192C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80052088);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800521A8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005227C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800523D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800539A4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80053B08);

// TODO: Insert field_2352 properly.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", GameFs_Tim00TIMLoad);
/*void GameFs_Tim00TIMLoad() // 0x80053dA0
{
    if (g_SysWork.flags_2352 & (1 << 0))
    {
        return;
    }
    
    Fs_QueueStartReadTim(FILE_ITEM_TIM00_TIM, FS_BUFFER_1, &D_800A906C);
    g_SysWork.flags_2352 |= 1 << 0;
}*/

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80053DFC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80054024);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800540A4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80054200);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80054558);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80054634);

// Requires jump table.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800546A8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80054720);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005487C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800548D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80054928);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800549A0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80054A04);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80054AD8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80054CAC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80054FC0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055028);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800550D0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055330);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800553C4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800553E0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055434);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005545C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055490);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800554C4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055648);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800557DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055814);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055840);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800559A8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055A50);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055A90);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055B74);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055C3C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055D78);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055E90);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055ECC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80055F08);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800560FC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800561A4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056244);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056348);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800563E8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056464);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056504);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056558);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005660C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800566B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056774);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056888);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056954);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056A88);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056BF8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056C80);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056C8C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056CB4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056D64);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80056D8C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80057090);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800571D0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80057200);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80057208);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80057210);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80057218);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80057220);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80057228);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80057344);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800574D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005759C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80057658);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80057A3C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80057B7C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005801C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80059D50);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80059E34);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005A21C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005A42C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005A478);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005A838);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005A900);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005AA08);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005AC50);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005B1A0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005B1FC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005B370);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005B378);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005B3A4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005B3BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005B424);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005B46C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005B474);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005B4BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005B55C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005B62C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005BF0C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005BF38);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005BF58);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005C1CC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005C478);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005C7B0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005C7D0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005C814);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005C944);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005CB20);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005CD38);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005D50C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005D86C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005D974);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005D9B8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005DC1C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005DC3C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005DD44);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005DE0C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005E0DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005E414);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005E650);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005E70C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005E7E0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005E89C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005F55C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005F680);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8005F6B0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80060044);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800611C0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800622B8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800625F4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80062708);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006342C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80063A50);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80064334);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80064F04);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80064FC0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800652F4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80065B94);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80066184);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80066D90);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80066E40);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80066E7C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80066EB0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80067914);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80068CC0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80068E0C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800692A4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800697EC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80069810);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80069820);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006982C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80069844);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80069860);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006993C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80069994);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800699E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800699F8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80069B24);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80069BA8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80069DF0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80069FFC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006A178);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006A1A4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006A3B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006A42C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006A4A8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006A940);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006AB50);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006ABC0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006AD44);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006AEAC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006B004);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006B1C8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006B318);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006B6E8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006B7E0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006B8F8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006B9C8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006BB50);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006BC34);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006BCC4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006BDDC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006BE40);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006BF88);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006C0C8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006C1B8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006C248);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006C3D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006C45C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006C794);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006C838);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006CA18);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006CB90);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006CC44);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006CC9C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006CF18);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006D01C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006D2B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006D600);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006D774);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006D7EC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006D90C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006DA08);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006DAE4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006DB3C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006DC18);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006DCE0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006DEB0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006E0AC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006E150);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006E490);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006E53C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006E78C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006EB8C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006EE0C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006EEB8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006F250);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006F338);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006F3C4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006F620);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006F8FC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006F99C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006FAFC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8006FD90);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80070030);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80070084);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800700F8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80070184);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80070208);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007029C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80070320);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80070360);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80070400);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800705E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800706E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80070B84);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80070CF0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80070DF0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800711C4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80071224);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80071284);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800713B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800713E8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80071620);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800717D0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80071968);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80071CE8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80073FC0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80074254);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80074350);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80075504);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800771BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80077BB8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80077D00);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007B924);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007C0D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007C800);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007D090);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007D6E0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007D6F0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007D970);

// TODO: Can this work without needing inlined func?
static inline SaveGame_PlayerReset(s_ShSaveGame* save)
{
    save->playerHealth_240  = 0x64000; // (100 << 0xC)?
    save->field_A0          = 0;
    save->field_AA          = 0;
    save->field_238         = 0;
    save->gameplayTimer_250 = 0;
    save->field_254         = 0;
    save->field_258         = 0;
    save->field_23C         = 0;
    save->field_24A         = 0;
    save->field_25C &= ~6;
}

void Game_SaveGameResetPlayer() // 0x8007E530
{
    s_ShSaveGame* save = g_SaveGamePtr;
    s32           i;

    g_SaveGamePtr->field_AB = 8;

    for (i = 0; i < GAME_INVENTORY_SIZE; i++)
    {
        save->items_0[i].id    = 0xFF;
        save->items_0[i].count = 0;
    }

    SaveGame_PlayerReset(g_SaveGamePtr);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007E5AC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007E860);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007E8C0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007E9C4);

void GameFs_PlayerMapAnimLoad(s32 mapIdx) // 0x8007EB64
{
    #define BASE_FILE_IDX FILE_ANIM_HB_M0S00_ANM
    
    if (g_GameWork.mapAnimIdx_5B1 != mapIdx ||
        mapIdx == (FILE_ANIM_HB_M6S04_ANM - BASE_FILE_IDX) ||
        mapIdx == (FILE_ANIM_HB_M7S01_ANM - BASE_FILE_IDX) ||
        mapIdx == (FILE_ANIM_HB_M7S02_ANM - BASE_FILE_IDX))
    {
        g_GameWork.mapAnimIdx_5B1 = mapIdx;
        Fs_QueueStartRead(BASE_FILE_IDX + mapIdx, FS_BUFFER_4);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007EBBC);

// Requires jump table.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007F14C);

void func_8007F1CC() // 0x8007F1CC
{
    D_800C455C = 0;
    D_800C4558 = 0;
    D_800C45C0 = 0;
    D_800C45BE = 0;
    D_800C45BC = 0;
    D_800C457E = 0;
    D_800C4604 = 0;
    D_800C45F0 = 0;
    D_800C45E8 = 0;
    D_800C4582 = 0;
    D_800C45AE = 0;
    D_800C4586 = 0;
    D_800C4580 = 0;
    D_800C45AC = 0;
    D_800C4584 = 0;
    D_800AF214 = 0;
}

void func_8007F250(u8* ptr, s8 arg1) // 0x8007F250
{
    *ptr = D_800C4561;
    D_800C4562 = arg1;
}

s32 func_8007F26C() // 0x8007F26C
{
    if (g_SysWork.player_4C.extra_128.field_20 == 25 ||
        g_SysWork.player_4C.extra_128.field_1C == 5 ||
        g_SysWork.player_4C.extra_128.field_1C == 6)
    {
        return 1;
    }
    
    return 0;
}

s32 func_8007F2AC() // 0x8007F2AC
{
    if (g_SysWork.player_4C.character.health_B0 <= 0 ||
        g_SysWork.field_4B != 0 ||
        g_SysWork.player_4C.extra_128.field_1C == 5 ||
        g_SysWork.player_4C.extra_128.field_1C == 6 ||
        (g_SysWork.player_4C.extra_128.field_1C - 7) < 44u) // TODO: Probably not how OG condition was.
    {
        return 1;
    }
    
    return 0;
}

s16 Player_AnimGetSomething() // 0x8007F308
{
    return g_MaybePlayerAnims[g_SysWork.player_4C.character.animIdx_4].field_C;
}

// Large function. Something to do with player control.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007F32C);

// Medium function. Player-related.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007F95C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007FB34);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007FB94);

// Similar to above.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007FC48);

s32 func_8007FD2C() // 0x8007FD2C
{
    return g_SysWork.player_4C.character.field_104;
}

s32 func_8007FD3C() // 0x8007FD3C
{
    return g_SysWork.player_4C.character.field_112;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007FD4C);

// Large function.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8007FDE0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800802CC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8008037C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800803FC);

void func_80080458() // 0x80080458
{
    g_ControllerPtr1->btns_new_10 |= Pad_BtnSelect;
}

s32 func_80080478(VECTOR3* pos0, VECTOR3* pos1) // 0x80080478
{
    s32 x0;
    s32 x1;
    s32 y1;
    s32 y0;
    s32 z0;
    s32 z1;
    s32 xDelta;
    s32 zDelta;
    s32 atan2Delta;
    s32 unk;

    x0 = pos0->vx;
    x1 = pos1->vx;
    y0 = pos0->vy;
    y1 = pos1->vy;
    z0 = pos0->vz;
    z1 = pos1->vz;

    xDelta = x1 - x0;
    zDelta = z1 - z0;
    atan2Delta = ratan2(xDelta, zDelta);
    
    unk = func_8008A058(func_80080540(xDelta, 0, zDelta));
    return (ratan2(unk, y1 - y0) << 0x10) | (atan2Delta & 0xFFFF);
}

s32 func_80080514() // 0x80080514
{
    s32 rand16;

    rand16 = Rng_Rand16();
    return (((rand16 * 2) ^ rand16) >> 3) & 0xFFF;
}

// TODO: Try decomping by hand. -- Sezz
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80080540);

s32 PreservedSignSubtract(s32 value, s32 subtractor) // 0x80080594
{
    s32 signBit;
    s32 absDiff;
    
    signBit = value >> 31;  
    absDiff = ((value ^ signBit) - signBit) - subtractor;  
    return ((absDiff & ~(absDiff >> 31)) ^ signBit) - signBit; 
}

// Unknown instruction error?
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800805BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_800806AC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8008074C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_8008076C);

// TODO: Matched, but some issue here.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", func_80080884);
/*s32 func_80080884() // 0x80080884
{
    func_8008076C();
    return D_800AFC7C;
}*/

s32 func_800808AC() // 0x800808AC
{
    func_8008076C();
    return D_800AFC90;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_8004A87C", Math_MulFixed);

s32 func_800808F8(s32 arg0) // 0x800808F8
{
    s32 res;

    if (arg0 < 0x4000)
    {
        return 0;
    }
    
    if (arg0 > 0x3FFFF)
    {
        if (arg0 > 0x3FFFFF)
        {
            return 12;
        }
    
        res = 8;
        return res;
    }
    
    res = 4;
    return res;
}
