q19_12 sharedFunc_800CD6B0_3_s03(MATRIX* mat, s32 matCount, VECTOR3* center)
{
    s32    i;
    q19_12 posX;
    q19_12 posZ;
    q23_8  minXTemp;
    q23_8  minX;
    q23_8  maxX;
    q23_8  minZTemp;
    q23_8  minZ;
    q23_8  maxZ;
    q19_12 radius;

    maxX =
    minX =
    posX = mat->t[0];
    maxZ =
    minZ =
    posZ = mat->t[2];
    mat++;

    for (i = 1; i < matCount; i++, mat++)
    {
        posX = mat->t[0];
        posZ = mat->t[2];

        // `minX = MIN(posX, minX)`
        minXTemp = minX;
        if (minXTemp >= posX)
        {
            minXTemp = posX;
        }
        minX = minXTemp;
        maxX = MAX(posX, maxX);

        // `minZ = MIN(posZ, minZ)`
        minZTemp = minZ;
        if (minZTemp >= posZ)
        {
            minZTemp = posZ;
        }
        minZ = minZTemp;
        maxZ = MAX(posZ, maxZ);
    }

    posX      = maxX - minX;
    posX      = Q8_TO_Q12(posX);
    posZ      = maxZ - minZ;
    posZ      = Q8_TO_Q12(posZ);
    radius = SquareRoot12(Q12_SQUARE_PRECISE(posX) +
                          Q12_SQUARE_PRECISE(posZ));

    posX       = Q8_TO_Q12(minX) + (posX / 2);
    posZ       = Q8_TO_Q12(minZ) + (posZ / 2);
    center->vx = posX;
    center->vz = posZ;
    return radius / 2;
}
