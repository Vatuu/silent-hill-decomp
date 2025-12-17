#include "game.h"

#include <psyq/libcd.h>
#include <psyq/libetc.h>
#include <psyq/libspu.h>

// Must define before `sound_system.h`. Additionally, this array is only used in this file.
static CdlLOC D_800C15E8[2];

#include "bodyprog/bodyprog.h"
#include "bodyprog/libsd.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

const s32 rodataPad_80025BF4 = 0;

s_800C15F0 D_800C15F0[4]; // Not required to be static, but it's only used in this file.

u16 D_800C15F8[24];

s16 D_800C1628[24];

s_Sd_AudioWork g_Sd_AudioWork;

s_AudioStreamingStates g_Sd_AudioStreamingStates;

s32 bssPad_800C1674;

void SD_Call(u32 cmd) // 0x80045A7C
{
    // Execute sound command based on category.
    switch ((cmd >> 8) & 0xFF)
    {
        // Sound effect management and VAB + KDT file loading. Range [0, 255].
        case 0:
            SD_BranchCTRL(cmd);
            return;

        // Related to music. Range [300, 1279].
        case 3:
        case 4:
            func_80046A24(cmd);
            return;

        // Play SFX. Range [1280, 1791].
        case 5:
        case 6:
            Sd_PlaySfx(cmd, 0, 0);
            return;

        // Unknown. Range [1792, 2303].
        case 7:
        case 8:
            func_8004692C(cmd - 0x200);
            return;

        // Unknown. Range [2816, 3327].
        case 11:
        case 12:
            Sd_LastVoiceKeyOff();
            return;

        // Play XA audio files (voice lines). Range [4096, 5887].
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
            Sd_XaAudioPlayTaskAdd(cmd);
    }
}

u8 Sd_AudioStreamingCheck(void) // 0x80045B28
{
    u8 var;

    var = 1;
    if (g_Sd_AudioWork.xaAudioIdx_4 != 0)
    {
        return var;
    }

    var = 2;
    if (!g_Sd_AudioWork.isAudioLoading_15)
    {
        if (g_Sd_AudioStreamingStates.xaPreLoadState_3 != 0)
        {
            D_800C1688.field_8 = VSync(SyncMode_Count);
            D_800C1688.field_4 = 0;
            return 3;
        }

        if (D_800C37DC == false)
        {
            if (g_Sd_CurrentTask == 0)
            {
                return 0;
            }

            var = 5;
            return var;
        }

        var = 4;
        return var;
    }

    return var;
}

u16 func_80045BC8(void) // 0x80045BC8
{
    return g_Sd_AudioWork.field_E;
}

void SD_BranchCTRL(u16 task) // 0x80045BD8
{
    switch (task)
    {
        case 1: // Set audio to mono.
            Sd_AudioSystemSet(false);
            break;

        case 2: // Set audio to stereo.
            Sd_AudioSystemSet(true);
            break;

        case 16:
            Sd_AllVoicesKeyOff();
            Sd_LastVoiceKeyOff();
            break;

        case 17:
            Sd_AllVoicesKeyOffVWithRROff();
            Sd_LastVoiceKeyOff();
            break;

        case 18:
            Sd_StopBgmTaskAdd();
            break;

        case 21:
            Sd_AllVoicesKeyOffVWithRROff();

        case 20:
            Sd_AllVoicesKeyOff();
            Sd_LastVoiceKeyOff();
            Sd_StopBgmTaskAdd();

        case 19:
            Sd_XaAudioStopTaskAdd();
            break;

        case 22: // Background music fade speed. Rarely used.
            g_Sd_AudioWork.bgmFadeSpeed_14 = 1;

        default:
            break;

        case 23: // Background music fade speed. Rarely used.
            g_Sd_AudioWork.bgmFadeSpeed_14 = 2;
            break;

        case 3:
            g_Sd_AudioWork.muteGame_17 = true;
            break;

        case 4:
            g_Sd_AudioWork.muteGame_17 = false;
            break;
    }

    // Load VAB audio.
    if (task >= 160 && task < 245)
    {
        Sd_VabLoad_TaskAdd(task);
    }

    // Load KDT song file and VAB music samples.
    // Passes command to previous conditional to load VAB audio.
    if (task >= 32 && task < 72)
    {
        Sd_KdtLoad_TaskAdd(task);
    }
}

void Sd_AudioSystemSet(u8 isStereo) // 0x80045D28
{
    CdlATV vol;

    switch (isStereo)
    {
        case false:
            SdSetMono();

            // SPU (L).
            vol.val0 =
            vol.val2 = 79;

            // SPU (R).
            vol.val1 =
            vol.val3 = 79;

            CdMix(&vol);

            g_SDVolConfig.volumeSe_4           = 127;
            g_Sd_AudioWork.isStereoEnabled_12 = false;
            return;

        case true:
            SdSetStereo();

            // SPU (L).
            vol.val0 =
            vol.val2 = 127;

            // SPU (R).
            vol.val1 =
            vol.val3 = 0;
            CdMix(&vol);

            g_SDVolConfig.volumeSe_4           = 127;
            g_Sd_AudioWork.isStereoEnabled_12 = true;
            return;
    }
}

