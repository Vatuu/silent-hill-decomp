#ifndef _GAME_H
#define _GAME_H

#include "gpu.h"
#include "types.h"

struct _SubCharacter;

#define TICKS_PER_SECOND 60 /** Game has a variable timestep with 60 ticks max. */

#define SCREEN_WIDTH                   320
#define SCREEN_HEIGHT                  240
#define FRAMEBUFFER_HEIGHT_PROGRESSIVE 224
#define FRAMEBUFFER_HEIGHT_INTERLACED  (FRAMEBUFFER_HEIGHT_PROGRESSIVE * 2)

#define NPC_COUNT_MAX            6
#define INVENTORY_ITEM_COUNT_MAX 40
#define INPUT_ACTION_COUNT       14
#define SAVEGAME_FOOTER_MAGIC    0xDCDC
#define MEMORY_CARD_SLOT_COUNT   2
#define CONTROLLER_COUNT_MAX     2

#define EVENT_FLAG5_FIRST_TIME_SAVE_GAME (1 << 26)

#define MAP_MSG_CODE_MARKER         '~' /** Message code start. */
#define MAP_MSG_CODE_COLOR          'C' /** Set color. */
#define MAP_MSG_CODE_DISPLAY_ALL    'D' /** Display message instantly without roll. */
#define MAP_MSG_CODE_END            'E' /** End message. */
#define MAP_MSG_CODE_HIGH_RES       'H' /** High-resolution glyph drawing. */
#define MAP_MSG_CODE_JUMP           'J' /** Jump timer. */
#define MAP_MSG_CODE_LINE_POSITION  'L' /** Set next line position. */
#define MAP_MSG_CODE_MIDDLE         'M' /** Align center. */
#define MAP_MSG_CODE_NEWLINE        'N' /** Newline. */
#define MAP_MSG_CODE_SELECT         'S' /** Display dialog prompt with selectable entries. */
#define MAP_MSG_CODE_TAB            'T' /** Inset line. */

#define MAP_MESSAGE_DISPLAY_ALL_LENGTH 400  /** Hack. Long string length is used to display a whole message instantly. */
#define GLYPH_TABLE_ASCII_OFFSET       '\'' /** Subtracted from ASCII bytes to get index to some string-related table. */

/** @brief Converts a floating-point X screen position in percent to a fixed-point X screen coodinate. */
#define SCREEN_POSITION_X(percent) \
    (s32)((SCREEN_WIDTH) * ((percent) / 100.0f))

/** @brief Converts a floating-point Y screen position in percent to a fixed-point Y screen coodinate. */
#define SCREEN_POSITION_Y(percent) \
    (s32)((SCREEN_HEIGHT) * ((percent) / 100.0f))

// TODO: Not correct. Should use unions instead.
/** @brief Accessors for low and high parts of each character property, returns a pointer which can be read or written to. */
#define GET_PROPERTY_LOW(prop) \
    ((u16*)&(prop))

#define GET_PROPERTY_HIGH(prop) \
    ((u16*)&(prop) + 1)

/** @brief Checks if a specified map has been collected. */
#define HAS_MAP(mapIdx) \
    ((((u32*)&g_SavegamePtr->hasMapsFlags_164)[(mapIdx) / 32] >> ((mapIdx) % 32)) & (1 << 0))

/** Each map has its own messages, with the first 15 hardcoded to be the same. */
typedef enum _MapMsgIdx
{
    MapMsgIdx_Yes               = 0,
    MapMsgIdx_No                = 1,
    MapMsgIdx_SaveGame          = 2, // "Someday, someone may experience..."
    MapMsgIdx_NoMap             = 3,
    MapMsgIdx_TooDarkForMap     = 4,
    MapMsgIdx_FirstAidSelect    = 5,
    MapMsgIdx_HealthDrinkSelect = 6,
    MapMsgIdx_AmpouleSelect     = 7,
    MapMsgIdx_HandgunAmmoSelect = 8,
    MapMsgIdx_RifleAmmoSelect   = 9,
    MapMsgIdx_ShotgunAmmoSelect = 10,
    MapMsgIdx_DoorJammer        = 11,
    MapMsgIdx_DoorLocked        = 12,
    MapMsgIdx_DoorUnlocked      = 13,
    MapMsgIdx_NowMaking         = 14  // Unused?
} e_MapMsgIdx;

typedef enum _MapMsgCode
{
    MapMsgCode_None        = 0,
    MapMsgCode_Select2     = 2,
    MapMsgCode_Select3     = 3,
    MapMsgCode_Select4     = 4,
    MapMsgCode_DisplayAll  = 20,
    MapMsgCode_SetByT      = 88,
    MapMsgCode_AlignCenter = 99
} e_MapMsgCode;

/** @brief Map message states.
 *
 * Return states used by `MapMsg_Draw`.
 */
typedef enum _MapMsgState
{
    MapMsgState_Finish       = NO_VALUE, /** Initial setup complete, cutscene timer complete, or input to continue from user received. */
    MapMsgState_Idle         = 0,        /** Continue displaying message. */
    MapMsgState_SelectEntry0 = 1,        /** First entry selected in selection dialog. */
    MapMsgState_SelectEntry1 = 2,        /** Second entry selected in selection dialog. */
    MapMsgState_SelectEntry2 = 3,        /** Third entry selected in selection dialog. */
} e_MapMsgState;

typedef enum _MapMsgAudioLoadBlock
{
    MapMsgAudioLoadBlock_None = 0, // TODO: Some code checks only for bit 0, so it should mean something.
    MapMsgAudioLoadBlock_Unk1 = 1,
    MapMsgAudioLoadBlock_J2   = 3  // `J2` map messages set this, causing voice audio to not load.
                                   // `J2` cutscenes use single audio file for all lines (e.g. video tape cutscene).
} e_MapMsgAudioLoadBlock;

typedef enum _MapOverlayId
{
    MapOverlayId_MAP0_S00 = 0,
    MapOverlayId_MAP0_S01 = 1,
    MapOverlayId_MAP0_S02 = 2,
    MapOverlayId_MAP1_S00 = 3,
    MapOverlayId_MAP1_S01 = 4,
    MapOverlayId_MAP1_S02 = 5,
    MapOverlayId_MAP1_S03 = 6,
    MapOverlayId_MAP1_S04 = 7,
    MapOverlayId_MAP1_S05 = 8,
    MapOverlayId_MAP1_S06 = 9,
    MapOverlayId_MAP2_S00 = 10,
    MapOverlayId_MAP2_S01 = 11,
    MapOverlayId_MAP2_S02 = 12,
    MapOverlayId_MAP2_S03 = 13,
    MapOverlayId_MAP2_S04 = 14,
    MapOverlayId_MAP3_S00 = 15,
    MapOverlayId_MAP3_S01 = 16,
    MapOverlayId_MAP3_S02 = 17,
    MapOverlayId_MAP3_S03 = 18,
    MapOverlayId_MAP3_S04 = 19,
    MapOverlayId_MAP3_S05 = 20,
    MapOverlayId_MAP3_S06 = 21,
    MapOverlayId_MAP4_S00 = 22,
    MapOverlayId_MAP4_S01 = 23,
    MapOverlayId_MAP4_S02 = 24,
    MapOverlayId_MAP4_S03 = 25,
    MapOverlayId_MAP4_S04 = 26,
    MapOverlayId_MAP4_S05 = 27,
    MapOverlayId_MAP4_S06 = 28,
    MapOverlayId_MAP5_S00 = 29,
    MapOverlayId_MAP5_S01 = 30,
    MapOverlayId_MAP5_S02 = 31,
    MapOverlayId_MAP5_S03 = 32,
    MapOverlayId_MAP6_S00 = 33,
    MapOverlayId_MAP6_S01 = 34,
    MapOverlayId_MAP6_S02 = 35,
    MapOverlayId_MAP6_S03 = 36,
    MapOverlayId_MAP6_S04 = 37,
    MapOverlayId_MAP6_S05 = 38,
    MapOverlayId_MAP7_S00 = 39,
    MapOverlayId_MAP7_S01 = 40,
    MapOverlayId_MAP7_S02 = 41,
    MapOverlayId_MAP7_S03 = 42
} e_MapOverlayId;

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

