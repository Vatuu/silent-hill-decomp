#include "game.h"
#include "inline_no_dmpsx.h"
#include "gtemac.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/rng.h"

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

void GameFs_UniqueItemModelLoad(s32 itemId) // 0x80053B08
{
    switch (itemId & 0xFF)
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

void GameFs_Tim00TIMLoad() // 0x80053dA0
{
    if (g_SysWork.flags_2352 & (1 << 0))
    {
        return;
    }

    Fs_QueueStartReadTim(FILE_ITEM_TIM00_TIM, FS_BUFFER_1, &D_800A906C);
    g_SysWork.flags_2352 |= 1 << 0;
}

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
                Fs_QueueStartReadTim(FILE_ITEM_TIM01_TIM, FS_BUFFER_1, &D_800A9064);
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
                Fs_QueueStartReadTim(FILE_ITEM_TIM02_TIM, FS_BUFFER_1, &D_800A9064);
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
                Fs_QueueStartReadTim(FILE_ITEM_TIM03_TIM, FS_BUFFER_1, &D_800A9064);
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
                Fs_QueueStartReadTim(FILE_ITEM_TIM04_TIM, FS_BUFFER_1, &D_800A9064);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 4);
            }
            break;

        case MapOverlayId_MAP7_S00:
        case MapOverlayId_MAP7_S01:
            if (!(g_SysWork.flags_2352 & (1 << 5)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM05_TIM, FS_BUFFER_1, &D_800A9064);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 5);
            }
            break;

        case MapOverlayId_MAP7_S02:
        case MapOverlayId_MAP7_S03:
            if (!(g_SysWork.flags_2352 & (1 << 6)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM06_TIM, FS_BUFFER_1, &D_800A9064);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 6);
            }
            break;

        case 0:
            break;
    }
}

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

/** @brief Function related to file loading of inventory element.
* This function loads Harry's potrait for the status image. */
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800540A4); // 0x800540A4

void func_80054200() // 0x80054200
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

    for (i = 0; i < 10; i++)
    {
        D_800C3E18[i] = NO_VALUE;

        D_800C3BE8[i].field_0.vz  = FP_METER(1.0f);
        D_800C3BE8[i].field_0.vy  = FP_METER(1.0f);
        D_800C3BE8[i].field_0.vx  = FP_METER(1.0f);
        D_800C3BE8[i].field_10.vz = 0;
        D_800C3BE8[i].field_10.vy = 0;
        D_800C3BE8[i].field_10.vx = 0;
        D_800C3BE8[i].field_18.vz = 0;
        D_800C3BE8[i].field_18.vy = 0;
        D_800C3BE8[i].field_18.vx = 0;
    }

    func_8004BCBC(FS_BUFFER_8);

    temp_s5 = (g_SysWork.field_2351 - 3 + g_SavegamePtr->field_AB) % g_SavegamePtr->field_AB;

    if (g_GameWork.gameStateStep_598[1] < 21)
    {
        for (specialItemIdx = 0; specialItemIdx < 7; specialItemIdx++)
        {
            D_800C3E18[specialItemIdx] = (temp_s5 + specialItemIdx) % g_SavegamePtr->field_AB;

            if (g_SavegamePtr->items_0[D_800C3E18[specialItemIdx]].id_0 == 0xFF)
            {
                continue;
            }

            for (itemIdx = 0; itemIdx < 40; itemIdx++)
            {
                if (g_SavegamePtr->items_0[D_800C3E18[specialItemIdx]].id_0 == D_800C3BB8[itemIdx])
                {
                    func_80054720(FS_BUFFER_8, specialItemIdx, itemIdx);
                    func_8005487C(specialItemIdx);

                    itemIdx = 40;
                }
            }
        }

        D_800AE184 = g_SavegamePtr->equippedWeapon_AA;

        for (i = 0; i < g_SavegamePtr->field_AB; i++)
        {
            if (g_SavegamePtr->items_0[i].id_0 == D_800AE184)
            {
                D_800C3E18[7] = i;

                i = g_SavegamePtr->field_AB;
            }
        }

        if (D_800C3E34 != NO_VALUE)
        {
            for (itemIdx = 0; itemIdx < 40; itemIdx++)
            {
                if (D_800AE184 == D_800C3BB8[itemIdx])
                {
                    func_80054720(FS_BUFFER_8, 7, itemIdx);
                    func_8005487C(7);

                    itemIdx = 40;
                }
            }
        }

        D_800C3E48.field_248.vx = 0;
        D_800C3E48.field_248.vy = FP_METER(-0.15625f);
        D_800C3E48.field_248.vz = 0;
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

            for (itemIdx = 0; itemIdx < 40; itemIdx++)
            {
                if (itemIds[specialItemIdx] == D_800C3BB8[itemIdx])
                {
                    func_80054720(FS_BUFFER_8, specialItemIdx, itemIdx);
                    func_8005487C(specialItemIdx);

                    itemIdx = 40;
                }
            }
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80054558); // 0x80054558

