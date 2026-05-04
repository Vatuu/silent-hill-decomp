void Map_RoomBgmInit_CondFalse(void)
{
    s32    bgmFlags;
    q19_12 fadeSpeed;
    u8*    layerLimits;

    fadeSpeed   = Q12(0.1f);
    layerLimits = sharedData_800CFB14_0_s02;

    switch (g_SavegamePtr->mapRoomIdx)
    {
        case 1:
            fadeSpeed = Q12(240.0f);
            bgmFlags  = Savegame_EventFlagGet(EventFlag_182) ? (BgmFlag_Layer1 | BgmFlag_Layer2 | BgmFlag_Layer3 | BgmFlag_Layer4 |
                                                                BgmFlag_Layer5 | BgmFlag_Layer6 | BgmFlag_Layer7) :
                                                               (BgmFlag_Layer0 | BgmFlag_MuteAll);
            break;

        case 2:
        case 3:
        case 4:
            bgmFlags    = (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1)) ? BgmFlag_Layer1 : BgmFlag_Layer0;
            layerLimits = sharedData_800CFB1C_0_s02;
            break;

        case 10:
        case 12:
        case 13:
            fadeSpeed   = Q12(0.25f);
            layerLimits = sharedData_800CFB24_0_s02;

            if (Savegame_EventFlagGet(EventFlag_312))
            {
                bgmFlags = BgmFlag_Layer2 | BgmFlag_Layer3;
            }
            else if (!Savegame_EventFlagGet(EventFlag_303))
            {
                if (Savegame_EventFlagGet(EventFlag_311))
                {
                    fadeSpeed = Q12(0.125f);
                    bgmFlags  = BgmFlag_Layer1;
                }
                else
                {
                    fadeSpeed = Q12(240.0f);
                    bgmFlags  = BgmFlag_Layer0 | BgmFlag_MuteAll;
                }
            }
            else
            {
                bgmFlags = BgmFlag_Layer3;
            }
            break;

        case 11:
            bgmFlags = BgmFlag_Layer0 | BgmFlag_MuteAll;
            break;

        case 17:
            layerLimits = sharedData_800CFB2C_0_s02;
            bgmFlags    = BgmFlag_Layer0 | BgmFlag_MuteAll;
            break;

        case 18:
            layerLimits = (g_GameWork.bgmIdx == BgmTrackIdx_7) ? sharedData_800CFB34_0_s02 : sharedData_800CFB3C_0_s02;

            if (Savegame_EventFlagGet(EventFlag_379))
            {
                if (Savegame_EventFlagGet(EventFlag_381))
                {
                    fadeSpeed = Q12(240.0f);
                    Savegame_EventFlagClear(EventFlag_381);
                }
                else
                {
                    fadeSpeed = Q12(0.125f);
                }

                bgmFlags = BgmFlag_Layer0 | BgmFlag_KeepAlive | BgmFlag_MuteAll;
            }
            else if (Savegame_EventFlagGet(EventFlag_381))
            {
                fadeSpeed = Q12(240.0f);
                bgmFlags  = BgmFlag_Layer1 | BgmFlag_Layer2 | BgmFlag_Layer3 | BgmFlag_Layer4 |
                            BgmFlag_Layer5 | BgmFlag_Layer6 | BgmFlag_Layer7 |
                            BgmFlag_KeepAlive;
            }
            else
            {
                fadeSpeed = Savegame_EventFlagGet(EventFlag_378) ? Q12(0.25f) : Q12(0.125f);
                bgmFlags  = BgmFlag_Layer0 | BgmFlag_KeepAlive | BgmFlag_MuteAll;
            }
            break;

        case 6:
        case 7:
        case 8:
        case 9:
            if (g_GameWork.bgmIdx == BgmTrackIdx_34)
            {
                if (Savegame_EventFlagGet(EventFlag_391))
                {
                    fadeSpeed = Q12(240.0f);
                    bgmFlags  = BgmFlag_Layer0 | BgmFlag_MuteAll;
                }
                else if (Savegame_EventFlagGet(EventFlag_395))
                {
                    fadeSpeed = Q12(240.0f);
                    bgmFlags  = BgmFlag_Layer1 | BgmFlag_Layer2 | BgmFlag_Layer3 | BgmFlag_Layer4 |
                                BgmFlag_Layer5 | BgmFlag_Layer6 | BgmFlag_Layer7;
                }
                else
                {
                    bgmFlags = BgmFlag_Layer0 | BgmFlag_MuteAll;
                }
            }
            else
            {
                layerLimits = sharedData_800CFB44_0_s02;
                bgmFlags    = BgmFlag_Layer0;
            }
            break;

        case 5:
            bgmFlags = BgmFlag_Layer0;
            break;

        case 19:
        case 20:
            if (g_GameWork.bgmIdx == BgmTrackIdx_23)
            {
                layerLimits = sharedData_800CFB4C_0_s02;
                fadeSpeed   = Q12(0.25f);

                if (Savegame_EventFlagGet(EventFlag_423) && !Savegame_EventFlagGet(EventFlag_424))
                {
                    bgmFlags = Savegame_EventFlagGet(EventFlag_427) ? (BgmFlag_Layer1 | BgmFlag_Layer3 | BgmFlag_Layer4) :
                                                                      (BgmFlag_Layer1 | BgmFlag_Layer2 | BgmFlag_Layer3);
                }
                else if (Savegame_EventFlagGet(EventFlag_425) && !Savegame_EventFlagGet(EventFlag_426))
                {
                    bgmFlags = BgmFlag_Layer1 | BgmFlag_Layer2;
                }
                else
                {
                    bgmFlags = BgmFlag_Layer1;
                }
            }
            else
            {
                layerLimits = sharedData_800CFB54_0_s02;
                bgmFlags    = BgmFlag_Layer1 | BgmFlag_Layer2 | BgmFlag_Layer4;
            }
            break;

        default:
            bgmFlags = BgmFlag_Layer1 | BgmFlag_Layer2 | BgmFlag_Layer3 | BgmFlag_Layer4 |
                       BgmFlag_Layer5 | BgmFlag_Layer6 | BgmFlag_Layer7;
            break;
    }

    Bgm_Update(bgmFlags, fadeSpeed, layerLimits);
}
