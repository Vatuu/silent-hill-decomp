s32 sharedFunc_800D3814_0_s01(s_SubCharacter* chara)
{
    s32 angleFacingOffset;
    s32 distResult;
    s32 distProp8;

    s32 angleTowards = func_80080478(&g_SysWork.player_4C.chara_0.position_18, &chara->position_18);
    s32 playerFacing = g_SysWork.player_4C.chara_0.rotation_24.vy;
    s32 distInverse = FP_METER(8.0f) - Math_Distance2d(&g_SysWork.player_4C.chara_0.position_18, &chara->position_18);
    if (distInverse < 0)
    {
        distInverse = 0;
    }
    else
    {
        distInverse = distInverse >> 3;
    }

    angleFacingOffset = ABS_32(FP_ANGLE_TRUNCATE(angleTowards - playerFacing));

    if (distInverse >= angleFacingOffset)
    {
        distResult = (distInverse - angleFacingOffset) * 4;
    }
    else
    {
        distResult = 0;
    }
    
    if (D_800C457E != 0)
    {
        distProp8 = func_8007FD2C(distInverse);
        if (distProp8 > FP_METER(2.0))
        {
            distResult += FP_METER(2.0);
        }
        else
        {
            distResult += distProp8;
        }

        if (chara == &g_SysWork.npcs_1A0[g_SysWork.field_2353])
        {
            distResult += FP_METER(1.0);
        }
    }
    else
    {
        distResult += FP_METER(0.5);
    }
    return distResult;
}
