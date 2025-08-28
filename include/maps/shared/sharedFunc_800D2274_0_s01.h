s32 sharedFunc_800D2274_0_s01(s_SubCharacter* chara)
{
    s32 i;
    u32 flags;
    s_func_800D2E04* data;

    flags = chara->properties_E4.player.flags_11C;
    if (!(flags & (1<<16)))
    {
        if (flags & ((1<<3) | (1<<6)))
        {
            flags &= ~((1<<3) | (1<<6));
            if (chara->health_B0 <= 0)
            {
                flags |= (1<<6);
            } else
            {
                flags |= (1<<3);
            }
        }

        if (flags & (1<<28))
        {
            flags &= ~0x7C;
        } else if (flags & (1<<6))
        {
            flags &= ~0x3C;
            func_8004690C(g_sfxTable0[0].id);
        }

        data = &sharedData_800CAA98_0_s01;
        for (i = 0; i < 11; i++)
        {
            if (flags & (1 << i))
            {
                func_8005DC1C(data->sfx_CE8[i].id, &chara->position_18, data->sfx_CE8[i].volume, 0);
            }
        }
    }

    return 1;
}

