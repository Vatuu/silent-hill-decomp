void Ai_Creeper_Update(s_SubCharacter* creeper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    // Initialize.
    if (creeper->model_0.state_2 == CreeperControl_None)
    {
        Ai_Creeper_Init(creeper);
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        sharedFunc_800D7EE8_1_s02(creeper);
        sharedFunc_800D8244_1_s02(creeper);
        sharedFunc_800D983C_1_s02(creeper);
    }

    sharedFunc_800D9960_1_s02(creeper, anmHdr, coords);
    sharedFunc_800D99D0_1_s02(creeper);
}
