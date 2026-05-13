#ifndef _BODYPROG_CHARA_H
#define _BODYPROG_CHARA_H

#include "bodyprog/anim.h"
#include "bodyprog/model.h"
#include "bodyprog/math/math.h"

#define NPC_COUNT_MAX        6
#define NPC_BONE_COUNT_MAX   10 * NPC_COUNT_MAX
#define CHARA_GROUP_COUNT    4 /** While up to 6 NPCs and a player can exist in the game world, only 4 different character
                                * types (including the player) can be loaded at a time.
                                */
#define CHARA_FORCE_FREE_ALL 0xFF /** `Chara_Load` can force free already loaded models to make room for new ones. */

// Collision-related.
typedef struct
{
    VECTOR3 position;
    s16     field_C;
    s16     field_E;
    s16     field_10;
    s8      collisionState; /** `e_CharaCollisionState` */
    u8      field_13;
} s_func_8006CF18;

/** @brief Character damage info. */
typedef struct _CharaDamage
{
    /* 0x0 */ VECTOR3 position;
    /* 0xC */ q19_12  amount;
} s_CharaDamage;

typedef union
{
    s32 val32;
    s16 val16[2];
    s8  val8[4];
} u_Property;

/** @brief Temporary struct. */
typedef struct _PropsDummy
{
    u_Property properties_E8[16];
} s_PropsDummy;
STATIC_ASSERT_SIZEOF(s_PropsDummy, 64);

/** @brief Player character properties. */
typedef struct _PropsPlayer
{
    /* 0xE8  */ q19_12        afkTimer; // Increments every tick for 10 seconds before AFK anim starts.
    /* 0xEC  */ q19_12        groundHeight;
    /* 0xF0  */ q19_12        field_F0;
    /* 0xF4  */ q19_12        field_F4; // Angle related to X axis flex rotation.
    /* 0xF8  */ q19_12        runTimer_F8;
    /* 0xFC  */ q19_12        exhaustionTimer;
    /* 0x100 */ q19_12        field_100;    // Angle?
    /* 0x104 */ q19_12        field_104;    // Distance?
    /* 0x108 */ q19_12        runTimer_108;
    /* 0x10C */ u8            field_10C;    // Player SFX pitch?
    /* 0x10D */ u8            field_10D;
    /* 0x10E */ s8            __pad_10E[2];
    /* 0x110 */ q19_12        timer_110; // Increases when `flags & CharaFlag_Unk4` is set, reset when reaches `D_800C45EC`.
    /* 0x114 */ q19_12        gasWeaponPowerTimer; // Timer for the rock drill and chainsaw power.
    /* 0x118 */ s16           field_118; // q3_12?
    /* 0x11A */ s8            __pad_11A[2];
    /* 0x11C */ s32 flags_11C; /** `e_PlayerFlags` */
    /* 0x120 */ q3_12         quickTurnHeadingAngle; /** Target quick turn heading angle. */
    /* 0x122 */ q3_12         field_122; // Specially used when aiming an enemy. Y angle delta to target? 
    /* 0x124 */ q3_12         headingAngle;
    /* 0x126 */ q3_12         moveDistance_126; // Used to indicate how much the player should move foward. Seems to be squared.
} s_PropsPlayer;
STATIC_ASSERT_SIZEOF(s_PropsPlayer, 64);

// TODO: Unsure if this struct is puppet doctor specific or shared with all characterss. Pointer gets set at puppetDoc+0x124.
typedef struct
{
    q19_12      health_0;
    s32         field_4;
    s32         field_8;
    s32         field_C;
    s8          unk_10[8];
    s32         field_18;
    s32         idx_1C;
    s32         field_20;
    s_AnimInfo* animInfo_24;
    s8          unk_28[4];
    q19_12      field_2C;
    s8          unk_30[4];
} s_800D5710;
STATIC_ASSERT_SIZEOF(s_800D5710, 52);

// TODO: This may be a puppet doctor/nurse specific struct, need to compare with other NPCs.
typedef struct _PropsNpc
{
    VECTOR3     position_E8; /** Q19.12 */
    s32         field_F4;
    s32         field_F8;
    s32         field_FC;
    s32         field_100;
    s32         field_104;
    s32         field_108;
    s32         field_10C;
    s8          unk_110[4];
    s32         field_114;
    s8          field_118;
    u8          modelVariantIdx;
    s16         field_11A;
    s32         field_11C;
    s16         field_120;
    s16         field_122;
    s_800D5710* field_124;
} s_PropsNpc;
STATIC_ASSERT_SIZEOF(s_PropsNpc, 64);