typedef enum _Current2dMapIdx
{
    Current2dMap_OtherPlaces    = 0,
    Current2dMap_OldTown        = 1,
    Current2dMap_FogCentralTown = 2,
    Current2dMap_AltCentralTown = 3,
    Current2dMap_ResortTown     = 4,
    Current2dMap_FogSchoolBF    = 5,
    Current2dMap_FogSchool1F    = 6,
    Current2dMap_FogSchool2F    = 7,
    Current2dMap_FogSchoolRF    = 8,
    Current2dMap_AltSchoolBF    = 9,
    Current2dMap_AltSchool1F    = 10,
    Current2dMap_AltSchool2F    = 11,
    Current2dMap_AltSchoolRF    = 12,
    Current2dMap_FogSewer1F     = 13,
    Current2dMap_FogSewer2F     = 14,
    Current2dMap_AltSewer       = 15,
    Current2dMap_FogHospitalBF  = 16,
    Current2dMap_FogHospital1F  = 17,
    Current2dMap_FogHospital2F  = 18,
    Current2dMap_FogHospital3F  = 19,
    Current2dMap_AltHospitalBF  = 20,
    Current2dMap_AltHospital1F  = 21,
    Current2dMap_AltHospital2F  = 22,
    Current2dMap_AltHospital3F  = 23
} e_Current2dMapIdx;

typedef enum _SysWorkProcessFlags
{
    SysWorkProcessFlag_None              = 0,
    SysWorkProcessFlag_RoomTransition    = 1 << 0,
    SysWorkProcessFlag_OverlayTransition = 1 << 1,
    SysWorkProcessFlag_NewGame           = 1 << 2,
    SysWorkProcessFlag_LoadSave          = 1 << 3,
    SysWorkProcessFlag_Continue          = 1 << 4,
    SysWorkProcessFlag_BootDemo          = 1 << 5
} e_SysWorkProcessFlags;

typedef enum _ControllerFlags
{
    ControllerFlag_Select       = 1 << 0,
    ControllerFlag_L3           = 1 << 1,
    ControllerFlag_R3           = 1 << 2,
    ControllerFlag_Start        = 1 << 3,
    ControllerFlag_DpadUp       = 1 << 4,
    ControllerFlag_DpadRight    = 1 << 5,
    ControllerFlag_DpadDown     = 1 << 6,
    ControllerFlag_DpadLeft     = 1 << 7,
    ControllerFlag_L2           = 1 << 8,
    ControllerFlag_R2           = 1 << 9,
    ControllerFlag_L1           = 1 << 10,
    ControllerFlag_R1           = 1 << 11,
    ControllerFlag_Triangle     = 1 << 12,
    ControllerFlag_Circle       = 1 << 13,
    ControllerFlag_Cross        = 1 << 14,
    ControllerFlag_Square       = 1 << 15,
    ControllerFlag_LStickUp2    = 1 << 16,
    ControllerFlag_LStickRight2 = 1 << 17,
    ControllerFlag_LStickDown2  = 1 << 18,
    ControllerFlag_LStickLeft2  = 1 << 19,
    ControllerFlag_RStickUp     = 1 << 20,
    ControllerFlag_RStickRight  = 1 << 21,
    ControllerFlag_RStickDown   = 1 << 22,
    ControllerFlag_RStickLeft   = 1 << 23,
    ControllerFlag_LStickUp     = 1 << 24,
    ControllerFlag_LStickRight  = 1 << 25,
    ControllerFlag_LStickDown   = 1 << 26,
    ControllerFlag_LStickLeft   = 1 << 27
} e_ControllerFlags;

/** @brief Flags with an unknown purpose used frequently for `s_SubCharacter::flags_3E`. */
typedef enum _CharaFlags
{
    CharaFlag_None = 0,
    CharaFlag_Unk2 = 1 << 1,
    CharaFlag_Unk3 = 1 << 2,
    CharaFlag_Unk4 = 1 << 3,
    CharaFlag_Unk5 = 1 << 4,
    CharaFlag_Unk6 = 1 << 5,
    CharaFlag_Unk7 = 1 << 6,
    CharaFlag_Unk8 = 1 << 7,
    CharaFlag_Unk9 = 1 << 8
} s_CharaFlags;

/** @brief Color IDs used by strings displayed on the screen. */
typedef enum _ColorId
{
    ColorId_Gold           = 0,
    ColorId_DarkGrey       = 1,
    ColorId_Green          = 2,
    ColorId_Nuclear        = 3,
    ColorId_Red            = 4,
    ColorId_GreenDuplicate = 5, // Gives same color as `ColorId_Green`. Unused?
    ColorId_LightGrey      = 6,
    ColorId_White          = 7
} e_ColorId;

typedef enum _AnimFlags
{
    AnimFlag_None    = 0,
    AnimFlag_Unk1    = 1 << 0, // Movement unlocked?
    AnimFlag_Visible = 1 << 1
} e_AnimFlags;

/** @brief State IDs used by the main game loop. The values are used as indices into the 0x800A977C function array. */
typedef enum _GameState
{
    GameState_Unk0                = 0,
    GameState_KonamiLogo          = 1,
    GameState_KcetLogo            = 2,
    GameState_StartMovieIntro     = 3,
    GameState_DeathLoadScreen     = 4,
    GameState_MovieIntroAlternate = 5,
    GameState_MovieIntro          = 6,
    GameState_MainMenu            = 7,
    GameState_SaveScreen          = 8,
    GameState_MovieOpening        = 9,
    GameState_MainLoadScreen      = 10,
    GameState_InGame              = 11,
    GameState_MapEvent            = 12,
    GameState_ExitMovie           = 13,
    GameState_InventoryScreen     = 14,
    GameState_MapScreen           = 15,
    GameState_Unk10               = 16,
    GameState_DebugMoviePlayer    = 17,
    GameState_OptionScreen        = 18,
    GameState_LoadStatusScreen    = 19,
    GameState_LoadMapScreen       = 20,
    GameState_Unk15               = 21,
    GameState_Unk16               = 22 /** Removed debug menu? Doesn't exist in function array, but `DebugMoviePlayer` state tries to switch to it. */
} e_GameState;

/** @brief State IDs used by `GameState_InGame`.
 *
 * The values are used as indices into the 0x800A9A2C function array.
 */
typedef enum _SysState
{
    SysState_Gameplay       = 0,
    SysState_OptionsMenu    = 1,
    SysState_StatusMenu     = 2,
    SysState_MapScreen      = 3,
    SysState_Fmv            = 4,
    SysState_LoadArea0      = 5,
    SysState_LoadArea1      = 6,
    SysState_ReadMessage    = 7,
    SysState_SaveMenu0      = 8,
    SysState_SaveMenu1      = 9,
    SysState_EventCallFunc  = 10,
    SysState_EventSetFlag   = 11,
    SysState_EventPlaySound = 12,
    SysState_GameOver       = 13,
    SysState_GamePaused     = 14,
    SysState_Unk15          = 15
} e_SysState;

/** @brief Inventory command IDs. */
typedef enum _InventoryCmdId
{
    InventoryCmdId_UseHealth     = 0,  /** Text is "Use", but this one is used exclusively on health items. */
    InventoryCmdId_Use           = 1,
    InventoryCmdId_Equip         = 2,
    InventoryCmdId_Unequip       = 3,
    InventoryCmdId_EquipReload   = 4,
    InventoryCmdId_UnequipReload = 5,
    InventoryCmdId_OnOff         = 6,
    InventoryCmdId_Reload        = 7,
    InventoryCmdId_Look          = 8,
    InventoryCmdId_UseLook       = 9,
    InventoryCmdId_Unk10         = 10,
    InventoryCmdId_Unk11         = 11 // Flashlight in daytime?
} e_InventoryCmdId;

