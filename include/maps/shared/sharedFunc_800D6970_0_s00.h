void sharedFunc_800D6970_0_s00(s_SubCharacter* chara, s_AnmHeader* animHdr, GsCOORDINATE2* coord)
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
    s_AnimInfo*                  anim;
    s_sharedFunc_800D6970_0_s00* ptr;

    func_8003DD80(chara->model_0.charaId_0, 2);

    switch (chara->model_0.anim_4.status_0)
    {
        case 14:
            STALKER_ANIM_INFOS[14].endKeyframeIdx_E = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 50;
            break;

        case 15:
            STALKER_ANIM_INFOS[15].startKeyframeIdx_C = (chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 50);

            if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 49 &&
                FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 59)
            {
                STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant = Q12(24.0f);
            }
            else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 58 &&
                     FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 66)
            {
                STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant = Q12(32.0f);
            }
            else
            {
                STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant = FP_MULTIPLY_PRECISE(MAX(chara->moveSpeed_38, Q12(0.1f)), Q12(30.67f), Q12_SHIFT);
            }
            break;

        case 75:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant = FP_MULTIPLY_PRECISE(MAX(chara->moveSpeed_38, Q12(1.5f)), Q12(30.67f), Q12_SHIFT);
            break;

        case 61:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant = FP_MULTIPLY_PRECISE(MAX(chara->moveSpeed_38, Q12(0.1f)), Q12(30.67f), Q12_SHIFT);
            break;

        case 2:
        case 84:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].endKeyframeIdx_E = chara->properties_E4.larvalStalker.properties_E8[5].val16[1];
            break;

        case 3:
        case 85:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C = chara->properties_E4.larvalStalker.properties_E8[5].val16[1];
            break;

        case 6:
        case 86:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].endKeyframeIdx_E = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 9;
            break;

        case 7:
        case 87:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 9;
            break;

        case 8:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].endKeyframeIdx_E = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 20;
            break;

        case 9:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 20;
            break;

        case 10:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].endKeyframeIdx_E = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 25;
            break;

        case 11:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 25;
            break;

        case 48:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].endKeyframeIdx_E = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 395;
            break;

        case 49:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 395;
            break;
    }

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coord);

    anim = &STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0];
    anim->updateFunc_0(&chara->model_0, animHdr, coord, anim);

    ptr = PSX_SCRATCH;

    if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 59 &&
        FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 66)
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
        ptr->field_20.vx = ptr->field_20.vx * 16;
        ptr->field_20.vy = ptr->field_20.vy * 16;
        ptr->field_20.vz = ptr->field_20.vz * 16;

        ptr->position_38.vx = chara->position_18.vx;
        ptr->position_38.vy = chara->position_18.vy + chara->field_C8.field_8;
        ptr->position_38.vz = chara->position_18.vz;

        // TODO: What's weapon attack 48?
        func_8008A0E4(1, 48, chara, &ptr->position_38, &g_SysWork.player_4C.chara_0,
                      ratan2(ptr->field_20.vx - chara->position_18.vx, ptr->field_20.vz - chara->position_18.vz),
                      ratan2(Math_Vector2MagCalc(chara->position_18.vx - ptr->field_20.vx,
                                                 chara->position_18.vz - ptr->field_20.vz),
                             ptr->field_20.vy - (chara->position_18.vy + chara->field_C8.field_8)));
    }

    ptr->angle_44 = chara->properties_E4.larvalStalker.properties_E8[11].val16[0];

    if (chara->model_0.state_2 == 2 || chara->model_0.state_2 == 3)
    {
        ptr->angle_46 = func_8005BF38((ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                                              g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) -
                                       chara->rotation_24.vy));
        temp          = Math_Vector2MagCalc(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx,
                                            g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);

        if (temp < Q12(3.0f) && ABS(ptr->angle_46) < FP_ANGLE(45.0f))
        {
            if (sharedData_800E3A18_0_s00 == chara->properties_E4.player.field_F0 &&
                sharedData_800E3A1C_0_s00 == chara->properties_E4.player.field_F4)
            {
                if (ptr->angle_46 > 0)
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

    chara->properties_E4.larvalStalker.properties_E8[11].val16[0] = ptr->angle_44;
}
