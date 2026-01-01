bool sharedFunc_800DBF88_2_s00(s_SubCharacter* airScreamer, s32 arg1)
{
    q19_12   posX;
    q19_12   posY;
    q19_12   posZ;
    q19_12   posDeltaX;
    q19_12   posDeltaY;
    q19_12   posDeltaZ;
    q19_12   charaFieldC8;
    s32      unkPosY;
    VECTOR3* unkVec;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    if (sharedData_800E21D0_0_s01.flags_0 & (1 << 27))
    {
        unkVec = &airScreamerProps.position_110;
    }
    else
    {
        unkVec = &airScreamerProps.targetPosition_F8;
    }

    posX = airScreamer->position_18.vx;
    posY = airScreamer->position_18.vy;
    posZ = airScreamer->position_18.vz;

    posDeltaX = unkVec->vx - posX;
    posDeltaY = unkVec->vy - posY;
    posDeltaZ = unkVec->vz - posZ;

    unkPosY = unkVec->vy;

    charaFieldC8 = airScreamer->field_C8.field_0;

    func_8006F250(sharedData_800E2370_0_s01, posX, posZ, posDeltaX, posDeltaZ);

    if (arg1 >= sharedData_800E2370_0_s01[0] && (Collision_GroundHeightGet(posX, posZ) + charaFieldC8) >= sharedData_800E2370_0_s01[1])
    {
        if (posDeltaY < Q12(0.0f))
        {
            if ((posY + charaFieldC8) < sharedData_800E2370_0_s01[1])
            {
                return true;
            }
        }
        else
        {
            if ((unkPosY + charaFieldC8) < sharedData_800E2370_0_s01[1])
            {
                return true;
            }
        }
    }

    return false;

    #undef airScreamerProps
}
