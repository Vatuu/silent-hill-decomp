#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map0/map0_s00.h"

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CB6B0);

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CBBBC

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CBC94);

void func_800CBFB0(void) // 0x800CBFB0
{
    VECTOR3 vecs[4] =
    {
        VECTOR3(-258.0f, -1.4f, 244.1f),
        VECTOR3(-254.5f,  0.0f,  220.5f),
        VECTOR3(-249.4f,  0.0f,  219.5f),
        VECTOR3(-250.5f,  0.0f,  217.7f)
    };

    GsInitCoordinate2(NULL, &g_SysWork.coord_22F8);
    D_800DD594 = 1;
    D_800DD593 = 1;
    D_800E34EC = 20;
    D_800E39AC = 60;
    func_800D0394(2, vecs);
}

#include "maps/shared/Particle_Update.h" // 0x800CC04C

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CC6E8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CC8FC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CD1F4);

INCLUDE_RODATA("asm/maps/map0_s00/nonmatchings/map0_s00", D_800CA7CC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CD8E8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CE02C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CE544);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800CEB24_0_s00); // 0x800CEB24

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800CEFF4_0_s00); // 0x800CEFF4

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800CF7AC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800CEFD0_1_s02); // 0x800CF974

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CFFF8

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800D0124

bool func_800D012C(VECTOR3* pos) // 0x800D012C
{
    s32 deltaX;
    s32 deltaZ;

    switch (g_SysWork.field_234B_4)
    {
        case 1:
            return true;

        case 2:
            deltaX = FP_METER_TO_GEO(g_SysWork.player_4C.chara_0.position_18.vx - pos->vx);
            deltaZ = FP_METER_TO_GEO(g_SysWork.player_4C.chara_0.position_18.vz - pos->vz);
            return SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)) < FP_METER_GEO(1.0f);
    }

    return false;
}

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800D01BC

void sharedFunc_800CF9A8_0_s01(s32 arg0, s_Particle* part, u16* arg2) // 0x800D0274
{
    s_Particle* partCpy;

    partCpy = part;

    switch (arg0)
    {
        case 0:
            if (D_800DD592 != 0)
            {
                part->type_1F = ParticleType_Snow;
            }
            else
            {
                part->type_1F = ParticleType_Unk1;
            }

            partCpy->position0_0.vy = sharedData_800E323C_0_s00.vy;
            partCpy->movement_18.vz = FP_METER(0.0f);
            partCpy->movement_18.vx = FP_METER(0.0f);
            partCpy->movement_18.vy = FP_METER(0.0245f);

            sharedFunc_800D01BC_0_s00(arg2, part, 5);
            partCpy->position1_C.vz = FP_METER(0.0f);
            partCpy->position1_C.vy = FP_METER(0.0f);
            partCpy->position1_C.vx = FP_METER(0.0f);
            break;

        case 1:
            partCpy->type_1F = ParticleType_Rain;
            partCpy->position0_0.vy = sharedData_800E323C_0_s00.vy + FP_METER(Rng_GenerateInt(Rng_Rand16(), 0, 2));

            partCpy->position1_C.vy = sharedData_800E323C_0_s00.vy;
            partCpy->movement_18.vy = FP_METER(0.03675f);
            sharedFunc_800D01BC_0_s00(arg2, part, 6);
            partCpy->position1_C.vx = partCpy->position0_0.vx;
            partCpy->position1_C.vz = partCpy->position0_0.vz;
            break;
    }

    partCpy->stateStep_1E++;
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0394);

bool func_800D0600() // 0x800D0600
{
    #define FIXED_DIST FP_METER(40.0f)
    
    s32 distX;
    s32 distZ;

    // Check against first position.
    distX = ABS(g_SysWork.player_4C.chara_0.position_18.vx - D_800E32DC.position0_0.vx);
    distZ = g_SysWork.player_4C.chara_0.position_18.vz - D_800E32DC.position0_0.vz;
    if (distZ >= FP_METER(0.0f) && (distX + distZ) < FIXED_DIST)
    {
        goto ret1;
    }
    else if (distZ < FP_METER(0.0f) && (distX + (D_800E32DC.position0_0.vz - g_SysWork.player_4C.chara_0.position_18.vz)) < FIXED_DIST)
    {
        goto ret1;
    }

    // Check against against second position.
    distX = ABS(g_SysWork.player_4C.chara_0.position_18.vx - D_800E32DC.position1_C.vx);
    distZ = g_SysWork.player_4C.chara_0.position_18.vz - D_800E32DC.position1_C.vz;
    if (distZ >= FP_METER(0.0f) && (distX + distZ) < FIXED_DIST)
    {
        goto ret1;
    }
    else if (distZ < FP_METER(0.0f) && (distX + (D_800E32DC.position1_C.vz - g_SysWork.player_4C.chara_0.position_18.vz)) < FIXED_DIST)
    {
        goto ret1;
    }
    else
    {
        // TODO: Ideally would return `false` here, but code matching requires jump to end.
        goto ret0;
    }
    
ret1:
    return true;
ret0:
    return false;
}

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800D0700

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800D08B8

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800D0A60

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800D0B18

