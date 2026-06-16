#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/events/map_msg.h"
#include "bodyprog/math/math.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/sound/sound_system.h"
#include "bodyprog/text/text_draw.h"
#include "main/fsqueue.h"

// ========================================
// STATIC VARIABLES
// ========================================

static s32 g_MapMsg_CurrentIdx       = 0;
static s16 g_MapMsg_SelectFlashTimer = 0;

// ========================================
// GLOBAL VARIABLES
// ========================================

s_MapMsgSelect g_MapMsg_Select;
u8             g_MapMsg_AudioLoadBlock;
s8             g_MapMsg_SelectCancelIdx;

// @hack JP calls different `Gfx_StringSetColor` / `Gfx_StringDraw` funcs here.
// The normal funcs available are also used in JP, so can't be renamed.
// For now override `Gfx_StringSetColor` calls in this file until those JP funcs get figured out.
#if VERSION_REGION_IS(NTSCJ)
    #define Gfx_StringSetColor Gfx_StringSetColor_JP
#endif

s32 Gfx_MapMsg_Draw(s32 mapMsgIdx) // 0x800365B8
{
    #define MSG_TIMER_MAX   (Q12(524288.0f) - 1)
    #define FINISH_CUTSCENE 0xFF
    #define FINISH_MAP_MSG  0xFF

    s32        temp_s1;
    bool       hasInput;
    s32        temp;
    s32        var_a1;
    static s32 stateMachineIdx0;
    static s32 stateMachineIdx1;
    static s32 msgDisplayLength;
    static s32 msgIdx;
    static s32 msgDisplayInc;
    static s32 D_800BCD74;

    // Check for user input.
    hasInput = false;
    if ((g_Controller0->clickedBtnFlags & (g_GameWorkPtr->config.controllerConfig.enter |
                                          g_GameWorkPtr->config.controllerConfig.cancel)) ||
        (g_Controller0->heldBtnFlags & g_GameWorkPtr->config.controllerConfig.skip))
    {
        hasInput = true;
    }

    g_SysWork.playerWork.player.properties.player.gasWeaponPowerTimer = Q12(0.0f);
    func_8004C564(g_SysWork.playerCombat.weaponAttack, WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap));

    if (msgIdx != mapMsgIdx)
    {
        g_SysWork.isMgsStringSet = false;
    }

    switch (g_SysWork.isMgsStringSet)
    {
        case false:
            g_SysWork.mapMsgTimer            = NO_VALUE;
            g_MapMsg_Select.maxIdx           = NO_VALUE;
            g_MapMsg_Select.selectedEntryIdx = 0;
            g_MapMsg_AudioLoadBlock          = 0;
            g_MapMsg_CurrentIdx              = mapMsgIdx;
            stateMachineIdx0                 = 0;
            stateMachineIdx1                 = 0;
            msgIdx                           = mapMsgIdx;
            msgDisplayLength                 = 0;
            msgDisplayInc                    = 2; // Advance 2 glyphs at a time.

            Gfx_MapMsg_DefaultStringInfoSet();
            var_a1 = Gfx_MapMsg_CalculateWidths(g_MapMsg_CurrentIdx);

#if VERSION_REGION_IS(NTSCJ)
            if (var_a1 != 0)
            {
                switch (var_a1)
                {
                    case 2:
                    case 3:
                        func_8004B45C(g_MapMsg_CurrentIdx + 1, var_a1);
                        break;

                    case 4:
                        func_8004B45C(0, 2);
                        break;
                }
            }
#endif

            D_800BCD74 = 1;
            g_SysWork.isMgsStringSet++;
            return MapMsgState_Finish;

        case true:
            if (g_SysWork.bgmStatusFlags & BgmStatusFlag_VoiceDialog)
            {
                if (Sd_AudioStreamingCheck() == AudioStreamingState_XaLoadPending)
                {
                    D_800BCD74 = 0;
                    break;
                }

                if (D_800BCD74 != 0)
                {
                    break;
                }
            }
            else
            {
                D_800BCD74 = 0;
            }

            Gfx_StringSetColor(StringColorId_White);
#if VERSION_REGION_IS(NTSC)
            Gfx_StringSetPosition(40, 160);
#endif

            msgDisplayLength += msgDisplayInc;
            msgDisplayLength  = CLAMP(msgDisplayLength, 0, MAP_MESSAGE_DISPLAY_ALL_LENGTH);

            if (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer > 0)
            {
                g_SysWork.mapMsgTimer -= g_DeltaTimeRaw;
                g_SysWork.mapMsgTimer  = CLAMP(g_SysWork.mapMsgTimer, Q12(0.0f), MSG_TIMER_MAX);
            }

            temp_s1 = stateMachineIdx0;
            if (temp_s1 == NO_VALUE)
            {
                if (g_MapMsg_AudioLoadBlock == 0)
                {
                    Game_TimerUpdate();
                }

                temp = stateMachineIdx1;
                if (temp == temp_s1)
                {
                    if (g_MapMsg_Select.maxIdx == temp)
                    {
                        if (!((g_MapMsg_AudioLoadBlock & (1 << 0)) || !hasInput) ||
                            (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer == 0))
                        {
                            stateMachineIdx1 = FINISH_MAP_MSG;

                            if (g_SysWork.bgmStatusFlags & BgmStatusFlag_VoiceDialog)
                            {
                                SD_Call(19);
                            }
                            break;
                        }
                    }
                    else if (g_Controller0->clickedBtnFlags & g_GameWorkPtr->config.controllerConfig.cancel)
                    {
                        g_MapMsg_Select.maxIdx           = temp;
                        g_MapMsg_Select.selectedEntryIdx = g_MapMsg_SelectCancelIdx;

                        Sd_PlaySfx(Sfx_MenuCancel, Q8(0.0f), Q8(0.25f));

                        if (g_SysWork.silentYesSelection)
                        {
                            g_SysWork.silentYesSelection = false;
                        }

                        stateMachineIdx1 = FINISH_MAP_MSG;
                        break;
                    }
                    else if (g_Controller0->clickedBtnFlags & g_GameWorkPtr->config.controllerConfig.enter)
                    {
                        g_MapMsg_Select.maxIdx = temp;

                        if (g_MapMsg_Select.selectedEntryIdx == (s8)g_MapMsg_SelectCancelIdx)
                        {
                            Sd_PlaySfx(Sfx_MenuCancel, Q8(0.0f), Q8(0.25f));
                        }
                        else if (!g_SysWork.silentYesSelection)
                        {
                            Sd_PlaySfx(Sfx_MenuConfirm, Q8(0.0f), Q8(0.25f));
                        }

                        if (g_SysWork.silentYesSelection)
                        {
                            g_SysWork.silentYesSelection = false;
                        }

                        stateMachineIdx1 = FINISH_MAP_MSG;
                        break;
                    }
                }
                else if ((!(g_MapMsg_AudioLoadBlock & (1 << 0)) && hasInput && g_MapMsg_Select.maxIdx != 0) ||
                         (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer == 0))
                {
                    if (g_MapMsg_Select.maxIdx != NO_VALUE)
                    {
                        g_MapMsg_Select.maxIdx  = NO_VALUE;
                        stateMachineIdx1 = FINISH_MAP_MSG;
                        break;
                    }

                    g_MapMsg_CurrentIdx++;
                    g_SysWork.mapMsgTimer = g_MapMsg_Select.maxIdx;

                    var_a1 = Gfx_MapMsg_CalculateWidths(g_MapMsg_CurrentIdx);

#if VERSION_REGION_IS(NTSCJ)
                    if (var_a1 != 0)
                    {
                        switch (var_a1)
                        {
                            case 2:
                            case 3:
                                func_8004B45C(g_MapMsg_CurrentIdx + 1, var_a1);
                                break;

                            case 4:
                                func_8004B45C(0, 2);
                                break;
                        }
                    }
#endif

                    msgDisplayLength = 0;
                    stateMachineIdx0 = 0;

                    if (g_MapMsg_AudioLoadBlock == MapMsgAudioLoadBlock_J2)
                    {
                        D_800BCD74 = 0;
                        return MapMsgState_Idle;
                    }

                    if (g_SysWork.bgmStatusFlags & BgmStatusFlag_VoiceDialog)
                    {
                        SD_Call(19);
                    }

                    D_800BCD74 = 1;
                    return MapMsgState_Finish;
                }
            }
            else
            {
                if (hasInput)
                {
                    msgDisplayLength = MAP_MESSAGE_DISPLAY_ALL_LENGTH;
                }
            }

            stateMachineIdx0 = 0;
            stateMachineIdx1 = Gfx_MapMsg_SelectionUpdate(g_MapMsg_CurrentIdx, &msgDisplayLength);

            if (stateMachineIdx1 != 0 && stateMachineIdx1 < MapMsgCode_Select4)
            {
                stateMachineIdx0 = NO_VALUE;
            }
    }

    if (stateMachineIdx1 != FINISH_MAP_MSG)
    {
        return MapMsgState_Idle;
    }

    g_SysWork.isMgsStringSet            = false;
    g_SysWork.enableHighResGlyphs = false;
    msgDisplayLength               = 0;

    if (g_SysWork.bgmStatusFlags & BgmStatusFlag_VoiceDialog)
    {
        D_800BCD74 = 1;
    }

    return g_MapMsg_Select.selectedEntryIdx + 1;

    #undef MSG_TIMER_MAX
    #undef FINISH_CUTSCENE
    #undef FINISH_MAP_MSG
}

