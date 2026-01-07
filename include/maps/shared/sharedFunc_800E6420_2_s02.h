void sharedFunc_800E6420_2_s02(s_SubCharacter* romper)
{
    s_Collision coll;
    s32         keyframeIdx;
    q19_12      unkHealth;
    s32         prevControlState;

    #define romperProps romper->properties_E4.romper    

    if (romper->health_B0 > Q12(0.0f))
    {
        Collision_Get(&coll, romper->position_18.vx, romper->position_18.vz);

        if (coll.field_8 == 12)
        {
            if (Rng_GenerateInt(Q12(4.0f), Q12(8.0f) - 1) < romper->position_18.vy)
            {
                romper->damage_B4.amount_C = Q12(3000.0f);
            }
        }
    }

    if (romper->damage_B4.amount_C == Q12(0.0f) || romper->health_B0 <= Q12(0.0f))
    {
        romper->damage_B4.amount_C      = Q12(0.0f);
        romper->damage_B4.position_0.vz = Q12(0.0f);
        romper->damage_B4.position_0.vy = Q12(0.0f);
        romper->damage_B4.position_0.vx = Q12(0.0f);
        return;
    }

    prevControlState = romper->model_0.controlState_2;

    romper->health_B0 = MAX(romper->health_B0 - romper->damage_B4.amount_C, Q12(0.0f));
    romperProps.field_E8 |= RomperFlag_7;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        unkHealth = Q12(400.0f);
    }
    else
    {
        unkHealth = Q12(200.0f);
    }

    if (unkHealth < romper->health_B0)
    {
        romperProps.positionX_FC = g_SysWork.playerWork_4C.player_0.position_18.vx;

        romperProps.positionZ_100 = g_SysWork.playerWork_4C.player_0.position_18.vz;
        romperProps.field_10E     = 0;

        romperProps.rotationY_F2 = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                          g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz);

        switch (romper->model_0.anim_4.status_0)
        {
            case ANIM_STATUS(RomperAnim_13, false):
                romper->model_0.anim_4.time_4 = Q12(109.0f);

            case ANIM_STATUS(RomperAnim_13, true):
                keyframeIdx = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 109;
                if (keyframeIdx > 0)
                {
                    if (keyframeIdx < 7)
                    {
                        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_18, true);
                    }
                    else if (keyframeIdx < 11)
                    {
                        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_8, false);
                    }
                    else if (keyframeIdx > 17)
                    {
                        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_7, false);
                    }
                    else
                    {
                        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_17, true);
                    }
                }
                else
                {
                    romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_7, false);
                }

                if (!ANIM_STATUS_IS_ACTIVE(romper->model_0.anim_4.status_0))
                {
                    romper->model_0.controlState_2 = 6;
                }
                break;

            case ANIM_STATUS(RomperAnim_15, false):
                romper->model_0.anim_4.time_4 = Q12(147.0f);

            case ANIM_STATUS(RomperAnim_15, true):
                keyframeIdx = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 147;
                if (keyframeIdx < 2)
                {
                    romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_7, false);
                }
                else if (keyframeIdx >= 10)
                {
                    romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_7, false);
                }
                else
                {
                    romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_8, false);
                }

                romper->model_0.controlState_2 = RomperControl_6;
                break;

            case ANIM_STATUS(RomperAnim_12, false):
            case ANIM_STATUS(RomperAnim_12, true):
            case ANIM_STATUS(RomperAnim_14, false):
            case ANIM_STATUS(RomperAnim_14, true):
                romper->model_0.controlState_2  = RomperControl_6;
                romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_7, false);
                break;
        }
    }
    else if (!(romperProps.field_E8 & RomperFlag_2))
    {
        romper->model_0.controlState_2         = RomperControl_7;
        romper->model_0.anim_4.status_0        = ANIM_STATUS(RomperAnim_11, false);
        romperProps.field_E8 |= RomperFlag_2;
    }

    romperProps.field_10E    = 0;
    romperProps.rotationY_F2 = FP_ANGLE(360.0f);
    romper->damage_B4.amount_C                = Q12(0.0f);
    romper->damage_B4.position_0.vz           = Q12(0.0f);
    romper->damage_B4.position_0.vy           = Q12(0.0f);
    romper->damage_B4.position_0.vx           = Q12(0.0f);

    if (prevControlState != romper->model_0.controlState_2)
    {
        if (romperProps.field_E8 & RomperFlag_11)
        {
            romperProps.field_E8 &= ~RomperFlag_11;
            g_SysWork.field_2284[3] &= 0xFFFC;
        }
    }

    #undef romperProps
}
