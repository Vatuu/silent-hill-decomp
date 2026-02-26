#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"

// ========================================
// VIBRATION HANDLING RELATED
// ========================================

void func_80089090(s32 arg0) // 0x80089090
{
    func_80089524(&g_SysWork.field_2514, arg0);
}

void func_800890B8(void) // 0x800890B8
{
    func_8009E198(&g_SysWork.field_2514, 0);
    func_8009E310(&g_SysWork.field_2514, &g_SysWork.field_2514.head_18.key_8, 2);
    func_8009EBB8(&g_SysWork.field_2514, g_SysWork.field_2514.head_18.unk_18, 16);

    g_SysWork.field_2510 = func_8009E4F8();

    func_8009E7D8(g_SysWork.field_2510);
    func_8009E97C(g_SysWork.field_2510);
}

s32 func_80089128(void) // 0x80089128
{
    s32              temp_s0;
    s32              var_s3;
    s32              var_s5;
    s32              var_s6;
    s_func_8009ECCC* temp_v0;
    s_func_8009ECCC* var_s0;
    s_func_8009ECCC* temp_s1;
    s_SysWork_2514*  var_s2;

    var_s2 = &g_SysWork.field_2514;

    temp_s0 = g_SysWork.field_2510;

    if (!var_s2->field_0.field_0_16)
    {
        func_800890B8();
    }

    if (g_GameWork.config_0.optVibrationEnabled_21)
    {
        func_8009E2A0(var_s2);
        var_s2->field_0.field_0_8 = 1 << 7;
    }
    else
    {
        func_8009E2D8(var_s2);
        var_s2->field_0.field_0_8 = 0;
    }

    if (PadChkVsync())
    {
        func_8009E61C(var_s2, func_8009E550(var_s2, temp_s0), temp_s0);
    }

    var_s5 = 0;

    var_s2->field_C[0].data_4 = 0;
    var_s2->field_C[1].data_4 = 0;

    temp_v0 = func_8009ED74(var_s2);
    var_s0  = func_8009ED7C(temp_v0);

    if (!var_s2->field_0.field_0_17)
    {
        var_s3 = g_VBlanks;
    }
    else
    {
        var_s3 = 0;
    }

    var_s6 = 0xFFFF;

    for (; var_s0 != temp_v0; var_s5++)
    {
        temp_s1 = func_8009ED7C(var_s0);

        if (!func_80089644(var_s2, var_s0, var_s6 & 0xFFFF, var_s3))
        {
            func_8009EC1C(var_s2, var_s0);
        }

        var_s0 = temp_s1;
    }

    func_8009E718(var_s2);

    return var_s5;
}

// Forward declare pointers used below.
extern const u32 D_8002AF04[];
extern const u32 D_8002AF08[];
extern const u32 D_8002AF20[];
extern const u32 D_8002AF24[];
extern const u32 D_8002AF28[];
extern const u32 D_8002AF2C[];
extern const u32 D_8002AF34[];
extern const u32 D_8002AF3C[];
extern const u32 D_8002AF48[];
extern const u32 D_8002AF54[];
extern const u32 D_8002AF5C[];
extern const u32 D_8002AF64[];
extern const u32 D_8002AF70[];

