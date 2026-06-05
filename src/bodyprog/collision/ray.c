#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/gtemac.h>
#include <psyq/libapi.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/collision/collision.h"
#include "bodyprog/math/math.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/player.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/sound/sound_system.h"
#include "main/rng.h"

bool Ray_TraceQuery(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* to) // 0x8006D90C
{
    s32         prevScratchAddr;
    s_RayState* state;
    VECTOR3     offset; // Q19.12

    offset.vx = to->vx - from->vx;
    offset.vy = to->vy - from->vy;
    offset.vz = to->vz - from->vz;

    trace->hasHit = false;

    if (Ray_TraceSetup((s_RayState*)PSX_SCRATCH, 0, 0, from, &offset, 0, 0, NULL, 0))
    {
        prevScratchAddr = SetSp((s32)PSX_SCRATCH_ADDR(984));

        state         = (s_RayState*)PSX_SCRATCH;
        trace->hasHit = Ray_TraceRun(trace, state);

        SetSp(prevScratchAddr);
    }

    if (!trace->hasHit)
    {
        Ray_MissSet(trace, from, &offset, state->rayDistance);
    }

    return trace->hasHit;
}

bool Ray_CharaTraceQuery(s_RayTrace* trace, const VECTOR3* from, VECTOR3* offset, s_SubCharacter* excludedChara) // 0x8006DA08
{
    s32              collCharaCount;
    s32              prevScratch;
    s_RayState*      state;
    s_SubCharacter** collCharas;

    collCharas = Collision_CollidableCharasGet(&collCharaCount, excludedChara, false);

    trace->hasHit = false;
    if (Ray_TraceSetup((s_RayState*)PSX_SCRATCH, 0, 0, from, offset, 0, 0, collCharas, collCharaCount))
    {
        prevScratch   = SetSp((s32)PSX_SCRATCH_ADDR(0x3D8));

        state         = (s_RayState*)PSX_SCRATCH;
        trace->hasHit = Ray_TraceRun(trace, state);

        SetSp(prevScratch);
    }

    if (!trace->hasHit)
    {
        Ray_MissSet(trace, from, offset, state->rayDistance);
    }

    return trace->hasHit;
}

void Ray_MissSet(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* offset, q23_8 dist) // 0x8006DAE4
{
    trace->hasHit       = false;
    trace->groundType   = GroundType_Default;
    trace->target.vx    = from->vx + offset->vx;
    trace->target.vy    = from->vy + offset->vy;
    trace->target.vz    = from->vz + offset->vz;
    trace->character    = NULL;
    trace->hitDistance  = Q8_TO_Q12(dist);
    trace->groundHeight = Q12(1.875f); // @bug? Awkward value suggests `Q8(30.0f)` may have been typed by mistake.
    trace->field_1C     = Q12_ANGLE(0.0f);
}

bool Ray_LosHitCheck(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* offset, s_SubCharacter* excludedChara) // 0x8006DB3C
{
    s32              collCharaCount;
    s32              prevScratchAddr;
    s_RayState*      state;
    s_SubCharacter** collCharas;

    collCharas = Collision_CollidableCharasGet(&collCharaCount, excludedChara, true);
    trace->hasHit    = false;

    if (Ray_TraceSetup((s_RayState*)PSX_SCRATCH, 1, 0, from, offset, 0, 0, collCharas, collCharaCount))
    {
        prevScratchAddr = SetSp((s32)PSX_SCRATCH_ADDR(984));

        state         = (s_RayState*)PSX_SCRATCH;
        trace->hasHit = Ray_TraceRun(trace, state);

        SetSp(prevScratchAddr);
    }

    if (!trace->hasHit)
    {
        Ray_MissSet(trace, from, offset, state->rayDistance);
    }

    return trace->hasHit;
}

bool func_8006DC18(s_RayTrace* trace, const VECTOR3* from, const VECTOR3* offset) // 0x8006DC18
{
    s32         prevScratchAddr;
    s_RayState* state;

    trace->hasHit = false;
    if (Ray_TraceSetup((s32)PSX_SCRATCH, 1, 76, from, offset, 0, 0, NULL, 0))
    {
        prevScratchAddr = SetSp((s32)PSX_SCRATCH_ADDR(0x3D8));

        state         = (s_RayState*)PSX_SCRATCH;
        trace->hasHit = Ray_TraceRun(trace, state);

        SetSp(prevScratchAddr);
    }

    if (!trace->hasHit)
    {
        Ray_MissSet(trace, from, offset, state->rayDistance);
    }

    return trace->hasHit;
}

