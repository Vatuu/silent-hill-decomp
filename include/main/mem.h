#ifndef _MEM_H
#define _MEM_H

#include "common.h"

/**
 * @brief Custom implementation of `memmove` that copies word-by-word.
 *
 * This function copies a specified number of bytes from the source
 * memory location to the destination memory location.
 * Copies word-by-word instead of byte-by-byte. Beware of unaligned access?
 *
 * @param dest Destination pointer where the content is to be copied.
 * @param src Source pointer from where the content is to be copied.
 * @param byteCount Number of bytes (not words) to copy.
 */
void memmove32(u32* dest, u32* src, s32 byteCount);

#endif
