#ifndef _MAPS_SHARED_H
#define _MAPS_SHARED_H

#include "game.h"
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

/*s_AnimInfo AIR_SCREAMER_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0, false), false, NO_VALUE, { Q12(10) }, NO_VALUE, NO_VALUE },
    { Anim_Update1, ANIM_STATUS(0, true), false, NO_VALUE, { Q12(10) }, NO_VALUE, NO_VALUE },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(10) }, NO_VALUE, 0 },
    { Anim_Update0, ANIM_STATUS(1, true), false, ANIM_STATUS(23, false), { Q12(20) }, 0, 11 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q12(15) }, NO_VALUE, 12 },
    { Anim_Update0, ANIM_STATUS(2, true), false, ANIM_STATUS(19, false), { Q12(15) }, 12, 25 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q12(30) }, NO_VALUE, 26 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(17, false), { Q12(25) }, 26, 55 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q12(15) }, NO_VALUE, 56 },
    { Anim_Update0, ANIM_STATUS(4, true), false, ANIM_STATUS(26, false), { Q12(15) }, 56, 80 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q12(10) }, NO_VALUE, 81 },
    { Anim_Update0, ANIM_STATUS(5, true), false, ANIM_STATUS(26, false), { Q12(10) }, 81, 99 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q12(30) }, NO_VALUE, 100 },
    { Anim_Update0, ANIM_STATUS(6, true), false, ANIM_STATUS(23, false), { Q12(20) }, 100, 114 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q12(30) }, NO_VALUE, 115 },
    { Anim_Update0, ANIM_STATUS(7, true), false, ANIM_STATUS(19, false), { Q12(20) }, 115, 129 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q12(30) }, NO_VALUE, 130 },
    { Anim_Update0, ANIM_STATUS(8, true), false, ANIM_STATUS(17, false), { Q12(25) }, 130, 153 },
    { Anim_Update2, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q12(30) }, NO_VALUE, 154 },
    { Anim_Update0, ANIM_STATUS(9, true), false, ANIM_STATUS(21, false), { Q12(24) }, 154, 171 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(10) }, NO_VALUE, 172 },
    { Anim_Update0, ANIM_STATUS(10, true), false, ANIM_STATUS(26, false), sharedFunc_800D77D0_0_s01, 172, 189 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(10) }, NO_VALUE, 190 },
    { Anim_Update0, ANIM_STATUS(11, true), false, ANIM_STATUS(26, false), sharedFunc_800D77D0_0_s01, 190, 230 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q12(10) }, NO_VALUE, 231 },
    { Anim_Update0, ANIM_STATUS(12, true), false, ANIM_STATUS(26, false), { Q12(10) }, 231, 242 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q12(5) }, NO_VALUE, 243 },
    { Anim_Update0, ANIM_STATUS(13, true), false, ANIM_STATUS(14, false), { Q12(10) }, 243, 272 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q12(1.5) }, NO_VALUE, 273 },
    { Anim_Update1, ANIM_STATUS(14, true), false, NO_VALUE, { Q12(10) }, 273, 302 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true), func_800E21C8, NO_VALUE, 303 },
    { Anim_Update0, ANIM_STATUS(15, true), false, ANIM_STATUS(19, false), func_800E21C8, 303, 314 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true), { Q12(30) }, NO_VALUE, 315 },
    { Anim_Update0, ANIM_STATUS(16, true), false, ANIM_STATUS(25, false), sharedFunc_800D77D0_0_s01, 315, 339 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true), func_800E21C8, NO_VALUE, 340 },
    { Anim_Update1, ANIM_STATUS(17, true), false, NO_VALUE, sharedFunc_800D77D0_0_s01, 340, 352 },
    { Anim_Update2, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true), { Q12(30) }, NO_VALUE, 353 },
    { Anim_Update0, ANIM_STATUS(18, true), false, ANIM_STATUS(17, false), { Q12(20) }, 353, 364 },
    { Anim_Update2, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true), func_800E21C8, NO_VALUE, 365 },
    { Anim_Update1, ANIM_STATUS(19, true), false, NO_VALUE, sharedFunc_800D77D0_0_s01, 365, 376 },
    { Anim_Update2, ANIM_STATUS(20, false), false, ANIM_STATUS(20, true), { Q12(10) }, NO_VALUE, 377 },
    { Anim_Update0, ANIM_STATUS(20, true), false, ANIM_STATUS(26, false), { Q12(10) }, 377, 383 },
    { Anim_Update2, ANIM_STATUS(21, false), false, ANIM_STATUS(21, true), { Q12(15) }, NO_VALUE, 384 },
    { Anim_Update1, ANIM_STATUS(21, true), false, NO_VALUE, sharedFunc_800D77D0_0_s01, 384, 407 },
    { Anim_Update2, ANIM_STATUS(22, false), false, ANIM_STATUS(22, true), { Q12(30) }, NO_VALUE, 408 },
    { Anim_Update0, ANIM_STATUS(22, true), false, ANIM_STATUS(19, false), { Q12(20) }, 408, 432 },
    { Anim_Update2, ANIM_STATUS(23, false), false, ANIM_STATUS(23, true), { Q12(10) }, NO_VALUE, 433 },
    { Anim_Update1, ANIM_STATUS(23, true), false, NO_VALUE, func_800E21C8, 433, 447 },
    { Anim_Update2, ANIM_STATUS(24, false), false, ANIM_STATUS(24, true), func_800E21C8, NO_VALUE, 448 },
    { Anim_Update0, ANIM_STATUS(24, true), false, ANIM_STATUS(17, false), func_800E21C8, 448, 482 },
    { Anim_Update2, ANIM_STATUS(25, false), false, ANIM_STATUS(25, true), { Q12(30) }, NO_VALUE, 483 },
    { Anim_Update1, ANIM_STATUS(25, true), false, NO_VALUE, sharedFunc_800D77D0_0_s01, 483, 523 },
    { Anim_Update2, ANIM_STATUS(26, false), false, ANIM_STATUS(26, true), { Q12(1.5) }, NO_VALUE, 96 },
    { Anim_Update1, ANIM_STATUS(26, true), false, NO_VALUE, sharedFunc_800D77D0_0_s01, 96, 99 },
    { Anim_Update2, ANIM_STATUS(27, false), false, ANIM_STATUS(27, true), { Q12(30) }, NO_VALUE, 365 },
    { Anim_Update1, ANIM_STATUS(27, true), false, NO_VALUE, sharedFunc_800D77D0_0_s01, 365, 376 }
};*/

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

/** @brief Cat character animation indices. */
typedef enum _CatAnim
{
    CatAnim_Still                 = 0,
    CatAnim_Jump                  = 1,
    CatAnim_Run                   = 2,
    CatAnim_TransitionStillToJump = 3,
    CatAnim_TransitionJumpToRun   = 4
} e_CatAnim;

/** @brief Cat character anim infos.
 * @unused Frames [1, 6].
 */
/*s_AnimInfo CAT_ANIM_INFOS[] = {
    { Anim_Update2, NO_VALUE,                                          false, ANIM_STATUS(CatAnim_Still,                 false), { Q12(0)     }, NO_VALUE, 0  },
    { NULL,         ANIM_STATUS(CatAnim_Still,                 false), false, ANIM_STATUS(CatAnim_Still,                 false), { Q12(0)     }, 0,        0  },
    { Anim_Update2, ANIM_STATUS(CatAnim_Jump,                  false), false, ANIM_STATUS(CatAnim_Jump,                  true),  { Q12(64)    }, NO_VALUE, 7  },
    { Anim_Update0, ANIM_STATUS(CatAnim_Jump,                  true),  false, ANIM_STATUS(CatAnim_TransitionJumpToRun,   false), { Q12(15.8f) }, 7,        22 },
    { Anim_Update2, ANIM_STATUS(CatAnim_Run,                   false), false, ANIM_STATUS(CatAnim_Run,                   true),  { Q12(64)    }, NO_VALUE, 23 },
    { Anim_Update1, ANIM_STATUS(CatAnim_Run,                   true),  false, NO_VALUE,                                          { Q12(35)    }, 23,       43 },
    { Anim_Update2, ANIM_STATUS(CatAnim_TransitionStillToJump, false), false, ANIM_STATUS(CatAnim_TransitionStillToJump, true),  { Q12(0)     }, NO_VALUE, 7  },
    { Anim_Update1, ANIM_STATUS(CatAnim_TransitionStillToJump, true),  false, NO_VALUE,                                          { Q12(0)     }, 7,        8  },
    { Anim_Update2, ANIM_STATUS(CatAnim_TransitionJumpToRun,   false), false, ANIM_STATUS(CatAnim_TransitionJumpToRun,   true),  { Q12(0)     }, NO_VALUE, 22 },
    { Anim_Update1, ANIM_STATUS(CatAnim_TransitionJumpToRun,   true),  false, NO_VALUE,                                          { Q12(0)     }, 22,       23 }
};*/

/** @brief Floatstinger character animation indices. */
typedef enum _FloatstingerAnim
{
    FloatstingerAnim_Still = 0,
    FloatstingerAnim_Unk1 = 1,
    FloatstingerAnim_Unk2 = 2,
    FloatstingerAnim_Unk3 = 3,
    FloatstingerAnim_Unk4 = 4,
    FloatstingerAnim_Unk5 = 5,
    FloatstingerAnim_Unk6 = 6,
    FloatstingerAnim_Unk7 = 7,
    FloatstingerAnim_Unk8 = 8,
    FloatstingerAnim_Unk9 = 9,
    FloatstingerAnim_Unk10 = 10,
    FloatstingerAnim_Unk11 = 11,
    FloatstingerAnim_Unk12 = 12
} e_FloatstingerAnim;

/*s_AnimInfo FLOATSTINGER_ANIM_INFOS[] = {
    { Anim_Update2, NO_VALUE, false, ANIM_STATUS(FloatstingerAnim_Still, false), { Q12(0) }, NO_VALUE, 0 },
    { NULL, ANIM_STATUS(FloatstingerAnim_Still, false), false, ANIM_STATUS(FloatstingerAnim_Still, false), { Q12(0) }, 0, 0 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_Unk1, false), false, ANIM_STATUS(FloatstingerAnim_Unk1, true), { Q12(4) }, NO_VALUE, 1 },
    { Anim_Update0, ANIM_STATUS(FloatstingerAnim_Unk1, true), false, ANIM_STATUS(FloatstingerAnim_Unk9, false), { Q12(32) }, 1, 31 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_Unk2, false), false, ANIM_STATUS(FloatstingerAnim_Unk2, true), { Q12(5) }, NO_VALUE, 32 },
    { Anim_Update0, ANIM_STATUS(FloatstingerAnim_Unk2, true), false, ANIM_STATUS(FloatstingerAnim_Unk9, false), { Q12(20) }, 32, 57 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_Unk3, false), false, ANIM_STATUS(FloatstingerAnim_Unk3, true), { Q12(10) }, NO_VALUE, 58 },
    { Anim_Update0, ANIM_STATUS(FloatstingerAnim_Unk3, true), false, ANIM_STATUS(FloatstingerAnim_Unk11, false), { Q12(20) }, 58, 78 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_Unk4, false), false, ANIM_STATUS(FloatstingerAnim_Unk4, true), { Q12(20) }, NO_VALUE, 116 },
    { Anim_Update0, ANIM_STATUS(FloatstingerAnim_Unk4, true), false, ANIM_STATUS(FloatstingerAnim_Unk7, false), { Q12(0) }, 116, 136 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_Unk5, false), false, ANIM_STATUS(FloatstingerAnim_Unk5, true), { Q12(2) }, NO_VALUE, 85 },
    { Anim_Update0, ANIM_STATUS(FloatstingerAnim_Unk5, true), false, ANIM_STATUS(FloatstingerAnim_Unk3, false), { Q12(4) }, 85, 115 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_Unk6, false), false, ANIM_STATUS(FloatstingerAnim_Unk6, true), { Q12(20) }, NO_VALUE, 116 },
    { Anim_Update1, ANIM_STATUS(FloatstingerAnim_Unk6, true), false, ANIM_STATUS(FloatstingerAnim_Unk11, false), { Q12(0) }, 116, 136 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_Unk7, false), false, ANIM_STATUS(FloatstingerAnim_Unk7, true), { Q12(20) }, NO_VALUE, 137 },
    { Anim_Update1, ANIM_STATUS(FloatstingerAnim_Unk7, true), false, NO_VALUE, { Q12(0) }, 137, 158 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_Unk8, false), false, ANIM_STATUS(FloatstingerAnim_Unk8, true), { Q12(20) }, NO_VALUE, 159 },
    { Anim_Update1, ANIM_STATUS(FloatstingerAnim_Unk8, true), false, NO_VALUE, { Q12(20) }, 159, 190 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_Unk9, false), false, ANIM_STATUS(FloatstingerAnim_Unk9, true), { Q12(5) }, NO_VALUE, 191 },
    { Anim_Update1, ANIM_STATUS(FloatstingerAnim_Unk9, true), false, NO_VALUE, { Q12(0) }, 191, 222 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_Unk10, false), false, ANIM_STATUS(FloatstingerAnim_Unk10, true), { Q12(20) }, NO_VALUE, 223 },
    { Anim_Update1, ANIM_STATUS(FloatstingerAnim_Unk10, true), false, NO_VALUE, { Q12(20) }, 223, 254 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_Unk11, false), false, ANIM_STATUS(FloatstingerAnim_Unk11, true), { Q12(20) }, NO_VALUE, 78 },
    { Anim_Update1, ANIM_STATUS(FloatstingerAnim_Unk11, true), false, NO_VALUE, { Q12(0) }, 78, 79 },
    { Anim_Update2, ANIM_STATUS(FloatstingerAnim_Unk12, false), false, ANIM_STATUS(FloatstingerAnim_Unk12, true), { Q12(4) }, NO_VALUE, 1 },
    { Anim_Update0, ANIM_STATUS(FloatstingerAnim_Unk12, true), false, ANIM_STATUS(FloatstingerAnim_Unk9, false), { Q12(32) }, 1, 31 }
};*/

