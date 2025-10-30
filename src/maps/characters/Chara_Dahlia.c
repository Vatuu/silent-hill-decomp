#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/Chara_Dahlia.h"

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
 
#if defined(MAP2_S01) || defined(MAP3_S06)
#define ANIM_TABLE KAUFMANN_ANIM_INFOS
#else
#define ANIM_TABLE DAHLIA_ANIM_INFOS
#endif

extern s_AnimInfo ANIM_TABLE[];

/** Addresses
 * MAP2_S01: 0x800CD20C
 * MAP3_S06: 0x800CF0F8
 * MAP6_S01: 0x800CF7D0
 * MAP6_S04: 0x800DCA30
 * MAP7_S02: 0x800D6ED4
 * MAP7_S03: 0x800D2368
 */
void Ai_Dahlia_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Dahlia_Init(chara);
    }

    Ai_Dahlia_AnimStateUpdate(chara, coords);
    Ai_Dahlia_MovementUpdate(chara, coords);
    Ai_Dahlia_AnimUpdate(chara, anmHdr, coords);
}

/** Addresses
 * MAP2_S01: 0x800CD280
 * MAP3_S06: 0x800CF16C
 * MAP6_S01: 0x800CF844
 * MAP6_S04: 0x800DCAA4
 * MAP7_S02: 0x800D6F48
 * MAP7_S03: 0x800D23DC
 */
void Ai_Dahlia_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;

    if (!chara->properties_E4.player.field_F0)
    {
        animInfo = &ANIM_TABLE[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
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
void Ai_Dahlia_MovementUpdate(s_SubCharacter* chara, GsCOORDINATE2* coords)
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
    moveAmt      = FP_MULTIPLY_PRECISE(moveSpeed, g_DeltaTime0, Q12_SHIFT);

    scaleRestoreShift = OVERFLOW_GUARD(moveAmt);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = (u32)FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    offset.vz = (u32)FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    offset.vy = FP_MULTIPLY_PRECISE(chara->field_34, g_DeltaTime0, Q12_SHIFT);

    func_80069B24(&sharedData_800E39BC_0_s00, &offset, chara);

    chara->position_18.vx += offset.vx;
    chara->position_18.vy  = Q12(0.0f);
    chara->position_18.vz += offset.vz;

    if (chara->position_18.vy > sharedData_800E39BC_0_s00.field_C)
    {
        chara->position_18.vy = sharedData_800E39BC_0_s00.field_C;
        chara->field_34       = 0;
    }

    coords->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coords->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coords->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);
}

/** Addresses
 * MAP2_S01: 0x800CD4A0
 * MAP3_S06: 0x800CF38C
 * MAP6_S01: 0x800CFA64
 * MAP6_S04: 0x800DCCC4
 * MAP7_S02: 0x800D7168
 * MAP7_S03: 0x800D25FC
 */
