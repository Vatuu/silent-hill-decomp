bool sharedFunc_800D9188_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx, s32 sfxId)
{
    // TODO: Should probably be using `properties_E4.npc` struct instead.
    if (chara->model_0.anim_4.status_0 == animStatus)
    {
        if (chara->model_0.anim_4.keyframeIdx_8 >= keyframeIdx)
        {
            if (!(chara->properties_E4.player.flags_11C & PlayerFlag_Unk13))
            {
                switch (sfxId)
                {
#if defined(MAP6_S04)
                    case Sfx_Unk1620:
                        func_8005DC1C(sfxId, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

                    case Sfx_Unk1621:
                        func_8005DC1C(sfxId, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

                    case Sfx_Unk1622:
                    case Sfx_Unk1638:
                        func_8005DC1C(sfxId, &chara->position_18, Q8_CLAMPED(0.75f), 0);
                        break;

                    case Sfx_Unk1631:
                    case Sfx_Unk1632:
                        func_8005DC1C(sfxId, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

#elif defined(MAP3_S00) || defined(MAP5_S02) || defined(MAP5_S03)
                    case Sfx_Unk1492:
                        func_8005DC1C(sfxId, &chara->position_18, Q8_CLAMPED(1.0f), 2);
                        break;

                    case Sfx_Unk1594:
                        func_8005DC1C(sfxId, &chara->position_18, Q8_CLAMPED(0.5f), 0);
                        break;

#elif defined(MAP3_S04) || defined(MAP4_S04) || defined(MAP7_S00)
                    case Sfx_Unk1639:
                        func_8005DC1C(sfxId, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

#elif defined(MAP0_S01) || defined(MAP4_S01)
                    case Sfx_Unk1368:
                    case Sfx_Unk1369:
                    case Sfx_Unk1370:
                        func_8005DC1C(sfxId, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

#elif defined(MAP2_S01) || defined(MAP3_S06)
                    case Sfx_Unk1488:
                    case Sfx_Unk1496:
                        func_8005DC1C(sfxId, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

#elif defined(MAP6_S01)
                    // TODO: This is made of two blocks above, maybe can be merged somehow.
                    case Sfx_Unk1488:
                    case Sfx_Unk1496:
                        func_8005DC1C(sfxId, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

                    case Sfx_Unk1368:
                    case Sfx_Unk1369:
                    case Sfx_Unk1370:
                        func_8005DC1C(sfxId, &chara->position_18, Q8_CLAMPED(0.25f), 0);
                        break;

#elif defined(MAP7_S03)
                    case Sfx_Unk1539:
                    case Sfx_Unk1674:
                    case Sfx_Unk1675:
                        func_8005DC1C(sfxId, &chara->position_18, Q8_CLAMPED(0.125f), 0);
                        break;

                    case Sfx_Unk1622:
                        func_8005DC1C(sfxId, &chara->position_18, Q8_CLAMPED(0.75f), 0);
                        break;

#endif
                    default:
                        func_8005DC1C(sfxId, &chara->position_18, Q8_CLAMPED(0.5f), 0);
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
