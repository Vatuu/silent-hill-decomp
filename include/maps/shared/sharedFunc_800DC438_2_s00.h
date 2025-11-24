s32 sharedFunc_800DC438_2_s00(s_SubCharacter* chara)
{
    // TODO: Wrong `properties_E4` union member.
    s32 result;

    result = 0;

    if (chara->model_0.anim_4.status_0 != ANIM_STATUS(17, true))
    {
        return result;
    }

    if (!(chara->properties_E4.player.flags_11C & (1 << 29)) &&
        (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 0x1) ||
         (g_SavegamePtr->gameDifficulty_260 > 0 && chara->model_0.charaId_0 != Chara_AirScreamer)))
    {
        if (sharedFunc_800DC3BC_2_s00(chara) && (sharedFunc_800DC0A8_2_s00(chara) || sharedFunc_800DBF88_2_s00(chara, Q12(2.0f)) != 0))
        {
            if (sharedFunc_800DC0E4_2_s00(chara, Q12(1.0f)) != 0)
            {
                result = 1;
            }
            else
            {
                result = 2;
            }
        }
    }
    else
    {
        result = 1;
    }
    return result;
}
