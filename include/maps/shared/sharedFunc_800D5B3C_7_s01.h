
void sharedFunc_800D5B3C_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    s_func_800699F8 sp18;
    s32             sp28;
    s8              sp2C;
    s8              sp2D; // Type asssumed.
    s32             tempVal;

    tempVal = chara->properties_E4.larvalStalker.properties_E8[0].val32;
    if (tempVal != 0 && chara->properties_E4.larvalStalker.properties_E8[0].val32 == 6)
    {
        if (chara->model_0.stateStep_3 == 0)
        {
            chara->model_0.anim_4.animIdx_0 = 2;
            chara->model_0.stateStep_3++;
        }

        if (chara->properties_E4.larvalStalker.properties_E8[4].val32 != 0)
        {
            chara->properties_E4.larvalStalker.properties_E8[0].val32 = 0;
            chara->model_0.stateStep_3 = 0;
            chara->properties_E4.larvalStalker.properties_E8[4].val32 = 0;
        }
    }

    func_800699F8(&sp18, chara->position_18.vx, chara->position_18.vz);
    func_8007FDE0(sp18.field_8, &sp28, &sp2C, &sp2D);

    if (chara->properties_E4.larvalStalker.properties_E8[0].val32 == 6)
    {
        if (chara->model_0.anim_4.keyframeIdx0_8 < 13)
        {
            sharedFunc_800D908C_0_s00(3, chara, 12, 27, sp28, sp2C);
        }
        else if (chara->model_0.anim_4.keyframeIdx0_8 < 50)
        {
            sharedFunc_800D908C_0_s00(3, chara, 49, 27, sp28, sp2C);
        }
        else
        {
            sharedFunc_800D908C_0_s00(3, chara, 92, 69, sp28, sp2C);
        }
    }

    chara->headingAngle_3C =
    chara->rotation_24.vy  = (chara->rotation_24.vy + (sharedData_800E2C38_7_s01 >> 4) + 0x1000) & 0xFFF;

    chara->moveSpeed_38 = chara->properties_E4.larvalStalker.properties_E8[15].val16[1];
    chara->field_34    += g_DeltaTime2;

    coords->flg = 0;

    func_80096E78(&chara->rotation_24, &coords->coord);
}
