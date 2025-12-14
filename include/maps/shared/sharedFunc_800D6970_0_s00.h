void sharedFunc_800D6970_0_s00(s_SubCharacter* chara, s_AnmHeader* anim, GsCOORDINATE2* coord)
{
    typedef struct
    {
        MATRIX  field_0;
        VECTOR  field_20;
        SVECTOR field_30;
        VECTOR3 field_38;
        s16     field_44;
        s16     field_46;
    } s_sharedFunc_800D6970_0_s00;

    s_AnimInfo*                  temp_a3;
    s_sharedFunc_800D6970_0_s00* ptr;
    s32                          temp;

    func_8003DD80(chara->model_0.charaId_0, 2);

    switch (chara->model_0.anim_4.status_0)
    {
        case 0xE:
            STALKER_ANIM_INFOS[14].endKeyframeIdx_E = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 0x32;
            break;

        case 0xF:
            STALKER_ANIM_INFOS[15].startKeyframeIdx_C = (chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 0x32);

            if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x31 && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x3B)
            {
                STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant = 0x18000;
            }
            else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x3A && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x42)
            {
                STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant = 0x20000;
            }
            else
            {
                STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant = FP_MULTIPLY_PRECISE(MAX(chara->moveSpeed_38, 0x199), 0x1EAB8, Q12_SHIFT);
            }
            break;

        case 0x4B:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant = FP_MULTIPLY_PRECISE(MAX(chara->moveSpeed_38, 0x1800), 0x1EAB8, Q12_SHIFT);
            break;

        case 0x3D:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant = FP_MULTIPLY_PRECISE(MAX(chara->moveSpeed_38, 0x199), 0x1EAB8, Q12_SHIFT);
            break;

        case 0x2:
        case 0x54:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].endKeyframeIdx_E = chara->properties_E4.larvalStalker.properties_E8[5].val16[1];
            break;

        case 0x3:
        case 0x55:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C = chara->properties_E4.larvalStalker.properties_E8[5].val16[1];
            break;

        case 0x6:
        case 0x56:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].endKeyframeIdx_E = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 9;
            break;

        case 0x7:
        case 0x57:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 9;
            break;

        case 0x8:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].endKeyframeIdx_E = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 0x14;
            break;

        case 0x9:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 0x14;
            break;

        case 0xA:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].endKeyframeIdx_E = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 0x19;
            break;

        case 0xB:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 0x19;
            break;

        case 0x30:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].endKeyframeIdx_E = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 0x18B;
            break;

        case 0x31:
            STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C = chara->properties_E4.larvalStalker.properties_E8[5].val16[1] + 0x18B;
            break;
    }

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coord);

    temp_a3 = &STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0];
    temp_a3->updateFunc_0(&chara->model_0, anim, coord, temp_a3);

    ptr = PSX_SCRATCH;

    if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x3B && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x42)
    {
        *(s32*)&ptr->field_30.vx = 0x21FFFB;
        ptr->field_30.vz         = 0x25;
        Vw_CoordHierarchyMatrixCompute(&coord[6], &ptr->field_0);

        gte_SetRotMatrix(&ptr->field_0);
        gte_SetTransMatrix(&ptr->field_0);
        gte_ldv0(&ptr->field_30);
        gte_rt();
        gte_stlvnl(&ptr->field_20);

        ptr->field_20.vx = ptr->field_20.vx * 0x10;
        ptr->field_20.vy = ptr->field_20.vy * 0x10;
        ptr->field_20.vz = ptr->field_20.vz * 0x10;

        ptr->field_38.vx = chara->position_18.vx;
        ptr->field_38.vy = chara->position_18.vy + chara->field_C8.field_8;
        ptr->field_38.vz = chara->position_18.vz;

        func_8008A0E4(1, 0x30, chara, &ptr->field_38, &g_SysWork.player_4C,
                      ratan2(ptr->field_20.vx - chara->position_18.vx, ptr->field_20.vz - chara->position_18.vz),
                      ratan2(SquareRoot0(SQUARE((chara->position_18.vx - ptr->field_20.vx) >> 6) +
                                         SQUARE((chara->position_18.vz - ptr->field_20.vz) >> 6))
                                 << 6,
                             ptr->field_20.vy - (chara->position_18.vy + chara->field_C8.field_8)));
    }

    ptr->field_44 = chara->properties_E4.larvalStalker.properties_E8[0xB].val16[0];

    if (chara->model_0.state_2 == 2 || chara->model_0.state_2 == 3)
    {
        ptr->field_46 = func_8005BF38((ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) - chara->rotation_24.vy));
        temp          = SquareRoot0(SQUARE((g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx) >> 6) + SQUARE((g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) >> 6)) << 6;

        if (temp < 0x3000 && ABS(ptr->field_46) < 0x200)
        {
            if (sharedData_800E3A18_0_s00 == chara->properties_E4.player.field_F0 && sharedData_800E3A1C_0_s00 == chara->properties_E4.player.field_F4)
            {
                if (ptr->field_46 > 0)
                {
                    ptr->field_44 = CLAMP_HIGH(ptr->field_46, ptr->field_44 + FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x200, Q12_SHIFT));
                }
                else
                {
                    ptr->field_44 = MAX(ptr->field_46, ptr->field_44 - FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x200, Q12_SHIFT));
                }
            }
        }
        else
        {
            if (ptr->field_44 > 0)
            {
                ptr->field_44 = CLAMP_LOW(ptr->field_44 - FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x200, Q12_SHIFT), 0);
            }
            else
            {
                ptr->field_44 = MIN(ptr->field_44 + FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x200, Q12_SHIFT), 0);
            }
        }
    }
    else
    {
        if (ptr->field_44 > 0)
        {
            ptr->field_44 = CLAMP_LOW(ptr->field_44 - FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x200, Q12_SHIFT), 0);
        }
        else
        {
            ptr->field_44 = MIN(ptr->field_44 + FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x200, Q12_SHIFT), 0);
        }
    }

    ptr->field_30.vz         = 0;
    *(s32*)&ptr->field_30.vx = ptr->field_44 << 16;

    Math_RotMatrixZxyNegGte(&ptr->field_30, &ptr->field_0);
    MulMatrix(&coord[3].coord, &ptr->field_0);

    chara->properties_E4.larvalStalker.properties_E8[0xB].val16[0] = ptr->field_44;
}