#include "maps/shared/sharedFunc_800D0CB8_0_s00.h" // 0x800D0CB8

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800D0E04

void func_800D0E24() {}

void func_800D0E2C() {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D0E34);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D1C38);

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800D209C

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800D20D8

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800D20E4

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800D2244

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D23EC);

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D2C7C

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D2D2C

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D2D44

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D2D6C

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D2D84

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800D2DAC

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D2E50

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D2E60

void func_800D2E6C() {}

void func_800D2E74() {}

void func_800D2E7C() {}

void func_800D2E84() {}

void func_800D2E8C() {}

s32 func_800D2E94()
{
    return 0;
}

void func_800D2E9C() {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D2EA4

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D2EB4

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D2EF4

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D2F08

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D309C

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800D3308_0_s00); // 0x800D3308

#include "maps/shared/sharedFunc_800D3B44_0_s00.h" // 0x800D3B44

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800D3EF4_0_s00);

void sharedFunc_800D4924_0_s00(s_SubCharacter* chara) {}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800D492C_0_s00);

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D63D0

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800D54A8_0_s00);

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D5B48

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800D5C64_0_s00);

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D5FCC

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D63D0

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D654C

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D6554

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D670C

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D67FC

INCLUDE_RODATA("asm/maps/map0_s00/nonmatchings/map0_s00", sharedData_800CAB70_0_s00);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800D6970_0_s00); // 0x800D6970

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800D70C4_0_s00); // 0x800D70C4

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", sharedFunc_800D7BE8_0_s00); // 0x800D7BE8

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D7E04

// `arg2` = another `s_SubCharacter`?
void Ai_Cheryl_Update(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coords) // 0x800D7FB8
{
    if (chara->model_0.charaId_0 != Chara_Cheryl)
    {
        Ai_Cheryl_Init(chara);
    }

    func_800D8310(chara, coords);       // Control.
    func_800D8124(chara, coords);       // Translate + rotate.
    func_800D802C(chara, anmHeader, coords); // Modulate speed and something else?
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D802C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D8124);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D8310);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D8748);

void Ai_Cheryl_Init(s_SubCharacter* chara) // 0x800D8888
{
    sharedFunc_800D923C_0_s00(chara);
    D_800E3A30 = 0;
}

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D88AC

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D88C0

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D8904

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D891C

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D8928

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D893C

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D8950

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D8964

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800D8A00

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D9064

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D9078

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D908C

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D9188

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D921C

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D923C

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D929C

#include "maps/shared/sharedFunc_800D92AC_0_s00.h" // 0x800D92AC

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D94F8);

/** Debug function? */
void Gfx_LoadingScreen_StageString() // 0x800D95D4
{
    g_Screen_FadeStatus = SCREEN_FADE_STATUS(ScreenFadeState_FadeInSteps, false);
    Gfx_DebugStringPosition(100, 100);
    Gfx_DebugStringDraw("STAGE 0-0");
}

const char* MAP_MESSAGES[] =
{
    #include "maps/shared/mapMsg_common.h"
    "~J0(2.5)\tCheryl.__Where_could_you_be? ~E ",
    "~J0(1.5)\tIt's_strange... ",
    "~J0(2.0)\tIt's_quiet.__Too_quiet. ",
    "~J0(3.0)\tThis_place_is ~N\n\t\t\tlike_a_ghost_town. ~E ",
    "~J0(3.0)\tCheryl. ~E ",
    "~J0(1.5)\tFootsteps? ~E ",
    "~J0(2.8)\tCheryl? ~N\n\t\t\tIs_that_Cheryl!? ~E ",
    "~J0(1.2)\tWhere_are_you_going? ~E ",
    "~J0(1.8)\tHey_wait...stop! ~E ",
    "\tI'd_better_follow_Cheryl... ~E ",
    "\tThat's_strange, ~N\n\tit's_getting_darker. ~E ",
    "\tA_dead_end? ~N\n\tWhat_the_hell!? ~E ",
    "~J0(1.6)\tWhat_is_this? ",
    "~J0(2.5)\tWhat's_going_on_here!? ~E ",
    "\tWhat's_this? ~E ",
    "\t......better_than_nothing, ~N\n\tI_guess. ~E ",
    "\tWhat? ~N\n\tWhat's_this_doing_here? ~E ",
    "\tBlocked_by_a_fence? ~E ",
    "\tA_broken_wheelchair? ~N\n\tWhat's_this_doing_here? ~E ",
    "\tWhat_the..? ~N\n\tWhat_is_it? ~E ",
    "\tThe_street_is_blocked.",
    "\tCan't_get_out_of_town ~N\n\tthrough_here. ~E ",
    "\tMy_car... ~N\n\ttoo_banged_up_to_drive. ",
    "\tWhere's_Cheryl? ~N\n\tHope_she's_safe. ~E ",
};

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D9610);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D9748);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D9D98);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DA028);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DA254);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DA454);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DA5A0);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DAA68);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DAB8C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DACB0);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DADD4);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DAEFC);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DB26C);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DB514);

