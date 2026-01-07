#include "common.h"
#include "lib_unk.h"

#include <psyq/libgte.h>
#include <psyq/libpad.h>

#include "bodyprog/math/math.h"

// TODO: Could be array?
s_SysWork_2510 D_800B13EC = {
    .next_0  = NULL,
    .key_4   = 0,
    .pad_5   = { 0, 0, 0 },
    .field_8 = 0,
    .func_C  = func_8009E3B0, // Handles `PadStateDiscon` / `PadStateFindPad`
};

s_SysWork_2510 D_800B13FC = {
    .next_0  = NULL,
    .key_4   = 3,
    .pad_5   = { 0, 0, 0 },
    .field_8 = 0,
    .func_C  = NULL,
};

s_SysWork_2510 D_800B140C = {
    .next_0  = NULL,
    .key_4   = 4,
    .pad_5   = { 0, 0, 0 },
    .field_8 = 0,
    .func_C  = func_8009E438, // Handles `PadStateFindCTP1`
};

s_SysWork_2510 D_800B141C = {
    .next_0  = NULL,
    .key_4   = 2,
    .pad_5   = { 0, 1, 0 },
    .field_8 = 0,
    .func_C  = func_8009E82C,
};

s_SysWork_2510 D_800B142C = {
    .next_0  = NULL,
    .key_4   = 1,
    .pad_5   = { 1, 2, 0 },
    .field_8 = 0x800B2610, // TODO: Pointer to data? Pretty far from this files .data section.
    .func_C  = func_8009E9D0,
};

