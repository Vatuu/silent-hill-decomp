#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
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

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800CFBF4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D0640);

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

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedSymbol_800D8A68_0_s01); // 0x800D12EC - Differs from `map0_s01`/`map6_s01` versions, matches `map4_s01`.

#include "maps/shared/Ai_Cybil_Init.h" // 0x800D232C - Differs to other maps `Ai_Cybil_Init`, possibly `Ai_EndingCybil_Init` if other Cybil funcs are a lot different.

#include "maps/shared/Ai_Dahlia_Update.h" // 0x800D2368

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CD280_2_s01); // 0x800D23DC

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CD2C8_2_s01); // 0x800D2424

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03", D_800CAB90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedSymbol_800CD4A0_2_s01); // 0x800D25FC

#include "maps/shared/Ai_Dahlia_Init.h" // 0x800D2ECC

#include "maps/shared/Ai_Alessa_Update.h" // 0x800D2F08

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CECFC_3_s02); // 0x800D2F7C

#include "maps/shared/sharedFunc_800CED44_3_s02.h" // 0x800D2FC4

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CEEDC_3_s02); // 0x800D315C

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

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedSymbol_800CF470_3_s00); // 0x800D41AC

#include "maps/shared/Ai_Kaufmann_Init.h" // 0x800D4C14

#include "maps/shared/Ai_BloodyLisa_Update.h" // 0x800D4C50

#include "maps/shared/sharedFunc_800D595C_7_s01.h" // 0x800D4CC4

#include "maps/shared/sharedFunc_800D59A4_7_s01.h" // 0x800D4D0C

#include "maps/shared/sharedFunc_800D5B3C_7_s01.h" // 0x800D4EA4

#include "maps/shared/Ai_BloodyLisa_Init.h" // 0x800D501C

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D5040

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D5054

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D5098

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D50B0

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D50BC

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D50D0

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D50E4

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D50F8

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800D5234

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D5898

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D58AC

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D58C0

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D59BC

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D5AA8

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D5B68

void Ai_LittleIncubus_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D5BC8
{
    s32         temp_s0;
    s32         var_a2;
    s_AnimInfo* animInfo;

    if (chara->model_0.state_2 == 0)
    {
        chara->model_0.anim_4.alpha_A = Q12(0.0f);
        chara->model_0.state_2        = 1;
        chara->model_0.stateStep_3    = 0;
        Character_AnimSet(chara, ANIM_STATUS(1, true), 0);

        D_800EDA00 = 0;
    }

    D_800EDA00 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 10.0f, Q12_SHIFT);
    var_a2 = FP_TO(D_800EDA00, Q12_SHIFT) / Q12(80.0f);

    temp_s0 = var_a2;

    if (var_a2 > Q12(1.0f))
    {
        var_a2 = Q12(1.0f);
    }

    temp_s0 = Math_Sin(var_a2 >> 2);

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coords);

    animInfo = &LITTLE_INCUBUS_ANIM_INFOS[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);

    func_800705E4(coords, 1, temp_s0, temp_s0, temp_s0);
    func_800705E4(coords, 7, temp_s0, temp_s0, temp_s0);
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D5D24);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D5D48);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D5E78);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D5EC0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D600C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D60E4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D621C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D625C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D6548);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D663C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D6690);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D6750);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D6788);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D6804);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D68C4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D6A10);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D6ADC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D6BCC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D6C0C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D6EF8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D6FA0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D6FF4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D70B4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D70EC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7144);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D71A4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D71B0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D74F4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D75D0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D77A4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D77E4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7AD0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7B78);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7BF4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7CB4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7CEC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7CF8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7D08);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7D74);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7E50);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7ED0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7EF0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7F10);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7F20);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D7F2C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D822C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D82AC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D8438);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D8454);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D8738);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D87D4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D8858);

void func_800D88C4() {}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D88CC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D88D8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D88E8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D8954);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D8CD4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D8D90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D905C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D90C8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D9114);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D917C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D9394);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D947C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D952C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D95D4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D9740);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D982C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D997C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D9AA0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D9B90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D9C20);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D9DF8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DA04C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DA08C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DA178);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DA1F4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DA420);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DA4B4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DA4EC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DA550);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DA774);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DA884);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DA9F8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DAB18);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DAC04);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DACFC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DAD54);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DAD90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DADE0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DB154);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DB288);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CD6B0_3_s03); // 0x800DB338

