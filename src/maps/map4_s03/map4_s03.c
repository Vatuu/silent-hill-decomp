#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/particle.h"
#include "maps/characters/player.h"
#include "maps/map4/map4_s03.h"

INCLUDE_RODATA("maps/map4_s03/nonmatchings/map4_s03", D_800C9578);

INCLUDE_RODATA("maps/map4_s03/nonmatchings/map4_s03", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB0A4_4_s03.h" // 0x800CB0A4

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800CB1B0);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800CBE54);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800CC004);

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

#include "maps/shared/sharedFunc_800CD6B0_3_s03.h" // 0x800D04BC

#include "maps/shared/sharedFunc_800CD7F8_3_s03.h" // 0x800D0604

#include "maps/shared/sharedFunc_800CD920_3_s03.h" // 0x800D072C

#include "maps/shared/sharedFunc_800CD940_3_s03.h" // 0x800D074C

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D078C);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D0840);

void func_800D0C50(SVECTOR* rot, MATRIX* mat) // 0x800D0C50
{
    MATRIX outMat;

    SetRotMatrix(mat);
    SetTransMatrix(mat);
    Math_RotMatrixXyz(rot, &outMat);
    SetMulRotMatrix(&outMat);
}

void func_800D0CA0(q19_12 rotY, SVECTOR* pos) // 0x800D0CA0
{
    MATRIX      mat;
    VECTOR      trans;
    SVECTOR     rot; // Q3.12
    s_800E0988* ptr;

    ptr = &D_800E0988;

    SetRotMatrix(&ptr->world_8);
    SetTransMatrix(&ptr->world_8);

    ApplyRotMatrix(pos, &trans);

    trans.vx += ptr->world_8.t[0];
    trans.vy += ptr->world_8.t[1];
    trans.vz += ptr->world_8.t[2];

    TransMatrix(&mat, &trans);
    SetTransMatrix(&mat);

    rot.vx = FP_ANGLE(0.0f);
    rot.vy = rotY;
    rot.vz = FP_ANGLE(0.0f);
    Math_RotMatrixZxyNeg(&rot, &mat);
    SetMulRotMatrix(&mat);
}

void func_800D0D6C(MATRIX* out, SVECTOR* pos, q3_12 rotY) // 0x800D0D6C
{
    SVECTOR     rot; // Q3.12
    s_800E0988* ptr;

    ptr = &D_800E0988;

    rot.vx = FP_ANGLE(0.0f);
    rot.vy = rotY;
    rot.vz = FP_ANGLE(0.0f);
    Math_RotMatrixXyz(&rot, out);

    out->t[0] = Q12_TO_Q8(ptr->x_0) + pos->vx;
    out->t[1] = Q12_TO_Q8(Q12(0.0f));
    out->t[2] = Q12_TO_Q8(ptr->z_4) + pos->vz;
}

void func_800D0DE4(SVECTOR* out, VECTOR* in, q19_12 headingAngle, q19_12 dist) // 0x800D0DE4
{
    q19_12 offsetX;
    q19_12 offsetZ;
    s32    x;
    s32    z;

    offsetX = Q12_MULT_PRECISE(Math_Sin(headingAngle), dist);
    offsetZ = Q12_MULT_PRECISE(Math_Cos(headingAngle), dist);

    x = in->vx - D_800E0988.x_0;
    z = in->vz - D_800E0988.z_4;

    out->vx = Q12_TO_Q8(x + offsetX);
    out->vy = Q12_TO_Q8(in->vy);
    out->vz = Q12_TO_Q8(z + offsetZ);
}

void func_800D0EC0(u8* buf, s32 w, s32 h) // 0x800D0EC0
{
    s32 i, j;
    s32 sum;

    for (i = 0; i < h - 1; i++)
    {
        for (j = 0; j < w; j++)
        {
            sum   = buf[w + j];
            sum  += buf[j - 1];
            sum  += buf[j];
            sum  += buf[j + 1];
            sum >>= 2;

            if (sum <= 0)
            {
                buf[j] = 0;
            }
            else
            {
                buf[j] = sum;
            }
        }

        buf += w;
    }
}

s32 func_800D0F40(s32 arg0, s32 arg1, s32 arg2) // 0x800D0F40
{
    s32 index;

    index = (arg0 * arg1) >> 8;
    if (index != 0 && g_DeltaTime0 != 0)
    {
        index += Rng_GenerateUInt(-2, 1);
        // TODO: `CLAMP` doesn't match?
        index = MIN(255, index);
        index = MAX(index, 0);
    }

    // @hack Needed to match weird a2 usage.
    if (arg2)
    {
        arg2++;
        arg2--;
    }

    return D_800DAA58[index];
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D0FD4);

void func_800D13B4(u8* arg0, s32 arg1, s32 arg2, s32 arg3) // 0x800D13B4
{
    u8* buf;
    s32 i;
    s32 rnd;
    s32 index;

    buf = arg0 + (arg1 * (arg2 - 1));
    memset(buf, 0, arg1);

    if (arg3 > Q12(0.75f))
    {
        for (i = 0; i < 3; i++)
        {
            if (Rng_Rand16() & 0x70)
            {
                rnd            = Rng_Rand16() >> 2;
                index          = (rnd % (arg1 / 4)) + (arg1 / 4);
                buf[index + 1] = 0xff;
            }
        }
    }
}

