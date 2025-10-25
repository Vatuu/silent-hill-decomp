void sharedFunc_800CE8B8_0_s02(void)
{
    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 5:
            func_8003640C(6);
            break;

        case 18:
            func_8003640C(!Savegame_EventFlagGet(EventFlag_379) ? 29 : 7);
            break;

        case 17:
            func_8003640C(7);
            break;
    }
}
