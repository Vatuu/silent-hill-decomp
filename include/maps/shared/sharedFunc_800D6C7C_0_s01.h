void sharedFunc_800D6C7C_0_s01(VECTOR* arg0, s_SubCharacter* chara, s32 arg2, VECTOR3* arg3)
{
    s32 sqr;
    s32 z;
    s32 y;
    s32 x;

    if (arg2 == 0)
    {
        x = 0;
        y = 0;
        z = 0;
    } 
    else 
    {
        x = arg0->vx;
        y = arg0->vy;
        z = arg0->vz;

        sqr = FP_MULTIPLY_PRECISE(x, x, Q12_SHIFT);
        sqr += FP_MULTIPLY_PRECISE(y, y, Q12_SHIFT);
        sqr += FP_MULTIPLY_PRECISE(z, z, Q12_SHIFT);
        
        sqr = SquareRoot12(sqr);
        
        chara->damageReceived_C0 += Math_PreservedSignSubtract(sqr, Q12(5.0f));
        if (sqr != 0) 
        {
            sqr = Q12(Math_PreservedSignSubtract(sqr, Q12(6.0f))) / sqr;
        }

        x = FP_MULTIPLY_PRECISE(x, sqr, Q12_SHIFT);
        y = FP_MULTIPLY_PRECISE(y, sqr, Q12_SHIFT);
        z = FP_MULTIPLY_PRECISE(z, sqr, Q12_SHIFT);
        
        if (x | y | z)
        {
            chara->field_B4 += FP_MULTIPLY_PRECISE(x, Q12(0.8f), Q12_SHIFT);
            chara->field_B8 += FP_MULTIPLY_PRECISE(y, Q12(0.8f), Q12_SHIFT);
            chara->field_BC += FP_MULTIPLY_PRECISE(z, Q12(0.8f), Q12_SHIFT);
        }
    }

    arg3->vx = x;
    arg3->vy = y;
    arg3->vz = z;
}
