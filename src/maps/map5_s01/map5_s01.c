#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
#include "maps/map5/map5_s01.h"
#include "maps/particle.h"
#include "maps/characters/air_screamer.h"
#include "maps/characters/groaner.h"
#include "maps/characters/player.h"
#include "maps/characters/romper.h"

#include "maps/shared/sharedFunc_800CE5D4_1_s03.h" // 0x800CCA90

#include "maps/shared/sharedFunc_800CE688_1_s03.h" // 0x800CCB44

s16 func_800CD20C(void) // 0x800CD20C
{
    s32      i;
    GsDOBJ2* itemModel;

    if (D_800F159C == 1)
    {
        if (g_SysWork.sysStateStep_C[0] == 5)
        {
            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickDown)
            {
                D_800ED5C8 += 3;
                Sd_PlaySfx(Sfx_MenuMove, 0, 0x40);
            }

            if (g_Controller0->btnsPulsed_18 & ControllerFlag_LStickUp)
            {
                D_800ED5C8 += 1;
                Sd_PlaySfx(Sfx_MenuMove, 0, 0x40);
            }

            D_800ED5C8 &= 0x3;

            if (g_Controller0->btnsHeld_C & ControllerFlag_LStickLeft)
            {
                Sd_PlaySfx(Sfx_Unk1589, 0, 0x40);

                D_800F1598[D_800ED5C8]++;
                if (D_800F1598[D_800ED5C8] == 8)
                {
                    D_800F1598[D_800ED5C8] = 0;
                }
            }

            if (g_Controller0->btnsHeld_C & ControllerFlag_LStickRight)
            {
                Sd_PlaySfx(Sfx_Unk1589, 0, 0x40);

                D_800F1598[D_800ED5C8]--;
                if (D_800F1598[D_800ED5C8] == -1)
                {
                    D_800F1598[D_800ED5C8] = 7;
                }
            }
        }
    }

    D_800F15A0 = D_800F1598[0] + (D_800F1598[1] * 10) + (D_800F1598[2] * 100) + (D_800F1598[3] * 1000);

    func_800CE180();

    func_800CD51C(D_800F15A0, D_800ED5C8);
    PushMatrix();
    func_8004BBF4(&D_800F1570, &D_800F1510, &D_800F1560);

    for (itemModel = g_Items_ItemsModelData, i = 0; i < 6; i++, itemModel++)
    {
        g_Items_Transforms[i].rotate.vx = Q12_ANGLE(90.0f);
        g_Items_Transforms[i].rotate.vz = Q12_ANGLE(0.0f);

        ItemScreen_ItemRotate(&g_Items_Coords[i].param->rotate, &g_Items_Coords[i]);

        if (D_800F159C != 0)
        {
            func_800CDB14(i, D_800ED5C8);
        }

        GsSetFlatLight(0, &D_800F1450[i][0]);
        func_8004BD74(i, itemModel, 0);
    }

    PopMatrix();
    func_800CDB98();

    if (D_800F159C == 1)
    {
        return D_800F15A0;
    }
    else
    {
        return 0;
    }
}

