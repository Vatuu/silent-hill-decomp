// Ai_LarvalStalker
// dummy union is just `u_Properties` ATM though.

void sharedFunc_800D140C_1_s00(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    s_800C4590 sp18;

    #define dummyProps (chara->properties_E4.dummy)

    chara->field_34 += g_DeltaTime2 >> 1;

    if (!(dummyProps.properties_E8[0].val16[0] & (1 << 1)))
    {
        chara->headingAngle_3C = chara->rotation_24.vy;
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        func_8005CB20(chara, &sp18, dummyProps.properties_E8[6].val16[0], dummyProps.properties_E8[6].val16[1]);
    }

    dummyProps.properties_E8[6].val16[1] = 0;
    dummyProps.properties_E8[6].val16[0] = 0;

    if (chara->field_34 != Q12(0.0f))
    {
        dummyProps.properties_E8[0].val16[0] |= 1 << 5;
    }
    else
    {
        dummyProps.properties_E8[0].val16[0] &= ~(1 << 5);
    }

    if (chara->moveSpeed_38 > Q12(0.0f))
    {
        if (sp18.offset_0.vx == 0 && sp18.offset_0.vz == 0)
        {
            dummyProps.properties_E8[8].val16[0]  = Chara_HeadingAngleGet(chara,
                                                                          Q12(1.0f),
                                                                          dummyProps.properties_E8[4].val32,
                                                                          dummyProps.properties_E8[5].val32,
                                                                          Q12(1.0f),
                                                                          false);
            dummyProps.properties_E8[0].val16[0] |= 1 << 3;
        }
    }

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coords);
}