/** @brief Inventory item IDs. */
typedef enum _InventoryItemId
{
    InventoryItemId_Empty                = NO_VALUE,
    InventoryItemId_Unequipped           = 0,

    InventoryItemId_HealthDrink          = 32,
    InventoryItemId_FirstAidKit          = 33,
    InventoryItemId_Ampoule              = 34,

    InventoryItemId_LobbyKey             = 64,
    InventoryItemId_HouseKey             = 65,
    InventoryItemId_KeyOfLion            = 66,
    InventoryItemId_KeyOfWoodman         = 67,
    InventoryItemId_KeyOfScarecrow       = 68,
    InventoryItemId_LibraryReserveKey    = 69,
    InventoryItemId_ClassroomKey         = 70,
    InventoryItemId_KGordonKey           = 71,
    InventoryItemId_DrawbridgeKey        = 72,
    InventoryItemId_BasementKey          = 73,
    InventoryItemId_BasementStoreroomKey = 74,
    InventoryItemId_ExaminationRoomKey   = 75,
    InventoryItemId_AntiqueShopKey       = 76,
    InventoryItemId_SewerKey             = 77,
    InventoryItemId_KeyOfOphiel          = 78,
    InventoryItemId_KeyOfHagith          = 79,
    InventoryItemId_KeyOfPhaleg          = 80,
    InventoryItemId_KeyOfBethor          = 81,
    InventoryItemId_KeyOfAratron         = 82,
    InventoryItemId_NoteToSchool         = 83,
    InventoryItemId_NoteDoghouse         = 84,
    InventoryItemId_PictureCard          = 85,

    InventoryItemId_SewerExitKey         = 87,
    InventoryItemId_ChannelingStone      = 88,

    InventoryItemId_Chemical             = 96,
    InventoryItemId_GoldMedallion        = 97,
    InventoryItemId_SilverMedallion      = 98,
    InventoryItemId_RubberBall           = 99,
    InventoryItemId_Flauros              = 100,
    InventoryItemId_PlasticBottle        = 101,
    InventoryItemId_UnknownLiquid        = 102,
    InventoryItemId_PlateOfTurtle        = 103,
    InventoryItemId_PlateOfHatter        = 104,
    InventoryItemId_PlateOfCat           = 105,
    InventoryItemId_PlateOfQueen         = 106,
    InventoryItemId_BloodPack            = 107,
    InventoryItemId_DisinfectingAlcohol  = 108,
    InventoryItemId_Lighter              = 109,
    InventoryItemId_VideoTape            = 110,

    InventoryItemId_KaufmannKey          = 112,
    InventoryItemId_Receipt              = 113,
    InventoryItemId_SafeKey              = 114,
    InventoryItemId_Magnet               = 115,
    InventoryItemId_MotorcycleKey        = 116,
    InventoryItemId_BirdCageKey          = 117,
    InventoryItemId_Pliers               = 118,
    InventoryItemId_Screwdriver          = 119,
    InventoryItemId_Camera               = 120,
    InventoryItemId_RingOfContract       = 121,
    InventoryItemId_StoneOfTime          = 122,
    InventoryItemId_AmuletOfSolomon      = 123,
    InventoryItemId_CrestOfMercury       = 124,
    InventoryItemId_Ankh                 = 125,
    InventoryItemId_DaggerOfMelchior     = 126,
    InventoryItemId_DiskOfOuroboros      = 127,

    InventoryItemId_KitchenKnife         = 128,
    InventoryItemId_SteelPipe            = 129,
    InventoryItemId_RockDrill            = 130,

    InventoryItemId_Hammer               = 132,
    InventoryItemId_Chainsaw             = 133,
    InventoryItemId_Katana               = 134,
    InventoryItemId_Axe                  = 135,

    InventoryItemId_Handgun              = 160,
    InventoryItemId_HuntingRifle         = 161,
    InventoryItemId_Shotgun              = 162,
    InventoryItemId_HyperBlaster         = 163,

    InventoryItemId_HandgunBullets       = 192,
    InventoryItemId_RifleShells          = 193,
    InventoryItemId_ShotgunShells        = 194,

    InventoryItemId_Flashlight           = 224,
    InventoryItemId_PocketRadio          = 225,
    InventoryItemId_GasolineTank         = 226
} e_InventoryItemId;

typedef enum _CommonPickupItemType
{
    CommonPickupItemId_FirstAidKit    = 0,
    CommonPickupItemId_HealthDrink    = 1,
    CommonPickupItemId_Ampoule        = 2,
    CommonPickupItemId_HandgunBullets = 3,
    CommonPickupItemId_RifleShells    = 4,
    CommonPickupItemId_ShotgunShells  = 5
} s_CommonPickupItemType;

/** @brief Equipped weapon IDs. Derivative of `e_InventoryItemId`.
 *
 * Maybe weapon state instead?
 * Name is likely inacurrate as some of values from the few uses of this enum
 * change in certain cases. Examples:
 *
 * The kitchen knife ID changes to 10 if the user holds the Action
 * button and 20 if they tap rapidly.
 *
 * The axe ID changes to 17 or 27 depending on whether the user presses or holds Action.
 *
 * See `func_80071968`.
 */
typedef enum _EquippedWeaponId
{
    EquippedWeaponId_KitchenKnife   = 0,
    EquippedWeaponId_SteelPipe      = 1,
    EquippedWeaponId_RockDrill      = 2,
    EquippedWeaponId_Unk3           = 3,
    EquippedWeaponId_Hammer         = 4,
    EquippedWeaponId_Chainsaw       = 5,
    EquippedWeaponId_Katana         = 6,
    EquippedWeaponId_Axe            = 7,
    EquippedWeaponId_Unk8           = 8,
    EquippedWeaponId_Unk9           = 9,

    EquippedWeaponId_Handgun        = 32,
    EquippedWeaponId_HuntingRifle   = 33,
    EquippedWeaponId_Shotgun        = 34,
    EquippedWeaponId_HyperBlaster   = 35,

    EquippedWeaponId_HandgunBullets = 64,
    EquippedWeaponId_RifleShells    = 65,
    EquippedWeaponId_ShotgunShells  = 66,

    EquippedWeaponId_Flashlight     = 96,
    EquippedWeaponId_PocketRadio    = 97,
    EquippedWeaponId_GasolineTank   = 98
} e_EquippedWeaponId;

/** @brief Player model bone indices. */
typedef enum _PlayerBone
{
    PlayerBone_Root          = 0,
    PlayerBone_Torso         = 1,
    PlayerBone_Head          = 2,
    PlayerBone_LeftShoulder  = 3,
    PlayerBone_LeftUpperArm  = 4,
    PlayerBone_LeftForearm   = 5,
    PlayerBone_LeftHand      = 6,
    PlayerBone_RightShoulder = 7,
    PlayerBone_RightUpperArm = 8,
    PlayerBone_RightForearm  = 9,
    PlayerBone_RightHand     = 10,
    PlayerBone_Hips          = 11,
    PlayerBone_LeftThigh     = 12,
    PlayerBone_LeftShin      = 13,
    PlayerBone_LeftFoot      = 14,
    PlayerBone_RightThigh    = 15,
    PlayerBone_RightShin     = 16,
    PlayerBone_RightFoot     = 17,

    PlayerBone_Count         = 18
} s_PlayerBone;

