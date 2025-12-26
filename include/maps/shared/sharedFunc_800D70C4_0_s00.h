
// TODO: Size of arrays may be incorrect. One big array doesn't match.
extern s_func_80070400_1 sharedData_800DDBA8_0_s00;
extern s_func_80070400_1 sharedData_800DDBBC_0_s00[9];
extern s_func_80070400_1 sharedData_800DDC70_0_s00[7];
extern s_func_80070400_1 sharedData_800DDCFC_0_s00[7];
extern s_func_80070400_1 sharedData_800DDD88_0_s00[16];
extern s_func_80070400_1 sharedData_800DDEC8_0_s00[5];
extern s_func_80070400_1 sharedData_800DDF2C_0_s00[11];
extern s_func_80070400_1 sharedData_800DE008_0_s00[11];
extern s_func_80070400_1 sharedData_800DE0E4_0_s00[13];
extern s_func_80070400_1 sharedData_800DE1E8_0_s00[11];
extern s_func_80070400_1 sharedData_800DE2C4_0_s00;
extern s_func_80070400_1 sharedData_800DE2D8_0_s00;
extern s_func_80070400_1 sharedData_800DE2EC_0_s00;
extern s_func_80070400_1 sharedData_800DE300_0_s00[16];
extern s_func_80070400_1 sharedData_800DE440_0_s00[16];
extern s_func_80070400_1 sharedData_800DE580_0_s00[42];
extern s_func_80070400_1 sharedData_800DE8C8_0_s00[29];
extern s_func_80070400_1 sharedData_800DEB0C_0_s00[18];
extern s_func_80070400_1 sharedData_800DEC74_0_s00[3];
extern s_func_80070400_1 sharedData_800DECB0_0_s00[12];
extern s_func_80070400_1 sharedData_800DEDA0_0_s00[5];
extern s_func_80070400_1 sharedData_800DEE04_0_s00[3];
extern s_func_80070400_1 sharedData_800DEE40_0_s00[2];
extern s_func_80070400_1 sharedData_800DEE68_0_s00[9];
extern s_func_80070400_1 sharedData_800DEF1C_0_s00[30];

#define CopyData(arg0, data)                  \
{                                             \
    s32 __temp;                               \
                                              \
    arg0->field_C8.field_0   = data.field_0;  \
                                              \
    __temp                   = data.field_2;  \
    arg0->field_C8.field_2   = __temp;        \
    arg0->field_C8.field_4   = data.field_4;  \
                                              \
    __temp                   = data.field_6;  \
    arg0->field_C8.field_6   = __temp;        \
    arg0->field_D8.offsetX_4 = data.field_10; \
                                              \
    __temp                   = data.field_12; \
    arg0->field_D8.offsetZ_6 = __temp;        \
    arg0->field_D4.field_0   = data.field_8;  \
    arg0->field_D8.offsetX_0 = data.field_C;  \
                                              \
    __temp                   = data.field_E;  \
    arg0->field_D8.offsetZ_2 = __temp;        \
                                              \
    __temp                   = data.field_A;  \
    arg0->field_D4.field_2   = __temp;        \
}

