#ifndef _BODYPROG_GAMEBOOT_BACKGROUNDSOUNDINIT_H
#define _BODYPROG_GAMEBOOT_BACKGROUNDSOUNDINIT_H

// ==========
// FUNCTIONS
// ==========

/** @brief Initializes background music or updates current track.
 *
 * @return Returns -1 if something is being loaded in memory or if
 * some audio is being play. Returns 0 if music has been muted or
 * updated, returns 1 if everything fails.
 *
 * @note In case of returning 0 for the only instance this function
 * is used the main loading screen will be triggered.
 */
bool Bgm_Init(void);

/** @brief Checks if a given background music track is not currently playing
 * or if it is a command to trigger the update of layers or track change.
 *
 * @param bgmIdx Index of the background music track to check.
 * @return `true` if the given track is not currently playing, `false` otherwise
 * and in case of being an update layer/track command.
 */
bool Bgm_ActiveTrackCheck(s32 bgmIdx);

void Bgm_TrackSet(s32 bgmIdx);

/** @brief Updates track in case `g_MapOverlayHdr.bgmCmd` is defined as
 * `BgmCmd_UpdateTrack`.
 *
 * @note This function is used to change tracks in between map/room
 * changes or when loading a save only in case the overlay uses multiple
 * tracks.
 */
void Bgm_UpdateTrack(void);

/** @brief Update channels being used by songs.
 * @todo Properly documment after investigating game's channel
 * functionallity
 */
void Bgm_ChannelSet(void);


bool Sd_AmbientSfxInit(void);

bool Sd_ActiveAmbientCheck(s32 ambientIdx);

void Sd_AmbientSfxSet(s32 idx);

#endif
