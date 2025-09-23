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
void Ai_Cheryl_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D7FB8
{
    if (chara->model_0.charaId_0 != Chara_Cheryl)
    {
        Ai_Cheryl_Init(chara);
    }

    func_800D8310(chara, coords);       // Control.
    func_800D8124(chara, coords);       // Translate + rotate.
    func_800D802C(chara, anmHdr, coords); // Modulate speed and something else?
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
    "\tWhere's_Cheryl? ~N\n\tHope_she's_safe. ~E "
};

void func_800D9610(void)
{
    VECTOR3 vec0;
    VECTOR3 vec1;

    // @hack alp0, alp1, ep and do {} while (0); are a permuter find.
    s_AreaLoadParams* alp0;
    s_AreaLoadParams* alp1;
    s_EventParam *ep;

    do {} while (0);
    ep = g_MapEventParam;
    alp0 = &g_MapAreaLoadParams;
    alp1 = alp0;

    vec1.vx = g_MapAreaLoadParams[ep->field_5].char_x_0;
    vec1.vy = Q12(-1.2f);
    vec1.vz = g_MapAreaLoadParams[ep->field_5].char_z_8;
    vec0 = vec1;

    switch (g_SysWork.sysStateStep_C[0]) {
    case 0:
        sharedFunc_800D20E4_0_s00(alp1, ep);
        func_8005DC1C(0x54B, &vec0, 0x80, 0);
        SysWork_StateStepIncrement();
        /* fallthrough */
    case 1:
        func_80085E6C(Q12(0.0999f), false);
        return;
    default:
        sharedFunc_800D2244_0_s00(0);
        SysWork_StateSetNext(SysState_Gameplay);
    }
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D9748);

void func_800D9D98(void)
{
    s_SysWork* syswork;

    func_800DA454();
    syswork = &g_SysWork;
    switch (g_SysWork.sysStateStep_C[0]) {
    case 0:
        sharedFunc_800D20E4_0_s00(syswork);
        func_8008616C(0, true, 2, 0, false);
        SysWork_StateStepIncrement();
        /* fallthrough */
    case 1:
        func_80085E6C(Q12(3.0f), false);
        return;
    case 2:
        func_80085DF0(syswork);
        return;
    case 3:
        func_800865FC(0, 0, 0, Q12(0.5f), 0, 0);
        SysWork_StateStepIncrement();
        /* fallthrough */
    case 4:
        func_800866D4(0x35, 1, 0);
        return;
    case 5:
        MapMsg_DisplayAndHandleSelection(false, 0x14, 0, 0, 0, false);
        return;
    case 6:
        func_800865FC(1, 0, 0, 0x800, -0xB000, 0x8D000);
        func_800865FC(1, 0, 1, 0x800, -0xB800, 0x89000);
        func_800865FC(1, 0, 2, 0x800, -0x9000, 0x85000);
        func_800865FC(1, 0, 3, -0x600, -0xA800, 0x82000);
        func_800865FC(1, 0, 4, -0x400, -0xE000, 0x81000);
        func_800865FC(1, 0, 5, -0x400, -0x12000, 0x81800);
        SysWork_StateStepIncrement();
        /* fallthrough */
    case 7:
        func_800866D4(0x36, 6, 0);
        return;
    default:
        SysWork_StateSetNext(SysState_Gameplay);
        return;
    }
}

void func_800DA028(void)
{
    s_SysWork* syswork;

    func_800DA454();
    syswork = &g_SysWork;

    switch (g_SysWork.sysStateStep_C[0]) {
    case 0:
        sharedFunc_800D20E4_0_s00(syswork);
        func_8008616C(0, true, 2, 0, false);
        SysWork_StateStepIncrement();

        /* fallthrough */
    case 1:
        func_80085E6C(0x3000, false);
        return;
    case 2:
        func_80085DF0(syswork);
        return;
    case 3:
        func_800865FC(0, 0, 0, -0x600, 0, 0);
        SysWork_StateStepIncrement();

        /* fallthrough */
    case 4:
        func_800866D4(0x35, 1, 0);
        return;
    case 5:
        MapMsg_DisplayAndHandleSelection(false, 0x14, 0, 0, 0, false);
        return;
    case 6:
        func_800865FC(1, 0, 0, 0x800, -0x6000, 0x87000);
        func_800865FC(1, 0, 1, -0x400, -0x7000, 0x83000);
        func_800865FC(1, 0, 2, -0x400, -0xB000, 0x80000);
        func_800865FC(1, 0, 3, -0x400, -0x11800, 0x81800);
        SysWork_StateStepIncrement();

        /* fallthrough */
    case 7:
        func_800866D4(0x36, 4, 0);
        return;
    default:
        SysWork_StateSetNext(SysState_Gameplay);
    }
}

