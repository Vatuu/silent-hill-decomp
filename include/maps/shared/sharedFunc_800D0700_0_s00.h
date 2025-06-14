void sharedFunc_800D0700_0_s00(VECTOR3 *point, VECTOR3 *lineStart, VECTOR3 *lineEnd, s32 flag)
{
    VECTOR3 offset;
    VECTOR3 offset2;
    VECTOR3 lineStart2;
    VECTOR3 lineEnd2;
    
    s32 vecPToA_VX;
    s32 vecPToA_VZ;
    s32 vecPToB_VX;
    s32 vecPToB_VZ;
    s32 crossTerm1;
    s32 crossTerm2;

    // Early exit check
    if (lineStart->vx == -1)
    {
        point->vy = 1;
        return;
    }
    
    point->vx += sharedData_800E323C_0_s00.vx;
    offset.vx = point->vx;

    point->vz += sharedData_800E323C_0_s00.vz;
    offset.vz = point->vz;
    
    offset2.vx = offset.vx;

    lineStart2.vx  = lineStart->vx;
    lineEnd2.vx = lineEnd->vx;
    
    offset2.vy = offset.vz;
    
    lineStart2.vy  = lineStart->vz;
    lineEnd2.vy = lineEnd->vz;
    
    vecPToA_VX = FP_FROM(lineStart2.vx  - offset.vx, Q4_SHIFT);
    vecPToB_VX = FP_FROM(lineEnd2.vx - offset.vx, Q4_SHIFT);
    vecPToA_VZ = FP_FROM(lineStart2.vy  - offset.vz, Q4_SHIFT);
    vecPToB_VZ = FP_FROM(lineEnd2.vy - offset.vz, Q4_SHIFT);
    
    crossTerm1 = vecPToA_VX * vecPToB_VZ;
    crossTerm2 = vecPToA_VZ * vecPToB_VX;

    if (crossTerm2 < crossTerm1)
    {
        if (!flag)
        {
            if (lineStart->vx == lineEnd->vx)
            {
                if (lineStart->vx < offset.vx)
                {
                    s32 distance = offset.vx - lineStart->vx;  
                    s32 baseVX = point->vx;
                    
                    if (distance >= 0)
                    {
                        point->vx = baseVX - distance * 2;
                    }
                    else
                    {
                        distance = lineStart->vx - offset.vx;
                        point->vx = baseVX - distance * 2;
                    }
                }
                else
                {
                    s32 distance = offset.vx - lineStart->vx;  
                    s32 baseVX = point->vx;
                    
                    if (distance >= 0)
                    {
                        point->vx = baseVX + distance * 2;
                    }
                    else
                    {
                        distance = lineStart->vx - offset.vx;
                        point->vx = baseVX + distance * 2;
                    }
                }
            }
            else
            {
                if (lineStart->vz < offset.vz)
                {
                    s32 distance = offset.vz - lineStart->vz;
                    s32 baseVZ = point->vz;
                    
                    if (distance < 0)
                    {
                        distance = lineStart->vz - offset.vz;
                    }
                    point->vz = baseVZ - distance * 2;
                }
                else
                {
                    s32 distance = offset.vz - lineStart->vz;
                    s32 baseVZ = point->vz;
                    
                    if (distance >= 0)
                    {
                        point->vz = baseVZ + distance * 2;
                    }
                    else
                    {
                        distance = lineStart->vz - offset.vz;
                        point->vz = baseVZ + distance * 2;
                    }
                }
            }
        }
        point->vy = 0;
    }
    else
    {
        point->vy = 1;
    }

    point->vx -= sharedData_800E323C_0_s00.vx;
    point->vz -= sharedData_800E323C_0_s00.vz;
}
