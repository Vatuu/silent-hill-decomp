void sharedFunc_800D0828_3_s03(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    MATRIX          sp10[4];
    s_SubCharacter* chara2;
    VECTOR3         sp90;
    s32             unused[2];

    s32 deltaX;
    s32 deltaY;
    s32 temp_v1;
    s32 temp_v0;
    s32 temp_v0_4;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a3;

    chara2 = chara;

    Vw_CoordHierarchyMatrixCompute(&coords[1], &sp10[0]);
    Vw_CoordHierarchyMatrixCompute(&coords[2], &sp10[1]);
    Vw_CoordHierarchyMatrixCompute(&coords[16], &sp10[2]);
    Vw_CoordHierarchyMatrixCompute(&coords[13], &sp10[3]);

    temp_a3          = chara2->position_18.vy;
    temp_a0          = Q8_TO_Q12(sp10[2].t[1]);
    temp_a1          = Q8_TO_Q12(sp10[3].t[1]);
    chara->field_C8  = Q8_TO_Q12(sp10[1].t[1]);
    temp_v1          = temp_a3 + Q12(0.25f);
    chara->field_C8 -= temp_v1;
    chara->field_CA  = temp_a3;

    if (temp_a0 >= temp_a1)
    {
        chara->field_CC = temp_a1 - chara->field_CA;
    }
    else
    {
        chara->field_CC = temp_a0 - chara->field_CA;
    }

    chara->field_CE = ((Q8_TO_Q12(sp10[1].t[1]) + Q8_TO_Q12(sp10[0].t[1])) >> 1) - temp_a3;

    temp_v0 = sharedFunc_800CD6B0_3_s03(sp10, 4, &sp90);
    deltaX  = sp90.vx - chara->position_18.vx;
    deltaY  = sp90.vz - chara->position_18.vz;

    temp_v0                   = sharedFunc_800CD940_3_s03(temp_v0 + 0xCC, chara->field_D4);
    chara->field_D6           = temp_v0 - 0xCC;
    chara->field_D4           = temp_v0;
    chara->field_D8.offsetX_0 = deltaX;
    chara->field_D8.offsetZ_2 = deltaY;

    sharedFunc_800CD920_3_s03(chara, deltaX, deltaY);

    temp_v0_4                             = chara->position_18.vx;
    chara2->properties_E4.npc.field_E8.vx = temp_v0_4;
    temp_v0_4                             = chara->position_18.vz;
    chara2->properties_E4.npc.field_E8.vz = temp_v0_4;
}
