void sharedFunc_800D0CB8_0_s00()
{
    u8 unkValueDiv4;

    switch (g_SavegamePtr->mapOverlayId_A4)
    {
        case MapOverlayId_MAP0_S00:
        case MapOverlayId_MAP0_S01:
        case MapOverlayId_MAP1_S02:
        case MapOverlayId_MAP1_S03:
        case MapOverlayId_MAP4_S02:
            unkValueDiv4 = sharedData_800E32CC_0_s00 >> 2; // sharedData_800E32CC_0_s00 / 4

            // Could be compiler-optimized range checks, something like `if (x > y && x < y + 0xf)`?
            if ((sharedData_800E32CC_0_s00 - sharedData_800DD58C_0_s00) > 0xF)
            {
                sharedData_800E32CC_0_s00 -= 0xF;
            }
            else if ((sharedData_800DD58C_0_s00 - sharedData_800E32CC_0_s00) > 0xF)
            {
                sharedData_800E32CC_0_s00 += 0xF;
            }

            if (sharedData_800E32CC_0_s00 == 0)
            {
                g_SysWork.field_234B_0 = 0;
                func_8004690C(0x550);
            }

            if (g_SysWork.field_234B_0 != 0)
            {
                func_8005DE0C(0x550, &g_SysWork.player_4C.chara_0.position_18, unkValueDiv4, 0, 0);
            }
            else if (sharedData_800E32CC_0_s00 != 0)
            {
                Sd_EngineCmd(0x550U);
                g_SysWork.field_234B_0 = 1;
            }
    }
}
