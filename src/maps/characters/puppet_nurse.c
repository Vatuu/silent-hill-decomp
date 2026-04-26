#include "bodyprog/bodyprog.h"
#include "bodyprog/events/npc_main.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/puppet_nurse.h"

// TODO:
// - Make this separate split in each map that uses it, instead of `#include`
// - Move funcdecls/structs for these out of shared.h header.

#define nurseProps nurse->properties.puppetNurse

q19_12 sharedFunc_800CD6B0_3_s03(MATRIX* mat, s32 matCount, VECTOR3* center)
{
    s32    i;
    q19_12 posX;
    q19_12 posZ;
    q23_8  minXTemp;
    q23_8  minX;
    q23_8  maxX;
    q23_8  minZTemp;
    q23_8  minZ;
    q23_8  maxZ;
    q19_12 radius;

    maxX =
    minX =
    posX = mat->t[0];

    maxZ =
    minZ =
    posZ = mat->t[2];

    mat++;

    for (i = 1; i < matCount; i++, mat++)
    {
        posX = mat->t[0];
        posZ = mat->t[2];

        // `minX = MIN(posX, minX)`
        minXTemp = minX;
        if (minXTemp >= posX)
        {
            minXTemp = posX;
        }
        minX = minXTemp;
        maxX = MAX(posX, maxX);

        // `minZ = MIN(posZ, minZ)`
        minZTemp = minZ;
        if (minZTemp >= posZ)
        {
            minZTemp = posZ;
        }
        minZ = minZTemp;
        maxZ = MAX(posZ, maxZ);
    }

    posX   = maxX - minX;
    posX   = Q8_TO_Q12(posX);
    posZ   = maxZ - minZ;
    posZ   = Q8_TO_Q12(posZ);
    radius = SquareRoot12(Q12_SQUARE_PRECISE(posX) +
                          Q12_SQUARE_PRECISE(posZ));

    posX       = Q8_TO_Q12(minX) + (posX / 2);
    posZ       = Q8_TO_Q12(minZ) + (posZ / 2);
    center->vx = posX;
    center->vz = posZ;
    return radius / 2;
}

void sharedFunc_800CD7F8_3_s03(s_SubCharacter* chara, q19_12 offsetX, q19_12 offsetZ, q19_12 range)
{
    q19_12 extraOffsetX;
    q19_12 extraOffsetZ;
    q19_12 extraDistSqr;
    q19_12 rootAdjOffsetSqr;
    q19_12 scale;
    q19_12 scaledExtraOffsetX;
    q19_12 scaledExtraOffsetZ;

    // Compute extra offset.
    extraOffsetX = chara->field_D8.offsetX_4 - offsetX;
    extraOffsetZ = chara->field_D8.offsetZ_6 - offsetZ;

    // Apply extra offset if its distance exceeds a threshold.
    extraDistSqr = Q12_SQUARE_PRECISE(extraOffsetX) +
                   Q12_SQUARE_PRECISE(extraOffsetZ);
    if (extraDistSqr > Q12_MULT_PRECISE(range, 4))
    {
        // Compute scale.
        rootAdjOffsetSqr = SquareRoot12(extraDistSqr);
        scale            = Q12(rootAdjOffsetSqr - 128) / rootAdjOffsetSqr;

        // Adjust extra X offset.
        scaledExtraOffsetX = scale * extraOffsetX;
        if (scaledExtraOffsetX < Q12(0.0f))
        {
            scaledExtraOffsetX += Q12_CLAMPED(1.0f);
        }
        extraOffsetX = FP_FROM(scaledExtraOffsetX, Q12_SHIFT);

        // Adjust extra Z offset.
        scaledExtraOffsetZ = scale * extraOffsetZ;
        if (scaledExtraOffsetZ < Q12(0.0f))
        {
            scaledExtraOffsetZ += Q12_CLAMPED(1.0f);
        }
        extraOffsetZ = FP_FROM(scaledExtraOffsetZ, Q12_SHIFT);

        // Apply extra offset.
        offsetX += extraOffsetX;
        offsetZ += extraOffsetZ;
    }

    // Set translation offset.
    chara->field_D8.offsetX_4 = offsetX;
    chara->field_D8.offsetZ_6 = offsetZ;
}

void sharedFunc_800CD920_3_s03(s_SubCharacter* chara, q19_12 offsetX, q19_12 offsetZ)
{
    sharedFunc_800CD7F8_3_s03(chara, offsetX, offsetZ, Q12(1.0f));
}

q19_12 sharedFunc_800CD940_3_s03(q19_12 pos0, q19_12 pos1)
{
    q19_12 delta;
    q19_12 absDelta;
    q19_12 result;

    delta    = pos0 - pos1;
    absDelta = ABS(delta);
    if (absDelta > Q12(1.0f / 32.0f))
    {
        if (delta <= 0)
        {
            pos0 = pos1 - Q12(1.0f / 32.0f);
        }
        else
        {
            pos0 = pos1 + Q12(1.0f / 32.0f);
        }
    }

    if (pos0 <= Q12(0.35f))
    {
        result = pos0;
    }
    else
    {
        result = Q12(0.35f);
    }

    return result;
}

s32 PuppetNurse_HurtSfxIdGet(s_SubCharacter* nurse)
{
    s32 weaponAttack;
    s32 idx;

    weaponAttack = nurse->attackReceived;
    if (weaponAttack != WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Tap) &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Hold) &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_Chainsaw, AttackInputType_Multitap) &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap) &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Hold) &&
        weaponAttack != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Multitap))
    {
        idx = D_800AD4C8[weaponAttack].field_10;
        return g_PuppetNurseHurtSfxIdxs[idx];
    }

    return NO_VALUE;
}

void Ai_PuppetNurse_SfxPlay(s_SubCharacter* nurse, s32 idx)
{
    s32        idx0;
    s_SfxPair* sfxPair;

    sfxPair = g_NursePuppetSfxs;
    idx0    = (nurseProps.field_124->idx_1C * 9) + idx;
    func_8005DC1C(sfxPair[idx0].sfxId, &nurse->position, sfxPair[idx0].vol, 0);
}

s32 Ai_PuppetNurse_AnimSfxGet(s32 animFrame)
{
    u8 idx;
    u8 sfxOffsets[4] = { 9, 6, 7, 8 };

    idx = g_NursePuppet_AnimSfxs[animFrame];
    return sfxOffsets[idx];
}

void sharedFunc_800CDA88_3_s03(s_SubCharacter* nurse)
{
    if (nurse->model.stateStep == 0)
    {
        Ai_PuppetNurse_Control(nurse);
    }
}

void Ai_PuppetNurse_UpdateMain(s_SubCharacter* nurse, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    if (g_DeltaTime != Q12(0.0f))
    {
        Ai_PuppetNurse_DamageHandle(nurse);
        Ai_PuppetNurse_Control(nurse);
        sharedFunc_800CDA88_3_s03(nurse);
        sharedFunc_800D03E4_3_s03(nurse);
        Ai_PuppetNurse_AnimUpdate(nurse, anmHdr, boneCoords);
        sharedFunc_800D0968_3_s03(nurse, boneCoords);
        sharedFunc_800D02E4_3_s03(nurse, boneCoords);
        return;
    }
    else
    {
        Ai_PuppetNurse_AnimUpdate(nurse, anmHdr, boneCoords);
    }
}

