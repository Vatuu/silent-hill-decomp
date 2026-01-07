extern s_func_80070400_1 sharedData_800EEE54_2_s00[];
extern s_func_80070400_1 sharedData_800EF0AC_2_s00[];
extern s_func_80070400_1 sharedData_800EF19C_2_s00;
extern s_func_80070400_1 sharedData_800EF1B0_2_s00[];
extern s_func_80070400_1 sharedData_800EF250_2_s00[];
extern s_func_80070400_1 sharedData_800EF28C_2_s00[];
extern s_func_80070400_1 sharedData_800EF368_2_s00[];
extern s_func_80070400_1 sharedData_800EF4BC_2_s00;
extern s_func_80070400_1 sharedData_800EF4D0_2_s00[];
extern s_func_80070400_1 sharedData_800EF624_2_s00;
extern s_func_80070400_1 sharedData_800EF638_2_s00[];
extern s_func_80070400_1 sharedData_800EF7A0_2_s00;
extern s_func_80070400_1 sharedData_800EF7B4_2_s00[];
extern s_func_80070400_1 sharedData_800EFA84_2_s00[];
extern s_func_80070400_1 sharedData_800EFCDC_2_s00[];
extern s_func_80070400_1 sharedData_800EFF48_2_s00[];
extern s_func_80070400_1 sharedData_800F0038_2_s00[];
extern s_func_80070400_1 sharedData_800F00EC_2_s00[];
extern s_func_80070400_1 sharedData_800F0268_2_s00[];
extern s_func_80070400_1 sharedData_800F03A8_2_s00[];
extern s_func_80070400_1 sharedData_800F04C0_2_s00[];

#define CopyData(arg0, data)                  \
{                                             \
    s32 __temp;                               \
    s32 __temp2;                              \
                                              \
    arg0->field_C8.field_0 = data.field_0;    \
                                              \
    __temp                 = data.field_2;    \
    arg0->field_C8.field_2 = __temp;          \
    arg0->field_C8.field_4 = data.field_4;    \
                                              \
    __temp                   = data.field_6;  \
    arg0->field_C8.field_6   = __temp;        \
    arg0->field_D8.offsetX_4 = data.field_10; \
                                              \
    __temp                   = data.field_12; \
    arg0->field_D8.offsetZ_6 = __temp;        \
    arg0->field_D4.radius_0  = data.field_8;  \
    arg0->field_D8.offsetX_0 = data.field_C;  \
                                              \
    __temp                   = data.field_E;  \
    arg0->field_D8.offsetZ_2 = __temp;        \
                                              \
    __temp2                = data.field_A;    \
    arg0->field_D4.field_2 = __temp2;         \
}

#define ANIM_INDEX_FROM_KEYFRAME(offset, keyframe, max, count) \
    ((offset) - ((keyframe) > (count)) < (max) ? ((offset) - ((keyframe) > (count))) : ((max) - 1))