void func_800CD51C(s32 arg0, s32 arg1) // 0x800CD51C
{
    s32 temp_v0;
    s32 i;
    s32 var_t1;
    s32 var_v0_2;
    s32 var_v0_3;
    s8  temp_v1_2;

    var_t1 = 0;

    switch (D_800F159C)
    {
        case 0:
            for (i = 0; i < 6; i++)
            {
                g_Items_Transforms[i].scale.vx =
                g_Items_Transforms[i].scale.vy =
                g_Items_Transforms[i].scale.vz = Q12(2.0f);

                temp_v0 = (D_800F159D * 0xFF) / 32;

                D_800F1450[i][1].b = temp_v0;
                D_800F1450[i][1].g = temp_v0;
                D_800F1450[i][1].r = temp_v0;
                D_800F1450[i][0].b = temp_v0;
                D_800F1450[i][0].g = temp_v0;
                D_800F1450[i][0].r = temp_v0;
            }

            D_800F159D++;

            if (D_800F159D >= 32)
            {
                D_800F159C = 1;
                D_800F159D = 0;
            }
            break;

        case 1:
            if (D_800F1590 != arg0)
            {
                D_800F159C = 2;
            }

            for (i = 0; i < 6; i++)
            {
                switch (i)
                {
                    case 0:
                        g_Items_Coords[i].coord.t[0] = Q8(0.0f);
                        g_Items_Coords[i].coord.t[1] = Q8(-0.204f);
                        g_Items_Coords[i].coord.t[2] = Q8(-32.5f);
                        break;

                    case 5:
                        g_Items_Coords[i].coord.t[0] = Q8(0.0f);
                        g_Items_Coords[i].coord.t[1] = Q8(-0.08f);
                        g_Items_Coords[i].coord.t[2] = Q8(-32.5f);
                        break;

                    default:
                        g_Items_Coords[i].coord.t[0] = Q8(0.0f);
                        g_Items_Coords[i].coord.t[1] = Q8(1.555f) - (i * Q8(0.415f));
                        g_Items_Coords[i].coord.t[2] = Q8(-32.5f);
                        break;
                }
            }
            break;

        case 2:
            D_800F159D++;

            if ((D_800F1594[arg1] < D_800F1598[arg1] && (D_800F1594[arg1] != 0 || D_800F1598[arg1] != 7)) ||
                (D_800F1594[arg1] == 7 && D_800F1598[arg1] == 0))
            {
                var_t1 = 1;
            }
            else
            {
                var_t1 = -1;
            }

            if (D_800F159D >= 16)
            {
                D_800F159C = 1;
                D_800F159D = 0;
                D_800F1590 = arg0;

                for (i = 0; i < 4; i++)
                {
                    D_800F1594[i] = D_800F1598[i];
                }

                var_t1 = 0;
            }
            break;
    }

    var_v0_2 = var_t1 * (D_800F159D << 9);

    g_Items_Transforms[0].rotate.vy = Q12_ANGLE(292.5f);
    g_Items_Transforms[5].rotate.vy = Q12_ANGLE(292.5f);

    for (i = 1; i < 5; i++)
    {
        temp_v1_2 = D_800F1594[i - 1];
        if (temp_v1_2 == D_800F1598[i - 1])
        {
            var_v0_3 = temp_v1_2 << 9;
        }
        else
        {
            var_v0_3 = (temp_v1_2 << 9) + (var_v0_2 / 16);
        }

        g_Items_Transforms[i].rotate.vy = var_v0_3 + Q12_ANGLE(247.5f);
    }
}

void func_800CD818(void) // 0x800CD818
{
    Fs_QueueStartReadTim(FILE_ITEM_FOOK_TIM, FS_BUFFER_1, &D_800A907C);
    Fs_QueueStartRead(FILE_ITEM_FOOK_TMD, FS_BUFFER_21);
    Fs_QueueWaitForEmpty();
}

