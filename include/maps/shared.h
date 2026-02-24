#ifndef _MAPS_SHARED_H
#define _MAPS_SHARED_H

#include "game.h"
#include "bodyprog/sound_background.h"
#include "bodyprog/gfx/screen_draw.h"

// BIG TODO: Move tables below to wherever they belong when data migration is performed. I've split these into alphabetised player and NPC sections
// to make them easier to sort through. -- Sezz
//
// Noteworthy things:
// - The player has one base Harry anim info table plus several unique tables per map, wherea NPCs share single tables across maps.
// - Cybil's table is near-identical bewteen the two maps in which it's used, with minor differences in frame ranges for three of its entires.
// - Harry's tables tend to have a zeroed out anim info as their last entry.
// - Anim 0 of each character is a still frame, possibly used as a "home" pose.

// ==============
// PLAYER TABLES
// ==============

/*s_AnimInfo HARRY_M0S00_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(10) }, 678, 713 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 718 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 718, 732 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 737 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 737, 751 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 758 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 758, 770 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 777 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(15) }, 777, 789 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(8) }, NO_VALUE, 790 },
    { Anim_Update1, ANIM_STATUS(44, true), false, NO_VALUE, { Q12(18) }, 790, 807 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(8) }, NO_VALUE, 808 },
    { Anim_Update1, ANIM_STATUS(45, true), false, NO_VALUE, { Q12(18) }, 808, 825 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(8) }, NO_VALUE, 826 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(18) }, 826, 843 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(8) }, NO_VALUE, 844 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(18) }, 844, 861 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(10) }, NO_VALUE, 862 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(15) }, 862, 882 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 883 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(15) }, 883, 903 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 904 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 904, 914 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 915 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(15) }, 915, 925 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(2) }, NO_VALUE, 926 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(4) }, 926, 972 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(10) }, NO_VALUE, 973 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(15) }, 973, 993 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 994 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(25) }, 994, 1026 },
    {}
}*/

/*s_AnimInfo HARRY_M0S01_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(10) }, 678, 713 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 718 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 718, 732 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 737 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 737, 751 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 758 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 758, 770 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 777 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(15) }, 777, 789 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 790 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(15) }, 790, 804 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 805 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(14.4) }, 805, 815 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(10) }, NO_VALUE, 816 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(18) }, 816, 826 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(10) }, NO_VALUE, 827 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(8.7) }, 827, 872 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(10) }, NO_VALUE, 873 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(7.8) }, 873, 900 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 901 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(4) }, 901, 916 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 917 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 917, 947 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(64) }, NO_VALUE, 948 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(18) }, 948, 1026 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 1027 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(15) }, 1027, 1037 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(10) }, NO_VALUE, 1038 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(15) }, 1038, 1054 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 1055 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(10) }, 1055, 1074 },
    { Anim_Update2, ANIM_STATUS(55, false), false, ANIM_STATUS(55, true), { Q12(10) }, NO_VALUE, 1075 },
    { Anim_Update1, ANIM_STATUS(55, true), false, NO_VALUE, { Q12(1) }, 1075, 1080 },
    { Anim_Update2, ANIM_STATUS(56, false), false, ANIM_STATUS(56, true), { Q12(10) }, NO_VALUE, 1081 },
    { Anim_Update1, ANIM_STATUS(56, true), false, NO_VALUE, { Q12(2) }, 1081, 1084 },
    { Anim_Update2, ANIM_STATUS(57, false), false, ANIM_STATUS(57, true), { Q12(10) }, NO_VALUE, 815 },
    { Anim_Update0, ANIM_STATUS(57, true), false, ANIM_STATUS(57, true), { Q12(15) }, 815, 815 },
    {}
}*/

/*s_AnimInfo HARRY_M0S02_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(10) }, 678, 713 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 718 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 718, 732 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 737 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 737, 751 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 758 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 758, 770 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 777 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(15) }, 777, 789 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(20) }, 485, 502 }
}*/

/*s_AnimInfo HARRY_M1S00_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(8) }, NO_VALUE, 801 },
    { Anim_Update1, ANIM_STATUS(45, true), false, NO_VALUE, { Q12(18) }, 801, 818 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(8) }, NO_VALUE, 819 },
    { Anim_Update1, ANIM_STATUS(46, true), false, NO_VALUE, { Q12(18) }, 819, 836 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(8) }, NO_VALUE, 837 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(18) }, 837, 854 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(8) }, NO_VALUE, 855 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(18) }, 855, 872 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 873 },
    { Anim_Update1, ANIM_STATUS(49, true), false, NO_VALUE, { Q12(18) }, 873, 909 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 910 },
    { Anim_Update1, ANIM_STATUS(50, true), false, NO_VALUE, { Q12(18) }, 910, 946 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(20) }, 485, 502 },
    {}
}*/

/*s_AnimInfo HARRY_M1S01_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(8) }, NO_VALUE, 801 },
    { Anim_Update1, ANIM_STATUS(45, true), false, NO_VALUE, { Q12(18) }, 801, 818 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(8) }, NO_VALUE, 819 },
    { Anim_Update1, ANIM_STATUS(46, true), false, NO_VALUE, { Q12(18) }, 819, 836 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(8) }, NO_VALUE, 837 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(18) }, 837, 854 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(8) }, NO_VALUE, 855 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(18) }, 855, 872 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 873 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(15) }, 873, 887 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 888 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 888, 899 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 900 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(15) }, 900, 948 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 949 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(12) }, 949, 960 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(10) }, NO_VALUE, 961 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(10) }, 961, 990 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(20) }, 485, 502 },
    {}
}*/

