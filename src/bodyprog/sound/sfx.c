#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>
#include <psyq/libapi.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/sound/sfx.h"
#include "bodyprog/math/math.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/sound/sound_system.h"

static VECTOR3  g_Sfx_CameraPosition; // Q19.12
static VECTOR3* g_Sfx_PlayerPosition; // Q19.12

s32 func_8005D86C(q19_12 arg0) // 0x8005D86C
{
    s32    var_a0;
    s32    var_v1;
    s32    temp_a1;
    q19_12 temp_a2;
    s32    idx;
    q19_12 temp;

    temp    = Q12_FRACT(arg0);
    temp_a1 = FP_FROM(arg0, Q12_SHIFT);

    if (temp_a1 >= 12)
    {
        return 0;
    }
    if (temp_a1 < -20)
    {
        return INT_MAX;
    }

    temp_a2 = (arg0 & 0x7F) << 5;
    idx = temp >> 7;

    var_a0 = D_800AE564[idx];
    if (temp_a1 > 0)
    {
        var_a0 >>= temp_a1;
    }
    else if (temp_a1 < 0)
    {
        var_a0 <<= -temp_a1;
    }

    if (temp_a2 != 0)
    {
        var_v1 = D_800AE564[idx + 1];
        if (temp_a1 > 0)
        {
            var_v1 >>= temp_a1;
        }
        else if (temp_a1 < 0)
        {
            var_v1 <<= -temp_a1;
        }

        var_a0 = Q12_MULT_PRECISE(var_a0, Q12(1.0f) - temp_a2) + Q12_MULT_PRECISE(var_v1, temp_a2);
    }

    return var_a0;
}

s32 func_8005D974(s32 arg0) // 0x8005D974
{
    s32 val;

    val = func_8005D86C(arg0);
    if (val > Q12(4.0f))
    {
        val = Q12(4.0f);
    }
    else if (val < Q12(0.0f))
    {
        val = Q12(0.0f);
    }

    return val;
}

q23_8 Sfx_DistanceAttenuatedVolumeGet(const VECTOR3* pos, q23_8 vol) // 0x8005D9B8
{
    q19_12 offsetX;
    q19_12 offsetY;
    q19_12 offsetZ;
    q19_12 camToPlayerFactor;
    q19_12 playerToPos;
    q23_8  adjVol;

    vwGetViewPosition(&g_Sfx_CameraPosition);
    g_Sfx_PlayerPosition = &g_SysWork.playerWork.player.position;

    offsetX           = g_Sfx_CameraPosition.vx - g_Sfx_PlayerPosition->vx;
    offsetY           = g_Sfx_CameraPosition.vy - g_Sfx_PlayerPosition->vy;
    offsetZ           = g_Sfx_CameraPosition.vz - g_Sfx_PlayerPosition->vz;
    camToPlayerFactor = func_8005D974((SquareRoot12(Q12_MULT_PRECISE(offsetX, offsetX) +
                                                    Q12_MULT_PRECISE(offsetY, offsetY) +
                                                    Q12_MULT_PRECISE(offsetZ, offsetZ)) - Q12(2.5f)) / 10);
    if (camToPlayerFactor > Q12(1.0f))
    {
        camToPlayerFactor = Q12(1.0f);
    }

    offsetX     = g_Sfx_PlayerPosition->vx - pos->vx;
    offsetY     = g_Sfx_PlayerPosition->vy - pos->vy;
    offsetZ     = g_Sfx_PlayerPosition->vz - pos->vz;
    playerToPos = func_8005D974((SquareRoot12(Q12_MULT_PRECISE(offsetX, offsetX) +
                                              Q12_MULT_PRECISE(offsetY, offsetY) +
                                              Q12_MULT_PRECISE(offsetZ, offsetZ)) - Q12(6.0f)) / 4);

    adjVol = Q12_MULT_PRECISE(camToPlayerFactor, playerToPos);
    if (adjVol > Q8(32.0f))
    {
        adjVol = Q8(32.0f);
    }
    else if (adjVol < Q8(0.0f))
    {
        adjVol = Q8(0.0f);
    }

    adjVol = Q12_MULT_PRECISE(vol, adjVol);
    if (adjVol > Q8_CLAMPED(1.0f))
    {
        adjVol = Q8_CLAMPED(1.0f);
    }
    else if (adjVol < Q8(0.0f))
    {
        adjVol = Q8(0.0f);
    }

    return adjVol;
}

