bool sharedFunc_800D2274_0_s01(s_SubCharacter* airScreamer)
{
    s32              i;
    u32              flags;
    s_func_800D2E04* data;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    flags = airScreamerProps.flags_11C;

    if (!(flags & AirScreamerFlag_16))
    {
        if (flags & (AirScreamerFlag_3 | AirScreamerFlag_6))
        {
            flags &= ~(AirScreamerFlag_3 | AirScreamerFlag_6);
            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                flags |= AirScreamerFlag_6;
            }
            else
            {
                flags |= AirScreamerFlag_3;
            }
        }

        if (flags & AirScreamerFlag_28)
        {
            flags &= ~(AirScreamerFlag_2 | AirScreamerFlag_3 | AirScreamerFlag_4 | AirScreamerFlag_5 | AirScreamerFlag_6);
        }
        else if (flags & AirScreamerFlag_6)
        {
            flags &= ~(AirScreamerFlag_2 | AirScreamerFlag_3 | AirScreamerFlag_4 | AirScreamerFlag_5);
            Sd_SfxStop(sharedData_800CAA98_0_s01.sfxVolumes_CE8[2].id_0);
        }

        // Run through flags defining which SFX to play.
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

    #undef airScreamerProps
}
