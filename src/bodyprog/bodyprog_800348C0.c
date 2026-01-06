#include "game.h"

#include <psyq/libetc.h>
#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/credits.h"
#include "bodyprog/demo.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/gfx/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"
#include "main/mem.h"
#include "main/rng.h"
#include "screens/stream/stream.h"

const s16 rodataPad_800251FC = 0;

void func_800348C0(void) // 0x800348C0
{
    bzero(&g_InitCharaDataAnimInfo[1], 0x48);
}

void GameState_LoadScreen_Update(void) // 0x800348E8
{
    Gfx_LoadingScreenDraw();
    GameFs_MapStartup();

    if (g_SysWork.flags_22A4 & SysFlag2_10)
    {
        D_800BCDD4++;

        if (D_800BCDD4 >= 21)
        {
            g_SysWork.flags_22A4 &= ~SysFlag2_10;

            SD_Call(Sfx_Unk1502);
            SD_Call(Sfx_Unk1501);
        }
    }
}

static inline void Game_StateStepIncrement(void) // TODO: Move to header?
{
    s32 gameStateStep0 = g_GameWork.gameStateStep_598[0];

    g_SysWork.timer_20              = 0;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;
    g_GameWork.gameStateStep_598[0] = gameStateStep0 + 1;
}

void GameFs_MapStartup(void) // 0x80034964
{
    switch (g_GameWork.gameStateStep_598[0])
    {
        case 0:
            g_IntervalVBlanks                  = 1;
            g_GameWork.background2dColor_R_58C = 0;
            g_GameWork.background2dColor_G_58D = 0;
            g_GameWork.background2dColor_B_58E = 0;

            if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_RoomTransition)
            {
                AreaLoad_UpdatePlayerPosition();
                g_GameWork.gameStateStep_598[0] = 7;
            }
            else if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_BootDemo)
            {
                g_DemoLoadAttempCount           = 0;
                g_GameWork.gameStateStep_598[0] = 1;
                g_SysWork.timer_20              = 1;
            }
            else
            {
                g_GameWork.gameStateStep_598[0] = 3;
            }

            SD_Call(19);
            break;

        case 1:
            if (g_SysWork.timer_20 > 1200 && Fs_QueueGetLength() == 0 && !Sd_AudioStreamingCheck())
            {
                Demo_DemoFileSavegameUpdate();
                Game_PlayerInit();

                if (Demo_PlayFileBufferSetup() != 0)
                {
                    GameFs_MapLoad(g_SavegamePtr->mapOverlayId_A4);

                    g_GameWork.gameStateStep_598[0] = 2;
                    g_SysWork.timer_20              = 0;
                    g_GameWork.gameStateStep_598[1] = 0;
                    g_GameWork.gameStateStep_598[2] = 0;
                    break;
                }

                Demo_SequenceAdvance(1);
                Demo_DemoDataRead();

                g_DemoLoadAttempCount++;
                if (g_DemoLoadAttempCount >= 5)
                {
                    g_DemoLoadAttempCount = 0;
                    g_SysWork.timer_20    = 0;
                    break;
                }
            }
            break;

        case 2:
            if (Fs_QueueGetLength() == 0 && !Sd_AudioStreamingCheck())
            {
                Demo_PlayDataRead();

                g_GameWork.gameStateStep_598[0] = 3;
                g_SysWork.timer_20              = 0;
                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;
            }
            break;

        case 3:
            if (Fs_QueueGetLength() == 0)
            {
                g_GameWork.gameStateStep_598[0] = 4;
            }
            break;

        case 4:
            if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_OverlayTransition)
            {
                AreaLoad_UpdatePlayerPosition();
            }
            else if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_LoadSave ||
                     g_SysWork.processFlags_2298 == SysWorkProcessFlag_Continue)
            {
                g_SysWork.loadingScreenIdx_2281 = LoadingScreenId_PlayerRun;
            }

            g_GameWork.gameStateStep_598[0]++;
            break;
        
        case 5:
            Fs_CharaAnimDataAlloc(1, g_MapOverlayHeader.charaGroupIds_248[0], NULL, 0);
            Fs_CharaAnimDataAlloc(2, g_MapOverlayHeader.charaGroupIds_248[1], NULL, 0);
            Fs_CharaAnimDataAlloc(3, g_MapOverlayHeader.charaGroupIds_248[2], NULL, 0);
            WorldGfx_MapInitCharaLoad(&g_MapOverlayHeader);

            g_GameWork.gameStateStep_598[0]++;

        case 6:
            if (Fs_QueueGetLength() == 0)
            {
                g_GameWork.gameStateStep_598[0]++;
            }
            break;

        case 7:
            if (func_80039F90() & EventParamUnkState_0)
            {
                Map_WorldClear();
            }

            Ipd_PlayerChunkInit(&g_MapOverlayHeader, g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz);
            if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_OverlayTransition)
            {
                Game_RadioSoundStop();
            }

            g_GameWork.gameStateStep_598[0]++;

        case 8:
            if (Ipd_ChunkInitCheck() != false)
            {
                Game_StateStepIncrement();
            }
            break;

        case 9:
            if (Bgm_Init() == 0)
            {
                g_GameWork.gameState_594 = GameState_MainLoadScreen;
                Game_StateStepIncrement();
            }
            break;

        case 10:
            if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_BootDemo && !(g_SysWork.flags_22A4 & SysFlag2_1))
            {
                Demo_Start();
                g_SysWork.flags_22A4 |= SysFlag2_1;
            }

            if (func_80039F90() & EventParamUnkState_2 || Sd_AmbientSfxInit() == 0)
            {
                Game_StateStepIncrement();
            }
            break;

        case 11:
            if (g_SysWork.timer_1C >= 60)
            {
                if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_RoomTransition)
                {
                    Game_NpcInit();
                }
                else
                {
                    Game_InGameInit();
                }

                if (g_SysWork.processFlags_2298 <= (u32)SysWorkProcessFlag_OverlayTransition)
                {
                    AreaLoad_TransitionSound();
                }

                func_8002E830(); // Likely close the access to memory card.
                g_GameWork.gameStateStep_598[0]++;
            }
            break;

        case 12:
            if (!Sd_AudioStreamingCheck())
            {
                Game_StateSetNext(GameState_InGame);

                if (func_80039F90() & EventParamUnkState_1)
                {
                    g_GameWork.gameStateStep_598[0] = 1;
                    g_Screen_FadeStatus             = SCREEN_FADE_STATUS(ScreenFadeState_ResetTimestep, IS_SCREEN_FADE_WHITE(g_Screen_FadeStatus));
                }
            }
            break;

        default:
            break;
    }
}

void Gfx_LoadingScreenDraw(void) // 0x80034E58
{
    if (g_SysWork.loadingScreenIdx_2281 != LoadingScreenId_None && g_GameWork.gameStateStep_598[0] < 10)
    {
        ScreenFade_Start(false, true, false);
        g_ScreenFadeTimestep = Q12(0.8f);
        g_MapOverlayHeader.loadingScreenFuncs_18[g_SysWork.loadingScreenIdx_2281]();
    }

    Gfx_2dBackgroundMotionBlur(SyncMode_Wait2);
}

void Game_NpcClear(void) // 0x80034EC8
{
    s32 i;

    g_SysWork.field_228C[0] = 0;
    g_SysWork.npcFlags_2290 = 0;

    bzero(g_SysWork.npcs_1A0, ARRAY_SIZE(g_SysWork.npcs_1A0) * sizeof(s_SubCharacter));

    for (i = 0; i < GROUP_CHARA_COUNT; i++)
    {
        g_SysWork.field_2284[i] = 0;
    }
}

void Game_NpcInit(void) // 0x80034F18
{
    vcSetCameraUseWarp(&g_SysWork.playerWork_4C.player_0.position_18, g_SysWork.cameraAngleY_237A);
    func_8005E70C();

    if (g_SysWork.field_234A)
    {
        g_MapOverlayHeader.func_16C(g_SysWork.field_2349, 127);
        g_MapOverlayHeader.func_168(0, g_SavegamePtr->mapOverlayId_A4, 0);
    }

    Game_NpcClear();
    func_80037F24(false);
    func_80037334();
}

void Game_InGameInit(void) // 0x80034FB8
{
    s32 mapOvlId;

    mapOvlId = g_SavegamePtr->mapOverlayId_A4;

    vcInitCamera(&g_MapOverlayHeader, &g_SysWork.playerWork_4C.player_0.position_18);

    vcSetCameraUseWarp(&g_SysWork.playerWork_4C.player_0.position_18, g_SysWork.cameraAngleY_237A);
    func_80040004(&g_MapOverlayHeader);
    func_80035B58(0);
    WorldGfx_CharaModelProcessAllLoads();
    func_8003EBA0();

    g_MapOverlayHeader.func_168(0, mapOvlId, NO_VALUE);

    Game_NpcClear();

    g_SysWork.npcId_2280 = 5;

    func_8005E650(mapOvlId);
    func_80037124();
    func_8007E8C0();
    func_80037F24(false);
    func_80037334();
    func_8003569C();
    func_8007EBBC();
    GameFs_Tim00TIMLoad();
    Fs_QueueWaitForEmpty();
    GameFs_MapItemsModelLoad(mapOvlId);
}

void Game_SavegameInitialize(s8 overlayId, s32 difficulty) // 0x800350BC
{
    s32  i;
    s32* var;

    bzero(g_SavegamePtr, sizeof(s_Savegame));

    g_SavegamePtr->mapOverlayId_A4 = overlayId;

    difficulty = CLAMP(difficulty, GameDifficulty_Easy, GameDifficulty_Hard);

    var = g_SavegamePtr->field_B0;

    g_SavegamePtr->gameDifficulty_260 = difficulty;
    g_SavegamePtr->paperMapIdx_A9     = PaperMapIdx_OldTown;

    for (i = 0; i < 45; i++)
    {
        var[44] = NO_VALUE;
        var--;
    }

    Game_SavegameResetPlayer();
}

void Game_PlayerInit(void) // 0x80035178
{
    func_8003C048();
    func_8003C110();
    func_8003C0C0();
    Anim_BoneInit(FS_BUFFER_0, g_SysWork.playerBoneCoords_890); // Load player anim file?
    func_8003D938();

    g_SysWork.field_229C = NO_VALUE;

    if ((g_SavegamePtr->itemToggleFlags_AC >> 1) & (1 << 0)) // & `ItemToggleFlag_FlashlightOff`
    {
        Game_TurnFlashlightOff();
    }
    else
    {
        Game_TurnFlashlightOn();
    }

    g_InitCharaDataAnimInfo[0].animBufferSize2_10 = 0x2E630;
    g_InitCharaDataAnimInfo[0].animBufferSize1_C  = 0x2E630;
    func_8007E5AC();
}

void GameFs_MapLoad(s32 mapIdx) // 0x8003521C
{
    #define BASE_FILE_IDX FILE_VIN_MAP0_S00_BIN

    Fs_QueueStartRead(BASE_FILE_IDX + mapIdx, g_OvlDynamic);
    Map_EffectTexturesLoad(mapIdx);
    GameFs_PlayerMapAnimLoad(mapIdx);

    // If the player spawns in the map with a weapon equipped (either because it's a demo
    // or because the player saved the game with a weapon equipped), this and the next function
    // make it appear and allocate its data.
    // @note This code has some special functionallity if player spawna without an equipped weapon.
    if (g_SysWork.processFlags_2298 & (SysWorkProcessFlag_NewGame | SysWorkProcessFlag_LoadSave
                                       | SysWorkProcessFlag_Continue | SysWorkProcessFlag_BootDemo))
    {
        func_8003CD6C(&g_SysWork.playerCombat_38);
    }

    func_800546A8(g_SysWork.playerCombat_38.weaponAttack_F);
}

// ========================================
// CHARACTER ANIMATIONS MEMORY ALLOC
// ========================================

bool func_8003528C(s32 charaDataAnimInfoIdx0, s32 charaDataAnimInfoIdx1) // 0x8003528C
{
    u32                  tempField_8;
    u32                  tempField_4;
    s_CharaAnimDataInfo* animDataInfo0;
    s_CharaAnimDataInfo* animDataInfo1;

    animDataInfo0 = &g_InitCharaDataAnimInfo[charaDataAnimInfoIdx0];
    animDataInfo1 = &g_InitCharaDataAnimInfo[charaDataAnimInfoIdx1];
    tempField_4   = animDataInfo0->animFile0_4;
    tempField_8   = animDataInfo1->animFile1_8;

    if (tempField_4 >= (tempField_8 + animDataInfo1->animBufferSize2_10) ||
        tempField_8 >= (tempField_4 + animDataInfo0->animBufferSize1_C))
    {
        return false;
    }

    return true;
}

s32 Fs_CharaAnimDataInfoIdxGet(e_CharacterId charaId) // 0x800352F8
{
    s32 i;

    for (i = 1; (i < GROUP_CHARA_COUNT); i++)
    {
        if (g_InitCharaDataAnimInfo[i].charaId1_1 == charaId)
        {
            return i;
        }
    }

    return 0;
}

void Fs_CharaAnimDataAlloc(s32 idx, e_CharacterId charaId, s_AnmHeader* animFile, GsCOORDINATE2* coord) // 0x80035338
{
    s32                  i;
    s_AnmHeader*         localAnimFile; // Local pointer required for match.
    s_CharaAnimDataInfo* initAnimDataInfo;
    s_CharaAnimDataInfo* npcAnimDataInfo;

    localAnimFile    = animFile;
    initAnimDataInfo = &g_InitCharaDataAnimInfo[idx];

    if (charaId == Chara_None)
    {
        return;
    }

    // Estimates animation buffer data pointer by adding buffer size and current pointer position.
    for (npcAnimDataInfo = &initAnimDataInfo[-1]; localAnimFile == NULL; npcAnimDataInfo--)
    {
        localAnimFile = npcAnimDataInfo->animFile0_4 + npcAnimDataInfo->animBufferSize1_C;
    }

    // If the target character ID matches with the selected element from `g_InitCharaDataAnimInfo`
    // then it ensures the animation buffer pointer matches with the previously estimated one, but
    // if the estimated pointer is in a position behind of the currently saved one then it moves
    // data to the position of the estimated pointer.
    // 
    // If any of the previous checks fail, values previously assigned at index are cleared. Then, if
    // the character hasn't been loaded in a different `g_InitializedCharaAnimInfo` slot, the
    // animation file is loaded.
    if (initAnimDataInfo->charaId1_1 == charaId)
    {
        if (idx == 1 || localAnimFile == initAnimDataInfo->animFile1_8)
        {
            func_80035560(idx, charaId, initAnimDataInfo->animFile1_8, coord);
            return;
        }
        else if (localAnimFile < initAnimDataInfo->animFile1_8)
        {
            initAnimDataInfo->animFile0_4 = localAnimFile;

            Mem_Move32(localAnimFile, g_InitCharaDataAnimInfo[idx].animFile1_8, g_InitCharaDataAnimInfo[idx].animBufferSize2_10);
            func_80035560(idx, charaId, localAnimFile, coord);
            return;
        }
    }

    initAnimDataInfo->npcCoords_14       = &g_SysWork.npcCoords_FC0[0];
    initAnimDataInfo->charaId1_1         = Chara_None;
    initAnimDataInfo->animFile1_8        = NULL;
    initAnimDataInfo->animBufferSize2_10 = 0;
    initAnimDataInfo->charaId0_0         = charaId;
    initAnimDataInfo->animFile0_4        = localAnimFile;
    initAnimDataInfo->animBufferSize1_C  = Fs_GetFileSectorAlignedSize(CHARA_FILE_INFOS[charaId].animFileIdx);

    i = Fs_CharaAnimDataInfoIdxGet(charaId);

    if (i > 0)
    {
        Mem_Move32(g_InitCharaDataAnimInfo[idx].animFile0_4, g_InitCharaDataAnimInfo[i].animFile1_8, g_InitCharaDataAnimInfo[i].animBufferSize2_10);
        func_80035560(idx, charaId, initAnimDataInfo->animFile0_4, coord);
    }
    else
    {
        Fs_QueueStartReadAnm(idx, charaId, localAnimFile, coord);
    }

    for (i = 1; i < GROUP_CHARA_COUNT; i++)
    {
        if (i != idx && g_InitCharaDataAnimInfo[i].charaId1_1 != Chara_None && func_8003528C(idx, i) != false)
        {
            bzero(&g_InitCharaDataAnimInfo[i], sizeof(s_CharaAnimDataInfo));
        }
    }
}

