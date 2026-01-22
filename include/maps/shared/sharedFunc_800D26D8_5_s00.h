void sharedFunc_800D26D8_5_s00(s_SubCharacter* scratcher)
{
    s_800C4590  sp10;
    s_Collision coll;
    u8          flag1Val;

    scratcher->rotation_24.vy  = func_8005BF38(scratcher->rotation_24.vy);
    scratcher->headingAngle_3C = scratcher->rotation_24.vy;

    switch (scratcher->model_0.controlState_2)
    {
        case HangedScratcherControl_5:
        case HangedScratcherControl_6:
        case HangedScratcherControl_7:
        case HangedScratcherControl_10:
        case HangedScratcherControl_12:
        case HangedScratcherControl_13:
            scratcher->field_34 += g_DeltaTime2;
            break;
    }

    func_8005CB20(scratcher, &sp10, scratcher->properties_E4.hangedScratcher.offsetX_F0, scratcher->properties_E4.hangedScratcher.offsetZ_F2);

    scratcher->properties_E4.hangedScratcher.offsetZ_F2 = Q12(0.0f);
    scratcher->properties_E4.hangedScratcher.offsetX_F0 = Q12(0.0f);

    flag1Val = scratcher->properties_E4.hangedScratcher.flags_E8 & HangedScratcherFlag_0;

    if (scratcher->position_18.vy == sp10.field_C)
    {
        scratcher->properties_E4.hangedScratcher.flags_E8 &= ~HangedScratcherFlag_0;

        if (flag1Val)
        {
            if (scratcher->model_0.anim_4.status_0 == ANIM_STATUS(HangedScratcherAnim_10, true))
            {
                Collision_Get(&coll, scratcher->position_18.vx, scratcher->position_18.vz);
                if (coll.field_8 == 11)
                {
                    func_8005DC1C(Sfx_Unk1582, &scratcher->position_18, Q8(0.5f), 0);
                }
                else
                {
                    func_8005DC1C(Sfx_Unk1581, &scratcher->position_18, Q8(0.5f), 0);
                }
            }
            else if (scratcher->model_0.anim_4.status_0 == ANIM_STATUS(HangedScratcherAnim_16, true))
            {
                Collision_Get(&coll, scratcher->position_18.vx, scratcher->position_18.vz);
                if (coll.field_8 == 11)
                {
                    func_8005DC1C(Sfx_Unk1582, &scratcher->position_18, Q8(0.25f), 0);
                }
                else
                {
                    func_8005DC1C(Sfx_Unk1581, &scratcher->position_18, Q8(0.25f), 0);
                }
            }
        }
    }
    else
    {
        scratcher->properties_E4.hangedScratcher.flags_E8 |= HangedScratcherFlag_0;
    }
}
