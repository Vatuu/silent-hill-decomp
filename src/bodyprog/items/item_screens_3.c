#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/math.h"

const s32 rodataPad_800262F8 = 0;

#include "D_800262FC_Rodata.h"

const char* g_ItemNames[] =
{
    "Health_drink(s)",
    "First_aid_kit(s)",
    "Ampoule(s)",
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    "Lobby_key",
    "House_key",
    "Key_of_[Lion]",
    "Key_of_[Woodman]",
    "Key_of_[Scarecrow]",
    "Library_reserve_key",
    "Classroom_key",
    "K._Gordon_key",
    "Drawbridge_key",
    "Basement_key",
    "Basement_storeroom_key",
    "Examination_room_key",
    "Antique_shop_key",
    "Sewer_key",
    "Key_of_[Ophiel]",
    "Key_of_[Hagith]",
    "Key_of_[Phaleg]",
    "Key_of_[Bethor]",
    "Key_of_[Aratron]",
    "A_note_[To_school]",
    "A_note_[Doghouse]",
    "Picture_card",
    " ",
    "Sewer_exit_key",
    "Channeling_stone",
    0, 0, 0, 0, 0, 0, 0,
    "Chemical",
    "Gold_medallion",
    "Silver_medallion",
    "Rubber_ball",
    "[Flauros]",
    "Plastic_bottle",
    "Unknown_liquid",
    "Plate_of_[Turtle]",
    "Plate_of_[Hatter]",
    "Plate_of_[Cat]",
    "Plate_of_[Queen]",
    "Blood_pack",
    "Disinfecting_alcohol",
    "Lighter",
    "Video_tape",
    " ",
    "Kaufmann_key",
    "Receipt",
    "Safe_key",
    "Magnet",
    "Motorcycle_key",
    "Bird_cage_key",
    "Pliers",
    "Screwdriver",
    "Camera",
    "Ring_of_contract",
    "Stone_of_time",
    "Amulet_of_Solomon",
    "Crest_of_Mercury",
    "Ankh",
    "Dagger_of_Melchior",
    "Disk_of_Ouroboros",
    "Kitchen_knife",
    "Steel_pipe",
    "Rock_drill",
    " ",
    "Hammer",
    "Chainsaw",
    "Katana",
    "Axe",
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    "Handgun",
    "Hunting_rifle",
    "Shotgun",
    "Hyper_Blaster",
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    "Handgun_bullets",
    "Rifle_shells",
    "Shotgun_shells",
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    "Flashlight",
    "Pocket_radio",
    "Gasoline_tank"
};

const char* g_ItemDescriptions[] =
{
    "Supplies_nutrition_to\n\t\t\t\t\trecover_a_small_amount_of\n\t\t\t\t\tstamina.",
    "Heals_injury_to_provide\n\t\t\t\t\tmoderate_stamina_recovery.",
    "Relieve_pain_to_recover\n\t\t\t\t\tstamina_to_high.\n\t\t\t\t\tEffect_lasts_for_a_while.",
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    "The_key_to_open\n\t\t\t\t\tthe_door_to_the_lobby.\n\t\t\t\t\tI_found_it_in_the_locker_room.", 
    "The_house_key\n\t\t\t\t\thidden_in_the_dog_house.",
    "The_key_to_the_garden_of\n\t\t\t\t\tthe_house._Found_in_patrol\n\t\t\t\t\tcar's_trunk.",
    "The_key_to_the_garden_of\n\t\t\t\t\tthe_house._Found_in_the\n\t\t\t\t\tbasketball_court.",
    "The_key_to_the_garden_of\n\t\t\t\t\tthe_house._Found_in_mailbox\n\t\t\t\t\tblocked_by_a_fallen_tree.",
    "The_key_to_the_school's_2nd\n\t\t\t\t\tfloor_library_reserves.\n\t\t\t\t\tPicked_up_in_the_locker_room.",
    "The_tagged_classroom_key\n\t\t\t\t\tfound_hanging_in_the_drainpipe\n\t\t\t\t\ton_the_roof.",
    "The_tag_says,_[K._Gordon;]\n\t\t\t\t\tfound_in_the_school's\n\t\t\t\t\tboiler_room.",
    "Key_to_operate_the_drawbridge.\n\t\t\t\t\tFound_in_the_church.",
    "The_hospital_basement\n\t\t\t\t\tdoor_key,_found_on_the_table\n\t\t\t\t\tin_1st_floor_conference_room.",
    "The_hospital_basement\n\t\t\t\t\tstoreroom_key_found\n\t\t\t\t\tin_the_operating_room.",
    "Found_in_patient_room\n\t\t\t\t\tin_the_2nd_floor_basement.",
    "The_tagged_key_with_a_shop\n\t\t\t\t\tname_on_it_that_Dahlia_left\n\t\t\t\t\tat_the_hospital.",
    "Sewer_passageway_door_key.",
    "The_word_[Ophiel]_is\n\t\t\t\t\tengraved_on_the_key.",
    "The_word_[Hagith]_is\n\t\t\t\t\tengraved_on_the_key.",
    "The_word_[Phaleg]_is\n\t\t\t\t\tengraved_on_the_key.",
    "The_word_[Bethor]_is\n\t\t\t\t\tengraved_on_the_key.",
    "The_word_[Aratron]_is\n\t\t\t\t\tengraved_on_the_key.",
    "[To_school]_is_written\n\t\t\t\t\tin_Cheryl's_handwriting.",
    "[Doghouse]_and_[Levin_st.]\n\t\t\t\t\tare_written_in\n\t\t\t\t\tCheryl's_handwriting.",
    "A_rectangular_card_with\n\t\t\t\t\ta_picture_of_a_key._Found_on\n\t\t\t\t\ta_desk_in_a_classroom.",
    " ",
    "Key_to_exit_from_the_sewer\n\t\t\t\t\tto_the_resort_area,_which_was\n\t\t\t\t\tdropped_in_the_water.",
    "A_mystical_stone_possessing\n\t\t\t\t\tpower._If_used_somewhere,\n\t\t\t\t\tthe_result_will_be...?",
    0, 0, 0, 0, 0, 0, 0,
    "The_label_reads,_[Concentrated\n\t\t\t\t\thydrochloric_acid.]_Found_in\n\t\t\t\t\tthe_lab_equipment_room.",
    "A_picture_of_a_clock_tower\n\t\t\t\t\tis_engraved_on_the_surface.\n\t\t\t\t\tFound_in_the_chemistry_lab.",
    "A_picture_of_a_clock_tower\n\t\t\t\t\tis_engraved_on_the_surface.\n\t\t\t\t\tFound_in_the_music_room.",
    "Florescent_pink_rubber_ball\n\t\t\t\t\tused_by_children.",
    "Pyramid_shaped_object_found\n\t\t\t\t\tin_the_church.\n\t\t\t\t\tPurpose_and_use_unknown.",
    "Empty_bottle_found\n\t\t\t\t\tin_the_kitchen\n\t\t\t\t\tof_the_hospital.",
    "Red_liquid_found_in\n\t\t\t\t\ta_broken_vial_in_the\n\t\t\t\t\tHospital_Director's_room.",
    "Square,_blue_plate\n\t\t\t\t\twith_a_picture_of\n\t\t\t\t\ta_[Mock_Turtle.]",
    "Square,_green_plate\n\t\t\t\t\twith_a_picture_of\n\t\t\t\t\ta_[Mad_Hatter.]",
    "Square,_yellow_plate\n\t\t\t\t\twith_a_picture_of\n\t\t\t\t\ta_[Cheshire_Cat.]",
    "Square,_red_plate\n\t\t\t\t\twith_a_picture_of\n\t\t\t\t\ta_[Queen_of_Hearts.]",
    "200ml_blood_pack.\n\t\t\t\t\tFound_in_the_hospital\n\t\t\t\t\tstorage_room.",
    "Isopropyl_alcohol_bottle,\n\t\t\t\t\tfound_in_ICU_at_the_hospital.",
    "Oil_lighter_found_in_Room_201.",
    "Nothing_on_the_label.\n\t\t\t\t\tFound_on_2nd_floor\n\t\t\t\t\thospital_basement.",
    " ",
    "A_[3]_is_written_on_the_tag.\n\t\t\t\t\tThe_key_was_thought_to_have\n\t\t\t\t\tbeen_dropped_by_Kaufmann.",
    "Receipt_from_General_Store,\n\t\t\t\t\tthought_to_have_been_dropped\n\t\t\t\t\tby_Kaufmann.",
    "Key_to_the_safe,\n\t\t\t\t\tfound_at_Indian_Runner\n\t\t\t\t\tGeneral_Store.",
    "Long,_thin_magnetic_rod\n\t\t\t\t\twith_a_string_attached,\n\t\t\t\t\tin_the_motel_office.",
    "Key_to_an_old_motorcycle,\n\t\t\t\t\twhich_was_dropped_between_the\n\t\t\t\t\tfloorboards_in_the_motel_room.",
    "Bird_cage_key_with\n\t\t\t\t\tengraved_handle.",
    "Tool_to_use_on\n\t\t\t\t\tmetal_and_wires.\n\t\t\t\t\tRusted_but_usable.",
    "Tool_for_screws.\n\t\t\t\t\tRusted,_but_usable.",
    "Camera_with_flash.",
    "Rustic,_hefty-looking_ring\n\t\t\t\t\tof_unknown_material.",
    "Large_stone_with_clock-face\n\t\t\t\t\tdesign_on_pillar_with_astrology\n\t\t\t\t\tchart_hanging_from_it.",
    "The_amulet_is_a_star_shaped\n\t\t\t\t\tobject_with_6_corners_named\n\t\t\t\t\tafter_the_ancient_magician.",
    "Snake_in_the_symbol_of\n\t\t\t\t\tmercury_signifies_alchemy.",
    "Elliptical_talisman\n\t\t\t\t\twith_a_cross_inside.",
    "The_ancient_dagger\n\t\t\t\t\tnamed_after_the_Magi.",
    "Ring_of_a_snake_biting\n\t\t\t\t\tit's_own_tail.",
    "Hard_to_use,\n\t\t\t\t\tbut_better_than_nothing.",
    "3'_long_steel_pipe.\n\t\t\t\t\tLong_range_but_of_limited_use.",
    "A_tool_used_in_road_construction\n\t\t\t\t\tto_create_holes_in_the_road_for\n\t\t\t\t\tpoles.",
    " ",
    "Emergency_hammer.\n\t\t\t\t\tHighly_damaging,\n\t\t\t\t\tbut_hard_to_use.",
    "Power_tool_used_for_cutting\n\t\t\t\t\tdown_trees,_etc.,_highly_deadly.",
    "Traditional_single_edged\n\t\t\t\t\tJapanese_blade.",
    "Small_one_hand_axe.\n\t\t\t\t\tModerately_effective\n\t\t\t\t\tas_a_weapon.",
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    "Handgun_received_from_Cybil.\n\t\t\t\t\tHolds_up_to_15_rounds.",
    "Holds_up_to_6_rounds.",
    "Fires_in_a_wide_radius.\n\t\t\t\t\tHolds_up_to_6_rounds.",
    "High-powered_handgun\n\t\t\t\t\twith_infrared_scope\n\t\t\t\t\tand_unlimited_bullets.",
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    "Ammo_for_the_handgun.",
    "Ammo_for_the_hunting_rifle.",
    "Ammo_for_the_shotgun.",
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    "One_touch_on/off_switch.\n\t\t\t\t\tIn_the_chest_pocket.",
    "Portable_radio_that\n\t\t\t\t\temits_static\n\t\t\t\t\twhen_monsters_are_near.",
    "Fuel_for_chainsaws_and\n\t\t\t\t\trock_drills."
};

s32 D_800AE178 = 0;
s32 g_Inventory_SelectedItemIdx = 0;
s32 D_800AE180 = 0;
u8 g_Inventory_EquippedItem = 0;
u8 D_800AE185 = 0;
u8 D_800AE186 = 0;
u8 D_800AE187 = 0;
u32 D_800AE188 = 0;
s16 D_800AE18C = 0; // only ever set to 0, nothing reads it.
s16 D_800AE18E = 0; // only ever set to 0, nothing reads it.
s32 D_800AE190 = 0;
s16 g_Inventory_HealthStatusScanlineTimer = 0;
s16 g_Inventory_HealthStatusColorGradientTimer = 0;
s16 D_800AE198 = 0;
s16 g_Inventory_HealthStatusScanlinePosition = -300;
s32 g_Inventory_ItemNameTimer = 0;
s32 g_Inventory_DescriptionRollTimer = 0;
s32 g_Inventory_ScrollTransitionTimer = 0;
s16 D_800AE1A8 = 0;
s16 __padding0 = 0;
s32 g_PickupItemAnimState = 0;
s32 D_800AE1B0 = 0;

u32 D_800AE1B4[3] = { 0x00000000, 0x000000CC, 0xFFFFFEC9 }; // `VECTOR3`?
// Referenced only by `func_80055648` (https://decomp.me/scratch/joGmE)
// Doesn't look like `VECTOR3` tbh. Each word is larger than the previous.
u32 D_800AE1C0[] =
{
    0x00000000,
    0x00000000,
    0x00000026,
    0x0000004C,
    0x0000005E,
    0x00000070,
    0x00000085,
    0x00000099,
    0x000000B0,
    0x000000BD,
    0x000000D1,
    0x000000DC,
    0x000000E6,
    0x000000F0,
    0x000000F5,
    0x000000FA,
    0x000000FF,
};