void func_800DA254(void)
{
    s_SysWork* syswork;

    func_800DA454();
    syswork = &g_SysWork;

    switch (g_SysWork.sysStateStep_C[0]) {
    case 0:
        sharedFunc_800D20E4_0_s00(syswork);
        func_8008616C(0, true, 2, 0, false);
        SysWork_StateStepIncrement();

        /* fallthrough */
    case 1:
        func_80085E6C(0x3000, false);
        return;
    case 2:
        func_80085DF0(syswork);
        return;
    case 3:
        func_800865FC(0, 0, 0, -0x500, 0, 0);
        SysWork_StateStepIncrement();

        /* fallthrough */
    case 4:
        func_800866D4(0x35, 1, 0);
        return;
    case 5:
        MapMsg_DisplayAndHandleSelection(false, 0x14, 0, 0, 0, false);
        return;
    case 6:
        func_800865FC(1, 0, 0, -0x600, 0x5000, 0x81000);
        func_800865FC(1, 0, 1, -0x400, -0x6000, 0x80000);
        func_800865FC(1, 0, 2, -0x400, -0x11800, 0x81800);
        SysWork_StateStepIncrement();

        /* fallthrough */
    case 7:
        func_800866D4(0x36, 3, 0);
        return;
    default:
        SysWork_StateSetNext(SysState_Gameplay);
    }
}

void func_800DA454(void)
{
    VECTOR3 vec0;
    s16 temp_v0_3;
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 var_a3;

    temp_v0 = (Q12(-29.5f) - g_SysWork.player_4C.chara_0.position_18.vx) >> 6;
    temp_v0_2 = (Q12(128.7f) - g_SysWork.player_4C.chara_0.position_18.vz) >> 6;
    if ((SquareRoot0(SQUARE(temp_v0) + SQUARE(temp_v0_2)) << 6) >= Q12(16.0f))
    {
        D_800DFAB8 += g_DeltaTime0;
        if (D_800DFAB8 > Q12(0.8f))
        {
            temp_v0_3 = ratan2(Q12(-29.5f) - g_SysWork.player_4C.chara_0.position_18.vx, Q12(128.7f) - g_SysWork.player_4C.chara_0.position_18.vz);
            temp_v0_4 = Math_Sin(temp_v0_3);
            vec0.vy = 0;
            vec0.vx = g_SysWork.player_4C.chara_0.position_18.vx + (temp_v0_4 * 0x10);
            vec0.vz = g_SysWork.player_4C.chara_0.position_18.vz + (Math_Cos((s32) temp_v0_3) * 0x10);
            temp_s0 = (Rng_Rand16() & 0x1F) + 0x4B;
            temp_v0_5 = Rng_Rand16();
            var_a3 = temp_v0_5;
            if (temp_v0_5 < 0)
            {
                var_a3 = temp_v0_5 + 0x1F;
            }
            func_8005DD44(0x549, &vec0, temp_s0, (s8) ((temp_v0_5 - ((var_a3 >> 5) << 5)) - 0x10));
            D_800DFAB8 = 0;
        }
    }
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DA5A0);

void func_800DAA68(void)
{
    switch (g_SysWork.sysStateStep_C[0])
    {
    case 0:
        sharedFunc_800D20E4_0_s00();
        func_800865FC(0, 0, 0, Q12(0.5f), 0, Q12(-1.0f));
        SysWork_StateStepIncrement();

        /* fallthrough */
    case 1:
        func_80085E6C(Q12(0.3f), false);
        return;
    case 2:
        func_80085DF0();
        return;
    case 3:
        MapMsg_DisplayAndHandleSelection(false, 0x18, 0, 0, 0, false);
        return;
    case 4:
        func_800866D4(0x36, 1, 0);
        return;
    default:
        sharedFunc_800D2244_0_s00(0);
        SysWork_StateSetNext(SysState_Gameplay);
    }
}

void func_800DAB8C(void)
{
    switch (g_SysWork.sysStateStep_C[0])
    {
    case 0:
        sharedFunc_800D20E4_0_s00();
        func_800865FC(0, 0, 0, Q12(0.25f), Q12(1.0f), 0);
        SysWork_StateStepIncrement();
        /* fallthrough */
    case 1:
        func_80085E6C(0x4CC, false);
        return;
    case 2:
        func_80085DF0();
        return;
    case 3:
        MapMsg_DisplayAndHandleSelection(false, 0x18, 0, 0, 0, false);
        return;
    case 4:
        func_800866D4(0x36, 1, 0);
        return;
    default:
        sharedFunc_800D2244_0_s00(0);
        SysWork_StateSetNext(SysState_Gameplay);
    }
}

