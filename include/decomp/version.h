#ifndef _VERSION_H_
#define _VERSION_H_

// Defines region and revision-specific version macros based on the `VER_XXX` Makefile target.
//
// Supports both region-gated code and date-based gating where changes are known to propagate
// forward across releases (e.g. `#if VERSION_EQUAL_OR_NEWER(JAP1)`).
//
// `VERSION_DATE` is set to the date of the game build being compiled.
// Region-specific `VERSION_NTSCJ` / `VERSION_PAL` / `VERSION_NTSC` macros are also defined for code
// that is tied to a particular regional build.
//
// This offers several ways to gate code behind version checks:
// - Specific releases, for code that changes between every release (e.g. random pad bytes, raw pointer addresses).
//   Use `#if VERSION_IS(USA)` / `VERSION_IS(JAP0)` / etc.
// - Regions, for code specific to all releases in a particular region (e.g. JP text rendering).
//   Use `#if VERSION_REGION_IS(NTSC)` / `VERSION_REGION_IS(NTSCJ)` / `VERSION_REGION_IS(PAL)`
// - Build dates, for code introduced in a given release and carried forward to later ones (e.g. bugfixes)
//   Use `#if VERSION_EQUAL_OR_NEWER(USA)` or `VERSION_EQUAL_OR_OLDER(JPN0)` with one of the version names.

/**
 * Checks if the build target is a specific release.
 * @param release The release identifier (JAP0, USA, JAP1, EUR, JAP2)
 */
#define VERSION_IS(release) defined(VER_##release)

/**
 * Checks if the build target matches a given region.
 * @param region The region identifier (e.g. NTSC, NTSCJ, PAL)
 */
#define VERSION_REGION_IS(region) defined(VERSION_##region)

/**
 * Checks if the build target version is equal to or newer than the given release.
 * @param release The release to compare against (PROTO_981216, JAP0, USA, JAP1, EUR, JAP2)
 */
#define VERSION_EQUAL_OR_NEWER(release) (VERSION_DATE >= VERSION_DATE_##release)

/**
 * Checks if the build target version is equal to or older than the given release.
 * @param release The release to compare against (PROTO_981216, JAP0, USA, JAP1, EUR, JAP2)
 */
#define VERSION_EQUAL_OR_OLDER(release) (VERSION_DATE <= VERSION_DATE_##release)

// Version defines that code can test against.
#define VERSION_DATE_PROTO_981216  981216
#define VERSION_DATE_JAP0          990126
#define VERSION_DATE_USA           990210
#define VERSION_DATE_JAP1          990602
#define VERSION_DATE_EUR           990607
#define VERSION_DATE_JAP2          990616

#if defined(VER_JAP0)
    // Silent Hill (JP) v1.0
    #define VERSION_NTSCJ 1
    #define VERSION_DATE VERSION_DATE_JAP0
    #define VERSION_SERIAL "SLPM-86192"
#elif defined(VER_USA)
    // Silent Hill (US) v1.1
    #define VERSION_NTSC 1
    #define VERSION_DATE VERSION_DATE_USA
    #define VERSION_SERIAL "SLUS-00707"
#elif defined(VER_JAP1)
    // Silent Hill (JP) v1.01
    #define VERSION_NTSCJ 1
    #define VERSION_DATE VERSION_DATE_JAP1
    #define VERSION_SERIAL "SLPM-86498"
#elif defined(VER_EUR)
    // Silent Hill (EU) v1.0
    #define VERSION_PAL 1
    #define VERSION_DATE VERSION_DATE_EUR
    #define VERSION_SERIAL "SLES-01514"
#elif defined(VER_JAP2)
    // Silent Hill (JP) v1.1
    #define VERSION_NTSCJ 1
    #define VERSION_DATE VERSION_DATE_JAP2
    #define VERSION_SERIAL "SLPM-87029"
#endif

#endif
