/** @brief Flag indices for game event flags stored in savegame.
 * Accessed via `Savegame_EventFlagGet`/`Savegame_EventFlagSet`.
 */
typedef enum _EventFlag
{
    EventFlag_0 = 0, // M0S01 FirstAidKit? Also used in M0S02, might just be a default.

    EventFlag_25 = 25,

    /** `MAP7_S01` and `MAP7_S02` common item pickups, early numbers could be reclaimed flags, or Nowhere was designed very early on? */
    EventFlag_M7S01_RifleShells     = 27,
    EventFlag_M7S01_HandgunBullets0 = 28,
    EventFlag_M7S01_HealthDrink0    = 29,
    EventFlag_M7S01_HandgunBullets1 = 30,
    EventFlag_M7S01_ShotgunShells   = 31,
    EventFlag_M7S01_FirstAidKit     = 32,
    EventFlag_M7S01_HandgunBullets2 = 33,

    EventFlag_M0S01_PickupKitchenKnife = 35,
    EventFlag_M0S01_PickupFlashlight   = 36,
    EventFlag_M0S01_PickupPocketRadio  = 37,
    EventFlag_M0S01_PickupMap          = 38,
    EventFlag_39                       = 39,
    EventFlag_40                       = 40,

    EventFlag_41 = 41,
    EventFlag_42 = 42,
    EventFlag_43 = 43,

    EventFlag_45 = 45,
    EventFlag_46 = 46,
    EventFlag_47 = 47,
    EventFlag_48 = 48,
    EventFlag_49 = 49,
    EventFlag_50 = 50,
    EventFlag_51 = 51,
    EventFlag_52 = 52,

    EventFlag_M0S02_PickupKatana = 56,

    EventFlag_57 = 57,
    EventFlag_58 = 58,

    EventFlag_M0S02_PickupGasolineTank = 60,
    EventFlag_61                       = 61,
    EventFlag_62                       = 62,

    EventFlag_M1S00_PickupMap = 67, // Shared with M1S06

    EventFlag_M7S01_HealthDrink1 = 86,

    EventFlag_105 = 105,
    EventFlag_106 = 106,

    EventFlag_133 = 133,
    EventFlag_134 = 134,

    EventFlag_143 = 143,

    EventFlag_M0S02_PickupChannelingStone = 144,

    EventFlag_146 = 146,

    EventFlag_159 = 159,

    EventFlag_M2S00_PickupMap = 171, // Shared with M2S04

    EventFlag_181 = 181,

    EventFlag_183 = 183,

    EventFlag_SeenSaveScreen = 186,

    EventFlag_197 = 197,

    EventFlag_M3S00_FirstAidKit = 199, // Odd numbering not with other common items, possibly some default that goes unused, shared with M3S01 and M3S06.

    EventFlag_M3S00_PickupMap = 207,   // Shared with M3S01, M3S06
    EventFlag_M3S01_PickupMap = 208,   // M3S01 also uses flag above.

    EventFlag_211 = 211,

    EventFlag_250 = 250,

    EventFlag_284 = 284,

    EventFlag_295 = 295,

    EventFlag_306 = 306,

    EventFlag_M5S00_PickupMap = 361,

    EventFlag_M5S01_PickupMap = 370,

    EventFlag_379 = 379,

    EventFlag_M6S03_PickupMap = 436,

    EventFlag_448 = 448,

    EventFlag_481 = 481,

    EventFlag_485 = 485,
    EventFlag_521 = 521,
    EventFlag_525 = 525,

    EventFlag_574 = 574,

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
    EventFlag_M0S02_HealthDrink4   = 604,

    // TODO: Following flags came from ghidra, not tested in decomp yet.
    /** `MAP1_S00` common item pickups. */
    EventFlag_M1S00_HandgunBullets0 = 605,
    EventFlag_M1S00_HandgunBullets1 = 606,
    EventFlag_M1S00_HandgunBullets2 = 607,
    EventFlag_M1S00_HealthDrink     = 608,
    EventFlag_M1S00_FirstAidKit     = 609,

    /** `MAP1_S01` common item pickups. */
    EventFlag_M1S01_HandgunBullets0 = 610,
    EventFlag_M1S01_FirstAidKit     = 611,
    EventFlag_M1S01_HealthDrink     = 612,
    EventFlag_M1S01_HandgunBullets1 = 613,
    EventFlag_M1S01_HandgunBullets2 = 614,

    /** `MAP1_S02` common item pickups. */
    EventFlag_M1S02_Ampoule0        = 615,
    EventFlag_M1S02_ShotgunShells0  = 616,
    EventFlag_M1S02_ShotgunShells1  = 617,
    EventFlag_M1S02_FirstAidKit0    = 618,
    EventFlag_M1S02_HandgunBullets0 = 619,
    EventFlag_M1S02_HandgunBullets1 = 620,
    EventFlag_M1S02_HandgunBullets2 = 621,
    EventFlag_M1S02_Ampoule1        = 622,
    EventFlag_M1S02_HealthDrink0    = 623,
    EventFlag_M1S02_FirstAidKit1    = 624,
    EventFlag_M1S02_HealthDrink1    = 625,

    /** `MAP1_S03` common item pickups. */
    EventFlag_M1S03_ShotgunShells0  = 626,
    EventFlag_M1S03_HandgunBullets0 = 627,
    EventFlag_M1S03_HealthDrink0    = 628,
    EventFlag_M1S03_HandgunBullets1 = 629,
    EventFlag_M1S03_HandgunBullets2 = 630,
    EventFlag_M1S03_ShotgunShells1  = 631,
    EventFlag_M1S03_HandgunBullets3 = 632,
    EventFlag_M1S03_HealthDrink1    = 633,
    EventFlag_M1S03_HealthDrink2    = 634,
    EventFlag_M1S03_FirstAidKit     = 635,

    /** `MAP2_S00` common item pickups. */
    EventFlag_M2S00_FirstAidKit0     = 636,
    EventFlag_M2S00_HandgunBullets0  = 637,
    EventFlag_M2S00_HandgunBullets1  = 638,
    EventFlag_M2S00_HealthDrink0     = 639,
    EventFlag_M2S00_HandgunBullets2  = 640,
    EventFlag_M2S00_ShotgunShells0   = 641,
    EventFlag_M2S00_HealthDrink1     = 642,
    EventFlag_M2S00_HandgunBullets3  = 643,
    EventFlag_M2S00_HandgunBullets4  = 644,
    EventFlag_M2S00_HandgunBullets5  = 645,
    EventFlag_M2S00_HandgunBullets6  = 646,
    EventFlag_M2S00_HandgunBullets7  = 647,
    EventFlag_M2S00_HandgunBullets8  = 648,
    EventFlag_M2S00_HealthDrink2     = 649,
    EventFlag_M2S00_HealthDrink3     = 650,
    EventFlag_M2S00_HealthDrink4     = 651,
    EventFlag_M2S00_HandgunBullets9  = 652,
    EventFlag_M2S00_HealthDrink5     = 653,
    EventFlag_M2S00_HandgunBullets10 = 654,
    EventFlag_M2S00_HealthDrink6     = 655,
    EventFlag_M2S00_HealthDrink7     = 656,
    EventFlag_M2S00_HealthDrink8     = 657,
    EventFlag_M2S00_HealthDrink9     = 658,
    EventFlag_M2S00_HealthDrink10    = 659,
    EventFlag_M2S00_HealthDrink11    = 660,
    EventFlag_M2S00_ShotgunShells1   = 661,
    EventFlag_M2S00_FirstAidKit1     = 662,
    EventFlag_M2S00_HandgunBullets11 = 663,
    EventFlag_M2S00_HandgunBullets12 = 664,
    EventFlag_M2S00_HandgunBullets13 = 665,
    EventFlag_M2S00_HandgunBullets14 = 666,
    EventFlag_M2S00_FirstAidKit2     = 667,

    /** `MAP2_S01` common item pickups. */
    EventFlag_M2S01_HealthDrink = 668,

    /** `MAP2_S02` common item pickups. */
    EventFlag_M2S02_HealthDrink0    = 669,
    EventFlag_M2S02_HealthDrink1    = 670,
    EventFlag_M2S02_HandgunBullets0 = 671,
    EventFlag_M2S02_HandgunBullets1 = 672,
    EventFlag_M2S02_HealthDrink2    = 673,

    /** `MAP2_S04` common item pickups. */
    EventFlag_M2S04_ShotgunShells0  = 674,
    EventFlag_M2S04_HandgunBullets0 = 675,
    EventFlag_M2S04_HandgunBullets1 = 676,
    EventFlag_M2S04_ShotgunShells1  = 677,
    EventFlag_M2S04_HandgunBullets2 = 678,
    EventFlag_M2S04_HandgunBullets3 = 679,
    EventFlag_M2S04_RifleShells     = 680,

    /** `MAP3_S01` common item pickups. */
    EventFlag_M3S01_HealthDrink = 681,

    /** `MAP3_S03` common item pickups. */
    EventFlag_M3S03_FirstAidKit0   = 682,
    EventFlag_M3S03_HealthDrink    = 683,
    EventFlag_M3S03_HandgunBullets = 684,
    EventFlag_M3S03_FirstAidKit1   = 685,
    EventFlag_M3S03_ShotgunShells  = 686,

    /** `MAP3_S04` common item pickups. */
    EventFlag_M3S04_HealthDrink0   = 687,
    EventFlag_M3S04_HealthDrink1   = 688,
    EventFlag_M3S04_HealthDrink2   = 689,
    EventFlag_M3S04_HealthDrink3   = 690,
    EventFlag_M3S04_HandgunBullets = 691,

    /** `MAP3_S05` common item pickups. */
    EventFlag_M3S05_Ampoule        = 692,
    EventFlag_M3S05_HealthDrink    = 693,
    EventFlag_M3S05_HandgunBullets = 694,
    EventFlag_M3S05_ShotgunShells  = 695,

    /** `MAP4_S03` common item pickups. */
    EventFlag_M4S03_FirstAidKit  = 696,
    EventFlag_M4S03_RifleShells0 = 697,
    EventFlag_M4S03_RifleShells1 = 698,

    /** `MAP5_S00` common item pickups. */
    EventFlag_M5S00_ShotgunShells   = 699,
    EventFlag_M5S00_HealthDrink0    = 700,
    EventFlag_M5S00_HandgunBullets0 = 701,
    EventFlag_M5S00_RifleShells     = 702,
    EventFlag_M5S00_FirstAidKit0    = 703,
    EventFlag_M5S00_FirstAidKit1    = 704,
    EventFlag_M5S00_HealthDrink1    = 705,
    EventFlag_M5S00_HandgunBullets1 = 706,

    /** `MAP5_S01` common item pickups. */
    EventFlag_M5S01_RifleShells0   = 707,
    EventFlag_M5S01_HandgunBullets = 708,
    EventFlag_M5S01_FirstAidKit    = 709,
    EventFlag_M5S01_HealthDrink    = 710,
    EventFlag_M5S01_RifleShells1   = 711,

    /** `MAP5_S02` common item pickups. */
    EventFlag_M5S02_HealthDrink0 = 712,
    EventFlag_M5S02_HealthDrink1 = 713,
    EventFlag_M5S02_RifleShells  = 714,
    EventFlag_M5S02_HealthDrink2 = 715,

    /** `MAP5_S03` common item pickups. */
    EventFlag_M5S03_HealthDrink0  = 716,
    EventFlag_M5S03_ShotgunShells = 717,
    EventFlag_M5S03_HealthDrink1  = 718,

    // TODO: 719/720/721, might be used in other MAP5/MAP6 code.

    /** `MAP6_S01` common item pickups. */
    EventFlag_M6S01_RifleShells    = 722,
    EventFlag_M6S01_HandgunBullets = 723,
    EventFlag_M6S01_HealthDrink    = 724,

    /** `MAP6_S03` common item pickups. */
    EventFlag_M6S03_HealthDrink0   = 725,
    EventFlag_M6S03_HandgunBullets = 726,
    EventFlag_M6S03_HealthDrink1   = 727,
} e_EventFlag;
