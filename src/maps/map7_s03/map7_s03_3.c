#include <memory.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/dms.h"
#include "bodyprog/gfx/map_effects.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/memcard.h"
#include "bodyprog/player.h"
#include "bodyprog/ranking.h"
#include "bodyprog/sound/sound_system.h"
#include "main/rng.h"
#include "maps/map7/map7_s03.h"
#include "maps/characters/alessa.h"
#include "maps/characters/bloody_incubator.h"
#include "maps/characters/bloody_lisa.h"
#include "maps/characters/cybil.h"
#include "maps/characters/dahlia.h"
#include "maps/characters/incubator.h"
#include "maps/characters/incubus.h"
#include "maps/characters/kaufmann.h"
#include "maps/characters/unknown23.h"
#include "screens/credits/credits.h"

void func_800E0A34(void) // 0x800E0A34
{
    s_FsImageDesc tex;

    tex.tPage[0] = 0;
    tex.tPage[1] = 21;
    tex.u        = 0;
    tex.v        = 0;
    tex.clutX    = 48;
    tex.clutY    = 0;
    Fs_QueueStartReadTim(FILE_TIM_BOSEF00_TIM, FS_BUFFER_1, &tex);
}

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800E0A80

#include "maps/shared/Map_RoomIdxGet.h" // 0x800E0A90

void func_800E0B28(s32 arg0) // 0x800E0B28
{
    (arg0 != 0) ? func_800E0B90() : sharedFunc_800D0110_7_s00();
}

void func_800E0B5C(s32 arg0) // 0x800E0B5C
{
    (arg0 != 0) ? func_800E0C10() : sharedFunc_800D0110_7_s00();
}

void func_800E0B90(void) // 0x800E0B90
{
    s32 bgmIdx; // `e_BgmTrackIdx`

    if (g_SavegamePtr->mapRoomIdx == 3)
    {
        bgmIdx = BgmTrackIdx_15;
    }
    else if (Savegame_EventFlagGet(EventFlag_481))
    {
        if (!Savegame_EventFlagGet(EventFlag_574))
        {
            Savegame_EventFlagSet(EventFlag_574);
            bgmIdx = BgmTrackIdx_1;
        }
        else
        {
            bgmIdx = BgmTrackIdx_22;
        }
    }
    else
    {
        bgmIdx = BgmTrackIdx_14;
    }

    Bgm_TrackChange(bgmIdx);
}

void func_800E0C10(void) // 0x800E0C10
{
    Bgm_TrackChange(Savegame_EventFlagGet(EventFlag_391) ? 40 : 35);
}

#include "maps/shared/sharedFunc_800D0110_7_s00.h" // 0x800E0C50

void GameBoot_LoadScreen_StageString(void) {}

void func_800E14DC(s_SubCharacter* player, s_SubCharacter* otherChara, bool warpCamera) // 0x800E14DC
{
    VECTOR3 camTargetPos;
    VECTOR3 camLookAtTargetPos;
    bool    isCamUpdated;
    q19_12  angleToOtherChara;
    s32     vcPrsFViewFlag;

    isCamUpdated        = false;
    angleToOtherChara = ratan2(player->position.vx - otherChara->position.vx,
                               player->position.vz - otherChara->position.vz);

    vcPrsFViewFlag = (vcWork.flags & VC_PRS_F_VIEW_F) == VC_PRS_F_VIEW_F;
    if (((g_GameWorkConst->config.extraViewCtrl && (vcPrsFViewFlag ^ 1) != 0) ||
         (!g_GameWorkConst->config.extraViewCtrl && vcPrsFViewFlag)) &&
        (g_GameWorkConst->config.extraViewMode == 0))
    {
        isCamUpdated = true;

        camTargetPos.vx = player->position.vx +
                          Q12_MULT_FLOAT(Math_Sin(player->rotation.vy), 1.5f) +
                          Q12_MULT_FLOAT(Math_Sin(angleToOtherChara), 2.5f);
        camTargetPos.vz = player->position.vz +
                          Q12_MULT_FLOAT(Math_Cos(player->rotation.vy), 1.5f) +
                          Q12_MULT_FLOAT(Math_Cos(angleToOtherChara), 2.5f);

        if (otherChara->model.charaId == Chara_Incubus)
        {
            camTargetPos.vy = Q12(-1.4f);
        }
        else
        {
            camTargetPos.vy = Q12(-2.3f);
        }

        camLookAtTargetPos.vx = otherChara->position.vx + FP_FROM(Q12(Math_Sin(angleToOtherChara)), Q12_SHIFT);
        camLookAtTargetPos.vz = otherChara->position.vz + FP_FROM(Q12(Math_Cos(angleToOtherChara)), Q12_SHIFT);

        if (warpCamera)
        {
            camLookAtTargetPos.vy = Q12(-0.002f);
        }
        else if (otherChara->model.charaId == Chara_Incubus)
        {
            camLookAtTargetPos.vy = Vc_LookAtPositionYGet();
        }
        else
        {
            camLookAtTargetPos.vy = Q12(-0.8f);
        }
    }

    if (isCamUpdated)
    {
        vcUserCamTarget(&camTargetPos, NULL, warpCamera);
        vcUserWatchTarget(&camLookAtTargetPos, NULL, warpCamera);

        if (warpCamera)
        {
            vcExecCamera();
        }
    }
    else
    {
        vcReturnPreAutoCamWork(false);
    }
}

void func_800E16FC(void) // 0x800E16FC
{
    D_800F4B40.field_0  = NO_VALUE;
    D_800F4B40.timer  = Q12(0.0f);
    D_800F4B40.field_18[0] = 250;
    D_800F4B40.field_18[1] = 200;
    D_800F4B40.field_18[2] = 150;

    D_800F4B40.field_1C[0].vec_0 = &D_800F4B40.field_B8[0];
    D_800F4B40.field_1C[0].vec_8 = &D_800F4B40.field_B8[1];
    D_800F4B40.field_1C[1].vec_0 = &D_800F4B40.field_B8[2];
    D_800F4B40.field_1C[1].vec_8 = &D_800F4B40.field_B8[3];
    D_800F4B40.field_64[0].vec_0 = &D_800F4B40.field_B8[4];
    D_800F4B40.field_64[0].vec_8 = &D_800F4B40.field_B8[5];
    D_800F4B40.field_64[1].vec_0 = &D_800F4B40.field_B8[6];
    D_800F4B40.field_64[1].vec_8 = &D_800F4B40.field_B8[7];

    func_800E1788(0);
}

void func_800E1788(s32 arg0) // 0x800E1788
{
    if (arg0 != D_800F4B40.field_0)
    {
        D_800F4B40.field_0  = arg0;
        D_800F4B40.field_4  = 0;
        D_800F4B40.timer  = Q12(0.0f);
        D_800F4B40.field_C  = 0;
        D_800F4B40.timer_10 = Q12(0.0f);
    }
}

void func_800E17B8(s_800F4B40_1C* dest, s_800F4B40_1C* src) // 0x800E17B8
{
    VECTOR3* origVec0Ptr;
    VECTOR3* origVec1Ptr;

    // Backup original `VECTOR3` pointers.
    origVec0Ptr = dest->vec_0;
    origVec1Ptr = dest->vec_8;

    // Copy struct data.
    *dest = *src;

    // Restore `VECTOR3` pointers.
    dest->vec_0 = origVec0Ptr;
    dest->vec_8 = origVec1Ptr;

    // Copy `VECTOR3` data.
    *dest->vec_0 = *src->vec_0;
    *dest->vec_8 = *src->vec_8;
}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/map_msg_common.h"
    /* 15 */ "~J1(4.9)\tI_was_shocked_to_realize ~N\n\t\t\tthe_talisman_of_Metraton ~N\n\t\t\twas_being_used. ",
    /* 16 */ "~J1(4.0)\tIn_spite_of_the_lost_soul ~N\n\t\t\treturning_at_last, ",
    /* 17 */ "~J1(4.3)\tJust_a_little_longer_and_all ~N\n\t\t\twould_have_been_for_naught. ",
    /* 18 */ "~J1(7.0)\tIt's_all_because_of_that_man. ~N\n\t\t\tWe_must_be_thankful_to_him. ",
    /* 19 */ "~J1(3.2)\tEven_though_Alessa ~N\n\t\t\thas_been_stopped, ",
    /* 20 */ "~J1(8.5)\this_little_girl_still_has_to_go. ~N\n\t\t\tWhat_a_pity... ~E ",
    /* 21 */ "~J0(1.2)\tFreeze! ~E ",
    /* 22 */ "~J0(2.6)\tWhat_in_the_devil's_name...! ~E ",
    /* 23 */ "~J0(1.1)\t~E ",
    /* 24 */ "~J1(1.1)\tDahlia! ",
    /* 25 */ "~J1(5.6)\tWell,_well,_well. ~N\n\t\t\tTo_think_you'd_make_it_this_far. ",
    /* 26 */ "~J1(2.5)\tWhere's_Cheryl!? ~N\n\t\t\tWhat_have_you_done_to_her!? ",
    /* 27 */ "~J1(2.0)\tWhat_are_you_talking_about? ",
    /* 28 */ "~J1(4.8)\tYou've_seen_her_many_times. ~N\n\t\t\tRestored_to_her_former_self. ",
    /* 29 */ "~J1(2.4)\tI'm_in_no_mood_for_jokes. ~E ",
    /* 30 */ "~J0(3.4)\tDon't_you_see? ~N\n\t\t\tShe's_right_there. ~E ",
    /* 31 */ "~J1(1.8)\tThat's_absurd. ",
    /* 32 */ "~J1(4.5)\tYou_are_the_only_one ~N\n\t\t\twho_thinks_so. ",
    /* 33 */ "~J1(1.4)\tWhy? ",
    /* 34 */ "~J1(2.2)\tWhy_are_you_doing_this? ~E ",
    /* 35 */ "~J1(3.8)\tIt's_been_a_long_seven_years... ",
    /* 36 */ "~J1(4.4)\tFor_the_seven_years ~N\n\t\t\tsince_that_terrible_day, ",
    /* 37 */ "~J1(3.2)\tAlessa_has_been_kept_alive, ",
    /* 38 */ "~J1(3.9)\tsuffering_a_fate_worse ~N\n\t\t\tthan_death. ",
    /* 39 */ "~J1(6.5)\tAlessa_has_been_trapped ~N\n\t\t\tin_an_endless_nightmare ~N\n\t\t\tfrom_which_she_never_wakens. ",
    /* 40 */ "~J1(4.0)\tHe_has_been_nurtured ~N\n\t\t\tby_that_nightmare. ",
    /* 41 */ "~J1(3.6)\tWaiting_for ~N\n\t\t\tthe_day_to_be_born. ",
    /* 42 */ "~J1(3.6)\tThat_day_has_finally_come. ",
    /* 43 */ "~J1(2.9)\tThe_time_is_neigh. ~E ",
    /* 44 */ "~J1(5.1)\tEveryone_will_be_released, ~N\n\t\t\tfrom_pain_and_suffering. ",
    /* 45 */ "~J1(3.1)\tOur_salvation_is_at_hand. ",
    /* 46 */ "~J1(2.8)\tThis_is_the_day_of_reckoning. ",
    /* 47 */ "~J1(4.7)\tWhen_all_our_sorrows ~N\n\t\t\twill_be_washed_away. ",
    /* 48 */ "~J1(4.8)\tWhen_we_return_to ~N\n\t\t\tthe_true_paradise!  ~E ",
    /* 49 */ "~J0(6.2)\tMy_daughter_will_be ~N\n\t\t\tthe_mother_of_God! ~E ",
    /* 50 */ "~J0(4.0)\t~E ",
    /* 51 */ "~J1(1.7)\tQuit_screwing_around! ",
    /* 52 */ "~J1(2.4)\tReturn_things_to_how ~N\n\t\t\tthey_were_before! ",
    /* 53 */ "~J1(1.0)\tKaufmann! ",
    /* 54 */ "~J1(1.9)\tDid_I_ask_for_this! ",
    /* 55 */ "~J1(1.9)\tNobody_uses_me! ",
    /* 56 */ "~J1(3.0)\tYou_won't_get_away ~N\n\t\t\twith_this! ~E ",
    /* 57 */ "~J1(4.7)\tYour_role_is_over. ~N\n\t\t\tWe_don't_need_you_anymore. ",
    /* 58 */ "~J1(3.6)\tWhat_do_you_think_you_can ~N\n\t\t\taccomplish_by_coming_here? ",
    /* 59 */ "~J1(3.5)\tMy,_aren't_we_getting_cocky? ",
    /* 60 */ "~J1(3.2)\tBet_you_can't_see_this ~N\n\t\t\tand_keep_your_cool.  ~E ",
    /* 61 */ "~J0(3.5)\tAglaophotis! ~N\n\t\t\tI_thought_I_got_rid_of_that! ",
    /* 62 */ "~J0(3.2)\tAll_I_had_to_do_was_plant_it ~N\n\t\t\tsomewhere_for_you_to_find, ",
    /* 63 */ "~J0(3.9)\tYou_all,_well, ~N\n\t\t\tit_kept_you_busy. ",
    /* 64 */ "~J0(1.7)\tYou're_easy! ",
    /* 65 */ "~J0(2.4)\tAnd_there's_more ~N\n\t\t\twhere_this_came_from! ~E ",
    /* 66 */ "~J0(1.7)\tStop_it!!  ~E ",
    /* 67 */ "~J0(2.2)\t~E ",
    /* 68 */ "~J0(1.4)\t",
    /* 69 */ "~J2(1.2)\tWhat_the!? ~E ",
    /* 70 */ "~J0(10.4)\t~E ",
    /* 71 */ "~J0(3.0)\tWhat_on_earth? ~N\n\t\t\tThat's_not_supposed_to... ~E ",
    /* 72 */ "~J0(1.8)\t~E ",
    /* 73 */ "~J0(3.5)\t~E ",
    /* 74 */ "~J0(3.4)\tIt's_awakening! ~N\n\t\t\tIt's_awake! ",
    /* 75 */ "~J0(3.0)\tNow_no_one_can_interfere! ~E ",
    /* 76 */ "~J0(1.2)\tCheryl!! ",
    /* 77 */ "~J0(3.5)\tGive_up! ~N\n\t\t\tThat_person_no_longer_exists. ~E ",
    /* 78 */ "~J0(2.0)\tThis_is_a_God! ",
    /* 79 */ "~J2(4.9)\tDescended_among_us_to_reach_out ~N\n\t\t\tand_save_us! ~E ",
    /* 80 */ "~J0(13.2)\t_ ~E ",
    /* 81 */ "~J0(2.4)\t_ ~E ",
    /* 82 */ "~J0(1.3)\t_",
    /* 83 */ "~J0(1.1)\t_ ~E ",
    /* 84 */ "~J0(1.6)\tThank_you_daddy. ",
    /* 85 */ "~J0(1.4)\tGoodbye. ~E ",
    /* 86 */ "~J0(3.0)\tCheryl...? ~E ",
    /* 87 */ "~J0(2.3)\tCan't_be? ",
    /* 88 */ "~J0(2.2)\tYou_can't_leave_like_this... ",
    /* 89 */ "~J0(3.2)\tThis_can't_be_happening! ~N\n\t\t\tCheryl!? ~E ",
    /* 90 */ "~J0(1.4)\t...Cheryl!! ~E ",
    /* 91 */ "~J0(1.1)\t~E ",
    /* 92 */ "~J0(3.9)\t~E ",
    /* 93 */ "~J0(1.3)\tWait... ~E ",
    /* 94 */ "~J0(4.8)\t~E ",
    /* 95 */ "~J0(1.0)\t~E ",
    /* 96 */ "~J0(1.0)\t~E ",
    /* 97 */ "~J0(4.5)\t~E ",
    /* 98 */ "~J0(1.4)\tHarry. ",
    /* 99 */ "~J0(1.0)\tGo. ~E "
};

