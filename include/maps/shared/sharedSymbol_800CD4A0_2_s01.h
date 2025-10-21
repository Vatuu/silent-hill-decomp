#if defined(MAP2_S01) || defined(MAP3_S06)
    #define ANIM_TABLE KAUFMANN_ANIM_INFOS
#else
    #define ANIM_TABLE DAHLIA_ANIM_INFOS
#endif

extern s_AnimInfo ANIM_TABLE[];

static inline void RESET_STATE_IDX0(s_SubCharacter* dahlia)
{
    if (dahlia->properties_E4.dahlia.resetStateIdx0_F8)
    {
        dahlia->properties_E4.dahlia.stateIdx0 = 0;
        dahlia->model_0.stateStep_3 = 0;
        dahlia->properties_E4.dahlia.resetStateIdx0_F8 = 0;
    }
}

static inline void NEXT_ANIM_STATUS(s_SubCharacter* dahlia, s32 animIdx, bool active)
{
    if (dahlia->model_0.stateStep_3 == 0)
    {
        dahlia->model_0.anim_4.status_0 = ANIM_STATUS(animIdx, active);
        dahlia->model_0.stateStep_3++;
    }
}

#define NEXT_ANIM_STATUS_OTHER(dahlia, animIdx, active, kaufmannIdx) \
        if (!dahlia->model_0.stateStep_3) \
        { \
            dahlia->model_0.anim_4.status_0 = ANIM_STATUS(animIdx, active); \
            dahlia->model_0.stateStep_3++; \
            dahlia->model_0.anim_4.time_4 = FP_TO(ANIM_TABLE[(kaufmannIdx)].startKeyframeIdx_C, Q12_SHIFT); \
            dahlia->model_0.anim_4.keyframeIdx_8 = ANIM_TABLE[(kaufmannIdx)].startKeyframeIdx_C; \
        }

