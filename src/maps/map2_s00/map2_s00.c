#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map2/map2_s00.h"

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800C9578);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CD5C0

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CDC3C

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CDD14

#include "maps/shared/Particle_Update.h" // 0x800CE020

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CEA04

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CF02C

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800CEFD0_1_s02); // 0x800CF17C

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CF544

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CF670

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CF678

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CF730

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CF7B8

#include "maps/shared/Player.h"

#include "maps/shared/Ai_AirScreamer_Update.h" // 0x800D1F40

#include "maps/shared/sharedFunc_800D21E4_0_s01.h" // 0x800D1FB4

#include "maps/shared/sharedFunc_800D2200_0_s01.h" // 0x800D1FD0

#include "maps/shared/sharedFunc_800D2274_0_s01.h" // 0x800D2044

#include "maps/shared/sharedFunc_800D2364_0_s01.h" // 0x800D2134

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D2390_0_s01); // 0x800D2160

#include "maps/shared/Ai_AirScreamer_Init.h" // 0x800D2744

#include "maps/shared/sharedFunc_800D2B00_0_s01.h" // 0x800D28D0

#include "maps/shared/sharedFunc_800D2B10_0_s01.h" // 0x800D28E0

#include "maps/shared/sharedFunc_800D2B28_0_s01.h" // 0x800D28F8

#include "maps/shared/sharedFunc_800D2B4C_0_s01.h" // 0x800D291C

#include "maps/shared/sharedFunc_800D2BB0_0_s01.h" // 0x800D2980

#include "maps/shared/sharedFunc_800D2BE4_0_s01.h" // 0x800D29B4

#include "maps/shared/sharedFunc_800D2BF4_0_s01.h" // 0x800D29C4

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", Chara_DamageTake); // 0x800D29DC

#include "maps/shared/sharedFunc_800D2E04_0_s01.h" // 0x800D2BE0

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D2FB4_0_s01);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D31D0_0_s01); // 0x800D2FAC

#include "maps/shared/sharedFunc_800D3430_0_s01.h" // 0x800D320C

#include "maps/shared/sharedFunc_800D3508_0_s01.h" // 0x800D32E4

#include "maps/shared/sharedFunc_800D3630_0_s01.h" // 0x800D340C

#include "maps/shared/sharedFunc_800D3758_0_s01.h" // 0x800D3534

#include "maps/shared/sharedFunc_800D3814_0_s01.h" // 0x800D35F0

#include "maps/shared/sharedFunc_800D3928_0_s01.h" // 0x800D3704

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CA860);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CA864);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CA870);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CA888);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CA8A0);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", D_800CA8B8);

INCLUDE_RODATA("asm/maps/map2_s00/nonmatchings/map2_s00", sharedData_800CAA98_0_s01);

#include "maps/shared/sharedSymbol_800D3B0C_0_s01.h" // 0x800D37D0

#include "maps/shared/sharedFunc_800D3CC4_0_s01.h" // 0x800D3A30

#include "maps/shared/sharedFunc_800D3DFC_0_s01.h" // 0x800D3B68

#include "maps/shared/sharedFunc_800D3C24_2_s00.h" // 0x800D3C24

#include "maps/shared/sharedFunc_800D3E44_2_s00.h" // 0x800D3E44

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D3FA4);

#include "maps/shared/sharedFunc_800D4358_2_s00.h" // 0x800D4358

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D46C8);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D4A9C);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D4E78);

#include "maps/shared/sharedFunc_800D5268_2_s00.h" // 0x800D5268

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D5554);

#include "maps/shared/sharedFunc_800D5974_2_s00.h" // 0x800D5974

#include "maps/shared/sharedFunc_800D5B88_2_s00.h" // 0x800D5B88

#include "maps/shared/sharedFunc_800D5DAC_2_s00.h" // 0x800D5DAC

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D603C);

#include "maps/shared/sharedFunc_800D6400_2_s00.h" // 0x800D6400

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D6504);

#include "maps/shared/sharedFunc_800D69A0_2_s00.h" // 0x800D69A0

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D6A7C);

#include "maps/shared/sharedFunc_800D6E28_2_s00.h" // 0x800D6E28

void func_800D71A4(s_SubCharacter* chara)
{
    bool temp_a0;
    s32 rngAngle0;
    s32 angle0;
    s32 angleSubtract;
    s32 switch3;
    s32 condModelStateIs2;
    s32 angle1;
    s32 dmgType;
    s32 animStatus;
    bool tmp1;
    bool tmp2;
    bool tmp3;
    bool flag1;
    bool flag2;
    bool flag0;

    animStatus = chara->model_0.anim_4.status_0;
    angle0 = sharedData_800E21D0_0_s01.field_15C;

    tmp3 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    tmp2 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    tmp1 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    flag0 = tmp3;
    flag1 = tmp2;
    flag2 = tmp1;
    temp_a0 = sharedFunc_800DC50C_2_s00(chara);
    condModelStateIs2 = switch3 = 0;
    switch (chara->model_0.stateStep_3)
    {
        case 0:
            chara->properties_E4.unk0.properties_120.val32 = Q12(6.0f);
            /* fallthrough */
        case 1:
            sharedFunc_800DE6A8_2_s00(chara, &chara->properties_E4.unk0.pos_104, Q12(1.5f));
            if (!sharedFunc_800DC3BC_2_s00(chara) || func_80080514() >= FP_ANGLE(72.0f))
            {
                chara->model_0.stateStep_3 = 2;
    
            }
            else
            {
                chara->model_0.stateStep_3 = 4;
            }
            break;
        case 2:
            condModelStateIs2 = 1;
            /* fallthrough */
        case 3:
            if (temp_a0)
            {
                chara->model_0.stateStep_3 = 4;
                break;
            }
            if (Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8) < Q12(1.0f))
            {

                chara->model_0.stateStep_3 = 1;
            }
            else if (!chara->properties_E4.unk0.properties_120.val32)
            {
                if (condModelStateIs2)
                {
                    switch3 = 1;
                }
                chara->model_0.stateStep_3 = 0;
            }
            else if (flag0 || flag1 || flag2)
            {
                chara->model_0.stateStep_3 = 3;
                if (angle0 > (FP_ANGLE(2.9f)))
                {
                    angle1 = func_80080478(&chara->position_18, &chara->properties_E4.unk0.pos_104) - chara->rotation_24.vy;
                    angle1 = FP_ANGLE_NORM_S(angle1);
                    if (angle1 < FP_ANGLE(0.0f))
                    {
                        angle1 += FP_ANGLE(0.3f);
                    }
                    sharedFunc_800D529C_0_s01(chara, Q12(1.5f), (angle1 >> 2) + chara->rotation_24.vy);
                    chara->properties_E4.unk0.properties_120.val32 = Q12(6.0f);
                }
            }
            break;
        case 4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switch3 = 2;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                if (flag2 || flag1)
                {
                    chara->model_0.stateStep_3 = 7;
                }
                else
                {
                    chara->model_0.stateStep_3 = 6;
                }
    
            }
            else if (flag2 || flag1)
            {
                chara->model_0.stateStep_3 = 5;
            }
            break;
        case 5:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switch3 = 3;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                chara->model_0.stateStep_3 = 7;
            }
            break;
        case 6:
            switch3 = 3;
            if (flag2 || flag1)
            {
                chara->model_0.stateStep_3 = 7;
            }
            else
            {
                switch3 = 2;
            }
            break;
        case 7:
            switch3 = 3;
            break;
    }
    sharedFunc_800D57C8_0_s01(chara);
    dmgType = Chara_DamageTake(chara, Q12(1.0f));
    switch (dmgType)
    {
        case 0:
            switch (switch3) 
            {
                case 0:
                case 1:
                    if (!flag2 && !flag1)
                    {
                        if (switch3 == 1)
                        {
                            rngAngle0 = func_80080514();
                            angleSubtract = FP_ANGLE(0.0f);
                            if (chara->properties_E4.unk0.field_E8_8 == switch3) 
                            {
                                angleSubtract = FP_ANGLE(36.0f);
                            }
                            if (rngAngle0 < (FP_ANGLE(252.0f) - (angleSubtract * 2))) 
                            {
                                chara->model_0.state_2 = 0x1C;
                                chara->model_0.stateStep_3 = 0;
                            }
                        }
                    }
                    else 
                    {
                        chara->model_0.state_2 = 0x15;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;
                case 2:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true)) 
                    {
                        chara->model_0.state_2 = 6;
                        chara->model_0.stateStep_3 = 0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(chara))
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;
                case 3:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true)) 
                    {
                        chara->model_0.state_2 = 7;
                        chara->model_0.stateStep_3 = 0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(chara))
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;
            }
            break;
        case 1:
            chara->model_0.state_2 = 0x1D;
            chara->model_0.stateStep_3 = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;
        case 2:
            chara->model_0.state_2 = 0x1E;
            chara->model_0.stateStep_3 = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;
        case 3:
        case 4:
            chara->model_0.state_2 = 0x20;
            chara->model_0.stateStep_3 = 0;
            if (chara->health_B0 <= 0)
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
        }

}

