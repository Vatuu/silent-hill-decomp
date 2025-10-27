// Ai_LarvalStalker
// larvalStalker union is just `u_Properties` ATM though.

void sharedFunc_800D140C_1_s00(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    s_800C4590 sp18;

    #define larvalStalkerProps (chara->properties_E4.larvalStalker)

    chara->field_34 += g_DeltaTime2 >> 1;

    if (!(larvalStalkerProps.properties_E8[0].val16[0] & (1 << 1)))
    {
        chara->headingAngle_3C = chara->rotation_24.vy;
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        func_8005CB20(chara, &sp18, larvalStalkerProps.properties_E8[6].val16[0], larvalStalkerProps.properties_E8[6].val16[1]);
    }

    larvalStalkerProps.properties_E8[6].val16[1] = 0;
    larvalStalkerProps.properties_E8[6].val16[0] = 0;

    if (chara->field_34 != 0)
    {
        larvalStalkerProps.properties_E8[0].val16[0] |= 1 << 5;
    }
    else
    {
        larvalStalkerProps.properties_E8[0].val16[0] &= ~(1 << 5);
    }

    if (chara->moveSpeed_38 > Q12(0.0f))
    {
        if (sp18.offset_0.vx == 0 && sp18.offset_0.vz == 0)
        {
            larvalStalkerProps.properties_E8[8].val16[0]  = func_8006FAFC(chara, Q12(1.0f), larvalStalkerProps.properties_E8[4].val32, larvalStalkerProps.properties_E8[5].val32, 0x1000, 0);
            larvalStalkerProps.properties_E8[0].val16[0] |= 1 << 3;
        }
    }

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coords);
}
