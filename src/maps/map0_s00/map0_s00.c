#include "common.h"

typedef struct
{
    s8  unk_0[5];
    u16 field_6;
} s_800BA134;

extern u8 D_800BA007;

extern u16 D_800BA012;

extern s_800BA134 D_800BA134[];

extern u8 D_800C4606;

extern u8 D_800DD59C;

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CB6B0);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CBBBC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CBC94);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CBFB0);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CC04C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CC6E8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CC8FC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CD1F4);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CD8E8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CE02C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CE544);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CEB24);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CEFF4);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CF7AC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CF974);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CFFF8);

void func_800D0124(void) {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D012C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D01BC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0274);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0394);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0600);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0700);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D08B8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0A60);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0B18);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0CB8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0E04);

void func_800D0E24(void) {}

void func_800D0E2C(void) {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0E34);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D1C38);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D209C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D20D8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D20E4);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D2244);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D23EC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D2C7C);

void func_800D2D2C(void)
{
    D_800C4606++;
}

void func_800D2D44(void)
{
    D_800BA134[0].field_6 = D_800BA134[0].field_6 & 0xFFFE;
    D_800BA134[-37].field_6 = D_800BA134[-37].field_6 & 0xFFFE; // -37?
}

s32 func_800D2D6C(void)
{
    return ~(D_800BA012 & 1);
}

void func_800D2D84(void)
{
    D_800BA134[0].field_6 = D_800BA134[0].field_6 | 1;
    D_800BA134[-37].field_6 = D_800BA134[-37].field_6 | 1; // -37?
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D2DAC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D2E50);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D2E60);

void func_800D2E6C(void) {}

void func_800D2E74(void) {}

void func_800D2E7C(void) {}

void func_800D2E84(void) {}

void func_800D2E8C(void) {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D2E94);

void func_800D2E9C(void) {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D2EA4);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D2EB4);

void func_800D2EF4(void)
{
    D_800BA007 = D_800DD59C;
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D2F08);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D309C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D3308);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D3B44);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D3EF4);

void func_800D4924(void) {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D492C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D5098);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D54A8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D5B48);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D5C64);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D5FCC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D63D0);

void func_800D654C(void) {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D6554);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D670C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D67FC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D6970);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D70C4);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D7BE8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D7E04);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D7FB8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D802C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D8124);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D8310);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D8748);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D8888);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D88AC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D88C0);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D8904);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D891C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D8928);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D893C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D8950);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D8964);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D8A00);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D9064);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D9078);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D908C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D9188);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D921C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D923C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D929C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D92AC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D94F8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D95D4);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D9610);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D9748);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D9D98);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DA028);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DA254);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DA454);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DA5A0);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DAA68);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DAB8C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DACB0);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DADD4);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DAEFC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DB26C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DB514);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DB870);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DB94C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DBE00);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DBE68);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DBF08);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DC1E8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DC33C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DC694);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DC8D8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DCA30);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DCC54);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DCDA8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DCF38);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DD0CC);
