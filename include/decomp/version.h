#ifndef _VERSION_H_
#define _VERSION_H_

// Defines region and revision-specific version macros, based on the `VER_XXX` Makefile target.
//
// Supports both region-gated code and date-based gating where changes are known to propagate
// forward across releases (e.g. `#if VERSION_DATE >= VERSION_DATE_NTSCJ_1_1`).
//
// `VERSION_DATE` is set to the date of the game build being compiled.
// Region-specific `VERSION_NTSCJ` / `VERSION_PAL` / `VERSION_NTSC` macros are also defined for code
// that is tied to a particular regional build.

// Version defines that code can test against.
#define VERSION_DATE_PROTO_981216  981216
#define VERSION_DATE_NTSCJ_1_0     990126
#define VERSION_DATE_NTSC_1_1      990210
#define VERSION_DATE_NTSCJ_1_1     990602
#define VERSION_DATE_PAL_1_0       990607
#define VERSION_DATE_NTSCJ_1_2     990616

#if defined(VER_JAP0)
    // Silent Hill (JP) v1.0
    #define VERSION_NTSCJ 1
    #define VERSION_DATE VERSION_DATE_NTSCJ_1_0
    #define VERSION_SERIAL "SLPM-86192"
#elif defined(VER_USA)
    // Silent Hill (US) v1.1
    #define VERSION_NTSC 1
    #define VERSION_DATE VERSION_DATE_NTSC_1_1
    #define VERSION_SERIAL "SLUS-00707"
#elif defined(VER_JAP1)
    // Silent Hill (JP) v1.01
    #define VERSION_NTSCJ 1
    #define VERSION_DATE VERSION_DATE_NTSCJ_1_1
    #define VERSION_SERIAL "SLPM-86498"
#elif defined(VER_EUR)
    // Silent Hill (EU) v1.0
    #define VERSION_PAL 1
    #define VERSION_DATE VERSION_DATE_PAL_1_0
    #define VERSION_SERIAL "SLES-01514"
#elif defined(VER_JAP2)
    // Silent Hill (JP) v1.1
    #define VERSION_NTSCJ 1
    #define VERSION_DATE VERSION_DATE_NTSCJ_1_2
    #define VERSION_SERIAL "SLPM-87029"
#endif

#endif
