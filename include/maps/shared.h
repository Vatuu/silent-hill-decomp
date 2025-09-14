#ifndef _MAPS_SHARED_H
#define _MAPS_SHARED_H

#include "game.h"

// TODO: Move to wherever it belongs.
/*s_AnimInfo ALESSA_ANIM_INFOS[] =
{
    { Anim_Update2, ANIM_STATUS(0,  false), false, ANIM_STATUS(0,  false), { Q19_12(0)  }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(0,  true),  false, NO_VALUE,               { Q19_12(30) }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(1,  false), false, ANIM_STATUS(10, true),  { Q19_12(5)  }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(1,  true),  false, NO_VALUE,               { Q19_12(5)  }, 0,        15  },
    { Anim_Update2, ANIM_STATUS(2,  false), false, ANIM_STATUS(10, true),  { Q19_12(5)  }, NO_VALUE, 16  },
    { Anim_Update1, ANIM_STATUS(2,  true),  false, NO_VALUE,               { Q19_12(15) }, 16,       44  },
    { Anim_Update2, ANIM_STATUS(3,  false), false, ANIM_STATUS(3,  true),  { Q19_12(10) }, NO_VALUE, 45  },
    { Anim_Update0, ANIM_STATUS(3,  true),  false, ANIM_STATUS(3,  true),  { Q19_12(10) }, 45,       131 },
    { Anim_Update2, ANIM_STATUS(4,  false), false, ANIM_STATUS(4,  true),  { Q19_12(20) }, NO_VALUE, 132 },
    { Anim_Update0, ANIM_STATUS(4,  true),  false, ANIM_STATUS(4,  true),  { Q19_12(10) }, 132,      170 },
    { Anim_Update2, ANIM_STATUS(5,  false), false, ANIM_STATUS(5,  true),  { Q19_12(10) }, NO_VALUE, 171 },
    { Anim_Update0, ANIM_STATUS(5,  true),  false, ANIM_STATUS(5,  true),  { Q19_12(10) }, 171,      216 },
    { Anim_Update2, ANIM_STATUS(6,  false), false, ANIM_STATUS(6,  true),  { Q19_12(1)  }, NO_VALUE, 217 },
    { Anim_Update0, ANIM_STATUS(6,  true),  false, ANIM_STATUS(6,  true),  { Q19_12(10) }, 217,      237 },
    { Anim_Update2, ANIM_STATUS(7,  true),  false, ANIM_STATUS(7,  true),  { Q19_12(1)  }, NO_VALUE, 238 },
    { Anim_Update0, ANIM_STATUS(7,  true),  false, ANIM_STATUS(7,  true),  { Q19_12(10) }, 238,      288 },
    { Anim_Update2, ANIM_STATUS(8,  false), false, ANIM_STATUS(8,  true),  { Q19_12(10) }, NO_VALUE, 289 },
    { Anim_Update0, ANIM_STATUS(8,  true),  false, ANIM_STATUS(8,  true),  { Q19_12(10) }, 289,      309 },
    { Anim_Update2, ANIM_STATUS(9,  false), false, ANIM_STATUS(9,  true),  { Q19_12(5)  }, NO_VALUE, 310 },
    { Anim_Update1, ANIM_STATUS(9,  true),  false, NO_VALUE,               { Q19_12(3)  }, 310,      325 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true),  { Q19_12(5)  }, NO_VALUE, 326 },
    { Anim_Update1, ANIM_STATUS(10, true),  false, NO_VALUE,               { Q19_12(3)  }, 326,      341 }
};*/

#define PARTICLE_COUNT_MAX 300

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
    VECTOR3     position0_0;  // Snow: position, Rain: streak start (bottom)
    VECTOR3     position1_C;  // Snow: unused, Rain: streak end (top)
    SVECTOR3    movement_18;  // Snow: random accumulation, Rain: Y accumulation (affects streak length).
    u8          stateStep_1E; /** `e_ParticleState` */
    u8          type_1F;      /** `e_ParticleType` */
} s_Particle;

typedef struct
{
    char unk_0[3420];
    u16  field_D5C;
    s16  field_D5E;
} s_func_800D8714;

typedef struct
{
    VECTOR3 field_0;
    VECTOR3 field_C;
    s16     field_18;
    s16     field_1A;
    s16     field_1C;
    u8      field_1E;
    s8      field_1F;
    char    unk_20[16];
} s_sharedFunc_800CEFD0_1_s02;

