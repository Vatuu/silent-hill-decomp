#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/map0_s00.h"

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D2F08

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D309C

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", sharedFunc_800D3308_0_s00); // 0x800D3308

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", sharedFunc_800D3B44_0_s00); // 0x800D3B44

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D3EF4);

void func_800D4924() {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D492C);

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D63D0

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D54A8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D5B48);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D5C64);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D5FCC);

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D63D0

void func_800D654C() {}

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D6554

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D670C

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D67FC

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", sharedFunc_800D6970_0_s00); // 0x800D6970

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", sharedFunc_800D70C4_0_s00); // 0x800D70C4

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", sharedFunc_800D7BE8_0_s00); // 0x800D7BE8

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D7E04

// `arg2` = another `s_SubCharacter`?
void Ai_Cheryl_Update(s_SubCharacter* chara, s32 arg1, s32 arg2) // 0x800D7FB8
{
    if (chara->model_0.charaId_0 != Chara_Cheryl)
    {
        Ai_Cheryl_Init(chara);
    }

    func_800D8310(chara, arg2);       // Control.
    func_800D8124(chara, arg2);       // Translate + rotate.
    func_800D802C(chara, arg1, arg2); // Modulate speed and something else?
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D802C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D8124);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D8310);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D8748);

void Ai_Cheryl_Init(s_SubCharacter* chara) // 0x800D8888
{
    sharedFunc_800D923C_0_s00(chara);
    D_800E3A30 = 0;
}

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D88AC

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D88C0

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D8904

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D891C

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D8928

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D893C

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D8950

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D8964);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D8A00);

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D9064

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D9078

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D908C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D9188);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D921C);

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D923C

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D929C

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D92AC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D94F8);

/** Debug function??? It is unused here... */
void func_800D95D4() // 0x800D95D4
{
    g_Gfx_ScreenFade = 7;
    Gfx_DebugStringPosition(100, 100);
    Gfx_DebugStringDraw(&D_800CAE7C); // String "STAGE 0-0"
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D9610);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D9748);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D9D98);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DA028);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DA254);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DA454);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DA5A0);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DAA68);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DAB8C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DACB0);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DADD4);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DAEFC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DB26C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DB514);

void func_800DB870() // 0x800DB870
{
    switch (g_SysWork.sysStateStep_C)
    {
        case 0:
            sharedFunc_800D20E4_0_s00();

            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.sysStateStep_C++;

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_800860B0(0, 26, 0, 0, 0, 0);
            break;

        default:
            func_800D2244(0);

            g_SysWork.sysState_8     = 0;
            g_SysWork.timer_24       = 0;
            g_SysWork.sysStateStep_C = 0;
            g_SysWork.field_28       = 0;
            g_SysWork.field_10       = 0;
            g_SysWork.timer_2C       = 0;
            g_SysWork.field_14       = 0;
            break;
    }
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DB94C);

void func_800DBE00() // 0x800DBE00
{
    func_8004690C(0x54F);
    func_8004690C(0x551);
    func_8004690C(0x550);

    Sd_EngineCmd(22);
    func_800892A4(4);

    g_SysWork.sysState_8                       = 0;
    g_SysWork.timer_24                         = 0;
    g_SysWork.sysStateStep_C                   = 0;
    g_SysWork.field_28                         = 0;
    g_SysWork.field_10                         = 0;
    g_SysWork.timer_2C                         = 0;
    g_SysWork.field_14                         = 0;
    g_SysWork.player_4C.chara_0.position_18.vy = 0;
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DBE68);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DBF08);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DC1E8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DC33C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DC694);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DC8D8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DCA30);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DCC54);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DCDA8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DCF38);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DD0CC);
