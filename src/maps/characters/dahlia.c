#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/dahlia.h"

/** AI code for `Chara_Dahlia`
 *
 * Included in:
 *  MAP2_S01
 *  MAP3_S06
 *  MAP6_S01
 *  MAP6_S04
 *  MAP7_S02
 *  MAP7_S03
 */

/** Addresses
 * MAP2_S01: 0x800CD20C
 * MAP3_S06: 0x800CF0F8
 * MAP6_S01: 0x800CF7D0
 * MAP6_S04: 0x800DCA30
 * MAP7_S02: 0x800D6ED4
 * MAP7_S03: 0x800D2368
 */
void Ai_Dahlia_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    if (chara->model.controlState == 0)
    {
        Ai_Dahlia_Init(chara);
    }

    Ai_Dahlia_AnimStateUpdate(chara, boneCoords);
    Ai_Dahlia_MovementUpdate(chara, boneCoords);
    Ai_Dahlia_AnimUpdate(chara, anmHdr, boneCoords);
}

/** Addresses
 * MAP2_S01: 0x800CD280
 * MAP3_S06: 0x800CF16C
 * MAP6_S01: 0x800CF844
 * MAP6_S04: 0x800DCAA4
 * MAP7_S02: 0x800D6F48
 * MAP7_S03: 0x800D23DC
 */
void Ai_Dahlia_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    s_AnimInfo* animInfo;

    if (!chara->properties.player.field_F0)
    {
        animInfo = &DAHLIA_ANIM_INFOS[chara->model.anim.status];
        animInfo->playbackFunc(&chara->model, anmHdr, boneCoords, animInfo);
    }
}

/** Addresses
 * MAP2_S01: 0x800CD2C8
 * MAP3_S06: 0x800CF1B4
 * MAP6_S01: 0x800CF88C
 * MAP6_S04: 0x800DCAEC
 * MAP7_S02: 0x800D6F90
 * MAP7_S03: 0x800D2424
 */
void Ai_Dahlia_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* boneCoords)
{
    VECTOR3 unused;
    VECTOR3 offset;
    q19_12  moveSpeed;
    q3_12   headingAngle;
    q19_12  moveDist;
    s32     scaleRestoreShift;
    u32     scaleReduceShift;

    unused       = chara->position;
    moveSpeed    = chara->moveSpeed;
    headingAngle = chara->headingAngle;
    moveDist      = Q12_MULT_PRECISE(moveSpeed, g_DeltaTime);

    scaleRestoreShift = OVERFLOW_GUARD(moveDist);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = (u32)Q12_MULT_PRECISE(moveDist >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vz = (u32)Q12_MULT_PRECISE(moveDist >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vy = Q12_MULT_PRECISE(chara->fallSpeed, g_DeltaTime);

    Collision_WallDetect(&sharedData_800E39BC_0_s00, &offset, chara);

    chara->position.vx += offset.vx;
    chara->position.vy  = Q12(0.0f);
    chara->position.vz += offset.vz;

    if (chara->position.vy > sharedData_800E39BC_0_s00.field_C)
    {
        chara->position.vy = sharedData_800E39BC_0_s00.field_C;
        chara->fallSpeed   = Q12(0.0f);
    }

    boneCoords->coord.t[0] = Q12_TO_Q8(chara->position.vx);
    boneCoords->coord.t[1] = Q12_TO_Q8(chara->position.vy);
    boneCoords->coord.t[2] = Q12_TO_Q8(chara->position.vz);
}

/** Addresses
 * MAP2_S01: 0x800CD4A0
 * MAP3_S06: 0x800CF38C
 * MAP6_S01: 0x800CFA64
 * MAP6_S04: 0x800DCCC4
 * MAP7_S02: 0x800D7168
 * MAP7_S03: 0x800D25FC
 */
void Ai_Dahlia_AnimStateUpdate(s_SubCharacter* dahlia, GsCOORDINATE2* boneCoords)
{
    s_Collision coll;
    e_SfxId     sfx;
    s8          pitch0;
    s8          pitch1;

    #define dahliaProps dahlia->properties.dahlia

    switch (dahliaProps.stateIdx0)
    {
        case 0:
        case 5:
            if (dahliaProps.moveDistance_126)
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < 0)
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            Model_AnimStatusSet(&dahlia->model, DahliaAnim_1, false);
            Character_AnimStateReset(dahlia);
            break;

        case 1:
            if (dahliaProps.moveDistance_126 > Q12(1.25f))
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.5f));
                if (dahliaProps.moveDistance_126 < Q12(1.25f))
                {
                    dahliaProps.moveDistance_126 = Q12(1.25f);
                }
            }
            else if (dahliaProps.moveDistance_126 < Q12(1.25f))
            {
                dahliaProps.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                dahliaProps.moveDistance_126  = CLAMP(dahliaProps.moveDistance_126, 0, Q12(1.25f));
            }

            Model_AnimStatusSet(&dahlia->model, DahliaAnim_2, false);
            Character_AnimStateReset(dahlia);
            break;

        case 6:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_14, false);
