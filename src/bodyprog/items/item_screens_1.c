#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/math/math.h"

static const s32 pad_rodata_80025E90 = 0;


s8 D_800C3960;

s8 D_800C3961;

s8 D_800C3962;

u8 D_800C3963;

s32 pad_bss_800C3964;

void Inventory_ExitAnimEquippedItemUpdate(u8* weaponId) // 0x8004C088
{
    s8       weaponAttack; // Packed weapon attack. See `WEAPON_ATTACK`.
    s32      playerState;
    s_Model* modelPtr3;
    s_Model* extraModelPtr2;
    s_Model* extraModelPtr0;
    s_Model* extraModelPtr1;
    s_Model* modelPtr0;
    s_Model* modelPtr1;

    Game_PlayerMovementsReset();

    playerState = g_SysWork.playerWork_4C.extra_128.state_1C;

    if (g_SysWork.playerWork_4C.extra_128.state_1C < PlayerState_Idle &&
        playerState >= PlayerState_None)
    {
        if (g_Player_WeaponAttack != g_SysWork.playerCombat_38.weaponAttack_F)
        {
            g_SysWork.playerCombat_38.isAiming_13 = false;
        }

        weaponId = WEAPON_ATTACK_ID_GET(g_Player_WeaponAttack);
        if (weaponId == EquippedWeaponId_Chainsaw &&
            g_SysWork.playerCombat_38.weaponAttack_F != weaponId)
        {
            goto Inventory_ExitAnimEquippedItemUpdate_block; // TODO: Remove goto if possible.
        }

        if (weaponId == EquippedWeaponId_RockDrill &&
            g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(weaponId, AttackInputType_Tap))
        {
        Inventory_ExitAnimEquippedItemUpdate_block:
            g_SysWork.playerWork_4C.player_0.field_44.field_0                             = 0;
            g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 = Q12(0.0f);
        }

        switch (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24)
        {
            case PlayerLowerBodyState_QuickTurnRight:
            case PlayerLowerBodyState_QuickTurnLeft:
            case PlayerLowerBodyState_JumpBackward:
            case PlayerLowerBodyState_AimQuickTurnRight:
            case PlayerLowerBodyState_AimQuickTurnLeft:
                break;

            default:

                if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_Combat &&
                    g_Player_WeaponAttack != g_SysWork.playerCombat_38.weaponAttack_F)
                {
                    g_SysWork.playerWork_4C.extra_128.state_1C                     = PlayerState_None;
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C = PlayerFlag_None;
                }

                if (g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 >= PlayerLowerBodyState_Aim &&
                    g_SysWork.playerCombat_38.weaponAttack_F != NO_VALUE &&
                    g_Player_WeaponAttack == g_SysWork.playerCombat_38.weaponAttack_F)
                {
                    extraModelPtr0 = &g_SysWork.playerWork_4C.extra_128.model_0;
                    if (extraModelPtr0->anim_4.status_0 >= ANIM_STATUS(33, false))
                    {
                        modelPtr0                                         = &g_SysWork.playerWork_4C.player_0.model_0;
                        extraModelPtr0->anim_4.status_0                 -= 10;
                        g_SysWork.playerWork_4C.player_0.model_0.controlState_2       = ModelState_Uninitialized;
                        g_SysWork.playerWork_4C.player_0.model_0.stateStep_3   = 0;
                        g_SysWork.playerWork_4C.extra_128.model_0.controlState_2     = ModelState_Uninitialized;
                        g_SysWork.playerWork_4C.extra_128.model_0.stateStep_3 = 0;
                        modelPtr0->anim_4.status_0                      -= 10;
                    }
                }
                else
                {
                    modelPtr1      = &g_SysWork.playerWork_4C.player_0.model_0;
                    extraModelPtr1 = &g_SysWork.playerWork_4C.extra_128.model_0;

                    modelPtr1->anim_4.status_0                        = ANIM_STATUS(HarryAnim_TransitionToStill, true);
                    modelPtr1->anim_4.keyframeIdx_8                   = 0;
                    extraModelPtr1->anim_4.status_0                   = ANIM_STATUS(HarryAnim_TransitionToStill, true);
                    extraModelPtr1->anim_4.keyframeIdx_8              = 0;

                    g_SysWork.playerWork_4C.player_0.model_0.controlState_2       = ModelState_Uninitialized;
                    g_SysWork.playerWork_4C.player_0.model_0.stateStep_3   = 0;
                    g_SysWork.playerWork_4C.extra_128.upperBodyState_20   = PlayerUpperBodyState_None;
                    g_SysWork.playerWork_4C.extra_128.lowerBodyState_24   = PlayerLowerBodyState_None;
                    g_SysWork.playerWork_4C.extra_128.model_0.controlState_2     = ModelState_Uninitialized;
                    g_SysWork.playerWork_4C.extra_128.model_0.stateStep_3 = 0;
                }

                g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
                g_SysWork.playerWork_4C.player_0.properties_E4.player.afkTimer_E8            = Q12(0.0f);
        }
    }

    modelPtr3      = &g_SysWork.playerWork_4C.player_0.model_0;
    extraModelPtr2 = &g_SysWork.playerWork_4C.extra_128.model_0;

    // Set animation alpha.
    modelPtr3->anim_4.alpha_A      = Q12(1.0f);
    extraModelPtr2->anim_4.alpha_A = Q12(1.0f);

    // Disable upper body bones.
    g_SysWork.playerWork_4C.extra_128.disabledAnimBones_18 = HARRY_UPPER_BODY_BONE_MASK;

    // Set animation time.
    modelPtr3->anim_4.time_4      = Q12(modelPtr3->anim_4.keyframeIdx_8);
    extraModelPtr2->anim_4.time_4 = Q12(extraModelPtr2->anim_4.keyframeIdx_8);

    Anim_BoneUpdate((s_AnmHeader*)FS_BUFFER_0, g_SysWork.playerBoneCoords_890, modelPtr3->anim_4.keyframeIdx_8, modelPtr3->anim_4.keyframeIdx_8, Q12(1.0f));

    // Re-enable upper body bones, disable lower body bones.
    g_SysWork.playerWork_4C.extra_128.disabledAnimBones_18 = HARRY_LOWER_BODY_BONE_MASK;

    Anim_BoneUpdate((s_AnmHeader*)FS_BUFFER_0, g_SysWork.playerBoneCoords_890, extraModelPtr2->anim_4.keyframeIdx_8, extraModelPtr2->anim_4.keyframeIdx_8, Q12(1.0f));
    func_8004C040();
}

