#include "common.h"

/** NOTE: `memcpy` may rely on hand-tuned or inline assembly.
 * Some have gotten close to matching but still haven't gotten it completely matched.
 * Matching it precisely isn't really a priority, since this would likely just be replaced down the line.
 * Closest scratches: https://decomp.me/scratch/4t6xS / https://decomp.me/scratch/NycrP / https://decomp.me/scratch/kHnqu
 */
INCLUDE_ASM("asm/main/nonmatchings/memcpy", memcpy);

void nullsub_800120b0(void) {}
