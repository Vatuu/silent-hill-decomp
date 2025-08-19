void sharedFunc_800CFFF8_0_s00(s32 arg0, s_func_800CFFF8* arg1)
#ifdef SHARED_FUNC_IMPL
{
    s32 absX;
    s32 threshold;

    arg1->field_0.vx += sharedData_800E324C_0_s00.vx - sharedData_800E323C_0_s00.vx;
    arg1->field_0.vz += sharedData_800E324C_0_s00.vz - sharedData_800E323C_0_s00.vz;

    if (arg0 == 0 && sharedData_800E0CAC_0_s00 == 3)
    {
        arg1->field_0.vx += FP_FROM(sharedData_800DFB64_0_s00, Q4_SHIFT);
        arg1->field_0.vz += FP_FROM(sharedData_800DFB68_0_s00, Q4_SHIFT);
    }

    if (sharedData_800DD591_0_s00 != 0)
    {
        return;
    }

    absX = abs(arg1->field_0.vx);

    // This helps match the original code: `threshold = threshold = ...` 
    threshold = threshold = FP_TO(arg0 + 5, Q12_SHIFT);

    // Also matches:
    // threshold = FP_TO(arg0 + 5, Q12_SHIFT);
    // threshold = threshold += 0;
    
    if (ABS_ADD(arg1->field_0.vz, absX) > threshold)
    {
        arg1->field_1E = 0;
    }
    
    if (arg1->field_1F == 3 || arg1->field_1F == 0xF3)
    {
        arg1->field_C.vx = arg1->field_0.vx;
        arg1->field_C.vz = arg1->field_0.vz;
    }
}
#else
;
#endif
