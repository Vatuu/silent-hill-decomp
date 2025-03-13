#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"

#include <memory.h>
#include <libgte.h>
#include <libgpu.h>
#include <libetc.h>

void func_8002E630() 
{
    s_800B5508* ptr;
    s32 i;

    func_800303E4();

    D_800B5480 = 0; 

    bzero(D_800B5508, 1816);
    bzero(D_800B2780, 768);

    for (i = 0; i < 8; i++) 
    {
        D_800B5508[i].field_0 = 0;
        
        func_8002E730(i);

        switch (i) 
        {                          
            case 0:
                ptr = D_800B2780;
                break;

            case 4:
                ptr = D_800B3680;
                break;

            default:
                ptr = D_800B4580;
                break;
        }

        D_800B5508[i].field_14 = ptr;
        
        func_8002E6E4(i);
    } 
}

void func_8002E6E4(s32 idx)
{
    s_800B5508* temp_v0;
    s_800B5508* temp_s0;

    temp_v0 = &D_800B5508;
    temp_s0 = &temp_v0[idx];
    temp_s0->field_0 = 0;
    
    func_8002E730(idx);
    bzero(temp_s0->field_14, 3840);
    
    temp_s0->field_18 = 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002E730);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002E76C);

void func_8002E7BC()
{
    s_800B5508* temp_v0;

    if (D_800B5480 != 1)
    {
        D_800B5480 = 1;
        
        func_8002E8E4();
        func_80030414();
        
        D_800B55E8.field_0 = 0;
        D_800B55E8.field_4 = 0;
        D_800B55E8.field_8 = 0;
        D_800B55E8.field_C = 0;
        D_800B55E8.field_10 = 0;
        D_800B55E8.field_14 = 0;
        D_800B55E8.field_18 = 0;
        
        temp_v0 = &((s_800B5508*)(&D_800B55E8))->field_18;
        
        temp_v0->field_4 = 0;
        temp_v0->field_8 = 0;
        temp_v0->field_C = 0;
        temp_v0->field_10 = 0;
        temp_v0->field_14 = 0;
    }
}

void func_8002E830()
{
    if (D_800B5480 != 0) 
    {
        D_800B5480 = 0;
        func_80030640();
    }
}

void func_8002E85C()
{
    D_800B5618 = 1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002E86C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002E898);

void func_8002E8D4()
{
    D_800B5618 = 1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002E8E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002E914);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002E94C);

s32 func_8002E990()
{
    return D_800B55FC;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002E9A0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002E9EC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002EA28);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002EA78);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002EABC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002EB88);

void func_8002ECE0(s_800B5508* arg0)
{
    if (func_8003030C(arg0->field_4) != 0)
    {
        arg0->field_14 = 11;
        D_800B5508[arg0->field_4].field_0 = 3;
        
        func_8002E730(arg0->field_4);
        
        D_800B5508[arg0->field_4].field_18 = 15;
    }
    else  
    {
        arg0->field_14 = 10;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002ED7C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002F278);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002F2C4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002F61C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002FB64);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002FBB4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002FC3C);

void SaveGame_CopyWithChecksum(s_ShSaveGameContainer* dest, s_ShSaveGame* src) // 0x8002FCCC
{
    bzero(dest, sizeof(s_ShSaveGameContainer));
    memcpy(&dest->saveGame_0, src, sizeof(s_ShSaveGame));
    SaveGame_ChecksumUpdate(&dest->footer_27C, &dest->saveGame_0, sizeof(s_ShSaveGameContainer));
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002FD5C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002FDB0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8002FE70);

void SaveGame_ChecksumUpdate(s_ShSaveGameFooter* saveFooter, s8* saveData, s32 saveDataLength) // 0x8002FF30
{
    u8 checksum;

    saveFooter->checksum_0[0] = saveFooter->checksum_0[1] = 0;
    saveFooter->magic_2                                   = SAVEGAME_FOOTER_MAGIC;
    checksum                                              = SaveGame_ChecksumGenerate(saveData, saveDataLength);
    saveFooter->checksum_0[0] = saveFooter->checksum_0[1] = checksum;
}

s32 SaveGame_ChecksumValidate(s_ShSaveGameFooter* saveFooter, s8* saveData, s32 saveDataLength) // 0x8002FF74
{
    s32 is_valid = 0;

    if (saveFooter->checksum_0[0] == SaveGame_ChecksumGenerate(saveData, saveDataLength))
    {
        is_valid = saveFooter->magic_2 == SAVEGAME_FOOTER_MAGIC;
    }

    return is_valid;
}