void func_800DACB0(void)
{
    switch (g_SysWork.sysStateStep_C[0])
    {
    case 0:
        sharedFunc_800D20E4_0_s00();
        func_800865FC(0, 0, 0, Q12(-0.25f), Q12(-1.0f), 0);
        SysWork_StateStepIncrement();

        /* fallthrough */
    case 1:
        func_80085E6C(0x4CC, false);
        return;
    case 2:
        func_80085DF0();
        return;
    case 3:
        MapMsg_DisplayAndHandleSelection(false, 0x18, 0, 0, 0, false);
        return;
    case 4:
        func_800866D4(0x36, 1, 0);
        return;
    default:
        sharedFunc_800D2244_0_s00(0);
        SysWork_StateSetNext(SysState_Gameplay);
    }
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DADD4);
/* TODO: linker can't find Event_ItemTake
void func_800DADD4(void)
{
    Event_ItemTake(InventoryItemId_Camera, 1, 0x207, 0x37);
}
*/

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

void Map_WorldObjectsInit(void) // 0x800DBE68
{
    s32 rotXY;
    WorldObject_ModelNameSet(&D_800E3A5C[0], "WHEEL1_H");
    WorldObject_ModelNameSet(&D_800E3A5C[1], "WHEEL2_H");
    D_800E3A9C.vx = Q12(-268.32f);
    D_800E3A9C.vy = Q12(-0.44f);
    D_800E3A9C.vz = Q12(245.72f);
    rotXY = 0xFAE4FE17; // @hack vx and vy combined into a single 32bit word.
    D_800E3AAC.vz = 0;

    g_SavegamePtr->eventFlags_168[5] &= 0xEFFFFFFF;
    *(s32*)&D_800E3AAC.vx = rotXY;
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DBF08);

void func_800DC1E8(void)
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if ((g_SavegamePtr->eventFlags_168[0] & 0x20000) && (g_SysWork.npcs_1A0[0].model_0.charaId_0 == 0))
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, -7, -1, -7) && PLAYER_IN_MAP_CHUNK(vz, 1, 7, -1, 7)) {
            Chara_Spawn(8, 0, Q12(-252.0f), Q12(223.0f), Q12(0.5f),   5);
            Chara_Spawn(8, 1, Q12(-254.0f), Q12(221.0f), Q12(0.375f), 5);
            Chara_Spawn(8, 2, Q12(-259.0f), Q12(232.0f), Q12(0.0f),   5);
        }
    }
}

