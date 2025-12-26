extern s_func_80070400_1 sharedData_800E0F78_1_s02[];
extern s_func_80070400_1 sharedData_800E0FC8_1_s02;
extern s_func_80070400_1 sharedData_800E0FDC_1_s02;
extern s_func_80070400_1 sharedData_800E0FF0_1_s02;
extern s_func_80070400_1 sharedData_800E1004_1_s02[];
extern s_func_80070400_1 sharedData_800E10CC_1_s02;
extern s_func_80070400_1 sharedData_800E10E0_1_s02[];
extern s_func_80070400_1 sharedData_800E1158_1_s02;
extern s_func_80070400_1 sharedData_800E116C_1_s02;
extern s_func_80070400_1 sharedData_800E1180_1_s02;
extern s_func_80070400_1 sharedData_800E1194_1_s02;
extern s_func_80070400_1 sharedData_800E11A8_1_s02;
extern s_func_80070400_1 sharedData_800E11BC_1_s02;

#define copyData(arg0, data)                      \
    {                                             \
        s32 __temp, __temp2;                      \
        arg0->field_C8.field_0   = data.field_0;  \
        __temp                   = data.field_2;  \
        arg0->field_C8.field_2   = __temp;        \
        arg0->field_C8.field_4   = data.field_4;  \
        __temp                   = data.field_6;  \
        arg0->field_C8.field_6   = __temp;        \
        arg0->field_D8.offsetX_4 = data.field_10; \
        __temp                   = data.field_12; \
        arg0->field_D8.offsetZ_6 = __temp;        \
        arg0->field_D4.field_0   = data.field_8;  \
        arg0->field_D8.offsetX_0 = data.field_C;  \
        __temp                   = data.field_E;  \
        arg0->field_D8.offsetZ_2 = __temp;        \
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
        case 2:
            func_80070400(creaper, &sharedData_800E0FC8_1_s02, &sharedData_800E0F78_1_s02[0]);
            break;

        case 3:
            creaper->properties_E4.dummy.properties_E8[8].val16[1] = 3;
            keyframeIdx0                                           = FP_FROM(creaper->model_0.anim_4.time_4, Q12_SHIFT);
            keyframeIdx1                                           = keyframeIdx0 + 1;
            func_80070400(creaper, &sharedData_800E0F78_1_s02[keyframeIdx0], &sharedData_800E0F78_1_s02[keyframeIdx1]);
            break;

        case 4:
            func_80070400(creaper, &sharedData_800E11A8_1_s02, &sharedData_800E0FC8_1_s02);
            break;

        case 5:
            copyData(creaper, sharedData_800E0FC8_1_s02);
            creaper->field_C8.field_8 = -0x28F;
            break;

        case 6:
            if (creaper->properties_E4.dummy.properties_E8[8].val16[1] == 0x21)
            {
                func_80070400(creaper, &sharedData_800E10CC_1_s02, &sharedData_800E0FDC_1_s02);
            }
            else
            {
                func_80070400(creaper, &sharedData_800E116C_1_s02, &sharedData_800E0FDC_1_s02);
            }
            break;

        case 7:
        case 28:
        case 29:
            copyData(creaper, sharedData_800E0FDC_1_s02);
            break;

        case 8:
            if (creaper->properties_E4.dummy.properties_E8[8].val16[1] == 0x23)
            {
                func_80070400(creaper, &sharedData_800E1158_1_s02, &sharedData_800E0FF0_1_s02);
            }
            else
            {
                func_80070400(creaper, &sharedData_800E1180_1_s02, &sharedData_800E0FF0_1_s02);
            }
            break;

        case 9:
        case 30:
        case 31:
            copyData(creaper, sharedData_800E0FF0_1_s02);
            break;

        case 14:
        case 32:
            copyData(creaper, sharedData_800E1004_1_s02[0]);
            break;

        case 15:
        case 33:
            keyframeIdx2 = FP_FROM(creaper->model_0.anim_4.time_4, Q12_SHIFT) - 0x32;
            keyframeIdx3 = keyframeIdx2 - !(keyframeIdx2 < 0xA) - !(keyframeIdx2 < 0xB);
            keyframeIdx0 = keyframeIdx3 - !(keyframeIdx2 < 0xC);
            keyframeIdx1 = (keyframeIdx2 + 1) - !(keyframeIdx2 < 9) - !(keyframeIdx2 < 0xA) - !(keyframeIdx2 < 0xB);
            func_80070400(creaper, &sharedData_800E1004_1_s02[keyframeIdx0], &sharedData_800E1004_1_s02[keyframeIdx1]);
            break;

        case 16:
        case 34:
            copyData(creaper, sharedData_800E10E0_1_s02[0]);
            break;

        case 17:
        case 35:
            keyframeIdx0 = FP_FROM(creaper->model_0.anim_4.time_4, Q12_SHIFT) - 0x40;
            keyframeIdx1 = keyframeIdx0 + 1;
            func_80070400(creaper, &sharedData_800E10E0_1_s02[keyframeIdx0], &sharedData_800E10E0_1_s02[keyframeIdx1]);
            break;

        case 18:
            func_80070400(creaper, &sharedData_800E10CC_1_s02, &sharedData_800E116C_1_s02);
            break;

        case 19:
            copyData(creaper, sharedData_800E116C_1_s02);
            break;

        case 20:
            func_80070400(creaper, &sharedData_800E1158_1_s02, &sharedData_800E1180_1_s02);
            break;

        case 21:
            copyData(creaper, sharedData_800E1180_1_s02);
            break;

        case 22:
            func_80070400(creaper, &sharedData_800E11BC_1_s02, &sharedData_800E1194_1_s02);
            break;

        case 23:
            creaper->properties_E4.dummy.properties_E8[8].val16[1] = 0x17;
            copyData(creaper, sharedData_800E1194_1_s02);
            break;

        case 24:
            func_80070400(creaper, &sharedData_800E11BC_1_s02, &sharedData_800E11A8_1_s02);
            break;

        case 25:
            copyData(creaper, sharedData_800E11A8_1_s02);
            break;

        case 26:
            if (creaper->properties_E4.dummy.properties_E8[8].val16[1] == 0x17)
            {
                func_80070400(creaper, &sharedData_800E1194_1_s02, &sharedData_800E11BC_1_s02);
            }
            else if (creaper->properties_E4.dummy.properties_E8[8].val16[1] == 3)
            {
                func_80070400(creaper, &sharedData_800E0F78_1_s02[0], &sharedData_800E11BC_1_s02);
            }
            else
            {
                copyData(creaper, sharedData_800E11BC_1_s02);
            }
            break;

        case 27:
            copyData(creaper, sharedData_800E11BC_1_s02);
            break;
    }

    func_8005C814(&creaper->field_D8, creaper);
}
