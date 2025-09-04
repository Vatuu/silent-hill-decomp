#include "bodyprog/bodyprog.h"
#include "game.h"

s_GameWork* const       g_GameWorkConst = &g_GameWork;
s_Savegame* const       g_SavegamePtr   = &g_GameWork.savegame_30C;
s_ControllerData* const g_Controller0   = &g_GameWork.controllers_38[0];
s_ControllerData* const g_Controller1   = &g_GameWork.controllers_38[1];
s_GameWork* const       g_GameWorkPtr   = &g_GameWork;

const u32 D_80024D58 = 0; // Nothing references it. Might be just padding.

const static s_WaterZone WaterLightZones0[] =
{
    { 1, 8, 0xF880, 0x0500, 0xF880, 0x0280 },
    { 1, 8, 0x0000, 0x0280, 0x0000, 0x0500 },
    {}
};

const static s_WaterZone WaterLightZones1[] =
{
    { 1, 8, 0xF600, 0x0280, 0xF600, 0x0A00 },
    { 1, 8, 0xF600, 0x0A00, 0xF600, 0x0280 },
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
    { FILE_BG_THR_GLB_PLM, "THR", 0, NULL            , SpeedZones_THR },
    { NO_VALUE,            "SC" , 6, NULL            , SpeedZones_SC  },
    { NO_VALUE,            "SU" , 6, NULL            , SpeedZones_SU  },
    { FILE_BG_SPR_GLB_PLM, "SPR", 0, NULL            , SpeedZones_SP  },
    { FILE_BG_SPU_GLB_PLM, "SPU", 0, NULL            , SpeedZones_SP  },
    { FILE_BG_RSR_GLB_PLM, "RSR", 0, NULL            , SpeedZones_RSR },
    { FILE_BG_RSU_GLB_PLM, "RSU", 0, NULL            , SpeedZones_RSU },
    { FILE_BG_APR_GLB_PLM, "APR", 0, NULL            , SpeedZones_AP  },
    { FILE_BG_APU_GLB_PLM, "APU", 0, NULL            , SpeedZones_AP  },
    { NO_VALUE,            "ER" , 6, NULL            , SpeedZones_ER  },
    { NO_VALUE,            "ER" , 6, NULL            , SpeedZones_ER  },
    { FILE_BG_DR_GLB_PLM,  "DR" , 0, WaterLightZones0, SpeedZones_DR  },
    { FILE_BG_DRU_GLB_PLM, "DRU", 0, WaterLightZones1, SpeedZones_DR  },
    { NO_VALUE,            "HP" , 6, NULL            , SpeedZones_HP  },
    { NO_VALUE,            "HU" , 6, NULL            , SpeedZones_HU  },
    { NO_VALUE,            "XXX", 8, NULL            , SpeedZones_XXX }
};
