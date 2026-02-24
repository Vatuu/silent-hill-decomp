#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "maps/shared.h"
#include "maps/characters/kaufmann.h"

/** AI code for `Chara_Kaufmann`
 *
 * Included in:
 *  MAP3_S00
 *  MAP5_S02
 *  MAP5_S03
 *  MAP7_S02
 *  MAP7_S03
 */

/** Addresses
 * MAP3_S00: 0x800CF21C
 * MAP5_S02: 0x800D2EA8
 * MAP5_S03: 0x800CF8DC
 * MAP7_S02: 0x800D7EAC
 * MAP7_S03: 0x800D3F58
 */
void Ai_Kaufmann_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (chara->model_0.controlState_2 == ModelState_Uninitialized)
    {
        Ai_Kaufmann_Init(chara);
    }

    Ai_Kaufmann_AnimStateUpdate(chara, coords);
    Ai_Kaufmann_MovementUpdate(chara, coords);
    Ai_Kaufmann_AnimUpdate(chara, anmHdr, coords);
}

/** Addresses
 * MAP3_S00: 0x800CF290
 * MAP5_S02: 0x800D2F1C
 * MAP5_S03: 0x800CF950
 * MAP7_S02: 0x800D7F20
 * MAP7_S03: 0x800D3FCC
 */
void Ai_Kaufmann_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;

    if (chara->properties_E4.player.field_F0 == 0)
    {
        animInfo = &KAUFMANN_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
    }
}

/** Addresses
 * MAP3_S00: 0x800CF2D8
 * MAP5_S02: 0x800D2F64
 * MAP5_S03: 0x800CF998
 * MAP7_S02: 0x800D7F68
 * MAP7_S03: 0x800D4014
 */
void Ai_Kaufmann_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords)
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
 * MAP3_S00: 0x800CF470
 * MAP5_S02: 0x800D30FC
 * MAP5_S03: 0x800CFB30
 * MAP7_S02: 0x800D8100
 * MAP7_S03: 0x800D41AC
 */
void Ai_Kaufmann_AnimStateUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords)
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

            Model_AnimStatusSet(&chara->model_0, 1, false);
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

            Model_AnimStatusSet(&chara->model_0, 3, false);
            Character_AnimStateReset(chara);
#if defined(MAP5_S03)
            WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(4, 3));
#endif
            break;

        case 5:
            Model_AnimStatusKeyframeSet(chara->model_0, 1, true, KAUFMANN_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
            WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(1, 0));
            break;

        case 24:
            Model_AnimStatusKeyframeSet(chara->model_0, 20, true, KAUFMANN_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
#if defined(MAP5_S03)
            WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(4, 3));
#else
            WorldGfx_HeldItemAttach(Chara_EndingKaufmann, MODEL_BONE(1, 3));
#endif
            break;

        case 6:
            Model_AnimStatusKeyframeSet(chara->model_0, 4, true, KAUFMANN_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
#if defined(MAP3_S00)
            WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(3, 1));
#endif
            break;

        case 7:
            if (chara->model_0.anim_4.keyframeIdx_8 >= 95 && g_SysWork.npcs_1A0[0].properties_E4.dahlia.properties_120.val32 == 0)
            {
                g_SysWork.npcs_1A0[0].properties_E4.dahlia.properties_120.val32 = 1;
                func_8006342C(70, 0, 0, &g_SysWork.npcCoords_FC0[0]);
            }

            Model_AnimStatusSet(&chara->model_0, 5, false);
            Character_AnimStateReset(chara);
#if defined(MAP3_S00)
            WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(3, 1));
#endif
            break;

        case 8:
            Model_AnimStatusSet(&chara->model_0, 6, false);
            Character_AnimStateReset(chara);
#if defined(MAP3_S00)
            WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(3, 1));
#endif
            break;

        case 9:
            Model_AnimStatusSet(&chara->model_0, 7, false);
            Character_AnimStateReset(chara);
            if (chara->model_0.anim_4.keyframeIdx_8 < 139 || !ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0))
            {
                WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(1, 1));
            }
            else
            {
                Savegame_EventFlagSet(EventFlag_198);
                WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(1, 3));
            }
            break;

        case 10:
            Model_AnimStatusSet(&chara->model_0, 8, false);
            Character_AnimStateReset(chara);
            break;

        case 11:
            Model_AnimStatusKeyframeSet(chara->model_0, 9, true, KAUFMANN_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
#if defined(MAP5_S02)
            WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(1, 1));
#endif
            break;

        case 12:
            Model_AnimStatusKeyframeSet(chara->model_0, 22, true, KAUFMANN_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
#if defined(MAP5_S02)
            WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(1, 1));
#endif
            break;

        case 13:
            Model_AnimStatusSet(&chara->model_0, 10, false);
            Character_AnimStateReset(chara);
#if defined(MAP5_S02)
            WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(1, 1));
#endif
            break;

        case 14:
            Model_AnimStatusSet(&chara->model_0, 11, false);
            Character_AnimStateReset(chara);
#if defined(MAP5_S02)
            WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(1, 1));
#endif
            break;

        case 15:
            Model_AnimStatusSet(&chara->model_0, 12, false);
            Character_AnimStateReset(chara);

            if (chara->model_0.anim_4.keyframeIdx_8 >= 364 && ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0))
            {
                WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(4, 0));
            }
            break;

        case 16:
            Model_AnimStatusSet(&chara->model_0, 2, false);
            Character_AnimStateReset(chara);
#if defined(MAP5_S03)
            WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(1, 3));