void func_80035560(s32 idx, e_CharacterId charaId, s_AnmHeader* animFile, GsCOORDINATE2* coord) // 0x80035560
{
    s32                  idx0;
    GsCOORDINATE2*       localCoord;
    s_CharaAnimDataInfo* animDataInfo;

    localCoord   = coord;
    animDataInfo = &g_InitCharaDataAnimInfo[idx];

    if (localCoord == NULL)
    {
        if (idx == 1)
        {
            localCoord = &g_SysWork.npcCoords_FC0[0];
        }
        else if (idx >= 2)
        {
            idx0        = g_InitCharaDataAnimInfo[idx - 1].animFile1_8->boneCount_6;
            localCoord  = g_InitCharaDataAnimInfo[idx - 1].npcCoords_14;
            localCoord += idx0 + 1;

            // Check for end of `g_SysWork.npcCoords_FC0` array.
            if ((&localCoord[animFile->boneCount_6] + 1) >= &g_SysWork.npcCoords_FC0[NPC_BONE_COUNT_MAX])
            {
                localCoord = g_MapOverlayHeader.field_28;
            }
        }
    }

    animDataInfo->charaId1_1         = charaId;
    animDataInfo->animFile1_8        = animFile;
    animDataInfo->animBufferSize2_10 = Fs_GetFileSectorAlignedSize(CHARA_FILE_INFOS[charaId].animFileIdx);
    animDataInfo->npcCoords_14       = localCoord;

    Anim_BoneInit(animFile, localCoord);

    g_CharaAnimInfoIdxs[charaId] = idx;
}

void func_8003569C(void) // 0x8003569C
{
    s32            i;
    GsCOORDINATE2* coord;
    s_AnmHeader*   animFile;

    for (i = 1; i < GROUP_CHARA_COUNT - 1; i++)
    {
        if (g_MapOverlayHeader.charaGroupIds_248[i] != Chara_None)
        {
            coord    = g_InitCharaDataAnimInfo[i].npcCoords_14;
            animFile = g_InitCharaDataAnimInfo[i + 1].animFile1_8;
            coord   += g_InitCharaDataAnimInfo[i].animFile1_8->boneCount_6 + 1;

            // Check for end of `g_SysWork.npcCoords_FC0` array.
            if ((&coord[animFile->boneCount_6] + 1) >= &g_SysWork.npcCoords_FC0[NPC_BONE_COUNT_MAX])
            {
                coord = g_MapOverlayHeader.field_28;
            }

            g_InitCharaDataAnimInfo[i + 1].npcCoords_14 = coord;
            Anim_BoneInit(animFile, coord);
        }
    }
}

// ========================================
// AUDIO HANDLING
// ========================================

s32 Bgm_Init(void) // 0x80035780
{
    if (Sd_AudioStreamingCheck())
    {
        return NO_VALUE;
    }

    if (Fs_QueueGetLength() > 0)
    {
        return NO_VALUE;
    }

    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            func_8003596C();
            g_GameWork.gameStateStep_598[1]++;

        case 1:
            if (Bgm_IsCurrentBgmTargetCheck(g_MapOverlayHeader.field_14) == false)
            {
                g_GameWork.gameStateStep_598[1] += 2;
            }
            else
            {
                SD_Call(18);
                Bgm_MuteBgmLayers();
        
                g_GameWork.gameStateStep_598[1]++;
            }
            break;

        case 2:
            if (func_80045BC8() == 0)
            {
                Bgm_AudioSet(g_MapOverlayHeader.field_14);
                g_GameWork.gameStateStep_598[1]++;
            }
            break;

        default:
            return 0;
    }

    return 1;
}

bool Bgm_IsCurrentBgmTargetCheck(s32 bgmIdx) // 0x800358A8
{
    if (bgmIdx == 0)
    {
        return false;
    }

    if (bgmIdx == 1)
    {
        return false;
    }

    return g_GameWork.bgmIdx_5B2 != bgmIdx;
}

void Bgm_AudioSet(s32 bgmIdx) // 0x800358DC
{
    if (bgmIdx == 0)
    {
        return;
    }

    if (bgmIdx == 1)
    {
        return;
    }

    g_GameWork.bgmIdx_5B2 = bgmIdx;
    SD_Call(g_BgmTaskLoadCmds[bgmIdx]);
}

void Bgm_BgmChannelSet(void) // 0x80035924
{
    if (g_GameWork.bgmIdx_5B2 == 0)
    {
        return;
    }

    if (g_GameWork.bgmIdx_5B2 == 1)
    {
        return;
    }

    SD_Call(g_BgmChannelSetTaskCmds[g_GameWork.bgmIdx_5B2]);
}

void func_8003596C(void) // 0x8003596C
{
    if (g_MapOverlayHeader.field_14 == 1)
    {
        func_80035DB4(true);
    }
}

s32 Sd_AmbientSfxInit(void) // 0x8003599C
{
    if (Sd_AudioStreamingCheck() || Fs_QueueGetLength() > 0)
    {
        return NO_VALUE;
    }

    switch (g_GameWork.gameStateStep_598[1])
    {
        case 0:
            if (g_SavegamePtr->mapOverlayId_A4 == MapOverlayId_MAP2_S00)
            {
                if (Savegame_EventFlagGet(EventFlag_133) || Savegame_EventFlagGet(EventFlag_181))
                {
                    g_MapOverlayHeader.ambientAudioIdx_15 = 11;
                }
                else
                {
                    g_MapOverlayHeader.ambientAudioIdx_15 = 4;
                }
            }

            if (func_80035AB0((s8)g_MapOverlayHeader.ambientAudioIdx_15) != 0)
            {
                SD_Call(17);
                g_GameWork.gameStateStep_598[1]++;
                return 1;
            }
            break;
            
        case 1:
            func_80035AC8((s8)g_MapOverlayHeader.ambientAudioIdx_15);
            g_GameWork.gameStateStep_598[1]++;
            return 1;

        default:
           break;
    }

    return 0;
}

s32 func_80035AB0(s32 arg0) // 0x80035AB0
{
    return g_GameWork.ambientIdx_5B4 != arg0;
}

void func_80035AC8(s32 idx) // 0x80035AC8
{
    g_GameWork.ambientIdx_5B4 = idx;
    SD_Call(g_AmbientVabTaskLoadCmds[idx]);
}

// ========================================
// LOADING SCREEN RELATED
// ========================================

void Math_MatrixTransform(VECTOR3* pos, SVECTOR* rot, GsCOORDINATE2* coord) // 0x80035B04
{
    coord->flg        = false;
    coord->coord.t[0] = Q12_TO_Q8(pos->vx);
    coord->coord.t[1] = Q12_TO_Q8(pos->vy);
    coord->coord.t[2] = Q12_TO_Q8(pos->vz);

    Math_RotMatrixZxyNegGte(rot, (MATRIX*)&coord->coord);
}

void func_80035B58(s32 arg0) // 0x80035B58
{
    func_8003EBF4(&g_MapOverlayHeader);
    g_MapOverlayHeader.func_16C(g_MapOverlayHeader.field_17, g_MapOverlayHeader.field_16);
}

void func_80035B98(void) // 0x80035B98
{
    Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);
}

void Gfx_LoadingScreen_BackgroundTexture(void) // 0x80035BBC
{
    Gfx_BackgroundSpriteDraw(&g_LoadingScreenImg);
}

void Gfx_LoadingScreen_PlayerRun(void) // 0x80035BE0
{
    VECTOR3        camLookAt;
    s32            temp;
    s_Model*       model;
    GsCOORDINATE2* boneCoords;

    boneCoords = g_SysWork.playerBoneCoords_890;
    model      = &g_SysWork.playerWork_4C.player_0.model_0;

    if (g_SysWork.sysState_8 == SysState_Gameplay)
    {
        if (g_SysWork.processFlags_2298 == SysWorkProcessFlag_OverlayTransition)
        {
            AreaLoad_UpdatePlayerPosition();
        }

        vcInitCamera(&g_MapOverlayHeader, &g_SysWork.playerWork_4C.player_0.position_18);
        func_80040004(&g_MapOverlayHeader);

        camLookAt.vy = Q12(-0.6f);
        camLookAt.vx = g_SysWork.playerWork_4C.player_0.position_18.vx;
        camLookAt.vz = g_SysWork.playerWork_4C.player_0.position_18.vz;

        vcUserWatchTarget(&camLookAt, NULL, true);

        camLookAt.vx -= Math_Sin(g_SysWork.playerWork_4C.player_0.rotation_24.vy - FP_ANGLE(22.5f)) * 2;
        temp          = Math_Cos(g_SysWork.playerWork_4C.player_0.rotation_24.vy - FP_ANGLE(22.5f));
        camLookAt.vy  = Q12(-1.0f);
        camLookAt.vz -= temp * 2;

        vcUserCamTarget(&camLookAt, NULL, true);
        func_8003EB54();
        func_8003EEDC(0, 0);

        model->anim_4.flags_2                                 |= AnimFlag_Visible;
        g_SysWork.playerWork_4C.extra_128.disabledAnimBones_18 = 0;
        model->anim_4.flags_2                                 |= AnimFlag_Unlocked | AnimFlag_Visible;
        model->anim_4.time_4                                   = Q12(26.0f);
        g_SysWork.playerWork_4C.player_0.position_18.vy        = Q12(0.2f);

        D_800A998C.status_4 = model->anim_4.status_0;

        Math_MatrixTransform(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, boneCoords);
        g_SysWork.sysState_8++;
    }

    Anim_Update1(model, (s_Skeleton*)FS_BUFFER_0, boneCoords, &D_800A998C);
    vcMoveAndSetCamera(true, false, false, false, false, false, false, false);
    func_8003F170();
    func_8003DA9C(Chara_Harry, boneCoords, 1, g_SysWork.playerWork_4C.player_0.timer_C6, 0);
}

// ========================================
// IN-GAME MUSIC HANDLING RELATED
// ========================================

void func_80035DB4(bool arg0) // 0x80035DB4
{
    D_800BCD5C = false;

    if (g_MapOverlayHeader.func_10) // Checks if function exists.
    {
        g_MapOverlayHeader.func_10(arg0);
        if (arg0 == false && D_800BCD5C == false)
        {
            func_80035F4C(BgmFlag_Unk0, Q12(240.0f), 0);
        }
    }
}

void Bgm_MuteBgmLayers(void) // 0x80035E1C
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(g_SysWork.bgmLayerVolumes_2748); i++)
    {
        g_SysWork.bgmLayerVolumes_2748[i] = 0;
    }
}

bool func_80035E44(void) // 0x80035E44
{
    s32 i;
    u16 val;
    
    for (i = 0; i < (ARRAY_SIZE(g_SysWork.bgmLayerVolumes_2748) - 1); i++)
    {
        if (g_SysWork.bgmLayerVolumes_2748[i] != 0) 
        {
            return false;
        }
    }

    val = func_80045BC8();
    if (val == 0) 
    {
        return true;
    }
    else if (val == 0xFFFF) 
    {
        return false;
    }

    for (i = 1; i < (ARRAY_SIZE(g_SysWork.bgmLayerVolumes_2748) - 1); i++) 
    {
        if (Sd_BgmLayerVolumeGet(i))
        {
            return false;
        }
    }

    return true;
}

void func_80035ED0(void) // 0x80035ED0
{
    s32 i;

    for (i = 1; i < (ARRAY_SIZE(g_SysWork.bgmLayerVolumes_2748) - 1); i++)
    {
        g_SysWork.bgmLayerVolumes_2748[i] = Sd_BgmLayerVolumeGet(i) << 5;
    }

    if (!func_80045BC8())
    {
        g_SysWork.bgmLayerVolumes_2748[0] = Q12(1.0f);
    }

    g_SysWork.bgmLayerVolumes_2748[ARRAY_SIZE(g_SysWork.bgmLayerVolumes_2748) - 1] = 0;
}

