#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/libapi.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/joy.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"

// Some kind of `Anim_UpdateX` function, included in some `s_AnimInfo` array which also had pointers to `Anim_Update1`/`Anim_Update2`.

// TODO: Might be able to merge into `bodyprog_80070B84` (will need rename to `bodyprog_800706E4`)

s32 func_800706E4(s_Model* model) // 0x800706E4
{
    s32 result;

    result = 0;

    switch (g_SysWork.player_4C.extra_128.state_1C)
    {
        case 39:
        case 40:
            switch (g_SavegamePtr->mapOverlayId_A4)
            {
                case MapOverlayId_MAP2_S00:
                case MapOverlayId_MAP2_S02:
                case MapOverlayId_MAP4_S02:
                case MapOverlayId_MAP5_S01:
                case MapOverlayId_MAP6_S00:
                case MapOverlayId_MAP6_S02:
                    if (g_MapOverlayHeader.field_38[D_800AF220].status_2 == ANIM_STATUS(128, false) ||
                        g_MapOverlayHeader.field_38[D_800AF220].status_2 == ANIM_STATUS(129, false))
                    {
                        if (g_SysWork.player_4C.chara_0.health_B0 <= Q12(0.0f))
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.afkTimer_E8 -= g_DeltaTime0;
                            if (g_SysWork.player_4C.chara_0.properties_E4.player.afkTimer_E8 >= Q12(0.0f))
                            {
                                g_SysWork.player_4C.chara_0.properties_E4.player.afkTimer_E8 -= g_DeltaTime0;
                                result = g_SysWork.player_4C.chara_0.properties_E4.player.afkTimer_E8;
                            }
                            else
                            {
                                result = Q12(0.0f);
                            }
                            break;
                        }
                    }

                    result = Q12(15.0f);
            }
            break;

        case 47:
        case 48:
            if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP6_S04)
            {
                if (g_MapOverlayHeader.field_38[D_800AF220].status_2 == ANIM_STATUS(132, true) ||
                    g_MapOverlayHeader.field_38[D_800AF220].status_2 == ANIM_STATUS(133, false))
                {
                    if (g_SysWork.player_4C.chara_0.health_B0 <= 0)
                    {
                        g_SysWork.player_4C.chara_0.properties_E4.player.afkTimer_E8 -= g_DeltaTime0 * 2;
                        if (g_SysWork.player_4C.chara_0.properties_E4.player.afkTimer_E8 >= Q12(0.0f))
                        {
                            g_SysWork.player_4C.chara_0.properties_E4.player.afkTimer_E8 -= g_DeltaTime0 * 2;

                            result = g_SysWork.player_4C.chara_0.properties_E4.player.afkTimer_E8;
                        }
                        else
                        {
                            result = Q12(0.0f);
                        }
                        break;
                    }
                }

                result = Q12(10.0f);
            }
            break;

        default:
            switch (model->anim_4.status_0)
            {
                case ANIM_STATUS(2, true):
                    if (g_Controller0->sticks_20.sticks_0.leftY < -63)
                    {
                        result = (ABS(g_Controller0->sticks_20.sticks_0.leftY + 64) * Q12(0.65f) / 64) * 16 + Q12(12.0f);
                    }
                    else if (D_800AF216 != 0)
                    {
                        result = ((ABS(D_800AF216 - 64) * Q12(0.65f) / 64) * 16) + Q12(12.0f);
                    }
                    else
                    {
                        result = Q12(22.0f);
                    }
                    break;

                case ANIM_STATUS(3, true):
                    if (g_Controller0->sticks_20.sticks_0.leftY < -63)
                    {
                        if ((model->anim_4.keyframeIdx_8 >= 40 && model->anim_4.keyframeIdx_8 < 46) ||
                            (model->anim_4.keyframeIdx_8 >= 30 && model->anim_4.keyframeIdx_8 < 36))
                        {
                            result = ABS(g_Controller0->sticks_20.sticks_0.leftY + 64) * Q12(0.25f) + Q12(16.0f);
                        }
                        else
                        {
                            result = Q12(32.0f);
                        }
                    }
                    else if (D_800AF216 != 0)
                    {
                        result = ABS(D_800AF216 - 64) * Q12(0.25f) + Q12(16.0f);
                    }
                    else
                    {
                        result = Q12(30.0f);
                    }
                    break;

                case ANIM_STATUS(4, true):
                    if (g_Controller0->sticks_20.sticks_0.leftY >= 64)
                    {
                        result = ((ABS(g_Controller0->sticks_20.sticks_0.leftY - 64) * Q12(0.4f) / 64) * Q12(1.0f) / 200) + Q12(15.36f);
                    }
                    else if (D_800AF216 != 0)
                    {
                        result = ((ABS(D_800AF216 - 64) * Q12(0.4f) / 64) * Q12(1.0f) / 200) + Q12(15.36f);
                    }
                    else
                    {
                        result = Q12(23.0f);
                    }
                    break;

                case ANIM_STATUS(27, true):
                    if (g_SysWork.player_4C.chara_0.health_B0 < Q12(30.0f))
                    {
                        result = Q12(40.0f) - g_SysWork.player_4C.chara_0.health_B0;
                    }
                    else
                    {
                        result = FP_TO(FP_FROM(g_SysWork.player_4C.chara_0.properties_E4.player.exhaustionTimer_FC, Q12_SHIFT), Q12_SHIFT);
                    }
                    break;
            }
    }

    return result;
}
