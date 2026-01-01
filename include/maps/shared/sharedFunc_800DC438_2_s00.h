s32 sharedFunc_800DC438_2_s00(s_SubCharacter* airScreamer)
{
    s32 stateStep;

    #define airScreamerProps airScreamer->properties_E4.player

    stateStep = AirScreamerStateStep_0;
    if (airScreamer->model_0.anim_4.status_0 != ANIM_STATUS(AirScreamerAnim_17, true))
    {
        return stateStep;
    }

    if (!(airScreamerProps.flags_11C & AirScreamerFlag_29) &&
        (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)) ||
         (g_SavegamePtr->gameDifficulty_260 > GameDifficulty_Normal && airScreamer->model_0.charaId_0 != Chara_AirScreamer)))
    {
        if (sharedFunc_800DC3BC_2_s00(airScreamer) && (sharedFunc_800DC0A8_2_s00(airScreamer) || sharedFunc_800DBF88_2_s00(airScreamer, Q12(2.0f))))
        {
            if (sharedFunc_800DC0E4_2_s00(airScreamer, Q12(1.0f)))
            {
                stateStep = AirScreamerStateStep_1;
            }
            else
            {
                stateStep = AirScreamerStateStep_2;
            }
        }
    }
    else
    {
        stateStep = AirScreamerStateStep_1;
    }

    return stateStep;

    #undef airScreamerProps
}
