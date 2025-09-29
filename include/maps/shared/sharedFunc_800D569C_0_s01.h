s32 sharedFunc_800D569C_0_s01(s_SubCharacter* chara, q19_12 vecY, q19_12 dist)
{
    q19_12 posY;
    s32    someY;
    s32    calcY;
    q19_12 vecYCpy;
    q19_12 distCpy;

    q19_12 vec_x;
    q19_12 vec_z;

    vecYCpy = vecY;
    posY    = chara->position_18.vy;
    distCpy = dist;
    calcY   = func_80080884(chara->position_18.vx, chara->position_18.vz);
    // @hack: We should not mix unions (npc vs larvalStalker).
    someY = chara->properties_E4.npc.field_124;

    vec_x = chara->properties_E4.unk0.field_110.vx;
    vec_z = chara->properties_E4.unk0.field_110.vz;

    if (someY < calcY)
    {
        calcY = someY;
    }

    calcY -= Q12(1.7f);
    someY  = func_800808AC(vec_x, vec_z); // collision type ? this returns `caseVar` from func_8008076C

    if (someY == 12 || someY == 0 || someY == 7)
    {
        distCpy = 0;
    }
    if (posY < calcY)
    {
        calcY = posY;
    }
    if (distCpy > Q12(12.0f))
    {
        vecYCpy = calcY;
    }
    else if (distCpy > Q12(4.0f))
    {
        someY    = FP_TO(distCpy - Q12(4.0f), Q12_SHIFT) / Q12(8.0f);
        vecYCpy += FP_MULTIPLY_PRECISE((calcY - vecYCpy), someY, Q12_SHIFT);
    }

    if (vecYCpy < sharedFunc_800D5274_0_s01())
    {
        vecYCpy = sharedFunc_800D5274_0_s01();
    }

    return vecYCpy;
}
