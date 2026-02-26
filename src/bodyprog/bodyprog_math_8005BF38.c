#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>
#include <psyq/libapi.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"

// ========================================
// MATHS?
// ========================================

q3_12 func_8005BF38(q3_12 angle) // 0x8005BF38
{
    q3_12 outAngle;
    q3_12 angleNorm;

    angleNorm = Q12_ANGLE_NORM_U(angle);

    outAngle = angleNorm;
    if (angleNorm > Q12_ANGLE(180.0f))
    {
        outAngle = angleNorm | 0xF000;
    }
    return outAngle;
}

bool func_8005BF58(s32* arg0, s32* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) // 0x8005BF58
{
    s32 temp_a0;
    s32 temp_lo;
    s32 temp_t4;
    s32 var_a2;
    s32 var_t0_5;
    s32 var_v0_5;
    s32 new_var;

    if (MAX(arg2, arg4) < CLAMP_HIGH(arg6, arg8) || MAX(arg6, arg8) < CLAMP_HIGH(arg2, arg4))
    {
        return false;
    }

    if (MAX(arg3, arg5) < CLAMP_HIGH(arg7, arg9) || MAX(arg7, arg9) < CLAMP_HIGH(arg3, arg5))
    {
        return false;
    }

    var_v0_5 = (arg6 - arg2) >> 6;
    new_var  = (arg7 - arg3) >> 6;
    temp_a0  = arg5 - arg3;
    temp_t4  = arg4 - arg2;

    if (((var_v0_5 * (temp_a0 >> 6)) - (new_var * (temp_t4 >> 6))) > 0 ||
        ((((arg8 - arg2) >> 6) * (temp_a0 >> 6)) - (((arg9 - arg3) >> 6) * (temp_t4 >> 6))) < 0)
    {
        return false;
    }

    if ((((arg2 - arg6) >> 6) * ((arg9 - arg7) >> 6)) - (((arg3 - arg7) >> 6) * ((arg8 - arg6) >> 6)) < 0 ||
        (((arg4 - arg6) >> 6) * ((arg9 - arg7) >> 6)) - (((arg5 - arg7) >> 6) * ((arg8 - arg6) >> 6)) > 0)
    {
        return false;
    }

    if (arg0 != NULL)
    {
        if (arg2 == arg4)
        {
            var_t0_5 = ((arg9 - arg7) << 9) / (arg8 - arg6);
            *arg0    = arg2;
            var_a2   = (arg7 << 9) - (var_t0_5 * arg6);
        }
        else
        {
            var_t0_5 = (temp_a0 << 9) / temp_t4;
            var_a2   = (arg3 << 9) - (var_t0_5 * arg2);

            if (arg6 == arg8)
            {
                *arg0 = arg6;
            }
            else
            {
                temp_lo = ((arg9 - arg7) << 9) / (arg8 - arg6);
                *arg0   = (var_a2 - ((arg7 << 9) - (temp_lo * arg6))) / (temp_lo - var_t0_5);
            }
        }

        *arg1 = ((var_t0_5 * *arg0) + var_a2) >> 9;
    }

    return true;
}

