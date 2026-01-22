void sharedFunc_800D2844_5_s00(s_SubCharacter* scratcher, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;
    s32         newAnimDuration;

#define curAnimInfo (HANGED_SCRATCHER_ANIM_INFOS[scratcher->model_0.anim_4.status_0])

    scratcher->rotation_24.vy = func_8005BF38(scratcher->rotation_24.vy);
    switch (scratcher->model_0.anim_4.status_0)
    {
        case 9:
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
            {
                curAnimInfo.duration_8.constant = Q12(19.5f);
            }
            else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
            {
                curAnimInfo.duration_8.constant = Q12(19.5f);
            }
            else
            {
                curAnimInfo.duration_8.constant = Q12(26.0f);
            }
            break;

        case 10:
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
            {
                curAnimInfo.duration_8.constant = Q12(12.0f);
            }
            else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
            {
                curAnimInfo.duration_8.constant = Q12(8.0f);
            }
            else
            {
                curAnimInfo.duration_8.constant = Q12(18.0f);
            }
            break;

        case 11:
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
            {
                curAnimInfo.duration_8.constant = Q12(23.0f);
            }
            else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
            {
                curAnimInfo.duration_8.constant = Q12(15.0f);
            }
            else
            {
                curAnimInfo.duration_8.constant = Q12(34.0f);
            }
            break;

        case 19:
            if (FP_FROM(scratcher->model_0.anim_4.time_4, Q12_SHIFT) != 173)
            {
                curAnimInfo.duration_8.constant = Q12(12.0f);
                break;
            }
            curAnimInfo.duration_8.constant = Q12(4.5f);
            break;

        case 47:
            if (FP_FROM(scratcher->model_0.anim_4.time_4, Q12_SHIFT) == 173)
            {
                curAnimInfo.duration_8.constant = Q12(3.0f);
            }
            else
            {
                curAnimInfo.duration_8.constant = Q12(9.0f);
            }
            break;

        case 23:
            if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 192, 193))
            {
                curAnimInfo.duration_8.constant = Q12(2.5f);
            }
            else
            {
                curAnimInfo.duration_8.constant = Q12(4.5f);
            }
            break;

        case 21:
        case 33:
            curAnimInfo.duration_8.constant = sharedData_800DE28C_5_s00;
            break;

        case 29:
        case 31:
            switch (scratcher->model_0.controlState_2)
            {
                case 1:
                    curAnimInfo.duration_8.constant = Q12(1.2f);
                    break;

                case 5:
                    curAnimInfo.duration_8.constant = Q12(2.4f);
                    break;

                default:
                    curAnimInfo.duration_8.constant = Q12(3.5f);
                    break;
            }
            break;

        case 35:
            curAnimInfo.duration_8.constant = MAX(Q12(2.0f), Q12_MULT_PRECISE(scratcher->moveSpeed_38, Q12(4.4f)));
            break;

        case 37:
            newAnimDuration = Q12_MULT_PRECISE(scratcher->moveSpeed_38, Q12(6.0f));
            if (scratcher->rotation_24.vy != scratcher->properties_E4.hangedScratcher.field_FC)
            {
                newAnimDuration = MAX(Q12(9.0f), newAnimDuration);
            }
            curAnimInfo.duration_8.constant = newAnimDuration;
            break;
    }

    Math_MatrixTransform(&scratcher->position_18, &scratcher->rotation_24, coords);

    animInfo = &curAnimInfo;
    animInfo->updateFunc_0(&scratcher->model_0, anmHdr, coords, animInfo);

    scratcher->properties_E4.hangedScratcher.field_FC = scratcher->rotation_24.vy;

#undef curAnimInfo
}
