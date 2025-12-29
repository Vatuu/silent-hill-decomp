s32 Chara_DamageTake(s_SubCharacter* chara, q19_12 mult)
{
    q19_12 damage;
    s32    animStatus;
    s32    attack;
    u32    ret;
    s32    temp_v0;
    u8     temp_a1;
    q19_12 angle;

    damage     = chara->damage_B4.amount_C;
    animStatus = chara->model_0.anim_4.status_0;
    attack     = chara->attackReceived_41;
    ret        = 0;

    if (chara->properties_E4.unk0.field_E8_0 == 3)
    {
        switch (attack)
        {
            case 1:
            case 4:
                damage += damage / 2;
                break;

            case 33:
            case 34:
                damage = damage / 2;
                break;

            default:
                break;
        }
    }

    if (chara->health_B0 > Q12(0.0f))
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
                chara->health_B0 = Q12(0.0f);
            }
        }

        chara->damage_B4.amount_C = Q12(0.0f);
        angle                     = mult; // @hack

        damage = FP_MULTIPLY_PRECISE(damage, angle, Q12_SHIFT);
        if (damage < chara->health_B0)
        {
            chara->health_B0 -= damage;
        }
        else
        {
            chara->health_B0 = Q12(0.0f);
        }
    }

    if (damage > Q12(0.0f) || chara->health_B0 <= Q12(0.0f))
    {
        temp_a1 = D_800AD4C8[attack].field_10;
        angle   = FP_ANGLE_NORM_S(g_SysWork.playerWork_4C.player_0.rotation_24.vy - chara->rotation_24.vy);

#ifdef MAP0_S01
        if (chara->health_B0 <= Q12(0.0f))
#else
        if (chara->health_B0 <= Q12(120.0f))
#endif
        {
            if (damage > Q12(5.0f))
            {
                ret = 4;
            }
            else
            {
                ret = 3;
            }
        }
        else if (chara->properties_E4.unk0.field_E8_0 != 3 && temp_a1 == 2 && Math_CheckSignedRange(angle, FP_ANGLE(120.0f)))
        {
            ret = 2;
        }
        else if (chara->properties_E4.unk0.field_E8_0 == 3)
        {
            if (damage > Q12(45.0f) || temp_a1 == 1)
            {
                ret = 1;
            }
        }
        else
        {
            if (damage > Q12(20.0f) || temp_a1 == 1)
            {
                ret = 1;
            }
        }
    }

    return ret;
}
