#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "maps/map0/map0_s01.h"
#include "maps/shared.h"

//INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01_events", func_800DA980);
//
//

#define StateStepIncrement_afterTime sharedFunc_800DA8E8_0_s01
void StateStepIncrement_afterTime(s32* timer, s32 incBy, s32 minTime, s32 maxTime, s32 setTimerToMax, s32 incrementStateIndex);

extern VECTOR3 g_cutsceneCameraLookAt;
extern s32 g_timer1;
extern u8 g_SdCmdIndex;
extern const VECTOR3 D_800CC8FC;
extern const char D_800CC908[];
extern const char D_800CC910[];

void func_800DA980()
{
    s_SubCharacter* chara0;
    s_SubCharacter* chara1;
    u8 temp_s0_5;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 &&
        g_SysWork.sysStateStep_C > 5 &&
        g_SysWork.sysStateStep_C < 47)
    {
        SysWork_NextStateStepSet(52);
    }
    
    switch (g_SysWork.sysStateStep_C)
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            
            g_SysWork.field_30 = 20;
            g_Gfx_ScreenFade = 4;
            g_SysWork.flags_22A4 |= 1 << 3;
            g_SavegamePtr->flags_AC &= ~(1 << 0);
            g_SysWork.flags_22A4 |= (1 << 5) | (1 << 9);
            g_SdCmdIndex = 0;
            D_800DE250 = 0;
            D_800DE251 = 0;
            
            Fs_QueueStartRead(FILE_ANIM_CAFE_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_11);
            Chara_Load(0, Chara_Cybil, &g_SysWork.npcCoords_FC0[0], NO_VALUE, NULL, NULL);
            func_80088D0C();
            Chara_Spawn(Chara_Cybil, 0, FP_METER(4.4f), FP_METER(269.9f), FP_METER(0.0f), 2);
            
            g_timer1 = 0;
            SysWork_StateStepIncrement();
        
        case 1:
            func_80087EDC(9);
            break;
        
        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x4D, false);
            func_8008616C(0, 0, 0, 0, 0);
            func_800D2054();
            SysWork_StateStepIncrement();
            break;
        
        case 3:
            func_80085EB8(2, &g_SysWork.player_4C.chara_0, NULL, false);
            SysWork_StateStepIncrement();
        
        case 4:
            func_8008616C(1, 0, 0, 0, 0);
            break;
        
        case 5:
            func_80085EB8(3, &g_SysWork.player_4C.chara_0, NULL, false);
            SysWork_StateStepIncrement();
        
        case 6:
            StateStepIncrement_afterTime(&g_timer1, 0x7CCC, 0, 0x5000, false, true);
            break;
        
        case 7:
            StateStepIncrement_afterTime(&g_timer1, 0x7CCC, 0, 0x1A000, true, false);
            func_800869E4(15, &g_SdCmdIndex, g_SdCmdTable); // was i dreaming ?
            break;
        
        case 8:
            StateStepIncrement_afterTime(&g_timer1, 0x7CCC, 0, 0x1A000, true, true);
            break;
        
        case 9:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x4E, false);
            D_800DE250 = 1;
            SysWork_StateStepIncrement();
        
        case 10:
        case 11:
        case 12:
        case 13:
            switch (g_SysWork.sysStateStep_C)
            {
                case 10:
                    func_800869E4(16, &g_SdCmdIndex, g_SdCmdTable); // how do you feel ?
                    break;
                
                case 11:
                    func_800869E4(17, &g_SdCmdIndex, g_SdCmdTable); // like i've been hit...
                    break;

                case 12:
                    if (g_timer1 == 0x30000 && D_800DE251 == 2)
                    {
                        SysWork_NextStateStepSet(13);
                    }
                    break;
                
                case 13:
                    func_800869E4(18, &g_SdCmdIndex, g_SdCmdTable); // glad to hear it.
                    break;
            }
            
            StateStepIncrement_afterTime(&g_timer1, 0x4000, 0x1B000, 0x30000, true, false);
            
            if (D_800DE251 == 0 && g_timer1 > 0x26000)
            {
                func_80085EB8(0, &g_SysWork.npcs_1A0[0], 0xA, false);
                func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x6E, false);
                
                D_800DE251++;
            }
            
            temp_s0_5 = D_800DE251;
            if (D_800DE251 == 1 && sharedFunc_800D8964_0_s00(&g_SysWork.npcs_1A0[0]) == temp_s0_5)
            {
                func_80085EB8(0, &g_SysWork.npcs_1A0[0], 0xB, false);
                D_800DE251++;
            }
            break;
        
        case 14:
            StateStepIncrement_afterTime(&g_timer1, 0x3000, 0x31000, 0x8B000, true, false);
            func_800869E4(25, &g_SdCmdIndex, g_SdCmdTable); // have you seen a little girl?
            break;
        
        case 15:
            g_timer1 = 0x8C000;
            SysWork_StateStepIncrement();
        
        case 16:
            func_800869E4(35, &g_SdCmdIndex, g_SdCmdTable); // whats your name ?
            break;
        
        case 17:
            func_80085E6C(0x1333, 0);
            break;
        
        case 18:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x5D, false);
            SysWork_StateStepIncrement();
        
        case 19:
            StateStepIncrement_afterTime(&g_timer1, 0xA000, 0x8D000, 0x98000, false, true);
            break;
        
        case 20:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x35, false);
            SysWork_StateStepIncrement();
        
        case 21:
            StateStepIncrement_afterTime(&g_timer1, 0xA000, 0x8D000, 0x9F000, true, true);
            func_8004729C(4108);
            break;
        
        case 22:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 7, false);
            Sd_EngineCmd(4108);
            SysWork_StateStepIncrement();
        
        case 23:
            StateStepIncrement_afterTime(&g_timer1, 0xA000, 0xA0000, 0xAD000, true, false);
            MapMsg_DisplayAndHandleSelection(0, 0x2B, 0, 0, 0, 0);
            Gfx_DebugStringPosition(30, 30);
            break;
        
        case 24:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x47, false);
            SysWork_StateStepIncrement();
        
        case 25:
            StateStepIncrement_afterTime(&g_timer1, 0xA000, 0xAE000, 0xB8000, true, false);
            func_800869E4(44, &g_SdCmdIndex, g_SdCmdTable);
            break;
            
        case 26:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x33, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 8, 0);
            SysWork_StateStepIncrement();
        
        case 27:
            StateStepIncrement_afterTime(&g_timer1, 0xA000, 0xB9000, 0xC2000, true, false);
            func_800869E4(45, &g_SdCmdIndex, g_SdCmdTable);
            break;
        
        case 28:
            g_timer1 = 0xC3000;
            
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);
            SysWork_StateStepIncrement();
        
        case 29:
            func_800869E4(46, &g_SdCmdIndex, g_SdCmdTable); // it's dangerous out there
            break;
            
        case 30:
            func_80085E6C(0x1800, 0);
            break;
            
        case 31:
            func_800869E4(49, &g_SdCmdIndex, g_SdCmdTable);
            break;
            
        case 32:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 1, false);
            SysWork_StateStepIncrement();
        
        case 33:
            StateStepIncrement_afterTime(&g_timer1, 0x14000, 0xCF000, 0xDE000, true, true);
            break;
        
        case 34:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 6, false);
            SysWork_StateStepIncrement();
        
        case 35:
            StateStepIncrement_afterTime(&g_timer1, 0x5000, 0xDF000, 0xFB000, true, false);
            func_800869E4(0x33, &g_SdCmdIndex, g_SdCmdTable);
            break;
        
        case 36:
            StateStepIncrement_afterTime(&g_timer1, 0x5000, 0xDF000, 0xFB000, true, false);
            func_80085E6C(0x999, 0);
            break;
        
        case 37:
            StateStepIncrement_afterTime(&g_timer1, 0x5000, 0xDF000, 0xFB000, true, false);
            func_800869E4(0x37, &g_SdCmdIndex, g_SdCmdTable);
            break;
        
        case 38:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 9, false);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x4C, false);
            SysWork_StateStepIncrement();
        
        case 39:
            StateStepIncrement_afterTime(&g_timer1, 0xA000, 0xFC000, 0x118000, true, false);
            func_800869E4(0x39, &g_SdCmdIndex, g_SdCmdTable);
            break;
        
        case 40:
            StateStepIncrement_afterTime(&g_timer1, 0xA000, 0xFC000, 0x118000, true, true);
            break;
        
        case 41:
            func_80085EB8(0, g_SysWork.npcs_1A0, 5, false);
            SysWork_StateStepIncrement();
        
        case 42:
            StateStepIncrement_afterTime(&g_timer1, 0xA000, 0x119000, 0x128000, true, true);
            break;
        
        case 43:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x33, false);
            g_timer1 = 0x129000;
            SysWork_StateStepIncrement();
        
        case 44:
            func_800869E4(0x3A, &g_SdCmdIndex, g_SdCmdTable);
            break;
        
        case 45:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x5A, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 1, false);
            SysWork_StateStepIncrement();
        
        case 46:
            StateStepIncrement_afterTime(&g_timer1, 0xA000, 0x120000 | 0xA000, 0x134000, true, true);
            break;
        
        case 47:
            D_800DE250 = 0;
            
            func_8005DC1C(1357, &D_800CC8FC, 0x80, 0);
            SysWork_StateStepIncrement();
        
        case 48:
            func_80088F94(g_SysWork.npcs_1A0,0 ,0);
            Sd_EngineCmd(19);
            Chara_Load(0, Chara_AirScreamer, &g_SysWork.npcCoords_FC0[0], NO_VALUE, 0, 0);
            func_80086470(3, InventoryItemId_Handgun, 15, false); // TODO: 15 bullets default. One func has a constant for this.
            SysWork_StateStepIncrement();
        
        case 49:
            func_8008616C(2, 1, 0, 0, 0);
            break;
        
        case 50:
            g_timer1 = 0x134000;
            func_80085E6C(0x800, 0);
            break;
        
        case 51:
            SysWork_StateStepReset();
            break;
        
        case 52:
            func_8008616C(2, 1, 0, 0, 0);
            break;
        
        case 53:
            //SysWork_NextStateStepSet(48); // TODO: Doesn't match?
            g_SysWork.sysStateStep_C = 48;
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            break;
        
        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(0);
            
            vcReturnPreAutoCamWork(1);
            func_8008616C(0, false, 2, 0, false);
            func_8008616C(0, false, 0, 0, false);
            Sd_EngineCmd(23);
            
            g_SavegamePtr->eventFlags_168[1] |= 1 << 17;
            g_timer1 = NO_VALUE;
            break;
    }
    
    if (g_timer1 >= 0)
    {
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_cutsceneCameraTarget, &g_cutsceneCameraLookAt, NULL, g_timer1, FS_BUFFER_11));
        vcUserCamTarget(&g_cutsceneCameraTarget, NULL, true);
        vcUserWatchTarget(&g_cutsceneCameraLookAt, NULL, true);
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, &D_800CC908, g_timer1, FS_BUFFER_11);
        
        if (D_800DE250 != 0)
        {
            chara0 = &g_SysWork.npcs_1A0[0];
            chara0->model_0.anim_4.flags_2 |= AnimFlag_Visible;
            Dms_CharacterGetPosRot(&chara0->position_18, &chara0->rotation_24, &D_800CC910, g_timer1, FS_BUFFER_11);
            return;
        }
        
        chara1 = &g_SysWork.npcs_1A0[0];
        chara1->model_0.anim_4.flags_2 &= ~AnimFlag_Visible;
    }
}

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01_events", func_800DB790);
const VECTOR3 D_800CCA1C = {
    0x00000CCC,
    0xFFFFE99A,
    0x0010BB33,
};
const VECTOR3 D_800CCA28 = {
    0x000004CC,
    0xFFFFE99A,
    0x0010BB33,
};
const VECTOR3 D_800CCA34 = {
    0x00000CCC,
    0xFFFFE334,
    0x0010BB33,
};
const VECTOR3 D_800CCA40 = {
    0x00000CCC,
    0xFFFFE99A,
    0x00111E66,
};
const VECTOR3 D_800CCA4C = {
    0x000004CC,
    0xFFFFE99A,
    0x00111E66,
};
const VECTOR3 D_800CCA58 = {
    0x00000CCC,
    0xFFFFE334,
    0x00108199,
};

