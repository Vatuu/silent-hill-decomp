#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/demo.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/gfx/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/ranking.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/mem.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

s32 g_MapMsg_CurrentIdx = 0;

s16 g_MapMsg_SelectFlashTimer = 0;

s_MapMsgSelect g_MapMsg_Select;

u8 g_MapMsg_AudioLoadBlock;

s8 g_MapMsg_SelectCancelIdx;

// ========================================
// MAP MESSAGE DISPLAY
// ========================================

s32 Gfx_MapMsg_Draw(s32 mapMsgIdx) // 0x800365B8
{
    #define MSG_TIMER_MAX   (Q12(524288.0f) - 1)
    #define FINISH_CUTSCENE 0xFF
    #define FINISH_MAP_MSG  0xFF

    s32  temp_s1;
    bool hasInput;
    s32  temp;
    static s32 stateMachineIdx1;
    static s32 stateMachineIdx2;
    static s32 msgDisplayLength;
    static s32 msgIdx;
    static s32 msgDisplayInc;
    static s32 D_800BCD74;

    // Check for user input.
    hasInput = false;
    if ((g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                          g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)) ||
        (g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.skip_4))
    {
        hasInput = true;
    }

    g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 = Q12(0.0f);
    func_8004C564(g_SysWork.playerCombat_38.weaponAttack_F, WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap));

    if (msgIdx != mapMsgIdx)
    {
        g_SysWork.isMgsStringSet_18 = 0;
    }

    switch (g_SysWork.isMgsStringSet_18)
    {
        case 0:
            g_SysWork.mapMsgTimer_234C         = NO_VALUE;
            g_MapMsg_Select.maxIdx_0           = NO_VALUE;
            g_MapMsg_Select.selectedEntryIdx_1 = 0;
            g_MapMsg_AudioLoadBlock            = 0;
            g_MapMsg_CurrentIdx                = mapMsgIdx;
            stateMachineIdx1          = 0;
            stateMachineIdx2          = 0;
            msgIdx                   = mapMsgIdx;
            msgDisplayLength             = 0;
            msgDisplayInc                = 2; // Advance 2 glyphs at a time.

            Gfx_MapMsg_DefaultStringInfoSet();
            Gfx_MapMsg_CalculateWidths(g_MapMsg_CurrentIdx);

            D_800BCD74 = 1;
            g_SysWork.isMgsStringSet_18++;
            return MapMsgState_Finish;

        case 1:
            if (g_SysWork.sysFlags_22A0 & SysFlag_5)
            {
                if (Sd_AudioStreamingCheck() == 4)
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
            Gfx_StringSetPosition(40, 160);

            msgDisplayLength += msgDisplayInc;
            msgDisplayLength  = CLAMP(msgDisplayLength, 0, MAP_MESSAGE_DISPLAY_ALL_LENGTH);

            if (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer_234C > 0)
            {
                g_SysWork.mapMsgTimer_234C -= g_DeltaTimeRaw;
                g_SysWork.mapMsgTimer_234C  = CLAMP(g_SysWork.mapMsgTimer_234C, Q12(0.0f), MSG_TIMER_MAX);
            }

            temp_s1 = stateMachineIdx1;
            if (temp_s1 == NO_VALUE)
            {
                if (g_MapMsg_AudioLoadBlock == 0)
                {
                    Game_TimerUpdate();
                }

                temp = stateMachineIdx2;
                if (temp == temp_s1)
                {
                    if (g_MapMsg_Select.maxIdx_0 == temp)
                    {
                        if (!((g_MapMsg_AudioLoadBlock & (1 << 0)) || !hasInput) ||
                            (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer_234C == 0))
                        {
                            stateMachineIdx2 = FINISH_MAP_MSG;

                            if (g_SysWork.sysFlags_22A0 & SysFlag_5)
                            {
                                SD_Call(19);
                            }
                            break;
                        }
                    }
                    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
                    {
                        g_MapMsg_Select.maxIdx_0           = temp;
                        g_MapMsg_Select.selectedEntryIdx_1 = g_MapMsg_SelectCancelIdx;

                        Sd_PlaySfx(Sfx_MenuCancel, 0, Q8_CLAMPED(0.25f));

                        if (g_SysWork.silentYesSelection_2350_4)
                        {
                            g_SysWork.silentYesSelection_2350_4 = false;
                        }

                        stateMachineIdx2 = FINISH_MAP_MSG;
                        break;
                    }
                    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
                    {
                        g_MapMsg_Select.maxIdx_0 = temp;

                        if ((u8)g_MapMsg_Select.selectedEntryIdx_1 == (s8)g_MapMsg_SelectCancelIdx)
                        {
                            Sd_PlaySfx(Sfx_MenuCancel, 0, Q8_CLAMPED(0.25f));
                        }
                        else if (!g_SysWork.silentYesSelection_2350_4)
                        {
                            Sd_PlaySfx(Sfx_MenuConfirm, 0, Q8_CLAMPED(0.25f));
                        }

                        if (g_SysWork.silentYesSelection_2350_4)
                        {
                            g_SysWork.silentYesSelection_2350_4 = false;
                        }

                        stateMachineIdx2 = FINISH_MAP_MSG;
                        break;
                    }
                }
                else if ((!(g_MapMsg_AudioLoadBlock & (1 << 0)) && hasInput && g_MapMsg_Select.maxIdx_0 != 0) ||
                         (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer_234C == 0))
                {
                    if (g_MapMsg_Select.maxIdx_0 != NO_VALUE)
                    {
                        g_MapMsg_Select.maxIdx_0  = NO_VALUE;
                        stateMachineIdx2 = FINISH_MAP_MSG;
                        break;
                    }

                    g_MapMsg_CurrentIdx++;
                    g_SysWork.mapMsgTimer_234C = g_MapMsg_Select.maxIdx_0;

                    Gfx_MapMsg_CalculateWidths(g_MapMsg_CurrentIdx);

                    msgDisplayLength    = 0;
                    stateMachineIdx1 = 0;

                    if (g_MapMsg_AudioLoadBlock == MapMsgAudioLoadBlock_J2)
                    {
                        D_800BCD74 = 0;
                        return MapMsgState_Idle;
                    }

                    if (g_SysWork.sysFlags_22A0 & SysFlag_5)
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

            stateMachineIdx1 = 0;
            stateMachineIdx2 = Gfx_MapMsg_SelectionUpdate(g_MapMsg_CurrentIdx, &msgDisplayLength);

            if (stateMachineIdx2 != 0 && stateMachineIdx2 < MapMsgCode_Select4)
            {
                stateMachineIdx1 = NO_VALUE;
            }
    }

    if (stateMachineIdx2 != FINISH_MAP_MSG)
    {
        return MapMsgState_Idle;
    }

    g_SysWork.isMgsStringSet_18            = 0;
    g_SysWork.enableHighResGlyphs_2350_0 = false;
    msgDisplayLength               = 0;

    if (g_SysWork.sysFlags_22A0 & SysFlag_5)
    {
        D_800BCD74 = 1;
    }

    return g_MapMsg_Select.selectedEntryIdx_1 + 1;
}

s32 Gfx_MapMsg_SelectionUpdate(u8 mapMsgIdx, s32* arg1) // 0x80036B5C
{
    #define STRING_LINE_OFFSET 16

    s32 i;
    s32 mapMsgCode;

    mapMsgCode = Gfx_MapMsg_StringDraw(g_MapOverlayHeader.mapMessages_30[mapMsgIdx], *arg1);

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
            g_MapMsg_Select.maxIdx_0  = 1;
            g_MapMsg_SelectCancelIdx = (mapMsgCode == 3) ? 2 : 1;

            if (mapMsgCode == MapMsgCode_Select4)
            {
                // Shows selection prompt with map messages at indices 0 and 1.
                // All maps have "Yes" and "No" as messages 0 and 1, respectively.
                for (i = 0; i < 2; i++)
                {
                    if ((u8)g_MapMsg_Select.selectedEntryIdx_1 == i)
                    {
                        Gfx_StringSetColor(((g_MapMsg_SelectFlashTimer >> 10) * 3) + 4);
                    }
                    else
                    {
                        Gfx_StringSetColor(StringColorId_White);
                    }

                    Gfx_StringSetPosition(32, (STRING_LINE_OFFSET * i) + 98);
                    Gfx_StringDraw(g_MapOverlayHeader.mapMessages_30[i], MAP_MESSAGE_DISPLAY_ALL_LENGTH);
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
                    if ((u8)g_MapMsg_Select.selectedEntryIdx_1 == i)
                    {
                        Gfx_StringSetColor(((g_MapMsg_SelectFlashTimer >> 10) * 3) + 4);
                    }
                    else
                    {
                        Gfx_StringSetColor(StringColorId_White);
                    }

                    Gfx_StringSetPosition(32, (STRING_LINE_OFFSET * i) + 96);
                    Gfx_StringDraw(g_MapOverlayHeader.mapMessages_30[(mapMsgIdx + i) + 1], MAP_MESSAGE_DISPLAY_ALL_LENGTH);
                }
            }

            if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickUp &&
                (u8)g_MapMsg_Select.selectedEntryIdx_1 != 0)
            {
                g_MapMsg_SelectFlashTimer = Q12(0.0f);
                g_MapMsg_Select.selectedEntryIdx_1--;

                Sd_PlaySfx(Sfx_MenuMove, 0, Q8_CLAMPED(0.25f));
            }

            if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickDown &&
                (u8)g_MapMsg_Select.selectedEntryIdx_1 != (mapMsgCode - 1))
            {
                g_MapMsg_SelectFlashTimer = Q12(0.0f);
                g_MapMsg_Select.selectedEntryIdx_1++;

                Sd_PlaySfx(Sfx_MenuMove, 0, Q8_CLAMPED(0.25f));
            }

            mapMsgCode = NO_VALUE;
            break;

        case MapMsgCode_DisplayAll:
            *arg1 = MAP_MESSAGE_DISPLAY_ALL_LENGTH;
            break;
    }

    return mapMsgCode;
}
