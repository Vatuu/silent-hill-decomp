#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
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
void Ai_Cybil_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (chara->model_0.controlState_2 == ModelState_Uninitialized)
    {
        Ai_Cybil_Init(chara);
    }

    Ai_Cybil_AnimStateUpdate(chara, coords);
    Ai_Cybil_MovementUpdate(chara, coords);
    Ai_Cybil_AnimUpdate(chara, anmHdr, coords);
}

/** Addresses
 * MAP0_S01: 0x800D8888
 * MAP4_S01: 0x800CFE64
 * MAP6_S01: 0x800CE570
 * MAP7_S03: 0x800D110C
 */
void Ai_Cybil_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* animHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;

    if (chara->properties_E4.player.field_F0 == 0)
    {
        animInfo = &CYBIL_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, animHdr, coords, animInfo);
    }
}

/** Addresses
 * MAP0_S01: 0x800D88D0
 * MAP4_S01: 0x800CFEAC
 * MAP6_S01: 0x800CE5B8
 * MAP7_S03: 0x800D1154
 */
void Ai_Cybil_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    VECTOR3 unused;
    VECTOR3 offset;
    q19_12  moveSpeed;
    q3_12   headingAngle;
    q19_12  moveAmt;
    s32     scaleRestoreShift;
    u32     scaleReduceShift;

    unused       = chara->position_18;
    moveSpeed    = chara->moveSpeed_38;
    headingAngle = chara->headingAngle_3C;
    moveAmt      = Q12_MULT_PRECISE(moveSpeed, g_DeltaTime);

    scaleRestoreShift = OVERFLOW_GUARD(moveAmt);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = (u32)Q12_MULT_PRECISE(moveAmt >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vz = (u32)Q12_MULT_PRECISE(moveAmt >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vy = Q12_MULT_PRECISE(chara->fallSpeed_34, g_DeltaTime);

    chara->position_18.vx += offset.vx;
    chara->position_18.vy  = Q12(0.0f);
    chara->position_18.vz += offset.vz;

    coords->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coords->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coords->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);
}

/** Addresses
 * MAP0_S01:
 * MAP4_S01:
 * MAP6_S01:
 * MAP7_S03:
 */
void Ai_Cybil_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    s_Collision coll;
    e_SfxId     sfx;
    s8          pitch0;
    s8          pitch1;

    #define dahliaProps (chara->properties_E4.dahlia)

    switch (dahliaProps.stateIdx0)
    {
        case 0:
            if (dahliaProps.moveDistance_126)
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            Model_AnimStatusSet(&chara->model_0, CybilAnim_1, false);
            Character_AnimStateReset(chara);
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

#if defined(MAP0_S01)
            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_3, true, CYBIL_ANIM_INFOS, 0);
#else
            Model_AnimStatusSet(&chara->model_0, CybilAnim_3, false);
