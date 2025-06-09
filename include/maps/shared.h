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

extern s_AnimInfo sharedData_800DA6C8_0_s00[]; // Used by `Ai_LarvalStalker_Init`.

extern s_AnimInfo sharedData_800DD5A8_0_s00[]; // Used by `Ai_Stalker_Init`.

// Two variables used by `Ai_Creaper_Init`.
extern s_AnimInfo sharedData_800E0D38_1_s02[];
extern s8  sharedData_800E57CC_1_s02;

extern s32 sharedData_800E21D0_0_s01;

extern s_AnimInfo sharedData_800CAA98_0_s01[]; // Used by `Ai_AirScreamer_Init` / `sharedFunc_800D2BF4_0_s01`

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

extern s32 sharedData_800D3150_3_s02; // Used by `Ai_Alessa_Init`.

extern s32 sharedData_800D5CF4_3_s00; // Used by `Ai_Kaufmann_Init`.

extern s_AnimInfo sharedData_800D5ABC_3_s03[]; // Used by `Ai_Bloodsucker_Init`.

extern s_AnimInfo sharedData_800DF174_0_s00[]; // Used by `sharedFunc_800D921C_0_s00`.

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

void Ai_Stalker_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void Ai_Stalker_Init(s_SubCharacter* chara); // Matches across all maps except `map6_s03`.

void sharedFunc_800D3308_0_s00(s_SubCharacter*);

void sharedFunc_800D3B44_0_s00(s_SubCharacter*);

void sharedFunc_800D6970_0_s00(s_SubCharacter*, s32, GsCOORDINATE2*);

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

s16 sharedFunc_800D921C_0_s00(s_SubCharacter* chara);

void sharedFunc_800D923C_0_s00(s_SubCharacter* chara); // Humanoid init function?

u8 sharedFunc_800D92AC_0_s00(s32 x, s32 y);

// MAP1_S00 LarvalStalker funcs
void Ai_LarvalStalker_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void sharedFunc_800CF168_1_s00(s_SubCharacter*);

void sharedFunc_800D140C_1_s00(s_SubCharacter*, GsCOORDINATE2*);

void sharedFunc_800D1524_1_s00(s_SubCharacter*, s32, GsCOORDINATE2*);

void Ai_LarvalStalker_Init(s_SubCharacter* chara);

void sharedFunc_800D17BC_1_s00(s_SubCharacter*);

void sharedFunc_800D1DBC_1_s00(s_SubCharacter*);

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

void sharedFunc_800D8244_1_s02(s_SubCharacter*);

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

void sharedFunc_800D88D0_0_s01(s_SubCharacter*, GsCOORDINATE2*);

void sharedSymbol_800D8A68_0_s01(s_SubCharacter*, GsCOORDINATE2*);

void Ai_Cybil_Init(s_SubCharacter* chara);

void Ai_AirScreamer_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);

void sharedFunc_800D21E4_0_s01(s32, GsCOORDINATE2* coords);

void sharedFunc_800D2200_0_s01(s_SubCharacter*);

void sharedFunc_800D2274_0_s01(s_SubCharacter*);

void sharedFunc_800D2390_0_s01(s_SubCharacter*);

s32 Ai_AirScreamer_Init(s_SubCharacter*);

void sharedFunc_800D2B00_0_s01(s_SubCharacter*);

void sharedFunc_800D2B10_0_s01(s_SubCharacter*);

void sharedFunc_800D2B28_0_s01(s_SubCharacter*);

void sharedFunc_800D2B4C_0_s01(s_SubCharacter*);

void sharedFunc_800D2BB0_0_s01(s_SubCharacter*);

void sharedFunc_800D2BE4_0_s01(s_SubCharacter*);

void sharedFunc_800D2BF4_0_s01(s_SubCharacter* chara);

void sharedFunc_800D3928_0_s01(s_SubCharacter*);

void sharedSymbol_800D3B0C_0_s01(s_SubCharacter*);

s32 sharedFunc_800D62D8_0_s01(s_SubCharacter* chara);

s32  sharedFunc_800D4A80_0_s01(s_SubCharacter*);
void sharedFunc_800D633C_0_s01(s_SubCharacter*);
void sharedFunc_800D63A4_0_s01(s_SubCharacter*);
void sharedFunc_800D6600_0_s01(s_SubCharacter*);
void sharedFunc_800D7560_0_s01(s_SubCharacter*);

void sharedFunc_800D7AB0_0_s01(s_SubCharacter*);

void sharedFunc_800D7EBC_0_s01(s_SubCharacter*);

void sharedFunc_800D81B0_0_s01(s_SubCharacter*);

// `Ai_Lisa` related
void Ai_Lisa_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedFunc_800D08FC_3_s04(s_SubCharacter*, s32, GsCOORDINATE2*);
void sharedFunc_800D0944_3_s04(s_SubCharacter*, GsCOORDINATE2*);
void sharedSymbol_800D0ADC_3_s04(s_SubCharacter*, GsCOORDINATE2*); // `Ai_Lisa_Control`
void Ai_Lisa_Init(s_SubCharacter* chara);

// `Ai_BloodyLisa` related
void Ai_BloodyLisa_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedFunc_800D595C_7_s01(s_SubCharacter*, s32, GsCOORDINATE2*);
void sharedFunc_800D59A4_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coords);
void sharedFunc_800D5B3C_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coords);
s32  sharedFunc_800D908C_0_s00(s32 arg0, s_SubCharacter* chara, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void Ai_BloodyLisa_Init(s_SubCharacter* chara);

// `Ai_Kaufmann` related
void Ai_Kaufmann_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedSymbol_800CF470_3_s00(s_SubCharacter*, GsCOORDINATE2*);
void sharedFunc_800CF2D8_3_s00(s_SubCharacter*, GsCOORDINATE2*);
void sharedFunc_800CF290_3_s00(s_SubCharacter*, s32, GsCOORDINATE2*);
void Ai_Kaufmann_Init(s_SubCharacter* chara);

// `Ai_GhostChildAlessa` related
void Ai_GhostChildAlessa_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedFunc_800D4A2C_7_s01(s_SubCharacter*, s32, GsCOORDINATE2*);
void sharedFunc_800D4A74_7_s01(s_SubCharacter*, GsCOORDINATE2*);
void sharedFunc_800D4C0C_7_s01(s_SubCharacter*, GsCOORDINATE2*);
void Ai_GhostChildAlessa_Init(s_SubCharacter* chara);

// `Ai_Alessa` related
void Ai_Alessa_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords);
void sharedFunc_800CECFC_3_s02(s_SubCharacter*, s32, GsCOORDINATE2*);
void sharedFunc_800CED44_3_s02(s_SubCharacter*, GsCOORDINATE2*);
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
    anim->animInfo_C = animInfo;
    anim->field_10   = 0;
}

#endif