s_800AE204 D_800AE204[26] =
{
    { 89,   102,  1820, 542,  387,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 21,   306,  3413, 573,  356,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 4,    306,  682,  558,  356,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { -30,  289,  2275, 527,  418,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { -64,  255,  3072, 527,  465,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { -115, 306,  341,  449,  387,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { -200, 289,  1137, 589,  465,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { -285, 221,  2048, 496,  387,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { -370, 272,  2844, 465,  387,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { -455, 255,  3413, 449,  387,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { -642, 170,  0,    418,  310,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { -727, 136,  910,  387,  310,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 13,   30,   2503, 270,  270,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { -64,  60,   568,  360,  240,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { -115, 100,  2048, 340,  190,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { -141, 30,   1137, 270,  240,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { -192, 70,   3640, 340,  180,  0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
    { 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 }
};

s_800AE4DC D_800AE4DC[3] = // Used in `func_8005B62C` (https://decomp.me/scratch/2BvV1)
{
    { &D_800AE204[1],  3,  0,      0, 0x80, 0x3F, 0xBF },
    { &D_800AE204[0],  12, 0,      0, 0x80, 0x3F, 0xBF },
    { &D_800AE204[12], 5,  0xFF67, 0, 0x80, 0x3F, 0xBF }, 
};

SVECTOR D_800AE500[4] =
{
    SVECTOR(0.0f,      255.65f,  255.65f),
    SVECTOR(-255.65f,  0.0f,     255.65f),
    SVECTOR(255.65f,   0.0f,     255.65f),
    SVECTOR(0.0f,     -255.65f,  255.65f),
};

s16 D_800AE520[] =
{
    0x03F6, 0x03E1, 0x03CD, 0x03B8,
    0x03A4, 0x038F, 0x037B, 0x0366,
    0x0351, 0x033B, 0x0326, 0x0310,
    0x02FA, 0x02E4, 0x02CD, 0x02B6,
    0x029E, 0x0286, 0x026E, 0x0254,
    0x023A, 0x021F, 0x0203, 0x01E6,
    0x01C7, 0x01A6, 0x0183, 0x015D,
    0x0133, 0x0102, 0x00C5, 0x0057,
    0x0000, 0x0000
};

s16 D_800AE564[] =
{
    0x1000, 0x0FCD, 0x0F52, 0x0EFE,
    0x0EAC, 0x0E5B, 0x0E0C, 0x0DBF,
    0x0D73, 0x0D2A, 0x0CE2, 0x0C9B,
    0x0C56, 0x0C12, 0x0BD0, 0x0B8F,
    0x0B50, 0x0B12, 0x0AD5, 0x0A9A,
    0x0A5F, 0x0A26, 0x09EF, 0x09B8,
    0x0983, 0x094F, 0x091C, 0x08EA,
    0x08B9, 0x0889, 0x085A, 0x082C,
    0x0800, 0x0000, 0x0000, 0x0020,
    0x0140, 0x00E0, 0x0000, 0x0100,
    0x0140, 0x00E0
};

// https://decomp.me/scratch/q3B9W `func_8005E414` accesses the table above using negative offsets from `D_800AE5B8`.
// The last 0x10 bytes of the above table might be `RECT` as well.
RECT D_800AE5B8[2] =
{
    { 0x140, 0x100, 0x140, 0x0E0 },
    { 0x0A0, 0x090, 0x0A0, 0x170 }
};

u16 D_800AE5C8[2] = {0x01E0, 0x0170}; // Passed to `SetDrawOffset`.

// https://decomp.me/scratch/HNL4n something to do with animations?
// `var_s7 = *(((animStatus + 1) * 2) + &D_800AE5CC) - *((animStatus * 2) + &D_800AE5CC);`
u16 D_800AE5CC[18] = 
{
    0x0000, 0x0001, 0x0004, 0x0007,
    0x0009, 0x000B, 0x000D, 0x000F,
    0x0011, 0x0014, 0x0017, 0x0018,
    0x0019, 0x001C, 0x001E, 0x0020,
    0x0022, 0x0000
};

// https://decomp.me/scratch/HNL4n Referenced under `if (g_GameWork.config_0.optExtraBloodColor_24 != 0xE)`
// Similar access pattern to the table above.
u16 D_800AE5F0[136] =
{
    0x0001, 0x0000, 0x0001, 0x0000,
    0x0360, 0x00C0, 0x03E0, 0xFD90,
    0x03E0, 0xFC20, 0x0320, 0xFE50,
    0x09C0, 0xF950, 0x0100, 0xFFE0,
    0x0160, 0x05E0, 0x01C0, 0xFE30,
    0x0360, 0x00F0, 0x02C0, 0xFDB0,
    0x0360, 0xFD70, 0x02C0, 0xFE40,
    0x0640, 0x0130, 0x0220, 0xFF40,
    0x04E0, 0xFFA0, 0x02A0, 0xFEC0,
    0x04E0, 0xFAC0, 0x0280, 0xFE70,
    0x05DC, 0xFCAE, 0x00C8, 0xFF9C,
    0x0300, 0xFCB0, 0x02C0, 0x00C0,
    0x06E0, 0xFFC0, 0x01E0, 0xFF70,
    0x0340, 0x00A0, 0x0360, 0xFF70,
    0x06E0, 0xFAA0, 0x0160, 0xFFC0,
    0x03A0, 0x0070, 0x0320, 0xFD10,
    0x07A0, 0xF9F0, 0x0160, 0xFEF0,
    0x0CC0, 0xFD90, 0x0100, 0xFFF0,
    0x04C0, 0x0080, 0x01C0, 0xFF00,
    0x0400, 0xFD40, 0x0260, 0xFEA0,
    0x01C0, 0x0D40, 0x0180, 0x0070,
    0x05A0, 0x01F0, 0x0B32, 0xFAD0,
    0x0AA0, 0xFAB0, 0x0200, 0xFF10,
    0x05A0, 0xFE90, 0x0160, 0xFF20,
    0x0620, 0xFC80, 0x0140, 0xFF30,
    0x0620, 0x0120, 0x0240, 0xFE70,
    0x0A20, 0x0090, 0x00E0, 0xFF70,
    0x0140, 0x0920, 0x00E0, 0xFF70,
    0x0580, 0x0180, 0x0220, 0xFDF0,
    0x0580, 0xFD80, 0x0220, 0xFE20,
    0x0300, 0x12E0, 0x02E0, 0x00F0,
    0x0AE0, 0x0B60, 0x02E0, 0x0210,
    0x08A0, 0xEDF0, 0x02A0, 0x0220,
    0x0300, 0xEDA0, 0x02E0, 0xFD70,
};
// https://decomp.me/scratch/HNL4n `temp_a0 = D_800AE700[animStatus];`
u8 D_800AE700[16] =
{
    0x64, 0x48, 0x48, 0x3C,
    0x3C, 0x6E, 0x6E, 0x6E,
    0x3A, 0x50, 0x3C, 0x3C,
    0x48, 0x5E, 0x64, 0x64,
};

// layout based on `func_800652F4`
typedef struct
{
    u8 unk_0;
    u8 unk_1;
    u8 unk_2;
} s_800AE710;

s_800AE710 D_800AE710[4] =
{
    {},
    {0x4C, 0x27, 0x7F},
    {},
    {}
};

// Seems like a struct of 2 s32 based on `func_80066184`.
s32 D_800AE71C[] =
{
    0x00015AE1, 0xFFFEAEB9,
    0x00017B33, 0xFFFEAEB9,
    0x00015AE1, 0xFFFE8E67,
    0x00017B33, 0xFFFE8E67,
};

// Some timer used in func_80066184
q19_12 D_800AE73C = FP_TIME(-524256.0f);

// Used by `func_80068CC0` and `GameState_MapScreen_Update`.
// I think this is save file flags related to
// placing the markings on the map.
u8 D_800AE740[] =
{
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x06, 0x00,
    0x07, 0x05, 0x08, 0x06,
    0x00, 0x07, 0x0A, 0x00,
    0x0B, 0x09, 0x0C, 0x0A,
    0x00, 0x0B, 0x0E, 0x00,
    0x00, 0x0D, 0x00, 0x00,
    0x11, 0x00, 0x12, 0x10,
    0x13, 0x11, 0x00, 0x12,
    0x15, 0x00, 0x16, 0x14,
    0x17, 0x15, 0x00, 0x16,
};

s32 D_800AE770 = 0; // `GameState_MapScreen_Update` uses this like a `bool`.

// `D_800AE774`. `D_800AE7E4`, `D_800AE820` are used by `func_80067914`. Might one big table.
// Seems like a pair of bytes `(->unk0, ->unk1)`
u8 D_800AE774[112] =
{
    0x00, 0x00, 0x00, 0x00, 0xD5, 0x5A, 0xD0, 0x48,
    0xCD, 0x2A, 0xD0, 0xE0, 0xD1, 0x44, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0x52, 0xDF, 0xFE, 0xF8, 0xB0,
    0x40, 0xB0, 0x00, 0x00, 0x00, 0x00, 0xDC, 0xB6,
    0x48, 0x50, 0x25, 0x01, 0x1C, 0xB0, 0x68, 0xB5,
    0x00, 0x00, 0x1F, 0xFD, 0x21, 0xD5, 0x20, 0x38,
    0x70, 0x20, 0x70, 0xE0, 0x00, 0x00, 0x36, 0x01,
    0x42, 0x64, 0x41, 0x41, 0xD0, 0x58, 0xD0, 0x48,
    0xD5, 0x25, 0xD0, 0xE0, 0x00, 0x00, 0x40, 0x41,
    0x6F, 0x4D, 0x04, 0x53, 0xE4, 0xFE, 0x00, 0x00,
    0x44, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x50, 0x2F, 0x01, 0xFC, 0xAE, 0x20, 0xB0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x38,
    0x6B, 0x20, 0x75, 0xE0, 0x59, 0xB0, 0x40, 0x01
};

u8 D_800AE7E4[60] =
{
    0x00, 0x00, 0x3C, 0xAD, 0x57, 0xAF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0xDC,
    0x44, 0xED, 0x66, 0xFF, 0x00, 0x00, 0xCB, 0xE7,
    0x00, 0x00, 0x3B, 0xD8, 0x6F, 0xAC, 0x68, 0x29,
    0x20, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x66, 0xCF, 0x66, 0x45, 0x01, 0x06, 0x00, 0x00,
    0x00, 0x00, 0x68, 0xE7, 0x68, 0xE8, 0x00, 0x00,
    0xF6, 0xD7, 0x00, 0x00
};

u8 D_800AE820[128] =
{
    0x00, 0x00, 0x20, 0x0B, 0xD8, 0x30, 0xFB, 0x48,
    0x3E, 0x47, 0xD9, 0xC2, 0x44, 0xBE, 0x00, 0x00,
    0x00, 0x00, 0x44, 0xBE, 0xD8, 0xBE, 0x00, 0x00,
    0x62, 0x4F, 0xDD, 0xFD, 0x3C, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x44, 0x26, 0xD8, 0xF4, 0x38, 0x4E,
    0x6E, 0x18, 0x00, 0x00, 0x0E, 0xF3, 0x00, 0x00,
    0x00, 0x00, 0xFC, 0xEF, 0xD8, 0x0D, 0x68, 0xEE,
    0x6D, 0xCB, 0x00, 0x00, 0xD2, 0x42, 0x20, 0x0C,
    0x00, 0x00, 0x00, 0x00, 0x1F, 0xBE, 0x20, 0x0C,
    0xF6, 0x30, 0x6E, 0xAD, 0x00, 0x00, 0x1F, 0x0A,
    0x00, 0x00, 0x00, 0x00, 0x3B, 0xD9, 0x20, 0xE8,
    0x00, 0x00, 0x74, 0xD0, 0x00, 0x00, 0x01, 0x07,
    0x00, 0x00, 0x00, 0x00, 0x62, 0xDB, 0x00, 0x00,
    0x00, 0x00, 0x68, 0xE8, 0x44, 0x47, 0xCC, 0xE8,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0xE9,
    0x44, 0xE8, 0x65, 0xFB, 0x29, 0x56, 0x00, 0x00
};

u32 D_800AE8A0[327] =
{
    0x00000000, 0x1F0F0000, 0x1F0F0010, 0x1F0F0020,
    0x1F0F0030, 0x1F0F0040, 0x1F0F0050, 0x1F0F0060,
    0x2F1F7050, 0x1F1F2020, 0x1F1F2040, 0x3F1F4000,
    0x2F0F4020, 0x5F4F8000, 0x2F1F4050, 0x1F1F2060,
    0x5F0F4070, 0x3F1FA050, 0x00018E07, 0x0004E20A,
    0x0005E90C, 0x000EBEF8, 0x0001BDDF, 0x0001ADCA,
    0x0001DDC1, 0x00016ACA, 0x00015CDD, 0x00015C00,
    0x00013606, 0x00014324, 0x000D4703, 0x00010F24,
    0x00010E07, 0x0001BC37, 0x000120DE, 0x00011AE8,
    0x000122EF, 0x000137E8, 0x000B20E2, 0x0001F9DD,
    0x0009DFDB, 0x000944DB, 0x000FBB25, 0x0010C715,
    0x0011001F, 0x0601203C, 0x000A1339, 0x03022B0D,
    0x000029C4, 0x03024EBD, 0x000844DB, 0x0007E0DF,
    0x00000000, 0x1F3F8000, 0x3F1F4030, 0x1F1F4050,
    0x3F1F4000, 0x1F0F0000, 0x1F0F0010, 0x1F0F0020,
    0x1F0F0040, 0x0001962C, 0x00065BF0, 0x0002CCE4,
    0x000369E4, 0x0002F232, 0x00024131, 0x00038820,
    0x0001962C, 0x00065BF0, 0x0002CAE4, 0x000369E4,
    0x00038820, 0x0005D124, 0x00052224, 0x00051C06,
    0x00023FF9, 0x0002F245, 0x0002EFCE, 0x0002A13C,
    0x00050442, 0x000088B0, 0x00023EE8, 0x00059710,
    0x0002AC2C, 0x000509F1, 0x00050FEA, 0x0002EDC0,
    0x0005F300, 0x07064DE1, 0x0008EAC8, 0x00000000,
    0x1F0F0000, 0x1F0F0010, 0x1F0F0020, 0x1F0F0030,
    0x1F0F0040, 0x1F0F0050, 0x1F0F0060, 0x1F1F2000,
    0x1F1F2020, 0x1F0F2050, 0x1F0F2040, 0x1F0F2060,
    0x1F1F4000, 0x04025224, 0x04003824, 0x0300580C,
    0x0300380C, 0x040B30F4, 0x030144F6, 0x03003817,
    0x0301200C, 0x040B3024, 0x040BC024, 0x0001B826,
    0x0402BE2C, 0x0402F22C, 0x0402FE2C, 0x0402322C,
    0x0300F839, 0x0300D00C, 0x0001B817, 0x0300B80C,
    0x0001B8F9, 0x0400C0F4, 0x0001980C, 0x0002BDEC,
    0x0002F1EC, 0x0002FEEC, 0x000231EC, 0x040044EC,
    0x040054EC, 0x00073CFE, 0x00061C1E, 0x000230F4,
    0x0002C024, 0x0001580C, 0x0300380C, 0x040B30F4,
    0x030044F6, 0x03003816, 0x030A200C, 0x04003024,
    0x040BC024, 0x0300B826, 0x0400BE2C, 0x0400F22C,
    0x0402FE2C, 0x0400322C, 0x0300F839, 0x0300D00C,
    0x0300B817, 0x0300B80C, 0x0300B8F9, 0x040BC0F4,
    0x0400BDEC, 0x0002F1EC, 0x0400FEEC, 0x040031EC,
    0x040044EC, 0x040054EC, 0x0300F8DF, 0x0001F8F0,
    0x0001F828, 0x030A3828, 0x0007F80C, 0x00059C0C,
    0x040B4EF4, 0x000C3928, 0x040B30F4, 0x030038F7,
    0x03003817, 0x04023024, 0x0402C024, 0x0301B827,
    0x0402BE2C, 0x0402F22C, 0x0402FE2C, 0x0402322C,
    0x0300F83A, 0x030AB821, 0x0300B800, 0x0300B8FA,
    0x0400C0F4, 0x0400BEEC, 0x0400F2EC, 0x0400FEEC,
    0x040032EC, 0x0300F8DF, 0x040044EC, 0x040054EC,
    0x04009E24, 0x0009AF08, 0x000854F8, 0x0007441E,
    0x040030F4, 0x000138F7, 0x03003817, 0x040B3024,
    0x040BC024, 0x0300B828, 0x040BBE2C, 0x040BF22C,
    0x0400FE2C, 0x0400322C, 0x0300F83A, 0x030AB821,
    0x0001B801, 0x0001B8FB, 0x0400C0F4, 0x0400BEEC,
    0x0400F2EC, 0x0400FEEC, 0x040032EC, 0x0300F8DF,
    0x040044EC, 0x040054EC, 0x0001F8F0, 0x000138F0,
    0x0001F828, 0x04009E24, 0x0402A0F3, 0x000DA922,
    0x00000000, 0x0F070040, 0x0F070038, 0x0F070010,
    0x0F070018, 0x2F1F1000, 0x0301240C, 0x0402C32E,
    0x0402B72E, 0x0301CB2F, 0x04022336, 0x04022322,
    0x040224FE, 0x04022DE6, 0x000509DC, 0x0005E528,
    0x00000000, 0x1F0F0000, 0x1F0F0010, 0x1F0F0020,
    0x1F0F0030, 0x1F0F0040, 0x1F0F0050, 0x1F0F0060,
    0x1F0F2050, 0x1F0F2040, 0x1F1F2000, 0x000110E1,
    0x0400F3E8, 0x0300C8F7, 0x0300E1EB, 0x0400FF00,
    0x03001014, 0x00012812, 0x0001281E, 0x0300342D,
    0x04021C24, 0x0402FE24, 0x0402E524, 0x0409C324,
    0x0002C324, 0x00021D0C, 0x0402A018, 0x000110E1,
    0x0400F3E8, 0x0001E1EB, 0x0409FF00, 0x03011014,
    0x03002812, 0x0300281E, 0x00021C24, 0x0400FE24,
    0x0400E524, 0x0400C324, 0x04001D0C, 0x0002A018,
    0x000128FC, 0x00012804, 0x0400CD24, 0x0002B018,
    0x0002DB18, 0x0400E624, 0x0002FE24, 0x0400CD24,
    0x0400B018, 0x0409DB18, 0x0400E624, 0x0002FE24,
    0x0001BC1E, 0x0308BC1E, 0x0400C324, 0x0002E624,
    0x04000D24, 0x03002818, 0x04004024, 0x03081015,
    0x04091D0C, 0x00012804, 0x000128FC, 0x04001DF4,
    0x040008F4, 0x0002EFF4, 0x0002DCF4, 0x0400C0F4,
    0x0400FF00, 0x0001BC1E, 0x0308BC1E, 0x0002C324,
    0x0400DC24, 0x00020C24, 0x03002818, 0x00024024,
    0x03001015, 0x04001C0C, 0x030028FC, 0x00012803,
    0x04001DF4, 0x040009F4, 0x0400F1F4, 0x0002DCF4,
    0x0400C0F4, 0x04000000, 0x000AE5E0
};

// Used by `func_80068E0C`. Contains pointers to the table above.
typedef struct
{
    u32* ptr_0;
    u32* ptr_4;
    s16  field_8;
    s16  field_A;
} s_800AEDBC;
s_800AEDBC D_800AEDBC[] =
{
    {},
    { &D_800AE8A0[0x00], &D_800AE8A0[0x12], 0x0363, 0x03A8 },
    { &D_800AE8A0[0x34], &D_800AE8A0[0x3D], 0x03AF, 0x03BE },
    { &D_800AE8A0[0x34], &D_800AE8A0[0x44], 0x03D1, 0x03F0 },
    { &D_800AE8A0[0x34], &D_800AE8A0[0x53], 0x03F3, 0x0404 },
    { &D_800AE8A0[0x5B], &D_800AE8A0[0x69], 0x0415, 0x041A },
    { &D_800AE8A0[0x5B], &D_800AE8A0[0x6B], 0x0429, 0x0466 },
    { &D_800AE8A0[0x5B], &D_800AE8A0[0xAA], 0x04C5, 0x04FA },
    { &D_800AE8A0[0x5B], &D_800AE8A0[0xDE], 0x0549, 0x054E },
    { &D_800AE8A0[0x5B], &D_800AE8A0[0x69], 0x041F, 0x0424 },
    { &D_800AE8A0[0x5B], &D_800AE8A0[0x89], 0x0477, 0x04BA },
    { &D_800AE8A0[0x5B], &D_800AE8A0[0xC4], 0x0507, 0x053C },
    { &D_800AE8A0[0x5B], &D_800AE8A0[0xDE], 0x0551, 0x0556 },
    { &D_800AE8A0[0xE0], &D_800AE8A0[0xE6], 0x0559, 0x0562 },
    { &D_800AE8A0[0xE0], &D_800AE8A0[0xEA], 0x056D, 0x0578 },
    { &D_800AE8A0[0xE0], &D_800AE8A0[0xEf], 0x0585, 0x0588 },
    { &D_800AE8A0[0xF0], &D_800AE8A0[0x11A],0x05E7, 0x05F2 },
    { &D_800AE8A0[0xF0], &D_800AE8A0[0xFB], 0x058F, 0x05B0 },
    { &D_800AE8A0[0xF0], &D_800AE8A0[0x124],0x060F, 0x0612 },
    { &D_800AE8A0[0xF0], &D_800AE8A0[0x135],0x0615, 0x0618 },
    { &D_800AE8A0[0xF0], &D_800AE8A0[0x11f],0x05FB, 0x0606 },
    { &D_800AE8A0[0xF0], &D_800AE8A0[0x10B],0x05BB, 0x05DA },
    { &D_800AE8A0[0xF0], &D_800AE8A0[0x125],0x061B, 0x063C },
    { &D_800AE8A0[0xF0], &D_800AE8A0[0x136],0x0649, 0x066C },
};

s16 D_800AEEDC[][2] =
{
    { 0xE667, 0xEE67 },
    { 0xE667, 0xEE67 },
    { 0xE667, 0xEE67 },
    { 0xE667, 0xEE67 },
    { 0xE667, 0xEE67 },
    { 0xE667, 0xEE67 },
    { 0xE667, 0xEE67 },
    { 0xE6B9, 0xEE67 },
    { 0xE70B, 0xEEB9 },
    { 0xE75D, 0xEEB9 },
    { 0xE7AF, 0xEEB9 },
    { 0xE800, 0xEFAF },
    { 0xE8F6, 0xF052 },
    { 0xEA15, 0xF052 },
    { 0xEB34, 0xF11F },
    { 0xEF34, 0xF59A },
    { 0xF0F6, 0xF667 },
    { 0xF47B, 0xF800 },
    { 0xF571, 0xF8A4 },
    { 0xF5C3, 0xF948 },
    { 0xF615, 0xF99A },
    { 0xF6E2, 0xFA3E },
    { 0xF734, 0xFAE2 },
    { 0xF734, 0xFA3E },
    { 0xF615, 0xF91F },
    { 0xF59A, 0xF800 },
    { 0xF452, 0xF70B },
    { 0xF3D8, 0xF667 },
    { 0xF2E2, 0xF5C3 },
    { 0xF2E2, 0xF5C3 },
    { 0xF23E, 0xF4A4 },
    { 0xF148, 0xF429 },
    { 0xF000, 0xF334 },
    { 0xED71, 0xF215 },
    { 0xEA90, 0xF0F6 },
    { 0xE8F6, 0xF07B },
    { 0xE7AF, 0xEFD8 },
    { 0xE6E2, 0xEF86 },
    { 0xE667, 0xEE67 },
};

s16 D_800AEF78[][2] =
{
    { 0xE667, 0xEE67 },
    { 0xE667, 0xEE67 },
    { 0xE6B9, 0xEEE2 },
    { 0xE948, 0xF029 },
    { 0xE948, 0xF052 },
    { 0xE829, 0xEF86 },
    { 0xE99A, 0xEFAF },
    { 0xE9EC, 0xF052 },
    { 0xED1F, 0xF400 },
    { 0xF0F6, 0xF829 },
    { 0xF2E2, 0xF99A },
    { 0xF47B, 0xFA15 },
    { 0xF571, 0xFA90 },
    { 0xF571, 0xFA90 },
    { 0xF75D, 0xFB34 },
    { 0xF75D, 0xFB86 },
    { 0xF75D, 0xFB86 },
    { 0xF800, 0xFC00 },
    { 0xF852, 0xFC00 },
    { 0xF852, 0xFC00 },
    { 0xF667, 0xFBD8 },
    { 0xF4F6, 0xFB86 },
    { 0xF3D8, 0xFAB9 },
    { 0xF290, 0xFA15 },
    { 0xF215, 0xFA15 },
    { 0xF148, 0xF9C3 },
    { 0xF07B, 0xF852 },
    { 0xEDEC, 0xF548 },
    { 0xEC7B, 0xF400 },
    { 0xE91F, 0xF0F6 },
    { 0xE70B, 0xEFD8 },
    { 0xE6B9, 0xEEB9 },
    { 0xE667, 0xEE67 },
    { 0xE667, 0xEE67 },
    { 0xE667, 0xEE67 },
    { 0xE667, 0xEE67 },
    { 0xE667, 0xEE67 },
    { 0xE667, 0xEE67 },
    { 0xE667, 0xEE67 },
};
s16 D_800AF014[] =
{
    0x0000, 0x0000, 0xFFD8, 0xFFAF,
    0xFF86, 0xFF5D, 0xFF0B, 0xFEB9,
    0xFE67, 0xFE15, 0xFDC3, 0xFD71,
    0xFD1F, 0xFCCD, 0xFC7B, 0xFCCD,
    0xFD1F, 0xFD71, 0xFDC3, 0xFE67,
    0xFEB9, 0xFF0B, 0xFF5D, 0xFF86,
    0xFFAF, 0xFFD8, 0x0000, 0x0000,
};

s16 D_800AF04C[] =
{
    0x0000, 0x0000, 0xFFD8, 0xFF86,
    0xFF34, 0xFEE2, 0xFE90, 0xFE3E,
    0xFDEC, 0xFD9A, 0xFD48, 0xFD1F,
    0xFD48, 0xFD9A, 0xFE15, 0xFEB9,
    0xFF5D, 0x0000
};

s16 D_800AF070[] =
{
    0x0000, 0x00A3, 0x0147, 0x01EB,
    0x028F, 0x0333, 0x03D7, 0x047A,
    0x051E, 0x05C2, 0x0666, 0x070A,
    0x07AE, 0x0851, 0x08F5, 0x0999,
    0x0A3D, 0x0AE1, 0x0B85, 0x0C28,
    0x0CCC, 0x0D70, 0x0E14, 0x0EB8,
    0x0F5C, 0x1000, 0x10A3, 0x1147,
    0x11EB, 0x128F, 0x1333, 0x13D7,
    0x147A, 0x151E, 0x15C2, 0x1666,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0xFFD8, 0xFEB9, 0xFD9A,
    0xFCCD, 0xFC52, 0xFBD8, 0xFB5D,
    0xFB5D, 0xFB5D, 0xFB5D, 0xFB5D,
    0xFB5D, 0xFB5D, 0xFB5D, 0xFB5D,
    0xFB5D, 0xFB5D, 0xFB5D, 0xFB5D,
    0xFB5D, 0xFB5D, 0xFA90, 0xFA67,
    0xFA67, 0xFA90, 0xFA90, 0xFAB9,
    0xFAB9, 0xFAB9, 0xFAE2, 0xFAE2,
    0xFB0B, 0xFB5D, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0xFF34, 0xFE3E, 0xFD9A, 0xFCCD,
    0xFC00, 0xFB34, 0xFB34, 0xFBAF,
    0xFC29, 0xFCA4, 0xFD1F, 0xFD9A,
    0xFE15, 0xFE90, 0xFF0B, 0xFF86,
    0x0000, 0x007A, 0x011E, 0x0000,
    0xFFAF, 0xFF86, 0xFF86, 0xFFAF,
    0xFFD8, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x04CC, 0x04CC, 0x04CC, 0x04CC,
    0x04CC, 0x04CC, 0x04CC, 0x04CC,
    0x04CC, 0x04CC, 0x04CC, 0x04CC,
    0x04CC, 0x04CC, 0x04CC, 0x04CC,
    0x051E, 0x0547, 0x0570, 0x0599,
    0x05C2, 0x05EB, 0x0614, 0x063D,
    0x0666, 0x0666, 0x0666, 0x0666,
    0x0666, 0x0666, 0x0666, 0x0666,
    0x0666, 0x0666, 0x0666, 0x0666,
    0x0666, 0x0666, 0x0666, 0x0666,
    0x0666, 0x0666, 0x04CC, 0x04CC,
    0x04CC, 0x04CC, 0x04CC, 0x04CC,
    0x04CC, 0x04CC, 0x04CC, 0x04CC,
    0x04CC, 0x0000
};

s16 D_800AF1FC[] =
{
    0x0147, 0x028F, 0x03D7, 0x051E,
    0x0666, 0x07AE, 0x07AE, 0x0000,
};

s32 g_Player_GrabFree_InputCount = 0;
s16 D_800AF210 = 0;
s16 D_800AF212 = 0;
u8 g_Player_IsInWalkToRunTransition = 0;
u8 g_Player_DisableControl = 0;
u8 D_800AF216 = 0;
s8 g_Player_RockDrill_DirectionAttack = 0;
u32 D_800AF218 = 0;
s32 D_800AF21C = NO_VALUE;
u8 D_800AF220 = 0;
// 3 bytes of padding.
s32 D_800AF224 = NO_VALUE;

s32 func_800706E4(); // This function is used in the table below. It's nearly completely matched https://decomp.me/scratch/PBvwU.
s_AnimInfo HARRY_BASE_ANIM_INFOS[57] =
{
    { Anim_Update2, ANIM_STATUS(PlayerAnim_Unk0,                    false), false, ANIM_STATUS(PlayerAnim_Unk0,                    true), 0, { FP_TIME(10.0f) }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(PlayerAnim_Unk0,                    true),  false, NO_VALUE,                                              0, { FP_TIME(30.0f) }, NO_VALUE, 1   },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_Unk1,                    false), false, ANIM_STATUS(PlayerAnim_Unk1,                    true), 0, { FP_TIME(10.0f) }, NO_VALUE, 0   },
    { Anim_Update1, ANIM_STATUS(PlayerAnim_Unk1,                    true),  false, NO_VALUE,                                              0, { FP_TIME(0.0f)  }, 0,        0   },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_WalkForward,             false), false, ANIM_STATUS(PlayerAnim_WalkForward,             true), 0, { FP_TIME(50.0f) }, NO_VALUE, 1   },
    { Anim_Update1, ANIM_STATUS(PlayerAnim_WalkForward,             true),  true,  NO_VALUE,                                              0, { func_800706E4  }, 1,        23  },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_RunForward,              false), false, ANIM_STATUS(PlayerAnim_RunForward,              true), 0, { FP_TIME(20.0f) }, NO_VALUE, 26  },
    { Anim_Update1, ANIM_STATUS(PlayerAnim_RunForward,              true),  true,  NO_VALUE,                                              0, { func_800706E4  }, 26,       45  },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_WalkBackward,            false), false, ANIM_STATUS(PlayerAnim_WalkBackward,            true), 0, { FP_TIME(20.0f) }, NO_VALUE, 46  },
    { Anim_Update1, ANIM_STATUS(PlayerAnim_WalkBackward,            true),  true,  NO_VALUE,                                              0, { func_800706E4  }, 46,       69  },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_SidestepLeft,            false), false, ANIM_STATUS(PlayerAnim_SidestepLeft,            true), 0, { FP_TIME(50.0f) }, NO_VALUE, 70  },
    { Anim_Update1, ANIM_STATUS(PlayerAnim_SidestepLeft,            true),  false, NO_VALUE,                                              0, { FP_TIME(30.0f) }, 70,       94  },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_SidestepRight,           false), false, ANIM_STATUS(PlayerAnim_SidestepRight,           true), 0, { FP_TIME(50.0f) }, NO_VALUE, 95  },
    { Anim_Update1, ANIM_STATUS(PlayerAnim_SidestepRight,           true),  false, NO_VALUE,                                              0, { FP_TIME(30.0f) }, 95,       119 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_RunLeft,                 false), false, ANIM_STATUS(PlayerAnim_RunLeft,                 true), 0, { FP_TIME(20.0f) }, NO_VALUE, 121 },
    { Anim_Update1, ANIM_STATUS(PlayerAnim_RunLeft,                 true),  false, NO_VALUE,                                              0, { FP_TIME(20.0f) }, 121,      133 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_RunRight,                false), false, ANIM_STATUS(PlayerAnim_RunRight,                true), 0, { FP_TIME(20.0f) }, NO_VALUE, 136 },
    { Anim_Update1, ANIM_STATUS(PlayerAnim_RunRight,                true),  false, NO_VALUE,                                              0, { FP_TIME(20.0f) }, 136,      148 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_RunForwardWallStopRight, false), false, ANIM_STATUS(PlayerAnim_RunForwardWallStopRight, true), 0, { FP_TIME(50.0f) }, NO_VALUE, 150 },
    { Anim_Update0, ANIM_STATUS(PlayerAnim_RunForwardWallStopRight, true),  false, ANIM_STATUS(PlayerAnim_RunForwardWallStopRight, true), 0, { FP_TIME(15.0f) }, 150,      159 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_RunForwardWallStopLeft,  false), false, ANIM_STATUS(PlayerAnim_RunForwardWallStopLeft,  true), 0, { FP_TIME(50.0f) }, NO_VALUE, 160 },
    { Anim_Update0, ANIM_STATUS(PlayerAnim_RunForwardWallStopLeft,  true),  false, ANIM_STATUS(PlayerAnim_RunForwardWallStopLeft,  true), 0, { FP_TIME(15.0f) }, 160,      169 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_RunForwardStumble,       false), false, ANIM_STATUS(PlayerAnim_RunForwardStumble,       true), 0, { FP_TIME(50.0f) }, NO_VALUE, 170 },
    { Anim_Update0, ANIM_STATUS(PlayerAnim_RunForwardStumble,       true),  false, ANIM_STATUS(PlayerAnim_RunForwardStumble,       true), 0, { FP_TIME(15.0f) }, 170,      179 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_TurnLeft,                false), false, ANIM_STATUS(PlayerAnim_TurnLeft,                true), 0, { FP_TIME(50.0f) }, NO_VALUE, 180 },
    { Anim_Update1, ANIM_STATUS(PlayerAnim_TurnLeft,                true),  false, NO_VALUE,                                              0, { FP_TIME(15.0f) }, 180,      192 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_TurnRight,               false), false, ANIM_STATUS(PlayerAnim_TurnRight,               true), 0, { FP_TIME(50.0f) }, NO_VALUE, 193 },
    { Anim_Update1, ANIM_STATUS(PlayerAnim_TurnRight,               true),  false, NO_VALUE,                                              0, { FP_TIME(15.0f) }, 193,      205 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_QuickTurnRight,          false), false, ANIM_STATUS(PlayerAnim_QuickTurnRight,          true), 0, { FP_TIME(50.0f) }, NO_VALUE, 206 },
    { Anim_Update0, ANIM_STATUS(PlayerAnim_QuickTurnRight,          true),  false, ANIM_STATUS(PlayerAnim_QuickTurnRight,          true), 0, { FP_TIME(28.0f) }, 206,      217 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_QuickTurnLeft,           false), false, ANIM_STATUS(PlayerAnim_QuickTurnLeft,           true), 0, { FP_TIME(50.0f) }, NO_VALUE, 219 },
    { Anim_Update0, ANIM_STATUS(PlayerAnim_QuickTurnLeft,           true),  false, ANIM_STATUS(PlayerAnim_QuickTurnLeft,           true), 0, { FP_TIME(28.0f) }, 219,      230 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_JumpBackward,            false), false, ANIM_STATUS(PlayerAnim_JumpBackward,            true), 0, { FP_TIME(10.0f) }, NO_VALUE, 240 },
    { Anim_Update0, ANIM_STATUS(PlayerAnim_JumpBackward,            true),  false, ANIM_STATUS(PlayerAnim_JumpBackward,            true), 0, { FP_TIME(10.0f) }, 240,      247 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_LookAround,              false), false, ANIM_STATUS(PlayerAnim_LookAround,              true), 0, { FP_TIME(50.0f) }, NO_VALUE, 248 },
    { Anim_Update1, ANIM_STATUS(PlayerAnim_LookAround,              true),  false, NO_VALUE,                                              0, { FP_TIME(7.0f)  }, 248,      320 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_RunLeftWallStop,         false), false, ANIM_STATUS(PlayerAnim_RunLeftWallStop,         true), 0, { FP_TIME(50.0f) }, NO_VALUE, 321 },
    { Anim_Update0, ANIM_STATUS(PlayerAnim_RunLeftWallStop,         true),  false, ANIM_STATUS(PlayerAnim_RunLeftWallStop,         true), 0, { FP_TIME(20.0f) }, 321,      336 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_RunLeftStumble,          false), false, ANIM_STATUS(PlayerAnim_RunLeftStumble,          true), 0, { FP_TIME(50.0f) }, NO_VALUE, 337 },
    { Anim_Update0, ANIM_STATUS(PlayerAnim_RunLeftStumble,          true),  false, ANIM_STATUS(PlayerAnim_RunLeftStumble,          true), 0, { FP_TIME(15.0f) }, 337,      349 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_RunRightWallStop,        false), false, ANIM_STATUS(PlayerAnim_RunRightWallStop,        true), 0, { FP_TIME(50.0f) }, NO_VALUE, 350 },
    { Anim_Update0, ANIM_STATUS(PlayerAnim_RunRightWallStop,        true),  false, ANIM_STATUS(PlayerAnim_RunRightWallStop,        true), 0, { FP_TIME(20.0f) }, 350,      365 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_RunRightStumble,         false), false, ANIM_STATUS(PlayerAnim_RunRightStumble,         true), 0, { FP_TIME(50.0f) }, NO_VALUE, 366 },
    { Anim_Update0, ANIM_STATUS(PlayerAnim_RunRightStumble,         true),  false, ANIM_STATUS(PlayerAnim_RunRightStumble,         true), 0, { FP_TIME(15.0f) }, 366,      378 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_FallForward,             false), false, ANIM_STATUS(PlayerAnim_FallForward,             true), 0, { FP_TIME(30.0f) }, NO_VALUE, 387 },
    { Anim_Update0, ANIM_STATUS(PlayerAnim_FallForward,             true),  false, ANIM_STATUS(PlayerAnim_FallForward,             true), 0, { FP_TIME(20.0f) }, 387,      417 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_FallBackward,            false), false, ANIM_STATUS(PlayerAnim_FallBackward,            true), 0, { FP_TIME(30.0f) }, NO_VALUE, 418 },
    { Anim_Update0, ANIM_STATUS(PlayerAnim_FallBackward,            true),  false, ANIM_STATUS(PlayerAnim_FallBackward,            true), 0, { FP_TIME(20.0f) }, 418,      456 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_Kick,                    false), false, ANIM_STATUS(PlayerAnim_Kick,                    true), 0, { FP_TIME(5.0f)  }, NO_VALUE, 457 },
    { Anim_Update0, ANIM_STATUS(PlayerAnim_Kick,                    true),  false, ANIM_STATUS(PlayerAnim_Kick,                    true), 0, { FP_TIME(20.0f) }, 457,      484 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_Stomp,                   false), false, ANIM_STATUS(PlayerAnim_Stomp,                   true), 0, { FP_TIME(5.0f)  }, NO_VALUE, 485 },
    { Anim_Update0, ANIM_STATUS(PlayerAnim_Stomp,                   true),  false, ANIM_STATUS(PlayerAnim_Stomp,                   true), 0, { FP_TIME(20.0f) }, 485,      502 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_Idle,                    false), false, ANIM_STATUS(PlayerAnim_Idle,                    true), 0, { FP_TIME(5.0f)  }, NO_VALUE, 503 },
    { Anim_Update1, ANIM_STATUS(PlayerAnim_Idle,                    true),  false, NO_VALUE,                                              0, { FP_TIME(10.0f) }, 503,      542 },
    { Anim_Update2, ANIM_STATUS(PlayerAnim_IdleTired,               false), false, ANIM_STATUS(PlayerAnim_IdleTired,               true), 0, { FP_TIME(5.0f)  }, NO_VALUE, 543 },
    { Anim_Update1, ANIM_STATUS(PlayerAnim_IdleTired,               true),  true,  NO_VALUE,                                              0, { func_800706E4  }, 543,      567 },
    {} // End of list.
};
u8 __padding1[14] = {};
s16 D_800AF5C6 = 0;
u32 D_800AF5C8[23] = {}; // Padding?
s16 D_800AF624 = 0;
s16 D_800AF626 = 0;
u32 D_800AF628[368] = {};
s32 g_Player_AttackAnimIdx = 0;
s32 g_Player_MeleeAttackType = 0;
s32 g_Player_IsMultiTapAttack = 0;

