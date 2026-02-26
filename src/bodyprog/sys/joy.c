#include "game.h"

#include <psyq/libpad.h>

#include "bodyprog/joy.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/math/math.h"

void Joy_Init(void) // 0x8003441C
{
    PadInitDirect(&g_GameWork.rawController_5B4, g_Controller1);
    PadStartCom();
}

void Joy_ReadP1(void) // 0x80034450
{
    s_ControllerData* cont;

    cont = &g_GameWork.controllers_38[0];

    // NOTE: `memcpy` is close, reads `rawController_5B4` as two `s32`s, but doesn't give match.
    // memcpy(&cont->analogController_0, &g_GameWork.rawController_5B4, sizeof(s_AnalogController));

    *(s32*)&cont->analogController_0        = *(s32*)&g_GameWork.rawController_5B4;
    *(s32*)&cont->analogController_0.rightX = *(s32*)&g_GameWork.rawController_5B4.rightX;

    // Alternate
    // ((s32*)&cont->analogController_0)[0] = ((s32*)&g_GameWork.rawController_5B4)[0];
    // ((s32*)&cont->analogController_0)[1] = ((s32*)&g_GameWork.rawController_5B4)[1];
}

void Joy_Update(void) // 0x8003446C
{
    Joy_ReadP1();
    Joy_ControllerDataUpdate();
}

