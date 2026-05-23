#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "maps/characters/incubus.h"
#include "maps/map7/map7_s03.h"

// Unknown23: Incubator transforms into this based on `map7_s03::func_800E9498`?
// Seems to include parts of Incubus code here exactly, maybe some half-way chara before Incubus spawns?

#define unknown23Props      chara->properties.incubus
#define localUnknown23Props localChara->properties.incubus

bool Unknown23_Init(s_SubCharacter* chara, GsCOORDINATE2* boneCoords) // 0x800DFB98
{
    s_SubCharacter* localChara; // TODO: Not sure why this is needed here, might be an inline in this func.

    localChara = chara;

    chara->model.anim.alpha = Q12(0.0f);

    if (g_SavegamePtr->gameDifficulty == GameDifficulty_Easy)
    {
        chara->health = Q12(17995.605f); // TODO: Some percentage taken from 30000?
    }
    else
    {
        chara->health = Q12(30000.0f);
    }

    chara->moveSpeed                          = Q12(0.0f);
    chara->collision.cylinder.radius          = Q12(0.3f);
    chara->collision.shapeOffsets.cylinder.vx = Q12(0.0f);
    chara->collision.shapeOffsets.cylinder.vz = Q12(0.0f);
    chara->collision.state                    = CharaCollisionState_4;
    chara->headingAngle                       = chara->rotation.vy;
    chara->flags                             |= CharaFlag_Hit;

    localUnknown23Props.someState_F0 = 0;

    if (chara->model.stateStep == 0)
    {
        chara->model.controlState = 1;
        chara->model.stateStep    = 0;
    }
    else
    {
        chara->model.controlState = chara->model.stateStep;
        chara->model.stateStep    = 0;
    }

    Chara_AnimSet(chara, ANIM_STATUS(2, false), 115);
    ModelAnim_AnimInfoSet(&chara->model.anim, UNKKOWN_23_ANIM_INFOS);

    Chara_DamageClear(chara);

    if (g_SavegamePtr->gameDifficulty == GameDifficulty_Hard)
    {
        localUnknown23Props.bossFightTimer_F4 = Q12(300.0f);
    }
    else
    {
        localUnknown23Props.bossFightTimer_F4 = Q12(30.0f);
    }

    func_800DD67C(&chara->position, chara, boneCoords);
    func_800DFA14();

    chara->flags |= CharaFlag_NoRadioStatic;
    return true;
}

void func_800DFCE4(s_SubCharacter* chara) // 0x800DFCE4
{
    if (unknown23Props.someState_F0 == 0)
    {
        if (unknown23Props.bossFightTimer_F4 < Q12(0.0f))
        {
            chara->health        = 0;
            chara->damage.amount = 1;
        }

        if (!func_8004C328(false))
        {
            unknown23Props.bossFightTimer_F4 -= g_DeltaTime;
        }

        if (!(chara->flags & CharaFlag_Hit))
        {
            chara->damage.amount *= 10;
        }

        if (chara->damage.amount > Q12(0.0f))
        {
            chara->health = MAX(Q12(0.0f), chara->health - chara->damage.amount);
            if (chara->health <= Q12(0.0f) && func_800DFB04() == 0)
            {
                Savegame_EventFlagSet(EventFlag_582);
                chara->model.controlState = 5;
                chara->model.stateStep    = 0;
                chara->health             = NO_VALUE;
                chara->flags             |= CharaFlag_Unk2;
                unknown23Props.someState_F0++;
            }
        }
    }

    Chara_DamageClear(chara);
}

void func_800DFE10(s_SubCharacter* chara) // 0x800DFE10
{
    s16 temp_v0;
    s16 var_v0;
    s16 var_v0_2;
    s32 tmp;

    temp_v0 = Math_AngleNormalizeSigned(ratan2(g_SysWork.playerWork.player.position.vx - chara->position.vx,
                                               g_SysWork.playerWork.player.position.vz - chara->position.vz) -
                                        chara->rotation.vy);
    var_v0  = ABS(temp_v0);

    if (var_v0 > Q12_ANGLE(10.0f))
    {
        var_v0_2 = Q12_ANGLE(90.0f);
        tmp      = Q12_MULT_PRECISE(g_DeltaTime, var_v0_2);
        if (temp_v0 > 0)
        {
            chara->rotation.vy += tmp;
        }
        else
        {
            chara->rotation.vy -= tmp;
        }
    }
}

void func_800DFEF0(s_SubCharacter* chara) // 0x800DFEF0
{
    if (chara->model.stateStep == 0)
    {
        chara->model.stateStep++;
        return;
    }

    if (chara->model.anim.status == 8)
    {
        chara->model.controlState = 2;
        chara->model.stateStep    = 0;
    }
}

