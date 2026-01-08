extern s_Keyframe sharedData_800ECC44_2_s02;
extern s_Keyframe sharedData_800ECC58_2_s02[];
extern s_Keyframe sharedData_800ECCBC_2_s02;
extern s_Keyframe sharedData_800ECCD0_2_s02[];
extern s_Keyframe sharedData_800ECD34_2_s02;
extern s_Keyframe sharedData_800ECD48_2_s02[];
extern s_Keyframe sharedData_800ECE24_2_s02[];
extern s_Keyframe sharedData_800ECF00_2_s02[];
extern s_Keyframe sharedData_800ECF64_2_s02[];
extern s_Keyframe sharedData_800ED018_2_s02[];
extern s_Keyframe sharedData_800ED1D0_2_s02[];
extern s_Keyframe sharedData_800ED2C0_2_s02;

#define CopyData(arg0, data)                      \
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

void sharedFunc_800E8DFC_2_s02(s_SubCharacter* romper)
{
    s32 sp10[2];
    s32 var_a1;
    s32 i;

    switch (romper->model_0.anim_4.status_0)
    {
        case 5:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 2; i < 2; i++, var_a1++)
            {
                sp10[i] = var_a1 - !(var_a1 < 5);
            }
            func_80070400(romper, &sharedData_800ECC58_2_s02[sp10[0]], &sharedData_800ECC58_2_s02[sp10[1]]);
            break;

        case 6:
        case 7:
        case 10:
        case 11:
            CopyData(romper, sharedData_800ECCBC_2_s02);
            break;

        case 9:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0xF; i < 2; i++, var_a1++)
            {
                sp10[i] = var_a1;
            }
            func_80070400(romper, &sharedData_800ECCD0_2_s02[sp10[0]], &sharedData_800ECCD0_2_s02[sp10[1]]);
            break;

        case 15:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0x27; i < 2; i++, var_a1++)
            {
                sp10[i] = var_a1;
            }
            func_80070400(romper, &sharedData_800ECD48_2_s02[sp10[0]], &sharedData_800ECD48_2_s02[sp10[1]]);
            break;

        case 17:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0x32; i < 2; i++, var_a1++)
            {
                sp10[i] = var_a1;
            }
            func_80070400(romper, &sharedData_800ECE24_2_s02[sp10[0]], &sharedData_800ECE24_2_s02[sp10[1]]);
            break;

        case 12:
        case 13:
        case 20:
        case 21:
        case 32:
        case 33:
            CopyData(romper, sharedData_800ECF00_2_s02[4]);
            break;

        case 22:
            CopyData(romper, sharedData_800ECF00_2_s02[0]);
            break;

        case 23:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0x5D; i < 2; i++, var_a1++)
            {
                sp10[i] = var_a1 >= 4 ? 4 : var_a1;
            }
            func_80070400(romper, &sharedData_800ECF00_2_s02[sp10[0]], &sharedData_800ECF00_2_s02[sp10[1]]);
            break;

        case 25:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0x64; i < 2;
                 i++, var_a1   = (var_a1 + 1) % 9)
            {
                sp10[i] = var_a1;
            }
            func_80070400(romper, &sharedData_800ECF64_2_s02[sp10[0]], &sharedData_800ECF64_2_s02[sp10[1]]);
            break;

        case 27:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0x6D; i < 2;
                 i++, var_a1   = (var_a1 + 1) % 22)
            {
                sp10[i] = var_a1;
            }
            func_80070400(romper, &sharedData_800ED018_2_s02[sp10[0]], &sharedData_800ED018_2_s02[sp10[1]]);
            break;

        case 29:
            CopyData(romper, sharedData_800ED2C0_2_s02);
            break;

        case 31:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0x93; i < 2;
                 i++, var_a1   = (var_a1 + 1) % 16)
            {
                sp10[i] = var_a1 - (var_a1 > 0) - !(var_a1 < 4) - !(var_a1 < 8) - !(var_a1 < 0xC);
            }
            func_80070400(romper, &sharedData_800ED1D0_2_s02[sp10[0]], &sharedData_800ED1D0_2_s02[sp10[1]]);
            break;

        case 19:
            CopyData(romper, sharedData_800ECD34_2_s02);
            romper->field_D4.radius_0 = (romper->model_0.anim_4.time_4 - 0x3D000) / 100;
            break;

        default:
            CopyData(romper, sharedData_800ECC44_2_s02);
            break;
    }

    func_8005C814(&romper->field_D8, romper);

    if ((romper->model_0.anim_4.status_0 >> 1) != 2)
    {
        romper->field_44.field_0 = 0;
    }
}