u8 SaveGame_ChecksumGenerate(s8* saveData, s32 saveDataLength) // 0x8002FFD0
{
    u8  checksum = 0;
    int i        = 0;

    for (i = 0; i < saveDataLength;)
    {
        i++;
        checksum ^= *saveData++;
    }

    return checksum;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030000);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800300B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030288);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003030C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030334);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030370);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800303E4);

void func_80030414() 
{
    func_80030444();
    func_8003045C();
    func_80030530();
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030444);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003045C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030530);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030640);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030668);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800306C8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030734);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800307BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030810);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030820);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030884);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030894);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800308A4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800308B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800308C4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800308D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800308E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800309FC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030A0C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030AD8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030C88);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030DC8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80030F7C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800310B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80031184);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80031260);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800314A4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800314EC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800317CC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80031AAC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80031CCC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80031EFC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80031F40);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80032154);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800321EC);

void GFX_ClearRectInterlaced(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b)
{
    setRECT((RECT*)PSX_SCRATCH, x, y, w, h);
    VSync(0);
    ClearImage2((RECT*)PSX_SCRATCH, r, g, b);
    DrawSync(0);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800323C8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", GFX_Init);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", Settings_ScreenXYSet);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", Settings_DispEnvXYSet);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800325A4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800325F8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003260C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003289C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80032904);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", GFX_VSyncCallback);

void GameFS_TitleGfxSeek() 
{
    // Looks for TIM\TITLE_E.TIM.
    Fs_QueueStartSeek(FILE_TIM_TITLE_E_TIM);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", GameFS_TitleGfxLoad);

void GameFS_StreamBinSeek() 
{
    // Looks for VIN\STREAM.BIN.
    Fs_QueueStartSeek(FILE_VIN_STREAM_BIN);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", GameFS_StreamBinLoad);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", GameFS_OptionBinLoad);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", GameFS_SaveLoadBinLoad);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80032CE8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80032D1C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", MainLoop);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", Settings_ScreenAndVolUpdate);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", Settings_RestoreDefaults);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", Settings_RestoreControlDefaults);

void nullsub_800334C8(void) {}

void func_800334D0(void) {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800334D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80033548);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", SysWork_Clear);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", MainLoop_ShouldWarmReset);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", Game_WarmBoot);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", JOY_Init);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", JOY_ReadP1);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", JOY_Update);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", JOY_ControllerDataUpdate);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", ControllerData_AnalogToDigital);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003483C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800348C0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800348E8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80034964);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80034E58);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80034EC8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80034F18);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80034FB8);

void Game_SaveGameInitialize(s8 overlayIdx, s32 difficulty) // 0x800350BC
{
    s32  i;
    s32* var_a2;

    bzero(g_SaveGamePtr, sizeof(s_ShSaveGame));

    g_SaveGamePtr->curMapOverlayIndex_A4 = overlayIdx;

    // -1 = easy, 0 = normal, 1 = hard.
    difficulty = CLAMP(difficulty, -1, 1);

    var_a2 = g_SaveGamePtr->field_B0;

    g_SaveGamePtr->field_260      = (g_SaveGamePtr->field_260 & 0x0FFFFFFF) | (difficulty << 28);
    g_SaveGamePtr->curMapIndex_A9 = 1;

    for (i = 0; i < 45; i++)
    {
        var_a2[44] = NO_VALUE;
        var_a2--;
    }

    Game_SaveGameResetPlayer();
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035178);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", GameFS_MapLoad);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003528C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800352F8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035338);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035560);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003569C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035780);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800358A8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800358DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035924);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003596C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003599C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035AB0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035AC8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035B04);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035B58);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035B98);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035BBC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035BE0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035DB4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035E1C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035E44);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035ED0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80035F4C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800363D0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003640C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80036420);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003647C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80036498);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800364BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003652C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800365B8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80036B5C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80036E48);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003708C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037124);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037154);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037188);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", Chara_PositionUpdateFromParams);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037334);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037388);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800373CC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800378D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037A4C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037C5C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037DC4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037E40);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037E78);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80037F24);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800382B0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800382EC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80038354);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80038A6C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80038B44);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80038BD4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80038F6C);

