#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/map7/map7_s02.h"

// TODO: Move to src/maps/characters/ once matched.

void Ai_GhostDoctor_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D8AF0
{
    if (chara->model.charaId_0 != Chara_GhostDoctor)
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
    if (chara->properties.player.field_F0 == 0)
    {
        animInfo = &GHOST_DOCTOR_ANIM_INFOS[chara->model.anim.status];
        animInfo->playbackFunc(&chara->model, anmHdr, coords, animInfo);
    }
}

void Character_CoordTransformUpdate(s_SubCharacter* chara, GsCOORDINATE2* coord) // 0x800D8BAC
{
    coord->coord.t[0] = Q12_TO_Q8(chara->position.vx);
    coord->coord.t[1] = Q12_TO_Q8(chara->position.vy);
    coord->coord.t[2] = Q12_TO_Q8(chara->position.vz);
}

void Ai_GhostDoctor_Init(s_SubCharacter* chara) // 0x800D8BE0
{
    sharedFunc_800D923C_0_s00(chara);
}

void func_800D8C00(s_SubCharacter* chara, GsCOORDINATE2* coord) // 0x800D8C00
{
    if (chara->properties.player.afkTimer_E8 == Q12(0.0f))
    {
        if (chara->model.stateStep == 0)
        {
            chara->model.anim.status = ANIM_STATUS(1, false);
            chara->model.stateStep++;
        }

        if (chara->properties.player.runTimer_F8 != Q12(0.0f))
        {
            chara->properties.player.afkTimer_E8 = Q12(0.0f);
            chara->model.stateStep              = 0;
            chara->properties.player.runTimer_F8 = Q12(0.0f);
        }
    }

    coord->flg = false;
    Math_RotMatrixZxyNegGte(&chara->rotation, &coord->coord);
}