void func_80035F4C(s32 flags, q19_12 arg1, s_func_80035F4C* bgmLayerLimitPtr) // 0x80035F4C
{
    s16  temp_v0;
    s32  var_a0;
    s32  var_a2;
    s32  layerVol0;
    s32  layerVol1;
    s32  temp_s2;
    s32  i;
    s32  flagsCpy;
    s32  areBgmLayersActive;
    bool musicIsPlaying;
    s32  var_t0;
    bool cond0;
    s32  temp_s7;
    s16* bgmLaterVolumesPtr;
    u8*  bgmLayerLimitCpy;

    flagsCpy           = flags;
    bgmLayerLimitCpy   = bgmLayerLimitPtr;
    bgmLaterVolumesPtr = g_SysWork.bgmLayerVolumes_2748;

    if (bgmLayerLimitCpy == NULL)
    {
        bgmLayerLimitCpy = g_Sd_BgmLayerLimits;
    }

    if (g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f) || g_SysWork.sysState_8 == SysState_GameOver)
    {
        flagsCpy &= BgmFlag_Unk8;
        flagsCpy |= BgmFlag_Unk0;
        arg1      = Q12(0.2f);
    }
    
    if (!(flagsCpy & BgmFlag_Unk8))
    {
        if (g_RadioPitchState > 0 && g_SavegamePtr->itemToggleFlags_AC & ItemToggleFlag_RadioOn)
        {
            g_SysWork.sysFlags_22A0 |= SysFlag_2;
        }
    }

    if (g_SysWork.sysFlags_22A0 & SysFlag_7)
    {
        flagsCpy                 = BgmFlag_Unk0 | BgmFlag_Unk9;
        g_SysWork.sysFlags_22A0 |= SysFlag_1;
    }

    if (flagsCpy & BgmFlag_Unk0)
    {
        flagsCpy &= BgmFlag_Unk8 | BgmFlag_Unk9;
    }
    else
    {
        flagsCpy ^= BgmFlag_Unk0;
    }

    for (i = 0, temp_s7 = 8; i < 9; i++)
    {
        layerVol0 = bgmLaterVolumesPtr[i];

        if (i == temp_s7) 
        {
            var_t0 = FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime1, 0.25f, Q12_SHIFT);
            if (g_SysWork.sysFlags_22A0 & SysFlag_1)
            {
                var_a0 = Q12(1.0f);
            } 
            else if (g_SysWork.sysFlags_22A0 & SysFlag_2)
            {
                var_a0 = Q12(0.75f);
            } 
            else 
            {
                var_a0 = (g_SysWork.sysFlags_22A0 << 8) & 0x800; // TODO: Weird `SysFlag_3` check.
            }
        } 
        else 
        {
            if ((flagsCpy >> i) & BgmFlag_Unk0)
            {
                var_t0 = FP_MULTIPLY(g_DeltaTime1, arg1, Q12_SHIFT - 1); // @hack Should be multiplied by 2 but doesn't match.
                var_a0 = Q12(1.0f);
            } 
            else
            {
                var_t0 = FP_MULTIPLY(g_DeltaTime1, arg1, Q12_SHIFT);
                var_a0 = Q12(0.0f);
            }
        }

        var_a2 = var_a0 - layerVol0;

        if (layerVol0 != var_a0) 
        {
            if (var_t0 < var_a2) 
            {
                layerVol0 += var_t0;
            } 
            else if (var_a2 >= -var_t0) 
            {
                layerVol0 = var_a0;
            }
            else
            {
                layerVol0 -= var_t0;
            }
        }

        bgmLaterVolumesPtr[i] = layerVol0;
    }

    areBgmLayersActive = 0;
    temp_v0            = Q12(1.0f) - bgmLaterVolumesPtr[8];

    for (i = 0; i < 8; i++)
    {
        layerVol1           = bgmLaterVolumesPtr[i];
        areBgmLayersActive |= layerVol1 != 0;

        if (i == 0) 
        {
            layerVol1 = FP_MULTIPLY_PRECISE(layerVol1, temp_v0, Q12_SHIFT);
        }

        layerVol1 = FP_MULTIPLY_PRECISE(layerVol1, Q12(0.0312f), Q12_SHIFT);
        if (layerVol1 > Q12(0.0312f)) 
        {
            layerVol1 = Q12(0.0312f);
        }

        layerVol1 = (layerVol1 * bgmLayerLimitCpy[i]) >> 7;
        if (layerVol1 > Q12(0.0312f)) 
        {
            layerVol1 = Q12(0.0312f);
        }

        bgmLayerVolumes[i] = layerVol1;
    }

    musicIsPlaying = false;
    temp_s2        = func_80045BC8();

    cond0 = temp_s2;
    cond0 = temp_s2 != 0 && cond0 != 0xFFFF;

    if (areBgmLayersActive) 
    {
        switch (D_800A99A0) 
        {
            case 3:
                Bgm_MuteBgmLayers();

                if (cond0) 
                {
                    D_800A99A0 = 0;
                } 
                else 
                {
                    Bgm_BgmChannelSet();
                    D_800A99A0 = 2;
                }
                break;

            case 2:
                Bgm_MuteBgmLayers();
                D_800A99A0 = 1;
                break;

            case 1:
                if (cond0) 
                {
                    func_80035ED0();
                } 
                else 
                {
                    Bgm_MuteBgmLayers();
                }

                D_800A99A0 = 0;
                break;

            case 0:
                musicIsPlaying = true;
                break;
        }
    } 
    else if (flagsCpy & BgmFlag_Unk9) 
    {
        if (D_800A99A0 != 3) 
        {
            D_800A99A0 = 3;
            SD_Call(18);
        }
    } 
    else if (D_800A99A0 == 0) 
    {
        musicIsPlaying = true;
    }

    if (musicIsPlaying)
    {
        if (cond0) 
        {
            for (i = 0; i < 8; i++)
            {
                Sd_BgmLayerVolumeSet(i, bgmLayerVolumes[i]);
            }
        } 
        else 
        {
            Bgm_MuteBgmLayers();
            D_800A99A0 = 3;
        }
    }

    D_800BCD5C = true;
}

void func_800363D0(void) // 0x800363D0
{
    g_RadioPitchState        = 0;
    g_SysWork.sysFlags_22A0 |= SysFlag_3;
    func_80035DB4(false);
}

void func_8003640C(s32 arg0) // 0x8003640C
{
    if (arg0 != 0)
    {
        g_MapOverlayHeader.field_14 = arg0;
    }
}

// ========================================
// UNKNOWN
// ========================================

void Savegame_MapRoomIdxSet(void) // 0x80036420
{
    s32 x;
    s32 z;
    s8  newMapRoomIdx;

    x = g_SysWork.playerWork_4C.player_0.position_18.vx;
    z = g_SysWork.playerWork_4C.player_0.position_18.vz;

    // Set map room index based on current player position.
    if (g_MapOverlayHeader.getMapRoomIdxFunc_4 == NULL)
    {
        newMapRoomIdx = 0;
    } 
    else 
    {
        newMapRoomIdx = g_MapOverlayHeader.getMapRoomIdxFunc_4(x, z);
    }
    g_SavegamePtr->mapRoomIdx_A5 = newMapRoomIdx;
}

s32 func_8003647C(void) // 0x8003647C
{
    return g_SavegamePtr->mapRoomIdx_A5 > g_MapOverlayHeader.field_8;
}

s32 func_80036498(void) // 80036498
{
    return !(g_SavegamePtr->mapRoomIdx_A5 > g_MapOverlayHeader.field_8);
}

u32 func_800364BC(void) // 0x800364BC
{
    u32 var0;
    u32 var1;

    D_800BCD58 += g_DeltaTime1 * (Q12(64.0f) + 1);

    var0  = 0x40000;
    var0 += Math_Sin(D_800BCD58 >> 18) * 8;
    var1  = Math_Sin((D_800BCD58 & 0xFFFF) / 16) * 32;
    return FP_FROM(var0 + var1, Q12_SHIFT);
}

// `RECT`s?
const char rodataPad_80025234[] = { 0, 177, 58, 204, 0, 0, 0, 0 }; // Could this indicate file split nearby?

void func_8003652C(void) // 0x8003652C
{
    RECT rect;

    u32 VALS[] = {
        0xFFFF0000, 0xBBEEE318, 0xFFEC9304, 0x83FFE30C,
        0x1F8318,   0x90840018, 0x90808080, 0x80048084
    };

    rect.x = 304;
    rect.y = 510;
    rect.w = 16;
    rect.h = 1;

    LoadImage(&rect, VALS);
}

s32 Gfx_MapMsg_Draw(s32 mapMsgIdx) // 0x800365B8
{
    #define MSG_TIMER_MAX   (Q12(524288.0f) - 1)
    #define FINISH_CUTSCENE 0xFF
    #define FINISH_MAP_MSG  0xFF

    s32  temp_s1;
    bool hasInput;
    s32  temp;

    // Check for user input.
    hasInput = false;
    if ((g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                          g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)) ||
        (g_Controller0->btnsHeld_C & g_GameWorkPtr->config_0.controllerConfig_0.skip_4))
    {
        hasInput = true;
    }

    g_SysWork.playerWork_4C.player_0.properties_E4.player.gasWeaponPowerTimer_114 = Q12(0.0f);
    func_8004C564(g_SysWork.playerCombat_38.weaponAttack_F, WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap));

    if (g_MapMsg_MainIdx != mapMsgIdx)
    {
        g_SysWork.isMgsStringSet_18 = 0;
    }

    switch (g_SysWork.isMgsStringSet_18)
    {
        case 0:
            g_SysWork.mapMsgTimer_234C         = NO_VALUE;
            g_MapMsg_Select.maxIdx_0           = NO_VALUE;
            g_MapMsg_Select.selectedEntryIdx_1 = 0;
            g_MapMsg_AudioLoadBlock            = 0;
            g_MapMsg_CurrentIdx                = mapMsgIdx;
            g_MapMsg_StateMachineIdx1          = 0;
            g_MapMsg_StateMachineIdx2          = 0;
            g_MapMsg_MainIdx                   = mapMsgIdx;
            g_MapMsg_DisplayLength             = 0;
            g_MapMsg_DisplayInc                = 2; // Advance 2 glyphs at a time.

            Gfx_MapMsg_DefaultStringInfoSet();
            Gfx_MapMsg_CalculateWidths(g_MapMsg_CurrentIdx);

            D_800BCD74 = 1;
            g_SysWork.isMgsStringSet_18++;
            return MapMsgState_Finish;

        case 1:
            if (g_SysWork.sysFlags_22A0 & SysFlag_5)
            {
                if (Sd_AudioStreamingCheck() == 4)
                {
                    D_800BCD74 = 0;
                    break;
                }

                if (D_800BCD74 != 0)
                {
                    break;
                }
            }
            else
            {
                D_800BCD74 = 0;
            }

            Gfx_StringSetColor(StringColorId_White);
            Gfx_StringSetPosition(40, 160);

            g_MapMsg_DisplayLength += g_MapMsg_DisplayInc;
            g_MapMsg_DisplayLength  = CLAMP(g_MapMsg_DisplayLength, 0, MAP_MESSAGE_DISPLAY_ALL_LENGTH);

            if (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer_234C > 0)
            {
                g_SysWork.mapMsgTimer_234C -= g_DeltaTime1;
                g_SysWork.mapMsgTimer_234C  = CLAMP(g_SysWork.mapMsgTimer_234C, Q12(0.0f), MSG_TIMER_MAX);
            }

            temp_s1 = g_MapMsg_StateMachineIdx1;
            if (temp_s1 == NO_VALUE)
            {
                if (g_MapMsg_AudioLoadBlock == 0)
                {
                    Game_TimerUpdate();
                }

                temp = g_MapMsg_StateMachineIdx2;
                if (temp == temp_s1)
                {
                    if (g_MapMsg_Select.maxIdx_0 == temp)
                    {
                        if (!((g_MapMsg_AudioLoadBlock & (1 << 0)) || !hasInput) || 
                            (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer_234C == 0))
                        {
                            g_MapMsg_StateMachineIdx2 = FINISH_MAP_MSG;

                            if (g_SysWork.sysFlags_22A0 & SysFlag_5)
                            {
                                SD_Call(19);
                            }
                            break;
                        }
                    } 
                    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)
                    {
                        g_MapMsg_Select.maxIdx_0           = temp;
                        g_MapMsg_Select.selectedEntryIdx_1 = g_MapMsg_SelectCancelIdx;

                        Sd_PlaySfx(Sfx_MenuCancel, 0, Q8_CLAMPED(0.25f));

                        if (g_SysWork.silentYesSelection_2350_4)
                        {
                            g_SysWork.silentYesSelection_2350_4 = false;
                        }

                        g_MapMsg_StateMachineIdx2 = FINISH_MAP_MSG;
                        break;
                    }
                    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.enter_0)
                    {
                        g_MapMsg_Select.maxIdx_0 = temp;

                        if ((u8)g_MapMsg_Select.selectedEntryIdx_1 == (s8)g_MapMsg_SelectCancelIdx)
                        {
                            Sd_PlaySfx(Sfx_MenuCancel, 0, Q8_CLAMPED(0.25f));
                        }
                        else if (!g_SysWork.silentYesSelection_2350_4)
                        {
                            Sd_PlaySfx(Sfx_MenuConfirm, 0, Q8_CLAMPED(0.25f));
                        }

                        if (g_SysWork.silentYesSelection_2350_4)
                        {
                            g_SysWork.silentYesSelection_2350_4 = false;
                        }

                        g_MapMsg_StateMachineIdx2 = FINISH_MAP_MSG;
                        break;
                    }
                }
                else if ((!(g_MapMsg_AudioLoadBlock & (1 << 0)) && hasInput && g_MapMsg_Select.maxIdx_0 != 0) ||
                         (g_MapMsg_AudioLoadBlock != 0 && g_SysWork.mapMsgTimer_234C == 0))
                {
                    if (g_MapMsg_Select.maxIdx_0 != NO_VALUE)
                    {
                        g_MapMsg_Select.maxIdx_0  = NO_VALUE;
                        g_MapMsg_StateMachineIdx2 = FINISH_MAP_MSG;
                        break;
                    }

                    g_MapMsg_CurrentIdx++;
                    g_SysWork.mapMsgTimer_234C = g_MapMsg_Select.maxIdx_0;

                    Gfx_MapMsg_CalculateWidths(g_MapMsg_CurrentIdx);

                    g_MapMsg_DisplayLength    = 0;
                    g_MapMsg_StateMachineIdx1 = 0;

                    if (g_MapMsg_AudioLoadBlock == MapMsgAudioLoadBlock_J2)
                    {
                        D_800BCD74 = 0;
                        return MapMsgState_Idle;
                    }

                    if (g_SysWork.sysFlags_22A0 & SysFlag_5)
                    {
                        SD_Call(19);
                    }

                    D_800BCD74 = 1;
                    return MapMsgState_Finish;
                }
            }
            else
            {
                if (hasInput)
                {
                    g_MapMsg_DisplayLength = MAP_MESSAGE_DISPLAY_ALL_LENGTH;
                }
            }

            g_MapMsg_StateMachineIdx1 = 0;
            g_MapMsg_StateMachineIdx2 = Gfx_MapMsg_SelectionUpdate(g_MapMsg_CurrentIdx, &g_MapMsg_DisplayLength);

            if (g_MapMsg_StateMachineIdx2 != 0 && g_MapMsg_StateMachineIdx2 < MapMsgCode_Select4)
            {
                g_MapMsg_StateMachineIdx1 = NO_VALUE;
            }
    }

    if (g_MapMsg_StateMachineIdx2 != FINISH_MAP_MSG)
    {
        return MapMsgState_Idle;
    }

    g_SysWork.isMgsStringSet_18            = 0;
    g_SysWork.enableHighResGlyphs_2350_0 = false;
    g_MapMsg_DisplayLength               = 0;

    if (g_SysWork.sysFlags_22A0 & SysFlag_5)
    {
        D_800BCD74 = 1;
    }

    return g_MapMsg_Select.selectedEntryIdx_1 + 1;
}

