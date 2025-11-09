#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"

s_AnimInfo HARRY_M2S04_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10.0f) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10.0f) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10.0f) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15.0f) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10.0f) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10.0f) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10.0f) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15.0f) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10.0f) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15.0f) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10.0f) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10.0f) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10.0f) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10.0f) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10.0f) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(20.0f) }, 485, 502 },
    {}
};

s_UnkStruct3_Mo g_MapHeaderTable_38[] = {
    { 19788, 0, 676, 677 },
    { 20302, 200, 678, 688 },
    { 20816, 202, 689, 724 },
    { 21330, 210, 725, 743 },
    { 21844, 211, 744, 762 },
    { 22358, 212, 763, 781 },
    { 22872, 213, 782, 800 },
    { 23386, 500, 485, 502 },
    {}
};

u8 LOADABLE_INVENTORY_ITEMS[] = {
    InventoryItemId_HealthDrink,
    InventoryItemId_FirstAidKit,
    InventoryItemId_Ampoule,
    InventoryItemId_KitchenKnife,
    InventoryItemId_SteelPipe,
    InventoryItemId_Hammer,
    InventoryItemId_Chainsaw,
    InventoryItemId_Axe,
    InventoryItemId_Handgun,
    InventoryItemId_HuntingRifle,
    InventoryItemId_Shotgun,
    InventoryItemId_HyperBlaster,
    InventoryItemId_HandgunBullets,
    InventoryItemId_RifleShells,
    InventoryItemId_ShotgunShells,
    InventoryItemId_Flashlight,
    InventoryItemId_PocketRadio,
    InventoryItemId_HouseKey,
    InventoryItemId_KeyOfLion,
    InventoryItemId_KeyOfWoodman,
    InventoryItemId_KeyOfScarecrow,
    InventoryItemId_KGordonKey,
    InventoryItemId_DrawbridgeKey,
    InventoryItemId_NoteToSchool,
    InventoryItemId_NoteDoghouse,
    InventoryItemId_Flauros,
    InventoryItemId_AntiqueShopKey,
    InventoryItemId_PlasticBottle,
    InventoryItemId_UnknownLiquid,
    InventoryItemId_VideoTape,
    InventoryItemId_RockDrill,
    InventoryItemId_GasolineTank,
    InventoryItemId_ChannelingStone,
    InventoryItemId_Katana,
    InventoryItemId_Unequipped
};

u8 sharedData_800DD584_0_s00 = 0;

s32 sharedData_800DD598_0_s00 = 0;

u8 sharedData_800DD59C_0_s00 = 255;