void func_800E1854(void) // 0x800E1854
{
    VECTOR3 sp10;
    VECTOR3 sp20;
    q19_12  var_v0;

    switch (D_800F4B40.field_0)
    {
        case NO_VALUE:
            return;

        case 0:
            func_800E1FE0(&D_800ED274[0]);
            break;

        case 1:
            if (D_800F4B40.field_4 == 0)
            {
                D_800F4B40.field_4 = 1;
                func_800E1FE0(&D_800ED274[1]);
            }
            break;

        case 2:
            if (D_800F4B40.field_4 == 0)
            {
                D_800F4B40.field_4 = 1;
                func_800E1FE0(&D_800ED274[2]);
            }
            break;

        case 3:
            switch (D_800F4B40.field_4)
            {
                case 0:
                    func_800E1FE0(&D_800ED274[3]);
                    D_800F4B40.field_4++;
                    break;

                case 1:
                    if (D_800F4B40.timer > Q12(0.6f))
                    {
                        D_800F4B40.field_4 = 2;
                        func_800E1FE0(&D_800ED274[4]);
                        D_800F4B40.timer = Q12(0.0f);
                    }
                    break;
            }
            break;

        case 5:
            if (D_800F4B40.field_4 == 0)
            {
                D_800F4B40.field_4 = 1;
                func_800E1FE0(&D_800ED274[5]);
            }
            break;

        case 6:
            if (D_800F4B40.field_4 == 0)
            {
                D_800F4B40.field_4 = 1;
                func_800E1FE0(&D_800ED274[6]);
            }
            break;

        case 7:
            D_800F4B30.vx = Q8_TO_Q12(g_SysWork.npcBoneCoordBuffer[1].workm.t[0]);
            D_800F4B30.vy = Q8_TO_Q12(g_SysWork.npcBoneCoordBuffer[1].workm.t[1]);
            D_800F4B30.vz = Q8_TO_Q12(g_SysWork.npcBoneCoordBuffer[1].workm.t[2]);

            if (D_800F4B40.field_4 == 0)
            {
                D_800F4B40.field_4 = 1;
                func_800E1FE0(&D_800ED274[7]);
            }
            break;

        case 8:
            D_800F4B30.vx = Q8_TO_Q12(g_SysWork.npcBoneCoordBuffer[1].workm.t[0]);
            D_800F4B30.vy = Q8_TO_Q12(g_SysWork.npcBoneCoordBuffer[1].workm.t[1]);
            D_800F4B30.vz = Q8_TO_Q12(g_SysWork.npcBoneCoordBuffer[1].workm.t[2]);

            if (D_800F4B40.field_4 == 0 && D_800F4B40.timer > Q12(0.5f))
            {
                D_800F4B40.field_4 = 1;
                func_800E1FE0(&D_800ED274[8]);
            }
            break;

        case 9:
            if (D_800F4B40.field_4 == 0)
            {
                D_800F4B40.field_4 = 1;
                func_800E1FE0(&D_800ED274[9]);
            }
            break;

        case 11:
            if (D_800F4B40.field_4 == 0)
            {
                D_800F4B40.field_4 = 1;
                func_800E1FE0(&D_800ED274[10]);
            }
            break;

        case 12:
            switch (D_800F4B40.field_4)
            {
                case 0:
                    D_800F4B40.field_4 = 1;
                    func_800E1FE0(&D_800ED274[11]);
                    break;

                case 1:
                    if (D_800F4B40.timer > Q12(3.5f))
                    {
                        D_800F4B40.field_4 = 2;
                        func_800E1FE0(&D_800ED274[12]);
                        D_800F4B40.timer = Q12(0.0f);
                    }
                    break;
            }
            break;

        case 13:
            switch (D_800F4B40.field_4)
            {
                case 0:
                    func_800E1FE0(&D_800ED274[13]);
                    D_800F4B40.field_4++;
                    break;

                case 1:
                    if (D_800F4B40.timer > Q12(2.0f))
                    {
                        func_800E1FE0(&D_800ED274[14]);
                        D_800F4B40.timer = Q12(0.0f);
                        D_800F4B40.field_4++;
                    }
                    break;

                case 2:
                    if (D_800F4B40.timer > Q12(3.0f))
                    {
                        D_800F4B40.timer = Q12(0.0f);
                        D_800F4B40.field_4++;
                    }
                    // @bug Missed `break` here?

                case 3:
                    if (D_800F4B40.timer > Q12(0.1f))
                    {
                        func_800E1FE0(&D_800ED274[15]);
                        D_800F4B40.timer = Q12(0.0f);
                        D_800F4B40.field_4++;
                    }
                    break;

                case 4:
                    if (D_800F4B40.timer > Q12(0.25f))
                    {
                        func_800E1FE0(&D_800ED274[14]);
                        D_800F4B40.timer = Q12(0.0f);
                        D_800F4B40.field_4--;
                    }
                    break;
            }
            break;

        case 14:
            if (D_800F4B40.field_4 == 0 && D_800F4B40.timer > Q12(4.0f))
            {
                func_800E1FE0(&D_800ED274[16]);
                D_800F4B40.field_4++;
            }
            break;

        case 15:
            if (D_800F4B40.field_4 == 0)
            {
                func_800E1FE0(&D_800ED274[17]);
                D_800F4B40.field_4++;
            }
            break;
    }

    switch (D_800F4B40.field_0)
    {
        case 4:
            if (D_800F4B40.field_C == 0)
            {
                D_800F4B40.field_C = 1;
                func_800DD7D0(&D_800ED244);
            }

            if (D_800F4B40.timer_10 < Q12(11.0f))
            {
                var_v0 = Q12(0.0f);
            }
            else
            {
                var_v0 = MIN(D_800F4B40.timer_10 - Q12(11.0f), Q12(6.0f)) / 6;
            }

            func_800E2664(Q12(1.8f), Q12_MULT_FLOAT(var_v0, 0.3f) + 245);
            func_800DD868();
            break;

        case 5:
            if (D_800F4B40.timer_10 < Q12(2.0f))
            {
                VECTOR3* srcPos = &g_SysWork.npcs[4].position;
                sp10            = *srcPos;
                sp10.vy        -= Q12(1.1f);

                D_800F4B40.field_C++;
                if (D_800F4B40.field_C % 2)
                {
                    func_800E27D0(Q12(4.0f), Q12(0.4f), 1, &sp10);
                }

                func_800E27D0(Q12(3.5f), Q12(1.0f), 0, &sp10);
                func_800E27D0(Q12(3.5f), Q12(0.5f), 0, &sp10);
                func_800DD868();
            }
            break;

        case 10:
            if (D_800F4B40.field_C == 0)
            {
                func_800DD8CC(&D_800ED244);
                D_800F4B40.field_C++;
            }

            if (D_800F4B40.timer_10 < Q12(2.0f))
            {
                sp20     = D_800ED250;
                sp20.vy -= Q12(3.81f);

                D_800F4B40.field_C++;
                if (D_800F4B40.field_C % 2)
                {
                    func_800E27D0(Q12(3.5f), Q12(0.5f), 1, &sp20);
                    func_800E27D0(Q12(3.5f), Q12(0.5f), 1, &sp20);
                }

                func_800E27D0(Q12(3.0f), Q12(1.0f), 0, &sp20);
                func_800E27D0(Q12(3.0f), Q12(0.5f), 0, &sp20);
                func_800DD868();
            }
            break;
    }

    func_800E20A4(&D_800F4B40.field_1C[0], &D_800F4B40.field_A4[0], D_800F4B40.field_5C, &D_800F4B40.field_64[0]);
    func_800E20A4(&D_800F4B40.field_1C[1], &D_800F4B40.field_A4[1], D_800F4B40.field_60, &D_800F4B40.field_64[1]);
    func_800E24A0(&D_800F4B40.field_1C[0]);
    func_800E24A0(&D_800F4B40.field_1C[1]);

    D_800F4B40.timer  += g_DeltaTime;
    D_800F4B40.timer_10 += g_DeltaTime;
}

void func_800E1FE0(s_func_800E1FE0* arg0) // 0x800E1FE0
{
    bzero(&D_800F4B40.field_A4[0], sizeof(D_800F4B40.field_A4[0]));
    bzero(&D_800F4B40.field_A4[1], sizeof(D_800F4B40.field_A4[1]));

    D_800F4B40.field_5C = &arg0->field_4[0];
    D_800F4B40.field_60 = &arg0->field_4[1];

    if (arg0->field_0 != 0)
    {
        func_800E17B8(&D_800F4B40.field_1C[0], &arg0->field_4[0]);
        func_800E17B8(&D_800F4B40.field_1C[1], &arg0->field_4[1]);
        func_800E17B8(&D_800F4B40.field_64[0], &arg0->field_4[0]);
        func_800E17B8(&D_800F4B40.field_64[1], &arg0->field_4[1]);
    }
    else
    {
        func_800E17B8(&D_800F4B40.field_64[0], &D_800F4B40.field_1C[0]);
        func_800E17B8(&D_800F4B40.field_64[1], &D_800F4B40.field_1C[1]);
    }
}

void func_800E20A4(s_800F4B40_1C* arg0, s_800F4B40_A4* arg1, s_800F4B40_1C* arg2, s_800F4B40_1C* arg3) // 0x800E20A4
{
    s32 var_v1;

    arg0->field_1E = arg2->field_1E;
    arg0->field_12 = func_800E2444(arg2->field_16, arg0->field_12, arg2->field_12);

    var_v1 = ABS((arg2->field_14 - arg3->field_14) / 15) + 1;
    if (arg0->field_14 > (arg2->field_14 + var_v1))
    {
        arg0->field_14 -= var_v1;
    }
    else if (arg0->field_14 < (arg2->field_14 - var_v1))
    {
        arg0->field_14 += var_v1;
    }
    else
    {
        arg0->field_14 = arg2->field_14;
    }

    arg1->now_spd_0 = vwRetNewVelocityToTargetVal(arg1->now_spd_0, arg0->pos_10, arg2->pos_10, Q12(0.586f), arg2->total_max_spd_18, Q12(1.9532f));
    arg0->pos_10   += Q12_MULT_PRECISE(arg1->now_spd_0, g_DeltaTime);

    // TODO: Rename the struct fields `field_8` etc passed here to match `func_800E22AC` param names.
    func_800E22AC(arg0->vec_0, &arg0->field_4, &arg1->field_8, &arg1->field_6, arg2->vec_0, arg2->field_4, arg3->vec_0, arg3->field_4, arg2->field_1C);
    func_800E22AC(arg0->vec_8, &arg0->field_C, &arg1->field_4, &arg1->field_2, arg2->vec_8, arg2->field_C, arg3->vec_8, arg3->field_C, arg2->field_1A);
}

void func_800E22AC(VECTOR3* arg0, s32* arg1, s16* mv_pos, s16* now_spd, VECTOR3* arg4, s32 arg5, VECTOR3* arg6, s32 arg7, s16 total_max_spd) // 0x800E22AC
{
    *now_spd = vwRetNewVelocityToTargetVal(*now_spd, *mv_pos, Q12(1.0f), Q12(2.0f), total_max_spd, Q12(10.0f));
    *mv_pos += Q12_MULT_PRECISE(*now_spd, g_DeltaTime);
    *arg1    = arg7 + Q12_MULT(*mv_pos, (arg5 - arg7));

    arg0->vx = arg6->vx + Q12_MULT(*mv_pos, (arg4->vx - arg6->vx));
    arg0->vy = arg6->vy + Q12_MULT(*mv_pos, (arg4->vy - arg6->vy));
    arg0->vz = arg6->vz + Q12_MULT(*mv_pos, (arg4->vz - arg6->vz));
}

q19_12 func_800E2444(q19_12 dampingRate, q19_12 current, q19_12 target) // 0x800E2444
{
    q19_12 delta;
    q19_12 step;
    q19_12 result;

    delta = current - target;
    step  = Q12_MULT_PRECISE(dampingRate, g_DeltaTime);
    if (step < delta)
    {
        result = current - step;
    }
    else
    {
        result = current + step;
        if (delta >= -step)
        {
            result = target;
        }
    }

    return result;
}

void func_800E24A0(s_800F4B40_1C* arg0) // 0x800E24A0
{
    VECTOR3 pos0; // Q19.12
    VECTOR3 pos1; // Q19.12
    DVECTOR screenPos0;
    DVECTOR screenPos1;
    s32     projDepth;
    q23_8   var_a1;

    if (arg0->pos_10 != Q12(0.0f) && arg0->field_12 != 0 && arg0->field_14 != 0)
    {
        SetRotMatrix(&GsWSMATRIX);
        SetTransMatrix(&GsWSMATRIX);

        pos0.vx = Q12_TO_Q8(arg0->vec_0->vx);
        pos0.vy = Q12_TO_Q8(arg0->vec_0->vy + arg0->field_4);
        pos0.vz = Q12_TO_Q8(arg0->vec_0->vz);

        pos1.vx = Q12_TO_Q8(arg0->vec_8->vx);
        pos1.vy = Q12_TO_Q8(arg0->vec_8->vy + arg0->field_C);
        pos1.vz = Q12_TO_Q8(arg0->vec_8->vz);

        projDepth = Vw_TransformAndProjectPoint(&pos0, &screenPos0) * 4;
        Vw_TransformAndProjectPoint(&pos1, &screenPos1);

        var_a1 = Q8(16.0f);
        if (arg0->field_1E != 0)
        {
            var_a1 = Q8(16384.0f) / MAX(projDepth, Q8(1.5f));
        }

        func_800E2968(D_800F4B40.field_118, 16, 6, &screenPos0, &screenPos1, 0,
                      Math_MulFixed(Q12_TO_Q8(arg0->pos_10), var_a1, Q12_SHIFT), Q12(0.0f), Q12(1.0f),
                      D_800F4B40.field_18, arg0->field_12, arg0->field_14);
        func_800E2C28(D_800F4B40.field_118, 16, 6, 1, 1);
    }
}

void func_800E2664(s32 arg0, s16 arg1) // 0x800E2664
{
    VECTOR3 pos1;
    VECTOR3 pos0;
    q19_12  angle;

    if (arg1 > Q12_ANGLE_NORM_U(func_800E28F4()))
    {
        VECTOR3* srcPos;
        srcPos = &g_SysWork.npcs[4].position;

        angle   = Q12_ANGLE_NORM_U(func_800E28F4());
        pos0.vx = srcPos->vx + Q12_MULT(Math_Sin(angle), arg0);
        pos0.vz = srcPos->vz + Q12_MULT(Math_Cos(angle), arg0);
        pos0.vy = ((func_800E28F4() % (arg0 * 2)) - arg0) - Q12(1.0f);

        pos1     = g_SysWork.npcs[4].position;
        pos1.vy -= Q12(1.1f);
        pos1.vx += Q12_MULT_FLOAT(Math_Sin(angle), 0.4f);
        pos1.vz += Q12_MULT_FLOAT(Math_Cos(angle), 0.4f);

        func_800DD738(&pos0, &pos1, Q12_ANGLE(54.0f), Q12(1.0f));
    }
}

void func_800E27D0(s32 arg0, s16 arg1, s32 arg2, VECTOR3* pos) // 0x800E27D0
{
    VECTOR3* srcPos;
    VECTOR3  pos0;
    q19_12   angle;

    if (arg2 != 0 || arg1 > Q12_ANGLE_NORM_U(func_800E28F4()))
    {
        angle = Q12_ANGLE_NORM_U(func_800E28F4());
        if (arg2 != 0)
        {
            srcPos  = &g_SysWork.npcs[1].position;
            pos0.vx = srcPos->vx - Q12(0.5f);
            pos0.vy = srcPos->vy - Q12(1.2f);
            pos0.vz = srcPos->vz;
        }
        else
        {
            // @hack Pointer to `position` needed for match, but doesn't work as a `VECTOR3*` variable?
            pos0.vx = (&g_SysWork.npcs[4].position)->vx + Q12_MULT(Math_Sin(angle), arg0);
            pos0.vz = (&g_SysWork.npcs[4].position)->vz + Q12_MULT(Math_Cos(angle), arg0);
            pos0.vy = (func_800E28F4() % (arg0 >> 1)) - (arg0 >> 2);
        }

        func_800DD738(pos, &pos0, Q12_ANGLE(180.0f), Q12(0.5f));
    }
}

