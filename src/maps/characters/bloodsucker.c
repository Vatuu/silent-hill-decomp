#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/bloodsucker.h"

void Ai_Bloodsucker_Update(s_SubCharacter* bloodsucker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    u32 animStatusDiv2;
    s32 stateStepMul2;

    // Initialize.
    if (bloodsucker->model_0.controlState_2 == BloodsuckerControl_None)
    {
        Ai_Bloodsucker_Init(bloodsucker);
    }

    // Handle control state.
    switch (bloodsucker->model_0.controlState_2)
    {
        case BloodsuckerControl_1:
            Ai_Bloodsucker_Control_1(bloodsucker);
            break;

        case BloodsuckerControl_2:
            Ai_Bloodsucker_Control_2(bloodsucker);
            break;

        case BloodsuckerControl_3:
            Ai_Bloodsucker_Control_3(bloodsucker);
            break;

        case BloodsuckerControl_4:
            Ai_Bloodsucker_Control_4(bloodsucker);
            break;
    }

    sharedFunc_800D0F28_3_s03(bloodsucker, anmHdr, coords);

    // Reset flags if ???
    if (g_SysWork.sysFlags_22A0 & SysFlag_6)
    {
        bloodsucker->properties_E4.bloodsucker.flags_118 &= ~BloodsuckerFlag_0;
        bloodsucker->properties_E4.bloodsucker.flags_118 &= ~BloodsuckerFlag_1;
    }

    if (bloodsucker->model_0.stateStep_3 != 0)
    {
        return;
    }

    if (!(bloodsucker->properties_E4.bloodsucker.flags_118 & BloodsuckerFlag_0))
    {
        SD_Call(Sfx_Unk1525);
        bloodsucker->properties_E4.bloodsucker.flags_118 |= BloodsuckerFlag_0;
    }

    func_8005DE0C(Sfx_Unk1525, &bloodsucker->position_18, bloodsucker->properties_E4.bloodsucker.timer_EC >> 5, Q12(16.0f), 0);

    if (bloodsucker->properties_E4.bloodsucker.timer_EC < bloodsucker->properties_E4.bloodsucker.timer_F0)
    {
        bloodsucker->properties_E4.bloodsucker.timer_EC += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.5f);
        if (bloodsucker->properties_E4.bloodsucker.timer_EC > bloodsucker->properties_E4.bloodsucker.timer_F0)
        {
            bloodsucker->properties_E4.bloodsucker.timer_EC = bloodsucker->properties_E4.bloodsucker.timer_F0;
        }
    }
    else if (bloodsucker->properties_E4.bloodsucker.timer_EC > bloodsucker->properties_E4.bloodsucker.timer_F0)
    {
        bloodsucker->properties_E4.bloodsucker.timer_EC -= Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.5f);
        if (bloodsucker->properties_E4.bloodsucker.timer_EC < bloodsucker->properties_E4.bloodsucker.timer_F0)
        {
            bloodsucker->properties_E4.bloodsucker.timer_EC = bloodsucker->properties_E4.bloodsucker.timer_F0;
        }
    }

    animStatusDiv2 = bloodsucker->model_0.anim_4.status_0 / 2;
    stateStepMul2  = bloodsucker->model_0.stateStep_3 * 2;

    // SFX timer state handling. TODO: Inspect behavior in-game.
    if (animStatusDiv2 == ((stateStepMul2 + 23) / 2) || animStatusDiv2 == ((stateStepMul2 + 17) / 2))
    {
        if (!(bloodsucker->properties_E4.bloodsucker.flags_118 & BloodsuckerFlag_1))
        {
            bloodsucker->properties_E4.bloodsucker.flags_118 |= BloodsuckerFlag_1;
            SD_Call(Sfx_Unk1527);
        }

        bloodsucker->properties_E4.bloodsucker.timer_F4 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 2.0f);
        if (bloodsucker->properties_E4.bloodsucker.timer_F4 > Q12(1.0f))
        {
            bloodsucker->properties_E4.bloodsucker.timer_F4 = Q12(1.0f);
        }

        func_8005DE0C(Sfx_Unk1527, &bloodsucker->position_18, bloodsucker->properties_E4.bloodsucker.timer_F4 >> 5, Q12(16.0f), 0);
    }
    else if (bloodsucker->properties_E4.bloodsucker.flags_118 & BloodsuckerFlag_1)
    {
        bloodsucker->properties_E4.bloodsucker.timer_F4 -= Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 2.0f);
        if (bloodsucker->properties_E4.bloodsucker.timer_F4 < Q12(0.0f))
        {
            bloodsucker->properties_E4.bloodsucker.timer_F4 = Q12(0.0f);
            bloodsucker->properties_E4.bloodsucker.flags_118 &= ~BloodsuckerFlag_1;
            Sd_SfxStop(Sfx_Unk1527);
        }
    }
}

