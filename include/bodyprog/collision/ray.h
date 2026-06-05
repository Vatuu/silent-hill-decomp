#ifndef _BODYPROG_COLLISION_RAY_H
#define _BODYPROG_COLLISION_RAY_H

#include "bodyprog/chara/chara.h"
#include "bodyprog/formats/ipd.h"

typedef struct
{
    s8         unk_0[8];
    DVECTOR    field_8;
    s16        field_C;
    s16        field_E;
    q19_12     field_10; // } X
    q19_12     field_14; // } Z
    s16        field_18;
    s8         unk_1A[2];
    s32        field_1C; // Index into `field_20`.
    DVECTOR_XZ field_20[2];
} s_func_8006E490;

// Something with a projected character position.
typedef struct
{
    /* 0x0 */ q23_8 positionX;
    /* 0x4 */ q23_8 positionZ;
    /* 0x8 */ q7_8  groundHeight;
    /* 0xA */ q7_8  topHeight;
    /* 0xC */ q7_8  field_C; // Collision cylinder radius?
    /* 0xE */ s16   field_E;
} s_RayState_6C;

typedef struct
{
    s16 field_0;
    s16 field_2;
} s_RayState_8C;

/** @brief State for an in-progress ray trace. Contains pointers to active characters among other things. */
typedef struct
{
    /* 0x0  */ bool             field_0; // "Use cylinder"?
    /* 0x4  */ s16              field_4; // Collision flags.
    /* 0x6  */ q7_8             field_6;
    /* 0x8  */ q7_8             field_8; // Hit distance? `SHRT_MAX` if no valid hit.
    /* 0xA  */ s8               __pad_A[2];
    /* 0xC  */ q19_12           field_C;  // } Q19.12 `VECTOR3`
    /* 0x10 */ q19_12           field_10; // }
    /* 0x14 */ q19_12           field_14; // }
    /* 0x18 */ s8               unk_18[4];
    /* 0x1C */ q7_8             groundHeight;
    /* 0x1E */ s8               __pad_1E[2];
    /* 0x20 */ s_SubCharacter*  field_20;
    /* 0x24 */ q7_8             field_24;   // X offset.
    /* 0x26 */ q7_8             field_26;   // Z offset.
    /* 0x28 */ s32              groundType; /** `e_GroundType` */
    /* 0x2C */ VECTOR3          from;       // Q23.8
    /* 0x38 */ s8               unk_38[4];
    /* 0x3C */ s32              field_3C; // X  } Q23.8 `VECTOR3`?
    /* 0x40 */ s32              field_40; // Y? }
    /* 0x44 */ s32              field_44; // Z  }
    /* 0x48 */ s8               unk_48[4];
    /* 0x4C */ q7_8             field_4C; // X?
    /* 0x4E */ q7_8             field_4E; // Height offset.
    /* 0x50 */ SVECTOR          offset;   // Q23.8
    /* 0x58 */ u16              field_58; // X
    /* 0x5A */ s16              field_5A; // Z
    /* 0x5C */ q7_8             rayDistance;
    /* 0x5E */ s16              field_5E;
    /* 0x60 */ s16              field_60;
    /* 0x62 */ s8               __pad_62[2];
    /* 0x64 */ s_SubCharacter** collCharas;
    /* 0x68 */ s32              collCharaCount;
    /* 0x6C */ s_RayState_6C    field_6C;
    /* 0x7C */ s32              field_7C;
    /* 0x80 */ s32              field_80;
    /* 0x84 */ u16              field_84;
    /* 0x86 */ u8               __pad_86[2];
    /* 0x88 */ s32              field_88;
    /* 0x8C */ s_RayState_8C    field_8C[1]; // Unknown size.
} s_RayState;

/** @brief Ray trace line of sight info. */
typedef struct _RayTrace
{
    /* 0x0  */ s8              hasHit;     /** `bool` */
    /* 0x1  */ u8              groundType; /** `e_GroundType` */
    /* 0x2  */ s8              __pad_2[2];
    /* 0x4  */ VECTOR3         target; /** Q19.12 */
    /* 0x10 */ s_SubCharacter* character;
    /* 0x14 */ q19_12          hitDistance;
    /* 0x18 */ q19_12          groundHeight;
    /* 0x1C */ q3_12           field_1C; // Angle.
} s_RayTrace;

bool Ray_TraceQuery(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* to);

/** Ray function. */
bool Ray_CharaTraceQuery(s_RayTrace* trace, const VECTOR3* from, VECTOR3* offset, s_SubCharacter* excludedChara);

void Ray_MissSet(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* offset, q23_8 dist);

/** @brief Checks if an obstruction in a ray's line of sight has been hit, ignoring a specified character.
 *
 * @param trace Ray trace.
 * @param from Ray origin.
 * @param offset Ray target offset from origin.
 * @param excludedChara Character to exclude.
 * @return `true` if there is an obstruction, `false` otherwise.
 */
bool Ray_LosHitCheck(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* offset, s_SubCharacter* excludedChara);

bool func_8006DC18(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* offset);

bool Ray_TraceSetup(s_RayState* state, bool useCylinder, q7_8 arg2, const VECTOR3* from, const VECTOR3* offset, q19_12 arg5, q19_12 arg6,
                    s_SubCharacter** collCharas, s32 collCharaCount);

bool Ray_TraceRun(s_RayTrace* trace, s_RayState* state);

// Fills `state` with info.
void func_8006E0AC(s_RayState* state, const s_IpdCollisionData* collData);

void func_8006E150(s_func_8006E490* arg0, DVECTOR arg1, DVECTOR arg2);

void func_8006E490(s_func_8006E490* arg0, u32 flags, q19_12 posX, q19_12 posZ);

void func_8006E53C(s_RayState* state, s_IpdCollSubcellRange* subcellRanges, s_IpdCollisionData* collData);

void func_8006E78C(s_RayState* state, s_IpdCollSubcell* subcell, SVECTOR3* collVerts, s_IpdCollSurface* surfaces, bool hasSurface);

void func_8006EB8C(s_RayState* state, s_IpdCollisionData_18* arg1);

// Fills ray hit data?
void func_8006EE0C(s_RayState_6C* arg0, bool useCylinder, const s_SubCharacter* chara);

void func_8006EEB8(s_RayState* state, s_SubCharacter* chara);

#endif
