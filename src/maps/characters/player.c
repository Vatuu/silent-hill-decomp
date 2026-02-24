#include "bodyprog/player_logic.h"
#include "maps/characters/player.h"

// Player-related functions kept inside map overlay for some reason.
//
// TODO:
//  - This should be a separate .c file/split in each map overlay, but for now #including this .c works.
//  - sharedData and structs that are only used in this file need to be moved from `shared.h` into `player.h`
//
// NOTES:
//  - All functions are declared in every map, but some function bodies are only included in specific maps.
//  - `sharedFunc_800CDAA8_0_s02` is the huge PlayerState function, probably best to keep that as separate file.

// NOTE: Huge PlayerState anim function, kept as separate file for now.
#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CBAE4

void sharedFunc_800D1C38_0_s00(s_SubCharacter* chara, s_PlayerExtra* extra, GsCOORDINATE2* coords)
{
    s_Collision coll;
    VECTOR3     offset;
    s32         headingAngle;
    s16         temp_v0;
    s32         temp_s0;
    s32         moveAmt;
    s32         temp_s2;
    s16         temp_s3;
    s32         scaleRestoreShift;
    u32         scaleReduceShift;
    s32         moveSpeed;
    bool        cond;
    s16         var_s0;
    s16         var_v1;

    cond = false;
    if (g_SysWork.playerWork_4C.extra_128.state_1C < PlayerState_Unk58)
    {
        cond = true;
    }

#if defined(MAP0_S00)
    else if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_Unk74)
    {
        cond = g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP1_S02;
    }

#elif defined(MAP1_S01) || defined(MAP1_S02) || defined(MAP1_S03) || defined(MAP1_S06) || \
      defined(MAP2_S00) || defined(MAP3_S01) || defined(MAP3_S03) || defined(MAP3_S04) || \
      defined(MAP3_S05) || defined(MAP4_S03) || defined(MAP4_S05) || defined(MAP5_S00) || \
      defined(MAP5_S02) || defined(MAP5_S03) || defined(MAP7_S01) || defined(MAP7_S02) || \
      defined(MAP7_S03)

    else
    {
        switch (g_SysWork.playerWork_4C.extra_128.state_1C)
        {
#ifdef HAS_PlayerState_Unk128
            case PlayerState_Unk128:
                cond = 1;
                break;
#endif

#ifdef HAS_PlayerState_Unk129
            case PlayerState_Unk129:
                cond = 1;
                break;
#endif

#ifdef HAS_PlayerState_Unk109
            case PlayerState_Unk109:
                cond = 1;
                break;
#endif

#ifdef HAS_PlayerState_Unk176
            case PlayerState_Unk176:
                cond = 1;
                break;
#endif

#ifdef HAS_PlayerState_Unk59
            case PlayerState_Unk59:
                cond = 1;
                break;
#endif

#ifdef HAS_PlayerState_Unk60
            case PlayerState_Unk60:
                cond = 1;
                break;
#endif

#ifdef HAS_PlayerState_Unk81
            case PlayerState_Unk81:
                cond = 1;
                break;
#endif

#ifdef HAS_PlayerState_Unk74
            case PlayerState_Unk74:
                cond = (g_SavegamePtr->mapOverlayId_A4 == 5);
                break;
#endif

            default:
                cond = 0;
                break;
        }
    }
#endif

#if defined(MAP0_S01)
    if (g_SysWork.playerWork_4C.extra_128.state_1C == PlayerState_Unk53)
    {
        cond = false;
    }