/*s_AnimInfo GHOST_DOCTOR_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(0, true), false, NO_VALUE, { Q12(30) }, NO_VALUE, 1 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(5) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(1, true), false, NO_VALUE, { Q12(15) }, 0, 15 }
};*/

typedef enum _GroanerAnim
{
    GroanerAnim_Still = 0,

    GroanerAnim_Unk17 = 17,
} e_GroanerAnim;

/*s_AnimInfo GROANER_ANIM_INFOS[] = {
    { Anim_Update2, NO_VALUE, false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { NULL, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, 0, 0 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(2) }, NO_VALUE, 0 },
    { Anim_Update0, ANIM_STATUS(1, true), false, ANIM_STATUS(18, false), { Q12(3) }, 0, 15 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q12(16) }, NO_VALUE, 19 },
    { Anim_Update0, ANIM_STATUS(2, true), false, ANIM_STATUS(9, false), { Q12(24.8f) }, 19, 36 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q12(16) }, NO_VALUE, 39 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(4, false), { Q12(0) }, 39, 77 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q12(1) }, NO_VALUE, 78 },
    { Anim_Update1, ANIM_STATUS(4, true), false, NO_VALUE, { Q12(4) }, 78, 93 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q12(2) }, NO_VALUE, 94 },
    { Anim_Update0, ANIM_STATUS(5, true), false, ANIM_STATUS(19, false), { Q12(3.5f) }, 94, 110 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q12(16) }, NO_VALUE, 114 },
    { Anim_Update0, ANIM_STATUS(6, true), false, ANIM_STATUS(9, false), { Q12(24.2f) }, 114, 130 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q12(16) }, NO_VALUE, 134 },
    { Anim_Update0, ANIM_STATUS(7, true), false, ANIM_STATUS(8, false), { Q12(0) }, 134, 164 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q12(1) }, NO_VALUE, 165 },
    { Anim_Update1, ANIM_STATUS(8, true), false, NO_VALUE, { Q12(6) }, 165, 190 },
    { Anim_Update2, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q12(2) }, NO_VALUE, 191 },
    { Anim_Update1, ANIM_STATUS(9, true), false, NO_VALUE, { Q12(7) }, 191, 206 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(20) }, NO_VALUE, 214 },
    { Anim_Update0, ANIM_STATUS(10, true), false, ANIM_STATUS(16, false), { Q12(0) }, 214, 243 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(2) }, NO_VALUE, 244 },
    { Anim_Update0, ANIM_STATUS(11, true), false, ANIM_STATUS(20, false), { Q12(3.5f) }, 244, 264 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q12(16) }, NO_VALUE, 268 },
    { Anim_Update0, ANIM_STATUS(12, true), false, ANIM_STATUS(9, false), { Q12(24.2f) }, 268, 284 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q12(32) }, NO_VALUE, 288 },
    { Anim_Update0, ANIM_STATUS(13, true), false, ANIM_STATUS(14, false), { Q12(0) }, 288, 318 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q12(1) }, NO_VALUE, 319 },
    { Anim_Update1, ANIM_STATUS(14, true), false, NO_VALUE, { Q12(6) }, 319, 345 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true), { Q12(32) }, NO_VALUE, 346 },
    { Anim_Update0, ANIM_STATUS(15, true), false, ANIM_STATUS(10, false), { Q12(54) }, 346, 362 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true), { Q12(16) }, NO_VALUE, 363 },
    { Anim_Update1, ANIM_STATUS(16, true), false, NO_VALUE, { Q12(0) }, 363, 370 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true), { Q12(2) }, NO_VALUE, 371 },
    { Anim_Update1, ANIM_STATUS(17, true), false, NO_VALUE, { Q12(11.5f) }, 371, 396 },
    { Anim_Update2, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true), { Q12(16) }, NO_VALUE, 15 },
    { Anim_Update1, ANIM_STATUS(18, true), false, NO_VALUE, { Q12(0) }, 15, 16 },
    { Anim_Update2, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true), { Q12(16) }, NO_VALUE, 110 },
    { Anim_Update1, ANIM_STATUS(19, true), false, NO_VALUE, { Q12(0) }, 110, 111 },
    { Anim_Update2, ANIM_STATUS(20, false), false, ANIM_STATUS(20, true), { Q12(16) }, NO_VALUE, 264 },
    { Anim_Update1, ANIM_STATUS(20, true), false, NO_VALUE, { Q12(0) }, 264, 265 },
    { Anim_Update2, ANIM_STATUS(21, false), false, ANIM_STATUS(21, true), { Q12(16) }, NO_VALUE, 0 },
    { Anim_Update0, ANIM_STATUS(21, true), false, ANIM_STATUS(4, false), { Q12(12) }, 0, 15 },
    { Anim_Update2, ANIM_STATUS(22, false), false, ANIM_STATUS(22, true), { Q12(16) }, NO_VALUE, 94 },
    { Anim_Update0, ANIM_STATUS(22, true), false, ANIM_STATUS(8, false), { Q12(12) }, 94, 110 },
    { Anim_Update2, ANIM_STATUS(23, false), false, ANIM_STATUS(23, true), { Q12(16) }, NO_VALUE, 244 },
    { Anim_Update0, ANIM_STATUS(23, true), false, ANIM_STATUS(14, false), { Q12(12) }, 244, 264 }
};*/

typedef enum _HangedScratcher
{
    HangedScratcherAnim_Still = 0,
    HangedScratcherAnim_Unk1 = 1,
    HangedScratcherAnim_Unk2 = 2,
    HangedScratcherAnim_Unk3 = 3,

    HangedScratcherAnim_Unk14 = 14,
    HangedScratcherAnim_Unk15 = 15,
} e_HangedScratcher;

/*s_AnimInfo HANGED_SCRATCHER_ANIM_INFOS[] = {
    { Anim_Update2, NO_VALUE, false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { NULL, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, 0, 0 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(0) }, NO_VALUE, 0 },
    { Anim_Update0, ANIM_STATUS(1, true), false, ANIM_STATUS(24, false), { Q12(0) }, 0, 50 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q12(0) }, NO_VALUE, 51 },
    { Anim_Update0, ANIM_STATUS(2, true), false, ANIM_STATUS(25, false), { Q12(0) }, 51, 86 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q12(0) }, NO_VALUE, 87 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(26, false), { Q12(0) }, 87, 97 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q12(18) }, NO_VALUE, 98 },
    { Anim_Update0, ANIM_STATUS(4, true), false, ANIM_STATUS(14, false), { Q12(19.5f) }, 98, 115 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q12(12) }, NO_VALUE, 116 },
    { Anim_Update0, ANIM_STATUS(5, true), false, ANIM_STATUS(15, false), { Q12(23) }, 116, 135 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q12(4) }, NO_VALUE, 136 },
    { Anim_Update0, ANIM_STATUS(6, true), false, ANIM_STATUS(19, false), { Q12(2) }, 136, 147 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q12(4) }, NO_VALUE, 148 },
    { Anim_Update0, ANIM_STATUS(7, true), false, ANIM_STATUS(20, false), { Q12(1) }, 148, 153 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q12(4) }, NO_VALUE, 154 },
    { Anim_Update0, ANIM_STATUS(8, true), false, ANIM_STATUS(14, false), { Q12(14) }, 154, 165 },
    { Anim_Update2, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q12(4) }, NO_VALUE, 168 },
    { Anim_Update0, ANIM_STATUS(9, true), false, ANIM_STATUS(15, false), { Q12(0) }, 168, 175 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(16) }, NO_VALUE, 176 },
    { Anim_Update0, ANIM_STATUS(10, true), false, ANIM_STATUS(12, false), { Q12(0) }, 176, 191 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(2) }, NO_VALUE, 192 },
    { Anim_Update0, ANIM_STATUS(11, true), false, ANIM_STATUS(13, false), { Q12(0) }, 192, 201 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q12(16) }, NO_VALUE, 202 },
    { Anim_Update1, ANIM_STATUS(12, true), false, NO_VALUE, { Q12(3) }, 202, 215 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q12(2) }, NO_VALUE, 216 },
    { Anim_Update1, ANIM_STATUS(13, true), false, NO_VALUE, { Q12(3) }, 216, 221 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q12(2) }, NO_VALUE, 222 },
    { Anim_Update1, ANIM_STATUS(14, true), false, NO_VALUE, { Q12(0) }, 222, 231 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true), { Q12(2) }, NO_VALUE, 232 },
    { Anim_Update1, ANIM_STATUS(15, true), false, NO_VALUE, { Q12(0) }, 232, 243 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true), { Q12(16) }, NO_VALUE, 244 },
    { Anim_Update0, ANIM_STATUS(16, true), false, ANIM_STATUS(15, false), { Q12(0) }, 244, 266 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true), { Q12(8) }, NO_VALUE, 267 },
    { Anim_Update1, ANIM_STATUS(17, true), false, NO_VALUE, { Q12(0) }, 267, 276 },
    { Anim_Update2, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true), { Q12(4) }, NO_VALUE, 277 },
    { Anim_Update1, ANIM_STATUS(18, true), false, NO_VALUE, { Q12(0) }, 277, 292 },
    { Anim_Update2, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true), { Q12(16) }, NO_VALUE, 147 },
    { Anim_Update1, ANIM_STATUS(19, true), false, NO_VALUE, { Q12(0) }, 147, 148 },
    { Anim_Update2, ANIM_STATUS(20, false), false, ANIM_STATUS(20, true), { Q12(16) }, NO_VALUE, 153 },
    { Anim_Update1, ANIM_STATUS(20, true), false, NO_VALUE, { Q12(0) }, 153, 154 },
    { Anim_Update2, ANIM_STATUS(21, false), false, ANIM_STATUS(21, true), { Q12(16) }, NO_VALUE, 136 },
    { Anim_Update0, ANIM_STATUS(21, true), false, ANIM_STATUS(12, false), { Q12(16) }, 136, 147 },
    { Anim_Update2, ANIM_STATUS(22, false), false, ANIM_STATUS(22, true), { Q12(16) }, NO_VALUE, 148 },
    { Anim_Update0, ANIM_STATUS(22, true), false, ANIM_STATUS(13, false), { Q12(8) }, 148, 153 },
    { Anim_Update2, ANIM_STATUS(23, false), false, ANIM_STATUS(23, true), { Q12(4) }, NO_VALUE, 168 },
    { Anim_Update0, ANIM_STATUS(23, true), false, ANIM_STATUS(11, false), { Q12(0) }, 168, 174 },
    { Anim_Update2, ANIM_STATUS(24, false), false, ANIM_STATUS(24, true), { Q12(0) }, NO_VALUE, 50 },
    { Anim_Update1, ANIM_STATUS(24, true), false, NO_VALUE, { Q12(0) }, 50, 51 },
    { Anim_Update2, ANIM_STATUS(25, false), false, ANIM_STATUS(25, true), { Q12(0) }, NO_VALUE, 86 },
    { Anim_Update1, ANIM_STATUS(25, true), false, NO_VALUE, { Q12(0) }, 86, 87 },
    { Anim_Update2, ANIM_STATUS(26, false), false, ANIM_STATUS(26, true), { Q12(0) }, NO_VALUE, 97 },
    { Anim_Update1, ANIM_STATUS(26, true), false, NO_VALUE, { Q12(0) }, 97, 98 }
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

typedef enum _LockerDeadBodyAnim
{
    LockerDeadBodyAnim_Still = 0,
    LockerDeadBodyAnim_1     = 1,
    LockerDeadBodyAnim_2     = 2,
    LockerDeadBodyAnim_3     = 3
} e_LockerDeadBodyAnim;

/*s_AnimInfo LOCKERR_DEAD_BODY_ANIM_INFOS[] = {

};*/

