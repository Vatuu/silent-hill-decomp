#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map2/map2_s01.h"

INCLUDE_RODATA("asm/maps/map2_s01/nonmatchings/map2_s01", D_800C9578);

INCLUDE_RODATA("asm/maps/map2_s01/nonmatchings/map2_s01", g_MapOverlayHeader);

INCLUDE_ASM("asm/maps/map2_s01/nonmatchings/map2_s01", func_800CB010);

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CB178

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CB2F8

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CB3B0

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CB514

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CB534

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CBDAC

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CC198

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CC7CC

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CCBF8

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CCC34

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CCC40

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CCDA0

s32 func_800CCF78()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CCF80

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CD030

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CD048

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CD070

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CD088

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CD0B0

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CD154

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CD164

void func_800CD170(void) {}

void func_800CD178(void) {}

void func_800CD180(void) {}

void func_800CD188(void) {}

void func_800CD190(void) {}

s32 func_800CD198()
{
    return 0;
}

void func_800CD1A0(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CD1A8

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CD1B8

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CD1F8

#include "maps/shared/Ai_Dahlia_Update.h" // 0x800CD20C

INCLUDE_ASM("asm/maps/map2_s01/nonmatchings/map2_s01", sharedFunc_800CD280_2_s01); // 0x800CD280

#include "maps/shared/sharedFunc_800CD2C8_2_s01.h" // 0x800CD2C8

INCLUDE_RODATA("asm/maps/map2_s01/nonmatchings/map2_s01", D_800CA618);

INCLUDE_ASM("asm/maps/map2_s01/nonmatchings/map2_s01", sharedSymbol_800CD4A0_2_s01); // 0x800CD4A0

#include "maps/shared/Ai_Dahlia_Init.h" // 0x800CDD64

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800CDDA0

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800CDDB4

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800CDDF8

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800CDE10

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800CDE1C

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800CDE30

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800CDE44

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800CDE58

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800CDEF4

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800CE558

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800CE56C

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800CE580

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800CE67C

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800CE730

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800CE750

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CE7B0

#include "maps/shared/Map_RoomIdxGet.h" // 0x800CE7C0

void func_800CE858(s32 arg0) // 0x800CE858
{
    (arg0 != 0) ? func_800CE88C() : sharedFunc_800CE934_0_s02();
}

void func_800CE88C(void)
{
    s32 soundCmd;

    switch (g_SavegamePtr->mapRoomIdx_A5)
    {
        case 5:
            soundCmd = 6;
            func_8003640C(soundCmd);
            break;
        case 18:
            if (!Savegame_EventFlagGet(EventFlag_379))
            {
                soundCmd = 29;
            }
            else
            {
                soundCmd = 7;
            }
            func_8003640C(soundCmd);
            break;
        case 17:
            soundCmd = 7;
            func_8003640C(soundCmd);
            break;
    }
}

#include "maps/shared/sharedFunc_800CE934_0_s02.h" // 0x800CE908

void func_800CEB94(void) {}

void func_800CEB9C(void)
{
    VECTOR3 vec = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    func_80086FE8(11, Sfx_Unk1334, &vec);
}

void func_800CEC30(void)
{
    VECTOR3 vec = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    if (g_MapEventParam->field_5 == 2)
    {
        if (Savegame_EventFlagGet(EventFlag_180))
        {
            func_80086FE8(38, Sfx_Unk1486, &vec);
            if (g_SysWork.sysState_8 == SysState_Gameplay)
            {
                Savegame_EventFlagSet(EventFlag_180);
            }
        }
        else
        {
            func_80086FE8(12, Sfx_Unk1486, &vec);
        }
    }
    else
    {
        func_80086FE8(12, Sfx_Unk1344, &vec);
    }
}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J1(1.9)\tWere_you_ringing_that_bell? ",
    "~J1(5.3)\tI've_been_expecting_you. ~N\n\t\t\tIt_was_foretold_by_Gyromancy. ",
    "~J1(1.8)\tWhat_are_you_talking_about? ~E ",
    "~J1(2.2)\tI_knew_you'd_come. ",
    "~J1(2.4)\tYou_want_the_girl,_right? ",
    "~J1(0.9)\tThe_girl? ",
    "~J1(1.7)\tYou're_talking_about_Cheryl? ",
    "~J1(2.8)\tI_see_everything. ~E ",
    "~J0(2.1)\tYou_know_something!? ~N\n\t\t\tTell_me! ~E ",
    "~J0(1.1)\tStay_back! ~E ",
    "~J1(4.0)\tNothing_is_to_be_gained_from ~N\n\t\t\tfloundering_about_at_random.  ",
    "~J1(2.3)\tYou_must_follow_the_path. ",
    "~J1(4.0)\tThe_path_of_the_hermit, ~N\n\t\t\tconcealed_by_Flauros... ",
    "~J1(3.6)\tWhat? ~N\n\t\t\tWhat_are_you_talking_about? ~E ",
    "~J0(4.0)\tHere,_the_Flauros, ~N\n\t\t\ta_cage_of_peace. ",
    "~J0(3.3)\tIt_can_break_through ~N\n\t\t\tthe_walls_of_darkness, ",
    "~J0(3.8)\tand_counteract_the_wrath_of ~N\n\t\t\tthe_underworld. ",
    "~J0(3.0)\tThese_will_help_you. ~E ",
    "~J0(4.2)\tMake_haste_to_the_hospital ~N\n\t\t\tbefore_it's_too_late. ~E ",
    "~J0(2.4)\tWait! ~N\n\t\t\tDon't_go_yet! ~E ",
    "\tThere_is_a_ ~C2 [Flauros] ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Drawbridge_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tBible. ~E ",
    "\tIt_won't_open. ",
    "\tIt_must_be_locked ~N\n\tfrom_the_other_side. ~E ",
    "\tThere's_a_collection_box. ~N\n\tNothing_inside. ~E ",
    "\tThere's_a_newspaper. ~N\n\tNothing_special. ~E ",
    "\tThere's_a_picture_on_the_wall. ~N\n\tNothing_special. ~E ",
    "\tThere's_a_candle_stand. ~N\n\tNothing_special. ~E "
};

