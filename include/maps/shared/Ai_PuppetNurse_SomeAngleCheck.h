bool Ai_PuppetNurse_SomeAngleCheck(s_SubCharacter* nurse)
{
    q19_12 sumSqr;
    q19_12 angle;

    sumSqr = FP_SQUARE_PRECISE(nurse->dmg_B4.field_0, Q12_SHIFT) +
             FP_SQUARE_PRECISE(nurse->dmg_B4.field_4, Q12_SHIFT) +
             FP_SQUARE_PRECISE(nurse->dmg_B4.field_8, Q12_SHIFT);

    angle = ratan2(nurse->dmg_B4.field_0, nurse->dmg_B4.field_8);
    angle = ABS(func_8005BF38(angle - nurse->rotation_24.vy));

    if (sumSqr > FP_ANGLE(360.0f) && angle > FP_ANGLE(10.0f))
    {
        return true;
    }

    return false;
}
