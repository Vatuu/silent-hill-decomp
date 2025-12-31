#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/map0_s01.h"
#include "maps/characters/air_screamer.h"

const VECTOR D_800CA5C8 = {};

#include "maps/shared/sharedFunc_800CCB8C_0_s01.h" // 0x800CCB8C

#include "maps/shared/sharedFunc_800CD1F8_0_s01.h" // 0x800CD1F8

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CE000

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CE4C4

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CE59C

#include "maps/shared/Particle_Update.h" // 0x800CE8A8

#include "maps/shared/sharedFunc_800CEB24_0_s00.h" // 0x800CEE2C

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CF2A4

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CF3F4

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CF7BC

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CF8E8

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CF8F0

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CF9A8

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CFA30

#include "../src/maps/characters/player.c"

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CA9F0);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CA9F4);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CAA00);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CAA18);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CAA30);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", D_800CAA48);

INCLUDE_RODATA("asm/maps/map0_s01/nonmatchings/map0_s01", sharedData_800CAA98_0_s01);

// TODO: Move this line into separate `Chara_AirScreamer` split.
// TODO: Most of the code below also belongs to `air_screamer.c`, move there once `INCLUDE_ASM` gaps are matched.
#include "../src/maps/characters/air_screamer.c" // 0x800D2170

void func_800D3EB8(s_SubCharacter* airScreamer) // 0x800D3EB8
{
    q19_12 damage;
    bool   cond1;
    bool   cond0;
    bool   temp_s3;
    u32    animStatus;
    s32    animStatus12;
    bool   activeAnimStatus;
    u32    stateStep;

    animStatus = airScreamer->model_0.anim_4.status_0;
    animStatus12 = ANIM_STATUS(12, true);

    sharedFunc_800D5638_0_s01(airScreamer);

    activeAnimStatus = ANIM_STATUS(ANIM_STATUS_IDX_GET(animStatus), true);

    stateStep = airScreamer->model_0.stateStep_3;
    switch (stateStep)
    {
        case 0:
            temp_s3 = sharedFunc_800D5F00_0_s01(airScreamer);
            cond0 = false;
            cond1 = airScreamer->position_18.vy >= Q12(8.0f);

            if (func_800808AC(airScreamer->position_18.vx, airScreamer->position_18.vz) == 7)
            {
                cond0 = airScreamer->position_18.vy >= Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz);
            }

            if (cond1)
            {
                Ai_AirScreamer_DamageTake(airScreamer, Q12(0.0f));

                airScreamer->position_18.vx = g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(100.0f);
                airScreamer->position_18.vz = g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(100.0f);

                sharedFunc_800D3DFC_0_s01(airScreamer);
                break;
            }

            if (cond0)
            {
                Ai_AirScreamer_DamageTake(airScreamer, Q12(0.0f));
                sharedFunc_800D2364_0_s01(airScreamer);

                airScreamer->position_18.vx = g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(100.0f);
                airScreamer->position_18.vz = g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(100.0f);

                sharedFunc_800D3DFC_0_s01(airScreamer);
                break;
            }

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                Ai_AirScreamer_DamageTake(airScreamer, Q12(0.0f));

                if (animStatus == ANIM_STATUS(26, true) && temp_s3 == true)
                {
                    airScreamer->health_B0 = NO_VALUE;

                    func_800622B8(3, airScreamer, ANIM_STATUS(4, true), 2);

                    airScreamer->model_0.stateStep_3 = 1;

                    sharedFunc_800D3DFC_0_s01(airScreamer);
                    break;
                }
            }
            else
            {
                airScreamer->flags_3E |= CharaFlag_Unk2;

                if (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)) == 4)
                {
                    if (airScreamer->health_B0 <= Q12(0.0f))
                    {
                        airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(5, false);
                        airScreamer->properties_E4.player.flags_11C |= PlayerFlag_Unk6;
                        break;
                    }

                    airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(12, false);
                    airScreamer->model_0.stateStep_3 = 2;
                    airScreamer->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
                    break;
                }

                damage = g_DeltaTime0 * 10;
                if (damage < airScreamer->health_B0)
                {
                    airScreamer->health_B0 -= damage;
                }
                else if (airScreamer->health_B0 > Q12(0.0f))
                {
                    airScreamer->health_B0 = Q12(0.0f);
                }
            }
            break;

        case 1:
            Ai_AirScreamer_DamageTake(airScreamer, Q12(0.0f));
            break;

        case 2:
            Ai_AirScreamer_DamageTake(airScreamer, Q12(0.5f));

            if (activeAnimStatus != animStatus12)
            {
                airScreamer->model_0.stateStep_3 = 0;
            }
            break;
    }
}

