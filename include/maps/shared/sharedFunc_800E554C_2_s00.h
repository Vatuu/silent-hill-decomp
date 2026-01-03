void sharedFunc_800E554C_2_s00(s_SubCharacter* groaner) // 0x800E4DA0
{
    if (!((u16)groaner->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 1)) &&
        groaner->model_0.anim_4.status_0 == ANIM_STATUS(9, true) &&
        !Rng_GenerateInt(0, 7)) // 1 in 8 chance.
    {
        groaner->model_0.controlState_2         = 1;
        groaner->model_0.anim_4.status_0 = ANIM_STATUS(17, false);
    }
}
