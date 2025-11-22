void sharedFunc_800E5FC8_2_s02(s_SubCharacter* chara, s16 arg1, s16 arg2, u8* arg3)
{
    q19_12 animTime;
    q19_12 arg1Plus2;
    q23_8  pitch;
    q23_8  vol;

    animTime  = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
    arg1Plus2 = arg1 + arg2;
    pitch     = Q8(0.0f);
    vol       = Q8(0.0f);

    if (animTime >= arg1Plus2 && animTime < (arg1Plus2 + 2))
    {
        if (*arg3 == 0)
        {
            switch (arg1)
            {
                case 2:
                    pitch = Q8(0.125f);
                    vol   = Q8(0.765625f);
                    break;

                case 8:
                case 15:
                case 93:
                    pitch = Q8(-0.125f);
                    vol   = Q8(0.5f);
                    break;

                case 109:
                    pitch = Q8(0.0f);
                    vol   = Q8(0.5f);
                    break;

                case 110:
                default:
                    pitch = -Q8(0.25f);
                    vol   = Q8(0.125f);
                    break;
            }

            func_8005DD44(Sfx_Unk1405, &chara->position_18, vol, pitch + ((Rng_Rand16() & 0xF) - 7));
            *arg3 = 1;
        }
    }
    else
    {
        *arg3 = 0;
    }
}
