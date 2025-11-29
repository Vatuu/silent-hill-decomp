#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map4/map4_s05.h"

INCLUDE_RODATA("asm/maps/map4_s05/nonmatchings/map4_s05", D_800C9578);

INCLUDE_RODATA("asm/maps/map4_s05/nonmatchings/map4_s05", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB0A4_4_s03.h" // 0x800CACA4

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800CADB0);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800CBA54);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800CBC04);

#include "maps/shared/sharedFunc_800CE5D4_1_s03.h" // 0x800CC300

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800CC3B4);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CCA7C

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CCE70

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CCF48

#include "maps/shared/Particle_Update.h" // 0x800CD264

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", sharedFunc_800CEFF4_0_s00); // 0x800CD88C

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CDF7C

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CE018

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CE2FC

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", sharedFunc_800D0690_1_s03); // 0x800CE3BC

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CE508

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CE510

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CE5C8

#include "maps/shared/Player.h"

void Ai_Floatstinger_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D16FC
{
    D_800DB928 = coords;

    if (chara->model_0.state_2 == 0)
    {
        Ai_Floatstinger_Init(chara);
    }

    if (g_DeltaTime0 != Q12(0.0))
    {
        func_800D1968(chara);
        func_800D1B98(chara);
        func_800D35F0(chara);
    }

    func_800D37E8(chara, anmHdr);
    func_800D3AD4(chara);

    chara->properties_E4.larvalStalker.properties_E8[1].val16[0] = chara->rotation_24.vy;
}

void Ai_Floatstinger_Init(s_SubCharacter* chara) // 0x800D1790
{
    s32 i;

    chara->properties_E4.larvalStalker.properties_E8[0].val16[0] = 0;

    chara->model_0.anim_4.alpha_A = Q12(0.0f);

    // Set health.
    chara->health_B0 = Q12(4000.0f);
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        chara->health_B0 = Q12(6000.0f);
    }
    else
    {
        
    }

    chara->moveSpeed_38 = Q12(0.0f);
    chara->field_34     = 0;
    chara->field_E1_0   = 4;

    for (i = 0; i < 16; i++)
    {
        chara->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    switch (chara->model_0.stateStep_3)
    {
        case 3:
            chara->model_0.state_2 = 5;
            Character_AnimSet(chara, ANIM_STATUS(FloatstingerAnim_Unk9, true), 191);

            chara->properties_E4.larvalStalker.properties_E8[7].val16[1] = -0x90; // Could be `FP_ANGLE(-12.7f)`?
            break;

        case 4:
            chara->position_18.vx = Q12(-114.5f);
            chara->position_18.vy = Q12(2.0f);
            chara->position_18.vz = Q12(108.0f);

            chara->model_0.state_2 = 2;
            Character_AnimSet(chara, ANIM_STATUS(FloatstingerAnim_Unk9, true), 191);
            chara->rotation_24.vy = FP_ANGLE(-90.0f);
            break;
    }

    chara->model_0.stateStep_3 = 0;

    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, FLOATSTINGER_ANIM_INFOS);

    chara->dmg_B4.damageReceived_C = Q12(0.0f);
    chara->dmg_B4.field_8          = 0;
    chara->dmg_B4.field_4          = 0;
    chara->dmg_B4.field_0          = 0;

    D_800DB89C = 0;
    D_800DB898 = 0;

    chara->headingAngle_3C = chara->rotation_24.vy;

    for (i = 0; i < 15; i++)
    {
        D_800DB8A8[i] = 0;
    }

    chara->properties_E4.larvalStalker.properties_E8[1].val16[0] = chara->rotation_24.vy;
    chara->flags_3E |= CharaFlag_Unk9 | CharaFlag_Unk3;

    D_800D7858 = 0;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        D_800D785C = Q12(2.4f);
        chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 0;
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        D_800D785C = Q12(4.0f);
    }
    else
    {
        D_800D785C = Q12(3.2f);
    }
}

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D1968);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D1B98);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D1BF8);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D2B90);

void func_800D341C(void) {}

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D3424);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D3564);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D35F0);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D37E8);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D3AD4);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D3F84);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D41F0);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D4458);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D48A4);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D4A3C);

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D5AFC

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D5B0C);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D5D08);

void func_800D5FDC(void) {}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D5FE4

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D607C

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D6110

void func_800D61A4(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.0)\tWhat? ~E ",
    "~J0(2.5)\tThat_light!? ~E ",
    "\tThe_stairs_are_wrecked! ~E ",
    "~C3\tAlchemilla_Hospital ~E "
};

