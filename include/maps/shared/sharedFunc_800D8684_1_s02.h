void sharedFunc_800D8684_1_s02(s_SubCharacter* creaper)
{
    q3_12         angle0;
    q3_12         angle1;
    s32           temp_s2;
    s32           temp;
    s_PlayerWork* ptr;

    angle1 = func_8005BF38((ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - creaper->position_18.vx,
                                    g_SysWork.playerWork_4C.player_0.position_18.vz - creaper->position_18.vz) -
                             creaper->rotation_24.vy));

    if (((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) == 2 && func_8006FD90(creaper, 0, Q12(12.0f), Q12(8.0f))) ||
        ((g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 0x2) &&
         (g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 0x1) && func_8006FD90(creaper, 2, Q12(0.8f), Q12(0.4f))) ||
        (!(g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) && func_8006FD90(creaper, 1, Q12(4.0f), Q12(12.0f))) ||
        (func_80070360(creaper, 0, Q12(0.5f)) || (u16)creaper->properties_E4.creaper.flags_E8 & (1 << 8)))
    {
        creaper->properties_E4.npc.field_F4                     = g_SysWork.playerWork_4C.player_0.position_18.vx;
        creaper->properties_E4.npc.field_F8                     = g_SysWork.playerWork_4C.player_0.position_18.vz;
        creaper->properties_E4.creaper.flags_E8 &= ~(1 << 5);
    }

    temp_s2 = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - creaper->position_18.vx,
                                  g_SysWork.playerWork_4C.player_0.position_18.vz - creaper->position_18.vz);
    temp    = Math_Vector2MagCalc(creaper->properties_E4.player.field_F4 - creaper->position_18.vx,
                                  creaper->properties_E4.player.runTimer_F8 - creaper->position_18.vz);

    if (temp < Q12(1.2f) && !(creaper->properties_E4.creaper.flags_E8 & (1 << 0)) &&
        !func_800700F8(creaper, &g_SysWork.playerWork_4C.player_0))
    {
        ptr = &g_SysWork.playerWork_4C;

        if (temp_s2 > Q12(1.2f))
        {
            if ((creaper->properties_E4.player.afkTimer_E8 & 0x30) == 0x10)
            {
                creaper->properties_E4.creaper.flags_E8  |= 1 << 5;
                creaper->properties_E4.player.field_F4    = creaper->properties_E4.player.exhaustionTimer_FC;
                creaper->properties_E4.player.runTimer_F8 = creaper->properties_E4.player.field_100;
            }
            else
            {
                creaper->model_0.state_2               = 1;
                creaper->model_0.anim_4.status_0       = ANIM_STATUS(CreaperAnim_11, false);
                creaper->properties_E4.player.field_F0 = 0;
            }
        }
        else if (!(g_SysWork.field_2284[3] & 2) && !(ptr->player_0.flags_3E & 8) &&
                 temp_s2 < Q12(0.5f) && ABS(angle1) < FP_ANGLE(10.0f) && g_SysWork.playerWork_4C.player_0.health_B0 > 0)
        {
            creaper->model_0.state_2               = 3;
            creaper->model_0.anim_4.status_0       = ANIM_STATUS(CreaperAnim_12, false);
            creaper->properties_E4.player.field_F0 = 0;
            g_SysWork.field_2284[3]               |= 1 << 1;
        }
        else
        {
            if (ABS(angle1) >= FP_ANGLE(90.0f))
            {
                Chara_MoveSpeedUpdate(creaper, Q12(4.0f));
            }
            else
            {
                Chara_MoveSpeedUpdate3(creaper, Q12(1.5f), ((u16)creaper->properties_E4.dummy.properties_E8[9].val16[0] * (FP_ANGLE(90.0f) - ABS(angle1))) >> 10);
            }

            if (((g_DeltaTime0 >> 2) + 1) < ABS(angle1) && Rng_GenerateInt(0, 7)) // 1 in 8 chance.
            {
                if (angle1 > FP_ANGLE(0.0f))
                {
                    creaper->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
                }
                else
                {
                    creaper->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
                }
            }
        }
    }
    else
    {
        Chara_MoveSpeedUpdate4(creaper, Q12(1.5f), (u16)creaper->properties_E4.dummy.properties_E8[9].val16[0]);

        creaper->properties_E4.player.field_F0 += g_DeltaTime0;

        if ((ABS(angle1) > FP_ANGLE(10.0f) && func_80070184(creaper, Q12(1.0f), creaper->properties_E4.dummy.properties_E8[8].val16[0])) ||
            (!Rng_GenerateInt(0, 7) && // 1 in 8 chance.
             ((!((u16)creaper->properties_E4.creaper.flags_E8 & (1 << 0)) && creaper->properties_E4.player.field_F0 > Q12(0.5f)) ||
              ( ((u16)creaper->properties_E4.creaper.flags_E8 & (1 << 0)) && creaper->properties_E4.player.field_F0 > Q12(2.0f)))))
        {
            if (creaper->properties_E4.player.field_F0 > Q12(2.0f))
            {
                creaper->properties_E4.creaper.flags_E8 &= 0xFFFE;
            }

            creaper->properties_E4.dummy.properties_E8[8].val16[0] = func_8006FAFC(creaper, Q12(1.2f), creaper->properties_E4.player.field_F4, creaper->properties_E4.player.runTimer_F8, Q12(1.0f), true);

            if (creaper->properties_E4.dummy.properties_E8[8].val16[0] == 0x1000)
            {
                creaper->properties_E4.dummy.properties_E8[8].val16[0] = creaper->rotation_24.vy;
            }
            else
            {
                creaper->properties_E4.player.field_F0 = 0;
            }
        }

        angle0 = func_8005BF38(creaper->properties_E4.dummy.properties_E8[8].val16[0] - creaper->rotation_24.vy);
        if (((g_DeltaTime0 >> 2) + 1) < ABS(angle0))
        {
            if (angle0 > FP_ANGLE(0.0f))
            {
                creaper->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
            }
            else
            {
                creaper->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
            }
        }
    }
}
