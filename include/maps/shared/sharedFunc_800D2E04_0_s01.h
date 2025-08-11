bool sharedFunc_800D2E04_0_s01(s_SubCharacter* chara, VECTOR3* vecIn, s32* outDistance, s32* outAngle)
{
    s32 tmp;
    
    u8 indexInfo = g_SysWork.field_2388.field_154.field_0.field_0.field_0;
    s32 index = (indexInfo & 2) ? ((indexInfo & 1) ? 2 : 3) : (sharedFunc_800D4A80_0_s01(chara) == 3);

    s32 xDelta = vecIn->vx - chara->position_18.vx;
    s32 zDelta = vecIn->vz - chara->position_18.vz;

    s32 temp_s4 = (u16)sharedData_800CAA98_0_s01.properties_D14[index].val16[0];
    s32 temp_s3 = (u16)sharedData_800CAA98_0_s01.properties_D14[index].val16[1];

    s32 angle = FP_ANGLE_TRUNCATE(ratan2(xDelta, zDelta) - (chara->rotation_24.vy + chara->rotation_24.pad));
    s32 distance = SquareRoot12(FP_MULTIPLY_PRECISE(xDelta, xDelta, 12) + FP_MULTIPLY_PRECISE(zDelta, zDelta, 12));
    
    if (outDistance != NULL)
    {
        *outDistance = distance;
    }
    if (outAngle != NULL)
    {
        *outAngle = angle;
    }

    tmp = angle + temp_s3;
    if ((u32)temp_s3 * 2 >= tmp && temp_s4 >= distance)
    {
        sharedData_800DE170_0_s01.vx = chara->position_18.vx;
        sharedData_800DE170_0_s01.vy = chara->position_18.vy + chara->field_C8; // Head offset
        sharedData_800DE170_0_s01.vz = chara->position_18.vz;
        return func_8006D90C(&sharedData_800E2330_0_s01, &sharedData_800DE170_0_s01, vecIn) == 0;
    }
    return false;
}
