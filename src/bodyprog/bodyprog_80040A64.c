#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"

// Known contents:
// - Animation funcs

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80040A64);

void func_80040B6C() {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80040B74);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80040BAC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80040E7C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80041074);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800410D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_8004122C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_8004137C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800414E0);

s32 func_80041ADC(s32 queueIdx) // 80041ADC
{
    if (queueIdx == NO_VALUE)
        return 0;

    if (Fs_QueueIsEntryLoaded(queueIdx) == 0)
        return 1;

    return 2;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80041B1C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80041BA0);

void func_80041C24(s_80041CEC* arg0, s32 arg1, s32 arg2) // 0x80041C24
{
    bzero(&D_800C1020, 1420);
    func_80041CB4((void*)((char*)&D_800C1020 + 312), arg0);

    D_800C1020.field_150 = arg1;
    D_800C1020.field_154 = arg2;
    D_800C1020.field_158 = 0;
    D_800C1020.field_588 = 1;

    func_80041D10((void*)((char*)&D_800C1020 + 348), 4);
    func_80041D48();
    func_80041E98();
}

// TODO: Likey not `s_Skeleton` after all. Expected struct fields don't match.
#ifdef NON_MATCHING
void func_80041CB4(s_Skeleton* skel, s_80041CEC* arg1) // 0x80041CB4
{
    skel->boneCount_0 = arg1; // TODO: `boneCount` isn't a ptr.
    func_80041CEC(arg1);

    skel->bones_8 = NULL;
    skel->field_4 = NO_VALUE;
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80041CB4);
#endif

void func_80041CEC(s_80041CEC* arg0) // 0x80041CEC
{
    arg0->field_0 = 48;
    arg0->field_1 = 6;
    arg0->field_2 = 1;
    arg0->field_3 = 0;
    arg0->field_8 = 0;
}

void func_80041D10(s_Skeleton* skels, s32 size) // 0x80041D10
{
    s_Skeleton* end;

    end = skels + size;
    while (skels < end)
    {
        skels->field_4 = NO_VALUE;
        skels = (s_Skeleton*)((u8*)skels + sizeof(s_Skeleton)); 
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80041D48);

void func_80041E98() // 0x80041E98
{
    bzero(&D_800C1020, 308);
    D_800C1020.field_1C = 512;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80041ED0);

void func_80041FF0() // 0x80041FF0
{
    func_80042300(&D_800C1020, D_800C1020.field_158);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_8004201C);

void func_800420C0() // 0x800420C0
{
    func_800420FC();
    func_80042300(&D_800C1020, D_800C1020.field_158);
    func_80041D48();
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800420FC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80042178);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800421D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80042300);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800423F4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_8004255C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800425D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800426E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_8004287C);

s32 func_80042C04(s32 idx) // 0x80042C04
{
    return (func_80041B1C(&D_800C117C[idx]) < 3) ^ 1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80042C3C);

s32 func_80042DE8(s32 posX, s32 posZ, s32 fileChunkCoordX, s32 fileChunkCoordZ, s32 clip) // 0x80042DE8
{
    #define DIST_THRESHOLD FP_METER(16.0f)

    s32 dist;

    dist = func_80042E2C(FP_FROM(posX, Q4_SHIFT), FP_FROM(posZ, Q4_SHIFT), fileChunkCoordX, fileChunkCoordZ);
    if (clip != 0)
    {
        dist -= DIST_THRESHOLD;
        if (dist < 0)
        {
            dist = 0;
        }
    }

    return dist;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80042E2C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80042EBC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800431E4);

void func_80043338(s_80043338* arg0, s32 posX0, s32 posZ0, s32 posX1, s32 posZ1, s32 clip) // 0x80043338
{
    arg0->field_C = func_80042DE8(posX0, posZ0, arg0->fileChunkCoordX_8, arg0->fileChunkCoordZ_A, clip);
    arg0->field_10 = func_80042DE8(posX1, posZ1, arg0->fileChunkCoordX_8, arg0->fileChunkCoordZ_A, clip);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800433B8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043554);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043578);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800435E4);

