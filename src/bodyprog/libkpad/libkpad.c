#include "common.h"
#include "libkpad.h"

#include <psyq/libgte.h>
#include <psyq/libpad.h>
#include <psyq/stdio.h>

#include "bodyprog/math/math.h"

// Data passed to `PadSetActAlign`
u8 D_800B2610[6] = { 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF }; 

// TODO: Could be array?
s_KPad_Handler D_800B13EC = {
    .next_0       = NULL,
    .deviceType_4 = 0,
    .pad_5        = { 0, 0, 0 },
    .alignData_8  = 0,
    .func_C       = func_8009E3B0, // Handles `PadStateDiscon` / `PadStateFindPad`
};

s_KPad_Handler D_800B13FC = {
    .next_0       = NULL,
    .deviceType_4 = 3,
    .pad_5        = { 0, 0, 0 },
    .alignData_8  = 0,
    .func_C       = NULL,
};

s_KPad_Handler D_800B140C = {
    .next_0       = NULL,
    .deviceType_4 = 4,
    .pad_5        = { 0, 0, 0 },
    .alignData_8  = 0,
    .func_C       = func_8009E438, // Handles `PadStateFindCTP1`
};

s_KPad_Handler D_800B141C = {
    .next_0       = NULL,
    .deviceType_4 = 2,
    .pad_5        = { 0, 1, 0 },
    .alignData_8  = 0,
    .func_C       = func_8009E82C,
};

s_KPad_Handler D_800B142C = {
    .next_0       = NULL,
    .deviceType_4 = 1,
    .pad_5        = { 1, 2, 0 },
    .alignData_8  = D_800B2610,
    .func_C       = func_8009E9D0,
};

bool func_8009E198(s_KPadWork* arg0, u32 port) // 0x8009E198
{
    s_KPad_Status status;
    s32           ret;
    const s32     strength = 0x80;

    ret = arg0 != NULL;
    if (ret)
    {
        s16 result = ret;
        port      &= 0x13;

        arg0->actuatorData_4        = 0;
        arg0->channelInfo_8         = (s_KPad_ChannelInfo){ 0 };
        arg0->channels_C            = NULL;
        arg0->freeEffects_10.next_0 = NULL;

        status = (s_KPad_Status){
            .port_0_0         = 0,
            .strength_0_8     = strength,
            .isInit_0_16      = 1,
            .isPaused_0_17    = 1,
            .isEnabled_0_18   = 1,
            .actCount_0_19    = 0,
            .isAlignDone_0_22 = 0,
            .isActSet_0_23    = 0,
            .deviceType_0_24  = 0,
        };

        ret             = port;
        status.port_0_0 = ret;

        arg0->status_0 = status;

        result = (u8)result;
        return result; // @hack This is close to the pattern used in other functions below, 
                       // but doesn't match with the same `ret = result` line they use, strange.
    }

    return ret;
}

s32 func_8009E230(s_KPadWork* arg0) // 0x8009E230
{
    s_KPad_Status status;
    s32           ret;

    status = arg0->status_0;
    ret    = status.isPaused_0_17;
    if (ret)
    {
        s16 result = ret;

        ret                  = ret & 2;
        status.isActSet_0_23 = ret;
        status.isPaused_0_17 = 0;
        arg0->status_0       = status;

        result = (u8)result;
        ret    = result;
    }

    return ret;
}

s32 func_8009E268(s_KPadWork* arg0) // 0x8009E268
{
    s_KPad_Status status;
    s32           ret;

    status = arg0->status_0;
    ret    = status.isPaused_0_17 ^ 1;
    if (ret)
    {
        s16 result = ret;

        ret                  = ret & 2;
        status.isActSet_0_23 = ret;
        status.isPaused_0_17 = 1;
        arg0->status_0       = status;

        result = (u8)result;
        ret    = result;
    }

    return ret;
}

s32 func_8009E2A0(s_KPadWork* arg0) // 0x8009E2A0
{
    s_KPad_Status status;
    s32           ret;

    status = arg0->status_0;
    ret    = status.isEnabled_0_18 ^ 1;
    if (ret)
    {
        s16 result = ret;

        ret                   = ret & 2;
        status.isActSet_0_23  = ret;
        status.isEnabled_0_18 = 1;
        arg0->status_0        = status;

        result = (u8)result;
        ret    = result;
    }

    return ret;
}

