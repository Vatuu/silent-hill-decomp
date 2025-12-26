s32 sharedFunc_800D7440_0_s01(s_800C4590* arg0, VECTOR* offset, s_SubCharacter* airScreamer)
{
    q19_12      groundHeight;
    q19_12      posY;
    s32         result;
    s32         cond;
    s_800C4590* localArg0C;

    localArg0C = arg0;

    sharedFunc_800D81D0_0_s01(airScreamer);
    sharedFunc_800D8714_0_s01(airScreamer, airScreamer->moveSpeed_38, airScreamer->headingAngle_3C);
    sharedFunc_800D87FC_0_s01(airScreamer);

    result = func_80069B24(localArg0C, offset, airScreamer);

    posY         = airScreamer->position_18.vy;
    groundHeight = Collision_GroundHeightGet(airScreamer->position_18.vx + localArg0C->offset_0.vx, airScreamer->position_18.vz + localArg0C->offset_0.vz);

    if (sharedFunc_800D4A80_0_s01(airScreamer) != 4)
    {
        if (offset->vy > Q12(0.0f) && groundHeight < (posY - Q12(0.5f)))
        {
            localArg0C->offset_0.vx = Q12(0.0f);
            localArg0C->offset_0.vz = Q12(0.0f);
        }
    }
    else if (groundHeight < posY)
    {
        localArg0C->offset_0.vx = Q12(0.0f);
        localArg0C->offset_0.vz = Q12(0.0f);
    }

    if ((FP_FROM(offset->vx, Q4_SHIFT) != FP_FROM(localArg0C->offset_0.vx, Q4_SHIFT)) ||
        (FP_FROM(offset->vz, Q4_SHIFT) != FP_FROM(localArg0C->offset_0.vz, Q4_SHIFT)))
    {
        result = 1;
    }

    sharedFunc_800D8244_0_s01(airScreamer);
    return result;
}
