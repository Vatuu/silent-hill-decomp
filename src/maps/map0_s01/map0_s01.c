#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/map0_s01.h"
#include "inline_no_dmpsx.h"
#include "psyq/gtemac.h"

const u32 D_800CA5C8[4] = {};

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800CCB8C);

bool func_800CD1F8(POLY_FT4** arg0, s32 arg1) // 0x800CD1F8
{
    s32                temp_s2;
    s16                var_v0_3;
    s32                temp_s1;
    s32                temp_s1_2;
    s32                temp_s1_3;
    s32                temp_s2_2;
    s32                temp_s3;
    s32                temp_v0_21;
    s32                temp_v0_6;
    s32                i;
    s32                var_v0_5;
    s32                var_v0_7;
    s32                var_v0_8;
    s32                var_v1_2;
    u16                temp_s0_3;
    u8                 temp_v0_23;
    u8                 temp_v0_24;
    u8                 temp_v0_25;
    u8                 temp_v1_4;
    s32                temp;
    s_MapHdr_field_4C* mapHdrPtr;
    s_func_800CD1F8*   ptr;

    ptr = PSX_SCRATCH;

    if (D_800DE270[arg1].field_B & 0x80)
    {
        D_800DE270[arg1].field_10.s_3.field_2 = CLAMP_LOW(D_800DE270[arg1].field_10.s_3.field_2 - g_DeltaTime0, 0);

        ptr->field_1C0 = SQUARE((D_800DE270[arg1].field_B - 0x80) >> 4);

        if (D_800DE270[arg1].field_10.s_3.field_2 == 0)
        {
            D_800DE270[arg1].field_B += 0x80;

            mapHdrPtr = &D_800DE270[arg1];

            temp_s2 = ((ratan2(D_800DE270[arg1].field_C.s_0.field_2, D_800DE270[arg1].field_10.s_0.field_0) - D_800DE270[arg1].field_0.s_0.field_2) > 0) << 7;

            mapHdrPtr->field_10.s_0.field_2 = temp_s2 |
                                              ((ratan2(D_800DE270[arg1].field_C.s_0.field_0, D_800DE270[arg1].field_10.s_0.field_0) - D_800DE270[arg1].field_4.s_0.field_2) > 0 ? 0x8000 : 0);

            temp_s2_2 = SquareRoot0(SQUARE(D_800DE270[arg1].field_C.s_0.field_2 >> 6) + SQUARE(D_800DE270[arg1].field_10.s_0.field_0 >> 6)) << 6;
            temp_s1   = temp_s2_2 >> 2;
            temp_s3   = temp_s2_2 >> 3;

            D_800DE270[arg1].field_10.s_3.field_2 += CLAMP_HIGH(((temp_s2_2 + (Rng_Rand16() % temp_s1)) - temp_s3), 0x7FFF) / 256;

            temp_s2_2 = SquareRoot0(SQUARE(D_800DE270[arg1].field_C.s_0.field_0 >> 6) + SQUARE(D_800DE270[arg1].field_10.s_0.field_0 >> 6)) << 6;
            temp_s1_2 = temp_s2_2 >> 2;
            temp_s3   = temp_s2_2 >> 3;

            D_800DE270[arg1].field_10.s_3.field_2 += (CLAMP_HIGH(((temp_s2_2 + (Rng_Rand16() % temp_s1_2)) - temp_s3), 0x7FFF) / 256) << 8;
        }
    }
    else
    {
        temp_v0_6      = ratan2(D_800DE270[arg1].field_0.s_0.field_0, D_800DE270[arg1].field_4.s_0.field_0);
        ptr->field_1C0 = SQUARE(D_800DE270[arg1].field_B >> 4);

        temp_s2_2 = ((ptr->field_1C0 + 7) * 0x1800) / 28;

        if (D_800DE270[arg1].field_C.s_0.field_0 > 0)
        {
            D_800DE270[arg1].field_C.s_0.field_0 = CLAMP_LOW(D_800DE270[arg1].field_C.s_0.field_0 - FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_MULTIPLY(temp_s2_2, Math_Sin(temp_v0_6), 0xC), 0xC), 0);
        }
        else if (D_800DE270[arg1].field_C.s_0.field_0 < 0)
        {
            D_800DE270[arg1].field_C.s_0.field_0 = MIN(D_800DE270[arg1].field_C.s_0.field_0 - FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_MULTIPLY(temp_s2_2, Math_Sin(temp_v0_6), 0xC), 0xC), 0);
        }

        if (D_800DE270[arg1].field_10.s_0.field_0 > 0)
        {
            D_800DE270[arg1].field_10.s_0.field_0 = CLAMP_LOW(D_800DE270[arg1].field_10.s_0.field_0 - FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_MULTIPLY(temp_s2_2, Math_Cos(temp_v0_6), 0xC), 0xC), 0);
        }
        else if (D_800DE270[arg1].field_10.s_0.field_0 < 0)
        {
            D_800DE270[arg1].field_10.s_0.field_0 = MIN(D_800DE270[arg1].field_10.s_0.field_0 - FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_MULTIPLY(temp_s2_2, Math_Cos(temp_v0_6), 0xC), 0xC), 0);
        }

        temp_s2_2 = (g_DeltaTime2 * ((D_800DE270[arg1].field_B >> 4) + 9)) >> 4;

        D_800DE270[arg1].field_C.s_0.field_2  = CLAMP_HIGH(D_800DE270[arg1].field_C.s_0.field_2 + temp_s2_2, 0x7FFF);
        D_800DE270[arg1].field_0.s_0.field_0 += FP_MULTIPLY_PRECISE(g_DeltaTime0, D_800DE270[arg1].field_C.s_0.field_0, 0xC);
        D_800DE270[arg1].vy_8                += FP_MULTIPLY_PRECISE(g_DeltaTime0, D_800DE270[arg1].field_C.s_0.field_2, 0xC);
        D_800DE270[arg1].field_4.s_0.field_0 += FP_MULTIPLY_PRECISE(g_DeltaTime0, D_800DE270[arg1].field_10.s_0.field_0, 0xC);

        if (D_800DE270[arg1].field_10.s_3.field_2 & 0x80)
        {
            D_800DE270[arg1].field_0.s_0.field_2 += FP_MULTIPLY_PRECISE(g_DeltaTime0, (D_800DE270[arg1].field_10.s_3.field_2 & 0x7F) << 7, 0xC);
        }
        else
        {
            D_800DE270[arg1].field_0.s_0.field_2 -= FP_MULTIPLY_PRECISE(g_DeltaTime0, (D_800DE270[arg1].field_10.s_3.field_2 & 0x7F) << 7, 0xC);
        }

        if (D_800DE270[arg1].field_10.s_3.field_2 & 0x8000)
        {
            D_800DE270[arg1].field_4.s_0.field_2 += FP_MULTIPLY_PRECISE(g_DeltaTime0, (D_800DE270[arg1].field_10.s_3.field_2 >> 1) & 0x3F80, 0xC);
        }
        else
        {
            D_800DE270[arg1].field_4.s_0.field_2 -= FP_MULTIPLY_PRECISE(g_DeltaTime0, (D_800DE270[arg1].field_10.s_3.field_2 >> 1) & 0x3F80, 0xC);
        }

        Collision_Get(&ptr->field_12C, D_800DE270[arg1].field_0.s_0.field_0, D_800DE270[arg1].field_4.s_0.field_0);

        if (((ptr->field_12C.field_8 == 0) && (D_800DE270[arg1].vy_8 > 0)) || (ptr->field_12C.groundHeight_0 < D_800DE270[arg1].vy_8))
        {
            D_800DE270[arg1].field_A = 0;
        }
    }

    temp_v1_4           = D_800DE270[arg1].field_B;
    *(s32*)&(*arg0)->u0 = ((temp_v1_4 & 3) << 4) + ((temp_v1_4 << 0xA) & 0x3000) + 0xE0000;
    temp_v0_23          = D_800DE270[arg1].field_B;
    *(s32*)&(*arg0)->u1 = ((temp_v0_23 & 3) << 4) + 0xF + (((temp_v0_23 << 0xA) & 0x3000)) + 0x2D0000;
    temp_v0_24          = D_800DE270[arg1].field_B;
    *(u16*)&(*arg0)->u2 = ((temp_v0_24 & 3) << 4) + ((((temp_v0_24 * 4) & 0x30) + 0xF) << 8);
    temp_v0_25          = D_800DE270[arg1].field_B;
    *(u16*)&(*arg0)->u3 = ((temp_v0_25 & 3) << 4) + 0xF + ((((temp_v0_25 * 4) & 0x30) + 0xF) << 8);

    temp_s1_3 = D_800DE270[arg1].field_A - 0x17;

    *(s32*)&ptr->field_158[0].vx = (u16)D_800DE270[arg1].field_0.s_0.field_2 + (D_800DE270[arg1].field_4.s_0.field_2 << 16);
    ptr->field_158[0].vz         = 0;

    Math_RotMatrixZxyNegGte(&ptr->field_158[0], &ptr->field_138);

    ptr->field_178[0].vx = D_800DFB10[temp_s1_3].vx;
    ptr->field_178[0].vy = 0;
    ptr->field_178[0].vz = D_800DFB10[temp_s1_3].vy;

    TransMatrix(&ptr->field_138, &ptr->field_178[0]);

    gte_SetRotMatrix(&ptr->field_138);
    gte_SetTransMatrix(&ptr->field_138);

    temp_s2_2 = ((s16)D_800DFB10[temp_s1_3].vz * (ptr->field_1C0 + 4)) >> 4;

    for (i = 0; i < 4; i++)
    {
        if (!(i & 1))
        {
            var_v1_2 = -temp_s2_2 & 0xFFFF;
        }
        else
        {
            var_v1_2 = temp_s2_2 & 0xFFFF;
        }

        if (i >= 2)
        {
            var_v0_8 = var_v1_2 + (-temp_s2_2 << 16);
        }
        else
        {
            var_v0_8 = var_v1_2 + (temp_s2_2 << 16);
        }

        *(s32*)&ptr->field_158[0].vx = var_v0_8;
        ptr->field_158[0].vz         = 0;

        gte_ldv0(&ptr->field_158[0]);
        gte_rt();
        gte_stlvnl(&ptr->field_178[i]);
    }

    gte_SetRotMatrix(&ptr->field_0.field_C);
    gte_SetTransMatrix(&ptr->field_0.field_C);

    for (i = 0; i < 4; i++)
    {
        *(s32*)&ptr->field_158[i].vx = ((((D_800DE270[arg1].field_0.s_0.field_0 + ptr->field_178[i].vx) >> 4) - (u16)ptr->field_0.field_0.vx) & 0xFFFF) +
                                       ((((D_800DE270[arg1].vy_8 + ptr->field_178[i].vy) >> 4) - ptr->field_0.field_0.vy) << 16);
        ptr->field_158[i].vz = ((D_800DE270[arg1].field_4.s_0.field_0 + ptr->field_178[i].vz) >> 4) - ptr->field_0.field_0.vz;
    }

    gte_ldv3c(&ptr->field_158[0]);
    gte_rtpt();
    gte_stsxy3_g3(*arg0);
    gte_stsz3c(&ptr->field_1C4);
    gte_ldv0(&ptr->field_158[3]);
    gte_rtps();
    gte_stsxy(&ptr->field_1D4);
    gte_stsz(&ptr->field_1D0);

    ptr->field_1C4 = (ptr->field_1C4 + ptr->field_1C8 + ptr->field_1CC + ptr->field_1D0) >> 2;

    if (ptr->field_1C4 <= 0 || (ptr->field_1C4 >> 3) >= 0x800)
    {
        return false;
    }

    if (ABS(ptr->field_1D4.vx) >= 0xC9)
    {
        return false;
    }

    if (ABS(ptr->field_1D4.vy) >= 0xA1)
    {
        return false;
    }

    func_80055A90(&ptr->field_1B8, &ptr->field_1BC, 0x80, ptr->field_1C4 * 0x10);

    *(s32*)&(*arg0)->r0 = (ptr->field_1BC.r + (ptr->field_1BC.g << 8) + (ptr->field_1BC.b << 16) + 0x2E000000);
    *(s32*)&(*arg0)->x3 = *(s32*)&ptr->field_1D4.vx;

    addPrimFast(&g_OrderingTable0[g_ActiveBufferIdx].org[ptr->field_1C4 - 0x1800 >= 0 ? (ptr->field_1C4 - 0x1800) >> 3 : 0], *arg0, 9);

    *arg0 += 1;

    return true;
}

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CE000

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CE4C4

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CE59C

