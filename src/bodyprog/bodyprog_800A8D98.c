#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"

s_FsImageDesc D_800A8D98 = { { 16 , 0   } , 0  , 0  , 8     , 0      };
s_FsImageDesc D_800A8DA0 = { { 44 , 0   } , 0  , 0  , 0     , 0      };
/* The bellow could also be some s_FsImageDesc but the big negative numbers make me think it's not.
 * Might be some other primitive data (POLY, RGBC0, etc.)
 */
u32 D_800A8DA8[] =
{
    0x00010010,
    0x84438000,
    0x88658C62,
    0x8CA798A4,
    0xA10794C8,
    0xA92794EA,
    0xA16C992C,
    0xA9F3A58F,
    0xAE37AE16,
    0x0000008C,
    0x00000000,
    0x00100004,
    0x65553300,
    0x00001136,
    0x01113310,
    0x00033111,
    0x58ACC610,
    0x00132111,
    0xFFEEFC00,
    0x0022111A,
    0xFEDEED00,
    0x0022103D,
    0xEEEFFD10,
    0x0022116D,
    0x633AA510,
    0x0022158A,
    0x001CA500,
    0x00745CA5,
    0xCBDEEC00,
    0x00BB7CDE,
    0xDEDDEC00,
    0x004B79BC,
    0xACC8A800,
    0x00049978,
    0x8BCA8500,
    0x00049976,
    0x65558100,
    0x00097777,
    0x58AAA000,
    0x000B9444,
    0x246A5000,
    0x006CB422,
    0x01300000,
    0x06DCCA31,
};

// This is propably used by setRGBC0 somewhere (D_800A8E58 is used that way and contains the same 32bit value)
u8 D_800A8E58 = 0x80;
u8 D_800A8E59 = 0x00;
u8 D_800A8E5A = 0x03;
u8 D_800A8E5B = 0x00;

DR_MODE D_800A8E5C[] =
{
    {0x03000000, {0xE1000240, 0x00000000}},
    {0x03000000, {0xE1000240, 0x00000000}},
};

TILE D_800A8E74[] =
{
    {0x03000000, 0xFF, 0x00, 0x00, 0x62, 0xFEC0, 0xFF10, 0x0280, 0x01E0},
    {0x03000000, 0xFF, 0x00, 0x00, 0x62, 0xFEC0, 0xFF10, 0x0280, 0x01E0},
};

s32 D_800A8E94 = 0x00000000;

DR_MODE D_800A8E98[] =
{
    {0x03000000, {0xE1000240, 0x00000000}},
    {0x03000000, {0xE1000240, 0x00000000}},
};

//TODO macrofy this ?
POLY_G4 D_800A8EB0[] =
{
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3a,
        0xff60, 0xff90,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0xff90,
        0x0, 0x0, 0x0, 0x0,
        0xff60, 0xffa0,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0xffa0,
    },
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3a,
        0xff60, 0xff90,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0xff90,
        0x0, 0x0, 0x0, 0x0,
        0xff60, 0xffa0,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0xffa0,
    },
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3a,
        0xff60, 0x70,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0x70,
        0x0, 0x0, 0x0, 0x0,
        0xff60, 0x60,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0x60,
    },
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3a,
        0xff60, 0x70,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0x70,
        0x0, 0x0, 0x0, 0x0,
        0xff60, 0x60,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0x60,
    },
};

s32 D_800A8F40 = 0x00000000;