/*s_AnimInfo HARRY_M1S02_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 801 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(18) }, 801, 815 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(10) }, NO_VALUE, 816 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(18) }, 816, 830 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(8) }, NO_VALUE, 831 },
    { Anim_Update1, ANIM_STATUS(47, true), false, NO_VALUE, { Q12(18) }, 831, 848 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(8) }, NO_VALUE, 849 },
    { Anim_Update1, ANIM_STATUS(48, true), false, NO_VALUE, { Q12(18) }, 849, 866 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(8) }, NO_VALUE, 867 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(18) }, 867, 884 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(8) }, NO_VALUE, 885 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(18) }, 885, 902 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 903 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(15) }, 903, 917 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 918 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(15) }, 918, 929 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(10) }, NO_VALUE, 970 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(8.9) }, 970, 1016 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 1017 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(15) }, 1017, 1037 },
    { Anim_Update2, ANIM_STATUS(55, false), false, ANIM_STATUS(55, true), { Q12(10) }, NO_VALUE, 1038 },
    { Anim_Update0, ANIM_STATUS(55, true), false, ANIM_STATUS(55, true), { Q12(12) }, 1038, 1049 },
    { Anim_Update2, ANIM_STATUS(56, false), false, ANIM_STATUS(56, true), { Q12(10) }, NO_VALUE, 1050 },
    { Anim_Update0, ANIM_STATUS(56, true), false, ANIM_STATUS(56, true), { Q12(1048564) }, 1050, 1061 },
    { Anim_Update2, ANIM_STATUS(57, false), false, ANIM_STATUS(57, true), { Q12(10) }, NO_VALUE, 1037 },
    { Anim_Update0, ANIM_STATUS(57, true), false, ANIM_STATUS(57, true), { Q12(1048568) }, 1032, 1037 },
    { Anim_Update2, ANIM_STATUS(58, false), false, ANIM_STATUS(58, true), { Q12(10) }, NO_VALUE, 960 },
    { Anim_Update0, ANIM_STATUS(58, true), false, ANIM_STATUS(58, true), { Q12(20) }, 960, 1016 },
    { Anim_Update2, ANIM_STATUS(59, false), false, ANIM_STATUS(59, true), { Q12(10) }, NO_VALUE, 1062 },
    { Anim_Update0, ANIM_STATUS(59, true), false, ANIM_STATUS(59, true), { Q12(6) }, 1062, 1110 },
    { Anim_Update2, ANIM_STATUS(60, false), false, ANIM_STATUS(60, true), { Q12(10) }, NO_VALUE, 1119 },
    { Anim_Update0, ANIM_STATUS(60, true), false, ANIM_STATUS(60, true), { Q12(10) }, 1119, 1147 },
    { Anim_Update2, ANIM_STATUS(61, false), false, ANIM_STATUS(61, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(61, true), false, ANIM_STATUS(61, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M1S03_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 801 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(18) }, 801, 815 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(10) }, NO_VALUE, 816 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(18) }, 816, 830 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(8) }, NO_VALUE, 831 },
    { Anim_Update1, ANIM_STATUS(47, true), false, NO_VALUE, { Q12(18) }, 831, 848 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(8) }, NO_VALUE, 849 },
    { Anim_Update1, ANIM_STATUS(48, true), false, NO_VALUE, { Q12(18) }, 849, 866 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(8) }, NO_VALUE, 867 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(18) }, 867, 884 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(8) }, NO_VALUE, 885 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(18) }, 885, 902 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 903 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(15) }, 903, 917 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 918 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(15) }, 918, 929 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(10) }, NO_VALUE, 930 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(15) }, 930, 976 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 977 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(25) }, 977, 1007 },
    { Anim_Update2, ANIM_STATUS(55, false), false, ANIM_STATUS(55, true), { Q12(10) }, NO_VALUE, 1008 },
    { Anim_Update0, ANIM_STATUS(55, true), false, ANIM_STATUS(55, true), { Q12(12) }, 1008, 1019 },
    { Anim_Update2, ANIM_STATUS(56, false), false, ANIM_STATUS(56, true), { Q12(25) }, NO_VALUE, 1027 },
    { Anim_Update0, ANIM_STATUS(56, true), false, ANIM_STATUS(56, true), { Q12(1048575) }, 1020, 1027 },
    { Anim_Update2, ANIM_STATUS(57, false), false, ANIM_STATUS(57, true), { Q12(10) }, NO_VALUE, 1032 },
    { Anim_Update0, ANIM_STATUS(57, true), false, ANIM_STATUS(57, true), { Q12(10) }, 1032, 1092 },
    { Anim_Update2, ANIM_STATUS(58, false), false, ANIM_STATUS(58, true), { Q12(10) }, NO_VALUE, 1092 },
    { Anim_Update0, ANIM_STATUS(58, true), false, ANIM_STATUS(58, true), { Q12(1048566) }, 1032, 1092 },
    { Anim_Update2, ANIM_STATUS(59, false), false, ANIM_STATUS(59, true), { Q12(10) }, NO_VALUE, 1047 },
    { Anim_Update0, ANIM_STATUS(59, true), false, ANIM_STATUS(59, true), { Q12(8) }, 1047, 1092 },
    { Anim_Update2, ANIM_STATUS(60, false), false, ANIM_STATUS(60, true), { Q12(10) }, NO_VALUE, 1092 },
    { Anim_Update0, ANIM_STATUS(60, true), false, ANIM_STATUS(60, true), { Q12(1048568) }, 1045, 1092 },
    { Anim_Update2, ANIM_STATUS(61, false), false, ANIM_STATUS(61, true), { Q12(10) }, NO_VALUE, 1093 },
    { Anim_Update0, ANIM_STATUS(61, true), false, ANIM_STATUS(61, true), { Q12(15) }, 1093, 1122 },
    { Anim_Update2, ANIM_STATUS(62, false), false, ANIM_STATUS(62, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(62, true), false, ANIM_STATUS(62, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M1S05_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(1) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(3) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(25) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(25) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(20) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(20) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(10) }, NO_VALUE, 390 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(20) }, 390, 412 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(10) }, NO_VALUE, 423 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(20) }, 423, 451 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M1S06_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 692 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 693 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 693, 704 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M2S00_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 801 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(15) }, 801, 815 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(15) }, NO_VALUE, 816 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(15) }, 816, 822 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(15) }, NO_VALUE, 823 },
    { Anim_Update1, ANIM_STATUS(47, true), false, NO_VALUE, { Q12(524400.4) }, 823, 836 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(15) }, NO_VALUE, 837 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(15) }, 837, 843 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(15) }, NO_VALUE, 844 },
    { Anim_Update1, ANIM_STATUS(49, true), false, NO_VALUE, { Q12(524400.4) }, 844, 857 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(15) }, NO_VALUE, 858 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 858, 884 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(15) }, NO_VALUE, 885 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(15) }, 885, 911 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(15) }, NO_VALUE, 912 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(15) }, 912, 929 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(15) }, NO_VALUE, 930 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(15) }, 930, 945 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 946 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(15) }, 946, 960 },
    { Anim_Update2, ANIM_STATUS(55, false), false, ANIM_STATUS(55, true), { Q12(10) }, NO_VALUE, 961 },
    { Anim_Update0, ANIM_STATUS(55, true), false, ANIM_STATUS(55, true), { Q12(15) }, 961, 972 },
    { Anim_Update2, ANIM_STATUS(56, false), false, ANIM_STATUS(56, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(56, true), false, ANIM_STATUS(56, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M2S01_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(16) }, 678, 722 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 723 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(5) }, 723, 744 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 745 },
    { Anim_Update1, ANIM_STATUS(41, true), false, NO_VALUE, { Q12(2) }, 745, 748 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M2S02_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(10) }, 678, 713 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 718 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 718, 732 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 737 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 737, 751 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 758 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(10) }, 758, 770 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 777 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 777, 789 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 790 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(15) }, 790, 804 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(15) }, NO_VALUE, 805 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(15) }, 805, 811 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(15) }, NO_VALUE, 812 },
    { Anim_Update1, ANIM_STATUS(46, true), false, NO_VALUE, { Q12(524400.4) }, 812, 825 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(15) }, NO_VALUE, 826 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(15) }, 826, 832 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(15) }, NO_VALUE, 833 },
    { Anim_Update1, ANIM_STATUS(48, true), false, NO_VALUE, { Q12(524400.4) }, 833, 846 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(15) }, NO_VALUE, 847 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(15) }, 847, 873 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(15) }, NO_VALUE, 874 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 874, 900 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(15) }, NO_VALUE, 901 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(15) }, 901, 918 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(15) }, NO_VALUE, 919 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(15) }, 919, 934 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M2S04_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M3S00_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(4.8) }, 678, 698 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(30) }, NO_VALUE, 699 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 699, 783 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 784 },
    { Anim_Update1, ANIM_STATUS(41, true), false, NO_VALUE, { Q12(2) }, 784, 787 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M3S01_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(10) }, 678, 713 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 718 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 718, 732 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 737 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 737, 751 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 758 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(10) }, 758, 770 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 777 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 777, 789 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 790 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(18) }, 790, 804 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 805 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(18) }, 805, 819 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(8) }, NO_VALUE, 820 },
    { Anim_Update1, ANIM_STATUS(46, true), false, NO_VALUE, { Q12(18) }, 820, 854 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(8) }, NO_VALUE, 855 },
    { Anim_Update1, ANIM_STATUS(47, true), false, NO_VALUE, { Q12(18) }, 854, 888 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(30) }, NO_VALUE, 889 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(24) }, 889, 922 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(30) }, NO_VALUE, 923 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(24) }, 923, 956 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 957 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 957, 971 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 972 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(15) }, 972, 983 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M3S02_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(10) }, 678, 713 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 718 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 718, 732 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 737 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 737, 751 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 758 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(10) }, 758, 770 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 777 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 777, 789 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 790 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(18) }, 790, 804 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 805 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(18) }, 805, 819 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(8) }, NO_VALUE, 820 },
    { Anim_Update1, ANIM_STATUS(46, true), false, NO_VALUE, { Q12(18) }, 820, 854 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(8) }, NO_VALUE, 855 },
    { Anim_Update1, ANIM_STATUS(47, true), false, NO_VALUE, { Q12(18) }, 855, 888 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(30) }, NO_VALUE, 889 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(24) }, 889, 922 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(30) }, NO_VALUE, 923 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(24) }, 923, 956 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M3S04_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(10) }, 678, 713 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 718 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 718, 732 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 737 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 737, 751 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 758 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(10) }, 758, 770 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 777 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 777, 789 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 790 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(18) }, 790, 804 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 805 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(18) }, 805, 819 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(8) }, NO_VALUE, 820 },
    { Anim_Update1, ANIM_STATUS(46, true), false, NO_VALUE, { Q12(18) }, 820, 854 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(8) }, NO_VALUE, 855 },
    { Anim_Update1, ANIM_STATUS(47, true), false, NO_VALUE, { Q12(18) }, 855, 888 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(30) }, NO_VALUE, 889 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(24) }, 889, 922 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(30) }, NO_VALUE, 923 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(24) }, 923, 956 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 957 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 957, 971 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 972 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(15) }, 972, 983 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 984 },
    { Anim_Update1, ANIM_STATUS(52, true), false, NO_VALUE, { Q12(2) }, 984, 987 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(10) }, NO_VALUE, 988 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(9) }, 988, 1104 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M3S05_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(10) }, 678, 713 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 718 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 718, 732 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 737 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 737, 751 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 758 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(10) }, 758, 770 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 777 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 777, 789 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 790 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(18) }, 790, 804 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 805 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(18) }, 805, 819 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(8) }, NO_VALUE, 820 },
    { Anim_Update1, ANIM_STATUS(46, true), false, NO_VALUE, { Q12(18) }, 820, 854 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(8) }, NO_VALUE, 855 },
    { Anim_Update1, ANIM_STATUS(47, true), false, NO_VALUE, { Q12(18) }, 855, 888 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(30) }, NO_VALUE, 889 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(24) }, 889, 922 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(30) }, NO_VALUE, 923 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(24) }, 923, 956 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 957 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 957, 971 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 972 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(15) }, 972, 983 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 984 },
    { Anim_Update1, ANIM_STATUS(52, true), false, NO_VALUE, { Q12(10) }, 984, 997 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(10) }, NO_VALUE, 998 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(10) }, 998, 1028 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 1029 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(7) }, 1029, 1065 },
    { Anim_Update2, ANIM_STATUS(55, false), false, ANIM_STATUS(55, true), { Q12(10) }, NO_VALUE, 1066 },
    { Anim_Update0, ANIM_STATUS(55, true), false, ANIM_STATUS(55, true), { Q12(8) }, 1066, 1112 },
    { Anim_Update2, ANIM_STATUS(56, false), false, ANIM_STATUS(56, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(56, true), false, ANIM_STATUS(56, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M3S06_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 722 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 723 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(4) }, 723, 762 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 763 },
    { Anim_Update1, ANIM_STATUS(41, true), false, NO_VALUE, { Q12(2) }, 763, 766 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M4S01_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update1, ANIM_STATUS(39, true), false, NO_VALUE, { Q12(4) }, 678, 691 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 692 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 692, 712 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 713 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(10) }, 713, 749 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 750 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(10) }, 750, 768 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 778 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 779 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 779, 806 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 807 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(10) }, 807, 841 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(10) }, NO_VALUE, 842 },
    { Anim_Update1, ANIM_STATUS(46, true), false, NO_VALUE, { Q12(2) }, 842, 845 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(10) }, NO_VALUE, 846 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(15) }, 846, 966 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(10) }, NO_VALUE, 967 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(10) }, 967, 981 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 982 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(10) }, 982, 1015 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 1016 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 1016, 1035 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 1036 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(8) }, 1036, 1056 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M4S02_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 801 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(15) }, 801, 823 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(15) }, NO_VALUE, 824 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(15) }, 824, 830 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(15) }, NO_VALUE, 831 },
    { Anim_Update1, ANIM_STATUS(47, true), false, NO_VALUE, { Q12(524400.4) }, 831, 844 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(15) }, NO_VALUE, 845 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(15) }, 845, 851 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(15) }, NO_VALUE, 852 },
    { Anim_Update1, ANIM_STATUS(49, true), false, NO_VALUE, { Q12(524400.4) }, 852, 865 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(15) }, NO_VALUE, 866 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 866, 892 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(15) }, NO_VALUE, 893 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(15) }, 893, 919 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(15) }, NO_VALUE, 920 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(15) }, 920, 937 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(15) }, NO_VALUE, 938 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(15) }, 938, 953 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M4S03_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(10) }, 678, 713 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 718 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 718, 732 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 737 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 737, 751 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 758 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(10) }, 758, 770 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 777 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 777, 789 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(8) }, NO_VALUE, 790 },
    { Anim_Update1, ANIM_STATUS(44, true), false, NO_VALUE, { Q12(18) }, 790, 807 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(8) }, NO_VALUE, 808 },
    { Anim_Update1, ANIM_STATUS(45, true), false, NO_VALUE, { Q12(18) }, 808, 825 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(10) }, NO_VALUE, 826 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(15) }, 826, 840 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(8) }, NO_VALUE, 841 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(18) }, 841, 858 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(8) }, NO_VALUE, 859 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(18) }, 859, 876 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 877 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(15) }, 877, 911 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 936 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 936, 948 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 970 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(15) }, 970, 987 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M4S04_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(10) }, 678, 701 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 718 },
    { Anim_Update1, ANIM_STATUS(40, true), false, NO_VALUE, { Q12(2) }, 718, 721 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(8) }, NO_VALUE, 722 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(8) }, 722, 747 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update1, ANIM_STATUS(42, true), false, NO_VALUE, { Q12(2) }, 748, 763 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M4S05_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 801 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(15) }, 801, 815 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(10) }, NO_VALUE, 390 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(20) }, 390, 417 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(10) }, NO_VALUE, 423 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(20) }, 423, 456 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(50) }, NO_VALUE, 821 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(45) }, 821, 836 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M5S00_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 801 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(18) }, 801, 815 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(10) }, NO_VALUE, 816 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(18) }, 816, 830 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(10) }, NO_VALUE, 831 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(15) }, 831, 845 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(10) }, NO_VALUE, 846 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(15) }, 846, 857 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 858 },
    { Anim_Update1, ANIM_STATUS(49, true), false, NO_VALUE, { Q12(18) }, 858, 894 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 895 },
    { Anim_Update1, ANIM_STATUS(50, true), false, NO_VALUE, { Q12(18) }, 895, 931 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 942 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(4.8) }, 942, 965 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M5S00_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 801 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(15) }, 801, 815 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(15) }, NO_VALUE, 816 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(15) }, 816, 822 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(15) }, NO_VALUE, 823 },
    { Anim_Update1, ANIM_STATUS(47, true), false, NO_VALUE, { Q12(524400.4) }, 823, 836 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(15) }, NO_VALUE, 837 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(15) }, 837, 843 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(15) }, NO_VALUE, 844 },
    { Anim_Update1, ANIM_STATUS(49, true), false, NO_VALUE, { Q12(524400.4) }, 844, 857 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(15) }, NO_VALUE, 858 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 858, 884 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(15) }, NO_VALUE, 885 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(15) }, 885, 911 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(15) }, NO_VALUE, 912 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(15) }, 912, 929 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(15) }, NO_VALUE, 930 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(15) }, 930, 945 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M5S02_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 801 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(15) }, 801, 815 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(10) }, NO_VALUE, 816 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(15) }, 816, 827 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(6) }, NO_VALUE, 828 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(6) }, 828, 852 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(10) }, NO_VALUE, 853 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(8) }, 853, 873 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 874 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(8) }, 874, 884 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 885 },
    { Anim_Update1, ANIM_STATUS(50, true), false, NO_VALUE, { Q12(2) }, 885, 888 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 889 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(8) }, 889, 909 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 910 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(10) }, 923, 952 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(10) }, NO_VALUE, 953 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(10) }, 953, 975 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 976 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(10) }, 976, 1007 },
    { Anim_Update2, ANIM_STATUS(55, false), false, ANIM_STATUS(55, true), { Q12(10) }, NO_VALUE, 899 },
    { Anim_Update0, ANIM_STATUS(55, true), false, ANIM_STATUS(55, true), { Q12(8) }, 899, 909 },
    { Anim_Update2, ANIM_STATUS(56, false), false, ANIM_STATUS(56, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(56, true), false, ANIM_STATUS(56, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M5S03_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 801 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(15) }, 801, 815 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(10) }, NO_VALUE, 816 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(15) }, 816, 827 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(10) }, NO_VALUE, 828 },
    { Anim_Update1, ANIM_STATUS(47, true), false, NO_VALUE, { Q12(6) }, 828, 841 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(10) }, NO_VALUE, 842 },
    { Anim_Update1, ANIM_STATUS(48, true), false, NO_VALUE, { Q12(2) }, 842, 845 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 846 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(10) }, 846, 863 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 864 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(10) }, 864, 900 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 901 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(10) }, 901, 955 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M6S00_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 801 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(15) }, 801, 815 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(15) }, NO_VALUE, 816 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(15) }, 816, 822 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(15) }, NO_VALUE, 823 },
    { Anim_Update1, ANIM_STATUS(47, true), false, NO_VALUE, { Q12(524400.4) }, 823, 836 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(15) }, NO_VALUE, 837 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(15) }, 837, 843 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(15) }, NO_VALUE, 844 },
    { Anim_Update1, ANIM_STATUS(49, true), false, NO_VALUE, { Q12(524400.4) }, 844, 857 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(15) }, NO_VALUE, 858 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 858, 884 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(15) }, NO_VALUE, 885 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(15) }, 885, 911 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(15) }, NO_VALUE, 912 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(15) }, 912, 929 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(15) }, NO_VALUE, 930 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(15) }, 930, 945 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 956 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(4) }, 956, 979 },
    { Anim_Update2, ANIM_STATUS(55, false), false, ANIM_STATUS(55, true), { Q12(18) }, NO_VALUE, 980 },
    { Anim_Update0, ANIM_STATUS(55, true), false, ANIM_STATUS(55, true), { Q12(10) }, 980, 1001 },
    { Anim_Update2, ANIM_STATUS(56, false), false, ANIM_STATUS(56, true), { Q12(3) }, NO_VALUE, 1002 },
    { Anim_Update0, ANIM_STATUS(56, true), false, ANIM_STATUS(56, true), { Q12(10) }, 1002, 1038 },
    { Anim_Update2, ANIM_STATUS(57, false), false, ANIM_STATUS(57, true), { Q12(18) }, NO_VALUE, 1039 },
    { Anim_Update0, ANIM_STATUS(57, true), false, ANIM_STATUS(57, true), { Q12(10) }, 1039, 1048 },
    { Anim_Update2, ANIM_STATUS(58, false), false, ANIM_STATUS(58, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(58, true), false, ANIM_STATUS(58, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M6S01_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 680 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(10) }, 680, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 699 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 700 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(10) }, 700, 721 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(3) }, NO_VALUE, 722 },
    { Anim_Update1, ANIM_STATUS(42, true), false, NO_VALUE, { Q12(2) }, 722, 725 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M6S02_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(10) }, 678, 713 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 718 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 718, 732 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 737 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 737, 751 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 758 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(10) }, 758, 770 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 777 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 777, 789 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 790 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(18) }, 790, 804 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 805 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(18) }, 805, 819 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(15) }, NO_VALUE, 820 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(15) }, 820, 826 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(15) }, NO_VALUE, 827 },
    { Anim_Update1, ANIM_STATUS(47, true), false, NO_VALUE, { Q12(524400.4) }, 827, 840 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(15) }, NO_VALUE, 841 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(15) }, 841, 847 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(15) }, NO_VALUE, 848 },
    { Anim_Update1, ANIM_STATUS(49, true), false, NO_VALUE, { Q12(524400.4) }, 848, 861 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(15) }, NO_VALUE, 862 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 862, 888 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(15) }, NO_VALUE, 889 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(15) }, 889, 915 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(15) }, NO_VALUE, 916 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(15) }, 916, 933 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(15) }, NO_VALUE, 934 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(15) }, 934, 949 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 950 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(20) }, 950, 960 },
    { Anim_Update2, ANIM_STATUS(55, false), false, ANIM_STATUS(55, true), { Q12(10) }, NO_VALUE, 961 },
    { Anim_Update0, ANIM_STATUS(55, true), false, ANIM_STATUS(55, true), { Q12(10) }, 961, 1005 },
    { Anim_Update2, ANIM_STATUS(56, false), false, ANIM_STATUS(56, true), { Q12(3) }, NO_VALUE, 1006 },
    { Anim_Update0, ANIM_STATUS(56, true), false, ANIM_STATUS(56, true), { Q12(2) }, 1006, 1009 },
    { Anim_Update2, ANIM_STATUS(57, false), false, ANIM_STATUS(57, true), { Q12(10) }, NO_VALUE, 1 },
    { Anim_Update1, ANIM_STATUS(57, true), false, NO_VALUE, { Q12(10) }, 1, 23 },
    { Anim_Update2, ANIM_STATUS(58, false), false, ANIM_STATUS(58, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(58, true), false, ANIM_STATUS(58, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M6S03_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(8) }, NO_VALUE, 801 },
    { Anim_Update1, ANIM_STATUS(45, true), false, NO_VALUE, { Q12(18) }, 801, 818 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(8) }, NO_VALUE, 819 },
    { Anim_Update1, ANIM_STATUS(46, true), false, NO_VALUE, { Q12(18) }, 819, 836 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(8) }, NO_VALUE, 837 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(18) }, 837, 854 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(8) }, NO_VALUE, 855 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(18) }, 855, 872 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 873 },
    { Anim_Update1, ANIM_STATUS(49, true), false, NO_VALUE, { Q12(18) }, 873, 909 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 910 },
    { Anim_Update1, ANIM_STATUS(50, true), false, NO_VALUE, { Q12(18) }, 910, 946 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(51, true), false, ANIM_STATUS(51, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M6S04_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(3) }, NO_VALUE, 678 },
    { Anim_Update1, ANIM_STATUS(39, true), false, NO_VALUE, { Q12(2) }, 678, 681 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 682 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 682, 692 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 693 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(10) }, 693, 728 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 733 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 733, 747 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 752 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(15) }, 752, 766 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 773 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 773, 785 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 792 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(10) }, 792, 804 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(8) }, NO_VALUE, 805 },
    { Anim_Update1, ANIM_STATUS(46, true), false, NO_VALUE, { Q12(18) }, 805, 822 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(8) }, NO_VALUE, 823 },
    { Anim_Update1, ANIM_STATUS(47, true), false, NO_VALUE, { Q12(18) }, 823, 840 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(8) }, NO_VALUE, 841 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(18) }, 841, 858 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(8) }, NO_VALUE, 859 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(18) }, 859, 876 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 918 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(15) }, 918, 922 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(5) }, NO_VALUE, 923 },
    { Anim_Update1, ANIM_STATUS(51, true), false, NO_VALUE, { Q12(10) }, 923, 933 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 934 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(5) }, 934, 973 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(10) }, NO_VALUE, 974 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(20) }, 974, 997 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 998 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(20) }, 998, 1021 },
    { Anim_Update2, ANIM_STATUS(55, false), false, ANIM_STATUS(55, true), { Q12(10) }, NO_VALUE, 1022 },
    { Anim_Update1, ANIM_STATUS(55, true), false, NO_VALUE, { Q12(524400.4) }, 1022, 1033 },
    { Anim_Update2, ANIM_STATUS(56, false), false, ANIM_STATUS(56, true), { Q12(10) }, NO_VALUE, 1034 },
    { Anim_Update1, ANIM_STATUS(56, true), false, NO_VALUE, { Q12(524400.4) }, 1034, 1045 },
    { Anim_Update2, ANIM_STATUS(57, false), false, ANIM_STATUS(57, true), { Q12(10) }, NO_VALUE, 1046 },
    { Anim_Update0, ANIM_STATUS(57, true), false, ANIM_STATUS(57, true), { Q12(10) }, 1046, 1064 },
    { Anim_Update2, ANIM_STATUS(58, false), false, ANIM_STATUS(58, true), { Q12(10) }, NO_VALUE, 1065 },
    { Anim_Update0, ANIM_STATUS(58, true), false, ANIM_STATUS(58, true), { Q12(10) }, 1065, 1083 },
    { Anim_Update2, ANIM_STATUS(59, false), false, ANIM_STATUS(59, true), { Q12(10) }, NO_VALUE, 1084 },
    { Anim_Update0, ANIM_STATUS(59, true), false, ANIM_STATUS(59, true), { Q12(10) }, 1084, 1105 },
    { Anim_Update2, ANIM_STATUS(60, false), false, ANIM_STATUS(60, true), { Q12(10) }, NO_VALUE, 1106 },
    { Anim_Update0, ANIM_STATUS(60, true), false, ANIM_STATUS(60, true), { Q12(10) }, 1106, 1125 },
    { Anim_Update2, ANIM_STATUS(61, false), false, ANIM_STATUS(61, true), { Q12(10) }, NO_VALUE, 1126 },
    { Anim_Update0, ANIM_STATUS(61, true), false, ANIM_STATUS(61, true), { Q12(10) }, 1126, 1206 },
    { Anim_Update2, ANIM_STATUS(62, false), false, ANIM_STATUS(62, true), { Q12(10) }, NO_VALUE, 1207 },
    { Anim_Update0, ANIM_STATUS(62, true), false, ANIM_STATUS(62, true), { Q12(10) }, 1207, 1236 },
    { Anim_Update2, ANIM_STATUS(63, false), false, ANIM_STATUS(63, true), { Q12(10) }, NO_VALUE, 1237 },
    { Anim_Update0, ANIM_STATUS(63, true), false, ANIM_STATUS(63, true), { Q12(10) }, 1237, 1336 },
    { Anim_Update2, ANIM_STATUS(64, false), false, ANIM_STATUS(64, true), { Q12(10) }, NO_VALUE, 1337 },
    { Anim_Update0, ANIM_STATUS(64, true), false, ANIM_STATUS(64, true), { Q12(10) }, 1337, 1346 },
    { Anim_Update2, ANIM_STATUS(65, false), false, ANIM_STATUS(65, true), { Q12(10) }, NO_VALUE, 1347 },
    { Anim_Update0, ANIM_STATUS(65, true), false, ANIM_STATUS(65, true), { Q12(10) }, 1347, 1362 },
    { Anim_Update2, ANIM_STATUS(66, false), false, ANIM_STATUS(66, true), { Q12(10) }, NO_VALUE, 1363 },
    { Anim_Update0, ANIM_STATUS(66, true), false, ANIM_STATUS(66, true), { Q12(10) }, 1363, 1410 },
    { Anim_Update2, ANIM_STATUS(67, false), false, ANIM_STATUS(67, true), { Q12(10) }, NO_VALUE, 1411 },
    { Anim_Update0, ANIM_STATUS(67, true), false, ANIM_STATUS(67, true), { Q12(10) }, 1411, 1436 },
    { Anim_Update2, ANIM_STATUS(68, false), false, ANIM_STATUS(68, true), { Q12(10) }, NO_VALUE, 1377 },
    { Anim_Update0, ANIM_STATUS(68, true), false, ANIM_STATUS(68, true), { Q12(10) }, 1377, 1410 },
    { Anim_Update2, ANIM_STATUS(69, false), false, ANIM_STATUS(69, true), { Q12(5) }, NO_VALUE, 1437 },
    { Anim_Update1, ANIM_STATUS(69, true), false, NO_VALUE, { Q12(5) }, 1437, 1452 },
    { Anim_Update2, ANIM_STATUS(70, false), false, ANIM_STATUS(70, true), { Q12(10) }, NO_VALUE, 682 },
    { Anim_Update0, ANIM_STATUS(70, true), false, ANIM_STATUS(70, true), { Q12(10) }, 682, 692 },
    { Anim_Update2, ANIM_STATUS(71, false), false, ANIM_STATUS(71, true), { Q12(10) }, NO_VALUE, 693 },
    { Anim_Update0, ANIM_STATUS(71, true), false, ANIM_STATUS(71, true), { Q12(10) }, 693, 727 },
    { Anim_Update2, ANIM_STATUS(72, false), false, ANIM_STATUS(72, true), { Q12(10) }, NO_VALUE, 728 },
    { Anim_Update0, ANIM_STATUS(72, true), false, ANIM_STATUS(72, true), { Q12(10) }, 728, 792 },
    { Anim_Update2, ANIM_STATUS(73, false), false, ANIM_STATUS(73, true), { Q12(10) }, NO_VALUE, 793 },
    { Anim_Update0, ANIM_STATUS(73, true), false, ANIM_STATUS(73, true), { Q12(10) }, 793, 851 },
    { Anim_Update2, ANIM_STATUS(74, false), false, ANIM_STATUS(74, true), { Q12(10) }, NO_VALUE, 852 },
    { Anim_Update0, ANIM_STATUS(74, true), false, ANIM_STATUS(74, true), { Q12(10) }, 852, 888 },
    { Anim_Update2, ANIM_STATUS(75, false), false, ANIM_STATUS(75, true), { Q12(10) }, NO_VALUE, 889 },
    { Anim_Update0, ANIM_STATUS(75, true), false, ANIM_STATUS(75, true), { Q12(10) }, 889, 918 },
    {}
};*/