void func_800D1478(SVECTOR* arg0, s32 arg1, q19_12 headingAgle, s32 mode, SVECTOR* arg4) // 0x800D1478
{
    s32    x;
    s32    y;
    s32    z;
    q19_12 dist;
    q19_12 angleStep;

    x = 0;
    y = 0;
    z = 0;

    switch (mode)
    {
        case 0:
        case 1:
            dist = (arg1 > Q12(0.75f)) ? 128 : 76;
            angleStep  = mode ? FP_ANGLE(-90.0f) : FP_ANGLE(90.0f);
            headingAgle += angleStep;

            x = Q12_MULT_PRECISE(dist, Math_Sin(headingAgle));
            z = Q12_MULT_PRECISE(dist, Math_Cos(headingAgle));
            y = (arg1 > Q12(0.75f)) ? 0x59 : 0x80;
            break;

        case 2:
            x = arg4->vx;
            y = arg4->vy;
            z = arg4->vz;
            break;

        case 3:
            break;
    }

    arg0->vx += Q12_MULT_PRECISE(x, g_DeltaTime0);
    arg0->vy += Q12_MULT_PRECISE(y, g_DeltaTime0);
    arg0->vz += Q12_MULT_PRECISE(z, g_DeltaTime0);
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D1604);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D17FC);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D185C);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D1900);

void func_800D19AC(VECTOR3* vec) // 0x800D19AC
{
    func_800D1900(vec, 3);
}

void func_800D19CC(VECTOR3* vec) // 0x800D19CC
{
    D_800E08F0.vx = vec->vx;
    D_800E08F0.vy = vec->vy;
    D_800E08F0.vz = vec->vz;
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D19F0);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D1AFC);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D1C48);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D1D3C);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D1FF4);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D2120);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D2150);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D21AC);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D2684);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D26FC);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D2790);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D2CC8);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D2CEC);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D2D28);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D2ED0);

void Ai_Twinfeeler_TextureLoad(void) // 0x800D3038
{
    // TODO: Does game ever use this texture afterward?
    // After this `Ai_Twinfeeler_Init` checks `Fs_QueueDoThingWhenEmpty()` before proceeding.
    // Could it be some preload/warm-up before the actual enemy file loads? If so, this func should be renamed.
    Fs_QueueStartReadTim(FILE_TEST_WARMTEST_TIM, FS_BUFFER_1, &D_800A9094);
}

void Math_Vector3Translate(VECTOR3* outVec, const VECTOR3* inVec, q19_12 headingAngle, q19_12 dist) // 0x800D3068
{
    outVec->vx = inVec->vx + Q12_MULT_PRECISE(Math_Sin(headingAngle), dist);
    outVec->vy = inVec->vy;
    outVec->vz = inVec->vz + Q12_MULT_PRECISE(Math_Cos(headingAngle), dist);
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D3114);

INCLUDE_RODATA("maps/map4_s03/nonmatchings/map4_s03", D_800CA788);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D326C);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D33D0);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D3428);

s_D_800E0930* func_800D344C(s_SubCharacter* chara, void (*funcptr)()) // 0x800D344C
{
    s_Collision      coll;
    s32              i;
    s_SubD_800E0930* node;
    s32*             marker;
    s_D_800E0930*    temp;
    
    temp = D_800E0930;

    for (i = 0; i < 3; i++, temp++)
    {
        marker = &temp->field_0;
        node = &temp->sub_4;

        if (!node->funcptr_14)
        {
            Collision_Get(&coll, chara->position_18.vx, chara->position_18.vz);

            node->chara_4 = chara;
            node->position_8.vx = chara->position_18.vx;
            node->position_8.vy = coll.groundHeight_0;
            node->position_8.vz = chara->position_18.vz;
            node->funcptr_14 = funcptr;
            node->field_0 = 0;

            *marker = 0;
            return temp;
        }
    }

    return NULL;
}

void func_800D3504(s_SubCharacter* chara) // 0x800D3504
{
    func_800D344C(chara, &func_800D326C);
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D3528);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D354C);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D35DC);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D3694);

void func_800D3AE0(s_SubCharacter* chara, s32 soundIdx)
{
    func_8005DC1C(D_800DB1F8[soundIdx].id_0, &chara->position_18, D_800DB1F8[soundIdx].volume_2.val16, 0);
}

u8 func_800D3B1C(void) // 0x800D3B1C
{
    u8 sp10;

    func_8007F250(&sp10, 0);
    return sp10;
}

void func_800D3B44(bool disableDamage)
{
    u8 sp10;

    func_8007F250(&sp10, disableDamage);
}

void func_800D3B68(s_SubCharacter* chara) // 0x800D3B68
{
    chara->health_B0 = chara->properties_E4.npc.field_11C;
}

void func_800D3B74(s_SubCharacter* chara) // 0x800D3B74
{
    if (chara->health_B0 >= 0)
    {
        chara->properties_E4.npc.field_11C = chara->health_B0;
        chara->health_B0                   = -1;
    }
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D3B98);

void func_800D3CBC(s_SubCharacter* chara) // 0x800D3CBC
{
    chara->position_18.vy               = Q12(10.0f);
    chara->properties_E4.npc.field_114 |= 1 << 2;
}

bool Ai_Twinfeeler_Init(s_SubCharacter* chara) // 0x800D3CD4
{
    q19_12          posX;
    q19_12          posZ;
    s_SubCharacter* localChara; // TODO: Not sure why this is needed here, could be an inline in this func.

    localChara = chara;

    if (!Fs_QueueDoThingWhenEmpty())
    {
        return false;
    }

    posX = chara->position_18.vx;
    posZ = chara->position_18.vz;

    chara->health_B0 = Q12(3000.0f);

    localChara->properties_E4.dummy.properties_E8[13].val32 = -1;

    chara->field_D4.radius_0 = Q12(0.3f);

    chara->model_0.anim_4.alpha_A = Q12(0.0f);

    chara->moveSpeed_38    = 0;
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->field_E1_0      = 4;

    localChara->properties_E4.dummy.properties_E8[1].val32     = 0;
    localChara->properties_E4.dummy.properties_E8[2].val32     = 0;
    localChara->properties_E4.dummy.properties_E8[3].val32     = 0;
    localChara->properties_E4.dummy.properties_E8[9].val32     = 0;
    localChara->properties_E4.dummy.properties_E8[10].val16[0] = 0;
    localChara->properties_E4.dummy.properties_E8[11].val32    = 0;
    localChara->properties_E4.dummy.properties_E8[6].val32     = posX;
    localChara->properties_E4.dummy.properties_E8[7].val32     = posZ;

    func_800D3CBC(chara);

    chara->field_D8.offsetX_4 = Q12(0.0f);
    chara->field_D8.offsetZ_6 = Q12(0.0f);
    chara->flags_3E          |= CharaFlag_Unk3;

    if (chara->model_0.stateStep_3 != 0)
    {
        chara->model_0.controlState_2     = chara->model_0.stateStep_3;
        chara->model_0.stateStep_3 = 0;
    }
    else
    {
        chara->model_0.controlState_2     = 11;
        chara->model_0.stateStep_3 = 0;
    }

    *(u16*)&localChara->properties_E4.dummy.properties_E8[0].val16[1] = -1;

    func_800D3B74(chara);

    Character_AnimSet(chara, ANIM_STATUS(8, false), 258);
    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, TWINFEELER_ANIM_INFOS);

    Chara_DamageClear(chara);

    func_800D354C(&chara->position_18);
    chara->flags_3E |= CharaFlag_Unk9;
    return true;
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D3E18);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D3E58);

