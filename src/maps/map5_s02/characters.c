#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/map5/map5_s02.h"
#include "maps/particle.h"
#include "maps/characters/player.h"
#include "maps/characters/stalker.h"

// player.c and stalker.c must stay in the same TU because they share an
// identical VECTOR3 compound literal that the compiler deduplicates into
// a single rodata entry. Splitting them into separate TUs produces two 
// copies, inflating rodata by 0x10 bytes.
//
// Could indicate that characters weren't built as separate .c files,
// but a single .c that would include the code for them as needed.
// (maybe a characters.c that had every character and conditionally included them based on what map needed?)
// 
// map5_s02 is currently the only map where this deduplication has been observed.
// Other maps use separate per-character splits for now, as proper splits make handling
// version differences easier. 
#include "../src/maps/characters/player.c"

#include "../src/maps/characters/stalker.c" // 0x800CDC08
