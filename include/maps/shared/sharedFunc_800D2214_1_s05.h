void sharedFunc_800D2214_1_s05(s_SubCharacter* splithead)
{
    q19_12 newMoveSpeed0;
    q19_12 moveSpeed;

    switch (splithead->model_0.anim_4.status_0)
    {
        case 23:
            moveSpeed = splithead->moveSpeed_38;
            if (moveSpeed > Q12(0.0f))
            {
                newMoveSpeed0 = moveSpeed - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.5f), Q12_SHIFT);
                if (newMoveSpeed0 < Q12(0.0f))
                {
                    newMoveSpeed0 = Q12(0.0f);
                }
            }
            else
            {
                newMoveSpeed0 = moveSpeed + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.5f), Q12_SHIFT);
                if (newMoveSpeed0 > Q12(0.0f))
                {
                    newMoveSpeed0 = Q12(0.0f);
                }
            }
            splithead->moveSpeed_38 = newMoveSpeed0;

            if (!sharedFunc_800D4530_1_s05(splithead))
            {
                break;
            }

        case 2:
        case 3:
        case 20:
        case 21:
        case 22:
            splithead->model_0.anim_4.status_0 = ANIM_STATUS(7, false);
            Chara_MoveSpeedUpdate(splithead, Q12(1.0f));
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
            Chara_MoveSpeedUpdate(splithead, Q12(1.0f));

            if (!Savegame_EventFlagGet(EventFlag_131))
            {
                func_8005DC1C(Sfx_Unk1479, &splithead->position_18, Q8_CLAMPED(0.5f), 0);
            }

            Savegame_EventFlagSet(EventFlag_131);
            break;
    }
}
