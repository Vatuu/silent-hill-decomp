void sharedFunc_800D6970_0_s00(s_SubCharacter* stalker, s_AnmHeader* animHdr, GsCOORDINATE2* coord)
{
    typedef struct
    {
        MATRIX  field_0;
        VECTOR  field_20; // Q23.8, then Q10.12.
        SVECTOR field_30;
        VECTOR3 position_38;
        q3_12   angle_44;
        q3_12   angle_46;
    } s_sharedFunc_800D6970_0_s00;

    s32                          temp;
    s_AnimInfo*                  animInfo;
    s_sharedFunc_800D6970_0_s00* ptr;

    #define stalkerProps stalker->properties_E4.stalker

    func_8003DD80(stalker->model_0.charaId_0, 2);

    switch (stalker->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(StalkerAnim_7, false):
            STALKER_ANIM_INFOS[ANIM_STATUS(StalkerAnim_7, false)].endKeyframeIdx_E = stalkerProps.relKeyframeIdx_FE + 50;
            break;

        case ANIM_STATUS(StalkerAnim_7, true):
            STALKER_ANIM_INFOS[ANIM_STATUS(StalkerAnim_7, true)].startKeyframeIdx_C = (stalkerProps.relKeyframeIdx_FE + 50);

            if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 50, 58))
            {
                STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant = Q12(24.0f);
            }
            else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 59, 65))
            {
                STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant = Q12(32.0f);
            }
            else
            {
                STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant = FP_MULTIPLY_PRECISE(MAX(stalker->moveSpeed_38, Q12(0.1f)), Q12(30.67f), Q12_SHIFT);
            }
            break;

        case ANIM_STATUS(StalkerAnim_37, true):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant = FP_MULTIPLY_PRECISE(MAX(stalker->moveSpeed_38, Q12(1.5f)), Q12(30.67f), Q12_SHIFT);
            break;

        case ANIM_STATUS(StalkerAnim_30, true):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant = FP_MULTIPLY_PRECISE(MAX(stalker->moveSpeed_38, Q12(0.1f)), Q12(30.67f), Q12_SHIFT);
            break;

        case ANIM_STATUS(StalkerAnim_1, false):
        case ANIM_STATUS(StalkerAnim_42, false):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].endKeyframeIdx_E = stalkerProps.relKeyframeIdx_FE;
            break;

        case ANIM_STATUS(StalkerAnim_1, true):
        case ANIM_STATUS(StalkerAnim_42, true):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].startKeyframeIdx_C = stalkerProps.relKeyframeIdx_FE;
            break;

        case ANIM_STATUS(StalkerAnim_3, false):
        case ANIM_STATUS(StalkerAnim_43, false):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].endKeyframeIdx_E = stalkerProps.relKeyframeIdx_FE + 9;
            break;

        case ANIM_STATUS(StalkerAnim_3, true):
        case ANIM_STATUS(StalkerAnim_43, true):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].startKeyframeIdx_C = stalkerProps.relKeyframeIdx_FE + 9;
            break;

        case ANIM_STATUS(StalkerAnim_4, false):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].endKeyframeIdx_E = stalkerProps.relKeyframeIdx_FE + 20;
            break;

        case ANIM_STATUS(StalkerAnim_4, true):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].startKeyframeIdx_C = stalkerProps.relKeyframeIdx_FE + 20;
            break;

        case ANIM_STATUS(StalkerAnim_5, false):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].endKeyframeIdx_E = stalkerProps.relKeyframeIdx_FE + 25;
            break;

        case ANIM_STATUS(StalkerAnim_5, true):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].startKeyframeIdx_C = stalkerProps.relKeyframeIdx_FE + 25;
            break;

        case ANIM_STATUS(StalkerAnim_24, false):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].endKeyframeIdx_E = stalkerProps.relKeyframeIdx_FE + 395;
            break;

        case ANIM_STATUS(StalkerAnim_24, true):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].startKeyframeIdx_C = stalkerProps.relKeyframeIdx_FE + 395;
            break;
    }

    Math_MatrixTransform(&stalker->position_18, &stalker->rotation_24, coord);

    animInfo = &STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&stalker->model_0, animHdr, coord, animInfo);

    ptr = PSX_SCRATCH;

    if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 60, 65))
    {
        // TODO: Use macro?
        *(s32*)&ptr->field_30.vx = 0x21FFFB;
        ptr->field_30.vz         = 0x25;
        Vw_CoordHierarchyMatrixCompute(&coord[6], &ptr->field_0);

        gte_SetRotMatrix(&ptr->field_0);
        gte_SetTransMatrix(&ptr->field_0);
        gte_ldv0(&ptr->field_30);
        gte_rt();
        gte_stlvnl(&ptr->field_20);

        // TODO: Q conversion. From Q8 to Q12?
        ptr->field_20.vx = Q8_TO_Q12(ptr->field_20.vx);
        ptr->field_20.vy = Q8_TO_Q12(ptr->field_20.vy);
        ptr->field_20.vz = Q8_TO_Q12(ptr->field_20.vz);

        ptr->position_38.vx = stalker->position_18.vx;
        ptr->position_38.vy = stalker->position_18.vy + stalker->field_C8.field_8;
        ptr->position_38.vz = stalker->position_18.vz;

        // TODO: What's weapon attack 48?
        func_8008A0E4(1, 48, stalker, &ptr->position_38, &g_SysWork.playerWork_4C.player_0,
                      ratan2(ptr->field_20.vx - stalker->position_18.vx, ptr->field_20.vz - stalker->position_18.vz),
                      ratan2(Math_Vector2MagCalc(stalker->position_18.vx - ptr->field_20.vx,
                                                 stalker->position_18.vz - ptr->field_20.vz),
                             ptr->field_20.vy - (stalker->position_18.vy + stalker->field_C8.field_8)));
    }

    ptr->angle_44 = stalkerProps.angle_114;

    if (stalker->model_0.controlState_2 == StalkerControl_2 ||
        stalker->model_0.controlState_2 == StalkerControl_3)
    {
        ptr->angle_46 = func_8005BF38(Math_AngleBetweenPositionsGet(stalker->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                      stalker->rotation_24.vy);
        temp          = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                            g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);

        if (temp < Q12(3.0f) && ABS(ptr->angle_46) < FP_ANGLE(45.0f))
        {
            if (sharedData_800E3A18_0_s00 == stalkerProps.targetPositionX_F0 &&
                sharedData_800E3A1C_0_s00 == stalkerProps.targetPositionZ_F4)
            {
                if (ptr->angle_46 > FP_ANGLE(0.0f))
                {
                    ptr->angle_44 = CLAMP_HIGH(ptr->angle_46, ptr->angle_44 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT));
                }
                else
                {
                    ptr->angle_44 = MAX(ptr->angle_46, ptr->angle_44 - FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT));
                }
            }
        }
        else
        {
            if (ptr->angle_44 > FP_ANGLE(0.0f))
            {
                ptr->angle_44 = CLAMP_LOW(ptr->angle_44 - FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT), FP_ANGLE(0.0f));
            }
            else
            {
                ptr->angle_44 = MIN(ptr->angle_44 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT), FP_ANGLE(0.0f));
            }
        }
    }
    else
    {
        if (ptr->angle_44 > FP_ANGLE(0.0f))
        {
            ptr->angle_44 = CLAMP_LOW(ptr->angle_44 - FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT), FP_ANGLE(0.0f));
        }
        else
        {
            ptr->angle_44 = MIN(ptr->angle_44 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(45.0f), Q12_SHIFT), FP_ANGLE(0.0f));
        }
    }

    ptr->field_30.vz         = 0;
    *(s32*)&ptr->field_30.vx = ptr->angle_44 << 16;

    Math_RotMatrixZxyNegGte(&ptr->field_30, &ptr->field_0);
    MulMatrix(&coord[3].coord, &ptr->field_0);

    stalkerProps.angle_114 = ptr->angle_44;

    #undef stalkerProps
}
