#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/save_system.h"
#include "main/fsqueue.h"

void func_8002E630() // 0x8002E630
{
    s_800B5508* ptr;
    s32         i;

    func_800303E4();

    D_800B5480 = 0;

    // Clear arrays.
    bzero(D_800B5508, 1816);
    bzero(D_800B2780, 768);

    for (i = 0; i < 8; i++) 
    {
        D_800B5508[i].field_0 = 0;
        
        func_8002E730(i);

        switch (i) 
        {                          
            case 0:
                ptr = D_800B2780;
                break;

            case 4:
                ptr = D_800B3680;
                break;

            default:
                ptr = D_800B4580;
                break;
        }

        D_800B5508[i].field_14 = ptr;

        func_8002E6E4(i);
    } 
}

void func_8002E6E4(s32 idx) // 0x8002E6E4
{
    D_800B5508[idx].field_0 = 0;
    func_8002E730(idx);
    bzero(D_800B5508[idx].field_14, 0xF00);
    D_800B5508[idx].field_18 = 0;
}

void func_8002E730(s32 idx) // 0x8002E730
{
    s32 i;

    for (i = 0; i < 15; i++) 
    {
        D_800B5508[idx].field_4[i] = 0;
    }
}

s32 func_8002E76C(s32 idx) // 0x8002E76C
{
    s32 ret;
    s32 i;

    ret = 1;

    for (i = 0; i < 15; i++)
    {    
        if (D_800B5508[idx].field_4[i] != 0) 
        {
            ret = 0; 
            break;
        }
    }

    return ret;
}

void func_8002E7BC() // 0x8002E7BC
{
    s_800B55E8* ptr;

    if (D_800B5480 == 1)
    {
        return;
    }

    D_800B5480 = 1;
    func_8002E8E4();
    func_80030414();

    D_800B55E8[0].field_0  = 0;
    D_800B55E8[0].field_4  = 0;
    D_800B55E8[0].field_8  = 0;
    D_800B55E8[0].field_C  = 0;
    D_800B55E8[0].field_10 = 0;
    D_800B55E8[0].field_14 = 0;
    D_800B55E8[1].field_0  = 0;

    ptr = &D_800B55E8[1];
    ptr->field_4  = 0;
    ptr->field_8  = 0;
    ptr->field_C  = 0;
    ptr->field_10 = 0;
    ptr->field_14 = 0;
}

void func_8002E830() // 0x8002E830
{
    if (D_800B5480 != 0) 
    {
        D_800B5480 = 0;
        func_80030640();
    }
}

void func_8002E85C() // 0x8002E85C
{
    D_800B5618 = 1;
}

void func_8002E86C() // 0x8002E86C
{
    s32* ptr;

    D_800B5508[9].field_14 = 0;
    D_800B5508[8].field_18 = 0;

    ptr    = &D_800B5508[8].field_18;
    ptr[1] = 0;
    ptr[2] = 0;
    ptr[3] = 0;
    ptr[4] = 0;
    ptr[5] = 0;
}

s32 func_8002E898() // 0x8002E898
{
    s32 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < 8; i++)
    {
        ret |= D_800B5508[i].field_0 << (i * 3);
    }

    return ret;
}

void func_8002E8D4() // 0x8002E8D4
{
    D_800B5618 = 1;
}

void func_8002E8E4() // 0x8002E8E4
{
    s_800B55E8* ptr;

    D_800B5508[9].field_14 = NULL;
    D_800B5508[8].field_18 = 0;
    
    ptr = &D_800B5508[8].field_18;
    
    ptr->field_4  = 0;
    ptr->field_8  = 0;
    ptr->field_C  = 0;
    ptr->field_10 = 0;
    ptr->field_14 = 1;
}

s32 func_8002E914() // 0x8002E914
{
    s32 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < 8; i++)
    {
        ret |= D_800B5508[i].field_0 << (i * 2);
    }

    return ret;
}
