void Ai_Splithead_DamageTake(s_SubCharacter* splithead)
{
    u8  playerIsDead;
    s32 dmgAmt;
    s32 newHealth;

    // `func_8007F250` sets first arg to `D_800C4561` value, which gets set to 1 by `Player_ReceiveDamage` when player health is 0 or below.
    // Second arg is used to set `g_Player_DisableDamage`.
    // `playerIsDead` gets checked below, if it's set then splithead health isn't allowed to go below 0.
    // Presumably this is used to prevent both player + splithead from dying at the same moment?
    func_8007F250(&playerIsDead, splithead->health_B0 == 0);

    // No damage or health is already 0, skip func.
    if (splithead->damage_B4.amount_C == Q12(0.0f) || splithead->health_B0 == 0) // Splithead health isn't Q12, going off checks below?
    {
        return;
    }

    dmgAmt = FP_FROM(splithead->damage_B4.amount_C, Q12_SHIFT);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        dmgAmt >>= 1;
    }

    if (dmgAmt == 0)
    {
        dmgAmt = 1;
    }

    if (splithead->properties_E4.splitHead.flags_E8 & (1 << 0))
    {
        // TODO: Odd `WEAPON_ATTACK` value.
        if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Hard && g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_Hammer, 3))
        {
            dmgAmt <<= 5;
        }
        else
        {
            dmgAmt <<= 4;
        }
    }

    newHealth = splithead->health_B0 - dmgAmt;
    if (playerIsDead)
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

    if (splithead->health_B0 < 24000 && !(splithead->properties_E4.splitHead.flags_E8 & (1 << 4)))
    {
        splithead->model_0.state_2                   = 4;
        splithead->properties_E4.splitHead.flags_E8 |= (1 << 4);
    }
    else if (splithead->health_B0 == 0)
    {
        if (ANIM_STATUS_IDX_GET(splithead->model_0.anim_4.status_0) == SplitheadAnim_Unk2)
        {
            splithead->model_0.anim_4.status_0 = (1 << 4);
        }
        else if (splithead->moveSpeed_38 > 0)
        {
            splithead->properties_E4.splitHead.flags_E8 |= (1 << 5);
        }
        else if (splithead->moveSpeed_38 < 0)
        {
            splithead->properties_E4.splitHead.flags_E8 &= ~(1 << 5);
        }

        splithead->model_0.state_2 = 6;
    }
    else if (splithead->properties_E4.splitHead.flags_E8 & (1 << 0))
    {
        splithead->properties_E4.splitHead.flags_E8 |= (1 << 6) | (1 << 7);
    }

    splithead->damage_B4.amount_C      = 0;
    splithead->damage_B4.position_0.vz = 0;
    splithead->damage_B4.position_0.vy = 0;
    splithead->damage_B4.position_0.vx = 0;

    func_8007F250(&playerIsDead, splithead->health_B0 == 0);
}