#endif
            Character_AnimStateReset(chara);
            break;

        case 2:
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
            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_21, false, CYBIL_ANIM_INFOS, 1);
            Character_AnimStateReset(chara);
            break;

        case 3:
            if (dahliaProps.moveDistance_126)
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            sharedData_800E2378_0_s01 = g_DeltaTime * 7;

            Model_AnimStatusSet(&chara->model_0, CybilAnim_4, false);
            Character_AnimStateReset(chara);
            break;

        case 4:
            if (dahliaProps.moveDistance_126)
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            sharedData_800E2378_0_s01 = g_DeltaTime * -7;

            Model_AnimStatusSet(&chara->model_0, CybilAnim_5, false);
            Character_AnimStateReset(chara);
            break;

        case 5:
            if (dahliaProps.moveDistance_126)
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_1, true, CYBIL_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            break;

        case 12:
            if (dahliaProps.moveDistance_126)
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE_30_FPS(g_DeltaTime, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < Q12(0.0f))
                {
                    dahliaProps.moveDistance_126 = Q12(0.0f);
                }
            }

            Model_AnimStatusSet(&chara->model_0, CybilAnim_1, false);
            Character_AnimStateReset(chara);
            break;

        case 6:
            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_7, true, CYBIL_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);

            if (chara->model_0.anim_4.keyframeIdx_8 < 91)
            {
                WorldGfx_HeldItemAttach(Chara_Cybil, MODEL_BONE(1, 1));
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 < 105)
            {
                WorldGfx_HeldItemAttach(Chara_Cybil, MODEL_BONE(2, 1));
            }
            else
            {
                WorldGfx_HeldItemAttach(Chara_Cybil, MODEL_BONE(1, 2));
            }
            break;

        case 7:
            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_8, true, CYBIL_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            break;

        case 8:
            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_9, true, CYBIL_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            break;

        case 9:
            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_10, true, CYBIL_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            WorldGfx_HeldItemAttach(Chara_Cybil, MODEL_BONE(1, 1));
            break;

        case 10:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_11, true);
            Character_AnimStateReset(chara);
            break;

        case 11:
            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_12, true, CYBIL_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            break;

        case 13:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_13, false);
            Character_AnimStateReset(chara);
            break;

        case 14:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_14, false);
            Character_AnimStateReset(chara);
            break;

        case 15:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_15, false);
            Character_AnimStateReset(chara);
            break;

        case 16:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_16, false);
            Character_AnimStateReset(chara);
            break;

        case 17:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_17, false);
            Character_AnimStateReset(chara);
            break;

        case 18:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_18, false);
            Character_AnimStateReset(chara);
            break;

        case 19:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_19, false);
            Character_AnimStateReset(chara);
            break;

        case 20:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_20, false);
            Character_AnimStateReset(chara);
            break;

        case 21:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_26, false);
            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_26, true, CYBIL_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            WorldGfx_HeldItemAttach(Chara_EndingCybil, MODEL_BONE(2, 1));

            if (chara->model_0.anim_4.keyframeIdx_8 == 295)
            {
                dahliaProps.stateIdx0 = 30;
                chara->model_0.stateStep_3 = 0;
            }
            break;

        case 22:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_27, false);
            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_27, true, CYBIL_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            WorldGfx_HeldItemAttach(Chara_EndingCybil, MODEL_BONE(2, 1));
            break;

        case 23:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_28, false);
            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_28, true, CYBIL_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            WorldGfx_HeldItemAttach(Chara_EndingCybil, MODEL_BONE(2, 1));

            if (dahliaProps.stateIdx0 != 23)
            {
                dahliaProps.flags_11C &= ~(1 << 13);
            }
            break;

        case 24:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_29, false);
            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_29, true, CYBIL_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            WorldGfx_HeldItemAttach(Chara_EndingCybil, MODEL_BONE(2, 1));
            break;

        case 25:
            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_22, true, CYBIL_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            break;

        case 26:
            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_23, true, CYBIL_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            break;

        case 27:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_24, false);
            Character_AnimStateReset(chara);
            break;

        case 29:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_30, false);
            Character_AnimStateReset(chara);
            break;

        case 28:
            Model_AnimStatusKeyframeSet(chara->model_0, CybilAnim_25, true, CYBIL_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            break;

        case 30:
            Model_AnimStatusSet(&chara->model_0, CybilAnim_31, false);
            Character_AnimStateReset(chara);
            WorldGfx_HeldItemAttach(Chara_EndingCybil, MODEL_BONE(2, 1));
            break;
    }

    Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);

#if defined(MAP6_S01)
    sfx = Sfx_Unk1607;
