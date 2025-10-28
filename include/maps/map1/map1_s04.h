#ifndef _MAPS_MAP1_S04_H
#define _MAPS_MAP1_S04_H

#define MAP_ROOM_MIN_X Q12(-160.0f)
#define MAP_ROOM_MAX_X Q12(160.0f)
#define MAP_ROOM_MIN_Z Q12(-80.0f)
#define MAP_ROOM_MAX_Z Q12(200.0f)

extern u16 D_800CD038[][0x28];

extern s32 D_800CD768;

// @hack Added `D_800CD768_tbl` to `lib_externs.ld`, as `D_800CD768_tbl` has to live at same offset as `D_800CD768`.
// Table has to be a separate symbol to get a code match, using `(u16*)D_800CD768` just causes compiler to optimize out parts.
// Not sure what would cause this.
extern u16 D_800CD768_tbl[0];

extern s32 D_800CD76C;
extern s32 D_800CD770;
extern s32 D_800CD774;

extern u8 D_800CCF54;

extern u16 D_800CCF5C[];

void func_800CC8C8(void);

// Some kind of debug menu? Controller buttons increment a counter which wraps around, has a `Gfx_DebugStringPosition` call but no strings drawn.
void func_800CCA2C(void);

// Sound test func that plays different sounds when R1/R2/R3 are pressed?
void func_800CCE38(void);

#endif
