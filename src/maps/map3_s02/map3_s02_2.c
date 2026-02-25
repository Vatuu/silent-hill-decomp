#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map3/map3_s02.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800CF404

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800CF418

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800CF45C

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800CF474

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800CF480

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800CF494

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800CF4A8

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800CF4BC

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800CF548

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800CFBAC

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800CFBC0

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800CFBD4

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800CFCD0

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800CFD64

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800CFD70

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CFDD0

#include "maps/shared/Map_RoomIdxGet.h" // 0x800CFDE0

#include "maps/shared/Map_RoomBgmInit_CheckCond.h" // 0x800CFE78

#include "maps/shared/Map_RoomBgmInit_3_s02_CondTrue.h" // 0x800CFEAC

#include "maps/shared/Map_RoomBgmInit_3_s02_CondFalse.h" // 0x800CFEEC

void Gfx_LoadingScreen_StageString(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D0184

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D0218

void func_800D02AC(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tNothing_happens_when_the ~N\n\televator_button_is_pressed. ~E ",
    "\tIt's_locked! ~E "
};

const VECTOR3 D_800CAAF8 = { Q12(100.0f), Q12(-1.2f), Q12(-127.2f) };

void func_800D02B4(void) // 0x800D02B4
{
    typedef enum _EventState
    {
        EventState_0   = 0,
        EventState_1   = 1,
        EventState_2   = 2,
        EventState_3   = 3,
        EventState_4   = 4,
        EventState_End = 5
    } e_EventState;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case EventState_0:
            Player_ControlFreeze();
            ScreenFade_ResetTimestep();
            SysWork_StateStepIncrement(0);
            break;

        case EventState_1:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case EventState_2:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case EventState_3:
            func_8005DC1C(Sfx_Unk1523, &D_800CAAF8, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case EventState_4:
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);

        default: // `EventState_End`
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            return;
    }
}

void func_800D03FC(void) // 0x800D03FC
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            D_800D1FBC = Q12(100.0f);

            ScreenFade_ResetTimestep();
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            Gfx_MapInitMapEffectsUpdate(7, 4);

            D_800D3154 = 0;

            Game_TurnFlashlightOff();
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);
            break;

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            break;

        case 3:
            Game_TurnFlashlightOn();
            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_236);
            break;
    }
}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D0570

