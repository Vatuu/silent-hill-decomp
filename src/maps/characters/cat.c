#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "maps/characters/cat.h"

void Cat_Update(s_SubCharacter* cat, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords) // 0x800D6D40
{
    s_AnimInfo* animInfo;
    bool        cond;

    if (cat->model.controlState == CatControl_None)
    {
        cat->model.controlState                        = CatControl_1;
        cat->model.anim.status                         = ANIM_STATUS(CatAnim_IdleToJump, true);
        cat->model.anim.time                           = Q12(7.0f);
        cat->model.anim.alpha                          = Q12(0.0f);
        cat->model.stateStep                           = 0;
        cat->model.anim.keyframeIdx                    = 7;
        cat->position.vy                               = Q12(0.0f);
        cat->properties.dummy.properties_E8[0].val8[0] = 0;
    }

    if (cat->model.stateStep == 0)
    {
        if (cat->model.controlState == CatControl_2)
        {
            cat->model.anim.status      = ANIM_STATUS(CatAnim_Jump, true);
            cat->model.anim.time        = Q12(7.0f);
            cat->model.anim.keyframeIdx = 7;
        }
        else if (cat->model.controlState == CatControl_3)
        {
            cat->model.anim.status      = ANIM_STATUS(CatAnim_Run, true);
            cat->model.anim.time        = Q12(23.0f);
            cat->model.anim.keyframeIdx = 23;
        }

        cat->model.stateStep++;
    }

    Math_MatrixTransform(&cat->position, &cat->rotation, boneCoords);

    animInfo = &CAT_ANIM_INFOS[cat->model.anim.status];
    animInfo->playbackFunc(&cat->model, anmHdr, boneCoords, animInfo);

    cond = false;
    if (cat->model.anim.status == ANIM_STATUS(1, true))
    {
        if (((u8)cat->properties.dummy.properties_E8[0].val8[0] == 0 &&
             (FP_FROM(cat->model.anim.time, Q12_SHIFT) - 20) < 3u) ||
            ((u8)cat->properties.dummy.properties_E8[0].val8[0] != 0 &&
             (FP_FROM(cat->model.anim.time, Q12_SHIFT) - 25) < 3u))
        {
            cond = true;
        }
    }
    else
    {
        if (((u8)cat->properties.dummy.properties_E8[0].val8[0] == 0 &&
             (FP_FROM(cat->model.anim.time, Q12_SHIFT) - 29) < 3u) ||
            ((u8)cat->properties.dummy.properties_E8[0].val8[0] != 0 &&
             (FP_FROM(cat->model.anim.time, Q12_SHIFT) - 36) < 3u))
        {
            cond = true;
        }
    }

    if (cond)
    {
        func_8005DD44(1447, &cat->position, Q8(0.5f), Rng_GenerateUInt(-7, 8));
        cat->properties.dummy.properties_E8[0].val8[0] ^= 1;
    }
}
