s32 Ai_PuppetNurse_AnimSfxGet(s32 animFrame)
{
    u8 sfxOffsets[4];
    u8 index;
    // @note we memcpy a rodata table... strange
    memcpy(sfxOffsets, g_NursePuppet_SfxOffsets, 4);
    index = g_NursePuppet_AnimSfxs[animFrame];
    return sfxOffsets[index];
}
