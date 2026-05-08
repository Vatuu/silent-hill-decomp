#ifndef _COLLISION_H
#define _COLLISION_H

// Related to collision?
typedef struct
{
    /* 0x0 */ u16            flags; /** `e_CollisionFlags` */
    /* 0x2 */ u8             triggerZoneCount;
    /* 0x3 */ u8             __pad_3;
    /* 0x4 */ s_TriggerZone* triggerZones[20]; // Guessed size.
} s_800C4478;

// emoose: Also works: `extern u16 D_800C4478[];`, `arg0->field_4 = D_800C4478[0];`.
// Didn't see any array accesses in Ghidra though, struct might be more likely.
extern s_800C4478 D_800C4478;

#endif
