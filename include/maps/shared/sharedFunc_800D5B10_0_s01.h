void sharedFunc_800D5B10_0_s01(s_SubCharacter* airScreamer)
{
    q19_12                       angle;
    q19_12                       dist;
    q19_12                       posY;
    s32                          idx0;
    s32                          idx1;
    s32                          idx2;
    s32                          idx3;
    s32                          animStatus0;
    bool                         cond;
    s32                          animStatus;
    s32                          element0;
    s32                          element1;
    s32                          element3;
    s32                          element2;
    s32                          element4;
    s32                          element5;
    q19_12                       tmp;
    VECTOR3*                     pos0;
    VECTOR3*                     pos;
    s_sharedData_800E21D0_0_s01* base;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    pos   = &airScreamer->position_18;
    pos0  = &airScreamerProps.targetPosition_F8;
    dist  = Math_Distance2dGet(pos, pos0);
    angle = FP_ANGLE_NORM_S(func_80080478(pos, pos0) - airScreamer->rotation_24.vy);

    tmp        = sharedFunc_800D569C_0_s01(airScreamer, airScreamerProps.targetPosition_F8.vy, dist);
    cond       = false;
    posY       = tmp - airScreamer->position_18.vy;
    animStatus = airScreamer->model_0.anim_4.status_0;

    animStatus0 = ANIM_STATUS(22, true);
    if (animStatus == animStatus0)
    {
        idx2 = 17;
    }
    else if (animStatus < animStatus0 || animStatus >= ANIM_STATUS(28, false) || animStatus < ANIM_STATUS(27, false))
    {
        cond = true;
        idx2 = 14;

        if (posY <= Q12(0.05f))
        {
            idx2 = 15;
            if (posY < Q12(-0.05f))
            {
                idx2 = 16;
            }
        }
    }
    else
    {
        idx2 = 18;
    }

    element0 = sharedData_800CAA98_0_s01.unk_380[34][0];
    element1 = sharedData_800CAA98_0_s01.unk_380[34][1];

    if (angle <= FP_ANGLE(0.5f))
    {
        element1 = -element1;
        if (angle < FP_ANGLE(-0.5f))
        {
            element0 = -element0;
        }
        else
        {
            element1 = 0;

            element0 = 0;
        }
    }

    element2 = sharedData_800CAA98_0_s01.unk_380[6][0];
    element3 = sharedData_800CAA98_0_s01.unk_380[6][1];
    base     = &sharedData_800E21D0_0_s01;

    idx3                    = 0;
    base->field_B4[idx3][2] = element2;
    base->field_B4[idx3][1] = element3;

    element4 = sharedData_800CAA98_0_s01.unk_380[idx2][0];
    element5 = sharedData_800CAA98_0_s01.unk_380[idx2][1];

    idx3                    = 1;
    base->field_B4[idx3][2] = element4;
    base->field_B4[idx3][1] = element5;
    if (cond)
    {
        base->field_B4[idx3][3] = posY;
        base->field_B4[idx3][0] = 1;
    }

    idx3                    = 3;
    base->field_B4[idx3][2] = element0;
    base->field_B4[idx3][1] = element1;
    base->field_B4[idx3][3] = angle;
    base->field_B4[idx3][0] =
    tmp                     = 1;

    sharedFunc_800D5E78_0_s01(airScreamer, angle / 2);

    #undef airScreamerProps
}
