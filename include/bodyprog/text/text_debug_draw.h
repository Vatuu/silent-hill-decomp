#ifndef _BODYPROG_TEXT_DEBUGDRAW_H
#define _BODYPROG_TEXT_DEBUGDRAW_H

/** @brief Sets the position for the next text to be drawn.
 *
 * @param x X position for the text.
 * @param y Y position for the text.
 */
void Text_Debug_PositionSet(s16 x, s16 y);

/** @brief Draws debug strings using 8x8 glyphs from `FONT8.TIM`.
 *
 * Valid `char` range: `[42, 95]` (`*` to `_`).
 *
 * @param str Pointer to the string to be drawn.
 */
void Text_Debug_Draw(char* str);

/** @brief Converts an integer to a string, written backwards into scratchpad memory.
 *
 * Handles negative values. Pads with `'\v'` (blank character in debug font) on the left
 * to meet the minimum width.
 *
 * @param widthMin Minimum character width of the output. Padded with blanks if needed.
 * @param val The integer value to convert (must be converted from q19_12 before calling).
 * @return Pointer to the formatted string in scratchpad memory.
 */
char* Text_Debug_IntToString(s32 widthMin, s32 val);

#if VERSION_EQUAL_OR_OLDER(PROTO_981216)
/** @brief Prints a Q19.12 fixed-point value to the screen with a specified number of decimal places.
 *
 * Converts the fixed-point value to an integer with extra precision, then passes it to
 * `Text_Debug_DrawDecimal` with rounding enabled.
 *
 * @param offsetX Character offset for the integer portion. Adjusted internally for the decimal point and fractional digits.
 * @param fracDigits Number of digits to display after the decimal point.
 * @param val The Q19.12 fixed-point value to print.
 */
void Text_Debug_DrawQ12(s32 offsetX, s32 fracDigits, q19_12 val);
#endif

/** @brief Formats an integer as a debug text string with optional decimal point and rounding.
 *
 * Writes the formatted string backwards into scratchpad memory and adjusts
 * `g_Text_Debug_PositionSet1` cursor position. Handles negative values.
 *
 * @param fieldWidth Total character width for the formatted number.
 * @param fracDigits Number of digits after the decimal point. 0 for no decimal point.
 * @param value The integer value to format (must be converted from q19_12 before calling).
 * @param round If `true`, rounds the value by `(value + 5) / 10` before formatting.
 */
void Text_Debug_DrawDecimal(s32 fieldWidth, s32 fracDigits, s32 value, bool round);

#endif
