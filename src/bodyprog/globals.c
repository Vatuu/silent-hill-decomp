#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "game.h"

s_GameWork* const       g_GameWorkConst = &g_GameWork;
s_Savegame* const       g_SavegamePtr   = &g_GameWork.savegame_30C;
s_ControllerData* const g_Controller0   = &g_GameWork.controllers_38[0];
s_ControllerData* const g_Controller1   = &g_GameWork.controllers_38[1];
s_GameWork* const       g_GameWorkPtr   = &g_GameWork;

const u32 D_80024D58 = 0; // Nothing references it. Might be just padding.

const static s_WaterZone WATER_LIGHT_ZONES_0[] = {
    { true, 8, Q4(-120.0f), Q4(80.0f), Q4(-120.0f), Q4(40.0f) },
    { true, 8, Q4(0.0f),    Q4(40.0f), Q4(0.0f),    Q4(80.0f) },
    {}
};

const static s_WaterZone WATER_LIGHT_ZONES_1[] = {
    { true, 8, Q4(-160.0f), Q4(40.0f),  Q4(-160.0f), Q4(160.0f) },
    { true, 8, Q4(-160.0f), Q4(160.0f), Q4(-160.0f), Q4(40.0f)  },
    {}
};

const static s_SpeedZone SPEED_ZONES_THR[] = {
    { SpeedZoneType_Fast,   Q4(-320.0f), Q4(280.0f), Q4(-240.0f), Q4(200.0f) },
    { SpeedZoneType_Fast,   Q4(-40.0f),  Q4(40.0f),  Q4(200.0f),  Q4(240.0f) },
    { SpeedZoneType_Normal, Q4(-280.0f), Q4(-80.0f), Q4(200.0f),  Q4(400.0f) },
    { NO_VALUE,             Q4(0.0f),    Q4(0.0f),   Q4(0.0f),    Q4(0.0f)   }
};

const static s_SpeedZone SPEED_ZONES_SP[] = {
    { SpeedZoneType_Fast,   Q4(-240.0f), Q4(80.0f),  Q4(-120.0f), Q4(40.0f)  },
    { SpeedZoneType_Fast,   Q4(-40.0f),  Q4(80.0f),  Q4(40.0f),   Q4(120.0f) },
    { SpeedZoneType_Normal, Q4(-160.0f), Q4(-80.0f), Q4(80.0f),   Q4(240.0f) },
    { SpeedZoneType_Normal, Q4(80.0f),   Q4(200.0f), Q4(-120.0f), Q4(160.0f) },
    { NO_VALUE,             Q4(0.0f),    Q4(0.0f),   Q4(0.0f),    Q4(0.0f)   }
};

// 2 bytes of padding.

const static s_SpeedZone SPEED_ZONES_RSR[] = {
    { SpeedZoneType_Fast,   Q4(-120.0f), Q4(80.0f),   Q4(-200.0f), Q4(40.0f) },
    { SpeedZoneType_Normal, Q4(-200.0f), Q4(-120.0f), Q4(-40.0f),  Q4(0.0f)  },
    { NO_VALUE,             Q4(0.0f),    Q4(0.0f),    Q4(0.0f),    Q4(0.0f)  }
};

// 2 bytes of padding.

const static s_SpeedZone SPEED_ZONES_RSU[] = {
    { SpeedZoneType_Fast,   Q4(-200.0f), Q4(0.0f),   Q4(40.0f),  Q4(160.0f) },
    { SpeedZoneType_Normal, Q4(-200.0f), Q4(-80.0f), Q4(-80.0f), Q4(40.0f)  },
    { NO_VALUE,             Q4(0.0f),    Q4(0.0f),   Q4(0.0f),   Q4(0.0f)   }
};

// 2 bytes of padding.

const static s_SpeedZone SPEED_ZONES_AP[] = {
    { SpeedZoneType_Fast,   Q4(-80.0f), Q4(40.0f), Q4(-120.0f), Q4(40.0f)  },
    { SpeedZoneType_Normal, Q4(0.0f),   Q4(40.0f), Q4(80.0f),   Q4(120.0f) },
    { NO_VALUE,             Q4(0.0f),   Q4(0.0f),  Q4(0.0f),    Q4(0.0f)   }
};

// 2 bytes of padding.

const static s_SpeedZone SPEED_ZONES_DR[] = {
    { SpeedZoneType_Normal, Q4(-800.0f), Q4(840.0f), Q4(-800.0f), Q4(840.0f) },
    { NO_VALUE,             Q4(0.0f),    Q4(0.0f),   Q4(0.0f),    Q4(0.0f)   }
};

