s32 Ai_PuppetNurse_AnimSfxGet(s32 animFrame)
{
    u8 idx;
    u8 sfxOffsets[4] = { 9, 6, 7, 8 };

    idx = g_NursePuppet_AnimSfxs[animFrame];
    return sfxOffsets[idx];
}
