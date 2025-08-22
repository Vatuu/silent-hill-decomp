
// TODO: Refine comments and names, it's still kind of unclear.
/** @brief Spawns snow particles. Called once when the map overlay is loaded.
 *
 * Spawns and updates snow particles.
 * This avoids having all the snow particles starting in the sky at the same time.
 *
 * The spawn loop works as follows (pseudocode):
 *
 * particlesAdded = 0;
 * toAddPerTick   = 1 or 3;
 * 
 * // Perform spawn tick.
 * while (particlesAdded < SNOW_SPAWN_COUNT_MAX)
 * {
 *     // Start at 0 to update all previously added particles by one step.
 *     for (i = 0; i < particlesAdded; i++)
 *     {
 *        updateParticle(i); // These particles will re-add below if they expire.
 *     }
 
 *     // Add new particles.
 *     for (i = 0; i < toAddPerTick; i++)
 *     {
 *         addParticle();
 *         particlesAdded++;
 *     }
 * }
 */
void sharedFunc_800CE59C_0_s01(s_Particle* parts)
{
    #define SNOW_COUNT_MAX       300
    #define SNOW_SPAWN_COUNT_MAX 150
    #define SNOW_REST_TICKS_MAX  16

    s32         i;
    s32         j;
    s16         rand;
    s32         density;
    s32         spawnMult;
    u16         settingsState; // TODO: Rename.
    u16         snowType;
    s32         deltaTime;
    s_Particle* part;

    deltaTime = FP_TIME(0.1f / 3.0f);

    GsInitCoordinate2(NULL, (GsCOORDINATE2*)g_SysWork.unk_22A8);

    // Reset states.
    for (i = 0, part = parts; i < SNOW_COUNT_MAX; i++, part++)
    {
        part->stateStep_1E = 0;
    }

    // Reset counts. NOTE: One is unused.
    sharedData_800DD78C_0_s01[1] = 0;
    sharedData_800DD78C_0_s01[0] = 0;

    // Settings byte holds state and snow type. Can be 0-2. 1 enables snow. TODO: Move doc.
    settingsState = (sharedData_800E0CB8_0_s00 & 0xC) >> 2;
    if (((sharedData_800E0CB8_0_s00 & 0xC) >> 2) == 1)
    {
        for (i = 0, part = parts; i < SNOW_COUNT_MAX; i++, part++)
        {
            part->type_1F = SnowType_Light;
        }

        density = (g_SysWork.field_2349 == 1) ? 1 : 3;
    }
    else
    {
        for (i = 0, part = parts; i < SNOW_COUNT_MAX; i++, part++)
        {
            part->type_1F = settingsState;
        }

        density = 10;
    }

    if (settingsState)
    {
        snowType = sharedData_800E0CB8_0_s00 & 0x3;
        settingsState--;

        // Set wind speed on XZ plane.
        if (snowType >= SnowType_LightWindy)
        {
            sharedData_800DFB68_0_s00 = SNOW_COUNT_MAX * 2;
            sharedData_800DFB64_0_s00 = SNOW_COUNT_MAX * 2;
        }
        else
        {
            sharedData_800DFB68_0_s00 = 0;
            sharedData_800DFB64_0_s00 = 0;
        }

        // Set start position.
        sharedData_800E323C_0_s00.vy = FP_METER(-6.0f);

        // Particle type determines particle multiplier for spawn loop.
        spawnMult = (snowType == SnowType_Light || snowType == SnowType_LightWindy) ? 1 : 2;

        // Spawn and update.
        for (j = 0; j < SNOW_SPAWN_COUNT_MAX; j++)
        {
            // Reset how many particles to spawn this iteration.
            sharedData_800E2156_0_s01 = 0;

            rand                                      = Rng_Rand16();
            sharedData_800DD78C_0_s01[settingsState] += spawnMult;

            // Clamp spawn count.
            if (snowType == SnowType_Light || snowType == SnowType_LightWindy)
            {
                limitRange(sharedData_800DD78C_0_s01[settingsState], 0, SNOW_SPAWN_COUNT_MAX);
            }
            else
            {
                limitRange(sharedData_800DD78C_0_s01[settingsState], 0, SNOW_COUNT_MAX);
            }

            for (i = 0, part = parts; i < sharedData_800DD78C_0_s01[settingsState]; i++, part++)
            {
                switch (part->stateStep_1E)
                {
                    case ParticleState_Spawn:
                        // Throttle spawning.
                        if (sharedData_800E2156_0_s01 < density)
                        {
                            sharedData_800E2156_0_s01++;
                            sharedFunc_800CF9A8_0_s01(settingsState, part, &rand);
                        }
                        break;

                    case ParticleState_Active:
                        sharedFunc_800CF2A4_0_s01(settingsState, part, &rand, &deltaTime);
                        
                        // Step to rest state when Y position reaches 0.
                        if (part->position0_0.vy == 0)
                        {
                            part->stateStep_1E++;
                        }
                        break;

                    default: // `ParticleState_Rest`
                        part->stateStep_1E++;
                        if (part->stateStep_1E >= SNOW_REST_TICKS_MAX)
                        {
                            part->stateStep_1E = 0;
                        }
                        break;
                }
            }
        }
    }
}
