#include "main/mem.h"

void memmove32(u32 *dest, u32 *src, s32 numbytes) {
  u32 *end;
  s32 numwords;

  if (dest == src) {
    return;
  }

  numwords = numbytes >> 2;

  if (dest < src) {
    end = src + numwords;

    while (src < end) {
      *dest++ = *src++;
    }
  } else {
    end = src;

    dest += numwords;
    src += numwords;

    while (src > end) {
      *(--dest) = *(--src);
    }
  }
}
