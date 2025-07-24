#include "game.h"
#include "inline_no_dmpsx.h"
#include "gtemac.h"
#include "libgs.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/credits.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math.h"

void func_8004BB4C(VbRVIEW* view, GsCOORDINATE2* coord, SVECTOR3* vec, s32 arg3) // 0x8004BB4C
{
    view->vr.vz = 10;
    view->vp.vx = 0;
    view->vp.vy = 0;
    view->vp.vz = 0;
    view->vr.vx = 0;
    view->vr.vy = 0;

    view->rz = 0;

    view->super       = coord;
    coord->coord.t[2] = -0x2800;
    coord->super      = NULL;
    coord->coord.t[0] = 0;
    coord->coord.t[1] = 0;

    vec->vx = 0;
    vec->vy = 0;
    vec->vz = 0;

    D_800C3928.scale.vz  = FP_ALPHA(1.0f);
    D_800C3928.scale.vy  = FP_ALPHA(1.0f);
    D_800C3928.scale.vx  = FP_ALPHA(1.0f);
    D_800C3928.rotate.vz = 0;
    D_800C3928.rotate.vy = 0;
    D_800C3928.rotate.vx = 0;
    D_800C3928.trans.vz  = 0;
    D_800C3928.trans.vy  = 0;
    D_800C3928.trans.vx  = 0;

    coord->param = &D_800C3928;

    Gfx_Results_ItemsRotate((SVECTOR*)vec, coord);
    vbSetRefView(view);
}

void func_8004BBF4(VbRVIEW* arg0, GsCOORDINATE2* arg1, SVECTOR* arg2) // 0x8004BBF4
{
    u16     vx;
    VECTOR  vec;
    SVECTOR sVec;

    vx  = arg2->vx;
    arg2->vx = 0;

    Gfx_Results_ItemsRotate(arg2, arg1);

    arg2->vx = vx;

    Gfx_Results_ItemsRotate(arg2, arg1);

    sVec.vx = 0;
    sVec.vy = 0;
    sVec.vz = 0;

    gte_ApplyMatrix(&arg1->coord, &sVec, &vec);
    vbSetRefView(arg0);
}

void func_8004BCBC(s32* buf) // 0x8004BCBC
{
    GsMapModelingData((unsigned long*)&buf[1]);
}

void Gfx_Results_ItemsRotate(SVECTOR* arg0, GsCOORDINATE2* arg1) // 0x8004BCDC
{
    MATRIX mat;

    mat.t[0] = arg1->coord.t[0];
    mat.t[1] = arg1->coord.t[1];
    mat.t[2] = arg1->coord.t[2];

    func_80096E78(arg0, &mat);

    arg1->coord = mat;

    ScaleMatrix(&arg1->coord, &arg1->param->scale);

    arg1->flg = 0;
}

/** Used for displaying model items. */
void func_8004BD74(s32 arg0, GsDOBJ2* arg1, s32 arg2)  // 0x8004BD74
{
    MATRIX sp10;
    MATRIX sp30;
    MATRIX sp50;
    s32 j;
    s32 i;

    func_80049B6C(arg1->coord2, &sp50, &sp10);

    sp30 = sp10;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            sp10.m[i][j] = FP_TO(sp10.m[i][j], Q12_SHIFT) / g_Items_Items3dData0[arg0].scale_0.vx;
        }
    }

    if (arg2 != 3 && arg0 < 7)
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                sp10.m[i][j] -= FP_MULTIPLY(sp10.m[i][j], shRsin((g_Items_Items3dData1[arg0].coord.t[2] + 0x400) >> 2), Q12_SHIFT);
            }
        }
    }

    GsSetLightMatrix(&sp10);
    GsSetLsMatrix(&sp30);

    if (arg2 == 2)
    {
        GsClearOt(0, 0, &D_800A8F9C[g_ObjectTableIdx]);
        GsSortOt(&D_800A8F9C[g_ObjectTableIdx], &g_ObjectTable0[g_ObjectTableIdx]);
        GsSortObject4J(arg1, &D_800A8F9C[g_ObjectTableIdx], 1, (u32*)PSX_SCRATCH);
    }
    else
    {
        GsSortObject4J(arg1, &g_ObjectTable0[g_ObjectTableIdx], 1, (u32*)PSX_SCRATCH);
    }
}

void func_8004BFE8() // 0x8004BFE8
{
    PushMatrix();
    D_800C3954 = ReadGeomScreen();
    ReadGeomOffset(&D_800C3958, &D_800C395C);
    GsSetProjection(0x3E8);
    D_800C3950 = g_SysWork.playerCombatInfo_38.field_F;
}

void func_8004C040() // 0x8004C040
{
    PopMatrix();
    GsSetProjection(D_800C3954);
    SetGeomOffset(D_800C3958, D_800C395C);
}

void Inventory_ExitAnimEquippedItemUpdate(u8* arg0) // 0x8004C088
{
    s8       temp_v0;
    s32      temp;
    s_Model* modelPtr3;
    s_Model* extraModelPtr2;
    s_Model* extraModelPtr0;
    s_Model* extraModelPtr1;
    s_Model* modelPtr0;
    s_Model* modelPtr1;

    func_8007F1CC();

    temp = g_SysWork.player_4C.extra_128.field_1C;

    if (g_SysWork.player_4C.extra_128.field_1C < 2 && temp >= 0)
    {
        if (D_800C3950 != g_SysWork.playerCombatInfo_38.field_F)
        {
            g_SysWork.playerCombatInfo_38.isAiming_13 = 0;
        }

        temp_v0 = D_800C3950 % 10;

        if (temp_v0 == 5 && g_SysWork.playerCombatInfo_38.field_F != temp_v0)
        {
            goto Inventory_ExitAnimEquippedItemUpdate_block; // TODO: Remove goto if possible.
        }

        if (temp_v0 == 2 && g_SysWork.playerCombatInfo_38.field_F != temp_v0)
        {
        Inventory_ExitAnimEquippedItemUpdate_block:
            g_SysWork.player_4C.chara_0.field_44                       = 0;
            g_SysWork.player_4C.chara_0.properties_E4.player.field_114 = 0;
        }

        switch (g_SysWork.player_4C.extra_128.field_24)
        {
            case 9:
            case 10:
            case 11:
            case 29:
            case 30:
                break;

            default:

                if (g_SysWork.player_4C.extra_128.field_1C == 1 && (s8)D_800C3950 != g_SysWork.playerCombatInfo_38.field_F)
                {
                    g_SysWork.player_4C.extra_128.field_1C                     = 0;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C = 0;
                }

                if (g_SysWork.player_4C.extra_128.field_24 >= 20 && g_SysWork.playerCombatInfo_38.field_F != NO_VALUE &&
                    (s8)D_800C3950 == g_SysWork.playerCombatInfo_38.field_F)
                {
                    extraModelPtr0 = &g_SysWork.player_4C.extra_128.model_0;
                    if (extraModelPtr0->anim_4.animIdx_0 >= 66u)
                    {
                        modelPtr0                                         = &g_SysWork.player_4C.chara_0.model_0;
                        extraModelPtr0->anim_4.animIdx_0                 -= 10;
                        g_SysWork.player_4C.chara_0.model_0.state_2       = 0;
                        g_SysWork.player_4C.chara_0.model_0.stateStep_3   = 0;
                        g_SysWork.player_4C.extra_128.model_0.state_2     = 0;
                        g_SysWork.player_4C.extra_128.model_0.stateStep_3 = 0;
                        modelPtr0->anim_4.animIdx_0                      -= 10;
                    }
                }
                else
                {
                    modelPtr1      = &g_SysWork.player_4C.chara_0.model_0;
                    extraModelPtr1 = &g_SysWork.player_4C.extra_128.model_0;

                    modelPtr1->anim_4.animIdx_0                       = 3;
                    modelPtr1->anim_4.keyframeIdx0_8                  = 0;
                    extraModelPtr1->anim_4.animIdx_0                  = 3;
                    extraModelPtr1->anim_4.keyframeIdx0_8             = 0;
                    g_SysWork.player_4C.chara_0.model_0.state_2       = 0;
                    g_SysWork.player_4C.chara_0.model_0.stateStep_3   = 0;
                    g_SysWork.player_4C.extra_128.field_20            = 0;
                    g_SysWork.player_4C.extra_128.field_24            = 0;
                    g_SysWork.player_4C.extra_128.model_0.state_2     = 0;
                    g_SysWork.player_4C.extra_128.model_0.stateStep_3 = 0;
                }

                g_SysWork.player_4C.chara_0.properties_E4.player.field_126        = 0;
                g_SysWork.player_4C.chara_0.properties_E4.player.properties_E4[1] = 0;
        }
    }

    modelPtr3      = &g_SysWork.player_4C.chara_0.model_0;
    extraModelPtr2 = &g_SysWork.player_4C.extra_128.model_0;

    modelPtr3->anim_4.keyframeIdx1_A       = FP_FLOAT_TO(1, Q12_SHIFT);
    extraModelPtr2->anim_4.keyframeIdx1_A  = FP_FLOAT_TO(1, Q12_SHIFT);
    g_SysWork.player_4C.extra_128.field_18 = 0x7FF;
    modelPtr3->anim_4.time_4               = FP_TO(modelPtr3->anim_4.keyframeIdx0_8, Q12_SHIFT);
    extraModelPtr2->anim_4.time_4          = FP_TO(extraModelPtr2->anim_4.keyframeIdx0_8, Q12_SHIFT);

    func_800446D8((s_Skeleton*)FS_BUFFER_0, g_SysWork.playerBoneCoords_890, modelPtr3->anim_4.keyframeIdx0_8, modelPtr3->anim_4.keyframeIdx0_8, FP_FLOAT_TO(1, Q12_SHIFT));

    g_SysWork.player_4C.extra_128.field_18 = 0x3F800;

    func_800446D8((s_Skeleton*)FS_BUFFER_0, g_SysWork.playerBoneCoords_890, extraModelPtr2->anim_4.keyframeIdx0_8, extraModelPtr2->anim_4.keyframeIdx0_8, FP_FLOAT_TO(1, Q12_SHIFT));
    func_8004C040();
}

s32 func_8004C328() // 0x8004C328
{
    u32 itemIdx;
    u8  itemId;
    u32 hasHuntingRifle;
    u32 hasShotgun;

    itemIdx         = 0;
    hasHuntingRifle = false;
    hasShotgun      = false;

    for (; (itemId = g_SavegamePtr->items_0[itemIdx].id_0) != 0; itemIdx++)
    {
        if (itemId == InventoryItemId_HuntingRifle)
        {
            hasHuntingRifle = true;
        }

        if (itemId == InventoryItemId_Shotgun)
        {
            hasShotgun = true;
        }

        if (g_SysWork.playerCombatInfo_38.field_12 != NO_VALUE && itemIdx == g_SysWork.playerCombatInfo_38.field_12)
        {
            if (itemId >= InventoryItemId_Handgun && itemId <= InventoryItemId_Shotgun)
            {
                if (g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10 != 0)
                {
                    return true;
                }
            }
            continue;
        }

        if (itemId == InventoryItemId_Handgun || itemId == InventoryItemId_HandgunBullets)
        {
            if (g_SavegamePtr->items_0[itemIdx].count_1 != 0)
            {
                return true;
            }
            continue;
        }

        switch (itemId)
        {
            case InventoryItemId_HuntingRifle:
            case InventoryItemId_Shotgun:
                // Loaded ammo?
                if (g_SavegamePtr->items_0[itemIdx].count_1 != 0)
                {
                    return true;
                }
                break;

            case InventoryItemId_RifleShells:
                if (hasHuntingRifle)
                {
                    if (g_SavegamePtr->items_0[itemIdx].count_1 != 0)
                    {
                        return true;
                    }
                }
                break;

            case InventoryItemId_ShotgunShells:
                if (hasShotgun)
                {
                    if (g_SavegamePtr->items_0[itemIdx].count_1 != 0)
                    {
                        return true;
                    }
                }
                break;
        }
    }

    return false;
}

s32 func_8004C45C() // 0x8004C45C
{
    s32 i;

    for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
    {
        // Already in inventory, can't add new one.
        if (g_SavegamePtr->items_0[i].id_0 == InventoryItemId_HyperBlaster)
        {
            return NO_VALUE;
        }
    }

    if (g_SavegamePtr->mapOverlayId_A4 > MapOverlayId_MAP0_S00)
    {
        // Konami gun controller connected.
        if (g_GameWork.controllers_38[1].analogController_0.status         == 0 &&
            g_GameWork.controllers_38[1].analogController_0.received_bytes == 1 &&
            g_GameWork.controllers_38[1].analogController_0.terminal_type  == PadTerminalType_GunControllerKonami)
        {
            return 1;
        }

        // Game completed with some condition met?
        if (g_SavegamePtr->clearGameCount_24A != 0 && (g_SavegamePtr->field_24B & (1 << 4)) != 0)
        {
            return 1;
        }
    }

    return 0;
}

s32 func_8004C4F8() // 0x8004C4F8
{
    if (g_SavegamePtr->mapOverlayId_A4 > MapOverlayId_MAP0_S00)
    {
        if ((g_SavegamePtr->field_24B & (1 << 4)) != 0)
        {
            // Game completed with some condition met?
            return 2;
        }

        // Returns 1 if controller port 2 has Konami gun controller connected.
        return g_GameWork.controllers_38[1].analogController_0.status         == 0 &&
               g_GameWork.controllers_38[1].analogController_0.received_bytes == 1 &&
               g_GameWork.controllers_38[1].analogController_0.terminal_type  == PadTerminalType_GunControllerKonami;
    }

    return 0;
}

u32 func_8004C54C() // 0x8004C54C
{
    return g_SavegamePtr->hyperBlasterFlags_25C_3 >> 3;
}

void func_8004C564(u8 arg0, s32 arg1) // 0x8004C564
{
    s32 temp_v1;
    s8  temp_a1;

    temp_a1 = arg1 + 1;
    switch (temp_a1)
    {
        case 0:
            D_800C3960 = g_SavegamePtr->mapOverlayId_A4;
            D_800C3962 = 0;
            D_800C3963 = 0;
            D_800C3961 = 32;

            func_8008B398();
            g_SysWork.player_4C.chara_0.properties_E4.player.field_114 = 0;
            break;

        case 1:
            D_800C3960 = g_SavegamePtr->mapOverlayId_A4;
            D_800C3962 = 0;
            D_800C3961 = 32;

            func_8008B438(arg0 != (1 << 1), 32, 0);
            func_8008B3E4(0);

            if (arg0 != (1 << 1))
            {
                D_800C3963 |= 1 << 0;
            }
            else
            {
                D_800C3963 |= 1 << 1;
            }
            break;

        case 2:
            if (arg0 == (1 << 1))
            {
                func_8008B40C((u8)D_800C3961, D_800C3962);
                D_800C3963 |= 1 << 2;
            }
            break;

        case 3:
            if (D_800C3961 != 0)
            {
                D_800C3961 -= ((g_DeltaTime0 / 68) == 0) ? 1 : (g_DeltaTime0 / 68);
                D_800C3962  = D_800C3961 - 32;
                D_800C3961  = CLAMP(D_800C3961, 0, 32);

                func_8008B438(arg0 != 2, 0, 0);
                func_8008B3E4(NO_VALUE);

                if (arg0 == 2)
                {
                    func_8008B40C((u8)D_800C3961, D_800C3962);
                }

                if (D_800C3961 == 0)
                {
                    func_8008B398();
                    D_800C3963                                                 = 0;
                    D_800C3962                                                 = 0;
                    g_SysWork.player_4C.chara_0.properties_E4.player.field_114 = 0;
                    g_SysWork.player_4C.chara_0.field_44                       = 0;
                }
            }
            break;

        case 4:
            if (D_800C3963 & (1 << 1))
            {
                if (!(D_800C3963 & (1 << 2)))
                {
                    func_8008B438(0, 0, 0);
                    func_8008B3E4(0);

                    g_SysWork.player_4C.chara_0.properties_E4.player.field_114 = 0;
                    D_800C3963                                                -= 2;
                }
            }
            break;

        case 5:
            if (g_SavegamePtr->mapOverlayId_A4 != D_800C3960)
            {
                D_800C3960 = g_SavegamePtr->mapOverlayId_A4;
                D_800C3963 = 0;
                D_800C3962 = 0;
                D_800C3961 = 32;

                temp_v1 = arg0;
                if (temp_v1 != (1 << 1))
                {
                    D_800C3963 = 1 << 0;
                }
                else
                {
                    D_800C3963 = temp_v1;
                }

                if (arg0 == (1 << 1))
                {
                    D_800C3963 |= 1 << 2;
                }
            }

            func_8008B438(arg0 != 2, (u8)D_800C3961, D_800C3962);

            if (arg0 == (1 << 1))
            {
                func_8008B40C((u8)D_800C3961, D_800C3962);
            }

            func_8008B3E4(NO_VALUE);
            break;
    }
}

static const s32 pad = 0; // Rodata padding.

static const s8 D_80025EB0[] =
{
    0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x4a, 0x16, 0x17, 0x18, 0x19, 0x20, 0x1f, 0x21,
    0x23, 0x26, 0x27, 0x28, 0x31, 0x32, 0x3f, 0x40,
    0x41, 0x42, 0x43, 0x14, 0x15, 0x1e, 0x00, 0x33,
    0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1a, 0x1b, 0x1c, 0x1d, 0x22, 0x24, 0x25, 0x2f,
    0x2e, 0x30, 0x2d, 0x29, 0x2a, 0x2b, 0x2c, 0x00,
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b,
    0x3c, 0x3d, 0x3e, 0x44, 0x45, 0x46, 0x47, 0x48,
    0x0a, 0x0b, 0x0f, 0x00, 0x0c, 0x0e, 0x10, 0x0d,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x07, 0x05, 0x09, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x11, 0x12, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
    0x00, 0x00, 0x00, 0x00
};

void func_8004C8DC() // 0x8004C8DC
{
    #define TIME_290_HOURS        FP_TO(290 * 60 * 60, Q12_SHIFT)
    #define TIME_130_HOURS        FP_TO(130 * 60 * 60, Q12_SHIFT)
    #define TIME_290_OVERFLOW_MAX 3                               // `add290Hours_25C_1` has max value of 3.

    g_SavegamePtr->gameplayTimer_250 += g_DeltaTime1;

    if (g_SavegamePtr->gameplayTimer_250 >= TIME_290_HOURS)
    {
        if (g_SavegamePtr->add290Hours_25C_1 < TIME_290_OVERFLOW_MAX)
        {
            g_SavegamePtr->add290Hours_25C_1++;
            g_SavegamePtr->gameplayTimer_250 += (UINT_MAX - TIME_290_HOURS + 1); // Wrap timer to 0 using unsigned overflow.
        }
        else
        {
            g_SavegamePtr->gameplayTimer_250 = TIME_290_HOURS - 1;
        }
    }

    if (g_SavegamePtr->add290Hours_25C_1 == TIME_290_OVERFLOW_MAX)
    {
        g_SavegamePtr->gameplayTimer_250 = CLAMP(g_SavegamePtr->gameplayTimer_250, 1, TIME_130_HOURS);
    }
}