void func_800CED44(void) // 0x800CED44
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 25:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S01_HealthDrink;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800CED88(void)
{
    s32 step;
    s_SubCharacter* dahlia;
    static const VECTOR3 soundPos = VECTOR3(12.0f, -1.2f, 24.0f);
    #define DAHLIA_PTR (&g_SysWork.npcs_1A0[0])
    #define PLAYER_PTR (&g_SysWork.player_4C.chara_0)
    #define CUTSCENE_SKIP_STATE 0x1F

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        (g_SysWork.sysStateStep_C[0] > 0) && (g_SysWork.sysStateStep_C[0] < CUTSCENE_SKIP_STATE))
    {
        SysWork_NextStateStepSet(CUTSCENE_SKIP_STATE);
    }
    step = g_SysWork.sysStateStep_C[0];
    switch (step)
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            Fs_QueueStartRead(FILE_ANIM_CHRC_DMS, FS_BUFFER_15);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_15);
            Chara_Load(0, Chara_Dahlia, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            func_80088D0C();
            Chara_Spawn(Chara_Dahlia, 0, Q12(20.0f), Q12(23.5f), 0, 3);
            sharedFunc_800D88AC_0_s00(DAHLIA_PTR);
            g_Timer0 = 0;
            g_SysWork.field_30 = 20;
            g_SysWork.flags_22A4 |= 8;
            func_80085EB8(0, PLAYER_PTR, 51, false);
            func_80085EB8(0, DAHLIA_PTR, 0, false);
            func_8003D03C();
            g_SavegamePtr->eventFlags_168[5] |= 0x400000;
            g_MapMsgSoundIdx = 0;
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 1:
            func_8008616C(2, false, 0, 0, false);
            break;
        case 2:
            Map_MessageWithAudio(15, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;
        case 3:
            Map_MessageWithAudio(18, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;
        case 4:
            Map_MessageWithAudio(23, &g_MapMsgSoundIdx, g_MapMsgSounds);
            func_80085E6C(Q12(1.2f), false);
            break;
        case 5:
            func_80085EB8(0, PLAYER_PTR, 113, false);
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 6:
            Map_MessageWithAudio(23, &g_MapMsgSoundIdx, g_MapMsgSounds);
            if (g_Timer0 < Q12(1.0f))
            {
                g_Timer0 = Q12(1.0f);
                break;
            }
            g_Timer0 += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(5.0f), Q12_SHIFT);
            if (g_Timer0 > Q12(23.0f))
            {
                g_Timer0 = Q12(23.0f);
            }
            break;
        case 7:
            Map_MessageWithAudio(0x18, &g_MapMsgSoundIdx, g_MapMsgSounds);
            if (g_Timer0 < Q12(1.0f))
            {
                g_Timer0 = Q12(1.0f);
                break;
            }
            g_Timer0 += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(5.0f), Q12_SHIFT);

            if (g_Timer0 > Q12(23.0f))
            {
                g_Timer0 = Q12(23.0f);
            }
            break;
        case 8:
            func_80085EB8(4, PLAYER_PTR, 0, false);
            func_80085E6C(Q12(0.8f), false);
            break;
        case 9:
            Map_MessageWithAudio(25, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;
        case 10:
            func_80085EB8(0, DAHLIA_PTR, 9, false);
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 11:
            func_80085E6C(Q12(0.5f), false);
            break;
        case 12:
            func_80085EB8(1, DAHLIA_PTR, 0, false);
            Map_MessageWithAudio(29, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;
        case 13:
            func_80085E6C(Q12(2.0f), false);
            Map_MessageWithAudio(29, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;
        case 14:
            func_80085EB8(0, DAHLIA_PTR, 10, false);
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 15:
            func_80085EB8(1, DAHLIA_PTR, 0, false);
            Map_MessageWithAudio(29, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;
        case 16:
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 17:
            Map_MessageWithAudio(29, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;
        case 18:
            func_80085EB8(0, DAHLIA_PTR, 8, false);
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 19:
            Map_MessageWithAudio(33, &g_MapMsgSoundIdx, g_MapMsgSounds);
            if (g_Timer0 >= Q12(142.0f))
            {
                g_Timer0 += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(10.0f), Q12_SHIFT);
        
                if (g_Timer0 > Q12(165.0f))
                {
                    g_Timer0 = Q12(165.0f);
                }
                break;
            }
            g_Timer0 = Q12(142.0f);
            break;
        case 20:
            func_80085E6C(Q12(0.3f), false);
            if (g_Timer0 < Q12(142.0f))
            {
                g_Timer0 = Q12(142.0f);
                break;
            }
            g_Timer0 += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(10.0f), Q12_SHIFT);

            if (g_Timer0 > Q12(165.0f))
            {
                g_Timer0 = Q12(165.0f);
            }
            break;
        case 21:
            func_80085EB8(0, DAHLIA_PTR, 1, false);
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 22:
            func_80085E6C(Q12(0.8f), false);
            if (g_Timer0 >= Q12(166.0f))
            {
                g_Timer0 += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(15.0f), Q12_SHIFT);
        
                if (g_Timer0 > Q12(180.0f))
                {
                    g_Timer0 = Q12(180.0f);
                }
                break;
            }
            g_Timer0 = Q12(166.0f);

            break;
        case 23:
            func_80085EB8(0, PLAYER_PTR, 111, false);
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 24:
            Map_MessageWithAudio(34, &g_MapMsgSoundIdx, g_MapMsgSounds);
            if (g_Timer0 < Q12(166.0f))
            {
                g_Timer0 = Q12(166.0f);
                break;
            }
            g_Timer0 += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(15.0f), Q12_SHIFT);

            if (g_Timer0 > Q12(253.0f))
            {
                g_Timer0 = Q12(253.0f);
            }
            break;
        case 25:
            if (g_Timer0 < Q12(166.0f))
            {
                g_Timer0 = Q12(166.0f);
            } 
            else
            {
                g_Timer0 += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(15.0f), Q12_SHIFT);
                if (g_Timer0 > Q12(253.0f))
                {
                    g_Timer0 = Q12(253.0f);
                    SysWork_StateStepIncrement();
                }
            }
            break;
        case 26:
            func_80085E6C(Q12(0.8f), false);
            break;
        case 27:
            func_8005DC1C(Sfx_Unk1323, &soundPos, 0x80, 0);
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 28:
            func_80085E6C(Q12(1.2f), false);
            break;
        case 29:
            func_8005DC1C(Sfx_Unk1324, &soundPos, 0x80, 0);
            func_80088F94(DAHLIA_PTR, 0, 0);
            SysWork_StateStepIncrement();
            /* fallthrough */
        case 30:
            func_80085E6C(Q12(0.5f), false);
            break;
        case CUTSCENE_SKIP_STATE:
            func_8008616C(2, true, 0, 0, false);
            if (g_SysWork.sysStateStep_C[0] != CUTSCENE_SKIP_STATE)
            {
                g_Timer0 = Q12(253.0f);
            }
            break;
        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            func_8008616C(0, false, 0, 0, false);
            vcReturnPreAutoCamWork(true);
            func_8008616C(0, false, 2, 0, false);
            Savegame_EventFlagSet(EventFlag_179);
            Savegame_EventFlagSet(EventFlag_176);
            g_SavegamePtr->mapMarkingFlags_1D4[2] |= 0x40000;
            g_SavegamePtr->mapMarkingFlags_1D4[3] |= 0x100000;
            func_80088F94(DAHLIA_PTR, 0, 0);
            g_Timer0 = -1;
            Sd_EngineCmd(19);
            func_8003D01C();
            break;
    }

    if (step < 15)
    {
        if (step >= 10)
        {
            if (g_Timer0 < Q12(24.0f))
            {
                g_Timer0 = Q12(24.0f);
            }
            else
            {
                g_Timer0 += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(10.0f), Q12_SHIFT);
                if (g_Timer0 > Q12(141.0f))
                {
                    g_Timer0 = Q12(141.0f);
                }
            }
            
            if (step > 13)
            {
                dahlia = DAHLIA_PTR;
                if (((dahlia->model_0.anim_4.time_4 - Q12(Anim_StartKeyframeIdxGet(dahlia))) <= Q12(30.0f)) &&
                    ((dahlia->model_0.anim_4.time_4 - Q12(Anim_StartKeyframeIdxGet(dahlia))) >= Q12(21.0f)))
                {
                    Savegame_EventFlagSet(EventFlag_176);
                }
            }
        }
    }

    if (g_Timer0 >= 0)
    {
        Dms_CharacterGetPosRot(&PLAYER_PTR->position_18, (SVECTOR3*)&PLAYER_PTR->rotation_24,
                "HERO", g_Timer0, (s_DmsHeader*)FS_BUFFER_15);
        Dms_CharacterGetPosRot(&DAHLIA_PTR->position_18, (SVECTOR3*)&DAHLIA_PTR->rotation_24,
                "DAHLIA", g_Timer0, (s_DmsHeader*)FS_BUFFER_15);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CamPosTarget, &g_CamLookAtTarget, NULL,
                    g_Timer0, (s_DmsHeader*)FS_BUFFER_15));
        vcUserCamTarget(&g_CamPosTarget, NULL, true);
        vcUserWatchTarget(&g_CamLookAtTarget, NULL, true);
    }
}