#if defined(MAP7_S03)
            WorldGfx_HeldItemAttach(Chara_EndingDahlia, MODEL_BONE(1, 0));
#endif
            Character_AnimStateReset(dahlia);
            break;

        case 7:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_3, false);
            Character_AnimStateReset(dahlia);
            break;

        case 8:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_4, false);
            Character_AnimStateReset(dahlia);
            break;

        case 11:
#if defined(MAP3_S06) || defined(MAP6_S01) || defined(MAP6_S04) || defined(MAP7_S02) || defined(MAP7_S03)
            Model_AnimStatusKeyframeSet(dahlia->model, DahliaAnim_7, true, DAHLIA_ANIM_INFOS, 0);
#else
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_7, false);
#endif
            Character_AnimStateReset(dahlia);
            break;

        case 9:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_5, false);
            Character_AnimStateReset(dahlia);

            if (dahlia->model.anim.keyframeIdx < 144)
            {
                WorldGfx_HeldItemAttach(Chara_Dahlia, MODEL_BONE(1, 0));
            }
            else
            {
#if !defined(MAP6_S01) && !defined(MAP6_S04) && !defined(MAP7_S02) && !defined(MAP7_S03)
#if defined(MAP3_S06)
                WorldGfx_HeldItemAttach(Chara_Dahlia, MODEL_BONE(2, 0));
#else
                WorldGfx_HeldItemAttach(Chara_Dahlia, MODEL_BONE(3, 0));
#endif
#endif
            }
            break;

        case 10:
#if !defined(MAP6_S01) && !defined(MAP6_S04) && !defined(MAP7_S02) && !defined(MAP7_S03)
#if defined(MAP3_S06)
            Model_AnimStatusKeyframeSet(dahlia->model, DahliaAnim_6, true, DAHLIA_ANIM_INFOS, 0);
#else
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_6, false);
#endif
#endif
            Character_AnimStateReset(dahlia);

            if (dahlia->model.anim.keyframeIdx < 198)
            {
#if !defined(MAP6_S01) && !defined(MAP6_S04) && !defined(MAP7_S02) && !defined(MAP7_S03)
#if defined(MAP3_S06)
                WorldGfx_HeldItemAttach(Chara_Dahlia, MODEL_BONE(2, 0));
#else
                WorldGfx_HeldItemAttach(Chara_Dahlia, MODEL_BONE(3, 0));
#endif
#endif
            }
            else
            {
                WorldGfx_HeldItemAttach(Chara_Dahlia, MODEL_BONE(1, 0));
            }
            break;

        case 12:
            Model_AnimStatusKeyframeSet(dahlia->model, DahliaAnim_8, true, DAHLIA_ANIM_INFOS, 0);
            Character_AnimStateReset(dahlia);
            break;

        case 13:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_9, false);
            Character_AnimStateReset(dahlia);
            break;

        case 14:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_10, false);
            Character_AnimStateReset(dahlia);
            break;

        case 15:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_15, false);
            Character_AnimStateReset(dahlia);
            break;

        case 16:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_16, false);
            Character_AnimStateReset(dahlia);

            if (dahlia->model.anim.keyframeIdx == 103)
            {
                dahliaProps.stateIdx0      = 5;
                dahlia->model.stateStep = 0;
            }
            break;

        case 17:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_17, false);
            Character_AnimStateReset(dahlia);
            break;

        case 18:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_18, false);
            Character_AnimStateReset(dahlia);
            break;

        case 19:
            if (dahlia->model.anim.keyframeIdx >= 40 && !sharedData_800D16E4_2_s01)
            {
                func_8005F6B0(&g_SysWork.npcs[1], &(VECTOR3){ Q12(138.3f), Q12(-1.1f), Q12(-100.8f) }, 3, 1);
                sharedData_800D16E4_2_s01 = 1;
            }

            Model_AnimStatusKeyframeSet(dahlia->model, DahliaAnim_19, true, DAHLIA_ANIM_INFOS, 0);
            Character_AnimStateReset(dahlia);

            if (dahliaProps.stateIdx0 != 19)
            {
                sharedData_800D16E4_2_s01 = 0;
            }
            break;

        case 20:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_20, false);
            Character_AnimStateReset(dahlia);
            break;

        case 21:
            Model_AnimStatusKeyframeSet(dahlia->model, DahliaAnim_21, true, DAHLIA_ANIM_INFOS, 0);
            Character_AnimStateReset(dahlia);
            break;

        case 22:
            Model_AnimStatusKeyframeSet(dahlia->model, DahliaAnim_22, true, DAHLIA_ANIM_INFOS, 0);
            Character_AnimStateReset(dahlia);
            break;

        case 23:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_23, false);
            Character_AnimStateReset(dahlia);
            break;

        case 24:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_24, false);
            Character_AnimStateReset(dahlia);
            break;

        case 25:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_11, false);
            WorldGfx_HeldItemAttach(Chara_Dahlia, MODEL_BONE(1, 0));

            if (dahlia->model.anim.keyframeIdx == 349)
            {
                dahliaProps.stateIdx0       = 26;
                dahlia->model.stateStep = 0;
                break;
            }
            break;

        case 26:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_12, false);
            Character_AnimStateReset(dahlia);
            break;

        case 27:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_13, false);
            Character_AnimStateReset(dahlia);
            break;

        case 28:
            Model_AnimStatusSet(&dahlia->model, DahliaAnim_25, false);
            Character_AnimStateReset(dahlia);
            break;
    }

    Collision_Get(&coll, dahlia->position.vx, dahlia->position.vz);

    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);