s32 Gfx_MapMsg_SelectionUpdate(u8 mapMsgIdx, s32* arg1) // 0x80036B5C
{
    #define STRING_LINE_OFFSET 16

    s32 i;
    s32 mapMsgCode;

    mapMsgCode = Gfx_MapMsg_StringDraw(g_MapOverlayHeader.mapMessages_30[mapMsgIdx], *arg1);

    g_MapMsg_SelectFlashTimer += g_DeltaTime1;
    if (g_MapMsg_SelectFlashTimer >= Q12(0.5f))
    {
        g_MapMsg_SelectFlashTimer -= Q12(0.5f);
    }

    switch (mapMsgCode)
    {
        case NO_VALUE:
        case MapMsgCode_None:
            g_MapMsg_SelectFlashTimer = Q12(0.0f);
            break;

        case MapMsgCode_Select2:
        case MapMsgCode_Select3:
        case MapMsgCode_Select4:
            g_MapMsg_Select.maxIdx_0  = 1;
            g_MapMsg_SelectCancelIdx = (mapMsgCode == 3) ? 2 : 1;

            if (mapMsgCode == MapMsgCode_Select4)
            {
                // Shows selection prompt with map messages at indices 0 and 1.
                // All maps have "Yes" and "No" as messages 0 and 1, respectively.
                for (i = 0; i < 2; i++)
                {
                    if ((u8)g_MapMsg_Select.selectedEntryIdx_1 == i)
                    {
                        Gfx_StringSetColor(((g_MapMsg_SelectFlashTimer >> 10) * 3) + 4);
                    }
                    else
                    {
                        Gfx_StringSetColor(StringColorId_White);
                    }

                    Gfx_StringSetPosition(32, (STRING_LINE_OFFSET * i) + 98);
                    Gfx_StringDraw(g_MapOverlayHeader.mapMessages_30[i], MAP_MESSAGE_DISPLAY_ALL_LENGTH);
                }

                mapMsgCode = 2;
            }
            else
            {
                // Shows selection prompt with 2 or 3 map messages from current index + 1/2/3.
                // Requires prompt options to be arranged sequentially in the map message array, e.g.
                // `[idx]`:     "Select one of 3 options. ~S3"
                // `[idx + 1]`: "Option 1"
                // `[idx + 2]`: "Option 2"
                // `[idx + 3]`: "Option 3"
                for (i = 0; i < mapMsgCode; i++)
                {
                    if ((u8)g_MapMsg_Select.selectedEntryIdx_1 == i)
                    {
                        Gfx_StringSetColor(((g_MapMsg_SelectFlashTimer >> 10) * 3) + 4);
                    }
                    else
                    {
                        Gfx_StringSetColor(StringColorId_White);
                    }

                    Gfx_StringSetPosition(32, (STRING_LINE_OFFSET * i) + 96);
                    Gfx_StringDraw(g_MapOverlayHeader.mapMessages_30[(mapMsgIdx + i) + 1], MAP_MESSAGE_DISPLAY_ALL_LENGTH);
                }
            }

            if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickUp &&
                (u8)g_MapMsg_Select.selectedEntryIdx_1 != 0)
            {
                g_MapMsg_SelectFlashTimer = Q12(0.0f);
                g_MapMsg_Select.selectedEntryIdx_1--;

                Sd_PlaySfx(Sfx_MenuMove, 0, Q8_CLAMPED(0.25f));
            }

            if (g_Controller0->btnsClicked_10 & ControllerFlag_LStickDown &&
                (u8)g_MapMsg_Select.selectedEntryIdx_1 != (mapMsgCode - 1))
            {
                g_MapMsg_SelectFlashTimer = Q12(0.0f);
                g_MapMsg_Select.selectedEntryIdx_1++;

                Sd_PlaySfx(Sfx_MenuMove, 0, Q8_CLAMPED(0.25f));
            }

            mapMsgCode = NO_VALUE;
            break;

        case MapMsgCode_DisplayAll:
            *arg1 = MAP_MESSAGE_DISPLAY_ALL_LENGTH;
            break;
    }

    return mapMsgCode;
}

const s32 RodataPad_800252B8 = 0;

/** @brief SFX pairs.
 * 
 * @note Used when loading areas. Maybe facilitates things like the
 * opening and closing door SFX when the player moves between rooms. */
s_AreaLoadSfx const SfxPairs[25] = {
    { Sfx_Base, Sfx_Base },
    { Sfx_DoorOpen0, Sfx_DoorClose0 },
    { Sfx_Unk1323, Sfx_Unk1324 },
    { Sfx_Unk1418, Sfx_Base },
    { Sfx_Unk1354, Sfx_Base },
    { Sfx_Unk1387, Sfx_Base },
    { Sfx_Unk1391, Sfx_Base },
    { Sfx_Unk1521, Sfx_Base },
    { Sfx_Unk1458, Sfx_Unk1459 },
    { Sfx_Unk1604, Sfx_Unk1605 },
    { Sfx_Unk1609, Sfx_Unk1610 },
    { Sfx_Unk1396, Sfx_Unk1397 },
    { Sfx_Unk1336, Sfx_Unk1337 },
    { Sfx_Unk1338, Sfx_Unk1339 },
    { Sfx_Unk1340, Sfx_Unk1341 },
    { Sfx_Unk1601, Sfx_Unk1602 },
    { Sfx_Unk1490, Sfx_Unk1491 },
    { Sfx_Unk1431, Sfx_Unk1432 },
    { Sfx_Unk1398, Sfx_Unk1399 },
    { Sfx_Unk1504, Sfx_Unk1505 },
    { Sfx_DoorOpen0, Sfx_Base },
    { Sfx_Unk1323, Sfx_Base },
    { Sfx_Base, Sfx_Unk1324 },
    { Sfx_Unk1351, Sfx_Unk1352 },
    { Sfx_Unk1487, Sfx_Base }
};

// These are referenced by pointers at `0x800A99E8`, which are then used by `func_800D3EAC`.
// Maybe meant to be separate .c file with .h externs.
const char g_80025320[] = "SHOT_NEA";
const char g_8002532C[] = "SHELL_NE";
const char g_80025338[] = "BULLET_N";
const char g_80025344[] = "AMPULE_N";
const char g_80025350[] = "DRINK_NE";
const char g_8002535C[] = "AIDKIT_N";
const char g_80025368[] = "PAD_NEAR";

void func_80036E48(u16* arg0, s16* arg1) // 0x80036E48
{
    u16  sp10[4];
    u8   sp18[16];
    u8   sp28[12];
    s32  temp_a0;
    s32  temp_v0_2;
    s32  var_a2;
    s32  i;
    u8   var_t4;
    s32  var_v0;
    u16  temp_v0;
    u16  var_a3;
    s16* var_t2;
    u16* var_t7;

    var_t2 = arg1;
    var_t4 = 0;
    var_t7 = arg0;

    for (i = 0; i < 15;)
    {
        temp_v0 = *var_t7;

        for (var_a2 = 0; var_a2 < 15; var_a2++)
        {
            if ((((temp_v0 >> 8) | ((temp_v0 & 0xFF) << 8)) >> (0xF - var_a2)) & 1)
            {
                sp18[var_a2] = 1;
            }
            else
            {
                sp18[var_a2] = 0;
            }
        }

        sp18[15] = 0;
        sp28[0]  = sp18[0];
        sp28[1]  = sp18[1] | sp18[2];
        sp28[2]  = sp18[3];
        sp28[3]  = sp18[4];
        sp28[4]  = sp18[5] | sp18[6];
        sp28[5]  = sp18[7];
        sp28[6]  = sp18[8] | sp18[9];
        sp28[7]  = sp18[10];
        sp28[8]  = sp18[11];
        sp28[9]  = sp18[12] | sp18[13];
        var_v0   = 2;
        sp28[10] = sp18[14];
        sp28[11] = 0;

        for (var_a3 = 0, var_a2 = 0; var_a2 < 12; var_a2++)
        {
            var_v0  = 2;
            temp_a0 = (var_a2 & 0x3) * 4;

            if (sp28[var_a2] != 0)
            {
                var_a3 |= var_v0 << temp_a0;
            }
            else
            {
                if (var_a2 > 0 && sp28[var_a2 - 1] != 0)
                {
                    var_a3 |= 11 << temp_a0;
                }

                if (i > 0)
                {
                    if (var_a2 != 0 && ((sp10[var_a2 >> 2] >> temp_a0) & 0xF) == 11 && var_t4)
                    {
                        var_a3 |= 11 << temp_a0;
                    }

                    temp_v0_2 = (sp10[var_a2 >> 2] >> temp_a0) & 0xF;

                    if (temp_v0_2 > 0 && temp_v0_2 != 11)
                    {
                        var_a3 |= 11 << temp_a0;
                        var_t4 = 1;
                    }
                    else
                    {
                        var_t4 = 0;
                    }
                }
            }

            if ((var_a2 & 3) == 3)
            {
                sp10[var_a2 >> 2] = var_a3;
                *var_t2           = var_a3;
                var_t2++;
                var_a3 = 0;
            }
        }

        do { i++; } while (0); // @hack Required for match.

        var_t7++;
        var_t2 += (D_800C3920 - 1) * 3;
    }

    func_8003708C(var_t2, sp10);
}

void func_8003708C(s16* ptr0, u16* ptr1) // 0x8003708C
{
    s32 var0;
    s16 var1;
    s32 var3;
    s32 shift;
    s32 i;

    var0 = 0;
    var1 = 0;

    for (i = 0; i < 12; i++)
    {
        shift = (i & 3) * 4;
        var3  = (*ptr1 >> shift) & 0xF;
        if (i != 0 && var3 == 11 && var0 != 0)
        {
            var1 |= 11 << shift;
        }

        var0 = 0;
        if (var3 != 0 && var3 != 11)
        {
            var1 |= 11 << shift;
            var0  = 1;
        }

        if ((i & 0x3) == 3 || i == 12)
        {
            ptr1++;
            *ptr0++ = var1;
            var1    = 0;
        }
    } 
}

void func_80037124(void) // 0x80037124
{
    g_MapMsg_Select.maxIdx_0 = NO_VALUE;
    func_8003652C();
    DrawSync(SyncMode_Wait);
}

void func_80037154(void) // 0x80037154
{
    s32 i;

    for (i = 0; i < 2; i++)
    {
        D_800BCDA8[i].field_2 = NO_VALUE;
        D_800BCDA8[i].field_1 = NO_VALUE;
        D_800BCDA8[i].field_3 = 0;
    }
}

void Game_RadioSoundStop(void) // 0x80037188
{
    s32 i;

    for (i = 0; i < 2; i++)
    {
        D_800BCDA8[i].field_0 = NO_VALUE;
    }

    for (i = 0; i < 2; i++)
    {
        Sd_SfxStop(Sfx_RadioInterferenceLoop + i);
    }
}

void Chara_PositionUpdateFromParams(s_MapPoint2d* mapPoint) // 0x800371E8
{
    s32 rotY;

    rotY = FP_ANGLE_FROM_PACKED(mapPoint->data.areaLoad.rotationY_4_16);
    Math_SVectorSet(&g_SysWork.playerWork_4C.player_0.rotation_24, FP_ANGLE(0.0f), rotY, FP_ANGLE(0.0f));

    g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(0.0f);
    g_SysWork.playerWork_4C.player_0.position_18.vx = mapPoint->positionX_0;
    g_SysWork.playerWork_4C.player_0.position_18.vz = mapPoint->positionZ_8;

    if (mapPoint->data.areaLoad.field_4_24 >= 2)
    {
        g_SysWork.playerWork_4C.player_0.position_18.vx += FP_MULTIPLY_FLOAT_PRECISE(Math_Sin(rotY), 0.4f, Q12_SHIFT);
        g_SysWork.playerWork_4C.player_0.position_18.vz += FP_MULTIPLY_FLOAT_PRECISE(Math_Cos(rotY), 0.4f, Q12_SHIFT);
    }

    g_SysWork.loadingScreenIdx_2281 = mapPoint->data.areaLoad.loadingScreenId_4_9;

    if (mapPoint->data.areaLoad.mapIdx_4_0 == 24) // TODO: Demagic 24.
    {
        g_SavegamePtr->paperMapIdx_A9 = PaperMapIdx_OtherPlaces;
    }
    else if (mapPoint->data.areaLoad.mapIdx_4_0 != PaperMapIdx_OtherPlaces)
    {
        g_SavegamePtr->paperMapIdx_A9 = mapPoint->data.areaLoad.mapIdx_4_0;
    }

    g_SysWork.cameraAngleY_237A = rotY;

    func_8007E9C4();
    Savegame_MapRoomIdxSet();
}

void func_80037334(void) // 0x80037334
{
    s_Collision coll;

    if (g_MapOverlayHeader.worldObjectsUpdate_40 != 0)
    {
        g_MapOverlayHeader.worldObjectsUpdate_40();
    }

    Collision_Get(&coll, g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz);
    g_SysWork.playerWork_4C.player_0.position_18.vy = coll.groundHeight_0;
}

