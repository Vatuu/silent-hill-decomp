
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

void sharedFunc_800D70C4_0_s00(s_SubCharacter* chara)
{
    s32 keyframeIdx0;
    s32 keyframeIdx1;
    s32 keyframeIdx2;

    switch (chara->model_0.anim_4.status_0)
    {
        case 0x10:
        case 0x12:
            func_80070400(chara, &sharedData_800DE440_0_s00[15], &sharedData_800DDBA8_0_s00);
            break;

        case 0x11:
        case 0x13:
            CopyData(chara, sharedData_800DDBA8_0_s00);
            break;

        case 0x4C:
            if (chara->properties_E4.larvalStalker.properties_E8[5].val16[0] == NO_VALUE)
            {
                func_80070400(chara, &sharedData_800DE2C4_0_s00, &sharedData_800DDBBC_0_s00[0]);
            }
            else
            {
                func_80070400(chara, &sharedData_800DE580_0_s00[20], &sharedData_800DDBBC_0_s00[0]);
            }
            break;

        case 0x2A:
            func_80070400(chara, &sharedData_800DE2C4_0_s00, &sharedData_800DDBBC_0_s00[0]);
            break;

        case 0x2B:
        case 0x4D:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 353;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 352;
            func_80070400(chara, &sharedData_800DDBBC_0_s00[keyframeIdx0], &sharedData_800DDBBC_0_s00[keyframeIdx1]);
            break;

        case 0x3E:
        case 0x3F:
            CopyData(chara, sharedData_800DDBBC_0_s00[8]);
            break;

        case 0x26:
            func_80070400(chara, &sharedData_800DE2D8_0_s00, &sharedData_800DDC70_0_s00[0]);
            break;

        case 0x4E:
            if (chara->properties_E4.larvalStalker.properties_E8[5].val16[0] == NO_VALUE)
            {
                func_80070400(chara, &sharedData_800DE2D8_0_s00, &sharedData_800DDC70_0_s00[0]);
            }
            else
            {
                func_80070400(chara, &sharedData_800DE8C8_0_s00[chara->properties_E4.larvalStalker.properties_E8[5].val16[0]], &sharedData_800DDC70_0_s00[0]);
            }
            break;

        case 0x27:
        case 0x4F:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 339;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 338;
            func_80070400(chara, &sharedData_800DDC70_0_s00[keyframeIdx0], &sharedData_800DDC70_0_s00[keyframeIdx1]);
            break;

        case 0x40:
        case 0x41:
            CopyData(chara, sharedData_800DDC70_0_s00[0]);
            break;

        case 0x28:
            func_80070400(chara, &sharedData_800DE2EC_0_s00, &sharedData_800DDCFC_0_s00[0]);
            break;

        case 0x50:
            if (chara->properties_E4.larvalStalker.properties_E8[5].val16[0] == NO_VALUE)
            {
                func_80070400(chara, &sharedData_800DE2EC_0_s00, &sharedData_800DDCFC_0_s00[0]);
            }
            else
            {
                func_80070400(chara, &sharedData_800DEB0C_0_s00[chara->properties_E4.larvalStalker.properties_E8[5].val16[0]], &sharedData_800DDCFC_0_s00[0]);
            }
            break;

        case 0x29:
        case 0x51:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 346;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 345;
            func_80070400(chara, &sharedData_800DDCFC_0_s00[keyframeIdx0], &sharedData_800DDCFC_0_s00[keyframeIdx1]);
            break;

        case 0x42:
        case 0x43:
            CopyData(chara, sharedData_800DDCFC_0_s00[6]);
            break;

        case 0x2C:
            CopyData(chara, sharedData_800DDD88_0_s00[0]);
            break;

        case 0x2D:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 362;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 361;
            func_80070400(chara, &sharedData_800DDD88_0_s00[keyframeIdx0], &sharedData_800DDD88_0_s00[keyframeIdx1]);
            break;

        case 0x2E:
        case 0x52:
            CopyData(chara, sharedData_800DDEC8_0_s00[0]);
            break;

        case 0x2F:
        case 0x53:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 378;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 377;
            func_80070400(chara, &sharedData_800DDEC8_0_s00[keyframeIdx0], &sharedData_800DDEC8_0_s00[keyframeIdx1]);
            break;

        case 0x48:
            func_80070400(chara, &sharedData_800DDBA8_0_s00, &sharedData_800DE008_0_s00[6]);
            break;

        case 0x14:
            func_80070400(chara, &sharedData_800DDBA8_0_s00, &sharedData_800DE008_0_s00[0]);
            break;

        case 0x15:
        case 0x49:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 96;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 95;
            func_80070400(chara, &sharedData_800DE008_0_s00[keyframeIdx0], &sharedData_800DE008_0_s00[keyframeIdx1]);
            break;

        case 0x30:
            if (chara->properties_E4.larvalStalker.properties_E8[5].val16[1] != 0)
            {
                func_80070400(chara,
                              &sharedData_800DDD88_0_s00[chara->properties_E4.larvalStalker.properties_E8[5].val16[0]],
                              &sharedData_800DE0E4_0_s00[chara->properties_E4.larvalStalker.properties_E8[5].val16[1]]);
            }
            else
            {
                CopyData(chara, sharedData_800DE0E4_0_s00[0]);
            }
            break;

        case 0x31:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 394;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 393;
            func_80070400(chara, &sharedData_800DE0E4_0_s00[keyframeIdx0], &sharedData_800DE0E4_0_s00[keyframeIdx1]);
            break;

        case 0x32:
            if (chara->properties_E4.larvalStalker.properties_E8[5].val16[1] == 83)
            {
                func_80070400(chara, &sharedData_800DDF2C_0_s00[0], &sharedData_800DE1E8_0_s00[1]);
            }
            else
            {
                keyframeIdx0 = chara->properties_E4.larvalStalker.properties_E8[5].val16[0];
                if (chara->properties_E4.larvalStalker.properties_E8[5].val16[1] == 23)
                {
                    func_80070400(chara, &sharedData_800DE580_0_s00[20 + keyframeIdx0], &sharedData_800DE1E8_0_s00[1]);
                }
                else if (chara->properties_E4.larvalStalker.properties_E8[5].val16[1] == 25)
                {
                    func_80070400(chara, &sharedData_800DE8C8_0_s00[keyframeIdx0], &sharedData_800DE1E8_0_s00[1]);
                }
                else if (chara->properties_E4.larvalStalker.properties_E8[5].val16[1] == 27)
                {
                    func_80070400(chara, &sharedData_800DEB0C_0_s00[keyframeIdx0], &sharedData_800DE1E8_0_s00[1]);
                }
            }
            break;

        case 0x33:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 407;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 406;
            func_80070400(chara, &sharedData_800DE1E8_0_s00[keyframeIdx0], &sharedData_800DE1E8_0_s00[keyframeIdx1]);
            break;

        case 0x34:
        case 0x35:
            CopyData(chara, sharedData_800DE2C4_0_s00);
            break;

        case 0x22:
        case 0x23:
            CopyData(chara, sharedData_800DE2D8_0_s00);
            break;

        case 0x24:
        case 0x25:
            CopyData(chara, sharedData_800DE2EC_0_s00);
            break;

        case 0x36:
            CopyData(chara, sharedData_800DE300_0_s00[0]);
            break;

        case 0x37:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 427;
            if (keyframeIdx0 != 15)
            {
                keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 426;
            }
            else
            {
                keyframeIdx1 = 0;
            }

            func_80070400(chara, &sharedData_800DE300_0_s00[keyframeIdx0], &sharedData_800DE300_0_s00[keyframeIdx1]);
            break;

        case 0x44:
        case 0x46:
            keyframeIdx0 = chara->properties_E4.larvalStalker.properties_E8[5].val16[0];
            keyframeIdx1 = 0;
            func_80070400(chara, &sharedData_800DEF1C_0_s00[keyframeIdx0], &sharedData_800DE440_0_s00[keyframeIdx1]);
            break;

        case 0x45:
        case 0x47:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 461;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 460;
            func_80070400(chara, &sharedData_800DE440_0_s00[keyframeIdx0], &sharedData_800DE440_0_s00[keyframeIdx1]);

            chara->field_C8.field_8 = chara->field_C8.field_6;
            break;

        case 0x16:
            func_80070400(chara, &sharedData_800DE2C4_0_s00, &sharedData_800DE580_0_s00[20]);
            break;

        case 0x17:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 107;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 106;
            func_80070400(chara, &sharedData_800DE580_0_s00[20 + keyframeIdx0], &sharedData_800DE580_0_s00[20 + keyframeIdx1]);
            break;

        case 0x18:
            func_80070400(chara, &sharedData_800DE2D8_0_s00, &sharedData_800DE8C8_0_s00[0]);
            break;

        case 0x19:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 129;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 128;
            func_80070400(chara, &sharedData_800DE8C8_0_s00[keyframeIdx0], &sharedData_800DE8C8_0_s00[keyframeIdx1]);
            break;

        case 0x1A:
            func_80070400(chara, &sharedData_800DE2EC_0_s00, &sharedData_800DEB0C_0_s00[0]);
            break;

        case 0x1B:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 158;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 157;
            func_80070400(chara, &sharedData_800DEB0C_0_s00[keyframeIdx0], &sharedData_800DEB0C_0_s00[keyframeIdx1]);
            break;

        case 0xE:
            keyframeIdx0 = chara->properties_E4.larvalStalker.properties_E8[5].val16[0];
            keyframeIdx1 = chara->properties_E4.larvalStalker.properties_E8[5].val16[1];
            func_80070400(chara, &sharedData_800DEF1C_0_s00[keyframeIdx0], &sharedData_800DE580_0_s00[keyframeIdx1]);
            break;

        case 0xF:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 50;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 49;
            func_80070400(chara, &sharedData_800DE580_0_s00[keyframeIdx0], &sharedData_800DE580_0_s00[keyframeIdx1]);

            chara->field_C8.field_8                                      = Q12(-0.7f);
            chara->properties_E4.larvalStalker.properties_E8[5].val16[0] = 15;
            break;

        case 0x2:
        case 0x54:
            func_80070400(chara,
                          &sharedData_800DE580_0_s00[19 + chara->properties_E4.larvalStalker.properties_E8[5].val16[0]],
                          &sharedData_800DEC74_0_s00[chara->properties_E4.larvalStalker.properties_E8[5].val16[1]]);
            break;

        case 0x3:
        case 0x55:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) + 1;
            func_80070400(chara, &sharedData_800DEC74_0_s00[keyframeIdx0], &sharedData_800DEC74_0_s00[keyframeIdx1]);
            break;

        case 0x6:
        case 0x56:
            func_80070400(chara,
                          &sharedData_800DE580_0_s00[19 + chara->properties_E4.larvalStalker.properties_E8[5].val16[0]],
                          &sharedData_800DECB0_0_s00[chara->properties_E4.larvalStalker.properties_E8[5].val16[1]]);
            break;

        case 0x7:
        case 0x57:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 10;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 9;
            func_80070400(chara, &sharedData_800DECB0_0_s00[keyframeIdx0 + 1], &sharedData_800DECB0_0_s00[keyframeIdx1 + 1]);
            break;

        case 0x4:
        case 0x58:
            keyframeIdx2 = chara->properties_E4.larvalStalker.properties_E8[5].val16[0];
            keyframeIdx2--;
            keyframeIdx1 = 0;
            func_80070400(chara, &sharedData_800DE580_0_s00[20 + keyframeIdx2], &sharedData_800DEDA0_0_s00[keyframeIdx1]);
            break;

        case 0x5:
        case 0x59:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 4;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 3;
            func_80070400(chara, &sharedData_800DEDA0_0_s00[keyframeIdx0], &sharedData_800DEDA0_0_s00[keyframeIdx1]);
            break;

        case 0x8:
            func_80070400(chara,
                          &sharedData_800DE8C8_0_s00[chara->properties_E4.larvalStalker.properties_E8[5].val16[0]],
                          &sharedData_800DEE04_0_s00[chara->properties_E4.larvalStalker.properties_E8[5].val16[1]]);
            break;

        case 0x9:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 20;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 19;
            func_80070400(chara, &sharedData_800DEE04_0_s00[keyframeIdx0], &sharedData_800DEE04_0_s00[keyframeIdx1]);
            break;

        case 0xA:
            if (chara->properties_E4.larvalStalker.properties_E8[5].val16[1] >= 2)
            {
                func_80070400(chara,
                              &sharedData_800DE8C8_0_s00[chara->properties_E4.larvalStalker.properties_E8[5].val16[0]],
                              &sharedData_800DEE40_0_s00[chara->properties_E4.larvalStalker.properties_E8[5].val16[1]]);
            }
            else
            {
                CopyData(chara, sharedData_800DEE68_0_s00[0]);
            }
            break;

        case 0xB:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 25;
            func_80070400(chara, &sharedData_800DEE68_0_s00[keyframeIdx0], &sharedData_800DEE68_0_s00[keyframeIdx0 + 1]);
            break;

        case 0x5B:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 158;
            func_80070400(chara, &sharedData_800DEB0C_0_s00[keyframeIdx0 + 1], &sharedData_800DEB0C_0_s00[keyframeIdx0]);
            break;

        case 0x3C:
            if (chara->properties_E4.larvalStalker.properties_E8[5].val16[0] == 15)
            {
                func_80070400(chara, &sharedData_800DE580_0_s00[19], &sharedData_800DEF1C_0_s00[0]);
            }
            else if (chara->properties_E4.larvalStalker.properties_E8[5].val16[0] == 55)
            {
                func_80070400(chara, &sharedData_800DE300_0_s00[chara->properties_E4.larvalStalker.properties_E8[5].val16[1]], &sharedData_800DEF1C_0_s00[0]);
            }
            break;

        case 0x3D:
        case 0x4B:
            keyframeIdx0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 477;
            if (keyframeIdx0 != 29)
            {
                keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 476;
            }
            else
            {
                keyframeIdx1 = 0;
            }

            func_80070400(chara, &sharedData_800DEF1C_0_s00[keyframeIdx0], &sharedData_800DEF1C_0_s00[keyframeIdx1]);
            break;
    }

    func_8005C814(&chara->field_D8, chara);
}