void Ai_PuppetNurse_Init(s_SubCharacter* nurse, bool isPuppetDoctor)
{
    extern s_800D5710 sharedData_800D5710_3_s03[4]; // Likely static.

    s32             charaState;
    s32             charStatIdx;
    s32             charPalette;
    s32             modelVariation;
    s32             stateStepDiv3;
    s_SubCharacter* chara2;

    chara2 = nurse; // TODO: Not sure why this is needed, possibly an inline here somewhere?

    nurse->moveSpeed                = Q12(0.0f);
    nurse->field_E1_0                  = 3;
    nurse->headingAngle             = nurse->rotation.vy;
    nurseProps.position_E8             = nurse->position;
    nurse->field_D4.radius_0           = Q12(0.3f);
    nurseProps.damage_F4.position.vx = Q12(0.0f);
    nurseProps.damage_F4.position.vy = Q12(0.0f);
    nurseProps.damage_F4.position.vz = Q12(0.0f);
    nurseProps.field_114               = 0;
    nurseProps.field_118               = 0;

    Chara_DamageClear(nurse);

    nurseProps.flags_122 = PuppetNurseFlag_None;
    nurseProps.field_108 = nurse->position.vx;
    nurseProps.field_10C = nurse->position.vz;

    charPalette    = (nurse->model.stateStep - 1) % 3;
    stateStepDiv3  = (nurse->model.stateStep - 1) / 3;
    modelVariation = stateStepDiv3 % 3;
    charaState     = stateStepDiv3 / 3;

    nurseProps.field_11A = 0;
    nurse->flags     |= CharaFlag_Unk3;

    if (!isPuppetDoctor)
    {
        charStatIdx                   = charPalette + 1; // Skip doctor stat at beginning.
        nurseProps.modelVariation_119 = modelVariation + 1;
    }
    else
    {
        nurseProps.modelVariation_119 = 1;
        charPalette                   = 0;
        charStatIdx                   = 0;
    }

    chara2->properties.puppetNurse.field_124 = &sharedData_800D5710_3_s03[charStatIdx];

    nurse->health            = chara2->properties.puppetNurse.field_124->health_0;
    nurse->model.paletteIdx = charPalette;

    switch (charaState)
    {
        case 0:
            nurse->model.controlState       = PuppetNurseControl_11;
            nurse->model.stateStep          = 0;
            nurse->model.anim.time        = Q12(459.0f);
            nurse->model.anim.keyframeIdx = 459;
            break;

        case 1:
            nurse->model.controlState       = PuppetNurseControl_10;
            nurse->model.stateStep          = 0;
            nurse->model.anim.time        = Q12(459.0f);
            nurse->model.anim.keyframeIdx = 459;
            break;

        case 2:
            nurse->model.controlState       = PuppetNurseControl_9;
            nurse->model.stateStep          = 0;
            nurse->model.anim.time        = Q12(459.0f);
            nurse->model.anim.keyframeIdx = 459;
            break;
    }

    ModelAnim_AnimInfoSet(&nurse->model.anim, chara2->properties.puppetNurse.field_124->animInfo_24);

    nurse->model.anim.status              = ANIM_STATUS(PuppetNurseAnim_17, false);
    nurse->model.anim.alpha               = Q12(0.0f);
    chara2->properties.puppetNurse.field_120 = Q12(1.0f);
}

void Ai_PuppetNurse_Update(s_SubCharacter* nurse, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    // Initialize.
    if (nurse->model.controlState == 0)
    {
        Ai_PuppetNurse_Init(nurse, false);
    }

    Ai_PuppetNurse_UpdateMain(nurse, anmHdr, boneCoords);
}

void Ai_PuppetDoctor_Update(s_SubCharacter* doctor, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords)
{
    // Initialize.
    if (doctor->model.controlState == 0)
    {
        Ai_PuppetNurse_Init(doctor, true);
    }

    Ai_PuppetNurse_UpdateMain(doctor, anmHdr, boneCoords);
}

bool Ai_PuppetNurse_SomeAngleCheck(s_SubCharacter* nurse)
{
    q19_12 sumSqr;
    q19_12 damageAngle;

    sumSqr = Q12_SQUARE_PRECISE(nurse->damage.position.vx) +
             Q12_SQUARE_PRECISE(nurse->damage.position.vy) +
             Q12_SQUARE_PRECISE(nurse->damage.position.vz);

    damageAngle = ratan2(nurse->damage.position.vx, nurse->damage.position.vz);
    damageAngle = ABS(Math_AngleNormalizeSigned(damageAngle - nurse->rotation.vy));
    if (sumSqr > Q12_ANGLE(360.0f) && damageAngle > Q12_ANGLE(10.0f))
    {
        return true;
    }

    return false;
}

void Ai_PuppetNurse_DamageHandle(s_SubCharacter* nurse)
{
    q19_12          newHealth;
    s32             sfxIdx;
    s_SubCharacter* nurseCpy;

    nurseCpy = nurse;

    if (nurse->damage.amount > Q12(0.0f))
    {
        sfxIdx = PuppetNurse_HurtSfxIdGet(nurse);
        if (sfxIdx != NO_VALUE)
        {
            Ai_PuppetNurse_SfxPlay(nurse, sfxIdx);
        }

        switch (nurse->properties.puppetNurse.field_118)
        {
            case 0:
                nurse->properties.puppetNurse.damage_F4  = nurse->damage;
                nurse->properties.puppetNurse.field_114 += nurse->damage.amount;

                newHealth = nurse->health - nurse->damage.amount;
                if (newHealth < Q12(0.0f))
                {
                    newHealth = Q12(0.0f);
                }
                nurse->health = newHealth;

                if (newHealth <= Q12(120.0f))
                {
                    nurse->properties.puppetNurse.field_118++;

                    if (!Ai_PuppetNurse_SomeAngleCheck(nurse))
                    {
                        nurse->model.controlState = PuppetNurseControl_4;
                        nurse->model.stateStep    = 0;
                    }
                    else
                    {
                        nurse->model.controlState = PuppetNurseControl_3;
                        nurse->model.stateStep    = 0;
                    }

                    if (!nurse->health)
                    {
                        Savegame_EnemyStateUpdate(nurse);
                    }
                }
                else
                {
                    if (nurse->model.controlState != PuppetNurseControl_2 &&
                        ((nurse->properties.puppetNurse.field_124->field_4 < nurse->properties.puppetNurse.field_114) ||
                         (nurse->damage.amount > Q12(320.0f))))
                    {
                        nurse->properties.puppetNurse.field_114 = 0;
                        nurse->model.controlState              = PuppetNurseControl_2;
                        nurse->model.stateStep                 = 0;
                    }
                }
                break;

            case 1:
                if (nurse->health)
                {
                    Ai_PuppetNurse_SfxPlay(nurse, 1);
                    nurse->health = Q12(0.0f);
                    Savegame_EnemyStateUpdate(nurse);

                    if (nurse->model.anim.status == ANIM_STATUS(14, true))
                    {
                        nurse->model.anim.status = ANIM_STATUS(22, false);
                    }
                }

                nurseCpy->properties.npc.field_118++;

            case 2:
                break;
        }
    }

    Chara_DamageClear(nurse);
}