s_800AFBF4 D_800AFBF4[11] =
{
    {},
    { 1293, 0,    0,    64, 62, 63, 0,  52, 0 },
    { 1294, 0,    0,    64, 62, 63, 0,  52, 0 },
    { 1295, 0,    0,    64, 62, 63, 0,  52, 0 },
    { 1301, 0,    0,    64, 62, 63, 0,  52, 0 },
    { 1303, 0,    0,    64, 58, 59, 0,  20, 0 },
    { 1283, 1284, 1285, 66, 72, 61, 37, 37, 0 },
    { 1290, 1291, 1292, 66, 72, 61, 24, 37, 0 },
    { 1287, 1288, 1289, 66, 72, 61, 23, 37, 0 },
    { 1299, 0,    0,    66, 72, 61, 0,  37, 0 },
    { 1298, 0,    0,    64, 62, 63, 0,  52, 0 }
};

s_800AFC78 D_800AFC78 =
{
    .position_0 = {},
    .field_C = {},
    .field_18 = NO_VALUE
};

void Inventory_DirectionalInputSet() // 0x8004F5DC
{
    if (g_Controller0->sticks_20.sticks_0.leftY < -64 || g_Controller0->sticks_20.sticks_0.leftY >= 64 ||
        g_Controller0->sticks_20.sticks_0.leftX < -64 || g_Controller0->sticks_20.sticks_0.leftX >= 64)
    {
        // Up.
        g_Inventory_IsUpClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickUp2;
        g_Inventory_IsUpPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickUp2;

        // Down.
        g_Inventory_IsDownClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickDown2;
        g_Inventory_IsDownPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickDown2;

        // Left.
        g_Inventory_IsLeftClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickLeft2;
        g_Inventory_IsLeftHeld    = g_Controller0->btnsHeld_C     & ControllerFlag_LStickLeft2;
        g_Inventory_IsLeftPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickLeft2;

        // Right.
        g_Inventory_IsRightClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickRight2;
        g_Inventory_IsRightHeld    = g_Controller0->btnsHeld_C     & ControllerFlag_LStickRight2;
        g_Inventory_IsRightPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickRight2;
    }
    else
    {
        // Up.
        g_Inventory_IsUpClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickUp;
        g_Inventory_IsUpPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickUp;

        // Down.
        g_Inventory_IsDownClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickDown;
        g_Inventory_IsDownPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickDown;

        // Left.
        g_Inventory_IsLeftClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickLeft;
        g_Inventory_IsLeftHeld    = g_Controller0->btnsHeld_C     & ControllerFlag_LStickLeft;
        g_Inventory_IsLeftPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickLeft;

        // Right.
        g_Inventory_IsRightClicked = g_Controller0->btnsClicked_10 & ControllerFlag_LStickRight;
        g_Inventory_IsRightHeld    = g_Controller0->btnsHeld_C     & ControllerFlag_LStickRight;
        g_Inventory_IsRightPulsed  = g_Controller0->btnsPulsed_18  & ControllerFlag_LStickRight;
    }
}

