void sharedFunc_800D0828_3_s03(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    MATRIX          boneMats[4];
    VECTOR3         unkPos;
    s32             unused[2];
    q19_12          deltaX;
    q19_12          deltaY;
    q19_12          unkQ12;
    q19_12          posY;
    q19_12          offsetPosY;
    q19_12          torsoPosY;
    q19_12          headPosY;
    q19_12          rightShinPosY;
    q19_12          leftShinPosY;
    q19_12          tempPosComp;
    s_SubCharacter* charaCpy;

    charaCpy = chara;

    // Get torso, head, right shin, and left shin bone matrices.
    Vw_CoordHierarchyMatrixCompute(&coords[HarryBone_Torso],     &boneMats[0]);
    Vw_CoordHierarchyMatrixCompute(&coords[HarryBone_Head],      &boneMats[1]);
    Vw_CoordHierarchyMatrixCompute(&coords[HarryBone_RightShin], &boneMats[2]);
    Vw_CoordHierarchyMatrixCompute(&coords[HarryBone_LeftShin],  &boneMats[3]);

    posY             = charaCpy->position_18.vy;
    rightShinPosY    = Q8_TO_Q12(boneMats[2].t[1]);
    leftShinPosY     = Q8_TO_Q12(boneMats[3].t[1]);
    chara->field_C8  = Q8_TO_Q12(boneMats[1].t[1]);
    offsetPosY       = posY + Q12(0.25f);
    chara->field_C8 -= offsetPosY;
    chara->field_CA  = posY;

    if (rightShinPosY >= leftShinPosY)
    {
        chara->field_CC = leftShinPosY - chara->field_CA;
    }
    else
    {
        chara->field_CC = rightShinPosY - chara->field_CA;
    }

    // `((torsoPosY - headPosY) / 2) - posY`
    chara->field_CE = ((Q8_TO_Q12(boneMats[1].t[1]) + Q8_TO_Q12(boneMats[0].t[1])) >> 1) - posY;

    unkQ12 = sharedFunc_800CD6B0_3_s03(boneMats, 4, &unkPos);
    deltaX = unkPos.vx - chara->position_18.vx;
    deltaY = unkPos.vz - chara->position_18.vz;

    unkQ12                    = sharedFunc_800CD940_3_s03(unkQ12 + Q12(0.05f), chara->field_D4);
    chara->field_D6           = unkQ12 - Q12(0.05f);
    chara->field_D4           = unkQ12;
    chara->field_D8.offsetX_0 = deltaX;
    chara->field_D8.offsetZ_2 = deltaY;

    sharedFunc_800CD920_3_s03(chara, deltaX, deltaY);

    tempPosComp                             = chara->position_18.vx;
    charaCpy->properties_E4.npc.field_E8.vx = tempPosComp;
    tempPosComp                             = chara->position_18.vz;
    charaCpy->properties_E4.npc.field_E8.vz = tempPosComp;
}
