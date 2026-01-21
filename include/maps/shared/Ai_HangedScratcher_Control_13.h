void Ai_HangedScratcher_Control_13(s_SubCharacter* scratcher)
{
    Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

    if (scratcher->health_B0 == Q12(0.0f))
    {
        if (g_SysWork.targetNpcIdx_2353 != Chara_NpcIdxGet(scratcher))
        {
            scratcher->health_B0  = NO_VALUE;
            scratcher->flags_3E  &= ~CharaFlag_Unk2;
            scratcher->field_E1_0 = 0;
            scratcher->properties_E4.hangedScratcher.flags_E8 |= (1 << 9);
        }
    }

    // TODO: Weird 32-bit flags access, maybe `if` is checking both `flags_E8` and `field_EA`?
    if (scratcher->moveSpeed_38 == 0 && !(*(u32*)&scratcher->properties_E4.hangedScratcher.flags_E8 & 5))
    {
        func_800622B8(3, scratcher, ANIM_STATUS(4, false), 8);
        scratcher->properties_E4.hangedScratcher.flags_E8 |= (1 << 2);
        Savegame_EnemyStateUpdate(scratcher);
    }
}
