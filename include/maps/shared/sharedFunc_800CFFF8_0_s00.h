// TODO: Change `s_func_800CFFF8` to `s_Particle`.

void sharedFunc_800CFFF8_0_s00(s32 pass, s_func_800CFFF8* part, s16* rand)
{
    s32 absX;
    s32 threshold;

#if defined(MAP7_S03)
    #define PASS_ADD 8
#elif defined(MAP1_S06)
    #define PASS_ADD 6
#else
    #define PASS_ADD 5
#endif

    #if !defined(MAP1_S03) && !defined(MAP1_S02) && !defined(MAP4_S04) && \
        !defined(MAP4_S02) && !defined(MAP4_S05) && !defined(MAP4_S03) && \
        !defined(MAP5_S00) && !defined(MAP6_S03)
        #define CODE_BLOCK1
    #endif

    #if !defined(MAP7_S03) && !defined(MAP1_S03) && !defined(MAP1_S00) && \
        !defined(MAP1_S02) && !defined(MAP4_S04) && !defined(MAP4_S05) && \
        !defined(MAP5_S00) && !defined(MAP6_S00) && !defined(MAP6_S03)
        #define CODE_BLOCK2
    #endif

    part->field_0.vx += g_Particle_PrevPosition.vx - g_Particle_Position.vx;
    part->field_0.vz += g_Particle_PrevPosition.vz - g_Particle_Position.vz;
#if defined(MAP7_S03)
    part->field_0.vz += ((g_Particle_PrevPosition.vz - g_Particle_Position.vz) - D_800F23D0);
#endif

#if defined(CODE_BLOCK1)
    if (pass == 0 && sharedData_800E0CAC_0_s00 == 3)
    {
        part->field_0.vx += FP_FROM(g_Particle_SpeedX, Q4_SHIFT);
        part->field_0.vz += FP_FROM(g_Particle_SpeedZ, Q4_SHIFT);
    }
#endif

#if defined(CODE_BLOCK2)
    if (sharedData_800DD591_0_s00 != 0)
    {
        return;
    }
#endif

    absX = abs(part->field_0.vx);

    // This helps match the original code: `threshold = threshold = ...` 
    threshold = threshold = FP_TO(pass + PASS_ADD, Q12_SHIFT);

    // Also matches:
    // threshold = FP_TO(pass + 5, Q12_SHIFT);
    // threshold = threshold += 0;
    
    if (ABS_ADD(part->field_0.vz, absX) > threshold)
    {
        part->field_1E = 0;
    }
    
    if (part->field_1F == 3 || part->field_1F == 0xF3)
    {
        part->field_C.vx = part->field_0.vx;
        part->field_C.vz = part->field_0.vz;
    }
    #undef CODE_BLOCK1
    #undef CODE_BLOCK2
}