s32 func_8005C1CC(s32* arg0, s32* arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) // 0x8005C1CC
{
    s16 temp_v0_6;
    s16 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s1;
    s32 temp_s2;
    s32 var_s0;

    if (arg2 + arg4 < CLAMP_HIGH(arg5, arg7) || arg2 - arg4 > MAX(arg5, arg7))
    {
        return 0;
    }

    if (arg3 + arg4 < CLAMP_HIGH(arg6, arg8) || arg3 - arg4 > MAX(arg6, arg8))
    {
        return 0;
    }

    temp_s2 = SquareRoot0(SQUARE((arg2 - arg5) >> 6) + SQUARE((arg3 - arg6) >> 6)) << 6;

    if (arg4 < temp_s2 && (SQUARE((arg7 - arg5) >> 6) + SQUARE((arg8 - arg6) >> 6)) < SQUARE((temp_s2 - arg4) >> 6))
    {
        return 0;
    }

    temp_s0   = ratan2(arg3 - arg6, arg2 - arg5);
    temp_v0_6 = ratan2(arg8 - arg6, arg7 - arg5);
    temp_s1   = temp_s0 - temp_v0_6;

    var_s0 = ABS(Q12_MULT(temp_s2, Math_Sin(temp_s1)));
    if (arg4 < var_s0)
    {
        return 0;
    }

    if (arg0 != NULL)
    {
        if (temp_s2 < arg4)
        {
            *arg0 = arg5;
            *arg1 = arg6;
        }
        else
        {
            temp_s0_2 = Math_Cos(temp_s0 - temp_v0_6);
            temp_s0_3 = Q12_MULT(temp_s2, temp_s0_2) - (SquareRoot0(SQUARE(arg4 >> 6) - SQUARE(var_s0 >> 6)) << 6);
            *arg0     = arg5 + Q12_MULT(temp_s0_3, Math_Cos(temp_v0_6));
            *arg1     = arg6 + Q12_MULT(temp_s0_3, Math_Sin(temp_v0_6));
        }
    }

    return 1;
}

u32 func_8005C478(s16* arg0, s32 x0, s32 y0, s32 x1, s32 y1, s32 x2, s32 y2) // 0x8005C478
{
    s32   sp10;
    q3_12 angle0;
    q3_12 angle1;
    q3_12 angle2;
    s32   mag0;
    s32   mag1;
    s32   var0;
    s32   var_s1;
    s32   var_v0_4;
    s32   var1;
    s32   temp;

    angle0 = func_8005BF38(ratan2(x0 - x1, y0 - y1));
    angle1 = func_8005BF38(ratan2(x0 - x2, y0 - y2));
    angle2 = func_8005BF38(ratan2(x2 - x1, y2 - y1));
    mag0   = Math_Vector2MagCalc(x0 - x1, y0 - y1);
    mag1   = Math_Vector2MagCalc(x0 - x2, y0 - y2);

    if ((mag0 * Math_Sin(angle0 - angle2)) < 0)
    {
        sp10 = -Q12_MULT(mag0, Math_Sin(angle0 - angle2));
    }
    else
    {
        sp10 = Q12_MULT(mag0, Math_Sin(angle0 - angle2));
    }

    if (mag1 < mag0)
    {
        var0 = mag0;
    }
    else
    {
        var0 = mag1;
    }

    if (!(mag1 < mag0))
    {
        var1 = mag0;
    }
    else
    {
        var1 = mag1;
    }

    var0 = SQUARE(var0 >> 6);
    var1 = SQUARE(var1 >> 6);

    if (var0 < (var1 + (SQUARE((x2 - x1) >> 6) + SQUARE((y2 - y1) >> 6))))
    {
        if (arg0 != NULL)
        {
            if (mag0 * Math_Cos(angle0 - angle2) < 0)
            {
                var_s1 = -Q12_MULT(mag0, Math_Cos(angle0 - angle2));
            }
            else
            {
                var_s1 = Q12_MULT(mag0, Math_Cos(angle0 - angle2));
            }

            if ((mag1 * Math_Cos(angle1 - angle2)) < 0)
            {
                var_v0_4 = -Q12_MULT(mag1, Math_Cos(angle1 - angle2));
            }
            else
            {
                var_v0_4 = Q12_MULT(mag1, Math_Cos(angle1 - angle2));
            }

            temp  = var_s1 + var_v0_4;
            *arg0 = ((var_s1 << Q12_SHIFT) / temp);
        }

        return ABS(sp10);
    }

    if (mag0 < mag1)
    {
        if (arg0 != NULL)
        {
            *arg0 = 0;
        }

        return ABS(mag0);
    }

    if (arg0 != NULL)
    {
        *arg0 = Q12(1.0f);
    }

    return ABS(mag1);
}

s32 func_8005C7B0(s32 arg0) // 0x8005C7B0
{
    return D_800AE520[arg0 >> 5];
}
