#ifndef MEM_H
#define MEM_H

#include "common.h"

/**
 * @brief Custom implementation of memmove for 32-bit unsigned integers.
 *
 * This function copies a specified number of bytes from the source
 * memory location to the destination memory location.
 *
 * @param dest Destination pointer where the content is to be copied.
 * @param src Source pointer from where the content is to be copied.
 * @param bytes_num Number of bytes (not words) to copy.
 */
void memmove(u32 *dest, u32 *src, s32 bytes_num);

#endif
