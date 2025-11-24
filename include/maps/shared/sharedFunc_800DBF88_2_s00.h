bool sharedFunc_800DBF88_2_s00(s_SubCharacter* chara, s32 arg1)
{
    s32      charaPosX;
    s32      charaPosY;
    s32      charaPosZ;
    s32      charaFieldC8;
    s32      unkPosX;
    s32      unkPosY;
    s32      unkPosZ;
    s32      posYDelta;
    VECTOR3* unkVec;

    if (sharedData_800E21D0_0_s01.flags_0 & (1 << 27))
    {
        unkVec = &chara->properties_E4.unk0.pos_110;
    }
    else
    {
        unkVec = &chara->properties_E4.unk0.field_F8;
    }

    charaPosX = chara->position_18.vx;
    charaPosY = chara->position_18.vy;
    charaPosZ = chara->position_18.vz;

    unkPosX = unkVec->vx;
    unkPosY = unkVec->vy;
    unkPosZ = unkVec->vz;

    posYDelta = unkVec->vy - chara->position_18.vy;

    charaFieldC8 = chara->field_C8;

    func_8006F250(sharedData_800E2370_0_s01, charaPosX, charaPosZ, unkPosX - charaPosX, unkPosZ - charaPosZ);

    if (arg1 >= sharedData_800E2370_0_s01[0] && func_80080884(charaPosX, charaPosZ) + charaFieldC8 >= sharedData_800E2370_0_s01[1])
    {
        if (posYDelta < 0)
        {
            if (charaPosY + charaFieldC8 < sharedData_800E2370_0_s01[1])
            {
                return true;
            }
        }
        else
        {
            if (unkPosY + charaFieldC8 < sharedData_800E2370_0_s01[1])
            {
                return true;
            }
        }
    }

    return false;
}
