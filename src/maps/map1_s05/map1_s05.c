#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map1/map1_s05.h"
#include "maps/characters/Chara_Splithead.h"

INCLUDE_RODATA("asm/maps/map1_s05/nonmatchings/map1_s05", D_800C9578);

INCLUDE_RODATA("asm/maps/map1_s05/nonmatchings/map1_s05", g_MapOverlayHeader);

void func_800CAAD0(void) // 0x800CAAD0
{
    s32 i;
    s32 fieldC;

    if (D_800D8568.flags_0 & (1 << 0))
    {
        D_800D8568.field_18 =
        D_800D8568.field_1A = D_800D8568.field_1C * 2;
    }
    else
    {
        D_800D8568.field_1C = (D_800D8568.field_18 + D_800D8568.field_1A) >> 1;
    }

    D_800D8568.field_16 = D_800D8568.field_12 - D_800D8568.field_14;

    if (D_800D8568.field_1 != 0)
    {
        D_800D8568.field_10 = Q12(1.0f);
    }
    else
    {
        D_800D8568.field_10 = Q12(0.0f);
    }

    fieldC = D_800D8568.field_C;
    for (i = ARRAY_SIZE(sharedData_800DFB7C_0_s00) - 1; i >= 0; i--)
    {
        if (sharedData_800DFB7C_0_s00[i].field_A != 0)
        {
            continue;
        }

        if (D_800D8568.field_1 == 0)
        {
            func_800CABF8(i, false);
        }
        else
        {
            sharedData_800DFB7C_0_s00[i].field_A = 12;
        }

        if (--fieldC == 0)
        {
            break;
        }
    }

    D_800C4414 |= 1 << 0;
}

void func_800CABF8(s32 idx, bool arg1) // 0x800CABF8
{
    s32   rand;
    q3_12 randAngle;

    if (D_800D8568.field_1 == 1 &&
        Rng_GenerateUInt(0, 4095) < D_800D8568.field_10 &&
        Rng_GenerateUInt(0, 7) == 0)
    {
        sharedData_800DFB7C_0_s00[idx].field_A = 12;
        return;
    }

    if ((D_800D8568.flags_0 & (1 << 4)) && Rng_GenerateUInt(0, 3) == 0)
    {
        sharedData_800DFB7C_0_s00[idx].field_A = 12;
        return;
    }

    rand      = Rng_GenerateInt(0, (s16)D_800D8568.field_1C - 1);
    randAngle = Rng_GenerateUInt(0, FP_ANGLE(360.0f) - 1);

    if ((D_800D8568.flags_0 & (1 << 2)) && Rng_GenerateUInt(0, 63) == 0)
    {
        sharedData_800DFB7C_0_s00[idx].field_A = 10;
    }
    else
    {
        sharedData_800DFB7C_0_s00[idx].field_A = 8;
    }

    if (arg1 == true)
    {
        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 = Rng_GenerateUInt(0, 15);
    }
    else
    {
        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 = Rng_GenerateUInt(0, 4095);
    }

    if (D_800D8568.flags_0 & (1 << 4))
    {
        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 = MIN((((D_800D8568.field_3 << 4) * rand) / (s16)D_800D8568.field_1C) +
                                                                 (u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 +
                                                                 D_800D8568.field_10 +
                                                                 Rng_GenerateUInt(0, 1023),
                                                                 4095);
    }
    else
    {
        sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 = MIN((((D_800D8568.field_3 << 4) * rand) / (s16)D_800D8568.field_1C) +
                                                                 (u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 +
                                                                 D_800D8568.field_10,
                                                                 4095);
    }

    sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_0 = (u8)Rng_Rand16() | 0x80; // TODO: Same as `Rng_Rand16() - 128`?
    sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_1 = (u8)Rng_Rand16() | 0x80;

    sharedData_800DFB7C_0_s00[idx].field_10.s_0.field_2 = Rng_GenerateUInt(0, 4095);

    if (D_800D8568.flags_0 & (1 << 0))
    {
        sharedData_800DFB7C_0_s00[idx].field_0.vx_0 = FP_FROM(rand * Math_Cos(randAngle), Q12_SHIFT);
        sharedData_800DFB7C_0_s00[idx].field_4.vz_4 = FP_FROM(rand * Math_Sin(randAngle), Q12_SHIFT);
    }
    else
    {
        sharedData_800DFB7C_0_s00[idx].field_0.vx_0 = Rng_GenerateInt(-D_800D8568.field_18, D_800D8568.field_18 - 1);
        sharedData_800DFB7C_0_s00[idx].field_4.vz_4 = Rng_GenerateInt(-D_800D8568.field_1A, D_800D8568.field_1A - 1);
    }

    sharedData_800DFB7C_0_s00[idx].vy_8    = D_800D8568.field_14 + FP_FROM((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_2 * D_800D8568.field_16, Q12_SHIFT);
    sharedData_800DFB7C_0_s00[idx].field_B = Rng_GenerateUInt(0, 1) + (Rng_GenerateInt(0, 2) * 2);
}

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CB040);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CB884);

#include "maps/shared/sharedFunc_800CBE7C_1_s05.h" // 0x800CBE7C

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800CBF74_1_s05); // 0x800CBF74

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800CC618_1_s05); // 0x800CC618