void Ai_PuppetNurse_Move(s_SubCharacter* nurse)
{
    q3_12  angleDeltaToPlayer;
    q3_12  tmpAngle;
    q3_12  absAngle;
    q19_12 distToPlayer;
    q19_12 addAngle;
    q19_12 distAbs;
    q19_12 limit;

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork.player.position.vx - nurse->position.vx,
                                       g_SysWork.playerWork.player.position.vz - nurse->position.vz) -
                   Q12(0.76f);
    distAbs = ABS(distToPlayer);

    angleDeltaToPlayer = Math_AngleNormalizeSigned(Math_AngleBetweenPositionsGet(nurse->position, g_SysWork.playerWork.player.position) -
                                       nurse->rotation.vy);
    absAngle           = ABS(angleDeltaToPlayer);

    if (distAbs > Q12(0.03f))
    {
        if (distToPlayer > Q12(0.0f))
        {
            limit = Q12(0.0f);
        }
        else
        {
            limit = Q12(-0.02f);
        }

        Chara_MoveSpeedUpdate2(nurse, Q12(4.0f), limit);
    }
    else
    {
        Chara_MoveSpeedUpdate(nurse, Q12(4.0f));
    }

    if (absAngle > Q12_ANGLE(10.0f))
    {
        tmpAngle = 2;
        tmpAngle = (absAngle * tmpAngle) + Q12_ANGLE(45.0f);
        addAngle = Q12_MULT_PRECISE(g_DeltaTime, tmpAngle);
        if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
        {
            nurse->rotation.vy += addAngle;
        }
        else
        {
            nurse->rotation.vy -= addAngle;
        }
    }
}

bool sharedFunc_800CE398_3_s03(s32 animStatus)
{
    return animStatus == ANIM_STATUS(PuppetNurseAnim_18, false) ||
           animStatus == ANIM_STATUS(PuppetNurseAnim_17, false) ||
           animStatus == ANIM_STATUS(PuppetNurseAnim_18, true) ||
           animStatus == ANIM_STATUS(PuppetNurseAnim_17, true);
}

void Ai_PuppetNurse_Control1(s_SubCharacter* nurse)
{
    s_SubCharacter* localNurse;

    localNurse = nurse;

    if (!nurse->model.stateStep)
    {
        if (!nurse->properties.puppetNurse.field_11E)
        {
            nurse->model.anim.status = 2;
        }
        else
        {
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
            {
                nurse->model.anim.status = ANIM_STATUS(PuppetNurseAnim_1, false);
            }
            else
            {
                nurse->model.anim.status = ANIM_STATUS(PuppetNurseAnim_21, false);
            }
        }

        nurse->properties.puppetNurse.field_11E = func_80070320();
        localNurse->model.stateStep++;
        nurse->properties.puppetNurse.field_104 = Q12(1.0f);
        return;
    }

    if (nurse->properties.puppetNurse.field_104 < Q12(0.0f) && (nurse->properties.puppetNurse.flags_122 & PuppetNurseFlag_0))
    {
        nurse->properties.puppetNurse.field_104 = Q12(100.0f);
        Ai_PuppetNurse_SfxPlay(nurse, 0);
    }

    if (localNurse->model.anim.status == ANIM_STATUS(PuppetNurseAnim_18, false))
    {
        localNurse->model.controlState = PuppetNurseControl_9;
        localNurse->model.stateStep    = 0;
    }

    if (nurse->properties.puppetNurse.field_11E && g_SysWork.playerWork.player.attackReceived == NO_VALUE)
    {
        localNurse->model.controlState = PuppetNurseControl_8;
        localNurse->model.stateStep    = 0;
        return;
    }

    Ai_PuppetNurse_Move(localNurse);
    nurse->properties.puppetNurse.field_104 -= g_DeltaTime;
}

void Ai_PuppetNurse_Control2(s_SubCharacter* nurse)
{
    s32 moveSpeed;

    if (!nurse->model.stateStep)
    {
        Ai_PuppetNurse_SfxPlay(nurse, 2);
        nurse->model.anim.status = ANIM_STATUS(PuppetNurseAnim_2, false);
        nurse->model.stateStep++;
    }
    if (nurse->model.anim.status == ANIM_STATUS(PuppetNurseAnim_18, false))
    {
        nurse->model.controlState = PuppetNurseControl_9;
        nurse->model.stateStep    = 0;
    }

    Chara_MoveSpeedUpdate(nurse, Q12(4.0f));
}

void Ai_PuppetNurse_Control3_4(s_SubCharacter* nurse, bool isDoctor)
{
    s32             animStatus;
    s_SubCharacter* localNurse;

    localNurse = nurse;

    if (!nurse->model.stateStep)
    {
        if (nurse->model.anim.status == ANIM_STATUS(PuppetNurseAnim_2, true))
        {
            return;
        }

        Ai_PuppetNurse_SfxPlay(nurse, 2);

        nurse->model.anim.status = g_PuppetNurse_AnimStatus0[isDoctor];
        nurse->field_E1_0              = 4;
        nurse->flags               |= CharaFlag_Unk2;
        nurse->model.stateStep++;
    }

    animStatus = nurse->model.anim.status;
    if (animStatus == ANIM_STATUS(PuppetNurseAnim_14, true) || animStatus == ANIM_STATUS(PuppetNurseAnim_5, true) ||
        animStatus == ANIM_STATUS(PuppetNurseAnim_5, false) || animStatus == ANIM_STATUS(PuppetNurseAnim_15, true))
    {
        if (Chara_NpcIdxGet(nurse) != g_SysWork.targetNpcIdx && nurse->health == Q12(0.0f))
        {
            nurse->health  = NO_VALUE;
            nurse->field_E1_0 = 0;
            func_800622B8(3, nurse, g_PuppetNurse_AnimStatus1[isDoctor], 11);

            localNurse->properties.puppetNurse.flags_122 |= PuppetNurseFlag_1;
        }
        else if (nurse->model.anim.status == ANIM_STATUS(PuppetNurseAnim_15, true) && nurse->health > Q12(0.0f))
        {
            nurse->model.anim.status = ANIM_STATUS(PuppetNurseAnim_5, false);
        }
    }

    Chara_MoveSpeedUpdate(nurse, Q12(4.0f));
}

