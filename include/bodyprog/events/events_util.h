#ifndef _BODYPROG_EVENTS_EVENTSUTIL_H
#define _BODYPROG_EVENTS_EVENTSUTIL_H

typedef enum _BgTextureCommand
{
    BgTextureCommand_QueueRead          = 0,
    BgTextureCommand_AwaitLoad          = 1, // Increments `sysStateSteps[0]`/`sysStateSteps[1]` if file is loaded.
    BgTextureCommand_Draw               = 2,
    BgTextureCommand_StoreVram          = 3,
    BgTextureCommand_QueueReadSecondary = 4,
    BgTextureCommand_DrawSecondary      = 5,
    BgTextureCommand_RestoreVram        = 6,
    BgTextureCommand_Auto               = 7, // Command is kept inside `sysStateSteps[2]` which is then incremented as texture is loaded/drawn?
    BgTextureCommand_8                  = 8, // TODO: Queues load as either primary or secondary, depending on whether primary is in use? (`g_SysWork.sysStateSteps[2] != 0`)
                                             // `Event_BgTextureCommand` has weird code that treats this as a different cmd by changing `activeCmd`, but seems that would skip `BgTextureCommand_QueueRead` for primary texture load?
} e_BgTextureCommand;

/** @brief Character animation commands. */
typedef enum _CharaAnimCommand
{
    CharaAnimCommand_SetState     = 0,
    CharaAnimCommand_AwaitAnimEnd = 1, // Calls `Event_SysStateStepIncrement` when an animation reaches its end.
    CharaAnimCommand_AnimLock     = 2,
    CharaAnimCommand_AnimUnlock   = 3,
    CharaAnimCommand_AnimReset    = 4 // TODO: Unsure on name, could be a forced stop.
} e_CharaAnimCommand;

typedef enum _InvItemCommand
{
    InvItemCommand_QueueLoad = 0,
    InvItemCommand_AwaitLoad = 1,
    InvItemCommand_Nop       = 2, // Does nothing? `activeCmd` is changed to 3, but then switch has no entry for `3`.
    InvItemCommand_AddItem   = 3, // Finalize + add to inventory (`activeCmd` changes to 2, which adds to inventory)
    InvItemCommand_4         = 4, // Auto, no inventory add? | @unused No caller passes this?
    InvItemCommand_5         = 5, // @unused No caller passes this?
    InvItemCommand_6         = 6, // Auto + add to inventory | @unused No caller passes this but code checks it
} e_InvItemCommand;

typedef enum _ScreenFadeCommand
{
    ScreenFadeCommand_Start = 0,
    ScreenFadeCommand_Await = 1,
    ScreenFadeCommand_Auto  = 2, // Uses `sysStateSteps[2]` as command.
} e_ScreenFadeCommand;

/** State step increment for some substate. */
void Event_SysStateStepIncrement(bool incSubStep);

/** State step setter for some substate. */
void Event_SysStateStepSet(bool setSubStep, s32 sysStateStep);

/** Calls `SysWork_StateStepIncrement(0)` with some preliminary safety check. */
void func_80085DF0(void);

void Event_SysStateStepIncrementDelayed(q19_12 delay, bool incSubStep);

/** @brief Updates character states during events/cutscenes. */
void Event_CharaAnimCommandExecute(e_CharaAnimCommand cmd, s_SubCharacter* chara, s32 cmdArg, bool incSubStep);

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
 * @param hasSelection `true` if it waits for a selection, `false` if `sysStateSteps` increments after displaying.
 * @param mapMsgIdx Map message index of the message to display.
 * @param step0 Step to use if selection #0 is chosen.
 * @param step1 Step to use if selection #1 is chosen.
 * @param step2 Step to use if selection #2 is chosen.
 * @param incSubStep If `true`, sets `sysStateSteps[1]` instead of `sysStateSteps[0]`, otherwise sets `sysStateSteps[0]`.
 */