/*s_AnimInfo HARRY_M7S00_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update1, ANIM_STATUS(39, true), false, NO_VALUE, { Q12(2) }, 678, 693 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(5) }, NO_VALUE, 694 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(6) }, 694, 710 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 711 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(8) }, 711, 727 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(2) }, NO_VALUE, 728 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(7.5) }, 728, 747 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(4) }, 748, 769 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 770 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 770, 824 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M7S01_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(10) }, 678, 713 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 718 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 718, 732 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 737 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 737, 751 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 758 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(10) }, 758, 770 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 777 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 777, 789 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(8) }, NO_VALUE, 790 },
    { Anim_Update1, ANIM_STATUS(44, true), false, NO_VALUE, { Q12(18) }, 790, 824 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(8) }, NO_VALUE, 825 },
    { Anim_Update1, ANIM_STATUS(45, true), false, NO_VALUE, { Q12(18) }, 825, 858 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(30) }, NO_VALUE, 859 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(24) }, 859, 892 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(30) }, NO_VALUE, 893 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(24) }, 893, 926 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(10) }, NO_VALUE, 927 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(15) }, 927, 941 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 942 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(15) }, 942, 953 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(4) }, NO_VALUE, 954 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(10) }, 954, 974 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(3) }, NO_VALUE, 975 },
    { Anim_Update1, ANIM_STATUS(51, true), false, NO_VALUE, { Q12(2) }, 975, 978 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 979 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(10) }, 979, 1036 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(10) }, NO_VALUE, 1069 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(1048566) }, 1037, 1069 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 1070 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(20) }, 1070, 1085 },
    { Anim_Update2, ANIM_STATUS(55, false), false, ANIM_STATUS(55, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(55, true), false, ANIM_STATUS(55, true), { Q12(10) }, 678, 732 },
    { Anim_Update2, ANIM_STATUS(56, false), false, ANIM_STATUS(56, true), { Q12(10) }, NO_VALUE, 733 },
    { Anim_Update0, ANIM_STATUS(56, true), false, ANIM_STATUS(56, true), { Q12(10) }, 733, 792 },
    { Anim_Update2, ANIM_STATUS(57, false), false, ANIM_STATUS(57, true), { Q12(10) }, NO_VALUE, 793 },
    { Anim_Update0, ANIM_STATUS(57, true), false, ANIM_STATUS(57, true), { Q12(10) }, 793, 833 },
    { Anim_Update2, ANIM_STATUS(58, false), false, ANIM_STATUS(58, true), { Q12(10) }, NO_VALUE, 834 },
    { Anim_Update0, ANIM_STATUS(58, true), false, ANIM_STATUS(58, true), { Q12(10) }, 834, 884 },
    { Anim_Update2, ANIM_STATUS(59, false), false, ANIM_STATUS(59, true), { Q12(20) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(59, true), false, ANIM_STATUS(59, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M7S02_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(10) }, 678, 713 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 718 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(15) }, 718, 732 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 737 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 737, 751 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 758 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(10) }, 758, 770 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 777 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 777, 789 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(8) }, NO_VALUE, 790 },
    { Anim_Update1, ANIM_STATUS(44, true), false, NO_VALUE, { Q12(18) }, 790, 807 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(8) }, NO_VALUE, 808 },
    { Anim_Update1, ANIM_STATUS(45, true), false, NO_VALUE, { Q12(18) }, 808, 825 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(8) }, NO_VALUE, 826 },
    { Anim_Update0, ANIM_STATUS(46, true), false, ANIM_STATUS(46, true), { Q12(18) }, 826, 843 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(8) }, NO_VALUE, 844 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(18) }, 844, 861 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(10) }, NO_VALUE, 862 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(15) }, 862, 876 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 877 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(15) }, 877, 888 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 889 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(10) }, 889, 909 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(3) }, NO_VALUE, 910 },
    { Anim_Update1, ANIM_STATUS(51, true), false, NO_VALUE, { Q12(2) }, 910, 913 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 914 },
    { Anim_Update0, ANIM_STATUS(52, true), false, ANIM_STATUS(52, true), { Q12(10) }, 914, 966 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(20) }, NO_VALUE, 967 },
    { Anim_Update0, ANIM_STATUS(53, true), false, ANIM_STATUS(53, true), { Q12(10) }, 967, 1073 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 1074 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(10) }, 1074, 1107 },
    { Anim_Update2, ANIM_STATUS(55, false), false, ANIM_STATUS(55, true), { Q12(10) }, NO_VALUE, 1108 },
    { Anim_Update0, ANIM_STATUS(55, true), false, ANIM_STATUS(55, true), { Q12(10) }, 1108, 1125 },
    { Anim_Update2, ANIM_STATUS(56, false), false, ANIM_STATUS(56, true), { Q12(10) }, NO_VALUE, 1158 },
    { Anim_Update0, ANIM_STATUS(56, true), false, ANIM_STATUS(56, true), { Q12(1048566) }, 1126, 1158 },
    { Anim_Update2, ANIM_STATUS(57, false), false, ANIM_STATUS(57, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(57, true), false, ANIM_STATUS(57, true), { Q12(10) }, 678, 732 },
    { Anim_Update2, ANIM_STATUS(58, false), false, ANIM_STATUS(58, true), { Q12(10) }, NO_VALUE, 733 },
    { Anim_Update0, ANIM_STATUS(58, true), false, ANIM_STATUS(58, true), { Q12(10) }, 733, 792 },
    { Anim_Update2, ANIM_STATUS(59, false), false, ANIM_STATUS(59, true), { Q12(10) }, NO_VALUE, 793 },
    { Anim_Update0, ANIM_STATUS(59, true), false, ANIM_STATUS(59, true), { Q12(10) }, 793, 833 },
    { Anim_Update2, ANIM_STATUS(60, false), false, ANIM_STATUS(60, true), { Q12(10) }, NO_VALUE, 834 },
    { Anim_Update0, ANIM_STATUS(60, true), false, ANIM_STATUS(60, true), { Q12(10) }, 834, 884 },
    { Anim_Update2, ANIM_STATUS(61, false), false, ANIM_STATUS(61, true), { Q12(20) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(61, true), false, ANIM_STATUS(61, true), { Q12(20) }, 485, 502 },
    {}
};*/

