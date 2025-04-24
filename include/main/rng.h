#ifndef _RNG_H
#define _RNG_H

#include "common.h"

/** @brief Tests if a probability is met.
 *
 * This macro evaluates the probability by performing a bitwise AND
 * operation with a mask that has the specified number of bits set to 1.
 *
 * Bits | Chance  | Mask
 * -----|---------|------
 * 1    | 50%     | 0x1
 * 2    | 25%     | 0x3
 * 3    | 12.5%   | 0x7
 * 4    | 6.25%   | 0xF
 * 5    | 3.125%  | 0x1F
 * 6    | 1.563%  | 0x3F
 * 7    | 0.781%  | 0x7F
 * 8    | 0.391%  | 0xFF
 * 9    | 0.195%  | 0x1FF
 * 10   | 0.098%  | 0x3FF
 * 11   | 0.049%  | 0x7FF
 * 12   | 0.024%  | 0xFFF
 * 13   | 0.012%  | 0x1FFF
 * 14   | 0.006%  | 0x3FFF
 * 15   | 0.003%  | 0x7FFF
 * 16   | 0.002%  | 0xFFFF
 */
#define TEST_RNG(bits) \
    (Rng_Rand16() & ((1 << (bits)) - 1))

/** @brief Global variable storing the current random seed for the `Rng_Rand32`
 * function. The value is updated with each call to the RNG functions.
 */
extern u32 g_RngSeed;

/** @brief Generates a new random 32-bit unsigned integer and updates
 * `g_RngSeed`.
 *
 * This function implements a Linear Congruential Generator (LCG) Random Number
 * Generator (RNG) algorithm, as outlined in "Numerical Recipes" (Second
 * Edition, Chapter 7.1, An Even Quicker Generator). It produces a pseudo-random
 * 32-bit unsigned integer value.
 *
 * @return A new pseudo-random 32-bit unsigned integer (u32).
 */
u32 Rng_Rand32();

/** @brief Generates a new random 16-bit unsigned integer.
 * 
 * This function calls `Rng_Rand32` to generate a random number, then
 * shifts the result right to produce a value within the range
 * of [0, 0x7FFF].
 *
 * @return A random positive 16-bit unsigned integer as a 32-bit unsigned
 * integer (u32).
 */
u32 Rng_Rand16();

/** @brief Returns the current random seed value.
 *
 * This function retrieves and returns the current value of the global variable
 * `g_RngSeed`.
 *
 * @return The current random seed as a 32-bit unsigned integer (u32).
 */
u32 Rng_GetSeed();

/** @brief Sets the random seed to a specified value.
 *
 * This function updates the global variable `g_RngSeed` with the given
 * seed value.
 *
 * @param newSeed The new seed value to be set, as a 32-bit unsigned integer
 * (u32).
 */
void Rng_SetSeed(u32 newSeed);

/** @brief Generates a new random 12-bit short integer.
 *
 * This function calls `Rng_Rand32` to generate a random number, then
 * shifts the result right to produce a value within the range
 * of 0 to 0xFFF (12-bit).
 *
 * @return A random 12-bit short integer (0 to 0xFFF).
 */
u16 Rng_Rand12();

#endif
