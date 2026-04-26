#ifndef _MAPS_CHARACTERS_TWINFEELER_H
#define _MAPS_CHARACTERS_TWINFEELER_H

/** @brief Twinfeeler character flags. */
typedef enum _TwinfeelerFlags
{
    TwinfeelerFlag_None        = 0,
    TwinfeelerFlag_0           = 1 << 0,
    TwinfeelerFlag_Underground = 1 << 2,
} e_TwinfeelerFlags;

// TODO: Unsure if anims marked as unused are actually unused. Code doesn't seem to reference them. Stuns also unclear.
/** @brief Twinfeeler character animation indices. */
typedef enum _TwinfeelerAnim
{
    TwinfeelerAnim_Still           = 0,
    TwinfeelerAnim_Resurface       = 1,
    TwinfeelerAnim_Burrow          = 2,
    TwinfeelerAnim_DeathStartAlt0  = 3,  /** @unused */
    TwinfeelerAnim_DeathStartAlt1  = 4,  /** @unused */
    TwinfeelerAnimDeathThroes      = 5,
    TwinfeelerAnim_WalkForward     = 6,
    TwinfeelerAnim_DeathStart      = 7,
    TwinfeelerAnim_InchForward     = 8,
    TwinfeelerAnim_9               = 9,  /** @unused Stun? */
    TwinfeelerAnim_10              = 10, /** @unused Recoil. Stand to idle. */
    TwinfeelerAnim_StunToIdle      = 11,
    TwinfeelerAnim_StandAcidAttack = 12,
    TwinfeelerAnim_StandRecoil     = 13,
    TwinfeelerAnim_StandRecoilAlt  = 14, /** @unused */
    TwinfeelerAnim_StandStunStart  = 15, /** @unused */
    TwinfeelerAnim_StunStart       = 16,
    TwinfeelerAnim_IdleToStand     = 17,
    TwinfeelerAnim_Idle            = 18,
    TwinfeelerAnim_DeathEndAlt     = 19,
    TwinfeelerAnim_StunIdleEnd     = 20,
    TwinfeelerAnim_StandStunEnd    = 21, /** @unused */
    TwinfeelerAnim_StunEnd         = 22,
    TwinfeelerAnim_23              = 23
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
    TwinfeelerControl_Stand       = 7,
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

// TODO: Move function decls here.

#endif