#include "maps/shared/sharedFunc_800CD7F8_3_s03.h" // 0x800DB480

#include "maps/shared/sharedFunc_800CD920_3_s03.h" // 0x800DB5A8

#include "maps/shared/sharedFunc_800CD940_3_s03.h" // 0x800DB5C8

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DB608);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DB6D0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DBA08);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DBABC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DBAE8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DBBA0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DBBD8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DBC18);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DBCA4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DBD94);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DC3EC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DC49C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DC544);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DC650);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03", D_800CAE30);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03", D_800CAE3C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DC6DC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DCD94);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DCDDC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DCF94);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DCFF8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD044);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD090);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD0EC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD240);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD260);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD2C8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD32C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD3D4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD464);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD4CC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD594);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD62C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD67C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD6CC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD738);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD7D0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD868);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD8CC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD964);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD98C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD9B0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD9D4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DD9F8);

bool Ai_Incubus_Init(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800DDA1C
{
    u8              curStateStep;
    s_SubCharacter* localChara; // TODO: Not sure why this is needed here, could be an inline in this func.

    chara->model_0.anim_4.alpha_A = Q12(0.0f);
    localChara                    = chara;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        chara->health_B0 = Q12(30000.0f);
    }
    else
    {
        chara->health_B0 = Q12(40000.0f);
    }

    chara->moveSpeed_38       = 0;
    chara->headingAngle_3C    = chara->rotation_24.vy;
    chara->field_D4           = Q12(0.3f);
    chara->field_E1_0         = 4;
    chara->field_D8.offsetX_4 = Q12(0.0f);
    chara->field_D8.offsetZ_6 = Q12(0.0f);
    chara->flags_3E          |= CharaFlag_Unk3;

    localChara->properties_E4.larvalStalker.properties_E8[2].val32 = 0;
    localChara->properties_E4.larvalStalker.properties_E8[1].val32 = 0;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        localChara->properties_E4.larvalStalker.properties_E8[3].val32 = Q12(300.0f);
    }
    else
    {
        localChara->properties_E4.larvalStalker.properties_E8[3].val32 = Q12(30.0f);
    }

    curStateStep = chara->model_0.stateStep_3;

    if (curStateStep != 0)
    {
        chara->model_0.stateStep_3 = 0;
        chara->model_0.state_2     = curStateStep;
    }
    else
    {
        chara->model_0.state_2     = 1;
        chara->model_0.stateStep_3 = 0;
    }

    Character_AnimSet(chara, ANIM_STATUS(3, false), 338);
    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, INCUBUS_ANIM_INFOS);

    chara->damageReceived_C0 = Q12(0.0f);
    chara->field_BC          = 0;
    chara->field_B8          = 0;
    chara->field_B4          = 0;

    chara->flags_3E |= CharaFlag_Unk9;

    return true;
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DDB3C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DDB68);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DDBA4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DDBBC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DDCC4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DDDB0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DDDD8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DDEEC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DDF14);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03", D_800CAEAC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DDF3C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DE2A4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DE68C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DEA54);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DEA90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DEAF4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DEBA8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DEC38);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DEC74);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DED68);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DEE44);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DEE90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DEF50);

void func_800DEFE8(s_SubCharacter* chara, GsCOORDINATE2* coord) // 0x800DEFE8
{
    s32 yPos;

    if (chara->model_0.anim_4.flags_2 & AnimFlag_Visible)
    {
        func_800DEF50();
        return;
    }

    yPos            = chara->position_18.vy;
    chara->field_CA = yPos;
    chara->field_CC = yPos;
    chara->field_C8 = yPos - Q12(1.0f);
    chara->field_CE = yPos - Q12(0.5f);
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DF044);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DF074);

