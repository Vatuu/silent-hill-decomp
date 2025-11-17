#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s03.h"
#include "maps/characters/Chara_Alessa.h"
#include "maps/characters/Chara_BloodyLisa.h"
#include "maps/characters/Chara_Cybil.h"
#include "maps/characters/Chara_Dahlia.h"
#include "maps/characters/Chara_Kaufmann.h"

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

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D5D24);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D5D48);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D5E78);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D5EC0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D600C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D60E4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D621C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D625C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D6548);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D663C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D6690);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D6750);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D6788);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D6804);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D68C4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D6A10);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D6ADC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D6BCC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D6C0C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D6EF8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D6FA0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D6FF4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D70B4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D70EC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D7144);

void func_800D71A4(s32 arg0) // 0x800D71A4
{
    D_800F2430 = arg0;
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D71B0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D74F4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D75D0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D77A4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D77E4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D7AD0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D7B78);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D7BF4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D7CB4);

void func_800D7CEC(void) // 0x800D7CEC
{
    D_800F2434 = 0;
}

void func_800D7CF8(void) // 0x800D7CF8
{
    D_800F2434 = 1;
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D7D08);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D7D74);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D7E50);

void func_800D7ED0(void) // 0x800D7ED0
{
    func_800D7B78();
}

void func_800D7EF0(void) // 0x800D7D08
{
    func_800D7D08();
}

PACKET* func_800D7F10(void) // 0x800D7F10
{
    return GsOUT_PACKET_P;
}

void func_800D7F20(u8* arg0) // 0x800D7F20
{
    GsOUT_PACKET_P = arg0;
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D7F2C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D822C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D82AC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D8438);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D8454);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D8738);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D87D4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D8858);

void func_800D88C4(void) // 0x800D88C4
{
}

void func_800D88CC(void) // 0x800D88CC
{
    D_800F3D8C = 0;
}

void func_800D88D8(void) // 0x800D88D8
{
    D_800F3D8C = 1;
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D88E8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D8954);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D8CD4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D8D90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D905C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D90C8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D9114);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D917C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D9394);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D947C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D952C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D95D4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D9740);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D982C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D997C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D9AA0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D9B90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D9C20);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800D9DF8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DA04C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DA08C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DA178);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DA1F4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DA420);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DA4B4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DA4EC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DA550);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DA774);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DA884);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DA9F8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DAB18);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DAC04);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DACFC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DAD54);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DAD90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DADE0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DB154);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DB288);

#include "maps/shared/sharedFunc_800CD6B0_3_s03.h" // 0x800DB338

#include "maps/shared/sharedFunc_800CD7F8_3_s03.h" // 0x800DB480

#include "maps/shared/sharedFunc_800CD920_3_s03.h" // 0x800DB5A8

#include "maps/shared/sharedFunc_800CD940_3_s03.h" // 0x800DB5C8

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DB608);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DB6D0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DBA08);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DBABC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DBAE8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DBBA0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DBBD8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DBC18);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DBCA4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DBD94);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DC3EC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DC49C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DC544);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DC650);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03_2", D_800CAE30);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03_2", D_800CAE3C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DC6DC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DCD94);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DCDDC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DCF94);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DCFF8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD044);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD090);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD0EC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD240);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD260);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD2C8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD32C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD3D4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD464);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD4CC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD594);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD62C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD67C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD6CC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD738);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD7D0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD868);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD8CC);

u8 func_800DD964(void) // 0x8007F250
{
    u8 sp10;

    func_8007F250(&sp10, 0);
    return sp10;
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD98C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD9B0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD9D4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DD9F8);

bool Ai_Incubus_Init(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800DDA1C
{
    u8              activeStateStep;
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

    activeStateStep = chara->model_0.stateStep_3;
    if (activeStateStep != 0)
    {
        chara->model_0.stateStep_3 = 0;
        chara->model_0.state_2     = activeStateStep;
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

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DDB3C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DDB68);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DDBA4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DDBBC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DDCC4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DDDB0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DDDD8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DDEEC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DDF14);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03_2", D_800CAEAC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DDF3C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DE2A4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DE68C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DEA54);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DEA90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DEAF4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DEBA8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DEC38);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DEC74);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DED68);

void func_800DEE44(s_SubCharacter* chara) // 0x800DEE44
{
    s_800C4590 sp10;

    chara->field_34 += g_DeltaTime2;

    func_8005C944(chara, &sp10);

    chara->rotation_24.vy = func_8005BF38(chara->rotation_24.vy);
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DEE90);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DEF50);

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

void func_800DF044(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800DF044
{
    if (chara->model_0.stateStep_3 == 0)
    {
        func_800DEC74(chara, coords);
    }
}

void func_800DF074(s_SubCharacter* chara) // 0x800DF074
{
    u8 charaState;

    charaState = chara->model_0.state_2;
    if (charaState != 2 && charaState != 4 && charaState != 13 && charaState != 3 && charaState != 5 && (chara->properties_E4.player.positionY_EC & (1 << 2)))
    {
        func_800DD6CC();
    }
}

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

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DF1D4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DF288);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DF348);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DF418);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DF458);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DF750);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DF7F8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DF84C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DF90C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DF944);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DFA14);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DFA48);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DFB04);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DFB2C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DFB50);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DFB74);

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

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DFCE4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DFE10);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DFEF0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DFF28);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DFF44);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800DFF60);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E04C4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E0528);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E05DC);

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

void func_800E0728(s_SubCharacter* chara) // 0x800E0728
{
    s_800C4590 sp10;

    chara->field_34 += g_DeltaTime2;
    func_8005C944(chara, &sp10);
    chara->rotation_24.vy = func_8005BF38(chara->rotation_24.vy);
}

void func_800E0774(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800E0774
{
    s_AnimInfo* animInfo;

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coords);

    if (chara->model_0.anim_4.status_0 != ANIM_STATUS(0, false))
    {
        animInfo = &UNKKOWN_23_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
    }
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E07F0);

void func_800E0888(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800E0888
{
    q19_12 posY;

    if (chara->model_0.anim_4.flags_2 & AnimFlag_Visible)
    {
        func_800E07F0();
        return;
    }

    posY            = chara->position_18.vy;
    chara->field_CA = posY;
    chara->field_CC = posY;
    chara->field_C8 = posY - Q12(1.0f);
    chara->field_CE = posY - Q12(0.5f);
}

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

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E0A34);

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800E0A80

