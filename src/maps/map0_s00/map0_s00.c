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
            deltaX = Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vx - pos->vx);
            deltaZ = Q12_TO_Q8(g_SysWork.player_4C.chara_0.position_18.vz - pos->vz);
            return SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)) < Q8(1.0f);
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
            partCpy->movement_18.vz = Q12(0.0f);
            partCpy->movement_18.vx = Q12(0.0f);
            partCpy->movement_18.vy = Q12(0.0245f);

            sharedFunc_800D01BC_0_s00(arg2, part, 5);
            partCpy->position1_C.vz = Q12(0.0f);
            partCpy->position1_C.vy = Q12(0.0f);
            partCpy->position1_C.vx = Q12(0.0f);
            break;

        case 1:
            partCpy->type_1F = ParticleType_Rain;
            partCpy->position0_0.vy = sharedData_800E323C_0_s00.vy + Q12(Rng_GenerateInt(Rng_Rand16(), 0, 2));

            partCpy->position1_C.vy = sharedData_800E323C_0_s00.vy;
            partCpy->movement_18.vy = Q12(0.03675f);
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
    #define FIXED_DIST Q12(40.0f)
    
    s32 distX;
    s32 distZ;

    // Check against first position.
    distX = ABS(g_SysWork.player_4C.chara_0.position_18.vx - D_800E32DC.position0_0.vx);
    distZ = g_SysWork.player_4C.chara_0.position_18.vz - D_800E32DC.position0_0.vz;
    if (distZ >= Q12(0.0f) && (distX + distZ) < FIXED_DIST)
    {
        goto ret1;
    }
    else if (distZ < Q12(0.0f) && (distX + (D_800E32DC.position0_0.vz - g_SysWork.player_4C.chara_0.position_18.vz)) < FIXED_DIST)
    {
        goto ret1;
    }

    // Check against against second position.
    distX = ABS(g_SysWork.player_4C.chara_0.position_18.vx - D_800E32DC.position1_C.vx);
    distZ = g_SysWork.player_4C.chara_0.position_18.vz - D_800E32DC.position1_C.vz;
    if (distZ >= Q12(0.0f) && (distX + distZ) < FIXED_DIST)
    {
        goto ret1;
    }
    else if (distZ < Q12(0.0f) && (distX + (D_800E32DC.position1_C.vz - g_SysWork.player_4C.chara_0.position_18.vz)) < FIXED_DIST)
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

#include "maps/shared/sharedFunc_800D7BE8_0_s00.h" // 0x800D7BE8

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

void func_800D802C(s_SubCharacter* arg0, s_AnmHeader* arg1, GsCOORDINATE2* arg2)
{
    s32 speed;
    s32 animDur;
    s_AnimInfo* animInfo;

    if (arg0->properties_E4.player.afkTimer_E8 == 1)
    {
        D_800DF1CC = FP_MULTIPLY_PRECISE(arg0->moveSpeed_38, 0x1e333, 12);
    }

    speed = MIN(arg0->moveSpeed_38, Q12(2.5f));
    arg0->moveSpeed_38 = speed;

    if (arg0->properties_E4.player.afkTimer_E8 == 2)
    {
        // @hack KAUFMAN anim in map0_s00 ? this might be a different anim table after all.
        animInfo = KAUFMANN_ANIM_INFOS;
        if (speed <= Q12(1.5f))
        {
            animDur = FP_MULTIPLY_PRECISE(speed, Q12(18.6), 12);
        } else
        {
            animDur = Q12(27.8999f);
        }
        animInfo[7].duration_8.constant = animDur;
    }
    if (!arg0->properties_E4.player.field_F0)
    {
        KAUFMANN_ANIM_INFOS[arg0->model_0.anim_4.status_0].
            updateFunc_0(&arg0->model_0, arg1, arg2, 
                    &KAUFMANN_ANIM_INFOS[arg0->model_0.anim_4.status_0]);
    }
}

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

void func_800D94F8(void) // 0x800D94F8
{
    s32  i;
    s32  flags1;
    s32  flags0;
    u16  saveFlag;
    u32  saveByte;
    u16* var_a2;

    // @hack Not used directly, but gets merged with  `Savegame_EventFlagGet` macros below.
    saveByte = g_SavegamePtr->eventFlags_168[0];
    flags1 = 0x199;
    flags0 = 0x100;

    if (g_SysWork.player_4C.chara_0.health_B0 > 0 && (!(Savegame_EventFlagGet(23) && !Savegame_EventFlagGet(20))))
    {
        for (i = 1; i < 7; i++)
        {
            saveFlag = D_800DF300[i];
            if (Savegame_EventFlagGet((s16)saveFlag))
            {
                flags0 |= 1 << i;
            }
        }
    }
    else
    {     
        Savegame_EventFlagClear(EventFlag_20);
        flags1 = 0x4CC;
    }

    func_80035F4C(flags0, flags1, &D_800DF2F8);
}

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

