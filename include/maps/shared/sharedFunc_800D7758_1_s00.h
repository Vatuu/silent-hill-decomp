
u8 sharedFunc_800D7758_1_s00(s32 arg0, s32 arg1)
#ifdef SHARED_FUNC_IMPL
{
    s32 unk1 = 0xFFFB0000;
    s32 unk2 = 0x13FFFFU;

    if ((u32) (arg0 + 0xA0000) > unk2 || arg1 < unk1 || arg1 > 0xC7FFF)
    {
        return 0U;
    }

    arg1 = (arg1 + 0x50000) / 163840;
    arg0 = (arg0 + 0xA0000) / 163840;
    return sharedData_800DCC14_1_s00[(arg0 * 7) + arg1];
}
#else
;
#endif
