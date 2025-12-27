void sharedFunc_800D267C_1_s05(s_SubCharacter* splitHead)
{
    s_800C4590 sp18;
    VECTOR3    pos;

    splitHead->headingAngle_3C = splitHead->rotation_24.vy;

    sharedFunc_800D4408_1_s05(&pos, 2, 0, -57, 3);

    splitHead->field_D8.offsetX_4 = pos.vx - splitHead->position_18.vx;
    splitHead->field_C8.field_0   = pos.vy;
    splitHead->field_D8.offsetZ_6 = pos.vz - splitHead->position_18.vz;

    if (ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0) == SplitHeadAnim_2 ||
        ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0) == SplitHeadAnim_14)
    {
        splitHead->field_D4.field_0 = Q12(1.3f);
    }
    else
    {
        splitHead->field_D4.field_0 = Q12(1.7f);
    }

    splitHead->field_E1_0 = 4;

    func_8005CB20(splitHead, &sp18, sharedData_800D8614_1_s05, sharedData_800D8616_1_s05);

    sharedData_800D8614_1_s05 = 0;
    sharedData_800D8616_1_s05 = 0;
}