/*s_AnimInfo HARRY_M7S03_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(10) }, NO_VALUE, 676 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(38, true), { Q12(10) }, 676, 677 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(10) }, NO_VALUE, 678 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(39, true), { Q12(15) }, 678, 688 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(10) }, NO_VALUE, 689 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(40, true), { Q12(10) }, 689, 724 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(10) }, NO_VALUE, 729 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(41, true), { Q12(15) }, 729, 743 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(10) }, NO_VALUE, 748 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(42, true), { Q12(15) }, 748, 762 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(10) }, NO_VALUE, 769 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(43, true), { Q12(10) }, 769, 781 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(10) }, NO_VALUE, 788 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(44, true), { Q12(10) }, 788, 800 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(10) }, NO_VALUE, 801 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(45, true), { Q12(10) }, 801, 811 },
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(3) }, NO_VALUE, 812 },
    { Anim_Update1, ANIM_STATUS(46, true), false, NO_VALUE, { Q12(2) }, 812, 815 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(10) }, NO_VALUE, 816 },
    { Anim_Update0, ANIM_STATUS(47, true), false, ANIM_STATUS(47, true), { Q12(10) }, 816, 836 },
    { Anim_Update2, ANIM_STATUS(48, false), false, ANIM_STATUS(48, true), { Q12(10) }, NO_VALUE, 837 },
    { Anim_Update0, ANIM_STATUS(48, true), false, ANIM_STATUS(48, true), { Q12(10) }, 837, 936 },
    { Anim_Update2, ANIM_STATUS(49, false), false, ANIM_STATUS(49, true), { Q12(10) }, NO_VALUE, 937 },
    { Anim_Update0, ANIM_STATUS(49, true), false, ANIM_STATUS(49, true), { Q12(10) }, 937, 960 },
    { Anim_Update2, ANIM_STATUS(50, false), false, ANIM_STATUS(50, true), { Q12(10) }, NO_VALUE, 961 },
    { Anim_Update0, ANIM_STATUS(50, true), false, ANIM_STATUS(50, true), { Q12(10) }, 961, 1054 },
    { Anim_Update2, ANIM_STATUS(51, false), false, ANIM_STATUS(51, true), { Q12(10) }, NO_VALUE, 1055 },
    { Anim_Update1, ANIM_STATUS(51, true), false, NO_VALUE, { Q12(10) }, 1055, 1070 },
    { Anim_Update2, ANIM_STATUS(52, false), false, ANIM_STATUS(52, true), { Q12(10) }, NO_VALUE, 1071 },
    { Anim_Update1, ANIM_STATUS(52, true), false, NO_VALUE, { Q12(10) }, 1071, 1086 },
    { Anim_Update2, ANIM_STATUS(53, false), false, ANIM_STATUS(53, true), { Q12(10) }, NO_VALUE, 1087 },
    { Anim_Update1, ANIM_STATUS(53, true), false, NO_VALUE, { Q12(20) }, 1087, 1110 },
    { Anim_Update2, ANIM_STATUS(54, false), false, ANIM_STATUS(54, true), { Q12(10) }, NO_VALUE, 1124 },
    { Anim_Update0, ANIM_STATUS(54, true), false, ANIM_STATUS(54, true), { Q12(10) }, 1124, 1144 },
    { Anim_Update2, ANIM_STATUS(55, false), false, ANIM_STATUS(55, true), { Q12(10) }, NO_VALUE, 1145 },
    { Anim_Update0, ANIM_STATUS(55, true), false, ANIM_STATUS(55, true), { Q12(10) }, 1145, 1197 },
    { Anim_Update2, ANIM_STATUS(56, false), false, ANIM_STATUS(56, true), { Q12(10) }, NO_VALUE, 1198 },
    { Anim_Update0, ANIM_STATUS(56, true), false, ANIM_STATUS(56, true), { Q12(10) }, 1198, 1249 },
    { Anim_Update2, ANIM_STATUS(57, false), false, ANIM_STATUS(57, true), { Q12(10) }, NO_VALUE, 1250 },
    { Anim_Update1, ANIM_STATUS(57, true), false, NO_VALUE, { Q12(10) }, 1250, 1265 },
    { Anim_Update2, ANIM_STATUS(58, false), false, ANIM_STATUS(58, true), { Q12(10) }, NO_VALUE, 1266 },
    { Anim_Update0, ANIM_STATUS(58, true), false, ANIM_STATUS(58, true), { Q12(10) }, 1266, 1357 },
    { Anim_Update2, ANIM_STATUS(59, false), false, ANIM_STATUS(59, true), { Q12(10) }, NO_VALUE, 1358 },
    { Anim_Update1, ANIM_STATUS(59, true), false, NO_VALUE, { Q12(10) }, 1358, 1374 },
    { Anim_Update2, ANIM_STATUS(60, false), false, ANIM_STATUS(60, true), { Q12(10) }, NO_VALUE, 1375 },
    { Anim_Update0, ANIM_STATUS(60, true), false, ANIM_STATUS(60, true), { Q12(10) }, 1375, 1452 },
    { Anim_Update2, ANIM_STATUS(61, false), false, ANIM_STATUS(61, true), { Q12(10) }, NO_VALUE, 1136 },
    { Anim_Update0, ANIM_STATUS(61, true), false, ANIM_STATUS(61, true), { Q12(10) }, 1136, 1144 },
    { Anim_Update2, ANIM_STATUS(62, false), false, ANIM_STATUS(62, true), { Q12(10) }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(62, true), false, ANIM_STATUS(62, true), { Q12(20) }, 485, 502 },
    {}
};*/

