#ifndef _MAPS_CHARACTERS_BLOODSUCKER_H
#define _MAPS_CHARACTERS_BLOODSUCKER_H

/** @brief Bloodsucker character flags. */
typedef enum _BloodsuckerFlags
{
    BloodsuckerFlag_None = 0,
    BloodsuckerFlag_0    = 1 << 0,
    BloodsuckerFlag_1    = 1 << 1
} e_BloodsuckerFlags;

/** @brief Bloodsucker character animation indices. */
typedef enum _BloodsuckerAnim
{
    BloodsuckerAnim_Still = 0,
    BloodsuckerAnim_1     = 1,
    BloodsuckerAnim_2     = 2,
    BloodsuckerAnim_3     = 3,
    BloodsuckerAnim_4     = 4,
    BloodsuckerAnim_5     = 5,
    BloodsuckerAnim_6     = 6,
    BloodsuckerAnim_7     = 7
} e_BloodsuckerAnim;

#endif
