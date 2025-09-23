s32 sharedFunc_800D7440_0_s01(VECTOR* vec0, VECTOR* vec1, s_SubCharacter* chara)
{
    s32     temp_s2;
    s32     posY;
    s32     result;
    s32     cond;
    VECTOR* vecCpy;

    vecCpy = vec0;

    sharedFunc_800D81D0_0_s01(chara);
    sharedFunc_800D8714_0_s01(chara, chara->moveSpeed_38, chara->headingAngle_3C);
    sharedFunc_800D87FC_0_s01(chara);

    result = func_80069B24(vecCpy, vec1, chara);

    posY    = chara->position_18.vy;
    temp_s2 = func_80080884(chara->position_18.vx + vecCpy->vx,
                            chara->position_18.vz + vecCpy->vz);

    if (sharedFunc_800D4A80_0_s01(chara) != 4)
    {
        if (vec1->vy > 0 && temp_s2 < (posY - Q12(0.5f)))
        {
            vecCpy->vx = 0;
            vecCpy->vz = 0;
        }
    }
    else if (temp_s2 < posY)
    {
        vecCpy->vx = 0;
        vecCpy->vz = 0;
    }

    if ((FP_FROM(vec1->vx, Q4_SHIFT) != FP_FROM(vecCpy->vx, Q4_SHIFT)) ||
        (FP_FROM(vec1->vz, Q4_SHIFT) != FP_FROM(vecCpy->vz, Q4_SHIFT)))
    {
        result = 1;
    }

    sharedFunc_800D8244_0_s01(chara);
    return result;
}
