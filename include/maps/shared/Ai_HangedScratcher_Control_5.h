void Ai_HangedScratcher_Control_5(s_SubCharacter* arg0)
{
#define MIN_OFF(a, neg, pos) ((((a) + (-neg)) <= ((a) + (pos))) ? ((a) - (neg)) : ((a) + (pos)))
#define MAX_OFF(a, neg, pos) ((((a) - (neg)) > ((a) + (pos))) ? ((a) - (neg)) : ((a) + (pos)))

    if (Vw_AabbVisibleInScreenCheck(
            MIN_OFF(arg0->position_18.vx, 0x800, 0x800),
            MAX_OFF(arg0->position_18.vx, 0x800, 0x800),
            MIN_OFF(arg0->position_18.vy, 0x1000, 0),
            MAX_OFF(arg0->position_18.vy, 0x1000, 0),
            MIN_OFF(arg0->position_18.vz, 0x800, 0x800),
            MAX_OFF(arg0->position_18.vz, 0x800, 0x800)) ||
        (Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - arg0->position_18.vx,
                             g_SysWork.playerWork_4C.player_0.position_18.vz - arg0->position_18.vz) < 0x1000))
    {
        if (func_800700F8(arg0, &g_SysWork.playerWork_4C.player_0))
        {
            return;
        }

        if (((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 3) == 2 && func_8006FD90(arg0, 1, 0x1800, 0x800)) ||
            (((u8)g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 2) &&
             ((u8)g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 1) && func_8006FD90(arg0, 1, 0x1333, 0x4CC)))
        {
            arg0->model_0.controlState_2  = 7;
            arg0->model_0.anim_4.status_0 = 0x24;
        }
    }
}