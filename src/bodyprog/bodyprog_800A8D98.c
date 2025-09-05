#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"

s_FsImageDesc D_800A8D98 = { { 16, 0 }, 0, 0, 8, 0 };
s_FsImageDesc D_800A8DA0 = { { 44, 0 }, 0, 0, 0, 0 };

// Could also be some `s_FsImageDesc`, but the big negative numbers suggest not.
// Might be some other primitive data (`POLY`, `RGBC0`, etc.).
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

u8 g_BackgroundColor = 0x80;
u8 D_800A8E59        = 0x00;
u8 D_800A8E5A        = 0x03;
u8 D_800A8E5B        = 0x00;

DR_MODE D_800A8E5C[] =
{
    { 0x03000000, { 0xE1000240, 0x00000000 } },
    { 0x03000000, { 0xE1000240, 0x00000000 } },
};

TILE D_800A8E74[] =
{
    { 0x03000000, 0xFF, 0x00, 0x00, 0x62, 0xFEC0, 0xFF10, 0x0280, 0x01E0 },
    { 0x03000000, 0xFF, 0x00, 0x00, 0x62, 0xFEC0, 0xFF10, 0x0280, 0x01E0 },
};

s32 g_ScreenFadeProgress = 0;

DR_MODE D_800A8E98[] =
{
    { 0x03000000, { 0xE1000240, 0x00000000 } },
    { 0x03000000, { 0xE1000240, 0x00000000 } },
};

// TODO: Make a macro?
POLY_G4 D_800A8EB0[] =
{
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3A,
        0xFF60, 0xFF90,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0xFF90,
        0x0, 0x0, 0x0, 0x0,
        0xFF60, 0xFFA0,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0xFFA0,
    },
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3A,
        0xFF60, 0xFF90,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0xFF90,
        0x0, 0x0, 0x0, 0x0,
        0xFF60, 0xFFA0,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0xFFA0,
    },
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3A,
        0xFF60, 0x70,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0x70,
        0x0, 0x0, 0x0, 0x0,
        0xFF60, 0x60,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0x60,
    },
    {
        0x8000000,
        0x0, 0x0, 0x0, 0x3A,
        0xFF60, 0x70,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0x70,
        0x0, 0x0, 0x0, 0x0,
        0xFF60, 0x60,
        0x0, 0x0, 0x0, 0x0,
        0xa0, 0x60,
    },
};

s32 D_800A8F40 = 0x00000000;

VC_ROAD_DATA vcNullRoadArray[] =
{
    {
        .lim_sw_0          = { Q7_8(-30.0f), Q7_8(30.0f), Q7_8(-30.0f), Q7_8(30.0f) },
        .lim_rd_8          = { Q7_8(-30.0f), Q7_8(30.0f), Q7_8(-30.0f), Q7_8(30.0f) },
        .flags_10          = VC_RD_NOFLAG,
        .area_size_type_11 = VC_AREA_WIDE,
        .rd_type_11        = VC_RD_TYPE_ROAD,
        .mv_y_type_11      = VC_MV_SELF_VIEW,
        .lim_rd_max_hy_12  = 96,
        .lim_rd_min_hy_13  = -96,
        .ofs_watch_hy_14   = 8,
        .field_15          = 1,
        .cam_mv_type_14    = VC_MV_CHASE,
        .fix_ang_x_16      = FP_ANGLE_PACKED(0.0f),
        .fix_ang_y_17      = FP_ANGLE_PACKED(0.0f)
    },
    {
        .lim_sw_0          = { Q7_8(0.0f), Q7_8(0.0f), Q7_8(0.0f), Q7_8(0.0f) },
        .lim_rd_8          = { Q7_8(0.0f), Q7_8(0.0f), Q7_8(0.0f), Q7_8(0.0f) },
        .flags_10          = VC_RD_END_DATA_F,
        .area_size_type_11 = VC_AREA_TINY,
        .rd_type_11        = VC_RD_TYPE_ROAD,
        .mv_y_type_11      = VC_MV_CHASE,
        .lim_rd_max_hy_12  = 0,
        .lim_rd_min_hy_13  = 0,
        .ofs_watch_hy_14   = 0,
        .field_15          = 0,
        .cam_mv_type_14    = VC_MV_CHASE,
        .fix_ang_x_16      = FP_ANGLE_PACKED(0.0f),
        .fix_ang_y_17      = FP_ANGLE_PACKED(0.0f)
    },
};

