#ifndef _MAPS_CHARACTERS_PUPPETNURSE_H
#define _MAPS_CHARACTERS_PUPPETNURSE_H

/** @brief Puppet Nurse or Puppet Doctor character flags. */
typedef enum _PuppetNurseFlags
{
    PuppetNurseFlag_None = 0,
    PuppetNurseFlag_0    = 1 << 0,
    PuppetNurseFlag_1    = 1 << 1
} e_PuppetNurseFlags;

/** @brief Puppet Nurse or Puppet Doctor character animation indices. */
typedef enum _PuppetNurseAnim
{
    PuppetNurseAnim_Still = 0,
    PuppetNurseAnim_1     = 1,
    PuppetNurseAnim_2     = 2,
    PuppetNurseAnim_3     = 3,
    PuppetNurseAnim_4     = 4,
    PuppetNurseAnim_5     = 5,
    PuppetNurseAnim_6     = 6,
    PuppetNurseAnim_7     = 7, // Nurse-specific.
    PuppetNurseAnim_8     = 8, // Doctor-specific.
    PuppetNurseAnim_9     = 9,
    PuppetNurseAnim_10    = 10,
    PuppetNurseAnim_14    = 14,
    PuppetNurseAnim_15    = 15,
    PuppetNurseAnim_16    = 16,
    PuppetNurseAnim_17    = 17,
    PuppetNurseAnim_18    = 18,
    PuppetNurseAnim_19    = 19,
    PuppetNurseAnim_20    = 20,
    PuppetNurseAnim_21    = 21
} e_PuppetNurseAnim;

/** @brief Puppet Nurse or Puppet Doctor character control states. */
typedef enum _PuppetNurseControl
{
    PuppetNurseControl_1  = 1,
    PuppetNurseControl_2  = 2,
    PuppetNurseControl_3  = 3, // Doctor-specific.
    PuppetNurseControl_4  = 4, // Nurse-specific.
    PuppetNurseControl_5  = 5,
    PuppetNurseControl_6  = 6, // Nurse-specific.
    PuppetNurseControl_7  = 7, // Doctor-specific.
    PuppetNurseControl_8  = 8,
    PuppetNurseControl_9  = 9,
    PuppetNurseControl_10 = 10,
    PuppetNurseControl_11 = 11,
    PuppetNurseControl_12 = 12,
    PuppetNurseControl_13 = 13
} e_PuppetNurseControl;

#endif
