#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s03.h"

#include <limits.h>

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800CD170);

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CD608

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800CD6E0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800CD9EC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800CDFAC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800CE358);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800CE4A8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800CE820);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800CE954);

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CEA60

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800CEB18);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800CEBA0);

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CED20

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800CEDD8);

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CEF70

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800CEF90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800CF808);

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

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800D8888_0_s01); // 0x800D110C

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800D88D0_0_s01); // 0x800D1154

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedSymbol_800D8A68_0_s01); // 0x800D12EC - Differs from `map0_s01`/`map6_s01` versions, matches `map4_s01`.

#include "maps/shared/Ai_Cybil_Init.h" // 0x800D232C - Differs to other maps `Ai_Cybil_Init`, possibly `Ai_EndingCybil_Init` if other Cybil funcs are a lot different.

#include "maps/shared/Ai_Dahlia_Update.h" // 0x800D2368

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CD280_2_s01); // 0x800D23DC

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CD2C8_2_s01); // 0x800D2424

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedSymbol_800CD4A0_2_s01); // 0x800D25FC

#include "maps/shared/Ai_Dahlia_Init.h" // 0x800D2ECC

#include "maps/shared/Ai_Alessa_Update.h" // 0x800D2F08

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CECFC_3_s02); // 0x800D2F7C

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CED44_3_s02); // 0x800D2FC4

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CEEDC_3_s02); // 0x800D315C

#include "maps/shared/Ai_Alessa_Init.h" // 0x800D3660

void Ai_BloodyIncubator_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords) // 0x800D3684
{
    if (chara->model_0.charaId_0 != Chara_BloodyIncubator)
    {
        Ai_BloodyIncubator_Init(chara);
    }

    func_800D38D8(chara, coords);
    func_800D3740(chara, coords);
    func_800D36F8(chara, arg1, coords);
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D36F8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D3740);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D38D8);

void Ai_BloodyIncubator_Init(s_SubCharacter* chara) // 0x800D3BA4
{
    sharedFunc_800D923C_0_s00(chara);
}

void Ai_Incubator_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords) // 0x800D3BC4
{
    if (chara->model_0.charaId_0 != Chara_Incubator)
    {
        Ai_Incubator_Init(chara);
    }

    func_800D3E18(chara, coords);
    func_800D3C80(chara, coords);
    func_800D3C38(chara, arg1, coords);
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D3C38);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D3C80);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D3E18);

void Ai_Incubator_Init(s_SubCharacter* chara) // 0x800D3F38
{
    sharedFunc_800D923C_0_s00(chara);
}

#include "maps/shared/Ai_Kaufmann_Update.h" // 0x800D3F58

#include "maps/shared/sharedFunc_800CF290_3_s00.h" // 0x800D3FCC

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800CF2D8_3_s00); // 0x800D4014

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedSymbol_800CF470_3_s00); // 0x800D41AC

#include "maps/shared/Ai_Kaufmann_Init.h" // 0x800D4C14

#include "maps/shared/Ai_BloodyLisa_Update.h" // 0x800D4C50

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800D595C_7_s01); // 0x800D4CC4

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

// TODO: Requires rodata for jump table
// #include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D50F8
INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800D8964_0_s00); // 0x800D50F8

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800D5234);

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D5898

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D58AC

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D58C0

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D59BC

// TODO: Requires rodata for jump table
// #include "maps/shared/sharedFunc_800D921C_0_s00.h" // 0x800D5AA8
INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", sharedFunc_800D921C_0_s00); // 0x800D5AA8

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D5B68

void Ai_LittleIncubus_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords) // 0x800D5BC8
{
    s32         temp_s0;
    s32         var_a2;
    s_AnimInfo* animInfo;

    if (chara->model_0.state_2 == 0)
    {
        chara->model_0.anim_4.keyframeIdx1_A = 0;
        chara->model_0.state_2               = 1;
        chara->model_0.stateStep_3           = 0;
        chara->model_0.anim_4.animIdx_0      = 3;
        chara->model_0.anim_4.time_4         = 0;
        chara->model_0.anim_4.keyframeIdx0_8 = 0;

        D_800EDA00 = 0;
    }

    D_800EDA00 += FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 10.0f, Q12_SHIFT);
    var_a2 = FP_TO(D_800EDA00, Q12_SHIFT) / FP_TO(80, Q12_SHIFT);

    temp_s0 = var_a2;

    if (var_a2 > FP_TO(1, Q12_SHIFT))
    {
        var_a2 = FP_TO(1, Q12_SHIFT);
    }

    temp_s0 = shRsin(var_a2 >> 2);

    func_80035B04(&chara->position_18, &chara->rotation_24, coords);

    animInfo = &g_Ai_LittleIncubus_AnimInfo[chara->model_0.anim_4.animIdx_0];
    animInfo->funcPtr_0(chara, arg1, coords, animInfo);

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

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DB338);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DB480);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DB5A8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DB5C8);

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