#endif

    if (cond)
    {
        Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);

        temp_s2 = Math_Sin(chara->headingAngle_3C);
        temp_s2 = Q12_MULT(chara->moveSpeed_38, temp_s2);
        temp_s0 = Math_Cos(chara->headingAngle_3C);
        temp_s0 = Q12_MULT(chara->moveSpeed_38, temp_s0);

        temp_s3 = Math_Cos(ABS(coll.field_4) >> 3); // `/ 8`.
        temp_v0 = Math_Cos(ABS(coll.field_6) >> 3); // `/ 8`.

        var_s0 = Q12_MULT(Q12_MULT(temp_s2, temp_s3), temp_s3);
        var_v1 = Q12_MULT(Q12_MULT(temp_s0, temp_v0), temp_v0);
    }
    else
    {
        var_s0 = Q12_MULT(chara->moveSpeed_38, Math_Sin(chara->headingAngle_3C));
        var_v1 = Q12_MULT(chara->moveSpeed_38, Math_Cos(chara->headingAngle_3C));
    }

    if (chara->moveSpeed_38 >= 0)
    {
        chara->moveSpeed_38 = SquareRoot0(SQUARE(var_s0) + SQUARE(var_v1));
    }
    else
    {
        chara->moveSpeed_38 = -SquareRoot0(SQUARE(var_s0) + SQUARE(var_v1));
    }

    moveSpeed    = chara->moveSpeed_38;
    headingAngle = chara->headingAngle_3C;
    moveAmt      = Q12_MULT_PRECISE(moveSpeed, g_DeltaTime);

    scaleRestoreShift = OVERFLOW_GUARD(moveAmt);
    scaleReduceShift  = scaleRestoreShift >> 1;

    offset.vx = Q12_MULT_PRECISE(moveAmt >> scaleReduceShift, Math_Sin(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vz = Q12_MULT_PRECISE(moveAmt >> scaleReduceShift, Math_Cos(headingAngle) >> scaleReduceShift) << scaleRestoreShift;
    offset.vy = Q12_MULT_PRECISE(chara->fallSpeed_34, g_DeltaTime);

    if (cond)
    {
        // Most maps use `D_800C4590` from bodyprog, but some use struct from inside map overlay.
#if defined(MAP0_S00) || defined(MAP2_S01) || defined(MAP3_S00) || defined(MAP3_S06) || \
    defined(MAP5_S02) || defined(MAP5_S03) || defined(MAP6_S01) || defined(MAP6_S04) || \
    defined(MAP7_S02) || defined(MAP7_S03)
    #define UnkStruct sharedData_800E39BC_0_s00
#else
    #define UnkStruct D_800C4590
#endif
        func_80069B24(&UnkStruct, &offset, chara);
        chara->position_18.vx += UnkStruct.offset_0.vx;
        chara->position_18.vy += UnkStruct.offset_0.vy;
        chara->position_18.vz += UnkStruct.offset_0.vz;

        if (UnkStruct.field_14 == 0)
        {
            UnkStruct.field_C = chara->properties_E4.player.positionY_EC;
        }

        if (chara->position_18.vy > UnkStruct.field_C)
        {
            chara->position_18.vy = UnkStruct.field_C;
            chara->fallSpeed_34   = Q12(0.0f);
        }
    }
    else
    {
        chara->position_18.vx += offset.vx;
        chara->position_18.vz += offset.vz;

        if (g_SysWork.playerWork_4C.extra_128.state_1C < PlayerState_Unk87 ||
            (g_SysWork.playerWork_4C.extra_128.state_1C >= PlayerState_Unk89 && g_SysWork.playerWork_4C.extra_128.state_1C != PlayerState_Unk106))
        {
            chara->position_18.vy = Q12(0.0f);
        }

        chara->fallSpeed_34 = Q12(0.0f);
    }

    if (g_DeltaTime == Q12(0.0f))
    {
        chara->rotationSpeed_2C.vy = Q12_ANGLE(0.0f);
    }
    else
    {
        chara->rotationSpeed_2C.vy = FP_TO(sharedData_800E39D8_0_s00, 8) / g_DeltaTime;
    }

    coords->coord.t[0] = Q12_TO_Q8(chara->position_18.vx);
    coords->coord.t[1] = Q12_TO_Q8(chara->position_18.vy);
    coords->coord.t[2] = Q12_TO_Q8(chara->position_18.vz);
}

void sharedFunc_800D209C_0_s00(void)
{
    g_SysWork.playerCombat_38.weaponAttack_F = NO_VALUE;
    g_SavegamePtr->equippedWeapon_AA         = InventoryItemId_Unequipped;

    Player_ControlFreeze();
    sharedFunc_800D2C7C_0_s00(PlayerState_Unk84);
}

void Player_MatchArmAnimDisable(void)
{
    g_SysWork.enablePlayerMatchAnim_2358 = false;
}

void Player_ControlFreeze(void)
{
    s_PlayerExtra*  playerExtra;
    s_SubCharacter* playerChara;

    playerExtra = &g_SysWork.playerWork_4C.extra_128;
    playerChara = &g_SysWork.playerWork_4C.player_0;

    sharedData_800DD59C_0_s00 = NO_VALUE;

    D_800C457C                       = 0;
    D_800C4588                       = 0;
    g_Player_DisableControl          = true;
    g_Player_IsInWalkToRunTransition = false;

    D_800AF216 = 0;

    playerChara->properties_E4.player.afkTimer_E8        = Q12(0.0f);
    playerChara->properties_E4.player.runTimer_F8        = Q12(0.0f);
    playerChara->properties_E4.player.exhaustionTimer_FC = Q12(0.0f);

    Player_ExtraStateSet(playerChara, playerExtra, PlayerState_Unk52);

    g_Player_IsShooting          = false;
    g_Player_IsAttacking         = false;
    g_Player_IsHoldAttack        = false;
    g_Player_IsAiming            = false;
    g_Player_IsRunning           = false;
    g_Player_IsMovingBackward    = false;
    g_Player_IsMovingForward     = false;
    g_Player_IsSteppingRightTap  = false;
    g_Player_IsSteppingRightHold = false;
    g_Player_IsTurningRight      = false;
    g_Player_IsSteppingLeftTap   = false;
    g_Player_IsSteppingLeftHold  = false;
    g_Player_IsTurningLeft       = false;

    sharedData_800E39D8_0_s00 = 0;

    playerChara->field_D4.field_2                               = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_Unk4 | PlayerFlag_Unk5;
    playerChara->flags_3E                                      |= CharaFlag_Unk4;
    playerChara->field_E1_0                                     = 4;

    if (g_SysWork.playerCombat_38.weaponAttack_F < WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
    {
        g_SysWork.playerCombat_38.weaponAttack_F = WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F);
    }
}

void Player_ControlUnfreeze(bool setIdle)
{
    s_SubCharacter* player;
    s_PlayerExtra*  extra;

    g_Player_DisableControl = false;

    extra  = &g_SysWork.playerWork_4C.extra_128;
    player = &g_SysWork.playerWork_4C.player_0;

    if (setIdle)
    {
        g_SysWork.playerWork_4C.extra_128.state_1C          = PlayerState_None;
        g_SysWork.playerWork_4C.extra_128.upperBodyState_20 = PlayerUpperBodyState_None;
        g_SysWork.playerWork_4C.extra_128.lowerBodyState_24 = PlayerLowerBodyState_None;

        // TODO: Will `Character_AnimSet` work here?
        player->model_0.anim_4.status_0      = ANIM_STATUS(HarryAnim_Idle, true);
        player->model_0.anim_4.keyframeIdx_8 = 503;
        extra->model_0.anim_4.status_0       = ANIM_STATUS(HarryAnim_Idle, true);
        extra->model_0.anim_4.keyframeIdx_8  = 503;
        player->model_0.anim_4.time_4        = Q12(503);
        player->model_0.anim_4.alpha_A       = Q12(1.0f);
        extra->model_0.anim_4.time_4         = Q12(503);
        extra->model_0.anim_4.alpha_A        = Q12(1.0f);
    }
    else
    {
        Player_ExtraStateSet(player, extra, PlayerState_None);
    }

    player->attackReceived_41 = NO_VALUE;
    player->field_40          = NO_VALUE;
    g_SysWork.npcIdxs_2354[1] = NO_VALUE;
    g_SysWork.npcIdxs_2354[0] = NO_VALUE;

#if !defined(MAP0_S00) && !defined(MAP0_S01)
    func_8003D01C();
#endif

    g_Player_IsShooting          = false;
    g_Player_IsAttacking         = false;
    g_Player_IsHoldAttack        = false;
    g_Player_IsAiming            = false;
    g_Player_IsRunning           = false;
    g_Player_IsMovingBackward    = false;
    g_Player_IsMovingForward     = false;
    g_Player_IsSteppingRightTap  = false;
    g_Player_IsSteppingRightHold = false;
    g_Player_IsTurningRight      = false;
    g_Player_IsSteppingLeftTap   = false;
    g_Player_IsSteppingLeftHold  = false;
    g_Player_IsTurningLeft       = false;

    g_SysWork.playerCombat_38.isAiming_13 = false;

    player->field_D4.field_2                                    = Q12(0.23f);
    g_SysWork.playerWork_4C.player_0.field_C8.field_0                = Q12(-1.6f);
    g_SysWork.playerWork_4C.player_0.field_C8.field_6                = Q12(-1.1f);
    g_SysWork.playerWork_4C.player_0.field_C8.field_2                = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_6              = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.field_D8.offsetX_4              = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.field_D8.offsetZ_2              = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.field_D8.offsetX_0              = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~(PlayerFlag_Unk2 |
                                                                    PlayerFlag_Unk13 |
                                                                    PlayerFlag_DamageReceived |
                                                                    PlayerFlag_Moving);

    player->flags_3E  &= ~CharaFlag_Unk4;
    player->field_E1_0 = 3;

    Player_AnimFlagsSet(AnimFlag_Unlocked);

    g_Player_PrevPosition.vx = player->position_18.vx;
    g_Player_PrevPosition.vz = player->position_18.vz;

#if !defined(MAP0_S00)
    g_Player_FlexRotationY = Q12_ANGLE(0.0f);
    g_Player_FlexRotationX = Q12_ANGLE(0.0f);
#endif
}

// Very similar to `sharedFunc_800D8A00_0_s00`, but that func is for NPCs.
bool sharedFunc_800D23EC_0_s00(s32 playerExtraState, VECTOR3* vec, q3_12 angle, s32 vecCount)
{
#if defined(MAP0_S00) || defined(MAP1_S02) || defined(MAP3_S05) || defined(MAP4_S05) || \
    defined(MAP7_S00) || defined(MAP7_S01)

    #define ANGLE_THRESHOLD (Q12_ANGLE(360.0) >> 6) // 360 / 64 = 5.625 degrees.

    VECTOR3*        localVec;
    s32             playerVecDist;
    s16             playerRotDelta;
    s32             angleStep;
    s_SubCharacter* playerChara;
    s_PlayerExtra*  playerExtra;

    angle       = Q12_ANGLE_ABS(angle);
    playerExtra = &g_SysWork.playerWork_4C.extra_128;
    playerChara = &g_SysWork.playerWork_4C.player_0;
    localVec    = vec;

    g_Player_FlexRotationY = Q12_ANGLE(0.0f);

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

            sharedData_800E39E0_0_s00 = Q12_ANGLE_ABS(ratan2(localVec->vx - playerChara->position_18.vx, localVec->vz - playerChara->position_18.vz));
            Math_ShortestAngleGet(playerChara->rotation_24.vy, sharedData_800E39E0_0_s00, &playerRotDelta);

            if (ABS(playerRotDelta) < ANGLE_THRESHOLD)
            {
                playerChara->rotation_24.vy = sharedData_800E39E0_0_s00;
                D_800C4588                  = 3;
                break;
            }

            if (playerRotDelta < Q12_ANGLE(0.0f))
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
            playerVecDist = SquareRoot0(Q12_2D_DISTANCE_SQR(localVec[0], playerChara->position_18));
            if (ABS((int)playerVecDist) < Q8(0.15f)) // @hack Needs to be `int` for `ABS` to match?
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
            sharedData_800E39E0_0_s00 = Q12_ANGLE_ABS(ratan2(localVec[sharedData_800DD5A4_0_s00].vx -
                                                            playerChara->position_18.vx, localVec[sharedData_800DD5A4_0_s00].vz -
                                                            playerChara->position_18.vz));
            if (sharedData_800DD5A4_0_s00 + 1 < vecCount)
            {
                sharedData_800E39E2_0_s00 = Q12_ANGLE_ABS(ratan2(localVec[sharedData_800DD5A4_0_s00 + 1].vx -
                                                                playerChara->position_18.vx, localVec[sharedData_800DD5A4_0_s00 + 1].vz -
                                                                playerChara->position_18.vz));
            }
            else
            {
                sharedData_800E39E2_0_s00 = sharedData_800E39E0_0_s00;
            }

            sharedData_800DD5A0_0_s00 = SquareRoot0(Q12_2D_DISTANCE_SQR(localVec[sharedData_800DD5A4_0_s00], playerChara->position_18));
            D_800C4588                = 5;

            Math_ShortestAngleGet(playerChara->rotation_24.vy, sharedData_800E39E2_0_s00, &g_Player_FlexRotationY);

            g_Player_FlexRotationY = CLAMP(g_Player_FlexRotationY, Q12_ANGLE(-45.0f), Q12_ANGLE(45.0f));

            break;

        case 5:
            if (sharedData_800DD5A4_0_s00 + 1 < vecCount)
            {
                sharedData_800E39E2_0_s00 = ratan2(localVec[sharedData_800DD5A4_0_s00 + 1].vx -
                                                   playerChara->position_18.vx, localVec[sharedData_800DD5A4_0_s00 + 1].vz -
                                                   playerChara->position_18.vz);
            }
            else
            {
                sharedData_800E39E2_0_s00 = ratan2(localVec[sharedData_800DD5A4_0_s00].vx -
                                                   playerChara->position_18.vx, localVec[sharedData_800DD5A4_0_s00].vz -
                                                   playerChara->position_18.vz);
            }

            sharedData_800E39E2_0_s00 = Q12_ANGLE_ABS(sharedData_800E39E2_0_s00);

            Math_ShortestAngleGet(playerChara->rotation_24.vy, sharedData_800E39E2_0_s00, &playerRotDelta);

            // Turn toward.
            angleStep = TIMESTEP_SCALE_30_FPS(g_DeltaTime, (playerRotDelta < Q12_ANGLE(45.0f)) ? Q12_ANGLE(2.9f) : Q12_ANGLE(22.5f));

            if (ABS(playerRotDelta) < ANGLE_THRESHOLD)
            {
                playerChara->rotation_24.vy = sharedData_800E39E2_0_s00;
            }
            else if (playerRotDelta < Q12_ANGLE(0.0f))
            {
                playerChara->rotation_24.vy -= angleStep;
            }
            else
            {
                playerChara->rotation_24.vy += angleStep;
            }

            playerChara->rotation_24.vy = Q12_ANGLE_ABS(playerChara->rotation_24.vy);

            playerVecDist = SquareRoot0(Q12_2D_DISTANCE_SQR(localVec[sharedData_800DD5A4_0_s00], playerChara->position_18));

            // Uses `playerExtraState` index to work out distance to check against? Odd.
            if (playerVecDist < Q12_TO_Q8((playerExtraState - 53) * Q12(0.15f) + Q12(0.15f)) ||
                (sharedData_800DD5A0_0_s00 < playerVecDist && sharedData_800DD5A4_0_s00 != vecCount - 1))
            {
                sharedData_800DD5A4_0_s00++;

                playerVecDist = SquareRoot0(Q12_2D_DISTANCE_SQR(localVec[sharedData_800DD5A4_0_s00], playerChara->position_18));

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
            g_Player_FlexRotationY = CLAMP(g_Player_FlexRotationY, Q12_ANGLE(-45.0f), Q12_ANGLE(45.0f));
            break;

        case 6:
            Math_ShortestAngleGet(playerChara->rotation_24.vy, angle, &playerRotDelta);
            if (ABS(playerRotDelta) < ANGLE_THRESHOLD)
            {
                playerChara->rotation_24.vy = angle;
                D_800C4588                  = 8;
                break;
            }

            if (playerRotDelta < Q12_ANGLE(0.0f))
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
            g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
            return true;
    }
#endif
    return false;
}

void sharedFunc_800D2C7C_0_s00(s32 playerExtraState)
{
    s_SubCharacter* player;
    s_PlayerExtra*  extra;

    extra  = &g_SysWork.playerWork_4C.extra_128;
    player = &g_SysWork.playerWork_4C.player_0;

    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);

    D_800C4606 = 0;

    switch (playerExtraState)
    {
        case PlayerState_Unk54:
            D_800C457C = 0;
            break;

        case PlayerState_Unk53:
            D_800C457C = 1;
            break;

        case PlayerState_Unk56:
            D_800C457C = 3;
            break;

        case PlayerState_Unk57:
            D_800C457C = 4;
            break;
    }

    Player_ExtraStateSet(player, extra, playerExtraState);
}