void Gfx_ItemScreens_RenderInit(u32* selectedItemId) // 0x8004F764
{
    GsDOBJ2* ptr;
    s32      i;

    DVECTOR strPosTable[] = // 0x80027DD8
    {
        { 118, -80 },
        { 144, 304 },
        { 36, 304 },
        { 240, 304 }, 
        { 218, -80 },
        { 40, -80 },
        { 16, 184 },
        { 16, 200 }
    };

    char* strs[] = // 0x80027E34
    {
        "Equipment",
        "Exit",
        "Option",
        "Map",
        "Command",
        "Status",
        "No.",
        "Name:"
    };

    Gfx_StringSetColor(ColorId_White);

    // In inventory.
    if (g_GameWork.gameStateStep_598[1] < 21)
    {
        for (i = 0; i < 8; i++)
        {
            Gfx_StringSetPosition(strPosTable[i].vx, strPosTable[i].vy);
            Gfx_StringDraw(strs[i], 10);
        }

        Inventory_PlayerItemScroll(selectedItemId);

        // Player items.
        for (i = 0, ptr = &g_Items_ItemsModelData[0]; i < 7; i++, ptr++)
        {
            if (D_800C3E18[i] != NO_VALUE)
            {
                if (g_SavegamePtr->items_0[D_800C3E18[i]].id_0 != 0xFF)
                {
                    g_Items_Items3dData0[i].rotation_10.vx = g_InventoryItemRotations[g_SavegamePtr->items_0[D_800C3E18[i]].id_0 - 32].vx;
                    g_Items_Items3dData0[i].rotation_10.vz = g_InventoryItemRotations[g_SavegamePtr->items_0[D_800C3E18[i]].id_0 - 32].vy;

                    Gfx_Items_ItemRotate(&g_Items_Items3dData1[i].param->rotate, &g_Items_Items3dData1[i]);
                    func_800548D8(i);
                    GsSetFlatLight(0, &g_Items_ItemsLightingData[i][0]);
                    GsSetFlatLight(1, &g_Items_ItemsLightingData[i][1]);
                    func_8004BD74(i, ptr, 0);
                }
            }
        }

        // Equipped item.
        if (g_SavegamePtr->items_0[g_Inventory_EquippedItemIdx].id_0 != 0xFF && g_Inventory_EquippedItemIdx != NO_VALUE)
        {
            g_Items_Items3dData0[7].rotation_10.vx = g_InventoryItemRotations[g_SavegamePtr->items_0[g_Inventory_EquippedItemIdx].id_0 - 32].vx;
            g_Items_Items3dData0[7].rotation_10.vz = g_InventoryItemRotations[g_SavegamePtr->items_0[g_Inventory_EquippedItemIdx].id_0 - 32].vy;

            Gfx_Items_ItemRotate(&g_Items_Items3dData1[7].param->rotate, &g_Items_Items3dData1[7]);
            func_800548D8(7);
            GsSetFlatLight(0, &D_800C3A88[0]);
            GsSetFlatLight(1, &D_800C3A88[1]);
            func_8004BD74(7, ptr, 0);
        }

        Gfx_Inventory_ItemDescriptionDraw(selectedItemId);
        Gfx_Inventory_2dBackgroundDraw(selectedItemId);
    }
    else
    {
        Gfx_Results_ItemsPosition(g_SavegamePtr->clearGameCount_24A);
        Gfx_Results_ItemsDisplay(g_SavegamePtr->clearGameCount_24A);
        Results_DisplayInfo(selectedItemId); // TODO: Takes no args in `credits.c`?
    }

    func_8004FB0C();
}

void func_8004FB0C() // 0x8004FB0C
{
    GsOT*    ot;
    POLY_F4* poly;

    ot   = &g_ObjectTable1[g_ObjectTableIdx];
    poly = (POLY_F4*)GsOUT_PACKET_P;

    setPolyF4(poly);
    setRGB0(poly, FP_COLOR(0.0f), FP_COLOR(0.0f), FP_COLOR(0.0f));
    setXY4(poly,
           -160, -224,
           -160, -222,
            160, -224,
            160, -222);
    addPrim(ot->org, poly);

    GsOUT_PACKET_P = (PACKET*)poly + sizeof(POLY_F4);
}

// TODO: RODATA migration.
//
// Function isn't fully matching.
// `new_var  -= SelectionOuline_InnerLine[g_Inventory_PrevSelectionId].field_0.vx` is mismatched
// Scratch: https://decomp.me/scratch/pGIn2
#ifdef NON_MATCHING
/** Draws many 2D menu elements.
 * The background behind the text in the upper
 * and lower part of the inventory screen, the
 * box used to indicate what the user has selected,
 * and triggers the drawing of the health status.
 */
