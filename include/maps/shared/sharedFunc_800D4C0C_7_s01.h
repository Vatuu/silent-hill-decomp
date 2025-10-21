// Ai_GhostChildAlessa

void sharedFunc_800D4C0C_7_s01(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
#define CHARA_PROPERTIES (chara->properties_E4.dahlia)

    switch (CHARA_PROPERTIES.stateIdx0)
    {
        case 0:
            break;

        case 1:
            CHARA_PROPERTIES.moveDistance_126 = CHARA_PROPERTIES.field_124;
            Model_AnimStatusSet(&chara->model_0, 1, false);
            Character_AnimStateTryReset(chara);
            break;

        case 2:
            CHARA_PROPERTIES.moveDistance_126 = CHARA_PROPERTIES.field_124;
            Model_AnimStatusSet(&chara->model_0, 2, false);
            Character_AnimStateTryReset(chara);
            break;

        case 6:
            Model_AnimStatusSet(&chara->model_0, 3, false);
            if (chara->model_0.anim_4.keyframeIdx_8 == 63)
            {
                CHARA_PROPERTIES.stateIdx0 = 7;
                chara->model_0.stateStep_3 = 0;
            }
            break;

        case 7:
            Model_AnimStatusSet(&chara->model_0, 4, false);
            Character_AnimStateTryReset(chara);
            break;

        case 8:
            Model_AnimStatusSet(&chara->model_0, 5, false);
            Character_AnimStateTryReset(chara);
            break;

        case 9:
            Model_AnimStatusSet(&chara->model_0, 6, false);
            Character_AnimStateTryReset(chara);
            break;

        case 10:
            Model_AnimStatusSet(&chara->model_0, 7, false);
            Character_AnimStateTryReset(chara);
            break;

        case 11:
            Model_AnimStatusSet(&chara->model_0, 8, false);
            Character_AnimStateTryReset(chara);
            break;
    }

    chara->rotation_24.vy  = ABS_ANGLE(chara->rotation_24.vy + Q8_TO_Q4(sharedData_800E39D8_0_s00));
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->moveSpeed_38    = CHARA_PROPERTIES.moveDistance_126;
    chara->field_34       += g_DeltaTime2;

    coords->flg = 0;
    Math_MatrixRotate1(&chara->rotation_24, &coords->coord);
}
