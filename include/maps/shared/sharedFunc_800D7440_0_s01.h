s32 sharedFunc_800D7440_0_s01(s_800C4590* arg0, VECTOR* offset, s_SubCharacter* airScreamer)
{
    s32         newPosY;
    s32         posY;
    s32         result;
    s32         cond;
    s_800C4590* arg0Cpy;

    arg0Cpy = arg0;

    sharedFunc_800D81D0_0_s01(airScreamer);
    sharedFunc_800D8714_0_s01(airScreamer, airScreamer->moveSpeed_38, airScreamer->headingAngle_3C);
    sharedFunc_800D87FC_0_s01(airScreamer);

    result = func_80069B24(arg0Cpy, offset, airScreamer);

    posY    = airScreamer->position_18.vy;
    newPosY = func_80080884(airScreamer->position_18.vx + arg0Cpy->offset_0.vx,
                            airScreamer->position_18.vz + arg0Cpy->offset_0.vz);

    if (sharedFunc_800D4A80_0_s01(airScreamer) != 4)
    {
        if (offset->vy > Q12(0.0f) && newPosY < (posY - Q12(0.5f)))
        {
            arg0Cpy->offset_0.vx = Q12(0.0f);
            arg0Cpy->offset_0.vz = Q12(0.0f);
        }
    }
    else if (newPosY < posY)
    {
        arg0Cpy->offset_0.vx = Q12(0.0f);
        arg0Cpy->offset_0.vz = Q12(0.0f);
    }

    if ((FP_FROM(offset->vx, Q4_SHIFT) != FP_FROM(arg0Cpy->offset_0.vx, Q4_SHIFT)) ||
        (FP_FROM(offset->vz, Q4_SHIFT) != FP_FROM(arg0Cpy->offset_0.vz, Q4_SHIFT)))
    {
        result = 1;
    }

    sharedFunc_800D8244_0_s01(airScreamer);
    return result;
}
