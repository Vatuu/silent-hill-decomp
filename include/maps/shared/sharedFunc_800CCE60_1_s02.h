#include "inline_no_dmpsx.h"
#include <psyq/gtemac.h>

void sharedFunc_800CCE60_1_s02(void)
{
    typedef struct
    {
        s_func_8005E89C field_0;
        SVECTOR         field_12C;
        u8              unk_134[8];
        DVECTOR         field_13C[16][2];
        s32             field_1BC[16][2];
        u8              field_23C[16][2];
        s16             field_25C;
        s16             field_25E;
        s16             field_260;
        s16             field_262;
        s16             field_264[2][2];
        s16             field_26C;
        u16             field_26E;
    } s_func_800CCE60;

    POLY_GT4*        poly;
    s32              sp14;
    s32              sp18;
    s32              sp1C;
    s32              sp20;
    s32              temp_lo_3;
    s32              temp_s0;
    s32              temp_v0_8;
    s32              temp_v1_3;
    s32              var_fp;
    s32              var_s2;
    s32              var_s3;
    s32              var_s4;
    s32              var_t2_2;
    s32              var_t3_2;
    s32              var_t5;
    s_func_800CCE60* ptr;

    ptr = PSX_SCRATCH;

    sp14 = 0;

    poly = (POLY_GT4*)GsOUT_PACKET_P;

    ptr->field_260 = 0x4E;
    ptr->field_262 = 0x2D;

    for (sp20 = 0; sp20 < sharedData_800E30C8_1_s02.field_78; sp20++)
    {
        temp_s0 = sharedData_800E30C8_1_s02.field_3C[sp20] >> 1;

        if (sharedData_800E30C8_1_s02.field_30[sp20] == 0)
        {
            ptr->field_25C       = Math_Sin(sharedData_800E30C8_1_s02.field_34[sp20]);
            ptr->field_25E       = Math_Cos(sharedData_800E30C8_1_s02.field_34[sp20]);
            ptr->field_264[0][0] = Q12_MULT(temp_s0, ptr->field_25E);
            ptr->field_264[0][1] = -ptr->field_264[0][0];
            ptr->field_264[1][0] = Q12_MULT(-temp_s0, ptr->field_25C);
            ptr->field_264[1][1] = -ptr->field_264[1][0];
        }
        else
        {
            ptr->field_264[0][0] = Q12_MULT(temp_s0, Math_Sin(ptr->field_0.field_30.vy - 0x400));
            ptr->field_264[1][0] = Q12_MULT(temp_s0, Math_Cos(ptr->field_0.field_30.vy - 0x400));
            ptr->field_264[0][1] = Q12_MULT(temp_s0, Math_Sin(ptr->field_0.field_30.vy + 0x400));
            ptr->field_264[1][1] = Q12_MULT(temp_s0, Math_Cos(ptr->field_0.field_30.vy + 0x400));
        }

        if (sp20 == (sharedData_800E30C8_1_s02.field_78 - 1))
        {
            ptr->field_26E = sharedData_800E30C8_1_s02.field_28[sp20] - sharedData_800E30C8_1_s02.field_28[sharedData_800E30C8_1_s02.field_78];
        }
        else
        {
            ptr->field_26E = 0xFFFF;
        }

        var_s4 = 0;

        for (var_t5 = 0;; var_t5++)
        {
            var_s2 = 0;

            if (sharedData_800E30C8_1_s02.field_30[sp20] == 0)
            {
                if (var_s4 == 0)
                {
                    ptr->field_26C = sharedData_800E30C8_1_s02.field_10[sp20];
                }
                else
                {
                    if (var_s4 == sharedData_800E30C8_1_s02.field_28[sp20])
                    {
                        ptr->field_26C = sharedData_800E30C8_1_s02.field_10[sp20 + 1];
                    }
                    else
                    {
                        ptr->field_26C = sharedData_800E30C8_1_s02.field_10[sp20] + ((sharedData_800E30C8_1_s02.field_10[sp20 + 1] - sharedData_800E30C8_1_s02.field_10[sp20]) * var_s4) / sharedData_800E30C8_1_s02.field_28[sp20];
                    }
                }

                if (ptr->field_26E < var_s4)
                {
                    var_s2 = Q12(var_s4 - ptr->field_26E) / sharedData_800E30C8_1_s02.field_28[sharedData_800E30C8_1_s02.field_78];

                    temp_s0 = Q12_MULT_PRECISE(0x1000 - var_s2, sharedData_800E30C8_1_s02.field_3C[sp20] >> 1) +
                              Q12_MULT_PRECISE(var_s2, sharedData_800E30C8_1_s02.field_3C[sp20 + 1] >> 1);

                    ptr->field_264[0][0] = Q12_MULT(temp_s0, ptr->field_25E);
                    ptr->field_264[0][1] = -ptr->field_264[0][0];
                    ptr->field_264[1][0] = Q12_MULT(-temp_s0, ptr->field_25C);
                    ptr->field_264[1][1] = -ptr->field_264[1][0];
                }
            }

            for (var_s3 = 0; var_s3 < 2; var_s3++)
            {
                if (sharedData_800E30C8_1_s02.field_30[sp20] == 0)
                {
                    var_fp = sharedData_800E30C8_1_s02.field_0[sp20] + ptr->field_264[0][var_s3] + Q12_MULT(var_s4, ptr->field_25C);
                    sp18   = ptr->field_26C;
                    sp1C   = sharedData_800E30C8_1_s02.field_18[sp20] + ptr->field_264[1][var_s3] + Q12_MULT(var_s4, ptr->field_25E);
                }
                else
                {
                    var_fp = sharedData_800E30C8_1_s02.field_0[sp20] + ptr->field_264[0][var_s3];
                    sp18   = sharedData_800E30C8_1_s02.field_10[sp20] + var_s4;
                    sp1C   = sharedData_800E30C8_1_s02.field_18[sp20] + ptr->field_264[1][var_s3];
                }

                ptr->field_23C[var_t5][var_s3] = Q12_MULT_PRECISE(Math_Cos(var_s2 >> 2), func_80055D78(var_fp, sp18, sp1C));

                if (sp20 < (sharedData_800E30C8_1_s02.field_78 - 1) && sharedData_800E30C8_1_s02.field_30[sp20] == 0)
                {
                    temp_s0 = sharedData_800E30C8_1_s02.field_30[sp20 + 1];

                    if (temp_s0 == 0)
                    {
                        temp_v0_8 = Math_Sin(sharedData_800E30C8_1_s02.field_34[sp20] - sharedData_800E30C8_1_s02.field_34[sp20 + 1]);
                        var_s2    = Q12_MULT(sharedData_800E30C8_1_s02.field_5C[sp20 + 1], temp_v0_8);

                        if (var_s3 == 0)
                        {
                            var_s2 = -var_s2;
                        }

                        temp_v1_3 = sharedData_800E30C8_1_s02.field_28[sp20] - var_s4;

                        if (temp_v1_3 < var_s2)
                        {
                            ptr->field_23C[var_t5][var_s3] = Q12_MULT_PRECISE(temp_v1_3 >= 0 ? Q12(temp_v1_3) / var_s2 : temp_s0 / var_s2, ptr->field_23C[var_t5][var_s3]);
                        }
                    }
                }

                if (sp20 > 0)
                {
                    if (sharedData_800E30C8_1_s02.field_30[sp20] == 0 && sharedData_800E30C8_1_s02.field_30[sp20 - 1] == 0)
                    {
                        var_s2 = FP_MULTIPLY(sharedData_800E30C8_1_s02.field_5C[sp20 - 1],
                                             Math_Sin(sharedData_800E30C8_1_s02.field_34[sp20 - 1] - sharedData_800E30C8_1_s02.field_34[sp20]), Q12_SHIFT);

                        if (var_s3 == 0)
                        {
                            var_s2 = -var_s2;
                        }

                        if (var_s4 < var_s2)
                        {
                            ptr->field_23C[var_t5][var_s3] = Q12_MULT_PRECISE(Q12(var_s4) / var_s2, ptr->field_23C[var_t5][var_s3]);
                        }
                    }
                }

                *(s32*)&ptr->field_12C = (((var_fp >> 4) - (u16)ptr->field_0.field_0.vx) & 0xFFFF) + (((sp18 >> 4) - ptr->field_0.field_0.vy) << 16);
                ptr->field_12C.vz      = (sp1C >> 4) - ptr->field_0.field_0.vz;

                gte_ldv0(&ptr->field_12C);
                gte_rtps();
                gte_stsxy(&ptr->field_13C[var_t5][var_s3]);
                gte_stsz(&ptr->field_1BC[var_t5][var_s3]);
            }

            if (var_s4 != sharedData_800E30C8_1_s02.field_28[sp20])
            {
                if (var_t5 != 0)
                {
                    if (sharedData_800E30C8_1_s02.field_28[sp20] < var_s4 + sharedData_800E30C8_1_s02.field_44[sp20])
                    {
                        sp14   = sharedData_800E30C8_1_s02.field_28[sp20] - var_s4;
                        var_s4 = sharedData_800E30C8_1_s02.field_28[sp20];
                    }
                    else
                    {
                        var_s4 += sharedData_800E30C8_1_s02.field_44[sp20];
                    }
                }
                else
                {
                    var_s4 += sharedData_800E30C8_1_s02.field_54[sp20];
                }
            }
            else
            {
                break;
            }
        }

        for (var_s3 = 0; var_s3 < var_t5; var_s3++)
        {
            if (var_s3 == 0)
            {
                temp_lo_3 = (sharedData_800E30C8_1_s02.field_54[sp20] << 6) / sharedData_800E30C8_1_s02.field_44[sp20];
                var_t2_2  = temp_lo_3;
                var_t2_2  = 0x7F - var_t2_2;
                var_t3_2  = temp_lo_3;
            }
            else
            {
                var_t2_2 = 0x40;
                if ((var_s3 + 1) == var_t5)
                {
                    var_t3_2 = (sp14 << 6) / sharedData_800E30C8_1_s02.field_44[sp20];
                }
                else
                {
                    var_t3_2 = 0x3F;
                }
            }

            setPolyGT4(poly);

            setXY0Fast(poly, ptr->field_13C[var_s3][0].vx, ptr->field_13C[var_s3][0].vy);
            setXY1Fast(poly, ptr->field_13C[var_s3][1].vx, ptr->field_13C[var_s3][1].vy);
            setXY2Fast(poly, ptr->field_13C[var_s3 + 1][0].vx, ptr->field_13C[var_s3 + 1][0].vy);
            setXY3Fast(poly, ptr->field_13C[var_s3 + 1][1].vx, ptr->field_13C[var_s3 + 1][1].vy);

            setSemiTrans(poly, 1);

            setRGB0Fast(poly, ptr->field_23C[var_s3][0], ptr->field_23C[var_s3][0], ptr->field_23C[var_s3][0]);
            setRGB1Fast(poly, ptr->field_23C[var_s3][1], ptr->field_23C[var_s3][1], ptr->field_23C[var_s3][1]);
            setRGB2Fast(poly, ptr->field_23C[var_s3 + 1][0], ptr->field_23C[var_s3 + 1][0], ptr->field_23C[var_s3 + 1][0]);
            setRGB3Fast(poly, ptr->field_23C[var_s3 + 1][1], ptr->field_23C[var_s3 + 1][1], ptr->field_23C[var_s3 + 1][1]);

            *(s32*)&poly->u0 = (var_t2_2 << 8) + 0x40 + (ptr->field_260 << 16);
            *(s32*)&poly->u1 = (var_t2_2 << 8) + 0x5F + (ptr->field_262 << 16);
            *(u16*)&poly->u2 = ((var_t2_2 + var_t3_2) << 8) + 0x40;
            *(u16*)&poly->u3 = ((var_t2_2 + var_t3_2) << 8) + 0x5F;

            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[(((ptr->field_1BC[var_s3][0] + ptr->field_1BC[var_s3][1] + ptr->field_1BC[var_s3 + 1][0] + ptr->field_1BC[var_s3 + 1][1]) >> 2) + 0x100) >> 3], poly);
            poly++;
        }

        sharedData_800E30C8_1_s02.field_54[sp20] += Q12_MULT_PRECISE(g_DeltaTime, sharedData_800E30C8_1_s02.field_4C[sp20]);

        while (sharedData_800E30C8_1_s02.field_54[sp20] >= sharedData_800E30C8_1_s02.field_44[sp20])
        {
            sharedData_800E30C8_1_s02.field_54[sp20] -= sharedData_800E30C8_1_s02.field_44[sp20];
        }
    }

    GsOUT_PACKET_P = (PACKET*)poly;
}