VC_ROAD_DATA vcNullRoadArray[] =
{
    {
        .lim_sw_0          = {Q7_8(-30.0f), Q7_8(30.0f), Q7_8(-30.0f), Q7_8(30.0f)},
        .lim_rd_8          = {Q7_8(-30.0f), Q7_8(30.0f), Q7_8(-30.0f), Q7_8(30.0f)},
        .flags_10          = 0,
        .area_size_type_11 = 2,
        .rd_type_11        = 0,
        .mv_y_type_11      = 3,
        .lim_rd_max_hy_12  = 96,
        .lim_rd_min_hy_13  = -96,
        .ofs_watch_hy_14   = 8,
        .field_15          = 1,
        .cam_mv_type_14    = 0,
        .fix_ang_x_16      = 0,
        .fix_ang_y_17      = 0,
    },
    {
        .lim_sw_0          = {Q7_8(0.0f), Q7_8(0.0f), Q7_8(0.0f), Q7_8(0.0f)},
        .lim_rd_8          = {Q7_8(0.0f), Q7_8(0.0f), Q7_8(0.0f), Q7_8(0.0f)},
        .flags_10          = 1,
        .area_size_type_11 = 0,
        .rd_type_11        = 0,
        .mv_y_type_11      = 0,
        .lim_rd_max_hy_12  = 0,
        .lim_rd_min_hy_13  = 0,
        .ofs_watch_hy_14   = 0,
        .field_15          = 0,
        .cam_mv_type_14    = 0,
        .fix_ang_x_16      = 0,
        .fix_ang_y_17      = 0,
    },
};

GsOT g_ObjectTable0[] =
{
    {0x0B, (GsOT_TAG*)0x800B5CC8, 0, 0, 0},
    {0x0B, (GsOT_TAG*)0x800B7CC8, 0, 0, 0},
};

GsOT D_800A8F9C[] =
{
    {0x09, (GsOT_TAG*)0x801E2600, 0, 0, 0},
    {0x09, (GsOT_TAG*)0x801E2E00, 0, 0, 0},
};

GsOT g_ObjectTable1[] =
{
    {0x04, (GsOT_TAG*)0x800B5C40, 0, 0, 0},
    {0x04, (GsOT_TAG*)0x800B5C80, 0, 0, 0},
};

q19_12 g_DeltaTime1      = 0x00000044;
s32    g_IntervalVBlanks = 1;

s_FsImageDesc g_Font16AtlasImg             = { { 0,   16  }, 0,    240, 304, 511 };
s_FsImageDesc g_KonamiLogoImg              = { { 0,   12  }, 0,    0,   0,   0   };
s_FsImageDesc g_KcetLogoImg                = { { 0,   14  }, 0,    0,   0,   1   };
s_FsImageDesc D_800A900C                   = { { 0,   28  }, 0,    0,   0,   2   };
s_FsImageDesc g_TitleImg                   = { { 1,   13  }, 32,   0,   224, 15  };
s_FsImageDesc g_MapImg                     = { { 1,   5   }, 0,    16,  224, 15  };
s_FsImageDesc g_MapMarkerAtlasImg          = { { 0,   7   }, 32,   0,   480, 255 };
s_FsImageDesc g_ItemInspectionImg          = { { 1,   5   }, 0,    16,  224, 14  };
s_FsImageDesc D_800A9034                   = { { 0,   5   }, 0,    16,  288, 0   };
s_FsImageDesc g_ControllerButtonAtlasImg   = { { 0,   7   }, 32,   0,   464, 0   };
s_FsImageDesc g_BrightnessScreenImg0       = { { 0,   28  }, 0,    16,  288, 0   };
s_FsImageDesc g_BrightnessScreenImg1       = { { 0,   30  }, 0,    16,  288, 0   };
s_FsImageDesc g_DeathTipImg                = { { 0,   30  }, 0,    16,  288, 0   };
s_FsImageDesc g_HealthPortraitImg          = { { 1,   31  }, 12,   103, 224, 13  };
s_FsImageDesc g_InventoryKeyItemTextureImg = { { 0,   14  }, 0,    0,   160, 0   };
s_FsImageDesc g_FirstAidKitItemTextureImg  = { { 0,   15  }, 0,    0,   176, 0   };
s_FsImageDesc D_800A9074                   = { { 0,   13  }, 32,   0,   240, 0   };
s_FsImageDesc D_800A907C                   = { { 0,   5   }, 0,    128, 240, 8   };
s_FsImageDesc D_800A9084                   = { { 0,   11  }, 0,    0,   304, 0   };
s_FsImageDesc D_800A908C                   = { { 0,   13  }, 0,    0,   224, 0   };
s_FsImageDesc D_800A9094                   = { { 0,   13  }, 0,    128, 224, 8   };
s_FsImageDesc g_Font24AtlasImg             = { { 0,   31  }, 0,    0,   960, 496 };
/* Not sure if these are really s_FsImageDesc. Seems plausible but not sure about negative values here */
s_FsImageDesc D_800A90A4                   = { { 0,   0   }, 35,   0,   35,  3   };
s_FsImageDesc D_800A90AC                   = { { 0,   0   }, 0,    0,   0,  -1   };
s_FsImageDesc D_800A90B4                   = { { 0,   0   }, 15,   0,  -53,  10  };
s_FsImageDesc D_800A90BC                   = { { 0,   0   }, 76,   0,   140, 2   };
s_FsImageDesc D_800A90C4                   = { { 168, 0   }, 246,  255, 7,   13  };
s_FsImageDesc D_800A90CC                   = { { 153, 0   }, 94,   0,   35,  13  };
s_FsImageDesc D_800A90D4                   = { { 205, 255 }, 122,  0,   56,  12  };
s_FsImageDesc D_800A90DC                   = { { 168, 0   }, 246,  255,-7,   15  };
s_FsImageDesc D_800A90E4                   = { { 153, 0   }, 94,   0,  -38,  15  };
s_FsImageDesc D_800A90EC                   = { { 51,  0   }, 125,  0,  -56,  14  };
s_FsImageDesc D_800A90F4                   = { { 0,   0   }, 0,    0,   0,   -1  };