#endif

    switch (dahliaProps.stateIdx0)
    {
        case 1:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_3, true), chara, 32, 45, sfx, pitch0);
            break;

        case 2:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_21, true), chara, 18, 7, sfx, pitch1);
            break;

        case 3:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_4, true), chara, 61, 57, sfx, pitch0);
            break;

        case 4:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_5, true), chara, 70, 74, sfx, pitch1);
            break;

        case 8:
            sharedFunc_800D9188_0_s00(chara->model_0.anim_4.status_0, chara, 128, Sfx_Unk1368);
            break;

        case 6:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_7, true), chara, 83, 86, sfx, pitch0);
            sharedFunc_800D9188_0_s00(ANIM_STATUS(CybilAnim_7, true), chara, 92, Sfx_Unk1369);
            break;

        case 13:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 185)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_13, true), chara, 185, 189, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 <= 192)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_13, true), chara, 192, 189, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_13, true), chara, 227, 222, sfx, pitch0);
            }
            break;

        case 15:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_15, true), chara, 260, 260, sfx, pitch0);
            break;

        case 14:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_14, true), chara, 239, 239, sfx, pitch0);
            break;

        case 19:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_19, true), chara, 362, 357, sfx, pitch0);
            break;

        case 20:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 373)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_20, true), chara, 373, 380, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 <= 391)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_20, true), chara, 391, 380, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_20, true), chara, 403, 398, sfx, pitch0);
            }
            break;

        case 10:
            sharedFunc_800D9188_0_s00(chara->model_0.anim_4.status_0, chara, 167, Sfx_Unk1370);
            break;

        case 25:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 63)
            {
                if (chara->model_0.anim_4.keyframeIdx_8 <= 30)
                {
                    sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_22, true), chara, 30, 39, sfx, pitch0);
                }
                else if (chara->model_0.anim_4.keyframeIdx_8 <= 46)
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
                if (chara->model_0.anim_4.keyframeIdx_8 <= 81)
                {
                    sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_22, true), chara, 81, 74, sfx, pitch0);
                }
                else
                {
                    sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_22, true), chara, 97, 91, sfx, pitch0);
                }
            }
            break;

        case 28:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(CybilAnim_25, true), chara, 201, 198, sfx, pitch0);

            if (sharedFunc_800D9188_0_s00(chara->model_0.anim_4.status_0, chara, 228, Sfx_Unk1699))
            {
                func_800892A4(6);
            }
            break;

        case 22:
            if (sharedData_800E237C_0_s01 == 1)
            {
                func_8005DC1C(Sfx_Unk1673, &g_SysWork.npcs_1A0[1].position_18, Q8_CLAMPED(0.75f), 0);
                sharedData_800E237C_0_s01 = 2;
            }

            if (chara->model_0.anim_4.keyframeIdx_8 == 299)
            {
                if (sharedData_800E237C_0_s01 == 0)
                {
                    func_8006342C(63, 1024, chara->rotation_24.vy, &g_SysWork.npcCoords_FC0[0]);
                    func_8005DC1C(Sfx_Unk1622, &chara->position_18, Q8_CLAMPED(0.75f), 0);
                    sharedData_800E237C_0_s01 = 1;
                }
            }
            break;

        case 24:
            sharedFunc_800D9188_0_s00(ANIM_STATUS(CybilAnim_29, true), chara, 327, Sfx_Unk1672);
            break;

        case 21:
            sharedFunc_800D9188_0_s00(ANIM_STATUS(CybilAnim_26, true), chara, 282, Sfx_Unk1539);
            break;
    }

    chara->rotation_24.vy  = Q12_ANGLE_ABS(chara->rotation_24.vy + (sharedData_800E2378_0_s01 >> 4));
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->moveSpeed_38    = dahliaProps.moveDistance_126;
    chara->fallSpeed_34   += g_GravitySpeed;

    coords->flg = false;
    Math_RotMatrixZxyNegGte(&chara->rotation_24, &coords->coord);
}

/** Addresses
 * MAP0_S01: 0x800D9AD0
 * MAP4_S01: 0x800D1084
 * MAP6_S01: 0x800CF794
 * MAP7_S03: 0x800D232C
 */
void Ai_Cybil_Init(s_SubCharacter* chara)
{
    sharedFunc_800D923C_0_s00(chara);
    sharedData_800E2378_0_s01 = 0;
    sharedData_800E237C_0_s01 = 0;

#ifdef MAP7_S03
    WorldGfx_HeldItemAttach(Chara_EndingCybil, MODEL_BONE(1, 1));
#else
    WorldGfx_HeldItemAttach(Chara_Cybil, MODEL_BONE(1, 1));
#endif
}