// ===========
// NPC TABLES
// ===========

/*s_AnimInfo BLOODY_INCUBATOR_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0,  false), false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(0,  true),  false, NO_VALUE, { Q12(30) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(1,  false), false, ANIM_STATUS(1, true), { Q12(10) }, NO_VALUE, 0 },
    { Anim_Update0, ANIM_STATUS(1,  true),  false, ANIM_STATUS(1, true), { Q12(10) }, 0, 54 },
    { Anim_Update2, ANIM_STATUS(2,  false), false, ANIM_STATUS(2, true), { Q12(10) }, NO_VALUE, 55 },
    { Anim_Update0, ANIM_STATUS(2,  true),  false, ANIM_STATUS(2, true), { Q12(10) }, 55, 117 },
    { Anim_Update2, ANIM_STATUS(3,  false), false, ANIM_STATUS(3, true), { Q12(10) }, NO_VALUE, 118 },
    { Anim_Update0, ANIM_STATUS(3,  true),  false, ANIM_STATUS(3, true), { Q12(10) }, 118, 152 },
    { Anim_Update2, ANIM_STATUS(4,  false), false, ANIM_STATUS(4, true), { Q12(10) }, NO_VALUE, 153 },
    { Anim_Update0, ANIM_STATUS(4,  true),  false, ANIM_STATUS(4, true), { Q12(10) }, 153, 213 },
    { Anim_Update2, ANIM_STATUS(5,  false), false, ANIM_STATUS(5, true), { Q12(10) }, NO_VALUE, 214 },
    { Anim_Update1, ANIM_STATUS(5,  true),  false, NO_VALUE, { Q12(10) }, 214, 229 },
    { Anim_Update2, ANIM_STATUS(6,  false), false, ANIM_STATUS(6, true), { Q12(10) }, NO_VALUE, 230 },
    { Anim_Update0, ANIM_STATUS(6,  true),  false, ANIM_STATUS(6, true), { Q12(10) }, 230, 260 },
    { Anim_Update2, ANIM_STATUS(7,  false), false, ANIM_STATUS(7, true), { Q12(10) }, NO_VALUE, 261 },
    { Anim_Update1, ANIM_STATUS(7,  true),  false, NO_VALUE, { Q12(10) }, 261, 276 },
    { Anim_Update2, ANIM_STATUS(8,  false), false, ANIM_STATUS(8, true), { Q12(10) }, NO_VALUE, 277 },
    { Anim_Update0, ANIM_STATUS(8,  true),  false, ANIM_STATUS(8, true), { Q12(10) }, 277, 295 },
    { Anim_Update2, ANIM_STATUS(9,  false), false, ANIM_STATUS(9, true), { Q12(10) }, NO_VALUE, 296 },
    { Anim_Update0, ANIM_STATUS(9,  true),  false, ANIM_STATUS(9, true), { Q12(8) }, 296, 365 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(10) }, NO_VALUE, 366 },
    { Anim_Update1, ANIM_STATUS(10, true),  false, NO_VALUE, { Q12(10) }, 366, 382 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(10) }, NO_VALUE, 295 },
    { Anim_Update0, ANIM_STATUS(11, true),  false, ANIM_STATUS(11, true), { Q12(10) }, 295, 295 }
};*/

/*s_AnimInfo GHOST_DOCTOR_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(0, true), false, NO_VALUE, { Q12(30) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(5) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(1, true), false, NO_VALUE, { Q12(15) }, 0, 15 }
};*/

/*s_AnimInfo INCUBATOR_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0)    }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(0, true),  false, NO_VALUE,              { Q12(30)   }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true),  { Q12(10)   }, NO_VALUE, 0   },
    { Anim_Update0, ANIM_STATUS(1, true),  false, ANIM_STATUS(1, true),  { Q12(6.1f) }, 0,        74  },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true),  { Q12(10)   }, NO_VALUE, 75  },
    { Anim_Update0, ANIM_STATUS(2, true),  false, ANIM_STATUS(2, true),  { Q12(10)   }, 75,       115 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true),  { Q12(10)   }, NO_VALUE, 116 },
    { Anim_Update1, ANIM_STATUS(3, true),  false, NO_VALUE,              { Q12(10)   }, 116,      132 }
};*/

/*s_AnimInfo MONSTER_CYBIL_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0)  }, NO_VALUE, 0  },
    { Anim_Update1, ANIM_STATUS(0, true),  false, NO_VALUE,              { Q12(30) }, NO_VALUE, 1  },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true),  { Q12(1)  }, NO_VALUE, 0  },
    { Anim_Update1, ANIM_STATUS(1, true),  false, NO_VALUE,              { func_800D8898 },  0,        23 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true),  { Q12(5)  }, NO_VALUE, 24 }
};*/

/** @brief Heading angle quadrants. TODO: Order uncertain. North/South and East/West could be swapped. */
typedef enum _Quadrant
{
    Quadrant_South = 0,
    Quadrant_North = 1,
    Quadrant_West  = 2,
    Quadrant_East  = 3
} e_Quadrant;

typedef struct
{
    char unk_0[3420];
    u16  field_D5C;
    s16  field_D5E;
} s_func_800D8714;

/** @brief Stores SFX ID and volume.
 *  Volume union required becase one function reads the value as `u16`, another as `u8`.
 *  Actual value fits into `u8` (8 bit volume control).
 */
typedef struct _SfxVolume
{
    u16 id_0;
    union
    {
        u8  val8;
        u16 val16;
    } volume_2;
} s_SfxVolume;

typedef struct
{
    s_AnimInfo  animInfo_0[56];
    s32         unk_380[301][2]; // Unknown size, biggest constant index used is 35. Associated with anims.
    s_SfxVolume sfxVolumes_CE8[11];
    u_Property  properties_D14[4];
    u16         field_D24[2][3][2];
    u8          field_D3C[2][6];
    SVECTOR*    ptr_D48[5];
    s16         field_D5C[4][2]; // Related to animations. Move offset distances?
    s8          unk_D6C[4];
    s16         field_D70[2][2];
} s_func_800D2E04;

typedef struct
{
    s32               flags_0;
    s_AnmHeader*      anmHdr_4;
    GsCOORDINATE2*    coords_8;
    VECTOR3           matrices_C[1]; // Unknown size.
    s8                unk_10[0x84];
    s_SubCharacter_C8 field_9C;
    s_SubCharacter_D4 field_A8;
    s_SubCharacter_D8 field_AC;
    s32               field_B4[6][4]; // [*][3] is angle.
    s32               field_114;
    s32               field_118;
    VECTOR3           field_11C; // Q19.12
    VECTOR3           field_128;
    VECTOR3           field_134;
    VECTOR3           unk_140;
    union
    {
        struct
        {
            u8  field_14C_0 : 1;
            u8  field_14C_1 : 1;
            u8  field_14C_2 : 1;
            u8  field_14C_3 : 1;
            u32 field_14C_4 : 28; // Unsure if used.
        } bits;
        // @hack Some functions only match when bits are defined as `u32`, but that breaks other functions.
        struct
        {
            u32 field_14C_0 : 1;
            u32 field_14C_1 : 1;
            u32 field_14C_2 : 1;
            u32 field_14C_3 : 1;
            u32 field_14C_4 : 28;
        } bits32;
        u32 flags;
    } field_14C;
    q19_12 distance_150;
    q19_12 angle_154;
    q19_12 field_158; // Displacement distance.
    s32    field_15C;
} s_sharedData_800E21D0_0_s01;

// Used by puzzle in M5S01 and M7S01.
typedef struct
{
    u8 field_0; // Q12
    u8 field_1;
} s_800F0158;

typedef struct
{
    u16 sfxId;
    u16 vol;
} s_SfxPair;

typedef struct
{
    SVECTOR3 vec;
    s16      idx;
} s_sharedData_800D5AB0_1_s05;

extern s_MapOverlayHeader_94 sharedData_800E30C8_1_s02;

#if defined(MAP_FIELD_4C_COUNT)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[MAP_FIELD_4C_COUNT];
#else
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[];
#endif

#if defined(MAP_BLOOD_SPLAT_COUNT_MAX)
    extern s_BloodSplat g_Effect_BloodSplats[MAP_BLOOD_SPLAT_COUNT_MAX];
#else
    extern s_BloodSplat g_Effect_BloodSplats[];
#endif

/** Air Screamer or Night Flutter control functions. Indexed using `e_AirScreamerControl`. */
extern void (*g_Ai_AirScreamer_ControlFuncs[52])(s_SubCharacter* airScreamer); // TODO: Use `AirScreamerControl_Count`.

extern s_MapPoint2d MAP_POINTS[];
extern s_EventData  MAP_EVENTS[];
extern void (*g_LoadScreenFuncs[])();
extern void (*g_MapEventFuncs[])();
extern u8 LOADABLE_INVENTORY_ITEMS[];
extern s_UnkStruct3_Mo g_MapHeaderTable_38[];

/** Scale. */
extern VECTOR sharedData_800DD870_0_s01;

/** Scale. */
extern VECTOR sharedData_800DD880_0_s01;

/** Could be a padded `VECTOR`, but the ASM for the function `vec = vec` assignments copies only the first 3 fields. */
extern VECTOR3 sharedData_800DE170_0_s01;
extern VECTOR3 sharedData_800DE180_0_s01; // Q19.12 player position relevant to Air Screamer.
extern VECTOR3 sharedData_800DE190_0_s01;

extern s_RayData sharedData_800E2330_0_s01;

/** Packed weapon attack. `See `WEAPON_ATTACK`. */
extern s8 sharedData_800DD59C_0_s00;

extern s32 sharedData_800DF1F4_0_s00;
extern s16 sharedData_800DF1F8_0_s00;
extern s16 sharedData_800DF1FA_0_s00;

/** Something related to rotation. */
extern s32 sharedData_800E39D8_0_s00;

// Next 4 set by `Ai_Stalker_Update`.
extern q19_12 sharedData_800E3A20_0_s00; // Health.
extern q19_12 sharedData_800E3A24_0_s00; // Health.
extern q19_12 sharedData_800E3A28_0_s00;
extern q19_12 sharedData_800E3A2C_0_s00;

