#ifndef _JOY_H
#define _JOY_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to general controller handling.
 *
 * To avoid confusion, this only covers the general controller
 * handling, controller IO stream and state.
 * Game controller logic seems to have been split among many parts of
 * the game depending on the state or screen the player is using.
 * For example, the controller logic for the inventory screen is handled apart from the
 * one for the in-game state.
 */

// ==========
// FUNCTIONS
// ==========

void Joy_Init();

void Joy_ReadP1();

void Joy_Update();

void Joy_ControllerDataUpdate();

void ControllerData_AnalogToDigital(s_ControllerData* cont, s32 arg1);

/** @brief @unused */
bool func_8003483C(u16* arg0);

void func_800348C0();

#endif
