#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>
#include <psyq/libapi.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/sound_system.h"

VECTOR3 D_800C42C0;
VECTOR3* D_800C42CC;

// ========================================
// 3D SOUND
// ========================================

s32 func_8005D86C(s32 arg0) // 0x8005D86C
{
    s32 var_a0;
    s32 var_v1;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp;

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
    temp_a3 = temp >> 7;

    var_a0 = D_800AE564[temp_a3];
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
        var_v1 = D_800AE564[temp_a3 + 1];
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

s32 func_8005D9B8(VECTOR3* pos, q23_8 vol) // 0x8005D9B8
{
    s32 temp_v0;
    s32 deltaX;
    s32 deltaY;
    s32 deltaZ;
    s32 var_s0;
    s32 var_v0;

    vwGetViewPosition(&D_800C42C0);
    D_800C42CC = &g_SysWork.playerWork_4C.player_0.position_18;

    deltaX = D_800C42C0.vx - D_800C42CC->vx;
    deltaY = D_800C42C0.vy - D_800C42CC->vy;
    deltaZ = D_800C42C0.vz - D_800C42CC->vz;
    var_s0 = func_8005D974((SquareRoot12(Q12_MULT_PRECISE(deltaX, deltaX) +
                                         Q12_MULT_PRECISE(deltaY, deltaY) +
                                         Q12_MULT_PRECISE(deltaZ, deltaZ)) - Q12(2.5f)) / 10);
    if (var_s0 > Q12(1.0f))
    {
        var_s0 = Q12(1.0f);
    }

    deltaX  = D_800C42CC->vx - pos->vx;
    deltaY  = D_800C42CC->vy - pos->vy;
    deltaZ  = D_800C42CC->vz - pos->vz;
    temp_v0 = func_8005D974((SquareRoot12(Q12_MULT_PRECISE(deltaX, deltaX) +
                                          Q12_MULT_PRECISE(deltaY, deltaY) +
                                          Q12_MULT_PRECISE(deltaZ, deltaZ)) - Q12(6.0f)) / 4);

    var_v0 = Q12_MULT_PRECISE(var_s0, temp_v0);
    if (var_v0 > Q12(2.0f))
    {
        var_v0 = Q12(2.0f);
    }
    else if (var_v0 < Q12(0.0f))
    {
        var_v0 = Q12(0.0f);
    }

    var_v0 = Q12_MULT_PRECISE(vol, var_v0);
    if (var_v0 > Q8_CLAMPED(1.0f))
    {
        var_v0 = Q8_CLAMPED(1.0f);
    }
    else if (var_v0 < Q12(0.0f))
    {
        var_v0 = Q12(0.0f);
    }

    return var_v0;
}

void func_8005DC1C(e_SfxId sfxId, const VECTOR3* pos, q23_8 vol, s32 soundType)
{
    func_8005DC3C(sfxId, pos, vol, soundType, 0);
}

void func_8005DC3C(e_SfxId sfxId, const VECTOR3* pos, q23_8 vol, s32 soundType, s32 pitch) // 0x8005DC3C
{
    q23_8 volCpy;
    q23_8 balance;

    // Get stereo balance.
    if (soundType & (1 << 0) || g_GameWork.config_0.optSoundType_1E)
    {
        balance = 0;
    }
    else
    {
        balance = Sound_StereoBalanceGet(pos);
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

    if (!(soundType & (1 << 1)))
    {
        volCpy = func_8005D9B8(pos, vol);
    }
    else
    {
        volCpy = vol;
    }

    if (volCpy > Q8_CLAMPED(1.0f))
    {
        volCpy = Q8_CLAMPED(1.0f);
    }

    if (soundType & (1 << 2))
    {
        Sd_SfxAttributesUpdate(sfxId, balance, ~volCpy, pitch);
    }
    else
    {
        Sd_PlaySfx(sfxId, balance, ~volCpy);
    }
}

void func_8005DD44(e_SfxId sfxId, VECTOR3* pos, q23_8 vol, s8 pitch) // 0x8005DD44
{
    q23_8 volCpy;
    s32   balance;

    // Get stereo balance.
    if (g_GameWork.config_0.optSoundType_1E)
    {
        balance = 0;
    }
    else
    {
        balance = Sound_StereoBalanceGet(pos);
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

    volCpy = func_8005D9B8(pos, vol);
    if (volCpy > Q8_CLAMPED(1.0f))
    {
        volCpy = Q8_CLAMPED(1.0f);
    }

    func_80046620(sfxId, balance, ~volCpy, pitch);
}

static inline s32 AttenuationCalc(s32 volume, VECTOR3* pos, q19_12 falloff)
{
    q19_12 dist;

    dist = Math_Vector3MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - pos->vx,
                               g_SysWork.playerWork_4C.player_0.position_18.vy - pos->vy,
                               g_SysWork.playerWork_4C.player_0.position_18.vz - pos->vz);
    return (volume * dist) / falloff;
}

void func_8005DE0C(e_SfxId sfxId, VECTOR3* pos, s32 vol, q19_12 falloff, s8 pitch)
{
    s32 balance;
    u16 finalVol;
    s32 s3;
    s32 att0;
    u8  att1;
    s32 att2;

    if (g_GameWork.config_0.optSoundType_1E)
    {
        balance = 0;
    }
    else
    {
        balance = Sound_StereoBalanceGet(pos);
    }

    if (vol > 0xFF)
    {
        vol = 0xFF;
    }

    if (vol < 0)
    {
        return;
    }

    att0 = AttenuationCalc(vol, pos, falloff);
    s3 = vol - 0xFF;
    if ((att0 - s3) >= 0xFF || (AttenuationCalc(vol, pos, falloff) - s3) >= 0)
    {
        att2 = AttenuationCalc(vol, pos, falloff) - s3;
        finalVol = 0xFF;
        if (att2 < 0xFF)
        {
            att1 = AttenuationCalc(vol, pos, falloff) - (vol + 1);
            finalVol = att1;
        }
    }
    else
    {
        finalVol = 0;
    }

    Sd_SfxAttributesUpdate(sfxId, balance, finalVol, pitch);
}