bool Ray_TraceSetup(s_RayState* state, bool useCylinder, q7_8 arg2, const VECTOR3* from, const VECTOR3* offset, q19_12 arg5, q19_12 arg6,
                    s_SubCharacter** collCharas, s32 collCharaCount)
{
    if (offset->vx == Q12(0.0f) && offset->vz == Q12(0.0f))
    {
        return false;
    }

    state->field_0  = useCylinder;
    state->field_4  = g_ActiveCollisionTriggers.flags; // Struct could begin some point earlier.
    state->field_6  = arg2;
    state->field_8  = SHRT_MAX;
    state->field_20 = 0;

    state->from.vx = Q12_TO_Q8(from->vx);
    state->from.vy = Q12_TO_Q8(from->vy);
    state->from.vz = Q12_TO_Q8(from->vz);

    state->offset.vx = Q12_TO_Q8(offset->vx);
    state->offset.vy = Q12_TO_Q8(offset->vy);
    state->offset.vz = Q12_TO_Q8(offset->vz);

    state->field_3C = state->from.vx + state->offset.vx;

    state->field_4C = Q12_TO_Q8(arg5);
    state->field_4E = Q12_TO_Q8(arg6);

    state->field_40 = state->from.vy + state->offset.vy;
    state->field_44 = state->from.vz + state->offset.vz;

    state->rayDistance = Math_Vector2MagCalc(state->offset.vx, state->offset.vz);
    if (state->rayDistance == Q8(0.0f))
    {
        return false;
    }

    state->field_58 = (state->offset.vx << Q12_SHIFT) / state->rayDistance;
    state->field_5A = (state->offset.vz << Q12_SHIFT) / state->rayDistance;

    if (state->offset.vy < 0)
    {
        state->field_5E = state->from.vy + state->field_4E;
        state->field_60 = state->field_40 + state->field_4E;
    }
    else
    {
        state->field_60 = state->from.vy + state->field_4E;
        state->field_5E = state->field_40 + state->field_4E;
    }

    state->collCharas     = collCharas;
    state->collCharaCount = collCharaCount;

    return true;
}

bool Ray_TraceRun(s_RayTrace* trace, s_RayState* state) // 0x8006DEB0
{
    s32                  collDataIdx;
    s32                  temp_lo;
    s_IpdCollisionData*  collData;
    s_SubCharacter**     curCollChara;
    s_IpdCollisionData** collDataPtrs;
    s_IpdCollisionData** curCollData;
    s_RayState_8C*       curUnk;

    // Run through IPD collision data.
    collDataPtrs = Ipd_ActiveChunksCollisionDataGet(&collDataIdx);
    for (curCollData = collDataPtrs; curCollData < &collDataPtrs[collDataIdx]; curCollData++)
    {
        collData = *curCollData;

        if (collData->surfaceCount || collData->subcellCount || collData->field_8_24)
        {
            func_8006E0AC(state, collData);
            Collision_SubcellChecksReset(collData);

            for (curUnk = &state->field_8C; curUnk < &state->field_8C[state->field_88]; curUnk++)
            {
                temp_lo = curUnk->field_2 * state->field_7C;
                func_8006E53C(state, &collData->subcellRanges[temp_lo + curUnk->field_0], collData);
            }
        }
    }

    // Run through collidable characters.
    for (curCollChara = state->collCharas;
         curCollChara < &state->collCharas[state->collCharaCount];
         curCollChara++)
    {
        func_8006EE0C(&state->field_6C, state->field_0, *curCollChara);
        func_8006EEB8(state, *curCollChara);
    }

    if (state->field_8 != SHRT_MAX)
    {
        trace->target.vx    = Q8_TO_Q12(state->field_C);
        trace->target.vy    = Q8_TO_Q12(state->field_10);
        trace->target.vz    = Q8_TO_Q12(state->field_14);
        trace->character    = state->field_20;
        trace->hitDistance  = Q8_TO_Q12(state->field_8);
        trace->groundHeight = Q8_TO_Q12(state->groundHeight);
        trace->field_1C     = ratan2(state->field_24, state->field_26);
        trace->groundType   = state->groundType;
        return true;
    }

    return false;
}