void Event_Update(bool disableButtonEvents) // 0x800373CC
{
    s_MapPoint2d* mapPoint;
    s_EventParam* mapEvent;
    q19_12        pointPosX;
    q19_12        pointPosZ;
    q19_12        pointRadiusX;
    q19_12        pointRadiusZ;
    s32           i;

    void Event_ItemTriggersClear() // 0x80037388
    {
        s32 i;

        for (i = 0; i < 5; i++)
        {
            g_ItemTriggerItemIds[i] = NO_VALUE;
            g_ItemTriggerEvents[i]  = NULL;
        }
    }

    // `lastUsedItem_28` is set by `Inventory_ItemUse` when player uses an item that matches one of the item trigger events.
    // If it's set, find its index in `g_ItemTriggerItemIds` and use that to get the corresponding `s_EventParam` from `g_ItemTriggerEvents`.
    // After processing, the field is cleared and item trigger IDs are reset.
    // (Multi-item events likely repopulate the trigger IDs below based on whichever events are still active?)
    if (g_SysWork.playerWork_4C.extra_128.lastUsedItem_28 != InventoryItemId_Unequipped)
    {
        for (i = 0; g_SysWork.playerWork_4C.extra_128.lastUsedItem_28 != g_ItemTriggerItemIds[i]; i++);

        g_MapEventParam        = g_ItemTriggerEvents[i];
        g_MapEventLastUsedItem = g_SysWork.playerWork_4C.extra_128.lastUsedItem_28;
        g_MapEventSysState     = g_MapEventParam->sysState_8_0;
        g_MapEventIdx          = g_MapEventParam->pointOfInterestIdx_8_5;

        g_SysWork.playerWork_4C.extra_128.lastUsedItem_28 = InventoryItemId_Unequipped;
        Event_ItemTriggersClear();
        return;
    }

    Event_ItemTriggersClear();

    g_MapEventLastUsedItem = InventoryItemId_Unequipped;

    mapEvent = &g_MapOverlayHeader.mapEvents_24[-1];

    while (true)
    {
        s32 disabledEventFlag_temp;
        s16 disabledEventFlag;
        s16 requiredEventFlag;

        mapEvent++;

        if (mapEvent->triggerType_4_0 == NO_VALUE)
        {
            break;
        }

        // `requiredEventFlag`: if set, EventFlag that must be set for event to trigger?
        // `disabledEventFlag`: if set, EventFlag that must not be set for event to trigger?
        // TODO: Can this s32 temp be removed? Trying to set `disabledEventFlag` directly results in `lhu` instead?
        requiredEventFlag      = mapEvent->requiredEventFlag_0;
        disabledEventFlag_temp = mapEvent->disabledEventFlag_2;
        disabledEventFlag      = disabledEventFlag_temp;

        if (requiredEventFlag != 0 && !Savegame_EventFlagGet(requiredEventFlag))
        {
            continue;
        }

        if (disabledEventFlag != 0 && Savegame_EventFlagGet(disabledEventFlag) &&
            (disabledEventFlag < 867 || mapEvent->activationType_4_4 == TriggerActivationType_Exclusive || mapEvent->sysState_8_0 == SysState_EventSetFlag))
        {
            continue;
        }

        // `TriggerType_None` skips any trigger/activation check and always executes.
        // Maybe used for map-load events, and events that should run every frame?
        // Returns before processing other events until flag checks above disable it.
        if (mapEvent->triggerType_4_0 == TriggerType_None)
        {
            g_MapEventParam    = mapEvent;
            g_MapEventSysState = mapEvent->sysState_8_0;
            g_MapEventIdx      = mapEvent->pointOfInterestIdx_8_5;
            return;
        }

        // `TriggerActivationType_Button`: Only continue processing event when action button is pressed and `func_8007F2AC` returns false (maybe some IsBusy function?)
        if (mapEvent->activationType_4_4 == TriggerActivationType_Button &&
            (!(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.action_6) || disableButtonEvents || func_8007F2AC()))
        {
            continue;
        }

        // TODO: This uses `field_5` as the map point index, but there is also a separate `pointOfInterestIdx_8_5` field.
        mapPoint = &g_MapOverlayHeader.mapPointsOfInterest_1C[mapEvent->field_5];

        switch (mapEvent->triggerType_4_0)
        {
            case TriggerType_TouchAabb:
                pointPosX    = mapPoint->positionX_0;
                pointPosZ    = mapPoint->positionZ_8;
                pointRadiusX = mapPoint->data.touchAabb.radiusX_4_16 * Q12(0.25f);
                pointRadiusZ = mapPoint->data.touchAabb.radiusZ_4_24 * Q12(0.25f);

                if (ABS(g_SysWork.playerWork_4C.player_0.position_18.vx - pointPosX) > pointRadiusX)
                {
                    continue;
                }

                if (ABS(g_SysWork.playerWork_4C.player_0.position_18.vz - pointPosZ) > pointRadiusZ)
                {
                    continue;
                }
                break;

            case TriggerType_TouchFacing:
                if (!Event_CheckTouchFacing(mapPoint))
                {
                    continue;
                }
                break;

            case TriggerType_TouchObbFacing:
                if (!Event_CheckTouchObbFacing(mapPoint))
                {
                    continue;
                }
                break;

            case TriggerType_TouchObb:
                if (!Event_CheckTouchObb(mapPoint))
                {
                    continue;
                }
                break;
        }

        // Trigger checks have passed. Check activation type.

        // `TriggerActivationType_Exclusive`: Skip processing any other events if this event is active.
        if (mapEvent->activationType_4_4 == TriggerActivationType_Exclusive && mapEvent == g_MapEventParam)
        {
            g_MapEventSysState = SysState_Invalid;
            return;
        }

        // `TriggerActivationType_Item`: When trigger check has passed (player is in the trigger area).
        // Required item ID for event is stored into `g_ItemTriggerItemIds` and event pointer at `g_ItemTriggerEvents`
        // Once player uses an item in the inventory screen, it compares the ID against the ones stored at `g_ItemTriggerItemIds`.
        // If used item ID matches one that event has requested, `extra_128.lastUsedItem_28` gets set to the item ID.
        // At the start of this function, if `extra_128.lastUsedItem_28` is set, it will locate the `s_EventParam` for it from `g_ItemTriggerEvents` and run the event.
        if (mapEvent->activationType_4_4 == TriggerActivationType_Item)
        {
            for (i = 0; g_ItemTriggerItemIds[i] != NO_VALUE; i++);

            g_ItemTriggerEvents[i]  = mapEvent;
            g_ItemTriggerItemIds[i] = mapEvent->requiredItemId_6;
            continue;
        }

        // `TriggerActivationType_Button`: Only allow button activated events when area is lit up?
        if (mapEvent->activationType_4_4 == TriggerActivationType_Button)
        {
            if ((g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 2) && !g_SysWork.field_2388.isFlashlightOn_15 &&
                ((g_SysWork.field_2388.field_1C[0].field_0.field_0.s_field_0.field_0 & 1) || (g_SysWork.field_2388.field_1C[1].field_0.field_0.s_field_0.field_0 & 1)))
            {
                if (mapEvent->sysState_8_0 != SysState_LoadOverlay &&
                    (mapEvent->sysState_8_0 != SysState_LoadRoom && mapEvent->pointOfInterestIdx_8_5 > 1))
                {
                    continue;
                }
            }
        }

        // Trigger and activation checks passed. Run event.

        // If this is `EventSetFlag`, handle setting the flag here and skip running it.
        // (Same as `SysState_EventSetFlag_Update`.)
        if (mapEvent->sysState_8_0 == SysState_EventSetFlag)
        {
            Savegame_EventFlagSetAlt(mapEvent->disabledEventFlag_2);
            break;
        }

        // Set `g_MapEventSysState` to the SysState needed for the event to be ran on next tick (`SysState_ReadMessage`/`SaveMenu`/`EventCallFunc`/etc.).
        g_MapEventParam    = mapEvent;
        g_MapEventSysState = mapEvent->sysState_8_0;
        g_MapEventIdx      = mapEvent->pointOfInterestIdx_8_5;
        return;
    }

    g_MapEventParam    = NULL;
    g_MapEventSysState = SysState_Invalid;
    g_MapEventIdx      = 0;
}