#include "maps/shared/sharedFunc_800CCDD4_1_s05.h" // 0x800CCDD4

#include "maps/shared/sharedFunc_800CCE2C_1_s05.h" // 0x800CCE2C

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CCF30);

#include "maps/shared/sharedFunc_800CB6B0_0_s00_noParticles.h" // 0x800CD5EC

#include "maps/shared/Player.h"

#include "maps/shared/Ai_Splithead_Update.h" // 0x800CF818

#include "maps/shared/Ai_Splithead_Init.h" // 0x800CF8D8

#include "maps/shared/sharedFunc_800CF990_1_s05.h" // 0x800CF990

#include "maps/shared/Ai_Splithead_DamageTake.h" // 0x800CFE94

#include "maps/shared/sharedFunc_800D0054_1_s05.h" // 0x800D0054

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D00D0);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D0948);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D11A0);

#include "maps/shared/sharedFunc_800D17BC_1_s05.h" // 0x800D17BC

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D19B8);

#include "maps/shared/sharedFunc_800D2214_1_s05.h" // 0x800D2214

#include "maps/shared/sharedFunc_800D2444_1_s05.h" // 0x800D2444

#include "maps/shared/sharedFunc_800D263C_1_s05.h" // 0x800D263C

#include "maps/shared/sharedFunc_800D267C_1_s05.h" // 0x800D267C

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D274C_1_s05); // 0x800D274C

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D2D74_1_s05); // 0x800D2D74

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D3388_1_s05); // 0x800D3388

#include "maps/shared/sharedFunc_800D3AFC_1_s05.h" // 0x800D3AFC

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D3B30_1_s05); // 0x800D3B30

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D4070_1_s05); // 0x800D4070

#include "maps/shared/sharedFunc_800D4408_1_s05.h" // 0x800D4408

#include "maps/shared/sharedFunc_800D450C_1_s05.h" // 0x800D450C

#include "maps/shared/sharedFunc_800D4530_1_s05.h" // 0x800D4530

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D4594);

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D489C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D48AC

void func_800D494C(void) // 0x800D494C
{
    s32 var_a0;

    var_a0 = 1;
    if (g_SysWork.npcs_1A0[0].health_B0 > 0)
    {
        var_a0 = 2;
        if (g_SysWork.npcs_1A0[0].properties_E4.dummy.properties_E8[0].val16[0] & 0x10)
        {
            var_a0 = 6;
        }
    }

    func_80035F4C(var_a0, Q12(0.1f), &D_800D5C3C);
}

void func_800D49A4(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
};

void func_800D49AC(void) // 0x800D49AC
{
    s32 i;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4)
    {
        if (g_SysWork.sysStateStep_C[0] >= 3)
        {
            D_800D8568.field_1  = 0;
            D_800D8568.field_10 = 0;

            for (i = 0; i < ARRAY_SIZE(sharedData_800DFB7C_0_s00); i++)
            {
                s32 field_A = sharedData_800DFB7C_0_s00[i].field_A;
                if (field_A < 12)
                {
                    if (field_A >= 8)
                    {
                        sharedData_800DFB7C_0_s00[i].field_A = 12;
                    }
                }
            }

            vcReturnPreAutoCamWork(true);
            SysWork_StateStepReset();
        }
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            g_SysWork.field_30   = 20;
            g_SysWork.field_2378 = 0;

            // Warp camera.
            Camera_PositionSet(NULL, Q12(19.72f), Q12(-5.2f), Q12(-27.6f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(19.72f), Q12(-3.3f), Q12(-24.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 2:
            D_800D8568.field_1 = 3;
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
            break;

        case 4:
            g_SysWork.field_2378 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.225f, Q12_SHIFT);
            if (g_SysWork.field_2378 > Q12(2.25f))
            {
                g_SysWork.field_2378 = Q12(2.25f);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 5:
            g_SysWork.field_2378 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.45f, Q12_SHIFT);
            if (g_SysWork.field_2378 < Q12(1.3843f))
            {
                Savegame_EventFlagSet(EventFlag_129);
                SysWork_StateStepReset();
            }
            break;

        default:
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);

            g_SysWork.field_2378 = Q12(1.3843f);

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(false);

            Savegame_EventFlagSet(EventFlag_130);
            func_8003A16C();
            break;
    }
}

