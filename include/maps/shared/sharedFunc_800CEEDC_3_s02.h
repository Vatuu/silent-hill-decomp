// Ai_Alessa

void sharedFunc_800CEEDC_3_s02(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    s_Collision coll;
    s32         sfx;
    s8          pitch0;
    s8          pitch1;

#define CHARA_PROPERTIES (chara->properties_E4.dahlia)

    switch (CHARA_PROPERTIES.stateIdx0)
    {
        case 0:
            break;

        case 2:
            if (CHARA_PROPERTIES.moveDistance_126 > Q12(1.25f))
            {
                CHARA_PROPERTIES.moveDistance_126 -= TIME_STEP_SCALE(g_DeltaTime0, Q12(0.5f));
                if (CHARA_PROPERTIES.moveDistance_126 < Q12(1.25f))
                {
                    CHARA_PROPERTIES.moveDistance_126 = Q12(1.25f);
                }
            }
            else if (CHARA_PROPERTIES.moveDistance_126 < Q12(1.25f))
            {
                CHARA_PROPERTIES.moveDistance_126 += TIME_STEP_SCALE(g_DeltaTime0, Q12(0.4f));
                CHARA_PROPERTIES.moveDistance_126  = CLAMP(CHARA_PROPERTIES.moveDistance_126, 0, Q12(1.25f));
            }

            Model_AnimStatusSet(&chara->model_0, 2, false);
            Character_AnimStateTryReset(chara);
            break;

        case 1:
            if (CHARA_PROPERTIES.moveDistance_126)
            {
                CHARA_PROPERTIES.moveDistance_126 -= TIME_STEP_SCALE(g_DeltaTime0, Q12(0.4f)) * 2;
                if (CHARA_PROPERTIES.moveDistance_126 < 0)
                {
                    CHARA_PROPERTIES.moveDistance_126 = 0;
                }
            }

            Model_AnimStatusKeyframeSet(chara->model_0, 1, true, ALESSA_ANIM_INFOS, 0);
            Character_AnimStateTryReset(chara);
            break;

        case 4:
            Model_AnimStatusSet(&chara->model_0, 4, false);
            Character_AnimStateTryReset(chara);
            break;

        case 3:
            Model_AnimStatusSet(&chara->model_0, 3, false);
            Character_AnimStateTryReset(chara);
            break;

        case 5:
            Model_AnimStatusSet(&chara->model_0, 5, false);
            Character_AnimStateTryReset(chara);
            break;

        case 6:
            Model_AnimStatusSet(&chara->model_0, 6, false);
            Character_AnimStateTryReset(chara);
            break;

        case 7:
            Model_AnimStatusSet(&chara->model_0, 7, false);
            Character_AnimStateTryReset(chara);
            break;

        case 8:
            Model_AnimStatusSet(&chara->model_0, 8, false);
            Character_AnimStateTryReset(chara);
            break;

        case 9:
            Model_AnimStatusSet(&chara->model_0, 9, false);
            Character_AnimStateTryReset(chara);
            break;

        case 10:
            Model_AnimStatusSet(&chara->model_0, 10, false);
            Character_AnimStateTryReset(chara);
            break;
    }

    Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);

    switch (CHARA_PROPERTIES.stateIdx0)
    {
        case 2:
            sharedFunc_800D908C_0_s00(5, chara, 24, 37, sfx, pitch0);
            break;

        case 3:
            if (chara->model_0.anim_4.keyframeIdx_8 < 90)
            {
                if (chara->model_0.anim_4.keyframeIdx_8 <= 60)
                {
                    sharedFunc_800D908C_0_s00(7, chara, 60, 71, sfx, pitch0);
                }
                else if (chara->model_0.anim_4.keyframeIdx_8 <= 81)
                {
                    sharedFunc_800D908C_0_s00(7, chara, 81, 71, sfx, pitch0);
                }
                else
                {
                    sharedFunc_800D908C_0_s00(7, chara, 89, 89, sfx, pitch0);
                }
            }
            else
            {
                if (chara->model_0.anim_4.keyframeIdx_8 <= 111)
                {
                    sharedFunc_800D908C_0_s00(7, chara, 121, 111, sfx, pitch1);
                }
                else
                {
                    sharedFunc_800D908C_0_s00(7, chara, 121, 128, sfx, pitch1);
                }
            }
            break;

        case 5:
            sharedFunc_800D9188_0_s00(chara->model_0.anim_4.status_0, chara, 210, Sfx_Unk1638);
            if (chara->model_0.anim_4.keyframeIdx_8 <= 173)
            {
                sharedFunc_800D908C_0_s00(11, chara, 182, 173, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(11, chara, 182, 199, sfx, pitch0);
            }
            break;

        case 8:
            sharedFunc_800D908C_0_s00(17, chara, 298, 298, sfx, pitch0);
            break;
    }

    chara->rotation_24.vy  = ABS_ANGLE(chara->rotation_24.vy + Q8_TO_Q4(sharedData_800D3150_3_s02));
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->moveSpeed_38    = CHARA_PROPERTIES.moveDistance_126;
    chara->field_34       += g_DeltaTime2;

    coords->flg = 0;
    Math_MatrixRotate1(&chara->rotation_24, &coords->coord);
}
