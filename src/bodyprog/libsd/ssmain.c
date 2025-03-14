#include "common.h"
#include "bodyprog/libsd.h"

void SsSetMVol(s16 left, s16 right) // 0x800A2294
{
    SdSetMVol(left, right);
}

void SsEnd() // 0x800A22C0
{
    SdEnd();
}

void SsSetSerialAttr(char s_num, char attr, char mode) // 0x800A22E0
{
    SdSetSerialAttr(s_num, attr, mode);
}

void SsSetSerialVol(char s_num, s16 voll, s16 volr) // 0x800A2308
{
    SdSetSerialVol(s_num, voll, volr);
}

void SsUtAllKeyOff(s16 mode) // 0x800A2338
{
    SdUtAllKeyOff(mode);
}