void func_800D3FB0(s_SubCharacter* chara) // 0x800D3FB0
{
    if (chara->model_0.controlState_2 >= 2)
    {
        chara->model_0.controlState_2     = 12;
        chara->model_0.stateStep_3 = 0;
    }
    else
    {
        chara->model_0.stateStep_3 = 12;
    }
}

void func_800D3FD8(s_SubCharacter* chara) // 0x800D3FD8
{
    if (chara->model_0.controlState_2 >= 2)
    {
        chara->model_0.controlState_2     = 13;
        chara->model_0.stateStep_3 = 0;
    }
    else
    {
        chara->model_0.stateStep_3 = 13;
    }
}

void func_800D4000(s_SubCharacter* chara) // 0x800D4000
{
    if (chara->model_0.controlState_2 >= 2)
    {
        chara->model_0.controlState_2     = 3;
        chara->model_0.stateStep_3 = 0;
    }
    else
    {
        chara->model_0.stateStep_3 = 3;
    }
}

void func_800D4028(s_SubCharacter* chara) // 0x800D4028
{
    if (chara->model_0.stateStep_3 == 0)
    {
        func_800D3B74(chara);
        chara->moveSpeed_38 = Q12(0.0f);
        chara->model_0.stateStep_3++;
    }

    func_800D3CBC(chara);
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D4078);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D4248);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D43AC);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D4488);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D4558);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D45C4);

void func_800D46E0(VECTOR3* vec0, VECTOR3* vec1) // 0x800D46E0
{
    sharedFunc_800CB0A4_4_s03(vec0, vec1);
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D4700);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D48CC);

s32 func_800D4924(VECTOR3* vec, q19_12 angle) // 0x800D4924
{
    q19_12 posX;
    q19_12 posZ;

    posX = vec->vx + Q12_MULT_FLOAT_PRECISE(Math_Sin(angle), 1.0f);
    posZ = vec->vz + Q12_MULT_FLOAT_PRECISE(Math_Cos(angle), 1.0f);

    return func_800D48CC(Q12_TO_Q8(posX), Q12_TO_Q8(posZ));
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D49C0);

void func_800D4A34(s_SubCharacter* chara) // 0x800D4A34
{
    if (chara->model_0.stateStep_3 == 0)
    {
        chara->model_0.anim_4.status_0 = ANIM_STATUS(17, false);
        chara->moveSpeed_38            = 0;
        chara->model_0.stateStep_3++;
    }

    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(18, false))
    {
        chara->model_0.controlState_2     = 8;
        chara->model_0.stateStep_3 = 0;
    }
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D4A78);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D4B28);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D4C0C);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D4C5C);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D4D80);

u32 func_800D4DD8(void) // 0x800D4DD8
{
    s32 var_v0;

    var_v0 = (g_SysWork.playerWork_4C.player_0.rotation_24.vy - 256) & 0xFFF;
    if (var_v0 < 0)
    {
        var_v0 += 0x1FF;
    }
    return var_v0 >> 9;
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D4E00);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D4E78);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D4FC0);

void func_800D50D8(s_SubCharacter* chara) // 0x800D50D8
{
    if (chara->model_0.stateStep_3 == 0)
    {
        chara->model_0.anim_4.status_0 = ANIM_STATUS(13, false);
        chara->model_0.stateStep_3++;
    }

    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(18, false))
    {
        chara->model_0.controlState_2     = 4;
        chara->model_0.stateStep_3 = 0;
        chara->moveSpeed_38        = 0;
    }
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D511C);

void func_800D53B0(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D53B0
{
    switch (chara->model_0.controlState_2)
    {
        case 11:
            func_800D4028(chara);
            break;

        case 12:
            func_800D4078(chara);
            break;

        case 13:
            func_800D4248(chara);
            break;

        case 5:
            func_800D45C4(chara);
            break;

        case 6:
            func_800D4700(chara, coords);
            break;

        case 4:
            func_800D4B28(chara);
            break;

        case 3:
            func_800D4FC0(chara);
            break;

        case 7:
            func_800D4A34(chara);
            break;

        case 8:
            func_800D4A78(chara, coords);
            break;

        case 2:
            func_800D50D8(chara);
            break;

        case 9:
            func_800D511C(chara);
            break;

        case 10:
            func_800D49C0(chara);
            break;
    }
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D54B4);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D55C8);

void func_800D5888(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D5888
{
    s_AnimInfo* animInfo;

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coords);

    if (chara->model_0.anim_4.status_0 != ANIM_STATUS(0, false))
    {
        animInfo = &TWINFEELER_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
    }
}