s_CharaFileInfo g_Chara_FileInfo[] =
{
    { -1,   0,    0,    0,   0, NULL,        0,  0,   0 },
    { 58,   1422, 1423, 64,  1, NULL,        0, -179, 0 },
    { 24,   1381, 1449, 64,  2, &D_800A90B4, 0, -153, 0 },
    { 24,   1375, 1376, 64,  2, &D_800A90B4, 0, -153, 0 },
    { 41,   1414, 1415, 64,  2, NULL,        0, -179, 0 },
    { 41,   1408, 1409, 64,  2, NULL,        0, -179, 0 },
    { 33,   1394, 1395, 64,  2, NULL,        0, -128, 0 },
    { 34,   1396, 1397, 64,  2, NULL,        0, -204, 0 },
    { 34,   1398, 1399, 64,  1, NULL,        0, -204, 0 },
    { 34,   1400, 1401, 64,  1, NULL,        0, -204, 0 },
    { 158,  1454, 1455, 64,  2, NULL,        0, -153, 0 },
    { 35,   1402, 1403, 64,  2, NULL,        0, -128, 0 },
    { 126,  1426, 1427, 76,  2, &D_800A90A4, 1, -204, 0 },
    { 32,   1392, 1393, 0,   2, NULL,        0, -230, 0 },
    { 51,   1418, 1419, 0,   2, NULL,        0, -179, 0 },
    { 144,  1442, 1439, 0,   1, NULL,        0, -588, 0 },
    { 151,  1445, 1446, 64,  2, NULL,        0, -230, 0 },
    { 43,   1416, -1,   64,  2, NULL,        0, -230, 0 },
    { 151,  1447, 1448, 64,  2, NULL,        0, -230, 0 },
    { 43,   1416, -1,   64,  2, NULL,        0, -230, 0 },
    { 170,  1465, 1464, 0,   2, NULL,        0, -179, 0 },
    { 152,  1450, 1451, 0,   2, NULL,        0, -179, 0 },
    { 26,   1384, 1385, 0,   1, NULL,        2,  0,   0 },
    { 140,  1435, 1436, 0,   0, NULL,        2,  0,   0 },
    { 143,  1440, 1441, 64,  2, NULL,        0, -345, 0 },
    { 38,   1406, 1407, 64,  2, NULL,        0, -128, 0 },
    { 154,  1452, 1453, 76,  2, NULL,        0, -128, 0 },
    { 155,  1452, 1453, 64,  2, NULL,        0, -128, 0 },
    { 162,  1458, 1459, 64,  2, NULL,        0, -128, 0 },
    { 30,   1390, 1391, 64,  2, NULL,        0, -128, 0 },
    { 36,   1404, 1405, 64,  1, NULL,        0, -128, 0 },
    { 37,   1404, 1405, 64,  1, NULL,        0, -128, 0 },
    { 138,  1430, 1431, 64,  2, NULL,        0, -128, 0 },
    { 25,   1382, 1383, 64,  2, NULL,        0, -128, 0 },
    { 19,   1371, 1372, 64,  1, NULL,        0, -128, 0 },
    { 163,  1460, 1461, 64,  1, NULL,        0, -128, 0 },
    { 140,  1435, 1436, 64,  1, NULL,        0, -128, 0 },
    { 20,   1373, 1374, 64,  1, NULL,        0, -128, 0 },
    { 127,  1428, 1429, 64,  1, NULL,        0, -128, 0 },
    { 128,  1428, 1429, 64,  1, NULL,        0, -128, 0 },
    { 22,   1377, 1378, 64,  1, NULL,        0,  0,   0 },
    { 135,  1432, 1433, 64,  1, NULL,        0,  0,   0 },
    { 40,   1412, 1413, 64,  1, NULL,        0,  0,   0 },
    { 125,  1424, 1425, 64,  1, NULL,        0,  0,   0 },
    { 0,    0,    0,    0,   0, NULL,        0,  0,   0 },
};