s32 func_800436D8(s_80043338* arg0, s32 fileIdx, s16 fileChunkCoordX, s16 fileChunkCoordZ, s32 posX0, s32 posZ0, s32 posX1, s32 posZ1, s32 clip) // 0x800436D8
{
    // Return `NO_VALUE` if no file specified.
    if (fileIdx == NO_VALUE)
    {
        return fileIdx;
    }

    // Store file chunk coords and read file.
    arg0->fileChunkCoordX_8 = fileChunkCoordX;
    arg0->fileChunkCoordZ_A = fileChunkCoordZ;
    arg0->queueEntryIdx_4 = Fs_QueueStartRead(fileIdx, arg0->field_0);

    // Compute and store distance to file chunk edge in `arg0`.
    func_80043338(arg0, posX0, posZ0, posX1, posZ1, clip);

    // Return queue entry index.
    return arg0->queueEntryIdx_4;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043740);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043830);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_8004393C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043A24);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043B34);

s32 func_80043B70(s_80043B70* arg0) // 0x80043B70
{
    if (arg0->field_1 == 0)
    {
        return 0;
    }

    return func_80056888(arg0->field_4);
}

s_80043BA4* func_80043BA4(s_80043BA4* arg0) // 0x80043BA4
{
    if (arg0->field_1 != 0)
    {
        return arg0 + 42;
    }

    return NULL;
}

void func_80043BC4(s_80043B70* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) // 0x80043BC4
{
    if (arg0->field_1 != 0)
    {
        return;
    }

    arg0->field_1 = 1;

    func_80043DA4();
    func_8006993C(arg0 + 3); // TODO: Pointer?
    func_800560FC(arg0->field_4);
    func_8008E4EC(arg0->field_4);
    func_80043C7C(arg0, arg3, arg4, arg5);
    func_80056954(arg0->field_4);
    func_80043E50(arg0, arg1, arg2);
    func_80043F88(arg0, arg0->field_14);
}

void func_80043C7C(s_80043B70* arg0, s32 arg1, s32* arg2, s32 arg3) // 0x80043C7C
{
    if (arg0->field_1 == 0)
    {
        return;
    }

    if (arg1 != 0)
    {
        func_80056774(arg0->field_4, arg1, &func_80043D44, arg3, 1);
    }

    if (arg2 != NULL)
    {
        func_80056774(arg0->field_4, arg2, &func_80043D64, arg3, 1);
    }
}

s32 func_80043D00(s_80043B70* arg0) // 0x80043D00
{
    if (arg0->field_1 == 0)
    {
        return 0;
    }

    return func_80056348(&func_80043D64, arg0->field_4);
}

s32 func_80043D44(s32 arg0) // 0x80043D44
{
    return func_80043D64(arg0) == 0;
}

s32 func_80043D64(s32 arg0) // 0x80043D64
{
    u32 i;
    u8 var;

    i = arg0 + 7;
    for (i = (arg0 + 7); i >= arg0; i--)
    {
        var = *(u8*)i;
        if (var != NULL)
        {
            return var == 0x48;
        }
    }

    return 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043DA4);

void func_80043E50(s_80043E50* arg0, s32* arg1, s32 arg2) // 0x80043E50
{
    s32 i;
    s32 j;
    s_80043E50Sub* element;

    for (i = 0; i < arg0->elementCount_8; i++)
    {
        element = &arg0->elements_14[i];
        if (element->field_0 == 0)
        {
            element->field_C = func_80043F2C(&element->field_4, arg0->field_4);
        }
        else
        {
            for (j = 0; j < arg2; j++)
            {
                element->field_C = func_80043F2C(&element->field_4, arg1[j]);
                if (element->field_C != 0)
                {
                    break;
                }
            }
        }
    }
}

s_80043F2C* func_80043F2C(s_80043F2C* arg0, s_80043F2C* arg1) // 0x80043F2C
{
    u8 size;
    s_80043F2C* var;
    s32 i;

    size = arg1->field_8;
    var = arg1->field_C;

    for (i = 0; i < size; i++)
    {
        if (arg0->field_0 == var->field_0 &&
            arg0->field_4 == var->field_4)
        {
            return var;
        }

        var++;
    }

    return NULL;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043F88);

