s32 Chara_DamageTake(s_SubCharacter* chara, q19_12 mult)
{
    s32 temp_a0;
    s32 temp_v0;
    s32 dmg;
    s32 var_hi;
    s32 sign_2;
    s32 attack;
    u32 var_lo;
    u32 ret;
    u32 sign;
    u8  temp_a1;
    s32 animStatus;
    s32 angle;
    u32 var0;
    u16 dmgConst;
    s32 dmgWtf;

    dmg        = chara->damage_B4.amount_C;
    animStatus = chara->model_0.anim_4.status_0;
    attack     = chara->attackReceived_41;
    ret        = 0;

    if (chara->properties_E4.unk0.field_E8_0 == 3)
    {
        switch (attack)
        {
            case 1:
            case 4:
                dmg += dmg / 2;
                break;
            case 0x21:
            case 0x22:
                dmg = dmg / 2;
                break;
            default:
                break;
        }
    }

    if (chara->health_B0 > 0)
    {
        if (animStatus == ANIM_STATUS(21, true))
        {
            temp_v0 = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 10.0f, Q12_SHIFT);
            if (temp_v0 < chara->health_B0)
            {
                chara->health_B0 -= temp_v0;
            }
            else
            {
                chara->health_B0 = 0;
            }
        }

        chara->damage_B4.amount_C = 0;
        angle                     = mult; // @hack

        dmg = FP_MULTIPLY_PRECISE(dmg, angle, Q12_SHIFT);
        if (dmg < chara->health_B0)
        {
            chara->health_B0 -= dmg;
        }
        else
        {
            chara->health_B0 = 0;
        }
    }

    if (dmg > 0 || chara->health_B0 <= 0)
    {
        temp_a1 = D_800AD4C8[attack].field_10;
        angle   = FP_ANGLE_NORM_S(g_SysWork.player_4C.chara_0.rotation_24.vy - chara->rotation_24.vy);

#ifdef MAP0_S01
        if (chara->health_B0 <= Q12(0.0f))
#else
        if (chara->health_B0 <= Q12(120.0f))
#endif
        {
            if (dmg > Q12(5.0f))
            {
                ret = 4;
            }
            else
            {
                ret = 3;
            }
        }
        else if (chara->properties_E4.unk0.field_E8_0 != 3 && temp_a1 == 2 && Math_CheckAngleRange(angle, FP_ANGLE(120.0f)))
        {
            ret = 2;
        }
        else if (chara->properties_E4.unk0.field_E8_0 == 3)
        {
            if (dmg > Q12(45.0f) || temp_a1 == 1)
            {
                ret = 1;
            }
        }
        else
        {
            if (dmg > Q12(20.0f) || temp_a1 == 1)
            {
                ret = 1;
            }
        }
    }
    return ret;
}