GsOT g_ObjectTable0[] =
{
    { 0x0B, (GsOT_TAG*)0x800B5CC8, 0, 0, 0 },
    { 0x0B, (GsOT_TAG*)0x800B7CC8, 0, 0, 0 },
};

GsOT D_800A8F9C[] =
{
    { 0x09, (GsOT_TAG*)0x801E2600, 0, 0, 0 },
    { 0x09, (GsOT_TAG*)0x801E2E00, 0, 0, 0 },
};

GsOT g_ObjectTable1[] =
{
    { 0x04, (GsOT_TAG*)0x800B5C40, 0, 0, 0 },
    { 0x04, (GsOT_TAG*)0x800B5C80, 0, 0, 0 },
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
/* Not sure if these are really `s_FsImageDesc`. Seems lausible but not sure about negative values here. */
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
    { -1,  0,    0,        0,  0, NULL,        0,  0,   0 },
    { 58,  1422, 1423,     64, 1, NULL,        0, -179, 0 },
    { 24,  1381, 1449,     64, 2, &D_800A90B4, 0, -153, 0 },
    { 24,  1375, 1376,     64, 2, &D_800A90B4, 0, -153, 0 },
    { 41,  1414, 1415,     64, 2, NULL,        0, -179, 0 },
    { 41,  1408, 1409,     64, 2, NULL,        0, -179, 0 },
    { 33,  1394, 1395,     64, 2, NULL,        0, -128, 0 },
    { 34,  1396, 1397,     64, 2, NULL,        0, -204, 0 },
    { 34,  1398, 1399,     64, 1, NULL,        0, -204, 0 },
    { 34,  1400, 1401,     64, 1, NULL,        0, -204, 0 },
    { 158, 1454, 1455,     64, 2, NULL,        0, -153, 0 },
    { 35,  1402, 1403,     64, 2, NULL,        0, -128, 0 },
    { 126, 1426, 1427,     76, 2, &D_800A90A4, 1, -204, 0 },
    { 32,  1392, 1393,     0,  2, NULL,        0, -230, 0 },
    { 51,  1418, 1419,     0,  2, NULL,        0, -179, 0 },
    { 144, 1442, 1439,     0,  1, NULL,        0, -588, 0 },
    { 151, 1445, 1446,     64, 2, NULL,        0, -230, 0 },
    { 43,  1416, NO_VALUE, 64, 2, NULL,        0, -230, 0 },
    { 151, 1447, 1448,     64, 2, NULL,        0, -230, 0 },
    { 43,  1416, NO_VALUE, 64, 2, NULL,        0, -230, 0 },
    { 170, 1465, 1464,     0,  2, NULL,        0, -179, 0 },
    { 152, 1450, 1451,     0,  2, NULL,        0, -179, 0 },
    { 26,  1384, 1385,     0,  1, NULL,        2,  0,   0 },
    { 140, 1435, 1436,     0,  0, NULL,        2,  0,   0 },
    { 143, 1440, 1441,     64, 2, NULL,        0, -345, 0 },
    { 38,  1406, 1407,     64, 2, NULL,        0, -128, 0 },
    { 154, 1452, 1453,     76, 2, NULL,        0, -128, 0 },
    { 155, 1452, 1453,     64, 2, NULL,        0, -128, 0 },
    { 162, 1458, 1459,     64, 2, NULL,        0, -128, 0 },
    { 30,  1390, 1391,     64, 2, NULL,        0, -128, 0 },
    { 36,  1404, 1405,     64, 1, NULL,        0, -128, 0 },
    { 37,  1404, 1405,     64, 1, NULL,        0, -128, 0 },
    { 138, 1430, 1431,     64, 2, NULL,        0, -128, 0 },
    { 25,  1382, 1383,     64, 2, NULL,        0, -128, 0 },
    { 19,  1371, 1372,     64, 1, NULL,        0, -128, 0 },
    { 163, 1460, 1461,     64, 1, NULL,        0, -128, 0 },
    { 140, 1435, 1436,     64, 1, NULL,        0, -128, 0 },
    { 20,  1373, 1374,     64, 1, NULL,        0, -128, 0 },
    { 127, 1428, 1429,     64, 1, NULL,        0, -128, 0 },
    { 128, 1428, 1429,     64, 1, NULL,        0, -128, 0 },
    { 22,  1377, 1378,     64, 1, NULL,        0,  0,   0 },
    { 135, 1432, 1433,     64, 1, NULL,        0,  0,   0 },
    { 40,  1412, 1413,     64, 1, NULL,        0,  0,   0 },
    { 125, 1424, 1425,     64, 1, NULL,        0,  0,   0 },
    {} // End of list?
};