void func_800CD860(void) // 0x800CD860
{
    GsCOORD2PARAM* var_v1;
    GsCOORDINATE2* var_s1_2;
    s32            i;
    s16            temp_a0;
    s16            var_s1;

    var_s1                 = D_800F15A0;
    g_Items_DisplayedCount = 0;

    D_800F159C = 0;
    D_800F159D = 0;
    D_800ED5C8 = 3;

    ItemScreen_CamSet(&D_800F1570, &D_800F1510, (SVECTOR3*)&D_800F1560, 0);

    for (i = 0; i < 6; i++)
    {
        g_Items_Transforms[i].rotate.vz = 0;
        g_Items_Transforms[i].rotate.vx = 0;
        g_Items_Transforms[i].trans.vz  = 0;
        g_Items_Transforms[i].trans.vy  = 0;
        g_Items_Transforms[i].trans.vx  = 0;

        switch (i)
        {
            case 0:
            case 5:
                g_Items_Transforms[i].rotate.vy = 0x500;
                break;

            default:
                D_800F1594[i] = temp_a0         = var_s1 % 10;
                var_s1                          = var_s1 / 10;
                g_Items_Transforms[i].rotate.vy = (temp_a0 << 9) + 0xB00;
                break;
        }

        g_Items_Transforms[0].rotate.vy = 0xD00;
        g_Items_Transforms[5].rotate.vy = 0xD00;

        for (i = 1; i < 5; i++)
        {
            g_Items_Transforms[i].rotate.vy = (D_800F1598[i - 1] << 9) + 0xB00;
        }
    }

    GameFs_TmdDataAlloc((s32*)FS_BUFFER_21);

    for (i = 0; i < 6; i++)
    {
        Gfx_Items_Display((s_TmdFile*)FS_BUFFER_21, i, i);
        func_8005487C(i);

        switch (i)
        {
            case 0:
                g_Items_Coords[i].coord.t[0] = 0;
                g_Items_Coords[i].coord.t[1] = -0x34;
                g_Items_Coords[i].coord.t[2] = -0x2080;
                break;

            case 5:
                g_Items_Coords[i].coord.t[0] = 0;
                g_Items_Coords[i].coord.t[1] = -0x14;
                g_Items_Coords[i].coord.t[2] = -0x2080;
                break;

            default:
                g_Items_Coords[i].coord.t[0] = 0;
                g_Items_Coords[i].coord.t[1] = 0x18E - 0x6A * i;
                g_Items_Coords[i].coord.t[2] = -0x2080;
                break;
        }
    }

    func_800CDA8C();
}

void func_800CDA8C(void) // 0x800CDA8C
{
    s32 i;

    for (i = 0; i < 6; i++)
    {
        D_800F1450[i][0].vx = g_Items_Coords[i].coord.t[0];
        D_800F1450[i][0].vy = g_Items_Coords[i].coord.t[1];
        D_800F1450[i][0].vz = g_Items_Coords[i].coord.t[2] + 0x4E20;

        D_800F1450[i][1].vx = 0x1000;
        D_800F1450[i][1].vy = 0;
        D_800F1450[i][1].vz = 0;
    }

    GsSetAmbient(0x100, 0x100, 0x100);
    GsSetLightMode(1);
}

void func_800CDB14(s32 arg0, s32 arg1) // 0x800CDB14
{
    s32 i;

    D_800F1450[arg0][0].vx = g_Items_Coords[arg0].coord.t[0];
    D_800F1450[arg0][0].vy = g_Items_Coords[arg0].coord.t[1];
    D_800F1450[arg0][0].vz = g_Items_Coords[arg0].coord.t[2] + 0x4E20;

    D_800F1450[arg0][1].vx = 0;
    D_800F1450[arg0][1].vy = 0;
    D_800F1450[arg0][1].vz = 0;

    for (i = 0; i < 2; i++)
    {
        D_800F1450[arg0][i].r = 0xFF;
        D_800F1450[arg0][i].g = 0xFF;
        D_800F1450[arg0][i].b = 0xFF;
    }
}

