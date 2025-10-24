#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s03.h"

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03", D_800C9578);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CD170

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CD608

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CD6E0

#include "maps/shared/Particle_Update.h" // 0x800CD9EC

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CEB24_0_s00); // 0x800CDFAC

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CE358

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CEFD0_1_s02); // 0x800CE4A8

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CFFF8_0_s00); // 0x800CE820

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CE954

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CEA60

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CEB18

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CEBA0

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CED20

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CEDD8

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CEF70

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CEF90

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CF808

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CFBF4

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800D0640

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800D0A84

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800D0AC0

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800D0ACC

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800D0C2C

s32 func_800D0E04()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D0E0C

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D0EBC

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D0ED4

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D0EFC

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D0F14

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800D0F3C

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D0FE0

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D0FF0

void func_800D0FFC() {}

void func_800D1004() {}

void func_800D100C() {}

void func_800D1014() {}

void func_800D101C() {}

s32 func_800D1024()
{
    return 0;
}

void func_800D102C() {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D1034

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D1044

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D1084

#include "maps/shared/Ai_Cybil_Update.h" // 0x800D1098

#include "maps/shared/sharedFunc_800D8888_0_s01.h"

#include "maps/shared/sharedFunc_800D88D0_0_s01.h" // 0x800D1154

#include "maps/shared/sharedSymbol_800D8A68_0_s01.h" // 0x800D12EC

#include "maps/shared/Ai_Cybil_Init.h" // 0x800D232C - Differs to other maps `Ai_Cybil_Init`, possibly `Ai_EndingCybil_Init` if other Cybil funcs are a lot different.

#include "maps/shared/Ai_Dahlia_Update.h" // 0x800D2368

#include "maps/shared/sharedFunc_800CD280_2_s01.h" // 0x800D23DC

#include "maps/shared/sharedFunc_800CD2C8_2_s01.h" // 0x800D2424

#include "maps/shared/sharedSymbol_800CD4A0_2_s01.h" // 0x800D25FC

#include "maps/shared/Ai_Dahlia_Init.h" // 0x800D2ECC

#include "maps/shared/Ai_Alessa_Update.h" // 0x800D2F08

#include "maps/shared/sharedFunc_800CECFC_3_s02.h" // 0x800D2F7C

#include "maps/shared/sharedFunc_800CED44_3_s02.h" // 0x800D2FC4

#include "maps/shared/sharedFunc_800CEEDC_3_s02.h" // 0x800D315C

#include "maps/shared/Ai_Alessa_Init.h" // 0x800D3660

void Ai_BloodyIncubator_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D3684
{
    if (chara->model_0.charaId_0 != Chara_BloodyIncubator)
    {
        Ai_BloodyIncubator_Init(chara);
    }

    func_800D38D8(chara, coords);
    func_800D3740(chara, coords);
    func_800D36F8(chara, anmHdr, coords);
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D36F8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D3740);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D38D8);

void Ai_BloodyIncubator_Init(s_SubCharacter* chara) // 0x800D3BA4
{
    sharedFunc_800D923C_0_s00(chara);
}

void Ai_Incubator_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D3BC4
{
    if (chara->model_0.charaId_0 != Chara_Incubator)
    {
        Ai_Incubator_Init(chara);
    }

    func_800D3E18(chara, coords);
    func_800D3C80(chara, coords);
    func_800D3C38(chara, anmHdr, coords);
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D3C38);

void func_800D3C80(s_SubCharacter* chara, GsCOORDINATE2* coord)
{
    VECTOR3 unused;
    VECTOR3 vec;
    s32     moveSpeed;
    s16     headingAngle;
    s32     moveAmt;
    s32     scaleRestoreShift;
    u32     scaleReduceShift;

    unused       = chara->position_18;
    moveSpeed    = chara->moveSpeed_38;
    headingAngle = chara->headingAngle_3C;
    moveAmt      = FP_MULTIPLY_PRECISE(moveSpeed, g_DeltaTime0, Q12_SHIFT);

    scaleRestoreShift = OVERFLOW_GUARD(moveAmt);
    scaleReduceShift  = scaleRestoreShift >> 1;

    vec.vx = (u32)FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    vec.vz = (u32)FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    vec.vy = FP_MULTIPLY_PRECISE(chara->field_34, g_DeltaTime0, Q12_SHIFT);

    chara->position_18.vx += vec.vx;
    chara->position_18.vy  = 0;
    chara->position_18.vz += vec.vz;

    coord->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coord->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coord->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D3E18);

void Ai_Incubator_Init(s_SubCharacter* chara) // 0x800D3F38
{
    sharedFunc_800D923C_0_s00(chara);
}

#include "maps/shared/Ai_Kaufmann_Update.h" // 0x800D3F58

#include "maps/shared/sharedFunc_800CF290_3_s00.h" // 0x800D3FCC

#include "maps/shared/sharedFunc_800CF2D8_3_s00.h" // 0x800D4014

#include "maps/shared/sharedSymbol_800CF470_3_s00.h" // 0x800D41AC

#include "maps/shared/Ai_Kaufmann_Init.h" // 0x800D4C14
