void sharedFunc_800E8A40_2_s02(s_SubCharacter* romper, s_AnmHeader* arg1, GsCOORDINATE2* arg2)
{
    typedef struct
    {
        MATRIX  field_0;
        SVECTOR field_20;
    } s_sharedFunc_800E8A40_2_s02;

    s32                          temp_v0_3;
    s32                          var_a1;
    s32                          temp_v0_4;
    s_AnimInfo*                  anim;
    s_sharedFunc_800E8A40_2_s02* ptr;

    ptr = PSX_SCRATCH;

    switch (romper->model_0.anim_4.status_0)
    {
        case 27:
        case 35:
        case 37:
            ROPMER_ANIM_INFOS[romper->model_0.anim_4.status_0].duration_8.constant = sharedData_800EC950_2_s02;
            break;

        case 28:
            sharedData_800ECB22_2_s02 = romper->properties_E4.romper.field_10C + 0x83;
            break;

        case 29:
            ROPMER_ANIM_INFOS[29].startKeyframeIdx_C                               = romper->properties_E4.romper.field_10C + 0x83;
            romper->properties_E4.romper.field_10C                                 = 0;
            ROPMER_ANIM_INFOS[romper->model_0.anim_4.status_0].duration_8.constant = Q12_MULT_PRECISE(MAX(romper->moveSpeed_38, 0x1800), 0x851E);
            break;

        case 38:
            sharedData_800ECBC2_2_s02 = romper->properties_E4.romper.field_10C + 0x6D;
            break;

        case 39:
            sharedData_800ECBD0_2_s02 = romper->properties_E4.romper.field_10C + 0x6D;
            break;
    }

    Math_MatrixTransform(&romper->position_18, (SVECTOR*)&romper->rotation_24, arg2);

    anim = &ROPMER_ANIM_INFOS[romper->model_0.anim_4.status_0];
    anim->updateFunc_0(&romper->model_0, arg1, arg2, anim);

    switch (romper->model_0.anim_4.status_0)
    {
        case 14:
            romper->model_0.controlState_2 = 6;
            if (romper->model_0.anim_4.time_4 == 0x7F000)
            {
                romper->model_0.anim_4.status_0 = 0xF;
                romper->model_0.anim_4.time_4   = 0x27000;
            }
            break;

        case 16:
            romper->model_0.controlState_2 = 6;
            if (romper->model_0.anim_4.time_4 == 0x74000)
            {
                romper->model_0.anim_4.status_0 = 0x11;
                romper->model_0.anim_4.time_4   = 0x32000;
            }
            break;

        case 26:
            if (romper->model_0.controlState_2 == 5)
            {
                romper->properties_E4.romper.flags_E8 &= ~0x800;
                g_SysWork.field_2284[3]               &= 0xFFFC;
            }

            romper->model_0.controlState_2        = 3;
            romper->properties_E4.romper.field_F4 = 0x15FFF;

            if (romper->model_0.anim_4.time_4 == 0x31000)
            {
                romper->model_0.anim_4.status_0       = 0x1B;
                romper->properties_E4.romper.field_F4 = 0xFFF;
                romper->model_0.anim_4.time_4         = 0x6E000;
                romper->properties_E4.romper.field_F0 = 0x477;
                romper->moveSpeed_38                  = 0;
            }
            else if (romper->model_0.anim_4.time_4 == 0x3C000)
            {
                romper->model_0.anim_4.status_0       = 0x1B;
                romper->properties_E4.romper.field_F4 = 0xAFFF;
                romper->properties_E4.romper.field_F0 = 0x79;
                romper->model_0.anim_4.time_4         = 0x78000;
                romper->moveSpeed_38                  = 0x1333;
            }
            break;

        case 39:
        case 41:
            romper->model_0.controlState_2        = 3;
            romper->model_0.anim_4.status_0       = 0x1B;
            romper->properties_E4.romper.field_F4 = romper->model_0.anim_4.time_4 - 0x6D001;
            break;
    }

    temp_v0_3 = func_8005BF38(romper->properties_E4.romper.field_EC - romper->rotation_24.vy);

    if (temp_v0_3 == 0)
    {
        var_a1 = 0;
    }
    else
    {
        var_a1 = 0xC4;
    }

    if (temp_v0_3 < 0)
    {
        var_a1 = -var_a1;
    }

    temp_v0_4 = Q12_MULT_PRECISE(g_DeltaTime0, 0x100);

    if (var_a1 < romper->properties_E4.romper.field_EE)
    {
        romper->properties_E4.romper.field_EE = MAX(var_a1, romper->properties_E4.romper.field_EE - temp_v0_4);
    }
    else
    {
        romper->properties_E4.romper.field_EE = CLAMP_HIGH(var_a1, romper->properties_E4.romper.field_EE + temp_v0_4);
    }

    *(s32*)&ptr->field_20 = romper->properties_E4.romper.field_EE << 16;
    ptr->field_20.vz      = 0;

    Math_RotMatrixZxyNegGte(&ptr->field_20, &ptr->field_0);
    MulMatrix2(&ptr->field_0, &arg2[2].coord);

    romper->properties_E4.romper.field_EC = romper->rotation_24.vy;
}