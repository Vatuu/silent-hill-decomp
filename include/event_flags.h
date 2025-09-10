/** @brief Game event flag IDs stored in savegame.
 * Can be accessed through `Savegame_EventFlagGet` / `Savegame_EventFlagSet` */
typedef enum _EventFlag
{
    EventFlag_0                  = 0,  // M0S01 FirstAidKid? Also used in M0S02, might just be a default.
    EventFlag_25                 = 25,
    EventFlag_PickupKitchenKnife = 35, // M0S01
    EventFlag_PickupFlashlight   = 36, // M0S01
    EventFlag_PickupPocketRadio  = 37, // M0S01
    EventFlag_38                 = 38,
    EventFlag_39                 = 39,
    EventFlag_40                 = 40,
    EventFlag_45                 = 45,
    EventFlag_46                 = 46,
    EventFlag_47                 = 47,
    EventFlag_48                 = 48,
    EventFlag_49                 = 49,
    EventFlag_50                 = 50,
    EventFlag_51                 = 51,
    EventFlag_52                 = 52,
    EventFlag_57                 = 57,
    EventFlag_58                 = 58,
    EventFlag_PickupGasolineTask = 60, // M0S02
    EventFlag_61                 = 61,
    EventFlag_62                 = 62,
    EventFlag_105                = 105,
    EventFlag_106                = 106,
    EventFlag_133                = 133,
    EventFlag_134                = 134,
    EventFlag_146                = 146,
    EventFlag_159                = 159,
    EventFlag_171                = 171,
    EventFlag_181                = 181,
    EventFlag_183                = 183,
    EventFlag_SeenSaveScreen     = 186,
    EventFlag_197                = 197,
    EventFlag_211                = 211,
    EventFlag_250                = 250,
    EventFlag_295                = 295,
    EventFlag_379                = 379,
    EventFlag_448                = 448,
    EventFlag_481                = 481,
    EventFlag_574                = 574,

    /** `MAP0_S01` common item pickups. */
    EventFlag_M0S01_HealthDrink0 = 596,
    EventFlag_M0S01_HealthDrink1 = 597,

    /** `MAP0_S02` common item pickups. */
    EventFlag_M0S02_FirstAidKit    = 598,
    EventFlag_M0S02_HealthDrink0   = 599,
    EventFlag_M0S02_HealthDrink1   = 600,
    EventFlag_M0S02_HealthDrink2   = 601,
    EventFlag_M0S02_HandgunBullets = 602,
    EventFlag_M0S02_HealthDrink3   = 603,
    EventFlag_M0S02_HealthDrink4   = 604
} e_EventFlag;