typedef struct
{
    VECTOR3 vector_0;
    VECTOR3 viewPosition_C; // Q19.12
    SVECTOR svec_18;
    SVECTOR viewRotation_20;
    s32     field_28;
} s_ParticleVectors;

/** Seems to be custom boundaries for snow/rain particle systems.
 * Only used in a small handful of maps, and not all fields are populated.
 *
 * Maybe 8 `VECTOR3`s holding positions in Q19.12? Se4ms to be an inefficient AABB.
 */
typedef struct
{
    VECTOR3 corners_0[8];
} s_func_800CB560;
STATIC_ASSERT_SIZEOF(s_func_800CB560, 96);

/** @brief Stores SFX ID and volume.
 * TODO: There's already an `s_Sfx` struct. Should harmonize the names once both are figured out.
 */
typedef struct _SfxVolume
{
    u16 id_0;
    u8  volume_2;
    u8  __pad_3;
} s_SfxVolume;
/** Likely maps onto another struct somewhere. Starts with an `s_AnimInfo`, has some index properties deeper in it. */
typedef struct
{
    s_AnimInfo  animInfo_0; // This might be a pointer instead - not enough clues available yet to tell.
    s8          unk_10[3288];
    s_SfxVolume sfxVolumes_CE8[11];
    u_Property  properties_D14[4]; // Read as 4 pairs of `u16`s.
} s_func_800D2E04;

typedef struct
{
    s32            flags_0;
    s32            field_4;
    GsCOORDINATE2* coords_8;
    MATRIX*        mat_C; // `MATRIX` array? Needs to be `s32` to match, weird.
} s_sharedData_800E21D0_0_s01;

extern s_SfxVolume g_SfxVolumes[46];

/** Scale. */
extern VECTOR sharedData_800DD870_0_s01;

/** Scale. */
extern VECTOR sharedData_800DD880_0_s01;

/** Could be a padded `VECTOR`, but the ASM for the function `vec = vec` assignments copies only the first 3 fields. */
extern VECTOR3 sharedData_800DE170_0_s01;
extern VECTOR3 sharedData_800DE180_0_s01;
extern VECTOR3 sharedData_800DE190_0_s01;

extern s_func_800700F8_2 sharedData_800E2330_0_s01;

extern u8 sharedData_800DF158_1_s02;

extern VECTOR sharedData_800CAB70_0_s00;

extern s32 sharedData_800E0CA8_0_s00;
extern s32 sharedData_800E0CAC_0_s00;
extern u32 sharedData_800E0CB0_0_s00;
extern u16 sharedData_800E0CB4_0_s00;
extern u16 sharedData_800E0CB6_0_s00;
extern u16 sharedData_800E0CB8_0_s00;
extern s8  sharedData_800E0CBA_0_s00;
extern s32 sharedData_800E32D0_0_s00;

/** `e_EquippedWeaponId` */
extern s8 sharedData_800DD59C_0_s00;

extern s32 sharedData_800DF1F4_0_s00;
extern s16 sharedData_800DF1F8_0_s00;
extern s16 sharedData_800DF1FA_0_s00;

extern s16 sharedData_800E0C6E_0_s00;

/** Related to particle position. */
extern VECTOR3 sharedData_800E323C_0_s00;

/** Previous particle position? */
extern VECTOR3 sharedData_800E324C_0_s00;

/** Previous particle Y angle? */
extern s16 sharedData_800E3260_0_s00;

extern s32 sharedData_800E39D8_0_s00;

// Next 4 set by `Ai_Stalker_Update`.
extern s32 sharedData_800E3A20_0_s00;
extern s32 sharedData_800E3A24_0_s00;
extern s32 sharedData_800E3A28_0_s00;
extern s32 sharedData_800E3A2C_0_s00;

extern s_AnimInfo LARVAL_STALKER_ANIM_INFOS[]; // Used by `Ai_LarvalStalker_Init`.

extern s_AnimInfo STALKER_ANIM_INFOS[]; // Used by `Ai_Stalker_Init`.

// Two variables used by `Ai_Creaper_Init`.
extern s_AnimInfo CREAPER_ANIM_INFOS[];
extern s8 sharedData_800E57CC_1_s02;

extern s_sharedData_800E21D0_0_s01 sharedData_800E21D0_0_s01;

extern s_func_800D2E04 sharedData_800CAA98_0_s01; // Used by `Ai_AirScreamer_Init` / `sharedFunc_800D2BF4_0_s01`