#include "maps/shared/Map_RoomIdxGet.h" // 0x800E0A90

void func_800E0B28(s32 arg0) // 0x800E0B28
{
    (arg0 != 0) ? func_800E0B90() : func_800E0C50();
}

void func_800E0B5C(s32 arg0) // 0x800E0B5C
{
    (arg0 != 0) ? func_800E0C10() : func_800E0C50();
}

void func_800E0B90(void) // 0x800E0B90
{
    s32 var_a0;

    if (g_SavegamePtr->mapRoomIdx_A5 == 3)
    {
        var_a0 = 15;
    }
    else if (Savegame_EventFlagGet(EventFlag_481))
    {
        if (!Savegame_EventFlagGet(EventFlag_574))
        {
            Savegame_EventFlagSet(EventFlag_574);
            var_a0 = 1;
        }
        else
        {
            var_a0 = 22;
        }
    }
    else
    {
        var_a0 = 14;
    }

    func_8003640C(var_a0);
}

void func_800E0C10(void) // 0x800E0C10
{
    func_8003640C(Savegame_EventFlagGet(EventFlag_391) ? 40 : 35);
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E0C50);

void func_800E14D4(void) {}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E14DC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E16FC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E1788);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E17B8);

const char* MAP_MESSAGES[] = {
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

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E1854);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E1FE0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E20A4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E22AC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E2444);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E24A0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E2664);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E27D0);

s32 func_800E28F4(void) // 0x800E28F4
{
    if (g_DeltaTime0 != 0)
    {
        D_800ED73C = ((s32)(D_800ED740 * 0x7169AC35) >> 3) ^ 0xA547B39E;
        D_800ED740 = ((u32)(D_800ED73C * 0x892D719C) >> 3) ^ 0xC65A4B97;
    }
    return (u16)D_800ED73C & 0x7FFF;
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E2968);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E2C28);

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800E2DF8

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E2E90);

void func_800E3390(void) // 0x800E3390
{
    s32 i;

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        D_800F4805 > 0 && D_800F4805 < 4)
    {
        D_800F4805 = 5;
        Savegame_EventFlagClear(EventFlag_576);
        Sd_EngineCmd(19);
    }

    switch (D_800F4805)
    {
        case 0:
            Player_ControlFreeze();
            func_8003A16C();
            func_8003ED74(18, 18);
            func_8008D438();

            D_800F4808 = 0;
            D_800F4809 = 0;
            D_800F480A = 0;
            D_800F480B = 0;
            D_800F480C = 0;
            D_800F480D = 0;
            D_800F480E = 0;
            D_800F480F = 0;
            D_800F4810 = 0;
            D_800F4811 = 1;
            D_800F4812 = 0;
            D_800F4813 = 0;
            D_800F4814 = 0;
            D_800F4815 = 0;
            D_800F4816 = 0;
            D_800F4817 = 0;
            D_800F4818 = 0;
            D_800F4819 = 0;
            D_800F481A = 0;
            D_800F481B = 0;

            func_800348C0();
            WorldGfx_CharaLmBufferAssign(CHARA_FORCE_FREE_ALL);

            ScreenFade_ResetTimestep();
            g_SysWork.field_30    = 20;
            g_SysWork.flags_22A4 |= 1 << 3;

            func_800E0A34();

            Fs_QueueStartRead(FILE_ANIM_LAST12_DMS, FS_BUFFER_21);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_21);

            D_800F4806 = 0;
            D_800F47F0 = 0;

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            func_800E94AC();
            func_800E94F4();
            func_800348C0();

            Savegame_EventFlagSet(EventFlag_576);
            Savegame_EventFlagSet(EventFlag_591);
            D_800F4805++;

        case 1:
            if (Savegame_EventFlagGet(EventFlag_449))
            {
                func_800E3F30();
            }
            else
            {
                D_800F4805++;
                func_800E4714();
            }
            break;

        case 2:
            func_800E4714();
            break;

        case 3:
            if (Savegame_EventFlagGet(EventFlag_391))
            {
                func_800E514C();
            }
            else
            {
                func_800E70F0();
            }
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);

            if (Savegame_EventFlagGet(EventFlag_391))
            {
                D_800F4805++;
                SysWork_StateStepSet(0, 0);
            }
            else
            {
                D_800F4805 += 2;
            }

        case 6:
            func_80087EDC(40);

            if (g_SysWork.sysStateStep_C[0] != 0)
            {
                D_800F4805++;
            }
            break;

        case 7:
            if ((g_Screen_FadeStatus & 7) == 5)
            {
                D_800F4805++;
            }
            break;

        case 8:
            for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
            {
                func_800E9490(&g_SysWork.npcs_1A0[i]);
            }

            if (Savegame_EventFlagGet(EventFlag_391))
            {
                if (!D_800F4815)
                {
                    Fs_QueueStartRead(FILE_ANIM_LAST3_DMS, FS_BUFFER_20);
                }
                Fs_QueueWaitForEmpty();
                DmsHeader_FixOffsets(FS_BUFFER_20);

                if (!D_800F4816)
                {
                    Fs_QueueStartRead(FILE_ANIM_LAST4_DMS, FS_BUFFER_21);
                    Fs_QueueWaitForEmpty();
                }

                D_800F4806 = 1;

                if (D_800F4813 != 2)
                {
                    if (!D_800F4813)
                    {
                        WorldGfx_CharaLmBufferAssign(CHARA_FORCE_FREE_ALL);
                        func_800E9260(Chara_Incubus, 1);
                    }
                    func_800E941C();
                }

                func_800E9444(Chara_Incubus, &g_SysWork.npcs_1A0[2]);
                func_800DD9B0(&g_SysWork.npcs_1A0[2]);

                D_800F4812 = 0;
                D_800F4811 = 0;
                D_800F4810 = 0;
                D_800F480E = 0;
                D_800F480D = 0;
                D_800F480C = 0;
                D_800F480B = 0;
                D_800F480A = 0;
                D_800F4809 = 0;
                D_800F4808 = 0;
                D_800F480F = 1;
                D_800F47F0 = Q12(670.0f);
            }
            else
            {
                if (!D_800F4817)
                {
                    Fs_QueueStartRead(FILE_ANIM_LAST5_DMS, FS_BUFFER_20);
                }
                Fs_QueueWaitForEmpty();
                DmsHeader_FixOffsets(FS_BUFFER_20);

                D_800F4806 = 1;
                if (D_800F4813 != 2)
                {
                    if (!D_800F4813)
                    {
                        WorldGfx_CharaLmBufferAssign(CHARA_FORCE_FREE_ALL);
                        func_800E9260(Chara_Incubator, 1);
                    }
                    func_800E941C();
                }

                func_800E9444(Chara_Incubator, &g_SysWork.npcs_1A0[4]);
                func_800E9498();

                D_800F4812 = 0;
                D_800F4811 = 0;
                D_800F4810 = 0;
                D_800F480E = 0;
                D_800F480D = 0;
                D_800F480F = 0;
                D_800F480B = 0;
                D_800F480A = 0;
                D_800F4809 = 0;
                D_800F4808 = 0;
                D_800F480C = 1;
                D_800F47F0 = Q12(68.0f);

                func_800DFB50(&g_SysWork.npcs_1A0[4]);
            }

            func_800D9394();
            Fs_QueueWaitForEmpty();
            D_800F4807 = 1;
            Model_AnimFlagsSet(&g_SysWork.player_4C.chara_0.model_0, 2);
            func_800E2E90();
            D_800F4805 = NO_VALUE;

            if (Savegame_EventFlagGet(EventFlag_391))
            {
                func_800E1788(-1);
            }
            else
            {
                func_800E1788(6);
            }
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);

            if (Savegame_EventFlagGet(EventFlag_391))
            {
                func_800DD9D4(&g_SysWork.npcs_1A0[2]);
            }
            else
            {
                func_800E9498();
                func_800DFB74(&g_SysWork.npcs_1A0[4]);
            }

            Savegame_EventFlagSet(EventFlag_577);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            D_800F47F0 = NO_VALUE;
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();

            Sd_EngineCmd(19);

            func_800E14DC(&g_SysWork.player_4C, &g_SysWork.npcs_1A0[2], 1);
            D_800F4805           = 0;
            g_SysWork.field_2378 = Q12(1.0f);
            break;
    }

    func_800E2E90();

    if (D_800F480C && D_800F4805 == 3 && Savegame_EventFlagGet(EventFlag_391))
    {
        g_SysWork.npcs_1A0[4].rotation_24.vy += FP_ANGLE(180.0f);
    }
}