void func_80054634() // 0x80054634
{
    u8 field_F;

    field_F                          = (u8)g_SysWork.field_38.field_F;
    g_SavegamePtr->equippedWeapon_AA = D_800AE184;

    if (g_SavegamePtr->equippedWeapon_AA & 0xFF)
    {
        g_SysWork.field_38.field_F = g_SavegamePtr->equippedWeapon_AA + 0x80;
    }
    else
    {
        g_SysWork.field_38.field_F        = NO_VALUE;
        g_SysWork.isPlayerInCombatMode_4B = 0;
    }

    func_800546A8((u8)g_SysWork.field_38.field_F);
    Player_AnimUpdate(&field_F);
}

void func_800546A8(s32 arg0) // 0x800546A8
{
    switch ((u8)arg0)
    {
        case 0:
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

        case 32:
        case 33:
        case 34:
            func_8003DD80(1, 19);
            break;

        default:
            func_8003DD80(1, 1);
            break;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80054720); // 0x80054720

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005487C); // 0x8005487C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800548D8); // 0x800548D8

void func_80054928() // 0x80054928
{
    s32         i;
    s_800C39A8* ptr;

    for (i = 0; i < 10; i++)
    {
        u8 val = 0xFF;
        ptr = &D_800C39A8[i];
        ptr->field_C  = val;
        ptr->field_D  = val;
        ptr->field_E  = val;
        ptr->field_10 = 1 << 12;
        ptr->field_14 = 0;
        ptr->field_18 = 0;
        ptr->field_1C = val;
        ptr->field_1D = val;
        ptr->field_1E = val;
    }

    GsSetAmbient(1024, 1024, 1024);
    GsSetLightMode(1);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800549A0); // 0x800549A0

void func_80054A04(s32 arg0) // 0x80054A04
{
    D_800AE187 = arg0;
    D_800AE180 = 0;
    D_800AE1AC = 0;
    D_800AE1B0 = 0;

    D_800C3E18[9]             = NO_VALUE;
    D_800C3BE8[9].field_10.vz = 0;
    D_800C3BE8[9].field_10.vy = 0;
    D_800C3BE8[9].field_10.vx = 0;
    D_800C3BE8[9].field_18.vz = 0;
    D_800C3BE8[9].field_18.vy = 0;
    D_800C3BE8[9].field_18.vx = 0;

    func_8004BCBC(FS_BUFFER_5);

    D_800C3E18[9] = 0;

    func_80054720(FS_BUFFER_5, 9, 0);
    func_8005487C(9);

    D_800C3BE8[9].field_0.vz = 1 << 12;
    D_800C3BE8[9].field_0.vy = 1 << 12;
    D_800C3BE8[9].field_0.vx = 1 << 12;

    func_800549A0();
    func_8004BB4C(&D_800C3B48, &D_800C3AE8, &D_800C3B38, 0);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80054AD8); // 0x80054AD8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80054CAC); // 0x80054CAC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80054FC0); // 0x80054FC0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80055028); // 0x80055028

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800550D0); // 0x800550D0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80055330); // 0x80055330

void func_800553C4(s8 arg0, s8 arg1, s8 arg2, s8 arg3) // 0x800553C4
{
    D_800C4168.field_1  = arg0;
    D_800C4168.field_1C = arg1;
    D_800C4168.field_1D = arg2;
    D_800C4168.field_1E = arg3;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800553E0); // 0x800553E0

