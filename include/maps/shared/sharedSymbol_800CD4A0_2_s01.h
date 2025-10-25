#if defined(MAP2_S01) || defined(MAP3_S06)
    #define ANIM_TABLE KAUFMANN_ANIM_INFOS
#else
    #define ANIM_TABLE DAHLIA_ANIM_INFOS
#endif

extern s_AnimInfo ANIM_TABLE[];

void sharedSymbol_800CD4A0_2_s01(s_SubCharacter* dahlia, GsCOORDINATE2* coord)
{
    s_Collision coll;
    s32         sfx;
    s8          pitch0;
    s8          pitch1;

    switch (dahlia->properties_E4.dahlia.stateIdx0)
    {
    case 0:
    case 5:
        if (dahlia->properties_E4.dahlia.moveDistance_126)
        {
            dahlia->properties_E4.dahlia.moveDistance_126 -= TIME_STEP_SCALE(g_DeltaTime0, Q12(0.4f)) * 2;
            if (dahlia->properties_E4.dahlia.moveDistance_126 < 0)
            {
                dahlia->properties_E4.dahlia.moveDistance_126 = 0;
            }
        }

        Model_AnimStatusSet(&dahlia->model_0, 1, false);
        Character_AnimStateReset(dahlia);
        break;

    case 1:
        if (dahlia->properties_E4.dahlia.moveDistance_126 > Q12(1.25f))
        {
            dahlia->properties_E4.dahlia.moveDistance_126 -= TIME_STEP_SCALE(g_DeltaTime0, Q12(0.5f));
            if (dahlia->properties_E4.dahlia.moveDistance_126 < Q12(1.25f))
            {
                dahlia->properties_E4.dahlia.moveDistance_126 = Q12(1.25f);
            }
        } 
        else if (dahlia->properties_E4.dahlia.moveDistance_126 < Q12(1.25f))
        {
            dahlia->properties_E4.dahlia.moveDistance_126 += TIME_STEP_SCALE(g_DeltaTime0, Q12(0.4f));
            dahlia->properties_E4.dahlia.moveDistance_126  = CLAMP(dahlia->properties_E4.dahlia.moveDistance_126, Q12(0.0f), Q12(1.25f));         
        }

        Model_AnimStatusSet(&dahlia->model_0, 2, false);
        Character_AnimStateReset(dahlia);
        break;

    case 6:
        Model_AnimStatusSet(&dahlia->model_0, 14, false);
#if defined(MAP7_S03)
        func_8003DD80(31, 1);
#endif
        Character_AnimStateReset(dahlia);
        break;

    case 7:
        Model_AnimStatusSet(&dahlia->model_0, 3, false);
        Character_AnimStateReset(dahlia);
        break;

    case 8:
        Model_AnimStatusSet(&dahlia->model_0, 4, false);
        Character_AnimStateReset(dahlia);
        break;

    case 11:
#if defined(MAP3_S06) || defined(MAP6_S01) || defined(MAP6_S04) || defined(MAP7_S02) || \
    defined(MAP7_S03)
        Model_AnimStatusKeyframeSet(dahlia->model_0, 7, true, ANIM_TABLE, 0);
#else
        Model_AnimStatusSet(&dahlia->model_0, 7, false);
#endif
        Character_AnimStateReset(dahlia);
        break;

    case 9:
        Model_AnimStatusSet(&dahlia->model_0, 5, false);
        Character_AnimStateReset(dahlia);

        if (dahlia->model_0.anim_4.keyframeIdx_8 < 144)
        {
            func_8003DD80(30, 1);
        }
        else
        {
#if !defined(MAP6_S01) && !defined(MAP6_S04) && !defined(MAP7_S02) && !defined(MAP7_S03)
#if defined(MAP3_S06)
            func_8003DD80(30, 2);
#else
            func_8003DD80(30, 3);
#endif
#endif
        }
        break;

    case 10:
#if !defined(MAP6_S01) && !defined(MAP6_S04) && !defined(MAP7_S02) && !defined(MAP7_S03)
#if defined(MAP3_S06)
        Model_AnimStatusKeyframeSet(dahlia->model_0, 6, true, ANIM_TABLE, 0);
#else
        Model_AnimStatusSet(&dahlia->model_0, 6, false);
#endif
#endif
        Character_AnimStateReset(dahlia);

        if (dahlia->model_0.anim_4.keyframeIdx_8 < 198)
        {
#if !defined(MAP6_S01) && !defined(MAP6_S04) && !defined(MAP7_S02) && !defined(MAP7_S03)
#if defined(MAP3_S06)
            func_8003DD80(30, 2);
#else
            func_8003DD80(30, 3);
#endif
#endif
        }
        else
        {
            func_8003DD80(30, 1);
        }
        break;

    case 12:
        Model_AnimStatusKeyframeSet(dahlia->model_0, 8, true, ANIM_TABLE, 0);
        Character_AnimStateReset(dahlia);
        break;

    case 13:
        Model_AnimStatusSet(&dahlia->model_0, 9, false);
        Character_AnimStateReset(dahlia);
        break;

    case 14:
        Model_AnimStatusSet(&dahlia->model_0, 10, false);
        Character_AnimStateReset(dahlia);
        break;

    case 15:
        Model_AnimStatusSet(&dahlia->model_0, 15, false);
        Character_AnimStateReset(dahlia);
        break;

    case 16:
        Model_AnimStatusSet(&dahlia->model_0, 16, false);
        Character_AnimStateReset(dahlia);

        if (dahlia->model_0.anim_4.keyframeIdx_8 == 103)
        {
            dahlia->properties_E4.dahlia.stateIdx0 = 5;
            dahlia->model_0.stateStep_3 = 0;
        }
        break;

    case 17:
        Model_AnimStatusSet(&dahlia->model_0, 17, false);
        Character_AnimStateReset(dahlia);
        break;

    case 18:
        Model_AnimStatusSet(&dahlia->model_0, 18, false);
        Character_AnimStateReset(dahlia);
        break;

    case 19:
        if (dahlia->model_0.anim_4.keyframeIdx_8 >= 40 && !sharedData_800D16E4_2_s01)
        {
            func_8005F6B0(&g_SysWork.npcs_1A0[1], &(VECTOR3){ Q12(138.3f), Q12(-1.1f), Q12(-100.8f) }, 3, 1);
            sharedData_800D16E4_2_s01 = 1;
        }

        Model_AnimStatusKeyframeSet(dahlia->model_0, 19, true, ANIM_TABLE, 0);
        Character_AnimStateReset(dahlia);

        if (dahlia->properties_E4.dahlia.stateIdx0 != 19)
        {
            sharedData_800D16E4_2_s01 = 0;
        }
        break;

    case 20:
        Model_AnimStatusSet(&dahlia->model_0, 20, false);
        Character_AnimStateReset(dahlia);
        break;

    case 21:
        Model_AnimStatusKeyframeSet(dahlia->model_0, 21, true, ANIM_TABLE, 0);
        Character_AnimStateReset(dahlia);
        break;

    case 22:
        Model_AnimStatusKeyframeSet(dahlia->model_0, 22, true, ANIM_TABLE, 0);
        Character_AnimStateReset(dahlia);
        break;

    case 23:
        Model_AnimStatusSet(&dahlia->model_0, 23, false);
        Character_AnimStateReset(dahlia);
        break;

    case 24:
        Model_AnimStatusSet(&dahlia->model_0, 24, false);
        Character_AnimStateReset(dahlia);
        break;

    case 25:
        Model_AnimStatusSet(&dahlia->model_0, 11, false);
        func_8003DD80(30, 1);

        if (dahlia->model_0.anim_4.keyframeIdx_8 == 349)
        {
            dahlia->properties_E4.dahlia.stateIdx0 = 26;
            dahlia->model_0.stateStep_3 = 0;
            break;
        }
        break;

    case 26:
        Model_AnimStatusSet(&dahlia->model_0, 12, false);
        Character_AnimStateReset(dahlia);
        break;

    case 27:
        Model_AnimStatusSet(&dahlia->model_0, 13, false);
        Character_AnimStateReset(dahlia);
        break;

    case 28:
        Model_AnimStatusSet(&dahlia->model_0, 25, false);
        Character_AnimStateReset(dahlia);
        break;
    }

    Collision_Get(&coll, dahlia->position_18.vx, dahlia->position_18.vz);

    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);

