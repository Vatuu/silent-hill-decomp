#ifndef _MAPS_CHARACTERS_CREEPER_H
#define _MAPS_CHARACTERS_CREEPER_H

/** @brief Creeper character flags. */
typedef enum _CreeperFlags
{
    CreeperFlag_0       = 1 << 0,
    CreeperFlag_1       = 1 << 1,
    CreeperFlag_2       = 1 << 2,
    CreeperFlag_3       = 1 << 3,
    CreeperFlag_4       = 1 << 4,
    CreeperFlag_5       = 1 << 5, // Target player position updated?
    CreeperFlag_6       = 1 << 6,
    CreeperFlag_7       = 1 << 7,
    CreeperFlag_Alerted = 1 << 8
} e_CreeperFlags;

/** @brief Creeper character animation indices. */
typedef enum _CreeperAnim
{
    CreeperAnim_Still = 0,

    CreeperAnim_2     = 2,
    CreeperAnim_3     = 3,
    CreeperAnim_4     = 4,
    CreeperAnim_5     = 5,

    CreeperAnim_7     = 7,
    CreeperAnim_8     = 8,
    CreeperAnim_9     = 9,

    CreeperAnim_11    = 11,
    CreeperAnim_12    = 12,
    CreeperAnim_13    = 13,
    CreeperAnim_14    = 14,
    CreeperAnim_15    = 15,
    CreeperAnim_16    = 16,
    CreeperAnim_17    = 17
} e_CreeperAnim;

#endif
