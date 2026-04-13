#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/particle.h"
#include "inline_no_dmpsx.h"

// TODO:
// - Make this separate split in each map that uses it instead of `#include`.
//   This file depends on some MAP_X macros from each mapX_sXX.h file though, which the maps .c currently handles including.
// - Move func decls and structs for these out of `shared.h`.

/** Character case switch handling.
 *
 * Maps define one or more `HAS_Chara_X` flags to include their respective switch cases.
 * When only a single case is present (`MAP_CHARA_COUNT == 1`), the
 * macro below replaces `case N:` with `default:` so that the compiler
 * collapses the switch into a direct block, matching single-case maps
 * that skip checking the case entirely.
 *
 * Used by both `Chara_AnimPlaybackStateGet` and `Chara_AnimStartKeyframeIdxGet` in this file.
 */
#if defined(MAP_CHARA_COUNT) && MAP_CHARA_COUNT > 1
    #define CHARA_CASE(id) case id
#else
    #define CHARA_CASE(id) default
#endif

void sharedFunc_800D88AC_0_s00(s_SubCharacter* stalker)
{
    // TODO: Not stalker? Properties don't fit.
    stalker->properties.player.field_F4         = Q12_ANGLE(0.0f);
    stalker->properties.player.field_F0         = Q12(0.0f);
    stalker->properties.player.positionY_EC     = Q12(0.0f);
    stalker->properties.player.moveDistance_126 = Q12(0.0f);
}

void sharedFunc_800D88C0_0_s00(s_SubCharacter* player, bool cond)
{
    player->properties.player.field_F4 = 1;

    if (cond)
    {
        player->model.anim.status      = ANIM_STATUS(HarryAnim_TransitionToStill, true);
        player->model.anim.keyframeIdx = 0;
        player->model.anim.time        = Q12(0.0f);
        player->model.anim.alpha       = Q12(1.0f);
    }
    else
    {
        player->properties.player.afkTimer_E8 = Q12(0.0f);
        player->model.stateStep              = 0;
    }

    player->model.anim.flags |= AnimFlag_Unlocked;
}

void sharedFunc_800D8904_0_s00(s_SubCharacter* player, q19_12 afkTime)
{
    player->properties.player.moveDistance_126 = Q12(0.0f);
    player->properties.player.runTimer_F8      = Q12(0.0f);
    player->properties.player.field_F0         = Q12(0.0f);
    player->properties.player.afkTimer_E8      = afkTime;
    player->model.stateStep                   = 0;
}

void Player_RunTimerReset(s_SubCharacter* player)
{
    player->properties.player.runTimer_F8 = 1;
}

void Chara_Lock(s_SubCharacter* chara)
{
    chara->model.anim.flags &= ~AnimFlag_Unlocked;
}

s32 Chara_IsLockedCheck(s_SubCharacter* chara)
{
    return ~(chara->model.anim.flags & AnimFlag_Unlocked);
}

void Chara_Unlock(s_SubCharacter* chara)
{
    chara->model.anim.flags |= AnimFlag_Unlocked;
}