void Ai_Incubus_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800DF0D8
{
    if ((chara->model_0.state_2 != 0 || Ai_Incubus_Init(chara, coords)) && chara->model_0.state_2 != 1)
    {
        if (g_DeltaTime0 != Q12(0.0))
        {
            func_800DDBBC(chara);
            func_800DEC74(chara, coords);
            func_800DF044(chara, coords);
            func_800DEE44(chara);
            func_800DEE90(chara, anmHdr, coords);
            func_800DEFE8(chara, coords);
            func_800DED68(chara, coords);
            func_800DF074(chara);
            func_800DD98C(chara->flags_3E & CharaFlag_Unk2);
        }
        else
        {
            func_800DEE90(chara, anmHdr, coords);
            func_800DB608();
            func_800DF074(chara);
        }
    }
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DF1D4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DF288);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DF348);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DF418);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DF458);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DF750);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DF7F8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DF84C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DF90C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DF944);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DFA14);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DFA48);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DFB04);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DFB2C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DFB50);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DFB74);

bool Ai_Unknown23_Init(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800DFB98
{
    s_SubCharacter* localChara; // TODO: Not sure why this is needed here, might be an inline in this func.

    localChara = chara;

    chara->model_0.anim_4.alpha_A = Q12(0.0f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        chara->health_B0 = Q12(17995.605f); // TODO: Some percentage taken from 30000?
    }
    else
    {
        chara->health_B0 = Q12(30000.0f);
    }

    chara->moveSpeed_38       = 0;
    chara->field_D4           = Q12(0.3f);
    chara->field_D8.offsetX_4 = Q12(0.0f);
    chara->field_D8.offsetZ_6 = Q12(0.0f);
    chara->field_E1_0         = 4;
    chara->headingAngle_3C    = chara->rotation_24.vy;
    chara->flags_3E          |= CharaFlag_Unk3;

    localChara->properties_E4.player.field_F0 = 0;

    if (chara->model_0.stateStep_3 == 0)
    {
        chara->model_0.state_2     = 1;
        chara->model_0.stateStep_3 = 0;
    }
    else
    {
        chara->model_0.state_2     = chara->model_0.stateStep_3;
        chara->model_0.stateStep_3 = 0;
    }

    Character_AnimSet(chara, ANIM_STATUS(2, false), 115);
    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, UNKKOWN_23_ANIM_INFOS);

    chara->damageReceived_C0 = Q12(0.0f);
    chara->field_BC          = 0;
    chara->field_B8          = 0;
    chara->field_B4          = 0;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        localChara->properties_E4.player.field_F4 = Q12(300.0f);
    }
    else
    {
        localChara->properties_E4.player.field_F4 = Q12(30.0f);
    }

    func_800DD67C(&chara->position_18, chara, coords);
    func_800DFA14();

    chara->flags_3E |= CharaFlag_Unk9;
    return true;
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DFCE4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DFE10);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DFEF0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DFF28);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DFF44);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DFF60);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E04C4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E0528);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E05DC);

void func_800E0670(s_SubCharacter* chara, GsCOORDINATE2* coord) // 0x800E0670
{
    s32 dist;

    func_800DB608();

    if (chara->model_0.state_2 == 3)
    {
        func_800DFF60(chara, coord);
    }

    dist = Math_Vector2MagCalc(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                               g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);
    if (dist < Q12(2.5f) && func_800DFB04() == 0)
    {
        func_800DFA48(&g_SysWork.player_4C.chara_0.position_18, &chara->position_18);
    }
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E0728);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E0774);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E07F0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E0888);

void func_800E08E4(s_SubCharacter* chara, GsCOORDINATE2* coord) // 0x800E08E4
{
    if (chara->model_0.stateStep_3 == 0)
    {
        func_800E05DC(chara, coord);
    }
}

void func_800E0914(s_SubCharacter* chara) // 0x800E0914
{
    func_800DD6CC();
    func_800DF944();
}

void Ai_Unknown23_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800E093C
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Unknown23_Init(chara, coords);
    }

    if (chara->model_0.state_2 != 1)
    {
        if (g_DeltaTime0 != Q12(0.0))
        {
            func_800DFCE4(chara);
            func_800E05DC(chara, coords);
            func_800E08E4(chara, coords);
            func_800E0728(chara);
            func_800E0774(chara, anmHdr, coords);
            func_800E0888(chara, coords);
            func_800E0670(chara, coords);
            func_800E0914(chara);
            func_800DFB2C(chara->flags_3E & CharaFlag_Unk2);
        }
        else
        {
            func_800DB608();
            func_800E0914(chara);
            func_800E0774(chara, anmHdr, coords);
        }
    }
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E0A34);

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800E0A80

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E0A90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E0B28);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E0B5C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E0B90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E0C10);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E0C50);

