
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
extern s_func_80070400_1 sharedData_800DE580_0_s00[42]; // Stalker anim data?
extern s_func_80070400_1 sharedData_800DE8C8_0_s00[29];
extern s_func_80070400_1 sharedData_800DEB0C_0_s00[18]; // Stalker anim data? Index is keyframe index.
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
            if (stalker->properties_E4.stalker.keyframeIdx_FC == NO_VALUE)
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
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 353);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 352);
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
            if (stalker->properties_E4.stalker.keyframeIdx_FC == NO_VALUE)
            {
                func_80070400(stalker, &sharedData_800DE2D8_0_s00, &sharedData_800DDC70_0_s00[0]);
            }
            else
            {
                func_80070400(stalker, &sharedData_800DE8C8_0_s00[stalker->properties_E4.stalker.keyframeIdx_FC], &sharedData_800DDC70_0_s00[0]);
            }
            break;

        case ANIM_STATUS(StalkerAnim_19, true):
        case ANIM_STATUS(StalkerAnim_39, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 339);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 338);
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
            if (stalker->properties_E4.stalker.keyframeIdx_FC == NO_VALUE)
            {
                func_80070400(stalker, &sharedData_800DE2EC_0_s00, &sharedData_800DDCFC_0_s00[0]);
            }
            else
            {
                func_80070400(stalker, &sharedData_800DEB0C_0_s00[stalker->properties_E4.stalker.keyframeIdx_FC], &sharedData_800DDCFC_0_s00[0]);
            }
            break;

        case ANIM_STATUS(StalkerAnim_20, true):
        case ANIM_STATUS(StalkerAnim_40, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 346);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 345);
            func_80070400(stalker, &sharedData_800DDCFC_0_s00[keyframeIdx0], &sharedData_800DDCFC_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_33, false):
        case ANIM_STATUS(StalkerAnim_33, true):
            CopyData(stalker, sharedData_800DDCFC_0_s00[6]);
            break;

        case ANIM_STATUS(StalkerAnim_22, false):
            CopyData(stalker, sharedData_800DDD88_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_22, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 362);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 361);
            func_80070400(stalker, &sharedData_800DDD88_0_s00[keyframeIdx0], &sharedData_800DDD88_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_23, false):
        case ANIM_STATUS(StalkerAnim_41, false):
            CopyData(stalker, sharedData_800DDEC8_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_23, true):
        case ANIM_STATUS(StalkerAnim_41, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 378);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 377);
            func_80070400(stalker, &sharedData_800DDEC8_0_s00[keyframeIdx0], &sharedData_800DDEC8_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_36, false):
            func_80070400(stalker, &sharedData_800DDBA8_0_s00, &sharedData_800DE008_0_s00[6]);
            break;

        case ANIM_STATUS(StalkerAnim_10, false):
            func_80070400(stalker, &sharedData_800DDBA8_0_s00, &sharedData_800DE008_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_10, true):
        case ANIM_STATUS(StalkerAnim_36, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 96);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 95);
            func_80070400(stalker, &sharedData_800DE008_0_s00[keyframeIdx0], &sharedData_800DE008_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_24, false):
            if (stalker->properties_E4.stalker.relKeyframeIdx_FE != 0)
            {
                func_80070400(stalker,
                              &sharedData_800DDD88_0_s00[stalker->properties_E4.stalker.keyframeIdx_FC],
                              &sharedData_800DE0E4_0_s00[stalker->properties_E4.stalker.relKeyframeIdx_FE]);
            }
            else
            {
                CopyData(stalker, sharedData_800DE0E4_0_s00[0]);
            }
            break;

        case ANIM_STATUS(StalkerAnim_24, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 394);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 393);
            func_80070400(stalker, &sharedData_800DE0E4_0_s00[keyframeIdx0], &sharedData_800DE0E4_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_25, false):
            if (stalker->properties_E4.stalker.relKeyframeIdx_FE == 83)
            {
                func_80070400(stalker, &sharedData_800DDF2C_0_s00[0], &sharedData_800DE1E8_0_s00[1]);
            }
            else
            {
                keyframeIdx0 = stalker->properties_E4.stalker.keyframeIdx_FC;
                if (stalker->properties_E4.stalker.relKeyframeIdx_FE == 23)
                {
                    func_80070400(stalker, &sharedData_800DE580_0_s00[keyframeIdx0 + 20], &sharedData_800DE1E8_0_s00[1]);
                }
                else if (stalker->properties_E4.stalker.relKeyframeIdx_FE == 25)
                {
                    func_80070400(stalker, &sharedData_800DE8C8_0_s00[keyframeIdx0], &sharedData_800DE1E8_0_s00[1]);
                }
                else if (stalker->properties_E4.stalker.relKeyframeIdx_FE == 27)
                {
                    func_80070400(stalker, &sharedData_800DEB0C_0_s00[keyframeIdx0], &sharedData_800DE1E8_0_s00[1]);
                }
            }
            break;

        case ANIM_STATUS(StalkerAnim_25, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 407);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 406);
            func_80070400(stalker, &sharedData_800DE1E8_0_s00[keyframeIdx0], &sharedData_800DE1E8_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_26, false):
        case ANIM_STATUS(StalkerAnim_26, true):
            CopyData(stalker, sharedData_800DE2C4_0_s00);
            break;

        case ANIM_STATUS(StalkerAnim_17, false):
        case ANIM_STATUS(StalkerAnim_17, true):
            CopyData(stalker, sharedData_800DE2D8_0_s00);
            break;

        case ANIM_STATUS(StalkerAnim_18, false):
        case ANIM_STATUS(StalkerAnim_18, true):
            CopyData(stalker, sharedData_800DE2EC_0_s00);
            break;

        case ANIM_STATUS(StalkerAnim_27, false):
            CopyData(stalker, sharedData_800DE300_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_27, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 427);
            if (keyframeIdx0 != 15)
            {
                keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 426);
            }
            else
            {
                keyframeIdx1 = 0;
            }

            func_80070400(stalker, &sharedData_800DE300_0_s00[keyframeIdx0], &sharedData_800DE300_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_34, false):
        case ANIM_STATUS(StalkerAnim_35, false):
            keyframeIdx0 = stalker->properties_E4.stalker.keyframeIdx_FC;
            keyframeIdx1 = 0;
            func_80070400(stalker, &sharedData_800DEF1C_0_s00[keyframeIdx0], &sharedData_800DE440_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_34, true):
        case ANIM_STATUS(StalkerAnim_35, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 461);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 460);
            func_80070400(stalker, &sharedData_800DE440_0_s00[keyframeIdx0], &sharedData_800DE440_0_s00[keyframeIdx1]);

            stalker->field_C8.field_8 = stalker->field_C8.field_6;
            break;

        case ANIM_STATUS(StalkerAnim_11, false):
            func_80070400(stalker, &sharedData_800DE2C4_0_s00, &sharedData_800DE580_0_s00[20]);
            break;

        case ANIM_STATUS(StalkerAnim_11, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 107);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 106);
            func_80070400(stalker, &sharedData_800DE580_0_s00[keyframeIdx0 + 20], &sharedData_800DE580_0_s00[keyframeIdx1 + 20]);
            break;

        case ANIM_STATUS(StalkerAnim_12, false):
            func_80070400(stalker, &sharedData_800DE2D8_0_s00, &sharedData_800DE8C8_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_12, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 129);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 128);
            func_80070400(stalker, &sharedData_800DE8C8_0_s00[keyframeIdx0], &sharedData_800DE8C8_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_13, false):
            func_80070400(stalker, &sharedData_800DE2EC_0_s00, &sharedData_800DEB0C_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_13, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 158);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 157);
            func_80070400(stalker, &sharedData_800DEB0C_0_s00[keyframeIdx0], &sharedData_800DEB0C_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_7, false):
            keyframeIdx0 = stalker->properties_E4.stalker.keyframeIdx_FC;
            keyframeIdx1 = stalker->properties_E4.stalker.relKeyframeIdx_FE;
            func_80070400(stalker, &sharedData_800DEF1C_0_s00[keyframeIdx0], &sharedData_800DE580_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_7, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 50);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 49);
            func_80070400(stalker, &sharedData_800DE580_0_s00[keyframeIdx0], &sharedData_800DE580_0_s00[keyframeIdx1]);

            stalker->field_C8.field_8                                      = Q12(-0.7f);
            stalker->properties_E4.stalker.keyframeIdx_FC = 15;
            break;

        case ANIM_STATUS(StalkerAnim_1, false):
        case ANIM_STATUS(StalkerAnim_42, false):
            func_80070400(stalker,
                          &sharedData_800DE580_0_s00[19 + stalker->properties_E4.stalker.keyframeIdx_FC],
                          &sharedData_800DEC74_0_s00[stalker->properties_E4.stalker.relKeyframeIdx_FE]);
            break;

        case ANIM_STATUS(StalkerAnim_1, true):
        case ANIM_STATUS(StalkerAnim_42, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT);
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) + 1;
            func_80070400(stalker, &sharedData_800DEC74_0_s00[keyframeIdx0], &sharedData_800DEC74_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_3, false):
        case ANIM_STATUS(StalkerAnim_43, false):
            func_80070400(stalker,
                          &sharedData_800DE580_0_s00[19 + stalker->properties_E4.stalker.keyframeIdx_FC],
                          &sharedData_800DECB0_0_s00[stalker->properties_E4.stalker.relKeyframeIdx_FE]);
            break;

        case ANIM_STATUS(StalkerAnim_3, true):
        case ANIM_STATUS(StalkerAnim_43, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 10);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 9);
            func_80070400(stalker, &sharedData_800DECB0_0_s00[keyframeIdx0 + 1], &sharedData_800DECB0_0_s00[keyframeIdx1 + 1]);
            break;

        case ANIM_STATUS(StalkerAnim_2, false):
        case ANIM_STATUS(StalkerAnim_44, false):
            keyframeIdx2 = stalker->properties_E4.stalker.keyframeIdx_FC;
            keyframeIdx2--;
            keyframeIdx1 = 0;
            func_80070400(stalker, &sharedData_800DE580_0_s00[keyframeIdx2 + 20], &sharedData_800DEDA0_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_2, true):
        case ANIM_STATUS(StalkerAnim_44, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 4);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 3);
            func_80070400(stalker, &sharedData_800DEDA0_0_s00[keyframeIdx0], &sharedData_800DEDA0_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_4, false):
            func_80070400(stalker,
                          &sharedData_800DE8C8_0_s00[stalker->properties_E4.stalker.keyframeIdx_FC],
                          &sharedData_800DEE04_0_s00[stalker->properties_E4.stalker.relKeyframeIdx_FE]);
            break;

        case ANIM_STATUS(StalkerAnim_4, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 20);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 19);
            func_80070400(stalker, &sharedData_800DEE04_0_s00[keyframeIdx0], &sharedData_800DEE04_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_5, false):
            if (stalker->properties_E4.stalker.relKeyframeIdx_FE >= 2)
            {
                func_80070400(stalker,
                              &sharedData_800DE8C8_0_s00[stalker->properties_E4.stalker.keyframeIdx_FC],
                              &sharedData_800DEE40_0_s00[stalker->properties_E4.stalker.relKeyframeIdx_FE]);
            }
            else
            {
                CopyData(stalker, sharedData_800DEE68_0_s00[0]);
            }
            break;

        case ANIM_STATUS(StalkerAnim_5, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 25);
            func_80070400(stalker, &sharedData_800DEE68_0_s00[keyframeIdx0], &sharedData_800DEE68_0_s00[keyframeIdx0 + 1]);
            break;

        case ANIM_STATUS(StalkerAnim_45, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 158);
            func_80070400(stalker, &sharedData_800DEB0C_0_s00[keyframeIdx0 + 1], &sharedData_800DEB0C_0_s00[keyframeIdx0]);
            break;

        case ANIM_STATUS(StalkerAnim_30, false):
            if (stalker->properties_E4.stalker.keyframeIdx_FC == 15)
            {
                func_80070400(stalker, &sharedData_800DE580_0_s00[19], &sharedData_800DEF1C_0_s00[0]);
            }
            else if (stalker->properties_E4.stalker.keyframeIdx_FC == 55)
            {
                func_80070400(stalker, &sharedData_800DE300_0_s00[stalker->properties_E4.stalker.relKeyframeIdx_FE], &sharedData_800DEF1C_0_s00[0]);
            }
            break;

        case ANIM_STATUS(StalkerAnim_30, true):
        case ANIM_STATUS(StalkerAnim_37, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 477);
            if (keyframeIdx0 != 29)
            {
                keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 476);
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