const char D_800CCA64[] = "BIRD";

#define EventPositionInit(eventPos, x, y, z, arg4, arg5) \
    EventPositionSet(eventPos, FP_METER(x), FP_METER(y), FP_METER(z), arg4, arg5)

static inline void EventPositionSet(s_EventPosition* eventPos, s32 x, s32 y, s32 z, s32 arg4, s16 arg5)
{
    Math_Vector3Set(&eventPos->position_0, x, y, z);
    eventPos->field_C  = arg4;
    eventPos->field_10 = arg5;
}

void func_800DBAA0() // 0x800DBAA0
{
    s32 var_a1;

    switch (g_SysWork.sysStateStep_C)
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8003A16C();

            Savegame_EventFlagSetAlt(EventFlag_50);

            Sd_EngineCmd(1321);
            Sd_EngineCmd(1322);

            Savegame_EventFlagSetAlt(EventFlag_52);

            // Warp player.
            g_SysWork.player_4C.chara_0.position_18.vx = FP_METER(1.3f);
            g_SysWork.player_4C.chara_0.position_18.vz = FP_METER(269.7f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(5.0f);

            g_timer1 = Q19_12(26.0f);

            func_8008616C(0, true, 3, 0, false);

            g_SdCmdIndex = 0;
            SysWork_StateStepIncrement();

        case 1:
            func_80087EDC(30);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 91, 0);
            SysWork_StateStepIncrement();

        case 4:
            var_a1     = g_timer1 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q19_12(15.0f), Q12_SHIFT);
            g_timer1 = MIN(var_a1, Q19_12(37.0f));
            if (g_timer1 >= Q19_12(37.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 5:
            func_800869E4(0x3E, &g_SdCmdIndex, &D_800DE124);
            break;

        case 6:
            func_80085E6C(FP_TIME(0.5f), false);
            break;

        case 7:
            func_800869E4(0x3F, &g_SdCmdIndex, &D_800DE124);
            break;

        case 8:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 92, false);
            SysWork_StateStepIncrement();

        case 9:
            var_a1     = g_timer1 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q19_12(15.0f), Q12_SHIFT);
            g_timer1 = MIN(var_a1, Q19_12(52.0f));
            if (g_timer1 >= Q19_12(52.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 10:
            g_timer1 = MAX(g_timer1, Q19_12(53.0f));
            D_800E23A1 = 0x80;
            Savegame_EventFlagSetAlt(EventFlag_45);
            
            func_80085E6C(FP_TIME(1.5f), false);
            break;

        case 11:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 53, false);
            SysWork_StateStepIncrement();

        case 12:
            var_a1     = g_timer1 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q19_12(15.0f), Q12_SHIFT);
            g_timer1 = MIN(var_a1, Q19_12(75.0f));

            if (g_timer1 >= Q19_12(75.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 13:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 89, false);

            D_800E23A1 = 0xE0;
            Savegame_EventFlagSetAlt(EventFlag_46);
            g_timer1 = Q19_12(76.0f);

            SysWork_StateStepIncrement();

        case 14:
            var_a1     = g_timer1 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q19_12(18.0f), Q12_SHIFT);
            g_timer1 = MIN(var_a1, Q19_12(115.0f));
            if (g_timer1 >= Q19_12(115.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 15:
            func_800CCB8C(&D_800CCA1C, &D_800CCA28, 0x2800, 0xCC, 0x999, 0x666, 0x199, 0);
            func_8005DC1C(1373, &D_800CCA34, 128, 0);
            SysWork_StateStepIncrement();

        case 16:
            var_a1     = g_timer1 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q19_12(18.0f), Q12_SHIFT);
            g_timer1 = MIN(var_a1, Q19_12(146.0f));
            if (g_timer1 >= Q19_12(146.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 17:
            func_800CCB8C(&D_800CCA40, &D_800CCA4C, 0x3000, 0x147, 0x666, 0x666, 0xED, 0);
            func_8005DC1C(1374, &D_800CCA58, 128, 0);
            func_8005DC1C(1375, &D_800CCA58, 128, 0);
            SysWork_StateStepIncrement();

        case 18:
            var_a1     = g_timer1 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q19_12(18.0f), Q12_SHIFT);
            g_timer1 = MIN(var_a1, Q19_12(147.0f));
            if (g_timer1 >= Q19_12(147.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 19:
            func_800D3AC0(g_SysWork.npcs_1A0);
            SysWork_StateStepIncrement();

        case 20:
            var_a1     = g_timer1 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q19_12(18.0f), Q12_SHIFT);
            g_timer1 = MIN(var_a1, Q19_12(154.0f));
            if (g_timer1 >= Q19_12(154.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 21:
            Savegame_EventFlagSetAlt(EventFlag_47);
            func_800D39F4(g_SysWork.npcs_1A0);
            func_8008616C(0, false, 2, 0, false);

            g_timer1 = NO_VALUE;

            vcReturnPreAutoCamWork(1);

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(0);
            func_800D2094();

            g_SysWork.flags_22A4 &= ~(1 << 5);
            g_SysWork.flags_22A4 &= ~(1 << 9);
            break;
    }

    if (g_timer1 >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, &D_800CC908, g_timer1, FS_BUFFER_11);

        if (g_SysWork.sysStateStep_C >= 20)
        {
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, D_800CCA64, g_timer1, FS_BUFFER_11);
            g_SysWork.npcs_1A0[0].position_18.vx += FP_MULTIPLY(Math_Sin(g_SysWork.npcs_1A0[0].rotation_24.vy), FP_METER(0.2f), Q12_SHIFT);
            g_SysWork.npcs_1A0[0].position_18.vz += FP_MULTIPLY(Math_Cos(g_SysWork.npcs_1A0[0].rotation_24.vy), FP_METER(0.2f), Q12_SHIFT);
        }

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_cutsceneCameraTarget, &g_cutsceneCameraLookAt, NULL, g_timer1, FS_BUFFER_11));
        vcUserCamTarget(&g_cutsceneCameraTarget, NULL, true);
        vcUserWatchTarget(&g_cutsceneCameraLookAt, NULL, true);
    }
}

