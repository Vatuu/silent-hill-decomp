
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

#define copyData(arg0, data)                      \
    {                                             \
        s32 __temp;                               \
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
        __temp                   = data.field_A;  \
        arg0->field_D4.field_2   = __temp;        \
    }

void sharedFunc_800D70C4_0_s00(s_SubCharacter* arg0)
{
    s32 var_a3;
    s32 temp;
    s32 temp3;

    switch (arg0->model_0.anim_4.status_0)
    {
        case 0x10:
        case 0x12:
            func_80070400(arg0, &sharedData_800DE440_0_s00[15], &sharedData_800DDBA8_0_s00);
            break;

        case 0x11:
        case 0x13:
            copyData(arg0, sharedData_800DDBA8_0_s00);
            break;

        case 0x4C:
            if (arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] == -1)
            {
                func_80070400(arg0, &sharedData_800DE2C4_0_s00, &sharedData_800DDBBC_0_s00[0]);
            }
            else
            {
                func_80070400(arg0, &sharedData_800DE580_0_s00[20], &sharedData_800DDBBC_0_s00[0]);
            }
            break;

        case 0x2A:
            func_80070400(arg0, &sharedData_800DE2C4_0_s00, &sharedData_800DDBBC_0_s00[0]);
            break;

        case 0x2B:
        case 0x4D:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x161;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x160;
            func_80070400(arg0, &sharedData_800DDBBC_0_s00[temp], &sharedData_800DDBBC_0_s00[var_a3]);
            break;

        case 0x3E:
        case 0x3F:
            copyData(arg0, sharedData_800DDBBC_0_s00[8]);
            break;

        case 0x26:
            func_80070400(arg0, &sharedData_800DE2D8_0_s00, &sharedData_800DDC70_0_s00[0]);
            break;

        case 0x4E:
            if (arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] == -1)
            {
                func_80070400(arg0, &sharedData_800DE2D8_0_s00, &sharedData_800DDC70_0_s00[0]);
            }
            else
            {
                func_80070400(arg0, &sharedData_800DE8C8_0_s00[arg0->properties_E4.larvalStalker.properties_E8[5].val16[0]], &sharedData_800DDC70_0_s00[0]);
            }
            break;

        case 0x27:
        case 0x4F:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x153;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x152;
            func_80070400(arg0, &sharedData_800DDC70_0_s00[temp], &sharedData_800DDC70_0_s00[var_a3]);
            break;

        case 0x40:
        case 0x41:
            copyData(arg0, sharedData_800DDC70_0_s00[0]);
            break;

        case 0x28:
            func_80070400(arg0, &sharedData_800DE2EC_0_s00, &sharedData_800DDCFC_0_s00[0]);
            break;

        case 0x50:
            if (arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] == -1)
            {
                func_80070400(arg0, &sharedData_800DE2EC_0_s00, &sharedData_800DDCFC_0_s00[0]);
            }
            else
            {
                func_80070400(arg0, &sharedData_800DEB0C_0_s00[arg0->properties_E4.larvalStalker.properties_E8[5].val16[0]], &sharedData_800DDCFC_0_s00[0]);
            }
            break;

        case 0x29:
        case 0x51:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x15A;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x159;
            func_80070400(arg0, &sharedData_800DDCFC_0_s00[temp], &sharedData_800DDCFC_0_s00[var_a3]);
            break;

        case 0x42:
        case 0x43:
            copyData(arg0, sharedData_800DDCFC_0_s00[6]);
            break;

        case 0x2C:
            copyData(arg0, sharedData_800DDD88_0_s00[0]);
            break;

        case 0x2D:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x16A;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x169;
            func_80070400(arg0, &sharedData_800DDD88_0_s00[temp], &sharedData_800DDD88_0_s00[var_a3]);
            break;

        case 0x2E:
        case 0x52:
            copyData(arg0, sharedData_800DDEC8_0_s00[0]);
            break;

        case 0x2F:
        case 0x53:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x17A;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x179;
            func_80070400(arg0, &sharedData_800DDEC8_0_s00[temp], &sharedData_800DDEC8_0_s00[var_a3]);
            break;

        case 0x48:
            func_80070400(arg0, &sharedData_800DDBA8_0_s00, &sharedData_800DE008_0_s00[6]);
            break;

        case 0x14:
            func_80070400(arg0, &sharedData_800DDBA8_0_s00, &sharedData_800DE008_0_s00[0]);
            break;

        case 0x15:
        case 0x49:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x60;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x5F;
            func_80070400(arg0, &sharedData_800DE008_0_s00[temp], &sharedData_800DE008_0_s00[var_a3]);
            break;

        case 0x30:
            if (arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] != 0)
            {
                func_80070400(arg0, &sharedData_800DDD88_0_s00[arg0->properties_E4.larvalStalker.properties_E8[5].val16[0]], &sharedData_800DE0E4_0_s00[arg0->properties_E4.larvalStalker.properties_E8[5].val16[1]]);
            }
            else
            {
                copyData(arg0, sharedData_800DE0E4_0_s00[0]);
            }
            break;

        case 0x31:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x18A;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x189;
            func_80070400(arg0, &sharedData_800DE0E4_0_s00[temp], &sharedData_800DE0E4_0_s00[var_a3]);
            break;

        case 0x32:
            if (arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] == 0x53)
            {
                func_80070400(arg0, &sharedData_800DDF2C_0_s00[0], &sharedData_800DE1E8_0_s00[1]);
            }
            else
            {
                temp = arg0->properties_E4.larvalStalker.properties_E8[5].val16[0];
                if (arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] == 23)
                {
                    func_80070400(arg0, &sharedData_800DE580_0_s00[20 + temp], &sharedData_800DE1E8_0_s00[1]);
                }
                else if (arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] == 25)
                {
                    func_80070400(arg0, &sharedData_800DE8C8_0_s00[temp], &sharedData_800DE1E8_0_s00[1]);
                }
                else if (arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] == 27)
                {
                    func_80070400(arg0, &sharedData_800DEB0C_0_s00[temp], &sharedData_800DE1E8_0_s00[1]);
                }
            }
            break;

        case 0x33:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x197;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x196;
            func_80070400(arg0, &sharedData_800DE1E8_0_s00[temp], &sharedData_800DE1E8_0_s00[var_a3]);
            break;

        case 0x34:
        case 0x35:
            copyData(arg0, sharedData_800DE2C4_0_s00);
            break;

        case 0x22:
        case 0x23:
            copyData(arg0, sharedData_800DE2D8_0_s00);
            break;

        case 0x24:
        case 0x25:
            copyData(arg0, sharedData_800DE2EC_0_s00);
            break;

        case 0x36:
            copyData(arg0, sharedData_800DE300_0_s00[0]);
            break;

        case 0x37:
            temp = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x1AB;
            if (temp != 0xF)
            {
                var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x1AA;
            }
            else
            {
                var_a3 = 0;
            }
            func_80070400(arg0, &sharedData_800DE300_0_s00[temp], &sharedData_800DE300_0_s00[var_a3]);
            break;

        case 0x44:
        case 0x46:
            temp   = arg0->properties_E4.larvalStalker.properties_E8[5].val16[0];
            var_a3 = 0;
            func_80070400(arg0, &sharedData_800DEF1C_0_s00[temp], &sharedData_800DE440_0_s00[var_a3]);
            break;

        case 0x45:
        case 0x47:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x1CD;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x1CC;
            func_80070400(arg0, &sharedData_800DE440_0_s00[temp], &sharedData_800DE440_0_s00[var_a3]);
            arg0->field_C8.field_8 = arg0->field_C8.field_6;
            break;

        case 0x16:
            func_80070400(arg0, &sharedData_800DE2C4_0_s00, &sharedData_800DE580_0_s00[20]);
            break;

        case 0x17:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x6B;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x6A;
            func_80070400(arg0, &sharedData_800DE580_0_s00[20 + temp], &sharedData_800DE580_0_s00[20 + var_a3]);
            break;

        case 0x18:
            func_80070400(arg0, &sharedData_800DE2D8_0_s00, &sharedData_800DE8C8_0_s00[0]);
            break;

        case 0x19:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x81;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x80;
            func_80070400(arg0, &sharedData_800DE8C8_0_s00[temp], &sharedData_800DE8C8_0_s00[var_a3]);
            break;

        case 0x1A:
            func_80070400(arg0, &sharedData_800DE2EC_0_s00, &sharedData_800DEB0C_0_s00[0]);
            break;

        case 0x1B:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x9E;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x9D;
            func_80070400(arg0, &sharedData_800DEB0C_0_s00[temp], &sharedData_800DEB0C_0_s00[var_a3]);
            break;

        case 0xE:
            temp   = arg0->properties_E4.larvalStalker.properties_E8[5].val16[0];
            var_a3 = arg0->properties_E4.larvalStalker.properties_E8[5].val16[1];
            func_80070400(arg0, &sharedData_800DEF1C_0_s00[temp], &sharedData_800DE580_0_s00[var_a3]);
            break;

        case 0xF:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x32;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x31;
            func_80070400(arg0, &sharedData_800DE580_0_s00[temp], &sharedData_800DE580_0_s00[var_a3]);
            arg0->field_C8.field_8                                      = -0xB33;
            arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] = 0xF;
            break;

        case 0x2:
        case 0x54:
            func_80070400(arg0, &sharedData_800DE580_0_s00[19 + arg0->properties_E4.larvalStalker.properties_E8[5].val16[0]], &sharedData_800DEC74_0_s00[arg0->properties_E4.larvalStalker.properties_E8[5].val16[1]]);
            break;

        case 0x3:
        case 0x55:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT);
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) + 1;
            func_80070400(arg0, &sharedData_800DEC74_0_s00[temp], &sharedData_800DEC74_0_s00[var_a3]);
            break;

        case 0x6:
        case 0x56:
            func_80070400(arg0, &sharedData_800DE580_0_s00[19 + arg0->properties_E4.larvalStalker.properties_E8[5].val16[0]], &sharedData_800DECB0_0_s00[arg0->properties_E4.larvalStalker.properties_E8[5].val16[1]]);
            break;

        case 0x7:
        case 0x57:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0xA;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 9;
            func_80070400(arg0, &sharedData_800DECB0_0_s00[temp + 1], &sharedData_800DECB0_0_s00[var_a3 + 1]);
            break;

        case 0x4:
        case 0x58:
            temp3 = arg0->properties_E4.larvalStalker.properties_E8[5].val16[0];
            temp3--;
            var_a3 = 0;
            func_80070400(arg0, &sharedData_800DE580_0_s00[20 + temp3], &sharedData_800DEDA0_0_s00[var_a3]);
            break;

        case 0x5:
        case 0x59:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 4;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 3;
            func_80070400(arg0, &sharedData_800DEDA0_0_s00[temp], &sharedData_800DEDA0_0_s00[var_a3]);
            break;

        case 0x8:
            func_80070400(arg0, &sharedData_800DE8C8_0_s00[arg0->properties_E4.larvalStalker.properties_E8[5].val16[0]], &sharedData_800DEE04_0_s00[arg0->properties_E4.larvalStalker.properties_E8[5].val16[1]]);
            break;

        case 0x9:
            temp   = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x14;
            var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x13;
            func_80070400(arg0, &sharedData_800DEE04_0_s00[temp], &sharedData_800DEE04_0_s00[var_a3]);
            break;

        case 0xA:
            if (arg0->properties_E4.larvalStalker.properties_E8[5].val16[1] >= 2)
            {
                func_80070400(arg0, &sharedData_800DE8C8_0_s00[arg0->properties_E4.larvalStalker.properties_E8[5].val16[0]], &sharedData_800DEE40_0_s00[arg0->properties_E4.larvalStalker.properties_E8[5].val16[1]]);
            }
            else
            {
                copyData(arg0, sharedData_800DEE68_0_s00[0]);
            }
            break;

        case 0xB:
            temp = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x19;
            func_80070400(arg0, &sharedData_800DEE68_0_s00[temp], &sharedData_800DEE68_0_s00[temp + 1]);
            break;

        case 0x5B:
            temp = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x9E;
            func_80070400(arg0, &sharedData_800DEB0C_0_s00[temp + 1], &sharedData_800DEB0C_0_s00[temp]);
            break;

        case 0x3C:
            if (arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] == 0xF)
            {
                func_80070400(arg0, &sharedData_800DE580_0_s00[19], &sharedData_800DEF1C_0_s00[0]);
            }
            else if (arg0->properties_E4.larvalStalker.properties_E8[5].val16[0] == 0x37)
            {
                func_80070400(arg0, &sharedData_800DE300_0_s00[arg0->properties_E4.larvalStalker.properties_E8[5].val16[1]], &sharedData_800DEF1C_0_s00[0]);
            }
            break;

        case 0x3D:
        case 0x4B:
            temp = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x1DD;
            if (temp != 0x1D)
            {
                var_a3 = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x1DC;
            }
            else
            {
                var_a3 = 0;
            }
            func_80070400(arg0, &sharedData_800DEF1C_0_s00[temp], &sharedData_800DEF1C_0_s00[var_a3]);
            break;
    }

    func_8005C814(&arg0->field_D8, arg0);
}