void func_800D4114(void) {}

void func_800D411C(void) {}

void func_800D4124(void) {}

void func_800D412C(void) {}

void func_800D4134(void) {}

void func_800D413C(void) {}

void func_800D4144(void) {}

void func_800D414C(void) {}

void func_800D4154(void) {}

void func_800D415C(void) {}

void func_800D4164(void) {}

void func_800D416C(void) {}

void func_800D4174(void) {}

void func_800D417C(void) {}

void func_800D4184(void) {}

void func_800D418C(void) {}

void func_800D4194(void) {}

void func_800D419C(void) {}

void func_800D41A4(void) {}

void func_800D41AC(void) {}

void func_800D41B4(void) {}

void func_800D41BC(void) {}

void func_800D41C4(void) {}

void func_800D41CC(void) {}

void func_800D41D4(void) {}

void func_800D41DC(void) {}

void func_800D41E4(void) {}

void func_800D41EC(void) {}

void func_800D41F4(void) {}

void func_800D41FC(void) {}

void func_800D4204(void) {}

void func_800D420C(void) {}

void func_800D4214(void) {}

void func_800D421C(void) {}

void func_800D4224(void) {}

void func_800D422C(void) {}

void func_800D4234(void) {}

void func_800D423C(void) {}

void func_800D4244(void) {}

void func_800D424C(void) {}

void func_800D4254(void) {}

void func_800D425C(void) {}

void func_800D4264(void) {}

void func_800D426C(s_SubCharacter* airScreamer) // 0x800D426C
{
    s32 animStatus;

    animStatus = airScreamer->model_0.anim_4.status_0;

    if (airScreamer->model_0.stateStep_3 != 1)
    {
        if (airScreamer->model_0.stateStep_3 == 0 && animStatus == ANIM_STATUS(2, true) && airScreamer->model_0.anim_4.keyframeIdx_8 < 8204)
        {
            airScreamer->properties_E4.unk0.properties_120.val32 = Q12(4.0f);
            airScreamer->model_0.stateStep_3 = 1;
            airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk5;
            airScreamer->flags_3E |= CharaFlag_Unk3;
        }
    }
    else if (ANIM_STATUS(ANIM_STATUS_IDX_GET(animStatus), true) == ANIM_STATUS(19, true))
    {
        airScreamer->model_0.stateStep_3 = 2;
        airScreamer->properties_E4.unk0.properties_120.val32 = Q12(4.0f);
    }

    sharedFunc_800D529C_0_s01(airScreamer, Q12(1.0f), func_80080478(&airScreamer->position_18, &g_SysWork.playerWork_4C.player_0.position_18));
    sharedFunc_800D598C_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            if (!airScreamer->properties_E4.unk0.properties_120.val32 ||
                airScreamer == &g_SysWork.npcs_1A0[g_SysWork.targetNpcIdx_2353] ||
                Math_Distance2dGet(&airScreamer->position_18, &g_SysWork.playerWork_4C.player_0.position_18) > Q12(6.5f))
            {
                airScreamer->model_0.controlState_2 = 47;
                airScreamer->model_0.stateStep_3 = 0;
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk4;
                return;
            }

        default:
            return;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = 50;
            airScreamer->model_0.stateStep_3 = 0;
            airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            return;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = 51;
            airScreamer->model_0.stateStep_3 = 0;
            if (airScreamer->health_B0 <= 0)
            {
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }
}

