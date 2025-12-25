void sharedFunc_800D041C_5_s00(s_SubCharacter* scratcher)
{
    q19_12 distToPlayer;

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);

    // TODO: Invert to return early instead?
    if (distToPlayer < Q12(1.0f) &&
        !func_800700F8(scratcher, &g_SysWork.playerWork_4C.player_0) &&
        (((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) == 2 && func_8006FD90(scratcher, 1, Q12(2.0f), Q12(1.5f))) ||
         ((g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) &&
          (g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)) &&
          func_8006FD90(scratcher, 1, Q12(1.5f), Q12(0.3f)))))
    {
        scratcher->model_0.state_2         = 3;
        scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_Unk17, false);
    }
}
