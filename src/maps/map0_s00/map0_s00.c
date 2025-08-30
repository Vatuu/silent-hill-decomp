#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/map0_s00.h"

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CB6B0);

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CBBBC

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CBC94);

// TODO: .rodata migration.
#ifdef NON_MATCHING
void func_800CBFB0(void) // 0x800CBFB0
{
    VECTOR3 vecs[4] =
    {
        VECTOR3(-258.0f, -1.34f, 244.1f),
        VECTOR3(-254.5f,  0.0f,  220.0f),
        VECTOR3(-249.4f,  0.0f,  219.5f),
        VECTOR3(-250.0f,  0.0f,  217.7f)
    };

    GsInitCoordinate2(NULL, (GsCOORDINATE2*)&g_SysWork.unk_22A8[80]);
    D_800DD594 = 1;
    D_800DD593 = 1;
    D_800E34EC = 20;
    D_800E39AC = 60;
    func_800D0394(2, vecs);
}
#else
INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CBFB0);
#endif

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CC04C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CC6E8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CC8FC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CD1F4);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CD8E8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CE02C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CE544);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CEB24);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CEFF4);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CF7AC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CF974);

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CFFF8

void func_800D0124() {}

bool func_800D012C(VECTOR3* pos) // 0x800D012C
{
    s32 deltaX;
    s32 deltaZ;

    switch (g_SysWork.field_234B_4)
    {
        case 1:
            return true;

        case 2:
            deltaX = FP_METER_TO_COLL(g_SysWork.player_4C.chara_0.position_18.vx - pos->vx);
            deltaZ = FP_METER_TO_COLL(g_SysWork.player_4C.chara_0.position_18.vz - pos->vz);
            return SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)) < FP_METER_COLL(1.0f);
    }

    return false;
}

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800D01BC

void func_800D0274(s32 arg0, s_Particle* part, u16* arg2) // 0x800D0274
{
    s_Particle* partCpy;

    partCpy = part;

    switch (arg0)
    {
        case 0:
            if (D_800DD592 != 0)
            {
                part->type_1F = ParticleType_Snow;
            }
            else
            {
                part->type_1F = ParticleType_Unk1;
            }

            partCpy->position0_0.vy = sharedData_800E323C_0_s00.vy;
            partCpy->movement_18.vz = FP_METER(0.0f);
            partCpy->movement_18.vx = FP_METER(0.0f);
            partCpy->movement_18.vy = FP_METER(0.0245f);

            sharedFunc_800D01BC_0_s00(arg2, part, 5);
            partCpy->position1_C.vz = FP_METER(0.0f);
            partCpy->position1_C.vy = FP_METER(0.0f);
            partCpy->position1_C.vx = FP_METER(0.0f);
            break;

        case 1:
            partCpy->type_1F = ParticleType_Rain;
            partCpy->position0_0.vy = sharedData_800E323C_0_s00.vy + FP_METER(Rng_GenerateInt(Rng_Rand16(), 0, 2));

            partCpy->position1_C.vy = sharedData_800E323C_0_s00.vy;
            partCpy->movement_18.vy = FP_METER(0.03675f);
            sharedFunc_800D01BC_0_s00(arg2, part, 6);
            partCpy->position1_C.vx = partCpy->position0_0.vx;
            partCpy->position1_C.vz = partCpy->position0_0.vz;
            break;
    }

    partCpy->stateStep_1E++;
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0394);

bool func_800D0600() // 0x800D0600
{
    #define FIXED_DIST FP_METER(40.0f)
    
    s32 distX;
    s32 distZ;

    // Check against first position.
    distX = ABS(g_SysWork.player_4C.chara_0.position_18.vx - D_800E32DC.position0_0.vx);
    distZ = g_SysWork.player_4C.chara_0.position_18.vz - D_800E32DC.position0_0.vz;
    if (distZ >= FP_METER(0.0f) && (distX + distZ) < FIXED_DIST)
    {
        goto ret1;
    }
    else if (distZ < FP_METER(0.0f) && (distX + (D_800E32DC.position0_0.vz - g_SysWork.player_4C.chara_0.position_18.vz)) < FIXED_DIST)
    {
        goto ret1;
    }

    // Check against against second position.
    distX = ABS(g_SysWork.player_4C.chara_0.position_18.vx - D_800E32DC.position1_C.vx);
    distZ = g_SysWork.player_4C.chara_0.position_18.vz - D_800E32DC.position1_C.vz;
    if (distZ >= FP_METER(0.0f) && (distX + distZ) < FIXED_DIST)
    {
        goto ret1;
    }
    else if (distZ < FP_METER(0.0f) && (distX + (D_800E32DC.position1_C.vz - g_SysWork.player_4C.chara_0.position_18.vz)) < FIXED_DIST)
    {
        goto ret1;
    }
    else
    {
        // TODO: Ideally would return `false` here, but code matching requires jump to end.
        goto ret0;
    }
    
ret1:
    return true;
ret0:
    return false;
}

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800D0700

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800D08B8

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800D0A60

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800D0B18

#include "maps/shared/sharedFunc_800D0CB8_0_s00.h" // 0x800D0CB8

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800D0E04

void func_800D0E24() {}

void func_800D0E2C() {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0E34);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D1C38);

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800D209C

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800D20D8

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800D20E4

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800D2244

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D23EC);

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D2C7C

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D2D2C

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D2D44

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D2D6C

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D2D84

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800D2DAC

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D2E50

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D2E60

void func_800D2E6C() {}

void func_800D2E74() {}

void func_800D2E7C() {}

void func_800D2E84() {}

void func_800D2E8C() {}

s32 func_800D2E94()
{
    return 0;
}

void func_800D2E9C() {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D2EA4

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D2EB4

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D2EF4
