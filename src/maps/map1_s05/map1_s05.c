#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map1/map1_s05.h"

INCLUDE_RODATA("asm/maps/map1_s05/nonmatchings/map1_s05", D_800C9578);

INCLUDE_RODATA("asm/maps/map1_s05/nonmatchings/map1_s05", g_MapOverlayHeader);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CAAD0);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CABF8);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CB040);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CB884);

void func_800CBE7C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x800CBE7C
{
    s32 i;

    i = func_8005E7E0(7);

    if (i != NO_VALUE)
    {
        sharedData_800E1FF8_1_s02[i].vx_0                 = ((arg0 + (Rng_Rand16() & 63)) - 32) * 16;
        sharedData_800E1FF8_1_s02[i].vy_8                 = (arg1 + (Rng_Rand16() & 63)) * 16;
        sharedData_800E1FF8_1_s02[i].vz_4                 = ((arg2 + (Rng_Rand16() & 63)) - 32) * 16;
        sharedData_800E1FF8_1_s02[i].field_B              = 0;
        sharedData_800E1FF8_1_s02[i].field_C.s_0.field_0  = 0;
        sharedData_800E1FF8_1_s02[i].field_C.s_0.field_2  = arg3;
        sharedData_800E1FF8_1_s02[i].field_10.s_1.field_0 = arg4;
        sharedData_800E1FF8_1_s02[i].field_10.s_1.field_2 = (Rng_Rand16() & 31) + 16;
        sharedData_800E1FF8_1_s02[i].field_10.s_1.field_3 = Rng_Rand16() & 15;
    }
}

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CBF74);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CC618);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CCDD4);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CCE2C);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CCF30);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CD5EC);

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CD754

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CD8D4

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CD98C

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CDAF0

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CDB10

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CE388

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CE774

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CEA68

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CEE94

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CEED0

#include "maps/shared/Player_ControlFreeze.h" // 0x800CEEDC

#include "maps/shared/Player_ControlUnfreeze.h" // 0x800CF03C

s32 func_800CF214(void) // 0x800CF214
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CF21C

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CF2CC

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CF2E4

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CF30C

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CF324

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CF34C

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CF3F0

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CF400

void func_800CF40C(void) {}

void func_800CF414(void) {}

void func_800CF41C(void) {}

void func_800CF424(void) {}

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CF42C);

s32 func_800CF7A4(void) // 0x800CF7A4
{
    return 0;
}

void func_800CF7AC(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CF7B4

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CF7C4

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CF804

#include "maps/shared/Ai_Splithead_Update.h" // 0x800CF818

#include "maps/shared/Ai_Splithead_Init.h" // 0x800CF8D8

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800CF990_1_s05); // 0x800CF990

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800CFE94_1_s05); // 0x800CFE94

#include "maps/shared/sharedFunc_800D0054_1_s05.h" // 0x800D0054

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D00D0);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D0948);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D11A0);

void func_800D17BC(s_SubCharacter* chara) // 0x800D17BC
{
    q19_12 moveSpeed;
    q19_12 newSpeed;
    s32    vol;
    s32    timer0;
    s16    timer1;
    s16    timer1_div6;

    moveSpeed = chara->moveSpeed_38;
    if (moveSpeed > Q12(0.0f))
    {
        newSpeed = MAX(moveSpeed - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.5997f), Q12_SHIFT), Q12(0.0f));
    }
    else
    {
        newSpeed = MIN(moveSpeed + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.5997f), Q12_SHIFT), Q12(0.0f));
    }
    chara->moveSpeed_38 = newSpeed;

    switch (chara->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(11, false):
        case ANIM_STATUS(11, true):
            chara->properties_E4.splitHead.flags_E8 |= 1 << 3;

            if (!func_800D4530(chara))
            {
                break;
            }

        case ANIM_STATUS(10, true):
            chara->model_0.anim_4.status_0 = ANIM_STATUS(1, false);
            Sd_EngineCmd(Sfx_Unk1477);
            break;

        case ANIM_STATUS(1, false):
        case ANIM_STATUS(1, true):
            timer0 = chara->properties_E4.splitHead.timer_F4;
            timer1 = D_800D5880;
            timer1_div6 = timer1 / 6;

            if (timer0 < timer1_div6)
            {
                vol = (timer0 << 7) / timer1_div6;
            }
            else if (((timer1 * 5) / 6) < timer0)
            {
                vol = ((D_800D5880 - timer0) << 7) / timer1_div6;
            }
            else
            {
                vol = 0x80;
            }

            func_8005DE0C(Sfx_Unk1477, &chara->position_18, vol, Q12(16.0f), 0);

            if (chara->properties_E4.splitHead.timer_F4 > D_800D5880)
            {
                D_800D5880 = Q12(3.8f);
                chara->model_0.state_2 = 5;
                chara->properties_E4.splitHead.timer_F4 = Q12(0.0f);
                chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);

                func_8004690C(Sfx_Unk1477);
                break;
            }

            chara->properties_E4.splitHead.timer_F4 += g_DeltaTime0;
            break;
    }
}

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D19B8);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D2214);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D2444);

void func_800D263C(s_SubCharacter* chara) // 0x800D263C
{
    if (Savegame_EventFlagGet(EventFlag_130))
    {
        chara->model_0.state_2 = 2;
        chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
        chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 0x100;
    }
}

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D267C_1_s05); // 0x800D267C

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D274C_1_s05); // 0x800D274C

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D2D74_1_s05); // 0x800D2D74

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D3388);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D3AFC_1_s05); // 0x800D3AFC

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D3B30_1_s05); // 0x800D3B30

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D4070_1_s05); // 0x800D4070

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D4408);