void func_800CDB98(void) // 0x800CDB98
{
    GsOT*    ot;
    s32      i;
    POLY_G3* poly_g3;
    POLY_G4* poly_g4;
    s32      temp_s5;
    s32      temp_s6;
    s32      temp_s7;

    ot = &g_OrderingTable2[g_ActiveBufferIdx];

    for (i = 0; i < 16; i++)
    {
        poly_g3 = GsOUT_PACKET_P;

        setPolyG3(poly_g3);
        setSemiTrans(poly_g3, 1);

        if (D_800F159C == 0)
        {
            setRGB0(poly_g3, D_800F159D * 4, D_800F159D * 4, D_800F159D * 0x70 / 32);
            setRGB1(poly_g3, D_800F159D * 0x62 / 32, D_800F159D * 0x62 / 32, D_800F159D * 0x54 / 32);
            setRGB2(poly_g3, D_800F159D * 0x62 / 32, D_800F159D * 0x62 / 32, D_800F159D * 0x54 / 32);
        }
        else
        {
            setRGB0(poly_g3, 0x80, 0x80, 0x70);
            setRGB1(poly_g3, 0x62, 0x62, 0x54);
            setRGB2(poly_g3, 0x62, 0x62, 0x54);
        }

        temp_s5 = 0x5A;

        setXY0Fast(poly_g3, 0, 0);
        setXY1Fast(poly_g3, Q12_MULT(Math_Sin(i << 8), temp_s5), Q12_MULT(Math_Cos(i << 8), temp_s5));
        setXY2Fast(poly_g3, Q12_MULT(Math_Sin((i + 1) << 8), temp_s5), Q12_MULT(Math_Cos((i + 1) << 8), temp_s5));

        addPrim(&ot->org[10], poly_g3);
        GsOUT_PACKET_P = poly_g3 + 1;
    }

    for (i = 0; i < 16; i++)
    {
        poly_g4 = GsOUT_PACKET_P;

        setPolyG4(poly_g4);
        setSemiTrans(poly_g4, 1);

        if (D_800F159C == 0)
        {
            setRGB0(poly_g4, D_800F159D * 3, D_800F159D * 3, D_800F159D * 0x54 / 32);
            setRGB1(poly_g4, D_800F159D * 3, D_800F159D * 3, D_800F159D * 0x54 / 32);
        }
        else
        {
            setRGB0(poly_g4, 0x60, 0x60, 0x54);
            setRGB1(poly_g4, 0x60, 0x60, 0x54);
        }

        setRGB2(poly_g4, 0, 0, 0);
        setRGB3(poly_g4, 0, 0, 0);

        temp_s7 = 0x5A;
        temp_s6 = 0xB4;

        setXY0Fast(poly_g4, Q12_MULT(Math_Sin(i << 8), temp_s7), Q12_MULT(Math_Cos(i << 8), temp_s7));
        setXY1Fast(poly_g4, Q12_MULT(Math_Sin((i + 1) << 8), temp_s7), Q12_MULT(Math_Cos((i + 1) << 8), temp_s7));
        setXY2Fast(poly_g4, Q12_MULT(Math_Sin(i << 8), temp_s6), Q12_MULT(Math_Cos(i << 8), temp_s6));
        setXY3Fast(poly_g4, Q12_MULT(Math_Sin((i + 1) << 8), temp_s6), Q12_MULT(Math_Cos((i + 1) << 8), temp_s6));

        addPrim(&ot->org[10], poly_g4);
        GsOUT_PACKET_P = poly_g4 + 1;
    }

    Gfx_Primitive2dTextureSet(0, 0, 0xA, 1);
}

void func_800CE180(void) // 0x800CE180
{
    GsOT*    ot;
    s32      i;
    POLY_G3* poly_g3;

    ot = &g_OrderingTable2[g_ActiveBufferIdx];

    for (i = 0; i < 2; i++)
    {
        poly_g3 = GsOUT_PACKET_P;

        setPolyG3(poly_g3);
        setSemiTrans(poly_g3, 1);

        setRGB0(poly_g3, 0xC0, 0x80, 0);
        setRGB1(poly_g3, 0xC0, 0x80, 0);
        setRGB2(poly_g3, 0xFF, 0x40, 0);

        setXY0Fast(poly_g3, -0x30 + 0x60 * i, (0x1D - D_800ED5C8 * 0x14));
        setXY1Fast(poly_g3, -0x30 + 0x60 * i, (0x2D - D_800ED5C8 * 0x14));
        setXY2Fast(poly_g3, -0x40 + 0x80 * i, (0x25 - D_800ED5C8 * 0x14));

        addPrim(&ot->org[9], poly_g3);

        GsOUT_PACKET_P = poly_g3 + 1;
    }
}

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", D_800CA7F0);

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", D_800CA7F4);

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", D_800CA800);

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", D_800CA818);

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", D_800CA830);

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", D_800CA848);

INCLUDE_RODATA("maps/map5_s01/nonmatchings/map5_s01", sharedData_800CAA98_0_s01);

// TODO: Move this line into separate `Chara_AirScreamer` split.
#include "../src/maps/characters/air_screamer.c" // 0x800D225C

// TODO: Move this line into separate `Chara_Groaner` split.
#include "../src/maps/characters/groaner.c" // 0x800E3294

// TODO: Move this line into separate `Chara_Romper` split.
#include "../src/maps/characters/romper.c" // 0x800E786C

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800EB460