void GameState_ItemScreens_Update() // 0x8004C9B0
{
    Gfx_StringSetColor(7);
    func_800363D0();

    if (g_GameWork.gameStateStep_598[1] < 21)
    {
        func_8004C8DC();
    }

    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            if (g_SavegamePtr->field_27A & 0x1F)
            {
                g_GameWork.gameStateStep_598[1] = 21;
                g_GameWork.gameStateStep_598[2] = 0;
                return;
            }

            if ((g_SavegamePtr->field_27A & (1 << 6)) &&
                g_GameWork.gameStatePrev_590 == 16)
            {
                g_Demo_ReproducedCount = 0;
                Game_WarmBoot();
                GameFs_StreamBinLoad();
                Fs_QueueWaitForEmpty();
                Game_StateSetNext(GameState_MovieIntro);
                return;
            }

            if (func_8004C45C() == 1)
            {
                func_80054CAC(InventoryItemId_HyperBlaster, 1);
            }

            Gfx_ClearRectInterlaced(0, 0x20, 0x140, 0x1C0, 0u, 0u, 0u);
            Gfx_Init(0x140, 1);

            g_IntervalVBlanks = 1;
            g_Gfx_ScreenFade  = 6;
            D_800B5C30        = 0x3000;

            func_80037188();

            D_800C3990                    = 1;
            g_Inventory_BorderSelectionId = 0;
            D_800AE178                    = 0;
            g_Inventory_CmdSelectedIdx    = 0;
            g_Inventory_SelectedItemIdx   = g_SysWork.inventoryItemSelectedIdx_2351;

            switch (g_GameWork.gameStatePrev_590)
            {
                case 19:
                    g_Inventory_SelectionId = InventorySelectionId_Item;
                    D_800C399C              = InventorySelectionId_Item;
                    break;

                case 18:
                    g_Inventory_SelectionId = InventorySelectionId_Settings;
                    D_800C399C              = InventorySelectionId_Settings;
                    break;

                case 15:
                    g_Inventory_SelectionId = InventorySelectionId_Map;
                    D_800C399C              = InventorySelectionId_Map;
                    break;

                default:
                    break;
            }

            g_SysWork.player_4C.extra_128.field_28 = 0;
            g_GameWork.background2dColor_R_58C     = 0;
            g_GameWork.background2dColor_G_58D     = 0;
            g_GameWork.background2dColor_B_58E     = 0;

            Gfx_Items_RenderInit();
            func_8004EF48();

            g_GameWork.gameStateStep_598[1] = 1;
            g_GameWork.gameStateStep_598[2] = 0;
            return;

        case 1:
        case 5: // Item equip.
        case 6: // Item unequip.
        case 7:
        case 8:
        case 9:
        case 11:
        case 12:
        case 13:
        case 16:
            if (g_SysWork.inventoryItemSelectedIdx_2351 == g_Inventory_SelectedItemIdx &&
                g_GameWork.gameState_594 == GameState_InventoryScreen &&
                g_Gfx_ScreenFade == 1)
            {
                s32 prevGameState;
                prevGameState = g_GameWork.gameStateStep_598[2];

                Inventory_Logic(g_SysWork.inventoryItemSelectedIdx_2351);

                g_GameWork.gameStateStep_598[2] = prevGameState;
            }

            Gfx_Inventory_CmdOptionsDraw();

            switch (g_GameWork.gameStateStep_598[1])
            {
                // "Can't use here" message. Triggers when attempting to use special items in places where they trigger nothing.
                case 12:
                    g_GameWork.gameStateStep_598[1] = 1;
                    g_GameWork.gameStateStep_598[2] = 0;
                    g_SysWork.field_10              = 3; // This specifically make it appear.
                    g_SysWork.timer_2C              = 0;
                    g_SysWork.field_14              = 0;
                    break;

                // "Too dark too look at the item" message. Triggers in circumstances like maps in Otherworld with the flashlight off.
                case 16:
                    g_GameWork.gameStateStep_598[1] = 1;
                    g_GameWork.gameStateStep_598[2] = 0;
                    g_SysWork.field_10              = 4; // This specifically make it appear.
                    g_SysWork.timer_2C              = 0;
                    g_SysWork.field_14              = 0;
                    break;

                default:
                    break;
            }
            break;

        case 17:
            {
                s32 prevGameState;

                prevGameState                   = g_GameWork.gameStateStep_598[2];
                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;

                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = prevGameState;
            }
            break;

        case 18:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                s32 prevGameState;

                Gfx_ScreenRefresh(320, 0);
                Fs_QueueWaitForEmpty();
                func_8004C040();

                D_800AE185 = NO_VALUE;
                D_800AE186 = NO_VALUE;

                Game_StateSetNext_ClearStateSteps(GameState_OptionScreen);
                return;
            }
            break;

        case 19:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                func_8004C040();
                Game_StateSetNext(GameState_MapScreen);
                return;
            }
            break;
			
		// Exiting inventory screen.
        case 20:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                Gfx_ScreenRefresh(320, 0);
                Inventory_ExitAnimFixes();

                g_SavegamePtr->inventoryItemSpaces_AB = func_8004F190(g_SavegamePtr);

                func_8003CD6C(&g_SysWork.playerCombatInfo_38);
                func_8003D01C();
                Fs_QueueWaitForEmpty();
                
                Game_StateSetNext(GameState_InGame);
                return;
            }
            break;

        // Results screen triggers here.
        case 21:
            Gfx_ClearRectInterlaced(0, 0x20, 0x140, 0x1C0, 0, 0, 0);
            Gfx_Init(0x140, 1);

            g_IntervalVBlanks                  = 1;
            g_Gfx_ScreenFade                   = 6;
            D_800B5C30                         = 0x3000;
            g_GameWork.background2dColor_R_58C = 0;
            g_GameWork.background2dColor_G_58D = 0;
            g_GameWork.background2dColor_B_58E = 0;
            g_Inventory_SelectionId            = InventorySelectionId_Item;

            Gfx_Items_RenderInit();
            func_8008F94C();

            D_800C3994 = g_SavegamePtr->gameDifficulty_260;

            if (g_SavegamePtr->gameDifficulty_260 <= 0)
            {
                g_SavegamePtr->gameDifficulty_260++;
            }

            Game_SavegameInitialize(0, g_SavegamePtr->gameDifficulty_260);
            func_800904F4();

            g_GameWork.gameStateStep_598[1] = 22;
            g_GameWork.gameStateStep_598[2] = 0;
            break;

        case 22:
            if (g_ControllerPtrConst->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                        g_GameWorkPtr->config_0.controllerConfig_0.skip_4))
            {
                g_GameWork.gameStateStep_598[1] = 23;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 23:
            if (g_ControllerPtrConst->btnsClicked_10 & (ControllerFlag_LStickRight | ControllerFlag_LStickLeft))
            {
                g_Inventory_SelectionId = g_Inventory_SelectionId == 0;
                Sd_PlaySfx(Sfx_Back, 0, 64);
            }

            if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                s32 prevGameState;
                g_Gfx_ScreenFade = 2;
                prevGameState    = g_GameWork.gameStateStep_598[2];

                Sd_PlaySfx(Sfx_Confirm, 0, 64);

                if (g_Inventory_SelectionId == InventorySelectionId_Item)
                {
                    GameFs_SaveLoadBinLoad();
                    g_GameWork.gameStateStep_598[1] = 24;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
                else
                {
                    g_GameWork.gameStateStep_598[1] = 25;
                    g_GameWork.gameStateStep_598[2] = 0;
                }

                g_GameWork.gameStateStep_598[2] = prevGameState;
            }
            break;

        case 24:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                Gfx_ScreenRefresh(320, 0);
                GameFs_SaveLoadBinLoad();
                Fs_QueueWaitForEmpty();
                Game_StateSetNext(GameState_Unk10);
                return;
            }
            break;

        case 25:
            if ((g_Gfx_ScreenFade & 0x7) == 5)
            {
                if (Fs_QueueDoThingWhenEmpty() != 0)
                {
                    g_Demo_ReproducedCount = 0;

                    Game_WarmBoot();
                    GameFs_StreamBinLoad();
                    Fs_QueueWaitForEmpty();
                    Game_StateSetNext(GameState_MovieIntro);
                    return;
                }
            }
            break;
    }

    Gfx_ItemScreens_RenderInit(&g_Inventory_SelectionId);

    if (g_GameWork.gameStateStep_598[1] < 21)
    {
        Gfx_Inventory_ScrollArrowsDraw(&g_Inventory_SelectionId);
    }

    if (g_GameWork.gameStateStep_598[1] >= 23)
    {
        Gfx_Results_Save();
    }
}

void Gfx_Results_Save() // 0x8004D1A0
{
    s32      i;
    s32      colorVar0;
    s32      colorVar1;
    s8       rgColor;
    LINE_F2* line;

    s_ResultStringOffset strOffsets[] = 
    {
        {   0,   0,   0,  64 },
        {   0,   0, 100,   0 },
        { 208, 144, 208,  80 },
        { 208, 144, 108, 144 },
        {   4,   8, 204,   8 },
        {   4, 136, 204, 136 },
        {   4,   8,   4, 136 },
        { 204,   8, 204, 136 },
        {   0,   1, 100,   1 },
        { 208, 143, 108, 143 },
        {   4,   7, 204,   7 },
        {   4, 137, 204, 137 },
        {   0,   0,   0,  20 },
        {   0,   0,  22,   0 },
        {  48,  48,  48,  28 },
        {  48,  48,  26,  48 },
        {   2,   4,  46,   4 },
        {   2,  44,  46,  44 },
        {   2,   4,   2,  44 },
        {  46,   4,  46,  44 },
        {   0,   1,  22,   1 },
        {  48,  47,  26,  47 },
        {   2,   3,  46,   3 },
        {   2,  45,  46,  45 }
    };

    GsOT* ot = &g_ObjectTable1[g_ObjectTableIdx];

    char* saveDialogStrs[] =
    {
        "\x07Is_it_OK_to_save?",
        "\x07Yes_____________No"
    };
    
    for (i = 0; i < 24; i++)
    {
        line = (LINE_F2*)GsOUT_PACKET_P;
        setLineF2(line);
        
        if (i % 12 < 8) 
        {
            colorVar0  = i % 12;
            colorVar0 += ((i % 12) < 0) ? 3 : 0;
            colorVar1  = colorVar0 >> 2;
            rgColor    = 0x60 - (colorVar1 << 6);
            setRGB0(line, rgColor, rgColor, 0xFF);
        } 
        else 
        {
            colorVar1 = ((i % 12) - 4) / 2;
            rgColor   = 0x60 - (colorVar1 << 6);
            setRGB0(line, rgColor, rgColor, 0xFF);
        }

        if (i < 12) 
        {
            setXY2(line,
                   strOffsets[i].x0_0 + 0xFF98, strOffsets[i].y0_1 + 0xFFB8,
                   strOffsets[i].x1_2 + 0xFF98, strOffsets[i].y1_3 + 0xFFB8);
        }
        else 
        {
            setXY2(line,
                   (strOffsets[i].x0_0 + 0xFFB4) + (g_Inventory_SelectionId * 102), strOffsets[i].y0_1 + 6,
                   (strOffsets[i].x1_2 + 0xFFB4) + (g_Inventory_SelectionId * 102), strOffsets[i].y1_3 + 6);
        }

        addPrim(&ot->org[7], line);
        GsOUT_PACKET_P = (PACKET*)line + sizeof(LINE_F2);
    }

    g_SysWork.field_2350_0 = 1;

    Gfx_StringSetPosition(90, 92);
    Gfx_StringDraw("\x07Is_it_OK_to_save?", 99);

    Gfx_StringSetPosition(94, 122);
    Gfx_StringDraw("\x07Yes_____________No", 99);

    g_SysWork.field_2350_0 = 0;

    Gfx_StringSetPosition(82, 200);
    Gfx_StringDraw("NEXT_GAME_MODE", 15);

    switch (D_800C3994)
    {
        case GameDifficulty_Easy:
            Gfx_StringSetPosition(123, 240);
            Gfx_StringDraw("NORMAL", 10);
            break;

        case GameDifficulty_Normal:
        case GameDifficulty_Hard:
            Gfx_StringSetPosition(136, 240);
            Gfx_StringDraw("HARD", 10);
            break;

        default:
            break;
    }
}