s32 Chara_AnimPlaybackStateGet(s_SubCharacter* chara)
{
    s_AnimInfo* animInfo = NULL;

    switch (chara->model.charaId_0)
    {
#ifdef HAS_Chara_EndingCybil
        CHARA_CASE(Chara_Cybil):
        CHARA_CASE(Chara_EndingCybil):
            animInfo = &CYBIL_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_Cybil
        CHARA_CASE(Chara_Cybil):
            animInfo = &CYBIL_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_MonsterCybil
        CHARA_CASE(Chara_MonsterCybil):
            animInfo = &MONSTER_CYBIL_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_EndingDahlia
        CHARA_CASE(Chara_Dahlia):
        CHARA_CASE(Chara_EndingDahlia):
            animInfo = &DAHLIA_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_Dahlia
    #if defined(MAP6_S01) // Some reason Dahlia is default case in M6S01?
        default:
    #else
        CHARA_CASE(Chara_Dahlia):
    #endif
            animInfo = &DAHLIA_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_Alessa
        CHARA_CASE(Chara_Alessa):
            animInfo = &ALESSA_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_GhostChildAlessa
        CHARA_CASE(Chara_GhostChildAlessa):
            animInfo = &GHOST_CHILD_ALESSA_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_EndingKaufmann
        CHARA_CASE(Chara_Kaufmann):
        CHARA_CASE(Chara_EndingKaufmann):
            animInfo = &KAUFMANN_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_Kaufmann
        CHARA_CASE(Chara_Kaufmann):
            animInfo = &KAUFMANN_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_Lisa
        CHARA_CASE(Chara_Lisa):
            animInfo = &LISA_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_BloodyLisa
    #ifdef MAP7_S03 // In M7S03 this checks for Lisa instead of BloodyLisa (while Chara_AnimStartKeyframeIdxGet checks for BloodyLisa instead?)
        CHARA_CASE(Chara_Lisa):
    #else
        CHARA_CASE(Chara_BloodyLisa):
    #endif
            animInfo = &BLOODY_LISA_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_GhostDoctor
        CHARA_CASE(Chara_GhostDoctor):
            animInfo = &GHOST_DOCTOR_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_Incubator
        CHARA_CASE(Chara_Incubator):
            animInfo = &INCUBATOR_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_BloodyIncubator
        CHARA_CASE(Chara_BloodyIncubator):
            animInfo = &BLOODY_INCUBATOR_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_Cheryl
        CHARA_CASE(Chara_Cheryl):
            animInfo = &CHERYL_ANIM_INFOS[chara->model.anim.status];
            break;
#endif
    }

    if (animInfo->playbackFunc == Anim_PlaybackOnce)
    {
        if (Anim_DurationGet(chara, animInfo) > Q12(0.0f))
        {
            return chara->model.anim.keyframeIdx == animInfo->endKeyframeIdx;
        }
        else
        {
            return chara->model.anim.keyframeIdx == animInfo->startKeyframeIdx;
        }
    }

    if (animInfo->playbackFunc == Anim_BlendLinear)
    {
        return -2;
    }

    return -1;
}

