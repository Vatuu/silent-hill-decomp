/** @brief Indices for game event flags stored in the savegame.
 * Accessed via `Savegame_EventFlagGet`/`Savegame_EventFlagSet`.
 */
typedef enum _EventFlag
{
    EventFlag_None = 0,

    EventFlag_1  = 1,
    EventFlag_2  = 2,
    EventFlag_3  = 3,
    EventFlag_4  = 4,
    EventFlag_5  = 5,
    EventFlag_6  = 6,
    EventFlag_7  = 7,
    EventFlag_8  = 8,
    EventFlag_9  = 9,
    EventFlag_10 = 10,
    EventFlag_11 = 11,
    EventFlag_12 = 12,
    EventFlag_13 = 13,
    EventFlag_14 = 14,
    EventFlag_15 = 15,
    EventFlag_16 = 16,
    EventFlag_17 = 17,
    EventFlag_18 = 18,
    EventFlag_19 = 19,
    EventFlag_20 = 20,
    EventFlag_21 = 21,
    EventFlag_22 = 22,
    EventFlag_23 = 23,
    EventFlag_24 = 24,
    EventFlag_25 = 25,
    EventFlag_26 = 26,

    /** `MAP7_S01` and `MAP7_S02` common item pickups. Early numbers could be reclaimed flags or Nowhere was designed very early on? */

    EventFlag_M7S01_RifleShells         = 27,
    EventFlag_M7S01_HandgunBullets0     = 28,
    EventFlag_M7S01_HealthDrink0        = 29,
    EventFlag_M7S01_HandgunBullets1     = 30,
    EventFlag_M7S01_ShotgunShells       = 31,
    EventFlag_M7S01_FirstAidKit         = 32,
    EventFlag_M7S01_HandgunBullets2     = 33,
    EventFlag_M2S00_WaterWorksCutscene  = 34,
    EventFlag_M0S01_PickupKitchenKnife  = 35,
    EventFlag_M0S01_PickupFlashlight    = 36,
    EventFlag_M0S01_PickupPocketRadio   = 37,
    EventFlag_M0S01_PickupMap           = 38,
    EventFlag_M0S01_FmvStarted          = 39,
    EventFlag_M0S01_CafeCutsceneStarted = 40,

    EventFlag_41                        = 41,
    EventFlag_42                        = 42,
    EventFlag_M0S01_PickedUpKnifeAndMap = 43,

    EventFlag_M0S01_AirScreamerIntroCutsceneStarted = 45,
    EventFlag_46                                    = 46,
    EventFlag_47                                    = 47,
    EventFlag_M0S01_AirScreamerDied                 = 48,
    EventFlag_49                                    = 49, // Might be end of CafeCutscene?
    EventFlag_50                                    = 50,
    EventFlag_M0S01_AirScreamerDeathPlayed          = 51,
    EventFlag_52                                    = 52,
    EventFlag_53                                    = 53,

    EventFlag_M0S02_PickupKatana = 56,

    EventFlag_57                          = 57,
    EventFlag_58                          = 58,
    EventFlag_59                          = 59,
    EventFlag_M0S02_PickupGasolineTank    = 60,
    EventFlag_61                          = 61,
    EventFlag_62                          = 62,
    EventFlag_M2S00_PickupChainsaw        = 63,
    EventFlag_M2S00_PickupRockDrill       = 64,
    EventFlag_65                          = 65,
    EventFlag_66                          = 66,
    EventFlag_M1S00_PickupMap             = 67, // Shared with M1S06
    EventFlag_M1S01_PickupChemical        = 68,
    EventFlag_M1S01_PickupGoldMedallion   = 69,
    EventFlag_M1S01_PickupSilverMedallion = 70,
    EventFlag_71                          = 71,
    EventFlag_72                          = 72,
    EventFlag_73                          = 73,
    EventFlag_74                          = 74,
    EventFlag_M1S01_PianoPuzzleSolved     = 75,
    EventFlag_76                          = 76,
    EventFlag_77                          = 77,
    EventFlag_78                          = 78,
    EventFlag_79                          = 79,
    EventFlag_80                          = 80,
    EventFlag_81                          = 81,
    EventFlag_82                          = 82,
    EventFlag_83                          = 83,
    EventFlag_84                          = 84,

    EventFlag_M7S01_HealthDrink1 = 86,

    EventFlag_91                               = 91,
    EventFlag_92                               = 92,
    EventFlag_M1S02_PickupPictureCard          = 93,
    EventFlag_M1S02_SeenDoorWithHorizontalSlot = 94,
    EventFlag_M1S02_PickupShotgun              = 95,
    EventFlag_96                               = 96,
    EventFlag_97                               = 97,
    EventFlag_98                               = 98,
    EventFlag_99                               = 99,
    EventFlag_100                              = 100,
    EventFlag_101                              = 101,
    EventFlag_102                              = 102,
    EventFlag_M1S03_LockerOpened               = 103,
    EventFlag_104                              = 104,
    EventFlag_105                              = 105,
    EventFlag_106                              = 106,
    EventFlag_107                              = 107,
    EventFlag_M1S03_PickupLibraryReserveKey    = 108,

    EventFlag_M1S02_PickupRubberBall     = 110,
    EventFlag_M1S02_UsedRubberBall       = 111,
    EventFlag_112                        = 112,
    EventFlag_M1S03_KeyDownTheDrain      = 113,
    EventFlag_M1S02_PickupClassroomKey   = 114,
    EventFlag_115                        = 115,
    EventFlag_M1S03_MonsterLurksBookRead = 116,
    EventFlag_117                        = 117,
    EventFlag_118                        = 118,
    EventFlag_119                        = 119,

    EventFlag_120 = 120,
    EventFlag_121 = 121,
    EventFlag_122 = 122,

    EventFlag_129 = 129,
    EventFlag_130 = 130,
    EventFlag_131 = 131,
    EventFlag_132 = 132,
    EventFlag_133 = 133,
    EventFlag_134 = 134,
    EventFlag_135 = 135,

    EventFlag_M1S06_ChurchMarkedOnMap     = 136,
    EventFlag_M1S06_PickupKGordonKey      = 137,
    EventFlag_138                         = 138,
    EventFlag_139                         = 139,
    EventFlag_140                         = 140,
    EventFlag_141                         = 141,
    EventFlag_142                         = 142,
    EventFlag_143                         = 143,
    EventFlag_M0S02_PickupChannelingStone = 144,
    EventFlag_145                         = 145,
    EventFlag_146                         = 146,
    EventFlag_147                         = 147,
    EventFlag_M2S00_DogHouseNoteFound     = 148,
    EventFlag_M2S00_PickupDogHouseKey     = 149,
    EventFlag_M2S00_PickupKeyOfLion       = 150,
    EventFlag_M2S00_PickupKeyOfWoodman    = 151,
    EventFlag_M2S00_PickupKeyOfScarecrow  = 152,
    EventFlag_153                         = 153,
    EventFlag_M2S00_LockOfLionOpen        = 154,
    EventFlag_M2S00_LockOfWoodmanOpen     = 155,
    EventFlag_M2S00_LockOfScarecrowOpen   = 156,
    EventFlag_M2S00_DoorOfEclypseOpen     = 157,
    EventFlag_158                         = 158,
    EventFlag_159                         = 159,

    EventFlag_M2S00_PickupSteelPipe   = 161,
    EventFlag_M2S00_KGordonDoorOpen   = 162,
    EventFlag_163                     = 163,
    EventFlag_164                     = 164,
    EventFlag_165                     = 165,
    EventFlag_166                     = 166,
    EventFlag_167                     = 167,
    EventFlag_168                     = 168,
    EventFlag_169                     = 169,
    EventFlag_170                     = 170,
    EventFlag_M2S00_PickupMap         = 171, // Shared with M2S04
    EventFlag_172                     = 172,
    EventFlag_173                     = 173,
    EventFlag_174                     = 174,
    EventFlag_M2S00_PickupHealthDrink = 175,

    EventFlag_176                       = 176,
    EventFlag_M2S01_PickupFlauros       = 177,
    EventFlag_M2S01_PickupDrawbridgeKey = 178,
    EventFlag_179                       = 179,
    EventFlag_180                       = 180,

    EventFlag_181 = 181,
    EventFlag_182 = 182,
    EventFlag_183 = 183,
    EventFlag_184 = 184,
    EventFlag_185 = 185,

    EventFlag_SeenSaveScreen = 186,

    EventFlag_188                   = 188,
    EventFlag_189                   = 189,
    EventFlag_M2S02_AntiqueShopOpen = 190,
    EventFlag_191                   = 191,
    EventFlag_192                   = 192,
    EventFlag_193                   = 193,
    EventFlag_194                   = 194,
    EventFlag_195                   = 195,
    EvnetFlag_196                   = 196,
    EventFlag_197                   = 197,
    EventFlag_198                   = 198,

    EventFlag_M3S00_FirstAidKit = 199, // Odd numbering not with other common items, possibly some default that goes unused. Shared with M3S01 and M3S06.
    EventFlag_200               = 200,

    EventFlag_203                       = 203,
    EventFlag_204                       = 204,
    EventFlag_M3S01_PickupPlasticBottle = 205,
    EventFlag_M3S01_PickupUnknownLiquid = 206,
    EventFlag_M3S00_PickupMap           = 207, // Shared with M3S01 and M3S06.
    EventFlag_M3S01_PickupMap           = 208, // M3S01 also uses flag above.
    EventFlag_M3S01_PickupBasementKey   = 209,
    EventFlag_M3S01_BasementDoorOpen    = 210,
    EventFlag_M3S01_GeneratorOn         = 211,

    EventFlag_212 = 212,
    EventFlag_213 = 213,
    EventFlag_214 = 214,
    EventFlag_215 = 215,
    EventFlag_216 = 216,
    EventFlag_217 = 217,
    EventFlag_218 = 218,
    EventFlag_219 = 219,
    EventFlag_220 = 220,
    EventFlag_221 = 221,
    EventFlag_222 = 222,
    EventFlag_223 = 223,
    EventFlag_224 = 224,
    EventFlag_225 = 225,
    EventFlag_226 = 226,

    EventFlag_232                       = 232,
    EventFlag_233                       = 233,
    EventFlag_234                       = 234,
    EventFlag_235                       = 235,
    EventFlag_236                       = 236,
    EventFlag_237                       = 237,
    EventFlag_238                       = 238,
    EventFlag_239                       = 239,
    EventFlag_240                       = 240,
    EventFlag_M3S04_PickupPlateOfQueen  = 241,
    EventFlag_M3S03_PickupPlateOfTurtle = 242,
    EventFlag_M3S03_PickupPlateOfHatter = 243,
    EventFlag_M3S03_PickupPlateOfCat    = 244,

    EventFlag_M3S03_PickupBloodPack            = 249,
    EventFlag_250                              = 250,
    EventFlag_M3S03_PickupDisinfectingAlcohol  = 251,
    EventFlag_M3S03_PickupLighter              = 252,
    EventFlag_M3S05_PickupVideoTape            = 253,
    EventFlag_254                              = 254,
    EventFlag_M3S03_PickupBasementStoreroomKey = 255,
    EventFlag_256                              = 256,

    EventFlag_M3S05_PickupExaminationRoomKey = 257,
    EventFlag_258                            = 258,
    EventFlag_259                            = 259,
    EventFlag_260                            = 260,

    EventFlag_265                        = 265,
    EventFlag_266                        = 266,
    EventFlag_267                        = 267,
    EventFlag_268                        = 268,
    EventFlag_269                        = 269,
    EventFlag_270                        = 270,
    EventFlag_271                        = 271,
    EventFlag_272                        = 272,
    EventFlag_273                        = 273,
    EventFlag_274                        = 274,
    EventFlag_275                        = 275,
    EventFlag_276                        = 276,
    EventFlag_277                        = 277,
    EventFlag_278                        = 278,
    EventFlag_279                        = 279,
    EventFlag_280                        = 280,
    EventFlag_281                        = 281,
    EventFlag_M3S05_CabinetPushed        = 282,
    EventFlag_M3S05_AlcoholPouredOnVines = 283,
    EventFlag_284                        = 284,
    EventFlag_285                        = 285,
    EventFlag_286                        = 286,

    EventFlag_288 = 288,

    EventFlag_M3S05_PickupHammer = 289,

    EventFlag_292                        = 292,
    EventFlag_293                        = 293,
    EventFlag_294                        = 294,
    EventFlag_295                        = 295,
    EventFlag_M3S06_PickupAntiqueShopKey = 296,
    EventFlag_297                        = 297,
    EventFlag_298                        = 298,
    EventFlag_299                        = 299,
    EventFlag_300                        = 300,
    EventFlag_301                        = 301,
    EventFlag_302                        = 302,
    EventFlag_303                        = 303,
    EventFlag_304                        = 304,
    EventFlag_305                        = 305,
    EventFlag_306                        = 306,
    EventFlag_307                        = 307,
    EventFlag_308                        = 308,
    EventFlag_309                        = 309,
    EventFlag_M4S01_PickupAxe            = 310,
    EventFlag_311                        = 311,
    EventFlag_312                        = 312,
    EventFlag_313                        = 313,

    EventFlag_314 = 314,
    EventFlag_315 = 315,
    EventFlag_316 = 316,
    EventFlag_317 = 317,

    EventFlag_319 = 319,
    EventFlag_320 = 320,
    EventFlag_321 = 321,
    EventFlag_322 = 322,
    EventFlag_323 = 323,
    EventFlag_324 = 324,
    EventFlag_325 = 325,
    EventFlag_326 = 326,

    EventFlag_327                      = 327,
    EventFlag_M4S03_PickupHuntingRifle = 328,
    EventFlag_329                      = 329,
    EventFlag_330                      = 330,
    EventFlag_331                      = 331,
    EventFlag_332                      = 332,
    EventFlag_333                      = 333,

    EventFlag_334 = 334,

    EventFlag_335 = 335,
    EventFlag_336 = 336,
    EventFlag_337 = 337,
    EventFlag_338 = 338,
    EventFlag_339 = 339,
    EventFlag_340 = 340,
    EventFlag_341 = 341,

    EventFlag_346 = 346,
    EventFlag_347 = 347,
    EventFlag_348 = 348,

    EventFlag_349                  = 349,
    EventFlag_350                  = 350,
    EventFlag_351                  = 351,
    EventFlag_352                  = 352,
    EventFlag_M5S00_PickupSewerKey = 353,
    EventFlag_354                  = 354,
    EventFlag_355                  = 355,
    EventFlag_356                  = 356,
    EventFlag_357                  = 357,
    EventFlag_358                  = 358,
    EventFlag_359                  = 359,
    EventFlag_360                  = 360,
    EventFlag_M5S00_PickupMap      = 361,
    EventFlag_362                  = 362,

    EventFlag_M5S01_PickupMap = 370,
    EventFlag_371             = 371,

    EventFlag_375                 = 375,
    EventFlag_M5S02_PickupSafeKey = 376,
    EventFlag_M5S02_UsedSafeKey   = 377,
    EventFlag_378                 = 378,
    EventFlag_379                 = 379,
    EventFlag_380                 = 380,
    EventFlag_381                 = 381,

    EventFlag_M5S03_PickupMagnet = 386,
    EventFlag_387                = 387,
    EventFlag_388                = 388,
    EventFlag_389                = 389,
    EventFlag_390                = 390,
    EventFlag_391                = 391,

    EventFlag_M5S03_SeenSecondNewspaper = 393,
    EventFlag_M5S01_KaufmannKeyUsed     = 394,
    EventFlag_395                       = 395,
    EventFlag_396                       = 396,
    EventFlag_397                       = 397,
    EventFlag_398                       = 398,

    EventFlag_401 = 401,
    EventFlag_402 = 402,
    EventFlag_403 = 403,

    EventFlag_405 = 405,
    EventFlag_406 = 406,
    EventFlag_407 = 407,
    EventFlag_408 = 408,
    EventFlag_409 = 409,
    EventFlag_410 = 410,
    EventFlag_411 = 411,
    EventFlag_412 = 412,
    EventFlag_413 = 413,
    EventFlag_414 = 414,
    EventFlag_415 = 415,
    EventFlag_416 = 416,
    EventFlag_417 = 417,
    EventFlag_418 = 418,
    EventFlag_419 = 419,
    EventFlag_420 = 420,

    EventFlag_423 = 423,
    EventFlag_424 = 424,
    EventFlag_425 = 425,
    EventFlag_426 = 426,
    EventFlag_427 = 427,
    EventFlag_428 = 428,
    EventFlag_429 = 429,
    EventFlag_430 = 430,

    EventFlag_431             = 431,
    EventFlag_432             = 432,
    EventFlag_433             = 433,
    EventFlag_434             = 434,
    EventFlag_435             = 435,
    EventFlag_M6S03_PickupMap = 436,
    EventFlag_437             = 437,
    EventFlag_438             = 438,
    EventFlag_439             = 439,
    EventFlag_440             = 440,
    EventFlag_441             = 441,
    EventFlag_442             = 442,
    EventFlag_443             = 443,
    EventFlag_444             = 444,
    EventFlag_445             = 445,
    EventFlag_446             = 446,
    EventFlag_447             = 447,
    EventFlag_448             = 448,
    EventFlag_449             = 449,
    EventFlag_450             = 450,
    EventFlag_451             = 451,
    EventFlag_452             = 452,
    EventFlag_453             = 453,
    EventFlag_454             = 454,
    EventFlag_455             = 455,
    EventFlag_456             = 456,
    EventFlag_457             = 457,
    EventFlag_458             = 458,
    EventFlag_459             = 459,
    EventFlag_460             = 460,

    EventFlag_461 = 461,
    EventFlag_462 = 462,
    EventFlag_463 = 463,
    EventFlag_464 = 464,
    EventFlag_465 = 465,
    EventFlag_466 = 466,
    EventFlag_467 = 467,
    EventFlag_468 = 468,
    EventFlag_469 = 469,
    EventFlag_470 = 470,
    EventFlag_471 = 471,
    EventFlag_472 = 472,
    EventFlag_473 = 473,
    EventFlag_474 = 474,
    EventFlag_475 = 475,
    EventFlag_476 = 476,
    EventFlag_477 = 477,
    EventFlag_478 = 478,
    EventFlag_479 = 479,
    EventFlag_480 = 480,
    EventFlag_481 = 481,
    EventFlag_482 = 482,
    EventFlag_483 = 483,

    EventFlag_484 = 484,
    EventFlag_485 = 485,
    EventFlag_486 = 486,
    EventFlag_487 = 487,
    EventFlag_488 = 488,
    EventFlag_489 = 489,
    EventFlag_490 = 490,
    EventFlag_491 = 491,
    EventFlag_492 = 492,
    EventFlag_493 = 493,
    EventFlag_494 = 494,
    EventFlag_495 = 495,
    EventFlag_496 = 496,
    EventFlag_497 = 497,
    EventFlag_498 = 498,
    EventFlag_499 = 499,

    EventFlag_500 = 500, // Used as base event index added to `D_800E1690.field_0` in loop.
    EventFlag_501 = 501,
    EventFlag_502 = 502,
    EventFlag_503 = 503,
    EventFlag_504 = 504,
    EventFlag_505 = 505,
    EventFlag_506 = 506,
    EventFlag_507 = 507, // } Used in `for (i < 4)` loop.
    EventFlag_508 = 508, // }
    EventFlag_509 = 509, // }
    EventFlag_510 = 510, // }

    EventFlag_511 = 511, // } Used in `for (i < 4)` loop.
    EventFlag_512 = 512, // }
    EventFlag_513 = 513, // }
    EventFlag_514 = 514, // }

    EventFlag_515 = 515, // } Used in `for (i < 4)` loop.
    EventFlag_516 = 516, // }
    EventFlag_517 = 517, // }
    EventFlag_518 = 518, // }

    EventFlag_M7S01_PickupCamera          = 519,
    EventFlag_M7S01_PickupRingOfContract  = 520,
    EventFlag_M7S01_PickupStoneOfTime     = 521,
    EventFlag_M7S01_PickupPliers          = 522,
    EventFlag_M7S01_PickupScrewdriver     = 523,
    EventFlag_M7S01_PickupBirdCageKey     = 524,
    EventFlag_525                         = 525,
    EventFlag_M7S01_PickupKeyOfHagith     = 526,
    EventFlag_M7S01_PickupKeyOfPhaleg     = 527,
    EventFlag_M7S02_PickupKeyOfBethor     = 528,
    EventFlag_M7S02_PickupKeyOfAratron    = 529,
    EventFlag_530                         = 530,
    EventFlag_531                         = 531,
    EventFlag_532                         = 532,
    EventFlag_533                         = 533,
    EventFlag_534                         = 534,
    EventFlag_M7S01_PickupAmuletOfSolomon = 535,
    EventFlag_M7S01_PickupCrestOfMercury  = 536,

    EventFlag_M7S02_PickupAnkh             = 537,
    EventFlag_M7S02_PickupDaggerOfMelchior = 538,
    EventFlag_M7S02_PickupDiskOfOuroboros  = 539,
    EventFlag_540                          = 540, // } Used in `for (i < 5)` loop.
    EventFlag_541                          = 541, // }
    EventFlag_542                          = 542, // }
    EventFlag_543                          = 543, // }
    EventFlag_544                          = 544, // }
    EventFlag_545                          = 545,
    EventFlag_546                          = 546,
    EventFlag_547                          = 547,
    EventFlag_548                          = 548,
    EventFlag_549                          = 549,
    EventFlag_550                          = 550,
    EventFlag_551                          = 551,
    EventFlag_552                          = 552,
    EventFlag_553                          = 553,
    EventFlag_554                          = 554,
    EventFlag_555                          = 555,
    EventFlag_556                          = 556,
    EventFlag_557                          = 557,

    EventFlag_559 = 559,
    EventFlag_560 = 560,
    EventFlag_561 = 561,
    EventFlag_562 = 562,
    EventFlag_563 = 563,
    EventFlag_564 = 564, // } Used in `for (i < 5)` loop.
    EventFlag_565 = 565, // }
    EventFlag_566 = 566, // }
    EventFlag_567 = 567, // }
    EventFlag_568 = 568, // }
    EventFlag_569 = 569,
    EventFlag_570 = 570,
    EventFlag_571 = 571,
    EventFlag_572 = 572,
    EventFlag_573 = 573,
    EventFlag_574 = 574,
    EventFlag_575 = 575,
    EventFlag_576 = 576,
    EventFlag_577 = 577,
    EventFlag_578 = 578,
    EventFlag_579 = 579,
    EventFlag_580 = 580,

    EventFlag_582 = 582,
    EventFlag_583 = 583,
    EventFlag_584 = 584,
    EventFlag_585 = 585,
    EventFlag_586 = 586,
    EventFlag_587 = 587,
    EventFlag_588 = 588,
    EventFlag_589 = 589,
    EventFlag_590 = 590,
    EventFlag_591 = 591,
    EventFlag_592 = 592,
    EventFlag_593 = 593,
    EventFlag_594 = 594,

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

    EventFlag_M6S00_HealthDrink   = 719,
    EventFlag_M6S00_ShotgunShells = 720,
    EventFlag_M6S00_FirstAidKit   = 721,

    /** `MAP6_S01` common item pickups. */

    EventFlag_M6S01_RifleShells    = 722,
    EventFlag_M6S01_HandgunBullets = 723,
    EventFlag_M6S01_HealthDrink    = 724,

    /** `MAP6_S03` common item pickups. */

    EventFlag_M6S03_HealthDrink0   = 725,
    EventFlag_M6S03_HandgunBullets = 726,
    EventFlag_M6S03_HealthDrink1   = 727,

    EventFlag_868 = 868,

    EventFlag_876 = 876,

    EventFlag_878 = 878,

    EventFlag_880 = 880,

    EventFlag_882 = 882,

    EventFlag_884 = 884,

    EventFlag_886 = 886,

    EventFlag_888 = 888,

    EventFlag_890 = 890,

    EventFlag_894 = 894,

    EventFlag_896 = 896,

    EventFlag_898 = 898,

    EventFlag_900 = 900,

    EventFlag_902 = 902,

    EventFlag_904 = 904,

    EventFlag_906 = 906,

    EventFlag_910 = 910,

    EventFlag_914 = 914,

    EventFlag_922 = 922,

    EventFlag_925 = 925,

    EventFlag_927 = 927,

    EventFlag_944 = 944,

    EventFlag_948 = 948,

    EventFlag_950 = 950,

    EventFlag_952 = 952,

    EventFlag_954 = 954,

    EventFlag_956 = 956,

    EventFlag_982 = 982,

    EventFlag_984 = 984,

    EventFlag_986 = 986,

    EventFlag_988 = 988,

    EventFlag_990 = 990,

    EventFlag_992 = 992,

    EventFlag_994 = 994,

    EventFlag_996 = 996,

    EventFlag_998 = 998,

    EventFlag_1000 = 1000,

    EventFlag_1002 = 1002,

    EventFlag_1012 = 1012,

    EventFlag_1014 = 1014,

    EventFlag_1016 = 1016,

    EventFlag_1018 = 1018,

    EventFlag_1020 = 1020,

    EventFlag_1022 = 1022,

    EventFlag_1046 = 1046,

    EventFlag_1049 = 1049,

    EventFlag_1057 = 1057,

    EventFlag_1059 = 1059,

    EventFlag_1069 = 1069,
    EventFlag_1070 = 1070,
    EventFlag_1071 = 1071,
    EventFlag_1072 = 1072,
    EventFlag_1073 = 1073,

    EventFlag_1075 = 1075,
    EventFlag_1076 = 1076,
    EventFlag_1077 = 1077,
    EventFlag_1078 = 1078,
    EventFlag_1079 = 1079,
    EventFlag_1080 = 1080,
    EventFlag_1081 = 1081,
    EventFlag_1082 = 1082,

    EventFlag_1084 = 1084,
    EventFlag_1085 = 1085,
    EventFlag_1086 = 1086,
    EventFlag_1087 = 1087,
    EventFlag_1088 = 1088,
    EventFlag_1089 = 1089,
    EventFlag_1090 = 1090,
    EventFlag_1091 = 1091,

    EventFlag_1093 = 1093,

    EventFlag_1095 = 1095,
    EventFlag_1096 = 1096,

    EventFlag_1099 = 1099,
    EventFlag_1100 = 1100,

    EventFlag_1103 = 1103,
    EventFlag_1104 = 1104,

    EventFlag_1106 = 1106,

    EventFlag_1108 = 1108,

    EventFlag_1110 = 1110,

    EventFlag_1112 = 1112,

    EventFlag_1115 = 1115,

    EventFlag_1117 = 1117,
    EventFlag_1118 = 1118,

    EventFlag_1120 = 1120,

    EventFlag_1122 = 1122,

    EventFlag_1124 = 1124,

    EventFlag_1144 = 1144,

    EventFlag_1147 = 1147,

    EventFlag_1148 = 1148,
    EventFlag_1149 = 1149,

    EventFlag_1151 = 1151,

    EventFlag_1153 = 1153,
    EventFlag_1154 = 1154,
    EventFlag_1155 = 1155,

    EventFlag_1157 = 1157,
    EventFlag_1158 = 1158,
    EventFlag_1159 = 1159,

    EventFlag_1161 = 1161,

    EventFlag_1163 = 1163,

    EventFlag_1165 = 1165,
    EventFlag_1166 = 1166,

    EventFlag_1169 = 1169,

    EventFlag_1171 = 1171,

    EventFlag_1173 = 1173,

    EventFlag_1175 = 1175,

    EventFlag_1177 = 1177,

    EventFlag_1179 = 1179,
    EventFlag_1180 = 1180,
    EventFlag_1181 = 1181,

    EventFlag_1183 = 1183,
    EventFlag_1184 = 1184,

    EventFlag_1187 = 1187,

    EventFlag_1189 = 1189,

    EventFlag_1191 = 1191,

    EventFlag_1193 = 1193,

    EventFlag_1195 = 1195,
    EventFlag_1196 = 1196,

    EventFlag_1198 = 1198,

    EventFlag_1200 = 1200,
    EventFlag_1201 = 1201,

    EventFlag_1204 = 1204,

    EventFlag_1206 = 1206,
    EventFlag_1207 = 1207,

    EventFlag_1208 = 1208,

    EventFlag_1222 = 1222,
    EventFlag_1223 = 1223,

    EventFlag_1225 = 1225,

    EventFlag_1227 = 1227,
    EventFlag_1228 = 1228,
    EventFlag_1229 = 1229,
    EventFlag_1230 = 1230,
    EventFlag_1231 = 1231,
    EventFlag_1232 = 1232,
    EventFlag_1233 = 1233,
    EventFlag_1234 = 1234,
    EventFlag_1235 = 1235,
    EventFlag_1236 = 1236,
    EventFlag_1237 = 1237,
    EventFlag_1238 = 1238,
    EventFlag_1239 = 1239,
    EventFlag_1240 = 1240,
    EventFlag_1241 = 1241,

    EventFlag_1243 = 1243,
    EventFlag_1244 = 1244,
    EventFlag_1245 = 1245,
    EventFlag_1247 = 1247,

    EventFlag_1249 = 1249,

    EventFlag_1251 = 1251,

    EventFlag_1253 = 1253,

    EventFlag_1255 = 1255,

    EventFlag_1257 = 1257,

    EventFlag_1259 = 1259,

    EventFlag_1261 = 1261,

    EventFlag_1263 = 1263,

    EventFlag_1265 = 1265,

    EventFlag_1267 = 1267,
    EventFlag_1268 = 1268,

    EventFlag_1270 = 1270,

    EventFlag_1289 = 1289,
    EventFlag_1290 = 1290,

    EventFlag_1293 = 1293,
    EventFlag_1294 = 1294,
    EventFlag_1295 = 1295,
    EventFlag_1296 = 1296,
    EventFlag_1297 = 1297,

    EventFlag_1299 = 1299,
    EventFlag_1300 = 1300,
    EventFlag_1301 = 1301,
    EventFlag_1302 = 1302,
    EventFlag_1303 = 1303,

    EventFlag_1305 = 1305,

    EventFlag_1307 = 1307,

    EventFlag_1309 = 1309,
    EventFlag_1310 = 1310,
    EventFlag_1311 = 1311,
    EventFlag_1312 = 1312,

    EventFlag_1314 = 1314,

    EventFlag_1317 = 1317,

    EventFlag_1319 = 1319,

    EventFlag_1321 = 1321,

    EventFlag_1323 = 1323,

    EventFlag_1325 = 1325,

    EventFlag_1327 = 1327,

    EventFlag_1329 = 1329,

    EventFlag_1331 = 1331,
    EventFlag_1332 = 1332,

    EventFlag_1334 = 1334,

    EventFlag_1336 = 1336,

    EventFlag_1339 = 1339,

    EventFlag_1354 = 1354,

    EventFlag_1363 = 1363,
    EventFlag_1364 = 1364,

    EventFlag_1370 = 1370,

    EventFlag_1371 = 1371,
    EventFlag_1372 = 1372,
    EventFlag_1373 = 1373,

    EventFlag_1375 = 1375,
    EventFlag_1377 = 1377,

    EventFlag_1390 = 1390,
    EventFlag_1391 = 1391,

    EventFlag_1393 = 1393,

    EventFlag_1395 = 1395,

    EventFlag_1397 = 1397,
    EventFlag_1398 = 1398,

    EventFlag_1414 = 1414,

    EventFlag_1424 = 1424,

    EventFlag_1427 = 1427,

    EventFlag_1429 = 1429,

    EventFlag_1431 = 1431,

    EventFlag_1433 = 1433,

    EventFlag_1435 = 1435,
    EventFlag_1436 = 1436,

    EventFlag_1438 = 1438,

    EventFlag_1441 = 1441,
    EventFlag_1442 = 1442,
    EventFlag_1443 = 1443,
    EventFlag_1444 = 1444,
    EventFlag_1445 = 1445,
    EventFlag_1446 = 1446,
    EventFlag_1447 = 1447,
    EventFlag_1448 = 1448,
    EventFlag_1449 = 1449,
    EventFlag_1450 = 1450,

    EventFlag_1452 = 1452,

    EventFlag_1454 = 1454,

    EventFlag_1468 = 1468,

    EventFlag_1472 = 1472,

    EventFlag_1474 = 1474,
    EventFlag_1475 = 1475,
    EventFlag_1476 = 1476,
    EventFlag_1477 = 1477,

    EventFlag_1479 = 1479,

    EventFlag_1481 = 1481,
    EventFlag_1482 = 1482,

    EventFlag_1485 = 1485,

    EventFlag_1487 = 1487,

    EventFlag_1489 = 1489,

    EventFlag_1491 = 1491,
    EventFlag_1492 = 1492,

    EventFlag_1494 = 1494,

    EventFlag_1496 = 1496,

    EventFlag_1513 = 1513,
    EventFlag_1514 = 1514,

    EventFlag_1516 = 1516,

    EventFlag_1519 = 1519,
    EventFlag_1520 = 1520,

    EventFlag_1533 = 1533,

    EventFlag_1535 = 1535,
    EventFlag_1536 = 1536,
    EventFlag_1537 = 1537,

    EventFlag_1539 = 1539,
    EventFlag_1540 = 1540,

    EventFlag_1552 = 1552,

    EventFlag_1558 = 1558,

    EventFlag_1564 = 1564,
    EventFlag_1565 = 1565,

    EventFlag_1567 = 1567,
    EventFlag_1568 = 1568,

    EventFlag_1571 = 1571,

    EventFlag_1573 = 1573,

    EventFlag_1575 = 1575,

    EventFlag_1577 = 1577,
    EventFlag_1578 = 1578,
    EventFlag_1579 = 1579,

    EventFlag_1580 = 1580,

    EventFlag_1582 = 1582,

    EventFlag_1585 = 1585,

    EventFlag_1587 = 1587,
    EventFlag_1588 = 1588,

    EventFlag_1590 = 1590,

    EventFlag_1593 = 1593,

    EventFlag_1595 = 1595,

    EventFlag_1610 = 1610,

    EventFlag_1611 = 1611,
    EventFlag_1612 = 1612,

    EventFlag_1615 = 1615,
    EventFlag_1616 = 1616,

    EventFlag_1619 = 1619,
    EventFlag_1620 = 1620,

    EventFlag_1623 = 1623,

    EventFlag_1625 = 1625,

    EventFlag_1627 = 1627,
    EventFlag_1628 = 1628,

    EventFlag_1631 = 1631,

    EventFlag_1633 = 1633,

    EventFlag_1635 = 1635,
    EventFlag_1636 = 1636,

    EventFlag_1639 = 1639,

    EventFlag_1641 = 1641,
    EventFlag_1642 = 1642,

    EventFlag_Hack = -1, // @hack Force enum to be treated as `s32`.
} e_EventFlag;
