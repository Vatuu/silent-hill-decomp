#include "common.h"
#include <libpad.h>
#include "lib_unk.h"

// TODO: Could be array?
s_SysWork_2510 D_800B13EC = {
    .next_0  = NULL,
    .key_4   = 0,
    .pad_5   = { 0, 0, 0 },
    .field_8 = 0,
    .func_C  = func_8009E3B0,
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
    .func_C  = func_8009E438,
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E198);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E230);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E268);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E2A0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E2D8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E310);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E3B0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E438);

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

s32 func_8009E550(s_SysWork_2514* arg0, s_SysWork_2510* arg1) // 0x8009E550
{
    s32 padState;
    s32 padInfoCurID;
    s32 padInfoCurExID;
    u8  padPort;

    padPort        = arg0->field_0;
    padState       = PadGetState(padPort);
    padInfoCurID   = PadInfoMode(padPort, InfoModeCurID, 0);
    padInfoCurExID = PadInfoMode(padPort, InfoModeCurExID, 0);

    while (arg1)
    {
        if (arg1->func_C != NULL && arg1->func_C(arg0, padState, padInfoCurID, padInfoCurExID) == 1)
        {
            break;
        }
        
        arg1 = arg1->next_0;
    }

    return padState;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E61C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E718);

bool func_8009E7D8(s_SysWork_2510* arg0) // 0x8009E7D8
{
    s_SysWork_2510* var_a1;

    for (var_a1 = arg0; var_a1; var_a1 = var_a1->next_0)
    {
        if (var_a1 == &D_800B141C)
        {
            return false;
        }
    }

    var_a1            = arg0->next_0;
    arg0->next_0      = &D_800B141C;
    D_800B141C.next_0 = var_a1;

    return true;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E82C);

bool func_8009E97C(s_SysWork_2510* arg0) // 0x8009E97C
{
    s_SysWork_2510* var_a1;

    for (var_a1 = arg0; var_a1; var_a1 = var_a1->next_0)
    {
        if (var_a1 == &D_800B142C)
        {
            return false;
        }
    }

    var_a1            = arg0->next_0;
    arg0->next_0      = &D_800B142C;
    D_800B142C.next_0 = var_a1;

    return true;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009E9D0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009EBB8);

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

    // Remove node from the doubly-linked list by making its neighbors skip over it.
    prev->next_0 = next;
    next->prev_4 = prev;

    // Add node to the front of the secondary list in `field_10` (free list?)
    next           = list->field_10;
    list->field_10 = node;
    node->next_0   = next;

    return true;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009EC64);

INCLUDE_ASM("asm/bodyprog/nonmatchings/lib_unk/lib_8009E198", func_8009ECCC);

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