#include "maps/shared/Particle_Update.h" // 0x800CE8A8

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CEE2C

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CF2A4

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800CEFD0_1_s02); // 0x800CF3F4

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CF7BC

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CF8E8

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CF8F0

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CF9A8

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CFA30

#include "maps/shared/Player.h"

#include "maps/shared/Ai_AirScreamer_Update.h" // 0x800D2170

#include "maps/shared/sharedFunc_800D21E4_0_s01.h" // 0x800D21E4

#include "maps/shared/sharedFunc_800D2200_0_s01.h" // 0x800D2200

#include "maps/shared/sharedFunc_800D2274_0_s01.h" // 0x800D2274

#include "maps/shared/sharedFunc_800D2364_0_s01.h" // 0x800D2364

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D2390_0_s01); // 0x800D2390

#include "maps/shared/Ai_AirScreamer_Init.h" // 0x800D2974

#include "maps/shared/sharedFunc_800D2B00_0_s01.h" // 0x800D2B00

#include "maps/shared/sharedFunc_800D2B10_0_s01.h" // 0x800D2B10

#include "maps/shared/sharedFunc_800D2B28_0_s01.h" // 0x800D2B28

#include "maps/shared/sharedFunc_800D2B4C_0_s01.h" // 0x800D2B4C

#include "maps/shared/sharedFunc_800D2BB0_0_s01.h" // 0x800D2BB0