s32 Gfx_MapMsg_SelectionUpdate(u8 mapMsgIdx, s32* arg1) // 0x80036B5C
{
    #define STRING_LINE_OFFSET 16

    s32 i;
    s32 mapMsgCode;

    mapMsgCode = Gfx_MapMsg_StringDraw(g_MapOverlayHdr.mapMessages[mapMsgIdx], *arg1);

    g_MapMsg_SelectFlashTimer += g_DeltaTimeRaw;
    if (g_MapMsg_SelectFlashTimer >= Q12(0.5f))
    {
        g_MapMsg_SelectFlashTimer -= Q12(0.5f);
    }

    switch (mapMsgCode)
    {
        case NO_VALUE:
        case MapMsgCode_None:
            g_MapMsg_SelectFlashTimer = Q12(0.0f);
            break;

        case MapMsgCode_Select2:
        case MapMsgCode_Select3:
        case MapMsgCode_Select4:
            g_MapMsg_Select.maxIdx  = 1;
            g_MapMsg_SelectCancelIdx = (mapMsgCode == 3) ? 2 : 1;

            if (mapMsgCode == MapMsgCode_Select4)
            {
                // Shows selection prompt with map messages at indices 0 and 1.
                // All maps have "Yes" and "No" as messages 0 and 1, respectively.
                for (i = 0; i < 2; i++)
                {
                    if (g_MapMsg_Select.selectedEntryIdx == i)
                    {
                        Gfx_StringSetColor(((g_MapMsg_SelectFlashTimer >> 10) * 3) + 4);
                    }
                    else
                    {
                        Gfx_StringSetColor(StringColorId_White);
                    }

#if VERSION_REGION_IS(NTSC)
                    Gfx_StringSetPosition(32, (STRING_LINE_OFFSET * i) + 98);
                    Gfx_StringDraw(g_MapOverlayHdr.mapMessages[i], MAP_MESSAGE_DISPLAY_ALL_LENGTH);
#else
                    Gfx_StringDraw_JP(g_MapOverlayHdr.mapMessages[i], i);
#endif
                }

                mapMsgCode = 2;
            }
            else
            {
                // Shows selection prompt with 2 or 3 map messages from current index + 1/2/3.
                // Requires prompt options to be arranged sequentially in the map message array, e.g.
                // `[idx]`:     "Select one of 3 options. ~S3"
                // `[idx + 1]`: "Option 1"
                // `[idx + 2]`: "Option 2"
                // `[idx + 3]`: "Option 3"
                for (i = 0; i < mapMsgCode; i++)
                {
                    if (g_MapMsg_Select.selectedEntryIdx == i)
                    {
                        Gfx_StringSetColor(((g_MapMsg_SelectFlashTimer >> 10) * 3) + 4);
                    }
                    else
                    {
                        Gfx_StringSetColor(StringColorId_White);
                    }

#if VERSION_REGION_IS(NTSC)
                    Gfx_StringSetPosition(32, (STRING_LINE_OFFSET * i) + 96);
                    Gfx_StringDraw(g_MapOverlayHdr.mapMessages[(mapMsgIdx + i) + 1], MAP_MESSAGE_DISPLAY_ALL_LENGTH);
#else
                    Gfx_StringDraw_JP(g_MapOverlayHdr.mapMessages[(mapMsgIdx + i) + 1], i);
#endif
                }
            }

            if (g_Controller0->clickedBtnFlags & ControllerFlag_LStickUp &&
                g_MapMsg_Select.selectedEntryIdx != 0)
            {
                g_MapMsg_SelectFlashTimer = Q12(0.0f);
                g_MapMsg_Select.selectedEntryIdx--;

                Sd_PlaySfx(Sfx_MenuMove, Q8(0.0f), Q8(0.25f));
            }

            if (g_Controller0->clickedBtnFlags & ControllerFlag_LStickDown &&
                g_MapMsg_Select.selectedEntryIdx != (mapMsgCode - 1))
            {
                g_MapMsg_SelectFlashTimer = Q12(0.0f);
                g_MapMsg_Select.selectedEntryIdx++;

                Sd_PlaySfx(Sfx_MenuMove, Q8(0.0f), Q8(0.25f));
            }

            mapMsgCode = NO_VALUE;
            break;

        case MapMsgCode_DisplayAll:
            *arg1 = MAP_MESSAGE_DISPLAY_ALL_LENGTH;
            break;
    }

    return mapMsgCode;

    #undef STRING_LINE_OFFSET
}
