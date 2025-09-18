
void sharedFunc_800D5B3C_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    s_Collision coll;
    s32         sfx;
    s8          pitch;
    s8          sp2D; // Type asssumed.
    s32         tempVal;

    tempVal = chara->properties_E4.larvalStalker.properties_E8[0].val32;
    if (tempVal != 0 && chara->properties_E4.larvalStalker.properties_E8[0].val32 == 6)
    {
        if (chara->model_0.stateStep_3 == 0)
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(1, false);
            chara->model_0.stateStep_3++;
        }

        if (chara->properties_E4.larvalStalker.properties_E8[4].val32 != 0)
        {
            chara->properties_E4.larvalStalker.properties_E8[0].val32 = 0;
            chara->model_0.stateStep_3 = 0;
            chara->properties_E4.larvalStalker.properties_E8[4].val32 = 0;
        }
    }

    Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch, &sp2D);

    if (chara->properties_E4.larvalStalker.properties_E8[0].val32 == 6)
    {
        if (chara->model_0.anim_4.keyframeIdx_8 < 13)
        {
            sharedFunc_800D908C_0_s00(3, chara, 12, 27, sfx, pitch);
        }
        else if (chara->model_0.anim_4.keyframeIdx_8 < 50)
        {
            sharedFunc_800D908C_0_s00(3, chara, 49, 27, sfx, pitch);
        }
        else
        {
            sharedFunc_800D908C_0_s00(3, chara, 92, 69, sfx, pitch);
        }
    }

    chara->headingAngle_3C =
    chara->rotation_24.vy  = FP_ANGLE_NORM_U((chara->rotation_24.vy + (sharedData_800E2C38_7_s01 >> 4)) + FP_ANGLE(360.0f));

    chara->moveSpeed_38 = chara->properties_E4.larvalStalker.properties_E8[15].val16[1];
    chara->field_34    += g_DeltaTime2;

    coords->flg = false;

    func_80096E78(&chara->rotation_24, &coords->coord);
}
