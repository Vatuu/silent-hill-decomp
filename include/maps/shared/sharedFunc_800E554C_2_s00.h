void sharedFunc_800E554C_2_s00(s_SubCharacter* chara) // 0x800E4DA0
{
    if (!((u16)chara->properties_E4.dummy.properties_E8[0].val16[0] & 0x2) &&
        chara->model_0.anim_4.status_0 == ANIM_STATUS(9, true) &&
        (Rng_Rand16() % 8) == 0)
    {
        chara->model_0.state_2         = 1;
        chara->model_0.anim_4.status_0 = ANIM_STATUS(17, false);
    }
}