void func_80055434(VECTOR3* vec) // 0x80055434
{
    *vec = D_800C4168.field_60;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005545C); // 0x8005545C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80055490); // 0x80055490

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800554C4); // 0x800554C4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80055648); // 0x80055648

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800557DC); // 0x800557DC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80055814); // 0x80055814

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80055840); // 0x80055840

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800559A8); // 0x800559A8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80055A50); // 0x80055A50

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80055A90); // 0x80055A90

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80055B74); // 0x80055B74

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80055C3C); // 0x80055C3C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80055D78); // 0x80055D78

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80055E90); // 0x80055E90

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80055ECC); // 0x80055ECC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80055F08); // 0x80055F08

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800560FC); // 0x800560FC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800561A4); // 0x800561A4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80056244); // 0x80056244

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80056348); // 0x80056348

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800563E8); // 0x800563E8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80056464); // 0x80056464

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80056504); // 0x80056504

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80056558); // 0x80056558

void func_8005660C(s_func_8005660C_0* arg0, s_func_8005660C_1* arg1, s32 arg2) // 0x8005660C
{
    s32 coeff;

    coeff = 4;
    switch (arg1->field_0)
    {
        default:
        case 0:
            break;

        case 1:
            coeff = 2;
            break;

        case 2:
            coeff = 1;
            break;
    }

    arg0->field_14 = arg1->field_2 * coeff;
    arg0->field_15 = arg1->field_3;

    arg0->field_E  = ((arg1->field_0 & 0x3) << 7) | ((arg2 & 0x3) << 5) | (arg1->field_1 & (1 << 4)) | (arg1->field_1 & 0xF);
    arg0->field_10 = (arg1->field_6 << 6) | ((arg1->field_4 >> 4) & 0x3F);
}

void func_800566B4(s_func_800566B4* arg0, s_FsImageDesc* image, s8 unused, s32 startIdx, s32 arg4) // 0x800566B4
{
    char                 filename[16];
    s_func_800566B4_sub* var_s0;
    s_FsImageDesc*       imagePtr;
    s32                  i;

    // Loop could be using `&image[i]`/`&arg0->field_4[i]` instead? Wasn't able to make that match though.
    imagePtr = image;
    var_s0   = arg0->field_4;

    for (i = 0; i < arg0->field_3; i++, var_s0++, imagePtr++)
    {
        func_8005B3BC(filename, var_s0);
        Fs_QueueStartReadTim(Fs_FindNextFile(filename, 0, startIdx), FS_BUFFER_9, imagePtr);
        func_8005660C(var_s0, imagePtr, arg4);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80056774); // 0x80056774

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80056888); // 0x80056888

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80056954); // 0x80056954

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80056A88); // 0x80056A88

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80056BF8); // 0x80056BF8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80056C80); // 0x80056C80

// First arg is `s_Bone`.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80056C8C); // 0x80056C8C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80056CB4); // 0x80056CB4

void func_80056D64(s8* prevStr, s8* newStr) // 0x80056D64
{
    *(s32*)&prevStr[4] = 0;
    *(s32*)&prevStr[0] = 0;
    strncpy(prevStr, newStr, 8);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80056D8C); // 0x80056D8C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80057090); // 0x80057090

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800571D0); // 0x800571D0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80057200); // 0x80057200

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80057208); // 0x80057208

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80057210); // 0x80057210

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80057218); // 0x80057218

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80057220); // 0x80057220

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80057228); // 0x80057228

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80057344); // 0x80057344

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800574D4); // 0x800574D4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005759C); // 0x8005759C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80057658); // 0x80057658

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80057A3C); // 0x80057A3C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80057B7C); // 0x80057B7C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005801C); // 0x8005801C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80059D50); // 0x80059D50

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80059E34); // 0x80059E34

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005A21C); // 0x8005A21C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005A42C); // 0x8005A42C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005A478); // 0x8005A478

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005A838); // 0x8005A838

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005A900); // 0x8005A900

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005AA08); // 0x8005AA08

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005AC50); // 0x8005AC50

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005B1A0); // 0x8005B1A0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005B1FC); // 0x8005B1FC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005B370); // 0x8005B370

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005B378); // 0x8005B378

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005B3A4); // 0x8005B3A4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005B3BC); // 0x8005B3BC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005B424); // 0x8005B424

void func_8005B46C(s32* arg0) // 0x8005B46C
{
    *arg0 = 0;
}

