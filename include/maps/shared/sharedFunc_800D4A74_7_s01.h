void sharedFunc_800D4A74_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coord)
{
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

    // Overflow guard, scale large `moveAmt` before trigonometric multiplication.
    // "Range-based scaling mechanism common in fixed-point DSP or low-level game engine math." - chatgpt
    scaleRestoreShift = ((u32)(moveAmt + SHRT_MAX) >= USHRT_MAX) ? 4 : 0;
    scaleReduceShift  = scaleRestoreShift >> 1;

    vec.vx = (u32)FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    vec.vz = (u32)FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    vec.vy = FP_MULTIPLY_PRECISE(chara->field_34, g_DeltaTime0, Q12_SHIFT);

    chara->position_18.vx += vec.vx;
    chara->position_18.vy  = 0;
    chara->position_18.vz += vec.vz;

    coord->coord.t[0] = FP_FROM(chara->position_18.vx, Q4_SHIFT);
    coord->coord.t[1] = FP_FROM(chara->position_18.vy, Q4_SHIFT);
    coord->coord.t[2] = FP_FROM(chara->position_18.vz, Q4_SHIFT);
}
