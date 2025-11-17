void sharedFunc_800CEFD0_1_s02(s32 arg0, s_sharedFunc_800CEFD0_1_s02* arg1, u16* arg2, s32* deltaTime)
{
    s_Collision                  coll;
    s32                          var_t0;
    s32                          var_t1;
    s_sharedFunc_800CEFD0_1_s02* var_s0;

    var_s0 = arg1;

#if defined(MAP5_S00) || defined(MAP6_S03)
    var_t0 = (g_Particle_PrevPosition.vx - g_Particle_Position.vx);
    var_t1 = (g_Particle_PrevPosition.vz - g_Particle_Position.vz);
#endif

    switch (arg0)
    {
        case 0:
            break;
        case 1:
#if !defined(MAP5_S00) && !defined(MAP6_S03)
            var_t0 = g_ParticleVectors1.viewPosition_C.vx - g_ParticleVectors0.viewPosition_C.vx;
            var_t1 = g_ParticleVectors1.viewPosition_C.vz - g_ParticleVectors0.viewPosition_C.vz;

            var_s0->field_C.vx = var_s0->field_0.vx;
            var_s0->field_C.vz = var_s0->field_0.vz;
            var_s0->field_C.vy = var_s0->field_0.vy - var_s0->field_1A;
#endif

            // TODO: Similar to `Math_DeltaTimeDistScale`.
            var_s0->field_0.vx += TIMESTEP_SCALE(*deltaTime, g_Particle_SpeedX + var_t0);
            var_s0->field_1A   += *(s32*)&sharedData_800E32D4_0_s00; // TODO: Should field be changed to `s32`?
            var_s0->field_0.vy += TIMESTEP_SCALE(*deltaTime, var_s0->field_1A << 2);
#if defined(MAP5_S00) || defined(MAP6_S03)
            var_s0->field_C.vy = var_s0->field_0.vy - Q12(0.125f);
#endif
            var_s0->field_0.vz += TIMESTEP_SCALE(*deltaTime, g_Particle_SpeedZ + var_t1);

#if defined(MAP5_S00) || defined(MAP6_S03)
            var_s0->field_C.vx = var_s0->field_0.vx;
            var_s0->field_C.vz = var_s0->field_0.vz;
#endif

            if (sharedData_800DF158_1_s02 != 0)
            {
                var_s0->field_C.vx = var_s0->field_0.vx;
                var_s0->field_C.vz = var_s0->field_0.vz;
            }

            if ((ABS(var_s0->field_0.vx) + ABS(var_s0->field_0.vz)) > Q12(6.0f))
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
                Collision_Get(&coll, var_s0->field_0.vx + g_Particle_Position.vx, var_s0->field_0.vz + g_Particle_Position.vz);
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
            break;
    }
}