void func_800DFF28(s_SubCharacter* chara) // 0x800DFF28
{
    if (chara->model.stateStep == 0)
    {
        chara->model.stateStep++;
    }
}

void func_800DFF44(s_SubCharacter* chara) // 0x800DFF44
{
    if (chara->model.stateStep == 0)
    {
        chara->model.stateStep++;
    }
}

void func_800DFF60(s_SubCharacter* chara, GsCOORDINATE2* boneCoords) // 0x800DFF60
{
    MATRIX          transformMat;
    VECTOR3         pos;
    q3_12           angleDeltaToPlayer;
    s_SubCharacter* localChara;

    localChara = chara;

    if (chara->model.stateStep == 0)
    {
        chara->model.stateStep++;
        unknown23Props.timer_E8 = Q12(1.5f);
        chara->flags           &= ~CharaFlag_Hit;
        return;
    }

    if (boneCoords == NULL)
    {
        func_800DFE10(chara);
    }

    switch (chara->model.stateStep)
    {
        case 1:
            if (boneCoords)
            {
                Vw_CoordHierarchyMatrixCompute(&boneCoords[6], &transformMat);
                pos.vx = Q8_TO_Q12(transformMat.t[0]);
                pos.vy = Q8_TO_Q12(transformMat.t[1]);
                pos.vz = Q8_TO_Q12(transformMat.t[2]);

                if (!(Rng_Rand16() & 0xF0))
                {
                    func_800DD0EC(&pos, 6);
                }

                Vw_CoordHierarchyMatrixCompute(&boneCoords[10], &transformMat);
                pos.vx = Q8_TO_Q12(transformMat.t[0]);
                pos.vy = Q8_TO_Q12(transformMat.t[1]);
                pos.vz = Q8_TO_Q12(transformMat.t[2]);

                if (!(Rng_Rand16() & 0xF0))
                {
                    func_800DD0EC(&pos, 10);
                }

                if (localUnknown23Props.timer_E8 < Q12(0.0f))
                {
                    if (g_SavegamePtr->gameDifficulty == GameDifficulty_Hard)
                    {
                        localUnknown23Props.timer_E8 = Q12(2.0f);
                    }
                    else
                    {
                        localUnknown23Props.timer_E8 = Q12(2.5f);
                    }

                    chara->model.stateStep++;
                }

                localUnknown23Props.timer_E8 -= g_DeltaTime;
            }
            break;

        case 2:
            if (boneCoords)
            {
                Vw_CoordHierarchyMatrixCompute(&boneCoords[6], &transformMat);
                pos.vx = Q8_TO_Q12(transformMat.t[0]);
                pos.vy = Q8_TO_Q12(transformMat.t[1]);
                pos.vz = Q8_TO_Q12(transformMat.t[2]);

                if (!(Rng_Rand16() & 0xFC))
                {
                    func_800DD0EC(&pos, 6);
                }

                if (!(Rng_Rand16() & 0x30))
                {
                    func_800DD260(&pos, &pos);
                }

                Vw_CoordHierarchyMatrixCompute(&boneCoords[10], &transformMat);
                pos.vx = Q8_TO_Q12(transformMat.t[0]);
                pos.vy = Q8_TO_Q12(transformMat.t[1]);
                pos.vz = Q8_TO_Q12(transformMat.t[2]);

                if (!(Rng_Rand16() & 0xFC))
                {
                    func_800DD0EC(&pos, 10);
                }

                if (!(Rng_Rand16() & 0x30))
                {
                    func_800DD260(&pos, &pos);
                }

                if (!(Rng_Rand16() & 0xFC))
                {
                    func_800DD464(&pos);
                }

                angleDeltaToPlayer = abs(Math_AngleNormalizeSigned(Math_AngleBetweenPositionsGet(chara->position, g_SysWork.playerWork.player.position) -
                                                       chara->rotation.vy));

                if (localUnknown23Props.timer_E8 < Q12(0.0f) && angleDeltaToPlayer < Q12_ANGLE(12.0f))
                {
                    localUnknown23Props.timer_E8 = Q12(0.3f);
                    chara->model.stateStep++;
                    break;
                }

                localUnknown23Props.timer_E8 -= g_DeltaTime;
            }
            break;

        case 3:
            if (boneCoords)
            {
                Vw_CoordHierarchyMatrixCompute(&boneCoords[6], &transformMat);
                pos.vx = Q8_TO_Q12(transformMat.t[0]);
                pos.vy = Q8_TO_Q12(transformMat.t[1]);
                pos.vz = Q8_TO_Q12(transformMat.t[2]);

                if (!(Rng_Rand16() & 0xFC))
                {
                    func_800DD0EC(&pos, 6);
                }

                if (!(Rng_Rand16() & 0x30))
                {
                    func_800DD3D4(&pos, D_800F48A8.velocityX_3C, 0, D_800F48A8.velocityZ_40);
                }

                Vw_CoordHierarchyMatrixCompute(&boneCoords[10], &transformMat);
                pos.vx = Q8_TO_Q12(transformMat.t[0]);
                pos.vy = Q8_TO_Q12(transformMat.t[1]);
                pos.vz = Q8_TO_Q12(transformMat.t[2]);

                if (!(Rng_Rand16() & 0xFC))
                {
                    func_800DD0EC(&pos, 10);
                }

                if (!(Rng_Rand16() & 0x30))
                {
                    func_800DD3D4(&pos, D_800F48A8.velocityX_3C, 0, D_800F48A8.velocityZ_40);
                }

                if (!(Rng_Rand16() & 0xFC))
                {
                    func_800DD464(&pos);
                }

                if (localUnknown23Props.timer_E8 < Q12(0.0f))
                {
                    chara->model.stateStep++;

                    if (g_SavegamePtr->gameDifficulty == GameDifficulty_Hard)
                    {
                        localUnknown23Props.timer_E8 = Q12(2.5f);
                    }
                    else
                    {
                        localUnknown23Props.timer_E8 = Q12(1.5f);
                    }
                }

                localUnknown23Props.timer_E8 -= g_DeltaTime;
            }
            break;

        case 4:
            if (boneCoords)
            {
                Vw_CoordHierarchyMatrixCompute(&boneCoords[6], &transformMat);
                pos.vx = Q8_TO_Q12(transformMat.t[0]);
                pos.vy = Q8_TO_Q12(transformMat.t[1]);
                pos.vz = Q8_TO_Q12(transformMat.t[2]);

                if (!(Rng_Rand16() & 0x70))
                {
                    func_800DD3D4(&pos, D_800F48A8.velocityX_3C, 0, D_800F48A8.velocityZ_40);
                }

                Vw_CoordHierarchyMatrixCompute(&boneCoords[10], &transformMat);
                pos.vx = Q8_TO_Q12(transformMat.t[0]);
                pos.vy = Q8_TO_Q12(transformMat.t[1]);
                pos.vz = Q8_TO_Q12(transformMat.t[2]);

                if (!(Rng_Rand16() & 0x70))
                {
                    func_800DD3D4(&pos, D_800F48A8.velocityX_3C, 0, D_800F48A8.velocityZ_40);
                }

                if (!(Rng_Rand16() & 0xFC))
                {
                    func_800DD464(&pos);
                }

                if (localUnknown23Props.timer_E8 < Q12(0.0f))
                {
                    chara->model.stateStep++;
                }

                localUnknown23Props.timer_E8 -= g_DeltaTime;
            }
            break;

        case 5:
            chara->model.controlState = 2;
            chara->model.stateStep    = 0;
            chara->flags             |= CharaFlag_Hit;
            break;
    }
}

