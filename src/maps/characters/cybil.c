#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/cybil.h"

/** AI code for `Chara_Cybil`
 *
 * Included in:
 *  MAP0_S01
 *  MAP4_S01
 *  MAP6_S01
 *  MAP7_S03
 */

/** Addresses
 * MAP0_S01: 0x800D8814
 * MAP4_S01: 0x800CFDF0
 * MAP6_S01: 0x800CE4FC
 * MAP7_S03: 0x800D1098
 */
void Cybil_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    if (chara->model.controlState == CybilControl_None)
    {
        Cybil_Init(chara);
    }

    Cybil_AnimStateUpdate(chara, boneCoords);
    Cybil_MovementUpdate(chara, boneCoords);
    Cybil_AnimUpdate(chara, anmHdr, boneCoords);
}

/** Addresses
 * MAP0_S01: 0x800D8888
 * MAP4_S01: 0x800CFE64
 * MAP6_S01: 0x800CE570
 * MAP7_S03: 0x800D110C
 */
void Cybil_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* animHdr, GsCOORDINATE2* boneCoords)
{
    s_AnimInfo* animInfo;

    if (chara->properties.player.field_F0 == 0)
    {
        animInfo = &CYBIL_ANIM_INFOS[chara->model.anim.status];
        animInfo->playbackFunc(&chara->model, animHdr, boneCoords, animInfo);
    }
}

/** Addresses
 * MAP0_S01: 0x800D88D0
 * MAP4_S01: 0x800CFEAC
 * MAP6_S01: 0x800CE5B8
 * MAP7_S03: 0x800D1154
 */
void Cybil_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* boneCoords)
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

    chara->position.vx += offset.vx;
    chara->position.vy  = Q12(0.0f);
    chara->position.vz += offset.vz;

    boneCoords->coord.t[0] = Q12_TO_Q8(chara->position.vx);
    boneCoords->coord.t[1] = Q12_TO_Q8(chara->position.vy);
    boneCoords->coord.t[2] = Q12_TO_Q8(chara->position.vz);
}

/** Addresses
 * MAP0_S01:
 * MAP4_S01:
 * MAP6_S01:
 * MAP7_S03:
 */