void func_80044044(s_80044044* arg0, s32 arg1, s32 arg2) // 0x80044044
{
    s32 var0;
    s32 var1;

    var0 = arg0->field_2;
    var1 = arg0->field_3;

    arg0->field_2 = arg1;
    arg0->field_3 = arg2;
    arg0->field_54 = (arg0->field_54 + ((arg1 - var0) * 0x2800));
    arg0->field_58 = (arg0->field_58 + ((arg2 - var1) * 0x2800));
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80044090);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80044420);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800445A4);

// ========================================
// ANIMATION
// ========================================

// Anim func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800446D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80044918);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80044950);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800449AC);

static inline s32 Anim_GetTimeStep(s_Model* model, s_AnimInfo* targetAnim)
{
    s32 timeDelta;

    if (model->anim_4.flags_2 & AnimFlag_Unk1)
    {
        timeDelta = func_800449AC(model, targetAnim);
        return FP_MULTIPLY((s64)timeDelta, (s64)g_DeltaTime0, Q12_SHIFT);
    }

    return 0;
}

void Anim_Update0(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_AnimInfo* targetAnim) // 0x800449F0
{
    s32 setAnimIdx;
    s32 timeStep;
    s32 newTime;
    s32 newKeyframeIdx0;
    s32 targetTime;
    s32 alpha;

    setAnimIdx = 0;

    // Get time step.
    timeStep = Anim_GetTimeStep(model, targetAnim);

    // Compute new time.
    newTime         = model->anim_4.time_4;
    newKeyframeIdx0 = FP_FROM(newTime, Q12_SHIFT);
    if (timeStep != 0)
    {
        // Clamp new time against target time?
        newTime   += timeStep;
        targetTime = FP_TO(targetAnim->keyframeIdx1_E, Q12_SHIFT);
        if (newTime < targetTime)
        {
            targetTime = FP_TO(targetAnim->keyframeIdx0_C, Q12_SHIFT);
            if (newTime <= targetTime)
            {
                newTime    = targetTime;
                setAnimIdx = 1;
            }
        }
        else
        {
            newTime    = targetTime;
            setAnimIdx = 1;
        }

        newKeyframeIdx0 = FP_FROM(newTime, Q12_SHIFT);
    }

    // Update skeleton.
    alpha = newTime & 0xFFF;
    if ((model->anim_4.flags_2 & AnimFlag_Unk1) || (model->anim_4.flags_2 & AnimFlag_Unk2))
    {
        func_800446D8(skel, coord, newKeyframeIdx0, newKeyframeIdx0 + 1, alpha);
    }

    // Update frame data.
    model->anim_4.time_4	     = newTime;
    model->anim_4.keyframeIdx0_8 = newKeyframeIdx0;
    model->anim_4.keyframeIdx1_A = 0;

    // Update anim.
    if (setAnimIdx != 0)
    {
        model->anim_4.animIdx_0 = targetAnim->animIdx_6;
    }
}

void Anim_Update1(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_AnimInfo* targetAnim) // 0x80044B38
{
    s32 keyframeIdx0;
    s32 keyframeIdx1;
    s32 nextKeyframeIdx;
    s32 keyframeDelta;
    s32 currentKeyframeTime;
    s32 nextKeyframeTime;
    s32 keyframeTimeDelta;
    s32 timeStep;
    s32 newTime;
    s32 newKeyframeIdx0;
    s32 newKeyframeIdx1;
    s32 alpha;

    keyframeIdx0    = targetAnim->keyframeIdx0_C;
    keyframeIdx1    = targetAnim->keyframeIdx1_E;
    nextKeyframeIdx = keyframeIdx1 + 1;
    keyframeDelta   = nextKeyframeIdx - keyframeIdx0;

    currentKeyframeTime = FP_TO(keyframeIdx0, Q12_SHIFT);
    nextKeyframeTime    = FP_TO(nextKeyframeIdx, Q12_SHIFT);
    keyframeTimeDelta   = FP_TO(keyframeDelta, Q12_SHIFT);

    // Get time step.
    timeStep = Anim_GetTimeStep(model, targetAnim);

    // Wrap new time to valid range?
    newTime = model->anim_4.time_4 + timeStep;
    while (newTime < currentKeyframeTime)
    {
        newTime += keyframeTimeDelta;
    }
    while (newTime >= nextKeyframeTime)
    {
        newTime -= keyframeTimeDelta;
    }

    // Compute new keyframe 1.
    newKeyframeIdx0 = FP_FROM(newTime, Q12_SHIFT);
    newKeyframeIdx1 = newKeyframeIdx0 + 1;
    if (newKeyframeIdx1 == nextKeyframeIdx)
    {
        newKeyframeIdx1 = keyframeIdx0;
    }

    // Update skeleton.
    alpha = newTime & 0xFFF;
    if ((model->anim_4.flags_2 & AnimFlag_Unk1) || (model->anim_4.flags_2 & AnimFlag_Unk2))
    {
        func_800446D8(skel, coord, newKeyframeIdx0, newKeyframeIdx1, alpha);
    }

    // Update frame data.
    model->anim_4.time_4         = newTime;
    model->anim_4.keyframeIdx0_8 = newKeyframeIdx0;
    model->anim_4.keyframeIdx1_A = 0;
}