q3_12 func_800E28F4(void) // 0x800E28F4
{
    if (g_DeltaTime != Q12(0.0f))
    {
        D_800ED73C = ((s32)(D_800ED740 * 0x7169AC35) >> 3) ^ 0xA547B39E;
        D_800ED740 = ((u32)(D_800ED73C * 0x892D719C) >> 3) ^ 0xC65A4B97;
    }

    return D_800ED73C & SHRT_MAX;
}

void func_800E2968(s_800F4B40_118* arg0, s32 colCount, s32 rowCount, DVECTOR* arg3, DVECTOR* arg4,
                   s32 arg5, s32 arg6, q19_12 angle0, q19_12 angle1, s_PrimColor* color, s32 arg10, u8 arg11) // 0x800E2968
{
    s_PrimColor color0;
    s32         i;
    s32         j;
    s32         temp_lo;
    q19_12      angle2;
    s32         temp_s3;
    s32         temp_s4;
    s32         temp_s5;
    s32         temp_v0;
    s32         colorComp;

    for (i = 0; i < rowCount; i++)
    {
        temp_lo = Q12(i) / (rowCount - 1);
        temp_v0 = vwOresenHokan(D_800ED744, ARRAY_SIZE(D_800ED744), temp_lo, 0, Q12(1.0f));

        colorComp = Q12_MULT(arg10, Q12_MULT(color->r, temp_v0));
        if (colorComp < arg11)
        {
            color0.r = colorComp;
        }
        else
        {
            color0.r = arg11;
        }

        colorComp = Q12_MULT(arg10, Q12_MULT(color->g, temp_v0));
        if (colorComp < arg11)
        {
            color0.g = colorComp;
        }
        else
        {
            color0.g = arg11;
        }

        colorComp = Q12_MULT(arg10, Q12_MULT(color->b, temp_v0));
        if (colorComp < arg11)
        {
            color0.b = colorComp;
        }
        else
        {
            color0.b = arg11;
        }

        temp_s5 = arg3->vx + Q12_MULT(temp_lo, arg4->vx - arg3->vx);
        temp_s4 = arg3->vy + Q12_MULT(temp_lo, arg4->vy - arg3->vy);
        temp_s3 = arg5 + Q12_MULT(temp_lo, arg6 - arg5);

        for (j = 0; j < colCount; j++)
        {
            s_800F4B40_118* temp_s1;
            temp_s1 = &arg0[(colCount * i) + j];

            *(s32*)&temp_s1->color_4 = *(s32*)&color0;

            angle2  = angle0;
            angle2 += FP_FROM((Q12(j) / (colCount - 1)) * (angle1 - angle2), Q12_SHIFT);

            temp_s1->x_0 = temp_s5 + Q12_MULT(temp_s3, Math_Cos(angle2));
            temp_s1->y_2 = temp_s4 + Q12_MULT(temp_s3, Math_Sin(angle2));
        }
    }
}

void func_800E2C28(s_800F4B40_118* arg0, s32 colCount, s32 rowCount, s32 zDepth, s32 arg4) // 0x800E2C28
{
    s32             row;
    s32             col;
    POLY_G4*        poly;
    GsOT_TAG*       ot;
    s_800F4B40_118* colData;
    DR_MODE*        drMode;

    poly = GsOUT_PACKET_P;
    ot   = &g_OrderingTable0[g_ActiveBufferIdx].org[zDepth];

    for (row = 0; row < rowCount - 1; row++)
    {
        for (col = 0; col < colCount - 1; col++, poly++)
        {
            colData = &arg0[(row * colCount) + col];

            *(s32*)&poly->x0 = *(s32*)&colData[0].x_0;
            *(s32*)&poly->r0 = *(s32*)&colData[0].color_4;
            *(s32*)&poly->x1 = *(s32*)&colData[1].x_0;
            *(s32*)&poly->r1 = *(s32*)&colData[1].color_4;

            // Fetch x2/x3 from same column in next row
            *(s32*)&poly->x2 = *(s32*)&colData[colCount + 0].x_0;
            *(s32*)&poly->r2 = *(s32*)&colData[colCount + 0].color_4;
            *(s32*)&poly->x3 = *(s32*)&colData[colCount + 1].x_0;
            *(s32*)&poly->r3 = *(s32*)&colData[colCount + 1].color_4;

            setPolyG4(poly);
            setSemiTrans(poly, 1);

            addPrim(ot, poly);
        }
    }

    GsOUT_PACKET_P = poly;

    drMode = poly;
    SetDrawMode(drMode, 0, 1, (arg4 & 3) << 5, NULL);
    GsOUT_PACKET_P = &drMode[1];
    addPrim(ot, drMode);
}

#include "maps/shared/Event_CutsceneTimerAdvance.h" // 0x800E2DF8

void Map_CutsceneObjectsUpdate(void) // 0x800E2E90
{
    if (g_Cutscene_Timer >= Q12(0.0f))
    {
        if (g_Cutscene_UpdateHero)
        {
            Dms_CharacterTransformGet(&g_SysWork.playerWork.player.position, &g_SysWork.playerWork.player.rotation, "HERO", g_Cutscene_Timer, D_800ED230[D_800F4806]);
        }
        if (g_Cutscene_UpdateSibyl)
        {
            Dms_CharacterTransformGet(&g_SysWork.npcs[0].position, &g_SysWork.npcs[0].rotation, "SIBYL", g_Cutscene_Timer, D_800ED230[D_800F4806]);
        }
        if (g_Cutscene_UpdateDaria)
        {
            Dms_CharacterTransformGet(&g_SysWork.npcs[1].position, &g_SysWork.npcs[1].rotation, "DARIA", g_Cutscene_Timer, D_800ED230[D_800F4806]);
        }
        if (g_Cutscene_UpdateArsia)
        {
            Dms_CharacterTransformGet(&g_SysWork.npcs[2].position, &g_SysWork.npcs[2].rotation, "ARSIA", g_Cutscene_Timer, D_800ED230[D_800F4806]);
        }
        if (g_Cutscene_UpdateKau)
        {
            Dms_CharacterTransformGet(&g_SysWork.npcs[3].position, &g_SysWork.npcs[3].rotation, "KAU", g_Cutscene_Timer, D_800ED230[D_800F4806]);
        }
        if (g_Cutscene_UpdateMar)
        {
            Dms_CharacterTransformGet(&g_SysWork.npcs[4].position, &g_SysWork.npcs[4].rotation, "MAR", g_Cutscene_Timer, D_800ED230[D_800F4806]);
        }
        if (g_Cutscene_UpdateBar)
        {
            Dms_CharacterTransformGet(&g_SysWork.npcs[5].position, &g_SysWork.npcs[5].rotation, "BAR", g_Cutscene_Timer, D_800ED230[D_800F4806]);
        }
        if (g_Cutscene_UpdateLitl)
        {
            Dms_CharacterTransformGet(&g_SysWork.npcs[0].position, &g_SysWork.npcs[0].rotation, "LITL", g_Cutscene_Timer, D_800ED230[D_800F4806]);
        }
        if (g_Cutscene_UpdateBos)
        {
            Dms_CharacterTransformGet(&g_SysWork.npcs[2].position, &g_SysWork.npcs[2].rotation, "BOS", g_Cutscene_Timer, D_800ED230[D_800F4806]);
        }
        if (g_Cutscene_UpdateBin)
        {
            Dms_CharacterTransformGet(&g_WorldObject_Bin.position, &g_WorldObject_Bin.rotation, "BIN", g_Cutscene_Timer, D_800ED230[D_800F4806]);
        }
        if (g_Cutscene_UpdateBaby)
        {
            Dms_CharacterTransformGet(&g_WorldObject_Baby.position, &g_WorldObject_Baby.rotation, "BABY", g_Cutscene_Timer, D_800ED230[D_800F4806]);
        }

        vcChangeProjectionValue(Dms_CameraTargetGet(&g_Cutscene_CameraPositionTarget, &g_Cutscene_CameraLookAtTarget, NULL, g_Cutscene_Timer, D_800ED230[D_800F4806]));
        vcUserCamTarget(&g_Cutscene_CameraPositionTarget, NULL, true);
        vcUserWatchTarget(&g_Cutscene_CameraLookAtTarget, NULL, true);

        // "LIGHT", cutscene light position?
        Dms_CharacterTransformGet(&g_SysWork.lightPosition, &D_800F47E8, "LIGHT", g_Cutscene_Timer, D_800ED230[D_800F4806]);

        // "L_INT", interior light or intersection point?
        Dms_CharacterTransformGet(&D_800F47D8, &D_800F47E8, "L_INT", g_Cutscene_Timer, D_800ED230[D_800F4806]);

        // Set light rotation.
        g_SysWork.lightRotation.vx = -ratan2(D_800F47D8.vy - g_SysWork.lightPosition.vy,
                                                  Math_Vector2MagCalcSafeQ6(D_800F47D8.vx - g_SysWork.lightPosition.vx,
                                                                      D_800F47D8.vz - g_SysWork.lightPosition.vz));
        g_SysWork.lightRotation.vy = ratan2(D_800F47D8.vx - g_SysWork.lightPosition.vx,
                                                 D_800F47D8.vz - g_SysWork.lightPosition.vz);
        g_SysWork.lightRotation.vz = Q12_ANGLE(0.0f);
    }
}

void func_800E3390(void) // 0x800E3390
{
    s32 i;

    if ((g_Controller0->clickedBtnFlags & g_GameWorkPtr->config.controllerConfig.skip) &&
        D_800F4805 > 0 && D_800F4805 < 4)
    {
        D_800F4805 = 5;
        Savegame_EventFlagClear(EventFlag_576);
        SD_Call(19);
    }

    switch (D_800F4805)
    {
        case 0:
            // Freeze player.
            Player_ControlFreeze();
            func_8003A16C();
            Gfx_MapInitMapEffectsUpdate(18, 18);
            func_8008D438();

            g_Cutscene_UpdateSibyl = false;
            g_Cutscene_UpdateDaria = false;
            g_Cutscene_UpdateArsia = false;
            g_Cutscene_UpdateKau   = false;
            g_Cutscene_UpdateMar   = false;
            g_Cutscene_UpdateBar   = false;
            g_Cutscene_UpdateLitl  = false;
            g_Cutscene_UpdateBos   = false;
            g_Cutscene_UpdateBin   = false;
            D_800F4811             = true;
            g_Cutscene_UpdateBaby  = false;
            D_800F4813 = 0;
            D_800F4814 = 0;
            D_800F4815 = 0;
            D_800F4816 = 0;
            D_800F4817 = 0;
            D_800F4818 = 0;
            D_800F4819 = 0;
            D_800F481A = 0;
            D_800F481B = 0;

            Anim_CharaTypeAnimInfoClear();
            WorldGfx_CharaLmBufferAssign(CHARA_FORCE_FREE_ALL);

            ScreenFade_ResetTimestep();
            g_SysWork.cutsceneBorderState    = 20;
            g_SysWork.sysFlags |= SysFlag_CutsceneActive;

            func_800E0A34();

            Fs_QueueStartRead(FILE_ANIM_LAST12_DMS, FS_BUFFER_20);
            Fs_QueueWaitForEmpty();
            Dms_HeaderFixOffsets(FS_BUFFER_20);

            D_800F4806 = 0;
            g_Cutscene_Timer = Q12(0.0f);

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            func_800E94AC();
            func_800E94F4();
            Anim_CharaTypeAnimInfoClear();

            Savegame_EventFlagSet(EventFlag_576);
            Savegame_EventFlagSet(EventFlag_591);
            D_800F4805++;

        case 1:
            if (Savegame_EventFlagGet(EventFlag_449))
            {
                func_800E3F30();
            }
            else
            {
                D_800F4805++;
                func_800E4714();
            }
            break;

        case 2:
            func_800E4714();
            break;

        case 3:
            if (Savegame_EventFlagGet(EventFlag_391))
            {
                func_800E514C();
            }
            else
            {
                func_800E70F0();
            }
            break;

        case 5:
            Event_ScreenFadeCmd(ScreenFadeCmd_Start, true, 0, Q12(0.0f), false);

            if (Savegame_EventFlagGet(EventFlag_391))
            {
                D_800F4805++;
                SysWork_StateStepSet(0, 0);
            }
            else
            {
                D_800F4805 += 2;
            }

        case 6:
            Bgm_CrossfadeToTrack(BgmTrackIdx_40);

            if (g_SysWork.sysStateSteps[0] != 0)
            {
                D_800F4805++;
            }
            break;

        case 7:
            if (ScreenFade_IsFinished())
            {
                D_800F4805++;
            }
            break;

        case 8:
            for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs); i++)
            {
                func_800E9490(&g_SysWork.npcs[i]);
            }

            if (Savegame_EventFlagGet(EventFlag_391))
            {
                if (!D_800F4815)
                {
                    Fs_QueueStartRead(FILE_ANIM_LAST3_DMS, FS_BUFFER_18);
                }

                Fs_QueueWaitForEmpty();
                Dms_HeaderFixOffsets(FS_BUFFER_18);

                if (!D_800F4816)
                {
                    Fs_QueueStartRead(FILE_ANIM_LAST4_DMS, FS_BUFFER_20);
                    Fs_QueueWaitForEmpty();
                }

                D_800F4806 = 1;

                if (D_800F4813 != 2)
                {
                    if (!D_800F4813)
                    {
                        WorldGfx_CharaLmBufferAssign(CHARA_FORCE_FREE_ALL);
                        func_800E9260(Chara_Incubus, 1);
                    }

                    func_800E941C();
                }

                func_800E9444(Chara_Incubus, &g_SysWork.npcs[2]);
                func_800DD9B0(&g_SysWork.npcs[2]);

                g_Cutscene_UpdateBaby  = false;
                D_800F4811             = false;
                g_Cutscene_UpdateBin   = false;
                g_Cutscene_UpdateLitl  = false;
                g_Cutscene_UpdateBar   = false;
                g_Cutscene_UpdateMar   = false;
                g_Cutscene_UpdateKau   = false;
                g_Cutscene_UpdateArsia = false;
                g_Cutscene_UpdateDaria = false;
                g_Cutscene_UpdateSibyl = false;
                g_Cutscene_UpdateBos   = true;
                g_Cutscene_Timer        = Q12(670.0f);
            }
            else
            {
                if (!D_800F4817)
                {
                    Fs_QueueStartRead(FILE_ANIM_LAST5_DMS, FS_BUFFER_18);
                }

                Fs_QueueWaitForEmpty();
                Dms_HeaderFixOffsets(FS_BUFFER_18);

                D_800F4806 = 1;
                if (D_800F4813 != 2)
                {
                    if (!D_800F4813)
                    {
                        WorldGfx_CharaLmBufferAssign(CHARA_FORCE_FREE_ALL);
                        func_800E9260(Chara_Incubator, 1);
                    }

                    func_800E941C();
                }

                func_800E9444(Chara_Incubator, &g_SysWork.npcs[4]);
                func_800E9498();

                g_Cutscene_UpdateBaby  = false;
                D_800F4811             = false;
                g_Cutscene_UpdateBin   = false;
                g_Cutscene_UpdateLitl  = false;
                g_Cutscene_UpdateBar   = false;
                g_Cutscene_UpdateBos   = false;
                g_Cutscene_UpdateKau   = false;
                g_Cutscene_UpdateArsia = false;
                g_Cutscene_UpdateDaria = false;
                g_Cutscene_UpdateSibyl = false;
                g_Cutscene_UpdateMar   = true;
                g_Cutscene_Timer        = Q12(68.0f);

                func_800DFB50(&g_SysWork.npcs[4]);
            }

            func_800D9394();
            Fs_QueueWaitForEmpty();

            g_Cutscene_UpdateHero = true;

            Model_AnimFlagsSet(&g_SysWork.playerWork.player.model, 2);
            Map_CutsceneObjectsUpdate();

            D_800F4805 = NO_VALUE;

            if (Savegame_EventFlagGet(EventFlag_391))
            {
                func_800E1788(-1);
            }
            else
            {
                func_800E1788(6);
            }

            Event_ScreenFadeCmd(ScreenFadeCmd_Start, false, 0, Q12(0.0f), false);

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);

            if (Savegame_EventFlagGet(EventFlag_391))
            {
                func_800DD9D4(&g_SysWork.npcs[2]);
            }
            else
            {
                func_800E9498();
                func_800DFB74(&g_SysWork.npcs[4]);
            }

            Savegame_EventFlagSet(EventFlag_577);

            Event_ScreenFadeCmd(ScreenFadeCmd_Start, false, 0, Q12(0.0f), false);
            Event_ScreenFadeCmd(ScreenFadeCmd_Start, false, 2, Q12(0.0f), false);

            g_Cutscene_Timer = NO_VALUE;

            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            SD_Call(19);
            func_800E14DC(&g_SysWork.playerWork.player, &g_SysWork.npcs[2], 1);

            D_800F4805               = 0;
            g_SysWork.lightIntensity = Q12(1.0f);
            break;
    }

    Map_CutsceneObjectsUpdate();

    if (g_Cutscene_UpdateMar && D_800F4805 == 3 && Savegame_EventFlagGet(EventFlag_391))
    {
        g_SysWork.npcs[4].rotation.vy += Q12_ANGLE(180.0f);
    }
}