void SD_Init(void) // 0x80045DD4
{
    SdInit();
    SdSetTickMode(1);
    Sd_AudioSystemSet(true);
    SdSetReservedVoice(24);
    SdStart();
    SdSetTableSize(&D_800C16C8, 16, 3);

    g_SDVolConfig.globalVolumeSe_C  = OPT_SOUND_VOLUME_MAX - 1;
    g_SDVolConfig.globalVolumeBgm_D = OPT_SOUND_VOLUME_MAX - 1;
    g_SDVolConfig.globalVolumeXa_E  = OPT_SOUND_VOLUME_MAX - 1;

    sd_work_init();
}

void sd_work_init(void) // 0x80045E44
{
	static s32 i;
    SdSetAutoKeyOffMode(0);
    SdUtSetReverbType(1);
    SpuClearReverbWorkArea(1);
    SdUtReverbOn();
    SpuSetTransferMode(0);

    g_Sd_ReverbDepth = 20;

    SdUtSetReverbDepth(20, 20);
    Sd_SetReverbEnable(0);
    SdSetSerialAttr(0, 0, 0);
    Sd_SetVolXa(0, 0);

    D_800C15F0[0].field_0 = CdlModeSpeed;
    Sd_CdPrimitiveCmdTry(CdlSetmode, &D_800C15F0[0].field_0, NULL);

    for (i = 0; i < (ARRAY_SIZE(g_Sd_TaskPool) - 1); i++)
    {
        g_Sd_TaskPool[i] = 0;
    }

    for (i = 0; i < ARRAY_SIZE(D_800C15F8); i++)
    {
        D_800C15F8[i] = 0;
    }

    g_Sd_AudioWork.bgmLoadedSongIdx_6         = 0;
    g_Sd_AudioWork.lastVabAudioLoadedIdx_8[0] = 0;
    g_Sd_AudioWork.lastVabAudioLoadedIdx_8[1] = 0;
    g_Sd_AudioWork.lastVabAudioLoadedIdx_8[2] = 0;
    g_Sd_AudioWork.xaAudioIdx_4               = 0;
    g_Sd_AudioWork.isXaStopping_13            = 0;
    g_Sd_AudioWork.cdErrorCount_0             = 0;
    g_Sd_AudioWork.bgmFadeSpeed_14            = 0;
    g_Sd_AudioWork.isAudioLoading_15          = false;
    g_Sd_AudioWork.isXaLoading_16             = false;
    g_Sd_AudioWork.muteGame_17                = 0;
    g_SDVolConfig.volumeGlobal_A               = 127;

    SdSetMVol(127, 127);

    D_800C37DC                                 = false;
    g_Sd_AudioWork.field_E                     = 0;
    g_Sd_AudioWork.field_10                    = 0;
    g_Sd_AudioStreamingStates.audioLoadState_0 = 0;
    g_Sd_AudioStreamingStates.xaLoadState_1    = 0;
    g_Sd_AudioStreamingStates.xaStopState_2    = 0;
    g_Sd_AudioStreamingStates.xaPreLoadState_3 = 0;
    g_SDVolConfig.volumeXa_0                    = 84;
    g_SDVolConfig.volumeBgm_8                   = 40;
    g_SDVolConfig.volumeBgm_6                   = 40;

    Sd_SetVolBgm(40, 40);
}

// ========================================
// AUDIO VAB
// ========================================

void func_80045FF8(void) // 0x80045FF8
{
    s32 i;

    SdSeqClose(0);

    for (i = 4; i >= 0; i--)
    {
        SdVabClose(i);
    }

    SdEnd();
    SdQuit();
}

static inline void WriteVolume(s16* left, s16* right, s16 vol)
{
    *left  = vol;
    *right = vol;
}

