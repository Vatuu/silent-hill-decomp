void sharedFunc_800D0690_1_s03(s32 pass, s_Particle* part, s16* rand, q19_12* deltaTime)
{
    q19_12 x = g_Particle_PrevPosition.vx - g_Particle_Position.vx;
    q19_12 z = g_Particle_PrevPosition.vz - g_Particle_Position.vz;

    part->position1_C.vy  = part->position0_0.vy - part->movement_18.vy;
    part->position0_0.vx += TIMESTEP_SCALE(*deltaTime, x);
    part->movement_18.vy += Q12(0.001f);
    part->position0_0.vy += TIMESTEP_SCALE(*deltaTime, part->movement_18.vy << 2);
    part->position1_C.vy  = part->position0_0.vy - Q12(1.0f / 32.0f);
    part->position0_0.vz += TIMESTEP_SCALE(*deltaTime, z);
    part->position1_C.vx  = part->position0_0.vx;
    part->position1_C.vz  = part->position0_0.vz;

    if ((ABS(part->position0_0.vx) + ABS(part->position0_0.vz)) > Q12(6.0f))
    {
        part->stateStep_1E = 0;
    }
}
