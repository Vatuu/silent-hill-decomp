#ifndef _MAPS_MAP0_S00_H
#define _MAPS_MAP0_S00_H

#define HAS_PlayerState_Unk51
#define HAS_PlayerState_Unk131
#define HAS_PlayerState_Unk52
#define HAS_PlayerState_Unk53
#define HAS_PlayerState_Unk54
#define HAS_PlayerState_Unk55
#define HAS_PlayerState_Unk56
#define HAS_PlayerState_Unk57
#define HAS_PlayerState_Unk74
#define HAS_PlayerState_Unk84

typedef struct
{
    s16 field_0;
    s16 field_2; // Angle.
} s_800DFB44;

typedef struct
{
    u8 field_0;
    u8 field_1;
    u8 field_2;
} s_800DFB48;

extern VECTOR3 D_800E32DC[4];

/** "STAGE 0-0" string */
extern char D_800CAE7C[];

extern VECTOR3 D_800CB6A4;

extern u8 D_800DD593;

extern u8 D_800DD594;

/** Distance. */
extern q19_12 D_800DFAD0;

extern s32 D_800DFAD4;

extern q19_12 D_800DFADC;

extern u8 D_800E34EC;

extern u8 D_800E39AC;

extern s_WorldObject_0 D_800E3A5C[2];

extern VECTOR3 D_800E3A9C;

extern SVECTOR3 D_800E3AAC;

/** Time. */
extern q19_12 D_800DFAB8;

extern u16 g_MapMsgSounds[];

extern u8 D_800DFAC2;

extern u8 g_MapMsgSoundIdx;

extern s32 D_800DFAC4;

extern VECTOR3 D_800DFAE0[];  // }  TODO might be one big table.
extern VECTOR3 D_800DFB28[3]; // }

extern s32 D_800DFB40;

extern s_800DFB44 D_800DFB44;

extern s_800DFB48 D_800DFB48;

extern s32 D_800DFB5C;

extern u8 D_800DFB60;

extern u8 D_800DF2F8;

extern s16 D_800DF300[];

extern bool g_WarpCamera;

extern s16 D_800E0C64;

void func_800CBFB0(s_800E34FC* arg0, s_800E330C* arg1, s32 mapId);

bool func_800CC6E8(s_800E34FC* arg0, s_800E330C* arg1, s32 mapId);

s32 func_800CC8FC(VECTOR3*, s32*, MATRIX*);

void func_800CD8E8(s32, s32, s_800E330C*);

void func_800CE02C(s32, s32, s_800E34FC* arg2, s32 mapId);

void func_800D0124();

/** Collision space distance check. @hack Guessed types. */
bool func_800D012C(VECTOR3* pos, MATRIX* unused0, s32* unused1);

void func_800CF7AC(s32 arg0, s_Particle* part, u16* arg2, s32* deltaTime);

void func_800D0274(s32 arg0, s_Particle* part, u16* arg2);

/** @brief 2D player distance check on XZ plane.
 *
 * Checks against a constant 2D distance of `Q12(40.0f)` between the player and two positions.
 * This is a lazy check, i.e.
 * instead of: `(SQUARE(x1 - x2) + SQUARE(z1 - z2)) < SQUARE(d)`
 * it does:    `(ABS(x1 - x2) + ABS(z1 - z2)) < d`.
 *
 * @return `true` if the player distance from either position is `< Q12(40.0f)`,
 *          otherwise `false`.
 */
bool func_800D0600();

void func_800D2E6C();

void func_800D2E74();

void func_800D2E7C();

void func_800D2E84();

void func_800D2E8C();

s32 func_800D2E94();

void func_800D2E9C();

void func_800D94F8(void);

/** Debug function? */
void Gfx_LoadingScreen_StageString();

void func_800DBE00();

void func_800DC33C(void);

void func_800DC694(void);

void func_800DC8D8(void);

void func_800DCA30(void);

s32 func_800DCDA8();

s32 func_800DCF38(s32);

void func_800DD0CC(void);

void Map_WorldObjectsInit(void);

void Map_WorldObjectsUpdate(void);

void Event_GreyChildrenSpawn(void);

void func_800DD0CC();

void func_800DCC54(void);

void func_800DA454(void);

void func_800DA5A0(void);

void func_800D9610(void);

void func_800D9D98(void);

void func_800DA028(void);

void func_800DA254(void);

void func_800DAA68(void);

void func_800DAB8C(void);

void func_800DACB0(void);

void func_800DAEFC(void);

void func_800DB26C(void);

void func_800DB514(void);

void func_800DB870(void);

void func_800D802C(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coord);

void func_800D8124(s_SubCharacter* chara, GsCOORDINATE2* coord);

bool func_800D8748(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx0, s32 keyframeIdx1, s32 arg4, s32 pitch);

void func_800D0394(s32 count, VECTOR3* vecs);

void func_800DADD4(void);

void func_800CE544(s32 idx0, s32 arg1, s_800E34FC* arg2);

#endif