s32 func_8009E2D8(s_KPadWork* arg0) // 0x8009E2D8
{
    s_KPad_Status status;
    s32           ret;

    status = arg0->status_0;
    ret    = status.isEnabled_0_18;
    if (ret)
    {
        s16 result = ret;

        ret                   = ret & 2;
        status.isActSet_0_23  = ret;
        status.isEnabled_0_18 = 0;
        arg0->status_0        = status;

        result = (u8)result;
        ret    = result;
    }

    return ret;
}

s32 func_8009E310(s_KPadWork* arg0, s_KPad_Channel* arg1, s32 arg2) // 0x8009E310
{
    s_KPad_ActuatorInfo tmp;
    s32                 ret;

    ret = arg0 != NULL;
    if (ret == 0)
    {
        return ret;
    }

    ret = arg0->status_0.isInit_0_16;
    if (ret != 0)
    {
        if (arg1 == NULL)
        {
            arg2 = 0;
        }

        arg0->channels_C               = arg1;
        arg0->channelInfo_8.capacity_3 = arg2;

        while (arg2 > 0)
        {
            tmp.bits_0_0        = 0;
            tmp.bits_0_8        = 0;
            tmp.bits_0_9        = 0;
            tmp.dataOffset_0_16 = 0;
            tmp.bits_0_19       = 0;
            tmp.dataSize_0_24   = 0;
            tmp.bits_0_27       = 0;
            arg2--;
            arg1->info_0     = tmp;
            arg1->strength_4 = 0;
            arg1++;
        }
    }

    return ret;
}

bool func_8009E3B0(s_KPadWork* arg0, s32 padState, s32 padInfoCurId, s32 padInfoCurExId) // 0x8009E3B0
{
    s_KPad_Status tmp;

    tmp = arg0->status_0;

    if (padState == PadStateDiscon || padState == PadStateFindPad)
    {
        if (tmp.deviceType_0_24 != 0)
        {
            tmp.deviceType_0_24  = 0;
            tmp.actCount_0_19    = 0;
            tmp.isActSet_0_23    = 0;
            tmp.isAlignDone_0_22 = 0;

            if (padState == PadStateDiscon)
            {
                tmp.isEnabled_0_18 = 0;
            }

            arg0->actuatorData_4        = 0;
            arg0->channelInfo_8.field_0 = 0;
            arg0->channelInfo_8.count_2 = 0;
            arg0->status_0              = tmp;
        }

        return true;
    }

    if (tmp.deviceType_0_24 == 0)
    {
        return false;
    }

    return tmp.deviceType_0_24 != 3;
}

bool func_8009E438(s_KPadWork* arg0, s32 padState, s32 padInfoCurId, s32 padInfoCurExId) // 0x8009E438
{
    s_KPad_Status tmp;
    bool          isChanged;

    tmp = arg0->status_0;

    // "Check for controller connection with controllers other than DUAL SHOCK (Complete the acquisition of controller information)".
    if (padState == PadStateFindCTP1)
    {
        // TODO: 16Button is just standard controller?
        if (padInfoCurId == PadTerminalType_16Button |
            padInfoCurId == PadTerminalType_AnalogJoystick |
            padInfoCurId == PadTerminalType_AnalogController) // `|` Dev mistake?
        {
            isChanged           = tmp.deviceType_0_24 != 3;
            tmp.deviceType_0_24 = 3;
        }
        else
        {
            isChanged           = tmp.deviceType_0_24 != 4;
            tmp.deviceType_0_24 = 4;
        }
    }
    else
    {
        isChanged           = tmp.deviceType_0_24 != 0;
        tmp.deviceType_0_24 = 0;
    }

    if (isChanged)
    {
        arg0->actuatorData_4        = 0;
        arg0->channelInfo_8.field_0 = 0;
        arg0->channelInfo_8.count_2 = 0;
        tmp.actCount_0_19           = 0;
        tmp.isActSet_0_23           = 0;
        tmp.isAlignDone_0_22        = 0;
        arg0->status_0              = tmp;
    }

    return true;
}

s_KPad_Handler* func_8009E4F8(void) // 0x8009E4F8
{
    D_800B13EC.next_0 = &D_800B13FC;
    D_800B13FC.next_0 = &D_800B140C;
    D_800B140C.next_0 = NULL;

    return &D_800B13EC;
}

s_KPad_Handler* func_8009E520(s_KPad_Handler* node, s32 key) // 0x8009E520
{
    for (; node; node = node->next_0)
    {
        if (node->deviceType_4 == key)
        {
            return node;
        }
    }

    return NULL;
}