bool sharedFunc_800D8A00_0_s00(s_SubCharacter* chara, s32 arg1, VECTOR3* arg2In, q19_12 angleIn, s32 arg4)
{
    #define ANGLE_THRESHOLD (Q12_ANGLE(360.0) >> 6) // 360 / 64 = 5.625 degrees.

    q7_8     shortestAngle;
    q19_12   angleStep;
    q23_8    dist;
    VECTOR3* arg2; // Q19.12

    // TODO: This data is hard to keep track of and may not point to the right `properties` struct.
    // Short-hand defines to make it easier to follow.
    #define charaState3  chara->model.stateStep
    #define charaStateE8 chara->properties.dummy.properties_E8[0].val32
    #define charaStateEC chara->properties.dummy.properties_E8[1].val32
    #define charaStateF4 chara->properties.dummy.properties_E8[3].val32
    #define charaStateFC chara->properties.dummy.properties_E8[5].val32

    angleIn = Q12_ANGLE_ABS(angleIn);
    arg2 = arg2In;

    switch (charaStateEC)
    {
        case 0:
            sharedData_800DF1F8_0_s00 = 0;
            charaStateEC = 1;
            break;

        case 1:
            if (arg2[0].vx == chara->position.vx && arg2[0].vz == chara->position.vz)
            {
                charaStateEC = 6;
            }
            else
            {
                sharedData_800DF1FA_0_s00 = Q12_ANGLE_ABS(ratan2(arg2[0].vx - chara->position.vx,
                                                                 arg2[0].vz - chara->position.vz));
                Math_ShortestAngleGet(chara->rotation.vy, sharedData_800DF1FA_0_s00, &shortestAngle);

                if (ABS(shortestAngle) < ANGLE_THRESHOLD)
                {
                    chara->rotation.vy = sharedData_800DF1FA_0_s00;
                    charaStateEC = 3;
                }
                else
                {
                    if (shortestAngle < Q12_ANGLE(0.0f))
                    {
                        charaStateFC = 4;
                        charaStateE8 = 4;
                        charaState3 = 0;
                    }
                    else
                    {
                        charaStateFC = 3;
                        charaStateE8 = 3;
                        charaState3 = 0;
                    }

                    charaStateEC = 2;
                }
            }
            break;

        case 2:
            Math_ShortestAngleGet(chara->rotation.vy, sharedData_800DF1FA_0_s00, &shortestAngle);
            if (ABS(shortestAngle) < ANGLE_THRESHOLD)
            {
                chara->rotation.vy = sharedData_800DF1FA_0_s00;
                charaStateEC = 3;
            }
            break;

        case 3:
            dist = SquareRoot0(Q12_2D_DISTANCE_SQR(arg2[0], chara->position));

            if (ABS((int)dist) < Q8(0.15f)) // @hack Needs to be `int` for `ABS` to match?
            {
                charaStateE8 = 0;
                charaState3 = 0;
                charaStateEC = 8;
            }
            else
            {
                charaStateE8 = arg1;
                charaState3 = 0;
                charaStateFC = arg1;
                charaStateEC = 4;
            }
            break;

        case 4:
            sharedData_800DF1FA_0_s00 = Q12_ANGLE_ABS(ratan2(arg2[sharedData_800DF1F8_0_s00].vx - chara->position.vx,
                                                      arg2[sharedData_800DF1F8_0_s00].vz - chara->position.vz));
            sharedData_800DF1F4_0_s00 = SquareRoot0(Q12_2D_DISTANCE_SQR(arg2[sharedData_800DF1F8_0_s00], chara->position));

            charaStateEC = 5;
            break;

        case 5:
            // Test against next `VECTOR3` unless last one has been reached.
            if ((sharedData_800DF1F8_0_s00 + 1) < arg4)
            {
                sharedData_800DF1FA_0_s00 = ratan2(arg2[sharedData_800DF1F8_0_s00 + 1].vx - chara->position.vx,
                                                   arg2[sharedData_800DF1F8_0_s00 + 1].vz - chara->position.vz);
            }
            else
            {
                sharedData_800DF1FA_0_s00 = ratan2(arg2[sharedData_800DF1F8_0_s00].vx - chara->position.vx,
                                                   arg2[sharedData_800DF1F8_0_s00].vz - chara->position.vz);
            }

            sharedData_800DF1FA_0_s00 = Q12_ANGLE_ABS(sharedData_800DF1FA_0_s00);

            Math_ShortestAngleGet(chara->rotation.vy, sharedData_800DF1FA_0_s00, &shortestAngle);

            // Turn toward.
            angleStep = TIMESTEP_SCALE_30_FPS(g_DeltaTime, (shortestAngle < Q12_ANGLE(45.0f)) ? Q12_ANGLE(2.9f) :
                                                                                                Q12_ANGLE(22.5f));

            if (ABS(shortestAngle) < ANGLE_THRESHOLD)
            {
                chara->rotation.vy = sharedData_800DF1FA_0_s00;
            }
            else if (shortestAngle < Q12_ANGLE(0.0f))
            {
                chara->rotation.vy -= angleStep;
            }
            else
            {
                chara->rotation.vy += angleStep;
            }

            chara->rotation.vy = Q12_ANGLE_ABS(chara->rotation.vy);

            dist = SquareRoot0(Q12_2D_DISTANCE_SQR(arg2[sharedData_800DF1F8_0_s00], chara->position));

            // TODO: Should be `arg1 * Q12(0.15f)`, but compiler splits out one distance for some reason.
            if (dist < (((arg1 - 1) * Q12(0.15f)) + Q12(0.15f)) >> 4 ||
                (sharedData_800DF1F4_0_s00 < dist && sharedData_800DF1F8_0_s00 != arg4 - 1))
            {
                sharedData_800DF1F8_0_s00++;
                dist = SquareRoot0(Q12_2D_DISTANCE_SQR(arg2[sharedData_800DF1F8_0_s00], chara->position));

                if (sharedData_800DF1F8_0_s00 == arg4)
                {
                    charaStateEC = 6;
                }
                else
                {
                    charaStateEC = 4;
                }
            }

            sharedData_800DF1F4_0_s00 = dist;
            break;

        case 6:
            Math_ShortestAngleGet(chara->rotation.vy, angleIn, &shortestAngle);
            if (ABS(shortestAngle) < ANGLE_THRESHOLD)
            {
                chara->rotation.vy = angleIn;
                charaStateEC = 8;
            }
            else
            {
                if (shortestAngle < Q12_ANGLE(0.0f))
                {
                    charaStateFC = 4;
                    charaStateE8 = 4;
                    charaState3 = 0;
                }
                else
                {
                    charaStateFC = 3;
                    charaStateE8 = 3;
                    charaState3 = 0;
                }

                charaStateEC = 7;
            }
            break;

        case 7:
            Math_ShortestAngleGet(chara->rotation.vy, angleIn, &shortestAngle);
            if (ABS(shortestAngle) < ANGLE_THRESHOLD)
            {
                charaStateFC = arg1 - 1;
                chara->rotation.vy = angleIn;
                charaStateE8 = 0;
                charaState3 = 0;
                charaStateEC = 8;
            }
            break;

        case 8:
            charaStateF4 = 1;
            sharedData_800DF1FA_0_s00 = 0;
            charaStateEC = 0;
            chara->properties.npc.field_124 = NULL;
            return true;
    }

    return false;
}

