void sharedSymbol_800D3B0C_0_s01(s_SubCharacter* chara)
{
    s32 animTime;
    s32 var0;
    s32 var1;
    s32 var2;
    u32 var3;
    u32 stateStep;
    s32 field40;
    u32 modelState;
    u32 animStatus;

    field40 = chara->field_40;
    switch (field40 % 3)
    {
        case 0:
        default:
            var2 = 0;
            break;

        case 1:
            var2 = 1;
            break;

        case 2:
            var2 = 2;
            break;
    }

    switch(field40 - (field40 / 2) * 2)
    {
        case 0:
        default:
            var1 = 1;
            break;

        case 1:
            var1 = 0;
            break;
    }

    stateStep = 0;
    switch (chara->model_0.stateStep_3)
    {
#if defined(MAP0_S01)
        case 12:
        default:
            var0 = 4;
            var1 = 1;
            var2 = 3;
            animStatus = NO_VALUE;
            var3 = 1;
            break;

        case 13:
            animStatus = ANIM_STATUS(19, true);
            if (g_SavegamePtr->mapOverlayId_A4 == 1)
            {
                var0 = 2;
                var1 = 1;
                var2 = 2;
                animStatus = ANIM_STATUS(2, true);
                var3 = 46;
            }
            else
            {
                var0 = 2;
                if (chara->model_0.anim_4.status_0 == ANIM_STATUS(19, true))
                {
                    animStatus = NO_VALUE;
                }
                var3 = 18;
            }
            break;
#else
        default:
            var0 = 1;
            animStatus = ANIM_STATUS(23, true);
            var3 = 3;
            break;

        case 0:
        case 2:
            var0 = 1;
            animStatus = ANIM_STATUS(25, true);
            var3 = 5;
            break;

        case 3:
            var0 = 1;
            animStatus = ANIM_STATUS(19, true);
            var3 = 19;
            break;

        case 4:
            var0 = 0;
            animStatus = ANIM_STATUS(25, true);
            var3 = 4;
            stateStep = 64;
            break;
        case 5:
            var0 = 0;
            animStatus = ANIM_STATUS(19, true);
            var3 = 18;
            stateStep = 64;
            break;

        case 6:
            var0 = 0;
            animStatus = ANIM_STATUS(17, true);
            var2 = 2;
            var3 = 33;
            stateStep = 64;
            break;

        case 8:
            var0 = 1;
            animStatus = ANIM_STATUS(14, true);
            var2 = 4;
            var3 = 9;
            break;

        case 9:
            var0 = 3;
            animStatus = ANIM_STATUS(19, true);;
            var3 = 19;
            var2 = 2;
            chara->health_B0 *= 4;;
            break;

        case 11:
            var0 = 0;
            animStatus = ANIM_STATUS(17, true);
            var3 = 33;
            stateStep = 65;
            var2 = 2;
            break;

        case 7:
            var0 = 0;
            animStatus = ANIM_STATUS(17, true);
            var3 = 33;
            stateStep = 66;
            var2 = 2;
            break;

        case 10:
            var0 = 0;
            animStatus = ANIM_STATUS(17, true);
            var3 = 33;
            stateStep = 67;
            var2 = 2;
            chara->health_B0 -= (chara->health_B0 >> 2);
            break;
#endif
    }

    chara->model_0.state_2 = var3;
    chara->model_0.stateStep_3 = stateStep;
    chara->properties_E4.player.flags_11C = 0;
    chara->properties_E4.unk0.field_E8_0 = var0;
    chara->properties_E4.unk0.field_E8_4 = var1;
    chara->properties_E4.unk0.field_E8_8 = var2;

    if (var3 == 1)
    {
        chara->properties_E4.unk0.flags_11C = CharaUnk0Flag_Unk16;
    }

    if ((animStatus != NO_VALUE) && (animStatus != chara->model_0.anim_4.status_0))
    {
        chara->model_0.anim_4.status_0 = animStatus;
        animTime = func_80044918(&chara->model_0.anim_4)->startKeyframeIdx_C;
        chara->model_0.anim_4.alpha_A = 0;
        chara->model_0.anim_4.keyframeIdx_8 = animTime;
        chara->model_0.anim_4.time_4 = FP_TO(animTime, Q12_SHIFT);
    }
}
