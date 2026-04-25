#ifndef _MAPS_CHARACTERS_TWINFEELER_H
#define _MAPS_CHARACTERS_TWINFEELER_H

/** @brief Twinfeeler character flags. */
typedef enum _TwinfeelerFlags
{
    TwinfeelerFlag_None        = 0,
    TwinfeelerFlag_0           = 1 << 0,
    TwinfeelerFlag_Underground = 1 << 2,
} e_TwinfeelerFlags;

/** @brief Twinfeeler character animation indices. */
typedef enum _TwinfeelerAnim
{
    TwinfeelerAnim_Still       = 0,
    TwinfeelerAnim_Surface     = 1,
    TwinfeelerAnim_Dive        = 2,
    TwinfeelerAnim_DeathStart  = 3, // Maybe not death?
    TwinfeelerAnim_4           = 4, // Another death start? Or stun?
    TwinfeelerAnim_5           = 5,
    TwinfeelerAnim_WalkForward = 6,
    TwinfeelerAnim_7           = 7, // To 20.
    TwinfeelerAnim_InchForward = 8,
    TwinfeelerAnim_9           = 9,
    TwinfeelerAnim_10          = 10,
    TwinfeelerAnim_11          = 11,
    TwinfeelerAnim_AcidAttack  = 12,
    TwinfeelerAnim_13          = 13, // To 18.
    TwinfeelerAnim_14          = 14, // Tecoil?
    TwinfeelerAnim_15          = 15, // Tecoil?
    TwinfeelerAnim_16          = 16, // To 22.
    TwinfeelerAnim_17          = 17, // Inch forward to stand up.
    TwinfeelerAnim_Idle        = 18,
    TwinfeelerAnim_DeathEnd    = 19, // Or stun?
    TwinfeelerAnim_20          = 20, // Stun?
    TwinfeelerAnim_21          = 21, // Stun?
    TwinfeelerAnim_22          = 22, // Stun?
    TwinfeelerAnim_23          = 23
} e_TwinfeelerAnim;

/** @brief Twinfeeler character control states. */
typedef enum _TwinfeelerControl
{
    TwinfeelerControl_None        = 0,
    TwinfeelerControl_WalkForward = 1,
    TwinfeelerControl_2           = 2,
    TwinfeelerControl_3           = 3,
    TwinfeelerControl_4           = 4,
    TwinfeelerControl_5           = 5,
    TwinfeelerControl_6           = 6,
    TwinfeelerControl_7           = 7,
    TwinfeelerControl_Attack      = 8,
    TwinfeelerControl_9           = 9,
    TwinfeelerControl_10          = 10,
    TwinfeelerControl_Idle        = 11,
    TwinfeelerControl_12          = 12,
    TwinfeelerControl_13          = 13
} e_TwinfeelerControl;

/** @brief Twinfeeler character model bone indices. */
typedef enum _TwinfeelerBone
{
    TwinfeelerBone_6    = 6,
    TwinfeelerBone_Head = 14
} e_TwinfeelerBone;

#endif
