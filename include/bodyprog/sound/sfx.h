#ifndef _BODYPROG_SOUND_SFX_H
#define _BODYPROG_SOUND_SFX_H

#include "bodyprog/sound/sound_effects.h"

s32 func_8005D86C(q19_12 arg0);

/** Looks like a clamping function. */
s32 func_8005D974(s32 arg0);

/** @brief Computes the distance-attenuated sound volume from a source position.
 *
 * @param srcPos Sound source position.
 * @param vol Sound volume to attenuate.
 * @return Distance-attenuated sound volume.
 */
q23_8 Sfx_DistanceAttenuatedVolumeGet(const VECTOR3* srcPos, q23_8 vol);

/** @brief Plays SFX with flags.
 *
 * @param sfxId ID of the SFX to play.
 * @param pos SFX position.
 * @param vol SFX volume.
 * @param sfxFlags SFX flags.
 */
void Sfx_WithFlagsPlay(e_SfxId sfxId, const VECTOR3* pos, q23_8 vol, s32 sfxFlags);

/** @brief Plays SFX with flags and a pitch.
 *
 * @param sfxId ID of the SFX to play.
 * @param pos SFX position.
 * @param vol SFX volume.
 * @param sfxFlags SFX flags.
 * @param pitch SFX pitch.
 */
void Sfx_WithFlagsAndPitchPlay(e_SfxId sfxId, const VECTOR3* pos, q23_8 vol, s32 sfxFlags, s32 pitch);

/** @brief Plays SFX with a pitch.
 *
 * @param sfxId ID of the SFX to play.
 * @param pos SFX position.
 * @param vol SFX volume.
 * @param pitch SFX pitch.
 */
void Sfx_WithPitchPlay(e_SfxId sfxId, const VECTOR3* pos, q23_8 vol, s8 pitch);

/** @brief Plays SFX with a falloff and pitch.
 *
 * @param sfxId ID of the SFX to play.
 * @param pos SFX position.
 * @param vol SFX volume.
 * @param sfxFlags SFX falloff.
 * @param pitch SFX pitch.
 */
void Sfx_WithFalloffAndPitchPlay(e_SfxId sfxId, VECTOR3* pos, s32 vol, q19_12 falloff, s8 pitch);

#endif