void Event_PocketRadioItemTake() // 0x800DC34C
{
    Event_ItemTake(InventoryItemId_PocketRadio, 1, 37, 64);
    g_SavegamePtr->flags_AC |= 1 << 0;
}

void Event_FlashlightItemTake() // 0x800DC394
{
    Event_ItemTake(InventoryItemId_Flashlight, 1, 36, 61);
    Game_TurnFlashlightOff();
}

void Event_MapItemTake() // 0x800DC3C8
{
    static const RECT IMG_BUFFER_RECT = { 320, 256, 160, 240 };

    switch (g_SysWork.sysStateStep_C)
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + D_800A99B5);
            SysWork_StateStepIncrement();

        case 1:
            func_8008616C(2, true, 0, 0, false);
            break;

        case 2:
            DrawSync(0);
            StoreImage(&IMG_BUFFER_RECT, IMAGE_BUFFER);
            DrawSync(0);
            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + D_800A99B5, FS_BUFFER_2, &g_MapImg);
            Gfx_Init(SCREEN_WIDTH, 1);

            g_IntervalVBlanks = 1;

            GsSwapDispBuff();
            func_8008616C(0, false, 0, 0, false);
            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrement();

        case 3:
            g_BackgroundColor = 88;

            Gfx_BackgroundSpriteDraw(&g_MapImg);
            MapMsg_DisplayAndHandleSelection(true, 59, 6, 4, 0, false);
            break;

        case 5:
            LoadImage(&IMG_BUFFER_RECT, IMAGE_BUFFER);
            DrawSync(0);
            Gfx_Init(SCREEN_WIDTH, 0);
            func_8008616C(0, false, 0, 0, false);
            SysWork_StateStepReset();
            break;

        case 6:
            g_SavegamePtr->hasMapsFlags_164 |= 1 << 1;

            Fs_QueueStartRead(FILE_ANIM_CAFE2_DMS, FS_BUFFER_11);
            SysWork_StateStepIncrement();

        case 4:
        case 7:
            g_BackgroundColor = 88;

            Gfx_BackgroundSpriteDraw(&g_MapImg);
            func_8008616C(2, true, 0, 0, false);
            break;

        case 8:
            LoadImage(&IMG_BUFFER_RECT, IMAGE_BUFFER);
            DrawSync(0);
            Gfx_Init(SCREEN_WIDTH, 0);
            func_8008616C(0, false, 0, 0, false);
            SysWork_StateStepIncrement();

        case 9:
            func_80088D0C();
            SysWork_StateStepIncrement();

        case 10:
            // Set cutscene character.
            Chara_Spawn(Chara_AirScreamer, 0, FP_METER(0.0f), FP_METER(0.0f), FP_METER(0.0f), 12);
            DmsHeader_FixOffsets(FS_BUFFER_11);
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, D_800CCA64, 0, FS_BUFFER_11);

            // Set camera.
            vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_cutsceneCameraTarget, &g_cutsceneCameraLookAt, NULL, 0, FS_BUFFER_11));
            vcUserCamTarget(&g_cutsceneCameraTarget, NULL, true);
            vcUserWatchTarget(&g_cutsceneCameraLookAt, NULL, true);

            // Warp player.
            g_SysWork.player_4C.chara_0.position_18.vx = FP_METER(4.585938f);
            g_SysWork.player_4C.chara_0.position_18.vz = FP_METER(267.285156f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(90.0f);

            // Set flags.
            g_SysWork.field_2290             |= 1 << 0;
            g_SysWork.field_228C             |= 1 << 0;
            g_SavegamePtr->eventFlags_168[1] |= 1 << 6;

            SysWork_StateStepIncrement();

        case 11:
            func_8008616C(1, false, 0, 0, false);
            break;

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(0);
            break;
    }
}