void func_8005B474(s32* arg0, u32 arg1, s32 idx) // 0x8005B474
{
    u32* ptr;
    u32  temp_a2;
    u32  var_a1;

    var_a1  = arg1;
    temp_a2 = var_a1 + (idx * 24);
    ptr     = arg0 + 1;

    if (var_a1 >= temp_a2)
    {
        return;
    }

    do
    {
        *ptr   = var_a1;
        var_a1 += 24;
        *arg0  += 1;

        ptr += 1;
    }
    while (var_a1 < temp_a2);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005B4BC); // 0x8005B4BC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005B55C); // 0x8005B55C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005B62C); // 0x8005B62C

void func_8005BF0C(s16 unused, s16 x, s16 y) // 0x8005BF0C
{
    Gfx_DebugStringPosition(x, y);
}

s16 func_8005BF38(s16 arg0) // 0x8005BF38
{
    s16 res;
    s16 temp;

    temp = arg0 & 0xFFF;
    res  = temp;

    if (temp >= 0x801)
    {
        res = temp | 0xF000;
    }

    return res;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005BF58); // 0x8005BF58

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005C1CC); // 0x8005C1CC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005C478); // 0x8005C478

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005C7B0); // 0x8005C7B0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005C7D0); // 0x8005C7D0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005C814); // 0x8005C814

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005C944); // 0x8005C944

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005CB20); // 0x8005CB20

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005CD38); // 0x8005CD38

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005D50C); // 0x8005D50C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005D86C); // 0x8005D86C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005D974); // 0x8005D974

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005D9B8); // 0x8005D9B8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005DC1C); // 0x8005DC1C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005DC3C); // 0x8005DC3C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005DD44); // 0x8005DD44

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005DE0C); // 0x8005DE0C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005E0DC); // 0x8005E0DC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005E414); // 0x8005E414

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005E650); // 0x8005E650

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005E70C); // 0x8005E70C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005E7E0); // 0x8005E7E0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005E89C); // 0x8005E89C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005F55C); // 0x8005F55C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005F680); // 0x8005F680

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8005F6B0); // 0x8005F6B0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80060044); // 0x80060044

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800611C0); // 0x800611C0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800622B8); // 0x800622B8

void func_800625F4(VECTOR3* arg0, s16 arg1, s32 arg2, s32 arg3) // 0x800625F4
{
    s32 idx;
    s8  var;

    var = func_8005F55C(arg2);

    idx = func_8005E7E0(4);
    if (idx == NO_VALUE)
    {
        return;
    }

    g_MapOverlayHeader.field_4C[idx].field_0  = arg0->vx;
    g_MapOverlayHeader.field_4C[idx].field_8  = arg0->vy;
    g_MapOverlayHeader.field_4C[idx].field_4  = arg0->vz;
    g_MapOverlayHeader.field_4C[idx].field_E  = arg1;
    g_MapOverlayHeader.field_4C[idx].field_D  = var;
    g_MapOverlayHeader.field_4C[idx].field_B  = TEST_RNG(2);
    g_MapOverlayHeader.field_4C[idx].field_C  = 6;
    g_MapOverlayHeader.field_4C[idx].field_10 = arg3 * 0x5000;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80062708); // 0x80062708

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006342C); // 0x8006342C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80063A50); // 0x80063A50

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80064334); // 0x80064334

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80064F04); // 0x80064F04

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80064FC0); // 0x80064FC0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800652F4); // 0x800652F4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80065B94); // 0x80065B94

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80066184); // 0x80066184

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80066D90); // 0x80066D90

void func_80066E40() // 0x80066E40
{
    DrawSync(0);
    StoreImage(&D_80028A20, FS_BUFFER_3);
    DrawSync(0);
}

void func_80066E7C() // 0x80066E7C
{
    LoadImage(&D_80028A20, FS_BUFFER_3);
    DrawSync(0);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", GameState_MapScreen_Update); // 0x80066EB0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80067914); // 0x80067914

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80068CC0); // 0x80068CC0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80068E0C); // 0x80068E0C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800692A4); // 0x800692A4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800697EC); // 0x800697EC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80069810); // 0x80069810

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80069820); // 0x80069820

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006982C); // 0x8006982C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80069844); // 0x80069844

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80069860); // 0x80069860

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006993C); // 0x8006993C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80069994); // 0x80069994

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800699E4); // 0x800699E4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800699F8); // 0x800699F8

