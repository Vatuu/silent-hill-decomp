#ifndef _MAPS_PARTICLE_H
#define _MAPS_PARTICLE_H

#define SNOW_COUNT_LIGHT_MAX 300

#if defined(MAP7_S03)
#define PARTICLE_COUNT_MAX 450
#else
#define PARTICLE_COUNT_MAX 300
#endif

typedef enum
{
    ParticleState_Spawn  = 0,
    ParticleState_Active = 1,
    ParticleState_Rest   = 2  
} e_ParticleState;

typedef enum
{
    ParticleType_Snow = 0,
    ParticleType_Unk1 = 1,
    ParticleType_Rain = 2
} e_ParticleType;

typedef enum
{
    SnowType_Light      = 0,
    SnowType_Heavy      = 1,
    SnowType_LightWindy = 2,
    SnowType_HeavyWindy = 3
} e_SnowType;

typedef struct
{
    VECTOR3  position0_0;  // Snow: position, Rain: streak start (bottom)
    VECTOR3  position1_C;  // Snow: unused, Rain: streak end (top)
    SVECTOR3 movement_18;  // Snow: random accumulation, Rain: Y accumulation (affects streak length).
    u8       stateStep_1E; /** `e_ParticleState` */
    u8       type_1F;      /** `e_ParticleType` */
} s_Particle;

typedef struct
{
    VECTOR3 vector_0;
    VECTOR3 viewPosition_C; // Q19.12
    SVECTOR svec_18;
    SVECTOR viewRotation_20;
    s32     field_28;
} s_ParticleVectors;

typedef struct
{
    DVECTOR field_0;
    u8      field_4;
    u8      field_5;
    u8      field_6;
    u8      field_7;
} s_func_800CC8FC_0; 

typedef struct
{
    s_func_800CC8FC_0 field_0[8];
} s_func_800CC8FC;

/** TODO: Rename to `g_Particles` after funcs have been shared. */
extern s_Particle sharedData_800E0CBC_0_s00[PARTICLE_COUNT_MAX];

extern s_ParticleVectors g_ParticleVectors0;

extern s_ParticleVectors g_ParticleVectors1;

/** `g_ParticlesAddedCounts`. Tracks how many total particles have been added. */
extern s32 sharedData_800DD588_0_s00[2];

/** `g_ParticleSpawnCount`. Tracks how many particles have been added per call. */
extern u8 sharedData_800E2156_0_s01;

extern s32 g_Particle_SpeedX;
extern s32 g_Particle_SpeedZ;

extern s32 sharedData_800E0CA8_0_s00;
extern s32 sharedData_800E0CAC_0_s00;
extern u32 sharedData_800E0CB0_0_s00;
extern u16 sharedData_800E0CB4_0_s00;
extern u16 sharedData_800E0CB6_0_s00;
extern u16 sharedData_800E0CB8_0_s00;
extern s8  sharedData_800E0CBA_0_s00;

extern s32 sharedData_800E32D0_0_s00;

extern u8 sharedData_800DF158_1_s02;

extern u8 sharedData_800DD592_0_s00;

extern s16 g_Particle_RotationY;

extern VECTOR3 g_Particle_Position;     // Q19_12
extern VECTOR3 g_Particle_PrevPosition; // Q19_12
extern q3_12   g_Particle_PrevRotationY;

extern s16 D_800F23D0; // MAP7_S03 extern, TODO: Might be sharedData?

extern s32 sharedData_800CD77C_1_s04; // Used by `sharedFunc_800CB6B0_0_s00` only in MAP1_S04 and MAP4_S00? Similar usage to `sharedData_800DFB50_0_s00`?

void sharedFunc_800CB6B0_0_s00(s32 arg1, s32 arg2, s32 arg3);

bool sharedFunc_800CBBBC_0_s00(void);

/** Snow effect init. */
void sharedFunc_800CBC94_0_s00(s_Particle* particles);

/** M0S00 only. */
void func_800CBFB0(s_800E34FC* arg0, s_800E330C* arg1, s32 mapId);

bool Particle_Update(s_Particle* partHead);

/** M0S00 only. */
bool func_800CC6E8(s_800E34FC* arg0, s_800E330C* arg1, s32 mapId);

/** M0S00 only. */
s32 func_800CC8FC(VECTOR3* arg0, s32* arg1, s_func_800CC8FC* arg2);

/** M0S00 only. */
void func_800CD1F4(s32 arg0, s32 arg1, s_800E330C* arg2);

/** M0S00 only, arg0 = value from 0 - 3 (enum?) */
void func_800CD8E8(s32 arg0, s32 arg1, s_800E330C* arg2);

/** M0S00 only, arg0 = value from 0 - 3 (enum?) */
void func_800CE02C(s32 arg0, s32 arg1, s_800E34FC* pos, s32 mapId);

/** M0S00 only. */
void func_800CE544(s32 idx0, s32 arg1, s_800E34FC* arg2);

void sharedFunc_800CEB24_0_s00(s_Particle* part);

void sharedFunc_800CEFF4_0_s00(s_Particle* part, s32 arg1);

/** @brief Adds a random offset to a snow particle movement vector. Moves particle vertically, clamps Y to 0. */
void sharedFunc_800CF2A4_0_s01(s32 arg0, s_Particle* part, u16* rand, s32* deltaTime);

void sharedFunc_800CEFD0_1_s02(s32 pass, s_Particle* part, u16* rand, s32* deltaTime);

void sharedFunc_800CFFF8_0_s00(s32 pass, s_Particle* part, s16* rand);

void sharedFunc_800D0690_1_s03(s32 pass, s_Particle* part, s16* rand, q19_12* deltaTime);

void sharedFunc_800CE954_7_s03(s32 pass, s_Particle* part, s16* rand, q19_12* deltaTime);

/** M0S00: Collision space distance check. @hack Guessed types. */
bool func_800D012C(VECTOR3* pos, s_func_800CC8FC* unused0, s32* unused1);

void sharedFunc_800D01BC_0_s00(u16* arg0, VECTOR3* arg1, s32 arg2);

/** @brief Reset function for a snow particle */
void sharedFunc_800CF9A8_0_s01(s32 arg0, s_Particle* part, u16* rand);

/** M0S00 only. */
void func_800D0394(s32 count, VECTOR3* vecs);

/** @brief M0S00: 2D player distance check on XZ plane.
 *
 * Checks against a constant 2D distance of `CHUNK_CELL_SIZE` between the player and two positions.
 * This is a lazy check, i.e.
 * instead of: `(SQUARE(x1 - x2) + SQUARE(z1 - z2)) < SQUARE(d)`
 * it does:    `(ABS(x1 - x2) + ABS(z1 - z2)) < d`.
 *
 * @return `true` if the player distance from either position is `< CHUNK_CELL_SIZE`, otherwise `false`.
 */
bool func_800D0600(void);

void sharedFunc_800D0700_0_s00(VECTOR3* point, VECTOR3* lineStart, VECTOR3* lineEnd, s32 flag);

void sharedFunc_800D08B8_0_s00(s8 arg0, u32 arg1);

void sharedFunc_800D0A60_0_s00(s32 caseArg);

bool sharedFunc_800D0B18_0_s00(s32 arg0);

void sharedFunc_800D0CB8_0_s00(void);

void sharedFunc_800D0E04_0_s00(void);

void sharedFunc_800CFFD8_0_s01(VECTOR3* vec0, q3_12* rotX, q3_12* rotY);

void sharedFunc_800D0850_0_s01(VECTOR3* vec0, VECTOR3* vec1);

#endif