void func_800E3B6C(void) // 0x800E3B6C
{
    switch (D_800F4805)
    {
        case 0:
            Player_ControlFreeze();

            g_SysWork.cutsceneBorderState          = 20;
            g_SysWork.sysStateSteps[0] = 0;
            g_SysWork.sysFlags       |= SysFlag_CutsceneActive;

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            func_8005E70C();

            D_800F4805++;

        case 1:
            func_800E62CC();
            break;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
            D_800F4805 = 0;
            Savegame_EventFlagSet(EventFlag_579);
            break;
    }

    Map_CutsceneObjectsUpdate();
}

void func_800E3C48(void) // 0x800E3C48
{
    switch (D_800F4805)
    {
        case 0:
            if (Savegame_EventFlagGet(EventFlag_449))
            {
                func_800E787C();
                Savegame_EventFlagSet(EventFlag_583);
                Savegame_EventFlagSet(EventFlag_587);
            }
            else
            {
                func_800E86BC();
                Savegame_EventFlagSet(EventFlag_585);
                Savegame_EventFlagSet(EventFlag_587);
            }
            g_SysWork.playerWork.player.health = Q12(100.0f);
            break;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
            D_800F4805 = 0;
            break;
    }

    D_800C48F0 += g_VBlanks;
    Map_CutsceneObjectsUpdate();
}

void func_800E3D18(void) // 0x800E3D18
{
    switch (D_800F4805)
    {
        case 0:
            Player_ControlFreeze();

            g_SysWork.playerWork.player.health = Q12(100.0f);
            g_SysWork.cutsceneBorderState                    = 20;
            g_SysWork.sysStateSteps[0]           = 0;
            g_SysWork.sysFlags                 |= SysFlag_CutsceneActive;

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            func_8005E70C();
            D_800F4805++;

        case 1:
            func_800E7380();
            break;

        case 2:
            if (Savegame_EventFlagGet(EventFlag_449))
            {
                D_800F4805 = 3;
                Savegame_EventFlagSet(EventFlag_584);
                break;
            }

            D_800F4805 = 3;

            Savegame_EventFlagSet(EventFlag_586);
            Sd_SfxStop(Sfx_Unk1688);
            Sd_SfxStop(Sfx_Unk1689);
            Sd_SfxStop(Sfx_Unk1690);

            D_800F4820 = 0;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
            D_800F4805 = 0;

            Savegame_EventFlagSet(EventFlag_587);
            break;
    }

    Map_CutsceneObjectsUpdate();
}

void func_800E3E84(void) // 0x800E3E84
{
    switch (D_800F4805)
    {
        case 0:
            g_SysWork.cutsceneBorderState = 20;
            g_SysWork.sysStateSteps[0]    = 0;
            D_800F4805                    = 1;
            g_SysWork.sysFlags           |= SysFlag_CutsceneActive;

        case 1:
            func_800E8D20();
            break;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_590);
            break;
    }

    Map_CutsceneObjectsUpdate();
}

void func_800E3F30(void) // 0x800E3F30
{
    typedef struct
    {
        SPRT*     sprt_0;
        DR_TPAGE* tpage_4;
        DR_STP*   stp_8;
        u8        unk_C[4];
        u8        unk_10[4];
        s32       activeBufferIdx_14;
    } g_GteScratchData_func_800DD2D4;

    g_GteScratchData_func_800DD2D4* scratchData;
    s32                             i;

    if (g_SysWork.sysStateSteps[0] == 0)
    {
        D_800EDA04 = 0;
    }

    if (D_800EDA04 != 0)
    {
        scratchData                     = PSX_SCRATCH_ADDR(0);
        scratchData->activeBufferIdx_14 = g_ActiveBufferIdx;
        scratchData->sprt_0             = (SPRT*)GsOUT_PACKET_P;

        for (i = 0; i < 2; i++)
        {
            setCodeWord(scratchData->sprt_0, PRIM_RECT | RECT_BLEND | RECT_TEXTURE, COLOR_RGBC(128, 128, 128, 0));
            setXY0Fast(scratchData->sprt_0, ((i << 8) - (SCREEN_WIDTH / 2)), -(FRAMEBUFFER_HEIGHT_PROGRESSIVE / 2));
            scratchData->sprt_0->u0 = 0;
            scratchData->sprt_0->v0 = (scratchData->activeBufferIdx_14 == 0) ? 32 : 0;
            setWH(scratchData->sprt_0, (i == 0) ? 256 : 64, FRAMEBUFFER_HEIGHT_PROGRESSIVE);
            addPrimFast(&g_OrderingTable2[g_ActiveBufferIdx].org[15], scratchData->sprt_0, 4);

            scratchData->sprt_0++;
            scratchData->tpage_4 = (DR_TPAGE*)scratchData->sprt_0;
            setDrawTPage(scratchData->tpage_4, 0, 0, getTPage(2, 0, ((scratchData->activeBufferIdx_14 << 4) + (i << 2)) << 6, (((scratchData->activeBufferIdx_14 << 4) >> 4) & 1) << 8));

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
    }

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            D_800F4804 = 0;

            func_800E9260(Chara_EndingCybil, 1);
            func_800E9260(Chara_Alessa, 2);
            func_800E9260(Chara_EndingDahlia, 3);
            func_800E941C();
            func_800E9444(Chara_EndingCybil, &g_SysWork.npcs[0]);
            func_800E9444(Chara_EndingDahlia, &g_SysWork.npcs[1]);
            func_800E9444(Chara_Alessa, &g_SysWork.npcs[2]);

            g_Cutscene_UpdateArsia = true;
            g_Cutscene_UpdateDaria = true;
            g_Cutscene_UpdateSibyl = true;

            g_SysWork.lightIntensity = Q12(0.7f);

            Model_AnimFlagsClear(&g_SysWork.playerWork.player.model, 2);

            SysWork_StateStepIncrement(0);
            D_800EDA04 = 0;
            break;

        case 1:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[0], 21, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[1], 5, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[2], 10, false);
            SysWork_StateStepIncrement(0);
            break;

        case 2:
            Event_CharaAnimCmdExecute(CharaAnimCmd_AnimLock, &g_SysWork.npcs[0], 0, false);
            SysWork_StateStepIncrement(0);

        case 3:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, false, 0, 0, false);
            break;

        case 4:
            Event_CharaAnimCmdExecute(CharaAnimCmd_AnimUnlock, &g_SysWork.npcs[0], 0, false);
            SysWork_StateStepIncrement(0);

        case 5:
            Event_DisplayMapMsgWithAudio(15, &D_800F4804, &D_800ED768);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(0.0f), Q12(16.0f), true, false);
            break;

        case 6:
            SysWork_StateStepIncrement(0);

        case 7:
            Event_DisplayMapMsgWithAudio(21, &D_800F4804, &D_800ED768);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(17.0f), Q12(31.0f), true, false);
            break;

        case 8:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(17.0f), Q12(31.0f), true, true);
            break;

        case 9:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[0], 22, false);
            SysWork_StateStepIncrement(0);

        case 10:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(32.0f), Q12(37.0f), false, true);
            break;

        case 11:
            Savegame_EventFlagClear(EventFlag_576);
            SysWork_StateStepIncrement(0);
            func_800D6804(&g_SysWork.npcs[1].position, &g_SysWork.npcs[0].position);

        case 12:
            Event_DisplayMapMsgWithAudio(22, &D_800F4804, &D_800ED768);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(32.0f), Q12(59.0f), true, false);
            func_800D6788();
            break;

        case 13:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[0], 23, false);
            SysWork_StateStepIncrement(0);

        case 14:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(32.0f), Q12(59.0f), true, false);
            func_800D6788();
            Event_SysStateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 15:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[0], 24, false);
            Event_DisplayMapMsgWithAudio(23, &D_800F4804, &D_800ED768);

            g_SysWork.lightIntensity = Q12(0.6f);
            D_800EDA04               = 1;

            SysWork_StateStepIncrement(0);

        case 16:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(61.0f), Q12(91.0f), true, true);
            break;

        case 17:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, true, 0, 0, false);
            break;

        default:
            g_SysWork.sysStateSteps[0] = 0;
            D_800F4805++;

            Model_AnimFlagsSet(&g_SysWork.playerWork.player.model, 2);
            func_800E9490(&g_SysWork.npcs[0]);

            g_Cutscene_UpdateSibyl = false;
            break;
    }
}

void func_800E4714(void) // 0x800E4714
{
    s32 temp_v0;

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            g_Cutscene_UpdateHero = true;
            D_800F4828 = 0;

            if (!Savegame_EventFlagGet(EventFlag_449))
            {
                func_800E9260(Chara_Alessa, 2);
                func_800E9260(Chara_EndingDahlia, 3);
                func_800E941C();
                func_800E9444(Chara_EndingDahlia, &g_SysWork.npcs[1]);
                func_800E9444(Chara_Alessa, &g_SysWork.npcs[2]);

                g_Cutscene_UpdateArsia = true;
                g_Cutscene_UpdateDaria = true;
            }

            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 153, false);

            D_800F4804 = 0;
            D_800EDA08 = 0;

            Savegame_EventFlagSet(EventFlag_592);
            g_SysWork.lightIntensity = Q12(0.8f);
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            if (!Savegame_EventFlagGet(EventFlag_449))
            {
                Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[1], 5, false);
                Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[2], 10, false);
            }

            SysWork_StateStepIncrement(0);

        case 2:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, false, 0, Q12(0.0f), false);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(92.0f), Q12(112.0f), true, false);
            break;

        case 3:
            Event_DisplayMapMsgWithAudio(24, &D_800F4804, &D_800ED77C);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(92.0f), Q12(112.0f), true, false);

            temp_v0 = Player_AnimPlaybackStateGet();
            if (temp_v0 == 1 && D_800EDA08 == 0)
            {
                Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 131, false);
                D_800EDA08 = temp_v0;
            }
            break;

        case 4:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[1], 15, false);
            SysWork_StateStepIncrement(0);

        case 5:
            Event_DisplayMapMsgWithAudio(30, &D_800F4804, &D_800ED77C);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(113.0f), Q12(129.0f), true, false);
            break;

        case 6:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(113.0f), Q12(129.0f), true, true);
            break;

        case 7:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 70, false);
            func_800E9260(Chara_Incubator, 1);
            D_800F4814 = 1;

            SysWork_StateStepIncrement(0);

        case 8:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(113.0f), Q12(134.0f), false, true);
            break;

        case 9:
            if (Fs_QueueChunksLoad())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 10:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 51, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[1], 16, false);
            SysWork_StateStepIncrement(0);

        case 11:
            Event_DisplayMapMsgWithAudio(31, &D_800F4804, &D_800ED77C);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(135.0f), Q12(142.0f), true, false);
            break;

        case 12:
            Event_DisplayMapMsgWithAudio(35, &D_800F4804, &D_800ED77C);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(135.0f), Q12(142.0f), true, false);
            break;

        case 13:
            Event_DisplayMapMsgWithAudio(44, &D_800F4804, &D_800ED77C);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(135.0f), Q12(142.0f), true, false);
            break;

        case 14:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[1], 6, false);
            SysWork_StateStepIncrement(0);

        case 15:
            Event_DisplayMapMsgWithAudio(49, &D_800F4804, &D_800ED77C);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(8.5f), Q12(143.0f), Q12(207.0f), true, false);

            Savegame_EventFlagClear(EventFlag_576);
            Savegame_EventFlagSet(EventFlag_593);
            Savegame_EventFlagSet(EventFlag_575);

            if (g_SysWork.sysStateSteps[0] != 15)
            {
                SD_Call(19);
            }
            break;

        case 16:
            SD_Call(Sfx_XaAudio600);
            SysWork_StateStepIncrement(0);

        case 17:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(8.5f), Q12(143.0f), Q12(207.0f), true, false);

            if (Sd_AudioStreamingCheck() == 1)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 18:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(8.5f), Q12(143.0f), Q12(207.0f), true, false);

            if (Sd_AudioStreamingCheck() == 1)
            {
                SysWork_StateStepIncrement(0);
            }
            else
            {
                break;
            }

        case 19:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 171, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[1], 18, false);
            func_800E1788(1);
            SysWork_StateStepIncrement(0);

        case 20:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(208.0f), Q12(231.0f), true, true);
            break;

        case 21:
            g_Cutscene_UpdateDaria = false;

            Model_AnimFlagsClear(&g_SysWork.npcs[1].model, 2);
            func_800E941C();
            func_800E9444(Chara_Incubator, &g_SysWork.npcs[4]);

            D_800F4814 = 2;

            Model_AnimFlagsClear(&g_SysWork.npcs[4].model, 2);
            SysWork_StateStepIncrement(0);

        case 22:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(232.0f), Q12(287.0f), false, true);

            if (g_Cutscene_Timer > Q12(230.0f))
            {
                if (D_800F481B == 0)
                {
                    Model_AnimFlagsClear(&g_SysWork.npcs[2].model, 2);
                    func_800E1788(2);
                    D_800F481B++;
                }
            }

            if (g_Cutscene_Timer > Q12(260.0f) && D_800F481B == 1)
            {
                D_800F481B++;
            }

            if (g_Cutscene_Timer > Q12(285.0f))
            {
                if (D_800F481B == 2)
                {
                    func_800E1788(3);
                    D_800F481B++;
                }
            }
            break;

        case 23:
            func_800E9490(&g_SysWork.npcs[2]);

            g_Cutscene_UpdateArsia = false;
            D_800F4811 = 0;

            SysWork_StateStepIncrement(0);

        case 24:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(232.0f), Q12(292.0f), false, true);
            break;

        case 25:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[4], 1, false);

            g_Cutscene_UpdateMar = true;

            Model_AnimFlagsSet(&g_SysWork.npcs[4].model, 2);
            func_800DD7D0(&g_SysWork.npcs[1].position);

            D_800F4828 = 1;

            SysWork_StateStepIncrement(0);

        case 26:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(232.0f), Q12(332.0f), false, true);
            break;

        case 27:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[4], 2, false);
            SysWork_StateStepIncrement(0);

        case 28:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(232.0f), Q12(341.0f), true, true);
            break;

        case 29:
            g_Cutscene_UpdateArsia = false;
            func_800D9394();

            if (Savegame_EventFlagGet(EventFlag_391))
            {
                Fs_QueueStartRead(FILE_ANIM_LAST3_DMS, FS_BUFFER_18);
                D_800F4815 = 1;
            }
            else
            {
                Fs_QueueStartRead(FILE_ANIM_LAST5_DMS, FS_BUFFER_18);
                D_800F4817 = 1;
            }

            SysWork_StateStepIncrement(0);

        case 30:
            Event_SysStateStepIncrementDelayed(Q12(4.0f), false);
            break;

        default:
            g_SysWork.sysStateSteps[0] = 0;
            D_800F4805++;
            break;
    }

    if (D_800F4828 != Q12(0.0f))
    {
        func_800DD868();
    }
}