// Used by `Ai_Stalker`/`Ai_LarvalStalker`.
extern u8  sharedData_800DD5A6_0_s00;
extern s32 sharedData_800E39E4_0_s00;
extern s32 sharedData_800E39E8_0_s00;
extern s32 sharedData_800E39EC_0_s00[];
extern u16 sharedData_800E3A0C_0_s00[];  // Angles?
extern q19_12 sharedData_800E3A18_0_s00; // Player X position?
extern q19_12 sharedData_800E3A1C_0_s00; // Player Z position?

extern s_AnimInfo LARVAL_STALKER_ANIM_INFOS[]; // Used by `Ai_LarvalStalker_Init`.

extern s_AnimInfo STALKER_ANIM_INFOS[]; // Used by `Ai_Stalker_Init`.

// Two variables used by `Ai_Creeper_Init`.
extern s_AnimInfo CREEPER_ANIM_INFOS[];
extern s8 sharedData_800E57CC_1_s02;

extern s_sharedData_800E21D0_0_s01 sharedData_800E21D0_0_s01;

extern s_func_800D2E04 const sharedData_800CAA98_0_s01; // Used by `Ai_AirScreamer_Init` / `sharedFunc_800D2BF4_0_s01`

extern s_AnimInfo ROPMER_ANIM_INFOS[];

extern s_AnimInfo GROANER_ANIM_INFOS[];

extern s_AnimInfo HANGED_SCRATCHER_ANIM_INFOS[];

// Three variables used by `Ai_SplitHead_Init`.
extern s_AnimInfo SPLIT_HEAD_ANIM_INFOS[];
extern q3_12 sharedData_800D8614_1_s05; // Offset X.
extern q3_12 sharedData_800D8616_1_s05; // Offset Z.

extern s32 sharedData_800D5884_1_s05;

extern s16 sharedData_800D5A8C_1_s05;

extern u8 sharedData_800D5AAE_1_s05;
extern u8 sharedData_800D5AAF_1_s05;

extern u8      sharedData_800D5CF8_1_s05[];
extern u8      sharedData_800D5D08_1_s05[];
extern VECTOR3 sharedData_800D8618_1_s05[];
extern SVECTOR3 sharedData_800D5A90_1_s05[]; // Q7.8

extern s_sharedData_800D5AB0_1_s05 sharedData_800D5AB0_1_s05[];
extern s16                         sharedData_800D5BE0_1_s05[6][3];

extern u8  sharedData_800D16E4_2_s01;

extern s_AnimInfo BLOODSUCKER_ANIM_INFOS[];

extern u8 sharedData_800DD591_0_s00;
extern u8 sharedData_800DD584_0_s00;

extern s_AnimInfo MONSTER_CYBIL_ANIM_INFOS[];
extern s_AnimInfo BLOODY_INCUBATOR_ANIM_INFOS[];
extern s_AnimInfo INCUBATOR_ANIM_INFOS[];
extern s_AnimInfo GHOST_DOCTOR_ANIM_INFOS[];

extern s32 sharedData_800DFB6C_0_s00;
extern s32 sharedData_800DFB70_0_s00;

extern s32 sharedData_800DD58C_0_s00;
extern s32 sharedData_800E32CC_0_s00;

extern u16 sharedData_800D21E8_3_s00[];

extern u16 sharedData_800E32D4_0_s00;

extern s32 sharedData_800DD598_0_s00;

extern CVECTOR sharedData_800E3258_0_s00;

extern CVECTOR sharedData_800E325C_0_s00;

extern s32 sharedData_800E2370_0_s01[2];

// Each of these holds 8 bytes, passed to `Bgm_Update` which loops through each byte.
extern u8 sharedData_800CFB14_0_s02[8];
extern u8 sharedData_800CFB1C_0_s02[8];
extern u8 sharedData_800CFB24_0_s02[8];
extern u8 sharedData_800CFB2C_0_s02[8];
extern u8 sharedData_800CFB34_0_s02[8];
extern u8 sharedData_800CFB3C_0_s02[8];
extern u8 sharedData_800CFB44_0_s02[8];
extern u8 sharedData_800CFB4C_0_s02[8];
extern u8 sharedData_800CFB54_0_s02[8];

/** Q19.12 */
extern VECTOR3 sharedData_800DE1A0_0_s01;

extern VECTOR3 sharedData_800DE1B0_0_s01;

extern VECTOR3 sharedData_800DE1C0_0_s01;

extern VECTOR3 sharedData_800DE1E0_0_s01;

extern VECTOR3 sharedData_800DE1F0_0_s01; // Q19.12

extern s_800C4590 sharedData_800E2350_0_s01;

extern s_800C4590 sharedData_800E39BC_0_s00;

extern s32 sharedData_800DD5A0_0_s00;
extern s16 sharedData_800DD5A4_0_s00; // Used as index into array of vectors.
extern s16 sharedData_800E39E0_0_s00;
extern s16 sharedData_800E39E2_0_s00;

extern s32 sharedData_800D8684_1_s05;
extern s32 sharedData_800D8688_1_s05;

extern u8      sharedData_800EB738_6_s04;
extern u8      sharedData_800EB740_6_s04[2];
extern u8      sharedData_800EB748_6_s04;
extern s8      sharedData_800EB74A_6_s04;
extern VECTOR3 sharedData_800EB750_6_s04;

extern s16 sharedData_800D5880_1_s05;

extern u8 sharedData_800E1208_1_s02[8];
extern u16 sharedData_800E1210_1_s02[42]; // Flags.

typedef struct
{
    VECTOR3 field_0; // Rotation?
    s16     field_C;
    s16     field_E;
    s8      field_10;
    u8      field_11;
    u8      field_12;
    s8      field_13;
} s_800E34FC;
STATIC_ASSERT_SIZEOF(s_800E34FC, 20);

typedef struct
{
    VECTOR3  field_0;
    SVECTOR3 field_C; // 2D position or offset.
    u8       unk_12[2];
    u8       field_14;
    u8       field_15;
    u8       field_16; // Packed angle?
} s_800E330C;
STATIC_ASSERT_SIZEOF(s_800E330C, 24);

typedef struct
{
    s32   field_0;
    s32   field_4;
    q3_12 field_8; // Y offset.
    s16   field_A;
} s_D_800D5A8C;
STATIC_ASSERT_SIZEOF(s_D_800D5A8C, 12);

typedef struct _MapHeader_field_5C
{
    u8    flags_0;
    u8    field_1;
    u8    field_2;
    u8    field_3;
    u8    field_4;
    u8    field_5;
    u8    field_6;
    u8    field_7;
    u16   field_8;
    s16   field_A;
    u16   field_C;
    s16   field_E;
    q3_12 field_10;
    s16   field_12;
    s16   field_14;
    s16   field_16;
    s16   field_18;
    s16   field_1A;
    u16   field_1C;
    s16   field_1E;
    s32   field_20;
    s32   field_24;
} s_MapHeader_field_5C;

typedef struct
{
    s32 vx;
    s32 vy;
    s16 vz;
} s_sharedData_800DFB10_0_s01;

typedef struct
{
    q19_12 field_0; // Relative anim time?
    s32    field_4;
} s_sharedData_800ED2D4_2_s02;

extern s_MapHeader_field_5C sharedData_800D8568_1_s05;

extern s_800E330C sharedData_800E330C_0_s00[20];

extern s_800E34FC sharedData_800E34FC_0_s00[60];

extern const char* MAP_MESSAGES[]; // 0x800DF6B8

extern s_MapOverlayHeader_7C sharedData_800DEE50_1_s01;

extern u8 sharedData_800EEAC4_2_s00[][4][4];

extern VECTOR3 sharedData_800F216C_2_s00;

extern VECTOR3 sharedData_800F217C_2_s00;

extern VECTOR3 sharedData_800F21BC_2_s00;

extern VECTOR3 sharedData_800F21CC_2_s00;

extern VECTOR3 sharedData_800F21DC_2_s00;

extern VECTOR3 sharedData_800F21EC_2_s00;

extern VECTOR3 sharedData_800F21FC_2_s00;

extern VECTOR sharedData_800DE200_0_s01;

extern VECTOR3 sharedData_800DE210_0_s01;

extern SVECTOR sharedData_800DE220_0_s01;

extern MATRIX sharedData_800DE230_0_s01;

extern s32 g_PuppetNurseHurtSfxIdxs[4];

extern s_SfxPair g_NursePuppetSfxs[18];

// Only used by `Ai_PuppetNurse_AnimSfxGet`. Currently causes a mismatch. Try to move it when more code gets decompiled.
extern u8 g_NursePuppet_SfxOffsets[4]; // = { 9, 6, 7, 8 };

// Only used by `Ai_PuppetNurse_Control8`. Currently causes a mismatch. Try to move it when more code gets decompiled.
extern u16 g_PuppetNurse_ModelStates0[8]; // = { 9, 9, 9, 6, 6, 9, 7, 7 }; // + 2 bytes of padding.

extern u8 g_NursePuppet_AnimSfxs[580];

extern s32 g_PuppetNurse_AnimStatus0[2];

extern s32 g_PuppetNurse_AnimStatus1[2];

extern u8  g_PuppetNurse_AnimStatus2[2];

extern u8  g_PuppetNurse_AnimStatus3[4];

extern u8  g_PuppetNurse_AnimStatus4[4];

extern u8      sharedData_800D4CD4_3_s01[][2];
extern DVECTOR sharedData_800D4D0C_3_s01;
extern VECTOR3 sharedData_800CB088_3_s01;
extern VECTOR3 sharedData_800CB094_3_s01;
extern VECTOR3 sharedData_800CB0A0_3_s01;
extern s32     sharedData_800D4D10_3_s01;
extern s32     sharedData_800D4D14_3_s01;
extern s8      sharedData_800D4D18_3_s01;

extern s_D_800D5A8C sharedData_800D5A8C_3_s03[3];

extern u8 sharedData_800D1D14_3_s02[8];

/** Room flags? */
extern u16 sharedData_800D1D1C_3_s02[60];

extern s_sharedData_800DFB10_0_s01 sharedData_800DFB10_0_s01[];

extern u8 sharedData_800ED430_2_s02[];

extern u8 sharedData_800ED43C_2_s02[];

extern s_sharedData_800ED2D4_2_s02 sharedData_800ED2D4_2_s02[];

extern s32 sharedData_800EC950_2_s02;

extern s32 sharedData_800ECA4C_2_s02;

extern s32 sharedData_800ECACC_2_s02;

extern s16 sharedData_800ECB22_2_s02;

extern s16 sharedData_800ECBC2_2_s02;

extern s16 sharedData_800ECBD0_2_s02;

extern s_sharedData_800ED2D4_2_s02 sharedData_800ED314_2_s02[];

extern u8  sharedData_800EFCFC_6_s00[8];
extern s32 sharedData_800EFD04_6_s00;
extern u16 sharedData_800EFD08_6_s00[];
extern u16 sharedData_800EFD34_6_s00[];


extern u8 sharedData_800ED418_4_s02[8];
extern s32 sharedData_800ED420_4_s02;
extern u8 sharedData_800ED424_4_s02[8];
extern u16 sharedData_800ED42C_4_s02[];
extern u8 sharedData_800ED458_4_s02[8];

extern void (*g_Romper_ControlFuncs[])(s_SubCharacter* romper);

extern s_Bgm_Update sharedData_800D2F18_7_s00;
extern s_Bgm_Update sharedData_800D2F20_7_s00;
extern u16          sharedData_800D2F28_7_s00[38]; // Flags array.
extern s_Bgm_Update sharedData_800D2F74_7_s00;
extern s_Bgm_Update sharedData_800D2F7C_7_s00;
extern s_Bgm_Update sharedData_800D2F84_7_s00;

extern s32 sharedData_800E1570_7_s01;
extern s32 sharedData_800E1574_7_s01;
extern u8  sharedData_800E1578_7_s01[3][3][3][2];
extern u32 sharedData_800E1694_7_s01;
extern s32 sharedData_800E2CA8_7_s01;
extern s32 sharedData_800E2CAC_7_s01;