void Inventory_Logic() // 0x8004D518
{
    s32 step;
    s32 cmdCountMax = 0;
    s32 temp;
    s32 curItemIdx;

    Inventory_DirectionalInputSet();

    g_Inventory_BorderSelectionId++;

    if (g_Inventory_BorderSelectionId >= InventorySelectionId_Examine)
    {
        D_800C399C = g_Inventory_SelectionId;
    }

    g_Inventory_BorderSelectionId = CLAMP(g_Inventory_BorderSelectionId, InventorySelectionId_Item, InventorySelectionId_Examine);

    if (g_GameWork.gameStateStep_598[1] != 1)
    {
        return;
    }

    if (g_Inventory_SelectionId == InventorySelectionId_Item)
    {
        if (g_Inventory_BorderSelectionId <= InventorySelectionId_Settings)
        {
            return;
        }
    }
    else if (g_Inventory_BorderSelectionId <= InventorySelectionId_Health)
    {
        return;
    }

    switch (g_Inventory_SelectionId)
    {
        case InventorySelectionId_Item:
            if ((g_Inventory_IsLeftClicked && g_Inventory_BorderSelectionId == InventorySelectionId_Examine) ||
                (g_Inventory_IsLeftHeld && (D_800C3990 != 0 || g_Inventory_BorderSelectionId == InventorySelectionId_Examine)))
            {
                if (g_Inventory_IsLeftClicked || g_Inventory_IsLeftHeld)
                {
                    D_800C3990 = 1;
                }

                D_800AE178                    = 1;
                g_Inventory_BorderSelectionId = InventorySelectionId_Exit;
                g_Inventory_CmdSelectedIdx    = 0;
                Sd_PlaySfx(Sfx_Back, -64, 64);

                g_SysWork.inventoryItemSelectedIdx_2351 = ((g_SysWork.inventoryItemSelectedIdx_2351 + g_SavegamePtr->inventoryItemSpaces_AB) - 1) % g_SavegamePtr->inventoryItemSpaces_AB;
                temp                                    = g_SavegamePtr->inventoryItemSpaces_AB - 3;
                func_800539A4(0, (g_SysWork.inventoryItemSelectedIdx_2351 + temp) % g_SavegamePtr->inventoryItemSpaces_AB);
            }
            else if (((g_Inventory_IsRightClicked || g_Inventory_IsRightPulsed) && g_Inventory_BorderSelectionId == InventorySelectionId_Examine) ||
                     (g_Inventory_IsRightHeld && (D_800C3990 != 0 || g_Inventory_BorderSelectionId == InventorySelectionId_Examine)))
            {
                if (g_Inventory_IsRightClicked || g_Inventory_IsRightHeld)
                {
                    D_800C3990 = 1;
                }

                D_800AE178                    = 1;
                g_Inventory_BorderSelectionId = InventorySelectionId_Exit;
                g_Inventory_CmdSelectedIdx    = 0;
                Sd_PlaySfx(Sfx_Back, 64, 64);

                g_SysWork.inventoryItemSelectedIdx_2351 = (g_SysWork.inventoryItemSelectedIdx_2351 + 1) % g_SavegamePtr->inventoryItemSpaces_AB;
                func_800539A4(1, (g_SysWork.inventoryItemSelectedIdx_2351 + 3) % g_SavegamePtr->inventoryItemSpaces_AB);
            }
            else if (g_Inventory_IsUpClicked != InventorySelectionId_Item && g_Inventory_BorderSelectionId == InventorySelectionId_Examine)
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;

                if (g_SysWork.playerCombatInfo_38.field_F >= 0)
                {
                    g_Inventory_SelectionId = InventorySelectionId_EquippedItem;
                    Sd_PlaySfx(Sfx_Back, 0, 64);
                }
            }
            else if ((g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2 || g_Inventory_IsDownClicked != 0) &&
                     g_Inventory_BorderSelectionId == InventorySelectionId_Examine)
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;

                if (g_Inventory_IsDownClicked != 0)
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);
                }
                else
                {
                    Sd_PlaySfx(Sfx_Cancel, 0, 64);
                }

                g_Inventory_SelectionId = InventorySelectionId_Exit;
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0 &&
                     g_Inventory_BorderSelectionId >= InventorySelectionId_Examine)
            {
                if (g_SavegamePtr->items_0[g_SysWork.inventoryItemSelectedIdx_2351].id_0 == InventoryItemId_Flauros ||
                    (g_SysWork.field_2388.field_16 != 0 && g_SavegamePtr->items_0[g_SysWork.inventoryItemSelectedIdx_2351].id_0 == InventoryItemId_Flashlight))
                {
                    Sd_PlaySfx(Sfx_Denied, 64, 64);
                }
                else if (g_SavegamePtr->items_0[g_SysWork.inventoryItemSelectedIdx_2351].command_2 == InventoryCmdId_Unk10)
                {
                    g_GameWork.gameStateStep_598[1] = 12;
                    g_GameWork.gameStateStep_598[2] = 0;
                    Sd_PlaySfx(Sfx_Denied, 64, 64);
                }
                else
                {
                    g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
                    g_Inventory_CmdSelectedIdx    = 0;

                    if (g_SavegamePtr->items_0[g_SysWork.inventoryItemSelectedIdx_2351].command_2 != InventoryCmdId_Unk11)
                    {
                        g_Inventory_SelectionId = InventorySelectionId_ItemCmd;
                        Sd_PlaySfx(Sfx_Confirm, 64, 64);
                    }
                }
            }
            else if (!(g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16))
            {
                D_800C3990 = 0;
            }
            else
            {
                step = g_GameWork.gameStateStep_598[2];
                Sd_PlaySfx(Sfx_Cancel, 0, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }
            break;

        case InventorySelectionId_EquippedItem:
            if (g_Inventory_IsDownClicked != 0)
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
                Sd_PlaySfx(Sfx_Back, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
                g_Inventory_CmdSelectedIdx    = 0;

                if (g_SavegamePtr->items_0[g_SysWork.playerCombatInfo_38.field_12].command_2 != InventoryCmdId_Unk11)
                {
                    g_Inventory_SelectionId = InventorySelectionId_EquippedItemCmd;
                    Sd_PlaySfx(Sfx_Confirm, 0, 64);
                }
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
                g_Inventory_SelectionId       = InventorySelectionId_Exit;
                Sd_PlaySfx(Sfx_Cancel, 0, 64);
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16)
            {
                step = g_GameWork.gameStateStep_598[2];
                Sd_PlaySfx(Sfx_Cancel, 0, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }
            break;

        case InventorySelectionId_Exit:
            if (g_Inventory_IsUpClicked)
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
                Sd_PlaySfx(Sfx_Back, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_Inventory_IsLeftClicked)
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
                Sd_PlaySfx(Sfx_Back, -64, 64);
                g_Inventory_SelectionId = InventorySelectionId_Settings;
            }
            else if (g_Inventory_IsRightClicked)
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
                Sd_PlaySfx(Sfx_Back, 64, 64);
                g_Inventory_SelectionId = InventorySelectionId_Map;
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.item_16 |
                                                             (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                              g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)))
            {
                step = g_GameWork.gameStateStep_598[2];
                Sd_PlaySfx(Sfx_Cancel, 0, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }
            break;

        case InventorySelectionId_Settings:
            if (g_Inventory_IsUpClicked)
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
                Sd_PlaySfx(Sfx_Back, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_Inventory_IsRightClicked || (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;

                if (!g_Inventory_IsRightClicked || (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
                {
                    Sd_PlaySfx(Sfx_Cancel, 0, 64);
                    g_Inventory_SelectionId = InventorySelectionId_Exit;
                }
                else
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);
                    g_Inventory_SelectionId = InventorySelectionId_Exit;
                }
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                Sd_PlaySfx(Sfx_Confirm, -64, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1] = 18;
                g_GameWork.gameStateStep_598[2] = 0;

                GameFs_OptionBinLoad();
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16)
            {
                step = g_GameWork.gameStateStep_598[2];
                Sd_PlaySfx(Sfx_Cancel, 0, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }
            break;

        case InventorySelectionId_Map:
            if (g_Inventory_IsUpClicked)
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
                Sd_PlaySfx(Sfx_Back, 0, 64);
                g_Inventory_SelectionId = InventorySelectionId_Item;
            }
            else if (g_Inventory_IsLeftClicked || g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;

                if (!g_Inventory_IsLeftClicked || g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
                {
                    Sd_PlaySfx(Sfx_Cancel, 0, 64);
                }
                else
                {
                    Sd_PlaySfx(Sfx_Back, 0, 64);
                }

                g_Inventory_SelectionId = InventorySelectionId_Exit;
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                if ((!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) || g_SysWork.field_2388.field_15 != 0 ||
                     (!(g_SysWork.field_2388.field_1C[0].field_0.field_0.s_field_0.field_0 & (1 << 0)) &&
                      !(g_SysWork.field_2388.field_1C[1].field_0.field_0.s_field_0.field_0 & (1 << 0)))) &&
                    HAS_MAP(g_SavegamePtr->current2dMapIdx_A9))
                {
                    Sd_PlaySfx(Sfx_Confirm, 64, 64);

                    if (D_800A99CC[g_SavegamePtr->current2dMapIdx_A9] != NO_VALUE)
                    {
                        Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + D_800A99CC[g_SavegamePtr->current2dMapIdx_A9], FS_BUFFER_1, &g_MapMarkerAtlasImg);
                    }
                    Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + D_800A99B4[g_SavegamePtr->current2dMapIdx_A9]);

                    g_Gfx_ScreenFade                = 2;
                    g_GameWork.gameStateStep_598[1] = 19;
                    g_GameWork.gameStateStep_598[2] = 0;
                }
                else
                {
                    Sd_PlaySfx(Sfx_Denied, 64, 64);
                }
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16)
            {
                step = g_GameWork.gameStateStep_598[2];
                Sd_PlaySfx(Sfx_Cancel, 0, 64);

                g_Gfx_ScreenFade                = 2;
                g_GameWork.gameStateStep_598[1] = 20;
                g_GameWork.gameStateStep_598[2] = 0;
                func_8007EBBC();

                g_GameWork.gameStateStep_598[2] = step;
            }

            if (!HAS_MAP(g_SavegamePtr->current2dMapIdx_A9))
            {
                Gfx_Inventory_UnavailableMapText(1);
            }
            else if (g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1) && g_SysWork.field_2388.field_15 == 0 &&
                     (g_SysWork.field_2388.field_1C[0].field_0.field_0.s_field_0.field_0 & (1 << 0) ||
                      g_SysWork.field_2388.field_1C[1].field_0.field_0.s_field_0.field_0 & (1 << 0)))
            {
                Gfx_Inventory_UnavailableMapText(0);
            }
            break;

        case InventorySelectionId_ItemCmd:
        case InventorySelectionId_EquippedItemCmd:
            if (g_Inventory_SelectionId == InventorySelectionId_ItemCmd)
            {
                curItemIdx = g_SysWork.inventoryItemSelectedIdx_2351;
            }
            else
            {
                curItemIdx = g_SysWork.playerCombatInfo_38.field_12;
            }

            switch (g_SavegamePtr->items_0[curItemIdx].command_2)
            {
                case InventoryCmdId_UseHealth:
                case InventoryCmdId_Use:
                case InventoryCmdId_Equip:
                case InventoryCmdId_Unequip:
                case InventoryCmdId_Reload:
                case InventoryCmdId_Look:
                    cmdCountMax = 1;
                    break;

                case InventoryCmdId_EquipReload:
                case InventoryCmdId_UnequipReload:
                case InventoryCmdId_OnOff:
                case InventoryCmdId_UseLook:
                    cmdCountMax = 2;
                    break;

                case InventoryCmdId_Unk10:
                    cmdCountMax = 0;
                    break;
            }

            if (g_Inventory_IsDownPulsed)
            {
                if (g_Inventory_CmdSelectedIdx < (cmdCountMax - 1))
                {
                    g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
                    g_Inventory_CmdSelectedIdx++;
                    Sd_PlaySfx(Sfx_Back, 64, 64);
                }
            }
            else if (g_Inventory_IsUpPulsed)
            {
                if (g_Inventory_CmdSelectedIdx > 0)
                {
                    g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
                    g_Inventory_CmdSelectedIdx--;
                    Sd_PlaySfx(Sfx_Back, 64, 64);
                }
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;

                switch (g_SavegamePtr->items_0[curItemIdx].command_2)
                {
                    case InventoryCmdId_OnOff:
                        g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
                        g_Inventory_SelectionId             = InventorySelectionId_Item;

                        if (g_Inventory_CmdSelectedIdx == 0)
                        {
                            switch (g_SavegamePtr->items_0[curItemIdx].id_0)
                            {
                                case InventoryItemId_Flashlight:
                                    func_8003ECBC();
                                    break;

                                case InventoryItemId_PocketRadio:
                                    g_SavegamePtr->flags_AC |= 1 << 0;
                                    break;
                            }
                        }
                        else
                        {
                            switch (g_SavegamePtr->items_0[curItemIdx].id_0)
                            {
                                case InventoryItemId_Flashlight:
                                    func_8003ECE4();
                                    break;

                                case InventoryItemId_PocketRadio:
                                    g_SavegamePtr->flags_AC &= ~(1 << 0);
                                    break;
                            }
                        }

                        g_GameWork.gameStateStep_598[1] = 1;
                        g_GameWork.gameStateStep_598[2] = 0;
                        break;

                    case InventoryCmdId_UseLook:
                        if (g_Inventory_CmdSelectedIdx != 0)
                        {
                            if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) || g_SysWork.field_2388.field_15 != 0 ||
                                (!(g_SysWork.field_2388.field_1C[0].field_0.field_0.s_field_0.field_0 & (1 << 0)) &&
                                 !(g_SysWork.field_2388.field_1C[1].field_0.field_0.s_field_0.field_0 & (1 << 0))))
                            {
                                g_Inventory_BorderSelectionId   = InventorySelectionId_EquippedItem;
                                g_Inventory_SelectionId         = InventorySelectionId_Examine;
                                g_GameWork.gameStateStep_598[1] = 13;
                                g_GameWork.gameStateStep_598[2] = 0;

                                switch (g_SavegamePtr->items_0[curItemIdx].id_0)
                                {
                                    case InventoryItemId_KeyOfLion:
                                        Fs_QueueStartReadTim(FILE_TIM_LION_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KeyOfWoodman:
                                        Fs_QueueStartReadTim(FILE_TIM_KIKORI_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KeyOfScarecrow:
                                        Fs_QueueStartReadTim(FILE_TIM_KAKASHI_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KeyOfOphiel:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_A_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KeyOfHagith:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_B_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KeyOfPhaleg:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_C_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KeyOfBethor:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_D_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KeyOfAratron:
                                        Fs_QueueStartReadTim(FILE_TIM_LAST_E_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KGordonKey:
                                        Fs_QueueStartReadTim(FILE_TIM_K_GORDON_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_KaufmannKey:
                                        Fs_QueueStartReadTim(FILE_TIM_MOTEL_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_AntiqueShopKey:
                                        if (g_SavegamePtr->eventFlags_168[5] & (1 << 11))
                                        {
                                            g_SavegamePtr->mapMarkingFlags_1DC |= 1 << 16;
                                        }

                                        Fs_QueueStartReadTim(FILE_TIM_ANTIQUE_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;

                                    case InventoryItemId_ClassroomKey:
                                        Fs_QueueStartReadTim(FILE_TIM_KEY_OF_2_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                        break;
                                }
                            }
                            else
                            {
                                g_GameWork.gameStateStep_598[1] = 16;
                                g_GameWork.gameStateStep_598[2] = 0;
                            }
                        }
                        else
                        {
                            func_8004E6D4(curItemIdx);
                        }
                        break;

                    case InventoryCmdId_Look:
                        if (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) || g_SysWork.field_2388.field_15 != 0 ||
                            (!(g_SysWork.field_2388.field_1C[0].field_0.field_0.s_field_0.field_0 & (1 << 0)) &&
                             !(g_SysWork.field_2388.field_1C[1].field_0.field_0.s_field_0.field_0 & (1 << 0))))
                        {
                            g_Inventory_BorderSelectionId   = InventorySelectionId_EquippedItem;
                            g_Inventory_SelectionId         = InventorySelectionId_Examine;
                            g_GameWork.gameStateStep_598[1] = 13;
                            g_GameWork.gameStateStep_598[2] = 0;

                            switch (g_SavegamePtr->items_0[curItemIdx].id_0)
                            {
                                case InventoryItemId_NoteToSchool:
                                    Fs_QueueStartReadTim(FILE_TIM_TOSCHOOL_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                    break;

                                case InventoryItemId_NoteDoghouse:
                                    Fs_QueueStartReadTim(FILE_TIM_STKENNEL_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                    break;

                                case InventoryItemId_Receipt:
                                    Fs_QueueStartReadTim(FILE_TIM_RECEIPT_TIM, FS_BUFFER_1, &g_ItemInspectionImg);
                                    break;
                            }
                        }
                        else
                        {
                            g_GameWork.gameStateStep_598[1] = 16;
                            g_GameWork.gameStateStep_598[2] = 0;
                            break;
                        }
                        break;

                    case InventoryCmdId_UseHealth:
                        g_Inventory_BorderSelectionId   = InventorySelectionId_EquippedItem;
                        g_Inventory_SelectionId         = InventorySelectionId_Health;
                        g_GameWork.gameStateStep_598[1] = 9;
                        g_GameWork.gameStateStep_598[2] = 0;
                        break;

                    case InventoryCmdId_Use:
                        func_8004E6D4(curItemIdx);
                        break;

                    case InventoryCmdId_Equip:
                        g_Inventory_BorderSelectionId   = InventorySelectionId_EquippedItem;
                        g_Inventory_SelectionId         = InventorySelectionId_EquippedItem;
                        g_GameWork.gameStateStep_598[1] = 5;
                        g_GameWork.gameStateStep_598[2] = 0;
                        break;

                    case InventoryCmdId_Unequip:
                        g_Inventory_BorderSelectionId   = InventorySelectionId_EquippedItem;
                        g_Inventory_SelectionId         = InventorySelectionId_EquippedItem;
                        g_GameWork.gameStateStep_598[1] = 6;
                        g_GameWork.gameStateStep_598[2] = 0;
                        break;

                    case InventoryCmdId_Reload:
                        g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;

                        if (curItemIdx != g_SysWork.playerCombatInfo_38.field_12)
                        {
                            g_GameWork.gameStateStep_598[1] = 8;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        else
                        {
                            g_GameWork.gameStateStep_598[1] = 7;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        break;

                    case InventoryCmdId_EquipReload:
                        g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;

                        if (g_Inventory_CmdSelectedIdx == 0)
                        {
                            g_Inventory_SelectionId         = InventorySelectionId_EquippedItem;
                            g_GameWork.gameStateStep_598[1] = 5;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        else if (curItemIdx != g_SysWork.playerCombatInfo_38.field_12)
                        {
                            g_GameWork.gameStateStep_598[1] = 8;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        else
                        {
                            g_GameWork.gameStateStep_598[1] = 7;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        break;

                    case InventoryCmdId_UnequipReload:
                        g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;

                        if (g_Inventory_CmdSelectedIdx == 0)
                        {
                            g_Inventory_SelectionId         = InventorySelectionId_EquippedItem;
                            g_GameWork.gameStateStep_598[1] = 6;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        else if (curItemIdx != g_SysWork.playerCombatInfo_38.field_12)
                        {
                            g_GameWork.gameStateStep_598[1] = 8;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        else
                        {
                            g_GameWork.gameStateStep_598[1] = 7;
                            g_GameWork.gameStateStep_598[2] = 0;
                        }
                        break;
                }

                if (g_GameWork.gameStateStep_598[1] == 12)
                {
                    Sd_PlaySfx(Sfx_Denied, 64, 64);
                }
                else
                {
                    Sd_PlaySfx(Sfx_Confirm, 64, 64);
                }
            }
            else if (g_ControllerPtrConst->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
                g_Inventory_CmdSelectedIdx    = 0;
                g_Inventory_SelectionId       = InventorySelectionId_Item;
                Sd_PlaySfx(Sfx_Cancel, 0, 64);
            }

            do {} while (0); // HACK: Required for match.
            break;

        case InventorySelectionId_Examine:
            g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
            break;
    }
}

void func_8004E6D4(s32 arg0) // 0x8004E6D4
{
    s32 i;

    g_GameWork.gameStateStep_598[1] = 12;
    g_GameWork.gameStateStep_598[2] = 0;

    if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP6_S04)
    {
        if (func_80038A6C(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.npcs_1A0[0].position_18, FP_METER(0.7f)) == 0 &&
            ABS(g_SysWork.player_4C.chara_0.position_18.vy - g_SysWork.npcs_1A0[0].position_18.vy) < FP_METER(0.3f) &&
            g_SysWork.player_4C.extra_128.field_1C == 0 &&
            g_SavegamePtr->items_0[arg0].id_0 == InventoryItemId_UnknownLiquid)
        {
            g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
            g_Inventory_SelectionId             = InventorySelectionId_Item;
            g_GameWork.gameStateStep_598[1]     = 11;
            g_GameWork.gameStateStep_598[2]     = 0;

            func_8003ECBC();
            g_SavegamePtr->eventFlags_1A0 |= 1 << 0;
        }
    }
    else
    {
        for (i = 0; D_800BCDC0[i] != NO_VALUE; i++)
        {
            if (D_800BCDC0[i] == g_SavegamePtr->items_0[arg0].id_0)
            {
                g_Inventory_BorderSelectionId = InventorySelectionId_EquippedItem;
                g_Inventory_SelectionId             = InventorySelectionId_Item;
                g_GameWork.gameStateStep_598[1]     = 11;
                g_GameWork.gameStateStep_598[2]     = 0;

                func_8003ECBC();
                g_SysWork.player_4C.extra_128.field_28 = D_800BCDC0[i];
                break;
            }
        }
    }
}

void Gfx_Inventory_CmdOptionsDraw() // 0x8004E864
{
    GsOT*    ot;
    s32      i;
    s32      idx;
    POLY_G4* poly;
    s32      x0;
    s32      y0;

    char* strs[] = // 0x80026214
    {
        "Use",
        "Equip",
        "Unequip",
        "Reload",
        "Detail",
        "On",
        "Off",
        "Look"
    };

    ot = &g_ObjectTable1[g_ObjectTableIdx];

    if (g_Inventory_SelectionId >= InventorySelectionId_ItemCmd &&
        g_Inventory_SelectionId <= InventorySelectionId_EquippedItemCmd)
    {
        Gfx_StringSetColor(ColorId_White);
    }
    else
    {
        Gfx_StringSetColor(ColorId_DarkGrey);
    }

    if (g_Inventory_SelectionId != InventorySelectionId_EquippedItem &&
        g_Inventory_SelectionId != InventorySelectionId_EquippedItemCmd)
    {
        idx = g_SysWork.inventoryItemSelectedIdx_2351;
    }
    else
    {
        idx = g_SysWork.playerCombatInfo_38.field_12;
    }

    switch (g_SavegamePtr->items_0[idx].command_2)
    {
        case InventoryCmdId_OnOff:
            if (g_SysWork.field_2388.field_16 == 0 || g_SavegamePtr->items_0[idx].id_0 != InventoryItemId_Flashlight)
            {
                Gfx_StringSetPosition(222, -42);
                Gfx_StringDraw(strs[5], 10);
                Gfx_StringSetPosition(222, -26);
                Gfx_StringDraw(strs[6], 10);
            }
            break;

        case InventoryCmdId_UseHealth:
        case InventoryCmdId_Use:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(strs[0], 10);
            break;

        case InventoryCmdId_Equip:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(strs[1], 10);
            break;

        case InventoryCmdId_Unequip:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(strs[2], 10);
            break;

        case InventoryCmdId_Reload:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(strs[3], 10);
            break;

        case InventoryCmdId_UseLook:
            Gfx_StringSetPosition(222, -42);
            Gfx_StringDraw(strs[0], 10);
            Gfx_StringSetPosition(222, -26);
            Gfx_StringDraw(strs[7], 10);
            break;

        case InventoryCmdId_EquipReload:
            Gfx_StringSetPosition(222, -42);
            Gfx_StringDraw(strs[1], 10);
            Gfx_StringSetPosition(222, -26);
            Gfx_StringDraw(strs[3], 10);
            break;

        case InventoryCmdId_UnequipReload:
            Gfx_StringSetPosition(222, -42);
            Gfx_StringDraw(strs[2], 10);
            Gfx_StringSetPosition(222, -26);
            Gfx_StringDraw(strs[3], 10);
            break;

        case InventoryCmdId_Look:
            Gfx_StringSetPosition(222, -34);
            Gfx_StringDraw(strs[7], 10);
            break;

        case 10:
        case 11:
            break;
    }

    if (g_Inventory_SelectionId >= InventorySelectionId_ItemCmd &&
        g_Inventory_SelectionId <= InventorySelectionId_EquippedItemCmd)
    {
        switch (g_SavegamePtr->items_0[idx].command_2)
        {
            case 4:
            case 5:
            case 6:
            case 9:
                y0 = -154;
                break;

            default:
                y0 = -146;
                break;
        }

        for (i = 0; i < 2; i++)
        {
            poly = (POLY_G4*)GsOUT_PACKET_P;

            x0 = 56;

            setPolyG4(poly);

            if (i != 0)
            {
                setRGB0(poly, 0, 0xC0, 0x40);
                setRGB1(poly, 0, 0, 0);
                setRGB2(poly, 0, 0xC0, 0x40);
                setRGB3(poly, 0, 0, 0);
            }
            else
            {
                setRGB0(poly, 0, 0, 0);
                setRGB1(poly, 0, 0xC0, 0x40);
                setRGB2(poly, 0, 0, 0);
                setRGB3(poly, 0, 0xC0, 0x40);
            }

            setXY4(poly,
                   x0,  (y0 + (i * 6))       + ((u16)g_Inventory_CmdSelectedIdx * 16),
                   x0,  (y0 + ((i + 1) * 6)) + ((u16)g_Inventory_CmdSelectedIdx * 16),
                   136, (y0 + (i * 6))       + ((u16)g_Inventory_CmdSelectedIdx * 16),
                   136, (y0 + ((i + 1) * 6)) + ((u16)g_Inventory_CmdSelectedIdx * 16));

            addPrim(&ot->org[7], poly);
            GsOUT_PACKET_P = (PACKET*)poly + sizeof(POLY_G4);
        }
    }
}

void Gfx_Inventory_ScrollArrowsDraw(s32* invSelectionId) // 0x8004EC7C
{
    #define ARROW_COUNT 4

    POLY_G3* arrowPoly;
    s32      baseColor;
    s32      i;
    s8       timeStep;

    GsOT* ot = &g_ObjectTable1[g_ObjectTableIdx];

    // TODO: Why the large values for some positions?
    s_Triangle2d arrowTris[] =
    {
        { { 0xFFC4, 0x000C }, { 0xFFCC, 0x0004 }, { 0xFFCC, 0x0014 } },
        { { 0xFFCC, 0x000C }, { 0xFFD4, 0x0004 }, { 0xFFD4, 0x0014 } },
        { { 0x0034, 0x000C }, { 0x002C, 0x0004 }, { 0x002C, 0x0014 } },
        { { 0x003C, 0x000C }, { 0x0034, 0x0004 }, { 0x0034, 0x0014 } },
        { { 0x0060, 0xFF53 }, { 0x0066, 0xFF60 }, { 0x005A, 0xFF60 } }, // Unused.
        { { 0x0060, 0xFFA4 }, { 0x005B, 0xFF98 }, { 0x0065, 0xFF98 } }  // Unused.
    };

    // Only draw arrows when item is selected.
    if (*invSelectionId != InventorySelectionId_Item) 
    {
        return;
    }

    // Draw 2 flashing left/right double arrows.
    for (i = 0; i < ARROW_COUNT; i++) 
    {
        timeStep = g_SysWork.timer_1C & 0x1F;

        arrowPoly = (POLY_G3*)GsOUT_PACKET_P;
        setPolyG3(arrowPoly);
        setSemiTrans(arrowPoly, 1);

        baseColor = 0xFF - (timeStep * 8);
        setRGB0(arrowPoly, baseColor, baseColor, baseColor);
        setRGB1(arrowPoly, timeStep * 8, timeStep * 8, timeStep * 8);
        setRGB2(arrowPoly, timeStep * 8, timeStep * 8, timeStep * 8);

        setXY3(arrowPoly,
               arrowTris[i].vertex0_0.vx, arrowTris[i].vertex0_0.vy,
               arrowTris[i].vertex1_4.vx, arrowTris[i].vertex1_4.vy,
               arrowTris[i].vertex2_8.vx, arrowTris[i].vertex2_8.vy);

        addPrim(&ot->org[7], arrowPoly);
        GsOUT_PACKET_P = (PACKET*)arrowPoly + sizeof(POLY_G3);
    }

    // Set texture.
    Gfx_Primitive2dTextureSet(0, 0, 7, 1);
}

s32 func_8004EE94(u8 arg0, u8 arg1) // 0x8004EE94
{
    s32 i;

    for (i = 0; i < g_SavegamePtr->inventoryItemSpaces_AB; i++)
    {
        if (arg0 == g_SavegamePtr->items_0[i].id_0)
        {
            if (arg1 != 0)
            {
                if (arg1 == 1)
                {
                    g_SavegamePtr->items_0[i].count_1--;
                    if (!(g_SavegamePtr->items_0[i].count_1 & 0xFF))
                    {
                        g_SavegamePtr->items_0[i].id_0 = 0xFF;
                        g_SavegamePtr->inventoryItemSpaces_AB        = func_8004F190(g_SavegamePtr);
                    }
                }
            }

            return 1;
        }
    }

    return 0;
}

/** Does something with data of items and also something with map.
 * Used in:
 * `GameState_ItemScreens_Update`
 * `Inventory_PlayerItemScroll`
 */
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", func_8004EF48); // 0x8004EF48

// Unused?
void func_8004F10C(s32* arg0) // 0x8004F10C
{
    s32 i;

    g_SavegamePtr->inventoryItemSpaces_AB = func_8004F190(g_SavegamePtr);

    for (i = *arg0; i >= 0; i--)
    {
        if (g_SavegamePtr->items_0[i].id_0 != 0xFF)
        {
            *arg0 = i;
            return;
        }
    }

    *arg0 = 0;
}

/** Used in:
 * `func_8004EE94`
 * `func_8004F10C`
 */
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", func_8004F190); // 0x8004F190

void Gfx_Inventory_UnavailableMapText(s32 strIdx) // 0x0x8004F57C
{
    char* D_800262AC[2] =
    {
        "Too_dark_to_look_at\n\t\tthe_map_here.",
        "I_don't_have_the_map\n\t\tfor_this_place."
    };

    Gfx_StringSetPosition(30, 232);
    Gfx_StringSetColor(7);
    Gfx_StringDraw(D_800262AC[strIdx], 0x63);
}

// Unknown RODATA values.
static const u8  unk0 = 0x2A; // '*' as `char`.
static const s32 unk1 = 0;

void Inventory_DirectionalInputSet() // 0x8004F5DC
{
    if (g_ControllerPtrConst->field_20.sticks_0.leftY < -64 || g_ControllerPtrConst->field_20.sticks_0.leftY >= 64 ||
        g_ControllerPtrConst->field_20.sticks_0.leftX < -64 || g_ControllerPtrConst->field_20.sticks_0.leftX >= 64)
    {
        // Up.
        g_Inventory_IsUpClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickUp2;
        g_Inventory_IsUpPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickUp2;

        // Down.
        g_Inventory_IsDownClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickDown2;
        g_Inventory_IsDownPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickDown2;

        // Left.
        g_Inventory_IsLeftClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickLeft2;
        g_Inventory_IsLeftHeld    = g_ControllerPtrConst->btnsHeld_C     & ControllerFlag_LStickLeft2;
        g_Inventory_IsLeftPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickLeft2;

        // Right.
        g_Inventory_IsRightClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickRight2;
        g_Inventory_IsRightHeld    = g_ControllerPtrConst->btnsHeld_C     & ControllerFlag_LStickRight2;
        g_Inventory_IsRightPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickRight2;
    }
    else
    {
        // Up.
        g_Inventory_IsUpClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickUp;
        g_Inventory_IsUpPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickUp;

        // Down.
        g_Inventory_IsDownClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickDown;
        g_Inventory_IsDownPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickDown;

        // Left.
        g_Inventory_IsLeftClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickLeft;
        g_Inventory_IsLeftHeld    = g_ControllerPtrConst->btnsHeld_C     & ControllerFlag_LStickLeft;
        g_Inventory_IsLeftPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickLeft;

        // Right.
        g_Inventory_IsRightClicked = g_ControllerPtrConst->btnsClicked_10 & ControllerFlag_LStickRight;
        g_Inventory_IsRightHeld    = g_ControllerPtrConst->btnsHeld_C     & ControllerFlag_LStickRight;
        g_Inventory_IsRightPulsed  = g_ControllerPtrConst->btnsPulsed_18  & ControllerFlag_LStickRight;
    }
}

static const DVECTOR D_800262FC[] =
{
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0xFE00, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0800 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0200 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0200, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0200, 0x0000 }, { 0x0A00, 0x0800 },
    { 0x0200, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x0000, 0x0000 }, { 0x0000, 0x0000 },
    { 0x6147, 0x6F73 }, { 0x696C, 0x656E },
    { 0x745F, 0x6E61 }, { 0x006B, 0x0000 },
    { 0x6F50, 0x6B63 }, { 0x7465, 0x725F },
    { 0x6461, 0x6F69 }, { 0x0000, 0x0000 },
    { 0x6C46, 0x7361 }, { 0x6C68, 0x6769 },
    { 0x7468, 0x0000 }, { 0x6853, 0x746F },
    { 0x7567, 0x5F6E }, { 0x6873, 0x6C65 },
    { 0x736C, 0x0000 }, { 0x6952, 0x6C66 },
    { 0x5F65, 0x6873 }, { 0x6C65, 0x736C },
    { 0x0000, 0x0000 }, { 0x6148, 0x646E },
    { 0x7567, 0x5F6E }, { 0x7562, 0x6C6C },
    { 0x7465, 0x0073 }, { 0x7948, 0x6570 },
    { 0x5F72, 0x6C42 }, { 0x7361, 0x6574 },
    { 0x0072, 0x0000 }, { 0x6853, 0x746F },
    { 0x7567, 0x006E }, { 0x7548, 0x746E },
    { 0x6E69, 0x5F67 }, { 0x6972, 0x6C66 },
    { 0x0065, 0x0000 }, { 0x6148, 0x646E },
    { 0x7567, 0x006E }, { 0x7841, 0x0065 },
    { 0x614B, 0x6174 }, { 0x616E, 0x0000 },
    { 0x6843, 0x6961 }, { 0x736E, 0x7761 },
    { 0x0000, 0x0000 }, { 0x6148, 0x6D6D },
    { 0x7265, 0x0000 }, { 0x6F52, 0x6B63 },
    { 0x645F, 0x6972 }, { 0x6C6C, 0x0000 },
    { 0x7453, 0x6565 }, { 0x5F6C, 0x6970 },
    { 0x6570, 0x0000 }, { 0x694B, 0x6374 },
    { 0x6568, 0x5F6E }, { 0x6E6B, 0x6669 },
    { 0x0065, 0x0000 }, { 0x6944, 0x6B73 },
    { 0x6F5F, 0x5F66 }, { 0x754F, 0x6F72 },
    { 0x6F62, 0x6F72 }, { 0x0073, 0x0000 },
    { 0x6144, 0x6767 }, { 0x7265, 0x6F5F },
    { 0x5F66, 0x654D }, { 0x636C, 0x6968 },
    { 0x726F, 0x0000 }, { 0x6E41, 0x686B },
    { 0x0000, 0x0000 }, { 0x7243, 0x7365 },
    { 0x5F74, 0x666F }, { 0x4D5F, 0x7265 },
    { 0x7563, 0x7972 }, { 0x0000, 0x0000 },
    { 0x6D41, 0x6C75 }, { 0x7465, 0x6F5F },
    { 0x5F66, 0x6F53 }, { 0x6F6C, 0x6F6D },
    { 0x006E, 0x0000 }, { 0x7453, 0x6E6F },
    { 0x5F65, 0x666F }, { 0x745F, 0x6D69 },
    { 0x0065, 0x0000 }, { 0x6952, 0x676E },
    { 0x6F5F, 0x5F66 }, { 0x6F63, 0x746E },
    { 0x6172, 0x7463 }, { 0x0000, 0x0000 },
    { 0x6143, 0x656D }, { 0x6172, 0x0000 },
    { 0x6353, 0x6572 }, { 0x6477, 0x6972 },
    { 0x6576, 0x0072 }, { 0x6C50, 0x6569 },
    { 0x7372, 0x0000 }, { 0x6942, 0x6472 },
    { 0x635F, 0x6761 }, { 0x5F65, 0x656B },
    { 0x0079, 0x0000 }, { 0x6F4D, 0x6F74 },
    { 0x6372, 0x6379 }, { 0x656C, 0x6B5F },
    { 0x7965, 0x0000 }, { 0x614D, 0x6E67 },
    { 0x7465, 0x0000 }, { 0x6153, 0x6566 },
    { 0x6B5F, 0x7965 }, { 0x0000, 0x0000 },
    { 0x6552, 0x6563 }, { 0x7069, 0x0074 },
    { 0x614B, 0x6675 }, { 0x616D, 0x6E6E },
    { 0x6B5F, 0x7965 }, { 0x0000, 0x0000 },
    { 0x6956, 0x6564 }, { 0x5F6F, 0x6174 },
    { 0x6570, 0x0000 }, { 0x694C, 0x6867 },
    { 0x6574, 0x0072 }, { 0x6944, 0x6973 },
    { 0x666E, 0x6365 }, { 0x6974, 0x676E },
    { 0x615F, 0x636C }, { 0x686F, 0x6C6F },
    { 0x0000, 0x0000 }, { 0x6C42, 0x6F6F },
    { 0x5F64, 0x6170 }, { 0x6B63, 0x0000 },
    { 0x6C50, 0x7461 }, { 0x5F65, 0x666F },
    { 0x5B5F, 0x7551 }, { 0x6565, 0x5D6E },
    { 0x0000, 0x0000 }, { 0x6C50, 0x7461 },
    { 0x5F65, 0x666F }, { 0x5B5F, 0x6143 },
    { 0x5D74, 0x0000 }, { 0x6C50, 0x7461 },
    { 0x5F65, 0x666F }, { 0x5B5F, 0x6148 },
    { 0x7474, 0x7265 }, { 0x005D, 0x0000 },
    { 0x6C50, 0x7461 }, { 0x5F65, 0x666F },
    { 0x5B5F, 0x7554 }, { 0x7472, 0x656C },
    { 0x005D, 0x0000 }, { 0x6E55, 0x6E6B },
    { 0x776F, 0x5F6E }, { 0x696C, 0x7571 },
    { 0x6469, 0x0000 }, { 0x6C50, 0x7361 },
    { 0x6974, 0x5F63 }, { 0x6F62, 0x7474 },
    { 0x656C, 0x0000 }, { 0x465B, 0x616C },
    { 0x7275, 0x736F }, { 0x005D, 0x0000 },
    { 0x7552, 0x6262 }, { 0x7265, 0x625F },
    { 0x6C61, 0x006C }, { 0x6953, 0x766C },
    { 0x7265, 0x6D5F }, { 0x6465, 0x6C61 },
    { 0x696C, 0x6E6F }, { 0x0000, 0x0000 },
    { 0x6F47, 0x646C }, { 0x6D5F, 0x6465 },
    { 0x6C61, 0x696C }, { 0x6E6F, 0x0000 },
    { 0x6843, 0x6D65 }, { 0x6369, 0x6C61 },
    { 0x0000, 0x0000 }, { 0x6843, 0x6E61 },
    { 0x656E, 0x696C }, { 0x676E, 0x735F },
    { 0x6F74, 0x656E }, { 0x0000, 0x0000 },
    { 0x6553, 0x6577 }, { 0x5F72, 0x7865 },
    { 0x7469, 0x6B5F }, { 0x7965, 0x0000 },
    { 0x0020, 0x0000 }, { 0x6950, 0x7463 },
    { 0x7275, 0x5F65 }, { 0x6163, 0x6472 },
    { 0x0000, 0x0000 }, { 0x5F41, 0x6F6E },
    { 0x6574, 0x5B5F }, { 0x6F44, 0x6867 },
    { 0x756F, 0x6573 }, { 0x005D, 0x0000 },
    { 0x5F41, 0x6F6E }, { 0x6574, 0x5B5F },
    { 0x6F54, 0x735F }, { 0x6863, 0x6F6F },
    { 0x5D6C, 0x0000 }, { 0x654B, 0x5F79 },
    { 0x666F, 0x5B5F }, { 0x7241, 0x7461 },
    { 0x6F72, 0x5D6E }, { 0x0000, 0x0000 },
    { 0x654B, 0x5F79 }, { 0x666F, 0x5B5F },
    { 0x6542, 0x6874 }, { 0x726F, 0x005D },
    { 0x654B, 0x5F79 }, { 0x666F, 0x5B5F },
    { 0x6850, 0x6C61 }, { 0x6765, 0x005D },
    { 0x654B, 0x5F79 }, { 0x666F, 0x5B5F },
    { 0x6148, 0x6967 }, { 0x6874, 0x005D },
    { 0x654B, 0x5F79 }, { 0x666F, 0x5B5F },
    { 0x704F, 0x6968 }, { 0x6C65, 0x005D },
    { 0x6553, 0x6577 }, { 0x5F72, 0x656B },
    { 0x0079, 0x0000 }, { 0x6E41, 0x6974 },
    { 0x7571, 0x5F65 }, { 0x6873, 0x706F },
    { 0x6B5F, 0x7965 }, { 0x0000, 0x0000 },
    { 0x7845, 0x6D61 }, { 0x6E69, 0x7461 },
    { 0x6F69, 0x5F6E }, { 0x6F72, 0x6D6F },
    { 0x6B5F, 0x7965 }, { 0x0000, 0x0000 },
    { 0x6142, 0x6573 }, { 0x656D, 0x746E },
    { 0x735F, 0x6F74 }, { 0x6572, 0x6F72 },
    { 0x6D6F, 0x6B5F }, { 0x7965, 0x0000 },
    { 0x6142, 0x6573 }, { 0x656D, 0x746E },
    { 0x6B5F, 0x7965 }, { 0x0000, 0x0000 },
    { 0x7244, 0x7761 }, { 0x7262, 0x6469 },
    { 0x6567, 0x6B5F }, { 0x7965, 0x0000 },
    { 0x2E4B, 0x475F }, { 0x726F, 0x6F64 },
    { 0x5F6E, 0x656B }, { 0x0079, 0x0000 },
    { 0x6C43, 0x7361 }, { 0x7273, 0x6F6F },
    { 0x5F6D, 0x656B }, { 0x0079, 0x0000 },
    { 0x694C, 0x7262 }, { 0x7261, 0x5F79 },
    { 0x6572, 0x6573 }, { 0x7672, 0x5F65 },
    { 0x656B, 0x0079 }, { 0x654B, 0x5F79 },
    { 0x666F, 0x5B5F }, { 0x6353, 0x7261 },
    { 0x6365, 0x6F72 }, { 0x5D77, 0x0000 },
    { 0x654B, 0x5F79 }, { 0x666F, 0x5B5F },
    { 0x6F57, 0x646F }, { 0x616D, 0x5D6E },
    { 0x0000, 0x0000 }, { 0x654B, 0x5F79 },
    { 0x666F, 0x5B5F }, { 0x694C, 0x6E6F },
    { 0x005D, 0x0000 }, { 0x6F48, 0x7375 },
    { 0x5F65, 0x656B }, { 0x0079, 0x0000 },
    { 0x6F4C, 0x6262 }, { 0x5F79, 0x656B },
    { 0x0079, 0x0000 }, { 0x6D41, 0x6F70 },
    { 0x6C75, 0x2865 }, { 0x2973, 0x0000 },
    { 0x6946, 0x7372 }, { 0x5F74, 0x6961 },
    { 0x5F64, 0x696B }, { 0x2874, 0x2973 },
    { 0x0000, 0x0000 }, { 0x6548, 0x6C61 },
    { 0x6874, 0x645F }, { 0x6972, 0x6B6E },
    { 0x7328, 0x0029 }, { 0x7546, 0x6C65 },
    { 0x665F, 0x726F }, { 0x635F, 0x6168 },
    { 0x6E69, 0x6173 }, { 0x7377, 0x615F },
    { 0x646E, 0x090A }, { 0x0909, 0x0909 },
    { 0x6F72, 0x6B63 }, { 0x645F, 0x6972 },
    { 0x6C6C, 0x2E73 }, { 0x0000, 0x0000 },
    { 0x6F50, 0x7472 }, { 0x6261, 0x656C },
    { 0x725F, 0x6461 }, { 0x6F69, 0x745F },
    { 0x6168, 0x0A74 }, { 0x0909, 0x0909 },
    { 0x6509, 0x696D }, { 0x7374, 0x735F },
    { 0x6174, 0x6974 }, { 0x0A63, 0x0909 },
    { 0x0909, 0x7709 }, { 0x6568, 0x5F6E },
    { 0x6F6D, 0x736E }, { 0x6574, 0x7372 },
    { 0x615F, 0x6572 }, { 0x6E5F, 0x6165 },
    { 0x2E72, 0x0000 }, { 0x6E4F, 0x5F65 },
    { 0x6F74, 0x6375 }, { 0x5F68, 0x6E6F },
    { 0x6F2F, 0x6666 }, { 0x735F, 0x6977 },
    { 0x6374, 0x2E68 }, { 0x090A, 0x0909 },
    { 0x0909, 0x6E49 }, { 0x745F, 0x6568 },
    { 0x635F, 0x6568 }, { 0x7473, 0x705F },
    { 0x636F, 0x656B }, { 0x2E74, 0x0000 },
    { 0x6D41, 0x6F6D }, { 0x665F, 0x726F },
    { 0x745F, 0x6568 }, { 0x735F, 0x6F68 },
    { 0x6774, 0x6E75 }, { 0x002E, 0x0000 },
    { 0x6D41, 0x6F6D }, { 0x665F, 0x726F },
    { 0x745F, 0x6568 }, { 0x685F, 0x6E75 },
    { 0x6974, 0x676E }, { 0x725F, 0x6669 },
    { 0x656C, 0x002E }, { 0x6D41, 0x6F6D },
    { 0x665F, 0x726F }, { 0x745F, 0x6568 },
    { 0x685F, 0x6E61 }, { 0x6764, 0x6E75 },
    { 0x002E, 0x0000 }, { 0x6948, 0x6867 },
    { 0x702D, 0x776F }, { 0x7265, 0x6465 },
    { 0x685F, 0x6E61 }, { 0x6764, 0x6E75 },
    { 0x090A, 0x0909 }, { 0x0909, 0x6977 },
    { 0x6874, 0x695F }, { 0x666E, 0x6172 },
    { 0x6572, 0x5F64 }, { 0x6373, 0x706F },
    { 0x0A65, 0x0909 }, { 0x0909, 0x6109 },
    { 0x646E, 0x755F }, { 0x6C6E, 0x6D69 },
    { 0x7469, 0x6465 }, { 0x625F, 0x6C75 },
    { 0x656C, 0x7374 }, { 0x002E, 0x0000 },
    { 0x6946, 0x6572 }, { 0x5F73, 0x6E69 },
    { 0x615F, 0x775F }, { 0x6469, 0x5F65 },
    { 0x6172, 0x6964 }, { 0x7375, 0x0A2E },
    { 0x0909, 0x0909 }, { 0x4809, 0x6C6F },
    { 0x7364, 0x755F }, { 0x5F70, 0x6F74 },
    { 0x365F, 0x725F }, { 0x756F, 0x646E },
    { 0x2E73, 0x0000 }, { 0x6F48, 0x646C },
    { 0x5F73, 0x7075 }, { 0x745F, 0x5F6F },
    { 0x5F36, 0x6F72 }, { 0x6E75, 0x7364 },
    { 0x002E, 0x0000 }, { 0x6148, 0x646E },
    { 0x7567, 0x5F6E }, { 0x6572, 0x6563 },
    { 0x7669, 0x6465 }, { 0x665F, 0x6F72 },
    { 0x5F6D, 0x7943 }, { 0x6962, 0x2E6C },
    { 0x090A, 0x0909 }, { 0x0909, 0x6F48 },
    { 0x646C, 0x5F73 }, { 0x7075, 0x745F },
    { 0x5F6F, 0x3531 }, { 0x725F, 0x756F },
    { 0x646E, 0x2E73 }, { 0x0000, 0x0000 },
    { 0x6D53, 0x6C61 }, { 0x5F6C, 0x6E6F },
    { 0x5F65, 0x6168 }, { 0x646E, 0x615F },
    { 0x6578, 0x0A2E }, { 0x0909, 0x0909 },
    { 0x4D09, 0x646F }, { 0x7265, 0x7461 },
    { 0x6C65, 0x5F79 }, { 0x6665, 0x6566 },
    { 0x7463, 0x7669 }, { 0x0A65, 0x0909 },
    { 0x0909, 0x6109 }, { 0x5F73, 0x5F61 },
    { 0x6577, 0x7061 }, { 0x6E6F, 0x002E },
    { 0x7254, 0x6461 }, { 0x7469, 0x6F69 },
    { 0x616E, 0x5F6C }, { 0x6973, 0x676E },
    { 0x656C, 0x655F }, { 0x6764, 0x6465 },
    { 0x090A, 0x0909 }, { 0x0909, 0x614A },
    { 0x6170, 0x656E }, { 0x6573, 0x625F },
    { 0x616C, 0x6564 }, { 0x002E, 0x0000 },
    { 0x6F50, 0x6577 }, { 0x5F72, 0x6F74 },
    { 0x6C6F, 0x755F }, { 0x6573, 0x5F64 },
    { 0x6F66, 0x5F72 }, { 0x7563, 0x7474 },
    { 0x6E69, 0x0A67 }, { 0x0909, 0x0909 },
    { 0x6409, 0x776F }, { 0x5F6E, 0x7274 },
    { 0x6565, 0x2C73 }, { 0x655F, 0x6374 },
    { 0x2C2E, 0x685F }, { 0x6769, 0x6C68 },
    { 0x5F79, 0x6564 }, { 0x6461, 0x796C },
    { 0x002E, 0x0000 }, { 0x6D45, 0x7265 },
    { 0x6567, 0x636E }, { 0x5F79, 0x6168 },
    { 0x6D6D, 0x7265 }, { 0x0A2E, 0x0909 },
    { 0x0909, 0x4809 }, { 0x6769, 0x6C68 },
    { 0x5F79, 0x6164 }, { 0x616D, 0x6967 },
    { 0x676E, 0x0A2C }, { 0x0909, 0x0909 },
    { 0x6209, 0x7475 }, { 0x685F, 0x7261 },
    { 0x5F64, 0x6F74 }, { 0x755F, 0x6573 },
    { 0x002E, 0x0000 }, { 0x5F41, 0x6F74 },
    { 0x6C6F, 0x755F }, { 0x6573, 0x5F64 },
    { 0x6E69, 0x725F }, { 0x616F, 0x5F64 },
    { 0x6F63, 0x736E }, { 0x7274, 0x6375 },
    { 0x6974, 0x6E6F }, { 0x090A, 0x0909 },
    { 0x0909, 0x6F74 }, { 0x635F, 0x6572 },
    { 0x7461, 0x5F65 }, { 0x6F68, 0x656C },
    { 0x5F73, 0x6E69 }, { 0x745F, 0x6568 },
    { 0x725F, 0x616F }, { 0x5F64, 0x6F66 },
    { 0x0A72, 0x0909 }, { 0x0909, 0x7009 },
    { 0x6C6F, 0x7365 }, { 0x002E, 0x0000 },
    { 0x2733, 0x6C5F }, { 0x6E6F, 0x5F67 },
    { 0x7473, 0x6565 }, { 0x5F6C, 0x6970 },
    { 0x6570, 0x0A2E }, { 0x0909, 0x0909 },
    { 0x4C09, 0x6E6F }, { 0x5F67, 0x6172 },
    { 0x676E, 0x5F65 }, { 0x7562, 0x5F74 },
    { 0x666F, 0x6C5F }, { 0x6D69, 0x7469 },
    { 0x6465, 0x755F }, { 0x6573, 0x002E },
    { 0x6148, 0x6472 }, { 0x745F, 0x5F6F },
    { 0x7375, 0x2C65 }, { 0x090A, 0x0909 },
    { 0x0909, 0x7562 }, { 0x5F74, 0x6562 },
    { 0x7474, 0x7265 }, { 0x745F, 0x6168 },
    { 0x5F6E, 0x6F6E }, { 0x6874, 0x6E69 },
    { 0x2E67, 0x0000 }, { 0x6952, 0x676E },
    { 0x6F5F, 0x5F66 }, { 0x5F61, 0x6E73 },
    { 0x6B61, 0x5F65 }, { 0x6962, 0x6974 },
    { 0x676E, 0x090A }, { 0x0909, 0x0909 },
    { 0x7469, 0x7327 }, { 0x6F5F, 0x6E77 },
    { 0x745F, 0x6961 }, { 0x2E6C, 0x0000 },
    { 0x6854, 0x5F65 }, { 0x6E61, 0x6963 },
    { 0x6E65, 0x5F74 }, { 0x6164, 0x6767 },
    { 0x7265, 0x090A }, { 0x0909, 0x0909 },
    { 0x616E, 0x656D }, { 0x5F64, 0x6661 },
    { 0x6574, 0x5F72 }, { 0x6874, 0x5F65 },
    { 0x614D, 0x6967 }, { 0x002E, 0x0000 },
    { 0x6C45, 0x696C }, { 0x7470, 0x6369 },
    { 0x6C61, 0x745F }, { 0x6C61, 0x7369 },
    { 0x616D, 0x0A6E }, { 0x0909, 0x0909 },
    { 0x7709, 0x7469 }, { 0x5F68, 0x5F61 },
    { 0x7263, 0x736F }, { 0x5F73, 0x6E69 },
    { 0x6973, 0x6564 }, { 0x002E, 0x0000 },
    { 0x6E53, 0x6B61 }, { 0x5F65, 0x6E69 },
    { 0x745F, 0x6568 }, { 0x735F, 0x6D79 },
    { 0x6F62, 0x5F6C }, { 0x666F, 0x090A },
    { 0x0909, 0x0909 }, { 0x656D, 0x6372 },
    { 0x7275, 0x5F79 }, { 0x6973, 0x6E67 },
    { 0x6669, 0x6569 }, { 0x5F73, 0x6C61 },
    { 0x6863, 0x6D65 }, { 0x2E79, 0x0000 },
    { 0x6854, 0x5F65 }, { 0x6D61, 0x6C75 },
    { 0x7465, 0x695F }, { 0x5F73, 0x5F61 },
    { 0x7473, 0x7261 }, { 0x735F, 0x6168 },
    { 0x6570, 0x0A64 }, { 0x0909, 0x0909 },
    { 0x6F09, 0x6A62 }, { 0x6365, 0x5F74 },
    { 0x6977, 0x6874 }, { 0x365F, 0x635F },
    { 0x726F, 0x656E }, { 0x7372, 0x6E5F },
    { 0x6D61, 0x6465 }, { 0x090A, 0x0909 },
    { 0x0909, 0x6661 }, { 0x6574, 0x5F72 },
    { 0x6874, 0x5F65 }, { 0x6E61, 0x6963 },
    { 0x6E65, 0x5F74 }, { 0x616D, 0x6967 },
    { 0x6963, 0x6E61 }, { 0x002E, 0x0000 },
    { 0x614C, 0x6772 }, { 0x5F65, 0x7473 },
    { 0x6E6F, 0x5F65 }, { 0x6977, 0x6874 },
    { 0x635F, 0x6F6C }, { 0x6B63, 0x662D },
    { 0x6361, 0x0A65 }, { 0x0909, 0x0909 },
    { 0x6409, 0x7365 }, { 0x6769, 0x5F6E },
    { 0x6E6F, 0x705F }, { 0x6C69, 0x616C },
    { 0x5F72, 0x6977 }, { 0x6874, 0x615F },
    { 0x7473, 0x6F72 }, { 0x6F6C, 0x7967 },
    { 0x090A, 0x0909 }, { 0x0909, 0x6863 },
    { 0x7261, 0x5F74 }, { 0x6168, 0x676E },
    { 0x6E69, 0x5F67 }, { 0x7266, 0x6D6F },
    { 0x695F, 0x2E74 }, { 0x0000, 0x0000 },
    { 0x7552, 0x7473 }, { 0x6369, 0x5F2C },
    { 0x6568, 0x7466 }, { 0x2D79, 0x6F6C },
    { 0x6B6F, 0x6E69 }, { 0x5F67, 0x6972 },
    { 0x676E, 0x090A }, { 0x0909, 0x0909 },
    { 0x666F, 0x755F }, { 0x6B6E, 0x6F6E },
    { 0x6E77, 0x6D5F }, { 0x7461, 0x7265 },
    { 0x6169, 0x2E6C }, { 0x0000, 0x0000 },
    { 0x6143, 0x656D }, { 0x6172, 0x775F },
    { 0x7469, 0x5F68 }, { 0x6C66, 0x7361 },
    { 0x2E68, 0x0000 }, { 0x6F54, 0x6C6F },
    { 0x665F, 0x726F }, { 0x735F, 0x7263 },
    { 0x7765, 0x2E73 }, { 0x090A, 0x0909 },
    { 0x0909, 0x7552 }, { 0x7473, 0x6465 },
    { 0x5F2C, 0x7562 }, { 0x5F74, 0x7375 },
    { 0x6261, 0x656C }, { 0x002E, 0x0000 },
    { 0x6F54, 0x6C6F }, { 0x745F, 0x5F6F },
    { 0x7375, 0x5F65 }, { 0x6E6F, 0x090A },
    { 0x0909, 0x0909 }, { 0x656D, 0x6174 },
    { 0x5F6C, 0x6E61 }, { 0x5F64, 0x6977 },
    { 0x6572, 0x2E73 }, { 0x090A, 0x0909 },
    { 0x0909, 0x7552 }, { 0x7473, 0x6465 },
    { 0x625F, 0x7475 }, { 0x755F, 0x6173 },
    { 0x6C62, 0x2E65 }, { 0x0000, 0x0000 },
    { 0x6942, 0x6472 }, { 0x635F, 0x6761 },
    { 0x5F65, 0x656B }, { 0x5F79, 0x6977 },
    { 0x6874, 0x090A }, { 0x0909, 0x0909 },
    { 0x6E65, 0x7267 }, { 0x7661, 0x6465 },
    { 0x685F, 0x6E61 }, { 0x6C64, 0x2E65 },
    { 0x0000, 0x0000 }, { 0x654B, 0x5F79 },
    { 0x6F74, 0x615F }, { 0x5F6E, 0x6C6F },
    { 0x5F64, 0x6F6D }, { 0x6F74, 0x6372 },
    { 0x6379, 0x656C }, { 0x0A2C, 0x0909 },
    { 0x0909, 0x7709 }, { 0x6968, 0x6863 },
    { 0x775F, 0x7361 }, { 0x645F, 0x6F72 },
    { 0x7070, 0x6465 }, { 0x625F, 0x7465 },
    { 0x6577, 0x6E65 }, { 0x745F, 0x6568 },
    { 0x090A, 0x0909 }, { 0x0909, 0x6C66 },
    { 0x6F6F, 0x6272 }, { 0x616F, 0x6472 },
    { 0x5F73, 0x6E69 }, { 0x745F, 0x6568 },
    { 0x6D5F, 0x746F }, { 0x6C65, 0x725F },
    { 0x6F6F, 0x2E6D }, { 0x0000, 0x0000 },
    { 0x6F4C, 0x676E }, { 0x5F2C, 0x6874 },
    { 0x6E69, 0x6D5F }, { 0x6761, 0x656E },
    { 0x6974, 0x5F63 }, { 0x6F72, 0x0A64 },
    { 0x0909, 0x0909 }, { 0x7709, 0x7469 },
    { 0x5F68, 0x5F61 }, { 0x7473, 0x6972 },
    { 0x676E, 0x615F }, { 0x7474, 0x6361 },
    { 0x6568, 0x2C64 }, { 0x090A, 0x0909 },
    { 0x0909, 0x6E69 }, { 0x745F, 0x6568 },
    { 0x6D5F, 0x746F }, { 0x6C65, 0x6F5F },
    { 0x6666, 0x6369 }, { 0x2E65, 0x0000 },
    { 0x654B, 0x5F79 }, { 0x6F74, 0x745F },
    { 0x6568, 0x735F }, { 0x6661, 0x2C65 },
    { 0x090A, 0x0909 }, { 0x0909, 0x6F66 },
    { 0x6E75, 0x5F64 }, { 0x7461, 0x495F },
    { 0x646E, 0x6169 }, { 0x5F6E, 0x7552 },
    { 0x6E6E, 0x7265 }, { 0x090A, 0x0909 },
    { 0x0909, 0x6547 }, { 0x656E, 0x6172 },
    { 0x5F6C, 0x7453 }, { 0x726F, 0x2E65 },
    { 0x0000, 0x0000 }, { 0x6552, 0x6563 },
    { 0x7069, 0x5F74 }, { 0x7266, 0x6D6F },
    { 0x475F, 0x6E65 }, { 0x7265, 0x6C61 },
    { 0x535F, 0x6F74 }, { 0x6572, 0x0A2C },
    { 0x0909, 0x0909 }, { 0x7409, 0x6F68 },
    { 0x6775, 0x7468 }, { 0x745F, 0x5F6F },
    { 0x6168, 0x6576 }, { 0x625F, 0x6565 },
    { 0x5F6E, 0x7264 }, { 0x706F, 0x6570 },
    { 0x0A64, 0x0909 }, { 0x0909, 0x6209 },
    { 0x5F79, 0x614B }, { 0x6675, 0x616D },
    { 0x6E6E, 0x002E }, { 0x5F41, 0x335B },
    { 0x5F5D, 0x7369 }, { 0x775F, 0x6972 },
    { 0x7474, 0x6E65 }, { 0x6F5F, 0x5F6E },
    { 0x6874, 0x5F65 }, { 0x6174, 0x2E67 },
    { 0x090A, 0x0909 }, { 0x0909, 0x6854 },
    { 0x5F65, 0x656B }, { 0x5F79, 0x6177 },
    { 0x5F73, 0x6874 }, { 0x756F, 0x6867 },
    { 0x5F74, 0x6F74 }, { 0x685F, 0x7661 },
    { 0x0A65, 0x0909 }, { 0x0909, 0x6209 },
    { 0x6565, 0x5F6E }, { 0x7264, 0x706F },
    { 0x6570, 0x5F64 }, { 0x7962, 0x4B5F },
    { 0x7561, 0x6D66 }, { 0x6E61, 0x2E6E },
    { 0x0000, 0x0000 }, { 0x6F4E, 0x6874 },
    { 0x6E69, 0x5F67 }, { 0x6E6F, 0x745F },
    { 0x6568, 0x6C5F }, { 0x6261, 0x6C65 },
    { 0x0A2E, 0x0909 }, { 0x0909, 0x4609 },
    { 0x756F, 0x646E }, { 0x6F5F, 0x5F6E },
    { 0x6E32, 0x5F64 }, { 0x6C66, 0x6F6F },
    { 0x0A72, 0x0909 }, { 0x0909, 0x6809 },
    { 0x736F, 0x6970 }, { 0x6174, 0x5F6C },
    { 0x6162, 0x6573 }, { 0x656D, 0x746E },
    { 0x002E, 0x0000 }, { 0x694F, 0x5F6C },
    { 0x696C, 0x6867 }, { 0x6574, 0x5F72 },
    { 0x6F66, 0x6E75 }, { 0x5F64, 0x6E69 },
    { 0x525F, 0x6F6F }, { 0x5F6D, 0x3032 },
    { 0x2E31, 0x0000 }, { 0x7349, 0x706F },
    { 0x6F72, 0x7970 }, { 0x5F6C, 0x6C61 },
    { 0x6F63, 0x6F68 }, { 0x5F6C, 0x6F62 },
    { 0x7474, 0x656C }, { 0x0A2C, 0x0909 },
    { 0x0909, 0x6609 }, { 0x756F, 0x646E },
    { 0x695F, 0x5F6E }, { 0x4349, 0x5F55 },
    { 0x7461, 0x745F }, { 0x6568, 0x685F },
    { 0x736F, 0x6970 }, { 0x6174, 0x2E6C },
    { 0x0000, 0x0000 }, { 0x3032, 0x6D30 },
    { 0x5F6C, 0x6C62 }, { 0x6F6F, 0x5F64 },
    { 0x6170, 0x6B63 }, { 0x0A2E, 0x0909 },
    { 0x0909, 0x4609 }, { 0x756F, 0x646E },
    { 0x695F, 0x5F6E }, { 0x6874, 0x5F65 },
    { 0x6F68, 0x7073 }, { 0x7469, 0x6C61 },
    { 0x090A, 0x0909 }, { 0x0909, 0x7473 },
    { 0x726F, 0x6761 }, { 0x5F65, 0x6F72 },
    { 0x6D6F, 0x002E }, { 0x7153, 0x6175 },
    { 0x6572, 0x5F2C }, { 0x6572, 0x5F64 },
    { 0x6C70, 0x7461 }, { 0x0A65, 0x0909 },
    { 0x0909, 0x7709 }, { 0x7469, 0x5F68 },
    { 0x5F61, 0x6970 }, { 0x7463, 0x7275 },
    { 0x5F65, 0x666F }, { 0x090A, 0x0909 },
    { 0x0909, 0x5F61 }, { 0x515B, 0x6575 },
    { 0x6E65, 0x6F5F }, { 0x5F66, 0x6548 },
    { 0x7261, 0x7374 }, { 0x5D2E, 0x0000 },
    { 0x7153, 0x6175 }, { 0x6572, 0x5F2C },
    { 0x6579, 0x6C6C }, { 0x776F, 0x705F },
    { 0x616C, 0x6574 }, { 0x090A, 0x0909 },
    { 0x0909, 0x6977 }, { 0x6874, 0x615F },
    { 0x705F, 0x6369 }, { 0x7574, 0x6572 },
    { 0x6F5F, 0x0A66 }, { 0x0909, 0x0909 },
    { 0x6109, 0x5B5F }, { 0x6843, 0x7365 },
    { 0x6968, 0x6572 }, { 0x435F, 0x7461 },
    { 0x5D2E, 0x0000 }, { 0x7153, 0x6175 },
    { 0x6572, 0x5F2C }, { 0x7267, 0x6565 },
    { 0x5F6E, 0x6C70 }, { 0x7461, 0x0A65 },
    { 0x0909, 0x0909 }, { 0x7709, 0x7469 },
    { 0x5F68, 0x5F61 }, { 0x6970, 0x7463 },
    { 0x7275, 0x5F65 }, { 0x666F, 0x090A },
    { 0x0909, 0x0909 }, { 0x5F61, 0x4D5B },
    { 0x6461, 0x485F }, { 0x7461, 0x6574 },
    { 0x2E72, 0x005D }, { 0x7153, 0x6175 },
    { 0x6572, 0x5F2C }, { 0x6C62, 0x6575 },
    { 0x705F, 0x616C }, { 0x6574, 0x090A },
    { 0x0909, 0x0909 }, { 0x6977, 0x6874 },
    { 0x615F, 0x705F }, { 0x6369, 0x7574 },
    { 0x6572, 0x6F5F }, { 0x0A66, 0x0909 },
    { 0x0909, 0x6109 }, { 0x5B5F, 0x6F4D },
    { 0x6B63, 0x545F }, { 0x7275, 0x6C74 },
    { 0x2E65, 0x005D }, { 0x6552, 0x5F64 },
    { 0x696C, 0x7571 }, { 0x6469, 0x665F },
    { 0x756F, 0x646E }, { 0x695F, 0x0A6E },
    { 0x0909, 0x0909 }, { 0x6109, 0x625F },
    { 0x6F72, 0x656B }, { 0x5F6E, 0x6976 },
    { 0x6C61, 0x695F }, { 0x5F6E, 0x6874 },
    { 0x0A65, 0x0909 }, { 0x0909, 0x4809 },
    { 0x736F, 0x6970 }, { 0x6174, 0x5F6C },
    { 0x6944, 0x6572 }, { 0x7463, 0x726F },
    { 0x7327, 0x725F }, { 0x6F6F, 0x2E6D },
    { 0x0000, 0x0000 }, { 0x6D45, 0x7470 },
    { 0x5F79, 0x6F62 }, { 0x7474, 0x656C },
    { 0x665F, 0x756F }, { 0x646E, 0x090A },
    { 0x0909, 0x0909 }, { 0x6E69, 0x745F },
    { 0x6568, 0x6B5F }, { 0x7469, 0x6863 },
    { 0x6E65, 0x090A }, { 0x0909, 0x0909 },
    { 0x666F, 0x745F }, { 0x6568, 0x685F },
    { 0x736F, 0x6970 }, { 0x6174, 0x2E6C },
    { 0x0000, 0x0000 }, { 0x7950, 0x6172 },
    { 0x696D, 0x5F64 }, { 0x6873, 0x7061 },
    { 0x6465, 0x6F5F }, { 0x6A62, 0x6365 },
    { 0x5F74, 0x6F66 }, { 0x6E75, 0x0A64 },
    { 0x0909, 0x0909 }, { 0x6909, 0x5F6E },
    { 0x6874, 0x5F65 }, { 0x6863, 0x7275 },
    { 0x6863, 0x0A2E }, { 0x0909, 0x0909 },
    { 0x5009, 0x7275 }, { 0x6F70, 0x6573 },
    { 0x615F, 0x646E }, { 0x755F, 0x6573 },
    { 0x755F, 0x6B6E }, { 0x6F6E, 0x6E77 },
    { 0x002E, 0x0000 }, { 0x6C46, 0x726F },
    { 0x7365, 0x6563 }, { 0x746E, 0x705F },
    { 0x6E69, 0x5F6B }, { 0x7572, 0x6262 },
    { 0x7265, 0x625F }, { 0x6C61, 0x0A6C },
    { 0x0909, 0x0909 }, { 0x7509, 0x6573 },
    { 0x5F64, 0x7962 }, { 0x635F, 0x6968 },
    { 0x646C, 0x6572 }, { 0x2E6E, 0x0000 },
    { 0x5F41, 0x6970 }, { 0x7463, 0x7275 },
    { 0x5F65, 0x666F }, { 0x615F, 0x635F },
    { 0x6F6C, 0x6B63 }, { 0x745F, 0x776F },
    { 0x7265, 0x090A }, { 0x0909, 0x0909 },
    { 0x7369, 0x655F }, { 0x676E, 0x6172 },
    { 0x6576, 0x5F64 }, { 0x6E6F, 0x745F },
    { 0x6568, 0x735F }, { 0x7275, 0x6166 },
    { 0x6563, 0x0A2E }, { 0x0909, 0x0909 },
    { 0x4609, 0x756F }, { 0x646E, 0x695F },
    { 0x5F6E, 0x6874 }, { 0x5F65, 0x756D },
    { 0x6973, 0x5F63 }, { 0x6F72, 0x6D6F },
    { 0x002E, 0x0000 }, { 0x5F41, 0x6970 },
    { 0x7463, 0x7275 }, { 0x5F65, 0x666F },
    { 0x615F, 0x635F }, { 0x6F6C, 0x6B63 },
    { 0x745F, 0x776F }, { 0x7265, 0x090A },
    { 0x0909, 0x0909 }, { 0x7369, 0x655F },
    { 0x676E, 0x6172 }, { 0x6576, 0x5F64 },
    { 0x6E6F, 0x745F }, { 0x6568, 0x735F },
    { 0x7275, 0x6166 }, { 0x6563, 0x0A2E },
    { 0x0909, 0x0909 }, { 0x4609, 0x756F },
    { 0x646E, 0x695F }, { 0x5F6E, 0x6874 },
    { 0x5F65, 0x6863 }, { 0x6D65, 0x7369 },
    { 0x7274, 0x5F79 }, { 0x616C, 0x2E62 },
    { 0x0000, 0x0000 }, { 0x6854, 0x5F65 },
    { 0x616C, 0x6562 }, { 0x5F6C, 0x6572 },
    { 0x6461, 0x2C73 }, { 0x5B5F, 0x6F43 },
    { 0x636E, 0x6E65 }, { 0x7274, 0x7461 },
    { 0x6465, 0x090A }, { 0x0909, 0x0909 },
    { 0x7968, 0x7264 }, { 0x636F, 0x6C68 },
    { 0x726F, 0x6369 }, { 0x615F, 0x6963 },
    { 0x2E64, 0x5F5D }, { 0x6F46, 0x6E75 },
    { 0x5F64, 0x6E69 }, { 0x090A, 0x0909 },
    { 0x0909, 0x6874 }, { 0x5F65, 0x616C },
    { 0x5F62, 0x7165 }, { 0x6975, 0x6D70 },
    { 0x6E65, 0x5F74 }, { 0x6F72, 0x6D6F },
    { 0x002E, 0x0000 }, { 0x5F41, 0x796D },
    { 0x7473, 0x6369 }, { 0x6C61, 0x735F },
    { 0x6F74, 0x656E }, { 0x705F, 0x736F },
    { 0x6573, 0x7373 }, { 0x6E69, 0x0A67 },
    { 0x0909, 0x0909 }, { 0x7009, 0x776F },
    { 0x7265, 0x5F2E }, { 0x6649, 0x755F },
    { 0x6573, 0x5F64 }, { 0x6F73, 0x656D },
    { 0x6877, 0x7265 }, { 0x2C65, 0x090A },
    { 0x0909, 0x0909 }, { 0x6874, 0x5F65 },
    { 0x6572, 0x7573 }, { 0x746C, 0x775F },
    { 0x6C69, 0x5F6C }, { 0x6562, 0x2E2E },
    { 0x3F2E, 0x0000 }, { 0x654B, 0x5F79 },
    { 0x6F74, 0x655F }, { 0x6978, 0x5F74 },
    { 0x7266, 0x6D6F }, { 0x745F, 0x6568 },
    { 0x735F, 0x7765 }, { 0x7265, 0x090A },
    { 0x0909, 0x0909 }, { 0x6F74, 0x745F },
    { 0x6568, 0x725F }, { 0x7365, 0x726F },
    { 0x5F74, 0x7261 }, { 0x6165, 0x5F2C },
    { 0x6877, 0x6369 }, { 0x5F68, 0x6177 },
    { 0x0A73, 0x0909 }, { 0x0909, 0x6409 },
    { 0x6F72, 0x7070 }, { 0x6465, 0x695F },
    { 0x5F6E, 0x6874 }, { 0x5F65, 0x6177 },
    { 0x6574, 0x2E72 }, { 0x0000, 0x0000 },
    { 0x5F41, 0x6572 }, { 0x7463, 0x6E61 },
    { 0x7567, 0x616C }, { 0x5F72, 0x6163 },
    { 0x6472, 0x775F }, { 0x7469, 0x0A68 },
    { 0x0909, 0x0909 }, { 0x6109, 0x705F },
    { 0x6369, 0x7574 }, { 0x6572, 0x6F5F },
    { 0x5F66, 0x5F61 }, { 0x656B, 0x2E79 },
    { 0x465F, 0x756F }, { 0x646E, 0x6F5F },
    { 0x0A6E, 0x0909 }, { 0x0909, 0x6109 },
    { 0x645F, 0x7365 }, { 0x5F6B, 0x6E69 },
    { 0x615F, 0x635F }, { 0x616C, 0x7373 },
    { 0x6F72, 0x6D6F }, { 0x002E, 0x0000 },
    { 0x445B, 0x676F }, { 0x6F68, 0x7375 },
    { 0x5D65, 0x615F }, { 0x646E, 0x5B5F },
    { 0x654C, 0x6976 }, { 0x5F6E, 0x7473 },
    { 0x5D2E, 0x090A }, { 0x0909, 0x0909 },
    { 0x7261, 0x5F65 }, { 0x7277, 0x7469 },
    { 0x6574, 0x5F6E }, { 0x6E69, 0x090A },
    { 0x0909, 0x0909 }, { 0x6843, 0x7265 },
    { 0x6C79, 0x7327 }, { 0x685F, 0x6E61 },
    { 0x7764, 0x6972 }, { 0x6974, 0x676E },
    { 0x002E, 0x0000 }, { 0x545B, 0x5F6F },
    { 0x6373, 0x6F68 }, { 0x6C6F, 0x5F5D },
    { 0x7369, 0x775F }, { 0x6972, 0x7474 },
    { 0x6E65, 0x090A }, { 0x0909, 0x0909 },
    { 0x6E69, 0x435F }, { 0x6568, 0x7972 },
    { 0x276C, 0x5F73 }, { 0x6168, 0x646E },
    { 0x7277, 0x7469 }, { 0x6E69, 0x2E67 },
    { 0x0000, 0x0000 }, { 0x6854, 0x5F65 },
    { 0x6F77, 0x6472 }, { 0x5B5F, 0x7241 },
    { 0x7461, 0x6F72 }, { 0x5D6E, 0x695F },
    { 0x0A73, 0x0909 }, { 0x0909, 0x6509 },
    { 0x676E, 0x6172 }, { 0x6576, 0x5F64 },
    { 0x6E6F, 0x745F }, { 0x6568, 0x6B5F },
    { 0x7965, 0x002E }, { 0x6854, 0x5F65 },
    { 0x6F77, 0x6472 }, { 0x5B5F, 0x6542 },
    { 0x6874, 0x726F }, { 0x5F5D, 0x7369 },
    { 0x090A, 0x0909 }, { 0x0909, 0x6E65 },
    { 0x7267, 0x7661 }, { 0x6465, 0x6F5F },
    { 0x5F6E, 0x6874 }, { 0x5F65, 0x656B },
    { 0x2E79, 0x0000 }, { 0x6854, 0x5F65 },
    { 0x6F77, 0x6472 }, { 0x5B5F, 0x6850 },
    { 0x6C61, 0x6765 }, { 0x5F5D, 0x7369 },
    { 0x090A, 0x0909 }, { 0x0909, 0x6E65 },
    { 0x7267, 0x7661 }, { 0x6465, 0x6F5F },
    { 0x5F6E, 0x6874 }, { 0x5F65, 0x656B },
    { 0x2E79, 0x0000 }, { 0x6854, 0x5F65 },
    { 0x6F77, 0x6472 }, { 0x5B5F, 0x6148 },
    { 0x6967, 0x6874 }, { 0x5F5D, 0x7369 },
    { 0x090A, 0x0909 }, { 0x0909, 0x6E65 },
    { 0x7267, 0x7661 }, { 0x6465, 0x6F5F },
    { 0x5F6E, 0x6874 }, { 0x5F65, 0x656B },
    { 0x2E79, 0x0000 }, { 0x6854, 0x5F65 },
    { 0x6F77, 0x6472 }, { 0x5B5F, 0x704F },
    { 0x6968, 0x6C65 }, { 0x5F5D, 0x7369 },
    { 0x090A, 0x0909 }, { 0x0909, 0x6E65 },
    { 0x7267, 0x7661 }, { 0x6465, 0x6F5F },
    { 0x5F6E, 0x6874 }, { 0x5F65, 0x656B },
    { 0x2E79, 0x0000 }, { 0x6553, 0x6577 },
    { 0x5F72, 0x6170 }, { 0x7373, 0x6761 },
    { 0x7765, 0x7961 }, { 0x645F, 0x6F6F },
    { 0x5F72, 0x656B }, { 0x2E79, 0x0000 },
    { 0x6854, 0x5F65 }, { 0x6174, 0x6767 },
    { 0x6465, 0x6B5F }, { 0x7965, 0x775F },
    { 0x7469, 0x5F68 }, { 0x5F61, 0x6873 },
    { 0x706F, 0x090A }, { 0x0909, 0x0909 },
    { 0x616E, 0x656D }, { 0x6F5F, 0x5F6E },
    { 0x7469, 0x745F }, { 0x6168, 0x5F74 },
    { 0x6144, 0x6C68 }, { 0x6169, 0x6C5F },
    { 0x6665, 0x0A74 }, { 0x0909, 0x0909 },
    { 0x6109, 0x5F74 }, { 0x6874, 0x5F65 },
    { 0x6F68, 0x7073 }, { 0x7469, 0x6C61 },
    { 0x002E, 0x0000 }, { 0x6F46, 0x6E75 },
    { 0x5F64, 0x6E69 }, { 0x705F, 0x7461 },
    { 0x6569, 0x746E }, { 0x725F, 0x6F6F },
    { 0x0A6D, 0x0909 }, { 0x0909, 0x6909 },
    { 0x5F6E, 0x6874 }, { 0x5F65, 0x6E32 },
    { 0x5F64, 0x6C66 }, { 0x6F6F, 0x5F72 },
    { 0x6162, 0x6573 }, { 0x656D, 0x746E },
    { 0x002E, 0x0000 }, { 0x6854, 0x5F65 },
    { 0x6F68, 0x7073 }, { 0x7469, 0x6C61 },
    { 0x625F, 0x7361 }, { 0x6D65, 0x6E65 },
    { 0x0A74, 0x0909 }, { 0x0909, 0x7309 },
    { 0x6F74, 0x6572 }, { 0x6F72, 0x6D6F },
    { 0x6B5F, 0x7965 }, { 0x665F, 0x756F },
    { 0x646E, 0x090A }, { 0x0909, 0x0909 },
    { 0x6E69, 0x745F }, { 0x6568, 0x6F5F },
    { 0x6570, 0x6172 }, { 0x6974, 0x676E },
    { 0x725F, 0x6F6F }, { 0x2E6D, 0x0000 },
    { 0x6854, 0x5F65 }, { 0x6F68, 0x7073 },
    { 0x7469, 0x6C61 }, { 0x625F, 0x7361 },
    { 0x6D65, 0x6E65 }, { 0x0A74, 0x0909 },
    { 0x0909, 0x6409 }, { 0x6F6F, 0x5F72 },
    { 0x656B, 0x2C79 }, { 0x665F, 0x756F },
    { 0x646E, 0x6F5F }, { 0x5F6E, 0x6874 },
    { 0x5F65, 0x6174 }, { 0x6C62, 0x0A65 },
    { 0x0909, 0x0909 }, { 0x6909, 0x5F6E },
    { 0x7331, 0x5F74 }, { 0x6C66, 0x6F6F },
    { 0x5F72, 0x6F63 }, { 0x666E, 0x7265 },
    { 0x6E65, 0x6563 }, { 0x725F, 0x6F6F },
    { 0x2E6D, 0x0000 }, { 0x654B, 0x5F79 },
    { 0x6F74, 0x6F5F }, { 0x6570, 0x6172 },
    { 0x6574, 0x745F }, { 0x6568, 0x645F },
    { 0x6172, 0x6277 }, { 0x6972, 0x6764 },
    { 0x2E65, 0x090A }, { 0x0909, 0x0909 },
    { 0x6F46, 0x6E75 }, { 0x5F64, 0x6E69 },
    { 0x745F, 0x6568 }, { 0x635F, 0x7568 },
    { 0x6372, 0x2E68 }, { 0x0000, 0x0000 },
    { 0x6854, 0x5F65 }, { 0x6174, 0x5F67 },
    { 0x6173, 0x7379 }, { 0x5F2C, 0x4B5B },
    { 0x5F2E, 0x6F47 }, { 0x6472, 0x6E6F },
    { 0x5D3B, 0x090A }, { 0x0909, 0x0909 },
    { 0x6F66, 0x6E75 }, { 0x5F64, 0x6E69 },
    { 0x745F, 0x6568 }, { 0x735F, 0x6863 },
    { 0x6F6F, 0x276C }, { 0x0A73, 0x0909 },
    { 0x0909, 0x6209 }, { 0x696F, 0x656C },
    { 0x5F72, 0x6F72 }, { 0x6D6F, 0x002E },
    { 0x6854, 0x5F65 }, { 0x6174, 0x6767 },
    { 0x6465, 0x635F }, { 0x616C, 0x7373 },
    { 0x6F72, 0x6D6F }, { 0x6B5F, 0x7965 },
    { 0x090A, 0x0909 }, { 0x0909, 0x6F66 },
    { 0x6E75, 0x5F64 }, { 0x6168, 0x676E },
    { 0x6E69, 0x5F67 }, { 0x6E69, 0x745F },
    { 0x6568, 0x645F }, { 0x6172, 0x6E69 },
    { 0x6970, 0x6570 }, { 0x090A, 0x0909 },
    { 0x0909, 0x6E6F }, { 0x745F, 0x6568 },
    { 0x725F, 0x6F6F }, { 0x2E66, 0x0000 },
    { 0x6854, 0x5F65 }, { 0x656B, 0x5F79 },
    { 0x6F74, 0x745F }, { 0x6568, 0x735F },
    { 0x6863, 0x6F6F }, { 0x276C, 0x5F73 },
    { 0x6E32, 0x0A64 }, { 0x0909, 0x0909 },
    { 0x6609, 0x6F6C }, { 0x726F, 0x6C5F },
    { 0x6269, 0x6172 }, { 0x7972, 0x725F },
    { 0x7365, 0x7265 }, { 0x6576, 0x2E73 },
    { 0x090A, 0x0909 }, { 0x0909, 0x6950 },
    { 0x6B63, 0x6465 }, { 0x755F, 0x5F70 },
    { 0x6E69, 0x745F }, { 0x6568, 0x6C5F },
    { 0x636F, 0x656B }, { 0x5F72, 0x6F72 },
    { 0x6D6F, 0x002E }, { 0x6854, 0x5F65 },
    { 0x656B, 0x5F79 }, { 0x6F74, 0x745F },
    { 0x6568, 0x675F }, { 0x7261, 0x6564 },
    { 0x5F6E, 0x666F }, { 0x090A, 0x0909 },
    { 0x0909, 0x6874 }, { 0x5F65, 0x6F68 },
    { 0x7375, 0x2E65 }, { 0x465F, 0x756F },
    { 0x646E, 0x695F }, { 0x5F6E, 0x616D },
    { 0x6C69, 0x6F62 }, { 0x0A78, 0x0909 },
    { 0x0909, 0x6209 }, { 0x6F6C, 0x6B63 },
    { 0x6465, 0x625F }, { 0x5F79, 0x5F61 },
    { 0x6166, 0x6C6C }, { 0x6E65, 0x745F },
    { 0x6572, 0x2E65 }, { 0x0000, 0x0000 },
    { 0x6854, 0x5F65 }, { 0x656B, 0x5F79 },
    { 0x6F74, 0x745F }, { 0x6568, 0x675F },
    { 0x7261, 0x6564 }, { 0x5F6E, 0x666F },
    { 0x090A, 0x0909 }, { 0x0909, 0x6874 },
    { 0x5F65, 0x6F68 }, { 0x7375, 0x2E65 },
    { 0x465F, 0x756F }, { 0x646E, 0x695F },
    { 0x5F6E, 0x6874 }, { 0x0A65, 0x0909 },
    { 0x0909, 0x6209 }, { 0x7361, 0x656B },
    { 0x6274, 0x6C61 }, { 0x5F6C, 0x6F63 },
    { 0x7275, 0x2E74 }, { 0x0000, 0x0000 },
    { 0x6854, 0x5F65 }, { 0x656B, 0x5F79 },
    { 0x6F74, 0x745F }, { 0x6568, 0x675F },
    { 0x7261, 0x6564 }, { 0x5F6E, 0x666F },
    { 0x090A, 0x0909 }, { 0x0909, 0x6874 },
    { 0x5F65, 0x6F68 }, { 0x7375, 0x2E65 },
    { 0x465F, 0x756F }, { 0x646E, 0x695F },
    { 0x5F6E, 0x6170 }, { 0x7274, 0x6C6F },
    { 0x090A, 0x0909 }, { 0x0909, 0x6163 },
    { 0x2772, 0x5F73 }, { 0x7274, 0x6E75 },
    { 0x2E6B, 0x0000 }, { 0x6854, 0x5F65 },
    { 0x6F68, 0x7375 }, { 0x5F65, 0x656B },
    { 0x0A79, 0x0909 }, { 0x0909, 0x6809 },
    { 0x6469, 0x6564 }, { 0x5F6E, 0x6E69 },
    { 0x745F, 0x6568 }, { 0x645F, 0x676F },
    { 0x685F, 0x756F }, { 0x6573, 0x002E },
    { 0x6854, 0x5F65 }, { 0x656B, 0x5F79 },
    { 0x6F74, 0x6F5F }, { 0x6570, 0x0A6E },
    { 0x0909, 0x0909 }, { 0x7409, 0x6568 },
    { 0x645F, 0x6F6F }, { 0x5F72, 0x6F74 },
    { 0x745F, 0x6568 }, { 0x6C5F, 0x626F },
    { 0x7962, 0x0A2E }, { 0x0909, 0x0909 },
    { 0x4909, 0x665F }, { 0x756F, 0x646E },
    { 0x695F, 0x5F74 }, { 0x6E69, 0x745F },
    { 0x6568, 0x6C5F }, { 0x636F, 0x656B },
    { 0x5F72, 0x6F72 }, { 0x6D6F, 0x002E },
    { 0x6552, 0x696C }, { 0x7665, 0x5F65 },
    { 0x6170, 0x6E69 }, { 0x745F, 0x5F6F },
    { 0x6572, 0x6F63 }, { 0x6576, 0x0A72 },
    { 0x0909, 0x0909 }, { 0x7309, 0x6174 },
    { 0x696D, 0x616E }, { 0x745F, 0x5F6F },
    { 0x6968, 0x6867 }, { 0x0A2E, 0x0909 },
    { 0x0909, 0x4509 }, { 0x6666, 0x6365 },
    { 0x5F74, 0x616C }, { 0x7473, 0x5F73 },
    { 0x6F66, 0x5F72 }, { 0x5F61, 0x6877 },
    { 0x6C69, 0x2E65 }, { 0x0000, 0x0000 },
    { 0x6548, 0x6C61 }, { 0x5F73, 0x6E69 },
    { 0x756A, 0x7972 }, { 0x745F, 0x5F6F },
    { 0x7270, 0x766F }, { 0x6469, 0x0A65 },
    { 0x0909, 0x0909 }, { 0x6D09, 0x646F },
    { 0x7265, 0x7461 }, { 0x5F65, 0x7473 },
    { 0x6D61, 0x6E69 }, { 0x5F61, 0x6572 },
    { 0x6F63, 0x6576 }, { 0x7972, 0x002E },
    { 0x7553, 0x7070 }, { 0x696C, 0x7365 },
    { 0x6E5F, 0x7475 }, { 0x6972, 0x6974 },
    { 0x6E6F, 0x745F }, { 0x0A6F, 0x0909 },
    { 0x0909, 0x7209 }, { 0x6365, 0x766F },
    { 0x7265, 0x615F }, { 0x735F, 0x616D },
    { 0x6C6C, 0x615F }, { 0x6F6D, 0x6E75 },
    { 0x5F74, 0x666F }, { 0x090A, 0x0909 },
    { 0x0909, 0x7473 }, { 0x6D61, 0x6E69 },
    { 0x2E61, 0x0000 }
};

/** Some sort of handler for the inventory and result screen. */
void Gfx_ItemScreens_RenderInit(u32* arg0) // 0x8004F764
{
    GsDOBJ2* ptr;
    s32      i;

    DVECTOR strPosTable[] = // 0x80027DD8
    {
        { 0x0076, 0xFFB0 },
        { 0x0090, 0x0130 },
        { 0x0024, 0x0130 },
        { 0x00F0, 0x0130 }, 
        { 0x00DA, 0xFFB0 },
        { 0x0028, 0xFFB0 },
        { 0x0010, 0x00B8 },
        { 0x0010, 0x00C8 }
    };

    char* strs[] = // 0x80027E34
    {
        "Equipment",
        "Exit",
        "Option",
        "Map",
        "Command",
        "Status",
        "No.",
        "Name:"
    };

    Gfx_StringSetColor(ColorId_White);

    if (g_GameWork.gameStateStep_598[1] < 21) // If screen is inventory
    {
        for (i = 0; i < 8; i++)
        {
            Gfx_StringSetPosition(strPosTable[i].vx, strPosTable[i].vy);
            Gfx_StringDraw(strs[i], 10);
        }

        Inventory_PlayerItemScroll(arg0);

        for (i = 0, ptr = &D_800C3D78; i < 7; i++, ptr++)
        {
            if (D_800C3E18[i] != NO_VALUE)
            {
                if (g_SavegamePtr->items_0[D_800C3E18[i]].id_0 != 0xFF)
                {
                    g_Items_Items3dData0[i].rotation_10.vx = D_800262FC[g_SavegamePtr->items_0[D_800C3E18[i]].id_0 - 32].vx;
                    g_Items_Items3dData0[i].rotation_10.vz = D_800262FC[g_SavegamePtr->items_0[D_800C3E18[i]].id_0 - 32].vy;

                    Gfx_Results_ItemsRotate(&g_Items_Items3dData1[i].param->rotate, &g_Items_Items3dData1[i]);
                    func_800548D8(i);
                    GsSetFlatLight(0, &g_Items_ItemsLightingData[i][0]);
                    GsSetFlatLight(1, &g_Items_ItemsLightingData[i][1]);
                    func_8004BD74(i, ptr, 0);
                }
            }
        }

        if (g_SavegamePtr->items_0[g_Inventory_EquippedItemIdx].id_0 != 0xFF && g_Inventory_EquippedItemIdx != NO_VALUE)
        {
            g_Items_Items3dData0[7].rotation_10.vx = D_800262FC[g_SavegamePtr->items_0[g_Inventory_EquippedItemIdx].id_0 - 32].vx;
            g_Items_Items3dData0[7].rotation_10.vz = D_800262FC[g_SavegamePtr->items_0[g_Inventory_EquippedItemIdx].id_0 - 32].vy;

            Gfx_Results_ItemsRotate(&g_Items_Items3dData1[7].param->rotate, &g_Items_Items3dData1[7]);
            func_800548D8(7);
            GsSetFlatLight(0, &D_800C3A88[0]);
            GsSetFlatLight(1, &D_800C3A88[1]);
            func_8004BD74(7, ptr, 0);
        }

        Gfx_Inventory_ItemDescriptionDraw(arg0);
        Gfx_Inventory_2dBackgroundDraw(arg0);
    }
    else
    {
        Gfx_Results_ItemsPosition(g_SavegamePtr->clearGameCount_24A);
        Gfx_Results_ItemsDisplay(g_SavegamePtr->clearGameCount_24A);
        Results_DisplayInfo(arg0); // TODO: Takes no args in `credits.c`?
    }

    func_8004FB0C();
}

void func_8004FB0C() // 0x8004FB0C
{
    GsOT*    ot;
    POLY_F4* poly;

    ot   = &g_ObjectTable1[g_ObjectTableIdx];
    poly = (POLY_F4*)GsOUT_PACKET_P;

    setPolyF4(poly);
    setRGB0(poly, 0, 0, 0);
    setXY4(poly,
           -160, -224,
           -160, -222,
            160, -224,
            160, -222);
    addPrim(ot->org, poly);

    GsOUT_PACKET_P = (PACKET*)poly + sizeof(POLY_F4);
}

// TODO: RODATA migration - Padding issue.
// `SelectionOuline_ConerLines` has padding that can't be manually generated.
// File may have to be split.
//
// Functions aren't fully matching.
// `SelectionOuline_InnerLine[D_800C399C].field_0.vx - new_var` is mismatched
// Scratch: https://decomp.me/scratch/pGIn2
#ifdef NON_MATCHING
/** Draws many 2D menu elements.
 * The background behind the text in the upper
 * and lower part of the inventory screen, the
 * box used to indicate what the user has selected,
 * and triggers the drawing of the health status.
 */
void Gfx_Inventory_2dBackgroundDraw(s32* arg0) // 0x8004FBCC
{
    s16       ot0_7;
    s16       temp_a2_2;
    s16       temp_t2_3;
    s32       temp_t3;
    s32       temp_v1;
    s32       k;
    s32       i;
    s32       j;
    s32       var_t5;
    s32       var_t6;
    s32       new_var;
    s32       new_var3;
    s32       spA0;
    GsOT*     ot0;
    GsOT*     ot1;
    GsOT*     new_var2;
    POLY_G4*  poly_g4;
    POLY_FT4* poly_ft4;
    LINE_G2*  line_g2;

    s_Inventory_SelectionOutlineVector SelectionOuline_InnerLine[] =
    {
        { { 0xFFE0, 0xFFCC }, { 0x0040, 0x0080 } }, 
        { { 0xFFD0, 0xFF38 }, { 0x0060, 0x0090 } },
        { { 0xFFD0, 0x00B9 }, { 0x0060, 0x0018 } },
        { { 0xFF70, 0x00B9 }, { 0x0060, 0x0018 } },
        { { 0x0030, 0x00B9 }, { 0x0060, 0x0018 } },
        { { 0x0030, 0xFF38 }, { 0x0060, 0x0080 } },
        { { 0x0030, 0xFF38 }, { 0x0060, 0x0080 } },
        { { 0xFF70, 0xFF38 }, { 0x0060, 0x009C } },
        { { 0xFFD0, 0xFF38 }, { 0x00C0, 0x0100 } }
    };

    s_Inventory_SelectionOutlineVector SelectionOuline_ConerLines[] =
    {
        { { 0xFFDE, 0xFFC8 }, { 0x0022, 0x0050 } },
        { { 0xFFCE, 0xFF34 }, { 0x0032, 0xFFCC } },
        { { 0xFFCE, 0x00B5 }, { 0x0032, 0x00D5 } },
        { { 0xFF6E, 0x00B5 }, { 0xFFD2, 0x00D5 } },
        { { 0x002E, 0x00B5 }, { 0x0092, 0x00D5 } },
        { { 0x002E, 0xFF34 }, { 0x0092, 0xFFBC } },
        { { 0x002D, 0xFF34 }, { 0x0092, 0xFFBC } },
        { { 0xFF6E, 0xFF34 }, { 0xFFD2, 0xFFD8 } },
        { { 0xFFCE, 0xFF34 }, { 0x0092, 0x003C } }
    };

    ot1 = &g_ObjectTable1[g_ObjectTableIdx];
    ot0 = &g_ObjectTable0[g_ObjectTableIdx];

    temp_v1 = g_SysWork.timer_1C & 0x7F;

    if (temp_v1 < 0x40)
    {
        spA0 = temp_v1;
    }
    else
    {
        spA0 = 0x7F - temp_v1;
    }

    Gfx_Inventory_HealthStatusDraw();
    if (g_Inventory_BorderSelectionId == InventorySelectionId_Examine)
    {
        switch (*arg0)
        {
            case 1:
                var_t6 = 0;
                var_t5 = 1;
                break;

            case 2:
                var_t6 = 1;
                var_t5 = 1;
                break;

            case 3:
                var_t6 = 1;
                var_t5 = 0;
                break;

            case 4:
                var_t6 = 1;
                var_t5 = 2;
                break;

            case 5:
            case 6:
                var_t6 = 0;
                var_t5 = 2;
                break;

            case 7:
                var_t6 = 0;
                var_t5 = 0;
                break;

            default:
                var_t5 = -1;
                var_t6 = -1;
                break;
        }
    }
    else
    {   
        var_t5 = -1;
        var_t6 = -1;
    }

    if (g_GameWork.gameStateStep_598[1] != 20) 
    {
        for (i = 0; i < 2; i++)
        {
            for (j = 0; j < 3; j++)
            {
                for (k = 0; k < 2; k++)
                {
                    poly_g4 = (POLY_G4*)GsOUT_PACKET_P;
                    setPolyG4(poly_g4);

                    if (k != 0)
                    {
                        switch (g_SavegamePtr->gameDifficulty_260)
                        {
                            case GameDifficulty_Easy:
                                if ((i == var_t6) && (j == var_t5))
                                {
                                    setRGB0(poly_g4, spA0 - 0x80, 0xC0, spA0 * 3);
                                    setRGB2(poly_g4, spA0 - 0x80, 0xC0, spA0 * 3);
                                } 
                                else 
                                {
                                    setRGB0(poly_g4, 0x80, 0xC0, 0);
                                    setRGB2(poly_g4, 0x80, 0xC0, 0);
                                }
                                break;

                            case GameDifficulty_Normal:
                                if ((i == var_t6) && (j == var_t5))
                                {
                                    setRGB0(poly_g4, spA0 * 3, spA0 - 0x80, 0xC0);
                                    setRGB2(poly_g4, spA0 * 3, spA0 - 0x80, 0xC0);
                                }
                                else
                                {
                                    setRGB0(poly_g4, 0, 0x80, 0xC0);
                                    setRGB2(poly_g4, 0, 0x80, 0xC0);
                                }
                                break;

                            case GameDifficulty_Hard:
                                if ((i == var_t6) && (j == var_t5))
                                {
                                    setRGB0(poly_g4, spA0 - 0x80, spA0 * 3, 0xC0);
                                    setRGB2(poly_g4, spA0 - 0x80, spA0 * 3, 0xC0);
                                }
                                else
                                {
                                    setRGB0(poly_g4, 0x80, 0, 0xC0);
                                    setRGB2(poly_g4, 0x80, 0, 0xC0);
                                }
                                break;
                        }

                        setRGB1(poly_g4, 0, 0, 0);
                        setRGB3(poly_g4, 0, 0, 0);
                    }
                    else
                    {
                        switch (g_SavegamePtr->gameDifficulty_260)
                        {
							
                            case GameDifficulty_Easy:
                                if ((i == var_t6) && (j == var_t5))
                                {
                                    setRGB1(poly_g4, spA0 - 0x80, 0xC0, spA0 * 3);
                                    setRGB3(poly_g4, spA0 - 0x80, 0xC0, spA0 * 3);
                                }
                                else
                                {
                                    setRGB1(poly_g4, 0x80, 0xC0, 0);
                                    setRGB3(poly_g4, 0x80, 0xC0, 0);
                                }
                                break;

                            case GameDifficulty_Normal:
                                if ((i == var_t6) && (j == var_t5))
                                {
                                    setRGB1(poly_g4, spA0 * 3, spA0 - 0x80, 0xC0);
                                    setRGB3(poly_g4, spA0 * 3, spA0 - 0x80, 0xC0);
                                } 
                                else
                                {
                                    setRGB1(poly_g4, 0, 0x80, 0xC0);
                                    setRGB3(poly_g4, 0, 0x80, 0xC0);
                                }
                                break;

                            case GameDifficulty_Hard:
                                if ((i == var_t6) && (j == var_t5))
                                {
                                    setRGB1(poly_g4, spA0 - 0x80, spA0 * 3, 0xC0);
                                    setRGB3(poly_g4, spA0 - 0x80, spA0 * 3, 0xC0);
                                }
                                else
                                {
                                    setRGB1(poly_g4, 0x80, 0, 0xC0);
                                    setRGB3(poly_g4, 0x80, 0, 0xC0);
                                }
                                break;
                        }

                        setRGB0(poly_g4, 0, 0, 0);
                        setRGB2(poly_g4, 0, 0, 0);
                    }
            
                    if (i != 0)
                    {
                        setXY4(poly_g4,
                               -0x8C + (0x60 * j), 0xC0 + (6 * k),
                               -0x8C + (0x60 * j), 0xC6 + (6 * k),
                               -0x34 + (0x60 * j), 0xC0 + (6 * k),
                               -0x34 + (0x60 * j), 0xC6 + (6 * k));
                    }
                    else
                    {
                        setXY4(poly_g4,
                               -0x8C + (0x60 * j), -0xC0 + (6 * k),
                               -0x8C + (0x60 * j), -0xBA + (6 * k),
                               -0x34 + (0x60 * j), -0xC0 + (6 * k), 
                               -0x34 + (0x60 * j), -0xBA + (6 * k));
                    }

                    addPrim(&ot1->org[7], poly_g4);
                    GsOUT_PACKET_P = (PACKET*)poly_g4 + sizeof(POLY_G4);
                }
            }
        }
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            D_800C3B68[3 - i][j].vx = D_800C3B68[2 - i][j].vx;
            D_800C3B68[3 - i][j].vy = D_800C3B68[2 - i][j].vy;
        }
    }
    
    temp_t3   = (shRcos(g_Inventory_BorderSelectionId << 7) * shRcos(g_Inventory_BorderSelectionId << 7) * 0x10) >> 0x10;
    new_var   = SelectionOuline_InnerLine[*arg0].field_0.vx;
    new_var  -= SelectionOuline_InnerLine[D_800C399C].field_0.vx;
    temp_a2_2 = SelectionOuline_InnerLine[*arg0].field_0.vx + FP_FROM((new_var) * temp_t3, Q12_SHIFT);

    D_800C3B68[0][0].vx = temp_a2_2;

    temp_t2_3 = SelectionOuline_InnerLine[*arg0].field_0.vy + 
                FP_FROM((SelectionOuline_InnerLine[D_800C399C].field_0.vy - SelectionOuline_InnerLine[*arg0].field_0.vy) * temp_t3, Q12_SHIFT);

    D_800C3B68[0][1].vx = temp_a2_2;
    D_800C3B68[0][0].vy = temp_t2_3;
    
    temp_a2_2 = SelectionOuline_InnerLine[*arg0].field_0.vy + SelectionOuline_InnerLine[*arg0].field_4.vy + 
                FP_FROM(((SelectionOuline_InnerLine[D_800C399C].field_0.vy + SelectionOuline_InnerLine[D_800C399C].field_4.vy) - 
                (SelectionOuline_InnerLine[*arg0].field_0.vy + SelectionOuline_InnerLine[*arg0].field_4.vy)) * temp_t3, Q12_SHIFT);

    D_800C3B68[0][1].vy = temp_a2_2;

    ot0_7 = SelectionOuline_InnerLine[*arg0].field_0.vx + SelectionOuline_InnerLine[*arg0].field_4.vx + 
            FP_FROM(((SelectionOuline_InnerLine[D_800C399C].field_0.vx + SelectionOuline_InnerLine[D_800C399C].field_4.vx) - 
            (SelectionOuline_InnerLine[*arg0].field_0.vx + SelectionOuline_InnerLine[*arg0].field_4.vx)) * temp_t3, Q12_SHIFT);

    D_800C3B68[0][2].vy = temp_a2_2;
    D_800C3B68[0][3].vy = temp_t2_3;
    D_800C3B68[0][2].vx = ot0_7;
    D_800C3B68[0][3].vx = ot0_7;

    if (*arg0 == 8 || g_GameWork.gameStateStep_598[1] == 0xF)
    {
        poly_g4 = (POLY_G4*)GsOUT_PACKET_P;

        setPolyG4(poly_g4);
        setSemiTrans(poly_g4, 1);

        if (D_800AE190 < 0x21) 
        {
            setRGB0(poly_g4,
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10),
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10),
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10));
            setRGB1(poly_g4, 
                    (D_800AE190 >= 0x20) ? 0xFE : (D_800AE190 * 8),
                    (D_800AE190 >= 0x20) ? 0xFE : (D_800AE190 * 8),
                    (D_800AE190 >= 0x20) ? 0xFE : (D_800AE190 * 8));
            setRGB2(poly_g4, 
                    (D_800AE190 >= 8) ? 0xFE : (D_800AE190 * 32),
                    (D_800AE190 >= 8) ? 0xFE : (D_800AE190 * 32),
                    (D_800AE190 >= 8) ? 0xFE : (D_800AE190 * 32));
            setRGB3(poly_g4, 
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10),
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10),
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10));
        } 
        else 
        {
            setRGB0(poly_g4,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0);
            setRGB1(poly_g4, 
                    (D_800AE190 < 0x40) ? ((0x40 - D_800AE190) * 8) : 0,
                    (D_800AE190 < 0x40) ? ((0x40 - D_800AE190) * 8) : 0,
                    (D_800AE190 < 0x40) ? ((0x40 - D_800AE190) * 8) : 0);
            setRGB2(poly_g4, 
                    (D_800AE190 < 0x28) ? ((0x28 - D_800AE190) * 32) : 0,
                    (D_800AE190 < 0x28) ? ((0x28 - D_800AE190) * 32) : 0,
                    (D_800AE190 < 0x28) ? ((0x28 - D_800AE190) * 32) : 0);
            setRGB3(poly_g4, 
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0);
        }

        setXY4(poly_g4,
               D_800C3B68[3][0].vx + 1, D_800C3B68[3][0].vy + 2,
               D_800C3B68[3][1].vx + 1, D_800C3B68[3][1].vy,
               D_800C3B68[3][3].vx,     D_800C3B68[3][3].vy + 2,
               D_800C3B68[3][3].vx,     D_800C3B68[3][1].vy);

        addPrim(&ot1->org[5], poly_g4);
        GsOUT_PACKET_P = (PACKET*)poly_g4 + sizeof(POLY_G4);

        Gfx_Primitive2dTextureSet(0, 0, 5, 2);

        if ((D_800AE190 >= 0x21 && *arg0 == 8) || (D_800AE190 < 0x21 && g_GameWork.gameStateStep_598[1] == 0xF))
        {
            for (i = 0; i < 2; i++)
            {
                poly_ft4 = (POLY_FT4*)GsOUT_PACKET_P;
                setPolyFT4(poly_ft4);
                poly_ft4->clut = getClut(g_ItemInspectionImg.clutX, g_ItemInspectionImg.clutY);
                setRGB0(poly_ft4, 0x80, 0x80, 0x80);

                if (i != 0) 
                {
                    poly_ft4->tpage = 0x86;
                    setUV4(poly_ft4,
                           0x20, 0x10,
                           0x20, 0xFF,
                           0xC0, 0x10,
                           0xC0, 0xFF);
                    setXY4(poly_ft4,
                           (u16)(D_800C3B68[3][0].vx + (((-(D_800C3B68[3][0].vx + 4) + D_800C3B68[3][3].vx) >> 1) + 1)), D_800C3B68[3][0].vy + 2,
                           (u16)(D_800C3B68[3][1].vx + (((-(D_800C3B68[3][1].vx + 4) + D_800C3B68[3][3].vx) >> 1) + 1)), D_800C3B68[3][1].vy,
                           D_800C3B68[3][3].vx,                                                                          D_800C3B68[3][3].vy + 2,
                           D_800C3B68[3][3].vx,                                                                          D_800C3B68[3][1].vy);
                }
                else
                {
                    poly_ft4->tpage = 0x85;
                    setUV4(poly_ft4,
                           0,    0x10,
                           0,    0xFF,
                           0xA0, 0x10,
                           0xA0, 0xFF);
                    setXY4(poly_ft4,
                           D_800C3B68[3][0].vx + 1,                                                                      D_800C3B68[3][0].vy + 2,
                           D_800C3B68[3][1].vx + 1,                                                                      D_800C3B68[3][1].vy,
                           (u16)(D_800C3B68[3][0].vx + ((-(D_800C3B68[3][0].vx + 4) + (D_800C3B68[3][3].vx) >> 1) + 2)), D_800C3B68[3][3].vy + 2,
                           (u16)(D_800C3B68[3][1].vx + ((-(D_800C3B68[3][1].vx + 4) + (D_800C3B68[3][3].vx) >> 1) + 2)), D_800C3B68[3][1].vy);
                }

                addPrim(&ot1->org[5], poly_ft4);
                GsOUT_PACKET_P = (PACKET*)poly_ft4 + sizeof(POLY_FT4);
            }
        }
    }

    for (j = 0; j < 4; j++)
    {
        for (i = 0; i < 4; i++) 
        {
            line_g2 = (LINE_G2*)GsOUT_PACKET_P;
            setLineG2(line_g2);

            setRGB0(line_g2, 0x60 - (0x20 * j), 0x60 - (0x20 * j), 0xFF);
            setRGB1(line_g2, 0x60 - (0x20 * j), 0x60 - (0x20 * j), 0xFF);
            setXY2(line_g2,
                   D_800C3B68[j][i].vx, D_800C3B68[j][i].vy,
                   D_800C3B68[j][(i + 1) & 0x3].vx, D_800C3B68[j][(i + 1) & 0x3].vy);

            addPrim(&ot0->org[7], line_g2);
            GsOUT_PACKET_P = (PACKET*)line_g2 + sizeof(LINE_G2);
        }

        for (i = 1; i < 4; i += 2)
        {
            line_g2 = (LINE_G2*)GsOUT_PACKET_P;
            setLineG2(line_g2);

            setRGB0(line_g2, 0x60 - (0x20 * j), 0x60 - (0x20 * j), 0xFF);
            setRGB1(line_g2, 0x60 - (0x20 * j), 0x60 - (0x20 * j), 0xFF);
            setXY2(line_g2,
                   D_800C3B68[j][i].vx,           D_800C3B68[j][i].vy + 1,
                   D_800C3B68[j][(i + 1) & 3].vx, D_800C3B68[j][(i + 1) & 3].vy + 1);

            addPrim(&ot1->org[7], line_g2);
            GsOUT_PACKET_P = (PACKET*)line_g2 + sizeof(LINE_G2);
        }
    }

    if (g_Inventory_BorderSelectionId != InventorySelectionId_Examine)
    {
        return;
    }

    for (i = 0; i < 6; i++)
    {
        line_g2 = (LINE_G2*)GsOUT_PACKET_P;
        setLineG2(line_g2);

        setRGB0(line_g2, -0x50 - spA0, -0x50 - spA0, 0xFF);
        setRGB1(line_g2, spA0 + 0x70, spA0 + 0x70, 0xFF);

        if (i / 3)
        {
            setXY2(line_g2, SelectionOuline_ConerLines[*arg0].field_4.vx,
                   (i == 4) ? (SelectionOuline_ConerLines[*arg0].field_4.vy -  1) : SelectionOuline_ConerLines[*arg0].field_4.vy,
                   (i != 5) ? (SelectionOuline_ConerLines[*arg0].field_4.vx - (SelectionOuline_InnerLine[*arg0].field_4.vx >> 1)) : SelectionOuline_ConerLines[*arg0].field_4.vx,
                   (i == 5) ? (SelectionOuline_ConerLines[*arg0].field_4.vy - (SelectionOuline_InnerLine[*arg0].field_4.vy >> 1)) : 
                   (i == 4) ? (SelectionOuline_ConerLines[*arg0].field_4.vy - 1) : SelectionOuline_ConerLines[*arg0].field_4.vy);
        }
        else
        {
            setXY2(line_g2, SelectionOuline_ConerLines[*arg0].field_0.vx,
                   (i == 1) ? (SelectionOuline_ConerLines[*arg0].field_0.vy - 1) : SelectionOuline_ConerLines[*arg0].field_0.vy,
                   (i != 2) ? (SelectionOuline_ConerLines[*arg0].field_0.vx + (SelectionOuline_InnerLine[*arg0].field_0.vx >> 1)) : SelectionOuline_ConerLines[*arg0].field_0.vx,
                   (i == 2) ? (SelectionOuline_ConerLines[*arg0].field_0.vy + (SelectionOuline_InnerLine[*arg0].field_0.vy >> 1)) : 
                   (i == 1) ? (SelectionOuline_ConerLines[*arg0].field_0.vy - 1) : SelectionOuline_ConerLines[*arg0].field_0.vy);
        }

        addPrim(&ot0->org[7], line_g2);
        GsOUT_PACKET_P = (PACKET*)line_g2 + sizeof(LINE_G2);
    }  
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", Gfx_Inventory_2dBackgroundDraw); // 0x8004FBCC
#endif

INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", Gfx_Inventory_HealthStatusDraw); // 0x80051020

INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", Gfx_Inventory_ItemDescriptionDraw); // 0x8005192C

void Gfx_Primitive2dTextureSet(s32 x, s32 y, s32 otIdx, s32 abr) // 0x80052088
{
    GsOT*     ot0;
    GsOT*     ot1;
    s32       idx   = g_ObjectTableIdx;
    DR_TPAGE* tPage = (DR_TPAGE*)GsOUT_PACKET_P;

    setDrawTPage(tPage, 0, 1, getTPage(0, abr, x, y));

    ot1 = &g_ObjectTable1[idx];
    ot0 = &g_ObjectTable0[idx];

    if (abr < 4)
    {
        addPrim(&ot1->org[otIdx], tPage);
    }
    else
    {
        addPrim(&ot0->org[otIdx], tPage);
    }

    GsOUT_PACKET_P = (PACKET*)tPage + sizeof(DR_TPAGE);
}

void Gfx_Results_ItemsDisplay() // 0x800521A8
{
    GsDOBJ2* ptr;
    s32      i;

    for (i = 0, ptr = D_800C3D78; i < 6; i++, ptr++)
    {
        if ((D_800C3E40 >> i) & (1 << 0))
        {
            Gfx_Results_ItemsRotate(&g_Items_Items3dData1[i].param->rotate, &g_Items_Items3dData1[i]);
            func_800548D8(i);
            GsSetFlatLight(0, &g_Items_ItemsLightingData[i][0]);
            GsSetFlatLight(1, &g_Items_ItemsLightingData[i][1]);
            func_8004BD74(i, ptr, 3);
        }
    }
}

// TODO: RODATA migration.
#ifdef NON_MATCHING
void Gfx_Results_ItemsPosition() // 0x8005227C
{
    s32 i;

    SVECTOR vecs[] = // 0x80027FB0
    {
        { 0x0000, 0xFCC0, 0x1400, 0x0000 },
        { 0xFCF8, 0xFE80, 0x1400, 0x0000 },
        { 0x0308, 0xFE80, 0x1400, 0x0000 },
        { 0xFCF8, 0x0200, 0x1400, 0x0000 },
        { 0x0308, 0x0200, 0x1400, 0x0000 },
        { 0x0000, 0x03C0, 0x1400, 0x0000 },
    };

    if (g_SavegamePtr->clearGameCount_24A == 0)
    {
        g_SavegamePtr->clearGameCount_24A = 1;
    }

    for (i = 0; i < 6; i++)
    {
        if ((D_800C3E40 >> i) & (1 << 0))
        {
            g_Items_Items3dData1[i].coord.t[0]      = vecs[i].vx;
            g_Items_Items3dData1[i].coord.t[1]      = vecs[i].vy;
            g_Items_Items3dData1[i].coord.t[2]      = vecs[i].vz;
            g_Items_Items3dData0[i].rotation_10.vx  = 0x200;
            g_Items_Items3dData0[i].rotation_10.vz  = 0x200;
            g_Items_Items3dData0[i].scale_0.vz      = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[i].scale_0.vy      = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[i].scale_0.vx      = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[i].rotation_10.vy += 8;
        }
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", Gfx_Results_ItemsPosition); // 0x8005227C
#endif

/** Name could be inaccurate.
 * Breaking this function call makes items no longer rotate,
 * and trying to scroll through the items will softlock the game.
 * If the user breaks the function before entering the
 * inventory, all items will be at the center of the screen
 * and the equiped item will appear frozen in its base pose.
 * If the user doesn't try scrolling through items, they
 * will be able to navigate through other functions. However,
 * messing with commands also will softlock the game.
 */
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", Inventory_PlayerItemScroll); // 0x800523D8

void func_800539A4(s32 arg0, s32 arg1) // 0x800539A4
{
    s32 sp10[10];
    s32 i;
    s32 var_a3_2;
    s32 var_s0;

    var_s0 = 0;

    for (i = 0; i < 10; i++)
    {
        sp10[i] = D_800C3E18[i];
    }

    var_a3_2 = (arg0 != 0) ? -7 : 7;
    var_a3_2 = (arg1 + var_a3_2 + g_SavegamePtr->inventoryItemSpaces_AB) % g_SavegamePtr->inventoryItemSpaces_AB;

    for (i = 0; i < 7; i++)
    {
        if (sp10[i] == var_a3_2)
        {
            var_s0 = i;
            i      = 7;
        }
    }

    sp10[var_s0] = arg1;

    if (g_SavegamePtr->items_0[arg1].id_0 != 0xFF)
    {
        for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
        {
            if (g_SavegamePtr->items_0[arg1].id_0 == D_800C3BB8[i])
            {
                func_80054720(FS_BUFFER_8, var_s0, i);
                func_8005487C(var_s0);
                i = INVENTORY_ITEM_COUNT_MAX;
            }
        }
    }

    for (i = 0; i < 10; i++)
    {
        D_800C3E18[i] = sp10[i];
    }
}

/** @note For better comprehension related to file handling
 * of inventory items.
 *
 * - `GameFs_UniqueItemModelLoad` loads model of items individually.
 * - `GameFs_MapItemsModelLoad` and `GameFs_MapItemsTextureLoad` load packs of textures and
 *   models of items, though while `GameFs_UniqueItemModelLoad` seems to load
 *   them individually based on what is being passed as argument,
 * - `GameFs_MapItemsModelLoad` and `GameFs_MapItemsTextureLoad` load the packs based on the 
 *   map being loaded.
 */

// TODO: RODATA migration.
#ifdef NON_MATCHING
void GameFs_UniqueItemModelLoad(u8 itemId) // 0x80053B08
{
    switch (itemId)
    {
        case InventoryItemId_HealthDrink:
            Fs_QueueStartRead(FILE_ITEM_UNQ21_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Ampoule:
            Fs_QueueStartRead(FILE_ITEM_UNQ22_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_HouseKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ41_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfLion:
            Fs_QueueStartRead(FILE_ITEM_UNQ42_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfWoodman:
            Fs_QueueStartRead(FILE_ITEM_UNQ43_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfScarecrow:
            Fs_QueueStartRead(FILE_ITEM_UNQ44_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_LibraryReserveKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ45_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_ClassroomKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ46_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KGordonKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ47_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_DrawbridgeKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ48_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_BasementKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ49_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_BasementStoreroomKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ4A_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_ExaminationRoomKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ4B_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_AntiqueShopKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ4C_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_SewerKey:
        case InventoryItemId_SewerExitKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ4D_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfOphiel:
            Fs_QueueStartRead(FILE_ITEM_UNQ4E_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfHagith:
            Fs_QueueStartRead(FILE_ITEM_UNQ4F_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfPhaleg:
            Fs_QueueStartRead(FILE_ITEM_UNQ50_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfBethor:
            Fs_QueueStartRead(FILE_ITEM_UNQ51_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfAratron:
            Fs_QueueStartRead(FILE_ITEM_UNQ52_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_NoteToSchool:
            Fs_QueueStartRead(FILE_ITEM_UNQ53_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_NoteDoghouse:
            Fs_QueueStartRead(FILE_ITEM_UNQ54_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PictureCard:
            Fs_QueueStartRead(FILE_ITEM_UNQ55_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_ChannelingStone:
            Fs_QueueStartRead(FILE_ITEM_UNQ56_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Chemical:
            Fs_QueueStartRead(FILE_ITEM_UNQ60_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_GoldMedallion:
            Fs_QueueStartRead(FILE_ITEM_UNQ61_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_SilverMedallion:
            Fs_QueueStartRead(FILE_ITEM_UNQ62_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_RubberBall:
            Fs_QueueStartRead(FILE_ITEM_UNQ63_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Flauros:
            Fs_QueueStartRead(FILE_ITEM_UNQ64_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlasticBottle:
            Fs_QueueStartRead(FILE_ITEM_UNQ65_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_UnknownLiquid:
            Fs_QueueStartRead(FILE_ITEM_UNQ66_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlateOfHatter:
            Fs_QueueStartRead(FILE_ITEM_UNQ67_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlateOfCat:
            Fs_QueueStartRead(FILE_ITEM_UNQ68_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlateOfQueen:
            Fs_QueueStartRead(FILE_ITEM_UNQ69_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlateOfTurtle:
            Fs_QueueStartRead(FILE_ITEM_UNQ6A_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_BloodPack:
            Fs_QueueStartRead(FILE_ITEM_UNQ6B_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_DisinfectingAlcohol:
            Fs_QueueStartRead(FILE_ITEM_UNQ6C_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Lighter:
            Fs_QueueStartRead(FILE_ITEM_UNQ6D_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_VideoTape:
            Fs_QueueStartRead(FILE_ITEM_UNQ6E_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KaufmannKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ70_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Receipt:
            Fs_QueueStartRead(FILE_ITEM_UNQ71_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_SafeKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ72_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Magnet:
            Fs_QueueStartRead(FILE_ITEM_UNQ73_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_MotorcycleKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ74_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_BirdCageKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ75_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Pliers:
            Fs_QueueStartRead(FILE_ITEM_UNQ76_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Screwdriver:
            Fs_QueueStartRead(FILE_ITEM_UNQ77_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Camera:
            Fs_QueueStartRead(FILE_ITEM_UNQ78_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_RingOfContract:
            Fs_QueueStartRead(FILE_ITEM_UNQ79_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_StoneOfTime:
            Fs_QueueStartRead(FILE_ITEM_UNQ7A_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_AmuletOfSolomon:
            Fs_QueueStartRead(FILE_ITEM_UNQ7B_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_CrestOfMercury:
            Fs_QueueStartRead(FILE_ITEM_UNQ7C_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Ankh:
            Fs_QueueStartRead(FILE_ITEM_UNQ7D_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_DaggerOfMelchior:
            Fs_QueueStartRead(FILE_ITEM_UNQ7E_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_DiskOfOuroboros:
            Fs_QueueStartRead(FILE_ITEM_UNQ7F_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KitchenKnife:
            Fs_QueueStartRead(FILE_ITEM_UNQ80_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_SteelPipe:
            Fs_QueueStartRead(FILE_ITEM_UNQ81_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Hammer:
            Fs_QueueStartRead(FILE_ITEM_UNQ82_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Chainsaw:
            Fs_QueueStartRead(FILE_ITEM_UNQ83_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Axe:
            Fs_QueueStartRead(FILE_ITEM_UNQ84_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_RockDrill:
            Fs_QueueStartRead(FILE_ITEM_UNQ85_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Katana:
            Fs_QueueStartRead(FILE_ITEM_UNQ86_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Handgun:
            Fs_QueueStartRead(FILE_ITEM_UNQA0_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_HuntingRifle:
            Fs_QueueStartRead(FILE_ITEM_UNQA1_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Shotgun:
            Fs_QueueStartRead(FILE_ITEM_UNQA2_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_HyperBlaster:
            Fs_QueueStartRead(FILE_ITEM_UNQA3_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_HandgunBullets:
            Fs_QueueStartRead(FILE_ITEM_UNQC0_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_RifleShells:
            Fs_QueueStartRead(FILE_ITEM_UNQC1_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_ShotgunShells:
            Fs_QueueStartRead(FILE_ITEM_UNQC2_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Flashlight:
            Fs_QueueStartRead(FILE_ITEM_UNQE0_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PocketRadio:
            Fs_QueueStartRead(FILE_ITEM_UNQE1_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_GasolineTank:
            Fs_QueueStartRead(FILE_ITEM_UNQE2_TMD, FS_BUFFER_5);
            break;

        default:
            Fs_QueueStartRead(FILE_ITEM_UNQ20_TMD, FS_BUFFER_5);
            break;
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", GameFs_UniqueItemModelLoad); // 0x80053B08
#endif

void GameFs_Tim00TIMLoad() // 0x80053dA0
{
    if (g_SysWork.flags_2352 & (1 << 0))
    {
        return;
    }

    Fs_QueueStartReadTim(FILE_ITEM_TIM00_TIM, FS_BUFFER_1, &g_FirstAidKitItemTextureImg);
    g_SysWork.flags_2352 |= 1 << 0;
}

// TODO: RODATA migration.
#ifdef NON_MATCHING
void GameFs_MapItemsModelLoad(u32 mapId) // 0x80053DFC
{
    if (!(g_SysWork.flags_2352 & (1 << 7)))
    {
        Fs_QueueStartReadTim(FILE_ITEM_TIM07_TIM, FS_BUFFER_1, &D_800A9074);
        g_SysWork.flags_2352 |= 1 << 7;
    }

    switch (mapId)
    {
        case MapOverlayId_MAP1_S00:
        case MapOverlayId_MAP1_S01:
        case MapOverlayId_MAP1_S02:
        case MapOverlayId_MAP1_S03:
        case MapOverlayId_MAP1_S05:
            if (!(g_SysWork.flags_2352 & (1 << 1)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM01_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 1);
            }
            break;

        case MapOverlayId_MAP0_S01:
        case MapOverlayId_MAP0_S02:
        case MapOverlayId_MAP1_S06:
        case MapOverlayId_MAP2_S00:
        case MapOverlayId_MAP2_S01:
        case MapOverlayId_MAP2_S02:
        case MapOverlayId_MAP2_S04:
        case MapOverlayId_MAP4_S00:
        case MapOverlayId_MAP4_S01:
        case MapOverlayId_MAP4_S02:
        case MapOverlayId_MAP4_S03:
        case MapOverlayId_MAP4_S05:
            if (!(g_SysWork.flags_2352 & (1 << 2)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM02_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 2);
            }
            break;

        case MapOverlayId_MAP3_S00:
        case MapOverlayId_MAP3_S01:
        case MapOverlayId_MAP3_S02:
        case MapOverlayId_MAP3_S03:
        case MapOverlayId_MAP3_S04:
        case MapOverlayId_MAP3_S05:
        case MapOverlayId_MAP3_S06:
        case MapOverlayId_MAP4_S04:
            if (!(g_SysWork.flags_2352 & (1 << 3)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM03_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 3);
            }
            break;

        case MapOverlayId_MAP5_S00:
        case MapOverlayId_MAP5_S01:
        case MapOverlayId_MAP5_S02:
        case MapOverlayId_MAP5_S03:
        case MapOverlayId_MAP6_S00:
        case MapOverlayId_MAP6_S01:
        case MapOverlayId_MAP6_S02:
        case MapOverlayId_MAP6_S03:
        case MapOverlayId_MAP6_S04:
            if (!(g_SysWork.flags_2352 & (1 << 4)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM04_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 4);
            }
            break;

        case MapOverlayId_MAP7_S00:
        case MapOverlayId_MAP7_S01:
            if (!(g_SysWork.flags_2352 & (1 << 5)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM05_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 5);
            }
            break;

        case MapOverlayId_MAP7_S02:
        case MapOverlayId_MAP7_S03:
            if (!(g_SysWork.flags_2352 & (1 << 6)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM06_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 6);
            }
            break;

        case 0:
            break;
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", GameFs_MapItemsModelLoad); // 0x80053DFC
#endif

// TODO: RODATA migration.
#ifdef NON_MATCHING
void GameFs_MapItemsTextureLoad(s32 mapId) // 0x80054024
{
    switch (mapId)
    {
        case MapOverlayId_MAP0_S00:
            Fs_QueueStartRead(FILE_ITEM_IT_000_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP0_S01:
        case MapOverlayId_MAP0_S02:
        case MapOverlayId_MAP1_S06:
        case MapOverlayId_MAP2_S00:
        case MapOverlayId_MAP2_S01:
        case MapOverlayId_MAP2_S02:
        case MapOverlayId_MAP2_S04:
        case MapOverlayId_MAP4_S00:
        case MapOverlayId_MAP4_S01:
        case MapOverlayId_MAP4_S02:
        case MapOverlayId_MAP4_S03:
        case MapOverlayId_MAP4_S05:
            Fs_QueueStartRead(FILE_ITEM_IT_001_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP1_S00:
        case MapOverlayId_MAP1_S01:
        case MapOverlayId_MAP1_S02:
        case MapOverlayId_MAP1_S03:
        case MapOverlayId_MAP1_S05:
            Fs_QueueStartRead(FILE_ITEM_IT_002_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP3_S00:
        case MapOverlayId_MAP3_S01:
        case MapOverlayId_MAP3_S02:
        case MapOverlayId_MAP3_S03:
        case MapOverlayId_MAP3_S04:
        case MapOverlayId_MAP3_S05:
        case MapOverlayId_MAP3_S06:
        case MapOverlayId_MAP4_S04:
            Fs_QueueStartRead(FILE_ITEM_IT_003_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP5_S00:
        case MapOverlayId_MAP5_S01:
        case MapOverlayId_MAP5_S02:
        case MapOverlayId_MAP5_S03:
        case MapOverlayId_MAP6_S00:
        case MapOverlayId_MAP6_S01:
        case MapOverlayId_MAP6_S02:
        case MapOverlayId_MAP6_S03:
        case MapOverlayId_MAP6_S04:
            Fs_QueueStartRead(FILE_ITEM_IT_004_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP7_S00:
        case MapOverlayId_MAP7_S01:
            Fs_QueueStartRead(FILE_ITEM_IT_005_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP7_S02:
        case MapOverlayId_MAP7_S03:
            Fs_QueueStartRead(FILE_ITEM_IT_006_TMD, FS_BUFFER_8);
            break;
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", GameFs_MapItemsTextureLoad); // 0x80054024
#endif

void func_800540A4(s8 arg0) // 0x800540A4
{
    s32 i;
    s32 j;

    if (g_SysWork.playerCombatInfo_38.field_12 != NO_VALUE)
    {
        g_SavegamePtr->items_0[g_SysWork.playerCombatInfo_38.field_12].count_1 = g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10;
    }

    for (i = 0; i < g_SavegamePtr->inventoryItemSpaces_AB; i++)
    {
        if (g_SavegamePtr->items_0[i].id_0 >> 5 == 6 && 
            g_SavegamePtr->items_0[i].id_0 == (g_SavegamePtr->items_0[g_SysWork.playerCombatInfo_38.field_12].id_0 + 32))
        {
            g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11;

            if (!g_SavegamePtr->items_0[i].count_1)
            {
                g_SavegamePtr->items_0[i].id_0 = NO_VALUE;
            }

            g_SavegamePtr->inventoryItemSpaces_AB = func_8004F190(g_SavegamePtr);
            break;
        }
    }

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            D_800C3B68[i][j].vy = 0;
            D_800C3B68[i][j].vx = 0;
        }
    }

    D_800AE18C = 0;
    D_800AE18E = 0;

    Fs_QueueStartReadTim(FILE_ITEM_HEROPIC2_TIM, FS_BUFFER_1, &g_HealthPortraitImg);
}

// TODO: RODATA migration.
#ifdef NON_MATCHING
// Item rendering related.
void Gfx_Items_RenderItems() // 0x80054200
{
    s32  temp_s5;
    s32  i;
    s32  itemIdx;
    s32  specialItemIdx;
    s32* var_s1;
    s32* var_s2;

    func_8004BFE8();

    D_800AE190 = 0;

    func_8004BB4C(&D_800C3B48, &D_800C3AE8, &D_800C3B38, 0);

	/** This loops define the position, rotation and scale of the item that
	* the player has initially equipped in the inventory.
	*/
    for (i = 0; i < 10; i++)
    {
        D_800C3E18[i] = NO_VALUE;

        g_Items_Items3dData0[i].scale_0.vz     = FP_METER(1.0f);
        g_Items_Items3dData0[i].scale_0.vy     = FP_METER(1.0f);
        g_Items_Items3dData0[i].scale_0.vx     = FP_METER(1.0f);
        g_Items_Items3dData0[i].rotation_10.vz = 0;
        g_Items_Items3dData0[i].rotation_10.vy = 0;
        g_Items_Items3dData0[i].rotation_10.vx = 0;
        g_Items_Items3dData0[i].field_18.vz    = 0;
        g_Items_Items3dData0[i].field_18.vy    = 0;
        g_Items_Items3dData0[i].field_18.vx    = 0;
    }

    func_8004BCBC(FS_BUFFER_8);

    temp_s5 = (g_SysWork.inventoryItemSelectedIdx_2351 - 3 + g_SavegamePtr->inventoryItemSpaces_AB) % g_SavegamePtr->inventoryItemSpaces_AB;

    if (g_GameWork.gameStateStep_598[1] < 21) // If screen is inventory
    {
        for (specialItemIdx = 0; specialItemIdx < 7; specialItemIdx++)
        {
            D_800C3E18[specialItemIdx] = (temp_s5 + specialItemIdx) % g_SavegamePtr->inventoryItemSpaces_AB;

            if (g_SavegamePtr->items_0[D_800C3E18[specialItemIdx]].id_0 == 0xFF)
            {
                continue;
            }

            for (itemIdx = 0; itemIdx < INVENTORY_ITEM_COUNT_MAX; itemIdx++)
            {
                if (g_SavegamePtr->items_0[D_800C3E18[specialItemIdx]].id_0 == D_800C3BB8[itemIdx])
                {
                    func_80054720(FS_BUFFER_8, specialItemIdx, itemIdx);
                    func_8005487C(specialItemIdx);

                    itemIdx = INVENTORY_ITEM_COUNT_MAX;
                }
            }
        }

        g_Inventory_EquippedItem = g_SavegamePtr->equippedWeapon_AA;

        for (i = 0; i < g_SavegamePtr->inventoryItemSpaces_AB; i++)
        {
            if (g_SavegamePtr->items_0[i].id_0 == g_Inventory_EquippedItem)
            {
                D_800C3E18[7] = i;

                i = g_SavegamePtr->inventoryItemSpaces_AB;
            }
        }

        if (g_Inventory_EquippedItemIdx != NO_VALUE) // If player has something equipped
        {
            for (itemIdx = 0; itemIdx < INVENTORY_ITEM_COUNT_MAX; itemIdx++)
            {
                if (g_Inventory_EquippedItem == D_800C3BB8[itemIdx])
                {
                    func_80054720(FS_BUFFER_8, 7, itemIdx);
                    func_8005487C(7);

                    itemIdx = INVENTORY_ITEM_COUNT_MAX;
                }
            }
        }

        g_Items_Items3dData1[7].coord.t[0] = 0;
        g_Items_Items3dData1[7].coord.t[1] = FP_METER(-0.15625f);
        g_Items_Items3dData1[7].coord.t[2] = 0;
    }
    else
    {
        u8 itemIds[] = // 0x8002848C .rodata
        {
            InventoryItemId_GasolineTank,
            InventoryItemId_Chainsaw,
            InventoryItemId_RockDrill,
            InventoryItemId_Katana,
            InventoryItemId_ChannelingStone,
            InventoryItemId_HyperBlaster
        };

        if (g_SavegamePtr->clearGameCount_24A == 0)
        {
            g_SavegamePtr->clearGameCount_24A = 1;
        }

        for (specialItemIdx = 0; specialItemIdx < 6; specialItemIdx++)
        {
            D_800C3E18[specialItemIdx] = specialItemIdx;

            for (itemIdx = 0; itemIdx < INVENTORY_ITEM_COUNT_MAX; itemIdx++)
            {
                if (itemIds[specialItemIdx] == D_800C3BB8[itemIdx])
                {
                    func_80054720(FS_BUFFER_8, specialItemIdx, itemIdx);
                    func_8005487C(specialItemIdx);

                    itemIdx = INVENTORY_ITEM_COUNT_MAX;
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", Gfx_Items_RenderItems); // 0x80054200
#endif

void Gfx_Items_RenderInit() // 0x80054558
{
    s32 i;

    D_800AE180                                 = 0;
    D_800AE187                                 = 0;
    g_Inventory_HealthStatusScanlineTimer      = 32;
    g_Inventory_HealthStatusColorGradientTimer = 0;
    D_800AE198                                 = 0;
    g_Inventory_HealthStatusScanlinePosition   = -300;
    g_Inventory_ItemNameTimer                  = 0;
    g_Inventory_DescriptionRollTimer           = 0;
    g_Inventory_ScrollTransitionTimer          = 0;

    for (i = 0; g_MapOverlayHeader.field_2C->field_0[i] != 0; i++)
    {
        D_800C3BB8[i] = g_MapOverlayHeader.field_2C->field_0[i];
    }

    D_800C3BB8[i] = 0;

    Gfx_Items_RenderItems();
    Gfx_Items_SetAmbientLighting();
}

void Inventory_ExitAnimFixes() // 0x80054634
{
    u8 field_F;

    field_F                          = (u8)g_SysWork.playerCombatInfo_38.field_F;
    g_SavegamePtr->equippedWeapon_AA = g_Inventory_EquippedItem;

    if (g_SavegamePtr->equippedWeapon_AA)
    {
        g_SysWork.playerCombatInfo_38.field_F = g_SavegamePtr->equippedWeapon_AA + 0x80;
    }
    else
    {
        g_SysWork.playerCombatInfo_38.field_F     = NO_VALUE;
        g_SysWork.playerCombatInfo_38.isAiming_13 = 0;
    }

    func_800546A8((u8)g_SysWork.playerCombatInfo_38.field_F);
    Inventory_ExitAnimEquippedItemUpdate(&field_F);
}

// TODO: RODATA migration.
#ifdef NON_MATCHING
void func_800546A8(s32 arg0) // 0x800546A8
{
    switch ((u8)arg0)
    {
        case InventoryItemId_Unequipped:
            func_8003DD80(1, 34);
            break;

        case 1:
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
            func_8003DD80(1, 34);
            break;

        case InventoryItemId_HealthDrink:
        case InventoryItemId_FirstAidKit:
        case InventoryItemId_Ampoule:
            func_8003DD80(1, 19);
            break;

        default:
            func_8003DD80(1, 1);
            break;
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", func_800546A8); // 0x800546A8
#endif

void func_80054720(s_TmdFile* tmd, s32 arg1, s32 arg2) 
{
    u8                 var_v0;
    GsDOBJ2*           ptr;
    struct TMD_STRUCT* objs;
	
	objs = tmd->objects_C;

    GsLinkObject4((u32)&objs[arg2], &D_800C3D78[arg1], 0);

    ptr         = &D_800C3D78[arg1];
    ptr->coord2 = &g_Items_Items3dData1[arg1];

    if (D_800AE187 != 0)
    {
        var_v0 = D_800AE187;
    }
    else
    {
        var_v0 = g_MapOverlayHeader.field_2C->field_0[arg2];
    }

    switch (var_v0) 
    {
        case InventoryItemId_HealthDrink: 
        case InventoryItemId_FirstAidKit: 
        case InventoryItemId_Ampoule:
        case InventoryItemId_KitchenKnife: 
        case InventoryItemId_SteelPipe:
        case InventoryItemId_Hammer: 
        case InventoryItemId_Chainsaw:
        case InventoryItemId_Handgun: 
        case InventoryItemId_HuntingRifle: 
        case InventoryItemId_Shotgun:
        case InventoryItemId_HandgunBullets: 
        case InventoryItemId_RifleShells: 
        case InventoryItemId_ShotgunShells:
        case InventoryItemId_Flashlight: 
        case InventoryItemId_PocketRadio:
        case InventoryItemId_Axe:
            ptr->attribute = 0;
            break;

        default:
            ptr->attribute = 0x40000000;
            break;
    }

    if (D_800AE180 < 10)
    {
        D_800AE180++;
    }
}

void func_8005487C(s32 arg0) // 0x8005487C
{
    GsInitCoordinate2(NULL, &g_Items_Items3dData1[arg0]);
    g_Items_Items3dData1[arg0].param = (GsCOORD2PARAM*) &g_Items_Items3dData0[arg0];
}

/** Something related to items lighting. */
void func_800548D8(s32 arg0) // 0x800548D8
{
    g_Items_ItemsLightingData[arg0][0].vx = g_Items_Items3dData1[arg0].coord.t[0];
    g_Items_ItemsLightingData[arg0][0].vy = g_Items_Items3dData1[arg0].coord.t[1];
    g_Items_ItemsLightingData[arg0][0].vz = g_Items_Items3dData1[arg0].coord.t[2] + 20000;
}

void Gfx_Items_SetAmbientLighting() // 0x80054928
{
    s32 i;

    for (i = 0; i < 10; i++)
    {
        g_Items_ItemsLightingData[i][0].r  = NO_VALUE;
        g_Items_ItemsLightingData[i][0].g  = NO_VALUE;
        g_Items_ItemsLightingData[i][0].b  = NO_VALUE;
        g_Items_ItemsLightingData[i][1].vx = FP_TO(1, Q12_SHIFT);
        g_Items_ItemsLightingData[i][1].vy = 0;
        g_Items_ItemsLightingData[i][1].vz = 0;
        g_Items_ItemsLightingData[i][1].r  = NO_VALUE;
        g_Items_ItemsLightingData[i][1].g  = NO_VALUE;
        g_Items_ItemsLightingData[i][1].b  = NO_VALUE;
    }

    GsSetAmbient(1024, 1024, 1024);
    GsSetLightMode(1);
}

// Similar to `Gfx_Items_SetAmbientLighting`.
void func_800549A0() // 0x800549A0
{
    #define IDX 9

    g_Items_ItemsLightingData[IDX][0].r  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].vx = FP_FLOAT_TO(1.0f, Q12_SHIFT);
    g_Items_ItemsLightingData[IDX][0].g  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][0].b  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].r  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].g  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].b  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].vy = 0;
    g_Items_ItemsLightingData[IDX][1].vz = 0;

    GsSetAmbient(2048, 2048, 2048);
    GsSetLightMode(1);
}

void func_80054A04(u8 itemId) // 0x80054A04
{
    D_800AE187 = itemId;
    D_800AE180 = 0;
    D_800AE1AC = 0;
    D_800AE1B0 = 0;

    D_800C3E18[9]                           = NO_VALUE;
    g_Items_Items3dData0[9].rotation_10.vz = 0;
    g_Items_Items3dData0[9].rotation_10.vy = 0;
    g_Items_Items3dData0[9].rotation_10.vx = 0;
    g_Items_Items3dData0[9].field_18.vz    = 0;
    g_Items_Items3dData0[9].field_18.vy    = 0;
    g_Items_Items3dData0[9].field_18.vx    = 0;

    func_8004BCBC(FS_BUFFER_5);

    D_800C3E18[9] = 0;

    func_80054720(FS_BUFFER_5, 9, 0);
    func_8005487C(9);

    g_Items_Items3dData0[9].scale_0.vz = FP_FLOAT_TO(1.0f, Q12_SHIFT);
    g_Items_Items3dData0[9].scale_0.vy = FP_FLOAT_TO(1.0f, Q12_SHIFT);
    g_Items_Items3dData0[9].scale_0.vx = FP_FLOAT_TO(1.0f, Q12_SHIFT);

    func_800549A0();
    func_8004BB4C(&D_800C3B48, &D_800C3AE8, &D_800C3B38, 0);
}

s32 func_80054AD8(u8 arg0) // 0x80054AD8
{
    s32 temp_a1;
    GsDOBJ2* obj;
    s_Items3dData* ptr;
    s16 x, y;

    g_Items_Items3dData1[9].coord.t[1] = 0x40;
    g_Items_Items3dData1[9].coord.t[0] = 0;
    g_Items_Items3dData1[9].coord.t[2] = -0x20B0;

    switch (D_800AE1AC) 
    {
        case 0:
            if (D_800AE1B0 >= 0x800) 
            {
                D_800AE1AC = 1;
            }

            ptr     = &g_Items_Items3dData0;
            temp_a1 = D_800AE1B0 << 12;

            x = D_800262FC[arg0 - 32].vx;
            y = D_800262FC[arg0 - 32].vy;

            ptr[9].scale_0.vz     = temp_a1 >> 11;
            ptr[9].scale_0.vy     = temp_a1 >> 11;
            ptr[9].scale_0.vx     = temp_a1 >> 11;

            ptr[9].rotation_10.vx = x;
            ptr[9].rotation_10.vy = 0;
            ptr[9].rotation_10.vz = y;
            break;

        case 1:
            g_Items_Items3dData0[9].scale_0.vz = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[9].scale_0.vy = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[9].scale_0.vx = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            D_800AE1AC = 2;
            break;
    }

    D_800AE1B0 += (g_DeltaTime1 * 2);
    D_800AE1B0  = CLAMP(D_800AE1B0, 0, 0x800);

    PushMatrix();
    func_8004BBF4(&D_800C3B48, &D_800C3AE8, &D_800C3B38);

    obj = &D_800C3E08;

    Gfx_Results_ItemsRotate(&g_Items_Items3dData1[9].param->rotate, &g_Items_Items3dData1[9]);

    g_Items_Items3dData0[9].rotation_10.vy += g_DeltaTime1 >> 1;

    func_800548D8(9);
    GsSetFlatLight(0, &D_800C3AC8[0]);
    GsSetFlatLight(1, &D_800C3AC8[1]);
    func_8004BD74(9, obj, 2);
    PopMatrix();

    return D_800AE1AC > 0;
}

// TODO: RODATA migration.
#ifdef NON_MATCHING
void func_80054CAC(u8 itemId, s32 itemCount) // 0x80054CAC
{
    switch (itemId)
    {
        case InventoryItemId_RockDrill:
        case InventoryItemId_Chainsaw:
        case InventoryItemId_Katana:
        case InventoryItemId_HyperBlaster:
        case InventoryItemId_GasolineTank:
            g_SavegamePtr->hyperBlasterFlags_25C_3++; // `pickedUpSpecialItemCount`?
            break;

        case InventoryItemId_ChannelingStone:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_ChannelingStone))
            {
                g_SavegamePtr->hyperBlasterFlags_25C_3++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_ChannelingStone; // `specialItemFlags`?
            }
            break;

        case InventoryItemId_PlateOfTurtle:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_PlateOfTurtle))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_PlateOfTurtle;
            }
            break;

        case InventoryItemId_PlateOfHatter:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_PlateOfHatter))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_PlateOfHatter;
            }
            break;

        case InventoryItemId_PlateOfCat:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_PlateOfCat))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_PlateOfCat;
            }
            break;

        case InventoryItemId_PlateOfQueen:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_PlateOfQueen))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_PlateOfQueen;
            }
            break;

        case InventoryItemId_Lighter:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_Lighter))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_Lighter;
            }
            break;

        case InventoryItemId_VideoTape:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_VideoTape))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_VideoTape;
            }
            break;

        case InventoryItemId_Camera:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_Camera))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_Camera;
            }
            break;

        default:
            g_SavegamePtr->pickedUpItemCount_23C++;
            break;
    }

    g_SavegamePtr->items_0[g_SavegamePtr->inventoryItemSpaces_AB].id_0    = itemId;
    g_SavegamePtr->items_0[g_SavegamePtr->inventoryItemSpaces_AB].count_1 = itemCount;
    g_SavegamePtr->inventoryItemSpaces_AB                                 = func_8004F190(g_SavegamePtr);
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/item_screens", func_80054CAC); // 0x80054CAC
#endif
