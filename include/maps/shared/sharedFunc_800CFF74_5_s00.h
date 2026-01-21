void sharedFunc_800CFF74_5_s00(s_SubCharacter* scratcher)
{
    s_Collision coll;
    s32         prevMoveSpeed;
    s16         prevHeadingAngle;

    if (scratcher->damage_B4.amount_C > 0 && scratcher->health_B0 > 0)
    {
        scratcher->health_B0                = MAX(0, scratcher->health_B0 - scratcher->damage_B4.amount_C);
        scratcher->damage_B4.position_0.vx += (scratcher->moveSpeed_38 * Math_Sin(scratcher->headingAngle_3C)) >> 14; // TODO: Weird shift?
        scratcher->damage_B4.position_0.vz += (scratcher->moveSpeed_38 * Math_Cos(scratcher->headingAngle_3C)) >> 14;

        prevMoveSpeed              = scratcher->moveSpeed_38;
        scratcher->moveSpeed_38    = FP_TO(Math_Vector2MagCalc(scratcher->damage_B4.position_0.vx, scratcher->damage_B4.position_0.vz), Q12_SHIFT) / Q12(4.0f);
        prevHeadingAngle           = scratcher->headingAngle_3C;
        scratcher->headingAngle_3C = ratan2(scratcher->damage_B4.position_0.vx, scratcher->damage_B4.position_0.vz);

        switch (scratcher->model_0.controlState_2)
        {
            case 4:
                g_SysWork.field_2284[3] &= ~(1 << 1);

            case 1:
            case 2:
            case 3:
            case 9:
                Collision_Get(&coll, scratcher->position_18.vx, scratcher->position_18.vz);

                if (scratcher->health_B0 == Q12(0.0f) && coll.field_8 == 7)
                {
                    scratcher->health_B0 = 1;

                    if ((Rng_Rand16() & 0xF) < 0xC)
                    {
                        scratcher->moveSpeed_38    = prevMoveSpeed;
                        scratcher->headingAngle_3C = prevHeadingAngle;

                        scratcher->damage_B4.amount_C      = Q12(0.0f);
                        scratcher->damage_B4.position_0.vz = Q12(0.0f);
                        scratcher->damage_B4.position_0.vy = Q12(0.0f);
                        scratcher->damage_B4.position_0.vx = Q12(0.0f);
                        return;
                    }
                }

                if (ABS(scratcher->position_18.vx - g_SysWork.playerWork_4C.player_0.position_18.vx) > Q12(0.2f) &&
                    ABS(scratcher->position_18.vz - g_SysWork.playerWork_4C.player_0.position_18.vz) > Q12(0.2f))
                {
                    if (coll.field_8 != 7 && (Rng_Rand16() & 0xF) < 4)
                    {
                        scratcher->properties_E4.dummy.properties_E8[0].val16[0] |= (1 << 1);
                    }
                }

                scratcher->model_0.controlState_2  = 9;
                scratcher->model_0.anim_4.status_0 = ANIM_STATUS(8, false);
                break;

            case 15:
                g_SysWork.field_2284[3] &= ~(1 << 1);

            case 5:
            case 6:
            case 7:
            case 10:
                if (scratcher->health_B0 > Q12(100.0f))
                {
                    scratcher->model_0.controlState_2  = 10;
                    scratcher->model_0.anim_4.status_0 = ANIM_STATUS(9, false);
                }
                else
                {
                    scratcher->model_0.controlState_2  = 12;
                    scratcher->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                }

                break;

            case 11:
                if (scratcher->model_0.anim_4.status_0 == ANIM_STATUS(12, true))
                {
                    scratcher->model_0.anim_4.status_0 = ANIM_STATUS(21, false);
                }

            case 8:
                scratcher->field_34 += FP_TO(scratcher->damage_B4.position_0.vy, Q12_SHIFT) / Q12(4.0f);
                break;

            case 12:
                if (scratcher->model_0.anim_4.status_0 == ANIM_STATUS(13, true))
                {
                    scratcher->model_0.anim_4.status_0 = ANIM_STATUS(22, false);
                }
        }

        scratcher->properties_E4.dummy.properties_E8[0].val16[1]  = 0;
        scratcher->properties_E4.dummy.properties_E8[0].val16[0] |= (1 << 4);
    }

    scratcher->damage_B4.amount_C      = Q12(0.0f);
    scratcher->damage_B4.position_0.vz = Q12(0.0f);
    scratcher->damage_B4.position_0.vy = Q12(0.0f);
    scratcher->damage_B4.position_0.vx = Q12(0.0f);
}