void sharedFunc_800D2D2C_0_s00(void)
{
    D_800C4606++;
}

void Player_AnimLock(void)
{
    Player_AnimFlagsClear(AnimFlag_Unlocked);
}

s32 Player_AnimIsLocked(void)
{
    return ~(g_SysWork.playerWork_4C.player_0.model_0.anim_4.flags_2 & AnimFlag_Unlocked);
}

void Player_AnimUnlock(void)
{
    Player_AnimFlagsSet(AnimFlag_Unlocked);
}

s32 sharedFunc_800D2DAC_0_s00(void)
{
    s_Model*    model;
    s_AnimInfo* animInfo;

    // NOTE: There are 37 base anims for Harry. 38 and beyond are map-specific.
    model    = &g_SysWork.playerWork_4C.player_0.model_0;
    animInfo = &g_MapOverlayHeader.animInfos_34[model->anim_4.status_0 - ANIM_STATUS(38, false)];

    if (animInfo->updateFunc_0 == Anim_Update0)
    {
        // Check if anim has started or finished.
        if (Anim_DurationGet(model, animInfo) > Q12(0.0f))
        {
            return model->anim_4.keyframeIdx_8 == animInfo->endKeyframeIdx_E;
        }
        else
        {
            return model->anim_4.keyframeIdx_8 == animInfo->startKeyframeIdx_C;
        }
    }

    if (animInfo->updateFunc_0 == Anim_Update2)
    {
        return -2;
    }
    else
    {
        return -1;
    }
}

