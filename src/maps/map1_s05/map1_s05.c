#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map1/map1_s05.h"

INCLUDE_RODATA("asm/maps/map1_s05/nonmatchings/map1_s05", D_800C9578);

INCLUDE_RODATA("asm/maps/map1_s05/nonmatchings/map1_s05", g_MapOverlayHeader);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CAAD0);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CABF8);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CB040);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CB884);

void func_800CBE7C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 i;
    i = func_8005E7E0(7);
    if (i != NO_VALUE)
    {
        g_MapHdr_Table_4C[i].vx_0 = ((arg0 + (Rng_Rand16() & 63)) - 32) * 16;
        g_MapHdr_Table_4C[i].vy_8 = (arg1 + (Rng_Rand16() & 63)) * 16;
        g_MapHdr_Table_4C[i].vz_4 = ((arg2 + (Rng_Rand16() & 63)) - 32) * 16;
        g_MapHdr_Table_4C[i].field_B = 0;
        g_MapHdr_Table_4C[i].field_C.field_0 = 0;
        g_MapHdr_Table_4C[i].field_E.field_0 = arg3;
        g_MapHdr_Table_4C[i].field_10.s_1.field_0 = arg4;
        g_MapHdr_Table_4C[i].field_10.s_1.field_2 = (Rng_Rand16() & 31) + 16;
        g_MapHdr_Table_4C[i].field_10.s_1.field_3 = Rng_Rand16() & 15;
    }
}

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CBF74);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CC618);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CCDD4);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CCE2C);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CCF30);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CD5EC);

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CD754

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CD8D4

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CD98C

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CDAF0

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CDB10

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CE388

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CE774

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CEA68

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CEE94

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CEED0

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CEEDC

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CF03C

s32 func_800CF214()
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CF21C

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CF2CC

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CF2E4

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CF30C

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CF324

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CF34C

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CF3F0

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CF400

void func_800CF40C(void) {}

void func_800CF414(void) {}

void func_800CF41C(void) {}

void func_800CF424(void) {}

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800CF42C);

s32 func_800CF7A4()
{
    return 0;
}

void func_800CF7AC(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CF7B4

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CF7C4

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CF804

#include "maps/shared/Ai_Splithead_Update.h" // 0x800CF818

#include "maps/shared/Ai_Splithead_Init.h" // 0x800CF8D8

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800CF990_1_s05); // 0x800CF990

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800CFE94_1_s05); // 0x800CFE94

#include "maps/shared/sharedFunc_800D0054_1_s05.h" // 0x800D0054

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D00D0);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D0948);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D11A0);

void func_800D17BC(s_SubCharacter* chara)
{
    s32 movSpeed;
    s32 newSpeed;
    s32 volume;
    s32 timer0;
    s16 timer1;
    s16 timer1_div6;

    movSpeed = chara->moveSpeed_38;
    if (movSpeed > 0)
    {
        newSpeed = MAX(movSpeed - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.5997f), Q12_SHIFT), 0);
    }
    else
    {
        newSpeed = MIN(movSpeed + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.5997f), Q12_SHIFT), 0);
    }
    chara->moveSpeed_38 = newSpeed;

    switch (chara->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(11, false):
        case ANIM_STATUS(11, true):
            chara->properties_E4.splitHead.flags_E8 |= (1<<3);
            if (!func_800D4530(chara))
            {
                break;
            }
        case ANIM_STATUS(10, true):
            chara->model_0.anim_4.status_0 = ANIM_STATUS(1, false);
            Sd_EngineCmd(Sfx_Unk1477);
            break;
        case ANIM_STATUS(1, false):
        case ANIM_STATUS(1, true):
            timer0 = chara->properties_E4.splitHead.timer_F4;
            timer1 = D_800D5880;
            timer1_div6 = timer1 / 6;
            if (timer0 < timer1_div6)
            {
                volume = (timer0 << 7) / timer1_div6;
            }
            else if ((( timer1 * 5) / 6) < timer0)
            {
                volume = (( D_800D5880 - timer0) << 7) / timer1_div6;
            }
            else
            {
                volume = 0x80;
            }
            func_8005DE0C(Sfx_Unk1477, &chara->position_18, volume, Q12(16.0f), 0);
            if (chara->properties_E4.splitHead.timer_F4 > D_800D5880)
            {
                D_800D5880 = Q12(3.8f);
                chara->model_0.state_2 = 5;
                chara->properties_E4.splitHead.timer_F4 = Q12(0.0f);
                chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
                func_8004690C(Sfx_Unk1477);
                break;
            }
            chara->properties_E4.splitHead.timer_F4 += g_DeltaTime0;
            break;
    }
}

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D19B8);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D2214);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D2444);

void func_800D263C(s_SubCharacter* chara)
{
    if (Savegame_EventFlagGet(EventFlag_130))
    {
        chara->model_0.state_2 = 2;
        chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
        chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 0x100;
    }
}

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D267C_1_s05); // 0x800D267C

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D274C_1_s05); // 0x800D274C

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D2D74_1_s05); // 0x800D2D74

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D3388);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D3AFC_1_s05); // 0x800D3AFC

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D3B30_1_s05); // 0x800D3B30

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", sharedFunc_800D4070_1_s05); // 0x800D4070

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D4408);

void func_800D450C(s32 arg0, s32 arg1) // 0x800D450C
{
    sharedData_800D8614_1_s05 += arg0;
    sharedData_800D8616_1_s05 += arg1;
}

s32 func_800D4530(s_SubCharacter* chara)
{
    u32 timer;
    s32 ret;

    timer = chara->properties_E4.player.runTimer_F8;
    ret = 0;
    if (((timer > 0xC6000) && (chara->model_0.anim_4.time_4 < 0xAF000)) ||
        (( timer < 0xAF000) && (chara->model_0.anim_4.time_4 > 0xC6000)))
    {
        ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D4594);

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D489C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D48AC

void func_800D494C(void) // 0x800D494C
{
    s32 var_a0;

    var_a0 = 1;
    if (g_SysWork.npcs_1A0[0].health_B0 > 0)
    {
        var_a0 = 2;
        if (g_SysWork.npcs_1A0[0].properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x10)
        {
            var_a0 = 6;
        }
    }

    func_80035F4C(var_a0, Q12(0.1f), &D_800D5C3C);
}

void func_800D49A4(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
};

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D49AC);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D4D1C);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D525C);

INCLUDE_ASM("asm/maps/map1_s05/nonmatchings/map1_s05", func_800D5400);

INCLUDE_RODATA("asm/maps/map1_s05/nonmatchings/map1_s05", D_800CAAC4);