void func_800DC33C(void) // 0x800DC33C
{
    VECTOR3     camPos;
    s16         temp_a0;
    s16         var_s1;
    s32         var_v1;
    q19_12      temp_a0_2;
    s32         temp_v1;
    s32         var_a0;
    s32         var_a2;
    s32         var_v1_2;
    s_Savegame* save;

    save = g_SavegamePtr;

    // TODO: Use `Savegame_EventFlagGet`.

    if (!(save->eventFlags_168[0] & 0x20))
    {
        func_800865FC(1, 1, 0, 0x800, -0x3E000, 0x6C000);
        sharedFunc_800D88AC_0_s00(g_SysWork.npcs_1A0);
        save->eventFlags_168[0] |= 0x20;
    }

    vwGetViewPosition(&camPos);
    if (Math_Vector2MagCalc(g_SysWork.npcs_1A0[0].position_18.vx - camPos.vx,
                            g_SysWork.npcs_1A0[0].position_18.vz - camPos.vz) <= Q12(16.5f) &&
        g_SysWork.npcs_1A0[0].position_18.vx >= Q12(-58.0f))
    {
        if (!(g_SysWork.flags_22A4 & 0x80))
        {
            if (!Vw_AabbVisibleInScreenCheck(g_SysWork.npcs_1A0[0].position_18.vx - Q12(1.0f),
                                             g_SysWork.npcs_1A0[0].position_18.vx + Q12(1.0f),
                                             g_SysWork.npcs_1A0[0].position_18.vy - Q12(1.5f),
                                             g_SysWork.npcs_1A0[0].position_18.vy,
                                             g_SysWork.npcs_1A0[0].position_18.vz - Q12(1.0f),
                                             g_SysWork.npcs_1A0[0].position_18.vz + Q12(1.0f)))
            {
block7:
                g_SysWork.npcs_1A0[0].position_18.vz = 1;
                g_SysWork.npcs_1A0[0].position_18.vx = 1;
                g_SysWork.npcs_1A0[0].properties_E4.player.headingAngle_124 = FP_ANGLE(0.0f);

                sharedFunc_800D88C0_0_s00(g_SysWork.npcs_1A0, 0);

                g_SavegamePtr->eventFlags_168[0] |= 0x40;
                return;
            }
        }

        var_s1 = func_8005BF38(ratan2(g_SysWork.npcs_1A0[0].position_18.vx - g_SysWork.player_4C.chara_0.position_18.vx,
                                      g_SysWork.npcs_1A0[0].position_18.vz - g_SysWork.player_4C.chara_0.position_18.vz) -
                               g_SysWork.player_4C.chara_0.headingAngle_3C);

        temp_a0 = func_8005BF38(ratan2(Q12(-62.0f) - g_SysWork.player_4C.chara_0.position_18.vx,
                                       Q12(106.0f) - g_SysWork.player_4C.chara_0.position_18.vz) -
                                g_SysWork.player_4C.chara_0.headingAngle_3C);

        if (ABS(var_s1) > ABS(temp_a0))
        {
            var_s1 = temp_a0;
        }
        var_a0 = var_s1 << 16;

        // TODO: Why shift 16?
        temp_a0_2 = (g_SysWork.player_4C.chara_0.moveSpeed_38 * Math_Cos(var_a0 >> 16) * 16) >> 16;
        if (temp_a0_2 > Q12(1.8f))
        {
            D_800DFAD0 = temp_a0_2 + Q12(0.9f);
        } 
        else if (D_800DFAD0 > Q12(1.8f))
        {
            var_a2 = Q12(1.8f);
            temp_v1 = D_800DFAD0 - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.5f, Q12_SHIFT);
            if (temp_v1 >= Q12(1.8f))
            {
                var_a2 = temp_v1;
            }
            D_800DFAD0 = var_a2;
        }
        else
        {
            var_v1_2 = D_800DFAD0 + FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.5f, Q12_SHIFT);
            if (var_v1_2 > Q12(1.8f))
            {
                var_v1_2 = Q12(1.8f);
            }
            D_800DFAD0 = var_v1_2;
        }

        g_SysWork.npcs_1A0[0].properties_E4.player.headingAngle_124 = D_800DFAD0;
        func_8008677C(&g_SysWork.npcs_1A0[0], 2, 1);
        return;
    }

    // TODO: Remove `goto`.
    goto block7;
}

void func_800DC694(void) // 0x800DC694
{
    q19_12 mag;
    s32    temp_a0_2;
    s32    temp_v1;
    s32    var_a2;
    s32    var_v1;

    mag = Math_Vector2MagCalc(g_SysWork.npcs_1A0[0].position_18.vx - g_SysWork.player_4C.chara_0.position_18.vx,
                              (g_SysWork.npcs_1A0[0].position_18.vz - g_SysWork.player_4C.chara_0.position_18.vz) - Q12(2.0f));

    // TODO: Use `Savegame_EventFlagGet`.
    if (!(g_SavegamePtr->eventFlags_168[0] & 0x80))
    {
        sharedFunc_800D88AC_0_s00(g_SysWork.npcs_1A0);
        return;
    }

    if (mag <= Q12(14.5f) && g_SysWork.npcs_1A0[0].position_18.vz >= Q12(49.0f))
    {
        if (!(g_SysWork.flags_22A4 & 0x80))
        {
            if (!Vw_AabbVisibleInScreenCheck(g_SysWork.npcs_1A0[0].position_18.vx - Q12(1.0f),
                                             g_SysWork.npcs_1A0[0].position_18.vx + Q12(1.0f),
                                             g_SysWork.npcs_1A0[0].position_18.vy - Q12(1.5f),
                                             g_SysWork.npcs_1A0[0].position_18.vy,
                                             g_SysWork.npcs_1A0[0].position_18.vz - Q12(1.0f),
                                             g_SysWork.npcs_1A0[0].position_18.vz + Q12(1.0f)))
            {
block7:
                g_SysWork.npcs_1A0[0].position_18.vz = 1;
                g_SysWork.npcs_1A0[0].position_18.vx = 1;

                sharedFunc_800D88C0_0_s00(g_SysWork.npcs_1A0, 0);

                g_SavegamePtr->eventFlags_168[0] |= 0x200;
                return;
            }
        }

        temp_a0_2 = FP_MULTIPLY(g_SysWork.player_4C.chara_0.moveSpeed_38, Math_Cos(g_SysWork.player_4C.chara_0.headingAngle_3C + FP_ANGLE(180.0f)), Q12_SHIFT);
        if (temp_a0_2 > Q12(1.8f))
        {
            D_800DFAD4 = temp_a0_2 + Q12(0.6f);
        }
        else if (D_800DFAD4 > Q12(1.8f))
        {
            var_a2 = Q12(1.8f);
            temp_v1 = D_800DFAD4 - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.5f, Q12_SHIFT);
            if (temp_v1 >= Q12(1.8f))
            {
                var_a2 = temp_v1;
            }
            D_800DFAD4 = var_a2;
        }
        else
        {
            var_v1 = D_800DFAD4 + FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.5f, Q12_SHIFT);
            if (var_v1 > Q12(1.8f))
            {
                var_v1 = Q12(1.8f);
            }
            D_800DFAD4 = var_v1;
        }

        g_SysWork.npcs_1A0[0].properties_E4.player.headingAngle_124 = D_800DFAD4;

        func_8008677C(&g_SysWork.npcs_1A0[0], 2, 1);
        return;
    }

