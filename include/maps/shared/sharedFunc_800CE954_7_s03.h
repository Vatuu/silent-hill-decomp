void sharedFunc_800CE954_7_s03(s32 pass, s_Particle* part, s16* rand, q19_12* deltaTime)
{
#if defined(MAP7_S03)
    q19_12      deltaX;
    q19_12      deltaZ;
    s_Particle* ptr;

    ptr = part;
    
    deltaX = g_Particle_PrevPosition.vx - g_Particle_Position.vx;
    deltaZ = g_Particle_PrevPosition.vz - g_Particle_Position.vz;

    if (pass == 0)
    {
        part->position0_0.vx += deltaX;
        part->position0_0.vz += deltaZ - ((*deltaTime) * 2);

        if ((ABS(part->position0_0.vx) + ABS(part->position0_0.vz)) > Q12(8.0))
        {
            if (sharedData_800DF158_1_s02 != 0)
            {
                sharedFunc_800D01BC_0_s00(rand, &part->position0_0, 8);
            }
            else
            {
                ptr->position0_0.vx = -ptr->position0_0.vx;
                ptr->position0_0.vz = -ptr->position0_0.vz;
            }

            ptr->type_1F += 0xF0;
        }
    }
#endif
}
