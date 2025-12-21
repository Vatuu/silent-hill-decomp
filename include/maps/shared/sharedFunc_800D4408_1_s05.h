void sharedFunc_800D4408_1_s05(VECTOR3* arg0, s32 idx, s32 posX, s32 posY, s32 posZ)
{
    typedef struct
    {
        MATRIX  mtx_0;
        SVECTOR field_20;
        VECTOR3 field_28;
    } s_ScratchData;

    s_ScratchData* scratch;
    scratch = PSX_SCRATCH;

    Math_SetSVectorFastSum(&scratch->field_20, posX, posY, posZ);
    scratch->field_20.vz = posZ; // @hack Needed for match.

    Vw_CoordHierarchyMatrixCompute(&sharedData_800D8610_1_s05[idx], &scratch->mtx_0);

    gte_SetRotMatrix(&scratch->mtx_0);
    gte_SetTransMatrix(&scratch->mtx_0);

    gte_ldv0(&scratch->field_20);
    gte_rt();
    gte_stlvnl(&scratch->field_28);

    arg0->vx = Q8_TO_Q12(scratch->field_28.vx);
    arg0->vy = Q8_TO_Q12(scratch->field_28.vy);
    arg0->vz = Q8_TO_Q12(scratch->field_28.vz);
}