s32 func_80069B24(s32 arg0, void* arg1, void* arg2) // 0x80069B24
{
    s32 var0; 
    s32 var1;

    var0 = SetSp(0x1F8003D8);
    var1 = func_80069BA8(arg0, arg1, arg2, func_80069FFC(arg0, arg1, arg2));
    SetSp(var0);
    return var1; 
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80069BA8); // 0x80069BA8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80069DF0); // 0x80069DF0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80069FFC); // 0x80069FFC

void func_8006A178(s_func_8006A178* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x8006A178
{
    arg0->field_0  = arg1;
    arg0->field_4  = arg2;
    arg0->field_8  = arg3;
    arg0->field_12 = 0;
    arg0->field_10 = 0;
    arg0->field_14 = 0;
    arg0->field_18 = 0xFFFF0000;
    arg0->field_C  = arg4;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006A1A4); // 0x8006A1A4

s32 func_8006A3B4(s32 arg0, s32 arg1, s32 arg2) // 0x8006A3B4
{
    s32 var0;
    s32 var1;

    var0 = SetSp(0x1F8003D8);
    var1 = func_8006A42C(arg0, arg1, arg2);
    SetSp(var0);

    if (var1 == NO_VALUE)
    {
        var1 = 1;
    }

    return var1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006A42C); // 0x8006A42C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006A4A8); // 0x8006A4A8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006A940); // 0x8006A940

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006AB50); // 0x8006AB50

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006ABC0); // 0x8006ABC0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006AD44); // 0x8006AD44

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006AEAC); // 0x8006AEAC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006B004); // 0x8006B004

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006B1C8); // 0x8006B1C8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006B318); // 0x8006B318

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006B6E8); // 0x8006B6E8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006B7E0); // 0x8006B7E0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006B8F8); // 0x8006B8F8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006B9C8); // 0x8006B9C8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006BB50); // 0x8006BB50

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006BC34); // 0x8006BC34

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006BCC4); // 0x8006BCC4

void func_8006BDDC(s_func_8006BDDC* arg0, s16 arg1, s16 arg2) // 0x8006BDDC
{
    if (arg0->field_0 == 0)
    {
        arg0->field_0 = 1;
        arg0->field_2 = arg1;
        arg0->field_4 = arg2;
        return;
    }

    arg0->field_0++;
    Vw_ClampAngleRange(&arg0->field_2, &arg0->field_4, arg1, arg2);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006BE40); // 0x8006BE40

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006BF88); // 0x8006BF88

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006C0C8); // 0x8006C0C8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006C1B8); // 0x8006C1B8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006C248); // 0x8006C248

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006C3D4); // 0x8006C3D4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006C45C); // 0x8006C45C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006C794); // 0x8006C794

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006C838); // 0x8006C838

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006CA18); // 0x8006CA18

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006CB90); // 0x8006CB90

s32 func_8006CC44(s32 arg0, s32 arg1, s_func_8006CC44* arg2) // 0x8006CC44
{
    if (arg2->field_94 != 12)
    {
        return FP_MULTIPLY(arg2->field_88, arg0 - arg2->field_80, Q12_SHIFT) +
               FP_MULTIPLY(arg2->field_8C, arg1 - arg2->field_84, Q12_SHIFT) +
               arg2->field_7C;
    }

    return 2048;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006CC9C); // 0x8006CC9C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006CF18); // 0x8006CF18

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006D01C); // 0x8006D01C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006D2B4); // 0x8006D2B4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006D600); // 0x8006D600

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006D774); // 0x8006D774

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006D7EC); // 0x8006D7EC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006D90C); // 0x8006D90C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006DA08); // 0x8006DA08

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006DAE4); // 0x8006DAE4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006DB3C); // 0x8006DB3C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006DC18); // 0x8006DC18

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006DCE0); // 0x8006DCE0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006DEB0); // 0x8006DEB0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006E0AC); // 0x8006E0AC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006E150); // 0x8006E150

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006E490); // 0x8006E490

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006E53C); // 0x8006E53C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006E78C); // 0x8006E78C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006EB8C); // 0x8006EB8C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006EE0C); // 0x8006EE0C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006EEB8); // 0x8006EEB8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006F250); // 0x8006F250

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006F338); // 0x8006F338

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006F3C4); // 0x8006F3C4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006F620); // 0x8006F620

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006F8FC); // 0x8006F8FC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006F99C); // 0x8006F99C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006FAFC); // 0x8006FAFC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8006FD90); // 0x8006FD90

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80070030); // 0x80070030

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80070084); // 0x80070084

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800700F8); // 0x800700F8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80070184); // 0x80070184

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80070208); // 0x80070208

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007029C); // 0x8007029C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80070320); // 0x80070320

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80070360); // 0x80070360

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80070400); // 0x80070400

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800705E4); // 0x800705E4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800706E4); // 0x800706E4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80070B84); // 0x80070B84

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80070CF0); // 0x80070CF0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80070DF0); // 0x80070DF0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800711C4); // 0x800711C4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80071224); // 0x80071224

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80071284); // 0x80071284

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800713B4); // 0x800713B4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800713E8); // 0x800713E8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80071620); // 0x80071620

