#include "common.h"

#include "bodyprog/vw_system.h"

void vwInitViewInfo() // 0x80048A38
{
    vwViewPointInfo.rview.vp.vz = 0;
    vwViewPointInfo.rview.vp.vy = 0;
    vwViewPointInfo.rview.vp.vx = 0;
    vwViewPointInfo.rview.vr.vx = 0;
    vwViewPointInfo.rview.vr.vy = 0;
    vwViewPointInfo.rview.vr.vz = 4096;
    vwViewPointInfo.rview.rz = 0;
    vwViewPointInfo.rview.super = &vwViewPointInfo.vwcoord;
    GsInitCoordinate2(NULL, &vwViewPointInfo.vwcoord);
    vwSetViewInfo();
}

GsCOORDINATE2 *vwGetViewCoord() // 0x80048A90
{
    return &vwViewPointInfo.vwcoord;
}

void vwGetViewPosition(VECTOR3 *pos) // 0x80048A9C
{
    *pos = vwViewPointInfo.worldpos;
}

void vwGetViewAngle(SVECTOR *ang) // 0x80048AC4
{
    *ang = vwViewPointInfo.worldang;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_main", func_80048AF4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_main", vwSetCoordRefAndEntou);

void vwSetViewInfoDirectMatrix(GsCOORDINATE2 *pcoord,
                               MATRIX        *cammat) // 0x80048CF0
{
    vwViewPointInfo.vwcoord.flg = 0;
    vwViewPointInfo.vwcoord.super = pcoord;
    vwViewPointInfo.vwcoord.coord = *cammat;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_main", vwSetViewInfo);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_main", func_80048DA8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_main", func_80048E3C);