void sharedSymbol_800CD4A0_2_s01(s_SubCharacter* dahlia, GsCOORDINATE2* coord)
{
    s_Collision coll;
    s32 sfx;
    s8 pitch0;
    s8 pitch1;

    #define DAHLIA_PROPS dahlia->properties_E4.dahlia

    switch (DAHLIA_PROPS.stateIdx0)
    {
    case 0:
    case 5:
        if (DAHLIA_PROPS.moveDistance_126)
        {
            DAHLIA_PROPS.moveDistance_126 -= TIME_STEP_SCALE(g_DeltaTime0, Q12(0.4f)) * 2;
            if (DAHLIA_PROPS.moveDistance_126 < 0)
            {
                DAHLIA_PROPS.moveDistance_126 = 0;
            }
        }
        NEXT_ANIM_STATUS(dahlia, 1, false);
        RESET_STATE_IDX0(dahlia);
        break;
    case 1:
        if ( DAHLIA_PROPS.moveDistance_126 > Q12(1.25f))
        {
            DAHLIA_PROPS.moveDistance_126 -= TIME_STEP_SCALE(g_DeltaTime0, Q12(0.5f));
            if (DAHLIA_PROPS.moveDistance_126 < Q12(1.25f))
            {
                DAHLIA_PROPS.moveDistance_126 = Q12(1.25f);
            }
        } 
        else if (DAHLIA_PROPS.moveDistance_126 < Q12(1.25f))
        {
            DAHLIA_PROPS.moveDistance_126 += TIME_STEP_SCALE(g_DeltaTime0, Q12(0.4f));
            DAHLIA_PROPS.moveDistance_126 = CLAMP(DAHLIA_PROPS.moveDistance_126, 0, Q12(1.25f));         
        }
        NEXT_ANIM_STATUS(dahlia, 2, false);
        RESET_STATE_IDX0(dahlia);
        break;
    case 6:
        NEXT_ANIM_STATUS(dahlia, 14, false);
#if defined(MAP7_S03)
        func_8003DD80(31, 1);
#endif
        RESET_STATE_IDX0(dahlia);
        break;
    case 7:
        NEXT_ANIM_STATUS(dahlia, 3, false);
        RESET_STATE_IDX0(dahlia);
        break;
    case 8:
        
        NEXT_ANIM_STATUS(dahlia, 4, false);
        RESET_STATE_IDX0(dahlia);
        break;
    case 11:
#if defined(MAP3_S06) || defined(MAP6_S01) || defined(MAP6_S04) || defined(MAP7_S02) || \
    defined(MAP7_S03)
        NEXT_ANIM_STATUS_OTHER(dahlia, 7, true, 15);
#else
        NEXT_ANIM_STATUS(dahlia, 7, false);
#endif
        RESET_STATE_IDX0(dahlia);
        break;
    case 9:
        NEXT_ANIM_STATUS(dahlia, 5, false);
        RESET_STATE_IDX0(dahlia);
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
        NEXT_ANIM_STATUS_OTHER(dahlia, 6, true, 13);
#else
        NEXT_ANIM_STATUS(dahlia, 6, false);
#endif
#endif
        RESET_STATE_IDX0(dahlia);
        
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
        NEXT_ANIM_STATUS_OTHER(dahlia, 8, true, 17);
        RESET_STATE_IDX0(dahlia);
        break;
    case 13:
        NEXT_ANIM_STATUS(dahlia, 9, false);
        RESET_STATE_IDX0(dahlia);
        break;
    case 14:
        NEXT_ANIM_STATUS(dahlia, 10, false);
        RESET_STATE_IDX0(dahlia);
        break;
    case 15:
        NEXT_ANIM_STATUS(dahlia, 15, false);
        RESET_STATE_IDX0(dahlia);
        break;
    case 16:
        NEXT_ANIM_STATUS(dahlia, 16, false);
        RESET_STATE_IDX0(dahlia);
        if (dahlia->model_0.anim_4.keyframeIdx_8 == 103)
        {
            DAHLIA_PROPS.stateIdx0 = 5;
            dahlia->model_0.stateStep_3 = 0;
        }
        break;
    case 17:
        NEXT_ANIM_STATUS(dahlia, 17, false);
        RESET_STATE_IDX0(dahlia);
        break;
    case 18:
        NEXT_ANIM_STATUS(dahlia, 18, false);
        RESET_STATE_IDX0(dahlia);
        break;
    case 19:
        if (dahlia->model_0.anim_4.keyframeIdx_8 >= 40 && !sharedData_800D16E4_2_s01)
        {
            func_8005F6B0(&g_SysWork.npcs_1A0[1], &(VECTOR3){Q12(138.3f), Q12(-1.1f), Q12(-100.8f)}, 3, 1);
            sharedData_800D16E4_2_s01 = 1;
        }
        
        NEXT_ANIM_STATUS_OTHER(dahlia, 19, true, 39);
        
        RESET_STATE_IDX0(dahlia);
        if (DAHLIA_PROPS.stateIdx0 != 19)
        {
            sharedData_800D16E4_2_s01 = 0;
        }
        break;
    case 20:
        NEXT_ANIM_STATUS(dahlia, 20, false);
        RESET_STATE_IDX0(dahlia);
        break;
    case 21:
        NEXT_ANIM_STATUS_OTHER(dahlia, 21, true, 43);
        RESET_STATE_IDX0(dahlia);
        break;
    case 22:
        NEXT_ANIM_STATUS_OTHER(dahlia, 22, true, 45);
        RESET_STATE_IDX0(dahlia);
        break;
    case 23:
        NEXT_ANIM_STATUS(dahlia, 23, false);
        RESET_STATE_IDX0(dahlia);
        break;
    case 24:
        NEXT_ANIM_STATUS(dahlia, 24, false);
        RESET_STATE_IDX0(dahlia);
        break;
    case 25:
        NEXT_ANIM_STATUS(dahlia, 11, false);
        func_8003DD80(30, 1);
        if (dahlia->model_0.anim_4.keyframeIdx_8 == 349)
        {
            DAHLIA_PROPS.stateIdx0 = 0x1A;
            dahlia->model_0.stateStep_3 = 0;
            break;
        }
        break;
    case 26:
        NEXT_ANIM_STATUS(dahlia, 12, false);
        RESET_STATE_IDX0(dahlia);
        break;
    case 27:
        NEXT_ANIM_STATUS(dahlia, 13, false);
        RESET_STATE_IDX0(dahlia);
        break;
    case 28:
        NEXT_ANIM_STATUS(dahlia, 25, false);
        RESET_STATE_IDX0(dahlia);
        break;
    }
    Collision_Get(&coll, dahlia->position_18.vx, dahlia->position_18.vz);
    func_8007FDE0(coll.field_8, &sfx, &pitch0, &pitch1);
#if defined(MAP6_S01)
    sfx = Sfx_Unk1606;
#else
    sfx = Sfx_Unk1489;
#endif
    switch (DAHLIA_PROPS.stateIdx0)
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
    dahlia->rotation_24.vy = ABS_ANGLE(dahlia->rotation_24.vy + Q8_TO_Q4(sharedData_800D16E0_2_s01));
    dahlia->headingAngle_3C = dahlia->rotation_24.vy;
    dahlia->moveSpeed_38 = DAHLIA_PROPS.moveDistance_126;
    dahlia->field_34 += g_DeltaTime2;

    coord->flg = 0;
    Math_MatrixRotate1(&dahlia->rotation_24, &coord->coord);
}
