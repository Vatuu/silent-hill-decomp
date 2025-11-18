bool sharedFunc_800D2E04_0_s01(s_SubCharacter* chara, VECTOR3* inVec, s32* outDist, s32* outAngle)
{
    s32 tmp;
    u8  idxInfo;
    s32 idx;
    s32 deltaX;
    s32 deltaZ;
    s32 temp_s4;
    s32 temp_s3;
    s32 angle;
    s32 dist;

    idxInfo = g_SysWork.field_2388.field_154.field_0.field_0.field_0;
    idx     = (idxInfo & (1 << 1)) ? ((idxInfo & (1 << 0)) ? 2 : 3) : (sharedFunc_800D4A80_0_s01(chara) == 3);

    deltaX = inVec->vx - chara->position_18.vx;
    deltaZ = inVec->vz - chara->position_18.vz;

    temp_s4 = (u16)sharedData_800CAA98_0_s01.properties_D14[idx].val16[0];
    temp_s3 = (u16)sharedData_800CAA98_0_s01.properties_D14[idx].val16[1];

    angle = FP_ANGLE_NORM_S(ratan2(deltaX, deltaZ) - (chara->rotation_24.vy + chara->field_2A));
    dist  = SquareRoot12(FP_MULTIPLY_PRECISE(deltaX, deltaX, 12) + FP_MULTIPLY_PRECISE(deltaZ, deltaZ, 12));

    if (outDist != NULL)
    {
        *outDist = dist;
    }
    if (outAngle != NULL)
    {
        *outAngle = angle;
    }

    tmp = angle + temp_s3;
    if (((u32)temp_s3 * 2) >= tmp && temp_s4 >= dist)
    {
        sharedData_800DE170_0_s01.vx = chara->position_18.vx;
        sharedData_800DE170_0_s01.vy = chara->position_18.vy + chara->field_C8; // Head offset.
        sharedData_800DE170_0_s01.vz = chara->position_18.vz;
        return !func_8006D90C(&sharedData_800E2330_0_s01, &sharedData_800DE170_0_s01, inVec);
    }

    return false;
}