typedef enum _PlayerFlags
{
    PlayerFlag_None               = 0,
    PlayerFlag_Unk0               = 1 << 0,
    PlayerFlag_Shoot              = 1 << 1,
    PlayerFlag_Unk2               = 1 << 2,
    PlayerFlag_WallStopAnimKind = 1 << 3, // Depending on the frame the player suddenly stopped running it could reproduce one of two animations, mainly differing in which leg Harry extends.
    PlayerFlag_Unk4               = 1 << 4,
    PlayerFlag_Unk5               = 1 << 5, // PlayerFlag_MoveBackward?
    PlayerFlag_Unk6               = 1 << 6,
    PlayerFlag_Unk7               = 1 << 7, // Not used anywhere yet.
    PlayerFlag_Unk8               = 1 << 8,
    PlayerFlag_Unk9               = 1 << 9,
    PlayerFlag_Unk10              = 1 << 10, // PlayerFlag_MeleeAttack?
    PlayerFlag_Unk11              = 1 << 11, // PlayerFlag_GunAttack?
    PlayerFlag_Unk12              = 1 << 12,
    PlayerFlag_Unk13              = 1 << 13,
    PlayerFlag_DamageReceived     = 1 << 14,
    PlayerFlag_Moving             = 1 << 15
} e_PlayerFlags;

/** @brief Names for each character index used in the game, `g_Chara_FileInfo` array associates each character ID with anim/model/texture files. */
typedef enum _CharacterId
{
    Chara_None             = 0,
    Chara_Hero             = 1,
    Chara_AirScreamer      = 2,
    Chara_NightFlutter     = 3,
    Chara_Groaner          = 4,
    Chara_Wormhead         = 5,
    Chara_LarvalStalker    = 6,
    Chara_Stalker          = 7,
    Chara_GreyChild        = 8,
    Chara_Mumbler          = 9,
    Chara_HangedScratcher  = 10,
    Chara_Creaper          = 11,
    Chara_Romper           = 12,
    Chara_UnusedChicken    = 13,
    Chara_Splithead        = 14,
    Chara_Floatstinger     = 15,
    Chara_PuppetNurse      = 16,
    Chara_DummyNurse       = 17, /** Uses dummy anim file without model/texture, but uses same update funcptr as `Chara_PuppetNurse`. */
    Chara_PuppetDoctor     = 18,
    Chara_DummyDoctor      = 19, /** Uses dummy anim file without model/texture, but uses same update funcptr as `Chara_PuppetDoctor`. */
    Chara_Twinfeeler       = 20,
    Chara_Bloodsucker      = 21,
    Chara_Incubus          = 22,
    Chara_Unknown23        = 23,
    Chara_MonsterCybil     = 24,
    Chara_LockerDeadBody   = 25,
    Chara_Cybil            = 26,
    Chara_EndingCybil      = 27,
    Chara_Cheryl           = 28,
    Chara_Cat              = 29,
    Chara_Dahlia           = 30,
    Chara_EndingDahlia     = 31,
    Chara_Lisa             = 32,
    Chara_BloodyLisa       = 33,
    Chara_Alessa           = 34,
    Chara_GhostChildAlessa = 35,
    Chara_Incubator        = 36,
    Chara_BloodyIncubator  = 37,
    Chara_Kaufmann         = 38,
    Chara_EndingKaufmann   = 39,
    Chara_Flauros          = 40,
    Chara_LittleIncubus    = 41,
    Chara_GhostDoctor      = 42,
    Chara_Parasite         = 43,
    Chara_Padlock          = 44,

    Chara_Count
} e_CharacterId;

/** Based on LIBOVR.PDF `Buffer Data Format` section. */
typedef enum _PadTerminalType
{
    PadTerminalType_Mouse               = 1,
    PadTerminalType_16ButtonAnalog      = 2,
    PadTerminalType_GunControllerKonami = 3,
    PadTerminalType_16Button            = 4,
    PadTerminalType_AnalogJoystick      = 5,
    PadTerminalType_GunControllerNamco  = 6,
    PadTerminalType_AnalogController    = 7,
    PadTerminalType_MultitapAdapter     = 8
} e_PadTerminalType;

typedef enum _GameDifficulty
{
    GameDifficulty_Easy   = -1,
    GameDifficulty_Normal = 0,
    GameDifficulty_Hard   = 1
} e_GameDifficulty;

typedef union
{
    u32 rawData_0;
    struct
    {
        s8 rightX;
        s8 rightY;
        s8 leftX;
        s8 leftY;
    } sticks_0;
} s_AnalogSticks;

typedef struct _AnalogController
{
    u8  status;
    u8  received_bytes : 4; /** Number of bytes received / 2. */
    u8  terminal_type  : 4; /** `e_PadTerminalType` */
    u16 digitalButtons;
    u8  rightX;
    u8  rightY;
    u8  leftX;
    u8  leftY;
} s_AnalogController;
STATIC_ASSERT_SIZEOF(s_AnalogController, 8);

typedef struct _ControllerData
{
    s_AnalogController analogController_0;
    s32                pulseTicks_8;
    s32                btnsHeld_C;       /** `e_ControllerFlags` */
    s32                btnsClicked_10;   /** `e_ControllerFlags` */
    s32                btnsReleased_14;  /** `e_ControllerFlags` */
    s32                btnsPulsed_18;    /** `e_ControllerFlags` */
    s32                btnsPulsedGui_1C; /** `e_ControllerFlags` */
    s_AnalogSticks     sticks_20;
    s32                field_24;
    s32                field_28;
} s_ControllerData;
STATIC_ASSERT_SIZEOF(s_ControllerData, 44);

/** Key bindings for input actions. */
// TODO: Instead of `u16`s, it should use 1-bit packed 16-bit `u32`, similar to `ControllerFlags` but not an enum because it can have multiple values.
// Only the first 16 values are counted (analog directions are not included). Also, D-Pad is not registered.
typedef struct _ControllerConfig
{
    u16 enter_0;
    u16 cancel_2;
    u16 skip_4;
    u16 action_6;
    u16 aim_8;
    u16 light_A;
    u16 run_C;
    u16 view_E;
    u16 stepLeft_10;
    u16 stepRight_12;
    u16 pause_14;
    u16 item_16;
    u16 map_18;
    u16 option_1A;
} s_ControllerConfig;
STATIC_ASSERT_SIZEOF(s_ControllerConfig, 28);

typedef struct _InventoryItem
{
    u8 id_0;      /** `InventoryItemId` */
    u8 count_1;
    u8 command_2; /** `InventoryCmdId` */
    u8 field_3;   // Some sort of index?
} s_InventoryItem;
STATIC_ASSERT_SIZEOF(s_InventoryItem, 4);

