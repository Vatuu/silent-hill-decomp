#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>
#include <psyq/libapi.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/events/bodyprog_data_800A99B4.h"
#include "bodyprog/events/radio.h"
#include "bodyprog/math/math.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"

// ========================================
// MAP
// ========================================

void GameState_MapScreen_Update(void) // 0x80066EB0
{
    s32           temp_s0_2;
    s32           temp_s4;
    s8            markingFileIdx;
    u16           var_s5;
    u16           var_s6;
    u32           temp_a0;
    u32           temp;
    u32           temp2;
    u32           temp3;
    u32           temp4;
    static u8     paperMapIdx;
    static u8     markingIdx;
    static s8     activeMarkingFileIdx;
    static s8     __pad_bss_800C444B;
    static q19_12 screenPosX;
    static q19_12 screenPosY;

    func_800363D0();
    Game_TimerUpdate();

    switch (g_GameWork.gameStateSteps[0])
    {
        case 0:
            Screen_Refresh(SCREEN_WIDTH, true);

            activeMarkingFileIdx = g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx];
            paperMapIdx = g_SavegamePtr->paperMapIdx;
            screenPosX = NO_VALUE;
            D_800C4454 = Q12(1.0f);
            D_800AE770 = false;

            Game_RadioSoundStop();
            SD_Call(Sfx_MenuMap);
            func_80066E40();
            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[paperMapIdx], FS_BUFFER_2, &g_PaperMapImg);
            Fs_QueueWaitForEmpty();

            g_IntervalVBlanks = 1;
            ScreenFade_Start(true, true, false);

            g_GameWork.gameStateSteps[0] = 2;
            g_SysWork.counters_1C[1]              = 0;
            g_GameWork.gameStateSteps[1] = 0;
            g_GameWork.gameStateSteps[2] = 0;
            break;

        case 2:
            if (screenPosX < Q12(0.0f))
            {
                var_s5 = 0;
                var_s6 = 0;
            }
            else
            {
                temp   = screenPosX - Q12_MULT_PRECISE(D_800C4454, screenPosX);
                var_s6 = FP_FROM(temp, Q12_SHIFT);

                temp2  = screenPosY - Q12_MULT_PRECISE(D_800C4454, screenPosY);
                var_s5 = FP_FROM(temp2, Q12_SHIFT);
            }

            temp_s4 = (D_800C4454 >> 1) + Q12(0.5f);

            temp_s0_2 = func_80067914(paperMapIdx, var_s6, var_s5, temp_s4);
            func_80068E0C(1, paperMapIdx, 0, 0, var_s6, var_s5, temp_s4);

            if (ScreenFade_IsNone())
            {
                if (!D_800AE770 && D_800C4454 == Q12(1.0f))
                {
                    func_80068CC0(paperMapIdx);
                }
            }

            func_800692A4(var_s6, var_s5, temp_s4);

            if ((g_GameWork.gameStatePrev == GameState_InventoryScreen && g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.cancel) ||
                (g_GameWork.gameStatePrev != GameState_InventoryScreen && g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config.controllerConfig.cancel |
                                                                                                           g_GameWorkPtr->config.controllerConfig.map)))
            {
                SD_Call(Sfx_MenuMap);

                if (g_GameWork.gameStatePrev == GameState_InventoryScreen)
                {
                    GsDrawOt(&g_OrderingTable0[g_ActiveBufferIdx]);
                    VSync(SyncMode_Wait);
                    GsDrawOt(&g_OrderingTable0[g_ActiveBufferIdx]);
                    func_80066E7C();
                    GameFs_MapItemsTextureLoad(g_SavegamePtr->mapIdx);
                    func_80066D90();
                    ScreenFade_ResetTimestep();
                }
                else
                {
                    ScreenFade_Start(true, false, false);
                }

                g_GameWork.gameStateSteps[0] = 4;
                g_SysWork.counters_1C[1]              = 0;
                g_GameWork.gameStateSteps[1] = 0;
                g_GameWork.gameStateSteps[2] = 0;
                break;
            }

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.enter)
            {
                if (D_800AE770)
                {
                    D_800AE770 = false;
                }
                else
                {
                    D_800AE770 = true;

                    if (screenPosX < Q12(0.0f))
                    {
                        screenPosX = Q12(CLAMP_LOW_THEN_MIN((s16)temp_s0_2 + 80, 0, 160));
                        screenPosY = Q12(CLAMP_LOW_THEN_MIN((temp_s0_2 >> 16) + 60, 0, 120));
                    }
                }
            }

            if (!D_800AE770)
            {
                if (D_800C4454 == Q12(1.0f))
                {
                    if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickUp)
                    {
                        if (HAS_MAP(D_800AE740[paperMapIdx][0]))
                        {
                            markingIdx = D_800AE740[paperMapIdx][0];

                            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[markingIdx]);
                            ScreenFade_Start(true, false, false);

                            screenPosX                      = NO_VALUE;
                            g_GameWork.gameStateSteps[0] = 3;
                            g_SysWork.counters_1C[1]              = 0;
                            g_GameWork.gameStateSteps[1] = 0;
                            g_GameWork.gameStateSteps[2] = 0;
                            break;
                        }
                    }

                    if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickDown)
                    {
                        if (HAS_MAP(D_800AE740[paperMapIdx][1]))
                        {
                            markingIdx = D_800AE740[paperMapIdx][1];

                            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[markingIdx]);
                            ScreenFade_Start(true, false, false);

                            screenPosX = NO_VALUE;
                            g_GameWork.gameStateSteps[0] = 3;
                            g_SysWork.counters_1C[1]              = 0;
                            g_GameWork.gameStateSteps[1] = 0;
                            g_GameWork.gameStateSteps[2] = 0;
                            break;
                        }
                    }
                    break;
                }

                D_800C4454 = MIN(D_800C4454 + 196, Q12(1.0f));
                break;
            }

            D_800C4454  = CLAMP_LOW(D_800C4454 - 196, 0);
            screenPosX += (g_Controller0->sticks_24.sticks_0.leftX * ((SHRT_MAX / 2) + 1)) / 75;
            screenPosX  = CLAMP_RANGE(screenPosX, Q12(0.0f), Q12(SCREEN_WIDTH / 2));
            screenPosY += (g_Controller0->sticks_24.sticks_0.leftY * ((SHRT_MAX / 2) + 1)) / 75;
            screenPosY  = CLAMP_RANGE(screenPosY, Q12(0.0f), Q12(SCREEN_HEIGHT / 2));
            break;

        case 3:
            if (ScreenFade_IsFinished())
            {
                paperMapIdx = markingIdx;

                SD_Call(Sfx_MenuMap);

                g_GameWork.gameStateSteps[0] = 1;
                g_SysWork.counters_1C[1]              = 0;
                g_GameWork.gameStateSteps[1] = 0;
                g_GameWork.gameStateSteps[2] = 0;
                break;
            }

            func_80067914(paperMapIdx, 0, 0, Q12(1.0f));
            func_80068E0C(1, paperMapIdx, 0, 0, 0, 0, Q12(1.0f));
            func_800692A4(0, 0, Q12(1.0f));
            break;

        case 1:
            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[paperMapIdx], FS_BUFFER_2, &g_PaperMapImg);

            markingFileIdx = g_PaperMapMarkingFileIdxs[paperMapIdx];
            if (markingFileIdx != activeMarkingFileIdx && markingFileIdx != NO_VALUE)
            {
                activeMarkingFileIdx = g_PaperMapMarkingFileIdxs[paperMapIdx];
                Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + g_PaperMapMarkingFileIdxs[paperMapIdx], FS_BUFFER_1, &g_PaperMapMarkingAtlasImg);
            }

            Fs_QueueWaitForEmpty();
            ScreenFade_Start(true, true, false);

            g_GameWork.gameStateSteps[0] = 2;
            g_SysWork.counters_1C[1]              = 0;
            g_GameWork.gameStateSteps[1] = 0;
            g_GameWork.gameStateSteps[2] = 0;
            break;

        case 4:
            temp3   = screenPosX - Q12_MULT_PRECISE(D_800C4454, screenPosX);
            var_s6  = FP_FROM(temp3, Q12_SHIFT);
            temp4   = screenPosY - Q12_MULT_PRECISE(D_800C4454, screenPosY);
            temp_s4 = (D_800C4454 >> 1) + Q12(0.5f);
            var_s5  = FP_FROM(temp4, Q12_SHIFT);

            func_80067914(paperMapIdx, var_s6, var_s5, temp_s4);
            func_80068E0C(1, paperMapIdx, 0, 0, var_s6, var_s5, temp_s4);
            func_800692A4(var_s6, var_s5, temp_s4);

            if (ScreenFade_IsFinished())
            {
                if (g_GameWork.gameStatePrev == GameState_InGame || g_GameWork.gameStatePrev == GameState_LoadMapScreen)
                {
                    func_80066E7C();
                    Screen_Init(SCREEN_WIDTH, false);
                    g_GameWork.gameStatePrev = GameState_InGame;
                }

                Game_StateSetPrevious();
            }
            break;
    }
}