bool Player_MoveDistanceIsZero(void)
{
    return g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 == Q12(0.0f);
}

void Player_MoveDistanceClear(void)
{
    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
}

void sharedFunc_800D2E6C_0_s00(void)
{
#if defined(MAP0_S01)
    g_SysWork.playerCombat_38.weaponAttack_F = WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap);
    WorldGfx_PlayerPrevHeldItem(&g_SysWork.playerCombat_38);

    g_SysWork.playerCombat_38.weaponAttack_F = NO_VALUE;

    func_8003D03C();
#endif
}

void Player_FallBackward(void)
{
#if defined(MAP0_S01)
    s_SubCharacter* playerChara;
    s_PlayerExtra*  playerExtra;

    playerChara = &g_SysWork.playerWork_4C.player_0;
    playerExtra = &g_SysWork.playerWork_4C.extra_128;

    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(2.3f);
    g_SysWork.playerWork_4C.player_0.properties_E4.player.headingAngle_124       = Q12_ANGLE(180.0f);
    g_Player_HeadingAngle                                                   = Q12_ANGLE(180.0f);

    Player_ExtraStateSet(playerChara, playerExtra, PlayerState_FallBackward);
#endif
}

void sharedFunc_800D2E7C_0_s00(void)
{
}

void Player_DamageFeetFront(void)
{
#if defined(MAP6_S04)
    s_SubCharacter* playerChara;
    s_PlayerExtra*  playerExtra;

    playerChara = &g_SysWork.playerWork_4C.player_0;
    playerExtra = &g_SysWork.playerWork_4C.extra_128;

    func_8005DC1C(Sfx_Unk1317, &playerChara->position_18, Q8_CLAMPED(0.125f), 0);

    Player_ExtraStateSet(playerChara, playerExtra, PlayerState_DamageFeetFront);
#endif
}