void Anim_Update2(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_AnimInfo* targetAnim) // 0x80044CA4
{
    s32 setAnimIdx;
    s32 newKeyframeIdx0;
    s32 newKeyframeIdx1;
    s32 timeStep;
    s32 alpha;
    
    setAnimIdx      = 0;
    newKeyframeIdx0 = targetAnim->keyframeIdx0_C;
    newKeyframeIdx1 = targetAnim->keyframeIdx1_E;

    // If no target frame 0 set, default to current frame index 0.
    if (newKeyframeIdx0 == NO_VALUE)
    {
        newKeyframeIdx0 = model->anim_4.keyframeIdx0_8;
    }

    // Get time step.
    timeStep = Anim_GetTimeStep(model, targetAnim);

    // Set time.
    alpha  = model->anim_4.keyframeIdx1_A;
    alpha += timeStep;
    if (alpha >= FP_ALPHA(0.5f))
    {
        model->anim_4.time_4 = FP_TO(newKeyframeIdx1, 12);
    }
    else
    {
        model->anim_4.time_4 = FP_TO(newKeyframeIdx0, Q12_SHIFT);
    }

    // Progress keyframes.
    if (alpha >= FP_ALPHA(1.0f))
    {
        newKeyframeIdx0              = newKeyframeIdx1;
        model->anim_4.keyframeIdx0_8 = newKeyframeIdx1;
        
        alpha      = 0;
        setAnimIdx = 1;
    }

    // Update skeleton.
    if ((model->anim_4.flags_2 & AnimFlag_Unk1) || (model->anim_4.flags_2 & AnimFlag_Unk2))
    {
        func_800446D8(skel, coord, newKeyframeIdx0, newKeyframeIdx1, alpha);
    }

    // Update frame 1.
    model->anim_4.keyframeIdx1_A = alpha;

    // Update anim.
    if (setAnimIdx != 0)
    {
        model->anim_4.animIdx_0 = targetAnim->animIdx_6;
    }
}

void Anim_Update3(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_AnimInfo* targetAnim) // 0x80044DF0
{
    s32 keyframeIdx0;
    s32 keyframeIdx1;
    s32 timeDelta;
    register s32 timeStep asm("v0"); // HACK: Manually set register to match.
    s32 newKeyframeIdx1;
    s32 sinValue;
    s32 newTime;
    s32 alpha;

    keyframeIdx0 = targetAnim->keyframeIdx0_C;
    keyframeIdx1 = targetAnim->keyframeIdx1_E;

    // Compute time step. NOTE: Can't call `Anim_GetTimeStep` inline due to register constraints.
    if (model->anim_4.flags_2 & AnimFlag_Unk1)
    {
        timeDelta = func_800449AC(model, targetAnim);
        timeStep = FP_MULTIPLY((s64)timeDelta, (s64)g_DeltaTime0, Q12_SHIFT);
    }
    else
    {
        timeStep = 0;
    }

    // Update keyframe 1.
    newKeyframeIdx1              = model->anim_4.keyframeIdx1_A + timeStep;
    model->anim_4.keyframeIdx1_A = newKeyframeIdx1;

    // Sine-based easing?
    sinValue = shRsin((newKeyframeIdx1 / 2) - FP_ALPHA(0.25f));
    alpha    = (sinValue / 2) + FP_ALPHA(0.5f);

    // Clamp new time to keyframe 0 or 1.
    if (alpha >= FP_ALPHA(0.5f))
    {
        newTime = FP_TO(keyframeIdx0, Q12_SHIFT);
    }
    else
    {
        newTime = FP_TO(keyframeIdx1, Q12_SHIFT);
    }

    // Update time.
    model->anim_4.time_4 = newTime;

    // Update skeleton.
    if ((model->anim_4.flags_2 & AnimFlag_Unk1) || (model->anim_4.flags_2 & AnimFlag_Unk2))
    {
        func_800446D8(skel, coord, keyframeIdx0, keyframeIdx1, alpha);
    }

    // Update keyframe 0.
    model->anim_4.keyframeIdx0_8 = FP_FROM(newTime, Q12_SHIFT);
}