void Gfx_Inventory_2dBackgroundDraw(s32* arg0) // 0x8004FBCC
{
    s16       ot0_7;
    s16       temp_a2_2;
    s16       temp_t2_3;
    s32       temp_t3;
    s32       temp_v1;
    s32       k;
    s32       i;
    s32       j;
    s32       var_t5;
    s32       var_t6;
    s32       new_var;
    s32       new_var3;
    s32       spA0;
    GsOT*     ot0;
    GsOT*     ot1;
    GsOT*     new_var2;
    POLY_G4*  poly_g4;
    POLY_FT4* poly_ft4;
    LINE_G2*  line_g2;

    s_Inventory_SelectionOutlineVector SelectionOuline_InnerLine[] = // 0x80027E54
    {
        { { 0xFFE0, 0xFFCC }, { 0x0040, 0x0080 } }, 
        { { 0xFFD0, 0xFF38 }, { 0x0060, 0x0090 } },
        { { 0xFFD0, 0x00B9 }, { 0x0060, 0x0018 } },
        { { 0xFF70, 0x00B9 }, { 0x0060, 0x0018 } },
        { { 0x0030, 0x00B9 }, { 0x0060, 0x0018 } },
        { { 0x0030, 0xFF38 }, { 0x0060, 0x0080 } },
        { { 0x0030, 0xFF38 }, { 0x0060, 0x0080 } },
        { { 0xFF70, 0xFF38 }, { 0x0060, 0x009C } },
        { { 0xFFD0, 0xFF38 }, { 0x00C0, 0x0100 } }
    };

    s_Inventory_SelectionOutlineVector SelectionOuline_ConerLines[] = // 0x80027E9C
    {
        { { 0xFFDE, 0xFFC8 }, { 0x0022, 0x0050 } },
        { { 0xFFCE, 0xFF34 }, { 0x0032, 0xFFCC } },
        { { 0xFFCE, 0x00B5 }, { 0x0032, 0x00D5 } },
        { { 0xFF6E, 0x00B5 }, { 0xFFD2, 0x00D5 } },
        { { 0x002E, 0x00B5 }, { 0x0092, 0x00D5 } },
        { { 0x002E, 0xFF34 }, { 0x0092, 0xFFBC } },
        { { 0x002D, 0xFF34 }, { 0x0092, 0xFFBC } },
        { { 0xFF6E, 0xFF34 }, { 0xFFD2, 0xFFD8 } },
        { { 0xFFCE, 0xFF34 }, { 0x0092, 0x003C } }
    };

    ot1 = &g_ObjectTable1[g_ObjectTableIdx];
    ot0 = &g_ObjectTable0[g_ObjectTableIdx];

    temp_v1 = g_SysWork.timer_1C & 0x7F;

    if (temp_v1 < 0x40)
    {
        spA0 = temp_v1;
    }
    else
    {
        spA0 = 0x7F - temp_v1;
    }

    Gfx_Inventory_HealthStatusDraw();
    if (g_Gfx_Inventory_SelectionBordersDraw == 8)
    {
        switch (*arg0)
        {
            case 1:
                var_t6 = 0;
                var_t5 = 1;
                break;

            case 2:
                var_t6 = 1;
                var_t5 = 1;
                break;

            case 3:
                var_t6 = 1;
                var_t5 = 0;
                break;

            case 4:
                var_t6 = 1;
                var_t5 = 2;
                break;

            case 5:
            case 6:
                var_t6 = 0;
                var_t5 = 2;
                break;

            case 7:
                var_t6 = 0;
                var_t5 = 0;
                break;

            default:
                var_t5 = -1;
                var_t6 = -1;
                break;
        }
    }
    else
    {   
        var_t5 = -1;
        var_t6 = -1;
    }

    if (g_GameWork.gameStateStep_598[1] != 20) 
    {
        for (i = 0; i < 2; i++)
        {
            for (j = 0; j < 3; j++)
            {
                for (k = 0; k < 2; k++)
                {
                    poly_g4 = (POLY_G4*)GsOUT_PACKET_P;
                    setPolyG4(poly_g4);

                    if (k != 0)
                    {
                        switch (g_SavegamePtr->gameDifficulty_260)
                        {
                            case GameDifficulty_Easy:
                                if (i == var_t6 && j == var_t5)
                                {
                                    setRGB0(poly_g4, spA0 - 0x80, 0xC0, spA0 * 3);
                                    setRGB2(poly_g4, spA0 - 0x80, 0xC0, spA0 * 3);
                                } 
                                else 
                                {
                                    setRGB0(poly_g4, 0x80, 0xC0, 0);
                                    setRGB2(poly_g4, 0x80, 0xC0, 0);
                                }
                                break;

                            case GameDifficulty_Normal:
                                if (i == var_t6 && j == var_t5)
                                {
                                    setRGB0(poly_g4, spA0 * 3, spA0 - 0x80, 0xC0);
                                    setRGB2(poly_g4, spA0 * 3, spA0 - 0x80, 0xC0);
                                }
                                else
                                {
                                    setRGB0(poly_g4, 0, 0x80, 0xC0);
                                    setRGB2(poly_g4, 0, 0x80, 0xC0);
                                }
                                break;

                            case GameDifficulty_Hard:
                                if (i == var_t6 && j == var_t5)
                                {
                                    setRGB0(poly_g4, spA0 - 0x80, spA0 * 3, 0xC0);
                                    setRGB2(poly_g4, spA0 - 0x80, spA0 * 3, 0xC0);
                                }
                                else
                                {
                                    setRGB0(poly_g4, 0x80, 0, 0xC0);
                                    setRGB2(poly_g4, 0x80, 0, 0xC0);
                                }
                                break;
                        }

                        setRGB1(poly_g4, 0, 0, 0);
                        setRGB3(poly_g4, 0, 0, 0);
                    }
                    else
                    {
                        switch (g_SavegamePtr->gameDifficulty_260)
                        {
                            case GameDifficulty_Easy:
                                if (i == var_t6 && j == var_t5)
                                {
                                    setRGB1(poly_g4, spA0 - 0x80, 0xC0, spA0 * 3);
                                    setRGB3(poly_g4, spA0 - 0x80, 0xC0, spA0 * 3);
                                }
                                else
                                {
                                    setRGB1(poly_g4, 0x80, 0xC0, 0);
                                    setRGB3(poly_g4, 0x80, 0xC0, 0);
                                }
                                break;

                            case GameDifficulty_Normal:
                                if (i == var_t6 && j == var_t5)
                                {
                                    setRGB1(poly_g4, spA0 * 3, spA0 - 0x80, 0xC0);
                                    setRGB3(poly_g4, spA0 * 3, spA0 - 0x80, 0xC0);
                                } 
                                else
                                {
                                    setRGB1(poly_g4, 0, 0x80, 0xC0);
                                    setRGB3(poly_g4, 0, 0x80, 0xC0);
                                }
                                break;

                            case GameDifficulty_Hard:
                                if (i == var_t6 && j == var_t5)
                                {
                                    setRGB1(poly_g4, spA0 - 0x80, spA0 * 3, 0xC0);
                                    setRGB3(poly_g4, spA0 - 0x80, spA0 * 3, 0xC0);
                                }
                                else
                                {
                                    setRGB1(poly_g4, 0x80, 0, 0xC0);
                                    setRGB3(poly_g4, 0x80, 0, 0xC0);
                                }
                                break;
                        }

                        setRGB0(poly_g4, 0, 0, 0);
                        setRGB2(poly_g4, 0, 0, 0);
                    }
            
                    if (i != 0)
                    {
                        setXY4(poly_g4,
                               -0x8C + (0x60 * j), 0xC0 + (6 * k),
                               -0x8C + (0x60 * j), 0xC6 + (6 * k),
                               -0x34 + (0x60 * j), 0xC0 + (6 * k),
                               -0x34 + (0x60 * j), 0xC6 + (6 * k));
                    }
                    else
                    {
                        setXY4(poly_g4,
                               -0x8C + (0x60 * j), -0xC0 + (6 * k),
                               -0x8C + (0x60 * j), -0xBA + (6 * k),
                               -0x34 + (0x60 * j), -0xC0 + (6 * k), 
                               -0x34 + (0x60 * j), -0xBA + (6 * k));
                    }

                    addPrim(&ot1->org[7], poly_g4);
                    GsOUT_PACKET_P = (PACKET*)poly_g4 + sizeof(POLY_G4);
                }
            }
        }
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            D_800C3B68[3 - i][j].vx = D_800C3B68[2 - i][j].vx;
            D_800C3B68[3 - i][j].vy = D_800C3B68[2 - i][j].vy;
        }
    }
    
    temp_t3   = (Math_Cos(g_Gfx_Inventory_SelectionBordersDraw << 7) * Math_Cos(g_Gfx_Inventory_SelectionBordersDraw << 7) * 0x10) >> 0x10;
    new_var   = SelectionOuline_InnerLine[*arg0].field_0.vx;
    new_var  -= SelectionOuline_InnerLine[g_Inventory_PrevSelectionId].field_0.vx;
    temp_a2_2 = SelectionOuline_InnerLine[*arg0].field_0.vx + FP_FROM((new_var) * temp_t3, Q12_SHIFT);

    D_800C3B68[0][0].vx = temp_a2_2;

    temp_t2_3 = SelectionOuline_InnerLine[*arg0].field_0.vy + 
                FP_FROM((SelectionOuline_InnerLine[g_Inventory_PrevSelectionId].field_0.vy - SelectionOuline_InnerLine[*arg0].field_0.vy) * temp_t3, Q12_SHIFT);

    D_800C3B68[0][1].vx = temp_a2_2;
    D_800C3B68[0][0].vy = temp_t2_3;
    
    temp_a2_2 = SelectionOuline_InnerLine[*arg0].field_0.vy + SelectionOuline_InnerLine[*arg0].field_4.vy + 
                FP_FROM(((SelectionOuline_InnerLine[g_Inventory_PrevSelectionId].field_0.vy + SelectionOuline_InnerLine[g_Inventory_PrevSelectionId].field_4.vy) - 
                (SelectionOuline_InnerLine[*arg0].field_0.vy + SelectionOuline_InnerLine[*arg0].field_4.vy)) * temp_t3, Q12_SHIFT);

    D_800C3B68[0][1].vy = temp_a2_2;

    ot0_7 = SelectionOuline_InnerLine[*arg0].field_0.vx + SelectionOuline_InnerLine[*arg0].field_4.vx + 
            FP_FROM(((SelectionOuline_InnerLine[g_Inventory_PrevSelectionId].field_0.vx + SelectionOuline_InnerLine[g_Inventory_PrevSelectionId].field_4.vx) - 
            (SelectionOuline_InnerLine[*arg0].field_0.vx + SelectionOuline_InnerLine[*arg0].field_4.vx)) * temp_t3, Q12_SHIFT);

    D_800C3B68[0][2].vy = temp_a2_2;
    D_800C3B68[0][3].vy = temp_t2_3;
    D_800C3B68[0][2].vx = ot0_7;
    D_800C3B68[0][3].vx = ot0_7;

    if (*arg0 == 8 || g_GameWork.gameStateStep_598[1] == 0xF)
    {
        poly_g4 = (POLY_G4*)GsOUT_PACKET_P;

        setPolyG4(poly_g4);
        setSemiTrans(poly_g4, 1);

        if (D_800AE190 < 0x21) 
        {
            setRGB0(poly_g4,
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10),
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10),
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10));
            setRGB1(poly_g4, 
                    (D_800AE190 >= 0x20) ? 0xFE : (D_800AE190 * 8),
                    (D_800AE190 >= 0x20) ? 0xFE : (D_800AE190 * 8),
                    (D_800AE190 >= 0x20) ? 0xFE : (D_800AE190 * 8));
            setRGB2(poly_g4, 
                    (D_800AE190 >= 8) ? 0xFE : (D_800AE190 * 32),
                    (D_800AE190 >= 8) ? 0xFE : (D_800AE190 * 32),
                    (D_800AE190 >= 8) ? 0xFE : (D_800AE190 * 32));
            setRGB3(poly_g4, 
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10),
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10),
                    (D_800AE190 >= 0x10) ? 0xFE : (D_800AE190 * 0x10));
        } 
        else 
        {
            setRGB0(poly_g4,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0);
            setRGB1(poly_g4, 
                    (D_800AE190 < 0x40) ? ((0x40 - D_800AE190) * 8) : 0,
                    (D_800AE190 < 0x40) ? ((0x40 - D_800AE190) * 8) : 0,
                    (D_800AE190 < 0x40) ? ((0x40 - D_800AE190) * 8) : 0);
            setRGB2(poly_g4, 
                    (D_800AE190 < 0x28) ? ((0x28 - D_800AE190) * 32) : 0,
                    (D_800AE190 < 0x28) ? ((0x28 - D_800AE190) * 32) : 0,
                    (D_800AE190 < 0x28) ? ((0x28 - D_800AE190) * 32) : 0);
            setRGB3(poly_g4, 
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0,
                    (D_800AE190 < 0x30) ? ((0x30 - D_800AE190) * 0x10) : 0);
        }

        setXY4(poly_g4,
               D_800C3B68[3][0].vx + 1, D_800C3B68[3][0].vy + 2,
               D_800C3B68[3][1].vx + 1, D_800C3B68[3][1].vy,
               D_800C3B68[3][3].vx,     D_800C3B68[3][3].vy + 2,
               D_800C3B68[3][3].vx,     D_800C3B68[3][1].vy);

        addPrim(&ot1->org[5], poly_g4);
        GsOUT_PACKET_P = (PACKET*)poly_g4 + sizeof(POLY_G4);

        Gfx_Primitive2dTextureSet(0, 0, 5, 2);

        if ((D_800AE190 >= 0x21 && *arg0 == 8) || (D_800AE190 < 0x21 && g_GameWork.gameStateStep_598[1] == 0xF))
        {
            for (i = 0; i < 2; i++)
            {
                poly_ft4 = (POLY_FT4*)GsOUT_PACKET_P;
                setPolyFT4(poly_ft4);
                poly_ft4->clut = getClut(g_ItemInspectionImg.clutX, g_ItemInspectionImg.clutY);
                setRGB0(poly_ft4, 0x80, 0x80, 0x80);

                if (i != 0) 
                {
                    poly_ft4->tpage = 0x86;
                    setUV4(poly_ft4,
                           0x20, 0x10,
                           0x20, 0xFF,
                           0xC0, 0x10,
                           0xC0, 0xFF);
                    setXY4(poly_ft4,
                           (u16)(D_800C3B68[3][0].vx + (((-(D_800C3B68[3][0].vx + 4) + D_800C3B68[3][3].vx) >> 1) + 1)), D_800C3B68[3][0].vy + 2,
                           (u16)(D_800C3B68[3][1].vx + (((-(D_800C3B68[3][1].vx + 4) + D_800C3B68[3][3].vx) >> 1) + 1)), D_800C3B68[3][1].vy,
                           D_800C3B68[3][3].vx,                                                                          D_800C3B68[3][3].vy + 2,
                           D_800C3B68[3][3].vx,                                                                          D_800C3B68[3][1].vy);
                }
                else
                {
                    poly_ft4->tpage = 0x85;
                    setUV4(poly_ft4,
                           0,    0x10,
                           0,    0xFF,
                           0xA0, 0x10,
                           0xA0, 0xFF);
                    setXY4(poly_ft4,
                           D_800C3B68[3][0].vx + 1,                                                                      D_800C3B68[3][0].vy + 2,
                           D_800C3B68[3][1].vx + 1,                                                                      D_800C3B68[3][1].vy,
                           (u16)(D_800C3B68[3][0].vx + ((-(D_800C3B68[3][0].vx + 4) + (D_800C3B68[3][3].vx) >> 1) + 2)), D_800C3B68[3][3].vy + 2,
                           (u16)(D_800C3B68[3][1].vx + ((-(D_800C3B68[3][1].vx + 4) + (D_800C3B68[3][3].vx) >> 1) + 2)), D_800C3B68[3][1].vy);
                }

                addPrim(&ot1->org[5], poly_ft4);
                GsOUT_PACKET_P = (PACKET*)poly_ft4 + sizeof(POLY_FT4);
            }
        }
    }

    for (j = 0; j < 4; j++)
    {
        for (i = 0; i < 4; i++) 
        {
            line_g2 = (LINE_G2*)GsOUT_PACKET_P;
            setLineG2(line_g2);

            setRGB0(line_g2, 0x60 - (0x20 * j), 0x60 - (0x20 * j), 0xFF);
            setRGB1(line_g2, 0x60 - (0x20 * j), 0x60 - (0x20 * j), 0xFF);
            setXY2(line_g2,
                   D_800C3B68[j][i].vx, D_800C3B68[j][i].vy,
                   D_800C3B68[j][(i + 1) & 0x3].vx, D_800C3B68[j][(i + 1) & 0x3].vy);

            addPrim(&ot0->org[7], line_g2);
            GsOUT_PACKET_P = (PACKET*)line_g2 + sizeof(LINE_G2);
        }

        for (i = 1; i < 4; i += 2)
        {
            line_g2 = (LINE_G2*)GsOUT_PACKET_P;
            setLineG2(line_g2);

            setRGB0(line_g2, 0x60 - (0x20 * j), 0x60 - (0x20 * j), 0xFF);
            setRGB1(line_g2, 0x60 - (0x20 * j), 0x60 - (0x20 * j), 0xFF);
            setXY2(line_g2,
                   D_800C3B68[j][i].vx,             D_800C3B68[j][i].vy + 1,
                   D_800C3B68[j][(i + 1) & 0x3].vx, D_800C3B68[j][(i + 1) & 0x3].vy + 1);

            addPrim(&ot1->org[7], line_g2);
            GsOUT_PACKET_P = (PACKET*)line_g2 + sizeof(LINE_G2);
        }
    }

    if (g_Gfx_Inventory_SelectionBordersDraw != 8)
    {
        return;
    }

    for (i = 0; i < 6; i++)
    {
        line_g2 = (LINE_G2*)GsOUT_PACKET_P;
        setLineG2(line_g2);

        setRGB0(line_g2, -0x50 - spA0, -0x50 - spA0, 0xFF);
        setRGB1(line_g2, spA0 + 0x70, spA0 + 0x70, 0xFF);

        if (i / 3)
        {
            setXY2(line_g2, SelectionOuline_ConerLines[*arg0].field_4.vx,
                   (i == 4) ? (SelectionOuline_ConerLines[*arg0].field_4.vy - 1) : SelectionOuline_ConerLines[*arg0].field_4.vy,
                   (i != 5) ? (SelectionOuline_ConerLines[*arg0].field_4.vx - (SelectionOuline_InnerLine[*arg0].field_4.vx >> 1)) : SelectionOuline_ConerLines[*arg0].field_4.vx,
                   (i == 5) ? (SelectionOuline_ConerLines[*arg0].field_4.vy - (SelectionOuline_InnerLine[*arg0].field_4.vy >> 1)) : 
                   (i == 4) ? (SelectionOuline_ConerLines[*arg0].field_4.vy - 1) : SelectionOuline_ConerLines[*arg0].field_4.vy);
        }
        else
        {
            setXY2(line_g2, SelectionOuline_ConerLines[*arg0].field_0.vx,
                   (i == 1) ? (SelectionOuline_ConerLines[*arg0].field_0.vy - 1) : SelectionOuline_ConerLines[*arg0].field_0.vy,
                   (i != 2) ? (SelectionOuline_ConerLines[*arg0].field_0.vx + (SelectionOuline_InnerLine[*arg0].field_0.vx >> 1)) : SelectionOuline_ConerLines[*arg0].field_0.vx,
                   (i == 2) ? (SelectionOuline_ConerLines[*arg0].field_0.vy + (SelectionOuline_InnerLine[*arg0].field_0.vy >> 1)) : 
                   (i == 1) ? (SelectionOuline_ConerLines[*arg0].field_0.vy - 1) : SelectionOuline_ConerLines[*arg0].field_0.vy);
        }

        addPrim(&ot0->org[7], line_g2);
        GsOUT_PACKET_P = (PACKET*)line_g2 + sizeof(LINE_G2);
    }  
}
#else
INCLUDE_RODATA("asm/bodyprog/nonmatchings/items/item_screens_3", D_80027E54);