#include "maps/shared/sharedFunc_800D2BE4_0_s01.h" // 0x800D2BE4

#include "maps/shared/sharedFunc_800D2BF4_0_s01.h" // 0x800D2BF4

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", Chara_DamageTake); // 0x800D2C0C

#include "maps/shared/sharedFunc_800D2E04_0_s01.h" // 0x800D2E04

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D2FB4_0_s01);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D31D0_0_s01); // 0x800D31D0

#include "maps/shared/sharedFunc_800D3430_0_s01.h" // 0x800D3430

#include "maps/shared/sharedFunc_800D3508_0_s01.h" // 0x800D3508

#include "maps/shared/sharedFunc_800D3630_0_s01.h" // 0x800D3630

#include "maps/shared/sharedFunc_800D3758_0_s01.h" // 0x800D3758

#include "maps/shared/sharedFunc_800D3814_0_s01.h" // 0x800D3814

#include "maps/shared/sharedFunc_800D3928_0_s01.h" // 0x800D3928

void func_800D39F4(s_SubCharacter* chara) // 0x800D39F4
{
    q19_12 animTime;

    // TODO: `Character_AnimSet` doesn't match?
    chara->model_0.anim_4.status_0 = ANIM_STATUS(19, true);
    animTime = func_80044918(&chara->model_0.anim_4)->startKeyframeIdx_C;
    chara->model_0.stateStep_3 = 7;
    chara->model_0.anim_4.keyframeIdx_8 = animTime;
    chara->model_0.anim_4.time_4 = FP_TO(animTime, Q12_SHIFT);
}

