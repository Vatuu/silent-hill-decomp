void sharedFunc_800D0968_3_s03(s_SubCharacter* nurse, GsCOORDINATE2* coords)
{
    q19_12 posY;

    if (nurse->model_0.anim_4.flags_2 & AnimFlag_Visible)
    {
        sharedFunc_800D0828_3_s03(nurse, coords);
        return;
    }

    posY = nurse->position_18.vy;

    nurse->field_C8.field_2 = posY;
    nurse->field_C8.field_4 = posY;
    nurse->field_C8.field_0 = posY - Q12(1.7f);
    nurse->field_C8.field_6 = posY - Q12(1.0f);
}