void func_800E514C(void) // 0x800E514C
{
    VECTOR3 pos; // Q19.12
    s32     localRand;

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Fs_QueueWaitForEmpty();

            D_800F4804 = 0;

            Dms_HeaderFixOffsets(FS_BUFFER_18);

            D_800F4806 = 1;
            g_Cutscene_Timer = Q12(0.0f);

            func_800E9260(Chara_EndingKaufmann, 2);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 51, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[1], 19, false);

            Sfx_WithFlagsPlay(Sfx_Unk1670, &g_SysWork.npcs[1].position, Q8_CLAMPED(0.785f), SfxFlag_None);

            g_SysWork.lightIntensity = Q12(0.7f);

            Model_AnimFlagsSet(&g_SysWork.npcs[1].model, 2);

            Savegame_EventFlagClear(EventFlag_591);
            Savegame_EventFlagClear(EventFlag_592);
            Savegame_EventFlagClear(EventFlag_593);
            Savegame_EventFlagClear(EventFlag_575);
            Savegame_EventFlagSet(EventFlag_576);

            g_Cutscene_UpdateDaria = true;
            SysWork_StateStepIncrement(0);

        case 1:
            Bgm_CrossfadeToTrack(BgmTrackIdx_29);
            break;

        case 2:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(0.0f), Q12(12.0f), true, true);
            break;

        case 3:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(13.0f), Q12(37.0f), true, true);
            break;

        case 4:
            func_800E941C();
            func_800E9444(Chara_EndingKaufmann, &g_SysWork.npcs[3]);
            g_Cutscene_UpdateKau = true;

            SysWork_StateStepIncrement(0);
            break;

        case 5:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[3], 25, false);
            SysWork_StateStepIncrement(0);

        case 6:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(38.0f), Q12(51.0f), true, true);
            break;

        case 7:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(52.0f), Q12(58.0f), true, true);
            break;

        case 8:
            g_Cutscene_Timer = Q12(59.0f);

            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[3], 24, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[1], 20, false);
            Savegame_EventFlagSet(EventFlag_591);
            SysWork_StateStepIncrement(0);

        case 9:
            Event_DisplayMapMsgWithAudio(51, &D_800F4804, &D_800ED7B4);
            break;

        case 10:
            Event_CharaAnimPlayToEnd(&g_SysWork.npcs[1], 21);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(60.0f), Q12(78.0f), true, false);
            break;

        case 11:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[1], 22, false);
            SysWork_StateStepIncrement(0);

        case 12:
            Event_DisplayMapMsgWithAudio(57, &D_800F4804, &D_800ED7B4);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(60.0f), Q12(78.0f), true, false);
            break;

        case 13:
            Event_CharaAnimPlayToEnd(&g_SysWork.npcs[3], 18);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(79.0f), Q12(100.0f), true, true);
            break;

        case 14:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[3], 19, false);
            g_Cutscene_Timer = Q12(101.0f);
            SysWork_StateStepIncrement(0);

        case 15:
            Event_DisplayMapMsgWithAudio(61, &D_800F4804, &D_800ED7B4);
            break;

        case 16:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[1], 23, false);
            g_SysWork.lightIntensity = Q12(0.6f);
            Savegame_EventFlagClear(EventFlag_591);
            SysWork_StateStepIncrement(0);

        case 17:
            Event_DisplayMapMsgWithAudio(66, &D_800F4804, &D_800ED7B4);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(102.0f), Q12(116.0f), true, false);
            break;

        case 18:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(102.0f), Q12(116.0f), true, true);
            break;

        case 19:
            func_800E9490(&g_SysWork.npcs[1]);
            func_800E9490(&g_SysWork.npcs[4]);

            g_Cutscene_UpdateMar   = false;
            g_Cutscene_UpdateDaria = false;

            WorldGfx_CharaLmBufferAssign(1);
            func_800E9260(Chara_Incubator, 3);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[3], 20, false);

            g_SysWork.lightIntensity = Q12(0.7f);

            SysWork_StateStepIncrement(0);

        case 20:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(117.0f), Q12(156.0f), true, true);
            break;

        case 21:
            g_Cutscene_UpdateBin = true;
            D_800F482C = -0x772; // TODO: Unsure if FP?

            if (g_SysWork.sysStateSteps[0] != 18)
            {
                Savegame_EventFlagClear(EventFlag_576);
            }

            Bgm_PlayNewTrack(BgmTrackIdx_40);
            SysWork_StateStepIncrement(0);

        case 22:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(157.0f), Q12(193.0f), true, true);
            break;

        case 23:
            func_800E941C();
            func_800E9444(Chara_Incubator, &g_SysWork.npcs[4]);
            func_800E9260(Chara_BloodyIncubator, 1);
            SysWork_StateStepIncrement(0);

        case 24:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(7.5f), Q12(194.0f), Q12(280.0f), true, true);
            break;

        case 25:
            if (Fs_QueueChunksLoad())
            {
                SysWork_StateStepIncrement(0);
            }
            else
            {
                break;
            }

        case 26:
            g_Cutscene_UpdateMar = true;

            func_800E941C();
            func_800E9444(Chara_BloodyIncubator, &g_SysWork.npcs[5]);
            Model_AnimFlagsClear(&g_SysWork.npcs[5].model, 2);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[4], 2, false);
            WorldGfx_CharaModelTransparentSet(Chara_BloodyIncubator, false);

            g_SysWork.lightIntensity = Q12(0.6f);

            Sd_XaPreLoadAudioPreTaskAdd(Sfx_XaAudio606);
            SysWork_StateStepIncrement(0);

        case 27:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(281.0f), Q12(313.0f), false, true);
            break;

        case 28:
            SysWork_StateStepIncrement(0);

        case 29:
            SysWork_StateStepIncrement(0);

        case 30:
            SD_Call(Sfx_XaAudio606);
            SysWork_StateStepIncrement(0);

        case 31:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(281.0f), Q12(320.0f), true, false);
            if (Sd_AudioStreamingCheck() != 1)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 32:
            if (Sd_AudioStreamingCheck() != 1)
            {
                Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(281.0f), Q12(320.0f), true, false);
                break;
            }

            SysWork_StateStepIncrement(0);

        case 33:
            func_800D7144(&g_WorldObject_Bin.position);
            func_800E1788(9);
            SysWork_StateStepIncrement(0);

        case 34:
            g_Cutscene_Timer = Q12(321.0f);
            Event_SysStateStepIncrementDelayed(Q12(1.0f), false);

            g_Cutscene_UpdateBin = false;
            func_800D70EC();
            break;

        case 35:
            g_Cutscene_UpdateMar = false;

            func_800E9490(&g_SysWork.npcs[4]);

            g_Cutscene_UpdateBar = true;

            Model_AnimFlagsSet(&g_SysWork.npcs[5].model, 2);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[5], 1, false);
            SysWork_StateStepIncrement(0);

        case 36:
            if (!Sd_AudioStreamingCheck())
            {
                func_800E9260(Chara_EndingDahlia, 3);
                SysWork_StateStepIncrement(0);
            }

            func_800D70EC();
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(322.0f), Q12(391.0f), true, false);
            break;

        case 37:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(322.0f), Q12(391.0f), true, true);

            if (g_SysWork.sysStateSteps[0] != 37)
            {
                Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 51, false);
            }
            break;

        case 38:
            if (Fs_QueueChunksLoad())
            {
                SysWork_StateStepIncrement(0);
            }

            g_SysWork.lightIntensity = Q12(0.7f);
            g_Cutscene_Timer         = Q12(392.0f);
            break;

        case 39:
            Event_DisplayMapMsgWithAudio(68, &D_800F4804, &D_800ED7B4);
            Savegame_EventFlagSet(EventFlag_591);
            break;

        case 40:
            func_800E941C();
            func_800E9444(Chara_EndingDahlia, &g_SysWork.npcs[1]);
            SysWork_StateStepIncrement(0);
            break;

        case 41:
            g_Cutscene_UpdateDaria = true;
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[1], 22, false);

            g_SysWork.lightIntensity = Q12(0.6f);
            g_Cutscene_Timer         = Q12(393.0f);

            SysWork_StateStepIncrement(0);

        case 42:
            Event_DisplayMapMsgWithAudio(70, &D_800F4804, &D_800ED7B4);
            break;

        case 43:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[3], 22, false);

            g_SysWork.lightIntensity = Q12(0.7f);
            g_Cutscene_UpdateDaria   = false;

            func_800E9490(&g_SysWork.npcs[1]);
            SysWork_StateStepIncrement(0);

        case 44:
            Event_DisplayMapMsgWithAudio(71, &D_800F4804, &D_800ED7B4);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(394.0f), Q12(417.0f), true, false);
            break;

        case 45:
            func_800E9260(Chara_LittleIncubus, 3);
            SysWork_StateStepIncrement(0);

        case 46:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(394.0f), Q12(417.0f), true, true);
            break;

        case 47:
            if (Fs_QueueChunksLoad())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 48:
            func_800E941C();
            func_800E9444(Chara_LittleIncubus, g_SysWork.npcs);

            g_Cutscene_UpdateLitl = true;

            WorldGfx_CharaModelTransparentSet(Chara_BloodyIncubator, true);
            Savegame_EventFlagSet(EventFlag_576);

            g_SysWork.lightIntensity = Q12(0.5f);

            SysWork_StateStepIncrement(0);

        case 49:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(418.0f), Q12(498.0f), true, true);

            g_SysWork.field_28             += g_DeltaTime;
            g_SysWork.npcs[5].timer_C6 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, 0.0625f, 12);

            if (g_SysWork.field_28 > Q12(0.3f))
            {
                localRand           = Rng_Rand16();
                pos.vx              = g_SysWork.npcs[0].position.vx + Q12(0.2f);
                pos.vy              = g_SysWork.npcs[0].position.vy + Q12(-0.9f);
                pos.vz              = g_SysWork.npcs[0].position.vz + Q12(0.2f);
                g_SysWork.field_28 -= Q12(0.2f);
                g_SysWork.field_28 -= Rng_GenerateIntFromInput(localRand, 0, Q12(0.1f) - 1);

                func_8005F6B0(g_SysWork.npcs, &pos, 8, 1);
            }
            break;

        case 50:
            func_800E9490(&g_SysWork.npcs[5]);
            func_800E9490(&g_SysWork.npcs[0]);

            g_Cutscene_UpdateLitl = false;
            g_Cutscene_UpdateBar  = false;

            func_800E9260(Chara_Incubus, 1);

            D_800F4813 = 1;

            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 171, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[3], 24, false);
            func_8005E70C();

            g_SysWork.lightIntensity = Q12(0.7f);
            SysWork_StateStepIncrement(0);

        case 51:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(499.0f), Q12(509.0f), true, true);
            break;

        case 52:
            func_800E941C();
            func_800E9444(Chara_Incubus, &g_SysWork.npcs[2]);

            D_800F4813 = 2;
            g_Cutscene_UpdateBos = true;

            SysWork_StateStepIncrement(0);
            break;

        case 53:
            func_800DD9B0(&g_SysWork.npcs[2]);
            func_800E9260(Chara_EndingDahlia, 3);

            g_SysWork.lightIntensity = Q12(0.8f);

            SysWork_StateStepIncrement(0);

        case 54:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(510.0f), Q12(539.0f), true, true);
            break;

        case 55:
            func_800E941C();
            func_800E9444(Chara_EndingDahlia, &g_SysWork.npcs[1]);

            g_Cutscene_UpdateDaria = true;

            SysWork_StateStepIncrement(0);
            break;

        case 56:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 51, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[1], 28, false);

            g_SysWork.lightIntensity = Q12(0.9f);

            Fs_QueueStartRead(FILE_ANIM_LAST4_DMS, FS_BUFFER_20);

            D_800F4816 = 0;

            SysWork_StateStepIncrement(0);

        case 57:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(540.0f), Q12(586.0f), true, true);
            break;

        case 58:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(587.0f), Q12(615.0f), false, true);
            g_SysWork.lightIntensity = Q12(0.8f);
            break;

        case 59:
            func_800E1788(10);
            func_800DAD54();
            func_800DB288();
            SysWork_StateStepIncrement(0);

        case 60:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(587.0f), Q12(629.0f), false, true);
            break;

        case 61:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[1], 24, false);
            SysWork_StateStepIncrement(0);

        case 62:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(587.0f), Q12(730.0f), true, true);
            break;

        case 63:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, true, 0, Q12(0.0f), false);
            break;

        default:
            g_SysWork.sysStateSteps[0] = 0;
            D_800F4805++;

            func_800E9490(&g_SysWork.npcs[3]);
            func_800E9490(&g_SysWork.npcs[1]);

            g_Cutscene_UpdateKau   = false;
            g_Cutscene_UpdateDaria = false;

            WorldGfx_CharaLmBufferAssign(6);
            break;
    }

    if (g_SysWork.sysStateSteps[0] >= 62 && g_SysWork.sysStateSteps[0] < 64)
    {
        func_800DB154(&g_NpcBoneCoords[HarryBone_Root]);
    }
}

// Referenced by some .data struct?
const u8 g_rodata_800CC320[40] = { 0 };

INCLUDE_RODATA("maps/map7_s03/nonmatchings/map7_s03_3", D_800CC348);

