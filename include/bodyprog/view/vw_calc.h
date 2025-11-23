#ifndef _BODYPROG_VIEW_VW_CALC_H
#define _BODYPROG_VIEW_VW_CALC_H

#include "gpu.h"

void vwRenewalXZVelocityToTargetPos(q19_12* velo_x, q19_12* velo_z, const VECTOR3* now_pos, const VECTOR3* tgt_pos, q19_12 tgt_r,
                                    q19_12 accel, q19_12 total_max_spd, q19_12 dec_forwd_lim_spd, q19_12 dec_accel_side);

void vwLimitOverLimVector(q19_12* vec_x, q19_12* vec_z, q19_12 lim_vec_len, q3_12 lim_vec_ang_y);

void vwDecreaseSideOfVector(q19_12* vec_x, q19_12* vec_z, q19_12 dec_val, q19_12 max_side_vec_len, q3_12 dir_ang_y);

q19_12 vwRetNewVelocityToTargetVal(q19_12 now_spd, q19_12 mv_pos, q19_12 tgt_pos, q19_12 accel, q19_12 total_max_spd, q19_12 dec_val_lim_spd);

/** @brief
 *
 * @param now_ang_spd Current angular speed.
 * @param now_ang Current angle.
 * @param tgt_ang Target angle.
 * @param accel_spd Acceleration speed.
 * @param total_max_ang_spd Max angular speed.
 * @param dec_val_lim_spd Deceleration speed.
 * @return New angular speed.
 */
q19_12 vwRetNewAngSpdToTargetAng(q19_12 now_ang_spd, q3_12 now_ang, q3_12 tgt_ang, q19_12 accel_spd, q19_12 total_max_ang_spd, q19_12 dec_val_lim_spd);

void vwMatrixToAngleYXZ(SVECTOR* ang, const MATRIX* mat);

void Vw_MultiplyAndTransformMatrix(MATRIX* transformMat, MATRIX* inMat, MATRIX* outMat);

void vbSetWorldScreenMatrix(GsCOORDINATE2* coord);

void vbSetRefView(VbRVIEW* rview);

void Vw_CoordHierarchyMatrixCompute(GsCOORDINATE2* rootCoord, MATRIX* outMat);

void func_80049AF8(GsCOORDINATE2* rootCoord, MATRIX* outMat);

void func_80049B6C(GsCOORDINATE2* rootCoord, MATRIX* outMat0, MATRIX* outMat1);

void func_80049C2C(MATRIX* mat, s32 x, s32 y, s32 z);

/** @brief Checks if an AABB is visible in the screen.
 *
 * @param minX AABB X minimum point.
 * @param minY AABB Y minimum point.
 * @param minZ AABB Z minimum point.
 * @param maxX AABB X maxiumum point.
 * @param maxY AABB Y maxiumum point.
 * @param maxZ AABB Z maxiumum point.
 * @return `true` if the AABB is visible, `false` otherwise.
 */
bool Vw_AabbVisibleInScreenCheck(s32 xMin, s32 xMax, s32 yMin, s32 yMax, s32 zMin, s32 zMax);

/** @brief Checks if an AABB is visible in a frustum.
 *
 * @param modelMat Model matrix. TODO: What for?
 * @param minX AABB X minimum point.
 * @param minY AABB Y minimum point.
 * @param minZ AABB Z minimum point.
 * @param maxX AABB X maxiumum point.
 * @param maxY AABB Y maxiumum point.
 * @param maxZ AABB Z maxiumum point.
 * @param nearPlane Frustum near plane.
 * @param farPlane Frustum far plane.
 * @return `true` if the AABB is visible, `false` otherwise.
 */
bool Vw_AabbVisibleInFrustumCheck(MATRIX* modelMat, s16 minX, s16 minY, s16 minZ, s32 maxX, s32 maxY, s32 maxZ, u16 nearPlane, u16 farPlane);

bool func_8004A54C(s_func_8004A54C* arg0);

/** @brief Converts a rotation to a direction vector with a given length.
 *
 * @param vec Output direction vector.
 * @param ang Rotation to convert.
 * @param r Radius representing the direction vector's length.
 */
void vwAngleToVector(SVECTOR* vec, const SVECTOR* ang, s32 r);

/** @brief Converts a direction vector to a rotation.
 *
 * @param ang Output rotation.
 * @param vec Direction vector to convert.
 * @return Direction vector length.
 */
q19_12 vwVectorToAngle(SVECTOR* ang, const SVECTOR* vec);

/** Performs linear interpolation between Y values based on an input X within the given range.
 *
 * TODO
 */
s32 vwOresenHokan(const s32* y_ary, s32 y_suu, s32 input_x, s32 min_x, s32 max_x);

#endif
