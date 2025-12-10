void sharedFunc_800D3DFC_0_s01(s_SubCharacter* chara)
{
    s32 angle; // Maybe not angle.
    s32 flags;

    if (chara->field_40 < 32)
    {
        flags = g_MapOverlayHeader.charaSpawns_24C[0][chara->field_40].data.spawnInfo.flags_6;
        switch (flags)
        {
            case 1:
            case 8:
            case 9:
                angle = FP_ANGLE(0.0f);
                break;

            case 10:
                angle = FP_ANGLE(360.0f);
                break;

            case 2:
            case 3:
                angle = FP_ANGLE(108.0f);
                break;

            default:
                angle = FP_ANGLE(252.0f);
                break;
        }

        if (Rng_RandQ12() >= angle)
        {
            func_80037DC4(chara);
        }
    }
}