#include "maps/shared/Map_RoomIdxGet.h" // 0x800EB470

void func_800EB6B0(void) // 0x800EB6B0
{
    s32    temp_v0;
    q19_12 posX;
    q19_12 posZ;
    q19_12 newPosComp;
    s32    var_v1;
    s32    temp_s1;

    posX  = g_SysWork.playerWork_4C.player_0.position_18.vx;
    posZ  = g_SysWork.playerWork_4C.player_0.position_18.vz;
    temp_s1 = D_800EFC80[g_SavegamePtr->mapRoomIdx_A5];

    if (g_SavegamePtr->mapRoomIdx_A5 == 10)
    {
        posX += Q12(150.0f);
        posZ  = Q12(-25.0f) - posZ;
        if (posX < posZ)
        {
            newPosComp = posX;
        }
        else
        {
            newPosComp = posZ;
        }

        newPosComp /= 2;
    }
    else
    {
        if (posZ > Q12(-120.0f))
        {
            posX = posX - Q12(16.0f);
            posZ = Q12(-48.0f) - posZ;
            if (posX < posZ)
            {
                newPosComp = posX;
            }
            else
            {
                newPosComp = posZ;
            }
        }
        else
        {
            if (posX > Q12(0.0f))
            {
                posX = posX - Q12(16.0f);
            }
            else
            {
                posX = Q12(-52.0f) - posX;
            }

            posZ = Q12(-144.0f) - posZ;

            if (posZ < posX)
            {
                newPosComp = posX;
            }
            else
            {
                newPosComp = posZ;
            }
        }
    }

    D_800EFC7C += g_DeltaTime;
    if (newPosComp < Q12(0.0f))
    {
        newPosComp = Q12(0.0f);
    }
    else if (newPosComp >= Q12(32.0f))
    {
        newPosComp = Q12(32.0f) - 1;
    }

    temp_v0 = (Math_Sin(D_800EFC7C / 12) + Q12(2.0f)) / 2;
    var_v1  = Q12_MULT_PRECISE(newPosComp, temp_v0);

    D_800EFC74.field_0[4] = var_v1 / Q12(0.5f);
    Bgm_Update(temp_s1, Q12(0.2f), &D_800EFC74);
}

void Gfx_LoadingScreen_StageString(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800EB87C

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800EB910

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~H\tThere_is_a_ ~C5 Resort_area_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tNothing_unusual. ~E ",
    "\tUsed_the_ ~C2 Kaufmann_key ~C7 . ~E ",
    "~J0(1.0)\tWhat? ~E ",
    "~J0(2.5)\tThat_light!? ~E "
};

