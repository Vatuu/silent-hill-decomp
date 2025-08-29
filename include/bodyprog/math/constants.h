#ifndef _BODYPROG_MATH_CONSTANTS_H
#define _BODYPROG_MATH_CONSTANTS_H

#define PI    3.1415927f
#define FP_PI (0x5000 / 2)

#define Q4_SHIFT  4  /** Used for: Q27.4 positions. */
#define Q8_SHIFT  8  /** Used for: Q23.8 collision positions. Q7.8 camera AABBs. */
#define Q12_SHIFT 12 /** Used for: Q3.12 alphas, angles. Q19.12 meters, timers, trigonometry. */

#endif
