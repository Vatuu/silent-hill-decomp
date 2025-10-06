void sharedFunc_800CD7F8_3_s03(s_SubCharacter* chara, q19_12 posX, q19_12 posZ, q19_12 range)
{
    s32 deltaX;
    s32 deltaZ;
    s32 sqrDelta;
    s32 sqrRootDelta;
    s32 scale;
    s32 scaledDeltaX;
    s32 scaledDeltaZ;

    deltaX = chara->field_D8.offsetX_4 - posX;
    deltaZ = chara->field_D8.offsetZ_6 - posZ;

    sqrDelta = FP_SQUARE_PRECISE(deltaX, Q12_SHIFT) + FP_SQUARE_PRECISE(deltaZ, Q12_SHIFT);
    if (sqrDelta > FP_MULTIPLY_PRECISE(range, 4, Q12_SHIFT))
    {
        sqrRootDelta = SquareRoot12(sqrDelta);
        scale        = FP_TO(sqrRootDelta - 128, Q12_SHIFT) / sqrRootDelta;

        scaledDeltaX = scale * deltaX;
        if (scaledDeltaX < 0)
        {
            scaledDeltaX += 0xFFF;
        }
        deltaX = FP_FROM(scaledDeltaX, Q12_SHIFT);

        scaledDeltaZ = scale * deltaZ;
        if (scaledDeltaZ < 0)
        {
            scaledDeltaZ += 0xFFF;
        }
        deltaZ = FP_FROM(scaledDeltaZ, Q12_SHIFT);

        posX += deltaX;
        posZ += deltaZ;
    }

    chara->field_D8.offsetX_4 = posX;
    chara->field_D8.offsetZ_6 = posZ;
}
