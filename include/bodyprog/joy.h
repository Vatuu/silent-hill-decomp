#ifndef _JOY_H
#define _JOY_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the general controller handling.
 *
 * For avoiding confusion, this only covers the general controller
 * handling, the game dectecting controller IO stream and state,
 * game controller logic seems to have been split among many parts of
 * the game depending on the state or screen the player is, for example:
 * the controller logic for the inventory screen is handled apart from the
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

void func_800348C0();

#endif