u8 Sd_PlaySfx(u16 sfxId, q0_8 balance, u8 vol) // 0x80046048
{
	static s16 audioIdx;
    SpuVoiceAttr attr;
    s16          convertedVol;
    s16          volCpy;
    s32          i;

    if (sfxId == Sfx_Base)
    {
        return NO_VALUE;
    }

    audioIdx = sfxId - Sfx_Base;
    volCpy   = vol;

    // Copy key VAB information.
    g_Sd_VabPlayingInfo.typeIdx_2 = g_Vab_InfoTable[audioIdx].vab_progIdx_2 >> 8;
    g_Sd_VabPlayingInfo.progIdx_4 = g_Vab_InfoTable[audioIdx].vab_progIdx_2 & 0xFF;
    g_Sd_VabPlayingInfo.noteIdx_8 = g_Vab_InfoTable[audioIdx].noteIdx_4;

    convertedVol = g_SDVolConfig.volumeSe_4 + g_Vab_InfoTable[audioIdx].field_5;
    convertedVol = convertedVol - (convertedVol * volCpy) / 255;

    WriteVolume(&g_Sd_VabPlayingInfo.volumeLeft_C, &g_Sd_VabPlayingInfo.volumeRight_E, convertedVol);

    // Apply stereo balance.
    if (g_Sd_AudioWork.isStereoEnabled_12 == true)
    {
        if (balance < 0)
        {
            g_Sd_VabPlayingInfo.volumeRight_E -= (g_Sd_VabPlayingInfo.volumeLeft_C * ABS(balance)) >> 7;
        }
        else
        {
            g_Sd_VabPlayingInfo.volumeLeft_C -= (g_Sd_VabPlayingInfo.volumeLeft_C * balance) >> 7;
        }
    }

    // Clamp volume to positive range.
    if (g_Sd_VabPlayingInfo.volumeLeft_C < 0)
    {
        g_Sd_VabPlayingInfo.volumeLeft_C = 0;
    }
    if (g_Sd_VabPlayingInfo.volumeRight_E < 0)
    {
        g_Sd_VabPlayingInfo.volumeRight_E = 0;
    }

    if (sfxId == Sfx_RadioInterferenceLoop)
    {
        g_Sd_VabPlayingInfo.toneIdx_6 = g_Vab_InfoTable[audioIdx].audioVabIdx_0;
        SdUtKeyOnV(22, g_Sd_VabPlayingInfo.typeIdx_2, g_Sd_VabPlayingInfo.progIdx_4, g_Sd_VabPlayingInfo.toneIdx_6, g_Sd_VabPlayingInfo.noteIdx_8, 0,
                   Sd_GetVolSe(g_Sd_VabPlayingInfo.volumeLeft_C), Sd_GetVolSe(g_Sd_VabPlayingInfo.volumeRight_E));
        g_Sd_VabPlayingInfo.audioVabIdx_0 = 22;
    }
    else if (sfxId == Sfx_RadioStaticLoop)
    {
        g_Sd_VabPlayingInfo.toneIdx_6 = g_Vab_InfoTable[audioIdx].audioVabIdx_0;
        SdUtKeyOnV(23, g_Sd_VabPlayingInfo.typeIdx_2, g_Sd_VabPlayingInfo.progIdx_4, g_Sd_VabPlayingInfo.toneIdx_6, g_Sd_VabPlayingInfo.noteIdx_8, 120,
                   Sd_GetVolSe(g_Sd_VabPlayingInfo.volumeLeft_C), Sd_GetVolSe(g_Sd_VabPlayingInfo.volumeRight_E));
        g_Sd_VabPlayingInfo.audioVabIdx_0 = 23;
    }
    else
    {
        g_Sd_VabPlayingInfo.audioVabIdx_0 = SdVoKeyOn(g_Vab_InfoTable[audioIdx].vab_progIdx_2, g_Sd_VabPlayingInfo.noteIdx_8 * 0x100,
                                                      Sd_GetVolSe(g_Sd_VabPlayingInfo.volumeLeft_C), Sd_GetVolSe(g_Sd_VabPlayingInfo.volumeRight_E));
    }

    for (i = 0; i < ARRAY_SIZE(D_800C15F8); i++)
    {
        if (D_800C15F8[i] == sfxId)
        {
            D_800C15F8[i] = 0;
        }
    }

    if (g_Sd_VabPlayingInfo.audioVabIdx_0 < ARRAY_SIZE(D_800C15F8))
    {
        D_800C15F8[g_Sd_VabPlayingInfo.audioVabIdx_0] = sfxId;
        attr.voice = 1 << g_Sd_VabPlayingInfo.audioVabIdx_0;

        SpuGetVoiceAttr(&attr);

        D_800C1628[g_Sd_VabPlayingInfo.audioVabIdx_0] = attr.pitch;
        return g_Sd_VabPlayingInfo.audioVabIdx_0;
    }

    return NO_VALUE;
}

