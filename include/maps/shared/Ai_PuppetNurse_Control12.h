void Ai_PuppetNurse_Control12(s_SubCharacter* nurse)
{
    s32             angleDeltaToPlayer;
    s16             angleDeltaAbs;
    s32             distToPlayer;
    s32             cond;
    s32             animStatus;
    s_SubCharacter* nurseCpy;

    animStatus         = nurse->model_0.anim_4.status_0;
    angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(nurse->position_18, g_SysWork.playerWork_4C.player_0.position_18) - nurse->rotation_24.vy);
    angleDeltaAbs      = abs(angleDeltaToPlayer);

    distToPlayer = Math_Vector2MagCalc((g_SysWork.playerWork_4C.player_0.position_18.vx - nurse->position_18.vx),
                                       (g_SysWork.playerWork_4C.player_0.position_18.vz - nurse->position_18.vz));

    distToPlayer = Q12_MULT_FLOAT_PRECISE(distToPlayer, 1.1f);
    cond         = sharedFunc_800CF294_3_s03(nurse, distToPlayer);

    if (g_SysWork.playerWork_4C.player_0.health_B0 < Q12(0.0f) || !cond)
    {
        nurse->model_0.controlState_2  = 9;
        nurse->model_0.stateStep_3     = 0;
        nurse->model_0.anim_4.status_0 = ANIM_STATUS(18, false);
        return;
    }

    switch (nurse->model_0.stateStep_3)
    {
        case 0:
            if (angleDeltaAbs >= Q12_ANGLE(10.1f))
            {
                s32 rotAmt = Q12_ANGLE(45.0f); // @hack? Should probably be part of the `FP_MULTIPLY_PRECISE`.
                rotAmt     = Q12_MULT_PRECISE(g_DeltaTime, rotAmt);
                if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
                {
                    nurse->rotation_24.vy += rotAmt;
                }
                else
                {
                    nurse->rotation_24.vy -= rotAmt;
                }

                Chara_MoveSpeedUpdate3(nurse, Q12(1.0f), Q12(0.0f));
                return;
            }

            nurse->model_0.stateStep_3 = 1;

        case 1:
            if (animStatus >= ANIM_STATUS(17, false) && animStatus < ANIM_STATUS(18, false))
            {
                nurse->model_0.anim_4.status_0 = ANIM_STATUS(9, false);
                nurse->model_0.stateStep_3++;
            }
            else if (animStatus >= ANIM_STATUS(18, false) && animStatus < ANIM_STATUS(19, false))
            {
                nurse->model_0.anim_4.status_0 = ANIM_STATUS(20, false);
                nurse->model_0.stateStep_3++;
            }
            else
            {
                break;
            }

            sharedFunc_800CF7F4_3_s03(nurse);

        case 2:
            nurse->field_44.field_0 = 0;
            nurseCpy                = nurse;
            distToPlayer            = sharedFunc_800CF600_3_s03(nurse);

            if (!func_80070320() && sharedFunc_800CF90C_3_s03(nurse))
            {
                if (distToPlayer < 0x199)
                {
                    nurse->model_0.controlState_2 = 5;
                    nurse->model_0.stateStep_3    = 0;
                }
            }
            else if (distToPlayer < 0x266)
            {
                if (!(g_SysWork.playerWork_4C.player_0.flags_3E & 8))
                {
                    nurseCpy->properties_E4.dummy.properties_E8[0xD].val16[1] = 0; // nurseCpy + 0x11E
                    nurse->model_0.controlState_2                             = 1;
                }
                else
                {
                    nurseCpy->properties_E4.dummy.properties_E8[0xD].val16[1] = 1; // nurseCpy + 0x11E
                    nurse->model_0.controlState_2                             = 1;
                }

                nurse->model_0.stateStep_3     = 0;
                nurse->model_0.anim_4.status_0 = ANIM_STATUS(18, false);
            }

            sharedFunc_800CF7F4_3_s03(nurse);
    }
}