INCLUDE_RODATA("asm/maps/map4_s05/nonmatchings/map4_s05", D_800CABE4);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D61AC);

void func_800D6800(void) // 0x800D6800
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
            g_SysWork.field_30 = 20;

            MAP_POINTS[14].positionX_0 = g_SysWork.player_4C.chara_0.position_18.vx;
            MAP_POINTS[14].positionZ_8 = g_SysWork.player_4C.chara_0.position_18.vz;
            // TODO: Likely wrong union field.
            MAP_POINTS[14].data.spawnInfo.flags_6 = ((u32)func_8005BF38(g_SysWork.player_4C.chara_0.rotation_24.vy) + Q12(1.0f)) >> 4;

            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 52, false);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-118.22f), Q12(1.46f), Q12(105.67f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-119.97f), Q12(-1.4f), Q12(107.85f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_8005E70C();

            D_800D7D80 = Q12(0.0f);
            D_800D7D82 = 0;

            SysWork_StateStepIncrement(0);

        case 3:
            func_80085EB8(2, &g_SysWork.player_4C.chara_0, 0, false);
            SysWork_StateStepIncrementDelayed(Q12(3.5f), false);

            // Warp player.
            g_SysWork.player_4C.chara_0.position_18.vx = Q12(-120.0f);
            g_SysWork.player_4C.chara_0.position_18.vy = Q12(2.0f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(104.0f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = 0;

            // Warp NPC.
            g_SysWork.npcs_1A0[0].position_18.vx = Q12(-120.0f);
            g_SysWork.npcs_1A0[0].position_18.vy = Q12(2.0f);
            g_SysWork.npcs_1A0[0].position_18.vz = Q12(108.0f);
            g_SysWork.npcs_1A0[0].rotation_24.vy = FP_ANGLE(180.0f);
            break;

        case 4:
            Savegame_EventFlagSet(EventFlag_351);
            SysWork_StateStepIncrementAfterFade(0, true, 1, Q12(0.2f), false);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 6:
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        default:
            func_80085EB8(3, &g_SysWork.player_4C.chara_0, 0, false);

            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_352);
            break;
    }

    if (D_800D7D80 == 0)
    {
        Sd_EngineCmd(Sfx_Unk1522);
        D_800D7D82++;
    }

    D_800D7D80 = MIN(D_800D7D80 + ((g_DeltaTime0 * 2) / 3), Q12(1.0f));
    func_800463C0(Sfx_Unk1522, 0, -(D_800D7D80 >> 4) & 0xFF, 0);

    if (D_800D7D80 == Q12(1.0f) && D_800D7D82 >= 0 && D_800D7D82 < 3)
    {
        D_800D7D80 = 0;
    }
}

// TODO: Move to funcs once `func_800D7360` is decomped.
INCLUDE_RODATA("asm/maps/map4_s05/nonmatchings/map4_s05", D_800CAC40);
INCLUDE_RODATA("asm/maps/map4_s05/nonmatchings/map4_s05", D_800CAC48);

extern SVECTOR3 D_800CAC40; // { 0, 0, 0 }
extern VECTOR3  D_800CAC48; // { 154.31f, -15.5f, 24.07f }