void func_800463C0(u16 sfxId, q0_8 balance, u8 vol, s8 pitch) // 0x800463C0
{
	static s16 audioIdx;
	static u16 D_800C15C0;
    SpuVoiceAttr attr;
    s16          convertedVol;
    s32          voiceIdx;
    s32          i;

    if (sfxId == Sfx_Base)
    {
        return;
    }

    audioIdx   = sfxId - Sfx_Base;
    D_800C16A4 = g_SDVolConfig.volumeSe_4 + g_Vab_InfoTable[audioIdx].field_5;

    if (sfxId == Sfx_RadioInterferenceLoop)
    {
        voiceIdx   = 22;
        attr.voice = 1 << 22;
    }
    else if (sfxId == Sfx_RadioStaticLoop)
    {
        voiceIdx   = 23;
        attr.voice = 1 << 23;
    }
    else
    {
        voiceIdx = NO_VALUE;
        for (i = 0; i < SD_VOICE_COUNT; i++)
        {
            if (D_800C15F8[i] == sfxId)
            {
                voiceIdx = i;
            }
        }

        if (voiceIdx < 0)
        {
            return;
        }

        // Set voice flag.
        attr.voice = 1 << voiceIdx;
    }

    g_Sd_VabPlayingInfo.pitch_A   = 0;
    g_Sd_VabPlayingInfo.noteIdx_8 = g_Vab_InfoTable[audioIdx].noteIdx_4;
    D_800C15C0                    = D_800C1628[voiceIdx] + (pitch * 2);
    convertedVol                  = vol;
    convertedVol                  = g_Sd_VabPlayingInfo.volumeLeft_C - ((g_Sd_VabPlayingInfo.volumeLeft_C * (convertedVol)) / 255);

    WriteVolume(&g_Sd_VabPlayingInfo.volumeLeft_C, &g_Sd_VabPlayingInfo.volumeRight_E, convertedVol);

    // Apply stereo balance.
    if (g_Sd_AudioWork.isStereoEnabled_12 == true)
    {
        if (balance < 0)
        {
            g_Sd_VabPlayingInfo.volumeRight_E -= (convertedVol * ABS(balance)) >> 7;
        }
        else
        {
            g_Sd_VabPlayingInfo.volumeLeft_C -= (convertedVol * balance) >> 7;
        }
    }

    SpuGetVoiceAttr(&attr);

    attr.mask          = 0x1F;
    attr.volmode.left  = 0;
    attr.volmode.right = 0;
    attr.volmode.left  = 0;
    attr.volmode.right = 0;

    // Clamp volume to positive range.
    if (g_Sd_VabPlayingInfo.volumeLeft_C < 0)
    {
        g_Sd_VabPlayingInfo.volumeLeft_C = 0;
    }
    if (g_Sd_VabPlayingInfo.volumeRight_E < 0)
    {
        g_Sd_VabPlayingInfo.volumeRight_E = 0;
    }

    attr.volume.right = Sd_GetVolSe(g_Sd_VabPlayingInfo.volumeRight_E << 7);
    attr.volume.left  = Sd_GetVolSe(g_Sd_VabPlayingInfo.volumeLeft_C << 7);
    attr.pitch        = D_800C15C0;

    SpuSetVoiceAttr(&attr);
}

void func_80046620(u16 sfxId, q0_8 balance, u8 vol, s8 pitch) // 0x80046620
{
	static s16 D_800C15C2;
    s16 temp;
    s16 convertedVol;

    if (sfxId == Sfx_Base)
    {
        return;
    }

    D_800C15C2                    = sfxId - Sfx_Base;
    g_Sd_VabPlayingInfo.typeIdx_2 = g_Vab_InfoTable[D_800C15C2].vab_progIdx_2 >> 8;
    g_Sd_VabPlayingInfo.progIdx_4 = g_Vab_InfoTable[D_800C15C2].vab_progIdx_2 & 0xFF;
    g_Sd_VabPlayingInfo.toneIdx_6 = g_Vab_InfoTable[D_800C15C2].audioVabIdx_0;
    g_Sd_VabPlayingInfo.noteIdx_8 = g_Vab_InfoTable[D_800C15C2].noteIdx_4 + (s8)(pitch * 5 / 127);

    if (pitch > 0)
    {
        g_Sd_VabPlayingInfo.pitch_A = ABS(pitch * 5) % 127;
    }
    else
    {
        g_Sd_VabPlayingInfo.pitch_A = 127 - ABS(pitch * 5) % 127;
    }

    temp                             = g_SDVolConfig.volumeSe_4 + g_Vab_InfoTable[D_800C15C2].field_5;
    convertedVol                     = vol;
    g_Sd_VabPlayingInfo.volumeLeft_C = temp - (temp * convertedVol) / 255;

    WriteVolume(&g_Sd_VabPlayingInfo.volumeLeft_C, &g_Sd_VabPlayingInfo.volumeRight_E, g_Sd_VabPlayingInfo.volumeLeft_C);

    // Apply stereo balance.
    if (g_Sd_AudioWork.isStereoEnabled_12 == true)
    {
        if (balance < 0)
        {
            g_Sd_VabPlayingInfo.volumeRight_E -= (g_Sd_VabPlayingInfo.volumeRight_E * ABS(balance)) >> 7;
        }
        else
        {
            g_Sd_VabPlayingInfo.volumeLeft_C -= (g_Sd_VabPlayingInfo.volumeLeft_C * balance) >> 7;
        }
    }

    // Clamp volume to positive range.
    if (g_Sd_VabPlayingInfo.volumeLeft_C < 0)
    {
        g_Sd_VabPlayingInfo.volumeLeft_C = 0;
    }
    if (g_Sd_VabPlayingInfo.volumeRight_E < 0)
    {
        g_Sd_VabPlayingInfo.volumeRight_E = 0;
    }

    g_Sd_VabPlayingInfo.audioVabIdx_0 = SdUtKeyOn(g_Sd_VabPlayingInfo.typeIdx_2, g_Sd_VabPlayingInfo.progIdx_4, g_Sd_VabPlayingInfo.toneIdx_6, g_Sd_VabPlayingInfo.noteIdx_8, g_Sd_VabPlayingInfo.pitch_A,
                                                  Sd_GetVolSe(g_Sd_VabPlayingInfo.volumeLeft_C), Sd_GetVolSe(g_Sd_VabPlayingInfo.volumeRight_E));
}

