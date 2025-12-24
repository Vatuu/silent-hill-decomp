#ifndef _MAPS_CHARACTERS_CREAPER_H
#define _MAPS_CHARACTERS_CREAPER_H

/** @brief Creaper character flags. */
typedef enum _CreaperFlags
{
	CreaperFlag_0 = 1 << 0,

	CreaperFlag_2 = 1 << 2,
	CreaperFlag_3 = 1 << 3,
	CreaperFlag_4 = 1 << 4,
	CreaperFlag_5 = 1 << 5,
	CreaperFlag_6 = 1 << 6,
	CreaperFlag_7 = 1 << 7,
	CreaperFlag_8 = 1 << 8
} e_CreaperFlags;

/** @brief Creaper character animation indices. */
typedef enum _CreaperAnim
{
	CreaperAnim_Still = 0,

	CreaperAnim_2     = 2,
	CreaperAnim_3     = 3,
	CreaperAnim_4     = 4,
	CreaperAnim_5     = 5,

	CreaperAnim_7     = 7,

	CreaperAnim_11    = 11,
	CreaperAnim_12    = 12,
	CreaperAnim_13    = 13,
	CreaperAnim_14    = 14,
	CreaperAnim_15    = 15
} e_CreaperAnim;

#endif
