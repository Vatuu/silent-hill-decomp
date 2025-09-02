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

const s_foo_unknown D_80024D5C[] =
{
    { 0x00080001, 0x0500F880, 0x0280F880 },
    { 0x00080001, 0x02800000, 0x05000000 },
    {}
};

const s_foo_unknown D_80024D80[] =
{
    { 0x00080001, 0x0280F600, 0x0A00F600 },
    { 0x00080001, 0x0A00F600, 0x0280F600 },
    {}
};

const s_MapBounds MapBounds_80024DA4[] =
{
    { 2, -5120,  4480, -3840, 3200 },
    { 2, -640,   640,   3200, 3840 },
    { 1, -4480, -1280,  3200, 6400 },
    { NO_VALUE, 0, 0, 0, 0         } // End of list.
};

const s_MapBounds MapBounds_80024DCC[] =
{
    { 2, -3840,  1280, -1920, 640  },
    { 2, -640,   1280,  640,  1920 },
    { 1, -2560, -1280,  1280, 3840 },
    { 1,  1280,  3200, -1920, 2560 },
    { NO_VALUE, 0, 0, 0, 0         } // End of list.
};

// 2 bytes of padding.

const s_MapBounds MapBounds_80024E00[] =
{
    { 2, -1920,  1280, -3200, 640 },
    { 1, -3200, -1920, -640,  0   },
    { NO_VALUE, 0, 0, 0, 0        } // End of list.
};

// 2 bytes of padding.

const s_MapBounds MapBounds_80024E20[] =
{
    { 2, -3200,  0,     640,  2560 },
    { 1, -3200, -1280, -1280, 640  },
    { NO_VALUE, 0, 0, 0, 0         } // End of list.
};

// 2 bytes of padding.

const s_MapBounds MapBounds_80024E40[] =
{
    { 2, -1280, 640, -1920, 640  },
    { 1,  0,    640,  1280, 1920 },
    { NO_VALUE, 0, 0, 0, 0       } // End of list.
};

// 2 bytes of padding.

const s_MapBounds MapBounds_80024E60[] =
{
    { 1, -12800, 13440, -12800, 13440 },
    { NO_VALUE, 0, 0, 0, 0            } // End of list.
};

const s_MapBounds MapBounds_80024E74[] =
{
    { 1, -1920, -640,   640,  1280 },
    { 1, -640,   0,     2560, 3200 },
    { 1, -640,   0,     0,    640  },
    { 1,  640,   1920,  640,  1280 },
    { 1,  1920,  2560,  0,    640  },
    { 1,  1920,  2560,  2560, 3200 },
    { 1, -1280,  0,    -1280, 0    },
    { 1,  640,   1280, -640,  0    },
    { NO_VALUE, 0, 0, 0, 0         } // End of list.
};

// 2 bytes of padding.

const s_MapBounds MapBounds_80024ED0[] =
{
    { 1, -1920, -640,   640,  1280 },
    { 1, -640,   0,     2560, 3200 },
    { 1, -640,   0,     0,    640  },
    { 1,  640,   1920,  640,  1280 },
    { 1,  1920,  2560,  0,    640  },
    { 1,  1920,  2560,  2560, 3200 },
    { 1, -1280,  0,    -1280, 0    },
    { 1,  0,     1280, -640,  0    },
    { NO_VALUE, 0, 0, 0, 0         } // End of list.
};

// 2 bytes of padding.

const s_MapBounds MapBounds_80024F2C[] =
{
    { 1, 0, 640, 1920, 2560 },
    { 1, 0, 640, 0,    640  },
    { NO_VALUE, 0, 0, 0, 0  } // End of list.
};

// 2 bytes of padding.

const s_MapBounds MapBounds_80024F4C[] =
{
    { 1,  1280,  1920,  1920,  2560 },
    { 1,  0,     640,   0,     640  },
    { 1,  1920,  2560,  0,     640  },
    { 1, -1920,  0,     1280,  1920 },
    { 1, -1280,  0,    -1920, -1280 },
    { 1, -2560, -1920, -1280, -640  },
    { 1, -2560, -1920, -2560, -1920 },
    { 1,  0,     1920, -2560, -1920 },
    { 1,  1280,  2560, -1920, -1280 },
    { 1,  640,   1280, -1280, -640  },
    { NO_VALUE, 0, 0, 0, 0          } // End of list.
};

// 2 bytes of padding.

const s_MapBounds MapBounds_80024FBC[] =
{
    { 1, -1280, -640,  -640,   0    },
    { 1, -1920, -640,  -1920, -1280 },
    { 1, -1920, -1280, -2560, -1920 },
    { 1, 2560,   3200, -640,   0    },
    { 1, 1280,   2560, -1920, -1280 },
    { NO_VALUE, 0, 0, 0, 0          } // End of list.
};

const s_MapBounds MapBounds_80024FF8[] =
{
    { 2, -12800, 13440, -12800, 13440 },
    { NO_VALUE, 0, 0, 0, 0            } // End of list.
};