q19_12 func_800E04C4(void) // 0x800E04C4
{
    q19_12 base;

    if (g_SavegamePtr->gameDifficulty == GameDifficulty_Hard)
    {
        base = Q12(2.0f);
    }
    else
    {
        base = Q12(5.0f);
    }

    return base + Rng_GenerateInt(0, Q12(2.0f) - 1);
}

void func_800E0528(s_SubCharacter* chara) // 0x800E0528
{
    if (chara->model.stateStep == 0)
    {
        unknown23Props.timer_E8 = func_800E04C4();
        chara->model.stateStep++;
        return;
    }

    func_800DFE10(chara);

    switch (chara->model.stateStep)
    {
        case 1:
            if (unknown23Props.timer_E8 <= Q12(0.0f))
            {
                chara->model.stateStep = 2;
            }
            break;

        case 2:
            chara->model.controlState = 3;
            chara->model.stateStep    = 0;
            break;
    }

    unknown23Props.timer_E8 -= g_DeltaTime;
}

void func_800E05DC(s_SubCharacter* chara, GsCOORDINATE2* boneCoords) // 0x800E05DC
{
    switch (chara->model.controlState)
    {
        case 4:
            func_800DFEF0(chara);
            break;

        case 5:
            func_800DFF28(chara);
            break;

        case 6:
            func_800DFF44(chara);
            break;

        case 3:
            func_800DFF60(chara, 0);
            break;

        case 2:
            func_800E0528(chara);
            break;

        case 1:
            break;
    }
}