void func_800DB870() // 0x800DB870
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement();

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 26, 0, 0, 0, false);
            break;

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DB94C);

void func_800DBE00() // 0x800DBE00
{
    func_8004690C(Sfx_Unk1359);
    func_8004690C(Sfx_Unk1361);
    func_8004690C(Sfx_Unk1360);

    Sd_EngineCmd(22);
    func_800892A4(4);

    SysWork_StateSetNext(SysState_Gameplay);
    g_SysWork.player_4C.chara_0.position_18.vy = 0;
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DBE68);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DBF08);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DC1E8);

void func_800DC33C(s32 eventFlags0)
{
    VECTOR3 sp18;
    s16 temp_a0;
    s16 var_s1;
    s32 var_v1;
    s32 temp_a0_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a2;
    s32 var_v1_2;
    s_Savegame* temp_s0;

    temp_s0 = g_SavegamePtr;
    if (!(temp_s0->eventFlags_168[0] & 0x20))
    {
        func_800865FC(1, 1, 0, 0x800, -0x3E000, 0x6C000);
        sharedFunc_800D88AC_0_s00(g_SysWork.npcs_1A0);
        temp_s0->eventFlags_168[0] |= 0x20;
    }

    vwGetViewPosition(&sp18);
    temp_v0 = (g_SysWork.npcs_1A0[0].position_18.vx - sp18.vx) >> 6;
    temp_v0_2 = (g_SysWork.npcs_1A0[0].position_18.vz - sp18.vz) >> 6;

    if (((SquareRoot0((temp_v0 * temp_v0) + (temp_v0_2 * temp_v0_2)) << 6) <= 0x10800) &&
        (g_SysWork.npcs_1A0[0].position_18.vx >= FP_METER(-58.0f)))
    {

        if (!(g_SysWork.flags_22A4 & 0x80))
        {
            if (!Vw_AabbVisibleInScreenCheck(
                    g_SysWork.npcs_1A0[0].position_18.vx - Q12(1.0f),
                    g_SysWork.npcs_1A0[0].position_18.vx + Q12(1.0f),
                    g_SysWork.npcs_1A0[0].position_18.vy - Q12(1.5f),
                    g_SysWork.npcs_1A0[0].position_18.vy,
                    g_SysWork.npcs_1A0[0].position_18.vz - Q12(1.0f),
                    g_SysWork.npcs_1A0[0].position_18.vz + Q12(1.0f)))
            {
block7:
                g_SysWork.npcs_1A0[0].position_18.vz = 1;
                g_SysWork.npcs_1A0[0].position_18.vx = 1;
                g_SysWork.npcs_1A0[0].properties_E4.player.headingAngle_124 = 0;
                sharedFunc_800D88C0_0_s00(g_SysWork.npcs_1A0, 0);
                g_SavegamePtr->eventFlags_168[0] |= 0x40;
                return;
            }
        }

        var_s1 = func_8005BF38(
            (ratan2(g_SysWork.npcs_1A0[0].position_18.vx - g_SysWork.player_4C.chara_0.position_18.vx,
                   g_SysWork.npcs_1A0[0].position_18.vz - g_SysWork.player_4C.chara_0.position_18.vz) - g_SysWork.player_4C.chara_0.headingAngle_3C));

        temp_a0 = func_8005BF38((
            ratan2(FP_METER(-62.0f) - g_SysWork.player_4C.chara_0.position_18.vx,
                   Q12(106.0f) - g_SysWork.player_4C.chara_0.position_18.vz) -
            g_SysWork.player_4C.chara_0.headingAngle_3C));


        if (ABS(var_s1) > ABS(temp_a0))
        {
            var_s1 = temp_a0;
        }
        var_a0 = var_s1 << 16;

        temp_a0_2 = (g_SysWork.player_4C.chara_0.moveSpeed_38 * Math_Cos(var_a0 >> 0x10) * 0x10) >> 0x10;

        if (temp_a0_2 > FP_METER(1.8))
        {
            D_800DFAD0 = temp_a0_2 + Q12(0.9f);
        } 
        else if (D_800DFAD0 > FP_METER(1.8))
        {
            var_a2 = FP_METER(1.8);
            temp_v1 = D_800DFAD0 - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.5f, 12);
            if (temp_v1 >= FP_METER(1.8))
            {
                var_a2 = temp_v1;
            }
            D_800DFAD0 = var_a2;
        }
        else
        {
            var_v1_2 = D_800DFAD0 + FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.5f, 12);

            if (var_v1_2 > FP_METER(1.8))
            {
                var_v1_2 = FP_METER(1.8);
            }
            D_800DFAD0 = var_v1_2;
        }

        g_SysWork.npcs_1A0[0].properties_E4.player.headingAngle_124 = D_800DFAD0;
        func_8008677C(g_SysWork.npcs_1A0, 2, 1);
        return;
    }

    goto block7;
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DC694);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DC8D8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DCA30);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DCC54);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DCDA8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DCF38);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DD0CC);

INCLUDE_RODATA("asm/maps/map0_s00/nonmatchings/map0_s00", D_800CB6A4);