extern s_AnimInfo sharedData_800EC954_2_s02[]; // Used by `Ai_Romper_Init`.

extern s_AnimInfo sharedData_800EEB14_2_s00[]; // Used by `Ai_Groaner_Init`.

extern s_AnimInfo sharedData_800D91A0_5_s00[]; // Used by `Ai_HangedScratcher_Init`.

// Three variables used by `Ai_Splithead_Init`.
extern s_AnimInfo sharedData_800D5888_1_s05[];
extern s16 sharedData_800D8614_1_s05; // These two s16s could be DVECTOR?
extern s16 sharedData_800D8616_1_s05;

extern u8 sharedData_800DCC14_1_s00[];

extern s32 sharedData_800D6BB8_3_s04; // Used by `Ai_Lisa_Init`.

extern s32 sharedData_800E2C38_7_s01; // Used by `Ai_BloodyLisa_Init`.

// Two variables used by `Ai_Cybil_Init`.
extern s32 sharedData_800E2378_0_s01;
extern s32 sharedData_800E237C_0_s01;

// Two variables used by `Ai_Dahlia_Init`.
extern s32 sharedData_800D16E0_2_s01;
extern s8  sharedData_800D16E4_2_s01;

extern s_AnimInfo ALESSA_ANIM_INFOS[];
extern s32 sharedData_800D3150_3_s02; // Used by `Ai_Alessa_Init`.

extern s32 sharedData_800D5CF4_3_s00; // Used by `Ai_Kaufmann_Init`.

extern s_AnimInfo BLOODSUCKER_ANIM_INFOS[]; // Used by `Ai_Bloodsucker_Init`.

extern u8 sharedData_800DD591_0_s00;
extern u8 sharedData_800DD78B_0_s01;
extern u8 sharedData_800DD796_0_s01;

/** `g_ParticlesAddedCounts`. Tracks how many total particles have been added. */
extern s32 sharedData_800DD78C_0_s01[2];

/** `g_ParticleSpawnCount`. Tracks how many particles have been added per call. */
extern u8 sharedData_800E2156_0_s01;

extern s_AnimInfo KAUFMANN_ANIM_INFOS[]; // Used by `Anim_StartKeyframeIdxGet`, `Ai_Kaufmann` related?

extern s_AnimInfo BLOODY_LISA_ANIM_INFOS[]; // `Ai_BloodyLisa` related?

/** Particle speed X. */
extern s32 sharedData_800DFB64_0_s00;

/** Particles speed Z. */
extern s32 sharedData_800DFB68_0_s00;

extern s32 sharedData_800DFB6C_0_s00;
extern s32 sharedData_800DFB70_0_s00;

extern s32 sharedData_800DD58C_0_s00;
extern s32 sharedData_800E32CC_0_s00;

extern s32 sharedData_800D32A0_0_s02; // `sharedFunc_800CDAA8_0_s02`

extern u16 sharedData_800D21E8_3_s00[];

extern s_func_800CB560 sharedData_800E5768_1_s02;

extern s_Particle g_Particles[PARTICLE_COUNT_MAX];

extern s_ParticleVectors g_ParticleVectors0;

extern s_ParticleVectors g_ParticleVectors1;

extern const char* MAP_MESSAGES[]; // 0x800DF6B8

bool sharedFunc_800CBBBC_0_s00();

void sharedFunc_800D01BC_0_s00(u16* arg0, VECTOR3* arg1, s32 arg2);

void sharedFunc_800D0A60_0_s00(s32 caseArg);

bool sharedFunc_800D0B18_0_s00(s32 arg0);

void sharedFunc_800D0E04_0_s00();

void sharedFunc_800D209C_0_s00();

void sharedFunc_800D20D8_0_s00();

void sharedFunc_800D20E4_0_s00();

void sharedFunc_800D2244_0_s00(s32 arg0);

void sharedFunc_800D2C7C_0_s00(s32 arg0);

void sharedFunc_800D2D2C_0_s00();

void sharedFunc_800D2D44_0_s00();

s32 sharedFunc_800D2D6C_0_s00();

void sharedFunc_800D2D84_0_s00();

/** Triggers at specific points after the start of a cutscene or dialogue. */
s32 sharedFunc_800D2E50_0_s00();

void sharedFunc_800D2E60_0_s00();

u8 sharedFunc_800D2EA4_0_s00();

