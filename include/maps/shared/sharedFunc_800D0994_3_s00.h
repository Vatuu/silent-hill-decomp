void sharedFunc_800D0994_3_s00()
{
    #define TEST_FLAG       (1 << 7)
    #define OVERLAY_VAL_ON  0x10
    #define OVERLAY_VAL_OFF 0x19

    s32 mapOverlayVal;

    mapOverlayVal = ((g_SavegamePtr->eventFlags_18C & TEST_FLAG) == 0) ? OVERLAY_VAL_OFF : OVERLAY_VAL_ON;
    func_8003640C(mapOverlayVal);
}