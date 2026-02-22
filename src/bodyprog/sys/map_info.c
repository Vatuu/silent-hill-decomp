#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "game.h"

s_MapEffectsInfo g_MapEffectsPresets[21] = {
    {
        .field_0        = { .field_0 = 0xFF00 },
        .field_4        = Q12(0.0f),
        .field_6        = Q12(1.15f),
        .worldTintR_8   = Q12(1.0f),
        .worldTintG_A   = Q12(1.0f),
        .worldTintB_C   = Q12(1.0f),
        .field_E        = 0,
        .unk_F          = 0,
        .fogDistance_10 = Q12(100.0f),
        .fogColor_14    = { 60, 60, 68, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 64, 64, 64, 0 },
        .field_25       = { 12, 12, 28, 0 },
        .unk_29         = 0,
        .unk_2A         = 0
    },
    {
        .field_0        = { .field_0 = 0xFF00 },
        .field_4        = Q12(0.0f),
        .field_6        = Q12(1.1f),
        .worldTintR_8   = Q12(0.95f),
        .worldTintG_A   = Q12(1.0f),
        .worldTintB_C   = Q12(1.08f),
        .field_E        = 1,
        .unk_F          = 0,
        .fogDistance_10 = Q12(13.5f),
        .fogColor_14    = { 108, 100, 116, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 48, 48, 48, 0 },
        .field_25       = { 14, 14, 30, 0 },
        .unk_29         = 0,
        .unk_2A         = 0
    },
    {
        .field_0        = { .field_0 = 0x2FF00 },
        .field_4        = Q12(0.6f),
        .field_6        = Q12(0.6f),
        .worldTintR_8   = Q12(0.9f),
        .worldTintG_A   = Q12(1.0f),
        .worldTintB_C   = Q12(1.05f),
        .field_E        = 1,
        .unk_F          = 0,
        .fogDistance_10 = Q12(14.0f),
        .fogColor_14    = { 100, 92, 108, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 48, 48, 48, 0 },
        .field_25       = { 13, 13, 29, 0 },
        .unk_29         = 0,
        .unk_2A         = 0
    },
    {
        .field_0        = { .field_0 = 0x1FF16 },
        .field_4        = Q12(1.3f),
        .field_6        = Q12(0.0f),
        .worldTintR_8   = Q12(0.95f),
        .worldTintG_A   = Q12(1.0f),
        .worldTintB_C   = Q12(1.08f),
        .field_E        = 0,
        .unk_F          = 0,
        .fogDistance_10 = Q12(40.0f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 48, 48, 48, 0 },
        .field_25       = { 12, 12, 12, 0 },
        .unk_29         = 0,
        .unk_2A         = 0
    },
    {
        .field_0        = { .field_0 = 0x1FF16 },
        .field_4        = Q12(0.7f),
        .field_6        = Q12(0.0f),
        .worldTintR_8   = Q12(0.9f),
        .worldTintG_A   = Q12(1.0f),
        .worldTintB_C   = Q12(1.05f),
        .field_E        = 0,
        .unk_F          = 0,
        .fogDistance_10 = Q12(40.0f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 48, 48, 48, 0 },
        .field_25       = { 12, 12, 12, 0 },
        .unk_29         = 0,
        .unk_2A         = 0
    },
    {
        .field_0        = { .field_0 = 0x1FF16 },
        .field_4        = Q12(1.3f),
        .field_6        = Q12(0.1f),
        .worldTintR_8   = Q12(0.95f),
        .worldTintG_A   = Q12(1.0f),
        .worldTintB_C   = Q12(1.08f),
        .field_E        = 3,
        .unk_F          = 0,
        .fogDistance_10 = Q12(13.5f),
        .fogColor_14    = { 68, 60, 76, 0 },
        .field_18       = 1,
        .field_19       = { 24, 16, 32, 0 },
        .screenTint_1D  = { 85, 75, 75, 0 },
        .field_21       = { 32, 32, 40, 0 },
        .field_25       = { 12, 12, 28, 0 },
        .unk_29         = 0,
        .unk_2A         = 0
    },
    {
        .field_0        = { .field_0 = 0xFF07 },
        .field_4        = Q12(0.0f),
        .field_6        = Q12(0.44f),
        .worldTintR_8   = Q12(0.4f),
        .worldTintG_A   = Q12(0.7f),
        .worldTintB_C   = Q12(1.0f),
        .field_E        = 1,
        .unk_F          = 0,
        .fogDistance_10 = Q12(14.0f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 16, 16, 24, 0 },
        .field_25       = { 8, 8, 20, 0 },
        .unk_29         = 0,
        .unk_2A         = 0
    },
    {
        .field_0        = { .field_0 = 0xFF07 },
        .field_4        = Q12(0.0f),
        .field_6        = Q12(0.44f),
        .worldTintR_8   = Q12(0.4f),
        .worldTintG_A   = Q12(0.7f),
        .worldTintB_C   = Q12(1.0f),
        .field_E        = 1,
        .unk_F          = 0,
        .fogDistance_10 = Q12(9.29987f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 16, 16, 24, 0 },
        .field_25       = { 8, 8, 20, 0 },
        .unk_29         = 0,
        .unk_2A         = 0
    },
    {
        .field_0        = { .field_0 = 0x15006 },
        .field_4        = Q12(0.35f),
        .field_6        = Q12(0.4f),
        .worldTintR_8   = Q12(0.7f),
        .worldTintG_A   = Q12(0.8f),
        .worldTintB_C   = Q12(1.0f),
        .field_E        = 1,
        .unk_F          = 0,
        .fogDistance_10 = Q12(40.0f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 64, 64, 64, 0 },
        .field_25       = { 12, 12, 12, 0 },
        .unk_29         = 0,
        .unk_2A         = 0
    },
    {
        .field_0        = { .field_0 = 130822 },
        .field_4        = Q12(1.8f),
        .field_6        = Q12(0.15f),
        .worldTintR_8   = Q12(1.0f),
        .worldTintG_A   = Q12(0.7f),
        .worldTintB_C   = Q12(0.6f),
        .field_E        = 0,
        .unk_F          = 0,
        .fogDistance_10 = Q12(40.0f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 64, 32, 16, 0 },
        .field_25       = { 24, 12, 12, 0 },
        .unk_29         = 0,
        .unk_2A         = 0,
    },
    {
        .field_0        = { .field_0 = 102926 },
        .field_4        = Q12(0.5f),
        .field_6        = Q12(0.0f),
        .worldTintR_8   = Q12(1.0f),
        .worldTintG_A   = Q12(0.8f),
        .worldTintB_C   = Q12(0.6f),
        .field_E        = 0,
        .unk_F          = 0,
        .fogDistance_10 = Q12(40.0f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 32, 24, 16, 0 },
        .field_25       = { 18, 8, 8, 0 },
        .unk_29         = 0,
        .unk_2A         = 0,
    },
    {
        .field_0        =  { .field_0 = 130822 },
        .field_4        = Q12(1.8f),
        .field_6        = Q12(0.15f),
        .worldTintR_8   = Q12(1.3f),
        .worldTintG_A   = Q12(0.4f),
        .worldTintB_C   = Q12(0.2f),
        .field_E        = 0,
        .unk_F          = 0,
        .fogDistance_10 = Q12(40.0f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 64, 32, 16, 0 },
        .field_25       = { 24, 12, 12, 0 },
        .unk_29         = 0,
        .unk_2A         = 0,
    },
    {
        .field_0        = { .field_0 = 130838 },
        .field_4        = Q12(1.3f),
        .field_6        = Q12(0.1f),
        .worldTintR_8   = Q12(0.95f),
        .worldTintG_A   = Q12(1.0f),
        .worldTintB_C   = Q12(1.08f),
        .field_E        = 0,
        .unk_F          = 0,
        .fogDistance_10 = Q12(40.0f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 48, 48, 48, 0 },
        .field_25       = { 12, 12, 12, 0 },
        .unk_29         = 0,
        .unk_2A         = 0,
    },
    {
        .field_0        = { .field_0 = 65280 },
        .field_4        = Q12(0.0f),
        .field_6        = Q12(0.78f),
        .worldTintR_8   = Q12(0.74f),
        .worldTintG_A   = Q12(0.85f),
        .worldTintB_C   = Q12(1.0f),
        .field_E        = 1,
        .unk_F          = 0,
        .fogDistance_10 = Q12(13.5f),
        .fogColor_14    = { 92, 84, 100, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 16, 16, 24, 0 },
        .field_25       = { 8, 8, 20, 0 },
        .unk_29         = 0,
        .unk_2A         = 0,
    },
    {
        .field_0        = { .field_0 = 79894 },
        .field_4        = Q12(0.7f),
        .field_6        = Q12(0.05f),
        .worldTintR_8   = Q12(1.1f),
        .worldTintG_A   = Q12(0.6f),
        .worldTintB_C   = Q12(0.65f),
        .field_E        = 0,
        .unk_F          = 0,
        .fogDistance_10 = Q12(40.0f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 48, 48, 48, 0 },
        .field_25       = { 12, 12, 12, 0 },
        .unk_29         = 0,
        .unk_2A         = 0,
    },
    {
        .field_0        = { .field_0 = 115718 },
        .field_4        = Q12(1.2f),
        .field_6        = Q12(0.2f),
        .worldTintR_8   = Q12(0.7f),
        .worldTintG_A   = Q12(0.45f),
        .worldTintB_C   = Q12(0.45f),
        .field_E        = 0,
        .unk_F          = 0,
        .fogDistance_10 = Q12(40.0f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 64, 32, 16, 0 },
        .field_25       = { 24, 12, 12, 0 },
        .unk_29         = 0,
        .unk_2A         = 0,
    },
    {
        .field_0        = { .field_0 = 130822 },
        .field_4        = Q12(1.4f),
        .field_6        = Q12(0.05f),
        .worldTintR_8   = Q12(0.85f),
        .worldTintG_A   = Q12(0.6f),
        .worldTintB_C   = Q12(0.6f),
        .field_E        = 0,
        .unk_F          = 0,
        .fogDistance_10 = Q12(40.0f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 64, 32, 16, 0 },
        .field_25       = { 24, 12, 12, 0 },
        .unk_29         = 0,
        .unk_2A         = 0,
    },
    {
        .field_0        = { .field_0 = 65280 },
        .field_4        = Q12(0.0f),
        .field_6        = Q12(1.0f),
        .worldTintR_8   = Q12(0.95f),
        .worldTintG_A   = Q12(0.9f),
        .worldTintB_C   = Q12(0.9f),
        .field_E        = 1,
        .unk_F          = 0,
        .fogDistance_10 = Q12(6.5f),
        .fogColor_14    = { 108, 100, 100, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 48, 48, 48, 0 },
        .field_25       = { 14, 14, 30, 0 },
        .unk_29         = 0,
        .unk_2A         = 0,
    },
    {
        .field_0        = { .field_0 = 130838 },
        .field_4        = Q12(2.5f),
        .field_6        = Q12(0.15f),
        .worldTintR_8   = Q12(1.0f),
        .worldTintG_A   = Q12(0.7f),
        .worldTintB_C   = Q12(0.7f),
        .field_E        = 0,
        .unk_F          = 0,
        .fogDistance_10 = Q12(40.0f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 64, 32, 16, 0 },
        .field_25       = { 24, 12, 12, 0 },
        .unk_29         = 0,
        .unk_2A         = 0,
    },
    {
        .field_0        = { .field_0 = 65287 },
        .field_4        = 0,
        .field_6        = Q12(0.55f),
        .worldTintR_8   = Q12(0.5f),
        .worldTintG_A   = Q12(0.88f),
        .worldTintB_C   = Q12(1.25f),
        .field_E        = 1,
        .unk_F          = 0,
        .fogDistance_10 = Q12(15.0f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 16, 16, 24, 0 },
        .field_25       = { 8, 8, 20, 0 },
        .unk_29         = 0,
        .unk_2A         = 0,
    },
    {
        .field_0        = { .field_0 = 130838 },
        .field_4        = Q12(0.8f),
        .field_6        = Q12(0.2f),
        .worldTintR_8   = Q12(0.95f),
        .worldTintG_A   = Q12(1.0f),
        .worldTintB_C   = Q12(1.08f),
        .field_E        = 0,
        .unk_F          = 0,
        .fogDistance_10 = Q12(40.0f),
        .fogColor_14    = { 0, 0, 0, 0 },
        .field_18       = 0,
        .field_19       = { 0, 0, 0, 0 },
        .screenTint_1D  = { 0, 0, 0, 0 },
        .field_21       = { 48, 48, 48, 0 },
        .field_25       = { 12, 12, 12, 0 },
        .unk_29         = 0,
        .unk_2A         = 0,
    }
};

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

