s32 sharedFunc_800DC598_2_s00(s_SubCharacter* airScreamer)
{
    s32 ret;
    u8  animStatus;

    ret        = 0;
    animStatus = airScreamer->model_0.anim_4.status_0;

    if (animStatus == ANIM_STATUS(25, true) ||
        animStatus == ANIM_STATUS(23, true))
    {
        if (airScreamer->position_18.vy < (Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz) - Q12(0.7f)))
        {
            if (sharedFunc_800DC200_2_s00(airScreamer) && airScreamer->moveSpeed_38 > Q12(1.5f))
            {
                ret = 2;
            }
            else
            {
                func_8006F250(sharedData_800E2370_0_s01, airScreamer->position_18.vx, airScreamer->position_18.vz, 0, 0);

                if (sharedData_800E2370_0_s01[1] < ((airScreamer->position_18.vy + airScreamer->field_C8.field_0) - Q12(2.0f)))
                {
                    ret = 1;
                }
            }
        }
    }

    return ret;
}
