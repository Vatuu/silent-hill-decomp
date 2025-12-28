// Ai_LarvalStalker
// dummy union is just `u_Properties` ATM though.

void sharedFunc_800D140C_1_s00(s_SubCharacter* larvalStalker, GsCOORDINATE2* coords)
{
    s_800C4590 sp18;

    #define larvalStalkerProps larvalStalker->properties_E4.larvalStalker
    #define dummyProps (larvalStalker->properties_E4.dummy)

    larvalStalker->field_34 += g_DeltaTime2 >> 1;

    if (!(larvalStalkerProps.flags_E8 & LarvalStalkerFlag_1))
    {
        larvalStalker->headingAngle_3C = larvalStalker->rotation_24.vy;
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        func_8005CB20(larvalStalker, &sp18, dummyProps.properties_E8[6].val16[0], dummyProps.properties_E8[6].val16[1]);
    }

    dummyProps.properties_E8[6].val16[1] = 0;
    dummyProps.properties_E8[6].val16[0] = 0;

    if (larvalStalker->field_34 != Q12(0.0f))
    {
        larvalStalkerProps.flags_E8 |= LarvalStalkerFlag_5;
    }
    else
    {
        larvalStalkerProps.flags_E8 &= ~LarvalStalkerFlag_5;
    }

    if (larvalStalker->moveSpeed_38 > Q12(0.0f))
    {
        if (sp18.offset_0.vx == Q12(0.0f) &&
            sp18.offset_0.vz == Q12(0.0f))
        {
            dummyProps.properties_E8[8].val16[0]  = Chara_HeadingAngleGet(larvalStalker,
                                                                          Q12(1.0f),
                                                                          dummyProps.properties_E8[4].val32,
                                                                          dummyProps.properties_E8[5].val32,
                                                                          Q12(1.0f),
                                                                          false);
            larvalStalkerProps.flags_E8 |= LarvalStalkerFlag_3;
        }
    }

    Math_MatrixTransform(&larvalStalker->position_18, &larvalStalker->rotation_24, coords);

    #undef larvalStalkerProps
}
