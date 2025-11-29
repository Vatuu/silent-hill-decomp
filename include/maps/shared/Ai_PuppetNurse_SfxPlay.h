void Ai_PuppetNurse_SfxPlay(s_SubCharacter* nurse, s32 idx)
{
    s_SfxPair* sfx;
    s32 index;

    sfx = g_NursePuppetSfxs;
    index = (nurse->properties_E4.puppetNurse.field_124->idx_1C * 9) + idx;
    func_8005DC1C(sfx[index].sfxId, &nurse->position_18, sfx[index].vol, 0);
}