void func_800E3B6C(void) // 0x800E3B6C
{
    switch (D_800F4805)
    {
        case 0:
            Player_ControlFreeze();

            g_SysWork.field_30          = 20;
            g_SysWork.sysStateStep_C[0] = 0;
            g_SysWork.flags_22A4       |= 1 << 3;

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            func_8005E70C();

            D_800F4805++;

        case 1:
            func_800E62CC();
            break;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
            D_800F4805 = 0;
            Savegame_EventFlagSet(EventFlag_579);
            break;
    }

    func_800E2E90();
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E3C48);

void func_800E3D18(void) // 0x800E3D18
{
    switch (D_800F4805)
    {
        case 0:
            Player_ControlFreeze();

            g_SysWork.player_4C.chara_0.health_B0 = Q12(100.0f);
            g_SysWork.field_30                    = 20;
            g_SysWork.sysStateStep_C[0]           = 0;
            g_SysWork.flags_22A4                 |= 1 << 3;

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            func_8005E70C();
            D_800F4805++;

        case 1:
            func_800E7380();
            break;

        case 2:
            if (Savegame_EventFlagGet(EventFlag_449))
            {
                D_800F4805 = 3;
                Savegame_EventFlagSet(EventFlag_584);
                break;
            }

            D_800F4805 = 3;

            Savegame_EventFlagSet(EventFlag_586);
            func_8004690C(Sfx_Unk1688);
            func_8004690C(Sfx_Unk1689);
            func_8004690C(Sfx_Unk1690);

            D_800F4820 = 0;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
            D_800F4805 = 0;

            Savegame_EventFlagSet(EventFlag_587);
            break;
    }

    func_800E2E90();
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E3E84);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E3F30);