s_sub_StructUnk3 D_800A93CC[] =
{
    {
        .field_0  = { .field_0 = 0xFF00 },
        .field_4  = 0,
        .field_6  = 4710,
        .field_8  = 4096,
        .field_A  = 4096,
        .field_C  = 4096,
        .field_E  = 0,
        .unk_F    = 0,
        .field_10 = 409600,
        .fogColor_14 = { 60, 60, 68, 0 },
        .field_18 = 0,
        .field_19 = { 0, 0, 0, 0 },
        .field_1D = { 0, 0, 0, 0 },
        .field_21 = { 64, 64, 64, 0 },
        .field_25 = { 12, 12, 28, 0 },
        .unk_29   = 0,
        .unk_2A   = 0
    },
    {
        .field_0  = { .field_0 = 0xFF00 },
        .field_4  = 0,
        .field_6  = 4505,
        .field_8  = 3891,
        .field_A  = 4096,
        .field_C  = 4423,
        .field_E  = 1,
        .unk_F    = 0,
        .field_10 = 55296,
        .fogColor_14 = { 108, 100, 116, 0 },
        .field_18 = 0,
        .field_19 = { 0, 0, 0, 0 },
        .field_1D = { 0, 0, 0, 0 },
        .field_21 = { 48, 48, 48, 0 },
        .field_25 = { 14, 14, 30, 0 },
        .unk_29   = 0,
        .unk_2A   = 0
    },
    {
        .field_0  = { .field_0 = 0x2ff00 },
        .field_4  = 2457,
        .field_6  = 2457,
        .field_8  = 3686,
        .field_A  = 4096,
        .field_C  = 4300,
        .field_E  = 1,
        .unk_F    = 0,
        .field_10 = 57344,
        .fogColor_14 = { 100, 92, 108, 0 },
        .field_18 = 0,
        .field_19 = { 0, 0, 0, 0 },
        .field_1D = { 0, 0, 0, 0 },
        .field_21 = { 48, 48, 48, 0 },
        .field_25 = { 13, 13, 29, 0 },
        .unk_29   = 0,
        .unk_2A   = 0
    },
    {
        .field_0  = { .field_0 = 0x1ff16},
        .field_4  = 5324,
        .field_6  = 0,
        .field_8  = 3891,
        .field_A  = 4096,
        .field_C  = 4423,
        .field_E  = 0,
        .unk_F    = 0,
        .field_10 = 163840,
        .fogColor_14 = { 0, 0, 0, 0 },
        .field_18 = 0,
        .field_19 = { 0, 0, 0, 0 },
        .field_1D = { 0, 0, 0, 0 },
        .field_21 = { 48, 48, 48, 0 },
        .field_25 = { 12, 12, 12, 0 },
        .unk_29   = 0,
        .unk_2A   = 0
    },
    {
        .field_0  = { .field_0 = 0x1ff16},
        .field_4  = 2867,
        .field_6  = 0,
        .field_8  = 3686,
        .field_A  = 4096,
        .field_C  = 4300,
        .field_E  = 0,
        .unk_F    = 0,
        .field_10 = 163840,
        .fogColor_14 = { 0, 0, 0, 0 },
        .field_18 = 0,
        .field_19 = { 0, 0, 0, 0 },
        .field_1D = { 0, 0, 0, 0 },
        .field_21 = { 48, 48, 48, 0 },
        .field_25 = { 12, 12, 12, 0 },
        .unk_29   = 0,
        .unk_2A   = 0
    },
    {
        .field_0  = { .field_0 = 0x1FF16},
        .field_4  = 5324,
        .field_6  = 409,
        .field_8  = 3891,
        .field_A  = 4096,
        .field_C  = 4423,
        .field_E  = 3,
        .unk_F    = 0,
        .field_10 = 55296,
        .fogColor_14 = { 68, 60, 76, 0 },
        .field_18 = 1,
        .field_19 = { 24, 16, 32, 0 },
        .field_1D = { 85, 75, 75, 0 },
        .field_21 = { 32, 32, 40, 0 },
        .field_25 = { 12, 12, 28, 0 },
        .unk_29   = 0,
        .unk_2A   = 0
    },
    {
        .field_0  = { .field_0 = 0xFF07},
        .field_4  = 0,
        .field_6  = 1802,
        .field_8  = 1638,
        .field_A  = 2867,
        .field_C  = 4096,
        .field_E  = 1,
        .unk_F    = 0,
        .field_10 = 57344,
        .fogColor_14 = { 0, 0, 0, 0 },
        .field_18 = 0,
        .field_19 = { 0, 0, 0, 0 },
        .field_1D = { 0, 0, 0, 0 },
        .field_21 = { 16, 16, 24, 0 },
        .field_25 = { 8, 8, 20, 0 },
        .unk_29   = 0,
        .unk_2A   = 0
    },
    {
        .field_0  = { .field_0 = 0xFF07},
        .field_4  = 0,
        .field_6  = 1802,
        .field_8  = 1638,
        .field_A  = 2867,
        .field_C  = 4096,
        .field_E  = 1,
        .unk_F    = 0,
        .field_10 = 38092,
        .fogColor_14 = { 0, 0, 0, 0 },
        .field_18 = 0,
        .field_19 = { 0, 0, 0, 0 },
        .field_1D = { 0, 0, 0, 0 },
        .field_21 = { 16, 16, 24, 0 },
        .field_25 = { 8, 8, 20, 0 },
        .unk_29   = 0,
        .unk_2A   = 0
    }
};