static inline void Ai_Bloodsucker_AnimUpdateFromStep(s_SubCharacter* chara)
{
    u32         stateStep;
    s_Savegame* save;

    switch (chara->model_0.stateStep_3)
    {
        case 17:
            chara->model_0.controlState_2     = 1;
            chara->model_0.stateStep_3 = 0;
            Character_AnimSet(chara, ANIM_STATUS(BloodsuckerAnim_7, true), 81);
            return;

#ifdef MAP7_S02 // MAP7_S02 skips rest of function.
    }
#else
        case 18:
            chara->health_B0       = 1;
            chara->model_0.controlState_2 = 2;
            break;

        case 19:
        case 20:
            chara->model_0.controlState_2 = 2;
            break;

        default:
            return;
    }

    save = g_SavegamePtr; // TODO: Odd pointer copy, might be some inline flag check func?

    // Anim-related?
    stateStep                  = chara->model_0.stateStep_3 - 18;
    chara->model_0.stateStep_3 = stateStep;

    // TODO: `Savegame_EventFlagGet(EventFlag_250)`
    if (!(save->eventFlags_168[7] & (1 << 26)))
    {
        chara->model_0.anim_4.status_0 = (stateStep * 2) + 23;
    }
    else
    {
        chara->model_0.anim_4.status_0 = (stateStep * 2) + 17;
    }

    chara->model_0.anim_4.time_4        = Q12(BLOODSUCKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C);
    chara->model_0.anim_4.keyframeIdx_8 = BLOODSUCKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C;
#endif
}

void Ai_Bloodsucker_Init(s_SubCharacter* bloodsucker)
{
    s32 i;

    Chara_PropertiesClear(bloodsucker);
    bloodsucker->field_E1_0      = 4;
    bloodsucker->headingAngle_3C = bloodsucker->rotation_24.vy;

    Ai_Bloodsucker_AnimUpdateFromStep(bloodsucker);
    ModelAnim_AnimInfoSet(&bloodsucker->model_0.anim_4, BLOODSUCKER_ANIM_INFOS);
    Chara_DamageClear(bloodsucker);
}

void Ai_Bloodsucker_Control_1(s_SubCharacter* bloodsucker)
{
    #define bloodsuckerProps bloodsucker->properties_E4.bloodsucker

    bloodsucker->model_0.anim_4.time_4 = Q12(81.0f) + bloodsuckerProps.timer_E8;

    #undef bloodsuckerProps
}

void Ai_Bloodsucker_Control_2(s_SubCharacter* bloodsucker)
{
#ifdef MAP3_S03
    if (bloodsucker->model_0.anim_4.status_0 == ((bloodsucker->model_0.stateStep_3 * 2) + 9))
    {
        bloodsucker->model_0.anim_4.status_0 = (bloodsucker->model_0.stateStep_3 * 2) + 22;
    }

    if (g_SysWork.playerWork_4C.player_0.position_18.vx < Q12(-140.75f))
    {
        bloodsucker->model_0.controlState_2 = BloodsuckerControl_3;
    }

    bloodsucker->properties_E4.bloodsucker.timer_F0 = Q12(0.3f);
#endif
}

void Ai_Bloodsucker_Control_3(s_SubCharacter* bloodsucker)
{
    if (bloodsucker->model_0.anim_4.status_0 == ((bloodsucker->model_0.stateStep_3 * 2) + 23))
    {
        bloodsucker->model_0.anim_4.status_0 = (bloodsucker->model_0.stateStep_3 * 2) + 8;
    }

    if (g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(-140.5f))
    {
        bloodsucker->model_0.controlState_2 = BloodsuckerControl_2;
    }

    bloodsucker->properties_E4.bloodsucker.timer_F0 = Q12(1.0f);
}