void Cybil_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* boneCoords)
{
    s_Collision coll;
    e_SfxId     sfx;
    s8          pitch0;
    s8          pitch1;

    #define dahliaProps (chara->properties.dahlia)

    switch (dahliaProps.controlState)
    {
        case CybilControl_None:
            if (dahliaProps.moveDistance_126)
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            Model_AnimStatusSet(&chara->model, CybilAnim_1, false);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_1:
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

#if defined(MAP0_S01)
            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_3, true, CYBIL_ANIM_INFOS, 0);
#else
            Model_AnimStatusSet(&chara->model, CybilAnim_3, false);
#endif
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_2:
            if (dahliaProps.moveDistance_126 > Q12(4.0f))
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f));
                if (dahliaProps.moveDistance_126 < Q12(4.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(4.0f);
                }
            }
            else if (dahliaProps.moveDistance_126 < Q12(4.0f))
            {
                dahliaProps.moveDistance_126 += TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.75f));
                dahliaProps.moveDistance_126 = CLAMP(dahliaProps.moveDistance_126, Q12(0.0f), Q12(4.0f));
            }

            // TODO: This uses `ANIM_STATUS(21, false)`, but then fetches `ANIM_STATUS(22, true)` keyframe.
            // Added `animInfosOffset` but maybe there's better way.
            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_21, false, CYBIL_ANIM_INFOS, 1);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_3:
            if (dahliaProps.moveDistance_126)
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            sharedData_800E2378_0_s01 = g_DeltaTime * 7;

            Model_AnimStatusSet(&chara->model, CybilAnim_4, false);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_4:
            if (dahliaProps.moveDistance_126)
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            sharedData_800E2378_0_s01 = g_DeltaTime * -7;

            Model_AnimStatusSet(&chara->model, CybilAnim_5, false);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_5:
            if (dahliaProps.moveDistance_126)
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_1, true, CYBIL_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_12:
            if (dahliaProps.moveDistance_126)
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            Model_AnimStatusSet(&chara->model, CybilAnim_1, false);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_6:
            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_7, true, CYBIL_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);

            if (chara->model.anim.keyframeIdx < 91)
            {
                WorldGfx_HeldItemAttach(Chara_Cybil, MODEL_BONE(1, 1));
            }
            else if (chara->model.anim.keyframeIdx < 105)
            {
                WorldGfx_HeldItemAttach(Chara_Cybil, MODEL_BONE(2, 1));
            }
            else
            {
                WorldGfx_HeldItemAttach(Chara_Cybil, MODEL_BONE(1, 2));
            }
            break;

        case CybilControl_7:
            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_8, true, CYBIL_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_8:
            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_9, true, CYBIL_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_9:
            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_10, true, CYBIL_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            WorldGfx_HeldItemAttach(Chara_Cybil, MODEL_BONE(1, 1));
            break;

        case CybilControl_10:
            Model_AnimStatusSet(&chara->model, CybilAnim_11, true);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_11:
            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_12, true, CYBIL_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_13:
            Model_AnimStatusSet(&chara->model, CybilAnim_13, false);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_14:
            Model_AnimStatusSet(&chara->model, CybilAnim_14, false);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_15:
            Model_AnimStatusSet(&chara->model, CybilAnim_15, false);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_16:
            Model_AnimStatusSet(&chara->model, CybilAnim_16, false);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_17:
            Model_AnimStatusSet(&chara->model, CybilAnim_17, false);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_18:
            Model_AnimStatusSet(&chara->model, CybilAnim_18, false);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_19:
            Model_AnimStatusSet(&chara->model, CybilAnim_19, false);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_20:
            Model_AnimStatusSet(&chara->model, CybilAnim_20, false);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_21:
            Model_AnimStatusSet(&chara->model, CybilAnim_26, false);
            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_26, true, CYBIL_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            WorldGfx_HeldItemAttach(Chara_EndingCybil, MODEL_BONE(2, 1));

            if (chara->model.anim.keyframeIdx == 295)
            {
                dahliaProps.controlState = 30;
                chara->model.stateStep = 0;
            }
            break;

        case CybilControl_22:
            Model_AnimStatusSet(&chara->model, CybilAnim_27, false);
            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_27, true, CYBIL_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            WorldGfx_HeldItemAttach(Chara_EndingCybil, MODEL_BONE(2, 1));
            break;

        case CybilControl_23:
            Model_AnimStatusSet(&chara->model, CybilAnim_28, false);
            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_28, true, CYBIL_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            WorldGfx_HeldItemAttach(Chara_EndingCybil, MODEL_BONE(2, 1));

            if (dahliaProps.controlState != 23)
            {
                dahliaProps.flags_11C &= ~(1 << 13);
            }
            break;

        case CybilControl_24:
            Model_AnimStatusSet(&chara->model, CybilAnim_29, false);
            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_29, true, CYBIL_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            WorldGfx_HeldItemAttach(Chara_EndingCybil, MODEL_BONE(2, 1));
            break;

        case CybilControl_25:
            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_22, true, CYBIL_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_26:
            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_23, true, CYBIL_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_27:
            Model_AnimStatusSet(&chara->model, CybilAnim_24, false);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_29:
            Model_AnimStatusSet(&chara->model, CybilAnim_30, false);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_28:
            Model_AnimStatusKeyframeSet(chara->model, CybilAnim_25, true, CYBIL_ANIM_INFOS, 0);
            Chara_AnimStateReset(chara);
            break;

        case CybilControl_30:
            Model_AnimStatusSet(&chara->model, CybilAnim_31, false);
            Chara_AnimStateReset(chara);
            WorldGfx_HeldItemAttach(Chara_EndingCybil, MODEL_BONE(2, 1));
            break;
    }

    Collision_Get(&coll, chara->position.vx, chara->position.vz);
    func_8007FDE0(coll.groundType, &sfx, &pitch0, &pitch1);

#if defined(MAP6_S01)
    sfx = Sfx_Unk1607;