s_StructUnk3 D_800A952C =
{
    .field_0 =
    {
        .field_0  = { .field_0 = 0x15006 },
        .field_4  = 1433,
        .field_6  = 1638,
        .field_8  = 2867,
        .field_A  = 3276,
        .field_C  = 4096,
        .field_E  = 1,
        .unk_F    = 0,
        .field_10 = 163840,
        .fogColor_14 = { 0, 0, 0, 0 },
        .field_18 = 0,
        .field_19 = { 0, 0, 0, 0 },
        .field_1D = { 0, 0, 0, 0 },
        .field_21 = { 64, 64, 64, 0 },
        .field_25 = { 12, 12, 12, 0 },
        .unk_29  = 0,
        .unk_2A  = 0
    },
    .field_2C = -250,
    .field_2E = 1,
    .field_30 = 0x2661CCC
};

u32 D_800A9560[] = // Unknown
{
    0x0B331000,
    0x00000999,
    0x00028000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x10204000,
    0x0C0C1800,
    0x00000000,
    0x0001920E,
    0x00000800,
    0x0CCC1000,
    0x00000999,
    0x00028000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x10182000,
    0x08081200,
    0x00000000,
    0x0001FF06,
    0x02661CCC,
    0x066614CC,
    0x00000333,
    0x00028000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x10204000,
    0x0C0C1800,
    0x00000000,
    0x0001FF16,
    0x019914CC,
    0x10000F33,
    0x00001147,
    0x00028000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x30303000,
    0x0C0C0C00,
    0x00000000,
    0x0000FF00,
    0x0C7A0000,
    0x0D990BD7,
    0x00011000,
    0x0000D800,
    0x0064545C,
    0x00000000,
    0x00000000,
    0x18101000,
    0x14080800,
    0x00000000,
    0x00013816,
    0x00CC0B33,
    0x09991199,
    0x00000A66,
    0x00028000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x30303000,
    0x0C0C0C00,
    0x00000000,
    0x0001C406,
    0x03331333,
    0x07330B33,
    0x00000733,
    0x00028000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x10204000,
    0x0C0C1800,
    0x00000000,
    0x0001FF06,
    0x00CC1666,
    0x09990D99,
    0x00000999,
    0x00028000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x10204000,
    0x0C0C1800,
    0x00000000,
    0x0000FF00,
    0x10000000,
    0x0E660F33,
    0x00010E66,
    0x00006800,
    0x0064646C,
    0x00000000,
    0x00000000,
    0x30303000,
    0x1E0E0E00,
    0x00000000,
    0x0001FF16,
    0x02662800,
    0x0B331000,
    0x00000B33,
    0x00028000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x10204000,
    0x0C0C1800,
    0x00000000,
    0x0000FF07,
    0x08CC0000,
    0x0E140800,
    0x00011400,
    0x0000F000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x18101000,
    0x14080800,
    0x00000000,
    0x0001FF16,
    0x03330CCC,
    0x10000F33,
    0x00001147,
    0x00028000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x30303000,
    0x0C0C0C00,
    0x00000000
};