#if defined(MAP6_S01)
    sfx = Sfx_Unk1606;
#else
    sfx = Sfx_Unk1489;
#endif

    switch (dahliaProps.stateIdx0)
    {
        case 1:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(DahliaAnim_2, true), dahlia, 24, 37, sfx, pitch0);
            break;

        case 8:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(DahliaAnim_4, true), dahlia, 107, 98, sfx, pitch0);
            break;

        case 11:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(DahliaAnim_7, true), dahlia, 235, 245, sfx, pitch0);
            break;

        case 7:
            if (dahlia->model.anim.keyframeIdx < 47)
            {
                sharedFunc_800D9188_0_s00(dahlia->model.anim.status, dahlia, 46, Sfx_Unk1674);
            }
            else
            {
                sharedFunc_800D9188_0_s00(dahlia->model.anim.status, dahlia, 47, Sfx_Unk1675);
            }
            break;

        default:
            break;

        case 17:
            if (dahlia->model.anim.keyframeIdx < 127)
            {
                sharedFunc_800D9188_0_s00(ANIM_STATUS(DahliaAnim_17, true), dahlia, 120, Sfx_Unk1674);
            }
            else
            {
                sharedFunc_800D9188_0_s00(ANIM_STATUS(DahliaAnim_17, true), dahlia, 127, Sfx_Unk1675);
            }
            break;

        case 10:
            if (g_SavegamePtr->mapIdx == MapIdx_MAP2_S01)
            {
                sharedFunc_800D9188_0_s00(dahlia->model.anim.status, dahlia, 193, Sfx_Unk1488);
            }
            else
            {
                sharedFunc_800D9188_0_s00(dahlia->model.anim.status, dahlia, 193, Sfx_Unk1496);
            }
            break;

        case 14:
            if (dahlia->model.anim.keyframeIdx < 310)
            {
                sharedFunc_800D908C_0_s00(dahlia->model.anim.status, dahlia, 319, 309, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(dahlia->model.anim.status, dahlia, 319, 329, sfx, pitch0);
            }
            break;

        case 19:
            if (dahlia->model.anim.keyframeIdx < 175)
            {

                sharedFunc_800D9188_0_s00(ANIM_STATUS(DahliaAnim_19, true), dahlia, 170, Sfx_Unk1674);
            }
            else
            {
                sharedFunc_800D9188_0_s00(ANIM_STATUS(DahliaAnim_19, true), dahlia, 177, Sfx_Unk1675);
            }
            break;
    }

    dahlia->rotation.vy  = Q12_ANGLE_ABS(dahlia->rotation.vy + Q8_TO_Q4(sharedData_800D16E0_2_s01));
    dahlia->headingAngle = dahlia->rotation.vy;
    dahlia->moveSpeed    = dahliaProps.moveDistance_126;
    dahlia->fallSpeed   += g_GravitySpeed;

    boneCoords->flg = false;
    Math_RotMatrixZxyNegGte(&dahlia->rotation, &boneCoords->coord);
}

/** Addresses
 * MAP2_S01: 0x800CDD64
 * MAP3_S06: 0x800CFC9C
 * MAP6_S01: 0x800D031C
 * MAP6_S04: 0x800DD57C
 * MAP7_S02: 0x800D7A20
 * MAP7_S03: 0x800D2ECC
 */
void Ai_Dahlia_Init(s_SubCharacter* chara)
{
    sharedFunc_800D923C_0_s00(chara);

    sharedData_800D16E0_2_s01 = 0;
    sharedData_800D16E4_2_s01 = 0;

#ifdef MAP7_S03
    WorldGfx_HeldItemAttach(Chara_EndingDahlia, MODEL_BONE(1, 0)); // TODO: MAP7_S03 Ai_Dahlia funcs could be Ai_EndingDahlia instead, if other Ai_Dahlia funcs don't match other overlays.
#else
    WorldGfx_HeldItemAttach(Chara_Dahlia, MODEL_BONE(1, 0));
#endif

#ifdef MAP7_S02
    WorldGfx_CharaModelTransparentSet(Chara_Dahlia, true);
#endif
}