#endif
            break;

        case 25:
            Model_AnimStatusSet(&chara->model_0, 21, false);
            Character_AnimStateReset(chara);
            WorldGfx_HeldItemAttach(Chara_EndingKaufmann, MODEL_BONE(3, 3));
            break;

        case 17:
            Model_AnimStatusSet(&chara->model_0, 13, false);
            Character_AnimStateReset(chara);
            break;

        case 18:
            Model_AnimStatusSet(&chara->model_0, 16, false);
            Character_AnimStateReset(chara);

#if defined(MAP7_S03)
            // TODO: Invert like case 15? can't find how to match.
            if (chara->model_0.anim_4.keyframeIdx_8 < 78 || !ANIM_STATUS_IS_ACTIVE(chara->model_0.anim_4.status_0))
            {
                WorldGfx_HeldItemAttach(Chara_EndingKaufmann, MODEL_BONE(1, 3));
            }
            else
            {
                WorldGfx_HeldItemAttach(Chara_EndingKaufmann, MODEL_BONE(4, 3));
            }
#endif
            break;

        case 19:
            Model_AnimStatusSet(&chara->model_0, 17, false);
            Character_AnimStateReset(chara);
#if defined(MAP7_S03)
            WorldGfx_HeldItemAttach(Chara_EndingKaufmann, MODEL_BONE(4, 3));
#endif
            break;

        case 20:
            Model_AnimStatusKeyframeSet(chara->model_0, 18, true, KAUFMANN_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);

#if defined(MAP7_S03)
            if (chara->model_0.anim_4.keyframeIdx_8 < 141)
            {
                WorldGfx_HeldItemAttach(Chara_EndingKaufmann, MODEL_BONE(4, 3));
            }
            else
            {
                WorldGfx_HeldItemAttach(Chara_EndingKaufmann, MODEL_BONE(1, 3));
            }
#endif
            break;

        case 21:
            Model_AnimStatusSet(&chara->model_0, 15, false);
            Character_AnimStateReset(chara);

#if defined(MAP7_S03)
            WorldGfx_HeldItemAttach(Chara_EndingKaufmann, MODEL_BONE(1, 1));
#endif
            break;

        case 22:
            Model_AnimStatusKeyframeSet(chara->model_0, 19, true, KAUFMANN_ANIM_INFOS, 0);
            Character_AnimStateReset(chara);
#if defined(MAP7_S03)
            WorldGfx_HeldItemAttach(Chara_EndingKaufmann, MODEL_BONE(1, 3));
#endif
            break;

        case 23:
            Model_AnimStatusSet(&chara->model_0, 14, false);
            Character_AnimStateReset(chara);
            break;
    }

    Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);

    switch (dahliaProps.stateIdx0)
    {
        case 1:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(3, true), chara, 53, 41, sfx, pitch0);
            break;

        case 6:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(4, true), chara, 80, 0, sfx, pitch0);
            break;

        case 7:
            sharedFunc_800D9188_0_s00(chara->model_0.anim_4.status_0, chara, 95, Sfx_Unk1492);
            break;

        case 9:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(7, true), chara, 132, 174, sfx, pitch0);
            break;

        case 10:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(8, true), chara, 191, 0, sfx, pitch0);
            break;

        case 17:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(13, true), chara, 393, 0, sfx, pitch0);
            break;

        case 13:
            sharedFunc_800D9188_0_s00(ANIM_STATUS(10, true), chara, 307, Sfx_Unk1594);
            break;

        case 15:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 353)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(12, true), chara, 357, 353, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(12, true), chara, 357, 361, sfx, pitch0);
            }
            break;

        case 16:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 21)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(2, true), chara, 28, 21, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(2, true), chara, 28, 34, sfx, pitch0);
            }
            break;

        case 25:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 247)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(21, true), chara, 254, 247, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(21, true), chara, 254, 260, sfx, pitch0);
            }
            break;

        case 22:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 211)
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(19, true), chara, 217, 211, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(ANIM_STATUS(19, true), chara, 217, 221, sfx, pitch0);
            }
            break;
    }

    chara->rotation_24.vy  = Q12_ANGLE_ABS(chara->rotation_24.vy + (sharedData_800D5CF4_3_s00 >> 4));
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->moveSpeed_38    = dahliaProps.moveDistance_126;
    chara->fallSpeed_34   += g_GravitySpeed;

    coords->flg = false;
    Math_RotMatrixZxyNegGte(&chara->rotation_24, &coords->coord);
}

/** Addresses
 * MAP3_S00: 0x800CFE48
 * MAP5_S02: 0x800D3AC0
 * MAP5_S03: 0x800D0510
 * MAP7_S02: 0x800D8AA8
 * MAP7_S03: 0x800D4C14
 */
void Ai_Kaufmann_Init(s_SubCharacter* chara)
{
    sharedFunc_800D923C_0_s00(chara);

    g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[14].val32 = 0; // TODO: Change to `properties_E4.humanoid`?

    sharedData_800D5CF4_3_s00 = 0;

#ifdef MAP7_S03
    WorldGfx_HeldItemAttach(Chara_EndingKaufmann, MODEL_BONE(0, 1)); // TODO: MAP7_S03 `Ai_Kaufmann` funcs could be `Ai_EndingKaufmann` instead, if other `Ai_Kaufmann` funcs don't match other overlays.
#else
    WorldGfx_HeldItemAttach(Chara_Kaufmann, MODEL_BONE(0, 1));
#endif

#ifdef MAP7_S02
    WorldGfx_CharaModelTransparentSet(Chara_Kaufmann, true);
#endif
}
