void sharedFunc_800D209C_0_s00()
#ifdef SHARED_FUNC_IMPL
{
    g_SysWork.playerCombatInfo_38.equippedWeapon_F = NO_VALUE;
    g_SavegamePtr->equippedWeapon_AA               = InventoryItemId_Unequipped;

    sharedFunc_800D20E4_0_s00();
    sharedFunc_800D2C7C_0_s00(84);
}
#else
;
#endif
