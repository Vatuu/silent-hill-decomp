void sharedFunc_800D7E04_0_s00(s_SubCharacter* stalker, s32 sfxId)
{
    s32 newSfxId;

    newSfxId = NO_VALUE;
    switch (sfxId)
    {
        case Sfx_Unk1365:
            if (stalker->properties_E4.stalker.field_10A < 3)
            {
                newSfxId                                 = sfxId;
                stalker->properties_E4.stalker.field_10A = 3;
                stalker->properties_E4.stalker.timer_108 = Rng_GenerateInt(Q12(0.0f), Q12(0.2f) - 1);
            }
            break;

        case Sfx_Unk1364:
            if (stalker->properties_E4.stalker.field_10A < 2)
            {
                newSfxId                                 = sfxId;
                stalker->properties_E4.stalker.field_10A = 2;
                stalker->properties_E4.stalker.timer_108 = Rng_GenerateInt(Q12(0.0f), Q12(0.3f) - 1);
            }
            break;

        case Sfx_Unk1363:
            if (stalker->properties_E4.stalker.field_10A < 2)
            {
                newSfxId                                 = sfxId;
                stalker->properties_E4.stalker.field_10A = 2;
                stalker->properties_E4.stalker.timer_108 = Rng_GenerateInt(Q12(0.0f), Q12(0.3f) - 1);
            }
            break;

        case Sfx_Unk1366:
            if (stalker->properties_E4.stalker.field_10A < 2)
            {
                newSfxId                                 = sfxId;
                stalker->properties_E4.stalker.field_10A = 2;
                stalker->properties_E4.stalker.timer_108 = Rng_GenerateInt(Q12(0.0f), Q12(0.3f) - 1);
            }
            break;
    }

    // TODO: `stalker->properties_E4.stalker.sfxId_102` doesn't match?
    if (newSfxId != NO_VALUE)
    {
        Sd_SfxStop(*((u16*)&stalker->properties_E4.player.field_100 + 1));
        *((u16*)&stalker->properties_E4.player.field_100 + 1) = newSfxId;
    }
}
