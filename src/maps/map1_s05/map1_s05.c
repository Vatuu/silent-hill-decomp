#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
#include "maps/map1/map1_s05.h"
#include "maps/particle.h"
#include "maps/characters/player.h"
#include "maps/characters/split_head.h"

#include "maps/shared/sharedFunc_800CAAD0_1_s05.h" // 0x800CAAD0

#include "maps/shared/sharedFunc_800CABF8_1_s05.h" // 0x800CABF8

#include "maps/shared/sharedFunc_800CB040_1_s05.h" // 0x800CB040

#include "maps/shared/sharedFunc_800CB884_1_s05.h" // 0x800CB884

#include "maps/shared/sharedFunc_800CBE7C_1_s05.h" // 0x800CBE7C

#include "maps/shared/sharedFunc_800CBF74_1_s05.h" // 0x800CBF74

#include "maps/shared/sharedFunc_800CC618_1_s05.h" // 0x800CC618

#include "maps/shared/sharedFunc_800CCDD4_1_s05.h" // 0x800CCDD4

#include "maps/shared/sharedFunc_800CCE2C_1_s05.h" // 0x800CCE2C

#include "maps/shared/sharedFunc_800CCF30_1_s05.h" // 0x800CCF30

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

// TODO: Move this line into separate `Chara_SplitHead` split.
#include "../src/maps/characters/split_head.c" // 0x800CF818

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D489C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D48AC

