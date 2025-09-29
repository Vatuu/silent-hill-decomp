void sharedFunc_800D57C8_0_s01(s_SubCharacter* chara)
{
    VECTOR3* vec1;
    VECTOR3* pos;
    s32      angle;
    s32      dist;
    s32      posY;
    s32      idx0;
    s32      idx1;
    s32      idx2;
    s32      idx3;

    s32 status45;

    bool var_t4;

    s32 animStatus;
    s32 element0;
    s32 element1;
    s32 element3;
    s32 element2;
    s32 element4;
    s32 element5;

    s32                          tmp;
    s_sharedData_800E21D0_0_s01* base;

    pos   = &chara->position_18;
    vec1  = &chara->properties_E4.unk0.field_110;
    dist  = Math_Distance2dGet(pos, vec1);
    angle = FP_ANGLE_NORM_S(func_80080478(pos, vec1) - chara->rotation_24.vy);

    tmp    = sharedFunc_800D569C_0_s01(chara, vec1->vy, dist);
    var_t4 = 0;
    posY   = tmp - chara->position_18.vy;

    if (dist > (chara->field_D4 + 0xCC) && (angle + 0x200) < 0x400U)
    {
        idx0 = 5;
        idx1 = 33;
    }
    else
    {
        idx0 = 7;
        idx1 = 35;
    }

    animStatus = chara->model_0.anim_4.status_0;

    status45 = 45;
    if (animStatus == status45)
    {
        idx2 = 17;
    }
    else if (animStatus < status45 || animStatus >= 0x38 || animStatus < 0x36)
    {
        var_t4 = 1;
        idx2   = 14;
        if (posY <= 0xCC)
        {
            idx2 = 15;
            if (posY < -0xCC)
            {
                idx2 = 16;
            }
        }
    }
    else
    {
        idx2 = 0x12;
    }

    element0 = sharedData_800CAA98_0_s01.unk_380[idx1][0];
    element1 = sharedData_800CAA98_0_s01.unk_380[idx1][1];
    if (angle < 6)
    {
        element1 = -element1;
        if (angle < -5)
        {
            element0 = -element0;
        }
        else
        {
            element1 = 0;

            element0 = 0;
        }
    }

    element2 = sharedData_800CAA98_0_s01.unk_380[idx0][0];
    element3 = sharedData_800CAA98_0_s01.unk_380[idx0][1];
    base     = &sharedData_800E21D0_0_s01;

    idx3                    = 0;
    base->field_B4[idx3][2] = element2;
    base->field_B4[idx3][1] = element3;
    base->field_B4[idx3][3] = dist;
    base->field_B4[idx3][0] = 1;

    element4 = sharedData_800CAA98_0_s01.unk_380[idx2][0];
    element5 = sharedData_800CAA98_0_s01.unk_380[idx2][1];

    idx3                    = 1;
    base->field_B4[idx3][2] = element4;
    base->field_B4[idx3][1] = element5;
    if (var_t4)
    {
        base->field_B4[idx3][3] = posY;
        base->field_B4[idx3][0] = 1;
    }

    idx3                    = 3;
    base->field_B4[idx3][2] = element0;
    base->field_B4[idx3][1] = element1;
    base->field_B4[idx3][3] = angle;
    base->field_B4[idx3][0] = 1;

    idx0 = angle / 2;
    sharedFunc_800D5E78_0_s01(chara, idx0);
}
