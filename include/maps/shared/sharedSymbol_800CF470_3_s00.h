// Ai_Kaufmann

void sharedSymbol_800CF470_3_s00(s_SubCharacter* chara, GsCOORDINATE2* coords)
{
    s_Collision sp18;
    s32         sfx;
    s8          pitch0;
    s8          pitch1;

#define CHARA_PROPERTIES (chara->properties_E4.dahlia)

    switch (CHARA_PROPERTIES.stateIdx0)
    {
        case 0:
            if (CHARA_PROPERTIES.moveDistance_126)
            {
                CHARA_PROPERTIES.moveDistance_126 -= TIME_STEP_SCALE(g_DeltaTime0, Q12(0.4f)) * 2;
                if (CHARA_PROPERTIES.moveDistance_126 < 0)
                {
                    CHARA_PROPERTIES.moveDistance_126 = 0;
                }
            }

            Model_AnimStatusSet(&chara->model_0, 1, false);
            Character_AnimStateTryReset(chara);
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

            Model_AnimStatusSet(&chara->model_0, 3, false);
            Character_AnimStateTryReset(chara);
#if defined(MAP5_S03)
            func_8003DD80(38, 52);
#endif
            break;
        case 5:
            Model_AnimStatusKeyframeSet(chara->model_0, 1, true, KAUFMANN_ANIM_INFOS);
            Character_AnimStateTryReset(chara);
            func_8003DD80(38, 1);
            break;
        case 24:
            Model_AnimStatusKeyframeSet(chara->model_0, 20, true, KAUFMANN_ANIM_INFOS);
            Character_AnimStateTryReset(chara);
#if defined(MAP5_S03)
            func_8003DD80(38, 52);
#else
            func_8003DD80(39, 49);
#endif
            break;
        case 6:
            Model_AnimStatusKeyframeSet(chara->model_0, 4, true, KAUFMANN_ANIM_INFOS);
            Character_AnimStateTryReset(chara);
#if defined(MAP3_S00)
            func_8003DD80(38, 19);
#endif
            break;
        case 7:
            if (chara->model_0.anim_4.keyframeIdx_8 >= 95 && g_SysWork.npcs_1A0[0].properties_E4.dahlia.properties_120.val32 == 0)
            {
                g_SysWork.npcs_1A0[0].properties_E4.dahlia.properties_120.val32 = 1;
                func_8006342C(70, 0, 0, &g_SysWork.npcCoords_FC0[0]);
            }

            Model_AnimStatusSet(&chara->model_0, 5, false);
            Character_AnimStateTryReset(chara);
#if defined(MAP3_S00)
            func_8003DD80(38, 19);
#endif
            break;
        case 8:
            Model_AnimStatusSet(&chara->model_0, 6, false);
            Character_AnimStateTryReset(chara);
#if defined(MAP3_S00)
            func_8003DD80(38, 19);
#endif
            break;
        case 9:
            Model_AnimStatusSet(&chara->model_0, 7, false);
            Character_AnimStateTryReset(chara);
            if (chara->model_0.anim_4.keyframeIdx_8 < 139 || (chara->model_0.anim_4.status_0 & 1) == 0)
            {
                func_8003DD80(38, 17);
            }
            else
            {
                Savegame_EventFlagSet(EventFlag_198);
                func_8003DD80(38, 49);
            }
            break;
        case 10:
            Model_AnimStatusSet(&chara->model_0, 8, false);
            Character_AnimStateTryReset(chara);
            break;
        case 11:
            Model_AnimStatusKeyframeSet(chara->model_0, 9, true, KAUFMANN_ANIM_INFOS);
            Character_AnimStateTryReset(chara);
#if defined(MAP5_S02)
            func_8003DD80(38, 17);
#endif
            break;
        case 12:
            Model_AnimStatusKeyframeSet(chara->model_0, 22, true, KAUFMANN_ANIM_INFOS);
            Character_AnimStateTryReset(chara);
#if defined(MAP5_S02)
            func_8003DD80(38, 17);
#endif
            break;
        case 13:
            Model_AnimStatusSet(&chara->model_0, 10, false);
            Character_AnimStateTryReset(chara);
#if defined(MAP5_S02)
            func_8003DD80(38, 17);
#endif
            break;
        case 14:
            Model_AnimStatusSet(&chara->model_0, 11, false);
            Character_AnimStateTryReset(chara);
#if defined(MAP5_S02)
            func_8003DD80(38, 17);
#endif
            break;
        case 15:
            Model_AnimStatusSet(&chara->model_0, 12, false);
            Character_AnimStateTryReset(chara);
            if (chara->model_0.anim_4.keyframeIdx_8 >= 364 && chara->model_0.anim_4.status_0 & 1)
            {
                func_8003DD80(38, 4);
            }
            break;
        case 16:
            Model_AnimStatusSet(&chara->model_0, 2, false);
            Character_AnimStateTryReset(chara);
#if defined(MAP5_S03)
            func_8003DD80(38, 49);
#endif
            break;
        case 25:
            Model_AnimStatusSet(&chara->model_0, 21, false);
            Character_AnimStateTryReset(chara);
            func_8003DD80(39, 51);
            break;
        case 17:
            Model_AnimStatusSet(&chara->model_0, 13, false);
            Character_AnimStateTryReset(chara);
            break;
        case 18:
            Model_AnimStatusSet(&chara->model_0, 16, false);
            Character_AnimStateTryReset(chara);

#if defined(MAP7_S03)
            // TODO: invert like case 15? can't find how to match
            if (chara->model_0.anim_4.keyframeIdx_8 < 78 || (chara->model_0.anim_4.status_0 & 1) == 0)
            {
                func_8003DD80(39, 49);
            }
            else
            {
                func_8003DD80(39, 52);
            }
#endif
            break;
        case 19:
            Model_AnimStatusSet(&chara->model_0, 17, false);
            Character_AnimStateTryReset(chara);
#if defined(MAP7_S03)
            func_8003DD80(39, 52);
#endif
            break;
        case 20:
            Model_AnimStatusKeyframeSet(chara->model_0, 18, true, KAUFMANN_ANIM_INFOS);
            Character_AnimStateTryReset(chara);

#if defined(MAP7_S03)
            if (chara->model_0.anim_4.keyframeIdx_8 < 141)
            {
                func_8003DD80(39, 52);
            }
            else
            {
                func_8003DD80(39, 49);
            }
#endif
            break;
        case 21:
            Model_AnimStatusSet(&chara->model_0, 15, false);
            Character_AnimStateTryReset(chara);

#if defined(MAP7_S03)
            func_8003DD80(39, 17);
#endif
            break;
        case 22:
            Model_AnimStatusKeyframeSet(chara->model_0, 19, true, KAUFMANN_ANIM_INFOS);
            Character_AnimStateTryReset(chara);
#if defined(MAP7_S03)
            func_8003DD80(39, 49);
#endif
            break;
        case 23:
            Model_AnimStatusSet(&chara->model_0, 14, false);
            Character_AnimStateTryReset(chara);
            break;
    }

    Collision_Get(&sp18, chara->position_18.vx, chara->position_18.vz);
    func_8007FDE0(sp18.field_8, &sfx, &pitch0, &pitch1);

    switch (CHARA_PROPERTIES.stateIdx0)
    {
        case 1:
            sharedFunc_800D908C_0_s00(7, chara, 53, 41, sfx, pitch0);
            break;
        case 6:
            sharedFunc_800D908C_0_s00(9, chara, 80, 0, sfx, pitch0);
            break;
        case 7:
            sharedFunc_800D9188_0_s00(chara->model_0.anim_4.status_0, chara, 95, Sfx_Unk1492);
            break;
        case 9:
            sharedFunc_800D908C_0_s00(15, chara, 132, 174, sfx, pitch0);
            break;
        case 10:
            sharedFunc_800D908C_0_s00(17, chara, 191, 0, sfx, pitch0);
            break;
        case 17:
            sharedFunc_800D908C_0_s00(27, chara, 393, 0, sfx, pitch0);
            break;
        case 13:
            sharedFunc_800D9188_0_s00(21, chara, 307, Sfx_Unk1594);
            break;
        case 15:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 353)
            {
                sharedFunc_800D908C_0_s00(25, chara, 357, 353, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(25, chara, 357, 361, sfx, pitch0);
            }
            break;
        case 16:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 21)
            {
                sharedFunc_800D908C_0_s00(5, chara, 28, 21, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(5, chara, 28, 34, sfx, pitch0);
            }
            break;
        case 25:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 247)
            {
                sharedFunc_800D908C_0_s00(43, chara, 254, 247, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(43, chara, 254, 260, sfx, pitch0);
            }
            break;
        case 22:
            if (chara->model_0.anim_4.keyframeIdx_8 <= 211)
            {
                sharedFunc_800D908C_0_s00(39, chara, 217, 211, sfx, pitch0);
            }
            else
            {
                sharedFunc_800D908C_0_s00(39, chara, 217, 221, sfx, pitch0);
            }
            break;
    }

    chara->rotation_24.vy  = ABS_ANGLE(chara->rotation_24.vy + Q8_TO_Q4(sharedData_800D5CF4_3_s00));
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->moveSpeed_38    = CHARA_PROPERTIES.moveDistance_126;
    chara->field_34       += g_DeltaTime2;

    coords->flg = 0;
    Math_MatrixRotate1(&chara->rotation_24, &coords->coord);
}
