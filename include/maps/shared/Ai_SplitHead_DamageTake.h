void Ai_SplitHead_DamageTake(s_SubCharacter* splitHead)
{
    u8  isPlayerDead;
    s32 damageAmt;
    s32 newHealth;

    #define splitHeadProps splitHead->properties_E4.splitHead

    // `func_8007F250` sets first arg to `D_800C4561` value, which gets set to 1 by `Player_ReceiveDamage` when player health is 0 or below.
    // Second arg is used to set `g_Player_DisableDamage`.
    // `isPlayerDead` gets checked below. If it's set, Split Head health isn't allowed to go below 0.
    // Presumably this is used to prevent both player + Split Head from dying at the same moment?
    func_8007F250(&isPlayerDead, splitHead->health_B0 == 0);

    // Return early if no damage or health is already 0.
    if (splitHead->damage_B4.amount_C == Q12(0.0f) || splitHead->health_B0 == 0) // TODO: Split Head health isn't Q12 going off checks below?
    {
        return;
    }

    damageAmt = FP_FROM(splitHead->damage_B4.amount_C, Q12_SHIFT);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        damageAmt >>= 1;
    }

    if (damageAmt == 0)
    {
        damageAmt = 1;
    }

    if (splitHeadProps.flags_E8 & SplitHeadFlag_0)
    {
        // TODO: Odd `WEAPON_ATTACK` value. Input type 3 doesn't exist.
        if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Hard &&
            g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_Hammer, 3))
        {
            damageAmt <<= 5;
        }
        else
        {
            damageAmt <<= 4;
        }
    }

    newHealth = splitHead->health_B0 - damageAmt;
    if (isPlayerDead)
    {
        if (newHealth <= 0)
        {
            newHealth = 1;
        }
    }
    else if (newHealth < 0)
    {
        newHealth = 0;
    }
    splitHead->health_B0 = newHealth;

    if (splitHead->health_B0 < 24000 && !(splitHeadProps.flags_E8 & SplitHeadFlag_4))
    {
        splitHead->model_0.controlState_2 = SplitHeadControl_4;
        splitHeadProps.flags_E8   |= SplitHeadFlag_4;
    }
    else if (splitHead->health_B0 == Q12(0.0f))
    {
        if (ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0) == SplitHeadAnim_2)
        {
            splitHead->model_0.anim_4.status_0 = ANIM_STATUS(8, false);
        }
        else if (splitHead->moveSpeed_38 > Q12(0.0f))
        {
            splitHeadProps.flags_E8 |= SplitHeadFlag_5;
        }
        else if (splitHead->moveSpeed_38 < Q12(0.0f))
        {
            splitHeadProps.flags_E8 &= ~SplitHeadFlag_5;
        }

        splitHead->model_0.controlState_2 = SplitHeadControl_6;
    }
    else if (splitHeadProps.flags_E8 & SplitHeadFlag_0)
    {
        splitHeadProps.flags_E8 |= SplitHeadFlag_6 | SplitHeadFlag_7;
    }

    splitHead->damage_B4.amount_C      = Q12(0.0f);
    splitHead->damage_B4.position_0.vz = Q12(0.0f);
    splitHead->damage_B4.position_0.vy = Q12(0.0f);
    splitHead->damage_B4.position_0.vx = Q12(0.0f);

    func_8007F250(&isPlayerDead, splitHead->health_B0 == 0);

    #undef splitHeadProps
}