void func_800D4D1C(void) // 0x800D4D1C
{
    typedef struct
    {
        SPRT*     sprt_0;
        DR_TPAGE* tpage_4;
        DR_STP*   stp_8;
        s32       activeBufferIdx_C;
    } g_GteScratchData_func_800D4D1C;

    g_GteScratchData_func_800D4D1C* scratchData;
    s32                             i;

    scratchData = PSX_SCRATCH_ADDR(0);

    if (g_SysWork.sysStateStep_C[0] < 5)
    {
        if (g_SysWork.sysStateStep_C[0] > 0)
        {
            scratchData->activeBufferIdx_C = g_ActiveBufferIdx;
            scratchData->sprt_0            = (SPRT*)GsOUT_PACKET_P;
            for (i = 0; i < 2; i++)
            {
                setCodeWord(scratchData->sprt_0, PRIM_RECT | RECT_BLEND | RECT_TEXTURE, PACKED_COLOR(128, 128, 128, 0));
                setXY0Fast(scratchData->sprt_0, ((i << 8) - 160), -112);
                scratchData->sprt_0->u0 = 0;
                scratchData->sprt_0->v0 = (scratchData->activeBufferIdx_C == 0) << 5;
                setWH(scratchData->sprt_0, i == 0 ? 256 : 64, 224);
                addPrimFast(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratchData->sprt_0, 4);

                scratchData->sprt_0++;
                scratchData->tpage_4 = (DR_TPAGE*)scratchData->sprt_0;
                setDrawTPage(scratchData->tpage_4, 0, 0, getTPageFromBuffer(2, 0, scratchData->activeBufferIdx_C, i));

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
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Savegame_EventFlagClear(EventFlag_129);
            D_800D5D11 = 1;
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);

            g_SysWork.field_2378 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.2f, Q12_SHIFT);
            if (g_SysWork.field_2378 > Q12(3.0f))
            {
                g_SysWork.field_2378 = Q12(3.0f);
            }
            break;

        case 2:
            D_800D8568.field_1 = 1;
            D_800D8568.field_2 = 3;
            SysWork_StateStepIncrement(0);

        case 3:
            if (D_800D5D11 & 1)
            {
                SD_Call(Sfx_Unk1359);
                D_800D5D11++;
            }

            Sd_SfxAttributesUpdate(Sfx_Unk1359, 0, MAX(0, (Q12_FRACT(g_SysWork.field_2378) >> 4) - (D_800D5D11 * 8)), 0);

            g_SysWork.field_2378 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.15f, 12);
            if (g_SysWork.field_2378 < (6 - D_800D5D11) * Q12(0.5f))
            {
                D_800D5D11++;
            }

            if (g_SysWork.field_2378 < 0)
            {
                g_SysWork.field_2378 = 0;
                SysWork_StateStepIncrement(0);
            }
            break;

        case 4:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(2.5f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_132);
            break;
    }
}

void func_800D525C(void) // 0x800D525C
{
    D_800D86F8[0] = 0;
    D_800D86F8[1] = 0;
    D_800D86FC[0] = 0x40;
    D_800D86FC[1] = 0x40;
    D_800D8568.flags_0 = (1 << 3) | (1 << 0);
    D_800D8568.field_C = 0x12C;
    D_800D8568.field_12 = -0x2CCCu;
    D_800D8568.field_14 = -0x800;
    D_800D8568.field_1C = 0xA00;
    D_800D8568.field_E = -0x1000;
    D_800D8568.field_4 = 0x80;
    D_800D8568.field_5 = 0xC4;
    D_800D8568.field_6 = 0x3C;
    D_800D8568.field_8 = 0x200;
    D_800D8568.field_A = 0x400;
    D_800D8568.field_1 = 2;
    D_800D8568.field_2 = 8;
    D_800D8568.field_3 = 0x40;
    D_800D8568.field_20 = Q12(19.7f);
    D_800D8568.field_24 = Q12(-19.1f);
    D_800D86FE = 48;

    if (Savegame_EventFlagGet(EventFlag_130))
    {
        g_SysWork.field_2378 = Q12(1.3843f);
        D_800D8568.field_1 = 0;
    }

    func_800CAAD0();
    WorldObjectInit(&g_WorldObject0, "SPHERE_H", 19.7f, 1.58f, -19.1f, 0.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject1, "WHEEL_HI", 19.7f, -0.06f, -19.1f, 0.0f, 0.0f, 0.0f);

    g_SysWork.field_235C = NULL;
    g_SysWork.cutsceneLightPos_2360.vx = Q12(19.7f);
    g_SysWork.cutsceneLightPos_2360.vy = Q12(-3.0f);
    g_SysWork.cutsceneLightPos_2360.vz = Q12(-19.1f);

    g_SysWork.field_236C = NULL;
    g_SysWork.cutsceneLightRot_2370.vx = FP_ANGLE(-90.0f);
    g_SysWork.cutsceneLightRot_2370.vy = FP_ANGLE(0.0f);
    g_SysWork.cutsceneLightRot_2370.vz = FP_ANGLE(0.0f);

    SD_Call(Sfx_Unk1478);
}

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D5400);

INCLUDE_RODATA("asm/maps/map1_s05/nonmatchings/map1_s05", D_800CAAC4);
