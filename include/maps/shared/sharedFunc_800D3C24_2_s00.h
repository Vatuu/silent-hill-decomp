void sharedFunc_800D3C24_2_s00(s_SubCharacter* airScreamer)
{
    bool cond0;
    bool isBelowGround;
    bool cond1;
    s32  animStatus;
    s32  animState;
    s32  animStatusCheck;
    u32  tmp0;
    u32  step;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus = airScreamer->model_0.anim_4.status_0;
    sharedFunc_800D5638_0_s01(airScreamer);
    step      = airScreamer->model_0.stateStep_3;
    animState = ANIM_STATUS(12, true);

    animStatusCheck = animStatus | 1; // TODO: Use macro.

    switch (step)
    {
        case 0:
            cond1         = sharedFunc_800D5F00_0_s01(airScreamer);
            isBelowGround = false;
            cond0 = airScreamer->position_18.vy >= Q12(8.0f);

            if (func_800808AC(airScreamer->position_18.vx, airScreamer->position_18.vz) == 7)
            {
                isBelowGround = airScreamer->position_18.vy >= Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz);
            }

            if (cond0)
            {
                Ai_AirScreamer_DamageTake(airScreamer, Q12(0.0f));

                airScreamer->position_18.vx = g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(100.0f);
                airScreamer->position_18.vz = g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(100.0f);

                sharedFunc_800D3DFC_0_s01(airScreamer);
                break;
            }

            if (isBelowGround)
            {
                Ai_AirScreamer_DamageTake(airScreamer, Q12(0.0f));
                sharedFunc_800D2364_0_s01(airScreamer);

                airScreamer->position_18.vx = g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(100.0f);
                airScreamer->position_18.vz = g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(100.0f);

                sharedFunc_800D3DFC_0_s01(airScreamer);
                break;
            }

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                Ai_AirScreamer_DamageTake(airScreamer, Q12(0.0f));

                if (animStatus == ANIM_STATUS(AirScreamerAnim_26, true) && cond1 == true)
                {
                    airScreamer->health_B0 = NO_VALUE;
                    func_800622B8(3, airScreamer, ANIM_STATUS(AirScreamerAnim_4, true), 2);

                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
                    sharedFunc_800D3DFC_0_s01(airScreamer);
                }
            }
            else
            {
                airScreamer->flags_3E |= CharaFlag_Unk2;

                if (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)) == 4)
                {
                    if (airScreamer->health_B0 <= Q12(0.0f))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_5, false);
                        airScreamerProps.flags_11C |= PlayerFlag_Unk6;
                        break;
                    }

                    airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_12, false);
                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                    airScreamerProps.flags_11C |= PlayerFlag_WallStopRight;
                }
            }
            break;

        case 1:
            Ai_AirScreamer_DamageTake(airScreamer, Q12(0.0f));
            break;

        case 2:
            Ai_AirScreamer_DamageTake(airScreamer, Q12(0.5f));

            if (animStatusCheck != animState)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;
    }

    #undef airScreamerProps
}
