#ifndef _TEXT_DRAW_H
#define _TEXT_DRAW_H

/** Control codes used by `Gfx_StringDraw`. (TODO: rename to actual purpose, update `Gfx_StringDraw` calls to use them) */
#define STRING_CTRL_07 "\x07"
#define STRING_CTRL_0A "\x0a"

/** Sets the position of the next string to be drawn by `Gfx_StringDraw`. */
void Gfx_StringSetPosition(s32 x, s32 y);

void func_8004A8C0(s32 arg0);

void func_8004A8CC();

/** Sets the color of the next string drawn by `Gfx_StringDraw`. (TODO: add color list) */
void Gfx_StringSetColor(s16 colorId);

/** Draws a string in screen space. */
bool Gfx_StringDraw(char* str, s32 size);

s32 func_8004AF18(char*, s32);

void func_8004B658();

void func_8004B684();

void func_8004B6D4(s16 arg0, s16 arg1);

void func_8004B74C(s16 arg0);

/** Draws string. */
void func_8004B76C(char* str, s32 useFixedWidth);

/** Draws an integer string in screen space. */
void Gfx_StringDrawInt(s32 widthMin, s32 val);

void func_8004BB10();

#endif
