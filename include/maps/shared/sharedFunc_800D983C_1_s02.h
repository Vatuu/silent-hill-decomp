void sharedFunc_800D983C_1_s02(s_SubCharacter* creaper)
{
    s_800C4590 unused;

    creaper->field_34 += g_DeltaTime2 >> 2;

    if (creaper->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 1))
    {
        Chara_MoveSpeedUpdate(creaper, Q12(4.0f));
    }
    else
    {
        creaper->headingAngle_3C = creaper->rotation_24.vy;
    }

    func_8005CB20(creaper, &unused, creaper->properties_E4.dummy.properties_E8[1].val16[0], creaper->properties_E4.dummy.properties_E8[1].val16[1]);
    creaper->properties_E4.dummy.properties_E8[1].val16[1] = 0;
    creaper->properties_E4.dummy.properties_E8[1].val16[0] = 0;

    if (creaper->field_34 != 0)
    {
        creaper->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 2;
    }
    else
    {
        creaper->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 2);
    }

    creaper->rotation_24.vy = func_8005BF38(creaper->rotation_24.vy);
}