void func_800D756C(s_SubCharacter* chara)
{
    bool temp_a0;
    s32 rngAngle0;
    s32 angle0;
    s32 angleSubtract;
    s32 switch3;
    s32 condModelStateIs2;
    s32 angle1;
    s32 dmgType;
    s32 animStatus;
    bool tmp1;
    bool tmp2;
    bool tmp3;
    bool flag1;
    bool flag2;
    bool flag0;

    switch3 = 0;
    condModelStateIs2 = 0;
    animStatus = chara->model_0.anim_4.status_0;
    angle0 = sharedData_800E21D0_0_s01.field_15C;

    tmp3 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_0;
    tmp2 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_1;
    tmp1 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    flag0 = tmp3;
    flag1 = tmp2;
    flag2 = tmp1;
    temp_a0 = sharedFunc_800DC50C_2_s00(chara);
    switch (chara->model_0.stateStep_3)
    {
        case 0:
            chara->properties_E4.unk0.properties_120.val32 = Q12(6.0f);
            /* fallthrough */
        case 1:
            sharedFunc_800DE6A8_2_s00(chara, &chara->properties_E4.unk0.pos_104, Q12(2.0f));
            if (!sharedFunc_800DC3BC_2_s00(chara) || func_80080514() >= FP_ANGLE(36.0f))
            {
                chara->model_0.stateStep_3 = 2;
    
            }
            else
            {
                chara->model_0.stateStep_3 = 4;
            }
            break;
        case 2:
            condModelStateIs2 = 1;
            /* fallthrough */
        case 3:
            if (temp_a0)
            {
                chara->model_0.stateStep_3 = 4;
                break;
            }
            if (Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8) < Q12(1.0f))
            {
                if (condModelStateIs2)
                {
                    switch3 = 1;
                }
                chara->model_0.stateStep_3 = 1;
            }
            else if (!chara->properties_E4.unk0.properties_120.val32)
            {
                chara->model_0.stateStep_3 = 0;
            }
            else if (flag2 || flag0 || flag1)
            {
                chara->model_0.stateStep_3 = 3;
                if (angle0 > (FP_ANGLE(2.9f)))
                {
                    angle1 = func_80080478(&chara->position_18, &chara->properties_E4.unk0.pos_104) - chara->rotation_24.vy;
                    angle1 = FP_ANGLE_NORM_S(angle1);
                    if (angle1 < FP_ANGLE(0.0f))
                    {
                        angle1 += FP_ANGLE(0.3f);
                    }
                    sharedFunc_800D529C_0_s01(chara, Q12(2.0f), (angle1 >> 2) + chara->rotation_24.vy);
                    chara->properties_E4.unk0.properties_120.val32 = Q12(6.0f);
                }
            }
            break;
        case 4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switch3 = 2;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                if (flag1 || flag0)
                {
                    chara->model_0.stateStep_3 = 7;
                }
                else
                {
                    chara->model_0.stateStep_3 = 6;
                }
    
            }
            else if (flag2 || flag1 || flag0)
            {
                chara->model_0.stateStep_3 = 5;
            }
            break;
        case 5:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switch3 = 3;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                chara->model_0.stateStep_3 = 7;
            }
            break;
        case 6:
            switch3 = 3;
            if (flag2 || flag1 || flag0)
            {
                chara->model_0.stateStep_3 = 7;
            }
            else
            {
                switch3 = 2;
            }
            break;
        case 7:
            switch3 = 3;
            break;
    }
    sharedFunc_800D57C8_0_s01(chara);
    dmgType = Chara_DamageTake(chara, Q12(1.0f));
    switch (dmgType)
    {
        case 0:
            switch (switch3) 
            {
                case 0:
                case 1:
                    if (flag2 == 0)
                    {
                        if (switch3 == 1)
                        {
                            rngAngle0 = func_80080514();
                            angleSubtract = FP_ANGLE(0.0f);
                            if (chara->properties_E4.unk0.field_E8_8 == switch3) 
                            {
                                angleSubtract = FP_ANGLE(36.0f);
                            }
                            if (rngAngle0 < (FP_ANGLE(252.0f) - (angleSubtract * 2))) 
                            {
                                chara->model_0.state_2 = 0x14;
                                chara->model_0.stateStep_3 = 0;
                            }
                        }
                    }
                    else 
                    {
                        chara->model_0.state_2 = 0x16;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;
                case 2:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true)) 
                    {
                        if (!flag2)
                        {
                            chara->model_0.state_2 = 6;
                        }
                        else
                        {
                            chara->model_0.state_2 = 8;
                        }
                        
                        chara->model_0.stateStep_3 = 0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(chara))
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;
                case 3:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true)) 
                    {
                        if (flag2) 
                        {
                            chara->model_0.state_2 = 8;
                        }
                        else
                        {
                            chara->model_0.state_2 = 7;
                        }
                        chara->model_0.stateStep_3 = 0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(chara))
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;
            }
            break;
        case 1:
            chara->model_0.state_2 = 0x1D;
            chara->model_0.stateStep_3 = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;
        case 2:
            chara->model_0.state_2 = 0x1E;
            chara->model_0.stateStep_3 = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;
        case 3:
        case 4:
            chara->model_0.state_2 = 0x20;
            chara->model_0.stateStep_3 = 0;
            if (chara->health_B0 <= 0)
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
        }
}

void func_800D794C(s_SubCharacter* chara)
{
    s32 flag2;
    s32 angle0;
    s32 angle1;
    s32 angle2;
    bool temp_s3;
    s32 distance0;
    s32 switch3;
    s32 var_s5;
    s32 angleAdd;
    s32 dmgType;
    s32 animStatus;

    switch3 = 0;
    angleAdd = 0;
    animStatus = chara->model_0.anim_4.status_0;
    distance0 = sharedData_800E21D0_0_s01.distance_150;
    angle0 = sharedData_800E21D0_0_s01.angle_154;
    flag2 = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2 & 1;
    if (chara->properties_E4.unk0.field_E8_4)
    {
        angleAdd = Q12(0.1f);
    }
    temp_s3 = sharedFunc_800DC50C_2_s00(chara);
    var_s5 = 0;
    switch (chara->model_0.stateStep_3)
    {
        case 0:
            switch3 = 1;
            chara->properties_E4.unk0.properties_120.val32 = Q12(2.0f);
            chara->flags_3E |= 4;
            /* fallthrough */
        case 1:
            sharedFunc_800D529C_0_s01(chara, distance0 / 2, angle0);
            if (func_80080514() < ((angleAdd * 2) + FP_ANGLE(72.0f)))
            {
                chara->model_0.stateStep_3 = 2;
            }
            else
            {
                chara->model_0.stateStep_3 = 3;
            }
        default:
            break;
        case 2:
            var_s5 = 1;
            if (!temp_s3)
            {
                if (chara->properties_E4.unk0.properties_120.val32 != 0)
                {
                    if (Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8) < Q12(1.0f))
                    {
                        chara->model_0.stateStep_3 = 1;
                    }
                }
                else
                {
                    chara->model_0.stateStep_3 = 0;
                }
            }
            else
            {
                chara->model_0.stateStep_3 = 4;
            }
            break;
        case 3:
            sharedFunc_800D529C_0_s01(chara, distance0 / 2, angle0);
            if (temp_s3)
            {
                chara->model_0.stateStep_3 = 4;
            }
            else if (chara->properties_E4.unk0.properties_120.val32 == 0)
            {
                chara->model_0.stateStep_3 = 0;
            }
            else if (FP_ANGLE_NORM_S(angle0 - chara->rotation_24.vy) >= FP_ANGLE(-10.0f) &&
                     FP_ANGLE_NORM_S(angle0 - chara->rotation_24.vy) < FP_ANGLE(10.0f))
            {
                var_s5 = 2;
            }
            break;
        case 4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switch3 = 2;
                chara->model_0.anim_4.status_0 = 0x36;
                chara->model_0.stateStep_3 = 5;
            }
            break;
        case 5:
            switch3 = 2;
            break;
    }
    if (var_s5 == 1)
    {
        sharedFunc_800D57C8_0_s01(chara);
    }
    else
    {
        sharedFunc_800D598C_0_s01(chara);
    }
    dmgType = Chara_DamageTake(chara, Q12(1.0f));
    switch (dmgType)
    {
        case 0:     
            switch (switch3)
            {
                case 0:
                    if (flag2 == 0)
                    {
                        chara->model_0.state_2 = 0x15;
                        chara->model_0.stateStep_3 = 0;
                        return;
                    }
                default:
                    return;
                case 2:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        chara->model_0.state_2 = 8;
                        chara->model_0.stateStep_3 = 0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(chara))
                    {
                        chara->model_0.anim_4.status_0 = 0x2E;
                    }
                    break;
                case 1:
                    angle1 = sharedFunc_800DC894_2_s00(chara, distance0);
                    angle2 = sharedFunc_800DC6E4_2_s00(chara, distance0);
                    if (func_80080514() < angle1)
                    {
                        if (chara->properties_E4.unk0.field_E8_0 == 3)
                        {
                            sharedFunc_800DD13C_2_s00(chara, chara->field_40 + 1, Q12(0.6f));
                        }
                        chara->model_0.state_2 = 0x17;
                        chara->model_0.stateStep_3 = 0;
                        chara->properties_E4.player.flags_11C |= 0x10;
                    }
                    else if (func_80080514() < angle2)
                    {
                        chara->model_0.state_2 = 0x1B;
                        chara->model_0.stateStep_3 = 0;
                        chara->properties_E4.player.flags_11C |= 0x10;
                    }
                    break;
            }
            break;
        case 1:
            chara->model_0.state_2 = 0x1D;
            chara->model_0.stateStep_3 = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;
        case 2:
            chara->model_0.state_2 = 0x1E;
            chara->model_0.stateStep_3 = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;
        case 3:
        case 4:
            chara->model_0.state_2 = 0x20;
            chara->model_0.stateStep_3 = 0;
            if (chara->health_B0 <= 0)
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
        }
}

#include "maps/shared/sharedFunc_800D7D0C_2_s00.h" // 0x800D7D0C

#include "maps/shared/sharedFunc_800D80EC_2_s00.h" // 0x800D80EC

#include "maps/shared/sharedFunc_800D83F8_2_s00.h" // 0x800D83F8

#include "maps/shared/sharedFunc_800D8618_2_s00.h" // 0x800D8618

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D8888);

#include "maps/shared/sharedFunc_800D8C34_2_s00.h" // 0x800D8C34

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D8D44);

#include "maps/shared/sharedFunc_800D91A0_2_s00.h" // 0x800D91A0

#include "maps/shared/sharedFunc_800D92B4_2_s00.h" // 0x800D92B4

#include "maps/shared/sharedFunc_800D93E8_2_s00.h" // 0x800D93E8

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D94EC);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D98DC);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800D9C60);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DA0D4);

#include "maps/shared/sharedFunc_800DA598_2_s00.h" // 0x800DA598

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DA900);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DACA8);

#include "maps/shared/sharedFunc_800DB038_2_s00.h" // 0x800DB038

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DB220);

#include "maps/shared/sharedFunc_800DB54C_2_s00.h" // 0x800DB54C

#include "maps/shared/sharedFunc_800DB8AC_2_s00.h" // 0x800DB8AC

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DB9B8);

#include "maps/shared/sharedFunc_800DBDEC_2_s00.h" // 0x800DBDEC

void func_800DBEEC(void) {}

void func_800DBEF4(void) {}

void func_800DBEFC(void) {}

void func_800DBF04(void) {}

void func_800DBF0C(void) {}

void func_800DBF14(void) {}

#include "maps/shared/sharedFunc_800D4A80_0_s01.h" // 0x800DBF1C

#include "maps/shared/sharedFunc_800DBF88_2_s00.h" // 0x800DBF88

#include "maps/shared/sharedFunc_800DC0A8_2_s00.h" // 0x800DC0A8

#include "maps/shared/sharedFunc_800DC0E4_2_s00.h" // 0x800DC0E4

#include "maps/shared/sharedFunc_800DC200_2_s00.h" // 0x800DC200

#include "maps/shared/sharedFunc_800DC30C_2_s00.h" // 0x800DC30C

#include "maps/shared/sharedFunc_800DC3BC_2_s00.h" // 0x800DC3BC

#include "maps/shared/sharedFunc_800DC438_2_s00.h" // 0x800DC438

#include "maps/shared/sharedFunc_800DC50C_2_s00.h" // 0x800DC50C

#include "maps/shared/sharedFunc_800DC598_2_s00.h" // 0x800DC598

#include "maps/shared/sharedFunc_800DC67C_2_s00.h" // 0x800DC67C

#include "maps/shared/sharedFunc_800DC6E4_2_s00.h" // 0x800DC6E4

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800DC894_2_s00); // 0x800DC894

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800DC98C_2_s00); // 0x800DC98C

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D4E84_0_s01); // 0x800DCD24

#include "maps/shared/sharedFunc_800D5274_0_s01.h" // 0x800DD114

#include "maps/shared/sharedFunc_800DD13C_2_s00.h" // 0x800DD13C

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800DD2C4_2_s00); // 0x800DD2C4