void func_800D3A3C(s_SubCharacter* chara) // 0x800D3A3C
{
    q19_12 animTime;
    s32    idx;

    idx = D_800A98FC[chara->model_0.charaId_0];
    Ai_AirScreamer_Update(chara, (&D_800A992C[idx])->animFile1_8, (&D_800A992C[idx])->npcCoords_14);

    chara->model_0.anim_4.status_0 = ANIM_STATUS(17, true);
    animTime = func_80044918(&chara->model_0.anim_4)->startKeyframeIdx_C;
    chara->model_0.stateStep_3 = 3;
    chara->model_0.anim_4.keyframeIdx_8 = animTime;
    chara->model_0.anim_4.time_4 = FP_TO(animTime, Q12_SHIFT);
}

void func_800D3AC0(s_SubCharacter* chara)
{
    switch(chara->model_0.stateStep_3)
    {
        case 1:
        case 3:
        case 5:
            chara->model_0.stateStep_3++;
            break;

        default:
            break;
    }
}

#include "maps/shared/sharedSymbol_800D3B0C_0_s01.h" // 0x800D3B0C

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CA9F0);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CA9F4);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CAA00);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CAA18);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CAA30);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CAA48);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", sharedData_800CAA98_0_s01);

#include "maps/shared/sharedFunc_800D3CC4_0_s01.h" // 0x800D3CC4

#include "maps/shared/sharedFunc_800D3DFC_0_s01.h" // 0x800D3DFC