void sharedFunc_800D2EB4_0_s00();

void sharedFunc_800D2EF4_0_s00();

void sharedFunc_800D5098_0_s00(s_SubCharacter* chara);

void sharedFunc_800D5B48_0_s00(s_SubCharacter* chara);

void sharedFunc_800D63D0_0_s00(s_SubCharacter* chara, s32 moveSpeed);

void sharedFunc_800D6554_0_s00(s_SubCharacter* chara);

void sharedFunc_800D670C_0_s00(s_SubCharacter* chara);

void sharedFunc_800D67FC_0_s00(s_SubCharacter* chara);

void sharedFunc_800D7E04_0_s00(s_SubCharacter* chara, s32 caseArg);

void sharedFunc_800D88AC_0_s00(s_SubCharacter* playerChara);

void Ai_Stalker_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_Stalker_Init(s_SubCharacter* chara); // Matches across all maps except `map6_s03`.

void sharedFunc_800D3308_0_s00(s_SubCharacter*);

void sharedFunc_800D3B44_0_s00(s_SubCharacter*);

void sharedFunc_800D6970_0_s00(s_SubCharacter*, s32, GsCOORDINATE2*);

void sharedFunc_800D70C4_0_s00(s_SubCharacter*);

void sharedFunc_800D7BE8_0_s00(s_SubCharacter*);

/** Among other things, sets the players's anim to anim 3 (which might actually be flags if the field packs more data). */
void sharedFunc_800D88C0_0_s00(s_SubCharacter* playerChara, s32 arg1);

/** Resets some player properties. */
void sharedFunc_800D8904_0_s00(s_SubCharacter* playerChara, s32 afkTime);

void sharedFunc_800D891C_0_s00(s_SubCharacter* playerChara);

void sharedFunc_800D8928_0_s00(s_SubCharacter* chara);

s32 sharedFunc_800D893C_0_s00(s_SubCharacter* chara);

void sharedFunc_800D8950_0_s00(s_SubCharacter* chara);

bool sharedFunc_800D8A00_0_s00(s_SubCharacter* chara, s32 arg1, VECTOR3* arg2In, s32 angleIn, s32 arg4);

void sharedFunc_800D9064_0_s00(s_SubCharacter* chara);

void sharedFunc_800D9078_0_s00(s_SubCharacter* chara);

s16 Anim_StartKeyframeIdxGet(s_SubCharacter* chara);

/** Humanoid init function? */
void sharedFunc_800D923C_0_s00(s_SubCharacter* chara);

u8 sharedFunc_800D92AC_0_s00(s32 x, s32 y);

/** Snow effect init. */
void sharedFunc_800CE59C_0_s01(s_Particle* particles);

/** Snow particle update. */
void sharedFunc_800CF2A4_0_s01(s32 arg0, s_Particle* part, u16* rand, s32* deltaTime);

/** Snow particle init. */
void sharedFunc_800CF9A8_0_s01(s32 arg0, s_Particle* part, u16* rand);

bool Particle_Update(s_Particle* partHead);

void sharedFunc_800CEFF4_0_s00(s_Particle* part, s32 arg1);

void sharedFunc_800CEB24_0_s00(s_Particle* part);

void sharedFunc_800CFFF8_0_s00(s32 pass, s_func_800CFFF8* part, s16* rand); // TODO: Make this match for `s_Particle`.

void sharedFunc_800CE954_7_s03(s32 pass, s_Particle* part, s16* rand, s32* deltaTime);

void sharedFunc_800DA8E8_0_s01(s32* timer, s32 inc, s32 timeMin, s32 timeMax, bool setTimerToMax, bool incStateStep);

void sharedFunc_800CDAA8_0_s02(s_SubCharacter* playerChara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord);

// MAP1_S00 LarvalStalker funcs
void Ai_LarvalStalker_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void sharedFunc_800CF168_1_s00(s_SubCharacter*);

void sharedFunc_800D140C_1_s00(s_SubCharacter*, GsCOORDINATE2*);

void sharedFunc_800D1524_1_s00(s_SubCharacter*, s32, GsCOORDINATE2*);

void Ai_LarvalStalker_Init(s_SubCharacter* chara);

void sharedFunc_800D17BC_1_s00(s_SubCharacter*);

void sharedFunc_800D1DBC_1_s00(s_SubCharacter*);

