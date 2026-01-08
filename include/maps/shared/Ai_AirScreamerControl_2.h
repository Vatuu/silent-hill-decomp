void Ai_AirScreamerControl_2(s_SubCharacter* airScreamer) // 0x800D3EB8
{
    q19_12 damage;
    bool   cond1;
    bool   isBelowGround;
    bool   temp_s3;
    u32    animStatus;
    s32    animStatus12;
    bool   activeAnimStatus;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    animStatus = airScreamer->model_0.anim_4.status_0;
    animStatus12 = ANIM_STATUS(AirScreamerAnim_12, true);

    sharedFunc_800D5638_0_s01(airScreamer);

    activeAnimStatus = ANIM_STATUS(ANIM_STATUS_IDX_GET(animStatus), true);

    // Handle state step.
    switch ((u32)airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            temp_s3 = sharedFunc_800D5F00_0_s01(airScreamer);
            isBelowGround = false;
            cond1 = airScreamer->position_18.vy >= Q12(8.0f);

            if (func_800808AC(airScreamer->position_18.vx, airScreamer->position_18.vz) == 7)
            {
                isBelowGround = airScreamer->position_18.vy >= Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz);
            }

            if (cond1)
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

                if (animStatus == ANIM_STATUS(AirScreamerAnim_26, true) && temp_s3 == true)
                {
                    airScreamer->health_B0 = NO_VALUE;

                    func_800622B8(3, airScreamer, ANIM_STATUS(AirScreamerAnim_4, true), 2);

                    airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;

                    sharedFunc_800D3DFC_0_s01(airScreamer);
                    break;
                }
            }
            else
            {
                airScreamer->flags_3E |= CharaFlag_Unk2;

                if (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)) == AirScreamerDamage_4)
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
                    break;
                }
#ifdef MAP0_S01
                damage = g_DeltaTime0 * 10;
                if (damage < airScreamer->health_B0)
                {
                    airScreamer->health_B0 -= damage;
                }
                else if (airScreamer->health_B0 > Q12(0.0f))
                {
                    airScreamer->health_B0 = Q12(0.0f);
                }
#endif
            }
            break;

        case AirScreamerStateStep_1:
            Ai_AirScreamer_DamageTake(airScreamer, Q12(0.0f));
            break;

        case AirScreamerStateStep_2:
            Ai_AirScreamer_DamageTake(airScreamer, Q12(0.5f));

            if (activeAnimStatus != animStatus12)
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;
    }

    #undef airScreamerProps
}