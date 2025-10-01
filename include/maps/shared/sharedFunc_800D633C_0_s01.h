void sharedFunc_800D633C_0_s01(s_SubCharacter* arg0)
{
    s32 someY;

    func_8006F250(&sharedData_800E2370_0_s01, arg0->position_18.vx, arg0->position_18.vz, 0, 0);
    someY = sharedData_800E2370_0_s01[1] - arg0->field_C8;
    if (arg0->position_18.vy < someY)
    {
        arg0->position_18.vy = someY;
    }
}
