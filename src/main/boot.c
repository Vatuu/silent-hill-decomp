#include "common.h"

extern s32 D_80010004;
extern struct D_800212DC_Struct {
    s16 unk2;
} D_800212DC;
extern struct D_800212F0_Struct {
    s16 unk2, unkA;
} D_800212F0;
extern struct D_80022C74_Struct { } D_80022C74;
extern struct D_80022C7C_Struct { } D_80022C7C;

extern struct Saved_Reg_Gp_Struct {
    s32 unkD4, unkCA;
    u32 unkC8;
} *saved_reg_gp;

u32 func_80010770(void) {
    s16 temp_v0;
    s32 temp_s1;
    s32 temp_v1;
    s32 phi_s3;
    s32 phi_s1;
    s32 phi_s2;

    func_80013024();
    func_8001335C();
    func_80013E6C();
    func_80011170();
    func_8001310C(0);
    func_800180FC(3);
    *(s32 *)0x1F800000 = 0;
    *(s32 *)0x1F800004 = 0x2000280;
    func_8001310C(0);
    func_8001868C(0x1F800000, 0, 0, 0);
    func_80018478(0);
    func_80018CA8(&D_800212DC);
    func_8001226C();
    func_80010F9C(1, 0x8010A600, &D_80022C74);
    while(func_80010E68() > 0) {
        func_80011260(3);
        func_8001310C(0);
    }
    func_80010F68(3, 0x8010A600);
    func_80010F68(4, 0x801E2600);
    func_800183E0(1);
    phi_s3 = 0xFF;
loop_4:
    D_800212DC.unk2 = (s16) (0x100 - (saved_reg_gp->unkD4 * 0xE0));
    func_80018CA8(&D_800212DC);
    if (phi_s3 >= 0) {
        temp_v1 = saved_reg_gp->unkD4 == 0;
        temp_v0 = 0x100 - (temp_v1 * 0xE0);
        saved_reg_gp->unkD4 = temp_v1;
        D_800212F0.unkA = temp_v0;
        D_800212F0.unk2 = temp_v0;
        func_80018ADC(&D_800212F0);
        phi_s1 = 0;
        phi_s2 = -0x40;
        do {
            *(s8 *)0x1F800003 = 1;
            *(s8 *)0x1F800004 = (s32) (((phi_s1 + 0xD) & 0xF) | (0xE1000000 | 0x280));
            func_80018A10((s8 *)0x1F800000);
            temp_s1 = phi_s1 + 1;
            *(s8 *)0x1F800003 = 4;
            *(s8 *)0x1F800004 = 0x64808080;
            *(s8 *)0x1F800010 = 0x100;
            *(s8 *)0x1F800012 = 0x100;
            *(s8 *)0x1F800008 = (s32) ((phi_s2 & 0xFFFF) + 0xFFF80000);
            *(s8 *)0x1F80000C = (s32) (((saved_reg_gp->unkCA << 6) | (((u32) saved_reg_gp->unkC8 >> 4) & 0x3F)) << 0x10);
            func_80018A10((s8 *)0x1F800000, 0x64808080);
            phi_s1 = temp_s1;
            phi_s2 += 0x80;
        } while (temp_s1 < 3);
        *(s8 *)0x1F800003 = 1;
        *(s8 *)0x1F800004 = 0xE1000240;
        func_80018A10((s8 *)0x1F800000);
        *(s8 *)0x1F800003 = 3;
        *(s8 *)0x1F800007 = 0x62;
        *(s8 *)0x1F800004 = (s8) phi_s3;
        *(s8 *)0x1F800005 = (s8) phi_s3;
        *(s8 *)0x1F800006 = (s8) phi_s3;
        *(s8 *)0x1F80000C = 0xF00280;
        *(s8 *)0x1F800008 = 0;
        func_80018A10((s8 *)0x1F800000);
        func_80011260();
        func_8001310C(0);
        phi_s3 += -4;
        goto loop_4;
    }
    while(func_80010E68() > 0) {
        func_80011260();
        func_8001310C(0);
    }
    func_80010AD0(D_80010004, 0x8010A600, func_80010B24(3));
    func_80010AD0(*(s32 *)0x80010000, 0x801E2600, func_80010B24(4));
    func_80010F9C(7, 0x801E2600, &D_80022C7C);
    while(func_80010E68() > 0) {
        func_80011260();
        func_8001310C(0);
    }
    func_800314EC(&D_80022C74);
    func_80032EE0();
    return 0;
}

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80010AD0);

extern u32 D_8001B11C;

s32 func_80010B24(s32 arg0) {
    return (((u32) *((arg0 * 12) + &D_8001B11C) >> 0x13) & 0xFFF) << 8;
}

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80010B54);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80010B88);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80010C60);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80010CD4);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80010D0C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80010D80);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80010E58);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80010E68);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80010E84);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80010ECC);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80010F34);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80010F68);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80010F9C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011018);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011074);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011170);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_800111DC);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011260);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001137C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_800114C4);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011630);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_800116BC);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_800117AC);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_800117E8);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001182C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011884);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001190C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011A4C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011B24);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011C3C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011C70);

void func_80011CFC(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011D04);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011E4C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011ED0);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011F48);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80011F78);

void func_800120B0(void) {
}

INCLUDE_ASM("asm/main/nonmatchings/boot", func_800120B8);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_800120E4);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012104);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012110);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001211C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001213C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_800121BC);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_800121CC);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_800121DC);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_800121EC);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_800121FC);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001220C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001221C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001222C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001223C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001224C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001225C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001226C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001228C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012374);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_800123EC);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001266C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_8001282C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_800128E8);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012990);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012C10);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012C94);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012CF8);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012D3C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012DE0);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012E1C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012E74);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012E9C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012EC4);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012F2C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012F3C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012F4C);

INCLUDE_ASM("asm/main/nonmatchings/boot", func_80012F7C);
