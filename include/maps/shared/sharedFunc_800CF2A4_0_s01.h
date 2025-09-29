/** @brief Adds a random offset to a snow particle movement vector. Moves particle vertically, clamps Y to 0. */
void sharedFunc_800CF2A4_0_s01(s32 arg0, s_Particle* part, u16* rand, s32* deltaTime)
{
    u16      localRand;
    s16      movement;
    VECTOR3* pos;
    
    pos = &part->position0_0;

    switch (arg0)
    {
        case 0:
            // Random value has been generated in caller and `rand` argument.
            // Add random X offset.
            part->movement_18.vx += Rng_GenerateInt(*rand, -7, 7);

            // Random value for Z and Y to share and store in `rand` argument.
            *rand = (u16)Rng_Rand16();

            // Add random Z offset.
            localRand             = *rand;
            part->movement_18.vz += Rng_GenerateInt(localRand, -7, 7);

            // Add random Y offset.
            part->movement_18.vy += Rng_GenerateInt(*rand, -1, 3);

            // Apply movement to position over time.
            part->position0_0.vy += TIME_STEP_SCALE(*deltaTime, (part->movement_18.vy >> 1) << 2);
            break;

        case 1:
    #if defined(MAP0_S00)
            part->position1_C.vx = pos->vx;
            part->position1_C.vz = pos->vz;
            part->position1_C.vy = pos->vy - part->movement_18.vy;
            part->movement_18.vy += sharedData_800E32D4_0_s00;

            pos->vy += TIME_STEP_SCALE(*deltaTime, part->movement_18.vy << 2);
    #endif
            break;
    }

    // Clamp Y position at 0 and rest.
    if (pos->vy >= Q12(0.0f))
    {
        pos->vy = Q12(0.0f);
    }
}
