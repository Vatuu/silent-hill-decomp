s32 sharedFunc_800CF600_3_s03(s_SubCharacter* nurse)
{
    s32 temp_a3;
    s32 var_a1;
    s32 var_v0;
    s32 var_v1;

    temp_a3 = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - nurse->position_18.vx,
                                  g_SysWork.playerWork_4C.player_0.position_18.vz - nurse->position_18.vz) -
              0xC28;

    var_v0 = ABS(temp_a3);

    if (var_v0 > 0x7A && nurse->model_0.anim_4.status_0 != 0x28)
    {
        if (temp_a3 > 0)
        {
            var_a1 = 0x8000;
            var_v1 = Q12_MULT_PRECISE(nurse->properties_E4.puppetNurse.field_124->field_18, 0x1CCC);
        }
        else
        {
            var_v1 = -0x51;
            var_a1 = 0x2000;
        }
        Chara_MoveSpeedUpdate2(nurse, var_a1, var_v1);
    }
    else
    {
        Chara_MoveSpeedUpdate(nurse, 0x3000);
    }

    return temp_a3;
}