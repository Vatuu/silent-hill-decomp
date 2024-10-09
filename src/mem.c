#include "mem.h"

void memmove(u32 *dest, u32 *src, s32 bytes_num) {
  u32 *end;
  s32  words_num;

  if (dest == src) {
    return;
  }

  words_num = bytes_num >> 2;

  if (dest < src) {
    end = src + words_num;

    while (src < end) {
      *dest++ = *src++;
    }
  } else {
    end = src;

    dest += words_num;
    src += words_num;

    while (src > end) {
      *(--dest) = *(--src);
    }
  }
}