void func_800E14D4() {}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E14DC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E16FC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E1788);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E17B8);

const char* MAP_MESSAGES[] =
{
    #include "maps/shared/mapMsg_common.h"
    "~J1(4.9)\tI_was_shocked_to_realize ~N\n\t\t\tthe_talisman_of_Metraton ~N\n\t\t\twas_being_used. ",
    "~J1(4.0)\tIn_spite_of_the_lost_soul ~N\n\t\t\treturning_at_last, ",
    "~J1(4.3)\tJust_a_little_longer_and_all ~N\n\t\t\twould_have_been_for_naught. ",
    "~J1(7.0)\tIt's_all_because_of_that_man. ~N\n\t\t\tWe_must_be_thankful_to_him. ",
    "~J1(3.2)\tEven_though_Alessa ~N\n\t\t\thas_been_stopped, ",
    "~J1(8.5)\this_little_girl_still_has_to_go. ~N\n\t\t\tWhat_a_pity... ~E ",
    "~J0(1.2)\tFreeze! ~E ",
    "~J0(2.6)\tWhat_in_the_devil's_name...! ~E ",
    "~J0(1.1)\t~E ",
    "~J1(1.1)\tDahlia! ",
    "~J1(5.6)\tWell,_well,_well. ~N\n\t\t\tTo_think_you'd_make_it_this_far. ",
    "~J1(2.5)\tWhere's_Cheryl!? ~N\n\t\t\tWhat_have_you_done_to_her!? ",
    "~J1(2.0)\tWhat_are_you_talking_about? ",
    "~J1(4.8)\tYou've_seen_her_many_times. ~N\n\t\t\tRestored_to_her_former_self. ",
    "~J1(2.4)\tI'm_in_no_mood_for_jokes. ~E ",
    "~J0(3.4)\tDon't_you_see? ~N\n\t\t\tShe's_right_there. ~E ",
    "~J1(1.8)\tThat's_absurd. ",
    "~J1(4.5)\tYou_are_the_only_one ~N\n\t\t\twho_thinks_so. ",
    "~J1(1.4)\tWhy? ",
    "~J1(2.2)\tWhy_are_you_doing_this? ~E ",
    "~J1(3.8)\tIt's_been_a_long_seven_years... ",
    "~J1(4.4)\tFor_the_seven_years ~N\n\t\t\tsince_that_terrible_day, ",
    "~J1(3.2)\tAlessa_has_been_kept_alive, ",
    "~J1(3.9)\tsuffering_a_fate_worse ~N\n\t\t\tthan_death. ",
    "~J1(6.5)\tAlessa_has_been_trapped ~N\n\t\t\tin_an_endless_nightmare ~N\n\t\t\tfrom_which_she_never_wakens. ",
    "~J1(4.0)\tHe_has_been_nurtured ~N\n\t\t\tby_that_nightmare. ",
    "~J1(3.6)\tWaiting_for ~N\n\t\t\tthe_day_to_be_born. ",
    "~J1(3.6)\tThat_day_has_finally_come. ",
    "~J1(2.9)\tThe_time_is_neigh. ~E ",
    "~J1(5.1)\tEveryone_will_be_released, ~N\n\t\t\tfrom_pain_and_suffering. ",
    "~J1(3.1)\tOur_salvation_is_at_hand. ",
    "~J1(2.8)\tThis_is_the_day_of_reckoning. ",
    "~J1(4.7)\tWhen_all_our_sorrows ~N\n\t\t\twill_be_washed_away. ",
    "~J1(4.8)\tWhen_we_return_to ~N\n\t\t\tthe_true_paradise!  ~E ",
    "~J0(6.2)\tMy_daughter_will_be ~N\n\t\t\tthe_mother_of_God! ~E ",
    "~J0(4.0)\t~E ",
    "~J1(1.7)\tQuit_screwing_around! ",
    "~J1(2.4)\tReturn_things_to_how ~N\n\t\t\tthey_were_before! ",
    "~J1(1.0)\tKaufmann! ",
    "~J1(1.9)\tDid_I_ask_for_this! ",
    "~J1(1.9)\tNobody_uses_me! ",
    "~J1(3.0)\tYou_won't_get_away ~N\n\t\t\twith_this! ~E ",
    "~J1(4.7)\tYour_role_is_over. ~N\n\t\t\tWe_don't_need_you_anymore. ",
    "~J1(3.6)\tWhat_do_you_think_you_can ~N\n\t\t\taccomplish_by_coming_here? ",
    "~J1(3.5)\tMy,_aren't_we_getting_cocky? ",
    "~J1(3.2)\tBet_you_can't_see_this ~N\n\t\t\tand_keep_your_cool.  ~E ",
    "~J0(3.5)\tAglaophotis! ~N\n\t\t\tI_thought_I_got_rid_of_that! ",
    "~J0(3.2)\tAll_I_had_to_do_was_plant_it ~N\n\t\t\tsomewhere_for_you_to_find, ",
    "~J0(3.9)\tYou_all,_well, ~N\n\t\t\tit_kept_you_busy. ",
    "~J0(1.7)\tYou're_easy! ",
    "~J0(2.4)\tAnd_there's_more ~N\n\t\t\twhere_this_came_from! ~E ",
    "~J0(1.7)\tStop_it!!  ~E ",
    "~J0(2.2)\t~E ",
    "~J0(1.4)\t",
    "~J2(1.2)\tWhat_the!? ~E ",
    "~J0(10.4)\t~E ",
    "~J0(3.0)\tWhat_on_earth? ~N\n\t\t\tThat's_not_supposed_to... ~E ",
    "~J0(1.8)\t~E ",
    "~J0(3.5)\t~E ",
    "~J0(3.4)\tIt's_awakening! ~N\n\t\t\tIt's_awake! ",
    "~J0(3.0)\tNow_no_one_can_interfere! ~E ",
    "~J0(1.2)\tCheryl!! ",
    "~J0(3.5)\tGive_up! ~N\n\t\t\tThat_person_no_longer_exists. ~E ",
    "~J0(2.0)\tThis_is_a_God! ",
    "~J2(4.9)\tDescended_among_us_to_reach_out ~N\n\t\t\tand_save_us! ~E ",
    "~J0(13.2)\t_ ~E ",
    "~J0(2.4)\t_ ~E ",
    "~J0(1.3)\t_",
    "~J0(1.1)\t_ ~E ",
    "~J0(1.6)\tThank_you_daddy. ",
    "~J0(1.4)\tGoodbye. ~E ",
    "~J0(3.0)\tCheryl...? ~E ",
    "~J0(2.3)\tCan't_be? ",
    "~J0(2.2)\tYou_can't_leave_like_this... ",
    "~J0(3.2)\tThis_can't_be_happening! ~N\n\t\t\tCheryl!? ~E ",
    "~J0(1.4)\t...Cheryl!! ~E ",
    "~J0(1.1)\t~E ",
    "~J0(3.9)\t~E ",
    "~J0(1.3)\tWait... ~E ",
    "~J0(4.8)\t~E ",
    "~J0(1.0)\t~E ",
    "~J0(1.0)\t~E ",
    "~J0(4.5)\t~E ",
    "~J0(1.4)\tHarry. ",
    "~J0(1.0)\tGo. ~E "
};

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E1854);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E1FE0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E20A4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E22AC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E2444);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E24A0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E2664);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E27D0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E28F4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E2968);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E2C28);

#include "maps/shared/sharedFunc_800DA8E8_0_s01.h" // 0x800E2DF8

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E2E90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E3390);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E3B6C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E3C48);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E3D18);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E3E84);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E3F30);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E4714);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E514C);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03", D_800CC348);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E62CC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E70F0);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03", D_800CC5C8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E7380);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03", D_800CC63C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E787C);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03", D_800CCD20);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E86BC);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03", D_800CCE80);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E8D20);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E9260);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E941C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E9444);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E9490);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E9498);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E94AC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E94C0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E94F4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E9528);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E972C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E9874);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E98EC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E9AC8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E9C28);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03", D_800CD168);
