void sharedFunc_800D2214_1_s05(s_SubCharacter* splitHead)
{
    switch (splitHead->model_0.anim_4.status_0)
    {
        case 23:
            Chara_MoveSpeedUpdate(splitHead, Q12(0.5f));

            if (!sharedFunc_800D4530_1_s05(splitHead))
            {
                break;
            }

        case 2:
        case 3:
        case 20:
        case 21:
        case 22:
            splitHead->model_0.anim_4.status_0 = ANIM_STATUS(7, false);
            Chara_MoveSpeedUpdate(splitHead, Q12(1.0f));
            break;

        default:
            break;

        case 14:
        case 15:
        case 16:
        case 17:
        case 24:
        case 25:
        case 26:
        case 27:
            Chara_MoveSpeedUpdate(splitHead, Q12(1.0f));

            if (!Savegame_EventFlagGet(EventFlag_131))
            {
                func_8005DC1C(Sfx_Unk1479, &splitHead->position_18, Q8_CLAMPED(0.5f), 0);
            }

            Savegame_EventFlagSet(EventFlag_131);
            break;
    }
}
