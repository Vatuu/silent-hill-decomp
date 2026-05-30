#ifndef _BODYPROG_EVENTS_EVENTSUTIL_H
#define _BODYPROG_EVENTS_EVENTSUTIL_H

/** @brief Bachground texture commands. */
typedef enum _BgTextureCmd
{
    BgTextureCmd_QueueRead          = 0,
    BgTextureCmd_AwaitLoad          = 1, // Increments `sysStateSteps[0]`/`sysStateSteps[1]` if file is loaded.
    BgTextureCmd_Draw               = 2,
    BgTextureCmd_StoreVram          = 3,
    BgTextureCmd_QueueReadSecondary = 4,
    BgTextureCmd_DrawSecondary      = 5,
    BgTextureCmd_RestoreVram        = 6,
    BgTextureCmd_Auto               = 7, // Command is kept inside `sysStateSteps[2]` which is then incremented as texture is loaded/drawn?
    BgTextureCmd_8                  = 8, // TODO: Queues load as either primary or secondary, depending on whether primary is in use? (`g_SysWork.sysStateSteps[2] != 0`)
                                         // `Event_BgTextureCmd` has weird code that treats this as a different cmd by changing `activeCmd`, but seems that would skip `BgTextureCmd_QueueRead` for primary texture load?
} e_BgTextureCmd;

/** @brief Character animation commands. */
typedef enum _CharaAnimCmd
{
    CharaAnimCmd_SetState     = 0,
    CharaAnimCmd_AwaitAnimEnd = 1, // Calls `Event_SysStateStepIncrement` when an animation reaches its end.
    CharaAnimCmd_AnimLock     = 2,
    CharaAnimCmd_AnimUnlock   = 3,
    CharaAnimCmd_AnimReset    = 4 // TODO: Unsure on name, could be a forced stop.
} e_CharaAnimCmd;

/** @brief Inventory item commands. */
typedef enum _InvItemCmd
{
    InvItemCmd_QueueLoad = 0,
    InvItemCmd_AwaitLoad = 1,
    InvItemCmd_Nop       = 2, // Does nothing? `activeCmd` is changed to 3, but then switch has no entry for `3`.
    InvItemCmd_AddItem   = 3, // Finalize + add to inventory (`activeCmd` changes to 2, which adds to inventory).
    InvItemCmd_4         = 4, // Auto, no inventory add? | @unused No caller passes this?
    InvItemCmd_5         = 5, // @unused No caller passes this?
    InvItemCmd_6         = 6, // Auto + add to inventory | @unused No caller passes thi, but code checks it.
} e_InvItemCmd;

/** @brief Screen fade commands. */
typedef enum _ScreenFadeCmd
{
    ScreenFadeCmd_Start = 0,
    ScreenFadeCmd_Await = 1,
    ScreenFadeCmd_Auto  = 2, // Uses `sysStateSteps[2]` as command.
} e_ScreenFadeCmd;

/** State step increment for some substate. */
void Event_SysStateStepIncrement(bool incSubStep);

/** State step setter for some substate. */
void Event_SysStateStepSet(bool setSubStep, s32 sysStateStep);

/** Calls `SysWork_StateStepIncrement(0)` with some preliminary safety check. */
void func_80085DF0(void);

void Event_SysStateStepIncrementDelayed(q19_12 delay, bool incSubStep);

/** @brief Updates character states during events and cutscenes. */
void Event_CharaAnimCmdExecute(e_CharaAnimCmd cmd, s_SubCharacter* chara, s32 animState, bool incSubStep);

/** @brief Sets `sysStateSteps` depending on whether `eventFlagIdx` flag is set.
 *
 * @param eventFlagIdx Flag index.
 * @param stepTrue Step to use if flag is set.
 * @param stepFalse Step to use if flag is not set.
 * @param setSubStep If `true`, sets `sysStateSteps[1]` instead of `sysStateSteps[0]`, otherwise sets `sysStateSteps[0]`.
 */
void Event_SysStateBranchOnFlag(e_EventFlag eventFlagIdx, s32 stepTrue, s32 stepFalse, bool setSubStep);

/** @brief Displays a selection menu and sets `sysStateSteps` depending on the chosen value.
 *
 * @param hasSelection `true` if waiting for a selection, `false` if `sysStateSteps` increments after displaying.
 * @param mapMsgIdx Index of the map message to display.
 * @param step0 Step to use if selection #0 is chosen.
 * @param step1 Step to use if selection #1 is chosen.
 * @param step2 Step to use if selection #2 is chosen.
 * @param incSubStep If `true`, sets `sysStateSteps[1]` instead of `sysStateSteps[0]`, otherwise sets `sysStateSteps[0]`.
 */
void Event_DisplayMapMsg(bool hasSelection, s32 mapMsgIdx, s32 step0, s32 step1, s32 step2, bool incSubStep);

