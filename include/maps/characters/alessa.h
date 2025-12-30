#ifndef _MAPS_CHARACTERS_ALESSA_H
#define _MAPS_CHARACTERS_ALESSA_H

/** @brief Alessa character animation indices. */
typedef enum _AlessaAnim
{
    AlessaAnim_Still                  = 0,
    AlessaAnim_StandIdle              = 1,
    AlessaAnim_WalkForward            = 2,
    AlessaAnim_WalkForwardTurnStumble = 3,
    AlessaAnim_ForcePush              = 4,
    AlessaAnim_StumbleForwardCrumple  = 5,
    AlessaAnim_CrumpleLookUp          = 6,
    AlessaAnim_CrumpleShakeHead       = 7,
    AlessaAnim_StandLookRight         = 8,
    AlessaAnim_CrumpleIdle            = 9,
    AlessaAnim_Kneel                  = 10
} e_AlessaAnim;

/** @brief Alessa character anim infos. */
extern s_AnimInfo ALESSA_ANIM_INFOS[];

/*s_AnimInfo ALESSA_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(AlessaAnim_Still,                  false), false, ANIM_STATUS(AlessaAnim_Still,                  false), { Q12(0.0f)  }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(AlessaAnim_Still,                  true),  false, NO_VALUE,                                              { Q12(30.0f) }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_StandIdle,              false), false, ANIM_STATUS(AlessaAnim_Kneel,                  true),  { Q12(5.0f)  }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(AlessaAnim_StandIdle,              true),  false, NO_VALUE,                                              { Q12(5.0f)  }, 0,        15  },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_WalkForward,            false), false, ANIM_STATUS(AlessaAnim_Kneel,                  true),  { Q12(5.0f)  }, NO_VALUE, 16  },
    { Anim_Update1, ANIM_STATUS(AlessaAnim_WalkForward,            true),  false, NO_VALUE,                                              { Q12(15.0f) }, 16,       44  },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_WalkForwardTurnStumble, false), false, ANIM_STATUS(AlessaAnim_WalkForwardTurnStumble, true),  { Q12(10.0f) }, NO_VALUE, 45  },
    { Anim_Update0, ANIM_STATUS(AlessaAnim_WalkForwardTurnStumble, true),  false, ANIM_STATUS(AlessaAnim_WalkForwardTurnStumble, true),  { Q12(10.0f) }, 45,       131 },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_ForcePush,              false), false, ANIM_STATUS(AlessaAnim_ForcePush,              true),  { Q12(20.0f) }, NO_VALUE, 132 },
    { Anim_Update0, ANIM_STATUS(AlessaAnim_ForcePush,              true),  false, ANIM_STATUS(AlessaAnim_ForcePush,              true),  { Q12(10.0f) }, 132,      170 },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_StumbleForwardCrumple,  false), false, ANIM_STATUS(AlessaAnim_StumbleForwardCrumple,  true),  { Q12(10.0f) }, NO_VALUE, 171 },
    { Anim_Update0, ANIM_STATUS(AlessaAnim_StumbleForwardCrumple,  true),  false, ANIM_STATUS(AlessaAnim_StumbleForwardCrumple,  true),  { Q12(10.0f) }, 171,      216 },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_CrumpleLookUp,          false), false, ANIM_STATUS(AlessaAnim_CrumpleLookUp,          true),  { Q12(1.0f)  }, NO_VALUE, 217 },
    { Anim_Update0, ANIM_STATUS(AlessaAnim_CrumpleLookUp,          true),  false, ANIM_STATUS(AlessaAnim_CrumpleLookUp,          true),  { Q12(10.0f) }, 217,      237 },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_CrumpleShakeHead,       true),  false, ANIM_STATUS(AlessaAnim_CrumpleShakeHead,       true),  { Q12(1.0f)  }, NO_VALUE, 238 },
    { Anim_Update0, ANIM_STATUS(AlessaAnim_CrumpleShakeHead,       true),  false, ANIM_STATUS(AlessaAnim_CrumpleShakeHead,       true),  { Q12(10.0f) }, 238,      288 },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_StandLookRight,         false), false, ANIM_STATUS(AlessaAnim_StandLookRight,         true),  { Q12(10.0f) }, NO_VALUE, 289 },
    { Anim_Update0, ANIM_STATUS(AlessaAnim_StandLookRight,         true),  false, ANIM_STATUS(AlessaAnim_StandLookRight,         true),  { Q12(10.0f) }, 289,      309 },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_CrumpleIdle,            false), false, ANIM_STATUS(AlessaAnim_CrumpleIdle,            true),  { Q12(5.0f)  }, NO_VALUE, 310 },
    { Anim_Update1, ANIM_STATUS(AlessaAnim_CrumpleIdle,            true),  false, NO_VALUE,                                              { Q12(3.0f)  }, 310,      325 },
    { Anim_Update2, ANIM_STATUS(AlessaAnim_Kneel,                  false), false, ANIM_STATUS(AlessaAnim_Kneel,                  true),  { Q12(5.0f)  }, NO_VALUE, 326 },
    { Anim_Update1, ANIM_STATUS(AlessaAnim_Kneel,                  true),  false, NO_VALUE,                                              { Q12(3.0f)  }, 326,      341 }
};*/

extern s32 sharedData_800D3150_3_s02; // Used by `Ai_Alessa_Init`.

void Ai_Alessa_Update(s_SubCharacter* alessa, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Alessa_AnimUpdate(s_SubCharacter* alessa, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Alessa_MovementUpdate(s_SubCharacter* alessa, GsCOORDINATE2* coords);

void Ai_Alessa_AnimStateUpdate(s_SubCharacter* alessa, GsCOORDINATE2* coords);

/** @brief Initializes an Alessa character.
 *
 * @param alessa Alessa character.
 */
void Ai_Alessa_Init(s_SubCharacter* alessa);

#endif