// SysState_GamePaused handler
void func_800391E8()
{
    D_800A9A68 += D_800A8FEC;
    if (((D_800A9A68 >> 0xB) & 1) == 0)
    {
        GFX_StringPosition(125, 104);
        GFX_StringDraw(D_80025394, 99); // "\x07PAUSED"
    }

    func_80091380();
    func_8004C8DC();

    if (g_SysWork.sysStateStep_C == 0)
    {
        SD_EngineCmd(3);
        g_SysWork.sysStateStep_C++;
    }

    // Debug button combo to bring up save screen from pause screen.
    // DPad-Left + L2 + L1 + LS-Left + RS-Left + L3
    if ((g_ControllerPtr0->btns_held_C == (Pad_BtnL3 | Pad_BtnDpadLeft | Pad_BtnL2 | Pad_BtnL1 | Pad_LSLeft2 | Pad_RSLeft | Pad_LSLeft)) &&
        (g_ControllerPtr0->btns_new_10 & Pad_BtnL3))
    {
        D_800A9A68 = 0;
        SD_EngineCmd(4);
        g_CurMapEventNum = 0;
        SysWork_StateSetNext(SysState_SaveMenu2);
        return;
    }

    if (g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->controllerBinds_0.pause)
    {
        D_800A9A68 = 0;
        SD_EngineCmd(4);
        SysWork_StateSetNext(SysState_Gameplay);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80039344);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003943C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80039568);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800395C0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_800396D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003991C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80039A58);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80039C40);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", AreaLoad_UpdatePlayerPosition);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80039F54);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80039F90);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80039FB8);

void SysWork_SaveGameUpdatePlayer() // 0x8003A120
{
    s_ShSaveGame* save      = g_SaveGamePtr;
    save->curMapEventNum_A8 = g_CurMapEventNum;

    save->playerPosX_244        = g_SysWork.player_4C.character.position_18.vx;
    save->playerPosZ_24C        = g_SysWork.player_4C.character.position_18.vz;
    save->playerRotationYaw_248 = g_SysWork.player_4C.character.rotation_24.vy;
    save->playerHealth_240      = g_SysWork.player_4C.character.health_B0;
}

void func_8003A16C() // 0x8003A16C
{
    if (!(g_SysWork.flags_22A4 & 2))
    {
        // Update saveGame_30C with player info.
        SysWork_SaveGameUpdatePlayer();

        // TODO: What is saveGame_90 used for?
        g_GameWork.saveGame_90 = g_GameWork.saveGame_30C;
    }
}

void SysWork_SaveGameReadPlayer() // 0x8003A1F4
{
    g_SysWork.player_4C.character.position_18.vx = g_SaveGamePtr->playerPosX_244;
    g_SysWork.player_4C.character.position_18.vz = g_SaveGamePtr->playerPosZ_24C;
    g_SysWork.player_4C.character.rotation_24.vy = g_SaveGamePtr->playerRotationYaw_248;
    g_SysWork.player_4C.character.health_B0      = g_SaveGamePtr->playerHealth_240;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003A230);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003A3C8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003A460);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003A4B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003A52C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003AA4C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003AB28);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003B550);

void func_8003B560(void) {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003B568);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003B678);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003B758);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003B7BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003B7FC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003B838);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BA08);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BAC4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BBF4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BC8C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BCF4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BD2C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BD48);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BE28);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BE50);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", GameFS_BgEtcGfxLoad_8003BE6C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", GameFS_BgItemLoad_8003BE9C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BED0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003BF60);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C048);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C0C0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C110);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C1AC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C220);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C2EC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C30C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C368);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C3A0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C3AC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003c850);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C878);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C8F8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003C92C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003CB3C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003CB44);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003CBA4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003CC7C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003CD5C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003CD6C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003CDA0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D01C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D03C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D058);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D160);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D21C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D354);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D3BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D444);

void func_8003D460(void) {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D468);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D550);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D5B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D6A4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D6E0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D7D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D938);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D95C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003D9C8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003DA9C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003DD74);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003DD80);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003DE60);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003DF84);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E08C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E194);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E238);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E388);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E414);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E4A0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E544);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E5E8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", GameFS_FlameGfxLoad_8003E710);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003E740);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EB54);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EBA0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EBF4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003ECBC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003ECE4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003ED08);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003ED64);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003ED74);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EDA8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EDB8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EE30);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EEDC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EF10);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003EF74);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003F08C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003F170);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003F4DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003F654);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003F6F0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003F7E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003F838);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003FCB0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003FD38);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003FE04);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003FEC0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_8003FF2C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80040004);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog", func_80040014);
