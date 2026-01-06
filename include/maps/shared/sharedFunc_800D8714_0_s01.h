void sharedFunc_800D8714_0_s01(s_SubCharacter* airScreamer, q19_12 moveSpeed, q19_12 headingAngle)
{
    q19_12           adjHeadingAngle;
    q19_12           moveDist;
    q19_12           moveDistBase;
    s32              idx;
    q19_12           offsetX;
    q19_12           offsetZ;
    s16*             ptr;
    s_func_800D2E04* base;

    adjHeadingAngle = headingAngle;
    idx = sharedFunc_800D4A80_0_s01(airScreamer);
    base = &sharedData_800CAA98_0_s01;
    moveDistBase = base->field_D5C[idx][1];
    airScreamer->field_C8.field_2 = base->field_D5C[idx][0];

    if (moveSpeed == Q12(0.0f)) 
    {
        airScreamer->field_D8.offsetX_4 = Q12(0.0f);
        airScreamer->field_D8.offsetZ_6 = Q12(0.0f);
        airScreamer->field_D4.radius_0  = moveDistBase;
        return;
    }

    moveDist = moveDistBase - Q12(0.4f);
    if (moveDist < Q12(0.0f))
    {
        moveDist = Q12(0.0f);
    }

    if (moveSpeed < Q12(0.0f))
    {
        adjHeadingAngle ^= FP_ANGLE(180.0f);
    }

    offsetX = Q12_MULT_PRECISE(moveDist, Math_Sin(adjHeadingAngle));
    offsetZ = Q12_MULT_PRECISE(moveDist, Math_Cos(adjHeadingAngle));

    airScreamer->field_D8.offsetX_4 = offsetX;
    airScreamer->field_D8.offsetZ_6 = offsetZ;
    airScreamer->field_D4.radius_0   = Q12(0.4f);
}
