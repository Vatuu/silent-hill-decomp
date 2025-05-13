void sharedFunc_800D0968_3_s03(s_SubCharacter* arg0, s32 arg1)
{
    s32 posY;

    if (arg0->model_0.anim_4.flags_2 & 2)
    {
        sharedFunc_800D0828_3_s03(arg0, arg1);
        return;
    }

    posY = arg0->position_18.vy;

    arg0->field_CA = posY;
    arg0->field_CC = posY;
    arg0->field_C8 = posY - FP_METER(27.2f);
    arg0->field_CE = posY - FP_METER(16.0f);
}
