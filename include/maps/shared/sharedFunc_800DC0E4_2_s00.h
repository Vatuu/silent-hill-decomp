bool sharedFunc_800DC0E4_2_s00(s_SubCharacter* airScreamer, s32 speedMult)
{
    q19_12 headingAngle;
    q19_12 moveSpeed;
    q19_12 posX;
    q19_12 posZ;

    moveSpeed    = airScreamer->moveSpeed_38;
    posX         = airScreamer->position_18.vx;
    posZ         = airScreamer->position_18.vz;
    headingAngle = airScreamer->headingAngle_3C;

    moveSpeed = FP_MULTIPLY_PRECISE(moveSpeed, speedMult, Q12_SHIFT);
    posX     += FP_MULTIPLY_PRECISE(Math_Sin(headingAngle), moveSpeed, Q12_SHIFT);
    posZ     += FP_MULTIPLY_PRECISE(Math_Cos(headingAngle), moveSpeed, Q12_SHIFT);

    switch (func_800808AC(posX, posZ))
    {
        case 0:
        case 7:
        case 12:
            return true;
    }

    return (Collision_GroundHeightGet(posX, posZ) + Q12(1.2f)) > airScreamer->position_18.vy;
}
