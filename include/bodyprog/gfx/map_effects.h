#ifndef _BODYPROG_GFX_MAPEFFECTS_H
#define _BODYPROG_GFX_MAPEFFECTS_H

void Options_BrightnessMenu_LinesDraw(s32 arg0);

/** Loads a flame graphic. */
void GameFs_FlameGfxLoad(void);

void func_8003E740(void);

void Game_SpotlightLoadScreenAttribsFix(void);

/** @brief Adjust light point attributes to make it simile a flashlight. */
void Game_FlashlightAttributesFix(void);

/** @brief Determines what enviroment effects data from `MAP_EFFECTS_INFOS` will use based on
 * `s_MapOverlayHeader::field_16`.
 */
void Gfx_MapEffectsAssign(s_MapOverlayHeader* mapHdr);

/** @brief Toggles the player's flashlight on. */
void Game_TurnFlashlightOn(void);

/** @brief Toggles the player's flashlight off. */
void Game_TurnFlashlightOff(void);

/** @brief Toggles the player's flashlight. */
void Game_FlashlightToggle(void);

/** @brief Checks if the player's flashlight is on.
 *
 * @return `true` if the flashlight is on, `false` otherwise.
 */
bool Game_FlashlightIsOn(void);

void Gfx_MapInitMapEffectsUpdate(s32 idx0, s32 idx1);

void func_8003EDA8(void);

void func_8003EDB8(CVECTOR* color0, CVECTOR* color1);

/** @brief @unused */
void func_8003EE30(s32 arg0, s32* arg1, s32 arg2, s32 arg3);

void Gfx_LoadScreenMapEffectsUpdate(s32 arg0, s32 arg1);

void Gfx_MapEffectsUpdate(s32 idx0, s32 idx1, e_PrimitiveType primType, void* primData, s32 arg4, s32 arg5);

void Gfx_MapEffectsStepUpdate(const s_MapEffectsInfo* preset0, const s_MapEffectsInfo* preset1,
                              e_PrimitiveType primType, void* primData, s32 arg4, s32 arg5);

void Gfx_FogParametersSet(s_StructUnk3* arg0, const s_MapEffectsInfo* preset);

void Gfx_FlashlightUpdate(void);

q19_12 func_8003F4DC(GsCOORDINATE2** coords, SVECTOR* rot, q19_12 alpha, s32 arg3, u32 arg4, s_SysWork* sysWork);

u32 func_8003F654(s_SysWork_2388* arg0);

/** @brief Computes the normalized progress alpha in the range `[0.0f, 1.0f]`.
 *
 * @param val Current value.
 * @param min Minumum range.
 * @param max Maximum range.
 * @return Normalized progress alpha.
 */
q19_12 Gfx_ProgressAlphaGet(s32 val, s32 min, s32 max);

/** @brief Computes the weighted average of `a` and `b`.
 *
 * @param a First value.
 * @param b Second value.
 * @param weight Weight as a fixed-point alpha in Q3.12, range `[0, 4096]`.
 * @return Weighted average of `a` and `b`.
 */
q19_12 Math_WeightedAverageGet(s32 a, s32 b, q19_12 weight);

void func_8003F838(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, q19_12 weight);

void func_8003FCB0(const s_MapEffectsInfo* arg0, const s_MapEffectsInfo* arg1, const s_MapEffectsInfo* arg2, q19_12 alphaTo);

void func_8003FD38(s_StructUnk3* arg0, s_StructUnk3* arg1, s_StructUnk3* arg2, q19_12 weight0, q19_12 weight1, q19_12 alphaTo);

void func_8003FE04(const s_MapEffectsInfo* arg0, const s_MapEffectsInfo* arg1, const s_MapEffectsInfo* arg2, q19_12 alphaTo);

s32 func_8003FEC0(const s_MapEffectsInfo* arg0);

void func_8003FF2C(s_StructUnk3* arg0);

#endif