void func_8006E0AC(s_RayState* state, const s_IpdCollisionData* arg1) // 0x8006E0AC
{
    // `state` type might be wrong.
    state->field_6C.positionX = arg1->positionX;
    state->field_6C.positionZ = arg1->positionZ;
    state->field_6C.groundHeight = state->from.vx - state->field_6C.positionX;
    state->field_6C.topHeight = state->from.vz - state->field_6C.positionZ;
    state->field_6C.field_C = state->field_6C.groundHeight + state->offset.vx;
    state->field_6C.field_E = state->field_6C.topHeight + state->offset.vz;
    state->field_7C = arg1->subcellCountX;
    state->field_80 = arg1->subcellCountZ;
    state->field_84 = arg1->subcellSize;

    func_8006E150(&state->field_6C, ((DVECTOR*)&state->offset)[0], ((DVECTOR*)&state->offset)[1]);
}

void func_8006E150(s_func_8006E490* arg0, DVECTOR arg1, DVECTOR arg2) // 0x8006E150
{
    DVECTOR subroutine_arg4;
    VECTOR  sp18;
    VECTOR  pos;
    s16     temp_lo;
    s16     temp_lo_2;
    s32     temp_a0_3;
    s32     temp_lo_4;
    s32     temp_t0;
    s32     temp_t1;
    s32     var_a2;
    s32     var_a3;
    u32     flags;

    flags = OrientationFlags_None;
    arg0->field_1C = Q8(0.0f);

    if (arg0->field_8.vx < 0 && arg0->field_C < 0 &&
        arg0->field_8.vy < 0 && arg0->field_E < 0)
    {
        return;
    }

    temp_lo   = arg0->field_10 * arg0->field_18;
    temp_lo_2 = arg0->field_14 * arg0->field_18;

    if (arg0->field_8.vx >= temp_lo && arg0->field_C >= temp_lo &&
        arg0->field_8.vy >= temp_lo_2 && arg0->field_E >= temp_lo_2)
    {
        return;
    }

    subroutine_arg4 = arg0->field_8;

    sp18.vz  = 0;
    sp18.pad = 0;

    sp18.vx = Q12(arg0->field_10);
    sp18.vy = Q12(arg0->field_14);

    if (arg1.vx < 0)
    {
        flags             |= OrientationFlags_InvertX;
        subroutine_arg4.vx = -subroutine_arg4.vx;

        arg1.vx = -arg1.vx;
        sp18.vz = -sp18.vx;
        sp18.vx = 0;
    }

    if (arg2.vx < 0)
    {
        flags             |= OrientationFlags_InvertZ;
        subroutine_arg4.vy = -subroutine_arg4.vy;
        arg2.vx            = -arg2.vx;
        sp18.pad           = -sp18.vy;
        sp18.vy            = 0;
    }

    if (arg1.vx < arg2.vx)
    {
        flags |= OrientationFlags_SwapXz;

        temp_a0_3          = subroutine_arg4.vx;
        subroutine_arg4.vx = subroutine_arg4.vy;
        subroutine_arg4.vy = temp_a0_3;

        temp_a0_3 = arg1.vx;
        arg1.vx   = arg2.vx;
        arg2.vx   = temp_a0_3;

        temp_a0_3 = sp18.vz;
        sp18.vz   = sp18.pad;
        sp18.pad  = temp_a0_3;
        temp_a0_3 = sp18.vx;
        sp18.vx   = sp18.vy;
        sp18.vy   = temp_a0_3;
    }

    if (subroutine_arg4.vx + arg1.vx < Q12_MULT(arg0->field_18, sp18.vx))
    {
        sp18.vx = Q12(subroutine_arg4.vx + arg1.vx) / arg0->field_18;
    }

    pos.vx = Q12(subroutine_arg4.vx) / arg0->field_18;
    pos.vy = Q12(subroutine_arg4.vy) / arg0->field_18;
    pos.vz = Q12(1.0f);

    pos.pad  = Q12(arg2.vx) / arg1.vx;
    temp_lo_4 = Q12_MULT(pos.pad, Q12_FRACT(pos.vx));

    if (FP_FROM(sp18.vx, Q12_SHIFT) < FP_FROM(pos.vx, Q12_SHIFT))
    {
        return;
    }

    do
    {
        func_8006E490(arg0, flags, pos.vx, pos.vy);

        temp_t0 = pos.vy;
        temp_t1 = pos.vx;
        var_a3  = temp_t0 + pos.pad;
        var_a2  = temp_t1 + Q12(1.0f);

        pos.vy = var_a3;
        pos.vx = var_a2;

        if (FP_FROM(temp_t0, Q12_SHIFT) < FP_FROM(var_a3, Q12_SHIFT))
        {
            if (Q12_FRACT(var_a3) < temp_lo_4)
            {
                func_8006E490(arg0, flags, var_a2, temp_t0);
            }
            else
            {
                func_8006E490(arg0, flags, temp_t1, var_a3);
            }
        }
    }
    while (arg0->field_1C < Q8(0.08f) && FP_FROM(pos.vx, Q12_SHIFT) <= FP_FROM(sp18.vx, Q12_SHIFT));
}

