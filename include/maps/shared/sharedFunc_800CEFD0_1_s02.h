void sharedFunc_800CEFD0_1_s02(s32 arg0, s_sharedFunc_800CEFD0_1_s02* arg1, u16* arg2, s32* deltaTime)
{
    s_Collision                  coll;
    s32                          x;
    s32                          z;
    s32                          var_t0;
    s32                          var_t1;
    s_sharedFunc_800CEFD0_1_s02* var_s0;

    var_s0 = arg1;

    if (arg0 == 0)
    {
        return;
    }

    if (arg0 == 1)
    {
        var_t0 = g_ParticleVectors1.viewPosition_C.vx - g_ParticleVectors0.viewPosition_C.vx;
        var_t1 = g_ParticleVectors1.viewPosition_C.vz - g_ParticleVectors0.viewPosition_C.vz;

        var_s0->field_C.vx = var_s0->field_0.vx;
        var_s0->field_C.vz = var_s0->field_0.vz;
        var_s0->field_C.vy = var_s0->field_0.vy - var_s0->field_1A;

        // TODO: Similar to `Math_DeltaTimeDistScale`.
        var_s0->field_0.vx += TIME_STEP_SCALE(*deltaTime, sharedData_800DFB64_0_s00 + var_t0);
        var_s0->field_1A   += *(s32*)&sharedData_800E5768_1_s02; // TODO: Should be `sharedData_800E5768_1_s02.corners_0[0].vx`.
        var_s0->field_0.vy += TIME_STEP_SCALE(*deltaTime, var_s0->field_1A << 2);
        var_s0->field_0.vz += TIME_STEP_SCALE(*deltaTime, sharedData_800DFB68_0_s00 + var_t1);

        if (sharedData_800DF158_1_s02 != 0)
        {
            var_s0->field_C.vx = var_s0->field_0.vx;
            var_s0->field_C.vz = var_s0->field_0.vz;
        }

        x  = abs(var_s0->field_0.vx);
        z = var_s0->field_0.vz;

        if ((z >= 0 && (x + z) > FP_METER(6.0f)) ||
            (z <  0 && (x - z) > FP_METER(6.0f)))
        {
            if (sharedData_800DF158_1_s02 != 0)
            {
                sharedFunc_800D01BC_0_s00(arg2, &arg1->field_0, 6);

                var_s0->field_C.vx = var_s0->field_0.vx;
                var_s0->field_C.vz = var_s0->field_0.vz;
            }
            else
            {
                var_s0->field_C.vx -= var_s0->field_0.vx;
                var_s0->field_C.vz -= var_s0->field_0.vz;

                var_s0->field_0.vx = -var_s0->field_0.vx;
                var_s0->field_0.vz = -var_s0->field_0.vz;

                var_s0->field_C.vx += var_s0->field_0.vx;
                var_s0->field_C.vz += var_s0->field_0.vz;
            }
        }

        if (var_s0->field_0.vy >= 0)
        {
            PushMatrix();
            Collision_Get(&coll, var_s0->field_0.vx + sharedData_800E323C_0_s00.vx, var_s0->field_0.vz + sharedData_800E323C_0_s00.vz);
            PopMatrix();

            var_s0->field_0.vy = coll.groundHeight_0;
            var_s0->field_18   = coll.field_8;

            if (coll.field_8 == 11)
            {
                var_s0->field_1F   = 3;
                var_s0->field_C.vx = var_s0->field_0.vx;
                var_s0->field_C.vz = var_s0->field_0.vz;
                var_s0->field_C.vy = var_s0->field_0.vy - 96;
            }

            var_s0->field_1C = 0;
            var_s0->field_1A = 0;
            var_s0->field_1E++;
        }
    }
}
