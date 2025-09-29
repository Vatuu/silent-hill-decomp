void sharedFunc_800D6554_0_s00(s_SubCharacter* chara)
{
    s32  someDist;
    s16  someRotY;
    s32  var;
    u16* flags;

    someDist = FP_TO(SquareRoot0(SQUARE(FP_FROM(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx, 6)) +
                                 SQUARE(FP_FROM(g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz, 6))),
                     6);

    someRotY = func_8005BF38((s16)(ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                                          g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) -
                             chara->rotation_24.vy));

    if (!(g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3))
    {
        var = func_8006FD90(chara, 0, 0x7800, 0x7800);
    }
    else if ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) == 2)
    {
#if defined(MAP1_S00) || defined(MAP1_S01)
        var = func_8006FD90(chara, 0, 0xC000, 0);
#else
        var = func_8006FD90(chara, 0, 0x10000, 0);
#endif
    }
    else
    {
        var = func_8006FD90(chara, 1, 0x666, 0xCCC);
    }

    var |= func_80070360(chara, someDist, Q12(1.0f));
    if (var == 0)
    {
        return;
    }

    chara->properties_E4.player.field_F0 = g_SysWork.player_4C.chara_0.position_18.vx;
    chara->properties_E4.player.field_F4 = g_SysWork.player_4C.chara_0.position_18.vz;

    if (someDist < Q12(1.2f) && someRotY < FP_ANGLE(180.0f))
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

        *GET_PROPERTY_LOW(chara->properties_E4.player.exhaustionTimer_FC)  = 0x37;
        *GET_PROPERTY_HIGH(chara->properties_E4.player.exhaustionTimer_FC) = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 0x1AB;
        *GET_PROPERTY_LOW(chara->properties_E4.player.afkTimer_E8) |= 1 << 10;

        sharedFunc_800D7E04_0_s00(chara, 0x553);
    }
}