s32 func_8009E550(s_KPadWork* arg0, s_KPad_Handler* node) // 0x8009E550
{
    s32 padState;
    s32 padInfoCurId;
    s32 padInfoCurExId;
    u8  padPort;

    padPort        = arg0->status_0.port_0_0;
    padState       = PadGetState(padPort);
    padInfoCurId   = PadInfoMode(padPort, InfoModeCurID, 0);
    padInfoCurExId = PadInfoMode(padPort, InfoModeCurExID, 0);

    while (node)
    {
        if (node->func_C != NULL && node->func_C(arg0, padState, padInfoCurId, padInfoCurExId) == 1)
        {
            break;
        }

        node = node->next_0;
    }

    return padState;
}

bool func_8009E61C(s_KPadWork* arg0, s32 state, s_KPad_Handler* head) // 0x8009E61C
{
    s_KPad_Status status;
    u8*           pattern;
    u8*           act;
    s32           length;

    status = arg0->status_0;

    if (!status.isActSet_0_23)
    {
        pattern = &arg0->actuatorData_4;
        if (status.isEnabled_0_18 && !status.isPaused_0_17)
        {
            length = status.actCount_0_19;
        }
        else
        {
            length = 0;
        }
        status.isActSet_0_23 = 1;
        PadSetAct(status.port_0_0, pattern, length);
    }

    if (!status.isAlignDone_0_22)
    {
        head = func_8009E520(head, status.deviceType_0_24);
        act  = (head == NULL) ? NULL : head->alignData_8;
        if (act == NULL)
        {
            status.isAlignDone_0_22 = true;
        }
        else if (state == 6)
        {
            status.isAlignDone_0_22 = PadSetActAlign(status.port_0_0, act);
        }
    }

    arg0->status_0 = status;

    return status.isAlignDone_0_22;
}

bool func_8009E718(s_KPadWork* arg0) // 0x8009E718
{
    s_KPad_Status   status;
    u32             packedVal;
    u32             scale;
    s32             outLen;
    s32             outIdx;
    s32             i;
    u64             tmp;
    u8              inLen;
    s_KPad_Channel* in;
    u8*             out;

    status = arg0->status_0;
    if (!(status.isEnabled_0_18 && !status.isPaused_0_17))
    {
        return false;
    }

    // 0-128, but seems to only ever be set to 128.
    scale = status.strength_0_8;

    in  = arg0->channels_C;
    out = &arg0->actuatorData_4;
    for (i = (u8)arg0->channelInfo_8.count_2; i != 0; i--)
    {
        // Contains up to 4 actuator data bytes packed into a `u32`, even though there are only two actuators max.
        packedVal = in->strength_4;
        outLen    = in->info_0.dataSize_0_24;

        // Scale original actuator values by `[0.0f, 1.0f]` (`[0, 128]`). However, scale seems to only ever be 1.0f, so this is useless?
        tmp = ((u64)packedVal * scale) >> 7;
        if (tmp > UINT_MAX)
        {
            // If overflowed, max out every actuator.
            packedVal = UINT_MAX;
        }
        else
        {
            packedVal = tmp;
        }

        outIdx = in->info_0.dataOffset_0_16;

        // Ensure there's data for at least 1 actuator.
        if (outLen == 0)
        {
            outLen = 1;
            if (packedVal != 0)
            {
                // If any actuator values were not zero, enable at least the first one.
                // The other bytes will be ignored because outLen = 1.
                // Note that it's actuator 0 in a dualshock/dual analog that only takes 0 or 1,
                // but outIdx could be non-zero, though it's unclear if it ever is.
                packedVal = 0x01FFFFFF;
            }
        }

        // Change outLen bytes of actuator data starting with byte outIdx.
        while (outLen != 0)
        {
            // Get high byte and store it in actuator data.
            out[outIdx] = packedVal >> 24;
            outLen--;
            outIdx++;

            // Shift next byte to high byte.
            packedVal <<= 8;
        }

        in++;
    }

    return true;
}

bool func_8009E7D8(s_KPad_Handler* node) // 0x8009E7D8
{
    s_KPad_Handler* curNode;

    for (curNode = node; curNode; curNode = curNode->next_0)
    {
        if (curNode == &D_800B141C)
        {
            return false;
        }
    }

    curNode           = node->next_0;
    node->next_0      = &D_800B141C;
    D_800B141C.next_0 = curNode;

    return true;
}

