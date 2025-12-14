void sharedFunc_800D0968_3_s03(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    q19_12 posY;

    if (chara->model_0.anim_4.flags_2 & AnimFlag_Visible)
    {
        sharedFunc_800D0828_3_s03(chara, coords);
        return;
    }

    posY = chara->position_18.vy;

    chara->field_C8.field_2 = posY;
    chara->field_C8.field_4 = posY;
    chara->field_C8.field_0 = posY - Q12(1.7f);
    chara->field_C8.field_6 = posY - Q12(1.0f);
}