void func_800D3EB8(s_SubCharacter* chara) // 0x800D3EB8
{
    q19_12 damage;
    bool   cond1;
    bool   cond0;
    s32    temp_s3;
    u32    animStatus;
    s32    animStatus12;
    bool   activeAnimStatus;
    u32    stateStep;

    animStatus = chara->model_0.anim_4.status_0;
    animStatus12 = ANIM_STATUS(12, true);

    sharedFunc_800D5638_0_s01(chara);

    activeAnimStatus = ANIM_STATUS(ANIM_STATUS_IDX_GET(animStatus), true);

    stateStep = chara->model_0.stateStep_3;
    switch (stateStep)
    {
        case 0:
            temp_s3 = func_800D5F00(chara);
            cond0 = false;
            cond1 = chara->position_18.vy >= Q12(8.0f);

            if (func_800808AC(chara->position_18.vx, chara->position_18.vz) == 7)
            {
                cond0 = chara->position_18.vy >= func_80080884(chara->position_18.vx, chara->position_18.vz);
            }

            if (cond1)
            {
                Chara_DamageTake(chara, Q12(0.0f));

                chara->position_18.vx = g_SysWork.player_4C.chara_0.position_18.vx + Q12(100.0f);
                chara->position_18.vz = g_SysWork.player_4C.chara_0.position_18.vz + Q12(100.0f);

                sharedFunc_800D3DFC_0_s01(chara);
                break;
            }

            if (cond0)
            {
                Chara_DamageTake(chara, Q12(0.0f));
                sharedFunc_800D2364_0_s01(chara);

                chara->position_18.vx = g_SysWork.player_4C.chara_0.position_18.vx + Q12(100.0f);
                chara->position_18.vz = g_SysWork.player_4C.chara_0.position_18.vz + Q12(100.0f);

                sharedFunc_800D3DFC_0_s01(chara);
                break;
            }

            if (chara->health_B0 <= Q12(0.0f))
            {
                Chara_DamageTake(chara, Q12(0.0f));

                if (animStatus == ANIM_STATUS(26, true) && temp_s3 == 1)
                {
                    chara->health_B0 = NO_VALUE;

                    func_800622B8(3, chara, ANIM_STATUS(4, true), 2);

                    chara->model_0.stateStep_3 = temp_s3;

                    sharedFunc_800D3DFC_0_s01(chara);
                    break;
                }
            }
            else
            {
                chara->flags_3E |= CharaFlag_Unk2;

                if (Chara_DamageTake(chara, Q12(1.0f)) == 4)
                {
                    if (chara->health_B0 <= Q12(0.0f))
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(5, false);
                        chara->properties_E4.player.flags_11C |= PlayerFlag_Unk6;
                        break;
                    }

                    chara->model_0.anim_4.status_0 = ANIM_STATUS(12, false);
                    chara->model_0.stateStep_3 = 2;
                    chara->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
                    break;
                }

                damage = g_DeltaTime0 * 10;
                if (damage < chara->health_B0)
                {
                    chara->health_B0 -= damage;
                }
                else if (chara->health_B0 > Q12(0.0f))
                {
                    chara->health_B0 = Q12(0.0f);
                }
            }
            break;

        case 1:
            Chara_DamageTake(chara, Q12(0.0f));
            break;

        case 2:
            Chara_DamageTake(chara, Q12(0.5f));

            if (activeAnimStatus != animStatus12)
            {
                chara->model_0.stateStep_3 = 0;
            }
            break;
    }
}

void func_800D4114(void) {}

void func_800D411C(void) {}

void func_800D4124(void) {}

void func_800D412C(void) {}

void func_800D4134(void) {}

void func_800D413C(void) {}

void func_800D4144(void) {}

void func_800D414C(void) {}

void func_800D4154(void) {}

void func_800D415C(void) {}

void func_800D4164(void) {}

void func_800D416C(void) {}

void func_800D4174(void) {}

void func_800D417C(void) {}

void func_800D4184(void) {}

void func_800D418C(void) {}

void func_800D4194(void) {}

void func_800D419C(void) {}

void func_800D41A4(void) {}

void func_800D41AC(void) {}

void func_800D41B4(void) {}

void func_800D41BC(void) {}

void func_800D41C4(void) {}

void func_800D41CC(void) {}

void func_800D41D4(void) {}

void func_800D41DC(void) {}

void func_800D41E4(void) {}