void func_800D4420(s_SubCharacter* airScreamer) // 0x800D4420
{
    q19_12 dist0;
    q19_12 deltaY;
    q19_12 angle;
    q19_12 dist;

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            airScreamer->properties_E4.unk0.properties_120.val32 = Q12(1.5f);
            airScreamer->model_0.stateStep_3 = 1;
            break;

        case 1:
            if (Math_Distance2dGet(&airScreamer->position_18, &airScreamer->properties_E4.unk0.field_F8) < Q12(0.5f))
            {
                airScreamer->model_0.stateStep_3 = 0;
            }
            break;
    }

    sharedFunc_800D53AC_0_s01(airScreamer);
    sharedFunc_800D57C8_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            dist0 = NO_VALUE;
            deltaY = airScreamer->properties_E4.unk0.field_F8.vy - airScreamer->position_18.vy;
            if (deltaY > Q12(-0.2f) && deltaY < Q12(0.8f))
            {
                dist0 = airScreamer->field_D4.radius_0 + Q12(0.15f);
            }

            dist = Math_Distance2dGet(&airScreamer->position_18, &airScreamer->properties_E4.unk0.field_F8);
            if (dist < dist0)
            {
                angle = FP_ANGLE_NORM_S(func_80080478(&airScreamer->position_18, &airScreamer->properties_E4.unk0.field_F8) - airScreamer->rotation_24.vy);
                if (angle >= FP_ANGLE(-8.0f) && angle < FP_ANGLE(8.0f))
                {
                    airScreamer->model_0.controlState_2 = 49;
                    airScreamer->model_0.stateStep_3 = 0;
                }
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = 50;
            airScreamer->model_0.stateStep_3 = 0;
            airScreamer->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = 51;
            airScreamer->model_0.stateStep_3 = 0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamer->properties_E4.player.flags_11C |= PlayerFlag_Unk6;
            }
            else
            {
                airScreamer->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            }
            break;
    }
}

void func_800D45BC(s_SubCharacter* airScreamer) // 0x800D45BC
{
    u32 temp_v0;

    if (!airScreamer->model_0.stateStep_3)
    {
        airScreamer->properties_E4.unk0.properties_120.val32 = Q12(2.0f);
        airScreamer->model_0.stateStep_3 = 1;
    }

    sharedFunc_800D53AC_0_s01(airScreamer);
    sharedFunc_800D5B10_0_s01(airScreamer);

    temp_v0 = Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f));
    switch (temp_v0)
    {
        case 0:
            if (!airScreamer->properties_E4.unk0.properties_120.val32 ||
                Math_Distance2dGet(&airScreamer->position_18, &g_SysWork.playerWork_4C.player_0.position_18) > Q12(2.0f))
            {
                airScreamer->model_0.controlState_2 = 47;
                airScreamer->model_0.stateStep_3 = 0;
                break;
            }

        default:
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2 = 50;
            airScreamer->model_0.stateStep_3 = 0;
            airScreamer->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = 51;
            airScreamer->model_0.stateStep_3 = 0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamer->properties_E4.player.flags_11C |= PlayerFlag_Unk6;
            }
            else
            {
                airScreamer->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
            }
            break;
    }
}

