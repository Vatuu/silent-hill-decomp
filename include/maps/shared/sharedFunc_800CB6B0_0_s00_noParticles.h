/** Barebones version of `sharedFunc_800CB6B0_0_s00`, missing calls to `Particle_Update` and other particle-related code.
 * Used in:
 * MAP1_S04 MAP2_S01 MAP2_S03 MAP2_S04 MAP3_S02 MAP4_S00 MAP4_S06 MAP6_S05 MAP4_S01
 * Changes to this file should be reflected inside `sharedFunc_800CB6B0_0_s00.h`
 */

void sharedFunc_800CB6B0_0_s00(s32 arg1, s32 arg2, s32 arg3)
{
    s32 temp_s0;

    func_80055434(&g_ParticleVectors0.vector_0);
    g_ParticleVectors0.field_28 = func_8005545C(&g_ParticleVectors0.svec_18);

    vwGetViewPosition(&g_ParticleVectors0.viewPosition_C);
    vwGetViewAngle(&g_ParticleVectors0.viewRotation_20);

    switch (arg3)
    {
        case 0:
        case -1:
            if (arg3 == NO_VALUE)
            {
                g_SysWork.field_2349 = g_MapOverlayHeader.field_17;
                g_SysWork.field_2348 = g_MapOverlayHeader.field_17;
            }

            sharedData_800DD598_0_s00 = 0;
            g_SysWork.field_234A      = 1;
            sharedData_800DFB4C_0_s00 = arg2;

            sharedData_800E0CB8_0_s00 = FP_FROM(sharedData_800E0CB0_0_s00, Q12_SHIFT);
            sharedData_800E0CB6_0_s00 = sharedData_800E0CB0_0_s00;
            sharedData_800E0CB4_0_s00 = sharedData_800E0CB0_0_s00;

            temp_s0 = SetSp(0x1F8003D8);
            SetSp(temp_s0);
            break;

        default:
            sharedData_800DD584_0_s00 = g_DeltaTime0 == Q12(0.0f);

            sharedData_800CD77C_1_s04 = arg2;

            temp_s0 = SetSp(0x1F8003D8);
            SetSp(temp_s0);
            break;
    }

    g_ParticleVectors1 = g_ParticleVectors0;
}
