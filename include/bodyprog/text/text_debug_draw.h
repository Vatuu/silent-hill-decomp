#ifndef _BODYPROG_TEXT_DEBUGDRAW_H
#define _BODYPROG_TEXT_DEBUGDRAW_H

// ==========
// FUNCTIONS
// ==========

void Text_Debug_PositionSet(s16 x, s16 y);

/** Draws debug strings using 8x8 glyphs from `FONT8.TIM`. Valid `char` range: `[42, 95]` (`*` to `_`). */
void Text_Debug_Draw(char* str);

char* Text_Debug_IntToString(s32 widthMin, s32 val);

#if VERSION_EQUAL_OR_OLDER(PROTO_981216)
void Text_Debug_DecToStringConversion(s32 offsetX, s32 fracDigits, q19_12 val);
#endif

void func_800321EC(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

#endif