void sharedFunc_800DB60C_7_s01(void);

bool sharedFunc_800CE688_1_s03(POLY_FT4** poly, s32 idx);

bool sharedFunc_800CD1F8_0_s01(POLY_FT4** poly, s32 idx);

void Map_RoomBgmInit(bool arg0);

void Map_RoomBgmInit_CondTrue(void);

void Map_RoomBgmInit_CondFalse(void);

void sharedFunc_800CAAD0_1_s05(void);

void sharedFunc_800CABF8_1_s05(s32 idx, bool arg1);

bool sharedFunc_800CB040_1_s05(POLY_FT4** poly, s32 idx);

bool sharedFunc_800CB884_1_s05(POLY_FT4** poly, s32 idx);

void sharedFunc_800CBE7C_1_s05(q23_8 posX, q23_8 posY, q23_8 posZ, s32 arg3, s32 arg4);

void sharedFunc_800CCDD4_1_s05(POLY_FT4** poly, s32 idx);

void sharedFunc_800CCE2C_1_s05(s32 arg0, s32 arg1, q23_8 posX0, q23_8 posY0, q23_8 posZ0, q23_8 posX1, q23_8 posY1, q23_8 posZ1);

void sharedFunc_800D4408_1_s05(VECTOR3* pos, s32 idx, q23_8 posX, q23_8 posY, q23_8 posZ);

q19_12 sharedFunc_800D7714_0_s01(s_SubCharacter* chara);

/* TODO: This function is almost identical to `sharedFunc_800D57C8_0_s01`.
 * Both are used in map0_s01 so ifdefs cannot be used based on the map name.
 * Sections under `#if 0` are what is missing compared to `sharedFunc_800D57C8_0_s01`.
 */
void sharedFunc_800D598C_0_s01(s_SubCharacter* airScreamer);

// Probably all Air Screamer section below. Unsure about functions above.

/* TODO: This function is almost identical to `sharedFunc_800D57C8_0_s01`.
 * Also look at `sharedFunc_800D598C_0_s01`.
 */