#include "maps/shared/sharedFunc_800DD4A4_2_s00.h" // 0x800DD4A4

#include "maps/shared/sharedFunc_800DD4EC_2_s00.h" // 0x800DD4EC

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DD534);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DD588);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DD834);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DDA80);

#include "maps/shared/sharedFunc_800DDE14_2_s00.h" // 0x800DDE14

#include "maps/shared/sharedFunc_800DDF74_2_s00.h" // 0x800DDF74

#include "maps/shared/sharedFunc_800DE034_2_s00.h" // 0x800DE034

#include "maps/shared/sharedFunc_800DE11C_2_s00.h" // 0x800DE11C

#include "maps/shared/sharedFunc_800DE1F8_2_s00.h" // 0x800DE1F8

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800DE250_2_s00); // 0x800DE250

#include "maps/shared/sharedFunc_800DE578_2_s00.h" // 0x800DE578

#include "maps/shared/sharedFunc_800D529C_0_s01.h" // 0x800DE598

#include "maps/shared/sharedFunc_800DE6A8_2_s00.h" // 0x800DE6A8

#include "maps/shared/sharedFunc_800DE7E0_2_s00.h" // 0x800DE7E0

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800DE940_2_s00); // 0x800DE940

#include "maps/shared/sharedFunc_800DEBCC_2_s00.h" // 0x800DEBCC

#include "maps/shared/sharedFunc_800DEC64_2_s00.h" // 0x800DEC64

#include "maps/shared/sharedFunc_800DEC84_2_s00.h" // 0x800DEC84

#include "maps/shared/sharedFunc_800DECA4_2_s00.h" // 0x800DECA4

#include "maps/shared/sharedFunc_800DECC4_2_s00.h" // 0x800DECC4

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800DEE24_2_s00); // 0x800DEE24

#include "maps/shared/sharedFunc_800DF22C_2_s00.h" // 0x800DF22C

#include "maps/shared/sharedFunc_800DF24C_2_s00.h" // 0x800DF24C

#include "maps/shared/sharedFunc_800D5638_0_s01.h" // 0x800DF26C

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800DF2D0_2_s00); // 0x800DF2D0

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800DF358_2_s00); // 0x800DF358

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800DF448_2_s00);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800DF60C);

#include "maps/shared/sharedFunc_800DF710_2_s00.h" // 0x800DF710

#include "maps/shared/sharedFunc_800DF80C_2_s00.h" // 0x800DF80C

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800DF8A0_2_s00); // 0x800DF8A0

#include "maps/shared/sharedFunc_800D569C_0_s01.h" // 0x800DF950

#include "maps/shared/sharedFunc_800D57C8_0_s01.h" // 0x800DFA7C

#include "maps/shared/sharedFunc_800D598C_0_s01.h" // 0x800DFC40

#include "maps/shared/sharedFunc_800D5B10_0_s01.h" // 0x800DFDC4

#include "maps/shared/sharedFunc_800D5C90_0_s01.h" // 0x800DFF44

#include "maps/shared/sharedFunc_800D5D80_0_s01.h" // 0x800E0034

#include "maps/shared/sharedFunc_800D5E14_0_s01.h" // 0x800E00C8

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E012C_2_s00); // 0x800E012C

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E021C_2_s00); // 0x800E021C

#include "maps/shared/sharedFunc_800E041C_2_s00.h" // 0x800E041C

#include "maps/shared/sharedFunc_800E04B0_2_s00.h" // 0x800E04B0

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E0514_2_s00); // 0x800E0514

#include "maps/shared/sharedFunc_800D5E78_0_s01.h" // 0x800E0610

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E0698_2_s00); // 0x800E0698

#include "maps/shared/sharedFunc_800D62D8_0_s01.h" // 0x800E0A70

#include "maps/shared/sharedFunc_800D633C_0_s01.h" // 0x800E0AD4

#include "maps/shared/sharedFunc_800D63A4_0_s01.h" // 0x800E0B3C

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D6600_0_s01); // 0x800E0D98

#include "maps/shared/sharedFunc_800D6A60_0_s01.h" // 0x800E11F8

#include "maps/shared/sharedFunc_800D6C7C_0_s01.h" // 0x800E1414

#include "maps/shared/sharedFunc_800D6EC4_0_s01.h"

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D7120_0_s01); // 0x800E18B8

#include "maps/shared/sharedFunc_800D71F0_0_s01.h" // 0x800E1988

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D72E8_0_s01); // 0x800D72E8

#include "maps/shared/sharedFunc_800D7440_0_s01.h" // 0x800E1BD8

#include "maps/shared/sharedFunc_800D7560_0_s01.h" // 0x800E1CF8

#include "maps/shared/sharedFunc_800D76A0_0_s01.h" // 0x800E1E38

#include "maps/shared/sharedFunc_800D7714_0_s01.h" // 0x800E1EAC

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D77D0_0_s01); // 0x800E1F68

#include "maps/shared/sharedFunc_800D7AB0_0_s01.h" // 0x800E2248

#include "maps/shared/sharedFunc_800D7B14_0_s01.h" // 0x800E22AC

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D7EBC_0_s01); // 0x800E2620

#include "maps/shared/sharedFunc_800D81B0_0_s01.h" // 0x800E2914

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D81D0_0_s01); // 0x800E2934

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D8244_0_s01); // 0x800E29A8

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800D82B8_0_s01); // 0x800E2A1C

#include "maps/shared/sharedFunc_800D8714_0_s01.h" // 0x800E2E78

#include "maps/shared/sharedFunc_800D87FC_0_s01.h" // 0x800E2F60

#include "maps/shared/sharedFunc_800D8804_0_s01.h" // 0x800E2F68

#include "maps/shared/Ai_Groaner_Update.h" // 0x800E2F78

#include "maps/shared/Ai_Groaner_Init.h" // 0x800E3074 - `map2_s00` includes extra block at end of function compared to other maps.

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E33DC_2_s00); // 0x800E33DC

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E384C_2_s00); // 0x800E384C - `map2_s00` version differs to the 4 other maps which share `Ai_Groaner_Update`.

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E39D8);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E3E94);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E4830);

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E4E84);

#include "maps/shared/sharedFunc_800E554C_2_s00.h" // 0x800E554C

#include "maps/shared/sharedFunc_800E55B0_2_s00.h" // 0x800E55B0

#include "maps/shared/sharedFunc_800E5930_2_s00.h" // 0x800E5930

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E5AA4_2_s00); // 0x800E5AA4

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E5EC4_2_s00); // 0x800E5EC4

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E6338_2_s00); // 0x800E6338

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", sharedFunc_800E71E8_2_s00); // 0x800E71E8

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800E76B8

#include "maps/shared/Map_RoomIdxGet.h" // 0x800E76C8

#include "maps/shared/sharedFunc_800E7914_2_s00.h" // 0x800E7914

void func_800E7A1C(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800E7A24

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800E7AB8

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tThere_is_a_ ~C2 Steel_pipe ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tWhere_could_Cheryl_have_gone? ",
    "\tI_guess_I'll_check ~N\n\tthat_alley_again. ~E ",
    "~C3\tTo_school ~E ",
    "~J1(2.5)\n\tIsn't_this ~N\n\tCheryl's_sketchbook? ",
    "~J1(3.8)\n\tHmm... ~N\n\tShe's_at_the_school... ~E ",
    "\tSketchbook_cover. ~N\n\tThis_picture..._it's_me. ",
    "\tThe_first_picture_that_Cheryl ~N\n\tdrew_in_the_sketchbook_that_I ~N\n\tgave_on_her_5th_birthday. ~E ",
    "~M ~C3\tDoghouse ~N\n\t\tLevin_st. ~E ",
    "\tNothing_unusual. ~E ",
    "\tProbably_a_doghouse, ~N\n\tthough_I'm_not_sure ~N\n\tsince_there's_no_dog_around. ",
    "\tNothing_in_particular_around. ~E ",
    "\t~C2 House_key ~C7 _was_hidden ~N\n\tin_the_dog_house._Take_it? ~S4 ",
    "\tThere_is_a_ ~C2 Key_of_[Lion] ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Key_of_[Woodman] ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Key_of_[Scarecrow] ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tUsed_the_ ~C2 House_key ~C7 . ~E ",
    "\tUsed_the_ ~C2 Key_of_[Lion] ~C7 . ~E ",
    "\tUsed_the_ ~C2 Key_of_[Woodman] ~C7 . ~E ",
    "\tUsed_the_ ~C2 Key_of_[Scarecrow] ~C7 . ~E ",
    "~J0(20)\tWhat? ~E ",
    "\tIt's_getting_dark_again? ",
    "\tWhat's_going_on!? ~E ",
    "\tA_dog's_head... ~E ",
    "\tUsed_the_ ~C2 K._Gordon_key ~C7 . ~E ",
    "~C3\tMidwich_Elementary_School ~E ",
    "\tNo_reason_to_search ~N\n\tthe_school_anymore. ~E ",
    "~C3\tOrridge_Bridge_Control_Room ~E ",
    "\tThere's_a_keyhole ~N\n\ton_the_control_panel. ~E ",
    "\tThe_machinery_is_running. ~N\n\tDo_you_want_to_press_the_switch? ~S4 ",
    "\tThe_street_is_blocked. ~N\n\tCan't_get_out_of_town_through_here. ~E ",
    "\tMy_car... ~N\n\ttoo_banged_up_to_drive. ",
    "\tWhere's_Cheryl? ~N\n\tHope_she's_safe. ~E ",
    "~C3\tOrridge_Bridge_Control_Room ~E ",
    "~C3\tReservoir. ~N\n\t\tAuthorized_Personnel_only. ~E ",
    "\tHmm..._the_lock_is_worn_out. ",
    "\tI_may_be_able_to_break_it ~N\n\tif_I_hit_it_hard. ~E ",
    "\tSomething_is_written_on_the_map ~N\n\thanging_on_the_wall. ",
    "\tCopied_it_to_the_map. ~E ",
    "\tSomething_is_written_on_the_map ~N\n\thanging_on_the_wall. ~E ",
    " ",
    "\tThere_are_three_locks. ~E ",
    "\tThere_are_two_locks. ~E ",
    "\tThere_is_one_lock. ~E ",
    "\tIt's_unlocked. ~E ",
    "~H\tThere_is_a_ ~C5 Shopping_district_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tNothing_special. ~E ",
    "\tThe_drawbridge_is_operating. ~E ",
    "\tThe_drawbridge_is_stopped. ~E ",
    "\tThere's_a_TV_set. ~N\n\tThe_power_must_be_out. ~N\n\tIt_doesn't_work. ~E ",
    "\tNothing_useful. ~E ",
    "\tNothing_special. ~E ",
    "\tThe_refrigerator_is_empty. ~E ",
    "\tThe_garage_door_is_smeared ~N\n\twith_blood. ~E ",
    "~C3\tK._Gordon ~E ",
    "~C3\tBalkan_Church ~E ",
    "\tThere_is_a_ ~C2 Rock_drill ~C7 . ",
    "\tThere_is_no_gasoline. ~N\n\tCan't_use_it. ~E ",
    "\tThere_is_a_ ~C2 Rock_drill ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Chainsaw ~C7 . ",
    "\tThere_is_no_gasoline. ~N\n\tCan't_use_it. ~E ",
    "\tThere_is_a_ ~C2 Chainsaw ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tUsed_the_gasoline. ~E ",
    "\tThis_must_be_that_water_works ~N\n\tLisa_was_talking_about. ~E "
};

