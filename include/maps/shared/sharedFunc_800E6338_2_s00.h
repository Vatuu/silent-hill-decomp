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
    s32 keyframeIdx2;
    s32 keyframeIdx1;
    s32 keyframeIdx0;
    s32 temp;

    #define groanerProps  groaner->properties_E4.groaner

    switch (groaner->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(GroanerAnim_9, false):
            if (groanerProps.relKeyframeIdx_100 == 5)
            {
                func_80070400(groaner, &sharedData_800EF4BC_2_s00, &sharedData_800EF250_2_s00[0]);
            }
            else if (groanerProps.relKeyframeIdx_100 == 13)
            {
                func_80070400(groaner, &sharedData_800EF624_2_s00, &sharedData_800EF250_2_s00[0]);
            }
            else if (groanerProps.relKeyframeIdx_100 == 25)
            {
                func_80070400(groaner, &sharedData_800EF7A0_2_s00, &sharedData_800EF250_2_s00[0]);
            }
            break;

        case ANIM_STATUS(GroanerAnim_9, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 191;
            keyframeIdx0 = !(keyframeIdx2 < 5) + !(keyframeIdx2 < 12);
            keyframeIdx1 = !(keyframeIdx2 < 4) + !(keyframeIdx2 < 11);

            if (keyframeIdx2 == 15)
            {
                keyframeIdx1 -= 2;
            }

            func_80070400(groaner, &sharedData_800EF250_2_s00[keyframeIdx0], &sharedData_800EF250_2_s00[keyframeIdx1]);
            groanerProps.relKeyframeIdx_100 = keyframeIdx2;
            break;

        case ANIM_STATUS(GroanerAnim_17, false):
            if (groanerProps.relKeyframeIdx_100 != 100)
            {
                keyframeIdx2      = groanerProps.relKeyframeIdx_100;
                keyframeIdx0 = !(keyframeIdx2 < 5) + !(keyframeIdx2 < 12);
                func_80070400(groaner, &sharedData_800EF250_2_s00[keyframeIdx0], &sharedData_800EF28C_2_s00[0]);
            }
            else
            {
                CopyData(groaner, sharedData_800EF28C_2_s00[0]);
            }
            break;

        case ANIM_STATUS(GroanerAnim_17, true):
            keyframeIdx2 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 371;

            if (keyframeIdx2 < 12)
            {
                if (keyframeIdx2 < 9)
                {
                    if (keyframeIdx2 < 4)
                    {
                        keyframeIdx0 = keyframeIdx2;
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
            else if (keyframeIdx2 < 22)
            {
                if (((keyframeIdx2 >> 1) - 1) < 8)
                {
                    keyframeIdx0 = (keyframeIdx2 >> 1) - 1;
                }
                else
                {
                    keyframeIdx0 = 7;
                }
            }
            else
            {
                keyframeIdx0 = keyframeIdx2 - 14 - !(keyframeIdx2 < 24);
            }

            if (keyframeIdx2 < 11)
            {
                if (keyframeIdx2 < 8)
                {
                    if ((keyframeIdx2 + 1) < 4)
                    {
                        keyframeIdx1 = keyframeIdx2 + 1;
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
            else if (keyframeIdx2 < 21)
            {
                if (((keyframeIdx2 - 1) >> 1) < 8)
                {
                    keyframeIdx1 = (keyframeIdx2 - 1) >> 1;
                }
                else
                {
                    keyframeIdx1 = 7;
                }
            }
            else if (keyframeIdx2 != 25)
            {
                keyframeIdx1 = (keyframeIdx2 - 13) - !(keyframeIdx2 < 23);
            }
            else
            {
                keyframeIdx1 = 0;
            }

            func_80070400(groaner, &sharedData_800EF28C_2_s00[keyframeIdx0], &sharedData_800EF28C_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_2, false):
            CopyData(groaner, sharedData_800EF368_2_s00[2]);
            break;

        case ANIM_STATUS(GroanerAnim_2, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 16;
            keyframeIdx0 = (keyframeIdx2 - (keyframeIdx2 > 0)) - !(keyframeIdx2 < 10);
            keyframeIdx1 = (keyframeIdx2 - !(keyframeIdx2 < 9)) - !(keyframeIdx2 < 19);
            func_80070400(groaner, &sharedData_800EF368_2_s00[keyframeIdx0], &sharedData_800EF368_2_s00[keyframeIdx1]);

            groanerProps.relKeyframeIdx_100 = 5;
            break;

        case ANIM_STATUS(GroanerAnim_6, false):
            CopyData(groaner, sharedData_800EF4D0_2_s00[2]);
            break;

        case ANIM_STATUS(GroanerAnim_6, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 111;
            keyframeIdx0 = (keyframeIdx2 - (keyframeIdx2 > 0)) - !(keyframeIdx2 < 11);
            keyframeIdx1 = keyframeIdx2 - !(keyframeIdx2 < 10);
            func_80070400(groaner, &sharedData_800EF4D0_2_s00[keyframeIdx0], &sharedData_800EF4D0_2_s00[keyframeIdx1]);

            groanerProps.relKeyframeIdx_100 = 13;
            break;

        case ANIM_STATUS(GroanerAnim_12, false):
            CopyData(groaner, sharedData_800EF638_2_s00[3]);
            break;

        case ANIM_STATUS(GroanerAnim_12, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 265;
            keyframeIdx0 = (keyframeIdx2 - !(keyframeIdx2 < 9));
            keyframeIdx1 = (FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 264) - !(keyframeIdx2 < 8);
            func_80070400(groaner, &sharedData_800EF638_2_s00[keyframeIdx0], &sharedData_800EF638_2_s00[keyframeIdx1]);
         
            groanerProps.relKeyframeIdx_100 = 25;
            break;

        case ANIM_STATUS(GroanerAnim_3, false):
            CopyData(groaner, sharedData_800EF7B4_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_3, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 37;
            keyframeIdx0 = ((FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 39) - !(keyframeIdx2 < 17)) - !(keyframeIdx2 < 38);
            keyframeIdx1 = (((FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 38) - !(keyframeIdx2 < 16)) - !(keyframeIdx2 < 37)) - !(keyframeIdx2 < 39);
            func_80070400(groaner, &sharedData_800EF7B4_2_s00[keyframeIdx0], &sharedData_800EF7B4_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_7, false):
            CopyData(groaner, sharedData_800EFA84_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_7, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 131;
            keyframeIdx0 = (FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 134) - !(keyframeIdx2 < 31);
            keyframeIdx1 = (FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 133) - !(keyframeIdx2 < 30);
            func_80070400(groaner, &sharedData_800EFA84_2_s00[keyframeIdx0], &sharedData_800EFA84_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_13, false):
            CopyData(groaner, sharedData_800EFCDC_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_13, true):
            keyframeIdx2 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 285;
            keyframeIdx0 = (keyframeIdx2 - (keyframeIdx2 > 0)) - !(keyframeIdx2 < 31);
            keyframeIdx1 = (keyframeIdx2 - !(keyframeIdx2 < 30)) - !(keyframeIdx2 < 32);
            func_80070400(groaner, &sharedData_800EFCDC_2_s00[keyframeIdx0], &sharedData_800EFCDC_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_4, false):
            CopyData(groaner, sharedData_800EFF48_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_4, true):
            keyframeIdx2 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 78;
            keyframeIdx0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 82;

            if (keyframeIdx2 < 9)
            {
                if (keyframeIdx2 <= 0)
                {
                    if (keyframeIdx2 < 6)
                    {
                        keyframeIdx0 = keyframeIdx2 - (keyframeIdx2 > 0);
                    }
                    else
                    {
                        keyframeIdx0 = 5;
                    }
                }
                else
                {
                    if (keyframeIdx2 - 1 < 6)
                    {
                        keyframeIdx0 = keyframeIdx2 - (keyframeIdx2 > 0);
                    }
                    else
                    {
                        keyframeIdx0 = 5;
                    }
                }
            }

            if (keyframeIdx2 != 15)
            {
                if (keyframeIdx2 < 8)
                {
                    if (keyframeIdx2 < 6)
                    {
                        keyframeIdx1 = keyframeIdx2;
                    }
                    else
                    {
                        keyframeIdx1 = 5;
                    }
                }
                else
                {
                    keyframeIdx1 = keyframeIdx2 - 3;
                }
            }
            else
            {
                keyframeIdx1 = 0;
            }

            func_80070400(groaner, &sharedData_800EFF48_2_s00[keyframeIdx0], &sharedData_800EFF48_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_8, false):
            CopyData(groaner, sharedData_800F0038_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_8, true):
            keyframeIdx2 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 165;
            if (keyframeIdx2 < 10)
            {
                if (keyframeIdx2 < 6)
                {
                    keyframeIdx0 = 1;
                    keyframeIdx1 = keyframeIdx2 >> 1;
                    if (keyframeIdx1 < 2)
                    {
                        keyframeIdx0 = keyframeIdx1;
                    }
                }
                else
                {
                    keyframeIdx0 = 4;
                    keyframeIdx1 = keyframeIdx2 - 4;
                    if (keyframeIdx1 < 5)
                    {
                        keyframeIdx0 = keyframeIdx1;
                    }
                }
            }
            else
            {
                if (keyframeIdx2 >= 18)
                {
                    keyframeIdx0 = 8;
                    keyframeIdx1 = (keyframeIdx2 >> 1) - 3;
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

            if (keyframeIdx2 < 17)
            {
                if (keyframeIdx2 < 5)
                {
                    if (keyframeIdx2 < 2)
                    {
                        keyframeIdx1 = keyframeIdx2;
                    }
                    else
                    {
                        keyframeIdx1 = 1;
                    }
                }
                else
                {
                    keyframeIdx1 = ANIM_INDEX_FROM_KEYFRAME(keyframeIdx2 - 3, keyframeIdx2, 6, 7);
                }
            }
            else
            {
                if (keyframeIdx2 != 25)
                {
                    if ((((keyframeIdx2 - 1) >> 1) - 2) < 9)
                    {
                        keyframeIdx1 = ((keyframeIdx2 - 1) >> 1) - 2;
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

        case ANIM_STATUS(GroanerAnim_14, false):
            CopyData(groaner, sharedData_800F00EC_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_14, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 319;
            keyframeIdx0 = keyframeIdx2 >> 1;

            if (keyframeIdx2 >= 7)
            {
                if (keyframeIdx2 < 16)
                {
                    keyframeIdx0 = ANIM_INDEX_FROM_KEYFRAME(keyframeIdx2 - 3, keyframeIdx2, 9, 9);
                }
                else
                {
                    keyframeIdx0 = (keyframeIdx2 - 7) - !(keyframeIdx2 < 20);
                }
            }

            if (keyframeIdx2 < 9)
            {
                keyframeIdx1 = keyframeIdx2 - !(keyframeIdx2 < 2) - !(keyframeIdx2 < 4);
            }
            else
            {
                if (keyframeIdx2 < 15)
                {
                    if ((keyframeIdx2 - 5) < 9)
                    {
                        keyframeIdx1 = keyframeIdx2 - 5;
                    }
                    else
                    {
                        keyframeIdx1 = 8;
                    }
                }
                else
                {
                    if (keyframeIdx2 != 26)
                    {
                        keyframeIdx1 = (keyframeIdx2 - 6) - !(keyframeIdx2 < 19);
                    }
                    else
                    {
                        keyframeIdx1 = 0;
                    }
                }
            }

            func_80070400(groaner, &sharedData_800F00EC_2_s00[keyframeIdx0], &sharedData_800F00EC_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_1, false):
        case ANIM_STATUS(GroanerAnim_21, false):
            keyframeIdx2 = groanerProps.relKeyframeIdx_100;
            if (keyframeIdx2 < 9)
            {
                keyframeIdx0 = ANIM_INDEX_FROM_KEYFRAME(keyframeIdx2, keyframeIdx2, 6, 0);
            }
            else
            {
                keyframeIdx0 = keyframeIdx2 - 4;
            }

            func_80070400(groaner, &sharedData_800EFF48_2_s00[keyframeIdx0], &sharedData_800F0268_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_1, true):
        case ANIM_STATUS(GroanerAnim_21, true):
            keyframeIdx0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT);
            keyframeIdx1 = keyframeIdx0 + 1;
            func_80070400(groaner, &sharedData_800F0268_2_s00[keyframeIdx0], &sharedData_800F0268_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_18, false):
        case ANIM_STATUS(GroanerAnim_18, true):
            CopyData(groaner, sharedData_800F0268_2_s00[15]);
            break;

        case ANIM_STATUS(GroanerAnim_5, false):
        case ANIM_STATUS(GroanerAnim_22, false):
            keyframeIdx2 = groanerProps.relKeyframeIdx_100;
            if (keyframeIdx2 < 10)
            {
                if (keyframeIdx2 < 6)
                {
                    keyframeIdx0 = 1;
                    keyframeIdx1 = keyframeIdx2 >> 1;
                    if (keyframeIdx1 < 2)
                    {
                        keyframeIdx0 = keyframeIdx1;
                    }
                }
                else
                {
                    keyframeIdx0 = 4;
                    keyframeIdx1 = keyframeIdx2 - 4;
                    if (keyframeIdx1 < 5)
                    {
                        keyframeIdx0 = keyframeIdx1;
                    }
                }
            }
            else if (keyframeIdx2 >= 18)
            {
                keyframeIdx0 = 8;
                keyframeIdx1 = (keyframeIdx2 >> 1) - 3;
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

        case ANIM_STATUS(GroanerAnim_5, true):
        case ANIM_STATUS(GroanerAnim_22, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 94;
            keyframeIdx0 = (keyframeIdx2 - !(keyframeIdx2 < 13)) - !(keyframeIdx2 < 15);
            keyframeIdx1 = (((FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 93) - !(keyframeIdx2 < 12)) - !(keyframeIdx2 < 14)) - !(keyframeIdx2 < 15);
            func_80070400(groaner, &sharedData_800F03A8_2_s00[keyframeIdx0], &sharedData_800F03A8_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_19, false):
        case ANIM_STATUS(GroanerAnim_19, true):
            CopyData(groaner, sharedData_800F03A8_2_s00[13]);
            break;

        case ANIM_STATUS(GroanerAnim_11, false):
        case ANIM_STATUS(GroanerAnim_23, false):
            keyframeIdx2      = groanerProps.relKeyframeIdx_100;
            keyframeIdx0 = keyframeIdx2 >> 1;
            if (keyframeIdx2 >= 7)
            {
                if (keyframeIdx2 < 16)
                {
                    keyframeIdx0 = ANIM_INDEX_FROM_KEYFRAME(keyframeIdx2 - 3, keyframeIdx2, 9, 9);
                }
                else
                {
                    keyframeIdx0 = (keyframeIdx2 - 7) - !(keyframeIdx2 < 20);
                }
            }

            func_80070400(groaner, &sharedData_800F00EC_2_s00[keyframeIdx0], &sharedData_800F04C0_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_11, true):
        case ANIM_STATUS(GroanerAnim_23, true):
            keyframeIdx2 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 244;
            if (keyframeIdx2 < 12)
            {
                keyframeIdx0 = (keyframeIdx2 - (keyframeIdx2 > 0)) - !(keyframeIdx2 < 9);
            }
            else
            {
                temp = keyframeIdx2 >> 1;
                if (keyframeIdx2 >= 16)
                {
                    keyframeIdx0 = temp + 3;
                }
                else
                {
                    keyframeIdx0 = temp + 4;
                }
            }

            if (keyframeIdx2 < 12)
            {
                keyframeIdx1 = keyframeIdx2 - !(keyframeIdx2 < 8);
            }
            else
            {
                temp = (keyframeIdx2 - 1) >> 1;
                if (keyframeIdx2 >= 15)
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

        case ANIM_STATUS(GroanerAnim_20, false):
        case ANIM_STATUS(GroanerAnim_20, true):
            CopyData(groaner, sharedData_800F04C0_2_s00[13]);
            break;

        case ANIM_STATUS(GroanerAnim_16, false):
            CopyData(groaner, sharedData_800EF1B0_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_16, true):
            keyframeIdx0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 363;
            func_80070400(groaner, &sharedData_800EF1B0_2_s00[keyframeIdx0], &sharedData_800EF1B0_2_s00[(FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 362) & 0x7]);
            break;

        case ANIM_STATUS(GroanerAnim_15, false):
            CopyData(groaner, sharedData_800EF0AC_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_15, true):
            keyframeIdx2      = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 346;
            keyframeIdx0 = (((keyframeIdx2 - !(keyframeIdx2 < 3)) - !(keyframeIdx2 < 9)) - !(keyframeIdx2 < 12)) - !(keyframeIdx2 < 13);
            keyframeIdx1 = ((((FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 345) - !(keyframeIdx2 < 2)) - !(keyframeIdx2 < 8)) - !(keyframeIdx2 < 11)) - !(keyframeIdx2 < 12);
            func_80070400(groaner, &sharedData_800EF0AC_2_s00[keyframeIdx0], &sharedData_800EF0AC_2_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(GroanerAnim_10, false):
            func_80070400(groaner, &sharedData_800EF19C_2_s00, &sharedData_800EEE54_2_s00[0]);
            break;

        case ANIM_STATUS(GroanerAnim_10, true):
            keyframeIdx0 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 214;
            keyframeIdx1 = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT) - 213;
            func_80070400(groaner, &sharedData_800EEE54_2_s00[keyframeIdx0], &sharedData_800EEE54_2_s00[keyframeIdx1]);

            groaner->field_C8.field_8 = Q12(-0.8f);
            break;
    }

    func_8005C814(&groaner->field_D8, groaner);

    #undef groanerProps
}