void func_8006E490(s_func_8006E490* arg0, u32 flags, q19_12 posX, q19_12 posZ) // 0x8006E490
{
    q19_12 tempPosX;

    if (flags & OrientationFlags_SwapXz)
    {
        tempPosX = posX;
        posX     = posZ;
        posZ     = tempPosX;
    }

    if (flags & OrientationFlags_InvertZ)
    {
        posZ = -posZ;
    }

    if (flags & OrientationFlags_InvertX)
    {
        posX = -posX;
    }

    posX = FP_FROM(posX, Q12_SHIFT);
    posZ = FP_FROM(posZ, Q12_SHIFT);
    if (posX >= Q12(0.0f) && posX < arg0->field_10 &&
        posZ >= Q12(0.0f) && posZ < arg0->field_14)
    {
        arg0->field_20[arg0->field_1C].vx = posX;
        arg0->field_20[arg0->field_1C].vz = posZ;
        arg0->field_1C++;
    }
}

void func_8006E53C(s_RayState* state, s_IpdCollSubcellRange* subcellRanges, s_IpdCollisionData* collData) // 0x8006E53C
{
    s32                    i;
    s32                    temp_v0;
    s32                    temp_v0_2;
    bool                   hasSurface;
    bool                   cond1;
    bool                   cond2;
    s32                    surfaceIdx0;
    s32                    surfaceIdx1;
    s32                    idx;
    s_IpdCollisionData_18* temp_a1_2;
    s_IpdCollSubcell*      curSubcell;

    for (i = subcellRanges[0].field_0; i < subcellRanges[1].field_0; i++)
    {
        idx = collData->ptr_28[i];

        if (collData->subcellCheckCount >= collData->subcellCheckIdx[idx])
        {
            collData->subcellCheckIdx[idx] = collData->subcellCheckCount + 1;

            if (idx < collData->subcellCount)
            {
                curSubcell = &collData->subcells[idx];

                temp_v0 = (u16)state->field_4 >> (curSubcell->field_0_14 * 4 | curSubcell->field_2_14);

                if (temp_v0 & (1 << 0))
                {
                    surfaceIdx0 = curSubcell->surfaceIdx0;
                    surfaceIdx1   = curSubcell->surfaceIdx1;

                    hasSurface = surfaceIdx0 != UCHAR_MAX && surfaceIdx1 != UCHAR_MAX;

                    if (state->field_0 == true)
                    {
                        if (hasSurface)
                        {
                            continue;
                        }
                    }
                    else
                    {
                        cond1 = false;
                        cond2 = false;

                        if (surfaceIdx0 == UCHAR_MAX || collData->surfaces[surfaceIdx0].groundType == GroundType_Default ||
                            collData->surfaces[surfaceIdx0].groundType == GroundType_None)
                        {
                            cond1 = true;
                        }

                        if (surfaceIdx1 == UCHAR_MAX || collData->surfaces[surfaceIdx1].groundType == GroundType_Default ||
                            collData->surfaces[surfaceIdx1].groundType == GroundType_None)
                        {
                            cond2 = true;
                        }

                        if (cond1 && cond2)
                        {
                            continue;
                        }
                    }

                    func_8006E78C(state, curSubcell, collData->splitVertices, collData->surfaces, hasSurface);
                }
            }
            else
            {
                temp_a1_2 = &collData->ptr_18[idx - collData->subcellCount];
                temp_v0_2 = (u16)state->field_4 >> temp_a1_2->field_0_8;

                if ((temp_v0_2 & (1 << 0)) &&
                    (state->field_0 == true ||
                     (temp_a1_2->groundType != GroundType_Default &&
                      temp_a1_2->groundType != GroundType_None)) &&
                    temp_a1_2->field_8 >= state->field_6)
                {
                    func_8006EB8C(state, temp_a1_2);
                }
            }
        }
    }
}

