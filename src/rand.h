#ifndef RAND_H
#define RAND_H

#include "common.h"

/**
 * @brief Global variable storing the current random seed for the `ranqd1`
 * function. The value is updated with each call to the RNG functions.
 */
extern u32 g_rand_seed;

/**
 * @brief Generates a new random 32-bit unsigned integer and updates the
 * `g_rand_seed`.
 *
 * This function implements a Linear Congruential Generator (LCG) Random Number
 * Generator (RNG) algorithm, as outlined in "Numerical Recipes" (Second
 * Edition, Chapter 7.1, An Even Quicker Generator). It produces a pseudo-random
 * 32-bit unsigned integer value.
 *
 * @return A new pseudo-random 32-bit unsigned integer (u32).
 */
u32 ranqd1();

/**
 * @brief Generates a new random positive 16-bit short integer.
 * 
 * This function calls `ranqd1` to generate a random number, then
 * shifts the result right to produce a value within the range
 * of 0 to 0x7FFF (16-bit - sign).
 *
 * @return A random positive 16-bit short integer (0 to 0x7FFF).
 */
s16 getPositive16BitRandomNumber();

/**
 * @brief Returns the current random seed value.
 *
 * This function retrieves and returns the current value of the global variable
 * `g_rand_seed`.
 *
 * @return The current random seed as a 32-bit unsigned integer (u32).
 */
u32 getRandomSeed();

/**
 * @brief Sets the random seed to a specified value.
 *
 * This function updates the global variable `g_rand_seed` with the given
 * seed value.
 *
 * @param next_seed The new seed value to be set, as a 32-bit unsigned integer
 * (u32).
 */
void setRandomSeed(u32 next_seed);

/**
 * @brief Generates a new random 12-bit short integer.
 *
 * This function calls `ranqd1` to generate a random number, then
 * shifts the result right to produce a value within the range
 * of 0 to 0xFFF (12-bit).
 *
 * @return A random 12-bit short integer (0 to 0xFFF).
 */
u16 get12BitRandomNumber();

#endif
