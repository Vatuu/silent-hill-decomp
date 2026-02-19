void sharedFunc_800CD7F8_3_s03(s_SubCharacter* chara, q19_12 offsetX, q19_12 offsetZ, q19_12 range)
{
    q19_12 adjOffsetX;
    q19_12 adjOffsetZ;
    q19_12 adjOffsetSqr;
    q19_12 rootAdjOffsetSqr;
    q19_12 scale;
    q19_12 scaledAdjX;
    q19_12 scaledAdjZ;

    adjOffsetX = chara->field_D8.offsetX_4 - offsetX;
    adjOffsetZ = chara->field_D8.offsetZ_6 - offsetZ;

    adjOffsetSqr = Q12_SQUARE_PRECISE(adjOffsetX) +
                   Q12_SQUARE_PRECISE(adjOffsetZ);
    if (adjOffsetSqr > Q12_MULT_PRECISE(range, 4))
    {
        rootAdjOffsetSqr = SquareRoot12(adjOffsetSqr);
        scale            = FP_TO(rootAdjOffsetSqr - 128, Q12_SHIFT) / rootAdjOffsetSqr;

        scaledAdjX = scale * adjOffsetX;
        if (scaledAdjX < Q12(0.0f))
        {
            scaledAdjX += Q12_CLAMPED(1.0f);
        }
        adjOffsetX = FP_FROM(scaledAdjX, Q12_SHIFT);

        scaledAdjZ = scale * adjOffsetZ;
        if (scaledAdjZ < Q12(0.0f))
        {
            scaledAdjZ += Q12_CLAMPED(1.0f);
        }
        adjOffsetZ = FP_FROM(scaledAdjZ, Q12_SHIFT);

        offsetX += adjOffsetX;
        offsetZ += adjOffsetZ;
    }

    chara->field_D8.offsetX_4 = offsetX;
    chara->field_D8.offsetZ_6 = offsetZ;
}
