void sharedFunc_800CD2C8_2_s01(s_SubCharacter* chara, GsCOORDINATE2* coord)
{
/* TODO: We probably want to make this sharedData.
 * Similar ifdef block is in include/maps/shared/sharedFunc_800D1C38_0_s00.h
 */
#if defined(MAP2_S01)
    #define UnkStruct D_800D16BC
#elif defined(MAP3_S06)
    #define UnkStruct D_800D5EA8
#elif defined(MAP6_S01)
    #define UnkStruct D_800D5314
#elif defined(MAP6_S04)
    #define UnkStruct D_800ED4C0
#elif defined(MAP7_S03)
    #define UnkStruct D_800F23D8
#elif defined(MAP7_S02)
    #define UnkStruct D_800EB604
#endif

    VECTOR3 unused;
    VECTOR3 vec;
    s32     moveSpeed;
    s16     headingAngle;
    s32     moveAmt;
    s32     scaleRestoreShift;
    u32     scaleReduceShift;

    unused       = chara->position_18;
    moveSpeed    = chara->moveSpeed_38;
    headingAngle = chara->headingAngle_3C;
    moveAmt      = FP_MULTIPLY_PRECISE(moveSpeed, g_DeltaTime0, Q12_SHIFT);

    scaleRestoreShift = OVERFLOW_GUARD(moveAmt);
    scaleReduceShift  = scaleRestoreShift >> 1;

    vec.vx = (u32)FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    vec.vz = (u32)FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    vec.vy = FP_MULTIPLY_PRECISE(chara->field_34, g_DeltaTime0, Q12_SHIFT);

    func_80069B24(&UnkStruct, &vec, chara);

    chara->position_18.vx += vec.vx;
    chara->position_18.vy  = 0;
    chara->position_18.vz += vec.vz;

    if (chara->position_18.vy > UnkStruct.field_C)
    {
        chara->position_18.vy = UnkStruct.field_C;
        chara->field_34 = 0;
    }
    coord->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coord->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coord->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);
}
