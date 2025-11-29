s32 sharedFunc_800CD980_3_s03(s_SubCharacter* chara)
{
    s32 weaponAttack;
    s32 idx;

    weaponAttack = chara->attackReceived_41;
    if (weaponAttack != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Tap)      &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Hold)     &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_Chainsaw,  AttackInputType_Multitap) &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap)      &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Hold)     &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Multitap))
    {
        idx = D_800AD4C8[weaponAttack].field_10;
        return sharedData_800D57E0_3_s03[idx];
    }

    return NO_VALUE;
}
