s32 Ai_PuppetNurse_AnimSfxGet(s32 animFrame)
{
    u8 sfxOffsets[4];
    u8 idx;

    // @note `memcpy` a rodata table. Strange.
    memcpy(sfxOffsets, g_NursePuppet_SfxOffsets, 4);
    idx = g_NursePuppet_AnimSfxs[animFrame];
    return sfxOffsets[idx];
}
