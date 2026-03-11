#include "common.h"

// HP_SAFE1: Second anti-modchip overlay, ran after S__SAFE2 code has run.
// Instead of calling `safechk` anti-modchip code, this calls some graphics-init functions which are normally called at
// the start of `MainLoop`.
// Likely been moved here so cracking the game by skipping these overlays would cause things to break.

void AntiModchip_Check(void) // JAP0 0x801E7EB4
{
    while (func_8004CB54(0, 2, 0) != 0)
    {
        VSync(0);
    }
    
    func_8004CB6C();

    func_8004CB90();
}