void sharedFunc_800D2E8C_0_s00(q19_12 posX, q19_12 posZ, VECTOR3* vec)
{
#if defined(MAP1_S05)
    q19_12          angle;
    s32             vecSqr;
    s32             playerExtraState;
    s_SubCharacter* playerChara;
    s_PlayerExtra*  playerExtra;

    playerChara = &g_SysWork.playerWork_4C.player_0;
    playerExtra = &g_SysWork.playerWork_4C.extra_128;

    if (vec->vx == 0 && vec->vz == 0)
    {
        if (D_800D587C != 0)
        {
            D_800D587C = 0;
        }
    }
    else
    {
        g_SysWork.playerWork_4C.player_0.properties_E4.player.field_118 = Q12_ANGLE_ABS(ratan2(vec->vx, vec->vz));
    }

    if (posX == Q12(0.0f) && posZ == Q12(0.0f))
    {
        return;
    }

    D_800C45B0.vx = posX;
    D_800C45B0.vz = posZ;

    if (g_SysWork.npcs_1A0[0].health_B0 <= Q12(0.0f) || g_Player_IsInWalkToRunTransition || playerChara->health_B0 <= Q12(0.0f))
    {
        return;
    }

    vecSqr      = SQUARE(vec->vx) + SQUARE(vec->vz);
    D_800D587C += SquareRoot0(vecSqr);

    if (vecSqr > Q12(0.75f))
    {
        if (g_SysWork.playerWork_4C.extra_128.state_1C < PlayerState_DamagePushBack || g_SysWork.playerWork_4C.extra_128.state_1C >= PlayerState_Unk31)
        {
            angle = Q12_ANGLE_ABS(Q12_ANGLE_ABS(ratan2(vec->vx, vec->vz)) - (u16)playerChara->rotation_24.vy);

            if (D_800D587C > Q12(1.75f))
            {
                if (g_SysWork.playerWork_4C.extra_128.state_1C >= 23 && g_SysWork.playerWork_4C.extra_128.state_1C < 27)
                {
                    playerChara->model_0.stateStep_3 = 0;
                    playerChara->model_0.controlState_2     = ModelState_Uninitialized;
                    playerExtra->model_0.stateStep_3 = 0;
                    playerExtra->model_0.controlState_2     = ModelState_Uninitialized;
                }

                if (angle >= Q12_ANGLE(90.0f) && angle < Q12_ANGLE(270.0f))
                {
                    playerExtraState = PlayerState_DamagePushFront;
                }
                else
                {
                    playerExtraState = PlayerState_DamagePushBack;
                }

                Player_ExtraStateSet(playerChara, playerExtra, playerExtraState);
                func_8005DC1C(Sfx_Unk1326, &playerChara->position_18, Q8_CLAMPED(0.125f), 0);
            }
            else if ((g_SysWork.playerWork_4C.extra_128.state_1C < PlayerState_DamageTorsoBack || g_SysWork.playerWork_4C.extra_128.state_1C >= PlayerState_DamageFeetFront) &&
                     g_SysWork.playerWork_4C.extra_128.state_1C != PlayerState_DamagePushBack &&
                     g_SysWork.playerWork_4C.extra_128.state_1C != PlayerState_DamagePushFront)
            {
                if (angle >= Q12_ANGLE(45.0f) && angle < Q12_ANGLE(135.0f))
                {
                    playerExtraState = PlayerState_DamageTorsoLeft;
                }
                else if (angle >= Q12_ANGLE(135.0f) && angle < Q12_ANGLE(225.0f))
                {
                    playerExtraState = PlayerState_DamageTorsoFront;
                }
                else if (angle >= Q12_ANGLE(225.0f) && angle < Q12_ANGLE(315.0f))
                {
                    playerExtraState = PlayerState_DamageTorsoRight;
                }
                else
                {
                    playerExtraState = PlayerState_DamageTorsoBack;
                }

                Player_ExtraStateSet(playerChara, playerExtra, playerExtraState);
            }

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk12;

            playerChara->properties_E4.player.afkTimer_E8 = Q12(0.0f);
            playerChara->properties_E4.player.field_F4    = 0;
            g_SysWork.playerCombat_38.isAiming_13     = false;
            playerChara->field_44.field_0                 = NO_VALUE;

            g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;

            playerChara->field_44.field_0 = NO_VALUE; // Redundant set needed for match.
        }
    }

    if (vecSqr > Q12(1.75f))
    {
        playerChara->damage_B4.amount_C = SquareRoot0(vecSqr) * 4;
    }
    else
    {
        playerChara->damage_B4.amount_C = SquareRoot0(vecSqr) * 64;
    }

    if (!(g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C & PlayerFlag_DamageReceived) &&
        vecSqr > Q12(0.75f) && vecSqr <= Q12(1.75f))
    {
        func_8005DC1C(Sfx_Unk1327, &playerChara->position_18, Q8_CLAMPED(0.125f), 0);

        playerChara->properties_E4.player.field_10C = 64;
        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C |= PlayerFlag_DamageReceived;
    }

    if (playerChara->damage_B4.amount_C != Q12(0.0f))
    {
        g_SysWork.playerWork_4C.player_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;

        playerChara->health_B0 -= playerChara->damage_B4.amount_C;
        func_800893D0(playerChara->damage_B4.amount_C);
        playerChara->damage_B4.amount_C = Q12(0.0f);
    }
#endif
}