void func_800D46C4(s_SubCharacter* airScreamer) // 0x800D46C4
{
    bool cond0;
    bool cond1;
    s32  animStatus;

    cond0 = false;
    animStatus = airScreamer->model_0.anim_4.status_0;
    cond1 = false;

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            airScreamer->model_0.stateStep_3 = 1;

        case 1:
            if (animStatus == ANIM_STATUS(19, true))
            {
                airScreamer->model_0.stateStep_3 = 2;
                airScreamer->model_0.anim_4.status_0 = 4;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(2, true) && airScreamer->model_0.anim_4.keyframeIdx_8 < 8192)
            {
                airScreamer->model_0.stateStep_3 = 3;
                airScreamer->properties_E4.player.flags_11C |= PlayerFlag_Unk5;
            }
            break;

        case 3:
            if (animStatus == ANIM_STATUS(19, true))
            {
                cond0 = true;
            }
            else if (airScreamer->field_44.field_8 == NO_VALUE)
            {
                cond0 = true;
                cond1 = true;
                airScreamer->model_0.stateStep_3 = 4;
            }
            break;

        case 4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                cond0 = true;
                cond1 = true;
            }
            break;
    }

    sharedFunc_800D53AC_0_s01(airScreamer);
    sharedFunc_800D5C90_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.2f)))
    {
        case 0: 
            if (cond0)
            {
                if (!cond1)
                {
                    if (Rng_RandQ12() >= FP_ANGLE(180.0f))
                    {
                        airScreamer->model_0.controlState_2 = 47;
                    }
                    else
                    {
                        airScreamer->model_0.controlState_2 = 48;
                    }
                }
                else
                {
                    airScreamer->model_0.controlState_2 = 48;
                }

                airScreamer->model_0.stateStep_3 = 0;
                break;
            }

        default:
            break;

        case 1: 
        case 2: 
            airScreamer->model_0.controlState_2 = 50;
            airScreamer->model_0.stateStep_3 = 0;
            airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3: 
        case 4: 
            airScreamer->model_0.controlState_2 = 51;
            airScreamer->model_0.stateStep_3 = 0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }
}

