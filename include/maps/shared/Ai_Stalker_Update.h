void Ai_Stalker_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords)
{
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        sharedData_800E3A20_0_s00 = 0x15E000;
        sharedData_800E3A24_0_s00 = 0x64000;
        sharedData_800E3A28_0_s00 = 0x3000;
        sharedData_800E3A2C_0_s00 = 0x32000;
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        sharedData_800E3A20_0_s00 = 0x15E000;
        sharedData_800E3A24_0_s00 = 0x64000;
        sharedData_800E3A28_0_s00 = 0;
        sharedData_800E3A2C_0_s00 = 0x23000;
    }
    else
    {
        sharedData_800E3A20_0_s00 = 0x258000;
        sharedData_800E3A24_0_s00 = 0xB4000;
        sharedData_800E3A28_0_s00 = 0x6000;
        sharedData_800E3A2C_0_s00 = 0x64000;
    }
    

    if (chara->model_0.state_2 == 0)
    {
        Ai_Stalker_Init(chara);
    }

    if (chara->model_0.state_2 != 1)
    {
        if (g_DeltaTime0 != 0)
        {
            sharedFunc_800D3308_0_s00(chara);
            sharedFunc_800D3B44_0_s00(chara);
            sharedFunc_800D67FC_0_s00(chara);
        }

        sharedFunc_800D6970_0_s00(chara, arg1, coords);
        sharedFunc_800D70C4_0_s00(chara);
        
        if (g_DeltaTime0 != 0)
        {
            sharedFunc_800D7BE8_0_s00(chara);
        }

        *(u16*)&chara->properties_E4.player.afkTimer_E8 &= 0xEFFF;
    }
}