void Map_RoomBgmInit(bool arg0) // 0x800D494C
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

    Bgm_Update(var_a0, Q12(0.1f), &D_800D5C3C);
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
            sharedData_800D8568_1_s05.field_1  = 0;
            sharedData_800D8568_1_s05.field_10 = 0;

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
            g_SysWork.pointLightIntensity_2378 = 0;

            // Warp camera.
            Camera_PositionSet(NULL, Q12(19.72f), Q12(-5.2f), Q12(-27.6f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(19.72f), Q12(-3.3f), Q12(-24.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 2:
            sharedData_800D8568_1_s05.field_1 = 3;
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
            break;

        case 4:
            g_SysWork.pointLightIntensity_2378 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.225f);
            if (g_SysWork.pointLightIntensity_2378 > Q12(2.25f))
            {
                g_SysWork.pointLightIntensity_2378 = Q12(2.25f);
                SysWork_StateStepIncrement(0);
            }
            break;

        case 5:
            g_SysWork.pointLightIntensity_2378 -= Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.45f);
            if (g_SysWork.pointLightIntensity_2378 < Q12(1.3843f))
            {
                Savegame_EventFlagSet(EventFlag_129);
                SysWork_StateStepReset();
            }
            break;

        default:
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);

            g_SysWork.pointLightIntensity_2378 = Q12(1.3843f);

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
                scratchData->sprt_0->v0 = (scratchData->activeBufferIdx_C == 0) ? 32 : 0;
                setWH(scratchData->sprt_0, (i == 0) ? 256 : 64, 224);
                addPrimFast(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratchData->sprt_0, 4);

                scratchData->sprt_0++;
                scratchData->tpage_4 = (DR_TPAGE*)scratchData->sprt_0;
                setDrawTPage(scratchData->tpage_4, 0, 0, getTPage(2, 0, ((scratchData->activeBufferIdx_C << 4) + (i << 2)) << 6, (((scratchData->activeBufferIdx_C << 4) >> 4) & 1) << 8));

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

            g_SysWork.pointLightIntensity_2378 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.2f);
            if (g_SysWork.pointLightIntensity_2378 > Q12(3.0f))
            {
                g_SysWork.pointLightIntensity_2378 = Q12(3.0f);
            }
            break;

        case 2:
            sharedData_800D8568_1_s05.field_1 = 1;
            sharedData_800D8568_1_s05.field_2 = 3;
            SysWork_StateStepIncrement(0);

        case 3:
            if (D_800D5D11 & 1)
            {
                SD_Call(Sfx_Unk1359);
                D_800D5D11++;
            }

            Sd_SfxAttributesUpdate(Sfx_Unk1359, 0, MAX(0, (Q12_FRACT(g_SysWork.pointLightIntensity_2378) >> 4) - (D_800D5D11 * 8)), 0);

            g_SysWork.pointLightIntensity_2378 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, 0.15f, 12);
            if (g_SysWork.pointLightIntensity_2378 < (6 - D_800D5D11) * Q12(0.5f))
            {
                D_800D5D11++;
            }

            if (g_SysWork.pointLightIntensity_2378 < 0)
            {
                g_SysWork.pointLightIntensity_2378 = 0;
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

void Map_WorldObjectsInit(void) // 0x800D525C
{
    D_800D86F8[0] = 0;
    D_800D86F8[1] = 0;
    D_800D86FC[0] = 0x40;
    D_800D86FC[1] = 0x40;
    sharedData_800D8568_1_s05.flags_0 = (1 << 3) | (1 << 0);
    sharedData_800D8568_1_s05.field_C = 0x12C;
    sharedData_800D8568_1_s05.field_12 = -0x2CCCu;
    sharedData_800D8568_1_s05.field_14 = -0x800;
    sharedData_800D8568_1_s05.field_1C = 0xA00;
    sharedData_800D8568_1_s05.field_E = -0x1000;
    sharedData_800D8568_1_s05.field_4 = 0x80;
    sharedData_800D8568_1_s05.field_5 = 0xC4;
    sharedData_800D8568_1_s05.field_6 = 0x3C;
    sharedData_800D8568_1_s05.field_8 = 0x200;
    sharedData_800D8568_1_s05.field_A = 0x400;
    sharedData_800D8568_1_s05.field_1 = 2;
    sharedData_800D8568_1_s05.field_2 = 8;
    sharedData_800D8568_1_s05.field_3 = 0x40;
    sharedData_800D8568_1_s05.field_20 = Q12(19.7f);
    sharedData_800D8568_1_s05.field_24 = Q12(-19.1f);
    D_800D86FE = 48;

    if (Savegame_EventFlagGet(EventFlag_130))
    {
        g_SysWork.pointLightIntensity_2378 = Q12(1.3843f);
        sharedData_800D8568_1_s05.field_1 = 0;
    }

    sharedFunc_800CAAD0_1_s05();
    WorldObjectInit(&g_WorldObject0, "SPHERE_H", 19.7f, 1.58f, -19.1f, 0.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject1, "WHEEL_HI", 19.7f, -0.06f, -19.1f, 0.0f, 0.0f, 0.0f);

    g_SysWork.field_235C = NULL;
    g_SysWork.pointLightPosition_2360.vx = Q12(19.7f);
    g_SysWork.pointLightPosition_2360.vy = Q12(-3.0f);
    g_SysWork.pointLightPosition_2360.vz = Q12(-19.1f);

    g_SysWork.field_236C = NULL;
    g_SysWork.pointLightRot_2370.vx = Q12_ANGLE(-90.0f);
    g_SysWork.pointLightRot_2370.vy = Q12_ANGLE(0.0f);
    g_SysWork.pointLightRot_2370.vz = Q12_ANGLE(0.0f);

    SD_Call(Sfx_Unk1478);
}

void Map_WorldObjectsUpdate(void) // 0x800D5400
{
    s32 sp18[2];
    s32 i;

    if (Savegame_EventFlagGet(EventFlag_129))
    {
        D_800D86F8[0] += g_DeltaTime;
        if ((D_800D86F8[0] * D_800D86FC[0]) >= Q12(SQUARE(8.0f)))
        {
            D_800D86F8[0] = 0;
            D_800D86FC[0] = Rng_GenerateUInt(32, 95);
            D_800D86FE    = Rng_GenerateUInt(32, 63);
        }

        sp18[0] = Q12_MULT(D_800D86FE, Math_Sin(D_800D86F8[1]));

        D_800D86F8[1] += g_DeltaTime;

        sp18[1] = (D_800D86F8[1] * D_800D86FC[1]) >> 6;

        if (sp18[1] >= Q12(1.0f))
        {
            D_800D86F8[1] = 0;
            D_800D86FC[1] = Rng_GenerateUInt(32, 95);
            sp18[1]       = Q12_FRACT(sp18[1]);
        }

        // TODO: Why doesn't `Q12_MULT_FLOAT_PRECISE(sp18[0], 0.6f)` work here?
        g_SysWork.pointLightIntensity_2378 = Q12(1.35f) + (((Q12(0.9f) + Q12_MULT_PRECISE(sp18[0], Q12(0.6f))) * Math_Sin(sp18[1])) >> 15);
    }

    g_WorldObject0.rotation_28.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(-90.0f));
    WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &g_WorldObject0.rotation_28);

    g_WorldObject1.rotation_28.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(15.0f));
    WorldGfx_ObjectAdd(&g_WorldObject1.object_0, &g_WorldObject1.position_1C, &g_WorldObject1.rotation_28);

    i = 0;
    while (1)
    {
        if (++i >= ARRAY_SIZE(sharedData_800DFB7C_0_s00))
        {
            break;
        }
    }

    func_8005DE0C(Sfx_Unk1478, &QVECTOR3(19.7f, -1.5f, -19.1f), Q8_CLAMPED(0.5f) - Q12_MULT_PRECISE(D_800D8578, Q8_CLAMPED(0.5f)), Q12(16.0f), 0);
}
