bool Ai_PuppetNurse_SomeAngleCheck(s_SubCharacter* nurse)
{
    q19_12 sumSqr;
    q19_12 damageAngle;

    sumSqr = Q12_SQUARE_PRECISE(nurse->damage_B4.position_0.vx) +
             Q12_SQUARE_PRECISE(nurse->damage_B4.position_0.vy) +
             Q12_SQUARE_PRECISE(nurse->damage_B4.position_0.vz);

    damageAngle = ratan2(nurse->damage_B4.position_0.vx, nurse->damage_B4.position_0.vz);
    damageAngle = ABS(func_8005BF38(damageAngle - nurse->rotation_24.vy));
    if (sumSqr > FP_ANGLE(360.0f) && damageAngle > FP_ANGLE(10.0f))
    {
        return true;
    }

    return false;
}