void func_800D9610(void) // 0x800D9610
{
    VECTOR3       posCpy;
    VECTOR3       pos;
    s_MapPoint2d* areaLoadParams0;
    s_MapPoint2d* areaLoadParams1;
    s_EventParam* eventParam;

    // @hack Permuter finds.
    do {} while (false);
    eventParam = g_MapEventParam;
    areaLoadParams0 = &g_MapAreaLoadParams;
    areaLoadParams1 = areaLoadParams0;

    pos.vx = g_MapAreaLoadParams[eventParam->field_5].positionX_0;
    pos.vy = Q12(-1.2f);
    pos.vz = g_MapAreaLoadParams[eventParam->field_5].positionZ_8;
    posCpy = pos;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00(areaLoadParams1, eventParam);
            func_8005DC1C(Sfx_Unk1355, &posCpy, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement();

        case 1:
            func_80085E6C(Q12(0.1f), false);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
    }
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800D9748);

void func_800D9D98(void) // 0x800D9D98
{
    s_SysWork* syswork;

    func_800DA454();

    syswork = &g_SysWork;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00(syswork);
            func_8008616C(0, true, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement();

        case 1:
            func_80085E6C(Q12(3.0f), false);
            break;

        case 2:
            func_80085DF0(syswork);
            break;

        case 3:
            func_800865FC(false, 0, 0, FP_ANGLE(180.0f), Q12(0.0f), Q12(0.0f));
            SysWork_StateStepIncrement();
            
        case 4:
            func_800866D4(53, 1, 0);
            break;

        case 5:
            MapMsg_DisplayAndHandleSelection(false, 20, 0, 0, 0, false);
            break;

        case 6:
            func_800865FC(true, 0, 0, FP_ANGLE(180.0f),  Q12(-11.0f), Q12(141.0f));
            func_800865FC(true, 0, 1, FP_ANGLE(180.0f),  Q12(-11.5f), Q12(137.0f));
            func_800865FC(true, 0, 2, FP_ANGLE(180.0f),  Q12(-9.0f),  Q12(133.0f));
            func_800865FC(true, 0, 3, FP_ANGLE(-135.0f), Q12(-10.5f), Q12(130.0f));
            func_800865FC(true, 0, 4, FP_ANGLE(-90.0f),  Q12(-14.0f), Q12(129.0f));
            func_800865FC(true, 0, 5, FP_ANGLE(-90.0f),  Q12(-18.0f), Q12(129.5f));
            SysWork_StateStepIncrement();

        case 7:
            func_800866D4(54, 6, 0);
            break;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800DA028(void) // 0x800DA028
{
    s_SysWork* syswork;

    func_800DA454();

    syswork = &g_SysWork;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00(syswork);
            func_8008616C(0, true, 2, 0, false);
            SysWork_StateStepIncrement();

        case 1:
            func_80085E6C(0x3000, false);
            break;

        case 2:
            func_80085DF0(syswork);
            break;

        case 3:
            func_800865FC(false, 0, 0, FP_ANGLE(-135.0f), Q12(0.0f), Q12(0.0f));
            SysWork_StateStepIncrement();

        case 4:
            func_800866D4(53, 1, 0);
            break;

        case 5:
            MapMsg_DisplayAndHandleSelection(false, 20, 0, 0, 0, false);
            break;

        case 6:
            func_800865FC(true, 0, 0, FP_ANGLE(180.0f), Q12(-6.0f),  Q12(135.0f));
            func_800865FC(true, 0, 1, FP_ANGLE(-90.0f), Q12(-7.0f),  Q12(131.0f));
            func_800865FC(true, 0, 2, FP_ANGLE(-90.0f), Q12(-11.0f), Q12(128.0f));
            func_800865FC(true, 0, 3, FP_ANGLE(-90.0f), Q12(-17.5f), Q12(129.5f));
            SysWork_StateStepIncrement();

        case 7:
            func_800866D4(54, 4, 0);
            break;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
    }
}

void func_800DA254(void) // 0x800DA254
{
    s_SysWork* syswork;

    func_800DA454();

    syswork = &g_SysWork;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00(syswork);
            func_8008616C(0, true, 2, 0, false);
            SysWork_StateStepIncrement();

        case 1:
            func_80085E6C(0x3000, false);
            break;

        case 2:
            func_80085DF0(syswork);
            break;

        case 3:
            func_800865FC(false, 0, 0, FP_ANGLE(-112.5f), Q12(0.0f), Q12(0.0f));
            SysWork_StateStepIncrement();

        case 4:
            func_800866D4(53, 1, 0);
            break;

        case 5:
            MapMsg_DisplayAndHandleSelection(false, 20, 0, 0, 0, false);
            break;

        case 6:
            func_800865FC(true, 0, 0, FP_ANGLE(-135.0f), Q12(5.0f), 0x81000);
            func_800865FC(true, 0, 1, FP_ANGLE(-90.0f), -0x6000, 0x80000);
            func_800865FC(true, 0, 2, FP_ANGLE(-90.0f), -0x11800, 0x81800);
            SysWork_StateStepIncrement();

        case 7:
            func_800866D4(54, 3, 0);
            break;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
    }
}

