#include "common.h"

INCLUDE_ASM("asm/main/nonmatchings/main_5", func_800120B8);

extern u32 func_800120B8(void);

u32 func_800120E4() 
{
    return func_800120B8() >> 17;
}

extern int D_80022C90;

s32 func_80012104() 
{
    return D_80022C90;
}

void func_80012110(s32 arg0) 
{
    D_80022C90 = arg0;
}

u32 func_8001211C()
{
    return func_800120B8() >> 20;
}

void func_8001213C(int *dst, int *src, int size)
{
    int *end;
    int  data;
    
    if (dst == src)
    {
        return;
    }
        
    size >>= 2;

    if (dst < src)
    {
        end = src + size;

        while (src < end)
        {
            data = *src++;
            *dst++ = data;
        }
    }
    else
    {   
        end = src;

        dst += size;            
        src += size;

        while (src > end)
        {
            *(--dst) = *(--src);
        }
    }
}