bool Event_CheckTouchFacing(s_MapPoint2d* mapPoint) // 0x800378D4
{
    q19_12 deltaX;
    q19_12 deltaZ;
    q3_12  rotY;
    q19_12 deltaRotY;

    if (g_MainLoop_FrameCount > D_800A9A20)
    {
        rotY       = g_SysWork.playerWork_4C.player_0.rotation_24.vy;
        D_800A9A24 = g_SysWork.playerWork_4C.player_0.position_18.vx - (Math_Sin(rotY) >> 3); // `/ 8`.
        D_800A9A28 = g_SysWork.playerWork_4C.player_0.position_18.vz - (Math_Cos(rotY) >> 3); // `/ 8`.
        D_800A9A20 = g_MainLoop_FrameCount;
    }

    deltaX = mapPoint->positionX_0 - D_800A9A24;
    if (ABS(deltaX) > Q12(0.8f))
    {
        return false;
    }

    deltaZ = mapPoint->positionZ_8 - D_800A9A28;
    if (ABS(deltaZ) > Q12(0.8f))
    {
        return false;
    }

    if ((SQUARE(deltaX) + SQUARE(deltaZ)) > SQUARE(Q12(0.8f)))
    {
        return false;
    }

    deltaRotY = g_SysWork.playerWork_4C.player_0.rotation_24.vy - ratan2(deltaX, deltaZ);
    if (deltaRotY >= FP_ANGLE(180.0f))
    {
        deltaRotY -= FP_ANGLE(360.0f);
    }

    if (FP_ANGLE(30.0f) < ABS(deltaRotY))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Event_CheckTouchObbFacing(s_MapPoint2d* mapPoint) // 0x80037A4C
{
    s32    temp_a0_2;
    s32    temp_a2;
    q19_12 halfCosPlayerRotY;
    s32    temp_s2;
    s32    halfSinRotY;
    s32    temp_s4;
    q19_12 deltaX;
    q19_12 deltaZ;
    s32    temp_v1;
    q19_12 clampedHalfCosPlayerRotY;
    bool   cond;
    s32    scaledSinPlayerRotY;
    s32    scaledCosRotY;

    halfSinRotY   = Math_Sin(g_SysWork.playerWork_4C.player_0.rotation_24.vy) >> 1; // `/ 2`.
    scaledCosRotY = -Math_Cos(FP_ANGLE_FROM_PACKED(mapPoint->data.areaLoad.rotationY_4_16)) * mapPoint->data.areaLoad.field_4_24;

    clampedHalfCosPlayerRotY = halfSinRotY;

    temp_a0_2 = scaledCosRotY >> 4; // `/ 16`.
    deltaX    = mapPoint->positionX_0 - g_SysWork.playerWork_4C.player_0.position_18.vx;
    temp_s2   = deltaX - temp_a0_2;
    temp_s4   = deltaX + temp_a0_2;

    clampedHalfCosPlayerRotY = MAX(halfSinRotY, 0);

    if (temp_s4 >= temp_s2)
    {
        cond = clampedHalfCosPlayerRotY < temp_s2;
    }
    else
    {
        cond = clampedHalfCosPlayerRotY < temp_s4;
    }

    if (!cond)
    {
        if (MIN(halfSinRotY, 0) <= MAX(temp_s2, temp_s4))
        {
            halfCosPlayerRotY   = Math_Cos(g_SysWork.playerWork_4C.player_0.rotation_24.vy) >> 1; // `/ 2`.
            scaledSinPlayerRotY = Math_Sin(FP_ANGLE_FROM_PACKED(mapPoint->data.areaLoad.rotationY_4_16)) * mapPoint->data.areaLoad.field_4_24;

            clampedHalfCosPlayerRotY = halfCosPlayerRotY;

            temp_a0_2 = scaledSinPlayerRotY >> 4; // `/ 16`.
            deltaZ    = mapPoint->positionZ_8 - g_SysWork.playerWork_4C.player_0.position_18.vz;
            temp_v1   = deltaZ - temp_a0_2;
            temp_a2   = deltaZ + temp_a0_2;

            clampedHalfCosPlayerRotY = MAX(halfCosPlayerRotY, 0);

            if (temp_a2 >= temp_v1)
            {
                cond = clampedHalfCosPlayerRotY < temp_v1;
            }
            else
            {
                cond = clampedHalfCosPlayerRotY < temp_a2;
            }

            if (!cond)
            {
                if (MIN(halfCosPlayerRotY, 0) <= MAX(temp_v1, temp_a2) &&
                   (((temp_s2 * halfCosPlayerRotY) - (halfSinRotY * temp_v1)) <= 0) && ((temp_s4 * halfCosPlayerRotY) - (halfSinRotY * temp_a2)) >= 0 &&
                   ((-temp_s2 * (temp_a2 - temp_v1)) + ((temp_s4 - temp_s2) * temp_v1)) >= 0)
                {
                    return (((halfSinRotY - temp_s2) * (temp_a2 - temp_v1)) -
                            ((temp_s4 - temp_s2) * (halfCosPlayerRotY - temp_v1))) < 1;
                }
            }
        }
    }

    return false;
}

bool Event_CheckTouchObb(s_MapPoint2d* mapPoint) // 0x80037C5C
{
    q19_12 sinAngle;
    q19_12 cosAngle;
    q19_12 angle;
    q19_12 deltaX;
    q19_12 deltaZ;
    s32    shift8Field_7;
    s32    temp_v0;
    s32    scale;
    u32    temp;

    shift8Field_7 = mapPoint->data.areaLoad.field_4_24 << 8;

    deltaX = g_SysWork.playerWork_4C.player_0.position_18.vx - mapPoint->positionX_0;
    if (mapPoint->data.areaLoad.field_4_24 << 9 < ABS(deltaX))
    {
        return false;
    }

    deltaZ = g_SysWork.playerWork_4C.player_0.position_18.vz - mapPoint->positionZ_8;
    scale  = 2;
    if ((shift8Field_7 * scale) < ABS(deltaZ))
    {
        return false;
    }

    // TODO: Odd packed angle conversion method. `FP_ANGLE_FROM_PACKED` doesn't match here.
    angle    = -(mapPoint->data.areaLoad.rotationY_4_16 << 20) >> 16;
    sinAngle = Math_Sin(angle);

    temp = FP_FROM((-deltaX * sinAngle) + (deltaZ * Math_Cos(angle)), Q12_SHIFT);
    if (temp > Q12(4.0f))
    {
        return false;
    }

    cosAngle = Math_Cos(angle);
    temp_v0  = FP_FROM((deltaX * cosAngle) + (deltaZ * Math_Sin(angle)), Q12_SHIFT);
    if (shift8Field_7 < ABS(temp_v0))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void func_80037DC4(s_SubCharacter* chara) // 0x80037DC4
{
    if (g_SavegamePtr->gameDifficulty_260 <= GameDifficulty_Normal || Rng_RandQ12() >= FP_ANGLE(108.0f))
    {
        g_SavegamePtr->field_B0[g_SavegamePtr->mapOverlayId_A4] &= ~(1 << chara->field_40);
    }
}

void func_80037E40(s_SubCharacter* chara) // 0x80037E40
{
    if (chara->damage_B4.amount_C > Q12(0.0f))
    {
        chara->flags_3E |= CharaFlag_Unk6;
    }
    else
    {
        chara->flags_3E &= ~CharaFlag_Unk6;
    }
}

void func_80037E78(s_SubCharacter* chara) // 0x80037E78
{
    s8  idx;
    s32 cond;

    // TODO: Strange `chara->headingAngle_3C` access.
    if (chara->health_B0 <= Q12(0.0f) && (*(s32*)&chara->headingAngle_3C & 0x600000) == 0x200000)
    {
        idx = chara->attackReceived_41;
        if (idx < 39)
        {
            cond = D_800AD4C8[idx].field_10 == 3;
            func_800914C4(cond, func_8009146C(cond) + 1);
        }

        chara->flags_3E |= CharaFlag_Unk7;
    }
}

void func_80037F24(bool cond) // 0x80037F24
{
    s_Collision     coll;
    s32             charaId0;
    s32             charaId1;
    s32             npcIdx;
    s32             i;
    s32*            temp_a0;
    s_MapPoint2d*   curCharaSpawn;
    s_SubCharacter* chara;
    VECTOR3*        pos;

    npcIdx        = 0;
    curCharaSpawn = g_MapOverlayHeader.charaSpawns_24C[0];
    temp_a0       = &g_SavegamePtr->field_B0[g_SavegamePtr->mapOverlayId_A4];

    if (!cond)
    {
        func_80037154();

        if (g_MapOverlayHeader.func_48 != NULL)
        {
            g_MapOverlayHeader.func_48();
        }
    }

    charaId0 = g_MapOverlayHeader.charaGroupIds_248[0];
    charaId1 = g_MapOverlayHeader.charaGroupIds_248[1];

    for (i = 0; i < 32 && g_VBlanks < 4; i++, curCharaSpawn++)
    {
        if (g_SysWork.npcFlags_2290 == (1 << g_SysWork.npcId_2280) - 1) // TODO: Macro for this check?
        {
            break;
        }

        pos = (VECTOR3*)curCharaSpawn;

        if (!(g_SysWork.flags_22A4 & SysFlag2_4) && HAS_FLAG(temp_a0, i) && !HAS_FLAG(g_SysWork.field_228C, i) &&
            curCharaSpawn->data.spawnInfo.flags_6 != 0 && g_SavegamePtr->gameDifficulty_260 >= curCharaSpawn->data.spawnInfo.field_7_0 &&
            func_8008F914(curCharaSpawn->positionX_0, curCharaSpawn->positionZ_8) &&
            !Math_Distance2dCheck(&g_SysWork.playerWork_4C.player_0.position_18, pos, Q12(22.0f)) &&
            (!cond || Math_Distance2dCheck(&g_SysWork.playerWork_4C.player_0.position_18, pos, Q12(20.0f))))
        {
            while (HAS_FLAG(&g_SysWork.npcFlags_2290, npcIdx))
            {
                npcIdx++;
            }

            bzero(&g_SysWork.npcs_1A0[npcIdx], sizeof(s_SubCharacter));

            if (curCharaSpawn->data.spawnInfo.charaId_4 > Chara_None)
            {
                g_SysWork.npcs_1A0[npcIdx].model_0.charaId_0 = curCharaSpawn->data.spawnInfo.charaId_4;
            }
            else
            {
                g_SysWork.npcs_1A0[npcIdx].model_0.charaId_0 = (i < 16) ? charaId0 : charaId1;
            }

            g_SysWork.npcs_1A0[npcIdx].field_40               = i;
            g_SysWork.npcs_1A0[npcIdx].model_0.controlState_2 = ModelState_Uninitialized;
            g_SysWork.npcs_1A0[npcIdx].model_0.stateStep_3    = curCharaSpawn->data.spawnInfo.flags_6;
            g_SysWork.npcs_1A0[npcIdx].position_18.vx         = curCharaSpawn->positionX_0;
            g_SysWork.npcs_1A0[npcIdx].position_18.vz         = curCharaSpawn->positionZ_8;

            Collision_Get(&coll, curCharaSpawn->positionX_0, curCharaSpawn->positionZ_8);

            g_SysWork.npcs_1A0[npcIdx].position_18.vy = coll.groundHeight_0;
            g_SysWork.npcs_1A0[npcIdx].rotation_24.vy = curCharaSpawn->data.spawnInfo.rotationY_5 * 16;

            SET_FLAG(&g_SysWork.npcFlags_2290, npcIdx);
            SET_FLAG(g_SysWork.field_228C, i);

            chara                          = &g_SysWork.npcs_1A0[npcIdx];
            chara->model_0.anim_4.flags_2 |= AnimFlag_Visible;
        }
    }
}

void func_80038354(void) // 0x80038354
{
    typedef struct
    {
        s8      bitIdx_0;
        u8      unk_1[3];
        s32     field_4;
        VECTOR3 field_8;
    } s_func_800382EC_0;

    s_func_800382EC_0  field_0[3];
    u32                field_40;
    s32                posZShift6;
    s32                posXShift6;
    s32                temp_t1;
    s32                m;
    u8                 var_a2_2;
    s32                j;
    s32                var_s3;
    s32                k;
    s32                var_t5;
    s32                var_v0_4;
    s32                var_v1_3;
    s32                temp_s0_2;
    s32                temp_s0_4;
    s8                 temp_s1;
    s32                temp_v0_4;
    s32                var_v0_5;
    u32                temp_t3;
    u8                 temp_a2;
    u32                new_var;
    s32                l;
    s32                tempAnimDataInfoIdx;
    s32                temp2;
    GsCOORDINATE2*     coord;
    s_SubCharacter*    npc;
    s_func_800382EC_0* temp_s0_3;

    // GCC extension funcs.
    s32 func_800382B0(s32 arg0)
    {
        s32 i;

        for (i = 0; i < 2; i++)
        {
            if (arg0 == field_0[i].bitIdx_0)
            {
                return i;
            }
        }

        return NO_VALUE;
    }

    s32 func_800382EC()
    {
        s32 i;

        for (i = 0; i < 2; i++)
        {
            if (field_0[i].bitIdx_0 == NO_VALUE)
            {
                break;
            }

            if ((field_40 & (1 << field_0[i].bitIdx_0)) == 0)
            {
                field_40 |= (1 << field_0[i].bitIdx_0);
                return i;
            }
        }

        return NO_VALUE;
    }

    posXShift6 = g_SysWork.playerWork_4C.player_0.position_18.vx >> 6;
    posZShift6 = g_SysWork.playerWork_4C.player_0.position_18.vz >> 6;

    Demo_DemoRandSeedBackup();
    Demo_DemoRandSeedRestore();

    for (j = 0; j < ARRAY_SIZE(field_0); j++)
    {
        field_0[j].bitIdx_0   = NO_VALUE;
        field_0[j].field_4    = Q12(0.25f);
        field_0[j].field_8.vy = 0;
    }

    for (k = 0, npc = g_SysWork.npcs_1A0; k < ARRAY_SIZE(g_SysWork.npcs_1A0); k++, npc++)
    {
        if (npc->model_0.charaId_0 != Chara_None && npc->model_0.charaId_0 != Chara_Padlock)
        {
            if (npc->model_0.charaId_0 <= Chara_MonsterCybil)
            {
                temp_t3 = FP_SQUARE_PRECISE((npc->position_18.vx >> 6) - posXShift6, Q12_SHIFT) +
                          FP_SQUARE_PRECISE((npc->position_18.vz >> 6) - posZShift6, Q12_SHIFT);
                var_t5 = 0;

                if (g_MapOverlayHeader.mapInfo_0->flags_6 & MapFlag_Interior)
                {
                    var_t5 = (g_MapOverlayHeader.mapInfo_0->flags_6 & (MapFlag_OneActiveChunk | MapFlag_TwoActiveChunks)) > 0;
                }

                for (j = 0; j < 3; j++)
                {
                    if (npc->health_B0 <= Q12(0.0f) || npc->flags_3E & CharaFlag_Unk9 || temp_t3 >= field_0[j].field_4)
                    {
                        continue;
                    }

                    if (var_t5 != 0)
                    {
                        s32 playerCell = (g_SysWork.playerWork_4C.player_0.position_18.vx + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                        s32 npcCell    = (npc->position_18.vx                        + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                        if (npcCell != playerCell)
                        {
                            continue;
                        }

                        // TODO: Unique vars for these.
                        playerCell = (g_SysWork.playerWork_4C.player_0.position_18.vz + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                        npcCell    = (npc->position_18.vz                        + (CHUNK_CELL_SIZE * 4)) / CHUNK_CELL_SIZE;
                        if (npcCell != playerCell)
                        {
                            continue;
                        }
                    }

                    for (m = 2; j < m; m--)
                    {
                        field_0[m].bitIdx_0   = field_0[m - 1].bitIdx_0;
                        field_0[m].field_4    = field_0[m - 1].field_4;
                        field_0[m].field_8.vx = field_0[m - 1].field_8.vx;
                        field_0[m].field_8.vz = field_0[m - 1].field_8.vz;
                    }

                    temp_t1 = (u32)npc - (u32)g_SysWork.npcs_1A0;
                    temp2   = ((((temp_t1 * 0x7E8) - (temp_t1 * 0xFD)) * 4) + temp_t1) * -0x3FFFF;

                    field_0[j].bitIdx_0   = temp2 >> 3;
                    field_0[j].field_4    = temp_t3;
                    field_0[j].field_8.vx = npc->position_18.vx;
                    field_0[j].field_8.vz = npc->position_18.vz;
                    break;
                }

                new_var = temp_t3;

                if (new_var > ((var_t5 == 0 && npc->health_B0 < Q12(0.0f)) ? SQUARE(24) : SQUARE(40)))
                {
                    npc->model_0.charaId_0 = Chara_None;
                    SysWork_NpcFlagClear(k);
                    CLEAR_FLAG(g_SysWork.field_228C, npc->field_40);
                    continue;
                }

                if ((g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 0x2 && temp_t3 > SQUARE(15)) ||
                    (!(g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 0x2) &&
                     Camera_Distance2dGet(&npc->position_18) > SQUARE(15)))
                {
                    npc->model_0.anim_4.flags_2 &= ~AnimFlag_Visible;
                }
                else
                {

                    npc->model_0.anim_4.flags_2 |= AnimFlag_Visible;
                }
            }

            npc->model_0.anim_4.flags_2 |= AnimFlag_Unlocked;

            tempAnimDataInfoIdx = g_CharaAnimInfoIdxs[npc->model_0.charaId_0];
            coord               = g_InitCharaDataAnimInfo[tempAnimDataInfoIdx].npcCoords_14;

            func_8008A384(npc);
            func_80037E40(npc);
            func_8003BD48(npc);

            g_MapOverlayHeader.charaUpdateFuncs_194[npc->model_0.charaId_0](npc, g_InitCharaDataAnimInfo[tempAnimDataInfoIdx].animFile1_8, coord);

            func_8003BE28();
            func_80037E78(npc);
            func_8008A3AC(npc);

            if (npc->model_0.anim_4.flags_2 & AnimFlag_Visible)
            {
                func_8003DA9C(npc->model_0.charaId_0, coord, 1, npc->timer_C6, (s8)npc->model_0.paletteIdx_1);
            }
        }
    }

    for (k = 2; k >= 0; k--)
    {
        if (field_0[k].bitIdx_0 != NO_VALUE)
        {
            break;
        }
    }

    g_RadioPitchState = k + 1;

    if (!(g_SavegamePtr->itemToggleFlags_AC & ItemToggleFlag_RadioOn))
    {
        return;
    }

    field_40 = 0;

    for (l = 0; l < ARRAY_SIZE(D_800BCDA8); l++)
    {
        temp_s0_2 = D_800BCDA8[l].field_1;
        if (temp_s0_2 == NO_VALUE)
        {
            var_v0_4 = NO_VALUE;
        }
        else
        {
            var_v0_4 = func_800382B0(temp_s0_2);
        }

        if (var_v0_4 >= 0)
        {
            D_800BCDA8[l].field_2 = var_v0_4;
            field_40             |= 1 << temp_s0_2;
        }
        else
        {
            D_800BCDA8[l].field_1 = NO_VALUE;
        }
    }

    for (l = 0; l < ARRAY_SIZE(D_800BCDA8); l++)
    {
        temp_s1 = D_800BCDA8[l].field_1;
        if (temp_s1 == NO_VALUE)
        {
            temp_v0_4 = func_800382EC();
            if (temp_v0_4 != temp_s1)
            {
                var_v0_5 = field_0[temp_v0_4].bitIdx_0;
            }
            else
            {
                var_v0_5 = NO_VALUE;
            }

            D_800BCDA8[l].field_2 = temp_v0_4;
            D_800BCDA8[l].field_1 = var_v0_5;
        }
    }

    for (l = 0; l < ARRAY_SIZE(D_800BCDA8); l++)
    {
        if (D_800BCDA8[l].field_0 == NO_VALUE)
        {
            if (D_800BCDA8[l].field_1 >= 0)
            {
                SD_Call((u16)(Sfx_RadioInterferenceLoop + l));
            }
        }
        else
        {
            var_s3 = 0;
            if (!(g_MapOverlayHeader.mapInfo_0->flags_6 & MapFlag_Interior) ||
                !(g_MapOverlayHeader.mapInfo_0->flags_6 & (MapFlag_OneActiveChunk | MapFlag_TwoActiveChunks)))
            {
                var_s3 = 1;
            }

            if (D_800BCDA8[l].field_1 >= 0)
            {
                temp_s0_3 = &field_0[D_800BCDA8[l].field_2];
                temp_s0_4 = Sound_StereoBalanceGet(&temp_s0_3->field_8);

                var_v1_3 = SquareRoot12(temp_s0_3->field_4 << Q12_SHIFT) >> 8;
                if (var_s3 != 0)
                {
                    var_v1_3 >>= 1;
                }

                var_a2_2 = CLAMP(var_v1_3, 0, 0xFF);

                Sd_SfxAttributesUpdate(Sfx_RadioInterferenceLoop + l, temp_s0_4, var_a2_2, 0);
            }
            else
            {
                Sd_SfxStop(Sfx_RadioInterferenceLoop + l);
            }
        }

        D_800BCDA8[l].field_0 = D_800BCDA8[l].field_1;
    }
}

bool Math_Distance2dCheck(const VECTOR3* posFrom, const VECTOR3* posTo, q19_12 radius) // 0x80038A6C
{
    q19_12 deltaX;
    q19_12 deltaZ;
    q19_12 radiusSqr;
    q19_12 sum;

    // Check rough radius intersection on X axis.
    deltaX = posFrom->vx - posTo->vx;
    if (radius < deltaX)
    {
        return true;
    }
    if (radius < -deltaX)
    {
        return true;
    }

    // Check rough radius intersection on Z axis.
    deltaZ = posFrom->vz - posTo->vz;
    if (radius < deltaZ)
    {
        return true;
    }
    if (radius < -deltaZ)
    {
        return true;
    }

    // Check distance.
    sum       = FP_MULTIPLY_PRECISE(deltaX, deltaX, Q12_SHIFT) + FP_MULTIPLY_PRECISE(deltaZ, deltaZ, Q12_SHIFT);
    radiusSqr = FP_MULTIPLY_PRECISE(radius, radius, Q12_SHIFT);
    return sum > radiusSqr;
}

s32 Camera_Distance2dGet(const VECTOR3* pos) // 0x80038B44
{
    VECTOR3 camPos; // Q19.12
    q25_6   deltaX;
    q25_6   deltaZ;

    vwGetViewPosition(&camPos);
    deltaX = Q12_TO_Q6(camPos.vx - pos->vx);
    deltaZ = Q12_TO_Q6(camPos.vz - pos->vz);
    return FP_MULTIPLY_PRECISE(deltaX, deltaX, Q12_SHIFT) + FP_MULTIPLY_PRECISE(deltaZ, deltaZ, Q12_SHIFT);
}

// ========================================
// GAME STATES UPDATERS
// ========================================

void GameState_InGame_Update(void) // 0x80038BD4
{
    s_SubCharacter* player;

    Demo_DemoRandSeedBackup();

    switch (g_GameWork.gameStateStep_598[0])
    {
        case 0:
            ScreenFade_Start(true, true, false);
            g_ScreenFadeTimestep            = Q12(3.0f);
            g_GameWork.gameStateStep_598[0] = 1;

        case 1:
            DrawSync(SyncMode_Wait);
            func_80037154();
            Savegame_MapRoomIdxSet();
            func_800892A4(1);

            g_IntervalVBlanks = 2;
            g_GameWork.gameStateStep_598[0]++;
            g_SysWork.sysFlags_22A0 |= SysFlag_6;
            break;
    }

    if (g_SysWork.sysState_8 != SysState_Gameplay && g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f))
    {
        SysWork_StateSetNext(SysState_Gameplay);
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        g_DeltaTimeCpy = g_DeltaTime0;
    }
    else
    {
        g_DeltaTimeCpy = g_DeltaTime1;
    }

    if (g_SysWork.sysState_8 == SysState_Gameplay)
    {
        g_SysWork.isMgsStringSet_18 = 0;
        g_SysStateFuncs[SysState_Gameplay]();
    }
    else
    {
        g_DeltaTime0 = 0;
        g_SysStateFuncs[g_SysWork.sysState_8]();

        if (g_SysWork.sysState_8 == SysState_Gameplay)
        {
            Event_Update(true);

            if (g_MapEventSysState != SysState_Invalid)
            {
                SysWork_StateSetNext(g_MapEventSysState);
            }
        }
    }
    Demo_DemoRandSeedRestore();

    D_800A9A0C = ScreenFade_IsFinished() && Fs_QueueDoThingWhenEmpty();

    if (!(g_SysWork.sysFlags_22A0 & SysFlag_Freeze) && g_MapOverlayHeader.worldObjectsUpdate_40 != NULL)
    {
        g_MapOverlayHeader.worldObjectsUpdate_40();
    }

    Screen_CutsceneCameraStateUpdate();
    func_80035DB4(false);
    Demo_DemoRandSeedRestore();
    Demo_DemoRandSeedRestore();

    if (!(g_SysWork.sysFlags_22A0 & SysFlag_Freeze))
    {
        func_80040014();
        vcMoveAndSetCamera(false, false, false, false, false, false, false, false);

        if (g_MapOverlayHeader.func_44 != NULL)
        {
            g_MapOverlayHeader.func_44();
        }

        Demo_DemoRandSeedRestore();

        player = &g_SysWork.playerWork_4C.player_0;
        Player_Update(player, FS_BUFFER_0, g_SysWork.playerBoneCoords_890);

        Demo_DemoRandSeedRestore();
        func_8003F170();

        if (g_SavegamePtr->mapOverlayId_A4 != MapOverlayId_MAP7_S03)
        {
            g_MapOverlayHeader.func_168(0, g_SavegamePtr->mapOverlayId_A4, 1);
        }

        Demo_DemoRandSeedRestore();

        if (player->model_0.anim_4.flags_2 & AnimFlag_Visible)
        {
            func_8003DA9C(Chara_Harry, g_SysWork.playerBoneCoords_890, 1, g_SysWork.playerWork_4C.player_0.timer_C6, 0);
            func_8008A384(&g_SysWork.playerWork_4C.player_0);
            func_8007D970(&g_SysWork.playerWork_4C, g_SysWork.playerBoneCoords_890);
            func_8008A3AC(&g_SysWork.playerWork_4C.player_0);
        }

        Demo_DemoRandSeedRestore();
        func_80037F24(true);
        func_80038354();
        func_8005E89C();
        Ipd_CloseRangeChunksInit();
        func_8003C878(1);
        Demo_DemoRandSeedAdvance();
    }
}

void SysState_Gameplay_Update(void) // 0x80038BD4
{
    s_SubCharacter* player;

    player = &g_SysWork.playerWork_4C.player_0;

    Event_Update(player->attackReceived_41 != NO_VALUE);
    Savegame_MapRoomIdxSet();

    switch (FP_ROUND_SCALED(player->health_B0, 10, Q12_SHIFT))
    {
        case 0:
            func_800892A4(17);
            break;

        case 1:
        case 2:
            func_800892A4(16);
            break;

        case 3:
            func_800892A4(15);
            break;

        case 4:
            func_800892A4(14);
            break;

        case 5:
            func_800892A4(13);
            break;

        case 6:
            func_800892A4(12);
            break;
    }

    if (g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f))
    {
        return;
    }

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.light_A &&
        g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1))
    {
        Game_FlashlightToggle();
    }

    if (g_MapEventSysState != SysState_Invalid)
    {
        SysWork_StateSetNext(g_MapEventSysState);
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.pause_14)
    {
        SysWork_StateSetNext(SysState_GamePaused);
    }
    else if (func_8007F26C() == true)
    {
        return;
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.item_16)
    {
        SysWork_StateSetNext(SysState_StatusMenu);
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.map_18)
    {
        SysWork_StateSetNext(SysState_MapScreen);
        g_SysWork.isMgsStringSet_18 = 0;
    }
    else if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.option_1A)
    {
        SysWork_StateSetNext(SysState_OptionsMenu);
    }

    if (g_SysWork.sysState_8 == SysState_OptionsMenu ||
        g_SysWork.sysState_8 == SysState_StatusMenu ||
        g_SysWork.sysState_8 == SysState_MapScreen)
    {
        g_SysWork.flags_22A4 |= SysFlag2_MenuOpen;
    }
    else if (ScreenFade_IsNone())
    {
        g_SysWork.flags_22A4 &= ~SysFlag2_MenuOpen;
    }
}