void sharedFunc_800CEFD0_1_s02(s32 arg0, s_sharedFunc_800CEFD0_1_s02* arg1, u16* arg2, s32* deltaTime); // TODO make this match for s_Particle

/** @brief Sets a map overlay value based on a whether a game event flag is set. */
void sharedFunc_800D0994_3_s00();

void sharedFunc_800D09D4_3_s00();

// MAP3_S03 puppet nurse/doctor funcs
void sharedFunc_800CDA88_3_s03(s_SubCharacter*);

void Ai_PuppetNurse_UpdateMain(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void func_800CDB5C(s_SubCharacter*, s32);

void Ai_PuppetNurse_Init(s_SubCharacter* chara, s32 isPuppetDoctor);

void Ai_PuppetNurse_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_PuppetDoctor_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void sharedFunc_800CDF24_3_s03(s_SubCharacter*);

void sharedFunc_800CE3CC_3_s03(s_SubCharacter*);

void sharedFunc_800CE500_3_s03(s_SubCharacter*);

void sharedFunc_800CE5E4_3_s03(s_SubCharacter*, s32);

void sharedFunc_800CEA64_3_s03(s_SubCharacter*);

void sharedFunc_800CEB90_3_s03(s_SubCharacter*, s32);

void sharedFunc_800CEC88_3_s03(s_SubCharacter*);

void sharedFunc_800CF3AC_3_s03(s_SubCharacter*);

void sharedFunc_800CF9F8_3_s03(s_SubCharacter*);

void sharedFunc_800CFD18_3_s03(s_SubCharacter*);

void sharedFunc_800CFDD4_3_s03(s_SubCharacter*);

void sharedFunc_800D0110_3_s03(s_SubCharacter*);

void Ai_PuppetNurse_Control(s_SubCharacter* chara);

void sharedFunc_800D02E4_3_s03(s_SubCharacter*, GsCOORDINATE2*);

void sharedFunc_800D03E4_3_s03(s_SubCharacter*);

void sharedFunc_800D06AC_3_s03(s_SubCharacter*, s32, GsCOORDINATE2*);

void sharedFunc_800D0828_3_s03(s_SubCharacter*, GsCOORDINATE2*);

void sharedFunc_800D0968_3_s03(s_SubCharacter* chara, GsCOORDINATE2* coords);

void Ai_Creaper_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_Creaper_Init(s_SubCharacter* chara); // `map5_s00` version has extra code at end of func.

void sharedFunc_800D7EE8_1_s02(s_SubCharacter*);

void sharedFunc_800D8244_1_s02(s_SubCharacter* chara);

void sharedFunc_800D82F0_1_s02(s_SubCharacter*);

void sharedFunc_800D8684_1_s02(s_SubCharacter*);

void sharedFunc_800D8F30_1_s02(s_SubCharacter*);

void sharedFunc_800D9528_1_s02(s_SubCharacter*);

void sharedFunc_800D9774_1_s02(s_SubCharacter*);

void sharedFunc_800D983C_1_s02(s_SubCharacter*);

void sharedFunc_800D9960_1_s02(s_SubCharacter*, s32, GsCOORDINATE2*);

void sharedFunc_800D99D0_1_s02(s_SubCharacter*);

void Ai_HangedScratcher_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_HangedScratcher_Init(s_SubCharacter* chara);

void sharedFunc_800CFF74_5_s00(s_SubCharacter*);

void sharedFunc_800D029C_5_s00(s_SubCharacter*);

void sharedFunc_800D26D8_5_s00(s_SubCharacter*);

void sharedFunc_800D2844_5_s00(s_SubCharacter*, s32, GsCOORDINATE2*);

void sharedFunc_800D2C18_5_s00(s_SubCharacter*);

void sharedFunc_800D3300_5_s00(s_SubCharacter*);

s32 sharedFunc_800D3508_0_s01(s_SubCharacter* chara, s32* arg1);

s32 sharedFunc_800D3630_0_s01(s_SubCharacter* chara, s32* arg1);

s32 sharedFunc_800D3758_0_s01(s_SubCharacter* chara, s32* outDistance, s32* outAngle, s32 arg3, s32 arg4);

void Ai_Romper_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_Romper_Init(s_SubCharacter* chara);

void sharedFunc_800E60FC_2_s02(s_SubCharacter*);

void sharedFunc_800E6420_2_s02(s_SubCharacter*);

void sharedFunc_800E66E8_2_s02(s_SubCharacter*);

void sharedFunc_800E8730_2_s02(s_SubCharacter*);

void sharedFunc_800E8A40_2_s02(s_SubCharacter*, s32, GsCOORDINATE2*);

void sharedFunc_800E8DFC_2_s02(s_SubCharacter*);

void Ai_Groaner_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_Groaner_Init(s_SubCharacter* chara); // `map2_s00` has extra block at end of func compared to other maps.

void sharedFunc_800E33DC_2_s00(s_SubCharacter*);

void sharedFunc_800E384C_2_s00(s_SubCharacter*); // `map2_s00` has different version to the other 4 maps which share this, shared sym is needed to share `Ai_Groaner_Update`.

void sharedFunc_800E5AA4_2_s00(s_SubCharacter*);

void sharedFunc_800E5EC4_2_s00(s_SubCharacter*, s32, GsCOORDINATE2*);

void sharedFunc_800E6338_2_s00(s_SubCharacter*);

void sharedFunc_800E71E8_2_s00(s_SubCharacter*);

void Ai_Splithead_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_Splithead_Init(s_SubCharacter* chara);

void sharedFunc_800CF990_1_s05(s_SubCharacter*);

void sharedFunc_800CFE94_1_s05(s_SubCharacter*);

void sharedFunc_800D0054_1_s05(s_SubCharacter*);

void sharedFunc_800D267C_1_s05(s_SubCharacter*);

void sharedFunc_800D274C_1_s05(s_SubCharacter*, s32);

void sharedFunc_800D2D74_1_s05(s_SubCharacter*);

void sharedFunc_800D3AFC_1_s05(s_SubCharacter*);

void sharedFunc_800D3B30_1_s05(s_SubCharacter*);

void sharedFunc_800D4070_1_s05(s_SubCharacter*);

extern GsCOORDINATE2* sharedData_800D8610_1_s05;

void Ai_Cybil_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void sharedFunc_800D8888_0_s01(s_SubCharacter*, s32, GsCOORDINATE2*);

void sharedFunc_800D88D0_0_s01(s_SubCharacter* chara, GsCOORDINATE2* coord);

void sharedSymbol_800D8A68_0_s01(s_SubCharacter*, GsCOORDINATE2*);

void Ai_Cybil_Init(s_SubCharacter* chara);

void Ai_AirScreamer_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

bool sharedFunc_800D21E4_0_s01(s32, GsCOORDINATE2* coords);

void sharedFunc_800D2200_0_s01(s_SubCharacter* chara);

bool sharedFunc_800D2274_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2364_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2390_0_s01(s_SubCharacter*);

bool Ai_AirScreamer_Init(s_SubCharacter* chara);

void sharedFunc_800D2B00_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2B10_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2B28_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2B4C_0_s01(s_SubCharacter*);

void sharedFunc_800D2BB0_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2BE4_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2BF4_0_s01(s_SubCharacter* chara);

bool sharedFunc_800D2E04_0_s01(s_SubCharacter* chara, VECTOR3* inVec, s32* outDist, s32* outAngle);

s32 sharedFunc_800D3430_0_s01(s_SubCharacter* chara, s32* arg1, s32* arg2);

s32 sharedFunc_800D3814_0_s01(s_SubCharacter* chara);

s32 sharedFunc_800D31D0_0_s01(s_SubCharacter* chara, VECTOR3* arg1, s32 arg2);

void sharedFunc_800D3928_0_s01(s_SubCharacter*);

void sharedSymbol_800D3B0C_0_s01(s_SubCharacter*);

bool sharedFunc_800D62D8_0_s01(s_SubCharacter* chara);

/** Returns anim-related index. */
s32 sharedFunc_800D4A80_0_s01(s_SubCharacter*);

s32 sharedFunc_800D5274_0_s01();

void sharedFunc_800D633C_0_s01(s_SubCharacter*);
void sharedFunc_800D63A4_0_s01(s_SubCharacter*);
void sharedFunc_800D6600_0_s01(s_SubCharacter*);

s32 sharedFunc_800D7120_0_s01(s32, s32, s32);
s32 sharedFunc_800D71F0_0_s01(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 sharedFunc_800D7440_0_s01(VECTOR* vec0, VECTOR* vec1, s_SubCharacter* chara);

void sharedFunc_800D7560_0_s01(s_SubCharacter* chara);

void sharedFunc_800D76A0_0_s01(s_SubCharacter* chara);

s32 sharedFunc_800D77D0_0_s01(s_SubCharacter*); // Assumed return type.

void sharedFunc_800D7AB0_0_s01(s_SubCharacter*);

void sharedFunc_800D7EBC_0_s01(s_SubCharacter*);

bool sharedFunc_800D81B0_0_s01(s_SubCharacter* chara);

void sharedFunc_800D82B8_0_s01(s_SubCharacter*);

void sharedFunc_800D8714_0_s01(s_SubCharacter*, s32, s32);

void sharedFunc_800D87FC_0_s01(s_SubCharacter* chara);

s32 sharedFunc_800D929C_0_s00();
s32 sharedFunc_800D2DAC_0_s00(); // Player anim func. Checks if the active keyframe is at the start or end of the anim's range.
s32 sharedFunc_800D8964_0_s00(s_SubCharacter* chara); // NPC anim func. Checks if the active keyframe is at the start or end of the anim's range.
bool sharedFunc_800D9188_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx, s32 sfx);
void sharedFunc_800D08B8_0_s00(s8 arg0, u32 arg1);

// `Ai_Lisa` related
void Ai_Lisa_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedFunc_800D08FC_3_s04(s_SubCharacter*, s32, GsCOORDINATE2*);
void sharedFunc_800D0944_3_s04(s_SubCharacter* chara, GsCOORDINATE2* coord);
void sharedSymbol_800D0ADC_3_s04(s_SubCharacter*, GsCOORDINATE2*); // `Ai_Lisa_Control`
void Ai_Lisa_Init(s_SubCharacter* chara);

// `Ai_BloodyLisa` related
void Ai_BloodyLisa_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedFunc_800D595C_7_s01(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coord);
void sharedFunc_800D59A4_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coords);
void sharedFunc_800D5B3C_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coords);
bool sharedFunc_800D908C_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx0, s32 keyframeIdx1, s32 sfx, s32 pitch);
void Ai_BloodyLisa_Init(s_SubCharacter* chara);

