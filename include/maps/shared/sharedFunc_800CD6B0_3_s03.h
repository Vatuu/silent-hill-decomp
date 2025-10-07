q19_12 sharedFunc_800CD6B0_3_s03(MATRIX* mtx, s32 mtxCount, VECTOR3* center)
{
    s32    i;
    s32    x;
    s32    z;
    s32    minXTemp;
    s32    minX;
    s32    maxX;
    s32    minZTemp;
    s32    minZ;
    s32    maxZ;
    q19_12 radius;

    maxX = minX = x = mtx->t[0];
    maxZ = minZ = z = mtx->t[2];
    mtx++;

    for (i = 1; i < mtxCount; i++, mtx++)
    {
        x = mtx->t[0];
        z = mtx->t[2];

        // `minX = MIN(x, minX)`
        minXTemp = minX;
        if (minXTemp >= x)
        {
            minXTemp = x;
        }
        minX = minXTemp;
        maxX = MAX(x, maxX);

        // `minZ = MIN(z, minZ)`
        minZTemp = minZ;
        if (minZTemp >= z)
        {
            minZTemp = z;
        }
        minZ = minZTemp;
        maxZ = MAX(z, maxZ);
    }

    x      = maxX - minX;
    x      = Q8_TO_Q12(x);
    z      = maxZ - minZ;
    z      = Q8_TO_Q12(z);
    radius = SquareRoot12(FP_SQUARE_PRECISE(x, Q12_SHIFT) + FP_SQUARE_PRECISE(z, Q12_SHIFT));

    x          = Q8_TO_Q12(minX) + (x / 2);
    z          = Q8_TO_Q12(minZ) + (z / 2);
    center->vx = x;
    center->vz = z;
    return radius / 2;
}