void Ai_Dahlia_AnimStateUpdate(s_SubCharacter* dahlia, GsCOORDINATE2* coords)
{
    s_Collision coll;
    s32         sfx;
    s8          pitch0;
    s8          pitch1;

    #define dahliaProps dahlia->properties_E4.dahlia

    switch (dahliaProps.stateIdx0)
    {
        case 0:
        case 5:
            if (dahliaProps.moveDistance_126)
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE(g_DeltaTime0, Q12(0.4f)) * 2;
                if (dahliaProps.moveDistance_126 < 0)
                {
                    dahliaProps.moveDistance_126 = 0;
                }
            }

            Model_AnimStatusSet(&dahlia->model_0, 1, false);
            Character_AnimStateReset(dahlia);
            break;

        case 1:
            if (dahliaProps.moveDistance_126 > Q12(1.25f))
            {
                dahliaProps.moveDistance_126 -= TIMESTEP_SCALE(g_DeltaTime0, Q12(0.5f));
                if (dahliaProps.moveDistance_126 < Q12(1.25f))
                {
                    dahliaProps.moveDistance_126 = Q12(1.25f);
                }
            }
            else if (dahliaProps.moveDistance_126 < Q12(1.25f))
            {
                dahliaProps.moveDistance_126 += TIMESTEP_SCALE(g_DeltaTime0, Q12(0.4f));
                dahliaProps.moveDistance_126  = CLAMP(dahliaProps.moveDistance_126, 0, Q12(1.25f));
            }

            Model_AnimStatusSet(&dahlia->model_0, 2, false);
            Character_AnimStateReset(dahlia);
            break;

        case 6:
            Model_AnimStatusSet(&dahlia->model_0, 14, false);
#if defined(MAP7_S03)
            func_8003DD80(Chara_EndingDahlia, 1);
#endif
            Character_AnimStateReset(dahlia);
            break;

        case 7:
            Model_AnimStatusSet(&dahlia->model_0, 3, false);
            Character_AnimStateReset(dahlia);
            break;

        case 8:
            Model_AnimStatusSet(&dahlia->model_0, 4, false);
            Character_AnimStateReset(dahlia);
            break;

        case 11:
#if defined(MAP3_S06) || defined(MAP6_S01) || defined(MAP6_S04) || defined(MAP7_S02) || defined(MAP7_S03)
            Model_AnimStatusKeyframeSet(dahlia->model_0, 7, true, ANIM_TABLE, 0);
#else
            Model_AnimStatusSet(&dahlia->model_0, 7, false);
#endif
            Character_AnimStateReset(dahlia);
            break;

        case 9:
            Model_AnimStatusSet(&dahlia->model_0, 5, false);
            Character_AnimStateReset(dahlia);

            if (dahlia->model_0.anim_4.keyframeIdx_8 < 144)
            {
                func_8003DD80(Chara_Dahlia, 1);
            }
            else
            {
#if !defined(MAP6_S01) && !defined(MAP6_S04) && !defined(MAP7_S02) && !defined(MAP7_S03)
#if defined(MAP3_S06)
                func_8003DD80(Chara_Dahlia, 2);
#else
                func_8003DD80(Chara_Dahlia, 3);
#endif
#endif
            }
            break;

        case 10:
#if !defined(MAP6_S01) && !defined(MAP6_S04) && !defined(MAP7_S02) && !defined(MAP7_S03)
#if defined(MAP3_S06)
            Model_AnimStatusKeyframeSet(dahlia->model_0, 6, true, ANIM_TABLE, 0);
#else
            Model_AnimStatusSet(&dahlia->model_0, 6, false);
#endif
#endif
            Character_AnimStateReset(dahlia);

            if (dahlia->model_0.anim_4.keyframeIdx_8 < 198)
            {
#if !defined(MAP6_S01) && !defined(MAP6_S04) && !defined(MAP7_S02) && !defined(MAP7_S03)
#if defined(MAP3_S06)
                func_8003DD80(Chara_Dahlia, 2);
#else
                func_8003DD80(Chara_Dahlia, 3);
#endif
#endif
            }
            else
            {
                func_8003DD80(Chara_Dahlia, 1);
            }
            break;

        case 12:
            Model_AnimStatusKeyframeSet(dahlia->model_0, 8, true, ANIM_TABLE, 0);
            Character_AnimStateReset(dahlia);
            break;

        case 13:
            Model_AnimStatusSet(&dahlia->model_0, 9, false);
            Character_AnimStateReset(dahlia);
            break;

        case 14:
            Model_AnimStatusSet(&dahlia->model_0, 10, false);
            Character_AnimStateReset(dahlia);
            break;

        case 15:
            Model_AnimStatusSet(&dahlia->model_0, 15, false);
            Character_AnimStateReset(dahlia);
            break;

        case 16:
            Model_AnimStatusSet(&dahlia->model_0, 16, false);
            Character_AnimStateReset(dahlia);

            if (dahlia->model_0.anim_4.keyframeIdx_8 == 103)
            {
                dahliaProps.stateIdx0      = 5;
                dahlia->model_0.stateStep_3 = 0;
            }
            break;

        case 17:
            Model_AnimStatusSet(&dahlia->model_0, 17, false);
            Character_AnimStateReset(dahlia);
            break;

        case 18:
            Model_AnimStatusSet(&dahlia->model_0, 18, false);
            Character_AnimStateReset(dahlia);
            break;

        case 19:
            if (dahlia->model_0.anim_4.keyframeIdx_8 >= 40 && !sharedData_800D16E4_2_s01)
            {
                func_8005F6B0(&g_SysWork.npcs_1A0[1], &(VECTOR3){ Q12(138.3f), Q12(-1.1f), Q12(-100.8f) }, 3, 1);
                sharedData_800D16E4_2_s01 = 1;
            }

            Model_AnimStatusKeyframeSet(dahlia->model_0, 19, true, ANIM_TABLE, 0);
            Character_AnimStateReset(dahlia);

            if (dahliaProps.stateIdx0 != 19)
            {
                sharedData_800D16E4_2_s01 = 0;
            }
            break;

        case 20:
            Model_AnimStatusSet(&dahlia->model_0, 20, false);
            Character_AnimStateReset(dahlia);
            break;

        case 21:
            Model_AnimStatusKeyframeSet(dahlia->model_0, 21, true, ANIM_TABLE, 0);
            Character_AnimStateReset(dahlia);
            break;

        case 22:
            Model_AnimStatusKeyframeSet(dahlia->model_0, 22, true, ANIM_TABLE, 0);
            Character_AnimStateReset(dahlia);
            break;

        case 23:
            Model_AnimStatusSet(&dahlia->model_0, 23, false);
            Character_AnimStateReset(dahlia);
            break;

        case 24:
            Model_AnimStatusSet(&dahlia->model_0, 24, false);
            Character_AnimStateReset(dahlia);
            break;

        case 25:
            Model_AnimStatusSet(&dahlia->model_0, 11, false);
            func_8003DD80(Chara_Dahlia, 1);

            if (dahlia->model_0.anim_4.keyframeIdx_8 == 349)
            {
                dahliaProps.stateIdx0       = 26;
                dahlia->model_0.stateStep_3 = 0;
                break;
            }
            break;

        case 26:
            Model_AnimStatusSet(&dahlia->model_0, 12, false);
            Character_AnimStateReset(dahlia);
            break;

        case 27:
            Model_AnimStatusSet(&dahlia->model_0, 13, false);
            Character_AnimStateReset(dahlia);
            break;

        case 28:
            Model_AnimStatusSet(&dahlia->model_0, 25, false);
            Character_AnimStateReset(dahlia);
            break;
    }

    Collision_Get(&coll, dahlia->position_18.vx, dahlia->position_18.vz);

    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);