void func_800717D0(s_SubCharacter* chara, void* arg1, GsCOORDINATE2* coord) // 0x800717D0
{
    // Called by `GameState_InGame_Update`, might be player update function.
    // `chara` always `&g_SysWork.player_4C.chara_0`
    // `arg1`  always `0x8010A600` / `FS_BUFFER_0` (holds anim related data?)
    // `coord` always `&g_SysWork.playerBoneCoords_890`

    s_MainCharacterExtra* extra = &g_SysWork.player_4C.extra_128;

    if (g_DeltaTime0 != 0)
    {
        func_8007C800(chara, extra);

        if (D_800AF214 != 0)
        {
            D_800C455C = 0;
            D_800C4558 = 0;
            D_800C45C0 = 0;
            D_800C45BE = 0;
            D_800C45BC = 0;
            D_800C457E = 0;
            D_800C4604 = 0;
            D_800C45F0 = 0;
            D_800C45E8 = 0;
            D_800C4582 = 0;
            D_800C45AE = 0;
            D_800C4586 = 0;
            D_800C4580 = 0;
            D_800C45AC = 0;
            D_800C4584 = 0;
        }

        if (D_800AF215 == 0)
        {
            func_80071CE8(chara, extra, coord);
        }
        else
        {
            g_MapOverlayHeader.func_B8(chara, extra, coord);
        }

        if (D_800AF215 == 0)
        {
            func_8007C0D8(chara, extra, coord);
        }
        else
        {
            g_MapOverlayHeader.func_BC(chara, extra, coord);
        }

        func_80071968(chara, extra, arg1, coord);
        func_8007D090(chara, extra, coord);
    }

    D_800C45B0.vx = 0;
    D_800C45B0.vz = 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80071968); // 0x80071968

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80071CE8); // 0x80071CE8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80073FC0); // 0x80073FC0

void func_80074254(s32 arg0, s32 arg1) // 0x80074254
{
    s32 var0;

    if (func_80075504() != 0)
    {
        return;
    }

    var0 = (D_800C45C9 == 10) ? 1333 : 1314;

    switch (g_SysWork.player_4C.extra_128.field_20)
    {
        case 0:
            func_80071620(55, arg0, 551, 1320);
            break;

        case 14:
            if (func_80071620(23, arg0, 173, var0) != 0)
            {
                func_8008944C();
            }
            break;

        case 17:
            if (func_80071620(39, arg0, 340, var0) != 0)
            {
                func_8008944C();
            }
            break;

        case 18:
            if (func_80071620(43, arg0, 369, var0) != 0)
            {
                func_8008944C();
            }
            break;

        default:
            break;
    }

    func_800771BC(arg0, arg1);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80074350); // 0x80074350

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80075504); // 0x80075504

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800771BC); // 0x800771BC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80077BB8); // 0x80077BB8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80077D00); // 0x80077D00

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007B924); // 0x8007B924

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007C0D8); // 0x8007C0D8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007C800); // 0x8007C800

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007D090); // 0x8007D090

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007D6E0); // 0x8007D6E0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007D6F0); // 0x8007D6F0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007D970); // 0x8007D970

// TODO: Can this work without needing inlined func?
static inline Savegame_PlayerReset(s_ShSavegame* save)
{
    save->playerHealth_240      = FP_TO(100, Q12_SHIFT);
    save->field_A0              = 0;
    save->equippedWeapon_AA     = 0;
    save->field_238             = 0;
    save->gameplayTimer_250     = 0;
    save->runDistance_254       = 0;
    save->walkDistance_258      = 0;
    save->pickedUpItemCount_23C = 0;
    save->clearGameCount_24A    = 0;
    save->add290Hours_25C_1     = 0;
}

