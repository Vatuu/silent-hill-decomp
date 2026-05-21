#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/map7/map7_s02.h"

// TODO: Move to src/maps/characters/ once matched.

void GhostDoctor_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords) // 0x800D8AF0
{
    if (chara->model.charaId != Chara_GhostDoctor)
    {
        GhostDoctor_Init(chara);
    }

    func_800D8C00(chara, boneCoords);
    Character_CoordTransformUpdate(chara, boneCoords);
    GhostDoctor_AnimUpdate(chara, anmHdr, boneCoords);
}

void GhostDoctor_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords) // 0x800D8B64
{
    s_AnimInfo* animInfo;

    // TODO: Wrong properties union.
    if (chara->properties.player.field_F0 == 0)
    {
        animInfo = &GHOST_DOCTOR_ANIM_INFOS[chara->model.anim.status];
        animInfo->playbackFunc(&chara->model, anmHdr, boneCoords, animInfo);
    }
}

void Character_CoordTransformUpdate(s_SubCharacter* chara, GsCOORDINATE2* boneCoords) // 0x800D8BAC
{
    boneCoords[0].coord.t[0] = Q12_TO_Q8(chara->position.vx);
    boneCoords[0].coord.t[1] = Q12_TO_Q8(chara->position.vy);
    boneCoords[0].coord.t[2] = Q12_TO_Q8(chara->position.vz);
}

void GhostDoctor_Init(s_SubCharacter* chara) // 0x800D8BE0
{
    Chara_CollisionReset(chara);
}

void func_800D8C00(s_SubCharacter* chara, GsCOORDINATE2* boneCoords) // 0x800D8C00
{
    if (chara->properties.player.afkTimer == Q12(0.0f))
    {
        if (chara->model.stateStep == 0)
        {
            chara->model.anim.status = ANIM_STATUS(1, false);
            chara->model.stateStep++;
        }

        if (chara->properties.player.runTimer_F8 != Q12(0.0f))
        {
            chara->properties.player.afkTimer = Q12(0.0f);
            chara->model.stateStep              = 0;
            chara->properties.player.runTimer_F8 = Q12(0.0f);
        }
    }

    boneCoords->flg = false;
    Math_RotMatrixZxyNegGte(&chara->rotation, &boneCoords->coord);
}