bool func_8009E82C(s_KPadWork* work, s32 padState, s32 padInfoCurId, s32 padInfoCurExId)
{
    s32                 actCount;
    s_KPad_Channel*     cur;
    s_KPad_ActuatorInfo tmp;
    s32                 i;
    s32                 count;
    s_KPad_Status       status;
    u8                  unused[24];

    if (padState == PadStateFindCTP1 && ((0xB0u >> padInfoCurId) & 0x1))
    {
        work->actuatorData_4        = 0x40;
        work->channelInfo_8.field_0 = 0;
        count                       = work->channelInfo_8.capacity_3;

        status                  = work->status_0;
        cur                     = work->channels_C;
        status.deviceType_0_24  = 2;
        status.isActSet_0_23    = 0;
        status.isAlignDone_0_22 = 0;
        actCount                = 0;
        i                       = 1;

        if (count < 2)
        {
            i = count;
        }
        if (i > 0)
        {
            tmp.bits_0_0        = 1;
            tmp.bits_0_8        = 0;
            tmp.bits_0_9        = 10;
            tmp.dataOffset_0_16 = 1;
            tmp.dataSize_0_24   = 0;
            tmp.bits_0_19       = 1;
            tmp.bits_0_27       = 2;
            cur->info_0         = tmp;
            actCount            = 2;
            i                   = 1;
        }

        work->channelInfo_8.count_2 = i;
        status.actCount_0_19        = actCount;
        work->status_0              = status;
        tmp                         = (s_KPad_ActuatorInfo){ 0 };
        cur++;

        while (i < count)
        {
            cur->info_0 = tmp;
            cur++;
            i++;
        };

        return true;
    }

    return false;
}

bool func_8009E97C(s_KPad_Handler* node) // 0x8009E97C
{
    s_KPad_Handler* curNode;

    for (curNode = node; curNode; curNode = curNode->next_0)
    {
        if (curNode == &D_800B142C)
        {
            return false;
        }
    }

    curNode           = node->next_0;
    node->next_0      = &D_800B142C;
    D_800B142C.next_0 = curNode;

    return true;
}

bool func_8009E9D0(s_KPadWork* work, s32 padState, s_KPad_Channel* arg2, s32 arg3)
{
    s_KPad_Status       status;
    s_KPad_ActuatorInfo tmp;
    s32                 actCount;
    s32                 unk_B_0;
    s32                 i;
    u32                 mask = (1 << padState);
    u8                  unused[24];

    status = work->status_0;

    if (mask & ((1 << PadStateReqInfo) | (1 << PadStateExecCmd)))
    {
        return status.deviceType_0_24 == 1;
    }
    if (padState != PadStateStable)
    {
        return false;
    }

    if (((0x90u >> arg3) & 0x1))
    {
        status.deviceType_0_24  = 1;
        status.isActSet_0_23    = 0;
        status.isAlignDone_0_22 = 0;

        arg2                        = work->channels_C;
        unk_B_0                     = work->channelInfo_8.capacity_3;
        work->actuatorData_4        = 0;
        work->channelInfo_8.field_0 = 0;

        actCount = 0;
        i        = 2;

        if (unk_B_0 < 3)
        {
            i = unk_B_0;
        }

        if (i > 0)
        {
            tmp.bits_0_0        = 2;
            tmp.bits_0_8        = 0;
            tmp.bits_0_9        = 10;
            tmp.dataOffset_0_16 = 0;
            tmp.dataSize_0_24   = 0;
            tmp.bits_0_19       = 1;
            tmp.bits_0_27       = 2;
            arg2->info_0        = tmp;
            actCount            = 1;
        }

        if (i >= 2)
        {
            tmp.bits_0_0        = 3;
            tmp.bits_0_8        = 0;
            tmp.bits_0_9        = 20;
            tmp.dataOffset_0_16 = 1;
            tmp.dataSize_0_24   = 1;
            tmp.bits_0_19       = 1;
            tmp.bits_0_27       = 1;
            arg2++;
            arg2->info_0 = tmp;

            actCount = 2;
            i        = 2;
        }

        work->channelInfo_8.count_2 = i;
        status.actCount_0_19        = actCount;
        work->status_0              = status;
        tmp                         = (s_KPad_ActuatorInfo){ 0 };
        arg2++;

        while (i < unk_B_0)
        {
            arg2->info_0 = tmp;
            arg2++;
            i++;
        };

        return true;
    }

    return false;
}