const s_MapInfo MAP_INFOS[MapType_Count] = {
    { FILE_BG_THR_GLB_PLM, "THR", MapFlag_FourActiveChunks,                   NULL,                SPEED_ZONES_THR },
    { NO_VALUE,            "SC",  MapFlag_TwoActiveChunks | MapFlag_Interior, NULL,                SPEED_ZONES_SC  },
    { NO_VALUE,            "SU",  MapFlag_TwoActiveChunks | MapFlag_Interior, NULL,                SPEED_ZONES_SU  },
    { FILE_BG_SPR_GLB_PLM, "SPR", MapFlag_FourActiveChunks,                   NULL,                SPEED_ZONES_SP  },
    { FILE_BG_SPU_GLB_PLM, "SPU", MapFlag_FourActiveChunks,                   NULL,                SPEED_ZONES_SP  },
    { FILE_BG_RSR_GLB_PLM, "RSR", MapFlag_FourActiveChunks,                   NULL,                SPEED_ZONES_RSR },
    { FILE_BG_RSU_GLB_PLM, "RSU", MapFlag_FourActiveChunks,                   NULL,                SPEED_ZONES_RSU },
    { FILE_BG_APR_GLB_PLM, "APR", MapFlag_FourActiveChunks,                   NULL,                SPEED_ZONES_AP  },
    { FILE_BG_APU_GLB_PLM, "APU", MapFlag_FourActiveChunks,                   NULL,                SPEED_ZONES_AP  },
    { NO_VALUE,            "ER",  MapFlag_TwoActiveChunks | MapFlag_Interior, NULL,                SPEED_ZONES_ER  },
    { NO_VALUE,            "ER",  MapFlag_TwoActiveChunks | MapFlag_Interior, NULL,                SPEED_ZONES_ER  },
    { FILE_BG_DR_GLB_PLM,  "DR",  MapFlag_FourActiveChunks,                   WATER_LIGHT_ZONES_0, SPEED_ZONES_DR  },
    { FILE_BG_DRU_GLB_PLM, "DRU", MapFlag_FourActiveChunks,                   WATER_LIGHT_ZONES_1, SPEED_ZONES_DR  },
    { NO_VALUE,            "HP",  MapFlag_TwoActiveChunks | MapFlag_Interior, NULL,                SPEED_ZONES_HP  },
    { NO_VALUE,            "HU",  MapFlag_TwoActiveChunks | MapFlag_Interior, NULL,                SPEED_ZONES_HU  },
    { NO_VALUE,            "XXX", MapFlag_Unk3,                               NULL,                SPEED_ZONES_XXX }
};