void Event_DisplayMapMsg(bool hasSelection, s32 mapMsgIdx, s32 step0, s32 step1, s32 step2, bool incSubStep);

void Event_ScreenFadeCommand(e_ScreenFadeCommand cmd, bool fadeOut, s32 fadeType, q19_12 fadeTimestep, bool incSubStep);

/** Handles background texture load/draw. Optionally allows layering two textures. */
void Event_BgTextureCommand(e_BgTextureCommand cmd, e_FsFile fileIdx, bool incSubStep);

/** Stepped state handler for displaying picked up items? */
void Event_InvItemCommand(e_InvItemCommand stateStep, e_InvItemId itemId, s32 itemCount, bool incSubStep);

void func_800865FC(bool isPos, s32 idx0, s32 idx1, q3_12 angleY, q19_12 offsetOrPosX, q19_12 offsetOrPosZ);

/** State step increment. */
void func_800866D4(s32 arg0, s32 arg1, bool incSubStep);

void func_80086728(s_SubCharacter* chara, s32 arg1, s32 arg2, bool incSubStep);

void func_8008677C(s_SubCharacter* chara, s32 arg1, s32 arg2);

/** Paper map state handler. Rough name could be `Map_PaperMapBackgroundStateUpdate`. */
void func_800867B4(s32 state, s32 paperMapFileIdx);

void func_800868DC(s32 idx);

s32 func_800868F4(s32 arg0, s32 arg1, s32 idx);

s32 func_8008694C(s32 arg0, s16 arg1, s16 arg2, s32 arg3, s32 idx);

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

/** Starts an animation on a character. Increments `sysStateSteps[0]` once animation has ended. */
void Event_CharaAnimPlayUntilEnd(s_SubCharacter* chara, s32 animState);

/** Unlocks/resumes an already playing animation on a character. Increments `sysStateSteps[0]` once animation has ended. */
void Event_CharaAnimUnlockPlayUntilEnd(s_SubCharacter* chara);

/** Starts a screen fade and begins loading a background texture. Increments `sysStateSteps[0]` once fade has completed. */
void Event_BgTextureLoadFadeIn(e_FsFile fileIdx, q19_12 fadeTimestep);

/** Fades screen while loading a background texture. Once texture is loaded, draws it to screen and increments `sysStateSteps[0]`. */
void Event_BgTextureFadeIn(e_FsFile fileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1);

/** Odd code?
 * This function appears to circumvent an issue with fading.
 * When the player is about to leave the clock tower screen marking certain
 * times, breaking it causes the clock tower image to dissapear. It then fades in
 * and out to the black screen before returning to gameplay.
 */
void func_80086F44(s32 fadeTimestep0, q19_12 fadeTimestep1);

/** @brief Displays a map message with SFX.
 *
 * @param mapMsgIdx Index of the message to display.
 * @param sfxId ID of the SFX to play.
 * @param sfxPos SFX position.
 */
void Event_DisplayMapMsgWithSfx(s32 mapMsgIdx, e_SfxId sfxId, VECTOR3* sfxPos);

/** @unused Freezes game and fades in a background texture, remaining on screen until button is pressed. */
void Event_DisplayBgTexture(e_FsFile textureFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1);

void Event_DisplayMapMsgWithTexture(e_FsFile textureFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1, s32 mapMsgIdx);

/** @brief Displays a message with a background texture that is darken after reading the first sentence. */
void Event_DisplayMapMsgWithTexture1(e_FsFile textureFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1, s32 mapMsgIdx0, s32 mapMsgIdx1);

void Event_ItemTake(e_InvItemId itemId, s32 itemCount, e_EventFlag eventFlagIdx, s32 mapMsgIdx);

void Event_CommonItemTake(u32 pickupType, e_EventFlag eventFlagIdx);

void Event_MapTake(s32 mapFlagIdx, e_EventFlag eventFlagIdx, s32 mapMsgIdx);

#endif