void func_800D4894(s_SubCharacter* airScreamer)
{
    s32  damageType;
    s32  animStatus;
    u32  stateStep;
    bool cond;

    stateStep  = airScreamer->model_0.stateStep_3;
    animStatus = airScreamer->model_0.anim_4.status_0;
    cond       = false;

    switch (stateStep)
    {
        case 0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(7, false);
                airScreamer->model_0.stateStep_3     = 1;
            }
            break;

        case 1:
            if (animStatus != ANIM_STATUS(7, false))
            {
                airScreamer->model_0.stateStep_3 = 2;
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;

        case 2:
            if (animStatus != ANIM_STATUS(7, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800D5D80_0_s01(airScreamer);

    damageType = Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f));
    // TODO: Switch?
    if (damageType >= 0)
    {
        if (damageType < 3)
        {
            if (cond)
            {
                airScreamer->model_0.controlState_2 = ANIM_STATUS(23, true);
                airScreamer->model_0.stateStep_3 = 0;
                airScreamer->properties_E4.unk0.field_E8_8 = 3;
            }
        }
        else if (damageType < 5)
        {
            airScreamer->model_0.controlState_2     = ANIM_STATUS(25, true);
            airScreamer->model_0.stateStep_3 = 0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
        }
    }
}

void func_800D49B0(s_SubCharacter* airScreamer) // 0x800D49B0
{
    s32  animStatus;
    u32  stateStep;
    bool cond;

    stateStep  = airScreamer->model_0.stateStep_3;
    animStatus = airScreamer->model_0.anim_4.status_0;
    cond       = false;

    switch (stateStep)
    {
        case 0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                airScreamer->model_0.stateStep_3 = 1;
            }
            break;

        case 1:
            if (animStatus != ANIM_STATUS(10, false))
            {
                airScreamer->model_0.stateStep_3 = 2;
                airScreamer->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;

        case 2:
            if (animStatus != ANIM_STATUS(10, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800D5E14_0_s01(airScreamer);
    Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f));

    if (cond)
    {
        airScreamer->model_0.controlState_2 = 2;
        airScreamer->model_0.stateStep_3 = 0;
        airScreamer->properties_E4.unk0.field_E8_8 = 1;
    }
}

#include "maps/shared/sharedFunc_800D4A80_0_s01.h" // 0x800D4A80

#include "maps/shared/sharedFunc_800D4AEC_0_s01.h" // 0x800D4AEC

#include "maps/shared/sharedFunc_800D4E84_0_s01.h" // 0x800D4E84

#include "maps/shared/sharedFunc_800D5274_0_s01.h" // 0x800D5274

#include "maps/shared/sharedFunc_800D529C_0_s01.h" // 0x800D529C

#include "maps/shared/sharedFunc_800D53AC_0_s01.h" // 0x800D53AC

#include "maps/shared/sharedFunc_800D5638_0_s01.h" // 0x800D5638

#include "maps/shared/sharedFunc_800D569C_0_s01.h" // 0x800D569C

#include "maps/shared/sharedFunc_800D57C8_0_s01.h" // 0x800D57C8

#include "maps/shared/sharedFunc_800D598C_0_s01.h" // 0x800D598C

#include "maps/shared/sharedFunc_800D5B10_0_s01.h" // 0x800D5B10

#include "maps/shared/sharedFunc_800D5C90_0_s01.h" // 0x800D5C90

#include "maps/shared/sharedFunc_800D5D80_0_s01.h" // 0x800D5D80

#include "maps/shared/sharedFunc_800D5E14_0_s01.h" // 0x800D5E14

#include "maps/shared/sharedFunc_800D5E78_0_s01.h" // 0x800D5E78

#include "maps/shared/sharedFunc_800D5F00_0_s01.h" // 0x800D5F00

#include "maps/shared/sharedFunc_800D62D8_0_s01.h" // 0x800D62D8

#include "maps/shared/sharedFunc_800D633C_0_s01.h" // 0x800D633C

#include "maps/shared/sharedFunc_800D63A4_0_s01.h" // 0x800D63A4

#include "maps/shared/sharedFunc_800D6600_0_s01.h" // 0x800D6600

#include "maps/shared/sharedFunc_800D6A60_0_s01.h" // 0x800D6A60

#include "maps/shared/sharedFunc_800D6C7C_0_s01.h" // 0x800D6C7C

#include "maps/shared/sharedFunc_800D6EC4_0_s01.h" // 0x800D6EC4

#include "maps/shared/sharedFunc_800D7120_0_s01.h" // 0x800D7120

#include "maps/shared/sharedFunc_800D71F0_0_s01.h" // 0x800D71F0

#include "maps/shared/sharedFunc_800D72E8_0_s01.h" // 0x800D72E8

#include "maps/shared/sharedFunc_800D7440_0_s01.h" // 0x800D7440

#include "maps/shared/sharedFunc_800D7560_0_s01.h" // 0x800D7560

#include "maps/shared/sharedFunc_800D76A0_0_s01.h" // 0x800D76A0

#include "maps/shared/sharedFunc_800D7714_0_s01.h" // 0x800D7714

#include "maps/shared/sharedFunc_800D77D0_0_s01.h" // 0x800D77D0

#include "maps/shared/sharedFunc_800D7AB0_0_s01.h" // 0x800D7AB0

#include "maps/shared/sharedFunc_800D7B14_0_s01.h" // 0x800D7B14

q19_12 Model_AnimDurationGet(s_Model* model) // 0x800D7E88
{
    return Anim_DurationGet(model, func_80044918(&model->anim_4));
}

#include "maps/shared/sharedFunc_800D7EBC_0_s01.h" // 0x800D7EBC

#include "maps/shared/sharedFunc_800D81B0_0_s01.h" // 0x800D81B0

#include "maps/shared/sharedFunc_800D81D0_0_s01.h" // 0x800D81D0

#include "maps/shared/sharedFunc_800D8244_0_s01.h" // 0x800D8244

#include "maps/shared/sharedFunc_800D82B8_0_s01.h" // 0x800D82B8

#include "maps/shared/sharedFunc_800D8714_0_s01.h" // 0x800D8714

#include "maps/shared/sharedFunc_800D87FC_0_s01.h" // 0x800D87FC

#include "maps/shared/sharedFunc_800D8804_0_s01.h" // 0x800D8804