void func_8006E78C(s_RayState* state, s_IpdCollSubcell* subcell, SVECTOR3* splitVerts, s_IpdCollSurface* surfaces, bool hasSurface) // 0x8006E78C
{
    SVECTOR   sp0;
    SVECTOR   sp8;
    SVECTOR3  maybeSplitDiff;
    s32       var_a3;
    q19_12    unkX;
    q19_12    unkZ;
    s32       var_a2;
    s32       groundType; // `e_GroundType`
    SVECTOR3* splitVert1;
    SVECTOR3* splitVert0;
    s32       unkXz;
    s32       var_v1;

    groundType = GroundType_Default;
    splitVert1  = &splitVerts[subcell->splitVertexIdx1];
    splitVert0  = &splitVerts[subcell->splitVertexIdx0];

    if (state->field_5E >= splitVert1->vy || state->field_5E >= splitVert0->vy)
    {
        if (subcell->surfaceIdx0 != UCHAR_MAX)
        {
            groundType = surfaces[subcell->surfaceIdx0].groundType;
        }
        if (subcell->surfaceIdx1 != UCHAR_MAX)
        {
            groundType = surfaces[subcell->surfaceIdx1].groundType;
        }

        unkXz = PACKED_XZ16(state->field_58, state->field_5A);
        gte_ldR11R12(unkXz);
        gte_ldR13R21(unkXz);
        gte_ldvxy0(PACKED_XZ16(splitVert1->vx - state->field_6C.groundHeight, splitVert1->vz - state->field_6C.topHeight));
        gte_ldvz0();
        gte_rtv0();
        gte_stMAC12(&sp0);

        gte_ldvxy0(PACKED_XZ16(splitVert0->vx - state->field_6C.groundHeight, splitVert0->vz - state->field_6C.topHeight));
        gte_ldvz0();
        gte_rtv0();
        gte_stMAC12(&sp8);

        if ((sp0.vy & 0x8000) != (sp8.vy & 0x8000))
        {
            if (state->field_0 == true)
            {
                gte_ldsxy3(0, *(s32*)&sp0.vx, *(s32*)&sp8.vx);
                gte_nclip();

                if (gte_stMAC0() >= 0)
                {
                    if (subcell->surfaceIdx0 != UCHAR_MAX)
                    {
                        return;
                    }
                }
                else
                {
                    if (subcell->surfaceIdx1 != UCHAR_MAX)
                    {
                        return;
                    }
                }
            }

            if (sp0.vy != sp8.vy)
            {
                var_v1 = ((sp0.vy << 12) / (sp0.vy - sp8.vy));
                var_a3 = (((sp8.vx - sp0.vx) * var_v1) >> 12) + sp0.vx;
                if (var_a3 >= 0 && state->rayDistance >= var_a3)
                {
                    gte_lddp(var_v1);
                    gte_ldsv3_(splitVert0->vx - splitVert1->vx, splitVert0->vy - splitVert1->vy, splitVert0->vz - splitVert1->vz);
                    gte_gpf12();
                    gte_stsv(&maybeSplitDiff);

                    maybeSplitDiff.vx += splitVert1->vx;
                    maybeSplitDiff.vy += splitVert1->vy;
                    maybeSplitDiff.vz += splitVert1->vz;

                    var_a2 = state->from.vy + state->field_4E;
                    if (state->offset.vy != Q8(0.0f))
                    {
                        var_a2 += (state->offset.vy * var_a3) / state->rayDistance;
                    }

                    if (var_a2 >= maybeSplitDiff.vy && var_a3 < state->field_8)
                    {
                        unkX = subcell->field_2_0;
                        unkZ = -subcell->field_0_0;
                        if (state->field_0 != true && hasSurface && (sp8.vy - sp0.vy) > 0)
                        {
                            unkX = -unkX;
                            unkZ = subcell->field_0_0;
                        }

                        state->field_8  = var_a3;
                        state->field_C  = (maybeSplitDiff.vx + state->field_6C.positionX);
                        state->field_10 = (var_a2 - state->field_4E);
                        state->field_14 = (maybeSplitDiff.vz + state->field_6C.positionZ);
                        state->groundHeight = maybeSplitDiff.vy;
                        state->field_24 = unkX;
                        state->field_26 = unkZ;
                        state->field_20 = NULL;
                        state->groundType = groundType;
                    }
                }
            }
        }
    }
}

