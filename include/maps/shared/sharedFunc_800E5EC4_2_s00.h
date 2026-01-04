void sharedFunc_800E5EC4_2_s00(s_SubCharacter* groaner, s_AnmHeader* arg1, GsCOORDINATE2* arg2)
{
    typedef struct
    {
        SVECTOR field_0;
        MATRIX  field_8;
    } s_sharedFunc_800E5EC4_2_s00;

    s16                          temp_v0_5;
    s16                          temp_v0_6;
    s16                          var_s0;
    s32                          var_a3;
    s_AnimInfo*                  temp_a3;
    s_sharedFunc_800E5EC4_2_s00* ptr;

    switch (groaner->model_0.anim_4.status_0)
    {
        case 21:
            if (FP_FROM(groaner->model_0.anim_4.time_4, 0xC) > 0xCE && FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) < 0xDC)
            {
                GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = 0x18000;
            }

            if (FP_FROM(groaner->model_0.anim_4.time_4, 0xC) > 0xDB && FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) < 0xE2)
            {
                GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = 0x18000;
            }

            if (FP_FROM(groaner->model_0.anim_4.time_4, 0xC) > 0xE1 && FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) < 0xF4)
            {
                GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = 0x1E000;
            }
            break;

        case 7:
            if (groaner->properties_E4.groaner.flags_E8.val16[0] & 0x20)
            {
                GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = 0x20000;
            }
            else
            {
                GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = 0x19C00;
            }
            break;

        case 15:
        case 27:
            if (groaner->properties_E4.groaner.flags_E8.val16[0] & 0x20)
            {
                GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = 0x1E000;
            }
            else
            {
                GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = 0x16800;
            }
            break;

        case 33:
            if (groaner->properties_E4.groaner.angle_EC == groaner->rotation_24.vy)
            {
                var_a3 = groaner->moveSpeed_38;
            }
            else
            {
                if (groaner->moveSpeed_38 >= 0x1000)
                {
                    var_a3 = groaner->moveSpeed_38;
                }
                else
                {
                    var_a3 = 0x1000;
                }
            }
            var_a3                                                                   = FP_TO(var_a3 * 20, Q12_SHIFT) / FP_MULTIPLY_PRECISE(groaner->properties_E4.groaner.field_114, 0x3999, Q12_SHIFT);
            GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0].duration_8.constant = var_a3;
            break;
    }

    Math_MatrixTransform(&groaner->position_18, (SVECTOR*)&groaner->rotation_24, arg2);

    temp_a3 = &GROANER_ANIM_INFOS[groaner->model_0.anim_4.status_0];
    temp_a3->updateFunc_0(&groaner->model_0, arg1, arg2, temp_a3);

    ptr = PSX_SCRATCH;

    switch (groaner->model_0.anim_4.status_0)
    {
        case 34:
        case 35:
            temp_v0_5 = FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x400, Q12_SHIFT);
            var_s0    = 0x180;
            break;

        case 20:
        case 21:
        case 30:
        case 31:
        case 32:
        case 33:
            temp_v0_5 = FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x600, Q12_SHIFT);
            var_s0    = 0x280;
            break;

        default:
            temp_v0_5 = FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x600, Q12_SHIFT);
            var_s0    = 0;
            break;
    }

    temp_v0_6 = func_8005BF38(groaner->properties_E4.groaner.angle_EC - groaner->rotation_24.vy);

    if (temp_v0_6 == 0)
    {
        var_s0 = 0;
    }
    else if (temp_v0_6 < 0)
    {
        var_s0 = -var_s0;
    }

    if (groaner->properties_E4.groaner.field_EE > var_s0)
    {
        groaner->properties_E4.groaner.field_EE = MAX(var_s0, groaner->properties_E4.groaner.field_EE - temp_v0_5);
    }
    else
    {
        groaner->properties_E4.groaner.field_EE = CLAMP_HIGH(var_s0, groaner->properties_E4.groaner.field_EE + temp_v0_5);
    }

    *(s32*)&ptr->field_0 = (groaner->properties_E4.groaner.field_EE >> 2) << 16;
    ptr->field_0.vz      = 0;

    Math_RotMatrixZxyNegGte(&ptr->field_0, &ptr->field_8);
    MulMatrix(&arg2[3].coord, &ptr->field_8);
    MulMatrix(&arg2[4].coord, &ptr->field_8);

    *(s32*)&ptr->field_0.vx = groaner->properties_E4.groaner.field_EE << 16;
    ptr->field_0.vz         = 0;

    Math_RotMatrixZxyNegGte(&ptr->field_0, &ptr->field_8);
    MulMatrix(&arg2[1].coord, &ptr->field_8);

    groaner->rotation_24.vy                 = func_8005BF38(groaner->rotation_24.vy);
    groaner->properties_E4.groaner.angle_EC = groaner->rotation_24.vy;
}