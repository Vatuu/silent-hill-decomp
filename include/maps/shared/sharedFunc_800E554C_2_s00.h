void sharedFunc_800E554C_2_s00(s_SubCharacter* groaner) // 0x800E4DA0
{
    if (!(groaner->properties_E4.groaner.flags_E8.val16[0] & GroanerFlag_1) &&
        groaner->model_0.anim_4.status_0 == ANIM_STATUS(GroanerAnim_9, true) &&
        !Rng_GenerateInt(0, 7)) // 1 in 8 chance.
    {
        groaner->model_0.controlState_2         = GroanerControl_1;
        groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_17, false);
    }
}