void func_8006EB8C(s_RayState* state, s_IpdCollisionData_18* arg1) // 0x8006EB8C
{
    SVECTOR sp10;
    SVECTOR sp18;
    s16     temp_a1_3;
    s32     temp_v0;
    s16     temp_a1;
    s32     temp_v1;

    temp_a1 = arg1->field_8;
    if (state->field_5E <= arg1->offset.vy)
    {
        return;
    }

    temp_v1 = PACKED_XZ16(state->field_58, state->field_5A);
    gte_ldR11R12(temp_v1);
    gte_ldR13R21(temp_v1);
    gte_ldvxy0(PACKED_XZ16(arg1->offset.vx - state->field_6C.groundHeight, arg1->offset.vz - state->field_6C.topHeight));
    gte_ldvz0();
    gte_rtv0();
    gte_stMAC12(&sp10);

    if (-temp_a1 < sp10.vx && sp10.vx < (state->rayDistance + temp_a1) && -temp_a1 < sp10.vy && sp10.vy < temp_a1)
    {
        temp_v0   = SquareRoot0(SQUARE(temp_a1) - SQUARE(sp10.vy));
        temp_a1_3 = sp10.vx - temp_v0;

        if (temp_a1_3 >= -temp_v0 && state->rayDistance >= temp_a1_3 && temp_a1_3 < state->field_8)
        {
            gte_lddp(Q12(temp_a1_3) / state->rayDistance);
            gte_ldsv3_(state->offset.vx, state->offset.vy, state->offset.vz);
            gte_gpf12();
            gte_stsv(&sp18);

            if ((sp18.vy + state->from.vy + state->field_4E) >= arg1->offset.vy)
            {
                state->field_8  = temp_a1_3;
                state->field_C  = sp18.vx + state->field_6C.groundHeight + state->field_6C.positionX;
                state->field_10 = sp18.vy + state->from.vy;
                state->field_14 = sp18.vz + state->field_6C.topHeight + state->field_6C.positionZ;
                state->groundHeight = arg1->offset.vy;
                state->field_24 = (sp18.vx + state->field_6C.groundHeight) - arg1->offset.vx;
                state->field_26 = (sp18.vz + state->field_6C.topHeight) - arg1->offset.vz;
                state->field_20 = NULL;
                state->groundType = arg1->groundType;
            }
        }
    }
}

void func_8006EE0C(s_RayState_6C* arg0, bool useCylinder, const s_SubCharacter* chara) // 0x8006EE0C
{
    q19_12 offsetZ;
    q19_12 offsetX;
    q19_12 topHeight;

    if (useCylinder == true)
    {
        arg0->field_C = Q12_TO_Q8(chara->collision.cylinder.radius);
        offsetX       = chara->collision.shapeOffsets.cylinder.vx;
        offsetZ       = chara->collision.shapeOffsets.cylinder.vz;
        topHeight     = chara->position.vy + chara->collision.box.bottom;
    }
    else
    {
        arg0->field_C = Q12_TO_Q8(chara->collision.cylinder.field_2);
        offsetX       = chara->collision.shapeOffsets.box.vx;
        offsetZ       = chara->collision.shapeOffsets.box.vz;
        topHeight     = chara->position.vy + chara->collision.box.height;
    }

    arg0->topHeight    = Q12_TO_Q8(topHeight);
    arg0->positionX    = Q12_TO_Q8(chara->position.vx + offsetX);
    arg0->positionZ    = Q12_TO_Q8(chara->position.vz + offsetZ);
    arg0->groundHeight = Q12_TO_Q8(chara->position.vy + chara->collision.box.top);
}

