
// How many snow particle inits are needed
#define PARTICLE_INIT_MAX 150
// A particle init sometimes can spawn either 1 or 3 particles - seems to be some sort of multiplier
// The actual size of the particle array is therefore double the init count
// Technically this won't accommodate all the particles requested, which is probably performance related
#define PARTICLES_ARRAY_MAX 300
// How long the snow particle rests on the ground during init logic
// NOTE: This is duration doubled in runtime logic
#define SNOW_RESTING_TICKS_INIT 16

typedef enum
{
    snowType_Light        = 0,    // 00 = Light snow
    snowType_Heavy        = 1,    // 01 = Heavy snow
    snowType_Light_Windy  = 2,    // 10 = Light snow, with wind
    snowType_Heavy_Windy  = 3,    // 11 = Heavy snow, with wind
} e_snowType;

// Tracks how many particles have been added per-entry
// Not sure why this isn't a local variable
#define D_ParticleInitCount sharedData_800E2156_0_s01
// Track how many total particles have been added
#define D_ParticleAddedCount sharedData_800DD78C_0_s01

/**
 * @brief Initialises snow particles. Called once when the map overlay is loaded.
 *
 * This function not only spawns particles but also runs logic on them so they are in a good ready state
 * This avoids having all the snow particles starting in the sky at the same time
 *
 * The spawn loop roughly works like this (simplfied pseudocode):
 * particlesAdded = 0;
 * toAddPerTick = 1 or 3;
 * while (particlesAdded < PARTICLE_INIT_MAX) // Perform an init tick
 * {
 *     // Start at 0 to update all previously added particles by one step
 *     for (i = 0; i < particlesAdded; i++)
 *     {
 *        updateParticle(i); // These particles will re-add below if they expire
 *     }
 *     // Then add the new particle(s)
 *     for (i = 0; i < toAddPerTick; i++)
 *     {
 *         addParticle();
 *         particlesAdded++;
 *     }
 * }
 */
void sharedFunc_800CE59C_0_s01(s_Particle* particles) {
    s32 i, j;
    s16 rand;

    s32 particleInitPerTick;
    s32 particlesAddedPerTick;

    // Pointer to the current particle
    s_Particle* particlePtr;

    u16 settingsState;
    u16 settingsSnowType;

    s32 deltaTime = 0x88;

    GsInitCoordinate2(NULL, (GsCOORDINATE2* ) g_SysWork.unk_22A8);

    // Reset all particles to the init state
    for (particlePtr = particles, i = 0; i < PARTICLES_ARRAY_MAX; i++, particlePtr++)
    {
        particlePtr->counter_1E = 0;
    }
    
    // Reset the particle count tracking variables
    // NOTE: Only one of them gets used
    D_ParticleAddedCount[1] = 0;
    D_ParticleAddedCount[0] = 0;

    // A single settings byte holds a general state and the snow type
    // Can be 0-2, needs to be 1 to enable snow
    settingsState = (sharedData_800E0CB8_0_s00 & 0xC) >> 2;
    
    if (((sharedData_800E0CB8_0_s00 & 0xC) >> 2) == 1)
    {
        for (particlePtr = particles, i = 0; i < PARTICLES_ARRAY_MAX; i++, particlePtr++)
        {
            // Sets the type to snow
            particlePtr->type_1F = 0;
        }
        // Helps control how heavy the snow is
        // A heavy snow type will need to process more particles per tick to maintain visual density
        particleInitPerTick = g_SysWork.unk_0[0x2349] == 1 ? 1 : 3;
    }
    else
    {
        for (particlePtr = particles, i = 0; i < PARTICLES_ARRAY_MAX; i++, particlePtr++)
        {
            // Not sure what this is doing yet
            particlePtr->type_1F = (u8)settingsState;
        }
        // This is probably to init a lot of particles to a default state every tick, so it's completed sooner
        particleInitPerTick = 0xA;
    }

    if (settingsState)
    {
        // Get lower two bits of the settings byte
        settingsSnowType = sharedData_800E0CB8_0_s00 & 0x3;
        // The state also acts as an index into an array of particle limits
        settingsState = settingsState - 1;

        // Set XZ wind speed
        // NOTE: The init update doesn't apply any XZ movement, so this has no impact until after init is completed
        if (settingsSnowType >= snowType_Light_Windy)
        {
            sharedData_800DFB68_0_s00 = 600;
            sharedData_800DFB64_0_s00 = 600;
        }
        else
        {
            sharedData_800DFB68_0_s00 = 0;
            sharedData_800DFB64_0_s00 = 0;
        }
        // Set the particle spawn ceiling height
        sharedData_800E323C_0_s00.vy = -0x6000;

        // The particle type indicates how many new particles can be added per tick
        // This is separate from particleInitPerTick, which throttles how many per tick can be initialised, including expired particles
        particlesAddedPerTick = (settingsSnowType == snowType_Light || settingsSnowType == snowType_Light_Windy) ? 1 : 2;

        // Run the init for 150 ticks
        for (j = 0; j < PARTICLE_INIT_MAX; j++)
        {
            // Reset how many particles we've inititialised this tick
            D_ParticleInitCount = 0;
            // Generate a random value for offsets
            // Seems to be kept here, and passed by pointer, so there's just one local variable needed to store it
            rand = Rng_Rand16();

            // The previously added count is the current limit - grow it by now many new particles we can add
            D_ParticleAddedCount[settingsState] += particlesAddedPerTick;

            // Then cap the limit
            if ((settingsSnowType == snowType_Light || settingsSnowType == snowType_Light_Windy))
            {
                // Light snow - 150 particles max
                // NB: limitRange() is the standard psyq clamp macro
                limitRange(D_ParticleAddedCount[settingsState], 0, PARTICLE_INIT_MAX);
            }
            else
            {
                limitRange(D_ParticleAddedCount[settingsState], 0, PARTICLES_ARRAY_MAX);
            }

            // And finally interate over all existing particles to update them, and add new ones
            for (i = 0, particlePtr = particles; i < D_ParticleAddedCount[settingsState]; ++i, ++particlePtr)
            {
                switch (particlePtr->counter_1E)
                {
                    // Init state
                    case 0:
                        // Throttle how many particles we init every tick
                        if (D_ParticleInitCount < particleInitPerTick)
                        {
                            D_ParticleInitCount++;
                            // Init the particle
                            sharedFunc_800CF9A8_0_s01(settingsState, particlePtr, &rand);
                        }
                        break;
                    // Active state
                    case 1:
                        // Randomise the movement offset a little more and travel along Y (ignores XZ and wind)
                        sharedFunc_800CF2A4_0_s01(settingsState, particlePtr, &rand, &deltaTime);
                        // Switch to the resting state when the particle Y position hits 0
                        // A messy way of doing: if (particlePtr->position1_0.vy == 0)
                        if (particlePtr->position1_0.vy == 0)
                        {
                            particlePtr->counter_1E++;
                        }
                        break;
                    // Rest state - sits on the ground for a while
                    default:
                        // Increment the counter
                        particlePtr->counter_1E++;
                        // Reset the counter when the rest duration ends
                        if (particlePtr->counter_1E >= SNOW_RESTING_TICKS_INIT)
                        {
                            particlePtr->counter_1E = 0;
                        }
                        break;
                }
            }
        }
    }
}