bool sharedFunc_800CE7C8_3_s03(s_SubCharacter* nurse)
{
    q19_12 deltaX;
    q19_12 deltaZ;
    q19_12 dist;
    q19_12 distAbs;
    q19_12 distSubtract;
    q19_12 moveSpeed;
    q3_12  angle;
    q3_12  angle2;
    q3_12  tmpAngle;
    q3_12  addAngle;
    q3_12  absAngle;
    q19_12 limit;

    distSubtract = Q12(0.78f);
    angle        = Math_AngleNormalizeSigned(ratan2(g_SysWork.playerWork.player.position.vx - nurse->position.vx,
                                        g_SysWork.playerWork.player.position.vz - nurse->position.vz) -
                                 nurse->rotation.vy);
    absAngle     = ABS(angle);

    angle2 = Math_AngleNormalizeSigned(g_SysWork.playerWork.player.rotation.vy - nurse->rotation.vy);
    angle2 = ABS(angle2);

    if (angle2 > Q12_ANGLE(90.0f))
    {
        distSubtract = Q12(0.85f);
    }

    deltaX  = Q12_TO_Q6(g_SysWork.playerWork.player.position.vx - nurse->position.vx);
    deltaZ  = Q12_TO_Q6(g_SysWork.playerWork.player.position.vz - nurse->position.vz);
    dist    = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ))) - distSubtract;
    distAbs = ABS(dist);

    if (dist > Q12(0.5f))
    {
        return false;
    }

    if (distAbs > Q12(0.2f))
    {
        limit = Q12(0.2f);
    }
    else
    {
        if (distAbs > Q12(0.05f))
        {
            if (dist > Q12(0.0f))
            {
                limit = Q12(0.6f);
            }
            else
            {
                limit = Q12(-0.6f);
            }
        }
        else
        {
            limit = Q12(0.0f);
        }
    }

    Chara_MoveSpeedUpdate2(nurse, Q12(2.0f), limit);

    if (absAngle > Q12_ANGLE(4.0f))
    {
        tmpAngle = 2;
        tmpAngle = (absAngle * tmpAngle) + Q12_ANGLE(45.0f);
        addAngle = Q12_MULT_PRECISE(g_DeltaTime, tmpAngle);
        if (angle > Q12_ANGLE(0.0f))
        {
            nurse->rotation.vy += addAngle;
        }
        else
        {
            nurse->rotation.vy -= addAngle;
        }
    }

    return true;
}

void Ai_PuppetNurse_Control5(s_SubCharacter* nurse)
{
    s32 controlState;

    if (!nurse->model.stateStep)
    {
        nurse->model.anim.status        = ANIM_STATUS(PuppetNurseAnim_6, false);
        nurse->properties.player.field_104 = 0;
        nurse->model.stateStep++;
    }

    sharedFunc_800CE7C8_3_s03(nurse);

    controlState = nurse->model.stateStep;
    if (controlState == PuppetNurseControl_1)
    {
        if (nurse->properties.puppetNurse.flags_122 & PuppetNurseFlag_0)
        {
            nurse->model.stateStep = 2;
        }
        else
        {
            if (nurse->properties.player.field_104 <= Q12(1.5f))
            {
                if (func_80070320())
                {
                    nurse->model.controlState  = controlState;
                    nurse->model.stateStep     = 0;
                    nurse->model.anim.status = ANIM_STATUS(PuppetNurseAnim_18, false);
                    return;
                }
            }
            else
            {
                nurse->model.controlState = PuppetNurseControl_13;
                nurse->model.stateStep    = 0;
                return;
            }
        }
    }
    else if (controlState == 2)
    {
        if (Chara_AttackReceivedGet(&g_SysWork.playerWork.player) == NO_VALUE)
        {
            nurse->model.controlState = PuppetNurseControl_8;
            nurse->model.stateStep    = 0;
            return;
        }

        if (nurse->properties.puppetNurse.field_104 >= Q12(1.5f))
        {
            g_SysWork.playerWork.player.damage.amount += Q12(D_800AD4C8[EquippedWeaponId_Unk56].field_4);
            nurse->properties.puppetNurse.field_104           = 0;
        }
    }

    nurse->properties.puppetNurse.field_104 += g_DeltaTime;
}

void Ai_PuppetNurse_Control6_7(s_SubCharacter* nurse, bool isDoctor)
{
    if (!nurse->model.stateStep)
    {
        Ai_PuppetNurse_SfxPlay(nurse, isDoctor + 1);

        if (isDoctor)
        {
            nurse->model.anim.status = ANIM_STATUS(PuppetNurseAnim_8, false);
        }
        else
        {
            nurse->model.anim.status = ANIM_STATUS(PuppetNurseAnim_7, false);
        }

        nurse->model.stateStep++;
    }

    if (nurse->model.anim.status == ANIM_STATUS(PuppetNurseAnim_18, false))
    {
        nurse->model.controlState = PuppetNurseControl_9;
        nurse->model.stateStep    = 0;
    }

    Chara_MoveSpeedUpdate(nurse, Q12(4.0f));
}

void Ai_PuppetNurse_Control8(s_SubCharacter* nurse)
{
    s32    controlState;
    q19_12 speed;
#if !defined(M2CTX)
    register q19_12 angle asm("v1"); // @hack forced register for a match. Doesn't affect code logic.
#else
    q19_12 angle;
#endif

    switch (nurse->model.stateStep)
    {
        case 0:
            angle = Math_AngleNormalizeSigned((g_SysWork.playerWork.player.rotation.vy - nurse->rotation.vy) - Q12_ANGLE(90.0f));
            if (angle < Q12_ANGLE(0.0f))
            {
                nurse->properties.puppetNurse.field_104 = -angle;
            }
            else
            {
                nurse->properties.puppetNurse.field_104 = angle;
            }

            nurse->model.stateStep++;
            break;

        case 1:
            if (nurse->properties.puppetNurse.field_104 < 0)
            {
                nurse->moveSpeed            = Q12(-1.0f);
                nurse->model.anim.status = ANIM_STATUS(10, false);
                nurse->model.stateStep     = 2;
            }

            nurse->properties.puppetNurse.field_104 -= g_DeltaTime;
            break;

        case 2:
        {
            u16 modelStates[8] = { 9, 9, 9, 6, 6, 9, 7, 7 };

            if (nurse->model.anim.status == ANIM_STATUS(18, false))
            {
                if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                {
                    controlState = PuppetNurseControl_9;
                }
                else
                {
                    controlState = modelStates[(Rng_Rand16() >> 4) & 7];
                }

                nurse->model.controlState = controlState;
                nurse->model.stateStep    = 0;
            }
            else
            {
                speed = Rng_GenerateUInt(0, 0x1FF); // TODO: Combine with the +0.8f below?
                Chara_MoveSpeedUpdate(nurse, (speed + Q12(0.8f)));
            }
        }
        break;
    }
}

