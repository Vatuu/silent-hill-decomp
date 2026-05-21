#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/map7/map7_s02.h"

// TODO: Move to src/maps/characters/ once matched.

void GhostDoctor_Update(s_SubCharacter* ghostDoc, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords) // 0x800D8AF0
{
    if (ghostDoc->model.charaId != Chara_GhostDoctor)
    {
        GhostDoctor_Init(ghostDoc);
    }

    func_800D8C00(ghostDoc, boneCoords);
    Character_CoordTransformUpdate(ghostDoc, boneCoords);
    GhostDoctor_AnimUpdate(ghostDoc, anmHdr, boneCoords);
}

void GhostDoctor_AnimUpdate(s_SubCharacter* ghostDoc, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords) // 0x800D8B64
{
    s_AnimInfo* animInfo;

    // TODO: Wrong properties union.
    if (ghostDoc->properties.player.field_F0 == 0)
    {
        animInfo = &GHOST_DOCTOR_ANIM_INFOS[ghostDoc->model.anim.status];
        animInfo->playbackFunc(&ghostDoc->model, anmHdr, boneCoords, animInfo);
    }
}

void Character_CoordTransformUpdate(s_SubCharacter* ghostDoc, GsCOORDINATE2* boneCoords) // 0x800D8BAC
{
    boneCoords[0].coord.t[0] = Q12_TO_Q8(ghostDoc->position.vx);
    boneCoords[0].coord.t[1] = Q12_TO_Q8(ghostDoc->position.vy);
    boneCoords[0].coord.t[2] = Q12_TO_Q8(ghostDoc->position.vz);
}

void GhostDoctor_Init(s_SubCharacter* ghostDoc) // 0x800D8BE0
{
    Chara_CollisionReset(ghostDoc);
}

void func_800D8C00(s_SubCharacter* ghostDoc, GsCOORDINATE2* boneCoords) // 0x800D8C00
{
    if (ghostDoc->properties.player.afkTimer == Q12(0.0f))
    {
        if (ghostDoc->model.stateStep == 0)
        {
            ghostDoc->model.anim.status = ANIM_STATUS(1, false);
            ghostDoc->model.stateStep++;
        }

        if (ghostDoc->properties.player.runTimer_F8 != Q12(0.0f))
        {
            ghostDoc->properties.player.afkTimer = Q12(0.0f);
            ghostDoc->model.stateStep              = 0;
            ghostDoc->properties.player.runTimer_F8 = Q12(0.0f);
        }
    }

    boneCoords->flg = false;
    Math_RotMatrixZxyNegGte(&ghostDoc->rotation, &boneCoords->coord);
}