void MapEvent_CommonItemTake(void) // 0x800EB9A4
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 40:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M5S01_RifleShells0;
            break;

        case 41:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M5S01_HandgunBullets;
            break;

        case 42:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M5S01_FirstAidKit;
            break;

        case 43:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M5S01_HealthDrink;
            break;

        case 44:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M5S01_RifleShells1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800EBA40(void) // 0x800EBA40
{
    s32 i;
    s32 j;

    Game_RadioSoundStop();

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
            D_800F0358 = 0;
            D_800F0354 = 0;

            for (i = 0; i < ARRAY_SIZE(D_800F0350); i++)
            {
                D_800F0350[i] = 10;
            }

            SysWork_StateStepIncrement(0);

        case 1:
            func_800862F8(7, FILE_TIM_DORPANEL_TIM, false);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);
            break;

        case 4:
            Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);

            D_800F0354 += (g_Controller0->sticks_24.sticks_0.leftX * 16384) / 75;
            D_800F0354  = CLAMP_RANGE(D_800F0354, Q12(-160.0f), Q12(160.0f));

            D_800F0358 += (g_Controller0->sticks_24.sticks_0.leftY * 16384) / 75;
            D_800F0358  = CLAMP_RANGE(D_800F0358, Q12(-120.0f), Q12(120.0f));

            Game_TimerUpdate();
            Gfx_CursorDraw((s16)(FP_FROM(D_800F0354, Q12_SHIFT) + 8), FP_FROM(D_800F0358, Q12_SHIFT) + 8, 8, 8, 0, 64, 32, 32, 128, 192, 0, 12);

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                SysWork_StateStepSet(0, 7);
                break;
            }

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                for (i = 0; i < ARRAY_SIZE(D_800F0158); i++)
                {
                    if ((D_800F0158[i].field_0 - 160) > FP_FROM(D_800F0354, Q12_SHIFT) ||
                        (D_800F0158[i].field_0 - 114) < FP_FROM(D_800F0354, Q12_SHIFT))
                    {
                        continue;
                    }

                    if ((D_800F0158[i].field_1 - 120) > FP_FROM(D_800F0358, Q12_SHIFT) ||
                        (D_800F0158[i].field_1 - 74) < FP_FROM(D_800F0358, Q12_SHIFT))
                    {
                        continue;
                    }

                    Sd_PlaySfx(Sfx_Unk1586, 0, Q8_CLAMPED(0.5f));

                    if (i < 11)
                    {
                        for (j = 0; j < (ARRAY_SIZE(D_800F0350) - 1); j++)
                        {
                            D_800F0350[j] = D_800F0350[j + 1];
                        }

                        D_800F0350[3] = i;
                        break;
                    }

                    for (j = 0; j < ARRAY_SIZE(D_800F0350); j++)
                    {
                        if (D_800F0170[j] != D_800F0350[j])
                        {
                            break;
                        }
                    }

                    if (j == 4)
                    {
                        Savegame_EventFlagSet(EventFlag_387);
                        SysWork_StateStepIncrement(0);
                    }
                    else
                    {
                        for (j = 0; j < ARRAY_SIZE(D_800F0350); j++)
                        {
                            D_800F0350[j] = 10;
                        }
                    }
                    break;
                }
            }
            break;

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);
            break;

        case 6:
            Sd_PlaySfx(Sfx_Unk1587, 0, Q8_CLAMPED(0.5f));
            SysWork_StateStepIncrement(0);

        case 7:
            Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            func_80037154();
            break;
    }
}

void MapEvent_MapTake(void) // 0x800EBF48
{
    Event_MapTake(4, EventFlag_M5S01_PickupMap, 15);
}

void func_800EBF70(void) // 0x800EBF70
{
    VECTOR3 camPos;    // Q19.12
    VECTOR3 canLookAt; // Q19.12
    s16     temp_v0;
    s16     temp;

    temp = 0x1D9;

    if (g_SysWork.sysStateStep_C[0] > 2)
    {
        Game_RadioSoundStop();
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800CD818();

            g_SysWork.field_30 = 20;

            SysWork_StateStepIncrementAfterFade(0, true, 2, 0, false);

            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(52.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(-57.8f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(107.6f);

            camPos.vx = Q12(49.8f);
            camPos.vy = Q12(-1.5f);
            camPos.vz = Q12(-60.0f);

            canLookAt.vx = Q12(52.5f);
            canLookAt.vy = Q12(-1.3f);
            canLookAt.vz = Q12(-57.9f);

            Camera_PositionSet(&camPos, 0, 0, 0, 0, 0, 0, 0, true);
            Camera_LookAtSet(&canLookAt, 0, 0, 0, 0, 0, 0, 0, true);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 3:
            if (Fs_QueueDoThingWhenEmpty())
            {
                g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;

                func_800CD860();
                SysWork_StateStepIncrement(0);
            }

        case 4:
            g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 5:
            Game_TimerUpdate();
            g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;

            temp_v0 = func_800CD20C();
            if (!(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                if (temp != temp_v0)
                {
                    break;
                }

                Savegame_EventFlagSet(EventFlag_371);
                Sd_PlaySfx(Sfx_Unk1588, 0, Q8(0.5f));
            }

            SysWork_StateStepIncrement(0);
            break;

        case 6:
            g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;

            func_800CD20C();
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 7:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);

        default:
            // Return to gameplay.
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            vcReturnPreAutoCamWork(true);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            func_80037154();
            break;
    }
}

void func_800EC2D8(void) // 0x800EC2D8
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_KaufmannKey, 1);
    Map_MessageWithSfx(17, Sfx_UseKey, &sfxPos); // "Used the Kaufmann key."
    Savegame_EventFlagSet(EventFlag_M5S01_KaufmannKeyUsed);
}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800EC394