void Game_SavegameResetPlayer() // 0x8007E530
{
    s_ShSavegame* save = g_SavegamePtr;
    s32           i;

    g_SavegamePtr->field_AB = 8;

    for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
    {
        save->items_0[i].id_0    = 0xFF;
        save->items_0[i].count_1 = 0;
    }

    Savegame_PlayerReset(g_SavegamePtr);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007E5AC); // 0x8007E5AC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007E860); // 0x8007E860

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007E8C0); // 0x8007E8C0

// Player func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007E9C4); // 0x8007E9C4

void GameFs_PlayerMapAnimLoad(s32 mapIdx) // 0x8007EB64
{
    #define BASE_FILE_IDX FILE_ANIM_HB_M0S00_ANM

    if (g_GameWork.mapAnimIdx_5B1 != mapIdx ||
        mapIdx == (FILE_ANIM_HB_M6S04_ANM - BASE_FILE_IDX) ||
        mapIdx == (FILE_ANIM_HB_M7S01_ANM - BASE_FILE_IDX) ||
        mapIdx == (FILE_ANIM_HB_M7S02_ANM - BASE_FILE_IDX))
    {
        g_GameWork.mapAnimIdx_5B1 = mapIdx;
        Fs_QueueStartRead(BASE_FILE_IDX + mapIdx, FS_BUFFER_4);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007EBBC); // 0x8007EBBC

// Requires jump table.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007F14C); // 0x8007F14C

void func_8007F1CC() // 0x8007F1CC
{
    D_800C455C = 0;
    D_800C4558 = 0;
    D_800C45C0 = 0;
    D_800C45BE = 0;
    D_800C45BC = 0;
    D_800C457E = 0;
    D_800C4604 = 0;
    D_800C45F0 = 0;
    D_800C45E8 = 0;
    D_800C4582 = 0;
    D_800C45AE = 0;
    D_800C4586 = 0;
    D_800C4580 = 0;
    D_800C45AC = 0;
    D_800C4584 = 0;
    D_800AF214 = 0;
}

void func_8007F250(u8* ptr, s8 arg1) // 0x8007F250
{
    *ptr = D_800C4561;
    D_800C4562 = arg1;
}

s32 func_8007F26C() // 0x8007F26C
{
    if (g_SysWork.player_4C.extra_128.field_20 == 25 ||
        g_SysWork.player_4C.extra_128.field_1C == 5 ||
        g_SysWork.player_4C.extra_128.field_1C == 6)
    {
        return 1;
    }

    return 0;
}

s32 func_8007F2AC() // 0x8007F2AC
{
    if (g_SysWork.player_4C.chara_0.health_B0 <= 0 ||
        g_SysWork.isPlayerInCombatMode_4B != 0 ||
        g_SysWork.player_4C.extra_128.field_1C == 5 ||
        g_SysWork.player_4C.extra_128.field_1C == 6 ||
        (g_SysWork.player_4C.extra_128.field_1C - 7) < 44u) // TODO: Probably not how OG condition was.
    {
        return 1;
    }

    return 0;
}

s16 Player_AnimGetSomething() // 0x8007F308
{
    return g_MaybePlayerAnims[g_SysWork.player_4C.chara_0.model_0.anim_4.animIdx_0].field_C;
}

// Large function. Something to do with player control.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007F32C); // 0x8007F32C

// Medium function. Player-related.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007F95C); // 0x8007F95C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007FB34); // 0x8007FB34

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007FB94); // 0x8007FB94

// Similar to above.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007FC48); // 0x8007FC48

s32 func_8007FD2C() // 0x8007FD2C
{
    return g_SysWork.player_4C.chara_0.properties_E4.player.properties_E4[PlayerProperty_Unk8];
}

s32 func_8007FD3C() // 0x8007FD3C
{
    return g_SysWork.player_4C.chara_0.properties_E4.player.field_114;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007FD4C); // 0x8007FD4C

// Large function.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8007FDE0); // 0x8007FDE0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800802CC); // 0x800802CC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8008037C); // 0x8008037C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_800803FC); // 0x800803FC

void func_80080458() // 0x80080458
{
    g_ControllerPtr->btns_new_10 |= ControllerFlag_Select;
}