static inline s32 MapCoordIdxGet(q19_12 coord, s32 bias, s32 shift, s32 offset)
{
    if (coord < Q12(0.0f))
    {
        coord += bias;
    }

    return (coord >> shift) + offset;
}

s32 func_80067914(s32 paperMapIdx, u16 arg1, u16 arg2, u16 arg3) // 0x80067914
{
    // TODO: Work out hex values in switches below.
    #define MAP_OFFSET(coord) \
        ((coord) + (((coord) < 0) ? 20 : 21))

    #define MAP_IDX(x, z) \
        ((MAP_OFFSET(x) * 100) + MAP_OFFSET(z))

    s32      sp10[6];
    s16      temp_s1;
    s16      temp_s2;
    s16      temp_v0_7;
    s32      var_a3;
    s32      temp_s4;
    s32      cellX;
    s32      cellZ;
    s32      projCellX1;
    s32      temp_v1_7;
    s32      var_v0_16;
    s32      projCellX0;
    q3_12    angle;
    u32      temp_a0;
    s16      mapCoordIdxX;
    s16      mapCoordIdxZ;
    s32      temp;
    s32      temp2;
    s32      temp3;
    s32      temp4;
    LINE_F4* line;
    POLY_G3* poly;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    #define playerChara g_SysWork.playerWork.player

    if (g_SavegamePtr->paperMapIdx != paperMapIdx)
    {
        return 0;
    }

    if (playerChara.position.vx <= Q12(0.0f))
    {
        cellX = (playerChara.position.vx - CHUNK_CELL_SIZE) / CHUNK_CELL_SIZE;
    }
    else
    {
        cellX = (playerChara.position.vx / CHUNK_CELL_SIZE);
    }

    if (playerChara.position.vz <= Q12(0.0f))
    {
        cellZ = (playerChara.position.vz - CHUNK_CELL_SIZE) / CHUNK_CELL_SIZE;
    }
    else
    {
        cellZ = playerChara.position.vz / CHUNK_CELL_SIZE;
    }

    mapCoordIdxX = SHRT_MAX;
    angle        = playerChara.rotation.vy;
    mapCoordIdxZ = SHRT_MAX;

    switch (paperMapIdx)
    {
        case PaperMapIdx_OldTown:
            switch (g_SavegamePtr->mapIdx)
            {
                case MapIdx_MAP2_S00:
                    if (cellZ < 4 || (cellZ < 6 && (cellX >= -1 && cellX < 1)))
                    {
                        mapCoordIdxX = MapCoordIdxGet( playerChara.position.vx, Q12(2.0f) - 1, 13, 19);
                        mapCoordIdxZ = MapCoordIdxGet(-playerChara.position.vz, Q12(2.0f) - 1, 13, 1);
                        break;
                    }

                    switch (MAP_IDX(cellX, cellZ))
                    {
                        case MAP_IDX(-5, 9):
                            mapCoordIdxX = 43;
                            mapCoordIdxZ = -34;
                            break;

                        case MAP_IDX(-5, 7):
                        case MAP_IDX(-3, 5):
                        case MAP_IDX(-3, 6):
                            mapCoordIdxX = -11;
                            mapCoordIdxZ = -19;
                            break;

                        case MAP_IDX(1, 9):
                            mapCoordIdxX = -63;
                            mapCoordIdxZ = 73;
                            break;

                        case MAP_IDX(3, 9):
                            mapCoordIdxX = -63;
                            mapCoordIdxZ = -28;
                            break;

                        case MAP_IDX(2, 7):
                        case MAP_IDX(3, 7):
                            mapCoordIdxX = -58;
                            mapCoordIdxZ = 73;
                            break;

                        case MAP_IDX(2, 5):
                        case MAP_IDX(3, 5):
                            mapCoordIdxX = -58;
                            mapCoordIdxZ = -28;
                            break;

                        case MAP_IDX(5, 5):
                            mapCoordIdxX = -112;
                            mapCoordIdxZ = 51;
                            break;

                        case MAP_IDX(-2, 8):
                        case MAP_IDX(5, 8):
                            mapCoordIdxX = 116;
                            mapCoordIdxZ = 47;
                            break;
                    }
                    break;

                case MapIdx_MAP0_S02:
                    switch (MAP_IDX(cellX, cellZ))
                    {
                        case MAP_IDX(-3, 0):
                            mapCoordIdxX = -103;
                            mapCoordIdxZ = 103;
                            break;

                        case MAP_IDX(-4, 0):
                            mapCoordIdxX = 36;
                            mapCoordIdxZ = -76;
                            angle       += Q12_ANGLE(90.0f);
                            break;

                        case MAP_IDX(-5, 0):
                            mapCoordIdxX = 62;
                            mapCoordIdxZ = 50;
                            angle       += Q12_ANGLE(180.0f);
                            break;

#if VERSION_EQUAL_OR_NEWER(JAP1) // @bugfix
                        case MAP_IDX(-4, 1):
                            mapCoordIdxX = -58;
                            mapCoordIdxZ = -28;
                            break;
#endif
                    }
                    break;

                case MapIdx_MAP2_S01:
                    mapCoordIdxX = 38;
                    mapCoordIdxZ = 50;
                    angle       += Q12_ANGLE(180.0f);
                    break;

                case MapIdx_MAP0_S01:
                    mapCoordIdxX = 33;
                    mapCoordIdxZ = -28;
                    break;

                case MapIdx_MAP1_S06:
                    mapCoordIdxX = -123;
                    mapCoordIdxZ = 81;
                    angle       -= Q12_ANGLE(90.0f);
                    break;
            }
            break;

        case PaperMapIdx_FogSchoolBF:
        case PaperMapIdx_FogSchool1F:
        case PaperMapIdx_FogSchool2F:
        case PaperMapIdx_FogSchoolRF:
        case PaperMapIdx_AltSchoolBF:
        case PaperMapIdx_AltSchool1F:
        case PaperMapIdx_AltSchool2F:
        case PaperMapIdx_AltSchoolRF:
            if (cellX == -2 && cellZ == 0)
            {
                angle       += Q12_ANGLE(180.0f);
                mapCoordIdxX = D_800AE774[2][2][0] + (((playerChara.position.vx - (cellX * CHUNK_CELL_SIZE)) - (CHUNK_CELL_SIZE / 2)) / Q12(-0.2f));
                mapCoordIdxZ = D_800AE774[2][2][1] + (((playerChara.position.vz - (cellZ * CHUNK_CELL_SIZE)) - (CHUNK_CELL_SIZE / 2)) / Q12(0.2f));
            }
            else
            {
                mapCoordIdxX = D_800AE774[cellX + 4][cellZ + 2][0] + (((playerChara.position.vx - (cellX * CHUNK_CELL_SIZE)) - (CHUNK_CELL_SIZE / 2)) / Q12(0.2f));
                mapCoordIdxZ = D_800AE774[cellX + 4][cellZ + 2][1] + (((playerChara.position.vz - (cellZ * CHUNK_CELL_SIZE)) - (CHUNK_CELL_SIZE / 2)) / Q12(-0.2f));
            }
            break;

        case PaperMapIdx_FogHospitalBF:
        case PaperMapIdx_FogHospital1F:
        case PaperMapIdx_FogHospital2F:
        case PaperMapIdx_FogHospital3F:
            mapCoordIdxX = D_800AE7E4[cellX + 1][cellZ + 2][0] + (((playerChara.position.vx - (cellX * CHUNK_CELL_SIZE)) - (CHUNK_CELL_SIZE / 2)) / 0x222); // TODO: Demagic into clean float.
            mapCoordIdxZ = D_800AE7E4[cellX + 1][cellZ + 2][1] + ((((playerChara.position.vz - (cellZ * CHUNK_CELL_SIZE)) - (CHUNK_CELL_SIZE / 2)) * 6) / Q12(-0.8f));
            break;

        case PaperMapIdx_AltHospitalBF:
        case PaperMapIdx_AltHospital1F:
        case PaperMapIdx_AltHospital2F:
        case PaperMapIdx_AltHospital3F:
            mapCoordIdxX = D_800AE820[cellX + 4][cellZ + 4][0] + (((playerChara.position.vx - (cellX * CHUNK_CELL_SIZE)) - (CHUNK_CELL_SIZE / 2)) / 0x222);
            mapCoordIdxZ = D_800AE820[cellX + 4][cellZ + 4][1] + ((((playerChara.position.vz - (cellZ * CHUNK_CELL_SIZE)) - (CHUNK_CELL_SIZE / 2)) * 6) / Q12(-0.8f));
            break;

        case PaperMapIdx_ResortTown:
            switch (g_SavegamePtr->mapIdx)
            {
                case MapIdx_MAP5_S01:
                    mapCoordIdxX = MapCoordIdxGet( playerChara.position.vx, Q12(2.0f) - 1, 13,  60);
                    mapCoordIdxZ = MapCoordIdxGet(-playerChara.position.vz, Q12(2.0f) - 1, 13, -85);

                    temp_v1_7 = playerChara.position.vx / CHUNK_CELL_SIZE;
                    if ((playerChara.position.vx >  Q12(0.0f) && (temp_v1_7 + 1) == -4) ||
                        (playerChara.position.vx <= Q12(0.0f) && (temp_v1_7 - 1) == -4))
                    // if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4)) // TODO: Causing mismatch.
                    {
                        if (PLAYER_IN_MAP_CHUNK(vz, 1, -1, -1, -1))
                        {
                            mapCoordIdxX += 87;
                            mapCoordIdxZ += 61;
                            break;
                        }
                    }

                    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, -1, -1))
                    {
                        mapCoordIdxX += 87;
                        mapCoordIdxZ += 61;
                        break;
                    }
                    break;

                case MapIdx_MAP5_S02:
                    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
                    {
                        mapCoordIdxX = 87;
                        mapCoordIdxZ = -56;
                        angle       += Q12_ANGLE(90.0f);
                    }
                    else if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 1, -1, 1))
                    {
                        mapCoordIdxX = 54;
                        mapCoordIdxZ = -53;
                        angle       += Q12_ANGLE(90.0f);
                    }
                    break;

                case MapIdx_MAP5_S03:
                    switch (MAP_IDX(cellX, cellZ))
                    {
                        case MAP_IDX(2, 1):
                            mapCoordIdxX = 69;
                            mapCoordIdxZ = -19;
                            break;

                        case MAP_IDX(2, 0):
                            mapCoordIdxX = 74;
                            mapCoordIdxZ = -12;
                            angle       -= Q12_ANGLE(90.0f);
                            break;

                        case MAP_IDX(1, 0):
                            mapCoordIdxX = 74;
                            mapCoordIdxZ = -14;
                            break;

                        case MAP_IDX(1, 1):
                            mapCoordIdxX = 73;
                            mapCoordIdxZ = -14;
                            break;
                    }
                    break;

                case MapIdx_MAP6_S00:
                    mapCoordIdxX = MapCoordIdxGet( playerChara.position.vx, Q12(2.0f) - 1, 13, 0);
                    mapCoordIdxZ = MapCoordIdxGet(-playerChara.position.vz, Q12(2.0f) - 1, 13, 55);
                    break;

                case MapIdx_MAP6_S01:
                    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
                    {
                        mapCoordIdxZ = 43;
                    }
                    else
                    {
                        mapCoordIdxZ = 46;
                    }

                    mapCoordIdxX = -77;
                    break;

                case MapIdx_MAP6_S02:
                    mapCoordIdxX = -55;
                    mapCoordIdxZ =  84;

                    if (!PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2))
                    {
                        angle += Q12_ANGLE(90.0f);
                    }
                    else if (PLAYER_NOT_IN_MAP_CHUNK(vz, 1, -1, -1, -1))
                    {
                        angle += Q12_ANGLE(90.0f);
                    }
                    break;
            }
            break;

        case PaperMapIdx_FogCentralTown:
        case PaperMapIdx_AltCentralTown:
            switch (g_SavegamePtr->mapIdx)
            {
                case MapIdx_MAP2_S02:
                case MapIdx_MAP4_S02:
                case MapIdx_MAP4_S05:
                    switch (MAP_IDX(cellX, cellZ))
                    {
                        case MAP_IDX(-6, 2):
                            mapCoordIdxX =  94;
                            mapCoordIdxZ = -103;
                            break;

                        case MAP_IDX(-3, 2):
                        case MAP_IDX(-4, 2):
                            mapCoordIdxX = -12;
                            mapCoordIdxZ =  63;
                            angle       += Q12_ANGLE(180.0f);
                            break;

                        case MAP_IDX(3, -1):
                            mapCoordIdxX = -16;
                            mapCoordIdxZ =  91;
                            break;

                        case MAP_IDX(-3, 4):
                        case MAP_IDX(-3, 5):
                            mapCoordIdxX = MapCoordIdxGet(playerChara.position.vx, Q12(1.0f) - 1, 12, 80);
                            mapCoordIdxZ = MapCoordIdxGet(Q12(280.0f) - playerChara.position.vz, Q12(1.0f) - 1, 12, 0);
                            break;

                        default:
                            mapCoordIdxX = MapCoordIdxGet( playerChara.position.vx, Q12(1.0f) - 1, 12, 80);
                            mapCoordIdxZ = MapCoordIdxGet(-playerChara.position.vz, Q12(1.0f) - 1, 12, 0);
                            break;
                    }
                    break;

                case MapIdx_MAP4_S01:
                    mapCoordIdxX =  95;
                    mapCoordIdxZ = -103;
                    break;

                case MapIdx_MAP4_S03:
                    switch (MAP_IDX(cellX, cellZ))
                    {
                        case MAP_IDX(3, 1):
                        case MAP_IDX(4, 1):
                            mapCoordIdxX =  100;
                            mapCoordIdxZ = -61;
                            break;

                        case MAP_IDX(2, -3):
                        case MAP_IDX(3, -3):
                            mapCoordIdxX =  115;
                            mapCoordIdxZ = -61;
                            break;

                        case MAP_IDX(5, -1):
                            mapCoordIdxX =  115;
                            mapCoordIdxZ = -63;
                            angle       += Q12_ANGLE(90.0f);
                            break;

                        case MAP_IDX(2, 3):
                        case MAP_IDX(3, 3):
                            mapCoordIdxX =  125;
                            mapCoordIdxZ = -60;
                            break;
                    }
                    break;

                case MapIdx_MAP2_S04:
                    projCellX0 = cellX + 21;
                    if (cellX < 0)
                    {
                        projCellX0 = cellX + 20;
                    }

                    projCellX1 = projCellX0 * 100;
                    if (cellZ < 0)
                    {
                        var_v0_16 = projCellX1 + 20;
                    }
                    else
                    {
                        var_v0_16 = projCellX1 + 21;
                    }

                    switch (var_v0_16 + cellZ)
                    // switch (MAP_IDX(temp_t3, temp_t4)) // TODO: Causing mismatch.
                    {
                        case MAP_IDX(-3, 1):
                            mapCoordIdxX = -19;
                            mapCoordIdxZ = -14;
                            break;

                        case MAP_IDX(-1, 0):
                            mapCoordIdxX = -19;
                            mapCoordIdxZ = -14;
                            break;

                        case MAP_IDX(-2, 0):
                            mapCoordIdxX = -21;
                            mapCoordIdxZ = -14;
                            break;
                    }
                    break;
            }
            break;

        case PaperMapIdx_FogSewer1F:
            mapCoordIdxX = MapCoordIdxGet(-playerChara.position.vz, Q12(0.5f) - 1, 11, 0);
            mapCoordIdxZ = MapCoordIdxGet(-playerChara.position.vx, Q12(0.5f) - 1, 11, 40);
            angle       -= Q12_ANGLE(90.0f);
            break;

        case PaperMapIdx_FogSewer2F:
            mapCoordIdxX = MapCoordIdxGet(-playerChara.position.vz, Q12(0.5f) - 1, 11, -80);
            mapCoordIdxZ = MapCoordIdxGet(-playerChara.position.vx, Q12(0.5f) - 1, 11, -140);
            angle       -= Q12_ANGLE(90.0f);
            break;

        case PaperMapIdx_AltSewer:
            mapCoordIdxX = MapCoordIdxGet(-playerChara.position.vx, Q12(0.5f) - 1, 11, 55);
            mapCoordIdxZ = MapCoordIdxGet( playerChara.position.vz, Q12(0.5f) - 1, 11, -80);
            angle       += Q12_ANGLE(180.0f);
            break;

        default:
            return 0;
    }

    var_a3 = mapCoordIdxX;

    if (var_a3 == SHRT_MAX)
    {
        return 0;
    }

    temp_s4 = (mapCoordIdxZ << 16) + var_a3;
    if (g_Controller0->btnsHeld_C & (ControllerFlag_L1 | ControllerFlag_R1))
    {
        return temp_s4;
    }

    temp_a0 = SCREEN_WIDTH / 2;
    temp3   = ((var_a3 - (arg1 - temp_a0)) * SCREEN_WIDTH);
    temp    = Q12_MULT_PRECISE(arg3, SCREEN_WIDTH);
    temp_s2 = (temp3 / temp) - (SCREEN_WIDTH / 2);

    temp_a0 = SCREEN_HEIGHT / 2;
    temp4   = ((mapCoordIdxZ - (arg2 - temp_a0)) * SCREEN_HEIGHT);
    temp2   = Q12_MULT_PRECISE(arg3, SCREEN_HEIGHT);
    temp_s1 = (temp4 / temp2) - (SCREEN_HEIGHT / 2);

    temp_v0_7 = Math_AngleNormalizeSigned(angle);

    sp10[0] = temp_s2 + FP_FROM(Math_Sin(temp_v0_7) * 6, Q12_SHIFT);
    sp10[1] = (temp_s1 + FP_FROM(Math_Cos(temp_v0_7) * -6, Q12_SHIFT)) * 2;
    sp10[2] = temp_s2 + FP_FROM(Math_Cos(temp_v0_7) * 4 - Math_Sin(temp_v0_7) * 6, Q12_SHIFT);
    sp10[3] = (temp_s1 + FP_FROM(Math_Sin(temp_v0_7) * 4 + Math_Cos(temp_v0_7) * 6, Q12_SHIFT)) * 2;
    sp10[4] = temp_s2 + FP_FROM(Math_Cos(temp_v0_7) * -4 - Math_Sin(temp_v0_7) * 6, Q12_SHIFT);
    sp10[5] = (temp_s1 + FP_FROM(Math_Sin(temp_v0_7) * -4 + Math_Cos(temp_v0_7) * 6, Q12_SHIFT)) * 2;

    line = (LINE_F4*)GsOUT_PACKET_P;
    setLineF4(line);
    setXY0Fast(line, sp10[0], sp10[1]);
    setXY1Fast(line, sp10[2], sp10[3]);
    setXY2Fast(line, sp10[4], sp10[5]);
    setXY3Fast(line, sp10[0], sp10[1]);
    *(u16*)&line->r0 = 0x1010; // TODO: Use packing macro?
    line->b0         = 0x10;

    addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], line);

    poly = (POLY_G3*)(++line);
    setPolyG3(poly);
    setXY0Fast(poly, sp10[0], sp10[1]);
    setXY1Fast(poly, sp10[2], sp10[3]);
    setXY2Fast(poly, sp10[4], sp10[5]);
    *(u16*)&poly->r0 = 0x0000;
    poly->b0         = 0xFF;
    *(u16*)&poly->r1 = 0xFF00;
    poly->b1         = 0x00;
    *(u16*)&poly->r2 = 0xFF00;
    poly->b2         = 0x00;

    addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], poly);
    GsOUT_PACKET_P = (PACKET*)poly + sizeof(POLY_G3);
    return temp_s4;

    #undef playerChara
}

