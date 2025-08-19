s32 sharedFunc_800D3630_0_s01(s_SubCharacter* chara, s32* arg1)
#ifdef SHARED_FUNC_IMPL
{
    s32 ret;
    s32 angle;
    s32 xOffset;
    s32 zOffset;
    s32 offset;

    offset = sharedFunc_800D3814_0_s01(chara);
    if (arg1 != NULL)
    {
        *arg1 = offset;
    }

    ret = sharedFunc_800D31D0_0_s01(chara, &g_SysWork.player_4C.chara_0.position_18, offset);
    if (ret != 0)
    {
        offset = MAX(offset, FP_METER(1.5));
        angle  = ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);

        xOffset = FP_MULTIPLY_PRECISE(offset, shRsin(angle), 12);
        zOffset = FP_MULTIPLY_PRECISE(offset, shRcos(angle), 12);

        chara->properties_E4.npc.field_104 = chara->position_18.vx + xOffset;
        chara->properties_E4.npc.field_108 = g_SysWork.player_4C.chara_0.position_18.vy + g_SysWork.player_4C.chara_0.field_CE;
        chara->properties_E4.npc.field_10C = chara->position_18.vz + zOffset;
    }

    return ret;
}
#else
;
#endif
