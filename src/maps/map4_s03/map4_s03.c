#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map4/map4_s03.h"

INCLUDE_RODATA("asm/maps/map4_s03/nonmatchings/map4_s03", D_800C9578);

INCLUDE_RODATA("asm/maps/map4_s03/nonmatchings/map4_s03", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB0A4_4_s03.h" // 0x800CB0A4

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800CB1B0);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800CBE54);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800CC004);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CC700

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CCB4C

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CCC24

#include "maps/shared/Particle_Update.h" // 0x800CCF40

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", sharedFunc_800CEFF4_0_s00); // 0x800CD568

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CDCD8

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CDD74

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", sharedFunc_800CFFF8_0_s00); // 0x800CE058

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CE12C

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CE134

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CE1EC

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CE2AC

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CE464

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CE60C

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CE6C4

#include "maps/shared/sharedFunc_800D0CB8_0_s00.h" // 0x800CE864

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CE9B0

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CE9D0

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CF248

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CF634

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CFA58

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CFEA8

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CFEE4

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CFEF0

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800D0050

s32 func_800D0228()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800D0230

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800D02E0

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800D02F8

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800D0320

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800D0338

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800D0360

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800D0404

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800D0414

void func_800D0420() {}

void func_800D0428() {}

void func_800D0430() {}

void func_800D0438() {}

void func_800D0440() {}

s32 func_800D0448() // 0x800D0448
{
    return 0;
}

void func_800D0450() {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800D0458

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800D0468

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800D04A8

#include "maps/shared/sharedFunc_800CD6B0_3_s03.h" // 0x800D04BC

#include "maps/shared/sharedFunc_800CD7F8_3_s03.h" // 0x800D0604

#include "maps/shared/sharedFunc_800CD920_3_s03.h" // 0x800D072C

#include "maps/shared/sharedFunc_800CD940_3_s03.h" // 0x800D074C

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D078C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D0840);

void func_800D0C50(SVECTOR* rot, MATRIX* mat) // 0x800D0C50
{
    MATRIX sp10;

    SetRotMatrix(mat);
    SetTransMatrix(mat);
    func_80096A5C(rot, &sp10);
    SetMulRotMatrix(&sp10);
}

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D0CA0);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D0D6C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D0DE4);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D0EC0);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D0F40);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D0FD4);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D13B4);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D1478);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D1604);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D17FC);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D185C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D1900);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D19AC);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D19CC);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D19F0);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D1AFC);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D1C48);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D1D3C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D1FF4);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D2120);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D2150);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D21AC);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D2684);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D26FC);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D2790);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D2CC8);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D2CEC);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D2D28);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D2ED0);

void Ai_Twinfeeler_TextureLoad() // 0x800D3038
{
    // TODO: Does game ever use this texture afterward?
    // After this `Ai_Twinfeeler_Init` checks `Fs_QueueDoThingWhenEmpty()` before proceeding.
    // Could it be some preload/warm-up before the actual enemy file loads? If so, this func should be renamed.
    Fs_QueueStartReadTim(FILE_TEST_WARMTEST_TIM, FS_BUFFER_1, &D_800A9094);
}

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D3068);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D3114);

INCLUDE_RODATA("asm/maps/map4_s03/nonmatchings/map4_s03", D_800CA788);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D326C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D33D0);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D3428);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D344C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D3504);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D3528);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D354C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D35DC);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D3694);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D3AE0);

u8 func_800D3B1C(void) // 0x800D3B1C
{
    u8 sp10;

    func_8007F250(&sp10, 0);
    return sp10;
}

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D3B44);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D3B68);

void func_800D3B74(s_SubCharacter* chara) // 0x800D3B74
{
    if (chara->health_B0 >= 0)
    {
        chara->properties_E4.npc.field_11C = chara->health_B0;
        chara->health_B0                   = -1;
    }
}

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D3B98);

void func_800D3CBC(s_SubCharacter* chara) // 0x800D3CBC
{
    chara->position_18.vy               = Q12(10.0f);
    chara->properties_E4.npc.field_114 |= 4;
}

bool Ai_Twinfeeler_Init(s_SubCharacter* chara) // 0x800D3CD4
{
    s32             charaPosX;
    s32             charaPosZ;
    s_SubCharacter* chara2; // TODO: Not sure why this is needed here, could be an inline in this func.

    chara2 = chara;

    if (!Fs_QueueDoThingWhenEmpty())
    {
        return false;
    }

    charaPosX = chara->position_18.vx;
    charaPosZ = chara->position_18.vz;

    chara->health_B0 = Q12(3000.0f);

    chara2->properties_E4.larvalStalker.properties_E8[13].val32 = -1;

    chara->field_D4 = Q12(0.3f);

    chara->model_0.anim_4.alpha_A = Q12(0.0f);

    chara->moveSpeed_38    = 0;
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->field_E1_0      = 4;

    chara2->properties_E4.larvalStalker.properties_E8[1].val32     = 0;
    chara2->properties_E4.larvalStalker.properties_E8[2].val32     = 0;
    chara2->properties_E4.larvalStalker.properties_E8[3].val32     = 0;
    chara2->properties_E4.larvalStalker.properties_E8[9].val32     = 0;
    chara2->properties_E4.larvalStalker.properties_E8[10].val16[0] = 0;
    chara2->properties_E4.larvalStalker.properties_E8[11].val32    = 0;
    chara2->properties_E4.larvalStalker.properties_E8[6].val32     = charaPosX;
    chara2->properties_E4.larvalStalker.properties_E8[7].val32     = charaPosZ;

    func_800D3CBC(chara);

    chara->field_D8.offsetX_4 = Q12(0.0f);
    chara->field_D8.offsetZ_6 = Q12(0.0f);
    chara->flags_3E          |= CharaFlag_Unk3;

    if (chara->model_0.stateStep_3 != 0)
    {
        chara->model_0.state_2     = chara->model_0.stateStep_3;
        chara->model_0.stateStep_3 = 0;
    }
    else
    {
        chara->model_0.state_2     = 11;
        chara->model_0.stateStep_3 = 0;
    }

    *(u16*)&chara2->properties_E4.larvalStalker.properties_E8[0].val16[1] = -1;

    func_800D3B74(chara);

    Character_AnimSet(chara, ANIM_STATUS(8, false), 258);
    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, TWINFEELER_ANIM_INFOS);

    chara->damageReceived_C0 = Q12(0.0f);
    chara->field_BC          = 0;
    chara->field_B8          = 0;
    chara->field_B4          = 0;

    func_800D354C(&chara->position_18);
    chara->flags_3E |= CharaFlag_Unk9;
    return true;
}

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D3E18);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D3E58);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D3FB0);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D3FD8);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4000);

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

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4078);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4248);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D43AC);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4488);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4558);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D45C4);

