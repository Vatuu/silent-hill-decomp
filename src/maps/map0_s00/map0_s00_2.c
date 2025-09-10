#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
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

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D5B48

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
void Ai_Cheryl_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords) // 0x800D7FB8
{
    if (chara->model_0.charaId_0 != Chara_Cheryl)
    {
        Ai_Cheryl_Init(chara);
    }

    func_800D8310(chara, coords);       // Control.
    func_800D8124(chara, coords);       // Translate + rotate.
    func_800D802C(chara, arg1, coords); // Modulate speed and something else?
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

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D8964

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D8A00);

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D9064

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D9078

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D908C

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D9188

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D921C

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D923C

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D929C

#include "maps/shared/sharedFunc_800D92AC_0_s00.h" // 0x800D92AC

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800D94F8);

/** Debug function? */
void Gfx_LoadingScreen_StageString() // 0x800D95D4
{
    g_Gfx_ScreenFade = SCREEN_FADE_STATUS(ScreenFadeState_FadeInSteps, false);
    Gfx_DebugStringPosition(100, 100);
    Gfx_DebugStringDraw(&D_800CAE7C);
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
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement();

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 26, 0, 0, 0, false);
            break;

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00_2", func_800DB94C);

void func_800DBE00() // 0x800DBE00
{
    func_8004690C(Sfx_Unk1359);
    func_8004690C(Sfx_Unk1361);
    func_8004690C(Sfx_Unk1360);

    Sd_EngineCmd(22);
    func_800892A4(4);

    SysWork_StateSetNext(SysState_Gameplay);
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