void Chara_VisibleSet(s_SubCharacter* chara)
{
    chara->model.anim.flags |= AnimFlag_Visible;
}

void Chara_InvisibleSet(s_SubCharacter* chara)
{
    chara->model.anim.flags &= ~AnimFlag_Visible;
}

bool sharedFunc_800D908C_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx0, s32 keyframeIdx1, s32 sfxId, s32 pitch)
{
    if (chara->model.anim.status != animStatus)
    {
        return false;
    }

    if (chara->model.anim.keyframeIdx >= keyframeIdx1)
    {
        if (!(chara->properties.dummy.properties_E8[13].val32 & (1 << 4)))
        {
            func_8005DD44(sfxId, &chara->position, Q8(0.5f), pitch);
            chara->properties.dummy.properties_E8[13].val32 |= 1 << 4;
            return true;
        }
    }
    else
    {
        chara->properties.dummy.properties_E8[13].val32 &= ~(1 << 4);
    }

    if (chara->model.anim.keyframeIdx >= keyframeIdx0)
    {
        if (!(chara->properties.dummy.properties_E8[13].val32 & (1 << 5)))
        {
            func_8005DD44(sfxId, &chara->position, Q8(0.5f), pitch);
            chara->properties.dummy.properties_E8[13].val32 |= 1 << 5;
            return true;
        }
    }
    else
    {
        chara->properties.dummy.properties_E8[13].val32 &= ~(1 << 5);
    }

    return false;
}

bool sharedFunc_800D9188_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx, s32 sfxId)
{
    // TODO: Should probably be using `properties.npc` struct instead.
    if (chara->model.anim.status == animStatus)
    {
        if (chara->model.anim.keyframeIdx >= keyframeIdx)
        {
            if (!(chara->properties.player.flags_11C & PlayerFlag_SfxActive))
            {
                switch (sfxId)
                {
#if defined(MAP6_S04)
                    case Sfx_Unk1620:
                        func_8005DC1C(sfxId, &chara->position, Q8(0.25f), 0);
                        break;

                    case Sfx_Unk1621:
                        func_8005DC1C(sfxId, &chara->position, Q8(0.25f), 0);
                        break;

                    case Sfx_Unk1622:
                    case Sfx_Unk1638:
                        func_8005DC1C(sfxId, &chara->position, Q8(0.75f), 0);
                        break;

                    case Sfx_Unk1631:
                    case Sfx_Unk1632:
                        func_8005DC1C(sfxId, &chara->position, Q8(0.25f), 0);
                        break;

#elif defined(MAP3_S00) || defined(MAP5_S02) || defined(MAP5_S03)
                    case Sfx_Unk1492:
                        func_8005DC1C(sfxId, &chara->position, Q8_CLAMPED(1.0f), 2);
                        break;

                    case Sfx_Unk1594:
                        func_8005DC1C(sfxId, &chara->position, Q8(0.5f), 0);
                        break;

#elif defined(MAP3_S04) || defined(MAP4_S04) || defined(MAP7_S00)
                    case Sfx_Unk1639:
                        func_8005DC1C(sfxId, &chara->position, Q8(0.25f), 0);
                        break;

#elif defined(MAP0_S01) || defined(MAP4_S01)
                    case Sfx_Unk1368:
                    case Sfx_Unk1369:
                    case Sfx_Unk1370:
                        func_8005DC1C(sfxId, &chara->position, Q8(0.25f), 0);
                        break;

#elif defined(MAP2_S01) || defined(MAP3_S06)
                    case Sfx_Unk1488:
                    case Sfx_Unk1496:
                        func_8005DC1C(sfxId, &chara->position, Q8(0.25f), 0);
                        break;

#elif defined(MAP6_S01)
                    // TODO: This is made of two blocks above, maybe can be merged somehow.
                    case Sfx_Unk1488:
                    case Sfx_Unk1496:
                        func_8005DC1C(sfxId, &chara->position, Q8(0.25f), 0);
                        break;

                    case Sfx_Unk1368:
                    case Sfx_Unk1369:
                    case Sfx_Unk1370:
                        func_8005DC1C(sfxId, &chara->position, Q8(0.25f), 0);
                        break;

#elif defined(MAP7_S03)
                    case Sfx_Unk1539:
                    case Sfx_Unk1674:
                    case Sfx_Unk1675:
                        func_8005DC1C(sfxId, &chara->position, Q8(1.0f / 8.0f), 0);
                        break;

                    case Sfx_Unk1622:
                        func_8005DC1C(sfxId, &chara->position, Q8(0.75f), 0);
                        break;

#endif
                    default:
                        func_8005DC1C(sfxId, &chara->position, Q8(0.5f), 0);
                        break;
                }

                chara->properties.player.flags_11C |= PlayerFlag_SfxActive;
                return true;
            }
        }
        else
        {
            chara->properties.player.flags_11C &= ~PlayerFlag_SfxActive;
        }
    }

    return false;
}

