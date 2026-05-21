#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "maps/characters/cat.h"

void Cat_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D6D40
{
    s_AnimInfo* animInfo;
    bool        cond;

    if (chara->model.controlState == 0)
    {
        chara->model.controlState                        = 1;
        chara->model.anim.status                         = ANIM_STATUS(3, true);
        chara->model.anim.time                           = Q12(7.0f);
        chara->model.anim.alpha                          = Q12(0.0f);
        chara->model.stateStep                           = 0;
        chara->model.anim.keyframeIdx                    = 7;
        chara->position.vy                               = 0;
        chara->properties.dummy.properties_E8[0].val8[0] = 0;
    }

    if (chara->model.stateStep == 0)
    {
        if (chara->model.controlState == 2)
        {
            chara->model.anim.status      = ANIM_STATUS(1, true);
            chara->model.anim.time        = Q12(7.0f);
            chara->model.anim.keyframeIdx = 7;
        }
        else if (chara->model.controlState == 3)
        {
            chara->model.anim.status      = ANIM_STATUS(2, true);
            chara->model.anim.time        = Q12(23.0f);
            chara->model.anim.keyframeIdx = 23;
        }

        chara->model.stateStep++;
    }

    Math_MatrixTransform(&chara->position, &chara->rotation, coords);

    animInfo = &CAT_ANIM_INFOS[chara->model.anim.status];
    animInfo->playbackFunc(&chara->model, anmHdr, coords, animInfo);

    cond = false;
    if (chara->model.anim.status == ANIM_STATUS(1, true))
    {
        if (((u8)chara->properties.dummy.properties_E8[0].val8[0] == 0 &&
             (FP_FROM(chara->model.anim.time, Q12_SHIFT) - 20) < 3u) ||
            ((u8)chara->properties.dummy.properties_E8[0].val8[0] != 0 &&
             (FP_FROM(chara->model.anim.time, Q12_SHIFT) - 25) < 3u))
        {
            cond = true;
        }
    }
    else
    {
        if (((u8)chara->properties.dummy.properties_E8[0].val8[0] == 0 &&
             (FP_FROM(chara->model.anim.time, Q12_SHIFT) - 29) < 3u) ||
            ((u8)chara->properties.dummy.properties_E8[0].val8[0] != 0 &&
             (FP_FROM(chara->model.anim.time, Q12_SHIFT) - 36) < 3u))
        {
            cond = true;
        }
    }

    if (cond)
    {
        func_8005DD44(1447, &chara->position, Q8(0.5f), Rng_GenerateUInt(-7, 8));
        chara->properties.dummy.properties_E8[0].val8[0] ^= 1;
    }
}
