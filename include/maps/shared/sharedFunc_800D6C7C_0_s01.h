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

        sqr  = Q12_MULT_PRECISE(x, x);
        sqr += Q12_MULT_PRECISE(y, y);
        sqr += Q12_MULT_PRECISE(z, z);
        sqr  = SquareRoot12(sqr);
        
        chara->damage_B4.amount_C += Math_PreservedSignSubtract(sqr, Q12(5.0f));
        if (sqr != Q12(0.0f)) 
        {
            sqr = Q12(Math_PreservedSignSubtract(sqr, Q12(6.0f))) / sqr;
        }

        x = Q12_MULT_PRECISE(x, sqr);
        y = Q12_MULT_PRECISE(y, sqr);
        z = Q12_MULT_PRECISE(z, sqr);
        if (x | y | z)
        {
            chara->damage_B4.position_0.vx += Q12_MULT_PRECISE(x, Q12(0.8f));
            chara->damage_B4.position_0.vy += Q12_MULT_PRECISE(y, Q12(0.8f));
            chara->damage_B4.position_0.vz += Q12_MULT_PRECISE(z, Q12(0.8f));
        }
    }

    arg3->vx = x;
    arg3->vy = y;
    arg3->vz = z;
}