void func_800E4714(void) // 0x800E4714
{
    s32 temp_v0;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            D_800F4807 = 1;
            D_800F4828 = 0;

            if (!Savegame_EventFlagGet(EventFlag_449))
            {
                func_800E9260(Chara_Alessa, 2);
                func_800E9260(Chara_EndingDahlia, 3);
                func_800E941C();
                func_800E9444(Chara_EndingDahlia, &g_SysWork.npcs_1A0[1]);
                func_800E9444(Chara_Alessa, &g_SysWork.npcs_1A0[2]);
                D_800F480A = 1;
                D_800F4809 = 1;
            }

            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 153, false);
            D_800F4804 = 0;
            D_800EDA08 = 0;
            Savegame_EventFlagSet(EventFlag_592);
            g_SysWork.field_2378 = Q12(0.8f);
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            if (!Savegame_EventFlagGet(EventFlag_449))
            {
                func_80085EB8(0, &g_SysWork.npcs_1A0[1], 5, false);
                func_80085EB8(0, &g_SysWork.npcs_1A0[2], 10, false);
            }
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(92.0f), Q12(112.0f), true, false);
            break;

        case 3:
            Map_MessageWithAudio(24, &D_800F4804, &D_800ED77C);
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(92.0f), Q12(112.0f), true, false);
            temp_v0 = sharedFunc_800D2DAC_0_s00();
            if (temp_v0 == 1 && D_800EDA08 == 0)
            {
                func_80085EB8(0, &g_SysWork.player_4C.chara_0, 131, false);
                D_800EDA08 = temp_v0;
            }
            break;

        case 4:
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 15, false);
            SysWork_StateStepIncrement(0);

        case 5:
            Map_MessageWithAudio(30, &D_800F4804, &D_800ED77C);
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(113.0f), Q12(129.0f), true, false);
            break;

        case 6:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(113.0f), Q12(129.0f), true, true);
            break;

        case 7:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 70, false);
            func_800E9260(Chara_Incubator, 1);
            D_800F4814 = 1;
            SysWork_StateStepIncrement(0);

        case 8:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(113.0f), Q12(134.0f), false, true);
            break;

        case 9:
            if (Fs_QueueDoThingWhenEmpty())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 10:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 16, false);
            SysWork_StateStepIncrement(0);

        case 11:
            Map_MessageWithAudio(31, &D_800F4804, &D_800ED77C);
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(135.0f), Q12(142.0f), true, false);
            break;

        case 12:
            Map_MessageWithAudio(35, &D_800F4804, &D_800ED77C);
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(135.0f), Q12(142.0f), true, false);
            break;

        case 13:
            Map_MessageWithAudio(44, &D_800F4804, &D_800ED77C);
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(135.0f), Q12(142.0f), true, false);
            break;

        case 14:
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 6, false);
            SysWork_StateStepIncrement(0);

        case 15:
            Map_MessageWithAudio(49, &D_800F4804, &D_800ED77C);
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(8.5f), Q12(143.0f), Q12(207.0f), true, false);

            Savegame_EventFlagClear(EventFlag_576);
            Savegame_EventFlagSet(EventFlag_593);
            Savegame_EventFlagSet(EventFlag_575);

            if (g_SysWork.sysStateStep_C[0] != 15)
            {
                Sd_EngineCmd(19);
            }
            break;

        case 16:
            Sd_EngineCmd(Sfx_XaAudio600);
            SysWork_StateStepIncrement(0);

        case 17:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(8.5f), Q12(143.0f), Q12(207.0f), true, false);
            if (func_80045B28() == 1)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 18:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(8.5f), Q12(143.0f), Q12(207.0f), true, false);
            if (func_80045B28() == 1)
            {
                SysWork_StateStepIncrement(0);
            }
            else
            {
                break;
            }

        case 19:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 171, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 18, false);
            func_800E1788(1);
            SysWork_StateStepIncrement(0);

        case 20:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(208.0f), Q12(231.0f), true, true);
            break;

        case 21:
            D_800F4809 = 0;
            Model_AnimFlagsClear(&g_SysWork.npcs_1A0[1].model_0, 2);
            func_800E941C();
            func_800E9444(Chara_Incubator, &g_SysWork.npcs_1A0[4]);
            D_800F4814 = 2;
            Model_AnimFlagsClear(&g_SysWork.npcs_1A0[4].model_0, 2);
            SysWork_StateStepIncrement(0);

        case 22:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(232.0f), Q12(287.0f), false, true);

            if (D_800F47F0 > Q12(230.0f))
            {
                if (D_800F481B == 0)
                {
                    Model_AnimFlagsClear(&g_SysWork.npcs_1A0[2].model_0, 2);
                    func_800E1788(2);
                    D_800F481B++;
                }
            }

            if (D_800F47F0 > Q12(260.0f) && D_800F481B == 1)
            {
                D_800F481B++;
            }

            if (D_800F47F0 > Q12(285.0f))
            {
                if (D_800F481B == 2)
                {
                    func_800E1788(3);
                    D_800F481B++;
                }
            }
            break;

        case 23:
            func_800E9490(&g_SysWork.npcs_1A0[2]);
            D_800F480A = 0;
            D_800F4811 = 0;
            SysWork_StateStepIncrement(0);

        case 24:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(232.0f), Q12(292.0f), false, true);
            break;

        case 25:
            func_80085EB8(0, &g_SysWork.npcs_1A0[4], 1, false);
            D_800F480C = 1;
            Model_AnimFlagsSet(&g_SysWork.npcs_1A0[4].model_0, 2);
            func_800DD7D0(&g_SysWork.npcs_1A0[1].position_18);
            D_800F4828 = 1;
            SysWork_StateStepIncrement(0);

        case 26:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(232.0f), Q12(332.0f), false, true);
            break;

        case 27:
            func_80085EB8(0, &g_SysWork.npcs_1A0[4], 2, false);
            SysWork_StateStepIncrement(0);

        case 28:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(232.0f), Q12(341.0f), true, true);
            break;

        case 29:
            D_800F480A = 0;
            func_800D9394();

            if (Savegame_EventFlagGet(EventFlag_391))
            {
                Fs_QueueStartRead(FILE_ANIM_LAST3_DMS, FS_BUFFER_18);
                D_800F4815 = 1;
            }
            else
            {
                Fs_QueueStartRead(FILE_ANIM_LAST5_DMS, FS_BUFFER_18);
                D_800F4817 = 1;
            }

            SysWork_StateStepIncrement(0);

        case 30:
            SysWork_StateStepIncrementDelayed(Q12(4.0f), false);
            break;

        default:
            g_SysWork.sysStateStep_C[0] = 0;
            D_800F4805++;
            break;
    }

    if (D_800F4828)
    {
        func_800DD868();
    }
}