typedef struct _Savegame
{
    s_InventoryItem items_0[INVENTORY_ITEM_COUNT_MAX];
    s8              field_A0;
    s8              field_A1[3];
    s8              mapOverlayId_A4;          /** `e_MapOverlayId` Index to overlay `.BIN` files. */
    s8              mapRoomIdx_A5;            /** Index to local map geometry `.IPD` files. */
    s16             savegameCount_A6;
    s8              locationId_A8;            /** `e_SaveLocationId` */
    u8              current2dMapIdx_A9;       /** `e_Current2dMapIdx` Index to the 2D map shown when opening the map screen. */
    u8              equippedWeapon_AA;        /** `e_InventoryItemId` Affects only the visible player weapon model. */
    u8              inventorySlotCount_AB;    /** Item slots. */
    u32             flags_AC;                 /** Flashlight state? On: 3, Off: 1*/
    s32             field_B0[45];
    s32             hasMapsFlags_164;         // See Sparagas' `HasMapsFlags` struct for details of every bit.
    u32             eventFlags_168[6];        //----------------------------------------
    s32             eventFlags_180[2];        //
    s32             eventFlags_188;           //
    s32             eventFlags_18C;           // Only tested a few, but it seems all are related to events and pick-up flags, grouped by location and not item types.
    s32             eventFlags_190[4];        //
    s32             eventFlags_1A0;           //
    s32             eventFlags_1A4[12];       //----------------------------------------
    s32             mapMarkingFlags_1D4[2];   //----------------------------------------
    s32             mapMarkingFlags_1DC;      // These 3 are one `u32 mapMarkingFlags[25];` (or maybe `u8 mapMarkingFlags[100];`?) See Sparagas' `MapMarkingsFlags` struct for details of every bit.
    s32             mapMarkingFlags_1E0[22];  //----------------------------------------
    q19_12          healthSaturation_238;     /** Range [0, 300]. Ampoules give extra health that get stored. If the player if loose health then the stored extra health will slowly start to sum to player's health, in any case extra health will start to reduce progressively even if the player has full health. */
    s16             pickedUpItemCount_23C;
    s8              field_23E;
    u8              field_23F;
    q19_12          playerHealth_240;         /** Default: 100 */
    q19_12          playerPositionX_244;
    q3_12           playerRotationY_248;      /** Range [0, 0.999755859375], positive Z: 0, clockwise rotation. It can be multiplied by 360 to get degrees. */
    u8              clearGameCount_24A;       /** Range [0, 99] */
    u8              clearGameEndings_24B;     /** `e_GameEndingFlags` */
    q19_12          playerPositionZ_24C;
    q20_12          gameplayTimer_250;
    q20_12          runDistance_254;
    q20_12          walkDistance_258;
    u8              isNextFearMode_25C             : 1; // Makes savegame entry text gold.
    u8              add290Hours_25C_1              : 2; // Adds 290 hours per 1 bit, i.e. 290, 580, 870.
    u8              pickedUpSpecialItemCount_25C_3 : 5; // Red/None: 0?, Yellow: 8, Green: 16, Rainbow: 24 (unobtainable).
                                                        /** Sparagas' investigations indicate this variable should be
                                                         * two different variables. However, splitting it causes minor
                                                         * mismatches in some functions.
                                                         *
                                                         * The first 3 bits indicate the number of special items the
                                                         * player has picked up, and the last 2 bits indicate the color of the Hyper
                                                         * Blaster beam.
                                                         *
                                                         * Belek666 suggests that some functions specifically access this field as 5 bits.
                                                         *
                                                         * The the odd access results in a bug where the results screen will count more collected
                                                         * special items than normal by additionally reading one of the two bits
                                                         * for the Hyper Blaster beam color.
                                                         */
    u8              meleeKillCount_25D;
    u8              meleeKillCountB_25E; // Can't be packed if used as `u16`.
    u8              rangedKillCount_25F;
    u32             field_260          : 28;
    s32             gameDifficulty_260 : 4;  /** `e_GameDifficulty`. */
    u16             firedShotCount_264;      /** Missed shot count = firedShotCount - (closeRangeShotCount + midRangeShotCount + longRangeShotCount). */
    u16             closeRangeShotCount_266; /** Only hits counted. */
    u16             midRangeShotCount_268;   /** Only hits counted. */
    u16             longRangeShotCount_26A;  /** Only hits counted. */
    u16             field_26C;
    u16             field_26E; // Related to enemy kills.
    u16             field_270;
    u16             field_272;
    u16             field_274;
    u16             field_276;
    u16             field_278;
    s8              field_27A; // Flags.
    u8              continueCount_27B;
} s_Savegame;
STATIC_ASSERT_SIZEOF(s_Savegame, 636);

/** TODO: Known as `Trigger` in SilentHillMapExaminer: https://github.com/ItEndsWithTens/SilentHillMapExaminer/blob/master/src/SHME.ExternalTool.Guts/Trigger.cs */
typedef struct _EventParam
{
    u8  unk_0[2];
    s16 eventFlagId_2;
    u8  unk_4[1];
    u8  field_5; // Something related to pickup items.
    u8  unk_6[2];
    u32 triggerType_8_0        : 5;
    u32 pointOfInterestIdx_8_5 : 8; /** Index into `g_MapOverlayHeader.mapAreaLoadParams_1C`. */
    u32 flags_8_13             : 6;
    u32 field_8_19             : 5;
    u32 field_8_24             : 1;
    u32 mapOverlayIdx_8_25     : 6;
    u32 field_8_31             : 1;
} s_EventParam;
STATIC_ASSERT_SIZEOF(s_EventParam, 12);

typedef struct _SaveUserConfig
{
    s_ControllerConfig controllerConfig_0;
    s8                 optScreenPosX_1C;          /** Range: [-11, 11], default: 0. */
    s8                 optScreenPosY_1D;          /** Range: [-8, 8], default: 0. */
    u8                 optSoundType_1E;           /** `bool` | Stereo: `false`, Monaural: `true`, default: Stereo. */
    u8                 optVolumeBgm_1F;           /** Range: [0, 128] with steps of 8, default: 16. */
    u8                 optVolumeSe_20;            /** Range: [0, 128] with steps of 8, default: 16. */
    u8                 optVibrationEnabled_21;    /** `bool` | Off: 0, On: 128, default: On. */
    u8                 optBrightness_22;          /** Range: [0, 7], default: 3. */
    u8                 optExtraWeaponCtrl_23;     /** `bool` | Switch: `false`, Press: `true`, default: Press. */
    u8                 optExtraBloodColor_24;     /** `e_BloodColor` | Default: Normal. */
    s8                 optAutoLoad_25;            /** `bool` | Off: `false`, On: `true`, default: Off. */
    u8                 unk_26;
    u8                 optExtraOptionsEnabled_27; /** Holds unlocked option flags. */
    s8                 optExtraViewCtrl_28;       /** `bool` | Normal: `false`, Reverse: `true`, default: Normal. */
    s8                 optExtraViewMode_29;       /** `bool` | Normal: `false`, Self View: `true`, default: Normal. */
    s8                 optExtraRetreatTurn_2A;    /** `bool` | Normal: `false`, Reverse: `true`, default: Normal. */
    s8                 optExtraWalkRunCtrl_2B;    /** `bool` | Normal: `false`, Reverse: `true`, default: Normal. */
    s8                 optExtraAutoAiming_2C;     /** `bool` | On: `false`, Off: `true`, default: On. */
    s8                 optExtraBulletAdjust_2D;   /** x1-x6: Range [0, 5], default: x1. */
    u16                seenGameOverTips_2E[1];    /** Bitfield tracking seen game-over tips. Each bit corresponds to a tip index (0–14), set bits indicate seen tips. Resets after picking all 15. */
    s8                 unk_30[4];
    u32                palLanguageId_34;
} s_SaveUserConfig;
STATIC_ASSERT_SIZEOF(s_SaveUserConfig, 56);

/** @brief Appended to `ShSavegame` and `ShSaveUserConfig` during game save. Contains 8-bit XOR checksum + magic.
 * Checksum generated via `Savegame_ChecksumGenerate`.
 */
typedef struct _SavegameFooter
{
    u8  checksum_0[2];
    u16 magic_2;
} s_SavegameFooter;
STATIC_ASSERT_SIZEOF(s_SavegameFooter, 4);

/** @brief Contains `s_Savegame` data with the footer appended to the end containing the checksum + magic. */
typedef struct _SavegameContainer
{
    s_Savegame       savegame_0;
    s_SavegameFooter footer_27C;
} s_SavegameContainer;
STATIC_ASSERT_SIZEOF(s_SavegameContainer, 640);

/** @brief Contains `s_SaveUserConfig` data padded to 128 bytes, with footer at the end containing checksum + magic. */
typedef struct _SaveUserConfigContainer
{
    s_SaveUserConfig config_0;
    u8               pad_38[68];
    s_SavegameFooter footer_7C;
} s_SaveUserConfigContainer;