void Event_ScreenFadeCmd(e_ScreenFadeCmd cmd, bool fadeOut, s32 fadeType, q19_12 fadeTimestep, bool incSubStep);

/** @brief Handles background texture loading and drawing. Optionally allows layering two textures.
 *
 * @param cmd Background texture command.
 * @param texFileIdx Texture file index of the background to load and draw.
 * @param incSubStep Increment sub-step.
 */
void Event_BgTextureCmd(e_BgTextureCmd cmd, e_FsFile texFileIdx, bool incSubStep);

/** Stepped state handler for displaying picked up items? */
void Event_InvItemCmd(e_InvItemCmd stateStep, e_InvItemId itemId, s32 itemCount, bool incSubStep);

/** @brief Sets a waypoint position for a character path.
 *
 * @param isAbs If `true`, uses `posX`/`posZ` as absolute coordinates. If `false`, it uses them as offsets from the player's current position.
 * @param charaSlotIdx Character slot index. 0 = player, 1 = NPC. @note Paths for NPCs are still offset from player position.
 * @param waypointIdx Index of the waypoint along the path.
 * @param headingAngle Heading angle for the character on this path.
 * @param posX X position or offset from player character, depending on `isAbsolute`.
 * @param posZ Z position or offset from player character, depending on `isAbsolute`.
 */
void Event_PathWaypointSet(bool isAbs, s32 charaSlotIdx, s32 waypointIdx, q3_12 headingAngle, q19_12 posX, q19_12 posZ);

/** @brief Executes the player's walk path and increments `sysStateSteps` on completion.
 *
 * @param animId Animation to use while walking.
 * @param waypointCount Number of waypoints in the path.
 * @param incSubStep If `true`, increments `sysStateSteps[1]` instead of `sysStateSteps[0]`.
 */
void Event_PathWaypointExecutePlayer(s32 animId, s32 waypointCount, bool incSubStep);

/** @brief Executes an NPC's walk path and increments `sysStateSteps` on completion.
 *
 * @param chara Character to move.
 * @param animId Animation to use while walking.
 * @param waypointCount Number of waypoints in the path.
 * @param incSubStep If `true`, increments `sysStateSteps[1]` instead of `sysStateSteps[0]`.
 */
void Event_PathWaypointExecuteChara(s_SubCharacter* chara, s32 animId, s32 waypointCount, bool incSubStep);

/** @brief Executes an NPC's walk path.
 *
 * @note Same as `Event_PathWaypointExecuteChara`, but doesn't affect `sysStateSteps`.
 * Used when event code doesn't need to wait for the waypoint to be reached?
 *
 * @param chara Character to move.
 * @param animId Animation to use while walking.
 * @param waypointCount Number of waypoints in the path.
 */
void Event_PathWaypointExecuteCharaNoWait(s_SubCharacter* chara, s32 animId, s32 waypointCount);

/** Paper map state handler. Rough name could be `Map_PaperMapBgStateUpdate`. */
void func_800867B4(s32 state, s32 paperMapFileIdx);

/** @brief Resets a tween timer slot to 0.
 *
 * @param idx Timer slot index.
 */
void Event_TweenReset(s32 idx);

/** @brief Linear tween from 0 to `target` over `duration`.
 *
 * @param target Target value at the end of the tween.
 * @param duration Total tween duration.
 * @param idx Timer slot index.
 * @return Interpolated value based on the elapsed time.
 */
q19_12 Event_TweenLinear(q19_12 target, q19_12 duration, s32 idx);

/** @brief @unused Sine-based tween over a given angle range.
 *
 * @param amp Amplitude multiplier applied to the sine result.
 * @param startAngle Starting angle for the sine function.
 * @param sweepAngle Angular span swept over the duration.
 * @param duration Total tween duration in delta time.
 * @param idx Timer slot index.
 * @return `amplitude * sin(startAngle + ((sweepAngle * elapsed) / duration))`.
 */
q19_12 Event_TweenSine(q19_12 amp, s16 startAngle, s16 sweepAngle, q19_12 duration, s32 idx);

/** @brief Displays a map message with dialog audio and increments the audio index.
 *
 * @param mapMsgIdx Index of the message to display.
 * @param audioIdx Index of the dialog audio command to play.
 * @param audioCmds Dialog audio commands.
 */
void Event_DisplayMapMsgWithAudio(s32 mapMsgIdx, u8* audioIdx, const u16* audioCmds);

/** @brief Sets the camera position target.
 *
 * @param pos Target position (Q19.12).
 * @param offsetOrPosX If `pos` is valid, X offset for `pos`. If `pos` is `NULL`, X target position.
 * @param offsetOrPosY If `pos` is valid, Y offset for `pos`. If `pos` is `NULL`, Y target position.
 * @param offsetOrPosZ If `pos` is valid, Z offset for `pos`. If `pos` is `NULL`, Z target position.
 * @param accelX X acceleration.
 * @param accelY X acceleration.
 * @param speedXMax Max X speed.
 * @param speedYMax Max Y speed.
 * @param warp If `true`, warp to the position target, otherwise transition over time.
 */
