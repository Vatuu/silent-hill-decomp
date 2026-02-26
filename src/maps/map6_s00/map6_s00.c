#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
#include "maps/map6/map6_s00.h"
#include "maps/particle.h"
#include "maps/characters/air_screamer.h"
#include "maps/characters/groaner.h"
#include "maps/characters/player.h"
#include "maps/characters/romper.h"

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

INCLUDE_RODATA("maps/map6_s00/nonmatchings/map6_s00", D_800CA854);

INCLUDE_RODATA("maps/map6_s00/nonmatchings/map6_s00", D_800CA858);

INCLUDE_RODATA("maps/map6_s00/nonmatchings/map6_s00", D_800CA864);

INCLUDE_RODATA("maps/map6_s00/nonmatchings/map6_s00", D_800CA87C);

INCLUDE_RODATA("maps/map6_s00/nonmatchings/map6_s00", D_800CA894);

INCLUDE_RODATA("maps/map6_s00/nonmatchings/map6_s00", D_800CA8AC);

INCLUDE_RODATA("maps/map6_s00/nonmatchings/map6_s00", sharedData_800CAA98_0_s01);

// TODO: Move this line into separate `Chara_AirScreamer` split.
#include "../src/maps/characters/air_screamer.c" // 0x800D18FC

// TODO: Move this line into separate `Chara_Groaner` split.
#include "../src/maps/characters/groaner.c" // 0x800E2934

// TODO: Move this line into separate `Chara_Romper` split.
#include "../src/maps/characters/romper.c" // 0x800E6F0C

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800EAB00

INCLUDE_ASM("maps/map6_s00/nonmatchings/map6_s00", func_800EAB10);

#include "maps/shared/Map_RoomBgmInit_6_s00.h" // 0x800EAD0C

void Gfx_LoadingScreen_StageString(void) {}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800EAFF8

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.5)\tWhat's_this! ~E ",
    "~J0(0.1)\t~E ",
    "~J0(0.1)\t~E ",
    "~J0(0.1)\t~E ",
    "~J1(4.0)\tNot_again...!? ~N\n\t\t\tNo,_this_time_it_feels_different. ",
    "~J1(4.5)\tRather_than_shifting ~N\n\t\t\tfrom_reality_to_a_nightmare, ",
    "~J1(4.5)\tthis_is_more_like_reality ~N\n\t\t\tbecoming_a_nightmare. ",
    "~J1(6.0)\tI_don't_like_this_feeling. ~N\n\t\t\tLike_something_bad ~N\n\t\t\twill_happen... ",
    "~J1(4.0)\tNo_doubt,_something_terrible ~N\n\t\t\tis_going_on... ~E ",
    "\tThe_cover_has_been_removed... ",
    "\tCould_Cybil_have_gotten ~N\n\tto_the_Amusement_Park_from_here? ~E ",
    "~C3\tLAKE_SIDE_AMUSEMENT_PARK ~E "
};

