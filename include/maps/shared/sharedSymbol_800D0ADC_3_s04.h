// Ai_Lisa

#if defined(MAP3_S04) || defined(MAP4_S04) || defined(MAP7_S00)
#define ANIM_TABLE KAUFMANN_ANIM_INFOS
#else
#define ANIM_TABLE LISA_ANIM_INFOS
#endif

extern s_AnimInfo ANIM_TABLE[];

void sharedSymbol_800D0ADC_3_s04(s_SubCharacter* chara, GsCOORDINATE2* coords)
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

        case 1:
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
            Character_AnimStateReset(chara);
            break;

        case 5:
        case 20:
            if (CHARA_PROPERTIES.moveDistance_126)
            {
                CHARA_PROPERTIES.moveDistance_126 -= TIME_STEP_SCALE(g_DeltaTime0, Q12(0.4f)) * 2;
                if (CHARA_PROPERTIES.moveDistance_126 < Q12(0.0f))
                {
                    CHARA_PROPERTIES.moveDistance_126 = Q12(0.0f);
                }
            }

            if (CHARA_PROPERTIES.stateIdx0 == 5)
            {
                Model_AnimStatusKeyframeSet(chara->model_0, 1, true, ANIM_TABLE, 0);
            }
            else
            {
                Model_AnimStatusSet(&chara->model_0, 1, true);
            }

            Character_AnimStateReset(chara);
            break;

        case 6:
            Model_AnimStatusSet(&chara->model_0, 3, false);
            Character_AnimStateReset(chara);
            break;

        case 7:
            Model_AnimStatusSet(&chara->model_0, 4, false);

            if (chara->model_0.anim_4.keyframeIdx_8 == 72)
            {
                CHARA_PROPERTIES.stateIdx0 = 20;
                chara->model_0.stateStep_3 = 0;
            }
            break;

        case 8:
            Model_AnimStatusSet(&chara->model_0, 5, false);
            Character_AnimStateReset(chara);
            break;

        case 9:
            Model_AnimStatusKeyframeSet(chara->model_0, 6, true, ANIM_TABLE, 0);
            Character_AnimStateReset(chara);
            break;

        case 10:
            Model_AnimStatusSet(&chara->model_0, 7, false);
            Character_AnimStateReset(chara);
            break;

        case 11:
            Model_AnimStatusKeyframeSet(chara->model_0, 8, true, ANIM_TABLE, 0);
            Character_AnimStateReset(chara);
            break;

        case 12:
            Model_AnimStatusKeyframeSet(chara->model_0, 9, true, ANIM_TABLE, 0);
            Character_AnimStateReset(chara);
            break;

        case 13:
            Model_AnimStatusSet(&chara->model_0, 10, false);
            Character_AnimStateReset(chara);
            break;

        case 14:
            Model_AnimStatusKeyframeSet(chara->model_0, 11, true, ANIM_TABLE, 0);
            break;

        case 15:
            Model_AnimStatusSet(&chara->model_0, 12, false);
            break;

        case 16:
            Model_AnimStatusSet(&chara->model_0, 13, false);
            Character_AnimStateReset(chara);
            break;

        case 17:
            Model_AnimStatusKeyframeSet(chara->model_0, 14, true, ANIM_TABLE, 0);
            Character_AnimStateReset(chara);
            break;

        case 18:
            Model_AnimStatusKeyframeSet(chara->model_0, 15, true, ANIM_TABLE, 0);
            Character_AnimStateReset(chara);
            break;

        case 19:
            Model_AnimStatusSet(&chara->model_0, 16, false);
            Character_AnimStateReset(chara);
            break;

        case 21:
            Model_AnimStatusSet(&chara->model_0, 17, false);
            Character_AnimStateReset(chara);
            break;
    }

    Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);

    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);
    sfx = Sfx_Unk1529;

    switch (CHARA_PROPERTIES.stateIdx0)
    {
        case 1:
            sharedFunc_800D908C_0_s00(5, chara, 14, 31, sfx, pitch0);
            break;

        case 8:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 125)
            {
                sharedFunc_800D908C_0_s00(11, chara, 125, 138, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 <= 153)
            {
                sharedFunc_800D908C_0_s00(11, chara, 153, 138, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(11, chara, 189, 184, sfx, pitch0);
            }
            break;

        case 12:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 258)
            {
                // @bug From the other `keyframeIdx_8` checks here, should this be 258 instead of 263?
                sharedFunc_800D908C_0_s00(19, chara, 263, 258, sfx, pitch1);
            }
            else
            {
                sharedFunc_800D908C_0_s00(19, chara, 263, 266, sfx, pitch1);
            }
            break;

        case 13:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 332)
            {
                sharedFunc_800D908C_0_s00(21, chara, 332, 337, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 <= 344)
            {
                sharedFunc_800D908C_0_s00(21, chara, 344, 337, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(21, chara, 352, 348, sfx, pitch0);
            }
            break;

        case 11:
            sharedFunc_800D908C_0_s00(17, chara, 240, 240, sfx, pitch0);
            break;

        case 15:
#if defined(MAP7_S00)
            sharedFunc_800D9188_0_s00(25, chara, 408, Sfx_Unk1639);
#endif
            sharedFunc_800D908C_0_s00(25, chara, 406, 406, sfx, pitch0);
            break;

        case 16:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 423)
            {
                sharedFunc_800D908C_0_s00(27, chara, 423, 425, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 <= 429)
            {
                sharedFunc_800D908C_0_s00(27, chara, 429, 425, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(27, chara, 435, 432, sfx, pitch0);
            }
            break;

        case 17:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 460)
            {
                sharedFunc_800D908C_0_s00(29, chara, 460, 477, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 <= 497)
            {
                sharedFunc_800D908C_0_s00(29, chara, 497, 477, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(29, chara, 536, 516, sfx, pitch0);
            }
            break;

        case 18:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 551)
            {
                sharedFunc_800D908C_0_s00(31, chara, 551, 555, sfx, pitch0);
            }
            else if (chara->model_0.anim_4.keyframeIdx_8 <= 559)
            {
                sharedFunc_800D908C_0_s00(31, chara, 559, 555, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(31, chara, 564, 564, sfx, pitch0);
            }
            break;
    }

    chara->rotation_24.vy  = ABS_ANGLE(chara->rotation_24.vy + Q8_TO_Q4(sharedData_800D6BB8_3_s04));
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->moveSpeed_38    = CHARA_PROPERTIES.moveDistance_126;
    chara->field_34       += g_DeltaTime2;

    coords->flg = false;
    Math_MatrixRotate1(&chara->rotation_24, &coords->coord);
}