void func_800E62CC(void) // 0x800E62CC
{
    VECTOR3         unused;
    s32             flags;
    s_800ED7E0_ptr* ptr;

    if (g_SysWork.sysStateSteps[0] >= 12)
    {
        func_80089500();
    }

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Dms_HeaderFixOffsets(FS_BUFFER_20);

            D_800F4806 = 0;
            g_Cutscene_Timer = Q12(0.0f);
            D_800F4804 = 0;

            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 182, false);
            func_800E9260(Chara_BloodyIncubator, 5);

            D_800F4820 = 0;

            Rng_SetSeed(0);

            g_SysWork.lightIntensity = Q12(1.0f);

            SysWork_StateStepIncrement(0);

        case 1:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(0.0f), Q12(24.0f), true, true);

            if (g_SysWork.sysStateSteps[0] != 1)
            {
                func_800E941C();
            }
            break;

        case 2:
            Sd_XaPreLoadAudioPreTaskAdd(Sfx_XaAudio596);
            Event_SysStateStepIncrementDelayed(Q12(0.3f), false);
            break;

        case 3:
            SD_Call(Sfx_XaAudio596);
            func_800DD9F8(&g_SysWork.npcs[2]);
            SysWork_StateStepIncrement(0);

        case 4:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(25.0f), Q12(175.0f), true, true);
            break;

        case 5:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 183, false);
            WorldGfx_CharaModelTransparentSet(Chara_Incubus, true);
            func_800E1788(11);
            SysWork_StateStepIncrement(0);

        case 6:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(176.0f), Q12(200.0f), false, true);
            break;

        case 7:
            func_800E9444(Chara_BloodyIncubator, &g_SysWork.npcs[5]);
            Model_AnimFlagsClear(&g_SysWork.npcs[5].model, 2);
            func_800E1788(12);
            SysWork_StateStepIncrement(0);

        case 8:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(176.0f), Q12(253.0f), true, true);

            g_SysWork.npcs[2].timer_C6 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime, 0.15f, 12);
            if (g_SysWork.npcs[2].timer_C6 > Q12(1.0f))
            {
                g_SysWork.npcs[2].timer_C6 = Q12(1.0f);
            }
            break;

        case 9:
            g_Cutscene_UpdateBar = true;
            Model_AnimFlagsSet(&g_SysWork.npcs[5].model, 2);

            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[5], 6, false);
            WorldGfx_CharaModelTransparentSet(Chara_BloodyIncubator, true);

            g_SysWork.npcs[5].timer_C6 = Q12(0.751f); // TODO: Odd value, possibly bad Q format.

            func_800E9490(&g_SysWork.npcs[2]);
            func_800E1788(13);

            g_Cutscene_UpdateBos = false;

            func_800D7E50(&g_SysWork.npcs[2].position);
            func_800D947C();

            Savegame_EventFlagSet(EventFlag_592);
            SysWork_StateStepIncrement(0);

        case 10:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(254.0f), Q12(314.0f), true, true);

            g_SysWork.npcs[5].timer_C6 -= Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.25f);
            if (g_SysWork.npcs[5].timer_C6 < 0)
            {
                g_SysWork.npcs[5].timer_C6 = 0;
            }
            break;

        case 11:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 174, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[5], 7, false);
            WorldGfx_CharaModelTransparentSet(Chara_BloodyIncubator, false);

            SysWork_StateStepIncrement(0);

            D_800F4820 = 1;
            D_800F4824 = 0;
            Savegame_EventFlagSet(EventFlag_593);

        case 12:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(315.0f), Q12(420.0f), true, true);
            break;

        case 13:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[5], 2, false);
            WorldGfx_PlayerHeldItemSet(InvItemId_CutsceneBaby);
            func_800E1788(14);
            SysWork_StateStepIncrement(0);

        case 14:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(421.0f), Q12(475.0f), true, true);
            break;

        case 15:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(476.0f), Q12(536.0f), true, false);
            SysWork_StateStepIncrement(0);
            break;

        case 16:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(476.0f), Q12(536.0f), true, true);
            break;

        case 17:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[5], 3, false);

            g_Cutscene_UpdateBaby = true;

            Sfx_WithFlagsPlay(Sfx_Unk1689, NULL, CHARA_FORCE_FREE_ALL, SfxFlag_Mono | SfxFlag_NoDistAtten);
            func_800E1788(15);
            SysWork_StateStepIncrement(0);

        case 18:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(537.0f), Q12(600.0f), true, true);
            break;

        case 19:
            Fs_QueueWaitForEmpty();
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 179, false);
            WorldGfx_CharaModelTransparentSet(Chara_BloodyIncubator, true);
            WorldGfx_CharaModelMaterialSet(Chara_BloodyIncubator, 0);

            g_Cutscene_UpdateBaby = false;

            func_8003D01C();
            SysWork_StateStepIncrement(0);

        case 20:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(601.0f), Q12(619.0f), false, true);
            break;

        case 21:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[5], 4, false);
            SysWork_StateStepIncrement(0);

        case 22:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(601.0f), Q12(635.0f), true, true);
            break;

        case 23:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(636.0f), Q12(653.0f), true, false);
            SysWork_StateStepIncrement(0);
            break;

        case 24:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(636.0f), Q12(653.0f), true, true);
            break;

        case 25:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 180, false);
            SysWork_StateStepIncrement(0);

        case 26:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(654.0f), Q12(721.0f), true, true);
            break;

        case 27:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[5], 8, false);

            if (Savegame_EventFlagGet(EventFlag_449))
            {
                func_800E9260(Chara_EndingCybil, 4);
            }
            else
            {
                func_800E9260(Chara_EndingKaufmann, 4);
            }

            Sd_SfxStop(Sfx_Unk1689);
            Sfx_WithFlagsPlay(Sfx_Unk1688, NULL, Q8_CLAMPED(1.0f), SfxFlag_Mono | SfxFlag_NoDistAtten);
            func_800D88C4();
            SysWork_StateStepIncrement(0);

        case 28:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(722.0f), Q12(752.0f), true, true);
            break;

        case 29:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 180, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[5], 9, false);
            Player_FlexRotationYReset();
            Savegame_EventFlagSet(EventFlag_593);
            SysWork_StateStepIncrement(0);

        case 30:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(753.0f), Q12(843.0f), true, true);
            break;

        case 31:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 181, false);
            SysWork_StateStepIncrement(0);

        case 32:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(844.0f), Q12(935.0f), true, true);
            break;

        case 33:
            if (Savegame_EventFlagGet(EventFlag_449))
            {
                func_800E941C();
                func_800E9444(Chara_EndingCybil, g_SysWork.npcs);

                g_Cutscene_UpdateSibyl = true;
                Model_AnimFlagsClear(&g_SysWork.npcs[0].model, 2);

                SysWork_StateStepIncrement(0);
            }
            else
            {
                SysWork_StateStepSet(0, 38);
            }
            break;

        case 34:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, g_SysWork.npcs, 26, false);
            Model_AnimFlagsSet(&g_SysWork.npcs[0].model, 2);
            func_800E9490(&g_SysWork.npcs[5]);
            func_800E9260(Chara_EndingKaufmann, 5);
            Sd_XaPreLoadAudioPreTaskAdd(Sfx_XaAudio657);

            g_Cutscene_UpdateBar = 0;

            SysWork_StateStepIncrement(0);

        case 35:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(936.0f), Q12(975.0f), true, true);
            break;

        case 36:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, g_SysWork.npcs, 25, false);
            SD_Call(Sfx_XaAudio657);
            func_800D7ED0();
            SysWork_StateStepIncrement(0);

        case 37:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(976.0f), Q12(1058.0f), true, true);

            if (g_SysWork.sysStateSteps[0] != 37)
            {
                SD_Call(19);
            }
            break;

        case 38:
            func_800E941C();
            func_800E9444(Chara_EndingKaufmann, &g_SysWork.npcs[3]);

            if (Savegame_EventFlagGet(EventFlag_449))
            {
                Fs_QueueStartRead(FILE_ANIM_ENDAA_DMS, FS_BUFFER_18);
            }
            else
            {
                Fs_QueueStartRead(FILE_ANIM_ENDBA_DMS, FS_BUFFER_18);
            }

            SysWork_StateStepIncrement(0);
            break;

        case 39:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[3], 21, false);
            g_Cutscene_UpdateKau = true;

            SysWork_StateStepIncrement(0);

        case 40:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(1059.0f), Q12(1122.0f), true, true);
            break;

        case 41:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, true, 0, 0, false);
            break;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
            func_800E9490(&g_SysWork.npcs[3]);

            g_Cutscene_UpdateKau = false;

            Sd_SfxStop(Sfx_Unk1688);

            D_800F4805++;
            break;
    }

    if (D_800F4820 != Q12(0.0f))
    {
        switch (D_800F4824)
        {
            case 0:
                if (g_Cutscene_Timer > Q12(700.0f))
                {
                    D_800F4824 = 1;
                }
                break;

            case 1:
                if (!(Rng_Rand16() & 0x70))
                {
                    func_800D7D74(0);
                }

                if (g_SysWork.sysStateSteps[0] >= 34)
                {
                    func_800D71A4(32);
                    D_800F4824++;
                }
                break;

            case 2:
                if (!(Rng_Rand16() & 0xF8))
                {
                    func_800D7D74(0);
                }
                break;
        }

        if (g_SysWork.sysStateSteps[0] >= 30 && g_SysWork.sysStateSteps[0] < 40)
        {
            if (g_SysWork.sysStateSteps[0] < 33)
            {
                D_800F4830 = 1;
            }
            else
            {
                D_800F4830 = 2;
                func_800D8858(1);
            }
        }
        else
        {
            D_800F4830 = 0;
        }

        ptr = D_800ED7E0[g_SysWork.sysStateSteps[0]];
        if (ptr)
        {
            do
            {
                unused.vx = ptr->field_0.vx >> 4; // @unused
                unused.vy = ptr->field_0.vy >> 4;
                unused.vz = ptr->field_0.vz >> 4;

                if (!(ptr->flags_38 & 2) || g_SysWork.sysStateSteps[0] != D_800EDA0C)
                {
                    func_800DA774(ptr);
                }

                flags = ptr->flags_38;
                ptr++;
            }
            while (flags & (1 << 0));
        }

        D_800EDA0C = g_SysWork.sysStateSteps[0];
    }
}

void func_800E70F0(void) // 0x800E70F0
{
    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Fs_QueueWaitForEmpty();
            Dms_HeaderFixOffsets((s_DmsHeader*)FS_BUFFER_18);

            D_800F4806 = 1;
            g_Cutscene_Timer = Q12(0.0f);
            D_800F4804 = 0;

            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 51, false);
            func_800E1788(4);

            Model_AnimFlagsSet(&g_SysWork.npcs[1].model, 2);
            g_SysWork.lightIntensity = Q12(0.8f);
            SysWork_StateStepIncrement(0);

        case 1:
            Event_DisplayMapMsgWithAudio(74, &D_800F4804, &D_800ED88C);
            break;

        case 2:
            Event_DisplayMapMsgWithAudio(76, &D_800F4804, &D_800ED88C);
            g_Cutscene_Timer = Q12(1.0f);
            break;

        case 3:
            Event_DisplayMapMsgWithAudio(78, &D_800F4804, &D_800ED88C);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(2.0f), Q12(33.0f), true, false);
            break;

        case 4:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[1], 17, false);
            Event_DisplayMapMsgWithAudio(80, &D_800F4804, &D_800ED88C);
            func_800E1788(5);
            func_800DAD54();
            func_800DB288();
            SysWork_StateStepIncrement(0);

        case 5:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(2.0f), Q12(41.0f), true, true);
            break;

        case 6:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(42.0f), Q12(68.0f), true, true);
            break;

        case 7:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, true, 0, Q12(0.0f), false);
            break;

        default:
            g_SysWork.sysStateSteps[0] = 0;
            D_800F4805++;

            func_800E9490(&g_SysWork.npcs[1]);

            g_Cutscene_UpdateDaria = false;
            break;
    }

    if (g_SysWork.sysStateSteps[0] >= 5 && g_SysWork.sysStateSteps[0] < 8)
    {
        func_800DB154(&g_NpcBoneCoords[HarryBone_Root]);
    }
}

INCLUDE_RODATA("maps/map7_s03/nonmatchings/map7_s03_3", D_800CC5C8);

void func_800E7380(void) // 0x800E7380
{
    s_800ED7E0_ptr* ptr;
    s32             flags;

    if (g_SysWork.sysStateSteps[0] >= 6 && g_SysWork.sysStateSteps[0] < 10)
    {
        func_80089500();
    }

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            D_800F4806 = 1;
            func_800E94AC();

            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 51, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[4], 3, false);

            D_800F4804 = 0;
            g_Cutscene_Timer = Q12(69.0f);

            SD_Call(Sfx_XaAudio602);

            g_SysWork.lightIntensity = Q12(0.8f);
            func_800E1788(7);
            SysWork_StateStepIncrement(0);

        case 1:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(6.8f), Q12(69.0f), Q12(143.0f), true, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_AwaitAnimEnd, &g_SysWork.npcs[4], 0, false);
            break;

        case 2:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(6.8f), Q12(69.0f), Q12(143.0f), true, true);

            if (g_SysWork.sysStateSteps[0] != 2)
            {
                SD_Call(19);
            }
            break;

        case 3:
            g_Cutscene_Timer = Q12(144.0f);
            Event_DisplayMapMsgWithAudio(82, &D_800F4804, &D_800ED898);
            break;

        case 4:
            Event_DisplayMapMsgWithAudio(84, &D_800F4804, &D_800ED898);
            break;

        case 5:
            func_800E9260(Chara_EndingCybil, 5);
            func_800D7E50(&g_SysWork.playerWork.player.position);
            func_800D947C();

            D_800F4824 = 0;
            D_800F4820 = 1;

            func_800E1788(8);
            SysWork_StateStepIncrement(0);

        case 6:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(12.0f), Q12(145.0f), Q12(201.0f), true, true);

            g_SysWork.npcs[4].timer_C6 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.25f);
            if (g_SysWork.npcs[4].timer_C6 > Q12(1.0f))
            {
                g_SysWork.npcs[4].timer_C6 = Q12(1.0f);
            }
            break;

        case 7:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 162, false);
            g_SysWork.lightIntensity = Q12(0.7f);
            func_800E9490(&g_SysWork.npcs[4]);
            g_Cutscene_UpdateMar = false;
            SysWork_StateStepIncrement(0);

        case 8:
            Event_DisplayMapMsgWithAudio(86, &D_800F4804, &D_800ED898);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(6.5f), Q12(202.0f), Q12(301.0f), true, false);
            break;

        case 9:
            Event_DisplayMapMsgWithAudio(87, &D_800F4804, &D_800ED898);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(6.5f), Q12(202.0f), Q12(301.0f), true, false);
            break;

        case 10:
            Event_DisplayMapMsgWithAudio(90, &D_800F4804, &D_800ED898);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(6.5f), Q12(202.0f), Q12(301.0f), true, false);
            break;

        case 11:
            if (Savegame_EventFlagGet(EventFlag_449))
            {
                Fs_QueueStartRead(FILE_ANIM_ENDC_DMS, FS_BUFFER_20);
            }

            SysWork_StateStepIncrement(0);

        case 12:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, true, 0, Q12(0.0f), false);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(6.5f), Q12(202.0f), Q12(301.0f), true, false);
            break;

        default:
            g_SysWork.sysStateSteps[0] = 0;
            D_800F4805++;
            Event_ScreenFadeCmd(ScreenFadeCmd_Start, false, 2, Q12(0.0f), false);
            break;
    }

    if (D_800F4820 != 0)
    {
        func_800D7EF0();

        if (D_800F4820)
        {
            ptr = D_800ED8B0[g_SysWork.sysStateSteps[0]];
            if (ptr != NULL)
            {
                do
                {
                    if (!(ptr->flags_38 & 2) || g_SysWork.sysStateSteps[0] != D_800ED8AC)
                    {
                        func_800DA774(ptr);
                    }

                    flags = ptr->flags_38;
                    ptr++;
                }
                while (flags & (1 << 0));
            }

            D_800ED8AC = g_SysWork.sysStateSteps[0];
        }
    }
}

INCLUDE_RODATA("maps/map7_s03/nonmatchings/map7_s03_3", D_800CC63C);

