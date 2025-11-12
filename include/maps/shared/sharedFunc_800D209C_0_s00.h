void sharedFunc_800D209C_0_s00(void)
{
    g_SysWork.playerCombatInfo_38.weaponAttack_F = NO_VALUE;
    g_SavegamePtr->equippedWeapon_AA             = InventoryItemId_Unequipped;

    Player_ControlFreeze();
    sharedFunc_800D2C7C_0_s00(84);
}
