void sharedFunc_800D8684_1_s02(s_SubCharacter* creaper)
{
    s16           temp_s4;
    s16           temp_v0_5;
    s32           temp_s2;
    s32           temp;
    s_PlayerWork* ptr;

    temp_s4 = func_8005BF38((ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - creaper->position_18.vx,
                                    g_SysWork.playerWork_4C.player_0.position_18.vz - creaper->position_18.vz) -
                             creaper->rotation_24.vy));

    if (((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 3) == 2 && func_8006FD90(creaper, 0, 0xC000, 0x8000)) ||
        ((g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 2) &&
         (g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 1) && func_8006FD90(creaper, 2, 0xCCC, 0x666)) ||
        (!(g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 3) && func_8006FD90(creaper, 1, 0x4000, 0xC000)) ||
        (func_80070360(creaper, 0, 0x800) || (u16)creaper->properties_E4.dummy.properties_E8[0].val16[0] & 0x100))
    {
        creaper->properties_E4.npc.field_F4                     = g_SysWork.playerWork_4C.player_0.position_18.vx;
        creaper->properties_E4.npc.field_F8                     = g_SysWork.playerWork_4C.player_0.position_18.vz;
        creaper->properties_E4.dummy.properties_E8[0].val16[0] &= 0xFFDF;
    }

    temp_s2 = SquareRoot0(SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vx - creaper->position_18.vx) >> 6) +
                          SQUARE((g_SysWork.playerWork_4C.player_0.position_18.vz - creaper->position_18.vz) >> 6))
              << 6;

    temp = SquareRoot0(SQUARE((creaper->properties_E4.player.field_F4 - creaper->position_18.vx) >> 6) +
                       SQUARE((creaper->properties_E4.player.runTimer_F8 - creaper->position_18.vz) >> 6))
           << 6;

    if (temp < 0x1333 && !(creaper->properties_E4.dummy.properties_E8[0].val16[0] & 1) &&
        !func_800700F8(creaper, &g_SysWork.playerWork_4C.player_0))
    {
        ptr = &g_SysWork.playerWork_4C;

        if (temp_s2 > 0x1333)
        {
            if ((creaper->properties_E4.player.afkTimer_E8 & 0x30) == 0x10)
            {
                creaper->properties_E4.dummy.properties_E8[0].val16[0] |= 0x20;
                creaper->properties_E4.player.field_F4                  = creaper->properties_E4.player.exhaustionTimer_FC;
                creaper->properties_E4.player.runTimer_F8               = creaper->properties_E4.player.field_100;
            }
            else
            {
                creaper->model_0.state_2               = 1;
                creaper->model_0.anim_4.status_0       = 0x16;
                creaper->properties_E4.player.field_F0 = 0;
            }
        }
        else if (!(g_SysWork.field_2284[3] & 2) && !(ptr->player_0.flags_3E & 8) &&
                 temp_s2 < 0x800 && ABS(temp_s4) < 0x71 && g_SysWork.playerWork_4C.player_0.health_B0 > 0)
        {
            creaper->model_0.state_2               = 3;
            creaper->model_0.anim_4.status_0       = 0x18;
            creaper->properties_E4.player.field_F0 = 0;
            g_SysWork.field_2284[3]               |= 2;
        }
        else
        {
            if (ABS(temp_s4) >= 0x400)
            {
                Chara_MoveSpeedUpdate(creaper, 0x4000);
            }
            else
            {
                Chara_MoveSpeedUpdate3(creaper, 0x1800, ((u16)creaper->properties_E4.dummy.properties_E8[9].val16[0] * (0x400 - ABS(temp_s4))) >> 0xA);
            }

            if (((g_DeltaTime0 >> 2) + 1) < ABS(temp_s4) && Rng_GenerateInt(0, 7))
            {
                if (temp_s4 > 0)
                {
                    creaper->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x800, Q12_SHIFT);
                }
                else
                {
                    creaper->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x800, Q12_SHIFT);
                }
            }
        }
    }
    else
    {
        Chara_MoveSpeedUpdate4(creaper, 0x1800, (u16)creaper->properties_E4.dummy.properties_E8[9].val16[0]);

        creaper->properties_E4.player.field_F0 += g_DeltaTime0;

        if ((ABS(temp_s4) >= 0x72 && func_80070184(creaper, 0x1000, creaper->properties_E4.dummy.properties_E8[8].val16[0])) ||
            (!Rng_GenerateInt(0, 7) &&
             ((!((u16)creaper->properties_E4.dummy.properties_E8[0].val16[0] & 1) && creaper->properties_E4.player.field_F0 > 0x800) ||
              (((u16)creaper->properties_E4.dummy.properties_E8[0].val16[0] & 1) && creaper->properties_E4.player.field_F0 > 0x2000))))
        {
            if (creaper->properties_E4.player.field_F0 > 0x2000)
            {
                creaper->properties_E4.dummy.properties_E8[0].val16[0] &= 0xFFFE;
            }

            creaper->properties_E4.dummy.properties_E8[8].val16[0] = func_8006FAFC(creaper, 0x1333, creaper->properties_E4.player.field_F4, creaper->properties_E4.player.runTimer_F8, 0x1000, true);

            if (creaper->properties_E4.dummy.properties_E8[8].val16[0] == 0x1000)
            {
                creaper->properties_E4.dummy.properties_E8[8].val16[0] = creaper->rotation_24.vy;
            }
            else
            {
                creaper->properties_E4.player.field_F0 = 0;
            }
        }

        temp_v0_5 = func_8005BF38(creaper->properties_E4.dummy.properties_E8[8].val16[0] - creaper->rotation_24.vy);

        if ((g_DeltaTime0 >> 2) + 1 < ABS(temp_v0_5))
        {
            if (temp_v0_5 > 0)
            {
                creaper->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x800, Q12_SHIFT);
            }
            else
            {
                creaper->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x800, Q12_SHIFT);
            }
        }
    }
}