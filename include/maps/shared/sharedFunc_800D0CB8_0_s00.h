void sharedFunc_800D0CB8_0_s00(void)
{
    u8 unkValDiv4;

    switch (g_SavegamePtr->mapOverlayId_A4)
    {
        case MapOverlayId_MAP0_S00:
        case MapOverlayId_MAP0_S01: // @unused Checks for `MAP0_S01`, but map itself doesn't contain this func?
        case MapOverlayId_MAP1_S02:
        case MapOverlayId_MAP1_S03:
        case MapOverlayId_MAP4_S02:
            unkValDiv4 = sharedData_800E32CC_0_s00 >> 2; // `sharedData_800E32CC_0_s00 / 4`

            // TODO: Could be compiler-optimized range checks, something like `if (x >= y && x <= (y + 0xf))`?
            // (https://wiki.decomp.dev/en/resources/guides/assembly-patterns#range-check)
            if ((sharedData_800E32CC_0_s00 - sharedData_800DD58C_0_s00) > 15)
            {
                sharedData_800E32CC_0_s00 -= 15;
            }
            else if ((sharedData_800DD58C_0_s00 - sharedData_800E32CC_0_s00) > 15)
            {
                sharedData_800E32CC_0_s00 += 15;
            }

            if (sharedData_800E32CC_0_s00 == 0)
            {
                g_SysWork.field_234B_0 = 0;
                func_8004690C(Sfx_Unk1360);
            }

            if (g_SysWork.field_234B_0 != 0)
            {
                func_8005DE0C(Sfx_Unk1360, &g_SysWork.player_4C.chara_0.position_18, unkValDiv4, 0, 0);
            }
            else if (sharedData_800E32CC_0_s00 != 0)
            {
                Sd_EngineCmd(Sfx_Unk1360);
                g_SysWork.field_234B_0 = 1;
            }
    }
}