void func_800E514C(void) // 0x800E514C
{
    VECTOR3 vec;
    s32     localRand;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Fs_QueueWaitForEmpty();
            D_800F4804 = 0;
            DmsHeader_FixOffsets(FS_BUFFER_18);
            D_800F4806 = 1;
            D_800F47F0 = 0;
            func_800E9260(Chara_EndingKaufmann, 2);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 19, false);

            func_8005DC1C(Sfx_Unk1670, &g_SysWork.npcs_1A0[1].position_18, Q8_CLAMPED(0.785f), 0);

            g_SysWork.field_2378 = Q12(0.7f);

            Model_AnimFlagsSet(&g_SysWork.npcs_1A0[1].model_0, 2);

            Savegame_EventFlagClear(EventFlag_591);
            Savegame_EventFlagClear(EventFlag_592);
            Savegame_EventFlagClear(EventFlag_593);
            Savegame_EventFlagClear(EventFlag_575);
            Savegame_EventFlagSet(EventFlag_576);

            D_800F4809 = 1;
            SysWork_StateStepIncrement(0);

        case 1:
            func_80087EDC(29);
            break;

        case 2:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(0.0f), Q12(12.0f), true, true);
            break;

        case 3:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(13.0f), Q12(37.0f), true, true);
            break;

        case 4:
            func_800E941C();
            func_800E9444(Chara_EndingKaufmann, &g_SysWork.npcs_1A0[3]);
            D_800F480B = 1;
            SysWork_StateStepIncrement(0);
            break;

        case 5:
            func_80085EB8(0, &g_SysWork.npcs_1A0[3], 25, false);
            SysWork_StateStepIncrement(0);

        case 6:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(38.0f), Q12(51.0f), true, true);
            break;

        case 7:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(52.0f), Q12(58.0f), true, true);
            break;

        case 8:
            D_800F47F0 = Q12(59.0f);
            func_80085EB8(0, &g_SysWork.npcs_1A0[3], 24, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 20, false);
            Savegame_EventFlagSet(EventFlag_591);
            SysWork_StateStepIncrement(0);

        case 9:
            Map_MessageWithAudio(51, &D_800F4804, &D_800ED7B4);
            break;

        case 10:
            func_80086C58(&g_SysWork.npcs_1A0[1], 21);
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(60.0f), Q12(78.0f), true, false);
            break;

        case 11:
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 22, false);
            SysWork_StateStepIncrement(0);

        case 12:
            Map_MessageWithAudio(57, &D_800F4804, &D_800ED7B4);
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(60.0f), Q12(78.0f), true, false);
            break;

        case 13:
            func_80086C58(&g_SysWork.npcs_1A0[3], 18);
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(79.0f), Q12(100.0f), true, true);
            break;

        case 14:
            func_80085EB8(0, &g_SysWork.npcs_1A0[3], 19, false);
            D_800F47F0 = Q12(101.0f);
            SysWork_StateStepIncrement(0);

        case 15:
            Map_MessageWithAudio(61, &D_800F4804, &D_800ED7B4);
            break;

        case 16:
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 23, false);
            g_SysWork.field_2378 = Q12(0.6f);
            Savegame_EventFlagClear(EventFlag_591);
            SysWork_StateStepIncrement(0);

        case 17:
            Map_MessageWithAudio(66, &D_800F4804, &D_800ED7B4);
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(102.0f), Q12(116.0f), true, false);
            break;

        case 18:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(102.0f), Q12(116.0f), true, true);
            break;

        case 19:
            func_800E9490(&g_SysWork.npcs_1A0[1]);
            func_800E9490(&g_SysWork.npcs_1A0[4]);

            D_800F480C = 0;
            D_800F4809 = 0;

            WorldGfx_CharaLmBufferAssign(1);
            func_800E9260(Chara_Incubator, 3);
            func_80085EB8(0, &g_SysWork.npcs_1A0[3], 20, false);
            g_SysWork.field_2378 = Q12(0.7f);

            SysWork_StateStepIncrement(0);

        case 20:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(117.0f), Q12(156.0f), true, true);
            break;

        case 21:
            D_800F4810 = 1;
            D_800F482C = -0x772; // TODO: Unsure if FP?
            if (g_SysWork.sysStateStep_C[0] != 18)
            {
                Savegame_EventFlagClear(EventFlag_576);
            }

            func_80087EA8(40);
            SysWork_StateStepIncrement(0);

        case 22:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(157.0f), Q12(193.0f), true, true);
            break;

        case 23:
            func_800E941C();
            func_800E9444(Chara_Incubator, &g_SysWork.npcs_1A0[4]);
            func_800E9260(Chara_BloodyIncubator, 1);
            SysWork_StateStepIncrement(0);

        case 24:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(7.5f), Q12(194.0f), Q12(280.0f), true, true);
            break;

        case 25:
            if (Fs_QueueDoThingWhenEmpty())
            {
                SysWork_StateStepIncrement(0);
            }
            else
            {
                break;
            }

        case 26:
            D_800F480C = 1;
            func_800E941C();
            func_800E9444(Chara_BloodyIncubator, &g_SysWork.npcs_1A0[5]);
            Model_AnimFlagsClear(&g_SysWork.npcs_1A0[5].model_0, 2);
            func_80085EB8(0, &g_SysWork.npcs_1A0[4], 2, false);
            func_8003D468(Chara_BloodyIncubator, false);
            g_SysWork.field_2378 = Q12(0.6f);
            Sd_XaPreLoadAudio(Sfx_XaAudio606);
            SysWork_StateStepIncrement(0);

        case 27:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(281.0f), Q12(313.0f), false, true);
            break;

        case 28:
            SysWork_StateStepIncrement(0);

        case 29:
            SysWork_StateStepIncrement(0);

        case 30:
            Sd_EngineCmd(Sfx_XaAudio606);
            SysWork_StateStepIncrement(0);

        case 31:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(281.0f), Q12(320.0f), true, false);
            if (func_80045B28() != 1)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 32:
            if (func_80045B28() != 1)
            {
                SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(281.0f), Q12(320.0f), true, false);
                break;
            }
            SysWork_StateStepIncrement(0);

        case 33:
            func_800D7144(&D_800F3DE4);
            func_800E1788(9);
            SysWork_StateStepIncrement(0);

        case 34:
            D_800F47F0 = Q12(321.0f);
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            D_800F4810 = 0;
            func_800D70EC();
            break;

        case 35:
            D_800F480C = 0;
            func_800E9490(&g_SysWork.npcs_1A0[4]);
            D_800F480D = 1;
            Model_AnimFlagsSet(&g_SysWork.npcs_1A0[5].model_0, 2);
            func_80085EB8(0, &g_SysWork.npcs_1A0[5], 1, false);
            SysWork_StateStepIncrement(0);

        case 36:
            if (!func_80045B28())
            {
                func_800E9260(Chara_EndingDahlia, 3);
                SysWork_StateStepIncrement(0);
            }
            func_800D70EC();
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(322.0f), Q12(391.0f), true, false);
            break;

        case 37:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(322.0f), Q12(391.0f), true, true);
            if (g_SysWork.sysStateStep_C[0] != 37)
            {
                func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            }
            break;

        case 38:
            if (Fs_QueueDoThingWhenEmpty())
            {
                SysWork_StateStepIncrement(0);
            }
            g_SysWork.field_2378 = Q12(0.7f);
            D_800F47F0           = Q12(392.0f);
            break;

        case 39:
            Map_MessageWithAudio(68, &D_800F4804, &D_800ED7B4);
            Savegame_EventFlagSet(EventFlag_591);
            break;

        case 40:
            func_800E941C();
            func_800E9444(Chara_EndingDahlia, &g_SysWork.npcs_1A0[1]);
            SysWork_StateStepIncrement(0);
            break;

        case 41:
            D_800F4809 = 1;
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 22, false);
            g_SysWork.field_2378 = Q12(0.6f);
            D_800F47F0           = Q12(393.0f);
            SysWork_StateStepIncrement(0);

        case 42:
            Map_MessageWithAudio(70, &D_800F4804, &D_800ED7B4);
            break;

        case 43:
            func_80085EB8(0, &g_SysWork.npcs_1A0[3], 22, false);
            g_SysWork.field_2378 = Q12(0.7f);
            D_800F4809           = 0;
            func_800E9490(&g_SysWork.npcs_1A0[1]);
            SysWork_StateStepIncrement(0);

        case 44:
            Map_MessageWithAudio(71, &D_800F4804, &D_800ED7B4);
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(394.0f), Q12(417.0f), true, false);
            break;

        case 45:
            func_800E9260(Chara_LittleIncubus, 3);
            SysWork_StateStepIncrement(0);

        case 46:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(394.0f), Q12(417.0f), true, true);
            break;

        case 47:
            if (Fs_QueueDoThingWhenEmpty())
            {
                SysWork_StateStepIncrement(0);
            }

            break;
        case 48:
            func_800E941C();
            func_800E9444(Chara_LittleIncubus, g_SysWork.npcs_1A0);
            D_800F480E = 1;
            func_8003D468(Chara_BloodyIncubator, true);
            Savegame_EventFlagSet(EventFlag_576);
            g_SysWork.field_2378 = Q12(0.5f);
            SysWork_StateStepIncrement(0);

        case 49:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(418.0f), Q12(498.0f), true, true);
            g_SysWork.field_28             += g_DeltaTime0;
            g_SysWork.npcs_1A0[5].timer_C6 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.0625f, 12);
            if (g_SysWork.field_28 > Q12(0.3f))
            {
                localRand           = Rng_Rand16();
                vec.vx              = g_SysWork.npcs_1A0[0].position_18.vx + Q12(0.2f);
                vec.vy              = g_SysWork.npcs_1A0[0].position_18.vy + Q12(-0.9f);
                vec.vz              = g_SysWork.npcs_1A0[0].position_18.vz + Q12(0.2f);
                g_SysWork.field_28 -= Q12(0.2f);
                g_SysWork.field_28 -= localRand % Q12(0.1f);
                func_8005F6B0(g_SysWork.npcs_1A0, &vec, 8, 1);
            }
            break;

        case 50:
            func_800E9490(&g_SysWork.npcs_1A0[5]);
            func_800E9490(&g_SysWork.npcs_1A0[0]);

            D_800F480E = 0;
            D_800F480D = 0;

            func_800E9260(Chara_Incubus, 1);
            D_800F4813 = 1;
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 171, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[3], 24, false);
            func_8005E70C();

            g_SysWork.field_2378 = Q12(0.7f);
            SysWork_StateStepIncrement(0);

        case 51:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(499.0f), Q12(509.0f), true, true);
            break;

        case 52:
            func_800E941C();
            func_800E9444(Chara_Incubus, &g_SysWork.npcs_1A0[2]);
            D_800F4813 = 2;
            D_800F480F = 1;
            SysWork_StateStepIncrement(0);
            break;

        case 53:
            func_800DD9B0(&g_SysWork.npcs_1A0[2]);
            func_800E9260(Chara_EndingDahlia, 3);
            g_SysWork.field_2378 = Q12(0.8f);
            SysWork_StateStepIncrement(0);

        case 54:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(510.0f), Q12(539.0f), true, true);
            break;

        case 55:
            func_800E941C();
            func_800E9444(Chara_EndingDahlia, &g_SysWork.npcs_1A0[1]);
            D_800F4809 = 1;
            SysWork_StateStepIncrement(0);
            break;

        case 56:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 28, false);
            g_SysWork.field_2378 = Q12(0.9f);
            Fs_QueueStartRead(FILE_ANIM_LAST4_DMS, FS_BUFFER_21);
            D_800F4816 = 0;
            SysWork_StateStepIncrement(0);

        case 57:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(540.0f), Q12(586.0f), true, true);
            break;

        case 58:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(587.0f), Q12(615.0f), false, true);
            g_SysWork.field_2378 = Q12(0.8f);
            break;

        case 59:
            func_800E1788(10);
            func_800DAD54();
            func_800DB288();
            SysWork_StateStepIncrement(0);

        case 60:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(587.0f), Q12(629.0f), false, true);
            break;

        case 61:
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 24, false);
            SysWork_StateStepIncrement(0);

        case 62:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(587.0f), Q12(730.0f), true, true);
            break;

        case 63:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            g_SysWork.sysStateStep_C[0] = 0;
            D_800F4805++;
            func_800E9490(&g_SysWork.npcs_1A0[3]);
            func_800E9490(&g_SysWork.npcs_1A0[1]);
            D_800F480B = 0;
            D_800F4809 = 0;
            WorldGfx_CharaLmBufferAssign(6);
            break;
    }

    if (g_SysWork.sysStateStep_C[0] >= 62 && g_SysWork.sysStateStep_C[0] < 64)
    {
        func_800DB154(&D_800F3E58); // TODO: Retype `D_800F3E58` as `GsCOORDINATE2` array.
    }
}

