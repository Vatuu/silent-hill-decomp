#ifndef _MAIN_MEM_H
#define _MAIN_MEM_H

#include "common.h"

/** @brief Custom implementation of `memmove` that copies word-by-word.
 *
 * Copies a specified number of bytes from the source
 * memory location to the destination memory location.
 * Copies word-by-word instead of byte-by-byte. Beware of unaligned access?
 *
 * @param dest Destination pointer to where the content is to be copied.
 * @param src Source pointer from where the content is to be copied.
 * @param byteCount Number of bytes (not words) to copy.
 */
void Mem_Move32(u32* dest, u32* src, s32 byteCount);

#endif