/** @brief Air Screamer or Night Flutter character properties. */
typedef struct _PropsAirScreamer
{
    /* 0xE8+0  */ u32     field_E8_0  : 4; // `AirScreamerHit_None` step.
    /* 0xE8+4  */ u32     field_E8_4  : 4; /** `bool` */
    /* 0xE8+8  */ u32     field_E8_8  : 4;
    /* 0xE8+12 */ u32     __pad_E8_12 : 20;
    /* 0xEC    */ s32     field_EC;
    /* 0xF0    */ s16     field_F0; // } Maybe 2D offset like in Creeper properties? Must check.
    /* 0xF2    */ s16     field_F2; // }
    /* 0xF4    */ s32     field_F4;
    /* 0xF8    */ VECTOR3 targetPosition; /** Q19.12 */
    /* 0x104   */ VECTOR3 position_104;   /** Q19.12 | Set to either Air Screamer position with slight offset toward player or player position. */
    /* 0x110   */ VECTOR3 position_110;
    /* 0x11C   */ s32     flags; /** `e_AirScreamerFlags` */
    /* 0x120   */ q19_12  timer_120;
    /* 0x124   */ q19_12  groundHeight;
} s_PropsAirScreamer;

/** @brief Alessa character properties. */
typedef struct _PropsAlessa
{
    /* 0xE8  */ s32        controlState; /** `e_AlessaControl` */
    /* 0xEC  */ u_Property properties_EC; // Unused.
    /* 0xF0  */ bool       freeze;
    /* 0xF4  */ u_Property properties_F4; // Unused.
    /* 0xF8  */ bool       resetControlState;
    /* 0xFC  */ s32        field_FC;
    /* 0x100 */ s32        field_100;
    /* 0x104 */ u_Property properties_104;
    /* 0x108 */ u_Property properties_108;
    /* 0x10C */ u_Property properties_10C;
    /* 0x110 */ VECTOR3    field_110;
    /* 0x11C */ s32        flags_11C;
    /* 0x120 */ u_Property properties_120;
    /* 0x124 */ q3_12      field_124;
    /* 0x126 */ q3_12      moveSpeed;
} s_PropsAlessa;

/** @brief Bloodsucker character properties. */
typedef struct _PropsBloodsucker
{
    q19_12 timer_E8;
    q19_12 timer_EC;
    q19_12 timer_F0;
    q19_12 timer_F4;
    s8     unused_F8[36]; /** @unused */
    s32    flags;         /** `e_BloodsuckerFlags` */
} s_PropsBloodsucker;


/** @brief Cheryl character properties. */
typedef struct _PropsCheryl
{
    /* 0xE8  */ s32        controlState; /** `e_CherylControl` */
    /* 0xEC  */ u_Property properties_EC; // Unused?
    /* 0xF0  */ s32        field_F0;
    /* 0xF4  */ u_Property properties_F4; // Unused?
    /* 0xF8  */ bool       resetControlState;
    /* 0xFC  */ s32        field_FC;
    /* 0x100 */ s32        field_100;
    /* 0x104 */ u_Property properties_104;
    /* 0x108 */ u_Property properties_108;
    /* 0x10C */ u_Property properties_10C;
    /* 0x110 */ VECTOR3    field_110;
    /* 0x11C */ s32        flags; /** `e_CherylFlags` */
    /* 0x120 */ u_Property properties_120;
    /* 0x124 */ q3_12      moveDistance_124;
    /* 0x126 */ q3_12      moveDistance_126;
} s_PropsCheryl;
STATIC_ASSERT_SIZEOF(s_PropsCheryl, 64);