void Sd_LastVoiceKeyOff(void) // 0x800468EC
{
    SdUtKeyOffV(23);
}

void func_8004690C(u16 sfxId) // 0x8004690C
{
    func_8004692C(sfxId);
}

void func_8004692C(u16 cmd) // 0x8004692C
{
    static s16 D_800C15C4;
    static s16 D_800C15C6;
    static s16 D_800C15C8;
    if (cmd == 1280)
    {
        return;
    }

    D_800C15C4 = cmd - 1280;
    D_800C15C6 = g_Vab_InfoTable[D_800C15C4].vab_progIdx_2;
    D_800C15C8 = g_Vab_InfoTable[D_800C15C4].noteIdx_4 << 8;
    SdVoKeyOff(D_800C15C6, D_800C15C8);
}

void Sd_AllVoicesKeyOff(void) // 0x800469AC
{
    s32 i;

    for (i = 0; i < 24; i++)
    {
        SdUtKeyOffV(i);
    }
}

void Sd_AllVoicesKeyOffVWithRROff(void) // 0x800469E8
{
    s32 i;

    for (i = 0; i < 24; i++)
    {
        SdUtKeyOffVWithRROff(i);
    }
}

// ========================================
// BGM HANDLING
// ========================================

void func_80046A24(u16 cmd) // 0x80046A24
{
    if (g_Sd_AudioWork.field_10 != cmd && g_Sd_AudioWork.field_E != cmd)
    {
        g_Sd_AudioWork.field_10 = cmd;
        Sd_TaskPoolAdd(7);
    }
}

void func_80046A70(void) // 0x80046A70
{
    u16 prevVal;

    prevVal                        = g_Sd_AudioWork.field_10;
    g_Sd_AudioWork.bgmFadeSpeed_14 = 0;
    g_Sd_AudioWork.field_10        = 0;
    g_Sd_AudioWork.field_E         = prevVal;

    SdSeqPlay(0, 1, 0);

    g_SDVolConfig.volumeBgm_6 = 40;
    g_SDVolConfig.volumeBgm_8 = 40;

    Sd_SetVolBgm(40, 40);
    Sd_TaskPoolUpdate();
}

void Sd_StopBgmTaskAdd(void) // 0x80046AD8
{
    g_Sd_AudioWork.field_E = NO_VALUE;
    Sd_TaskPoolAdd(8);
}

void Sd_StopBgm(void) // 0x80046B04
{
    if (g_SDVolConfig.volumeBgm_8 > 0)
    {
        g_SDVolConfig.volumeBgm_8 -= 4;
    }

    if (g_SDVolConfig.volumeBgm_8 <= 0)
    {
        g_SDVolConfig.volumeBgm_8 = 0;
        Sd_StopBgmStep();
        Sd_TaskPoolUpdate();
    }

    g_SDVolConfig.volumeBgm_6 = g_SDVolConfig.volumeBgm_8;
    Sd_SetVolBgm(g_SDVolConfig.volumeBgm_6, g_SDVolConfig.volumeBgm_6);
}

void Sd_StopBgmStep(void) // 0x80046B78
{
    Sd_SetVolBgm(0, 0);
    SdSeqStop(0);

    g_Sd_AudioWork.bgmFadeSpeed_14 = 0;
    g_Sd_AudioWork.field_E         = 0;
}

u8 Sd_BgmLayerVolumeGet(u8 layerIdx) // 0x80046BB4
{
    u32 i;
    u8  ret;

    if (layerIdx == 0)
    {
        return 0;
    }

    if (g_Sd_AudioWork.field_E >= 809)
    {
        return 0;
    }

    ret = 0;

    for (i = 0; i < 15; i++)
    {
        if (D_800AA604[(u8)g_Sd_AudioWork.field_E][i] == layerIdx)
        {
            ret = SdGetMidiVol(0, i);
            break;
        }
    }

    return ret;
}

void Sd_BgmLayerVolumeSet(u8 layerIdx, u8 vol) // 0x80046C54
{
    u32 i;
    s16 volCpy;
    u8  var1;
    u8  idx;

    if (layerIdx == 0)
    {
        g_SDVolConfig.volumeBgm_6 = (vol * 40) / 127;
    }
    else if (g_Sd_AudioWork.field_E < 809)
    {
		
        idx = g_Sd_AudioWork.field_E;

        for (i = 0; i < 15; i++)
        {
            var1   = D_800AA604[idx][i];
            volCpy = vol;

            if (var1 == layerIdx)
            {
                SdSetMidiVol(0, i, volCpy);
            }
        }
    }
}

// ========================================
// XA FILES RELATED
// ========================================

void Sd_XaAudioPlayTaskAdd(u16 sfx) // 0x80046D3C
{
    g_Sd_AudioWork.xaAudioIdxCheck_2 = sfx & 0xFFF;

    if (g_XaItemData[g_Sd_AudioWork.xaAudioIdxCheck_2].xaFileIdx_0 != 0)
    {
        D_800C37DC         = true;
        D_800C1688.field_8 = VSync(SyncMode_Count);
        D_800C1688.field_4 = 0;

        Sd_TaskPoolAdd(2);

        g_Sd_AudioWork.xaAudioIdx_4 = g_Sd_AudioWork.xaAudioIdxCheck_2;

        Sd_TaskPoolAdd(1);
    }
}

