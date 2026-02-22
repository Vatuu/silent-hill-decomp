void sharedFunc_800CD7F8_3_s03(s_SubCharacter* chara, q19_12 offsetX, q19_12 offsetZ, q19_12 range)
{
    q19_12 extraOffsetX;
    q19_12 extraOffsetZ;
    q19_12 extraDistSqr;
    q19_12 rootAdjOffsetSqr;
    q19_12 scale;
    q19_12 scaledExtraOffsetX;
    q19_12 scaledExtraOffsetZ;

    // Compute extra offset.
    extraOffsetX = chara->field_D8.offsetX_4 - offsetX;
    extraOffsetZ = chara->field_D8.offsetZ_6 - offsetZ;

    // Apply extra offset if its distance exceeds a threshold.
    extraDistSqr = Q12_SQUARE_PRECISE(extraOffsetX) +
                   Q12_SQUARE_PRECISE(extraOffsetZ);
    if (extraDistSqr > Q12_MULT_PRECISE(range, 4))
    {
        // Compute scale.
        rootAdjOffsetSqr = SquareRoot12(extraDistSqr);
        scale            = Q12(rootAdjOffsetSqr - 128) / rootAdjOffsetSqr;

        // Adjust extra X offset.
        scaledExtraOffsetX = scale * extraOffsetX;
        if (scaledExtraOffsetX < Q12(0.0f))
        {
            scaledExtraOffsetX += Q12_CLAMPED(1.0f);
        }
        extraOffsetX = FP_FROM(scaledExtraOffsetX, Q12_SHIFT);

        // Adjust extra Z offset.
        scaledExtraOffsetZ = scale * extraOffsetZ;
        if (scaledExtraOffsetZ < Q12(0.0f))
        {
            scaledExtraOffsetZ += Q12_CLAMPED(1.0f);
        }
        extraOffsetZ = FP_FROM(scaledExtraOffsetZ, Q12_SHIFT);

        // Apply extra offset.
        offsetX += extraOffsetX;
        offsetZ += extraOffsetZ;
    }

    // Set translation offset.
    chara->field_D8.offsetX_4 = offsetX;
    chara->field_D8.offsetZ_6 = offsetZ;
}