void func_800D450C(s32 arg0, s32 arg1) // 0x800D450C
{
    sharedData_800D8614_1_s05 += arg0;
    sharedData_800D8616_1_s05 += arg1;
}

s32 func_800D4530(s_SubCharacter* chara) // 0x800D4530
{
    q20_12 timer;
    s32    ret;

    timer = chara->properties_E4.player.runTimer_F8;

    ret = 0;
    if ((timer > Q12(198.0f) && chara->model_0.anim_4.time_4 < Q12(175.0f)) ||
        (timer < Q12(175.0f) && chara->model_0.anim_4.time_4 > Q12(198.0f)))
    {
        ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D4594);

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D489C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D48AC

void func_800D494C(void) // 0x800D494C
{
    s32 var_a0;

    var_a0 = 1;
    if (g_SysWork.npcs_1A0[0].health_B0 > 0)
    {
        var_a0 = 2;
        if (g_SysWork.npcs_1A0[0].properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x10)
        {
            var_a0 = 6;
        }
    }

    func_80035F4C(var_a0, Q12(0.1f), &D_800D5C3C);
}

void func_800D49A4(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
};

void func_800D49AC(void) // 0x800D49AC
{
    s32 i;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (g_SysWork.sysStateStep_C[0] >= 3)
        {
            D_800D8568.field_1  = 0;
            D_800D8568.field_10 = 0;

            for (i = 0; i < ARRAY_SIZE(sharedData_800E1FF8_1_s02); i++)
            {
                s32 field_A = sharedData_800E1FF8_1_s02[i].field_A;
                if (field_A < 12)
                {
                    if (field_A >= 8)
                    {
                        sharedData_800E1FF8_1_s02[i].field_A = 12;
                    }
                }
            }

            vcReturnPreAutoCamWork(true);
            SysWork_StateStepReset();
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            g_SysWork.field_30   = 20;
            g_SysWork.field_2378 = 0;

            // Warp camera.
            Camera_PositionSet(NULL, Q12(19.72f), Q12(-5.2f), Q12(-27.6f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(19.72f), Q12(-3.3f), Q12(-24.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 2:
            D_800D8568.field_1 = 3;
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
            break;

        case 4:
            g_SysWork.field_2378 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.225f, Q12_SHIFT);
            if (g_SysWork.field_2378 > Q12(2.25f))
            {
                g_SysWork.field_2378 = Q12(2.25f);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 5:
            g_SysWork.field_2378 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.45f, Q12_SHIFT);
            if (g_SysWork.field_2378 < Q12(1.3843f))
            {
                Savegame_EventFlagSet(EventFlag_129);
                SysWork_StateStepReset();
            }
            break;

        default:
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);

            g_SysWork.field_2378 = Q12(1.3843f);

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(false);

            Savegame_EventFlagSet(EventFlag_130);
            func_8003A16C();
            break;
    }
}

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D4D1C);

void func_800D525C(void) // 0x800D525C
{
    D_800D86F8[0] = 0;
    D_800D86F8[1] = 0;
    D_800D86FC[0] = 0x40;
    D_800D86FC[1] = 0x40;
    D_800D8568.field_0 = 9;
    D_800D8568.field_C = 0x12C;
    D_800D8568.field_12 = -0x2CCCu;
    D_800D8568.field_14 = -0x800;
    D_800D8568.field_1C = 0xA00;
    D_800D8568.field_E = -0x1000;
    D_800D8568.field_4 = 0x80;
    D_800D8568.field_5 = 0xC4;
    D_800D8568.field_6 = 0x3C;
    D_800D8568.field_8 = 0x200;
    D_800D8568.field_A = 0x400;
    D_800D8568.field_1 = 2;
    D_800D8568.field_2 = 8;
    D_800D8568.field_3 = 0x40;
    D_800D8568.field_20 = Q12(19.7f);
    D_800D8568.field_24 = Q12(-19.1f);
    D_800D86FE = 48;

    if (Savegame_EventFlagGet(EventFlag_130))
    {
        g_SysWork.field_2378 = Q12(1.3843f);
        D_800D8568.field_1 = 0;
    }

    func_800CAAD0();
    WorldObjectInit(&g_WorldObject0, 19.7f, 1.58f, -19.1f, 0.0f, 0.0f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObject0.object_0, "SPHERE_H");

    WorldObjectInit(&g_WorldObject1, 19.7f, -0.06f, -19.1f, 0.0f, 0.0f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObject1.object_0, "WHEEL_HI");

    g_SysWork.field_235C = NULL;
    g_SysWork.field_2360.vx = Q12(19.7f);
    g_SysWork.field_2360.vy = Q12(-3.0f);
    g_SysWork.field_2360.vz = Q12(-19.1f);

    g_SysWork.field_236C = NULL;
    g_SysWork.field_2370.vx = Q12(-0.25f);
    g_SysWork.field_2370.vy = Q12(0.0f);
    g_SysWork.field_2370.vz = Q12(0.0f);

    Sd_EngineCmd(Sfx_Unk1478);
}

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D5400);

INCLUDE_RODATA("asm/maps/map1_s05/nonmatchings/map1_s05", D_800CAAC4);
