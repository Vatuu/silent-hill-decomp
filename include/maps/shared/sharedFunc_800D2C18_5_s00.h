// Likely internal to this func, can add to .c instead of .h.
extern s_Keyframe sharedData_800D9500_5_s00[];
extern s_Keyframe sharedData_800D9654_5_s00;
extern s_Keyframe sharedData_800D9668_5_s00;
extern s_Keyframe sharedData_800D967C_5_s00[];
extern s_Keyframe sharedData_800D96F4_5_s00;
extern s_Keyframe sharedData_800D9708_5_s00[];
extern s_Keyframe sharedData_800D97F8_5_s00;
extern s_Keyframe sharedData_800D980C_5_s00;
extern s_Keyframe sharedData_800D9820_5_s00[];
extern s_Keyframe sharedData_800D99D8_5_s00;
extern s_Keyframe sharedData_800D99EC_5_s00;
extern s_Keyframe sharedData_800D9A00_5_s00[];
extern s_Keyframe sharedData_800D9A64_5_s00;
extern s_Keyframe sharedData_800D9A78_5_s00[];
extern s_Keyframe sharedData_800D9AF0_5_s00;
extern s_Keyframe sharedData_800D9B04_5_s00;
extern s_Keyframe sharedData_800D9B18_5_s00;
extern s_Keyframe sharedData_800D9B2C_5_s00[];

#define CopyData(arg0, data)                  \
{                                             \
    s32 __temp;                               \
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
    __temp                 = data.field_A;    \
    arg0->field_D4.field_2 = __temp;          \
}

