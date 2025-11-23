#ifndef _BODYPROG_VIEW_VWMAIN_H
#define _BODYPROG_VIEW_VWMAIN_H

#include "gpu.h"

void vwInitViewInfo(void);

/** @brief Gets the camera coordinate.
 *
 * @return Camera coordinate.
 */
GsCOORDINATE2* vwGetViewCoord(void);

/** @brief Gets the camera position.
 *
 * @param pos Output camera position (Q19.12).
 */
void vwGetViewPosition(VECTOR3* pos);

/** @brief Gets the camera rotation.
 *
 * @param ang Output camera rotation (Q19.12).
 */
void vwGetViewAngle(SVECTOR* ang);

void Vw_SetLookAtMatrix(const VECTOR3* pos, const VECTOR3* lookAt);

void vwSetCoordRefAndEntou(GsCOORDINATE2* parent_p, q19_12 ref_x, q19_12 ref_y, q19_12 ref_z, q3_12 cam_ang_y, q3_12 cam_ang_z, q19_12 cam_y, q19_12 cam_xz_r);

/** @brief Sets the camera look-at direction matrix.
 *
 * @param pcoord TODO
 * @param cammat TODO
 */
void vwSetViewInfoDirectMatrix(GsCOORDINATE2* pcoord, const MATRIX* cammat);

void vwSetViewInfo(void);

/** @brief Clamps an angle range to be within a given set of constraints.
 *
 * @param angleMin Output minimum angle to clamp.
 * @param angleMax Output maximum angle to clamp.
 * @param angleConstrainMin Minimum angle constraint.
 * @param angleConstraintMax Maximum angle constraint.
 */
void Vw_ClampAngleRange(q3_12* angleMin, q3_12* angleMax, q3_12 angleConstraintMin, q3_12 angleConstraintMax);

s16 func_80048E3C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);

#endif