bool func_80068CC0(s32 arg0) // 0x80068CC0
{
    s32      i;
    POLY_G3* poly;

    for (i = 0; i < 2; i++)
    {
        if (HAS_MAP(D_800AE740[arg0][i]))
        {
            poly = GsOUT_PACKET_P;
            setPolyG3(poly);

            if (i != 0)
            {
                setXY0Fast(poly,  0, 216);
                setXY1Fast(poly, -8, 200);
                setXY2Fast(poly,  8, 200);
            }
            else
            {
                setXY0Fast(poly,  0, -216);
                setXY1Fast(poly, -8, -200);
                setXY2Fast(poly,  8, -200);
            }

            *(u16*)&poly->r0 = 0x1010;
            poly->b0         = 0xC4;
            *(u16*)&poly->r1 = 0x8080;
            poly->b1         = 0xC4;
            *(u16*)&poly->r2 = 0x8080;
            poly->b2         = 0xC4;

            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], poly);
            GsOUT_PACKET_P = ++poly;
        }
    }

    return true;
}

bool func_80068E0C(s32 arg0, s32 idx, s32 arg2, s32 shade, u16 arg4, u16 arg5, u16 arg6) // 0x80068E0C
{
    s32              sp0;
    u16              sp4;
    s16              y0;
    s32              x0;
    s32              x1;
    s32              y1;
    s32              j;
    s32              i;
    s32              temp;
    s32              temp2;
    s16              temp3;
    s32              temp4;
    s32              temp6;
    s_func_80068E0C* ptr;

    ptr = PSX_SCRATCH;

    if (g_PaperMapMarkingFileIdxs[idx] == NO_VALUE)
    {
        return false;
    }

    if (D_800AEDBC[idx].ptr_0 == NULL)
    {
        return false;
    }

    if (D_800AEDBC[idx].ptr_4 == NULL)
    {
        return false;
    }

    ptr->field_0 = (POLY_FT4*)GsOUT_PACKET_P;
    i            = 0;

    if (arg0 == 2)
    {
        i            = (arg2 - D_800AEDBC[idx].field_8) >> 1;
        ptr->field_C = i + 1;
    }
    else
    {
        shade         = 128;
        ptr->field_C = (D_800AEDBC[idx].field_A - D_800AEDBC[idx].field_8) >> 1;
    }

    for (; i < ptr->field_C; i++)
    {
        for (j = 0; j < 2; j++)
        {
            if (arg0 == 1 && !Savegame_EventFlagGet(((D_800AEDBC[idx].field_8 + (i * 2)) + j) + 1))
            {
                continue;
            }

            if (arg0 == 2 && (arg2 & (1 << 0)) != j)
            {
                continue;
            }

            ptr->field_8 = *(s_800AE8A0_4*)&D_800AEDBC[idx].ptr_4[i];
            if (j != 0)
            {
                if (ptr->field_8.field_3)
                {
                    ptr->field_4 = *(s_800AE8A0_0*)&D_800AEDBC[idx].ptr_0[ptr->field_8.field_3];
                }
                else
                {
                    continue;
                }
            }
            else if (ptr->field_8.field_2)
            {
                ptr->field_4 = *(s_800AE8A0_0*)&D_800AEDBC[idx].ptr_0[ptr->field_8.field_2];
            }
            else
            {
                continue;
            }

            sp4   = SCREEN_WIDTH / 2;
            temp6 = (ptr->field_8.field_0 << 1) - (arg4 - sp4);
            x0    = (Q12(temp6) / arg6) - (SCREEN_WIDTH / 2);

            sp4   = SCREEN_HEIGHT;
            temp4 = Q12((ptr->field_8.field_1 << 1) - ((arg5 * 2) - sp4));
            y0    = (temp4 / arg6) - SCREEN_HEIGHT;

            x1    = x0 + (Q12(ptr->field_4.field_2) / arg6);
            temp3 = Q12(ptr->field_4.field_3) / arg6;
            y1    = y0 + temp3;

            // Set polygon vertices.
            setPolyFT4(ptr->field_0);
            setXY0Fast(ptr->field_0, x0, y0);
            setXY1Fast(ptr->field_0, x1, y0);
            setXY2Fast(ptr->field_0, x0, y1);
            setXY3Fast(ptr->field_0, x1, y1);

            // Set polygon UVs.
            temp                       = (ptr->field_4.field_1 << 8) + 0x80;
            *((s32*)&ptr->field_0->u0) = ptr->field_4.field_0 + temp + (getClut(g_PaperMapMarkingAtlasImg.clutX, g_PaperMapMarkingAtlasImg.clutY) << 16);
            temp2                      = ptr->field_4.field_2 + 0x80;
            *((s32*)&ptr->field_0->u1) = ptr->field_4.field_0 + temp2 + (ptr->field_4.field_1 << 8) + 0x470000;
            sp0                        = ((ptr->field_4.field_1 + ptr->field_4.field_3) << 8) + 0x80;
            *((s16*)&ptr->field_0->u2) = ptr->field_4.field_0 + sp0;
            *((s16*)&ptr->field_0->u3) = ptr->field_4.field_2 + (ptr->field_4.field_0 + 0x80) + ((ptr->field_4.field_1 + ptr->field_4.field_3) << 8);

            // Set polygon color.
            setRGBC0(ptr->field_0, shade, shade, shade, 0x2E);

            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[3], ptr->field_0);
            ptr->field_0++;
        }
    }

    GsOUT_PACKET_P = (PACKET*)ptr->field_0;
    return true;
}

INCLUDE_RODATA("bodyprog/nonmatchings/bodyprog_mapscreen_80066D90", D_80028B2C);

INCLUDE_RODATA("bodyprog/nonmatchings/bodyprog_mapscreen_80066D90", D_80028B34);

INCLUDE_ASM("bodyprog/nonmatchings/bodyprog_mapscreen_80066D90", func_800692A4); // 0x800692A4
