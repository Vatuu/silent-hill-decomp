void sharedFunc_800D7EE8_1_s02(s_SubCharacter* creeper)
{
    #define creeperProps creeper->properties_E4.creeper

    if (creeper->damage_B4.amount_C > Q12(0.0f) && creeper->health_B0 > Q12(0.0f))
    {
        func_8005DC1C(Sfx_Unk1425, &creeper->position_18, Q8_CLAMPED(0.5f), 0);
        creeperProps.timer_104 = Q12(0.0f);

        // TODO: Weird position scaling?
        creeper->damage_B4.position_0.vx += (creeper->moveSpeed_38 * Math_Sin(creeper->headingAngle_3C)) >> 15;
        creeper->damage_B4.position_0.vz += (creeper->moveSpeed_38 * Math_Cos(creeper->headingAngle_3C)) >> 15;

        creeper->moveSpeed_38 = (SquareRoot0(SQUARE(Q12_TO_Q6(creeper->damage_B4.position_0.vx)) +
                                             SQUARE(Q12_TO_Q6(creeper->damage_B4.position_0.vz))) << 18) /
                                Q12(0.8f);

        creeper->field_34        = FP_TO(creeper->damage_B4.position_0.vy, Q12_SHIFT) / Q12(0.8f);
        creeper->headingAngle_3C = Rng_AddGeneratedUInt(ratan2(creeper->damage_B4.position_0.vx, creeper->damage_B4.position_0.vz), -128, 127);

        creeperProps.flags_E8 |= CreeperFlag_1;

        if (ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_7)
        {
            creeper->health_B0 = Q12(0.0f);

            creeperProps.animStatus_10A = ANIM_STATUS(CreeperAnim_16, true);
            if (creeper->model_0.anim_4.status_0 == ANIM_STATUS(CreeperAnim_7, true))
            {
                creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_16, true);
            }
            else
            {
                creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_16, false);
            }
        }
        else if (ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_8)
        {
            creeper->health_B0 = Q12(0.0f);

            creeperProps.animStatus_10A = ANIM_STATUS(CreeperAnim_17, true);
            if (creeper->model_0.anim_4.status_0 == ANIM_STATUS(CreeperAnim_8, true))
            {
                creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_17, true);
            }
            else
            {
                creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_17, false);
            }
        }
        else if (ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_9)
        {
            creeper->health_B0               = Q12(0.0f);
            creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_3, false);
            creeper->model_0.state_2         = CreeperControl_5;
        }
        else if (ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == 10)
        {
            creeper->health_B0               = Q12(0.0f);
            creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_4, false);
            creeper->model_0.state_2         = CreeperControl_5;
        }
        else
        {
            if (creeper->model_0.state_2 == CreeperControl_3)
            {
                g_SysWork.field_2284[3] &= ~(1 << 1);
            }

            creeper->model_0.state_2 = CreeperControl_4;
            creeper->health_B0       = Q12(20.0f);
            creeper->flags_3E       |= CharaFlag_Unk2;

            if (ABS(func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - creeper->position_18.vx,
                                         g_SysWork.playerWork_4C.player_0.position_18.vz - creeper->position_18.vz) - creeper->rotation_24.vy)) < FP_ANGLE(60.0f))
            {
                creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_7, false);
            }
            else
            {
                creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_8, false);
            }
        }
    }

    if (creeper->damage_B4.amount_C < Q12(200.0f) || creeper->health_B0 <= Q12(0.0f))
    {
        creeper->damage_B4.amount_C      = Q12(0.0f);
        creeper->damage_B4.position_0.vz = Q12(0.0f);
        creeper->damage_B4.position_0.vy = Q12(0.0f);
        creeper->damage_B4.position_0.vx = Q12(0.0f);
    }

    #undef creeperProps
}