#if defined(MAP6_S01)
    sfx = Sfx_Unk1606;
#else
    sfx = Sfx_Unk1489;
#endif

    switch (dahlia->properties_E4.dahlia.stateIdx0)
    {
    case 1:             
        sharedFunc_800D908C_0_s00(5, dahlia, 24, 37, sfx, pitch0);
        break;

    case 8:             
        sharedFunc_800D908C_0_s00(9, dahlia, 107, 98, sfx, pitch0);
        break;

    case 11:            
        sharedFunc_800D908C_0_s00(15, dahlia, 235, 245, sfx, pitch0);
        break;

    case 7:             
        if (dahlia->model_0.anim_4.keyframeIdx_8 < 47)
        {
            sharedFunc_800D9188_0_s00(dahlia->model_0.anim_4.status_0, dahlia, 46, Sfx_Unk1674);
        }
        else
        {
            sharedFunc_800D9188_0_s00(dahlia->model_0.anim_4.status_0, dahlia, 47, Sfx_Unk1675);
        }
        break;

    default:            
        break;

    case 17:            
        if (dahlia->model_0.anim_4.keyframeIdx_8 < 127)
        {
            sharedFunc_800D9188_0_s00(35, dahlia, 120, Sfx_Unk1674);
        }
        else
        {
            sharedFunc_800D9188_0_s00(35, dahlia, 127, Sfx_Unk1675);
        }
        break;

    case 10:            
        if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP2_S01)
        {
            sharedFunc_800D9188_0_s00(dahlia->model_0.anim_4.status_0, dahlia, 193, Sfx_Unk1488);
        }
        else
        {
            sharedFunc_800D9188_0_s00(dahlia->model_0.anim_4.status_0, dahlia, 193, Sfx_Unk1496);
        }
        break;

    case 14:            
        if (dahlia->model_0.anim_4.keyframeIdx_8 < 310)
        {
            sharedFunc_800D908C_0_s00(dahlia->model_0.anim_4.status_0, dahlia, 319, 309, sfx, pitch0);
        }
        else
        {
            sharedFunc_800D908C_0_s00(dahlia->model_0.anim_4.status_0, dahlia, 319, 329, sfx, pitch0);
        }
        break;

    case 19:
        if (dahlia->model_0.anim_4.keyframeIdx_8 < 175)
        {

            sharedFunc_800D9188_0_s00(39, dahlia, 170, Sfx_Unk1674);
        }
        else
        {
            sharedFunc_800D9188_0_s00(39, dahlia, 177, Sfx_Unk1675);
        }
        break;
    }

    dahlia->rotation_24.vy  = ABS_ANGLE(dahlia->rotation_24.vy + (sharedData_800D16E0_2_s01 >> 4));
    dahlia->headingAngle_3C = dahlia->rotation_24.vy;
    dahlia->moveSpeed_38    = dahlia->properties_E4.dahlia.moveDistance_126;
    dahlia->field_34       += g_DeltaTime2;

    coord->flg = false;
    Math_MatrixRotate1(&dahlia->rotation_24, &coord->coord);
}