INCLUDE_RODATA("asm/bodyprog/nonmatchings/items/item_screens_3", D_80027E9C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/items/item_screens_3", Gfx_Inventory_2dBackgroundDraw); // 0x8004FBCC
#endif

static inline s16 GetUvOrRandom()
{
    if (D_800AE198 == 1) 
    {
        D_800AE1A8 = Rng_Rand16() % 134; // TODO: `Rng_GenerateInt(Rng_Rand16(), 0, 133)` doesn't match.
        return D_800AE1A8;
    }
    else
    {
        return D_800AE1A8 & 0xFF;
    }
}

void Gfx_Inventory_HealthStatusDraw() 
{
    s32       tempOverlayY;
    s16       overlayYPos;
    s32       health;
    s32       healthSegment;
    s16       healthStage;
    s32       i;
    u8        greenVal;
    u8        redVal;
    GsOT*     ot;
    POLY_FT4* poly_ft4;
    POLY_G4*  poly_g4;
    DR_TPAGE* tPage;

    u8 D_80027F04[] =
    { 
        0xFF, 0x00, 0x00, 0x00, 
        0xFF, 0xA0, 0x00, 0x00, 
        0xa0, 0xFF, 0x00, 0x00, 
        0x00, 0xFF, 0x00, 0x00 
    };

    ot     = &g_ObjectTable0[g_ObjectTableIdx];
    health = g_SysWork.player_4C.chara_0.health_B0;

    if (health < FP_HEALTH(10.0f))
    {
        healthStage = 3;
    } 
    else if (health < FP_HEALTH(50.0f))
    {
        healthStage = 2;
    }
    else
    {
        healthStage = 1;
    }

    healthStage                          += g_Inventory_HealthStatusScanlineTimer;
    g_Inventory_HealthStatusScanlineTimer = healthStage % 164;

    for (i = 0; i < 3; i++)
    {
        if (i != 1 || g_Inventory_HealthStatusScanlineTimer >= 30)
        {
            if (i == 2)
            {
                if (g_SysWork.player_4C.chara_0.health_B0 != FP_HEALTH(100.0f) &&
                    ((Rng_Rand16() % ((g_SysWork.player_4C.chara_0.health_B0 >> 13) + 2) == 0) || D_800AE198 != 0))
                {
                    D_800AE198++;

                    if (D_800AE198 == 4) 
                    {
                        D_800AE198 = 0;
                    }
                }
                else
                {
                    continue;
                }
            } 

            poly_ft4 = (POLY_FT4*)GsOUT_PACKET_P;
            setPolyFT4(poly_ft4);
            poly_ft4->tpage = 159;
            poly_ft4->clut  = getClut(g_HealthPortraitImg.clutX, g_HealthPortraitImg.clutY);
            setRGB0(poly_ft4, 0x80, 0x80, 0x80);

            switch (i) 
            {
                case 0:
                    setUV4(poly_ft4,
                           40, 103,
                           40, 237,
                           124, 103,
                           124, 237);
                    setXY4(poly_ft4,
                           -138, -184,
                           -138, -50,
                           -54, -184,
                           -54, -50);
                    break;

                case 1:
                    setUV4(poly_ft4,
                           40,  g_Inventory_HealthStatusScanlineTimer + 73,
                           40,  g_Inventory_HealthStatusScanlineTimer + 75,
                           124, g_Inventory_HealthStatusScanlineTimer + 73,
                           124, g_Inventory_HealthStatusScanlineTimer + 75);
                    setXY4(poly_ft4,
                           -136, g_Inventory_HealthStatusScanlineTimer - 214,
                           -136, g_Inventory_HealthStatusScanlineTimer - 212,
                           -52,  g_Inventory_HealthStatusScanlineTimer - 214,
                           -52,  g_Inventory_HealthStatusScanlineTimer - 212);

                    if (g_Inventory_HealthStatusColorGradientTimer == 0)
                    {
                        g_Inventory_HealthStatusScanlinePosition = poly_ft4->y0;
                    }
                    break;

                case 2:
                    setUV4(poly_ft4,
                           40,  GetUvOrRandom() + 103,
                           40,  D_800AE1A8 + 105,
                           124, D_800AE1A8 + 103,
                           124, D_800AE1A8 + 105);
                    setXY4(poly_ft4,
                           -136, D_800AE1A8 - 184,
                           -136, D_800AE1A8 - 182,
                           -52,  D_800AE1A8 - 184,
                           -52,  D_800AE1A8 - 182);
                    break;
            }

            addPrim((u8*)ot->org - (-8156 + (i * 4)), poly_ft4);
            GsOUT_PACKET_P = (PACKET*)poly_ft4 + sizeof(POLY_FT4);
        }
    }

    poly_g4 = (POLY_G4*)GsOUT_PACKET_P;

    setPolyG4(poly_g4);
    setSemiTrans(poly_g4, 1);
    setRGB0(poly_g4, 0xFF, 0xFF, 0xFF);
    setRGB1(poly_g4, 0, 0, 0);
    setRGB2(poly_g4, 0xFF, 0xFF, 0xFF);
    setRGB3(poly_g4, 0, 0, 0);
    setXY4(poly_g4,
           -136, g_Inventory_HealthStatusScanlineTimer - 212,
           -136, g_Inventory_HealthStatusScanlineTimer - 182,
           -54,  g_Inventory_HealthStatusScanlineTimer - 212,
           -54,  g_Inventory_HealthStatusScanlineTimer - 182);

    tempOverlayY = poly_g4->y0 - 2;

    if (tempOverlayY >= -214)
    {
        if (tempOverlayY >= (g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)))
        {
            overlayYPos = tempOverlayY;
        }
        else
        {
            overlayYPos = -52;
        }
    } 
    else 
    {
        overlayYPos = -52;
    }

    addPrim(&ot->org[2036], poly_g4);
    GsOUT_PACKET_P = (PACKET*)poly_g4 + sizeof(POLY_G4);

    tPage = (DR_TPAGE*)GsOUT_PACKET_P;
    setDrawTPage(tPage, 0, 1, 64);
    addPrim(&ot->org[2036], tPage);
    GsOUT_PACKET_P = (PACKET*)tPage + sizeof(DR_TPAGE);

    if (g_Inventory_HealthStatusScanlinePosition != -300)
    {
        healthSegment = FP_FROM(g_SysWork.player_4C.chara_0.health_B0, Q12_SHIFT);

        if (healthSegment < 39)
        {
            redVal   = D_80027F04[0];
            greenVal = D_80027F04[1];
        }
        else if (healthSegment < 0x41)
        {
            redVal   = D_80027F04[4];
            greenVal = D_80027F04[5];
        }
        else if (healthSegment < 0x55)
        {
            redVal   = D_80027F04[8];
            greenVal = D_80027F04[9];
        }
        else
        {
            redVal   = D_80027F04[12];
            greenVal = D_80027F04[13];
        }

        for (i = 0; i < 2; i++)
        {
            poly_g4 = (POLY_G4*)GsOUT_PACKET_P;
            
            setPolyG4(poly_g4);
            setRGB0(poly_g4,
                    redVal   - ((redVal   * g_Inventory_HealthStatusColorGradientTimer) >> 6),
                    greenVal - ((greenVal * g_Inventory_HealthStatusColorGradientTimer) >> 6),
                    0);
            setRGB1(poly_g4, 0, 0, 0);
            setRGB2(poly_g4,
                    redVal   - ((redVal   * g_Inventory_HealthStatusColorGradientTimer) >> 6),
                    greenVal - ((greenVal * g_Inventory_HealthStatusColorGradientTimer) >> 6),
                    0);
            setRGB3(poly_g4, 0, 0, 0);

            if (i != 0)
            {
                setXY4(poly_g4,
                    -136, ((g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)) < -182) ?
                          -182 :
                          (g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)),
                    -136, poly_g4->y0 - 16,
                    -56,  ((g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)) < -182) ?
                          -182 :
                          (g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)),
                    -56,  poly_g4->y0 - 16);
            } 
            else
            {
                setXY4(poly_g4,
                    -136, ((g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)) < -182) ?
                          -182 :
                          (g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)),
                    -136, overlayYPos,
                    -56,  ((g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)) < -182) ?
                          -182 :
                          (g_Inventory_HealthStatusScanlinePosition - (g_Inventory_HealthStatusColorGradientTimer >> 1)),
                    -56,  overlayYPos);
            }

            addPrim(&ot->org[2040], poly_g4);
            GsOUT_PACKET_P = (PACKET*)poly_g4 + sizeof(POLY_G4);
        }
    }

    if (g_SysWork.player_4C.chara_0.health_B0 < FP_HEALTH(10.0f))
    {
        healthStage = 3;
    }
    else if (g_SysWork.player_4C.chara_0.health_B0 < FP_HEALTH(50.0f))
    {
        healthStage = 2;
    }
    else
    {
        healthStage = 1;
    }

    g_Inventory_HealthStatusColorGradientTimer = healthStage + g_Inventory_HealthStatusColorGradientTimer;
    
    if (g_Inventory_HealthStatusColorGradientTimer >= 64)
    {
        g_Inventory_HealthStatusColorGradientTimer = 0;
        g_Inventory_HealthStatusScanlinePosition   = -300;
    }
}

void Gfx_Inventory_ItemDescriptionDraw(s32* selectedItemId) // 0x8005192C
{
    s32 temp;
    s32 i;
    s32 idx;

    DVECTOR stringPos = { 208, 200 };

    char* D_80027F14[] =
    {
        "Can't_use_it_here.",
        "Too_dark_to_look_at\n\t\tthe_item_here."
    };

    char* D_80027F94[] =
    {
        "Stock:",
        "==On==",
        "==Off==",
        "==Use_OK==",
        "==Use_OK?==",
        "==Use_NG==",
        "Fuel:"
    };

    switch (*selectedItemId)
    {
        case 0:
        case 5:
        case 7:
        case 8:
            idx = g_SysWork.inventoryItemSelectedIdx_2351;
            break;

        default:
            idx = g_SysWork.playerCombatInfo_38.field_12;
            break;
    }
    
    if (D_800AE185 != ((g_SavegamePtr->items_0[idx].id_0 >> 5) - 1) ||
        D_800AE186 != (g_SavegamePtr->items_0[idx].id_0 & 0x1F))
    {
        g_SysWork.sysStateStep_C[1]      = 0;
        g_SysWork.timer_2C               = 0;
        g_SysWork.sysStateStep_C[2]      = 0;
        g_Inventory_ItemNameTimer        = 0;
        g_Inventory_DescriptionRollTimer = 0;
        D_800AE18C                       = 0;
        D_800AE18E                       = 0;
        D_800AE178                       = 0;
    }
    
    if (idx != NO_VALUE && *selectedItemId != 2 && *selectedItemId != 3 && *selectedItemId != 4)
    {
        for (i = 0; i < g_SavegamePtr->inventorySlotCount_AB; i++)
        {
            if (i == idx)
            {    
                if (idx + 1 >= 10)
                {
                    Gfx_StringSetPosition(45, 184);
                }
                else
                {
                    Gfx_StringSetPosition(55, 184);
                }

                Gfx_StringDrawInt(2, i + 1);
                i = g_SavegamePtr->inventorySlotCount_AB;
            }
        }
    }

    if ((g_Inventory_EquippedItem >> 5) == 5 && g_Inventory_EquippedItem != InventoryItemId_HyperBlaster)
    {
        Gfx_StringSetPosition(122, 30);
        Gfx_StringDraw(D_80027F94[0], 10);
        
        for (i = 0; i < g_SavegamePtr->inventorySlotCount_AB; i++) 
        {
            if (g_Inventory_EquippedItem == g_SavegamePtr->items_0[i].id_0) 
            {
                if (g_SavegamePtr->items_0[i].count_1 >= 10) 
                {
                    Gfx_StringSetPosition(178, 30);
                }
                else
                {
                    Gfx_StringSetPosition(188, 30);
                }
                Gfx_StringDrawInt(2, g_SavegamePtr->items_0[i].count_1);
            }
        }
    }

    temp = *selectedItemId;

    if (temp < 0 || (temp >= 2 && (*selectedItemId >= 9 || temp < 5)) ||
        g_SavegamePtr->items_0[idx].id_0 == 0xFF)
    {
        return;
    }

    switch (g_SavegamePtr->items_0[idx].id_0) 
    {
        case InventoryItemId_Flashlight:
            Gfx_StringSetPosition(stringPos.vx, stringPos.vy);
            if (func_8003ED64() == 0)
            {
                Gfx_StringDraw(D_80027F94[2], 10);
            } 
            else 
            {
                Gfx_StringDraw(D_80027F94[1], 10);
            }
            break;

        case InventoryItemId_PocketRadio:
            Gfx_StringSetPosition(stringPos.vx, stringPos.vy);
            if (g_SavegamePtr->flags_AC & 1)
            {
                Gfx_StringDraw(D_80027F94[1], 10);
            }
            else
            {
                Gfx_StringDraw(D_80027F94[2], 10);
            }
            break;

        case InventoryItemId_HyperBlaster:
            Gfx_StringSetPosition(stringPos.vx - 16, stringPos.vy);
            switch (Inventory_HyperBlasterFunctionalTest())
            {
                case 2: // If Hyper Blaster connected (Port 1) or player has unlocked it.
                    Gfx_StringDraw(D_80027F94[3], 10);
                    break;

                case 1: // If Hyper Blaster connected (Port 2).
                    Gfx_StringDraw(D_80027F94[4], 10);
                    break;

                case 0: // If Hyper Blaster is in inventory, but needs to be unlocked by finishing the game.
                    Gfx_StringDraw(D_80027F94[5], 10);
                    break;
            }
            break;
        
        case InventoryItemId_HealthDrink:
        case InventoryItemId_FirstAidKit:
        case InventoryItemId_Ampoule:
        case InventoryItemId_Handgun:
        case InventoryItemId_HuntingRifle:
        case InventoryItemId_Shotgun:
        case InventoryItemId_HandgunBullets:
        case InventoryItemId_RifleShells:
        case InventoryItemId_ShotgunShells:
            Gfx_StringSetPosition(stringPos.vx, stringPos.vy);
            Gfx_StringDraw(D_80027F94[0], 10);
            if (g_SavegamePtr->items_0[idx].id_0 != 0xFF) 
            {
                if (g_SavegamePtr->items_0[idx].count_1 >= 100)
                {
                    Gfx_StringSetPosition(260, 200);
                }
                else if (g_SavegamePtr->items_0[idx].count_1 >= 10)
                {
                    Gfx_StringSetPosition(270, 200);
                }
                else
                {
                    Gfx_StringSetPosition(280, 200);
                }
                Gfx_StringDrawInt(3, g_SavegamePtr->items_0[idx].count_1);
            }
            break;
    }

    Gfx_StringSetColor(ColorId_White);

    D_800AE185 = (g_SavegamePtr->items_0[idx].id_0 >> 5) - 1;
    D_800AE186 = g_SavegamePtr->items_0[idx].id_0 & 0x1F;

    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            g_Inventory_ItemNameTimer++;
            Gfx_StringSetPosition(68, 200);
            if (Gfx_StringDraw(g_ItemNames[g_SavegamePtr->items_0[idx].id_0 - 32], g_Inventory_ItemNameTimer) == true)
            {
                g_Inventory_ItemNameTimer   = 100;
                g_SysWork.timer_2C          = 0;
                g_SysWork.sysStateStep_C[2] = 0;
                g_SysWork.sysStateStep_C[1]++;
            }
            break;

        case 1:
            g_Inventory_DescriptionRollTimer += 2;
            Gfx_StringSetPosition(68, 200);
            Gfx_StringDraw(g_ItemNames[g_SavegamePtr->items_0[idx].id_0 - 32], 100);

            if (idx == g_Inventory_SelectedItemIdx)
            {
                g_Inventory_ItemNameTimer = 0;
            }

            Gfx_StringSetPosition(30, 232);

            if (Gfx_StringDraw(g_ItemDescriptions[g_SavegamePtr->items_0[idx].id_0 - 32], g_Inventory_DescriptionRollTimer) == true)
            {
                g_Inventory_DescriptionRollTimer = 100;
                g_SysWork.timer_2C               = 0;
                g_SysWork.sysStateStep_C[2]      = 0;
                g_SysWork.sysStateStep_C[1]++;
            }
            break;

        case 2:
        case 3:
        case 4:
            Gfx_StringSetPosition(68, 200);
            Gfx_StringDraw(g_ItemNames[g_SavegamePtr->items_0[idx].id_0 - 32], 100);
            Gfx_StringSetPosition(30, 232);

            switch (g_SysWork.sysStateStep_C[1])
            {
                case 2:
                    Gfx_StringDraw(g_ItemDescriptions[g_SavegamePtr->items_0[idx].id_0 - 32], 100);
                    break;
                
                case 3:
                    Gfx_StringDraw(D_80027F14[0], 100);
                    break;
                
                case 4:
                    Gfx_StringDraw(D_80027F14[1], 100);
                    break;
            }
            
            if (idx == g_Inventory_SelectedItemIdx)
            {
                g_Inventory_ItemNameTimer = 0;
            }
            break;
    }
}

void Gfx_Primitive2dTextureSet(s32 x, s32 y, s32 otIdx, s32 abr) // 0x80052088
{
    GsOT*     ot0;
    GsOT*     ot1;
    s32       idx   = g_ObjectTableIdx;
    DR_TPAGE* tPage = (DR_TPAGE*)GsOUT_PACKET_P;

    setDrawTPage(tPage, 0, 1, getTPage(0, abr, x, y));

    ot1 = &g_ObjectTable1[idx];
    ot0 = &g_ObjectTable0[idx];

    if (abr < 4)
    {
        addPrim(&ot1->org[otIdx], tPage);
    }
    else
    {
        addPrim(&ot0->org[otIdx], tPage);
    }

    GsOUT_PACKET_P = (PACKET*)tPage + sizeof(DR_TPAGE);
}

void Gfx_Results_ItemsDisplay() // 0x800521A8
{
    GsDOBJ2* ptr;
    s32      i;

    for (i = 0, ptr = g_Items_ItemsModelData; i < 6; i++, ptr++)
    {
        if ((D_800C3E40 >> i) & (1 << 0))
        {
            Gfx_Items_ItemRotate(&g_Items_Items3dData1[i].param->rotate, &g_Items_Items3dData1[i]);
            func_800548D8(i);
            GsSetFlatLight(0, &g_Items_ItemsLightingData[i][0]);
            GsSetFlatLight(1, &g_Items_ItemsLightingData[i][1]);
            func_8004BD74(i, ptr, 3);
        }
    }
}

void Gfx_Results_ItemsPosition() // 0x8005227C
{
    s32 i;

    SVECTOR vecs[] = // 0x80027FB0
    {
        { 0x0000, 0xFCC0, 0x1400, 0x0000 },
        { 0xFCF8, 0xFE80, 0x1400, 0x0000 },
        { 0x0308, 0xFE80, 0x1400, 0x0000 },
        { 0xFCF8, 0x0200, 0x1400, 0x0000 },
        { 0x0308, 0x0200, 0x1400, 0x0000 },
        { 0x0000, 0x03C0, 0x1400, 0x0000 },
    };

    if (g_SavegamePtr->clearGameCount_24A == 0)
    {
        g_SavegamePtr->clearGameCount_24A = 1;
    }

    for (i = 0; i < 6; i++)
    {
        if ((D_800C3E40 >> i) & (1 << 0))
        {
            g_Items_Items3dData1[i].coord.t[0]      = vecs[i].vx;
            g_Items_Items3dData1[i].coord.t[1]      = vecs[i].vy;
            g_Items_Items3dData1[i].coord.t[2]      = vecs[i].vz;
            g_Items_Items3dData0[i].rotation_10.vx  = 0x200;
            g_Items_Items3dData0[i].rotation_10.vz  = 0x200;
            g_Items_Items3dData0[i].scale_0.vz      = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[i].scale_0.vy      = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[i].scale_0.vx      = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[i].rotation_10.vy += 8;
        }
    }
}

