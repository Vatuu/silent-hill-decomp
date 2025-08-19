void sharedFunc_800D0700_0_s00(VECTOR3* point, VECTOR3* lineStart, VECTOR3* lineEnd, s32 flag)
#ifdef SHARED_FUNC_IMPL
{
    VECTOR3 offset0;
    VECTOR3 offset1;
    VECTOR3 lineStartCpy;
    VECTOR3 lineEndCpy;

    s32 vecPToA_X;
    s32 vecPToA_Z;
    s32 vecPToB_X;
    s32 vecPToB_Z;
    s32 crossTerm1;
    s32 crossTerm2;

    // Early exit check.
    if (lineStart->vx == NO_VALUE)
    {
        point->vy = 1;
        return;
    }
    
    point->vx += sharedData_800E323C_0_s00.vx;
    offset0.vx = point->vx;

    point->vz += sharedData_800E323C_0_s00.vz;
    offset0.vz = point->vz;
    
    offset1.vx = offset0.vx;

    lineStartCpy.vx = lineStart->vx;
    lineEndCpy.vx   = lineEnd->vx;
    
    offset1.vy = offset0.vz;

    lineStartCpy.vy = lineStart->vz;
    lineEndCpy.vy   = lineEnd->vz;
    
    vecPToA_X = FP_FROM(lineStartCpy.vx - offset0.vx, Q4_SHIFT);
    vecPToB_X = FP_FROM(lineEndCpy.vx   - offset0.vx, Q4_SHIFT);
    vecPToA_Z = FP_FROM(lineStartCpy.vy - offset0.vz, Q4_SHIFT);
    vecPToB_Z = FP_FROM(lineEndCpy.vy   - offset0.vz, Q4_SHIFT);

    crossTerm1 = vecPToA_X * vecPToB_Z;
    crossTerm2 = vecPToA_Z * vecPToB_X;

    if (crossTerm2 < crossTerm1)
    {
        if (!flag)
        {
            if (lineStart->vx == lineEnd->vx)
            {
                if (lineStart->vx < offset0.vx)
                {
                    s32 dist  = offset0.vx - lineStart->vx;  
                    s32 baseX = point->vx;

                    if (dist >= 0)
                    {
                        point->vx = baseX - (dist * 2);
                    }
                    else
                    {
                        dist      = lineStart->vx - offset0.vx;
                        point->vx = baseX - (dist * 2);
                    }
                }
                else
                {
                    s32 dist  = offset0.vx - lineStart->vx;  
                    s32 baseX = point->vx;

                    if (dist >= 0)
                    {
                        point->vx = baseX + (dist * 2);
                    }
                    else
                    {
                        dist      = lineStart->vx - offset0.vx;
                        point->vx = baseX + (dist * 2);
                    }
                }
            }
            else
            {
                if (lineStart->vz < offset0.vz)
                {
                    s32 dist  = offset0.vz - lineStart->vz;
                    s32 baseZ = point->vz;

                    if (dist < 0)
                    {
                        dist = lineStart->vz - offset0.vz;
                    }
                    point->vz = baseZ - (dist * 2);
                }
                else
                {
                    s32 dist  = offset0.vz - lineStart->vz;
                    s32 baseZ = point->vz;

                    if (dist >= 0)
                    {
                        point->vz = baseZ + (dist * 2);
                    }
                    else
                    {
                        dist      = lineStart->vz - offset0.vz;
                        point->vz = baseZ + (dist * 2);
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
#else
;
#endif