void sharedFunc_800D5B10_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D5C90_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D5D80_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D5E14_0_s01(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_2(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_3(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_5(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_6(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_7(s_SubCharacter* airScreamer);

bool sharedFunc_800D4AEC_0_s01(s_SubCharacter* airScreamer, VECTOR3* arg1, VECTOR3* arg2, VECTOR3* arg3);

void Ai_AirScreamer_Control_8(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_9(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_11(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_12(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_13(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_14(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_15(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_16(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_17(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_18(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_19(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_20(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_21(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_22(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_23(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_24(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_25(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_26(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_27(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_28(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_30(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_31(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_32(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_33(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_34(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_36(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_37(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_40(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_41(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_42(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_43(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_44(s_SubCharacter* airScreamer);

void Ai_AirScreamer_Control_45(s_SubCharacter* airScreamer);

bool sharedFunc_800DBF88_2_s00(s_SubCharacter* airScreamer, s32 arg1);

/** Checks if an Air Screamer is below the ground with a slight height intolerance. */
bool sharedFunc_800DC0A8_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DC0E4_2_s00(s_SubCharacter* airScreamer, q19_12 moveSpeedMult);

bool sharedFunc_800DC200_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DC30C_2_s00(s_SubCharacter* airScreamer);

/** Checks if an Air Screamer is near the ground? */
bool sharedFunc_800DC3BC_2_s00(s_SubCharacter* airScreamer);

/** State step getter. */
s32 sharedFunc_800DC438_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DC50C_2_s00(s_SubCharacter* airScreamer);

s32 sharedFunc_800DC598_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DC67C_2_s00(s_SubCharacter* airScreamer);

/** Chance getter? */
q19_12 sharedFunc_800DC6E4_2_s00(s_SubCharacter* airScreamer, q19_12 arg1);

/** Chance getter? */
q19_12 sharedFunc_800DC894_2_s00(s_SubCharacter* airScreamer, q19_12 dist);

void sharedFunc_800DD13C_2_s00(s_SubCharacter* airScreamer, s32 npcSlot, q19_12 spawnChance);

void sharedFunc_800DD2C4_2_s00(s_SubCharacter* airScreamer, s32 arg1, s32 arg2);

void sharedFunc_800DD4A4_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DD4EC_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DD534_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DD588_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DD834_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DDA80_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DDE14_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DDF74_2_s00(s_SubCharacter* airScreamer, q19_12 dist, q19_12 headingAngle);

void sharedFunc_800DE034_2_s00(s_SubCharacter* airScreamer, VECTOR3* vec, q19_12 dist);

void sharedFunc_800DE11C_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DE250_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DE578_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DE6A8_2_s00(s_SubCharacter* airScreamer, VECTOR3* vec, q19_12 dist);

void sharedFunc_800DE7E0_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DEBCC_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DECC4_2_s00(s_SubCharacter* airScreamer);

q19_12 sharedFunc_800DEE24_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DF358_2_s00(s_SubCharacter* airScreamer);

/** Condition is probably to differentiate between an Air Screamer and Night Flutter. */
void sharedFunc_800DF448_2_s00(s_SubCharacter* airScreamer, bool cond);

void sharedFunc_800DF60C_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DF710_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DF80C_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DF8A0_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800E012C_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800E021C_2_s00(s_SubCharacter* airScreamer, s32 arg1, s32 arg2);

void sharedFunc_800E041C_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800E04B0_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800E0514_2_s00(s_SubCharacter* airScreamer);

/** Air Screamer state step getter. `const` is required for match. */
bool sharedFunc_800D5F00_0_s01(s_SubCharacter* const airScreamer);

/** Among other things, sets the players's anim to anim 3 (which might actually be flags if the field packs more data). */
void sharedFunc_800D88C0_0_s00(s_SubCharacter* player, bool cond);

/** Resets some player properties. */
void sharedFunc_800D8904_0_s00(s_SubCharacter* player, q19_12 afkTime);

void sharedFunc_800D891C_0_s00(s_SubCharacter* player);

/** Locks a character's animation. */
void sharedFunc_800D8928_0_s00(s_SubCharacter* chara);

/** Unlocked flag getter. */
s32 sharedFunc_800D893C_0_s00(s_SubCharacter* chara);

/** Unlocks a character's animation. */
void sharedFunc_800D8950_0_s00(s_SubCharacter* chara);

bool sharedFunc_800D8A00_0_s00(s_SubCharacter* chara, s32 arg1, VECTOR3* arg2In, s32 angleIn, s32 arg4);

void sharedFunc_800D9064_0_s00(s_SubCharacter* chara);

void sharedFunc_800D9078_0_s00(s_SubCharacter* chara);

s32 Anim_StartKeyframeIdxGet(s_SubCharacter* chara);

/** Humanoid init function? */
void sharedFunc_800D923C_0_s00(s_SubCharacter* chara);

void SysWork_StateStepIncrementAfterTime(q19_12* timer, q19_12 inc, q19_12 timeMin, q19_12 timeMax, bool setTimerToMax, bool incStateStep);

void sharedFunc_800CB7F4_1_s01(void);

void sharedFunc_800CB8A0_1_s01(s32 idx);

bool sharedFunc_800CBA38_1_s01(s32 idx);

bool sharedFunc_800CBB30_1_s01(POLY_FT4** poly, s32 idx);

bool sharedFunc_800CBDA8_1_s02(POLY_FT4** poly, s32 idx);

void sharedFunc_800CCE60_1_s02(void);

bool sharedFunc_800CBF74_1_s05(POLY_FT4** poly, s32 idx);

bool sharedFunc_800CC618_1_s05(POLY_FT4** poly, s32 idx);

bool sharedFunc_800CCF30_1_s05(POLY_FT4** poly, s32 idx);

/** Unsure which character this takes, stalker doesn't fit? */
void sharedFunc_800D88AC_0_s00(s_SubCharacter* stalker);

// MAP3_S03 puppet nurse/doctor funcs

void sharedFunc_800CDA88_3_s03(s_SubCharacter* nurse);

void Ai_PuppetNurse_UpdateMain(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800CDB5C(s_SubCharacter* nurse, s32);

void Ai_PuppetNurse_Init(s_SubCharacter* nurse, bool isPuppetDoctor);

void Ai_PuppetNurse_Update(s_SubCharacter* nurse, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_PuppetDoctor_Update(s_SubCharacter* doctor, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_PuppetNurse_DamageHandle(s_SubCharacter* nurse);

s32 PuppetNurse_HurtSfxIdGet(s_SubCharacter* nurse);

void Ai_PuppetNurse_SfxPlay(s_SubCharacter* nurse, s32 idx);

s32 Ai_PuppetNurse_AnimSfxGet(s32 idx);

/** Checks damage angle. */
bool Ai_PuppetNurse_SomeAngleCheck(s_SubCharacter* nurse);

void Ai_PuppetNurse_Move(s_SubCharacter* nurse);

/** Checks if some special animation is set. */
bool sharedFunc_800CE398_3_s03(s32 animStatus);

void Ai_PuppetNurse_Control1(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control2(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control3_4(s_SubCharacter* nurse, bool isDoctor);

bool sharedFunc_800CE7C8_3_s03(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control5(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control6_7(s_SubCharacter* nurse, bool isDoctor);

void Ai_PuppetNurse_Control8(s_SubCharacter* nurse);

s32 sharedFunc_800CEEAC_3_s03(void);

void Ai_PuppetNurse_Control9(s_SubCharacter* nurse);

s32 sharedFunc_800CF600_3_s03(s_SubCharacter* nurse);

void sharedFunc_800CF7F4_3_s03(s_SubCharacter* nurse);

bool sharedFunc_800CF90C_3_s03(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control12(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control10(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control11(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control13(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control(s_SubCharacter* nurse);

void sharedFunc_800D02E4_3_s03(s_SubCharacter* nurse, GsCOORDINATE2* coords);

void sharedFunc_800D03E4_3_s03(s_SubCharacter* nurse);

void Ai_PuppetNurse_AnimUpdate(s_SubCharacter* nurse, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

// Not Harry?
void sharedFunc_800D0828_3_s03(s_SubCharacter* harry, GsCOORDINATE2* coords);

void sharedFunc_800D0968_3_s03(s_SubCharacter* nurse, GsCOORDINATE2* coords);

void Ai_Creeper_Update(s_SubCharacter* creeper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Creeper_Init(s_SubCharacter* creeper); // `map5_s00` version has extra code at end of func.

void sharedFunc_800D7EE8_1_s02(s_SubCharacter* creeper);

void Ai_Creeper_ControlUpdate(s_SubCharacter* creeper);

void Ai_Creeper_Control_1(s_SubCharacter* creeper);

void Ai_Creeper_Control_2(s_SubCharacter* creeper);

void Ai_Creeper_Control_3(s_SubCharacter* creeper);

void Ai_Creeper_Control_4(s_SubCharacter* creeper);

void Ai_Creeper_Control_5(s_SubCharacter* creeper);

void sharedFunc_800D983C_1_s02(s_SubCharacter* creeper);

void sharedFunc_800D9960_1_s02(s_SubCharacter* creeper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void sharedFunc_800D99D0_1_s02(s_SubCharacter* creeper);

bool sharedFunc_800D3508_0_s01(s_SubCharacter* airScreamer, q19_12* dist);

bool sharedFunc_800D3630_0_s01(s_SubCharacter* airScreamer, q19_12* dist);

/** Returns flags? Specific to Air Screamer? */
s32 sharedFunc_800D3758_0_s01(s_SubCharacter* airScreamer, q19_12* outDist, q19_12* outAngle, q19_12 dist, s32* arg4);

void Ai_Romper_Update(s_SubCharacter* romper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Romper_Init(s_SubCharacter* romper);

/** Probably Romper func given the placement. */
void sharedFunc_800E5FC8_2_s02(s_SubCharacter* chara, s16 arg1, s16 arg2, u8* arg3);

void sharedFunc_800E60FC_2_s02(s_SubCharacter* romper);

void sharedFunc_800E6420_2_s02(s_SubCharacter* romper);

void Ai_Romper_ControlUpdate(s_SubCharacter* romper);

void Ai_Romper_Control_1(s_SubCharacter* romper);

void Ai_Romper_Control_8(s_SubCharacter* romper);

void Ai_Romper_Control_9(s_SubCharacter* romper);

void Ai_Romper_Control_11(s_SubCharacter* romper);

void sharedFunc_800E8730_2_s02(s_SubCharacter* romper);

void sharedFunc_800E8A40_2_s02(s_SubCharacter* romper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void sharedFunc_800E8DFC_2_s02(s_SubCharacter* romper);

s32 sharedFunc_800E939C_2_s02(s_SubCharacter* romper);

s32 sharedFunc_800E94B4_2_s02(s_SubCharacter* romper);

void sharedFunc_800E9714_2_s02(s_SubCharacter* romper);

void Ai_Groaner_Update(s_SubCharacter* groaner, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Groaner_Init(s_SubCharacter* groaner); // `map2_s00` has extra block at end of func compared to other maps.

void sharedFunc_800E554C_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E55B0_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E33DC_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E384C_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E39D8_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E3E94_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E4830_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E4E84_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E5930_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E5AA4_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E5EC4_2_s00(s_SubCharacter* groaner, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void sharedFunc_800E6338_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E71E8_2_s00(s_SubCharacter* groaner);

/** Related to Air Screamer? */
extern GsCOORDINATE2* sharedData_800D8610_1_s05;

/** Unclear, but funcs past here may be specific to Air Screamer. */

void sharedFunc_800D8804_0_s01(void);

s32 sharedFunc_800D929C_0_s00(void);

/** NPC anim func. Checks if the active keyframe is at the start or end of the anim's range. */
s32 sharedFunc_800D8964_0_s00(s_SubCharacter* chara);

bool sharedFunc_800D9188_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx, s32 sfxId);

bool sharedFunc_800D908C_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx0, s32 keyframeIdx1, s32 sfxId, s32 pitch);

void sharedFunc_800CCB8C_0_s01(VECTOR* arg0, VECTOR* arg1, s16 arg2, s32 arg3, s16 arg4, s16 arg5, s32 arg6, s32 arg7);

s32 sharedFunc_800D569C_0_s01(s_SubCharacter* airScreamer, q19_12 posY, q19_12 dist);

void sharedFunc_800D57C8_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D5E78_0_s01(s_SubCharacter* airScreamer, q19_12 angle);

s32 sharedFunc_800D6A60_0_s01(VECTOR3* offset, VECTOR3* vec1, s_SubCharacter* airScreamer, s32 arg3, VECTOR3* vec2);

void sharedFunc_800D6C7C_0_s01(VECTOR* arg0, s_SubCharacter* airScreamer, s32 arg2, VECTOR3* arg3);

/** Plays SFX. */
void sharedFunc_800D2364_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D5638_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800DF2D0_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800D4E84_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D529C_0_s01(s_SubCharacter* airScreamer, q19_12 radius, q19_12 headingAngle);

void sharedFunc_800D53AC_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800CD7F8_3_s03(s_SubCharacter* chara, q19_12 posX, q19_12 posZ, q19_12 range);

void sharedFunc_800CD920_3_s03(s_SubCharacter* chara, q19_12 posX, q19_12 posZ);

q19_12 sharedFunc_800CD940_3_s03(q19_12 pos0, q19_12 pos1);

s32 sharedFunc_800CD980_3_s03(s_SubCharacter* chara);

q19_12 sharedFunc_800CD6B0_3_s03(MATRIX* mat, s32 matCount, VECTOR3* center);

void sharedFunc_800D6EC4_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D7B14_0_s01(s_SubCharacter*, GsCOORDINATE2*);

void sharedFunc_800CE5D4_1_s03(VECTOR3* arg0, u16 arg1, u16 arg2, u32 arg3);

void sharedFunc_800CBA4C_1_s02(s32 idx, s32 arg1, s32 arg2);

void sharedFunc_800CBC98_1_s02(void);

void sharedFunc_800CBD58_1_s02(void);

void sharedFunc_800DE1F8_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DEC64_2_s00(s_SubCharacter* airScreamer);

void sharedFunc_800DEC84_2_s00(s_SubCharacter* airScreamer, q19_12 radius, q19_12 angle);

void sharedFunc_800DECA4_2_s00(s_SubCharacter* airScreamer, VECTOR3* vec, q19_12 dist);

void sharedFunc_800DF22C_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800DF24C_2_s00(s_SubCharacter* airScreamer);

bool sharedFunc_800D2FB4_0_s01(s_SubCharacter* airScreamer, VECTOR3* playerPos, s32 playerField10C);

void sharedFunc_800D72E8_0_s01(s_SubCharacter* airScreamer, q19_12 angle0, q19_12 rotSpeedY);

void sharedFunc_800D6EC4_0_s01(s_SubCharacter* airScreamer);

/** @brief Handles the jammed door event. */
void MapEvent_DoorJammed(void);

/** @brief Handles the locked door event. */
void MapEvent_DoorLocked(void);

void sharedFunc_800D15F0_3_s01(void);

/** @brief Handles the unlocked door event. */
void MapEvent_DoorUnlocked(void);

void sharedFunc_800CEEE0_3_s03(s_SubCharacter* nurse);

void sharedFunc_800CF0B4_3_s03(s_SubCharacter* nurse);

bool sharedFunc_800CF294_3_s03(s_SubCharacter* nurse, q19_12 dist);

/** @brief Gets the room index corresponding to the current 2D position.
 *
 * @param x X position in Q19.12.
 * @param z Z position in Q19.12.
 * @return Room index.
 */
u8 Map_RoomIdxGet(s32 x, s32 z);

void sharedFunc_800CBE54_4_s03(VECTOR3* arg0, s32 arg1);

bool sharedFunc_800CC004_4_s03(POLY_FT4** poly, s32 arg1);

bool sharedFunc_800CB1B0_4_s03(POLY_FT4** poly, s32 arg1);

void sharedFunc_800CB0A4_4_s03(VECTOR3* arg0, VECTOR3* arg1);

void sharedFunc_800D0110_7_s00(void);

static inline void ModelAnim_AnimInfoSet(s_ModelAnim* anim, s_AnimInfo* animInfo)
{
    anim->animInfo_C  = animInfo;
    anim->animInfo_10 = NULL;
}

// TODO: Could also call this a "transform"? "Pose" is a less common term for a position+rotation struct.
typedef struct
{
    VECTOR3  position_0; // Q19.12
    SVECTOR3 rotation_C; // Q19.12
} s_WorldObjectPose;
STATIC_ASSERT_SIZEOF(s_WorldObjectPose, 0x14);

typedef struct
{
    s_WorldObjectModel object_0;
    VECTOR3         position_1C; // Q19.12
    SVECTOR3        rotation_28; // Q19.12
} s_WorldObjectDesc;
STATIC_ASSERT_SIZEOF(s_WorldObjectDesc, 0x30);

typedef struct
{
    s_WorldObjectModel object_0;
    VECTOR3         position_1C; // Q19.12
} s_WorldObjectDescNoRot;
STATIC_ASSERT_SIZEOF(s_WorldObjectDescNoRot, 40);

#define WorldObjectPoseInit(eventPos, posX, posY, posZ, rotX, rotY, rotZ) \
    WorldObjectPoseSet(eventPos, Q12(posX), Q12(posY), Q12(posZ), Q12_ANGLE(rotX), Q12_ANGLE(rotY), Q12_ANGLE(rotZ))

#define WorldObjectPoseSet(eventPose, posX, posY, posZ, rotX, rotY, rotZ) \
{                                                                         \
    Math_Vector3Set(&(eventPose)->position_0, posX, posY, posZ);          \
    Math_SetSVectorFast(&(eventPose)->rotation_C, rotX, rotY, rotZ);      \
}

#define WorldObjectInit(eventPos, name, posX, posY, posZ, rotX, rotY, rotZ) \
    WorldObjectSet(eventPos, name, Q12(posX), Q12(posY), Q12(posZ), Q12_ANGLE(rotX), Q12_ANGLE(rotY), Q12_ANGLE(rotZ))

#define WorldObjectSet(eventPose, name, posX, posY, posZ, rotX, rotY, rotZ) \
{                                                                           \
    Math_Vector3Set(&(eventPose)->position_1C, posX, posY, posZ);           \
    Math_SetSVectorFast(&(eventPose)->rotation_28, rotX, rotY, rotZ);       \
    WorldObject_ModelNameSet(&(eventPose)->object_0, (name));               \
}

#define WorldObjectNoRotInit(eventPos, name, posX, posY, posZ) \
    WorldObjectNoRotSet(eventPos, name, Q12(posX), Q12(posY), Q12(posZ))

#define WorldObjectNoRotSet(eventPose, name, posX, posY, posZ)    \
{                                                                 \
    Math_Vector3Set(&(eventPose)->position_1C, posX, posY, posZ); \
    WorldObject_ModelNameSet(&(eventPose)->object_0, (name));     \
}

#define APPROACH(current, target, step) \
    ((current) > (target) ? MAX((current) - (step), (target)) : MIN((target), (current) + (step)))

#define APPROACH_ALT(current, target, step) \
    ((current) > (target) ? MAX((current) - (step), (target)) : CLAMP_HIGH((current) + (step), (target)))

#define APPROACH_ALT2(current, target, step) \
    ((current) > (target) ? CLAMP_LOW((current) - (step), (target)) : CLAMP_HIGH((target), (current) + (step)))

/** @brief Updates the move speed of a character.
 *
 * @param chara Character to update.
 * @param speed Move speed (Q*.12).
 */
#define Chara_MoveSpeedUpdate(chara, speed) \
    chara->moveSpeed_38 = APPROACH(chara->moveSpeed_38, Q12(0.0f), Q12_MULT_PRECISE(g_DeltaTime, speed))

// TODO: Is it possible to merge these macros?
#define Chara_MoveSpeedUpdate2(chara, speed, limit)                       \
{                                                                         \
    q19_12 moveSpeed;                                                     \
    q19_12 newSpeed;                                                      \
    q19_12 newMoveSpeed;                                                  \
                                                                          \
    moveSpeed = chara->moveSpeed_38;                                      \
    if (moveSpeed > limit)                                                \
    {                                                                     \
        newMoveSpeed = limit;                                             \
        limit        = Q12(0.0f);                                         \
        newSpeed     = moveSpeed - Q12_MULT_PRECISE(g_DeltaTime, speed); \
        if (newMoveSpeed < newSpeed)                                      \
        {                                                                 \
            newMoveSpeed = newSpeed;                                      \
        }                                                                 \
    }                                                                     \
    else                                                                  \
    {                                                                     \
        newMoveSpeed = limit;                                             \
        newSpeed     = moveSpeed + Q12_MULT_PRECISE(g_DeltaTime, speed); \
        if (newMoveSpeed >= newSpeed)                                     \
        {                                                                 \
            newMoveSpeed = newSpeed;                                      \
        }                                                                 \
    }                                                                     \
    chara->moveSpeed_38 = newMoveSpeed;                                   \
}

#define Chara_MoveSpeedUpdate3(chara, speed, limit) \
    chara->moveSpeed_38 = APPROACH(chara->moveSpeed_38, limit, Q12_MULT_PRECISE(g_DeltaTime, speed))

#define Chara_MoveSpeedUpdate4(chara, speed, limit) \
    chara->moveSpeed_38 = APPROACH_ALT(chara->moveSpeed_38, limit, Q12_MULT_PRECISE(g_DeltaTime, speed))

#endif
