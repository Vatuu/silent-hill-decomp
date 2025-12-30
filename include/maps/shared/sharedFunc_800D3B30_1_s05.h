void sharedFunc_800D3B30_1_s05(s_SubCharacter* splitHead)
{
    s_sharedFunc_800D4594_1_s05 sp18;
    s_sharedFunc_800D4594_1_s05 sp28;
    VECTOR3                     sp38;
    s32                         sp48;
    s32                         sp4C;
    s32                         temp_v0;
    s32                         deltaX;
    s32                         deltaZ;
    s32                         var_v1;
    s16                         var_v1_3;

    splitHead->field_C8.field_2   = 0;
    splitHead->field_D4.field_0   = 0;
    splitHead->field_D8.offsetX_4 = 0;
    splitHead->field_D8.offsetZ_6 = 0;
    splitHead->field_E0          &= ~0xF00;
    splitHead->field_E0          |= 0x400;

    sharedFunc_800D4408_1_s05(&D_800D8618[0], 0x11, D_800D5A90[0].vx, D_800D5A90[0].vy, D_800D5A90[0].vz);
    sharedFunc_800D4408_1_s05(&D_800D8618[1], 0x15, (s16)((u16)D_800D5A90[0].vx * -1), D_800D5A90[0].vy, D_800D5A90[0].vz);
    D_800D8618[0].vx = ((D_800D8618[0].vx + D_800D8618[1].vx) >> 1);
    D_800D8618[0].vy = ((D_800D8618[0].vy + D_800D8618[1].vy) >> 1);
    D_800D8618[0].vz = ((D_800D8618[0].vz + D_800D8618[1].vz) >> 1);
    sharedFunc_800D4408_1_s05(&D_800D8618[1], 0x13, D_800D5A90[2].vx, D_800D5A90[2].vy, D_800D5A90[2].vz);
    sharedFunc_800D4408_1_s05(&D_800D8618[2], 0x13, D_800D5A90[3].vx, D_800D5A90[3].vy, D_800D5A90[3].vz);
    sharedFunc_800D4408_1_s05(&D_800D8618[3], 2, (s16)((u16)D_800D5A90[1].vx * -1), D_800D5A90[1].vy, D_800D5A90[1].vz);
    sharedFunc_800D4408_1_s05(&D_800D8618[4], 3, D_800D5A90[4].vx, D_800D5A90[4].vy, D_800D5A90[4].vz);
    sharedFunc_800D4408_1_s05(&D_800D8618[5], 7, (s16)((u16)D_800D5A90[4].vx * -1), D_800D5A90[4].vy, D_800D5A90[4].vz);
    sharedFunc_800D4408_1_s05(&D_800D8618[6], 2, D_800D5A90[1].vx, D_800D5A90[1].vy, D_800D5A90[1].vz);
    sharedFunc_800D4408_1_s05(&D_800D8618[7], 0x17, (s16)((u16)D_800D5A90[3].vx * -1), D_800D5A90[3].vy, D_800D5A90[3].vz);
    sharedFunc_800D4408_1_s05(&D_800D8618[8], 0x17, (s16)((u16)D_800D5A90[2].vx * -1), D_800D5A90[2].vy, D_800D5A90[2].vz);

    if (!(splitHead->properties_E4.splitHead.flags_E8 & 1))
    {
        D_800D5AAE       = 2;
        D_800D8618[8].vx = ((D_800D8618[8].vx + D_800D8618[1].vx) >> 1);
        D_800D8618[8].vy = ((D_800D8618[8].vy + D_800D8618[1].vy) >> 1);
        D_800D8618[8].vz = ((D_800D8618[8].vz + D_800D8618[1].vz) >> 1);
    }
    else
    {
        D_800D5AAE = 0;
    }

    D_800D5AAF = 0;
    sp48       = sharedData_800D8684_1_s05;
    sp4C       = sharedData_800D8688_1_s05;
    sharedFunc_800D3388_1_s05(splitHead, &sp48, &sp4C);

    if (D_800D5AAF != 0)
    {
        sp38.vx = 0;
        sp38.vy = 0;
        sp38.vz = 0;
    }
    else
    {
        temp_v0 = ABS(sp48) - 0x20;
        var_v1  = temp_v0 < 0 ? 0 : temp_v0 >> 4;
        sp38.vx = sp48 <= 0 ? var_v1 * -var_v1 : SQUARE(var_v1);

        sp38.vy = 0;

        temp_v0 = ABS(sp4C) - 0x20;
        var_v1  = temp_v0 < 0 ? 0 : temp_v0 >> 4;
        sp38.vz = sp4C <= 0 ? var_v1 * -var_v1 : SQUARE(var_v1);
    }
    sharedFunc_800D2E8C_0_s00(sp48 + sharedData_800D8684_1_s05, sp4C + sharedData_800D8688_1_s05, &sp38);

    if (splitHead->properties_E4.splitHead.flags_E8 & 1)
    {
        deltaX = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vx - splitHead->position_18.vx);
        deltaZ = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vz - splitHead->position_18.vz);

        if (Q6_TO_Q12((SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)))) < Q12(3.3f))
        {
            sharedFunc_800D4594_1_s05(&sp18, g_SysWork.playerWork_4C.player_0.position_18.vx,
                                      g_SysWork.playerWork_4C.player_0.position_18.vz, &D_800D8618[0], &D_800D8618[1]);
            sharedFunc_800D4594_1_s05(&sp28, g_SysWork.playerWork_4C.player_0.position_18.vx,
                                      g_SysWork.playerWork_4C.player_0.position_18.vz, &D_800D8618[0], &D_800D8618[8]);

            if (splitHead->model_0.anim_4.time_4 < Q12(31.0f))
            {
                var_v1_3 = 0;
            }
            else if (splitHead->model_0.anim_4.time_4 < Q12(33.0f))
            {
                var_v1_3 = FP_MULTIPLY_PRECISE(g_SysWork.playerWork_4C.player_0.field_D4.field_0, splitHead->model_0.anim_4.time_4 + Q12(-31.0f), Q12_SHIFT) >> 1;
            }
            else
            {
                var_v1_3 = 0;
                if (splitHead->model_0.anim_4.time_4 < Q12(37.0f))
                {
                    var_v1_3 = g_SysWork.playerWork_4C.player_0.field_D4.field_0;
                }
            }

            if ((sp18.field_0 < var_v1_3) &&
                (sp28.field_0 < var_v1_3) &&
                !(splitHead->properties_E4.splitHead.flags_E8 & 0x200))
            {
                (&g_SysWork.playerWork_4C)->player_0.attackReceived_41 = 0x2F;
                splitHead->properties_E4.splitHead.flags_E8           |= 0x202;
                func_8005DC1C(0x5C1, &g_SysWork.playerWork_4C.player_0.position_18, Q8(0.999f), 2);
            }
        }
    }
}