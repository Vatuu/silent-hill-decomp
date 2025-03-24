#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"

// Known contents:
// - Animation funcs
// - SD sound lib

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

s32 func_80041ADC(s32 queueIdx)
{
    if (queueIdx == NO_VALUE)
        return 0;
    
    if (Fs_QueueIsEntryLoaded(queueIdx) == 0)
        return 1;
    
    return 2;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80041B1C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80041BA0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80041C24);

void func_80041CB4(s_80041CB4* arg0, s_80041CEC* arg1)
{
    arg0->field_0 = arg1;
    func_80041CEC(arg1);
    
    arg0->field_8 = 0;
    arg0->field_4 = NO_VALUE;
}

void func_80041CEC(s_80041CEC* arg0)
{
    arg0->field_0 = 48;
    arg0->field_1 = 6;
    arg0->field_2 = 1;
    arg0->field_3 = 0;
    arg0->field_8 = 0;
}

void func_80041D10(s_80041D10* array, s32 size)
{
    s_80041D10* end = array + size;
    while (array < end)
    {
        array->field_4 = NO_VALUE;
        array = (s_80041D10*)((u8*)array + sizeof(s_80041D10)); 
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

// TODO: Matched, but checksum fails.
#ifdef NON_MATCHING
s32 func_80042C04(s32 idx) // 0x80042C04
{
    return (func_80041B1C(&D_800C117C[idx]) < 3) ^ 1;
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80042C04);
#endif

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80042C3C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80042DE8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80042E2C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80042EBC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800431E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043338);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800433B8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043554);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043578);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800435E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800436D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043740);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043830);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_8004393C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043A24);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043B34);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043B70);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043BA4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043BC4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043C7C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043D00);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043D44);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043D64);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043DA4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043E50);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043F2C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043F88);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80044044);

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

void Anim_Update(s_Model* model, s_Skeleton* skel, s32 arg2, s_Model* targetModel) // 0x800449F0
{
    s32 setAnimIdx;
    s32 timeDelta;
    s32 timeStep;
    s32 keyframeIdx0;
    s32 newTime;
    s32 targetTime;
    s32 alpha;

    setAnimIdx = 0;

    // Compute time step.
    if (model->anim_4.flags_2 & AnimFlag_Interpolate)
    {
        timeDelta = func_800449AC(model, targetModel);
        timeStep = FP_MULTIPLY((s64)timeDelta, (s64)g_DeltaTime0, Q12_SHIFT);
    }
    else
    {
        timeStep = 0;
    }
    
    // Compute new time.
    newTime = model->anim_4.time_4;
    keyframeIdx0 = FP_FROM(newTime, Q12_SHIFT);
    if (timeStep != 0)
    {
        // Clamp new time against target time?
        newTime += timeStep;
        targetTime = FP_TO(targetModel->anim_4.targetKeyframeIdx_A, Q12_SHIFT);
        if (newTime < targetTime)
        {
            targetTime = FP_TO(targetModel->anim_4.keyframeIdx_8, Q12_SHIFT);
            if (newTime <= targetTime)
            {
                newTime = targetTime;
                setAnimIdx = 1;
            }
        }
        else
        {
            newTime = targetTime;
            setAnimIdx = 1;
        }

        keyframeIdx0 = FP_FROM(newTime, Q12_SHIFT);
    }

    // Update skeleton?
    alpha = newTime & 0xFFF;
    if ((model->anim_4.flags_2 & AnimFlag_Interpolate) || (model->anim_4.flags_2 & AnimFlag_Unk2))
    {
        func_800446D8(skel, arg2, keyframeIdx0, keyframeIdx0 + 1, alpha);
    }

    // Update frame data.
    model->anim_4.time_4 = newTime;
    model->anim_4.keyframeIdx_8 = keyframeIdx0;
    model->anim_4.targetKeyframeIdx_A = 0;

    // Update anim index.
    if (setAnimIdx != 0)
    {
        model->anim_4.animIdx_0 = targetModel->anim_4.flags_2;
    }
}

void func_80044B38(s_Model* model, s_Skeleton* skel, s32 arg2, s_Model* targetModel) // 0x80044B38
{
    s32 targetKeyframeIdx;
    s32 nextKeyframe;
    s32 keyframeDelta;
    s32 fpTime;
    s32 fpNextTime;
    s32 fpTimeDelta;
    s32 keyframeIdx;
    s32 keyframeIdx0;
    s32 keyframeIdx1;
    s32 timeDelta;
    s32 timeStep;
    s32 newTime;
    s32 temp;
    s32 alpha;
    
    keyframeIdx = targetModel->anim_4.keyframeIdx_8;
    targetKeyframeIdx = targetModel->anim_4.targetKeyframeIdx_A;
    nextKeyframe = targetKeyframeIdx + 1;
    keyframeDelta = nextKeyframe - keyframeIdx;

    fpTime = FP_TO(keyframeIdx, Q12_SHIFT);
    fpNextTime = FP_TO(nextKeyframe, Q12_SHIFT);
    fpTimeDelta = FP_TO(keyframeDelta, Q12_SHIFT);

    // Compute time step.
    if (model->anim_4.flags_2 & AnimFlag_Interpolate)
    {
        timeDelta = func_800449AC(model, targetModel);
        timeStep = ((s64)timeDelta * (s64)g_DeltaTime0) >> Q12_SHIFT;
    }
    else
    {
        timeStep = 0;
    }
    
    // Wrap new time to valid range?
    newTime = model->anim_4.time_4 + timeStep;
    while (newTime < fpTime)
    {
        newTime += fpTimeDelta;
    }
    while (newTime >= fpNextTime)
    {
        newTime -= fpTimeDelta;
    }

    keyframeIdx0 = FP_FROM(newTime, Q12_SHIFT);
    keyframeIdx1 = keyframeIdx0 + 1;
    if (keyframeIdx1 == nextKeyframe)
    {
        keyframeIdx1 = keyframeIdx;
    }

    // Update skeleton?
    alpha = newTime & 0xFFF;
    if ((model->anim_4.flags_2 & AnimFlag_Interpolate) || (model->anim_4.flags_2 & AnimFlag_Unk2))
    {
        func_800446D8(skel, arg2, keyframeIdx0, keyframeIdx1, alpha);
    }

    // Update frame data.
    model->anim_4.time_4 = newTime;
    model->anim_4.keyframeIdx_8 = keyframeIdx0;
    model->anim_4.targetKeyframeIdx_A = 0;
}

