#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map6/map6_s02.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800CDEB0

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800CDEC4

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800CDF08

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800CDF20

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800CDF2C

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800CDF40

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800CDF54

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800CDF68

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800CDFF4

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800CE658

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800CE66C

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800CE680

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800CE77C

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800CE810

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800CE81C

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CE87C

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800CE88C);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800CEA88);

void func_800CED6C(void) {}

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800CED74);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800CEF88);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800CF01C);

void func_800CF0B0(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.0)\t...! ~E ",
    "~J0(1.0)\tWait! ~E ",
    "~J0(1.7)\tDamn! ~N\n\t\t\tI_was_too_late? ~E ",
    "~J0(1.5)\tSorry... ",
    "~J0(0.6)\tAh... ",
    "~J0(1.5)\t_ ",
    "~J0(3.6)\tLet_me_ask_you,_have_you_seen ~N\n\t\t\ta_little_girl_around_here? ~E ",
    "~J0(2.8)\tShort,_black_hair... ~E ",
    "~J0(1.0)\tWhat? ~E ",
    "~J0(2.5)\tThat_light!? ~E "
};

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800CF0B8);

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800CFB9C

void func_800CFC34(void) // 0x800CFC34
{
    s32 i;
    s32 curTimerVal;
    s32 pitch;
    s32 pitchDiv512;

    curTimerVal = D_800D3C90;
    pitch       = (Math_Sin(curTimerVal >> 3) * 2) + Math_Cos(curTimerVal >> 4) + Math_Sin(Math_Cos(curTimerVal >> 4));

    D_800D3C90 += g_DeltaTime0;
    D_800D3C90 += g_DeltaTime0;

    pitchDiv512 = pitch >> 9; // `/ 512`

    if (g_SysWork.sysStateStep_C[0] == 11 || g_SysWork.sysStateStep_C[0] == 13)
    {
        D_800D3C94 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.5f, Q12_SHIFT);
        if (D_800D3C94 < 0)
        {
            D_800D3C94 = 0;
        }
        func_800463C0(Sfx_Unk1467, 0, ~(D_800D3C94 >> 4), pitchDiv512);
    }
    else if (g_SysWork.sysStateStep_C[0] > 0)
    {
        D_800D3C94 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.25f, Q12_SHIFT);
        if (D_800D3C94 > 4080)
        {
            D_800D3C94 = 4080;
        }
        func_800463C0(Sfx_Unk1467, 0, ~(D_800D3C94 >> 4), pitchDiv512);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8004690C(Sfx_Unk1611);

            if (Savegame_EventFlagGet(EventFlag_456) && Savegame_EventFlagGet(EventFlag_457) &&
                Savegame_EventFlagGet(EventFlag_458) && Savegame_EventFlagGet(EventFlag_459))
            {
                Savegame_EventFlagSet(EventFlag_469);
            }

            D_800D3C88 = 0;
            Fs_QueueStartReadTim(FILE_TIM_ENBAN_TIM, FS_BUFFER_1, &D_800D3B70);
            Fs_QueueStartRead(FILE_ANIM_UFO5_DMS, FS_BUFFER_13);

            D_800D4E28 = NO_VALUE;

            ScreenFade_ResetTimestep();

            Sd_EngineCmd(Sfx_Unk1467);
            func_800463C0(Sfx_Unk1467, 0, 255, 0);

            D_800D3C94 = 0;
            D_800D3C90 = 0;
            Savegame_EventFlagSet(EventFlag_417);

            D_800D3C8C = 0;
            SysWork_StateStepIncrement();

        case 1:
            func_80085DF0();
            break;

        case 2:
            if (Fs_QueueDoThingWhenEmpty())
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 3:
            D_800D4E28 = 0;
            SysWork_StateStepIncrementAfterFade(0, true, 3, Q12(0.0f), false);
            DmsHeader_FixOffsets(FS_BUFFER_13);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            Game_TurnFlashlightOn();
            SysWork_StateStepIncrement();

        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);

        case 5:
            Map_MessageWithAudio(23, &D_800D3C88, &D_800D3B6C);
            break;

        case 6:
            SysWork_StateStepIncrementAfterTime(&D_800D4E28, Q12(40.0f), Q12(0.0f), Q12(30.0f), true, true);

            for (i = 0; i < 15; i++)
            {
                func_800CABA0(&D_800D3B78[i], Q12(0.5f), 0xCC, 0);
            }
            break;

        case 7:
            if (Savegame_EventFlagGet(EventFlag_469))
            {
                Fs_QueueStartReadTim(FILE_TIM_UFO1_TIM, FS_BUFFER_1, &D_800D3B44[0]);
                Fs_QueueStartReadTim(FILE_TIM_UFO6_TIM, FS_BUFFER_1, &D_800D3B44[1]);
            }
            SysWork_StateStepIncrement();

        case 8:
            MapMsg_DisplayAndHandleSelection(false, 24, 0, 0, 0, false);
            for (i = 0; i < 15; i++)
            {
                func_800CABA0(&D_800D3B78[i], Q12(0.5f), 0xCC, 0);
            }
            break;

        case 9:
            func_80080B58(&g_SysWork.playerBoneCoords_890[HarryBone_Head], &(SVECTOR){}, &(VECTOR3) { Q12(5.39f), Q12(-19.0f), Q12(-16.34f) });

            for (i = 0; i < 15; i++)
            {
                func_800CABA0(&D_800D3B78[i], Q12(0.5f), 0x266, 0);
            }

            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);

            if (g_SysWork.sysStateStep_C[0] != 9)
            {
                Savegame_EventFlagSet(EventFlag_412);
            }
            break;

        case 10:
            if (D_800D3C8C > Q12(8.0f))
            {
                if (Savegame_EventFlagGet(EventFlag_469))
                {
                    SysWork_NextStateStepSet(12);
                }
                else
                {
                    SysWork_NextStateStepSet(11);
                }
            }
            break;

        case 11:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);

            if (g_SysWork.sysStateStep_C[0] != 11)
            {
                SysWork_StateStepReset();
            }
            break;

        case 12:
            SysWork_StateStepIncrementDelayed(Q12(4.0f), false);

            if (g_SysWork.sysStateStep_C[0] != 12)
            {
                SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            }
            break;

        case 13:
            SysWork_StateStepIncrementAfterFade(2, true, 1, Q12(1.0f), false);
            break;

        default:
            vcReturnPreAutoCamWork(true);
            Savegame_EventFlagSet(EventFlag_460);
            func_80086470(3, InventoryItemId_ChannelingStone, 1, false);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            D_800D4E28 = NO_VALUE;

            if (Savegame_EventFlagGet(EventFlag_469))
            {
                SysWork_StateSetNext(SysState_Gameplay);
                D_800C4414 &= ~(1 << 5);
            }
            else
            {
                SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
                sharedFunc_800D2244_0_s00(false);

                SysWork_StateSetNext(SysState_Gameplay);

                Sd_EngineCmd(Sfx_Unk1611);
                func_8004690C(Sfx_Unk1467);
            }
            break;
    }

    if (g_SysWork.sysStateStep_C[0] == 10 || g_SysWork.sysStateStep_C[0] == 12 || g_SysWork.sysStateStep_C[0] == 13)
    {
        D_800D3C8C += g_DeltaTime0;

        for (i = 0; i < 15; i++)
        {
            if (Savegame_EventFlagGet(EventFlag_469) || D_800D3C8C < D_800D3C2C[i])
            {
                func_800CABA0(&D_800D3B78[i], Q12(0.5f), 0xCC, 0);

                if (D_800D3C8C > Q12(1.5f))
                {
                    D_800D3B78[i].vx += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 3.5f, 12);
                    D_800D3B78[i].vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.2f, 12);
                    D_800D3B78[i].vz += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, -0.2f, 12);
                }
            }
        }
    }

    if (D_800D4E28 >= 0)
    {
        // TODO: Remove null chars from "HERO" once later rodata is added.
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, "HERO\0\0\0\0", D_800D4E28, FS_BUFFER_13);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800D4E0C, &D_800D4E1C, NULL, D_800D4E28, FS_BUFFER_13));
        vcUserCamTarget(&D_800D4E0C, NULL, true);
        vcUserWatchTarget(&D_800D4E1C, NULL, true);
    }
}

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D0500);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D1040);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D1330);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D1658);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D1718);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D1AE4);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D1D40);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D1EB8);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D2170);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D2364);

INCLUDE_ASM("asm/maps/map6_s02/nonmatchings/map6_s02_2", func_800D32D0);

INCLUDE_RODATA("asm/maps/map6_s02/nonmatchings/map6_s02_2", D_800CAB90);

INCLUDE_RODATA("asm/maps/map6_s02/nonmatchings/map6_s02_2", D_800CAB98);