void func_800E787C(void) // 0x800E787C
{
    s_800ED7E0_ptr* ptr;
    s32             flags;

    if (g_SysWork.sysStateSteps[0] == 31)
    {
        sharedFunc_800D08B8_0_s00(2, 127);
    }

    if (g_SysWork.sysStateSteps[0] >= 31)
    {
        Particle_SystemUpdate(0, g_SavegamePtr->mapIdx, g_SysWork.sysStateSteps[0] != 31);
    }

    if (g_SysWork.sysStateSteps[0] >= 1 && g_SysWork.sysStateSteps[0] < 14)
    {
        func_80089500();
    }

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Bgm_CrossfadeToTrack(BgmTrackIdx_35);
            break;

        case 1:
            Fs_QueueWaitForEmpty();
            Dms_HeaderFixOffsets(FS_BUFFER_18);
            D_800F4806 = 1;
            g_Cutscene_Timer = Q12(0.0f);

            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 176, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[0], 2, false);

            Fs_QueueStartRead(FILE_ANIM_ENDAB_DMS, FS_BUFFER_20);

            func_800E9260(Chara_BloodyIncubator, 5);
            D_800F4819 = 1;
            D_800F481A = 1;

            Model_AnimFlagsClear(&g_SysWork.npcs[5].model, 2);
            func_800D7E50(&g_SysWork.playerWork.player.position);

            func_800D947C();
            D_800F4824 = 0;
            D_800F4820 = 1;
            D_800F4834 = 0;
            D_800F4838 = 1;

            Sfx_WithFlagsPlay(Sfx_Unk1688, NULL, Q8_CLAMPED(1.0f), SfxFlag_Mono | SfxFlag_NoDistAtten);

            SysWork_StateStepIncrement(0);

        case 2:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, false, 0, Q12(0.0f), false);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(0.0f), Q12(64.0f), true, false);
            break;

        case 3:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(0.0f), Q12(64.0f), false, true);
            break;

        case 4:
            Sfx_WithFlagsPlay(Sfx_Unk1694, NULL, Q8_CLAMPED(1.0f), SfxFlag_Mono | SfxFlag_NoDistAtten);
            Sfx_WithFlagsPlay(Sfx_Unk1695, NULL, Q8_CLAMPED(1.0f), SfxFlag_Mono | SfxFlag_NoDistAtten);
            SysWork_StateStepIncrement(0);

        case 5:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(0.0f), Q12(68.0f), true, true);
            break;

        case 6:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 177, false);
            Sfx_WithFlagsPlay(Sfx_Unk1694, NULL, Q8_CLAMPED(1.0f), SfxFlag_Mono | SfxFlag_NoDistAtten);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[0], 27, false);
            SD_Call(Sfx_XaAudio612);
            D_800F4819 = 2;
            SysWork_StateStepIncrement(0);

        case 7:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(69.0f), Q12(89.0f), true, true);
            break;

        case 8:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 184, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[0], 29, false);
            SysWork_StateStepIncrement(0);

        case 9:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(90.0f), Q12(98.0f), true, true);
            break;

        case 10:
            GameFs_StfRollBinLoad();
            SysWork_StateStepIncrement(0);

        case 11:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, true, 1, Q12(0.5f), false);
            break;

        case 12:
            func_800D88D8();
            func_800D7CF8();
            D_800F4834 = 1;
            Sd_SfxStop(Sfx_Unk1688);
            Sfx_WithFlagsPlay(Sfx_Unk1689, NULL, Q8_CLAMPED(1.0f), SfxFlag_Mono | SfxFlag_NoDistAtten);
            SysWork_StateStepIncrement(0);

        case 13:
            Savegame_EventFlagSet(EventFlag_575);

            if (!Sd_AudioStreamingCheck())
            {
                func_800E941C();
                func_800E9444(Chara_BloodyIncubator, &g_SysWork.npcs[5]);
                Model_AnimFlagsClear(&g_SysWork.npcs[5].model, 2);
                func_801E2E28(D_800F481C);
                SysWork_StateStepIncrement(0);
            }
            else
            {
                break;
            }

        case 14:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 178, false);
            Event_ScreenFadeCmd(ScreenFadeCmd_Start, false, 1, Q12(0.5f), false);
            SysWork_StateStepIncrement(0);

        case 15:
            if (func_801E2ED8())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 16:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(99.0f), Q12(154.0f), true, true);
            break;

        case 17:
            D_800F4806 = 0;
            g_Cutscene_Timer = Q12(0.0f);

            Dms_HeaderFixOffsets(FS_BUFFER_20);

            g_Cutscene_UpdateBar   = true;
            g_Cutscene_UpdateSibyl = false;
            g_Cutscene_UpdateHero  = false;

            Model_AnimFlagsSet(&g_SysWork.npcs[5].model, 2);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 51, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[0], 5, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[5], 9, false);
            WorldGfx_CharaModelTransparentSet(Chara_BloodyIncubator, true);

            g_SysWork.playerWork.player.position.vx = Q12(140.0f);
            g_SysWork.playerWork.player.position.vz = Q12(-100.0f);

            D_800F4819 = 0;
            D_800F481A = 0;
            D_800F4838 = 0;
            D_800F4824 = 0;

            Model_AnimFlagsClear(&g_SysWork.playerWork.player.model, 2);
            func_800D7E50(&g_SysWork.playerWork.player.position);

            SysWork_StateStepIncrement(0);
            Rng_SetSeed(0);

        case 18:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(0.0f), Q12(60.0f), true, true);
            break;

        case 19:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, true, 0, Q12(0.0f), false);
            break;

        case 20:
            D_800F4806 = 1;
            g_Cutscene_UpdateBar   = false;
            g_Cutscene_UpdateSibyl = true;
            g_Cutscene_UpdateHero  = true;
            g_Cutscene_Timer        = Q12(155.0f);

            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 176, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[0], 2, false);

            D_800F4819 = 1;

            Model_AnimFlagsSet(&g_SysWork.playerWork.player.model, 2);

            Event_ScreenFadeCmd(ScreenFadeCmd_Start, false, 0, Q12(0.0f), false);
            Gfx_MapEffectsUpdate(17, 17, PrimitiveType_S32, &D_800F483C, 0, Q12(100.0f));

            D_800F483C = Q12(40.0f);
            D_800F4838 = 1;
            D_800F4824 = 0;

            func_800D7E50(&g_SysWork.playerWork.player.position);
            SysWork_StateStepIncrement(0);

        case 21:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(155.0f), Q12(224.0f), true, true);
            D_800F483C += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 3.0f);
            break;

        case 22:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, true, 0, Q12(0.0f), false);
            D_800F483C += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 3.0f);
            break;

        case 23:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[5], 9, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 51, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[0], 5, false);

            D_800F483C = Q12(100.0f);

            Gfx_MapInitMapEffectsUpdate(9, 9);

            D_800F4806           = false;
            g_Cutscene_Timer      = Q12(61.0f);
            g_Cutscene_UpdateBar = true;

            g_SysWork.playerWork.player.position.vx = Q12(140.0f);
            g_SysWork.playerWork.player.position.vz = Q12(-100.0f);

            g_Cutscene_UpdateSibyl = false;
            g_Cutscene_UpdateHero  = false;
            D_800F4819 = 0;

            Model_AnimFlagsClear(&g_SysWork.playerWork.player.model, 2);

            Event_ScreenFadeCmd(ScreenFadeCmd_Start, false, 0, Q12(0.0f), false);
            func_800D7E50(&g_SysWork.playerWork.player.position);
            SysWork_StateStepIncrement(0);

        case 24:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(61.0f), Q12(77.0f), false, true);
            break;

        case 25:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[5], 10, false);
            SysWork_StateStepIncrement(0);

        case 26:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(61.0f), Q12(84.0f), false, true);
            break;

        case 27:
            D_800F4824 = 0;

            func_800D88CC();
            func_800D7CEC();

            D_800F4838 = 0;
            D_800F4834 = 0;

            Sd_SfxStop(Sfx_Unk1689);
            Sfx_WithFlagsPlay(Sfx_Unk1690, NULL, Q8_CLAMPED(1.0f), SfxFlag_Mono | SfxFlag_NoDistAtten);
            SysWork_StateStepIncrement(0);

        case 28:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(61.0f), Q12(95.0f), true, true);
            break;

        case 29:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(96.0f), Q12(121.0f), true, true);
            break;

        case 30:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, true, 0, Q12(0.0f), false);
            break;

        case 31:
            D_800F4806 = 1;
            D_800F4820 = 0;

            func_800D7E50(&g_SysWork.playerWork.player.position);
            Sd_SfxStop(Sfx_Unk1690);

            g_Cutscene_UpdateBar   = false;
            g_Cutscene_UpdateSibyl = true;
            g_Cutscene_UpdateHero  = true;
            g_Cutscene_Timer        = Q12(225.0f);

            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 176, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[0], 2, false);

            D_800F4819 = 0;
            D_800F4818 = 1;

            Model_AnimFlagsSet(&g_SysWork.playerWork.player.model, 2);
            Gfx_MapInitMapEffectsUpdate(9, 9);
            Gfx_MapEffectsUpdate(17, 17, PrimitiveType_S32, &D_800F483C, 0, Q12(100.0f));
            Event_ScreenFadeCmd(ScreenFadeCmd_Start, false, 0, Q12(0.0f), false);
            D_800F483C = Q12(80.0f);
            SysWork_StateStepIncrement(0);

        case 32:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(225.0f), Q12(259.0f), true, true);
            D_800F483C += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 10.0f);
            if (D_800F483C > Q12(100.0f))
            {
                D_800F483C = Q12(100.0f);
            }
            break;

        case 33:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(260.0f), Q12(325.0f), false, true);

            D_800F483C += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 10.0f);
            if (D_800F483C > Q12(100.0f))
            {
                D_800F483C = Q12(100.0f);
            }
            break;

        case 34:
            Event_ScreenFadeCmd(ScreenFadeCmd_Start, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 35:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, true, 1, Q12(0.4f), false);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(260.0f), Q12(340.0f), true, false);
            break;

        default:
            D_800F4818 = 0;
            D_800F4820 = 0;

            g_SysWork.sysStateSteps[0] = 0;

            D_800F483C = Q12(100.0f);
            D_800F4805++;

            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            func_800E9490(&g_SysWork.npcs[0]);
            break;
    }

    if (D_800F4820 != 0)
    {
        switch (D_800F4824)
        {
            case 0:
                D_800F4824 = 1;

            case 1:
                if (!D_800F4834 && !(Rng_Rand16() & 0x70))
                {
                    func_800D7D74(0);
                }
                break;
        }

        if (D_800F4820)
        {
            ptr = D_800ED8EC[g_SysWork.sysStateSteps[0]];
            if (ptr)
            {
                do
                {
                    if (!(ptr->flags_38 & 2) || g_SysWork.sysStateSteps[0] != D_800ED8E8)
                    {
                        func_800DA774(ptr);
                    }

                    flags = ptr->flags_38;
                    ptr++;
                }
                while (flags & (1 << 0));
            }

            D_800ED8E8 = g_SysWork.sysStateSteps[0];
        }
    }

    if (g_SysWork.sysStateSteps[0] >= 1 && g_SysWork.sysStateSteps[0] < 7)
    {
        D_800F4830 = 3;
    }
    else
    {
        D_800F4830 = 0;
    }
}

INCLUDE_RODATA("maps/map7_s03/nonmatchings/map7_s03_3", D_800CCD20);

void func_800E86BC(void) // 0x800E86BC
{
    s_800ED7E0_ptr* ptr;
    s32             flags;

    if (g_SysWork.sysStateSteps[0] == 8)
    {
        sharedFunc_800D08B8_0_s00(2, 127);
    }

    if (g_SysWork.sysStateSteps[0] >= 8)
    {
        Particle_SystemUpdate(0, g_SavegamePtr->mapIdx, g_SysWork.sysStateSteps[0] != 8);
    }

    if (g_SysWork.sysStateSteps[0] >= 1 && g_SysWork.sysStateSteps[0] < 6)
    {
        func_80089500();
    }

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Bgm_CrossfadeToTrack(BgmTrackIdx_35);
            break;

        case 1:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 176, false);

            Dms_HeaderFixOffsets(FS_BUFFER_18);
            Fs_QueueStartRead(FILE_ANIM_ENDBB_DMS, FS_BUFFER_20);

            D_800F4806 = 1;
            g_Cutscene_UpdateHero = true;
            g_Cutscene_UpdateBar  = false;
            D_800F4819 = 1;
            D_800F481A = 1;

            Event_ScreenFadeCmd(ScreenFadeCmd_Start, false, 0, Q12(0.0f), false);
            func_800D7E50(&g_SysWork.playerWork.player.position);
            func_800D947C();
            D_800F4824 = 0;
            D_800F4820 = 1;
            D_800F4838 = 1;

            GameFs_StfRollBinLoad();
            WorldGfx_CharaModelTransparentSet(Chara_BloodyIncubator, true);
            SysWork_StateStepIncrement(0);

        case 2:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(0.0f), Q12(89.0f), true, true);
            break;

        case 3:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(90.0f), Q12(160.0f), true, true);
            break;

        case 4:
            Fs_QueueWaitForEmpty();
            Dms_HeaderFixOffsets(FS_BUFFER_20);

            D_800F4806 = 0;
            g_Cutscene_Timer       = Q12(0.0f);
            g_Cutscene_UpdateHero = false;
            g_Cutscene_UpdateBar  = true;
            D_800F4819 = 0;
            D_800F481A = 0;

            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 51, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[5], 11, false);

            g_SysWork.playerWork.player.position.vx = Q12(140.0f);
            g_SysWork.playerWork.player.position.vz = Q12(-100.0f);
            Model_AnimFlagsClear(&g_SysWork.playerWork.player.model, 2);

            Savegame_EventFlagSet(EventFlag_575);

            func_801E2E28(D_800F481C);
            D_800F4838 = 0;
            SysWork_StateStepIncrement(0);

        case 5:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(0.0f), Q12(60.0f), true, true);
            break;

        case 6:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, true, 0, Q12(0.0f), false);
            break;

        case 7:
            if (func_801E2ED8())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 8:
            D_800F4806 = 1;
            func_800E9490(&g_SysWork.npcs[5]);
            g_Cutscene_Timer = Q12(161.0f);

            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 176, false);

            g_Cutscene_UpdateHero = true;
            g_Cutscene_UpdateBar  = false;
            D_800F4820 = 0;
            D_800F4818 = 1;

            Model_AnimFlagsSet(&g_SysWork.playerWork.player.model, 2);

            Event_ScreenFadeCmd(ScreenFadeCmd_Start, false, 0, Q12(0.0f), false);
            D_800F483C = Q12(70.0f);
            Gfx_MapInitMapEffectsUpdate(9, 9);
            Gfx_MapEffectsUpdate(17, 17, PrimitiveType_S32, &D_800F483C, 0, Q12(100.0f));
            SysWork_StateStepIncrement(0);

        case 9:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(161.0f), Q12(291.0f), true, true);
            D_800F483C += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 10.0f);
            if (D_800F483C > Q12(100.0f))
            {
                D_800F483C = Q12(100.0f);
            }
            break;

        case 10:
            Event_ScreenFadeCmd(ScreenFadeCmd_Start, false, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 11:
            Event_ScreenFadeCmd(ScreenFadeCmd_Auto, true, 1, Q12(1.0f), false);
            break;

        default:
            D_800F4805++;

            Sd_SfxStop(Sfx_Unk1688);
            Sd_SfxStop(Sfx_Unk1689);
            Sd_SfxStop(Sfx_Unk1690);

            D_800F4818 = 0;

            g_SysWork.sysStateSteps[0] = 0;

            D_800F4820 = 0;
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    if (D_800F4820 != 0)
    {
        switch (D_800F4824)
        {
            case 0:
                if (!(Rng_Rand16() & 0x70))
                {
                    func_800D7D74(0);
                }
                break;

            case 1:
                if (!(Rng_Rand16() & 0x70))
                {
                    func_800D7D74(0);
                }

            case 2:
                break;
        }

        if (D_800F4820 != 0)
        {
            ptr = D_800ED984[g_SysWork.sysStateSteps[0]];
            if (ptr)
            {
                do
                {
                    if (!(ptr->flags_38 & 2) || g_SysWork.sysStateSteps[0] != D_800ED980)
                    {
                        func_800DA774(ptr);
                    }

                    flags = ptr->flags_38;
                    ptr++;
                }
                while (flags & (1 << 0));
            }

            D_800ED980 = g_SysWork.sysStateSteps[0];
        }
    }
}

INCLUDE_RODATA("maps/map7_s03/nonmatchings/map7_s03_3", D_800CCE80);