void Ai_Bloodsucker_Control_4(s_SubCharacter* bloodsucker)
{
#ifdef MAP3_S03
    if (bloodsucker->model_0.anim_4.status_0 != ((bloodsucker->model_0.stateStep_3 * 2) + 2) &&
        bloodsucker->model_0.anim_4.status_0 != ((bloodsucker->model_0.stateStep_3 * 2) + 3) &&
        bloodsucker->model_0.anim_4.status_0 != ((bloodsucker->model_0.stateStep_3 * 2) + 16) &&
        bloodsucker->model_0.anim_4.status_0 != ((bloodsucker->model_0.stateStep_3 * 2) + 17))
    {
        bloodsucker->model_0.anim_4.status_0 = (bloodsucker->model_0.stateStep_3 * 2) + 2;
    }

    if (ANIM_STATUS_IS_ACTIVE(bloodsucker->model_0.anim_4.status_0))
    {
        bloodsucker->properties_E4.bloodsucker.timer_F0 = Q12(0.3f);
    }
    else
    {
        bloodsucker->properties_E4.bloodsucker.timer_F0 = Q12(0.75f);
    }
#endif
}

void sharedFunc_800D0F28_3_s03(s_SubCharacter* bloodsucker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    typedef struct
    {
        MATRIX   field_0;
        SVECTOR3 field_20;
        u8       unk_26[2];
        VECTOR3  field_28;
        u8       unk_34[4];
        VECTOR3  field_38;
    } s_sharedFunc_800D0F28_3_s03;

    s_AnimInfo*                  animInfo;
    s_sharedFunc_800D0F28_3_s03* scratchData;

    scratchData = PSX_SCRATCH;

    Math_MatrixTransform(&bloodsucker->position_18, &bloodsucker->rotation_24, coords);
    animInfo = &BLOODSUCKER_ANIM_INFOS[bloodsucker->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&bloodsucker->model_0, anmHdr, coords, animInfo);
    Vw_CoordHierarchyMatrixCompute(&coords[14], &scratchData->field_0);

    gte_SetRotMatrix(&scratchData->field_0);
    gte_SetTransMatrix(&scratchData->field_0);

    Math_SetSVectorFast(&scratchData->field_20, 0, 0, 0);

    gte_ldv0(&scratchData->field_20);
    gte_rt();
    gte_stlvnl(&scratchData->field_28);

    scratchData->field_28.vx = Q8_TO_Q12(scratchData->field_28.vx);
    scratchData->field_28.vy = Q8_TO_Q12(scratchData->field_28.vy);
    scratchData->field_28.vz = Q8_TO_Q12(scratchData->field_28.vz);

    bloodsucker->field_C8.field_0   = scratchData->field_28.vy - Q12(0.05f);
    bloodsucker->field_C8.field_2   = scratchData->field_28.vy + Q12(0.05f);
    bloodsucker->field_C8.field_4   = scratchData->field_28.vy + Q12(0.05f);
    bloodsucker->field_C8.field_6   = scratchData->field_28.vy;
    bloodsucker->field_D8.offsetX_0 = scratchData->field_28.vx - bloodsucker->position_18.vx;
    bloodsucker->field_D8.offsetZ_2 = scratchData->field_28.vz - bloodsucker->position_18.vz;
    bloodsucker->field_D4.field_2   = Q12(0.05f);
    bloodsucker->field_D8.offsetX_4 = scratchData->field_28.vx - bloodsucker->position_18.vx;
    bloodsucker->field_D8.offsetZ_6 = scratchData->field_28.vz - bloodsucker->position_18.vz;
    bloodsucker->field_D4.radius_0   = Q12(0.05f);
    Math_SetSVectorFast(&scratchData->field_20, 0, -22, 0);

    gte_ldv0(&scratchData->field_20);
    gte_rt();
    gte_stlvnl(&scratchData->field_28);

    scratchData->field_28.vx = Q8_TO_Q12(scratchData->field_28.vx);
    scratchData->field_28.vy = Q8_TO_Q12(scratchData->field_28.vy);
    scratchData->field_28.vz = Q8_TO_Q12(scratchData->field_28.vz);
    scratchData->field_38.vx = scratchData->field_28.vx;
    scratchData->field_38.vy = scratchData->field_28.vy;
    scratchData->field_38.vz = scratchData->field_28.vz;

    bloodsucker->field_44.field_0 = 1;

    // TODO: 0x45 should be `WEAPON_ATTACK` macro?
    func_8008A0E4(1, 0x45, bloodsucker, &scratchData->field_38, &g_SysWork.playerWork_4C.player_0, Q12_ANGLE(90.0f), Q12_ANGLE(90.0f));
}
