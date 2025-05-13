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

// MAP3_S03 puppet nurse/doctor funcs
void sharedFunc_800CDA88_3_s03(s_SubCharacter*);
void sharedFunc_800CDF24_3_s03(s_SubCharacter*);
void sharedFunc_800D01D0_3_s03(s_SubCharacter*);
void sharedFunc_800D02E4_3_s03(s_SubCharacter*, s32);
void sharedFunc_800D03E4_3_s03(s_SubCharacter*);
void sharedFunc_800D06AC_3_s03(s_SubCharacter*, s32, s32);
void sharedFunc_800D0828_3_s03(s_SubCharacter*, s32);
void sharedFunc_800D0968_3_s03(s_SubCharacter*, s32);
void sharedFunc_800CDAB8_3_s03(s_SubCharacter* chara, s32 arg1, s32 arg2);

#endif
