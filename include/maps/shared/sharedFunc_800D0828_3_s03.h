void sharedFunc_800D0828_3_s03(s_SubCharacter* harry, GsCOORDINATE2* coords)
{
    typedef enum _BoneMatIdx
    {
        BoneMatIdx_Torso     = 0,
        BoneMatIdx_Head      = 1,
        BoneMatIdx_RightShin = 2,
        BoneMatIdx_LeftShin  = 3,

        BoneMatIdx_Count     = 4
    } e_BoneMatIdx;

    MATRIX          boneMats[BoneMatIdx_Count];
    VECTOR3         unkPos;
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
    s_SubCharacter* localHarry;

    localHarry = harry;

    // Get torso, head, right shin, and left shin bone matrices.
    Vw_CoordHierarchyMatrixCompute(&coords[HarryBone_Torso],     &boneMats[BoneMatIdx_Torso]);
    Vw_CoordHierarchyMatrixCompute(&coords[HarryBone_Head],      &boneMats[BoneMatIdx_Head]);
    Vw_CoordHierarchyMatrixCompute(&coords[HarryBone_RightShin], &boneMats[BoneMatIdx_RightShin]);
    Vw_CoordHierarchyMatrixCompute(&coords[HarryBone_LeftShin],  &boneMats[BoneMatIdx_LeftShin]);

    posY             = localHarry->position_18.vy;
    rightShinPosY    = Q8_TO_Q12(boneMats[BoneMatIdx_RightShin].t[1]);
    leftShinPosY     = Q8_TO_Q12(boneMats[BoneMatIdx_LeftShin].t[1]);
    harry->field_C8.field_0  = Q8_TO_Q12(boneMats[BoneMatIdx_Head].t[1]);
    offsetPosY       = posY + Q12(0.25f);
    harry->field_C8.field_0 -= offsetPosY;
    harry->field_C8.field_2  = posY;

    if (rightShinPosY >= leftShinPosY)
    {
        harry->field_C8.field_4 = leftShinPosY - harry->field_C8.field_2;
    }
    else
    {
        harry->field_C8.field_4 = rightShinPosY - harry->field_C8.field_2;
    }

    // `((torsoPosY - headPosY) / 2) - posY`
    harry->field_C8.field_6 = ((Q8_TO_Q12(boneMats[BoneMatIdx_Head].t[1]) + Q8_TO_Q12(boneMats[BoneMatIdx_Torso].t[1])) / 2) - posY;

    unkQ12 = sharedFunc_800CD6B0_3_s03(boneMats, ARRAY_SIZE(boneMats), &unkPos);
    deltaX = unkPos.vx - harry->position_18.vx;
    deltaY = unkPos.vz - harry->position_18.vz;

    unkQ12                    = sharedFunc_800CD940_3_s03(unkQ12 + Q12(0.05f), harry->field_D4.field_0);
    harry->field_D4.field_2   = unkQ12 - Q12(0.05f);
    harry->field_D4.field_0   = unkQ12;
    harry->field_D8.offsetX_0 = deltaX;
    harry->field_D8.offsetZ_2 = deltaY;

    sharedFunc_800CD920_3_s03(harry, deltaX, deltaY);

    tempPosComp                             = harry->position_18.vx;
    localHarry->properties_E4.npc.position_E8.vx = tempPosComp;
    tempPosComp                             = harry->position_18.vz;
    localHarry->properties_E4.npc.position_E8.vz = tempPosComp;
}
