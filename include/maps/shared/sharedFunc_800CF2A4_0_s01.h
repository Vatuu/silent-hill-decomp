/** @brief Adds a random offset to a snow particle movement vector. Moves particle vertically, clamps Y to 0. */
void sharedFunc_800CF2A4_0_s01(s32 arg0, s_Particle* part, u16* rand, s32* deltaTime)
{
    u16      localRand;
    VECTOR3* pos;
    
    pos= &part->position1_0;

    if (arg0 == 0)
    {
        // Random value has been generated in caller and `rand` argument.
        // Add random X offset in range [-7, 7].
        part->movement_18.vx += (s32)(*rand % 15) - 7;

        // Random value for Z and Y to share and store in `rand` argument.
        *rand = (u16)Rng_Rand16();

        // Add random Z offset in range [-7, 7].
        localRand             = *rand;
        part->movement_18.vz += (s32)(localRand % 15) - 7;

        // Add random Y offset in range [-1, 3].
        part->movement_18.vy += (s32)(*rand % 5) - 1;

        // Apply movement to position over time.
        part->position1_0.vy += ((((part->movement_18.vy >> 1) << 2) * *deltaTime) / 136);
    }

    // Clamp Y position at 0 and rest.
    if (pos->vy >= 0)
    {
        pos->vy = 0;
    }

    // Needed for match.
    if (pos->vy >= 0) {}
}
