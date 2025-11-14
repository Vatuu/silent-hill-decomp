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

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CE688

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CE830

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CE8E8

#include "maps/shared/sharedFunc_800D0CB8_0_s00.h" // 0x800CEA88

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CEBD4

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CEBF4

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CF46C

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CF858

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800D041C

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800D0860

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800D089C

#include "maps/shared/Player_ControlFreeze.h" // 0x800D08A8

#include "maps/shared/Player_ControlUnfreeze.h" // 0x800D0A08

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D0BE0);

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D1470

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D1520

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D1538

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D1560

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D1578

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800D15A0

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D1644

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D1654

void func_800D1660(void) {}

void func_800D1668(void) {}

void func_800D1670(void) {}

void func_800D1678(void) {}

void func_800D1680(void) {}

s32 func_800D1688(void) // 0x800D1688
{
    return 0;
}

void func_800D1690(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D1698

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D16A8

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D16E8

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

    chara->damageReceived_C0 = Q12(0.0f);
    chara->field_BC          = 0;
    chara->field_B8          = 0;
    chara->field_B4          = 0;

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

INCLUDE_RODATA("asm/maps/map4_s05/nonmatchings/map4_s05", D_800CAC40);

INCLUDE_RODATA("asm/maps/map4_s05/nonmatchings/map4_s05", D_800CAC48);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D6BC0);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D723C);

INCLUDE_ASM("asm/maps/map4_s05/nonmatchings/map4_s05", func_800D7360);

INCLUDE_RODATA("asm/maps/map4_s05/nonmatchings/map4_s05", D_800CAC98);
