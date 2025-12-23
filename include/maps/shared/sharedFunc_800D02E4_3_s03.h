void sharedFunc_800D02E4_3_s03(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    VECTOR3 sp20;
    MATRIX sp30;
    s32 weaponAttack;
    s32 tmp1;
    s32 tmp2;
    s32 tmp3;
    s_SubCharacter *charaCpy;

    charaCpy = chara;
    chara->properties_E4.puppetNurse.flags_122 &= ~PuppetNurseFlag_0;
    if (charaCpy->model_0.state_2 == 1 || charaCpy->model_0.state_2 == 5)
    {
        Vw_CoordHierarchyMatrixCompute(&coords[10], &sp30);
        tmp1 = sp30.t[0] * 16;
        tmp2 = sp30.t[1] * 16;
        tmp3 = sp30.t[2] * 16;
        chara->field_C8.field_8 = chara->position_18.vy - tmp2;
        sp20.vx = tmp1;
        sp20.vy = tmp2;
        sp20.vz = tmp3;
        
        if (charaCpy->model_0.state_2 == 1)
        {
            weaponAttack = charaCpy->properties_E4.npc.field_124->field_20;
        }
        else
        {
            weaponAttack = 56;
        }
        if (func_8008A0E4(1, weaponAttack, chara, &sp20, &g_SysWork.playerWork_4C.player_0, chara->rotation_24.vy, 0x400) != -1)
        {
            charaCpy->properties_E4.puppetNurse.flags_122 |= PuppetNurseFlag_0;
        }
    }
}
