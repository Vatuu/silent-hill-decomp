void sharedFunc_800D17BC_1_s05(s_SubCharacter* splitHead)
{
    s32 vol;
    s32 timer0;
    s16 timer1;
    s16 timer1_div6;

    Chara_MoveSpeedUpdate(splitHead, Q12(1.5997f));
    switch (splitHead->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(11, false):
        case ANIM_STATUS(11, true):
            splitHead->properties_E4.splitHead.flags_E8 |= 1 << 3;

            if (!sharedFunc_800D4530_1_s05(splitHead))
            {
                break;
            }

        case ANIM_STATUS(10, true):
            splitHead->model_0.anim_4.status_0 = ANIM_STATUS(1, false);
            SD_Call(Sfx_Unk1477);
            break;

        case ANIM_STATUS(1, false):
        case ANIM_STATUS(1, true):
            timer0      = splitHead->properties_E4.splitHead.timer_F4;
            timer1      = sharedData_800D5880_1_s05;
            timer1_div6 = timer1 / 6;

            if (timer0 < timer1_div6)
            {
                vol = (timer0 << 7) / timer1_div6;
            }
            else if (((timer1 * 5) / 6) < timer0)
            {
                vol = ((sharedData_800D5880_1_s05 - timer0) << 7) / timer1_div6;
            }
            else
            {
                vol = 0x80;
            }

            func_8005DE0C(Sfx_Unk1477, &splitHead->position_18, vol, Q12(16.0f), 0);

            if (splitHead->properties_E4.splitHead.timer_F4 > sharedData_800D5880_1_s05)
            {
                sharedData_800D5880_1_s05                   = Q12(3.8f);
                splitHead->model_0.controlState_2           = SplitHeadControl_5;
                splitHead->properties_E4.splitHead.timer_F4 = Q12(0.0f);
                splitHead->model_0.anim_4.status_0          = ANIM_STATUS(11, false);

                Sd_SfxStop(Sfx_Unk1477);
                break;
            }

            splitHead->properties_E4.splitHead.timer_F4 += g_DeltaTime0;
            break;
    }
}
