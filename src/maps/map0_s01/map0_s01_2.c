#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/map0_s01.h"
#include "maps/characters/Chara_Cybil.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D9B0C

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D9B20

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D9B64

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D9B7C

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D9B88

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D9B9C

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D9BB0

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D9BC4

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800D9C60

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800DA2C4

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800DA2D8

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800DA2EC

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800DA3E8

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800DA49C

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800DA4BC

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800DA51C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800DA52C

void func_800DA778(s32 arg0) // 0x800DA778
{
    (arg0 != 0) ? func_800DA7AC() : func_800DA7FC();
}

void func_800DA7AC(void) // 0x800DA7AC
{
    s32 var;

    if (!Savegame_EventFlagGet(EventFlag_48))
    {
        if (!Savegame_EventFlagGet(EventFlag_49))
        {
            var = 9;
        }
        else
        {
            var = 30;
        }
    }
    else
    {
        var = 6;
    }

    func_8003640C(var);
}

void func_800DA7FC(void) // 0x800DA7FC
{
    s32    flags;
    q19_12 var1;

    var1 = Q12(0.333f);
    if (!Savegame_EventFlagGet(EventFlag_146))
    {
        if (!(Savegame_EventFlagGet(EventFlag_48) || Savegame_EventFlagGet(EventFlag_49)))
        {
            var1 = Q12(240.0f);
            if (Savegame_EventFlagGet(EventFlag_39) && g_GameWork.soundCmd_5B2 == 9)
            {
                flags = 2;
            }
            else
            {
                flags = (1 << 0) | (1 << 9);
            }
        }
        else if (Savegame_EventFlagGet(EventFlag_47))
        {
            if (!Savegame_EventFlagGet(EventFlag_48))
            {
                var1  = Q12(240.0f);
                flags = 1 << 8;
            }
            else
            {
                var1  = Q12(0.125f);
                flags = (1 << 0) | (1 << 9);
            }
        }
        else
        {
            flags = 1 << 0;
        }
    }
    else
    {
        flags = 1 << 0;
    }

    func_80035F4C(flags, var1, NULL);
}

void Gfx_LoadingScreen_StageString(void) // 0x800DA8A4
{
    ScreenFade_Start(false, true, false);

    Gfx_DebugStringPosition(100, 100);
    Gfx_DebugStringDraw("STAGE 0-1");
    Gfx_LoadingScreen_BackgroundTexture();
}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800DA8E8
