void sharedFunc_800CD7F8_3_s03(s_SubCharacter* chara, q19_12 posX, q19_12 posZ, q19_12 range)
{
    q19_12 deltaX;
    q19_12 deltaZ;
    q19_12 deltaSqr;
    q19_12 rootDeltaSqr;
    q19_12 scale;
    q19_12 scaledDeltaX;
    q19_12 scaledDeltaZ;

    deltaX = chara->field_D8.offsetX_4 - posX;
    deltaZ = chara->field_D8.offsetZ_6 - posZ;

    deltaSqr = FP_SQUARE_PRECISE(deltaX, Q12_SHIFT) + FP_SQUARE_PRECISE(deltaZ, Q12_SHIFT);
    if (deltaSqr > FP_MULTIPLY_PRECISE(range, 4, Q12_SHIFT))
    {
        rootDeltaSqr = SquareRoot12(deltaSqr);
        scale        = FP_TO(rootDeltaSqr - 128, Q12_SHIFT) / rootDeltaSqr;

        scaledDeltaX = scale * deltaX;
        if (scaledDeltaX < Q12(0.0f))
        {
            scaledDeltaX += Q12_CLAMPED(1.0f);
        }
        deltaX = FP_FROM(scaledDeltaX, Q12_SHIFT);

        scaledDeltaZ = scale * deltaZ;
        if (scaledDeltaZ < Q12(0.0f))
        {
            scaledDeltaZ += Q12_CLAMPED(1.0f);
        }
        deltaZ = FP_FROM(scaledDeltaZ, Q12_SHIFT);

        posX += deltaX;
        posZ += deltaZ;
    }

    chara->field_D8.offsetX_4 = posX;
    chara->field_D8.offsetZ_6 = posZ;
}
