#include "bodyprog/bodyprog.h"
#include "game.h"

s_GameWork* const       g_GameWorkConst = &g_GameWork;
s_Savegame* const       g_SavegamePtr   = &g_GameWork.savegame_30C;
s_ControllerData* const g_Controller0   = &g_GameWork.controllers_38[0];
s_ControllerData* const g_Controller1   = &g_GameWork.controllers_38[1];
s_GameWork* const       g_GameWorkPtr   = &g_GameWork;

const u32 D_80024D58 = 0; // Nothing references it. Might be just padding.

/** TODO: Figure out what this is. I'm only guessing this layout based
 * on the fact the last 3 words are zero and that matches the pattern of
 * using last empty entry as end of list. marker.
 */
typedef struct
{
    s32 unk0;
    s32 unk4;
    s32 unk8;
} s_foo_unknown;

const static s_foo_unknown D_80024D5C[] =
{
    { 0x00080001, 0x0500F880, 0x0280F880 },
    { 0x00080001, 0x02800000, 0x05000000 },
    {}
};

const static s_foo_unknown D_80024D80[] =
{
    { 0x00080001, 0x0280F600, 0x0A00F600 },
    { 0x00080001, 0x0A00F600, 0x0280F600 },
    {}
};

const static s_SpeedZone SpeedZones_THR[] =
{
    { 2, -5120,  4480, -3840, 3200 },
    { 2, -640,   640,   3200, 3840 },
    { SpeedZoneType_Norm,  -4480, -1280,  3200, 6400 },
    { NO_VALUE, 0, 0, 0, 0         } // End of list.
};

const static s_SpeedZone SpeedZones_SP[] =
{
    { SpeedZoneType_Fast,  -3840,  1280, -1920, 640  },
    { SpeedZoneType_Fast,  -640,   1280,  640,  1920 },
    { SpeedZoneType_Norm,  -2560, -1280,  1280, 3840 },
    { SpeedZoneType_Norm,   1280,  3200, -1920, 2560 },
    { NO_VALUE, 0, 0, 0, 0         } // End of list.
};

// 2 bytes of padding.

const static s_SpeedZone SpeedZones_RSR[] =
{
    { SpeedZoneType_Fast,  -1920,  1280, -3200, 640 },
    { SpeedZoneType_Norm,  -3200, -1920, -640,  0   },
    { NO_VALUE, 0, 0, 0, 0        } // End of list.
};

// 2 bytes of padding.

const static s_SpeedZone SpeedZones_RSU[] =
{
    { SpeedZoneType_Fast,  -3200,  0,     640,  2560 },
    { SpeedZoneType_Norm,  -3200, -1280, -1280, 640  },
    { NO_VALUE, 0, 0, 0, 0         } // End of list.
};

// 2 bytes of padding.

const static s_SpeedZone SpeedZones_AP[] =
{
    { SpeedZoneType_Fast,  -1280, 640, -1920, 640  },
    { SpeedZoneType_Norm,   0,    640,  1280, 1920 },
    { NO_VALUE, 0, 0, 0, 0       } // End of list.
};

// 2 bytes of padding.

const static s_SpeedZone SpeedZones_DR[] =
{
    { SpeedZoneType_Norm,  -12800, 13440, -12800, 13440 },
    { NO_VALUE, 0, 0, 0, 0            } // End of list.
};

const static s_SpeedZone SpeedZones_SC[] =
{
    { SpeedZoneType_Norm,  -1920, -640,   640,  1280 },
    { SpeedZoneType_Norm,  -640,   0,     2560, 3200 },
    { SpeedZoneType_Norm,  -640,   0,     0,    640  },
    { SpeedZoneType_Norm,   640,   1920,  640,  1280 },
    { SpeedZoneType_Norm,   1920,  2560,  0,    640  },
    { SpeedZoneType_Norm,   1920,  2560,  2560, 3200 },
    { SpeedZoneType_Norm,  -1280,  0,    -1280, 0    },
    { SpeedZoneType_Norm,   640,   1280, -640,  0    },
    { NO_VALUE, 0, 0, 0, 0         } // End of list.
};

// 2 bytes of padding.

