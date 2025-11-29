bool sharedFunc_800CDDE8_3_s03(s_SubCharacter* chara)
{
    s32 squareSum;
    s32 angle;

    squareSum = FP_SQUARE_PRECISE(chara->field_B4, Q12_SHIFT) +
                FP_SQUARE_PRECISE(chara->field_B8, Q12_SHIFT) +
                FP_SQUARE_PRECISE(chara->field_BC, Q12_SHIFT);

    angle = ratan2(chara->field_B4, chara->field_BC);
    angle = ABS(func_8005BF38(angle - chara->rotation_24.vy));

    if (squareSum > FP_ANGLE(360.0f) && angle > FP_ANGLE(10.0f))
    {
        return true;
    }
    return false;
}