// Referenced by some .data struct?
const u8 g_rodata_800CC320[0x28] = { 0 };

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03_2", D_800CC348);

void func_800E62CC(void) // 0x800E62CC
{
    VECTOR3         unused;
    s32             flags;
    s_800ED7E0_ptr* ptr;

    if (g_SysWork.sysStateStep_C[0] >= 12)
    {
        func_80089500();
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            DmsHeader_FixOffsets(FS_BUFFER_21);
            D_800F4806 = 0;
            D_800F47F0 = 0;
            D_800F4804 = 0;
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 182, false);
            func_800E9260(Chara_BloodyIncubator, 5);
            D_800F4820 = 0;
            Rng_SetSeed(0);
            g_SysWork.field_2378 = Q12(1.0f);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(0.0f), Q12(24.0f), true, true);
            if (g_SysWork.sysStateStep_C[0] != 1)
            {
                func_800E941C();
            }
            break;

        case 2:
            Sd_XaPreLoadAudio(Sfx_XaAudio596);
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            break;

        case 3:
            Sd_EngineCmd(Sfx_XaAudio596);
            func_800DD9F8(&g_SysWork.npcs_1A0[2]);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(25.0f), Q12(175.0f), true, true);
            break;

        case 5:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 183, false);
            func_8003D468(Chara_Incubus, true);
            func_800E1788(11);
            SysWork_StateStepIncrement(0);

        case 6:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(176.0f), Q12(200.0f), false, true);
            break;

        case 7:
            func_800E9444(Chara_BloodyIncubator, &g_SysWork.npcs_1A0[5]);
            Model_AnimFlagsClear(&g_SysWork.npcs_1A0[5].model_0, 2);
            func_800E1788(12);
            SysWork_StateStepIncrement(0);

        case 8:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(176.0f), Q12(253.0f), true, true);
            g_SysWork.npcs_1A0[2].timer_C6 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.15f, 12);
            if (g_SysWork.npcs_1A0[2].timer_C6 > Q12(1.0f))
            {
                g_SysWork.npcs_1A0[2].timer_C6 = Q12(1.0f);
            }
            break;

        case 9:
            D_800F480D = 1;
            Model_AnimFlagsSet(&g_SysWork.npcs_1A0[5].model_0, 2);

            func_80085EB8(0, &g_SysWork.npcs_1A0[5], 6, false);
            func_8003D468(Chara_BloodyIncubator, true);

            g_SysWork.npcs_1A0[5].timer_C6 = Q12(0.751f); // TODO: Odd value, possibly bad Q format.

            func_800E9490(&g_SysWork.npcs_1A0[2]);
            func_800E1788(13);

            D_800F480F = 0;

            func_800D7E50(&g_SysWork.npcs_1A0[2].position_18);
            func_800D947C();

            Savegame_EventFlagSet(EventFlag_592);
            SysWork_StateStepIncrement(0);

        case 10:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(254.0f), Q12(314.0f), true, true);

            g_SysWork.npcs_1A0[5].timer_C6 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.25f, Q12_SHIFT);
            if (g_SysWork.npcs_1A0[5].timer_C6 < 0)
            {
                g_SysWork.npcs_1A0[5].timer_C6 = 0;
            }
            break;

        case 11:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 174, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[5], 7, false);
            func_8003D468(Chara_BloodyIncubator, false);

            SysWork_StateStepIncrement(0);

            D_800F4820 = 1;
            D_800F4824 = 0;
            Savegame_EventFlagSet(EventFlag_593);

        case 12:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(315.0f), Q12(420.0f), true, true);
            break;

        case 13:
            func_80085EB8(0, &g_SysWork.npcs_1A0[5], 2, false);
            WorldGfx_PlayerHeldItemSet(InventoryItemId_CutsceneBaby);
            func_800E1788(14);
            SysWork_StateStepIncrement(0);

        case 14:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(421.0f), Q12(475.0f), true, true);
            break;

        case 15:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(476.0f), Q12(536.0f), true, false);
            SysWork_StateStepIncrement(0);
            break;

        case 16:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(476.0f), Q12(536.0f), true, true);
            break;

        case 17:
            func_80085EB8(0, &g_SysWork.npcs_1A0[5], 3, false);
            D_800F4812 = 1;
            func_8005DC1C(Sfx_Unk1689, NULL, CHARA_FORCE_FREE_ALL, 3);
            func_800E1788(15);
            SysWork_StateStepIncrement(0);

        case 18:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(537.0f), Q12(600.0f), true, true);
            break;

        case 19:
            Fs_QueueWaitForEmpty();
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 179, false);
            func_8003D468(Chara_BloodyIncubator, true);
            WorldGfx_CharaModelMaterialSet(Chara_BloodyIncubator, 0);
            D_800F4812 = 0;
            func_8003D01C();
            SysWork_StateStepIncrement(0);

        case 20:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(601.0f), Q12(619.0f), false, true);
            break;

        case 21:
            func_80085EB8(0, &g_SysWork.npcs_1A0[5], 4, false);
            SysWork_StateStepIncrement(0);

        case 22:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(601.0f), Q12(635.0f), true, true);
            break;

        case 23:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(636.0f), Q12(653.0f), true, false);
            SysWork_StateStepIncrement(0);
            break;

        case 24:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(636.0f), Q12(653.0f), true, true);
            break;

        case 25:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 180, false);
            SysWork_StateStepIncrement(0);

        case 26:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(654.0f), Q12(721.0f), true, true);
            break;

        case 27:
            func_80085EB8(0, &g_SysWork.npcs_1A0[5], 8, false);

            if (Savegame_EventFlagGet(EventFlag_449))
            {
                func_800E9260(Chara_EndingCybil, 4);
            }
            else
            {
                func_800E9260(Chara_EndingKaufmann, 4);
            }

            func_8004690C(Sfx_Unk1689);
            func_8005DC1C(Sfx_Unk1688, NULL, Q8_CLAMPED(1.0f), 3);
            func_800D88C4();
            SysWork_StateStepIncrement(0);

        case 28:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(722.0f), Q12(752.0f), true, true);
            break;

        case 29:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 180, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[5], 9, false);
            Player_FlexRotationYReset();
            Savegame_EventFlagSet(EventFlag_593);
            SysWork_StateStepIncrement(0);

        case 30:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(753.0f), Q12(843.0f), true, true);
            break;

        case 31:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 181, false);
            SysWork_StateStepIncrement(0);

        case 32:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(844.0f), Q12(935.0f), true, true);
            break;

        case 33:
            if (Savegame_EventFlagGet(EventFlag_449))
            {
                func_800E941C();
                func_800E9444(Chara_EndingCybil, g_SysWork.npcs_1A0);
                D_800F4808 = 1;
                Model_AnimFlagsClear(&g_SysWork.npcs_1A0[0].model_0, 2);
                SysWork_StateStepIncrement(0);
            }
            else
            {
                SysWork_StateStepSet(0, 38);
            }
            break;

        case 34:
            func_80085EB8(0, g_SysWork.npcs_1A0, 26, false);
            Model_AnimFlagsSet(&g_SysWork.npcs_1A0[0].model_0, 2);
            func_800E9490(&g_SysWork.npcs_1A0[5]);
            func_800E9260(Chara_EndingKaufmann, 5);
            Sd_XaPreLoadAudio(Sfx_XaAudio657);
            D_800F480D = 0;
            SysWork_StateStepIncrement(0);

        case 35:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(936.0f), Q12(975.0f), true, true);
            break;

        case 36:
            func_80085EB8(0, g_SysWork.npcs_1A0, 25, false);
            Sd_EngineCmd(Sfx_XaAudio657);
            func_800D7ED0();
            SysWork_StateStepIncrement(0);

        case 37:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(976.0f), Q12(1058.0f), true, true);
            if (g_SysWork.sysStateStep_C[0] != 37)
            {
                Sd_EngineCmd(19);
            }
            break;

        case 38:
            func_800E941C();
            func_800E9444(Chara_EndingKaufmann, &g_SysWork.npcs_1A0[3]);
            if (Savegame_EventFlagGet(EventFlag_449))
            {
                Fs_QueueStartRead(FILE_ANIM_ENDAA_DMS, FS_BUFFER_18);
            }
            else
            {
                Fs_QueueStartRead(FILE_ANIM_ENDBA_DMS, FS_BUFFER_18);
            }
            SysWork_StateStepIncrement(0);
            break;

        case 39:
            func_80085EB8(0, &g_SysWork.npcs_1A0[3], 21, false);
            D_800F480B = 1;
            SysWork_StateStepIncrement(0);

        case 40:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(1059.0f), Q12(1122.0f), true, true);
            break;

        case 41:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
            func_800E9490(&g_SysWork.npcs_1A0[3]);
            D_800F480B = 0;
            func_8004690C(Sfx_Unk1688);
            D_800F4805++;
            break;
    }

    if (D_800F4820 != 0)
    {
        switch (D_800F4824)
        {
            case 0:
                if (D_800F47F0 > Q12(700.0f))
                {
                    D_800F4824 = 1;
                }
                break;
            case 1:
                if (!(Rng_Rand16() & 0x70))
                {
                    func_800D7D74(0);
                }

                if (g_SysWork.sysStateStep_C[0] >= 34)
                {
                    func_800D71A4(32);
                    D_800F4824++;
                }
                break;
            case 2:
                if (!(Rng_Rand16() & 0xF8))
                {
                    func_800D7D74(0);
                }
                break;
        }

        if (g_SysWork.sysStateStep_C[0] >= 30 && g_SysWork.sysStateStep_C[0] < 40)
        {
            if (g_SysWork.sysStateStep_C[0] < 33)
            {
                D_800F4830 = 1;
            }
            else
            {
                D_800F4830 = 2;
                func_800D8858(1);
            }
        }
        else
        {
            D_800F4830 = 0;
        }

        ptr = D_800ED7E0[g_SysWork.sysStateStep_C[0]];
        if (ptr)
        {
            do
            {
                unused.vx = ptr->field_0.vx >> 4; // @unused
                unused.vy = ptr->field_0.vy >> 4;
                unused.vz = ptr->field_0.vz >> 4;

                if (!(ptr->flags_38 & 2) || g_SysWork.sysStateStep_C[0] != D_800EDA0C)
                {
                    func_800DA774(ptr);
                }

                flags = ptr->flags_38;
                ptr++;
            } while (flags & 1);
        }

        D_800EDA0C = g_SysWork.sysStateStep_C[0];
    }
}