/** @brief Creeper character properties. */
typedef struct _PropsCreeper
{
    /* 0xE8  */ u16    flags; /** `e_CreeperFlags` */
    /* 0xEA  */ s8     __pad_EA[2];
    /* 0xEC  */ q3_12  collisionOffsetX;
    /* 0xEE  */ q3_12  collisionOffsetZ;
    /* 0xF0  */ q19_12 attackTimer;
    /* 0xF4  */ q19_12 targetPositionX;
    /* 0xF8  */ q19_12 targetPositionZ;
    /* 0xFC  */ q19_12 homePositionX;
    /* 0x100 */ q19_12 homePositionZ;
    /* 0x104 */ q19_12 chirpTimer;
    /* 0x108 */ q3_12  angleToTarget;
    /* 0x10A */ s16    animStatus_10A; // TODO: Purpose unclear.
    /* 0x10C */ q4_12  moveSpeed;
} s_PropsCreeper;
STATIC_ASSERT_SIZEOF(s_PropsCreeper, 40);

/** @brief Dahlia character properties. */
typedef struct _PropsDahlia
{
    /* 0x0   */ s32        controlState; /** `e_DahliaControl` */
    /* 0xEC  */ u_Property properties_EC; // Unused?
    /* 0xF0  */ u_Property properties_F0; // Unused?
    /* 0xF4  */ u_Property properties_F4; // Unused?
    /* 0xF8  */ bool       resetControlState;
    /* 0xFC  */ s32        field_FC;
    /* 0x100 */ s32        field_100;
    /* 0x104 */ u_Property properties_104;
    /* 0x108 */ u_Property properties_108;
    /* 0x10C */ u_Property properties_10C;
    /* 0x110 */ VECTOR3    field_110;
    /* 0x11C */ s32        flags_11C;
    /* 0x120 */ u_Property properties_120;
    /* 0x124 */ q3_12      field_124;
    /* 0x126 */ q3_12      moveDistance_126;
} s_PropsDahlia;
STATIC_ASSERT_SIZEOF(s_PropsDahlia, 64);

/** @brief Floatstinger character properties. */
typedef struct _PropsFloatstinger
{
    s16        flags_E8;
    s8         unk_EA[4];
    q3_12      field_EE; // Angle.
    q19_12     field_F0;
    s16        field_F4;
    s8         __pad_F6[2];
    u16        field_F8;
    u16        field_FA;
    u16        field_FC;
    s8         __pad_FE[2];
    s32        field_100;
    u8         field_104;
    s8         __pad_105;
    s16        field_106;
    s32        field_108;
    s16        field_10C;
    q3_12      field_10E;
    u_Property properties_110[6];
} s_PropsFloatstinger;
STATIC_ASSERT_SIZEOF(s_PropsFloatstinger, 64);

/** @brief Groaner character properties. */
typedef struct _PropsGroaner
{
    /* 0xE8  */ u_Property flags; /** `e_GroanerFlags` TODO: One weird exception where it's accessed as `s32`. */
    /* 0xEC  */ q3_12      targetHeadingAngle;
    /* 0xEE  */ q3_12      flexAngle;
    /* 0xF0  */ q3_12      field_F0;
    /* 0xF2  */ q3_12      field_F2;
    /* 0xF4  */ q19_12     targetPositionX;
    /* 0xF8  */ q19_12     targetPositionZ;
    /* 0xFC  */ q3_12      angleToTarget;
    /* 0xFE  */ q3_12      field_FE;
    /* 0x100 */ u16        relKeyframeIdx_100;
    /* 0x102 */ s8         __pad_102[2];
    /* 0x104 */ q19_12     timer_104;
    /* 0x108 */ u32        field_108;
    /* 0x10C */ q3_12      timer_10C; // SFX timer?
    /* 0x10E */ u8         field_10E; // } Sound states?
    /* 0x10F */ u8         field_10F; // }
    /* 0x110 */ u8         playLeftFootstepSfx;  /** `bool` */
    /* 0x111 */ u8         playRightFootstepSfx; /** `bool` */
    /* 0x112 */ s8         __pad_112[2];
    /* 0x114 */ q3_12      field_114; // Move speed coefficient?
} e_PropsGroaner;

/** @brief Hanged Scratcher character properties. */
typedef struct _PropsHangedScratcher
{
    s16    flags_E8; /** `e_HangedScratcherFlags` */
    q4_12  timer_EA;
    q3_12  targetHeadingAngle_EC;
    u8     field_EE;
    s8     __pad_EF;
    q3_12  offsetX_F0; // } Offsets passed to `func_8005CB20`
    q3_12  offsetZ_F2; // }
    q19_12 positionX_F4;
    q19_12 positionZ_F8;
    q3_12  field_FC;
    s8     __pad_FE[2];
    q3_12  timer_100;
    u8     field_102;
    u8     field_103;
    s32    field_104;
    q3_12  timer_108;
    s8     __pad_10A[2];
    q4_12  radiusMax_10C; // } Used as `Chara_MoveSpeedUpdate` limit param, TODO: rename?
    q4_12  radiusMin_10E; // }
} s_PropsHangedScratcher;

