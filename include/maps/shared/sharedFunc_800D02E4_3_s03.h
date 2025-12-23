void sharedFunc_800D02E4_3_s03(s_SubCharacter* nurse, GsCOORDINATE2* coords)
{
    VECTOR3         pos;
    MATRIX          mat; // "Hierarchy matrix"?
    s32             weaponAttack;
    q19_12          posX;
    q19_12          posY;
    q19_12          posZ;
    s_SubCharacter* localNurse;

    localNurse = nurse;
    nurse->properties_E4.puppetNurse.flags_122 &= ~PuppetNurseFlag_0;

    if (localNurse->model_0.state_2 == 1 || localNurse->model_0.state_2 == 5)
    {
        Vw_CoordHierarchyMatrixCompute(&coords[10], &mat);
        posX = Q8_TO_Q12(mat.t[0]);
        posY = Q8_TO_Q12(mat.t[1]);
        posZ = Q8_TO_Q12(mat.t[2]);

        nurse->field_C8.field_8 = nurse->position_18.vy - posY;
        pos.vx = posX;
        pos.vy = posY;
        pos.vz = posZ;
        
        if (localNurse->model_0.state_2 == 1)
        {
            weaponAttack = localNurse->properties_E4.npc.field_124->field_20;
        }
        else
        {
            // TODO: What's weapon attack 56?
            weaponAttack = 56;
        }

        if (func_8008A0E4(1, weaponAttack, nurse, &pos, &g_SysWork.playerWork_4C.player_0, nurse->rotation_24.vy, FP_ANGLE(90.0f)) != NO_VALUE)
        {
            localNurse->properties_E4.puppetNurse.flags_122 |= PuppetNurseFlag_0;
        }
    }
}
