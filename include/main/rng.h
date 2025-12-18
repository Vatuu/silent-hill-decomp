#ifndef _MAIN_RNG_H
#define _MAIN_RNG_H

#include "common.h"

/** @brief Global variable storing the current random seed for the `Rng_Rand32`
 * function. The value is updated with each call to the RNG functions.
 */
extern u32 g_RngSeed;

/** @brief Tests if a probability is met.
 *
 * Evaluates the probability by performing a bitwise AND
 * operation with a mask that has the specified number of consecutive
 * low bits set to 1.
 *
 * @note
 * Bits | Mask   | Chance     | Percent
 * -----|--------|------------|---------
 * 1    | 0x1    | 1 in 2     | 50%
 * 2    | 0x3    | 1 in 4     | 25%
 * 3    | 0x7    | 1 in 8     | 12.5%
 * 4    | 0xF    | 1 in 16    | 6.25%
 * 5    | 0x1F   | 1 in 32    | 3.125%
 * 6    | 0x3F   | 1 in 64    | 1.563%
 * 7    | 0x7F   | 1 in 128   | 0.781%
 * 8    | 0xFF   | 1 in 256   | 0.391%
 * 9    | 0x1FF  | 1 in 512   | 0.195%
 * 10   | 0x3FF  | 1 in 1024  | 0.098%
 * 11   | 0x7FF  | 1 in 2048  | 0.049%
 * 12   | 0xFFF  | 1 in 4096  | 0.024%
 * 13   | 0x1FFF | 1 in 8192  | 0.012%
 * 14   | 0x3FFF | 1 in 16384 | 0.006%
 * 15   | 0x7FFF | 1 in 32768 | 0.003%
 * 16   | 0xFFFF | 1 in 65536 | 0.002%
 *
 * @param bits Number of consecutive bits to use in the probability test.
 * @return `true` if the probability is met, `false` otherwise.
 */
#define Rng_TestProbabilityBits(bits) \
    (Rng_Rand16() & ((1 << (bits)) - 1))

/** @brief Generates an integer in the range `[low, high]` from a random input.
 *
 * @param rand Random base value.
 * @param low Lower range (inclusive).
 * @param high Upper range (inclusive).
 * @return Random integer in the range `[low, high]` (`s32`).
*/
#define Rng_GenerateIntFromInput(rand, low, high) \
    ((s32)((rand) % (((high) - (low)) + 1)) + (low))

/** @brief Generates an integer in the range `[low, high]` from an unsigned random input.
 *
 * @param rand Random base value.
 * @param low Lower range (inclusive).
 * @param high Upper range (inclusive).
 * @return Random integer in the range `[low, high]` (`s32`).
*/
#define Rng_GenerateUIntFromInput(rand, low, high) \
    ((s32)((u32)(rand) % (((high) - (low)) + 1)) + (low))

/** @brief Shorthand of `Rng_GenerateIntFromInput(Rng_Rand16(), low, high)` .
 *
 * @param low Lower range (inclusive).
 * @param high Upper range (inclusive).
 * @return Random integer in the range `[low, high]` (`s32`).
*/
#define Rng_GenerateInt(low, high) \
    Rng_GenerateIntFromInput(Rng_Rand16(), low, high)

/** @brief Shorthand of `Rng_GenerateUIntFromInput(Rng_Rand16(), low, high)` .
 *
 * @param low Lower range (inclusive).
 * @param high Upper range (inclusive).
 * @return Random integer in the range `[low, high]` (`s32`).
*/
#define Rng_GenerateUInt(low, high) \
    Rng_GenerateUIntFromInput(Rng_Rand16(), low, high)

/** @brief Adds a generated integer in the range `[low, high]` from an unsigned random input to `base`.
 *
 * @hack Needed to fix issue with wrong instruction order when `n + Rng_GenerateUInt(low, high)` is used with non-zero `low` value.
 * More info: https://decomp.me/scratch/UlgCi
 *
 * @param base Base number to be added to.
 * @param low Lower range (inclusive).
 * @param high Upper range (inclusive).
 * @return Random integer in the range `[low, high]` (`s32`).
*/
#define Rng_AddGeneratedUInt(base, low, high) \
    (base + (s32)((u32)Rng_Rand16() % (((high) - (low)) + 1)) + (low))

/** @brief Generates a new random 32-bit unsigned integer and updates
 * `g_RngSeed`.
 *
 * Implements a Linear Congruential Generator (LCG) Random Number
 * Generator (RNG) algorithm, as outlined in "Numerical Recipes" (Second
 * Edition, Chapter 7.1, An Even Quicker Generator). It produces a pseudo-random
 * 32-bit unsigned integer value.
 *
 * @return New pseudo-random 32-bit unsigned integer (`u32`).
 */
u32 Rng_Rand32(void);

/** @brief Generates a new random 16-bit unsigned integer.
 * 
 * Calls `Rng_Rand32` to generate a random number, then
 * shifts the result right to produce a value within the range
 * of `[0, 0x7FFF]`.
 *
 * @return Random positive 16-bit unsigned integer as a 32-bit signed
 * integer (`s32`).
 */
s32 Rng_Rand16(void);

/** @brief Returns the current random seed value.
 *
 * Retrieves and returns the current value of the global variable
 * `g_RngSeed`.
 *
 * @return Current random seed as a 32-bit unsigned integer (`u32`).
 */
u32 Rng_GetSeed(void);

/** @brief Sets the random seed to a specified value.
 *
 * Updates the global variable `g_RngSeed` with the given
 * seed value.
 *
 * @param newSeed New seed value to be set, as a 32-bit unsigned integer
 * (`u32`).
 */
void Rng_SetSeed(u32 newSeed);

/** @brief Generates a new random 12-bit short integer.
 *
 * Calls `Rng_Rand32` to generate a random number, then
 * shifts the result right to produce a value within the range
 * of `0` to `0xFFF` (12-bit).
 *
 * @return Random 12-bit short integer in the range `[0, 0xFFF]`.
 */
u16 Rng_Rand12(void);

#endif
