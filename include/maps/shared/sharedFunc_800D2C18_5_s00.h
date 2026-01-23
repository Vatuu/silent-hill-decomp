// Likely internal to this func, can add to .c instead of .h
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

#define CopyData(arg0, data)                      \
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

#define animKeyframeIdx (scratcher->model_0.anim_4.time_4 >> 0xC)

    switch (scratcher->model_0.anim_4.status_0)
    {
        case 0x8:
            func_80070400(scratcher, &sharedData_800D980C_5_s00, sharedData_800D9500_5_s00);
            break;

        case 0x9:
            scratcher->properties_E4.hangedScratcher.field_EE = 9;

            relKeyframeIdx = animKeyframeIdx - 98;
            func_80070400(scratcher, &sharedData_800D9500_5_s00[relKeyframeIdx], &sharedData_800D9500_5_s00[relKeyframeIdx + 1]);
            break;

        case 0x14:
            func_80070400(scratcher, &sharedData_800D980C_5_s00, sharedData_800D9708_5_s00);
            break;

        case 0x15:
            scratcher->properties_E4.hangedScratcher.field_EE = 21;

            relKeyframeIdx = animKeyframeIdx - 176;
            keyframeIdx0   = relKeyframeIdx - (relKeyframeIdx >= 12 ? 1 : 0) - (relKeyframeIdx >= 14 ? 1 : 0);
            keyframeIdx1   = (relKeyframeIdx + 1) - (relKeyframeIdx >= 11 ? 1 : 0) - (relKeyframeIdx >= 13 ? 1 : 0) - (relKeyframeIdx >= 14 ? 1 : 0);

            func_80070400(scratcher, &sharedData_800D9708_5_s00[keyframeIdx0], &sharedData_800D9708_5_s00[keyframeIdx1]);
            break;

        case 0x18:
            if (scratcher->properties_E4.hangedScratcher.field_EE == 21)
            {
                func_80070400(scratcher, &sharedData_800D97F8_5_s00, &sharedData_800D9668_5_s00);
            }
            else
            {
                CopyData(scratcher, sharedData_800D9668_5_s00);
            }
            break;

        case 0x2B:
            scratcher->properties_E4.hangedScratcher.field_EE = 43;

        case 0xC:
        case 0xD:
        case 0x19:
        case 0x26:
        case 0x27:
        case 0x2A:
            CopyData(scratcher, sharedData_800D9668_5_s00);
            break;

        case 0x10:
            CopyData(scratcher, sharedData_800D967C_5_s00[0]);
            break;

        case 0x11:
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
                keyframeIdx1 = (relKeyframeIdx - 3) - (relKeyframeIdx == 10 ? 1 : 0);
            }

            func_80070400(scratcher, &sharedData_800D967C_5_s00[keyframeIdx0], &sharedData_800D967C_5_s00[keyframeIdx1]);
            break;

        case 0x1C:
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

        case 0x23:
            scratcher->properties_E4.hangedScratcher.field_EE = 35;

        case 0x1D:
        case 0x22:
            CopyData(scratcher, sharedData_800D980C_5_s00);
            break;

        case 0x20:
            func_80070400(scratcher, &sharedData_800D980C_5_s00, sharedData_800D9820_5_s00);
            break;

        case 0x21:
            scratcher->properties_E4.hangedScratcher.field_EE = 33;

            relKeyframeIdx = animKeyframeIdx - 244;
            func_80070400(scratcher, &sharedData_800D9820_5_s00[relKeyframeIdx], &sharedData_800D9820_5_s00[relKeyframeIdx + 1]);
            break;

        case 0x1A:
            if (scratcher->properties_E4.hangedScratcher.field_EE == 23)
            {
                func_80070400(scratcher, &sharedData_800D9AF0_5_s00, &sharedData_800D99EC_5_s00);
            }
            else
            {
                CopyData(scratcher, sharedData_800D99EC_5_s00);
            }
            break;

        case 0x2D:
            scratcher->properties_E4.hangedScratcher.field_EE = 45;

        case 0xE:
        case 0xF:
        case 0x1B:
        case 0x28:
        case 0x29:
        case 0x2C:
            CopyData(scratcher, sharedData_800D99EC_5_s00);
            break;

        case 0x12:
        case 0x2E:
            CopyData(scratcher, sharedData_800D9A00_5_s00[0]);
            break;

        case 0x13:
        case 0x2F:
            scratcher->properties_E4.hangedScratcher.field_EE = 19;

            relKeyframeIdx = animKeyframeIdx - 166;
            keyframeIdx0   = relKeyframeIdx - (relKeyframeIdx > 0 ? 1 : 0) - (relKeyframeIdx >= 4 ? 1 : 0) - (relKeyframeIdx >= 5 ? 1 : 0);
            keyframeIdx1   = relKeyframeIdx - (relKeyframeIdx >= 3 ? 1 : 0) - (relKeyframeIdx >= 4 ? 1 : 0) - (relKeyframeIdx >= 8 ? 1 : 0);

            func_80070400(scratcher, &sharedData_800D9A00_5_s00[keyframeIdx0], &sharedData_800D9A00_5_s00[keyframeIdx1]);
            break;

        case 0x16:
            if (scratcher->properties_E4.hangedScratcher.field_EE == 31)
            {
                func_80070400(scratcher, &sharedData_800D9B04_5_s00, sharedData_800D9A78_5_s00);
            }
            else
            {
                func_80070400(scratcher, &sharedData_800D9A64_5_s00, sharedData_800D9A78_5_s00);
            }
            break;

        case 0x17:
            scratcher->properties_E4.hangedScratcher.field_EE = 23;

            relKeyframeIdx = animKeyframeIdx - 192;
            keyframeIdx0   = relKeyframeIdx - (relKeyframeIdx >= 2 ? 1 : 0) - (relKeyframeIdx >= 8 ? 1 : 0);
            keyframeIdx1   = (relKeyframeIdx + 1) - (relKeyframeIdx > 0 ? 1 : 0) - (relKeyframeIdx >= 7 ? 1 : 0) - (relKeyframeIdx >= 8 ? 1 : 0);

            func_80070400(scratcher, &sharedData_800D9A78_5_s00[keyframeIdx0], &sharedData_800D9A78_5_s00[keyframeIdx1]);
            break;

        case 0x1E:
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

        case 0x1F:
        case 0x24:
        case 0x25:
            CopyData(scratcher, sharedData_800D9B04_5_s00);
            break;

        case 0x2:
        case 0x3:
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
            CopyData(scratcher, sharedData_800D9B18_5_s00);
            break;

        case 0xA:
            CopyData(scratcher, sharedData_800D9B2C_5_s00[0]);
            break;

        case 0xB:
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
