bool sharedFunc_800D2E94_0_s00(void)
{
#if defined(MAP2_S00)
    s_SubCharacter* npcChara;
    s32             playerDist;

    npcChara = &g_SysWork.npcs_1A0[5];

    if (g_SysWork.player_4C.chara_0.position_18.vx < Q12(-255.0f) &&
        g_SysWork.player_4C.chara_0.position_18.vz > Q12(-110.0f) &&
        g_SysWork.player_4C.chara_0.position_18.vz < Q12(-100.0f))
    {
        playerDist = SquareRoot0(SQUARE(Q12(-262.0f) - g_SysWork.player_4C.chara_0.position_18.vx) +
                                 SQUARE(Q12(-104.0f) - g_SysWork.player_4C.chara_0.position_18.vz));

        if (npcChara->model_0.state_2 == 0 || npcChara->model_0.stateStep_3 == 0)
        {
            npcChara->health_B0 = Q12(400.0f);
            npcChara->model_0.state_2++;
            npcChara->field_C8           = Q12(-0.2f);
            npcChara->field_CA           = Q12(0.2f);
            npcChara->field_D4           = Q12(0.05f);
            npcChara->field_D6           = Q12(0.5f);
            npcChara->field_40           = 0;
            npcChara->field_CE           = 0;
            npcChara->field_D0           = 0;
            npcChara->field_D8.offsetZ_6 = 0;
            npcChara->field_D8.offsetX_4 = 0;
            npcChara->field_D8.offsetZ_2 = 0;
            npcChara->field_D8.offsetX_0 = 0;
            npcChara->position_18.vx     = Q12(-262.0f);
            npcChara->position_18.vy     = Q12(-1.1f);
            npcChara->position_18.vz     = Q12(-104.0f);
            npcChara->field_E1_0         = 3;
            npcChara->model_0.stateStep_3++;
            npcChara->flags_3E               |= CharaFlag_Unk3;
            npcChara->model_0.anim_4.flags_2 &= ~(AnimFlag_Visible | AnimFlag_Unlocked);
        }

        // TODO: `else` branch is duplicated here, is there some way to merge them? Decompiler used `goto`.
        if (npcChara->health_B0 > Q12(0.0f))
        {
            if (playerDist < Q12(2.0f) &&
                Savegame_EventFlagGet(EventFlag_167) && !Savegame_EventFlagGet(EventFlag_168) &&
                g_SysWork.playerCombatInfo_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Tap))
            {
                npcChara->model_0.charaId_0 = Chara_Padlock;
            }
            else
            {
                if (npcChara->health_B0 <= Q12(0.0f))
                {
                    if (Savegame_EventFlagGet(EventFlag_167) && npcChara->model_0.charaId_0 == Chara_Padlock)
                    {
                        npcChara->flags_3E |= CharaFlag_Unk1;
                        Savegame_EventFlagSet(EventFlag_168);
                    }
                }

                npcChara->model_0.charaId_0 = Chara_None;
            }
        }
        else
        {
            if (Savegame_EventFlagGet(EventFlag_167) && npcChara->model_0.charaId_0 == Chara_Padlock)
            {
                npcChara->flags_3E |= CharaFlag_Unk1;
                Savegame_EventFlagSet(EventFlag_168);
            }
            npcChara->model_0.charaId_0 = Chara_None;
        }

        if (npcChara->damageReceived_C0 != Q12(0.0f))
        {
            if (WEAPON_ATTACK_ID_GET(g_SysWork.playerCombatInfo_38.weaponAttack_F) == EquippedWeaponId_KitchenKnife)
            {
                npcChara->damageReceived_C0 >>= 1;
            }

            // Apply `damageReceived` to character health.
            if (g_SysWork.playerCombatInfo_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                npcChara->health_B0 = NO_VALUE;
            }
            else
            {
                npcChara->health_B0 -= npcChara->damageReceived_C0;
            }

            npcChara->damageReceived_C0 = Q12(0.0f);
        }

        return true;
    }

    npcChara->model_0.state_2     = 0;
    npcChara->model_0.stateStep_3 = 0;
    npcChara->model_0.charaId_0   = Chara_None;
    npcChara->health_B0           = Q12(0.0f);
#endif
    return false;
}