void Event_KitchenKnifeItemTake() // 0x800DC830
{
    Event_ItemTake(InventoryItemId_KitchenKnife, 1, 35, 60);
}

/** Presumably a pickup function. Maybe debug or something unused and commented out. */
void Event_EmptyFunction() {}

void Event_HealthItemTake() // 0x800DC864
{
    s32 globalPickupId;
    u32 pickupType;

    pickupType     = CommonPickupItemId_FirstAidKit;
    globalPickupId = 0;

    switch (g_MapEventParam->field_5)
    {
        case 13:
            pickupType     = CommonPickupItemId_HealthDrink;
            globalPickupId = 596;
            break;

        case 14:
            pickupType     = CommonPickupItemId_HealthDrink;
            globalPickupId = 597;
            break;
    }

    Event_CommonItemTake(pickupType, globalPickupId);
}

void Event_HandgunItemTake() // 0x800DC8C8
{
    switch (g_SysWork.sysStateStep_C)
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8004690C(Sfx_Unk1321);
            func_8004690C(Sfx_Unk1322);

            g_SavegamePtr->eventFlags_168[1] &= ~(1 << 20);
            g_SdCmdIndex                        = 0;
            SysWork_StateStepIncrement();

        case 1:
            func_800869E4(68, &g_SdCmdIndex, &D_800DE128); // This_is_not_a_dream!
            break;

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(SysState_Gameplay);

            g_SavegamePtr->eventFlags_168[1] |= 1 << 19;
            break;
    }
}

