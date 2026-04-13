#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/sound_system.h"
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
    if ((g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                          g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)) ||
        (g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.skip_4))
    {
        hasInput = true;
    }

    g_SysWork.playerWork.player.properties.player.gasWeaponPowerTimer_114 = Q12(0.0f);
    func_8004C564(g_SysWork.playerCombat_38.weaponAttack, WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap));

    if (msgIdx != mapMsgIdx)
    {
        g_SysWork.isMgsStringSet_18 = false;
    }

    switch (g_SysWork.isMgsStringSet_18)
    {
        case false:
            g_SysWork.mapMsgTimer_234C         = NO_VALUE;
            g_MapMsg_Select.maxIdx_0           = NO_VALUE;
            g_MapMsg_Select.selectedEntryIdx_1 = 0;
            g_MapMsg_AudioLoadBlock            = 0;
            g_MapMsg_CurrentIdx                = mapMsgIdx;
            stateMachineIdx0          = 0;
            stateMachineIdx1          = 0;
            msgIdx                   = mapMsgIdx;
            msgDisplayLength             = 0;
            msgDisplayInc                = 2; // Advance 2 glyphs at a time.

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
            g_SysWork.isMgsStringSet_18++;
            return MapMsgState_Finish;

        case true:
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
#if VERSION_REGION_IS(NTSC)
            Gfx_StringSetPosition(40, 160);
#endif

            msgDisplayLength += msgDisplayInc;
            msgDisplayLength  = CLAMP(msgDisplayLength, 0, MAP_MESSAGE_DISPLAY_ALL_LENGTH);

            if (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer_234C > 0)
            {
                g_SysWork.mapMsgTimer_234C -= g_DeltaTimeRaw;
                g_SysWork.mapMsgTimer_234C  = CLAMP(g_SysWork.mapMsgTimer_234C, Q12(0.0f), MSG_TIMER_MAX);
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
                    if (g_MapMsg_Select.maxIdx_0 == temp)
                    {
                        if (!((g_MapMsg_AudioLoadBlock & (1 << 0)) || !hasInput) ||
                            (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer_234C == 0))
                        {
                            stateMachineIdx1 = FINISH_MAP_MSG;

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

                        Sd_PlaySfx(Sfx_MenuCancel, 0, Q8(0.25f));

                        if (g_SysWork.silentYesSelection_2350_4)
                        {
                            g_SysWork.silentYesSelection_2350_4 = false;
                        }

                        stateMachineIdx1 = FINISH_MAP_MSG;
                        break;
                    }
                    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
                    {
                        g_MapMsg_Select.maxIdx_0 = temp;

                        if (g_MapMsg_Select.selectedEntryIdx_1 == (s8)g_MapMsg_SelectCancelIdx)
                        {
                            Sd_PlaySfx(Sfx_MenuCancel, 0, Q8(0.25f));
                        }
                        else if (!g_SysWork.silentYesSelection_2350_4)
                        {
                            Sd_PlaySfx(Sfx_MenuConfirm, 0, Q8(0.25f));
                        }

                        if (g_SysWork.silentYesSelection_2350_4)
                        {
                            g_SysWork.silentYesSelection_2350_4 = false;
                        }

                        stateMachineIdx1 = FINISH_MAP_MSG;
                        break;
                    }
                }
                else if ((!(g_MapMsg_AudioLoadBlock & (1 << 0)) && hasInput && g_MapMsg_Select.maxIdx_0 != 0) ||
                         (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer_234C == 0))
                {
                    if (g_MapMsg_Select.maxIdx_0 != NO_VALUE)
                    {
                        g_MapMsg_Select.maxIdx_0  = NO_VALUE;
                        stateMachineIdx1 = FINISH_MAP_MSG;
                        break;
                    }

                    g_MapMsg_CurrentIdx++;
                    g_SysWork.mapMsgTimer_234C = g_MapMsg_Select.maxIdx_0;

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

    g_SysWork.isMgsStringSet_18            = false;
    g_SysWork.enableHighResGlyphs_2350_0 = false;
    msgDisplayLength               = 0;

    if (g_SysWork.sysFlags_22A0 & SysFlag_5)
    {
        D_800BCD74 = 1;
    }

    return g_MapMsg_Select.selectedEntryIdx_1 + 1;

    #undef MSG_TIMER_MAX
    #undef FINISH_CUTSCENE
    #undef FINISH_MAP_MSG
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
                    if (g_MapMsg_Select.selectedEntryIdx_1 == i)
                    {
                        Gfx_StringSetColor(((g_MapMsg_SelectFlashTimer >> 10) * 3) + 4);
                    }
                    else
                    {
                        Gfx_StringSetColor(StringColorId_White);
                    }

#if VERSION_REGION_IS(NTSC)
                    Gfx_StringSetPosition(32, (STRING_LINE_OFFSET * i) + 98);
                    Gfx_StringDraw(g_MapOverlayHeader.mapMessages_30[i], MAP_MESSAGE_DISPLAY_ALL_LENGTH);
#else
                    Gfx_StringDraw_JP(g_MapOverlayHeader.mapMessages_30[i], i);
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
                    if (g_MapMsg_Select.selectedEntryIdx_1 == i)
                    {
                        Gfx_StringSetColor(((g_MapMsg_SelectFlashTimer >> 10) * 3) + 4);
                    }
                    else
                    {
                        Gfx_StringSetColor(StringColorId_White);
                    }

#if VERSION_REGION_IS(NTSC)
                    Gfx_StringSetPosition(32, (STRING_LINE_OFFSET * i) + 96);
                    Gfx_StringDraw(g_MapOverlayHeader.mapMessages_30[(mapMsgIdx + i) + 1], MAP_MESSAGE_DISPLAY_ALL_LENGTH);
#else
                    Gfx_StringDraw_JP(g_MapOverlayHeader.mapMessages_30[(mapMsgIdx + i) + 1], i);
#endif
                }
            }

            if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickUp &&
                g_MapMsg_Select.selectedEntryIdx_1 != 0)
            {
                g_MapMsg_SelectFlashTimer = Q12(0.0f);
                g_MapMsg_Select.selectedEntryIdx_1--;

                Sd_PlaySfx(Sfx_MenuMove, 0, Q8(0.25f));
            }

            if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickDown &&
                g_MapMsg_Select.selectedEntryIdx_1 != (mapMsgCode - 1))
            {
                g_MapMsg_SelectFlashTimer = Q12(0.0f);
                g_MapMsg_Select.selectedEntryIdx_1++;

                Sd_PlaySfx(Sfx_MenuMove, 0, Q8(0.25f));
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

void func_80036E48(u16* arg0, s16* arg1) // 0x80036E48
{
    u16  sp10[4];
    u8   sp18[16];
    u8   sp28[12];
    s32  temp_a0;
    s32  temp_v0_2;
    s32  var_a2;
    s32  i;
    u8   var_t4;
    s32  var_v0;
    u16  temp_v0;
    u16  var_a3;
    s16* var_t2;
    u16* var_t7;

    var_t2 = arg1;
    var_t4 = 0;
    var_t7 = arg0;

    for (i = 0; i < 15;)
    {
        temp_v0 = *var_t7;

        for (var_a2 = 0; var_a2 < 15; var_a2++)
        {
            if ((((temp_v0 >> 8) | ((temp_v0 & 0xFF) << 8)) >> (0xF - var_a2)) & 1)
            {
                sp18[var_a2] = 1;
            }
            else
            {
                sp18[var_a2] = 0;
            }
        }

        sp18[15] = 0;
        sp28[0]  = sp18[0];
        sp28[1]  = sp18[1] | sp18[2];
        sp28[2]  = sp18[3];
        sp28[3]  = sp18[4];
        sp28[4]  = sp18[5] | sp18[6];
        sp28[5]  = sp18[7];
        sp28[6]  = sp18[8] | sp18[9];
        sp28[7]  = sp18[10];
        sp28[8]  = sp18[11];
        sp28[9]  = sp18[12] | sp18[13];
        var_v0   = 2;
        sp28[10] = sp18[14];
        sp28[11] = 0;

        for (var_a3 = 0, var_a2 = 0; var_a2 < 12; var_a2++)
        {
            var_v0  = 2;
            temp_a0 = (var_a2 & 0x3) * 4;

            if (sp28[var_a2] != 0)
            {
                var_a3 |= var_v0 << temp_a0;
            }
            else
            {
                if (var_a2 > 0 && sp28[var_a2 - 1] != 0)
                {
                    var_a3 |= 11 << temp_a0;
                }

                if (i > 0)
                {
                    if (var_a2 != 0 && ((sp10[var_a2 >> 2] >> temp_a0) & 0xF) == 11 && var_t4)
                    {
                        var_a3 |= 11 << temp_a0;
                    }

                    temp_v0_2 = (sp10[var_a2 >> 2] >> temp_a0) & 0xF;

                    if (temp_v0_2 > 0 && temp_v0_2 != 11)
                    {
                        var_a3 |= 11 << temp_a0;
                        var_t4 = 1;
                    }
                    else
                    {
                        var_t4 = 0;
                    }
                }
            }

            if ((var_a2 & 3) == 3)
            {
                sp10[var_a2 >> 2] = var_a3;
                *var_t2           = var_a3;
                var_t2++;
                var_a3 = 0;
            }
        }

        do { i++; } while (0); // @hack Required for match.

        var_t7++;
        var_t2 += (D_800C3920 - 1) * 3;
    }

    func_8003708C(var_t2, sp10);
}

void func_8003708C(s16* ptr0, u16* ptr1) // 0x8003708C
{
    s32 var0;
    s16 var1;
    s32 var3;
    s32 shift;
    s32 i;

    var0 = 0;
    var1 = 0;

    for (i = 0; i < 12; i++)
    {
        shift = (i & 0x3) * 4;
        var3  = (*ptr1 >> shift) & 0xF;
        if (i != 0 && var3 == 11 && var0 != 0)
        {
            var1 |= 11 << shift;
        }

        var0 = 0;
        if (var3 != 0 && var3 != 11)
        {
            var1 |= 11 << shift;
            var0  = 1;
        }

        if ((i & 0x3) == 3 || i == 12)
        {
            ptr1++;
            *ptr0++ = var1;
            var1    = 0;
        }
    }
}

void func_80037124(void) // 0x80037124
{
    g_MapMsg_Select.maxIdx_0 = NO_VALUE;
    func_8003652C();
    DrawSync(SyncMode_Wait);
}