bool func_8004C328(bool unused) // 0x8004C328
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

        if (g_SysWork.playerCombat_38.weaponInventoryIdx_12 != NO_VALUE && itemIdx == g_SysWork.playerCombat_38.weaponInventoryIdx_12)
        {
            if (itemId >= InventoryItemId_Handgun && itemId <= InventoryItemId_Shotgun)
            {
                if (g_SysWork.playerCombat_38.currentWeaponAmmo_10 != 0)
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

        // Checks if player has ammo.
        switch (itemId)
        {
            case InventoryItemId_HuntingRifle:
            case InventoryItemId_Shotgun:
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

s32 Inventory_HyperBlasterUnlockTest(void) // 0x8004C45C
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

s32 Inventory_HyperBlasterFunctionalTest(void) // 0x8004C4F8
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

s32 Game_HyperBlasterBeamColorGet(void) // 0x8004C54C
{
    return g_SavegamePtr->pickedUpSpecialItemCount_25C_3 >> 3;
}

void func_8004C564(u8 arg0, s8 weaponAttack) // 0x8004C564
{
    s32 temp_v1;

    switch (weaponAttack)
    {
        case -1:
            D_800C3960 = g_SavegamePtr->mapOverlayId_A4;
            D_800C3962 = 0;
            D_800C3963 = 0;
            D_800C3961 = 32;

            func_8008B398();

            g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 = Q12(0.0f);
            break;

        case 0:
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

        case 1:
            if (arg0 == (1 << 1))
            {
                func_8008B40C((u8)D_800C3961, D_800C3962);
                D_800C3963 |= 1 << 2;
            }
            break;

        case 2:
            if (D_800C3961 != 0)
            {
                D_800C3961 -= ((g_DeltaTime / 68) == 0) ? 1 : (g_DeltaTime / 68);
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
                    D_800C3963                                                                    = 0;
                    D_800C3962                                                                    = 0;
                    g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 = Q12(0.0f);
                    g_SysWork.playerWork_4C.player_0.field_44.field_0                             = 0;
                }
            }
            break;

        case 3:
            if (D_800C3963 & (1 << 1))
            {
                if (!(D_800C3963 & (1 << 2)))
                {
                    func_8008B438(0, 0, 0);
                    func_8008B3E4(0);

                    g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 = Q12(0.0f);
                    D_800C3963                                                              -= 2;
                }
            }
            break;

        case 4:
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