void func_800E70F0(void) // 0x800E70F0
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_18);

            D_800F4806 = 1;
            D_800F47F0 = Q12(0.0f);
            D_800F4804 = 0;

            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            func_800E1788(4);

            Model_AnimFlagsSet(&g_SysWork.npcs_1A0[1].model_0, 2);
            g_SysWork.field_2378 = Q12(0.8f);
            SysWork_StateStepIncrement(0);

        case 1:
            Map_MessageWithAudio(74, &D_800F4804, &D_800ED88C);
            break;

        case 2:
            Map_MessageWithAudio(76, &D_800F4804, &D_800ED88C);
            D_800F47F0 = Q12(1.0f);
            break;

        case 3:
            Map_MessageWithAudio(78, &D_800F4804, &D_800ED88C);
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(2.0f), Q12(33.0f), true, false);
            break;

        case 4:
            func_80085EB8(0, &g_SysWork.npcs_1A0[1], 17, false);
            Map_MessageWithAudio(80, &D_800F4804, &D_800ED88C);
            func_800E1788(5);
            func_800DAD54();
            func_800DB288();
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(2.0f), Q12(41.0f), true, true);
            break;

        case 6:
            SysWork_StateStepIncrementAfterTime(&D_800F47F0, Q12(10.0f), Q12(42.0f), Q12(68.0f), true, true);
            break;

        case 7:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            g_SysWork.sysStateStep_C[0] = 0;
            D_800F4805++;

            func_800E9490(&g_SysWork.npcs_1A0[1]);

            D_800F4809 = 0;
            break;
    }

    if (g_SysWork.sysStateStep_C[0] >= 5 && g_SysWork.sysStateStep_C[0] < 8)
    {
        func_800DB154(&D_800F3E58);
    }
}

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03_2", D_800CC5C8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E7380);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03_2", D_800CC63C);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E787C);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03_2", D_800CCD20);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E86BC);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03_2", D_800CCE80);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E8D20);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E9260);

void func_800E941C(void) // 0x800E941C
{
    Fs_QueueWaitForEmpty();
    WorldGfx_CharaModelProcessAllLoads();
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E9444);

void func_800E9490(s_SubCharacter* chara) // 0x800E9490
{
    chara->model_0.charaId_0 = 0;
}

void func_800E9498(void) // 0x800E9498
{
    g_MapOverlayHeader.charaUpdateFuncs_194[Chara_Incubator] = Ai_Unknown23_Update;
}

void func_800E94AC(void) // 0x800E94AC
{
    g_MapOverlayHeader.charaUpdateFuncs_194[Chara_Incubator] = Ai_Incubator_Update;
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E94C0);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E94F4);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E9528);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E972C);

void func_800E9874(void) // 0x800E9874
{
    func_800E1854();

    if (D_800F4820 != 0)
    {
        if (D_800F4838 == 0)
        {
            func_800D5E78();
            func_800D7D08();
        }

        func_800D917C();
    }

    if (D_800F4830 > 0)
    {
        func_800D8858(D_800F4830 - 1);
    }
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E98EC);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E9AC8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/map7_s03_2", func_800E9C28);

INCLUDE_RODATA("asm/maps/map7_s03/nonmatchings/map7_s03_2", D_800CD168);