void func_800E7B74(void) // 0x800E7B74
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 139:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M2S00_FirstAidKit0;
            break;

        case 140:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets0;
            break;

        case 141:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets1;
            break;

        case 142:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink0;
            break;

        case 143:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets2;
            break;

        case 144:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M2S00_ShotgunShells0;
            break;

        case 145:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink1;
            break;

        case 146:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets3;
            break;

        case 147:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets4;
            break;

        case 148:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets5;
            break;

        case 149:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets6;
            break;

        case 150:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets7;
            break;

        case 151:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets8;
            break;

        case 152:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink2;
            break;

        case 153:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink3;
            break;
        case 154:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink4;
            break;

        case 155:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets9;
            break;

        case 156:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink5;
            break;

        case 157:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets10;
            break;

        case 158:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink6;
            break;

        case 159:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink7;
            break;

        case 160:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink8;
            break;

        case 161:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink9;
            break;

        case 162:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink10;
            break;

        case 163:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S00_HealthDrink11;
            break;

        case 164:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M2S00_ShotgunShells1;
            break;

        case 165:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M2S00_FirstAidKit1;
            break;

        case 166:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets11;
            break;

        case 167:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets12;
            break;

        case 168:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets13;
            break;

        case 169:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M2S00_HandgunBullets14;
            break;

        case 170:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M2S00_FirstAidKit2;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800E7D54(void) // 0x800E7D54
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
    {
        // Breaks if there are any characters with IDs in range `[Chara_Harry, Chara_MonsterCybil]` with health above `Q12(0.0f)`.
        if (g_SysWork.npcs_1A0[i].model_0.charaId_0 >= Chara_Harry &&
            g_SysWork.npcs_1A0[i].model_0.charaId_0 <= Chara_MonsterCybil &&
            g_SysWork.npcs_1A0[i].health_B0 > Q12(0.0f))
        {
            break;
        }
    }

    if (i != ARRAY_SIZE(g_SysWork.npcs_1A0))
    {
        g_DeltaTime0 = Q12(0.0f);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            MapMsg_DisplayAndHandleSelection(false, 46, 0, 0, 0, false);
            break;

        case 2:
            Event_ItemTake(InventoryItemId_HealthDrink, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupHealthDrink, 6);
            break;
    }
}

void MapEvent_AtWaterWorks(void) // 0x800E7E60
{
    s32 sysState0;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            g_SysWork.player_4C.chara_0.position_18.vx = Q12(-255.78f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(-107.46f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(-45.0f);

            ScreenFade_ResetTimestep();
            func_800867B4(0, 1);
            func_800EB824(1);
            SysWork_StateStepIncrement(0);

        case 1:
        case 2:
        case 3:
            func_800692A4(0, 120, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 0, 120, Q12(0.5f));
            func_80067914(1, 0, 120, Q12(0.5f));

            sysState0 = g_SysWork.sysStateStep_C[0];
            switch (sysState0)
            {
                case 2:
                    SysWork_StateStepIncrementDelayed(Q12(3.5f), false);

                    if (g_SysWork.sysStateStep_C[0] == sysState0 &&
                        (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                          g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)))
                    {
                        SysWork_StateStepSet(0, 3);
                    }
                    break;

                case 3:
                    SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.0f), false);
                    break;

                case 1:
                    SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(1.0f), false);
                    break;
            }
            break;

        case 4:
            g_SysWork.field_30 = 20;

            func_800867B4(2, 0);
            Camera_PositionSet(NULL, Q12(-254.15f), Q12(-1.95f), Q12(-109.3f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-257.0398f), Q12(-1.94f), Q12(-106.54f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(1.0f), false);
            break;

        case 6:
            MapMsg_DisplayAndHandleSelection(false, 78, 0, 0, 0, false); // "This must be the water works."
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_M2S00_WaterWorksCutscene);

            g_SysWork.flags_22A4 &= ~SysFlag2_4;
            break;
    }
}

void func_800E816C(void) // 0x800E816C
{
    Event_ItemTake(InventoryItemId_RockDrill, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupRockDrill, 73);
}

void func_800E8198(void) // 0x800E8198
{
    Event_ItemTake(InventoryItemId_Chainsaw, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupChainsaw, 76);
}

void MapEvent_MapTake(void) // 0x800E81C4
{
    Event_MapTake(2, EventFlag_M2S00_PickupMap, 60);
}

void MapEvent_SteelPipeTake(void) // 0x800E81EC
{
    typedef enum _EventState
    {
        EventState_TakeSteelPipe     = 5,
        EventState_DontTakeSteelPipe = 6
    } e_EventState;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_80086470(0u, InventoryItemId_SteelPipe, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.player_4C.chara_0, 59);
            break;

        case 3:
            func_80086470(1, InventoryItemId_SteelPipe, 0, false);
            break;

        case 4:
            Savegame_EventFlagSet(EventFlag_M2S00_PickupSteelPipe);

            if (Gfx_PickupItemAnimate(InventoryItemId_SteelPipe))
            {
                MapMsg_DisplayAndHandleSelection(true, 15, EventState_TakeSteelPipe, EventState_DontTakeSteelPipe, 0, false);
            }
            break;

        case EventState_TakeSteelPipe:
            func_80086470(3, InventoryItemId_SteelPipe, 1, false);
            SysWork_StateStepSet(0, 7);
            break;

        case EventState_DontTakeSteelPipe:
            Savegame_EventFlagClear(EventFlag_M2S00_PickupSteelPipe);
            SysWork_StateStepIncrement(0);

        case 7:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void MapEvent_CutsceneExitCafe(void) // 0x800E83C0
{
    s32 zoomX;
    s32 zoomZ;
    s32 zoomHuh;
    s16 curve;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (g_SysWork.sysStateStep_C[0] == 2)
        {
            SysWork_StateStepSet(0, 13);
        }
        else
        {
            if (!D_800F228E && g_SysWork.sysStateStep_C[0] > 5 && g_SysWork.sysStateStep_C[0] < 11)
            {
                SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
                D_800F228E = 1;
            }
        }
    }

    if (D_800F228E)
    {
        if (ScreenFade_IsFinished())
        {
            D_800F228E = 0;
            SysWork_StateStepSet(0, 12);
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            g_SysWork.field_30 = 20;
            D_800F228C = 0;
            g_Gfx_Map2dMarkingFade = 0;

            Savegame_MapMarkingSet(MapMarkFlag_OldTown_CofeArrowOnly);
            Savegame_MapMarkingSet(MapMarkFlag_OldTown_CofeSignOnly);

            D_800F228E = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            Camera_PositionSet(NULL, Q12(15.54f), Q12(-1.5f), Q12(55.64f), 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, Q12(19.42f), Q12(-1.75f), Q12(56.6f), 0, 0, 0, 0, true);
            SysWork_StateStepIncrement(0);

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 16, 0, 0, 0, false); // "Where could Cheryl have gone?"
            break;

        case 3:
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + D_800A99B5);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 5:
            func_800867B4(0, 1);
            SysWork_StateStepIncrement(0);

        case 6:
            func_800692A4(0, 0, Q12(1.0f));
            func_80068E0C(1, 1, 0, 0, 0, 0, Q12(1.0f));
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 7:
            func_800692A4(0, 0, Q12(1.0f));
            func_80068E0C(1, 1, 0, 0, 0, 0, Q12(1.0f));

            D_800F228C += 0x20;

            func_80088370(D_800F228C, -0xA0, -0xE0, 0x13F, 0x1BF, -0x58, -0xC0, 0x9F, 0xDF);

            if (D_800F228C == Q12(1.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 8:
            // Decrement zoom counter.
            D_800F228C -= 0x40;

            func_800692A4(0x48 - FP_MULTIPLY_PRECISE(D_800F228C, 0x48, Q12_SHIFT),
                          0x10 - FP_MULTIPLY_PRECISE(D_800F228C, 0x10, Q12_SHIFT),
                          (D_800F228C >> 1) + Q12(0.5f));

            func_80068E0C(1, 1, 0, 0,
                          0x48 - FP_MULTIPLY_PRECISE(D_800F228C, 0x48, Q12_SHIFT),
                          0x10 - FP_MULTIPLY_PRECISE(D_800F228C, 0x10, Q12_SHIFT),
                          (D_800F228C >> 1) + Q12(0.5f));

            curve = (FP_TO(D_800F228C, 12) / (D_800F228C + Q12(1.0f))) * -1;

            func_80088370(curve, -0xA0, -0xE0, 0x13F, 0x1BF, -0x10, -0xA0, 0, 0);

            if (D_800F228C == 0)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 9:
            func_800692A4(0x48, 0x10, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 72, 0x10, Q12(0.5f));
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 10:
            func_800692A4(0x48, 0x10, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 72, 0x10, Q12(0.5f));
            func_80068E0C(2, 1, 0x36A, g_Gfx_Map2dMarkingFade, 0x48, 0x10, Q12(0.5f));

            // Fade in map marking to half opacity.
            g_Gfx_Map2dMarkingFade++;
            if (g_Gfx_Map2dMarkingFade >= 128)
            {
                if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                     g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
                {
                    SysWork_StateStepIncrement(0);
                }

                SysWork_StateStepIncrementDelayed(Q12(1.5f), false);

                if (g_SysWork.sysStateStep_C[0] > 11)
                {
                    g_SysWork.sysStateStep_C[0] = 11;
                }

                // Clamp map marking fade.
                g_Gfx_Map2dMarkingFade = 128;
            }
            break;

        case 11:
            func_800692A4(0x48, 0x10, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 0x48, 0x10, Q12(0.5f));
            func_80068E0C(2, 1, 0x36A, 128, 0x48, 0x10, Q12(0.5f));
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 12:
            func_800867B4(2, 0);
            D_800F228E = 0;
            SysWork_StateStepIncrement(0);

        case 13:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 14:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_MapMarkingSet(MapMarkFlag_OldTown_CherylArrowAndSign);
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            g_SysWork.flags_22A4 &= ~SysFlag2_4;

            func_8003A16C();
            break;
    }
}

void MapEvent_CherylsSketchbook(void) // 0x800E8C0C
{
    s16 curve;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (!D_800F2295)
        {
            if (g_SysWork.sysStateStep_C[0] > 1 && g_SysWork.sysStateStep_C[0] < 10)
            {
                SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
                D_800F2295 = 1;
            }
            else if (g_SysWork.sysStateStep_C[0] > 10 && g_SysWork.sysStateStep_C[0] < 16)
            {
                SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
                D_800F2295 = 2;
            }
        }
    }

    if (D_800F2295)
    {
        if (ScreenFade_IsFinished())
        {
            if (D_800F2295 == 1)
            {
                SysWork_StateStepSet(0, 21);
            }
            else
            {
                SysWork_StateStepSet(0, 22);
            }

            D_800F2295 = 0;
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            Savegame_MapMarkingSet(MapMarkFlag_11);
            func_800862F8(0, FILE_TIM_TOSCHOOL_TIM, false);

            g_MapMsgSoundIdx = 0;
            D_800F2298 = 0;
            D_800F229C = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.player_4C.chara_0, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 4:
            func_800862F8(1, 0, false);
            break;

        case 5:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 6:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 18, 0, 0, 0, false); // "To school."
            break;

        case 7:
            g_BackgroundColor = 48;

            func_800862F8(2, 0, false);
            Map_MessageWithAudio(19, &g_MapMsgSoundIdx, &g_MapMsgSounds); // "Isn't this Cheryl's sketchbook?"
            break;

        case 8:
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + D_800A99B5);
            SysWork_StateStepIncrement(0);

        case 9:
            g_BackgroundColor = 48;

            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 10:
            func_800867B4(0, 1);
            Savegame_EventFlagSet(EventFlag_147);
            SysWork_StateStepIncrement(0);

        case 11:
            func_800692A4(0, 0, Q12(1.0f));
            func_80068E0C(1, 1, 0, 0, 0, 0, Q12(1.0f));
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 12:
            func_800692A4(0, 0, Q12(1.0f));
            func_80068E0C(1, 1, 0, 0, 0, 0, Q12(1.0f));
            D_800F229C += 0x20;
            func_80088370(D_800F229C, -0xA0, -0xE0, 0x13F, 0x1BF, -0xA0, 8, 0x9F, 0xDF);

            if (D_800F229C == Q12(1.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 13:
            // Decrement zoom counter.
            D_800F229C -= 0x40;

            func_800692A4(0,
                          0x74 - FP_MULTIPLY_PRECISE(D_800F229C, 0x74, 12),
                          (D_800F229C >> 1) + Q12(0.5f));

            func_80068E0C(1, 1, 0, 0, 0,
                          0x74 - FP_MULTIPLY_PRECISE(D_800F229C, 0x74, 12),
                          (D_800F229C >> 1) + Q12(0.5f));

            curve = (FP_TO(D_800F229C, 12) / (D_800F229C + Q12(1.0f))) * -1;

            func_80088370(curve, -0xA0, -0xE0, 0x13F, 0x1BF, -0xA0, 0xF0, 0, 0);

            if (D_800F229C == 0)
            {
                SysWork_StateStepIncrement(0);
                break;
            }
            break;

        case 14:
            func_800692A4(0, 0x74, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 0, 0x74, Q12(0.5f));
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);

            break;
        case 15:
            func_800692A4(0, 0x74, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 0, 0x74, Q12(0.5f));
            func_80068E0C(2, 1, 0x3A2, D_800F2298, 0, 0x74, Q12(0.5f));

            D_800F2298++;
            if (D_800F2298 >= 0x80)
            {
                if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
                {
                    SysWork_StateStepIncrement(0);
                }

                SysWork_StateStepIncrementDelayed(Q12(1.5f), false);

                if (g_SysWork.sysStateStep_C[0] > 16)
                {
                    g_SysWork.sysStateStep_C[0] = 16;
                }

                D_800F2298 = 0x80;
            }
            break;

        case 16:
            func_800692A4(0, 0x74, Q12(0.5f));
            func_80068E0C(1, 1, 0, 0, 0, 0x74, Q12(0.5f));
            func_80068E0C(2, 1, 0x3A2, 128, 0, 0x74, Q12(0.5f));
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 17:
            func_800867B4(2, 0);
            Savegame_MapMarkingSet(MapMarkFlag_OldTown_SchoolCircle);

            D_800F2295 = 0;

            SysWork_StateStepIncrement(0);

        case 18:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 19:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        case 22:
            func_800867B4(2, 0);

        case 21:
            Savegame_EventFlagSet(EventFlag_147);
            Savegame_MapMarkingSet(MapMarkFlag_OldTown_SchoolCircle);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            func_80086470(3, InventoryItemId_NoteToSchool, 1, false);
            func_8003A16C();
            break;
    }
}

