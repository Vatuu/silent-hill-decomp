#include "common.h"

#include "bodyprog/vw_system.h"

// 0x80048A38
void vwInitViewInfo()
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

// 0x80048A90
GsCOORDINATE2* vwGetViewCoord()
{
    return &vwViewPointInfo.vwcoord;
}

// 0x80048A9C
void vwGetViewPosition(VECTOR3* pos)
{
    *pos = vwViewPointInfo.worldpos;
}

// 0x80048AC4
void vwGetViewAngle(SVECTOR* ang)
{
    *ang = vwViewPointInfo.worldang;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_main", func_80048AF4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_main", vwSetCoordRefAndEntou);

// 0x80048CF0
void vwSetViewInfoDirectMatrix(GsCOORDINATE2* pcoord, MATRIX* cammat)
{
    vwViewPointInfo.vwcoord.flg = 0;
    vwViewPointInfo.vwcoord.super = pcoord;
    vwViewPointInfo.vwcoord.coord = *cammat;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_main", vwSetViewInfo);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_main", func_80048DA8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/view/vw_main", func_80048E3C);