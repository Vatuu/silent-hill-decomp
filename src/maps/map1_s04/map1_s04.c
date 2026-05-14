#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/sound/sound_system.h"
#include "main/rng.h"
#include "maps/map1/map1_s04.h"
#include "maps/particle.h"
#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

#include "maps/characters/player.h"

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CC818

#include "maps/shared/Map_RoomIdxGet.h" // 0x800CC828

void Map_RoomBgmInit(bool arg0) // 0x800CC8C8
{
    s32 fadeSpeed;
    s32 mapRoomIdx;
    s32 bgmFlags;

    mapRoomIdx = g_SavegamePtr->mapRoomIdx;
    bgmFlags     = D_800CCF5C[mapRoomIdx];
    fadeSpeed     = Q12(0.1f);

    switch (mapRoomIdx)
    {
        case 23:
            bgmFlags = 1;
            if (Savegame_EventFlagGet(EventFlag_MapMark_AltSchool1F_CourtyardQuestion))
            {
                bgmFlags = 0x1FE;
                if (Savegame_EventFlagGet(EventFlag_MapMark_308) || Savegame_EventFlagGet(EventFlag_MapMark_AltSchool1F_CourtyardTopArrows))
                {
                    bgmFlags = 0x10;
                }
            }
            break;

        case 38:
            if (Savegame_EventFlagGet(EventFlag_100) && !Savegame_EventFlagGet(EventFlag_107))
            {
                bgmFlags = 1;
                fadeSpeed = Q12(0.3f);
            }
            break;

        case 5:
            if (Savegame_EventFlagGet(EventFlag_121))
            {
                fadeSpeed = Q12(240.0f);
                if (Savegame_EventFlagGet(EventFlag_96))
                {
                    bgmFlags |= 8;
                }
                else
                {
                    bgmFlags = 1;
                }
            }
            break;

        case 11:
            Savegame_EventFlagClear(EventFlag_121);
            break;

        case 7:
            if (!Savegame_EventFlagGet(EventFlag_98) && Savegame_EventFlagGet(EventFlag_122))
            {
                fadeSpeed = Q12(240.0f);
                bgmFlags = 1;
            }
            break;
    }

    Bgm_Update(bgmFlags, fadeSpeed, &D_800CCF54);
}

void GameBoot_LoadScreen_StageString(void) {} // 0x800CCA24

void func_800CCA2C(void) // 0x800CCA2C
{
    s32 temp_s0;

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            g_SysWork.cutsceneBorderState = 20;
            SysWork_StateStepIncrement(0);

        case 1:
            if (g_Controller0->btnsClicked_10 & ControllerFlag_R3)
            {
                D_800CD768 = 0;
                D_800CD76C = 0;
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
            {
                if (D_800CD768 == 0)
                {
                    D_800CD768 = 23;
                }
                D_800CD768--;
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickUp)
            {
                D_800CD768++;
                if (D_800CD768 == 23)
                {
                    D_800CD768 = 0;
                }
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickLeft)
            {
                if (D_800CD76C != 0)
                {
                    D_800CD76C--;
                }
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickRight)
            {
                if (D_800CD76C != 39 && D_800CD038[D_800CD768][D_800CD76C + 1] != 0)
                {
                    D_800CD76C++;
                }
            }

            if (g_Controller0->btnsClicked_10 & ControllerFlag_Circle)
            {
                SD_Call(D_800CD038[D_800CD768][D_800CD76C]);
                D_800CD770 = 0;
                D_800CD774 = 1;
            }

            temp_s0 = D_800CD774;
            if (temp_s0 == 1 && Sd_AudioStreamingCheck() != temp_s0)
            {
                D_800CD774 = 2;
            }

            if (D_800CD774 == 2 && Sd_AudioStreamingCheck() == 1)
            {
                D_800CD770 += g_DeltaTime;

                if (g_Controller0->btnsClicked_10 & ControllerFlag_Cross)
                {
                    D_800CD774 = 0;
                }
            }

            Text_Debug_PositionSet(50, 50);

#if VERSION_EQUAL_OR_OLDER(PROTO_981216)
            // Code seen in 98-12-16 build.
            Text_Debug_Draw("VS 0:");
            Text_Debug_Draw(Text_Debug_IntToString(3, D_800CD768));
            Text_Debug_Draw("\n");
            Text_Debug_Draw("VS 1:");
            Text_Debug_Draw(Text_Debug_IntToString(3, D_800CD76C));
            Text_Debug_Draw("\n");
            Text_Debug_Draw("SDST:");
            Text_Debug_Draw(Text_Debug_IntToString(3, Sd_AudioStreamingCheck()));
            Text_Debug_Draw("\n");

            if (D_800CD774 != 2)
            {
                Text_Debug_Draw("TIME:");
                // 98-12-16 calls into a `8002BCAC` func which is missing in retail. That func then calls `func_800321EC`.
                Gfx_DebugQ12Print(6, 2, D_800CD770);
                Text_Debug_Draw("\n");
            }
#endif

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.skip)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 2:
            if (g_Controller0->btnsClicked_10 & ControllerFlag_Circle)
            {
                SD_Call(D_800CD768_tbl[D_800CD768]);
            }

            if (g_Controller0->btnsClicked_10 & ControllerFlag_Cross)
            {
                Sd_SfxStop(D_800CD768_tbl[D_800CD768]);
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
            {
                if (D_800CD768 == 0)
                {
                    D_800CD768 = 4;
                }
                D_800CD768--;
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickUp)
            {
                D_800CD768++;
                if (D_800CD768 == 4)
                {
                    D_800CD768 = 0;
                }
            }
            break;
    }
}

void Map_WorldObjectsInit(void) {} // 0x800CCE30

void Map_WorldObjectsUpdate(void) // 0x800CCE38
{
    if (g_Controller0->btnsClicked_10 & ControllerFlag_R1)
    {
        SD_Call(Sfx_UseKey);
    }

    if (g_Controller0->btnsClicked_10 & ControllerFlag_R2)
    {
        SD_Call(Sfx_DoorUnlocked);
    }

    if (g_Controller0->btnsClicked_10 & ControllerFlag_R3)
    {
        SD_Call(Sfx_Unk1343);
    }
}

const char* MAP_MESSAGES[] = {
#include "maps/shared/map_msg_common.h"
    /* 15 */ "\tNO_STAGE! ~E "
};