void func_800CF798(void) // 0x800CF798
{
    Event_ItemTake(InventoryItemId_Flauros, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S01_PickupFlauros, 35);
}

void func_800CF7C4(void) // 0x800CF7C4
{
    Event_ItemTake(InventoryItemId_DrawbridgeKey, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S01_PickupDrawbridgeKey, 36);
}

extern u8 D_800D177C;
extern s_WorldObject_0 g_CommonWorldObjects[6];
extern s_WorldObjectDesc g_WorldObject_SavePad;
extern s_WorldObjectDesc g_WorldObject_Key;
extern s_WorldObjectDesc g_WorldObject_Item;
extern s_WorldObjectPose D_800D0528;

void func_800CF7F0(void)
{
    func_8003ED74(1, 1);

    Math_Vector3Set(&(g_WorldObject_Item.pose_1C), Q12(19.8289f), Q12(-1.3633f), Q12(24.0735f));
    WorldObject_ModelNameSet(&g_WorldObject_Item.object_0, "ITEM_HID");

    WorldObjectPoseInit(&g_WorldObject_Key.pose_1C, 20.073f, -0.858f, 24.1469f, 0.0f, 23.0f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObject_Key.object_0, "KEY_HIDE");

    WorldObjectPoseInit(&g_WorldObject_SavePad.pose_1C, 18.3345f, -0.9102f, 14.1985f, 0.0f, 10.5f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObject_SavePad.object_0, D_800A99E4.savePadName_4);

    D_800D177C = 0;
    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void func_800CF938(void)
{
    s_Savegame* temp_s0;
    MAP_CHUNK_CHECK_VARIABLE_DECL();
    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
            temp_s0 = g_SavegamePtr;
            if (Savegame_EventFlagGet(EventFlag_176) && !Savegame_EventFlagGet(EventFlag_M2S01_PickupFlauros))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObject_Item.object_0, &g_WorldObject_Item.pose_1C.position_0, &(SVECTOR3){});
            }
            if (!Savegame_EventFlagGet(EventFlag_M2S01_PickupDrawbridgeKey))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObject_Key.object_0, &g_WorldObject_Key.pose_1C.position_0, &g_WorldObject_Key.pose_1C.rotation_C);
                temp_s0->mapMarkingFlags_1D4[1] &= ~(1<<31);
            }
            else
            {
                temp_s0->mapMarkingFlags_1D4[1] |= (1<<31);
            }
            g_WorldGfx_ObjectAdd(&g_WorldObject_SavePad.object_0, &g_WorldObject_SavePad.pose_1C.position_0, &g_WorldObject_SavePad.pose_1C.rotation_C);
    }

    if (D_800D177C == 0)
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S01_PickupDrawbridgeKey))
        {
            if (PLAYER_NEAR_POS(vx, 20.0f, 0.7f) && PLAYER_NEAR_POS(vz, 23.9f, 0.5f))
            {
                    Camera_PositionSet(NULL, Q12(19.57f), Q12(-2.91f), Q12(23.91f), 0, 0, 0, 0, true);
                    Camera_LookAtSet(NULL, Q12(20.69f), Q12(0.92f), Q12(24.22f), 0, 0, 0, 0, true);
                    D_800D177C = 1;
            }
        }
    }
    else
    {
        // NOTE: This macro uses > comparison, but this part of the code is apparently suing >=
        // which would require a separate macro or slightly larger number to compensate.
        if (!(PLAYER_NEAR_POS(vx, 20.0f, 1.2004f) && PLAYER_NEAR_POS(vz, 23.9f, 1.0004f)))
        {
            vcReturnPreAutoCamWork(true);
            D_800D177C = 0;
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S01_HealthDrink))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &D_800D0528.position_0, &D_800D0528.rotation_C);
        }
    }
}