void func_800E9470(void) // 0x800E9470
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_SKETCHBK_TIM, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.player_4C.chara_0, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 4:
            func_800862F8(1, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case 5:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 6:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            MapMsg_DisplayAndHandleSelection(false, 21, 0, 0, 0, false);
            break;

        case 7:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 8:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void MapEvent_DoghouseNote(void) // 0x800E95F8
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_STKENNEL_TIM, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.player_4C.chara_0, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 4:
            func_800862F8(1, 0, false);
            break;

        case 5:
            func_800862F8(2, 0, false);
            Savegame_EventFlagSet(EventFlag_M2S00_DogHouseNoteFound);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 6:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 23, 0, 0, 0, false); // "Doghouse Levin St."
            break;

        case 7:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 9:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            func_80086470(3, InventoryItemId_NoteDoghouse, 1, false);
            break;
    }
}

void MapEvent_DoghouseKeyTake(void) // 0x800E97E4
{
    typedef enum _EventState
    {
        EventState_TakeKey     = 8,
        EventState_DontTakeKey = 9
    } e_EventState;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_INKENNEL_TIM, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.player_4C.chara_0, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 4:
            func_800862F8(1, 0, false);
            break;

        case 5:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 6:
            SysWork_StateStepIncrement(0);

        case 7:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(true, 27, EventState_TakeKey, EventState_DontTakeKey, 0, false); // "House Key in doghouse. Take it?"
            break;

        case EventState_TakeKey:
            func_80086470(3, InventoryItemId_HouseKey, 1, false);
            Savegame_EventFlagSet(EventFlag_M2S00_PickupDogHouseKey);
            Player_ItemRemove(InventoryItemId_NoteDoghouse, 1);
            SysWork_StateStepIncrement(0);

        case EventState_DontTakeKey:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 10:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 11:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
        }
}

void func_800E9A0C(void) // 0x800E9A0C
{
    Event_ItemTake(InventoryItemId_KeyOfLion, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupKeyOfLion, 28);

    if (Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfLion))
    {
        if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_FineyStRightKeyArrow))
        {
            Savegame_MapMarkingSet(MapMarkFlag_53);
        }
    }
}

void func_800E9A74(void) // 0x800E9A74
{
    typedef enum _EventState
    {
        EventState_TakeKey     = 6,
        EventState_DontTakeKey = 7
    } e_EventState;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_80086470(0, InventoryItemId_KeyOfWoodman, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 59, false);
            SysWork_StateStepIncrement(0);

        case 3:
            func_80086470(1, InventoryItemId_KeyOfWoodman, 0, false);
            break;

        case 4:
            func_80085EB8(1, &g_SysWork.player_4C.chara_0, 0, false);
            break;

        case 5:
            if (Gfx_PickupItemAnimate(InventoryItemId_KeyOfWoodman))
            {
                MapMsg_DisplayAndHandleSelection(true, 29, EventState_TakeKey, EventState_DontTakeKey, 0, false); // "Key of Woodman. Take it?"
            }

            Savegame_EventFlagSet(EventFlag_M2S00_PickupKeyOfWoodman);
            break;

        case EventState_TakeKey:
            func_80086470(3, InventoryItemId_KeyOfWoodman, 1, false);

            if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_DogYardKeyLine))
            {
                Savegame_MapMarkingSet(MapMarkFlag_55);
            }

            SysWork_StateStepSet(0, 8);
            break;

        case EventState_DontTakeKey:
            Savegame_EventFlagClear(EventFlag_M2S00_PickupKeyOfWoodman);
            SysWork_StateStepIncrement(0);

        case 8:
            func_80086C58(&g_SysWork.player_4C.chara_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
        }
}

void func_800E9CB4(void) // 0x800E9CB4
{
    Event_ItemTake(InventoryItemId_KeyOfScarecrow, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S00_PickupKeyOfScarecrow, 30);

    if (Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfScarecrow))
    {
        if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_EllroyStKeyCircle))
        {
            Savegame_MapMarkingSet(MapMarkFlag_57);
        }
    }
}

void MapEvent_HouseKeyUse(void) // 0x800E9D1C
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_HouseKey, 1);
    Map_MessageWithSfx(31, Sfx_UseKey, &sfxPos); // "Used the House Key."
    Savegame_MapMarkingSet(MapMarkFlag_OldTown_DoghouseDotOnly);
}

INCLUDE_ASM("asm/maps/map2_s00/nonmatchings/map2_s00", func_800E9DD8);

void MapEvent_DoorOfEclipseEnter(void) // 0x800EA444
{
    s32 tmp;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_8003ED74(1, 1);
            func_8003EF10(6, 6, PrimitiveType_S32, &D_800F1A24, 0, Q12(100.0f));

            g_SysWork.player_4C.chara_0.position_18.vx = Q12(147.7f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(376.5f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = Q12(-0.25f);
            g_SysWork.field_30 = 20;
            g_SysWork.flags_22A4 |= SysFlag2_3;

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            g_SysWork.field_28 += g_DeltaTime0;
            tmp = Q12(1.0f) - Math_Cos(g_SysWork.field_28/12);
            D_800F1A24 = FP_MULTIPLY_PRECISE(tmp, Q12(60.0f), Q12_SHIFT) + Q12(40.0f);

            if (g_SysWork.field_28 > Q12(1.5f) && g_SysWork.field_28 < Q12(4.5f))
            {
                MapMsg_DisplayAndHandleSelection(false, 35, 0, 0, 0, false); // "What? It's getting dark again?"
            }

            SysWork_StateStepIncrementDelayed(Q12(6.0f), false);
            break;

        case 2:
            D_800F1A24 = Q12(100.0f);

            Game_TurnFlashlightOff();
            SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 36, 0, 0, 0, false);
            break;

        case 4:
            func_8003ED74(6, 3);
            Game_TurnFlashlightOn();
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(1.2f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_159);

            vcReturnPreAutoCamWork(false);
            break;
    }
}

void func_800EA6E0(void) // 0x800EA6E0
{
    // TODO: Probably inaccurate. Need to figure out what the unknown functions are doing.
    typedef enum _EventState
    {
        EventState_Setup       = 0,
        EventState_FadeOutGame = 1,
        EventState_Load        = 2, // TODO: Something else?
        EventState_FadeInMap   = 3,
        EventState_Msg         = 4,
        EventState_FadeOutMap  = 5,
        EventState_Finish      = 6
    } e_EventState;

    g_BackgroundColor = 72;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case EventState_Setup:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_KEYMAP_TIM, false);
            SysWork_StateStepIncrement(0);

        case EventState_FadeOutGame:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case EventState_Load:
            func_800862F8(1, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case EventState_FadeInMap:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case EventState_Msg:
            if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_FineyStRightKeyArrow))
            {
                MapMsg_DisplayAndHandleSelection(false, 54, 0, 0, 0, false); // "Something is written on the map on the wall.{E}"
            }
            else
            {
                MapMsg_DisplayAndHandleSelection(false, 52, 0, 0, 0, false); // "... Copied it to the map."
            }

            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            break;

        case EventState_FadeOutMap:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default: // `EventState_Finish`
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            Savegame_MapMarkingSet(MapMarkFlag_OldTown_FineyStRightKeyArrow);
            Savegame_MapMarkingSet(MapMarkFlag_OldTown_DogYardKeyLine);
            Savegame_MapMarkingSet(MapMarkFlag_OldTown_EllroyStKeyCircle);
            break;
        }
}