void func_800EC42C(void) // 0x800EC42C
{
    s32    mulZ;
    s32    mulX;
    s32    pitch;
    s32    tmp0;
    s32    tmp1;
    q19_12 sin0;
    q19_12 sin1;

    tmp0 = D_800F0360;
    sin0 = Math_Sin(tmp0 >> 2);
    sin1 = Math_Sin(tmp0 >> 3);
    tmp1 = ((sin0 * 2) + sin1) + Math_Sin(Math_Cos(tmp0 >> 4));
    pitch = tmp1 >> 8;
    D_800F0360 += g_DeltaTime;

    if (g_SysWork.sysStateStep_C[0] >= 10)
    {
        D_800F035E -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.5f));
        if (D_800F035E < 0)
        {
            D_800F035E = 0;
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, ~(D_800F035E >> 4), pitch);
    }
    else if (g_SysWork.sysStateStep_C[0] > 0)
    {
        D_800F035E += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.25f));
        if (D_800F035E > Q12(0.9961f))
        {
            D_800F035E = Q12(0.9961f);
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, ~(D_800F035E >> 4), pitch);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            Fs_QueueStartReadTim(FILE_TIM_ENBAN_TIM, FS_BUFFER_1, &D_800F0178);
            Fs_QueueStartRead(FILE_ANIM_UFO3_DMS, FS_BUFFER_13);

            D_800F3E0C = NO_VALUE;

            ScreenFade_ResetTimestep();
            SD_Call(Sfx_Unk1467);
            Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, Q8_CLAMPED(1.0f), 0);

            D_800F035E = 0;
            D_800F0360 = 0;
            D_800F035D = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            if (Fs_QueueDoThingWhenEmpty() != false)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 3:
            D_800F3E0C = 0;

            SysWork_StateStepIncrementAfterFade(0, true, 3, 0, false);
            DmsHeader_FixOffsets((s_DmsHeader* )FS_BUFFER_13);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            Game_TurnFlashlightOn();

            D_800F035C = 0;

            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 5:
            Map_MessageWithAudio(18, &D_800F035C, &D_800F0174);
            break;

        case 6:
            SysWork_StateStepIncrementAfterTime(&D_800F3E0C, Q12(40.0f), Q12(0.0f), Q12(30.0f), true, true);
    block_18:
            sharedFunc_800CE5D4_1_s03(&D_800F0180, Q12(0.5f), Q12(0.05f), 0);
            break;

        case 7:
            MapMsg_DisplayAndHandleSelection(false, 19, 0, 0, 0, false);
            sharedFunc_800CE5D4_1_s03(&D_800F0180, Q12(0.5f), Q12(0.05f), 0);
            break;

        case 8:
            func_80080B58(&g_SysWork.playerBoneCoords_890[2], &(SVECTOR3){ 0, 0, 0 }, &QVECTOR3(-196.53f, -14.25f, -9.73f));
            sharedFunc_800CE5D4_1_s03(&D_800F0180, Q12(1.0f), Q12(0.1f), 1);
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 9:
            g_SysWork.field_28 += g_DeltaTime;

            switch (g_SysWork.field_28 / Q12(0.1f))
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    mulZ = Q12(0.0f);
                    mulX = Q12(0.0f);
                    break;

                case 4:
                case 5:
                case 6:
                case 11:
                case 12:
                case 13:
                case 18:
                case 19:
                case 20:
                    mulX = Q12(-0.9f);
                    mulZ = Q12(1.0f);
                    break;

                case 7:
                case 8:
                case 9:
                case 10:
                case 14:
                case 15:
                case 16:
                case 17:
                case 21:
                case 22:
                case 23:
                case 24:
                    mulX = Q12(1.2f);
                    mulZ = Q12(1.0f);
                    break;

                case 25:
                    if (D_800F035D == 0)
                    {
                        D_800F0180.vy = Q12(-13.0f);
                        D_800F0180.vz = Q12(2.5f);
                        D_800F035D++;
                    }

                case 26:
                case 27:
                case 31:
                case 32:
                case 33:
                case 37:
                case 38:
                case 39:
                case 43:
                case 44:
                case 45:
                    mulX = Q12(-1.2f);
                    mulZ = Q12(-1.2f);
                    break;

                case 28:
                case 29:
                case 30:
                case 34:
                case 35:
                case 36:
                case 40:
                case 41:
                case 42:
                    mulX = Q12(1.2f);
                    mulZ = Q12(-1.2f);
                    break;

                case 46:
                    if (D_800F035D == 1)
                    {
                        D_800F0180.vy = Q12(-15.75f);
                        D_800F0180.vz = Q12(-12.25f);
                        D_800F035D++;
                    }

                case 59:
                    mulX = Q12(0.0f);
                    mulZ = Q12(-1.6f);
                    break;

                case 47:
                case 48:
                case 49:
                case 56:
                case 57:
                case 58:
                    mulX = Q12(0.6f);
                    mulZ = Q12(-1.6f);
                    break;

                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    mulX = Q12(-0.6f);
                    mulZ = Q12(-1.6f);
                    break;

                default:
                    mulZ = Q12(0.0f);
                    mulX = Q12(0.0f);
                    SysWork_StateStepIncrement(0);
                    break;
            }

            D_800F0180.vy += Q12_MULT_PRECISE(g_DeltaTime, mulX * 4);
            D_800F0180.vz += Q12_MULT_PRECISE(g_DeltaTime, mulZ * 4);

            sharedFunc_800CE5D4_1_s03(&D_800F0180, Q12(0.5f), Q12(0.05f), 0);
            break;

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);

            vcReturnPreAutoCamWork(true);
            Savegame_EventFlagSet(EventFlag_458);
            func_80086470(3, InventoryItemId_ChannelingStone, 1, false);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();

            D_800F3E0C = NO_VALUE;

            Sd_SfxStop(Sfx_Unk1467);
            break;
    }

    if (D_800F3E0C >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800F3E0C, (s_DmsHeader*)FS_BUFFER_13);

        g_SysWork.playerWork_4C.player_0.position_18.vx -= Q12(20.0f);

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800F3DF0, &D_800F3E00, NULL, D_800F3E0C, (s_DmsHeader*)FS_BUFFER_13));

        D_800F3DF0.vx -= Q12(20.0f);
        D_800F3E00.vx -= Q12(20.0f);

        vcUserCamTarget(&D_800F3DF0, NULL, true);
        vcUserWatchTarget(&D_800F3E00, NULL, true);
    }
}