s32 g_Demo_FrameCount = 0;
s32 g_UnknownFrameCounter = 0;
s32 g_PrevVBlanks = 0;
u16 D_800A9774[] =
{
   0x00A0,
   0x00A2,
   0x0000,
   0x0000,
};

void (*g_GameStateUpdateFuncs[])() =
{
    GameState_Unk0_Update,
    (void (*)())0x800C95AC, // Konami Logo.
    (void (*)())0x800C99A4, // KCET Logo.
    GameState_StartMovieIntro_Update,
    GameState_DeathLoadScreen_Update,
    GameState_MovieIntroAlternate_Update,
    GameState_MovieIntro_Update,
    GameState_MainMenu_Update,
    GameState_SaveScreen_Update,
    GameState_MovieOpening_Update,
    GameState_LoadScreen_Update,
    GameState_InGame_Update,
    GameState_MapEvent_Update,
    GameState_ExitMovie_Update,
    GameState_ItemScreens_Update,
    GameState_MapScreen_Update,
    GameState_SaveScreen_Update,
    GameState_DebugMoviePlayer_Update,
    GameState_Options_Update,
    GameState_LoadStatusScreen_Update,
    GameState_LoadMapScreen_Update,
    GameState_Unk15_Update,
};

u8 g_SlotElementSelectedIdx[MEMORY_CARD_SLOT_COUNT] = { 0, 0 };
s8 g_SelectedSaveSlotIdx = 0;
u8 D_800A97D7 = 0;
u8 D_800A97D8 = 0xFF;
s8 D_800A97D9 = 0;
s8 D_800A97DA = 0;
s8 D_800A97DB = 0;
s32 D_800A97DC = 0; /** `e_SavegameEntryType` */
s8 D_800A97E0 = 0xFF;
s8 D_800A97E1 = 0;
s8 D_800A97E2 = 0;
s8 D_800A97E3 = 0;
u32 D_800A97E4[8] = {};
u16 g_UnknownEngineCmdTable0[] =
{
    0x0000,
    0x0000,
    0x0020,
    0x0021,
    0x0022,
    0x0023,
    0x0024,
    0x0025,
    0x0026,
    0x0027,
    0x0028,
    0x0029,
    0x002A,
    0x002B,
    0x002C,
    0x002E,
    0x002F,
    0x0030,
    0x0031,
    0x0032,
    0x0033,
    0x0034,
    0x0035,
    0x0036,
    0x0037,
    0x0038,
    0x0039,
    0x003A,
    0x003B,
    0x003C,
    0x003D,
    0x003E,
    0x0040,
    0x0041,
    0x0042,
    0x0043,
    0x0044,
    0x0045,
    0x002D,
    0x0046,
    0x0047,
    0x003F,
};
u16 g_UnknownEngineCmdTable1[] =
{
    0x0000,
    0x0000,
    0x0301,
    0x0302,
    0x0303,
    0x0304,
    0x0305,
    0x0306,
    0x0307,
    0x0308,
};
s_800C37D4 D_800A986C[] =
{
    { 9,  3, 778, 0x30C030B, 0x30F030D },
    { 16, 3, 785, 0x3130312, 0x3150314 },
    { 22, 3, 791, 0x3190318, 0x31B031A },
    { 28, 3, 797, 0x31F031E, 0x3220321 },
    { 35, 3, 804, 0x3260325, 0x327030E },
};
u32 D_800A98A8 = 0x03200328;
u16 g_UnknownEngineCmdTable2[] =
{
    0x0000,
    0x00A2,
    0x00AA,
    0x00AB,
    0x00CC,
    0x00AC,
    0x00AD,
    0x00AE,
    0x00AF,
    0x00B0,
    0x00B1,
    0x00B2,
    0x00B3,
    0x00B3,
    0x00B3,
    0x00B4,
    0x00B5,
    0x00B6,
    0x00B7,
    0x00B8,
    0x00B9,
    0x00BA,
    0x00BB,
    0x00BC,
    0x00BD,
    0x00B8,
    0x00BE,
    0x00BF,
    0x00C0,
    0x00C1,
    0x00C2,
    0x00C3,
    0x00C4,
    0x00C5,
    0x00C6,
    0x00C7,
    0x00C8,
    0x00C9,
    0x00CA,
    0x00CB,
};
s8 D_800A98FC[Chara_Count] =
{
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 3 0x00 padding.
};

