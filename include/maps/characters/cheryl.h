#ifndef _MAPS_CHARACTERS_CHERYL_H
#define _MAPS_CHARACTERS_CHERYL_H

/** @brief Cheryl character flags. */
typedef enum _CherylFlags
{
    CherylFlag_None = 0,
    CherylFlag_4    = 1 << 4,
    CherylFlag_5    = 1 << 5
} e_CherylFlags;

/** @brief Cheryl character animation indices. */
typedef enum _CherylAnim
{
    CherylAnim_Still       = 0,
    CherylAnim_Idle        = 1,
    CherylAnim_WalkForward = 2,
    CherylAnim_RunForward  = 3
} e_CherylAnim;

/** @brief Cheryl character anim infos. */
extern s_AnimInfo CHERYL_ANIM_INFOS[];

extern s32 D_800DF1CC;

/** Timer. */
extern q19_12 D_800E3A30;

void Cheryl_Update(s_SubCharacter* cheryl, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Cheryl_AnimUpdate(s_SubCharacter* cheryl, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Cheryl_MovementUpdate(s_SubCharacter* cheryl, GsCOORDINATE2* coords);
void Cheryl_ControlUpdate(s_SubCharacter* cheryl, GsCOORDINATE2* coords);
bool Cheryl_FootstepTrigger(s32 animStatus, s_SubCharacter* cheryl, s32 keyframeIdx0, s32 keyframeIdx1, q23_8 distToPlayerSqr, s32 pitch);
void Cheryl_Init(s_SubCharacter* cheryl);

#endif