// `Ai_Kaufmann` related
void Ai_Kaufmann_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedSymbol_800CF470_3_s00(s_SubCharacter*, GsCOORDINATE2*);
void sharedFunc_800CF2D8_3_s00(s_SubCharacter* chara, GsCOORDINATE2* coord);
void sharedFunc_800CF290_3_s00(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coord);
void Ai_Kaufmann_Init(s_SubCharacter* chara);

// `Ai_GhostChildAlessa` related
void Ai_GhostChildAlessa_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedFunc_800D4A2C_7_s01(s_SubCharacter*, s32, GsCOORDINATE2*);
void sharedFunc_800D4A74_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coord);
void sharedFunc_800D4C0C_7_s01(s_SubCharacter*, GsCOORDINATE2*);
void Ai_GhostChildAlessa_Init(s_SubCharacter* chara);

// `Ai_Alessa` related
void Ai_Alessa_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedFunc_800CECFC_3_s02(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coord);
void sharedFunc_800CED44_3_s02(s_SubCharacter* chara, GsCOORDINATE2* coord);
void sharedFunc_800CEEDC_3_s02(s_SubCharacter*, GsCOORDINATE2*);
void Ai_Alessa_Init(s_SubCharacter* chara);

// `Ai_Dahlia` related
void Ai_Dahlia_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedFunc_800CD280_2_s01(s_SubCharacter*, s32, GsCOORDINATE2*);
void sharedFunc_800CD2C8_2_s01(s_SubCharacter*, GsCOORDINATE2*);
void sharedSymbol_800CD4A0_2_s01(s_SubCharacter*, GsCOORDINATE2*);
void Ai_Dahlia_Init(s_SubCharacter* chara);

// `Ai_Bloodsucker` related
void Ai_Bloodsucker_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void Ai_Bloodsucker_Init(s_SubCharacter*);
void sharedFunc_800D0E20_3_s03(s_SubCharacter*);
void sharedSymbol_800D0E38_3_s03(s_SubCharacter*);
void sharedFunc_800D0E80_3_s03(s_SubCharacter*);
void sharedSymbol_800D0ECC_3_s03(s_SubCharacter*);
void sharedFunc_800D0F28_3_s03(s_SubCharacter*, s32, GsCOORDINATE2*);

static inline void ModelAnim_AnimInfoSet(s_ModelAnim* anim, s_AnimInfo* animInfo)
{
    anim->animInfo_C  = animInfo;
    anim->animInfo_10 = NULL;
}

#endif