INCLUDE_ASM("bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E198);

s32 func_8009E230(s_SysWork_2514* arg0) // 0x8009E230
{
    u32 tmp;
    s32 ret;

    tmp = *(u32*)arg0;

    ret = arg0->field_0.field_0_17;
    if (ret != 0)
    {
        // @hack bitfield struct assignments don't match here?
        u32 mask    = ~(1 << 23);
        tmp        &= mask;
        mask        = ~(1 << 17);
        tmp        &= mask;
        *(u32*)arg0 = tmp;
    }

    return ret;
}

s32 func_8009E268(s_SysWork_2514* arg0) // 0x8009E268
{
    u32 tmp;
    s32 ret;

    tmp = *(u32*)arg0;

    ret = arg0->field_0.field_0_17 ^ 1;
    if (ret != 0)
    {
        // @hack bitfield struct assignments don't match here?
        u32 mask    = ~(1 << 23);
        tmp        &= mask;
        mask        = 1 << 17;
        tmp        |= mask;
        *(u32*)arg0 = tmp;
    }

    return ret;
}

s32 func_8009E2A0(s_SysWork_2514* arg0)
{
    u32 tmp = *(u32*)arg0;
    s32 ret = arg0->field_0.field_0_18 ^ 1;
    if (ret != 0)
    {
        // @hack bitfield struct assignments don't match here?
        u32 mask    = ~(1 << 23);
        tmp        &= mask;
        mask        = 1 << 18;
        tmp        |= mask;
        *(u32*)arg0 = tmp;
    }

    return ret;
}

s32 func_8009E2D8(s_SysWork_2514* arg0) // 0x8009E2D8
{
    u32 tmp;
    s32 ret;

    tmp = *(u32*)arg0;

    ret = arg0->field_0.field_0_18;
    if (ret != 0)
    {
        // @hack bitfield struct assignments don't match here?
        u32 mask    = ~(1 << 23);
        tmp        &= mask;
        mask        = ~(1 << 18);
        tmp        &= mask;
        *(u32*)arg0 = tmp;
    }

    return ret;
}

s32 func_8009E310(s_SysWork_2514* arg0, s_SysWork_2514_C* arg1, s32 arg2) // 0x8009E310
{
    s_SysWork_2514_C_0 tmp;
    s32                ret;

    ret = arg0 != NULL;
    if (ret == 0)
    {
        return ret;
    }

    ret = arg0->field_0.field_0_16;
    if (ret != 0)
    {
        if (arg1 == NULL)
        {
            arg2 = 0;
        }

        arg0->field_C  = arg1;
        arg0->unk_B[0] = arg2;

        while (arg2 > 0)
        {
            tmp.bits_0_0  = 0;
            tmp.bits_0_8  = 0;
            tmp.bits_0_9  = 0;
            tmp.bits_0_16 = 0;
            tmp.bits_0_19 = 0;
            tmp.bits_0_24 = 0;
            tmp.bits_0_27 = 0;
            arg2--;
            arg1->flags_0 = tmp;
            arg1->data_4  = 0;
            arg1++;
        }
    }

    return ret;
}

bool func_8009E3B0(s_SysWork_2514* arg0, s32 padState, s32 padInfoCurId, s32 padInfoCurExId) // 0x8009E3B0
{
    s_SysWork_2514_0 tmp;

    tmp = arg0->field_0;

    if (padState == PadStateDiscon || padState == PadStateFindPad)
    {
        if (tmp.field_0_24 != 0)
        {
            tmp.field_0_24 = 0;
            tmp.field_0_19 = 0;
            tmp.field_0_23 = 0;
            tmp.field_0_22 = 0;

            if (padState == PadStateDiscon)
            {
                tmp.field_0_18 = 0;
            }

            arg0->actuatorData_4 = 0;
            arg0->field_8 = 0;
            arg0->field_A = 0;
            arg0->field_0 = tmp;
        }

        return true;
    }

    if (tmp.field_0_24 == 0)
    {
        return false;
    }

    return tmp.field_0_24 != 3;
}

bool func_8009E438(s_SysWork_2514* arg0, s32 padState, s32 padInfoCurId, s32 padInfoCurExId) // 0x8009E438
{
    s_SysWork_2514_0 tmp;
    bool             isChanged;

    tmp = arg0->field_0;

    // "Check for controller connection with controllers other than DUAL SHOCK (Complete the acquisition of controller information)".
    if (padState == PadStateFindCTP1)
    {
        // TODO: 16Button is just standard controller?
        if (padInfoCurId == PadTerminalType_16Button |
            padInfoCurId == PadTerminalType_AnalogJoystick |
            padInfoCurId == PadTerminalType_AnalogController) // `|` Dev mistake?
        {
            isChanged      = tmp.field_0_24 != 3;
            tmp.field_0_24 = 3;
        }
        else
        {
            isChanged      = tmp.field_0_24 != 4;
            tmp.field_0_24 = 4;
        }
    }
    else
    {
        isChanged      = tmp.field_0_24 != 0;
        tmp.field_0_24 = 0;
    }

    if (isChanged)
    {
        arg0->actuatorData_4  = 0;
        arg0->field_8  = 0;
        arg0->field_A  = 0;
        tmp.field_0_19 = 0;
        tmp.field_0_23 = 0;
        tmp.field_0_22 = 0;
        arg0->field_0  = tmp;
    }

    return true;
}

s_SysWork_2510* func_8009E4F8(void) // 0x8009E4F8
{
    D_800B13EC.next_0 = &D_800B13FC;
    D_800B13FC.next_0 = &D_800B140C;
    D_800B140C.next_0 = NULL;

    return &D_800B13EC;
}

s_SysWork_2510* func_8009E520(s_SysWork_2510* node, s32 key) // 0x8009E520
{
    for (; node; node = node->next_0)
    {
        if (node->key_4 == key)
        {
            return node;
        }
    }

    return NULL;
}

s32 func_8009E550(s_SysWork_2514* arg0, s_SysWork_2510* node) // 0x8009E550
{
    s32 padState;
    s32 padInfoCurId;
    s32 padInfoCurExId;
    u8  padPort;

    padPort        = arg0->field_0.padPort_0_0;
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

bool func_8009E61C(s_SysWork_2514* arg0, s32 state, s_SysWork_2510* head) // 0x8009E61C
{
    s_SysWork_2514_0 status;
    s_SysWork_2510*  node;
    u8*              pattern;
    u8*              act;
    s32              length;

    status = arg0->field_0;

    if (!status.field_0_23)
    {
        pattern = &arg0->actuatorData_4;
        if (status.field_0_18 && !status.field_0_17)
        {
            length = status.field_0_19;
        }
        else
        {
            length = 0;
        }
        status.field_0_23 = 1;
        PadSetAct(status.padPort_0_0, pattern, length);
    }

    if (!status.field_0_22)
    {
        node = func_8009E520(head, status.field_0_24);
        act  = (node == NULL) ? NULL : node->field_8;
        if (act == NULL)
        {
            status.field_0_22 = true;
        }
        else
        {
            if (state == 6)
            {
                status.field_0_22 = PadSetActAlign(status.padPort_0_0, act);
            }
            // @hack keep node alive
            act = (node == NULL) ? NULL : node->field_8;
        }
    }

    arg0->field_0 = status;

    return status.field_0_22;
}

bool func_8009E718(s_SysWork_2514* arg0) // 0x8009E718
{
    s_SysWork_2514_0  status;
    u32               packedVal;
    u32               scale;
    s32               outLen;
    s32               outIdx;
    s32               i;
    u64               tmp;
    u8                inLen;
    s_SysWork_2514_C* in;
    u8*               out;

    status = arg0->field_0;
    if (!(status.field_0_18 && !status.field_0_17))
    {
        return false;
    }

    // 0-128, but seems to only ever be set to 128.
    scale = status.field_0_8;

    in  = arg0->field_C;
    out = &arg0->actuatorData_4;
    for (i = (u8)arg0->field_A; i != 0; i--)
    {
        // Contains up to 4 actuator data bytes packed into a `u32`, even though there are only two actuators max.
        packedVal = in->data_4;
        outLen    = in->flags_0.bits_0_24;

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

        outIdx = in->flags_0.bits_0_16;

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

bool func_8009E7D8(s_SysWork_2510* node) // 0x8009E7D8
{
    s_SysWork_2510* curNode;

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

bool func_8009E82C(s_SysWork_2514* work, s32 padState, s32 padInfoCurId, s32 padInfoCurExId)
{
    s32                 field_0_19;
    s_SysWork_2514_C_0* cur;
    s_SysWork_2514_C_0  tmp;
    s32                 i;
    s32                 count;
    s_SysWork_2514_0    status;
    u8                  stack[24];

    if (padState == PadStateFindCTP1 && ((0xB0u >> padInfoCurId) & 0x1))
    {
        work->actuatorData_4 = 0x40;
        work->field_8        = 0;
        count                = work->unk_B[0];

        status            = work->field_0;
        cur               = (s_SysWork_2514_C_0*)work->field_C;
        status.field_0_24 = 2;
        status.field_0_23 = 0;
        status.field_0_22 = 0;
        field_0_19        = 0;
        i                 = 1;

        if (count < 2)
        {
            i = count;
        }
        if (i > 0)
        {
            tmp.bits_0_0  = 1;
            tmp.bits_0_8  = 0;
            tmp.bits_0_9  = 10;
            tmp.bits_0_16 = 1;
            tmp.bits_0_24 = 0;
            tmp.bits_0_19 = 1;
            tmp.bits_0_27 = 2;
            *cur          = tmp;
            field_0_19    = 2;
            i             = 1;
        }

        work->field_A     = i;
        status.field_0_19 = field_0_19;
        work->field_0     = status;
        tmp               = (s_SysWork_2514_C_0){ 0 };
        cur              += 2;

        while (i < count)
        {
            *cur = tmp;
            cur += 2;
            i++;
        };

        return true;
    }

    return false;
}

bool func_8009E97C(s_SysWork_2510* node) // 0x8009E97C
{
    s_SysWork_2510* curNode;

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

bool func_8009E9D0(s_SysWork_2514* work, s32 padState, s_SysWork_2514_C* arg2, s32 arg3)
{
    s_SysWork_2514_0   status;
    u_SysWork_2514_C_0 tmp;
    s32                field_0_19;
    s32                unk_B_0;
    s32                i;
    u32                mask = (1 << padState);
    u8                 stack[24];

    status = work->field_0;

    if (mask & ((1 << PadStateReqInfo) | (1 << PadStateExecCmd)))
    {
        return status.field_0_24 == 1;
    }
    if (padState != PadStateStable)
    {
        return false;
    }

    if (((0x90u >> arg3) & 0x1))
    {
        status.field_0_24 = 1;
        status.field_0_23 = 0;
        status.field_0_22 = 0;

        arg2          = work->field_C;
        unk_B_0       = work->unk_B[0];
        work->actuatorData_4 = 0;
        work->field_8 = 0;

        field_0_19 = 0;
        i          = 2;

        if (unk_B_0 < 3)
        {
            i = unk_B_0;
        }

        if (i > 0)
        {
            tmp.flags.bits_0_0  = 2;
            tmp.flags.bits_0_8  = 0;
            tmp.flags.bits_0_9  = 10;
            tmp.flags.bits_0_16 = 0;
            tmp.flags.bits_0_24 = 0;
            tmp.flags.bits_0_19 = 1;
            tmp.flags.bits_0_27 = 2;
            arg2->flags_0       = tmp.flags;
            field_0_19          = 1;
        }

        if (i >= 2)
        {
            tmp.flags.bits_0_0  = 3;
            tmp.flags.bits_0_8  = 0;
            tmp.flags.bits_0_9  = 20;
            tmp.flags.bits_0_16 = 1;
            tmp.flags.bits_0_24 = 1;
            tmp.flags.bits_0_19 = 1;
            tmp.flags.bits_0_27 = 1;
            arg2++;
            arg2->flags_0 = tmp.flags;

            field_0_19 = 2;
            i          = 2;
        }

        work->field_A     = i;
        status.field_0_19 = field_0_19;
        work->field_0     = status;
        tmp.value         = 0;
        arg2++;

        while (i < unk_B_0)
        {
            *(u32*)arg2 = tmp.value;
            arg2++;
            i++;
        };

        return true;
    }

    return false;
}

bool func_8009EBB8(s_SysWork_2514* list, s_SysWork_2514_18* node, s32 count) // 0x8009EBB8
{
    s_SysWork_2514_18* cur;
    s_SysWork_2514_18* head;

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
        cur->next_0 = head;
        cur->prev_4 = NULL;
        head        = cur++;
    }

    list->field_10 = head;
    list->unk_14   = NULL;

    list->head_18.next_0 = &list->head_18;
    list->head_18.prev_4 = &list->head_18;

    return true;
}

bool func_8009EC1C(s_SysWork_2514* list, s_SysWork_2514_18* node) // 0x8009EC1C
{
    s_SysWork_2514_18* next;
    s_SysWork_2514_18* prev;

    next = node->next_0;
    prev = node->prev_4;

    // @bug `node == NULL` check happens after already trying to read from `node`
    if (node == NULL)
    {
        return false;
    }

    if (node == &list->head_18)
    {
        return false;
    }

    if (node->prev_4 == NULL)
    {
        return false;
    }

    // Remove node from doubly-linked list by making its neighbors skip over it.
    prev->next_0 = next;
    next->prev_4 = prev;

    // Add node to front of secondary list in `field_10` (free list?).
    next           = list->field_10;
    list->field_10 = node;
    node->next_0   = next;

    return true;
}

bool func_8009EC64(s_SysWork_2514* work, s16 val) // 0x8009EC64
{
    s_SysWork_2514*     list = work;
    s32                 val32;
    s_SysWork_2514_18*  prev;
    s_SysWork_2514_18*  head;
    s_SysWork_2514_18** prevAddress;
    s32*                prevUnk8;
    s_SysWork_2514_18*  node;
    s_SysWork_2514_18*  cur;
    bool                unsorted;

    head    = &list->head_18;
    node    = list->field_10;
    val32 = val;

    prevAddress = &head->prev_4;
    prev        = *prevAddress;
    prevUnk8    = &prev->key_8.value;

    unsorted = ((!node) & (prev == head) & (val32 >= prev->key_8.value)) != 0;
    if (!unsorted)
    {
        return unsorted;
    }

    // Remove `prev`.
    cur          = prev->prev_4;
    cur->next_0  = head;
    head->prev_4 = cur;

    // Insert in front of `node`.
    list->field_10 = prev;
    prev->next_0   = node;

    return true;
}

s_SysWork_2514_18* func_8009ECCC(s_SysWork_2514* arg0, s32 key) // 0x8009ECCC
{
    s_SysWork_2514_18* head;
    s_SysWork_2514_18* node;
    s_SysWork_2514_18* next;
    s_SysWork_2514_18* prev;
    s_SysWork_2514_18* tmp;
    s_SysWork_2514_18* cur;
    s32                midpoint;

    node = arg0->field_10;
    head = &arg0->head_18;

    if (node == NULL)
    {
        return NULL;
    }

    cur            = node->next_0;
    next           = head->next_0;
    arg0->field_10 = cur;

    tmp  = arg0->head_18.prev_4;
    prev = tmp;

    midpoint = (next->key_8.value + prev->key_8.value) >> 1;
    if (midpoint <= key)
    {
        prev = head;
        cur  = next;

        while (cur != head && key < cur->key_8.value)
        {
            prev = cur;
            cur  = prev->next_0;
        }
    }
    else
    {
        cur = head;
    }

    cur->prev_4  = node;
    prev->next_0 = node;
    node->next_0 = cur;

    tmp          = prev;
    node->prev_4 = tmp;

    node->key_8.value = key;

    return node;
}

s_SysWork_2514_18* func_8009ED74(s_SysWork_2514* list) // 0x8009ED74
{
    return &list->head_18;
}

s_SysWork_2514_18* func_8009ED7C(s_SysWork_2514_18* node) // 0x8009ED7C
{
    if (node != NULL)
    {
        return node->next_0;
    }

    return NULL;
}

s_SysWork_2514_18* func_8009ED90(s_SysWork_2514_18* node) // 0x8009ED90
{
    if (node != NULL)
    {
        return node->prev_4;
    }

    return NULL;
}