/*s_AnimInfo MONSTER_CYBIL_ANIM_INFOS[] = {
    { Anim_Update2, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0)  }, NO_VALUE, 0  },
    { Anim_Update1, ANIM_STATUS(0, true),  false, NO_VALUE,              { Q12(30) }, NO_VALUE, 1  },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true),  { Q12(1)  }, NO_VALUE, 0  },
    { Anim_Update1, ANIM_STATUS(1, true),  false, NO_VALUE,              { func_800D8898 },  0,        23 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true),  { Q12(5)  }, NO_VALUE, 24 }
};*/

typedef enum _RomperAnim
{
    RomperAnim_Still = 0,

    RomperAnim_Unk15 = 15,
} e_RomperAnim;

/*s_AnimInfo ROMPER_ANIM_INFOS[] = {
    { Anim_Update2, NO_VALUE, false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { NULL, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, 0, 0 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(20) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(1, true), false, NO_VALUE, { Q12(10) }, 0, 1 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q12(18) }, NO_VALUE, 2 },
    { Anim_Update0, ANIM_STATUS(2, true), false, ANIM_STATUS(4, false), { Q12(12) }, 2, 7 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q12(15) }, NO_VALUE, 8 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(5, false), { Q12(15) }, 8, 14 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q12(20) }, NO_VALUE, 15 },
    { Anim_Update0, ANIM_STATUS(4, true), false, ANIM_STATUS(13, false), { Q12(12) }, 15, 19 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q12(15) }, NO_VALUE, 20 },
    { Anim_Update1, ANIM_STATUS(5, true), false, NO_VALUE, { Q12(15) }, 20, 33 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q12(20) }, NO_VALUE, 34 },
    { Anim_Update0, ANIM_STATUS(6, true), false, ANIM_STATUS(16, false), { Q12(5) }, 34, 38 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q12(10) }, NO_VALUE, 39 },
    { Anim_Update0, ANIM_STATUS(7, true), false, ANIM_STATUS(13, false), { Q12(8) }, 39, 49 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q12(10) }, NO_VALUE, 50 },
    { Anim_Update0, ANIM_STATUS(8, true), false, ANIM_STATUS(13, false), { Q12(8) }, 50, 60 },
    { Anim_Update2, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q12(10) }, NO_VALUE, 61 },
    { Anim_Update0, ANIM_STATUS(9, true), false, ANIM_STATUS(21, false), { Q12(10) }, 61, 87 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(20) }, NO_VALUE, 88 },
    { Anim_Update1, ANIM_STATUS(10, true), false, NO_VALUE, { Q12(5) }, 88, 92 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(4) }, NO_VALUE, 93 },
    { Anim_Update0, ANIM_STATUS(11, true), false, ANIM_STATUS(10, false), { Q12(6.5f) }, 93, 99 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q12(10) }, NO_VALUE, 100 },
    { Anim_Update1, ANIM_STATUS(12, true), false, NO_VALUE, { Q12(6) }, 100, 108 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q12(20) }, NO_VALUE, 109 },
    { Anim_Update1, ANIM_STATUS(13, true), false, NO_VALUE, { Q12(0) }, 109, 130 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q12(6) }, NO_VALUE, 131 },
    { Anim_Update1, ANIM_STATUS(14, true), false, NO_VALUE, { Q12(0) }, 131, 146 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true), { Q12(16) }, NO_VALUE, 147 },
    { Anim_Update1, ANIM_STATUS(15, true), false, NO_VALUE, { Q12(4) }, 147, 162 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true), { Q12(16) }, NO_VALUE, 38 },
    { Anim_Update1, ANIM_STATUS(16, true), false, NO_VALUE, { Q12(0) }, 38, 39 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true), { Q12(0) }, NO_VALUE, 120 },
    { Anim_Update0, ANIM_STATUS(17, true), false, ANIM_STATUS(7, false), { Q12(0) }, 120, 127 },
    { Anim_Update2, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true), { Q12(0) }, NO_VALUE, 110 },
    { Anim_Update0, ANIM_STATUS(18, true), false, ANIM_STATUS(8, false), { Q12(0) }, 110, 116 },
    { Anim_Update2, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true), { Q12(12) }, NO_VALUE, 109 },
    { Anim_Update0, ANIM_STATUS(19, true), false, ANIM_STATUS(13, false), { Q12(0) }, 109, 130 }
};*/

typedef enum _SplitheadAnim
{
    SplitheadAnim_Still = 0,

    SplitheadAnim_Unk10 = 10,
} e_SplitheadAnim;

/*s_AnimInfo SPLITHEAD_ANIM_INFOS[] = {
    { Anim_Update2, NO_VALUE, false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { NULL, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, 0, 0 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(2) }, NO_VALUE, 0 },
    { Anim_Update1, ANIM_STATUS(1, true), false, NO_VALUE, { Q12(3.5f) }, 0, 13 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q12(8) }, NO_VALUE, 14 },
    { Anim_Update0, ANIM_STATUS(2, true), false, ANIM_STATUS(10, false), { Q12(0) }, 14, 40 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q12(18) }, NO_VALUE, 41 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(10, false), { Q12(12) }, 41, 50 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q12(12) }, NO_VALUE, 51 },
    { Anim_Update0, ANIM_STATUS(4, true), false, ANIM_STATUS(10, false), { Q12(12) }, 51, 60 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q12(12) }, NO_VALUE, 61 },
    { Anim_Update0, ANIM_STATUS(5, true), false, ANIM_STATUS(6, false), { Q12(12) }, 61, 63 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q12(12) }, NO_VALUE, 78 },
    { Anim_Update0, ANIM_STATUS(6, true), false, ANIM_STATUS(10, false), { Q12(12) }, 78, 80 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q12(4) }, NO_VALUE, 94 },
    { Anim_Update0, ANIM_STATUS(7, true), false, ANIM_STATUS(12, false), { Q12(2) }, 94, 114 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q12(0.5f) }, NO_VALUE, 115 },
    { Anim_Update0, ANIM_STATUS(8, true), false, ANIM_STATUS(13, false), { Q12(1.5f) }, 115, 131 },
    { Anim_Update2, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q12(4) }, NO_VALUE, 132 },
    { Anim_Update0, ANIM_STATUS(9, true), false, ANIM_STATUS(1, false), { Q12(0) }, 132, 161 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(8) }, NO_VALUE, 162 },
    { Anim_Update1, ANIM_STATUS(10, true), false, NO_VALUE, { Q12(6) }, 162, 171 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(4) }, NO_VALUE, 172 },
    { Anim_Update1, ANIM_STATUS(11, true), false, NO_VALUE, { Q12(0) }, 172, 201 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q12(8) }, NO_VALUE, 114 },
    { Anim_Update1, ANIM_STATUS(12, true), false, NO_VALUE, { Q12(0) }, 114, 115 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q12(8) }, NO_VALUE, 131 },
    { Anim_Update1, ANIM_STATUS(13, true), false, NO_VALUE, { Q12(0) }, 131, 132 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q12(2) }, NO_VALUE, 34 },
    { Anim_Update1, ANIM_STATUS(14, true), false, NO_VALUE, { Q12(2) }, 34, 36 }
};*/

typedef enum _StalkerAnim
{
    StalkerAnim_Still = 0,

    StalkerAnim_Unk14 = 14,
    StalkerAnim_Unk27 = 27,
    StalkerAnim_Unk28 = 28,

    StalkerAnim_Unk30 = 30,
} e_StalkerAnim;