void func_800D6BC0(void) // 0x800D6BC0
{
    s32    pitch;
    s32    tmp0;
    s32    tmp1;
    q19_12 cos0;
    q19_12 sin0;

    tmp0  = D_800D7D6C;
    tmp1  = tmp0 >> 1;
    sin0  = Math_Sin(tmp1);
    cos0  = Math_Cos(tmp0 >> 4);
    pitch = ((sin0 * 2) + cos0 + Math_Cos(Math_Cos(tmp1))) >> 9;

    D_800D7D6C += g_DeltaTime0;

    if (g_SysWork.sysStateStep_C[0] >= 10)
    {
        D_800D7D70 -= FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.5f), Q12_SHIFT);
        if (D_800D7D70 < 0)
        {
            D_800D7D70 = 0;
        }

        func_800463C0(Sfx_Unk1467, 0, ~(D_800D7D70 >> 4), pitch);
    }
    else if (g_SysWork.sysStateStep_C[0] > 0)
    {
        D_800D7D70 += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.25f), Q12_SHIFT);
        if (D_800D7D70 > Q12(0.9961f))
        {
            D_800D7D70 = Q12(0.9961f);
        }

        func_800463C0(Sfx_Unk1467, 0, ~(D_800D7D70 >> 4), pitch);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            D_800D7D94 = 0;

            Fs_QueueStartReadTim(FILE_TIM_ENBAN_TIM, FS_BUFFER_1, &D_800D7D64);
            Fs_QueueStartRead(FILE_ANIM_UFO2_DMS, FS_BUFFER_19);

            D_800DB954 = NO_VALUE;
            ScreenFade_ResetTimestep();

            Sd_EngineCmd(Sfx_Unk1467);
            func_800463C0(Sfx_Unk1467, 0, Q8_CLAMPED(1.0f), 0);

            D_800D7D70 = 0;
            D_800D7D6C = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            if (Fs_QueueDoThingWhenEmpty())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 3:
            D_800DB954 = 0;

            SysWork_StateStepIncrementAfterFade(0, true, 3, 0, false);
            DmsHeader_FixOffsets(FS_BUFFER_19);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            Game_TurnFlashlightOn();

            D_800D7D88.vx = Q12(155.0f);
            D_800D7D88.vy = Q12(-16.0f);
            D_800D7D88.vz = Q12(28.0f);
            D_800D7D95    = 0;

            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 5:
            Map_MessageWithAudio(15, &D_800D7D94, &D_800D7D74);
            break;

        case 6:
            SysWork_StateStepIncrementAfterTime(&D_800DB954, Q12(40.0f), Q12(0.0f), Q12(30.0f), true, true);
            sharedFunc_800CE5D4_1_s03(&D_800D7D88, Q12(0.6f), Q12(0.15f), 0);
            break;

        case 7:
            MapMsg_DisplayAndHandleSelection(false, 16, 0, 0, 0, false);
            sharedFunc_800CE5D4_1_s03(&D_800D7D88, Q12(0.6f), Q12(0.15f), 0);
            break;

        case 8:
            func_80080B58(&g_SysWork.playerBoneCoords_890[2], &D_800CAC40, &D_800CAC48);
            sharedFunc_800CE5D4_1_s03(&D_800D7D88, Q12(1.0f), Q12(0.2f), 1);
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 9:
            sharedFunc_800CE5D4_1_s03(&D_800D7D88, Q12(0.6f), Q12(0.15f), 0);

            g_SysWork.field_28 += g_DeltaTime0;
            if (g_SysWork.field_28 > Q12(1.5f))
            {
                if (D_800D7D95 != 0)
                {
                    D_800D7D88.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(3.5f), Q12_SHIFT);
                    if (D_800D7D88.vy < Q12(-17.5f))
                    {
                        D_800D7D95 = 0;
                    }
                }
                else
                {
                    D_800D7D88.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(3.5f), Q12_SHIFT);
                    if (D_800D7D88.vy > Q12(-14.5f))
                    {
                        D_800D7D95 = 1;
                    }
                }
            }

            if (g_SysWork.field_28 > Q12(0.5f))
            {
                D_800D7D88.vx -= FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(2.5f), Q12_SHIFT);
            }

            if (g_SysWork.field_28 > Q12(6.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            vcReturnPreAutoCamWork(true);

            Savegame_EventFlagSet(EventFlag_457);
            func_80086470(3, InventoryItemId_ChannelingStone, 1, false);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();

            D_800DB954 = NO_VALUE;

            break;
    }

    if (D_800DB954 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, "HERO", D_800DB954, FS_BUFFER_19);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800DB938, &D_800DB948, NULL, D_800DB954, FS_BUFFER_19));
        vcUserCamTarget(&D_800DB938, NULL, true);
        vcUserWatchTarget(&D_800DB948, NULL, true);
    }
}

void Map_WorldObjectsInit(void) // 0x800D723C
{
    D_800DB9B0 = 0;

    WorldObjectNoRotInit(&g_WorldObject_Kidn04, "KIDN04_H", -119.8019f, 5.0f, 107.861f);

    WorldObjectNoRotInit(&g_WorldObject_Kidn05, "KIDN05_H", -114.89f, 5.0f, 108.36f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        D_800C4418.field_0 = Q12(5.5f);
    }
    else
    {
        D_800C4418.field_0 = Q12(3.75f);
    }

    D_800C4418.field_2 = Q12(0.2f);
    D_800C4418.field_4 = Q12(0.1f);
    D_800C4418.field_6 = Q12(0.45f);
    D_800C4418.field_8 = Q12(6.0f);
    D_800C4418.field_A = Q12(0.55f);
    D_800C4418.field_C = 18;

    if (Savegame_EventFlagGet(EventFlag_349) && !Savegame_EventFlagGet(EventFlag_350))
    {
        func_80088FF4(Chara_Floatstinger, 0, 4);
    }
}

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D7360);
