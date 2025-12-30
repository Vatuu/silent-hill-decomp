void sharedFunc_800D2D74_1_s05(s_SubCharacter* splitHead)
{
    VECTOR3 sp20[4];
    VECTOR3 sp50[4];
    s32     sp80[4];
    s16     sp90[4];
    s16     sp98[3];
    q19_12  deltaX;
    q19_12  deltaZ;
    s32     dist;
    s32     i;
    s32     unkIdx;
    s32     dx_offset;
    s32     dz_offset;

    #define splitHeadProps splitHead->properties_E4.splitHead

    sharedFunc_800D4408_1_s05(&sp20[0], 2, 0, -0x45, 0xFB);
    sharedFunc_800D4408_1_s05(&sp50[0], 2, 0, 0xED, 0xA6);
    sharedFunc_800D4408_1_s05(&sp20[1], 0x13, -0x24, 5, 0x71);
    sharedFunc_800D4408_1_s05(&sp20[2], 0x17, 0x24, 5, 0x71);

    deltaX = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vx - splitHead->position_18.vx);
    deltaZ = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vz - splitHead->position_18.vz);
    dist   = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    sp98[0] = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - sp20[0].vx, g_SysWork.playerWork_4C.player_0.position_18.vz - sp20[0].vz);
    sp98[1] = func_8005BF38((ratan2(sp20[1].vx - sp20[0].vx, sp20[1].vz - sp20[0].vz) - sp98[0]));
    sp98[2] = func_8005BF38((ratan2(sp20[2].vx - sp20[0].vx, sp20[2].vz - sp20[0].vz) - sp98[0]));

    if (sp98[1] < 0x400 && sp98[2] > -0x400)
    {
        if ((sp98[1] >= 0 && sp98[2] <= 0) || (dist > 0x2C00 && sp98[1] >= -0x40 && sp98[2] <= 0x40))
        {
            if (ABS(sp98[1] - sp98[2]) >= 0x72)
            {
                splitHeadProps.flags_E8 |= 1;
                splitHead->field_C8.field_0                  = sp20[0].vy;
                splitHead->field_C8.field_4                  = sp50[0].vy;
                splitHead->field_D4.field_2                  = 0x999;

                dx_offset = (sp20[0].vx - splitHead->position_18.vx) * 3;

                if (dx_offset < 0)
                {
                    dx_offset += 3;
                }
                splitHead->field_D8.offsetX_0 = (dx_offset >> 2);

                dz_offset = (sp20[0].vz - splitHead->position_18.vz) * 3;

                if (dz_offset < 0)
                {
                    dz_offset += 3;
                }

                splitHead->field_D8.offsetZ_2 = dz_offset >> 2;
                return;
            }
        }
    }

    if (dist > Q12(2.75f))
    {
        splitHeadProps.flags_E8 &= ~(1 << 0);
    }

    sharedFunc_800D4408_1_s05(&sp20[3], 1, 0, -0x46, -0xB7);

    unkIdx = 1;

    sp80[0] = func_8005C478(&sp90[0], g_SysWork.playerWork_4C.player_0.position_18.vx,
                            g_SysWork.playerWork_4C.player_0.position_18.vz, sp20[0].vx, sp20[0].vz,
                            (sp20[1].vx + sp20[2].vx) >> 1, (sp20[1].vz + sp20[2].vz) >> 1);

    for (i = 1; i < 4; i++)
    {
        sp80[i] = func_8005C478(&sp90[i], g_SysWork.playerWork_4C.player_0.position_18.vx,
                                g_SysWork.playerWork_4C.player_0.position_18.vz, sp20[0].vx, sp20[0].vz, sp20[i].vx, sp20[i].vz);

        if (sp80[i] < sp80[unkIdx])
        {
            unkIdx = i;
        }
    }

    if (unkIdx < 3)
    {
        if (sp90[0] > 0xD99)
        {
            sp90[unkIdx] = 0xD99;
        }
        else
        {
            sp90[unkIdx] = sp90[0];
        }

        if (unkIdx == 1)
        {
            sharedFunc_800D4408_1_s05(&sp50[1], 0x13, -0x24, 0x88, 0x16);
        }
        else
        {
            sharedFunc_800D4408_1_s05(&sp50[2], 0x17, 0x24, 0x88, 0x16);
        }
    }
    else
    {
        if (sp90[3] > 0xE66)
        {
            sp90[3] = 0xE66;
        }
        sharedFunc_800D4408_1_s05(&sp50[3], 1, 0, 0x95, -0x13F);
    }

    splitHead->field_C8.field_0 = FP_FROM(sp20[0].vy * (Q12(1.0f) - sp90[unkIdx]) + sp20[unkIdx].vy * sp90[unkIdx], Q12_SHIFT);
    splitHead->field_C8.field_4 = FP_FROM(sp50[0].vy * (Q12(1.0f) - sp90[unkIdx]) + sp20[unkIdx + 4].vy * sp90[unkIdx], Q12_SHIFT);
    splitHead->field_C8.field_6 = (splitHead->field_C8.field_0 + splitHead->field_C8.field_4) >> 1;

    if (unkIdx == 3)
    {
        splitHead->field_D4.field_2 = 0x999;
    }
    else
    {
        splitHead->field_D4.field_2 = FP_FROM((Q12(1.0f) - sp90[unkIdx]) * 0x999 + sp90[unkIdx] * 0x599, Q12_SHIFT);
    }

    splitHead->field_D8.offsetX_0 = FP_FROM(sp20[0].vx * (Q12(1.0f) - sp90[unkIdx]) + sp20[unkIdx].vx * sp90[unkIdx], Q12_SHIFT) - splitHead->position_18.vx;
    splitHead->field_D8.offsetZ_2 = FP_FROM(sp20[0].vz * (Q12(1.0f) - sp90[unkIdx]) + sp20[unkIdx].vz * sp90[unkIdx], Q12_SHIFT) - splitHead->position_18.vz;

    #undef splitHeadProps
}