s32 sharedFunc_800CEEAC_3_s03(void)
{
    s32 temp_a0;

    temp_a0 = g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x3;
    if (temp_a0 == 0)
    {
        return 0;
    }
    else if (temp_a0 == 2)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

void sharedFunc_800CEEE0_3_s03(s_SubCharacter* nurse)
{
    s32             limit;
    s16             angle;
    s_SubCharacter* nurseCpy;

    limit    = Q12_MULT_PRECISE(nurse->properties.npc.field_124->field_C, Q12(0.27f));
    nurseCpy = nurse;
    Chara_MoveSpeedUpdate2(nurse, Q12(1.4f), limit);
    limit = 0;

    if (Rng_GenerateUInt(0, 63) == 0) // 1 in 64 chance.
    {
        nurseCpy->properties.puppetNurse.field_11C = func_8006F99C(nurse, Q12_ANGLE(360.0f), nurse->rotation.vy);
    }
    angle = Math_AngleNormalizeSigned(nurseCpy->properties.puppetNurse.field_11C - nurse->rotation.vy);
    if (ABS(angle) > Q12_ANGLE(5.0f))
    {
        if (angle > Q12_ANGLE(0.0f))
        {
            nurse->rotation.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
        }
        else
        {
            nurse->rotation.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
        }
    }
}

void sharedFunc_800CF0B4_3_s03(s_SubCharacter* nurse)
{
    q19_12          limit;
    q3_12           angle;
    s_SubCharacter* localNurse;

    limit      = Q12_MULT_PRECISE(nurse->properties.npc.field_124->field_C, Q12(0.27f));
    localNurse = nurse;

    Chara_MoveSpeedUpdate2(nurse, Q12(1.4f), limit);
    limit = Q12(0.0f);

    // @note Did they forget to make it an if?
    Rng_Rand16();
    localNurse->properties.puppetNurse.field_11C = Chara_HeadingAngleGet(nurse,
                                                                            Q12(1.0f),
                                                                            g_SysWork.playerWork.player.position.vx,
                                                                            g_SysWork.playerWork.player.position.vz,
                                                                            Q12_ANGLE(360.0f),
                                                                            true);

    angle = Math_AngleNormalizeSigned(localNurse->properties.puppetNurse.field_11C - nurse->rotation.vy);
    if (ABS(angle) > Q12_ANGLE(5.0f))
    {
        if (angle > Q12_ANGLE(0.0f))
        {
            nurse->rotation.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
        }
        else
        {
            nurse->rotation.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
        }
    }
}

bool sharedFunc_800CF294_3_s03(s_SubCharacter* arg0, q19_12 dist)
{
    s32           temp_a0;
    s32           temp_v1;
    s32           ret;
    s_D_800D5A8C* somePtr;

    somePtr = &sharedData_800D5A8C_3_s03[sharedFunc_800CEEAC_3_s03()];

    if (arg0->properties.npc.field_11A > 0)
    {
        arg0->properties.npc.field_11A -= g_DeltaTime;
    }

    if (func_80070360(arg0, dist, somePtr->field_8))
    {
        arg0->properties.npc.field_11A = Q12_ANGLE(360.0f);
    }

    temp_v1 = somePtr->field_0;
    temp_a0 = arg0->properties.npc.field_124->field_8;

    ret = false;
    if (func_8006FD90(arg0, 1, Q12_MULT_PRECISE(temp_v1, temp_a0), Q12_MULT_PRECISE(somePtr->field_4, temp_a0)) ||
        arg0->properties.npc.field_11A > 0)
    {
        ret = true;
    }

    return ret;
}

void Ai_PuppetNurse_Control9(s_SubCharacter* nurse)
{
    bool            cond;
    q19_12          dist;
    q19_12          deltaX;
    q19_12          deltaZ;
    u16             rng;
    q3_12           angle;
    q3_12           angleAbs;
    s_800D5710*     somePtr;
    s_SubCharacter* localNurse;

    localNurse = nurse;

    deltaX = Q12_TO_Q6(g_SysWork.playerWork.player.position.vx - nurse->position.vx);
    deltaZ = Q12_TO_Q6(g_SysWork.playerWork.player.position.vz - nurse->position.vz);
    dist   = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    angle    = Math_AngleNormalizeSigned(Math_AngleBetweenPositionsGet(nurse->position, g_SysWork.playerWork.player.position) -
                             nurse->rotation.vy);
    angleAbs = ABS(angle);

    if (!nurse->model.stateStep)
    {
        nurse->properties.player.field_104      = 0;
        nurse->properties.puppetNurse.field_11C = func_8006F99C(nurse, Q12_ANGLE(360.0f), nurse->rotation.vy);
        nurse->model.stateStep++;
    }

    cond                    = sharedFunc_800CF294_3_s03(nurse, dist);
    nurse->field_44.field_0 = 0;

    switch (nurse->model.stateStep)
    {
        case 1:
            if (!cond)
            {
                sharedFunc_800CEEE0_3_s03(nurse);
                break;
            }
            else
            {
                nurse->model.stateStep = 2;
            }

        case 2:
            if (!cond)
            {
                nurse->model.stateStep = 1;
            }
            else
            {
                sharedFunc_800CF0B4_3_s03(nurse);

                somePtr = localNurse->properties.npc.field_124;
                if (dist < Q12_MULT_PRECISE(somePtr->field_8, Q12(3.0f)) &&
                    angleAbs < Q12_ANGLE(60.0f) && g_SysWork.playerWork.player.health > Q12(0.0f))
                {
                    nurse->model.controlState = PuppetNurseControl_12;
                    nurse->model.stateStep    = 0;
                }
            }
            break;
    }

    if (nurse->model.stateStep && sharedFunc_800CE398_3_s03(nurse->model.anim.status))
    {
        if (!Rng_GenerateUInt(0, 31)) // 1 in 32 chance.
        {
            rng                            = Rng_Rand16();
            nurse->model.anim.status = g_PuppetNurse_AnimStatus2[(rng >> 7) & 0x1];
            nurse->model.controlState  = PuppetNurseControl_6;
            nurse->model.stateStep     = 0;
            return;
        }
        else
        {
            nurse->model.anim.status = g_PuppetNurse_AnimStatus3[(Rng_Rand16() >> 2) & 0x3];
        }
    }
}

s32 sharedFunc_800CF600_3_s03(s_SubCharacter* nurse)
{
    s32 temp_a3;
    s32 var_a1;
    s32 var_v0;
    s32 var_v1;

    temp_a3 = Math_Vector2MagCalc(g_SysWork.playerWork.player.position.vx - nurse->position.vx,
                                  g_SysWork.playerWork.player.position.vz - nurse->position.vz) -
              0xC28;

    var_v0 = ABS(temp_a3);

    if (var_v0 > 0x7A && nurse->model.anim.status != 0x28)
    {
        if (temp_a3 > 0)
        {
            var_a1 = 0x8000;
            var_v1 = Q12_MULT_PRECISE(nurse->properties.puppetNurse.field_124->field_18, 0x1CCC);
        }
        else
        {
            var_v1 = -0x51;
            var_a1 = 0x2000;
        }
        Chara_MoveSpeedUpdate2(nurse, var_a1, var_v1);
    }
    else
    {
        Chara_MoveSpeedUpdate(nurse, 0x3000);
    }

    return temp_a3;
}

void sharedFunc_800CF7F4_3_s03(s_SubCharacter* nurse)
{
    int angle; // TODO: Type

    if ((Rng_Rand16() & Q8_CLAMPED(1.0f)) >= Q8(0.5f))
    {
        nurse->properties.dummy.properties_E8[13].val16[0] = Chara_HeadingAngleGet(nurse,
                                                                                      Q12(1.0f),
                                                                                      g_SysWork.playerWork.player.position.vx,
                                                                                      g_SysWork.playerWork.player.position.vz,
                                                                                      Q12_ANGLE(360.0f),
                                                                                      true);
    }

    angle = Math_AngleNormalizeSigned(nurse->properties.dummy.properties_E8[13].val16[0] - nurse->rotation.vy);
    if (ABS(angle) > Q12_ANGLE(5.0f))
    {
        if (angle > Q12_ANGLE(0.0f))
        {
            nurse->rotation.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
        }
        else
        {
            nurse->rotation.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
        }
    }
}

bool sharedFunc_800CF90C_3_s03(s_SubCharacter* nurse)
{
    s_SubCharacter* curNpc;
    s32             i;

    // Run through NPCs.
    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs); i++)
    {
        if ((g_SysWork.npcs[i].model.charaId == Chara_PuppetNurse || g_SysWork.npcs[i].model.charaId == Chara_PuppetDoctor) &&
            g_SysWork.npcs[i].health > Q12(0.0f) &&
            g_SysWork.npcs[i].field_40 != nurse->field_40 &&
            !Math_Distance2dCheck(&nurse->position, &g_SysWork.npcs[i].position, Q12(4.0f)))
        {
            curNpc = g_SysWork.npcs;

            if (!(curNpc[i].flags & CharaFlag_Unk2))
            {
                return true;
            }
        }
    }

    return false;
}

