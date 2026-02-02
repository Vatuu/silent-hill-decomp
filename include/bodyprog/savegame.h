#ifndef _SAVEGAME_H
#define _SAVEGAME_H

/** @brief This header contains struct and enums related to specific game
 * save information.
 */
 
#define SAVEGAME_ENTRY_BUFFER_0 ((u8*)0x801E09E0) // Slot 1 savegame entry.
#define SAVEGAME_ENTRY_BUFFER_1 ((u8*)0x801E1430) // Slot 2 savegame entry.

#define SAVEGAME_FOOTER_MAGIC 0xDCDC

#define GetActiveSavegameEntry(slotIdx) \
    ((s_Savegame_Entry*)&SAVEGAME_ENTRY_BUFFER_0[2640 * (slotIdx)])

// ============
// ENUMERATORS
// ============

/** @brief Used by `s_Savegame_Entry`. */
typedef enum _SavegameEntryType
{
    SavegameEntryType_NoMemCard          = 0,
    SavegameEntryType_UnformattedMemCard = 1,
    SavegameEntryType_CorruptedMemCard   = 2,
    SavegameEntryType_LoadMemCard        = 3,
    SavegameEntryType_OutOfBlocks        = 4,
    SavegameEntryType_NoDataInMemCard    = 5,
    SavegameEntryType_Unk6               = 6,
    SavegameEntryType_CorruptedSave      = 7,
    SavegameEntryType_Save               = 8,
    SavegameEntryType_NewSave            = 9,
    SavegameEntryType_NewFile            = 10
} e_SavegameEntryType;

/** @brief Save location IDs. */
typedef enum _SaveLocationId
{
    SaveLocationId_Anywhere    = 0,
    SaveLocationId_Cafe        = 1,
    SaveLocationId_Bus         = 2,
    SaveLocationId_Store       = 3,
    SaveLocationId_Infirmary   = 4,
    SaveLocationId_Doghouse    = 5,
    SaveLocationId_Gordon      = 6,
    SaveLocationId_Church      = 7,
    SaveLocationId_Garage      = 8,
    SaveLocationId_Police      = 9,
    SaveLocationId_Reception   = 10,
    SaveLocationId_Room302     = 11,
    SaveLocationId_Directors   = 12,
    SaveLocationId_JewelryShop = 13,
    SaveLocationId_PoolHall    = 14,
    SaveLocationId_AntiqueShop = 15,
    SaveLocationId_ThemePark   = 16,
    SaveLocationId_Boat        = 17,
    SaveLocationId_Bridge      = 18,
    SaveLocationId_Motel       = 19,
    SaveLocationId_Lighthouse  = 20,
    SaveLocationId_Sewer       = 21,
    SaveLocationId_Nowhere     = 22,
    SaveLocationId_ChildsRoom  = 23,
    SaveLocationId_NextFear    = 24
} e_SaveLocationId;

// ========
// STRUCTS
// ========

typedef struct _Savegame_Metadata
{
    s32 totalSavegameCount_0;
    u32 gameplayTimer_4;
    u16 savegameCount_8;
    u8  locationId_A;
    u8  isNextFearMode_B             : 1;
    u8  add290Hours_B_1              : 2;
    u8  pickedUpSpecialItemCount_B_3 : 5; /** See `pickedUpSpecialItemCount_25C_3` comment in `s_Savegame`. */
} s_Savegame_Metadata;
STATIC_ASSERT_SIZEOF(s_Savegame_Metadata, 12);

typedef struct _Savegame_Entry
{
    s16                  totalSavegameCount_0; /** Counter that stores all the times the player have save throughout the entire game.
	                                            * In order to get the set this value the code will go through all saves in the memory
	                                            * card and check which have this variable with the biggest value.
	                                            *
	                                            * @bug: For some unknown reason, this counter it is used by the code uses to
	                                            * determine if the player have selected the "New Save" element which will make
	                                            * overwrites to not show the "Yes/No" message to show up.
	                                            */
    s16                  savegameCount_2;
    s8                   type_4;               /** `e_SavegameEntryType` */
    s8                   deviceId_5;
    s8                   fileIdx_6;
    s8                   elementIdx_7;         // Index in file?
    s8                   locationId_8;
    s8                   unk_9[3]; // Probably padding.
    s_Savegame_Metadata* saveMetadata_C;
} s_Savegame_Entry;
STATIC_ASSERT_SIZEOF(s_Savegame_Entry, 16);

/** @brief Appended to `ShSavegame` and `ShSaveUserConfig` during game save. Contains 8-bit XOR checksum + magic.
 * Checksum generated via `MemCard_ChecksumGenerate`.
 */
typedef struct _SavegameFooter
{
    u8  checksum_0[2];
    u16 magic_2;
} s_Savegame_Footer;
STATIC_ASSERT_SIZEOF(s_Savegame_Footer, 4);

/** @brief Contains `s_Savegame` data with the footer appended to the end containing the checksum + magic. */
typedef struct _SavegameContainer
{
    s_Savegame        savegame_0;
    s_Savegame_Footer footer_27C;
} s_Savegame_Container;
STATIC_ASSERT_SIZEOF(s_Savegame_Container, 640);

/** @brief Contains `s_SaveUserConfig` data padded to 128 bytes with a footer at the end containing checksum + magic. */
typedef struct _SaveUserConfigContainer
{
    s_SaveUserConfig  config_0;
    u8                pad_38[68];
    s_Savegame_Footer footer_7C;
} s_Savegame_UserConfigs;

// ========
// GLOBALS
// ========

/** @brief Basic information required to draw information of elements in save slots.
 * Address access is based on the slot: slot 1 = 0x801E09E0, slot 2 = 0x801E1440.
 * 
 * @note Macros for its references are in `saveload.h`:
 * `SAVEGAME_ENTRY_BUFFER_0`
 * `SAVEGAME_ENTRY_BUFFER_1`
 *
 * @note Should go in MEMCARD
 */

extern s_Savegame_Entry* g_MemCard_ActiveSavegameEntry; // 0x800BCD2C

/** @brief Amount of elements in each memory card.
 @note Should go in MEMCARD
 */
extern u8 g_Savegame_ElementCount0[2];

extern s32 D_800BCD18[2];

extern s32 D_800BCD20[2];

/** @brief Stores all memory cards/devices status.
 @note Should go in MEMCARD
 */
extern u32 g_MemCard_AllMemCardsStatus;

/** @brief Some determinator for the state of the save screen.
 * 2 - Saving, 3 - Loading.
 */
extern s8 g_SaveScreen_SaveScreenState;

extern s8 D_800BCD39; // Boolean.

/** @brief Counts all elements of all inserted memory cards. */
extern s16 g_MemCard_TotalElementsCount;

extern s8 g_SelectedDeviceId;

/** @brief Amount of elements in each memory card.
 @note Should go in MEMCARD
 */
extern u8 g_Savegame_ElementCount1[2];

/** @brief Index of selected element in each memory card.
 @note Should go in SAVELOAD
 */
extern u8 g_Savegame_SelectedElementIdx;

extern s8 g_SelectedFileIdx;

#endif
