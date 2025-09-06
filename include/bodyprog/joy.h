#ifndef _JOY_H
#define _JOY_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the controller handling.
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
