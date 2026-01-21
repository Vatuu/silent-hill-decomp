void Ai_HangedScratcher_Control_6(s_SubCharacter* scratcher)
{
    s32 playerDist;
    u16 temp_v1;

    playerDist = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                     g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);

    Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

    if (scratcher->properties_E4.hangedScratcher.field_EA == 0 &&
        scratcher->model_0.anim_4.status_0 == ANIM_STATUS(15, true))
    {
        if (playerDist < Q12(12.0f) && !Rng_GenerateInt(0, 127))
        {
            scratcher->model_0.controlState_2  = 7;
            scratcher->model_0.anim_4.status_0 = 0x24;
        }
        else if (playerDist < Q12(6.0f) && !Rng_GenerateInt(0, 15))
        {
            scratcher->model_0.controlState_2  = 7;
            scratcher->model_0.anim_4.status_0 = 0x24;
        }
    }

    // @bug Weird function pointer check, code will never be ran?
    if (&sharedFunc_800D3214_5_s00 == NULL && playerDist > Q12(24.0f))
    {
        scratcher->model_0.controlState_2 = 0;
        scratcher->model_0.stateStep_3    = 3;
    }

    temp_v1                                           = scratcher->properties_E4.hangedScratcher.field_EA;
    scratcher->properties_E4.hangedScratcher.field_EA = MAX(0, temp_v1 - g_DeltaTime0);
}