/* These is some 24-byte struct with data followed by 72 bytes (3 structs worth)
 * of zeros, which are also zeroed at runtime in `func_800348C0`.
 * I think it is an array of this struct.
 */
s_800A992C D_800A992C[4] =
{
    {
        .charaId0_0       = Chara_Harry,
        .charaId1_1       = Chara_Harry,
        .unk_2            = { 0, 0 },
        .animFile0_4      = FS_BUFFER_0,
        .animFile1_8      = (s_AnimFile*)FS_BUFFER_0,
        .animFileSize1_C  = 0x2E630,
        .animFileSize2_10 = 0x2E630,
        .npcCoords_14     = NULL
//extern u8 D_800A9944[]; <-- Aforementioned 72 empty bytes below.
    }, {}, {}, {}
};
s_AnimInfo D_800A998C =
{
    .updateFunc_0           = Anim_Update1,
    .field_4                = 0,
    .hasVariableTimeDelta_5 = false,
    .status_6               = ANIM_STATUS(0, false),
    .field_7                = 0,
    .timeDelta_8            = { .constTimeDelta = FP_TIME(8.0f) },
    .keyframeStartIdx_C     = 26,
    .keyframeEndIdx_E       = 44
};
u32 unknown_D_800A999C = 0x80025234;
s32 D_800A99A0 = 0;
u8 D_800A99A4[8] = { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 };
s32 g_MapMsg_CurrentIdx = 0;
s16 g_MapMsg_SelectFlashTimer = 0;
//s16 __padding = 0;
s8 g_FullscreenMapTimFileIdxs[24] =
{
    0, 0, 1, 1, 9, 12, 10, 11,
    13, 12, 10, 11, 13, 2, 3, 4,
    8, 5, 6, 7, 8, 5, 6, 7
};
s8 g_MapMarkingTimFileIdxs[56] =
{
    255, 0, 1, 1, 1, 4, 4, 4,
    4, 4, 4, 4, 4, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3,
    0, 0, 0, 0, 104, 83, 2, 128,
    92, 83, 2, 128, 80, 83, 2, 128,
    68, 83, 2, 128, 56, 83, 2, 128,
    44, 83, 2, 128, 32, 83, 2, 128
};