void SysState_GamePaused_Update(void) // 0x800391E8
{
    D_800A9A68 += g_DeltaTime1;
    if (!((D_800A9A68 >> 11) & (1 << 0)))
    {
        Gfx_StringSetPosition(SCREEN_POSITION_X(39.25f), SCREEN_POSITION_Y(43.5f));
        Gfx_StringDraw("\x07PAUSED", DEFAULT_MAP_MESSAGE_LENGTH);
    }

    func_80091380();
    Game_TimerUpdate();

    if (g_SysWork.sysStateStep_C[0] == 0)
    {
        SD_Call(3);
        g_SysWork.sysStateStep_C[0]++;
    }

    // Debug button combo to bring up save screen from pause screen.
    // DPad-Left + L2 + L1 + LS-Left + RS-Left + L3
    if ((g_Controller0->btnsHeld_C == (ControllerFlag_L3 |
                                       ControllerFlag_DpadLeft |
                                       ControllerFlag_L2 |
                                       ControllerFlag_L1 |
                                       ControllerFlag_LStickLeft2 |
                                       ControllerFlag_RStickLeft |
                                       ControllerFlag_LStickLeft)) &&
        (g_Controller0->btnsClicked_10 & ControllerFlag_L3))
    {
        D_800A9A68 = 0;
        SD_Call(4);
        g_MapEventIdx = 0;
        SysWork_StateSetNext(SysState_SaveMenu1);
        return;
    }

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.pause_14)
    {
        D_800A9A68 = 0;
        SD_Call(4);
        SysWork_StateSetNext(SysState_Gameplay);
    }
}

void SysState_OptionsMenu_Update(void) // 0x80039344
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            ScreenFade_Start(true, false, false);
            g_ScreenFadeTimestep        = Q12(0.0f);
            g_SysWork.sysStateStep_C[0] = 1;

        case 1:
            if (Ipd_ChunkInitCheck() != 0)
            {
                SD_Call(19);
                GameFs_OptionBinLoad();

                g_SysWork.sysStateStep_C[0]++;
            }
            break;
    }

    if (D_800A9A0C != 0)
    {
        Game_StateSetNext(GameState_OptionScreen);
    }
}

void func_8003943C(void) // 0x8003943C
{
    s32 roundedVal0;
    s32 roundedVal1;
    s32 val0;
    s32 val1;

    func_8008B3E4(0);

    if (g_SysWork.field_275C > Q12(256.0f))
    {
        val0        = g_SysWork.field_275C - Q12(256.0f);
        roundedVal0 = FP_ROUND_TO_ZERO(val0, Q12_SHIFT);
        func_8008B438(g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap), roundedVal0, 0);

        if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
        {
            val1        = g_SysWork.field_2764 - Q12(256.0f);
            roundedVal1 = FP_ROUND_TO_ZERO(val1, Q12_SHIFT);
            func_8008B40C(roundedVal1, 0);
        }
    }
    else
    {
        func_8008B438(g_SysWork.playerCombat_38.weaponAttack_F != WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap), 0, 0);

        if (g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_RockDrill, AttackInputType_Tap))
        {
            func_8008B40C(0, 0);
        }
    }
    
    switch (g_SavegamePtr->mapOverlayId_A4)
    {
        case MapOverlayId_MAP0_S01:
        case MapOverlayId_MAP0_S02:
        case MapOverlayId_MAP1_S00:
        case MapOverlayId_MAP1_S01:
        case MapOverlayId_MAP1_S02:
        case MapOverlayId_MAP1_S03:
        case MapOverlayId_MAP1_S04:
        case MapOverlayId_MAP1_S05:
        case MapOverlayId_MAP1_S06:
        case MapOverlayId_MAP2_S00:
        case MapOverlayId_MAP2_S01:
        case MapOverlayId_MAP2_S02:
        case MapOverlayId_MAP2_S03:
        case MapOverlayId_MAP2_S04:
        case MapOverlayId_MAP3_S00:
        case MapOverlayId_MAP3_S01:
        case MapOverlayId_MAP3_S02:
        case MapOverlayId_MAP3_S04:
        case MapOverlayId_MAP3_S05:
        case MapOverlayId_MAP3_S06:
        case MapOverlayId_MAP4_S00:
        case MapOverlayId_MAP4_S01:
        case MapOverlayId_MAP4_S02:
        case MapOverlayId_MAP4_S03:
        case MapOverlayId_MAP4_S04:
        case MapOverlayId_MAP4_S05:
        case MapOverlayId_MAP4_S06:
        case MapOverlayId_MAP5_S00:
        case MapOverlayId_MAP5_S01:
        case MapOverlayId_MAP5_S02:
        case MapOverlayId_MAP5_S03:
        case MapOverlayId_MAP6_S00:
        case MapOverlayId_MAP6_S01:
        case MapOverlayId_MAP6_S02:
        case MapOverlayId_MAP6_S03:
        case MapOverlayId_MAP6_S04:
        case MapOverlayId_MAP6_S05:
        case MapOverlayId_MAP7_S00:
        case MapOverlayId_MAP7_S01:
        case MapOverlayId_MAP7_S02:
            break;

        case MapOverlayId_MAP3_S03:
            Sd_SfxStop(Sfx_Unk1525);
            Sd_SfxStop(Sfx_Unk1527);
            break;

        case MapOverlayId_MAP0_S00:
            Sd_SfxStop(Sfx_Unk1358);
            break;
    }
}

void SysState_StatusMenu_Update(void) // 0x80039568
{
    e_GameState gameState;

    gameState = g_GameWork.gameState_594;

    g_GameWork.gameState_594 = GameState_LoadStatusScreen;
    g_SysWork.timer_1C = 0;
    g_SysWork.timer_20 = 0;

    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;

    SysWork_StateSetNext(SysState_Gameplay);

    g_GameWork.gameStateStep_598[0] = gameState;
    g_GameWork.gameStatePrev_590    = gameState;
    g_GameWork.gameStateStep_598[0] = 0;
}

void GameState_LoadStatusScreen_Update(void) // 0x800395C0
{
    s_Savegame* save;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        DrawSync(SyncMode_Wait);
        g_IntervalVBlanks   = 1;
        ScreenFade_Reset();

        func_8003943C();

        if (Sd_AudioStreamingCheck())
        {
            SD_Call(19);
        }

        save = g_SavegamePtr;
        func_800540A4(save->mapOverlayId_A4);
        GameFs_MapItemsTextureLoad(save->mapOverlayId_A4);

        g_GameWork.gameStateStep_598[0]++;
    }

    Gfx_2dBackgroundMotionBlur(SyncMode_Wait2);

    if (Fs_QueueDoThingWhenEmpty())
    {
        Game_StateSetNext(GameState_InventoryScreen);
    }
}

void SysState_MapScreen_Update(void) // 0x800396D4
{
    if (!HAS_MAP(g_SavegamePtr->paperMapIdx_A9))
    {
        if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.map_18 ||
            Gfx_MapMsg_Draw(MapMsgIdx_NoMap) > MapMsgState_Idle)
        {
            SysWork_StateSetNext(SysState_Gameplay);
        }
    }
    else if ((g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) && !g_SysWork.field_2388.isFlashlightOn_15 &&
             ((g_SysWork.field_2388.field_1C[0].field_0.field_0.s_field_0.field_0 & (1 << 0)) ||
              (g_SysWork.field_2388.field_1C[1].field_0.field_0.s_field_0.field_0 & (1 << 0))))
    {
        if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.map_18 ||
            Gfx_MapMsg_Draw(MapMsgIdx_TooDarkForMap) > MapMsgState_Idle)
        {
            SysWork_StateSetNext(SysState_Gameplay);
        }
    }
    else
    {
        if (g_SysWork.sysStateStep_C[0] == 0)
        {
            if (g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx_A9] != NO_VALUE)
            {
                Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx_A9], FS_BUFFER_1, &g_PaperMapMarkingAtlasImg);
            }

            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[g_SavegamePtr->paperMapIdx_A9]);

            ScreenFade_Start(true, false, false);
            g_ScreenFadeTimestep = Q12(0.0f);
            g_SysWork.sysStateStep_C[0]++;
        }

        if (D_800A9A0C != 0)
        {
            Game_StateSetNext(GameState_MapScreen);
        }
    }
}

void GameState_LoadMapScreen_Update(void) // 0x8003991C
{
    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        DrawSync(SyncMode_Wait);
        g_IntervalVBlanks = 1;

        func_8003943C();
        func_80066E40();

        if (g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx_A9] != NO_VALUE)
        {
            Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + g_PaperMapMarkingFileIdxs[g_SavegamePtr->paperMapIdx_A9], FS_BUFFER_1, &g_PaperMapMarkingAtlasImg);
        }

        Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[g_SavegamePtr->paperMapIdx_A9], FS_BUFFER_2, &g_PaperMapImg);
        g_GameWork.gameStateStep_598[0]++;
    }

    Gfx_2dBackgroundMotionBlur(SyncMode_Wait2);

    if (Fs_QueueDoThingWhenEmpty())
    {
        Game_StateSetNext(GameState_MapScreen);
    }
}

void SysState_Fmv_Update(void) // 0x80039A58
{
    #define BASE_AUDIO_FILE_IDX FILE_XA_ZC_14392

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            ScreenFade_Start(false, false, false);
            D_800A9A0C                  = 0;
            g_SysWork.sysStateStep_C[0] = 1;

        case 1:
            if (Ipd_ChunkInitCheck() != 0)
            {
                GameFs_StreamBinLoad();
                g_SysWork.sysStateStep_C[0]++;
            }
            break;
    }

    if (D_800A9A0C == 0)
    {
        return;
    }

    // Copy framebuffer into `IMAGE_BUFFER_0` before movie playback.
    DrawSync(SyncMode_Wait);
    StoreImage(&D_800A9A6C, (u32*)IMAGE_BUFFER_0);
    DrawSync(SyncMode_Wait);

    func_800892A4(0);
    func_80089128();

    // Start playing movie. File to play is based on file ID `BASE_AUDIO_FILE_IDX - g_MapEventIdx`.
    // Blocks until movie has finished playback or user has skipped it.
    open_main(BASE_AUDIO_FILE_IDX - g_MapEventIdx, g_FileTable[BASE_AUDIO_FILE_IDX - g_MapEventIdx].blockCount_0_19);

    func_800892A4(1);

    // Restore copied framebuffer from `IMAGE_BUFFER_0`.
    GsSwapDispBuff();
    LoadImage(&D_800A9A6C, (u32*)IMAGE_BUFFER_0);
    DrawSync(SyncMode_Wait);

    // Set savegame flag based on `g_MapEventParam->disabledEventFlag_2` flag ID.
    Savegame_EventFlagSetAlt(g_MapEventParam->disabledEventFlag_2);

    // Return to game.
    Game_StateSetNext(GameState_InGame);

    // If flag is set, returns to `GameState_InGame` with `gameStateStep[0]` = 1.
    if (g_MapEventParam->flags_8_13 & EventParamUnkState_1)
    {
        g_GameWork.gameStateStep_598[0] = 1;
    }
}

