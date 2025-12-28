s32 sharedFunc_800D4A80_0_s01(s_SubCharacter* airScreamer)
{
    s32 flags;
    s32 result;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    flags = airScreamerProps.flags_11C;
    result = 0;
    if (sharedData_800E21D0_0_s01.flags_0 >= 0 && airScreamer->health_B0 >= Q12(0.0f))
    {
        result = 4;
        if (!(flags & PlayerFlag_Unk17))
        {
            result = 1;
            if (!(flags & PlayerFlag_Unk18))
            {
                result = 2;
                if (!(flags & PlayerFlag_Unk19))
                {
                    result = NO_VALUE;
                    if (flags & PlayerFlag_Unk20)
                    {
                        result = 3;
                    }
                }
            }
        }
    }

    return result;

    #undef airScreamerProps
}