void MapEvent_KGordonKeyUse(void) // 0x800EA894
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_KGordonKey, 1);
    Map_MessageWithSfx(39, Sfx_UseKey, &sfxPos); // "Used the K. Gordon key."

    Savegame_EventFlagSet(EventFlag_M2S00_KGordonDoorOpen);
    Savegame_MapMarkingSet(MapMarkFlag_OldTown_KGordonArrowsOnly);
}

void func_800EA960(void) // 0x800EA960
{
    typedef enum _EventState
    {
        EventState_PressSwitch     = 5,
        EventState_DontPressSwitch = NO_VALUE
    } e_EventState;

    s32 vol;
    s32 balance;
    s16 time;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 3, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_8005DC1C(Sfx_Unk1481, &QVECTOR3(-41.576f, -3.619f, 345.992f), Q8_CLAMPED(0.5f), 0);
            Savegame_EventFlagSet(EventFlag_164);
            Sd_EngineCmd(Sfx_Unk1482);

            D_800F534C = NO_VALUE;

            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 4:
            g_SysWork.silentYesSelection_2350_4 = true;

            // "The machinery is running. Do you want to press the switch?"
            MapMsg_DisplayAndHandleSelection(true, 44, EventState_PressSwitch, EventState_DontPressSwitch, 0, false);
            break;

        case EventState_PressSwitch:
            func_8005DC1C(Sfx_Unk1483, &QVECTOR3(-41.576f, -3.619f, 345.992f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 6:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;
        case 7:
            Sd_EngineCmd(Sfx_Unk1484);
            D_800F534E = Q12(0.0f);
            SysWork_StateStepIncrement(0);

        case 8:
            D_800F534E += ((u16)g_DeltaTime0 * 4);
            if (D_800F534E > Q12(1.0f))
            {
                D_800F534E = Q12(1.0f);
            }

            balance = Sound_StereoBalanceGet(&QVECTOR3(-35.0f, 0.0f, 352.0f));
            if ((Q8_CLAMPED(1.0f) - (D_800F534E >> 4)) >= 0)
            {
                vol = ~(D_800F534E >> 4) & Q8_CLAMPED(1.0f);
            }
            else
            {
                vol = 0;
            }

            func_800463C0(Sfx_Unk1484, balance, vol, 0);

            D_800F5344.vz += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x88, Q12_SHIFT);
            if (D_800F5344.vz > 0)
            {
                D_800F5344.vz = 0;

                func_8004690C(Sfx_Unk1484);
                Sd_PlaySfx(Sfx_Unk1485, Sound_StereoBalanceGet(&QVECTOR3(-35.0f, 0.0f, 352.0f)), 0);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 9:
            Savegame_EventFlagSet(EventFlag_165);
            Savegame_EventFlagSet(EventFlag_166);

            if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_BotBridgeCross))
            {
                Savegame_MapMarkingSet(MapMarkFlag_OldTown_BotBridgeCorrection);
                Savegame_MapMarkingSet(MapMarkFlag_OldTown_BotBridgeArrow);
            }

            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            break;
    }

    if (Savegame_EventFlagGet(EventFlag_164))
    {
        if (g_SysWork.sysStateStep_C[0] > 4)
        {
            func_800894B8(0x90);
        }
        else
        {
            func_800894B8(0x70);
        }
    }
}

void func_800EAD2C(void) // 0x800EAD2C
{
    typedef enum _EventState
    {
        EventState_PressSwitch     = 3,
        EventState_DontPressSwitch = NO_VALUE
    } e_EventState;

    s32 vol;
    s32 balance;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            g_SysWork.silentYesSelection_2350_4 = true;

            // "The machinery is running. Do you want to press the switch?"
            MapMsg_DisplayAndHandleSelection(true, 44, EventState_PressSwitch, EventState_DontPressSwitch, 0, false);
            break;

        case EventState_PressSwitch:
            SysWork_StateStepIncrementAfterFade(0, true, 3, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            func_8005DC1C(Sfx_Unk1483, &QVECTOR3(-41.576f, -3.619f, 345.992f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 6:
            Sd_EngineCmd(Sfx_Unk1484);
            D_800F534E = Q12(0.0f);
            SysWork_StateStepIncrement(0);

        case 7:
            D_800F534E += g_DeltaTime0;
            if (D_800F534E > Q12(1.0f))
            {
                D_800F534E = Q12(1.0f);
            }

            balance = Sound_StereoBalanceGet(&QVECTOR3(-35.0f, 0.0f, 352.0f));
            if ((Q8_CLAMPED(1.0f) - (D_800F534E >> 4)) >= 0)
            {
                vol = ~(D_800F534E >> 4) & Q8_CLAMPED(1.0f);
            }
            else
            {
                vol = 0;
            }

            func_800463C0(Sfx_Unk1484, balance, vol, 0);

            D_800F5344.vz += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.1f / 3.0f), Q12_SHIFT);
            if (D_800F5344.vz > 0)
            {
                D_800F5344.vz = 0;
                func_8004690C(Sfx_Unk1484);
                Sd_PlaySfx(Sfx_Unk1485, Sound_StereoBalanceGet(&QVECTOR3(-35.0f, 0.0f, 352.0f)), 0);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 8:
            Savegame_EventFlagSet(EventFlag_165);
            Savegame_EventFlagSet(EventFlag_166);

            if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_BotBridgeCross))
            {
                Savegame_MapMarkingSet(MapMarkFlag_OldTown_BotBridgeCorrection);
                Savegame_MapMarkingSet(MapMarkFlag_OldTown_BotBridgeArrow);
            }

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    if (g_SysWork.sysStateStep_C[0] > 3)
    {
        func_800894B8(0x90);
    }
    else
    {
        func_800894B8(0x70);
    }
}

void func_800EB090(void) // 0x800EB090
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 61, 0, 0, 0, false); // "Nothing special."
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    func_800894B8(96);
}

