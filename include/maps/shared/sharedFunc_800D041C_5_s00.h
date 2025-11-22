void sharedFunc_800D041C_5_s00(s_SubCharacter* chara)
{
    q19_12 playerDist;

    playerDist = Math_Vector2MagCalc(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                                     g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);

    // TODO: Invert to return early instead?
    if (playerDist < Q12(1.0f) &&
        !func_800700F8(chara, &g_SysWork.player_4C.chara_0) &&
        (((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) == 2 && func_8006FD90(chara, 1, Q12(2.0f), Q12(1.5f))) ||
         ((g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) &&
          (g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)) &&
          func_8006FD90(chara, 1, Q12(1.5f), Q12(0.3f)))))
    {
        chara->model_0.state_2         = 3;
        chara->model_0.anim_4.status_0 = ANIM_STATUS(17, false);
    }
}
