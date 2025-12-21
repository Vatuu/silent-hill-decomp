void sharedFunc_800D267C_1_s05(s_SubCharacter* splithead)
{
    s_800C4590 sp18;
    VECTOR3    sp38;

    splithead->headingAngle_3C = splithead->rotation_24.vy;

    sharedFunc_800D4408_1_s05(&sp38, 2, 0, -57, 3);

    splithead->field_D8.offsetX_4 = sp38.vx - splithead->position_18.vx;
    splithead->field_C8.field_0   = sp38.vy;
    splithead->field_D8.offsetZ_6 = sp38.vz - splithead->position_18.vz;

    if (ANIM_STATUS_IDX_GET(splithead->model_0.anim_4.status_0) == 2 ||
        ANIM_STATUS_IDX_GET(splithead->model_0.anim_4.status_0) == 0xE)
    {
        splithead->field_D4.field_0 = Q12(1.3f);
    }
    else
    {
        splithead->field_D4.field_0 = Q12(1.7f);
    }

    splithead->field_E1_0 = 4;

    func_8005CB20(splithead, &sp18, sharedData_800D8614_1_s05, sharedData_800D8616_1_s05);

    sharedData_800D8614_1_s05 = 0;
    sharedData_800D8616_1_s05 = 0;
}