void func_800DA454(void) // 0x800DA454
{
    VECTOR3 vec0;
    s16     angle;
    s32     temp_s0;
    s32     sinAngle;
    s32     temp_v0_5;
    s32     temp_v1;
    s32     var_a3;

    if (Math_Vector2MagCalc(Q12(-29.5f) - g_SysWork.player_4C.chara_0.position_18.vx,
                            Q12(128.7f) - g_SysWork.player_4C.chara_0.position_18.vz) >= Q12(16.0f))
    {
        D_800DFAB8 += g_DeltaTime0;
        if (D_800DFAB8 > Q12(0.8f))
        {
            angle = ratan2(Q12(-29.5f) - g_SysWork.player_4C.chara_0.position_18.vx,
                           Q12(128.7f) - g_SysWork.player_4C.chara_0.position_18.vz);
            sinAngle = Math_Sin(angle);

            vec0.vy = Q12(0.0f);
            vec0.vx = g_SysWork.player_4C.chara_0.position_18.vx + (sinAngle * 16);
            vec0.vz = g_SysWork.player_4C.chara_0.position_18.vz + (Math_Cos((s32)angle) * 16);

            temp_s0 = (Rng_Rand16() & 0x1F) + 75;
            temp_v0_5 = Rng_Rand16();
            var_a3 = temp_v0_5;

            if (temp_v0_5 < 0)
            {
                var_a3 = temp_v0_5 + 0x1F;
            }

            func_8005DD44(Sfx_Unk1353, &vec0, temp_s0, (s8)((temp_v0_5 - ((var_a3 >> 5) << 5)) - 16));
            D_800DFAB8 = 0;
        }
    }
}