// Anim func, similar to above.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80044CA4);

// Anim func, similar to above.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80044DF0);

void func_80044F14(s32 mtx, s16 z, s16 x, s16 y) // 0x80044F14
{
    *(s16*)0x1F800004 = z;
    *(s16*)0x1F800002 = y;
    *(s16*)0x1F800000 = x;
    
    func_80096E78((SVECTOR*)0x1F800000, (MATRIX*)0x1F800008);
    MulMatrix(mtx + 4, (MATRIX*)0x1F800008);
}

// Anim func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80044F6C);

// arg0 is maybe skeleton or first bone in bones array.
void func_80044FE0(s_80044FE0* arg0, s32 arg1, s8 arg2) // 0x80044FE0
{
    arg0->field_8 = arg1;
    arg0->field_0 = arg2;
    arg0->field_1 = 0;
    arg0->field_2 = 1;
    arg0->field_4 = 0;
    
    func_80045014(arg0);
}

// Anim func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045014);

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

// Anim func. Traverses skeleton bones for something.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800453E8);

// Anim func. Traverses skeleton bones for something.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045468);

// Maybe larger anim func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045534);

// ========================================
// SOUND
// ========================================

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", SD_EngineCmd);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045B28);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045BC8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045BD8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045D28);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", SD_DriverInit);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045E44);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045FF8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80046048);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800463C0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80046620);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800468EC);

void func_8004690C(s32 arg0) // 0x8004690C
{
    func_8004692C(arg0 & 0xFFFF);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_8004692C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800469AC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800469E8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80046A24);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80046A70);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80046AD8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80046B04);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80046B78);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80046BB4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80046C54);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80046D3C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80046DCC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80046E00);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_8004729C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800472BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80047308);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_8004760C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80047634);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", SD_SetVolume);

#ifdef NON_MATCHING
void Sd_SetVolBgm(s16 arg0, s16 arg1) // 0x80047808
{
    SdSeqSetVol(0, ((arg0 * g_Sd_VolumeBgm) << 9) >> 16, ((arg1 * g_Sd_VolumeBgm) << 9) >> 16);
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", Sd_SetVolBgm);
#endif

#ifdef NON_MATCHING
void Sd_SetVolXa(s16 arg0, s16 arg1) // 0x80047860
{
    SdSetSerialVol(0, ((arg0 * g_Sd_VolumeXa) << 9) >> 16, ((arg1 * g_Sd_VolumeXa) << 9) >> 16);
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", Sd_SetVolXa);
#endif

s32 Sd_GetVolSe(s16 arg0) // 0x800478B8
{
    return ((arg0 * g_Sd_VolumeSe) << 9) >> 16;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800478DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80047A70);

void Sd_SetReverbDepth(s8 depth)
{
    s32 left;

    g_Sd_ReverbDepth = depth;
    
    left = depth & 0xFF;
    SdUtSetReverbDepth(left, left);
}

void Sd_SetReverbEnable(s32 mode)
{
    SdSetSerialAttr(0, 1, mode & 0xFF);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80047B24);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80047B80);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80047D1C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80047D50);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80047DB0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80047E3C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80047F18);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80048000);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_8004807C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800480FC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800481F8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80048244);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800482D8);

void Sd_StopSeq()
{
    func_80046B78();
    SdSeqClose(D_800C37C8);
    
    D_800C1670 = 2;
}

void func_800483D4() // 0x800483D4
{
    s32 sp10;

    if (!(func_80048954(2, CdIntToPos(D_800C37D8->field_8, &sp10), 0) & 0xFF))
    {
        D_800C1670 = 3;
    }
}

void func_80048424() // 0x80048424
{
    if (CdSync(1, 0) == 2)
    {
        CdRead((D_800C37D8->field_4 + 0x7FF) >> 11, FS_BUFFER_1, 0x80);
        
        D_800C1670 = 4;
        D_800C1658 = 0;
    }
    
    D_800C1658++;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80048498);

void func_800485B0() {}

void func_800485B8() {}

void func_800485C0(s32 idx)
{
    D_800C15F8[idx] = 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800485D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80048954);
