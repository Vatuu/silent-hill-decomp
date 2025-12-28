bool sharedFunc_800D7EBC_0_s01(s_SubCharacter* airScreamer)
{
    s32                temp_v0;
    s32                temp_v1_2;
    s32                animStatus;
    VECTOR3*           vec;
    GsCOORDINATE2*     coords;
    s_SubCharacter_44* temp_s1;
    s_PlayerWork*      player;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    player = &g_SysWork.playerWork_4C;

    animStatus = airScreamer->model_0.anim_4.status_0;
    temp_s1    = &airScreamer->field_44;

    if (!(player->player_0.flags_3E & CharaFlag_Unk4) &&
        g_SysWork.npcIdxs_2354[0] == NO_VALUE && g_SysWork.npcIdxs_2354[1] == NO_VALUE &&
        airScreamer->model_0.controlState_2 != AirScreamerControl_12 && airScreamer->model_0.controlState_2 != AirScreamerControl_25 &&
        airScreamer->model_0.controlState_2 != AirScreamerControl_40 && airScreamer->model_0.controlState_2 != AirScreamerControl_49)
    {
        airScreamer->field_44.field_0 = 0;
    }
    else
    {
        vec    = sharedData_800E21D0_0_s01.matrices_C;
        coords = sharedData_800E21D0_0_s01.coords_8;

        switch (animStatus)
        {
            case ANIM_STATUS(AirScreamerAnim_2, true):
            case ANIM_STATUS(AirScreamerAnim_1, true):
                if (temp_s1->field_0 == 0)
                {
                    if (animStatus == ANIM_STATUS(AirScreamerAnim_1, true))
                    {
                        temp_s1->field_2 = 40;
                    }
                    else
                    {
                        temp_s1->field_2 = 41;
                    }

                    temp_s1->field_0 = 1;
                }

                func_800805BC(&vec[0], sharedData_800CAA98_0_s01.ptr_D48[1], &coords[sharedData_800CAA98_0_s01.ptr_D48[1]->pad], 2);

                temp_v0           = func_80080478(&vec[0], &vec[1]);
                temp_v1_2         = temp_v0 >> 16;
                temp_s1->field_18 = *vec;
                temp_s1->field_C  = temp_v0;
                temp_s1->field_E  = temp_v1_2;

                if (func_8008A3E0(airScreamer) != 0)
                {
                    airScreamerProps.flags_11C |= PlayerFlag_Unk0;
                }
                break;

            case ANIM_STATUS(AirScreamerAnim_3, true):
                if (temp_s1->field_0 == 0)
                {
                    temp_s1->field_2 = 42;
                    temp_s1->field_0 = 1;
                }

                func_800805BC(vec, sharedData_800CAA98_0_s01.ptr_D48[2], &coords[sharedData_800CAA98_0_s01.ptr_D48[2]->pad], 2);
                func_800805BC(&vec[2], sharedData_800CAA98_0_s01.ptr_D48[3], &coords[sharedData_800CAA98_0_s01.ptr_D48[3]->pad], 2);

                vec[0].vx = (vec[0].vx + vec[2].vx) / 2;
                vec[0].vy = (vec[0].vy + vec[2].vy) / 2;
                vec[0].vz = (vec[0].vz + vec[2].vz) / 2;
                vec[1].vx = (vec[1].vx + vec[3].vx) / 2;
                vec[1].vy = (vec[1].vy + vec[3].vy) / 2;
                vec[1].vz = (vec[1].vz + vec[3].vz) / 2;

                temp_v0   = func_80080478(vec, &vec[1]);
                temp_v1_2 = temp_v0 >> 16;

                temp_s1->field_18 = sharedData_800E21D0_0_s01.matrices_C[0];
                temp_s1->field_C  = temp_v0;
                temp_s1->field_E  = temp_v1_2;

                if (func_8008A3E0(airScreamer) != 0)
                {
                    airScreamerProps.flags_11C |= CharaUnk0Flag_Unk1;
                }
                break;
        }
    }

    return true;

    #undef airScreamerProps
}
