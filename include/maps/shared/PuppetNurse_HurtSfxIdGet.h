s32 PuppetNurse_HurtSfxIdGet(s_SubCharacter* nurse)
{
    s32 weaponAttack;
    s32 idx;

    weaponAttack = nurse->attackReceived_41;
    if (weaponAttack != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap)      &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Hold)     &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Multitap) &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap)      &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Hold)     &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Multitap))
    {
        idx = D_800AD4C8[weaponAttack].field_10;
        return g_PuppetNurseHurtSfxIdx[idx];
    }

    return NO_VALUE;
}