void func_800D5904(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D5904
{
    MATRIX mat;
    q19_12 unkPosY;
    q19_12 unkBasePosY;
    q19_12 posX;
    q19_12 posY;
    q19_12 posZ;

    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(2, true))
    {
        Vw_CoordHierarchyMatrixCompute(&coords[6], &mat);
    }
    else
    {
        Vw_CoordHierarchyMatrixCompute(&coords[14], &mat);
    }
    
    posY = chara->position_18.vy;
    posX = Q8_TO_Q12(mat.t[0]) - chara->position_18.vx;
    posZ = Q8_TO_Q12(mat.t[2]) - chara->position_18.vz;

    unkBasePosY = Q8_TO_Q12(mat.t[1]) - posY;
    unkPosY = unkBasePosY - Q12(0.25f);
    chara->field_C8.field_0 = unkPosY;
    if (unkPosY >= posY)
    {
        chara->field_C8.field_2 = posY;
    }
    else
    {
        chara->field_C8.field_2 = unkPosY;
    }

    chara->field_C8.field_4 = unkBasePosY + Q12(0.25f);
    chara->field_D4.radius_0 = Q12(0.5f);
    chara->field_C8.field_6 = unkBasePosY;
    chara->field_D4.field_2 = Q12(0.4f);
    sharedFunc_800CD920_3_s03(chara, posX, posZ);
        
    chara->field_D8.offsetX_0 = chara->field_D8.offsetX_4;
    chara->field_D8.offsetZ_2 = chara->field_D8.offsetZ_6;
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D59C0);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D59EC);