typedef struct _GameWork
{
    s_SaveUserConfig   config_0;
    s_ControllerData   controllers_38[CONTROLLER_COUNT_MAX];
    s_Savegame         autosave_90;
    s_Savegame         savegame_30C;
    u16                gsScreenWidth_588;
    u16                gsScreenHeight_58A;
    u8                 background2dColor_R_58C;
    u8                 background2dColor_G_58D;
    u8                 background2dColor_B_58E;
    u8                 field_58F;            // Command code? Maybe `s_PrimColor` fits here.
    s32                gameStatePrev_590;    /** `e_GameState` */
    s32                gameState_594;        /** `e_GameState` */
    s32                gameStateStep_598[3]; /** Temp data used by current `gameState`. Can be another state ID or other data. 
                                              * This states could be sub-states for specific events of individual screens
                                              * because of the way it's normally used in menus. For example: in the settings
                                              * screen, [0] is used to define what option the player has selected, and [1] is used
                                              * during specific settings screens, such as the position screen or the brightness screen.
                                              *
                                              * [2] is likely rarely used or maybe only used during maps.
                                              */
    s8                 unk_5A4[4];
    s32                field_5A8;
    s32                field_5AC;
    s8                 unk_5B0;
    s8                 mapAnimIdx_5B1;
    s8                 soundCmd_5B2;
    s8                 field_5B3;
    s_AnalogController rawController_5B4;
    s8                 unk_5BC[28];
} s_GameWork;
STATIC_ASSERT_SIZEOF(s_GameWork, 1496);

/** @brief Const data passed over to `Anim_Update` funcs. Struct itself contains which `Anim_Update` func is to be called. */
typedef struct _AnimInfo
{
    void (*funcPtr_0)(struct _SubCharacter*, s32, GsCOORDINATE2*, struct _AnimInfo*); // TODO: `funcPtr_0` signature doesn't currently match `Anim_Update`.
    u8  field_4;
    s8  hasVariableTimeDelta_5;
    s8  animIdx_6;
    u8  unk_7;
    union
    {
        q19_12 constTimeDelta;
        q19_12 (*variableTimeDeltaFunc)();
    } timeDelta_8;
    s16 keyframeIdx0_C;
    s16 keyframeIdx1_E;
} s_AnimInfo;
STATIC_ASSERT_SIZEOF(s_AnimInfo, 16);

typedef struct _ModelAnimData
{
    // Following 4 bytes might be packed into an s32 called `animStatus`,
    // implied by an original param name in `vcMixSelfViewEffectToWatchTgtPos`.

    u8          animIdx_0;        // Sometimes checked like a bit field.
    u8          maybeSomeState_1; // State says if `animTime_4` is anim time or a func ptr? That field could be a union.
    u16         flags_2;          /** `e_AnimFlags` */
    q19_12      time_4;           /** Time along keyframe timeline. */ 
    s16         keyframeIdx0_8;
    s16         keyframeIdx1_A;
    s_AnimInfo* animInfo_C;
    s_AnimInfo* animInfo_10;
} s_ModelAnim;
STATIC_ASSERT_SIZEOF(s_ModelAnim, 20);

typedef struct _Model
{
    s8 charaId_0;      /** `e_CharacterId` */
    u8 paletteIdx_1;   /** Changes the texture palette index for this model. */
    u8 state_2;        /** Current state for this model/character. 0 usually means it still has to be initialize. */
    u8 stateStep_3;    // Step number or temp data for the current `state_2`? In `s_MainCharacterExtra` always 1, set to 0 for 1 tick when anim state appears to change.
                       // Used differently in player's `s_SubCharacter`. 0: anim transitioning(?), bit 1: animated, bit 2: turning.
    s_ModelAnim anim_4;
} s_Model;
STATIC_ASSERT_SIZEOF(s_Model, 24);

typedef union 
{
    s32 val32;
    s16 val16[2];
    s8  val8[4];
} u_Property;

// TODO: Unsure if this struct is puppet doctor specific or shared with all characterss. Pointer gets set at puppetDoc+0x124.
typedef struct
{
    s32         health_0;
    s8          unk_4[32];
    s_AnimInfo* animInfo_24;
    s8          unk_28[12];
} s_800D5710;
STATIC_ASSERT_SIZEOF(s_800D5710, 0x34);

// TODO: Re-offset `s_SubCharaPropertiesPlayer` / `s_SubCharaPropertiesNpc`.
// Probably easier to do that after it's merged with rest of code.
typedef struct _SubCharaPropertiesPlayer
{
    s32    field_E4;
    s32    afkTimer_E8; // Increments every tick for 10 seconds before AFK anim starts.
    s32    positionY_EC;
    s32    field_F0;
    s32    field_F4;
    s32    runTimer_F8;      // Tick counter?
    q19_12 exertionTimer_FC; // Counts ~20 seconds worth of ticks while running and caps at 0x23000.
    s32    field_100;
    s32    field_104;    // Distance?
    q19_12 runTimer_108; // `FP_TIME` format timer?.
    u8     field_10C;    // Player SFX pitch?
    u8     field_10D;
    s8     unk_10E[6];
    q19_12 gasWeaponPowerTimer_114; // Timer for the rock drill and chainsaw power.
    s16    field_118;
    s8     unk_11A[2];
    s32    flags_11C; /** `e_PlayerFlags`. */
    s16    field_120; // Angle which the player turns when doing a quick turn. In order words, some sort of holder for angle Y.
    s16    field_122; // Some sort of X angle for the player. Specially used when aiming an enemy.
    s16    field_124;
    q3_12  playerMoveDistance_126; // Used to indicate how much the player should move foward.
} s_SubCharaPropertiesPlayer;
STATIC_ASSERT_SIZEOF(s_SubCharaPropertiesPlayer, 68);

// TODO: This may be a puppet doctor/nurse specific struct, need to compare with other NPCs.
typedef struct _SubCharaPropertiesNpc
{
    s32         unk_E4;
    VECTOR3     field_E8;
    s32         field_F4;
    s32         field_F8;
    s32         field_FC;
    s32         field_100;
    s32         field_104;
    s32         field_108;
    s32         field_10C;
    s8          unk_110[4];
    s32         field_114;
    s8          field_118;
    s8          modelVariation_119;
    s16         field_11A;
    s32         field_11C;
    s16         field_120;
    s16         field_122;
    s_800D5710* field_124;
} s_SubCharaPropertiesNpc;
STATIC_ASSERT_SIZEOF(s_SubCharaPropertiesNpc, 68);

typedef struct _SubCharPropertiesLarvalStalker
{
    s32        unk_E4;            // Is this part of `a_SubCharacter`?
    u_Property properties_E8[16];
} s_SubCharaPropertiesLarvalStalker;
STATIC_ASSERT_SIZEOF(s_SubCharaPropertiesLarvalStalker, 68);

typedef struct
{
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s16 field_6;
} s_SubCharacter_D8;
STATIC_ASSERT_SIZEOF(s_SubCharacter_D8, 8);

