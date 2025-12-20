void sharedFunc_800D6554_0_s00(s_SubCharacter* chara)
{
    q19_12 dist;
    q3_12  angle;
    s32    cond; // Not `bool`?
    u16*   flags;

    dist = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                               g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);
    angle = func_8005BF38((s16)(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz) -
                          chara->rotation_24.vy));

    if (!(g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))))
    {
        cond = func_8006FD90(chara, 0, Q12(7.5f), Q12(7.5f));
    }
    else if ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1))
    {
#if defined(MAP1_S00) || defined(MAP1_S01)
        cond = func_8006FD90(chara, 0, Q12(12.0f), Q12(0.0f));
#else
        cond = func_8006FD90(chara, 0, Q12(16.0f), Q12(0.0f));
#endif
    }
    else
    {
        cond = func_8006FD90(chara, 1, Q12(0.4f), Q12(0.8f));
    }

    cond |= func_80070360(chara, dist, Q12(1.0f));
    if (cond == 0)
    {
        return;
    }

    chara->properties_E4.player.field_F0 = g_SysWork.playerWork_4C.player_0.position_18.vx;
    chara->properties_E4.player.field_F4 = g_SysWork.playerWork_4C.player_0.position_18.vz;

    if (dist < Q12(1.2f) && angle < FP_ANGLE(180.0f))
    {
        flags = &chara->properties_E4.player.afkTimer_E8;
        if (!(*flags & (1 << 1)))
        {
            chara->model_0.state_2 = 3;
        }
        else
        {
            chara->model_0.state_2 = 2;
        }

        chara->model_0.anim_4.status_0 = ANIM_STATUS(30, false);

        *GET_PROPERTY_LOW(chara->properties_E4.player.exhaustionTimer_FC)  = 55;
        *GET_PROPERTY_HIGH(chara->properties_E4.player.exhaustionTimer_FC) = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 427;
        *GET_PROPERTY_LOW(chara->properties_E4.player.afkTimer_E8) |= 1 << 10;

        sharedFunc_800D7E04_0_s00(chara, 1363);
    }
}