void func_80044F14(s32 mat, s16 z, s16 x, s16 y) // 0x80044F14
{
    *(s16*)0x1F800004 = z;
    *(s16*)0x1F800002 = y;
    *(s16*)0x1F800000 = x;
    
    func_80096E78((SVECTOR*)0x1F800000, (MATRIX*)0x1F800008);
    MulMatrix(mat + 4, (MATRIX*)0x1F800008);
}

s8 func_80044F6C(s8* ptr, s32 arg1) // 0x80044F6C
{
    s8 temp;

    if (arg1 != 0)
    {
        D_800C15B0 = ptr;
    }

    if (D_800C15B0[0] != -3)
    {
        D_800C15B4 = D_800C15B0[0];
        D_800C15B0++;
    }
    else if (++D_800C15B4 >= (D_800C15B0[1] - 1))
    {
        D_800C15B0++;
    }

    return D_800C15B4;
}

void func_80044FE0(s_Skeleton* skel, s_Bone* bones, u8 boneCount) // 0x80044FE0
{
    skel->bones_8 = bones;
    skel->boneCount_0 = boneCount;
    skel->boneIdx_1 = 0;
    skel->field_2 = 1;
    skel->field_4 = 0;

    func_80045014(skel);
}

void func_80045014(s_Skeleton* skel) // 0x80045014
{
    s_Bone* bone = skel->bones_8;

    // Traverse bone hierarchy and clear flags.
    while (bone < &skel->bones_8[skel->boneCount_0])
    {
        bone->flags_0 = 0;
        bone++;
    }
}

// Anim func. Used in tandem with skeleton bone traversal.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_8004506C);

// Anim func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045108);

// Anim func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800451B0);

// Anim func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045258);

// Anim func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800452EC);

// Anim func. Traverses skeleton bones for something.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045360);

// `cond` may actually be another `s_Skeleton` pointer.
void func_800453E8(s_Skeleton* skel, s32 cond) // 0x800453E8
{
    s_Bone* bone;

    // Check if skeleton has bones.
    bone = skel->bones_8;
    if (bone >= &skel->bones_8[skel->boneCount_0])
    {
        return;
    }

    // Traverse bone hierarchy and set flags according to cond.
    while (bone < &skel->bones_8[skel->boneCount_0])
    {
        if (cond != 0)
        {
            bone->flags_0 &= ~(1 << 31);
        }
        else
        {
            bone->flags_0 |= 1 << 31;
        }
        
        bone++;
    }
}

void func_80045468(s_Skeleton* skel, s32* arg1, s32 cond) // 0x80045468
{
    s_Bone* bone;
    s32 status;

    bone = skel->bones_8;

    // Get skeleton status?
    status = func_80044F6C(arg1, 1);
    if (status == -2)
    {
        return;
    }

    // Traverse bone hierarchy and set flags according to cond.
    do
    {
        if (cond != 0)
        {
            bone[status].flags_0 &= ~(1 << 31);
        }
        else
        {
            bone[status].flags_0 |= 1 << 31;
        }
        
        status = func_80044F6C(arg1, 0);
    }
    while (status != -2);
}

// Maybe larger anim func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045534);