extern s32 sharedData_800D5884_1_s05;

void sharedFunc_800CF990_1_s05(s_SubCharacter* splithead)
{
    s32     keyframeIdx;
    s32     sfxVol;
    s32     sfxPitch;
    VECTOR3 sfxPos;

    keyframeIdx = FP_FROM(splithead->model_0.anim_4.time_4, Q12_SHIFT);
    sfxVol      = ((FP_TO(sharedData_800D5884_1_s05, Q12_SHIFT) / Q12(24.0f)) >> 7) + 96;                          // @hack `(/ Q12(24.0f)) >> 7` should be same as `/ 0xC00000`?
    sfxPitch    = ((FP_TO(sharedData_800D5884_1_s05, Q12_SHIFT) / Q12(24.0f)) >> 6) - 64 + Rng_GenerateUInt(0, 7); // @hack `(/ Q12(24.0f)) >> 6` should be same as `/ 0x600000`?

    if ((keyframeIdx >= 147 && keyframeIdx < 162) ||
        (keyframeIdx >= 187 && keyframeIdx < 201))
    {
        if (splithead->properties_E4.splithead.field_108[0] == 0)
        {
            sfxPos.vx = splithead->position_18.vx + FP_FROM(Math_Sin(splithead->rotation_24.vy + FP_ANGLE(45.0f)) * Q12(1.2f), Q12_SHIFT);
            sfxPos.vy = splithead->position_18.vy;
            sfxPos.vz = splithead->position_18.vz + FP_FROM(Math_Cos(splithead->rotation_24.vy + FP_ANGLE(45.0f)) * Q12(1.2f), Q12_SHIFT);

            func_8005DD44(Sfx_Unk1472, &sfxPos, sfxVol, sfxPitch);
            splithead->properties_E4.splithead.field_108[0]++;
        }
    }
    else
    {
        splithead->properties_E4.splithead.field_108[0] = 0;
    }

    if ((keyframeIdx >= 132 && keyframeIdx < 148) ||
        keyframeIdx == 161 ||
        (keyframeIdx >= 172 && keyframeIdx < 185) ||
        (keyframeIdx >= 200 && keyframeIdx < 202))
    {
        if (splithead->properties_E4.splithead.field_108[1] == 0)
        {
            sfxPos.vx = splithead->position_18.vx + FP_FROM(Math_Sin(splithead->rotation_24.vy + FP_ANGLE(135.0f)) * Q12(1.2f), Q12_SHIFT);
            sfxPos.vy = splithead->position_18.vy;
            sfxPos.vz = splithead->position_18.vz + FP_FROM(Math_Cos(splithead->rotation_24.vy + FP_ANGLE(135.0f)) * Q12(1.2f), Q12_SHIFT);
            splithead->properties_E4.splithead.field_108[1]++;
        }
    }
    else
    {
        splithead->properties_E4.splithead.field_108[1] = 0;
    }

    if ((keyframeIdx >= 132 && keyframeIdx < 147) ||
        (keyframeIdx >= 160 && keyframeIdx < 162) ||
        (keyframeIdx >= 172 && keyframeIdx < 187) ||
        (keyframeIdx >= 199 && keyframeIdx < 202))
    {
        if (splithead->properties_E4.splithead.field_108[2] == 0)
        {
            sfxPos.vx = splithead->position_18.vx + FP_FROM(Math_Sin(splithead->rotation_24.vy - FP_ANGLE(45.0f)) * Q12(1.2f), Q12_SHIFT);
            sfxPos.vy = splithead->position_18.vy;
            sfxPos.vz = splithead->position_18.vz + FP_FROM(Math_Cos(splithead->rotation_24.vy - FP_ANGLE(45.0f)) * Q12(1.2f), Q12_SHIFT);

            func_8005DD44(Sfx_Unk1472, &sfxPos, sfxVol, sfxPitch);
            splithead->properties_E4.splithead.field_108[2]++;
        }
    }
    else
    {
        splithead->properties_E4.splithead.field_108[2] = 0;
    }

    if ((keyframeIdx >= 146 && keyframeIdx < 161) ||
        (keyframeIdx >= 186 && keyframeIdx < 200))
    {
        if ((u8)splithead->properties_E4.splithead.field_108[3] == 0)
        {
            sfxPos.vx = splithead->position_18.vx + FP_FROM(Math_Sin(splithead->rotation_24.vy - FP_ANGLE(135.0f)) * Q12(1.2f), Q12_SHIFT);
            sfxPos.vy = splithead->position_18.vy;
            sfxPos.vz = splithead->position_18.vz + FP_FROM(Math_Cos(splithead->rotation_24.vy - FP_ANGLE(135.0f)) * Q12(1.2f), Q12_SHIFT);
            splithead->properties_E4.splithead.field_108[3]++;
        }
    }
    else
    {
        splithead->properties_E4.splithead.field_108[3] = 0;
    }

    if (splithead->properties_E4.splithead.field_10C == Q12(0.0f))
    {
        if (splithead->properties_E4.splithead.flags_E8 & SplitheadFlag_8)
        {
            func_8005DC1C(Sfx_Unk1422, &splithead->position_18, Q8_CLAMPED(0.5f), 0);
            splithead->properties_E4.splithead.field_10C = Rng_GenerateInt(Q12(3.0f), Q12(5.0f) - 1);
        }
        else if (splithead->properties_E4.splithead.flags_E8 & SplitheadFlag_7)
        {
            func_8005DC1C(Sfx_Unk1474, &splithead->position_18, Q8_CLAMPED(0.5f), 0);
            splithead->properties_E4.splithead.field_10C = Rng_GenerateInt(Q12(1.5f), Q12(2.5f) - 1);
        }
    }
    else
    {
        splithead->properties_E4.splithead.field_10C -= g_DeltaTime0;
        if (splithead->properties_E4.splithead.field_10C < Q12(0.0f))
        {
            splithead->properties_E4.splithead.field_10C = Q12(0.0f);
        }
    }

    splithead->properties_E4.splithead.flags_E8 &= ~(SplitheadFlag_8 | SplitheadFlag_7);
}