// TODO: Remvoe `goto`.
block_7:
    goto block7;
}

void func_800DC8D8(void) // 0x800DC8D8
{
    q19_12 mag;

    mag = Math_Vector2MagCalc(g_SysWork.npcs_1A0[0].position_18.vx - g_SysWork.player_4C.chara_0.position_18.vx,
                              (g_SysWork.npcs_1A0[0].position_18.vz - g_SysWork.player_4C.chara_0.position_18.vz) - Q12(2.0f));

    // TODO: Use `Savegame_EventFlagGet`.
    if (!(g_SavegamePtr->eventFlags_168[0] & 0x400))
    {
        g_SysWork.npcs_1A0[0].position_18.vx = Q12(-61.0f);
        g_SysWork.npcs_1A0[0].position_18.vz = Q12(48.0f);
        g_SysWork.npcs_1A0[0].rotation_24.vy = FP_ANGLE(90.0f);

        if (mag < Q12(14.8f))
        {
            sharedFunc_800D88AC_0_s00(g_SysWork.npcs_1A0);

            g_SavegamePtr->eventFlags_168[0] |= 0x400;

            func_800865FC(1, 1, 0, 0x400, Q12(-57.0f), Q12(47.0f));
        }
    }
    else
    {
        g_SysWork.npcs_1A0[0].properties_E4.player.headingAngle_124 = Q12(1.8f);

        func_8008677C(&g_SysWork.npcs_1A0[0], 2, 1);

        if (g_SysWork.npcs_1A0[0].position_18.vx > Q12(-58.0f))
        {
            g_SavegamePtr->eventFlags_168[0] |= 0x800;
            g_SysWork.npcs_1A0[0].model_0.charaId_0 = Chara_None;

            func_8005DC1C(Sfx_Unk1354, &D_800CB6A4, 0x80, 0);
        }
    }
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DCA30);

void func_800DCC54(void)
{
    s_Savegame* temp_s0;
    u32 temp_v1;

    if (D_800DFADC == NO_VALUE)
    {
        func_8003EF10(6, 6, 5, (s32) &D_800DFADC, 0, 0x64000);
        D_800DFADC = 0;
        Sd_PlaySfx(0x54FU, 0, 0xE0U);
    }
    temp_s0 = g_SavegamePtr;
    temp_v1 = temp_s0->eventFlags_168[0];
    if (temp_v1 & 0x4000)
    {
        if (!(temp_v1 & 0x40000))
        {
            sharedFunc_800D0B18_0_s00(6);
            temp_s0->eventFlags_168[0] |= 0x40000;
            Sd_PlaySfx(0x54FU, 0, 0xC0U);
            D_800DFADC = 0x3C000;
        }
        D_800DFADC = func_800DCF38(D_800DFADC);
    } 
    else
    {
        D_800DFADC = func_800DCDA8();
    }
    if (D_800DFADC > 0x4FFFF)
    {
        g_SavegamePtr->eventFlags_168[0] |= 0x8000;
    }
    if (D_800DFADC > 0x63FFF)
    {
        g_SavegamePtr->eventFlags_168[0] |= 0x10000;
    }
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DCDA8);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DCF38);

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DD0CC);

INCLUDE_RODATA("asm/maps/map0_s00/nonmatchings/map0_s00", D_800CB6A4);