void Ai_PuppetNurse_Control12(s_SubCharacter* nurse)
{
    s32             angleDeltaToPlayer;
    s16             angleDeltaAbs;
    s32             distToPlayer;
    s32             cond;
    s32             animStatus;
    s_SubCharacter* nurseCpy;

    animStatus         = nurse->model.anim.status;
    angleDeltaToPlayer = Math_AngleNormalizeSigned(Math_AngleBetweenPositionsGet(nurse->position, g_SysWork.playerWork.player.position) - nurse->rotation.vy);
    angleDeltaAbs      = abs(angleDeltaToPlayer);

    distToPlayer = Math_Vector2MagCalc((g_SysWork.playerWork.player.position.vx - nurse->position.vx),
                                       (g_SysWork.playerWork.player.position.vz - nurse->position.vz));

    distToPlayer = Q12_MULT_FLOAT_PRECISE(distToPlayer, 1.1f);
    cond         = sharedFunc_800CF294_3_s03(nurse, distToPlayer);

    if (g_SysWork.playerWork.player.health < Q12(0.0f) || !cond)
    {
        nurse->model.controlState  = 9;
        nurse->model.stateStep     = 0;
        nurse->model.anim.status = ANIM_STATUS(18, false);
        return;
    }

    switch (nurse->model.stateStep)
    {
        case 0:
            if (angleDeltaAbs >= Q12_ANGLE(10.1f))
            {
                s32 rotAmount = Q12_ANGLE(45.0f); // @hack? Should probably be part of the `FP_MULTIPLY_PRECISE`.
                rotAmount     = Q12_MULT_PRECISE(g_DeltaTime, rotAmount);
                if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
                {
                    nurse->rotation.vy += rotAmount;
                }
                else
                {
                    nurse->rotation.vy -= rotAmount;
                }

                Chara_MoveSpeedUpdate3(nurse, Q12(1.0f), Q12(0.0f));
                return;
            }

            nurse->model.stateStep = 1;

        case 1:
            if (animStatus >= ANIM_STATUS(17, false) && animStatus < ANIM_STATUS(18, false))
            {
                nurse->model.anim.status = ANIM_STATUS(9, false);
                nurse->model.stateStep++;
            }
            else if (animStatus >= ANIM_STATUS(18, false) && animStatus < ANIM_STATUS(19, false))
            {
                nurse->model.anim.status = ANIM_STATUS(20, false);
                nurse->model.stateStep++;
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
                    nurse->model.controlState = 5;
                    nurse->model.stateStep    = 0;
                }
            }
            else if (distToPlayer < 0x266)
            {
                if (!(g_SysWork.playerWork.player.flags & 8))
                {
                    nurseCpy->properties.dummy.properties_E8[0xD].val16[1] = 0; // nurseCpy + 0x11E
                    nurse->model.controlState                             = 1;
                }
                else
                {
                    nurseCpy->properties.dummy.properties_E8[0xD].val16[1] = 1; // nurseCpy + 0x11E
                    nurse->model.controlState                             = 1;
                }

                nurse->model.stateStep     = 0;
                nurse->model.anim.status = ANIM_STATUS(18, false);
            }

            sharedFunc_800CF7F4_3_s03(nurse);
    }
}

void Ai_PuppetNurse_Control10(s_SubCharacter* nurse)
{
    u8     animStatus;
    q19_12 deltaX;
    q19_12 deltaZ;
    q19_12 dist;

    if (!nurse->model.stateStep)
    {
        nurse->properties.player.field_104 = 0;
        nurse->model.anim.status        = ANIM_STATUS(19, false);
        nurse->model.stateStep++;
    }

    deltaX = Q12_TO_Q6(g_SysWork.playerWork.player.position.vx - nurse->position.vx);
    deltaZ = Q12_TO_Q6(g_SysWork.playerWork.player.position.vz - nurse->position.vz);
    dist   = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    if (sharedFunc_800CF294_3_s03(nurse, dist))
    {
        nurse->model.controlState = PuppetNurseControl_9;
        nurse->model.stateStep    = 0;

        if (Rng_Rand16() & 0x80)
        {
            animStatus = ANIM_STATUS(7, false);
        }
        else
        {
            animStatus = ANIM_STATUS(8, false);
        }

        nurse->model.anim.status = animStatus;
    }
}

void Ai_PuppetNurse_Control11(s_SubCharacter* nurse)
{
    u8              controlState;
    q19_12          deltaX;
    q19_12          deltaZ;
    q19_12          dist;
    q3_12           angle;
    q19_12          tmp;
    s32             temp_s0;
    s_SubCharacter* localNurse;

    if (!nurse->model.stateStep)
    {
        nurseProps.field_104           = 0;
        nurse->model.anim.status = ANIM_STATUS(PuppetNurseAnim_17, false);
        nurseProps.field_11C           = func_8006F99C(nurse, Q12(1.0f), nurse->rotation.vy);
        nurse->model.stateStep++;
    }

    if (sharedFunc_800CE398_3_s03(nurse->model.anim.status))
    {
        if (Rng_GenerateUInt(0, 15) == 0) // 1 in 16 chance.
        {
            if (Rng_Rand16() & 0x80)
            {
                controlState = PuppetNurseControl_6;
            }
            else
            {
                controlState = PuppetNurseControl_7;
            }

            nurse->model.controlState = controlState;
            nurse->model.stateStep    = 0;
        }
        else
        {
            nurse->model.anim.status = g_PuppetNurse_AnimStatus4[(Rng_Rand16() >> 2) & 3];
        }
    }

    deltaX = Q12_TO_Q6(g_SysWork.playerWork.player.position.vx - nurse->position.vx);
    deltaZ = Q12_TO_Q6(g_SysWork.playerWork.player.position.vz - nurse->position.vz);
    dist   = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    if (sharedFunc_800CF294_3_s03(nurse, dist))
    {
        nurse->model.controlState = PuppetNurseControl_9;
        nurse->model.stateStep    = 0;
        return;
    }

    localNurse = nurse;
#define localNurseProps localNurse->properties.puppetNurse

    Chara_MoveSpeedUpdate3(nurse, Q12(1.4f), Q12(0.27f));

    if (Rng_GenerateUInt(0, 63) == 0) // 1 in 64 chance.
    {
        tmp                       = Q12(1.5f);
        temp_s0                   = localNurseProps.field_108 + ((Rng_Rand16() % Q12(3.0f)) - tmp);
        localNurseProps.field_11C = Chara_HeadingAngleGet(nurse,
                                                          Q12(1.0f),
                                                          temp_s0,
                                                          localNurseProps.field_10C + ((Rng_Rand16() % Q12(3.0f)) - tmp),
                                                          Q12_ANGLE(360.0f),
                                                          true);
    }

    angle = Math_AngleNormalizeSigned(localNurseProps.field_11C - nurse->rotation.vy);
    if (ABS(angle) > Q12_ANGLE(5.0f))
    {
        if (angle > Q12_ANGLE(0.0f))
        {
            nurse->rotation.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
        }
        else
        {
            nurse->rotation.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
        }
    }

#undef localNurseProps
}

