void sharedFunc_800D9774_1_s02(s_SubCharacter* creeper)
{
    #define creeperProps creeper->properties_E4.creeper

    creeper->flags_3E &= ~CharaFlag_Unk2;

    if (creeper->health_B0 == Q12(0.0f) && func_8005C7D0(creeper) != g_SysWork.targetNpcIdx_2353)
    {
        creeper->health_B0  = NO_VALUE;
        creeper->field_E1_0 = 0;
    }

    //if (creeper->moveSpeed_38 == Q12(0.0f) && !(creeper->properties_E4.creeper.flags_E8 & (CreeperFlag_3 | CreeperFlag_4))) // TODO: Doesn't match?
    if (creeper->moveSpeed_38 == Q12(0.0f) && !(creeper->properties_E4.player.afkTimer_E8 & 0xC))
    {
        creeper->properties_E4.creeper.flags_E8 |= CreeperFlag_3;
        func_80037DC4(creeper);

        if (creeper->model_0.anim_4.status_0 == ANIM_STATUS(CreeperAnim_14, true))
        {
            func_800622B8(3, creeper, ANIM_STATUS(CreeperAnim_5, false), 5);
        }
        else
        {
            func_800622B8(3, creeper, ANIM_STATUS(CreeperAnim_5, true), 5);
        }
    }

    #undef creeperProps
}
