void Ai_Splithead_DamageTake(s_SubCharacter* splithead)
{
    u8  isPlayerDead;
    s32 damageAmt;
    s32 newHealth;

    // `func_8007F250` sets first arg to `D_800C4561` value, which gets set to 1 by `Player_ReceiveDamage` when player health is 0 or below.
    // Second arg is used to set `g_Player_DisableDamage`.
    // `isPlayerDead` gets checked below. If it's set, splithead health isn't allowed to go below 0.
    // Presumably this is used to prevent both player + splithead from dying at the same moment?
    func_8007F250(&isPlayerDead, splithead->health_B0 == 0);

    // Return early if no damage or health is already 0.
    if (splithead->damage_B4.amount_C == Q12(0.0f) || splithead->health_B0 == 0) // TODO: Splithead health isn't Q12 going off checks below?
    {
        return;
    }

    damageAmt = FP_FROM(splithead->damage_B4.amount_C, Q12_SHIFT);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        damageAmt >>= 1;
    }

    if (damageAmt == 0)
    {
        damageAmt = 1;
    }

    if (splithead->properties_E4.splitHead.flags_E8 & SplitheadFlag_0)
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

    newHealth = splithead->health_B0 - damageAmt;
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

    splithead->health_B0 = newHealth;

    if (splithead->health_B0 < 24000 && !(splithead->properties_E4.splitHead.flags_E8 & SplitheadFlag_4))
    {
        splithead->model_0.state_2                   = 4;
        splithead->properties_E4.splitHead.flags_E8 |= SplitheadFlag_4;
    }
    else if (splithead->health_B0 == 0)
    {
        if (ANIM_STATUS_IDX_GET(splithead->model_0.anim_4.status_0) == SplitheadAnim_Unk2)
        {
            splithead->model_0.anim_4.status_0 = ANIM_STATUS(8, false);
        }
        else if (splithead->moveSpeed_38 > Q12(0.0f))
        {
            splithead->properties_E4.splitHead.flags_E8 |= SplitheadFlag_5;
        }
        else if (splithead->moveSpeed_38 < Q12(0.0f))
        {
            splithead->properties_E4.splitHead.flags_E8 &= ~SplitheadFlag_5;
        }

        splithead->model_0.state_2 = 6;
    }
    else if (splithead->properties_E4.splitHead.flags_E8 & SplitheadFlag_0)
    {
        splithead->properties_E4.splitHead.flags_E8 |= SplitheadFlag_6 | SplitheadFlag_7;
    }

    splithead->damage_B4.amount_C      = Q12(0.0f);
    splithead->damage_B4.position_0.vz = Q12(0.0f);
    splithead->damage_B4.position_0.vy = Q12(0.0f);
    splithead->damage_B4.position_0.vx = Q12(0.0f);

    func_8007F250(&isPlayerDead, splithead->health_B0 == 0);
}
