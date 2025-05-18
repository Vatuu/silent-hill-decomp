#ifndef _MAPS_SHARED_H
#define _MAPS_SHARED_H

extern s32 sharedData_800CAB70_0_s00; // Type assumed.

extern s32 sharedData_800DFB6C_0_s00;
extern s32 sharedData_800DFB70_0_s00;
extern s32 sharedData_800E0CA8_0_s00;
extern s32 sharedData_800E0CAC_0_s00;
extern u32 sharedData_800E0CB0_0_s00;
extern u16 sharedData_800E0CB4_0_s00;
extern u16 sharedData_800E0CB6_0_s00;
extern u16 sharedData_800E0CB8_0_s00;
extern s32 sharedData_800E32D0_0_s00;

extern s8 sharedData_800DD59C_0_s00;

extern s16 sharedData_800E0C6E_0_s00;

extern VECTOR3 sharedData_800E323C_0_s00;

extern VECTOR3 sharedData_800E324C_0_s00;

extern s16 sharedData_800E3260_0_s00;

extern s32 sharedData_800E39D8_0_s00;

// Next 4 set by `Ai_Stalker_Update`.
extern s32 sharedData_800E3A20_0_s00;
extern s32 sharedData_800E3A24_0_s00;
extern s32 sharedData_800E3A28_0_s00;
extern s32 sharedData_800E3A2C_0_s00;
// This is set by `Ai_Stalker_Init`.
extern s8 sharedData_800DA6C8_0_s00;

s32 sharedFunc_800CBBBC_0_s00();

void sharedFunc_800D01BC_0_s00(u16* arg0, VECTOR3* arg1, s32 arg2);

void sharedFunc_800D0A60_0_s00(s32 caseArg);

s32 sharedFunc_800D0B18_0_s00(s32 arg0);

void sharedFunc_800D0E04_0_s00();

void sharedFunc_800D209C_0_s00();

void sharedFunc_800D20D8_0_s00();

void sharedFunc_800D20E4_0_s00();

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

void sharedFunc_800D63D0_0_s00(s_SubCharacter* chara, s32 arg1);

void sharedFunc_800D6554_0_s00(s_SubCharacter* chara);

void sharedFunc_800D670C_0_s00(s_SubCharacter* arg0);

void sharedFunc_800D67FC_0_s00(s_SubCharacter* chara);

void sharedFunc_800D7E04_0_s00(s_SubCharacter* chara, s32 caseArg);

void sharedFunc_800D88AC_0_s00(s_SubCharacter* playerChara);

void Ai_Stalker_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

void sharedSymbol_800D309C_0_s00(s_SubCharacter*, s32); // Matches across all maps except `map6_s03`.

void sharedFunc_800D3308_0_s00(s_SubCharacter*);

void sharedFunc_800D3B44_0_s00(s_SubCharacter*);

void sharedFunc_800D6970_0_s00(s_SubCharacter*, s32, s32);

void sharedFunc_800D70C4_0_s00(s_SubCharacter*);

void sharedFunc_800D7BE8_0_s00(s_SubCharacter*);

/** Among other things, sets the players's anim to anim 3 (which might actually be flags if the field packs more data). */
void sharedFunc_800D88C0_0_s00(s_SubCharacter* playerChara, s32 arg1);

void sharedFunc_800D8904_0_s00(s_SubCharacter* playerChara, s32 afkTime);

void sharedFunc_800D891C_0_s00(s_SubCharacter* playerChara);

void sharedFunc_800D8928_0_s00(s_SubCharacter* chara);

s32 sharedFunc_800D893C_0_s00(s_SubCharacter* chara);

void sharedFunc_800D8950_0_s00(s_SubCharacter* chara);

void sharedFunc_800D9064_0_s00(s_SubCharacter* chara);

void sharedFunc_800D9078_0_s00(s_SubCharacter* chara);

void sharedFunc_800D923C_0_s00(s_SubCharacter* playerChara);

// MAP1_S00 LarvalStalker funcs
void Ai_LarvalStalker_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

void sharedFunc_800CF168_1_s00(s_SubCharacter*);

void sharedFunc_800D140C_1_s00(s_SubCharacter*, s32);

void sharedFunc_800D1524_1_s00(s_SubCharacter*, s32, s32);

void Ai_LarvalStalker_Init(s_SubCharacter*);

void sharedFunc_800D17BC_1_s00(s_SubCharacter*);

void sharedFunc_800D1DBC_1_s00(s_SubCharacter*);

// MAP3_S03 puppet nurse/doctor funcs
void sharedFunc_800CDA88_3_s03(s_SubCharacter*);

void sharedFunc_800CDAB8_3_s03(s_SubCharacter* chara, s32 arg1, s32 arg2);

void func_800CDB5C(s_SubCharacter*, s32);

void Ai_PuppetNurse_Init(s_SubCharacter* chara, s32 isPuppetDoctor);

void Ai_PuppetNurse_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

void Ai_PuppetDoctor_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

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

void sharedFunc_800D01D0_3_s03(s_SubCharacter* chara);

void sharedFunc_800D02E4_3_s03(s_SubCharacter*, s32);

void sharedFunc_800D03E4_3_s03(s_SubCharacter*);

void sharedFunc_800D06AC_3_s03(s_SubCharacter*, s32, s32);

void sharedFunc_800D0828_3_s03(s_SubCharacter*, s32);

void sharedFunc_800D0968_3_s03(s_SubCharacter*, s32);

void Ai_Creaper_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

void sharedFunc_800D7C28_1_s02(s_SubCharacter*); // `map5_s00` version has extra code at end of func, other maps are 1:1, shared symbol name is needed for `Ai_Creaper_Update`.