void func_800EB174(void) // 0x800EB174
{
    VECTOR3 soundPos;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            soundPos.vx = MAP_POINTS[g_MapEventParam->field_5].positionX_0;
            soundPos.vy = Q12(-1.2f);
            soundPos.vz = MAP_POINTS[g_MapEventParam->field_5].positionZ_8;

            func_8005DC1C(Sfx_Unk1349, &soundPos, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, MapMsgIdx_DoorLocked, false, false, 0, false);
            break;

        case 4:
            Camera_PositionSet(NULL, Q12(-261.27f), Q12(-2.11f), Q12(-105.46f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-262.74f), Q12(0.07f), Q12(-102.45f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            g_SysWork.player_4C.chara_0.position_18.vx = Q12(-262.39f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(-104.33f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(45.0f);

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 2, false, false);
            break;

        case 6:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 7:
            MapMsg_DisplayAndHandleSelection(false, 50, false, false, 0, false); // "Hmm... the lock is worn out."
            break;

        case 8:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();

            Savegame_EventFlagSet(EventFlag_167);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            break;
    }
}

void func_800EB3F4(void) // 0x800EB3F4
{
    const static VECTOR3 D_800CD45C = { Q12(-261.977f), Q12(-0.1f),  Q12(-104.286f) };
    const static VECTOR3 D_800CD468 = { Q12(-263.0f),   Q12(-1.25f), Q12(-104.0f)   };

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_8005DC1C(Sfx_Unk1393, &D_800CD45C, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            Camera_PositionSet(NULL, Q12(-263.03f), Q12(-3.43f), Q12(-105.37f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-261.58f), Q12(-0.08f), Q12(-103.73f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            D_800F22AE = 0;

            Savegame_EventFlagSet(EventFlag_169);

            g_SysWork.field_30 = 20;
            Model_AnimFlagsClear(&g_SysWork.player_4C.chara_0.model_0, AnimFlag_Visible);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case 6:
            func_8005DC1C(Sfx_Unk1394, &D_800CD468, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);

            // TODO: Odd float values, maybe using different Q format for `s16`?
            D_800F22AE += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(-0.0277f), Q12_SHIFT);
            D_800F22AE  = MAX(Q12(-0.0137f), D_800F22AE);

            D_800F538C.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, D_800F22AE, Q12_SHIFT);
            if (D_800F538C.vy < Q12(-0.02222f)) // TODO: `MAX`? Currently doesn't match.
            {
                D_800F538C.vy = Q12(-0.02222f);
            }
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            Model_AnimFlagsSet(&g_SysWork.player_4C.chara_0.model_0, AnimFlag_Visible);

            if (g_SysWork.playerCombatInfo_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                g_SysWork.playerCombatInfo_38.weaponAttack_F %= 10; // TODO: Use macro.
            }

            vcReturnPreAutoCamWork(true);
            break;
    }
}

void func_800EB758(void) // 0x800EB758
{
    func_800EB824(0);
    SysWork_StateSetNext(SysState_Gameplay);
}

void func_800EB79C(void) // 0x800EB79C
{
    func_800EB824(1);
    SysWork_StateSetNext(SysState_Gameplay);
}

void func_800EB7E0(void) // 0x800EB7E0
{
    func_800EB824(2);
    SysWork_StateSetNext(SysState_Gameplay);
}

void func_800EB824(s32 arg0) // 0x800EB824
{
    if (arg0 == 0)
    {
        Savegame_EventFlagSet(EventFlag_172);
    }
    else
    {
        Savegame_EventFlagClear(EventFlag_172);
    }

    if (arg0 == 1)
    {
        Savegame_EventFlagSet(EventFlag_173);
    }
    else
    {
        Savegame_EventFlagClear(EventFlag_173);
    }

    if (arg0 == 2)
    {
        Savegame_EventFlagSet(EventFlag_174);
    }
    else
    {
        Savegame_EventFlagClear(EventFlag_174);
    }

    func_800EE5D0();
}

void func_800EB908(void) // 0x800EB908
{
    D_800F534C = 0;
    WorldObjectInit(&g_WorldObject9, "DRILL_NE", 236.7151f, -0.281f, 345.046f, 2.8f, 7.5f, -180.5f);

    WorldObjectInit(&g_WorldObjectA, "CHAINSAW", -82.3f, -0.7f, -91.6f, -17.0f, 18.1f, -7.22f);

    WorldObjectInit(&g_WorldObject0, "IRONPIPE", -187.591f, -0.093f, 300.271f, 4.4f, 36.8f, 2.9f);

    WorldObjectInit(&g_WorldObject1, "SKB2_NEA", -186.68f, -0.483f, 300.829f, 4.1f, -74.05f, -9.5f);

    WorldObjectInit(&g_WorldObject2, "PPR1_NEA", -154.56f, 0.0f, 1.78f, 0.0f, -51.7f, 0.0f);

    WorldObjectInit(&g_WorldObject3, "PPR2_NEA", -154.6f, 0.0f, 2.22f, 0.0f, 74.3f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObjectB[0], "JO0A_HID", 111.94f, -0.81f, 216.25f);

    WorldObjectNoRotInit(&g_WorldObjectB[1], "JO0B_HID", 111.94f, -0.57f, 216.25f);

    WorldObjectNoRotInit(&g_WorldObjectB[2], "JO0C_HID", 111.94f, -0.32f, 216.25f);

    WorldObjectInit(&g_WorldObject4[0], "KEY_HIDE", 185.76f, -0.59f, 116.12f, 0.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject4[1], "KEY_NEAR", -190.42f, 0.0f, 376.63f, 0.0f, 58.5f, 0.0f);

    WorldObjectInit(&g_WorldObject4[2], "KEY_NEAR", 99.4f, -0.35f, -33.26f, 1.6f, 0.0f, 0.9f);

    WorldObject_ModelNameSet(&g_WorldObject5[0], "AXIS1_HI");
    WorldObject_ModelNameSet(&g_WorldObject5[1], "AXIS2_BA");
    WorldObject_ModelNameSet(&g_WorldObject5[2], "AXIS1_HI");
    WorldObject_ModelNameSet(&g_WorldObject5[3], "AXIS2_BA");

    Math_Vector3Set(&D_800F55DC[0], Q12(205.0f), Q12(0.0f), Q12(-80.0f));
    Math_Vector3Set(&D_800F55DC[1], Q12(-35.0f), Q12(0.0f), Q12(360.0f));

    Math_SetSVectorFast(&D_800F5344, 0, 0, 0);

    WorldObject_ModelNameSet(&g_WorldObject6[0], "CHAIN1_1");
    WorldObject_ModelNameSet(&g_WorldObject6[1], "CHAIN1_2");
    WorldObject_ModelNameSet(&g_WorldObject6[2], "CHAIN1_3");
    WorldObject_ModelNameSet(&g_WorldObject7[0], "CHAIN2_1");
    WorldObject_ModelNameSet(&g_WorldObject7[1], "CHAIN2_2");
    WorldObject_ModelNameSet(&g_WorldObject7[2], "CHAIN2_3");
    WorldObject_ModelNameSet(&g_WorldObject7[3], "CHAIN2_4");

    Math_Vector3Set(&D_800F56CC[0], Q12(-262.0f), Q12(0.0f), Q12(-104.0f));
    Math_Vector3Set(&D_800F56CC[1], Q12(-263.0f), Q12(0.0f), Q12(-104.0f));

    WorldObject_ModelNameSet(&D_800F535C, "DOOR1_BA");
    Math_Vector3Set(&D_800F537C, Q12(-263.0f), Q12(0.0f), Q12(-104.0f));

    Math_SetSVectorFast(&D_800F538C, 0, 0, 0);
    WorldObject_ModelNameSet(&D_800F56EC, D_800A99E4.savePadName_4);

    WorldObjectPoseInit(&D_800F570C, 117.681641f, -1.01f, 216.263f, 0.0f, 193.51f, 0.0f);
    WorldObjectPoseInit(&D_800F572C, 116.3013f, -0.905f, 299.1139f, 0.0f, 84.56f, 0.0f);
    WorldObjectPoseInit(&D_800F574C, -44.234f, -3.453f, 345.2f, 0.0f, 180.0f, 0.0f);

    WorldObjectInit(&g_WorldObject8, "MAP_NEAR", -43.694f, -3.1824f, 345.764f, 6.7f, 6.1f, 0.0f);

    D_800F56E4 = 0;

    if (!Savegame_EventFlagGet(EventFlag_146) ||
        (Savegame_EventFlagGet(EventFlag_193) &&  !Savegame_EventFlagGet(EventFlag_M2S00_WaterWorksCutscene)))
    {
        g_SysWork.flags_22A4 |= SysFlag2_4;
    }

    if (Savegame_EventFlagGet(EventFlag_159))
    {
        D_800F1A24 = 0x64000;
    }

    if (!Savegame_EventFlagGet(EventFlag_166))
    {
        D_800F5344.vz = FP_ANGLE(-49.94f);
    }

    if (Savegame_EventFlagGet(EventFlag_168))
    {
        D_800F538C.vy = FP_ANGLE(8.0f);
    }

    func_800EE5D0();

    if (Savegame_EventFlagGet(EventFlag_132) && !Savegame_EventFlagGet(EventFlag_M2S00_KGordonDoorOpen))
    {
        g_SavegamePtr->field_B0[10] &= 0xF3FFFEFF;
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        g_SysWork.npcId_2280 = 2;
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        g_SysWork.npcId_2280 = 3;
    }
    else
    {
        g_SysWork.npcId_2280 = 4;
    }

    g_SysWork.npcId_2280++;
    SysWork_NpcFlagSet(g_SysWork.npcId_2280 - 1);

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void func_800EC080(void) // 0x800EC080
{
    s32 cellX0;
    s32 cellX1;
    s32 cellX2;
    s32 cellZ0;
    s32 cellZ1;
    s32 cellZ2;
    s32 projCellX0;
    s32 projCellX1;
    s32 projCellX2;
    s32 projCellZ0;
    s32 projCellZ1;
    s32 projCellZ2;
    s32 flags;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    flags = 0;

    cellZ0 = g_SysWork.player_4C.chara_0.position_18.vz / CHUNK_CELL_SIZE;
    cellX0 = g_SysWork.player_4C.chara_0.position_18.vx / CHUNK_CELL_SIZE;

    if (g_SysWork.player_4C.chara_0.position_18.vx > Q12(0.0f))
    {
        projCellX0 = cellX0 + 17;
    }
    else
    {
        projCellX0 = cellX0 + 15;
    } 

    if (g_SysWork.player_4C.chara_0.position_18.vz > Q12(0.0f))
    {
        projCellZ0 = cellZ0 + 17;
    }
    else
    {
        projCellZ0 = cellZ0 + 15;
    }

    switch (PACKED_CELL_XZ(projCellX0, projCellZ0))
    {
        case PACKED_CELL_XZ(11, 24):
            if (!Savegame_EventFlagGet(EventFlag_147))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObject1.object_0, &g_WorldObject1.position_1C, &g_WorldObject1.rotation_28);
            }

            if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupSteelPipe))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &g_WorldObject0.rotation_28);
            }
            break;

        case PACKED_CELL_XZ(12, 17):
        case PACKED_CELL_XZ(12, 15):
            if (!Savegame_EventFlagGet(EventFlag_M2S00_DogHouseNoteFound))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObject2.object_0, &g_WorldObject2.position_1C, &g_WorldObject2.rotation_28);
                g_WorldGfx_ObjectAdd(&g_WorldObject3.object_0, &g_WorldObject3.position_1C, &g_WorldObject3.rotation_28);
            }
            break;

        case PACKED_CELL_XZ(14, 25):
            g_WorldGfx_ObjectAdd(&g_WorldObject5[2], &D_800F55DC[1], &D_800F5344);
            g_WorldGfx_ObjectAdd(&g_WorldObject5[3], &D_800F55DC[1], &D_800F5344);

            if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupMap))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObject8.object_0, &g_WorldObject8.position_1C, &g_WorldObject8.rotation_28);
            }

            g_WorldGfx_ObjectAdd(&D_800F56EC, &D_800F574C.position_0, &D_800F574C.rotation_C);
            break;

        case PACKED_CELL_XZ(21, 13):
            if (Savegame_EventFlagGet(EventFlag_163)) 
            {
                flags |= 1 << 2;
                if (g_SysWork.player_4C.chara_0.position_18.vx > Q12(198.0f))
                {
                    Savegame_EventFlagClear(EventFlag_163);
                }
            }
            else
            {
                flags |= 1 << 1;
            }

        case PACKED_CELL_XZ(21, 14):
        case PACKED_CELL_XZ(22, 14):
        case PACKED_CELL_XZ(22, 13):
            g_WorldGfx_ObjectAdd(&g_WorldObject5[0], &D_800F55DC[0], &D_800F5344);
            g_WorldGfx_ObjectAdd(&g_WorldObject5[1], &D_800F55DC[0], &D_800F5344);

            if (!Savegame_EventFlagGet(EventFlag_166))
            {
                flags |= 1 << 3;
            }

            if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_BotBridgeCorrection))
            {
                Savegame_MapMarkingClear(MapMarkFlag_61);
            }
            else
            {
                Savegame_MapMarkingSet(MapMarkFlag_61);
            }
            break;

        case PACKED_CELL_XZ(9, 13):
            g_WorldGfx_ObjectAdd(&D_800F535C, &D_800F537C, &D_800F538C);

            if (!Savegame_EventFlagGet(EventFlag_170))
            {
                if (!Savegame_EventFlagGet(EventFlag_169))
                {
                    g_WorldGfx_ObjectAdd(&g_WorldObject6[0], &D_800F56CC[0], &(SVECTOR3){ 0, 0, 0 });
                    g_WorldGfx_ObjectAdd(&g_WorldObject6[1], &D_800F56CC[0], &(SVECTOR3){ 0, 0, 0 });
                    g_WorldGfx_ObjectAdd(&g_WorldObject6[2], &D_800F56CC[0], &(SVECTOR3){ 0, 0, 0 });
                }
                else
                {
                    g_WorldGfx_ObjectAdd(&g_WorldObject7[0], &D_800F56CC[1], &D_800F538C);
                    g_WorldGfx_ObjectAdd(&g_WorldObject7[1], &D_800F56CC[1], &D_800F538C);
                    g_WorldGfx_ObjectAdd(&g_WorldObject7[2], &D_800F56CC[0], &(SVECTOR3){ 0, 0, 0 });
                    g_WorldGfx_ObjectAdd(&g_WorldObject7[3], &D_800F56CC[0], &(SVECTOR3){ 0, 0, 0 });
                }
            }
            break;

        case PACKED_CELL_XZ(19, 22):
        case PACKED_CELL_XZ(20, 22):
            if (!Savegame_EventFlagGet(EventFlag_M2S00_LockOfLionOpen))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObjectB->object_0, &g_WorldObjectB->position_1C, &(SVECTOR3){ 0, 0, 0 });
            }

            if (!Savegame_EventFlagGet(EventFlag_M2S00_LockOfWoodmanOpen))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObjectB[1].object_0, &g_WorldObjectB[1].position_1C, &(SVECTOR3){ 0, 0, 0 });
            }

            if (!Savegame_EventFlagGet(EventFlag_M2S00_LockOfScarecrowOpen))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObjectB[2].object_0, &g_WorldObjectB[2].position_1C, &(SVECTOR3){ 0, 0, 0 });
            }

            g_WorldGfx_ObjectAdd(&D_800F56EC, &D_800F570C.position_0, &D_800F570C.rotation_C);
            break;

        case PACKED_CELL_XZ(21, 19):
            if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfLion))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObject4[0].object_0, &g_WorldObject4[0].position_1C, &g_WorldObject4[0].rotation_28);
            }
            break;

        case PACKED_CELL_XZ(11, 26):
            if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfWoodman))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObject4[1].object_0, &g_WorldObject4[1].position_1C, &g_WorldObject4[1].rotation_28);
            }
            break;

        case PACKED_CELL_XZ(19, 15):
            if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupKeyOfScarecrow))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObject4[2].object_0, &g_WorldObject4[2].position_1C, &g_WorldObject4[2].rotation_28);
            }
            break;

        case PACKED_CELL_XZ(19, 24):
        case PACKED_CELL_XZ(20, 24):
            g_WorldGfx_ObjectAdd(&D_800F56EC, &D_800F572C.position_0, &D_800F572C.rotation_C);
            break;

        default:
            break;
    }

    cellZ1 = g_SysWork.player_4C.chara_0.position_18.vz / CHUNK_CELL_SIZE;
    cellX1 = g_SysWork.player_4C.chara_0.position_18.vx / CHUNK_CELL_SIZE;

    if (g_SysWork.player_4C.chara_0.position_18.vx > Q12(0.0f)) 
    {
        projCellX1 = cellX1 + 17;
    }
    else
    {
        projCellX1 = cellX1 + 15;
    }

    if (g_SysWork.player_4C.chara_0.position_18.vz > Q12(0.0f)) 
    {
        projCellZ1 = cellZ1 + 17;
    }
    else
    {
        projCellZ1 = cellZ1 + 15;
    }

    switch (PACKED_CELL_XZ(projCellX1, projCellZ1))
    {
        case PACKED_CELL_XZ(14, 25):
            if (Savegame_EventFlagGet(EventFlag_164))
            {
                if (D_800F534C == 0)
                {
                    D_800F534C = 1;
                    Sd_EngineCmd(Sfx_Unk1482);
                    D_800F5350 = Q12(0.75f);
                }
                else if (D_800F534C == NO_VALUE)
                {
                    D_800F5350 += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.25f), Q12_SHIFT);
                    if (D_800F5350 > Q12(0.75f))
                    {
                        D_800F5350 = Q12(0.75f);
                        D_800F534C = 1;
                    }
                }

                func_8005DE0C(Sfx_Unk1482, &QVECTOR3(-43.0f, -1.0f, 346.0f), D_800F5350 >> 5, Q12(32.0f), 0);
            }
            break;

        case PACKED_CELL_XZ(22, 25):
            if (Savegame_EventFlagGet(EventFlag_164))
            {
                if (D_800F534C == 0)
                {
                    D_800F534C++;
                    Sd_EngineCmd(Sfx_Unk1482);
                }

                func_8005DE0C(Sfx_Unk1482, &QVECTOR3(237.0f, -1.0f, 346.0f), Q8(0.5f), Q12(16.0f), 0);
            }

            if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupRockDrill))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObject9.object_0, &g_WorldObject9.position_1C, &g_WorldObject9.rotation_28);
                Savegame_EventFlagSet(EventFlag_66);
            }
            else
            {
                Savegame_EventFlagClear(EventFlag_66);
            }
            break;

        default:
            if (D_800F534C != 0)
            {
                D_800F534C = 0;
                func_8004690C(Sfx_Unk1482);
            }
            break;
    }

    cellZ2 = g_SysWork.player_4C.chara_0.position_18.vz / CHUNK_CELL_SIZE;
    cellX2 = g_SysWork.player_4C.chara_0.position_18.vx / CHUNK_CELL_SIZE;

    if (g_SysWork.player_4C.chara_0.position_18.vx > Q12(0.0f))
    {
        projCellX2 = cellX2 + 17;
    }
    else
    {
        projCellX2 = cellX2 + 15;
    }

    if (g_SysWork.player_4C.chara_0.position_18.vz > Q12(0.0f))
    {
        projCellZ2 = cellZ2 + 17;
    }
    else
    {
        projCellZ2 = cellZ2 + 15;
    }

    switch (PACKED_CELL_XZ(projCellX2, projCellZ2))
    {
        case PACKED_CELL_XZ(22, 25):
            if (D_800F56E4 != 2)
            {
                func_8003ED74(6, 3);
                D_800F56E4 = 2;
                Game_TurnFlashlightOff();
            }
            break;

        case PACKED_CELL_XZ(19, 22):
        case PACKED_CELL_XZ(20, 22):
            if (!Savegame_EventFlagGet(EventFlag_134) && Savegame_EventFlagGet(EventFlag_159))
            {
                if (D_800F56E4 != 1)
                {
                    func_8003ED74(6, 3);
                    D_800F56E4 = 1;
                }
            }
            else
            {
                if (D_800F56E4 != 3)
                {
                    func_8003ED74(13, 13);
                    D_800F56E4 = 3;
                }
            }
            break;

        case PACKED_CELL_XZ(19, 24):
        case PACKED_CELL_XZ(20, 24):
            if (D_800F56E4 != 3)
            {
                func_8003ED74(13, 13);
                D_800F56E4 = 3;
            }
            break;

        case PACKED_CELL_XZ(13, 13):
        case PACKED_CELL_XZ(14, 13):
            if (!Savegame_EventFlagGet(EventFlag_M2S00_PickupChainsaw))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObjectA.object_0, &g_WorldObjectA.position_1C, &g_WorldObjectA.rotation_28);
                Savegame_EventFlagSet(EventFlag_65);
            }
            else
            {
                Savegame_EventFlagClear(EventFlag_65);
            }
            break;

        default:
            if (D_800F56E4 != 1)
            {
                if (Savegame_EventFlagGet(EventFlag_134) || !Savegame_EventFlagGet(EventFlag_159))
                {
                    func_8003ED74(1, 1);
                    Game_TurnFlashlightOff();
                }
                else
                {
                    func_8003ED74(6, 3);
                }

                D_800F56E4 = 1;
            }
            break;

    }

    if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_BradburyStLeftCross) &&
        Savegame_MapMarkingGet(MapMarkFlag_OldTown_BachmanRdBotCross) &&
        Savegame_MapMarkingGet(MapMarkFlag_OldTown_ElroyStBotCross))
    {
        Savegame_MapMarkingSet(MapMarkFlag_OldTown_BotRightHugeComboCross);
    }

    if (Savegame_MapMarkingGet(MapMarkFlag_OldTown_BlochStLeftCross) &&
        Savegame_MapMarkingGet(MapMarkFlag_OldTown_LevinStTopCross) &&
        Savegame_MapMarkingGet(MapMarkFlag_OldTown_BlochStRightCross) &&
        Savegame_MapMarkingGet(MapMarkFlag_OldTown_LevinStBotCross))
    {
        Savegame_MapMarkingSet(MapMarkFlag_OldTown_LevinBlochBigCombo);
    }

    func_800EE660();
    func_80069844(0xFFFF);
    func_8006982C(flags);

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_FirstAidKit0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[0], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[3].position_0, &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, -4, -1, -4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets2))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[4].position_0, &g_CommonWorldObjectPoses[4].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, -4, -1, -4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_ShotgunShells0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[5].position_0, &g_CommonWorldObjectPoses[5].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 6, -1, 6))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[6].position_0, &g_CommonWorldObjectPoses[6].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 6, -1, 6))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets3))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[7].position_0, &g_CommonWorldObjectPoses[7].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 6, -1, 6))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets4))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[8].position_0, &g_CommonWorldObjectPoses[8].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 8, -1, 8))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets5))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[9].position_0, &g_CommonWorldObjectPoses[9].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 8, -1, 8))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets6))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[10].position_0, &g_CommonWorldObjectPoses[10].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -7, -1, -7) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets7))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[11].position_0, &g_CommonWorldObjectPoses[11].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 5, -1, 5) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets8))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[12].position_0, &g_CommonWorldObjectPoses[12].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, 9, -1, 9))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink2))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[13].position_0, &g_CommonWorldObjectPoses[13].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -7, -1, -7) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink3))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[14].position_0, &g_CommonWorldObjectPoses[14].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink4))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[15].position_0, &g_CommonWorldObjectPoses[15].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets9))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[16].position_0, &g_CommonWorldObjectPoses[16].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -5, -1, -5))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink5))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[17].position_0, &g_CommonWorldObjectPoses[17].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -4, -1, -4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets10))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[18].position_0, &g_CommonWorldObjectPoses[18].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink6))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[19].position_0, &g_CommonWorldObjectPoses[19].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -4, -1, -4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink7))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[20].position_0, &g_CommonWorldObjectPoses[20].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 10, -1, 10))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink8))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[21].position_0, &g_CommonWorldObjectPoses[21].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 10, -1, 10))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink9))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[22].position_0, &g_CommonWorldObjectPoses[22].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 1, 10, -1, 10))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink10))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[23].position_0, &g_CommonWorldObjectPoses[23].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HealthDrink11))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[24].position_0, &g_CommonWorldObjectPoses[24].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_ShotgunShells1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[25].position_0, &g_CommonWorldObjectPoses[25].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_FirstAidKit1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[0], &g_CommonWorldObjectPoses[26].position_0, &g_CommonWorldObjectPoses[26].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets11))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[27].position_0, &g_CommonWorldObjectPoses[27].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets12))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[28].position_0, &g_CommonWorldObjectPoses[28].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 1, 8, -1, 8))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets13))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[29].position_0, &g_CommonWorldObjectPoses[29].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 1, 8, -1, 8))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_HandgunBullets14))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[30].position_0, &g_CommonWorldObjectPoses[30].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 6, -1, 6))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S00_FirstAidKit2))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[0], &g_CommonWorldObjectPoses[31].position_0, &g_CommonWorldObjectPoses[31].rotation_C);
        }
    }
}