#if defined(MAP6_S01)
    sfx = Sfx_Unk1606;
#else
    sfx = Sfx_Unk1489;
#endif

    switch (dahliaProps.stateIdx0)
    {
        case 1:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(2, true), dahlia, 24, 37, sfx, pitch0);
            break;

        case 8:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(4, true), dahlia, 107, 98, sfx, pitch0);
            break;

        case 11:
            sharedFunc_800D908C_0_s00(ANIM_STATUS(7, true), dahlia, 235, 245, sfx, pitch0);
            break;

        case 7:
            if (dahlia->model_0.anim_4.keyframeIdx_8 < 47)
            {
                sharedFunc_800D9188_0_s00(dahlia->model_0.anim_4.status_0, dahlia, 46, Sfx_Unk1674);
            }
            else
            {
                sharedFunc_800D9188_0_s00(dahlia->model_0.anim_4.status_0, dahlia, 47, Sfx_Unk1675);
            }
            break;

        default:
            break;

        case 17:
            if (dahlia->model_0.anim_4.keyframeIdx_8 < 127)
            {
                sharedFunc_800D9188_0_s00(ANIM_STATUS(17, true), dahlia, 120, Sfx_Unk1674);
            }
            else
            {
                sharedFunc_800D9188_0_s00(ANIM_STATUS(17, true), dahlia, 127, Sfx_Unk1675);
            }
            break;

        case 10:
            if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP2_S01)
            {
                sharedFunc_800D9188_0_s00(dahlia->model_0.anim_4.status_0, dahlia, 193, Sfx_Unk1488);
            }
            else
            {
                sharedFunc_800D9188_0_s00(dahlia->model_0.anim_4.status_0, dahlia, 193, Sfx_Unk1496);
            }
            break;

        case 14:
            if (dahlia->model_0.anim_4.keyframeIdx_8 < 310)
            {
                sharedFunc_800D908C_0_s00(dahlia->model_0.anim_4.status_0, dahlia, 319, 309, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(dahlia->model_0.anim_4.status_0, dahlia, 319, 329, sfx, pitch0);
            }
            break;

        case 19:
            if (dahlia->model_0.anim_4.keyframeIdx_8 < 175)
            {

                sharedFunc_800D9188_0_s00(ANIM_STATUS(19, true), dahlia, 170, Sfx_Unk1674);
            }
            else
            {
                sharedFunc_800D9188_0_s00(ANIM_STATUS(19, true), dahlia, 177, Sfx_Unk1675);
            }
            break;
    }

    dahlia->rotation_24.vy  = FP_ANGLE_ABS(dahlia->rotation_24.vy + Q8_TO_Q4(sharedData_800D16E0_2_s01));
    dahlia->headingAngle_3C = dahlia->rotation_24.vy;
    dahlia->moveSpeed_38    = dahliaProps.moveDistance_126;
    dahlia->field_34       += g_DeltaTime2;

    coords->flg = false;
    Math_MatrixRotate1(&dahlia->rotation_24, &coords->coord);
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
    func_8003DD80(Chara_EndingDahlia, 1); // TODO: MAP7_S03 Ai_Dahlia funcs could be Ai_EndingDahlia instead, if other Ai_Dahlia funcs don't match other overlays.
#else
    func_8003DD80(Chara_Dahlia, 1);
#endif

#ifdef MAP7_S02
    func_8003D468(Chara_Dahlia, true);
#endif
}
