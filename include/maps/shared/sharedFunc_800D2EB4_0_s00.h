void sharedFunc_800D2EB4_0_s00()
#ifdef SHARED_FUNC_IMPL
{
    u8 prevVar;

    prevVar = g_SysWork.playerCombatInfo_38.equippedWeapon_F;

    g_SysWork.playerCombatInfo_38.equippedWeapon_F = NO_VALUE;

    sharedData_800DD59C_0_s00 = prevVar;

    func_8003DD80(1, 17);
}
#else
;
#endif
