void Ai_PuppetNurse_SfxPlay(s_SubCharacter* nurse, s32 idx)
{
    s32        idx0;
    s_SfxPair* sfxPair;

    #define nurseProps nurse->properties_E4.puppetNurse

    sfxPair = g_NursePuppetSfxs;
    idx0    = (nurseProps.field_124->idx_1C * 9) + idx;
    func_8005DC1C(sfxPair[idx0].sfxId, &nurse->position_18, sfxPair[idx0].vol, 0);

    #undef nurseProps
}
