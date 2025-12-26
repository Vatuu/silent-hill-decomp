void sharedFunc_800D7EE8_1_s02(s_SubCharacter* creaper)
{
    if (creaper->damage_B4.amount_C > Q12(0.0f) && creaper->health_B0 > Q12(0.0f))
    {
        func_8005DC1C(Sfx_Unk1425, &creaper->position_18, Q8_CLAMPED(0.5f), 0);
        creaper->properties_E4.creaper.timer_104 = Q12(0.0f);

        // TODO: Weird position scaling?
        creaper->damage_B4.position_0.vx += (creaper->moveSpeed_38 * Math_Sin(creaper->headingAngle_3C)) >> 15;
        creaper->damage_B4.position_0.vz += (creaper->moveSpeed_38 * Math_Cos(creaper->headingAngle_3C)) >> 15;

        creaper->moveSpeed_38 = (SquareRoot0(SQUARE(Q12_TO_Q6(creaper->damage_B4.position_0.vx)) +
                                             SQUARE(Q12_TO_Q6(creaper->damage_B4.position_0.vz))) << 18) /
                                Q12(0.8f);

        creaper->field_34        = FP_TO(creaper->damage_B4.position_0.vy, Q12_SHIFT) / Q12(0.8f);
        creaper->headingAngle_3C = Rng_AddGeneratedUInt(ratan2(creaper->damage_B4.position_0.vx, creaper->damage_B4.position_0.vz), -128, 127);

        creaper->properties_E4.creaper.flags_E8 |= CreaperFlag_1;

        if (ANIM_STATUS_IDX_GET(creaper->model_0.anim_4.status_0) == CreaperAnim_7)
        {
            creaper->health_B0 = Q12(0.0f);

            creaper->properties_E4.creaper.animStatus_10A = ANIM_STATUS(CreaperAnim_16, true);
            if (creaper->model_0.anim_4.status_0 == ANIM_STATUS(CreaperAnim_7, true))
            {
                creaper->model_0.anim_4.status_0 = ANIM_STATUS(CreaperAnim_16, true);
            }
            else
            {
                creaper->model_0.anim_4.status_0 = ANIM_STATUS(CreaperAnim_16, false);
            }
        }
        else if (ANIM_STATUS_IDX_GET(creaper->model_0.anim_4.status_0) == CreaperAnim_8)
        {
            creaper->health_B0 = Q12(0.0f);

            creaper->properties_E4.creaper.animStatus_10A = ANIM_STATUS(CreaperAnim_17, true);
            if (creaper->model_0.anim_4.status_0 == ANIM_STATUS(CreaperAnim_8, true))
            {
                creaper->model_0.anim_4.status_0 = ANIM_STATUS(CreaperAnim_17, true);
            }
            else
            {
                creaper->model_0.anim_4.status_0 = ANIM_STATUS(CreaperAnim_17, false);
            }
        }
        else if (ANIM_STATUS_IDX_GET(creaper->model_0.anim_4.status_0) == CreaperAnim_9)
        {
            creaper->health_B0               = Q12(0.0f);
            creaper->model_0.anim_4.status_0 = ANIM_STATUS(CreaperAnim_3, false);
            creaper->model_0.state_2         = 5;
        }
        else if (ANIM_STATUS_IDX_GET(creaper->model_0.anim_4.status_0) == 10)
        {
            creaper->health_B0               = Q12(0.0f);
            creaper->model_0.anim_4.status_0 = ANIM_STATUS(CreaperAnim_4, false);
            creaper->model_0.state_2         = 5;
        }
        else
        {
            if (creaper->model_0.state_2 == 3)
            {
                g_SysWork.field_2284[3] &= ~(1 << 1);
            }

            creaper->model_0.state_2 = 4;
            creaper->health_B0       = Q12(20.0f);
            creaper->flags_3E       |= CharaFlag_Unk2;

            if (ABS(func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - creaper->position_18.vx,
                                         g_SysWork.playerWork_4C.player_0.position_18.vz - creaper->position_18.vz) - creaper->rotation_24.vy)) < FP_ANGLE(60.0f))
            {
                creaper->model_0.anim_4.status_0 = ANIM_STATUS(CreaperAnim_7, false);
            }
            else
            {
                creaper->model_0.anim_4.status_0 = ANIM_STATUS(CreaperAnim_8, false);
            }
        }
    }

    if (creaper->damage_B4.amount_C < Q12(200.0f) || creaper->health_B0 <= Q12(0.0f))
    {
        creaper->damage_B4.amount_C      = Q12(0.0f);
        creaper->damage_B4.position_0.vz = Q12(0.0f);
        creaper->damage_B4.position_0.vy = Q12(0.0f);
        creaper->damage_B4.position_0.vx = Q12(0.0f);
    }
}
