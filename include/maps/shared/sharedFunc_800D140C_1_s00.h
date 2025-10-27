// Ai_LarvalStalker
// larvalStalker union is just u_Properties atm though..

void sharedFunc_800D140C_1_s00(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    s_800C4590 sp18;

#define CHARA_PROPERTIES (chara->properties_E4.larvalStalker)

    chara->field_34 += g_DeltaTime2 >> 1;

    if (!(CHARA_PROPERTIES.properties_E8[0].val16[0] & (1 << 1)))
    {
        chara->headingAngle_3C = chara->rotation_24.vy;
    }

    if (g_DeltaTime0 != 0)
    {
        func_8005CB20(chara, &sp18, CHARA_PROPERTIES.properties_E8[6].val16[0], CHARA_PROPERTIES.properties_E8[6].val16[1]);
    }

    CHARA_PROPERTIES.properties_E8[6].val16[1] = 0;
    CHARA_PROPERTIES.properties_E8[6].val16[0] = 0;

    if (chara->field_34 != 0)
    {
        CHARA_PROPERTIES.properties_E8[0].val16[0] |= (1 << 5);
    }
    else
    {
        CHARA_PROPERTIES.properties_E8[0].val16[0] &= ~(1 << 5);
    }

    if (chara->moveSpeed_38 > 0)
    {
        if (sp18.offset_0.vx == 0 && sp18.offset_0.vz == 0)
        {
            CHARA_PROPERTIES.properties_E8[8].val16[0]  = func_8006FAFC(chara, Q12(1.0f), CHARA_PROPERTIES.properties_E8[4].val32, CHARA_PROPERTIES.properties_E8[5].val32, 0x1000, 0);
            CHARA_PROPERTIES.properties_E8[0].val16[0] |= (1 << 3);
        }
    }

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coords);
}