extern s_800BCE18_2BEC_0 D_800E23B0[1];
extern s_800BCE18_2BEC_0 D_800E23D0[1];
extern s_800BCE18_2BEC_0 D_800E23F0[3];
extern s_800BCE18_2BEC_0 D_800E2450[2];

extern s_EventPosition g_DefaultEventPosition;
extern s_EventThing g_EventThing4A0;
extern s_EventThing g_EventThing4D0;
extern s_EventThing g_EventThing500;
extern s_EventThing g_EventThing530;

void func_800DC9C8() // 0x800DC9C8
{
    D_800E23A1 = 224;
    Math_Vector3f(&g_DefaultEventPosition.position_0, 0.0f, 0.0f, 280.0f, Q12_SHIFT);

    func_8003C8F8(&D_800E23B0[0], "IN_BLD1_");
    func_8003C8F8(&D_800E23D0[0], "IN1_HIDE");
    func_8003C8F8(&D_800E23F0[0], "BRK_BLD1");
    func_8003C8F8(&D_800E23F0[1], "BRK_GLS1");
    func_8003C8F8(&D_800E23F0[2], "BRK_GLS2");
    func_8003C8F8(&D_800E2450[0], "OUT1_HID");
    func_8003C8F8(&D_800E2450[1], "OUT_BLD_");

    EventPositionInit(&g_EventThing4A0.eventPosition_1C, 5.089844f, -1.009766f, 274.119873f, 0x16C0000, 0);
    func_8003C8F8(&g_EventThing4A0.field_0, "KNIFE_HI");

    EventPositionInit(&g_EventThing4D0.eventPosition_1C, 5.179932f, -1.0f, 267.279785f, 0x4EEFFDE, 0);
    func_8003C8F8(&g_EventThing4D0.field_0, "FLASH_HI");

    EventPositionInit(&g_EventThing500.eventPosition_1C, 5.23999f, -1.0f, 267.209961f, 0x2880000, 0);
    func_8003C8F8(&g_EventThing500.field_0, "MAP_HIDE");

    EventPositionInit(&g_EventThing530.eventPosition_1C, 2.309815f, -0.599854f, 273.949951f, 0x6880000, 0);
    func_8003C8F8(&g_EventThing530.field_0, "RADIO_HI");

    if ((g_SavegamePtr->eventFlags_168[1] & ((1 << 8) | (1 << 15))) == (1 << 8))
    {
        g_SysWork.flags_22A4 |= (1 << 5) | (1 << 9);

        Chara_Load(0, Chara_AirScreamer, &g_SysWork.npcCoords_FC0, NO_VALUE, NULL, NULL);

        if (g_SavegamePtr->eventFlags_168[1] & (1 << 6))
        {
            func_80088D0C();
            Chara_Spawn(Chara_AirScreamer, 0, FP_METER(1048566.0f), FP_METER(280.0f), FP_METER(0.0f), 12);
            func_800D3A3C(&g_SysWork.npcs_1A0[0]);

            Fs_QueueStartRead(FILE_ANIM_CAFE2_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);
        }
    }

    if ((g_SavegamePtr->eventFlags_168[4] & ((1 << 6) | (1 << 31))) == (1 << 31))
    {
        func_8003ED74(6, 3);
    }

    g_timer1 = 0;
    D_800E2560 = 0;

    // There are 6 NPCs max. Maybe related?
    func_8003C8F8(&D_800E2570[0], D_800A99E4.field_8);
    func_8003C8F8(&D_800E2570[1], D_800A99E4.field_C);
    func_8003C8F8(&D_800E2570[2], D_800A99E4.field_10);
    func_8003C8F8(&D_800E2570[3], D_800A99E4.field_14);
    func_8003C8F8(&D_800E2570[4], D_800A99E4.field_18);
    func_8003C8F8(&D_800E2570[5], D_800A99E4.field_1C);
}


INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01_events", func_800DCCF4); // Set in map `header.func_40`.

void func_800DD2EC(s32 arg0) // 0x800DD2EC // called by func_800DCCF4 only
{
    static const SVECTOR3 DEFAULT_ROT = {};

    s32 i;

    if (arg0 == 0)
    {
        for (i = 0; i <= 0; i++)
        {
            func_8003C92C(&D_800E23D0[i], &g_DefaultEventPosition, &DEFAULT_ROT);
        }

        for (i = 0; i <= 0; i++)
        {
            func_8003C92C(&D_800E23B0[i], &g_DefaultEventPosition, &DEFAULT_ROT);
        }

        return;
    }

    if (arg0 == 1)
    {
        for (i = 0; i < 2; i++)
        {
            func_8003C92C(&D_800E2450[i], &g_DefaultEventPosition, &DEFAULT_ROT);
        }

        return;
    }

    for (i = 0; i <= 0; i++)
    {
        func_8003C92C(&D_800E23D0[i], &g_DefaultEventPosition, &DEFAULT_ROT);
    }

    for (i = 0; i < 3; i++)
    {
        func_8003C92C(&D_800E23F0[i], &g_DefaultEventPosition, &DEFAULT_ROT);
    }
}
