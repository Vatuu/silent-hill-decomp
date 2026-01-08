#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map4/map4_s02.h"
#include "maps/characters/air_screamer.h"
#include "maps/characters/groaner.h"
#include "maps/characters/romper.h"

INCLUDE_RODATA("maps/map4_s02/nonmatchings/map4_s02", D_800C9578);

INCLUDE_RODATA("maps/map4_s02/nonmatchings/map4_s02", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CC808

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CCBFC

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CCCD4

#include "maps/shared/Particle_Update.h" // 0x800CCFF0

#include "maps/shared/sharedFunc_800CEFF4_0_s00.h" // 0x800CD634

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CDED8

#include "maps/shared/sharedFunc_800CEFD0_1_s02.h" // 0x800CDF74

#include "maps/shared/sharedFunc_800CFFF8_0_s00.h" // 0x800CE258

#include "maps/shared/sharedFunc_800D0690_1_s03.h" // 0x800CE32C

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CE478

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CE480

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CE538

#include "maps/shared/sharedFunc_800D0700_0_s00.h" // 0x800CE5F8

#include "../src/maps/characters/player.c"

INCLUDE_RODATA("maps/map4_s02/nonmatchings/map4_s02", D_800CA77C);

INCLUDE_RODATA("maps/map4_s02/nonmatchings/map4_s02", D_800CA780);

INCLUDE_RODATA("maps/map4_s02/nonmatchings/map4_s02", D_800CA78C);

INCLUDE_RODATA("maps/map4_s02/nonmatchings/map4_s02", D_800CA7A4);

INCLUDE_RODATA("maps/map4_s02/nonmatchings/map4_s02", D_800CA7BC);

INCLUDE_RODATA("maps/map4_s02/nonmatchings/map4_s02", D_800CA7D4);

INCLUDE_RODATA("maps/map4_s02/nonmatchings/map4_s02", sharedData_800CAA98_0_s01);

// TODO: Move this line into separate `Chara_AirScreamer` split.
// TODO: Most of the code below also belongs to `air_screamer.c`, move there once `INCLUDE_ASM` gaps are matched.
#include "../src/maps/characters/air_screamer.c" // 0x800D0B24

#include "maps/shared/Ai_Groaner_Update.h" // 0x800E1B5C

#include "maps/shared/Ai_Groaner_Init.h" // 0x800E1C58

#include "maps/shared/sharedFunc_800E33DC_2_s00.h" // 0x800E1E58

#include "maps/shared/sharedFunc_800E384C_2_s00.h" // 0x800E22C8

#include "maps/shared/sharedFunc_800E39D8_2_s00.h" // 0x800E2454

#include "maps/shared/sharedFunc_800E3E94_2_s00.h" // 0x800E2910

#include "maps/shared/sharedFunc_800E4830_2_s00.h" // 0x800E32AC

#include "maps/shared/sharedFunc_800E4E84_2_s00.h" // 0x800E3900

#include "maps/shared/sharedFunc_800E554C_2_s00.h" // 0x800E3FC8

#include "maps/shared/sharedFunc_800E55B0_2_s00.h" // 0x800E402C

#include "maps/shared/sharedFunc_800E5930_2_s00.h" // 0x800E43AC

#include "maps/shared/sharedFunc_800E5AA4_2_s00.h" // 0x800E4520

#include "maps/shared/sharedFunc_800E5EC4_2_s00.h" // 0x800E4940

#include "maps/shared/sharedFunc_800E6338_2_s00.h" // 0x800E4DB4

#include "maps/shared/sharedFunc_800E71E8_2_s00.h" // 0x800E5C64

#include "maps/shared/Ai_Romper_Update.h" // 0x800E6134

#include "maps/shared/Ai_Romper_Init.h" // 0x800E61D4

#include "maps/shared/sharedFunc_800E5FC8_2_s02.h" // 0x800E63C4

#include "maps/shared/sharedFunc_800E60FC_2_s02.h" // 0x800E64F8

#include "maps/shared/sharedFunc_800E6420_2_s02.h" // 0x800E681C

#include "maps/shared/Ai_Romper_Control.h" // 0x800E6AE4

#include "maps/shared/Ai_Romper_Control_1.h" // 0x800E6B54

#include "maps/shared/Ai_Romper_Control_2.h" // 0x800E6C74

#include "maps/shared/Ai_Romper_Control_3.h" // 0x800E703C

#include "maps/shared/Ai_Romper_Control_4.h" // 0x800E793C

#include "maps/shared/Ai_Romper_Control_5.h" // 0x800E7DD4

#include "maps/shared/Ai_Romper_Control_6.h" // 0x800E8438

#include "maps/shared/Ai_Romper_Control_7.h" // 0x800E8554

#include "maps/shared/Ai_Romper_Control_8.h" // 0x800E87D0

#include "maps/shared/Ai_Romper_Control_9.h" // 0x800E8874

#include "maps/shared/Ai_Romper_Control_10.h" // 0x800E887C

#include "maps/shared/Ai_Romper_Control_11.h" // 0x800E8ABC

#include "maps/shared/sharedFunc_800E8730_2_s02.h" // 0x800E8B2C

#include "maps/shared/sharedFunc_800E8A40_2_s02.h" // 0x800E8E3C

#include "maps/shared/sharedFunc_800E8DFC_2_s02.h" // 0x800E91F8

#include "maps/shared/sharedFunc_800E939C_2_s02.h" // 0x800E9798

#include "maps/shared/sharedFunc_800E94B4_2_s02.h" // 0x800E98B0

#include "maps/shared/sharedFunc_800E9714_2_s02.h" // 0x800E9B10

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800E9D28

#include "maps/shared/Map_RoomIdxGet.h" // 0x800E9D38

void func_800E9F34(void)
{
    s32              var_a0;
    s32              var_a1;
    s32              temp_a3;
    s_func_80035F4C* var_a2;

    temp_a3 = g_SavegamePtr->mapRoomIdx_A5;
    var_a1  = 0x199;

    if (g_GameWork.bgmIdx_5B2 == 0xD)
    {
        var_a2 = &D_800ED418;

        switch (temp_a3)
        {
            case 0xF:
                var_a0 = 4;
                break;

            case 0x10:
                var_a0 = 6;
                break;

            case 0xE:
                if (Savegame_EventFlagGet(EventFlag_352))
                {
                    var_a1 = 0xA000;
                    var_a0 = 0x101;
                }
                else if (Savegame_EventFlagGet(EventFlag_350))
                {
                    var_a1 = 0x200;
                    var_a0 = 0x101;
                }
                else if (Savegame_EventFlagGet(EventFlag_348))
                {
                    if (g_SysWork.npcs_1A0[0].health_B0 < 0x3E8000)
                    {
                        var_a0 = 0x1FE;
                    }
                    else
                    {
                        if (g_SysWork.playerWork_4C.player_0.position_18.vy > -0x800)
                        {
                            D_800ED420 = 0x10A;
                        }
                        else if (g_SysWork.playerWork_4C.player_0.position_18.vy < -0x2800)
                        {
                            D_800ED420 = 0x112;
                        }

                        var_a0 = D_800ED420;

                        if (g_SysWork.npcs_1A0[0].health_B0 < 0x7D0000)
                        {
                            var_a0 |= 0x24;
                        }
                        else if (g_SysWork.npcs_1A0[0].health_B0 < 0xBB8000)
                        {
                            var_a0 |= 4;
                        }
                    }
                }
                else
                {
                    var_a1 = 0x1000;
                    var_a0 = 0x101;
                }
                break;

            default:
                var_a0 = 1;
                break;
        }
    }
    else if (g_GameWork.bgmIdx_5B2 == 0x21)
    {
        var_a2 = &D_800ED424;

        switch (temp_a3)
        {
            case 0x12:
                if (Savegame_EventFlagGet(EventFlag_334) || !Savegame_EventFlagGet(EventFlag_333))
                {
                    var_a0 = 2;
                }
                else
                {
                    if (Savegame_EventFlagGet(EventFlag_330))
                    {
                        var_a0 = 0x1E;
                        var_a1 = 0x28000;
                    }
                    else
                    {
                        var_a0 = 0xE;
                    }
                }
                break;

            case 0x13:
                Savegame_EventFlagSet(EventFlag_334);

                if (Savegame_EventFlagGet(EventFlag_320))
                {
                    var_a0 = 0x101;
                }
                else
                {
                    var_a0 = 0x104;
                }
                break;

            case 0x15:
                var_a0 = 8;
                break;

            case 0x14:
                if (Savegame_EventFlagGet(EventFlag_327))
                {
                    var_a0 = 0x110;
                }
                else if (Savegame_EventFlagGet(EventFlag_324) || Savegame_EventFlagGet(EventFlag_329))
                {
                    var_a1 = 0x800;

                    if (g_SysWork.npcs_1A0[0].health_B0 > 0 && g_SysWork.npcs_1A0[0].position_18.vy < 0x1000)
                    {
                        var_a0 = 0x160;
                    }
                    else
                    {
                        var_a0 = 0x120;
                    }
                }
                else
                {
                    var_a0 = 0x110;
                }
                break;

            default:
                var_a0 = 0x101;
                break;
        }
    }
    else
    {
        var_a2 = &D_800ED458;

        if (!Savegame_EventFlagGet(EventFlag_314))
        {
            if (g_SysWork.playerWork_4C.player_0.position_18.vz < 0x28000)
            {
                Savegame_EventFlagSet(EventFlag_314);
            }
            var_a0 = 2;
        }
        else
        {
            var_a0 = D_800ED42C[temp_a3];
        }
    }

    func_80035F4C(var_a0, var_a1, var_a2);
}

void func_800EA208(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800EA210

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800EA2A4

void func_800EA338(void) {}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~C3\tgreen_lion ~E ",
    "~C3\tAlchemilla_Hospital ~E "
};

void Map_WorldObjectsInit(void) // 0x800EA340
{
    D_800F13AC = 0;

    WorldObjectNoRotInit(&g_WorldObject_Kidn04, "KIDN04_H", -119.8019f, 5.0f, 107.861f);

    WorldObject_ModelNameSet(&g_WorldObject_Fan0, "FAN0_HID");

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        g_SysWork.npcId_2280 = 3;
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        g_SysWork.npcId_2280 = 4;
    }
    else
    {
        g_SysWork.npcId_2280 = 5;
    }
}