void func_800E0670(s_SubCharacter* chara, GsCOORDINATE2* boneCoords) // 0x800E0670
{
    s32 dist;

    func_800DB608();

    if (chara->model.controlState == 3)
    {
        func_800DFF60(chara, boneCoords);
    }

    dist = Math_Vector2MagCalcSafeQ6(g_SysWork.playerWork.player.position.vx - chara->position.vx,
                               g_SysWork.playerWork.player.position.vz - chara->position.vz);
    if (dist < Q12(2.5f) && func_800DFB04() == 0)
    {
        func_800DFA48(&g_SysWork.playerWork.player.position, &chara->position);
    }
}

void func_800E0728(s_SubCharacter* chara) // 0x800E0728
{
    s_CollisionResult sp10;

    chara->fallSpeed += g_GravitySpeed;
    func_8005C944(chara, &sp10);
    chara->rotation.vy = Math_AngleNormalizeSigned(chara->rotation.vy);
}

void func_800E0774(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords) // 0x800E0774
{
    s_AnimInfo* animInfo;

    Math_MatrixTransform(&chara->position, &chara->rotation, boneCoords);

    if (chara->model.anim.status != ANIM_STATUS(0, false))
    {
        animInfo = &UNKKOWN_23_ANIM_INFOS[chara->model.anim.status];
        animInfo->playbackFunc(&chara->model, anmHdr, boneCoords, animInfo);
    }
}

void func_800E07F0(s_SubCharacter* chara, GsCOORDINATE2* boneCoords) // 0x800E07F0
{
    MATRIX transformMat;
    q19_12 posY;
    q19_12 posX;
    q19_12 posZ;

    Vw_CoordHierarchyMatrixCompute(&boneCoords[2], &transformMat);
    posX = Q8_TO_Q12(transformMat.t[0]) - chara->position.vx;
    posY = Q8_TO_Q12(transformMat.t[1]) - chara->position.vy;
    posZ = Q8_TO_Q12(transformMat.t[2]) - chara->position.vz;

    chara->collision.cylinder.radius = Q12(0.5f);
    chara->collision.cylinder.field_2  = Q12(0.5f);
    chara->collision.box.top  = posY - Q12(0.25f);
    chara->collision.box.bottom  = posY;
    chara->collision.box.height  = posY + Q12(0.25f);
    chara->collision.box.offsetY  = posY;

    sharedFunc_800CD920_3_s03(chara, posX, posZ);

    chara->collision.shapeOffsets.box.vx = chara->collision.shapeOffsets.cylinder.vx;
    chara->collision.shapeOffsets.box.vz = chara->collision.shapeOffsets.cylinder.vz;
}

void func_800E0888(s_SubCharacter* chara, GsCOORDINATE2* boneCoords) // 0x800E0888
{
    q19_12 posY;

    if (chara->model.anim.flags & AnimFlag_Visible)
    {
        func_800E07F0(chara, boneCoords);
        return;
    }

    posY            = chara->position.vy;
    chara->collision.box.bottom = posY;
    chara->collision.box.height = posY;
    chara->collision.box.top = posY - Q12(1.0f);
    chara->collision.box.offsetY = posY - Q12(0.5f);
}

void func_800E08E4(s_SubCharacter* chara, GsCOORDINATE2* boneCoords) // 0x800E08E4
{
    if (chara->model.stateStep == 0)
    {
        func_800E05DC(chara, boneCoords);
    }
}

void func_800E0914(s_SubCharacter* chara) // 0x800E0914
{
    func_800DD6CC();
    func_800DF944();
}

void Unknown23_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* boneCoords) // 0x800E093C
{
    if (chara->model.controlState == 0)
    {
        Unknown23_Init(chara, boneCoords);
    }

    if (chara->model.controlState != 1)
    {
        if (g_DeltaTime != Q12(0.0f))
        {
            func_800DFCE4(chara);
            func_800E05DC(chara, boneCoords);
            func_800E08E4(chara, boneCoords);
            func_800E0728(chara);
            func_800E0774(chara, anmHdr, boneCoords);
            func_800E0888(chara, boneCoords);
            func_800E0670(chara, boneCoords);
            func_800E0914(chara);
            func_800DFB2C(chara->flags & CharaFlag_Unk2);
        }
        else
        {
            func_800DB608();
            func_800E0914(chara);
            func_800E0774(chara, anmHdr, boneCoords);
        }
    }
}