s32 Chara_AnimStartKeyframeIdxGet(s_SubCharacter* chara)
{
    s_AnimInfo* animInfo = NULL;

    switch (chara->model.charaId_0)
    {
#if defined(MAP5_S02) || defined(MAP5_S03)
        // `animInfo` left as `NULL`.
#else

#ifdef HAS_Chara_EndingCybil
        CHARA_CASE(Chara_Cybil):
        CHARA_CASE(Chara_EndingCybil):
            animInfo = &CYBIL_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_Cybil
        CHARA_CASE(Chara_Cybil):
            animInfo = &CYBIL_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_MonsterCybil
        CHARA_CASE(Chara_MonsterCybil):
            animInfo = &MONSTER_CYBIL_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_EndingDahlia
        CHARA_CASE(Chara_Dahlia):
        CHARA_CASE(Chara_EndingDahlia):
            animInfo = &DAHLIA_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_Dahlia
    #if defined(MAP6_S01) // Some reason Dahlia is default case in M6S01?
        default:
    #else
        CHARA_CASE(Chara_Dahlia):
    #endif
            animInfo = &DAHLIA_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_Alessa
        CHARA_CASE(Chara_Alessa):
            animInfo = &ALESSA_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_GhostChildAlessa
        CHARA_CASE(Chara_GhostChildAlessa):
            animInfo = &GHOST_CHILD_ALESSA_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_EndingKaufmann
        CHARA_CASE(Chara_Kaufmann):
        CHARA_CASE(Chara_EndingKaufmann):
            animInfo = &KAUFMANN_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_Kaufmann
        CHARA_CASE(Chara_Kaufmann):
            animInfo = &KAUFMANN_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

// M7S02 uses Chara_GhostDoctor in Chara_AnimPlaybackStateGet, but includes Lisa/BloodyLisa here?
#if defined(HAS_Chara_Lisa) || defined(HAS_Chara_GhostDoctor)
        CHARA_CASE(Chara_Lisa):
            animInfo = &LISA_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#if defined(HAS_Chara_BloodyLisa) || defined(HAS_Chara_GhostDoctor)
        CHARA_CASE(Chara_BloodyLisa):
            animInfo = &BLOODY_LISA_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_Incubator
        CHARA_CASE(Chara_Incubator):
            animInfo = &INCUBATOR_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_BloodyIncubator
        CHARA_CASE(Chara_BloodyIncubator):
            animInfo = &BLOODY_INCUBATOR_ANIM_INFOS[chara->model.anim.status];
            break;
#endif

#ifdef HAS_Chara_Cheryl
        CHARA_CASE(Chara_Cheryl):
            animInfo = &CHERYL_ANIM_INFOS[chara->model.anim.status];
            break;
#endif
#endif
    }

    return animInfo->startKeyframeIdx;
}

void sharedFunc_800D923C_0_s00(s_SubCharacter* chara)
{
    chara->model.stateStep = 0;

    chara->field_C8.field_0   = Q12(0.0f);
    chara->field_C8.field_2   = Q12(0.0f);
    chara->field_C8.field_6   = Q12(0.0f);
    chara->field_D4.radius_0   = Q12(0.0f);
    chara->field_D4.field_2   = Q12(0.0f);
    chara->field_D8.offsetZ_6 = Q12(0.0f);
    chara->field_D8.offsetX_4 = Q12(0.0f);
    chara->field_D8.offsetZ_2 = Q12(0.0f);
    chara->field_D8.offsetX_0 = Q12(0.0f);

    chara->properties.player.positionY_EC = Q12(0.0f);
    chara->properties.player.afkTimer_E8  = Q12(0.0f);
    chara->properties.player.positionY_EC = Q12(0.0f);
    chara->properties.player.field_F0     = 0;
    chara->properties.player.field_F4     = Q12_ANGLE(0.0f);

    chara->model.controlState++;

    chara->field_E1_0 = 3;
}

#undef CHARA_CASE