s32 func_800EE518(void) // 0x800EE518
{
    s32 ret;

    if (!Savegame_EventFlagGet(EventFlag_172))
    {
        if (Savegame_EventFlagGet(EventFlag_173))
        {
            ret = 1;
        }
        else if (Savegame_EventFlagGet(EventFlag_174))
        {
            ret = 2;
        }
        else
        {
            Savegame_EventFlagSet(EventFlag_172);
            ret = 0;
        }
    }
    else
    {
        ret = 0;
    }

    if (Savegame_EventFlagGet(EventFlag_131) && !Savegame_EventFlagGet(EventFlag_181) && ret == 1)
    {
        ret = 2;
    }

    return ret;
}

s32 func_800EE5A8(u32 arg0) // 0x800EE5A8
{
    if (arg0 < 3)
    {
        return D_800F1CA8[arg0];
    }

    return 10;
}

void func_800EE5D0(void) // 0x800EE5D0
{
    s32 idx;

    idx = func_800EE518();
    memcpy(g_MapOverlayHeader.charaSpawns_24C, D_800F1CAC[idx], sizeof(D_800F1CAC[idx]));
    g_SavegamePtr->field_B0[10] = g_SavegamePtr->field_B0[idx];
}

void func_800EE660(void) // 0x800EE660
{
    s32 val;
    s32 idx;

    idx = func_800EE518();
    val = g_SavegamePtr->field_B0[10];
    g_SavegamePtr->field_B0[func_800EE5A8(idx)] = val;
}