s_sub_StructUnk3 D_800A93CC[] =
{
    {
        .field_0  = {.field_0 = 0xff00},
        .field_4  = 0,
        .field_6  = 4710,
        .field_8  = 4096,
        .field_A  = 4096,
        .field_C  = 4096,
        .field_E  = 0,
        .unk_F    = 0,
        .field_10 = 409600,
        .field_14 = {.vec_0 = {60, 60, 68, 0}},
        .field_18 = {.vec_0 = {0, 0, 0, 0}},
        .field_1C = {.vec_0 = {0, 0, 0, 0}},
        .field_20 = {.vec_0 = {0, 64, 64, 64}},
        .field_24 = {.vec_0 = {0, 12, 12, 28}},
        .unk_28   = 0,
        .unk_2A   = 0,
    },
    {
        .field_0  = {.field_0 = 0xff00},
        .field_4  = 0,
        .field_6  = 4505,
        .field_8  = 3891,
        .field_A  = 4096,
        .field_C  = 4423,
        .field_E  = 1,
        .unk_F    = 0,
        .field_10 = 55296,
        .field_14 = {.vec_0 = {108, 100, 116, 0}},
        .field_18 = {.vec_0 = {0, 0, 0, 0}},
        .field_1C = {.vec_0 = {0, 0, 0, 0}},
        .field_20 = {.vec_0 = {0, 48, 48, 48}},
        .field_24 = {.vec_0 = {0, 14, 14, 30}},
        .unk_28   = 0,
        .unk_2A   = 0,
    },
    {
        .field_0  = {.field_0 = 0x2ff00},
        .field_4  = 2457,
        .field_6  = 2457,
        .field_8  = 3686,
        .field_A  = 4096,
        .field_C  = 4300,
        .field_E  = 1,
        .unk_F    = 0,
        .field_10 = 57344,
        .field_14 = {.vec_0 = {100, 92, 108, 0}},
        .field_18 = {.vec_0 = {0, 0, 0, 0}},
        .field_1C = {.vec_0 = {0, 0, 0, 0}},
        .field_20 = {.vec_0 = {0, 48, 48, 48}},
        .field_24 = {.vec_0 = {0, 13, 13, 29}},
        .unk_28   = 0,
        .unk_2A   = 0,
    },
    {
        .field_0  = {.field_0 = 0x1ff16},
        .field_4  = 5324,
        .field_6  = 0,
        .field_8  = 3891,
        .field_A  = 4096,
        .field_C  = 4423,
        .field_E  = 0,
        .unk_F    = 0,
        .field_10 = 163840,
        .field_14 = {.vec_0 = {0, 0, 0, 0}},
        .field_18 = {.vec_0 = {0, 0, 0, 0}},
        .field_1C = {.vec_0 = {0, 0, 0, 0}},
        .field_20 = {.vec_0 = {0, 48, 48, 48}},
        .field_24 = {.vec_0 = {0, 12, 12, 12}},
        .unk_28   = 0,
        .unk_2A   = 0,
    },
    {
        .field_0  = {.field_0 = 0x1ff16},
        .field_4  = 2867,
        .field_6  = 0,
        .field_8  = 3686,
        .field_A  = 4096,
        .field_C  = 4300,
        .field_E  = 0,
        .unk_F    = 0,
        .field_10 = 163840,
        .field_14 = {.vec_0 = {0, 0, 0, 0}},
        .field_18 = {.vec_0 = {0, 0, 0, 0}},
        .field_1C = {.vec_0 = {0, 0, 0, 0}},
        .field_20 = {.vec_0 = {0, 48, 48, 48}},
        .field_24 = {.vec_0 = {0, 12, 12, 12}},
        .unk_28   = 0,
        .unk_2A   = 0,
    },
    {
        .field_0  = {.field_0 = 0x1ff16},
        .field_4  = 5324,
        .field_6  = 409,
        .field_8  = 3891,
        .field_A  = 4096,
        .field_C  = 4423,
        .field_E  = 3,
        .unk_F    = 0,
        .field_10 = 55296,
        .field_14 = {.vec_0 = {68, 60, 76, 0}},
        .field_18 = {.vec_0 = {1, 24, 16, 32}},
        .field_1C = {.vec_0 = {0, 85, 75, 75}},
        .field_20 = {.vec_0 = {0, 32, 32, 40}},
        .field_24 = {.vec_0 = {0, 12, 12, 28}},
        .unk_28   = 0,
        .unk_2A   = 0,
    },
    {
        .field_0  = {.field_0 = 0xff07},
        .field_4  = 0,
        .field_6  = 1802,
        .field_8  = 1638,
        .field_A  = 2867,
        .field_C  = 4096,
        .field_E  = 1,
        .unk_F    = 0,
        .field_10 = 57344,
        .field_14 = {.vec_0 = {0, 0, 0, 0}},
        .field_18 = {.vec_0 = {0, 0, 0, 0}},
        .field_1C = {.vec_0 = {0, 0, 0, 0}},
        .field_20 = {.vec_0 = {0, 16, 16, 24}},
        .field_24 = {.vec_0 = {0, 8, 8, 20}},
        .unk_28   = 0,
        .unk_2A   = 0,
    },
    {
        .field_0  = {.field_0 = 0xff07},
        .field_4  = 0,
        .field_6  = 1802,
        .field_8  = 1638,
        .field_A  = 2867,
        .field_C  = 4096,
        .field_E  = 1,
        .unk_F    = 0,
        .field_10 = 38092,
        .field_14 = {.vec_0 = {0, 0, 0, 0}},
        .field_18 = {.vec_0 = {0, 0, 0, 0}},
        .field_1C = {.vec_0 = {0, 0, 0, 0}},
        .field_20 = {.vec_0 = {0, 16, 16, 24}},
        .field_24 = {.vec_0 = {0, 8, 8, 20}},
        .unk_28   = 0,
        .unk_2A   = 0,
    }
};

