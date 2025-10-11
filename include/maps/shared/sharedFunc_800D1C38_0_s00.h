void sharedFunc_800D1C38_0_s00(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord)
{
    s_Collision coll;
    VECTOR3     offset;
    s32         headingAngle;
    s16         temp_v0;
    s32         temp_s0;
    s32         moveAmt;
    s32         temp_s2;
    s16         temp_s3;
    s32         scaleRestoreShift;
    u32         scaleReduceShift;
    s32         moveSpeed;
    bool        cond;
    s16         var_s0;
    s16         var_v1;

    cond = false;
    if (g_SysWork.player_4C.extra_128.state_1C < PlayerState_Unk58)
    {
        cond = true;
    }
#if defined(MAP0_S00)
    else if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_Unk74)
    {
        cond = g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP1_S02;
    }
#elif defined(MAP0_S01)
    if (g_SysWork.player_4C.extra_128.state_1C == PlayerState_Unk53)
    {
        cond = false;
    }
#endif

    if (cond)
    {
        Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);

        temp_s2 = Math_Sin(chara->headingAngle_3C);
        temp_s2 = FP_MULTIPLY(chara->moveSpeed_38, temp_s2, Q12_SHIFT);
        temp_s0 = Math_Cos(chara->headingAngle_3C);
        temp_s0 = FP_MULTIPLY(chara->moveSpeed_38, temp_s0, Q12_SHIFT);

        temp_s3 = Math_Cos(ABS(coll.field_4) >> 3); // `/ 8`.
        temp_v0 = Math_Cos(ABS(coll.field_6) >> 3); // `/ 8`.

        var_s0 = FP_MULTIPLY(FP_MULTIPLY(temp_s2, temp_s3, Q12_SHIFT), temp_s3, Q12_SHIFT);
        var_v1 = FP_MULTIPLY(FP_MULTIPLY(temp_s0, temp_v0, Q12_SHIFT), temp_v0, Q12_SHIFT);
    }
    else
    {
        var_s0 = FP_MULTIPLY(chara->moveSpeed_38, Math_Sin(chara->headingAngle_3C), Q12_SHIFT);
        var_v1 = FP_MULTIPLY(chara->moveSpeed_38, Math_Cos(chara->headingAngle_3C), Q12_SHIFT);
    }

    if (chara->moveSpeed_38 >= 0)
    {
        chara->moveSpeed_38 = SquareRoot0(SQUARE(var_s0) + SQUARE(var_v1));
    }
    else
    {
        chara->moveSpeed_38 = -SquareRoot0(SQUARE(var_s0) + SQUARE(var_v1));
    }

    moveSpeed    = chara->moveSpeed_38;
    headingAngle = chara->headingAngle_3C;
    moveAmt      = FP_MULTIPLY_PRECISE(moveSpeed, g_DeltaTime0, Q12_SHIFT);

    scaleRestoreShift = OVERFLOW_GUARD(moveAmt);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    offset.vz = FP_MULTIPLY_PRECISE(moveAmt >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift, Q12_SHIFT) << scaleRestoreShift;
    offset.vy = FP_MULTIPLY_PRECISE(chara->field_34, g_DeltaTime0, Q12_SHIFT);

    if (cond)
    {
        // Most maps use `D_800C4590` from bodyprog, but some use struct from inside map overlay.
        // TODO: Not sure if these should be sharedData or not, maybe need to check if data matches.
#if defined(MAP0_S00)
    #define UnkStruct D_800E39BC
#elif defined(MAP2_S01)
    #define UnkStruct D_800D16BC
#elif defined(MAP3_S00)
    #define UnkStruct D_800D5CD0
#elif defined(MAP3_S06)
    #define UnkStruct D_800D5EA8
#elif defined(MAP6_S01)
    #define UnkStruct D_800D5314
#elif defined(MAP6_S04)
    #define UnkStruct D_800ED4C0
#else
    #define UnkStruct D_800C4590
#endif
        func_80069B24(&UnkStruct, &offset, chara);
        chara->position_18.vx += UnkStruct.offset_0.vx;
        chara->position_18.vy += UnkStruct.offset_0.vy;
        chara->position_18.vz += UnkStruct.offset_0.vz;

        if (UnkStruct.field_14 == 0)
        {
            UnkStruct.field_C = chara->properties_E4.player.positionY_EC;
        }

        if (chara->position_18.vy > UnkStruct.field_C)
        {
            chara->position_18.vy = UnkStruct.field_C;
            chara->field_34       = 0;
        }
    }
    else
    {
        chara->position_18.vx += offset.vx;
        chara->position_18.vz += offset.vz;

        if (g_SysWork.player_4C.extra_128.state_1C < PlayerState_Unk87 ||
            (g_SysWork.player_4C.extra_128.state_1C >= PlayerState_Unk89 && g_SysWork.player_4C.extra_128.state_1C != PlayerState_Unk106))
        {
            chara->position_18.vy = Q12(0.0f);
        }

        chara->field_34 = 0;
    }

    if (g_DeltaTime0 == Q12(0.0f))
    {
        chara->rotationSpeed_2C.vy = FP_ANGLE(0.0f);
    }
    else
    {
        chara->rotationSpeed_2C.vy = (sharedData_800E39D8_0_s00 << 8) / g_DeltaTime0;
    }

    coord->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coord->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coord->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);
}
