#ifndef _BODYPROG_EVENTS_PLAYERPOSUPDATE_H
#define _BODYPROG_EVENTS_PLAYERPOSUPDATE_H

/** @brief Set player position.
 * Used for setting the position of the player when transitioning in from rooms.
 */
void Chara_PositionSet(s_MapPoint2d* mapPoint);

/** Finds the ground hight and warps the player to it? */
void Game_PlayerHeightUpdate(void);

#endif