/*s_AnimInfo STALKER_ANIM_INFOS[] = {
    { Anim_Update2, NO_VALUE, false, ANIM_STATUS(0, false), { Q12(0) }, NO_VALUE, 0 },
    { NULL, ANIM_STATUS(0, false), false, ANIM_STATUS(0, false), { Q12(0) }, 0, 0 },
    { Anim_Update2, ANIM_STATUS(1, false), false, ANIM_STATUS(1, true), { Q12(5) }, NO_VALUE, 0 },
    { Anim_Update0, ANIM_STATUS(1, true), false, ANIM_STATUS(26, false), { Q12(12) }, 0, 3 },
    { Anim_Update2, ANIM_STATUS(2, false), false, ANIM_STATUS(2, true), { Q12(5) }, NO_VALUE, 4 },
    { Anim_Update0, ANIM_STATUS(2, true), false, ANIM_STATUS(26, false), { Q12(6) }, 4, 8 },
    { Anim_Update2, ANIM_STATUS(3, false), false, ANIM_STATUS(3, true), { Q12(5) }, NO_VALUE, 9 },
    { Anim_Update0, ANIM_STATUS(3, true), false, ANIM_STATUS(26, false), { Q12(6) }, 9, 19 },
    { Anim_Update2, ANIM_STATUS(4, false), false, ANIM_STATUS(4, true), { Q12(4) }, NO_VALUE, 20 },
    { Anim_Update0, ANIM_STATUS(4, true), false, ANIM_STATUS(17, false), { Q12(6) }, 20, 24 },
    { Anim_Update2, ANIM_STATUS(5, false), false, ANIM_STATUS(5, true), { Q12(4) }, NO_VALUE, 25 },
    { Anim_Update0, ANIM_STATUS(5, true), false, ANIM_STATUS(17, false), { Q12(6) }, 25, 33 },
    { Anim_Update2, ANIM_STATUS(6, false), false, ANIM_STATUS(6, true), { Q12(0) }, NO_VALUE, 34 },
    { NULL, ANIM_STATUS(6, true), false, ANIM_STATUS(0, false), { Q12(0) }, 34, 49 },
    { Anim_Update2, ANIM_STATUS(7, false), false, ANIM_STATUS(7, true), { Q12(16) }, NO_VALUE, 50 },
    { Anim_Update0, ANIM_STATUS(7, true), false, ANIM_STATUS(30, false), { Q12(0) }, 50, 69 },
    { Anim_Update2, ANIM_STATUS(8, false), false, ANIM_STATUS(8, true), { Q12(32) }, NO_VALUE, 70 },
    { Anim_Update1, ANIM_STATUS(8, true), false, NO_VALUE, { Q12(13) }, 70, 82 },
    { Anim_Update2, ANIM_STATUS(9, false), false, ANIM_STATUS(9, true), { Q12(32) }, NO_VALUE, 83 },
    { Anim_Update1, ANIM_STATUS(9, true), false, NO_VALUE, { Q12(13) }, 83, 95 },
    { Anim_Update2, ANIM_STATUS(10, false), false, ANIM_STATUS(10, true), { Q12(16) }, NO_VALUE, 96 },
    { Anim_Update0, ANIM_STATUS(10, true), false, ANIM_STATUS(18, false), { Q12(8) }, 96, 106 },
    { Anim_Update2, ANIM_STATUS(11, false), false, ANIM_STATUS(11, true), { Q12(4) }, NO_VALUE, 107 },
    { Anim_Update0, ANIM_STATUS(11, true), false, ANIM_STATUS(27, false), { Q12(8) }, 107, 128 },
    { Anim_Update2, ANIM_STATUS(12, false), false, ANIM_STATUS(12, true), { Q12(4) }, NO_VALUE, 129 },
    { Anim_Update0, ANIM_STATUS(12, true), false, ANIM_STATUS(27, false), { Q12(8) }, 129, 157 },
    { Anim_Update2, ANIM_STATUS(13, false), false, ANIM_STATUS(13, true), { Q12(4) }, NO_VALUE, 158 },
    { Anim_Update0, ANIM_STATUS(13, true), false, ANIM_STATUS(27, false), { Q12(10) }, 158, 175 },
    { Anim_Update2, ANIM_STATUS(14, false), false, ANIM_STATUS(14, true), { Q12(10) }, NO_VALUE, 176 },
    { Anim_Update0, ANIM_STATUS(14, true), false, ANIM_STATUS(46, false), { Q12(10) }, 176, 263 },
    { Anim_Update2, ANIM_STATUS(15, false), false, ANIM_STATUS(15, true), { Q12(5) }, NO_VALUE, 264 },
    { Anim_Update0, ANIM_STATUS(15, true), false, ANIM_STATUS(47, false), { Q12(10) }, 264, 294 },
    { Anim_Update2, ANIM_STATUS(16, false), false, ANIM_STATUS(16, true), { Q12(0) }, NO_VALUE, 295 },
    { NULL, ANIM_STATUS(16, true), false, ANIM_STATUS(0, false), { Q12(0) }, 295, 322 },
    { Anim_Update2, ANIM_STATUS(17, false), false, ANIM_STATUS(17, true), { Q12(16) }, NO_VALUE, 323 },
    { Anim_Update1, ANIM_STATUS(17, true), false, NO_VALUE, { Q12(4) }, 323, 332 },
    { Anim_Update2, ANIM_STATUS(18, false), false, ANIM_STATUS(18, true), { Q12(16) }, NO_VALUE, 333 },
    { Anim_Update1, ANIM_STATUS(18, true), false, NO_VALUE, { Q12(4) }, 333, 338 },
    { Anim_Update2, ANIM_STATUS(19, false), false, ANIM_STATUS(19, true), { Q12(8) }, NO_VALUE, 339 },
    { Anim_Update0, ANIM_STATUS(19, true), false, ANIM_STATUS(32, false), { Q12(1.5) }, 339, 344 },
    { Anim_Update2, ANIM_STATUS(20, false), false, ANIM_STATUS(20, true), { Q12(8) }, NO_VALUE, 346 },
    { Anim_Update0, ANIM_STATUS(20, true), false, ANIM_STATUS(33, false), { Q12(1.5) }, 346, 351 },
    { Anim_Update2, ANIM_STATUS(21, false), false, ANIM_STATUS(21, true), { Q12(8) }, NO_VALUE, 353 },
    { Anim_Update0, ANIM_STATUS(21, true), false, ANIM_STATUS(31, false), { Q12(1.5) }, 353, 360 },
    { Anim_Update2, ANIM_STATUS(22, false), false, ANIM_STATUS(22, true), { Q12(16) }, NO_VALUE, 362 },
    { Anim_Update0, ANIM_STATUS(22, true), false, ANIM_STATUS(27, false), { Q12(12) }, 362, 377 },
    { Anim_Update2, ANIM_STATUS(23, false), false, ANIM_STATUS(23, true), { Q12(16) }, NO_VALUE, 378 },
    { Anim_Update0, ANIM_STATUS(23, true), false, ANIM_STATUS(27, false), { Q12(12) }, 378, 393 },
    { Anim_Update2, ANIM_STATUS(24, false), false, ANIM_STATUS(24, true), { Q12(16) }, NO_VALUE, 395 },
    { Anim_Update0, ANIM_STATUS(24, true), false, ANIM_STATUS(26, false), { Q12(15) }, 395, 406 },
    { Anim_Update2, ANIM_STATUS(25, false), false, ANIM_STATUS(25, true), { Q12(4) }, NO_VALUE, 408 },
    { Anim_Update0, ANIM_STATUS(25, true), false, ANIM_STATUS(17, false), { Q12(10) }, 408, 417 },
    { Anim_Update2, ANIM_STATUS(26, false), false, ANIM_STATUS(26, true), { Q12(16) }, NO_VALUE, 418 },
    { Anim_Update1, ANIM_STATUS(26, true), false, NO_VALUE, { Q12(8) }, 418, 426 },
    { Anim_Update2, ANIM_STATUS(27, false), false, ANIM_STATUS(27, true), { Q12(16) }, NO_VALUE, 427 },
    { Anim_Update1, ANIM_STATUS(27, true), false, NO_VALUE, { Q12(4) }, 427, 442 },
    { Anim_Update2, ANIM_STATUS(28, false), false, ANIM_STATUS(28, true), { Q12(20) }, NO_VALUE, 443 },
    { Anim_Update1, ANIM_STATUS(28, true), false, NO_VALUE, { Q12(20) }, 443, 460 },
    { Anim_Update2, ANIM_STATUS(29, false), false, ANIM_STATUS(29, true), { Q12(0) }, NO_VALUE, 461 },
    { Anim_Update0, ANIM_STATUS(29, true), false, ANIM_STATUS(0, false), { Q12(0) }, 461, 476 },
    { Anim_Update2, ANIM_STATUS(30, false), false, ANIM_STATUS(30, true), { Q12(4) }, NO_VALUE, 477 },
    { Anim_Update1, ANIM_STATUS(30, true), false, NO_VALUE, { Q12(0) }, 477, 506 },
    { Anim_Update2, ANIM_STATUS(31, false), false, ANIM_STATUS(31, true), { Q12(16) }, NO_VALUE, 360 },
    { Anim_Update1, ANIM_STATUS(31, true), false, NO_VALUE, { Q12(0) }, 360, 361 },
    { Anim_Update2, ANIM_STATUS(32, false), false, ANIM_STATUS(32, true), { Q12(16) }, NO_VALUE, 344 },
    { Anim_Update1, ANIM_STATUS(32, true), false, NO_VALUE, { Q12(0) }, 344, 345 },
    { Anim_Update2, ANIM_STATUS(33, false), false, ANIM_STATUS(33, true), { Q12(16) }, NO_VALUE, 351 },
    { Anim_Update1, ANIM_STATUS(33, true), false, NO_VALUE, { Q12(0) }, 351, 352 },
    { Anim_Update2, ANIM_STATUS(34, false), false, ANIM_STATUS(34, true), { Q12(48) }, NO_VALUE, 461 },
    { Anim_Update0, ANIM_STATUS(34, true), false, ANIM_STATUS(9, false), { Q12(48) }, 461, 476 },
    { Anim_Update2, ANIM_STATUS(35, false), false, ANIM_STATUS(35, true), { Q12(48) }, NO_VALUE, 461 },
    { Anim_Update0, ANIM_STATUS(35, true), false, ANIM_STATUS(8, false), { Q12(48) }, 461, 476 },
    { Anim_Update2, ANIM_STATUS(36, false), false, ANIM_STATUS(36, true), { Q12(32) }, NO_VALUE, 102 },
    { Anim_Update0, ANIM_STATUS(36, true), false, ANIM_STATUS(18, false), { Q12(6) }, 102, 106 },
    { Anim_Update2, ANIM_STATUS(37, false), false, ANIM_STATUS(37, true), { Q12(0) }, NO_VALUE, 477 },
    { Anim_Update0, ANIM_STATUS(37, true), false, ANIM_STATUS(7, false), { Q12(0) }, 477, 506 },
    { Anim_Update2, ANIM_STATUS(38, false), false, ANIM_STATUS(38, true), { Q12(12) }, NO_VALUE, 353 },
    { Anim_Update0, ANIM_STATUS(38, true), false, ANIM_STATUS(26, false), { Q12(12) }, 353, 361 },
    { Anim_Update2, ANIM_STATUS(39, false), false, ANIM_STATUS(39, true), { Q12(12) }, NO_VALUE, 339 },
    { Anim_Update0, ANIM_STATUS(39, true), false, ANIM_STATUS(17, false), { Q12(12) }, 339, 345 },
    { Anim_Update2, ANIM_STATUS(40, false), false, ANIM_STATUS(40, true), { Q12(12) }, NO_VALUE, 346 },
    { Anim_Update0, ANIM_STATUS(40, true), false, ANIM_STATUS(18, false), { Q12(12) }, 346, 352 },
    { Anim_Update2, ANIM_STATUS(41, false), false, ANIM_STATUS(41, true), { Q12(16) }, NO_VALUE, 378 },
    { Anim_Update0, ANIM_STATUS(41, true), false, ANIM_STATUS(25, false), { Q12(6) }, 378, 383 },
    { Anim_Update2, ANIM_STATUS(42, false), false, ANIM_STATUS(42, true), { Q12(4) }, NO_VALUE, 0 },
    { Anim_Update0, ANIM_STATUS(42, true), false, ANIM_STATUS(26, false), { Q12(8) }, 0, 3 },
    { Anim_Update2, ANIM_STATUS(43, false), false, ANIM_STATUS(43, true), { Q12(4) }, NO_VALUE, 9 },
    { Anim_Update0, ANIM_STATUS(43, true), false, ANIM_STATUS(26, false), { Q12(4) }, 9, 19 },
    { Anim_Update2, ANIM_STATUS(44, false), false, ANIM_STATUS(44, true), { Q12(4) }, NO_VALUE, 4 },
    { Anim_Update0, ANIM_STATUS(44, true), false, ANIM_STATUS(26, false), { Q12(4) }, 4, 8 },
    { Anim_Update2, ANIM_STATUS(45, false), false, ANIM_STATUS(45, true), { Q12(8) }, NO_VALUE, 158 },
    { Anim_Update0, ANIM_STATUS(45, true), false, ANIM_STATUS(18, false), { Q12(1048564) }, 158, 175 }, // TODO: Unsure. Check data, the FFFF could be something else.
    { Anim_Update2, ANIM_STATUS(46, false), false, ANIM_STATUS(46, true), { Q12(0) }, NO_VALUE, 263 },
    { Anim_Update1, ANIM_STATUS(46, true), false, ANIM_STATUS(15, false), { Q12(0) }, 263, 264 },
    { Anim_Update2, ANIM_STATUS(47, false), false, ANIM_STATUS(47, true), { Q12(0) }, NO_VALUE, 294 },
    { Anim_Update1, ANIM_STATUS(47, true), false, ANIM_STATUS(15, false), { Q12(0) }, 294, 295 }
};*/

#if defined(MAP7_S03)
#define PARTICLE_COUNT_MAX 450
#else
#define PARTICLE_COUNT_MAX 300
#endif
#define SNOW_COUNT_LIGHT_MAX 300

typedef enum
{
    ParticleState_Spawn  = 0,
    ParticleState_Active = 1,
    ParticleState_Rest   = 2  
} e_ParticleState;

typedef enum
{
    ParticleType_Snow = 0,
    ParticleType_Unk1 = 1,
    ParticleType_Rain = 2
} e_ParticleType;

typedef enum
{
    SnowType_Light      = 0,
    SnowType_Heavy      = 1,
    SnowType_LightWindy = 2,
    SnowType_HeavyWindy = 3
} e_SnowType;

