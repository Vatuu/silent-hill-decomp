typedef struct
{
    s32 field_0;
    s32 field_4;
} s_800EEE3C;

extern s_800EEE3C sharedData_800EEE3C_2_s00[];

#if defined(MAP2_S00)
#define UNK_VAL Q12(0.6f)
#else
#define UNK_VAL Q12(1.0f)
#endif

void sharedFunc_800E384C_2_s00(s_SubCharacter* groaner)
{
    extern void (*sharedData_800EEE14_2_s00[])(s_SubCharacter* chara);

    #define getIndex() (((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 3) == 0) * 2 + ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 3) == 2))

    if (func_80070360(groaner, Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - groaner->position_18.vx, 
            g_SysWork.playerWork_4C.player_0.position_18.vz - groaner->position_18.vz), UNK_VAL) != 0 ||
        func_8006FD90(groaner, 1, sharedData_800EEE3C_2_s00[getIndex()].field_0, sharedData_800EEE3C_2_s00[getIndex()].field_4))
    {
        groaner->properties_E4.groaner.flags_E8.val16[0] |= (1 << 7);

        if (groaner->properties_E4.groaner.flags_E8.val16[0] & (1 << 5))
        {
            groaner->properties_E4.groaner.targetPositionX_F4 = g_SysWork.playerWork_4C.player_0.position_18.vx;
            groaner->properties_E4.groaner.targetPositionZ_F8 = g_SysWork.playerWork_4C.player_0.position_18.vz;
        }
    }
    else
    {
        groaner->properties_E4.groaner.flags_E8.val16[0] &= ~(1 << 7);
    }

    if (groaner->model_0.anim_4.status_0 != ANIM_STATUS(10, true))
    {
        groaner->field_44.field_0 = 0;
    }

    sharedData_800EEE14_2_s00[groaner->model_0.controlState_2](groaner);
}