s32 Ai_Incubus_Init(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800DDA1C
{
    u8              curStateStep;
    s_SubCharacter* chara2; // TODO: Not sure why this is needed here, could be an inline in this func.

    chara->model_0.anim_4.keyframeIdx1_A = 0;
    chara2                               = chara;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        chara->health_B0 = FP_TO(30000, Q12_SHIFT);
    }
    else
    {
        chara->health_B0 = FP_TO(40000, Q12_SHIFT);
    }

    chara->moveSpeed_38    = 0;
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->field_D4        = FP_FLOAT_TO(0.3f, Q12_SHIFT);
    chara->field_E0_8      = 4;
    chara->field_DC        = 0;
    chara->field_DE        = 0;
    chara->flags_3E       |= CharaFlag_Unk3;

    chara2->properties_E4.larvalStalker.properties_E8[2].val32 = 0;
    chara2->properties_E4.larvalStalker.properties_E8[1].val32 = 0;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        chara2->properties_E4.larvalStalker.properties_E8[3].val32 = FP_TO(300, Q12_SHIFT);
    }
    else
    {
        chara2->properties_E4.larvalStalker.properties_E8[3].val32 = FP_TO(30, Q12_SHIFT);
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

    chara->model_0.anim_4.animIdx_0      = 6;
    chara->model_0.anim_4.time_4         = FP_TO(338, Q12_SHIFT);
    chara->model_0.anim_4.keyframeIdx0_8 = 338;

    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, g_Ai_Incubus_AnimInfo);

    chara->field_C0 = 0;
    chara->field_BC = 0;
    chara->field_B8 = 0;
    chara->field_B4 = 0;

    chara->flags_3E |= CharaFlag_Unk9;

    return 1;
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

    if (chara->model_0.anim_4.flags_2 & AnimFlag_Unk2)
    {
        func_800DEF50();
        return;
    }

    yPos            = chara->position_18.vy;
    chara->field_CA = yPos;
    chara->field_CC = yPos;
    chara->field_C8 = yPos - FP_METER(1.0f);
    chara->field_CE = yPos - FP_METER(0.5f);
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DF044);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800DF074);

void Ai_Incubus_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords) // 0x800DF0D8
{
    if ((chara->model_0.state_2 != 0 || Ai_Incubus_Init(chara, coords)) && chara->model_0.state_2 != 1)
    {
        if (g_DeltaTime0 != 0)
        {
            func_800DDBBC(chara);
            func_800DEC74(chara, coords);
            func_800DF044(chara, coords);
            func_800DEE44(chara);
            func_800DEE90(chara, arg1, coords);
            func_800DEFE8(chara, coords);
            func_800DED68(chara, coords);
            func_800DF074(chara);
            func_800DD98C(chara->flags_3E & CharaFlag_Unk2);
        }
        else
        {
            func_800DEE90(chara, arg1, coords);
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

s32 Ai_Unknown23_Init(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800DFB98
{
    s_SubCharacter* chara2; // TODO: Not sure why this is needed here, might be an inline in this func.

    chara2 = chara;

    chara->model_0.anim_4.keyframeIdx1_A = 0;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        chara->health_B0 = FP_FLOAT_TO(17995.605f, Q12_SHIFT); // Some percentage taken from 30000?
    }
    else
    {
        chara->health_B0 = FP_FLOAT_TO(30000.f, Q12_SHIFT);
    }

    chara->moveSpeed_38    = 0;
    chara->field_D4        = FP_FLOAT_TO(0.3f, Q12_SHIFT);
    chara->field_DC        = 0;
    chara->field_DE        = 0;
    chara->field_E0_8      = 4;
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->flags_3E       |= CharaFlag_Unk3;

    chara2->properties_E4.player.properties_E4[3] = 0;

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

    chara->model_0.anim_4.animIdx_0      = 4;
    chara->model_0.anim_4.keyframeIdx0_8 = 115;
    chara->model_0.anim_4.time_4         = FP_TO(115, Q12_SHIFT);

    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, g_Ai_Unknown23_AnimInfo);

    chara->field_C0 = 0;
    chara->field_BC = 0;
    chara->field_B8 = 0;
    chara->field_B4 = 0;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        chara2->properties_E4.player.properties_E4[4] = FP_TO(300, Q12_SHIFT);
    }
    else
    {
        chara2->properties_E4.player.properties_E4[4] = FP_TO(30, Q12_SHIFT);
    }

    func_800DD67C(&chara->position_18, chara, coords);
    func_800DFA14();

    chara->flags_3E |= CharaFlag_Unk9;
    return 1;
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
    s32 xDelta;
    s32 zDelta;

    func_800DB608();

    if (chara->model_0.state_2 == 3)
    {
        func_800DFF60(chara, coord);
    }

    xDelta = (g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx) >> 6;
    zDelta = (g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) >> 6;
    if ((SquareRoot0(SQUARE(xDelta) + SQUARE(zDelta)) << 6) < FP_METER(2.5f) && func_800DFB04() == 0)
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

void Ai_Unknown23_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords) // 0x800E093C
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Unknown23_Init(chara, coords);
    }

    if (chara->model_0.state_2 != 1)
    {
        if (g_DeltaTime0 != 0)
        {
            func_800DFCE4(chara);
            func_800E05DC(chara, coords);
            func_800E08E4(chara, coords);
            func_800E0728(chara);
            func_800E0774(chara, arg1, coords);
            func_800E0888(chara, coords);
            func_800E0670(chara, coords);
            func_800E0914(chara);
            func_800DFB2C(chara->flags_3E & CharaFlag_Unk2);
        }
        else
        {
            func_800DB608();
            func_800E0914(chara);
            func_800E0774(chara, arg1, coords);
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

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E2DF8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E2E90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E3390);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E3B6C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E3C48);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E3D18);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E3E84);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E3F30);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E4714);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E514C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E62CC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E70F0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E7380);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E787C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03", func_800E86BC);

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
