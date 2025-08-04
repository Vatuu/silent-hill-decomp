/** @brief Adds a random offset to a snow particle movement vector. Moves particle vertically, clamps Y to 0 */
void sharedFunc_800CF2A4_0_s01(s32 arg0, s_particle* particle, u16* rand, s32* deltaTime)
{
    u16 localRand;

    VECTOR3* pos = &particle->position1_0;

    if (arg0 == 0)
    {
        // A random value has been generated in caller and a pointer to it passed as arg2
        // Add a random X offset [-7,7]
        particle->movement_18.vx += (s32)(*rand % 15) - 7;
        
        // New random value for Z and Y to share and store in arg2
        *rand = (u16)Rng_Rand16();
        
        // NOTE: The movement.vz offset below needs a local variable for the function to match
         localRand = *rand;

        // Add a random Z offset [-7,7]
        particle->movement_18.vz += (s32)(localRand % 15) - 7;
        // Add a random Y offset [-1,3]
        particle->movement_18.vy += (s32)(*rand % 5) - 1;
        
        // Apply the movement to position over time
        particle->position1_0.vy += ((((particle->movement_18.vy >> 1) << 2) * *deltaTime) / 136);
    }
    
    // Always clamp the main Y value
    // NOTE: Particle enters resting state ends when 0 is reached
    if (pos->vy >= 0)
    {
        pos->vy = 0;
    }
    // Permuter needed - credit: belek666
    if (pos->vy >= 0) {}
}