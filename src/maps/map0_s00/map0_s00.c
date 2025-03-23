#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "maps/map0/s00.h"

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

void func_800D0124() {}

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

void func_800D0E04()
{
    func_8004690C(0x550);
}

void func_800D0E24() {}

void func_800D0E2C() {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0E34);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D1C38);

void func_800D209C()
{
    g_SysWork.field_47 = NO_VALUE;
    g_SaveGamePtr->field_AA = 0;

    func_800D20E4();
    func_800D2C7C(84);
}

void func_800D20D8()
{
    g_SysWork.field_2358 = 0;
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D20E4);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D2244);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D23EC);

void func_800D2C7C(s32 arg0)
{
    s_MainCharacterExtra* playerExtra = &g_SysWork.player_4C.extra_128;
    s_SubCharacter*       chara       = &g_SysWork.player_4C.chara_0;

    g_SysWork.player_4C.chara_0.field_126 = 0;

    D_800C4606 = 0;
    
    switch (arg0)
    {
        case 0x36:
            D_800C457C = 0;
            break;

        case 0x35:
            D_800C457C = 1;
            break;

        case 0x38:
            D_800C457C = 3;
            break;

        case 0x39:
            D_800C457C = 4;
            break;
    }

    g_SysWork.player_4C.extra_128.field_1C = arg0;

    chara->model_0.isAnimStateUnchanged_3 = 0;
    chara->model_0.field_2 = 0;

    playerExtra->model_0.isAnimStateUnchanged_3 = 0;
    playerExtra->model_0.field_2 = 0;

    g_SysWork.player_4C.extra_128.field_20 = 0;
    g_SysWork.player_4C.extra_128.field_24 = 0;
}

void func_800D2D2C()
{
    D_800C4606++;
}

void func_800D2D44()
{
    s_MainCharacterExtra* playerExtra = &g_SysWork.player_4C.extra_128;
    s_SubCharacter*       chara       = &g_SysWork.player_4C.chara_0;

    playerExtra->model_0.anim_4.flags_2 &= ~AnimFlag_Interpolate;
    chara->model_0.anim_4.flags_2 &= ~AnimFlag_Interpolate;
}

s32 func_800D2D6C()
{
    return ~(g_SysWork.player_4C.chara_0.model_0.anim_4.flags_2 & AnimFlag_Interpolate);
}

void func_800D2D84()
{
    s_MainCharacterExtra* playerExtra = &g_SysWork.player_4C.extra_128;
    s_SubCharacter*       chara       = &g_SysWork.player_4C.chara_0;

    playerExtra->model_0.anim_4.flags_2 |= AnimFlag_Interpolate;
    chara->model_0.anim_4.flags_2 |= AnimFlag_Interpolate;
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D2DAC);

s32 func_800D2E50()
{
    return g_SysWork.player_4C.chara_0.field_126 == 0;
}

void func_800D2E60()
{
    g_SysWork.player_4C.chara_0.field_126 = 0;
}

void func_800D2E6C() {}

void func_800D2E74() {}

void func_800D2E7C() {}

void func_800D2E84() {}

void func_800D2E8C() {}

s32 func_800D2E94()
{
	return 0;
}

void func_800D2E9C() {}

u8 func_800D2EA4()
{
    return g_SysWork.player_4C.chara_0.field_10D;
}

void func_800D2EB4()
{
    u8 temp_a0;

    temp_a0 = g_SysWork.field_47;
    g_SysWork.field_47 = NO_VALUE;
    D_800DD59C = temp_a0;

    func_8003DD80(1, 17);
}

void func_800D2EF4()
{
    g_SysWork.field_47 = D_800DD59C;
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D2F08);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D309C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D3308);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D3B44);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D3EF4);

void func_800D4924() {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D492C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D5098);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D54A8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D5B48);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D5C64);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D5FCC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D63D0);

void func_800D654C() {}

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

void func_800D8888()
{
    func_800D923C();
    D_800E3A30 = 0;
}

void func_800D88AC(s_SubCharacter* arg0)
{
    arg0->field_F4 = 0;
    arg0->field_F0 = 0;
    arg0->field_EC = 0;
    arg0->field_126 = 0;
}

void func_800D88C0(s_SubCharacter* chara, s32 arg1)
{
    chara->field_F4 = 1;

    if (arg1 != 0)
    {
        chara->model_0.anim_4.animIdx_0 = 3;
        chara->model_0.anim_4.frameIdx_8 = 0;
        chara->model_0.anim_4.frameTime_4 = 0;
        chara->model_0.anim_4.frameTimeTarget_A = FP_TO(1, Q12_SHIFT);
    }
    else
    {
        chara->field_E8 = 0;
        chara->model_0.isAnimStateUnchanged_3 = 0;
    }

    chara->model_0.anim_4.flags_2 |= AnimFlag_Interpolate;
}

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

s32 func_800D929C()
{
    return D_800A999C;
}

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

void func_800DBE00()
{
    func_8004690C(0x54F);
    func_8004690C(0x551);
    func_8004690C(0x550);

    SD_EngineCmd(22);
    func_800892A4(4);

    g_SysWork.sysState_8 = 0;
    g_SysWork.field_24 = 0;
    g_SysWork.sysStateStep_C = 0;
    g_SysWork.field_28 = 0;
    g_SysWork.field_10 = 0;
    g_SysWork.field_2C = 0;
    g_SysWork.field_14 = 0;
    g_SysWork.player_4C.chara_0.position_18.vy = 0;
}

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