void func_800D0608(void) // 0x800D0608
{
    VECTOR3  cameraPos;
    VECTOR3  cameraTarget;
    VECTOR3  lightIntPos;
    SVECTOR3 unused;

    // Weird code that changes g_DeltaTime, some kind of 50Hz/60Hz conversion trick?
    // Maybe cutscene was timed at wrong rate?
    g_DeltaTime = (g_DeltaTime * 4) / 5;
    ClearImage(&D_800D1FD0, 0, 0, 0);

    // GPU packet setup.
    {
        typedef struct
        {
            SPRT*      sprt_0;
            DR_TPAGE*  tpage_4;
            DR_STP*    stp_8;
            DR_AREA*   area_C;
            DR_OFFSET* offset_10;
        } s_ScratchData;

        s32            layer;
        s32            i;
        s_ScratchData* scratch;

        scratch = PSX_SCRATCH_ADDR(0);

        scratch->sprt_0 = (SPRT*)GsOUT_PACKET_P;
        for (layer = 0; layer < 4; layer++)
        {
            for (i = 0; i < 2; i++)
            {
                s32 colorVal;
                u8  tpageAbr;

                // @hack Might have been a switch instead?
                setXY0Fast(scratch->sprt_0,
                           (i * 256) - ((layer < 2) ? ((layer == 1) ? 159 : 161) : 160),
                           ((layer < 2) ? -112 : ((layer == 2) ? -111 : -113)));

                setUV0(scratch->sprt_0, 0, 0);

                switch (layer)
                {
                    case 0:
                        colorVal = 0x20;
                        tpageAbr = 1;
                        break;

                    case 1:
                        colorVal = 0x40;
                        tpageAbr = 0;
                        break;

                    default:
                        colorVal = 0x80;
                        tpageAbr = 0;
                }

                if (layer == 3)
                {
                    setRGBC0(scratch->sprt_0, 0x80, 0x80, 0x80, PRIM_RECT | RECT_TEXTURE);
                }
                else
                {
                    setRGBC0(scratch->sprt_0, colorVal, colorVal, colorVal, PRIM_RECT | RECT_TEXTURE | RECT_BLEND);
                }

                setWH(scratch->sprt_0, (i == 0) ? 256 : 64, 224);
                addPrimFast(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->sprt_0, 4);

                scratch->sprt_0++;
                scratch->tpage_4 = (DR_TPAGE*)scratch->sprt_0;

                setDrawTPage(scratch->tpage_4, 0, 0, getTPageN(2, tpageAbr, (i * 4) + 21, 1));

                addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->tpage_4);
                scratch->tpage_4++;
                scratch->sprt_0 = (SPRT*)scratch->tpage_4;
            }
        }

        // First `DR_AREA`.
        scratch->area_C = (DR_AREA*)scratch->sprt_0;
        SetDrawArea(scratch->area_C, &D_800D1FC0[g_ActiveBufferIdx == 0 ? 1 : 0]);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->area_C);
        scratch->area_C++;

        // Second `DR_AREA`.
        SetDrawArea(scratch->area_C, &D_800D1FD0);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ORDERING_TABLE_SIZE - 1], scratch->area_C);
        scratch->area_C++;

        // First `DR_OFFSET`.
        scratch->offset_10 = (DR_OFFSET*)scratch->area_C;
        SetDrawOffset(scratch->offset_10, &D_800D1FD8[g_ActiveBufferIdx == 0 ? 1 : 0]);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->offset_10);
        scratch->offset_10++;

        // Second `DR_OFFSET`.
        SetDrawOffset(scratch->offset_10, &D_800D1FE0);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ORDERING_TABLE_SIZE - 1], scratch->offset_10);
        scratch->offset_10++;

        // First `DR_STP` (disabled).
        scratch->stp_8 = (DR_STP*)scratch->offset_10;
        SetDrawStp(scratch->stp_8, 0);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], scratch->stp_8);
        scratch->stp_8++;

        // Second `DR_STP` (enabled).
        SetDrawStp(scratch->stp_8, 1);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ORDERING_TABLE_SIZE - 1], scratch->stp_8);
        scratch->stp_8++;

        GsOUT_PACKET_P = (PACKET*)scratch->stp_8;
    }

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 4)
    {
        SysWork_StateStepSet(0, 4);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_8003A16C();
            ScreenFade_ResetTimestep();

            g_SysWork.field_30    = 20;
            g_SysWork.flags_22A4 |= SysFlag2_3;

            Fs_QueueStartRead(FILE_ANIM_DWSTWY_DMS, FS_BUFFER_24);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_24);

            Chara_Spawn(Chara_Alessa, 0, Q12(80.0f), Q12(100.0f), Q12_ANGLE(0.0f), 3);

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(0.7f);

            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, 2);

            func_8008D438();
            Gfx_MapInitMapEffectsUpdate(16, 16);
            D_800D1FEC = 0;

            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 2, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.0f), false);
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementAfterTime(&D_800D1FEC, Q12(12.0f), Q12(0.0f), Q12(60.0f), false, true);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.0f), false);
            SysWork_StateStepIncrementAfterTime(&D_800D1FEC, Q12(12.0f), Q12(0.0f), Q12(75.0f), true, false);
            break;

        case 4:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);

            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, 2);

            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            g_SysWork.field_30   = 0;

            Savegame_EventFlagSet(EventFlag_237);

            vcReturnPreAutoCamWork(true);
            D_800D1FEC = NO_VALUE;
            Gfx_MapInitMapEffectsUpdate(2, 2);
            Gfx_MapEffectsUpdate(7, 7, PrimitiveType_S32, &D_800D1FBC, 0, Q12(100.0f));
            break;
    }

    if (D_800D1FEC >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "ARISA", D_800D1FEC, FS_BUFFER_24);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&cameraPos, &cameraTarget, NULL, D_800D1FEC, FS_BUFFER_24));
        vcUserCamTarget(&cameraPos, NULL, true);
        vcUserWatchTarget(&cameraTarget, NULL, true);
        Dms_CharacterGetPosRot(&g_SysWork.pointLightPosition_2360, &unused, "LIGHT", D_800D1FEC, FS_BUFFER_24);
        Dms_CharacterGetPosRot(&lightIntPos, &unused, "L_INT", D_800D1FEC, FS_BUFFER_24);

        g_SysWork.pointLightRot_2370.vx = -ratan2(lightIntPos.vy - g_SysWork.pointLightPosition_2360.vy, Math_Vector2MagCalc(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz));
        g_SysWork.pointLightRot_2370.vy = ratan2(lightIntPos.vx - g_SysWork.pointLightPosition_2360.vx, lightIntPos.vz - g_SysWork.pointLightPosition_2360.vz);
        g_SysWork.pointLightRot_2370.vz = Q12_ANGLE(0.0f);
    }
}