void sharedFunc_800D7EE8_1_s02(s_SubCharacter*);

void sharedFunc_800D8244_1_s02(s_SubCharacter*);

void sharedFunc_800D983C_1_s02(s_SubCharacter*);

void sharedFunc_800D9960_1_s02(s_SubCharacter*, s32, s32);

void sharedFunc_800D99D0_1_s02(s_SubCharacter*);

void Ai_HangedScratcher_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

void sharedFunc_800CFCA8_5_s00(s_SubCharacter*);

void sharedFunc_800CFF74_5_s00(s_SubCharacter*);

void sharedFunc_800D029C_5_s00(s_SubCharacter*);

void sharedFunc_800D26D8_5_s00(s_SubCharacter*);

void sharedFunc_800D2844_5_s00(s_SubCharacter*, s32, s32);

void sharedFunc_800D2C18_5_s00(s_SubCharacter*);

void sharedFunc_800D3300_5_s00(s_SubCharacter*);

void Ai_Romper_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

void sharedFunc_800E5DD8_2_s02(s_SubCharacter*);

void sharedFunc_800E60FC_2_s02(s_SubCharacter*);

void sharedFunc_800E6420_2_s02(s_SubCharacter*);

void sharedFunc_800E66E8_2_s02(s_SubCharacter*);

void sharedFunc_800E8730_2_s02(s_SubCharacter*);

void sharedFunc_800E8A40_2_s02(s_SubCharacter*, s32, s32);

void sharedFunc_800E8DFC_2_s02(s_SubCharacter*);

void Ai_Groaner_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

void sharedFunc_800E3074_2_s00(s_SubCharacter*); // `map2_s00` has different version to the other 4 maps which share this, shared sym is needed to share `Ai_Groaner_Update`.

void sharedFunc_800E33DC_2_s00(s_SubCharacter*);

void sharedFunc_800E384C_2_s00(s_SubCharacter*); // `map2_s00` has different version to the other 4 maps which share this, shared sym is needed to share `Ai_Groaner_Update`.

void sharedFunc_800E5AA4_2_s00(s_SubCharacter*);

void sharedFunc_800E5EC4_2_s00(s_SubCharacter*, s32, s32);

void sharedFunc_800E6338_2_s00(s_SubCharacter*);

void sharedFunc_800E71E8_2_s00(s_SubCharacter*);

void Ai_Splithead_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

void sharedFunc_800CF8D8_1_s05(s_SubCharacter*);

void sharedFunc_800CF990_1_s05(s_SubCharacter*);

void sharedFunc_800CFE94_1_s05(s_SubCharacter*);

void sharedFunc_800D0054_1_s05(s_SubCharacter*);

void sharedFunc_800D267C_1_s05(s_SubCharacter*);

void sharedFunc_800D274C_1_s05(s_SubCharacter*, s32);

void sharedFunc_800D2D74_1_s05(s_SubCharacter*);

void sharedFunc_800D3AFC_1_s05(s_SubCharacter*);

void sharedFunc_800D3B30_1_s05(s_SubCharacter*);

void sharedFunc_800D4070_1_s05(s_SubCharacter*);

extern s32 sharedData_800D8610_1_s05;

void Ai_Cybil_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

void sharedFunc_800D8888_0_s01(s_SubCharacter*, s32, s32);

void sharedFunc_800D88D0_0_s01(s_SubCharacter*, s32);

void sharedSymbol_800D8A68_0_s01(s_SubCharacter*, s32);

void sharedSymbol_800D9AD0_0_s01(s_SubCharacter*);

void Ai_AirScreamer_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

void sharedFunc_800D21E4_0_s01(s32, s32);

void sharedFunc_800D2200_0_s01(s_SubCharacter*);

void sharedFunc_800D2274_0_s01(s_SubCharacter*);

void sharedFunc_800D2390_0_s01(s_SubCharacter*);

void sharedFunc_800D2974_0_s01(s_SubCharacter*);

void sharedFunc_800D3928_0_s01(s_SubCharacter*);

void sharedFunc_800D62D8_0_s01(s_SubCharacter*);

void sharedFunc_800D7AB0_0_s01(s_SubCharacter*);

void sharedFunc_800D7EBC_0_s01(s_SubCharacter*);

void sharedFunc_800D81B0_0_s01(s_SubCharacter*);

void Ai_Lisa_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

void sharedFunc_800D08FC_3_s04(s_SubCharacter*, s32, s32);

void sharedFunc_800D0944_3_s04(s_SubCharacter*, s32);

void sharedSymbol_800D0ADC_3_s04(s_SubCharacter*, s32); // `Ai_Lisa_Control`

void sharedFunc_800D1350_3_s04(s_SubCharacter*);

void Ai_BloodyLisa_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

void sharedFunc_800D595C_7_s01(s_SubCharacter*, s32, s32);

void sharedFunc_800D59A4_7_s01(s_SubCharacter*, s32);

void sharedFunc_800D5B3C_7_s01(s_SubCharacter*, s32);

void sharedFunc_800D5CB4_7_s01(s_SubCharacter*);

void Ai_GhostChildAlessa_Update(s_SubCharacter* chara, s32 arg1, s32 arg2);

void sharedFunc_800D4A2C_7_s01(s_SubCharacter*, s32, s32);

void sharedFunc_800D4A74_7_s01(s_SubCharacter*, s32);

void sharedFunc_800D4C0C_7_s01(s_SubCharacter*, s32);

void sharedFunc_800D4DD8_7_s01(s_SubCharacter*);

#endif
