void sharedFunc_800D983C_1_s02(s_SubCharacter* creaper)
{
    s_800C4590 unused;

    creaper->field_34 += g_DeltaTime2 >> 2;

    if (creaper->properties_E4.creaper.flags_E8 & CreaperFlag_1)
    {
        Chara_MoveSpeedUpdate(creaper, Q12(4.0f));
    }
    else
    {
        creaper->headingAngle_3C = creaper->rotation_24.vy;
    }

    func_8005CB20(creaper, &unused, creaper->properties_E4.creaper.offsetX_EC, creaper->properties_E4.creaper.offsetZ_EE);
    creaper->properties_E4.creaper.offsetZ_EE = Q12(0.0f);
    creaper->properties_E4.creaper.offsetX_EC = Q12(0.0f);

    if (creaper->field_34 != Q12(0.0f))
    {
        creaper->properties_E4.creaper.flags_E8 |= CreaperFlag_2;
    }
    else
    {
        creaper->properties_E4.creaper.flags_E8 &= ~CreaperFlag_2;
    }

    creaper->rotation_24.vy = func_8005BF38(creaper->rotation_24.vy);
}