bool func_8009EBB8(s_KPadWork* list, s_KPad_Effect* node, s32 count) // 0x8009EBB8
{
    s_KPad_Effect* cur;
    s_KPad_Effect* head;

    if (count >= 128)
    {
        return false;
    }

    if (count <= 0 || list == NULL)
    {
        return false;
    }

    if (node == NULL)
    {
        return false;
    }

    head = NULL;
    cur  = node;

    for (; count > 0; count--)
    {
        cur->links_0.next_0 = head;
        cur->links_0.prev_4 = NULL;
        head                = cur++;
    }

    list->freeEffects_10.next_0 = head;
    list->freeEffects_10.prev_4 = NULL;

    list->effects_18.next_0 = KPAD_EFFECTS_HEAD(list);
    list->effects_18.prev_4 = KPAD_EFFECTS_HEAD(list);

    return true;
}

bool func_8009EC1C(s_KPadWork* list, s_KPad_Effect* node) // 0x8009EC1C
{
    s_KPad_Effect* next;
    s_KPad_Effect* prev;

    next = node->links_0.next_0;
    prev = node->links_0.prev_4;

    // @bug `node == NULL` check happens after already trying to read from `node`
    if (node == NULL)
    {
        return false;
    }

    if (node == KPAD_EFFECTS_HEAD(list))
    {
        return false;
    }

    if (node->links_0.prev_4 == NULL)
    {
        return false;
    }

    // Remove node from doubly-linked list by making its neighbors skip over it.
    prev->links_0.next_0 = next;
    next->links_0.prev_4 = prev;

    // Add node to front of the free list.
    next                        = list->freeEffects_10.next_0;
    list->freeEffects_10.next_0 = node;
    node->links_0.next_0        = next;

    return true;
}

bool func_8009EC64(s_KPadWork* work, s16 val) // 0x8009EC64
{
    s32            val32;
    s_KPad_Effect* prev;
    s_KPad_Effect* head;
    s_KPad_Effect* node;
    s_KPad_Effect* cur;
    bool           unsorted;

    head  = KPAD_EFFECTS_HEAD(work);
    node  = work->freeEffects_10.next_0;
    val32 = val;
    prev  = work->effects_18.prev_4;

    unsorted = ((!node) & (prev == head) & (val32 >= prev->priority_8)) != 0;
    if (!unsorted)
    {
        return unsorted;
    }

    // Remove `prev`.
    cur                  = prev->links_0.prev_4;
    cur->links_0.next_0  = head;
    head->links_0.prev_4 = cur;

    // Insert in front of `node`.
    work->freeEffects_10.next_0 = prev;
    prev->links_0.next_0        = node;

    return true;
}

s_KPad_Effect* func_8009ECCC(s_KPadWork* arg0, s32 key) // 0x8009ECCC
{
    s_KPad_Effect* head;
    s_KPad_Effect* node;
    s_KPad_Effect* next;
    s_KPad_Effect* prev;
    s_KPad_Effect* tmp;
    s_KPad_Effect* cur;
    s32            midpoint;

    node = arg0->freeEffects_10.next_0;
    head = KPAD_EFFECTS_HEAD(arg0);

    if (node == NULL)
    {
        return NULL;
    }

    cur                         = node->links_0.next_0;
    next                        = head->links_0.next_0;
    arg0->freeEffects_10.next_0 = cur;

    tmp  = arg0->effects_18.prev_4;
    prev = tmp;

    midpoint = (next->priority_8 + prev->priority_8) >> 1;
    if (midpoint <= key)
    {
        prev = head;
        cur  = next;

        while (cur != head && key < cur->priority_8)
        {
            prev = cur;
            cur  = prev->links_0.next_0;
        }
    }
    else
    {
        cur = head;
    }

    cur->links_0.prev_4  = node;
    prev->links_0.next_0 = node;
    node->links_0.next_0 = cur;

    tmp                  = prev;
    node->links_0.prev_4 = tmp;

    node->priority_8 = key;

    return node;
}

s_KPad_Effect* func_8009ED74(s_KPadWork* list) // 0x8009ED74
{
    return KPAD_EFFECTS_HEAD(list);
}

s_KPad_Effect* func_8009ED7C(s_KPad_Effect* node) // 0x8009ED7C
{
    if (node != NULL)
    {
        return node->links_0.next_0;
    }

    return NULL;
}

s_KPad_Effect* func_8009ED90(s_KPad_Effect* node) // 0x8009ED90
{
    if (node != NULL)
    {
        return node->links_0.prev_4;
    }

    return NULL;
}