typedef struct
{
    VECTOR3     position0_0;  // Snow: position, Rain: streak start (bottom)
    VECTOR3     position1_C;  // Snow: unused, Rain: streak end (top)
    SVECTOR3    movement_18;  // Snow: random accumulation, Rain: Y accumulation (affects streak length).
    u8          stateStep_1E; /** `e_ParticleState` */
    u8          type_1F;      /** `e_ParticleType` */
} s_Particle;

typedef struct
{
    char unk_0[3420];
    u16  field_D5C;
    s16  field_D5E;
} s_func_800D8714;

typedef struct
{
    VECTOR3 vector_0;
    VECTOR3 viewPosition_C; // Q19.12
    SVECTOR svec_18;
    SVECTOR viewRotation_20;
    s32     field_28;
} s_ParticleVectors;

/** Seems to be custom boundaries for snow/rain particle systems.
 * Only used in a small handful of maps, and not all fields are populated.
 *
 * Maybe 8 `VECTOR3`s holding positions in Q19.12? Se4ms to be an inefficient AABB.
 */
typedef struct
{
    VECTOR3 corners_0[8];
} s_func_800CB560;
STATIC_ASSERT_SIZEOF(s_func_800CB560, 96);

/** @brief Stores SFX ID and volume.
 * TODO: There's already an `s_Sfx` struct. Should harmonize the names once both are figured out.
 */
typedef struct _SfxVolume
{
    u16 id_0;
    u8  volume_2;
    u8  __pad_3;
} s_SfxVolume;

typedef struct
{
    s_AnimInfo  animInfo_0[56];
    s32         unk_380[301][2]; // Unknown size, biggest constant index used is 35. Associated with anims.
    s_SfxVolume sfxVolumes_CE8[11];
    u_Property  properties_D14[4];
    s8          unk_D24[36];
    s8*         ptr_D48[5];
    s16         field_D5C[4][2]; // Related to animations. Move offset distances?
} s_func_800D2E04;
typedef char static_assertion_sizeof_s_func_800D2E04[(sizeof(s_func_800D2E04) == 3436) ? 1 : -1];

typedef struct
{
    s32               flags_0;
    s_AnmHeader*      anmHdr_4;
    GsCOORDINATE2*    coords_8;
    MATRIX*           matrices_C;
    s8                unk_10[0x8C];
    s_SubCharacter_C8 field_9C;
    s_SubCharacter_D4 field_A8;
    s_SubCharacter_D8 field_AC;
    s32               field_B4[6][4]; // [*][3] is angle.
    s32               field_114;
    s32               field_118;
    VECTOR3           field_11C;
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
    u8 field_0;
    u8 field_1;
} s_800F0158;

typedef struct
{
    u16 sfxId;
    u16 vol;
} s_SfxPair;

extern s_MapOverlayHeader_94 sharedData_800E30C8_1_s02;

// TODO: Ideally this should use some kind of `MAP_FIELD_4C_COUNT` define from each map .h file.
// Right now, `shared.h` gets included before map headers, since this file has decls that map headers may need.
// Not sure of a good fix yet. Might just have to move the decls for these into each map header, or move map config into a file included before shared.h?
#if defined(MAP0_S00)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[200];
#elif defined(MAP0_S01)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[300];
#elif defined(MAP0_S02)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[100];
#elif defined(MAP1_S01)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[300];
#elif defined(MAP1_S03)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[300];
#elif defined(MAP1_S04)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[100];
#elif defined(MAP1_S05)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[500];
#elif defined(MAP2_S01)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[200];
#elif defined(MAP2_S03)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[200];
#elif defined(MAP2_S04)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[200];
#elif defined(MAP3_S05)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[450];
#elif defined(MAP4_S01)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[450];
#elif defined(MAP5_S03)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[150];
#elif defined(MAP6_S04)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[300];
#elif defined(MAP7_S01)
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[250];
#else
    extern s_MapHdr_field_4C sharedData_800DFB7C_0_s00[200];
#endif

extern void (*sharedData_800DD7A0_0_s01[52])(s_SubCharacter*);

extern s_MapPoint2d MAP_POINTS[];

/** Scale. */
extern VECTOR sharedData_800DD870_0_s01;

/** Scale. */
extern VECTOR sharedData_800DD880_0_s01;

/** Could be a padded `VECTOR`, but the ASM for the function `vec = vec` assignments copies only the first 3 fields. */
extern VECTOR3 sharedData_800DE170_0_s01;
extern VECTOR3 sharedData_800DE180_0_s01;
extern VECTOR3 sharedData_800DE190_0_s01;

extern s_func_800700F8_2 sharedData_800E2330_0_s01;

extern u8 sharedData_800DF158_1_s02;

extern s32 sharedData_800E0CA8_0_s00;
extern s32 sharedData_800E0CAC_0_s00;
extern u32 sharedData_800E0CB0_0_s00;
extern u16 sharedData_800E0CB4_0_s00;
extern u16 sharedData_800E0CB6_0_s00;
extern u16 sharedData_800E0CB8_0_s00;
extern s8  sharedData_800E0CBA_0_s00;
extern s32 sharedData_800E32D0_0_s00;

/** Packed weapon attack. `See `WEAPON_ATTACK`. */
extern s8 sharedData_800DD59C_0_s00;

extern s32 sharedData_800DF1F4_0_s00;
extern s16 sharedData_800DF1F8_0_s00;
extern s16 sharedData_800DF1FA_0_s00;

extern s16 g_Particle_RotationY;

extern VECTOR3 g_Particle_Position;     // Q19_12
extern VECTOR3 g_Particle_PrevPosition; // Q19_12
extern q3_12   g_Particle_PrevRotationY;

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
extern u16 sharedData_800E3A0C_0_s00[];
extern s32 sharedData_800E3A18_0_s00;
extern s32 sharedData_800E3A1C_0_s00;

extern s_AnimInfo LARVAL_STALKER_ANIM_INFOS[]; // Used by `Ai_LarvalStalker_Init`.

extern s_AnimInfo STALKER_ANIM_INFOS[]; // Used by `Ai_Stalker_Init`.

// Two variables used by `Ai_Creaper_Init`.
extern s_AnimInfo CREAPER_ANIM_INFOS[];
extern s8 sharedData_800E57CC_1_s02;

extern s_sharedData_800E21D0_0_s01 sharedData_800E21D0_0_s01;

extern s_func_800D2E04 sharedData_800CAA98_0_s01; // Used by `Ai_AirScreamer_Init` / `sharedFunc_800D2BF4_0_s01`

extern s_AnimInfo ROPMER_ANIM_INFOS[];

extern s_AnimInfo GROANER_ANIM_INFOS[];

extern s_AnimInfo HANGED_SCRATCHER_ANIM_INFOS[];

// Three variables used by `Ai_Splithead_Init`.
extern s_AnimInfo SPLITHEAD_ANIM_INFOS[];
extern s16 sharedData_800D8614_1_s05; // These two `s16`s could be `DVECTOR`?
extern s16 sharedData_800D8616_1_s05;

extern u8  sharedData_800D16E4_2_s01;

extern s_AnimInfo BLOODSUCKER_ANIM_INFOS[];

extern u8 sharedData_800DD591_0_s00;
extern u8 sharedData_800DD584_0_s00;
extern u8 sharedData_800DD592_0_s00;

/** `g_ParticlesAddedCounts`. Tracks how many total particles have been added. */
extern s32 sharedData_800DD588_0_s00[2];

/** `g_ParticleSpawnCount`. Tracks how many particles have been added per call. */
extern u8 sharedData_800E2156_0_s01;

extern s_AnimInfo MONSTER_CYBIL_ANIM_INFOS[];
extern s_AnimInfo BLOODY_INCUBATOR_ANIM_INFOS[];
extern s_AnimInfo INCUBATOR_ANIM_INFOS[];
extern s_AnimInfo GHOST_DOCTOR_ANIM_INFOS[];

extern s32 g_Particle_SpeedX;
extern s32 g_Particle_SpeedZ;

extern s32 sharedData_800DFB6C_0_s00;
extern s32 sharedData_800DFB70_0_s00;

extern s32 sharedData_800DD58C_0_s00;
extern s32 sharedData_800E32CC_0_s00;

extern s32 sharedData_800D32A0_0_s02; // `sharedFunc_800CDAA8_0_s02`

extern u16 sharedData_800D21E8_3_s00[];

extern s_func_800CB560 sharedData_800E326C_0_s00;

extern u16 sharedData_800E32D4_0_s00;

/** TODO: Rename to `g_Particles` after funcs have been shared. */
extern s_Particle sharedData_800E0CBC_0_s00[PARTICLE_COUNT_MAX];

extern s_ParticleVectors g_ParticleVectors0;

extern s_ParticleVectors g_ParticleVectors1;

extern u8 sharedData_800DD592_0_s00;

extern s32 sharedData_800DD598_0_s00;

extern s32 sharedData_800DFB4C_0_s00;

extern s32 sharedData_800DFB50_0_s00;

extern s32 sharedData_800CD77C_1_s04; // Used by `sharedFunc_800CB6B0_0_s00` only in MAP1_S04 and MAP4_S00? Similar usage to `sharedData_800DFB50_0_s00`?

extern CVECTOR sharedData_800E3258_0_s00;

extern CVECTOR sharedData_800E325C_0_s00;

extern s32 sharedData_800E2370_0_s01[2];

// Each of these holds 8 bytes, passed to `func_80035F4C` which loops through each byte.
extern u8 sharedData_800CFB14_0_s02[8];
extern u8 sharedData_800CFB1C_0_s02[8];
extern u8 sharedData_800CFB24_0_s02[8];
extern u8 sharedData_800CFB2C_0_s02[8];
extern u8 sharedData_800CFB34_0_s02[8];
extern u8 sharedData_800CFB3C_0_s02[8];
extern u8 sharedData_800CFB44_0_s02[8];
extern u8 sharedData_800CFB4C_0_s02[8];
extern u8 sharedData_800CFB54_0_s02[8];

extern VECTOR3 sharedData_800DE1E0_0_s01;

extern VECTOR3 sharedData_800DE1F0_0_s01;

extern VECTOR3 sharedData_800E2350_0_s01;

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
    s32 field_0;
    s32 field_4;
    s16 field_8;
    s16 field_A;
} s_D_800D5A8C;
STATIC_ASSERT_SIZEOF(s_D_800D5A8C, 12);

typedef struct _MapHeader_field_5C
{
    u8  field_0;
    u8  field_1;
    u8  field_2;
    u8  field_3;
    u8  field_4;
    u8  field_5;
    u8  field_6;
    u8  field_7;
    s16 field_8;
    s16 field_A;
    u16 field_C;
    s16 field_E;
    s16 field_10;
    s16 field_12;
    s16 field_14;
    s16 field_16;
    s16 field_18;
    s16 field_1A;
    u16 field_1C;
    s16 field_1E;
    s32 field_20;
    s32 field_24;
} s_MapHeader_field_5C;

extern s_MapHeader_field_5C sharedData_800DD180_3_s05;

extern s_800E330C sharedData_800E330C_0_s00[20];

extern s_800E34FC sharedData_800E34FC_0_s00[60];

extern const char* MAP_MESSAGES[]; // 0x800DF6B8

extern s_MapOverlayHeader_7C sharedData_800DEE50_1_s01;

extern VECTOR3 sharedData_800F216C_2_s00;

extern VECTOR3 sharedData_800F217C_2_s00;

extern VECTOR3 sharedData_800F21BC_2_s00;

extern VECTOR3 sharedData_800F21DC_2_s00;

extern VECTOR3 sharedData_800F21EC_2_s00;

extern SVECTOR sharedData_800DE220_0_s01;

extern MATRIX sharedData_800DE230_0_s01;

extern s32 g_PuppetNurseHurtSfxIdx[4];

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

extern s_D_800D5A8C sharedData_800D5A8C_3_s03[3];

extern u8 sharedData_800D1D14_3_s02[8];

