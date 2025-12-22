bool sharedFunc_800D2274_0_s01(s_SubCharacter* airScreamer)
{
    s32              i;
    u32              flags;
    s_func_800D2E04* data;

    flags = airScreamer->properties_E4.player.flags_11C;
    if (!(flags & (1 << 16)))
    {
        if (flags & ((1 << 3) | (1 << 6)))
        {
            flags &= ~(( 1 << 3) | (1 << 6));
            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                flags |= 1 << 6;
            }
            else
            {
                flags |= 1 << 3;
            }
        }

        if (flags & (1 << 28))
        {
            flags &= ~((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6));
        }
        else if (flags & (1 << 6))
        {
            flags &= ~((1 << 2) | (1 << 3) | (1 << 4) | (1 << 5));
            Sd_SfxStop(sharedData_800CAA98_0_s01.sfxVolumes_CE8[2].id_0);
        }

        // Run through flags.
        data = &sharedData_800CAA98_0_s01;
        for (i = 0; i < 11; i++)
        {
            if (flags & (1 << i))
            {
                func_8005DC1C(data->sfxVolumes_CE8[i].id_0, &airScreamer->position_18, data->sfxVolumes_CE8[i].volume_2, 0);
            }
        }
    }

    return true;
}

