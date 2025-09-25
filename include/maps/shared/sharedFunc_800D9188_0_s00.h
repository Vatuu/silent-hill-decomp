bool sharedFunc_800D9188_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx, s32 sfx)
{
    // TODO: Should probably be using `properties_E4.npc` struct instead.
    if (chara->model_0.anim_4.status_0 == animStatus)
    {
        if (chara->model_0.anim_4.keyframeIdx_8 >= keyframeIdx)
        {
            if (!(chara->properties_E4.player.flags_11C & PlayerFlag_Unk13))
            {
                switch (sfx)
                {
#if defined(MAP6_S04)
                    case 0x654:
                        func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

                    case 0x655:
                        func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

                    case 0x656:
                    case 0x666:
                        func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.75f), 0);
                        break;

                    case 0x65F:
                    case 0x660:
                        func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

#elif defined(MAP3_S00) || defined(MAP5_S02) || defined(MAP5_S03)
                    case 0x5D4:
                        func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(1.0f), 2);
                        break;

                    case 0x63A:
                        func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.5f), 0);
                        break;

#elif defined(MAP3_S04) || defined(MAP4_S04) || defined(MAP7_S00)
                    case 0x667:
                        func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

#elif defined(MAP0_S01) || defined(MAP4_S01)
                    case 0x558:
                    case 0x559:
                    case 0x55A:
                        func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

#elif defined(MAP2_S01) || defined(MAP3_S06)
                    case 0x5D0:
                    case 0x5D8:
                        func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

#elif defined(MAP6_S01)
                    // TODO: This is made of two blocks above, maybe can be merged somehow.
                    case 0x5D0:
                    case 0x5D8:
                        func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

                    case 0x558:
                    case 0x559:
                    case 0x55A:
                        func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

#elif defined(MAP7_S03)
                    case 0x603:
                    case 0x68A:
                    case 0x68B:
                        func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.125f), 0);
                        break;

                    case 0x656:
                        func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.75f), 0);
                        break;

#endif
                    default:
                        func_8005DC1C(sfx, &chara->position_18, Q8_CLAMPED(0.5f), 0);
                        break;
                }

                chara->properties_E4.player.flags_11C |= PlayerFlag_Unk13;
                return true;
            }
        }
        else
        {
            chara->properties_E4.player.flags_11C &= ~PlayerFlag_Unk13;
        }
    }

    return false;
}