s32 Sd_XaAudioLengthGet(s32 idx) // 0x80046DCC
{
    return (g_XaItemData[idx & 0xFFF].audioLength_8 & 0xFFFFFF) + 32;
}

void Sd_XaAudioPlay(void) // 0x80046E00
{
	static u16 D_800C15CA;
	static u32 D_800C15CC;
    u32* temp_a1;
    u32* temp_v0;

    g_Sd_AudioWork.cdErrorCount_0++;

    switch (g_Sd_AudioStreamingStates.xaLoadState_1)
    {
        case 0:
            if (g_Sd_AudioWork.bgmFadeSpeed_14 == 0)
            {
                g_SDVolConfig.volumeBgm_6 = 24;
            }

            D_800C15CA = g_Sd_AudioWork.xaAudioIdxCheck_2;
            switch (D_800C15CA)
            {
                case 53:
                case 56:
                case 596:
                case 597:
                case 598:
                case 600:
                case 602:
                case 612:
                case 614:
                case 620:
                case 657:
                case 606:
                    g_SDVolConfig.volumeXa_2 = Sd_GetVolSe(84);
                    break;

                case 723:
                case 725:
                    g_SDVolConfig.volumeXa_2 = 50;
                    break;

                case 724:
                    g_SDVolConfig.volumeXa_2 = 40;
                    break;

                default:
                    g_SDVolConfig.volumeXa_2 = 84;
                    break;
            }

            g_SDVolConfig.volumeXa_0                   = g_SDVolConfig.volumeXa_2;
            Sd_SetVolXa(g_SDVolConfig.volumeXa_2, g_SDVolConfig.volumeXa_2);
            D_800C15F0[0].field_0                      = CdlModeSF | CdlModeRT | CdlModeSpeed;
            g_Sd_AudioStreamingStates.xaLoadState_1 = 1;
            break;

        case 1:
            if (!Sd_CdPrimitiveCmdTry(CdlSetmode, &D_800C15F0[0].field_0, NULL))
            {
                g_Sd_AudioWork.cdErrorCount_0           = 0;
                g_Sd_AudioStreamingStates.xaLoadState_1 = 2;
            }
            break;

        default:
            break;

        case 2:
            D_800C15F0[0].field_0                      = g_XaItemData[D_800C15CA].field_8_24;
            D_800C15F0[0].field_1                      = g_XaItemData[D_800C15CA].field_4_24;
            g_Sd_AudioStreamingStates.xaLoadState_1 = 3;
            break;

        case 3:
            if (!Sd_CdPrimitiveCmdTry(CdlSetfilter, &D_800C15F0[0].field_0, NULL))
            {
                g_Sd_AudioWork.cdErrorCount_0           = 0;
                g_Sd_AudioStreamingStates.xaLoadState_1 = 4;
            }
            break;

        case 4:
            // @hack Needed for match, weird code.
            temp_a1     = g_FileXaLoc;
            temp_v0     = &temp_a1[g_XaItemData[D_800C15CA].xaFileIdx_0];
            D_800C15CC  = *temp_v0;
            D_800C15CC += 0x96 + g_XaItemData[D_800C15CA].sector_4;

            D_800C1688.field_0 = g_XaItemData[D_800C15CA].audioLength_8 + 32;

            g_Sd_AudioStreamingStates.xaLoadState_1 = 5;
            D_800C15E8[0].sector                    = itob(D_800C15CC % 75);
            D_800C15CC                             /= 75;
            D_800C15E8[0].second                    = itob(D_800C15CC % 60);
            D_800C15CC                             /= 60;
            D_800C15E8[0].minute                    = itob(D_800C15CC);
            break;

        case 5:
            if (!Sd_CdPrimitiveCmdTry(CdlSeekL, (u8*)&D_800C15E8[0], NULL))
            {
                g_Sd_AudioWork.cdErrorCount_0           = 0;
                g_Sd_AudioStreamingStates.xaLoadState_1 = 6;
            }
            break;

        case 6:
            if (!Sd_CdPrimitiveCmdTry(CdlReadN, NULL, NULL))
            {
                g_Sd_AudioWork.cdErrorCount_0           = 0;
                D_800C37DC                              = false;
                g_Sd_AudioStreamingStates.xaLoadState_1 = 7;
            }
            break;

        case 7:
            g_Sd_AudioWork.xaAudioIdx_4 = D_800C15CA;

            SdSetSerialAttr(0, 0, 1);
            D_800C1688.field_8                      = VSync(SyncMode_Count);
            D_800C1688.field_4                      = 0;
            g_Sd_AudioStreamingStates.xaLoadState_1 = 0;

            Sd_TaskPoolUpdate();
            g_Sd_AudioWork.cdErrorCount_0 = 0;
            g_Sd_AudioWork.isXaLoading_16 = false;
            break;
    }
}