/** @brief Incubus or Incubator character properties. TODO: Check which one. */
typedef struct _PropsIncubus
{
    q19_12 timer_E8;
    s32    field_EC;
    s32    someState_F0;
    q19_12 bossFightTimer_F4;
    s8     __pad_F8[48];
} s_PropsIncubus;

/** @brief Kaufmann character properties. TODO: Largely a copy of Dahlia's for now. */
typedef struct _PropsKaufmann
{
    /* 0x0   */ s32        controlState; /** `e_KaufmannControl` */
    /* 0xEC  */ u_Property properties_EC; // Unused?
    /* 0xF0  */ u_Property properties_F0; // Unused?
    /* 0xF4  */ u_Property properties_F4; // Unused?
    /* 0xF8  */ bool       resetControlState;
    /* 0xFC  */ s32        field_FC;
    /* 0x100 */ s32        field_100;
    /* 0x104 */ u_Property properties_104;
    /* 0x108 */ u_Property properties_108;
    /* 0x10C */ u_Property properties_10C;
    /* 0x110 */ VECTOR3    field_110;
    /* 0x11C */ s32        flags_11C;
    /* 0x120 */ s32        field_120;
    /* 0x124 */ q3_12      field_124;
    /* 0x126 */ q3_12      moveSpeed;
} s_PropsKaufmann;
STATIC_ASSERT_SIZEOF(s_PropsKaufmann, 64);

/** @brief Larval Stalker character properties. */
typedef struct _PropsLarvalStalker
{
    /* 0x */ u16        flags_E8; /** `e_LarvalStalkerFlags` */
    /* 0x */ u8         field_EA;
    /* 0x */ s8         __pad_EB;
    /* 0x */ q19_12     timer_EC;
    /* 0x */ q20_12     timer_F0;
    /* 0x */ s16        keyframeIdx_F4; // Relative keyframe?
    /* 0x */ s16        keyframeIdx_F8; // Relative keyframe?
    /* 0x */ q19_12     targetPositionX;
    /* 0x */ q19_12     targetPositionZ;
    /* 0x */ q3_12      angle_100;
    /* 0x */ q3_12      angle_102;
    /* 0x */ q19_12     animTime_104;
    /* 0x */ q3_12      angle_108;
    /* 0x */ q4_12      timer_10A;
    /* 0x */ u_Property field_10C;
    /* 0x */ VECTOR3    field_110;
    /* 0x */ s32        flags_11C;
    /* 0x */ u_Property field_120;
    /* 0x */ s16        field_124;
    /* 0x */ q3_12      moveDistance_126;
} s_PropsLarvalStalker;
STATIC_ASSERT_SIZEOF(s_PropsLarvalStalker, 64);

/** @brief Monster Cybil character properties. */
typedef struct _PropsMonsterCybil
{
    s32    field_E8;
    s16    field_EC;
    s16    field_EE; // Anim index?
    q19_12 field_F0; // Timer.
    s32    field_F4;
    q19_12 field_F8; // Timer.
    s8     __pad_FC[2];
    q3_12  field_FE; // Angle?
    q19_12 field_100;
    s16    field_104;
    q3_12  field_106; // Angle.
    s32    field_108;
    q19_12 field_10C; // Timer.
    q19_12 field_110; // Distance?
    u8     field_114;
    u8     field_115;
    u8     field_116;
    s8     __pad_117;
    s16    field_118;
    q3_12  field_11A; // Angle.
    s16    field_11C;
    s16    field_11E;
    s16    field_120;
    s16    field_122;
    s8     __pad_124[2];
    s16    field_126;
} s_PropsMonsterCybil;
STATIC_ASSERT_SIZEOF(s_PropsMonsterCybil, 64);