void func_800D5B6C(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D5B6C
{
    q19_12 posY;

    if (chara->model_0.anim_4.flags_2 & 2)
    {
        func_800D5904(chara, coords);
        return;
    }

    posY            = chara->position_18.vy;
    chara->field_C8.field_2 = posY;
    chara->field_C8.field_4 = posY;
    chara->field_C8.field_0 = posY - Q12(1.0f);
    chara->field_C8.field_6 = posY - Q12(0.5f);
}

void func_800D5BC8(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D5BC8
{
    if (chara->model_0.stateStep_3 == 0)
    {
        func_800D53B0(chara, coords);
    }
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D5BF8);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D5C3C);

void func_800D5DF4(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D5DF4
{
    if (g_DeltaTime0 != Q12(0.0f))
    {
        func_800D5C3C(chara, coords);
    }

    func_800D35DC(&chara->rotation_24);
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D5E30);

void Ai_Twinfeeler_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D5F28
{
    if (chara->model_0.controlState_2 == ModelState_Uninitialized)
    {
        Ai_Twinfeeler_TextureLoad(); // Just calls `Fs_QueueStartReadTim`.
        chara->model_0.controlState_2     = 1;
        chara->model_0.stateStep_3 = 0;
    }

    if (chara->model_0.controlState_2 != 1 || Ai_Twinfeeler_Init(chara))
    {
        if (g_DeltaTime0 != Q12(0.0f))
        {
            func_800D3E58(chara);
            func_800D53B0(chara, coords);
            func_800D55C8(chara);
            func_800D5BC8(chara, coords);
            func_800D5888(chara, anmHdr, coords);
            func_800D5B6C(chara, coords);
            func_800D54B4(chara, coords);
            func_800D5DF4(chara, coords);
            func_800D59EC(chara, coords);
            func_800D5E30(chara, coords);
            func_800D3B44(chara->flags_3E & CharaFlag_Unk2);

            if (chara->model_0.controlState_2 != 10)
            {
                Sd_SfxStop(Sfx_Unk1567);
            }
        }
        else
        {
            func_800D5888(chara, anmHdr, coords);
            func_800D5DF4(chara, coords);
        }
    }
}

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D606C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D607C

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D6278);

void func_800D654C(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D6554

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D65E8

INCLUDE_RODATA("maps/map4_s03/nonmatchings/map4_s03", D_800CA814);

// Assumed type.
const s32 D_800CA824[] = {
    -25,
    -25,
    -30,
    -30,
    -40,
    -40,
    -66,
    -66,
    -30,
    -30,
    -20,
    -20,
    -23,
    -23,
    -28,
    -28,
};

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tDaddy...where_are_you...? ",
    "~J0(1.0)\tCheryl! ~E  ",
    "\tThere_is_a_ ~C2 Hunting_rifle ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tNothing_unusual. ~E ",
    "\tA_picture_is_projected ~N\n\ton_the_screen. ",
    "\tCheryl... ~N\n\twhere_could_she_be? ~E "
};

void MapEvent_CommonItemTake(void) // 0x800D667C
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 27:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M4S03_FirstAidKit;
            break;

        case 28:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M4S03_RifleShells0;
            break;

        case 29:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M4S03_RifleShells1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800D6704(void) // 0x800D6704
{
    s32 i;

    // Breaks from loop if there are any characters with ID in range [1, 24].
    for (i = 0; i < 6; i++)
    {
        if (g_SysWork.npcs_1A0[i].model_0.charaId_0 >= Chara_Harry &&
            g_SysWork.npcs_1A0[i].model_0.charaId_0 <= Chara_MonsterCybil)
        {
            break;
        }
    }

    if (i != 6)
    {
        g_DeltaTime0 = 0;
    }

    Event_ItemTake(InventoryItemId_HuntingRifle, RIFLE_AMMO_PICKUP_ITEM_COUNT, EventFlag_M4S03_PickupHuntingRifle, 17);
}

void func_800D6774(void) // 0x800D6774
{
    s_Collision coll;
    VECTOR3     vec;
    s32         i;

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 11)
    {
        SysWork_StateStepSet(0, 12);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(120.5f), Q12(-9.5f), Q12(137.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vy, g_SysWork.playerWork_4C.player_0.position_18.vz,
                             Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            D_800DB9E0 = Q12(0.0f);
            break;

        case 1:
        case 2:
            Camera_PositionSet(NULL, Q12(120.5f), Q12(-5.5f), Q12(138.0f), Q12(0.0f), Q12(0.0f), cam_mv_prm_user.max_spd_xz >> 3, cam_mv_prm_user.max_spd_y >> 1, false);
            D_800DB9E0 += g_DeltaTime0;

            if (D_800DB9E0 >= Q12(1.8f))
            {
                break;
            }

            i = Rng_Rand16() % (((Q12(2.5f) - D_800DB9E0) / Q12(0.5f)) + 1);
            for (; i > 0; i--)
            {
                vec.vx = Rng_GenerateInt(Q12(118.0f), Q12(123.0f) - 1);
                vec.vy = 0;
                vec.vz = Rng_GenerateInt(Q12(140.0f), Q12(143.0f) - 1);
                func_800D19AC(&vec);
            }
            break;

        case 3:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(119.48f), Q12(-0.5f), Q12(143.35f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(118.16f), Q12(-0.86f), Q12(139.59f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            break;

        case 9:
        case 10:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(119.87f), Q12(-3.4f), Q12(138.71f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(119.13f), Q12(-1.49f), Q12(142.15f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            break;
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_8008D448();
            Game_FlashlightAttributesFix();

            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            Game_TurnFlashlightOn();

            Gfx_MapInitMapEffectsUpdate(6, 3);

            if (Savegame_EventFlagGet(EventFlag_322))
            {
                func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 129, false);
            }
            else
            {
                func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 128, false);
            }

            Collision_Get(&coll, g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz);
            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();

            g_SysWork.playerWork_4C.player_0.position_18.vy = coll.groundHeight_0;

            func_8005DC1C(Sfx_Unk1556, &QVECTOR3(119.5f, 0.0f, 141.5f), Q8_CLAMPED(0.5f), 0);
            func_80089470();
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            func_80085EB8(2, &g_SysWork.playerWork_4C.player_0, 0, false);
            break;

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(4.5f), false);
            break;

        case 3:
            func_800D3FB0(&g_SysWork.npcs_1A0[0]);
            Savegame_EventFlagSet(EventFlag_329);
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementDelayed(Q12(0.7f), false);
            break;

        case 5:
            func_80085EB8(3, &g_SysWork.playerWork_4C.player_0, 0, false);
            SysWork_StateStepIncrement(0);

        case 6:
            func_80085EB8(1, &g_SysWork.playerWork_4C.player_0, 0, false);
            break;

        case 7:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 123, false);
            SysWork_StateStepIncrement(0);

        case 8:
            SysWork_StateStepIncrementDelayed(Q12(2.4f), false);
            break;

        case 9:
            Player_ControlUnfreeze(true);
            Player_ControlFreeze();
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 52, false);

            g_SysWork.playerWork_4C.player_0.position_18.vx += Q12(0.5f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy += FP_ANGLE(45.0f);

            SysWork_StateStepIncrement(0);

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(3.5f), false);
            break;

        case 11:
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepReset();
            break;

        case 12:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            if (g_SysWork.sysStateStep_C[0] != 12)
            {
                Camera_PositionSet(NULL, Q12(119.87f), Q12(-3.4f), Q12(138.71f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
                Camera_LookAtSet(NULL, Q12(119.13f), Q12(-1.49f), Q12(142.15f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
                func_800D3E18(&g_SysWork.npcs_1A0[0]);
                func_800D4000(&g_SysWork.npcs_1A0[0]);
            }
            break;

        case 13:
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(120.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(141.5f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(-45.0f);

            Savegame_EventFlagSet(EventFlag_329);

            Player_ControlUnfreeze(true);

            SysWork_StateSetNext(SysState_Gameplay);

            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        default:
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            func_800D4000(&g_SysWork.npcs_1A0[0]);

            Savegame_EventFlagSet(EventFlag_324);

            func_8003A16C();
            break;
    }
}

void func_800D6F24(void) // 0x800D6F24
{
    s32   var_a0;
    s32   var_a0_2;
    s32   var_a2;
    s32   var_v0;
    void* var_s0;

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 9)
    {
        SysWork_StateStepSet(0, 9);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 2, Q12(0.0f), false);
            break;

        case 3:
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(124.4f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(140.9f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(90.0f);

            Camera_PositionSet(NULL, Q12(122.1f), Q12(-4.34f), Q12(141.87f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(125.65f), Q12(-2.74f), Q12(140.95f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 4:
            func_800D3FD8(&g_SysWork.npcs_1A0[0]);
            SysWork_StateStepIncrement(0);

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 6:
            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);

            Savegame_EventFlagSet(EventFlag_327);

            Camera_PositionSet(NULL, Q12(128.82f), Q12(-0.26f), Q12(139.1f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(125.24f), Q12(-0.8f), Q12(140.79f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_8005DC1C(Sfx_Unk1554, &QVECTOR3(132.0f, -0.75f, 140.0f), Q8_CLAMPED(0.5f), 0);

            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case 8:
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(126.86f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(140.36f);

            Camera_PositionSet(NULL, Q12(122.55f), Q12(-2.1f), Q12(138.5f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(126.39f), Q12(-1.73f), Q12(139.56f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrementDelayed(Q12(3.5f), false);

            if (g_SysWork.sysStateStep_C[0] != 8)
            {
                SysWork_StateStepReset();
            }
            break;

        case 9:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 10:
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(126.86f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(140.36f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(90.0f);

            func_80088F94(&g_SysWork.npcs_1A0[0], 0, 0);

            Savegame_EventFlagSet(EventFlag_327);

            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);
            break;

        default:
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(false);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            func_8003A16C();
            break;
    }
}

s32 func_800D7394(void) // 0x800D7394
{
    if (g_DeltaTime0 != Q12(0.0f))
    {
        D_800DB914 = ((s32)(D_800DB918 * 0x7169AC35) >> 3) ^ 0xA547B39E;
        D_800DB918 = ((u32)(D_800DB914 * 0x892D719C) >> 3) ^ 0xC65A4B97;
    }

    return (u16)D_800DB914 & SHRT_MAX;
}

void func_800D7408(void) // 0x800D7408
{
    D_800E0698.field_0 = 0;
    D_800E0698.field_4 = 0;

    func_800D7450();
    func_800D7548();

    WorldObject_ModelNameSet(&D_800E0698.objRef_238, "REF_NEAR");
}

void func_800D7450(void) // 0x800D7450
{
    e_FsFile texFileIdx;
    s32      i;

    texFileIdx = NO_VALUE;

    for (i = 0; i < 3; i++)
    {
        switch (i)
        {
            case 0:
                texFileIdx          = FILE_TIM_TV1_TIM;
                D_800DB91C.tPage[1] = 29;
                D_800DB91C.u        = 0;
                D_800DB91C.v        = 0;
                D_800DB91C.clutY    = 0;
                break;

            case 1:
                texFileIdx          = FILE_TIM_TV2_TIM;
                D_800DB91C.tPage[1] = 12;
                D_800DB91C.u        = 32;
                D_800DB91C.v        = 0;
                D_800DB91C.clutY    = 5;
                break;

            case 2:
                texFileIdx          = FILE_TIM_TV3_TIM;
                D_800DB91C.tPage[1] = 28;
                D_800DB91C.v        = 128;
                D_800DB91C.u        = 0;
                D_800DB91C.clutY    = 10;
                break;
        }

        Fs_QueueStartReadTim(texFileIdx, FS_BUFFER_1, &D_800DB91C);
    }
}

void func_800D7548(void) // 0x800D7548
{
    s32 i;
    s32 j;

    func_800D761C(&D_800E0698.field_8[9], &D_800DB7D4, 1, 0);

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            func_800D761C(&D_800E0698.field_8[(i * 3) + j], &D_800DB7E4[i][j], 0, 0);
        }
    }
}

void func_800D761C(s_800E06A0* arg0, s_800DB7D4* arg1, s8 arg2, s32 arg3) // 0x800D761C
{
    arg0->field_20    = arg2;
    arg0->field_22    = 0;
    arg0->field_24    = 0;
    arg0->field_23    = 0;
    arg0->field_2C    = 0;
    arg0->field_21    = 0;

    arg0->field_0     = arg1->field_0;
    arg0->field_18    = arg1->field_8;

    // Switches `vy` to the other arg1 field?
    arg0->field_8.vx  = arg1->field_8.vx;
    arg0->field_8.vy  = arg1->field_0.vy;
    arg0->field_8.vz  = arg1->field_8.vz;
    arg0->field_10.vx = arg1->field_0.vx;
    arg0->field_10.vy = arg1->field_8.vy;
    arg0->field_10.vz = arg1->field_0.vz;
}

void func_800D76BC(s32 arg0) // 0x800D76BC
{
    D_800E0698.field_0 = arg0;
    D_800E0698.field_4 = 0;

    func_800D7548();
}

bool func_800D76E8(void) // 0x800D76E8
{
    s32  i;
    bool result;

    result = true;
    
    for(i = 0; i < ARRAY_SIZE(D_800E0698.field_8); i++)
    {
        result &= D_800E0698.field_8[i].field_21;
    }

    return result;
}

void func_800D7718(void) // 0x800D7718
{
    MATRIX      mat;
    s16         temp_v0;
    s32         var_s2;
    s32         i;
    s_800E06A0* ptr;

    func_80049C2C(&mat, Q12(160.0f), Q12(0.0f), Q12(40.0f));
    SetRotMatrix(&mat);
    SetTransMatrix(&mat);

    var_s2 = 188;
    if (D_800E0698.field_0 != 0)
    {
        if (g_DeltaTime0 != Q12(0.0f))
        {
            D_800DB924.pad++;
            if (!(D_800DB924.pad & 0xB))
            {
                var_s2 = 164;
            }
        }

        g_WorldGfx_ObjectAdd(&D_800E0698.objRef_238, &D_800DB7C8, (SVECTOR3*)&D_800DB924);
    }

    for (i = 0; i < ARRAY_SIZE(D_800E0698.field_8); i++)
    {
        func_800D7808(&D_800E0698.field_8[i], i);
        func_800D88C8(&D_800E0698.field_8[i], var_s2);
    }
}

void func_800D7808(s_800E06A0* arg0, s32 arg1) // 0x800D7808
{
    // TODO: `arg1` is unused, but might be passed to one of these funcs.
    s32 temp;

    if (g_DeltaTime0 == 0)
    {
        return;
    }

    temp = D_800E0698.field_0;
    switch (D_800E0698.field_0)
    {
        case 0:
            func_800D78D4(arg0);
            break;

        case 1:
            if (func_800D78F4(arg0) != 0)
            {
                arg0->field_21 = temp;
            }
            break;

        case 2:
            if (func_800D7AE0(arg0) != 0)
            {
                func_800D76BC(3);
            }
            break;

        case 3:
            func_800D7F1C(arg0);
            break;
    }
}

bool func_800D78D4(s_800E06A0* arg0) // 0x800D78D4
{
    return func_800D81FC(arg0, 0);
}

INCLUDE_RODATA("maps/map4_s03/nonmatchings/map4_s03", D_800CACA8);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D78F4);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D7AE0);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D7F1C);

bool func_800D81FC(s_800E06A0* arg0, s32 arg1) // 0x800D81FC
{
    if (arg0->field_24 == 0)
    {
        arg0->field_28 = arg1;
    }
    
    arg0->field_30 = 0;
    arg0->field_34 = 0;
    arg0->field_36 = 0;
    
    return arg0->field_24 >= arg0->field_28;
}

bool func_800D8230(s_800E06A0* arg0, s32 arg1, s32 arg2) // 0x800D8230
{
    if (arg0->field_24 == 0)
    {
        arg0->field_28 = arg2;
    }

    arg0->field_30 = arg1 + 6;
    arg0->field_36 = 0;
    arg0->field_34 = 0;

    return arg0->field_24 >= arg0->field_28;
}

bool func_800D826C(s_800E06A0* arg0, s32 arg1, s32 arg2) // 0x800D826C
{
    if (arg0->field_24 == 0)
    {
        arg0->field_28 = arg2;
    }

    arg0->field_30 = 4;
    arg0->field_34 = 0;

    switch (arg1)
    {
        default:
        case 0:
            arg0->field_36 = 0;
            break;

        case 1:
            arg0->field_36 = 64;
            break;

        case 2:
            arg0->field_36 = 32;
            break;

        case 4:
            arg0->field_36 = (u32)((MIN(arg2, arg0->field_24) << 12) / arg2) >> 6; // TODO: Weird shifts, not sure if these are FP related?
            break;

        case 3:
            arg0->field_36 = 64 - ((((MIN(arg2, arg0->field_24) << 12) / arg2) << 6) >> 12);
            break;
    }

    return arg0->field_24 >= arg0->field_28;
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D8354);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D84C0);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D85E4);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D8620);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D87AC);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D8874);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800D88C8);

void func_800D8FC0(void) // 0x800D8FC0
{
    typedef struct
    {
        SPRT*     sprt_0;
        DR_TPAGE* tpage_4;
        DR_STP*   stp_8;
        s32       activeBufferIdx_C;
    } g_GteScratchData_func_800D8FC0;

    g_GteScratchData_func_800D8FC0* scratchData;
    s32                             i;

    scratchData = PSX_SCRATCH_ADDR(0);

    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 5)
    {
        SysWork_StateStepSet(0, 5);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800868DC(0);
            func_800868DC(1);
            func_800868DC(2);
            func_800868DC(3);
            func_800868DC(4);
            func_800868DC(5);
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_333);
            func_800D76BC(1);
            Game_TurnFlashlightOn();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(2.2f), false);

            scratchData->activeBufferIdx_C = g_ActiveBufferIdx;
            scratchData->sprt_0            = (SPRT*)GsOUT_PACKET_P;
            for (i = 0; i < 2; i++)
            {
                setCodeWord(scratchData->sprt_0, PRIM_RECT | RECT_BLEND | RECT_TEXTURE, PACKED_COLOR(128, 128, 128, 0));
                setXY0Fast(scratchData->sprt_0, ((i << 8) - 160), -112);
                scratchData->sprt_0->u0 = 0;
                scratchData->sprt_0->v0 = (scratchData->activeBufferIdx_C == 0) ? 32 : 0;
                setWH(scratchData->sprt_0, (i == 0) ? 256 : 64, 224);
                addPrimFast(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratchData->sprt_0, 4);

                scratchData->sprt_0++;
                scratchData->tpage_4 = (DR_TPAGE*)scratchData->sprt_0;
                setDrawTPage(scratchData->tpage_4, 0, 0, getTPageFromBuffer(2, 0, scratchData->activeBufferIdx_C, i));

                AddPrim(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratchData->tpage_4);
                scratchData->tpage_4++;
                scratchData->sprt_0 = (SPRT*)scratchData->tpage_4;
            }

            scratchData->stp_8 = (DR_STP*)scratchData->sprt_0;
            SetDrawStp(scratchData->stp_8, 1);
            addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[ORDERING_TABLE_SIZE - 1], scratchData->stp_8);
            scratchData->stp_8++;
            SetDrawStp(scratchData->stp_8, 0);
            addPrim(&g_OrderingTable2[g_ActiveBufferIdx].org[0], scratchData->stp_8);
            scratchData->stp_8++;
            GsOUT_PACKET_P = (PACKET*)scratchData->stp_8;

            Camera_LookAtSet(NULL, Q12(162.5f), Q12(-1.15f), Q12(50.5f), Q12(0.375f), Q12(0.475f), Q12(0.0374f), Q12(0.0875f), false);
            break;

        case 3:
            Fs_QueueStartSeek(FILE_1ST_NO_BLOCK_TIM);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(162.77f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(55.43f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(180.0f);

            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, 2);
            func_8008D438();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(163.78f), Q12(-2.31f), Q12(58.91f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(162.5f), Q12(-1.15f), Q12(50.5f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrement(0);
            break;

        case 4:
            if (func_800D76E8())
            {
                SysWork_StateStepIncrement(0);
            }

            // Warp camera.
            Camera_PositionSet(NULL,
                               func_800868F4(Q12(-1.28f), Q12(6.5f), 0) + Q12(163.78f),
                               func_800868F4(Q12(1.16f), Q12(6.5f), 1) - Q12(2.31f),
                               func_800868F4(Q12(-4.41f), Q12(6.5f), 2) + Q12(58.91f),
                               Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), false);

            if (g_SysWork.sysStateStep_C[0] != 4)
            {
                SysWork_StateStepReset();
            }
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_330);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(162.77f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(55.43f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(180.0f);
            break;
    }
}

void func_800D960C(void) // 0x800D960C
{
    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] < 4)
    {
        SysWork_StateStepReset();
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(159.59f), Q12(-1.25f), Q12(59.49f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(161.69f), Q12(-1.53f), Q12(56.1f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_800D76BC(2);
            D_800DB9E2 = 0;

            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, 2);

            func_8008D448();
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 2:
            Map_MessageWithAudio(16, &D_800DB9E2, &D_800DB92C);
            break;

        case 3:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        default:
            Savegame_EventFlagSet(EventFlag_332);

            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(false);
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D9824(void) // 0x800D9824
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            ScreenFade_ResetTimestep();

            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_800D4000(&g_SysWork.npcs_1A0[0]);

            SysWork_StateStepIncrement(0);
            break;

        default:
            Savegame_EventFlagClear(EventFlag_335);

            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            break;
    }
}

void Map_WorldObjectsInit(void) // 0x800D991C
{
    D_800E05E2 = 0;
    D_800E05E0 = 0;
    D_800E05E1 = 0;
    D_800E05A8 = 0;
    D_800E05AC = 0;
    D_800E05AE = 0;

    if (!Savegame_EventFlagGet(EventFlag_324))
    {
        g_MapOverlayHeader.charaUpdateFuncs_194[Chara_Twinfeeler] = func_800D3694;
        func_800D7408();
        Fs_QueueWaitForEmpty();
    }

    WorldObjectInit(&g_WorldObject_Fence, "FENCE_HI", 130.5f, 0.0f, -93.0f, 0.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject_Mal5_21, "MAL5_21_", 117.2464f, -0.685f, 145.896f, -36.0f, 243.0f, 60.21f);

    WorldObject_ModelNameSet(&g_WorldObject_Mal6[0], "MAL6_27_");
    WorldObject_ModelNameSet(&g_WorldObject_Mal6[1], "MAL6_28_");

    Math_Vector3Set(&g_WorldObject_UnkPos, Q12(132.0f), Q12(-0.75f), Q12(140.0f));
    Math_SetSVectorFast(&g_WorldObject_UnkRot, FP_ANGLE(90.0f), FP_ANGLE(90.0f), FP_ANGLE(0.0f));

    WorldObjectInit(&g_WorldObject_SavePad, D_800A99E4.savePadName_4, 217.15f, -1.25f, -22.9f, 0.0f, -173.0f, 0.0f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        D_800C4418.field_0 = Q12(5.0f);
    }
    else
    {
        D_800C4418.field_0 = Q12(3.5f);
    }

    D_800C4418.field_2 = Q12(0.2f);
    D_800C4418.field_4 = Q12(0.1f);
    D_800C4418.field_6 = Q12(0.45f);
    D_800C4418.field_8 = Q12(6.0f);
    D_800C4418.field_A = Q12(0.55f);
    D_800C4418.field_C = 18;

    if (Savegame_EventFlagGet(EventFlag_324) && !Savegame_EventFlagGet(EventFlag_327))
    {
        Savegame_EventFlagSet(EventFlag_335);
        Savegame_EventFlagClear(EventFlag_325);
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void func_800D9BB0(void) // 0x800D9BB0
{
    q19_12 var_a0; // Angle?
    q19_12 var;    // Angle?
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 6, -1, 6) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        g_WorldGfx_ObjectAdd(&g_WorldObject_SavePad.object_0, &g_WorldObject_SavePad.position_1C, &g_WorldObject_SavePad.rotation_28);
    }

    if ((PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) || PLAYER_IN_MAP_CHUNK(vx, 1, 5, -1, 5)) && PLAYER_IN_MAP_CHUNK(vz, 1, -3, -1, -3))
    {
        if (Savegame_EventFlagGet(EventFlag_320))
        {
            if (!D_800E05A8) 
            {
                func_8005DC1C(Sfx_Unk1555, &QVECTOR3(130.5f, 0.0f, -93.0f), Q8(0.5f), 0);

                g_SysWork.playerWork_4C.player_0.field_34 += Q12(1.0f);
                D_800E05AE += Q12(1.0f);
            }

            func_80069844(2);
            D_800E05A8 += g_DeltaTime0;

            if (D_800E05AC) {} // @hack

            var = ratan2(FP_ANGLE(360.0f), FP_FROM(g_DeltaTime2 * Math_Cos(g_WorldObject_Fence.rotation_28.vx), Q12_SHIFT));
            var_a0 = MAX(Q12(0.0f), Q12(1.0f) - (D_800E05A8 * 2));
            D_800E05AC = Q12_MULT_PRECISE(var_a0, D_800E05AC + var);
            g_WorldObject_Fence.rotation_28.vx += Q12_MULT_PRECISE(g_DeltaTime0, D_800E05AC);

            D_800E05AE = MIN(Q12(15.0f), (D_800E05AE + g_DeltaTime2) + (g_DeltaTime2 >> 4));

            g_WorldObject_Fence.position_1C.vy += Q12_MULT_PRECISE(g_DeltaTime0, D_800E05AE);
            if (g_WorldObject_Fence.rotation_28.vx > FP_ANGLE(90.0f))
            {
                g_WorldObject_Fence.rotation_28.vx = FP_ANGLE(90.0f);
            }

            if (D_800E05A8 > Q12(1.0f))
            {
                // NOTE: Changed return type to `s32` in context.
                if (sharedFunc_800D2EA4_0_s00())
                {
                    Savegame_EventFlagSet(EventFlag_322);
                }

                Savegame_EventFlagSet(EventFlag_321);
            }
        }
        else
        {
            func_8006982C(2);
        }

        g_WorldGfx_ObjectAdd(&g_WorldObject_Fence.object_0, &g_WorldObject_Fence.position_1C, &g_WorldObject_Fence.rotation_28);
    }

    if ((PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) || PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4)) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M4S03_PickupHuntingRifle))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject_Mal5_21.object_0, &g_WorldObject_Mal5_21.position_1C, &g_WorldObject_Mal5_21.rotation_28);
        }

        if (!Savegame_EventFlagGet(EventFlag_327))
        {
            func_8006982C(2);
            g_WorldGfx_ObjectAdd(&g_WorldObject_Mal6[0], &g_WorldObject_UnkPos, &g_WorldObject_UnkRot);
        }
        else
        {
            func_80069844(2);
            g_WorldGfx_ObjectAdd(&g_WorldObject_Mal6[1], &g_WorldObject_UnkPos, &g_WorldObject_UnkRot);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 6, -1, 6) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M4S03_FirstAidKit))
        {
            g_WorldGfx_ObjectAdd(g_CommonWorldObjects, &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 6, -1, 6) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M4S03_RifleShells0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 6, -1, 6) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (!Savegame_EventFlagGet(EventFlag_M4S03_RifleShells1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }
}

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800DA3E0);

INCLUDE_ASM("maps/map4_s03/nonmatchings/map4_s03", func_800DA718);

INCLUDE_RODATA("maps/map4_s03/nonmatchings/map4_s03", D_800CB08C);

INCLUDE_RODATA("maps/map4_s03/nonmatchings/map4_s03", D_800CB098);
