#ifndef _BODYPROG_SYS_JOY_H
#define _BODYPROG_SYS_JOY_H

#include "bodyprog/math/math.h"

/** @brief Handles the general controller
 * handling, controller IO stream and state.
 * Game controller logic seems to have been split among many parts of
 * the game depending on the state or screen the player is using.
 * For example, the controller logic for the inventory screen is handled separately from the
 * one for the in-game state.
 */

#define INPUT_ACTION_COUNT   14
#define CONTROLLER_COUNT_MAX 2
#define STICK_THRESHOLD      FP_STICK(0.5f)

typedef enum _ControllerFlags
{
    ControllerFlag_None         = 0,
    ControllerFlag_Select       = 1 << 0,
    ControllerFlag_L3           = 1 << 1,
    ControllerFlag_R3           = 1 << 2,
    ControllerFlag_Start        = 1 << 3,
    ControllerFlag_DpadUp       = 1 << 4,
    ControllerFlag_DpadRight    = 1 << 5,
    ControllerFlag_DpadDown     = 1 << 6,
    ControllerFlag_DpadLeft     = 1 << 7,
    ControllerFlag_L2           = 1 << 8,
    ControllerFlag_R2           = 1 << 9,
    ControllerFlag_L1           = 1 << 10,
    ControllerFlag_R1           = 1 << 11,
    ControllerFlag_Triangle     = 1 << 12,
    ControllerFlag_Circle       = 1 << 13,
    ControllerFlag_Cross        = 1 << 14,
    ControllerFlag_Square       = 1 << 15,
    ControllerFlag_LStickUp2    = 1 << 16,
    ControllerFlag_LStickRight2 = 1 << 17,
    ControllerFlag_LStickDown2  = 1 << 18,
    ControllerFlag_LStickLeft2  = 1 << 19,
    ControllerFlag_RStickUp     = 1 << 20,
    ControllerFlag_RStickRight  = 1 << 21,
    ControllerFlag_RStickDown   = 1 << 22,
    ControllerFlag_RStickLeft   = 1 << 23,
    ControllerFlag_LStickUp     = 1 << 24,
    ControllerFlag_LStickRight  = 1 << 25,
    ControllerFlag_LStickDown   = 1 << 26,
    ControllerFlag_LStickLeft   = 1 << 27
} e_ControllerFlags;

typedef union
{
    /* 0x0 */ u32 rawData_0;
              struct
              {
                  s8 rightX;
                  s8 rightY;
                  s8 leftX;
                  s8 leftY;
    /* 0x4 */ } sticks_0; // Normalized range: `[-128, 127]`.
} s_AnalogSticks;

typedef struct _AnalogController
{
    u8  status;
    u8  received_bytes : 4; /** Number of bytes received / 2. */
    u8  terminal_type  : 4; /** `e_PadTerminalType` */
    u16 digitalButtons;
    u8  rightX;
    u8  rightY;
    u8  leftX;
    u8  leftY;
} s_AnalogController;
STATIC_ASSERT_SIZEOF(s_AnalogController, 8);

typedef struct _ControllerData
{
    /* 0x0  */ s_AnalogController analogController_0;
    /* 0x8  */ s32                pulseTicks_8;
    /* 0xC  */ e_ControllerFlags  btnsHeld_C;
    /* 0x10 */ e_ControllerFlags  btnsClicked_10;
    /* 0x14 */ e_ControllerFlags  btnsReleased_14;
    /* 0x18 */ e_ControllerFlags  btnsPulsed_18;
    /* 0x1C */ e_ControllerFlags  btnsPulsedGui_1C;
    /* 0x20 */ s_AnalogSticks     sticks_20;
    /* 0x24 */ s_AnalogSticks     sticks_24;
    /* 0x28 */ s32                field_28;
} s_ControllerData;
STATIC_ASSERT_SIZEOF(s_ControllerData, 44);

/** @brief Controller key bindings for input actions. Contains bitfield of button presses assigned to each action.
 *
 * Bitfields only contain buttons. Analog directions and D-Pad aren't included.
 */
typedef struct _ControllerConfig
{
    /* 0x0  */ u16 enter;
    /* 0x2  */ u16 cancel;
    /* 0x4  */ u16 skip;
    /* 0x6  */ u16 action;
    /* 0x8  */ u16 aim;
    /* 0xA  */ u16 light;
    /* 0xC  */ u16 run;
    /* 0xE  */ u16 view;
    /* 0x10 */ u16 stepLeft;
    /* 0x12 */ u16 stepRight;
    /* 0x14 */ u16 pause;
    /* 0x16 */ u16 item;
    /* 0x18 */ u16 map;
    /* 0x1A */ u16 option;
} s_ControllerConfig;
STATIC_ASSERT_SIZEOF(s_ControllerConfig, 28);

extern s_ControllerData* const g_Controller0;
extern s_ControllerData* const g_Controller1;

// ==========
// FUNCTIONS
// ==========

void Joy_Init(void);

void Joy_ReadP1(void);

void Joy_Update(void);

void Joy_ControllerDataUpdate(void);

void ControllerData_AnalogToDigital(s_ControllerData* cont, bool arg1);

/** @brief @unused */
bool func_8003483C(u16* arg0);

#endif