void func_800D41EC(void) {}

void func_800D41F4(void) {}

void func_800D41FC(void) {}

void func_800D4204(void) {}

void func_800D420C(void) {}

void func_800D4214(void) {}

void func_800D421C(void) {}

void func_800D4224(void) {}

void func_800D422C(void) {}

void func_800D4234(void) {}

void func_800D423C(void) {}

void func_800D4244(void) {}

void func_800D424C(void) {}

void func_800D4254(void) {}

void func_800D425C(void) {}

void func_800D4264(void) {}

void func_800D426C(s_SubCharacter* chara) // 0x800D426C
{
    s32 animStatus;

    animStatus = chara->model_0.anim_4.status_0;

    if (chara->model_0.stateStep_3 != 1)
    {
        if (chara->model_0.stateStep_3 == 0 && animStatus == ANIM_STATUS(2, true) && chara->model_0.anim_4.keyframeIdx_8 < 8204)
        {
            chara->properties_E4.unk0.properties_120.val32 = Q12(4.0f);
            chara->model_0.stateStep_3 = 1;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk5;
            chara->flags_3E |= CharaFlag_Unk3;
        }
    }
    else if (ANIM_STATUS(ANIM_STATUS_IDX_GET(animStatus), true) == ANIM_STATUS(19, true))
    {
        chara->model_0.stateStep_3 = 2;
        chara->properties_E4.unk0.properties_120.val32 = Q12(4.0f);
    }

    sharedFunc_800D529C_0_s01(chara, Q12(1.0f), func_80080478(&chara->position_18, &g_SysWork.player_4C.chara_0.position_18));
    sharedFunc_800D598C_0_s01(chara);

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            if (!chara->properties_E4.unk0.properties_120.val32 ||
                chara == &g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353] ||
                Math_Distance2dGet(&chara->position_18, &g_SysWork.player_4C.chara_0.position_18) > Q12(6.5f))
            {
                chara->model_0.state_2 = 47;
                chara->model_0.stateStep_3 = 0;
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk4;
                return;
            }

        default:
            return;

        case 1:
        case 2:
            chara->model_0.state_2 = 50;
            chara->model_0.stateStep_3 = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            return;

        case 3:
        case 4:
            chara->model_0.state_2 = 51;
            chara->model_0.stateStep_3 = 0;
            if (chara->health_B0 <= 0)
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }
}

void func_800D4420(s_SubCharacter* chara) // 0x800D4420
{
    q19_12 dist0;
    q19_12 deltaY;
    q19_12 angle;
    q19_12 dist;

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            chara->properties_E4.unk0.properties_120.val32 = Q12(1.5f);
            chara->model_0.stateStep_3 = 1;
            break;

        case 1:
            if (Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8) < Q12(0.5f))
            {
                chara->model_0.stateStep_3 = 0;
            }
            break;
    }

    func_800D53AC(chara);
    sharedFunc_800D57C8_0_s01(chara);

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            dist0 = NO_VALUE;
            deltaY = chara->properties_E4.unk0.field_F8.vy - chara->position_18.vy;
            if (deltaY > Q12(-0.2f) && deltaY < Q12(0.8f))
            {
                dist0 = chara->field_D4 + Q12(0.15f);
            }

            dist = Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8);
            if (dist < dist0)
            {
                angle = FP_ANGLE_NORM_S(func_80080478(&chara->position_18, &chara->properties_E4.unk0.field_F8) - chara->rotation_24.vy);
                if (angle >= FP_ANGLE(-8.0f) && angle < FP_ANGLE(8.0f))
                {
                    chara->model_0.state_2 = 49;
                    chara->model_0.stateStep_3 = 0;
                }
            }
            break;

        case 1:
        case 2:
            chara->model_0.state_2 = 50;
            chara->model_0.stateStep_3 = 0;
            chara->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            break;

        case 3:
        case 4:
            chara->model_0.state_2 = 51;
            chara->model_0.stateStep_3 = 0;

            if (chara->health_B0 <= Q12(0.0f))
            {
                chara->properties_E4.player.flags_11C |= PlayerFlag_Unk6;
            }
            else
            {
                chara->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            }
            break;
    }
}