void Ai_PuppetNurse_Control13(s_SubCharacter* nurse)
{
    if (nurse->model.stateStep == 0)
    {
        nurse->model.anim.status = ANIM_STATUS(PuppetNurseAnim_10, false);
        nurse->model.stateStep++;
    }

    if (nurse->model.anim.status == ANIM_STATUS(PuppetNurseAnim_18, false))
    {
        nurse->model.controlState = PuppetNurseControl_9;
        nurse->model.stateStep    = 0;
    }

    Chara_MoveSpeedUpdate3(nurse, Q12(4.0f), Q12(0.0f));
}

void Ai_PuppetNurse_Control(s_SubCharacter* nurse)
{
    // Handle control state.
    switch (nurse->model.controlState)
    {
        case PuppetNurseControl_1:
            Ai_PuppetNurse_Control1(nurse);
            break;

        case PuppetNurseControl_2:
            Ai_PuppetNurse_Control2(nurse);
            break;

        case PuppetNurseControl_3:
            Ai_PuppetNurse_Control3_4(nurse, true);
            break;

        case PuppetNurseControl_4:
            Ai_PuppetNurse_Control3_4(nurse, false);
            break;

        case PuppetNurseControl_5:
            Ai_PuppetNurse_Control5(nurse);
            break;

        case PuppetNurseControl_6:
            Ai_PuppetNurse_Control6_7(nurse, false);
            break;

        case PuppetNurseControl_7:
            Ai_PuppetNurse_Control6_7(nurse, true);
            break;

        case PuppetNurseControl_8:
            Ai_PuppetNurse_Control8(nurse);
            break;

        case PuppetNurseControl_9:
            Ai_PuppetNurse_Control9(nurse);
            break;

        case PuppetNurseControl_10:
            Ai_PuppetNurse_Control10(nurse);
            break;

        case PuppetNurseControl_11:
            Ai_PuppetNurse_Control11(nurse);
            break;

        case PuppetNurseControl_12:
            Ai_PuppetNurse_Control12(nurse);
            break;

        case PuppetNurseControl_13:
            Ai_PuppetNurse_Control13(nurse);
            break;
    }
}

void sharedFunc_800D02E4_3_s03(s_SubCharacter* nurse, GsCOORDINATE2* boneCoords)
{
    VECTOR3         pos;
    MATRIX          mat; // "Hierarchy matrix"?
    s32             weaponAttack;
    q19_12          posX;
    q19_12          posY;
    q19_12          posZ;
    s_SubCharacter* localNurse;

    localNurse                                  = nurse;
    nurse->properties.puppetNurse.flags_122 &= ~PuppetNurseFlag_0;

    if (localNurse->model.controlState == PuppetNurseControl_1 ||
        localNurse->model.controlState == PuppetNurseControl_5)
    {
        Vw_CoordHierarchyMatrixCompute(&boneCoords[10], &mat);
        posX = Q8_TO_Q12(mat.t[0]);
        posY = Q8_TO_Q12(mat.t[1]);
        posZ = Q8_TO_Q12(mat.t[2]);

        nurse->field_C8.field_8 = nurse->position.vy - posY;
        pos.vx                  = posX;
        pos.vy                  = posY;
        pos.vz                  = posZ;

        if (localNurse->model.controlState == PuppetNurseControl_1)
        {
            weaponAttack = localNurse->properties.npc.field_124->field_20;
        }
        else
        {
            // TODO: What's weapon attack 56?
            weaponAttack = EquippedWeaponId_Unk56;
        }

        if (func_8008A0E4(1, weaponAttack, nurse, &pos, &g_SysWork.playerWork.player, nurse->rotation.vy, Q12_ANGLE(90.0f)) != NO_VALUE)
        {
            localNurse->properties.puppetNurse.flags_122 |= PuppetNurseFlag_0;
        }
    }
}

void sharedFunc_800D03E4_3_s03(s_SubCharacter* nurse)
{
    s_CollisionResult sp10;
    VECTOR            damagePos; // Q19.12
    VECTOR            dir;       // Q19.12
    VECTOR            unkPos;
    q19_12            moveSpeed;
    q19_12            damagePosComp;
    q19_12            temp_s1;
    q19_12            unkPosX;
    q19_12            unkPosY;
    q19_12            unkPosZ;

    temp_s1 = nurse->properties.puppetNurse.field_124->field_2C;

    damagePos.vx = nurse->properties.puppetNurse.damage_F4.position.vx;
    damagePos.vz = nurse->properties.puppetNurse.damage_F4.position.vz;
    damagePos.vy = nurse->properties.puppetNurse.damage_F4.position.vy;

    moveSpeed                                      = nurse->moveSpeed;
    nurse->properties.puppetNurse.moveSpeed_110 = moveSpeed;

    dir.vx = Math_Sin(nurse->rotation.vy);
    dir.vz = Math_Cos(nurse->rotation.vy);
    dir.vy = Q12(0.0f);

    unkPosX = Q12_MULT_PRECISE(temp_s1, damagePos.vx) + Q12_MULT_PRECISE(moveSpeed, dir.vx);
    unkPosY = Q12_MULT_PRECISE(temp_s1, damagePos.vy);
    unkPosZ = Q12_MULT_PRECISE(temp_s1, damagePos.vz) + Q12_MULT_PRECISE(moveSpeed, dir.vz);

    unkPos.vx = unkPosX;
    unkPos.vy = unkPosY;
    unkPos.vz = unkPosZ;

    nurse->moveSpeed    = SquareRoot12(Q12_MULT_PRECISE(unkPosX, unkPosX) + Q12_MULT_PRECISE(unkPosZ, unkPosZ));
    nurse->headingAngle = ratan2(unkPosX, unkPosZ);
    nurse->fallSpeed   += g_GravitySpeed;

    func_8005C944(nurse, &sp10);

    damagePosComp                                            = nurse->properties.puppetNurse.damage_F4.position.vx;
    nurse->moveSpeed                                      = nurse->properties.puppetNurse.moveSpeed_110;
    nurse->properties.puppetNurse.damage_F4.position.vx = SquareRoot12(Q12_MULT_PRECISE(damagePosComp, damagePosComp) >> g_VBlanks);

    if (damagePosComp <= Q12(0.0f))
    {
        nurse->properties.puppetNurse.damage_F4.position.vx = -nurse->properties.puppetNurse.damage_F4.position.vx;
    }

    damagePosComp                                            = nurse->properties.puppetNurse.damage_F4.position.vy;
    nurse->properties.puppetNurse.damage_F4.position.vy = SquareRoot12(Q12_MULT_PRECISE(damagePosComp, damagePosComp) >> g_VBlanks);

    if (damagePosComp <= Q12(0.0f))
    {
        nurse->properties.puppetNurse.damage_F4.position.vy = -nurse->properties.puppetNurse.damage_F4.position.vy;
    }

    damagePosComp = nurse->properties.puppetNurse.damage_F4.position.vz;

    nurse->properties.puppetNurse.damage_F4.position.vz = SquareRoot12(Q12_MULT_PRECISE(damagePosComp, damagePosComp) >> g_VBlanks);
    if (damagePosComp <= Q12(0.0f))
    {
        nurse->properties.puppetNurse.damage_F4.position.vz = -nurse->properties.puppetNurse.damage_F4.position.vz;
    }

    nurse->rotation.vy = Math_AngleNormalizeSigned(nurse->rotation.vy);
}

