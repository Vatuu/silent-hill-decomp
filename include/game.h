#ifndef GAME_H
#define GAME_H

#include "common.h"

typedef struct {
  /* 0x00 */ u32 *dynamic_overlay;
  /* 0x04 */ u32 *bodyprog_overlay;
} OverlayAddresses;

extern const OverlayAddresses OVERLAY_POINTERS;

#endif