void func_800E8D20(void) // 0x800E8D20
{
    s32             flags;
    s_800ED7E0_ptr* ptr;

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Fs_QueueWaitForEmpty();
            Dms_HeaderFixOffsets(FS_BUFFER_20);

            D_800F4806 = 0;

            func_800E941C();
            func_800E9444(Chara_EndingCybil, &g_SysWork.npcs[0]);

            g_Cutscene_UpdateSibyl = true;
            D_800F4804 = 0;

            Model_AnimFlagsClear(&g_SysWork.playerWork.player.model, 2);
            Event_CharaAnimCmdExecute(CharaAnimCmd_AnimUnlock, &g_SysWork.playerWork.player, 0, false);
            g_Cutscene_Timer = Q12(0.0f);
            func_800D7E50(&g_SysWork.playerWork.player.position);
            func_800D947C();

            D_800F4824 = 0;
            D_800F4820 = 1;

            g_SysWork.lightIntensity = Q12(0.7f);
            SysWork_StateStepIncrement(0);
            break;

        case 1:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[0], 26, false);
            Event_ScreenFadeCmd(ScreenFadeCmd_Start, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 2:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(0.0f), Q12(23.0f), true, true);
            break;

        case 3:
            func_800D7ED0();
            SysWork_StateStepIncrement(0);

        case 4:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(24.0f), Q12(39.0f), true, true);
            break;

        case 5:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[0], 25, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 173, false);
            SysWork_StateStepIncrement(0);

        case 6:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(40.0f), Q12(122.0f), true, true);
            break;

        case 7:
            g_Cutscene_Timer = Q12(123.0f);
            Model_AnimFlagsSet(&g_SysWork.playerWork.player.model, 2);
            Event_SysStateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 8:
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.playerWork.player, 172, false);
            Event_CharaAnimCmdExecute(CharaAnimCmd_SetState, &g_SysWork.npcs[0], 28, false);
            SysWork_StateStepIncrement(0);

        case 9:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(124.0f), Q12(162.0f), false, true);
            break;

        case 10:
            Event_DisplayMapMsgWithAudio(98, &D_800F4804, &D_800ED9B4);
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(124.0f), Q12(400.0f), true, false);
            break;

        case 11:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(124.0f), Q12(258.0f), false, true);
            break;

        case 12:
            Event_CutsceneTimerAdvance(&g_Cutscene_Timer, Q12(10.0f), Q12(124.0f), Q12(400.0f), true, false);
            if (g_Cutscene_Timer > Q12(375.0f))
            {
                Event_ScreenFadeCmd(ScreenFadeCmd_Auto, true, 0, Q12(0.3f), false);
            }
            break;

        default:
            D_800F4805++;

            Sd_SfxStop(Sfx_Unk1688);
            Sd_SfxStop(Sfx_Unk1689);
            Sd_SfxStop(Sfx_Unk1690);

            D_800F4820 = 0;

            Event_ScreenFadeCmd(ScreenFadeCmd_Start, false, 2, Q12(0.0f), false);

            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            func_800E9490(&g_SysWork.npcs[0]);
            break;
    }

    if (D_800F4820 != 0)
    {
        switch (D_800F4824)
        {
            case 0:
                if (!(Rng_Rand16() & 0x70))
                {
                    func_800D7D74(0);
                }
                break;

            case 1:
                if (!(Rng_Rand16() & 0x70))
                {
                    func_800D7D74(0);
                }

            case 2:
                break;
        }

        if (D_800F4820 != 0)
        {
            ptr = D_800ED9BC[g_SysWork.sysStateSteps[0]];
            if (ptr != NULL)
            {
                do
                {
                    if (!(ptr->flags_38 & 2) || g_SysWork.sysStateSteps[0] != D_800ED9B8)
                    {
                        func_800DA774(ptr);
                    }

                    flags = ptr->flags_38;
                    ptr++;
                }
                while (flags & (1 << 0));
            }

            D_800ED9B8 = g_SysWork.sysStateSteps[0];
        }
    }
}

void func_800E9260(e_CharaId charaId, s32 arg1) // 0x800E9260
{
    // TODO: Setup buffer defines for these (or maybe they're included in existing buffer?)

    WorldGfx_CharaLmBufferAssign(1 << (arg1 - 1));

    switch (arg1)
    {
        case 1:
            Fs_CharaAnimDataAlloc(arg1, charaId, (s_AnmHeader*)FS_BUFFER_29, &g_SysWork.npcBoneCoordBuffer[0]);
            WorldGfx_CharaLoad(charaId, 0, (s_LmHeader*)FS_BUFFER_31, &D_800ED218);
            break;

        case 2:
            Fs_CharaAnimDataAlloc(arg1, charaId, (s_AnmHeader*)FS_BUFFER_30, &g_SysWork.npcBoneCoordBuffer[30]);
            WorldGfx_CharaLoad(charaId, 1, LM_BUFFER_2, &D_800ED220);
            break;

        case 3:
            Fs_CharaAnimDataAlloc(arg1, charaId, (s_AnmHeader*)FS_BUFFER_26, &g_NpcBoneCoords[HarryBone_Root]);
            WorldGfx_CharaLoad(charaId, 2, (s_LmHeader*)FS_BUFFER_32, &D_800ED228);
            break;

        case 4:
            func_800E94C0();
            Fs_CharaAnimDataAlloc(arg1 - 3, charaId, (s_AnmHeader*)FS_BUFFER_29, &g_SysWork.npcBoneCoordBuffer[0]);
            WorldGfx_CharaLoad(charaId, 0, (s_LmHeader*)FS_BUFFER_31, &D_800ED218);
            func_800E94F4();
            break;

        case 5:
            func_800E94C0();
            Fs_CharaAnimDataAlloc(arg1 - 3, charaId, (s_AnmHeader*)FS_BUFFER_33, &g_SysWork.npcBoneCoordBuffer[30]);
            WorldGfx_CharaLoad(charaId, 1, (s_LmHeader*)FS_BUFFER_34, &D_800ED220);
            func_800E94F4();
            break;
    }
}

void func_800E941C(void) // 0x800E941C
{
    Fs_QueueWaitForEmpty();
    WorldGfx_CharaModelProcessAllLoads();
}

void func_800E9444(e_CharaId charaId, s_SubCharacter* chara) // 0x800E9444
{
    bzero(chara, sizeof(s_SubCharacter));

    chara->model.charaId       = charaId;
    chara->model.controlState  = 0;
    chara->model.anim.flags |= 2;
}

void func_800E9490(s_SubCharacter* chara) // 0x800E9490
{
    chara->model.charaId = Chara_None;
}

void func_800E9498(void) // 0x800E9498
{
    g_MapOverlayHdr.charaUpdateFuncs[Chara_Incubator] = Unknown23_Update;
}

void func_800E94AC(void) // 0x800E94AC
{
    g_MapOverlayHdr.charaUpdateFuncs[Chara_Incubator] = Incubator_Update;
}

void func_800E94C0(void) // 0x800E94C0
{
    // @hack Weird pointer arithmetic in this func.
    // Tracking that separately lets it match, but there's probably still a cleaner way.
    #define SET_ANIM_FILE_IDX(ptr, val) \
        ((ptr)->animFileIdx = (val))

    s_CharaFileInfo* ptr = &CHARA_FILE_INFOS[Chara_EndingCybil];

    SET_ANIM_FILE_IDX(&CHARA_FILE_INFOS[Chara_EndingCybil], FILE_ANIM_SBL_LAST_ANM);
    ptr += 10;
    SET_ANIM_FILE_IDX(&CHARA_FILE_INFOS[Chara_BloodyIncubator], FILE_ANIM_BAR_LAST_ANM);
    ptr += 2;
    SET_ANIM_FILE_IDX(&CHARA_FILE_INFOS[Chara_EndingKaufmann], FILE_ANIM_KAU_LAST_ANM);
    ptr -= 3;
    SET_ANIM_FILE_IDX(&CHARA_FILE_INFOS[Chara_Incubator], FILE_ANIM_MAR_LAST_ANM);

    #undef SET_ANIM_FILE_IDX
}

void func_800E94F4(void) // 0x800E94F4
{
    #define SET_ANIM_FILE_IDX(ptr, val) \
        ((ptr)->animFileIdx = (val))

    // @hack Weird pointer arithmetic in this func.
    // Tracking that separately lets it match, but there's probably still a cleaner way.
    s_CharaFileInfo* ptr = &CHARA_FILE_INFOS[Chara_EndingCybil];

    SET_ANIM_FILE_IDX(&CHARA_FILE_INFOS[Chara_EndingCybil], FILE_ANIM_SBL2_ANM);
    ptr += 10;
    SET_ANIM_FILE_IDX(&CHARA_FILE_INFOS[Chara_BloodyIncubator], FILE_ANIM_BAR_ANM);
    ptr += 2;
    SET_ANIM_FILE_IDX(&CHARA_FILE_INFOS[Chara_EndingKaufmann], FILE_ANIM_KAU2_ANM);
    ptr -= 3;
    SET_ANIM_FILE_IDX(&CHARA_FILE_INFOS[Chara_Incubator], FILE_ANIM_MAR_ANM);

    #undef SET_ANIM_FILE_IDX
}

void Map_WorldObjectsInit(void) // 0x800E9528
{
    D_800F4805 = 0;
    D_800F48A4 = 0;

    WorldObject_ModelNameSet(&g_WorldObject_Real, "REAL_HID");
    WorldObject_ModelNameSet(&g_WorldObject_Ura, "URA_HIDE");
    WorldObject_ModelNameSet(&g_WorldObject_Under, "UNDER_HI");

    Math_Vector3Set(&g_WorldObject_UnkPos, Q12(100.0f), Q12(0.0f), Q12(-140.0f));
    WorldObject_Init(&g_WorldObject_Bin, "BIN_HIDE", 140.0f, 0.0f, -100.0f, 0.0f, 0.0f, 0.0f);
    WorldObject_Init(&g_WorldObject_Nu, "NU_HIDE", 139.7f, 0.0f, -99.1f, 0.0f, -90.0f, 0.0f);
    WorldObject_Init(&g_WorldObject_Baby, "BABY_HID", 140.0f, 0.0f, -100.0f, 0.0f, 0.0f, 0.0f);

    g_SysWork.lightBoneCoord = NULL;

    // Set light position.
    g_SysWork.lightPosition.vx = Q12(139.7f);
    g_SysWork.lightPosition.vy = Q12(-4.5f);
    g_SysWork.lightPosition.vz = Q12(-98.1f);

    g_SysWork.lensFlareBoneCoord = NULL;

    // Set light rotation.
    g_SysWork.lightRotation.vx = Q12_ANGLE(-90.0f);
    g_SysWork.lightRotation.vy = Q12_ANGLE(0.0f);
    g_SysWork.lightRotation.vz = Q12_ANGLE(0.0f);

    g_SysWork.lightIntensity = Q12(2.0f);

    D_800F4820 = 0;

    func_800D5D24();
    func_800E16FC();

    D_800F4838 = 0;
    D_800F4830 = 0;

    if (Savegame_EventFlagGet(EventFlag_449))
    {
        D_800F481C = 1;
    }
    else
    {
        D_800F481C = 2;
    }

    if (!Savegame_EventFlagGet(EventFlag_391))
    {
        D_800F481C += 2;
    }
}

void Map_WorldObjectsUpdate(void) // 0x800E972C
{
    if (g_Cutscene_UpdateBin)
    {
        *(s32*)&(g_WorldObject_Bin.rotation.vx) = (u16)D_800F482C;
        *(s16*)&(g_WorldObject_Bin.rotation.vz) = 0;

        WorldGfx_ObjectAdd(&g_WorldObject_Bin.object, &g_WorldObject_Bin.position, &g_WorldObject_Bin.rotation);
        D_800F482C -= (FP_TO(g_DeltaTime, Q12_SHIFT) / Q12(3.6f));
    }

    if (D_800F4811)
    {
        WorldGfx_ObjectAdd(&g_WorldObject_Nu.object, &g_WorldObject_Nu.position, &g_WorldObject_Nu.rotation);
    }

    if (g_Cutscene_UpdateBaby)
    {
        WorldGfx_ObjectAdd(&g_WorldObject_Baby.object, &g_WorldObject_Baby.position, &g_WorldObject_Baby.rotation);
    }

    if (Savegame_EventFlagGet(EventFlag_577) && !Savegame_EventFlagGet(EventFlag_578) && !Savegame_EventFlagGet(EventFlag_582))
    {
        if (Savegame_EventFlagGet(EventFlag_391))
        {
            func_800E14DC(&g_SysWork.playerWork.player, &g_SysWork.npcs[2], false);
        }
        else
        {
            func_800E14DC(&g_SysWork.playerWork.player, &g_SysWork.npcs[4], false);
        }
    }

    if (D_800F4818 || D_800F4819)
    {
        func_800E98EC();
    }
}

void func_800E9874(void) // 0x800E9874
{
    func_800E1854();

    if (D_800F4820 != 0)
    {
        if (D_800F4838 == 0)
        {
            func_800D5E78();
            func_800D7D08();
        }

        func_800D917C();
    }

    if (D_800F4830 > 0)
    {
        func_800D8858(D_800F4830 - 1);
    }
}

void func_800E98EC(void) // 0x800E98EC
{
    static const SVECTOR3 DEFAULT_ROT = {}; // .rodata 0x800CD168

    s32     i;
    VECTOR3 objPos;

    if (D_800F4819 != 2)
    {
        D_800F48A4 += Q12_MULT_PRECISE(g_DeltaTime, Q12(2.67f));
    }

    if (D_800F48A4 > Q12(20.0f))
    {
        D_800F48A4 -= Q12(20.0f);
    }

    for (i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            objPos.vx = g_WorldObject_UnkPos.vx;
            objPos.vy = g_WorldObject_UnkPos.vy;
            objPos.vz = g_WorldObject_UnkPos.vz - D_800F48A4;
        }
        else if (i == 1)
        {
            objPos.vz = (g_WorldObject_UnkPos.vz - D_800F48A4) - Q12(20.0f);
        }
        else
        {
            objPos.vz = (g_WorldObject_UnkPos.vz - D_800F48A4) + Q12(20.0f);
        }

        if (D_800F4818)
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Real, &objPos, &DEFAULT_ROT);
        }

        if (D_800F4819)
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Ura, &objPos, &DEFAULT_ROT);
        }

        if (D_800F481A)
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Under, &objPos, &DEFAULT_ROT);
        }
    }

    Collision_FlagBitsClear(CollisionTriggerFlag_All);

    if (D_800F4818)
    {
        Collision_FlagBitsSet(2);
    }

    if (D_800F4819)
    {
        Collision_FlagBitsSet(4);
    }
}

void func_800E9AC8(void) // 0x800E9AC8
{
    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            Event_CharaAnimCmdExecute(CharaAnimCmd_AnimLock, &g_SysWork.playerWork.player, 0, false);

            if (D_800F481C >= 1 && D_800F481C < 3)
            {
                g_SysWork.sysStateSteps[0] = 3;
                break;
            }

            GameFs_StfRollBinLoad();
            g_SysWork.sysStateSteps[0]++;

        case 1:
            if (Fs_QueueGetLength() == 0)
            {
                func_801E2E28(D_800F481C);
                g_SysWork.sysStateSteps[0]++;
            }
            break;

        case 2:
            if (func_801E2ED8())
            {
                g_SysWork.sysStateSteps[0]++;
            }
            break;

        case 3:
            if (func_801E2FC0())
            {
                Savegame_EventFlagSet(EventFlag_588);
                SysWork_StateSetNext(SysState_Gameplay);
            }
            break;
    }
}

void func_800E9C28(void) // 0x800E9C28
{
    g_Screen_FadeStatus = ScreenFadeState_FadeOutComplete;

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            Event_CharaAnimCmdExecute(CharaAnimCmd_AnimLock, &g_SysWork.playerWork.player, 0, false);
            g_SysWork.sysStateSteps[0]++;
            break;

        case 1:
            Bgm_CrossfadeToTrack(BgmTrackIdx_5);
            break;

        case 2:
            g_SavegamePtr->isNextFearMode = true;

            g_SavegamePtr->clearGameCount++;
            g_SavegamePtr->clearGameCount = CLAMP(g_SavegamePtr->clearGameCount, 1, 99);

            g_SavegamePtr->field_27A                             = 1 << (D_800F481C - 1);
            g_SavegamePtr->clearGameEndings                 |= 1 << (D_800F481C - 1);
            g_GameWorkConst->config.extraOptionsEnabled |= 1 << (D_800F481C - 1);

            g_SavegamePtr->locationId = SaveLocationId_NextFear;

            SysWork_StateSetNext(SysState_StatusMenu);
            break;
    }
}

