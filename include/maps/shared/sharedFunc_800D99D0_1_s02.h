extern s_func_80070400_1 sharedData_800E0F78_1_s02[];
extern s_func_80070400_1 sharedData_800E0FC8_1_s02;
extern s_func_80070400_1 sharedData_800E0FDC_1_s02;
extern s_func_80070400_1 sharedData_800E0FF0_1_s02;
extern s_func_80070400_1 sharedData_800E1004_1_s02[]; // Creeper keyframe data?
extern s_func_80070400_1 sharedData_800E10CC_1_s02;
extern s_func_80070400_1 sharedData_800E10E0_1_s02[];
extern s_func_80070400_1 sharedData_800E1158_1_s02;
extern s_func_80070400_1 sharedData_800E116C_1_s02;
extern s_func_80070400_1 sharedData_800E1180_1_s02;
extern s_func_80070400_1 sharedData_800E1194_1_s02;
extern s_func_80070400_1 sharedData_800E11A8_1_s02;
extern s_func_80070400_1 sharedData_800E11BC_1_s02;

#define CopyData(arg0, data)                  \
{                                             \
    s32 __temp;                               \
    s32 __temp2;                              \
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
    __temp2                  = data.field_A;  \
    arg0->field_D4.field_2   = __temp2;       \
}

void sharedFunc_800D99D0_1_s02(s_SubCharacter* creaper)
{
    s32 keyframeIdx0;
    s32 keyframeIdx1;
    s32 keyframeIdx2;
    s32 keyframeIdx3;

    switch (creaper->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(CreeperAnim_1, false):
            func_80070400(creaper, &sharedData_800E0FC8_1_s02, &sharedData_800E0F78_1_s02[0]);
            break;

        case ANIM_STATUS(CreeperAnim_1, true):
            creaper->properties_E4.creeper.animStatus_10A          = ANIM_STATUS(CreeperAnim_1, true);
            keyframeIdx0                                           = FP_FROM(creaper->model_0.anim_4.time_4, Q12_SHIFT);
            keyframeIdx1                                           = keyframeIdx0 + 1;
            func_80070400(creaper, &sharedData_800E0F78_1_s02[keyframeIdx0], &sharedData_800E0F78_1_s02[keyframeIdx1]);
            break;

        case ANIM_STATUS(CreeperAnim_2, false):
            func_80070400(creaper, &sharedData_800E11A8_1_s02, &sharedData_800E0FC8_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_2, true):
            CopyData(creaper, sharedData_800E0FC8_1_s02);
            creaper->field_C8.field_8 = -655;
            break;

        case ANIM_STATUS(CreeperAnim_3, false):
            if (creaper->properties_E4.creeper.animStatus_10A == ANIM_STATUS(CreeperAnim_16, true))
            {
                func_80070400(creaper, &sharedData_800E10CC_1_s02, &sharedData_800E0FDC_1_s02);
            }
            else
            {
                func_80070400(creaper, &sharedData_800E116C_1_s02, &sharedData_800E0FDC_1_s02);
            }
            break;

        case ANIM_STATUS(CreeperAnim_3, true):
        case ANIM_STATUS(CreeperAnim_14, false):
        case ANIM_STATUS(CreeperAnim_14, true):
            CopyData(creaper, sharedData_800E0FDC_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_4, false):
            if (creaper->properties_E4.creeper.animStatus_10A == ANIM_STATUS(CreeperAnim_17, true))
            {
                func_80070400(creaper, &sharedData_800E1158_1_s02, &sharedData_800E0FF0_1_s02);
            }
            else
            {
                func_80070400(creaper, &sharedData_800E1180_1_s02, &sharedData_800E0FF0_1_s02);
            }
            break;

        case ANIM_STATUS(CreeperAnim_4, true):
        case ANIM_STATUS(CreeperAnim_15, false):
        case ANIM_STATUS(CreeperAnim_15, true):
            CopyData(creaper, sharedData_800E0FF0_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_7, false):
        case ANIM_STATUS(CreeperAnim_16, false):
            CopyData(creaper, sharedData_800E1004_1_s02[0]);
            break;

        case ANIM_STATUS(CreeperAnim_7, true):
        case ANIM_STATUS(CreeperAnim_16, true):
            keyframeIdx2 = FP_FROM(creaper->model_0.anim_4.time_4, Q12_SHIFT) - 50;
            keyframeIdx3 = keyframeIdx2 - !(keyframeIdx2 < 10) - !(keyframeIdx2 < 11);
            keyframeIdx0 = keyframeIdx3 - !(keyframeIdx2 < 12);
            keyframeIdx1 = (keyframeIdx2 + 1) - !(keyframeIdx2 < 9) - !(keyframeIdx2 < 10) - !(keyframeIdx2 < 11);
            func_80070400(creaper, &sharedData_800E1004_1_s02[keyframeIdx0], &sharedData_800E1004_1_s02[keyframeIdx1]);
            break;

        case ANIM_STATUS(CreeperAnim_8, false):
        case ANIM_STATUS(CreeperAnim_17, false):
            CopyData(creaper, sharedData_800E10E0_1_s02[0]);
            break;

        case ANIM_STATUS(CreeperAnim_8, true):
        case ANIM_STATUS(CreeperAnim_17, true):
            keyframeIdx0 = FP_FROM(creaper->model_0.anim_4.time_4, Q12_SHIFT) - 64;
            keyframeIdx1 = keyframeIdx0 + 1;
            func_80070400(creaper, &sharedData_800E10E0_1_s02[keyframeIdx0], &sharedData_800E10E0_1_s02[keyframeIdx1]);
            break;

        case ANIM_STATUS(CreeperAnim_9, false):
            func_80070400(creaper, &sharedData_800E10CC_1_s02, &sharedData_800E116C_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_9, true):
            CopyData(creaper, sharedData_800E116C_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_10, false):
            func_80070400(creaper, &sharedData_800E1158_1_s02, &sharedData_800E1180_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_10, true):
            CopyData(creaper, sharedData_800E1180_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_11, false):
            func_80070400(creaper, &sharedData_800E11BC_1_s02, &sharedData_800E1194_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_11, true):
            creaper->properties_E4.creeper.animStatus_10A = ANIM_STATUS(CreeperAnim_11, true);
            CopyData(creaper, sharedData_800E1194_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_12, false):
            func_80070400(creaper, &sharedData_800E11BC_1_s02, &sharedData_800E11A8_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_12, true):
            CopyData(creaper, sharedData_800E11A8_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_13, false):
            if (creaper->properties_E4.creeper.animStatus_10A == ANIM_STATUS(CreeperAnim_11, true))
            {
                func_80070400(creaper, &sharedData_800E1194_1_s02, &sharedData_800E11BC_1_s02);
            }
            else if (creaper->properties_E4.creeper.animStatus_10A == ANIM_STATUS(CreeperAnim_1, true))
            {
                func_80070400(creaper, &sharedData_800E0F78_1_s02[0], &sharedData_800E11BC_1_s02);
            }
            else
            {
                CopyData(creaper, sharedData_800E11BC_1_s02);
            }
            break;

        case ANIM_STATUS(CreeperAnim_13, true):
            CopyData(creaper, sharedData_800E11BC_1_s02);
            break;
    }

    func_8005C814(&creaper->field_D8, creaper);
}