#endif

    switch (dahliaProps.controlState)
    {
        case CybilControl_1:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_3, true), chara, 32, 45, sfx, pitch0);
            break;

        case CybilControl_2:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_21, true), chara, 18, 7, sfx, pitch1);
            break;

        case CybilControl_3:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_4, true), chara, 61, 57, sfx, pitch0);
            break;

        case CybilControl_4:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_5, true), chara, 70, 74, sfx, pitch1);
            break;

        case CybilControl_8:
            sharedFunc_800D9188_0_s00(chara->model.anim.status, chara, 128, Sfx_Unk1368);
            break;

        case CybilControl_6:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_7, true), chara, 83, 86, sfx, pitch0);
            sharedFunc_800D9188_0_s00(ANIM_STATUS(CybilAnim_7, true), chara, 92, Sfx_Unk1369);
            break;

        case CybilControl_13:
            if (chara->model.anim.keyframeIdx <= 185)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_13, true), chara, 185, 189, sfx, pitch0);
            }
            else if (chara->model.anim.keyframeIdx <= 192)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_13, true), chara, 192, 189, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_13, true), chara, 227, 222, sfx, pitch0);
            }
            break;

        case CybilControl_15:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_15, true), chara, 260, 260, sfx, pitch0);
            break;

        case CybilControl_14:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_14, true), chara, 239, 239, sfx, pitch0);
            break;

        case CybilControl_19:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_19, true), chara, 362, 357, sfx, pitch0);
            break;

        case CybilControl_20:
            if (chara->model.anim.keyframeIdx <= 373)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_20, true), chara, 373, 380, sfx, pitch0);
            }
            else if (chara->model.anim.keyframeIdx <= 391)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_20, true), chara, 391, 380, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_20, true), chara, 403, 398, sfx, pitch0);
            }
            break;

        case CybilControl_10:
            sharedFunc_800D9188_0_s00(chara->model.anim.status, chara, 167, Sfx_Unk1370);
            break;

        case CybilControl_25:
            if (chara->model.anim.keyframeIdx <= 63)
            {
                if (chara->model.anim.keyframeIdx <= 30)
                {
                    sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_22, true), chara, 30, 39, sfx, pitch0);
                }
                else if (chara->model.anim.keyframeIdx <= 46)
                {
                    sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_22, true), chara, 46, 39, sfx, pitch0);
                }
                else
                {
                    sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_22, true), chara, 63, 56, sfx, pitch0);
                }
            }
            else
            {
                if (chara->model.anim.keyframeIdx <= 81)
                {
                    sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_22, true), chara, 81, 74, sfx, pitch0);
                }
                else
                {
                    sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_22, true), chara, 97, 91, sfx, pitch0);
                }
            }
            break;

        case CybilControl_28:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_25, true), chara, 201, 198, sfx, pitch0);

            if (sharedFunc_800D9188_0_s00(chara->model.anim.status, chara, 228, Sfx_Unk1699))
            {
                func_800892A4(6);
            }
            break;

        case CybilControl_22:
            if (sharedData_800E237C_0_s01 == 1)
            {
                func_8005DC1C(Sfx_Unk1673, &g_SysWork.npcs[1].position, Q8(0.75f), 0);
                sharedData_800E237C_0_s01 = 2;
            }

            if (chara->model.anim.keyframeIdx == 299)
            {
                if (sharedData_800E237C_0_s01 == 0)
                {
                    func_8006342C(EquippedWeaponId_Unk63, Q12_ANGLE(90.0f), chara->rotation.vy, &g_SysWork.npcBoneCoords[0]);
                    func_8005DC1C(Sfx_Unk1622, &chara->position, Q8(0.75f), 0);
                    sharedData_800E237C_0_s01 = 1;
                }
            }
            break;

        case CybilControl_24:
            sharedFunc_800D9188_0_s00(ANIM_STATUS(CybilAnim_29, true), chara, 327, Sfx_Unk1672);
            break;

        case CybilControl_21:
            sharedFunc_800D9188_0_s00(ANIM_STATUS(CybilAnim_26, true), chara, 282, Sfx_Unk1539);
            break;
    }

    chara->rotation.vy  = Q12_ANGLE_ABS(chara->rotation.vy + (sharedData_800E2378_0_s01 >> 4));
    chara->headingAngle = chara->rotation.vy;
    chara->moveSpeed    = dahliaProps.moveDistance_126;
    chara->fallSpeed   += g_GravitySpeed;

    boneCoords->flg = false;
    Math_RotMatrixZxyNegGte(&chara->rotation, &boneCoords->coord);
}

/** Addresses
 * MAP0_S01: 0x800D9AD0
 * MAP4_S01: 0x800D1084
 * MAP6_S01: 0x800CF794
 * MAP7_S03: 0x800D232C
 */
void Cybil_Init(s_SubCharacter* chara)
{
    Chara_CollisionReset(chara);
    sharedData_800E2378_0_s01 = 0;
    sharedData_800E237C_0_s01 = 0;

#ifdef MAP7_S03
    WorldGfx_HeldItemAttach(Chara_EndingCybil, MODEL_BONE(1, 1));
#else
    WorldGfx_HeldItemAttach(Chara_Cybil, MODEL_BONE(1, 1));
#endif
}