s32 func_80080478(VECTOR3* pos0, VECTOR3* pos1) // 0x80080478
{
    s32 x0;
    s32 x1;
    s32 y1;
    s32 y0;
    s32 z0;
    s32 z1;
    s32 xDelta;
    s32 zDelta;
    s32 atan2Delta;
    s32 unk;

    x0 = pos0->vx;
    x1 = pos1->vx;
    y0 = pos0->vy;
    y1 = pos1->vy;
    z0 = pos0->vz;
    z1 = pos1->vz;

    xDelta = x1 - x0;
    zDelta = z1 - z0;
    atan2Delta = ratan2(xDelta, zDelta);

    unk = func_8008A058(func_80080540(xDelta, 0, zDelta));
    return (ratan2(unk, y1 - y0) << 0x10) | (atan2Delta & 0xFFFF);
}

s32 func_80080514() // 0x80080514
{
    s32 rand16;

    rand16 = Rng_Rand16();
    return (((rand16 * 2) ^ rand16) >> 3) & 0xFFF;
}

// TODO: Try decomping by hand. -- Sezz
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_80080540); // 0x80080540

s32 PreservedSignSubtract(s32 value, s32 subtractor) // 0x80080594
{
    s32 signBit;
    s32 absDiff;

    signBit = value >> 31;  
    absDiff = ((value ^ signBit) - signBit) - subtractor;  
    return ((absDiff & ~(absDiff >> 31)) ^ signBit) - signBit; 
}

void func_800805BC(VECTOR3* arg0, SVECTOR* arg1, GsCOORDINATE2* arg2, s32 arg3) // 0x800805BC
{
    MATRIX mat;
    VECTOR vec;

    Vw_CoordHierarchyMatrixCompute(arg2, &mat);
    gte_SetRotMatrix(&mat);
    gte_SetTransMatrix(&mat);

    while (arg3 > 0)
    {
        gte_ldv0(arg1);
        gte_rt();
        gte_stlvnl(&vec);

        arg0->vx = vec.vx * 16;
        arg0->vy = vec.vy * 16;
        arg0->vz = vec.vz * 16;

        arg3--;
        arg1++;
        arg0++;
    }
}

u32 func_800806AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x800806AC
{
    u32 res;

    res = arg0 != 0;
    if (res == 0)
    {
        return res;
    }

    res = ~arg0 == 0;
    if (res != 0)
    {
        return res;
    }

    func_800699F8(&D_800C4620, arg1, arg3);

    res = arg2 < D_800C4620.field_0;
    if (res != 0)
    {
        res = ~D_800C4620.field_8 != 0;
        if (res != 0)
        {
            res = (arg0 & (1 << D_800C4620.field_8));
            return res > 0u; 
        }
    }

    return res;
}

void func_8008074C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x8008074C
{
    func_800806AC(arg0, arg1, 1 << 31, arg3);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80053B08", func_8008076C); // 0x8008076C

s32 func_80080884() // 0x80080884
{
    func_8008076C();
    return D_800AFC7C;
}

s32 func_800808AC() // 0x800808AC
{
    func_8008076C();
    return D_800AFC90;
}

s32 Math_MulFixed(s32 val0, s32 val1, s32 shift) // 0x800808D4
{
    u32 lo;

    // Use inline asm to fetch high/low parts of mult.
    // Only method found to allow C to keep same insn/reg order so far.
    __asm__ volatile(
        "mult %0, %1\n" // Multiply val0 and val1
        "mfhi %0\n"     // Move high result back into val0?
        "mflo %2\n"     // Move low result to lo
        : "=r"(val0), "=r"(val1), "=r"(lo)
        : "0"(val0), "1"(val1));

#if 0
    // Equivalent C version of above (non-matching).
    s64 res = (s64)val0 * (s64)val1;
    val0 = (u32)(res >> 32);
    lo = (u32)res;
#endif

    return (val0 << (32 - shift)) | (lo >> shift);
}

s32 Math_GetMagnitudeShift(s32 mag) // 0x800808F8
{
    #define THRESHOLD_0 (1 << 14)
    #define THRESHOLD_1 ((1 << 18) - 1)
    #define THRESHOLD_2 ((1 << 22) - 1)

    s32 qShift;

    if (mag < THRESHOLD_0)
    {
        return 0;
    }

    if (mag > THRESHOLD_1)
    {
        if (mag > THRESHOLD_2)
        {
            return Q12_SHIFT;
        }

        qShift = Q8_SHIFT;
        return qShift;
    }

    qShift = Q4_SHIFT;
    return qShift;
}
