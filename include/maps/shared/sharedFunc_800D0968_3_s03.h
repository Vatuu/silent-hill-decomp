void sharedFunc_800D0968_3_s03(s_SubCharacter* chara, GsCOORDINATE2* coords)
#ifdef SHARED_FUNC_IMPL
{
    s32 posY;

    if (chara->model_0.anim_4.flags_2 & AnimFlag_Visible)
    {
        sharedFunc_800D0828_3_s03(chara, coords);
        return;
    }

    posY = chara->position_18.vy;

    chara->field_CA = posY;
    chara->field_CC = posY;
    chara->field_C8 = posY - FP_METER(1.7f);
    chara->field_CE = posY - FP_METER(1.0f);
}
#else
;
#endif
