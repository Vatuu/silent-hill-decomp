/** @brief Reset function for a snow particle */
void sharedFunc_800CF9A8_0_s01(s32 arg0, s_Particle* part, u16* rand)
{
    #define SNOW_XZ_SPAWN_RANGE 5
    #define SNOW_Y_START_SPEED  100

    VECTOR3* pos;

    pos = &part->position1_0;

    if (arg0 == 0)
    {
        if (sharedData_800DD796_0_s01 != 0)
        {
            part->type_1F = 0;
        }
        else
        {
            part->type_1F = 1;
        }

        // Set Y start position.
        part->position1_0.vy = sharedData_800E323C_0_s00.vy;

        // Set downward movement.
        part->movement_18.vz = 0;
        part->movement_18.vx = 0;
        part->movement_18.vy = SNOW_Y_START_SPEED;

        // Set random start XZ position.
        sharedFunc_800D01BC_0_s00(rand, pos, SNOW_XZ_SPAWN_RANGE);

        // 2nd position unused for snow.
        part->position2_C.vz = 0;
        part->position2_C.vy = 0;
        part->position2_C.vx = 0;
    }

    // Move particle into active state.
    part->counter_1E++;
}