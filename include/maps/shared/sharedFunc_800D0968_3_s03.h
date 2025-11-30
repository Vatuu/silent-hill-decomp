void sharedFunc_800D0968_3_s03(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    q19_12 posY;

    if (chara->model_0.anim_4.flags_2 & AnimFlag_Visible)
    {
        sharedFunc_800D0828_3_s03(chara, coords);
        return;
    }

    posY = chara->position_18.vy;

    chara->field_CA = posY;
    chara->field_CC = posY;
    chara->field_C8 = posY - Q12(1.7f);
    chara->field_CE = posY - Q12(1.0f);
}