/** @brief Puppet Nurse or Puppet Doctor character properties. */
typedef struct _PropsPuppetNurse
{
    /* 0xE8  */ VECTOR3       position_E8; /** Q19.12 */
    /* 0xF4  */ s_CharaDamage damage;
    /* 0x104 */ q19_12        field_104;
    /* 0x108 */ s32           field_108;
    /* 0x10C */ s32           field_10C;
    /* 0x110 */ q19_12        moveSpeed;
    /* 0x114 */ s32           field_114;
    /* 0x118 */ u8            field_118;
    /* 0x119 */ u8            modelVariantIdx;
    /* 0x11A */ u16           field_11A;
    /* 0x11C */ q3_12         field_11C; // Angle.
    /* 0x11E */ s16           field_11E;
    /* 0x120 */ s16           field_120;
    /* 0x122 */ u16           flags_122; /** `e_PuppetNurseFlags` */
    /* 0x124 */ s_800D5710*   field_124;
} s_PropsPuppetNurse;
STATIC_ASSERT_SIZEOF(s_PropsPuppetNurse, 64);

/** @brief Romper character properties. */
typedef struct _PropsRomper
{
    /* 0xE8 */ s32    flags; /** `e_RomperFlags` */
               q3_12  angle_EC; // Target heading angle?
               s16    field_EE;
               q3_12  field_F0; // Move speed accumulation for this tick.
               q3_12  rotationY_F2;
               q19_12 field_F4; // Relative anim time?
    /* 0xF8 */ q3_12  movementOffsetX;
    /* 0xFA */ q3_12  movementOffsetZ;
               q19_12 targetPositionX_FC;
               q19_12 targetPositionZ_100;
               s32    field_104;
               q19_12 positionX_108;
               u8     field_10C; // Relative keyframe index?
               s8     __pad_10D;
               u16    field_10E;
               q19_12 positionZ_110;
               u8     field_114;
               u8     field_115;
               q3_12  field_116;
               q3_12  timer_118;
               u8     field_11A;
               s8     __pad_11B;
               q3_12  timer_11C;
               s8     __pad_11E[2];
               q19_12 distance_120;
               q19_12 field_124; // Move speed step?
} s_PropsRomper;

/** @brief Split Head character properties. */
typedef struct _PropsSplitHead
{
    u16     flags; /** `e_SplitHeadFlags` */
    u8      field_EA;
    s8      __pad_EB;
    q3_12   angle_EC;
    q3_12   field_EE;
    q4_12   angle_F0;
    q4_12   timer_F2;
    q4_12   timer_F4;
    s8      __pad_F8[2];
    q19_12  animTime_F8;
    s32     field_FC;
    s32     field_100;
    s8      unk_104[4];
    u8      field_108[4];
    q19_12  field_10C;
    VECTOR3 field_110;
    s32     flags_11C; /** `e_SplitHeadFlags` */
    s8      unk_120[4];
    s16     field_124;
    q3_12   moveDistance_126;
} s_PropsSplitHead;
STATIC_ASSERT_SIZEOF(s_PropsSplitHead, 64);

/** @brief Stalker character properties. */
typedef struct _PropsStalker
{
    /* 0xE8  */ s16    flags; /** `e_StalkerFlags` */
    /* 0xEA  */ s8     __pad_EA[2];
    /* 0xEC  */ q3_12  offset_EC;
    /* 0xEE  */ q3_12  offset_EE;
    /* 0xF0  */ q19_12 targetPositionX;
    /* 0xF4  */ q19_12 targetPositionZ;
    /* 0xF8  */ q19_12 timer_F8;
    /* 0xFC  */ s16    keyframeIdx_FC;    // Or anim status?? Seems to be used as both.
    /* 0xFE  */ s16    relKeyframeIdx_FE; // Unsure.
    /* 0x100 */ q3_12  targetHeadingAngle;
    /* 0x102 */ s16    sfxId_102;
    /* 0x104 */ q19_12 relAnimTime_104;
    /* 0x108 */ q4_12  timer_108;
    /* 0x10A */ u8     field_10A;
    /* 0x10B */ s8     __pad_10B;
    /* 0x10C */ q19_12 timer_10C;
    /* 0x110 */ q19_12 health_110;
    /* 0x114 */ q3_12  angle_114;
    /* 0x116 */ q4_12  timer_116;
} s_PropsStalker;

