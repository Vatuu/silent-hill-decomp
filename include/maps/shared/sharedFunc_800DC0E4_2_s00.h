bool sharedFunc_800DC0E4_2_s00(s_SubCharacter* chara, s32 speedMult)
{
    s32 headingAngle;
    s32 moveSpeed;
    s32 posZ;
    s32 posX;

    moveSpeed    = chara->moveSpeed_38;
    posX         = chara->position_18.vx;
    posZ         = chara->position_18.vz;
    headingAngle = chara->headingAngle_3C;

    moveSpeed = FP_MULTIPLY_PRECISE(moveSpeed, speedMult, Q12_SHIFT);
    posX     += FP_MULTIPLY_PRECISE(Math_Sin(headingAngle), moveSpeed, Q12_SHIFT);
    posZ     += FP_MULTIPLY_PRECISE(Math_Cos(headingAngle), moveSpeed, Q12_SHIFT);

    switch (func_800808AC(posX, posZ))
    {
        case 0:
        case 7:
        case 12:
            return 1;
    }

    return func_80080884(posX, posZ) + Q12(1.2f) > chara->position_18.vy;
}