/** Name could be inaccurate.
 * Breaking this function call makes items no longer rotate,
 * and trying to scroll through the items will softlock the game.
 * If the user breaks the function before entering the
 * inventory, all items will be at the center of the screen
 * and the equiped item will appear frozen in its base pose.
 * If the user doesn't try scrolling through items, they
 * will be able to navigate through other functions. However,
 * messing with commands also will softlock the game.
 */
INCLUDE_ASM("asm/bodyprog/nonmatchings/items/item_screens_3", Inventory_PlayerItemScroll); // 0x800523D8

void func_800539A4(s32 scrollDirection, s32 arg1) // 0x800539A4
{
    #define RIGHT_SCROLL 7
    #define LEFT_SCROLL -7

    s32 sp10[10];
    s32 i;
    s32 var_a3_2;
    s32 var_s0;

    var_s0 = 0;

    for (i = 0; i < 10; i++)
    {
        sp10[i] = D_800C3E18[i];
    }

    var_a3_2 = (scrollDirection != 0) ? LEFT_SCROLL : RIGHT_SCROLL;
    var_a3_2 = (arg1 + var_a3_2 + g_SavegamePtr->inventorySlotCount_AB) % g_SavegamePtr->inventorySlotCount_AB;

    for (i = 0; i < 7; i++)
    {
        if (sp10[i] == var_a3_2)
        {
            var_s0 = i;
            i      = 7;
        }
    }

    sp10[var_s0] = arg1;

    if (g_SavegamePtr->items_0[arg1].id_0 != 0xFF)
    {
        for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
        {
            if (g_SavegamePtr->items_0[arg1].id_0 == g_Item_MapLoadableItems[i])
            {
                Gfx_Items_Display(FS_BUFFER_8, var_s0, i);
                func_8005487C(var_s0);
                i = INVENTORY_ITEM_COUNT_MAX;
            }
        }
    }

    for (i = 0; i < 10; i++)
    {
        D_800C3E18[i] = sp10[i];
    }
}

/** @note For better comprehension related to file handling
 * of inventory items.
 *
 * - `GameFs_UniqueItemModelLoad` loads model of items individually.
 * - `GameFs_MapItemsModelLoad` and `GameFs_MapItemsTextureLoad` load packs of textures and
 *   models of items, though while `GameFs_UniqueItemModelLoad` seems to load
 *   them individually based on what is being passed as argument,
 * - `GameFs_MapItemsModelLoad` and `GameFs_MapItemsTextureLoad` load the packs based on the 
 *   map being loaded.
 */