void func_800D45BC(s_SubCharacter* chara) // 0x800D45BC
{
    u32 temp_v0;

    if (!chara->model_0.stateStep_3)
    {
        chara->properties_E4.unk0.properties_120.val32 = Q12(2.0f);
        chara->model_0.stateStep_3 = 1;
    }

    func_800D53AC(chara);
    sharedFunc_800D5B10_0_s01(chara);

    temp_v0 = Chara_DamageTake(chara, Q12(1.0f));
    switch (temp_v0)
    {
        case 0:
            if (!chara->properties_E4.unk0.properties_120.val32 ||
                Math_Distance2dGet(&chara->position_18, &g_SysWork.player_4C.chara_0.position_18) > Q12(2.0f))
            {
                chara->model_0.state_2 = 47;
                chara->model_0.stateStep_3 = 0;
                break;
            }

        default:
            break;

        case 1:
        case 2:
            chara->model_0.state_2 = 50;
            chara->model_0.stateStep_3 = 0;
            chara->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            break;

        case 3:
        case 4:
            chara->model_0.state_2 = 51;
            chara->model_0.stateStep_3 = 0;

            if (chara->health_B0 <= Q12(0.0f))
            {
                chara->properties_E4.player.flags_11C |= PlayerFlag_Unk6;
            }
            else
            {
                chara->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            }
            break;
    }
}

void func_800D46C4(s_SubCharacter* chara) // 0x800D46C4
{
    bool cond0;
    bool cond1;
    s32  animStatus;

    cond0 = false;
    animStatus = chara->model_0.anim_4.status_0;
    cond1 = false;

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            chara->model_0.stateStep_3 = 1;

        case 1:
            if (animStatus == ANIM_STATUS(19, true))
            {
                chara->model_0.stateStep_3 = 2;
                chara->model_0.anim_4.status_0 = 4;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(2, true) && chara->model_0.anim_4.keyframeIdx_8 < 8192)
            {
                chara->model_0.stateStep_3 = 3;
                chara->properties_E4.player.flags_11C |= PlayerFlag_Unk5;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(19, true))
            {
                cond0 = true;
            }
            else if (chara->field_44.field_8 == NO_VALUE)
            {
                cond0 = true;
                cond1 = true;
                chara->model_0.stateStep_3 = 4;
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                cond0 = true;
                cond1 = true;
            }
            break;
    }

    func_800D53AC(chara);
    sharedFunc_800D5C90_0_s01(chara);

    switch (Chara_DamageTake(chara, Q12(1.2f)))
    {
        case 0: 
            if (cond0)
            {
                if (!cond1)
                {
                    if (func_80080514() >= FP_ANGLE(180.0f))
                    {
                        chara->model_0.state_2 = 47;
                    }
                    else
                    {
                        chara->model_0.state_2 = 48;
                    }
                }
                else
                {
                    chara->model_0.state_2 = 48;
                }

                chara->model_0.stateStep_3 = 0;
                break;
            }

        default:
            break;

        case 1: 
        case 2: 
            chara->model_0.state_2 = 50;
            chara->model_0.stateStep_3 = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3: 
        case 4: 
            chara->model_0.state_2 = 51;
            chara->model_0.stateStep_3 = 0;

            if (chara->health_B0 <= Q12(0.0f))
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }
}

