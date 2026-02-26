#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_background.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"

// ========================================
// BGM RELATED
// ========================================

void func_80087EA8(s32 cmd) // 0x80087EA8
{
    if (!Bgm_IsCurrentBgmTargetCheck(cmd))
    {
        return;
    }

    Bgm_TrackSet(cmd);
}

void func_80087EDC(s32 cmd) // 0x80087EDC
{
    if (Sd_AudioStreamingCheck() || !Fs_QueueDoThingWhenEmpty())
    {
        return;
    }

    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            if (!Bgm_IsCurrentBgmTargetCheck(cmd))
            {
                SysWork_StateStepSet(1, 3);
                break;
            }

            g_SysWork.sysFlags_22A0 |= SysFlag_7;
            SysWork_StateStepIncrement(1);
            break;

        case 1:
            g_SysWork.sysFlags_22A0 |= SysFlag_7;
            SD_Call(23);

            SysWork_StateStepIncrement(1);
            break;

        case 2:
            g_SysWork.sysFlags_22A0 |= SysFlag_7;

            if (!func_80045BC8())
            {
                Bgm_TrackSet(cmd);

                SysWork_StateStepIncrement(1);
            }
            break;

        case 3:
            SysWork_StateStepIncrement(0); // Resets `field_10` to 0.
            break;
    }
}

void func_80088028(void) // 0x80088028
{
    func_80087EDC(0);
}

void func_80088048(void) // 0x80088048
{
    if (Sd_AudioStreamingCheck())
    {
        return;
    }

    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            Bgm_AllLayersMute();
            SD_Call(18);
            SysWork_StateStepIncrement(1);
            break;

        case 1:
            if (!func_80045BC8())
            {
                SysWork_StateStepIncrement(0); // Resets `field_10` to 0.
            }
            break;

        default:
            break;
    }
}

void func_800880F0(s32 arg0) // 0x800880F0
{
    if (Sd_AudioStreamingCheck())
    {
        return;
    }

    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            Bgm_AllLayersMute();

            if (arg0 == 0)
            {
                SD_Call(22);
            }
            else
            {
                SD_Call(23);
            }

            SysWork_StateStepIncrement(1);
            break;

        case 1:
            if (!func_80045BC8())
            {
                SysWork_StateStepIncrement(0); // Resets `field_10` to 0.
            }
            break;
    }
}