void Sd_XaPreLoadAudioPreTaskAdd(u16 xaIdx) // 0x8004729C
{
    Sd_XaPreLoadAudioTaskAdd(xaIdx);
}

void Sd_XaPreLoadAudioTaskAdd(s32 xaIdx) // 0x800472BC
{
    g_Sd_AudioWork.xaAudioIdxCheck_2 = xaIdx & 0xFFF;
    D_800C37DC                       = true;

    if (g_Sd_AudioWork.xaAudioIdx_4 != 0)
    {
        Sd_TaskPoolAdd(2);
    }

    Sd_TaskPoolAdd(6);
}

void Sd_XaPreLoadAudio(void) // 0x80047308
{
	static u16 D_800C15D0;
	static u16 pad_800C15D2;
	static u32 D_800C15D4;

    u32* temp_a1;
    u32* temp_v0;

    g_Sd_AudioWork.cdErrorCount_0++;

    switch (g_Sd_AudioStreamingStates.xaPreLoadState_3)
    {
        case 0:
            D_800C15D0 = g_Sd_AudioWork.xaAudioIdxCheck_2;

            Sd_SetVolXa(0, 0);

            D_800C15F0[0].field_0                      = CdlModeSF | CdlModeRT | CdlModeSpeed;
            g_Sd_AudioStreamingStates.xaPreLoadState_3 = 1;
            break;

        case 1:
            if (!Sd_CdPrimitiveCmdTry(CdlSetmode, &D_800C15F0[0].field_0, NULL))
            {
                g_Sd_AudioWork.cdErrorCount_0              = 0;
                g_Sd_AudioStreamingStates.xaPreLoadState_3 = 2;
            }
            break;

        case 2:
            D_800C15F0[0].field_0                         = g_XaItemData[D_800C15D0].field_8_24;
            D_800C15F0[0].field_1                         = g_XaItemData[D_800C15D0].field_4_24;
            g_Sd_AudioStreamingStates.xaPreLoadState_3 = 3;
            return;

        case 3:
            if (!Sd_CdPrimitiveCmdTry(CdlSetfilter, &D_800C15F0[0].field_0, NULL))
            {
                g_Sd_AudioWork.cdErrorCount_0              = 0;
                g_Sd_AudioStreamingStates.xaPreLoadState_3 = 4;
            }
            break;

        case 4:
            // @hack Needed for match, weird code.
            temp_a1     = g_FileXaLoc;
            temp_v0     = &temp_a1[g_XaItemData[D_800C15D0].xaFileIdx_0];
            D_800C15D4  = *temp_v0;
            D_800C15D4 += 0x96 + g_XaItemData[D_800C15D0].sector_4;

            D_800C1688.field_0 = g_XaItemData[D_800C15D0].audioLength_8 + 32;

            g_Sd_AudioStreamingStates.xaPreLoadState_3 = 5;
            D_800C15E8[0].sector                       = itob(D_800C15D4 % 75);
            D_800C15D4                                /= 75;
            D_800C15E8[0].second                       = itob(D_800C15D4 % 60);
            D_800C15D4                                /= 60;
            D_800C15E8[0].minute                       = itob(D_800C15D4);
            break;

        case 5:
            if (!Sd_CdPrimitiveCmdTry(CdlSeekL, (u8*)&D_800C15E8[0], NULL))
            {
                g_Sd_AudioWork.cdErrorCount_0              = 0;
                g_Sd_AudioStreamingStates.xaPreLoadState_3 = 6;
            }
            break;

        case 6:
            if (!Sd_CdPrimitiveCmdTry(CdlPause, NULL, NULL))
            {
                g_Sd_AudioStreamingStates.xaPreLoadState_3 = 0;
                D_800C37DC                                 = false;
                Sd_TaskPoolUpdate();
                g_Sd_AudioWork.cdErrorCount_0              = 0;
            }
            break;

        default:
            break;
    }
}

void Sd_XaAudioStopTaskAdd(void) // 0x8004760C
{
    Sd_TaskPoolAdd(2);
    g_Sd_AudioWork.isXaLoading_16 = true;
}

void Sd_XaAudioStop(void) // 0x80047634
{
    g_Sd_AudioWork.isXaStopping_13 = 1;

    switch (g_Sd_AudioStreamingStates.xaStopState_2)
    {
        case 0:
            Sd_SetVolXa(g_SDVolConfig.volumeXa_0, g_SDVolConfig.volumeXa_0);
            g_SDVolConfig.volumeXa_0 -= 24;
            g_SDVolConfig.volumeXa_2  = g_SDVolConfig.volumeXa_0;

            if (g_SDVolConfig.volumeXa_0 < 2)
            {
                g_Sd_AudioStreamingStates.xaStopState_2 = 1;
            }
            break;

        case 1:
            g_SDVolConfig.volumeXa_0 = 0;
            g_SDVolConfig.volumeXa_2 = 0;

            Sd_SetVolXa(0, 0);
            SdSetSerialAttr(0, 0, 0);

            g_Sd_AudioStreamingStates.xaStopState_2 = 2;
            break;

        case 2:
            if (!Sd_CdPrimitiveCmdTry(CdlPause, NULL, NULL))
            {
                g_Sd_AudioWork.cdErrorCount_0            = 0;
                g_Sd_AudioStreamingStates.xaStopState_2  = 3;
            }

            g_Sd_AudioWork.cdErrorCount_0++;
            break;

        case 3:
            g_Sd_AudioWork.isXaStopping_13           = 0;
            g_Sd_AudioWork.xaAudioIdx_4              = 0;
            g_Sd_AudioStreamingStates.xaStopState_2  = 0;

            if (g_Sd_AudioWork.bgmFadeSpeed_14 == 0)
            {
                g_SDVolConfig.volumeBgm_6 = 40;
            }

            Sd_TaskPoolUpdate();
            g_Sd_AudioWork.cdErrorCount_0 = 0;
            break;

        default:
            break;
    }
}

