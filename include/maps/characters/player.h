#ifndef _MAPS_CHARACTERS_PLAYER_H
#define _MAPS_CHARACTERS_PLAYER_H

extern s32 sharedData_800D32A0_0_s02; // `sharedFunc_800CDAA8_0_s02`

void sharedFunc_800CDAA8_0_s02(s_SubCharacter* playerChara, s_PlayerExtra* extra, GsCOORDINATE2* coord);

void sharedFunc_800D1C38_0_s00(s_SubCharacter* chara, s_PlayerExtra* extra, GsCOORDINATE2* coords);

void sharedFunc_800D209C_0_s00(void);

void Player_MatchArmAnimDisable(void);

void Player_ControlFreeze(void);

void Player_ControlUnfreeze(bool setIdle);

bool sharedFunc_800D23EC_0_s00(s32 playerExtraState, VECTOR3* vec, q3_12 angle, s32 vecCount);

void sharedFunc_800D2C7C_0_s00(s32 playerExtraState);

void sharedFunc_800D2D2C_0_s00(void);

void Player_AnimLock(void);

s32 Player_AnimIsLocked(void);

void Player_AnimUnlock(void);

/** Player anim func. Checks if the active keyframe is at the start or end of the anim's range. */
s32 sharedFunc_800D2DAC_0_s00(void);

/** Triggers at specific points after the start of a cutscene or dialogue. */
bool Player_MoveDistanceIsZero(void);

void Player_MoveDistanceClear(void);

void sharedFunc_800D2E6C_0_s00(void);

void Player_FallBackward(void);

void sharedFunc_800D2E7C_0_s00(void);

void Player_DamageFeetFront(void);

void sharedFunc_800D2E8C_0_s00(q19_12 posX, q19_12 posZ, VECTOR3* vec);

bool sharedFunc_800D2E94_0_s00(void);

void sharedFunc_800D2E9C_0_s00(q19_12* offsetX, q19_12* offsetZ, q3_12* angle);

s32 sharedFunc_800D2EA4_0_s00(void);

void sharedFunc_800D2EB4_0_s00(void);

void sharedFunc_800D2EF4_0_s00(void);

#endif