void MapEvent_CommonItemTake(void) // 0x800EB090
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 22:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M6S00_HealthDrink;
            break;

        case 23:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M6S00_ShotgunShells;
            break;

        case 24:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M6S00_FirstAidKit;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800EB11C(void) // 0x800EB11C
{
    typedef enum _EventState
    {
        EventState_Skip = 19
    } e_EventState;

    typedef struct
    {
        SPRT*     sprt_0;
        DR_TPAGE* tpage_4;
        DR_STP*   stp_8;
        u8        unk_C[4];
        u8        unk_10[4];
        s32       activeBufferIdx_14;
    } g_GteScratchData_func_800DD2D4;
    g_GteScratchData_func_800DD2D4* scratchData;

    s32 i;
    s32 vol;

    // Skip.
    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 &&
        g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] < EventState_Skip)
    {
        SysWork_StateStepSet(0, EventState_Skip);
    }

    if (g_SysWork.sysStateStep_C[0] >= 5 && g_SysWork.sysStateStep_C[0] < 13)
    {
        scratchData                     = PSX_SCRATCH_ADDR(0);
        scratchData->activeBufferIdx_14 = g_ActiveBufferIdx;
        scratchData->sprt_0             = (SPRT*)GsOUT_PACKET_P;
        for (i = 0; i < 2; i++)
        {
            setCodeWord(scratchData->sprt_0, PRIM_RECT | RECT_BLEND | RECT_TEXTURE, PACKED_COLOR(128, 128, 128, 0));
            setXY0Fast(scratchData->sprt_0, ((i << 8) - 160), -112);
            scratchData->sprt_0->u0 = 0;
            scratchData->sprt_0->v0 = (scratchData->activeBufferIdx_14 == 0) ? 32 : 0;
            setWH(scratchData->sprt_0, (i == 0) ? 256 : 64, 224);
            addPrimFast(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratchData->sprt_0, 4);

            scratchData->sprt_0++;
            scratchData->tpage_4 = (DR_TPAGE*)scratchData->sprt_0;
            setDrawTPage(scratchData->tpage_4, 0, 0, getTPage(2, 0, ((scratchData->activeBufferIdx_14 << 4) + (i << 2)) << 6, (((scratchData->activeBufferIdx_14 << 4) >> 4) & 1) << 8));

            AddPrim(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratchData->tpage_4);
            scratchData->tpage_4++;
            scratchData->sprt_0 = (SPRT*)scratchData->tpage_4;
        }

        scratchData->stp_8 = (DR_STP*)scratchData->sprt_0;
        SetDrawStp(scratchData->stp_8, 1);
        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ORDERING_TABLE_SIZE - 1], scratchData->stp_8);
        scratchData->stp_8++;
        SetDrawStp(scratchData->stp_8, 0);
        addPrim(&g_OrderingTable2[g_ActiveBufferIdx].org[0], scratchData->stp_8);
        scratchData->stp_8++;
        GsOUT_PACKET_P = (PACKET*)scratchData->stp_8;
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            ScreenFade_ResetTimestep();
            g_SysWork.field_30    = 20;
            g_SysWork.flags_22A4 |= SysFlag2_3;

            Fs_QueueStartRead(FILE_ANIM_RSU_DMS, FS_BUFFER_15);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_15);

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();

            D_800F0684 = 0;
            D_800F0044 = 0;
            D_800F0040 = 0;

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 53, false);
            Game_TurnFlashlightOn();

            sharedFunc_800D08B8_0_s00(2, 127);
            Particle_SystemUpdate(0, g_SavegamePtr->mapOverlayId_A4, 0);
            sharedFunc_800D0B18_0_s00(6);

            SD_Call(Sfx_Unk1522);
            SD_Call(Sfx_Unk1599);
            D_800F0686 = 0;
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrementAfterTime(&D_800F0040, Q12(12.5f), Q12(0.0f), Q12(22.0f), true, false);
            break;

        case 2:
            SysWork_StateStepIncrementAfterTime(&D_800F0040, Q12(12.5f), Q12(0.0f), Q12(22.0f), true, true);
            break;

        case 3:
            D_800F0040 = Q12(23.0f);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 52, false);
            SysWork_StateStepIncrement(0);

        case 4:
            Map_MessageWithAudio(15, &D_800F0684, &D_800F0038);
            break;

        case 5:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 126, false);
            Savegame_EventFlagSet(EventFlag_413);
            SysWork_StateStepIncrement(0);

        case 6:
            Map_MessageWithAudio(16, &D_800F0684, &D_800F0038);
            SysWork_StateStepIncrementAfterTime(&D_800F0040, Q12(18.0f), Q12(23.0f), Q12(43.0f), true, false);
            break;

        case 7:
            SysWork_StateStepIncrementAfterTime(&D_800F0040, Q12(18.0f), Q12(23.0f), Q12(43.0f), true, true);
            break;

        case 8:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 133, false);
            SysWork_StateStepIncrement(0);

        case 9:
            SysWork_StateStepIncrementAfterTime(&D_800F0040, Q12(4.2f), Q12(44.0f), Q12(47.0f), true, true);
            break;

        case 10:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 114, false);
            Savegame_EventFlagSet(EventFlag_402);
            sharedFunc_800D08B8_0_s00(6, 127);
            Particle_SystemUpdate(0, g_SavegamePtr->mapOverlayId_A4, 0);
            Savegame_EventFlagSet(EventFlag_414);
            D_800F0044 = Q12(3.4f);
            SysWork_StateStepIncrement(0);

        case 11:
            Map_MessageWithAudio(17, &D_800F0684, &D_800F0038);

        case 12:
            SysWork_StateStepIncrementAfterTime(&D_800F0040, Q12(4.0f), Q12(48.0f), Q12(57.0f), true, true);
            D_800F0044 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 1.0f);
            break;

        case 13:
            D_800F0044 = Q12(5.2f);
            SysWork_StateStepIncrement(0);

        case 14:
            Map_MessageWithAudio(18, &D_800F0684, &D_800F0038);

        case 15:
            SysWork_StateStepIncrementAfterTime(&D_800F0040, Q12(4.0f), Q12(58.0f), Q12(67.0f), true, true);
            D_800F0044 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.7f);
            break;

        case 16:
            SysWork_StateStepIncrementDelayed(Q12(2.2f), false);
            D_800F0044 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.7f);
            break;

        case 17:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 127, false);
            Savegame_EventFlagSet(EventFlag_415);
            SysWork_StateStepIncrement(0);

        case 18:
            MapMsg_DisplayAndHandleSelection(false, 19, 0, 0, 0, false);
            SysWork_StateStepIncrementAfterTime(&D_800F0040, Q12(2.5f), Q12(68.0f), Q12(143.0f), true, false);

            D_800F0044 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.4f);
            if (D_800F0044 > Q12(16.0f))
            {
                D_800F0044 = Q12(16.0f);
            }
            break;

        case EventState_Skip:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            D_800F0040 = NO_VALUE;

            Savegame_EventFlagSet(EventFlag_402);
            Savegame_EventFlagClear(EventFlag_414);

            SD_Call(19);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            Sd_SfxStop(Sfx_Unk1522);
            Sd_SfxStop(Sfx_Unk1599);
            sharedFunc_800D08B8_0_s00(6, 127);
            Particle_SystemUpdate(0, g_SavegamePtr->mapOverlayId_A4, 0);
            break;
    }

    func_800EC4B4(D_800F0044);

    if (g_SysWork.sysStateStep_C[0] >= 1 && g_SysWork.sysStateStep_C[0] < 17)
    {
        if (g_SysWork.sysStateStep_C[0] >= 2)
        {
            D_800F0686 += g_DeltaTime >> 3;
        }

        if (D_800F0686 > Q12(1.0f))
        {
            D_800F0686 = Q12(1.0f);
        }

        vol = (D_800F0686 + Math_Sin(D_800F0686 >> 2)) >> 5;
        if (vol > 255)
        {
            vol = 255;
        }
        Sd_SfxAttributesUpdate(Sfx_Unk1522, 0, ~vol, 0);

        vol = (Q12(1.0f) - Math_Cos((D_800F0686) >> 2)) >> 4;
        if (vol > 255)
        {
            vol = 255;
        }
        Sd_SfxAttributesUpdate(Sfx_Unk1599, 0, ~vol, 0);
    }
    else if (g_SysWork.sysStateStep_C[0] >= 17 && g_SysWork.sysStateStep_C[0] < 20)
    {
        D_800F0686 -= g_DeltaTime >> 3;
        if (D_800F0686 < 0)
        {
            D_800F0686 = 0;
        }

        vol = D_800F0686 >> 4;
        if (vol > 255)
        {
            vol = 255;
        }
        Sd_SfxAttributesUpdate(Sfx_Unk1522, 0, ~vol, 0);

        vol = D_800F0686 >> 4;
        if (vol > 255)
        {
            vol = 255;
        }
        Sd_SfxAttributesUpdate(Sfx_Unk1599, 0, ~vol, 0);
    }

    if (g_SysWork.sysStateStep_C[0] >= 5 && g_SysWork.sysStateStep_C[0] < 10)
    {
        func_800894DC();
    }

    if (D_800F0040 >= 0)
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800F0040, FS_BUFFER_15);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800F0668, &D_800F0678, NULL, D_800F0040, FS_BUFFER_15));
        vcUserCamTarget(&D_800F0668, NULL, true);
        vcUserWatchTarget(&D_800F0678, NULL, true);
    }
}