const static s_SpeedZone SPEED_ZONES_SC[] = {
    { SpeedZoneType_Normal, Q4(-120.0f), Q4(-40.0f), Q4(40.0f),  Q4(80.0f)  },
    { SpeedZoneType_Normal, Q4(-40.0f),  Q4(0.0f),   Q4(160.0f), Q4(200.0f) },
    { SpeedZoneType_Normal, Q4(-40.0f),  Q4(0.0f),   Q4(0.0f),   Q4(40.0f)  },
    { SpeedZoneType_Normal, Q4(40.0f),   Q4(120.0f), Q4(40.0f),  Q4(80.0f)  },
    { SpeedZoneType_Normal, Q4(120.0f),  Q4(160.0f), Q4(0.0f),   Q4(40.0f)  },
    { SpeedZoneType_Normal, Q4(120.0f),  Q4(160.0f), Q4(160.0f), Q4(200.0f) },
    { SpeedZoneType_Normal, Q4(-80.0f),  Q4(0.0f),   Q4(-80.0f), Q4(0.0f)   },
    { SpeedZoneType_Normal, Q4(40.0f),   Q4(80.0f),  Q4(-40.0f), Q4(0.0f)   },
    { NO_VALUE,             Q4(0.0f),    Q4(0.0f),   Q4(0.0f),   Q4(0.0f)   }
};

// 2 bytes of padding.

const static s_SpeedZone SPEED_ZONES_SU[] = {
    { SpeedZoneType_Normal, Q4(-120.0f), Q4(-40.0f), Q4(40.0f),  Q4(80.0f)  },
    { SpeedZoneType_Normal, Q4(-40.0f),  Q4(0.0f),   Q4(160.0f), Q4(200.0f) },
    { SpeedZoneType_Normal, Q4(-40.0f),  Q4(0.0f),   Q4(0.0f),   Q4(40.0f)  },
    { SpeedZoneType_Normal, Q4(40.0f),   Q4(120.0f), Q4(40.0f),  Q4(80.0f)  },
    { SpeedZoneType_Normal, Q4(120.0f),  Q4(160.0f), Q4(0.0f),   Q4(40.0f)  },
    { SpeedZoneType_Normal, Q4(120.0f),  Q4(160.0f), Q4(160.0f), Q4(200.0f) },
    { SpeedZoneType_Normal, Q4(-80.0f),  Q4(0.0f),   Q4(-80.0f), Q4(0.0f)   },
    { SpeedZoneType_Normal, Q4(0.0f),    Q4(80.0f),  Q4(-40.0f), Q4(0.0f)   },
    { NO_VALUE,             Q4(0.0f),    Q4(0.0f),   Q4(0.0f),   Q4(0.0f)   }
};

// 2 bytes of padding.

const static s_SpeedZone SPEED_ZONES_HP[] = {
    { SpeedZoneType_Normal, Q4(0.0f), Q4(40.0f), Q4(120.0f), Q4(160.0f) },
    { SpeedZoneType_Normal, Q4(0.0f), Q4(40.0f), Q4(0.0f),   Q4(40.0f)  },
    { NO_VALUE,             Q4(0.0f), Q4(0.0f),  Q4(0.0f),   Q4(0.0f)   }
};

// 2 bytes of padding.

const static s_SpeedZone SPEED_ZONES_HU[] = {
    { SpeedZoneType_Normal, Q4(80.0f),   Q4(120.0f),  Q4(120.0f),  Q4(160.0f)  },
    { SpeedZoneType_Normal, Q4(0.0f),    Q4(40.0f),   Q4(0.0f),    Q4(40.0f)   },
    { SpeedZoneType_Normal, Q4(120.0f),  Q4(160.0f),  Q4(0.0f),    Q4(40.0f)   },
    { SpeedZoneType_Normal, Q4(-120.0f), Q4(0.0f),    Q4(80.0f),   Q4(120.0f)  },
    { SpeedZoneType_Normal, Q4(-80.0f),  Q4(0.0f),    Q4(-120.0f), Q4(-80.0f)  },
    { SpeedZoneType_Normal, Q4(-160.0f), Q4(-120.0f), Q4(-80.0f),  Q4(-40.0f)  },
    { SpeedZoneType_Normal, Q4(-160.0f), Q4(-120.0f), Q4(-160.0f), Q4(-120.0f) },
    { SpeedZoneType_Normal, Q4(0.0f),    Q4(120.0f),  Q4(-160.0f), Q4(-120.0f) },
    { SpeedZoneType_Normal, Q4(80.0f),   Q4(160.0f),  Q4(-120.0f), Q4(-80.0f)  },
    { SpeedZoneType_Normal, Q4(40.0f),   Q4(80.0f),   Q4(-80.0f),  Q4(-40.0f)  },
    { NO_VALUE,             Q4(0.0f),    Q4(0.0f),    Q4(0.0f),    Q4(0.0f)    }
};