void Sd_SetVolume(u8 xaVol, s16 bgmVol, u8 seVol) // 0x80047798
{
    g_SDVolConfig.globalVolumeXa_E  = xaVol;
    g_SDVolConfig.globalVolumeBgm_D = bgmVol;
    g_SDVolConfig.globalVolumeSe_C  = seVol;
    
    if (g_Sd_AudioWork.field_E != 0)
    {
        Sd_SetVolBgm(g_SDVolConfig.volumeBgm_8, g_SDVolConfig.volumeBgm_8);
    }
    
    if (g_Sd_AudioWork.xaAudioIdx_4 != 0)
    {
        Sd_SetVolXa(g_SDVolConfig.volumeXa_0, g_SDVolConfig.volumeXa_0);
    }
}

void Sd_SetVolBgm(s16 volLeft, s16 volRight) // 0x80047808
{
    SdSeqSetVol(0, (volLeft * g_SDVolConfig.globalVolumeBgm_D) >> 7, (volRight * g_SDVolConfig.globalVolumeBgm_D) >> 7);
}

void Sd_SetVolXa(s16 volLeft, s16 volRight) // 0x80047860
{
    SdSetSerialVol(0, (volLeft * g_SDVolConfig.globalVolumeXa_E) >> 7, (volRight * g_SDVolConfig.globalVolumeXa_E) >> 7);
}

s16 Sd_GetVolSe(s16 arg0) // 0x800478B8
{
    return (arg0 * g_SDVolConfig.globalVolumeSe_C) >> 7;
}

// ========================================
// TASK POOL HANDLING
// ========================================

void Sd_TaskPoolAdd(u8 task) // 0x800478DC
{
    static s32 i;
    static s32 y;
	
    // If `task` is 2, shift field next to element containing value that matches 1 in `g_Sd_TaskPool`.
    if (task == 2)
    {
        for (i = 1; i < (ARRAY_SIZE(g_Sd_TaskPool) - 2); i++)
        {
            if (g_Sd_TaskPool[i] == 1)
            {
                for (y = i; y < (ARRAY_SIZE(g_Sd_TaskPool) - 2); y++)
                {
                    g_Sd_TaskPool[y] = g_Sd_TaskPool[y + 1];
                }

                g_Sd_TaskPool[31] = 0;
                D_800C37DC        = false;
            }
        }
    }

    // Shift field next to element containing value that matches `task` in `g_Sd_TaskPool`.
    for (i = 1; i < (ARRAY_SIZE(g_Sd_TaskPool) - 2); i++)
    {
        if (g_Sd_TaskPool[i] == task)
        {
            for (y = i; y < (ARRAY_SIZE(g_Sd_TaskPool) - 2); y++)
            {
                g_Sd_TaskPool[y] = g_Sd_TaskPool[y + 1];
            }

            g_Sd_TaskPool[31] = 0;
        }
    }

    // If `g_Sd_TaskPool` field is empty, assign value of `task`.
    for (i = 0; i < (ARRAY_SIZE(g_Sd_TaskPool) - 1); i++)
    {
        if (g_Sd_TaskPool[i] == 0)
        {
            g_Sd_TaskPool[i] = task;
            break;
        }
    }

    g_Sd_CurrentTask = g_Sd_TaskPool[0];
}

void Sd_TaskPoolUpdate(void) // 0x80047A70
{
    static s32 i;
    static s32 pad_800C15E4;
    if (g_Sd_TaskPool[0] != 0)
    {
        for (i = 0; i < (ARRAY_SIZE(g_Sd_TaskPool) - 1); i++)
        {
            g_Sd_TaskPool[i] = g_Sd_TaskPool[i + 1];
        }

        g_Sd_TaskPool[31] = 0;
    }
}

// ========================================
// REVERB HANDLING
// ========================================

void Sd_SetReverbDepth(u8 depth) // 0x80047AD0
{
    s32 left;

    g_Sd_ReverbDepth = depth;

    left = depth;
    SdUtSetReverbDepth(left, left);
}

void Sd_SetReverbEnable(s32 mode) // 0x80047AFC
{
    SdSetSerialAttr(0, 1, mode);
}

const s32 rodataPad_80025CF8 = 0;