void sharedFunc_800D2C18_5_s00(s_SubCharacter* scratcher)
{
    s32 relKeyframeIdx;
    s32 keyframeIdx0;
    s32 keyframeIdx1;

    #define animKeyframeIdx FP_FROM(scratcher->model_0.anim_4.time_4, Q12_SHIFT)

    // TODO: Demagic these.
    switch (scratcher->model_0.anim_4.status_0)
    {
        case 8:
            func_80070400(scratcher, &sharedData_800D980C_5_s00, sharedData_800D9500_5_s00);
            break;

        case 9:
            scratcher->properties_E4.hangedScratcher.field_EE = 9;

            relKeyframeIdx = animKeyframeIdx - 98;
            func_80070400(scratcher, &sharedData_800D9500_5_s00[relKeyframeIdx], &sharedData_800D9500_5_s00[relKeyframeIdx + 1]);
            break;

        case 20:
            func_80070400(scratcher, &sharedData_800D980C_5_s00, sharedData_800D9708_5_s00);
            break;

        case 21:
            scratcher->properties_E4.hangedScratcher.field_EE = 21;

            relKeyframeIdx = animKeyframeIdx - 176;
            keyframeIdx0   = relKeyframeIdx - ((relKeyframeIdx >= 12) ? 1 : 0) - ((relKeyframeIdx >= 14) ? 1 : 0);
            keyframeIdx1   = (relKeyframeIdx + 1) - ((relKeyframeIdx >= 11) ? 1 : 0) - ((relKeyframeIdx >= 13) ? 1 : 0) - ((relKeyframeIdx >= 14) ? 1 : 0);

            func_80070400(scratcher, &sharedData_800D9708_5_s00[keyframeIdx0], &sharedData_800D9708_5_s00[keyframeIdx1]);
            break;

        case 24:
            if (scratcher->properties_E4.hangedScratcher.field_EE == 21)
            {
                func_80070400(scratcher, &sharedData_800D97F8_5_s00, &sharedData_800D9668_5_s00);
            }
            else
            {
                CopyData(scratcher, sharedData_800D9668_5_s00);
            }
            break;

        case 43:
            scratcher->properties_E4.hangedScratcher.field_EE = 43;

        case 12:
        case 13:
        case 25:
        case 38:
        case 39:
        case 42:
            CopyData(scratcher, sharedData_800D9668_5_s00);
            break;

        case 16:
            CopyData(scratcher, sharedData_800D967C_5_s00[0]);
            break;

        case 17:
            scratcher->properties_E4.hangedScratcher.field_EE = 17;

            relKeyframeIdx = animKeyframeIdx - 154;

            // TODO: Could these `if`s be flattened?
            if (relKeyframeIdx < 7)
            {
                if (relKeyframeIdx < 3)
                {
                    keyframeIdx0 = (relKeyframeIdx == 2 ? 1 : 0);
                }
                else
                {
                    keyframeIdx0 = 2;
                }
            }
            else
            {
                keyframeIdx0 = animKeyframeIdx - 158;
            }

            if (relKeyframeIdx < 6)
            {
                if (relKeyframeIdx >= 3)
                {
                    keyframeIdx1 = 2;
                }
                else
                {
                    keyframeIdx1 = relKeyframeIdx;
                }
            }
            else
            {
                keyframeIdx1 = (relKeyframeIdx - 3) - ((relKeyframeIdx == 10) ? 1 : 0);
            }

            func_80070400(scratcher, &sharedData_800D967C_5_s00[keyframeIdx0], &sharedData_800D967C_5_s00[keyframeIdx1]);
            break;

        case 28:
            if (scratcher->properties_E4.hangedScratcher.field_EE == 9)
            {
                func_80070400(scratcher, &sharedData_800D9654_5_s00, &sharedData_800D980C_5_s00);
            }
            else if (scratcher->properties_E4.hangedScratcher.field_EE == 17)
            {
                func_80070400(scratcher, &sharedData_800D96F4_5_s00, &sharedData_800D980C_5_s00);
            }
            else
            {
                CopyData(scratcher, sharedData_800D980C_5_s00);
            }
            break;

        case 35:
            scratcher->properties_E4.hangedScratcher.field_EE = 35;

        case 29:
        case 34:
            CopyData(scratcher, sharedData_800D980C_5_s00);
            break;

        case 32:
            func_80070400(scratcher, &sharedData_800D980C_5_s00, sharedData_800D9820_5_s00);
            break;

        case 33:
            scratcher->properties_E4.hangedScratcher.field_EE = 33;

            relKeyframeIdx = animKeyframeIdx - 244;
            func_80070400(scratcher, &sharedData_800D9820_5_s00[relKeyframeIdx], &sharedData_800D9820_5_s00[relKeyframeIdx + 1]);
            break;

        case 26:
            if (scratcher->properties_E4.hangedScratcher.field_EE == 23)
            {
                func_80070400(scratcher, &sharedData_800D9AF0_5_s00, &sharedData_800D99EC_5_s00);
            }
            else
            {
                CopyData(scratcher, sharedData_800D99EC_5_s00);
            }
            break;

        case 45:
            scratcher->properties_E4.hangedScratcher.field_EE = 45;

        case 14:
        case 15:
        case 27:
        case 40:
        case 41:
        case 44:
            CopyData(scratcher, sharedData_800D99EC_5_s00);
            break;

        case 18:
        case 46:
            CopyData(scratcher, sharedData_800D9A00_5_s00[0]);
            break;

        case 19:
        case 47:
            scratcher->properties_E4.hangedScratcher.field_EE = 19;

            relKeyframeIdx = animKeyframeIdx - 166;
            keyframeIdx0   = relKeyframeIdx - ((relKeyframeIdx > 0) ? 1 : 0) - ((relKeyframeIdx >= 4) ? 1 : 0) - ((relKeyframeIdx >= 5) ? 1 : 0);
            keyframeIdx1   = relKeyframeIdx - ((relKeyframeIdx >= 3) ? 1 : 0) - ((relKeyframeIdx >= 4) ? 1 : 0) - ((relKeyframeIdx >= 8) ? 1 : 0);

            func_80070400(scratcher, &sharedData_800D9A00_5_s00[keyframeIdx0], &sharedData_800D9A00_5_s00[keyframeIdx1]);
            break;

        case 22:
            if (scratcher->properties_E4.hangedScratcher.field_EE == 31)
            {
                func_80070400(scratcher, &sharedData_800D9B04_5_s00, sharedData_800D9A78_5_s00);
            }
            else
            {
                func_80070400(scratcher, &sharedData_800D9A64_5_s00, sharedData_800D9A78_5_s00);
            }
            break;

        case 23:
            scratcher->properties_E4.hangedScratcher.field_EE = 23;

            relKeyframeIdx = animKeyframeIdx - 192;
            keyframeIdx0   = relKeyframeIdx - ((relKeyframeIdx >= 2) ? 1 : 0) - ((relKeyframeIdx >= 8) ? 1 : 0);
            keyframeIdx1   = (relKeyframeIdx + 1) - ((relKeyframeIdx > 0) ? 1 : 0) - ((relKeyframeIdx >= 7) ? 1 : 0) - ((relKeyframeIdx >= 8) ? 1 : 0);

            func_80070400(scratcher, &sharedData_800D9A78_5_s00[keyframeIdx0], &sharedData_800D9A78_5_s00[keyframeIdx1]);
            break;

        case 30:
            if (scratcher->properties_E4.hangedScratcher.field_EE == 33)
            {
                func_80070400(scratcher, &sharedData_800D99D8_5_s00, &sharedData_800D9B04_5_s00);
            }
            else if (scratcher->properties_E4.hangedScratcher.field_EE == 19)
            {
                func_80070400(scratcher, &sharedData_800D9A64_5_s00, &sharedData_800D9B04_5_s00);
            }
            else
            {
                CopyData(scratcher, sharedData_800D9B04_5_s00);
            }
            break;

        case 31:
        case 36:
        case 37:
            CopyData(scratcher, sharedData_800D9B04_5_s00);
            break;

        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
            CopyData(scratcher, sharedData_800D9B18_5_s00);
            break;

        case 10:
            CopyData(scratcher, sharedData_800D9B2C_5_s00[0]);
            break;

        case 11:
            relKeyframeIdx = animKeyframeIdx - 116;
            func_80070400(scratcher, &sharedData_800D9B2C_5_s00[relKeyframeIdx], &sharedData_800D9B2C_5_s00[relKeyframeIdx + 1]);
            break;
    }

    func_8005C814(&scratcher->field_D8, scratcher);

    if (!(scratcher->properties_E4.hangedScratcher.flags_E8 & (1 << 9)))
    {
        if (!(scratcher->flags_3E & (1 << 1)) && scratcher->health_B0 > Q12(0.0f) &&
            (scratcher->properties_E4.hangedScratcher.flags_E8 & (1 << 1)) && (scratcher->properties_E4.hangedScratcher.flags_E8 & (1 << 0)))
        {
            scratcher->field_E1_0 = 4;
        }
        else
        {
            scratcher->field_E1_0 = 2;
        }
    }

    #undef animKeyframeIdx
}