void func_800EA3F0(void) // 0x800EA3F0
{
    VECTOR3  objPos;
    SVECTOR3 objRot;
    q19_12   dist0;
    q19_12   dist1;
    s32      tmp0;
    s32      i;
    s32      vol;
    s32      audioBalance;
    s32      var_v0;
    s32      tmp1;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    func_80069844(0xFFFF);

    if ((PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3)) ||
        (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3)))
    {
        g_WorldGfx_ObjectAdd(&g_WorldObject_Kidn04.object_0, &g_WorldObject_Kidn04.position_1C, &(SVECTOR3){ 0, 0, 0 });
        func_8006982C(2);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (Savegame_EventFlagGet(EventFlag_346))
        {
            func_8006982C(4);

            if (g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(-68.0f))
            {
                Savegame_EventFlagClear(EventFlag_346);
            }
        }
        else
        {
            func_8006982C(2);
        }
    }

    audioBalance = 0;
    tmp0 = Q12_MULT_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f));

    for (i = 0; i < ARRAY_SIZE(D_800ED8B0); i++)
    {
        switch (i)
        {
            case 0:
                objPos.vx = Q12(53.211f);
                objPos.vy = Q12(-2.375f);
                objPos.vz = Q12(32.5f);
                Math_SetSVectorFast(&objRot, 0, 0, 0);
                break;

            case 4:
                objPos.vx = Q12(56.575f);
                objPos.vy = Q12(-2.875f);
                objPos.vz = Q12(27.5f);
                break;

            case 7:
                objPos.vx = Q12(65.45f);
                objPos.vy = Q12(-2.875f);
                objPos.vz = Q12(27.5f);
                objRot.vy = FP_ANGLE(180.0f);
                break;

            case 11:
                objPos.vx = Q12(68.8f);
                objPos.vy = Q12(-2.375f);
                objPos.vz = Q12(32.5f);
                break;
        }

        if (i < 7)
        {
            D_800ED8B0[i] -= tmp0;
        }
        else
        {
            D_800ED8B0[i] += tmp0;
        }

        // @hack
        tmp1 = (g_SysWork.playerWork_4C.player_0.position_18.vx / ((s32)(40.0f * Q12(1.0f))));
        
        objRot.vx = D_800ED8B0[i];
        
        if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject_Fan0, &objPos, &objRot);
        }

        audioBalance += Sound_StereoBalanceGet(&objPos);
        objPos.vz -= Q12(5.0f);
    }

    if (PLAYER_NEAR_POS(vx, 61.0f, 4.0f) && PLAYER_NEAR_POS(vz, 22.5f, 5.0f))
    {
        vol = Q8(1.0f);
    }
    else
    {        
        dist0 = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - Q12(61.0f), g_SysWork.playerWork_4C.player_0.position_18.vz - Q12(27.5f));
        dist1 = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - Q12(61.0f), g_SysWork.playerWork_4C.player_0.position_18.vz - Q12(17.5f));
        if (dist1 >= dist0) 
        {
            tmp0 = dist0;
        }
        else
        {
            tmp0 = dist1;
        }

        if (tmp0 <= Q12(32.0f))
        {
            tmp1 = tmp0 >> 9;
            vol = Q8(1.0f) - tmp1;
        }
        else
        {
            vol = Q8(0.0f);
        }
    }

    if (vol != Q8(0.0f)) 
    {
        if (!D_800F13AC)
        {
            SD_Call(Sfx_Unk1542);
            D_800F13AC++;
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1542, audioBalance >> 4, -vol, 0);
    }
    else if (D_800F13AC)
    {
        Sd_SfxStop(Sfx_Unk1542);
        D_800F13AC = 0;
    }
}