void SysState_LoadArea_Update(void) // 0x80039C40
{
    u32           var1;
    s_MapPoint2d* mapPoint;

    g_SysWork.field_229C            = 0;
    g_SysWork.loadingScreenIdx_2281 = D_800BCDB0.data.areaLoad.loadingScreenId_4_9;
    g_SysWork.field_2283            = g_MapEventParam->field_8_19;
    g_SysWork.field_2282            = g_MapEventParam->flags_8_13;

    SD_Call(SfxPairs[g_SysWork.field_2283].sfx_0);

    if (g_SysWork.field_2283 == 7)
    {
        D_800BCDD4            = 0;
        g_SysWork.flags_22A4 |= SysFlag2_10;
    }

    D_800BCDB0 = g_MapOverlayHeader.mapPointsOfInterest_1C[g_MapEventParam->pointOfInterestIdx_8_5];

    if (D_800BCDB0.data.areaLoad.field_4_24 == 1)
    {
        mapPoint                = &g_MapOverlayHeader.mapPointsOfInterest_1C[g_MapEventParam->field_5];
        var1                    = g_SysWork.playerWork_4C.player_0.position_18.vz - mapPoint->positionZ_8;
        D_800BCDB0.positionX_0 += g_SysWork.playerWork_4C.player_0.position_18.vx - mapPoint->positionX_0;
        D_800BCDB0.positionZ_8 += var1;
    }

    if (g_SysWork.sysState_8 == SysState_LoadOverlay)
    {
        g_SysWork.processFlags_2298    = SysWorkProcessFlag_OverlayTransition;
        g_SavegamePtr->mapOverlayId_A4 = g_MapEventParam->mapOverlayIdx_8_25;
        GameFs_MapLoad(g_SavegamePtr->mapOverlayId_A4);
    }
    else
    {
        g_SysWork.processFlags_2298 = SysWorkProcessFlag_RoomTransition;
        func_8003640C(g_MapEventParam->mapOverlayIdx_8_25);

        if (g_MapOverlayHeader.mapPointsOfInterest_1C[g_MapEventParam->pointOfInterestIdx_8_5].data.areaLoad.field_4_5 != 0)
        {
            g_SysWork.field_2349 = g_MapOverlayHeader.mapPointsOfInterest_1C[g_MapEventParam->pointOfInterestIdx_8_5].data.areaLoad.field_4_5 - 1;
        }
    }

    Savegame_EventFlagSetAlt(g_MapEventParam->disabledEventFlag_2);

    if (g_MapEventParam->field_8_24)
    {
        g_SysWork.flags_22A4 |= SysFlag2_6;
    }
    else
    {
        g_SysWork.flags_22A4 &= ~SysFlag2_6;
    }

    g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;
    Game_StateSetNext(GameState_MainLoadScreen);
    Gfx_2dBackgroundMotionBlur(SyncMode_Immediate);
}

// ========================================
// MAP EVENTS RELATED
// ========================================

void AreaLoad_UpdatePlayerPosition(void) // 0x80039F30
{
    Chara_PositionUpdateFromParams(&D_800BCDB0);
}

void AreaLoad_TransitionSound(void) // 0x80039F54
{
    SD_Call(SfxPairs[g_SysWork.field_2283].sfx_2);
}

s8 func_80039F90(void) // 0x80039F90
{
    if (g_SysWork.processFlags_2298 & (SysWorkProcessFlag_RoomTransition | SysWorkProcessFlag_OverlayTransition))
    {
        return g_SysWork.field_2282;
    }

    return 0;
}

void SysState_ReadMessage_Update(void) // 0x80039FB8
{
    s32 i;
    void (**unfreezePlayerFunc)(bool);
	
	// When `SysState_ReadMessage_Update` is called, the game world freezes.
	// The following conditions unfreeze:
	// - A specific event related flag is disenabled.
	// - A specific camera related flag is disenabled.
	// - There is no alive enemy.
    if (!(g_MapEventParam->flags_8_13 & EventParamUnkState_0) && !(g_SysWork.flags_22A4 & SysFlag2_5))
    {
        for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
        {
            if (g_SysWork.npcs_1A0[i].model_0.charaId_0 >= Chara_Harry && g_SysWork.npcs_1A0[i].model_0.charaId_0 <= Chara_MonsterCybil &&
                g_SysWork.npcs_1A0[i].health_B0 > Q12(0.0f))
            {
                break;
            }
        }

        if (i == ARRAY_SIZE(g_SysWork.npcs_1A0))
        {
            g_DeltaTime0 = g_DeltaTimeCpy;
        }
    }
    else
    {
        g_DeltaTime0 = g_DeltaTimeCpy;
    }

    if (g_SysWork.isMgsStringSet_18 == 0)
    {
        g_MapOverlayHeader.freezePlayerControl_C8();
    }

    switch (Gfx_MapMsg_Draw(g_MapEventIdx)) 
    {
        case MapMsgState_Finish:
            break;

        case MapMsgState_Idle:
            break;

        case MapMsgState_SelectEntry0:
            Savegame_EventFlagSetAlt(g_MapEventParam->disabledEventFlag_2);

            unfreezePlayerFunc = &g_MapOverlayHeader.unfreezePlayerControl_CC;

            SysWork_StateSetNext(SysState_Gameplay);

            (*unfreezePlayerFunc)(false);
            break;
    }
}

void SysWork_SavegameUpdatePlayer(void) // 0x8003A120
{
    s_Savegame* save;

    save = g_SavegamePtr;

    save->locationId_A8       = g_MapEventIdx;
    save->playerPositionX_244 = g_SysWork.playerWork_4C.player_0.position_18.vx;
    save->playerPositionZ_24C = g_SysWork.playerWork_4C.player_0.position_18.vz;
    save->playerRotationY_248 = g_SysWork.playerWork_4C.player_0.rotation_24.vy;
    save->playerHealth_240    = g_SysWork.playerWork_4C.player_0.health_B0;
}

void func_8003A16C(void) // 0x8003A16C
{
    if (!(g_SysWork.flags_22A4 & SysFlag2_1))
    {
        // Update `savegame_30C` with player info.
        SysWork_SavegameUpdatePlayer();

        g_GameWork.autosave_90 = g_GameWork.savegame_30C;
    }
}

void SysWork_SavegameReadPlayer(void) // 0x8003A1F4
{
    g_SysWork.playerWork_4C.player_0.position_18.vx = g_SavegamePtr->playerPositionX_244;
    g_SysWork.playerWork_4C.player_0.position_18.vz = g_SavegamePtr->playerPositionZ_24C;
    g_SysWork.playerWork_4C.player_0.rotation_24.vy = g_SavegamePtr->playerRotationY_248;
    g_SysWork.playerWork_4C.player_0.health_B0      = g_SavegamePtr->playerHealth_240;
}

void SysState_SaveMenu_Update(void) // 0x8003A230
{
    s32 gameState;

    func_80033548();

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            SysWork_SavegameUpdatePlayer();

            if (Savegame_EventFlagGet(EventFlag_SeenSaveScreen) || g_SavegamePtr->locationId_A8 == SaveLocationId_NextFear || g_MapEventIdx == 0)
            {
                GameFs_SaveLoadBinLoad();

                ScreenFade_Start(true, false, false);
                SysWork_StateStepIncrement(0);
            }
            else if (Gfx_MapMsg_Draw(MapMsgIdx_SaveGame) == MapMsgState_SelectEntry0)
            {
                Savegame_EventFlagSet(EventFlag_SeenSaveScreen);

                GameFs_SaveLoadBinLoad();

                ScreenFade_Start(true, false, false);
                SysWork_StateStepIncrement(0);
            }
            break;
        
        case 1:
            if (D_800A9A0C != 0)
            {
                ScreenFade_Start(true, true, false);

                func_8003943C();

                gameState = g_GameWork.gameState_594;

                g_GameWork.gameState_594 = GameState_Unk10;

                g_SysWork.timer_1C = 0;
                g_SysWork.timer_20 = 0;

                g_GameWork.gameStateStep_598[1] = 0;
                g_GameWork.gameStateStep_598[2] = 0;

                SysWork_StateSetNext(SysState_Gameplay);

                g_GameWork.gameStateStep_598[0] = gameState;
                g_GameWork.gameStatePrev_590    = gameState;
                g_GameWork.gameStateStep_598[0] = 0;
            }
            break;
    }
}

void SysState_EventCallFunc_Update(void) // 0x8003A3C8
{
    if (g_MapEventParam->flags_8_13 != EventParamUnkState_None)
    {
        Savegame_EventFlagSetAlt(g_MapEventParam->disabledEventFlag_2);
    }

    g_DeltaTime0 = g_DeltaTimeCpy;
    g_MapOverlayHeader.mapEventFuncs_20[g_MapEventIdx]();
}

void SysState_EventSetFlag_Update(void) // 0x8003A460
{
    g_DeltaTime0 = g_DeltaTimeCpy;
    Savegame_EventFlagSetAlt(g_MapEventParam->disabledEventFlag_2);
    g_SysWork.sysState_8 = SysState_Gameplay;
}

void SysState_EventPlaySound_Update(void) // 0x8003A4B4
{
    g_DeltaTime0 = g_DeltaTimeCpy;

    SD_Call(((u16)g_MapEventIdx + Sfx_Base) & 0xFFFF);

    Savegame_EventFlagSetAlt(g_MapEventParam->disabledEventFlag_2);
    g_SysWork.sysState_8 = SysState_Gameplay;
}

void SysState_GameOver_Update(void) // 0x8003A52C
{
    #define TIP_COUNT 15

    u16  seenTipIdxs[1];
    s32  tipIdx;
    s32  randTipVal;
    u16* temp_a0;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            g_MapOverlayHeader.freezePlayerControl_C8();
            g_SysWork.field_28 = Q12(0.0f);

            if (g_GameWork.autosave_90.continueCount_27B < 99)
            {
                g_GameWork.autosave_90.continueCount_27B++;
            }

            MainMenu_SelectedOptionIdxReset();

            // If every game over tip has been seen, reset flag bits.
            if (g_GameWork.config_0.seenGameOverTips_2E[0] == SHRT_MAX)
            {
                g_GameWork.config_0.seenGameOverTips_2E[0] = 0;
            }

            randTipVal = 0;

            seenTipIdxs[0] = g_GameWork.config_0.seenGameOverTips_2E[0];
            for (tipIdx = 0; tipIdx < TIP_COUNT; tipIdx++)
            {
                if (!Flags16b_IsSet(seenTipIdxs, tipIdx))
                {
                    if ((!(g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) && (tipIdx - 13) >= 2u) ||
                        ( (g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) && (tipIdx - 13) <  2u))
                    {
                        randTipVal += 3;
                    }
                    else
                    {
                        randTipVal++;
                    }
                }
            }

            randTipVal = Rng_GenerateInt(0, randTipVal - 1);

            // `randTipVal` seems to go unused after loop, gets checked during loop and can cause early exit,
            // thereby affecting what `tipIdx` will contain.
            for (tipIdx = 0; tipIdx < TIP_COUNT; tipIdx++)
            {
                if (!Flags16b_IsSet(seenTipIdxs, tipIdx))
                {
                    if ((!(g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) && (tipIdx - 13) >= 2u) ||
                        ( (g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 0x3) && (tipIdx - 13) <  2u))
                    {
                        if (randTipVal < 3)
                        {
                            break;
                        }

                        randTipVal -= 3;
                    }
                    else
                    {
                        if (randTipVal <= 0)
                        {
                            break;
                        }

                        randTipVal--;
                    }
                }
            }

            // Store current shown `tipIdx`, later `sysStateStep_C == 7` will set it inside `seenGameOverTips_2E`.
            g_SysState_GameOver_TipIdx = tipIdx;

            Fs_QueueStartReadTim(FILE_TIM_TIPS_E01_TIM + tipIdx, FS_BUFFER_1, &g_DeathTipImg);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.5f), false);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.5f), false);
            SysWork_StateStepIncrement(0);

        case 3:
            Gfx_StringSetPosition(SCREEN_POSITION_X(32.5f), SCREEN_POSITION_Y(43.5f));
            Gfx_StringDraw("\aGAME_OVER", DEFAULT_MAP_MESSAGE_LENGTH);
            g_SysWork.field_28++;

            if ((g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                  g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)) ||
                g_SysWork.field_28 > Q12(1.0f / 17.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 4:
            Gfx_StringSetPosition(SCREEN_POSITION_X(32.5f), SCREEN_POSITION_Y(43.5f));
            Gfx_StringDraw("\aGAME_OVER", DEFAULT_MAP_MESSAGE_LENGTH);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(2.0f), false);
            break;

        case 5:
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
            {
                SysWork_StateStepReset();
                break;
            }
            else
            {
                Fs_QueueWaitForEmpty();
                Game_RadioSoundStop();
                SysWork_StateStepIncrement(0);
            }

        case 6:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(2.0f), false);
            g_SysWork.field_28 = Q12(0.0f);
            Gfx_BackgroundSpriteDraw(&g_DeathTipImg);
            break;

        case 7:
            g_SysWork.field_28++;
            Gfx_BackgroundSpriteDraw(&g_DeathTipImg);

            if (!(g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                   g_GameWorkPtr->config_0.controllerConfig_0.cancel_2)))
            {
                if (g_SysWork.field_28 <= 480)
                {
                    break;
                }
            }

            // TODO: some inline FlagSet func? couldn't get matching ver, but pretty sure temp_a0 can be removed somehow
            temp_a0 = &g_GameWork.config_0.seenGameOverTips_2E[(g_SysState_GameOver_TipIdx >> 5)];
            *temp_a0 |= (1 << 0) << (g_SysState_GameOver_TipIdx & 0x1F);

            SysWork_StateStepIncrement(0);
            break;

        case 8:
            Gfx_BackgroundSpriteDraw(&g_DeathTipImg);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(2.0f), false);
            break;

        default:
            g_MapOverlayHeader.unfreezePlayerControl_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            Game_WarmBoot();
            break;
    }

    if (g_SysWork.sysStateStep_C[0] >= 2 || g_GameWork.gameState_594 != GameState_InGame)
    {
        g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;
    }
}

void GameState_MapEvent_Update(void) // 0x8003AA4C
{
    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        g_IntervalVBlanks               = 1;
        ScreenFade_Start(true, true, false);
        g_GameWork.gameStateStep_598[0] = 1;
    }

    D_800A9A0C = ScreenFade_IsFinished() && Fs_QueueDoThingWhenEmpty();

    Savegame_EventFlagSetAlt(g_MapEventParam->disabledEventFlag_2);

    g_MapOverlayHeader.mapEventFuncs_20[g_MapEventIdx]();

    Gfx_BackgroundSpriteDraw(&g_ItemInspectionImg);
}