/** Room flags? */
extern u16 sharedData_800D1D1C_3_s02[60];

extern VECTOR3 sharedData_800DFB10_0_s01[];

extern u8 sharedData_800ED430_2_s02[];

extern u8 sharedData_800ED43C_2_s02[];

bool sharedFunc_800CE688_1_s03(POLY_FT4** poly, s32 idx);

void sharedFunc_800E9B38_2_s02(void);

bool sharedFunc_800CD1F8_0_s01(POLY_FT4** poly, s32 idx);

void sharedFunc_800CFE78_3_s02(s32 arg0);

void sharedFunc_800CFEAC_3_s02(void);

void sharedFunc_800CFEEC_3_s02(void);

void sharedFunc_800CB5F4_3_s05(void);

void sharedFunc_800CBE7C_1_s05(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void sharedFunc_800CCDD4_1_s05(void* arg0, s32 arg1); // Unknown arg types.

q19_12 sharedFunc_800D7714_0_s01(s_SubCharacter* chara);

/* TODO: This function is almost identical to `sharedFunc_800D57C8_0_s01`.
 * Both are used in map0_s01 so ifdefs cannot be used based on the map name.
 * Sections under `#if 0` are what is missing compared to `sharedFunc_800D57C8_0_s01`.
 */
void sharedFunc_800D598C_0_s01(s_SubCharacter* chara);

/* TODO: This function is almost identical to `sharedFunc_800D57C8_0_s01`.
 * Also look at `sharedFunc_800D598C_0_s01`.
 */
void sharedFunc_800D5B10_0_s01(s_SubCharacter* chara);

void sharedFunc_800D5C90_0_s01(s_SubCharacter* chara);

void sharedFunc_800D5D80_0_s01(s_SubCharacter* chara);

void sharedFunc_800D5E14_0_s01(s_SubCharacter* chara);

void sharedFunc_800D3C24_2_s00(s_SubCharacter* chara);

void sharedFunc_800D3E44_2_s00(s_SubCharacter* chara);

void sharedFunc_800D4358_2_s00(s_SubCharacter* chara);

void sharedFunc_800D5268_2_s00(s_SubCharacter* chara);

void sharedFunc_800D5974_2_s00(s_SubCharacter* chara);

void sharedFunc_800D5B88_2_s00(s_SubCharacter* chara);

void sharedFunc_800D5DAC_2_s00(s_SubCharacter* chara);

void sharedFunc_800D6400_2_s00(s_SubCharacter* chara);

void sharedFunc_800D69A0_2_s00(s_SubCharacter* chara);

void sharedFunc_800D6A7C_2_s00(s_SubCharacter* chara);

void sharedFunc_800D6E28_2_s00(s_SubCharacter* chara);

void sharedFunc_800D71A4_2_s00(s_SubCharacter* chara);

void sharedFunc_800D756C_2_s00(s_SubCharacter* chara);

void sharedFunc_800D794C_2_s00(s_SubCharacter* chara);

void sharedFunc_800D7D0C_2_s00(s_SubCharacter* chara);

void sharedFunc_800D80EC_2_s00(s_SubCharacter* chara);

void sharedFunc_800D83F8_2_s00(s_SubCharacter* chara);

void sharedFunc_800D8618_2_s00(s_SubCharacter* chara);

void sharedFunc_800D8C34_2_s00(s_SubCharacter* chara);

void sharedFunc_800D91A0_2_s00(s_SubCharacter* chara);

void sharedFunc_800D92B4_2_s00(s_SubCharacter* chara);

/** Player func. */
void sharedFunc_800D93E8_2_s00(s_SubCharacter* chara);

void sharedFunc_800D98DC_2_s00(s_SubCharacter* chara);

void sharedFunc_800DA598_2_s00(s_SubCharacter* chara);

void sharedFunc_800DB038_2_s00(s_SubCharacter* chara);

void sharedFunc_800DB220_2_s00(s_SubCharacter* chara);

void sharedFunc_800DB54C_2_s00(s_SubCharacter* chara);

void sharedFunc_800DB8AC_2_s00(s_SubCharacter* chara);

/** Player func. */
void sharedFunc_800DBDEC_2_s00(s_SubCharacter* chara);

bool sharedFunc_800DBF88_2_s00(s_SubCharacter* chara, s32 arg1);

bool sharedFunc_800DC0A8_2_s00(s_SubCharacter* chara);

bool sharedFunc_800DC0E4_2_s00(s_SubCharacter* chara, s32 speedMult);

bool sharedFunc_800DC200_2_s00(s_SubCharacter* chara);

bool sharedFunc_800DC30C_2_s00(s_SubCharacter* chara);

bool sharedFunc_800DC3BC_2_s00(s_SubCharacter* chara);

s32 sharedFunc_800DC438_2_s00(s_SubCharacter* chara);

bool sharedFunc_800DC50C_2_s00(s_SubCharacter* chara);

s32 sharedFunc_800DC598_2_s00(s_SubCharacter* chara);

bool sharedFunc_800DC67C_2_s00(s_SubCharacter* chara);

s32 sharedFunc_800DC6E4_2_s00(s_SubCharacter* chara, q19_12 arg1);

q19_12 sharedFunc_800DC894_2_s00(s_SubCharacter*, s32);

s32 sharedFunc_800DC98C_2_s00(s_SubCharacter*, VECTOR3*, VECTOR3*, VECTOR3*);

void sharedFunc_800DD2C4_2_s00(s_SubCharacter*, s32, s32); // Assumed void return type.

void sharedFunc_800DD13C_2_s00(s_SubCharacter* chara, s32 npcSlot, q19_12 spawnChance);

void sharedFunc_800DD4A4_2_s00(s_SubCharacter* chara);

void sharedFunc_800DD4EC_2_s00(s_SubCharacter* chara);

void sharedFunc_800DD534_2_s00(s_SubCharacter* chara);

void sharedFunc_800DDE14_2_s00(s_SubCharacter* chara);

void sharedFunc_800DDF74_2_s00(s_SubCharacter* chara, s32 mulX, q19_12 angle0);

void sharedFunc_800DE034_2_s00(s_SubCharacter* chara, VECTOR3* vec, q19_12 dist);

void sharedFunc_800DE11C_2_s00(s_SubCharacter* chara);

s32 sharedFunc_800DE250_2_s00(s_SubCharacter*); // Assumed return type.

s32 sharedFunc_800DE578_2_s00(s_SubCharacter* chara);

void sharedFunc_800DE6A8_2_s00(s_SubCharacter* chara, VECTOR3* vec, q19_12 dist);

void sharedFunc_800DE7E0_2_s00(s_SubCharacter* chara);

void sharedFunc_800DE940_2_s00(s_SubCharacter*); // Assumed return type.

void sharedFunc_800DEBCC_2_s00(s_SubCharacter* chara);

void sharedFunc_800DECC4_2_s00(s_SubCharacter* chara);

void sharedFunc_800DEE24_2_s00(s_SubCharacter*); // Assumed return type.

void sharedFunc_800DF358_2_s00(s_SubCharacter*); // Assumed return type.

void sharedFunc_800DF448_2_s00(s_SubCharacter*, s32); // Assumed return type.

void sharedFunc_800DF710_2_s00(s_SubCharacter* chara);

void sharedFunc_800DF80C_2_s00(s_SubCharacter* chara);

void sharedFunc_800DF8A0_2_s00(s_SubCharacter*);

void sharedFunc_800E012C_2_s00(s_SubCharacter*); // Assumed return type.

void sharedFunc_800E021C_2_s00(s_SubCharacter*, s32, s32); // Assumed void return type.

void sharedFunc_800E041C_2_s00(s_SubCharacter* chara);

void sharedFunc_800E04B0_2_s00(s_SubCharacter* chara);

void sharedFunc_800E0514_2_s00(s_SubCharacter*); // Assumed return type.

u32 sharedFunc_800E0698_2_s00(s_SubCharacter*);

void sharedFunc_800CB6B0_0_s00(s32 arg1, s32 arg2, s32 arg3);

bool sharedFunc_800CBBBC_0_s00(void);

void sharedFunc_800D01BC_0_s00(u16* arg0, VECTOR3* arg1, s32 arg2);

void sharedFunc_800D0A60_0_s00(s32 caseArg);

bool sharedFunc_800D0B18_0_s00(s32 arg0);

void sharedFunc_800D0CB8_0_s00(void);

void sharedFunc_800D0E04_0_s00(void);

void sharedFunc_800D1C38_0_s00(s_SubCharacter* chara, s_MainCharacterExtra* extra, GsCOORDINATE2* coords);

void sharedFunc_800D209C_0_s00(void);

void sharedFunc_800D20D8_0_s00(void);

void Player_ControlFreeze(void);

void Player_ControlUnfreeze(bool setIdle);

bool sharedFunc_800D23EC_0_s00(s32 playerExtraState, VECTOR3* vec, q3_12 angle, s32 vecCount);

void sharedFunc_800D2C7C_0_s00(s32 arg0);

void sharedFunc_800D2D2C_0_s00(void);

void sharedFunc_800D2D44_0_s00(void);

s32 sharedFunc_800D2D6C_0_s00(void);

void sharedFunc_800D2D84_0_s00(void);

/** Triggers at specific points after the start of a cutscene or dialogue. */
s32 sharedFunc_800D2E50_0_s00(void);

void sharedFunc_800D2E60_0_s00(void);

void sharedFunc_800D2E9C_0_s00(q19_12* offsetX, q19_12* offsetZ, q3_12* angle);

void sharedFunc_800D2E6C_0_s00(void);

void Player_FallBackward(void);

void sharedFunc_800D2E7C_0_s00(void);

void sharedFunc_800D2E84_0_s00(void);

void sharedFunc_800D2E8C_0_s00(q19_12 posX, q19_12 posZ, VECTOR3* vec);

bool sharedFunc_800D2E94_0_s00(void);

u8 sharedFunc_800D2EA4_0_s00(void);

void sharedFunc_800D2EB4_0_s00(void);

void sharedFunc_800D2EF4_0_s00(void);

void sharedFunc_800D3EF4_0_s00(s_SubCharacter* chara);

void sharedFunc_800D4924_0_s00(s_SubCharacter* chara);

void sharedFunc_800D492C_0_s00(s_SubCharacter* chara);

void sharedFunc_800D5098_0_s00(s_SubCharacter* chara);

void sharedFunc_800D54A8_0_s00(s_SubCharacter* chara);

void sharedFunc_800D5B48_0_s00(s_SubCharacter* chara);

void sharedFunc_800D5C64_0_s00(s_SubCharacter* chara);

void sharedFunc_800D5FCC_0_s00(s_SubCharacter* chara);

void sharedFunc_800D63D0_0_s00(s_SubCharacter* chara);

void sharedFunc_800D654C_0_s00(s_SubCharacter* chara);

void sharedFunc_800D6554_0_s00(s_SubCharacter* chara);

void sharedFunc_800D670C_0_s00(s_SubCharacter* chara);

void sharedFunc_800D67FC_0_s00(s_SubCharacter* chara);

void sharedFunc_800D7E04_0_s00(s_SubCharacter* chara, s32 caseArg);

void sharedFunc_800D88AC_0_s00(s_SubCharacter* playerChara);

void Ai_Stalker_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Stalker_Init(s_SubCharacter* chara); // Matches across all maps except `map6_s03`.

void sharedFunc_800D3308_0_s00(s_SubCharacter* chara);

void sharedFunc_800D3B44_0_s00(s_SubCharacter* chara);

void sharedFunc_800D6970_0_s00(s_SubCharacter*, s_AnmHeader*, GsCOORDINATE2*);

void sharedFunc_800D70C4_0_s00(s_SubCharacter*);

void sharedFunc_800D7BE8_0_s00(s_SubCharacter* chara);

/** Among other things, sets the players's anim to anim 3 (which might actually be flags if the field packs more data). */
void sharedFunc_800D88C0_0_s00(s_SubCharacter* player, bool cond);

/** Resets some player properties. */
void sharedFunc_800D8904_0_s00(s_SubCharacter* player, q19_12 afkTime);

void sharedFunc_800D891C_0_s00(s_SubCharacter* player);

void sharedFunc_800D8928_0_s00(s_SubCharacter* chara);

s32 sharedFunc_800D893C_0_s00(s_SubCharacter* chara);

void sharedFunc_800D8950_0_s00(s_SubCharacter* chara);

bool sharedFunc_800D8A00_0_s00(s_SubCharacter* chara, s32 arg1, VECTOR3* arg2In, s32 angleIn, s32 arg4);

void sharedFunc_800D9064_0_s00(s_SubCharacter* chara);

void sharedFunc_800D9078_0_s00(s_SubCharacter* chara);

s32 Anim_StartKeyframeIdxGet(s_SubCharacter* chara);

/** Humanoid init function? */
void sharedFunc_800D923C_0_s00(s_SubCharacter* chara);

/** Snow effect init. */
void sharedFunc_800CBC94_0_s00(s_Particle* particles);

/** Snow particle update. */
void sharedFunc_800CF2A4_0_s01(s32 arg0, s_Particle* part, u16* rand, s32* deltaTime);

/** Snow particle init. */
void sharedFunc_800CF9A8_0_s01(s32 arg0, s_Particle* part, u16* rand);

bool Particle_Update(s_Particle* partHead);

void sharedFunc_800CEFF4_0_s00(s_Particle* part, s32 arg1);

void sharedFunc_800CEB24_0_s00(s_Particle* part);

void sharedFunc_800CFFF8_0_s00(s32 pass, s_func_800CFFF8* part, s16* rand); // TODO: Make this match for `s_Particle`.

void sharedFunc_800CE954_7_s03(s32 pass, s_Particle* part, s16* rand, s32* deltaTime);

void SysWork_StateStepIncrementAfterTime(s32* timer, s32 inc, s32 timeMin, s32 timeMax, bool setTimerToMax, bool incStateStep);

void sharedFunc_800CDAA8_0_s02(s_SubCharacter* playerChara, s_MainCharacterExtra* extra, GsCOORDINATE2* coord);

void sharedFunc_800CB7F4_1_s01(void);

void sharedFunc_800CB8A0_1_s01(s32 idx);

bool sharedFunc_800CBA38_1_s01(s32 idx);

// MAP1_S00 LarvalStalker funcs
void Ai_LarvalStalker_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void sharedFunc_800CF168_1_s00(s_SubCharacter*);

void sharedFunc_800D140C_1_s00(s_SubCharacter*, GsCOORDINATE2*);

void sharedFunc_800D1524_1_s00(s_SubCharacter*, s_AnmHeader*, GsCOORDINATE2*);

void Ai_LarvalStalker_Init(s_SubCharacter* chara);

void sharedFunc_800D17BC_1_s00(s_SubCharacter*);

void sharedFunc_800D1DBC_1_s00(s_SubCharacter*);

// TODO: Make this match for `s_Particle`.
void sharedFunc_800CEFD0_1_s02(s32 pass, s_Particle* part, u16* rand, s32* deltaTime);

/** @brief Sets a map overlay value based on a whether a game event flag is set. */
void sharedFunc_800D0994_3_s00(void);

void sharedFunc_800D09D4_3_s00(void);

// MAP3_S03 puppet nurse/doctor funcs

void sharedFunc_800CDA88_3_s03(s_SubCharacter* nurse);

void Ai_PuppetNurse_UpdateMain(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void func_800CDB5C(s_SubCharacter*, s32);

void Ai_PuppetNurse_Init(s_SubCharacter* chara, s32 isPuppetDoctor);

void Ai_PuppetNurse_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_PuppetDoctor_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_PuppetNurse_DamageHandle(s_SubCharacter*);

s32 PuppetNurse_HurtSfxIdGet(s_SubCharacter* nurse);

void Ai_PuppetNurse_SfxPlay(s_SubCharacter* nurse, s32 idx);

s32 Ai_PuppetNurse_AnimSfxGet(s32 idx);

bool Ai_PuppetNurse_SomeAngleCheck(s_SubCharacter* nurse);

void Ai_NursePuppet_Move(s_SubCharacter* nurse);

bool sharedFunc_800CE398_3_s03(s32 arg0);

void Ai_PuppetNurse_Control1(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control2(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control3_4(s_SubCharacter* nurse, s32 idx);

void Ai_PuppetNurse_Control5(s_SubCharacter* nurse);

void Ai_PuppetNurse_Control6_7(s_SubCharacter* nurse, s32 arg1);

void Ai_PuppetNurse_Control8(s_SubCharacter* nurse);

s32 sharedFunc_800CEEAC_3_s03(void);

void Ai_PuppetNurse_Control9(s_SubCharacter*);

void sharedFunc_800CF7F4_3_s03(s_SubCharacter* chara);

bool sharedFunc_800CF90C_3_s03(s_SubCharacter* chara);

void sharedFunc_800CF9F8_3_s03(s_SubCharacter*);

void Ai_PuppetNurse_Control10(s_SubCharacter*);

void Ai_PuppetNurse_Control11(s_SubCharacter*);

void sharedFunc_800D0110_3_s03(s_SubCharacter*);

void Ai_PuppetNurse_Control(s_SubCharacter* nurse);

void sharedFunc_800D02E4_3_s03(s_SubCharacter*, GsCOORDINATE2*);

void sharedFunc_800D03E4_3_s03(s_SubCharacter*);

void Ai_PuppetNurse_AnimUpdate(s_SubCharacter*, s_AnmHeader*, GsCOORDINATE2*);

void sharedFunc_800D0828_3_s03(s_SubCharacter* harry, GsCOORDINATE2* coords);

void sharedFunc_800D0968_3_s03(s_SubCharacter* chara, GsCOORDINATE2* coords);

void Ai_Creaper_Update(s_SubCharacter* creaper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Creaper_Init(s_SubCharacter* creaper); // `map5_s00` version has extra code at end of func.

void sharedFunc_800D7EE8_1_s02(s_SubCharacter* creaper);

void sharedFunc_800D8244_1_s02(s_SubCharacter* creaper);

void sharedFunc_800D82F0_1_s02(s_SubCharacter* creaper);

void sharedFunc_800D8684_1_s02(s_SubCharacter* creaper);

void sharedFunc_800D8F30_1_s02(s_SubCharacter* creaper);

void sharedFunc_800D9528_1_s02(s_SubCharacter* creaper);

void sharedFunc_800D9774_1_s02(s_SubCharacter* creaper);

void sharedFunc_800D983C_1_s02(s_SubCharacter* creaper);

void sharedFunc_800D9960_1_s02(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void sharedFunc_800D99D0_1_s02(s_SubCharacter* creaper);

void Ai_HangedScratcher_Update(s_SubCharacter* scratcher, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_HangedScratcher_Init(s_SubCharacter* scratcher);

void sharedFunc_800CFF74_5_s00(s_SubCharacter* scratcher);

void sharedFunc_800D029C_5_s00(s_SubCharacter* scratcher);

void sharedFunc_800D03F8_5_s00(s_SubCharacter* chara);

void sharedFunc_800D041C_5_s00(s_SubCharacter* chara);

void sharedFunc_800D26D8_5_s00(s_SubCharacter* scratcher);

void sharedFunc_800D2844_5_s00(s_SubCharacter* scratcher, s_AnmHeader*, GsCOORDINATE2*);

void sharedFunc_800D2C18_5_s00(s_SubCharacter* scratcher);

void sharedFunc_800D3300_5_s00(s_SubCharacter* scratcher);

bool sharedFunc_800D3508_0_s01(s_SubCharacter* chara, s32* arg1);

bool sharedFunc_800D3630_0_s01(s_SubCharacter* chara, q19_12* dist);

/** Returns flags? */
s32 sharedFunc_800D3758_0_s01(s_SubCharacter* chara, q19_12* outDist, q19_12* outAngle, q19_12 dist, s32* arg4);

void Ai_Romper_Update(s_SubCharacter* romper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Romper_Init(s_SubCharacter* romper);

/** Probably Romper func given the placement.. */
void sharedFunc_800E5FC8_2_s02(s_SubCharacter* chara, s16 arg1, s16 arg2, u8* arg3);

void sharedFunc_800E60FC_2_s02(s_SubCharacter* romper);

void sharedFunc_800E6420_2_s02(s_SubCharacter* romper);

void sharedFunc_800E66E8_2_s02(s_SubCharacter* romper);

void sharedFunc_800E6758_2_s02(s_SubCharacter* groaner);

void sharedFunc_800E83D4_2_s02(s_SubCharacter* chara);

void sharedFunc_800E8478_2_s02(s_SubCharacter* chara);

void sharedFunc_800E86C0_2_s02(s_SubCharacter* chara);

void sharedFunc_800E8730_2_s02(s_SubCharacter* romper);

void sharedFunc_800E8A40_2_s02(s_SubCharacter* romper, s_AnmHeader*, GsCOORDINATE2*);

void sharedFunc_800E8DFC_2_s02(s_SubCharacter* romper);

void Ai_Groaner_Update(s_SubCharacter* groaner, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Groaner_Init(s_SubCharacter* groaner); // `map2_s00` has extra block at end of func compared to other maps.

void sharedFunc_800E7914_2_s00(void);

void sharedFunc_800E554C_2_s00(s_SubCharacter* chara);

void sharedFunc_800E55B0_2_s00(s_SubCharacter* chara);

void sharedFunc_800E33DC_2_s00(s_SubCharacter*);

void sharedFunc_800E384C_2_s00(s_SubCharacter* groaner); // `map2_s00` has different version to the other 4 maps which share this, shared sym is needed to share `Ai_Groaner_Update`.

void sharedFunc_800E5930_2_s00(s_SubCharacter* chara);

void sharedFunc_800E5AA4_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E5EC4_2_s00(s_SubCharacter* groaner, s_AnmHeader*, GsCOORDINATE2*);

void sharedFunc_800E6338_2_s00(s_SubCharacter* groaner);

void sharedFunc_800E71E8_2_s00(s_SubCharacter* groaner);

void Ai_Splithead_Update(s_SubCharacter* splithead, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void Ai_Splithead_Init(s_SubCharacter* splithead);

void sharedFunc_800CF990_1_s05(s_SubCharacter* splithead);

void sharedFunc_800CFE94_1_s05(s_SubCharacter* splithead);

void sharedFunc_800D0054_1_s05(s_SubCharacter* splithead);

void sharedFunc_800D267C_1_s05(s_SubCharacter* splithead);

void sharedFunc_800D274C_1_s05(s_SubCharacter* splithead, s_AnmHeader*);

void sharedFunc_800D2D74_1_s05(s_SubCharacter* splithead);

void sharedFunc_800D3388_1_s05(s_SubCharacter* splithead, s32*, s32*);

void sharedFunc_800D17BC_1_s05(s_SubCharacter* splithead);

void sharedFunc_800D2214_1_s05(s_SubCharacter* splithead);

void sharedFunc_800D263C_1_s05(s_SubCharacter* splithead);

void sharedFunc_800D3AFC_1_s05(s_SubCharacter* splithead);

void sharedFunc_800D3B30_1_s05(s_SubCharacter* splithead);

void sharedFunc_800D4070_1_s05(s_SubCharacter* splithead);

/** Probably takes X and Z position values. */
void sharedFunc_800D450C_1_s05(s32 arg0, s32 arg1);

bool sharedFunc_800D4530_1_s05(s_SubCharacter* splithead);

extern GsCOORDINATE2* sharedData_800D8610_1_s05;

void Ai_AirScreamer_Update(s_SubCharacter* airScreamer, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

bool sharedFunc_800D21E4_0_s01(s_AnmHeader* anmHdr, GsCOORDINATE2* coords);

void sharedFunc_800D2200_0_s01(s_SubCharacter* airScreamer);

bool sharedFunc_800D2274_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D2364_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2390_0_s01(s_SubCharacter* airScreamer);

bool Ai_AirScreamer_Init(s_SubCharacter* airScreamer);

void sharedFunc_800D2B00_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2B10_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2B28_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2B4C_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2BB0_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2BE4_0_s01(s_SubCharacter* chara);

void sharedFunc_800D2BF4_0_s01(s_SubCharacter* chara);

bool sharedFunc_800D2E04_0_s01(s_SubCharacter* chara, VECTOR3* inVec, s32* outDist, s32* outAngle);

bool sharedFunc_800D3430_0_s01(s_SubCharacter* chara, s32* arg1, s32* arg2);

s32 sharedFunc_800D3814_0_s01(s_SubCharacter* chara);

s32 sharedFunc_800D31D0_0_s01(s_SubCharacter* chara, VECTOR3* arg1, s32 arg2);

bool sharedFunc_800D3928_0_s01(s_SubCharacter* airScreamer);

void sharedSymbol_800D3B0C_0_s01(s_SubCharacter* chara);

bool sharedFunc_800D62D8_0_s01(s_SubCharacter* airScreamer);

/** Returns anim-related index. */
s32 sharedFunc_800D4A80_0_s01(s_SubCharacter* chara);

/** Gets player Y position with an offset. */
s32 sharedFunc_800D5274_0_s01(void);

void sharedFunc_800D633C_0_s01(s_SubCharacter* chara);
void sharedFunc_800D63A4_0_s01(s_SubCharacter* chara);
void sharedFunc_800D6600_0_s01(s_SubCharacter*);

s32 sharedFunc_800D7120_0_s01(s32, s32, s32);
s32 sharedFunc_800D71F0_0_s01(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 sharedFunc_800D7440_0_s01(s_800C4590* arg0, VECTOR* vec1, s_SubCharacter* chara);

void sharedFunc_800D7560_0_s01(s_SubCharacter* chara);

void sharedFunc_800D76A0_0_s01(s_SubCharacter* chara);

s32 sharedFunc_800D77D0_0_s01(s_SubCharacter*); // Assumed return type.

bool sharedFunc_800D7AB0_0_s01(s_SubCharacter* airScreamer);

/** @brief Applies a multi-stage bend deformation to several model coordinates.
 * Builds three rotation matrices using scaled fractions of `chara->field_2A` and
 * multiplies them into `coords[10]`, `coords[9]`, `coords[1]`, and `coords[2]`.
 * Used when the animation flag bit 0 is active to drive a chained bending motion.
 */
void sharedFunc_800D7B14_0_s01(s_SubCharacter* airScreamer, GsCOORDINATE2* coords);

void sharedFunc_800D7EBC_0_s01(s_SubCharacter* airScreamer);

bool sharedFunc_800D81B0_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D81D0_0_s01(s_SubCharacter* chara);

void sharedFunc_800D8244_0_s01(s_SubCharacter* chara);

void sharedFunc_800D82B8_0_s01(s_SubCharacter* airScreamer);

void sharedFunc_800D8714_0_s01(s_SubCharacter* chara, s32 arg1, s32 arg2);

void sharedFunc_800D87FC_0_s01(s_SubCharacter* chara);

void sharedFunc_800D8804_0_s01(void);

s32 sharedFunc_800D929C_0_s00(void);

s32 sharedFunc_800E1114_6_s04(s32 arg0, s32 arg1);

void sharedFunc_800E1258_6_s04(s32 arg0);

void sharedFunc_800E1290_6_s04(void);

void sharedFunc_800E12D0_6_s04(void);

s32 sharedFunc_800D2DAC_0_s00(void); // Player anim func. Checks if the active keyframe is at the start or end of the anim's range.
s32 sharedFunc_800D8964_0_s00(s_SubCharacter* chara); // NPC anim func. Checks if the active keyframe is at the start or end of the anim's range.
bool sharedFunc_800D9188_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx, s32 sfx);

void sharedFunc_800D0700_0_s00(VECTOR3* point, VECTOR3* lineStart, VECTOR3* lineEnd, s32 flag);

void sharedFunc_800D08B8_0_s00(s8 arg0, u32 arg1);

bool sharedFunc_800D908C_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx0, s32 keyframeIdx1, s32 sfx, s32 pitch);

// `Ai_Bloodsucker` related
void Ai_Bloodsucker_Update(s_SubCharacter* bloodsucker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords);
void Ai_Bloodsucker_Init(s_SubCharacter* bloodsucker);
void sharedFunc_800D0E20_3_s03(s_SubCharacter* bloodsucker);
void sharedSymbol_800D0E38_3_s03(s_SubCharacter* bloodsucker);
void sharedFunc_800D0E80_3_s03(s_SubCharacter* bloodsucker);
void sharedSymbol_800D0ECC_3_s03(s_SubCharacter* bloodsucker);
void sharedFunc_800D0F28_3_s03(s_SubCharacter* bloodsucker, s_AnmHeader*, GsCOORDINATE2*);

/** `arg1` is a multiplier? */
s32 Chara_DamageTake(s_SubCharacter*, s32 mult);

void sharedFunc_800D3CC4_0_s01(s_SubCharacter* chara);

void sharedFunc_800D3DFC_0_s01(s_SubCharacter* chara);

s32 sharedFunc_800D569C_0_s01(s_SubCharacter* chara, q19_12 posY, q19_12 dist);

void sharedFunc_800D57C8_0_s01(s_SubCharacter* chara);

void sharedFunc_800D5E78_0_s01(s_SubCharacter* chara, q19_12 angle);

s32 sharedFunc_800D6A60_0_s01(VECTOR3* vec0, VECTOR3* vec1, s_SubCharacter* chara, s32 arg3, VECTOR3* vec2);

void sharedFunc_800D6C7C_0_s01(VECTOR* arg0, s_SubCharacter* chara, s32 arg2, VECTOR3* arg3);

void sharedFunc_800D2364_0_s01(s_SubCharacter* chara);

void sharedFunc_800D5638_0_s01(s_SubCharacter* chara);

void sharedFunc_800DF2D0_2_s00(s_SubCharacter* chara);

void sharedFunc_800D4E84_0_s01(s_SubCharacter* chara);

void sharedFunc_800D529C_0_s01(s_SubCharacter* chara, s32 radius, s32 angle);

void sharedFunc_800CE934_0_s02(void);

void sharedFunc_800D0850_0_s01(VECTOR3* vec0, VECTOR3* vec1);

void sharedFunc_800CFFD8_0_s01(VECTOR3* vec0, q3_12* rotX, q3_12* rotY);

void sharedFunc_800CD7F8_3_s03(s_SubCharacter* chara, q19_12 posX, q19_12 posZ, q19_12 range);

void sharedFunc_800CD920_3_s03(s_SubCharacter* chara, q19_12 posX, q19_12 posZ);

q19_12 sharedFunc_800CD940_3_s03(q19_12 pos0, q19_12 pos1);

s32 sharedFunc_800CD980_3_s03(s_SubCharacter* chara);

q19_12 sharedFunc_800CD6B0_3_s03(MATRIX* mat, s32 matCount, VECTOR3* center);

void sharedFunc_800D6EC4_0_s01(s_SubCharacter* chara);

void sharedFunc_800D7B14_0_s01(s_SubCharacter*, GsCOORDINATE2*);

void sharedFunc_800CE884_0_s02(s32 arg0);

void sharedFunc_800CE8B8_0_s02(void);

void sharedFunc_800CE5D4_1_s03(VECTOR3* arg0, u16 arg1, u16 arg2, u32 arg3);

void sharedFunc_800CBA4C_1_s02(s32, s32, s32);

void sharedFunc_800CBC98_1_s02(void);

void sharedFunc_800CBD58_1_s02(void);

void sharedFunc_800DE1F8_2_s00(s_SubCharacter* chara);

void sharedFunc_800DEC64_2_s00(s_SubCharacter* chara);

void sharedFunc_800DEC84_2_s00(s_SubCharacter* chara, q19_12 radius, q19_12 angle);

void sharedFunc_800DECA4_2_s00(s_SubCharacter* chara, VECTOR3* vec, q19_12 dist);

void sharedFunc_800DF22C_2_s00(s_SubCharacter* chara);

s32 sharedFunc_800DF24C_2_s00(s_SubCharacter* chara);

s32 sharedFunc_800D2FB4_0_s01(s_SubCharacter* chara, VECTOR3* playerPos, s32 playerField10C);

void sharedFunc_800D72E8_0_s01(s_SubCharacter* chara, s32 field_34, s32 rotSpeedY);

void sharedFunc_800D6EC4_0_s01(s_SubCharacter* chara);

void MapEvent_DoorJammed(void);

void MapEvent_DoorLocked(void);

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

typedef struct
{
    s_WorldObject_0 object_0;
    VECTOR3         position_1C; // Q19.12
    SVECTOR3        rotation_28; // Q19.12
} s_WorldObjectDesc;

typedef struct
{
    s_WorldObject_0 object_0;
    VECTOR3         position_1C; // Q19.12
} s_WorldObjectDescNoRot;

#define WorldObjectPoseInit(eventPos, posX, posY, posZ, rotX, rotY, rotZ) \
    WorldObjectPoseSet(eventPos, Q12(posX), Q12(posY), Q12(posZ), FP_ANGLE(rotX), FP_ANGLE(rotY), FP_ANGLE(rotZ))

#define WorldObjectPoseSet(eventPose, posX, posY, posZ, rotX, rotY, rotZ) \
{                                                                         \
    Math_Vector3Set(&(eventPose)->position_0, posX, posY, posZ);          \
    Math_SetSVectorFast(&(eventPose)->rotation_C, rotX, rotY, rotZ);      \
}

#define WorldObjectInit(eventPos, name, posX, posY, posZ, rotX, rotY, rotZ) \
    WorldObjectSet(eventPos, name, Q12(posX), Q12(posY), Q12(posZ), FP_ANGLE(rotX), FP_ANGLE(rotY), FP_ANGLE(rotZ))

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

/** @brief Updates the move speed of a character.
 *
 * @param chara Character to update.
 * @param speed Move speed (Q*.12).
 */
#define Chara_MoveSpeedUpdate(chara, speed) \
    chara->moveSpeed_38 = APPROACH(chara->moveSpeed_38, Q12(0.0f), FP_MULTIPLY_PRECISE(g_DeltaTime0, speed, Q12_SHIFT))

// TODO: Is it possible to merge these macros?
#define Chara_MoveSpeedUpdate2(chara, speed, limit)                                                  \
{                                                                                                    \
    q19_12 moveSpeed;                                                                                \
    q19_12 newSpeed;                                                                                 \
    q19_12 newMoveSpeed;                                                                             \
                                                                                                     \
    moveSpeed = chara->moveSpeed_38;                                                                 \
    if (moveSpeed > limit)                                                                           \
    {                                                                                                \
        newMoveSpeed = limit;                                                                        \
        limit        = Q12(0.0f);                                                                    \
        newSpeed     = moveSpeed - FP_MULTIPLY_PRECISE(g_DeltaTime0, speed, Q12_SHIFT);              \
        if (newMoveSpeed < newSpeed)                                                                 \
        {                                                                                            \
            newMoveSpeed = newSpeed;                                                                 \
        }                                                                                            \
    }                                                                                                \
    else                                                                                             \
    {                                                                                                \
        newMoveSpeed = limit;                                                                        \
        newSpeed     = moveSpeed + FP_MULTIPLY_PRECISE(g_DeltaTime0, speed, Q12_SHIFT);              \
        if (newMoveSpeed >= newSpeed)                                                                \
        {                                                                                            \
            newMoveSpeed = newSpeed;                                                                 \
        }                                                                                            \
    }                                                                                                \
    chara->moveSpeed_38 = newMoveSpeed;                                                              \
}

#define Chara_MoveSpeedUpdate3(chara, speed, limit) \
    chara->moveSpeed_38 = APPROACH(chara->moveSpeed_38, limit, FP_MULTIPLY_PRECISE(g_DeltaTime0, speed, Q12_SHIFT))

#endif