void Joy_ControllerDataUpdate(void) // 0x80034494
{
    #define CONTROLLER_COUNT             2
    #define PULSE_INITIAL_INTERVAL_TICKS (TICKS_PER_SECOND / 2)
    #define PULSE_INTERVAL_TICKS         (PULSE_INITIAL_INTERVAL_TICKS / 10)

    s_ControllerData* cont;
    s32               i;
    s32               prevBtnsHeld;
    s32               pulseTicks;
    s32               btnsPulsed;

    // Update controller button flags.
    for (i = CONTROLLER_COUNT, cont = g_Controller0; i > 0; i--, cont++)
    {
        prevBtnsHeld = cont->btnsHeld_C;

        // Update held button flags.
        if (cont->analogController_0.status == 0xFF)
        {
            cont->btnsHeld_C = ControllerFlag_None;
        }
        else
        {
            cont->btnsHeld_C = ~cont->analogController_0.digitalButtons & 0xFFFF;
        }

        // TODO: Demagic hex values.
        ControllerData_AnalogToDigital(cont, (*(u16*)&cont->analogController_0.status & 0x5300) == 0x5300);

        // Directional held flag sanitation? TODO: Find out what it's doing.
        cont->btnsHeld_C = cont->btnsHeld_C | (((cont->btnsHeld_C << 20) | (cont->btnsHeld_C << 8)) &
                                                (ControllerFlag_LStickUp | ControllerFlag_LStickRight | ControllerFlag_LStickDown | ControllerFlag_LStickLeft));

        // Clear up/down held flags if concurrent.
        if ((cont->btnsHeld_C & (ControllerFlag_LStickUp | ControllerFlag_LStickDown)) == (ControllerFlag_LStickUp | ControllerFlag_LStickDown))
        {
            cont->btnsHeld_C &= ~(ControllerFlag_LStickUp | ControllerFlag_LStickDown);
        }

        // Clear left/right held flags if concurrent.
        if ((cont->btnsHeld_C & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft)) == (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
        {
            cont->btnsHeld_C = cont->btnsHeld_C & ~(ControllerFlag_LStickRight | ControllerFlag_LStickLeft);
        }

        // Update clicked and released button flags.
        cont->btnsClicked_10  = ~prevBtnsHeld & cont->btnsHeld_C;
        cont->btnsReleased_14 =  prevBtnsHeld & ~cont->btnsHeld_C;

        // Update pulse ticks.
        pulseTicks = cont->pulseTicks_8;
        if (cont->btnsHeld_C != prevBtnsHeld)
        {
            pulseTicks = 0;
        }
        else
        {
            pulseTicks += g_VBlanks;
        }

        // Update pulsed button flags.
        if (pulseTicks >= PULSE_INITIAL_INTERVAL_TICKS)
        {
            cont->btnsPulsed_18 = cont->btnsHeld_C;
            pulseTicks          = PULSE_INITIAL_INTERVAL_TICKS - PULSE_INTERVAL_TICKS;
        }
        else
        {
            cont->btnsPulsed_18 = cont->btnsClicked_10;
        }

        btnsPulsed             = cont->btnsPulsed_18;
        cont->pulseTicks_8     = pulseTicks;
        cont->btnsPulsedGui_1C = btnsPulsed;

        // Clear left/right pulse flags if concurrent.
        if ((btnsPulsed & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft)) == (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
        {
            cont->btnsPulsedGui_1C &= ~(ControllerFlag_LStickRight | ControllerFlag_LStickLeft);
        }

        // Clear up/down pulse flags if concurrent.
        if ((cont->btnsPulsedGui_1C & (ControllerFlag_LStickUp | ControllerFlag_LStickDown)) == (ControllerFlag_LStickUp | ControllerFlag_LStickDown))
        {
            cont->btnsPulsedGui_1C &= ~(ControllerFlag_LStickUp | ControllerFlag_LStickDown);
        }

        // Clear left/right pulse flags if up/down is concurrent.
        if ((cont->btnsPulsedGui_1C & (ControllerFlag_LStickUp | ControllerFlag_LStickDown)))
        {
            cont->btnsPulsedGui_1C &= ~(ControllerFlag_LStickRight | ControllerFlag_LStickLeft);
        }
    }
}

void ControllerData_AnalogToDigital(s_ControllerData* cont, bool arg1) // 0x80034670
{
    s32 val;
    s32 axisIdx;
    s32 processedInputFlags;
    s32 normalizedAnalogData;
    s32 xorShiftedRawAnalog;
    s32 btnsHeld;
    s32 signedRawAnalog;
    s32 negativeDirBitIdx;
    s32 positiveDirBitIdx;

    btnsHeld = cont->btnsHeld_C;

    if (arg1)
    {
        signedRawAnalog     = *(u32*)&cont->analogController_0.rightX ^ 0x80808080;
        xorShiftedRawAnalog = signedRawAnalog;

        for (normalizedAnalogData = 0, axisIdx = 3;
             axisIdx >= 0;
             axisIdx--)
        {
            normalizedAnalogData <<= 8;
            val                    = xorShiftedRawAnalog >> 24;
            xorShiftedRawAnalog  <<= 8;

            if (val < -STICK_THRESHOLD)
            {
                normalizedAnalogData |= (val + STICK_THRESHOLD) & 0xFF;
                negativeDirBitIdx     = 23 - (axisIdx & (1 << 0));
                btnsHeld             |= 1 << (negativeDirBitIdx - (axisIdx * 2));
            }
            else if (val >= STICK_THRESHOLD)
            {
                normalizedAnalogData |= (val - (STICK_THRESHOLD - 1)) & 0xFF;
                positiveDirBitIdx     = (axisIdx & 0x1) + 21;
                btnsHeld             |= 1 << (positiveDirBitIdx - ((axisIdx >> 1) * 4));
            }
        }

        cont->btnsHeld_C = btnsHeld;
    }
    else
    {
        signedRawAnalog      = 0;
        normalizedAnalogData = 0;
    }

    processedInputFlags       = normalizedAnalogData;
    cont->sticks_20.rawData_0 = signedRawAnalog;

    // TODO: Demagic hex values. Analog stick or button flags?
    if (cont == g_Controller0)
    {
        if (!(processedInputFlags & 0xFF000000))
        {
            val = btnsHeld & 0x50;
            if (val == 0x40)
            {
                normalizedAnalogData = processedInputFlags | 0x2D000000;
            }
            else if (val == 0x10)
            {
                normalizedAnalogData = processedInputFlags | 0xD3000000;
            }
        }
        if (!(normalizedAnalogData & 0xFF0000))
        {
            val = btnsHeld & 0xA0;
            if (val == 0x20)
            {
                normalizedAnalogData |= 0x2D0000;
            }
            else if (val == 0x80)
            {
                normalizedAnalogData |= 0xD30000;
            }
        }
        if (!(processedInputFlags & 0xFF000000))
        {
            val = btnsHeld & 0x50;
            if (val == 0x40)
            {
                processedInputFlags |= 0x20000000;
            }
            else if (val == 0x10)
            {
                if (!(btnsHeld & g_GameWorkPtr->config_0.controllerConfig_0.run_C))
                {
                    processedInputFlags |= 0xE0000000;
                }
                else
                {
                    processedInputFlags |= 0xC0000000;
                }
            }
        }
        if (!(processedInputFlags & 0xFF0000))
        {
            val = btnsHeld & 0xA0;
            if (val == 0x20)
            {
                processedInputFlags |= 0x200000;
            }
            else if (val == 0x80)
            {
                processedInputFlags |= 0xE00000;
            }
        }
    }

    cont->sticks_24.rawData_0 = normalizedAnalogData;
    cont->field_28 = processedInputFlags;
}

bool func_8003483C(u16* arg0) // 0x8003483C
{
    if (g_Controller0->btnsClicked_10 & *(*arg0 + arg0))
    {
        *arg0 = *arg0 + 1;
    }
    else if (g_Controller0->btnsClicked_10 & (*(arg0 + 1)))
    {
        *arg0 = 2;
    }
    else if (g_Controller0->btnsClicked_10 & 0xFFFF)
    {
        *arg0 = 1;
    }

    if (*(*arg0 + arg0) == 0xFFFF)
    {
        *arg0 = 1;
        return true;
    }
    else
    {
        return false;
    }
}
