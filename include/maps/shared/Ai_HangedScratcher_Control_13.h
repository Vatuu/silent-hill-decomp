void Ai_HangedScratcher_Control_13(s_SubCharacter* scratcher)
{
    #define scratcherProps scratcher->properties_E4.hangedScratcher

    Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

    if (scratcher->health_B0 == Q12(0.0f))
    {
        if (g_SysWork.targetNpcIdx_2353 != Chara_NpcIdxGet(scratcher))
        {
            scratcher->health_B0  = NO_VALUE;
            scratcher->flags_3E  &= ~CharaFlag_Unk2;
            scratcher->field_E1_0 = 0;
            scratcherProps.flags_E8 |= HangedScratcherFlag_9;
        }
    }

    // TODO: Weird 32-bit flags access, maybe `if` is checking both `flags_E8` and `field_EA`?
    if (scratcher->moveSpeed_38 == Q12(0.0f) &&
        !(*(u32*)&scratcherProps.flags_E8 & (HangedScratcherFlag_0 | HangedScratcherFlag_2)))
    {
        func_800622B8(3, scratcher, ANIM_STATUS(HangedScratcherAnim_4, false), 8);
        scratcherProps.flags_E8 |= HangedScratcherFlag_2;
        Savegame_EnemyStateUpdate(scratcher);
    }

    #undef scratcherProps
}
