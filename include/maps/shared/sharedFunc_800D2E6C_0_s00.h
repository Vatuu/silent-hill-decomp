void sharedFunc_800D2E6C_0_s00(void)
{
#if defined(MAP0_S01)
    g_SysWork.playerCombatInfo_38.weaponAttack_F = WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap);
    func_8003CD6C(&g_SysWork.playerCombatInfo_38);

    g_SysWork.playerCombatInfo_38.weaponAttack_F = NO_VALUE;

    func_8003D03C();
#endif
}
