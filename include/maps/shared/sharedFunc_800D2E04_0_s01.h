bool sharedFunc_800D2E04_0_s01(s_SubCharacter* chara, VECTOR3* inVec, q19_12* outDist, q19_12* outAngle)
{
    u8     idxInfo;
    s32    idx;
    q19_12 angle1;
    q19_12 deltaX;
    q19_12 deltaZ;
    q19_12 dist0;
    q19_12 angle0;
    q19_12 angle;
    q19_12 dist;

    idxInfo = g_SysWork.field_2388.field_154.field_0.field_0.field_0;
    idx     = (idxInfo & (1 << 1)) ? ((idxInfo & (1 << 0)) ? 2 : 3) : (sharedFunc_800D4A80_0_s01(chara) == 3);

    deltaX = inVec->vx - chara->position_18.vx;
    deltaZ = inVec->vz - chara->position_18.vz;

    dist0  = (u16)sharedData_800CAA98_0_s01.properties_D14[idx].val16[0];
    angle0 = (u16)sharedData_800CAA98_0_s01.properties_D14[idx].val16[1];

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

    angle1 = angle + angle0;
    if (((u32)angle0 * 2) >= angle1 && dist0 >= dist)
    {
        sharedData_800DE170_0_s01.vx = chara->position_18.vx;
        sharedData_800DE170_0_s01.vy = chara->position_18.vy + chara->field_C8.field_0; // Head offset.
        sharedData_800DE170_0_s01.vz = chara->position_18.vz;
        return !func_8006D90C(&sharedData_800E2330_0_s01, &sharedData_800DE170_0_s01, inVec);
    }

    return false;
}
