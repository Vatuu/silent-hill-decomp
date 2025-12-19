void sharedFunc_800D0F28_3_s03(s_SubCharacter* bloodsucker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    typedef struct
    {
        MATRIX   field_0;
        SVECTOR3 field_20;
        u8       unk_26[2];
        VECTOR3  field_28;
        u8       unk_34[4];
        VECTOR3  field_38;
    } s_sharedFunc_800D0F28_3_s03;

    s_AnimInfo*                  animInfo;
    s_sharedFunc_800D0F28_3_s03* scratchData;

    scratchData = PSX_SCRATCH;

    Math_MatrixTransform(&bloodsucker->position_18, &bloodsucker->rotation_24, coords);
    animInfo = &BLOODSUCKER_ANIM_INFOS[bloodsucker->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&bloodsucker->model_0, anmHdr, coords, animInfo);
    Vw_CoordHierarchyMatrixCompute(&coords[14], &scratchData->field_0);

    gte_SetRotMatrix(&scratchData->field_0);
    gte_SetTransMatrix(&scratchData->field_0);

    Math_SetSVectorFast(&scratchData->field_20, 0, 0, 0);

    gte_ldv0(&scratchData->field_20);
    gte_rt();
    gte_stlvnl(&scratchData->field_28);

    scratchData->field_28.vx = Q8_TO_Q12(scratchData->field_28.vx);
    scratchData->field_28.vy = Q8_TO_Q12(scratchData->field_28.vy);
    scratchData->field_28.vz = Q8_TO_Q12(scratchData->field_28.vz);

    bloodsucker->field_C8.field_0   = scratchData->field_28.vy - Q12(0.05f);
    bloodsucker->field_C8.field_2   = scratchData->field_28.vy + Q12(0.05f);
    bloodsucker->field_C8.field_4   = scratchData->field_28.vy + Q12(0.05f);
    bloodsucker->field_C8.field_6   = scratchData->field_28.vy;
    bloodsucker->field_D8.offsetX_0 = scratchData->field_28.vx - bloodsucker->position_18.vx;
    bloodsucker->field_D8.offsetZ_2 = scratchData->field_28.vz - bloodsucker->position_18.vz;
    bloodsucker->field_D4.field_2   = Q12(0.05f);
    bloodsucker->field_D8.offsetX_4 = scratchData->field_28.vx - bloodsucker->position_18.vx;
    bloodsucker->field_D8.offsetZ_6 = scratchData->field_28.vz - bloodsucker->position_18.vz;
    bloodsucker->field_D4.field_0   = Q12(0.05f);
    Math_SetSVectorFast(&scratchData->field_20, 0, -22, 0);

    gte_ldv0(&scratchData->field_20);
    gte_rt();
    gte_stlvnl(&scratchData->field_28);

    scratchData->field_28.vx = Q8_TO_Q12(scratchData->field_28.vx);
    scratchData->field_28.vy = Q8_TO_Q12(scratchData->field_28.vy);
    scratchData->field_28.vz = Q8_TO_Q12(scratchData->field_28.vz);
    scratchData->field_38.vx = scratchData->field_28.vx;
    scratchData->field_38.vy = scratchData->field_28.vy;
    scratchData->field_38.vz = scratchData->field_28.vz;

    bloodsucker->field_44.field_0 = 1;

    // TODO: 0x45 should be `WEAPON_ATTACK` macro?
    func_8008A0E4(1, 0x45, bloodsucker, &scratchData->field_38, &g_SysWork.playerWork_4C, FP_ANGLE(90.0f), FP_ANGLE(90.0f));
}
