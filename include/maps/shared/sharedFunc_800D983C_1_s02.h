void sharedFunc_800D983C_1_s02(s_SubCharacter* creeper)
{
    s_800C4590 unused;

    creeper->field_34 += g_DeltaTime2 >> 2;

    if (creeper->properties_E4.creeper.flags_E8 & CreeperFlag_1)
    {
        Chara_MoveSpeedUpdate(creeper, Q12(4.0f));
    }
    else
    {
        creeper->headingAngle_3C = creeper->rotation_24.vy;
    }

    func_8005CB20(creeper, &unused, creeper->properties_E4.creeper.offsetX_EC, creeper->properties_E4.creeper.offsetZ_EE);
    creeper->properties_E4.creeper.offsetZ_EE = Q12(0.0f);
    creeper->properties_E4.creeper.offsetX_EC = Q12(0.0f);

    if (creeper->field_34 != Q12(0.0f))
    {
        creeper->properties_E4.creeper.flags_E8 |= CreeperFlag_2;
    }
    else
    {
        creeper->properties_E4.creeper.flags_E8 &= ~CreeperFlag_2;
    }

    creeper->rotation_24.vy = func_8005BF38(creeper->rotation_24.vy);
}