/** @brief Twinfeeler character properties. */
typedef struct _PropsTwinfeeler
{
    // TODO: Weird `field_E8` access.
    /* 0xE8  */ u_Property    field_E8;
    /* 0xE8  */ //q3_12         sfxTimer_E8;
    /* 0xE8  */ //q4_12         field_EA;
    /* 0xEC  */ s_CharaDamage damage;
    /* 0xFC  */ q19_12        digTimer;
    /* 0x100 */ q19_12        spawnPositionX; /** @unused */
    /* 0x104 */ q19_12        spawnPositionZ; /** @unused */
    /* 0x108 */ q19_12        prevMoveSpeed;
    /* 0x10C */ q19_12        accumulatedDamage;
    /* 0x110 */ s16           field_110; /** @unused */
    /* 0x112 */ s8            __pad_112[2];
    /* 0x114 */ u32           flags;     /** `e_TwinfeelerFlags` */
    /* 0x118 */ u16           field_118; /** `bool` */
    /* 0x11C */ s8            __pad_11C[2]; // TODO: Should be `s32 prevHealth`.
    /* 0x120 */ s32           field_120; /** @unused */
    /* 0x124 */ s8            __pad_124[8];
} s_PropsTwinfeeler;
STATIC_ASSERT_SIZEOF(s_PropsTwinfeeler, 64);

typedef struct
{
    s16     field_0; // Something dependent on `CharaFlag_Unk8`.
    u8      field_2; // In player: packed weapon attack. See `WEAPON_ATTACK`.
                     // This is not the same as `attackReceived`, as this value only resets when player is aiming.
                     // In NPCs: Indicates attack performed on player.
    u8      field_3;
    u8      field_4;
    s8      __pad_5[3];
    s32     field_8;  // } Fields used by `func_8008A3E0`. Types guessed for now.
    s16     field_C;  // } Angle?
    s16     field_E;  // } Angle?
    s16     field_10; // }
    s16     field_12; // }
    s32     field_14; // }
    VECTOR3 field_18; // Q19.12 | Set to player attack position.
    VECTOR3 field_24[3];
    VECTOR3 field_48[3];
} s_SubCharacter_44;

/** @brief Character collision box. */
typedef struct _CharaBox
{
    /* 0x0 */ q3_12 top;
    /* 0x2 */ q3_12 bottom;
    /* 0x4 */ q3_12 height;
    /* 0x6 */ q3_12 offsetY;
    /* 0x8 */ q3_12 field_8; // X extent?? Always negative, but why?
    /* 0xA */ q3_12 field_A; // Z extent??
} s_CharaBox;
STATIC_ASSERT_SIZEOF(s_CharaBox, 12);

/** @brief Character collision cylinder. */
typedef struct _CharaCylinder
{
    /* 0x0 */ q3_12 radius;
    /* 0x2 */ q3_12 field_2; // Secondary radius?
} s_CharaCylinder;
STATIC_ASSERT_SIZEOF(s_CharaCylinder, 4);

/** @brief Character shape offsets for `s_CharaBox` and `s_CharaCylinder`. */
typedef struct _CharaShapeOffsets
{
    /* 0x0 */ DVECTOR_XZ box;
    /* 0x4 */ DVECTOR_XZ cylinder;
} s_CharaShapeOffsets;
STATIC_ASSERT_SIZEOF(s_CharaShapeOffsets, 8);

/** @brief Character keyframe collision info. */
typedef struct _Keyframe
{
    /* 0x0 */ s_CharaBox          box;
    /* 0xC */ s_CharaShapeOffsets shapeOffsets;
} s_Keyframe;

/** @brief Character collision info for the active animation frame. */
typedef struct _CharaCollision
{
    /* 0x0    */ s_CharaBox          box;
    /* 0xC    */ s_CharaCylinder     cylinder;
    /* 0x10   */ s_CharaShapeOffsets shapeOffsets;   // Translation data?
    /* 0x18+0 */ u8                  field_E0;       // Related to collision. If the player collides with the only enemy in memory and the enemy is knocked down, this is set to 1.
    /* 0x19+0 */ s8                  state      : 4; /** `e_CharaCollisionState` */
    /* 0x19+4 */ u8                  field_E1_4 : 4; // Index for array of `s_func_8006CF18`.
    /* 0x1C   */ s_func_8006CF18*    field_E4;
} s_CharaCollision;

