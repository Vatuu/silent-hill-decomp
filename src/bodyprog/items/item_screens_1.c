#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/math.h"

void Inventory_ExitAnimEquippedItemUpdate(u8* arg0) // 0x8004C088
{
    s8       temp_v0;
    s32      playerState;
    s_Model* modelPtr3;
    s_Model* extraModelPtr2;
    s_Model* extraModelPtr0;
    s_Model* extraModelPtr1;
    s_Model* modelPtr0;
    s_Model* modelPtr1;

    Game_PlayerMovementsReset();

    playerState = g_SysWork.player_4C.extra_128.state_1C;

    if (g_SysWork.player_4C.extra_128.state_1C < PlayerState_Idle &&
        playerState >= PlayerState_None)
    {
        if (D_800C3950 != g_SysWork.playerCombatInfo_38.equippedWeapon_F)
        {
            g_SysWork.playerCombatInfo_38.isAiming_13 = false;
        }

        temp_v0 = D_800C3950 % 10;

        if (temp_v0 == 5 && g_SysWork.playerCombatInfo_38.equippedWeapon_F != temp_v0)
        {
            goto Inventory_ExitAnimEquippedItemUpdate_block; // TODO: Remove goto if possible.
        }

        if (temp_v0 == 2 && g_SysWork.playerCombatInfo_38.equippedWeapon_F != temp_v0)
        {
        Inventory_ExitAnimEquippedItemUpdate_block:
            g_SysWork.player_4C.chara_0.field_44                                     = 0;
            g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
        }

        switch (g_SysWork.player_4C.extra_128.lowerBodyState_24)
        {
            case PlayerLowerBodyState_QuickTurnRight:
            case PlayerLowerBodyState_QuickTurnLeft:
            case PlayerLowerBodyState_JumpBackward:
            case PlayerLowerBodyState_AimQuickTurnRight:
            case PlayerLowerBodyState_AimQuickTurnLeft:
                break;

            default:

                if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_Combat && (s8)D_800C3950 != g_SysWork.playerCombatInfo_38.equippedWeapon_F)
                {
                    g_SysWork.player_4C.extra_128.state_1C                     = PlayerState_None;
                    g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C = PlayerFlag_None;
                }

                if (g_SysWork.player_4C.extra_128.lowerBodyState_24 >= PlayerLowerBodyState_Aim && g_SysWork.playerCombatInfo_38.equippedWeapon_F != NO_VALUE &&
                    (s8)D_800C3950 == g_SysWork.playerCombatInfo_38.equippedWeapon_F)
                {
                    extraModelPtr0 = &g_SysWork.player_4C.extra_128.model_0;
                    if (extraModelPtr0->anim_4.status_0 >= ANIM_STATUS(33, false))
                    {
                        modelPtr0                                         = &g_SysWork.player_4C.chara_0.model_0;
                        extraModelPtr0->anim_4.status_0                 -= 10;
                        g_SysWork.player_4C.chara_0.model_0.state_2       = 0;
                        g_SysWork.player_4C.chara_0.model_0.stateStep_3   = 0;
                        g_SysWork.player_4C.extra_128.model_0.state_2     = 0;
                        g_SysWork.player_4C.extra_128.model_0.stateStep_3 = 0;
                        modelPtr0->anim_4.status_0                      -= 10;
                    }
                }
                else
                {
                    modelPtr1      = &g_SysWork.player_4C.chara_0.model_0;
                    extraModelPtr1 = &g_SysWork.player_4C.extra_128.model_0;

                    modelPtr1->anim_4.status_0                       = ANIM_STATUS(1, true);
                    modelPtr1->anim_4.keyframeIdx0_8                  = 0;
                    extraModelPtr1->anim_4.status_0                  = ANIM_STATUS(1, true);
                    extraModelPtr1->anim_4.keyframeIdx0_8             = 0;
                    g_SysWork.player_4C.chara_0.model_0.state_2       = 0;
                    g_SysWork.player_4C.chara_0.model_0.stateStep_3   = 0;
                    g_SysWork.player_4C.extra_128.upperBodyState_20   = PlayerUpperBodyState_None;
                    g_SysWork.player_4C.extra_128.lowerBodyState_24   = PlayerLowerBodyState_None;
                    g_SysWork.player_4C.extra_128.model_0.state_2     = 0;
                    g_SysWork.player_4C.extra_128.model_0.stateStep_3 = 0;
                }

                g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
                g_SysWork.player_4C.chara_0.properties_E4.player.afkTimer_E8            = 0;
        }
    }

    modelPtr3      = &g_SysWork.player_4C.chara_0.model_0;
    extraModelPtr2 = &g_SysWork.player_4C.extra_128.model_0;

    modelPtr3->anim_4.keyframeIdx1_A       = 4096;
    extraModelPtr2->anim_4.keyframeIdx1_A  = 4096;
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

    for (; (itemId = g_SavegamePtr->items_0[itemIdx].id_0) != InventoryItemId_Unequipped; itemIdx++)
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

s32 Inventory_HyperBlasterUnlockTest() // 0x8004C45C
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
        if (g_SavegamePtr->clearGameCount_24A != 0 && (g_SavegamePtr->clearGameEndings_24B & GameEndingFlag_Ufo))
        {
            return 1;
        }
    }

    return 0;
}

s32 Inventory_HyperBlasterFunctionalTest() // 0x8004C4F8
{
    if (g_SavegamePtr->mapOverlayId_A4 > MapOverlayId_MAP0_S00)
    {
        if ((g_SavegamePtr->clearGameEndings_24B & GameEndingFlag_Ufo) != 0)
        {
            // Game completed with Ufo ending.
            return 2;
        }

        // Returns 1 if controller port 2 has Konami gun controller connected.
        return g_GameWork.controllers_38[1].analogController_0.status         == 0 &&
               g_GameWork.controllers_38[1].analogController_0.received_bytes == 1 &&
               g_GameWork.controllers_38[1].analogController_0.terminal_type  == PadTerminalType_GunControllerKonami;
    }

	// Neither of the conditions has been completed.
    return 0;
}

u32 Game_HyperBlasterBeamColorGet() // 0x8004C54C
{
    return g_SavegamePtr->pickedUpSpecialItemCount_25C_3 >> 3;
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
            g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
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
                    D_800C3963                                                               = 0;
                    D_800C3962                                                               = 0;
                    g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
                    g_SysWork.player_4C.chara_0.field_44                                     = 0;
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

                    g_SysWork.player_4C.chara_0.properties_E4.player.gasWeaponPowerTimer_114 = FP_FLOAT_TO(0.0f, Q12_SHIFT);
                    D_800C3963                                                              -= 2;
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