void Ai_PuppetNurse_AnimUpdate(s_SubCharacter* nurse, s_AnmHeader* anmHdr, GsCOORDINATE2* coord)
{
    s32         sfxIdx0;
    s32         sfxIdx1;
    q19_12      angle;
    s32         i;
    s32         j;
    s_AnimInfo* animInfo;
    s_AnimInfo* animInfoBase;

    animInfoBase = nurseProps.field_124->animInfo_24;
    sfxIdx0      = Ai_PuppetNurse_AnimSfxGet(FP_FROM(nurse->model.anim.time, Q12_SHIFT));

    WorldGfx_HeldItemAttach(nurse->model.charaId, nurseProps.modelVariation_119);
    Math_MatrixTransform(&nurse->position, &nurse->rotation, coord);

    if (nurse->model.anim.status != ANIM_STATUS(0, false))
    {
        (&animInfoBase[nurse->model.anim.status])->playbackFunc(&nurse->model, anmHdr, coord, &animInfoBase[nurse->model.anim.status]);
    }

    angle = nurse->properties.npc.field_124->field_18;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            coord->coord.m[i][j] = Q12_MULT_PRECISE(angle, coord->coord.m[i][j]);
        }
    }

    sfxIdx1 = Ai_PuppetNurse_AnimSfxGet(FP_FROM(nurse->model.anim.time, Q12_SHIFT));
    if (sfxIdx1 != sfxIdx0 && sfxIdx1 != 9)
    {
        Ai_PuppetNurse_SfxPlay(nurse, sfxIdx1);
    }
}

void sharedFunc_800D0828_3_s03(s_SubCharacter* nurse, GsCOORDINATE2* boneCoords)
{
    typedef enum _BoneMatIdx
    {
        BoneMatIdx_Torso     = 0,
        BoneMatIdx_Head      = 1,
        BoneMatIdx_RightShin = 2,
        BoneMatIdx_LeftShin  = 3,

        BoneMatIdx_Count = 4
    } e_BoneMatIdx;

    MATRIX          boneMats[BoneMatIdx_Count];
    VECTOR3         unkPos;
    q19_12          deltaX;
    q19_12          deltaY;
    q19_12          unkQ12;
    q19_12          posY;
    q19_12          offsetPosY;
    q19_12          torsoPosY;
    q19_12          headPosY;
    q19_12          rightShinPosY;
    q19_12          leftShinPosY;
    q19_12          tempPosComp;
    s_SubCharacter* localNurse;

    localNurse = nurse;

    // Get torso, head, right shin, and left shin bone matrices.
    Vw_CoordHierarchyMatrixCompute(&boneCoords[HarryBone_Torso], &boneMats[BoneMatIdx_Torso]);
    Vw_CoordHierarchyMatrixCompute(&boneCoords[HarryBone_Head], &boneMats[BoneMatIdx_Head]);
    Vw_CoordHierarchyMatrixCompute(&boneCoords[HarryBone_RightShin], &boneMats[BoneMatIdx_RightShin]);
    Vw_CoordHierarchyMatrixCompute(&boneCoords[HarryBone_LeftShin], &boneMats[BoneMatIdx_LeftShin]);

    posY                     = localNurse->position.vy;
    rightShinPosY            = Q8_TO_Q12(boneMats[BoneMatIdx_RightShin].t[1]);
    leftShinPosY             = Q8_TO_Q12(boneMats[BoneMatIdx_LeftShin].t[1]);
    nurse->field_C8.field_0  = Q8_TO_Q12(boneMats[BoneMatIdx_Head].t[1]);
    offsetPosY               = posY + Q12(0.25f);
    nurse->field_C8.field_0 -= offsetPosY;
    nurse->field_C8.field_2  = posY;

    if (rightShinPosY >= leftShinPosY)
    {
        nurse->field_C8.field_4 = leftShinPosY - nurse->field_C8.field_2;
    }
    else
    {
        nurse->field_C8.field_4 = rightShinPosY - nurse->field_C8.field_2;
    }

    // `((torsoPosY - headPosY) / 2) - posY`
    nurse->field_C8.field_6 = ((Q8_TO_Q12(boneMats[BoneMatIdx_Head].t[1]) + Q8_TO_Q12(boneMats[BoneMatIdx_Torso].t[1])) / 2) - posY;

    unkQ12 = sharedFunc_800CD6B0_3_s03(boneMats, ARRAY_SIZE(boneMats), &unkPos);
    deltaX = unkPos.vx - nurse->position.vx;
    deltaY = unkPos.vz - nurse->position.vz;

    unkQ12                    = sharedFunc_800CD940_3_s03(unkQ12 + Q12(0.05f), nurse->field_D4.radius_0);
    nurse->field_D4.field_2   = unkQ12 - Q12(0.05f);
    nurse->field_D4.radius_0  = unkQ12;
    nurse->field_D8.offsetX_0 = deltaX;
    nurse->field_D8.offsetZ_2 = deltaY;

    sharedFunc_800CD920_3_s03(nurse, deltaX, deltaY);

    tempPosComp                                  = nurse->position.vx;
    localNurse->properties.npc.position_E8.vx = tempPosComp;
    tempPosComp                                  = nurse->position.vz;
    localNurse->properties.npc.position_E8.vz = tempPosComp;
}

void sharedFunc_800D0968_3_s03(s_SubCharacter* nurse, GsCOORDINATE2* boneCoords)
{
    q19_12 posY;

    if (nurse->model.anim.flags & AnimFlag_Visible)
    {
        sharedFunc_800D0828_3_s03(nurse, boneCoords);
        return;
    }

    posY = nurse->position.vy;

    nurse->field_C8.field_2 = posY;
    nurse->field_C8.field_4 = posY;
    nurse->field_C8.field_0 = posY - Q12(1.7f);
    nurse->field_C8.field_6 = posY - Q12(1.0f);
}