/** @brief Character info. */
typedef struct _SubCharacter
{
    /* 0x0  */ s_Model           model;    // In player: Manage the half lower part of Harry's body animations (legs and feet).
    /* 0x18 */ VECTOR3           position; /** Q19.12 */
    /* 0x24 */ SVECTOR3          rotation; /** Q3.12 */
    /* 0x2A */ q3_12             angleToTarget;
    /* 0x2C */ SVECTOR3          rotationSpeed;              /** Q3.12 | Rotation speed for `rotation`. */
    /* 0x32 */ q3_12             angleToTargetRotationSpeed; /** Rotation speed for `angleToTarget`. */
    /* 0x34 */ q19_12            fallSpeed;
    /* 0x38 */ q19_12            moveSpeed;
    /* 0x3C */ q3_12             headingAngle;
    /* 0x3E */ s16               flags;          /** `e_CharaFlags` */
    /* 0x40 */ s8                field_40;       // In player: Index of the NPC attacking the player.
                                                 // In NPCs: Unknown. `Game_NpcRoomInitSpawn` sugests it indicates the NPC index in `s_Savegame::ovlEnemyStates`.
    /* 0x41 */ s8                attackReceived; // Packed weapon attack indicating what attack has been performed to the character. See `WEAPON_ATTACK`.
               // 2 bytes of padding.
    /* 0x44 */ s_SubCharacter_44 field_44;
    /* 0xB0 */ q19_12            health;
    /* 0xB4 */ s_CharaDamage     damage;
    /* 0xC4 */ u16               deathTimer;     // Part of `shBattleInfo` struct in SH2, may use something similar here.
    /* 0xC6 */ q3_12             timer_C6;       // Some sort of timer. Written to by `LarvalStalker_Update`.
    /* 0xC8 */ s_CharaCollision  collision;
               union
               {
                   s_PropsDummy           dummy;
                   s_PropsPlayer          player;
                   s_PropsNpc             npc;
               
                   s_PropsAirScreamer     airScreamer;
                   s_PropsAlessa          alessa;
                   s_PropsBloodsucker     bloodsucker;
                   s_PropsCheryl          cheryl;
                   s_PropsCreeper         creeper;
                   s_PropsDahlia          dahlia;
                   s_PropsFloatstinger    floatstinger;
                   e_PropsGroaner         groaner;
                   s_PropsHangedScratcher hangedScratcher;
                   s_PropsIncubus         incubus;
                   s_PropsKaufmann        kaufmann;
                   s_PropsLarvalStalker   larvalStalker;
                   s_PropsMonsterCybil    monsterCybil;
                   s_PropsPuppetNurse     puppetNurse;
                   s_PropsRomper          romper;
                   s_PropsSplitHead       splitHead;
                   s_PropsStalker         stalker;
                   s_PropsTwinfeeler      twinfeeler;
    /* 0xE8 */ } properties;
} s_SubCharacter;
STATIC_ASSERT_SIZEOF(s_SubCharacter, 296);

/** @brief Sets the collision shapes of a character from keyframe collision data.
 *
 * @param chara Character to update (`s_SubCharacter`).
 * @param keyframe Keyframe collision data (`s_Keyframe`).
 */
#define Chara_CollisionSet(chara, keyframe)                                         \
{                                                                                   \
    s32 __temp;                                                                     \
                                                                                    \
    chara->collision.box.top = keyframe.box.top;                                    \
                                                                                    \
    __temp                      = keyframe.box.bottom;                              \
    chara->collision.box.bottom = __temp;                                           \
    chara->collision.box.height = keyframe.box.height;                              \
                                                                                    \
    __temp                                    = keyframe.box.offsetY;               \
    chara->collision.box.offsetY              = __temp;                             \
    chara->collision.shapeOffsets.cylinder.vx = keyframe.shapeOffsets.cylinder.vx;  \
                                                                                    \
    __temp                                    = keyframe.shapeOffsets.cylinder.vz;  \
    chara->collision.shapeOffsets.cylinder.vz = __temp;                             \
    chara->collision.cylinder.radius          = keyframe.box.field_8;               \
    chara->collision.shapeOffsets.box.vx      = keyframe.shapeOffsets.box.vx;       \
                                                                                    \
    __temp                               = keyframe.shapeOffsets.box.vz;            \
    chara->collision.shapeOffsets.box.vz = __temp;                                  \
                                                                                    \
    __temp                            = keyframe.box.field_A;                       \
    chara->collision.cylinder.field_2 = __temp;                                     \
}