bool sharedFunc_800D2E94_0_s00(void)
{
#if defined(MAP2_S00)
    s_SubCharacter* npcChara;
    s32             playerDist;

    npcChara = &g_SysWork.npcs_1A0[5];

    if (g_SysWork.playerWork_4C.player_0.position_18.vx < Q12(-255.0f) &&
        g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(-110.0f) &&
        g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(-100.0f))
    {
        playerDist = SquareRoot0(SQUARE(Q12(-262.0f) - g_SysWork.playerWork_4C.player_0.position_18.vx) +
                                 SQUARE(Q12(-104.0f) - g_SysWork.playerWork_4C.player_0.position_18.vz));

        if (npcChara->model_0.controlState_2 == ModelState_Uninitialized || npcChara->model_0.stateStep_3 == 0)
        {
            npcChara->health_B0 = Q12(400.0f);
            npcChara->model_0.controlState_2++;
            npcChara->field_C8.field_0   = Q12(-0.2f);
            npcChara->field_C8.field_2   = Q12(0.2f);
            npcChara->field_D4.radius_0   = Q12(0.05f);
            npcChara->field_D4.field_2   = Q12(0.5f);
            npcChara->field_40           = 0;
            npcChara->field_C8.field_6   = 0;
            npcChara->field_C8.field_8   = 0;
            npcChara->field_D8.offsetZ_6 = Q12(0.0f);
            npcChara->field_D8.offsetX_4 = Q12(0.0f);
            npcChara->field_D8.offsetZ_2 = Q12(0.0f);
            npcChara->field_D8.offsetX_0 = Q12(0.0f);
            npcChara->position_18.vx     = Q12(-262.0f);
            npcChara->position_18.vy     = Q12(-1.1f);
            npcChara->position_18.vz     = Q12(-104.0f);
            npcChara->field_E1_0         = 3;
            npcChara->model_0.stateStep_3++;
            npcChara->flags_3E               |= CharaFlag_Unk3;
            npcChara->model_0.anim_4.flags_2 &= ~(AnimFlag_Visible | AnimFlag_Unlocked);
        }

        // TODO: `else` branch is duplicated here, is there some way to merge them? Decompiler used `goto`.
        if (npcChara->health_B0 > Q12(0.0f))
        {
            if (playerDist < Q12(2.0f) &&
                Savegame_EventFlagGet(EventFlag_167) && !Savegame_EventFlagGet(EventFlag_168) &&
                g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_KitchenKnife, AttackInputType_Tap))
            {
                npcChara->model_0.charaId_0 = Chara_Padlock;
            }
            else
            {
                if (npcChara->health_B0 <= Q12(0.0f))
                {
                    if (Savegame_EventFlagGet(EventFlag_167) && npcChara->model_0.charaId_0 == Chara_Padlock)
                    {
                        npcChara->flags_3E |= CharaFlag_Unk1;
                        Savegame_EventFlagSet(EventFlag_168);
                    }
                }

                npcChara->model_0.charaId_0 = Chara_None;
            }
        }
        else
        {
            if (Savegame_EventFlagGet(EventFlag_167) && npcChara->model_0.charaId_0 == Chara_Padlock)
            {
                npcChara->flags_3E |= CharaFlag_Unk1;
                Savegame_EventFlagSet(EventFlag_168);
            }
            npcChara->model_0.charaId_0 = Chara_None;
        }

        if (npcChara->damage_B4.amount_C != Q12(0.0f))
        {
            if (WEAPON_ATTACK_ID_GET(g_SysWork.playerCombat_38.weaponAttack_F) == EquippedWeaponId_KitchenKnife)
            {
                npcChara->damage_B4.amount_C >>= 1;
            }

            // Apply `damageReceived` to character health.
            if (g_SysWork.playerCombat_38.weaponAttack_F >= WEAPON_ATTACK(EquippedWeaponId_Handgun, AttackInputType_Tap))
            {
                npcChara->health_B0 = NO_VALUE;
            }
            else
            {
                npcChara->health_B0 -= npcChara->damage_B4.amount_C;
            }

            npcChara->damage_B4.amount_C = Q12(0.0f);
        }

        return true;
    }

    npcChara->model_0.controlState_2     = ModelState_Uninitialized;
    npcChara->model_0.stateStep_3 = 0;
    npcChara->model_0.charaId_0   = Chara_None;
    npcChara->health_B0           = Q12(0.0f);