void func_800D46E0(VECTOR3* vec0, VECTOR3* vec1) // 0x800D46E0
{
    sharedFunc_800CB0A4_4_s03(vec0, vec1);
}

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4700);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D48CC);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4924);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D49C0);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4A34);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4A78);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4B28);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4C0C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4C5C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4D80);

u32 func_800D4DD8(void) // 0x800D4DD8
{
    s32 var_v0;

    var_v0 = (g_SysWork.player_4C.chara_0.rotation_24.vy - 256) & 0xFFF;
    if (var_v0 < 0)
    {
        var_v0 += 0x1FF;
    }
    return var_v0 >> 9;
}

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4E00);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4E78);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D4FC0);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D50D8);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D511C);

void func_800D53B0(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D53B0
{
    switch (chara->model_0.state_2)
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

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D54B4);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D55C8);

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

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D5904);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D59C0);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D59EC);

void func_800D5B6C(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D5B6C
{
    s32 posY;

    if (chara->model_0.anim_4.flags_2 & 2)
    {
        func_800D5904(chara, coords);
        return;
    }

    posY            = chara->position_18.vy;
    chara->field_CA = posY;
    chara->field_CC = posY;
    chara->field_C8 = posY - Q12(1.0f);
    chara->field_CE = posY - Q12(0.5f);
}

void func_800D5BC8(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D5BC8
{
    if (chara->model_0.stateStep_3 == 0)
    {
        func_800D53B0(chara, coords);
    }
}

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D5BF8);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D5C3C);

void func_800D5DF4(s_SubCharacter* chara, GsCOORDINATE2* coords) // 0x800D5DF4
{
    if (g_DeltaTime0 != Q12(0.0f))
    {
        func_800D5C3C(chara, coords);
    }

    func_800D35DC(&chara->rotation_24);
}

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D5E30);

void Ai_Twinfeeler_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D5F28
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_Twinfeeler_TextureLoad(); // Just calls `Fs_QueueStartReadTim`.
        chara->model_0.state_2     = 1;
        chara->model_0.stateStep_3 = 0;
    }

    if (chara->model_0.state_2 != 1 || Ai_Twinfeeler_Init(chara))
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

            if (chara->model_0.state_2 != 10)
            {
                func_8004690C(Sfx_Unk1567);
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

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D607C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D6278);

void func_800D654C() {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D6554

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D65E8

INCLUDE_RODATA("asm/maps/map4_s03/nonmatchings/map4_s03", D_800CA814);

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

INCLUDE_RODATA("asm/maps/map4_s03/nonmatchings/map4_s03", D_800CABE8);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D6774);

INCLUDE_RODATA("asm/maps/map4_s03/nonmatchings/map4_s03", D_800CAC60);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D6F24);

s32 func_800D7394(void) // 0x800D7394
{
    if (g_DeltaTime0 != Q12(0.0f))
    {
        D_800DB914 = ((s32)(D_800DB918 * 0x7169AC35) >> 3) ^ 0xA547B39E;
        D_800DB918 = ((u32)(D_800DB914 * 0x892D719C) >> 3) ^ 0xC65A4B97;
    }

    return (u16)D_800DB914 & 0x7FFF;
}

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D7408);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D7450);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D7548);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D761C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D76BC);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D76E8);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D7718);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D7808);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D78D4);

INCLUDE_RODATA("asm/maps/map4_s03/nonmatchings/map4_s03", D_800CACA8);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D78F4);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D7AE0);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D7F1C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D81FC);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D8230);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D826C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D8354);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D84C0);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D85E4);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D8620);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D87AC);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D8874);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D88C8);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D8FC0);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D960C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D9824);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D991C);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800D9BB0);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800DA3E0);

INCLUDE_ASM("asm/maps/map4_s03/nonmatchings/map4_s03", func_800DA718);

INCLUDE_RODATA("asm/maps/map4_s03/nonmatchings/map4_s03", D_800CB080);

INCLUDE_RODATA("asm/maps/map4_s03/nonmatchings/map4_s03", D_800CB08C);

INCLUDE_RODATA("asm/maps/map4_s03/nonmatchings/map4_s03", D_800CB098);
