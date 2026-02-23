#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map7/map7_s02.h"

// TODO: Move to src/maps/characters/ once matched.

void Ai_GhostDoctor_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D8AF0
{
    if (chara->model_0.charaId_0 != Chara_GhostDoctor)
    {
        Ai_GhostDoctor_Init(chara);
    }

    func_800D8C00(chara, coords);
    Character_CoordTransformUpdate(chara, coords);
    Ai_GhostDoctor_AnimUpdate(chara, anmHdr, coords);
}

void Ai_GhostDoctor_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D8B64
{
    s_AnimInfo* animInfo;

    // TODO: Wrong properties union.
    if (chara->properties_E4.player.field_F0 == 0)
    {
        animInfo = &GHOST_DOCTOR_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
    }
}

void Character_CoordTransformUpdate(s_SubCharacter* chara, GsCOORDINATE2* coord) // 0x800D8BAC
{
    coord->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coord->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coord->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);
}

void Ai_GhostDoctor_Init(s_SubCharacter* chara) // 0x800D8BE0
{
    sharedFunc_800D923C_0_s00(chara);
}

void func_800D8C00(s_SubCharacter* chara, GsCOORDINATE2* coord) // 0x800D8C00
{
    if (chara->properties_E4.player.afkTimer_E8 == Q12(0.0f))
    {
        if (chara->model_0.stateStep_3 == 0)
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(1, false);
            chara->model_0.stateStep_3++;
        }

        if (chara->properties_E4.player.runTimer_F8 != Q12(0.0f))
        {
            chara->properties_E4.player.afkTimer_E8 = Q12(0.0f);
            chara->model_0.stateStep_3              = 0;
            chara->properties_E4.player.runTimer_F8 = Q12(0.0f);
        }
    }

    coord->flg = false;
    Math_RotMatrixZxyNegGte(&chara->rotation_24, &coord->coord);
}
