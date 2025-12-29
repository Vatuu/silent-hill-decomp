void Ai_Stalker_Update(s_SubCharacter* stalker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    #define stalkerProps stalker->properties_E4.stalker

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        sharedData_800E3A20_0_s00 = Q12(350.0f);
        sharedData_800E3A24_0_s00 = Q12(100.0f);
        sharedData_800E3A28_0_s00 = Q12(3.0f);
        sharedData_800E3A2C_0_s00 = Q12(50.0f);
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        sharedData_800E3A20_0_s00 = Q12(350.0f);
        sharedData_800E3A24_0_s00 = Q12(100.0f);
        sharedData_800E3A28_0_s00 = Q12(0.0f);
        sharedData_800E3A2C_0_s00 = Q12(35.0f);
    }
    else
    {
        sharedData_800E3A20_0_s00 = Q12(600.0f);
        sharedData_800E3A24_0_s00 = Q12(180.0f);
        sharedData_800E3A28_0_s00 = Q12(6.0f);
        sharedData_800E3A2C_0_s00 = Q12(100.0f);
    }
    
    // Initialize.
    if (stalker->model_0.controlState_2 == StalkerControl_None)
    {
        Ai_Stalker_Init(stalker);
    }

    if (stalker->model_0.controlState_2 != StalkerControl_1)
    {
        if (g_DeltaTime0 != Q12(0.0f))
        {
            sharedFunc_800D3308_0_s00(stalker);
            sharedFunc_800D3B44_0_s00(stalker);
            sharedFunc_800D67FC_0_s00(stalker);
        }

        sharedFunc_800D6970_0_s00(stalker, anmHdr, coords);
        sharedFunc_800D70C4_0_s00(stalker);
        
        if (g_DeltaTime0 != Q12(0.0f))
        {
            sharedFunc_800D7BE8_0_s00(stalker);
        }

        stalkerProps.flags_E8 &= ~StalkerFlag_WarpRotation;
    }

    #undef stalkerProps
}