const s_8002AC04 D_8002AC04[] = {
    // 2nd field is used as index into `D_800AFD08` funcptr array.
    // Seems each function takes different kind of params in 5th/6th fields:
    // #0 5th field is some kind of index/counter.
    // #1 5th field is pointer to another `D_8002AC04` entry.
    // #2 5th field points to some data that comes after this array.
    // #3 5th field is always 0.
    // #4 5th field is index/counter.
    { NULL, { .func_8008973C_data = { 3, 2, 0, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 3, 3, 0, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 3, 1, 0, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 3, 0, 0, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 3, 4, 0, 0, 0 } } },
    { &D_8002AC04[22], { .func_8008973C_data = { 0, 0, 0, 5, 0 } } },
    { &D_8002AC04[25], { .func_8008973C_data = { 0, 32, 0, 6, 0 } } },
    { &D_8002AC04[26], { .func_8008973C_data = { 0, 32, 0, 7, 0 } } },
    { &D_8002AC04[27], { .func_8008973C_data = { 0, 32, 0, 8, 0 } } },
    { &D_8002AC04[23], { .func_8008973C_data = { 0, 32, 0, 9, 0 } } },
    { &D_8002AC04[24], { .func_8008973C_data = { 0, 32, 0, 10, 0 } } },
    { &D_8002AC04[5], { .func_8008973C_data = { 1, 0, 0, &D_8002AC04[6], 0 } } },
    { &D_8002AC04[31], { .func_8008973C_data = { 0, 32, 0, 12, 0 } } },
    { &D_8002AC04[34], { .func_8008973C_data = { 0, 32, 0, 12, 0 } } },
    { &D_8002AC04[37], { .func_8008973C_data = { 0, 32, 0, 12, 0 } } },
    { &D_8002AC04[40], { .func_8008973C_data = { 0, 32, 0, 12, 0 } } },
    { &D_8002AC04[43], { .func_8008973C_data = { 0, 32, 0, 12, 0 } } },
    { &D_8002AC04[46], { .func_8008973C_data = { 0, 32, 0, 12, 0 } } },
    { &D_8002AC04[28], { .func_8008973C_data = { 0, 32, 0, 18, 0 } } },
    { &D_8002AC04[29], { .func_8008973C_data = { 0, 32, 0, 19, 0 } } },
    { NULL, { .func_8008973C_data = { 4, 0, NO_VALUE, 20, -255 } } },
    { NULL, { .func_8008973C_data = { 4, 1, NO_VALUE, 21, -255 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF70, 0x2D, 9, 1, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF64, 0x180, 0x30, 1, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF5C, 0x90, 0x18, 1, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF54, 0x5A, 0xF, 1, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF48, 0x96, 0xF, 1, 1 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF3C, 0x60, 0xC, 1, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF3C, 0x60, 0xC, 1, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF34, 0x4B, 0xF, 1, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 0, NO_VALUE, &D_8002AF2C, 0x258, 0xF, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 0, NO_VALUE, &D_8002AF28, 0x1E0, 0xF, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 0, NO_VALUE, &D_8002AF24, 0x1A4, 0xF, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 0, NO_VALUE, &D_8002AF20, 0x168, 0xF, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 0, NO_VALUE, &D_8002AF20, 0x10E, 0xF, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { &D_8002AC04[47], { .func_80089DF0_data = { 2, 0, NO_VALUE, &D_8002AF08, 0xB40, 0xF, 0, 0 } } },
    { &D_8002AC04[47], { .func_80089DF0_data = { 2, 0, NO_VALUE, &D_8002AF04, 0x1E, 0xF, 0, 0 } } },
};

// TODO: Figure out what kind of data this is. The array above has some entries pointing to it, all of them using funcptr #2 (`func_80089DF0`).
// Not sure why they'd all be different sizes though.
const u32 D_8002AF04[] = { 0 };
const u32 D_8002AF08[] = { 0x8000184, 0x61000003, 0x81000000, 1, 0x181, 0x10000 };
const u32 D_8002AF20[] = { 0x184 };
const u32 D_8002AF24[] = { 0x308 };
const u32 D_8002AF28[] = { 0x610 };
const u32 D_8002AF2C[] = { 0xC010, 0 };
const u32 D_8002AF34[] = { 0x80008080, 0x80 };
const u32 D_8002AF3C[] = { 0xFFFFFF, 0xFFFFFF00, 0 };
const u32 D_8002AF48[] = { 0x468CA0A0, 0x1E28323C, 0xA14};
const u32 D_8002AF54[] = { 0xAFC8C8C8, 0x4B96};
const u32 D_8002AF5C[] = { 0x309060C0, 0xC048A8 };
const u32 D_8002AF64[] = { 0x143C2850, 0xA321E46, 0x50};
const u32 D_8002AF70[] = { 0xC4E0E0A8, 0x54A8, 0};

void func_800892A4(s32 idx) // 0x800892A4
{
    func_800895E4(&g_SysWork.field_2514, &D_8002AC04[idx], 0x80);
}

void func_800892DC(s32 idx, u8 arg1) // 0x800892DC
{
    func_800895E4(&g_SysWork.field_2514, &D_8002AC04[idx], arg1);
}

void func_80089314(s32 arg0) // 0x80089314
{
    s32 var0;
    s32 var1;

    var0        = 24;
    D_800AFD05 += g_VBlanks;

    if (arg0 != 0)
    {
        var0 = 6;
    }

    if ((s32)D_800AFD05 >= var0)
    {
        var0 = Rng_RandQ12();
        if (arg0 != 0)
        {
            var1 = ((var0 * 16) >> 12) + 20;
        }
        else
        {
            var1 = ((var0 * 20) >> 12) + 60;
        }

        D_800AFD04 = (D_800AFD04 + var1) & 0x7F;
    }

    func_800892DC(21, D_800AFD04 + 32);
}

void func_800893D0(q19_12 arg0) // 0x800893D0
{
    u32 var;

    if (arg0 > Q12(25.0f))
    {
        var = 200;
    }
    else if (arg0 < Q12(5.0f))
    {
        var = 100;
    }
    else
    {
        var = ((arg0 + Q12(15.0f)) / Q12(5.0f)) * 25;
    }

    func_800892DC(10, var);
}

void func_8008944C(void) // 0x8008944C
{
    func_800892DC(19, 0xA0);
}

void func_80089470(void) // 0x80089470
{
    func_800892DC(19, 0xA0);
}

void func_80089494(void) // 0x80089494
{
    func_800892DC(9, 0xA0);
}

void func_800894B8(s32 arg0) // 0x800894B8
{
    func_800892DC(9, arg0);
}

void func_800894DC(void) // 0x800894DC
{
    func_800892DC(9, 0xE0);
}

void func_80089500(void) // 0x80089500
{
    func_800892DC(9, 0xA0);
}

bool func_80089524(s_SysWork_2514* arg0, s32 padInfoMode) // 0x80089524
{
    s32             padState;
    bool            cond;
    u8              socket;
    s_SysWork_2514* temp;

    socket = arg0->field_0.padPort_0_0;
    PadInfoMode(socket, 2, 0);

    padState = PadGetState(socket);
    cond     = PadInfoMode(socket, 3, 0) == padInfoMode;
    if (!cond && padState == 6)
    {
        PadSetMainMode(socket, padInfoMode, 0);

        cond = PadSetMainMode(socket, 1, 0);

        temp            = &g_SysWork.field_2514;
        temp->field_0.field_0_23 = 0;
        temp->field_0.field_0_22 = 0;
    }

    return cond;
}

s32 func_800895E4(s_SysWork_2514* arg0, s_8002AC04* arg1, u8 arg2) // 0x800895E4
{
    u32 sp10;

    sp10 = arg2;

    if (arg1 == NULL)
    {
        return 0;
    }

    return D_800AFD08[arg1->field_4.funcIdx_4](arg0, 0, arg1, &sp10);
}

bool func_80089644(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s32 arg2, u32 arg3) // 0x80089644
{
    u32                var1;
    s_SysWork_2514_C*  ptr0;
    s_8002AC04*        ptr1;

    arg3             *= 5;
    arg1->field_18    = 0;
    arg1->field_14_31 = 0;
    while (true)
    {
        ptr1 = arg1->field_10;
        if (!ptr1)
        {
            break;
        }

        if (D_800AFD08[ptr1->field_4.funcIdx_4](arg0, arg1, ptr1, &arg3) == 0)
        {
            break;
        }
    }

    if (arg1->field_14_31 && (arg2 & arg1->field_1E))
    {
        var1 = arg1->field_18;
        ptr0 = &arg0->field_C[arg1->field_14_24];
        if (ptr0->data_4 < var1)
        {
            ptr0->data_4 = var1;
        }
    }

    return arg1->field_10 != NULL;
}

bool func_8008973C(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* ptr, u32* arg3)
{
    if (!arg0 || arg1)
    {
        return false;
    }

    if (ptr == NULL || ptr->field_4.func_8008973C_data.funcIdx_4 != 3)
    {
        return false;
    }

    switch (ptr->field_4.func_8008973C_data.field_5)
    {
        case 0:
            func_8009E2A0(arg0);
            break;

        case 1:
            func_8009E2D8(arg0);
            break;

        case 2:
            func_8009E268(arg0);
            break;

        case 3:
            func_8009E230(arg0);
            break;

        case 4:
            func_80089840(arg0);
            break;

        case 5:
            func_8008989C(arg0, ptr->field_4.func_8008973C_data.field_6, ptr->field_4.func_8008973C_data.field_C);
            break;

        case 6:
            func_8008992C(arg0, ptr->field_4.func_8008973C_data.field_6, ptr->field_4.func_8008973C_data.field_C);
            break;

        case 7:
            func_800899BC(arg0, ptr->field_4.func_8008973C_data.field_8);
            break;
    }

    return true;
}

void func_80089840(s_SysWork_2514* arg0) // 0x80089840
{
    s_SysWork_2514_18* next;
    s_SysWork_2514_18* curr;
    s_SysWork_2514_18* head;

    if (arg0 == NULL)
    {
        return;
    }

    curr = arg0->head_18.next_0;
    head = &arg0->head_18;

    while (curr != head)
    {
        next = curr->next_0;
        func_8009EC1C(arg0, curr);
        curr = next;
    }
}

void func_8008989C(s_SysWork_2514* arg0, u16 arg1, s32 (*arg2)(u16, s32)) // 0x8008989C
{
    s_SysWork_2514_18* next;
    s_SysWork_2514_18* head;
    s_SysWork_2514_18* curr;

    if (arg0 == NULL)
    {
        return;
    }

    curr = arg0->head_18.next_0;
    head = &arg0->head_18;

    while (curr != head)
    {
        next = curr->next_0;

        if (arg2(curr->field_1E, arg1) != 0)
        {
            func_8009EC1C(arg0, curr);
        }

        curr = next;
    }
}

void func_8008992C(s_SysWork_2514* arg0, u16 arg1, s32 (*arg2)(u16, s32)) // 0x8008992C
{
    s_SysWork_2514_18* next;
    s_SysWork_2514_18* head;
    s_SysWork_2514_18* curr;

    if (arg0 == NULL)
    {
        return;
    }

    curr = arg0->head_18.next_0;
    head = &arg0->head_18;

    while (curr != head)
    {
        next = curr->next_0;

        if (arg2(curr->field_1C, arg1) != 0)
        {
            func_8009EC1C(arg0, curr);
        }

        curr = next;
    }
}

void func_800899BC(s_SysWork_2514* arg0, s32 arg1) // 0x800899BC
{
    s_SysWork_2514_18* next;
    s_SysWork_2514_18* head;
    s_SysWork_2514_18* curr;

    if (arg0 == NULL)
    {
        return;
    }

    curr = arg0->head_18.next_0;
    head = &arg0->head_18;

    while (curr != head)
    {
        next = curr->next_0;

        if (curr->field_C == arg1)
        {
            func_8009EC1C(arg0, curr);
        }

        curr = next;
    }
}

bool func_80089A30(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* arg2, u32* arg3) // 0x80089A30
{
    s32                temp_s3;
    s_SysWork_2514_18* next;
    s_SysWork_2514_18* head;
    s_SysWork_2514_18* current;
    s_func_8009ECCC*   ptr;

    ptr = arg1;

    if (arg0 == NULL)
    {
        return false;
    }

    if (arg2 == NULL)
    {
        return false;
    }

    if (arg2->field_4.funcIdx_4 != 0)
    {
        return false;
    }

    temp_s3 = arg2->field_4.func_80089A30_data.field_8;

    if (arg2->field_4.func_80089A30_data.field_5_5 || arg2->field_4.func_80089A30_data.field_5_6)
    {
        current = arg0->head_18.next_0;
        head    = &arg0->head_18;

        if (arg2->field_4.func_80089A30_data.field_5_5)
        {
            while (current != head)
            {
                if (current->field_C == temp_s3)
                {
                    if (ptr != NULL)
                    {
                        ptr->field_10 = NULL;
                    }

                    return false;
                }

                current = current->next_0;
            }
        }
        else
        {
            while (current != head)
            {
                next = current->next_0;
                if ((ptr == NULL || current != ptr) && current->field_C == temp_s3)
                {
                    func_8009EC1C(arg0, current);
                }
                current = next;
            }
        }
    }

    if (ptr == NULL)
    {
        ptr = func_8009ECCC(arg0, arg2->field_4.func_80089A30_data.field_C);
        if (ptr == NULL)
        {
            return false;
        }
        ptr->field_14_16 = *arg3;
    }

    ptr->field_10   = arg2->field_0;
    ptr->field_14_0 = 0;
    ptr->field_C    = temp_s3;

    if (arg2->field_4.func_80089A30_data.field_5_7)
    {
        ptr->field_1C = arg2->field_4.func_80089A30_data.field_6;
    }

    return true;
}

bool func_80089BB8(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* arg2, u32* arg3) // 0x80089BB8
{
    s_func_8009ECCC* temp_a0;
    s_func_8009ECCC* temp_v0;
    u32              var_s1;

    if (arg0 == NULL || arg2 == NULL)
    {
        return false;
    }

    if (arg2->field_4.funcIdx_4 != 1)
    {
        return false;
    }

    if (arg1 == NULL)
    {
        var_s1 = arg2->field_4.func_80089BB8_data.field_C;
        arg1   = func_8009ECCC(arg0, var_s1);
        if (arg1 == NULL)
        {
            return false;
        }
        arg1->field_14_16 = *arg3;
    }
    else
    {
        if (arg1->field_10 != arg2)
        {
            arg1->field_10 = NULL;
            return false;
        }
        else
        {
            var_s1 = arg1->field_8;
        }
    }

    arg1->field_10   = arg2->field_0;
    arg1->field_14_0 = 0;

    if (arg2->field_4.func_80089BB8_data.field_5_7)
    {
        arg1->field_1C = arg2->field_4.func_80089BB8_data.field_6;
    }

    temp_v0 = func_8009ECCC(arg0, var_s1);
    if (temp_v0 != NULL)
    {
        temp_a0                   = temp_v0->field_0;
        temp_a0->field_4          = temp_v0->field_4;
        temp_a0->field_4->field_0 = temp_a0;

        temp_a0          = arg1->field_0;
        temp_v0->field_4 = arg1;
        temp_v0->field_0 = temp_a0;
        temp_a0->field_4 = temp_v0;

        arg1->field_0 = temp_v0;

        temp_v0->field_10    = arg2->field_4.func_80089BB8_data.field_8;
        temp_v0->field_14_0  = 0;
        temp_v0->field_C     = arg1->field_C;
        temp_v0->field_14_16 = arg1->field_14_16;
        temp_v0->field_1C    = arg1->field_1C;
    }

    return true;
}

bool func_80089D0C(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* arg2, u32* arg3) // 0x80089D0C
{
    if (arg0 == NULL || arg2 == NULL)
    {
        return false;
    }

    if (arg2->field_4.func_80089D0C_data.funcIdx_4 == 4)
    {
        if (arg1 != NULL)
        {
            arg1->field_14_24 = arg2->field_4.func_80089D0C_data.field_5 & 0x7F;
            arg1->field_1E    = arg2->field_4.func_80089D0C_data.field_6;
            arg1->field_10    = arg2->field_0;
            arg1->field_14_31 = 1;
            arg1->field_18    = arg1->field_14_16 << 24;
            return false;
        }
        else
        {
            arg1 = func_8009ECCC(arg0, arg2->field_4.func_80089D0C_data.field_C);
            if (arg1 != NULL)
            {
                arg1->field_10    = arg2;
                arg1->field_14_16 = *arg3;
                arg1->field_C     = arg2->field_4.func_80089D0C_data.field_8;
                return true;
            }
        }
    }

    return false;
}

bool func_80089DF0(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* arg2, u32* arg3) // 0x80089DF0
{
    u32 temp_a0;
    s32 temp_a0_2;
    u32 temp_lo;
    u8* temp_t5;
    s32 var_a1_2;
    u32 var_t1;
    u32 var_t3;
    u32 temp_t6;
    u32 temp_v1_3;
    u32 var_t0;
    u32 temp_t2;
    u32 temp_t4;
    u32 var_a1;
    u32 var_a2;
    u32 var_t7;
    u32 temp_s0;
    s32 temp;
    s32 temp2;
    u32 temp3;
    u32 temp4;
    u64 temp5;

    if (arg2 == NULL || arg1 == NULL || arg2->field_4.funcIdx_4 != 2)
    {
        return false;
    }

    if (arg1->field_10 != arg2)
    {
        arg1->field_10 = NULL;
        return false;
    }

    temp_t6 = arg1->field_14_0;

    if (!arg1->field_14_31)
    {
        arg1->field_14_31 = 1;

        temp_s0   = arg1->field_14_16;
        var_t1    = arg2->field_4.func_80089DF0_data.field_5 & 0x7F;
        temp_t5   = arg2->field_4.func_80089DF0_data.field_8;
        temp_t4   = arg2->field_4.func_80089DF0_data.field_C_16;
        var_a1    = arg2->field_4.func_80089DF0_data.field_C_28;
        temp_a0_2 = arg2->field_4.func_80089DF0_data.field_C_31;

        arg1->field_14_24 = var_t1;
        arg1->field_1E    = arg2->field_4.func_80089DF0_data.field_6;

        if (temp_t4 == 0)
        {
            var_t0 = temp_t6;
            var_t7 = 0;
        }
        else
        {
            var_t0 = (temp_t6 / temp_t4);
            var_t7 = temp_t6 % temp_t4;
        }

        if (temp_a0_2 == 0)
        {
            var_t7 = 0;
        }

        if (var_a1 == 0)
        {
            temp_t2 = var_t0 + 1;
            temp    = (temp_t5[var_t0 >> 3] >> (var_t0 & 7));
            var_t3  = temp & 1;
            var_t3  = -var_t3;

            temp2  = temp_t5[temp_t2 >> 3] >> (temp_t2 & 7);
            var_t1 = temp2 & 1;
            var_t1 = -var_t1;
        }
        else
        {
            if (var_a1 >= 5)
            {
                var_a1 = 4;
            }

            var_t0 = var_t0 * var_a1;

            var_t3 = 0;
            var_t1 = 0;

            for (var_a2 = var_a1, var_a1_2 = 0x18, temp_t2 = var_t0 + var_a2; var_a2 != 0;
                 var_a2--, var_a1_2 -= 8, var_t0++, temp_t2++)
            {
                var_t3 += temp_t5[var_t0] << var_a1_2;
                var_t1 += temp_t5[temp_t2] << var_a1_2;
            }
        }

        if (var_t7 == 0)
        {
            temp_a0 = var_t3;
        }
        else
        {
            temp_lo = ((UINT_MAX / temp_t4) + 1) * var_t7;
            temp3   = (var_t3 * (u64)-temp_lo) >> 32;
            temp4   = (var_t1 * (u64)temp_lo) >> 32;
            temp_a0 = temp4 + temp3;
        }

        temp5 = (u64)temp_a0 * temp_s0 >> 7;

        if (temp5 > UINT_MAX)
        {
            temp_a0 = UINT_MAX;
        }
        else
        {
            temp_a0 = temp5;
        }

        arg1->field_18 = temp_a0;
    }

    temp_a0   = *arg3;
    temp_v1_3 = arg2->field_4.func_80089DF0_data.field_C_0;
    temp_t6   = temp_t6 + temp_a0;

    if (temp_t6 >= temp_v1_3)
    {
        arg1->field_10   = arg2->field_0;
        arg1->field_14_0 = 0;
        temp_a0          = temp_t6 - temp_v1_3;
        *arg3            = temp_a0;

        return true;
    }

    arg1->field_14_0 = temp_t6;
    *arg3            = 0;

    return false;
}
