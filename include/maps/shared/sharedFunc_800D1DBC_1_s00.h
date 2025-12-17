#include "bodyprog/bodyprog.h"

#define CopyData(arg0, data)                  \
{                                             \
    s32 __temp;                               \
                                              \
    arg0->field_C8.field_0 = data.field_0;    \
                                              \
    __temp = data.field_2;                    \
    arg0->field_C8.field_2 = __temp;          \
    arg0->field_C8.field_4 = data.field_4;    \
                                              \
    __temp = data.field_6;                    \
    arg0->field_C8.field_6 = __temp;          \
    arg0->field_D8.offsetX_4 = data.field_10; \
                                              \
    __temp = data.field_12;                   \
    arg0->field_D8.offsetZ_6 = __temp;        \
    arg0->field_D4.field_0   = data.field_8;  \
    arg0->field_D8.offsetX_0 = data.field_C;  \
                                              \
    __temp = data.field_E;                    \
    arg0->field_D8.offsetZ_2 = __temp;        \
                                              \
    __temp = data.field_A;                    \
    arg0->field_D4.field_2 = __temp;          \
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

void sharedFunc_800D1DBC_1_s00(s_SubCharacter* chara)
{
    s32 keyframeIdx0;
    s32 keyframeIdx1;
    s32 keyframeIdx2;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;

    switch (chara->model_0.anim_4.status_0) 
    {
        case ANIM_STATUS(2, false):
            keyframeIdx1 = chara->properties_E4.larvalStalker.properties_E8[3].val16[1];
            if (keyframeIdx1 != -1) 
            {
                if (keyframeIdx1 == -2) 
                {
                    func_80070400(chara, &sharedData_800DAF54_1_s00, &sharedData_800DA93C_1_s00);
                    break;
                } 

                var_a1 = keyframeIdx1;
                if (var_a1 < 15) 
                {
                    keyframeIdx0 = var_a1 - (var_a1 >= 11);
                } 
                else 
                {
                    if ((var_a1 - 24) >= 0) 
                    {
                        keyframeIdx0 = var_a1 - 10;
                    }
                    else
                    {
                        keyframeIdx0 = 14;
                    }
                }

                func_80070400(chara, &sharedData_800DA964_1_s00[keyframeIdx0], &sharedData_800DA93C_1_s00);
                break;
            } 

            CopyData(chara, sharedData_800DA928_1_s00[1]);
            break;

        case ANIM_STATUS(3, true):
        case ANIM_STATUS(18, true):
            keyframeIdx0 = (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 24 && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 30) ? 0 : 1;
            keyframeIdx1 = (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 23 && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 29) ? 0 : 1;
            func_80070400(chara, &sharedData_800DA928_1_s00[keyframeIdx0], &sharedData_800DA928_1_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(2, true):
        case ANIM_STATUS(3, false):
        case ANIM_STATUS(14, false):
        case ANIM_STATUS(14, true):
        case ANIM_STATUS(18, false):
            CopyData(chara, sharedData_800DA928_1_s00[1]);
            break;  
            
        case ANIM_STATUS(4, false):
            func_80070400(chara, &sharedData_800DB008_1_s00, &sharedData_800DA950_1_s00);
            break;
            
        case ANIM_STATUS(4, true):
        case ANIM_STATUS(13, false):
        case ANIM_STATUS(13, true):
            CopyData(chara, sharedData_800DA950_1_s00);
            break;
            
        case ANIM_STATUS(5, false):
            var_a3 = chara->properties_E4.larvalStalker.properties_E8[3].val16[0];
            if (var_a3 == 0) 
            {
                CopyData(chara, sharedData_800DA964_1_s00[0]);
                break;
            }

            keyframeIdx1 = chara->properties_E4.larvalStalker.properties_E8[3].val16[1];
            if ((keyframeIdx1 - 24) >= 0) 
            {
                keyframeIdx0 = keyframeIdx1 - 10;
            }
            else
            {
                keyframeIdx0 = 14;
            }

            func_80070400(chara, &sharedData_800DA964_1_s00[keyframeIdx0], &sharedData_800DA964_1_s00[var_a3]);
            break;
            
        case ANIM_STATUS(5, true):
        case ANIM_STATUS(15, true):
            var_a0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
            var_a1 = var_a0 - 41;
            if (var_a1 < 15) 
            {
                keyframeIdx0 = var_a1 - (var_a1 >= 11);
                keyframeIdx1 = (var_a0 - 40) - (var_a1 >= 10);
            } 
            else 
            {
                if ((var_a0 - 65) >= 0) 
                {
                    keyframeIdx0 = var_a0 - 51;
                }
                else
                {
                    keyframeIdx0 = 14;
                }
                
                if ((var_a0 - 64) >= 0) 
                {
                    keyframeIdx1 = var_a0 - 50;
                }
                else
                {
                    keyframeIdx1 = 14;
                }
            }

            func_80070400(chara, &sharedData_800DA964_1_s00[keyframeIdx0], &sharedData_800DA964_1_s00[keyframeIdx1]);
            break;
            
        case ANIM_STATUS(6, false):
            keyframeIdx2 = chara->properties_E4.larvalStalker.properties_E8[3].val16[0];
            if (keyframeIdx2 == 0) 
            {
                CopyData(chara, sharedData_800DAC34_1_s00[0]);
                break;
            }

            var_a1 = chara->properties_E4.larvalStalker.properties_E8[3].val16[1];
            keyframeIdx0 = ((var_a1 - 7) - (var_a1 >= 23)) - (var_a1 >= 24);
            func_80070400(chara, &sharedData_800DAC34_1_s00[keyframeIdx0], &sharedData_800DAC34_1_s00[keyframeIdx2]);
            break;

        case ANIM_STATUS(6, true):
        case ANIM_STATUS(16, true):
            var_a2 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
            var_a1 = var_a2 - 86;
            if (var_a1 < 15) 
            {
                keyframeIdx0 = MIN(8, var_a1);
                keyframeIdx1 = MIN(8, var_a2 - 85);
            } 
            else 
            {
                keyframeIdx0 = var_a2 - 93 - (var_a1 >= 23) - (var_a1 >= 24);
                keyframeIdx1 = var_a2 - 92 - (var_a1 >= 22) - (var_a1 >= 23) - (var_a1 >= 33);
            }

            func_80070400(chara, &sharedData_800DAC34_1_s00[keyframeIdx0], &sharedData_800DAC34_1_s00[keyframeIdx1]);
            break;
            
        case ANIM_STATUS(7, false):
            if (chara->properties_E4.larvalStalker.properties_E8[3].val16[0] == 0) 
            {
                CopyData(chara, sharedData_800DAE28_1_s00[0]);
                break;
            }
            
            var_a1 = chara->properties_E4.larvalStalker.properties_E8[3].val16[1];
            if (var_a1 < 15) 
            {
                keyframeIdx0 = var_a1 - (var_a1 >= 11);
            } 
            else 
            {
                if ((var_a1 - 24) >= 0) 
                {
                    keyframeIdx0 = var_a1 - 10;
                }
                else
                {
                    keyframeIdx0 = 14;
                }
            }

            keyframeIdx1 = chara->properties_E4.larvalStalker.properties_E8[3].val16[0];
            func_80070400(chara, &sharedData_800DA964_1_s00[keyframeIdx0], &sharedData_800DAE28_1_s00[keyframeIdx1]);
            break;
            
        case ANIM_STATUS(7, true):
            chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = -2;
            keyframeIdx1 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);

            var_a1 = keyframeIdx1 - 121;
            if (var_a1 < 11) 
            {
                if (var_a1 < 16) 
                {
                    goto block_48;
                } 
                else 
                {
                    keyframeIdx0 = 15;
                }
            } 
            else 
            {
                if ((keyframeIdx1 - 122) < 16) 
                {
    block_48:
                    keyframeIdx0 = var_a1 - (var_a1 > 10);
                } 
                else 
                {
                    keyframeIdx0 = 15;
                }
            }
            
            if (var_a1 > 9) 
            {
                if (var_a1 < 16) 
                {
                    goto block_54;
                } 
                else 
                {
                    keyframeIdx1 = 15;
                }
            } 
            else 
            {
                keyframeIdx1 = var_a1 + 1;
                if (keyframeIdx1 < 16) 
                {
    block_54:
                    keyframeIdx1 = var_a1 + (var_a1 < 10);
                }
                else
                {
                    keyframeIdx1 = 15;
                }
            }

            func_80070400(chara, &sharedData_800DAE28_1_s00[keyframeIdx0], &sharedData_800DAE28_1_s00[keyframeIdx1]);
            break;
            
        case ANIM_STATUS(8, false):
            if (chara->properties_E4.larvalStalker.properties_E8[3].val16[0] == 0) 
            {
                CopyData(chara, sharedData_800DAF68_1_s00[0]);
                break;
            }

            var_a1 = chara->properties_E4.larvalStalker.properties_E8[3].val16[1];
            if (var_a1 < 15) 
            {
                keyframeIdx0 = MIN(8, var_a1);
            } 
            else 
            {
                keyframeIdx0 = ((var_a1 - 7) - (var_a1 >= 23)) - (var_a1 >= 24);
            }

            keyframeIdx1 = chara->properties_E4.larvalStalker.properties_E8[3].val16[0];
            func_80070400(chara, &sharedData_800DAC34_1_s00[keyframeIdx0], &sharedData_800DAF68_1_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(8, true):
            chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = -2;
            var_a0 = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
            var_a1 = var_a0 - 143;

            keyframeIdx0 = MIN(7, var_a1);
            keyframeIdx1 = MIN(7, var_a0 - 142);
            func_80070400(chara, &sharedData_800DAF68_1_s00[keyframeIdx0], &sharedData_800DAF68_1_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(9, false):
            keyframeIdx1 = chara->properties_E4.larvalStalker.properties_E8[3].val16[1];
            if (keyframeIdx1 == -1) 
            {
                CopyData(chara, sharedData_800DB008_1_s00);
                break;
            }
            if (keyframeIdx1 == -2) 
            {
                func_80070400(chara, &sharedData_800DAFF4_1_s00, &sharedData_800DB008_1_s00);
                break;
            }

            var_a1 = keyframeIdx1;
            if (var_a1 < 15) 
            {
                keyframeIdx0 = MIN(8, var_a1);
            } 
            else 
            {
                keyframeIdx0 = var_a1 - 7;
            }

            func_80070400(chara, &sharedData_800DAC34_1_s00[keyframeIdx0], &sharedData_800DB008_1_s00);
            break;

        case ANIM_STATUS(9, true):
        case ANIM_STATUS(17, false):
        case ANIM_STATUS(17, true):
            CopyData(chara, sharedData_800DB008_1_s00);
            break;
            
        case ANIM_STATUS(10, false):
        case ANIM_STATUS(10, true):
            CopyData(chara, sharedData_800DB01C_1_s00);
            break;
            
        case ANIM_STATUS(11, false):
        case ANIM_STATUS(11, true):
        case ANIM_STATUS(12, false):
        case ANIM_STATUS(12, true):
            CopyData(chara, sharedData_800DB030_1_s00);
            break;
            
        case ANIM_STATUS(1, false):
        case ANIM_STATUS(1, true):
            chara->field_C8.field_0   = Q12(-0.72f);
            chara->field_C8.field_4   = Q12(-0.2f);
            chara->field_C8.field_6   = Q12(-0.66f);
            chara->field_D4.field_0   = Q12(0.12f);
            chara->field_D8.offsetZ_2 = Q12(0.02f);
            chara->field_D4.field_2   = Q12(0.11f);
            chara->field_C8.field_2   = Q12(0.0f);
            chara->field_D8.offsetX_4 = Q12(0.0f);
            chara->field_D8.offsetZ_6 = Q12(0.0f);
            chara->field_D8.offsetX_0 = Q12(0.0f);
            chara->field_C8.field_8   = Q12(-0.59f);
            break;
    }

    func_8005C814(&chara->field_D8, chara);
}
