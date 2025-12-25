#ifndef _MAPS_CHARACTERS_SPLITHEAD_H
#define _MAPS_CHARACTERS_SPLITHEAD_H

// TODO: Offical name is actually "Split Head", not "Splithead", which has been used predominantly until now.

/** @brief Splithead character flags. */
typedef enum _SplitheadFlags
{
	SplitheadFlag_None = 0,
	SplitheadFlag_0    = 1 << 0,

	SplitheadFlag_4    = 1 << 4,
	SplitheadFlag_5    = 1 << 5,
	SplitheadFlag_6    = 1 << 6,
	SplitheadFlag_7    = 1 << 7,
	SplitheadFlag_8    = 1 << 8
} e_SplitheadFlags;

#endif
