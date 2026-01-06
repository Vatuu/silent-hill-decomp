bool sharedFunc_800DC0E4_2_s00(s_SubCharacter* airScreamer, q19_12 moveSpeedMult)
{
    q19_12 headingAngle;
    q19_12 moveSpeed;
    q19_12 posX;
    q19_12 posZ;

    moveSpeed    = airScreamer->moveSpeed_38;
    posX         = airScreamer->position_18.vx;
    posZ         = airScreamer->position_18.vz;
    headingAngle = airScreamer->headingAngle_3C;

    moveSpeed = Q12_MULT_PRECISE(moveSpeed, moveSpeedMult);
    posX     += Q12_MULT_PRECISE(Math_Sin(headingAngle), moveSpeed);
    posZ     += Q12_MULT_PRECISE(Math_Cos(headingAngle), moveSpeed);

    switch (func_800808AC(posX, posZ))
    {
        case 0:
        case 7:
        case 12:
            return true;
    }

    return (Collision_GroundHeightGet(posX, posZ) + Q12(1.2f)) > airScreamer->position_18.vy;
}
