#include "bodyprog/bodyprog.h"

#define copyData(arg0, data) \
{\
    s32 __temp; \
    arg0->field_C8.field_0 = data.field_0; \
    __temp = data.field_2; \
    arg0->field_C8.field_2 = __temp; \
    arg0->field_C8.field_4 = data.field_4; \
    __temp = data.field_6; \
    arg0->field_C8.field_6 = __temp; \
    arg0->field_D8.offsetX_4 = data.field_10; \
    __temp = data.field_12; \
    arg0->field_D8.offsetZ_6 = __temp; \
    arg0->field_D4.field_0 = data.field_8; \
    arg0->field_D8.offsetX_0 = data.field_C; \
    __temp = data.field_E; \
    arg0->field_D8.offsetZ_2 = __temp; \
    __temp = data.field_A; \
    arg0->field_D4.field_2 = __temp; \
}

extern s_func_80070400_1 sharedData_800DA928_1_s00[];
extern s_func_80070400_1 sharedData_800DA93C_1_s00;
extern s_func_80070400_1 sharedData_800DA950_1_s00;
extern s_func_80070400_1 sharedData_800DA964_1_s00[];

extern s_func_80070400_1 sharedData_800DAC34_1_s00[];
extern s_func_80070400_1 sharedData_800DAE28_1_s00[];

extern s_func_80070400_1 sharedData_800DAF54_1_s00;
extern s_func_80070400_1 sharedData_800DAF68_1_s00[];

extern s_func_80070400_1 sharedData_800DAFF4_1_s00;

extern s_func_80070400_1 sharedData_800DB008_1_s00;
extern s_func_80070400_1 sharedData_800DB01C_1_s00;

extern s_func_80070400_1 sharedData_800DB030_1_s00;