void Map_WorldObjectsInit(void) // 0x800EBCE8
{
    if (!Savegame_EventFlagGet(EventFlag_402))
    {
        g_LoadingScreenImg.v = 0;
        Fs_QueueStartReadTim(FILE_TIM_GROUND_TIM, IMAGE_BUFFER_4, &g_LoadingScreenImg);
    }

    WorldObjectNoRotInit(&g_WorldObject_Window, "WINDOW_H", -155.0f, 3.0f, 20.0f);
    WorldObjectNoRotInit(&g_WorldObject_DrOpen1, "DROPEN1_", -190.5f, 0.0f, 132.5f);
    WorldObjectNoRotInit(&g_WorldObject_DrOpen2, "DROPEN2_", -190.5f, -0.05f, 132.214f);
    WorldObjectNoRotInit(&g_WorldObject_DrClose, "DRCLOSE_", -189.5f, 0.0f, 132.5f);

    func_8008D448();
    Game_FlashlightAttributesFix();

    g_SysWork.pointLightIntensity_2378 = Q12(1.0f);

    switch (g_SavegamePtr->gameDifficulty_260)
    {
        case GameDifficulty_Normal:
            g_SysWork.npcId_2280 = 4;
            break;

        case GameDifficulty_Easy:
            g_SysWork.npcId_2280 = 3;
            break;

        default:
            g_SysWork.npcId_2280 = 5;
            break;
    }

    if (Savegame_EventFlagGet(EventFlag_428))
    {
        Savegame_EventFlagClear(EventFlag_428);
        Game_TurnFlashlightOn();
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x800EBEE0
{
    s32 flags;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    flags = 0;

    if (!Savegame_EventFlagGet(EventFlag_401) && Savegame_EventFlagGet(EventFlag_403))
    {
        Savegame_EventFlagSet(EventFlag_401);
        func_8003A16C();
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, 7, -1, 7))
    {
        if (!Savegame_EventFlagGet(EventFlag_402))
        {
            flags |= 1 << 1;
        }

        Text_Debug_PositionSet(30, 30);
    }

    if (PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) || PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5))
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Window.object_0, &g_WorldObject_Window.position_1C, &(SVECTOR3){ 0, 0, 0 });
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5))
    {
        if (PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4) || PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
        {
            if (Savegame_EventFlagGet(EventFlag_424))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_DrOpen1.object_0, &g_WorldObject_DrOpen1.position_1C, &(SVECTOR3){ 0, 0, 0 });
                WorldGfx_ObjectAdd(&g_WorldObject_DrOpen2.object_0, &g_WorldObject_DrOpen2.position_1C, &(SVECTOR3){ 0, 0, 0 });
                flags |= 1 << 1;
            }
            else
            {
                WorldGfx_ObjectAdd(&g_WorldObject_DrClose.object_0, &g_WorldObject_DrClose.position_1C, &(SVECTOR3){ 0, 0, 0 });
            }
        }
    }

    func_80069844(0xFFFF);
    func_8006982C(flags);

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M6S00_HealthDrink))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M6S00_ShotgunShells))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -5, -1, -5) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M6S00_FirstAidKit))
        {
            WorldGfx_ObjectAdd(g_CommonWorldObjects, &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }
}

