void sharedFunc_800D5E78_0_s01(s_SubCharacter* chara, q19_12 angle) // 0x800D5E78
{
    q19_12                       angleDelta;
    q19_12                       angleCpy;
    q19_12                       angle0;
    s_sharedData_800E21D0_0_s01* base;
    s32                          idx0;

    angleCpy = angle;

    if (angleCpy > FP_ANGLE(60.0f))
    {
        angleCpy = FP_ANGLE(60.0f);
    }
    else if (angleCpy < FP_ANGLE(-60.0f))
    {
        angleCpy = FP_ANGLE(-60.0f);
    }

    angleDelta = angleCpy - chara->field_2A;

    if (angleDelta > FP_ANGLE(0.5f))
    {
        angleDelta -= FP_ANGLE(0.5f);
    }
    else if (angleDelta >= FP_ANGLE(-0.5f))
    {
        angleDelta = FP_ANGLE(0.0f);
    }
    else
    {
        angleDelta += FP_ANGLE(0.5f);
    }

    angle0 = FP_ANGLE(90.0f);
    if (angleDelta <= FP_ANGLE(0.0f))
    {
        angle0 = FP_ANGLE(0.0f);
        if (angleDelta < FP_ANGLE(0.0f))
        {
            angle0 = FP_ANGLE(-90.0f);
        }
    }

    base                    = &sharedData_800E21D0_0_s01;
    idx0                    = 5;
    base->field_B4[idx0][2] = angle0;
    base->field_B4[idx0][1] = 0x1800;
    base->field_B4[idx0][3] = angleDelta;
    base->field_B4[idx0][0] = 1;
}