void sharedFunc_800D1DBC_1_s00(s_SubCharacter* arg0) {
    s32 var_v0;
    s32 var_v1;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;

    switch (arg0->model_0.anim_4.status_0) 
    {
    case 4:
        var_v1 = arg0->properties_E4.larvalStalker.properties_E8[3].val16[1];
        if (var_v1 != -1) 
        {
            if (var_v1 == -2) 
            {
                func_80070400(arg0, &sharedData_800DAF54_1_s00, &sharedData_800DA93C_1_s00);
                break;
            } 
            var_a1 = var_v1;
            if (var_a1 < 0xF) 
            {
                var_t0 = var_a1 - (var_a1 >= 0xB);
            } 
            else 
            {
                if ((var_a1 - 0x18) >= 0) 
                {
                    var_t0 = var_a1 - 0xA;
                }
                else
                {
                    var_t0 = 0xE;
                }
            }

            func_80070400(arg0, &sharedData_800DA964_1_s00[var_t0], &sharedData_800DA93C_1_s00);
            break;
        } 

        copyData(arg0, sharedData_800DA928_1_s00[1]);
        break;

    case 7:
    case 37:
        var_t0 = ((arg0->model_0.anim_4.time_4 >> 0xC) > 0x18 && (arg0->model_0.anim_4.time_4 >> 0xC) < 0x1E) ? 0 : 1;
        var_v1 = ((arg0->model_0.anim_4.time_4 >> 0xC) > 0x17 && (arg0->model_0.anim_4.time_4 >> 0xC) < 0x1D) ? 0 : 1;

        func_80070400(arg0, &sharedData_800DA928_1_s00[var_t0], &sharedData_800DA928_1_s00[var_v1]);
        break;

    case 5:
    case 6:
    case 28:
    case 29:
    case 36:
        copyData(arg0, sharedData_800DA928_1_s00[1]);
        break;  
        
    case 8:
        func_80070400(arg0, &sharedData_800DB008_1_s00, &sharedData_800DA950_1_s00);
        break;
        
    case 9:
    case 26:
    case 27:
        copyData(arg0, sharedData_800DA950_1_s00);
        break;
        
    case 10:
        var_a3 = arg0->properties_E4.larvalStalker.properties_E8[3].val16[0];
        if (var_a3 == 0) 
        {
            copyData(arg0, sharedData_800DA964_1_s00[0]);
            break;
        }
        var_v1 = arg0->properties_E4.larvalStalker.properties_E8[3].val16[1];
        if ((var_v1 - 0x18) >= 0) 
        {
            var_t0 = var_v1 - 0xA;
        }
        else
        {
            var_t0 = 0xE;
        }
        func_80070400(arg0, &sharedData_800DA964_1_s00[var_t0], &sharedData_800DA964_1_s00[var_a3]);
        break;
        
    case 11:
    case 31:
        var_a0 = arg0->model_0.anim_4.time_4 >> 0xC;
        var_a1 = var_a0 - 0x29;
        if (var_a1 < 0xF) 
        {
            var_t0 = var_a1 - (var_a1 >= 0xB);
            var_v1 = (var_a0 - 0x28) - (var_a1 >= 0xA);
        } 
        else 
        {
            if ((var_a0 - 0x41) >= 0) 
            {
                var_t0 = var_a0 - 0x33;
            }
            else
            {
                var_t0 = 0xE;
            }
            
            if ((var_a0 - 0x40) >= 0) 
            {
                var_v1 = var_a0 - 0x32;
            }
            else
            {
                var_v1 = 0xE;
            }
        }
        func_80070400(arg0, &sharedData_800DA964_1_s00[var_t0], &sharedData_800DA964_1_s00[var_v1]);
        break;
        
    case 12:
        var_v0 = arg0->properties_E4.larvalStalker.properties_E8[3].val16[0];
        if (var_v0 == 0) 
        {
            copyData(arg0, sharedData_800DAC34_1_s00[0]);
            break;
        }
        var_a1 = arg0->properties_E4.larvalStalker.properties_E8[3].val16[1];
        var_t0 = ((var_a1 - 7) - (var_a1 >= 0x17)) - (var_a1 >= 0x18);
        func_80070400(arg0, &sharedData_800DAC34_1_s00[var_t0], &sharedData_800DAC34_1_s00[var_v0]);
        break;
        
    case 13:
    case 33:
        var_a2 = arg0->model_0.anim_4.time_4 >> 0xC;
        var_a1 = var_a2 - 0x56;
        if (var_a1 < 0xF) 
        {
            var_t0 = MIN(8, var_a1);
            var_v1 = MIN(8, var_a2 - 0x55);
        } 
        else 
        {
            var_t0 = var_a2 - 0x5D - (var_a1 >= 0x17) - (var_a1 >= 0x18);
            var_v1 = var_a2 - 0x5C - (var_a1 >= 0x16) - (var_a1 >= 0x17) - (var_a1 >= 0x21);
        }
        func_80070400(arg0, &sharedData_800DAC34_1_s00[var_t0], &sharedData_800DAC34_1_s00[var_v1]);
        break;
        
    case 14:
        if (arg0->properties_E4.larvalStalker.properties_E8[3].val16[0] == 0) 
        {
            copyData(arg0, sharedData_800DAE28_1_s00[0]);
            break;
        }
        
        var_a1 = arg0->properties_E4.larvalStalker.properties_E8[3].val16[1];
        if (var_a1 < 0xF) 
        {
            var_t0 = var_a1 - (var_a1 >= 0xB);
        } 
        else 
        {
            if ((var_a1 - 0x18) >= 0) 
            {
                var_t0 = var_a1 - 0xA;
            }
            else
            {
                var_t0 = 0xE;
            }
        }
        var_v1 = arg0->properties_E4.larvalStalker.properties_E8[3].val16[0];
        func_80070400(arg0, &sharedData_800DA964_1_s00[var_t0], &sharedData_800DAE28_1_s00[var_v1]);
        break;
        
    case 15:
        arg0->properties_E4.larvalStalker.properties_E8[3].val16[1] = -2;
        var_v1 = arg0->model_0.anim_4.time_4 >> 0xC;
        var_a1 = var_v1 - 0x79;
        if (var_a1 < 0xB) 
        {
            if (var_a1 < 0x10) 
            {
                goto block_48;
            } 
            else 
            {
                var_t0 = 0xF;
            }
        } 
        else 
        {
            if ((var_v1 - 0x7A) < 0x10) 
            {
block_48:
                var_t0 = var_a1 - (var_a1 > 0xA);
            } 
            else 
            {
                var_t0 = 0xF;
            }
        }
        
        if (var_a1 > 9) 
        {
            if (var_a1 < 0x10) 
            {
                goto block_54;
            } 
            else 
            {
                var_v1 = 0xF;
            }
        } 
        else 
        {
            var_v1 = var_a1 + 1;
            if (var_v1 < 0x10) 
            {
block_54:
                var_v1 = var_a1 + (var_a1 < 0xA);
            }
            else
            {
                var_v1 = 0xF;
            }
        }
        func_80070400(arg0, &sharedData_800DAE28_1_s00[var_t0], &sharedData_800DAE28_1_s00[var_v1]);
        break;
        
    case 16:
        if (arg0->properties_E4.larvalStalker.properties_E8[3].val16[0] == 0) 
        {
            copyData(arg0, sharedData_800DAF68_1_s00[0]);
            break;
        }
        var_a1 = arg0->properties_E4.larvalStalker.properties_E8[3].val16[1];
        if (var_a1 < 0xF) 
        {
            var_t0 = MIN(8, var_a1);
        } 
        else 
        {
            var_t0 = ((var_a1 - 7) - (var_a1 >= 0x17)) - (var_a1 >= 0x18);
        }
        var_v1 = arg0->properties_E4.larvalStalker.properties_E8[3].val16[0];
        func_80070400(arg0, &sharedData_800DAC34_1_s00[var_t0], &sharedData_800DAF68_1_s00[var_v1]);
        break;
        
    case 17:
        arg0->properties_E4.larvalStalker.properties_E8[3].val16[1] = -2;
        var_a0 = arg0->model_0.anim_4.time_4 >> 0xC;
        var_a1 = var_a0 - 0x8F;
        var_t0 = MIN(7, var_a1);
        var_v1 = MIN(7, var_a0 - 0x8E);
        func_80070400(arg0, &sharedData_800DAF68_1_s00[var_t0], &sharedData_800DAF68_1_s00[var_v1]);
        break;
        
    case 18:
        var_v1 = arg0->properties_E4.larvalStalker.properties_E8[3].val16[1];
        if (var_v1 == -1) 
        {
            copyData(arg0, sharedData_800DB008_1_s00);
            break;
        }
        if (var_v1 == -2) 
        {
            func_80070400(arg0, &sharedData_800DAFF4_1_s00, &sharedData_800DB008_1_s00);
            break;
        }

        var_a1 = var_v1;
        if (var_a1 < 0xF) 
        {
            var_t0 = MIN(8, var_a1);
        } 
        else 
        {
            var_t0 = var_a1 - 7;
        }

        func_80070400(arg0, &sharedData_800DAC34_1_s00[var_t0], &sharedData_800DB008_1_s00);
        break;

    case 19:
    case 34:
    case 35:
        copyData(arg0, sharedData_800DB008_1_s00);
        break;
        
    case 20:
    case 21:
        copyData(arg0, sharedData_800DB01C_1_s00);
        break;
        
    case 22:
    case 23:
    case 24:
    case 25:
        copyData(arg0, sharedData_800DB030_1_s00);
        break;
        
    case 2:
    case 3:
        arg0->field_C8.field_0 = -0xB85;
        arg0->field_C8.field_4 = -0x333;
        arg0->field_C8.field_6 = -0xA8F;
        arg0->field_D4.field_0 = 0x1EB;
        arg0->field_D8.offsetZ_2 = 0x51;
        arg0->field_D4.field_2 = 0x1C2;
        arg0->field_C8.field_2 = 0;
        arg0->field_D8.offsetX_4 = 0;
        arg0->field_D8.offsetZ_6 = 0;
        arg0->field_D8.offsetX_0 = 0;
        arg0->field_C8.field_8 = -0x970;
        break;
    }
    func_8005C814(&arg0->field_D8, arg0);
}