void sharedFunc_800D70C4_0_s00(s_SubCharacter* stalker)
{
    s32 keyframeIdx0;
    s32 keyframeIdx1;
    s32 keyframeIdx2;

    switch (stalker->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(StalkerAnim_8, false):
        case ANIM_STATUS(StalkerAnim_9, false):
            func_80070400(stalker, &sharedData_800DE440_0_s00[15], &sharedData_800DDBA8_0_s00);
            break;

        case ANIM_STATUS(StalkerAnim_8, true):
        case ANIM_STATUS(StalkerAnim_9, true):
            CopyData(stalker, sharedData_800DDBA8_0_s00);
            break;

        case ANIM_STATUS(StalkerAnim_38, false):
            if (stalker->properties_E4.dummy.properties_E8[5].val16[0] == NO_VALUE)
            {
                func_80070400(stalker, &sharedData_800DE2C4_0_s00, &sharedData_800DDBBC_0_s00[0]);
            }
            else
            {
                func_80070400(stalker, &sharedData_800DE580_0_s00[20], &sharedData_800DDBBC_0_s00[0]);
            }
            break;

        case ANIM_STATUS(StalkerAnim_21, false):
            func_80070400(stalker, &sharedData_800DE2C4_0_s00, &sharedData_800DDBBC_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_21, true):
        case ANIM_STATUS(StalkerAnim_38, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 353;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 352;
            func_80070400(stalker, &sharedData_800DDBBC_0_s00[keyframeIdx0], &sharedData_800DDBBC_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_31, false):
        case ANIM_STATUS(StalkerAnim_31, true):
            CopyData(stalker, sharedData_800DDBBC_0_s00[8]);
            break;

        case ANIM_STATUS(StalkerAnim_19, false):
            func_80070400(stalker, &sharedData_800DE2D8_0_s00, &sharedData_800DDC70_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_39, false):
            if (stalker->properties_E4.dummy.properties_E8[5].val16[0] == NO_VALUE)
            {
                func_80070400(stalker, &sharedData_800DE2D8_0_s00, &sharedData_800DDC70_0_s00[0]);
            }
            else
            {
                func_80070400(stalker, &sharedData_800DE8C8_0_s00[stalker->properties_E4.dummy.properties_E8[5].val16[0]], &sharedData_800DDC70_0_s00[0]);
            }
            break;

        case ANIM_STATUS(StalkerAnim_19, true):
        case ANIM_STATUS(StalkerAnim_39, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 339;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 338;
            func_80070400(stalker, &sharedData_800DDC70_0_s00[keyframeIdx0], &sharedData_800DDC70_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_32, false):
        case ANIM_STATUS(StalkerAnim_32, true):
            CopyData(stalker, sharedData_800DDC70_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_20, false):
            func_80070400(stalker, &sharedData_800DE2EC_0_s00, &sharedData_800DDCFC_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_40, false):
            if (stalker->properties_E4.dummy.properties_E8[5].val16[0] == NO_VALUE)
            {
                func_80070400(stalker, &sharedData_800DE2EC_0_s00, &sharedData_800DDCFC_0_s00[0]);
            }
            else
            {
                func_80070400(stalker, &sharedData_800DEB0C_0_s00[stalker->properties_E4.dummy.properties_E8[5].val16[0]], &sharedData_800DDCFC_0_s00[0]);
            }
            break;

        case ANIM_STATUS(StalkerAnim_20, true):
        case ANIM_STATUS(StalkerAnim_40, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 346;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 345;
            func_80070400(stalker, &sharedData_800DDCFC_0_s00[keyframeIdx0], &sharedData_800DDCFC_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(33, false):
        case ANIM_STATUS(33, true):
            CopyData(stalker, sharedData_800DDCFC_0_s00[6]);
            break;

        case ANIM_STATUS(22, false):
            CopyData(stalker, sharedData_800DDD88_0_s00[0]);
            break;

        case ANIM_STATUS(22, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 362;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 361;
            func_80070400(stalker, &sharedData_800DDD88_0_s00[keyframeIdx0], &sharedData_800DDD88_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(23, false):
        case ANIM_STATUS(41, false):
            CopyData(stalker, sharedData_800DDEC8_0_s00[0]);
            break;

        case ANIM_STATUS(23, true):
        case ANIM_STATUS(41, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 378;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 377;
            func_80070400(stalker, &sharedData_800DDEC8_0_s00[keyframeIdx0], &sharedData_800DDEC8_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(36, false):
            func_80070400(stalker, &sharedData_800DDBA8_0_s00, &sharedData_800DE008_0_s00[6]);
            break;

        case ANIM_STATUS(10, false):
            func_80070400(stalker, &sharedData_800DDBA8_0_s00, &sharedData_800DE008_0_s00[0]);
            break;

        case ANIM_STATUS(10, true):
        case ANIM_STATUS(36, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 96;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 95;
            func_80070400(stalker, &sharedData_800DE008_0_s00[keyframeIdx0], &sharedData_800DE008_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(24, false):
            if (stalker->properties_E4.dummy.properties_E8[5].val16[1] != 0)
            {
                func_80070400(stalker,
                              &sharedData_800DDD88_0_s00[stalker->properties_E4.dummy.properties_E8[5].val16[0]],
                              &sharedData_800DE0E4_0_s00[stalker->properties_E4.dummy.properties_E8[5].val16[1]]);
            }
            else
            {
                CopyData(stalker, sharedData_800DE0E4_0_s00[0]);
            }
            break;

        case ANIM_STATUS(24, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 394;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 393;
            func_80070400(stalker, &sharedData_800DE0E4_0_s00[keyframeIdx0], &sharedData_800DE0E4_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(25, false):
            if (stalker->properties_E4.dummy.properties_E8[5].val16[1] == 83)
            {
                func_80070400(stalker, &sharedData_800DDF2C_0_s00[0], &sharedData_800DE1E8_0_s00[1]);
            }
            else
            {
                keyframeIdx0 = stalker->properties_E4.dummy.properties_E8[5].val16[0];
                if (stalker->properties_E4.dummy.properties_E8[5].val16[1] == 23)
                {
                    func_80070400(stalker, &sharedData_800DE580_0_s00[keyframeIdx0 + 20], &sharedData_800DE1E8_0_s00[1]);
                }
                else if (stalker->properties_E4.dummy.properties_E8[5].val16[1] == 25)
                {
                    func_80070400(stalker, &sharedData_800DE8C8_0_s00[keyframeIdx0], &sharedData_800DE1E8_0_s00[1]);
                }
                else if (stalker->properties_E4.dummy.properties_E8[5].val16[1] == 27)
                {
                    func_80070400(stalker, &sharedData_800DEB0C_0_s00[keyframeIdx0], &sharedData_800DE1E8_0_s00[1]);
                }
            }
            break;

        case ANIM_STATUS(25, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 407;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 406;
            func_80070400(stalker, &sharedData_800DE1E8_0_s00[keyframeIdx0], &sharedData_800DE1E8_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(26, false):
        case ANIM_STATUS(26, true):
            CopyData(stalker, sharedData_800DE2C4_0_s00);
            break;

        case ANIM_STATUS(17, false):
        case ANIM_STATUS(17, true):
            CopyData(stalker, sharedData_800DE2D8_0_s00);
            break;

        case ANIM_STATUS(18, false):
        case ANIM_STATUS(18, true):
            CopyData(stalker, sharedData_800DE2EC_0_s00);
            break;

        case ANIM_STATUS(27, false):
            CopyData(stalker, sharedData_800DE300_0_s00[0]);
            break;

        case ANIM_STATUS(27, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 427;
            if (keyframeIdx0 != 15)
            {
                keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 426;
            }
            else
            {
                keyframeIdx1 = 0;
            }

            func_80070400(stalker, &sharedData_800DE300_0_s00[keyframeIdx0], &sharedData_800DE300_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(34, false):
        case ANIM_STATUS(35, false):
            keyframeIdx0 = stalker->properties_E4.dummy.properties_E8[5].val16[0];
            keyframeIdx1 = 0;
            func_80070400(stalker, &sharedData_800DEF1C_0_s00[keyframeIdx0], &sharedData_800DE440_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(34, true):
        case ANIM_STATUS(35, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 461;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 460;
            func_80070400(stalker, &sharedData_800DE440_0_s00[keyframeIdx0], &sharedData_800DE440_0_s00[keyframeIdx1]);

            stalker->field_C8.field_8 = stalker->field_C8.field_6;
            break;

        case ANIM_STATUS(11, false):
            func_80070400(stalker, &sharedData_800DE2C4_0_s00, &sharedData_800DE580_0_s00[20]);
            break;

        case ANIM_STATUS(11, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 107;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 106;
            func_80070400(stalker, &sharedData_800DE580_0_s00[keyframeIdx0 + 20], &sharedData_800DE580_0_s00[keyframeIdx1 + 20]);
            break;

        case ANIM_STATUS(12, false):
            func_80070400(stalker, &sharedData_800DE2D8_0_s00, &sharedData_800DE8C8_0_s00[0]);
            break;

        case ANIM_STATUS(12, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 129;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 128;
            func_80070400(stalker, &sharedData_800DE8C8_0_s00[keyframeIdx0], &sharedData_800DE8C8_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(13, false):
            func_80070400(stalker, &sharedData_800DE2EC_0_s00, &sharedData_800DEB0C_0_s00[0]);
            break;

        case ANIM_STATUS(13, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 158;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 157;
            func_80070400(stalker, &sharedData_800DEB0C_0_s00[keyframeIdx0], &sharedData_800DEB0C_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(7, false):
            keyframeIdx0 = stalker->properties_E4.dummy.properties_E8[5].val16[0];
            keyframeIdx1 = stalker->properties_E4.dummy.properties_E8[5].val16[1];
            func_80070400(stalker, &sharedData_800DEF1C_0_s00[keyframeIdx0], &sharedData_800DE580_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(7, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 50;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 49;
            func_80070400(stalker, &sharedData_800DE580_0_s00[keyframeIdx0], &sharedData_800DE580_0_s00[keyframeIdx1]);

            stalker->field_C8.field_8                                      = Q12(-0.7f);
            stalker->properties_E4.dummy.properties_E8[5].val16[0] = 15;
            break;

        case ANIM_STATUS(1, false):
        case ANIM_STATUS(42, false):
            func_80070400(stalker,
                          &sharedData_800DE580_0_s00[19 + stalker->properties_E4.dummy.properties_E8[5].val16[0]],
                          &sharedData_800DEC74_0_s00[stalker->properties_E4.dummy.properties_E8[5].val16[1]]);
            break;

        case ANIM_STATUS(1, true):
        case ANIM_STATUS(42, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT);
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) + 1;
            func_80070400(stalker, &sharedData_800DEC74_0_s00[keyframeIdx0], &sharedData_800DEC74_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(3, false):
        case ANIM_STATUS(43, false):
            func_80070400(stalker,
                          &sharedData_800DE580_0_s00[19 + stalker->properties_E4.dummy.properties_E8[5].val16[0]],
                          &sharedData_800DECB0_0_s00[stalker->properties_E4.dummy.properties_E8[5].val16[1]]);
            break;

        case ANIM_STATUS(3, true):
        case ANIM_STATUS(43, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 10;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 9;
            func_80070400(stalker, &sharedData_800DECB0_0_s00[keyframeIdx0 + 1], &sharedData_800DECB0_0_s00[keyframeIdx1 + 1]);
            break;

        case ANIM_STATUS(2, false):
        case ANIM_STATUS(44, false):
            keyframeIdx2 = stalker->properties_E4.dummy.properties_E8[5].val16[0];
            keyframeIdx2--;
            keyframeIdx1 = 0;
            func_80070400(stalker, &sharedData_800DE580_0_s00[keyframeIdx2 + 20], &sharedData_800DEDA0_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(2, true):
        case ANIM_STATUS(44, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 4;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 3;
            func_80070400(stalker, &sharedData_800DEDA0_0_s00[keyframeIdx0], &sharedData_800DEDA0_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(4, false):
            func_80070400(stalker,
                          &sharedData_800DE8C8_0_s00[stalker->properties_E4.dummy.properties_E8[5].val16[0]],
                          &sharedData_800DEE04_0_s00[stalker->properties_E4.dummy.properties_E8[5].val16[1]]);
            break;

        case ANIM_STATUS(4, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 20;
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 19;
            func_80070400(stalker, &sharedData_800DEE04_0_s00[keyframeIdx0], &sharedData_800DEE04_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(5, false):
            if (stalker->properties_E4.dummy.properties_E8[5].val16[1] >= 2)
            {
                func_80070400(stalker,
                              &sharedData_800DE8C8_0_s00[stalker->properties_E4.dummy.properties_E8[5].val16[0]],
                              &sharedData_800DEE40_0_s00[stalker->properties_E4.dummy.properties_E8[5].val16[1]]);
            }
            else
            {
                CopyData(stalker, sharedData_800DEE68_0_s00[0]);
            }
            break;

        case ANIM_STATUS(5, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 25;
            func_80070400(stalker, &sharedData_800DEE68_0_s00[keyframeIdx0], &sharedData_800DEE68_0_s00[keyframeIdx0 + 1]);
            break;

        case ANIM_STATUS(45, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 158;
            func_80070400(stalker, &sharedData_800DEB0C_0_s00[keyframeIdx0 + 1], &sharedData_800DEB0C_0_s00[keyframeIdx0]);
            break;

        case ANIM_STATUS(30, false):
            if (stalker->properties_E4.dummy.properties_E8[5].val16[0] == 15)
            {
                func_80070400(stalker, &sharedData_800DE580_0_s00[19], &sharedData_800DEF1C_0_s00[0]);
            }
            else if (stalker->properties_E4.dummy.properties_E8[5].val16[0] == 55)
            {
                func_80070400(stalker, &sharedData_800DE300_0_s00[stalker->properties_E4.dummy.properties_E8[5].val16[1]], &sharedData_800DEF1C_0_s00[0]);
            }
            break;

        case ANIM_STATUS(30, true):
        case ANIM_STATUS(37, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 477;
            if (keyframeIdx0 != 29)
            {
                keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 476;
            }
            else
            {
                keyframeIdx1 = 0;
            }

            func_80070400(stalker, &sharedData_800DEF1C_0_s00[keyframeIdx0], &sharedData_800DEF1C_0_s00[keyframeIdx1]);
            break;
    }

    func_8005C814(&stalker->field_D8, stalker);
}
