s32 sharedFunc_800D3814_0_s01(s_SubCharacter* chara)
{
    s32 headingAngleDelta;
    s32 invDist;
    s32 dist;
    s32 distProp8;
    s32 headingAngleTo;
    s32 headingAngleFrom;

    headingAngleTo = func_80080478(&g_SysWork.player_4C.chara_0.position_18, &chara->position_18);
    headingAngleFrom = g_SysWork.player_4C.chara_0.rotation_24.vy;

    invDist = Q12(8.0f) - Math_Distance2dGet(&g_SysWork.player_4C.chara_0.position_18, &chara->position_18);
    if (invDist < Q12(0.0f))
    {
        invDist = Q12(0.0f);
    }
    else
    {
        invDist = invDist >> 3;
    }

    headingAngleDelta = ABS_32(FP_ANGLE_NORM_S(headingAngleTo - headingAngleFrom));
    if (invDist >= headingAngleDelta)
    {
        dist = (invDist - headingAngleDelta) * 4;
    }
    else
    {
        dist = Q12(0.0f);
    }
    
    if (g_Player_IsAiming)
    {
        distProp8 = func_8007FD2C(invDist);
        if (distProp8 > Q12(2.0f))
        {
            dist += Q12(2.0f);
        }
        else
        {
            dist += distProp8;
        }

        if (chara == &g_SysWork.npcs_1A0[g_SysWork.enemyTargetIdx_2353])
        {
            dist += Q12(1.0f);
        }
    }
    else
    {
        dist += Q12(0.5f);
    }

    return dist;
}