static inline s32 inline_sub(s32 arg0, s32 arg1)
{
    return arg0 - arg1;
}

void func_800EC4B4(s32 arg0) // 0x800EC4B4
{
    s32                posX;
    s32                posZ;
    s32                posY;
    s32                temp_v1_14;
    s32                var_a2;
    s32                var_a3;
    s32                var_a3_2;
    s32                j;
    s32                i;
    s32                var_t0_2;
    s32                var_t1_2;
    s32                var_t2_2;
    s32                var_t3;
    s32                temp;
    s_func_800EC4B4*   ptr;
    s_func_800EC4B4_2* ptr2;

    ptr2 = FS_BUFFER_1;
    ptr  = PSX_SCRATCH;

    posX = FP_FROM(g_SysWork.playerWork_4C.player_0.position_18.vx, Q12_SHIFT);
    posY = FP_FROM(g_SysWork.playerWork_4C.player_0.position_18.vy, Q12_SHIFT);
    posZ = FP_FROM(g_SysWork.playerWork_4C.player_0.position_18.vz, Q12_SHIFT);

    ptr->field_5C.vx = posX << 8;
    ptr->field_5C.vy = posY << 8;
    ptr->field_5C.vz = posZ << 8;

    func_80049C2C(&ptr->field_4, FP_TO(posX, Q12_SHIFT), FP_TO(posY, Q12_SHIFT), FP_TO(posZ, Q12_SHIFT));

    gte_SetRotMatrix(&ptr->field_4);
    gte_SetTransMatrix(&ptr->field_4);
    gte_ReadGeomScreen(&ptr->field_84);

    ptr->field_24      = GsIDMATRIX;
    ptr->field_24.t[0] = Q12(-0.75f); // TODO: Or Q8, since it's a `MATRIX`?
    ptr->field_24.t[2] = Q12(15.0f);
    ptr->field_24.t[1] = Q12(0.0f);
    ptr->field_68.vx   = Q12(0.0f);
    ptr->field_68.vy   = Q12(-1.0f);
    ptr->field_68.vz   = Q12(0.0f);

    for (i = 0; i < 287; i += 3)
    {
        for (j = 0; j < 3; j++)
        {
            Math_SetSVectorFastSum(&ptr->field_44[j], inline_sub((((i + j) % 17) << 8) - 0x1400, (u16)ptr->field_5C.vx),
                                   -ptr->field_5C.vy, inline_sub(-0x800 - (u16)ptr->field_5C.vz, ((i + j) / 17) << 8));
        }

        gte_ldv3c(&ptr->field_44[0]);
        gte_rtpt();
        gte_stsxy3c(&ptr2->field_0[i / 17][i % 17]);
        gte_stsz3c(&ptr2->field_484[i / 17][i % 17]);
    }

    for (i = 288; i < 289; i++)
    {
        Math_SetSVectorFastSum(&ptr->field_44[0], inline_sub(((i % 17) << 8) - 0x1400, (u16)ptr->field_5C.vx),
                               -ptr->field_5C.vy, inline_sub(-0x800 - (u16)ptr->field_5C.vz, (i / 17) << 8));

        gte_ldv0(&ptr->field_44[0]);
        gte_rtps();
        gte_stsxy(&ptr2->field_0[i % 17][i / 17]);
        gte_stsz(&ptr2->field_484[i % 17][i / 17]);
    }

    for (i = 0; i < 17; i++)
    {
        for (j = 0; j < 17; j++)
        {
            *(s32*)&ptr->field_44[0] = ((j << 8) - 0x800) & 0xFFFF;
            ptr->field_44[0].vz      = 0x800 - (i << 8);

            if (arg0 < D_800F0084[j][i].vx * 4)
            {
                ptr->field_90[i][j] = 0;
                ptr->field_1B4      = 0x80;
            }
            else if (arg0 >= D_800F0084[j][i].vy * 4)
            {
                ptr->field_90[i][j] = 3;
                ptr->field_1B4      = 0;
            }
            else
            {
                ptr->field_1B8 = arg0 - D_800F0084[j][i].vx * 4;
                ptr->field_1BC = (D_800F0084[j][i].vy - D_800F0084[j][i].vx) * 4;
                ptr->field_1C0 = ptr->field_1BC >> 2;

                if (ptr->field_1B8 < ptr->field_1C0)
                {
                    ptr->field_90[i][j] = 0;
                    ptr->field_1B4      = ((ptr->field_1C0 - ptr->field_1B8) << 7) / ptr->field_1C0;
                }
                else
                {
                    ptr->field_1C4 = ptr->field_1BC >> 1;

                    if (ptr->field_1B8 < ptr->field_1C4)
                    {
                        ptr->field_90[i][j] = 1;
                        ptr->field_1B4      = ((ptr->field_1C4 - ptr->field_1B8) << 7) / (ptr->field_1C4 - ptr->field_1C0);
                    }
                    else
                    {
                        ptr->field_1C0 = (ptr->field_1BC * 3) >> 2;

                        if (ptr->field_1B8 < ptr->field_1C0)
                        {
                            ptr->field_90[i][j] = 2;
                            ptr->field_1B4      = ((ptr->field_1C0 - ptr->field_1B8) << 7) / (ptr->field_1C0 - ptr->field_1C4);
                        }
                        else
                        {
                            ptr->field_90[i][j] = 3;
                            ptr->field_1BC     -= (ptr->field_1BC - ptr->field_1C0) >> 1;

                            if (ptr->field_1BC < ptr->field_1B8)
                            {
                                ptr->field_1B4 = 0;
                            }
                            else
                            {
                                ptr->field_1B4 = ((ptr->field_1BC - ptr->field_1B8) << 7) / (ptr->field_1BC - ptr->field_1C0);
                            }
                        }
                    }
                }
            }

            func_80055ECC(&ptr->field_70, &ptr->field_44, &ptr->field_68, &ptr->field_24);

            ptr2->field_908[i][j][0].r = MIN((ptr->field_70.r * ptr->field_1B4) >> 7, 0xFF);
            ptr2->field_908[i][j][0].g = MIN((ptr->field_70.g * ptr->field_1B4) >> 7, 0xFF);
            ptr2->field_908[i][j][0].b = MIN((ptr->field_70.b * ptr->field_1B4) >> 7, 0xFF);

            ptr2->field_908[i][j][1].r = MIN((ptr->field_70.r * (0x80 - ptr->field_1B4)) >> 7, 0xFF);
            ptr2->field_908[i][j][1].g = MIN((ptr->field_70.g * (0x80 - ptr->field_1B4)) >> 7, 0xFF);
            ptr2->field_908[i][j][1].b = MIN((ptr->field_70.b * (0x80 - ptr->field_1B4)) >> 7, 0xFF);
        }
    }

    ptr->field_0 = (POLY_GT4*)GsOUT_PACKET_P;

    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 16; j++)
        {
            ptr->field_88 = (ptr2->field_484[i][j] + ptr2->field_484[i + 1][j] +
                             ptr2->field_484[i][j + 1] + ptr2->field_484[i + 1][j + 1]) >>
                            2;

            if (ptr->field_88 + 0x80 < ptr->field_84)
            {
                continue;
            }

            if ((ptr->field_88 + 0x80 >> 3) >= 0x800)
            {
                continue;
            }

            temp = 0x2F;

            for (var_t2_2 = 0; var_t2_2 < 5; var_t2_2++)
            {
                for (var_a3 = 0; var_a3 < 2; var_a3++)
                {
                    for (var_a2 = 0; var_a2 < 2; var_a2++)
                    {
                        if (ptr->field_90[i + var_a3][j + var_a2] == var_t2_2)
                        {
                            ptr->field_74[(var_a3 * 2) + var_a2].r = ptr2->field_908[i + var_a3][j + var_a2][0].r;
                            ptr->field_74[(var_a3 * 2) + var_a2].g = ptr2->field_908[i + var_a3][j + var_a2][0].g;
                            ptr->field_74[(var_a3 * 2) + var_a2].b = ptr2->field_908[i + var_a3][j + var_a2][0].b;
                        }
                        else if ((ptr->field_90[i + var_a3][j + var_a2] + 1) == var_t2_2)
                        {
                            ptr->field_74[(var_a3 * 2) + var_a2].r = ptr2->field_908[i + var_a3][j + var_a2][1].r;
                            ptr->field_74[(var_a3 * 2) + var_a2].g = ptr2->field_908[i + var_a3][j + var_a2][1].g;
                            ptr->field_74[(var_a3 * 2) + var_a2].b = ptr2->field_908[i + var_a3][j + var_a2][1].b;
                        }
                        else
                        {
                            ptr->field_74[(var_a3 * 2) + var_a2].r = 0;
                            ptr->field_74[(var_a3 * 2) + var_a2].g = 0;
                            ptr->field_74[(var_a3 * 2) + var_a2].b = 0;
                        }
                    }
                }

                if (!(ptr->field_74[0].r == 0 && ptr->field_74[0].g == 0 && ptr->field_74[0].b == 0) ||
                    !(ptr->field_74[1].r == 0 && ptr->field_74[1].g == 0 && ptr->field_74[1].b == 0) ||
                    !(ptr->field_74[2].r == 0 && ptr->field_74[2].g == 0 && ptr->field_74[2].b == 0) ||
                    !(ptr->field_74[3].r == 0 && ptr->field_74[3].g == 0 && ptr->field_74[3].b == 0))
                {
                    ptr->field_1B8 = !(var_t2_2 < 2) + !(var_t2_2 < 3);
                    temp_v1_14     = ptr->field_1B8 + 5;

                    ptr->field_8E = temp_v1_14 | 0x20;
                    ptr->field_8C = getClut(g_LoadingScreenImg.clutX, g_LoadingScreenImg.clutY + var_t2_2);

                    if (var_t2_2 == 0)
                    {
                        var_t0_2 = 0;
                        var_a3_2 = 0;
                        var_t3   = 0x2F;
                        var_t1_2 = temp;
                    }
                    else if (var_t2_2 == 4)
                    {
                        var_t0_2       = 0;
                        ptr->field_1B8 = (((u32)i & 7) > 0) + ((i & 7) == 7);
                        ptr->field_1BC = (((u32)j & 7) > 0) + ((j & 7) == 7);

                        if (ptr->field_1B8 == 1)
                        {
                            if (ptr->field_1BC == 1)
                            {
                                var_a3_2 = 0;
                            }
                            else
                            {
                                var_a3_2 = 0x90;
                            }
                        }
                        else
                        {
                            if (ptr->field_1BC == 1)
                            {
                                var_a3_2 = 0x30;
                            }
                            else
                            {
                                var_a3_2 = 0x60;
                            }
                        }

                        if (ptr->field_1B8 >= 2)
                        {
                            var_t3    = -0x2F;
                            var_t0_2 += 0x2F;
                        }
                        else
                        {
                            var_t3 = 0x2F;
                        }

                        if (ptr->field_1BC <= 0)
                        {
                            var_t1_2  = -0x2F;
                            var_a3_2 += 0x2F;
                        }
                        else
                        {
                            var_t1_2 = 0x2F;
                        }
                    }
                    else
                    {
                        if (j & 4)
                        {
                            var_a3_2 = 0xBF - ((j & 3) * 0x30);
                            var_t1_2 = -0x2F;
                        }
                        else
                        {
                            var_a3_2 = ((j & 3) * 3) * 0x10;
                            var_t1_2 = 0x2F;
                        }

                        if (i & 4)
                        {
                            var_t0_2 = ((i & 3) * 0x30) + 0x40;
                            var_t3   = 0x2F;
                        }
                        else
                        {
                            var_t0_2 = 0xFF - ((i & 3) * 0x30);
                            var_t3   = -0x2F;
                        }
                    }

                    setPolyGT4(ptr->field_0);
                    setSemiTrans(ptr->field_0, 1);

                    if (var_t2_2 == 4 && ptr->field_1B8 != ptr->field_1BC && ptr->field_1B8 != 1 && ptr->field_1BC != 1)
                    {
                        setXY0Fast(ptr->field_0, ptr2->field_0[i][j + 1].vx, ptr2->field_0[i][j + 1].vy);
                        setXY1Fast(ptr->field_0, ptr2->field_0[i][j].vx, ptr2->field_0[i][j].vy);
                        setXY2Fast(ptr->field_0, ptr2->field_0[i + 1][j + 1].vx, ptr2->field_0[i + 1][j + 1].vy);
                        setXY3Fast(ptr->field_0, ptr2->field_0[i + 1][j].vx, ptr2->field_0[i + 1][j].vy);

                        setRGB0Fast(ptr->field_0, ptr->field_74[1].r, ptr->field_74[1].g, ptr->field_74[1].b);
                        setRGB1Fast(ptr->field_0, ptr->field_74[0].r, ptr->field_74[0].g, ptr->field_74[0].b);
                        setRGB2Fast(ptr->field_0, ptr->field_74[3].r, ptr->field_74[3].g, ptr->field_74[3].b);
                        setRGB3Fast(ptr->field_0, ptr->field_74[2].r, ptr->field_74[2].g, ptr->field_74[2].b);

                        *(s32*)&ptr->field_0->u0 = (var_a3_2 + var_t1_2) + (var_t0_2 << 8) + (ptr->field_8C << 16);
                        *(s32*)&ptr->field_0->u1 = ((var_a3_2 + var_t1_2) - var_t1_2) + (var_t0_2 << 8) + (ptr->field_8E << 16);
                        *(u16*)&ptr->field_0->u2 = (var_a3_2 + var_t1_2) + ((var_t0_2 + var_t3) << 8);
                        *(u16*)&ptr->field_0->u3 = ((var_a3_2 + var_t1_2) - var_t1_2) + ((var_t0_2 + var_t3) << 8);
                    }
                    else
                    {
                        setXY0Fast(ptr->field_0, ptr2->field_0[i][j].vx, ptr2->field_0[i][j].vy);
                        setXY1Fast(ptr->field_0, ptr2->field_0[i][j + 1].vx, ptr2->field_0[i][j + 1].vy);
                        setXY2Fast(ptr->field_0, ptr2->field_0[i + 1][j].vx, ptr2->field_0[i + 1][j].vy);
                        setXY3Fast(ptr->field_0, ptr2->field_0[i + 1][j + 1].vx, ptr2->field_0[i + 1][j + 1].vy);

                        setRGB0Fast(ptr->field_0, ptr->field_74[0].r, ptr->field_74[0].g, ptr->field_74[0].b);
                        setRGB1Fast(ptr->field_0, ptr->field_74[1].r, ptr->field_74[1].g, ptr->field_74[1].b);
                        setRGB2Fast(ptr->field_0, ptr->field_74[2].r, ptr->field_74[2].g, ptr->field_74[2].b);
                        setRGB3Fast(ptr->field_0, ptr->field_74[3].r, ptr->field_74[3].g, ptr->field_74[3].b);

                        *(s32*)&ptr->field_0->u0 = var_a3_2 + (var_t0_2 << 8) + (ptr->field_8C << 16);
                        *(s32*)&ptr->field_0->u1 = (var_a3_2 + var_t1_2) + (var_t0_2 << 8) + (ptr->field_8E << 16);
                        *(u16*)&ptr->field_0->u2 = var_a3_2 + ((var_t0_2 + var_t3) << 8);
                        *(u16*)&ptr->field_0->u3 = (var_a3_2 + var_t1_2) + ((var_t0_2 + var_t3) << 8);
                    }

                    addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[(ptr->field_88 + 0x80) >> 3], ptr->field_0);
                    ptr->field_0++;
                }
            }
        }
    }

    GsOUT_PACKET_P = (PACKET*)ptr->field_0;
}