#endif
    return false;
}

/** @brief Checks if two angles are within the forward arc.
 *
 * @param angle0 First angle.
 * @param angle1 Second angle.
 * @return `true` if the angles are within the forward arc, `false` otherwise.
 */
static inline bool Math_AngleFrontCheck(q4_12 angle0, q4_12 angle1)
{
    q19_12 angleDelta = Q12_ANGLE_ABS(angle0 - angle1);
    return angleDelta < Q12_ANGLE(90.0f) || angleDelta >= Q12_ANGLE(270.0f);
}

void sharedFunc_800D2E9C_0_s00(q19_12* offsetX, q19_12* offsetZ, q3_12* angle)
{
#if defined(MAP2_S00) || defined(MAP2_S02) || defined(MAP4_S02) || defined(MAP5_S01) || defined(MAP6_S00)
    VECTOR3 vec; // Q19.12
    q3_12   headingAngle;
    q3_12   angle0;
    bool    isInFront;

    g_SysWork.playerWork_4C.player_0.properties_E4.player.moveDistance_126 = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.headingAngle_3C                       = Q12_ANGLE(0.0f);
    isInFront                                                              = Math_AngleFrontCheck(*angle, g_SysWork.playerWork_4C.player_0.rotation_24.vy);

    angle--; // @hack Permuter find, needed for match.
    angle++;

    if (!isInFront)
    {
        D_800C4610.vx = *offsetX + FP_FROM(( Math_Cos(*angle) * -0x16C) + (Math_Sin(*angle) * -0x6B0), Q12_SHIFT);
        D_800C4610.vz = *offsetZ + FP_FROM((-Math_Sin(*angle) * -0x16C) + (Math_Cos(*angle) * -0x6B0), Q12_SHIFT);
    }
    else
    {
        D_800C4610.vx = *offsetX + FP_FROM(( Math_Cos(*angle) * -0xCB) + (Math_Sin(*angle) * 0x3C6), Q12_SHIFT);
        D_800C4610.vz = *offsetZ + FP_FROM((-Math_Sin(*angle) * -0xCB) + (Math_Cos(*angle) * 0x3C6), Q12_SHIFT);
    }

    headingAngle = g_SysWork.playerWork_4C.player_0.headingAngle_3C;
    vec.vx       = Math_Sin(headingAngle); // @unused
    vec.vx       = Q12(0.0f);
    vec.vz       = Math_Cos(headingAngle); // @unused
    vec.vz       = Q12(0.0f);

    vec.vx = D_800C4610.vx - g_SysWork.playerWork_4C.player_0.position_18.vx;
    vec.vz = D_800C4610.vz - g_SysWork.playerWork_4C.player_0.position_18.vz;
    vec.vy = Q12_MULT_PRECISE(g_SysWork.playerWork_4C.player_0.fallSpeed_34, g_DeltaTime);

    func_80069B24(&D_800C4590, &vec, &g_SysWork.playerWork_4C.player_0);

    D_800C4610.vx = g_SysWork.playerWork_4C.player_0.position_18.vx + D_800C4590.offset_0.vx;
    D_800C4610.vz = g_SysWork.playerWork_4C.player_0.position_18.vz + D_800C4590.offset_0.vz;

    // TODO: Convert hex to float or fraction.
    if (!isInFront)
    {
        angle0   = *angle + Q12_ANGLE(180.0f);
        *offsetX = D_800C4610.vx + FP_FROM(( Math_Cos(angle0) * 0x16C) + (Math_Sin(angle0) * 0x6B0), Q12_SHIFT);
        *offsetZ = D_800C4610.vz + FP_FROM((-Math_Sin(angle0) * 0x16C) + (Math_Cos(angle0) * 0x6B0), Q12_SHIFT);
    }
    else
    {
        angle0   = *angle;
        *offsetX = D_800C4610.vx + FP_FROM(( Math_Cos(angle0) * 0xCB) + (Math_Sin(angle0) * -0x3C6), Q12_SHIFT);
        *offsetZ = D_800C4610.vz + FP_FROM((-Math_Sin(angle0) * 0xCB) + (Math_Cos(angle0) * -0x3C6), Q12_SHIFT);
    }
#endif
}

s32 sharedFunc_800D2EA4_0_s00(void)
{
    return g_SysWork.playerWork_4C.player_0.properties_E4.player.field_10D;
}

void sharedFunc_800D2EB4_0_s00(void)
{
    u8 prevVar;

    prevVar = g_SysWork.playerCombat_38.weaponAttack_F;
    g_SysWork.playerCombat_38.weaponAttack_F = NO_VALUE;
    sharedData_800DD59C_0_s00 = prevVar;

    WorldGfx_HeldItemAttach(Chara_Harry, MODEL_BONE(1, 1));
}

void sharedFunc_800D2EF4_0_s00(void)
{
    g_SysWork.playerCombat_38.weaponAttack_F = sharedData_800DD59C_0_s00;
}