void func_800DA5A0(void) // 0x800DA5A0
{
    s32 temp_s1_2;
    s32 temp_s2;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Camera_TranslationSet(NULL, Q12(-22.0f), Q12(-2.4f), Q12(130.1f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_RotationSet(&g_SysWork.npcs_1A0[0].position_18, Q12(0.0f), Q12(-1.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            break;

        case 1:
        case 2:
            func_800868DC(0);
            func_800868DC(1);
            func_800868DC(2);
            break;

        case 4:
        case 5:
        case 6:
            Camera_TranslationSet(NULL,
                                  Q12(-22.0f) - func_800868F4(Q12(4.0f),  Q12(5.0f), 0),
                                  Q12(-2.4f)  - func_800868F4(Q12(-1.5f), Q12(5.0f), 1),
                                  Q12(130.1f) - func_800868F4(Q12(4.0f),  Q12(5.0f), 2),
                                  Q12(0.0f), Q12(0.0f),
                                  Q12(0.0f), Q12(0.0f),
                                  false);
            Camera_RotationSet(&g_SysWork.npcs_1A0[0].position_18, Q12(0.0f), Q12(-1.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), false);
            break;

        case 3:
            Camera_RotationSet(&g_SysWork.npcs_1A0[0].position_18, Q12(0.0f), Q12(-1.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), false);
            break;
        
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        default:
            vcReturnPreAutoCamWork(D_800DFAC2);
            D_800DFAC2 = 0;
            break;
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            sharedFunc_800D88AC_0_s00(&g_SysWork.npcs_1A0[0]);
            func_800865FC(true, 1, 0, FP_ANGLE(-135.0f), Q12(-35.0f), Q12(120.0f));

            temp_s1_2 = g_SysWork.player_4C.chara_0.position_18.vx;
            temp_s2 = g_SysWork.player_4C.chara_0.position_18.vz;
            g_MapMsgSoundIdx = 0;

            g_SysWork.player_4C.chara_0.position_18.vx = Q12(-40.0f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(127.0f);

            func_8003C3AC();

            g_SysWork.player_4C.chara_0.position_18.vx = temp_s1_2;
            g_SysWork.player_4C.chara_0.position_18.vz = temp_s2;

            SysWork_StateStepIncrement();
            break;

        case 1:
            func_800CB6B0(0, g_SavegamePtr->mapOverlayId_A4, 0);
            SysWork_StateStepIncrement();

        case 2:
            Map_MessageWithAudio(0x15, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 3:
            g_SysWork.npcs_1A0[0].properties_E4.player.headingAngle_124 = Q12(1.8f);

            func_80086728(&g_SysWork.npcs_1A0[0], 2, 1, 0);
            func_80085E6C(Q12(1.5f), false);
            break;

        case 4:
            g_SysWork.npcs_1A0[0].properties_E4.player.headingAngle_124 = Q12(1.8f);
            func_80086728(&g_SysWork.npcs_1A0[0], 2, 1, 0);
            break;

        case 5:
            g_SysWork.player_4C.chara_0.position_18.vx = Q12(-26.0f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(127.0);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(-135.0f);

            func_800865FC(true, 0, 0, FP_ANGLE(-135.0f), Q12(-29.0f), Q12(125.0f));
            SysWork_StateStepIncrement();

        case 6:
            func_800866D4(54, 1, 0);
            break;

        case 7:
            if (func_8003C850())
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 8:
            Map_MessageWithAudio(22, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 9:
            func_800865FC(true, 1, 0, FP_ANGLE(-112.5f), Q12(-36.0f), Q12(119.5f));
            SysWork_StateStepIncrement();

        case 10:
            g_SysWork.npcs_1A0[0].properties_E4.player.headingAngle_124 = Q12(0.55f);
            func_80086728(&g_SysWork.npcs_1A0[0], 1, 1, 0);
            break;

        case 11:
            Map_MessageWithAudio(0x17, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        default:
            func_8008616C(0, false, 2, 0, false);
            Savegame_EventFlagSet(EventFlag_4);
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            sharedFunc_800D88C0_0_s00(&g_SysWork.npcs_1A0[0], false);
            break;
    }
}

void func_800DAA68(void) // 0x800DAA68
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_800865FC(false, 0, 0, FP_ANGLE(180.0f), Q12(0.0f), Q12(-1.0f));
            SysWork_StateStepIncrement();

        case 1:
            func_80085E6C(Q12(0.3f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 24, 0, 0, 0, false);
            break;

        case 4:
            func_800866D4(54, 1, 0);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
    }
}

void func_800DAB8C(void) // 0x800DAB8C
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_800865FC(false, 0, 0, FP_ANGLE(90.0f), Q12(1.0f), Q12(0.0f));
            SysWork_StateStepIncrement();

        case 1:
            func_80085E6C(Q12(0.3f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 24, 0, 0, 0, false);
            break;

        case 4:
            func_800866D4(54, 1, 0);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
    }
}

void func_800DACB0(void) // 0x800DACB0
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_800865FC(false, 0, 0, FP_ANGLE(-90.0f), Q12(-1.0f), Q12(0.0f));
            SysWork_StateStepIncrement();

        case 1:
            func_80085E6C(Q12(0.3f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 24, 0, 0, 0, false);
            break;

        case 4:
            func_800866D4(54, 1, 0);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
    }
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DADD4);
/* TODO: linker can't find `Event_ItemTake`.
void func_800DADD4(void)
{
    Event_ItemTake(InventoryItemId_Camera, 1, 0x207, 0x37);
}
*/

void func_800DAEFC(void) // 0x800DAEFC
{
    q19_12 offsetY;
    q19_12 offsetZ;
    s32    temp;
    s32    temp2;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();

            g_SysWork.npcs_1A0[0].position_18.vx = Q12(-62.0f);
            g_SysWork.npcs_1A0[0].rotation_24.vy = FP_ANGLE(180.0f);
            g_SysWork.npcs_1A0[0].position_18.vz = g_SysWork.player_4C.chara_0.position_18.vz - Q12(19.0f);

            func_8008616C(0, true, 2, 0, false);
            SysWork_StateStepIncrement();

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_800865FC(false, 0, 0, FP_ANGLE(180.0f), Q12(0.0f), Q12(0.0f));
            Camera_TranslationSet(&g_SysWork.player_4C.chara_0.position_18, Q12(0.24f), Q12(-4.06f), Q12(-5.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_RotationSet(&g_SysWork.player_4C.chara_0.position_18, Q12(-0.72f), Q12(-2.11f), Q12(-1.63f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            SysWork_StateStepIncrement();

        case 3:
            func_800866D4(53, 1, 0);
            break;

        case 4:
            func_800865FC(true, 0, 0, FP_ANGLE(180.0f), Q12(-62.0f), g_SysWork.player_4C.chara_0.position_18.vz - Q12(10.0f));
            func_80085E6C(0x1000, false);
            break;

        case 5:
            func_800866D4(54, 1, 0);
            func_80085E6C(Q12(1.0f), false);
            break;

        case 6:
            func_800866D4(54, 1, 0);
         
            offsetY = FP_MULTIPLY(Math_Cos(g_SysWork.player_4C.chara_0.rotation_24.vy), Q12(0.6f), Q12_SHIFT) - Q12(1.84f);
            temp = FP_MULTIPLY(Math_Cos(g_SysWork.player_4C.chara_0.rotation_24.vy), Q12(2.0f), Q12_SHIFT) + Q12(4.0f);

            if ((g_SysWork.player_4C.chara_0.position_18.vz + temp) < Q12(130.0f))
            {
                temp2 = FP_MULTIPLY(Math_Cos(g_SysWork.player_4C.chara_0.rotation_24.vy), Q12(2.0f), Q12_SHIFT) + Q12(4.0f);
                offsetZ = g_SysWork.player_4C.chara_0.position_18.vz + temp2;
            } 
            else 
            {
                offsetZ = Q12(130.0f);
            }

            Camera_TranslationSet(NULL, Q12(-62.0f), offsetY, offsetZ, Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), D_800DFAC4);
            Camera_RotationSet(NULL,
                               g_SysWork.player_4C.chara_0.position_18.vx,
                               Q12(-0.7f),
                               g_SysWork.player_4C.chara_0.position_18.vz - Q12(5.0f),
                               Q12(0.0f), Q12(0.0f),
                               Q12(0.0f), Q12(0.0f),
                               D_800DFAC4);

            D_800DFAC4 = false;
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            func_8008616C(0, false, 2, 0, false);

            Savegame_EventFlagSet(EventFlag_7);
            Savegame_EventFlagSet(EventFlag_8);

            func_800865FC(true, 1, 0, FP_ANGLE(180.0f), Q12(-62.0f), Q12(49.0f));
    }
}

void func_800DB26C(void) // 0x800DB26C
{
    if (g_SysWork.sysStateStep_C[0] == 0)
    {
        Camera_TranslationSet(NULL, Q12(-62.0f), Q12(-2.24f), Q12(117.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
        Camera_RotationSet(NULL, Q12(-62.0f), Q12(-0.7f), Q12(104.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
        func_800868DC(2);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8008616C(0, true, 2, 0, false);
            func_800865FC(1, 0, 0, FP_ANGLE(-90.0f), Q12(-60.5f), g_SysWork.player_4C.chara_0.position_18.vz);

            g_SysWork.npcs_1A0[0].position_18.vx = Q12(-62.0f);
            g_SysWork.npcs_1A0[0].rotation_24.vy = FP_ANGLE(180.0f);
            g_SysWork.npcs_1A0[0].position_18.vz = g_SysWork.player_4C.chara_0.position_18.vz - Q12(9.0f);

            SysWork_StateStepIncrement();

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_800866D4(54, 1, 0);
            break;

        case 3:
            g_DeltaTime0 >>= 1; // `/ 2`.

            func_800865FC(0, 0, 0, FP_ANGLE(-135.0f), Q12(0.0f), Q12(0.0f));
            func_80085E6C(Q12(0.8f), false);
            break;

        case 4:
            g_DeltaTime0 >>= 1; // `/ 2`.

            Savegame_EventFlagSet(EventFlag_8);
            func_800866D4(54, 1, 0);
            break;

        case 5:
            g_DeltaTime0 >>= 1;
            func_80085E6C(Q12(1.0f), false);
            break;

        default:
            func_8008616C(0, false, 2, 0, false);
            Savegame_EventFlagSet(EventFlag_7);
            func_800865FC(1, 1, 0, FP_ANGLE(180.0f), Q12(-62.0f), Q12(49.0f));
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800DB514(void) // 0x800DB514
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();

            D_800DFB5C = 0;
            D_800DFB60 = 0;

            GameFs_FlameGfxLoad();
            SysWork_StateStepIncrement();

        case 1:
            func_8008616C(2, true, 2, 0, false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            SysWork_StateStepIncrement();

        case 4:
            MapMsg_DisplayAndHandleSelection(false, 25, false, false, 0, false);
            break;

        case 5:
            func_8008605C(16, 6, 5, false);
            break;

        case 6:
            if (D_800DFB60)
            {
                SysWork_StateStepIncrement();
            }
            break;

            if (Fs_QueueDoThingWhenEmpty())
            {
                D_800DFB60++;
                Chara_Load(1, Chara_GreyChild, &g_SysWork.npcCoords_FC0[0], 0, NULL, NULL);
            }

        case 7:
            sharedFunc_800D209C_0_s00();
            SysWork_StateStepIncrement();

        case 8:
            func_80085EB8(1, &g_SysWork.player_4C.chara_0, 0, false);
            break;

        case 9:
            func_8003EF10(10, 10, PrimitiveType_S32, &D_800DFB5C, 0, Q12(0.5f));
            SysWork_StateStepIncrement();

        case 10:
            D_800DFB5C += g_DeltaTime0;

            if (D_800DFB5C > Q12(0.5f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 11:
            Savegame_EventFlagSet(EventFlag_17);
            MapMsg_DisplayAndHandleSelection(false, 30, false, false, 0, false);
            break;

        default:
            func_8008616C(0, false, 2, 0, false);
            sharedFunc_800D2244_0_s00(true);
            SysWork_StateSetNext(SysState_Gameplay);

            func_80088D0C();
            Chara_Spawn(Chara_GreyChild, 0, Q12(-252.0f), Q12(223.0f), FP_ANGLE(180.0f), 5);
            Chara_Spawn(Chara_GreyChild, 1, Q12(-254.0f), Q12(221.0f), FP_ANGLE(135.0f), 5);
            Chara_Spawn(Chara_GreyChild, 2, Q12(-259.0f), Q12(232.0f), FP_ANGLE(0.0f),   5);
            break;
    }

    if (D_800DFB60 == 0)
    {
        if (Fs_QueueDoThingWhenEmpty())
        {
            D_800DFB60++;
            Chara_Load(1, Chara_GreyChild, &g_SysWork.npcCoords_FC0[0], 0, NULL, NULL);
        }
    }
}

void func_800DB870(void) // 0x800DB870
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
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DB94C);

void func_800DBE00(void) // 0x800DBE00
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

    rotXY = 0xFAE4FE17; // @hack `vx` and `vy` combined into `s32`.
    D_800E3AAC.vz = 0;

    Savegame_EventFlagClear(EventFlag_188);
    *(s32*)&D_800E3AAC.vx = rotXY;
}

void Map_WorldObjectsUpdate(void) // 0x800DBF08
{
    VECTOR3 viewPos;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    vwGetViewPosition(&viewPos);

    if (Savegame_EventFlagGet(EventFlag_4) && !Savegame_EventFlagGet(EventFlag_13))
    {
        if (!Savegame_EventFlagGet(EventFlag_6))
        {
            func_800DC33C();
        }
        else if (!Savegame_EventFlagGet(EventFlag_9))
        {
            func_800DC694();
        }
        else if (!Savegame_EventFlagGet(EventFlag_11))
        {
            func_800DC8D8();
        }

        func_800DCA30();
    }

    if (Savegame_EventFlagGet(EventFlag_13) && !Savegame_EventFlagGet(EventFlag_16))
    {
        func_800DCC54();
    }

    if (Savegame_EventFlagGet(EventFlag_17))
    {
        func_800DD0CC();
    }

    if (!Savegame_EventFlagGet(EventFlag_24))
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, -7, -1, -7) && 
            (PLAYER_IN_MAP_CHUNK(vz, 1, 6, -1, 6) || PLAYER_IN_MAP_CHUNK(vz, 1, 7, -1, 7)))
        {
            D_800E3AAC.vz += FP_MULTIPLY_PRECISE(g_DeltaTime0, (-0x400 - (Rng_Rand16() & 0x1FF)), Q12_SHIFT);
            g_WorldGfx_ObjectAdd(&D_800E3A5C[0], &D_800E3A9C, &D_800E3AAC);
            g_WorldGfx_ObjectAdd(&D_800E3A5C[1], &D_800E3A9C, &D_800E3AAC);
        
            if (g_SysWork.field_22A0 & 0x40)
            {
                Savegame_EventFlagClear(EventFlag_188);
            }

            if (!Savegame_EventFlagGet(EventFlag_188))
            {
                func_8004690C(Sfx_Unk1361);
                Sd_EngineCmd(Sfx_Unk1358);
                Savegame_EventFlagSet(EventFlag_188);
            }

            if (!Savegame_EventFlagGet(EventFlag_24))
            {
                func_8005DE0C(Sfx_Unk1358, &D_800E3A9C, 0x40, 0x8000, 0);
            }
        }
    }
}

void Event_GreyChildrenSpawn(void) // 0x800DC1E8
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (Savegame_EventFlagGet(EventFlag_17) && g_SysWork.npcs_1A0[0].model_0.charaId_0 == Chara_None)
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, -7, -1, -7) && PLAYER_IN_MAP_CHUNK(vz, 1, 7, -1, 7))
        {
            Chara_Spawn(Chara_GreyChild, 0, Q12(-252.0f), Q12(223.0f), FP_ANGLE(180.0f), 5);
            Chara_Spawn(Chara_GreyChild, 1, Q12(-254.0f), Q12(221.0f), FP_ANGLE(135.0f), 5);
            Chara_Spawn(Chara_GreyChild, 2, Q12(-259.0f), Q12(232.0f), FP_ANGLE(0.0f),   5);
        }
    }
}

void func_800DC33C(void) // 0x800DC33C
{
    VECTOR3 camPos;
    s16     temp_a0;
    s16     var_s1;
    q19_12  temp_a0_2;
    s32     temp_v1;
    s32     var_a0;
    s32     var_a2;
    s32     var_v1_2;

    if (!Savegame_EventFlagGet(EventFlag_5))
    {
        func_800865FC(true, 1, 0, FP_ANGLE(180.0f), Q12(-62.0f), Q12(108.0f));
        sharedFunc_800D88AC_0_s00(&g_SysWork.npcs_1A0[0]);

        Savegame_EventFlagSet(EventFlag_5);
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

                sharedFunc_800D88C0_0_s00(&g_SysWork.npcs_1A0[0], false);

                Savegame_EventFlagSet(EventFlag_6);
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

    if (!Savegame_EventFlagGet(EventFlag_7))
    {
        sharedFunc_800D88AC_0_s00(&g_SysWork.npcs_1A0[0]);
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

                sharedFunc_800D88C0_0_s00(&g_SysWork.npcs_1A0[0], false);

                Savegame_EventFlagSet(EventFlag_9);
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

    if (!Savegame_EventFlagGet(EventFlag_10))
    {
        g_SysWork.npcs_1A0[0].position_18.vx = Q12(-61.0f);
        g_SysWork.npcs_1A0[0].position_18.vz = Q12(48.0f);
        g_SysWork.npcs_1A0[0].rotation_24.vy = FP_ANGLE(90.0f);

        if (mag < Q12(14.8f))
        {
            sharedFunc_800D88AC_0_s00(&g_SysWork.npcs_1A0[0]);

            Savegame_EventFlagSet(EventFlag_10);

            func_800865FC(true, 1, 0, FP_ANGLE(90.0f), Q12(-57.0f), Q12(47.0f));
        }
    }
    else
    {
        g_SysWork.npcs_1A0[0].properties_E4.player.headingAngle_124 = Q12(1.8f);

        func_8008677C(&g_SysWork.npcs_1A0[0], 2, 1);

        if (g_SysWork.npcs_1A0[0].position_18.vx > Q12(-58.0f))
        {
            Savegame_EventFlagSet(EventFlag_11);
            g_SysWork.npcs_1A0[0].model_0.charaId_0 = Chara_None;

            func_8005DC1C(Sfx_Unk1354, &D_800CB6A4, Q8_CLAMPED(0.5f), 0);
        }
    }
}

INCLUDE_ASM("asm/maps/map0_s00/nonmatchings/map0_s00", func_800DCA30);

void func_800DCC54(void) // 0x800DCC54
{
    if (D_800DFADC == NO_VALUE)
    {
        func_8003EF10(6, 6, PrimitiveType_S32, &D_800DFADC, Q12(0.0f), Q12(100.0f));
        D_800DFADC = Q12(0.0f);

        Sd_PlaySfx(Sfx_Unk1359, 0, Q8_CLAMPED(0.875f));
    }

    if (Savegame_EventFlagGet(EventFlag_14))
    {
        if (!Savegame_EventFlagGet(EventFlag_18))
        {
            sharedFunc_800D0B18_0_s00(6);

            Savegame_EventFlagSet(EventFlag_18);

            Sd_PlaySfx(Sfx_Unk1359, 0, Q8_CLAMPED(0.75f));

            D_800DFADC = Q12(60.0f);
        }

        D_800DFADC = func_800DCF38(D_800DFADC);
    } 
    else
    {
        D_800DFADC = func_800DCDA8();
    }

    if (D_800DFADC >= Q12(80.0f))
    {
        Savegame_EventFlagSet(EventFlag_15);
    }

    if (D_800DFADC >= Q12(100.0f))
    {
        Savegame_EventFlagSet(EventFlag_16);
    }
}

s32 func_800DCDA8(void) // 0x800DCDA8
{
    s16 sp20;
    s32 i;
    s32 var_s2;
    s16 var_s5;
    s32 var_s4;
    s32 temp_v1_3;

    var_s4 = 0;
    var_s5 = 0;
    var_s2 = 0;

    for (i = 0; i < 5; i++)
    {
        temp_v1_3 = func_8005C478(&sp20,
                                  g_SysWork.player_4C.chara_0.position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz,
                                  D_800DFAE0[i].vx, D_800DFAE0[i].vy,
                                  D_800DFAE0[i + 1].vx, D_800DFAE0[i + 1].vy);

        if (i == 0)
        {
            var_s4 = temp_v1_3;
            var_s5 = sp20;
            var_s2 = 0;
        }
        else if (temp_v1_3 < var_s4)
        {
            var_s4 = temp_v1_3;
            var_s5 = sp20;
            var_s2 = i;
        }
    }

    return FP_MULTIPLY_PRECISE(D_800DFAE0[var_s2 + 1].vz - D_800DFAE0[var_s2].vz, var_s5, Q12_SHIFT) + D_800DFAE0[var_s2].vz;
}

s32 func_800DCF38(s32 arg0) // 0x800DCF38
{
    s16 sp20;
    s32 var_t0;
    s32 var_v0;

    var_t0 = 0;

    if (g_SysWork.sysState_8 == SysState_EventCallFunc)
    {
        if (!Savegame_EventFlagGet(EventFlag_15))
        {
            return arg0;
        }
    }
    else
    {
        if (!Savegame_EventFlagGet(EventFlag_15))
        {
            if (g_SysWork.player_4C.chara_0.position_18.vx < Q12(-200.0f))
            {
                func_8005C478(&sp20,
                              g_SysWork.player_4C.chara_0.position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz,
                              D_800DFB28[0].vx, D_800DFB28[0].vy, D_800DFB28[1].vx, D_800DFB28[1].vy);

                var_v0 = FP_MULTIPLY_PRECISE(D_800DFB28[1].vz - D_800DFB28[0].vz, sp20, Q12_SHIFT) + Q12(60.0f);
                var_t0 = D_800DFB28[0].vz + var_v0;
            }

            return MAX(var_t0, arg0);
        }
    }

    return FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(9.0f), Q12_SHIFT) + arg0;
}

void func_800DD0CC(void) // 0x800DD0CC
{
    s32 vecs[2];

    if (D_800DFB40 == NO_VALUE)
    {
        func_8003EF10(6, 6, PrimitiveType_S32, &D_800DFB40, 0, Q12(100.0f));
        D_800DFB40 = 0;
    }

    D_800DFB44.field_0 += g_DeltaTime0;

    vecs[0] = FP_MULTIPLY(D_800DFB44.field_0, D_800DFB48.field_0, 6);
    if (vecs[0] >= Q12(1.0f))
    {
        D_800DFB44.field_0 = 0;
        D_800DFB48.field_0 = Rng_GenerateInt((u32)Rng_Rand16(), 32, 95);
        D_800DFB48.field_1 = Rng_GenerateInt((u32)Rng_Rand16(), 32, 63);
        vecs[0]           &= Q12_FRACT(vecs[0]);
    }

    vecs[0] = FP_MULTIPLY(D_800DFB48.field_1, Math_Sin(D_800DFB44.field_2), Q12_SHIFT);
    D_800DFB44.field_2 += g_DeltaTime0;

    vecs[1] = FP_MULTIPLY(D_800DFB44.field_2, D_800DFB48.field_2, 6);
    if (vecs[1] >= Q12(1.0f))
    {
        D_800DFB44.field_2 = 0;
        D_800DFB48.field_2 = Rng_GenerateInt((u32)Rng_Rand16(), 32, 95);
        vecs[1]           &= Q12_FRACT(vecs[1]);
    }

    D_800DFB40 = MAX(Q12(0.0f), FP_MULTIPLY((FP_MULTIPLY(vecs[0], Q12(4.5f), 6) + Q12(2.5f)), Math_Sin(vecs[1]), Q12_SHIFT) + Q12(4.0f));
}

INCLUDE_RODATA("asm/maps/map0_s00/nonmatchings/map0_s00", D_800CB6A4);
