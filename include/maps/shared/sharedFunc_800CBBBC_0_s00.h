bool sharedFunc_800CBBBC_0_s00()
{
    q19_12 dist;
    q19_12 rotY;

    dist = SquareRoot0(SQUARE(ABS_DIFF(g_Particle_Position.vx, g_Particle_PrevPosition.vx)) +
                       SQUARE(ABS_DIFF(g_Particle_Position.vz, g_Particle_PrevPosition.vz)));
    rotY = ABS_DIFF(g_Particle_PrevRotationY, g_Particle_RotationY);
    if (dist > 10000 || rotY > FP_ANGLE(45.0f))
    {
        return true;
    }

    return false;
}
