// Very similar to `sharedFunc_800D8A00_0_s00`, but that func is for NPCs.

s32 sharedFunc_800D23EC_0_s00(s32 playerExtraState, VECTOR3* vec, q3_12 angle, s32 vecCount)
{
#if defined(MAP0_S00) || defined(MAP1_S02) || defined(MAP3_S05) || defined(MAP4_S05) || \
    defined(MAP7_S00) || defined(MAP7_S01)

    #define ANGLE_THRESHOLD (FP_ANGLE(360.0) >> 6) // 360 / 64 = 5.625 degrees.

    VECTOR3*              localVec;
    int                   playerVecDist; // @hack Needs to be `int` for `ABS` to match?
    s16                   playerRotDelta;
    s32                   angleStep;
    s_MainCharacterExtra* playerExtra;
    s_SubCharacter*       playerChara;

    angle       = FP_ANGLE_ABS(angle);
    playerExtra = &g_SysWork.player_4C.extra_128;
    playerChara = &g_SysWork.player_4C.chara_0;
    localVec    = vec;

    g_Player_FlexRotationY = FP_ANGLE(0.0f);

    switch (D_800C4588)
    {
        case 0:
            sharedData_800DD5A4_0_s00 = 0;
            D_800C4588                = 1;
            break;

        case 1:
            if (localVec->vx == playerChara->position_18.vx && localVec->vz == playerChara->position_18.vz)
            {
                D_800C4588 = 6;
                break;
            }

            sharedData_800E39E0_0_s00 = FP_ANGLE_ABS(ratan2(localVec->vx - playerChara->position_18.vx, localVec->vz - playerChara->position_18.vz));
            Math_ShortestAngleGet(playerChara->rotation_24.vy, sharedData_800E39E0_0_s00, &playerRotDelta);

            if (ABS(playerRotDelta) < ANGLE_THRESHOLD)
            {
                playerChara->rotation_24.vy = sharedData_800E39E0_0_s00;
                D_800C4588                  = 3;
                break;
            }

            if (playerRotDelta < FP_ANGLE(0.0f))
            {
                D_800C457C = 4;
                Player_ExtraStateSet(playerChara, playerExtra, PlayerState_Unk57);
                D_800C4588 = 2;
            }
            else
            {
                D_800C457C = 3;
                Player_ExtraStateSet(playerChara, playerExtra, PlayerState_Unk56);
                D_800C4588 = 2;
            }

            break;

        case 2:
            Math_ShortestAngleGet(playerChara->rotation_24.vy, sharedData_800E39E0_0_s00, &playerRotDelta);
            if (ABS(playerRotDelta) < ANGLE_THRESHOLD)
            {
                playerChara->rotation_24.vy = sharedData_800E39E0_0_s00;
                D_800C4588                  = 3;
            }
            break;

        case 3:
            playerVecDist = SquareRoot0(FP_2D_DISTANCE_SQR(localVec[0], playerChara->position_18));

            if (ABS(playerVecDist) < Q8(0.15f))
            {
                Player_ExtraStateSet(playerChara, playerExtra, PlayerState_Unk52);
                D_800C4588 = 8;
                break;
            }

            Player_ExtraStateSet(playerChara, playerExtra, playerExtraState);
            switch (playerExtraState)
            {
                case PlayerState_Unk54:
                    D_800C457C = 0;
                    break;
                case PlayerState_Unk53:
                    D_800C457C = 1;
                    break;
            }

            D_800C4588 = 4;
            break;

        case 4:
            sharedData_800E39E0_0_s00 = FP_ANGLE_ABS(ratan2(localVec[sharedData_800DD5A4_0_s00].vx - playerChara->position_18.vx, localVec[sharedData_800DD5A4_0_s00].vz - playerChara->position_18.vz));
            if (sharedData_800DD5A4_0_s00 + 1 < vecCount)
            {
                sharedData_800E39E2_0_s00 = FP_ANGLE_ABS(ratan2(localVec[sharedData_800DD5A4_0_s00 + 1].vx - playerChara->position_18.vx, localVec[sharedData_800DD5A4_0_s00 + 1].vz - playerChara->position_18.vz));
            }
            else
            {
                sharedData_800E39E2_0_s00 = sharedData_800E39E0_0_s00;
            }

            sharedData_800DD5A0_0_s00 = SquareRoot0(FP_2D_DISTANCE_SQR(localVec[sharedData_800DD5A4_0_s00], playerChara->position_18));
            D_800C4588                = 5;

            Math_ShortestAngleGet(playerChara->rotation_24.vy, sharedData_800E39E2_0_s00, &g_Player_FlexRotationY);

            g_Player_FlexRotationY = CLAMP(g_Player_FlexRotationY, FP_ANGLE(-45.0f), FP_ANGLE(45.0f));

            break;

        case 5:
            if (sharedData_800DD5A4_0_s00 + 1 < vecCount)
            {
                sharedData_800E39E2_0_s00 = ratan2(localVec[sharedData_800DD5A4_0_s00 + 1].vx - playerChara->position_18.vx, localVec[sharedData_800DD5A4_0_s00 + 1].vz - playerChara->position_18.vz);
            }
            else
            {
                sharedData_800E39E2_0_s00 = ratan2(localVec[sharedData_800DD5A4_0_s00].vx - playerChara->position_18.vx, localVec[sharedData_800DD5A4_0_s00].vz - playerChara->position_18.vz);
            }

            sharedData_800E39E2_0_s00 = FP_ANGLE_ABS(sharedData_800E39E2_0_s00);

            Math_ShortestAngleGet(playerChara->rotation_24.vy, sharedData_800E39E2_0_s00, &playerRotDelta);

            // Turn toward.
            angleStep = TIMESTEP_SCALE(g_DeltaTime0, (playerRotDelta < FP_ANGLE(45.0f)) ? FP_ANGLE(2.9f) : FP_ANGLE(22.5f));

            if (ABS(playerRotDelta) < ANGLE_THRESHOLD)
            {
                playerChara->rotation_24.vy = sharedData_800E39E2_0_s00;
            }
            else if (playerRotDelta < FP_ANGLE(0.0f))
            {
                playerChara->rotation_24.vy -= angleStep;
            }
            else
            {
                playerChara->rotation_24.vy += angleStep;
            }

            playerChara->rotation_24.vy = FP_ANGLE_ABS(playerChara->rotation_24.vy);

            playerVecDist = SquareRoot0(FP_2D_DISTANCE_SQR(localVec[sharedData_800DD5A4_0_s00], playerChara->position_18));

            // Uses `playerExtraState` index to work out distance to check against? Odd.
            if (playerVecDist < Q12_TO_Q8((playerExtraState - 53) * Q12(0.15f) + Q12(0.15f)) ||
                (sharedData_800DD5A0_0_s00 < playerVecDist && sharedData_800DD5A4_0_s00 != vecCount - 1))
            {
                sharedData_800DD5A4_0_s00++;

                playerVecDist = SquareRoot0(FP_2D_DISTANCE_SQR(localVec[sharedData_800DD5A4_0_s00], playerChara->position_18));

                if (sharedData_800DD5A4_0_s00 == vecCount)
                {
                    D_800C4588 = 6;
                }
                else
                {
                    D_800C4588 = 4;
                }
            }

            sharedData_800DD5A0_0_s00 = playerVecDist;

            Math_ShortestAngleGet(playerChara->rotation_24.vy, sharedData_800E39E2_0_s00, &g_Player_FlexRotationY);
            g_Player_FlexRotationY = CLAMP(g_Player_FlexRotationY, FP_ANGLE(-45.0f), FP_ANGLE(45.0f));

            break;

        case 6:
            Math_ShortestAngleGet(playerChara->rotation_24.vy, angle, &playerRotDelta);

            if (ABS(playerRotDelta) < ANGLE_THRESHOLD)
            {
                playerChara->rotation_24.vy = angle;
                D_800C4588                  = 8;
                break;
            }

            if (playerRotDelta < FP_ANGLE(0.0f))
            {
                D_800C457C = 4;
                Player_ExtraStateSet(playerChara, playerExtra, PlayerState_Unk57);
            }
            else
            {
                D_800C457C = 3;
                Player_ExtraStateSet(playerChara, playerExtra, PlayerState_Unk56);
            }
            D_800C4588 = 7;

            break;

        case 7:
            Math_ShortestAngleGet(playerChara->rotation_24.vy, angle, &playerRotDelta);

            if (ABS(playerRotDelta) < ANGLE_THRESHOLD)
            {
                playerChara->rotation_24.vy = angle;
                Player_ExtraStateSet(playerChara, playerExtra, PlayerState_Unk52);
                D_800C457C = 0;
                D_800C4588 = 8;
            }
            break;

        case 8:
            D_800C4606                                                              = 1;
            sharedData_800E39E0_0_s00                                               = 0;
            D_800C4588                                                              = 0;
            g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
            return 1;
    }
#endif
    return 0;
}