void Map_WorldObjectsInit(void) // 0x800ECB58
{
    WorldObjectNoRotInit(&g_WorldObject0, "RSRMAP_H", -46.5f, 0.0f, 2.5f);

    WorldObjectInit(&g_WorldObject1, "FOOK_HID", 52.15f, -1.359f, -57.925f, 0.0f, 0.0f, 5.8f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        g_SysWork.npcId_2280 = 3;
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        g_SysWork.npcId_2280 = 4;
    }
    else
    {
        g_SysWork.npcId_2280 = 5;
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x800ECC8C
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if ((PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1)) ||
        (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0)))
    {
            if (!Savegame_EventFlagGet(EventFlag_M5S01_PickupMap))
            {
                WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &(SVECTOR3){ 0, 0, 0 });
            }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
            if (!Savegame_EventFlagGet(EventFlag_371))
            {
                WorldGfx_ObjectAdd(&g_WorldObject1.object_0, &g_WorldObject1.position_1C, &g_WorldObject1.rotation_28);
            }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_RifleShells0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_HandgunBullets))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_FirstAidKit))
        {
            WorldGfx_ObjectAdd(g_CommonWorldObjects, &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -5, -1, -5))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_HealthDrink))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[3].position_0, &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -5, -1, -5))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_RifleShells1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &g_CommonWorldObjectPoses[4].position_0, &g_CommonWorldObjectPoses[4].rotation_C);
        }
    }
}
