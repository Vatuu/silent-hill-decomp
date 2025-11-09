void sharedFunc_800D0994_3_s00(void)
{
    #define OVERLAY_VAL_ON  0x10
    #define OVERLAY_VAL_OFF 0x19

    s32 mapOverlayVal;

    mapOverlayVal = !Savegame_EventFlagGet(EventFlag_295) ? OVERLAY_VAL_OFF : OVERLAY_VAL_ON;
    func_8003640C(mapOverlayVal);
}