void func_800D4894(s_SubCharacter* chara)
{
    s32  damageType;
    s32  animStatus;
    u32  stateStep;
    bool cond;

    stateStep  = chara->model_0.stateStep_3;
    animStatus = chara->model_0.anim_4.status_0;
    cond       = false;

    switch (stateStep)
    {
        case 0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(7, false);
                chara->model_0.stateStep_3     = 1;
            }
            break;

        case 1:
            if (animStatus != ANIM_STATUS(7, false))
            {
                chara->model_0.stateStep_3 = 2;
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;

        case 2:
            if (animStatus != ANIM_STATUS(7, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800D5D80_0_s01(chara);

    damageType = Chara_DamageTake(chara, 0x999);
    if (damageType >= 0)
    {
        if (damageType < 3)
        {
            if (cond)
            {
                chara->model_0.state_2 = ANIM_STATUS(23, true);
                chara->model_0.stateStep_3 = 0;
                chara->properties_E4.unk0.field_E8_8 = 3;
            }
        }
        else if (damageType < 5)
        {
            chara->model_0.state_2     = ANIM_STATUS(25, true);
            chara->model_0.stateStep_3 = 0;

            if (chara->health_B0 <= Q12(0.0f))
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
        }
    }
}

void func_800D49B0(s_SubCharacter* chara) // 0x800D49B0
{
    s32  animStatus;
    u32  stateStep;
    bool cond;

    stateStep  = chara->model_0.stateStep_3;
    animStatus = chara->model_0.anim_4.status_0;
    cond       = false;

    switch (stateStep)
    {
        case 0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                chara->model_0.stateStep_3 = 1;
            }
            break;

        case 1:
            if (animStatus != ANIM_STATUS(10, false))
            {
                chara->model_0.stateStep_3 = 2;
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;

        case 2:
            if (animStatus != ANIM_STATUS(10, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800D5E14_0_s01(chara);
    Chara_DamageTake(chara, Q12(0.6f));

    if (cond)
    {
        chara->model_0.state_2 = 2;
        chara->model_0.stateStep_3 = 0;
        chara->properties_E4.unk0.field_E8_8 = 1;
    }
}

#include "maps/shared/sharedFunc_800D4A80_0_s01.h"

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D4AEC);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D4E84_0_s01); // 0x800D4E84

#include "maps/shared/sharedFunc_800D5274_0_s01.h" // 0x800D5274

#include "maps/shared/sharedFunc_800D529C_0_s01.h" // 0x800D529C

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D53AC);

#include "maps/shared/sharedFunc_800D5638_0_s01.h" // 0x800D5638

#include "maps/shared/sharedFunc_800D569C_0_s01.h" // 0x800D569C

#include "maps/shared/sharedFunc_800D57C8_0_s01.h" // 0x800D57C8

#include "maps/shared/sharedFunc_800D598C_0_s01.h" // 0x800D598C

#include "maps/shared/sharedFunc_800D5B10_0_s01.h" // 0x800D5B10

#include "maps/shared/sharedFunc_800D5C90_0_s01.h" // 0x800D5C90

#include "maps/shared/sharedFunc_800D5D80_0_s01.h" // 0x800D5D80

#include "maps/shared/sharedFunc_800D5E14_0_s01.h" // 0x800D5E14

#include "maps/shared/sharedFunc_800D5E78_0_s01.h" // 0x800D5E78

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", func_800D5F00);

#include "maps/shared/sharedFunc_800D62D8_0_s01.h" // 0x800D62D8

#include "maps/shared/sharedFunc_800D633C_0_s01.h" // 0x800D633C

#include "maps/shared/sharedFunc_800D63A4_0_s01.h" // 0x800D63A4

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D6600_0_s01); // 0x800D6600

#include "maps/shared/sharedFunc_800D6A60_0_s01.h" // 0x800D6A60

#include "maps/shared/sharedFunc_800D6C7C_0_s01.h" // 0x800D6C7C

#include "maps/shared/sharedFunc_800D6EC4_0_s01.h" // 0x800D6EC4

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D7120_0_s01);

#include "maps/shared/sharedFunc_800D71F0_0_s01.h" // 0x800D71F0

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D72E8_0_s01);

#include "maps/shared/sharedFunc_800D7440_0_s01.h" // 0x800D7440

#include "maps/shared/sharedFunc_800D7560_0_s01.h" // 0x800D7560

#include "maps/shared/sharedFunc_800D76A0_0_s01.h" // 0x800D76A0

#include "maps/shared/sharedFunc_800D7714_0_s01.h" // 0x800D7714

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D77D0_0_s01);

#include "maps/shared/sharedFunc_800D7AB0_0_s01.h" // 0x800D7AB0

#include "maps/shared/sharedFunc_800D7B14_0_s01.h" // 0x800D7B14

q19_12 Model_AnimDurationGet(s_Model* model) // 0x800D7E88
{
    return Anim_DurationGet(model, func_80044918(&model->anim_4));
}

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D7EBC_0_s01); // 0x800D7EBC

#include "maps/shared/sharedFunc_800D81B0_0_s01.h" // 0x800D81B0

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D81D0_0_s01);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D8244_0_s01);

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01", sharedFunc_800D82B8_0_s01); // 0x800D82B8

#include "maps/shared/sharedFunc_800D8714_0_s01.h" // 0x800D8714

#include "maps/shared/sharedFunc_800D87FC_0_s01.h" // 0x800D87FC

#include "maps/shared/sharedFunc_800D8804_0_s01.h" // 0x800D8804