void Camera_PositionSet(VECTOR3* pos, q19_12 offsetOrPosX, q19_12 offsetOrPosY, q19_12 offsetOrPosZ,
                        q19_12 accelXz, q19_12 accelY, q19_12 speedXzMax, q19_12 speedYMax, bool warp);

/** @brief Sets the camera rotation and look-at position targets.
 *
 * @param lookAt Target look-at position (Q19.12).
 * @param lookAtOffsetOrPosX If `lookAt` is valid, X offset for `lookAt`. If `lookAt` is `NULL`, X target look-at position.
 * @param lookAtOffsetOrPosY If `lookAt` is valid, X offset for `lookAt`. If `lookAt` is `NULL`, Y target look-at position.
 * @param lookAtOffsetOrPosZ If `lookAt` is valid, Z offset for `lookAt`. If `lookAt` is `NULL`, Z target look-at position.
 * @param angularAccelX TODO
 * @param angularAccelY TODO
 * @param angularSpeedXMax TODO
 * @param angularSpeedYMax TODO
 * @param warp If `true`, warp to the look-at target, otherwise transition over time.
 */
void Camera_LookAtSet(VECTOR3* lookAt, q19_12 lookAtOffsetOrPosX, q19_12 lookAtOffsetOrPosY, q19_12 lookAtOffsetOrPosZ,
                      q19_12 angularAccelX, q19_12 angularAccelY, q19_12 angularSpeedXMax, q19_12 angularSpeedYMax, bool warp);

/** @brief Starts a character animation.
 * Increments `sysStateSteps[0]` when the animation has finished.
 *
 * @param chara Character to update.
 * @param animState Animation state.
 */
void Event_CharaAnimPlayToEnd(s_SubCharacter* chara, s32 animState);

/** @brief Unlocks/resumes an already playing character animation.
 * Increments `sysStateSteps[0]` when the animation has finished.
 *
 * @param chara Character to update.
 */
void Event_CharaAnimUnlockPlayToEnd(s_SubCharacter* chara);

/** @brief Starts a screen fade and begins loading a background texture.
 * Increments `sysStateSteps[0]` when the fade has completed.
 *
 * @param texFileIdx Texture file index to of the background load.
 * @param fadeTimestep Image fade timestep.
 */
void Event_BgTextureLoadFadeIn(e_FsFile texFileIdx, q19_12 fadeTimestep);

/** @brief Fades the screen while loading a background texture.
 * When the texture is loaded, it draws it to screen and increments `sysStateSteps[0]`.
 *
 * @param texFileIdx Texture file index of the background to load.
 * @param fadeTimestep0 Image fade timestep 0. TODO
 * @param fadeTimestep1 Image fade timestep 1. TODO
 */
void Event_BgTextureFadeIn(e_FsFile texFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1);

/** Odd code?
 * This function appears to circumvent an issue with fading.
 * When the player is about to leave the clock tower screen marking certain
 * times, breaking it causes the clock tower image to dissapear. It then fades in
 * and out to the black screen before returning to gameplay.
 */
void func_80086F44(s32 fadeTimestep0, q19_12 fadeTimestep1);

/** @brief Displays a map message with SFX.
 *
 * @param mapMsgIdx Index of the map message to display.
 * @param sfxId ID of the SFX to play.
 * @param sfxPos SFX position.
 */
void Event_DisplayMapMsgWithSfx(s32 mapMsgIdx, e_SfxId sfxId, VECTOR3* sfxPos);

/** @brief @unused Freezes the game and fades in a background texture.
 * The image remains on the screen until a button is pressed by the user.
 *
 * @param texFileIdx Texture file index of the background to display.
 * @param fadeTimestep0 Image fade timestep 0. TODO
 * @param fadeTimestep1 Image fade timestep 1. TODO
 */
void Event_DisplayBgTexture(e_FsFile texFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1);

void Event_DisplayMapMsgWithTexture(e_FsFile textureFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1, s32 mapMsgIdx);

/** @brief Displays a message with a background texture that is darken after reading the first sentence. */
void Event_DisplayMapMsgWithTexture1(e_FsFile textureFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1, s32 mapMsgIdx0, s32 mapMsgIdx1);

void Event_ItemTake(e_InvItemId itemId, s32 itemCount, e_EventFlag eventFlagIdx, s32 mapMsgIdx);

void Event_CommonItemTake(u32 pickupType, e_EventFlag eventFlagIdx);

void Event_MapTake(s32 mapFlagIdx, e_EventFlag eventFlagIdx, s32 mapMsgIdx);

#endif