const static s_SpeedZone SpeedZones_SU[] =
{
    { SpeedZoneType_Norm,  -1920, -640,   640,  1280 },
    { SpeedZoneType_Norm,  -640,   0,     2560, 3200 },
    { SpeedZoneType_Norm,  -640,   0,     0,    640  },
    { SpeedZoneType_Norm,   640,   1920,  640,  1280 },
    { SpeedZoneType_Norm,   1920,  2560,  0,    640  },
    { SpeedZoneType_Norm,   1920,  2560,  2560, 3200 },
    { SpeedZoneType_Norm,  -1280,  0,    -1280, 0    },
    { SpeedZoneType_Norm,   0,     1280, -640,  0    },
    { NO_VALUE, 0, 0, 0, 0         } // End of list.
};

// 2 bytes of padding.

const static s_SpeedZone SpeedZones_HP[] =
{
    { SpeedZoneType_Norm,  0, 640, 1920, 2560 },
    { SpeedZoneType_Norm,  0, 640, 0,    640  },
    { NO_VALUE, 0, 0, 0, 0  } // End of list.
};

// 2 bytes of padding.

const static s_SpeedZone SpeedZones_HU[] =
{
    { SpeedZoneType_Norm,   1280,  1920,  1920,  2560 },
    { SpeedZoneType_Norm,   0,     640,   0,     640  },
    { SpeedZoneType_Norm,   1920,  2560,  0,     640  },
    { SpeedZoneType_Norm,  -1920,  0,     1280,  1920 },
    { SpeedZoneType_Norm,  -1280,  0,    -1920, -1280 },
    { SpeedZoneType_Norm,  -2560, -1920, -1280, -640  },
    { SpeedZoneType_Norm,  -2560, -1920, -2560, -1920 },
    { SpeedZoneType_Norm,   0,     1920, -2560, -1920 },
    { SpeedZoneType_Norm,   1280,  2560, -1920, -1280 },
    { SpeedZoneType_Norm,   640,   1280, -1280, -640  },
    { NO_VALUE, 0, 0, 0, 0          } // End of list.
};

// 2 bytes of padding.

const static s_SpeedZone SpeedZones_ER[] =
{
    { SpeedZoneType_Norm,  -1280, -640,  -640,   0    },
    { SpeedZoneType_Norm,  -1920, -640,  -1920, -1280 },
    { SpeedZoneType_Norm,  -1920, -1280, -2560, -1920 },
    { SpeedZoneType_Norm,  2560,   3200, -640,   0    },
    { SpeedZoneType_Norm,  1280,   2560, -1920, -1280 },
    { NO_VALUE, 0, 0, 0, 0          } // End of list.
};

const static s_SpeedZone SpeedZones_XXX[] =
{
    { SpeedZoneType_Fast,  -12800, 13440, -12800, 13440 },
    { NO_VALUE, 0, 0, 0, 0            } // End of list.
};

const s_MapType g_MapTypes[16] =
{
    { 1370, "THR", 0, 0, NULL      , SpeedZones_THR },
    { -1  , "SC" , 6, 0, NULL      , SpeedZones_SC  },
    { -1  , "SU" , 6, 0, NULL      , SpeedZones_SU  },
    { 912 , "SPR", 0, 0, NULL      , SpeedZones_SP  },
    { 976 , "SPU", 0, 0, NULL      , SpeedZones_SP  },
    { 679 , "RSR", 0, 0, NULL      , SpeedZones_RSR },
    { 738 , "RSU", 0, 0, NULL      , SpeedZones_RSU },
    { 173 , "APR", 0, 0, NULL      , SpeedZones_AP  },
    { 196 , "APU", 0, 0, NULL      , SpeedZones_AP  },
    { -1  , "ER" , 6, 0, NULL      , SpeedZones_ER  },
    { -1  , "ER" , 6, 0, NULL      , SpeedZones_ER  },
    { 266 , "DR" , 0, 0, D_80024D5C, SpeedZones_DR  },
    { 265 , "DRU", 0, 0, D_80024D80, SpeedZones_DR  },
    { -1  , "HP" , 6, 0, NULL      , SpeedZones_HP  },
    { -1  , "HU" , 6, 0, NULL      , SpeedZones_HU  },
    { -1  , "XXX", 8, 0, NULL      , SpeedZones_XXX }
};