typedef struct _SubCharacter
{
    s_Model model_0;           // In player: Manage the half lower part of Harry's body animations (legs and feet).
    VECTOR3 position_18;       /** `Q19.12` */
    SVECTOR rotation_24;       // Maybe `SVECTOR3` instead of `SVECTOR` because 4th field is copy of `.xy` field.
    SVECTOR rotationSpeed_2C;  /** Range [-0x700, 0x700]. */
    q19_12  field_34;          // Character Y Position?
    s32     moveSpeed_38;
    s16     headingAngle_3C;
    s16     flags_3E;
    s8      field_40;          // In player: Index of the NPC attacking the player.
                               // In NPCs: Unknown.
    s8      attackReceived_41; // Indicates what attack has been performed to the character. For enemies is based on `e_EquippedWeaponId` enum.
    s8      unk_42[2];
    s16     field_44;
    s8      field_46; // In player: The ID (from `e_EquippedWeaponId`) of the weapon which player is using.
                      // This is not the same as `attackReceived_41`, as this value only resets when player is aiming.
                      // In NPCs: Indicates attack performed on player.
    s8      field_47;
    s8      unk_48[4];
    s32     field_4C; // } Fields used by `func_8008A3E0`. Types guessed for now.
    s16     field_50; // } Angle?
    s16     field_52; // } Angle?
    s16     field_54; // }
    s16     field_56; // }
    s32     field_58; // }
    VECTOR3 field_5C;
    VECTOR3 field_68;
    VECTOR3 field_74;
    VECTOR3 field_80;
    VECTOR3 field_8C;
    VECTOR3 field_98;
    VECTOR3 field_A4;
    q19_12  health_B0;
    s32     field_B4;          // X? - In player: Adds/subtracts if hurt by enemy.
    s32     field_B8;          // Y? - In player: Adds/subtracts if hurt by enemy.
    s32     field_BC;          // Z? - In player: Adds/subtracts if hurt by enemy.
    q19_12  damageReceived_C0;
    u16     deathTimer_C4;     // Part of `shBattleInfo` struct in SH2, may use something similar here.
    s16     timer_C6;          // Some sort of timer, value written by `Ai_LarvalStalker_Update`.

    // Fields seen used inside maps (eg. `map0_s00` `func_800D923C`)

    s16               field_C8; // } Anim root offset?
    s16               field_CA; // }
    s16               field_CC; // }
    s16               field_CE;
    s16               field_D0;
    s16               field_D2;
    s16               field_D4;
    s16               field_D6;
    s_SubCharacter_D8 field_D8;

    s32 field_E0   : 8; // Related to collision. If the player collides with the only enemy in memory and the enemy is knocked down, this is set to 1.
    s32 field_E0_8 : 4; // Flags?
    s32 unk_E0_12  : 20;

    union
    {
        s_SubCharaPropertiesPlayer        player;
        s_SubCharaPropertiesNpc           npc;
        s_SubCharaPropertiesLarvalStalker larvalStalker;
    } properties_E4;
} s_SubCharacter;
STATIC_ASSERT_SIZEOF(s_SubCharacter, 296);

typedef struct _MainCharacterExtra
{
    s_Model model_0;           // Manages upper half body's animations (torso, arms, head).
    q19_12  field_18;
    s32     state_1C;          /** `e_PlayerState` */
    s32     upperBodyState_20; /** `e_PlayerUpperBodyState` */
    s32     lowerBodyState_24; /** `e_PlayerLowerBodyState` */
    s32     field_28;          // Related to item interactions. Forcing specific values opens options menu, a behaviour is caused by `func_800373CC`.
} s_MainCharacterExtra;
STATIC_ASSERT_SIZEOF(s_MainCharacterExtra, 44);

// Based on SH2 symbols this struct should be named `shPlayerWork` and `chara_0` should be `player`.
typedef struct _MainCharacter
{
    s_SubCharacter       chara_0;
    s_MainCharacterExtra extra_128;
} s_MainCharacter;
STATIC_ASSERT_SIZEOF(s_MainCharacter, 340);

typedef struct _PlayerCombat
{
    VECTOR3 field_0;
    s8      unk_C[3];
    s8      equippedWeapon_F; /** `e_EquippedWeaponId` */
    u8      currentWeaponAmmo_10;
    u8      totalWeaponAmmo_11;
    s8      field_12;
    u8      isAiming_13; /** `bool` */
} s_PlayerCombat;
STATIC_ASSERT_SIZEOF(s_PlayerCombat, 20);

typedef union
{
    s32 field_0;
    struct
    {
        u8 field_0;
        u8 field_1;
        u8 field_2;
        u8 unk_3;
    } s_field_0;
} u_Unk0;

typedef union
{
    s32 field_0;
    u8  vec_0[4];
} u_Color;

typedef struct
{
    u_Unk0  field_0;
    s16     field_4; // FP alpha.
    s16     field_6;
    s16     field_8;
    s16     field_A;
    s16     field_C;
    u8      field_E;
    s8      unk_F;
    s32     field_10;
    u_Color field_14;
    u_Color field_18;
    u_Color field_1C;
    u_Color field_20;
    u_Color field_24;
    s16     unk_28;
    s16     unk_2A;
} s_sub_StructUnk3;
STATIC_ASSERT_SIZEOF(s_sub_StructUnk3, 44);

typedef struct
{
    s_sub_StructUnk3 field_0;
    s16              field_2C; // FP alpha.
    s16              field_2E; // FP alpha.
    s32              field_30;
} s_StructUnk3;
STATIC_ASSERT_SIZEOF(s_StructUnk3, 52);

typedef struct
{
    s32          field_0;
    s8*          field_4;
    s32          field_8;
    s32          field_C;
    s32          field_10;
    u8           field_14;
    u8           isFlashlightOn_15; /** `bool` | Off: `false`, On: `true`. */
    u8           field_16;          /** `bool` */
    s8           unk_17;
    s16          flashlightIntensity_18;
    u16          field_1A;
    s_StructUnk3 field_1C[2];
    s_StructUnk3 field_84[2];
    s_StructUnk3 field_EC[2];
    s_StructUnk3 field_154;
} s_SysWork_2288;
STATIC_ASSERT_SIZEOF(s_SysWork_2288, 392);

typedef struct
{
    s8  field_0[4];
    s32 field_4;
    s8  unk_8[4];
    s32 field_C;
} s_SysWork_2514_C;

typedef struct _s_SysWork_2514_18
{
    struct _s_SysWork_2514_18* next_0;

    u8  unk_4[4]; // Prev?
    u8  unk_8[4];
    s32 field_C;
    u8  unk_10[8];
    u8  unk_18[4];
    u16 field_1C;
    u16 field_1E;
} s_SysWork_2514_18;

typedef struct
{
    u32               unk_0     : 8;
    u8                field_1   : 8;
    u32               field_2_0 : 1;
    u32               field_2_1 : 1;
    u32               field_2_2 : 14;
    u8                unk_4[8];
    s_SysWork_2514_C* field_C;
    u8                unk_10[8];
    s_SysWork_2514_18 head_18;
} s_SysWork_2514;
STATIC_ASSERT_SIZEOF(s_SysWork_2514, 56);

typedef struct _SysWork
{
    s8              unk_0[8];
    s32             sysState_8;     /** `e_SysState` */
    s32             sysStateStep_C; /** Current state step of `sysState_8` the game is in. */
    s32             field_10;       // Sometimes assigned to same thing as `sysStateStep_C`. Contains selected entry index from pickup item dialogs?
    s32             field_14;
    s32             field_18;
    s32             timer_1C;
    s32             timer_20;
    s32             timer_24;
    s32             field_28;
    q19_12          timer_2C; // Cutscene message timer?
    s32             field_30;
    s8              unk_34[4];
    s_PlayerCombat  playerCombatInfo_38; // Something related to weapons and attack. This is a struct as `func_8003CD6C` requires one and `GameFs_MapLoad` input is pointing here.
    s_MainCharacter player_4C;
    s_SubCharacter  npcs_1A0[NPC_COUNT_MAX];
    GsCOORDINATE2   playerBoneCoords_890[PlayerBone_Count];
    GsCOORDINATE2   unkCoords_E30[5];  // Might be part of previous array for 5 extra coords which go unused.
    GsCOORDINATE2   npcCoords_FC0[60]; // Dynamic coord buffer? 10 coords per NPC (given max of 6 NPCs).
    s8              field_2280;        // Maybe NPC AI data past this point.
    s8              loadingScreenIdx_2281;
    s8              field_2282;
    s8              field_2283; // Index into `SfxPairs`.
    u16             field_2284[3];
    u16             field_228A;
    s32             field_228C;
    s32             field_2290;
    s8              unk_2294[4];
    s32             processFlags_2298; /** `e_SysWorkProcessFlags` */
    s32             field_229C;
    s32             field_22A0; // Flags.
    s32             flags_22A4;
    s8              unk_22A8[160]; // TODO: Confirmed `GsCOORDINATE2` at start.
    s8              field_2348   : 8;
    s8              field_2349   : 8; // Particle spawn multiplier?
    u8              field_234A   : 8;
    u8              field_234B_0 : 4;
    u8              field_234B_4 : 4;
    s32             mapMsgTimer_234C;
    u8              enableHighResGlyphs_2350_0      : 4; /** `bool` */
    u8              silentYesSelection_2350_4       : 4; /** `bool` */
    u32             inventoryItemSelectedIdx_2351   : 8;
    u32             flags_2352                      : 8;
    s8              enemyTargetIdx_2353; // Index of the enemy that is being attacked by the player.
    s8              field_2354[4];       // Size dervied from `func_80070320`.
    u8              field_2358;
    s8              unk_2359[1];
    u8              field_235A; /** If the player stop walking or running forward the value (as a bit) changes
                                 * to 00000001 and if the player stop walking backward the value changes
                                 * to 00000010.
                                 */
    s8              unk_235B[1];
    GsCOORDINATE2*  field_235C;
    VECTOR3         field_2360; // Position?
    GsCOORDINATE2*  field_236C;
    SVECTOR         field_2370; // Rotation.
    s16             field_2378;
    s16             cameraAngleY_237A;
    s16             cameraAngleZ_237C;
    s16             field_237E;
    s32             cameraRadiusXz_2380;
    s32             cameraY_2384;
    s_SysWork_2288  field_2388;
    s32             field_2510;
    s_SysWork_2514  field_2514;
    u8              unk_254C[508];
    s16             field_2748[9];  // `func_80035ED0` loops over this.
    u8              unk_275A[2];
    s32             field_275C; // `q19_12`?
    s32             field_2760;
    s32             field_2764;
} s_SysWork;
STATIC_ASSERT_SIZEOF(s_SysWork, 10088);

