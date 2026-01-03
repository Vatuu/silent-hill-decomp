bool sharedFunc_800CF90C_3_s03(s_SubCharacter* nurse)
{
    s_SubCharacter* curNpc;
    s32             i;

    // Run through NPCs.
    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
    {
        if ((g_SysWork.npcs_1A0[i].model_0.charaId_0 == Chara_PuppetNurse || g_SysWork.npcs_1A0[i].model_0.charaId_0 == Chara_PuppetDoctor) &&
            g_SysWork.npcs_1A0[i].health_B0 > Q12(0.0f) &&
            g_SysWork.npcs_1A0[i].field_40 != nurse->field_40 &&
            !Math_Distance2dCheck(&nurse->position_18, &g_SysWork.npcs_1A0[i].position_18, Q12(4.0f)))
        {
            curNpc = g_SysWork.npcs_1A0;

            if (!(curNpc[i].flags_3E & CharaFlag_Unk2))
            {
                return true;
            }
        }
    }

    return false;
}