// 2 bytes of padding.

const static s_SpeedZone SPEED_ZONES_ER[] = {
    { SpeedZoneType_Normal, Q4(-80.0f),  Q4(-40.0f), Q4(-40.0f),  Q4(0.0f)    },
    { SpeedZoneType_Normal, Q4(-120.0f), Q4(-40.0f), Q4(-120.0f), Q4(-80.0f)  },
    { SpeedZoneType_Normal, Q4(-120.0f), Q4(-80.0f), Q4(-160.0f), Q4(-120.0f) },
    { SpeedZoneType_Normal, Q4(160.0f),  Q4(200.0f), Q4(-40.0f),  Q4(0.0f)    },
    { SpeedZoneType_Normal, Q4(80.0f),   Q4(160.0f), Q4(-120.0f), Q4(-80.0f)  },
    { NO_VALUE,             Q4(0.0f),    Q4(0.0f),   Q4(0.0f),    Q4(0.0f)    }
};

const static s_SpeedZone SPEED_ZONES_XXX[] = {
    { SpeedZoneType_Fast, Q4(-800.0f), Q4(840.0f), Q4(-800.0f), Q4(840.0f) },
    { NO_VALUE,           Q4(0.0f),    Q4(0.0f),   Q4(0.0f),    Q4(0.0f)   }
};

const s_MapType MAP_TYPES[16] = {
    { FILE_BG_THR_GLB_PLM, "THR", MapTypeFlag_FourActiveChunks,                       NULL,                SPEED_ZONES_THR },
    { NO_VALUE,            "SC",  MapTypeFlag_TwoActiveChunks | MapTypeFlag_Interior, NULL,                SPEED_ZONES_SC  },
    { NO_VALUE,            "SU",  MapTypeFlag_TwoActiveChunks | MapTypeFlag_Interior, NULL,                SPEED_ZONES_SU  },
    { FILE_BG_SPR_GLB_PLM, "SPR", MapTypeFlag_FourActiveChunks,                       NULL,                SPEED_ZONES_SP  },
    { FILE_BG_SPU_GLB_PLM, "SPU", MapTypeFlag_FourActiveChunks,                       NULL,                SPEED_ZONES_SP  },
    { FILE_BG_RSR_GLB_PLM, "RSR", MapTypeFlag_FourActiveChunks,                       NULL,                SPEED_ZONES_RSR },
    { FILE_BG_RSU_GLB_PLM, "RSU", MapTypeFlag_FourActiveChunks,                       NULL,                SPEED_ZONES_RSU },
    { FILE_BG_APR_GLB_PLM, "APR", MapTypeFlag_FourActiveChunks,                       NULL,                SPEED_ZONES_AP  },
    { FILE_BG_APU_GLB_PLM, "APU", MapTypeFlag_FourActiveChunks,                       NULL,                SPEED_ZONES_AP  },
    { NO_VALUE,            "ER",  MapTypeFlag_TwoActiveChunks | MapTypeFlag_Interior, NULL,                SPEED_ZONES_ER  },
    { NO_VALUE,            "ER",  MapTypeFlag_TwoActiveChunks | MapTypeFlag_Interior, NULL,                SPEED_ZONES_ER  },
    { FILE_BG_DR_GLB_PLM,  "DR",  MapTypeFlag_FourActiveChunks,                       WATER_LIGHT_ZONES_0, SPEED_ZONES_DR  },
    { FILE_BG_DRU_GLB_PLM, "DRU", MapTypeFlag_FourActiveChunks,                       WATER_LIGHT_ZONES_1, SPEED_ZONES_DR  },
    { NO_VALUE,            "HP",  MapTypeFlag_TwoActiveChunks | MapTypeFlag_Interior, NULL,                SPEED_ZONES_HP  },
    { NO_VALUE,            "HU",  MapTypeFlag_TwoActiveChunks | MapTypeFlag_Interior, NULL,                SPEED_ZONES_HU  },
    { NO_VALUE,            "XXX", MapTypeFlag_Unk3,                                   NULL,                SPEED_ZONES_XXX }
};
