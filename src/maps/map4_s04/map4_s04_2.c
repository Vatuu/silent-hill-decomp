#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map4/map4_s04.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D098C

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D09A0

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D09E4

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D09FC

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D0A08

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D0A1C

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D0A30

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D0A44

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800D0AE0

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D1144

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D1158

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D116C

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D1268

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D1314

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D1334

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D1394

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D13A4

void func_800D143C(s32 arg0) // 0x800D143C
{
    (arg0 != 0) ? func_800D1470() : func_800D14B0();
}

void func_800D1470(void) // 0x800D1470
{
    func_8003640C(!Savegame_EventFlagGet(EventFlag_237) ? (1 << 3) : (1 << 1));
}

INCLUDE_RODATA("asm/maps/map4_s04/nonmatchings/map4_s04_2", D_800CA964);

INCLUDE_ASM("asm/maps/map4_s04/nonmatchings/map4_s04_2", func_800D14B0);

void func_800D1740(void) {}

#include "maps/shared/Event_DoorJammed.h" // 0x800D1748

#include "maps/shared/Event_DoorLocked.h" // 0x800D17DC

void func_800D1870(void) {}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D1878

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J0(1.8)\tWhere_am_I? ~E ",
    "~J1(1.0)\tHarry. ",
    "~J1(1.2)\tLisa... ",
    "~J1(1.5)\tThen_I'm_in_the_hospital. ",
    "~J1(2.4)\tYou_were_having_a_bad_dream. ",
    "~J1(0.8)\tWas_I? ",
    "~J1(4.2)\tHey,_you_don't_look_too_good. ~N\n\t\t\tAre_you_OK? ",
    "~J1(1.3)\tI'm_fine. ",
    "~J1(2.2)\tNothing_you_need_to ~N\n\t\t\tworry_about. ",
    "~J1(2.2)\tWell,_if_you're_sure... ~E ",
    "~J1(4.3)\tLisa... ~N\n\t\t\tDo_you_know_a_woman ~N\n\t\t\tnamed_Dahlia_Gillespie? ",
    "~J1(3.2)\tOh_yeah, ~N\n\t\t\tthat_crazy_Gillespie_lady. ",
    "~J1(2.3)\tShe's_kinda'_famous_around_here. ",
    "~J1(4.0)\tShe_never_sees_anybody, ~N\n\t\t\tso_I_don't_know ~N\n\t\t\tthat_much_about_her. ",
    "~J1(5.2)\tI_heard_her_kid_died_in_a_fire, ~N\n\t\t\tand_supposedly_she's_been_crazy ~N\n\t\t\tever_since. ~E ",
    "~J1(5.1)\tWell,_she_says_the_town_is_being ~N\n\t\t\tdevoured_by_the_darkness. ",
    "~J1(2.7)\tDo_you_have_any_idea ~N\n\t\t\twhat_she's_talking_about? ",
    "~J1(3.5)\tThe_town..._devoured ~N\n\t\t\tby_the_darkness. ",
    "~J1(2.1)\tYes,_I_think_I_do. ",
    "~J1(2.9)\tBefore_this_place_was_turned ~N\n\t\t\tinto_a_resort, ",
    "~J1(3.4)\tthe_townspeople_here_were ~N\n\t\t\ton_the_quiet_side. ",
    "~J1(4.1)\tEverybody_followed ~N\n\t\t\tsome_kind_of_queer_religion. ~E ",
    "~J1(4.8)\tWeird_occult_stuff... ~N\n\t\t\tBlack_magic,_that_kind_of_thing. ",
    "~J1(5.0)\tAs_young_people_moved_away, ~N\n\t\t\tthe_people_figured_they'd_been ~N\n\t\t\tsummoned_by_the_gods. ",
    "~J1(3.7)\tEvidently,_things_like_that ~N\n\t\t\tused_to_happen_around_here ~N\n\t\t\tall_the_time. ",
    "~J1(3.5)\tBefore_the_resort, ~N\n\t\t\tthere_really_wasn't ~N\n\t\t\tanything_else_out_here. ",
    "~J1(4.5)\tEveryone_was_so_flipped_out. ~N\n\t\t\tGotta_blame_it_on_something. ",
    "~J1(3.8)\tThen_a_lot_of_new_people ~N\n\t\t\tcame_in_and_everybody ~N\n\t\t\tclammed_up_about_it. ",
    "~J0(1.8)\tA_cult... ~E ",
    "~J0(4.8)\tLast_time_I_heard_anything ~N\n\t\t\tabout_it_was,_gosh,_years_ago... ",
    "~J1(4.4)\tWhen_several_people_connected ~N\n\t\t\twith_developing_the_town ~N\n\t\t\tdied_in_accidents. ",
    "~J1(2.0)\tPeople_said_it_was_a_curse. ",
    "~J1(4.2)\tI'm_sorry,_I'm_rambling... ~N\n\t\t\tI'll_shut_up. ~E ",
    "~J0(1.1)\tHarry! ~E ",
    "~J0(1.6)\tGlad_you're_OK. ~E ",
    "~J0(4.6)\tThank_God_you_came_back. ~N\n\t\t\tI_was_scared_to_be_here_all_alone. ",
    "~J0(2.5)\tI'm_here_now. ~N\n\t\t\tI_was_worried,_too. ",
    "~J0(1.6)\tI'm_real_happy_to_see_you. ~E ",
    "~J1(3.3)\tLisa,_can_you_tell_me ~N\n\t\t\thow_to_get_to_the_lake? ",
    "~J1(3.0)\tThe_lake? ~N\n\t\t\tYou_take_Bachman_Road. ",
    "~J1(1.5)\tThe_road's_blocked. ",
    "~J1(2.3)\tWell,_that's ~N\n\t\t\tthe_only_way_out_there. ",
    "~J1(1.3)\tAre_you_sure? ",
    "~J1(2.7)\tThere's_gotta_be_another_way. ~E ",
    "~J1(3.0)\tWait, ~N\n\t\t\tI_just_remembered_something. ",
    "~J1(0.6)\tWhat? ",
    "~J1(3.3)\tThere's_a_water_works_over_by ~N\n\t\t\tmy_old_elementary_school. ",
    "~J1(2.3)\tIt's_been_abandoned_for_years. ",
    "~J1(4.2)\tThere's_an_underground_tunnel ~N\n\t\t\tout_there_used_for_inspections, ~N\n\t\t\tor_something! ",
    "~J1(3.2)\tI_remember_hearing_it_runs ~N\n\t\t\tall_the_way_to_the_lake! ~E ",
    "~J1(0.9)\tReally?! ",
    "~J1(2.3)\tYou_think_I_can_get_to_the_lake ~N\n\t\t\tfrom_there? ",
    "~J1(3.1)\tI've_never_been_down ~N\n\t\t\tin_there_myself, ~N\n\t\t\tso_I'm_not_positive. ",
    "~J1(2.8)\tBesides,_it's_all_fenced_off ~N\n\t\t\tto_keep_people_out. ",
    "~J1(2.3)\tIf_there's_a_chance, ~N\n\t\t\tI've_got_to_try. ~E  ",
    "~J1(2.0)\tHarry,_don't_go! ",
    "~J1(4.2)\tI_don't_want_to_be_alone. ~N\n\t\t\tIt's_so_scary._I_can't_stand_it. ",
    "~J1(1.6)\tHow_about_coming_with_me? ",
    "~J1(2.6)\tThis_may_not_be_the_safest_place ~N\n\t\t\tin_the_world_either. ",
    "~J1(3.6)\tI_can't_promise_you_anything, ~N\n\t\t\tbut_I'll_do_my_best ~N\n\t\t\tto_protect_you. ",
    "~J1(4.2)\tNo... ~N\n\t\t\tsomehow_I_feel_I'm_not_supposed ~N\n\t\t\tto_leave_this_place. ",
    "~J1(4.0)\tOh,_Harry,_I'm_so_scared... ~N\n\t\t\tI'm_cold. ",
    "~J1(3.8)\tLook,_just_wait_here ~N\n\t\t\ta_little_longer. ",
    "~J1(3.0)\tI'll_be_back_as_soon_as ~N\n\t\t\tI_find_my_daughter. ~E ",
    "~J0(1.5)\tHarry... ~E ",
    "\tNothing_unusual. ~E ",
    "\tNothing_helpful. ~E "
};

INCLUDE_RODATA("asm/maps/map4_s04/nonmatchings/map4_s04_2", D_800CBB78);

INCLUDE_RODATA("asm/maps/map4_s04/nonmatchings/map4_s04_2", D_800CBB80);

INCLUDE_ASM("asm/maps/map4_s04/nonmatchings/map4_s04_2", func_800D1910);

INCLUDE_RODATA("asm/maps/map4_s04/nonmatchings/map4_s04_2", D_800CBBC4);

INCLUDE_ASM("asm/maps/map4_s04/nonmatchings/map4_s04_2", func_800D23E4);

INCLUDE_ASM("asm/maps/map4_s04/nonmatchings/map4_s04_2", func_800D2D6C);

INCLUDE_ASM("asm/maps/map4_s04/nonmatchings/map4_s04_2", func_800D2DF4);

INCLUDE_RODATA("asm/maps/map4_s04/nonmatchings/map4_s04_2", D_800CBC58);