/** @brief Alternative to `Chara_CollisionSet`. TODO: Can they be merged into one? */
#define Chara_CollisionSetAlt(chara, keyframe)                                     \
{                                                                                  \
    s32 __temp;                                                                    \
    s32 __temp2;                                                                   \
                                                                                   \
    chara->collision.box.top = keyframe.box.top;                                   \
                                                                                   \
    __temp                      = keyframe.box.bottom;                             \
    chara->collision.box.bottom = __temp;                                          \
    chara->collision.box.height = keyframe.box.height;                             \
                                                                                   \
    __temp                       = keyframe.box.offsetY;                           \
    chara->collision.box.offsetY = __temp;                                         \
    chara->collision.shapeOffsets.cylinder.vx = keyframe.shapeOffsets.cylinder.vx; \
                                                                                   \
    __temp                                    = keyframe.shapeOffsets.cylinder.vz; \
    chara->collision.shapeOffsets.cylinder.vz = __temp;                            \
    chara->collision.cylinder.radius          = keyframe.box.field_8;              \
    chara->collision.shapeOffsets.box.vx      = keyframe.shapeOffsets.box.vx;      \
                                                                                   \
    __temp                               = keyframe.shapeOffsets.box.vz;           \
    chara->collision.shapeOffsets.box.vz = __temp;                                 \
                                                                                   \
    __temp2                           = keyframe.box.field_A;                      \
    chara->collision.cylinder.field_2 = __temp2;                                   \
}

/** @brief Checks if the `s_SubCharacter*` has the given `flags` value set. */
#define Chara_HasFlag(chara, flag) \
    ((chara)->flags & (flag))

/** @brief Clears a character's properties. TODO: Declare `i` here.
 *
 * @param chara Character to update.
 */
#define Chara_PropsClear(chara)                             \
    for (i = 0; i < 16; i++)                                \
    {                                                       \
        chara->properties.dummy.properties_E8[i].val32 = 0; \
    }

/** @brief Clears a character's damage field.
 *
 * @param chara Character to update.
 */
#define Chara_DamageClear(chara)             \
    (chara)->damage.amount      = Q12(0.0f); \
    (chara)->damage.position.vz = Q12(0.0f); \
    (chara)->damage.position.vy = Q12(0.0f); \
    (chara)->damage.position.vx = Q12(0.0f)

/** @brief Sets a character's received attack type.
 *
 * TODO: Could make this use `WEAPON_ATTACK` macro and take the values needed for that instead.
 * Maybe devs did similar thing, which is why this separate macro/inline is needed for a match?
 *
 * @param chara Character to update.
 * @param attack Attack type to set.
 */
#define Chara_AttackReceivedSet(chara, attack) \
    (chara)->attackReceived = (attack)

/** @brief Gets a character's received attack type.
 *
 * @param chara Character to update.
 */
#define Chara_AttackReceivedGet(chara) \
    (chara)->attackReceived

/** @brief Sets the animation of a character.
 *
 * @param chara Character to set animation for. TODO: Maybe should take `s_ModelAnim` instead? If fits better, also rename to `Anim_Set`.
 * @param animStatus Packed anim status. See `s_ModelAnim::status`.
 * @param keyframeIdx Active keyframe index.
 */
static inline void Chara_AnimSet(s_SubCharacter* chara, s32 animStatus, s32 keyframeIdx)
{
    chara->model.anim.status      = animStatus;
    chara->model.anim.time        = Q12(keyframeIdx);
    chara->model.anim.keyframeIdx = keyframeIdx;
}

/** @brief Resets a humanoid character's control state to `*_None` if the control subsystem was flagged for a reset.
 *
 * TODO: This uses `dahlia` part of union, but is most likely either a `human` part shared with all humanoid characters
 * or humanoids only share a small struct early in the union.
 *
 * @param chara Character to update.
 */
static inline void Chara_AnimStateReset(s_SubCharacter* chara)
{
    if (chara->properties.dahlia.resetControlState)
    {
        chara->properties.dahlia.controlState      = 0;
        chara->model.stateStep                     = 0;
        chara->properties.dahlia.resetControlState = false;
    }
}

#endif