void Map_WorldObjectsInit(void) // 0x800D0F8C
{
    D_800D3154 = 1;
}

void Map_WorldObjectsUpdate(void) // 0x800D0F9C
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (D_800D3154)
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, -4, -1, -4))
        {
            D_800D1FBC = MAX(D_800D1FBC, Q12(10.0f));
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, -4, -1, -4))
    {
        if (D_800D3154)
        {
            D_800D1FBC = MAX(D_800D1FBC, Q12_MULT_PRECISE(func_800D1354(), Q12(24.0f)) + Q12(25.0f));
        }

        if (!Savegame_EventFlagGet(EventFlag_233) && g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(-129.0f))
        {
            Savegame_EventFlagSet(EventFlag_233);
            func_8005DC1C(Sfx_Unk1523, &D_800CAAF8, Q8_CLAMPED(0.5f), 0);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -4, -1, -4))
    {

        if (!Savegame_EventFlagGet(EventFlag_234) && g_SysWork.playerWork_4C.player_0.position_18.vx < Q12(67.0f))
        {
            Savegame_EventFlagSet(EventFlag_234);
            func_8005DC1C(Sfx_Unk1523, &QVECTOR3(69.6f, -1.2f, -138.4f), Q8_CLAMPED(0.5f), 0);
        }
    }
}

s16 func_800D1354(void) // 0x800D1354
{
    s32 cos0;
    s32 tmp0;
    s32 x;
    s32 z;
    s32 var1;
    s32 var;
    s32 x6;
    s32 z6;

    // TODO: Use `Math_Vector2MagCalc`.
    x = g_SysWork.playerWork_4C.player_0.position_18.vx - Q12(95.2f);
    z = g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(140.0f);
    cos0 = Math_Cos(func_8005BF38((ratan2(x, z) - ratan2(Q12(4.8f) + 1, Q12(12.8f) + 1))));

    x6 = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vx - Q12(95.2f));
    z6 = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(140.0f));

    tmp0 = FP_FROM((cos0 * Q6_TO_Q12((SquareRoot0(SQUARE(x6) + SQUARE(z6))))), Q12_SHIFT);
    var1 = FP_TO(tmp0, Q12_SHIFT) / Q6_TO_Q12(SquareRoot0(0xBAC52));
    var = MIN(var1, Q8(16.0f));

    if (var >= 0)
    {
        if (var1 > Q8(16.0f))
        {
            var1 = Q8(16.0f);
        }

        return Q8(16.0f) - var1;
    }

    return Q8(16.0f);
}
