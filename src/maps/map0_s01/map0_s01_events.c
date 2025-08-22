#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"
#include "maps/map0/map0_s01.h"
#include "maps/shared.h"

void Event_MapItemTake() // 0x800DC3C8
{
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
            StoreImage(&D_800CCAC8, IMAGE_BUFFER);
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
            LoadImage(&D_800CCAC8, IMAGE_BUFFER);
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
            LoadImage(&D_800CCAC8, IMAGE_BUFFER);
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
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, &D_800CCA64, 0, FS_BUFFER_11);

            // Set camera.
            vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800E2380, &D_800E2390, NULL, 0, FS_BUFFER_11));
            vcUserCamTarget(&D_800E2380, NULL, true);
            vcUserWatchTarget(&D_800E2390, NULL, true);

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
void func_800DC85C() {}

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
            D_800E23A0                        = 0;
            SysWork_StateStepIncrement();

        case 1:
            func_800869E4(68, &D_800E23A0, &D_800DE128);
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

extern s_eventPosition D_800E2490;
extern s_eventThing g_eventThing4A0;
extern s_eventThing g_eventThing4D0;
extern s_eventThing g_eventThing500;
extern s_eventThing g_eventThing530;

static inline void EventPositionInit_int(s_eventPosition* ep, s32 x, s32 y, s32 z, s32 a, s16 b)
{
    Math_Vector3Set(&ep->v3_0, x, y, z);
    ep->field_C = a;
    ep->field_10 = b;
}
#define EventPositionInit(ep, x, y, z, a, b)\
    EventPositionInit_int(ep, Q19_12((x)), Q19_12((y)), Q19_12((z)), a, b)


void func_800DC9C8() // 0x800DC9C8
{
    D_800E23A1         = 0xE0;
    Math_Vector3f(&D_800E2490.v3_0, 0.0f, 0.0f, 280.0f);

    func_8003C8F8(&D_800E23B0[0], "IN_BLD1_");
    func_8003C8F8(&D_800E23D0[0], "IN1_HIDE");
    func_8003C8F8(&D_800E23F0[0], "BRK_BLD1");
    func_8003C8F8(&D_800E23F0[1], "BRK_GLS1");
    func_8003C8F8(&D_800E23F0[2], "BRK_GLS2");
    func_8003C8F8(&D_800E2450[0], "OUT1_HID");
    func_8003C8F8(&D_800E2450[1], "OUT_BLD_");

    EventPositionInit(&g_eventThing4A0.ep_1C, 5.089844f, -1.009766f, 274.119873f, 0x016C0000, 0);
    func_8003C8F8(&g_eventThing4A0.thing_0, "KNIFE_HI");

    EventPositionInit(&g_eventThing4D0.ep_1C, 5.179932f, -1.0f, 267.279785f, 0x04EEFFDE, 0);
    func_8003C8F8(&g_eventThing4D0.thing_0, "FLASH_HI");

    EventPositionInit(&g_eventThing500.ep_1C, 5.239990f, -1.0f, 267.209961f, 0x02880000, 0);
    func_8003C8F8(&g_eventThing500.thing_0, "MAP_HIDE");

    EventPositionInit(&g_eventThing530.ep_1C, 2.309815f, -0.599854f, 273.949951f, 0x06880000, 0);
    func_8003C8F8(&g_eventThing530.thing_0, "RADIO_HI");

    if ((g_SavegamePtr->eventFlags_168[1] & ((1 << 8) | (1 << 15))) == (1 << 8))
    {
        g_SysWork.flags_22A4 |= (1 << 5) | (1 << 9);

        Chara_Load(0, Chara_AirScreamer, &g_SysWork.npcCoords_FC0, NO_VALUE, 0, 0);

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

    D_800E239C = 0;
    D_800E2560 = 0;

    // There are 6 NPCs max. Maybe related?
    func_8003C8F8(&D_800E2570[0], D_800A99E4.field_8);
    func_8003C8F8(&D_800E2570[1], D_800A99E4.field_C);
    func_8003C8F8(&D_800E2570[2], D_800A99E4.field_10);
    func_8003C8F8(&D_800E2570[3], D_800A99E4.field_14);
    func_8003C8F8(&D_800E2570[4], D_800A99E4.field_18);
    func_8003C8F8(&D_800E2570[5], D_800A99E4.field_1C);
}

const SVECTOR3 D_800CCB84 = {};

INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01_events", func_800DCCF4);

void func_800DD2EC(s32 arg0) // 0x800DD2EC
{
    s32 i;

    if (arg0 == 0)
    {
        for (i = 0; i <= 0; i++)
        {
            func_8003C92C(&D_800E23D0[i], &D_800E2490, &D_800CCB84);
        }

        for (i = 0; i <= 0; i++)
        {
            func_8003C92C(&D_800E23B0[i], &D_800E2490, &D_800CCB84);
        }

        return;
    }

    if (arg0 == 1)
    {
        for (i = 0; i < 2; i++)
        {
            func_8003C92C(&D_800E2450[i], &D_800E2490, &D_800CCB84);
        }

        return;
    }

    for (i = 0; i <= 0; i++)
    {
        func_8003C92C(&D_800E23D0[i], &D_800E2490, &D_800CCB84);
    }

    for (i = 0; i < 3; i++)
    {
        func_8003C92C(&D_800E23F0[i], &D_800E2490, &D_800CCB84);
    }
}