void GameFs_UniqueItemModelLoad(u8 itemId) // 0x80053B08
{
    switch (itemId)
    {
        case InventoryItemId_HealthDrink:
            Fs_QueueStartRead(FILE_ITEM_UNQ21_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Ampoule:
            Fs_QueueStartRead(FILE_ITEM_UNQ22_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_HouseKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ41_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfLion:
            Fs_QueueStartRead(FILE_ITEM_UNQ42_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfWoodman:
            Fs_QueueStartRead(FILE_ITEM_UNQ43_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfScarecrow:
            Fs_QueueStartRead(FILE_ITEM_UNQ44_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_LibraryReserveKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ45_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_ClassroomKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ46_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KGordonKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ47_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_DrawbridgeKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ48_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_BasementKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ49_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_BasementStoreroomKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ4A_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_ExaminationRoomKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ4B_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_AntiqueShopKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ4C_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_SewerKey:
        case InventoryItemId_SewerExitKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ4D_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfOphiel:
            Fs_QueueStartRead(FILE_ITEM_UNQ4E_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfHagith:
            Fs_QueueStartRead(FILE_ITEM_UNQ4F_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfPhaleg:
            Fs_QueueStartRead(FILE_ITEM_UNQ50_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfBethor:
            Fs_QueueStartRead(FILE_ITEM_UNQ51_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KeyOfAratron:
            Fs_QueueStartRead(FILE_ITEM_UNQ52_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_NoteToSchool:
            Fs_QueueStartRead(FILE_ITEM_UNQ53_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_NoteDoghouse:
            Fs_QueueStartRead(FILE_ITEM_UNQ54_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PictureCard:
            Fs_QueueStartRead(FILE_ITEM_UNQ55_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_ChannelingStone:
            Fs_QueueStartRead(FILE_ITEM_UNQ56_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Chemical:
            Fs_QueueStartRead(FILE_ITEM_UNQ60_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_GoldMedallion:
            Fs_QueueStartRead(FILE_ITEM_UNQ61_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_SilverMedallion:
            Fs_QueueStartRead(FILE_ITEM_UNQ62_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_RubberBall:
            Fs_QueueStartRead(FILE_ITEM_UNQ63_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Flauros:
            Fs_QueueStartRead(FILE_ITEM_UNQ64_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlasticBottle:
            Fs_QueueStartRead(FILE_ITEM_UNQ65_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_UnknownLiquid:
            Fs_QueueStartRead(FILE_ITEM_UNQ66_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlateOfHatter:
            Fs_QueueStartRead(FILE_ITEM_UNQ67_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlateOfCat:
            Fs_QueueStartRead(FILE_ITEM_UNQ68_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlateOfQueen:
            Fs_QueueStartRead(FILE_ITEM_UNQ69_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PlateOfTurtle:
            Fs_QueueStartRead(FILE_ITEM_UNQ6A_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_BloodPack:
            Fs_QueueStartRead(FILE_ITEM_UNQ6B_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_DisinfectingAlcohol:
            Fs_QueueStartRead(FILE_ITEM_UNQ6C_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Lighter:
            Fs_QueueStartRead(FILE_ITEM_UNQ6D_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_VideoTape:
            Fs_QueueStartRead(FILE_ITEM_UNQ6E_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KaufmannKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ70_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Receipt:
            Fs_QueueStartRead(FILE_ITEM_UNQ71_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_SafeKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ72_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Magnet:
            Fs_QueueStartRead(FILE_ITEM_UNQ73_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_MotorcycleKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ74_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_BirdCageKey:
            Fs_QueueStartRead(FILE_ITEM_UNQ75_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Pliers:
            Fs_QueueStartRead(FILE_ITEM_UNQ76_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Screwdriver:
            Fs_QueueStartRead(FILE_ITEM_UNQ77_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Camera:
            Fs_QueueStartRead(FILE_ITEM_UNQ78_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_RingOfContract:
            Fs_QueueStartRead(FILE_ITEM_UNQ79_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_StoneOfTime:
            Fs_QueueStartRead(FILE_ITEM_UNQ7A_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_AmuletOfSolomon:
            Fs_QueueStartRead(FILE_ITEM_UNQ7B_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_CrestOfMercury:
            Fs_QueueStartRead(FILE_ITEM_UNQ7C_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Ankh:
            Fs_QueueStartRead(FILE_ITEM_UNQ7D_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_DaggerOfMelchior:
            Fs_QueueStartRead(FILE_ITEM_UNQ7E_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_DiskOfOuroboros:
            Fs_QueueStartRead(FILE_ITEM_UNQ7F_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_KitchenKnife:
            Fs_QueueStartRead(FILE_ITEM_UNQ80_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_SteelPipe:
            Fs_QueueStartRead(FILE_ITEM_UNQ81_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Hammer:
            Fs_QueueStartRead(FILE_ITEM_UNQ82_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Chainsaw:
            Fs_QueueStartRead(FILE_ITEM_UNQ83_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Axe:
            Fs_QueueStartRead(FILE_ITEM_UNQ84_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_RockDrill:
            Fs_QueueStartRead(FILE_ITEM_UNQ85_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Katana:
            Fs_QueueStartRead(FILE_ITEM_UNQ86_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Handgun:
            Fs_QueueStartRead(FILE_ITEM_UNQA0_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_HuntingRifle:
            Fs_QueueStartRead(FILE_ITEM_UNQA1_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Shotgun:
            Fs_QueueStartRead(FILE_ITEM_UNQA2_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_HyperBlaster:
            Fs_QueueStartRead(FILE_ITEM_UNQA3_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_HandgunBullets:
            Fs_QueueStartRead(FILE_ITEM_UNQC0_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_RifleShells:
            Fs_QueueStartRead(FILE_ITEM_UNQC1_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_ShotgunShells:
            Fs_QueueStartRead(FILE_ITEM_UNQC2_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_Flashlight:
            Fs_QueueStartRead(FILE_ITEM_UNQE0_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_PocketRadio:
            Fs_QueueStartRead(FILE_ITEM_UNQE1_TMD, FS_BUFFER_5);
            break;

        case InventoryItemId_GasolineTank:
            Fs_QueueStartRead(FILE_ITEM_UNQE2_TMD, FS_BUFFER_5);
            break;

        default:
            Fs_QueueStartRead(FILE_ITEM_UNQ20_TMD, FS_BUFFER_5);
            break;
    }
}

void GameFs_Tim00TIMLoad() // 0x80053dA0
{
    if (g_SysWork.flags_2352 & (1 << 0))
    {
        return;
    }

    Fs_QueueStartReadTim(FILE_ITEM_TIM00_TIM, FS_BUFFER_1, &g_FirstAidKitItemTextureImg);
    g_SysWork.flags_2352 |= 1 << 0;
}

void GameFs_MapItemsModelLoad(u32 mapId) // 0x80053DFC
{
    if (!(g_SysWork.flags_2352 & (1 << 7)))
    {
        Fs_QueueStartReadTim(FILE_ITEM_TIM07_TIM, FS_BUFFER_1, &D_800A9074);
        g_SysWork.flags_2352 |= 1 << 7;
    }

    switch (mapId)
    {
        case MapOverlayId_MAP1_S00:
        case MapOverlayId_MAP1_S01:
        case MapOverlayId_MAP1_S02:
        case MapOverlayId_MAP1_S03:
        case MapOverlayId_MAP1_S05:
            if (!(g_SysWork.flags_2352 & (1 << 1)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM01_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 1);
            }
            break;

        case MapOverlayId_MAP0_S01:
        case MapOverlayId_MAP0_S02:
        case MapOverlayId_MAP1_S06:
        case MapOverlayId_MAP2_S00:
        case MapOverlayId_MAP2_S01:
        case MapOverlayId_MAP2_S02:
        case MapOverlayId_MAP2_S04:
        case MapOverlayId_MAP4_S00:
        case MapOverlayId_MAP4_S01:
        case MapOverlayId_MAP4_S02:
        case MapOverlayId_MAP4_S03:
        case MapOverlayId_MAP4_S05:
            if (!(g_SysWork.flags_2352 & (1 << 2)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM02_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 2);
            }
            break;

        case MapOverlayId_MAP3_S00:
        case MapOverlayId_MAP3_S01:
        case MapOverlayId_MAP3_S02:
        case MapOverlayId_MAP3_S03:
        case MapOverlayId_MAP3_S04:
        case MapOverlayId_MAP3_S05:
        case MapOverlayId_MAP3_S06:
        case MapOverlayId_MAP4_S04:
            if (!(g_SysWork.flags_2352 & (1 << 3)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM03_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 3);
            }
            break;

        case MapOverlayId_MAP5_S00:
        case MapOverlayId_MAP5_S01:
        case MapOverlayId_MAP5_S02:
        case MapOverlayId_MAP5_S03:
        case MapOverlayId_MAP6_S00:
        case MapOverlayId_MAP6_S01:
        case MapOverlayId_MAP6_S02:
        case MapOverlayId_MAP6_S03:
        case MapOverlayId_MAP6_S04:
            if (!(g_SysWork.flags_2352 & (1 << 4)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM04_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 4);
            }
            break;

        case MapOverlayId_MAP7_S00:
        case MapOverlayId_MAP7_S01:
            if (!(g_SysWork.flags_2352 & (1 << 5)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM05_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 5);
            }
            break;

        case MapOverlayId_MAP7_S02:
        case MapOverlayId_MAP7_S03:
            if (!(g_SysWork.flags_2352 & (1 << 6)))
            {
                Fs_QueueStartReadTim(FILE_ITEM_TIM06_TIM, FS_BUFFER_1, &g_InventoryKeyItemTextureImg);
                g_SysWork.flags_2352 = (g_SysWork.flags_2352 & 0x81) | (1 << 6);
            }
            break;

        case 0:
            break;
    }
}

void GameFs_MapItemsTextureLoad(s32 mapId) // 0x80054024
{
    switch (mapId)
    {
        case MapOverlayId_MAP0_S00:
            Fs_QueueStartRead(FILE_ITEM_IT_000_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP0_S01:
        case MapOverlayId_MAP0_S02:
        case MapOverlayId_MAP1_S06:
        case MapOverlayId_MAP2_S00:
        case MapOverlayId_MAP2_S01:
        case MapOverlayId_MAP2_S02:
        case MapOverlayId_MAP2_S04:
        case MapOverlayId_MAP4_S00:
        case MapOverlayId_MAP4_S01:
        case MapOverlayId_MAP4_S02:
        case MapOverlayId_MAP4_S03:
        case MapOverlayId_MAP4_S05:
            Fs_QueueStartRead(FILE_ITEM_IT_001_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP1_S00:
        case MapOverlayId_MAP1_S01:
        case MapOverlayId_MAP1_S02:
        case MapOverlayId_MAP1_S03:
        case MapOverlayId_MAP1_S05:
            Fs_QueueStartRead(FILE_ITEM_IT_002_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP3_S00:
        case MapOverlayId_MAP3_S01:
        case MapOverlayId_MAP3_S02:
        case MapOverlayId_MAP3_S03:
        case MapOverlayId_MAP3_S04:
        case MapOverlayId_MAP3_S05:
        case MapOverlayId_MAP3_S06:
        case MapOverlayId_MAP4_S04:
            Fs_QueueStartRead(FILE_ITEM_IT_003_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP5_S00:
        case MapOverlayId_MAP5_S01:
        case MapOverlayId_MAP5_S02:
        case MapOverlayId_MAP5_S03:
        case MapOverlayId_MAP6_S00:
        case MapOverlayId_MAP6_S01:
        case MapOverlayId_MAP6_S02:
        case MapOverlayId_MAP6_S03:
        case MapOverlayId_MAP6_S04:
            Fs_QueueStartRead(FILE_ITEM_IT_004_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP7_S00:
        case MapOverlayId_MAP7_S01:
            Fs_QueueStartRead(FILE_ITEM_IT_005_TMD, FS_BUFFER_8);
            break;

        case MapOverlayId_MAP7_S02:
        case MapOverlayId_MAP7_S03:
            Fs_QueueStartRead(FILE_ITEM_IT_006_TMD, FS_BUFFER_8);
            break;
    }
}

void func_800540A4(s8 arg0) // 0x800540A4
{
    s32 i;
    s32 j;

    if (g_SysWork.playerCombatInfo_38.field_12 != NO_VALUE)
    {
        g_SavegamePtr->items_0[g_SysWork.playerCombatInfo_38.field_12].count_1 = g_SysWork.playerCombatInfo_38.currentWeaponAmmo_10;
    }

    for (i = 0; i < g_SavegamePtr->inventorySlotCount_AB; i++)
    {
        if (g_SavegamePtr->items_0[i].id_0 >> 5 == 6 && 
            g_SavegamePtr->items_0[i].id_0 == (g_SavegamePtr->items_0[g_SysWork.playerCombatInfo_38.field_12].id_0 + 32))
        {
            g_SavegamePtr->items_0[i].count_1 = g_SysWork.playerCombatInfo_38.totalWeaponAmmo_11;

            if (!g_SavegamePtr->items_0[i].count_1)
            {
                g_SavegamePtr->items_0[i].id_0 = NO_VALUE;
            }

            g_SavegamePtr->inventorySlotCount_AB = func_8004F190(g_SavegamePtr);
            break;
        }
    }

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            D_800C3B68[i][j].vy = 0;
            D_800C3B68[i][j].vx = 0;
        }
    }

    D_800AE18C = 0;
    D_800AE18E = 0;

    Fs_QueueStartReadTim(FILE_ITEM_HEROPIC2_TIM, FS_BUFFER_1, &g_HealthPortraitImg);
}

// Item rendering related.
void Gfx_Items_Render() // 0x80054200
{
    s32  temp_s5;
    s32  i;
    s32  saveItemsIdx;
    s32  inventoryItemsIdx;
    s32* var_s1;
    s32* var_s2;

    func_8004BFE8();

    D_800AE190 = 0;

    Gfx_ItemScreens_CameraSet(&D_800C3B48, &D_800C3AE8, &D_800C3B38, 0);

    /** This loops define the position, rotation and scale of the item that
    * the player has initially equipped in the inventory.
    */
    for (i = 0; i < 10; i++)
    {
        D_800C3E18[i] = NO_VALUE;

        g_Items_Items3dData0[i].scale_0.vz     = FP_METER(1.0f);
        g_Items_Items3dData0[i].scale_0.vy     = FP_METER(1.0f);
        g_Items_Items3dData0[i].scale_0.vx     = FP_METER(1.0f);
        g_Items_Items3dData0[i].rotation_10.vz = 0;
        g_Items_Items3dData0[i].rotation_10.vy = 0;
        g_Items_Items3dData0[i].rotation_10.vx = 0;
        g_Items_Items3dData0[i].field_18.vz    = 0;
        g_Items_Items3dData0[i].field_18.vy    = 0;
        g_Items_Items3dData0[i].field_18.vx    = 0;
    }

    GameFs_TmdDataAlloc(FS_BUFFER_8);

    temp_s5 = (g_SysWork.inventoryItemSelectedIdx_2351 - 3 + g_SavegamePtr->inventorySlotCount_AB) % g_SavegamePtr->inventorySlotCount_AB;

    if (g_GameWork.gameStateStep_598[1] < 21) // If screen is inventory
    {
        for (inventoryItemsIdx = 0; inventoryItemsIdx < 7; inventoryItemsIdx++)
        {
            D_800C3E18[inventoryItemsIdx] = (temp_s5 + inventoryItemsIdx) % g_SavegamePtr->inventorySlotCount_AB;

            if (g_SavegamePtr->items_0[D_800C3E18[inventoryItemsIdx]].id_0 == 0xFF)
            {
                continue;
            }

            for (saveItemsIdx = 0; saveItemsIdx < INVENTORY_ITEM_COUNT_MAX; saveItemsIdx++)
            {
                if (g_SavegamePtr->items_0[D_800C3E18[inventoryItemsIdx]].id_0 == g_Item_MapLoadableItems[saveItemsIdx])
                {
                    Gfx_Items_Display(FS_BUFFER_8, inventoryItemsIdx, saveItemsIdx);
                    func_8005487C(inventoryItemsIdx);

                    saveItemsIdx = INVENTORY_ITEM_COUNT_MAX;
                }
            }
        }

        g_Inventory_EquippedItem = g_SavegamePtr->equippedWeapon_AA;

        for (i = 0; i < g_SavegamePtr->inventorySlotCount_AB; i++)
        {
            if (g_SavegamePtr->items_0[i].id_0 == g_Inventory_EquippedItem)
            {
                D_800C3E18[7] = i;

                i = g_SavegamePtr->inventorySlotCount_AB;
            }
        }

        if (g_Inventory_EquippedItemIdx != NO_VALUE) // If player has something equipped
        {
            for (saveItemsIdx = 0; saveItemsIdx < INVENTORY_ITEM_COUNT_MAX; saveItemsIdx++)
            {
                if (g_Inventory_EquippedItem == g_Item_MapLoadableItems[saveItemsIdx])
                {
                    Gfx_Items_Display(FS_BUFFER_8, 7, saveItemsIdx);
                    func_8005487C(7);

                    saveItemsIdx = INVENTORY_ITEM_COUNT_MAX;
                }
            }
        }

        g_Items_Items3dData1[7].coord.t[0] = 0;
        g_Items_Items3dData1[7].coord.t[1] = FP_METER(-0.15625f);
        g_Items_Items3dData1[7].coord.t[2] = 0;
    }
    else
    {
        u8 itemIds[] = // 0x8002848C .rodata
        {
            InventoryItemId_GasolineTank,
            InventoryItemId_Chainsaw,
            InventoryItemId_RockDrill,
            InventoryItemId_Katana,
            InventoryItemId_ChannelingStone,
            InventoryItemId_HyperBlaster
        };

        if (g_SavegamePtr->clearGameCount_24A == 0)
        {
            g_SavegamePtr->clearGameCount_24A = 1;
        }

        for (inventoryItemsIdx = 0; inventoryItemsIdx < 6; inventoryItemsIdx++)
        {
            D_800C3E18[inventoryItemsIdx] = inventoryItemsIdx;

            for (saveItemsIdx = 0; saveItemsIdx < INVENTORY_ITEM_COUNT_MAX; saveItemsIdx++)
            {
                if (itemIds[inventoryItemsIdx] == g_Item_MapLoadableItems[saveItemsIdx])
                {
                    Gfx_Items_Display(FS_BUFFER_8, inventoryItemsIdx, saveItemsIdx);
                    func_8005487C(inventoryItemsIdx);

                    saveItemsIdx = INVENTORY_ITEM_COUNT_MAX;
                }
            }
        }
    }
}

void Gfx_Items_RenderInit() // 0x80054558
{
    s32 i;

    D_800AE180                                 = 0;
    D_800AE187                                 = 0;
    g_Inventory_HealthStatusScanlineTimer      = 32;
    g_Inventory_HealthStatusColorGradientTimer = 0;
    D_800AE198                                 = 0;
    g_Inventory_HealthStatusScanlinePosition   = -300;
    g_Inventory_ItemNameTimer                  = 0;
    g_Inventory_DescriptionRollTimer           = 0;
    g_Inventory_ScrollTransitionTimer          = 0;

    for (i = 0; g_MapOverlayHeader.loadableItems_2C[i] != 0; i++)
    {
        g_Item_MapLoadableItems[i] = g_MapOverlayHeader.loadableItems_2C[i];
    }

    g_Item_MapLoadableItems[i] = 0;

    Gfx_Items_Render();
    Gfx_Items_SetAmbientLighting();
}

void Inventory_ExitAnimFixes() // 0x80054634
{
    u8 field_F;

    field_F                          = (u8)g_SysWork.playerCombatInfo_38.equippedWeapon_F;
    g_SavegamePtr->equippedWeapon_AA = g_Inventory_EquippedItem;

    if (g_SavegamePtr->equippedWeapon_AA)
    {
        g_SysWork.playerCombatInfo_38.equippedWeapon_F = g_SavegamePtr->equippedWeapon_AA + InventoryItemId_KitchenKnife;
    }
    else
    {
        g_SysWork.playerCombatInfo_38.equippedWeapon_F = NO_VALUE;
        g_SysWork.playerCombatInfo_38.isAiming_13      = false;
    }

    func_800546A8((u8)g_SysWork.playerCombatInfo_38.equippedWeapon_F);
    Inventory_ExitAnimEquippedItemUpdate(&field_F);
}

void func_800546A8(s32 arg0) // 0x800546A8
{
    switch ((u8)arg0)
    {
        case InventoryItemId_Unequipped:
            func_8003DD80(1, 34);
            break;

        case 1:
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
            func_8003DD80(1, 34);
            break;

        case InventoryItemId_HealthDrink:
        case InventoryItemId_FirstAidKit:
        case InventoryItemId_Ampoule:
            func_8003DD80(1, 19);
            break;

        default:
            func_8003DD80(1, 1);
            break;
    }
}

void Gfx_Items_Display(s_TmdFile* tmd, s32 arg1, s32 arg2) 
{
    u8                 var_v0;
    GsDOBJ2*           ptr;
    struct TMD_STRUCT* objs;

    objs = tmd->objects_C;

    GsLinkObject4((u32)&objs[arg2], &g_Items_ItemsModelData[arg1], 0);

    ptr         = &g_Items_ItemsModelData[arg1];
    ptr->coord2 = &g_Items_Items3dData1[arg1];

    if (D_800AE187 != 0)
    {
        var_v0 = D_800AE187;
    }
    else
    {
        var_v0 = g_MapOverlayHeader.loadableItems_2C[arg2];
    }

    switch (var_v0) 
    {
        case InventoryItemId_HealthDrink: 
        case InventoryItemId_FirstAidKit: 
        case InventoryItemId_Ampoule:
        case InventoryItemId_KitchenKnife: 
        case InventoryItemId_SteelPipe:
        case InventoryItemId_Hammer: 
        case InventoryItemId_Chainsaw:
        case InventoryItemId_Handgun: 
        case InventoryItemId_HuntingRifle: 
        case InventoryItemId_Shotgun:
        case InventoryItemId_HandgunBullets: 
        case InventoryItemId_RifleShells: 
        case InventoryItemId_ShotgunShells:
        case InventoryItemId_Flashlight: 
        case InventoryItemId_PocketRadio:
        case InventoryItemId_Axe:
            ptr->attribute = 0;
            break;

        default:
            ptr->attribute = 0x40000000;
            break;
    }

    if (D_800AE180 < 10)
    {
        D_800AE180++;
    }
}

void func_8005487C(s32 arg0) // 0x8005487C
{
    GsInitCoordinate2(NULL, &g_Items_Items3dData1[arg0]); // Initializes the coordinate system base.  base->coord is set to an identity matrix (GsIDMATRIX). super->sub is set to base.
    g_Items_Items3dData1[arg0].param = (GsCOORD2PARAM*) &g_Items_Items3dData0[arg0];
}

/** Something related to items lighting. */
void func_800548D8(s32 Idx) // 0x800548D8
{
    g_Items_ItemsLightingData[Idx][0].vx = g_Items_Items3dData1[Idx].coord.t[0];
    g_Items_ItemsLightingData[Idx][0].vy = g_Items_Items3dData1[Idx].coord.t[1];
    g_Items_ItemsLightingData[Idx][0].vz = g_Items_Items3dData1[Idx].coord.t[2] + 20000;
}

void Gfx_Items_SetAmbientLighting() // 0x80054928
{
    s32 i;

    for (i = 0; i < 10; i++)
    {
        g_Items_ItemsLightingData[i][0].r  = NO_VALUE;
        g_Items_ItemsLightingData[i][0].g  = NO_VALUE;
        g_Items_ItemsLightingData[i][0].b  = NO_VALUE;
        g_Items_ItemsLightingData[i][1].vx = FP_TO(1, Q12_SHIFT);
        g_Items_ItemsLightingData[i][1].vy = 0;
        g_Items_ItemsLightingData[i][1].vz = 0;
        g_Items_ItemsLightingData[i][1].r  = NO_VALUE;
        g_Items_ItemsLightingData[i][1].g  = NO_VALUE;
        g_Items_ItemsLightingData[i][1].b  = NO_VALUE;
    }

    GsSetAmbient(1024, 1024, 1024);
    GsSetLightMode(1);
}

// Similar to `Gfx_Items_SetAmbientLighting`.
void func_800549A0() // 0x800549A0
{
    #define IDX 9

    g_Items_ItemsLightingData[IDX][0].r  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].vx = FP_FLOAT_TO(1.0f, Q12_SHIFT);
    g_Items_ItemsLightingData[IDX][0].g  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][0].b  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].r  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].g  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].b  = NO_VALUE;
    g_Items_ItemsLightingData[IDX][1].vy = 0;
    g_Items_ItemsLightingData[IDX][1].vz = 0;

    GsSetAmbient(2048, 2048, 2048);
    GsSetLightMode(1);
}

void func_80054A04(u8 itemId) // 0x80054A04
{
    D_800AE187            = itemId;
    D_800AE180            = 0;
    g_PickupItemAnimState = 0;
    D_800AE1B0            = 0;

    D_800C3E18[9]                          = NO_VALUE;
    g_Items_Items3dData0[9].rotation_10.vz = 0;
    g_Items_Items3dData0[9].rotation_10.vy = 0;
    g_Items_Items3dData0[9].rotation_10.vx = 0;
    g_Items_Items3dData0[9].field_18.vz    = 0;
    g_Items_Items3dData0[9].field_18.vy    = 0;
    g_Items_Items3dData0[9].field_18.vx    = 0;

    GameFs_TmdDataAlloc(FS_BUFFER_5);

    D_800C3E18[9] = 0;

    Gfx_Items_Display(FS_BUFFER_5, 9, 0);
    func_8005487C(9);

    g_Items_Items3dData0[9].scale_0.vz = FP_FLOAT_TO(1.0f, Q12_SHIFT);
    g_Items_Items3dData0[9].scale_0.vy = FP_FLOAT_TO(1.0f, Q12_SHIFT);
    g_Items_Items3dData0[9].scale_0.vx = FP_FLOAT_TO(1.0f, Q12_SHIFT);

    func_800549A0();
    Gfx_ItemScreens_CameraSet(&D_800C3B48, &D_800C3AE8, &D_800C3B38, 0);
}

bool Gfx_PickupItemAnimate(u8 itemId) // 0x80054AD8
{
    s32            temp_a1;
    s16            x;
    s16            y;
    GsDOBJ2*       obj;
    s_Items3dData* ptr;

    g_Items_Items3dData1[9].coord.t[1] = 0x40;
    g_Items_Items3dData1[9].coord.t[0] = 0;
    g_Items_Items3dData1[9].coord.t[2] = -0x20B0;

    switch (g_PickupItemAnimState) 
    {
        case 0:
            if (D_800AE1B0 >= 0x800) 
            {
                g_PickupItemAnimState = 1;
            }

            ptr     = &g_Items_Items3dData0[0];
            temp_a1 = D_800AE1B0 << 12;

            x = g_InventoryItemRotations[itemId - 32].vx;
            y = g_InventoryItemRotations[itemId - 32].vy;

            ptr[9].scale_0.vz     = temp_a1 >> 11;
            ptr[9].scale_0.vy     = temp_a1 >> 11;
            ptr[9].scale_0.vx     = temp_a1 >> 11;

            ptr[9].rotation_10.vx = x;
            ptr[9].rotation_10.vy = 0;
            ptr[9].rotation_10.vz = y;
            break;

        case 1:
            g_Items_Items3dData0[9].scale_0.vz = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[9].scale_0.vy = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_Items_Items3dData0[9].scale_0.vx = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            g_PickupItemAnimState = 2;
            break;
    }

    D_800AE1B0 += (g_DeltaTime1 * 2);
    D_800AE1B0  = CLAMP(D_800AE1B0, 0, 0x800);

    PushMatrix();
    func_8004BBF4(&D_800C3B48, &D_800C3AE8, &D_800C3B38);

    obj = &D_800C3E08;

    Gfx_Items_ItemRotate(&g_Items_Items3dData1[9].param->rotate, &g_Items_Items3dData1[9]);

    g_Items_Items3dData0[9].rotation_10.vy += g_DeltaTime1 >> 1;

    func_800548D8(9);
    GsSetFlatLight(0, &D_800C3AC8[0]);
    GsSetFlatLight(1, &D_800C3AC8[1]);
    func_8004BD74(9, obj, 2);
    PopMatrix();

    return g_PickupItemAnimState > 0;
}

void Inventory_AddSpecialItem(u8 itemId, s32 itemCount) // 0x80054CAC
{
    switch (itemId)
    {
        case InventoryItemId_RockDrill:
        case InventoryItemId_Chainsaw:
        case InventoryItemId_Katana:
        case InventoryItemId_HyperBlaster:
        case InventoryItemId_GasolineTank:
            g_SavegamePtr->pickedUpSpecialItemCount_25C_3++;
            break;

        case InventoryItemId_ChannelingStone:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_ChannelingStone))
            {
                g_SavegamePtr->pickedUpSpecialItemCount_25C_3++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_ChannelingStone; // `specialItemFlags`?
            }
            break;

        case InventoryItemId_PlateOfTurtle:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_PlateOfTurtle))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_PlateOfTurtle;
            }
            break;

        case InventoryItemId_PlateOfHatter:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_PlateOfHatter))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_PlateOfHatter;
            }
            break;

        case InventoryItemId_PlateOfCat:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_PlateOfCat))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_PlateOfCat;
            }
            break;

        case InventoryItemId_PlateOfQueen:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_PlateOfQueen))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_PlateOfQueen;
            }
            break;

        case InventoryItemId_Lighter:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_Lighter))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_Lighter;
            }
            break;

        case InventoryItemId_VideoTape:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_VideoTape))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_VideoTape;
            }
            break;

        case InventoryItemId_Camera:
            if (!(g_SavegamePtr->field_23F & InventoryItemFlag_Camera))
            {
                g_SavegamePtr->pickedUpItemCount_23C++;
                g_SavegamePtr->field_23F |= InventoryItemFlag_Camera;
            }
            break;

        default:
            g_SavegamePtr->pickedUpItemCount_23C++;
            break;
    }

    g_SavegamePtr->items_0[g_SavegamePtr->inventorySlotCount_AB].id_0    = itemId;
    g_SavegamePtr->items_0[g_SavegamePtr->inventorySlotCount_AB].count_1 = itemCount;
    g_SavegamePtr->inventorySlotCount_AB                                 = func_8004F190(g_SavegamePtr);
}

void Items_AmmoReloadCalculation(s32* currentAmmo, s32* availableAmmo, u8 gunIdx) // 0x80054FC0
{
    s32 missingAmmo;

    missingAmmo = g_Items_GunsMaxLoadAmmo[gunIdx] - *currentAmmo;
    if (missingAmmo == 0)
    {
        return;
    }

    if (*availableAmmo >= missingAmmo)
    {
        *currentAmmo   += missingAmmo;
        *availableAmmo -= missingAmmo;
        return;
    }
	else
	{
		*currentAmmo  += *availableAmmo;
		*availableAmmo = 0;
		return;
	}
}

// Likely the first pad is supposed to be generated in the file linking while the second being inserted at `bodyprog_80055028.c` directly.
const s32 rodataPad_80028524 = 0;
const s32 rodataPad_80028528 = 0;
