#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/map0/map0_s01.h"
#include "maps/characters/cybil.h"

#include "../src/maps/chara_util.c" // 0x800D9B0C

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800DA51C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800DA52C

#include "maps/shared/Map_RoomBgmInit_CheckCond.h" // 0x800DA778

void Map_RoomBgmInit_CondTrue(void) // 0x800DA7AC
{
    s32 var;

    if (!Savegame_EventFlagGet(EventFlag_M0S01_AirScreamerDied))
    {
        if (!Savegame_EventFlagGet(EventFlag_49)) // If Cybil and Harry cutscene hasn't finished.
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

    Bgm_TrackChange(var);
}

void Map_RoomBgmInit_CondFalse(void) // 0x800DA7FC
{
    s32    flags;
    q19_12 var1;

    var1 = Q12(0.333f);
    if (!Savegame_EventFlagGet(EventFlag_146))
    {
        // Air Screamer isn't dead or the Cybil and Harry cutscene has started.
        if (!(Savegame_EventFlagGet(EventFlag_M0S01_AirScreamerDied) || Savegame_EventFlagGet(EventFlag_49)))
        {
            var1 = Q12(240.0f);

            // FMV has just played and unknown.
            if (Savegame_EventFlagGet(EventFlag_M0S01_FmvStarted) && g_GameWork.bgmIdx == 9)
            {
                flags = BgmFlag_Layer1;
            }
            else
            {
                flags = BgmFlag_Layer0 | BgmFlag_MuteAll;
            }
        }
        // Air Screamer cutscene finished.
        else if (Savegame_EventFlagGet(EventFlag_47))
        {
            if (!Savegame_EventFlagGet(EventFlag_M0S01_AirScreamerDied))
            {
                var1  = Q12(240.0f);
                flags = BgmFlag_KeepAlive;
            }
            else
            {
                var1  = Q12(0.125f);
                flags = BgmFlag_Layer0 | BgmFlag_MuteAll;
            }
        }
        else
        {
            flags = BgmFlag_Layer0;
        }
    }
    else
    {
        flags = BgmFlag_Layer0;
    }

    Bgm_Update(flags, var1, NULL);
}

void GameBoot_LoadScreen_StageString(void) // 0x800DA8A4
{
    ScreenFade_Start(false, true, false);

    Text_Debug_PositionSet(100, 100);
    Text_Debug_Draw("STAGE 0-1");
    GameBoot_LoadScreen_BackgroundImg();
}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800DA8E8
