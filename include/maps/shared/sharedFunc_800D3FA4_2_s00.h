// Similar to `sharedFunc_800D4358_2_s00`

void sharedFunc_800D3FA4_2_s00(s_SubCharacter* arg0)
{
    s32  temp_fp;
    s32  temp_s0_3;
    s32  temp_s1_2;
    bool temp_s5;
    bool temp_s6;
    bool temp_s7;
    s32  temp_v0;
    s32  var_s3;
    s32  var_s4;
    bool var_v0_2;
    s32  temp_s0;
    bool new_var;

    temp_s0 = arg0->model_0.anim_4.status_0;
    var_s3  = 0;
    var_s4  = 0;
    temp_fp = sharedFunc_800D4A80_0_s01(arg0);

    var_v0_2 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    new_var  = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    temp_s6  = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;

    temp_s5 = var_v0_2;
    temp_s7 = new_var;

    switch (arg0->model_0.stateStep_3)
    {
        case 0x40:
            sharedFunc_800DD4A4_2_s00(arg0);
            arg0->model_0.stateStep_3 = 1;
            break;

        case 0x0:
            sharedFunc_800DDF74_2_s00(arg0, 0x4000, arg0->rotation_24.vy);
            sharedFunc_800DE034_2_s00(arg0, (VECTOR3*)&arg0->properties_E4.dummy.properties_E8[4], 0x3000);
            arg0->model_0.stateStep_3 = 1;
            break;

        case 0x1:
            var_s4                                             = 1;
            arg0->properties_E4.dummy.properties_E8[0xE].val32 = 0x8000;
            arg0->model_0.stateStep_3                          = 2;

        case 0x2:
            temp_s0_3 = Math_Distance2dGet(&arg0->position_18, (VECTOR3*)&arg0->properties_E4.dummy.properties_E8[4]);
            temp_s1_2 = FP_ANGLE_NORM_S(func_80080478(&arg0->position_18, (VECTOR3*)&arg0->properties_E4.dummy.properties_E8[4]) - arg0->rotation_24.vy);
            temp_v0   = sharedFunc_800DC598_2_s00(arg0);

            if (temp_v0 == 1)
            {
                arg0->model_0.stateStep_3 = 3;
            }
            else if (temp_v0 == 2)
            {
                arg0->model_0.stateStep_3 = 5;
            }
            else if ((temp_s0_3 < 0x1000 && (temp_s1_2 > -0x39 && temp_s1_2 < 0x39)) ||
                     arg0->properties_E4.dummy.properties_E8[0xD].val32 < 0)
            {
                arg0->model_0.stateStep_3 = 0;
            }
            else if (arg0->properties_E4.dummy.properties_E8[0xE].val32 == 0)
            {
                arg0->model_0.stateStep_3 = 1;
            }
            else if (var_s4 != 0)
            {
                if (sharedFunc_800DC200_2_s00(arg0) && temp_s0_3 > 0x6000)
                {
                    arg0->model_0.stateStep_3 = 5;
                }
                else if (sharedFunc_800DC30C_2_s00(arg0))
                {
                    if (temp_s0_3 >= 0x1800 || (Rng_RandQ12() >= 0x800))
                    {
                        // @hack This check should be `if (diff >= Q12(-1.0f) && diff < Q12(1.0f))`,
                        // but that results in `sltiu 0x2000` instead of the `li 0x2000/sltu` needed.
                        if (Math_CheckSignedRange(arg0->properties_E4.unk0.field_F8.vy - arg0->position_18.vy, Q12(1.0f)))
                        {
                            arg0->model_0.stateStep_3 = 3;
                        }
                    }
                    else
                    {
                        arg0->model_0.stateStep_3 = 3;
                    }
                }
            }
            break;

        case 0x3:
            if (temp_s0 == 0x33 || temp_s0 == 0x2F)
            {
                var_s3                        = 1;
                arg0->model_0.anim_4.status_0 = 0x2C;
                arg0->model_0.stateStep_3     = 4;
            }
            break;

        case 0x4:
            var_s3 = 1;
            break;

        case 0x5:
            if (temp_s0 == 0x33 || temp_s0 == 0x2F)
            {
                var_s3                        = 2;
                arg0->model_0.anim_4.status_0 = 0x30;
                arg0->model_0.stateStep_3     = 6;
            }
            break;

        case 0x6:
            var_s3 = 2;
            break;
    }

    sharedFunc_800DF448_2_s00(arg0, 0);

    switch (Ai_AirScreamer_DamageTake(arg0, 0x1000))
    {
        case 0:
            switch (var_s3)
            {
                case 0:
                    if (temp_s5 | temp_s6 | temp_s7)
                    {
                        arg0->model_0.controlState_2 = 6;
                        arg0->model_0.stateStep_3    = 0;
                    }
                    break;

                case 1:
                    if (temp_fp == 2)
                    {

                        if (temp_s5 | temp_s6 | temp_s7)
                        {
                            arg0->model_0.controlState_2 = 0x14;
                        }
                        else
                        {
                            arg0->model_0.controlState_2 = 0x12;
                        }
                        arg0->model_0.stateStep_3 = 0;
                    }
                    break;

                case 2:
                    if (temp_fp == 3)
                    {
                        if (temp_s5 | temp_s6 | temp_s7)
                        {
                            arg0->model_0.controlState_2 = 0x23;
                        }
                        else
                        {
                            arg0->model_0.controlState_2 = 0x21;
                        }
                        arg0->model_0.stateStep_3 = 0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            arg0->model_0.controlState_2                       = 0x10;
            arg0->model_0.stateStep_3                          = 0;
            arg0->properties_E4.dummy.properties_E8[13].val32 |= 8;
            break;

        case 3:
        case 4:
            arg0->model_0.controlState_2 = 0x11;
            arg0->model_0.stateStep_3    = 0;
            if (arg0->health_B0 <= 0)
            {
                arg0->properties_E4.dummy.properties_E8[13].val32 |= 0x40;
            }
            else
            {
                arg0->properties_E4.dummy.properties_E8[13].val32 |= 8;
            }
            break;
    }
}