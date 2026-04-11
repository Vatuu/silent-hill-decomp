#ifndef _BODYPROG_EVENTS_EVENTSMAIN_H
#define _BODYPROG_EVENTS_EVENTSMAIN_H

void Event_Update(bool disableButtonEvents);

bool Event_CollideFacingCheck(s_MapPoint2d* mapPoint);

bool Event_CollideObbFacingCheck(s_MapPoint2d* mapPoint);

bool Event_CollideObbCheck(s_MapPoint2d* mapPoint);

#endif