extern void* g_OvlBodyprog; // 0x80010004
extern void* g_OvlDynamic;  // 0x80010000

extern s_SysWork               g_SysWork;       // 0x800B9FC0
extern s_GameWork              g_GameWork;      // 0x800BC728
extern s_GameWork* const       g_GameWorkConst; // 0x80024D44
extern s_GameWork* const       g_GameWorkPtr;   // 0x80024D54
extern s_Savegame* const       g_SavegamePtr;   // 0x80024D48
extern s_ControllerData* const g_Controller0;   // 0x80024D4C
extern s_ControllerData* const g_Controller1;   // 0x80024D50

extern s32  g_ObjectTableIdx; // 0x800B9FB8
extern GsOT g_ObjectTable0[]; // 0x800A8F74
extern GsOT g_ObjectTable1[]; // 0x800A8FC4

extern q19_12        g_DeltaTime0;    // 0x800B5CC0
extern q19_12        g_DeltaTime1;    // 0x800A8FEC
extern q19_12        g_DeltaTime2;    // 0x800B9CC8
extern u32           g_MapEventIdx;   // 0x800A9A14
extern s_EventParam* g_MapEventParam; // 0x800BCDD8

extern s32 g_IntervalVBlanks; // 0x800A8FF0
extern s32 g_PrevVBlanks;     // 0x800A9770
extern s32 g_VBlanks;         // 0x800B5C34
extern s32 g_UncappedVBlanks; // 0x800B5C38

/** @brief Sets `sysState` in `g_SysWork` for the next tick. */
static inline void SysWork_StateSetNext(e_SysState sysState)
{
    g_SysWork.sysState_8     = sysState;
    g_SysWork.timer_24       = 0;
    g_SysWork.sysStateStep_C = 0;
    g_SysWork.field_28       = 0;
    g_SysWork.field_10       = 0;
    g_SysWork.timer_2C       = 0;
    g_SysWork.field_14       = 0;
}

/** @brief Increments `sysStateStep` in `g_SysWork` for the next tick. */
static inline void SysWork_StateStepIncrement()
{
    g_SysWork.field_28 = 0;
    g_SysWork.field_10 = 0;
    g_SysWork.timer_2C = 0;
    g_SysWork.field_14 = 0;
    g_SysWork.sysStateStep_C++;
}

/** @brief Sets `sysStateStep` in `g_SysWork` for the next tick. */
static inline void SysWork_NextStateStepSet(s32 sysStateStep)
{
    g_SysWork.sysStateStep_C = sysStateStep;
    g_SysWork.field_28       = 0;
    g_SysWork.field_10       = 0;
    g_SysWork.timer_2C       = 0;
    g_SysWork.field_14       = 0;
}

/** @brief Resets `sysStateStep` in `g_SysWork` for the next tick. */
static inline void SysWork_StateStepReset()
{
    g_SysWork.sysStateStep_C = NO_VALUE;
    g_SysWork.field_28       = 0;
    g_SysWork.field_10       = 0;
    g_SysWork.timer_2C       = 0;
    g_SysWork.field_14       = 0;
}

/** @brief Clears state steps twice for some reason? Only used once below, others use regular `Game_StateSetNext`. */
static inline void Game_StateSetNext_ClearStateSteps(e_GameState gameState)
{
    e_GameState prevState;

    prevState = g_GameWork.gameState_594;

    g_GameWork.gameState_594        = gameState;
    g_SysWork.timer_1C              = 0;
    g_SysWork.timer_20              = 0;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;
    g_GameWork.gameStateStep_598[0] = prevState;
    g_GameWork.gameStatePrev_590    = prevState;
    g_GameWork.gameStateStep_598[0] = 0;
}

/** @brief Sets the GameState to be used in the next game update.
 * Inlined into `stream` and `b_konami`.
 */
static inline void Game_StateSetNext(e_GameState gameState)
{
    e_GameState prevState;

    prevState = g_GameWork.gameState_594;

    g_GameWork.gameState_594 = gameState;

    g_SysWork.timer_1C = 0;
    g_SysWork.timer_20 = 0;

    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateStep_598[0] = prevState;
    g_GameWork.gameStatePrev_590    = prevState;
    g_GameWork.gameStateStep_598[0] = 0;
}

/** @brief Returns the GameState to the previously used state.
 * Inlined into credits.
 */
static inline void Game_StateSetPrevious()
{
    e_GameState prevState;

    prevState = g_GameWork.gameState_594;

    g_SysWork.timer_1C = 0;
    g_SysWork.timer_20 = 0;

    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateStep_598[0] = prevState;
    g_GameWork.gameState_594        = g_GameWork.gameStatePrev_590;
    g_GameWork.gameStatePrev_590    = prevState;
    g_GameWork.gameStateStep_598[0] = 0;
}

/** @brief Sets the given flag ID inside the savegame event flags array. */
static inline void Savegame_EventFlagSet(u32 flagId)
{
    s16 flagIdx;
    s16 flagBit;

    flagIdx = flagId / 32;
    flagBit = flagId % 32;

    g_SavegamePtr->eventFlags_168[flagIdx] |= 1 << flagBit;
}

/** @brief Sets the given flag ID inside the savegame event flags array.
 *
 * @note This macro version seems to work better for `func_800DBAA0` than the `Savegame_EventFlagSet` inline above.
 * Maybe other code depends on how the inline worked though.
 */
#define Savegame_EventFlagSetAlt(flagIdx) \
    (g_SavegamePtr->eventFlags_168[(flagIdx) / 32] |= 1 << ((flagIdx) % 32))

/** @brief Checks if the given flag ID is set inside the array of 16-bit flag values. */
static inline s32 Flags16b_IsSet(u16* array, s32 flagId)
{
    // BUG: `>> 5` divides `flagId` by 32 to get array index, but array is of 16-bit values.
    // Maybe copy-paste from `u32` version of func.
    return (array[flagId >> 5] >> (flagId & 0x1F)) & (1 << 0);
}

/** @brief Sets the given animation flag on both player character and player extra data. */
// TODO: Move to separate character/player header.
static inline void Player_AnimFlagsSet(u32 flags)
{
    s_MainCharacterExtra* extra;
    s_SubCharacter*       chara;

    extra = &g_SysWork.player_4C.extra_128;
    chara = &g_SysWork.player_4C.chara_0;

    extra->model_0.anim_4.flags_2 |= flags;
    chara->model_0.anim_4.flags_2 |= flags;
}

#endif
