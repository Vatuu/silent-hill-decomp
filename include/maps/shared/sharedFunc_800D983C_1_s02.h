void sharedFunc_800D983C_1_s02(s_SubCharacter* chara)
{
    s_800C4590 unused;
    s32 newMoveSpeed;

    chara->field_34 += g_DeltaTime2 >> 2;

    if (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & (1 << 1))
    {
        if (chara->moveSpeed_38 > 0)
        {
            newMoveSpeed = chara->moveSpeed_38 - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 4.0f, Q12_SHIFT);
            if (newMoveSpeed < 0)
            {
                newMoveSpeed = 0;
            }
        }
        else
        {
            newMoveSpeed = chara->moveSpeed_38 + FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 4.0f, Q12_SHIFT);
            if (newMoveSpeed > 0)
            {
                newMoveSpeed = 0;
            }
        }

        chara->moveSpeed_38 = newMoveSpeed;
    }
    else
    {
        chara->headingAngle_3C = chara->rotation_24.vy;
    }

    func_8005CB20(chara, &unused, chara->properties_E4.larvalStalker.properties_E8[1].val16[0], chara->properties_E4.larvalStalker.properties_E8[1].val16[1]);
    chara->properties_E4.larvalStalker.properties_E8[1].val16[1] = 0;
    chara->properties_E4.larvalStalker.properties_E8[1].val16[0] = 0;

    if (chara->field_34 != 0)
    {
        chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 2;
    }
    else
    {
        chara->properties_E4.larvalStalker.properties_E8[0].val16[0] &= ~(1 << 2);
    }

    chara->rotation_24.vy = func_8005BF38(chara->rotation_24.vy);
}