void Sfx_WithFlagsPlay(e_SfxId sfxId, const VECTOR3* pos, q23_8 vol, s32 sfxFlags) // 0x8005DC1C
{
    Sfx_WithFlagsAndPitchPlay(sfxId, pos, vol, sfxFlags, SfxFlag_None);
}

void Sfx_WithFlagsAndPitchPlay(e_SfxId sfxId, const VECTOR3* pos, q23_8 vol, s32 sfxFlags, s32 pitch) // 0x8005DC3C
{
    q23_8 adjVol;
    q23_8 balance;

    // Get stereo balance.
    if (sfxFlags & SfxFlag_Mono || g_GameWork.config.soundType)
    {
        balance = Q8(0.0f);
    }
    else
    {
        balance = Vc_StereoBalanceGet(pos);
    }

    // Clamp volume.
    if (vol > Q8_CLAMPED(1.0f))
    {
        vol = Q8_CLAMPED(1.0f);
    }
    else if (vol < Q8_CLAMPED(0.0f))
    {
        vol = Q8_CLAMPED(0.0f);
    }

    if (sfxFlags & SfxFlag_NoDistAtten)
    {
        adjVol = vol;
    }
    else
    {
        adjVol = Sfx_DistanceAttenuatedVolumeGet(pos, vol);
    }

    if (adjVol > Q8_CLAMPED(1.0f))
    {
        adjVol = Q8_CLAMPED(1.0f);
    }

    if (sfxFlags & SfxFlag_UpdateAttribs)
    {
        Sd_SfxAttributesUpdate(sfxId, balance, ~adjVol, pitch);
    }
    else
    {
        Sd_PlaySfx(sfxId, balance, ~adjVol);
    }
}

void Sfx_WithPitchPlay(e_SfxId sfxId, const VECTOR3* pos, q23_8 vol, s8 pitch) // 0x8005DD44
{
    q23_8 volCpy;
    s32   balance;

    // Get stereo balance.
    if (g_GameWork.config.soundType)
    {
        balance = 0;
    }
    else
    {
        balance = Vc_StereoBalanceGet(pos);
    }

    // Clamp volume.
    if (vol > Q8_CLAMPED(1.0f))
    {
        vol = Q8_CLAMPED(1.0f);
    }
    else if (vol < Q8_CLAMPED(0.0f))
    {
        vol = Q8_CLAMPED(0.0f);
    }

    volCpy = Sfx_DistanceAttenuatedVolumeGet(pos, vol);
    if (volCpy > Q8_CLAMPED(1.0f))
    {
        volCpy = Q8_CLAMPED(1.0f);
    }

    func_80046620(sfxId, balance, ~volCpy, pitch);
}

static inline q23_8 AttenuationCalc(s32 vol, VECTOR3* pos, q19_12 falloff)
{
    q19_12 dist;

    dist = Math_Vector3MagCalcSafe(g_SysWork.playerWork.player.position.vx - pos->vx,
                                   g_SysWork.playerWork.player.position.vy - pos->vy,
                                   g_SysWork.playerWork.player.position.vz - pos->vz);
    return (vol * dist) / falloff;
}

void Sfx_WithFalloffAndPitchPlay(e_SfxId sfxId, VECTOR3* pos, s32 vol, q19_12 falloff, s8 pitch)
{
    s32 balance;
    u16 adjVol;
    s32 unkVol;
    s32 atten0;
    u8  atten1;
    s32 atten2;

    if (g_GameWork.config.soundType)
    {
        balance = 0;
    }
    else
    {
        balance = Vc_StereoBalanceGet(pos);
    }

    if (vol > Q8_CLAMPED(1.0f))
    {
        vol = Q8_CLAMPED(1.0f);
    }

    if (vol < Q8(0.0f))
    {
        return;
    }

    atten0 = AttenuationCalc(vol, pos, falloff);
    unkVol = vol - Q8_CLAMPED(1.0f);
    if ((atten0 - unkVol) >= Q8_CLAMPED(1.0f) || (AttenuationCalc(vol, pos, falloff) - unkVol) >= 0)
    {
        atten2 = AttenuationCalc(vol, pos, falloff) - unkVol;
        adjVol = Q8_CLAMPED(1.0f);
        if (atten2 < Q8_CLAMPED(1.0f))
        {
            atten1 = AttenuationCalc(vol, pos, falloff) - (vol + 1);
            adjVol = atten1;
        }
    }
    else
    {
        adjVol = Q8(0.0f);
    }

    Sd_SfxAttributesUpdate(sfxId, balance, adjVol, pitch);
}
