void sharedFunc_800DACA8_2_s00(s_SubCharacter* chara)
{
    s32  sp10;
    s32  temp_a0;
    s32  temp_s0_2;
    s32  temp_s3;
    s32  temp_s5;
    s32  temp_s7;
    s32  temp_v0;
    s32  var_s4;
    s32  temp_s6;
    bool new_var;
    s32  temp_s8;

    temp_s6 = chara->model_0.anim_4.status_0;
    var_s4  = 0;
    temp_v0 = sharedFunc_800D4A80_0_s01(chara);
    new_var = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    sp10    = new_var;

    temp_s5   = sharedData_800E21D0_0_s01.distance_150;
    temp_s7   = sharedData_800E21D0_0_s01.angle_154;
    temp_s8   = temp_v0;
    temp_s3   = Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8);
    temp_s0_2 = FP_ANGLE_NORM_S(func_80080478(&chara->position_18, &chara->properties_E4.unk0.field_F8) - chara->rotation_24.vy);
    temp_a0   = sharedFunc_800DC438_2_s00(chara);

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            sharedFunc_800DF24C_2_s00(chara);
            Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8);

            if (temp_s5 > 0x6000)
            {
                temp_s3 = 0x6000;
            }
            else if (temp_s5 > 0x2000)
            {
                temp_s3 = 0xC000 - temp_s5;
            }
            else
            {
                temp_s3 = 0xA000;
            }

            temp_s3  += Rng_RandQ12() * 2;
            temp_s0_2 = FP_ANGLE_NORM_S((temp_s7 + 0x800) - chara->rotation_24.vy) / 2 + chara->rotation_24.vy;

            sharedFunc_800DEC84_2_s00(chara, temp_s3, temp_s0_2 + (Rng_RandQ12() - 0x800) / 8);
            chara->properties_E4.unk0.properties_120.val32 = 0x5000;
            chara->model_0.stateStep_3                     = 1;
            break;

        case 1:
            if (temp_a0 == 2)
            {
                chara->model_0.stateStep_3 = 2;
            }
            else if (temp_a0 == 1)
            {
                chara->model_0.stateStep_3 = 4;
            }
            else if (temp_s3 < 0x2000 || Math_CheckSignedRange(temp_s0_2, 0x400) ||
                     chara->properties_E4.unk0.properties_120.val32 == 0)
            {
                var_s4 = 1;
            }
            break;

        case 2:
            if (temp_s6 == 0x23)
            {
                var_s4                         = 2;
                chara->model_0.anim_4.status_0 = 0x20;
                chara->model_0.stateStep_3     = 3;
            }
            break;

        case 3:
            var_s4 = 2;
            break;

        case 4:
            if (temp_s6 == 0x23)
            {
                var_s4                         = 3;
                chara->model_0.anim_4.status_0 = 0x1E;
                chara->model_0.stateStep_3     = 5;
            }
            break;

        case 5:
            var_s4 = 3;
            break;
    }

    sharedFunc_800E021C_2_s00(chara, 2, 0);

    switch (Ai_AirScreamer_DamageTake(chara, 0x1000))
    {
        case 0:
            switch (var_s4)
            {
                case 0:
                case 1:
                    if (sp10 != 0)
                    {
                        if (temp_s5 > 0x7000)
                        {
                            chara->model_0.controlState_2 = 0x26;
                            chara->model_0.stateStep_3    = 0;
                            break;
                        }
                    }

                    if (var_s4 == 1)
                    {
                        if (chara->properties_E4.unk0.field_E8_8 != 3)
                        {
                            chara->properties_E4.unk0.field_E8_8 = 2;
                        }
                        chara->model_0.controlState_2 = 0x29;
                        chara->model_0.stateStep_3    = 0;
                    }
                    break;

                case 2:
                    if (temp_s8 == 1)
                    {
                        chara->model_0.controlState_2 = 0xD;
                        chara->model_0.stateStep_3    = 0;
                    }
                    break;

                case 3:
                    if (temp_s8 == 2)
                    {
                        chara->model_0.controlState_2 = 0x1A;
                        chara->model_0.stateStep_3    = 0;
                    }
                    break;
            }
            break;
        case 1:
        case 2:
            chara->model_0.controlState_2        = 0x2C;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= 8;
            break;

        case 3:
        case 4:
            chara->model_0.controlState_2 = 0x2D;
            chara->model_0.stateStep_3    = 0;

            if (chara->health_B0 <= Q12(0.0f))
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }
}