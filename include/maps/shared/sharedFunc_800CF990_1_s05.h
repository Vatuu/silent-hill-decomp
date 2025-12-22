extern s32 sharedData_800D5884_1_s05;

void sharedFunc_800CF990_1_s05(s_SubCharacter* splithead)
{
    s32     animTime;
    s32     sfxVol;
    s32     sfxPitch;
    VECTOR3 sfxPos;

    animTime = FP_FROM(splithead->model_0.anim_4.time_4, Q12_SHIFT);
    sfxVol   = ((FP_TO(sharedData_800D5884_1_s05, Q12_SHIFT) / Q12(24.0f)) >> 7) + 96;                          // @hack `(/ Q12(24.0f)) >> 7` should be same as `/ 0xC00000`?
    sfxPitch = ((FP_TO(sharedData_800D5884_1_s05, Q12_SHIFT) / Q12(24.0f)) >> 6) - 64 + Rng_GenerateUInt(0, 7); // @hack `(/ Q12(24.0f)) >> 6` should be same as `/ 0x600000`?

    if ((animTime >= 147 && animTime < 162) || (animTime >= 187 && animTime < 201))
    {
        if (splithead->properties_E4.splitHead.field_108[0] == 0)
        {
            sfxPos.vx = splithead->position_18.vx + FP_FROM(Math_Sin(splithead->rotation_24.vy + FP_ANGLE(45.0f)) * Q12(1.2f), Q12_SHIFT);
            sfxPos.vy = splithead->position_18.vy;
            sfxPos.vz = splithead->position_18.vz + FP_FROM(Math_Cos(splithead->rotation_24.vy + FP_ANGLE(45.0f)) * Q12(1.2f), Q12_SHIFT);
            func_8005DD44(Sfx_Unk1472, &sfxPos, sfxVol, sfxPitch);
            splithead->properties_E4.splitHead.field_108[0]++;
        }
    }
    else
    {
        splithead->properties_E4.splitHead.field_108[0] = 0;
    }

    if ((animTime >= 132 && animTime < 148) || animTime == 161 || (animTime >= 172 && animTime < 185) || (animTime >= 200 && animTime < 202))
    {
        if (splithead->properties_E4.splitHead.field_108[1] == 0)
        {
            sfxPos.vx = splithead->position_18.vx + FP_FROM(Math_Sin(splithead->rotation_24.vy + FP_ANGLE(135.0f)) * Q12(1.2f), Q12_SHIFT);
            sfxPos.vy = splithead->position_18.vy;
            sfxPos.vz = splithead->position_18.vz + FP_FROM(Math_Cos(splithead->rotation_24.vy + FP_ANGLE(135.0f)) * Q12(1.2f), Q12_SHIFT);
            splithead->properties_E4.splitHead.field_108[1]++;
        }
    }
    else
    {
        splithead->properties_E4.splitHead.field_108[1] = 0;
    }

    if ((animTime >= 132 && animTime < 147) || (animTime >= 160 && animTime < 162) || (animTime >= 172 && animTime < 187) || (animTime >= 199 && animTime < 202))
    {
        if (splithead->properties_E4.splitHead.field_108[2] == 0)
        {
            sfxPos.vx = splithead->position_18.vx + FP_FROM(Math_Sin(splithead->rotation_24.vy - FP_ANGLE(45.0f)) * Q12(1.2f), Q12_SHIFT);
            sfxPos.vy = splithead->position_18.vy;
            sfxPos.vz = splithead->position_18.vz + FP_FROM(Math_Cos(splithead->rotation_24.vy - FP_ANGLE(45.0f)) * Q12(1.2f), Q12_SHIFT);
            func_8005DD44(Sfx_Unk1472, &sfxPos, sfxVol, sfxPitch);
            splithead->properties_E4.splitHead.field_108[2]++;
        }
    }
    else
    {
        splithead->properties_E4.splitHead.field_108[2] = 0;
    }

    if ((animTime >= 146 && animTime < 161) || (animTime >= 186 && animTime < 200))
    {
        if ((u8)splithead->properties_E4.splitHead.field_108[3] == 0)
        {
            sfxPos.vx = splithead->position_18.vx + FP_FROM(Math_Sin(splithead->rotation_24.vy - FP_ANGLE(135.0f)) * Q12(1.2f), Q12_SHIFT);
            sfxPos.vy = splithead->position_18.vy;
            sfxPos.vz = splithead->position_18.vz + FP_FROM(Math_Cos(splithead->rotation_24.vy - FP_ANGLE(135.0f)) * Q12(1.2f), Q12_SHIFT);
            splithead->properties_E4.splitHead.field_108[3]++;
        }
    }
    else
    {
        splithead->properties_E4.splitHead.field_108[3] = 0;
    }

    if (splithead->properties_E4.splitHead.field_10C == 0)
    {
        if (splithead->properties_E4.splitHead.flags_E8 & (1 << 8))
        {
            func_8005DC1C(Sfx_Unk1422, &splithead->position_18, Q8_CLAMPED(0.5f), 0);
            splithead->properties_E4.splitHead.field_10C = Rng_GenerateInt(Q12(3.0f), Q12(5.0f) - 1);
        }
        else if (splithead->properties_E4.splitHead.flags_E8 & (1 << 7))
        {
            func_8005DC1C(Sfx_Unk1474, &splithead->position_18, Q8_CLAMPED(0.5f), 0);
            splithead->properties_E4.splitHead.field_10C = Rng_GenerateInt(Q12(1.5f), Q12(2.5f) - 1);
        }
    }
    else
    {
        splithead->properties_E4.splitHead.field_10C -= g_DeltaTime0;
        if (splithead->properties_E4.splitHead.field_10C < 0)
        {
            splithead->properties_E4.splitHead.field_10C = 0;
        }
    }

    splithead->properties_E4.splitHead.flags_E8 &= ~((1 << 8) | (1 << 7));
}