void func_8006EEB8(s_RayState* state, s_SubCharacter* chara) // 0x8006EEB8
{
    VECTOR3 pos; // Q23.8
    s32     bound;
    q3_12   alpha;
    q3_12   clampedRayDist;
    q23_8   x1;
    q23_8   z1;
    q23_8   x0;
    q23_8   z0;
    q19_12  var_v1;

    if (state->from.vx <= state->field_3C)
    {
        x0 = state->from.vx;
        z0 = state->field_3C;
    }
    else
    {
        x0 = state->field_3C;
        z0 = state->from.vx;
    }

    if (state->from.vz <= state->field_44)
    {
        z1 = state->from.vz;
        x1 = state->field_44;
    }
    else
    {
        z1 = state->field_44;
        x1 = state->from.vz;
    }

    bound = state->field_6C.field_C;
    if ((state->field_6C.positionX + bound) < x0 ||
         z0 < (state->field_6C.positionX - bound))
    {
        return;
    }

    if ((state->field_6C.positionZ + bound) < z1 || x1 < (state->field_6C.positionZ - bound) ||
        ((state->from.vy + state->field_4E) < state->field_6C.groundHeight && (state->field_40 + state->field_4E) < state->field_6C.groundHeight) ||
        ((state->from.vy + state->field_4C) > state->field_6C.topHeight && state->field_6C.topHeight < (state->field_40 + state->field_4C)))
    {
        return;
    }

    alpha = func_8006C248(*(s32*)&state->field_58, state->rayDistance,
                          state->field_6C.positionX - state->from.vx,
                          state->field_6C.positionZ - state->from.vz,
                          bound);
    if (alpha == NO_VALUE)
    {
        return;
    }

    clampedRayDist = Q12_MULT(state->rayDistance, alpha);
    if (clampedRayDist >= state->field_8)
    {
        return;
    }

    pos.vy = state->from.vy + (Q12_MULT(state->offset.vy, alpha));
    if ((pos.vy + state->field_4E) < state->field_6C.groundHeight ||
        state->field_6C.topHeight < (pos.vy + state->field_4C))
    {
        if (state->offset.vy == 0)
        {
            return;
        }

        if ((pos.vy + state->field_4E) < state->field_6C.groundHeight)
        {
            var_v1 = Q12(state->field_6C.groundHeight - (state->from.vy + state->field_4E)) / state->offset.vy;
            if (var_v1 > Q12(1.0f))
            {
                return;
            }
            pos.vy = state->field_6C.groundHeight - state->field_4E;
        }
        else
        {
            var_v1 = Q12(state->field_6C.topHeight - (state->from.vy + state->field_4C)) / state->offset.vy;
            if (var_v1 > Q12(1.0f))
            {
                return;
            }
            pos.vy = state->field_6C.topHeight - state->field_4C;
        }

        pos.vx = state->from.vx + Q12_MULT(state->offset.vx, var_v1);
        pos.vz = state->from.vz + Q12_MULT(state->offset.vz, var_v1);
        if ((SQUARE(state->field_6C.positionX - pos.vx) + SQUARE(state->field_6C.positionZ - pos.vz)) >= SQUARE(state->field_6C.field_C))
        {
            return;
        }
    }
    else
    {
        pos.vx = state->from.vx + Q12_MULT(state->offset.vx, alpha);
        pos.vz = state->from.vz + Q12_MULT(state->offset.vz, alpha);
    }

    state->field_8  = clampedRayDist;
    state->field_C  = pos.vx;
    state->field_10 = pos.vy;
    state->field_14 = pos.vz;
    state->groundHeight = state->field_6C.groundHeight;
    state->field_24 = pos.vx - state->field_6C.positionX;
    state->field_26 = pos.vz - state->field_6C.positionZ;
    state->field_20 = chara;
    state->groundType = GroundType_Default;
}