void sharedFunc_800E6338_2_s00(s_SubCharacter* groaner)
{
    s32 temp_s0;
    s32 keyframeIdx1;
    s32 keyframeIdx0;
    s32 temp;

    switch (groaner->model_0.anim_4.status_0)
    {
        case 18:
            if (groaner->properties_E4.groaner.relKeyframeIdx_100 == 5)
            {
                func_80070400(groaner, &sharedData_800EF4BC_2_s00, &sharedData_800EF250_2_s00[0]);
            }
            else if (groaner->properties_E4.groaner.relKeyframeIdx_100 == 13)
            {
                func_80070400(groaner, &sharedData_800EF624_2_s00, &sharedData_800EF250_2_s00[0]);
            }
            else if (groaner->properties_E4.groaner.relKeyframeIdx_100 == 25)
            {
                func_80070400(groaner, &sharedData_800EF7A0_2_s00, &sharedData_800EF250_2_s00[0]);
            }
            break;

        case 19:
            temp_s0      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 191;
            keyframeIdx0 = !(temp_s0 < 5) + !(temp_s0 < 12);
            keyframeIdx1 = !(temp_s0 < 4) + !(temp_s0 < 11);

            if (temp_s0 == 15)
            {
                keyframeIdx1 -= 2;
            }

            func_80070400(groaner, &sharedData_800EF250_2_s00[keyframeIdx0], &sharedData_800EF250_2_s00[keyframeIdx1]);
            groaner->properties_E4.groaner.relKeyframeIdx_100 = temp_s0;
            break;

        case 34:
            if (groaner->properties_E4.groaner.relKeyframeIdx_100 != 100)
            {
                temp_s0      = groaner->properties_E4.groaner.relKeyframeIdx_100;
                keyframeIdx0 = !(temp_s0 < 5) + !(temp_s0 < 12);
                func_80070400(groaner, &sharedData_800EF250_2_s00[keyframeIdx0], &sharedData_800EF28C_2_s00[0]);
            }
            else
            {
                CopyData(groaner, sharedData_800EF28C_2_s00[0]);
            }
            break;

        case 35:
            temp_s0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 371;

            if (temp_s0 < 12)
            {
                if (temp_s0 < 9)
                {
                    if (temp_s0 < 4)
                    {
                        keyframeIdx0 = temp_s0;
                    }
                    else
                    {
                        keyframeIdx0 = 3;
                    }
                }
                else
                {
                    keyframeIdx0 = 4;
                }
            }
            else if (temp_s0 < 22)
            {
                if (((temp_s0 >> 1) - 1) < 8)
                {
                    keyframeIdx0 = (temp_s0 >> 1) - 1;
                }
                else
                {
                    keyframeIdx0 = 7;
                }
            }
            else
            {
                keyframeIdx0 = temp_s0 - 14 - !(temp_s0 < 24);
            }

            if (temp_s0 < 11)
            {
                if (temp_s0 < 8)
                {
                    if ((temp_s0 + 1) < 4)
                    {
                        keyframeIdx1 = temp_s0 + 1;
                    }
                    else
                    {
                        keyframeIdx1 = 3;
                    }
                }
                else
                {
                    keyframeIdx1 = 4;
                }
            }
            else if (temp_s0 < 21)
            {
                if (((temp_s0 - 1) >> 1) < 8)
                {
                    keyframeIdx1 = (temp_s0 - 1) >> 1;
                }
                else
                {
                    keyframeIdx1 = 7;
                }
            }
            else if (temp_s0 != 25)
            {
                keyframeIdx1 = (temp_s0 - 13) - !(temp_s0 < 23);
            }
            else
            {
                keyframeIdx1 = 0;
            }

            func_80070400(groaner, &sharedData_800EF28C_2_s00[keyframeIdx0], &sharedData_800EF28C_2_s00[keyframeIdx1]);
            break;

        case 4:
            CopyData(groaner, sharedData_800EF368_2_s00[2]);
            break;

        case 5:
            temp_s0      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 16;
            keyframeIdx0 = (temp_s0 - (temp_s0 > 0)) - !(temp_s0 < 10);
            keyframeIdx1 = (temp_s0 - !(temp_s0 < 9)) - !(temp_s0 < 19);
            func_80070400(groaner, &sharedData_800EF368_2_s00[keyframeIdx0], &sharedData_800EF368_2_s00[keyframeIdx1]);

            groaner->properties_E4.groaner.relKeyframeIdx_100 = 5;
            break;

        case 12:
            CopyData(groaner, sharedData_800EF4D0_2_s00[2]);
            break;

        case 13:
            temp_s0      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 111;
            keyframeIdx0 = (temp_s0 - (temp_s0 > 0)) - !(temp_s0 < 11);
            keyframeIdx1 = temp_s0 - !(temp_s0 < 10);
            func_80070400(groaner, &sharedData_800EF4D0_2_s00[keyframeIdx0], &sharedData_800EF4D0_2_s00[keyframeIdx1]);

            groaner->properties_E4.groaner.relKeyframeIdx_100 = 13;
            break;

        case 24:
            CopyData(groaner, sharedData_800EF638_2_s00[3]);
            break;

        case 25:
            temp_s0      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 265;
            keyframeIdx0 = (temp_s0 - !(temp_s0 < 9));
            keyframeIdx1 = (FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 264) - !(temp_s0 < 8);
            func_80070400(groaner, &sharedData_800EF638_2_s00[keyframeIdx0], &sharedData_800EF638_2_s00[keyframeIdx1]);
         
            groaner->properties_E4.groaner.relKeyframeIdx_100 = 0x19;
            break;

        case 6:
            CopyData(groaner, sharedData_800EF7B4_2_s00[0]);
            break;

        case 7:
            temp_s0      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 37;
            keyframeIdx0 = ((FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 39) - !(temp_s0 < 17)) - !(temp_s0 < 38);
            keyframeIdx1 = (((FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 38) - !(temp_s0 < 16)) - !(temp_s0 < 37)) - !(temp_s0 < 39);
            func_80070400(groaner, &sharedData_800EF7B4_2_s00[keyframeIdx0], &sharedData_800EF7B4_2_s00[keyframeIdx1]);
            break;

        case 14:
            CopyData(groaner, sharedData_800EFA84_2_s00[0]);
            break;

        case 15:
            temp_s0      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 0x83;
            keyframeIdx0 = (FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 0x86) - !(temp_s0 < 0x1F);
            keyframeIdx1 = (FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 0x85) - !(temp_s0 < 0x1E);
            func_80070400(groaner, &sharedData_800EFA84_2_s00[keyframeIdx0], &sharedData_800EFA84_2_s00[keyframeIdx1]);
            break;

        case 26:
            CopyData(groaner, sharedData_800EFCDC_2_s00[0]);
            break;

        case 27:
            temp_s0      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 285;
            keyframeIdx0 = (temp_s0 - (temp_s0 > 0)) - !(temp_s0 < 31);
            keyframeIdx1 = (temp_s0 - !(temp_s0 < 30)) - !(temp_s0 < 32);
            func_80070400(groaner, &sharedData_800EFCDC_2_s00[keyframeIdx0], &sharedData_800EFCDC_2_s00[keyframeIdx1]);
            break;

        case 8:
            CopyData(groaner, sharedData_800EFF48_2_s00[0]);
            break;

        case 9:
            temp_s0      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 78;
            keyframeIdx0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 82;

            if (temp_s0 < 9)
            {
                if (temp_s0 <= 0)
                {
                    if (temp_s0 < 6)
                    {
                        keyframeIdx0 = temp_s0 - (temp_s0 > 0);
                    }
                    else
                    {
                        keyframeIdx0 = 5;
                    }
                }
                else
                {
                    if (temp_s0 - 1 < 6)
                    {
                        keyframeIdx0 = temp_s0 - (temp_s0 > 0);
                    }
                    else
                    {
                        keyframeIdx0 = 5;
                    }
                }
            }

            if (temp_s0 != 15)
            {
                if (temp_s0 < 8)
                {
                    if (temp_s0 < 6)
                    {
                        keyframeIdx1 = temp_s0;
                    }
                    else
                    {
                        keyframeIdx1 = 5;
                    }
                }
                else
                {
                    keyframeIdx1 = temp_s0 - 3;
                }
            }
            else
            {
                keyframeIdx1 = 0;
            }

            func_80070400(groaner, &sharedData_800EFF48_2_s00[keyframeIdx0], &sharedData_800EFF48_2_s00[keyframeIdx1]);
            break;

        case 16:
            CopyData(groaner, sharedData_800F0038_2_s00[0]);
            break;

        case 17:
            temp_s0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 165;
            if (temp_s0 < 10)
            {
                if (temp_s0 < 6)
                {
                    keyframeIdx0 = 1;
                    keyframeIdx1 = temp_s0 >> 1;
                    if (keyframeIdx1 < 2)
                    {
                        keyframeIdx0 = keyframeIdx1;
                    }
                }
                else
                {
                    keyframeIdx0 = 4;
                    keyframeIdx1 = temp_s0 - 4;
                    if (keyframeIdx1 < 5)
                    {
                        keyframeIdx0 = keyframeIdx1;
                    }
                }
            }
            else
            {
                if (temp_s0 >= 18)
                {
                    keyframeIdx0 = 8;
                    keyframeIdx1 = (temp_s0 >> 1) - 3;
                    if (keyframeIdx1 < 9)
                    {
                        keyframeIdx0 = keyframeIdx1;
                    }
                }
                else
                {
                    keyframeIdx0 = 5;
                }
            }

            if (temp_s0 < 17)
            {
                if (temp_s0 < 5)
                {
                    if (temp_s0 < 2)
                    {
                        keyframeIdx1 = temp_s0;
                    }
                    else
                    {
                        keyframeIdx1 = 1;
                    }
                }
                else
                {
                    keyframeIdx1 = ANIM_INDEX_FROM_KEYFRAME(temp_s0 - 3, temp_s0, 6, 7);
                }
            }
            else
            {
                if (temp_s0 != 25)
                {
                    if ((((temp_s0 - 1) >> 1) - 2) < 9)
                    {
                        keyframeIdx1 = ((temp_s0 - 1) >> 1) - 2;
                    }
                    else
                    {
                        keyframeIdx1 = 8;
                    }
                }
                else
                {
                    keyframeIdx1 = 0;
                }
            }

            func_80070400(groaner, &sharedData_800F0038_2_s00[keyframeIdx0], &sharedData_800F0038_2_s00[keyframeIdx1]);
            break;

        case 28:
            CopyData(groaner, sharedData_800F00EC_2_s00[0]);
            break;

        case 29:
            temp_s0      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 319;
            keyframeIdx0 = temp_s0 >> 1;

            if (temp_s0 >= 7)
            {
                if (temp_s0 < 16)
                {
                    keyframeIdx0 = ANIM_INDEX_FROM_KEYFRAME(temp_s0 - 3, temp_s0, 9, 9);
                }
                else
                {
                    keyframeIdx0 = temp_s0 - 7 - !(temp_s0 < 20);
                }
            }

            if (temp_s0 < 9)
            {
                keyframeIdx1 = temp_s0 - !(temp_s0 < 2) - !(temp_s0 < 4);
            }
            else
            {
                if (temp_s0 < 15)
                {
                    if (temp_s0 - 5 < 9)
                    {
                        keyframeIdx1 = temp_s0 - 5;
                    }
                    else
                    {
                        keyframeIdx1 = 8;
                    }
                }
                else
                {
                    if (temp_s0 != 26)
                    {
                        keyframeIdx1 = (temp_s0 - 6) - !(temp_s0 < 19);
                    }
                    else
                    {
                        keyframeIdx1 = 0;
                    }
                }
            }

            func_80070400(groaner, &sharedData_800F00EC_2_s00[keyframeIdx0], &sharedData_800F00EC_2_s00[keyframeIdx1]);
            break;

        case 2:
        case 42:
            temp_s0 = groaner->properties_E4.groaner.relKeyframeIdx_100;
            if (temp_s0 < 9)
            {
                keyframeIdx0 = ANIM_INDEX_FROM_KEYFRAME(temp_s0, temp_s0, 6, 0);
            }
            else
            {
                keyframeIdx0 = temp_s0 - 4;
            }

            func_80070400(groaner, &sharedData_800EFF48_2_s00[keyframeIdx0], &sharedData_800F0268_2_s00[0]);
            break;

        case 3:
        case 43:
            keyframeIdx0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT);
            keyframeIdx1 = keyframeIdx0 + 1;
            func_80070400(groaner, &sharedData_800F0268_2_s00[keyframeIdx0], &sharedData_800F0268_2_s00[keyframeIdx1]);
            break;

        case 36:
        case 37:
            CopyData(groaner, sharedData_800F0268_2_s00[15]);
            break;

        case 10:
        case 44:
            temp_s0 = groaner->properties_E4.groaner.relKeyframeIdx_100;
            if (temp_s0 < 10)
            {
                if (temp_s0 < 6)
                {
                    keyframeIdx0 = 1;
                    keyframeIdx1 = temp_s0 >> 1;
                    if (keyframeIdx1 < 2)
                    {
                        keyframeIdx0 = keyframeIdx1;
                    }
                }
                else
                {
                    keyframeIdx0 = 4;
                    keyframeIdx1 = temp_s0 - 4;
                    if (keyframeIdx1 < 5)
                    {
                        keyframeIdx0 = keyframeIdx1;
                    }
                }
            }
            else if (temp_s0 >= 18)
            {
                keyframeIdx0 = 8;
                keyframeIdx1 = (temp_s0 >> 1) - 3;
                if (keyframeIdx1 < 9)
                {
                    keyframeIdx0 = keyframeIdx1;
                }
            }
            else
            {
                keyframeIdx0 = 5;
            }

            func_80070400(groaner, &sharedData_800F0038_2_s00[keyframeIdx0], &sharedData_800F03A8_2_s00[0]);
            break;

        case 11:
        case 45:
            temp_s0      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 94;
            keyframeIdx0 = (temp_s0 - !(temp_s0 < 13)) - !(temp_s0 < 15);
            keyframeIdx1 = (((FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 93) - !(temp_s0 < 12)) - !(temp_s0 < 14)) - !(temp_s0 < 15);
            func_80070400(groaner, &sharedData_800F03A8_2_s00[keyframeIdx0], &sharedData_800F03A8_2_s00[keyframeIdx1]);
            break;

        case 38:
        case 39:
            CopyData(groaner, sharedData_800F03A8_2_s00[13]);
            break;

        case 22:
        case 46:
            temp_s0      = groaner->properties_E4.groaner.relKeyframeIdx_100;
            keyframeIdx0 = temp_s0 >> 1;
            if (temp_s0 >= 7)
            {
                if (temp_s0 < 16)
                {
                    keyframeIdx0 = ANIM_INDEX_FROM_KEYFRAME(temp_s0 - 3, temp_s0, 9, 9);
                }
                else
                {
                    keyframeIdx0 = (temp_s0 - 7) - !(temp_s0 < 20);
                }
            }

            func_80070400(groaner, &sharedData_800F00EC_2_s00[keyframeIdx0], &sharedData_800F04C0_2_s00[0]);
            break;

        case 23:
        case 47:
            temp_s0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 244;
            if (temp_s0 < 12)
            {
                keyframeIdx0 = (temp_s0 - (temp_s0 > 0)) - !(temp_s0 < 9);
            }
            else
            {
                temp = temp_s0 >> 1;
                if (temp_s0 >= 16)
                {
                    keyframeIdx0 = temp + 3;
                }
                else
                {
                    keyframeIdx0 = temp + 4;
                }
            }

            if (temp_s0 < 12)
            {
                keyframeIdx1 = temp_s0 - !(temp_s0 < 8);
            }
            else
            {
                temp = (temp_s0 - 1) >> 1;
                if (temp_s0 >= 15)
                {
                    keyframeIdx1 = temp + 4;
                }
                else
                {
                    keyframeIdx1 = temp + 5;
                }
            }

            func_80070400(groaner, &sharedData_800F04C0_2_s00[keyframeIdx0], &sharedData_800F04C0_2_s00[keyframeIdx1]);
            break;

        case 40:
        case 41:
            CopyData(groaner, sharedData_800F04C0_2_s00[13]);
            break;

        case 32:
            CopyData(groaner, sharedData_800EF1B0_2_s00[0]);
            break;

        case 33:
            keyframeIdx0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 363;
            func_80070400(groaner, &sharedData_800EF1B0_2_s00[keyframeIdx0], &sharedData_800EF1B0_2_s00[(FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 362) & 0x7]);
            break;

        case 30:
            CopyData(groaner, sharedData_800EF0AC_2_s00[0]);
            break;

        case 31:
            temp_s0      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 346;
            keyframeIdx0 = (((temp_s0 - !(temp_s0 < 3)) - !(temp_s0 < 9)) - !(temp_s0 < 12)) - !(temp_s0 < 13);
            keyframeIdx1 = ((((FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 345) - !(temp_s0 < 2)) - !(temp_s0 < 8)) - !(temp_s0 < 11)) - !(temp_s0 < 12);
            func_80070400(groaner, &sharedData_800EF0AC_2_s00[keyframeIdx0], &sharedData_800EF0AC_2_s00[keyframeIdx1]);
            break;

        case 20:
            func_80070400(groaner, &sharedData_800EF19C_2_s00, &sharedData_800EEE54_2_s00[0]);
            break;

        case 21:
            keyframeIdx0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 214;
            keyframeIdx1 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 213;
            func_80070400(groaner, &sharedData_800EEE54_2_s00[keyframeIdx0], &sharedData_800EEE54_2_s00[keyframeIdx1]);

            groaner->field_C8.field_8 = -0xCCC;
            break;
    }

    func_8005C814(&groaner->field_D8, groaner);
}
